/*
****************************************************************************
* Copyright (C) 2015 - 2016 Bosch Sensortec GmbH
*
* bma2x2_support.c
* Date: 2016/03/09
* Revision: 1.0.4 $
*
* Usage: Sensor Driver support file for  BMA2x2 sensor
*
****************************************************************************
* Disclaimer
*
* Common:
* Bosch Sensortec products are developed for the consumer goods industry.
* They may only be used within the parameters of the respective valid
* product data sheet.  Bosch Sensortec products are provided with the
* express understanding that there is no warranty of fitness for a
* particular purpose.They are not fit for use in life-sustaining,
* safety or security sensitive systems or any system or device
* that may lead to bodily harm or property damage if the system
* or device malfunctions. In addition,Bosch Sensortec products are
* not fit for use in products which interact with motor vehicle systems.
* The resale and or use of products are at the purchasers own risk and
* his own responsibility. The examination of fitness for the intended use
* is the sole responsibility of the Purchaser.
*
* The purchaser shall indemnify Bosch Sensortec from all third party
* claims, including any claims for incidental, or consequential damages,
* arising from any product use not covered by the parameters of
* the respective valid product data sheet or not approved by
* Bosch Sensortec and reimburse Bosch Sensortec for all costs in
* connection with such claims.
*
* The purchaser must monitor the market for the purchased products,
* particularly with regard to product safety and inform Bosch Sensortec
* without delay of all security relevant incidents.
*
* Engineering Samples are marked with an asterisk (*) or (e).
* Samples may vary from the valid technical specifications of the product
* series. They are therefore not intended or fit for resale to third
* parties or for use in end products. Their sole purpose is internal
* client testing. The testing of an engineering sample may in no way
* replace the testing of a product series. Bosch Sensortec assumes
* no liability for the use of engineering samples.
* By accepting the engineering samples, the Purchaser agrees to indemnify
* Bosch Sensortec from all claims arising from the use of engineering
* samples.
*
* Special:
* This software module (hereinafter called "Software") and any information
* on application-sheets (hereinafter called "Information") is provided
* free of charge for the sole purpose to support your application work.
* The Software and Information is subject to the following
* terms and conditions:
*
* The Software is specifically designed for the exclusive use for
* Bosch Sensortec products by personnel who have special experience
* and training. Do not use this Software if you do not have the
* proper experience or training.
*
* This Software package is provided `` as is `` and without any expressed
* or implied warranties,including without limitation, the implied warranties
* of merchantability and fitness for a particular purpose.
*
* Bosch Sensortec and their representatives and agents deny any liability
* for the functional impairment
* of this Software in terms of fitness, performance and safety.
* Bosch Sensortec and their representatives and agents shall not be liable
* for any direct or indirect damages or injury, except as
* otherwise stipulated in mandatory applicable law.
*
* The Information provided is believed to be accurate and reliable.
* Bosch Sensortec assumes no responsibility for the consequences of use
* of such Information nor for any infringement of patents or
* other rights of third parties which may result from its use.
* No license is granted by implication or otherwise under any patent or
* patent rights of Bosch. Specifications mentioned in the Information are
* subject to change without notice.
**************************************************************************/
/*---------------------------------------------------------------------------*/
/* Includes*/
/*---------------------------------------------------------------------------*/
#include "bma2x2.h"

