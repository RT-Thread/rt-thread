/**************************************************************************//**
 * @file     sclib.h
 * @version  V1.00
 * $Revision: 2 $
 * $Date: 15/05/18 3:44p $
 * @brief    Smartcard library header file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __SCLIB_H__
#define __SCLIB_H__

#include "NUC100Series.h"

/** @addtogroup Library Library
  @{
*/

/** @addtogroup SCLIB Smartcard Library
  @{
*/

/** @addtogroup SCLIB_EXPORTED_CONSTANTS Smartcard Library Exported Constants
  @{
*/


#ifdef __cplusplus
extern "C"
{
#endif

#define SCLIB_MAX_ATR_LEN       32  ///< Max ATR length. ISO-7816 8.2.1
#define SCLIB_MIN_ATR_LEN        2  ///< Min ATR length, TS and T0

// Protocol
#define SCLIB_PROTOCOL_UNDEFINED                0x00000000  ///< There is no active protocol.
#define SCLIB_PROTOCOL_T0                       0x00000001  ///< T=0 is the active protocol.
#define SCLIB_PROTOCOL_T1                       0x00000002  ///< T=1 is the active protocol.

#define SCLIB_SUCCESS                           0x00000000  ///< Command successful without error
// error code generate by interrupt handler
#define SCLIB_ERR_CARD_REMOVED                  0x00000001  ///< Smartcard removed
#define SCLIB_ERR_OVER_RUN                      0x00000002  ///< Rx FIFO over run
#define SCLIB_ERR_PARITY_ERROR                  0x00000003  ///< Tx/Rx parity error
#define SCLIB_ERR_NO_STOP                       0x00000004  ///< Stop bit not found
#define SCLIB_ERR_SILENT_BYTE                   0x00000005  ///< I/O pin stay at low for longer than 1 character time
#define SCLIB_ERR_CMD                           0x00000006
#define SCLIB_ERR_UNSUPPORTEDCARD               0x00000007
#define SCLIB_ERR_READ                          0x00000008
#define SCLIB_ERR_WRITE                         0x00000009
#define SCLIB_ERR_TIME0OUT                      0x0000000A  ///< Smartcard timer 0 timeout
#define SCLIB_ERR_TIME1OUT                      0x0000000B  ///< Smartcard timer 1 timeout
#define SCLIB_ERR_TIME2OUT                      0x0000000C  ///< Smartcard timer 2 timeout
#define SCLIB_ERR_AUTOCONVENTION                0x0000000D  ///< Smartcard is neither direct nor inverse convention
#define SCLIB_ERR_CLOCK                         0x0000000E  ///< Smartcard clock frequency is not between 1MHz and 5 MHz
#define SCLIB_ERR_BGTIMEOUT                     0x0000000E
// error code generate while parsing ATR and process PPS
#define SCLIB_ERR_ATR_UNRECOGNIZED              0x00001001  ///< Unrecognized ATR
#define SCLIB_ERR_ATR_INVALID_PARAM             0x00001002  ///< ATR parsing interface bytes error
#define SCLIB_ERR_ATR_INVALID_TCK               0x00001003  ///< TCK check byte error
#define SCLIB_ERR_PPS                           0x00001004
// error code for T=1 protocol
#define SCLIB_ERR_T1_PARITY                     0x00002001            ///< T=1 Parity Error Notice
#define SCLIB_ERR_T1_ICC                        0x00002002           ///< ICC communication error
#define SCLIB_ERR_T1_PROTOCOL                   0x00002003  ///< T=1 Protocol Error
#define SCLIB_ERR_T1_ABORT_RECEIVED             0x00002004  ///< Received ABORT request
#define SCLIB_ERR_T1_RESYNCH_RECEIVED           0x00002005  ///< Received RESYNCH request
#define SCLIB_ERR_T1_VPP_ERROR_RECEIVED         0x00002006  ///< Received VPP error
#define SCLIB_ERR_T1_WTXRES_RECEIVED            0x00002007  ///< Received BWT extension request
#define SCLIB_ERR_T1_IFSRES_RECEIVED            0x00002008  ///< Received max IFS offer
#define SCLIB_ERR_T1_ABORTRES_RECEIVED          0x00002009  ///< Received ABORT response
#define SCLIB_ERR_T1_CHECKSUM                   0x0000200A  ///< T=1 block check sum error

// error code for T=0 protocol
#define SCLIB_ERR_T0_PROTOCOL                   0x00003003      ///< T=0 Protocol Error

// error code indicates application control flow error
#define SCLIB_ERR_DEACTIVE                      0x0000F001      ///< Smartcard is deactivation
#define SCLIB_ERR_CARDBUSY                      0x0000F002      ///< Smartcard is busy, previous transmission is not complete yet

/*@}*/ /* end of group NUC400_SCLIB_EXPORTED_CONSTANTS */

/** @addtogroup NUC400_SCLIB_EXPORTED_STRUCTS Smartcard Library Exported Structs
  @{
*/

/**
  * @brief  A structure holds smartcard information
  */
typedef struct {
    uint32_t T;                         ///< Protocol, ether \ref SCLIB_PROTOCOL_T0 or \ref SCLIB_PROTOCOL_T1.
    uint32_t ATR_Len;                   ///< ATR length, between SCLIB_MAX_ATR_LEN and SCLIB_MIN_ATR_LEN
    uint8_t ATR_Buf[SCLIB_MAX_ATR_LEN]; ///< Buffer holds ATR answered by smartcard
} SCLIB_CARD_INFO_T;

/**
  * @brief  A structure holds smartcard attribute, including convention, guard time, waiting time, IFCS... etc.
  */
typedef struct
{
    uint8_t Fi;        ///< Findex;
    uint8_t Di;        ///< Dindex;
    uint8_t conv;      ///< Convention, direct or inverse. 0 direct, 1 inverse
    uint8_t chksum;    ///< Checksum type
    uint8_t GT;        ///< Guard Time
    uint8_t WI;        ///< Wait integer for T0
    uint8_t BWI;       ///< Block waiting integer for T1;
    uint8_t CWI;       ///< Character waiting integer for T1;
    uint8_t clkStop;   ///< Card clock stop status. 00 Not allowed, 01 low, 02, high, 03 ether high or low
    uint8_t IFSC;      ///< size of negotiated IFCS
    uint8_t NAD;       ///< NAD value
} SCLIB_CARD_ATTRIB_T;


/*@}*/ /* end of group NUC400_SCLIB_EXPORTED_STRUCTS */

/** @addtogroup NUC400_SCLIB_EXPORTED_FUNCTIONS Smartcard Library Exported Functions
  @{
*/

/**
  * @brief Activate a smartcard
  * @param[in] num Smartcard interface number. From 0 ~ ( \ref SC_INTERFACE_NUM - 1)
  * @param[in] u32EMVCheck Enable EMV error check or not. Valid setting are \ref TRUE and \ref FALSE.
  *            By enable EMV error checking, this library will perform ATR checking according to
  *            EMV book 1 specification. Otherwise, the error checking follows ISO 7816-3
  * @return Smartcard successfully activated or not
  * @retval SCLIB_SUCCESS Smartcard activated successfully
  * @retval Others Smartcard activation failed
  * @note It is required to set smartcard interface clock between 1 MHz and 5 MHz before
  *       calling this API, otherwise this API return with \ref SCLIB_ERR_CLOCK error code.
  * @note EMV book 1 is stricter than ISO-7816 on ATR checking. Enable EMV check iff the
  *       application supports EMV cards only.
  */
int32_t SCLIB_Activate(uint32_t num, uint32_t u32EMVCheck);

/**
  * @brief Activate a smartcard with large delay between set VCC high and start CLK output
  * @param[in] num Smartcard interface number. From 0 ~ ( \ref SC_INTERFACE_NUM - 1)
  * @param[in] u32EMVCheck Enable EMV error check or not. Valid setting are \ref TRUE and \ref FALSE.
  *            By enable EMV error checking, this library will perform ATR checking according to
  *            EMV book 1 specification. Otherwise, the error checking follows ISO 7816-3
  * @param[in] u32Delay Extra delay time between set VCC high and start CLK output, using ETU as time unit.
  * @return Smartcard successfully activated or not
  * @retval SCLIB_SUCCESS Smartcard activated successfully
  * @retval Others Smartcard activation failed
  * @note It is required to set smartcard interface clock between 1 MHz and 5 MHz before
  *       calling this API, otherwise this API return with \ref SCLIB_ERR_CLOCK error code.
  * @note EMV book 1 is stricter than ISO-7816 on ATR checking. Enable EMV check iff the
  *       application supports EMV cards only.
  * @note Only use this function instead of \ref SCLIB_Activate if there's large capacitor on VCC pin and 
  *       VCC raise slowly.
  */
int32_t SCLIB_ActivateDelay(uint32_t num, uint32_t u32EMVCheck, uint32_t u32Delay);



/**
  * @brief Cold reset a smartcard
  * @param[in] num Smartcard interface number. From 0 ~ ( \ref SC_INTERFACE_NUM - 1)
  * @return Smartcard cold reset success or not
  * @retval SCLIB_SUCCESS Smartcard cold reset success
  * @retval Others Smartcard cold reset failed
  */
int32_t SCLIB_ColdReset(uint32_t num);

/**
  * @brief Warm reset a smartcard
  * @param[in] num Smartcard interface number. From 0 ~ ( \ref SC_INTERFACE_NUM - 1)
  * @return Smartcard warm reset success or not
  * @retval SCLIB_SUCCESS Smartcard warm reset success
  * @retval Others Smartcard warm reset failed
  */
int32_t SCLIB_WarmReset(uint32_t num);

/**
  * @brief Deactivate a smartcard
  * @param[in] num Smartcard interface number. From 0 ~ ( \ref SC_INTERFACE_NUM - 1)
  * @return None
  */
void SCLIB_Deactivate(uint32_t num);

/**
  * @brief Get the card information (e.g., protocol selected, ATR...) after activation success
  * @param[in] num Smartcard interface number. From 0 ~ ( \ref SC_INTERFACE_NUM - 1)
  * @param[out] s_info A pointer to \ref SCLIB_CARD_INFO_T holds the card information
  * @return Success or not
  * @retval SCLIB_SUCCESS              Success, s_info contains card information
  * @retval SCLIB_ERR_CARD_REMOVED     Card removed, s_info does not contains card information
  * @retval SCLIB_ERR_DEACTIVE         Card is deactivated, s_info does not contains card information
  */
int32_t SCLIB_GetCardInfo(uint32_t num, SCLIB_CARD_INFO_T *s_info);


/**
  * @brief Get the card attribute (e.g., Fi, Di, convention, guard time... etc. ) after activation success
  * @param[in] num Smartcard interface number. From 0 ~ ( \ref SC_INTERFACE_NUM - 1)
  * @param[out] s_attrib A pointer to \ref SCLIB_CARD_ATTRIB_T holds the card information
  * @return Success or not
  * @retval SCLIB_SUCCESS              Success, s_info contains card information
  * @retval SCLIB_ERR_CARD_REMOVED     Card removed, s_info does not contains card information
  * @retval SCLIB_ERR_DEACTIVE         Card is deactivated, s_info does not contains card information
  */
int32_t SCLIB_GetCardAttrib(uint32_t num, SCLIB_CARD_ATTRIB_T *s_attrib);

/**
  * @brief Start a smartcard transmission.
  * @details SCLIB will start a transmission according to the protocol selected
  * @param[in] num Smartcard interface number. From 0 ~ ( \ref SC_INTERFACE_NUM - 1)
  * @param[in] cmdBuf Command buffer pointer
  * @param[in] cmdLen Command length
  * @param[out] rspBuf Buffer to holds card response
  * @param[out] rspLen Response length received
  * @return Smartcard transmission success or failed
  * @retval SCLIB_SUCCESS Transmission success. rspBuf and rspLen holds response data and length
  * @retval Others Transmission failed
  * @note This API supports case 1, 2S, 3S, and 4S defined in ISO-7816, but does \b NOT support case 2E, 3E, and 4E.
  */
int32_t SCLIB_StartTransmission(uint32_t num, uint8_t *cmdBuf, uint32_t cmdLen, uint8_t *rspBuf, uint32_t *rspLen);

/**
  * @brief Set interface device max information field size (IFSD)
  * @details This function sends S block to notify card about the max size of information filed blocks that
  *          can be received by the interface device. According to EMV 9.2.4.3, this should be the first
  *          block transmitted by terminal to ICC after ATR.
  * @param[in] num Smartcard interface number. From 0 ~ ( \ref SC_INTERFACE_NUM - 1)
  * @param[in] size IFSD size. According to EMV spec 9.2.4.3 Error Free Operation, this field must be 0xFE.
  * @return Smartcard transmission success or failed
  * @retval SCLIB_SUCCESS Smartcard warm reset success
  * @retval Others Smartcard warm reset failed
  */
int32_t SCLIB_SetIFSD(uint32_t num, uint8_t size);


/**
  * @brief  A callback called by library while smartcard request for a time extension
  * @param[in]  u32Protocol What protocol the card is using while it requested for a time extension.
  *                     Could be ether \ref SCLIB_PROTOCOL_T0 or \ref SCLIB_PROTOCOL_T1
  * @return None
  * @note   This function is defined with __weak attribute and does nothing in library.
  *         Application can provide its own time extension function. For example, and CCID reader
  *         can use this function to report this status to PC. See CCID rev 1.1 Table 6.2-3
  */
#if defined (__GNUC__)
void SCLIB_RequestTimeExtension () __attribute__ ((weak));
void SCLIB_RequestTimeExtension(uint32_t u32Protocol);
#else
__weak void SCLIB_RequestTimeExtension(uint32_t u32Protocol);
#endif

/**
  * @brief Process card detect event in IRQ handler
  * @param[in] num Smartcard interface number. From 0 ~ ( \ref SC_INTERFACE_NUM - 1)
  * @return Card detect event occur or not
  * @retval 1 Card detect event occurred
  * @retval 0 Card detect event did not occur
  * @note Smartcard IRQ handler shall call this function with correct interface number as parameter
  */
uint32_t SCLIB_CheckCDEvent(uint32_t num);

/**
  * @brief Process time out event in IRQ handler
  * @param[in] num Smartcard interface number. From 0 ~ ( \ref SC_INTERFACE_NUM - 1)
  * @return Time out event occur or not
  * @retval 1 Time out event occurred
  * @retval 0 Time out event did not occur
  * @note Smartcard IRQ handler shall call this function with correct interface number as parameter
  */
uint32_t SCLIB_CheckTimeOutEvent(uint32_t num);

/**
  * @brief Process card transmission event in IRQ handler
  * @param[in] num Smartcard interface number. From 0 ~ ( \ref SC_INTERFACE_NUM - 1)
  * @return Transmission event occur or not
  * @retval 1 Transmission event occurred
  * @retval 0 Transmission event did not occur
  * @note Smartcard IRQ handler shall call this function with correct interface number as parameter
  */
uint32_t SCLIB_CheckTxRxEvent(uint32_t num);

/**
  * @brief Process error event in IRQ handler
  * @param[in] num Smartcard interface number. From 0 ~ ( \ref SC_INTERFACE_NUM - 1)
  * @return Error event occur or not
  * @retval 1 Error event occurred
  * @retval 0 Error event did not occur
  * @note Smartcard IRQ handler shall call this function with correct interface number as parameter
  */
uint32_t SCLIB_CheckErrorEvent(uint32_t num);


#ifdef __cplusplus
}
#endif

#endif //__SCLIB_H__

/*@}*/ /* end of group SCLIB_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group SC_Library */

/*@}*/ /* end of group Library */

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
