#include "bpe_vocabulary_trie.h"

#define MAX_INPUT_SIZE 64  // Define a large enough buffer size to hold longer inputs

void setup() {
    Serial.begin(115200);
    while (!Serial) {
        ; // Wait for the serial port to connect (for Leonardo/Micro boards)
    }

    // Initialize the Trie with the vocabulary data
    setupTrie();

    Serial.println("Ready for input...");
}

void loop() {
    // Check if there is any input from the serial monitor
    // if (Serial.available() > 0) {
    //     char inputStr[MAX_INPUT_SIZE] = {0}; // Initialize a buffer to store the input
    //     int index = 0;

    //     // Read data from the serial until newline or the buffer is full
    //     while (Serial.available() > 0 && index < MAX_INPUT_SIZE - 1) {
    //         char incomingByte = Serial.read();
    //         if (incomingByte == '\n') {
    //             break; // Exit the loop if a newline character is detected
    //         }
    //         inputStr[index++] = incomingByte;
    //     }

    //     // Null-terminate the string
    //     inputStr[index] = '\0';

    //     // Clean the input string
    //     cleanInput(inputStr);
    //     trimWhitespace(inputStr);

    //     // Output cleaned input for debugging
    //     Serial.print("Cleaned Input: ");
    //     Serial.println(inputStr);

    //     // Allocate buffer for encoded tokens
    //     int maxTokens = 100;  // Adjust this based on expected output size
    //     uint8_t outputTokens[maxTokens * 3];  // Each token is stored as 3 bytes (24 bits)
    //     int outputSize = 0;

    //     // Tokenize the cleaned input string
    //     tokenizeBPE(inputStr, outputTokens, outputSize);

    //     // Output the tokenized binary result
    //     Serial.print("Tokenized Output (Binary): ");
    //     for (int i = 0; i < outputSize; i++) {
    //         Serial.print(outputTokens[i], BIN);
    //         Serial.print(" ");
    //     }
    //     Serial.println();

    //     // Clear the serial buffer
    //     while (Serial.available() > 0) {
    //         Serial.read();
    //     }
    // }
}
