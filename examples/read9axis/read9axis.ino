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
  int ax, ay, az;
  int gx, gy, gz;
  int mx, my, mz;
  uint16_t temp;
  
  fabo9axis.readAccelXYZ(&ax, &ay, &az);
  fabo9axis.readGyroXYZ(&gx, &gy, &gz);
  fabo9axis.readMagnetXYZ(&mx, &my, &mz);
  temp = fabo9axis.readTemperature();

  delay(1000);
}
