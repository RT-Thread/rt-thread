/** \mainpage
*
****************************************************************************
* Copyright (C) 2015 - 2016 Bosch Sensortec GmbH
*
* File : bma2x2.h
*
* Date : 2016/11/14
*
* Revision : 2.0.7 $
*
* Usage: Sensor Driver file for BMA2x2 sensor
*
****************************************************************************
* \section Disclaimer
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
/*! \file bma2x2.h
    \brief BMA2x2 Sensor Driver Support Header File */
#ifndef __BMA2x2_H__
#define __BMA2x2_H__
/****************************************************************/
/**\name    DATA TYPES INCLUDES     */
/************************************************************/
/*!
* @brief The following definition uses for define the data types
*
* @note While porting the API please consider the following
* @note Please check the version of C standard
* @note Are you using Linux platform
*/

/*!
* @brief For the Linux platform support
* Please use the types.h for your data types definitions
*/
#ifdef  __KERNEL__

    #include <linux/types.h>
    /* singed integer type*/
    typedef int8_t s8;/**< used for signed 8bit */
    typedef int16_t s16;/**< used for signed 16bit */
    typedef int32_t s32;/**< used for signed 32bit */
    typedef int64_t s64;/**< used for signed 64bit */

    typedef u_int8_t u8;/**< used for unsigned 8bit */
    typedef u_int16_t u16;/**< used for unsigned 16bit */
    typedef u_int32_t u32;/**< used for unsigned 32bit */
    typedef u_int64_t u64;/**< used for unsigned 64bit */



#else /* ! __KERNEL__ */
    /**********************************************************
    * These definition uses for define the C
    * standard version data types
    ***********************************************************/
    #if !defined(__STDC_VERSION__)

        /************************************************
        * compiler is C11 C standard
        ************************************************/
        #if (__STDC_VERSION__ == 201112L)

            /************************************************/
            #include <stdint.h>
            /************************************************/

            /*unsigned integer types*/
            typedef uint8_t u8;/**< used for unsigned 8bit */
            typedef uint16_t u16;/**< used for unsigned 16bit */
            typedef uint32_t u32;/**< used for unsigned 32bit */
            typedef uint64_t u64;/**< used for unsigned 64bit */

            /*signed integer types*/
            typedef int8_t s8;/**< used for signed 8bit */
            typedef int16_t s16;/**< used for signed 16bit */
            typedef int32_t s32;/**< used for signed 32bit */
            typedef int64_t s64;/**< used for signed 64bit */
            /************************************************
            * compiler is C99 C standard
            ************************************************/

        #elif (__STDC_VERSION__ == 199901L)

            /* stdint.h is a C99 supported c library.
            which is used to fixed the integer size*/
            /************************************************/
            #include <stdint.h>
            /************************************************/

            /*unsigned integer types*/
            typedef uint8_t u8;/**< used for unsigned 8bit */
            typedef uint16_t u16;/**< used for unsigned 16bit */
            typedef uint32_t u32;/**< used for unsigned 32bit */
            typedef uint64_t u64;/**< used for unsigned 64bit */

            /*signed integer types*/
            typedef int8_t s8;/**< used for signed 8bit */
            typedef int16_t s16;/**< used for signed 16bit */
            typedef int32_t s32;/**< used for signed 32bit */
            typedef int64_t s64;/**< used for signed 64bit */
            /************************************************
            * compiler is C89 or other C standard
            ************************************************/

        #else /*  !defined(__STDC_VERSION__) */
            /*!
            * @brief By default it is defined as 32 bit machine configuration
            *   define your data types based on your
            *   machine/compiler/controller configuration
            */
            #define  MACHINE_32_BIT

            /*! @brief
            *  If your machine support 16 bit
            *  define the MACHINE_16_BIT
            */
            #ifdef MACHINE_16_BIT
                #include <limits.h>
                /*signed integer types*/
                typedef signed char  s8;/**< used for signed 8bit */
                typedef signed short int s16;/**< used for signed 16bit */
                typedef signed long int s32;/**< used for signed 32bit */

                #if defined(LONG_MAX) && LONG_MAX == 0x7fffffffffffffffL
                    typedef long int s64;/**< used for signed 64bit */
                    typedef unsigned long int u64;/**< used for unsigned 64bit */
                #elif defined(LLONG_MAX) && (LLONG_MAX == 0x7fffffffffffffffLL)
                    typedef long long int s64;/**< used for signed 64bit */
                    typedef unsigned long long int u64;/**< used for unsigned 64bit */
                #else
                    #warning Either the correct data type for signed 64 bit integer \
                    could not be found, or 64 bit integers are not supported in your environment.
                    #warning If 64 bit integers are supported on your platform, \
                    please set s64 manually.
                #endif

                /*unsigned integer types*/
                typedef unsigned char u8;/**< used for unsigned 8bit */
                typedef unsigned short int u16;/**< used for unsigned 16bit */
                typedef unsigned long int u32;/**< used for unsigned 32bit */

                /* If your machine support 32 bit
                define the MACHINE_32_BIT*/
            #elif defined MACHINE_32_BIT
                /*signed integer types*/
                typedef signed char  s8;/**< used for signed 8bit */
                typedef signed short int s16;/**< used for signed 16bit */
                typedef signed int s32;/**< used for signed 32bit */
                typedef signed long long int s64;/**< used for signed 64bit */

                /*unsigned integer types*/
                typedef unsigned char u8;/**< used for unsigned 8bit */
                typedef unsigned short int u16;/**< used for unsigned 16bit */
                typedef unsigned int u32;/**< used for unsigned 32bit */
                typedef unsigned long long int u64;/**< used for unsigned 64bit */

                /* If your machine support 64 bit
                define the MACHINE_64_BIT*/
            #elif defined MACHINE_64_BIT
                /*signed integer types*/
                typedef signed char  s8;/**< used for signed 8bit */
                typedef signed short int s16;/**< used for signed 16bit */
                typedef signed int s32;/**< used for signed 32bit */
                typedef signed long int s64;/**< used for signed 64bit */

                /*unsigned integer types*/
                typedef unsigned char u8;/**< used for unsigned 8bit */
                typedef unsigned short int u16;/**< used for unsigned 16bit */
                typedef unsigned int u32;/**< used for unsigned 32bit */
                typedef unsigned long int u64;/**< used for unsigned 64bit */

            #else
                #warning The data types defined above which not supported \
                define the data types manually
            #endif
        #endif

        /*** This else will execute for the compilers
        *  which are not supported the C standards
        *  Like C89/C99/C11***/
    #else
        /*!
        * @brief By default it is defined as 32 bit machine configuration
        *   define your data types based on your
        *   machine/compiler/controller configuration
        */
        #define  MACHINE_32_BIT

        /* If your machine support 16 bit
        define the MACHINE_16_BIT*/
        #ifdef MACHINE_16_BIT
            #include <limits.h>
            /*signed integer types*/
            typedef signed char  s8;/**< used for signed 8bit */
            typedef signed short int s16;/**< used for signed 16bit */
            typedef signed long int s32;/**< used for signed 32bit */

            #if defined(LONG_MAX) && LONG_MAX == 0x7fffffffffffffffL
                typedef long int s64;/**< used for signed 64bit */
                typedef unsigned long int u64;/**< used for unsigned 64bit */
            #elif defined(LLONG_MAX) && (LLONG_MAX == 0x7fffffffffffffffLL)
                typedef long long int s64;/**< used for signed 64bit */
                typedef unsigned long long int u64;/**< used for unsigned 64bit */
            #else
                #warning Either the correct data type for signed 64 bit integer \
                could not be found, or 64 bit integers are not supported in your environment.
                #warning If 64 bit integers are supported on your platform, \
                please set s64 manually.
            #endif

            /*unsigned integer types*/
            typedef unsigned char u8;/**< used for unsigned 8bit */
            typedef unsigned short int u16;/**< used for unsigned 16bit */
            typedef unsigned long int u32;/**< used for unsigned 32bit */

            /*! @brief If your machine support 32 bit
            define the MACHINE_32_BIT*/
        #elif defined MACHINE_32_BIT
            /*signed integer types*/
            typedef signed char  s8;/**< used for signed 8bit */
            typedef signed short int s16;/**< used for signed 16bit */
            typedef signed int s32;/**< used for signed 32bit */
            typedef signed long long int s64;/**< used for signed 64bit */

            /*unsigned integer types*/
            typedef unsigned char u8;/**< used for unsigned 8bit */
            typedef unsigned short int u16;/**< used for unsigned 16bit */
            typedef unsigned int u32;/**< used for unsigned 32bit */
            typedef unsigned long long int u64;/**< used for unsigned 64bit */

            /* If your machine support 64 bit
            define the MACHINE_64_BIT*/
        #elif defined MACHINE_64_BIT
            /*signed integer types*/
            typedef signed char  s8;/**< used for signed 8bit */
            typedef signed short int s16;/**< used for signed 16bit */
            typedef signed int s32;/**< used for signed 32bit */
            typedef signed long int s64;/**< used for signed 64bit */

            /*unsigned integer types*/
            typedef unsigned char u8;/**< used for unsigned 8bit */
            typedef unsigned short int u16;/**< used for unsigned 16bit */
            typedef unsigned int u32;/**< used for unsigned 32bit */
            typedef unsigned long int u64;/**< used for unsigned 64bit */

        #else
            #warning The data types defined above which not supported \
            define the data types manually
        #endif
    #endif
#endif

/***************************************************************/
/**\name    BUS READ AND WRITE FUNCTION POINTERS        */
/***************************************************************/
/*!
* @brief Define the calling convention of YOUR bus communication routine.
* @note This includes types of parameters.
* This example shows the configuration for an SPI bus link.

* If your communication function looks like this:

* write_my_bus_xy(u8 device_addr,
* u8 register_addr, u8 * data, u8 length);

* The BMA2x2_WR_FUNC_PTR would equal:

* BMA2x2_WR_FUNC_PTR char
* (* bus_write)(u8, u8, u8 *, u8)

* Parameters can be mixed as needed refer to
* the \ref BMA2x2_BUS_WRITE_FUNC  macro.
*/
#define BMA2x2_WR_FUNC_PTR s8(*bus_write)\
(u8, u8, u8 *, u8)

/*!
* @brief link macro between API function calls and bus write function
* @note The bus write function can change since
* this is a system dependant issue.

* If the bus_write parameter calling order is like:
* reg_addr, reg_data, wr_len it would be as it is here.

* If the parameters are differently ordered or your communication function
* like I2C need to know the device address,
* you can change this macro accordingly.


* define BMA2x2_BUS_WRITE_FUNC(dev_addr, reg_addr, reg_data, wr_len)\
* bus_write(dev_addr, reg_addr, reg_data, wr_len)

* This macro lets all API functions call YOUR communication routine in
* a way that equals your definition in the
* ref BMA2x2_WR_FUNC_PTR definition.

*/
#define BMA2x2_BUS_WRITE_FUNC(dev_addr, reg_addr, reg_data, wr_len)\
bus_write(dev_addr, reg_addr, reg_data, wr_len)


/*!
* @brief Define the calling convention of YOUR bus communication routine.
* @note This includes types of parameters. This example
*shows the configuration for an SPI bus link.

*If your communication function looks like this:

*read_my_bus_xy(u8 device_addr,
*u8 register_addr, u8* data, u8 length);

*The BMA2x2_RD_FUNC_PTR would equal:

*BMA2x2_RD_FUNC_PTR s8
*(* bus_read)(u8, u8, u8*, u8)

*Parameters can be mixed as needed refer to the
 ref BMA2x2_BUS_READ_FUNC  macro.
*/

#define BMA2x2_SPI_RD_MASK 0x80
/* for spi read transactions on SPI the MSB has to be set */
#define BMA2x2_RD_FUNC_PTR s8(*bus_read)\
(u8, u8, u8 *, u8)
#define BMA2x2_BRD_FUNC_PTR s8(*burst_read)\
(u8, u8, u8 *, u32)

/*!
* @brief link macro between API function calls and bus read function
* @note The bus write function can change since
* this is a system dependant issue.

* If the bus_read parameter calling order is like:
* reg_addr, reg_data, wr_len it would be as it is here.

*  If the parameters are differently ordered or your
*  communication function like I2C need to know the device address,
*  you can change this macro accordingly.


*  define BMA2x2_BUS_READ_FUNC(dev_addr, reg_addr, reg_data, wr_len)\
* bus_read(dev_addr, reg_addr, reg_data, wr_len)

* This macro lets all API functions call YOUR
* communication routine in a way that equals your definition in the
* ref BMA2x2_WR_FUNC_PTR definition.

* @note: this macro also includes the "MSB='1'" for reading BMA2x2 addresses.
*/



#define BMA2x2_BUS_READ_FUNC(dev_addr, reg_addr, reg_data, r_len)\
bus_read(dev_addr, reg_addr, reg_data, r_len)
#define BMA2x2_BURST_READ_FUNC(device_addr,\
register_addr, register_data, rd_len)\
burst_read(device_addr, register_addr, register_data, rd_len)
/**************************************************************/
/**\name    I2C ADDRESS DEFINITIONS    */
/**************************************************************/
/**< The following definition of I2C address is used for the following sensors
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
*/
#define BMA2x2_I2C_ADDR1                (0x18)
#define BMA2x2_I2C_ADDR2                (0x19)

/**< The following definition of I2C address is used for the following sensors
* BMC150
* BMC056
* BMC156
*/
#define BMA2x2_I2C_ADDR3                (0x10)
#define BMA2x2_I2C_ADDR4                (0x11)

/**************************************************************/
/**\name    CONSTANTS DEFINITION    */
/**************************************************************/
#define BMA2x2_INIT_VALUE                       ((u8)0)
#define BMA2x2_GEN_READ_WRITE_LENGTH            ((u8)1)
#define BMA2x2_INTERFACE_IDLE_TIME_DELAY        ((u8)1)
#define BMA2x2_LSB_MSB_READ_LENGTH              ((u8)2)
/** BIT SHIFT DEFINITIONS    */
#define BMA2x2_SHIFT_TWO_BITS                   ((u8)2)
#define BMA2x2_SHIFT_FOUR_BITS                  ((u8)4)
#define BMA2x2_SHIFT_FIVE_BITS                  ((u8)5)
#define BMA2x2_SHIFT_SIX_BITS                   ((u8)6)
#define BMA2x2_SHIFT_EIGHT_BITS                 ((u8)8)
/** FIFO DEFINITIONS    */
#define BMA2x2_FIFO_MODE_STATUS_RANGE           ((u8)2)
#define BMA2x2_FIFO_DATA_SELECT_RANGE           ((u8)4)
#define BMA2x2_FIFO_MODE_RANGE                  ((u8)4)
#define BMA2x2_FIFO_WML_RANGE                   ((u8)32)

#define BMA2x2_FIFO_XYZ_DATA_ENABLED            (0x00)
#define BMA2x2_FIFO_X_DATA_ENABLED              (0x01)
#define BMA2x2_FIFO_Y_DATA_ENABLED              (0x02)
#define BMA2x2_FIFO_Z_DATA_ENABLED              (0x03)
#define BMA2x2_FIFO_DATA_ENABLED_MASK           (0x03)
#define BMA2x2_FIFO_XYZ_AXES_FRAME_SIZE         ((u8)6)
#define BMA2x2_FIFO_SINGLE_AXIS_FRAME_SIZE      ((u8)2)
/** MODE RANGES    */
#define BMA2x2_ACCEL_BW_MIN_RANGE               ((u8)7)
#define BMA2x2_ACCEL_BW_1000HZ_RANGE            ((u8)15)
#define BMA2x2_ACCEL_BW_MAX_RANGE               ((u8)16)
#define BMA2x2_SLEEP_DURN_MIN_RANGE             ((u8)4)
#define BMA2x2_SLEEP_TIMER_MODE_RANGE           ((u8)2)
#define BMA2x2_SLEEP_DURN_MAX_RANGE             ((u8)16)
#define BMA2x2_POWER_MODE_RANGE                 ((u8)6)
#define BMA2x2_SELF_TEST_AXIS_RANGE             ((u8)4)
#define BMA2x2_SELF_TEST_SIGN_RANGE             ((u8)2)

/**************************************************************/
/**\name    ERROR CODE DEFINITIONS    */
/**************************************************************/
#define E_OUT_OF_RANGE          ((s8)-2)
#define E_BMA2x2_NULL_PTR       ((s8)-127)
#define BMA2x2_NULL             ((void *)0)
#define ERROR                   ((s8)-1)
#define SUCCESS                 ((u8)0)
/**************************************************************/
/**\name    RETURN TYPE DEFINITION    */
/**************************************************************/
#define BMA2x2_RETURN_FUNCTION_TYPE        s8
/**< This refers BMA2x2 return type as char */

/**************************************************************/
/**\name    REGISTER ADDRESS DEFINITIONS    */
/**************************************************************/
#define BMA2x2_EEP_OFFSET                       (0x16)
#define BMA2x2_IMAGE_BASE                       (0x38)
#define BMA2x2_IMAGE_LEN                        (22)
#define BMA2x2_CHIP_ID_ADDR                     (0x00)
/** DATA ADDRESS DEFINITIONS */
#define BMA2x2_X_AXIS_LSB_ADDR                  (0x02)
#define BMA2x2_X_AXIS_MSB_ADDR                  (0x03)
#define BMA2x2_Y_AXIS_LSB_ADDR                  (0x04)
#define BMA2x2_Y_AXIS_MSB_ADDR                  (0x05)
#define BMA2x2_Z_AXIS_LSB_ADDR                  (0x06)
#define BMA2x2_Z_AXIS_MSB_ADDR                  (0x07)
#define BMA2x2_TEMP_ADDR                        (0x08)
/**STATUS ADDRESS DEFINITIONS */
#define BMA2x2_STAT1_ADDR                       (0x09)
#define BMA2x2_STAT2_ADDR                       (0x0A)
#define BMA2x2_STAT_TAP_SLOPE_ADDR              (0x0B)
#define BMA2x2_STAT_ORIENT_HIGH_ADDR            (0x0C)
#define BMA2x2_STAT_FIFO_ADDR                   (0x0E)
/**STATUS ADDRESS DEFINITIONS */
#define BMA2x2_RANGE_SELECT_ADDR                (0x0F)
#define BMA2x2_BW_SELECT_ADDR                   (0x10)
#define BMA2x2_MODE_CTRL_ADDR                   (0x11)
#define BMA2x2_LOW_NOISE_CTRL_ADDR              (0x12)
#define BMA2x2_DATA_CTRL_ADDR                   (0x13)
#define BMA2x2_RST_ADDR                         (0x14)
/**INTERUPT ADDRESS DEFINITIONS */
#define BMA2x2_INTR_ENABLE1_ADDR                (0x16)
#define BMA2x2_INTR_ENABLE2_ADDR                (0x17)
#define BMA2x2_INTR_SLOW_NO_MOTION_ADDR         (0x18)
#define BMA2x2_INTR1_PAD_SELECT_ADDR            (0x19)
#define BMA2x2_INTR_DATA_SELECT_ADDR            (0x1A)
#define BMA2x2_INTR2_PAD_SELECT_ADDR            (0x1B)
#define BMA2x2_INTR_SOURCE_ADDR                 (0x1E)
#define BMA2x2_INTR_SET_ADDR                    (0x20)
#define BMA2x2_INTR_CTRL_ADDR                   (0x21)
/** FEATURE ADDRESS DEFINITIONS */
#define BMA2x2_LOW_DURN_ADDR                     (0x22)
#define BMA2x2_LOW_THRES_ADDR                    (0x23)
#define BMA2x2_LOW_HIGH_HYST_ADDR                (0x24)
#define BMA2x2_HIGH_DURN_ADDR                    (0x25)
#define BMA2x2_HIGH_THRES_ADDR                   (0x26)
#define BMA2x2_SLOPE_DURN_ADDR                   (0x27)
#define BMA2x2_SLOPE_THRES_ADDR                  (0x28)
#define BMA2x2_SLOW_NO_MOTION_THRES_ADDR         (0x29)
#define BMA2x2_TAP_PARAM_ADDR                    (0x2A)
#define BMA2x2_TAP_THRES_ADDR                    (0x2B)
#define BMA2x2_ORIENT_PARAM_ADDR                 (0x2C)
#define BMA2x2_THETA_BLOCK_ADDR                  (0x2D)
#define BMA2x2_THETA_FLAT_ADDR                   (0x2E)
#define BMA2x2_FLAT_HOLD_TIME_ADDR               (0x2F)
#define BMA2x2_SELFTEST_ADDR                     (0x32)
#define BMA2x2_EEPROM_CTRL_ADDR                  (0x33)
#define BMA2x2_SERIAL_CTRL_ADDR                  (0x34)
/**OFFSET ADDRESS DEFINITIONS */
#define BMA2x2_OFFSET_CTRL_ADDR                  (0x36)
#define BMA2x2_OFFSET_PARAMS_ADDR                (0x37)
#define BMA2x2_OFFSET_X_AXIS_ADDR                (0x38)
#define BMA2x2_OFFSET_Y_AXIS_ADDR                (0x39)
#define BMA2x2_OFFSET_Z_AXIS_ADDR                (0x3A)
/**GP ADDRESS DEFINITIONS */
#define BMA2x2_GP0_ADDR                          (0x3B)
#define BMA2x2_GP1_ADDR                          (0x3C)
/**FIFO ADDRESS DEFINITIONS */
#define BMA2x2_FIFO_MODE_ADDR                    (0x3E)
#define BMA2x2_FIFO_DATA_OUTPUT_ADDR             (0x3F)
#define BMA2x2_FIFO_WML_TRIG                     (0x30)

/**************************************************************/
/**\name    ACCEL RESOLUTION DEFINITION   */
/**************************************************************/
#define BMA2x2_12_RESOLUTION                    (0)
#define BMA2x2_10_RESOLUTION                    (1)
#define BMA2x2_14_RESOLUTION                    (2)

/**************************************************************/
/**\name    ACCEL DELAY DEFINITION   */
/**************************************************************/
/* register write and read delays */
#define BMA2x2_MDELAY_DATA_TYPE                 u32
#define BMA2x2_EE_W_DELAY                       (28)

/**************************************************************/
/**\name    STRUCTURE DEFINITIONS    */
/**************************************************************/
/*!
*   @brief read accel xyz data for 10,14 and 12 bit resolution
*/
struct bma2x2_accel_data
{
    s16 x,/**< accel x data 10,14 and 12 resolution*/
        y,/**< accel y data 10,14 and 12 resolution*/
        z;/**< accel z data 10,14 and 12 resolution*/
};
/*!
*   @brief read accel xyz data for 10,14 and 12 bit resolution
*   and temperature output
*/
struct bma2x2_accel_data_temp
{
    s16 x,/**< accel x data 10,14 and 12 resolution*/
        y,/**< accel y data 10,14 and 12 resolution*/
        z;/**< accel z data 10,14 and 12 resolution*/
    s8 temp;/**< accel temperature data*/
};

/*!
*   @brief read accel xyz data for 8 bit resolution
*/
struct  bma2x2_accel_eight_resolution
{
    s8 x,/**< accel x data with eight bit resolution*/
    y,/**< accel y data with eight bit resolution*/
    z;/**< accel z data with eight bit resolution*/
};
/*!
*   @brief read accel xyz data for 8 bit resolution and temperature
*/
struct bma2x2_accel_eight_resolution_temp
{
    s8 x,/**< accel x data with eight bit resolution*/
    y,/**< accel y data with eight bit resolution*/
    z;/**< accel z data with eight bit resolution*/
    s8 temp;/**< accel temperature data*/
};

/*!
 *  @brief FIFO data read is parsed and returned to user using this union.
 *
 *  @note Read the respective data fields in the union for corresponding
 *  accel data axes enabled in FIFO storage( Axes stored in FIFO can be set
 *  by the data_select_bits in the register FIFO_CONFIG_1 )
 *
 *  data enabled for FIFO storage | Data field to be read from the below union
 *  ------------------------------|-------------------------------------------
 *          XYZ axes enabled      |         struct bma2x2_accel_data
 *          X axis data enabled   |         x data
 *          Y axis data enabled   |         y data
 *          Z axis data enabled   |         z data
 */
union fifo_frame
{
    /*! FIFO data stored here when XYZ data enabled in
    fifo_data_select bits of register 0x3E*/
    struct bma2x2_accel_data accel_data;
    /*! FIFO data stored here when accel X data enabled in
    fifo_data_select bits of register 0x3E*/
    s16 x;
    /*! FIFO data stored here when accel Y data enabled in
    fifo_data_select bits of register 0x3E*/
    s16 y;
    /*! FIFO data stored here when accel Z data enabled in
    fifo_data_select bits of register 0x3E*/
    s16 z;
};

/*!
 *  @brief bma2x2 initialization struct
 *  struct bma2x2_t is used for assigning the following parameters.
 *
 *  Bus write function pointer: BMA2x2_WR_FUNC_PTR
 *  Bus read function pointer: BMA2x2_RD_FUNC_PTR
 *  Burst read function pointer: BMA2x2_BRD_FUNC_PTR
 *  Delay function pointer: delay_msec
 *  I2C address: dev_addr
 *  Chip id of the sensor: chip_id
 */
