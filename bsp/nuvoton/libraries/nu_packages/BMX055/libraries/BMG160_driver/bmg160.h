/** \mainpage
*
****************************************************************************
* Copyright (C) 2010 - 2015 Bosch Sensortec GmbH
*
* File : bmg160.h
*
* Date : 2015/04/29
*
* Revision : 2.0.4 $
*
* Usage: Sensor Driver for BMG160 sensor
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
/*! \file BMG160.h
    \brief Header for BMG160 API */
/* user defined code to be added here ... */
#ifndef __BMG160_H__
#define __BMG160_H__

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
    @brief Define the calling convention of YOUR bus communication routine.
    @note This includes types of parameters. This example shows the
    configuration for an SPI bus link.

    If your communication function looks like this:

    write_my_bus_xy(u8 device_addr, u8 register_addr,
    u8 * data, u8 length);

    The BMG160_WR_FUNC_PTR would equal:

    BMG160_WR_FUNC_PTR s8 (* bus_write)(u8,
    u8, u8 *, u8)

    Parameters can be mixed as needed refer to the
    refer BMG160_BUS_WRITE_FUNC  macro.


*/
/* defines the calling parameter types of the BMG160_WR_FUNCTION */
#define BMG160_BUS_WR_RETURN_TYPE s8

/* links the order of parameters defined in
BMG160_BUS_WR_PARAM_TYPE to function calls used inside the API*/
#define BMG160_BUS_WR_PARAM_TYPES u8, u8,\
u8 *, u8

/* links the order of parameters defined in
BMG160_BUS_WR_PARAM_TYPE to function calls used inside the API*/
#define BMG160_BUS_WR_PARAM_ORDER(device_addr, register_addr,\
register_data, wr_len)

/* never change this line */
#define BMG160_BUS_WRITE_FUNC(device_addr, register_addr,\
register_data, wr_len) bus_write(device_addr, register_addr,\
register_data, wr_len)
/**< link macro between API function calls and bus read function
    @note The bus write function can change since this is a
    system dependant issue.

    If the bus_read parameter calling order is like: reg_addr,
    reg_data, wr_len it would be as it is here.

    If the parameters are differently ordered or your communication
    function like I2C need to know the device address,
    you can change this macro accordingly.


    BMG160_BUS_READ_FUNC(dev_addr, reg_addr, reg_data, wr_len)\
    bus_read(dev_addr, reg_addr, reg_data, wr_len)

    This macro lets all API functions call YOUR communication routine in a
    way that equals your definition in the
    refer BMG160_WR_FUNC_PTR definition.

    @note: this macro also includes the "MSB='1'
    for reading BMG160 addresses.

*/
/*defines the return parameter type of the BMG160_RD_FUNCTION
*/
#define BMG160_BUS_RD_RETURN_TYPE s8
/* defines the calling parameter types of the BMG160_RD_FUNCTION
*/
#define BMG160_BUS_RD_PARAM_TYPES u8, u8,\
u8 *, u8
/* links the order of parameters defined in \
BMG160_BUS_RD_PARAM_TYPE to function calls used inside the API
*/
#define BMG160_BUS_RD_PARAM_ORDER (device_addr, register_addr,\
register_data)
/* never change this line */
#define BMG160_BUS_READ_FUNC(device_addr, register_addr,\
register_data, rd_len)bus_read(device_addr, register_addr,\
register_data, rd_len)
/* defines the return parameter type of the BMG160_RD_FUNCTION
*/
#define BMG160_BURST_RD_RETURN_TYPE s8
/* defines the calling parameter types of the BMG160_RD_FUNCTION
*/
#define BMG160_BURST_RD_PARAM_TYPES u8,\
u8, u8 *, s32
/* links the order of parameters defined in \
BMG160_BURST_RD_PARAM_TYPE to function calls used inside the API
*/
#define BMG160_BURST_RD_PARAM_ORDER (device_addr, register_addr,\
register_data)
/* never change this line */
#define BMG160_BURST_READ_FUNC(device_addr, register_addr,\
register_data, rd_len)burst_read(device_addr, \
register_addr, register_data, rd_len)
/*!
 * @brief defines the return parameter type of the BMG160_DELAY_FUNCTION
*/
#define BMG160_DELAY_RETURN_TYPE void
/* never change this line */
#define BMG160_DELAY_FUNC(delay_in_msec)\
        delay_func(delay_in_msec)

#define BMG160_RETURN_FUNCTION_TYPE         s8
/*This refers BMG160 return type as signed */
/***************************************************************/
/**\name    DEVICE ADDRESS OF BMG160       */
/***************************************************************/
#define BMG160_I2C_ADDR1                (0x68)
#define BMG160_I2C_ADDR2                (0x69)

/***************************************************************/
/**\name    REGISTER ADDRESS DEFINITION        */
/***************************************************************/

/*******************************************/
/**\name    CHIP ID       */
/*******************************************/
#define BMG160_CHIP_ID_ADDR                      (0x00)
/**<Address of Chip ID Register*/
/*******************************************/
/**\name    DATA REGISTER       */
/*******************************************/
#define BMG160_RATE_X_LSB_ADDR                     (0x02)
/**<        Address of X axis Rate LSB Register       */
#define BMG160_RATE_X_MSB_ADDR                     (0x03)
/**<        Address of X axis Rate MSB Register       */
#define BMG160_RATE_Y_LSB_ADDR                     (0x04)
/**<        Address of Y axis Rate LSB Register       */
#define BMG160_RATE_Y_MSB_ADDR                     (0x05)
/**<        Address of Y axis Rate MSB Register       */
#define BMG160_RATE_Z_LSB_ADDR                     (0x06)
/**<        Address of Z axis Rate LSB Register       */
#define BMG160_RATE_Z_MSB_ADDR                     (0x07)
/**<        Address of Z axis Rate MSB Register       */
#define BMG160_TEMP_ADDR                           (0x08)
/**<        Address of Temperature Data LSB Register  */
/*******************************************/
/**\name    STATUS REGISTER     */
/*******************************************/
#define BMG160_INTR_STAT0_ADDR                     (0x09)
/**<        Address of Interrupt status Register    */
#define BMG160_INTR_STAT1_ADDR                     (0x0A)
/**<        Address of Interrupt status Register     */
#define BMG160_INTR_STAT2_ADDR                     (0x0B)
/**<        Address of Interrupt status Register     */
#define BMG160_INTR_STAT3_ADDR                     (0x0C)
/**<        Address of Interrupt status Register     */
#define BMG160_FIFO_STAT_ADDR                      (0x0E)
/**<        Address of FIFO status Register           */
/*******************************************/
/**\name    CONTROL REGISTER    */
/*******************************************/
#define BMG160_RANGE_ADDR                         (0x0F)
/**<        Address of Range address Register     */
#define BMG160_BW_ADDR                            (0x10)
/**<        Address of Bandwidth Register         */
#define BMG160_MODE_LPM1_ADDR                     (0x11)
/**<        Address of Mode LPM1 Register         */
#define BMG160_MODE_LPM2_ADDR                     (0x12)
/**<        Address of Mode LPM2 Register         */
#define BMG160_HIGH_BW_ADDR                       (0x13)
/**<        Address of Rate HIGH_BW Register       */
#define BMG160_BGW_SOFT_RST_ADDR                  (0x14)
/**<        Address of BGW Softreset Register      */
/*******************************************/
/**\name    INTERRUPT STATUS REGISTERS    */
/*******************************************/
#define BMG160_INTR_ENABLE0_ADDR                  (0x15)
/**<        Address of Interrupt Enable             */
#define BMG160_INTR_ENABLE1_ADDR                  (0x16)
/**<        Address of Interrupt Enable             */
#define BMG160_INTR_MAP_ZERO_ADDR                 (0x17)
/**<        Address of Interrupt MAP                */
#define BMG160_INTR_MAP_ONE_ADDR                  (0x18)
/**<        Address of Interrupt MAP                */
#define BMG160_INTR_MAP_TWO_ADDR                  (0x19)
/**<        Address of Interrupt MAP                */
#define BMG160_INTR_ZERO_ADDR                     (0x1A)
/**<        Address of Interrupt  register   */
#define BMG160_INTR_ONE_ADDR                      (0x1B)
/**<        Address of Interrupt  register   */
#define BMG160_INTR_TWO_ADDR                      (0x1C)
/**<        Address of Interrupt  register   */
#define BMG160_INTR_4_ADDR                        (0x1E)
/**<        Address of Interrupt register   */
#define BMG160_RST_LATCH_ADDR                     (0x21)
/**<        Address of Reset Latch Register           */
/***********************************************/
/**\name    INTERRUPT HIGH RATE CONFIGURATION REGISTER  */
/***********************************************/
#define BMG160_HIGHRATE_THRES_X_ADDR              (0x22)
/**<        Address of High Th x Address register     */
#define BMG160_HIGHRATE_DURN_X_ADDR               (0x23)
/**<        Address of High Dur x Address register    */
#define BMG160_HIGHRATE_THRES_Y_ADDR              (0x24)
/**<        Address of High Th y  Address register    */
#define BMG160_HIGHRATE_DURN_Y_ADDR               (0x25)
/**<        Address of High Dur y Address register    */
#define BMG160_HIGHRATE_THRES_Z_ADDR              (0x26)
/**<        Address of High Th z Address register  */
#define BMG160_HIGHRATE_DURN_Z_ADDR               (0x27)
/**<        Address of High Dur z Address register  */
#define BMG160_SOC_ADDR                           (0x31)
/**<        Address of SOC register        */
/***********************************************/
/**\name    OFFSET REGISTER  */
/***********************************************/
#define BMG160_A_FOC_ADDR                         (0x32)
/**<        Address of A_FOC Register        */
/***********************************************/
/**\name    NVM CONTROL REGISTER  */
/***********************************************/
#define BMG160_TRIM_NVM_CTRL_ADDR                 (0x33)
/**<        Address of Trim NVM control register    */
#define BMG160_BGW_SPI3_WDT_ADDR                  (0x34)
/**<        Address of BGW SPI3,WDT Register           */

/***********************************************/
/**\name    OFFSET OCNFIGURATION REGISTER  */
/***********************************************/
/* Trim Register */
#define BMG160_OFFSET_OFC1_ADDR            (0x36)
/**<        Address of OFC1 Register          */
#define BMG160_OFC2_ADDR                   (0x37)
/**<        Address of OFC2 Register          */
#define BMG160_OFC3_ADDR                   (0x38)
/**<        Address of OFC3 Register          */
#define BMG160_OFC4_ADDR                   (0x39)
/**<        Address of OFC4 Register          */
#define BMG160_TRIM_GP0_ADDR               (0x3A)
/**<        Address of Trim GP0 Register              */
#define BMG160_TRIM_GP1_ADDR               (0x3B)
/**<        Address of Trim GP1 Register              */
/***********************************************/
/**\name    SELFTEST REGISTER  */
/***********************************************/
#define BMG160_SELFTEST_ADDR            (0x3C)
/**<        Address of BGW Self test Register           */
/***********************************************/
/**\name    FIFO REGISTER  */
/***********************************************/
/* Control Register */
#define BMG160_FIFO_CGF1_ADDR              (0x3D)
/**<        Address of FIFO CGF0 Register             */
#define BMG160_FIFO_CGF0_ADDR              (0x3E)
/**<        Address of FIFO CGF1 Register             */

/* Data Register */
#define BMG160_FIFO_DATA_ADDR              (0x3F)
/**<        Address of FIFO Data Register             */



/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR THE DATA REGISTERS  */
/***********************************************/
/* Rate X LSB Register */
#define BMG160_RATE_X_LSB_BIT__POS        (0)
/**< Last (8) bits of RateX LSB Registers */
#define BMG160_RATE_X_LSB_BIT__LEN        (8)
#define BMG160_RATE_X_LSB_BIT__MSK        (0xFF)
#define BMG160_RATE_X_LSB_BIT__REG        (BMG160_RATE_X_LSB_ADDR)

/* Rate Y LSB Register */
/**<  Last (8) bits of RateY LSB Registers */
#define BMG160_RATE_Y_LSB_BIT__POS        (0)
#define BMG160_RATE_Y_LSB_BIT__LEN        (8)
#define BMG160_RATE_Y_LSB_BIT__MSK        (0xFF)
#define BMG160_RATE_Y_LSB_BIT__REG        (BMG160_RATE_Y_LSB_ADDR)

/* Rate Z LSB Register */
/**< Last (8) bits of RateZ LSB Registers */
#define BMG160_RATE_Z_LSB_BIT__POS        (0)
#define BMG160_RATE_Z_LSB_BIT__LEN        (8)
#define BMG160_RATE_Z_LSB_BIT__MSK        (0xFF)
#define BMG160_RATE_Z_LSB_BIT__REG        (BMG160_RATE_Z_LSB_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK,
POSITION FOR THE INTERRUPT STATUS REGISTERS  */
/***********************************************/
/* Interrupt status (0) Register */
/**< 2th bit of Interrupt status  register */
#define BMG160_INTR_STAT0_ANY_MOTION_INTR__POS     (2)
#define BMG160_INTR_STAT0_ANY_MOTION_INTR__LEN     (1)
#define BMG160_INTR_STAT0_ANY_MOTION_INTR__MSK     (0x04)
#define BMG160_INTR_STAT0_ANY_MOTION_INTR__REG     (BMG160_INTR_STAT0_ADDR)

/**< 1st bit of Interrupt status register */
#define BMG160_INTR_STAT0_HIGHRATE_INTR__POS    (1)
#define BMG160_INTR_STAT0_HIGHRATE_INTR__LEN    (1)
#define BMG160_INTR_STAT0_HIGHRATE_INTR__MSK    (0x02)
#define BMG160_INTR_STAT0_HIGHRATE_INTR__REG    (BMG160_INTR_STAT0_ADDR)

/**< 1st and 2nd bit of Interrupt status  register */
#define BMG160_INTR_STAT_ZERO__POS    (1)
#define BMG160_INTR_STAT_ZERO__LEN    (2)
#define BMG160_INTR_STAT_ZERO__MSK    (0x06)
#define BMG160_INTR_STAT_ZERO__REG    (BMG160_INTR_STAT0_ADDR)

/* Interrupt status (1) Register */
/**< 7th bit of Interrupt status  register */
#define BMG160_INTR_STAT1_DATA_INTR__POS           (7)
#define BMG160_INTR_STAT1_DATA_INTR__LEN           (1)
#define BMG160_INTR_STAT1_DATA_INTR__MSK           (0x80)
#define BMG160_INTR_STAT1_DATA_INTR__REG           (BMG160_INTR_STAT1_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR THE OFFSET STATUS REGISTERS  */
/***********************************************/
/**< 6th bit of Interrupt status  register */
#define BMG160_INTR_STAT1_AUTO_OFFSET_INTR__POS    (6)
#define BMG160_INTR_STAT1_AUTO_OFFSET_INTR__LEN    (1)
#define BMG160_INTR_STAT1_AUTO_OFFSET_INTR__MSK    (0x40)
#define BMG160_INTR_STAT1_AUTO_OFFSET_INTR__REG    (BMG160_INTR_STAT1_ADDR)

/**< 5th bit of Interrupt status  register */
#define BMG160_INTR_STAT1_FAST_OFFSET_INTR__POS    (5)
#define BMG160_INTR_STAT1_FAST_OFFSET_INTR__LEN    (1)
#define BMG160_INTR_STAT1_FAST_OFFSET_INTR__MSK    (0x20)
#define BMG160_INTR_STAT1_FAST_OFFSET_INTR__REG    (BMG160_INTR_STAT1_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR THE FIFO STATUS REGISTERS  */
/***********************************************/
/**< 4th bit of Interrupt status  register */
#define BMG160_INTR_STAT1_FIFO_INTR__POS           (4)
#define BMG160_INTR_STAT1_FIFO_INTR__LEN           (1)
#define BMG160_INTR_STAT1_FIFO_INTR__MSK           (0x10)
#define BMG160_INTR_STAT1_FIFO_INTR__REG           (BMG160_INTR_STAT1_ADDR)

/**< MSB (4) bits of Interrupt status1 register */
#define BMG160_INTR_STAT_ONE__POS           (4)
#define BMG160_INTR_STAT_ONE__LEN           (4)
#define BMG160_INTR_STAT_ONE__MSK           (0xF0)
#define BMG160_INTR_STAT_ONE__REG           (BMG160_INTR_STAT1_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR
THE ANY MOTION CONFIGURATION REGISTERS  */
/***********************************************/
/* Interrupt status (2) Register */
/**< 3th bit of Interrupt status  register */
#define BMG160_INTR_STAT2_ANY_MOTION_SIGN_INTR__POS     (3)
#define BMG160_INTR_STAT2_ANY_MOTION_SIGN_INTR__LEN     (1)
#define BMG160_INTR_STAT2_ANY_MOTION_SIGN_INTR__MSK     (0x08)
#define BMG160_INTR_STAT2_ANY_MOTION_SIGN_INTR__REG     (BMG160_INTR_STAT2_ADDR)

/**< 2th bit of Interrupt status register */
#define BMG160_INTR_STAT2_ANY_MOTION_FIRSTZ_INTR__POS   (2)
#define BMG160_INTR_STAT2_ANY_MOTION_FIRSTZ_INTR__LEN   (1)
#define BMG160_INTR_STAT2_ANY_MOTION_FIRSTZ_INTR__MSK   (0x04)
#define BMG160_INTR_STAT2_ANY_MOTION_FIRSTZ_INTR__REG   (BMG160_INTR_STAT2_ADDR)

/**< 1st bit of Interrupt status  register */
#define BMG160_INTR_STAT2_ANY_MOTION_FIRSTY_INTR__POS   (1)
#define BMG160_INTR_STAT2_ANY_MOTION_FIRSTY_INTR__LEN   (1)
#define BMG160_INTR_STAT2_ANY_MOTION_FIRSTY_INTR__MSK   (0x02)
#define BMG160_INTR_STAT2_ANY_MOTION_FIRSTY_INTR__REG   (BMG160_INTR_STAT2_ADDR)

/**< 0th bit of Interrupt status register */
#define BMG160_INTR_STAT2_ANY_MOTION_FIRSTX_INTR__POS   (0)
#define BMG160_INTR_STAT2_ANY_MOTION_FIRSTX_INTR__LEN   (1)
#define BMG160_INTR_STAT2_ANY_MOTION_FIRSTX_INTR__MSK   (0x01)
#define BMG160_INTR_STAT2_ANY_MOTION_FIRSTX_INTR__REG   (BMG160_INTR_STAT2_ADDR)

