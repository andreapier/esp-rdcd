#include <Arduino.h>
#include <WiFi.h>

#include <settings.h>
#include <state.h>

bool check_wifi()
{
  int i = 0;

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");

    if (i++ == 120)
    {
      Serial.printf("Tried connecting for 60 sec, rebooting now.");

      return false;
    }
  }

  return true;
}

void setup_wifi()
{
  delay(10);
  boolean connected = false;

  while (!connected)
  {
    // We start by connecting to the main WiFi network
    mqtt_serial.printf("Connecting to %s\n", WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PWD);
    connected = check_wifi();

    // If it fails, we restart the device
    if (!connected)
    {
      esp_restart();
    }

    mqtt_serial.printf("Connected. IP Address: %s\n", WiFi.localIP().toString().c_str());
  }
}