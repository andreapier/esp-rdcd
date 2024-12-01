#ifndef MQTT_h
#define MQTT_h

#include <PubSubClient.h>

#include <mqtt_serial.h>
#include <settings.h>
#include <state.h>
#include <pwm.h>

void on_message_received(char *topic, uint8_t *payload, unsigned int length);

bool mqtt_connected()
{
  boolean result = pub_sub_client.connected();

  return result;
}

bool mqtt_connect()
{
  if (!mqtt_connected())
  {
    if (pub_sub_client.connect(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PWD, CHANNEL_LWT, 0, true, "Offline"))
    {
      pub_sub_client.publish(CHANNEL_CONFIG, "{\"name\":\"Esp RDCD\",\"avty_t\":\"~/LWT\",\"pl_avail\":\"Online\",\"pl_not_avail\":\"Offline\",\"uniq_id\":\"esp_rdcd\",\"device\":{\"identifiers\":[\"esp_rdcd\"]}, \"~\":\"esp_rdcd\"}", true);
      pub_sub_client.publish(CHANNEL_LWT, "Online", true);
      pub_sub_client.publish(CHANNEL_STATE_PWM, 0, true);

      pub_sub_client.subscribe(CHANNEL_PWM_SET);
    }
  }

  return mqtt_connected();
}

void mqtt_loop(unsigned int wait_time)
{
  unsigned long start_time = millis();

  while (millis() < start_time + wait_time)
  {
    pub_sub_client.loop();
  }
}

void mqtt_setup()
{
  pub_sub_client.setServer(MQTT_SERVER, MQTT_PORT);
  pub_sub_client.setCallback(on_message_received);
}

void on_message_received(char *topic, uint8_t *payload, unsigned int length)
{
  if (strcmp(topic, CHANNEL_PWM_SET) == 0)
  {
    mqtt_serial.printf("[MQTT] Received message %s with payload %i:\n", topic, &payload);
    pwm_set(*payload);
  }
  else
  {
    mqtt_serial.printf("[MQTT] Received message for unknown topic: %s\n", topic);
  }
}

#endif