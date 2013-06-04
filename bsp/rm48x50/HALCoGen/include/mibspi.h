/** @file mibspi.h
*   @brief MIBSPI Driver Definition File
*   @date 29.May.2013
*   @version 03.05.02
*   
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */


#ifndef __MIBSPI_H__
#define __MIBSPI_H__

#include "reg_mibspi.h"


/** @enum triggerEvent
*   @brief Transfer Group Trigger Event
*/
enum triggerEvent
{
    TRG_NEVER   = 0U,
    TRG_RISING  = 1U,
    TRG_FALLING = 2U,
    TRG_BOTH    = 3U,
    TRG_HIGH    = 5U,
    TRG_LOW     = 6U,
    TRG_ALWAYS  = 7U
};

/** @enum triggerSource
*   @brief Transfer Group Trigger Source
*/
enum triggerSource
{
    TRG_DISABLED,
    TRG_GIOA0,
    TRG_GIOA1,
    TRG_GIOA2,
    TRG_GIOA3,
    TRG_GIOA4,
    TRG_GIOA5,
    TRG_GIOA6,
    TRG_GIOA7,
    TRG_HET1_8,
    TRG_HET1_10,
    TRG_HET1_12,
    TRG_HET1_14,
    TRG_HET1_16,
    TRG_HET1_18,
    TRG_TICK
};


/** @enum mibspiPinSelect
*   @brief mibspi Pin Select
*/
enum mibspiPinSelect
{
    PIN_CS0   = 0U,
    PIN_CS1 = 1U,
    PIN_CS2 = 2U,
    PIN_CS3  = 3U,
    PIN_CS4 = 4U,
    PIN_CS5    = 5U,
    PIN_CS6    = 6U,
    PIN_CS7  = 7U,
    PIN_ENA = 8U,
    PIN_CLK = 9U,
    PIN_SIMO = 10U,
    PIN_SOMI = 11U,
   PIN_SIMO_1 = 17U,
   PIN_SIMO_2 = 18U,
   PIN_SIMO_3 = 19U,
   PIN_SIMO_4 = 20U,
   PIN_SIMO_5 = 21U,
   PIN_SIMO_6 = 22U,
   PIN_SIMO_7 = 23U,
   PIN_SOMI_1 = 25U,
   PIN_SOMI_2 = 26U,
   PIN_SOMI_3 = 27U,
   PIN_SOMI_4 = 28U,
   PIN_SOMI_5 = 29U,
   PIN_SOMI_6 = 30U,
   PIN_SOMI_7 = 31U
};


/** @enum chipSelect
*   @brief Transfer Group Chip Select
*/
enum chipSelect
{
    CS_NONE = 0xFFU,
    CS_0    = 0xFEU,
    CS_1    = 0xFDU,
    CS_2    = 0xFBU,
    CS_3    = 0xF7U,
    CS_4    = 0xEFU,
    CS_5    = 0xDFU,
    CS_6    = 0xBFU,
    CS_7    = 0x7FU
};

/** 
 *  @defgroup MIBSPI MIBSPI
 *  @brief Multi-Buffered Serial Peripheral Interface Module.
 *  
 *  The MibSPI/MibSPIP is a high-speed synchronous serial input/output port that allows a serial bit stream of
 *  programmed length (2 to 16 bits) to be shifted in and out of the device at a programmed bit-transfer rate.
 *  The MibSPI has a programmable buffer memory that enables programmed transmission to be completed
 *  without CPU intervention
 *
 *	Related Files
 *   - reg_mibspi.h
 *   - mibspi.h
 *   - mibspi.c
 *  @addtogroup MIBSPI
 *  @{
 */
 
/* MIBSPI Interface Functions */
void mibspiInit(void);
void mibspiSetFunctional(mibspiBASE_t *mibspi, uint32 port);
void mibspiSetData(mibspiBASE_t *mibspi, uint32 group, uint16 * data);
uint32 mibspiGetData(mibspiBASE_t *mibspi, uint32 group, uint16 * data);
void mibspiTransfer(mibspiBASE_t *mibspi, uint32 group);
boolean mibspiIsTransferComplete(mibspiBASE_t *mibspi, uint32 group);
void mibspiEnableGroupNotification(mibspiBASE_t *mibspi, uint32 group, uint32 level);
void mibspiDisableGroupNotification(mibspiBASE_t *mibspi, uint32 group);
void mibspiEnableLoopback(mibspiBASE_t *mibspi, loopBackType_t Loopbacktype);
void mibspiDisableLoopback(mibspiBASE_t *mibspi);


/** @fn void mibspiNotification(mibspiBASE_t *mibspi, uint32 flags)
*   @brief Error interrupt callback
*   @param[in] mibspi   - mibSpi module base address
*   @param[in] flags - Copy of error interrupt flags
*
* This is a error callback that is provided by the application and is call upon
* an error interrupt.  The paramer passed to the callback is a copy of the error
* interrupt flag register.
*/
void mibspiNotification(mibspiBASE_t *mibspi, uint32 flags);


/** @fn void mibspiGroupNotification(mibspiBASE_t *mibspi, uint32 group)
*   @brief Transfer complete notification callback
*   @param[in] mibspi   - mibSpi module base address
*   @param[in] group - Transfer group
*
* This is a callback function provided by the application.  It is call when
* a transfer is complete.  The parameter is the transfer group that triggered
* the interrupt.
*/
void mibspiGroupNotification(mibspiBASE_t *mibspi, uint32 group);

/**@}*/
#endif
