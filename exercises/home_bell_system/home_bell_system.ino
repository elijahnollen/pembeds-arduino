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
  delay(1500); 

  matrix.begin();
  pinMode(LED_PIN, OUTPUT);           
  pinMode(BUZZER_PIN, OUTPUT); 

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
}

void loop() {
  ArduinoCloud.update();
}

// Reusable function to play a note and show a frame
void ring(uint8_t frame[8][12], int note, int duration) {
  matrix.renderBitmap(frame, 8, 12);
  tone(BUZZER_PIN, note);
  delay(duration);
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
  if (buzzer_switch == true) {
    Serial.println("Ding-Dong Sequence Started!");

    for (int i = 0; i < 2; i++) {
      ring(bell_right, 2637, 600); // Ding
      ring(bell_left, 2093, 800);  // Dong
      
      if (i == 0) {
        noTone(BUZZER_PIN);
        delay(250); 
      }
    }

    tone(BUZZER_PIN, 1975); 
    delay(400);
    
    noTone(BUZZER_PIN);
    matrix.renderBitmap(bell_frame, 8, 12);
    delay(500);
    matrix.clear(); 

    buzzer_switch = false;
    ArduinoCloud.update();
    
  } else {
    noTone(BUZZER_PIN); 
    matrix.clear();
  }
}