/*----------------------------------------------------------------------------*
*   The following functions are used for reading and writing of
*   sensor data using I2C or SPI communication
*----------------------------------------------------------------------------*/
#ifdef BMA2x2_API
    /* \Brief: The function is used as I2C bus read
    *  \Return : Status of the I2C read
    *  \param dev_addr : The device address of the sensor
    *  \param reg_addr : Address of the first register,
    *               will data is going to be read
    *  \param reg_data : This data read from the sensor,
    *               which is hold in an array
    *  \param cnt : The no of byte of data to be read
    */
    s8 BMA2x2_I2C_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt);
    /* \Brief: The function is used as I2C bus write
    *  \Return : Status of the I2C write
    *  \param dev_addr : The device address of the sensor
    *  \param reg_addr : Address of the first register,
    *              will data is going to be written
    *  \param reg_data : It is a value hold in the array,
    *      will be used for write the value into the register
    *  \param cnt : The no of byte of data to be write
    */
    s8 BMA2x2_I2C_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt);
    /* \Brief: The function is used as SPI bus write
    * \Return : Status of the SPI write
    * \param dev_addr : The device address of the sensor
    * \param reg_addr : Address of the first register,
    *      will data is going to be written
    * \param reg_data : It is a value hold in the array,
    *  will be used for write the value into the register
    * \param cnt : The no of byte of data to be write
    */
    s8 BMA2x2_SPI_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt);
    /* \Brief: The function is used as SPI bus read
    * \Return : Status of the SPI read
    * \param dev_addr : The device address of the sensor
    * \param reg_addr : Address of the first register,
    *   will data is going to be read
    * \param reg_data : This data read from the sensor, which is hold in an array
    * \param cnt : The no of byte of data to be read */
    s8 BMA2x2_SPI_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt);
    /*
    * \Brief: SPI/I2C init routine
    */
    s8 I2C_routine(void);
    s8 SPI_routine(void);
#endif
/********************End of I2C/SPI function declarations*******************/
/*  Brief : The delay routine
 *  \param : delay in ms
 */
void BMA2x2_delay_msek(u32 msek);
/*!
 *  @brief This function is an example for delay
 *  @param : None
 *  @return : communication result
 */
s32 bma2x2_data_readout_template(void);
/*----------------------------------------------------------------------------*
*  struct bma2x2_t parameters can be accessed by using bma2x2
 *  bma2x2_t having the following parameters
 *  Bus write function pointer: BMA2x2_WR_FUNC_PTR
 *  Bus read function pointer: BMA2x2_RD_FUNC_PTR
 *  Burst read function pointer: BMA2x2_BRD_FUNC_PTR
 *  Delay function pointer: delay_msec
 *  I2C address: dev_addr
 *  Chip id of the sensor: chip_id
 *---------------------------------------------------------------------------*/
struct bma2x2_t bma2x2;
/*----------------------------------------------------------------------------*
*  V_BMA2x2RESOLUTION_u8R used for selecting the accelerometer resolution
 *  12 bit
 *  14 bit
 *  10 bit
*----------------------------------------------------------------------------*/
extern u8 V_BMA2x2RESOLUTION_u8R;
/* This function is an example for reading sensor data
 *  \param: None
 *  \return: communication result
 */
