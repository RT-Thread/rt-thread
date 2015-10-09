/*
 * File      : mpu6050.c
 *
 */
#include <string.h>

#include <rtthread.h>

#include "mpu6050.h"
#include "fsl_i2c_hal.h"
#include "fsl_i2c_master_driver.h"
#include "board.h"

static uint32_t s_instance;

int32_t ga_accrange[][2] = { 
  { -2, 2},
  { -4, 4},
  { -8, 8},
  { -16, 16}
};

int32_t ga_gyrorange[][2] = {
  {-250, 250},
  {-500, 500},
  {-500, 1000},
  {-2000, 2000}
};

static uint8_t readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data, uint16_t timeout) 
{
  i2c_status_t ret;
  I2C_Type * baseAddr = g_i2cBase[s_instance];
  ret = I2C_HAL_MasterReceiveDataPolling(baseAddr, devAddr, (const uint8_t * )&regAddr, 1, data, length);
  if (ret == kStatus_I2C_Success)
  {
    return length;
  } else {
    return 0;
  }  
}

static bool writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data)
{
  I2C_Type * baseAddr = g_i2cBase[s_instance];
  I2C_HAL_MasterSendDataPolling(baseAddr, (uint16_t)devAddr, (const uint8_t * )&regAddr, 1, (const uint8_t *)data, 1);
  return true;
}

static int8_t readByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint16_t timeout)
{
  i2c_status_t ret;
  I2C_Type * baseAddr = g_i2cBase[s_instance];
  ret = I2C_HAL_MasterReceiveDataPolling(baseAddr, devAddr, (const uint8_t * )&regAddr, 1, data, 1);
  if (ret == kStatus_I2C_Success)
  {
    return 1;
  } else {
    return 0;
  }
}

static int8_t mpu6050_readbits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data, uint16_t timeout)
{
    // 01101001 read byte
    // 76543210 bit numbers
    //    xxx   args: bitStart=4, length=3
    //    010   masked
    //   -> 010 shifted
    uint8_t count, b;
    if ((count = readByte(devAddr, regAddr, &b, timeout)) != 0) {
        uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
        b &= mask;
        b >>= (bitStart - length + 1);
        *data = b;
    }
    return count;
}

static bool mpu6050_writebits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data)
{
    //      010 value to write
    // 76543210 bit numbers
    //    xxx   args: bitStart=4, length=3
    // 00011100 mask byte
    // 10101111 original value (sample)
    // 10100011 original & ~mask
    // 10101011 masked | value
    uint8_t b;
    if (readByte(devAddr, regAddr, &b, -1) != 0) {
        uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
        data <<= (bitStart - length + 1); // shift data into correct position
        data &= mask; // zero all non-important bits in data
        b &= ~(mask); // zero all important bits in existing byte
        b |= data; // combine data with existing byte
        return writeByte(devAddr, regAddr, b);
    } else {
        return false;
    }
}

static void setClockSource(uint8_t source)
{
   mpu6050_writebits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, source);
}

static void setFullScaleGyroRange(uint8_t range)
{
  mpu6050_writebits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, range);
}

static void setFullScaleAccelRange(uint8_t range)
{
  mpu6050_writebits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, range);
}

static void  setSleepEnabled(bool enabled)
{
  mpu6050_writebits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, 1, enabled);
}

static uint8_t getDeviceID() {
    uint8_t buffer = 0; 
    mpu6050_readbits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_WHO_AM_I, MPU6050_WHO_AM_I_BIT, MPU6050_WHO_AM_I_LENGTH, &buffer, 0);
    return buffer;
}

void mpu6050_init(uint32_t i2c_instance)
{
   s_instance = i2c_instance;
   mpu6050_reset();
   setClockSource(MPU6050_CLOCK_INTERNAL);
   setFullScaleGyroRange(MPU6050_GYRO_FS_250);
   setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
   setSleepEnabled(false);
}

