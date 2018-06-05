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

# define nSamples 25        // Number of Samples

/*
 * DHT22
 */
# include <DHT.h>
# define dhtPIN 16          // (D0) DHT22 Data Pin
DHT dht(dhtPIN, DHT22);
int humSum = 0;
int humValue = 0;
int tempSum = 0;
int tempValue = 0;

/*
 * GL5516
 */
# define gl5516PIN A0       // (A0) Analog Luminosity Sensor
int luxSum = 0;
int luxValue = 0;

/*
 * BMP280
 */
# include <Adafruit_BMP280.h>
# define bmp280sckPIN  5    // (D1) BMP280 SCK
# define bmp280misoPIN 4    // (D2) BMP280 MISO
# define bmp280mosiPIN 0    // (D3) BMP280 MOSI
# define bmp280csPIN   2    // (D4) BMP280 CS
Adafruit_BMP280 bmp(bmp280csPIN, bmp280mosiPIN, bmp280misoPIN, bmp280sckPIN);
int presSum = 0;
int presValue = 0;

/*
 * RAIN SENSOR
 */
# define rainPIN 14         // (D5) Rain Sensor
boolean rain = false;
int rainCount = 0;

/*
 * Custom Functions
 */
void collectSamples() {
  for(int i = 0; i < nSamples; i++) {
    //-------------------------------
    // DHT22
    dht.read(dhtPIN);
    humSum += dht.readHumidity();
    tempSum += dht.readTemperature();
    //-------------------------------
    // GL5516
    luxSum += analogRead(gl5516PIN);
    //-------------------------------
    // BMP280
    tempSum += bmp.readTemperature();
    presSum += bmp.readPressure();
    //-------------------------------
    // RAIN SENSOR
    rainCount++;
    //-------------------------------
    delay(100);
  }
}

void calculateValues() {
  humValue  = humSum  / nSamples;
  tempValue = tempSum / nSamples / 2;    // Both DHT22 and BMP280 are reading temperature values
  luxValue  = luxSum  / nSamples;
  presValue = presSum / nSamples;
  rain = rainCount > (nSamples/2);
}

void resetData() {
  humSum  = 0;
  tempSum = 0;
  luxSum  = 0;
  presSum = 0;
  rainCount = 0;
}

String rainState() {
  if(rain) { return "DRY"; }
  return "WET";
}

void printToSerial() {
  Serial.print("-------------------------\n" );
  // Air Humidity
  Serial.print("Humidity    = ");
  Serial.print(humValue);
  Serial.print("%\n");
  // Air Temperature
  Serial.print("Temperature = ");
  Serial.print(tempValue);
  Serial.print(char(176));
  Serial.print("C\n");
  // Luminosity
  Serial.print("Luminosity  = ");
  Serial.print(luxValue);
  Serial.print("%\n");
  // Air Pressure
  Serial.print("Pressure    = ");
  Serial.print(presValue);
  Serial.print("Pa\n");
  // Rain
  Serial.print("Rain Sensor = ");
  Serial.print(rainState());
  Serial.print("\n");
  Serial.print("-------------------------\n\n" );
}

/*
 * SETUP and LOOP
 */
void setup() {
  Serial.begin(9600);
  delay(500);
  if (!bmp.begin()) {  
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }
}

void loop() {
  delay(2000);
  collectSamples();
  calculateValues();
  resetData();
}
