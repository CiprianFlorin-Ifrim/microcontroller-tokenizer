#include <Arduino.h>
#include <ctype.h> // For tolower()

// Huffman encoding table including lowercase letters, digits, punctuation, and whitespace
struct HuffmanCode {
    char character;
    const char* code;
};

HuffmanCode huffmanTable[] = {
    {'a', "00"}, {'b', "01"}, {'c', "100"}, {'d', "101"},
    {'e', "1100"}, {'f', "1101"}, {'g', "11100"}, {'h', "11101"},
    {'i', "11110"}, {'j', "111110"}, {'k', "111111"}, {'l', "00000"},
    {'m', "00001"}, {'n', "00010"}, {'o', "00011"}, {'p', "00100"},
    {'q', "00101"}, {'r', "00110"}, {'s', "00111"}, {'t', "01000"},
    {'u', "01001"}, {'v', "01010"}, {'w', "01011"}, {'x', "01100"},
    {'y', "01101"}, {'z', "01110"},
    {'0', "000101"}, {'1', "000110"}, {'2', "000111"}, {'3', "001000"},
    {'4', "001001"}, {'5', "001010"}, {'6', "001011"}, {'7', "001100"},
    {'8', "001101"}, {'9', "001110"},
    {' ', "001111"}, {'.', "010000"}, {',', "010001"}, {'!', "010010"},
    {'?', "010011"}, {';', "010100"}, {':', "010101"}, {'\'', "010110"},
    {'"', "010111"}, {'-', "011000"}, {'_', "011001"}, {'(', "011010"},
    {')', "011011"}, {'[', "011100"}, {']', "011101"}, {'{', "011110"},
    {'}', "011111"}, {'<', "100000"}, {'>', "100001"}, {'@', "100010"},
    {'#', "100011"}, {'$', "100100"}, {'%', "100101"}, {'^', "100110"},
    {'&', "100111"}, {'*', "101000"}
};

// Utility function to set bits in a byte array
void setBits(uint8_t* data, int bitPosition, const char* bits) {
    while (*bits) {
        if (*bits == '1') {
            data[bitPosition / 8] |= (1 << (7 - (bitPosition % 8)));
        }
        bitPosition++;
        bits++;
    }
}

// Convert the entire input string to lowercase
String toLowerCase(const char* input) {
    String lowercased = "";
    while (*input != '\0') {
        lowercased += tolower(*input);
        input++;
    }
    return lowercased;
}

// Run-Length Encoding (RLE) function
String runLengthEncode(const char* input) {
    String rleOutput = "";
    int count = 1;
    while (*input != '\0') {
        char currentChar = *input;
        char nextChar = *(input + 1);
        if (currentChar == nextChar) {
            count++;
        } else {
            rleOutput += String(count) + currentChar;
            count = 1;
        }
        input++;
    }
    return rleOutput;
}

int encodeHuffmanRLE(const char* input, uint8_t* encodedBits, int* lengths) {
    String lowercasedInput = toLowerCase(input);  // Convert input to lowercase
    String rleOutput = runLengthEncode(lowercasedInput.c_str());
    int bitPosition = 0;
    int lengthCount = 0;

    for (int i = 0; i < rleOutput.length(); i++) {
        char character = rleOutput[i];
        for (int j = 0; j < sizeof(huffmanTable) / sizeof(HuffmanCode); j++) {
            if (huffmanTable[j].character == character) {
                int codeLength = strlen(huffmanTable[j].code);
                lengths[lengthCount++] = codeLength;  // Store length in the array
                setBits(encodedBits, bitPosition, huffmanTable[j].code);
                bitPosition += codeLength;
                break;
            }
        }
    }

    return lengthCount;  // Return number of lengths stored
}

String decodeHuffmanRLE(const uint8_t* encodedBits, int bitLength, int* lengths, int lengthCount) {
    String decoded = "";
    int bitPosition = 0;

    for (int i = 0; i < lengthCount; i++) {
        int codeLength = lengths[i];  // Get the length for this code

        String code = "";

        for (int j = 0; j < codeLength; j++) {
            int byteIndex = (bitPosition + j) / 8;
            int bitIndex = 7 - ((bitPosition + j) % 8);
            char bit = (encodedBits[byteIndex] & (1 << bitIndex)) ? '1' : '0';
            code += bit;
        }
        bitPosition += codeLength;

        bool matchFound = false;
        for (int j = 0; j < sizeof(huffmanTable) / sizeof(HuffmanCode); j++) {
            if (code.equals(huffmanTable[j].code)) {
                decoded += huffmanTable[j].character;
                matchFound = true;
                break;
            }
        }

        if (!matchFound) {
            Serial.println("Decoding error: no match found for code " + code);
            return "";
        }
    }

    // Decoding the RLE encoded string back to the original string
    String rleDecoded = "";
    for (int i = 0; i < decoded.length(); i++) {
        int count = 0;
        while (isdigit(decoded[i])) {
            count = count * 10 + (decoded[i] - '0');
            i++;
        }
        char character = decoded[i];
        for (int j = 0; j < count; j++) {
            rleDecoded += character;
        }
    }

    return rleDecoded;
}

void setup() {
    Serial.begin(115200);
    while (!Serial) {
        ; // Wait for serial port to connect.
    }
    Serial.println("Enter text to encode with Huffman:");
}

void loop() {
    if (Serial.available() > 0) {
        String input = Serial.readString();
        input.trim(); // Remove any leading/trailing whitespace

        uint8_t encodedBits[256] = {0};  // 256 bytes buffer for encoded data
        int lengths[256] = {0};  // Array to store lengths
        int lengthCount = 0;

        lengthCount = encodeHuffmanRLE(input.c_str(), encodedBits, lengths);

        // Calculate memory usage
        int inputBits = input.length() * 8;
        int encodedBitsUsed = 0;
        for (int i = 0; i < lengthCount; i++) {
            encodedBitsUsed += lengths[i];
        }
        int lengthBitsUsed = lengthCount * 4;  // Each length uses approximately 4 bits

        Serial.print("Input String: ");
        Serial.print(inputBits);
        Serial.print(" bits, ");
        Serial.print(inputBits / 8);
        Serial.println(" bytes");

        Serial.print("Huffman Encoded Bits: ");
        Serial.print(encodedBitsUsed);
        Serial.print(" bits, ");
        Serial.print((encodedBitsUsed + 7) / 8);
        Serial.println(" bytes");

        Serial.print("Length Array: ");
        Serial.print(lengthBitsUsed);
        Serial.print(" bits, ");
        Serial.print((lengthBitsUsed + 7) / 8);
        Serial.println(" bytes");

        Serial.print("Encoded Bits: ");
        for (int i = 0; i < (encodedBitsUsed + 7) / 8; i++) {
            Serial.print(encodedBits[i], BIN);
            Serial.print(" ");
        }
        Serial.println();

        Serial.print("Lengths: ");
        for (int i = 0; i < lengthCount; i++) {
            Serial.print(lengths[i]);
            Serial.print(" ");
        }
        Serial.println();

        // Decode the Huffman encoded string
        String decoded = decodeHuffmanRLE(encodedBits, encodedBitsUsed, lengths, lengthCount);
        Serial.print("Decoded: ");
        Serial.println(decoded);
    }
}
