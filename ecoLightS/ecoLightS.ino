#include <VirtualWire.h>

#define TRANSMITTER_PIN 2
#define LIGHT_PIN A0

unsigned int lightValue;
unsigned int valueOfSwitch = 520;
boolean relayState = false;

void setup()
{
    Serial.begin(9600);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    
    vw_set_tx_pin(TRANSMITTER_PIN);
    vw_setup(2000);
}

void sendSignal(const char *msg){
  vw_send((uint8_t *)msg, strlen(msg));
  vw_wait_tx();
}

void loop()
{
  lightValue = analogRead(LIGHT_PIN);
  if(lightValue > valueOfSwitch && !relayState){
   
    sendSignal("on");
    relayState = true;
    
  }
  
  else if(lightValue < valueOfSwitch && relayState){
    
    sendSignal("off");
    relayState = false;
    
  }
}