/**< (4) bits of Interrupt status  register */
#define BMG160_INTR_STAT_TWO__POS   (0)
#define BMG160_INTR_STAT_TWO__LEN   (4)
#define BMG160_INTR_STAT_TWO__MSK   (0x0F)
#define BMG160_INTR_STAT_TWO__REG   (BMG160_INTR_STAT2_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR
THE HIGH RATE XYZ SIGN REGISTERS  */
/***********************************************/
/* Interrupt status (3) Register */
/**< 3th bit of Interrupt status  register */
#define BMG160_INTR_STAT3_HIGHRATE_SIGN_INTR__POS     (3)
#define BMG160_INTR_STAT3_HIGHRATE_SIGN_INTR__LEN     (1)
#define BMG160_INTR_STAT3_HIGHRATE_SIGN_INTR__MSK     (0x08)
#define BMG160_INTR_STAT3_HIGHRATE_SIGN_INTR__REG     (BMG160_INTR_STAT3_ADDR)

/**< 2th bit of Interrupt status  register */
#define BMG160_INTR_STAT3_HIGHRATE_FIRSTZ_INTR__POS   (2)
#define BMG160_INTR_STAT3_HIGHRATE_FIRSTZ_INTR__LEN   (1)
#define BMG160_INTR_STAT3_HIGHRATE_FIRSTZ_INTR__MSK   (0x04)
#define BMG160_INTR_STAT3_HIGHRATE_FIRSTZ_INTR__REG  (BMG160_INTR_STAT3_ADDR)

/**< 1st bit of Interrupt status  register */
#define BMG160_INTR_STAT3_HIGHRATE_FIRSTY_INTR__POS   (1)
#define BMG160_INTR_STAT3_HIGHRATE_FIRSTY_INTR__LEN   (1)
#define BMG160_INTR_STAT3_HIGHRATE_FIRSTY_INTR__MSK   (0x02)
#define BMG160_INTR_STAT3_HIGHRATE_FIRSTY_INTR__REG   (BMG160_INTR_STAT3_ADDR)

/**< 0th bit of Interrupt status  register */
#define BMG160_INTR_STAT3_HIGHRATE_FIRSTX_INTR__POS   (0)
#define BMG160_INTR_STAT3_HIGHRATE_FIRSTX_INTR__LEN   (1)
#define BMG160_INTR_STAT3_HIGHRATE_FIRSTX_INTR__MSK   (0x01)
#define BMG160_INTR_STAT3_HIGHRATE_FIRSTX_INTR__REG   (BMG160_INTR_STAT3_ADDR)

/**< LSB (4) bits of Interrupt status  register */
#define BMG160_INTR_STAT_THREE__POS   (0)
#define BMG160_INTR_STAT_THREE__LEN   (4)
#define BMG160_INTR_STAT_THREE__MSK   (0x0F)
#define BMG160_INTR_STAT_THREE__REG   (BMG160_INTR_STAT3_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR THE FIFO OVERRUN  */
/***********************************************/
/* BMG160 FIFO Status Register */
/**< 7th bit of FIFO status Register */
#define BMG160_FIFO_STAT_OVERRUN__POS         (7)
#define BMG160_FIFO_STAT_OVERRUN__LEN         (1)
#define BMG160_FIFO_STAT_OVERRUN__MSK         (0x80)
#define BMG160_FIFO_STAT_OVERRUN__REG         (BMG160_FIFO_STAT_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR THE FIFO FRAME COUNT  */
/***********************************************/
/**< First (7) bits of FIFO status Register */
#define BMG160_FIFO_STAT_FRAME_COUNTER__POS   (0)
#define BMG160_FIFO_STAT_FRAME_COUNTER__LEN   (7)
#define BMG160_FIFO_STAT_FRAME_COUNTER__MSK   (0x7F)
#define BMG160_FIFO_STAT_FRAME_COUNTER__REG   (BMG160_FIFO_STAT_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR THE RANGE  */
/***********************************************/
/**< First (3) bits of range Registers */
#define BMG160_RANGE_ADDR_RANGE__POS           (0)
#define BMG160_RANGE_ADDR_RANGE__LEN           (3)
#define BMG160_RANGE_ADDR_RANGE__MSK           (0x07)
#define BMG160_RANGE_ADDR_RANGE__REG           (BMG160_RANGE_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR THE BANDWIDTH  */
/***********************************************/
/**< First (3) bits of Bandwidth Registers */
#define BMG160_BW_ADDR__POS             (0)
#define BMG160_BW_ADDR__LEN             (3)
#define BMG160_BW_ADDR__MSK             (0x07)
#define BMG160_BW_ADDR__REG             (BMG160_BW_ADDR)

/**< 5th and 7th bit of LPM1 Register */
#define BMG160_MODE_LPM1__POS             (5)
#define BMG160_MODE_LPM1__LEN             (3)
#define BMG160_MODE_LPM1__MSK             (0xA0)
#define BMG160_MODE_LPM1__REG             (BMG160_MODE_LPM1_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR THE POWER MODE  */
/***********************************************/
/**< 1st to 3rd bit of LPM1 Register */
#define BMG160_MODELPM1_ADDR_SLEEP_DURN__POS              (1)
#define BMG160_MODELPM1_ADDR_SLEEP_DURN__LEN              (3)
#define BMG160_MODELPM1_ADDR_SLEEP_DURN__MSK              (0x0E)
#define BMG160_MODELPM1_ADDR_SLEEP_DURN__REG              \
(BMG160_MODE_LPM1_ADDR)

/**< 7th bit of Mode LPM2 Register */
#define BMG160_MODE_LPM2_ADDR_FAST_POWERUP__POS         (7)
#define BMG160_MODE_LPM2_ADDR_FAST_POWERUP__LEN         (1)
#define BMG160_MODE_LPM2_ADDR_FAST_POWERUP__MSK         (0x80)
#define BMG160_MODE_LPM2_ADDR_FAST_POWERUP__REG         \
(BMG160_MODE_LPM2_ADDR)

/**< 6th bit of Mode LPM2 Register */
#define BMG160_MODE_LPM2_ADDR_ADV_POWERSAVING__POS      (6)
#define BMG160_MODE_LPM2_ADDR_ADV_POWERSAVING__LEN      (1)
#define BMG160_MODE_LPM2_ADDR_ADV_POWERSAVING__MSK      (0x40)
#define BMG160_MODE_LPM2_ADDR_ADV_POWERSAVING__REG      \
(BMG160_MODE_LPM2_ADDR)

