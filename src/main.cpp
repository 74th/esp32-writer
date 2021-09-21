#include <Arduino.h>

// #define RTS_PIN 2
// #define RXD_PIN 3
#define TXD_PIN 6
// #define CTS_PIN 5
#define BOOT_PIN 27
#define EN_PIN 26
#define SWITCH_PIN 4

void setup()
{
    // pinMode(RTS_PIN, INPUT_PULLUP);
    // pinMode(RXD_PIN, INPUT_PULLUP);
    pinMode(TXD_PIN, INPUT_PULLUP);
    // pinMode(CTS_PIN, INPUT_PULLUP);
    pinMode(SWITCH_PIN, INPUT_PULLUP);

    pinMode(EN_PIN, OUTPUT);
    pinMode(BOOT_PIN, OUTPUT);

    digitalWrite(EN_PIN, HIGH);
    digitalWrite(BOOT_PIN, HIGH);
    Serial.begin(115200);
}

void loop()
{
    if (digitalRead(SWITCH_PIN) == LOW)
    {
        Serial.println("1. PUSH detected. BOOT = LOW");
        digitalWrite(BOOT_PIN, LOW);
        delay(500);
        Serial.println("2. EN = LOW");
        digitalWrite(EN_PIN, LOW);
        delay(500);
        Serial.println("3. EN = HIGH");
        digitalWrite(EN_PIN, HIGH);
        delay(500);
        Serial.println("4. BOOT = HIGH");
        digitalWrite(BOOT_PIN, HIGH);
        Serial.println("5. Waiting complete to upload.");
        bool keep = true;
        PinStatus txd_out;
        while (keep)
        {
            delay(500);
            absolute_time_t start = get_absolute_time();
            while (1)
            {
                txd_out = digitalRead(TXD_PIN);
                if (txd_out == LOW)
                {
                    Serial.print(".");
                    break;
                }
                absolute_time_t current = get_absolute_time();
                int64_t us = absolute_time_diff_us(start, current);
                if (us > 2000000)
                {
                    keep = false;
                    break;
                }
            }
        }
        Serial.println("");
        Serial.println("6. Upload Done. EN = LOW");
        digitalWrite(EN_PIN, LOW);
        delay(500);
        Serial.println("7. EN = HIGH");
        digitalWrite(EN_PIN, HIGH);
        Serial.println("8. All done!!");
    }
}
