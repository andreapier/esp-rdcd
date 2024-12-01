#include <ArduinoOTA.h>

#include <state.h>

bool ota_busy = false;

void ota_setup()
{
    // ArduinoOTA.setHostname("ESP-RDCD");
    ArduinoOTA.onStart([]()
                       { ota_busy = true; });

    ArduinoOTA.onError([](ota_error_t error)
                       {
    mqtt_serial.print("Error on OTA - restarting");
    esp_restart(); });
    ArduinoOTA.begin();
}

void ota_loop()
{
    ArduinoOTA.handle();

    while (ota_busy)
    {
        // Stop processing during OTA
        ArduinoOTA.handle();
    }
}