/** \mainpage
*
****************************************************************************
* Copyright (C) 2015 - 2016 Bosch Sensortec GmbH
*
* File : bmm050.h
*
* Date : 2016/03/17
*
* Revision : 2.0.5 $
*
* Usage: Sensor Driver for BMM050 and BMM150 sensor
*
****************************************************************************
*
* \section License
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
*   Redistributions of source code must retain the above copyright
*   notice, this list of conditions and the following disclaimer.
*
*   Redistributions in binary form must reproduce the above copyright
*   notice, this list of conditions and the following disclaimer in the
*   documentation and/or other materials provided with the distribution.
*
*   Neither the name of the copyright holder nor the names of the
*   contributors may be used to endorse or promote products derived from
*   this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER
* OR CONTRIBUTORS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
* OR CONSEQUENTIAL DAMAGES(INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
*
* The information provided is believed to be accurate and reliable.
* The copyright holder assumes no responsibility
* for the consequences of use
* of such information nor for any infringement of patents or
* other rights of third parties which may result from its use.
* No license is granted by implication or otherwise under any patent or
* patent rights of the copyright holder.
**************************************************************************/
/****************************************************************************/

/*! \file bmm050.h
    \brief BMM050 Sensor Driver Support Header File */

#ifndef __BMM050_H__
#define __BMM050_H__

/*!
* @brief For Enabling and Disabling the floating point API's
* If your platform supports the FLOAT support, please enable this
* macro
*/
/*#define ENABLE_FLOAT*/

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

                #if defined(LONG_MAX) && (LONG_MAX == 0x7fffffffffffffffL)
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
    @brief Define the calling convention of YOUR bus communication routine.
    @note This includes types of parameters. This example shows the
    configuration for an SPI bus link.

    If your communication function looks like this:

    write_my_bus_xy(u8 device_addr, u8 register_addr,
    u8 * data, u8 length);

    The BMM050_WR_FUNC_PTR would equal:

    BMM050_WR_FUNC_PTR s8 (* bus_write)(u8,
    u8, u8 *, u8)

    Parameters can be mixed as needed refer to the
    refer BMM050_BUS_WRITE_FUNC  macro.


*/
#define BMM050_BUS_WR_RETURN_TYPE s8
#define BMM050_BUS_WR_PARAM_TYPES \
u8, u8, u8 *, u8
#define BMM050_BUS_WR_PARAM_ORDER \
(device_addr, register_addr, register_data, wr_len)
#define BMM050_BUS_WRITE_FUNC( \
device_addr, register_addr, register_data, wr_len) \
bus_write(device_addr, register_addr, register_data, wr_len)

/*!
    @brief  link macro between API function calls and bus read function
    @note The bus write function can change since this is a
    system dependant issue.

    @note If the bus_read parameter calling order is like: reg_addr,
    reg_data, wr_len it would be as it is here.

    @note If the parameters are differently ordered or your communication
    function like I2C need to know the device address,
    you can change this macro accordingly.


    @note BMM050_BUS_READ_FUNC(dev_addr, reg_addr, reg_data, wr_len)\
    bus_read(dev_addr, reg_addr, reg_data, wr_len)

    @note This macro lets all API functions call
    YOUR communication routine in a
    way that equals your definition in the
    refer BMM050_RD_FUNC_PTR definition.

    @note : this macro also includes the "MSB='1'
    for reading BMM050 addresses.

*/
#define BMM050_BUS_RD_RETURN_TYPE s8
#define BMM050_BUS_RD_PARAM_TYPES \
u8, u8, u8 *, u8
#define BMM050_BUS_RD_PARAM_ORDER (device_addr, register_addr, register_data)
#define BMM050_BUS_READ_FUNC(device_addr, register_addr, register_data, rd_len)\
bus_read(device_addr, register_addr, register_data, rd_len)
/***************************************************************/
/**\name    RETURN TYPE DEFINITIONS        */
/***************************************************************/
#define BMM050_DELAY_RETURN_TYPE void
#define BMM050_DELAY_FUNC(delay_in_msec) \
delay_func(delay_in_msec)
#define BMM050_RETURN_FUNCTION_TYPE        s8
/***************************************************************/
/**\name    I2C ADDRESS DEFINITIONS        */
/***************************************************************/
#define BMM050_I2C_ADDRESS                 (0x10)
/***************************************************************/
/**\name    REGISTER ADDRESS DEFINITION        */
/***************************************************************/
/********************************************/
/**\name    CHIP ID       */
/********************************************/
/* Fixed Data Registers */
#define BMM050_CHIP_ID                     (0x40)
/********************************************/
/**\name    DATA REGISTERS       */
/********************************************/
/* Data Registers*/
#define BMM050_DATA_X_LSB                   (0x42)
#define BMM050_DATA_X_MSB                   (0x43)
#define BMM050_DATA_Y_LSB                   (0x44)
#define BMM050_DATA_Y_MSB                   (0x45)
#define BMM050_DATA_Z_LSB                   (0x46)
#define BMM050_DATA_Z_MSB                   (0x47)
#define BMM050_DATA_R_LSB                   (0x48)
#define BMM050_DATA_R_MSB                   (0x49)
/********************************************/
/**\name    REMAPPED DATA REGISTERS      */
/********************************************/
/* Data Registers for remapped axis(XandY)
 * this only applicable for BMX055 */
#define BMM050_REMAPPED_BMX055_DATA_Y_LSB      (0x42)
#define BMM050_REMAPPED_BMX055_DATA_Y_MSB      (0x43)
#define BMM050_REMAPPED_BMX055_DATA_X_LSB      (0x44)
#define BMM050_REMAPPED_BMX055_DATA_X_MSB      (0x45)
/********************************************/
/**\name    INTERRUPT STATUS      */
/********************************************/
/* Status Registers */
#define BMM050_INT_STAT_REG                    (0x4A)
/********************************************/
/**\name    POWER MODE DEFINITIONS      */
/********************************************/
/* Control Registers */
#define BMM050_POWER_CONTROL               (0x4B)
#define BMM050_CONTROL                     (0x4C)
#define BMM050_INT_CONTROL                 (0x4D)
#define BMM050_SENS_CONTROL                (0x4E)
#define BMM050_LOW_THRES                   (0x4F)
#define BMM050_HIGH_THRES                  (0x50)
/********************************************/
/**\name XY AND Z REPETITIONS DEFINITIONS  */
/********************************************/
#define BMM050_REP_XY                      (0x51)
#define BMM050_REP_Z                       (0x52)
/********************************************/
/**\name    TRIM REGISTERS      */
/********************************************/
/* Trim Extended Registers */
#define BMM050_DIG_X1                      (0x5D)
#define BMM050_DIG_Y1                      (0x5E)
#define BMM050_DIG_Z4_LSB                  (0x62)
#define BMM050_DIG_Z4_MSB                  (0x63)
#define BMM050_DIG_X2                      (0x64)
#define BMM050_DIG_Y2                      (0x65)
#define BMM050_DIG_Z2_LSB                  (0x68)
#define BMM050_DIG_Z2_MSB                  (0x69)
#define BMM050_DIG_Z1_LSB                  (0x6A)
#define BMM050_DIG_Z1_MSB                  (0x6B)
#define BMM050_DIG_XYZ1_LSB                (0x6C)
#define BMM050_DIG_XYZ1_MSB                (0x6D)
#define BMM050_DIG_Z3_LSB                  (0x6E)
#define BMM050_DIG_Z3_MSB                  (0x6F)
#define BMM050_DIG_XY2                     (0x70)
#define BMM050_DIG_XY1                     (0x71)

