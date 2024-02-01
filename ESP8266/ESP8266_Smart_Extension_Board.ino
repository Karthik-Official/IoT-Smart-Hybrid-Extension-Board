#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <ESP8266WiFi.h>

#define Toggle_Trigger_Pin 1 // TX pin will trigger the wifi configuration portal when set to LOW
#define Wifi_Led_Pin 3 // RX Wifi Connection Indicator
int timeout = 120; // wifi config trigger timeout

// Set web server port number to 80
WiFiServer server(80);
// Variable to store the HTTP request
String header;


void toggle_wificonnect() {
 
    // is configuration portal requested?
    if ( digitalRead(Toggle_Trigger_Pin) == LOW) {
        digitalWrite(Wifi_Led_Pin, HIGH);
        
        WiFiManager wm;    
        
        Serial.println("Wifi Config Mode Activated");
        
        //reset settings - for testing
        //wm.resetSettings();
    
        // set configportal timeout
        wm.setConfigPortalTimeout(timeout);

        if (!wm.startConfigPortal("Smart-ExtBoard-AP")) {
        Serial.println("failed to connect and hit timeout");
        digitalWrite(Wifi_Led_Pin, LOW);
        //reset and try again, or maybe put it to deep sleep
        ESP.restart();
        delay(3000);
        }

        //if you get here you have connected to the WiFi
        Serial.println("connected to the wifi)");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
        digitalWrite(Wifi_Led_Pin, LOW);
    }
}

void webserver() {
    Serial.print("Hola Webserver");
}

void setup() {

    Serial.begin(115200); 
    WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP  
    pinMode(Toggle_Trigger_Pin, INPUT_PULLUP);
    pinMode(Wifi_Led_Pin, OUTPUT);

}

void loop() {

    toggle_wificonnect();

    if(WiFi.status() == WL_CONNECTED) {
        webserver();
    }

    
}
