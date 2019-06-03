#include <VirtualWire.h>

#define RELAY_PIN 2
#define BUTTON_PIN 3
#define RECIVER_PIN 5

boolean relayState = false;
boolean sysState = true;
boolean recoveryState;

byte message[VW_MAX_MESSAGE_LEN];
byte messageLen = VW_MAX_MESSAGE_LEN;

void setup(){
  Serial.begin(9600);
  
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  digitalWrite(RELAY_PIN, relayState);

  vw_set_rx_pin(RECIVER_PIN);
  vw_set_ptt_inverted(true);
  vw_setup(2000);
  vw_rx_start();
}

boolean changeStatus(boolean state){
  if(state) return false;
  else return true;
}

boolean compare(char* text) {
  for(int i = 0; i<messageLen; i++)
  {
    if(message[i] != text[i]) return false;
  }
 
  return true;
}

void loop(){
  
  if(digitalRead(BUTTON_PIN) == LOW){
    sysState = changeStatus(sysState);
    if(!sysState){
      recoveryState = relayState;
    }
    else{
      relayState = recoveryState;
      digitalWrite(RELAY_PIN, relayState);
    }
    delay(700);
  }
  
  if(sysState){
    if(vw_get_message(message, &messageLen)){
      //sistema acceso e ricezione 433Mhz
      if(compare("on") && !relayState){
      
        relayState = true;
        digitalWrite(RELAY_PIN, relayState);
        delay(1000);
      
      }
    
      else if(compare("off") && relayState){
      
        relayState = false;
        digitalWrite(RELAY_PIN, relayState);
        delay(1000);
      
      }
    }
  }
  
  else{
    //Il sistema è spento
    if(vw_get_message(message, &messageLen)){
      if(compare("on")) recoveryState = true;
      else if(compare("off")) recoveryState = false;
    }
    relayState = false;
    digitalWrite(RELAY_PIN, relayState);  
  }
}
