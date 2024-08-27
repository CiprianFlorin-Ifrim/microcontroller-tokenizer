#include <Arduino.h>

// Delimiters for splitting words
const char delimiters[] = " ,.!?;:\n";

// Most common English words stored in RAM
const char* dictionary[] = {
  "the", "and", "he", "she", "it", "you", "we", "they", "run", "walk",
  "have", "be", "do", "say", "make", "go", "know", "get", "think",
  "see", "come", "could", "would", "should", "can", "will", "not"
};

// Common subwords (prefixes/suffixes) stored in RAM
const char* subwords[] = {
  "un", "ing", "ed", "ly", "er", "re", "pre", "tion", "able", "ness", "ment"
};

// Function to check if a word is in the dictionaryTok
bool isWordInDictionary(const char* word) {
  for (int i = 0; i < sizeof(dictionary) / sizeof(dictionary[0]); i++) {
    if (strcmp(word, dictionary[i]) == 0) {
      return true;
    }
  }
  return false;
}

// Function to check if a subword (prefix/suffix) is in the dictionary
bool isSubwordInDictionary(const char* subword) {
  for (int i = 0; i < sizeof(subwords) / sizeof(subwords[0]); i++) {
    if (strcmp(subword, subwords[i]) == 0) {
      return true;
    }
  }
  return false;
}

// Tokenization function that also handles subwords
void tokenizeWithSubwords(const char* input) {
  char tokenBuffer[32]; // Fixed-size buffer for tokens
  int tokenIndex = 0;

  while (*input != '\0') {
    // Check if the current character is a delimiter
    if (strchr(delimiters, *input) != NULL) {
      if (tokenIndex > 0) {
        tokenBuffer[tokenIndex] = '\0';

        // Check for subwords and split accordingly
        for (int i = tokenIndex - 1; i > 0; i--) {
          if (isSubwordInDictionary(tokenBuffer + i)) {
            char subwordBuffer[32];
            strncpy(subwordBuffer, tokenBuffer + i, sizeof(subwordBuffer) - 1);
            subwordBuffer[sizeof(subwordBuffer) - 1] = '\0';
            tokenBuffer[i] = '\0';
            Serial.print("Root: ");
            Serial.println(tokenBuffer);
            Serial.print("Subword: ");
            Serial.println(subwordBuffer);
            break;
          }
        }

        if (isWordInDictionary(tokenBuffer)) {
          Serial.print("Word: ");
        } else {
          Serial.print("Unknown: ");
        }
        Serial.println(tokenBuffer);

        tokenIndex = 0;
      }
    } else {
      if (tokenIndex < sizeof(tokenBuffer) - 1) {
        tokenBuffer[tokenIndex++] = *input;
      }
    }
    input++;
  }

  // Handle the last token if there's any left
  if (tokenIndex > 0) {
    tokenBuffer[tokenIndex] = '\0';

    if (isWordInDictionary(tokenBuffer)) {
      Serial.print("Word: ");
    } else {
      Serial.print("Unknown: ");
    }
    Serial.println(tokenBuffer);
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // Wait for serial port to connect.
  }
  Serial.println("Enter text to tokenize:");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readString();
    tokenizeWithSubwords(input.c_str());
  }
}
