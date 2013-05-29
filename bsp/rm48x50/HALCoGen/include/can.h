/** @file can.h
*   @brief CAN Driver Header File
*   @date 29.May.2013
*   @version 03.05.02
*   
*   This file contains:
*   - Definitions
*   - Types
*   - Interface Prototypes
*   .
*   which are relevant for the CAN driver.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef __CAN_H__
#define __CAN_H__

#include "reg_can.h"



/* USER CODE BEGIN (0) */
/* USER CODE END */

/* CAN General Definitions */

/** @def canLEVEL_ACTIVE
*   @brief Alias name for CAN error operation level active (Error counter 0-95)  
*/
#define canLEVEL_ACTIVE 0x00U

/** @def canLEVEL_WARNING
*   @brief Alias name for CAN error operation level warning (Error counter 96-127)  
*/
#define canLEVEL_WARNING 0x40U

/** @def canLEVEL_PASSIVE
*   @brief Alias name for CAN error operation level passive (Error counter 128-255)  
*/
#define canLEVEL_PASSIVE 0x20U

/** @def canLEVEL_BUS_OFF
*   @brief Alias name for CAN error operation level bus off (Error counter 256)  
*/
#define canLEVEL_BUS_OFF 0x80U

/** @def canERROR_NO
*   @brief Alias name for no CAN error occurred 
*/
#define canERROR_OK 0U

/** @def canERROR_STUFF
*   @brief Alias name for CAN stuff error an RX message 
*/
#define canERROR_STUFF 1U

/** @def canERROR_FORMAT
*   @brief Alias name for CAN form/format error an RX message 
*/
#define canERROR_FORMAT 2U

/** @def canERROR_ACKNOWLEDGE
*   @brief Alias name for CAN TX message wasn't acknowledged  
*/
#define canERROR_ACKNOWLEDGE 3U

/** @def canERROR_BIT1
*   @brief Alias name for CAN TX message sending recessive level but monitoring dominant  
*/
#define canERROR_BIT1 4U

/** @def canERROR_BIT0
*   @brief Alias name for CAN TX message sending dominant level but monitoring recessive  
*/
#define canERROR_BIT0 5U

/** @def canERROR_CRC
*   @brief Alias name for CAN RX message received wrong CRC  
*/
#define canERROR_CRC 6U

/** @def canERROR_NO
*   @brief Alias name for CAN no message has send or received since last call of CANGetLastError  
*/
#define canERROR_NO 7U

