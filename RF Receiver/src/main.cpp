#include <Arduino.h>

// Receiver
#include <VirtualWire.h> 4 6
#define sendPin 8
#define ledPin 13        //Onboard LED = digital pin 13

uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen=VW_MAX_MESSAGE_LEN;

const char *check="Wakaka!";
const char *swOn="On";

int count = 0;

void setup() 
{
    Serial.begin(9600);
    vw_set_ptt_inverted(true);
    vw_setup(300);
    vw_set_rx_pin(11);
    vw_rx_start();
    pinMode(ledPin, OUTPUT);
}

void loop() 
{
    if (vw_get_message(buf, &buflen)) 
    {
        Serial.println(millis());    
        Serial.print("Message: ");
        Serial.println((char*)buf);    
        digitalWrite(ledPin, HIGH);     
        count = 0;
    }
    else
        count++;

    if(count > 100)
        digitalWrite(ledPin, LOW);
}