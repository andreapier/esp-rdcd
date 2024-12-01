#ifndef STATE_h
#define STATE_h

#include <PubSubClient.h>

#include <const.h>
#include <mqtt_serial.h>

/**
 * Last PWM value
 */
uint8_t state_pwm = 0;

WiFiClient wifi_client;
PubSubClient pub_sub_client(wifi_client);
MQTTSerial mqtt_serial(&pub_sub_client, CHANNEL_LOG);

#endif