
#include "bpe_vocabulary.h"

#define MAX_INPUT_SIZE 512  // Define a large enough buffer size to hold longer inputs

void setup() {
    Serial.begin(115200);
    while (!Serial) {
        ; // Wait for the serial port to connect (for Leonardo/Micro boards)
    }
}

void loop() {
    // Check if there is any input from the serial monitor
    if (Serial.available() > 0) {
        char inputStr[MAX_INPUT_SIZE] = {0}; // Initialize a buffer to store the input
        int index = 0;

        // Read the input from the serial monitor
        while (Serial.available() > 0 && index < MAX_INPUT_SIZE - 1) {
            inputStr[index++] = Serial.read();
        }
        inputStr[index] = '\0'; // Null-terminate the input string

        // Process the input using BPE
        uint8_t outputTokens[MAX_INPUT_SIZE] = {0};  // Buffer to store the tokenized output
        int outputSize = 0;
        tokenizeBPE(inputStr, outputTokens, &outputSize);

        // Output the tokenized result
        for (int i = 0; i < outputSize; i++) {
            Serial.print(outputTokens[i], HEX);
            Serial.print(" ");
        }
        Serial.println();
    }
}
