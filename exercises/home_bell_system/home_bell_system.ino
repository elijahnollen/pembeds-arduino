#include "thingProperties.h"
#include "Arduino_LED_Matrix.h"

const int BUZZER_PIN = 8; 

ArduinoLEDMatrix matrix;

// ORIGINAL CENTERED BELL
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

// DING - SHIFTED RIGHT
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

// DONG - SHIFTED LEFT
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

  pinMode(13, OUTPUT);          
  pinMode(BUZZER_PIN, OUTPUT); 

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
}

void onLedChange()  {
  if (led == true) {
    digitalWrite(13, HIGH);
    matrix.renderBitmap(bell_frame, 8, 12); 
  } else {
    digitalWrite(13, LOW);
    matrix.clear(); 
  }
}

void onBuzzerSwitchChange()  {
  if (buzzer_switch == true) {
    Serial.println("Ding Dong!");
    
    matrix.renderBitmap(bell_right, 8, 12);
    tone(BUZZER_PIN, 2637); 
    delay(300);            

    matrix.renderBitmap(bell_left, 8, 12);
    tone(BUZZER_PIN, 2093); 
    delay(600);             

    noTone(BUZZER_PIN);
    
    matrix.renderBitmap(bell_frame, 8, 12);
    delay(400);
    matrix.clear(); 
    
    buzzer_switch = false;
    ArduinoCloud.update();
    
  } else {
    noTone(BUZZER_PIN); 
    matrix.clear();
  }
}
