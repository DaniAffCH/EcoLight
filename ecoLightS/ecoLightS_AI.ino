#include <VirtualWire.h>

#define TRANSMITTER_PIN 2
#define LIGHT_PIN A0

unsigned int lightValue;
boolean relayState = false;
boolean switch_;

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

bool reciveFromPython(){
  char msg = Serial.read();
  if(msg == 't') return true;
  if(msg == 'f') return false;
}

void loop()
{
  lightValue = analogRead(LIGHT_PIN);
  //Invio a python il valore tramite seriale
  Serial.println("ard"+String(lightValue));
  
  switch_ = reciveFromPython();
  
  if(switch_ && !relayState){
   
    sendSignal("on");
    relayState = true;
    
  }
  
  else if(!switch_ && relayState){
    
    sendSignal("off");
    relayState = false;
    
  }
}
