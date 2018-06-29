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

const char* ssid     = "KarkaniusHS";
const char* password = "NHATest0";

WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Assign output variables to GPIO pins
int counter1 = 10;
int counter2 = 10;

void setup() {
  Serial.begin(9600);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            String aux = "";
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /c1/inc") >= 0) {
              counter1++;
              Serial.print("Counter 1++ => Counter 1 = ");
              Serial.println(counter1);
            } else if (header.indexOf("GET /c1/dec") >= 0) {
              counter1--;
              Serial.print("Counter 1-- => Counter 1 = ");
              Serial.println(counter1);
            } else if (header.indexOf("GET /c2/inc") >= 0) {
              counter2++;
              Serial.print("Counter 2++ => Counter 2 = ");
              Serial.println(counter2);
            } else if (header.indexOf("GET /c2/dec") >= 0) {
              counter2--;
              Serial.print("Counter 2-- => Counter 2 = ");
              Serial.println(counter2);
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
            client.println("i { border: solid black; border-width: 0 3px 3px 0; display: inline-block; padding: 3px; }");
            client.println(".right { transform: rotate(-45deg); -webkit-transform: rotate(-45deg); }");
            client.println(".left { transform: rotate(135deg); -webkit-transform: rotate(135deg); }");
            client.println(".up { transform: rotate(-135deg); -webkit-transform: rotate(-135deg); }");
            client.println(".down { transform: rotate(45deg); -webkit-transform: rotate(45deg); }</style></head>");
            
            client.println("<body><h1>ESP8266 Web Server</h1>");
            // Counter 1
            aux = "<p>Counter 1: ";
            aux = aux + counter1 + "</p>";
            client.println(aux);
            client.println("<p><a href=\"/c1/inc\"><button class=\"button\"><i class=\"up\"></i></button></a></p>");
            client.println("<p><a href=\"/c1/dec\"><button class=\"button\"><i class=\"down\"></i></button></a></p>");
            // Counter 2
            aux = "<p>Counter 2: ";
            aux = aux + counter2 + "</p>";
            client.println(aux);
            client.println("<p><a href=\"/c2/inc\"><button class=\"button\"><i class=\"up\"></i></button></a></p>");
            client.println("<p><a href=\"/c2/dec\"><button class=\"button\"><i class=\"down\"></i></button></a></p>");
            client.println("</body></html>");
            
            client.println();
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
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