struct bma2x2_t
{
    /*! save current bma2x2 operation mode */
    u8 power_mode_u8;
    /*! chip_id of bma2x2 */
    u8 chip_id;
    /*! the value of power mode register 0x11*/
    u8 ctrl_mode_reg;
    /*! the value of power mode register 0x12*/
    u8 low_mode_reg;
    /*! initializes bma2x2's I2C device address*/
    u8 dev_addr;
    /*! store the fifo configuration register*/
    u8 fifo_config;
    /*! function pointer to the SPI/I2C write function */
    BMA2x2_WR_FUNC_PTR;
    /*! function pointer to the SPI/I2C read function */
    BMA2x2_RD_FUNC_PTR;
    /*! function pointer to the SPI/I2C burst read function */
    BMA2x2_BRD_FUNC_PTR;
    /*! delay(in ms) function pointer */
    void (*delay_msec)(BMA2x2_MDELAY_DATA_TYPE);
};

/*!
 *  @brief FIFO configurations are stored in this structure
 *
 *  @note User should map the following before reading the FIFO data
 *    - buffer for storing the FIFO data should be mapped to the member
 *     "fifo_data" of this structure
 *    - Number of bytes to be read from the FIFO should be mapped to the member
 *     "fifo_length" of this structure
 */
struct fifo_configuration
{
    /*! Data buffer of user defined length is to be mapped here */
    u8 *fifo_data;
    /*! Index of accel data stored in FIFO buffer */
    u8 accel_byte_start_index;
    /*! No of bytes to be read in FIFO as specified by the user */
    u8 fifo_length;
};

/*********************************************************************/
/**\name REGISTER BIT MASK, BIT LENGTH, BIT POSITION DEFINITIONS  */
/********************************************************************/
/******************************/
/**\name CHIP ID  */
/******************************/
#define BMA2x2_CHIP_ID_POS             (0)
#define BMA2x2_CHIP_ID_MSK             (0xFF)
#define BMA2x2_CHIP_ID_LEN             (8)
#define BMA2x2_CHIP_ID_REG             BMA2x2_CHIP_ID_ADDR

/******************************/
/**\name DATA REGISTER-X  */
/******************************/
#define BMA2x2_NEW_DATA_X_POS          (0)
#define BMA2x2_NEW_DATA_X_LEN          (1)
#define BMA2x2_NEW_DATA_X_MSK          (0x01)
#define BMA2x2_NEW_DATA_X_REG          BMA2x2_X_AXIS_LSB_ADDR

#define BMA2x2_ACCEL_X14_LSB_POS          (2)
#define BMA2x2_ACCEL_X14_LSB_LEN          (6)
#define BMA2x2_ACCEL_X14_LSB_MSK          (0xFC)
#define BMA2x2_ACCEL_X14_LSB_REG           BMA2x2_X_AXIS_LSB_ADDR

#define BMA2x2_ACCEL_X12_LSB_POS           (4)
#define BMA2x2_ACCEL_X12_LSB_LEN           (4)
#define BMA2x2_ACCEL_X12_LSB_MSK           (0xF0)
#define BMA2x2_ACCEL_X12_LSB_REG           BMA2x2_X_AXIS_LSB_ADDR

#define BMA2x2_ACCEL_X10_LSB_POS           (6)
#define BMA2x2_ACCEL_X10_LSB_LEN           (2)
#define BMA2x2_ACCEL_X10_LSB_MSK           (0xC0)
#define BMA2x2_ACCEL_X10_LSB_REG           BMA2x2_X_AXIS_LSB_ADDR

#define BMA2x2_ACCEL_X8_LSB_POS           (0)
#define BMA2x2_ACCEL_X8_LSB_LEN           (0)
#define BMA2x2_ACCEL_X8_LSB_MSK           (0x00)
#define BMA2x2_ACCEL_X8_LSB_REG           BMA2x2_X_AXIS_LSB_ADDR

#define BMA2x2_ACCEL_X_MSB_POS           (0)
#define BMA2x2_ACCEL_X_MSB_LEN           (8)
#define BMA2x2_ACCEL_X_MSB_MSK           (0xFF)
#define BMA2x2_ACCEL_X_MSB_REG           BMA2x2_X_AXIS_MSB_ADDR
/******************************/
/**\name DATA REGISTER-Y  */
/******************************/
#define BMA2x2_NEW_DATA_Y_POS          (0)
#define BMA2x2_NEW_DATA_Y_LEN          (1)
#define BMA2x2_NEW_DATA_Y_MSK          (0x01)
#define BMA2x2_NEW_DATA_Y_REG          BMA2x2_Y_AXIS_LSB_ADDR

#define BMA2x2_ACCEL_Y14_LSB_POS           (2)
#define BMA2x2_ACCEL_Y14_LSB_LEN           (6)
#define BMA2x2_ACCEL_Y14_LSB_MSK           (0xFC)
#define BMA2x2_ACCEL_Y14_LSB_REG           BMA2x2_Y_AXIS_LSB_ADDR

#define BMA2x2_ACCEL_Y12_LSB_POS           (4)
#define BMA2x2_ACCEL_Y12_LSB_LEN           (4)
#define BMA2x2_ACCEL_Y12_LSB_MSK           (0xF0)
#define BMA2x2_ACCEL_Y12_LSB_REG           BMA2x2_Y_AXIS_LSB_ADDR

#define BMA2x2_ACCEL_Y10_LSB_POS           (6)
#define BMA2x2_ACCEL_Y10_LSB_LEN           (2)
#define BMA2x2_ACCEL_Y10_LSB_MSK           (0xC0)
#define BMA2x2_ACCEL_Y10_LSB_REG           BMA2x2_Y_AXIS_LSB_ADDR

#define BMA2x2_ACCEL_Y8_LSB_POS           (0)
#define BMA2x2_ACCEL_Y8_LSB_LEN           (0)
#define BMA2x2_ACCEL_Y8_LSB_MSK           (0x00)
#define BMA2x2_ACCEL_Y8_LSB_REG           BMA2x2_Y_AXIS_LSB_ADDR

#define BMA2x2_ACCEL_Y_MSB_POS           (0)
#define BMA2x2_ACCEL_Y_MSB_LEN           (8)
#define BMA2x2_ACCEL_Y_MSB_MSK           (0xFF)
#define BMA2x2_ACCEL_Y_MSB_REG           BMA2x2_Y_AXIS_MSB_ADDR
/******************************/
/**\name DATA REGISTER-Z  */
/******************************/
#define BMA2x2_NEW_DATA_Z_POS          (0)
#define BMA2x2_NEW_DATA_Z_LEN          (1)
#define BMA2x2_NEW_DATA_Z_MSK          (0x01)
#define BMA2x2_NEW_DATA_Z_REG          BMA2x2_Z_AXIS_LSB_ADDR

#define BMA2x2_ACCEL_Z14_LSB_POS           (2)
#define BMA2x2_ACCEL_Z14_LSB_LEN           (6)
#define BMA2x2_ACCEL_Z14_LSB_MSK           (0xFC)
#define BMA2x2_ACCEL_Z14_LSB_REG           BMA2x2_Z_AXIS_LSB_ADDR

#define BMA2x2_ACCEL_Z12_LSB_POS           (4)
#define BMA2x2_ACCEL_Z12_LSB_LEN           (4)
#define BMA2x2_ACCEL_Z12_LSB_MSK           (0xF0)
#define BMA2x2_ACCEL_Z12_LSB_REG           BMA2x2_Z_AXIS_LSB_ADDR

#define BMA2x2_ACCEL_Z10_LSB_POS           (6)
#define BMA2x2_ACCEL_Z10_LSB_LEN           (2)
#define BMA2x2_ACCEL_Z10_LSB_MSK           (0xC0)
#define BMA2x2_ACCEL_Z10_LSB_REG           BMA2x2_Z_AXIS_LSB_ADDR

#define BMA2x2_ACCEL_Z8_LSB_POS           (0)
#define BMA2x2_ACCEL_Z8_LSB_LEN           (0)
#define BMA2x2_ACCEL_Z8_LSB_MSK           (0x00)
#define BMA2x2_ACCEL_Z8_LSB_REG           BMA2x2_Z_AXIS_LSB_ADDR

#define BMA2x2_ACCEL_Z_MSB_POS           (0)
#define BMA2x2_ACCEL_Z_MSB_LEN           (8)
#define BMA2x2_ACCEL_Z_MSB_MSK           (0xFF)
#define BMA2x2_ACCEL_Z_MSB_REG           BMA2x2_Z_AXIS_MSB_ADDR

/******************************/
/**\name TEMPERATURE */
/******************************/
#define BMA2x2_ACCEL_TEMP_MSB_POS           (0)
#define BMA2x2_ACCEL_TEMP_MSB_LEN           (8)
#define BMA2x2_ACCEL_TEMP_MSB_MSK           (0xFF)
#define BMA2x2_ACCEL_TEMP_MSB_REG           BMA2x2_TEMPERATURE_REG

/***************************************/
/**\name INTERRUPT STATUS OF LOW-G */
/**************************************/
#define BMA2x2_LOW_G_INTR_STAT_POS          (0)
#define BMA2x2_LOW_G_INTR_STAT_LEN          (1)
#define BMA2x2_LOW_G_INTR_STAT_MSK          (0x01)
#define BMA2x2_LOW_G_INTR_STAT_REG          BMA2x2_STAT1_ADDR
/***************************************/
/**\name INTERRUPT STATUS OF HIGH-G */
/**************************************/
#define BMA2x2_HIGH_G_INTR_STAT_POS          (1)
#define BMA2x2_HIGH_G_INTR_STAT_LEN          (1)
#define BMA2x2_HIGH_G_INTR_STAT_MSK          (0x02)
#define BMA2x2_HIGH_G_INTR_STAT_REG          BMA2x2_STAT1_ADDR
/***************************************/
/**\name INTERRUPT STATUS OF SLOPE */
/**************************************/
#define BMA2x2_SLOPE_INTR_STAT_POS          (2)
#define BMA2x2_SLOPE_INTR_STAT_LEN          (1)
#define BMA2x2_SLOPE_INTR_STAT_MSK          (0x04)
#define BMA2x2_SLOPE_INTR_STAT_REG          BMA2x2_STAT1_ADDR
/*******************************************/
/**\name INTERRUPT STATUS OF SLOW NO MOTION*/
/*******************************************/
#define BMA2x2_SLOW_NO_MOTION_INTR_STAT_POS          (3)
#define BMA2x2_SLOW_NO_MOTION_INTR_STAT_LEN          (1)
#define BMA2x2_SLOW_NO_MOTION_INTR_STAT_MSK          (0x08)
#define BMA2x2_SLOW_NO_MOTION_INTR_STAT_REG          BMA2x2_STAT1_ADDR
/***************************************/
/**\name INTERRUPT STATUS OF DOUBLE TAP */
/**************************************/
#define BMA2x2_DOUBLE_TAP_INTR_STAT_POS     (4)
#define BMA2x2_DOUBLE_TAP_INTR_STAT_LEN     (1)
#define BMA2x2_DOUBLE_TAP_INTR_STAT_MSK     (0x10)
#define BMA2x2_DOUBLE_TAP_INTR_STAT_REG     BMA2x2_STAT1_ADDR
/***************************************/
/**\name INTERRUPT STATUS OF SINGLE TAP */
/**************************************/
#define BMA2x2_SINGLE_TAP_INTR_STAT_POS     (5)
#define BMA2x2_SINGLE_TAP_INTR_STAT_LEN     (1)
#define BMA2x2_SINGLE_TAP_INTR_STAT_MSK     (0x20)
#define BMA2x2_SINGLE_TAP_INTR_STAT_REG     BMA2x2_STAT1_ADDR
/***************************************/
/**\name INTERRUPT STATUS OF ORIENT*/
/**************************************/
#define BMA2x2_ORIENT_INTR_STAT_POS         (6)
#define BMA2x2_ORIENT_INTR_STAT_LEN         (1)
#define BMA2x2_ORIENT_INTR_STAT_MSK         (0x40)
#define BMA2x2_ORIENT_INTR_STAT_REG         BMA2x2_STAT1_ADDR
/***************************************/
/**\name INTERRUPT STATUS OF FLAT */
/**************************************/
#define BMA2x2_FLAT_INTR_STAT_POS           (7)
#define BMA2x2_FLAT_INTR_STAT_LEN           (1)
#define BMA2x2_FLAT_INTR_STAT_MSK           (0x80)
#define BMA2x2_FLAT_INTR_STAT_REG           BMA2x2_STAT1_ADDR
/***************************************/
/**\name INTERRUPT STATUS OF FIFO FULL */
/**************************************/
#define BMA2x2_FIFO_FULL_INTR_STAT_POS           (5)
#define BMA2x2_FIFO_FULL_INTR_STAT_LEN           (1)
#define BMA2x2_FIFO_FULL_INTR_STAT_MSK           (0x20)
#define BMA2x2_FIFO_FULL_INTR_STAT_REG           BMA2x2_STAT2_ADDR
/*******************************************/
/**\name INTERRUPT STATUS OF FIFO WATERMARK*/
/******************************************/
#define BMA2x2_FIFO_WM_INTR_STAT_POS           (6)
#define BMA2x2_FIFO_WM_INTR_STAT_LEN           (1)
#define BMA2x2_FIFO_WM_INTR_STAT_MSK           (0x40)
#define BMA2x2_FIFO_WM_INTR_STAT_REG           BMA2x2_STAT2_ADDR
/***************************************/
/**\name INTERRUPT STATUS OF DATA */
/**************************************/
#define BMA2x2_DATA_INTR_STAT_POS           (7)
#define BMA2x2_DATA_INTR_STAT_LEN           (1)
#define BMA2x2_DATA_INTR_STAT_MSK           (0x80)
#define BMA2x2_DATA_INTR_STAT_REG           BMA2x2_STAT2_ADDR
/*********************************************/
/**\name INTERRUPT STATUS SLOPE XYZ AND SIGN */
/*********************************************/
#define BMA2x2_SLOPE_FIRST_X_POS        (0)
#define BMA2x2_SLOPE_FIRST_X_LEN        (1)
#define BMA2x2_SLOPE_FIRST_X_MSK        (0x01)
#define BMA2x2_SLOPE_FIRST_X_REG        BMA2x2_STAT_TAP_SLOPE_ADDR

#define BMA2x2_SLOPE_FIRST_Y_POS        (1)
#define BMA2x2_SLOPE_FIRST_Y_LEN        (1)
#define BMA2x2_SLOPE_FIRST_Y_MSK        (0x02)
#define BMA2x2_SLOPE_FIRST_Y_REG        BMA2x2_STAT_TAP_SLOPE_ADDR

#define BMA2x2_SLOPE_FIRST_Z_POS        (2)
#define BMA2x2_SLOPE_FIRST_Z_LEN        (1)
#define BMA2x2_SLOPE_FIRST_Z_MSK        (0x04)
#define BMA2x2_SLOPE_FIRST_Z_REG        BMA2x2_STAT_TAP_SLOPE_ADDR

#define BMA2x2_SLOPE_SIGN_STAT_POS         (3)
#define BMA2x2_SLOPE_SIGN_STAT_LEN         (1)
#define BMA2x2_SLOPE_SIGN_STAT_MSK         (0x08)
#define BMA2x2_SLOPE_SIGN_STAT_REG         BMA2x2_STAT_TAP_SLOPE_ADDR
/*********************************************/
/**\name INTERRUPT STATUS TAP XYZ AND SIGN */
/*********************************************/
#define BMA2x2_TAP_FIRST_X_POS        (4)
#define BMA2x2_TAP_FIRST_X_LEN        (1)
#define BMA2x2_TAP_FIRST_X_MSK        (0x10)
#define BMA2x2_TAP_FIRST_X_REG        BMA2x2_STAT_TAP_SLOPE_ADDR

#define BMA2x2_TAP_FIRST_Y_POS        (5)
#define BMA2x2_TAP_FIRST_Y_LEN        (1)
#define BMA2x2_TAP_FIRST_Y_MSK        (0x20)
#define BMA2x2_TAP_FIRST_Y_REG        BMA2x2_STAT_TAP_SLOPE_ADDR

#define BMA2x2_TAP_FIRST_Z_POS        (6)
#define BMA2x2_TAP_FIRST_Z_LEN        (1)
#define BMA2x2_TAP_FIRST_Z_MSK        (0x40)
#define BMA2x2_TAP_FIRST_Z_REG        BMA2x2_STAT_TAP_SLOPE_ADDR

#define BMA2x2_TAP_SIGN_STAT_POS         (7)
#define BMA2x2_TAP_SIGN_STAT_LEN         (1)
#define BMA2x2_TAP_SIGN_STAT_MSK         (0x80)
#define BMA2x2_TAP_SIGN_STAT_REG         BMA2x2_STAT_TAP_SLOPE_ADDR
/*********************************************/
/**\name INTERRUPT STATUS HIGH_G XYZ AND SIGN */
/*********************************************/
#define BMA2x2_HIGH_G_FIRST_X_POS        (0)
#define BMA2x2_HIGH_G_FIRST_X_LEN        (1)
#define BMA2x2_HIGH_G_FIRST_X_MSK        (0x01)
#define BMA2x2_HIGH_G_FIRST_X_REG        BMA2x2_STAT_ORIENT_HIGH_ADDR

#define BMA2x2_HIGH_G_FIRST_Y_POS        (1)
#define BMA2x2_HIGH_G_FIRST_Y_LEN        (1)
#define BMA2x2_HIGH_G_FIRST_Y_MSK        (0x02)
#define BMA2x2_HIGH_G_FIRST_Y_REG        BMA2x2_STAT_ORIENT_HIGH_ADDR

#define BMA2x2_HIGH_G_FIRST_Z_POS        (2)
#define BMA2x2_HIGH_G_FIRST_Z_LEN        (1)
#define BMA2x2_HIGH_G_FIRST_Z_MSK        (0x04)
#define BMA2x2_HIGH_G_FIRST_Z_REG        BMA2x2_STAT_ORIENT_HIGH_ADDR

#define BMA2x2_HIGH_G_SIGN_STAT_POS         (3)
#define BMA2x2_HIGH_G_SIGN_STAT_LEN         (1)
#define BMA2x2_HIGH_G_SIGN_STAT_MSK         (0x08)
#define BMA2x2_HIGH_G_SIGN_STAT_REG         BMA2x2_STAT_ORIENT_HIGH_ADDR
/*********************************************/
/**\name INTERRUPT STATUS ORIENT */
/*********************************************/
#define BMA2x2_ORIENT_STAT_POS             (4)
#define BMA2x2_ORIENT_STAT_LEN             (3)
#define BMA2x2_ORIENT_STAT_MSK             (0x70)
#define BMA2x2_ORIENT_STAT_REG             BMA2x2_STAT_ORIENT_HIGH_ADDR
/*********************************************/
/**\name INTERRUPT STATUS FLAT */
/*********************************************/
#define BMA2x2_FLAT_STAT_POS               (7)
#define BMA2x2_FLAT_STAT_LEN               (1)
#define BMA2x2_FLAT_STAT_MSK               (0x80)
#define BMA2x2_FLAT_STAT_REG               BMA2x2_STAT_ORIENT_HIGH_ADDR

/*********************************************/
/**\name INTERRUPT STATUS OF FIFO FRAME COUNT */
/*********************************************/
#define BMA2x2_FIFO_FRAME_COUNT_STAT_POS             (0)
#define BMA2x2_FIFO_FRAME_COUNT_STAT_LEN             (7)
#define BMA2x2_FIFO_FRAME_COUNT_STAT_MSK             (0x7F)
#define BMA2x2_FIFO_FRAME_COUNT_STAT_REG             BMA2x2_STAT_FIFO_ADDR
/*********************************************/
/**\name INTERRUPT STATUS OF FIFO OVERRUN */
/*********************************************/
#define BMA2x2_FIFO_OVERRUN_STAT_POS             (7)
#define BMA2x2_FIFO_OVERRUN_STAT_LEN             (1)
#define BMA2x2_FIFO_OVERRUN_STAT_MSK             (0x80)
#define BMA2x2_FIFO_OVERRUN_STAT_REG             BMA2x2_STAT_FIFO_ADDR
/****************************/
/**\name RANGE */
/****************************/
#define BMA2x2_RANGE_SELECT_POS             (0)
#define BMA2x2_RANGE_SELECT_LEN             (4)
#define BMA2x2_RANGE_SELECT_MSK             (0x0F)
#define BMA2x2_RANGE_SELECT_REG             BMA2x2_RANGE_SELECT_ADDR
/****************************/
/**\name BANDWIDTH */
/****************************/
#define BMA2x2_BW_POS             (0)
#define BMA2x2_BW_LEN             (5)
#define BMA2x2_BW_MSK             (0x1F)
#define BMA2x2_BW_REG             BMA2x2_BW_SELECT_ADDR
/****************************/
/**\name SLEEP DURATION */
/****************************/
#define BMA2x2_SLEEP_DURN_POS             (1)
#define BMA2x2_SLEEP_DURN_LEN             (4)
#define BMA2x2_SLEEP_DURN_MSK             (0x1E)
#define BMA2x2_SLEEP_DURN_REG             BMA2x2_MODE_CTRL_ADDR
/****************************/
/**\name POWER MODEPOWER MODE */
/****************************/
#define BMA2x2_MODE_CTRL_POS             (5)
#define BMA2x2_MODE_CTRL_LEN             (3)
#define BMA2x2_MODE_CTRL_MSK             (0xE0)
#define BMA2x2_MODE_CTRL_REG             BMA2x2_MODE_CTRL_ADDR
/****************************/
/**\name SLEEP TIMER */
/****************************/
#define BMA2x2_SLEEP_TIMER_POS          (5)
#define BMA2x2_SLEEP_TIMER_LEN          (1)
#define BMA2x2_SLEEP_TIMER_MSK          (0x20)
#define BMA2x2_SLEEP_TIMER_REG          BMA2x2_LOW_NOISE_CTRL_ADDR
/****************************/
/**\name LOWPOWER MODE */
/****************************/
#define BMA2x2_LOW_POWER_MODE_POS          (6)
#define BMA2x2_LOW_POWER_MODE_LEN          (1)
#define BMA2x2_LOW_POWER_MODE_MSK          (0x40)
#define BMA2x2_LOW_POWER_MODE_REG          BMA2x2_LOW_NOISE_CTRL_ADDR
/*******************************************/
/**\name DISABLE MSB SHADOWING PROCEDURE  */
/*******************************************/
#define BMA2x2_DIS_SHADOW_PROC_POS       (6)
#define BMA2x2_DIS_SHADOW_PROC_LEN       (1)
#define BMA2x2_DIS_SHADOW_PROC_MSK       (0x40)
#define BMA2x2_DIS_SHADOW_PROC_REG       BMA2x2_DATA_CTRL_ADDR
/***************************************************/
/**\name FILTERED OR UNFILTERED ACCELERATION DATA   */
/***************************************************/
#define BMA2x2_ENABLE_DATA_HIGH_BW_POS         (7)
#define BMA2x2_ENABLE_DATA_HIGH_BW_LEN         (1)
#define BMA2x2_ENABLE_DATA_HIGH_BW_MSK         (0x80)
#define BMA2x2_ENABLE_DATA_HIGH_BW_REG         BMA2x2_DATA_CTRL_ADDR
/***************************************************/
/**\name SOFT RESET VALUE   */
/***************************************************/
#define BMA2x2_ENABLE_SOFT_RESET_VALUE        (0xB6)
/**********************************************/
/**\name INTERRUPT ENABLE OF SLOPE-XYZ   */
/**********************************************/
#define BMA2x2_ENABLE_SLOPE_X_INTR_POS         (0)
#define BMA2x2_ENABLE_SLOPE_X_INTR_LEN         (1)
#define BMA2x2_ENABLE_SLOPE_X_INTR_MSK         (0x01)
#define BMA2x2_ENABLE_SLOPE_X_INTR_REG         BMA2x2_INTR_ENABLE1_ADDR

#define BMA2x2_ENABLE_SLOPE_Y_INTR_POS         (1)
#define BMA2x2_ENABLE_SLOPE_Y_INTR_LEN         (1)
#define BMA2x2_ENABLE_SLOPE_Y_INTR_MSK         (0x02)
#define BMA2x2_ENABLE_SLOPE_Y_INTR_REG         BMA2x2_INTR_ENABLE1_ADDR

