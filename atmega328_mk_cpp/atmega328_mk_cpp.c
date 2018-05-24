#include <Arduino.h>

#define LED_PIN 13
void loop()
{
        pinMode(LED_PIN, OUTPUT);

}
void loop()
{
        digitalWrite(LED_PIN, HIGH);
        delay(1000);
        digitalWrite(LED_PIN, LOW);
        delay(500);
}

