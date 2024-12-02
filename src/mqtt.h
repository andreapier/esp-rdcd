#ifndef DEF_ESP_RDCD_MQTT
#define DEF_ESP_RDCD_MQTT

#include <ArduinoOTA.h>
#include <PubSubClient.h>
#include <WiFi.h>

#include "mqtt_serial.h"
#include "pwm.h"
#include "setup.h"
#include "restart.h"

#define MQTT_TOPIC_ANNOUNCE_SENSORS "homeassistant/sensor/esp-rdcd/config"
#define MQTT_TOPIC_LWT "esp-rdcd/LWT"
#define MQTT_TOPIC_LOG "esp-rdcd/log"
#define MQTT_TOPIC_PWM_SET "esp-rdcd/pwm/set"
#define MQTT_TOPIC_PWM_STATE "esp-rdcd/pwm/state"

WiFiClient wifi_client;
PubSubClient mqtt_client(wifi_client);

void send_values()
{
  Serial.printf("Sending values in MQTT.\n");
  char dataArray[10];
  sprintf(dataArray, "%d", pwm_get());
  mqtt_client.publish(MQTT_TOPIC_PWM_STATE, dataArray, true);
}

void reconnect_mqtt()
{
  // Loop until we're reconnected
  int i = 0;
  while (!mqtt_client.connected())
  {
    Serial.print("Attempting MQTT connection...");

    if (mqtt_client.connect(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD, MQTT_TOPIC_LWT, 0, true, "Offline"))
    {
      Serial.println("connected!");
      mqtt_client.publish(MQTT_TOPIC_ANNOUNCE_SENSORS, "{\"name\":\"Sensors\",\"stat_t\":\"~/LWT\",\"avty_t\":\"~/LWT\",\"pl_avail\":\"Online\",\"pl_not_avail\":\"Offline\",\"uniq_id\":\"esp-rdcd\",\"device\":{\"identifiers\":[\"esp-rdcd\"]}, \"~\":\"esp-rdcd\",\"json_attr_t\":\"~/ATTR\"}", true);
      mqtt_client.publish(MQTT_TOPIC_LWT, "Online", true);
      mqtt_client.publish(MQTT_TOPIC_PWM_STATE, "0", true);
      mqtt_client.subscribe(MQTT_TOPIC_PWM_SET);
    }
    else
    {
      Serial.printf("failed, rc=%d, try again in 5 seconds", mqtt_client.state());
      unsigned long start = millis();

      while (millis() < start + 5000)
      {
        ArduinoOTA.handle();
      }

      if (i++ == 100)
      {
        Serial.printf("Tried for 500 sec, rebooting now.");
        restart_board();
      }
    }
  }
}

void callback(char *topic, uint8_t *payload, unsigned int length)
{
  mqtt_serial.printf("Message arrived [%s]: %s\n", topic, payload);

  if (strcmp(topic, MQTT_TOPIC_PWM_SET) == 0)
  {
    uint8_t pwm_value = 0;
    sscanf((const char*)payload, "%d", &pwm_value);
    pwm_set(pwm_value);
  }
  else
  {
    Serial.printf("Unknown topic: %s\n", topic);
  }

  send_values();
}

#endif