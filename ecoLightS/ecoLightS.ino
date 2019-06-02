//#include <RH_ASK.h>
//#include <SR04.h>
//#include <SPI.h>
//
//#define TRIG_PIN 9
//#define ECHO_PIN 10
//
//SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
//RH_ASK driverRFS;
//
//char distance;
//
//void setup() {
//  Serial.begin(9600);
//}
//
//void loop() {
//  //distance=sr04.Distance();
//  const char *msg = "Hello World!";
//  driverRFS.send((uint8_t *) msg, strlen(msg));
//  driverRFS.waitPacketSent();
//  delay(1000);
//}

#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;

void setup()
{
    Serial.begin(9600);    // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    const char *msg = "Hello World!";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    delay(1000);
}