s32 bma2x2_data_readout_template(void)
{
    /*Local variables for reading accel x, y and z data*/
    s16 accel_x_s16, accel_y_s16, accel_z_s16 = BMA2x2_INIT_VALUE;

    /* bma2x2acc_data structure used to read accel xyz data*/
    struct bma2x2_accel_data sample_xyz;
    /* bma2x2acc_data_temp structure used to read
        accel xyz and temperature data*/
    struct bma2x2_accel_data_temp sample_xyzt;
    /* Local variable used to assign the bandwidth value*/
    u8 bw_value_u8 = BMA2x2_INIT_VALUE;
    /* Local variable used to set the bandwidth value*/
    u8 banwid = BMA2x2_INIT_VALUE;
    /* status of communication*/
    s32 com_rslt = ERROR;


    /*********************** START INITIALIZATION ************************
      * Based on the user need configure I2C or SPI interface.
      * It is example code to explain how to use the bma2x2 API*/
#ifdef BMA2x2_API
    I2C_routine();
    /*SPI_routine(); */
#endif
    /*--------------------------------------------------------------------------*
    *  This function used to assign the value/reference of
    *  the following parameters
    *  I2C address
    *  Bus Write
    *  Bus read
    *  Chip id
    *-------------------------------------------------------------------------*/
    com_rslt = bma2x2_init(&bma2x2);

    /*  For initialization it is required to set the mode of
     *  the sensor as "NORMAL"
     *  NORMAL mode is set from the register 0x11 and 0x12
     *  0x11 -> bit 5,6,7 -> set value as 0
     *  0x12 -> bit 5,6 -> set value as 0
     *  data acquisition/read/write is possible in this mode
     *  by using the below API able to set the power mode as NORMAL
     *  For the Normal/standby/Low power 2 mode Idle time
            of at least 2us(micro seconds)
     *  required for read/write operations*/
    /* Set the power mode as NORMAL*/
    com_rslt += bma2x2_set_power_mode(BMA2x2_MODE_NORMAL);
    /*  Note:
        * For the Suspend/Low power1 mode Idle time of
            at least 450us(micro seconds)
        * required for read/write operations*/

    /************************* END INITIALIZATION *************************/

    /*------------------------------------------------------------------------*
    ************************* START GET and SET FUNCTIONS DATA ****************
    *---------------------------------------------------------------------------*/
    /* This API used to Write the bandwidth of the sensor input
    value have to be given
    bandwidth is set from the register 0x10 bits from 1 to 4*/
    bw_value_u8 = 0x08;/* set bandwidth of 7.81Hz*/
    com_rslt += bma2x2_set_bw(bw_value_u8);

    /* This API used to read back the written value of bandwidth*/
    com_rslt += bma2x2_get_bw(&banwid);
    /*-----------------------------------------------------------------*
    ************************* END GET and SET FUNCTIONS ****************
    *-------------------------------------------------------------------*/
    /*------------------------------------------------------------------*
    ************************* START READ SENSOR DATA(X,Y and Z axis) ********
    *---------------------------------------------------------------------*/
    /* Read the accel X data*/
    com_rslt += bma2x2_read_accel_x(&accel_x_s16);
    /* Read the accel Y data*/
    com_rslt += bma2x2_read_accel_y(&accel_y_s16);
    /* Read the accel Z data*/
    com_rslt += bma2x2_read_accel_z(&accel_z_s16);

    /* accessing the bma2x2acc_data parameter by using sample_xyz*/
    /* Read the accel XYZ data*/
    com_rslt += bma2x2_read_accel_xyz(&sample_xyz);

    /* accessing the bma2x2acc_data_temp parameter by using sample_xyzt*/
    /* Read the accel XYZT data*/
    com_rslt += bma2x2_read_accel_xyzt(&sample_xyzt);

    /*--------------------------------------------------------------------*
    ************************* END READ SENSOR DATA(X,Y and Z axis) ************
    *-------------------------------------------------------------------------*/
    /*-----------------------------------------------------------------------*
    ************************* START DE-INITIALIZATION ***********************
    *-------------------------------------------------------------------------*/
    /*  For de-initialization it is required to set the mode of
     *  the sensor as "DEEP SUSPEND"
     *  DEEP SUSPEND mode is set from the register 0x11
     *  0x11 -> bit 5 -> set value as 1
     *  the device reaches the lowest power consumption only
     *  interface selection is kept alive
     *  No data acquisition is performed
     *  by using the below API able to set the power mode as DEEPSUSPEND*/
    /* Set the power mode as DEEPSUSPEND*/
    com_rslt += bma2x2_set_power_mode(BMA2x2_MODE_DEEP_SUSPEND);
    /*---------------------------------------------------------------------*
    ************************* END DE-INITIALIZATION **********************
    *---------------------------------------------------------------------*/
    return com_rslt;
}

#ifdef BMA2x2_API
/*--------------------------------------------------------------------------*
*   The following function is used to map the I2C bus read, write, delay and
*   device address with global structure bma2x2_t
*-------------------------------------------------------------------------*/
s8 I2C_routine(void)
{
    /*--------------------------------------------------------------------------*
     *  By using bma2x2 the following structure parameter can be accessed
     *  Bus write function pointer: BMA2x2_WR_FUNC_PTR
     *  Bus read function pointer: BMA2x2_RD_FUNC_PTR
     *  Delay function pointer: delay_msec
     *  I2C address: dev_addr
     *--------------------------------------------------------------------------*/
    bma2x2.bus_write = BMA2x2_I2C_bus_write;
    bma2x2.bus_read = BMA2x2_I2C_bus_read;
    bma2x2.delay_msec = BMA2x2_delay_msek;
    bma2x2.dev_addr = BMA2x2_I2C_ADDR2;

    return BMA2x2_INIT_VALUE;
}

