/**
 * @file main.cpp
 * @brief IoT Environmental Monitoring System for Smart Agriculture
 *
 * This firmware runs on an ESP32 and performs the following actions:
 * 1. Connects to a local Wi-Fi network.
 * 2. Reads temperature and humidity data from a DHT22 sensor.
 * 3. Prints the collected data to the Serial Monitor.
 *
 * This system is designed as the data collection node for a larger smart
 * agriculture platform. The data can be sent to a cloud server for storage
 * and analysis by a machine learning model.
 *
 * @vijitviveksingh
 * @Feb 2025
 */

#include <Arduino.h>
#include <WiFi.h>
#include "DHT.h"

// --- Configuration ---

// WiFi Credentials
const char* WIFI_SSID = "ultron";         
const char* WIFI_PASSWORD = "12345678"; 

// DHT Sensor Configuration
#define DHT_PIN 4       // The ESP32 pin connected to the DHT22 data pin
#define DHT_TYPE DHT22  // Using the DHT22 sensor

// --- Global Objects ---
DHT dht(DHT_PIN, DHT_TYPE);

/**
 * @brief Connects the ESP32 to the configured Wi-Fi network.
 *
 * This function will attempt to connect to Wi-Fi and will block until a
 * connection is established. It provides serial feedback on the connection status.
 */
void connectToWiFi() {
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

/**
 * @brief Standard Arduino setup function. Runs once on boot.
 *
 * Initializes Serial communication, the DHT sensor, and connects to Wi-Fi.
 */
void setup() {
  // Start serial communication for debugging and output
  Serial.begin(115200);
  Serial.println("\n--- IoT Environmental Monitor ---");

  // Initialize the DHT sensor
  dht.begin();

  // Connect to Wi-Fi
  connectToWiFi();
}

/**
 * @brief Standard Arduino loop function. Runs repeatedly.
 *
 * Reads sensor data every 5 seconds and prints it to the serial monitor.
 */
void loop() {
  // Wait 5 seconds between measurements
  delay(5000);

  // Read humidity
  float humidity = dht.readHumidity();
  // Read temperature as Celsius
  float temperature = dht.readTemperature();

  // Check if any reads failed and exit early to try again.
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Error: Failed to read from DHT sensor!");
    return;
  }

  // If readings are successful, print them
  Serial.println("--- New Sensor Reading ---");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

}
