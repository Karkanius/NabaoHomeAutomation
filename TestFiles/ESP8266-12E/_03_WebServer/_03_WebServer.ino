#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
// Replace with your network credentials
const char* ssid = "********";
const char* password = "********";
 
ESP8266WebServer server(80);   //instantiate server at port 80 (http port)
 
String page = "";
int LEDPin = 2;
boolean toggle = false;

void setup(void){
  //the HTML of the web page
  page = "<h1>Simple NodeMCU Web Server</h1><p><a href=\"LEDToggle\"><button>Turn ON</button></a>&nbsp;</p>";
  //make the LED pin output and initially turned off
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, HIGH);
   
  delay(1000);
  Serial.begin(9600);
  WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");
 
  // Wait for connection
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
    server.send(200, "text/html", page);
  });
  server.on("/LEDToggle", [](){
    if(toggle) {
      page = "<h1>Simple NodeMCU Web Server</h1><p><a href=\"LEDToggle\"><button>Turn ON</button></a>&nbsp;</p>";
      digitalWrite(LEDPin, HIGH);
    }
    else {
      page = "<h1>Simple NodeMCU Web Server</h1><p><a href=\"LEDToggle\"><button>Turn OFF</button></a>&nbsp;</p>";
      digitalWrite(LEDPin, LOW);
    }
    server.send(200, "text/html", page);
    toggle = !toggle;
    delay(100);
  });
  server.begin();
  Serial.println("Web server started!");
}
 
void loop(void){
  server.handleClient();
}