/**< 4th & 5th bit of Mode LPM2 Register */
#define BMG160_MODE_LPM2_ADDR_EXT_TRI_SELECT__POS          (4)
#define BMG160_MODE_LPM2_ADDR_EXT_TRI_SELECT__LEN          (2)
#define BMG160_MODE_LPM2_ADDR_EXT_TRI_SELECT__MSK          (0x30)
#define BMG160_MODE_LPM2_ADDR_EXT_TRI_SELECT__REG          \
(BMG160_MODE_LPM2_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR THE AUTO SLEEP DURATION  */
/***********************************************/
/**< 0th to 2nd bit of LPM2 Register */
#define BMG160_MODE_LPM2_ADDR_AUTO_SLEEP_DURN__POS  (0)
#define BMG160_MODE_LPM2_ADDR_AUTO_SLEEP_DURN__LEN  (3)
#define BMG160_MODE_LPM2_ADDR_AUTO_SLEEP_DURN__MSK  (0x07)
#define BMG160_MODE_LPM2_ADDR_AUTO_SLEEP_DURN__REG  (BMG160_MODE_LPM2_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR THE HIGH BANDWIDTH  */
/***********************************************/
/**< 7th bit of HIGH_BW Register */
#define BMG160_HIGH_BW__POS         (7)
#define BMG160_HIGH_BW__LEN         (1)
#define BMG160_HIGH_BW__MSK         (0x80)
#define BMG160_HIGH_BW__REG         (BMG160_HIGH_BW_ADDR)

/**< 6th bit of HIGH_BW Register */
#define BMG160_SHADOW_DIS__POS          (6)
#define BMG160_SHADOW_DIS__LEN          (1)
#define BMG160_SHADOW_DIS__MSK          (0x40)
#define BMG160_SHADOW_DIS__REG          (BMG160_HIGH_BW_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR THE DATA INTERRUPT  */
/***********************************************/
/**< 7th bit of Interrupt Enable Registers */
#define BMG160_INTR_ENABLE0_DATA__POS               (7)
#define BMG160_INTR_ENABLE0_DATA__LEN               (1)
#define BMG160_INTR_ENABLE0_DATA__MSK               (0x80)
#define BMG160_INTR_ENABLE0_DATA__REG               (BMG160_INTR_ENABLE0_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR THE FIFO INTERRUPT  */
/***********************************************/
/**< 6th bit of Interrupt Enable Registers */
#define BMG160_INTR_ENABLE0_FIFO__POS               (6)
#define BMG160_INTR_ENABLE0_FIFO__LEN               (1)
#define BMG160_INTR_ENABLE0_FIFO__MSK               (0x40)
#define BMG160_INTR_ENABLE0_FIFO__REG               (BMG160_INTR_ENABLE0_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION
FOR THE AUTO OFFSET INTERRUPT  */
/***********************************************/
/**< 2nd bit of Interrupt Enable Registers */
#define BMG160_INTR_ENABLE0_AUTO_OFFSET__POS        (2)
#define BMG160_INTR_ENABLE0_AUTO_OFFSET__LEN        (1)
#define BMG160_INTR_ENABLE0_AUTO_OFFSET__MSK        (0x04)
#define BMG160_INTR_ENABLE0_AUTO_OFFSET__REG        (BMG160_INTR_ENABLE0_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR THE OUTPUT TYPE  */
/***********************************************/
/**< 3rd bit of Interrupt Enable Registers */
#define BMG160_INTR_ENABLE1_IT2_OUTPUT_TYPE__POS               (3)
#define BMG160_INTR_ENABLE1_IT2_OUTPUT_TYPE__LEN               (1)
#define BMG160_INTR_ENABLE1_IT2_OUTPUT_TYPE__MSK               (0x08)
#define BMG160_INTR_ENABLE1_IT2_OUTPUT_TYPE__REG               \
(BMG160_INTR_ENABLE1_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR THE LEVEL  */
/***********************************************/
/**< 2nd bit of Interrupt Enable Registers */
#define BMG160_INTR_ENABLE1_IT2_LEVEL__POS              (2)
#define BMG160_INTR_ENABLE1_IT2_LEVEL__LEN              (1)
#define BMG160_INTR_ENABLE1_IT2_LEVEL__MSK              (0x04)
#define BMG160_INTR_ENABLE1_IT2_LEVEL__REG              \
(BMG160_INTR_ENABLE1_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR THE OUTPUT TYPE  */
/***********************************************/
/**< 1st bit of Interrupt Enable Registers */
#define BMG160_INTR_ENABLE1_IT1_OUTPUT_TYPE__POS               (1)
#define BMG160_INTR_ENABLE1_IT1_OUTPUT_TYPE__LEN               (1)
#define BMG160_INTR_ENABLE1_IT1_OUTPUT_TYPE__MSK               (0x02)
#define BMG160_INTR_ENABLE1_IT1_OUTPUT_TYPE__REG               \
(BMG160_INTR_ENABLE1_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR THE LEVEL  */
/***********************************************/
/**< 0th bit of Interrupt Enable Registers */
#define BMG160_INTR_ENABLE1_IT1_LEVEL__POS              (0)
#define BMG160_INTR_ENABLE1_IT1_LEVEL__LEN              (1)
#define BMG160_INTR_ENABLE1_IT1_LEVEL__MSK              (0x01)
#define BMG160_INTR_ENABLE1_IT1_LEVEL__REG              \
(BMG160_INTR_ENABLE1_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR HIGH RATE INTERRUPT  */
/***********************************************/
/**< 3rd bit of Interrupt MAP (0) Registers */
#define BMG160_INTR_MAP_ZERO_INTR1_HIGHRATE__POS            (3)
#define BMG160_INTR_MAP_ZERO_INTR1_HIGHRATE__LEN            (1)
#define BMG160_INTR_MAP_ZERO_INTR1_HIGHRATE__MSK            (0x08)
#define BMG160_INTR_MAP_ZERO_INTR1_HIGHRATE__REG            \
(BMG160_INTR_MAP_ZERO_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR ANY_MOTION INTERRUPT  */
/***********************************************/
/**< 1st bit of Interrupt MAP  Registers */
#define BMG160_INTR_MAP_ZERO_INTR1_ANY_MOTION__POS             (1)
#define BMG160_INTR_MAP_ZERO_INTR1_ANY_MOTION__LEN             (1)
#define BMG160_INTR_MAP_ZERO_INTR1_ANY_MOTION__MSK             (0x02)
#define BMG160_INTR_MAP_ZERO_INTR1_ANY_MOTION__REG             \
(BMG160_INTR_MAP_ZERO_ADDR)

/**< 7th bit of MAP_1Registers */
#define BMG160_MAP_ONE_INTR2_DATA__POS                  (7)
#define BMG160_MAP_ONE_INTR2_DATA__LEN                  (1)
#define BMG160_MAP_ONE_INTR2_DATA__MSK                  (0x80)
#define BMG160_MAP_ONE_INTR2_DATA__REG                  \
(BMG160_INTR_MAP_ONE_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR FAST OFFSET INTERRUPT  */
/***********************************************/
/**< 6th bit of MAP_1Registers */
#define BMG160_MAP_ONE_INTR2_FAST_OFFSET__POS           (6)
#define BMG160_MAP_ONE_INTR2_FAST_OFFSET__LEN           (1)
#define BMG160_MAP_ONE_INTR2_FAST_OFFSET__MSK           (0x40)
#define BMG160_MAP_ONE_INTR2_FAST_OFFSET__REG           \
(BMG160_INTR_MAP_ONE_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR FIFO INTERRUPT  */
/***********************************************/
/**< 5th bit of MAP_1Registers */
#define BMG160_MAP_ONE_INTR2_FIFO__POS                  (5)
#define BMG160_MAP_ONE_INTR2_FIFO__LEN                  (1)
#define BMG160_MAP_ONE_INTR2_FIFO__MSK                  (0x20)
#define BMG160_MAP_ONE_INTR2_FIFO__REG                  \
(BMG160_INTR_MAP_ONE_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR AUTO OFFSET INTERRUPT  */
/***********************************************/
/**< 4th bit of MAP_1Registers */
#define BMG160_MAP_ONE_INTR2_AUTO_OFFSET__POS           (4)
#define BMG160_MAP_ONE_INTR2_AUTO_OFFSET__LEN           (1)
#define BMG160_MAP_ONE_INTR2_AUTO_OFFSET__MSK           (0x10)
#define BMG160_MAP_ONE_INTR2_AUTO_OFFSET__REG           \
(BMG160_INTR_MAP_ONE_ADDR)

/**< 3rd bit of MAP_1Registers */
#define BMG160_MAP_ONE_INTR1_AUTO_OFFSET__POS           (3)
#define BMG160_MAP_ONE_INTR1_AUTO_OFFSET__LEN           (1)
#define BMG160_MAP_ONE_INTR1_AUTO_OFFSET__MSK           (0x08)
#define BMG160_MAP_ONE_INTR1_AUTO_OFFSET__REG           \
(BMG160_INTR_MAP_ONE_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR FIFO INTERRUPT  */
/**********************************************/
/**< 2nd bit of MAP_1Registers */
#define BMG160_MAP_ONE_INTR1_FIFO__POS                  (2)
#define BMG160_MAP_ONE_INTR1_FIFO__LEN                  (1)
#define BMG160_MAP_ONE_INTR1_FIFO__MSK                  (0x04)
#define BMG160_MAP_ONE_INTR1_FIFO__REG                  \
(BMG160_INTR_MAP_ONE_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR FAST OFFSET INTERRUPT  */
/**********************************************/
/**< 1st bit of MAP_1Registers */
#define BMG160_MAP_ONE_INTR1_FAST_OFFSET__POS           (1)
#define BMG160_MAP_ONE_INTR1_FAST_OFFSET__LEN           (1)
#define BMG160_MAP_ONE_INTR1_FAST_OFFSET__MSK           (0x02)
#define BMG160_MAP_ONE_INTR1_FAST_OFFSET__REG           \
(BMG160_INTR_MAP_ONE_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR DATA INTERRUPT  */
/**********************************************/
/**< 0th bit of MAP_1Registers */
#define BMG160_MAP_ONE_INTR1_DATA__POS                  (0)
#define BMG160_MAP_ONE_INTR1_DATA__LEN                  (1)
#define BMG160_MAP_ONE_INTR1_DATA__MSK                  (0x01)
#define BMG160_MAP_ONE_INTR1_DATA__REG                  \
(BMG160_INTR_MAP_ONE_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR HIGH RATE INTERRUPT  */
/**********************************************/
/**< 3rd bit of Interrupt Map  Registers */
#define BMG160_INTR_MAP_TWO_INTR2_HIGHRATE__POS            (3)
#define BMG160_INTR_MAP_TWO_INTR2_HIGHRATE__LEN            (1)
#define BMG160_INTR_MAP_TWO_INTR2_HIGHRATE__MSK            (0x08)
#define BMG160_INTR_MAP_TWO_INTR2_HIGHRATE__REG            \
(BMG160_INTR_MAP_TWO_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR ANY MOTION INTERRUPT  */
/**********************************************/
/**< 1st bit of Interrupt Map  Registers */
#define BMG160_INTR_MAP_TWO_INTR2_ANY_MOTION__POS             (1)
#define BMG160_INTR_MAP_TWO_INTR2_ANY_MOTION__LEN             (1)
#define BMG160_INTR_MAP_TWO_INTR2_ANY_MOTION__MSK             (0x02)
#define BMG160_INTR_MAP_TWO_INTR2_ANY_MOTION__REG             \
(BMG160_INTR_MAP_TWO_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR SLOW OFFSET UNFILT  */
/**********************************************/
/**< 5th bit of Interrupt  Registers */
#define BMG160_INTR_ZERO_ADDR_SLOW_OFFSET_UNFILT__POS          (5)
#define BMG160_INTR_ZERO_ADDR_SLOW_OFFSET_UNFILT__LEN          (1)
#define BMG160_INTR_ZERO_ADDR_SLOW_OFFSET_UNFILT__MSK          (0x20)
#define BMG160_INTR_ZERO_ADDR_SLOW_OFFSET_UNFILT__REG          \
(BMG160_INTR_ZERO_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR HIGH RATE UNFILT  */
/**********************************************/
/**< 3rd bit of Interrupt  Registers */
#define BMG160_INTR_ZERO_ADDR_HIGHRATE_UNFILT_DATA__POS            (3)
#define BMG160_INTR_ZERO_ADDR_HIGHRATE_UNFILT_DATA__LEN            (1)
#define BMG160_INTR_ZERO_ADDR_HIGHRATE_UNFILT_DATA__MSK            (0x08)
#define BMG160_INTR_ZERO_ADDR_HIGHRATE_UNFILT_DATA__REG            \
(BMG160_INTR_ZERO_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR ANY MOTION UNFILT  */
/**********************************************/
/**< 1st bit of Interrupt (0) Registers */
#define BMG160_INTR_ZERO_ADDR_ANY_MOTION_UNFILT_DATA__POS             (1)
#define BMG160_INTR_ZERO_ADDR_ANY_MOTION_UNFILT_DATA__LEN             (1)
#define BMG160_INTR_ZERO_ADDR_ANY_MOTION_UNFILT_DATA__MSK             (0x02)
#define BMG160_INTR_ZERO_ADDR_ANY_MOTION_UNFILT_DATA__REG             \
(BMG160_INTR_ZERO_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR FAST OFFSET UNFILT  */
/**********************************************/
/**< 7th bit of INT_1  Registers */
#define BMG160_INTR_ONE_ADDR_FAST_OFFSET_UNFILT__POS            (7)
#define BMG160_INTR_ONE_ADDR_FAST_OFFSET_UNFILT__LEN            (1)
#define BMG160_INTR_ONE_ADDR_FAST_OFFSET_UNFILT__MSK            (0x80)
#define BMG160_INTR_ONE_ADDR_FAST_OFFSET_UNFILT__REG            \
(BMG160_INTR_ONE_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR ANY MOTION THRESHOLD */
/**********************************************/
/**< First (7) bits of INT_1  Registers */
#define BMG160_INTR_ONE_ADDR_ANY_MOTION_THRES__POS                       (0)
#define BMG160_INTR_ONE_ADDR_ANY_MOTION_THRES__LEN                       (7)
#define BMG160_INTR_ONE_ADDR_ANY_MOTION_THRES__MSK                       (0x7F)
#define BMG160_INTR_ONE_ADDR_ANY_MOTION_THRES__REG                       \
(BMG160_INTR_ONE_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR AWAKE DURATION */
/**********************************************/
/**< Last (2) bits of INT 2Registers */
#define BMG160_INTR_TWO_ADDR_AWAKE_DURN__POS          (6)
#define BMG160_INTR_TWO_ADDR_AWAKE_DURN__LEN          (2)
#define BMG160_INTR_TWO_ADDR_AWAKE_DURN__MSK          (0xC0)
#define BMG160_INTR_TWO_ADDR_AWAKE_DURN__REG          (BMG160_INTR_TWO_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR ANY MOTION SAMPLE */
/**********************************************/
/**< 4th & 5th bit of INT 2Registers */
#define BMG160_INTR_TWO_ADDR_ANY_MOTION_DURN_SAMPLE__POS      (4)
#define BMG160_INTR_TWO_ADDR_ANY_MOTION_DURN_SAMPLE__LEN      (2)
#define BMG160_INTR_TWO_ADDR_ANY_MOTION_DURN_SAMPLE__MSK      (0x30)
#define BMG160_INTR_TWO_ADDR_ANY_MOTION_DURN_SAMPLE__REG      \
(BMG160_INTR_TWO_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR ANY MOTION XYZ AXIS */
/**********************************************/
/**< 2nd bit of INT 2Registers */
#define BMG160_INTR_TWO_ADDR_ANY_MOTION_ENABLE_Z__POS           (2)
#define BMG160_INTR_TWO_ADDR_ANY_MOTION_ENABLE_Z__LEN           (1)
#define BMG160_INTR_TWO_ADDR_ANY_MOTION_ENABLE_Z__MSK           (0x04)
#define BMG160_INTR_TWO_ADDR_ANY_MOTION_ENABLE_Z__REG           \
(BMG160_INTR_TWO_ADDR)

/**< 1st bit of INT 2Registers */
#define BMG160_INTR_TWO_ADDR_ANY_MOTION_ENABLE_Y__POS           (1)
#define BMG160_INTR_TWO_ADDR_ANY_MOTION_ENABLE_Y__LEN           (1)
#define BMG160_INTR_TWO_ADDR_ANY_MOTION_ENABLE_Y__MSK           (0x02)
#define BMG160_INTR_TWO_ADDR_ANY_MOTION_ENABLE_Y__REG           \
(BMG160_INTR_TWO_ADDR)

/**< 0th bit of INT 2Registers */
#define BMG160_INTR_TWO_ADDR_ANY_MOTION_ENABLE_X__POS           (0)
#define BMG160_INTR_TWO_ADDR_ANY_MOTION_ENABLE_X__LEN           (1)
#define BMG160_INTR_TWO_ADDR_ANY_MOTION_ENABLE_X__MSK           (0x01)
#define BMG160_INTR_TWO_ADDR_ANY_MOTION_ENABLE_X__REG           \
(BMG160_INTR_TWO_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR FIFO WATER MARK*/
/**********************************************/
/**< Last bit of INT  Registers */
#define BMG160_INTR_4_FIFO_WM_ENABLE__POS           (7)
#define BMG160_INTR_4_FIFO_WM_ENABLE__LEN           (1)
#define BMG160_INTR_4_FIFO_WM_ENABLE__MSK           (0x80)
#define BMG160_INTR_4_FIFO_WM_ENABLE__REG           (BMG160_INTR_4_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR LATCH*/
/**********************************************/
/**< Last bit of Reset Latch Registers */
#define BMG160_RST_LATCH_ADDR_RST_INTR__POS           (7)
#define BMG160_RST_LATCH_ADDR_RST_INTR__LEN           (1)
#define BMG160_RST_LATCH_ADDR_RST_INTR__MSK           (0x80)
#define BMG160_RST_LATCH_ADDR_RST_INTR__REG           (BMG160_RST_LATCH_ADDR)

/**< 6th bit of Reset Latch Registers */
#define BMG160_RST_LATCH_ADDR_OFFSET_RST__POS        (6)
#define BMG160_RST_LATCH_ADDR_OFFSET_RST__LEN        (1)
#define BMG160_RST_LATCH_ADDR_OFFSET_RST__MSK        (0x40)
#define BMG160_RST_LATCH_ADDR_OFFSET_RST__REG        (BMG160_RST_LATCH_ADDR)

/**< 4th bit of Reset Latch Registers */
#define BMG160_RST_LATCH_ADDR_LATCH_STAT__POS        (4)
#define BMG160_RST_LATCH_ADDR_LATCH_STAT__LEN        (1)
#define BMG160_RST_LATCH_ADDR_LATCH_STAT__MSK        (0x10)
#define BMG160_RST_LATCH_ADDR_LATCH_STAT__REG        (BMG160_RST_LATCH_ADDR)

/**< First (4) bits of Reset Latch Registers */
#define BMG160_RST_LATCH_ADDR_LATCH_INTR__POS           (0)
#define BMG160_RST_LATCH_ADDR_LATCH_INTR__LEN           (4)
#define BMG160_RST_LATCH_ADDR_LATCH_INTR__MSK           (0x0F)
#define BMG160_RST_LATCH_ADDR_LATCH_INTR__REG           (BMG160_RST_LATCH_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR HIGH RATE CONFIGURATION*/
/**********************************************/
/**< Last (2) bits of HIGHRATE_THRES_X Registers */
#define BMG160_HIGHRATE_HYST_X__POS        (6)
#define BMG160_HIGHRATE_HYST_X__LEN        (2)
#define BMG160_HIGHRATE_HYST_X__MSK        (0xC0)
#define BMG160_HIGHRATE_HYST_X__REG        (BMG160_HIGHRATE_THRES_X_ADDR)

/**< (5) bits of HIGHRATE_THRES_X Registers */
#define BMG160_HIGHRATE_THRES_X__POS        (1)
#define BMG160_HIGHRATE_THRES_X__LEN        (5)
#define BMG160_HIGHRATE_THRES_X__MSK        (0x3E)
#define BMG160_HIGHRATE_THRES_X__REG        (BMG160_HIGHRATE_THRES_X_ADDR)

/**< 0th bit of HIGHRATE_THRES_X Registers */
#define BMG160_HIGHRATE_ENABLE_X__POS        (0)
#define BMG160_HIGHRATE_ENABLE_X__LEN        (1)
#define BMG160_HIGHRATE_ENABLE_X__MSK        (0x01)
#define BMG160_HIGHRATE_ENABLE_X__REG        (BMG160_HIGHRATE_THRES_X_ADDR)

/**< Last (2) bits of HIGHRATE_THRES_Y Registers */
#define BMG160_HIGHRATE_HYST_Y__POS        (6)
#define BMG160_HIGHRATE_HYST_Y__LEN        (2)
#define BMG160_HIGHRATE_HYST_Y__MSK        (0xC0)
#define BMG160_HIGHRATE_HYST_Y__REG        (BMG160_HIGHRATE_THRES_Y_ADDR)

/**< (5) bits of HIGHRATE_THRES_Y Registers */
#define BMG160_HIGHRATE_THRES_Y__POS        (1)
#define BMG160_HIGHRATE_THRES_Y__LEN        (5)
#define BMG160_HIGHRATE_THRES_Y__MSK        (0x3E)
#define BMG160_HIGHRATE_THRES_Y__REG        (BMG160_HIGHRATE_THRES_Y_ADDR)

/**< 0th bit of HIGHRATE_THRES_Y Registers */
#define BMG160_HIGHRATE_ENABLE_Y__POS        (0)
#define BMG160_HIGHRATE_ENABLE_Y__LEN        (1)
#define BMG160_HIGHRATE_ENABLE_Y__MSK        (0x01)
#define BMG160_HIGHRATE_ENABLE_Y__REG        (BMG160_HIGHRATE_THRES_Y_ADDR)

/**< Last (2) bits of HIGHRATE_THRES_Z Registers */
#define BMG160_HIGHRATE_HYST_Z__POS        (6)
#define BMG160_HIGHRATE_HYST_Z__LEN        (2)
#define BMG160_HIGHRATE_HYST_Z__MSK        (0xC0)
#define BMG160_HIGHRATE_HYST_Z__REG        (BMG160_HIGHRATE_THRES_Z_ADDR)

/**< (5) bits of HIGHRATE_THRES_Z Registers */
#define BMG160_HIGHRATE_THRES_Z__POS        (1)
#define BMG160_HIGHRATE_THRES_Z__LEN        (5)
#define BMG160_HIGHRATE_THRES_Z__MSK        (0x3E)
#define BMG160_HIGHRATE_THRES_Z__REG        (BMG160_HIGHRATE_THRES_Z_ADDR)

/**< 0th bit of HIGHRATE_THRES_Z Registers */
#define BMG160_HIGHRATE_ENABLE_Z__POS        (0)
#define BMG160_HIGHRATE_ENABLE_Z__LEN        (1)
#define BMG160_HIGHRATE_ENABLE_Z__MSK        (0x01)
#define BMG160_HIGHRATE_ENABLE_Z__REG        (BMG160_HIGHRATE_THRES_Z_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR SLOW OFFSET */
/**********************************************/
/**< Last 3 bits of INT OFF0 Registers */
#define BMG160_SLOW_OFFSET_THRES__POS          (6)
#define BMG160_SLOW_OFFSET_THRES__LEN          (2)
#define BMG160_SLOW_OFFSET_THRES__MSK          (0xC0)
#define BMG160_SLOW_OFFSET_THRES__REG          (BMG160_SOC_ADDR)

/**< 2  bits of INT OFF0 Registers */
#define BMG160_SLOW_OFFSET_DURN__POS         (3)
#define BMG160_SLOW_OFFSET_DURN__LEN         (3)
#define BMG160_SLOW_OFFSET_DURN__MSK         (0x38)
#define BMG160_SLOW_OFFSET_DURN__REG         (BMG160_SOC_ADDR)

/**< 2nd bit of INT OFF0 Registers */
#define BMG160_SLOW_OFFSET_ENABLE_Z__POS        (2)
#define BMG160_SLOW_OFFSET_ENABLE_Z__LEN        (1)
#define BMG160_SLOW_OFFSET_ENABLE_Z__MSK        (0x04)
#define BMG160_SLOW_OFFSET_ENABLE_Z__REG        (BMG160_SOC_ADDR)

/**< 1st bit of INT OFF0 Registers */
#define BMG160_SLOW_OFFSET_ENABLE_Y__POS        (1)
#define BMG160_SLOW_OFFSET_ENABLE_Y__LEN        (1)
#define BMG160_SLOW_OFFSET_ENABLE_Y__MSK        (0x02)
#define BMG160_SLOW_OFFSET_ENABLE_Y__REG        (BMG160_SOC_ADDR)

/**< 0th bit of INT OFF0 Registers */
#define BMG160_SLOW_OFFSET_ENABLE_X__POS        (0)
#define BMG160_SLOW_OFFSET_ENABLE_X__LEN        (1)
#define BMG160_SLOW_OFFSET_ENABLE_X__MSK        (0x01)
#define BMG160_SLOW_OFFSET_ENABLE_X__REG        (BMG160_SOC_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR AUTO OFFSET*/
/**********************************************/
/**< Last 2 bits of INT OFF1 Registers */
#define BMG160_AUTO_OFFSET_WORD_LENGHTH__POS        (6)
#define BMG160_AUTO_OFFSET_WORD_LENGHTH__LEN        (2)
#define BMG160_AUTO_OFFSET_WORD_LENGHTH__MSK        (0xC0)
#define BMG160_AUTO_OFFSET_WORD_LENGHTH__REG        (BMG160_A_FOC_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR FATS OFFSET*/
/**********************************************/
/**< 2  bits of INT OFF1 Registers */
#define BMG160_FAST_OFFSET_WORD_LENGHTH__POS        (4)
#define BMG160_FAST_OFFSET_WORD_LENGHTH__LEN        (2)
#define BMG160_FAST_OFFSET_WORD_LENGHTH__MSK        (0x30)
#define BMG160_FAST_OFFSET_WORD_LENGHTH__REG        (BMG160_A_FOC_ADDR)

/**< 3nd bit of INT OFF1 Registers */
#define BMG160_FAST_OFFSET_ENABLE__POS        (3)
#define BMG160_FAST_OFFSET_ENABLE__LEN        (1)
#define BMG160_FAST_OFFSET_ENABLE__MSK        (0x08)
#define BMG160_FAST_OFFSET_ENABLE__REG        (BMG160_A_FOC_ADDR)

/**< 2nd bit of INT OFF1 Registers */
#define BMG160_FAST_OFFSET_ENABLE_Z__POS      (2)
#define BMG160_FAST_OFFSET_ENABLE_Z__LEN      (1)
#define BMG160_FAST_OFFSET_ENABLE_Z__MSK      (0x04)
#define BMG160_FAST_OFFSET_ENABLE_Z__REG      (BMG160_A_FOC_ADDR)

/**< 1st bit of INT OFF1 Registers */
#define BMG160_FAST_OFFSET_ENABLE_Y__POS      (1)
#define BMG160_FAST_OFFSET_ENABLE_Y__LEN      (1)
#define BMG160_FAST_OFFSET_ENABLE_Y__MSK      (0x02)
#define BMG160_FAST_OFFSET_ENABLE_Y__REG      (BMG160_A_FOC_ADDR)

/**< 0th bit of INT OFF1 Registers */
#define BMG160_FAST_OFFSET_ENABLE_X__POS      (0)
#define BMG160_FAST_OFFSET_ENABLE_X__LEN      (1)
#define BMG160_FAST_OFFSET_ENABLE_X__MSK      (0x01)
#define BMG160_FAST_OFFSET_ENABLE_X__REG      (BMG160_A_FOC_ADDR)

/**< 0 to (2) bits of INT OFF1 Registers */
#define BMG160_FAST_OFFSET_ENABLE_XYZ__POS      (0)
#define BMG160_FAST_OFFSET_ENABLE_XYZ__LEN      (3)
#define BMG160_FAST_OFFSET_ENABLE_XYZ__MSK      (0x07)
#define BMG160_FAST_OFFSET_ENABLE_XYZ__REG      (BMG160_A_FOC_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR NVM*/
/**********************************************/
/**< Last 4 bits of Trim NVM control Registers */
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_REMAIN__POS        (4)
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_REMAIN__LEN        (4)
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_REMAIN__MSK        (0xF0)
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_REMAIN__REG        \
(BMG160_TRIM_NVM_CTRL_ADDR)

/**< 3rd bit of Trim NVM control Registers */
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_LOAD__POS          (3)
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_LOAD__LEN          (1)
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_LOAD__MSK          (0x08)
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_LOAD__REG          \
(BMG160_TRIM_NVM_CTRL_ADDR)

/**< 2nd bit of Trim NVM control Registers */
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_RDY__POS           (2)
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_RDY__LEN           (1)
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_RDY__MSK           (0x04)
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_RDY__REG           \
(BMG160_TRIM_NVM_CTRL_ADDR)

/**< 1st bit of Trim NVM control Registers */
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_PROG_TRIG__POS     (1)
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_PROG_TRIG__LEN     (1)
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_PROG_TRIG__MSK     (0x02)
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_PROG_TRIG__REG     \
(BMG160_TRIM_NVM_CTRL_ADDR)

/**< 0th bit of Trim NVM control Registers */
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_PROG_MODE__POS     (0)
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_PROG_MODE__LEN     (1)
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_PROG_MODE__MSK     (0x01)
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_PROG_MODE__REG     \
(BMG160_TRIM_NVM_CTRL_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR I2C CONFIGURATION*/
/**********************************************/
/**< 2nd bit of SPI3 WDT Registers */
#define BMG160_BGW_SPI3_WDT_ADDR_I2C_WDT_ENABLE__POS      (2)
#define BMG160_BGW_SPI3_WDT_ADDR_I2C_WDT_ENABLE__LEN      (1)
#define BMG160_BGW_SPI3_WDT_ADDR_I2C_WDT_ENABLE__MSK      (0x04)
#define BMG160_BGW_SPI3_WDT_ADDR_I2C_WDT_ENABLE__REG      \
(BMG160_BGW_SPI3_WDT_ADDR)

/**< 1st bit of SPI3 WDT Registers */
#define BMG160_BGW_SPI3_WDT_ADDR_I2C_WDT_SELECT__POS     (1)
#define BMG160_BGW_SPI3_WDT_ADDR_I2C_WDT_SELECT__LEN     (1)
#define BMG160_BGW_SPI3_WDT_ADDR_I2C_WDT_SELECT__MSK     (0x02)
#define BMG160_BGW_SPI3_WDT_ADDR_I2C_WDT_SELECT__REG     \
(BMG160_BGW_SPI3_WDT_ADDR)

/**< 0th bit of SPI3 WDT Registers */
#define BMG160_BGW_SPI3_WDT_ADDR_SPI3__POS            (0)
#define BMG160_BGW_SPI3_WDT_ADDR_SPI3__LEN            (1)
#define BMG160_BGW_SPI3_WDT_ADDR_SPI3__MSK            (0x01)
#define BMG160_BGW_SPI3_WDT_ADDR_SPI3__REG            \
(BMG160_BGW_SPI3_WDT_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR SELFTEST*/
/**********************************************/
/**< 4th bit of Self test Registers */
#define BMG160_SELFTEST_ADDR_RATEOK__POS            (4)
#define BMG160_SELFTEST_ADDR_RATEOK__LEN            (1)
#define BMG160_SELFTEST_ADDR_RATEOK__MSK            (0x10)
#define BMG160_SELFTEST_ADDR_RATEOK__REG            \
(BMG160_SELFTEST_ADDR)

/**< 2nd bit of Self test Registers */
#define BMG160_SELFTEST_ADDR_BISTFAIL__POS          (2)
#define BMG160_SELFTEST_ADDR_BISTFAIL__LEN          (1)
#define BMG160_SELFTEST_ADDR_BISTFAIL__MSK          (0x04)
#define BMG160_SELFTEST_ADDR_BISTFAIL__REG          \
(BMG160_SELFTEST_ADDR)

/**< 1st bit of Self test Registers */
#define BMG160_SELFTEST_ADDR_BISTRDY__POS           (1)
#define BMG160_SELFTEST_ADDR_BISTRDY__LEN           (1)
#define BMG160_SELFTEST_ADDR_BISTRDY__MSK           (0x02)
#define BMG160_SELFTEST_ADDR_BISTRDY__REG           \
(BMG160_SELFTEST_ADDR)

/**< 0th bit of Self test Registers */
#define BMG160_SELFTEST_ADDR_TRIGBIST__POS          (0)
#define BMG160_SELFTEST_ADDR_TRIGBIST__LEN          (1)
#define BMG160_SELFTEST_ADDR_TRIGBIST__MSK          (0x01)
#define BMG160_SELFTEST_ADDR_TRIGBIST__REG          \
(BMG160_SELFTEST_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR FIFO CONFIGURATION*/
/**********************************************/
/**< 7th bit of FIFO CGF1 Registers */
#define BMG160_FIFO_CGF1_ADDR_TAG__POS     (7)
#define BMG160_FIFO_CGF1_ADDR_TAG__LEN     (1)
#define BMG160_FIFO_CGF1_ADDR_TAG__MSK     (0x80)
#define BMG160_FIFO_CGF1_ADDR_TAG__REG     (BMG160_FIFO_CGF1_ADDR)

/**< First 7 bits of FIFO CGF1 Registers */
#define BMG160_FIFO_CGF1_ADDR_WML__POS     (0)
#define BMG160_FIFO_CGF1_ADDR_WML__LEN     (7)
#define BMG160_FIFO_CGF1_ADDR_WML__MSK     (0x7F)
#define BMG160_FIFO_CGF1_ADDR_WML__REG     (BMG160_FIFO_CGF1_ADDR)

/**< Last 2 bits of FIFO CGF0 Addr Registers */
#define BMG160_FIFO_CGF0_ADDR_MODE__POS         (6)
#define BMG160_FIFO_CGF0_ADDR_MODE__LEN         (2)
#define BMG160_FIFO_CGF0_ADDR_MODE__MSK         (0xC0)
#define BMG160_FIFO_CGF0_ADDR_MODE__REG         (BMG160_FIFO_CGF0_ADDR)

/**< First 2 bits of FIFO CGF0 Addr Registers */
#define BMG160_FIFO_CGF0_ADDR_DATA_SELECT__POS     (0)
#define BMG160_FIFO_CGF0_ADDR_DATA_SELECT__LEN     (2)
#define BMG160_FIFO_CGF0_ADDR_DATA_SELECT__MSK     (0x03)
#define BMG160_FIFO_CGF0_ADDR_DATA_SELECT__REG     (BMG160_FIFO_CGF0_ADDR)
/***********************************************/
/**\name    BIT LENGTH, MASK, POSITION FOR OFFSET*/
/**********************************************/
/**< Last 2 bits of INL Offset MSB Registers */
#define BMG160_OFC1_ADDR_OFFSET_X__POS       (6)
#define BMG160_OFC1_ADDR_OFFSET_X__LEN       (2)
#define BMG160_OFC1_ADDR_OFFSET_X__MSK       (0xC0)
#define BMG160_OFC1_ADDR_OFFSET_X__REG       (BMG160_OFFSET_OFC1_ADDR)

/**< 3 bits of INL Offset MSB Registers */
#define BMG160_OFC1_ADDR_OFFSET_Y__POS       (3)
#define BMG160_OFC1_ADDR_OFFSET_Y__LEN       (3)
#define BMG160_OFC1_ADDR_OFFSET_Y__MSK       (0x38)
#define BMG160_OFC1_ADDR_OFFSET_Y__REG       (BMG160_OFFSET_OFC1_ADDR)

/**< First 3 bits of INL Offset MSB Registers */
#define BMG160_OFC1_ADDR_OFFSET_Z__POS       (0)
#define BMG160_OFC1_ADDR_OFFSET_Z__LEN       (3)
#define BMG160_OFC1_ADDR_OFFSET_Z__MSK       (0x07)
#define BMG160_OFC1_ADDR_OFFSET_Z__REG       (BMG160_OFFSET_OFC1_ADDR)

/**< 4 bits of Trim GP0 Registers */
#define BMG160_TRIM_GP0_ADDR_GP0__POS            (4)
#define BMG160_TRIM_GP0_ADDR_GP0__LEN            (4)
#define BMG160_TRIM_GP0_ADDR_GP0__MSK            (0xF0)
#define BMG160_TRIM_GP0_ADDR_GP0__REG            (BMG160_TRIM_GP0_ADDR)

/**< 2 bits of Trim GP0 Registers */
#define BMG160_TRIM_GP0_ADDR_OFFSET_X__POS       (2)
#define BMG160_TRIM_GP0_ADDR_OFFSET_X__LEN       (2)
#define BMG160_TRIM_GP0_ADDR_OFFSET_X__MSK       (0x0C)
#define BMG160_TRIM_GP0_ADDR_OFFSET_X__REG       (BMG160_TRIM_GP0_ADDR)

/**< 1st bit of Trim GP0 Registers */
#define BMG160_TRIM_GP0_ADDR_OFFSET_Y__POS       (1)
#define BMG160_TRIM_GP0_ADDR_OFFSET_Y__LEN       (1)
#define BMG160_TRIM_GP0_ADDR_OFFSET_Y__MSK       (0x02)
#define BMG160_TRIM_GP0_ADDR_OFFSET_Y__REG       (BMG160_TRIM_GP0_ADDR)

/**< First bit of Trim GP0 Registers */
#define BMG160_TRIM_GP0_ADDR_OFFSET_Z__POS       (0)
#define BMG160_TRIM_GP0_ADDR_OFFSET_Z__LEN       (1)
#define BMG160_TRIM_GP0_ADDR_OFFSET_Z__MSK       (0x01)
#define BMG160_TRIM_GP0_ADDR_OFFSET_Z__REG       (BMG160_TRIM_GP0_ADDR)

/***********************************************/
/**\name    CONSTANT DEFINITIONS*/
/**********************************************/
/***********************************************/
/**\name    AXIS ENABLE DEFINITIONS*/
/**********************************************/
/* For Axis Selection   */
/**< It refers BMG160 X-axis */
#define BMG160_X_AXIS           (0)
/**< It refers BMG160 Y-axis */
#define BMG160_Y_AXIS           (1)
/**< It refers BMG160 Z-axis */
#define BMG160_Z_AXIS           (2)
/***********************************************/
/**\name    POWER MODE*/
/**********************************************/
/* For Mode Settings    */
#define BMG160_MODE_NORMAL              (0)
#define BMG160_MODE_DEEPSUSPEND         (1)
#define BMG160_MODE_SUSPEND             (2)
#define BMG160_MODE_FASTPOWERUP         (3)
#define BMG160_MODE_ADVANCEDPOWERSAVING (4)
/***********************************************/
/**\name    BIT SLICE FUNCTIONS */
/**********************************************/
/* get bit slice  */
#define BMG160_GET_BITSLICE(regvar, bitname)\
((regvar & bitname##__MSK) >> bitname##__POS)

/* Set bit slice */
#define BMG160_SET_BITSLICE(regvar, bitname, val)\
((regvar&~bitname##__MSK)|((val<<bitname##__POS)&bitname##__MSK))

/****************************************************/
/**\name    ARRAY SIZE DEFINITIONS      */
/***************************************************/
#define BMG160_X_DATA_SIZE          (2)
#define BMG160_Y_DATA_SIZE          (2)
#define BMG160_Z_DATA_SIZE          (2)
#define BMG160_XYZ_DATA_SIZE        (6)
#define BMG160_XYZ_INTR_DATA_SIZE   (12)

#define BMG160_X_LSB_DATA   (0)
#define BMG160_X_MSB_DATA   (1)
#define BMG160_Y_LSB_DATA   (0)
#define BMG160_Y_MSB_DATA   (1)
#define BMG160_Z_LSB_DATA   (0)
#define BMG160_Z_MSB_DATA   (1)
#define BMG160_INTR0_STAT   (0)
#define BMG160_INTR1_STAT   (1)
#define BMG160_INTR2_STAT   (2)
#define BMG160_INTR3_STAT   (3)
#define BMG160_INTR4_STAT   (4)

#define BMG160_DATA_FRAME_X_LSB_BYTE        (0)
#define BMG160_DATA_FRAME_X_MSB_BYTE        (1)
#define BMG160_DATA_FRAME_Y_LSB_BYTE        (2)
#define BMG160_DATA_FRAME_Y_MSB_BYTE        (3)
#define BMG160_DATA_FRAME_Z_LSB_BYTE        (4)
#define BMG160_DATA_FRAME_Z_MSB_BYTE        (5)
#define BMG160_DATA_FRAME_INTR0_BYTE    (7)
#define BMG160_DATA_FRAME_INTR1_BYTE    (8)
#define BMG160_DATA_FRAME_INTR2_BYTE    (9)
#define BMG160_DATA_FRAME_INTR3_BYTE    (10)
#define BMG160_DATA_FRAME_INTR4_BYTE    (11)
/***********************************************/
/**\name    COMMON DEFINITIONS*/
/**********************************************/

#define BMG160_NULL                             (0)
/**< constant declaration of NULL */
#define BMG160_DISABLE                          (0)
/**< It refers BMG160 disable */
#define BMG160_ENABLE                           (1)
/**< It refers BMG160 enable */
#define BMG160_OFF                              (0)
/**< It refers BMG160 OFF state */
#define BMG160_ON                               (1)
/**< It refers BMG160 ON state  */


#define BMG160_INTR1                              (0)
/**< It refers BMG160 INT1 */
#define BMG160_INTR2                              (1)
/**< It refers BMG160 INT2 */
/***********************************************/
/**\name    OFFSET DEFINITIONS*/
/**********************************************/
#define BMG160_SLOW_OFFSET                         (0)
/**< It refers BMG160 Slow Offset */
#define BMG160_AUTO_OFFSET                         (1)
/**< It refers BMG160 Auto Offset */
#define BMG160_FAST_OFFSET                         (2)
/**< It refers BMG160 Fast Offset */
/***********************************************/
/**\name    INTERRUPT DEFINITIONS*/
/**********************************************/
#define BMG160_S_TAP                               (0)
/**< It refers BMG160 Single Tap */
#define BMG160_D_TAP                               (1)
/**< It refers BMG160 Double Tap */
#define BMG160_INTR1_DATA                          (0)
/**< It refers BMG160 Int1 Data */
#define BMG160_INTR2_DATA                          (1)
/**< It refers BMG160 Int2 Data */
#define BMG160_TAP_UNFILT_DATA                     (0)
/**< It refers BMG160 Tap unfilt data */
#define BMG160_HIGHRATE_UNFILT_DATA                (1)
/**< It refers BMG160 High unfilt data */
#define BMG160_CONST_UNFILT_DATA                   (2)
/**< It refers BMG160 Const unfilt data */
#define BMG160_ANY_MOTION_UNFILT_DATA              (3)
/**< It refers BMG160 Any unfilt data */
#define BMG160_SHAKE_UNFILT_DATA                   (4)
/**< It refers BMG160 Shake unfilt data */
#define BMG160_SHAKE_TH                            (0)
/**< It refers BMG160 Shake Threshold */
#define BMG160_SHAKE_TH2                           (1)
/**< It refers BMG160 Shake Threshold2 */
#define BMG160_AUTO_OFFSET_WORD_LENGHTH            (0)
/**< It refers BMG160 Auto Offset word length */
#define BMG160_FAST_OFFSET_WORD_LENGHTH            (1)
/**< It refers BMG160 Fast Offset word length */
/***********************************************/
/**\name    I2C CONFIGURATION DEFINITIONS*/
/**********************************************/
#define BMG160_I2C_WDT_ENABLE                   (0)
/**< It refers BMG160 I2C WDT En */
#define BMG160_I2C_WDT_SELECT                   (1)
/**< It refers BMG160 I2C WDT Sel */
#define BMG160_EXT_MODE                         (0)
/**< It refers BMG160 Ext Mode */
#define BMG160_EXT_PAGE                         (1)
/**< It refers BMG160 Ext page */
#define BMG160_START_ADDR                       (0)
/**< It refers BMG160 Start Address */
#define BMG160_STOP_ADDR                        (1)
/**< It refers BMG160 Stop Address */
#define BMG160_SLOW_CMD                         (0)
/**< It refers BMG160 Slow Command */
#define BMG160_FAST_CMD                         (1)
/**< It refers BMG160 Fast Command */
#define BMG160_TRIM_VRA                         (0)
/**< It refers BMG160 Trim VRA */
#define BMG160_TRIM_VRD                         (1)
/**< It refers BMG160 Trim VRD */
#define BMG160_LOGBIT_EM                        (0)
/**< It refers BMG160 LogBit Em */
#define BMG160_LOGBIT_VM                        (1)
/**< It refers BMG160 LogBit VM */
#define BMG160_GP0                              (0)
/**< It refers BMG160 GP0 */
#define BMG160_GP1                              (1)
/**< It refers BMG160 GP1*/
#define BMG160_LOW_SPEED                        (0)
/**< It refers BMG160 Low Speed Oscillator */
#define BMG160_HIGHRATE_SPEED                   (1)
/**< It refers BMG160 High Speed Oscillator */
#define BMG160_DRIVE_OFFSET_P                   (0)
/**< It refers BMG160 Drive Offset P */
#define BMG160_DRIVE_OFFSET_N                   (1)
/**< It refers BMG160 Drive Offset N */
#define BMG160_TEST_MODE_ENABLE                 (0)
/**< It refers BMG160 Test Mode Enable */
#define BMG160_TEST_MODE_REG                    (1)
/**< It refers BMG160 Test Mode reg */
#define BMG160_IBIAS_DRIVE_TRIM                 (0)
/**< It refers BMG160 IBIAS Drive Trim */
#define BMG160_IBIAS_RATE_TRIM                  (1)
/**< It refers BMG160 IBIAS Rate Trim */
#define BMG160_BAA_MODE                         (0)
/**< It refers BMG160 BAA Mode Trim */
#define BMG160_BMA_MODE                         (1)
/**< It refers BMG160 BMA Mode Trim */
#define BMG160_PI_KP                            (0)
/**< It refers BMG160 PI KP */
#define BMG160_PI_KI                            (1)
/**< It refers BMG160 PI KI */

/***********************************************/
/**\name    ERROR/SUCCESS DEFINITIONS*/
/**********************************************/
#define C_BMG160_SUCCESS                        (0)
/**< It refers BMG160 operation is success */
#define C_BMG160_FAILURE                        (1)
/**< It refers BMG160 operation is Failure */
#define E_BMG160_NULL_PTR               ((s8)-127)
#define E_BMG160_OUT_OF_RANGE           ((s8)-2)
#define ERROR                           ((s8)-1)
/***********************************************/
/**\name    SPI DEFINITIONS*/
/**********************************************/
#define BMG160_SPI_RD_MASK     (0x80)
/**< Read mask **/
#define BMG160_READ_SET       (0x01)
/**< Setting for reading data **/
/***********************************************/
/**\name    BIT SHIFTING DEFINITIONS*/
/**********************************************/
#define BMG160_SHIFT_BIT_POSITION_BY_01_BIT   (1)
/**< Shift bit by 1 Position **/
#define BMG160_SHIFT_BIT_POSITION_BY_02_BITS  (4)
/**< Shift bit by 2 Position **/
#define BMG160_SHIFT_BIT_POSITION_BY_04_BITS  (4)
/**< Shift bit by (4) Position **/
#define BMG160_SHIFT_BIT_POSITION_BY_08_BITS  (8)
/**< Shift bit by (8) Position **/
/***********************************************/
/**\name    NUMERIC DEFINITIONS*/
/**********************************************/
#define BMG160_INIT_VALUE                   ((u8)0)
#define BMG160_GEN_READ_WRITE_DATA_LENGTH   ((u8)1)
#define BMG160_X_DATA_LENGTH                ((u8)2)
#define BMG160_Y_DATA_LENGTH                ((u8)2)
#define BMG160_Z_DATA_LENGTH                ((u8)2)
#define BMG160_ALL_DATA_FRAME_LENGTH        ((u8)6)
#define BMG160_BIT_LENGTH_HIGH_BW           ((u8)2)
#define BMG160_BIT_LENGTH_SHADOW_DIS        ((u8)2)
#define BMG160_BIT_LENGTH_FIFO              ((u8)2)
#define BMG160_BIT_LENGTH_FIFO_WM           ((u8)2)
#define BMG160_BIT_LENGTH_FIFO_TAG          ((u8)2)
#define BMG160_BIT_LENGTH_FIFO_MODE         ((u8)4)
#define BMG160_BIT_LENGTH_FIFO_DATA_SELECT  ((u8)4)
#define BMG160_BIT_MASK_MODE_LPM1           ((u8)4)
#define BMG160_BIT_LENGTH_RANGE             ((u8)5)
#define BMG160_BIT_LENGTH_BW                ((u8)8)
#define BMG160_BIT_LENGTH_DURN              ((u8)8)
#define BMG160_BIT_LENGTH_POWER_MODE        ((u8)5)
#define BMG160_XYZ_AND_INTR_DATA_LENGTH     ((u8)12)
#define BMG160_FIFO_WM_LENGTH               ((u8)128)
#define BMG160_POWER_MODE_DELAY     ((u8)1)
#define BMG160_SELFTEST_DELAY       ((u8)10)
#define BMG160_SELFTEST_BISTFAIL    ((u8)0x00)
#define BMG160_SELFTEST_RATEOK      ((u8)0x01)
/***********************************************/
/**\name    BANDWIDTH DEFINITIONS*/
/**********************************************/
#define C_BMG160_NO_FILTER_U8X          (0)
#define C_BMG160_BW_230HZ_U8X           (1)
#define C_BMG160_BW_116HZ_U8X           (2)
#define C_BMG160_BW_47HZ_U8X            (3)
#define C_BMG160_BW_23HZ_U8X            (4)
#define C_BMG160_BW_12HZ_U8X            (5)
#define C_BMG160_BW_64HZ_U8X            (6)
#define C_BMG160_BW_32HZ_U8X            (7)

#define BMG160_BW_500_HZ    (0x01)
#define BMG160_BW_230_HZ    (0x01)
#define BMG160_BW_116_HZ    (0x02)
#define BMG160_BW_47_HZ     (0x03)
#define BMG160_BW_23_HZ     (0x04)
#define BMG160_BW_12_HZ     (0x05)
#define BMG160_BW_64_HZ     (0x06)
#define BMG160_BW_32_HZ     (0x07)
/***********************************************/
/**\name    SLEEP DURATION DEFINITIONS*/
/**********************************************/

#define C_BMG160_NO_AUTO_SLEEP_DURN_U8X     (0)
#define C_BMG160_4MS_AUTO_SLEEP_DURN_U8X    (1)
#define C_BMG160_5MS_AUTO_SLEEP_DURN_U8X    (2)
#define C_BMG160_8MS_AUTO_SLEEP_DURN_U8X    (3)
#define C_BMG160_10MS_AUTO_SLEEP_DURN_U8X   (4)
#define C_BMG160_15MS_AUTO_SLEEP_DURN_U8X   (5)
#define C_BMG160_20MS_AUTO_SLEEP_DURN_U8X   (6)
#define C_BMG160_40MS_AUTO_SLEEP_DURN_U8X   (7)
/***********************************************/
/**\name    RANGE DEFINITIONS*/
/**********************************************/
#define BMG160_RANGE_2000   (0x00)
#define BMG160_RANGE_1000   (0x01)
#define BMG160_RANGE_500    (0x02)
#define BMG160_RANGE_250    (0x03)
#define BMG160_RANGE_125    (0x04)

/***********************************************/
/**\name    SOFT RESET DEFINITIONS*/
/**********************************************/
#define BMG160_SOFT_RESET   (0xB6)
/***********************************************/
/**\name    LATCH  DEFINITIONS*/
/**********************************************/
#define BMG160_NON_LATCH            (0x00)
#define BMG160_LATCH_250_MS         (0x01)
#define BMG160_LATCH_500_MS         (0x02)
#define BMG160_LATCH_1_SEC          (0x03)
#define BMG160_LATCH_2_SEC          (0x04)
#define BMG160_LATCH_4_SEC          (0x05)
#define BMG160_LATCH_8_SEC          (0x06)
#define BMG160_LATCH_LATCHED        (0x07)
#define BMG160_LATCH_NON_LATCHED    (0x08)
#define BMG160_LATCH_250_MICRO_SEC  (0x09)
#define BMG160_LATCH_500_MICRO_SEC  (0x0A)
#define BMG160_LATCH_1_MILLI_SEC    (0x0B)
#define BMG160_LATCH_12_5_MILLI_SEC (0x0C)
#define BMG160_LATCH_25_MILLI_SEC   (0x0D)
#define BMG160_LATCH_50_MILLI_SEC   (0x0E)
/***********************************************/
/**\name    OFFSET DEFINITIONS*/
/**********************************************/
#define BMG160_OFFSET_MASK_BYTE_OF_DATA (0x0FF0)
#define BMG160_OFFSET_X_BIT_MASK1       (0x000C)
#define BMG160_OFFSET_X_BIT_MASK2       (0x0003)
#define BMG160_OFFSET_Y_Z_BIT_MASK1     (0x0001)
#define BMG160_OFFSET_Y_Z_BIT_MASK2     (0x000E)
/***********************************************/
/**\name    BUS READ AND WRITE FUNCTION POINTERS DEFINITIONS*/
/**********************************************/
#define BMG160_WR_FUNC_PTR s8 (*bus_write)\
(u8, u8, u8 *, u8)
#define BMG160_RD_FUNC_PTR s8 (*bus_read)\
(u8, u8, u8 *, u8)
#define BMG160_BRD_FUNC_PTR s8 (*burst_read)\
(u8, u8, u8 *, s32)
#define BMG160_MDELAY_DATA_TYPE u32
/**************************************************************/
/**\name    STRUCTURE DEFINITIONS                         */
/**************************************************************/
/*!
 * @brief Structure containing gyro xyz data
 */
struct bmg160_data_t
{
    s16 datax;/**<gyro X  data*/
    s16 datay;/**<gyro Y  data*/
    s16 dataz;/**<gyro Z  data*/
    char intstatus[5];/**<gyro interrupt status*/
};

/*!
 * @brief Structure containing gyro offset xyz data
 */
struct bmg160_offset_t
{
    u16 datax;/**<offset X  data*/
    u16 datay;/**<offset Y  data*/
    u16 dataz;/**<offset Z  data*/
};
/*!
*   @brief bmg160_t structure
*   This structure holds all relevant information about bmg160
*/
struct bmg160_t
{
    u8 chip_id;/**< chip id of BMG160 */
    u8 dev_addr;/**< device address of BMG160 */

    BMG160_BRD_FUNC_PTR;/**< burst read function pointer of BMG160 */
    BMG160_WR_FUNC_PTR;/**< bus write function pointer of BMG160 */
    BMG160_RD_FUNC_PTR;/**< bus read function pointer of BMG160 */
    void (*delay_msec)(BMG160_MDELAY_DATA_TYPE);/**< delay function pointer of BMG160 */
};
/***********************************************/
/**\name    FUNCTION DECLARATIONS */
/**********************************************/
/*!
 *  @brief This function is used for initialize
 *  the bus read and bus write functions
 *  and assign the chip id and I2C address of the gyro
 *  chip id is read in the register 0x00 bit from 0 to 7
 *
 *  @param bmg160 structure pointer.
 *
 *  @note While changing the parameter of the bmg160_t
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
BMG160_RETURN_FUNCTION_TYPE bmg160_init(struct bmg160_t *bmg160);
/***********************************************/
/**\name    DATA READ XYZ */
/**********************************************/
/*!
 * @brief Reads Rate data X in the registers 0x02 to 0x03
 *
 *
 *
 *
 *  @param v_data_x_s16: The value of gyro x axis data
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
*   @retval -1 -> Error
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_data_X(s16 *v_data_x_s16);
/*!
 * @brief Reads Rate data Y in the registers 0x04 to 0x05
 *
 *
 *
 *
 *  @param v_data_y_s16: The value of gyro y axis data
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_data_Y(s16 *v_data_y_s16);
/*!
 *  @brief Reads Rate data Z in the registers 0x06 to 0x07
 *
 *
 *  @param v_data_z_s16: The value of gyro z axis data
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_data_Z(s16 *v_data_z_s16);
/*!
 * @brief Reads data X,Y and Z from register location 0x02 to 0x07
 *
 *
 *
 *
 *  @param data: The value of gyro xyz axis data
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_data_XYZ(struct bmg160_data_t *data);
/*!
 *  @brief Reads data X,Y,Z and Interrupts
 *  from register location 0x02 to 0x07
 *
 *
 *  @param data: The value of gyro xyz axis data and interrupt status
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_data_XYZI(struct bmg160_data_t *data);
/***********************************************/
/**\name    TEMPERATURE DATA READ */
/**********************************************/
/*!
 * @brief Reads Temperature from register location 0x08
 *
 *
 *
 *
 *  @param v_temp_s8: The value of temperature
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_temp(s8 *v_temp_s8);
/***********************************************/
/**\name    COMMON READ AND WRITE FUNCTIONS */
/**********************************************/
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
BMG160_RETURN_FUNCTION_TYPE bmg160_read_register(u8 v_addr_u8,
        u8 *v_data_u8, u8 v_len_u8);
/*!
 * @brief
 *  This API reads the data from
 *  the given register
 *
 *
 *  @param v_addr_u8 -> Address of the register
 *  @param v_data_u8 -> The data from the register
 *  @param v_len_u32 -> no of bytes to read
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMG160_RETURN_FUNCTION_TYPE bmg160_burst_read(u8 v_addr_u8,
        u8 *v_data_u8, u32 v_len_u32);
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
BMG160_RETURN_FUNCTION_TYPE bmg160_write_register(u8 v_addr_u8,
        u8 *v_data_u8, u8 v_len_u8);
/***********************************************/
/**\name    INTERRUPT STATUS */
/**********************************************/
/*!
 *  @brief This api used to reads interrupt status of
 *  any motion and high rate in the register 0x09
 *  @note  any motion bit   ->  2
 *  @note high rate bit ->  1
 *
 *
 *
 *  @param v_stat0_data_u8 : The interrupt status of
 *  any motion and high rate
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_intr_stat_reg_zero(
    u8 *v_stat0_data_u8);
/*!
 *  @brief This api used to reads the interrupt status of
 *  data, auto_offset, fast_offset and fifo_int in the register 0x0A
 *  @note data bit          ->  7
 *  @note auto_offset bit   ->  6
 *  @note fast_offset bit   ->  5
 *  @note fifo_int bit      ->  4
 *
 *
 *
 *  @param
 *  v_stat1_data_u8 : The interrupt status of
 *  data, auto_offset, fast_offset and fifo_int
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_intr_stat_reg_one(
    u8 *v_stat1_data_u8);
/*!
 *  @brief This api used to reads the interrupt status of
 *  @note any motion sign, any motion first_z, any motion
 *  first_x and any motion first_y in the register 0x0B
 *  @note any motion sign bit       ->  3
 *  @note any motion first_z bit    ->  2
 *  @note any motion first_x bit    ->  1
 *  @note any motion first_y bit    ->  0
 *
 *
 *
 *  @param
 *  v_stat2_data_u8 : Pointer holding the the interrupt status of
 *  any motion sign, any motion first_z,
 *  any motion first_x and any motion first_y
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_intr_stat_reg_two(
    u8 *v_stat2_data_u8);
/*!
*  @brief This api used to reads the interrupt status of
*  high_rate sign, high_rate first_z, high_rate first_x
*  and high_rate first_y in the register 0x0C
*  @note high_rate sign bit        ->  3
*  @note high_rate first_z bit ->  2
*  @note high_rate first_x bit ->  1
*  @note high_rate first_y bit ->  0
*  @note high_rate first_y bit ->  0
*
*
*
*  @param
*  v_stat3_data_u8 : The interrupt status of
*  high_rate sign, high_rate first_z,
*  high_rate first_x and high_rate first_y
*
*
*  @return results of bus communication function
*  @retval 0 -> Success
*  @retval -1 -> Error
*
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_intr_stat_reg_three(
    u8 *v_stat3_data_u8);
/***********************************************/
/**\name     RANGE*/
/**********************************************/
/*!
 *  @brief This API is used to get
 *  the range in the register 0x0F bits from 0 to 2
 *
 *  @param v_range_u8 : The value of gyro range
 *  value    |   range
 * ----------|-----------
 *    0x00   | BMG160_RANGE_2000
 *    0x01   | BMG160_RANGE_1000
 *    0x02   | BMG160_RANGE_500
 *    0x03   | BMG160_RANGE_250
 *    0x04   | BMG160_RANGE_125
 *
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
BMG160_RETURN_FUNCTION_TYPE bmg160_get_range_reg(u8 *v_range_u8);
/*!
 *  @brief This API is used to set
 *  the range in the register 0x0F bits from 0 to 2
 *
 *  @param v_range_u8 : The value of gyro range
 *  value    |   range
 * ----------|-----------
 *    0x00   | BMG160_RANGE_2000
 *    0x01   | BMG160_RANGE_1000
 *    0x02   | BMG160_RANGE_500
 *    0x03   | BMG160_RANGE_250
 *    0x04   | BMG160_RANGE_125
 *
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
BMG160_RETURN_FUNCTION_TYPE bmg160_set_range_reg(u8 v_range_u8);
/***********************************************/
/**\name    BANDWIDTH  */
/**********************************************/
/*!
 *  @brief This API is used to get the gyro bandwidth
 *  in the register 0x10 bits from 0 to 3
 *
 *
 *
 *
 *
 *  @param  v_bw_u8: The value of gyro bandwidth
 *  value   |  bandwidth
 * ---------|---------------
 *   0x00   |  BMG160_BW_500_HZ
 *   0x01   |  BMG160_BW_230_HZ
 *   0x02   |  BMG160_BW_116_HZ
 *   0x03   |  BMG160_BW_47_HZ
 *   0x04   |  BMG160_BW_23_HZ
 *   0x05   |  BMG160_BW_12_HZ
 *   0x06   |  BMG160_BW_64_HZ
 *   0x07   |  BMG160_BW_32_HZ
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_bw(u8 *v_bw_u8);
/*!
 *  @brief This API is used to set the gyro bandwidth
 *  in the register 0x10 bits from 0 to 3
 *
 *
 *
 *
 *
 *  @param  v_bw_u8: The value of gyro bandwidth
 *  value   |  bandwidth
 * ---------|---------------
 *   0x00   |  BMG160_BW_500_HZ
 *   0x01   |  BMG160_BW_230_HZ
 *   0x02   |  BMG160_BW_116_HZ
 *   0x03   |  BMG160_BW_47_HZ
 *   0x04   |  BMG160_BW_23_HZ
 *   0x05   |  BMG160_BW_12_HZ
 *   0x06   |  BMG160_BW_64_HZ
 *   0x07   |  BMG160_BW_32_HZ
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_bw(u8 v_bw_u8);
/***********************************************/
/**\name     POWER MODE TRIGGER */
/**********************************************/
/*!
 *  @brief This API used to get the status of
 *  External Trigger selection in the register 0x12h bits from 4 to 5
 *
 *
 *
 *
 *  @param v_pwu_ext_tri_select_u8 : The value of External Trigger selection
 *  v_pwu_ext_tri_select_u8  |  Trigger source
 * --------------------------|-------------------------
 *      0x00                 |      No
 *      0x01                 |   INT1 pin
 *      0x02                 |   INT2 pin
 *      0x03                 |  SDO pin(SPI3 mode)
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_pmu_ext_tri_select(
    u8 *v_pwu_ext_tri_select_u8);
/*!
 *  @brief This API used to set the status of
 *  External Trigger selection in the register 0x12h bits from 4 to 5
 *
 *
 *
 *
 *  @param v_pwu_ext_tri_select_u8 : The value of External Trigger selection
 *  v_pwu_ext_tri_select_u8  |  Trigger source
 * --------------------------|-------------------------
 *      0x00                 |      No
 *      0x01                 |   INT1 pin
 *      0x02                 |   INT2 pin
 *      0x03                 |  SDO pin(SPI3 mode)
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_pmu_ext_tri_select(
    u8 v_pwu_ext_tri_select_u8);
/***********************************************/
/**\name     HIGH BANDWIDTH*/
/**********************************************/
/*!
 *  @brief  This API is used to get data high bandwidth
 *  in the register 0x13 bit 7
 *
 *
 *
 *  @param v_high_bw_u8 : The value of high bandwidth
 *  value   |  Description
 * ---------|--------------
 *    1     | unfiltered
 *    0     | filtered
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_high_bw(u8 *v_high_bw_u8);
/*!
 *  @brief  This API is used to set data high bandwidth
 *  in the register 0x13 bit 7
 *
 *
 *
 *  @param v_high_bw_u8 : The value of high bandwidth
 *  value   |  Description
 * ---------|--------------
 *    1     | unfiltered
 *    0     | filtered
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_high_bw(u8 v_high_bw_u8);
/***********************************************/
/**\name     SHADOW DIS*/
/**********************************************/
/*!
 *  @brief  This API is used to get the shadow dis
 *  in the register 0x13 bit 6
 *
 *
 *
 *  @param v_shadow_dis_u8 : The value of shadow dis
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_shadow_dis(u8 *v_shadow_dis_u8);
/*!
 *  @brief  This API is used to set the shadow dis
 *  in the register 0x13 bit 6
 *
 *
 *
 *  @param v_shadow_dis_u8 : The value of shadow dis
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_shadow_dis(u8 v_shadow_dis_u8);
/***********************************************/
/**\name     OFFSET RESET */
/**********************************************/
/*!
 *  This function is used for the soft reset
 *  The soft reset register will be written with 0xB6 in the register 0x14.
 *
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
BMG160_RETURN_FUNCTION_TYPE bmg160_set_soft_rst(void);
/***********************************************/
/**\name      DATA INTERRUPT */
/**********************************************/
/*!
 *  @brief This API is used to get the data(data_enable)
 *  interrupt enable bits of the sensor in the registers 0x15 bit 7
 *
 *
 *
 *
 *  @param v_data_enable_u8 : The value of data enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_data_enable(u8 *v_data_enable_u8);
/*!
 *  @brief This API is used to set the data(data_enable)
 *  interrupt enable bits of the sensor in the registers 0x15 bit 7
 *
 *
 *
 *
 *  @param v_data_enable_u8 : The value of data enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_data_enable(u8 v_data_enable_u8);
/***********************************************/
/**\name     FIFO INTERRUPT */
/**********************************************/
/*!
 *  @brief This API is used to get the fifo(fifo_enable)
 *  interrupt enable bits of the sensor in the registers 0x15 bit 6
 *
 *
 *
 *
 *  @param v_fifo_enable_u8 : The value of  fifo enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_fifo_enable(u8 *v_fifo_enable_u8);
/*!
 *  @brief This API is used to set the fifo(fifo_enable)
 *  interrupt enable bits of the sensor in the registers 0x15 bit 6
 *
 *
 *
 *
 *  @param v_fifo_enable_u8 : The value of  fifo enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_fifo_enable(u8 v_fifo_enable_u8);
/***********************************************/
/**\name     AUTO OFFSET INTERRUPT */
/**********************************************/
/*!
 *  @brief This API is used to get
 *  the auto offset(auto_offset_enable) interrupt enable bits of
 *  the sensor in the registers 0x15 bit 3
 *
 *
 *
 *  @param v_offset_enable_u8 : The value of offset enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_auto_offset_enable(
    u8 *v_offset_enable_u8);
/*!
 *  @brief This API is used to set
 *  the auto offset(auto_offset_enable) interrupt enable bits of
 *  the sensor in the registers 0x15 bit 3
 *
 *
 *
 *  @param v_offset_enable_u8 : The value of offset enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_auto_offset_enable(
    u8 v_offset_enable_u8);
/***********************************************/
/**\name     OUTPUT TYPE AND LEVEL CONFIGURATION FOR INTERRUPT */
/**********************************************/
/*!
 *  @brief This API is used to get
 *  the output type status in the register 0x16.
 *  @note INT1 -> bit 1
 *  @note INT2 -> bit 3
 *
 *  @param  v_param_u8: The value of output type selection number
 *    v_param_u8| output type
 *  ------------|--------------
 *      0       |   BMG160_INTR1
 *      1       |   BMG160_INTR2
 *
 *  @param v_intr_output_type_u8: The value of output type
 *   value    |  output
 * -----------|-------------
 *    1       | open drain
 *    0       | push pull
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_intr_output_type(u8 v_param_u8,
        u8 *v_intr_output_type_u8);
/*!
 *  @brief This API is used to set
 *  the output type status in the register 0x16.
 *  @note INT1 -> bit 1
 *  @note INT2 -> bit 3
 *
 *  @param  v_param_u8: The value of output type selection number
 *    v_param_u8| output type
 *  ------------|--------------
 *      0       |   BMG160_INTR1
 *      1       |   BMG160_INTR2
 *
 *  @param v_intr_output_type_u8: The value of output type
 *   value    |  output
 * -----------|-------------
 *    1       | open drain
 *    0       | push pull
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_intr_output_type(u8 v_param_u8,
        u8 v_intr_output_type_u8);
/*!
 *  @brief This API is used to get
 *  Active Level status in the register 0x16
 *  @note INT1 -> bit 0
 *  @note INT2 -> bit 2
 *
 *  @param  v_param_u8: The value of Active Level selection number
 *    v_param_u8| Active Level
 *  ------------|--------------
 *      0       |   BMG160_INTR1
 *      1       |   BMG160_INTR2
 *
 *  @param  v_intr_level_u8: The  value of Active Level status value
 *   value    |  Active Level
 * -----------|-------------
 *    1       | Active HIGH
 *    0       | Active LOW
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_intr_level(u8 v_param_u8,
        u8 *v_intr_level_u8);
/*!
 *  @brief This API is used to set
 *  Active Level status in the register 0x16
 *  @note INT1 -> bit 0
 *  @note INT2 -> bit 2
 *
 *  @param  v_param_u8: The value of Active Level selection number
 *    v_param_u8| Active Level
 *  ------------|--------------
 *      0       |   BMG160_INTR1
 *      1       |   BMG160_INTR2
 *
 *  @param  v_intr_level_u8: The  value of Active Level status value
 *   value    |  Active Level
 * -----------|-------------
 *    1       | Active HIGH
 *    0       | Active LOW
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_intr_level(u8 v_param_u8,
        u8 v_intr_level_u8);
/***********************************************/
/**\name     HIGH RATE INTERRUPT */
/**********************************************/
/*!
 *  @brief This API is used to get
 *  the high rate(int1_high) interrupt1 enable bits of
 *  the sensor in the registers 0x17 bit 3
 *
 *
 *
 *  @param v_intr1_u8 : The value of interrupt1 high_rate enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_intr1_highrate(u8 *v_intr1_u8);
/*!
 *  @brief This API is used to set
 *  the high rate(int1_high) interrupt1 enable bits of
 *  the sensor in the registers 0x17 bit 3
 *
 *
 *
 *  @param v_intr1_u8 : The value of interrupt1 high_rate enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_intr1_highrate(
    u8 v_intr1_u8);
/***********************************************/
/**\name     ANY MOTION INTERRUPT */
/**********************************************/
/*!
 *  @brief This API is used to get
 *  the any motion(int1_any) interrupt1 enable bits of
 *  the sensor in the registers 0x17 bit 1
 *
 *
 *
 *  @param v_int1r_any_motion_u8 : The value of any motion interrupt1
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_intr1_any_motion(
    u8 *v_int1r_any_motion_u8);
/*!
 *  @brief This API is used to set
 *  the any motion(int1_any) interrupt1 enable bits of
 *  the sensor in the registers 0x17 bit 1
 *
 *
 *
 *  @param v_int1r_any_motion_u8 : The value of any motion interrupt1
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_intr1_any_motion(
    u8 v_int1r_any_motion_u8);
/***********************************************/
/**\name     DATA INTERRUPT */
/**********************************************/
/*!
 *  @brief This API is used to get
 *  the data interrupt1 and interrupt2(int1_data and int2_data)
 *  in the register 0x18
 *  @note INT1 -> bit 0
 *  @note INT2 -> bit 7
 *
 *  @param  v_axis_u8: data interrupt selection
 *    v_axis_u8 | Data interrupt
 *  ------------|--------------
 *      0       |   BMG160_INTR1_DATA
 *      1       |   BMG160_INTR2_DATA
 *
 *  @param  v_intr_data_u8: The value of data interrupt1 or interrupt2
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_intr_data(u8 v_axis_u8,
        u8 *v_intr_data_u8);
/*!
 *  @brief This API is used to set
 *  the data interrupt1 and interrupt2(int1_data and int2_data)
 *  in the register 0x18
 *  @note INT1 -> bit 0
 *  @note INT2 -> bit 7
 *
 *  @param  v_axis_u8: data interrupt selection
 *    v_axis_u8 | Data interrupt
 *  ------------|--------------
 *      0       |   BMG160_INTR1_DATA
 *      1       |   BMG160_INTR2_DATA
 *
 *  @param  v_intr_data_u8: The value of data interrupt1 or interrupt2
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_intr_data(u8 v_axis_u8,
        u8 v_intr_data_u8);
/***********************************************/
/**\name     OFFSET AND AUTO OFFSET ENABLE */
/**********************************************/
/*!
 *  @brief This API is used to get
 *  the fast offset(intr2_fast_offset) and auto offset(intr2_auto_offset)
 *  of interrupt2 in the register 0x18
 *  @note int2_fast_offset -> bit 6
  * @note int2_auto_offset -> bit 4
 *
 *  @param v_axis_u8: The value of fast/auto offset interrupts selection
 *    v_axis_u8 | Data interrupt
 *  ------------|--------------
 *      1       |   BMG160_FAST_OFFSET
 *      2       |   BMG160_AUTO_OFFSET
 *
 *  @param v_intr2_offset_u8: The value of fast/auto offset enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_intr2_offset(u8 v_axis_u8,
        u8 *v_intr2_offset_u8);
/*!
 *  @brief This API is used to set
 *  the fast offset(intr2_fast_offset) and auto offset(intr2_auto_offset)
 *  of interrupt2 in the register 0x18
 *  @note int2_fast_offset -> bit 6
  * @note int2_auto_offset -> bit 4
 *
 *  @param v_axis_u8: The value of fast/auto offset interrupts selection
 *    v_axis_u8 | Data interrupt
 *  ------------|--------------
 *      1       |   BMG160_FAST_OFFSET
 *      2       |   BMG160_AUTO_OFFSET
 *
 *  @param v_intr2_offset_u8: The value of fast/auto offset enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_intr2_offset(u8 v_axis_u8,
        u8 v_intr2_offset_u8);
/*!
 *  @brief This API is used to get
 *  the fast offset(int1_fast_offset) and auto offset(int1_auto_offset)
 *  of interrupt1 in the register 0x18
 *  @note int1_fast_offset -> bit 1
 *  @note int1_auto_offset -> bit 3
 *
 *  @param v_axis_u8: The value of fast/auto offset interrupts selection
 *    v_axis_u8 | Data interrupt
 *  ------------|--------------
 *      1       |   BMG160_FAST_OFFSET
 *      2       |   BMG160_AUTO_OFFSET
 *
 *  @param v_intr1_offset_u8: The value of fast/auto offset
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_intr_offset(u8 v_axis_u8,
        u8 *v_intr1_offset_u8);
/*!
 *  @brief This API is used to set
 *  the fast offset(int1_fast_offset) and auto offset(int1_auto_offset)
 *  of interrupt1 in the register 0x18
 *  @note int1_fast_offset -> bit 1
 *  @note int1_auto_offset -> bit 3
 *
 *  @param v_axis_u8: The value of fast/auto offset interrupts selection
 *    v_axis_u8 | Data interrupt
 *  ------------|--------------
 *      1       |   BMG160_FAST_OFFSET
 *      2       |   BMG160_AUTO_OFFSET
 *
 *  @param v_intr1_offset_u8: The value of fast/auto offset
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_intr1_offset(u8 v_axis_u8,
        u8 v_intr1_offset_u8);
/***********************************************/
/**\name    FIFO ENABLE */
/**********************************************/
/*!
 *  @brief This API is used to get
 *  the fifo(int2_fifo) interrupt2 enable bits of
 *  the sensor in the registers 0x18 bit 5
 *
 *
 *
 *  @param v_intr_fifo_u8 : The interrupt2 fifo value
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_intr2_fifo(u8 *v_intr_fifo_u8);
/*!
 *  @brief This API is used to get
 *  the fifo(int1_fifo) interrupt1 enable bits of
 *  the sensor in the registers 0x18 bit 5
 *
 *
 *
 *  @param v_intr_fifo_u8 : The interrupt1 fifo value
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_intr1_fifo(u8 *v_intr_fifo_u8);
/*!
 *  @brief This API is used to set the value of
 *  the fifo interrupt1 and interrupt2(int1_fifo and int2_fifo)
 *  in the register 0x18
 *  @note int1_fifo -> bit 2
 *  @note int2_fifo -> bit 5
 *
 *  @param v_axis_u8: The value of fifo interrupts selection
 *    v_axis_u8 | fifo interrupt
 *  ------------|--------------
 *      0       |   BMG160_INTR1
 *      1       |   BMG160_INTR2
 *
 *  @param v_intr_fifo_u8: the value of int1_fifo/int2_fifo enable/disable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_intr_fifo(u8 v_axis_u8,
        u8 v_intr_fifo_u8);
/***********************************************/
/**\name    HIGH RATE ENABLE */
/**********************************************/
/*!
 *  @brief This API is used to get
 *  the high rate(int2_high_rate) interrupt2 enable bits of
 *  the sensor in the registers 0x19 bit 3
 *
 *
 *
 *  @param v_intr2_highrate_u8 : The interrupt2 high_rate value
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_intr2_highrate(
    u8 *v_intr2_highrate_u8);
/*!
 *  @brief This API is used to set
 *  the high rate(int2_high_rate) interrupt2 enable bits of
 *  the sensor in the registers 0x19 bit 3
 *
 *
 *
 *  @param v_intr2_highrate_u8 : The interrupt2 high_rate value
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_intr2_highrate(
    u8 v_intr2_highrate_u8);
/***********************************************/
/**\name    ANY MOTION ENABLE */
/**********************************************/
/*!
 *  @brief This API is used to get
 *  the any motion(int2_any_motion) interrupt2 enable bits of
 *  the sensor in the registers 0x19 bit 1
 *
 *
 *
 *  @param v_intr2_any_motion_u8 : The value of interrupt2 any_motion
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_intr2_any_motion(
    u8 *v_intr2_any_motion_u8);
/*!
 *  @brief This API is used to set
 *  the any motion(int2_any_motion) interrupt2 enable bits of
 *  the sensor in the registers 0x19 bit 1
 *
 *
 *
 *  @param v_intr2_any_motion_u8 : The value of interrupt2 any_motion
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_intr2_any_motion(
    u8 v_intr2_any_motion_u8);
/***********************************************/
/**\name    OFFSET UNFILT ENABLE */
/**********************************************/
/*!
 *  @brief This API is used to get
 *  the slow offset and fast offset unfilt data in the register 0x1A and 1B
 *  @note slow_offset_unfilt -> 0x1A bit 5
 *  @note fast_offset_unfilt -> 0x1B bit 7
 *
 *  @param  v_param_u8: The value of fast/slow offset unfilt data selection
 *   v_param_u8 | offset selection
 *  ------------|--------------
 *      0       |   BMG160_SLOW_OFFSET
 *      1       |   BMG160_FAST_OFFSET
 *
 *  @param v_offset_unfilt_u8: The value of fast/slow offset unfilt data
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_offset_unfilt(u8 v_param_u8,
        u8 *v_offset_unfilt_u8);
/*!
 *  @brief This API is used to set
 *  the slow offset and fast offset unfilt data in the register 0x1A and 1B
 *  @note slow_offset_unfilt -> 0x1A bit 5
 *  @note fast_offset_unfilt -> 0x1B bit 7
 *
 *  @param  v_param_u8: The value of fast/slow offset unfilt data selection
 *   v_param_u8 | offset selection
 *  ------------|--------------
 *      0       |   BMG160_SLOW_OFFSET
 *      1       |   BMG160_FAST_OFFSET
 *
 *  @param v_offset_unfilt_u8: The value of fast/slow offset unfilt data
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_offset_unfilt(u8 v_param_u8,
        u8 v_offset_unfilt_u8);
/*!
 *  @brief This API is used to get
 *  the any motion  and high rate unfilt data in the register 0x1A
 *  @note any_unfilt_data -> bit 1
 *  @note high_unfilt_data -> bit 3
 *
 *  @param  v_param_u8: The value of any/high offset unfilt data selection
 *   v_param_u8 | offset selection
 *  ------------|--------------
 *      1       |   BMG160_HIGHRATE_UNFILT_DATA
 *      3       |   BMG160_ANY_MOTION_UNFILT_DATA
 *
 *  @param v_unfilt_data_u8: The value of any/high unfilt data
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_unfilt_data(u8 v_param_u8,
        u8 *v_unfilt_data_u8);
/*!
 *  @brief This API is used to set
 *  the any motion  and high rate unfilt data in the register 0x1A
 *  @note any_unfilt_data -> bit 1
 *  @note high_unfilt_data -> bit 3
 *
 *  @param  v_param_u8: The value of any/high offset unfilt data selection
 *   v_param_u8 | offset selection
 *  ------------|--------------
 *      1       |   BMG160_HIGHRATE_UNFILT_DATA
 *      3       |   BMG160_ANY_MOTION_UNFILT_DATA
 *
 *  @param v_unfilt_data_u8: The value of any/high unfilt data
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_unfilt_data(u8 v_param_u8,
        u8 v_unfilt_data_u8);
/***********************************************/
/**\name    ANY-MOTION CONFIGURATION  */
/**********************************************/
/*!
 *  @brief This API is used to get Any motion Threshold
 *  in the register 0x1B bit from 0 to 6
 *
 *
 *
 *  @param v_any_motion_thres_u8 : The value of any_motion Threshold
 *
 *  @note Any motion threshold can be calculate using
 *  @note ((1+ v_any_motion_thres_u8)*16LSB)
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_any_motion_thres(
    u8 *v_any_motion_thres_u8);
/*!
 *  @brief This API is used to set Any motion Threshold
 *  in the register 0x1B bit from 0 to 6
 *
 *
 *
 *  @param v_any_motion_thres_u8 : The value of any_motion Threshold
 *
 *  @note Any motion threshold can be calculate using
 *  @note ((1+ v_any_motion_thres_u8)*16LSB)
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_any_motion_thres(
    u8 v_any_motion_thres_u8);
/*!
 *  @brief This API is used to get the awake Duration
 *  in the register 0x1C bit 6 and 7
 *
 *
 *
 *  @param v_awake_durn_u8 : The value of awake Duration
 *  value   |  Duration
 * ---------|-----------
 *   0x00   | 8 samples
 *   0x01   | 16 samples
 *   0x02   | 32 samples
 *   0x03   | 64 samples
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_awake_durn(u8 *v_awake_durn_u8);
/*!
 *  @brief This API is used to set the awake Duration
 *  in the register 0x1C bit 6 and 7
 *
 *
 *
 *  @param v_awake_durn_u8 : The value of awake Duration
 *  value   |  Duration
 * ---------|-----------
 *   0x00   | 8 samples
 *   0x01   | 16 samples
 *   0x02   | 32 samples
 *   0x03   | 64 samples
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_awake_durn(u8 v_awake_durn_u8);
/*!
 *  @brief This API is used to get
 *  the any motion Duration samples in the register 0x1C bit 4 and 5
 *
 *
 *
 *  @param v_durn_sample_u8 : The value of any motion duration samples
 *  value   |  Samples
 * ---------|-----------
 *   0x00   | 4 samples
 *   0x01   | 8 samples
 *   0x02   | 12 samples
 *   0x03   | 16 samples
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_any_motion_durn_sample(
    u8 *v_durn_sample_u8);
/*!
 *  @brief This API is used to set
 *  the any motion Duration samples in the register 0x1C bit 4 and 5
 *
 *
 *
 *  @param v_durn_sample_u8 : The value of any motion duration samples
 *  value   |  Samples
 * ---------|-----------
 *   0x00   | 4 samples
 *   0x01   | 8 samples
 *   0x02   | 12 samples
 *   0x03   | 16 samples
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_any_motion_durn_sample(
    u8 v_durn_sample_u8);
/*!
 *  @brief This API is used to get the status of
 *  Any motion interrupt axis(X,Y,Z) enable channel
 *  @note BMG160_X_AXIS -> bit 0
 *  @note BMG160_Y_AXIS -> bit 1
 *  @note BMG160_Z_AXIS -> bit 2
 *
 *  @param v_channel_u8 : The value of Any Enable channel number
 *   v_channel_u8 | axis
 *  --------------|--------------
 *      0         | BMG160_X_AXIS
 *      1         | BMG160_Y_AXIS
 *      2         | BMG160_Z_AXIS
 *
 *  @param v_any_motion_axis_u8: The value of Any motion axis enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_any_motion_enable_axis(u8 v_channel_u8,
        u8 *v_any_motion_axis_u8);
/*!
 *  @brief This API is used to set the status of
 *  Any motion interrupt axis(X,Y,Z) enable channel
 *  @note BMG160_X_AXIS -> bit 0
 *  @note BMG160_Y_AXIS -> bit 1
 *  @note BMG160_Z_AXIS -> bit 2
 *
 *  @param v_channel_u8 : The value of Any Enable channel number
 *   v_channel_u8 | axis
 *  --------------|--------------
 *      0         | BMG160_X_AXIS
 *      1         | BMG160_Y_AXIS
 *      2         | BMG160_Z_AXIS
 *
 *  @param v_any_motion_axis_u8: The value of Any motion axis enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_any_motion_enable_axis(u8 v_channel_u8,
        u8 v_any_motion_axis_u8);
/***********************************************/
/**\name    FIFO CONFIGURATION  */
/**********************************************/
/*!
 *  @brief This API is used to get
 *  the status of fifo water mark in the register 0x1E bit 7
 *
 *
 *
 *  @param v_fifo_wm_enable_u8 : The value of fifo water mark enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_fifo_wm_enable(
    u8 *v_fifo_wm_enable_u8);
/*!
 *  @brief This API is used to set
 *  the status of fifo water mark in the register 0x1E bit 7
 *
 *
 *
 *  @param v_fifo_wm_enable_u8 : The value of fifo water mark enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_fifo_wm_enable(
    u8 v_fifo_wm_enable_u8);
/***********************************************/
/**\name    RESET INTERRUPT AND OFFSET CONFIGURATION  */
/**********************************************/
/*!
 *  @brief This API is used to set the Interrupt Reset
 *  in the register 0x21 bit 7
 *
 *
 *
 *  @param v_rst_int_u8: the value of reset interrupt
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
BMG160_RETURN_FUNCTION_TYPE bmg160_set_rst_intr(u8 v_rst_int_u8);
/*!
 *  @brief This API is used to set the offset Reset
 *  in the register 0x21 bit 6
 *
 *
 *
 *  @param v_offset_rst_u8: the value of reset offset
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
BMG160_RETURN_FUNCTION_TYPE bmg160_set_offset_rst(
    u8 v_offset_rst_u8);
/***********************************************/
/**\name    LATCH CONFIGURATION  */
/**********************************************/
/*!
 *  @brief This API is used to get the Latch Status
 *  in the register 0x21 bit 4
 *
 *
 *
 *  @param v_latch_stat_u8 : The value of latch status
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_latch_stat(
    u8 *v_latch_stat_u8);
/*!
 *  @brief This API is used to set the Latch Status
 *  in the register 0x21 bit 4
 *
 *
 *
 *  @param v_latch_stat_u8 : The value of latch status
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_latch_stat(
    u8 v_latch_stat_u8);
/*!
 *  @brief This API is used to get the Latch interrupt
 *  in the register 0x21 bit from 0 to 3
 *
 *
 *
 *  @param v_latch_intr_u8 : The value of latch interrupt
 *      Latch Interrupt        |  Value
 * ----------------------------|-----------------
 * BMG160_NON_LATCH            | 0x00
 * BMG160_LATCH_250_MS         | 0x01
 * BMG160_LATCH_500_MS         | 0x02
 * BMG160_LATCH_1_SEC          | 0x03
 * BMG160_LATCH_2_SEC          | 0x04
 * BMG160_LATCH_4_SEC          | 0x05
 * BMG160_LATCH_8_SEC          | 0x06
 * BMG160_LATCH_LATCHED        | 0x07
 * BMG160_LATCH_NON_LATCHED    | 0x08
 * BMG160_LATCH_250_MICRO_SEC  | 0x09
 * BMG160_LATCH_500_MICRO_SEC  | 0x0A
 * BMG160_LATCH_1_MILLI_SEC    | 0x0B
 * BMG160_LATCH_12.5_MILLI_SEC | 0x0C
 * BMG160_LATCH_25_MILLI_SEC   | 0x0D
 * BMG160_LATCH_50_MILLI_SEC   | 0x0E
 * BMG160_LATCH_LATCHED        | 0x0F
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_latch_intr(u8 *v_latch_intr_u8);
/*!
 *  @brief This API is used to set the Latch interrupt
 *  in the register 0x21 bit from 0 to 3
 *
 *
 *
 *  @param v_latch_intr_u8 : The value of latch interrupt
 *      Latch Interrupt        |  Value
 * ----------------------------|-----------------
 * BMG160_NON_LATCH            | 0x00
 * BMG160_LATCH_250_MS         | 0x01
 * BMG160_LATCH_500_MS         | 0x02
 * BMG160_LATCH_1_SEC          | 0x03
 * BMG160_LATCH_2_SEC          | 0x04
 * BMG160_LATCH_4_SEC          | 0x05
 * BMG160_LATCH_8_SEC          | 0x06
 * BMG160_LATCH_LATCHED        | 0x07
 * BMG160_LATCH_NON_LATCHED    | 0x08
 * BMG160_LATCH_250_MICRO_SEC  | 0x09
 * BMG160_LATCH_500_MICRO_SEC  | 0x0A
 * BMG160_LATCH_1_MILLI_SEC    | 0x0B
 * BMG160_LATCH_12.5_MILLI_SEC | 0x0C
 * BMG160_LATCH_25_MILLI_SEC   | 0x0D
 * BMG160_LATCH_50_MILLI_SEC   | 0x0E
 * BMG160_LATCH_LATCHED        | 0x0F
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_latch_intr(u8 v_latch_intr_u8);
/***********************************************/
/**\name    HIGH RATE CONFIGURATION  */
/**********************************************/
/*!
 *  @brief This API is used to get the status of High
 *  Hysteresis of X,Y,Z axis in the registers 0x22,0x24 and 0x26
 *  @note X_AXIS - 0x22 bit 6 and 7
 *  @note Y_AXIS - 0x24 bit 6 and 7
 *  @note Z_AXIS - 0x26 bit 6 and 7
 *
 *  @param v_channel_u8: The value of high Hysteresis channel number
 *  v_channel_u8  |    value
 *  --------------|--------------
 *  BMG160_X_AXIS |   0
 *  BMG160_Y_AXIS |   1
 *  BMG160_Z_AXIS |   2
 *
 *  @param v_highrate_hyst_u8: The value of high Hysteresis
 *
 *  @note High hysteresis can be calculated by
 *  @note High_hyst = ((255+256 *v_highrate_hyst_u8) * 4LSB)
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_highrate_hyst(u8 v_channel_u8,
        u8 *v_highrate_hyst_u8);
/*!
 *  @brief This API is used to set the status of High
 *  Hysteresis of X,Y,Z axis in the registers 0x22,0x24 and 0x26
 *  @note X_AXIS - 0x22 bit 6 and 7
 *  @note Y_AXIS - 0x24 bit 6 and 7
 *  @note Z_AXIS - 0x26 bit 6 and 7
 *
 *  @param v_channel_u8: The value of high Hysteresis channel number
 *  v_channel_u8  |    value
 *  --------------|--------------
 *  BMG160_X_AXIS |   0
 *  BMG160_Y_AXIS |   1
 *  BMG160_Z_AXIS |   2
 *
 *  @param v_highrate_hyst_u8: The value of high Hysteresis
 *
 *  @note High hysteresis can be calculated by
 *  @note High_hyst = ((255+256 *v_highrate_hyst_u8) * 4LSB)
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_highrate_hyst(u8 v_channel_u8,
        u8 v_highrate_hyst_u8);
/*!
 *  @brief This API is used to get the value of High rate
 *  Threshold of X,Y,Z axis in the registers 0x22, 0x24 and 0x26
 *  @note X_AXIS - 0x22 bit from 1 to 5
 *  @note Y_AXIS - 0x24 bit from 1 to 5
 *  @note Z_AXIS - 0x26 bit from 1 to 5
 *
 *  @param  v_channel_u8 : The value of high threshold channel number
 *  v_channel_u8  |    value
 *  --------------|--------------
 *  BMG160_X_AXIS |   0
 *  BMG160_Y_AXIS |   1
 *  BMG160_Z_AXIS |   2
 *
 *  @param v_highrate_thres_u8: the high threshold value
 *
 *  @note High Threshold can be calculated by
 *  @note High_thres = ((255+256 *v_highrate_thres_u8) * 4LSB)
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_highrate_thres(u8 v_channel_u8,
        u8 *v_highrate_thres_u8);
/*!
 *  @brief This API is used to set the value of High rate
 *  Threshold of X,Y,Z axis in the registers 0x22, 0x24 and 0x26
 *  @note X_AXIS - 0x22 bit from 1 to 5
 *  @note Y_AXIS - 0x24 bit from 1 to 5
 *  @note Z_AXIS - 0x26 bit from 1 to 5
 *
 *  @param  v_channel_u8 : The value of high threshold channel number
 *  v_channel_u8  |    value
 *  --------------|--------------
 *  BMG160_X_AXIS |   0
 *  BMG160_Y_AXIS |   1
 *  BMG160_Z_AXIS |   2
 *
 *  @param v_highrate_thres_u8: the high threshold value
 *
 *  @note High Threshold can be calculated by
 *  @note High_thres = ((255+256 *v_highrate_thres_u8) * 4LSB)
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_highrate_thres(u8 v_channel_u8,
        u8 v_highrate_thres_u8);
/*!
 * @brief This API is used to get the status of High Enable
 * Channel X,Y,Z in the registers 0x22, 0x24 and 0x26
 *  @note X_AXIS - 0x22 bit 0
 *  @note Y_AXIS - 0x24 bit 0
 *  @note Z_AXIS - 0x26 bit 0
 *
 *  @param v_channel_u8 : The value of high enable channel number
 *  v_channel_u8  |    value
 *  --------------|--------------
 *  BMG160_X_AXIS |   0
 *  BMG160_Y_AXIS |   1
 *  BMG160_Z_AXIS |   2
 *
 *  @param v_enable_u8: The value of high axis enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_highrate_enable_axis(u8 v_channel_u8,
        u8 *v_enable_u8);
/*!
 * @brief This API is used to set the status of High Enable
 * Channel X,Y,Z in the registers 0x22, 0x24 and 0x26
 *  @note X_AXIS - 0x22 bit 0
 *  @note Y_AXIS - 0x24 bit 0
 *  @note Z_AXIS - 0x26 bit 0
 *
 *  @param v_channel_u8 : The value of high enable channel number
 *  v_channel_u8  |    value
 *  --------------|--------------
 *  BMG160_X_AXIS |   0
 *  BMG160_Y_AXIS |   1
 *  BMG160_Z_AXIS |   2
 *
 *  @param v_enable_u8: The value of high axis enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_highrate_enable_axis(u8 v_channel_u8,
        u8 v_enable_u8);
/*!
 * @brief This API is used to get the status
 * of High duration of X,Y,Z axis in
 * the registers 0x23, 0x25 and 0x27
 *  @note X_AXIS - 0x23 bit form 0 to 7
 *  @note Y_AXIS - 0x25 bit form 0 to 7
 *  @note Z_AXIS - 0x27 bit form 0 to 7
 *
 *
 *
 *  @param  v_channel_u8: The value of High Duration channel number
 *  v_channel_u8  |    value
 *  --------------|--------------
 *  BMG160_X_AXIS |   0
 *  BMG160_Y_AXIS |   1
 *  BMG160_Z_AXIS |   2
 *
 *  @param v_highrate_durn_axis_u8: The value of high duration
 *
 *  @note High rate duration can be calculated by using the formula
 *  @note High_durn = ((1+v_highrate_durn_axis_u8)*2.5ms)
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_highrate_durn_axis(u8 v_channel_u8,
        u8 *v_highrate_durn_axis_u8);
/*!
 * @brief This API is used to set the value
 * of High duration of X,Y,Z axis in
 * the registers 0x23, 0x25 and 0x27
 *  @note X_AXIS - 0x23 bit form 0 to 7
 *  @note Y_AXIS - 0x25 bit form 0 to 7
 *  @note Z_AXIS - 0x27 bit form 0 to 7
 *
 *
 *
 *  @param  v_channel_u8: The value of High Duration channel number
 *  v_channel_u8  |    value
 *  --------------|--------------
 *  BMG160_X_AXIS |   0
 *  BMG160_Y_AXIS |   1
 *  BMG160_Z_AXIS |   2
 *
 *  @param v_highrate_durn_axis_u8: The value of high duration
 *
 *  @note High rate duration can be calculated by using the formula
 *  @note High_durn = ((1+v_highrate_durn_axis_u8)*2.5ms)
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_highrate_durn_axis(u8 v_channel_u8,
        u8 v_highrate_durn_axis_u8);
/***********************************************/
/**\name    SLOW OFFSET CONFIGURATION  */
/**********************************************/
/*!
 *  @brief This API is used to get Slow Offset Threshold
 *  status in the register 0x31 bit 6 and 7
 *
 *
 *
 *  @param v_offset_thres_u8 : The value of slow offset Threshold
 *  value    |   threshold
 * ----------|-------------
 *    0x00   | 0.1 degree/sec
 *    0x01   | 0.2 degree/sec
 *    0x02   | 0.5 degree/sec
 *    0x03   | 1 degree/sec
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_slow_offset_thres(
    u8 *v_offset_thres_u8);
/*!
 *  @brief This API is used to set Slow Offset Threshold
 *  status in the register 0x31 bit 6 and 7
 *
 *
 *
 *  @param v_offset_thres_u8 : The value of slow offset Threshold
 *  value    |   threshold
 * ----------|-------------
 *    0x00   | 0.1 degree/sec
 *    0x01   | 0.2 degree/sec
 *    0x02   | 0.5 degree/sec
 *    0x03   | 1 degree/sec
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_slow_offset_thres(u8 v_offset_thres_u8);
/*!
 *  @brief This API is used to get Slow Offset duration
 *  status in the register 0x31 bit 4,5 and 6
 *
 *
 *
 *  @param v_offset_durn_u8 : The value of Slow Offset duration
 *   value    |  Duration
 * -----------|-----------
 *    0x00    | 40ms
 *    0x01    | 80ms
 *    0x02    | 160ms
 *    0x03    | 320ms
 *    0x04    | 640ms
 *    0x05    | 1280ms
 *    0x06    | unused
 *    0x07    | unused
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_slow_offset_durn(
    u8 *v_offset_durn_u8);
/*!
 *  @brief This API is used to set Slow Offset duration
 *  status in the register 0x31 bit 4,5 and 6
 *
 *
 *
 *  @param v_offset_durn_u8 : The value of Slow Offset duration
 *   value    |  Duration
 * -----------|-----------
 *    0x00    | 40ms
 *    0x01    | 80ms
 *    0x02    | 160ms
 *    0x03    | 320ms
 *    0x04    | 640ms
 *    0x05    | 1280ms
 *    0x06    | unused
 *    0x07    | unused
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_slow_offset_durn(
    u8 v_offset_durn_u8);
/*!
 *  @brief This API is used to get Slow Offset Enable channel
 *  X,Y,Z in the register 0x31
 *  @note X_AXIS -> bit 0
 *  @note Y_AXIS -> bit 1
 *  @note Z_AXIS -> bit 2
 *
 *
 *  @param v_channel_u8: The value of slow offset channel number
 *  v_channel_u8  |    value
 *  --------------|--------------
 *  BMG160_X_AXIS |   0
 *  BMG160_Y_AXIS |   1
 *  BMG160_Z_AXIS |   2
 *
 *  @param v_slow_offset_u8: The slow offset value
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_slow_offset_enable_axis(
    u8 v_channel_u8, u8 *v_slow_offset_u8);
/*!
 *  @brief This API is used to set Slow Offset Enable channel
 *  X,Y,Z in the register 0x31
 *  @note X_AXIS -> bit 0
 *  @note Y_AXIS -> bit 1
 *  @note Z_AXIS -> bit 2
 *
 *
 *  @param v_channel_u8: The value of slow offset channel number
 *  v_channel_u8  |    value
 *  --------------|--------------
 *  BMG160_X_AXIS |   0
 *  BMG160_Y_AXIS |   1
 *  BMG160_Z_AXIS |   2
 *
 *  @param v_slow_offset_u8: The slow offset value
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_slow_offset_enable_axis(
    u8 v_channel_u8, u8 v_slow_offset_u8);
/*!
 *  @brief This API is used to get
 *  Fast Offset WordLength and Auto Offset WordLength in the register 0x32
 *  @note fast_offset_wordlength -> bit 4 and 5
 *  @note auto_offset_wordlength -> bit 6 and 7
 *
 *
 *  @param v_channel_u8: The value of WordLengthchannel number
 *  v_channel_u8          |    value
 *  ----------------------|--------------
 *  BMG160_AUTO_OFFSET_WL |   0
 *  BMG160_FAST_OFFSET_WL |   1
 *
 *  @param  v_offset_word_length_u8: The value of offset word length
 *   value    |  word length
 *  ----------|--------------
 *    0x00    | 32 samples
 *    0x01    | 64 samples
 *    0x02    | 128 samples
 *    0x03    | 256 samples
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_offset_word_length(u8 v_channel_u8,
        u8 *v_offset_word_length_u8);
/*!
 *  @brief This API is used to set
 *  Fast Offset WordLength and Auto Offset WordLength in the register 0x32
 *  @note fast_offset_wordlength -> bit 4 and 5
 *  @note auto_offset_wordlength -> bit 6 and 7
 *
 *
 *  @param v_channel_u8: The value of WordLengthchannel number
 *  v_channel_u8          |    value
 *  ----------------------|--------------
 *  BMG160_AUTO_OFFSET_WL |   0
 *  BMG160_FAST_OFFSET_WL |   1
 *
 *  @param  v_offset_word_length_u8: The value of offset word length
 *   value    |  word length
 *  ----------|--------------
 *    0x00    | 32 samples
 *    0x01    | 64 samples
 *    0x02    | 128 samples
 *    0x03    | 256 samples
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_offset_word_length(
    u8 v_channel_u8, u8 v_offset_word_length_u8);
/***********************************************/
/**\name    OFFSET CONFIGURATION  */
/**********************************************/
/*!
 *  @brief This API is used to enable fast offset
 *  in the register 0x32 bit 3 it is a write only register
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_enable_fast_offset(void);
/*!
 *  @brief This API read the Fast offset enable
 *  v_axis_u8(X,Y and Z) in the register 0x32
 *  @note X_AXIS -> bit 0
 *  @note Y_AXIS -> bit 1
 *  @note Z_AXIS -> bit 2
 *
 *
 *
 *  @param v_fast_offset_u8: The value of fast offset enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_fast_offset_enable_axis(
    u8 *v_fast_offset_u8);
/*!
 *  @brief This API set the Fast offset enable
 *  v_axis_u8(X,Y and Z) in the register 0x32
 *  @note X_AXIS -> bit 0
 *  @note Y_AXIS -> bit 1
 *  @note Z_AXIS -> bit 2
 *
 *
 *  @param v_channel_u8: The value of fast offset channel select
 *  v_channel_u8    |    value
 *  ----------------|--------------
 *  BMG160_X_AXIS   |   0
 *  BMG160_Y_AXIS   |   1
 *  BMG160_Z_AXIS   |   2
 *
 *  @param v_fast_offset_u8: The value of fast offset enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_fast_offset_enable_axis(
    u8 v_channel_u8, u8 v_fast_offset_u8);
/***********************************************/
/**\name    NVM CONFIGURATION  */
/**********************************************/
/*!
 *  @brief This API is used to get the status of nvm program
 *  remain in the register 0x33 bit from 4 to 7
 *
 *
 *  @param v_nvm_remain_u8: The value of nvm program
 *   value    |  Description
 * -----------|---------------
 *    1       |  Do not trigger
 *    0       |  Trigger
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_nvm_remain(u8 *v_nvm_remain_u8);
/*!
 *  @brief This API is used to set the status of nvm program
 *  remain in the register 0x33 bit from 4 to 7
 *
 *
 *  @param v_nvm_load_u8: The value of nvm program
 *   value    |  Description
 * -----------|---------------
 *    1       |  Do not trigger
 *    0       |  Trigger
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_nvm_load(u8 v_nvm_load_u8);
/*!
 *  @brief This API is used to get the status of nvm
 *  program in the register 0x33 bit 2
 *
 *  @param v_nvm_rdy_u8: The value of nvm program
 *   value    |  Description
 * -----------|---------------
 *    1       |  NVM write is in progress
 *    0       |  NVM is ready to accept a new write
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_nvm_rdy(u8 *v_nvm_rdy_u8);
/*!
 *  @brief This API is used to set the status of nvm
 *  ready in the register 0x33 bit 1
 *
 *  @param nvm_prog_trig: The value of nvm program
 *   value    |  Description
 * -----------|---------------
 *    1       |  program seq in progress
 *    0       |  program seq finished
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_nvm_prog_trig(u8 nvm_prog_trig);
/*!
 *  @brief This API is used to get
 *  the status of nvm program mode in the register 0x33 bit 0
 *
 *
 *  @param nvm_prog_mode: The value of nvm program mode
 *   value    |  Description
 * -----------|---------------
 *    1       |  Unlock
 *    0       |  Lock nvm write
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_nvm_prog_mode(u8 *nvm_prog_mode);
/*!
 *  @brief This API is used to set
 *  the status of nvm program mode in the register 0x33 bit 0
 *
 *
 *  @param nvm_prog_mode: The value of nvm program mode
 *   value    |  Description
 * -----------|---------------
 *    1       |  Unlock
 *    0       |  Lock nvm write
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_nvm_prog_mode(u8 nvm_prog_mode);
/***********************************************/
/**\name    I2C CONFIGURATION  */
/**********************************************/
/*!
 *  @brief This API is used to get
 *  the status of i2c wdt select and enable in the register 0x34
 *  @note i2c_wdt_select -> bit 1
 *  @note i2c_wdt_enable -> bit 2
 *
 *  @param v_channel_u8: The value of i2c wdt channel number
 *  v_channel_u8            |    value
 *  ------------------------|--------------
 *  BMG160_I2C_WDT_ENABLE   |   1
 *  BMG160_I2C_WDT_SELECT   |   0
 *
 *  @param v_i2c_wdt_u8: The value of I2C enable and WDT select
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_i2c_wdt(u8 v_channel_u8,
        u8 *v_i2c_wdt_u8);
/*!
 *  @brief This API is used to set
 *  the status of i2c wdt select and enable in the register 0x34
 *  @note i2c_wdt_select -> bit 1
 *  @note i2c_wdt_enable -> bit 2
 *
 *  @param v_channel_u8: The value of i2c wdt channel number
 *  v_channel_u8            |    value
 *  ------------------------|--------------
 *  BMG160_I2C_WDT_ENABLE   |   1
 *  BMG160_I2C_WDT_SELECT   |   0
 *
 *  @param v_i2c_wdt_u8: The value of I2C enable and WDT select
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_i2c_wdt(u8 v_channel_u8,
        u8 v_i2c_wdt_u8);
/***********************************************/
/**\name    SPI CONFIGURATION  */
/**********************************************/
/*!
 *  @brief  This API is used to get the status of spi3
 *  in the register 0x34 bit 0
 *
 *
 *
 *  @param  v_spi3_u8 : The value of spi3 enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_spi3(u8 *v_spi3_u8);
/*!
 *  @brief  This API is used to set the status of spi3
 *  in the register 0x34 bit 0
 *
 *
 *
 *  @param  v_spi3_u8 : The value of spi3 enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_spi3(u8 v_spi3_u8);
/***********************************************/
/**\name    FIFO CONFIGURATION  */
/**********************************************/
/*!
 *  @brief  This API is used to get the status of FIFO tag
 *  in the register 0x3D bit 7
 *
 *
 *
 *  @param  v_fifo_tag_u8 : The value of fifo tag enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_fifo_tag(u8 *v_fifo_tag_u8);
/*!
 *  @brief  This API is used to set the status of FIFO tag
 *  in the register 0x3D bit 7
 *
 *
 *
 *  @param  v_fifo_tag_u8 : The value of fifo tag enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_fifo_tag(u8 v_fifo_tag_u8);
/*!
 *  @brief This API is used to get Water Mark Level
 *  in the register 0x3D bit from 0 to 6
 *
 *
 *
 *  @param v_fifo_wm_level_u8 : The value of fifo water mark level
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_fifo_wm_level(
    u8 *v_fifo_wm_level_u8);
/*!
 *  @brief This API is used to set Water Mark Level
 *  in the register 0x3D bit from 0 to 6
 *
 *
 *
 *  @param v_fifo_wm_level_u8 : The value of fifo water mark level
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_fifo_wm_level(
    u8 v_fifo_wm_level_u8);
/***********************************************/
/**\name    OFFSET FUNCTIONS */
/**********************************************/
/*!
 *  @brief This API is used to get the value of offset
 *  X, Y and Z in the registers 0x36, 0x37, 0x38, 0x39 and 0x3A
 *  the offset is a 12bit value
 *  @note X_AXIS ->
 *      @note bit 0 and 1 is available in the register 0x3A bit 2 and 3
 *      @note bit 2 and 3 is available in the register 0x36 bit 6 and 7
 *      @note bit 4 to 11 is available in the register 0x37 bit 0 to 7
 *  @note Y_AXIS ->
 *      @note bit 0 is available in the register 0x3A bit 1
 *      @note bit 1,2 and 3 is available in the register 0x36 bit 3,4 and 5
 *      @note bit 4 to 11 is available in the register 0x38 bit 0 to 7
 *  @note Z_AXIS ->
 *      @note bit 0 is available in the register 0x3A bit 0
 *      @note bit 1,2 and 3 is available in the register 0x36 bit 0,1 and 3
 *      @note bit 4 to 11 is available in the register 0x39 bit 0 to 7
 *
 *  @param  v_axis_u8 : The value of offset axis selection
 *  v_axis_u8       |    value
 *  ----------------|--------------
 *  BMG160_X_AXIS   |   1
 *  BMG160_Y_AXIS   |   0
 *  BMG160_Z_AXIS   |   0
 *
 *  @param v_offset_s16: The value of offset
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_offset(u8 v_axis_u8,
        s16 *v_offset_s16);
/*!
 *  @brief This API is used to set the value of offset
 *  X, Y and Z in the registers 0x36, 0x37, 0x38, 0x39 and 0x3A
 *  the offset is a 12bit value
 *  @note X_AXIS ->
 *      @note bit 0 and 1 is available in the register 0x3A bit 2 and 3
 *      @note bit 2 and 3 is available in the register 0x36 bit 6 and 7
 *      @note bit 4 to 11 is available in the register 0x37 bit 0 to 7
 *  @note Y_AXIS ->
 *      @note bit 0 is available in the register 0x3A bit 1
 *      @note bit 1,2 and 3 is available in the register 0x36 bit 3,4 and 5
 *      @note bit 4 to 11 is available in the register 0x38 bit 0 to 7
 *  @note Z_AXIS ->
 *      @note bit 0 is available in the register 0x3A bit 0
 *      @note bit 1,2 and 3 is available in the register 0x36 bit 0,1 and 3
 *      @note bit 4 to 11 is available in the register 0x39 bit 0 to 7
 *
 *  @param  v_axis_u8 : The value of offset axis selection
 *  v_axis_u8       |    value
 *  ----------------|--------------
 *  BMG160_X_AXIS   |   1
 *  BMG160_Y_AXIS   |   0
 *  BMG160_Z_AXIS   |   0
 *
 *  @param v_offset_s16: The value of offset
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_offset(
    u8 v_axis_u8, s16 v_offset_s16);
/*!
 *  @brief This API is used to get the status of general
 *  purpose register in the register 0x3A and 0x3B
 *
 *
 *
 *
 *  @param v_param_u8: The value of general purpose register select
 *  v_param_u8      |    value
 *  ----------------|--------------
 *  BMG160_GP0      |  0
 *  BMG160_GP1      |  1
 *
 *  @param v_gp_u8: The value of general purpose register
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_gp(u8 v_param_u8,
        u8 *v_gp_u8);
/*!
 *  @brief This API is used to set the status of general
 *  purpose register in the register 0x3A and 0x3B
 *
 *
 *
 *
 *  @param v_param_u8: The value of general purpose register select
 *  v_param_u8      |    value
 *  ----------------|--------------
 *  BMG160_GP0      |  0
 *  BMG160_GP1      |  1
 *
 *  @param v_gp_u8: The value of general purpose register
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_gp(u8 v_param_u8,
        u8 v_gp_u8);
/***********************************************/
/**\name    FIFO READ AND CONFIGURATION  */
/**********************************************/
/*!
 * @brief Reads FIFO data from location 0x3F
 *
 *
 *
 *
 *  @param v_fifo_data_u8 : The data of fifo
 *
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error result of communication routines
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_FIFO_data_reg(u8 *v_fifo_data_u8);
/*!
 *  @brief this api is used to read the fifo status
 *  of frame_counter and overrun in the register 0x0E
 *  @note frame_counter > bit from 0 to 6
 *  @note overrun -> bit 7
 *
 *
 *
 *  @param v_fifo_stat_u8 : The value of fifo overrun and fifo counter
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_fifo_stat_reg(
    u8 *v_fifo_stat_u8);
/*!
 *  @brief this API is used to get the fifo frame counter
 *  in the register 0x0E bit 0 to 6
 *
 *
 *
 *  @param v_fifo_frame_count_u8: The value of fifo frame counter
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_fifo_frame_count(
    u8 *v_fifo_frame_count_u8);
/*!
 *  @brief this API is used to get the fifo over run
 *  in the register 0x0E bit 7
 *
 *
 *
 *  @param v_fifo_overrun_u8: The value of fifo over run
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_fifo_overrun(
    u8 *v_fifo_overrun_u8);
/*!
 *  @brief This API is used to get the status of fifo mode
 *  in the register 0x3E bit 6 and 7
 *
 *
 *
 *  @param v_fifo_mode_u8 : The value of fifo mode
 *        mode      |    value
 *  ----------------|--------------
 *      BYPASS      |  0
 *      FIFO        |  1
 *      STREAM      |  2
 *      RESERVED    |  3
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_fifo_mode(u8 *v_fifo_mode_u8);
/*!
 *  @brief This API is used to set the status of fifo mode
 *  in the register 0x3E bit 6 and 7
 *
 *
 *
 *  @param v_fifo_mode_u8 : The value of fifo mode
 *        mode      |    value
 *  ----------------|--------------
 *      BYPASS      |  0
 *      FIFO        |  1
 *      STREAM      |  2
 *      RESERVED    |  3
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_fifo_mode(u8 v_fifo_mode_u8);
/*!
 *  @brief This API is used to get the status of fifo
 *  data select in the register 0x3E bit 0 and 1
 *
 *
 *  @param v_fifo_data_select_u8 : The value of fifo data selection
 *      data selection         |    value
 *  ---------------------------|--------------
 *      X,Y and Z (DEFAULT)    |  0
 *      X only                 |  1
 *      Y only                 |  2
 *      Z only                 |  3
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_fifo_data_select(
    u8 *v_fifo_data_select_u8);
/*!
 *  @brief This API is used to set the status of fifo
 *  data select in the register 0x3E bit 0 and 1
 *
 *
 *  @param v_fifo_data_select_u8 : The value of fifo data selection
 *      data selection         |    value
 *  ---------------------------|--------------
 *      X,Y and Z (DEFAULT)    |  0
 *      X only                 |  1
 *      Y only                 |  2
 *      Z only                 |  3
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_fifo_data_select(
    u8 v_fifo_data_select_u8);
/***********************************************/
/**\name    POWER MODE CONFIGURATION  */
/**********************************************/
/*!
 *  @brief This API is used to get the operating modes of the
 *  sensor in the registers 0x11 and 0x12
 *
 *
 *
 *  @param  v_power_mode_u8 :The value of power mode
 *  value     |   power mode
 * -----------|----------------
 *     0      | BMG160_MODE_NORMAL
 *     1      | BMG160_MODE_SUSPEND
 *     2      | BMG160_MODE_DEEPSUSPEND
 *     3      | BMG160_MODE_FASTPOWERUP
 *     4      | BMG160_MODE_ADVANCEDPOWERSAVING
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_power_mode(u8 *v_power_mode_u8);
/*!
 *  @brief This API is used to set the operating modes of the
 *  sensor in the registers 0x11 and 0x12
 *
 *
 *
 *  @param  v_power_mode_u8 :The value of power mode
 *  value     |   power mode
 * -----------|----------------
 *     0      | BMG160_MODE_NORMAL
 *     1      | BMG160_MODE_SUSPEND
 *     2      | BMG160_MODE_DEEPSUSPEND
 *     3      | BMG160_MODE_FASTPOWERUP
 *     4      | BMG160_MODE_ADVANCEDPOWERSAVING
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_power_mode(u8 v_power_mode_u8);
/***********************************************/
/**\name    SELF TEST CONFIGURATION  */
/**********************************************/
/*!
 *  @brief This API is used to to do selftest to sensor
 *  sensor in the register 0x3C
 *
 *
 *
 *
 *  @param v_result_u8: The value of self test
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
BMG160_RETURN_FUNCTION_TYPE bmg160_selftest(u8 *v_result_u8);
/***********************************************/
/**\name    SLEEP AND AUTO SLEEP CONFIGURATION  */
/**********************************************/
/*!
 *  @brief  This API is used to get the auto sleep duration
 *  in the register 0x12 bit 0 to 2
 *
 *
 *
 *  @param v_durn_u8 : The value of gyro auto sleep duration
 *           sleep duration     |   value
 *  ----------------------------|----------
 *               not allowed    |   0
 *               4ms            |   1
 *               5ms            |   2
 *               8ms            |   3
 *               10ms           |   4
 *               15ms           |   5
 *               20ms           |   6
 *               40ms           |   7
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_auto_sleep_durn(u8 *v_durn_u8);
/*!
 *  @brief  This API is used to set the auto sleep duration
 *  in the register 0x12 bit 0 to 2
 *
 *
 *
 *  @param v_durn_u8 : The value of gyro auto sleep duration
 *           sleep duration     |   value
 *  ----------------------------|----------
 *               not allowed    |   0
 *               4ms            |   1
 *               5ms            |   2
 *               8ms            |   3
 *               10ms           |   4
 *               15ms           |   5
 *               20ms           |   6
 *               40ms           |   7
 *
 *  @param v_bw_u8 : The value of selected bandwidth
 *        v_bw_u8               |   value
 *  ----------------------------|----------
 *  C_BMG160_NO_FILTER_U8X      |   0
 *  C_BMG160_BW_230HZ_U8X       |   1
 *  C_BMG160_BW_116HZ_u8X       |   2
 *  C_BMG160_BW_47HZ_u8X        |   3
 *  C_BMG160_BW_23HZ_u8X        |   4
 *  C_BMG160_BW_12HZ_u8X        |   5
 *  C_BMG160_BW_64HZ_u8X        |   6
 *  C_BMG160_BW_32HZ_u8X        |   7
 *
 *  @note: sleep duration depends on selected power mode and bandwidth
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_auto_sleep_durn(u8 v_durn_u8,
        u8 v_bw_u8);
/*!
 *  @brief  This API is used to get the sleep duration
 *  in the register 0x11 bit 1 to 3
 *
 *
 *
 *  @param v_durn_u8 : The value of sleep duration
 *           sleep duration     |   value
 *  ----------------------------|----------
 *               2ms            |   0
 *               4ms            |   1
 *               5ms            |   2
 *               8ms            |   3
 *               10ms           |   4
 *               15ms           |   5
 *               18ms           |   6
 *               20ms           |   7
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_sleep_durn(u8 *v_durn_u8);
/*!
 *  @brief  This API is used to set the sleep duration
 *  in the register 0x11 bit 1 to 3
 *
 *
 *
 *  @param v_durn_u8 : The value of sleep duration
 *           sleep duration     |   value
 *  ----------------------------|----------
 *               2ms            |   0
 *               4ms            |   1
 *               5ms            |   2
 *               8ms            |   3
 *               10ms           |   4
 *               15ms           |   5
 *               18ms           |   6
 *               20ms           |   7
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_sleep_durn(u8 v_durn_u8);
#endif
