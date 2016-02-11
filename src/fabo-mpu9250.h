#include "Arduino.h"
#include "Wire.h"

#define ADXL345_SLAVE_ADDRESS (0x53)

#define ADXL345_DEVID_REG 0x00
#define ADXL345_THRESH_TAP_REG 0x1D
#define ADXL345_DUR_REG 0x22
#define ADXL345_LATENT_REG 0x23
#define ADXL345_WINDOW_REG 0x24
#define ADXL345_POWER_CTL_REG 0x2D
#define ADXL345_TAP_STATUS_REG 0x2B
#define ADXL345_TAP_AXES_REG 0x2A
#define ADXL345_INT_SOURCE_REG 0x30
#define ADXL345_DATA_FORMAT_REG 0x31

#define ADXL345_SELF_TEST_ON 0b10000000
#define ADXL345_SELF_TEST_OFF 0b00000000
#define ADXL345_SPI_ON 0b01000000
#define ADXL345_SPI_OFF 0b00000000
#define ADXL345_INT_INVERT_ON 0b00100000
#define ADXL345_INT_INVERT_OFF 0b00000000
#define ADXL345_FULL_RES_ON 0b00001000
#define ADXL345_FULL_RES_OFF 0b00000000
#define ADXL345_JUSTIFY_ON 0b00000100
#define ADXL345_JUSTIFY_OFF 0b00000000

#define ADXL345_RANGE_2G 0b00
#define ADXL345_RANGE_4G 0b01
#define ADXL345_RANGE_8G 0b10
#define ADXL345_RANGE_16G 0b11

#define ADXL345_AUTO_SLEEP_ON 0b00010000
#define ADXL345_AUTO_SLEEP_OFF 0b00000000
#define ADXL345_MEASURE_ON 0b00001000
#define ADXL345_MEASURE_OFF 0b00000000
#define ADXL345_SLEEP_ON 0b00000100
#define ADXL345_SLEEP_OFF 0b00000000

#define ADXL345_WAKEUP_8HZ 0b00
#define ADXL345_WAKEUP_4HZ 0b01
#define ADXL345_WAKEUP_2HZ 0b10
#define ADXL345_WAKEUP_1HZ 0b11

#define ADXL345_DEVICE 0xe5

class adxl345
{
public:
  bool searchDevice(void);
  void configuration(void);
  void powerOn(void);
  void readXYZ(int *x, int *y, int *z);
  byte readIntStatus();
  void enableTap();
  bool isDoubleTap(byte value);
  bool isSingleTap(byte value);
private:
  void readI2c(byte register_addr, int num, byte *buf);
  void writeI2c(byte register_addr, byte value);
};

extern adxl345 fabo3Axis;
