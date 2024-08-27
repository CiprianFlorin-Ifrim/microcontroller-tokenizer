#include <Arduino.h>
#include <stdint.h>
#include <stddef.h>
#include "bpe-vocab_radix-tree.h"

#define MAX_CHILDREN 46
#define SPACE_ID 22
#define BUFFER_SIZE 512

// Define the RadixNode structure
typedef struct RadixNode {
    int32_t tokenID;
    const char *prefix;
    struct RadixNode *children[MAX_CHILDREN];
} RadixNode;

// Declare the root node globally
RadixNode *root = nullptr;

// Function to build the Radix Tree from the hex data
RadixNode* buildRadixTree(const uint8_t *data, size_t &offset, size_t dataSize) {
    if (offset + 8 > dataSize) return nullptr;
    
    RadixNode *node = (RadixNode*)malloc(sizeof(RadixNode));
    if (!node) return nullptr;
    
    memcpy(&node->tokenID, &data[offset], sizeof(int32_t));
    int32_t numChildren;
    memcpy(&numChildren, &data[offset + 4], sizeof(int32_t));
    offset += 8;

    memset(node->children, 0, sizeof(node->children));

    for (int i = 0; i < numChildren; i++) {
        int32_t prefixLen;
        memcpy(&prefixLen, &data[offset], sizeof(int32_t));
        offset += 4;

        char *prefix = (char*)malloc(prefixLen + 1);
        if (!prefix) return nullptr;

        memcpy(prefix, &data[offset], prefixLen);
        prefix[prefixLen] = '\0';
        offset += prefixLen;

        node->children[i] = buildRadixTree(data, offset, dataSize);
        node->children[i]->prefix = prefix;
    }
    
    return node;
}

// Traverse the Radix Tree
int32_t traverseRadixTree(const char *phrase, RadixNode *node) {
    while (*phrase) {
        bool found = false;
        for (int i = 0; i < MAX_CHILDREN && node->children[i]; i++) {
            size_t len = strlen(node->children[i]->prefix);
            if (strncmp(phrase, node->children[i]->prefix, len) == 0) {
                phrase += len;
                node = node->children[i];
                found = true;
                break;
            }
        }
        if (!found) return -1;
    }
    return node->tokenID;
}

// Clean input: convert to lowercase and remove non-ASCII characters
void cleanInput(char *phrase) {
    char *dst = phrase;
    while (*phrase) {
        if (*phrase >= 0 && *phrase <= 127) *dst++ = tolower(*phrase);
        phrase++;
    }
    *dst = '\0';
}

// Append an integer as a string to a character array
void appendIntToCharArray(char* buffer, int32_t value) {
    char temp[12];  // Large enough to hold any 32-bit integer
    itoa(value, temp, 10);
    strcat(buffer, temp);
    strcat(buffer, " ");
}

// Append a hexadecimal value as a string to a character array
void appendHexToCharArray(char* buffer, int32_t value) {
    char temp[9];  // Enough for a 32-bit hex value
    sprintf(temp, "%08x", value);
    strcat(buffer, temp);
    strcat(buffer, " ");
}

// Process each word and split into tokens
void processWord(const char *word, char* resultIDs, char* resultHex) {
    char token[BUFFER_SIZE] = "";
    while (*word) {
        if (isalnum(*word)) {
            strncat(token, word, 1);
        } else {
            if (strlen(token) > 0) {
                int32_t nodeID = traverseRadixTree(token, root);
                if (nodeID != -1) {
                    appendIntToCharArray(resultIDs, nodeID);
                    appendHexToCharArray(resultHex, nodeID);
                }
                token[0] = '\0';  // Reset token
            }
            char symbolToken[2] = {*word, '\0'};
            int32_t nodeID = traverseRadixTree(symbolToken, root);
            if (nodeID != -1) {
                appendIntToCharArray(resultIDs, nodeID);
                appendHexToCharArray(resultHex, nodeID);
            }
        }
        word++;
    }
    if (strlen(token) > 0) {
        int32_t nodeID = traverseRadixTree(token, root);
        if (nodeID != -1) {
            appendIntToCharArray(resultIDs, nodeID);
            appendHexToCharArray(resultHex, nodeID);
        }
    }
}

void setup() {
    Serial.begin(9600);
    while (!Serial) {}

    size_t offset = 0;
    root = buildRadixTree(radix_tree_hex, offset, radix_tree_hex_size);
    Serial.println(root ? "Radix Tree built." : "Failed to build Radix Tree.");
    Serial.println("Enter a phrase:");
}

void loop() {
    if (Serial.available() > 0) {
        char inputPhrase[BUFFER_SIZE];
        size_t len = Serial.readBytesUntil('\n', inputPhrase, sizeof(inputPhrase) - 1);
        inputPhrase[len] = '\0';

        cleanInput(inputPhrase);

        char resultIDs[BUFFER_SIZE] = "";
        char resultHex[BUFFER_SIZE] = "";
        char *word = strtok(inputPhrase, " ");
        while (word) {
            processWord(word, resultIDs, resultHex);
            word = strtok(NULL, " ");
            if (word) {
                appendIntToCharArray(resultIDs, SPACE_ID);
                appendHexToCharArray(resultHex, SPACE_ID);
            }
        }

        Serial.print("Node IDs: "); Serial.println(resultIDs);
        Serial.print("Hex Encodings: "); Serial.println(resultHex);
        Serial.println("Enter another phrase:");
    }
}
