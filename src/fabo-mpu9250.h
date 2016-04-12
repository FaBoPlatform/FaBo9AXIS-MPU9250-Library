/**
 * @file  fabo-mpu9250.h
 * @brief fabo libtary of mpu9250
 * @author Akira Sasaki
 * @date 2,10, 2016
 */

#include "Arduino.h"
#include "Wire.h"

/** SLAVE_ADDRESS MPU9250 Register */
#define MPU9250_SLAVE_ADDRESS 0x68
/** SLAVE_ADDRESS AK8963 Register */
#define AK8963_SLAVE_ADDRESS 0x0C

/** Who_am_i MPU9250 register */
#define MPU9250_WHO_AM_I_REG 0x75
/** Who_am_i AK8963 register */
#define AK8963_WHO_AM_I_REG 0x00

/** Device name MPU9250 */
#define MPU9250_DEVICE_NAME 0x71
/** Device name AK8963 */
#define AK8963_DEVICE_NAME 0x48

/** INT PIN CFG */
#define MPU9250_INT_PIN_CFG 0x37

/** Power management1 register */
#define MPU9250_POWER_MNG1_REG 0x6B
/** Power management2 register */
#define MPU9250_POWER_MNG2_REG 0x6C

/** Read accel X MSB register */
#define MPU9250_ACCEL_X_MSB_REG 0x3B
/** Read accel X LSB register */
#define MPU9250_ACCEL_X_LSB_REG 0x3C
/** Read accel Y MSB register */
#define MPU9250_ACCEL_Y_MSB_REG 0x3D
/** Read accel Y LSB register */
#define MPU9250_ACCEL_Y_LSB_REG 0x3E
/** Read accel Z MSB register */
#define MPU9250_ACCEL_Z_MSB_REG 0x3F
/** Read accel Z LSB register */
#define MPU9250_ACCEL_Z_LSB_REG 0x40

/** Read Temperature MSB register */
#define MPU9250_TEMP_MSB_REG 0x41
/** Read Temperature LSB register */
#define MPU9250_TEMP_LSB_REG 0x42

/** Read Gyroscope X MSB register */
#define MPU9250_GYRO_X_MSB_REG 0x43
/** Read Gyroscope X LSB register */
#define MPU9250_GYRO_X_LSB_REG 0x44
/** Read Gyroscope Y MSB register */
#define MPU9250_GYRO_Y_MSB_REG 0x45
/** Read Gyroscope Y MSB register */
#define MPU9250_GYRO_Y_LSB_REG 0x46
/** Read Gyroscope Z MSB register */
#define MPU9250_GYRO_Z_MSB_REG 0x47
/** Read Gyroscope Z MSB register */
#define MPU9250_GYRO_Z_LSB_REG 0x48

/** Read Magnetometer X LSB register */
#define AK8963_MANGET_X_LSB_REG 0x03
/** Read Magnetometer X MSB register */
#define AK8963_MANGET_X_MSB_REG 0x04
/** Read Magnetometer Y LSB register */
#define AK8963_MANGET_Y_LSB_REG 0x05
/** Read Magnetometer Y MSB register */
#define AK8963_MANGET_Y_MSB_REG 0x06
/** Read Magnetometer Z LSB register */
#define AK8963_MANGET_Z_LSB_REG 0x07
/** Read Magnetometer Z MSB register */
#define AK8963_MANGET_Z_MSB_REG 0x08

/** MPU9250 Config register */
#define MPU9250_CONFIGURATION_REG 0x1A
/** MPU9250 Gyro Config register */
#define MPU9250_GYRO_CONFIG_REG 0x1B
/** MPU9250 accel Config register */
#define MPU9250_ACCEL_CONFIG2_REG 0x1D
/** AK8963 Control 1 register */
#define AK8963_CTRL1_REG 0x0A

/** MPU9250 Config EXT_SYNC_SET Disable */
#define MPU9250_EXT_SYNC_SET_DISABLE 0b00000000
/** MPU9250 Config DLPF_CFG 0 */
#define MPU9250_DLPF_CFG_0 0b000
/** MPU9250 Config DLPF_CFG 1 */
#define MPU9250_DLPF_CFG_1 0b001
/** MPU9250 Config DLPF_CFG 2 */
#define MPU9250_DLPF_CFG_2 0b010
/** MPU9250 Config DLPF_CFG 3 */
#define MPU9250_DLPF_CFG_3 0b011
/** MPU9250 Config DLPF_CFG 4 */
#define MPU9250_DLPF_CFG_4 0b100
/** MPU9250 Config DLPF_CFG 5 */
#define MPU9250_DLPF_CFG_5 0b101
/** MPU9250 Config DLPF_CFG 6 */
#define MPU9250_DLPF_CFG_6 0b110
/** MPU9250 Config DLPF_CFG 7 */
#define MPU9250_DLPF_CFG_7 0b111

/** MPU9250 Config FCHOICE_B Band 0 */
#define MPU9250_FCHOICE_B_BAND_0 0b00
/** MPU9250 Config FCHOICE_B Band 1 */
#define MPU9250_FCHOICE_B_BAND_1 0b01
/** MPU9250 Config FCHOICE_B Band 3 */
#define MPU9250_FCHOICE_B_BAND_3 0b11

/** MPU9250 Config Accell Output Bandwidths 1.13k */
#define MPU9250_ACCELL_OUTPUT_BAND_1_13K 0b0000
/** MPU9250 Config Accell Output Bandwidths 460 */
#define MPU9250_ACCELL_OUTPUT_BAND_460 0b1001
/** MPU9250 Config Accell Output Bandwidths 92 */
#define MPU9250_ACCELL_OUTPUT_BAND_92 0b1010
/** MPU9250 Config Accell Output Bandwidths 41 */
#define MPU9250_ACCELL_OUTPUT_BAND_41 0b1011
/** MPU9250 Config Accell Output Bandwidths 20 */
#define MPU9250_ACCELL_OUTPUT_BAND_20 0b1100
/** MPU9250 Config Accell Output Bandwidths 10 */
#define MPU9250_ACCELL_OUTPUT_BAND_10 0b1101
/** MPU9250 Config Accell Output Bandwidths 5 */
#define MPU9250_ACCELL_OUTPUT_BAND_5 0b1110

/** AK8963 16bit OUTPUT Mode */
#define AK8963_BIT_16_OUTPUT 0b10000
/** AK8963 14bit OUTPUT Mode */
#define AK8963_BIT_14_OUTPUT 0b00000

/** AK8963 Control1 Power down Mode */
#define AK8963_MODE_POWER_DOWN 0b0000
/** AK8963 Control1 Single measurement Mode */
#define AK8963_MODE_SINGLE 0b0001
/** AK8963 Control1 Continuous measurement Mode 1 */
#define AK8963_MODE_CONTINOUS1 0b0010
/** AK8963 Control1 Continuous measurement Mode 2 */
#define AK8963_MODE_CONTINOUS2 0b0110
/** AK8963 Control1 External trigger measurement Mode */
#define AK8963_MODE_EXTERNAL_TRIGGER 0b0100
/** AK8963 Control1 Self-test Mode */
#define AK8963_MODE_SELF_TEST 0b1000
/** AK8963 Control1 Fuse ROM access Mode */
#define AK8963_MODE_FUSE_ROM 0b1111

/**
 * @class FaBo9Axis
 * @brief mpu9250 Control
 */
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
  void writeI2c(byte address, byte register_addr, byte value);
  void readI2c(int address, byte register_addr, int num, byte *buf);
};
