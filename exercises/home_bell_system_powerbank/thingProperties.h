#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

// WiFi Credentials
const char SSID[]     = "ZTE_2.4G_uQdX4Y"; 
const char PASS[]     = "U99EH5E5";    

void onBuzzerSwitchChange();
void onLedChange();

bool buzzer_switch;
bool led;

void initProperties(){
  ArduinoCloud.addProperty(buzzer_switch, READWRITE, ON_CHANGE, onBuzzerSwitchChange);
  ArduinoCloud.addProperty(led, READWRITE, ON_CHANGE, onLedChange);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