#define BMA2x2_ENABLE_SLOPE_Z_INTR_POS         (2)
#define BMA2x2_ENABLE_SLOPE_Z_INTR_LEN         (1)
#define BMA2x2_ENABLE_SLOPE_Z_INTR_MSK         (0x04)
#define BMA2x2_ENABLE_SLOPE_Z_INTR_REG         BMA2x2_INTR_ENABLE1_ADDR
/**********************************************/
/**\name INTERRUPT ENABLE OF DOUBLE TAP   */
/**********************************************/
#define BMA2x2_ENABLE_DOUBLE_TAP_INTR_POS      (4)
#define BMA2x2_ENABLE_DOUBLE_TAP_INTR_LEN      (1)
#define BMA2x2_ENABLE_DOUBLE_TAP_INTR_MSK      (0x10)
#define BMA2x2_ENABLE_DOUBLE_TAP_INTR_REG      BMA2x2_INTR_ENABLE1_ADDR
/**********************************************/
/**\name INTERRUPT ENABLE OF SINGLE TAP   */
/**********************************************/
#define BMA2x2_ENABLE_SINGLE_TAP_INTR_POS      (5)
#define BMA2x2_ENABLE_SINGLE_TAP_INTR_LEN      (1)
#define BMA2x2_ENABLE_SINGLE_TAP_INTR_MSK      (0x20)
#define BMA2x2_ENABLE_SINGLE_TAP_INTR_REG      BMA2x2_INTR_ENABLE1_ADDR
/**********************************************/
/**\name INTERRUPT ENABLE OF ORIENT  */
/**********************************************/
#define BMA2x2_ENABLE_ORIENT_INTR_POS          (6)
#define BMA2x2_ENABLE_ORIENT_INTR_LEN          (1)
#define BMA2x2_ENABLE_ORIENT_INTR_MSK          (0x40)
#define BMA2x2_ENABLE_ORIENT_INTR_REG          BMA2x2_INTR_ENABLE1_ADDR
/**********************************************/
/**\name INTERRUPT ENABLE OF FLAT  */
/**********************************************/
#define BMA2x2_ENABLE_FLAT_INTR_POS            (7)
#define BMA2x2_ENABLE_FLAT_INTR_LEN            (1)
#define BMA2x2_ENABLE_FLAT_INTR_MSK            (0x80)
#define BMA2x2_ENABLE_FLAT_INTR_REG            BMA2x2_INTR_ENABLE1_ADDR
/**********************************************/
/**\name INTERRUPT ENABLE OF HIGH_G-XYZ   */
/**********************************************/
#define BMA2x2_ENABLE_HIGH_G_X_INTR_POS         (0)
#define BMA2x2_ENABLE_HIGH_G_X_INTR_LEN         (1)
#define BMA2x2_ENABLE_HIGH_G_X_INTR_MSK         (0x01)
#define BMA2x2_ENABLE_HIGH_G_X_INTR_REG         BMA2x2_INTR_ENABLE2_ADDR

#define BMA2x2_ENABLE_HIGH_G_Y_INTR_POS         (1)
#define BMA2x2_ENABLE_HIGH_G_Y_INTR_LEN         (1)
#define BMA2x2_ENABLE_HIGH_G_Y_INTR_MSK         (0x02)
#define BMA2x2_ENABLE_HIGH_G_Y_INTR_REG         BMA2x2_INTR_ENABLE2_ADDR

#define BMA2x2_ENABLE_HIGH_G_Z_INTR_POS         (2)
#define BMA2x2_ENABLE_HIGH_G_Z_INTR_LEN         (1)
#define BMA2x2_ENABLE_HIGH_G_Z_INTR_MSK         (0x04)
#define BMA2x2_ENABLE_HIGH_G_Z_INTR_REG         BMA2x2_INTR_ENABLE2_ADDR
/**********************************************/
/**\name INTERRUPT ENABLE OF LOW_G  */
/**********************************************/
#define BMA2x2_ENABLE_LOW_G_INTR_POS            (3)
#define BMA2x2_ENABLE_LOW_G_INTR_LEN            (1)
#define BMA2x2_ENABLE_LOW_G_INTR_MSK            (0x08)
#define BMA2x2_ENABLE_LOW_G_INTR_REG            BMA2x2_INTR_ENABLE2_ADDR
/**********************************************/
/**\name INTERRUPT ENABLE OF DATA   */
/**********************************************/
#define BMA2x2_ENABLE_NEW_DATA_INTR_POS        (4)
#define BMA2x2_ENABLE_NEW_DATA_INTR_LEN        (1)
#define BMA2x2_ENABLE_NEW_DATA_INTR_MSK        (0x10)
#define BMA2x2_ENABLE_NEW_DATA_INTR_REG        BMA2x2_INTR_ENABLE2_ADDR
/**********************************************/
/**\name INTERRUPT ENABLE OF FIFO FULL   */
/**********************************************/
#define BMA2x2_INTR_FIFO_FULL_ENABLE_INTR_POS        (5)
#define BMA2x2_INTR_FIFO_FULL_ENABLE_INTR_LEN        (1)
#define BMA2x2_INTR_FIFO_FULL_ENABLE_INTR_MSK        (0x20)
#define BMA2x2_INTR_FIFO_FULL_ENABLE_INTR_REG        BMA2x2_INTR_ENABLE2_ADDR
/**********************************************/
/**\name INTERRUPT ENABLE OF FIFO WATER MARK   */
/**********************************************/
#define BMA2x2_INTR_FIFO_WM_ENABLE_INTR_POS        (6)
#define BMA2x2_INTR_FIFO_WM_ENABLE_INTR_LEN        (1)
#define BMA2x2_INTR_FIFO_WM_ENABLE_INTR_MSK        (0x40)
#define BMA2x2_INTR_FIFO_WM_ENABLE_INTR_REG        BMA2x2_INTR_ENABLE2_ADDR
/************************************************/
/**\name INTERRUPT ENABLE OF SLOW NO MOTION-XYZ */
/*************************************************/
#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_X_INTR_POS        (0)
#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_X_INTR_LEN        (1)
#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_X_INTR_MSK        (0x01)
#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_X_INTR_REG        \
BMA2x2_INTR_SLOW_NO_MOTION_ADDR

#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_Y_INTR_POS        (1)
#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_Y_INTR_LEN        (1)
#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_Y_INTR_MSK        (0x02)
#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_Y_INTR_REG        \
BMA2x2_INTR_SLOW_NO_MOTION_ADDR

#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_Z_INTR_POS        (2)
#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_Z_INTR_LEN        (1)
#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_Z_INTR_MSK        (0x04)
#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_Z_INTR_REG        \
BMA2x2_INTR_SLOW_NO_MOTION_ADDR
/**********************************************/
/**\name INTERRUPT ENABLE OF SLOW NO MOTION SELECT */
/**********************************************/
#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_SELECT_INTR_POS        (3)
#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_SELECT_INTR_LEN        (1)
#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_SELECT_INTR_MSK        (0x08)
#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_SELECT_INTR_REG        \
BMA2x2_INTR_SLOW_NO_MOTION_ADDR
/**********************************************/
/**\name INTERRUPT1 ENABLE OF PAD LOW_G */
/**********************************************/
#define BMA2x2_ENABLE_INTR1_PAD_LOW_G_POS        (0)
#define BMA2x2_ENABLE_INTR1_PAD_LOW_G_LEN        (1)
#define BMA2x2_ENABLE_INTR1_PAD_LOW_G_MSK        (0x01)
#define BMA2x2_ENABLE_INTR1_PAD_LOW_G_REG        BMA2x2_INTR1_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT1 ENABLE OF PAD HIGH_G */
/**********************************************/
#define BMA2x2_ENABLE_INTR1_PAD_HIGH_G_POS       (1)
#define BMA2x2_ENABLE_INTR1_PAD_HIGH_G_LEN       (1)
#define BMA2x2_ENABLE_INTR1_PAD_HIGH_G_MSK       (0x02)
#define BMA2x2_ENABLE_INTR1_PAD_HIGH_G_REG       BMA2x2_INTR1_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT1 ENABLE OF PAD SLOPE */
/**********************************************/
#define BMA2x2_ENABLE_INTR1_PAD_SLOPE_POS       (2)
#define BMA2x2_ENABLE_INTR1_PAD_SLOPE_LEN       (1)
#define BMA2x2_ENABLE_INTR1_PAD_SLOPE_MSK       (0x04)
#define BMA2x2_ENABLE_INTR1_PAD_SLOPE_REG       BMA2x2_INTR1_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT1 ENABLE OF SLOW NO MOTION  */
/**********************************************/
#define BMA2x2_ENABLE_INTR1_PAD_SLOW_NO_MOTION_POS        (3)
#define BMA2x2_ENABLE_INTR1_PAD_SLOW_NO_MOTION_LEN        (1)
#define BMA2x2_ENABLE_INTR1_PAD_SLOW_NO_MOTION_MSK        (0x08)
#define BMA2x2_ENABLE_INTR1_PAD_SLOW_NO_MOTION_REG        \
BMA2x2_INTR1_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT1 ENABLE OF PAD DOUBLE_TAP */
/**********************************************/
#define BMA2x2_ENABLE_INTR1_PAD_DOUBLE_TAP_POS      (4)
#define BMA2x2_ENABLE_INTR1_PAD_DOUBLE_TAP_LEN      (1)
#define BMA2x2_ENABLE_INTR1_PAD_DOUBLE_TAP_MSK      (0x10)
#define BMA2x2_ENABLE_INTR1_PAD_DOUBLE_TAP_REG      BMA2x2_INTR1_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT1 ENABLE OF PAD SINGLE_TAP */
/**********************************************/
#define BMA2x2_ENABLE_INTR1_PAD_SINGLE_TAP_POS     (5)
#define BMA2x2_ENABLE_INTR1_PAD_SINGLE_TAP_LEN     (1)
#define BMA2x2_ENABLE_INTR1_PAD_SINGLE_TAP_MSK     (0x20)
#define BMA2x2_ENABLE_INTR1_PAD_SINGLE_TAP_REG     BMA2x2_INTR1_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT1 ENABLE OF PAD ORIENT*/
/**********************************************/
#define BMA2x2_ENABLE_INTR1_PAD_ORIENT_POS      (6)
#define BMA2x2_ENABLE_INTR1_PAD_ORIENT_LEN      (1)
#define BMA2x2_ENABLE_INTR1_PAD_ORIENT_MSK      (0x40)
#define BMA2x2_ENABLE_INTR1_PAD_ORIENT_REG      BMA2x2_INTR1_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT1 ENABLE OF PAD FLAT */
/**********************************************/
#define BMA2x2_ENABLE_INTR1_PAD_FLAT_POS        (7)
#define BMA2x2_ENABLE_INTR1_PAD_FLAT_LEN        (1)
#define BMA2x2_ENABLE_INTR1_PAD_FLAT_MSK        (0x80)
#define BMA2x2_ENABLE_INTR1_PAD_FLAT_REG        BMA2x2_INTR1_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD LOW_G */
/**********************************************/
#define BMA2x2_ENABLE_INTR2_PAD_LOW_G_POS        (0)
#define BMA2x2_ENABLE_INTR2_PAD_LOW_G_LEN        (1)
#define BMA2x2_ENABLE_INTR2_PAD_LOW_G_MSK        (0x01)
#define BMA2x2_ENABLE_INTR2_PAD_LOW_G_REG        BMA2x2_INTR2_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD HIGH_G */
/**********************************************/
#define BMA2x2_ENABLE_INTR2_PAD_HIGH_G_POS       (1)
#define BMA2x2_ENABLE_INTR2_PAD_HIGH_G_LEN       (1)
#define BMA2x2_ENABLE_INTR2_PAD_HIGH_G_MSK       (0x02)
#define BMA2x2_ENABLE_INTR2_PAD_HIGH_G_REG       BMA2x2_INTR2_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD SLOPE */
/**********************************************/
#define BMA2x2_ENABLE_INTR2_PAD_SLOPE_POS       (2)
#define BMA2x2_ENABLE_INTR2_PAD_SLOPE_LEN       (1)
#define BMA2x2_ENABLE_INTR2_PAD_SLOPE_MSK       (0x04)
#define BMA2x2_ENABLE_INTR2_PAD_SLOPE_REG       BMA2x2_INTR2_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD SLOW NO MOTION */
/**********************************************/
#define BMA2x2_ENABLE_INTR2_PAD_SLOW_NO_MOTION_POS        (3)
#define BMA2x2_ENABLE_INTR2_PAD_SLOW_NO_MOTION_LEN        (1)
#define BMA2x2_ENABLE_INTR2_PAD_SLOW_NO_MOTION_MSK        (0x08)
#define BMA2x2_ENABLE_INTR2_PAD_SLOW_NO_MOTION_REG        \
BMA2x2_INTR2_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD DOUBLE_TAP */
/**********************************************/
#define BMA2x2_ENABLE_INTR2_PAD_DOUBLE_TAP_POS      (4)
#define BMA2x2_ENABLE_INTR2_PAD_DOUBLE_TAP_LEN      (1)
#define BMA2x2_ENABLE_INTR2_PAD_DOUBLE_TAP_MSK      (0x10)
#define BMA2x2_ENABLE_INTR2_PAD_DOUBLE_TAP_REG      BMA2x2_INTR2_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD SINGLE_TAP */
/**********************************************/
#define BMA2x2_ENABLE_INTR2_PAD_SINGLE_TAP_POS     (5)
#define BMA2x2_ENABLE_INTR2_PAD_SINGLE_TAP_LEN     (1)
#define BMA2x2_ENABLE_INTR2_PAD_SINGLE_TAP_MSK     (0x20)
#define BMA2x2_ENABLE_INTR2_PAD_SINGLE_TAP_REG     BMA2x2_INTR2_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD ORIENT */
/**********************************************/
#define BMA2x2_ENABLE_INTR2_PAD_ORIENT_POS      (6)
#define BMA2x2_ENABLE_INTR2_PAD_ORIENT_LEN      (1)
#define BMA2x2_ENABLE_INTR2_PAD_ORIENT_MSK      (0x40)
#define BMA2x2_ENABLE_INTR2_PAD_ORIENT_REG      BMA2x2_INTR2_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD FLAT */
/**********************************************/
#define BMA2x2_ENABLE_INTR2_PAD_FLAT_POS        (7)
#define BMA2x2_ENABLE_INTR2_PAD_FLAT_LEN        (1)
#define BMA2x2_ENABLE_INTR2_PAD_FLAT_MSK        (0x80)
#define BMA2x2_ENABLE_INTR2_PAD_FLAT_REG        BMA2x2_INTR2_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD DATA */
/**********************************************/
#define BMA2x2_ENABLE_INTR1_PAD_NEWDATA_POS     (0)
#define BMA2x2_ENABLE_INTR1_PAD_NEWDATA_LEN     (1)
#define BMA2x2_ENABLE_INTR1_PAD_NEWDATA_MSK     (0x01)
#define BMA2x2_ENABLE_INTR1_PAD_NEWDATA_REG     BMA2x2_INTR_DATA_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT1 ENABLE OF FIFO WATER MARK */
/**********************************************/
#define BMA2x2_ENABLE_INTR1_PAD_FIFO_WM_POS     (1)
#define BMA2x2_ENABLE_INTR1_PAD_FIFO_WM_LEN     (1)
#define BMA2x2_ENABLE_INTR1_PAD_FIFO_WM_MSK     (0x02)
#define BMA2x2_ENABLE_INTR1_PAD_FIFO_WM_REG     BMA2x2_INTR_DATA_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT1 ENABLE OF FIFO FULL*/
/**********************************************/
#define BMA2x2_ENABLE_INTR1_PAD_FIFO_FULL_POS     (2)
#define BMA2x2_ENABLE_INTR1_PAD_FIFO_FULL_LEN     (1)
#define BMA2x2_ENABLE_INTR1_PAD_FIFO_FULL_MSK     (0x04)
#define BMA2x2_ENABLE_INTR1_PAD_FIFO_FULL_REG     BMA2x2_INTR_DATA_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD FIFO FULL */
/**********************************************/
#define BMA2x2_ENABLE_INTR2_PAD_FIFO_FULL_POS     (5)
#define BMA2x2_ENABLE_INTR2_PAD_FIFO_FULL_LEN     (1)
#define BMA2x2_ENABLE_INTR2_PAD_FIFO_FULL_MSK     (0x20)
#define BMA2x2_ENABLE_INTR2_PAD_FIFO_FULL_REG     BMA2x2_INTR_DATA_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD FIFO WATERMARK*/
/**********************************************/
#define BMA2x2_ENABLE_INTR2_PAD_FIFO_WM_POS     (6)
#define BMA2x2_ENABLE_INTR2_PAD_FIFO_WM_LEN     (1)
#define BMA2x2_ENABLE_INTR2_PAD_FIFO_WM_MSK     (0x40)
#define BMA2x2_ENABLE_INTR2_PAD_FIFO_WM_REG     BMA2x2_INTR_DATA_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD DATA */
/**********************************************/
#define BMA2x2_ENABLE_INTR2_PAD_NEWDATA_POS     (7)
#define BMA2x2_ENABLE_INTR2_PAD_NEWDATA_LEN     (1)
#define BMA2x2_ENABLE_INTR2_PAD_NEWDATA_MSK     (0x80)
#define BMA2x2_ENABLE_INTR2_PAD_NEWDATA_REG     BMA2x2_INTR_DATA_SELECT_ADDR
/**********************************************/
/**\name  INTERRUPT SOURCE SELECTION OF LOW_G*/
/**********************************************/
#define BMA2x2_UNFILT_INTR_SOURCE_LOW_G_POS        (0)
#define BMA2x2_UNFILT_INTR_SOURCE_LOW_G_LEN        (1)
#define BMA2x2_UNFILT_INTR_SOURCE_LOW_G_MSK        (0x01)
#define BMA2x2_UNFILT_INTR_SOURCE_LOW_G_REG        BMA2x2_INTR_SOURCE_ADDR
/**********************************************/
/**\name  INTERRUPT SOURCE SELECTION OF HIGH_G*/
/**********************************************/
#define BMA2x2_UNFILT_INTR_SOURCE_HIGH_G_POS       (1)
#define BMA2x2_UNFILT_INTR_SOURCE_HIGH_G_LEN       (1)
#define BMA2x2_UNFILT_INTR_SOURCE_HIGH_G_MSK       (0x02)
#define BMA2x2_UNFILT_INTR_SOURCE_HIGH_G_REG       BMA2x2_INTR_SOURCE_ADDR
/**********************************************/
/**\name  INTERRUPT SOURCE SELECTION OF SLOPE*/
/**********************************************/
#define BMA2x2_UNFILT_INTR_SOURCE_SLOPE_POS       (2)
#define BMA2x2_UNFILT_INTR_SOURCE_SLOPE_LEN       (1)
#define BMA2x2_UNFILT_INTR_SOURCE_SLOPE_MSK       (0x04)
#define BMA2x2_UNFILT_INTR_SOURCE_SLOPE_REG       BMA2x2_INTR_SOURCE_ADDR
/**********************************************/
/**\name  INTERRUPT SOURCE SELECTION OF SLOW NO MOTION*/
/**********************************************/
#define BMA2x2_UNFILT_INTR_SOURCE_SLOW_NO_MOTION_POS        (3)
#define BMA2x2_UNFILT_INTR_SOURCE_SLOW_NO_MOTION_LEN        (1)
#define BMA2x2_UNFILT_INTR_SOURCE_SLOW_NO_MOTION_MSK        (0x08)
#define BMA2x2_UNFILT_INTR_SOURCE_SLOW_NO_MOTION_REG        \
BMA2x2_INTR_SOURCE_ADDR
/**********************************************/
/**\name  INTERRUPT SOURCE SELECTION OF TAP*/
/**********************************************/
#define BMA2x2_UNFILT_INTR_SOURCE_TAP_POS         (4)
#define BMA2x2_UNFILT_INTR_SOURCE_TAP_LEN         (1)
#define BMA2x2_UNFILT_INTR_SOURCE_TAP_MSK         (0x10)
#define BMA2x2_UNFILT_INTR_SOURCE_TAP_REG         BMA2x2_INTR_SOURCE_ADDR
/**********************************************/
/**\name  INTERRUPT SOURCE SELECTION OF DATA*/
/**********************************************/
#define BMA2x2_UNFILT_INTR_SOURCE_DATA_POS        (5)
#define BMA2x2_UNFILT_INTR_SOURCE_DATA_LEN        (1)
#define BMA2x2_UNFILT_INTR_SOURCE_DATA_MSK        (0x20)
#define BMA2x2_UNFILT_INTR_SOURCE_DATA_REG        BMA2x2_INTR_SOURCE_ADDR
/****************************************************/
/**\name  INTERRUPT PAD ACTIVE LEVEL AND OUTPUT TYPE*/
/****************************************************/
#define BMA2x2_INTR1_PAD_ACTIVE_LEVEL_POS       (0)
#define BMA2x2_INTR1_PAD_ACTIVE_LEVEL_LEN       (1)
#define BMA2x2_INTR1_PAD_ACTIVE_LEVEL_MSK       (0x01)
#define BMA2x2_INTR1_PAD_ACTIVE_LEVEL_REG       BMA2x2_INTR_SET_ADDR

#define BMA2x2_INTR2_PAD_ACTIVE_LEVEL_POS       (2)
#define BMA2x2_INTR2_PAD_ACTIVE_LEVEL_LEN       (1)
#define BMA2x2_INTR2_PAD_ACTIVE_LEVEL_MSK       (0x04)
#define BMA2x2_INTR2_PAD_ACTIVE_LEVEL_REG       BMA2x2_INTR_SET_ADDR

#define BMA2x2_INTR1_PAD_OUTPUT_TYPE_POS        (1)
#define BMA2x2_INTR1_PAD_OUTPUT_TYPE_LEN        (1)
#define BMA2x2_INTR1_PAD_OUTPUT_TYPE_MSK        (0x02)
#define BMA2x2_INTR1_PAD_OUTPUT_TYPE_REG        BMA2x2_INTR_SET_ADDR

#define BMA2x2_INTR2_PAD_OUTPUT_TYPE_POS        (3)
#define BMA2x2_INTR2_PAD_OUTPUT_TYPE_LEN        (1)
#define BMA2x2_INTR2_PAD_OUTPUT_TYPE_MSK        (0x08)
#define BMA2x2_INTR2_PAD_OUTPUT_TYPE_REG        BMA2x2_INTR_SET_ADDR
/****************************************************/
/**\name   LATCH INTERRUPT */
/****************************************************/
#define BMA2x2_LATCH_INTR_POS                (0)
#define BMA2x2_LATCH_INTR_LEN                (4)
#define BMA2x2_LATCH_INTR_MSK                (0x0F)
#define BMA2x2_LATCH_INTR_REG                BMA2x2_INTR_CTRL_ADDR
/****************************************************/
/**\name   RESET LATCH INTERRUPT */
/****************************************************/
#define BMA2x2_RESET_INTR_POS           (7)
#define BMA2x2_RESET_INTR_LEN           (1)
#define BMA2x2_RESET_INTR_MSK           (0x80)
#define BMA2x2_RESET_INTR_REG           BMA2x2_INTR_CTRL_ADDR
/****************************************************/
/**\name   LOW_G HYSTERESIS */
/****************************************************/
#define BMA2x2_LOW_G_HYST_POS                   (0)
#define BMA2x2_LOW_G_HYST_LEN                   (2)
#define BMA2x2_LOW_G_HYST_MSK                   (0x03)
#define BMA2x2_LOW_G_HYST_REG                   BMA2x2_LOW_HIGH_HYST_ADDR
/****************************************************/
/**\name   LOW_G MODE */
/****************************************************/
#define BMA2x2_LOW_G_INTR_MODE_POS               (2)
#define BMA2x2_LOW_G_INTR_MODE_LEN               (1)
#define BMA2x2_LOW_G_INTR_MODE_MSK               (0x04)
#define BMA2x2_LOW_G_INTR_MODE_REG               BMA2x2_LOW_HIGH_HYST_ADDR

/****************************************************/
/**\name   HIGH_G HYSTERESIS */
/****************************************************/
#define BMA2x2_HIGH_G_HYST_POS                  (6)
#define BMA2x2_HIGH_G_HYST_LEN                  (2)
#define BMA2x2_HIGH_G_HYST_MSK                  (0xC0)
#define BMA2x2_HIGH_G_HYST_REG                  BMA2x2_LOW_HIGH_HYST_ADDR
/****************************************************/
/**\name   SLOPE DURATION */
/****************************************************/
#define BMA2x2_SLOPE_DURN_POS                    (0)
#define BMA2x2_SLOPE_DURN_LEN                    (2)
#define BMA2x2_SLOPE_DURN_MSK                    (0x03)
#define BMA2x2_SLOPE_DURN_REG                    BMA2x2_SLOPE_DURN_ADDR
/****************************************************/
/**\name   SLOW NO MOTION DURATION */
/****************************************************/
#define BMA2x2_SLOW_NO_MOTION_DURN_POS                    (2)
#define BMA2x2_SLOW_NO_MOTION_DURN_LEN                    (6)
#define BMA2x2_SLOW_NO_MOTION_DURN_MSK                    (0xFC)
#define BMA2x2_SLOW_NO_MOTION_DURN_REG                    BMA2x2_SLOPE_DURN_ADDR

/****************************************************/
/**\name   TAP DURATION */
/****************************************************/
#define BMA2x2_TAP_DURN_POS                    (0)
#define BMA2x2_TAP_DURN_LEN                    (3)
#define BMA2x2_TAP_DURN_MSK                    (0x07)
#define BMA2x2_TAP_DURN_REG                    BMA2x2_TAP_PARAM_ADDR

/****************************************************/
/**\name   TAP SHOCK DURATION */
/****************************************************/
#define BMA2x2_TAP_SHOCK_DURN_POS             (6)
#define BMA2x2_TAP_SHOCK_DURN_LEN             (1)
#define BMA2x2_TAP_SHOCK_DURN_MSK             (0x40)
#define BMA2x2_TAP_SHOCK_DURN_REG             BMA2x2_TAP_PARAM_ADDR

