#include <connection.h>
#include <const.h>
#include <mqtt.h>
#include <ota.h>
#include <pwm.h>
#include <state.h>

char pwm_str[10];

void wait_loop()
{
    mqtt_serial.printf("[MAIN] Waiting %i seconds\n", FREQUENCY / 1000);
    ota_loop();
    mqtt_loop(FREQUENCY);
}

void setup()
{
    pwm_setup();
    setup_wifi();
    mqtt_setup();
    ota_setup();
}

void loop()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        // restart board if needed
        check_wifi();
    }

    if (!mqtt_connected())
    {
        if (!mqtt_connect())
        {
            mqtt_serial.println("[MQTT] Connection KO");
            wait_loop();

            return;
        }
    }

    sprintf(pwm_str, "%i", state_pwm);

    mqtt_serial.println();
    mqtt_serial.printf("[RDCD] PWM: %s cm\n", pwm_str);
    mqtt_serial.println();

    pub_sub_client.publish(CHANNEL_STATE_PWM, pwm_str, true);

    wait_loop();
}