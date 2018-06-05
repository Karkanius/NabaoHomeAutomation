/*
 * Paulo Vasconcelos
 * 2018 june
 * paulobvasconcelos@gmail.com
 */

/*
 * ---NodeMCU pinout---
 * #define D0 16
 * #define D1  5 // I2C Bus SCL (clock)
 * #define D2  4 // I2C Bus SDA (data)
 * #define D3  0
 * #define D4  2 // Same as "LED_BUILTIN", but inverted logic
 * #define D5 14 // SPI Bus SCK (clock)
 * #define D6 12 // SPI Bus MISO 
 * #define D7 13 // SPI Bus MOSI
 * #define D8 15 // SPI Bus SS (CS)
 * #define D9  3 // RX0 (Serial console)
 * #define D10 1 // TX0 (Serial console)
 */

# include <DHT.h>

# define nSamples 25   // Number of Samples

# define dataPIN 16    // (D0) DHT22 Data Output Pin

DHT dht(dataPIN, DHT22);
double humSum = 0;
int humValue = 0;
double tempSum = 0;
int tempValue = 0;

/*
 * Custom Functions
 */
void pinSetup() {
  pinMode(dataPIN, OUTPUT);
}

void printToSerial() {
  Serial.print("-------------------------\n" );
  // Air Humidity
  Serial.print("Air Humidity = " );                       
  Serial.print(humValue);
  Serial.print("%\n");
  // Air Temperature
  Serial.print("Air Temperature = " );                       
  Serial.print(tempValue);
  Serial.print(char(176));
  Serial.print("C\n");
  Serial.print("-------------------------\n\n" );
}

void collectSamples() {
  for(int i = 0; i < nSamples; i++) {
    dht.read(dataPIN);
    humSum += dht.readHumidity();
    tempSum += dht.readTemperature();
    delay(100);
  }
}

void calculateValues() {
  humValue   = humSum  / nSamples;
  tempValue  = tempSum / nSamples;
}

/*
 * SETUP and LOOP
 */
void setup() {
  Serial.begin(9600);
  delay(500);
  pinSetup();
}

void loop() {
  delay(2000);
  collectSamples();
  calculateValues();
}
