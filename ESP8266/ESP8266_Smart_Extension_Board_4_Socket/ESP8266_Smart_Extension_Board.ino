#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <ESP8266WiFi.h>

#define TOGGLE_TRIGGER_PIN 1 // TX - pin will trigger the wifi configuration portal when set to LOW
#define WIFI_LED_PIN 3 // RX - Wifi Connection Indicator

#define PIN_RELAY_1 5  //D1
#define PIN_RELAY_2 4  //D2
#define PIN_RELAY_3 14 //D5
#define PIN_RELAY_4 12 //D6

#define TOUCH_SENSOR_1 10  //SD3
#define TOUCH_SENSOR_2 0   //D3 
#define TOUCH_SENSOR_3 13  //D7
#define TOUCH_SENSOR_4 9   //RX

int relayState1 = 0; // toggle state for relay 1 
int relayState2 = 0; // toggle state for relay 2
int relayState3 = 0; // toggle state for relay 3
int relayState4 = 0; // toggle state for relay 4

int timeout = 120; // wifi config trigger timeout

WiFiServer server(80); // Set web server port number to 80

String header; // Variable to store the HTTP request

void wifiConnect() {
 
    // wifi configuration portal request button
    if ( digitalRead(TOGGLE_TRIGGER_PIN) == LOW) {

        Serial.println("Wifi Config Mode Activated");
        
        digitalWrite(WIFI_LED_PIN, HIGH); // Wifi Connection Mode Indicator On         

        WiFiManager wm;    
        // wm.resetSettings(); // reset wifi settings - uncomment for testing
        wm.setConfigPortalTimeout(timeout); // set configportal timeout

        // uncomment below part-1 and part-2 for custom static IP address. CAUTION: Static IP may conflict IP DHCP IP address, 
        // Only use if you know how to configure your router to exclude the static IP address from the DHCP scope and know your Gateway and Subnet mask.
        // // Added parameters for static IP configuration part-1

        // WiFiManagerParameter custom_ip("ip", "Static IP", "192.168.1.100", 15); //Default IP address
        // WiFiManagerParameter custom_gateway("gateway", "Gateway", "192.168.1.1", 15); //Default Gateway
        // WiFiManagerParameter custom_subnet("subnet", "Subnet", "255.255.255.0", 15); //Default Subnet mask
        // wifiManager.addParameter(&custom_ip);
        // wifiManager.addParameter(&custom_gateway);
        // wifiManager.addParameter(&custom_subnet);
        
        // creating wifi config portal
        if (!wm.startConfigPortal("Smart-ExtBoard-AP")) {
            Serial.println("failed to connect and hit timeout");
            digitalWrite(WIFI_LED_PIN, LOW); // Wifi Connection Mode Indicator Off by Reset
            ESP.restart(); //reset and try again
            delay(3000);
        }

        // // Apply static IP configuration part-2

        // IPAddress staticIP, gateway, subnet;
        // staticIP.fromString(custom_ip.getValue());
        // gateway.fromString(custom_gateway.getValue());
        // subnet.fromString(custom_subnet.getValue());
        // WiFi.config(staticIP, gateway, subnet); 

        digitalWrite(WIFI_LED_PIN, LOW); // Wifi Connection Mode Indicator Off by Connection

        //only prints when ESP connected to the WiFi
        Serial.println("connected to the wifi)");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
    }
}

void relayOnOff(int relay) {

    switch(relay){
      case 1: 
          if(relayState1 == 1){
            digitalWrite(PIN_RELAY_1, LOW); // turn on relay 1
            relayState1 = 0;
            Serial.println("Switch 1 ON");
          }
          else{
            digitalWrite(PIN_RELAY_1, HIGH); // turn off relay 1
            relayState1 = 1;
            Serial.println("Switch 1 OFF");
          }
          delay(100);
      break;
      case 2: 
          if(relayState2 == 1){
          digitalWrite(PIN_RELAY_2, LOW); // turn on relay 2
          relayState2 = 0;
          Serial.println("Switch 2 ON");
          }
          else{
          digitalWrite(PIN_RELAY_2, HIGH); // turn off relay 2
          relayState2 = 1;
          Serial.println("Switch 2 OFF");
          }
          delay(100);
      break;
      case 3: 
          if(relayState3 == 1){
          digitalWrite(PIN_RELAY_3, LOW); // turn on relay 3
          relayState3 = 0;
          Serial.println("Switch 3 ON");
          }
          else{
          digitalWrite(PIN_RELAY_3, HIGH); // turn off relay 3
          relayState3 = 1;
          Serial.println("Switch 3 OFF");
          }
          delay(100);
      break;
      case 4: 
          if(relayState4 == 1){
          digitalWrite(PIN_RELAY_4, LOW); // turn on relay 4
          relayState4 = 0;
          Serial.println("Switch 4 ON");
          }
          else{
          digitalWrite(PIN_RELAY_4, HIGH); // turn off relay 4
          relayState4 = 1;
          Serial.println("Switch 4 OFF");
          }
          delay(100);
      break;
      default : break;      
      }  
}

void touchControl() {

    //Manual Touch Switch Control
    if (digitalRead(TOUCH_SENSOR_1) == LOW){
      delay(200);
      relayOnOff(1);      
    }
    else if (digitalRead(TOUCH_SENSOR_2) == LOW){
      delay(200);
      relayOnOff(2);
    }
    else if (digitalRead(TOUCH_SENSOR_3) == LOW){
      delay(200);
      relayOnOff(3);
    }
    else if (digitalRead(TOUCH_SENSOR_4) == LOW){
      delay(200);
      relayOnOff(4);
    }
}

void webserverControl() { 
    Serial.print("Hola Webserver");
}

void setup() {

    Serial.begin(115200); 
    WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP  
    // Wifi Modules
    pinMode(TOGGLE_TRIGGER_PIN, INPUT_PULLUP);
    pinMode(WIFI_LED_PIN, OUTPUT);
    // Relay Modules
    pinMode(PIN_RELAY_1, OUTPUT);
    pinMode(PIN_RELAY_2, OUTPUT);
    pinMode(PIN_RELAY_3, OUTPUT);
    pinMode(PIN_RELAY_4, OUTPUT);
    // Relay Modules intializing with ACTIVE HIGH to make relay off state
    digitalWrite(PIN_RELAY_1, HIGH);
    digitalWrite(PIN_RELAY_2, HIGH);
    digitalWrite(PIN_RELAY_3, HIGH);
    digitalWrite(PIN_RELAY_4, HIGH);
    // Touch Sensor Modules
    pinMode(TOUCH_SENSOR_1, INPUT_PULLUP);
    pinMode(TOUCH_SENSOR_2, INPUT_PULLUP);
    pinMode(TOUCH_SENSOR_3, INPUT_PULLUP);
    pinMode(TOUCH_SENSOR_4, INPUT_PULLUP);
}

void loop() {

    wifiConnect(); 

    touchControl();
    if(WiFi.status() == WL_CONNECTED) {
        webserverControl();
    }
    
}
