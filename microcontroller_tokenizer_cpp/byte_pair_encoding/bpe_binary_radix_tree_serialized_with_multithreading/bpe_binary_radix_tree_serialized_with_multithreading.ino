#include <Arduino.h>
#include <stdint.h>
#include <stddef.h>
#include "bpe-vocab_radix-tree.h"

#define MAX_CHILDREN 46
#define BUFFER_SIZE 512

typedef struct RadixNode {
    int32_t tokenID;
    const char *prefix;
    struct RadixNode *children[MAX_CHILDREN];
} RadixNode;

RadixNode *root = nullptr;
SemaphoreHandle_t xMutex;
TaskHandle_t task1Handle = NULL, task2Handle = NULL;
char resultIDs[BUFFER_SIZE] = "", resultHex[BUFFER_SIZE] = "", cleanedPhrase[BUFFER_SIZE] = "";

void cleanInput(const char *input, char *output) {
    // Skip leading whitespace
    while (*input == ' ') {
        input++;
    }

    const char *end = input + strlen(input) - 1;

    // Trim trailing whitespace
    while (end > input && *end == ' ') {
        end--;
    }

    while (input <= end) {
        if (*input >= 0 && *input <= 127) {
            *output++ = tolower(*input);
        }
        input++;
    }
    *output = '\0';
}


void tokenize(const char *phrase, char *tokens[], int &tokenCount) {
    const char *currentToken = nullptr;
    tokenCount = 0;
    while (*phrase) {
        if (isalnum(*phrase)) {
            if (!currentToken) currentToken = phrase;
        } else {
            if (currentToken) {
                tokens[tokenCount++] = strndup(currentToken, phrase - currentToken);
                currentToken = nullptr;
            }
            if (*phrase == ' ') {
                tokens[tokenCount++] = strdup("|");  // Replace space with pipe in tokens
            } else {
                tokens[tokenCount++] = strndup(phrase, 1);
            }
        }
        phrase++;
    }
    if (currentToken) tokens[tokenCount++] = strdup(currentToken);
    tokens[tokenCount] = nullptr;
}

RadixNode* buildRadixTree(const uint8_t *data, size_t &offset, size_t dataSize) {
    RadixNode *node = (RadixNode*)malloc(sizeof(RadixNode));
    if (!node) return nullptr;
    memcpy(&node->tokenID, &data[offset], 4);
    int32_t numChildren;
    memcpy(&numChildren, &data[offset + 4], 4);
    offset += 8;
    memset(node->children, 0, sizeof(node->children));

    for (int i = 0; i < numChildren; i++) {
        int32_t prefixLen;
        memcpy(&prefixLen, &data[offset], 4);
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

void appendIntToCharArray(char* buffer, int32_t value, bool isHex = false) {
    char temp[12];
    sprintf(temp, isHex ? "%08x " : "%d ", value);
    strcat(buffer, temp);
}

void processTokens(char** tokens, int start, int end) {
    for (int i = start; i < end; i++) {
        int32_t nodeID = traverseRadixTree(tokens[i], root);
        if (nodeID != -1) {
            xSemaphoreTake(xMutex, portMAX_DELAY);
            appendIntToCharArray(resultIDs, nodeID);
            appendIntToCharArray(resultHex, nodeID, true);
            xSemaphoreGive(xMutex);
        }
    }
}

void TaskTokenProcessor(void *pvParameters) {
    char** tokens = (char**)pvParameters;
    int numTokens = 0;
    while (tokens[numTokens] != nullptr) numTokens++;

    int midPoint = numTokens / 2;
    processTokens(tokens, xPortGetCoreID() == 0 ? 0 : midPoint, xPortGetCoreID() == 0 ? midPoint : numTokens);

    vTaskDelete(NULL);
}

void setup() {
    Serial.begin(115200);
    while (!Serial) {}

    size_t offset = 0;
    root = buildRadixTree(radix_tree_hex, offset, radix_tree_hex_size);
    Serial.println(root ? "Radix Tree built." : "Failed to build Radix Tree.");
    Serial.println("Enter a phrase:");

    xMutex = xSemaphoreCreateMutex();
}

void loop() {
    if (Serial.available() > 0) {
        char inputPhrase[BUFFER_SIZE];
        size_t len = Serial.readBytesUntil('\n', inputPhrase, sizeof(inputPhrase) - 1);
        inputPhrase[len] = '\0';

        cleanInput(inputPhrase, cleanedPhrase);

        char* tokens[BUFFER_SIZE / 2] = {0};
        int tokenCount = 0;
        tokenize(cleanedPhrase, tokens, tokenCount);

        xTaskCreatePinnedToCore(TaskTokenProcessor, "TaskTokenProcessor1", 2048, (void*)tokens, 1, &task1Handle, 0);
        xTaskCreatePinnedToCore(TaskTokenProcessor, "TaskTokenProcessor2", 2048, (void*)tokens, 1, &task2Handle, 1);

        while (eTaskGetState(task1Handle) != eDeleted || eTaskGetState(task2Handle) != eDeleted) delay(100);

        Serial.printf("Original Input: %s\nCleaned Input: %s\nNode IDs: %s\nHex Encodings: %s\nEnter another phrase:\n", inputPhrase, cleanedPhrase, resultIDs, resultHex);

        resultIDs[0] = resultHex[0] = '\0';
        for (int i = 0; i < tokenCount; i++) free(tokens[i]);
    }
}
