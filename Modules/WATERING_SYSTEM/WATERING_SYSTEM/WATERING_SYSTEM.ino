/*
 * Paulo Vasconcelos
 * 2018 may
 * paulobvasconcelos@gmail.com
 */

/*
 * ---NodeMCU pinout---
 * #define D0 16
 * #define D1 5  // I2C Bus SCL (clock)
 * #define D2 4  // I2C Bus SDA (data)
 * #define D3 0
 * #define D4 2  // Same as "LED_BUILTIN", but inverted logic
 * #define D5 14 // SPI Bus SCK (clock)
 * #define D6 12 // SPI Bus MISO 
 * #define D7 13 // SPI Bus MOSI
 * #define D8 15 // SPI Bus SS (CS)
 * #define D9 3  // RX0 (Serial console)
 * #define D10 1 // TX0 (Serial console)
 */

# define wateringTime 600     // Watering Time (miliseconds)

# define pumpPIN    16         // (D0) Water Pump
# define soilMoisturePIN 4     // (D2) FC-28 Soil Hygrometer Module

boolean belowThreshold = false;
uint8_t n = 15;

/*
 * Custom Functions
 */
void pinSetup() {
  pinMode(pumpPIN,    OUTPUT);
  pinMode(soilMoisturePIN, INPUT);
}

// Threshold Value Defined by Potentiometer
boolean checkMoistureSensor() {
  return (soilMoisturePIN==HIGH);
}

void water() {
  // Pump ON
  digitalWrite(pumpPIN, HIGH);
  Serial.print("---------------\n");
  Serial.print("PUMP_STATE = ON\n");

  for(int i = 0; i < n; i++) {
    Serial.print("-");
    delay(wateringTime/n);
  }
  Serial.print("\n");

  // Pump OFF
  digitalWrite(pumpPIN, LOW);
  Serial.print("PUMP_STATE = OFF\n");
  Serial.print("---------------\n\n");
  delay(500);
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
  belowThreshold = checkMoistureSensor();
  if(belowThreshold) { water(); }
}
