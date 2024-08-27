#include "bpe_vocabulary_trie.h"

// Example partial vocabulary
const char* const bpeVocabulary[] = {
    " ",
    "!",
    "#",
    "$",
    "%",
    "&",
    "\'",
    "(",
    ")",
   "{",
    "|",
    "}",
    "~",
    // Add the rest of the 260,072 tokens here...
};

const int numTokens = 260072;  // Total number of tokens in the vocabulary

// Definition of a TrieNode that will be used to build the Trie structure
class TrieNode {
public:
    std::unordered_map<char, TrieNode*> children;  // Children nodes mapped by character
    int tokenID;  // ID of the token if the node represents the end of a token

    TrieNode() : tokenID(-1) {}  // Constructor initializes tokenID to -1 (no token)
};

// Trie class that will be used to store the BPE vocabulary for efficient searching
class Trie {
public:
    TrieNode* root;  // Root node of the Trie

    Trie() {
        root = new TrieNode();  // Allocate root node, let the system decide where to place it
        if (root == nullptr) {
            Serial.println("Failed to allocate memory for Trie root");
        }
    }

    // Function to insert a token into the Trie
    void insert(const char* token, int tokenID) {
        TrieNode* node = root;
        for (int i = 0; token[i] != '\0'; i++) {
            char c = token[i];
            if (node->children.find(c) == node->children.end()) {
                TrieNode* newNode = new TrieNode();  // Allocate new node, let the system decide where to place it
                if (newNode == nullptr) {
                    Serial.println("Failed to allocate memory for Trie node");
                    return;  // Abort insertion if allocation fails
                }
                node->children[c] = newNode;
            }
            node = node->children[c];  // Move to the next node
            if (node == nullptr) {
                Serial.println("Node is null after allocation, unexpected error!");
                return;
            }
        }
        node->tokenID = tokenID;  // Set the token ID at the end of the token
    }

    // Function to search for the longest matching token in the Trie
    int search(const char* input, int& matchLength) {
        TrieNode* node = root;
        int tokenID = -1;  // Initialize tokenID to -1 (no match)
        matchLength = 0;  // Initialize matchLength to 0

        // Traverse the Trie to find the longest matching token
        for (int i = 0; input[i] != '\0'; i++) {
            char c = input[i];
            if (node->children.find(c) == node->children.end()) {
                break;  // If character not found, break out of the loop
            }
            node = node->children[c];  // Move to the next node
            if (node->tokenID != -1) {
                tokenID = node->tokenID;  // Update tokenID if a valid token is found
                matchLength = i + 1;  // Update matchLength to the length of the matched token
            }
        }
        return tokenID;  // Return the found token ID (or -1 if not found)
    }
};

// Global Trie object
Trie trie;

// Function to initialize the Trie with the vocabulary
void setupTrie() {
    for (int i = 200; i < 220; i++) {  // Start with 10 tokens for testing
        Serial.print("Inserting token ");
        Serial.println(i);

        trie.insert(bpeVocabulary[i], i);

        Serial.print("Free heap: ");
        Serial.println(ESP.getFreeHeap());
        Serial.print("Free PSRAM: ");
        Serial.println(ESP.getFreePsram());
    }
    Serial.println("Trie initialized");
}


// Function to convert a string to lowercase and remove non-ASCII characters
void cleanInput(char* input) {
    int writeIndex = 0;
    for (int readIndex = 0; input[readIndex] != '\0'; readIndex++) {
        char c = input[readIndex];
        if (c >= 32 && c <= 126) {  // ASCII printable characters (space to ~)
            input[writeIndex++] = tolower(c);
        }
    }
    input[writeIndex] = '\0';  // Null-terminate the cleaned string
}

// Function to trim leading and trailing whitespace from the input string
void trimWhitespace(char* input) {
    // Trim leading whitespace
    int startPos = 0;
    while (input[startPos] == ' ') {
        startPos++;
    }

    // Trim trailing whitespace
    int endPos = strlen(input) - 1;
    while (endPos >= 0 && input[endPos] == ' ') {
        endPos--;
    }

    // Shift the trimmed string to the beginning
    int length = endPos - startPos + 1;
    memmove(input, input + startPos, length);
    input[length] = '\0';  // Null-terminate the trimmed string
}

// Store token index as 3 bytes (24 bits)
void storeTokenAs24Bits(uint8_t* outputTokens, int& outputSize, int tokenID) {
    outputTokens[outputSize++] = (tokenID >> 16) & 0xFF;  // Most significant byte
    outputTokens[outputSize++] = (tokenID >> 8) & 0xFF;   // Middle byte
    outputTokens[outputSize++] = tokenID & 0xFF;          // Least significant byte
}

// Tokenize a string using the Trie and store as binary
void tokenizeBPE(const char* input, uint8_t* outputTokens, int& outputSize) {
    int startPos = 0;
    outputSize = 0;

    // Tokenize the input by searching for the longest matching token in the Trie
    while (input[startPos] != '\0') {
        int matchLength = 0;
        int tokenID = trie.search(input + startPos, matchLength);  // Search in Trie

        if (tokenID != -1) {
            storeTokenAs24Bits(outputTokens, outputSize, tokenID);  // Store as 24-bit value
            startPos += matchLength;  // Move start position by the length of the matched token
        } else {
            // If no matching token is found, move to the next character
            startPos++;
        }
    }
}
