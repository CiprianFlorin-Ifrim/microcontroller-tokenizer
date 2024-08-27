#include <Arduino.h>
#include <ctype.h> // For tolower()
#include "esp_heap_caps.h"

// Huffman encoding table including spaces and common punctuation
struct HuffmanCode {
  char character;
  const char* code;
};

// Store the Huffman table in flash memory automatically
const HuffmanCode huffmanTable[] = {
  {'e', "00"}, {'t', "01"}, {'a', "100"}, {'o', "101"},
  {'i', "1100"}, {'n', "1101"}, {'s', "1110"}, {'h', "1111"},
  {'r', "0000"}, {'d', "0001"}, {'l', "0010"}, {'c', "0011"},
  {'u', "0100"}, {'m', "0101"}, {'w', "0110"}, {'f', "0111"},
  {'g', "1000"}, {'y', "1001"}, {'p', "1010"}, {'b', "1011"},
  {'v', "11000"}, {'k', "11001"}, {'x', "11010"}, {'j', "11011"},
  {'q', "11100"}, {'z', "11101"}, {' ', "00000"}, {'.', "00001"},
  {',', "00100"}, {'!', "00101"}, {'?', "00110"}, {'-', "00111"},
  {'\'', "01000"}, {'\"', "01001"}, {'(', "01010"}, {')', "01011"},
  {';', "01100"}, {':', "01101"},
};

void setBits(uint8_t* data, int bitPosition, const char* bits, int& maxBitPosition) {
  while (*bits) {
    if (*bits == '1') {
      data[bitPosition / 8] |= (1 << (7 - (bitPosition % 8)));
    }
    bitPosition++;
    if (bitPosition > maxBitPosition) {
        maxBitPosition = bitPosition;  // Track the maximum position reached
    }
    bits++;
  }
}

void toLowerCaseString(String &input) {
    for (int i = 0; i < input.length(); i++) {
        input[i] = tolower(input[i]);
    }
}

void cleanString(String &input) {
    int j = 0;
    for (int i = 0; i < input.length(); i++) {
        char c = input[i];
        for (int k = 0; k < sizeof(huffmanTable) / sizeof(HuffmanCode); k++) {
            if (c == huffmanTable[k].character) {
                input[j++] = c;
                break;
            }
        }
    }
    input.remove(j);
}

int calculateBufferSize(const char* input) {
    int totalBits = 0;
    while (*input != '\0') {
        for (int i = 0; i < sizeof(huffmanTable) / sizeof(HuffmanCode); i++) {
            if (huffmanTable[i].character == *input) {
                totalBits += strlen(huffmanTable[i].code);
                break;
            }
        }
        input++;
    }
    return (totalBits + 7) / 8;  // Convert bits to bytes
}

int encodeHuffman(const char* input, uint8_t* encodedBits, uint8_t* binaryLengths, int& bitLengthCount) {
  int bitPosition = 0;
  int lengthPosition = 0;
  bitLengthCount = 0;
  int maxBitPosition = 0;

  while (*input != '\0') {
    char character = *input;
    for (int i = 0; i < sizeof(huffmanTable) / sizeof(HuffmanCode); i++) {
      if (huffmanTable[i].character == character) {
        const char* code = huffmanTable[i].code;
        int codeLength = strlen(code);

        // Append the Huffman code to the encodedBits array
        setBits(encodedBits, bitPosition, code, maxBitPosition);
        bitPosition += codeLength;

        // Store the length in binary format in the binaryLengths array
        for (int j = 0; j < 3; j++) {
          int bit = (codeLength >> (2 - j)) & 1;
          if (bit) {
            binaryLengths[lengthPosition / 8] |= (1 << (7 - (lengthPosition % 8)));
          }
          lengthPosition++;
        }
        bitLengthCount++;
        break;
      }
    }
    input++;
  }

  return (maxBitPosition + 7) / 8; // Number of bytes used for encodedBits
}

String decodeHuffman(uint8_t* encodedBits, int bitLength, uint8_t* binaryLengths, int bitLengthCount) {
  String decoded = "";
  int bitPosition = 0;
  int lengthPosition = 0;

  for (int i = 0; i < bitLengthCount; i++) {
    int codeLength = 0;

    // Extract the length from the binaryLengths array
    for (int j = 0; j < 3; j++) {
      int bit = (binaryLengths[lengthPosition / 8] >> (7 - (lengthPosition % 8))) & 1;
      codeLength = (codeLength << 1) | bit;
      lengthPosition++;
    }

    String code = "";

    for (int j = 0; j < codeLength; j++) {
      int bit = (encodedBits[bitPosition / 8] >> (7 - (bitPosition % 8))) & 1;
      code += bit ? '1' : '0';
      bitPosition++;
    }

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
      break;
    }
  }

  return decoded;
}

