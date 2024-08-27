#ifndef HUFFMAN_CODES_H
#define HUFFMAN_CODES_H

#include <cstddef> // For size_t

// Define the HuffmanCode structure
struct HuffmanCode {
    const char* token;
    const char* code;
};

// Declare the HuffmanTable array
extern const HuffmanCode huffmanTable[];
extern const size_t huffmanTableSize;

// Define the function for checking symbols
bool isSymbol(char c);

#endif // HUFFMAN_CODES_H
