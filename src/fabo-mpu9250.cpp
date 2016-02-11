#include "fabo-mpu9250.h"

bool FaBo9Axis::searchDevice()
{
  byte device_mpu9250 = 0x00;
  readI2c(MPU9250_SLAVE_ADDRESS, MPU9250_WHO_AM_I_REG, 1, &device_mpu9250);

  byte device_ak8963 = 0x00;
  readI2c(AK8963_SLAVE_ADDRESS, AK8963_DEVICE_ID_REG, 1, &device_ak8963);
  
  if(device_mpu9250 == MPU9250_DEVICE_NAME && device_ak8963 == AK8963_DEVICE_NAME){
    return true;
  } else{
    return false;
  }
}

void FaBo9Axis::powerOn()
{
  writeI2c(MPU9250_SLAVE_ADDRESS, MPU9250_POWER_MNG1_REG, 0x00);
  writeI2c(MPU9250_SLAVE_ADDRESS, MPU9250_POWER_MNG2_REG, 0x00);
}

void FaBo9Axis::reset()
{
  writeI2c(MPU9250_SLAVE_ADDRESS, MPU9250_POWER_MNG1_REG, 0x80);
}

void FaBo9Axis::configuration()
{
  byte accel_conf = MPU9250_ACCELL_OUTPUT_BAND_1_13K;
  writeI2c(MPU9250_SLAVE_ADDRESS, MPU9250_ACCEL_CONFIG2_REG, accel_conf);

  byte gyro_conf = MPU9250_FCHOICE_B_BAND_0;
  writeI2c(MPU9250_SLAVE_ADDRESS, MPU9250_GYRO_CONFIG_REG, gyro_conf);

  byte conf = MPU9250_EXT_SYNC_SET_DISABLE;
  conf |= MPU9250_DLPF_CFG_0;
  writeI2c(MPU9250_SLAVE_ADDRESS, MPU9250_CONFIGURATION_REG, conf);

  byte ak8963_ctrl = AK8963_BIT_16_OUTPUT;
  ak8963_ctrl |= AK8963_MODE_SINGLE;
  writeI2c(AK8963_SLAVE_ADDRESS, AK8963_CTRL1_REG, ak8963_ctrl);
}

void FaBo9Axis::readAccelXYZ(int *x, int *y, int *z)
{
  uint8_t length = 6;
  byte accel_buff[6];
  readI2c(MPU9250_SLAVE_ADDRESS, MPU9250_ACCEL_X_MSB_REG, length, accel_buff); 
  *x = (((int)accel_buff[0]) << 8) | accel_buff[1];   
  *y = (((int)accel_buff[2]) << 8) | accel_buff[3];
  *z = (((int)accel_buff[4]) << 8) | accel_buff[5];
}

void FaBo9Axis::readGyroXYZ(int *x, int *y, int *z)
{
  uint8_t length = 6;
  byte gyro_buff[6];
  readI2c(MPU9250_SLAVE_ADDRESS, MPU9250_GYRO_X_MSB_REG, length, gyro_buff); 
  *x = (((int)gyro_buff[0]) << 8) | gyro_buff[1];   
  *y = (((int)gyro_buff[2]) << 8) | gyro_buff[3];
  *z = (((int)gyro_buff[4]) << 8) | gyro_buff[5];
}

uint16_t FaBo9Axis::readTemperature()
{
  uint8_t length = 2;
  byte temp_buff[2];
  readI2c(MPU9250_SLAVE_ADDRESS, MPU9250_TEMP_MSB_REG, length, temp_buff); 
  return (((int)temp_buff[0]) << 8) | temp_buff[1];   
}

void FaBo9Axis::readMagnetXYZ(int *x, int *y, int *z)
{
  uint8_t length = 6;
  byte maget_buff[6];
  readI2c(AK8963_SLAVE_ADDRESS, AK8963_MANGET_X_LSB_REG, length, maget_buff); 
  *x = (((int)maget_buff[1]) << 8) | maget_buff[0];   
  *y = (((int)maget_buff[3]) << 8) | maget_buff[2];
  *z = (((int)maget_buff[5]) << 8) | maget_buff[4];
}

// I2Cへの書き込み
void FaBo9Axis::writeI2c(uint8_t address, byte register_addr, byte value) {
  Wire.begin();       // I2Cの開始
  Wire.beginTransmission(address);  
  Wire.write(register_addr);         
  Wire.write(value);                 
  Wire.endTransmission();        
}

// I2Cへの読み込み
void FaBo9Axis::readI2c(uint8_t address, byte register_addr, int num, byte buffer[]) {
  Wire.begin();       // I2Cの開始
  Wire.beginTransmission(address); 
  Wire.write(register_addr);           
  Wire.endTransmission();         

  Wire.beginTransmission(address); 
  Wire.requestFrom(address, num);   

  int i = 0;
  while(Wire.available())        
  { 
    buffer[i] = Wire.read();   
    i++;
  }
  Wire.endTransmission();         
}