/** @def canMESSAGE_BOX1
*   @brief Alias name for CAN message box 1
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX1 1U

/** @def canMESSAGE_BOX2
*   @brief Alias name for CAN message box 2
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX2 2U

/** @def canMESSAGE_BOX3
*   @brief Alias name for CAN message box 3
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX3 3U

/** @def canMESSAGE_BOX4
*   @brief Alias name for CAN message box 4
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX4 4U

/** @def canMESSAGE_BOX5
*   @brief Alias name for CAN message box 5
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX5 5U

/** @def canMESSAGE_BOX6
*   @brief Alias name for CAN message box 6
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX6 6U

/** @def canMESSAGE_BOX7
*   @brief Alias name for CAN message box 7
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX7 7U

/** @def canMESSAGE_BOX8
*   @brief Alias name for CAN message box 8
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX8 8U

/** @def canMESSAGE_BOX9
*   @brief Alias name for CAN message box 9
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX9 9U

/** @def canMESSAGE_BOX10
*   @brief Alias name for CAN message box 10
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX10 10U

/** @def canMESSAGE_BOX11
*   @brief Alias name for CAN message box 11
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX11 11U

/** @def canMESSAGE_BOX12
*   @brief Alias name for CAN message box 12
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX12 12U

/** @def canMESSAGE_BOX13
*   @brief Alias name for CAN message box 13
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX13 13U

/** @def canMESSAGE_BOX14
*   @brief Alias name for CAN message box 14
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX14 14U

/** @def canMESSAGE_BOX15
*   @brief Alias name for CAN message box 15
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX15 15U

/** @def canMESSAGE_BOX16
*   @brief Alias name for CAN message box 16
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX16 16U

/** @def canMESSAGE_BOX17
*   @brief Alias name for CAN message box 17
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX17 17U

/** @def canMESSAGE_BOX18
*   @brief Alias name for CAN message box 18
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX18 18U

/** @def canMESSAGE_BOX19
*   @brief Alias name for CAN message box 19
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX19 19U

/** @def canMESSAGE_BOX20
*   @brief Alias name for CAN message box 20
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX20 20U

/** @def canMESSAGE_BOX21
*   @brief Alias name for CAN message box 21
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX21 21U

/** @def canMESSAGE_BOX22
*   @brief Alias name for CAN message box 22
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX22 22U

/** @def canMESSAGE_BOX23
*   @brief Alias name for CAN message box 23
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX23 23U

/** @def canMESSAGE_BOX24
*   @brief Alias name for CAN message box 24
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX24 24U

/** @def canMESSAGE_BOX25
*   @brief Alias name for CAN message box 25
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX25 25U

/** @def canMESSAGE_BOX26
*   @brief Alias name for CAN message box 26
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX26 26U

/** @def canMESSAGE_BOX27
*   @brief Alias name for CAN message box 27
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX27 27U

/** @def canMESSAGE_BOX28
*   @brief Alias name for CAN message box 28
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX28 28U

/** @def canMESSAGE_BOX29
*   @brief Alias name for CAN message box 29
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX29 29U

/** @def canMESSAGE_BOX30
*   @brief Alias name for CAN message box 30
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX30 30U

/** @def canMESSAGE_BOX31
*   @brief Alias name for CAN message box 31
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX31 31U

/** @def canMESSAGE_BOX32
*   @brief Alias name for CAN message box 32
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX32 32U

/** @def canMESSAGE_BOX33
*   @brief Alias name for CAN message box 33
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX33 33U

/** @def canMESSAGE_BOX34
*   @brief Alias name for CAN message box 34
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX34 34U

/** @def canMESSAGE_BOX35
*   @brief Alias name for CAN message box 35
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX35 35U

/** @def canMESSAGE_BOX36
*   @brief Alias name for CAN message box 36
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX36 36U

/** @def canMESSAGE_BOX37
*   @brief Alias name for CAN message box 37
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX37 37U

/** @def canMESSAGE_BOX38
*   @brief Alias name for CAN message box 38
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX38 38U

/** @def canMESSAGE_BOX39
*   @brief Alias name for CAN message box 39
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX39 39U

/** @def canMESSAGE_BOX40
*   @brief Alias name for CAN message box 40
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX40 40U

/** @def canMESSAGE_BOX41
*   @brief Alias name for CAN message box 41
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX41 41U

/** @def canMESSAGE_BOX42
*   @brief Alias name for CAN message box 42
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX42 42U

/** @def canMESSAGE_BOX43
*   @brief Alias name for CAN message box 43
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX43 43U

/** @def canMESSAGE_BOX44
*   @brief Alias name for CAN message box 44
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX44 44U

/** @def canMESSAGE_BOX45
*   @brief Alias name for CAN message box 45
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX45 45U

/** @def canMESSAGE_BOX46
*   @brief Alias name for CAN message box 46
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX46 46U

/** @def canMESSAGE_BOX47
*   @brief Alias name for CAN message box 47
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX47 47U

/** @def canMESSAGE_BOX48
*   @brief Alias name for CAN message box 48
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX48 48U

/** @def canMESSAGE_BOX49
*   @brief Alias name for CAN message box 49
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX49 49U

/** @def canMESSAGE_BOX50
*   @brief Alias name for CAN message box 50
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX50 50U

/** @def canMESSAGE_BOX51
*   @brief Alias name for CAN message box 51
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX51 51U

/** @def canMESSAGE_BOX52
*   @brief Alias name for CAN message box 52
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX52 52U

/** @def canMESSAGE_BOX53
*   @brief Alias name for CAN message box 53
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX53 53U

/** @def canMESSAGE_BOX54
*   @brief Alias name for CAN message box 54
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX54 54U

/** @def canMESSAGE_BOX55
*   @brief Alias name for CAN message box 55
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX55 55U

/** @def canMESSAGE_BOX56
*   @brief Alias name for CAN message box 56
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX56 56U

/** @def canMESSAGE_BOX57
*   @brief Alias name for CAN message box 57
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX57 57U

/** @def canMESSAGE_BOX58
*   @brief Alias name for CAN message box 58
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX58 58U

/** @def canMESSAGE_BOX59
*   @brief Alias name for CAN message box 59
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX59 59U

/** @def canMESSAGE_BOX60
*   @brief Alias name for CAN message box 60
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX60 60U

/** @def canMESSAGE_BOX61
*   @brief Alias name for CAN message box 61
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX61 61U

/** @def canMESSAGE_BOX62
*   @brief Alias name for CAN message box 62
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX62 62U

/** @def canMESSAGE_BOX63
*   @brief Alias name for CAN message box 63
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX63 63U

/** @def canMESSAGE_BOX64
*   @brief Alias name for CAN message box 64
*
*   @note This value should be used for API argument @a messageBox
*/
#define canMESSAGE_BOX64 64U


