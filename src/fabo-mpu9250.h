#include "Arduino.h"
#include "Wire.h"

// Slave address
#define MPU9250_SLAVE_ADDRESS 0x68
#define AK8963_SLAVE_ADDRESS 0x0C

// Who am I (device id)
#define MPU9250_WHO_AM_I_REG 0x75
#define AK8963_DEVICE_ID_REG 0x00

// Power management
#define MPU9250_POWER_MNG1_REG 0x6B
#define MPU9250_POWER_MNG2_REG 0x6C

// Read accel
#define MPU9250_ACCEL_X_MSB_REG 0x3B
#define MPU9250_ACCEL_X_LSB_REG 0x3C
#define MPU9250_ACCEL_Y_MSB_REG 0x3D
#define MPU9250_ACCEL_Y_LSB_REG 0x3E
#define MPU9250_ACCEL_Z_MSB_REG 0x3F
#define MPU9250_ACCEL_Z_LSB_REG 0x40

// Read Temperature
#define MPU9250_TEMP_MSB_REG 0x41
#define MPU9250_TEMP_LSB_REG 0x42

// Read Gyroscope
#define MPU9250_GYRO_X_MSB_REG 0x43
#define MPU9250_GYRO_X_LSB_REG 0x44
#define MPU9250_GYRO_Y_MSB_REG 0x45
#define MPU9250_GYRO_Y_LSB_REG 0x46
#define MPU9250_GYRO_Z_MSB_REG 0x47
#define MPU9250_GYRO_Z_LSB_REG 0x48

// Read Magnetometer
#define AK8963_MANGET_X_LSB_REG 0x03
#define AK8963_MANGET_X_MSB_REG 0x04
#define AK8963_MANGET_Y_LSB_REG 0x05
#define AK8963_MANGET_Y_MSB_REG 0x06
#define AK8963_MANGET_Z_LSB_REG 0x07
#define AK8963_MANGET_Z_MSB_REG 0x08

// Configuration
#define MPU9250_CONFIGURATION_REG 0x1A
#define MPU9250_GYRO_CONFIG_REG 0x1B
#define MPU9250_ACCEL_CONFIG2_REG 0x1D
#define AK8963_CTRL1_REG 0x0A

// Device name
#define MPU9250_DEVICE_NAME 0x68
#define AK8963_DEVICE_NAME 0x48 

// Configuration
#define MPU9250_EXT_SYNC_SET_DISABLE 0b00000000
#define MPU9250_DLPF_CFG_0 0b000
#define MPU9250_DLPF_CFG_1 0b001
#define MPU9250_DLPF_CFG_2 0b010
#define MPU9250_DLPF_CFG_3 0b011
#define MPU9250_DLPF_CFG_4 0b100
#define MPU9250_DLPF_CFG_5 0b101
#define MPU9250_DLPF_CFG_6 0b110
#define MPU9250_DLPF_CFG_7 0b111

#define MPU9250_FCHOICE_B_BAND_0 0b00
#define MPU9250_FCHOICE_B_BAND_1 0b01
#define MPU9250_FCHOICE_B_BAND_3 0b11

#define MPU9250_ACCELL_OUTPUT_BAND_1_13K 0b0000
#define MPU9250_ACCELL_OUTPUT_BAND_460 0b1001
#define MPU9250_ACCELL_OUTPUT_BAND_92 0b1010
#define MPU9250_ACCELL_OUTPUT_BAND_41 0b1011
#define MPU9250_ACCELL_OUTPUT_BAND_20 0b1100
#define MPU9250_ACCELL_OUTPUT_BAND_10 0b1101
#define MPU9250_ACCELL_OUTPUT_BAND_5 0b1110

#define AK8963_BIT_16_OUTPUT 0b10000
#define AK8963_BIT_14_OUTPUT 0b00000

#define AK8963_MODE_POWER_DOWN 0b0000 
#define AK8963_MODE_SINGLE 0b0001 
#define AK8963_MODE_CONTINOUS1 0b0010
#define AK8963_MODE_CONTINOUS2 0b0110 
#define AK8963_MODE_EXTERNAL_TRIGGER 0b0100 
#define AK8963_MODE_SELF_TEST 0b1000 
#define AK8963_MODE_FUSE_ROM 0b1111

class FaBo9Axis
{
public:
  bool searchDevice(void);
  void configuration(void);
  void powerOn(void);
  void reset(void);
  void readAccelXYZ(int *x, int *y, int *z);
  void readGyroXYZ(int *x, int *y, int *z);
  uint16_t readTemperature();
  void readMagnetXYZ(int *x, int *y, int *z);
private:
  void readI2c(byte address, byte register_addr, int num, byte *buf);
  void writeI2c(byte address, byte register_addr, byte value);
};