/*---------------------------------------------------------------------------*
 * The following function is used to map the SPI bus read, write and delay
 * with global structure bma2x2_t
 *--------------------------------------------------------------------------*/
s8 SPI_routine(void)
{
    /*--------------------------------------------------------------------------*
     *  By using bma2x2 the following structure parameter can be accessed
     *  Bus write function pointer: BMA2x2_WR_FUNC_PTR
     *  Bus read function pointer: BMA2x2_RD_FUNC_PTR
     *  Delay function pointer: delay_msec
     *--------------------------------------------------------------------------*/

    bma2x2.bus_write = BMA2x2_SPI_bus_write;
    bma2x2.bus_read = BMA2x2_SPI_bus_read;
    bma2x2.delay_msec = BMA2x2_delay_msek;

    return BMA2x2_INIT_VALUE;
}

/************** I2C/SPI buffer length ******/
#define I2C_BUFFER_LEN 8
#define SPI_BUFFER_LEN 5
#define BMA2x2_BUS_READ_WRITE_ARRAY_INDEX   1
#define BMA2x2_SPI_BUS_WRITE_CONTROL_BYTE   0x7F
#define BMA2x2_SPI_BUS_READ_CONTROL_BYTE    0x80

/*-------------------------------------------------------------------*
*   This is a sample code for read and write the data by using I2C/SPI
*   Use either I2C or SPI based on your need
*
*-----------------------------------------------------------------------*/
/*  For configuring the I2C it is required to switch ON
 *  SDI, SDO and CLk and also select the device address
 * The following definition of I2C address is used for the following sensors
 * BMA255
 * BMA253
 * BMA355
 * BMA280
 * BMA282
 * BMA223
 * BMA254
 * BMA284
 * BMA250E
 * BMA222E

 #define BMA2x2_I2C_ADDR1         0x18
 #define BMA2x2_I2C_ADDR2         0x19

 * The following definition of I2C address is used for the following sensors
 * BMC150
 * BMC056
 * BMC156

 #define BMA2x2_I2C_ADDR3        0x10
 #define BMA2x2_I2C_ADDR4        0x11
 *************************************************************************/
/* \Brief: The function is used as I2C bus write
*  \Return : Status of the I2C write
*  \param dev_addr : The device address of the sensor
*  \param reg_addr : Address of the first register,
*              will data is going to be written
*  \param reg_data : It is a value hold in the array,
*      will be used for write the value into the register
*  \param cnt : The no of byte of data to be write
*/
s8 BMA2x2_I2C_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
    s32 iError = BMA2x2_INIT_VALUE;
    u8 array[I2C_BUFFER_LEN];
    u8 stringpos = BMA2x2_INIT_VALUE;

    array[BMA2x2_INIT_VALUE] = reg_addr;
    for (stringpos = BMA2x2_INIT_VALUE; stringpos < cnt; stringpos++)
    {
        array[stringpos + BMA2x2_BUS_READ_WRITE_ARRAY_INDEX] =
            *(reg_data + stringpos);
    }
    /*
    * Please take the below function as your reference for
    * write the data using I2C communication
    * "IERROR = I2C_WRITE_STRING(DEV_ADDR, ARRAY, CNT+1)"
    * add your I2C write function here
    * iError is an return value of I2C read function
    * Please select your valid return value
    * In the driver SUCCESS defined as 0
    * and FAILURE defined as -1
    * Note :
    * This is a full duplex operation,
    * The first read data is discarded, for that extra write operation
    * have to be initiated. For that cnt+1 operation
    * done in the I2C write string function
    * For more information please refer data sheet SPI communication:
    */
    return (s8)iError;
}