/* This advance tap interrupt only uses for the chip id 0xFB */
#define BMA2x2_ADV_TAP_INTR_POS                (5)
#define BMA2x2_ADV_TAP_INTR_LEN                (1)
#define BMA2x2_ADV_TAP_INTR_MSK                (0x20)
#define BMA2x2_ADV_TAP_INTR_REG                BMA2x2_TAP_PARAM_ADDR
/****************************************************/
/**\name   TAP QUIET DURATION */
/****************************************************/
#define BMA2x2_TAP_QUIET_DURN_POS             (7)
#define BMA2x2_TAP_QUIET_DURN_LEN             (1)
#define BMA2x2_TAP_QUIET_DURN_MSK             (0x80)
#define BMA2x2_TAP_QUIET_DURN_REG             BMA2x2_TAP_PARAM_ADDR
/****************************************************/
/**\name   TAP THRESHOLD */
/****************************************************/
#define BMA2x2_TAP_THRES_POS                  (0)
#define BMA2x2_TAP_THRES_LEN                  (5)
#define BMA2x2_TAP_THRES_MSK                  (0x1F)
#define BMA2x2_TAP_THRES_REG                  BMA2x2_TAP_THRES_ADDR
/****************************************************/
/**\name   TAP SAMPLES */
/****************************************************/
#define BMA2x2_TAP_SAMPLES_POS                (6)
#define BMA2x2_TAP_SAMPLES_LEN                (2)
#define BMA2x2_TAP_SAMPLES_MSK                (0xC0)
#define BMA2x2_TAP_SAMPLES_REG                BMA2x2_TAP_THRES_ADDR
/****************************************************/
/**\name  ORIENT MODE */
/****************************************************/
#define BMA2x2_ORIENT_MODE_POS                  (0)
#define BMA2x2_ORIENT_MODE_LEN                  (2)
#define BMA2x2_ORIENT_MODE_MSK                  (0x03)
#define BMA2x2_ORIENT_MODE_REG                  BMA2x2_ORIENT_PARAM_ADDR
/****************************************************/
/**\name   ORIENT BLOCKING */
/****************************************************/
#define BMA2x2_ORIENT_BLOCK_POS                 (2)
#define BMA2x2_ORIENT_BLOCK_LEN                 (2)
#define BMA2x2_ORIENT_BLOCK_MSK                 (0x0C)
#define BMA2x2_ORIENT_BLOCK_REG                 BMA2x2_ORIENT_PARAM_ADDR
/****************************************************/
/**\name   ORIENT HYSTERESIS */
/****************************************************/
#define BMA2x2_ORIENT_HYST_POS                  (4)
#define BMA2x2_ORIENT_HYST_LEN                  (3)
#define BMA2x2_ORIENT_HYST_MSK                  (0x70)
#define BMA2x2_ORIENT_HYST_REG                  BMA2x2_ORIENT_PARAM_ADDR
/****************************************************/
/**\name   ORIENT AXIS  */
/****************************************************/
#define BMA2x2_ORIENT_UD_ENABLE_POS                  (6)
#define BMA2x2_ORIENT_UD_ENABLE_LEN                  (1)
#define BMA2x2_ORIENT_UD_ENABLE_MSK                  (0x40)
#define BMA2x2_ORIENT_UD_ENABLE_REG                  BMA2x2_THETA_BLOCK_ADDR

/****************************************************/
/**\name   THETA BLOCKING */
/****************************************************/
#define BMA2x2_THETA_BLOCK_POS                  (0)
#define BMA2x2_THETA_BLOCK_LEN                  (6)
#define BMA2x2_THETA_BLOCK_MSK                  (0x3F)
#define BMA2x2_THETA_BLOCK_REG                  BMA2x2_THETA_BLOCK_ADDR
/****************************************************/
/**\name   THETA FLAT */
/****************************************************/
#define BMA2x2_THETA_FLAT_POS                  (0)
#define BMA2x2_THETA_FLAT_LEN                  (6)
#define BMA2x2_THETA_FLAT_MSK                  (0x3F)
#define BMA2x2_THETA_FLAT_REG                  BMA2x2_THETA_FLAT_ADDR
/****************************************************/
/**\name   THETA HOLD TIME */
/****************************************************/
#define BMA2x2_FLAT_HOLD_TIME_POS              (4)
#define BMA2x2_FLAT_HOLD_TIME_LEN              (2)
#define BMA2x2_FLAT_HOLD_TIME_MSK              (0x30)
#define BMA2x2_FLAT_HOLD_TIME_REG              BMA2x2_FLAT_HOLD_TIME_ADDR
/****************************************************/
/**\name   FLAT HYSTERESIS */
/****************************************************/
#define BMA2x2_FLAT_HYST_POS                   (0)
#define BMA2x2_FLAT_HYST_LEN                   (3)
#define BMA2x2_FLAT_HYST_MSK                   (0x07)
#define BMA2x2_FLAT_HYST_REG                   BMA2x2_FLAT_HOLD_TIME_ADDR
/****************************************************/
/**\name   FIFO WATER MARK LEVEL TRIGGER RETAIN  */
/****************************************************/
#define BMA2x2_FIFO_WML_TRIG_RETAIN_POS                   (0)
#define BMA2x2_FIFO_WML_TRIG_RETAIN_LEN                   (6)
#define BMA2x2_FIFO_WML_TRIG_RETAIN_MSK                   (0x3F)
#define BMA2x2_FIFO_WML_TRIG_RETAIN_REG                   BMA2x2_FIFO_WML_TRIG
/****************************************************/
/**\name   ACTIVATE SELF TEST  */
/****************************************************/
#define BMA2x2_ENABLE_SELFTEST_POS                (0)
#define BMA2x2_ENABLE_SELFTEST_LEN                (2)
#define BMA2x2_ENABLE_SELFTEST_MSK                (0x03)
#define BMA2x2_ENABLE_SELFTEST_REG                BMA2x2_SELFTEST_ADDR
/****************************************************/
/**\name   SELF TEST -- NEGATIVE   */
/****************************************************/
#define BMA2x2_NEG_SELFTEST_POS               (2)
#define BMA2x2_NEG_SELFTEST_LEN               (1)
#define BMA2x2_NEG_SELFTEST_MSK               (0x04)
#define BMA2x2_NEG_SELFTEST_REG               BMA2x2_SELFTEST_ADDR
/****************************************************/
/**\name   EEPROM CONTROL   */
/****************************************************/
#define BMA2x2_UNLOCK_EE_PROG_MODE_POS     (0)
#define BMA2x2_UNLOCK_EE_PROG_MODE_LEN     (1)
#define BMA2x2_UNLOCK_EE_PROG_MODE_MSK     (0x01)
#define BMA2x2_UNLOCK_EE_PROG_MODE_REG     BMA2x2_EEPROM_CTRL_ADDR
/**********************************************************************/
/**\name  SETTING THIS BIT STARTS WRITING SETTING REGISTERS TO EEPROM */
/*********************************************************************/
#define BMA2x2_START_EE_PROG_TRIG_POS      (1)
#define BMA2x2_START_EE_PROG_TRIG_LEN      (1)
#define BMA2x2_START_EE_PROG_TRIG_MSK      (0x02)
#define BMA2x2_START_EE_PROG_TRIG_REG      BMA2x2_EEPROM_CTRL_ADDR
/****************************************************/
/**\name   STATUS OF WRITING TO EEPROM   */
/****************************************************/
#define BMA2x2_EE_PROG_READY_POS          (2)
#define BMA2x2_EE_PROG_READY_LEN          (1)
#define BMA2x2_EE_PROG_READY_MSK          (0x04)
#define BMA2x2_EE_PROG_READY_REG          BMA2x2_EEPROM_CTRL_ADDR
/****************************************************/
/**\name   UPDATE IMAGE REGISTERS WRITING TO EEPROM   */
/****************************************************/
#define BMA2x2_UPDATE_IMAGE_POS                (3)
#define BMA2x2_UPDATE_IMAGE_LEN                (1)
#define BMA2x2_UPDATE_IMAGE_MSK                (0x08)
#define BMA2x2_UPDATE_IMAGE_REG                BMA2x2_EEPROM_CTRL_ADDR

#define BMA2x2_EE_REMAIN_POS                (4)
#define BMA2x2_EE_REMAIN_LEN                (4)
#define BMA2x2_EE_REMAIN_MSK                (0xF0)
#define BMA2x2_EE_REMAIN_REG                BMA2x2_EEPROM_CTRL_ADDR
/****************************************************/
/**\name   SPI INTERFACE MODE SELECTION   */
/***************************************************/
#define BMA2x2_ENABLE_SPI_MODE_3_POS              (0)
#define BMA2x2_ENABLE_SPI_MODE_3_LEN              (1)
#define BMA2x2_ENABLE_SPI_MODE_3_MSK              (0x01)
#define BMA2x2_ENABLE_SPI_MODE_3_REG              BMA2x2_SERIAL_CTRL_ADDR
/****************************************************/
/**\name   I2C WATCHDOG PERIOD SELECTION   */
/***************************************************/
#define BMA2x2_I2C_WDT_PERIOD_POS        (1)
#define BMA2x2_I2C_WDT_PERIOD_LEN        (1)
#define BMA2x2_I2C_WDT_PERIOD_MSK        (0x02)
#define BMA2x2_I2C_WDT_PERIOD_REG        BMA2x2_SERIAL_CTRL_ADDR
/****************************************************/
/**\name   I2C WATCHDOG ENABLE   */
/***************************************************/
#define BMA2x2_ENABLE_I2C_WDT_POS            (2)
#define BMA2x2_ENABLE_I2C_WDT_LEN            (1)
#define BMA2x2_ENABLE_I2C_WDT_MSK            (0x04)
#define BMA2x2_ENABLE_I2C_WDT_REG            BMA2x2_SERIAL_CTRL_ADDR
/****************************************************/
/**\name   SPI INTERFACE MODE SELECTIONE            */
/***************************************************/
#define BMA2x2_UNLOCK_EE_WRITE_TRIM_POS        (4)
#define BMA2x2_UNLOCK_EE_WRITE_TRIM_LEN        (4)
#define BMA2x2_UNLOCK_EE_WRITE_TRIM_MSK        (0xF0)
#define BMA2x2_UNLOCK_EE_WRITE_TRIM_REG        BMA2x2_CTRL_UNLOCK_REG
/******************************************************************/
/**\name   OFFSET  COMPENSATION/SLOW COMPENSATION FOR X,Y,Z AXIS */
/*****************************************************************/
#define BMA2x2_ENABLE_SLOW_COMP_X_POS              (0)
#define BMA2x2_ENABLE_SLOW_COMP_X_LEN              (1)
#define BMA2x2_ENABLE_SLOW_COMP_X_MSK              (0x01)
#define BMA2x2_ENABLE_SLOW_COMP_X_REG              BMA2x2_OFFSET_CTRL_ADDR

#define BMA2x2_ENABLE_SLOW_COMP_Y_POS              (1)
#define BMA2x2_ENABLE_SLOW_COMP_Y_LEN              (1)
#define BMA2x2_ENABLE_SLOW_COMP_Y_MSK              (0x02)
#define BMA2x2_ENABLE_SLOW_COMP_Y_REG              BMA2x2_OFFSET_CTRL_ADDR

#define BMA2x2_ENABLE_SLOW_COMP_Z_POS              (2)
#define BMA2x2_ENABLE_SLOW_COMP_Z_LEN              (1)
#define BMA2x2_ENABLE_SLOW_COMP_Z_MSK              (0x04)
#define BMA2x2_ENABLE_SLOW_COMP_Z_REG              BMA2x2_OFFSET_CTRL_ADDR
/****************************************************/
/**\name   FAST COMPENSATION READY FLAG            */
/***************************************************/
#define BMA2x2_FAST_CAL_RDY_STAT_POS             (4)
#define BMA2x2_FAST_CAL_RDY_STAT_LEN             (1)
#define BMA2x2_FAST_CAL_RDY_STAT_MSK             (0x10)
#define BMA2x2_FAST_CAL_RDY_STAT_REG             BMA2x2_OFFSET_CTRL_ADDR
/****************************************************/
/**\name   FAST COMPENSATION FOR X,Y,Z AXIS         */
/***************************************************/
#define BMA2x2_CAL_TRIGGER_POS                (5)
#define BMA2x2_CAL_TRIGGER_LEN                (2)
#define BMA2x2_CAL_TRIGGER_MSK                (0x60)
#define BMA2x2_CAL_TRIGGER_REG                BMA2x2_OFFSET_CTRL_ADDR
/****************************************************/
/**\name   RESET OFFSET REGISTERS         */
/***************************************************/
#define BMA2x2_RST_OFFSET_POS           (7)
#define BMA2x2_RST_OFFSET_LEN           (1)
#define BMA2x2_RST_OFFSET_MSK           (0x80)
#define BMA2x2_RST_OFFSET_REG           BMA2x2_OFFSET_CTRL_ADDR
/****************************************************/
/**\name   SLOW COMPENSATION  CUTOFF        */
/***************************************************/
#define BMA2x2_COMP_CUTOFF_POS                 (0)
#define BMA2x2_COMP_CUTOFF_LEN                 (1)
#define BMA2x2_COMP_CUTOFF_MSK                 (0x01)
#define BMA2x2_COMP_CUTOFF_REG                 BMA2x2_OFFSET_PARAMS_ADDR
/****************************************************/
/**\name    COMPENSATION TARGET       */
/***************************************************/
#define BMA2x2_COMP_TARGET_OFFSET_X_POS        (1)
#define BMA2x2_COMP_TARGET_OFFSET_X_LEN        (2)
#define BMA2x2_COMP_TARGET_OFFSET_X_MSK        (0x06)
#define BMA2x2_COMP_TARGET_OFFSET_X_REG        BMA2x2_OFFSET_PARAMS_ADDR

#define BMA2x2_COMP_TARGET_OFFSET_Y_POS        (3)
#define BMA2x2_COMP_TARGET_OFFSET_Y_LEN        (2)
#define BMA2x2_COMP_TARGET_OFFSET_Y_MSK        (0x18)
#define BMA2x2_COMP_TARGET_OFFSET_Y_REG        BMA2x2_OFFSET_PARAMS_ADDR

#define BMA2x2_COMP_TARGET_OFFSET_Z_POS        (5)
#define BMA2x2_COMP_TARGET_OFFSET_Z_LEN        (2)
#define BMA2x2_COMP_TARGET_OFFSET_Z_MSK        (0x60)
#define BMA2x2_COMP_TARGET_OFFSET_Z_REG        BMA2x2_OFFSET_PARAMS_ADDR
/****************************************************/
/**\name    FIFO DATA SELECT       */
/***************************************************/
#define BMA2x2_FIFO_DATA_SELECT_POS                 (0)
#define BMA2x2_FIFO_DATA_SELECT_LEN                 (2)
#define BMA2x2_FIFO_DATA_SELECT_MSK                 (0x03)
#define BMA2x2_FIFO_DATA_SELECT_REG                 BMA2x2_FIFO_MODE_ADDR
/****************************************************/
/**\name   FIFO MODE      */
/***************************************************/
#define BMA2x2_FIFO_MODE_POS                 (6)
#define BMA2x2_FIFO_MODE_LEN                 (2)
#define BMA2x2_FIFO_MODE_MSK                 (0xC0)
#define BMA2x2_FIFO_MODE_REG                 BMA2x2_FIFO_MODE_ADDR

