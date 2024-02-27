#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <ESP8266WiFi.h>

#define PIN_RELAY_1 5  //D1
#define PIN_RELAY_2 4  //D2
#define PIN_RELAY_3 14 //D5
#define PIN_RELAY_4 12 //D6

#define TOUCH_SENSOR_1 10 //SD3
#define TOUCH_SENSOR_2 16 //D0
#define TOUCH_SENSOR_3 13 //D7
#define TOUCH_SENSOR_4 15 //D8  

#define WIFI_LED_PIN 0 // D3 - Wifi Connection Indicator
#define TOGGLE_TRIGGER_PIN 3 // RX - pin will trigger the wifi configuration portal when set to LOW

int timeout = 60; // wifi config trigger timeout
WiFiServer server(80); // Set web server port number to 80
String header; // Variable to store the HTTP request
unsigned long currentTime = millis(); // Current time
unsigned long previousTime = 0; // Previous time
const long timeoutTime = 2000; // Define timeout time in milliseconds (example: 2000ms = 2s)
bool webServerRunning = false;  // Variable to track whether the server is running

int relayState1 = 1; // toggle state for relay 1, 0 means On, 1 means Off.
int relayState2 = 1; // toggle state for relay 2, 0 means On, 1 means Off.
int relayState3 = 1; // toggle state for relay 3, 0 means On, 1 means Off.
int relayState4 = 1; // toggle state for relay 4, 0 means On, 1 means Off.

WiFiManager wm; 

void wifiConnect() {
    
    // wifi configuration portal request button
    if ( digitalRead(TOGGLE_TRIGGER_PIN) == HIGH ) {

        stopWebServer(); // stops a running web server

        WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP  

        Serial.println("Wifi Config Mode Activated");
        
        digitalWrite(WIFI_LED_PIN, HIGH); // Wifi Connection Mode Indicator On         

        // wm.resetSettinxgs(); // reset wifi settings - uncomment for testing
        wm.setConfigPortalTimeout(timeout); // set configportal timeout

        // // uncomment below part-1 and part-2 for custom static IP address. CAUTION: Static IP may conflict IP DHCP IP address, 
        // // Only use if you know how to configure your router to exclude the static IP address from the DHCP scope and know your Gateway and Subnet mask.
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
            delay(1000);
            digitalWrite(WIFI_LED_PIN, LOW); // Wifi Connection Mode Indicator Off by Reset
            ESP.reset(); //reset and try again`
            delay(3000);
        }
        
        //only prints when ESP connected to the WiFi
        Serial.println("connected to the wifi)");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
        digitalWrite(WIFI_LED_PIN, LOW); // Wifi Connection Mode Indicator Off by Connection

        // // Apply static IP configuration part-2
        // IPAddress staticIP, gateway, subnet;
        // staticIP.fromString(custom_ip.getValue());
        // gateway.fromString(custom_gateway.getValue());
        // subnet.fromString(custom_subnet.getValue());
        // WiFi.config(staticIP, gateway, subnet); 

        startWebServer(); // starts the web server
    }

} 

