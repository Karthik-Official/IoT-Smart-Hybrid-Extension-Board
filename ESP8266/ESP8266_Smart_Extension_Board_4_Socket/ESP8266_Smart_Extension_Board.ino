#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <ESP8266WiFi.h>

#define Toggle_Trigger_Pin 1 // TX - pin will trigger the wifi configuration portal when set to LOW
#define Wifi_Led_Pin 3 // RX - Wifi Connection Indicator

#define RelayPin1 5  //D1
#define RelayPin2 4  //D2
#define RelayPin3 14 //D5
#define RelayPin4 12 //D6

#define SwitchPin1 10  //SD3
#define SwitchPin2 0   //D3 
#define SwitchPin3 13  //D7
#define SwitchPin4 3   //RX

int timeout = 120; // wifi config trigger timeout

WiFiServer server(80); // Set web server port number to 80

String header; // Variable to store the HTTP request

void wifiConnect() {
 
    // wifi configuration portal request button
    if ( digitalRead(Toggle_Trigger_Pin) == LOW) {

        Serial.println("Wifi Config Mode Activated");
        
        digitalWrite(Wifi_Led_Pin, HIGH); // Wifi Connection Mode Indicator On         

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
            digitalWrite(Wifi_Led_Pin, LOW); // Wifi Connection Mode Indicator Off by Reset
            ESP.restart(); //reset and try again
            delay(3000);
        }

        // // Apply static IP configuration part-2

        // IPAddress staticIP, gateway, subnet;
        // staticIP.fromString(custom_ip.getValue());
        // gateway.fromString(custom_gateway.getValue());
        // subnet.fromString(custom_subnet.getValue());
        // WiFi.config(staticIP, gateway, subnet); 

        digitalWrite(Wifi_Led_Pin, LOW); // Wifi Connection Mode Indicator Off by Connection

        //only prints when ESP connected to the WiFi
        Serial.println("connected to the wifi)");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
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

    wifiConnect(); 

    touchControl();

    if(WiFi.status() == WL_CONNECTED) {
        webserver();
    }
    
}
