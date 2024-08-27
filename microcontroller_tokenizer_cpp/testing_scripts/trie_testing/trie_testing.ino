#include <cstdlib>  // For random number generation
#include <ctime>    // For seeding random generator

void generateRandomToken(char* token, int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < length; i++) {
        token[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    token[length] = '\0';  // Null-terminate the string
}

// Function to initialize the Trie with random tokens
void setupTrie() {
    const int tokenLength = 8;  // Length of each random token
    char token[tokenLength + 1];  // +1 for null terminator

    srand(time(NULL));  // Seed the random number generator

    for (int i = 0; i < 100; i++) {  // Adjust the number of tokens as needed
        generateRandomToken(token, tokenLength);

        Serial.print("Inserting random token ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(token);

        trie.insert(token, i);

        Serial.print("Free heap: ");
        Serial.println(ESP.getFreeHeap());
        Serial.print("Free PSRAM: ");
        Serial.println(ESP.getFreePsram());

        heap_caps_check_integrity_all(true);  // Check heap integrity

        if (ESP.getFreeHeap() < 10000) {  // Early stop if heap is dangerously low
            Serial.println("Stopping due to low heap memory");
            break;
        }
    }
    Serial.println("Random Trie initialized");
}

void setup() {
    Serial.begin(115200);
    while (!Serial) {
        ; // Wait for the serial port to connect
    }

    Serial.println("Checking memory availability...");

    // Print available heap and PSRAM
    Serial.print("Free heap: ");
    Serial.println(ESP.getFreeHeap());
    Serial.print("Free PSRAM: ");
    Serial.println(ESP.getFreePsram());

    // Call setupTrie() and monitor memory usage before and after
    Serial.println("Initializing Trie with random tokens...");
    setupTrie();

    // Check memory again after Trie initialization
    Serial.print("Free heap after Trie initialization: ");
    Serial.println(ESP.getFreeHeap());
    Serial.print("Free PSRAM after Trie initialization: ");
    Serial.println(ESP.getFreePsram());

    Serial.println("Setup complete");
}

void loop() {
    // Do nothing in the loop
}