void printMemoryUsage() {
  // Heap Memory
  Serial.print("Total Heap: ");
  Serial.print(ESP.getHeapSize());
  Serial.println(" bytes");

  Serial.print("Free Heap: ");
  Serial.print(ESP.getFreeHeap());
  Serial.println(" bytes");

  Serial.print("Min Free Heap: ");
  Serial.print(ESP.getMinFreeHeap());
  Serial.println(" bytes");

  // PSRAM (if available)
  if (psramFound()) {
    Serial.print("Total PSRAM: ");
    Serial.print(ESP.getPsramSize());
    Serial.println(" bytes");

    Serial.print("Free PSRAM: ");
    Serial.print(ESP.getFreePsram());
    Serial.println(" bytes");
  } else {
    Serial.println("PSRAM not available");
  }

  // Flash (This is more about free space in the internal flash filesystem, not the program memory)
  Serial.print("Flash Chip Size: ");
  Serial.print(ESP.getFlashChipSize());
  Serial.println(" bytes");

  Serial.print("Sketch Size: ");
  Serial.print(ESP.getSketchSize());
  Serial.println(" bytes");

  Serial.print("Free Sketch Space: ");
  Serial.print(ESP.getFreeSketchSpace());
  Serial.println(" bytes");

  Serial.print("Flash Frequency: ");
  Serial.print(ESP.getFlashChipSpeed() / 1000000);
  Serial.println(" MHz");

  Serial.print("Flash Mode: ");
  Serial.println(ESP.getFlashChipMode());
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // Wait for serial port to connect.
  }

  // Example input string
  String inputStr = "Most rockets can be launched from the ground because exhaust thrust from the engine is bigger than the weight of the vehicle on Earth. Some are used to bring satellites into orbit, for example from a spaceport. Some rockets such as ion thrusters are too weak and heavy to lift themselves. They work after other rockets bring them to outer space.";
  
  // Lowercase the input and clean it
  toLowerCaseString(inputStr);
  cleanString(inputStr);

  // Dynamically calculate required buffer sizes
  int bufferSize = calculateBufferSize(inputStr.c_str()) * 2;  // *2 to be safe
  int lengthBufferSize = (inputStr.length() * 3 + 7) / 8;  // Assuming each character needs 3 bits for length

  // Allocate buffers dynamically
  uint8_t* encodedBits = new uint8_t[bufferSize]();
  uint8_t* binaryLengths = new uint8_t[lengthBufferSize]();
  int bitLengthCount = 0;

  int bytesUsed = encodeHuffman(inputStr.c_str(), encodedBits, binaryLengths, bitLengthCount);

  // Calculate memory usage
  int lengthBitsUsed = bitLengthCount * 3;  // Each length uses 3 bits
  int huffmanBitsUsed = bytesUsed * 8;      // Total bits used for Huffman encoding
  int lengthBytesUsed = (lengthBitsUsed + 7) / 8; // Convert length bits to bytes
  int huffmanBytesUsed = (huffmanBitsUsed + 7) / 8; // Convert huffman bits to bytes

  Serial.println("");
  Serial.print("Original Input String: ");
  Serial.println(inputStr);

  Serial.print("Input String: ");
  Serial.print(inputStr.length() * 8);
  Serial.print(" bits, ");
  Serial.print(inputStr.length());
  Serial.println(" bytes");

  Serial.print("Huffman Encoded Bits: ");
  Serial.print(huffmanBitsUsed);
  Serial.print(" bits, ");
  Serial.print(huffmanBytesUsed);
  Serial.println(" bytes");

  Serial.print("Lengths Memory Usage: ");
  Serial.print(lengthBitsUsed);
  Serial.print(" bits, ");
  Serial.print(lengthBytesUsed);
  Serial.println(" bytes");

  Serial.print("Total Memory Usage: ");
  Serial.print(lengthBitsUsed + huffmanBitsUsed);
  Serial.print(" bits, ");
  Serial.print(lengthBytesUsed + huffmanBytesUsed);
  Serial.println(" bytes");

  Serial.print("Encoded Bits: ");
  for (int i = 0; i < huffmanBytesUsed; i++) {
    Serial.print(encodedBits[i], BIN);
    Serial.print(" ");
  }
  Serial.println();

  Serial.print("Binary Lengths: ");
  for (int i = 0; i < lengthBytesUsed; i++) {
    Serial.print(binaryLengths[i], BIN);
    Serial.print(" ");
  }
  Serial.println();

  // Decode the Huffman encoded string
  String decoded = decodeHuffman(encodedBits, huffmanBytesUsed, binaryLengths, bitLengthCount);
  Serial.print("Decoded: ");
  Serial.println(decoded);

  // Clean up dynamically allocated memory
  delete[] encodedBits;
  delete[] binaryLengths;

  // Print memory usage after processing input
  printMemoryUsage();
}

void loop() {
  // No need for loop code since everything is done in setup
}
