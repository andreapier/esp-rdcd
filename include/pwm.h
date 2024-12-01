#ifndef PWM_h
#define PWM_h

#include <Arduino.h>

#include <settings.h>
#include <state.h>

void pwm_setup()
{
    pinMode(PIN_PWM, OUTPUT);

    Serial.begin(9600);

    // Wait for serial port to connect. Needed for native USB port only
    while (!Serial)
    {
        ;
    }
}

void pwm_set(int payload)
{
    analogWrite(PIN_PWM, payload);
    state_pwm = payload;
}
#endif