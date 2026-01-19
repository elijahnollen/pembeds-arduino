#include "thingProperties.h"
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

const int redPin = 9;
const int greenPin = 6;
const int yellowPin = 5;

void setup() {
  Serial.begin(9600);
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  dht.begin();
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
}

void loop() {
  ArduinoCloud.update();
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  temperature = t;
  humidity = h;

  // LED Logic
  if (led_override) {
    setColor(255, 255, 255); 
  } 
  else {
    // Based ONLY on Temperature
    if (t > 30) {
      setColor(255, 0, 0);   // RED: Hot
    } 
    else if (t < 20) {
      setColor(0, 0, 255);   // YELLOW: Cold
    } 
    else {
      setColor(0, 255, 0);   // GREEN: Comfortable
    }
  }
  
  delay(2000); 
}

// Helper function to handle the pins
void setColor(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(yellowPin, b);
}

void onLedOverrideChange()  {

}
