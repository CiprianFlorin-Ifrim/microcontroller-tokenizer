#include <Arduino.h>

// Mapping letters to integers
int letterToInt(char letter) {
  if (letter >= 'a' && letter <= 'z') {
    return letter - 'a' + 1;
  }
  if (letter >= 'A' && letter <= 'Z') {
    return letter - 'A' + 1;
  }
  return 0; // Return 0 for any non-alphabetic character
}

// Dictionary of words stored as integer arrays in PROGMEM
const int hello[] PROGMEM = {8, 5, 12, 12, 15};
const int world[] PROGMEM = {23, 15, 18, 12, 4};

const int* const dictionary[] PROGMEM = {
  hello,
  world
};

const int dictionarySizes[] PROGMEM = {
  sizeof(hello) / sizeof(hello[0]),
  sizeof(world) / sizeof(world[0])
};

// Function to convert a string to an array of integers
void stringToIntArray(const char* str, int* arr, int* length) {
  *length = 0;
  while (*str != '\0' && *length < 32) {
    arr[(*length)++] = letterToInt(*str++);
  }
}

// Function to compare integer arrays
bool compareIntArrays(const int* arr1, const int* arr2, int length) {
  for (int i = 0; i < length; i++) {
    if (pgm_read_word(&arr1[i]) != arr2[i]) {
      return false;
    }
  }
  return true;
}

// Function to check if a word matches any in the dictionary
bool isWordInDictionary(const int* wordArray, int wordLength) {
  for (int i = 0; i < sizeof(dictionary) / sizeof(dictionary[0]); i++) {
    int storedWordLength = pgm_read_word(&dictionarySizes[i]);
    if (storedWordLength == wordLength) {
      if (compareIntArrays((int*)pgm_read_word(&dictionary[i]), wordArray, wordLength)) {
        return true;
      }
    }
  }
  return false;
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // Wait for serial port to connect.
  }
  Serial.println("Enter text to check against dictionary:");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readString();
    input.trim(); // Remove any leading/trailing whitespace

    int wordArray[32]; // Fixed-size array to hold the converted word
    int wordLength;

    stringToIntArray(input.c_str(), wordArray, &wordLength);

    if (isWordInDictionary(wordArray, wordLength)) {
      Serial.println("Word found in dictionary!");
    } else {
      Serial.println("Word not found in dictionary.");
    }
  }
}
