#ifndef BPE_VOCABULARY_H
#define BPE_VOCABULARY_H

#include <Arduino.h>

// Declare the size of the vocabulary
extern const int numTokens;

// Declare the BPE vocabulary
extern const char* const bpeVocabulary[];

// Function declarations
void cleanInput(char* input);
void trimWhitespace(char* input);
int findBPETokenID(const char* token);
void storeTokenAs24Bits(uint8_t* outputTokens, int& outputSize, int tokenID);
void tokenizeBPE(const char* input, uint8_t* outputTokens, int& outputSize);

#endif // BPE_VOCABULARY_H
