#define RELAY_PIN 2
#define LIGHT_PIN A0
#define BUTTON_PIN 3

boolean relayState = false;
boolean sysState = true;

unsigned int lightValue;
unsigned int valueOfSwitch = 520;

void setup(){
  Serial.begin(9600);
  
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  digitalWrite(RELAY_PIN, relayState);
}

boolean changeStatus(boolean state){
  if(state) return false;
  else return true;
}

void loop(){
  
  if(digitalRead(BUTTON_PIN) == LOW){
    sysState = changeStatus(sysState);
    delay(700);
  }
  
  if(sysState){
    //controllo per switch
    lightValue = analogRead(LIGHT_PIN);
  
    if(lightValue > valueOfSwitch && !relayState){
    
      relayState = true;
      digitalWrite(RELAY_PIN, relayState);
      delay(1000);
    
    }
  
    else if(lightValue < valueOfSwitch && relayState){
    
      relayState = false;
      digitalWrite(RELAY_PIN, relayState);
      delay(1000);
    
    }
  }
  else{
    //Il sistema è spento
    relayState = false;
    digitalWrite(RELAY_PIN, relayState);
    
  }
}
