#include "fabo-mpu9250.h"
#include "Wire.h"

FaBo9Axis fabo9axis;

void setup() {
  // デバイス初期化
  Serial.println("Checking I2C device...");
  if (fabo9axis.searchDevice()) {
    Serial.println("I am MPU9250");
    fabo9axis.configuration();
  } else {
    Serial.println("device error");
    while(1);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
