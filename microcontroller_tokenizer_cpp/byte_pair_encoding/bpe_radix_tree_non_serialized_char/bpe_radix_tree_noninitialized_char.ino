#include "radix_tree.h"
#include <ctype.h>
#include <string.h>

// Function to clean the input: convert to lowercase, remove non-ASCII characters, and trim whitespace
void cleanInput(char* input) {
    char cleanedInput[256];
    size_t j = 0;

    // Convert to lowercase and handle each character
    for (size_t i = 0; input[i] != '\0'; i++) {
        if ((unsigned char)input[i] < 128) { // Keep only ASCII characters
            char c = tolower(input[i]);

            // Check if the character is a punctuation or symbol, and add spaces around it
            if (ispunct(c) || isspace(c)) {
                if (j > 0 && !isspace(cleanedInput[j - 1])) {
                    cleanedInput[j++] = ' '; // Add space before punctuation/symbol
                }
                cleanedInput[j++] = c; // Add the punctuation/symbol
                if (input[i + 1] != '\0' && !isspace(input[i + 1])) {
                    cleanedInput[j++] = ' '; // Add space after punctuation/symbol
                }
            } else {
                cleanedInput[j++] = c; // Add the character as is
            }
        }
    }

    cleanedInput[j] = '\0';

    // Trim leading and trailing whitespace
    char* start = cleanedInput;
    while (isspace((unsigned char)*start)) {
        start++;
    }

    char* end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }

    *(end + 1) = '\0';

    // Copy the cleaned and trimmed string back to the input
    strcpy(input, start);
}

// Function to find and print the token ID for each word/punctuation in the input
void processAndFindTokens(char* input) {
    char* token = strtok(input, " ");
    while (token != NULL) {
        Serial.print("Split word: ");
        Serial.println(token);

        RadixNode* currentNode = &root;
        size_t position = 0;
        bool found = true;

        while (token[position] != '\0' && found) {
            found = false;
            for (int i = 0; i < sizeof(currentNode->children) / sizeof(currentNode->children[0]); i++) {
                if (currentNode->children[i].prefix == NULL) {
                    break;
                }
                if (strncmp(&token[position], currentNode->children[i].prefix, strlen(currentNode->children[i].prefix)) == 0) {
                    position += strlen(currentNode->children[i].prefix);
                    currentNode = currentNode->children[i].node;
                    found = true;
                    break;
                }
            }
        }

        if (found && currentNode->tokenID != -1) {
            Serial.print("Node ID: ");
            Serial.println(currentNode->tokenID);
        } else {
            Serial.print("Not found: ");
            Serial.println(token);
        }

        token = strtok(NULL, " ");
    }
    Serial.println();
}

void setup() {
    Serial.begin(9600);
    while (!Serial) {}
    Serial.println("Enter a phrase:");
}

void loop() {
    if (Serial.available() > 0) {
        char inputPhrase[256];
        size_t len = Serial.readBytesUntil('\n', inputPhrase, sizeof(inputPhrase) - 1);
        inputPhrase[len] = '\0';

        // Clean the input
        cleanInput(inputPhrase);

        // Output the cleaned phrase
        Serial.print("Cleaned phrase: ");
        Serial.println(inputPhrase);

        // Split and process each word/punctuation
        processAndFindTokens(inputPhrase);

        Serial.println("Enter another phrase:");
    }
}
