#include <Arduino.h>
// Transmitter
#include <VirtualWire.h>

#define sendPin 7
#define ledPin 13        //Onboard LED = digital pin 13

uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen=VW_MAX_MESSAGE_LEN;

const char *check="Wakaka!";
const char *swOn="On";

void setup() 
{
    Serial.begin(9600);
    vw_set_ptt_inverted(true);          // Enable RF module
    vw_setup(300);                      // Initialize transmit rate
    vw_set_tx_pin(12);                  // TX pin (Transmit pin)
    pinMode(sendPin, INPUT_PULLUP);
    pinMode(ledPin, OUTPUT);
}

void loop() 
{
    digitalWrite(ledPin, LOW);
    if (digitalRead(sendPin) == 0)
    {
        vw_send((uint8_t *)swOn, strlen(swOn));
        vw_wait_tx();
        Serial.println("Switch On");
        delay(100);
    }
    
    vw_send((uint8_t *)check, strlen(check));
    vw_wait_tx();
    Serial.println((char*)check);
    delay(300);
}