/*   \Brief: The function is used as I2C bus read
*    \Return : Status of the I2C read
*    \param dev_addr : The device address of the sensor
*    \param reg_addr : Address of the first register,
*            will data is going to be read
*    \param reg_data : This data read from the sensor,
*            which is hold in an array
*    \param cnt : The no of byte of data to be read
*/
s8 BMA2x2_I2C_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
    s32 iError = BMA2x2_INIT_VALUE;
    u8 array[I2C_BUFFER_LEN] = {BMA2x2_INIT_VALUE};
    u8 stringpos = BMA2x2_INIT_VALUE;

    array[BMA2x2_INIT_VALUE] = reg_addr;
    /* Please take the below function as your reference
     * for read the data using I2C communication
     * add your I2C rad function here.
     * "IERROR = I2C_WRITE_READ_STRING(DEV_ADDR, ARRAY, ARRAY, 1, CNT)"
     * iError is an return value of SPI write function
     * Please select your valid return value
     * In the driver SUCCESS defined as 0
     * and FAILURE defined as -1
     */
    for (stringpos = BMA2x2_INIT_VALUE; stringpos < cnt; stringpos++)
        *(reg_data + stringpos) = array[stringpos];
    return (s8)iError;
}

/*  \Brief: The function is used as SPI bus read
 *  \Return : Status of the SPI read
 *  \param dev_addr : The device address of the sensor
 *  \param reg_addr : Address of the first register,
 *          will data is going to be read
 *  \param reg_data : This data read from the sensor,
 *          which is hold in an array
 *  \param cnt : The no of byte of data to be read */
s8 BMA2x2_SPI_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
    s32 iError = BMA2x2_INIT_VALUE;
    u8 array[SPI_BUFFER_LEN] = {0xFF};
    u8 stringpos;
    /*  For the SPI mode only 7 bits of register addresses are used.
    The MSB of register address is declared the bit what functionality it is
    read/write (read as 1/write as 0)*/
    array[BMA2x2_INIT_VALUE] = reg_addr | BMA2x2_SPI_BUS_READ_CONTROL_BYTE;
    /*read routine is initiated register address is mask with 0x80*/
    /*
    * Please take the below function as your reference for
    * read the data using SPI communication
    * " IERROR = SPI_READ_WRITE_STRING(ARRAY, ARRAY, CNT+1)"
    * add your SPI read function here
    * iError is an return value of SPI read function
    * Please select your valid return value
    * In the driver SUCCESS defined as 0
    * and FAILURE defined as -1
    * Note :
    * This is a full duplex operation,
    * The first read data is discarded, for that extra write operation
    * have to be initiated. For that cnt+1 operation done in the SPI read
    * and write string function
    * For more information please refer data sheet SPI communication:
    */
    for (stringpos = BMA2x2_INIT_VALUE; stringpos < cnt; stringpos++)
    {
        *(reg_data + stringpos) = array[stringpos +
                                                  BMA2x2_BUS_READ_WRITE_ARRAY_INDEX];
    }
    return (s8)iError;
}

/*  \Brief: The function is used as SPI bus write
 *  \Return : Status of the SPI write
 *  \param dev_addr : The device address of the sensor
 *  \param reg_addr : Address of the first register,
*               will data is going to be written
 *  \param reg_data : It is a value hold in the array,
 *      will be used for write the value into the register
 *  \param cnt : The no of byte of data to be write
 */
s8 BMA2x2_SPI_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
    s32 iError = BMA2x2_INIT_VALUE;
    u8 array[SPI_BUFFER_LEN * 2];
    u8 stringpos = BMA2x2_INIT_VALUE;

    for (stringpos = BMA2x2_INIT_VALUE; stringpos < cnt; stringpos++)
    {
        /* the operation of (reg_addr++)&0x7F done:
        because it ensure the
        0 and 1 of the given value
        It is done only for 8bit operation*/
        array[stringpos * 2] = (reg_addr++) &
                               BMA2x2_SPI_BUS_WRITE_CONTROL_BYTE;
        array[stringpos * 2 + BMA2x2_BUS_READ_WRITE_ARRAY_INDEX] =
            *(reg_data + stringpos);
    }
    /* Please take the below function as your reference
     * for write the data using SPI communication
     * add your SPI write function here.
     * "IERROR = SPI_WRITE_STRING(ARRAY, CNT*2)"
     * iError is an return value of SPI write function
     * Please select your valid return value
     * In the driver SUCCESS defined as 0
     * and FAILURE defined as -1
     */
    return (s8)iError;
}

/*  Brief : The delay routine
 *  \param : delay in ms
*/
void BMA2x2_delay_msek(u32 msek)
{
    /*Here you can write your own delay routine*/
}
#endif
