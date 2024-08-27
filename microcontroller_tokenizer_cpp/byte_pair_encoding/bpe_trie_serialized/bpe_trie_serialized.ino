#include "bpe_trie_vocabulary.cpp"

struct TrieNode {
    int32_t tokenID;
    int32_t children[128];  // Array for child nodes' indices
};

const TrieNode* root = &trieNodes[0];  // Root of the Trie

int searchTrie(const char* word) {
    const TrieNode* node = root;
    for (int i = 0; word[i] != '\0'; i++) {
        char c = word[i];
        if (node->children[(unsigned char)c] == -1) {
            return -1;  // Word not found
        }
        node = &trieNodes[node->children[(unsigned char)c]];
    }
    return node->tokenID;
}

void setup() {
    Serial.begin(115200);

    // Example search
    const char* word = "example";
    int tokenID = searchTrie(word);
    if (tokenID != -1) {
        Serial.print("Found token ID: ");
        Serial.println(tokenID);
    } else {
        Serial.println("Token not found.");
    }
}

void loop() {
    // Do nothing in the loop
}