void relayOnOff(int relay) {

    switch(relay){
      case 1: 
          if(relayState1 == 1) {
            digitalWrite(PIN_RELAY_1, LOW); // turn on relay 1
            relayState1 = 0;
            Serial.println("Switch 1 ON");
          }
          else if (relayState1 == 0) {
            digitalWrite(PIN_RELAY_1, HIGH); // turn off relay 1
            relayState1 = 1;
            Serial.println("Switch 1 OFF");
          }
          delay(100);
      break;
      case 2: 
          if(relayState2 == 1) {
          digitalWrite(PIN_RELAY_2, LOW); // turn on relay 2
          relayState2 = 0;
          Serial.println("Switch 2 ON");
          }
          else if (relayState2 == 0) {
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
          else if (relayState3 == 0) {
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
          else if (relayState4 == 0) {
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
    if (digitalRead(TOUCH_SENSOR_1) == HIGH){
        delay(500);
        relayOnOff(1);      
    }   
    if (digitalRead(TOUCH_SENSOR_2) == HIGH) {
        delay(500);
        relayOnOff(2);  
    }   
    if (digitalRead(TOUCH_SENSOR_3) == HIGH) {
        delay(500);
        relayOnOff(3);  
    }   
    if (digitalRead(TOUCH_SENSOR_4) == HIGH) {
        delay(500);
        relayOnOff(4);  
    }
    
}

void webControl() { 

    WiFiClient client = server.available();   // Listen for incoming clients

    if (client) {                               // If a new client connects,
     
        Serial.println("New Client.");          // print a message out in the serial port
        String currentLine = "";                // make a String to hold incoming data from the client
        currentTime = millis();
        previousTime = currentTime;
        while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
            currentTime = millis();         
            if (client.available()) {             // if there's bytes to read from the client,
                char c = client.read();             // read a byte, then
                Serial.write(c);                    // print it out the serial monitor
                header += c;
                if (c == '\n') {                    // if the byte is a newline character
                    // if the current line is blank, you got two newline characters in a row.
                    // that's the end of the client HTTP request, so send a response:
                    if (currentLine.length() == 0) {
                        // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                        // and a content-type so the client knows what's coming, then a blank line:
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();
                        
                        // To turn the Relay on and off
                        if (header.indexOf("GET /1") >= 0) {
                            relayOnOff(1);
                        } 
                        else if (header.indexOf("GET /2") >= 0) {
                            relayOnOff(2);
                        } 
                        else if (header.indexOf("GET /3") >= 0) {
                            relayOnOff(3);
                        } 
                        else if (header.indexOf("GET /4") >= 0) {
                            relayOnOff(4);
                        }
                                    
                        // Display the HTML web page
                        client.println("<!DOCTYPE html><html>");
                        client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
                        client.println("<link rel=\"icon\" href=\"data:,\">");
                        // CSS to style the on/off buttons 
                        // Feel free to change the background-color and font-size attributes to fit your preferences
                        client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
                        client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
                        client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
                        client.println(".button2 {background-color: #77878A;}</style>");
                        client.println("<script>function autoRefresh() {window.location.href = window.location.protocol + '//' + window.location.hostname;} setInterval(autoRefresh, 1000); </script></head>");
                        
                        // Web Page Heading
                        client.println("<body><h1>Smart Extension Board (ESP8266)</h1>");

                        // Updating all switches
                        client.println("<p><h2 id='switch1'>");
                        if (relayState1==0) {
                            client.println("Switch 1 ON:</h2>");
                        } 
                        else {
                            client.println("Switch 1 Off:</h2>");
                        }
                        client.println("<a href=\"/1\"><button class=\"button\">Switch</button></a>");
                        client.println("</p>");

                        client.println("<p><h2 id='switch2'>");
                        if (relayState2==0) {
                            client.println("Switch 2 ON:</h2>");
                        } 
                        else {
                            client.println("Switch 2 Off:</h2>");
                        }
                        client.println("<a href=\"/2\"><button class=\"button\">Switch</button></a>");
                        client.println("</p>");

                        client.println("<p><h2 id='switch3'>");
                        if (relayState3==0) {
                            client.println("Switch 3 ON:</h2>");
                        } 
                        else {
                            client.println("Switch 3 Off:</h2>");
                        }
                        client.println("<a href=\"/3\"><button class=\"button\">Switch</button></a>");
                        client.println("</p>");

                        client.println("<p><h2 id='switch4'>");
                        if (relayState4==0) {
                            client.println("Switch 4 ON:</h2>");
                        } 
                        else {
                            client.println("Switch 4 Off:</h2>");
                        }
                        client.println("<a href=\"/4\"><button class=\"button\">Switch</button></a>");
                        client.println("</p>");


                        client.println("</body></html>");
                        // The HTTP response ends with another blank line
                        client.println();
                        // Break out of the while loop
                        break;
                    } 
                    else { // if you got a newline, then clear currentLine
                        currentLine = "";
                    }

                } 
                else if (c != '\r') {  // if you got anything else but a carriage return character,
                    currentLine += c;      // add it to the end of the currentLine
                }
            }
        }
        // Clear the header variable
        header = "";
        // Close the connection
        client.stop();
        Serial.println("Client disconnected.");
        Serial.println("");
    }    
}

void startWebServer() {

  // Start the server only if WiFi is connected
  if (WiFi.status() == WL_CONNECTED) {
    server.begin();
    Serial.println("HTTP server started");
    webServerRunning = true;
  }

}

void stopWebServer() {

  if (webServerRunning) {
    server.stop();
    Serial.println("HTTP server stopped");
    webServerRunning = false;
  }

}

void setup() {

    Serial.begin(115200); 
    Serial.println("Setting up...");
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

    wm.autoConnect();
    startWebServer();
    
}
 
void loop() {
    
    wifiConnect(); 
    touchControl();
    webControl();
    
}
