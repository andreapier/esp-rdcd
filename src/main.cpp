#include <Arduino.h>
#include <ArduinoOTA.h>
#include <HardwareSerial.h>
#include <PubSubClient.h>
#include <WiFi.h>

#include "mqtt.h"
#include "mqtt_serial.h"
#include "restart.h"
#include "setup.h"
#include "pwm.h"

bool busy = false;
uint16_t loopcount = 0;
const uint16_t RECIEVE_TIMEOUT_MS = 1000;

void extra_loop()
{
  mqtt_client.loop();
  ArduinoOTA.handle();

  while (busy)
  {
    //Stop processing during OTA
    ArduinoOTA.handle();
  }
}

void check_wifi()
{
  int i = 0;

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    mqtt_serial.print(".");
    
    if (i++ == 240)
    {
      mqtt_serial.printf("Tried connecting for 120 sec, rebooting now.");
      restart_board();
    }
  }
}

void setup_wifi()
{
  delay(10);
  mqtt_serial.printf("Connecting to %s with pwd %s\n", WIFI_SSID, WIFI_PWD);
  WiFi.begin(WIFI_SSID, WIFI_PWD, 0, 0, true);
  check_wifi();
  mqtt_serial.printf("Connected. IP Address: %s\n", WiFi.localIP().toString().c_str());
}

void setup()
{
  mqtt_serial.print("Setting up wifi...");
  setup_wifi();
  
  mqtt_serial.print("Setting up OTA...");
  ArduinoOTA.setHostname(HOSTNAME);
  ArduinoOTA.onStart([]() {
    busy = true;
  });
  ArduinoOTA.onError([](ota_error_t error) {
    mqtt_serial.print("Error on OTA - restarting");
    restart_board();
  });
  ArduinoOTA.begin();

  mqtt_client.setCallback(callback);
  mqtt_client.setServer(MQTT_SERVER, MQTT_PORT);

  auto timeout = wifi_client.getTimeout();
  mqtt_serial.printf("Wifi client timeout: %d\n", timeout);
  mqtt_serial.printf(
    "Connecting to MQTT server: %s:%d with username %s and password %s\n",
    MQTT_SERVER, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD
  );
  mqtt_serial.begin(&mqtt_client, MQTT_TOPIC_LOG);
  reconnect_mqtt();
  mqtt_serial.println("OK!");

  pwm_setup();

  mqtt_serial.print("ESP RDCD started!");
}

void wait_loop(uint ms)
{
    unsigned long start = millis();

    while (millis() < start + ms) //wait .5sec between registries
    {
        extra_loop();
    }
}

void loop()
{
  unsigned long start = millis();

  if (WiFi.status() != WL_CONNECTED)
  {
    //restart board if needed
    check_wifi();
  }

  if (!mqtt_client.connected())
  {
    //(re)connect to MQTT if needed
    reconnect_mqtt();
  }

  send_values();//Send the full json message
  mqtt_serial.printf("Done. Waiting %ld ms...", FREQUENCY - millis() + start);
  wait_loop(FREQUENCY - millis() + start);
}