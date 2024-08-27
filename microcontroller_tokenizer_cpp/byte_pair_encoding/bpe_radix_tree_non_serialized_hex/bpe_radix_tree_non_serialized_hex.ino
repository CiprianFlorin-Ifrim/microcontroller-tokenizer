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

// Function to compare the input token with the radix tree prefix byte by byte
bool comparePrefix(const char* token, const uint32_t prefix, size_t prefix_len) {
    for (size_t i = 0; i < prefix_len; i++) {
        // Extract each byte from the prefix
        char prefixChar = (prefix >> ((3 - i) * 8)) & 0xFF;

        // If the extracted character is null or doesn't match, return false
        if (prefixChar == 0 || token[i] != prefixChar) {
            return false;
        }
    }
    return true;
}


size_t calculatePrefixLen(uint32_t prefix) {
    if (prefix & 0xFF000000) {
        return 4;
    } else if (prefix & 0x00FF0000) {
        return 3;
    } else if (prefix & 0x0000FF00) {
        return 2;
    } else if (prefix & 0x000000FF) {
        return 1;
    }
    return 0; // No valid prefix found
}

void processAndFindTokens(char* input) {
    char* token = strtok(input, " ");
    while (token != NULL) {
        Serial.print("Split word: ");
        Serial.println(token);

        const RadixNode* currentNode = &root;
        size_t position = 0;
        bool found = true;

        while (token[position] != '\0' && found) {
            found = false;

            for (int i = 0; i < sizeof(currentNode->children) / sizeof(currentNode->children[0]); i++) {
                if (currentNode->children[i].prefix == 0) {
                    break;
                }

                size_t prefix_len = calculatePrefixLen(currentNode->children[i].prefix);

                // Debugging output
                Serial.print("Checking prefix: 0x");
                Serial.print(currentNode->children[i].prefix, HEX);
                Serial.print(" with token part: ");
                for (size_t j = 0; j < prefix_len; j++) {
                    Serial.print(token[position + j]);
                }
                Serial.println();

                if (comparePrefix(&token[position], currentNode->children[i].prefix, prefix_len)) {
                    position += prefix_len;
                    currentNode = currentNode->children[i].node;
                    found = true;

                    // Output the matching prefix as a hex value
                    Serial.print("Matching Prefix (Hex): 0x");
                    Serial.println(currentNode->children[i].prefix, HEX);
                    break;
                }
            }
        }

        if (found && currentNode->tokenID != -1) {
            Serial.print("Node ID: ");
            Serial.println(currentNode->tokenID);

            Serial.print("Hex Encoding: 0x");
            Serial.println(currentNode->tokenID, HEX);
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