/* USER CODE BEGIN (1) */
/* USER CODE END */

/** 
 *  @defgroup CAN CAN
 *  @brief Controller Area Network Module.
 *  
 *  The Controller Area Network is a high-integrity, serial, multi-master communication protocol for distributed
 *  real-time applications. This CAN module is implemented according to ISO 11898-1 and is suitable for
 *  industrial, automotive and general embedded communications
 *
 *	Related Files
 *   - reg_can.h
 *   - can.h
 *   - can.c
 *  @addtogroup CAN
 *  @{
 */
 
/* CAN Interface Functions */

void     canInit(void);
uint32 canTransmit(canBASE_t *node, uint32 messageBox, const uint8 * data);
uint32 canGetData(canBASE_t *node, uint32 messageBox, uint8 * const data);
uint32 canIsTxMessagePending(canBASE_t *node, uint32 messageBox);
uint32 canIsRxMessageArrived(canBASE_t *node, uint32 messageBox);
uint32 canIsMessageBoxValid(canBASE_t *node, uint32 messageBox);
uint32 canGetLastError(canBASE_t *node);
uint32 canGetErrorLevel(canBASE_t *node);
void     canEnableErrorNotification(canBASE_t *node);
void     canDisableErrorNotification(canBASE_t *node);
void canIoSetDirection(canBASE_t *node,uint32 TxDir,uint32 RxDir);
void canIoSetPort(canBASE_t *node, uint32 TxValue, uint32 RxValue);
uint32 canIoTxGetBit(canBASE_t *node);
uint32 canIoRxGetBit(canBASE_t *node);

/** @fn void canErrorNotification(canBASE_t *node, uint32 notification)
*   @brief Error notification
*   @param[in] node Pointer to CAN node:
*              - canREG1: CAN1 node pointer
*              - canREG2: CAN2 node pointer
*              - canREG3: CAN3 node pointer
*   @param[in] notification Error notification code:
*           - canLEVEL_WARNING (0x40): When RX- or TX error counter are between 96 and 127     
*           - canLEVEL_BUS_OFF (0x80): When RX- or TX error counter are above 255     
*
*   @note This function has to be provide by the user.
*/
void canErrorNotification(canBASE_t *node, uint32 notification);

/** @fn void canMessageNotification(canBASE_t *node, uint32 messageBox)
*   @brief Message notification
*   @param[in] node Pointer to CAN node:
*              - canREG1: CAN1 node pointer
*              - canREG2: CAN2 node pointer
*              - canREG3: CAN3 node pointer
*   @param[in] messageBox Message box number of CAN node:
*              - canMESSAGE_BOX1: CAN message box 1
*              - canMESSAGE_BOXn: CAN message box n [n: 1-64]
*              - canMESSAGE_BOX64: CAN message box 64
*
*   @note This function has to be provide by the user.
*/
void canMessageNotification(canBASE_t *node, uint32 messageBox);

/**@}*/
/* USER CODE BEGIN (2) */
/* USER CODE END */


#endif
