#include "thingProperties.h"
#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include <dht11esp8266.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// Replace with your network credentials


// Define the pins for the sensors
#define DHTPIN D7
// DHT11 data pin
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);

Adafruit_BMP085 bmp;

TinyGPSPlus gps;
SoftwareSerial ss(D1, D0); // RX, TX

// Variables to hold sensor data


// Cloud properties
float cloudTemperature;
float cloudHumidity;
float cloudPressure;
double cloudLatitude;
double cloudLongitude;





void setup() {
  Serial.begin(115200);
  ss.begin(9600);

  dht.begin();
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) {}
  }

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
}

void loop() {
  ArduinoCloud.update();

  // Read DHT11 sensor data
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  // Read BMP180 sensor data
  pressure = bmp.readPressure() / 100.0F; // hPa

  // Read GPS data
  while (ss.available() > 0) {
    gps.encode(ss.read());
  }
  if (gps.location.isUpdated()) {
    latitude = gps.location.lat();
    longitude = gps.location.lng();
  }

  // Update cloud properties
  cloudTemperature = temperature;
  cloudHumidity = humidity;
  cloudPressure = pressure;
  cloudLatitude = latitude;
  cloudLongitude = longitude;

  // Print values to Serial Monitor (optional)
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" degC ");
  Serial.print(" ");
  Serial.print("Humidity");
  Serial.print(humidity);
  Serial.print("%");
  Serial.print("Pressure");
  Serial.print(pressure);
  Serial.print("hPa");
  
  delay(1000); // Wait for 1 second before next update
  
}

/*
  Since Latitude is READ_WRITE variable, onLatitudeChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onLatitudeChange()  {
  // Add your code here to act upon Latitude change
}
/*
  Since Longitude is READ_WRITE variable, onLongitudeChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onLongitudeChange()  {
  // Add your code here to act upon Longitude change
}
