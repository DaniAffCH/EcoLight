#define LIGHT_PIN A0
#define yButton 8
#define nButton 9
unsigned int lightValue;
String x = "[";
String y = "[";
void setup() {
  Serial.begin(9600);
  pinMode(yButton, INPUT_PULLUP);
  pinMode(nButton, INPUT_PULLUP);
}

void loop() {
  lightValue = analogRead(LIGHT_PIN);
  if(Serial.read() == 'r'){
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    x = x+"]";
    y = y+"]";
    Serial.println(x);    Serial.println("");
    Serial.println(y);
  }
  
  if(digitalRead(yButton) == LOW){
    
    x = x+String(lightValue)+",";
    y = y+"1,";

    Serial.println(x);
    Serial.println(y);
    delay(1000);
  }
  
  if(digitalRead(nButton) == LOW){

    x = x+String(lightValue)+",";
    y = y+"0,";

    Serial.println(x);
    Serial.println(y);
    delay(1000);
  }
  
}
