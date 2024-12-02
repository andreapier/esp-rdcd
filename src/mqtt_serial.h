#ifndef DEF_ESP_RDCD_MQTT_SERIAL
#define DEF_ESP_RDCD_MQTT_SERIAL

#include "Stream.h"
#include <PubSubClient.h>
#include <WiFi.h>

HardwareSerial log_serial(0);

class MQTTSerial: public Stream
{
private:
    PubSubClient* _client = nullptr;
    char _topic[64];

public:
    inline void begin(PubSubClient* mqtt_client, const char* topic)
    {
        _client = mqtt_client;
        strcpy(_topic, topic);
    };

    inline size_t write(uint8_t)
    {
        return 0;
    };
    
    size_t write(const uint8_t *buffer, size_t size);
    
    inline int available(void)
    {
        return _client->connected();
    };
    
    inline int availableForWrite(void)
    {
        return 0;
    };

    inline int peek(void)
    {
        return 0;
    };
    
    inline int read(void)
    {
        return 0;
    };

    inline void flush(void)
    {};

    inline size_t write(const char * s)
    {
        return write((uint8_t*) s, strlen(s));
    }

    inline size_t write(unsigned long n)
    {
        return write((uint8_t) n);
    }

    inline size_t write(long n)
    {
        return write((uint8_t) n);
    }

    inline size_t write(unsigned int n)
    {
        return write((uint8_t) n);
    }

    inline size_t write(int n)
    {
        return write((uint8_t) n);
    }

    MQTTSerial();
    ~MQTTSerial();
};

MQTTSerial mqtt_serial;

MQTTSerial::MQTTSerial()
{
    log_serial.begin(115200);
}

size_t MQTTSerial::write(const uint8_t *buffer, size_t size)
{
    if (WiFi.status() == WL_CONNECTED && _client!=nullptr &&_client->connected())
    {
        _client->publish(_topic,buffer,size);
    }

    log_serial.write(buffer,size);
    
    return size;
}

MQTTSerial::~MQTTSerial()
{
}

#endif