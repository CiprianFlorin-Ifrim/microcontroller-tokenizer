#include <Arduino.h>
#include "huffman_codes.h"

void preprocessPhrase(char* phrase, char* result);
void encodePhrase(const char* phrase, char* encoded);
void decodePhrase(const char* encoded, char* decoded);
bool isSymbol(char c);
void calculateMemoryUsage(const char* input, const char* encoded);

void setup() {
    // Initialize serial communication at 2 million baud rate
    Serial.begin(2000000);
    while (!Serial) {
        ; // Wait for the serial port to connect
    }

    // Prompt user input
    Serial.println("Enter a phrase to encode and decode using Huffman coding:");
}

void loop() {
    if (Serial.available() > 0) {
        // Dynamically allocate memory for input
        char* input = (char*)malloc(512 * sizeof(char));
        if (input == NULL) {
            Serial.println("Failed to allocate memory for input.");
            return;
        }
        
        size_t len = Serial.readBytesUntil('\n', input, 511);
        input[len] = '\0';  // Null-terminate the input

        // Dynamically allocate memory for preprocessing result
        char* processed = (char*)malloc(512 * sizeof(char));
        if (processed == NULL) {
            Serial.println("Failed to allocate memory for preprocessing.");
            free(input);
            return;
        }

        // Convert to lowercase and preprocess
        preprocessPhrase(input, processed);
        Serial.print("Processed Phrase: ");
        Serial.println(processed);

        // Dynamically allocate memory for encoding
        char* encoded = (char*)malloc(2048 * sizeof(char));
        if (encoded == NULL) {
            Serial.println("Failed to allocate memory for encoding.");
            free(input);
            free(processed);
            return;
        }
        encoded[0] = '\0';  // Initialize encoded string as empty

        // Encode the phrase using Huffman codes
        encodePhrase(processed, encoded);
        Serial.print("Encoded Phrase: ");
        Serial.println(encoded);

        // Dynamically allocate memory for decoding
        char* decoded = (char*)malloc(512 * sizeof(char));
        if (decoded == NULL) {
            Serial.println("Failed to allocate memory for decoding.");
            free(input);
            free(processed);
            free(encoded);
            return;
        }
        decoded[0] = '\0';  // Initialize decoded string as empty

        // Decode the encoded phrase back to original
        decodePhrase(encoded, decoded);
        Serial.print("Decoded Phrase: ");
        Serial.println(decoded);

        // Calculate and display memory usage
        calculateMemoryUsage(processed, encoded);

        // Free allocated memory
        free(input);
        free(processed);
        free(encoded);
        free(decoded);

        // Wait before the next loop
        delay(5000);
    }
}

// Function to preprocess and clean the phrase, adding spaces around punctuation and symbols
void preprocessPhrase(char* phrase, char* result) {
    int j = 0;
    char prev_char = ' ';

    for (int i = 0; phrase[i] != '\0'; i++) {
        char c = tolower(phrase[i]);

        if (isSymbol(c) || isSymbol(prev_char)) {
            result[j++] = ' ';
        }
        result[j++] = c;
        prev_char = c;
    }

    result[j] = '\0';  // Null-terminate the result
}

// Function to encode a phrase using Huffman codes
void encodePhrase(const char* phrase, char* encoded) {
    char phrase_copy[512];
    strcpy(phrase_copy, phrase);

    char* token = strtok(phrase_copy, " ");
    while (token != NULL) {
        bool found = false;
        for (size_t i = 0; i < huffmanTableSize; i++) {
            if (strcmp(huffmanTable[i].token, token) == 0) {
                strcat(encoded, huffmanTable[i].code);
                strcat(encoded, " ");
                found = true;
                break;
            }
        }
        if (!found) {
            Serial.print("Token not found: ");
            Serial.println(token);
        }
        token = strtok(NULL, " ");
    }

    size_t len = strlen(encoded);
    if (len > 0 && encoded[len - 1] == ' ') {
        encoded[len - 1] = '\0';  // Remove trailing space
    }
}

// Function to decode the encoded phrase back to the original
void decodePhrase(const char* encoded, char* decoded) {
    char encoded_copy[2048];
    strcpy(encoded_copy, encoded);

    char* code = strtok(encoded_copy, " ");
    while (code != NULL) {
        bool found = false;
        for (size_t i = 0; i < huffmanTableSize; i++) {
            if (strcmp(huffmanTable[i].code, code) == 0) {
                strcat(decoded, huffmanTable[i].token);
                strcat(decoded, " ");
                found = true;
                break;
            }
        }
        if (!found) {
            Serial.print("Code not found: ");
            Serial.println(code);
        }
        code = strtok(NULL, " ");
    }

    size_t len = strlen(decoded);
    if (len > 0 && decoded[len - 1] == ' ') {
        decoded[len - 1] = '\0';  // Remove trailing space
    }
}

// Function to calculate and display memory usage in bits and bytes
void calculateMemoryUsage(const char* input, const char* encoded) {
    size_t input_bits = strlen(input) * 8;  // Each character is 8 bits
    size_t input_bytes = strlen(input);

    size_t encoded_bits = 0;
    for (size_t i = 0; encoded[i] != '\0'; i++) {
        if (encoded[i] != ' ') {
            encoded_bits++;
        }
    }
    size_t encoded_bytes = (encoded_bits + 7) / 8;  // Convert bits to bytes (rounding up)

    Serial.print("Original String Size: ");
    Serial.print(input_bits);
    Serial.print(" bits (");
    Serial.print(input_bytes);
    Serial.println(" bytes)");

    Serial.print("Encoded Size: ");
    Serial.print(encoded_bits);
    Serial.print(" bits (");
    Serial.print(encoded_bytes);
    Serial.println(" bytes)");
}

bool isSymbol(char c) {
    // Returns true if the character is a symbol or punctuation
    return ispunct(c);
}