/********************************************/
/**\name BIT MASK, LENGTH AND POSITION OF DATA REGISTERS   */
/********************************************/
/* Data X LSB Register */
#define BMM050_DATA_X_LSB_BIT__POS        (3)
#define BMM050_DATA_X_LSB_BIT__LEN        (5)
#define BMM050_DATA_X_LSB_BIT__MSK        (0xF8)
#define BMM050_DATA_X_LSB_BIT__REG        (BMM050_DATA_X_LSB)

/* Data X SelfTest Register */
#define BMM050_DATA_X_LSB_TESTX__POS         (0)
#define BMM050_DATA_X_LSB_TESTX__LEN         (1)
#define BMM050_DATA_X_LSB_TESTX__MSK         (0x01)
#define BMM050_DATA_X_LSB_TESTX__REG         (BMM050_DATA_X_LSB)

/* Data Y LSB Register */
#define BMM050_DATA_Y_LSB_BIT__POS        (3)
#define BMM050_DATA_Y_LSB_BIT__LEN        (5)
#define BMM050_DATA_Y_LSB_BIT__MSK        (0xF8)
#define BMM050_DATA_Y_LSB_BIT__REG        (BMM050_DATA_Y_LSB)

/* Data Y SelfTest Register */
#define BMM050_DATA_Y_LSB_TESTY__POS         (0)
#define BMM050_DATA_Y_LSB_TESTY__LEN         (1)
#define BMM050_DATA_Y_LSB_TESTY__MSK         (0x01)
#define BMM050_DATA_Y_LSB_TESTY__REG         (BMM050_DATA_Y_LSB)

/* Data Z LSB Register */
#define BMM050_DATA_Z_LSB_BIT__POS        (1)
#define BMM050_DATA_Z_LSB_BIT__LEN        (7)
#define BMM050_DATA_Z_LSB_BIT__MSK        (0xFE)
#define BMM050_DATA_Z_LSB_BIT__REG        (BMM050_DATA_Z_LSB)

/* Data Z SelfTest Register */
#define BMM050_DATA_Z_LSB_TESTZ__POS         (0)
#define BMM050_DATA_Z_LSB_TESTZ__LEN         (1)
#define BMM050_DATA_Z_LSB_TESTZ__MSK         (0x01)
#define BMM050_DATA_Z_LSB_TESTZ__REG         (BMM050_DATA_Z_LSB)

/* Hall Resistance LSB Register */
#define BMM050_DATA_R_LSB_BIT__POS             (2)
#define BMM050_DATA_R_LSB_BIT__LEN             (6)
#define BMM050_DATA_R_LSB_BIT__MSK             (0xFC)
#define BMM050_DATA_R_LSB_BIT__REG             (BMM050_DATA_R_LSB)

#define BMM050_DATA_RDYSTAT__POS            (0)
#define BMM050_DATA_RDYSTAT__LEN            (1)
#define BMM050_DATA_RDYSTAT__MSK            (0x01)
#define BMM050_DATA_RDYSTAT__REG            (BMM050_DATA_R_LSB)
/********************************************/
/**\name BIT MASK, LENGTH AND POSITION OF REMAPPED DATA REGISTERS   */
/********************************************/
/* Data X LSB Remapped Register only applicable for BMX055 */
#define BMM050_REMAPPED_BMX055_DATA_X_LSB_BIT__POS        (3)
#define BMM050_REMAPPED_BMX055_DATA_X_LSB_BIT__LEN        (5)
#define BMM050_REMAPPED_BMX055_DATA_X_LSB_BIT__MSK        (0xF8)
#define BMM050_REMAPPED_BMX055_DATA_X_LSB_BIT__REG\
(BMM050_REMAPPED_BMX055_DATA_X_LSB)

/* Data Y LSB Remapped Register only applicable for BMX055  */
#define BMM050_REMAPPED_BMX055_DATA_Y_LSB_BIT__POS        (3)
#define BMM050_REMAPPED_BMX055_DATA_Y_LSB_BIT__LEN        (5)
#define BMM050_REMAPPED_BMX055_DATA_Y_LSB_BIT__MSK        (0xF8)
#define BMM050_REMAPPED_BMX055_DATA_Y_LSB_BIT__REG\
(BMM050_REMAPPED_BMX055_DATA_Y_LSB)
/********************************************/
/**\name BIT MASK, LENGTH AND POSITION OF INTERRUPT STATUS REGISTERS   */
/********************************************/
/* Interrupt Status Register */
#define BMM050_INT_STAT_DOR__POS            (7)
#define BMM050_INT_STAT_DOR__LEN            (1)
#define BMM050_INT_STAT_DOR__MSK            (0x80)
#define BMM050_INT_STAT_DOR__REG            (BMM050_INT_STAT_REG)

#define BMM050_INT_STAT_OVRFLOW__POS        (6)
#define BMM050_INT_STAT_OVRFLOW__LEN        (1)
#define BMM050_INT_STAT_OVRFLOW__MSK        (0x40)
#define BMM050_INT_STAT_OVRFLOW__REG        (BMM050_INT_STAT_REG)

#define BMM050_INT_STAT_HIGH_THZ__POS       (5)
#define BMM050_INT_STAT_HIGH_THZ__LEN       (1)
#define BMM050_INT_STAT_HIGH_THZ__MSK       (0x20)
#define BMM050_INT_STAT_HIGH_THZ__REG       (BMM050_INT_STAT_REG)

#define BMM050_INT_STAT_HIGH_THY__POS       (4)
#define BMM050_INT_STAT_HIGH_THY__LEN       (1)
#define BMM050_INT_STAT_HIGH_THY__MSK       (0x10)
#define BMM050_INT_STAT_HIGH_THY__REG       (BMM050_INT_STAT_REG)

#define BMM050_INT_STAT_HIGH_THX__POS       (3)
#define BMM050_INT_STAT_HIGH_THX__LEN       (1)
#define BMM050_INT_STAT_HIGH_THX__MSK       (0x08)
#define BMM050_INT_STAT_HIGH_THX__REG       (BMM050_INT_STAT_REG)

#define BMM050_INT_STAT_LOW_THZ__POS        (2)
#define BMM050_INT_STAT_LOW_THZ__LEN        (1)
#define BMM050_INT_STAT_LOW_THZ__MSK        (0x04)
#define BMM050_INT_STAT_LOW_THZ__REG        (BMM050_INT_STAT_REG)

#define BMM050_INT_STAT_LOW_THY__POS        (1)
#define BMM050_INT_STAT_LOW_THY__LEN        (1)
#define BMM050_INT_STAT_LOW_THY__MSK        (0x02)
#define BMM050_INT_STAT_LOW_THY__REG        (BMM050_INT_STAT_REG)

