/*
   Paulo Vasconcelos
   2018 june
   paulobvasconcelos@gmail.com
*/

/*
   ---NodeMCU pinout---
   #define D0 16
   #define D1  5 // I2C Bus SCL (clock)
   #define D2  4 // I2C Bus SDA (data)
   #define D3  0
   #define D4  2 // Same as "LED_BUILTIN", but inverted logic
   #define D5 14 // SPI Bus SCK (clock)
   #define D6 12 // SPI Bus MISO
   #define D7 13 // SPI Bus MOSI
   #define D8 15 // SPI Bus SS (CS)
   #define D9  3 // RX0 (Serial console)
   #define D10 1 // TX0 (Serial console)
*/

# include <ESP8266WiFi.h>
# include <WiFiClient.h>
# include <ESP8266WebServer.h>
 
// Replace with your network credentials
const char* ssid = "KarkaniusHS";
const char* password = "NHATest0";

ESP8266WebServer server(80);

# define LEDPin 2
# define potPin A0

// Potentiometer Analog Value [0-1023]
int potValue=0;

// HTML page
String page;

void setLEDstate(boolean turnOn) {
  // Negative logic (PIN = HIGH => LED = OFF)
  if(turnOn) { digitalWrite(LEDPin, LOW); }
  else       { digitalWrite(LEDPin, HIGH); }
}

void setup() {
  Serial.begin(9600);
  pinMode(LEDPin, OUTPUT);
  pinMode(potPin, INPUT);
  delay(100);

  // Connect to network
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.on("/", [](){
    // Initialization as String to prevent errors when concatenating String with int
    page = "<h1>Potentiometer Value</h1><p><div>";
    page = page+potValue+"</div></p>";
    server.send(200, "text/html", page);
  });

  server.begin();
}

void loop() {
  potValue = analogRead(potPin);
  if(potValue>511) { setLEDstate(true);  }    // LED OF
  else             { setLEDstate(false); }    // LED OFF
  server.handleClient();
  delay(50);
}

