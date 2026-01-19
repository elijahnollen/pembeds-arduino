#include "thingProperties.h"
#include "Arduino_LED_Matrix.h"

const int BUZZER_PIN = 8; 
const int LED_PIN = 13;

ArduinoLEDMatrix matrix;

// --- Corrected Matrix Bitmaps (8 rows, 12 columns) ---
uint8_t bell_frame[8][12] = {
  { 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

uint8_t bell_right[8][12] = {
  { 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0 },
  { 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
  { 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

uint8_t bell_left[8][12] = {
  { 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
  { 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

void setup() {
  Serial.begin(9600);
  delay(2000); 

  matrix.begin();
  pinMode(LED_PIN, OUTPUT);           
  pinMode(BUZZER_PIN, OUTPUT); 

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
}

void loop() {
  ArduinoCloud.update();
}

// Fixed ring function to ensure the matrix updates properly
void ring(uint8_t frame[8][12], int note, int duration) {
  matrix.renderBitmap(frame, 8, 12);
  tone(BUZZER_PIN, note);
  delay(duration);
  noTone(BUZZER_PIN); // Stop sound before next note
}

void onLedChange() {
  if (led) {
    digitalWrite(LED_PIN, HIGH);
    matrix.renderBitmap(bell_frame, 8, 12);
  } else {
    digitalWrite(LED_PIN, LOW);
    matrix.clear();
  }
}

void onBuzzerSwitchChange() {
  if (buzzer_switch) {
    // Animation Loop
    for (int i = 0; i < 2; i++) {
      ring(bell_right, 2637, 400);
      delay(50);
      ring(bell_left, 2093, 400); 
      delay(50);
    }

    // Return to center
    matrix.renderBitmap(bell_frame, 8, 12);
    tone(BUZZER_PIN, 1975, 400);
    delay(500);
    matrix.clear(); 

    // Reset the cloud switch so you can trigger it again
    buzzer_switch = false;
    ArduinoCloud.update();
  }
}
