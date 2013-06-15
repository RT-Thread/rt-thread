/** @file I2C.h
*   @brief I2C Driver Definition File
*   @date 29.May.2013
*   @version 03.05.02
*   
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef __I2C_H__
#define __I2C_H__

#include "reg_i2c.h"



/** @enum i2cMode
*   @brief Alias names for i2c modes
*   This enumeration is used to provide alias names for I2C modes:
*/

enum i2cMode
{
    I2C_FD_FORMAT   = 0x0008U,  /* Free Data Format    */
    I2C_START_BYTE  = 0x0010U,
    I2C_RESET_OUT   = 0x0020U,  I2C_RESET_IN   = 0x0000U,
    I2C_DLOOPBACK   = 0x0040U,    
    I2C_REPEATMODE  = 0x0080U,  /* In Master Mode only */ 
    I2C_10BIT_AMODE = 0x0100U,  I2C_7BIT_AMODE = 0x0000U,
    I2C_TRANSMITTER = 0x0200U,  I2C_RECEIVER   = 0x0000U,        
    I2C_MASTER      = 0x0400U,  I2C_SLAVE      = 0x0000U,     
    I2C_STOP_COND   = 0x0800U,  /* In Master Mode only */
    I2C_START_COND  = 0x2000U,  /* In Master Mode only */    
    I2C_FREE_RUN    = 0x4000U,
    I2C_NACK_MODE   = 0x8000U
};


/** @enum i2cBitCount
*   @brief Alias names for i2c bit count
*   This enumeration is used to provide alias names for I2C bit count:
*/

enum i2cBitCount
{
    I2C_2_BIT   = 0x2U, 
    I2C_3_BIT   = 0x3U, 
    I2C_4_BIT   = 0x4U, 
    I2C_5_BIT   = 0x5U, 
    I2C_6_BIT   = 0x6U, 
    I2C_7_BIT   = 0x7U,     
    I2C_8_BIT   = 0x0U  
};



/** @enum i2cIntFlags
*   @brief Interrupt Flag Definitions
*
*   Used with I2CEnableNotification, I2CDisableNotification
*/
enum i2cIntFlags
{
    I2C_AL_INT     = 0x0001U,  /* arbitration lost      */
    I2C_NACK_INT   = 0x0002U,  /* no acknowledgment    */
    I2C_ARDY_INT   = 0x0004U,  /* access ready          */
    I2C_RX_INT     = 0x0008U,  /* receive data ready    */
    I2C_TX_INT     = 0x0010U,  /* transmit data ready   */
    I2C_SCD_INT    = 0x0020U,  /* stop condition detect */
    I2C_AAS_INT    = 0x0040U   /* address as slave      */
};


/** @enum i2cStatFlags
*   @brief Interrupt Status Definitions
*
*/
enum i2cStatFlags
{
    I2C_AL         = 0x0001U,  /* arbitration lost          */
    I2C_NACK       = 0x0002U,  /* no acknowledgement        */
    I2C_ARDY       = 0x0004U,  /* access ready              */
    I2C_RX         = 0x0008U,  /* receive data ready        */
    I2C_TX         = 0x0010U,  /* transmit data ready       */
    I2C_SCD        = 0x0020U,  /* stop condition detect     */
    I2C_AD0        = 0x0100U,  /* address Zero Status       */
    I2C_AAS        = 0x0200U,  /* address as slave          */
    I2C_XSMT       = 0x0400U,  /* Transmit shift empty not  */	
    I2C_RXFULL     = 0x0800U,  /* receive full              */
    I2C_BUSBUSY    = 0x1000U,  /* bus busy                  */
    I2C_NACKSNT    = 0x2000U,  /* No Ack Sent               */
    I2C_SDIR       = 0x4000U   /* Slave Direction           */	
};


/** @enum i2cDMA
*   @brief I2C DMA definitions 
*
*   Used before i2c transfer
*/
enum i2cDMA
{
    I2C_TXDMA   = 0x20U, 
    I2C_RXDMA   = 0x10U 
};

/** 
 *  @defgroup I2C I2C
 *  @brief Inter-Integrated Circuit Module.
 *  
 *  The I2C is a multi-master communication module providing an interface between the Texas Instruments (TI) microcontroller
 *  and devices compliant with Philips Semiconductor I2C-bus specification version 2.1 and connected by an I2Cbus.
 *  This module will support any slave or master I2C compatible device.
 *
 *	Related Files
 *   - reg_i2c.h
 *   - i2c.h
 *   - i2c.c
 *  @addtogroup I2C
 *  @{
 */
 
/* I2C Interface Functions */
void i2cInit(void);
void i2cSetOwnAdd(i2cBASE_t *i2c, uint32 oadd);
void i2cSetSlaveAdd(i2cBASE_t *i2c, uint32 sadd);
void i2cSetBaudrate(i2cBASE_t *i2c, uint32 baud);
uint32  i2cIsTxReady(i2cBASE_t *i2c);
void i2cSendByte(i2cBASE_t *i2c, uint8 byte);
void i2cSend(i2cBASE_t *i2c, uint32 length, uint8 * data);
uint32  i2cIsRxReady(i2cBASE_t *i2c);
void i2cClearSCD(i2cBASE_t *i2c);
uint32  i2cRxError(i2cBASE_t *i2c);
uint32  i2cReceiveByte(i2cBASE_t *i2c);
void i2cReceive(i2cBASE_t *i2c, uint32 length, uint8 * data);
void i2cEnableNotification(i2cBASE_t *i2c, uint32 flags);
void i2cDisableNotification(i2cBASE_t *i2c, uint32 flags);
void i2cSetStart(i2cBASE_t *i2c);
void i2cSetStop(i2cBASE_t *i2c);
void i2cSetCount(i2cBASE_t *i2c ,uint32 cnt);
void i2cEnableLoopback(i2cBASE_t *i2c);
void i2cDisableLoopback(i2cBASE_t *i2c);

/** @fn void i2cNotification(i2cBASE_t *i2c, uint32 flags)
*   @brief Interrupt callback
*   @param[in] i2c   - I2C module base address
*   @param[in] flags - copy of error interrupt flags
*
* This is a callback that is provided by the application and is called apon
* an interrupt.  The parameter passed to the callback is a copy of the 
* interrupt flag register.
*/
void i2cNotification(i2cBASE_t *i2c, uint32 flags);

/**@}*/
#endif