#define BMM050_INT_STAT_LOW_THX__POS        (0)
#define BMM050_INT_STAT_LOW_THX__LEN        (1)
#define BMM050_INT_STAT_LOW_THX__MSK        (0x01)
#define BMM050_INT_STAT_LOW_THX__REG        (BMM050_INT_STAT_REG)
/********************************************/
/**\name BIT MASK, LENGTH AND POSITION OF SOFT RESET REGISTERS   */
/********************************************/
/* Power Control Register */
#define BMM050_POWER_CONTROL_SOFT_RST_7__POS       (7)
#define BMM050_POWER_CONTROL_SOFT_RST_7__LEN       (1)
#define BMM050_POWER_CONTROL_SOFT_RST_7__MSK       (0x80)
#define BMM050_POWER_CONTROL_SOFT_RST_7__REG       (BMM050_POWER_CONTROL)

#define BMM050_POWER_CONTROL_SPI3_ENABLE__POS     (2)
#define BMM050_POWER_CONTROL_SPI3_ENABLE__LEN     (1)
#define BMM050_POWER_CONTROL_SPI3_ENABLE__MSK     (0x04)
#define BMM050_POWER_CONTROL_SPI3_ENABLE__REG     (BMM050_POWER_CONTROL)

#define BMM050_POWER_CONTROL_SOFT_RST_1__POS       (1)
#define BMM050_POWER_CONTROL_SOFT_RST_1__LEN       (1)
#define BMM050_POWER_CONTROL_SOFT_RST_1__MSK       (0x02)
#define BMM050_POWER_CONTROL_SOFT_RST_1__REG       (BMM050_POWER_CONTROL)
/********************************************/
/**\name BIT MASK, LENGTH AND POSITION OF POWER MODE REGISTERS   */
/********************************************/
#define BMM050_POWER_CONTROL_POWER_CONTROL_BIT__POS         (0)
#define BMM050_POWER_CONTROL_POWER_CONTROL_BIT__LEN         (1)
#define BMM050_POWER_CONTROL_POWER_CONTROL_BIT__MSK         (0x01)
#define BMM050_POWER_CONTROL_POWER_CONTROL_BIT__REG         \
(BMM050_POWER_CONTROL)
/********************************************/
/**\name BIT MASK, LENGTH AND POSITION OF SELF TEST REGISTERS   */
/********************************************/
/* Control Register */
#define BMM050_CONTROL_ADVANCED_SELFTEST__POS            (6)
#define BMM050_CONTROL_ADVANCED_SELFTEST__LEN            (2)
#define BMM050_CONTROL_ADVANCED_SELFTEST__MSK            (0xC0)
#define BMM050_CONTROL_ADVANCED_SELFTEST__REG            (BMM050_CONTROL)
/********************************************/
/**\name BIT MASK, LENGTH AND POSITION OF DATA RATE REGISTERS   */
/********************************************/
#define BMM050_CONTROL_DATA_RATE__POS                (3)
#define BMM050_CONTROL_DATA_RATE__LEN                (3)
#define BMM050_CONTROL_DATA_RATE__MSK                (0x38)
#define BMM050_CONTROL_DATA_RATE__REG                (BMM050_CONTROL)
/********************************************/
/**\name BIT MASK, LENGTH AND POSITION OF OPERATION MODE REGISTERS   */
/********************************************/
#define BMM050_CONTROL_OPERATION_MODE__POS            (1)
#define BMM050_CONTROL_OPERATION_MODE__LEN            (2)
#define BMM050_CONTROL_OPERATION_MODE__MSK            (0x06)
#define BMM050_CONTROL_OPERATION_MODE__REG            (BMM050_CONTROL)
/********************************************/
/**\name BIT MASK, LENGTH AND POSITION OF SELF TEST REGISTERS   */
/********************************************/
#define BMM050_CONTROL_SELFTEST__POS            (0)
#define BMM050_CONTROL_SELFTEST__LEN            (1)
#define BMM050_CONTROL_SELFTEST__MSK            (0x01)
#define BMM050_CONTROL_SELFTEST__REG            (BMM050_CONTROL)
/********************************************/
/**\name BIT MASK, LENGTH AND POSITION OF INTERRUPT CONTROL REGISTERS   */
/********************************************/
/* Interrupt Control Register */
#define BMM050_INT_CONTROL_DOR_EN__POS            (7)
#define BMM050_INT_CONTROL_DOR_EN__LEN            (1)
#define BMM050_INT_CONTROL_DOR_EN__MSK            (0x80)
#define BMM050_INT_CONTROL_DOR_EN__REG            (BMM050_INT_CONTROL)

#define BMM050_INT_CONTROL_OVRFLOW_EN__POS        (6)
#define BMM050_INT_CONTROL_OVRFLOW_EN__LEN        (1)
#define BMM050_INT_CONTROL_OVRFLOW_EN__MSK        (0x40)
#define BMM050_INT_CONTROL_OVRFLOW_EN__REG        (BMM050_INT_CONTROL)

#define BMM050_INT_CONTROL_HIGH_THZ_EN__POS       (5)
#define BMM050_INT_CONTROL_HIGH_THZ_EN__LEN       (1)
#define BMM050_INT_CONTROL_HIGH_THZ_EN__MSK       (0x20)
#define BMM050_INT_CONTROL_HIGH_THZ_EN__REG       (BMM050_INT_CONTROL)

#define BMM050_INT_CONTROL_HIGH_THY_EN__POS       (4)
#define BMM050_INT_CONTROL_HIGH_THY_EN__LEN       (1)
#define BMM050_INT_CONTROL_HIGH_THY_EN__MSK       (0x10)
#define BMM050_INT_CONTROL_HIGH_THY_EN__REG       (BMM050_INT_CONTROL)

#define BMM050_INT_CONTROL_HIGH_THX_EN__POS       (3)
#define BMM050_INT_CONTROL_HIGH_THX_EN__LEN       (1)
#define BMM050_INT_CONTROL_HIGH_THX_EN__MSK       (0x08)
#define BMM050_INT_CONTROL_HIGH_THX_EN__REG       (BMM050_INT_CONTROL)

#define BMM050_INT_CONTROL_LOW_THZ_EN__POS        (2)
#define BMM050_INT_CONTROL_LOW_THZ_EN__LEN        (1)
#define BMM050_INT_CONTROL_LOW_THZ_EN__MSK        (0x04)
#define BMM050_INT_CONTROL_LOW_THZ_EN__REG        (BMM050_INT_CONTROL)

#define BMM050_INT_CONTROL_LOW_THY_EN__POS        (1)
#define BMM050_INT_CONTROL_LOW_THY_EN__LEN        (1)
#define BMM050_INT_CONTROL_LOW_THY_EN__MSK        (0x02)
#define BMM050_INT_CONTROL_LOW_THY_EN__REG        (BMM050_INT_CONTROL)

#define BMM050_INT_CONTROL_LOW_THX_EN__POS        (0)
#define BMM050_INT_CONTROL_LOW_THX_EN__LEN        (1)
#define BMM050_INT_CONTROL_LOW_THX_EN__MSK        (0x01)
#define BMM050_INT_CONTROL_LOW_THX_EN__REG        (BMM050_INT_CONTROL)

/* Sensor Control Register */
#define BMM050_SENS_CONTROL_DRDY_EN__POS          (7)
#define BMM050_SENS_CONTROL_DRDY_EN__LEN          (1)
#define BMM050_SENS_CONTROL_DRDY_EN__MSK          (0x80)
#define BMM050_SENS_CONTROL_DRDY_EN__REG          (BMM050_SENS_CONTROL)

