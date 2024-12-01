
#ifndef MQTTSerial_h
#define MQTTSerial_h

#include <Stream.h>
#include <PubSubClient.h>

class MQTTSerial : public Stream
{
private:
    PubSubClient *_client = nullptr;
    char _topic[64];

public:
    size_t write(uint8_t)
    {
        return 0;
    }

    size_t write(const uint8_t *buffer, size_t size)
    {
        if (_client != nullptr && _client->connected())
        {
            _client->publish(_topic, buffer, size);
        }

        Serial.write(buffer, size);

        return size;
    }

    int available(void)
    {
        return _client->connected();
    }

    int availableForWrite(void)
    {
        return 0;
    }

    int peek(void)
    {
        return 0;
    }

    int read(void)
    {
        return 0;
    }

    void flush(void) {}

    void printf(const char *s, ...)
    {
        char char_buffer[255];
        va_list args;
        va_start(args, s);
        int len = vsnprintf(NULL, 0, s, args);
        vsnprintf(char_buffer, 255, s, args);
        write((uint8_t *)char_buffer, len);
        va_end(args);
    }

    size_t write(const char *s)
    {
        return write((uint8_t *)s, strlen(s));
    }

    size_t write(unsigned long n)
    {
        return write((uint8_t)n);
    }

    size_t write(long n)
    {
        return write((uint8_t)n);
    }

    size_t write(unsigned int n)
    {
        return write((uint8_t)n);
    }

    size_t write(int n)
    {
        return write((uint8_t)n);
    }

    size_t write(float n)
    {
        return write((uint32_t)n);
    }

    MQTTSerial(PubSubClient *pub_sub_client, const char *topic)
    {
        _client = pub_sub_client;
        strcpy(_topic, topic);
    }

    ~MQTTSerial() {}
};

#endif