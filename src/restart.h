#ifndef ESP_RDCD_RESTART_H
#define ESP_RDCD_RESTART_H

#include <Arduino.h>

void restart_board()
{
  esp_restart();
}

#endif