#include <Arduino.h>

#include "pwm.h"
#include "setup.h"

uint8_t pwm_state = 0;

uint8_t pwm_get() {
    return pwm_state;
}

void pwm_set(uint8_t payload)
{
    analogWrite(PIN_PWM, payload);
    pwm_state = payload;
}

void pwm_setup()
{
    pinMode(PIN_PWM, OUTPUT);
}