#define BMM050_SENS_CONTROL_IE__POS               (6)
#define BMM050_SENS_CONTROL_IE__LEN               (1)
#define BMM050_SENS_CONTROL_IE__MSK               (0x40)
#define BMM050_SENS_CONTROL_IE__REG               BMM050_SENS_CONTROL

#define BMM050_SENS_CONTROL_CHANNELZ__POS         (5)
#define BMM050_SENS_CONTROL_CHANNELZ__LEN         (1)
#define BMM050_SENS_CONTROL_CHANNELZ__MSK         (0x20)
#define BMM050_SENS_CONTROL_CHANNELZ__REG         (BMM050_SENS_CONTROL)

#define BMM050_SENS_CONTROL_CHANNELY__POS         (4)
#define BMM050_SENS_CONTROL_CHANNELY__LEN         (1)
#define BMM050_SENS_CONTROL_CHANNELY__MSK         (0x10)
#define BMM050_SENS_CONTROL_CHANNELY__REG         (BMM050_SENS_CONTROL)

#define BMM050_SENS_CONTROL_CHANNELX__POS         (3)
#define BMM050_SENS_CONTROL_CHANNELX__LEN         (1)
#define BMM050_SENS_CONTROL_CHANNELX__MSK         (0x08)
#define BMM050_SENS_CONTROL_CHANNELX__REG         (BMM050_SENS_CONTROL)

#define BMM050_SENS_CONTROL_DR_POLARITY__POS      (2)
#define BMM050_SENS_CONTROL_DR_POLARITY__LEN      (1)
#define BMM050_SENS_CONTROL_DR_POLARITY__MSK      (0x04)
#define BMM050_SENS_CONTROL_DR_POLARITY__REG      (BMM050_SENS_CONTROL)

#define BMM050_SENS_CONTROL_INTERRUPT_LATCH__POS    (1)
#define BMM050_SENS_CONTROL_INTERRUPT_LATCH__LEN    (1)
#define BMM050_SENS_CONTROL_INTERRUPT_LATCH__MSK    (0x02)
#define BMM050_SENS_CONTROL_INTERRUPT_LATCH__REG    (BMM050_SENS_CONTROL)

#define BMM050_SENS_CONTROL_INTERRUPT_POLARITY__POS         (0)
#define BMM050_SENS_CONTROL_INTERRUPT_POLARITY__LEN         (1)
#define BMM050_SENS_CONTROL_INTERRUPT_POLARITY__MSK         (0x01)
#define BMM050_SENS_CONTROL_INTERRUPT_POLARITY__REG         \
(BMM050_SENS_CONTROL)
/********************************************/
/**\name BIT MASK, LENGTH AND POSITION OF TRIM REGISTER   */
/********************************************/
/* Register 6D */
#define BMM050_DIG_XYZ1_MSB__POS         (0)
#define BMM050_DIG_XYZ1_MSB__LEN         (7)
#define BMM050_DIG_XYZ1_MSB__MSK         (0x7F)
#define BMM050_DIG_XYZ1_MSB__REG         (BMM050_DIG_XYZ1_MSB)
/*****************************************************************/
/********************************************/
/**\name CONSTANTS DEFINITIONS  */
/********************************************/
/********************************************/
/**\name ERROR CODE */
/********************************************/

/** Error code definitions**/
#define E_BMM050_NULL_PTR           ((s8)-127)
#define ERROR                       ((s8)-1)
#define E_BMM050_OUT_OF_RANGE       ((s8)-2)
#define BMM050_NULL                 ((u8)0)
#define E_BMM050_UNDEFINED_MODE     (0)

/********************************************/
/**\name RESET DEFINITIONS */
/********************************************/
/*General Info data's*/
#define BMM050_SOFT_RESET7_ON              (1)
#define BMM050_SOFT_RESET1_ON              (1)
#define BMM050_SOFT_RESET7_OFF             (0)
#define BMM050_SOFT_RESET1_OFF             (0)
#define BMM050_DELAY_SOFTRESET             (1)

/********************************************/
/**\name DELAY DEFINITIONS  */
/********************************************/
/* Constants */
#define BMM050_DELAY_POWEROFF_SUSPEND      (1)
#define BMM050_DELAY_SUSPEND_SLEEP         (3)
#define BMM050_DELAY_SLEEP_ACTIVE          (1)
#define BMM050_DELAY_ACTIVE_SLEEP          (1)
#define BMM050_DELAY_SLEEP_SUSPEND         (1)
#define BMM050_DELAY_ACTIVE_SUSPEND        (1)
#define BMM050_DELAY_SLEEP_POWEROFF        (1)
#define BMM050_DELAY_ACTIVE_POWEROFF       (1)
#define BMM050_DELAY_SETTLING_TIME         (3)
#define BMM050_MDELAY_DATA_TYPE           u32
/********************************************/
/**\name XYZ AXIS DEFINITIONS  */
/********************************************/
#define BMM050_X_AXIS               (0)
#define BMM050_Y_AXIS               (1)
#define BMM050_Z_AXIS               (2)
#define BMM050_RESISTANCE           (3)
#define BMM050_X                    (1)
#define BMM050_Y                    (2)
#define BMM050_Z                    (4)
#define BMM050_XYZ                  (7)
/********************************************/
/**\name ENABLE/DISABLE DEFINITIONS  */
/********************************************/
#define BMM050_CHANNEL_DISABLE                  (1)
#define BMM050_CHANNEL_ENABLE                   (0)
#define BMM050_OFF                              (0)
#define BMM050_ON                               (1)
/********************************************/
/**\name POWER MODE DEFINITIONS  */
/********************************************/
#define BMM050_NORMAL_MODE                      (0x00)
#define BMM050_FORCED_MODE                      (0x01)
#define BMM050_SUSPEND_MODE                     (0x02)
#define BMM050_SLEEP_MODE                       (0x03)
/********************************************/
/**\name SELF TEST DEFINITIONS  */
/********************************************/
#define BMM050_ADVANCED_SELFTEST_OFF            (0)
#define BMM050_ADVANCED_SELFTEST_NEGATIVE       (2)
#define BMM050_ADVANCED_SELFTEST_POSITIVE       (3)

#define BMM050_NEGATIVE_SATURATION_Z            (-32767)
#define BMM050_POSITIVE_SATURATION_Z            (32767)
/********************************************/
/**\name SPI READ/WRITE DEFINITIONS  */
/********************************************/
#define BMM050_SPI_RD_MASK                      (0x80)
#define BMM050_READ_SET                         (0x01)
/********************************************/
/**\name READ AND WRITE FUNCTION POINTERS  */
/********************************************/
/* Bus read and bus write */
#define BMM050_WR_FUNC_PTR \
    s8 (*bus_write)(u8, u8, \
    u8 *, u8)

#define BMM050_RD_FUNC_PTR \
    s8 (*bus_read)(u8, u8, \
    u8 *, u8)

/********************************************/
/**\name NUMERIC DEFINITIONS  */
/********************************************/
#define  BMM050_GEN_READ_WRITE_DATA_LENGTH      ((u8)1)
#define  BMM050_TRIM_DATA_LENGTH        ((u8)2)
#define  BMM050_SELFTEST_DELAY          ((u8)4)
#define  BMM050_SELFTEST_DATA_LENGTH    ((u8)5)
#define  BMM050_ALL_DATA_FRAME_LENGTH   ((u8)8)
/**< Frame length refers the
x,y,z and r values*/
#define BMM050_INIT_VALUE               (0)