/****************************************************/
/**\name  BITSLICE FUNCTIONS      */
/***************************************************/
#define BMA2x2_GET_BITSLICE(regvar, bitname)\
((regvar & bitname##_MSK) >> bitname##_POS)


#define BMA2x2_SET_BITSLICE(regvar, bitname, val)\
((regvar & ~bitname##_MSK) | ((val<<bitname##_POS)&bitname##_MSK))

/****************************************************/
/**\name   CONSTANTS      */
/***************************************************/
/****************************************************/
/**\name  RESOLUTION SELECTION      */
/***************************************************/
/* Definitions used for accel resolution bit shifting*/
#define BMA2x2_14_BIT_SHIFT     (0xFC)
/**< It refers 14bit accel resolution*/
#define BMA2x2_10_BIT_SHIFT     (0xC0)
/**< It refers 10bit accel resolution*/
#define BMA2x2_12_BIT_SHIFT     (0xF0)
/**< It refers 12bit accel resolution*/
#define BANDWIDTH_DEFINE        (0xFB)
/**< Chip id set for accel bandwidth define*/

/****************************************************/
/**\name  ENABLE DISABLE SELECTION     */
/***************************************************/
#define INTR_ENABLE (0X01)
/**< Enable selection for bit */
#define INTR_DISABLE    (0x00)
/**< Disable selection for bit */

/****************************************************/
/**\name  OUTPUT TYPE SELECT     */
/***************************************************/
#define OPEN_DRAIN  (0x01)
/**< It refers open drain selection*/
#define PUSS_PULL   (0x01)
/**< It refers push pull selection*/

/****************************************************/
/**\name  LEVEL SELECT     */
/***************************************************/
#define ACTIVE_LOW  (0x00)
/**< It refers active low selection*/
#define ACTIVE_HIGH (0x01)
/**< It refers active high selection*/

/****************************************************/
/**\name  STATUS SELECT     */
/***************************************************/
#define BMA2x2_STAT1                             (0)
/**< It refers Status interrupt1 */
#define BMA2x2_STAT2                             (1)
/**< It refers Status interrupt2 */
#define BMA2x2_STAT3                             (2)
/**< It refers Status interrupt3  */
#define BMA2x2_STAT4                             (3)
/**< It refers Status interrupt4  */
#define BMA2x2_STAT5                             (4)
/**< It refers Status interrupt5  */

/****************************************************/
/**\name  RANGE AND BANDWIDTH SELECT     */
/***************************************************/
#define BMA2x2_RANGE_2G                 (3)
/**< sets range to +/- 2G mode */
#define BMA2x2_RANGE_4G                 (5)
/**< sets range to +/- 4G mode */
#define BMA2x2_RANGE_8G                 (8)
/**< sets range to +/- 8G mode */
#define BMA2x2_RANGE_16G                (12)
/**< sets range to +/- 16G mode */


#define BMA2x2_BW_7_81HZ        (0x08)
/**< sets bandwidth to LowPass 7.81HZ  */
#define BMA2x2_BW_15_63HZ       (0x09)
/**< sets bandwidth to LowPass 15.63HZ  */
#define BMA2x2_BW_31_25HZ       (0x0A)
/**< sets bandwidth to LowPass 31.25HZ  */
#define BMA2x2_BW_62_50HZ       (0x0B)
/**< sets bandwidth to LowPass 62.50HZ  */
#define BMA2x2_BW_125HZ         (0x0C)
/**< sets bandwidth to LowPass 125HZ  */
#define BMA2x2_BW_250HZ         (0x0D)
/**< sets bandwidth to LowPass 250HZ  */
#define BMA2x2_BW_500HZ         (0x0E)
/**< sets bandwidth to LowPass 500HZ  */
#define BMA2x2_BW_1000HZ        (0x0F)
/**< sets bandwidth to LowPass 1000HZ  */

/******************************************/
/**\name  SLEEP DURATION SELECT     */
/******************************************/
#define BMA2x2_SLEEP_DURN_0_5MS        (0x05)
/* sets sleep duration to 0.5 ms  */
#define BMA2x2_SLEEP_DURN_1MS          (0x06)
/* sets sleep duration to 1 ms */
#define BMA2x2_SLEEP_DURN_2MS          (0x07)
/* sets sleep duration to 2 ms */
#define BMA2x2_SLEEP_DURN_4MS          (0x08)
/* sets sleep duration to 4 ms */
#define BMA2x2_SLEEP_DURN_6MS          (0x09)
/* sets sleep duration to 6 ms*/
#define BMA2x2_SLEEP_DURN_10MS         (0x0A)
/* sets sleep duration to 10 ms */
#define BMA2x2_SLEEP_DURN_25MS         (0x0B)
/* sets sleep duration to 25 ms */
#define BMA2x2_SLEEP_DURN_50MS         (0x0C)
/* sets sleep duration to 50 ms */
#define BMA2x2_SLEEP_DURN_100MS        (0x0D)
/* sets sleep duration to 100 ms */
#define BMA2x2_SLEEP_DURN_500MS        (0x0E)
/* sets sleep duration to 500 ms */
#define BMA2x2_SLEEP_DURN_1S           (0x0F)
/* sets sleep duration to 1 s */

/******************************************/
/**\name  LATCH DURATION     */
/******************************************/
#define BMA2x2_LATCH_DURN_NON_LATCH    (0x00)
/* sets LATCH duration to NON LATCH  */
#define BMA2x2_LATCH_DURN_250MS        (0x01)
/* sets LATCH duration to 250 ms */
#define BMA2x2_LATCH_DURN_500MS        (0x02)
/* sets LATCH duration to 500 ms */
#define BMA2x2_LATCH_DURN_1S           (0x03)
/* sets LATCH duration to 1 s */
#define BMA2x2_LATCH_DURN_2S           (0x04)
/* sets LATCH duration to 2 s*/
#define BMA2x2_LATCH_DURN_4S           (0x05)
/* sets LATCH duration to 4 s */
#define BMA2x2_LATCH_DURN_8S           (0x06)
/* sets LATCH duration to 8 s */
#define BMA2x2_LATCH_DURN_LATCH        (0x07)
/* sets LATCH duration to LATCH */
#define BMA2x2_LATCH_DURN_NON_LATCH1   (0x08)
/* sets LATCH duration to NON LATCH1 */
#define BMA2x2_LATCH_DURN_250US        (0x09)
/* sets LATCH duration to 250 Us */
#define BMA2x2_LATCH_DURN_500US        (0x0A)
/* sets LATCH duration to 500 Us */
#define BMA2x2_LATCH_DURN_1MS          (0x0B)
/* sets LATCH duration to 1 Ms */
#define BMA2x2_LATCH_DURN_12_5MS       (0x0C)
/* sets LATCH duration to 12.5 Ms */
#define BMA2x2_LATCH_DURN_25MS         (0x0D)
/* sets LATCH duration to 25 Ms */
#define BMA2x2_LATCH_DURN_50MS         (0x0E)
/* sets LATCH duration to 50 Ms */
#define BMA2x2_LATCH_DURN_LATCH1       (0x0F)
/* sets LATCH duration to LATCH*/

/******************************************/
/**\name  MODE SETTINGS     */
/******************************************/
#define BMA2x2_MODE_NORMAL             (0)
#define BMA2x2_MODE_LOWPOWER1          (1)
#define BMA2x2_MODE_SUSPEND            (2)
#define BMA2x2_MODE_DEEP_SUSPEND       (3)
#define BMA2x2_MODE_LOWPOWER2          (4)
#define BMA2x2_MODE_STANDBY            (5)

/******************************************/
/**\name  AXIS SELECTION     */
/******************************************/
#define BMA2x2_X_AXIS           (0)
/**< It refers BMA2x2 X-axis */
#define BMA2x2_Y_AXIS           (1)
/**< It refers BMA2x2 Y-axis */
#define BMA2x2_Z_AXIS           (2)
/**< It refers BMA2x2 Z-axis */

/******************************************/
/**\name  INTERRUPT TYPE SELECTION     */
/******************************************/
#define BMA2x2_LOW_G_INTR       (0)
/**< enable/disable low-g interrupt*/
#define BMA2x2_HIGH_G_X_INTR    (1)
/**< enable/disable high_g X interrupt*/
#define BMA2x2_HIGH_G_Y_INTR    (2)
/**< enable/disable high_g Y interrupt*/
#define BMA2x2_HIGH_G_Z_INTR    (3)
/**< enable/disable high_g Z interrupt*/
#define BMA2x2_DATA_ENABLE      (4)
/**< enable/disable data interrupt*/
#define BMA2x2_SLOPE_X_INTR     (5)
/**< enable/disable slope X interrupt*/
#define BMA2x2_SLOPE_Y_INTR     (6)
/**< enable/disable slope X interrupt*/
#define BMA2x2_SLOPE_Z_INTR     (7)
/**< enable/disable slope X interrupt*/
#define BMA2x2_SINGLE_TAP_INTR  (8)
/**< enable/disable single tap interrupt*/
#define BMA2x2_DOUBLE_TAP_INTR  (9)
/**< enable/disable double tap interrupt*/
#define BMA2x2_ORIENT_INTR      (10)
/**< enable/disable orient interrupt*/
#define BMA2x2_FLAT_INTR        (11)
/**< enable/disable flat interrupt*/
#define BMA2x2_FIFO_FULL_INTR   (12)
/**< enable/disable fifo full interrupt*/
#define BMA2x2_FIFO_WM_INTR     (13)
/**< enable/disable fifo water mark interrupt*/

/******************************************/
/**\name  INTERRUPTS PADS     */
/******************************************/
#define BMA2x2_INTR1_LOW_G             (0)
/**< disable low-g interrupt*/
#define BMA2x2_INTR2_LOW_G             (1)
/**< enable low-g interrupt*/
#define BMA2x2_INTR1_HIGH_G            (0)
/**< disable high-g interrupt*/
#define BMA2x2_INTR2_HIGH_G            (1)
/**< enable high-g interrupt*/
#define BMA2x2_INTR1_SLOPE             (0)
/**< disable slope interrupt*/
#define BMA2x2_INTR2_SLOPE             (1)
/**< enable slope interrupt*/
#define BMA2x2_INTR1_SLOW_NO_MOTION    (0)
/**< disable slow no motion interrupt*/
#define BMA2x2_INTR2_SLOW_NO_MOTION    (1)
/**< enable slow no motion  interrupt*/
#define BMA2x2_INTR1_DOUBLE_TAP        (0)
/**< disable double tap  interrupt*/
#define BMA2x2_INTR2_DOUBLE_TAP        (1)
/**< enable double tap  interrupt*/
#define BMA2x2_INTR1_SINGLE_TAP        (0)
/**< disable single tap  interrupt*/
#define BMA2x2_INTR2_SINGLE_TAP        (1)
/**< enable single tap  interrupt*/
#define BMA2x2_INTR1_ORIENT            (0)
/**< disable orient  interrupt*/
#define BMA2x2_INTR2_ORIENT            (1)
/**< enable orient  interrupt*/
#define BMA2x2_INTR1_FLAT              (0)
/**< disable flat  interrupt*/
#define BMA2x2_INTR2_FLAT              (1)
/**< enable flat  interrupt*/
#define BMA2x2_INTR1_NEWDATA           (0)
/**< disable data  interrupt*/
#define BMA2x2_INTR2_NEWDATA           (1)
/**< enable data interrupt*/
#define BMA2x2_INTR1_FIFO_WM           (0)
/**< disable fifo watermark  interrupt*/
#define BMA2x2_INTR2_FIFO_WM           (1)
/**< enable fifo watermark  interrupt*/
#define BMA2x2_INTR1_FIFO_FULL         (0)
/**< disable fifo full  interrupt*/
#define BMA2x2_INTR2_FIFO_FULL         (1)
/**< enable fifo full  interrupt*/

/******************************************/
/**\name  SOURCE REGISTER     */
/******************************************/
#define BMA2x2_SOURCE_LOW_G            (0)
#define BMA2x2_SOURCE_HIGH_G           (1)
#define BMA2x2_SOURCE_SLOPE            (2)
#define BMA2x2_SOURCE_SLOW_NO_MOTION   (3)
#define BMA2x2_SOURCE_TAP              (4)
#define BMA2x2_SOURCE_DATA             (5)

#define BMA2x2_INTR1_OUTPUT      (0)
#define BMA2x2_INTR2_OUTPUT      (1)
#define BMA2x2_INTR1_LEVEL       (0)
#define BMA2x2_INTR2_LEVEL       (1)

/******************************************/
/**\name  DURATION     */
/******************************************/
#define BMA2x2_LOW_DURN                (0)
#define BMA2x2_HIGH_DURN               (1)
#define BMA2x2_SLOPE_DURN              (2)
#define BMA2x2_SLOW_NO_MOTION_DURN     (3)

/******************************************/
/**\name  THRESHOLD     */
/******************************************/
#define BMA2x2_LOW_THRES                (0)
#define BMA2x2_HIGH_THRES               (1)
#define BMA2x2_SLOPE_THRES              (2)
#define BMA2x2_SLOW_NO_MOTION_THRES     (3)


#define BMA2x2_LOW_G_HYST                (0)
#define BMA2x2_HIGH_G_HYST               (1)

#define BMA2x2_ORIENT_THETA             (0)
#define BMA2x2_FLAT_THETA               (1)

#define BMA2x2_I2C_SELECT               (0)
#define BMA2x2_I2C_ENABLE               (1)
/******************************************/
/**\name  COMPENSATION     */
/******************************************/
#define BMA2x2_SLOW_COMP_X              (0)
#define BMA2x2_SLOW_COMP_Y              (1)
#define BMA2x2_SLOW_COMP_Z              (2)
/******************************************/
/**\name  OFFSET TRIGGER     */
/******************************************/
#define BMA2x2_CUT_OFF                  (0)
#define BMA2x2_OFFSET_TRIGGER_X         (1)
#define BMA2x2_OFFSET_TRIGGER_Y         (2)
#define BMA2x2_OFFSET_TRIGGER_Z         (3)
/******************************************/
/**\name  GP REGISTERS     */
/******************************************/
#define BMA2x2_GP0                      (0)
#define BMA2x2_GP1                      (1)
/******************************************/
/**\name  SLO NO MOTION REGISTER      */
/******************************************/
#define BMA2x2_SLOW_NO_MOTION_ENABLE_X          (0)
#define BMA2x2_SLOW_NO_MOTION_ENABLE_Y          (1)
#define BMA2x2_SLOW_NO_MOTION_ENABLE_Z          (2)
#define BMA2x2_SLOW_NO_MOTION_ENABLE_SELECT     (3)
/******************************************/
/**\name  WAKE UP      */
/******************************************/
#define BMA2x2_WAKE_UP_DURN_20MS         (0)
#define BMA2x2_WAKE_UP_DURN_80MS         (1)
#define BMA2x2_WAKE_UP_DURN_320MS        (2)
#define BMA2x2_WAKE_UP_DURN_2560MS       (3)


/* LG/HG thresholds are in LSB and depend on RANGE setting */
/* no range check on threshold calculation */

#define BMA2x2_SELFTEST0_ON            (1)
#define BMA2x2_SELFTEST1_ON            (2)

#define BMA2x2_EE_W_OFF                 (0)
#define BMA2x2_EE_W_ON                  (1)
/******************************************/
/**\name  RESOLUTION SETTINGS      */
/******************************************/
#define BMA2x2_RESOLUTION_12_BIT        (0)
#define BMA2x2_RESOLUTION_10_BIT        (1)
#define BMA2x2_RESOLUTION_14_BIT        (3)

/******************************************/
/**\name  CHIP ID SELECTION      */
/******************************************/
#define BMA2x2           (0x16)
#define BMA280           (0x17)
#define BMA222E          (0x18)
#define BMA250E          (0x19)
/******************************************/
/**\name  LOW-G MODE SELECTION    */
/******************************************/
#define LOW_G_SINGLE_AXIS_MODE      (0x00)
#define LOW_G_SUMMING_MODE      (0x01)
/******************************************/
/**\name TAP DURATION DEFINITION    */
/******************************************/
#define TAP_DURN_50_MS          (0x00)
#define TAP_DURN_100_MS         (0x01)
#define TAP_DURN_150_MS         (0x02)
#define TAP_DURN_200_MS         (0x03)
#define TAP_DURN_250_MS         (0x04)
#define TAP_DURN_375_MS         (0x05)
#define TAP_DURN_500_MS         (0x06)
#define TAP_DURN_700_MS         (0x07)
/******************************************/
/**\name TAP SHOCK DEFINITION    */
/******************************************/
#define TAP_SHOCK_50_MS     (0x00)
#define TAP_SHOCK_75_MS     (0x01)
/******************************************/
/**\name TAP QUIET DEFINITION    */
/******************************************/
#define TAP_QUIET_30_MS     (0x00)
#define TAP_QUIET_20_MS     (0x01)
/****************************************************/
/**\name    ARRAY SIZE DEFINITIONS      */
/***************************************************/
#define BMA2x2_ACCEL_DATA_SIZE          (2)
#define BMA2x2_ACCEL_XYZ_DATA_SIZE      (6)
#define BMA2x2_ACCEL_XYZ_TEMP_DATA_SIZE     (7)
/****************************************************/
/**\name    ARRAY PARAMETERS      */
/***************************************************/

#define BMA2x2_SENSOR_DATA_ACCEL_LSB    (0)
#define BMA2x2_SENSOR_DATA_ACCEL_MSB    (1)

#define BMA2x2_SENSOR_DATA_XYZ_X_LSB    (0)
#define BMA2x2_SENSOR_DATA_XYZ_X_MSB    (1)
#define BMA2x2_SENSOR_DATA_XYZ_Y_LSB    (2)
#define BMA2x2_SENSOR_DATA_XYZ_Y_MSB    (3)
#define BMA2x2_SENSOR_DATA_XYZ_Z_LSB    (4)
#define BMA2x2_SENSOR_DATA_XYZ_Z_MSB    (5)
#define BMA2x2_SENSOR_DATA_TEMP     (6)

#define BMA2x2_RESOLUTION_12_MASK       (0xF0)
#define BMA2x2_RESOLUTION_10_MASK       (0xC0)
#define BMA2x2_RESOLUTION_14_MASK       (0xFC)

#define BMA2x2_POWER_MODE_HEX_E_ZERO_MASK   (0xE0)
#define BMA2x2_POWER_MODE_HEX_4_ZERO_MASK   (0x40)
#define BMA2x2_POWER_MODE_HEX_ZERO_ZERO_MASK    (0x00)
#define BMA2x2_POWER_MODE_HEX_ZERO_ONE_MASK (0x01)
#define BMA2x2_POWER_MODE_HEX_ZERO_TWO_MASK (0x02)
#define BMA2x2_POWER_MODE_HEX_ZERO_FOUR_MASK    (0x04)
#define BMA2x2_POWER_MODE_HEX_ZERO_SIX_MASK (0x06)

/** Macro to convert floating point
low-g-thresholds in G to 8-bit register values.<br>
  * Example: BMA2x2_LOW_TH_IN_G( 0.3, 2.0) generates
  * the register value for 0.3G threshold in 2G mode.
  * \brief convert g-values to 8-bit value
 */
#define BMA2x2_LOW_THRES_IN_G(gthres, range)  ((256 * gthres) / range)

/** Macro to convert floating point high-g-thresholds
    in G to 8-bit register values.<br>
  * Example: BMA2x2_HIGH_TH_IN_G( 1.4, 2.0)
  * generates the register value for 1.4G threshold in 2G mode.
  * \brief convert g-values to 8-bit value
 */
#define BMA2x2_HIGH_THRES_IN_G(gthres, range)   ((256 * gthres) / range)

/** Macro to convert floating point low-g-hysteresis
in G to 8-bit register values.<br>
  * Example: BMA2x2_LOW_HY_IN_G( 0.2, 2.0)
  *generates the register value for 0.2G threshold in 2G mode.
  * \brief convert g-values to 8-bit value
 */
#define BMA2x2_LOW_HYST_IN_G(ghyst, range)   ((32 * ghyst) / range)

/** Macro to convert floating point high-g-hysteresis
   in G to 8-bit register values.<br>
  * Example: BMA2x2_HIGH_HY_IN_G( 0.2, 2.0) generates
  *the register value for 0.2G threshold in 2G mode.
  * \brief convert g-values to 8-bit value
 */
#define BMA2x2_HIGH_HYST_IN_G(ghyst, range)    ((32 * ghyst) / range)


/** Macro to convert floating point G-thresholds
    to 8-bit register values<br>
  * Example: BMA2x2_SLOPE_TH_IN_G( 1.2, 2.0)
  * generates the register value for 1.2G threshold in 2G mode.
  * \brief convert g-values to 8-bit value
 */

#define BMA2x2_SLOPE_THRES_IN_G(gthres, range)    ((128 * gthres) / range)
/******************************************/
/**\name FUNCTION DECLARATION  */
/******************************************/
/******************************************/
/**\name FUNCTION FOR COMMON READ AND WRITE   */
/******************************************/
/*!
 * @brief
 *  This API reads the data from
 *  the given register continuously
 *
 *
 *  @param addr_u8 -> Address of the register
 *  @param data_u8 -> The data from the register
 *  @param len_u32 -> no of bytes to read
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_burst_read(u8 addr_u8,
        u8 *data_u8, u32 len_u32);
/******************************************/
/**\name FUNCTION FOR INTIALIZE  */
/******************************************/
/*!
 *  @brief
 *  This function is used for initialize
 *  bus read and bus write functions
 *  assign the chip id and device address
 *  chip id is read in the register 0x00 bit from 0 to 7
 *
 *  @param bma2x2 : structure pointer
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *  @note
 *  While changing the parameter of the bma2x2_t
 *  consider the following point:
 *  Changing the reference value of the parameter
 *  will changes the local copy or local reference
 *  make sure your changes will not
 *  affect the reference value of the parameter
 *  (Better case don't change the reference value of the parameter)
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_init(struct bma2x2_t *bma2x2);
/*!
 * @brief
 *  This API gives data to the given register and
 *  the data is written in the corresponding register address
 *
 *
 *  @param adr_u8  -> Address of the register
 *  @param data_u8 -> The data to the register
 *  @param len_u8 -> no of bytes to read
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_write_reg(u8 adr_u8,
        u8 *data_u8, u8 len_u8);
/*!
 * @brief This API reads the data from
 *           the given register address
 *
 *
 *  @param adr_u8 -> Address of the register
 *  @param data_u8 -> The data from the register
 *  @param len_u8 -> no of bytes to read
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_read_reg(u8 adr_u8,
        u8 *data_u8, u8 len_u8);
/******************************************/
/**\name FUNCTION FOR   DATA READ*/
/******************************************/
/*!
 * @brief
 *  This API reads acceleration data X values
 *  from location 02h and 03h
 *
 *
 *  @param   accel_x_s16 : pointer holding the data of accel X
 *             value       |   resolution
 *       ----------------- | --------------
 *              0          | BMA2x2_12_RESOLUTION
 *              1          | BMA2x2_10_RESOLUTION
 *              2          | BMA2x2_14_RESOLUTION
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_read_accel_x(s16 *accel_x_s16);
/*!
 * @brief
 *  This API reads acceleration data X values
 *  from location 02h and 03h bit resolution support 8bit
 *
 *
 *  @param   accel_x_s8 : pointer holding the data of accel X
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_read_accel_eight_resolution_x(
    s8 *accel_x_s8);
/*!
 * @brief
 *  This API reads acceleration data Y values
 *  from location 04h and 05h
 *
 *  @param   accel_y_s16 : pointer holding the data of accel Y
 *             value       |   resolution
 *       ----------------- | --------------
 *              0          | BMA2x2_12_RESOLUTION
 *              1          | BMA2x2_10_RESOLUTION
 *              2          | BMA2x2_14_RESOLUTION
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_read_accel_y(s16 *accel_y_s16);
/*!
 * @brief This API reads acceleration data Y values of
 * 8bit  resolution  from location 05h
 *
 *
 *
 *
 *  @param accel_y_s8   The data of y
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_read_accel_eight_resolution_y(
    s8 *accel_y_s8);
/*!
 * @brief This API reads acceleration data Z values
 *                          from location 06h and 07h
 *
 *
 *  @param   accel_z_s16 : pointer holding the data of accel Z
 *             value       |   resolution
 *       ----------------- | --------------
 *              0          | BMA2x2_12_RESOLUTION
 *              1          | BMA2x2_10_RESOLUTION
 *              2          | BMA2x2_14_RESOLUTION
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_read_accel_z(s16 *accel_z_s16);
/*!
 * @brief
 *  This API reads acceleration data Z values of
 *  8bit  resolution  from location 07h
 *
 *
 *
 *
 *  \@aram  accel_z_s8 : the data of z
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_read_accel_eight_resolution_z(
    s8 *accel_z_s8);
/*!
 *  @brief This API reads acceleration data X,Y,Z values
 *  from location 02h to 07h
 *
 *  @param accel : pointer holding the data of accel
 *             value       |   resolution
 *       ----------------- | --------------
 *              0          | BMA2x2_12_RESOLUTION
 *              1          | BMA2x2_10_RESOLUTION
 *              2          | BMA2x2_14_RESOLUTION
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_read_accel_xyz(
    struct bma2x2_accel_data *accel);
/*!
 * @brief This API reads acceleration of 8 bit resolution
 * data of X,Y,Z values
 * from location 03h , 05h and 07h
 *
 *
 *
 *
 *  @param accel : pointer holding the data of accel
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_read_accel_eight_resolution_xyz(
    struct bma2x2_accel_eight_resolution *accel);
/******************************************/
/**\name FUNCTION FOR INTERRUPT STATUS*/
/******************************************/
/*!
 *  @brief This API read tap-sign, tap-first-xyz
 *  slope-sign, slope-first-xyz status register byte
 *  from location 0Bh
 *
 *   @param stat_tap_u8 : The status of tap and slope
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_tap_stat(
    u8 *stat_tap_u8);
/*!
 *  @brief This API read orient, high-sign and high-first-xyz
 *  status register byte from location 0Ch
 *
 *
 *  @param stat_orient_u8 : The status of orient and high
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_orient_stat(
    u8 *stat_orient_u8);
/*!
 *  @brief This API reads fifo overrun and fifo frame counter
 *  status register byte  from location 0Eh
 *
 *  @param stat_fifo_u8 : The status of fifo overrun and frame counter
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_fifo_stat(
    u8 *stat_fifo_u8);
/*!
 *  @brief This API read fifo frame count
 *  from location 0Eh bit position 0 to 6
 *
 *
 * @param frame_count_u8 : The status of fifo frame count
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_fifo_frame_count(
    u8 *frame_count_u8);
/*!
 *  @brief This API read fifo overrun
 *  from location 0Eh bit position 7
 *
 *
 * @param fifo_overrun_u8 : The status of fifo overrun
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_fifo_overrun(
    u8 *fifo_overrun_u8);
/******************************************/
/**\name FUNCTION FOR  RANGE */
/******************************************/
/*!
 *  @brief This API read interrupt status of flat, orient, single tap,
 *  double tap, slow no motion, slope, highg and lowg from location 09h
 *
 *
 *
 *  @param  intr_stat_u8 : The value of interrupt status
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_stat(
    u8 *intr_stat_u8);
/*!
 * @brief This API is used to get the ranges(g values) of the sensor
 *  in the register 0x0F bit from 0 to 3
 *
 *
 *  @param range_u8 : The value of range
 *        range_u8       |   result
 *       ----------------- | --------------
 *              0x03       | BMA2x2_RANGE_2G
 *              0x05       | BMA2x2_RANGE_4G
 *              0x08       | BMA2x2_RANGE_8G
 *              0x0C       | BMA2x2_RANGE_16G
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_range(u8 *range_u8);
/*!
 * @brief This API is used to set the ranges(g values) of the sensor
 *  in the register 0x0F bit from 0 to 3
 *
 *
 *  @param range_u8 : The value of range
 *        range_u8       |   result
 *       ----------------- | --------------
 *              0x03       | BMA2x2_RANGE_2G
 *              0x05       | BMA2x2_RANGE_4G
 *              0x08       | BMA2x2_RANGE_8G
 *              0x0C       | BMA2x2_RANGE_16G
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_range(u8 range_u8);
/******************************************/
/**\name FUNCTION FOR   BANDWIDTH*/
/******************************************/
/*!
 *  @brief This API is used to get the bandwidth of the sensor in the register
 *  0x10 bit from 0 to 4
 *
 *
 *  @param bw_u8 : The value of bandwidth
 *        bw_u8          |   result
 *       ----------------- | --------------
 *              0x08       | BMA2x2_BW_7_81HZ
 *              0x09       | BMA2x2_BW_15_63HZ
 *              0x0A       | BMA2x2_BW_31_25HZ
 *              0x0B       | BMA2x2_BW_62_50HZ
 *              0x0C       | BMA2x2_BW_125HZ
 *              0x0D       | BMA2x2_BW_250HZ
 *              0x0E       | BMA2x2_BW_500HZ
 *              0x0F       | BMA2x2_BW_1000HZ
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_bw(u8 *bw_u8);
/*!
 *  @brief This API is used to set the bandwidth of the sensor in the register
 *  0x10 bit from 0 to 4
 *
 *
 *  @param bw_u8 : The value of bandwidth
 *        bw_u8          |   result
 *       ----------------- | --------------
 *              0x08       | BMA2x2_BW_7_81HZ
 *              0x09       | BMA2x2_BW_15_63HZ
 *              0x0A       | BMA2x2_BW_31_25HZ
 *              0x0B       | BMA2x2_BW_62_50HZ
 *              0x0C       | BMA2x2_BW_125HZ
 *              0x0D       | BMA2x2_BW_250HZ
 *              0x0E       | BMA2x2_BW_500HZ
 *              0x0F       | BMA2x2_BW_1000HZ
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_bw(u8 bw_u8);
/******************************************/
/**\name FUNCTION FOR   POWER MODE*/
/******************************************/
/*!
 *  @brief This API is used to get the operating
 *  modes of the sensor in the register 0x11 and 0x12
 *  @note Register 0x11 - bit from 5 to 7
 *  @note Register 0x12 - bit from 5 and 6
 *
 *
 *  @param power_mode_u8 : The value of power mode
 *  power_mode_u8           |value  |   0x11  |   0x12
 *  ------------------------- |-------| --------|--------
 *  BMA2x2_MODE_NORMAL        |  0    |  0x00   |  0x00
 *  BMA2x2_MODE_LOWPOWER1     |  1    |  0x02   |  0x00
 *  BMA2x2_MODE_SUSPEND       |  2    |  0x06   |  0x00
 *  BMA2x2_MODE_DEEP_SUSPEND  |  3    |  0x01   |  0x00
 *  BMA2x2_MODE_LOWPOWER2     |  4    |  0x02   |  0x01
 *  BMA2x2_MODE_STANDBY       |  5    |  0x04   |  0x00
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_power_mode(
    u8 *power_mode_u8);
/*!
 *  @brief This API is used to set the operating
 *  modes of the sensor in the register 0x11 and 0x12
 *  @note Register 0x11 - bit from 5 to 7
 *  @note Register 0x12 - bit from 5 and 6
 *
 *
 *  @param power_mode_u8 : The value of power mode
 *  power_mode_u8           |value  |   0x11  |   0x12
 *  ------------------------- |-------| --------|--------
 *  BMA2x2_MODE_NORMAL        |  0    |  0x00   |  0x00
 *  BMA2x2_MODE_LOWPOWER1     |  1    |  0x02   |  0x00
 *  BMA2x2_MODE_SUSPEND       |  2    |  0x06   |  0x00
 *  BMA2x2_MODE_DEEP_SUSPEND  |  3    |  0x01   |  0x00
 *  BMA2x2_MODE_LOWPOWER2     |  4    |  0x02   |  0x01
 *  BMA2x2_MODE_STANDBY       |  5    |  0x04   |  0x00
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_power_mode(u8 power_mode_u8);
/*!
 *  @brief This API is used to assign the power mode values
 *  modes of the sensor in the register 0x11 and 0x12
 *  @note Register 0x11 - bit from 5 to 7
 *  @note Register 0x12 - bit from 5 and 6
 *
 *
 *  @param power_mode_u8 : The value of power mode
 *  power_mode_u8           |value  |   0x11  |   0x12
 *  ------------------------- |-------| --------|--------
 *  BMA2x2_MODE_NORMAL        |  0    |  0x00   |  0x00
 *  BMA2x2_MODE_LOWPOWER1     |  1    |  0x02   |  0x00
 *  BMA2x2_MODE_SUSPEND       |  2    |  0x06   |  0x00
 *  BMA2x2_MODE_DEEP_SUSPEND  |  3    |  0x01   |  0x00
 *  BMA2x2_MODE_LOWPOWER2     |  4    |  0x02   |  0x01
 *  BMA2x2_MODE_STANDBY       |  5    |  0x04   |  0x00
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_mode_value(u8 power_mode_u8);
/******************************************/
/**\name FUNCTION FOR  SLEEP CONFIGURATION */
/******************************************/
/*!
 *  @brief This API is used to get
 *  the sleep duration of the sensor in the register 0x11
 *  Register 0x11 - bit from 0 to 3
 *
 *
 *
 *
 *  @param  sleep_durn_u8 : The value of sleep duration time
 *        sleep_durn_u8  |   result
 *       ----------------- | ----------------------
 *              0x05       | BMA2x2_SLEEP_DURN_0_5MS
 *              0x06       | BMA2x2_SLEEP_DURN_1MS
 *              0x07       | BMA2x2_SLEEP_DURN_2MS
 *              0x08       | BMA2x2_SLEEP_DURN_4MS
 *              0x09       | BMA2x2_SLEEP_DURN_6MS
 *              0x0A       | BMA2x2_SLEEP_DURN_10MS
 *              0x0B       | BMA2x2_SLEEP_DURN_25MS
 *              0x0C       | BMA2x2_SLEEP_DURN_50MS
 *              0x0D       | BMA2x2_SLEEP_DURN_100MS
 *              0x0E       | BMA2x2_SLEEP_DURN_500MS
 *              0x0F       | BMA2x2_SLEEP_DURN_1S
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_sleep_durn(u8 *sleep_durn_u8);
/*!
 *  @brief This API is used to set
 *  the sleep duration of the sensor in the register 0x11
 *  Register 0x11 - bit from 0 to 3
 *
 *
 *
 *
 *  @param  sleep_durn_u8 : The value of sleep duration time
 *        sleep_durn_u8  |   result
 *       ----------------- | ----------------------
 *              0x05       | BMA2x2_SLEEP_DURN_0_5MS
 *              0x06       | BMA2x2_SLEEP_DURN_1MS
 *              0x07       | BMA2x2_SLEEP_DURN_2MS
 *              0x08       | BMA2x2_SLEEP_DURN_4MS
 *              0x09       | BMA2x2_SLEEP_DURN_6MS
 *              0x0A       | BMA2x2_SLEEP_DURN_10MS
 *              0x0B       | BMA2x2_SLEEP_DURN_25MS
 *              0x0C       | BMA2x2_SLEEP_DURN_50MS
 *              0x0D       | BMA2x2_SLEEP_DURN_100MS
 *              0x0E       | BMA2x2_SLEEP_DURN_500MS
 *              0x0F       | BMA2x2_SLEEP_DURN_1S
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_sleep_durn(u8 sleep_durn_u8);
/*!
 * @brief This API is used to get the sleep timer mode
 *  in the register 0x12 bit 5
 *
 *
 *
 *
 *  @param  sleep_timer_u8 : The value of sleep timer mode
 *        sleep_timer_u8 |   result
 *       ----------------- | ----------------------
 *              0          | enable EventDrivenSampling(EDT)
 *              1          | enable Equidistant sampling mode(EST)
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_sleep_timer_mode(
    u8 *sleep_timer_u8);
/*!
 * @brief This API is used to set the sleep timer mode
 *  in the register 0x12 bit 5
 *
 *
 *
 *
 *  @param  sleep_timer_u8 : The value of sleep timer mode
 *        sleep_timer_u8 |   result
 *       ----------------- | ----------------------
 *              0          | enable EventDrivenSampling(EDT)
 *              1          | enable Equidistant sampling mode(EST)
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_sleep_timer_mode(u8 sleep_timer_u8);
/******************************************/
/**\name FUNCTION FOR   HIGH BANDWIDTH*/
/******************************************/
/*!
 * @brief This API is used to get high bandwidth
 *      in the register 0x13 bit 7
 *
 *  @param  high_bw_u8 : The value of high bandwidth
 *         high_bw_u8    |   result
 *       ----------------- | ----------------------
 *              0          | Unfiltered High Bandwidth
 *              1          | Filtered Low Bandwidth
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_high_bw(u8 *high_bw_u8);
/*!
 * @brief This API is used to write high bandwidth
 *      in the register 0x13 bit 7
 *
 *  @param  high_bw_u8 : The value of high bandwidth
 *         high_bw_u8    |   result
 *       ----------------- | ----------------------
 *              0          | Unfiltered High Bandwidth
 *              1          | Filtered Low Bandwidth
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_high_bw(u8 high_bw_u8);
/*!
 *  @brief This API is used to get shadow dis
 *  in the register 0x13 bit 6
 *
 *  @param  shadow_dis_u8 : The value of shadow dis
 *        shadow_dis_u8  |   result
 *       ----------------- | ------------------
 *              0          | MSB is Locked
 *              1          | No MSB Locking
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_shadow_dis(u8 *shadow_dis_u8);
/*!
 *  @brief This API is used to set shadow dis
 *  in the register 0x13 bit 6
 *
 *  @param  shadow_dis_u8 : The value of shadow dis
 *        shadow_dis_u8  |   result
 *       ----------------- | ------------------
 *              0          | MSB is Locked
 *              1          | No MSB Locking
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_shadow_dis(u8 shadow_dis_u8);
/******************************************/
/**\name FUNCTION FOR  SOFT RESET */
/******************************************/
/*!
 *  @brief This function is used for the soft reset
 *  The soft reset register will be written
 *  with 0xB6 in the register 0x14.
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_soft_rst(void);
/*!
 * @brief This API is used to update the register values
 *
 *
 *
 *
 *  @param : None
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_update_image(void);
/******************************************/
/**\name FUNCTION FOR  INTERRUPT ENABLE */
/******************************************/
/*!
 *  @brief This API is used to get
 *  interrupt enable bits of the sensor in the registers 0x16 and 0x17
 *  @note It reads the flat enable, orient enable,
 *  @note single tap enable, double tap enable
 *  @note slope-x enable, slope-y enable, slope-z enable,
 *  @note fifo watermark enable,
 *  @note fifo full enable, data enable, low-g enable,
 *  @note high-z enable, high-y enable
 *  @note high-z enable
 *
 *
 *
 *  @param intr_type_u8: The value of interrupts
 *        intr_type_u8   |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_LOW_G_INTR
 *              1          | BMA2x2_HIGH_G_X_INTR
 *              2          | BMA2x2_HIGH_G_Y_INTR
 *              3          | BMA2x2_HIGH_G_Z_INTR
 *              4          | BMA2x2_DATA_ENABLE
 *              5          | SLOPE_X_INTR
 *              6          | SLOPE_Y_INTR
 *              7          | SLOPE_Z_INTR
 *              8          | SINGLE_TAP_INTR
 *              9          | SINGLE_TAP_INTR
 *              10         | ORIENT_INT
 *              11         | FLAT_INT
 *
 *  @param value_u8 : The value of interrupts enable
 *        value_u8       |   result
 *       ----------------- | ------------------
 *              0x00       | INTR_DISABLE
 *              0x01       | INTR_ENABLE
 *
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_enable(u8 intr_type_u8,
        u8 *value_u8);
/*!
 *  @brief This API is used to set
 *  interrupt enable bits of the sensor in the registers 0x16 and 0x17
 *  @note It reads the flat enable, orient enable,
 *  @note single tap enable, double tap enable
 *  @note slope-x enable, slope-y enable, slope-z enable,
 *  @note fifo watermark enable,
 *  @note fifo full enable, data enable, low-g enable,
 *  @note high-z enable, high-y enable
 *  @note high-z enable
 *
 *
 *
 *  @param intr_type_u8: The value of interrupts
 *        intr_type_u8   |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_LOW_G_INTR
 *              1          | BMA2x2_HIGH_G_X_INTR
 *              2          | BMA2x2_HIGH_G_Y_INTR
 *              3          | BMA2x2_HIGH_G_Z_INTR
 *              4          | BMA2x2_DATA_ENABLE
 *              5          | SLOPE_X_INTR
 *              6          | SLOPE_Y_INTR
 *              7          | SLOPE_Z_INTR
 *              8          | SINGLE_TAP_INTR
 *              9          | SINGLE_TAP_INTR
 *              10         | ORIENT_INT
 *              11         | FLAT_INT
 *
 *  @param value_u8 : The value of interrupts enable
 *        value_u8       |   result
 *       ----------------- | ------------------
 *              0x00       | INTR_DISABLE
 *              0x01       | INTR_ENABLE
 *
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr_enable(u8 intr_type_u8,
        u8 value_u8);
/*!
 *  @brief This API is used to get
 *  the interrupt fifo full enable interrupt status
 *  in the register 0x17 bit 5
 *
 *
 *  @param fifo_full_u8 The value of fifo full interrupt enable
 *        fifo_full_u8   |   result
 *       ----------------- | ------------------
 *              0x00       | INTR_DISABLE
 *              0x01       | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_fifo_full(u8 *fifo_full_u8);
/*!
 *  @brief This API is used to set
 *  the interrupt fifo full enable interrupt status
 *  in the register 0x17 bit 5
 *
 *
 *  @param fifo_full_u8 The value of fifo full interrupt enable
 *        fifo_full_u8   |   result
 *       ----------------- | ------------------
 *              0x00       | INTR_DISABLE
 *              0x01       | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr_fifo_full(u8 fifo_full_u8);
/*!
 * @brief This API is used to get
 *  the interrupt fifo watermark enable interrupt status
 *  in the register 0x17 bit 6
 *
 *
 *
 *
 *  @param fifo_wm_u8 : the value FIFO Water Mark
 *        fifo_wm_u8     |   result
 *       ----------------- | ------------------
 *              0x00       | INTR_DISABLE
 *              0x01       | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_fifo_wm(u8 *fifo_wm_u8);
/*!
 * @brief This API is used to set
 *  the interrupt fifo watermark enable interrupt status
 *  in the register 0x17 bit 6
 *
 *
 *
 *
 *  @param fifo_wm_u8 : the value FIFO Water Mark
 *        fifo_wm_u8     |   result
 *       ----------------- | ------------------
 *              0x00       | INTR_DISABLE
 *              0x01       | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr_fifo_wm(u8 fifo_wm_u8);
/*!
 * @brief This API is used to get
 * the interrupt status of slow/no motion select and slow no motion
 * enable xyz interrupt in the register 0x18 bit from 0 to 3
 *
 *
 *  @param  channel_u8 : The value of slow/no motion select
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_SLOW_NO_MOTION_ENABLE_X
 *              1          | BMA2x2_ACCEL_SLOW_NO_MOTION_ENABLE_Y
 *              2          | BMA2x2_ACCEL_SLOW_NO_MOTION_ENABLE_Z
 *              3          | BMA2x2_ACCEL_SLOW_NO_MOTION_ENABLE_SEL
 *
 *  @param slow_no_motion_u8 : The value of slow no motion interrupt
 *      enable
 *        slow_no_motion_u8     |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_slow_no_motion(u8 channel_u8,
        u8 *slow_no_motion_u8);
/*!
 * @brief This API is used to set
 * the interrupt status of slow/no motion select and slow no motion
 * enable xyz interrupt in the register 0x18 bit from 0 to 3
 *
 *
 *  @param  channel_u8 : The value of slow/no motion select
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_SLOW_NO_MOTION_ENABLE_X
 *              1          | BMA2x2_ACCEL_SLOW_NO_MOTION_ENABLE_Y
 *              2          | BMA2x2_ACCEL_SLOW_NO_MOTION_ENABLE_Z
 *              3          | BMA2x2_ACCEL_SLOW_NO_MOTION_ENABLE_SEL
 *
 *  @param slow_no_motion_u8 : The value of slow no motion interrupt enable
 *        slow_no_motion_u8     |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_slow_no_motion(u8 channel_u8,
        u8 slow_no_motion_u8);
/*!
 * @brief  This API is used to get
 * the interrupt enable of low_g interrupt in the register 0x19 and 0x1B
 * @note INTR1_Low_g -> register 0x19 bit 0
 * @note INTR2_Low_g -> register 0x1B bit 0
 *
 *
 *
 *
 * @param channel_u8 : The value of low interrupt selection channel
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_LOW_G
 *              1          | BMA2x2_ACCEL_INTR2_LOW_G
 *
 * @param intr_low_g_u8 : the value of low_g interrupt
 *        intr_low_u8           |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_low_g(u8 channel_u8,
        u8 *intr_low_g_u8);
/*!
 * @brief  This API is used to set
 * the interrupt enable of low_g interrupt in the register 0x19 and 0x1B
 * @note INTR1_Low_g -> register 0x19 bit 0
 * @note INTR2_Low_g -> register 0x1B bit 0
 *
 *
 *
 *
 * @param channel_u8 : The value of low interrupt selection channel
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_LOW_G
 *              1          | BMA2x2_ACCEL_INTR2_LOW_G
 *
 * @param intr_low_u8 : the value of low_g interrupt
 *        intr_low_u8           |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr_low_g(u8 channel_u8,
        u8 intr_low_u8);
/*!
 * @brief This API is used to get
 * the interrupt enable of high_g interrupt in the register 0x19 and 0x1B
 * @note INTR1_high_g -> register 0x19 bit 1
 * @note INTR2_high_g -> register 0x1B bit 1
 *
 *
 *  @param  channel_u8: The value of high_g interrupt selection
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_HIGH_G
 *              1          | BMA2x2_ACCEL_INTR2_HIGH_G
 *
 * @param intr_high_g_u8 : the value of high_g interrupt
 *        intr_high_g_u8        |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_high_g(u8 channel_u8,
        u8 *intr_high_g_u8);
/*!
 * @brief This API is used to set
 * the interrupt enable of high_g interrupt in the register 0x19 and 0x1B
 * @note INTR1_high_g -> register 0x19 bit 1
 * @note INTR2_high_g -> register 0x1B bit 1
 *
 *
 *  @param  channel_u8: The value of high_g interrupt selection
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_HIGH_G
 *              1          | BMA2x2_ACCEL_INTR2_HIGH_G
 *
 * @param intr_high_g_u8 : the value of high_g interrupt
 *        intr_high_g_u8        |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr_high_g(u8 channel_u8,
        u8 intr_high_g_u8);
/*!
 * @brief This API is used to get
 * the interrupt enable of slope interrupt in the register 0x19 and 0x1B
 * @note INTR1_slope -> register 0x19 bit 2
 * @note INTR2_slope -> register 0x1B bit 2
 *
 *
 *
 * @param channel_u8: the value of slope channel select
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_SLOPE
 *              1          | BMA2x2_ACCEL_INTR2_SLOPE
 *
 * @param intr_slope_u8 : The slope value enable value
 *        intr_slope_u8         |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_slope(u8 channel_u8,
        u8 *intr_slope_u8);
/*!
 * @brief This API is used to set
 * the interrupt enable of slope interrupt in the register 0x19 and 0x1B
 * @note INTR1_slope -> register 0x19 bit 2
 * @note INTR2_slope -> register 0x1B bit 2
 *
 *
 *
 * @param channel_u8: the value of slope channel select
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_SLOPE
 *              1          | BMA2x2_ACCEL_INTR2_SLOPE
 *
 * @param intr_slope_u8 : The slope value enable value
 *        intr_slope_u8         |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr_slope(u8 channel_u8,
        u8 intr_slope_u8);
/*!
 * @brief This API is used to get
 * the interrupt enable of slow/no motion interrupt in
 * the register 0x19 and 0x1B
 * @note INTR1_slow_no_motion -> register 0x19 bit 3
 * @note INTR2_slow_no_motion -> register 0x1B bit 3
 *
 *
 *
 *
 *  @param channel_u8 : The value of slow/no motion selection
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_INTR1_SLOW_NO_MOTION
 *              1          | BMA2x2_INTR2_SLOW_NO_MOTION
 *
 *  @param intr_slow_no_motion_u8:  the slow_no_motion enable value
 *       intr_slow_no_motion_u8 |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_slow_no_motion(u8 channel_u8,
        u8 *intr_slow_no_motion_u8);
/*!
 * @brief This API is used to set
 * the interrupt enable of slow/no motion interrupt in
 * the register 0x19 and 0x1B
 * @note INTR1_slow_no_motion -> register 0x19 bit 3
 * @note INTR2_slow_no_motion -> register 0x1B bit 3
 *
 *
 *
 *
 *  @param channel_u8 : The value of slow/no motion selection
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_INTR1_SLOW_NO_MOTION
 *              1          | BMA2x2_INTR2_SLOW_NO_MOTION
 *
 *  @param intr_slow_no_motion_u8:  the slow_no_motion enable value
 *       intr_slow_no_motion_u8 |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr_slow_no_motion(u8 channel_u8,
        u8 intr_slow_no_motion_u8);
/*!
 * @brief This API is used to get
 * the interrupt enable of double tap interrupt
 * in the register 0x19 and 0x1B
 * @note INTR1_double -> register 0x19 bit 4
 * @note INTR2_double -> register 0x1B bit 4
 *
 *
 *
 *
 *  @param channel_u8: The value of double tap selection
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_DOUBLE_TAP
 *              1          | BMA2x2_ACCEL_INTR2_DOUBLE_TAP
 *
 *  @param intr_double_tap_u8: The double tap interrupt enable value
 *       intr_double_tap_u8     |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_double_tap(u8 channel_u8,
        u8 *intr_double_tap_u8);
/*!
 * @brief This API is used to set
 * the interrupt enable of double tap interrupt
 * in the register 0x19 and 0x1B
 * @note INTR1_double -> register 0x19 bit 4
 * @note INTR2_double -> register 0x1B bit 4
 *
 *
 *
 *
 *  @param channel_u8: The value of double tap selection
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_DOUBLE_TAP
 *              1          | BMA2x2_ACCEL_INTR2_DOUBLE_TAP
 *
 *  @param intr_double_tap_u8: The double tap interrupt enable value
 *       intr_double_tap_u8     |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr_double_tap(u8 channel_u8,
        u8 intr_double_tap_u8);
/*!
 * @brief This API is used to get
 * the interrupt enable of single tap
 * interrupt in the register 0x19 and 0x1B
 * @note INTR1_single_tap -> register 0x19 bit 5
 * @note INTR2_single_tap -> register 0x1B bit 5
 *
 *
 *  @param channel_u8: The value of single tap interrupt select
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_SINGLE_TAP
 *              1          | BMA2x2_ACCEL_INTR2_SINGLE_TAP
 *
 *  @param intr_single_tap_u8: The single tap interrupt enable value
 *       intr_single_tap_u8     |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_single_tap(u8 channel_u8,
        u8 *intr_single_tap_u8);
/*!
 * @brief This API is used to set
 * the interrupt enable of single tap
 * interrupt in the register 0x19 and 0x1B
 * @note INTR1_single_tap -> register 0x19 bit 5
 * @note INTR2_single_tap -> register 0x1B bit 5
 *
 *
 *  @param channel_u8: The value of single tap interrupt select
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_SINGLE_TAP
 *              1          | BMA2x2_ACCEL_INTR2_SINGLE_TAP
 *
 *  @param intr_single_tap_u8: The single tap interrupt enable value
 *       intr_single_tap_u8     |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr_single_tap(u8 channel_u8,
        u8 intr_single_tap_u8);
/*!
 * @brief This API is used to get
 * the interrupt status of orient interrupt in the register 0x19 and 0x1B
 * @note INTR1_orient -> register 0x19 bit 6
 * @note INTR2_orient -> register 0x1B bit 6
 *
 *
 * @param channel_u8: The value of orient interrupt select
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_ORIENT
 *              1          | BMA2x2_ACCEL_INTR2_ORIENT
 *
 *  @param intr_orient_u8: The value of orient interrupt enable
 *       intr_orient_u8         |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_orient(u8 channel_u8,
        u8 *intr_orient_u8);
/*!
 * @brief This API is used to set
 * the interrupt status of orient interrupt in the register 0x19 and 0x1B
 * @note INTR1_orient -> register 0x19 bit 6
 * @note INTR2_orient -> register 0x1B bit 6
 *
 *
 * @param channel_u8: The value of orient interrupt select
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_ORIENT
 *              1          | BMA2x2_ACCEL_INTR2_ORIENT
 *
 *  @param intr_orient_u8: The value of orient interrupt enable
 *       intr_orient_u8         |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr_orient(u8 channel_u8,
        u8 intr_orient_u8);
/*!
 * @brief This API is used to get
 * the interrupt enable of flat interrupt in the register 0x19 and 0x1B
 * @note INTR1_flat -> register 0x19 bit 7
 * @note INTR2_flat -> register 0x1B bit 7
 *
 *
 *
 *
 * @param channel_u8: The value of flat interrupt select
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_FLAT
 *              1          | BMA2x2_ACCEL_INTR2_FLAT
 *
 * @param intr_flat_u8: The flat interrupt enable value
 *       intr_flat_u8           |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_flat(u8 channel_u8,
        u8 *intr_flat_u8);
/*!
 * @brief This API is used to set
 * the interrupt enable of flat interrupt in the register 0x19 and 0x1B
 * @note INTR1_flat -> register 0x19 bit 7
 * @note INTR2_flat -> register 0x1B bit 7
 *
 *
 *
 *
 * @param channel_u8: The value of flat interrupt select
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_FLAT
 *              1          | BMA2x2_ACCEL_INTR2_FLAT
 *
 * @param intr_flat_u8: The flat interrupt enable value
 *       intr_flat_u8           |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr_flat(u8 channel_u8,
        u8 intr_flat_u8);
/*!
 * @brief This API is used to get
 * the interrupt status of new data in the register 0x19
 * @note INTR1_data -> register 0x19 bit 0
 * @note INTR2_data -> register 0x19 bit 7
 *
 *
 *
 *  @param channel_u8: The value of new data interrupt select
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_NEWDATA
 *              1          | BMA2x2_ACCEL_INTR2_NEWDATA
 *
 *  @param intr_newdata_u8: The new data interrupt enable value
 *       intr_newdata_u8          |    result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_new_data(u8 channel_u8,
        u8 *intr_newdata_u8);
/*!
 * @brief This API is used to set
 * the interrupt status of new data in the register 0x19
 * @note INTR1_data -> register 0x19 bit 0
 * @note INTR2_data -> register 0x19 bit 7
 *
 *
 *
 *  @param channel_u8: The value of new data interrupt select
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_NEWDATA
 *              1          | BMA2x2_ACCEL_INTR2_NEWDATA
 *
 *  @param intr_newdata_u8: The new data interrupt enable value
 *       intr_newdata_u8          |    result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_new_data(u8 channel_u8,
        u8 intr_newdata_u8);
/******************************************/
/**\name FUNCTION FOR   FIFO INTERRUPT ENABLE*/
/******************************************/
/*!
 * @brief This API is used to get the fifo watermark interrupt1 data
 * in the register 0x1A bit 1
 *
 *  @param  intr1_fifo_wm_u8 : The value of interrupt1 FIFO watermark enable
 *       intr1_fifo_wm_u8       |    result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr1_fifo_wm(u8 *intr1_fifo_wm_u8);
/*!
 * @brief This API is used to set the fifo watermark interrupt1 data
 * in the register 0x1A bit 1
 *
 *  @param  intr1_fifo_wm_u8 : The value of interrupt1 FIFO watermark enable
 *       intr1_fifo_wm_u8       |    result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr1_fifo_wm(u8 intr1_fifo_wm_u8);
/*!
 * @brief This API is used to get the fifo watermark interrupt2 data
 * in the register 0x1A bit 6
 *
 *  @param  intr2_fifo_wm_u8 : The value of interrupt1 FIFO watermark enable
 *       intr2_fifo_wm_u8       |    result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr2_fifo_wm(u8 *intr2_fifo_wm_u8);
/*!
 * @brief This API is used to set the fifo watermark interrupt2 data
 * in the register 0x1A bit 6
 *
 *  @param  intr2_fifo_wm_u8 : The value of interrupt1 FIFO watermark enable
 *       intr2_fifo_wm_u8       |    result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr2_fifo_wm(u8 intr2_fifo_wm_u8);
/*!
 *  @brief This API is used to get
 *  the fifo full interrupt1 in the register 0x1A bit 2
 *
 *
 *
 *  @param intr1_fifo_full_u8 : The value of fifo full interrupt enable
 *       intr1_fifo_full_u8     |    result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr1_fifo_full(
    u8 *intr1_fifo_full_u8);
/*!
 *  @brief This API is used to set
 *  the fifo full interrupt1 in the register 0x1A bit 2
 *
 *
 *
 *  @param intr1_fifo_full_u8 : The value of fifo full interrupt enable
 *       intr1_fifo_full_u8     |    result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr1_fifo_full(u8 intr1_fifo_full_u8);
/*!
 *  @brief This API is used to get
 *  the fifo full interrupt2 in the register 0x1A bit 5
 *
 *
 *
 *  @param intr2_fifo_full_u8 : Thee vale of fifo full enable
 *       intr2_fifo_full_u8     |    result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr2_fifo_full(
    u8 *intr2_fifo_full_u8);
/*!
 *  @brief This API is used to set
 *  the fifo full interrupt2 in the register 0x1A bit 5
 *
 *
 *
 *  @param intr2_fifo_full_u8 : Thee vale of fifo full enable
 *       intr2_fifo_full_u8     |    result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr2_fifo_full(u8 intr2_fifo_full_u8);
/******************************************/
/**\name FUNCTION FOR  SOURCE CONFIGURATION */
/******************************************/
/*!
 *  @brief This API is used to get
 *  the source data status of source data,
 *  source slow no motion, source slope, source high
 *  and source low in the register 0x1E bit from 0 to 5
 *
 *
 *
 *  @param channel_u8 : The value of source select
 *       channel_u8     |    result
 *       -----------------| ------------------
 *               0        | BMA2x2_ACCEL_SOURCE_LOW_G
 *               1        | BMA2x2_ACCEL_SOURCE_HIGH_G
 *               2        | BMA2x2_ACCEL_SOURCE_SLOPE
 *               3        | BMA2x2_ACCEL_SOURCE_SLOW_NO_MOTION
 *               4        | BMA2x2_ACCEL_SOURCE_TAP
 *               5        | BMA2x2_ACCEL_SOURCE_DATA
 *
 *  @param intr_source_u8: The source status enable value
 *       intr_source_u8         |    result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_source(u8 channel_u8,
        u8 *intr_source_u8);
/*!
 *  @brief This API is used to set
 *  the source data status of source data,
 *  source slow no motion, source slope, source high
 *  and source low in the register 0x1E bit from 0 to 5
 *
 *
 *
 *  @param channel_u8 : The value of source select
 *       channel_u8     |    result
 *       -----------------| ------------------
 *               0        | BMA2x2_ACCEL_SOURCE_LOW_G
 *               1        | BMA2x2_ACCEL_SOURCE_HIGH_G
 *               2        | BMA2x2_ACCEL_SOURCE_SLOPE
 *               3        | BMA2x2_ACCEL_SOURCE_SLOW_NO_MOTION
 *               4        | BMA2x2_ACCEL_SOURCE_TAP
 *               5        | BMA2x2_ACCEL_SOURCE_DATA
 *
 *  @param intr_source_u8: The source status enable value
 *       intr_source_u8         |    result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_source(u8 channel_u8,
        u8 intr_source_u8);
/******************************************/
/**\name FUNCTION FOR   OUTPUT TYPE AND LEVEL*/
/******************************************/
/*!
 *  @brief This API is used to get
 *  the interrupt output type in the register 0x20.
 *  @note INTR1 -> bit 1
 *  @note INTR2 -> bit 3
 *
 *  @param channel_u8: The value of output type select
 *       channel_u8     |    result
 *       -----------------| ------------------
 *               0        | BMA2x2_ACCEL_INTR1_OUTPUT
 *               1        | BMA2x2_ACCEL_INTR2_OUTPUT
 *
 *  @param intr_output_type_u8: The value of output type select
 *       intr_source_u8         |    result
 *       ------------------------ | ------------------
 *              0x01              | OPEN_DRAIN
 *              0x00              | PUSS_PULL
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_output_type(u8 channel_u8,
        u8 *intr_output_type_u8);
/*!
 *  @brief This API is used to set
 *  the interrupt output type in the register 0x20.
 *  @note INTR1 -> bit 1
 *  @note INTR2 -> bit 3
 *
 *  @param channel_u8: The value of output type select
 *         channel_u8   |    result
 *       -----------------| ------------------
 *               0        | BMA2x2_ACCEL_INTR1_OUTPUT
 *               1        | BMA2x2_ACCEL_INTR2_OUTPUT
 *
 *  @param intr_output_type_u8: The value of output type select
 *       intr_source_u8         |    result
 *       ------------------------ | ------------------
 *              0x01              | OPEN_DRAIN
 *              0x00              | PUSS_PULL
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr_output_type(u8 channel_u8,
        u8 intr_output_type_u8);
/*!
 *  @brief This API is used to get
 *  Active Level status in the register 0x20
 *  @note INTR1 -> bit 0
 *  @note INTR2 -> bit 2
 *
 *  @param channel_u8: The value of Active Level select
 *       channel_u8     |    result
 *       -----------------| ------------------
 *               0        | BMA2x2_ACCEL_INTR1_LEVEL
 *               1        | BMA2x2_ACCEL_INTR2_LEVEL
 *
 *  @param intr_level_u8: The Active Level status enable value
 *       intr_level_u8          |    result
 *       ------------------------ | ------------------
 *              0x01              | ACTIVE_HIGH
 *              0x00              | ACTIVE_LOW
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_level(u8 channel_u8,
        u8 *intr_level_u8);
/*!
 *  @brief This API is used to set
 *  Active Level status in the register 0x20
 *  @note INTR1 -> bit 0
 *  @note INTR2 -> bit 2
 *
 *  @param channel_u8: The value of Active Level select
 *       channel_u8     |    result
 *       -----------------| ------------------
 *               0        | BMA2x2_ACCEL_INTR1_LEVEL
 *               1        | BMA2x2_ACCEL_INTR2_LEVEL
 *
 *  @param intr_level_u8: The Active Level status enable value
 *       intr_level_u8          |    result
 *       ------------------------ | ------------------
 *              0x01              | ACTIVE_HIGH
 *              0x00              | ACTIVE_LOW
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr_level(u8 channel_u8,
        u8 intr_level_u8);
/******************************************/
/**\name FUNCTION FOR  RESET INTERRUPT*/
/******************************************/
/*!
 *  @brief This API is used to set
 *  the reset interrupt in the register 0x21 bit 7
 *
 *
 *
 *  @param  rst_intr_u8: The value of reset interrupt
 *          rst_intr_u8         |  result
 *       ------------------------ | ------------------
 *              0x01              | clear any latch interrupt
 *              0x00              | keep latch interrupt active
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_rst_intr(u8 rst_intr_u8);
/******************************************/
/**\name FUNCTION FOR   LATCH INTERRUPT INTERRUPT*/
/******************************************/
/*!
 *  @brief This API is used to get
 *  the latch duration in the register 0x21 bit from 0 to 3
 *
 *  @param latch_intr_u8: The value of latch duration
 *        latch_intr_u8 |  result
 *       -----------------| ------------------
 *               0x00     | BMA2x2_LATCH_DURN_NON_LATCH
 *               0x01     | BMA2x2_LATCH_DURN_250MS
 *               0x02     | BMA2x2_LATCH_DURN_500MS
 *               0x03     | BMA2x2_LATCH_DURN_1S
 *               0x04     | BMA2x2_LATCH_DURN_2S
 *               0x05     | BMA2x2_LATCH_DURN_4S
 *               0x06     | BMA2x2_LATCH_DURN_8S
 *               0x07     | BMA2x2_LATCH_DURN_LATCH
 *               0x08     | BMA2x2_LATCH_DURN_NON_LATCH1
 *               0x09     | BMA2x2_LATCH_DURN_250US
 *               0x0A     | BMA2x2_LATCH_DURN_500US
 *               0x0B     | BMA2x2_LATCH_DURN_1MS
 *               0x0C     | BMA2x2_LATCH_DURN_12_5MS
 *               0x0D     | BMA2x2_LATCH_DURN_25MS
 *               0x0E     | BMA2x2_LATCH_DURN_50MS
 *               0x0F     | BMA2x2_LATCH_DURN_LATCH1
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_latch_intr(u8 *latch_intr_u8);
/*!
 *  @brief This API is used to set
 *  the latch duration in the register 0x21 bit from 0 to 3
 *
 *  @param latch_intr_u8: The value of latch duration
 *        latch_intr_u8 |  result
 *       -----------------| ------------------
 *               0x00     | BMA2x2_LATCH_DURN_NON_LATCH
 *               0x01     | BMA2x2_LATCH_DURN_250MS
 *               0x02     | BMA2x2_LATCH_DURN_500MS
 *               0x03     | BMA2x2_LATCH_DURN_1S
 *               0x04     | BMA2x2_LATCH_DURN_2S
 *               0x05     | BMA2x2_LATCH_DURN_4S
 *               0x06     | BMA2x2_LATCH_DURN_8S
 *               0x07     | BMA2x2_LATCH_DURN_LATCH
 *               0x08     | BMA2x2_LATCH_DURN_NON_LATCH1
 *               0x09     | BMA2x2_LATCH_DURN_250US
 *               0x0A     | BMA2x2_LATCH_DURN_500US
 *               0x0B     | BMA2x2_LATCH_DURN_1MS
 *               0x0C     | BMA2x2_LATCH_DURN_12_5MS
 *               0x0D     | BMA2x2_LATCH_DURN_25MS
 *               0x0E     | BMA2x2_LATCH_DURN_50MS
 *               0x0F     | BMA2x2_LATCH_DURN_LATCH1
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_latch_intr(u8 latch_intr_u8);
/******************************************/
/**\name FUNCTION FOR   INTERRUPT DURATION CONFIGURATION*/
/******************************************/
/*!
 *  @brief This API is used to get the duration of
 *  Low, High, Slope and slow no motion interrupts in the registers
 *  @note LOW_DURN      -> register 0x22 bit form 0 to 7
 *  @note HIGH_DURN     -> register 0x25 bit form 0 to 7
 *  @note SLOPE_DURN        -> register 0x27 bit form 0 to 1
 *  @note SLO_NO_MOT_DURN -> register 0x27 bit form 2 to 7
 *
 *  @param channel_u8: The value of duration select
 *     channel_u8   | result
 *   -----------------| ------------------
 *               0    | BMA2x2_ACCEL_LOW_DURN
 *               1    | BMA2x2_ACCEL_HIGH_DURN
 *               2    | BMA2x2_ACCEL_SLOPE_DURN
 *               3    | BMA2x2_ACCEL_SLOW_NO_MOTION_DURN
 *
 *  @param durn_u8: The value of duration
 *
 *  @note :
 *     Duration           |    result
 * -----------------------| ------------------
 * BMA2x2_ACCEL_LOW_DURN  | Low-g interrupt trigger
 *         -              | delay according to([durn_u8 +1]*2)ms
 *         -              | range from 2ms to 512ms. default is 20ms
 * BMA2x2_ACCEL_HIGH_DURN | high-g interrupt trigger
 *         -              | delay according to([durn_u8 +1]*2)ms
 *         -              | range from 2ms to 512ms. default is 32ms
 * BMA2x2_ACCEL_SLOPE_DURN| slope interrupt trigger
 *         -              | if[durn_u8<1:0>+1] consecutive data points
 *         -              | are above the slope interrupt threshold
 * SLO_NO_MOT_DURN        | Refer data sheet for clear information
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_durn(u8 channel_u8,
        u8 *durn_u8);
/*!
 *  @brief This API is used to set the duration of
 *  Low, High, Slope and slow no motion interrupts in the registers
 *  @note LOW_DURN      -> register 0x22 bit form 0 to 7
 *  @note HIGH_DURN     -> register 0x25 bit form 0 to 7
 *  @note SLOPE_DURN        -> register 0x27 bit form 0 to 1
 *  @note SLO_NO_MOT_DURN -> register 0x27 bit form 2 to 7
 *
 *  @param channel_u8: The value of duration select
 *     channel_u8   | result
 *   -----------------| ------------------
 *               0    | BMA2x2_ACCEL_LOW_DURN
 *               1    | BMA2x2_ACCEL_HIGH_DURN
 *               2    | BMA2x2_ACCEL_SLOPE_DURN
 *               3    | BMA2x2_ACCEL_SLOW_NO_MOTION_DURN
 *
 *  @param durn_u8: The value of duration
 *
 *  @note :
 *     Duration           |    result
 * -----------------------| ------------------
 * BMA2x2_ACCEL_LOW_DURN  | Low-g interrupt trigger
 *         -              | delay according to([durn_u8 +1]*2)ms
 *         -              | range from 2ms to 512ms. default is 20ms
 * BMA2x2_ACCEL_HIGH_DURN | high-g interrupt trigger
 *         -              | delay according to([durn_u8 +1]*2)ms
 *         -              | range from 2ms to 512ms. default is 32ms
 * BMA2x2_ACCEL_SLOPE_DURN| slope interrupt trigger
 *         -              | if[durn_u8<1:0>+1] consecutive data points
 *         -              | are above the slope interrupt threshold
 * SLO_NO_MOT_DURN        | Refer data sheet for clear information
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_durn(u8 channel_u8,
        u8 durn_u8);
/******************************************/
/**\name FUNCTION FOR  INTERRUPT THRESHOLD CONFIGURATION */
/******************************************/
/*!
 * @brief This API is used to get the threshold of
 *  Low, High, Slope and slow no motion interrupts in the registers
 *  @note LOW_THRES     -> register 0x23 bit form 0 to 7
 *  @note HIGH_THRES        -> register 0x26 bit form 0 to 7
 *  @note SLOPE_THRES       -> register 0x28 bit form 0 to 7
 *  @note SLO_NO_MOT_THRES -> register 0x29 bit form 0 to 7
 *
 *  @param channel_u8: The value of threshold selection
 *     channel_u8   | result
 *   -----------------| ------------------
 *               0    | BMA2x2_ACCEL_LOW_THRES
 *               1    | BMA2x2_ACCEL_HIGH_THRES
 *               2    | BMA2x2_ACCEL_SLOPE_THRES
 *               3    | BMA2x2_ACCEL_SLOW_NO_MOTION_THRES
 *
 *  @param thres_u8: The threshold value of selected interrupts
 *
 *  @note : LOW-G THRESHOLD
 *     Threshold                    |    result
 * ---------------------------------| ------------------
 * BMA2x2_ACCEL_LOW_THRES           | Low-threshold interrupt trigger
 *                                  | according to(thres_u8 * 7.81) mg
 *                                  | range from 0g to 1.992g
 *                                  | default is 375mg
 *  @note : HIGH-G THRESHOLD
 *  @note Threshold of high-g interrupt according to accel g range
 *    g-range           |      High-g threshold
 *  --------------------|----------------------------
 *     2g               |    (thres_u8 * 7.81) mg
 *     4g               |    (thres_u8 * 15.63) mg
 *     8g               |    (thres_u8 * 31.25) mg
 *     16g              |    (thres_u8 * 62.5) mg
 *
 *  @note : SLOPE THRESHOLD
 *  @note Threshold of slope interrupt according to accel g range
 *    g-range           |      Slope threshold
 *  --------------------|----------------------------
 *     2g               |    (thres_u8 * 3.19) mg
 *     4g               |    (thres_u8 * 7.81) mg
 *     8g               |    (thres_u8 * 15.63) mg
 *     16g              |    (thres_u8 * 31.25) mg
 *
 *  @note : SLOW NO MOTION THRESHOLD
 *  @note Threshold of slow no motion interrupt according to accel g range
 *    g-range           |   slow no motion threshold
 *  --------------------|----------------------------
 *     2g               |    (thres_u8 * 3.19) mg
 *     4g               |    (thres_u8 * 7.81) mg
 *     8g               |    (thres_u8 * 15.63) mg
 *     16g              |    (thres_u8 * 31.25) mg
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_thres(u8 channel_u8,
        u8 *thres_u8);
/*!
 * @brief This API is used to set the threshold of
 *  Low, High, Slope and slow no motion interrupts in the registers
 *  @note LOW_THRES     -> register 0x23 bit form 0 to 7
 *  @note HIGH_THRES        -> register 0x26 bit form 0 to 7
 *  @note SLOPE_THRES       -> register 0x28 bit form 0 to 7
 *  @note SLO_NO_MOT_THRES -> register 0x29 bit form 0 to 7
 *
 *  @param channel_u8: The value of threshold selection
 *     channel_u8   | result
 *   -----------------| ------------------
 *               0    | BMA2x2_ACCEL_LOW_THRES
 *               1    | BMA2x2_ACCEL_HIGH_THRES
 *               2    | BMA2x2_ACCEL_SLOPE_THRES
 *               3    | BMA2x2_ACCEL_SLOW_NO_MOTION_THRES
 *
 *  @param thres_u8: The threshold value of selected interrupts
 *
 *  @note : LOW-G THRESHOLD
 *     Threshold                    |    result
 * ---------------------------------| ------------------
 * BMA2x2_ACCEL_LOW_THRES           | Low-threshold interrupt trigger
 *                                  | according to(thres_u8 * 7.81) mg
 *                                  | range from 0g to 1.992g
 *                                  | default is 375mg
 *  @note : HIGH-G THRESHOLD
 *  @note Threshold of high-g interrupt according to accel g range
 *    g-range           |      High-g threshold
 *  --------------------|----------------------------
 *     2g               |    (thres_u8 * 7.81) mg
 *     4g               |    (thres_u8 * 15.63) mg
 *     8g               |    (thres_u8 * 31.25) mg
 *     16g              |    (thres_u8 * 62.5) mg
 *
 *  @note : SLOPE THRESHOLD
 *  @note Threshold of slope interrupt according to accel g range
 *    g-range           |      Slope threshold
 *  --------------------|----------------------------
 *     2g               |    (thres_u8 * 3.19) mg
 *     4g               |    (thres_u8 * 7.81) mg
 *     8g               |    (thres_u8 * 15.63) mg
 *     16g              |    (thres_u8 * 31.25) mg
 *
 *  @note : SLOW NO MOTION THRESHOLD
 *  @note Threshold of slow no motion interrupt according to accel g range
 *    g-range           |   slow no motion threshold
 *  --------------------|----------------------------
 *     2g               |    (thres_u8 * 3.19) mg
 *     4g               |    (thres_u8 * 7.81) mg
 *     8g               |    (thres_u8 * 15.63) mg
 *     16g              |    (thres_u8 * 31.25) mg
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_thres(u8 channel_u8,
        u8 thres_u8);
/******************************************/
/**\name FUNCTION FOR INTERRUPT HYSTERESIS  */
/******************************************/
/*!
 *  @brief This API is used to get
 *  the low high hysteresis in the registers 0x24
 *  @note LOW_G_HYST  -> bit form 0 to 1
 *  @note HIGH_G_HYST  -> bit from 6 to 7
 *
 *  @param channel_u8: The value of hysteresis selection
 *     channel_u8   | result
 *   -----------------| ------------------
 *           0        | BMA2x2_ACCEL_LOW_G_HYST
 *           1        | BMA2x2_ACCEL_HIGH_G_HYST
 *
 *  @param hyst_u8: The hysteresis data
 *
 *  @note LOW HYSTERESIS
 *  @note Hysteresis of low-g interrupt according to (hyst_u8 * 125)mg
 *
 *  @note HIGH HYSTERESIS
 *  @note High hysteresis depends on the accel range selection
 *    g-range           |    High Hysteresis
 *  --------------------|----------------------------
 *     2g               |    (thres_u8 * 125) mg
 *     4g               |    (thres_u8 * 250) mg
 *     8g               |    (thres_u8 * 500) mg
 *     16g              |    (thres_u8 * 1000) mg
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_low_high_g_hyst(u8 channel_u8,
        u8 *hyst_u8);
/*!
 *  @brief This API is used to set
 *  the low high hysteresis in the registers 0x24
 *  @note LOW_G_HYST  -> bit form 0 to 1
 *  @note HIGH_G_HYST  -> bit from 6 to 7
 *
 *  @param channel_u8: The value of hysteresis selection
 *     channel_u8   | result
 *   -----------------| ------------------
 *           0        | BMA2x2_ACCEL_LOW_G_HYST
 *           1        | BMA2x2_ACCEL_HIGH_G_HYST
 *
 *  @param hyst_u8: The hysteresis data
 *
 *  @note LOW HYSTERESIS
 *  @note Hysteresis of low-g interrupt according to (hyst_u8 * 125)mg
 *
 *  @note HIGH HYSTERESIS
 *  @note High hysteresis depends on the accel range selection
 *    g-range           |    High Hysteresis
 *  --------------------|----------------------------
 *     2g               |    (thres_u8 * 125) mg
 *     4g               |    (thres_u8 * 250) mg
 *     8g               |    (thres_u8 * 500) mg
 *     16g              |    (thres_u8 * 1000) mg
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_low_high_g_hyst(u8 channel_u8,
        u8 hyst_u8);
/******************************************/
/**\name FUNCTION FOR  LOW_G MODE */
/******************************************/
/*!
 *  @brief This API is used to get
 *  low_g  mode in the registers 0x24 bit 2
 *
 *
 *  @param low_g_mode_u8: The value of Low_G mode
 *      low_g_mode_u8   |   g-result
 *  --------------------|----------------------------
 *     0x00             | LOW_G_SINGLE_AXIS_MODE
 *     0x01             | LOW_G_SUMMING_MODE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_low_g_mode(u8 *low_g_mode_u8);
/*!
 *  @brief This API is used to set
 *  low_g  mode in the registers 0x24 bit 2
 *
 *
 *  @param low_g_mode_u8: The value of Low_G mode
 *    low_g_mode_u8   |    result
 *  --------------------|----------------------------
 *     0x00             | LOW_G_SINGLE_AXIS_MODE
 *     0x01             | LOW_G_SUMMING_MODE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_low_g_mode(u8 low_g_mode_u8);
/******************************************/
/**\name FUNCTION FOR  TAP DURATION */
/******************************************/
/*!
 *  @brief This API is used to get
 *  the tap duration in the register 0x2A bit form 0 to 2
 *
 *
 *  @param tap_durn_u8: The value of tap duration
 *    tap_durn_u8     |    result
 *  --------------------|----------------------------
 *     0x00             | TAP_DURN_50_MS
 *     0x01             | TAP_DURN_100_MS
 *     0x02             | TAP_DURN_150_MS
 *     0x03             | TAP_DURN_200_MS
 *     0x04             | TAP_DURN_250_MS
 *     0x05             | TAP_DURN_375_MS
 *     0x06             | TAP_DURN_500_MS
 *     0x07             | TAP_DURN_700_MS
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_tap_durn(u8 *tap_durn_u8);
/*!
 *  @brief This API is used to set
 *  the tap duration in the register 0x2A bit form 0 to 2
 *
 *
 *  @param tap_durn_u8: The value of tap duration
 *    tap_durn_u8     |    result
 *  --------------------|----------------------------
 *     0x00             | TAP_DURN_50_MS
 *     0x01             | TAP_DURN_100_MS
 *     0x02             | TAP_DURN_150_MS
 *     0x03             | TAP_DURN_200_MS
 *     0x04             | TAP_DURN_250_MS
 *     0x05             | TAP_DURN_375_MS
 *     0x06             | TAP_DURN_500_MS
 *     0x07             | TAP_DURN_700_MS
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_tap_durn(u8 tap_durn_u8);
/******************************************/
/**\name FUNCTION FOR  TAP SHOCK */
/******************************************/
/*!
 *  @brief This API is used to get
 *  the tap shock form the register 0x2A bit 6
 *
 *
 *
 *  @param tap_shock_u8: The value of tap shock
 *    tap_shock_u8    |    result
 *  --------------------|----------------------
 *     0x00             | TAP_SHOCK_50_MS
 *     0x01             | TAP_SHOCK_75_MS
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_tap_shock(u8 *tap_shock_u8);
/*!
 *  @brief This API is used to set
 *  the tap shock form the register 0x2A bit 6
 *
 *
 *
 *  @param tap_shock_u8: The value of tap shock
 *    tap_shock_u8    |    result
 *  --------------------|----------------------
 *     0x00             | TAP_SHOCK_50_MS
 *     0x01             | TAP_SHOCK_75_MS
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_tap_shock(u8 tap_shock_u8);
/******************************************/
/**\name FUNCTION FOR  TAP QUIET */
/******************************************/
/*!
 *  @brief This API is used to get
 *  the tap quiet in the register 0x2A bit 7
 *
 *
 *
 *  @param  tap_quiet_u8 : The value of tap quiet
 *    tap_quiet_u8    |    result
 *  --------------------|----------------------
 *     0x00             | TAP_QUIET_30_MS
 *     0x01             | TAP_QUIET_20_MS
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_tap_quiet(u8 *tap_quiet_u8);
/*!
 *  @brief This API is used to set
 *  the tap quiet in the register 0x2A bit 7
 *
 *
 *
 *  @param  tap_quiet_u8 : The value of tap quiet
 *    tap_quiet_u8    |    result
 *  --------------------|----------------------
 *     0x00             | TAP_QUIET_30_MS
 *     0x01             | TAP_QUIET_20_MS
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_tap_quiet(u8 tap_quiet_u8);
/******************************************/
/**\name FUNCTION FOR  TAP THRESHOLD */
/******************************************/
/*!
 *  @brief This API is used to get
 *  the tap threshold in the register 0x2B bit from 0 to 4
 *
 *
 *
 *  @param tap_thres_u8 : The value of tap threshold
 *  @note Tap threshold of single and double tap corresponding
 *       to accel range
 *     range            |    Tap threshold
 *  --------------------|----------------------
 *     2g               | (tap_thres_u8 * 62.5)mg
 *     4g               | (tap_thres_u8 * 125)mg
 *     8g               | (tap_thres_u8 * 250)mg
 *     16g              | (tap_thres_u8 * 500)mg
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_tap_thres(u8 *tap_thres_u8);
/*!
 *  @brief This API is used to set
 *  the tap threshold in the register 0x2B bit from 0 to 4
 *
 *
 *
 *  @param tap_thres_u8 : The value of tap threshold
 *  @note Tap threshold of single and double tap corresponding
 *       to accel range
 *     range            |    Tap threshold
 *  --------------------|----------------------
 *     2g               | (tap_thres_u8 * 62.5)mg
 *     4g               | (tap_thres_u8 * 125)mg
 *     8g               | (tap_thres_u8 * 250)mg
 *     16g              | (tap_thres_u8 * 500)mg
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_tap_thres(u8 tap_thres_u8);
/******************************************/
/**\name FUNCTION FOR  TAP SAMPLES */
/******************************************/
/*!
 *  @brief This API is used to get
 *  the tap sample in the register 0x2B bit 6 and 7
 *
 *
 *
 *  @param   *tap_sample_u8 : The value of tap sample
 *     tap_sample_u8  |    result
 *  --------------------|----------------------
 *     0x00             | 2 samples
 *     0x01             | 4 samples
 *     0x02             | 8 samples
 *     0x03             | 16 samples
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_tap_sample(u8 *tap_sample_u8);
/*!
 *  @brief This API is used to set
 *  the tap sample in the register 0x2B bit 6 and 7
 *
 *
 *
 *  @param   *tap_sample_u8 : The value of tap sample
 *     tap_sample_u8  |    result
 *  --------------------|----------------------
 *     0x00             | 2 samples
 *     0x01             | 4 samples
 *     0x02             | 8 samples
 *     0x03             | 16 samples
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_tap_sample(u8 tap_sample_u8);
/******************************************/
/**\name FUNCTION FOR  ORIENT MODE */
/******************************************/
/*!
 *  @brief This API is used to get
 *  the orient mode in the register 0x2C bit 0 and 1
 *
 *
 *
 *  @param orient_mode_u8 : The value of orient mode
 *     orient_mode_u8 |    result
 *  --------------------|------------------
 *     0x00             | symmetrical
 *     0x01             | high asymmetrical
 *     0x02             | low asymmetrical
 *     0x03             | symmetrical
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_orient_mode(u8 *orient_mode_u8);
/*!
 *  @brief This API is used to set
 *  the orient mode in the register 0x2C bit 0 and 1
 *
 *
 *
 *  @param orient_mode_u8 : The value of orient mode
 *     orient_mode_u8 |    result
 *  --------------------|------------------
 *     0x00             | symmetrical
 *     0x01             | high asymmetrical
 *     0x02             | low asymmetrical
 *     0x03             | symmetrical
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_orient_mode(u8 orient_mode_u8);
/******************************************/
/**\name FUNCTION FOR  ORIENT BLOCK*/
/******************************************/
/*!
 *  @brief This API is used to get
 *  the orient block in the register 0x2C bit 2 and 3
 *
 *
 *
 *  @param orient_block_u8 : The value of orient block
 *     orient_mode_u8 |    result
 *  --------------------|------------------
 *     0x00             | no blocking
 *     0x01             | theta blocking or
 *                      | acceleration slope in any axis > 1.5g
 *     0x02             | theta blocking or
 *                      | acceleration slope in any axis > 0.2g
 *                      | acceleration in any axis > 1.5g
 *     0x03             | theta blocking or
 *                      | acceleration slope in any axis > 0.4g
 *                      | acceleration in any axis > 1.5g
 *                      | value of orient is not stable for at lease 100ms
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_orient_block(
    u8 *orient_block_u8);
/*!
 *  @brief This API is used to set
 *  the orient block in the register 0x2C bit 2 and 3
 *
 *
 *
 *  @param orient_block_u8 : The value of orient block
 *     orient_mode_u8 |    result
 *  --------------------|------------------
 *     0x00             | no blocking
 *     0x01             | theta blocking or
 *                      | acceleration slope in any axis > 1.5g
 *     0x02             | theta blocking or
 *                      | acceleration slope in any axis > 0.2g
 *                      | acceleration in any axis > 1.5g
 *     0x03             | theta blocking or
 *                      | acceleration slope in any axis > 0.4g
 *                      | acceleration in any axis > 1.5g
 *                      | value of orient is not stable for at lease 100ms
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_orient_block(u8 orient_block_u8);
/******************************************/
/**\name FUNCTION FOR  ORIENT HYSTERESIS */
/******************************************/
/*!
 *  @brief This API is used to get
 *  the orient hysteresis in the register 0x2C bit 4 to 6
 *
 *
 *
 *  @param orient_hyst_u8 : The value of orient hysteresis
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_orient_hyst(u8 *orient_hyst_u8);
/*!
 *  @brief This API is used to set
 *  the orient hysteresis in the register 0x2C bit 4 to 6
 *
 *
 *
 *  @param orient_hyst_u8 : The value of orient hysteresis
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_orient_hyst(u8 orient_hyst_u8);
/******************************************/
/**\name FUNCTION FOR  ORIENT THETA */
/******************************************/
/*!
 *  @brief  This API is used to get
 *  the theta value of orient and flat interrupts
 *  @note ORIENT_THETA -> register 0x2D bit 0 to 5
 *  @note FLAT_THETA   -> register 0x2E bit 0 to 5
 *
 *  @param channel_u8: The value of theta selection
 *     channel_u8     |    result
 *  --------------------|------------------
 *     0x00             | BMA2x2_ACCEL_ORIENT_THETA
 *     0x01             | BMA2x2_ACCEL_FLAT_THETA
 * @note
 * @note FLAT_THETA : Defines a blocking angle between 0 deg to 44.8 deg
 * @note ORIENT_THETA : Defines threshold for detection of flat position
 *                in range from 0 deg to 44.8 deg
 *
 *  @param theta_u8: The value of theta
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_theta(u8 channel_u8,
        u8 *theta_u8);
/*!
 *  @brief  This API is used to set
 *  the theta value of orient and flat interrupts
 *  @note ORIENT_THETA -> register 0x2D bit 0 to 5
 *  @note FLAT_THETA   -> register 0x2E bit 0 to 5
 *
 *  @param channel_u8: The value of theta selection
 *     channel_u8     |    result
 *  --------------------|------------------
 *     0x00             | BMA2x2_ACCEL_ORIENT_THETA
 *     0x01             | BMA2x2_ACCEL_FLAT_THETA
 * @note
 * @note FLAT_THETA : Defines a blocking angle between 0 deg to 44.8 deg
 * @note ORIENT_THETA : Defines threshold for detection of flat position
 *                in range from 0 deg to 44.8 deg
 *
 *  @param theta_u8: The value of theta
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_theta(u8 channel_u8,
        u8 theta_u8);
/******************************************/
/**\name FUNCTION FOR   ORIENT ENABLE*/
/******************************************/
/*!
 *  @brief This API is used to get
 *  the interrupt enable of orient ud_enable in the register 0x2D bit 6
 *
 *
 *  @param orient_enable_u8 : The value of orient ud_enable
 *     orient_enable_u8     |    result
 *  ------------------------- |------------------
 *     0x00                   | Generates Interrupt
 *     0x01                   | Do not generate interrupt
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_orient_enable(
    u8 *orient_enable_u8);
/*!
 *  @brief This API is used to set
 *  the interrupt enable of orient ud_enable in the register 0x2D bit 6
 *
 *
 *  @param orient_enable_u8 : The value of orient ud_enable
 *     orient_enable_u8     |    result
 *  ------------------------- |------------------
 *     0x00                   | Generates Interrupt
 *     0x01                   | Do not generate interrupt
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_orient_enable(u8 orient_enable_u8);
/******************************************/
/**\name FUNCTION FOR  FLAT HYSTERESIS */
/******************************************/
/*!
 *  @brief This API is used to get
 *  the interrupt enable of flat hysteresis("flat_hy)
 *  in the register 0x2F bit 0 to 2
 *
 *
 *
 *
 *  @param flat_hyst_u8 : The value of flat hysteresis
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_flat_hyst(u8 *flat_hyst_u8);
/*!
 *  @brief This API is used to set
 *  the interrupt enable of flat hysteresis("flat_hy)
 *  in the register 0x2F bit 0 to 2
 *
 *
 *
 *
 *  @param flat_hyst_u8 : The value of flat hysteresis
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_flat_hyst(u8 flat_hyst_u8);
/******************************************/
/**\name FUNCTION FOR  FLAT HOLD TIME */
/******************************************/
/*!
 *  @brief This API is used to get
 *  the interrupt enable of flat hold time(flat_hold_time)
 *  in the register 0x2F bit 4 and 5
 *
 *
 *  @param  flat_hold_time_u8 : The value of flat hold time
 *     flat_hold_time_u8    |    result
 *  ------------------------- |------------------
 *     0x00                   | 0ms
 *     0x01                   | 512ms
 *     0x02                   | 1024ms
 *     0x03                   | 2048ms
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_flat_hold_time(
    u8 *flat_hold_time_u8);
/*!
 *  @brief This API is used to set
 *  the interrupt enable of flat hold time(flat_hold_time)
 *  in the register 0x2F bit 4 and 5
 *
 *
 *  @param  flat_hold_time_u8 : The value of flat hold time
 *     flat_hold_time_u8    |    result
 *  ------------------------- |------------------
 *     0x00                   | 0ms
 *     0x01                   | 512ms
 *     0x02                   | 1024ms
 *     0x03                   | 2048ms
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_flat_hold_time(
    u8 flat_hold_time_u8);
/******************************************/
/**\name FUNCTION FOR FIFO WATER MARK LEVEL TRIGGER */
/******************************************/
/*!
 *  @brief This API is used to get
 *  the fifo water mark level trigger in the register 0x30 bit from 0 to 5
 *
 *
 *
 *
 *  @param fifo_wml_trig: The value of fifo watermark trigger level
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_fifo_wml_trig(
    u8 *fifo_wml_trig);
/*!
 *  @brief This API is used to set
 *  the fifo water mark level trigger in the register 0x30 bit from 0 to 5
 *
 *
 *
 *
 *  @param fifo_wml_trig: The value of fifo watermark trigger level
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_fifo_wml_trig(
    u8 fifo_wml_trig);
/******************************************/
/**\name FUNCTION FOR SELFTEST   */
/******************************************/
/*!
 *  @brief This API is for to get
 *  the self test axis(self_test_axis) in the register ox32 bit 0 to 2
 *
 *
 *
 *  @param selftest_axis_u8 : The value of selftest axis
 *     selftest_axis_u8     |    result
 *  ------------------------- |------------------
 *     0x00                   | self test disable
 *     0x01                   | x-axis
 *     0x02                   | y-axis
 *     0x03                   | z-axis
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_selftest_axis(
    u8 *selftest_axis_u8);
/*!
 *  @brief This API is for to set
 *  the self test axis(self_test_axis) in the register ox32 bit 0 to 2
 *
 *
 *
 *  @param selftest_axis_u8 : The value of selftest axis
 *     selftest_axis_u8     |    result
 *  ------------------------- |------------------
 *     0x00                   | self test disable
 *     0x01                   | x-axis
 *     0x02                   | y-axis
 *     0x03                   | z-axis
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_selftest_axis(
    u8 selftest_axis_u8);
/*!
 *  @brief This API is for to get
 *  the Self Test sign(selftest_sign) in the register 0x32 bit 2
 *
 *
 *
 *  @param selftest_sign_u8 : The value of self test sign
 *     selftest_sign_u8     |    result
 *  ------------------------- |------------------
 *     0x00                   | negative sign
 *     0x01                   | positive sign
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_selftest_sign(
    u8 *selftest_sign_u8);
/*!
 *  @brief This API is for to set
 *  the Self Test sign(selftest_sign) in the register 0x32 bit 2
 *
 *
 *
 *  @param selftest_sign_u8 : The value of self test sign
 *     selftest_sign_u8     |    result
 *  ------------------------- |------------------
 *     0x00                   | negative sign
 *     0x01                   | positive sign
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_selftest_sign(
    u8 selftest_sign_u8);
/******************************************/
/**\name FUNCTION FOR  NVM */
/******************************************/
/*!
 * @brief This API is used to get
 * the nvm program mode(nvm_prog_mode)in the register 0x33 bit 0
 *
 *
 *  @param  nvmprog_mode_u8 : The value of nvm program mode
 *     nvmprog_mode_u8      |    result
 *  ------------------------- |------------------
 *     0x00                   | Disable program mode
 *     0x01                   | Enable program mode
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_nvmprog_mode(
    u8 *nvmprog_mode_u8);
/*!
 * @brief This API is used to set
 * the nvm program mode(nvm_prog_mode)in the register 0x33 bit 0
 *
 *
 *  @param  nvmprog_mode_u8 : The value of nvm program mode
 *     nvmprog_mode_u8      |    result
 *  ------------------------- |------------------
 *     0x00                   | Disable program mode
 *     0x01                   | Enable program mode
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_nvmprog_mode(u8 nvmprog_mode_u8);
/*!
 *  @brief This API is used to set
 *  the value of nvm program trig in the register 0x33 bit 1
 *
 *
 *
 *
 *  @param nvprog_trig_u8: The value of nvm program trig
 *     nvprog_trig_u8       |    result
 *  ------------------------- |------------------
 *     0x00                   | Do not trigger nvm program
 *     0x01                   | Trigger nvm program
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_nvprog_trig(u8 nvprog_trig_u8);
/*!
 * @brief This API is used to get
 * the nvm program ready in the register bit 2
 *
 *
 *  @param nvprog_ready_u8: The value of nvm program ready
 *     nvprog_ready_u8      |    result
 *  ------------------------- |------------------
 *     0x00                   | nvm write/update operation is in progress
 *     0x01                   | nvm is ready to accept a new write
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_nvmprog_ready(u8 *nvprog_ready_u8);
/*!
 * @brief This API is used to set
 * the nvm program ready in the register bit 2
 *
 *
 *  @param nvprog_remain_u8: The value of nvm program ready
 *     nvprog_remain_u8     |    result
 *  ------------------------- |------------------
 *     0x00                   | nvm write/update operation is in progress
 *     0x01                   | nvm is ready to accept a new write
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_nvmprog_remain(u8 *nvprog_remain_u8);
/******************************************/
/**\name FUNCTION FOR  SPI/I2C CONFIGURATION */
/******************************************/
/*!
 *  @brief This API is used to get the enable status of spi3
 *  in the register 0x34 bit 0
 *
 *
 *
 *  @param  spi3_u8 : The value of SPI 3 or 4 wire enable
 *     spi3_u8              |    result
 *  ------------------------- |------------------
 *     0x00                   |     spi4
 *     0x01                   |     spi3
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_spi3(u8 *spi3_u8);
/*!
 *  @brief This API is used to set the enable status of spi3
 *  in the register 0x34 bit 0
 *
 *
 *
 *  @param  spi3_u8 : The value of SPI 3 or 4 wire enable
 *     spi3_u8              |    result
 *  ------------------------- |------------------
 *     0x00                   |     spi4
 *     0x01                   |     spi3
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_spi3(u8 spi3_u8);
/*!
 *  @brief This API is used to get the i2c
 *  watch dog timer period and I2C interface mode is selected
 *  in the register 0x34 bit 1 and 2
 *
 *
 *  @param channel_u8: The i2c option selection
 *     channel_u8           |    result
 *  ------------------------- |------------------
 *        0                   |   BMA2x2_ACCEL_I2C_SELECT
 *        1                   |   BMA2x2_ACCEL_I2C_ENABLE
 *
 *  @param i2c_wdt_u8: watch dog timer period
 *  and I2C interface mode is selected
 *     BMA2x2_ACCEL_I2C_SELECT|    result
 *  ------------------------- |------------------
 *     0x00                   | Disable the watchdog at SDI pin
 *     0x01                   | Enable watchdog
 *
 *     BMA2x2_I2C_ENABLE      |    result
 *  ------------------------- |------------------
 *     0x00                   | 1ms
 *     0x01                   | 50ms
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_i2c_wdt(u8 channel_u8,
        u8 *i2c_wdt_u8);
/*!
 *  @brief This API is used to set the i2c
 *  watch dog timer period and I2C interface mode is selected
 *  in the register 0x34 bit 1 and 2
 *
 *
 *  @param channel_u8: The i2c option selection
 *     channel_u8           |    result
 *  ------------------------- |------------------
 *        0                   |   BMA2x2_ACCEL_I2C_SELECT
 *        1                   |   BMA2x2_ACCEL_I2C_ENABLE
 *
 *  @param i2c_wdt_u8: watch dog timer period
 *  and I2C interface mode is selected
 *     BMA2x2_ACCEL_I2C_SELECT|    result
 *  ------------------------- |------------------
 *     0x00                   | Disable the watchdog at SDI pin
 *     0x01                   | Enable watchdog
 *
 *     BMA2x2_I2C_ENABLE      |    result
 *  ------------------------- |------------------
 *     0x00                   | 1ms
 *     0x01                   | 50ms
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_i2c_wdt(u8 channel_u8,
        u8 i2c_wdt_u8);
/******************************************/
/**\name FUNCTION FOR OFFSET  */
/******************************************/
/*!
 *  @brief This API is used to get
 *  slow compensation(hp_x_enable, hp_y_enable and hp_z_enable) enable
 *  in the register 0x36 bit 0 to 2
 *  @note SLOW_COMP_X -> bit 0
 *  @note SLOW_COMP_Y -> bit 1
 *  @note SLOW_COMP_Z -> bit 2
 *
 *
 *  @param channel_u8: The value of slow compensation selection
 *     channel_u8           |    result
 *  ------------------------- |------------------
 *        0                   |   BMA2x2_ACCEL_SLOW_COMP_X
 *        1                   |   BMA2x2_ACCEL_SLOW_COMP_Y
 *        2                   |   BMA2x2_ACCEL_SLOW_COMP_Z
 *
 *  @param slow_comp_u8: The value of slow compensation enable
 *     slow_comp_u8         |    result
 *  ------------------------- |------------------
 *         0x00               |    Disable
 *        0x01                |    Enable
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_slow_comp(u8 channel_u8,
        u8 *slow_comp_u8);
/*!
 *  @brief This API is used to set
 *  slow compensation(hp_x_enable, hp_y_enable and hp_z_enable) enable
 *  in the register 0x36 bit 0 to 2
 *  @note SLOW_COMP_X -> bit 0
 *  @note SLOW_COMP_Y -> bit 1
 *  @note SLOW_COMP_Z -> bit 2
 *
 *
 *  @param channel_u8: The value of slow compensation selection
 *     channel_u8           |    result
 *  ------------------------- |------------------
 *        0                   |   BMA2x2_ACCEL_SLOW_COMP_X
 *        1                   |   BMA2x2_ACCEL_SLOW_COMP_Y
 *        2                   |   BMA2x2_ACCEL_SLOW_COMP_Z
 *
 *  @param slow_comp_u8: The value of slow compensation enable
 *     slow_comp_u8         |    result
 *  ------------------------- |------------------
 *         0x00               |    Disable
 *        0x01                |    Enable
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_slow_comp(u8 channel_u8,
        u8 slow_comp_u8);
/*!
 *  @brief This API is used to get
 *  the status of fast offset compensation(cal_rdy) in the register 0x36
 *  bit 4(Read Only Possible)
 *
 *
 *
 *  @param  cal_rdy_u8: The value of cal_ready
 *
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_cal_rdy(u8 *cal_rdy_u8);
/*!
 *  @brief This API is used to set
 *  the status of fast offset compensation(cal_rdy) in the register 0x36
 *  bit 4(Read Only Possible)
 *
 *
 *
 *  @param  cal_trigger_u8: The value of cal_ready
 *
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_cal_trigger(u8 cal_trigger_u8);
/*!
 *  @brief This API is used to set
 *  the offset reset(offset_reset) in the register 0x36
 *  bit 7(Write only possible)
 *
 *
 *
 *  @param  offset_rst_u8: The offset reset value
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_offset_rst(u8 offset_rst_u8);
/*!
 *  @brief This API is used to get
 *  the status of offset target axis(offset_target_x, offset_target_y and
 *  offset_target_z) and cut_off in the register 0x37
 *  @note CUT_OFF -> bit 0
 *  @note OFFSET_TRIGGER_X -> bit 1 and 2
 *  @note OFFSET_TRIGGER_Y -> bit 3 and 4
 *  @note OFFSET_TRIGGER_Z -> bit 5 and 6
 *
 *
 *  @param channel_u8: The value of offset axis selection
 *     channel_u8           |    result
 *  ------------------------- |------------------
 *        0                   |   BMA2x2_ACCEL_CUT_OFF
 *        1                   |   BMA2x2_ACCEL_OFFSET_TRIGGER_X
 *        2                   |   BMA2x2_ACCEL_OFFSET_TRIGGER_Y
 *        2                   |   BMA2x2_ACCEL_OFFSET_TRIGGER_Z
 *
 *  @param  offset_u8: The offset target value
 *     CUT_OFF                |    result
 *  ------------------------- |------------------
 *        0                   |   1Hz
 *        1                   |   10Hz
 *
 *
 *     OFFSET_TRIGGER         |    result
 *  ------------------------- |------------------
 *        0x00                |   0g
 *        0x01                |   +1g
 *        0x02                |   -1g
 *        0x03                |   0g
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_offset_target(u8 channel_u8,
        u8 *offset_u8);
/*!
 *  @brief This API is used to set
 *  the status of offset target axis(offset_target_x, offset_target_y and
 *  offset_target_z) and cut_off in the register 0x37
 *  @note CUT_OFF -> bit 0
 *  @note OFFSET_TRIGGER_X -> bit 1 and 2
 *  @note OFFSET_TRIGGER_Y -> bit 3 and 4
 *  @note OFFSET_TRIGGER_Z -> bit 5 and 6
 *
 *
 *  @param channel_u8: The value of offset axis selection
 *     channel_u8           |    result
 *  ------------------------- |------------------
 *        0                   |   BMA2x2_ACCEL_CUT_OFF
 *        1                   |   BMA2x2_ACCEL_OFFSET_TRIGGER_X
 *        2                   |   BMA2x2_ACCEL_OFFSET_TRIGGER_Y
 *        2                   |   BMA2x2_ACCEL_OFFSET_TRIGGER_Z
 *
 *  @param  offset_u8: The offset target value
 *     CUT_OFF                |    result
 *  ------------------------- |------------------
 *        0                   |   1Hz
 *        1                   |   10Hz
 *
 *
 *     OFFSET_TRIGGER         |    result
 *  ------------------------- |------------------
 *        0x00                |   0g
 *        0x01                |   +1g
 *        0x02                |   -1g
 *        0x03                |   0g
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_offset_target(u8 channel_u8,
        u8 offset_u8);
/*!
 *  @brief This API is used to get the status of offset
 *  (offset_x, offset_y and offset_z) in the registers 0x38,0x39 and 0x3A
 *  @note offset_x -> register 0x38 bit 0 to 7
 *  @note offset_y -> register 0x39 bit 0 to 7
 *  @note offset_z -> register 0x3A bit 0 to 7
 *
 *
 *  @param channel_u8: The value of offset selection
 *     channel_u8           |    result
 *  ------------------------- |------------------
 *        0                   |   BMA2x2_ACCEL_X_AXIS
 *        1                   |   BMA2x2_ACCEL_Y_AXIS
 *        2                   |   BMA2x2_ACCEL_Z_AXIS
 *
 *  @param offset_u8: The value of offset
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_offset(u8 channel_u8,
        s8 *offset_u8);
/*!
 *  @brief This API is used to set the status of offset
 *  (offset_x, offset_y and offset_z) in the registers 0x38,0x39 and 0x3A
 *  @note offset_x -> register 0x38 bit 0 to 7
 *  @note offset_y -> register 0x39 bit 0 to 7
 *  @note offset_z -> register 0x3A bit 0 to 7
 *
 *
 *  @param channel_u8: The value of offset selection
 *     channel_u8           |    result
 *  ------------------------- |------------------
 *        0                   |   BMA2x2_ACCEL_X_AXIS
 *        1                   |   BMA2x2_ACCEL_Y_AXIS
 *        2                   |   BMA2x2_ACCEL_Z_AXIS
 *
 *  @param offset_u8: The value of offset
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_offset(u8 channel_u8,
        s8 offset_u8);
/******************************************/
/**\name FUNCTION FOR FIFO CONFIGURATION  */
/******************************************/
/*!
 *  @brief This API is used to get
 *  the status of fifo (fifo_mode) in the register 0x3E bit 6 and 7
 *
 *
 *  @param fifo_mode_u8 : The value of fifo mode
 *     fifo_mode_u8         |    result
 *  ------------------------- |------------------
 *        0x00                |   BYPASS
 *        0x01                |   FIFO
 *        0x02                |   STREAM
 *        0x03                |   RESERVED
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_fifo_mode(u8 *fifo_mode_u8);
/*!
 *  @brief This API is used to set
 *  the status of fifo (fifo_mode) in the register 0x3E bit 6 and 7
 *
 *
 *  @param fifo_mode_u8 : The value of fifo mode
 *     fifo_mode_u8         |    result
 *  ------------------------- |------------------
 *        0x00                |   BYPASS
 *        0x01                |   FIFO
 *        0x02                |   STREAM
 *        0x03                |   RESERVED
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_fifo_mode(u8 fifo_mode_u8);
/*!
 * @brief This API is used to get
 * the axis enable of fifo data select in the register 0x3E bit 0 and 1
 *
 *
 *  @param fifo_data_select_u8 : The value of FIFO axis data select
 *   fifo_data_select_u8    |    result
 *  ------------------------- |------------------
 *        0x00                |   XYZ
 *        0x01                |   Y
 *        0x02                |   X
 *        0x03                |   Z
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_fifo_data_select(
    u8 *fifo_data_select_u8);
/*!
 * @brief This API is used to set
 * the axis enable of fifo data select in the register 0x3E bit 0 and 1
 *
 *
 *  @param fifo_data_select_u8 : The value of FIFO axis data select
 *   fifo_data_select_u8    |    result
 *  ------------------------- |------------------
 *        0x00                |   XYZ
 *        0x01                |   Y
 *        0x02                |   X
 *        0x03                |   Z
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_fifo_data_select(
    u8 fifo_data_select_u8);

/*!
 *  @brief This API reads the FIFO data from the register 0x3F
 *  and store the data in the user defined buffer mapped to the member
 *  of structure "fifo_configuration"
 *
 *  @note Before calling this API user must map the following FIFO settings
 *  required to read the FIFO data to the structure "fifo_configuration"
 *    - Data buffer to store the FIFO data is mapped to
 *      the structure member "fifo_data"
 *    - Number of bytes to be read from FIFO is mapped to
 *      the structure member "fifo_length"
 *
 *  @note The number of bytes to be read from the FIFO is specified in the
 *  member "fifo_length" of the structure "fifo_configuration"
 *
 *  @param[in,out] fifo_conf : Structure containing the FIFO configurations
 *  is passed as input and FIFO data of specified length is obtained as output
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_read_fifo_data(
    struct fifo_configuration *fifo_conf);

/*!
 *  @brief This API extracts the accel data from the FIFO frames
 *
 *  @note The bma2x2_extract_accel() API should be called only after reading
 *  the FIFO data by calling the bma2x2_read_fifo_data() API
 *
 *  @param[in,out] accel_frame      : Instance of the union where accel data
 *                                    in FIFO is parsed and stored
 *
 *  @param[in,out] accel_frame_count: Number of Accel frames requested by user
 *                                    is got as input and number of
 *                                    accel frames parsed and stored is
 *                                    returned as output to user
 *
 *  @param[in, out] fifo_conf       : FIFO configuration structure.
 *                                    It provides the following as input
 *                                        - user defined buffer
 *                                        - length of FIFO data read
 *                                    It returns the accel_byte_start_index
 *                                    (index of accel bytes parsed from FIFO)
 *
 *  @return results of API execution status
 *  @retval 0 -> Success
 *  @retval -127 -> Error
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_extract_accel(union fifo_frame *accel_frame,
        u8 *accel_frame_count, struct fifo_configuration *fifo_conf);
/******************************************/
/**\name FUNCTION FOR  TEMPERATURE DATA READ */
/******************************************/
/*!
 * @brief This API is used to read the temp
 * from register 0x08
 *
 *
 *
 *  @param  temp_s8: The value of temperature
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_read_temp(s8 *temp_s8);
/******************************************/
/**\name FUNCTION FOR  DATA XYZ WITH TEMPERATURE */
/******************************************/
/*!
 * @brief This API reads accelerometer data X,Y,Z values and
 * temperature data from location 02h to 08h
 *
 *
 *
 *
 *  @param accel : The value of accel xyz and temperature data
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_read_accel_xyzt(
    struct bma2x2_accel_data_temp *accel);
/*!
 * @brief This API reads accelerometer data X,Y,Z values and
 * temperature data from location 0x02 to 0x08
 *
 *
 *
 *
 *  @param accel : The value of accel xyz and temperature data
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_read_accel_eight_resolution_xyzt(
    struct bma2x2_accel_eight_resolution_temp *accel);
/*Depreciated Functions*/
/*!
 *  @brief This API is used to get
 *  the fifo data in the register 0x3F bit 0 to 7
 *
 *
 *  @param  output_reg_u8 : The value of fifo data
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_fifo_data_output_reg(
    u8 *output_reg_u8);
#endif

