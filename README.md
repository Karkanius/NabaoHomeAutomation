# NabaoHomeAutomation

Home Automation project developed as complementary work besides the degree of Computer and Telematics Engineering from University of Aveiro.

### Modules

The system is being developed having "modular" as keyword.

* [CENTRAL](./Modules/CENTRAL) - The system's central unit. Receives and processes the information sent by the other modules.
* [CONTROL_PANEL](./Modules/CONTROL_PANEL) - Fast way to check if the remaining modules (apart from the CENTRAL module) are working as expected.
* [WATERING_SYSTEM](./Modules/WATERING_SYSTEM) - Watering system based on a soil moisture sensor (FC-28) and a water pump.
* [WEATHER_STATION](./Modules/WEATHER_STATION) - Module based on a DHT22, a GL5516 and a rain sensor.

So far, these are the modules which are developed/projected.

### Libraries

The following libraries are required for the _.ino_ files.

* *DHT.h*
* *ESP8266WebServer.h*
* *ESP8266WiFi.h*
* *WiFiClient.h*

Libraries list will be updated everytime a ney library is required.

### Acknowledgments

* Professor J. A. Fonseca
* Professor J. P. Barraca
* Professor J. E. Oliveira
* Professor M. Vasconcelos
[![Movimento Maker Portugal](https://forum.movimentomaker.pt/uploads/default/original/1X/c2ce1564e35d002983319f614bebd67ee76a054d.png)](http://forum.movimentomaker.pt)
