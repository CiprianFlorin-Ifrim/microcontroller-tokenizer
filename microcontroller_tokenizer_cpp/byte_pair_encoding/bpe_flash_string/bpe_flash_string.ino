#include "bpe_vocabulary.h"

void setup() {
    Serial.begin(115200);

    // Example input string
    char inputStr[] = "  Hello world!  ";

    // Clean the input string
    cleanInput(inputStr);
    trimWhitespace(inputStr);

    // Output cleaned input for debugging
    Serial.print("Cleaned Input: ");
    Serial.println(inputStr);

    // Allocate buffer for encoded tokens
    int maxTokens = 100;  // Adjust this based on expected output size
    uint8_t outputTokens[maxTokens * 3];  // Each token is stored as 3 bytes (24 bits)
    int outputSize = 0;

    // Tokenize the cleaned input string
    tokenizeBPE(inputStr, outputTokens, outputSize);

    // Output the tokenized binary result
    Serial.print("Tokenized Output (Binary): ");
    for (int i = 0; i < outputSize; i++) {
        Serial.print(outputTokens[i], BIN);
        Serial.print(" ");
    }
    Serial.println();
}

void loop() {
    // No need for loop code since everything is done in setup
}