bool mpu6050_testConnection()
{
  //0b110100
    if( 0x34 == getDeviceID())
    {
       return true;
    }
    return false;
}
/*
 * <pre>
 * AFS_SEL | Full Scale Range | LSB Sensitivity
 * --------+------------------+----------------
 * 0       | +/- 2g           | 8192 LSB/mg
 * 1       | +/- 4g           | 4096 LSB/mg
 * 2       | +/- 8g           | 2048 LSB/mg
 * 3       | +/- 16g          | 1024 LSB/mg
 * </pre>
*/
void mpu6050_getAcc(int16_t* x, int16_t* y, int16_t* z)
{
  uint8_t buffer[6];
  memset(buffer, 0, sizeof(buffer));
  readBytes(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_ACCEL_XOUT_H, 6, buffer, 0);
  *x = (((int16_t)buffer[0]) << 8) | buffer[1];
  *y = (((int16_t)buffer[2]) << 8) | buffer[3];
  *z = (((int16_t)buffer[4]) << 8) | buffer[5];
}

int16_t mpu6050_getTemperature() 
{
    uint8_t buffer[2];
    int16_t temp;
    memset(buffer, 0, sizeof(buffer));
    readBytes(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_TEMP_OUT_H, 1, buffer, 0);
    temp = (((int16_t)buffer[0]) << 8) | buffer[1];
    temp = 35 + temp / 340;
    return temp;
}

/*
 * Each 16-bit gyroscope measurement has a full scale defined in FS_SEL
 * (Register 27). For each full scale setting, the gyroscopes' sensitivity per
 * LSB in GYRO_xOUT is shown in the table below:
 *
 * <pre>
 * FS_SEL | Full Scale Range   | LSB Sensitivity
 * -------+--------------------+----------------
 * 0      | +/- 250 degrees/s  | 131 LSB/deg/s
 * 1      | +/- 500 degrees/s  | 65.5 LSB/deg/s
 * 2      | +/- 1000 degrees/s | 32.8 LSB/deg/s
 * 3      | +/- 2000 degrees/s | 16.4 LSB/deg/s
 * </pre>
*/
void mpu6050_getRotation(int16_t* x, int16_t* y, int16_t* z)
{
    uint8_t buffer[6];
    memset(buffer, 0, sizeof(buffer));
    readBytes(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_GYRO_XOUT_H, 6, buffer, 0);
    *x = (((int16_t)buffer[0]) << 8) | buffer[1];
    *y = (((int16_t)buffer[2]) << 8) | buffer[3];
    *z = (((int16_t)buffer[4]) << 8) | buffer[5];
}

/*
 * <pre>
 * 0 = +/- 250 degrees/sec
 * 1 = +/- 500 degrees/sec
 * 2 = +/- 1000 degrees/sec
 * 3 = +/- 2000 degrees/sec
 * </pre>
*/
uint8_t mpu6050_getFullScaleGyroRange()
{
    uint8_t buffer = 0;
    mpu6050_readbits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, &buffer, 0);
    return buffer;
}

void mpu6050_setFullScaleGyroRange(uint8_t range)
{
    mpu6050_writebits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, range);
}

/*
* <pre>
 * 0 = +/- 2g
 * 1 = +/- 4g
 * 2 = +/- 8g
 * 3 = +/- 16g
 * </pre>
*/
uint8_t mpu6050_getFullScaleAccelRange()
{
    uint8_t buffer = 0;
    mpu6050_readbits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, &buffer, 0);
    return buffer;
}

void mpu6050_setFullScaleAccelRange(uint8_t range)
{
    mpu6050_writebits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, range);
}

void mpu_6050_setTempSensorEnabled(bool enabled)
{
    // 1 is actually disabled here
    mpu6050_writebits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_TEMP_DIS_BIT, 1, !enabled);
}

void mpu6050_reset()
{
  mpu6050_writebits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_DEVICE_RESET_BIT, 1, true);
  rt_thread_delay(RT_TICK_PER_SECOND*0.1);
  mpu6050_writebits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_DEVICE_RESET_BIT, 1, false);
}