/********************************************/
/**\name GET AND SET BITSLICE FUNCTIONS  */
/********************************************/
/* get bit slice  */
#define BMM050_GET_BITSLICE(regvar, bitname)\
    ((regvar & bitname##__MSK) >> bitname##__POS)

/* Set bit slice */
#define BMM050_SET_BITSLICE(regvar, bitname, val)\
    ((regvar & ~bitname##__MSK) | ((val<<bitname##__POS)&bitname##__MSK))

/********************************************/
/**\name OVERFLOW DEFINITIONS  */
/********************************************/
/* compensated output value returned if sensor had overflow */
#define BMM050_OVERFLOW_OUTPUT          -32768
#define BMM050_OVERFLOW_OUTPUT_S32      ((s32)(-2147483647-1))
#define BMM050_OVERFLOW_OUTPUT_FLOAT    0.0f
#define BMM050_FLIP_OVERFLOW_ADCVAL     -4096
#define BMM050_HALL_OVERFLOW_ADCVAL     -16384
/********************************************/
/**\name PRESET MODE DEFINITIONS  */
/********************************************/
#define BMM050_PRESETMODE_LOWPOWER                  (1)
#define BMM050_PRESETMODE_REGULAR                   (2)
#define BMM050_PRESETMODE_HIGHACCURACY              (3)
#define BMM050_PRESETMODE_ENHANCED                  (4)

/* PRESET MODES - DATA RATES */
#define BMM050_LOWPOWER_DR                       (BMM050_DR_10HZ)
#define BMM050_REGULAR_DR                        (BMM050_DR_10HZ)
#define BMM050_HIGHACCURACY_DR                   (BMM050_DR_20HZ)
#define BMM050_ENHANCED_DR                       (BMM050_DR_10HZ)

/* PRESET MODES - REPETITIONS-XY RATES */
#define BMM050_LOWPOWER_REPXY                     (1)
#define BMM050_REGULAR_REPXY                      (4)
#define BMM050_HIGHACCURACY_REPXY                (23)
#define BMM050_ENHANCED_REPXY                     (7)

/* PRESET MODES - REPETITIONS-Z RATES */
#define BMM050_LOWPOWER_REPZ                      (2)
#define BMM050_REGULAR_REPZ                      (14)
#define BMM050_HIGHACCURACY_REPZ                 (82)
#define BMM050_ENHANCED_REPZ                     (26)
/********************************************/
/**\name DATA RATE DEFINITIONS  */
/********************************************/
/* Data Rates */
#define BMM050_DR_10HZ                     (0)
#define BMM050_DR_02HZ                     (1)
#define BMM050_DR_06HZ                     (2)
#define BMM050_DR_08HZ                     (3)
#define BMM050_DR_15HZ                     (4)
#define BMM050_DR_20HZ                     (5)
#define BMM050_DR_25HZ                     (6)
#define BMM050_DR_30HZ                     (7)

#define BMM050_DATA_RATE_10HZ        (0x00)
#define BMM050_DATA_RATE_02HZ        (0x01)
#define BMM050_DATA_RATE_06HZ        (0x02)
#define BMM050_DATA_RATE_08HZ        (0x03)
#define BMM050_DATA_RATE_15HZ        (0x04)
#define BMM050_DATA_RATE_20HZ        (0x05)
#define BMM050_DATA_RATE_25HZ        (0x06)
#define BMM050_DATA_RATE_30HZ        (0x07)

/********************************************/
/**\name BIT SHIFTING DEFINITIONS  */
/********************************************/
/*Shifting Constants*/
#define BMM050_SHIFT_BIT_POSITION_BY_01_BIT     (1)
#define BMM050_SHIFT_BIT_POSITION_BY_02_BITS    (2)
#define BMM050_SHIFT_BIT_POSITION_BY_03_BITS    (3)
#define BMM050_SHIFT_BIT_POSITION_BY_05_BITS    (5)
#define BMM050_SHIFT_BIT_POSITION_BY_06_BITS    (6)
#define BMM050_SHIFT_BIT_POSITION_BY_07_BITS    (7)
#define BMM050_SHIFT_BIT_POSITION_BY_08_BITS    (8)
#define BMM050_SHIFT_BIT_POSITION_BY_09_BITS    (9)
#define BMM050_SHIFT_BIT_POSITION_BY_12_BITS    (12)
#define BMM050_SHIFT_BIT_POSITION_BY_13_BITS    (13)
#define BMM050_SHIFT_BIT_POSITION_BY_16_BITS    (16)
#define BMM050_SHIFT_BIT_POSITION_BY_14_BITS    (14)
#define BMM050_SHIFT_BIT_POSITION_BY_15_BITS    (15)
/****************************************************/
/**\name    ARRAY SIZE DEFINITIONS      */
/***************************************************/
#define BMM050_DATA_FRAME_SIZE      (8)
#define BMM050_INIT_DATA_SIZE       (2)
#define BMM050_CHIP_ID_DATA         (0)
#define BMM050_SELFTEST_DATA_SIZE   (5)
#define BMM050_TRIM_DATA_SIZE       (2)
#define BMM050_XLSB_DATA            (0)
#define BMM050_XMSB_DATA            (1)
#define BMM050_YLSB_DATA            (2)
#define BMM050_YMSB_DATA            (3)
#define BMM050_ZLSB_DATA            (4)
#define BMM050_ZMSB_DATA            (5)
#define BMM050_RLSB_DATA            (6)
#define BMM050_RMSB_DATA            (7)
#define BMM050_TRIM_DIG_Z1_LSB_DATA (0)
#define BMM050_TRIM_DIG_Z1_MSB_DATA (1)
#define BMM050_TRIM_DIG_Z2_LSB_DATA (0)
#define BMM050_TRIM_DIG_Z2_MSB_DATA (1)
#define BMM050_TRIM_DIG_Z3_LSB_DATA (0)
#define BMM050_TRIM_DIG_Z3_MSB_DATA (1)
#define BMM050_TRIM_DIG_Z4_LSB_DATA (0)
#define BMM050_TRIM_DIG_Z4_MSB_DATA (1)
#define BMM050_TRIM_DIG_XYZ1_LSB_DATA   (0)
#define BMM050_TRIM_DIG_XYZ1_MSB_DATA   (1)
#define BMM050_REMAPPED_YLSB_DATA           (0)
#define BMM050_REMAPPED_YMSB_DATA           (1)
#define BMM050_REMAPPED_XLSB_DATA           (2)
#define BMM050_REMAPPED_XMSB_DATA           (3)

/********************************************/
/**\name STRUCTURE DEFINITIONS  */
/********************************************/
/*!
 * @brief Structure containing mag xyz data
 * output of the data is s16
 */
struct bmm050_mag_data_s16_t
{
    s16 datax;/**<mag compensated X  data*/
    s16 datay;/**<mag compensated Y  data*/
    s16 dataz;/**<mag compensated Z  data*/
    u16 resistance;/**<mag R  data*/
    u8 data_ready;/**<mag data ready status*/
};
/*!
 * @brief Structure containing mag xyz data
 * output of the data is s32
 */
struct bmm050_mag_s32_data_t
{
    s32 datax;/**<mag compensated X  data*/
    s32 datay;/**<mag compensated Y  data*/
    s32 dataz;/**<mag compensated Z  data*/
    u16 resistance;/**<mag R  data*/
    u8 data_ready;/**<mag data ready status*/
};
/*!
 * @brief Structure containing mag xyz data
 * output of the data is float
 */
struct bmm050_mag_data_float_t
{
    float datax;/**<mag compensated X  data*/
    float datay;/**<mag compensated Y  data*/
    float  dataz;/**<mag compensated Z  data*/
    u16 resistance;/**<mag R  data*/
    u8 data_ready;/**<mag data ready status*/
};
/*!
 * @brief Structure containing mag remapped xyz data
 * output of the data is s16
 * this only applicable for BMX055 sensor
 */
struct bmm050_remapped_mag_s16_data_t
{
    s16 datax;/**<mag compensated remapped X  data*/
    s16 datay;/**<mag compensated remapped Y  data*/
    s16 dataz;/**<mag compensated Z  data*/
    u16 resistance;/**<mag R  data*/
    u8 data_ready;/**<mag data ready status*/
};
/*!
 * @brief Structure containing mag remapped xyz data
 * output of the data is s32
 * this only applicable for BMX055 sensor
 */
struct bmm050_remapped_mag_s32_data_t
{
    s32 datax;/**<mag compensated remapped X  data*/
    s32 datay;/**<mag compensated remapped Y  data*/
    s32 dataz;/**<mag compensated Z  data*/
    u16 resistance;/**<mag R  data*/
    u8 data_ready;/**<mag data ready status*/
};
/*!
 * @brief Structure containing mag remapped xyz data
 * output of the data is float
 * this only applicable for BMX055 sensor
 */
struct bmm050_remapped_mag_data_float_t
{
    float datax;/**<mag compensated remapped X  data*/
    float datay;/**<mag compensated remapped Y  data*/
    float  dataz;/**<mag compensated Z  data*/
    u16 resistance;/**<mag R  data*/
    u8 data_ready;/**<mag data ready status*/
};
/*!
 * @brief Structure containing mag initial parameters
 */
struct bmm050_t
{
    u8 company_id;/**<mag chip id*/
    u8 dev_addr;/**<mag device address*/

    BMM050_WR_FUNC_PTR;/**< bus write function pointer*/
    BMM050_RD_FUNC_PTR;/**< bus read function pointer*/
    void (*delay_msec)(BMM050_MDELAY_DATA_TYPE);/**< delay function pointer*/

    s8 dig_x1;/**< trim x1 data */
    s8 dig_y1;/**< trim y1 data */

    s8 dig_x2;/**< trim x2 data */
    s8 dig_y2;/**< trim y2 data */

    u16 dig_z1;/**< trim z1 data */
    s16 dig_z2;/**< trim z2 data */
    s16 dig_z3;/**< trim z3 data */
    s16 dig_z4;/**< trim z4 data */

    u8 dig_xy1;/**< trim xy1 data */
    s8 dig_xy2;/**< trim xy2 data */

    u16 dig_xyz1;/**< trim xyz1 data */
};
/********************************************/
/**\name FUNCTION DECLARATIONS  */
/********************************************/
/********************************************/
/**\name INITIALIZATION  */
/********************************************/
/*!
 *  @brief This function is used for initialize
 *  bus read and bus write functions
 *  assign the chip id and device address
 *  chip id is read in the register 0x40 bit from 0 to 7
 *
 *  @note While changing the parameter of the bmm050
 *  consider the following point:
 *  @note Changing the reference value of the parameter
 *  will changes the local copy or local reference
 *  make sure your changes will not
 *  affect the reference value of the parameter
 *  (Better case don't change the reference value of the parameter)
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_init(struct bmm050_t *bmm050);
/********************************************/
/**\name DATA READ FUNCTIONS  */
/********************************************/
/*!
 * @brief This API reads compensated Magnetometer
 * data of X,Y,Z values
 * from location 0x42 to 0x49
 *
 *
 *
 *
 *  @param  mag_data : The data of mag compensated XYZ data
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_read_mag_data_XYZ(
    struct bmm050_mag_data_s16_t *mag_data);
/*!
 *  @brief This API reads remapped compensated Magnetometer
 *  data of X,Y,Z values
 *  @note In this function X and Y axis is remapped
 *  @note X is read from the address 0x44 & 0x45
 *  @note Y is read from the address 0x42 & 0x43
 *  @note this API is only applicable for BMX055 sensor
 *
 *
 *
 *  @param  mag_data : The data of remapped compensated mag xyz data
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_read_bmx055_remapped_mag_data_XYZ(
    struct bmm050_remapped_mag_s16_data_t *mag_data);
/*!
 *  @brief This API reads compensated magnetometer
 *  data of X,Y,Z values
 *  @note The output value of compensated X, Y, Z  as s32
 *
 *
 *  @param mag_data : The data of compensated XYZ data
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_read_mag_data_XYZ_s32(
    struct bmm050_mag_s32_data_t *mag_data);
/*!
 *  @brief This API reads remapped compensated magnetometer
 *  data of X,Y,Z values
 *  @note The output value of compensated X, Y, Z  as s32
 *  @note In this function X and Y axis is remapped
 *  @note X is read from the address 0x44 & 0x45
 *  @note Y is read from the address 0x42 & 0x43
 *  @note this API is only applicable for BMX055 sensor
 *
 *
 *  @param mag_data : The data of remapped compensated XYZ data
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_read_bmx055_remapped_mag_data_XYZ_s32(
    struct bmm050_remapped_mag_s32_data_t *mag_data);
#ifdef ENABLE_FLOAT
/*!
 *  @brief This API reads compensated Magnetometer
 *  data of X,Y,Z values
 *  @note The output value of compensated X, Y, Z as float
 *
 *
 *
 *  @param mag_data : The value of compensated XYZ float data
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_read_mag_data_XYZ_float(
    struct bmm050_mag_data_float_t *mag_data);
#endif
#ifdef ENABLE_FLOAT
/*!
 *  @brief This API reads remapped compensated Magnetometer
 *  data of X,Y,Z values
 *  @note The output value of compensated X, Y, Z as float
 *
 *  @note In this function X and Y axis is remapped
 *  @note X is read from the address 0x44 & 0x45
 *  @note Y is read from the address 0x42 & 0x43
 *  @note this API is only applicable for BMX055 sensor
 *
 *  @param mag_data : The value of remapped compensated XYZ float data
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_read_bmx055_remapped_mag_data_XYZ_float(
    struct bmm050_remapped_mag_data_float_t *mag_data);
#endif
/********************************************/
/**\name COMMON READ AND WRITE FUNCTIONS  */
/********************************************/
/*!
 * @brief
 *  This API reads the data from
 *  the given register
 *
 *
 *  @param v_addr_u8 -> Address of the register
 *  @param v_data_u8 -> The data from the register
 *  @param v_len_u8 -> no of bytes to read
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMM050_RETURN_FUNCTION_TYPE bmm050_read_register(u8 v_addr_u8,
        u8 *v_data_u8, u8 v_len_u8);
/*!
 * @brief
 *  This API write the data to
 *  the given register
 *
 *
 *  @param v_addr_u8 -> Address of the register
 *  @param v_data_u8 -> The data from the register
 *  @param v_len_u8 -> no of bytes to read
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMM050_RETURN_FUNCTION_TYPE bmm050_write_register(u8 v_addr_u8,
        u8 *v_data_u8, u8 v_len_u8);
/********************************************/
/**\name SELF TEST FUNCTION  */
/********************************************/
/*!
 *  @brief This API used to set the self test of the sensor
 *  in the register 0x4C bit 0
 *
 *
 *
 *  @param  v_selftest_u8 : The value of selftest
 *  @note write 0x01 to start self test
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_set_selftest(u8 v_selftest_u8);
/*!
 *  @brief This API used to read the selftest of the sensor
 *
 *
 *
 *
 *  @param v_selftest_xyz: The self test value of XYZ
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_get_selftest_XYZ(
    u8 *v_selftest_xyz);
/********************************************/
/**\name SPI ENABLE FUNCTION  */
/********************************************/
/*!
 *  @brief This API used to set the spi3
 *  in the register 0x4B bit 2
 *
 *
 *
 *  @param  v_value_u8 : the value of spi3
 *  value  | Description
 * --------|------------
 *   0     | Disable
 *   1     | Enable
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_set_spi3(u8 v_value_u8);
/********************************************/
/**\name DATA RATE FUNCTIONS  */
/********************************************/
/*!
 *  @brief This API used to set the data rate of the sensor
 *  in the register 0x4C bit 3 to 5
 *
 *
 *
 *  @param  v_data_rate_u8 : The value of data rate
 *  value     |       Description
 * -----------|-----------------------
 *   0x00     |  BMM050_DATA_RATE_10HZ
 *   0x01     |  BMM050_DATA_RATE_02HZ
 *   0x02     |  BMM050_DATA_RATE_06HZ
 *   0x03     |  BMM050_DATA_RATE_08HZ
 *   0x04     |  BMM050_DATA_RATE_15HZ
 *   0x05     |  BMM050_DATA_RATE_20HZ
 *   0x06     |  BMM050_DATA_RATE_25HZ
 *   0x07     |  BMM050_DATA_RATE_30HZ
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_set_data_rate(u8 v_data_rate_u8);
/*!
 *  @brief This API used to get the data rate of the sensor
 *  in the register 0x4C bit 3 to 5
 *
 *
 *
 *  @param  v_data_rate_u8 : The value of data rate
 *  value     |       Description
 * -----------|-----------------------
 *   0x00     |  BMM050_DATA_RATE_10HZ
 *   0x01     |  BMM050_DATA_RATE_02HZ
 *   0x02     |  BMM050_DATA_RATE_06HZ
 *   0x03     |  BMM050_DATA_RATE_08HZ
 *   0x04     |  BMM050_DATA_RATE_15HZ
 *   0x05     |  BMM050_DATA_RATE_20HZ
 *   0x06     |  BMM050_DATA_RATE_25HZ
 *   0x07     |  BMM050_DATA_RATE_30HZ
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_get_data_rate(u8 *v_data_rate_u8);
/********************************************/
/**\name FUNCTIONAL STATE FUNCTION  */
/********************************************/
/*!
 *  @brief This API used to set the functional state
 *  in the register 0x4C and 0x4B
 *  @note 0x4C bit 1 and 2
 *  @note 0x4B bit 0
 *
 *
 *  @param  v_functional_state_u8: The value of functional mode
 *  value     |   functional state
 * -----------|-------------------
 *   0x00     | BMM050_NORMAL_MODE
 *   0x01     | BMM050_SUSPEND_MODE
 *   0x02     | BMM050_FORCED_MODE
 *   0x03     | BMM050_SLEEP_MODE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_set_functional_state(
    u8 v_functional_state_u8);
/*!
 *  @brief This API used to get the functional state
 *  in the register 0x4C bit 1 and 2
 *
 *
 *
 *
 *  @param v_functional_state_u8: The value of functional mode
 *  value     |  functional state
 * -----------|--------------------
 *    0x00    |  Normal
 *    0x03    |  Sleep
 *  @note If user set the functional state as Force mode(0x01) and read the
 *  register it returns the value as 0x03 that is sleep mode.
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_get_functional_state(
    u8 *v_functional_state_u8);
/********************************************/
/**\name ADVANCED SELFTEST  */
/********************************************/
/*!
 *  @brief This API used to perform the
 *  advanced self test
 *
 *
 *
 *  @param v_diff_z_s16 : The output of advance self test
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_perform_advanced_selftest(
    s16 *v_diff_z_s16);
/********************************************/
/**\name TRIM REGISTER  */
/********************************************/
/*!
 *  @brief This API used to get the trim values
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 */
BMM050_RETURN_FUNCTION_TYPE bmm050_init_trim_registers(void);
/********************************************/
/**\name SET ADVANCED SELFTEST  */
/********************************************/
/*!
 *  @brief This API used to set the advanced self test
 *  in the register 0x4C bit 6 and 7
 *
 *
 *
 *  @param  v_advanced_selftest_u8 : The output value of advanced self test
 *    value      |   Status
 *  -------------|-------------------
 *       0       |  BMM050_ADVANCED_SELFTEST_OFF
 *       2       |  BMM050_ADVANCED_SELFTEST_NEGATIVE
 *       3       |  BMM050_ADVANCED_SELFTEST_POSITIVE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_set_advanced_selftest(
    u8 v_advanced_selftest_u8);
/*!
 *  @brief This API used to get the advanced self test
 *  in the register 0x4C bit 6 and 7
 *
 *
 *
 *  @param  v_advanced_selftest_u8 : The output value of advanced self test
 *    value      |   Status
 *  -------------|-------------------
 *       0       |  BMM050_ADVANCED_SELFTEST_OFF
 *       2       |  BMM050_ADVANCED_SELFTEST_NEGATIVE
 *       3       |  BMM050_ADVANCED_SELFTEST_POSITIVE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_get_advanced_selftest(
    u8 *v_advanced_selftest_u8);
/********************************************/
/**\name POWER MODE   */
/********************************************/
/*!
 *  @brief This API used to get the power control bit
 *  in the register 0x4B bit 0
 *
 *
 *
 *  @param v_power_mode_u8 : The value of power control bit enable
 *   value     |  status
 *  -----------|------------
 *      0      | Disable the power control bit
 *      1      | Enable the power control bit
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_get_power_mode(u8 *v_power_mode_u8);
/*!
 *  @brief This API used to set the power control bit
 *  in the register 0x4B bit 0
 *
 *
 *
 *  @param v_power_mode_u8 : The value of power control bit enable
 *   value     |  status
 *  -----------|------------
 *      0      | Disable the power control bit
 *      1      | Enable the power control bit
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_set_power_mode(u8 v_power_mode_u8);
/********************************************/
/**\name XY AND Z REPETITIONS */
/********************************************/
/*!
 *  @brief This API used to get the x and y
 *  repetition in the register 0x51 bit 0 to 7
 *
 *
 *
 *  @param v_rep_xy_u8 : The value of x and y repetitions
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_get_rep_XY(
    u8 *v_rep_xy_u8);
/*!
 *  @brief This API used to set the x and y
 *  repetition in the register 0x51 bit 0 to 7
 *
 *
 *
 *  @param v_rep_xy_u8 : The value of x and y repetitions
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_set_rep_XY(
    u8 v_rep_xy_u8);
/*!
 *  @brief This API used to get the z repetition in the
 *  register 0x52 bit 0 to 7
 *
 *
 *
 *  @param v_rep_z_u8 : The value of z repetitions
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_get_rep_Z(
    u8 *v_rep_z_u8);
/*!
 *  @brief This API used to set the z repetition in the
 *  register 0x52 bit 0 to 7
 *
 *
 *
 *  @param v_rep_z_u8 : The value of z repetitions
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_set_rep_Z(
    u8 v_rep_z_u8);
/********************************************/
/**\name PRESET MODE  */
/********************************************/
/*!
 *  @brief This API used to get the preset modes
 *
 *  @note The preset mode setting is
 *  depend on Data Rate, XY and Z repetitions
 *
 *
 *
 *  @param v_presetmode_u8: The value of selected preset mode
 *  value    | preset_mode
 * ----------|-----------------
 *    1      | BMM050_PRESETMODE_LOWPOWER
 *    2      | BMM050_PRESETMODE_REGULAR
 *    3      | BMM050_PRESETMODE_HIGHACCURACY
 *    4      | BMM050_PRESETMODE_ENHANCED
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_get_presetmode(
    u8 *v_presetmode_u8);
/*!
 *  @brief This API used to set the preset modes
 *
 *  @note The preset mode setting is
 *  depend on Data Rate, XY and Z repetitions
 *
 *
 *
 *  @param v_presetmode_u8: The value of selected preset mode
 *  value    | preset_mode
 * ----------|-----------------
 *    1      | BMM050_PRESETMODE_LOWPOWER
 *    2      | BMM050_PRESETMODE_REGULAR
 *    3      | BMM050_PRESETMODE_HIGHACCURACY
 *    4      | BMM050_PRESETMODE_ENHANCED
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_set_presetmode(u8 v_presetmode_u8);
/********************************************/
/**\name COMPENSATE X DATA   */
/********************************************/
/*!
 *  @brief This API used to get the compensated X data
 *  the out put of X as s16
 *
 *
 *
 *  @param  mag_data_x : The value of raw X data
 *  @param  data_r : The value of R data
 *
 *  @return results of compensated X data value output as s16
 *
*/
s16 bmm050_compensate_X(s16 mag_data_x, u16 data_r);
/*!
 *  @brief This API used to get the compensated X data
 *  the out put of X as s32
 *
 *
 *
 *  @param  mag_data_x : The value of raw X data
 *  @param  data_r : The value of R data
 *
 *  @return results of compensated X data value output as s32
 *
*/
s32 bmm050_compensate_X_s32(s16 mag_data_x, u16 data_r);
#ifdef ENABLE_FLOAT
    /*!
    *  @brief This API used to get the compensated X data
    *  the out put of X as float
    *
    *
    *
    *  @param  mag_data_x : The value of raw X data
    *  @param  data_r : The value of R data
    *
    *  @return results of compensated X data value output as float
    *
    */
    float bmm050_compensate_X_float(s16 mag_data_x, u16 data_r);
#endif
/********************************************/
/**\name COMPENSATE Y DATA   */
/********************************************/
/*!
 *  @brief This API used to get the compensated Y data
 *  the out put of Y as s16
 *
 *
 *
 *  @param  mag_data_y : The value of raw Y data
 *  @param  data_r : The value of R data
 *
 *  @return results of compensated Y data value output as s16
 *
*/
s16 bmm050_compensate_Y(s16 mag_data_y, u16 data_r);
/*!
 *  @brief This API used to get the compensated Y data
 *  the out put of Y as s32
 *
 *
 *
 *  @param  mag_data_y : The value of raw Y data
 *  @param  data_r : The value of R data
 *
 *  @return results of compensated Y data value output as s32
 *
*/
s32 bmm050_compensate_Y_s32(s16 mag_data_y, u16 data_r);
#ifdef ENABLE_FLOAT
    /*!
    *  @brief This API used to get the compensated Y data
    *  the out put of Y as float
    *
    *
    *
    *  @param  mag_data_y : The value of raw Y data
    *  @param  data_r : The value of R data
    *
    *  @return results of compensated Y data value output as float
    *
    */
    float bmm050_compensate_Y_float(s16 mag_data_y, u16 data_r);
#endif
/********************************************/
/**\name COMPENSATE Z DATA   */
/********************************************/
/*!
 *  @brief This API used to get the compensated Z data
 *  the out put of Z as s16
 *
 *
 *
 *  @param  mag_data_z : The value of raw Z data
 *  @param  data_r : The value of R data
 *
 *  @return results of compensated Z data value output as s16
 *
*/
s16 bmm050_compensate_Z(s16 mag_data_z, u16 data_r);
/*!
 *  @brief This API used to get the compensated Z data
 *  the out put of Z as s32
 *
 *
 *
 *  @param  mag_data_z : The value of raw Z data
 *  @param  data_r : The value of R data
 *
 *  @return results of compensated Z data value output as s32
 *
*/
s32 bmm050_compensate_Z_s32(s16 mag_data_z, u16 data_r);
#ifdef ENABLE_FLOAT
    /*!
    *  @brief This API used to get the compensated Z data
    *  the out put of Z as float
    *
    *
    *
    *  @param  mag_data_z : The value of raw Z data
    *  @param  data_r : The value of R data
    *
    *  @return results of compensated Z data value output as float
    *
    */
    float bmm050_compensate_Z_float(s16 mag_data_z, u16 data_r);
#endif
/********************************************/
/**\name CONTROL MEASUREMENT OF X AND Y  */
/********************************************/
/*!
 *  @brief This API used to set the control measurement
 *  X data in the register 0x4E bit 3
 *
 *
 *  @param  v_enable_disable_u8: The value of control measurement-x
 *   value  |  Status
 *  --------|----------
 *     1    | ENABLE
 *     0    | DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_set_control_measurement_x(
    u8 v_enable_disable_u8);
/*!
 *  @brief This API used to set the control measurement
 *  Y data in the register 0x4E bit 4
 *
 *
 *  @param  v_enable_disable_u8: The value of control measurement-y
 *   value  |  Status
 *  --------|----------
 *     1    | ENABLE
 *     0    | DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_set_control_measurement_y(
    u8 v_enable_disable_u8);
/********************************************/
/**\name SOFT RESET   */
/********************************************/
/*!
 *  @brief This API used reset the register values to default
 *  in the register 0x4B
 *
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_soft_rst(void);
/********************************************/
/**\name RAW XYZ DATA  */
/********************************************/
/*!
 *  @brief This API reads Magnetometer
 *  raw data of X,Y,Z values and RHALL values
 *  from location 0x42 to 0x49
 *
 *
 *
 *
 *  @param  mag_data : The data of raw XYZ data
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_get_raw_xyz(
    struct bmm050_mag_data_s16_t *mag_data);
/********************************************/
/**\name REMAPPED RAW XYZ DATA  */
/********************************************/
/*!
 *  @brief This API reads remapped Magnetometer
 *  raw data of X,Y,Z values and RHALL values
 *  from location 0x42 to 0x49
 *
 *  @note In this function X and Y axis is remapped
 *  @note X is read from the address 0x44 & 0x45
 *  @note Y is read from the address 0x42 & 0x43
 *  @note this API is only applicable for BMX055 sensor
 *
 *
 *
 *  @param  mag_data : The data of remapped raw XYZ data
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_get_bmx055_remapped_raw_xyz(
    struct bmm050_remapped_mag_s16_data_t *mag_data);

#endif
