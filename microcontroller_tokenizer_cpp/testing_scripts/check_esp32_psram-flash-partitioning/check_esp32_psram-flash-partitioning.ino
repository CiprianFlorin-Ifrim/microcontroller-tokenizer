#include <Arduino.h>

void setup() {
  Serial.begin(115200);

  // Check if PSRAM is available
  if (psramFound()) {
    Serial.println("PSRAM found and available");

    // Try to allocate a buffer for testing
    size_t testSize = 7.87 * 1024 * 1024; // Almost 8 MB (cannot go over 7.87)
    uint8_t* buffer = (uint8_t*)ps_malloc(testSize); // Allocate 8MB

    if (buffer) {
      Serial.print("PSRAM allocated successfully: ");
      Serial.println(testSize);
      free(buffer);
    } else {
      Serial.println("PSRAM allocation failed");
    }
  } else {
    Serial.println("PSRAM not found");
  }

  // Print free heap memory
  Serial.print("Free Heap Memory: ");
  Serial.print(ESP.getFreeHeap());
  Serial.println(" bytes");
}

void loop() {
  // Do nothing here
}
