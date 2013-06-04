/** @file reg_can.h
*   @brief CAN Register Layer Header File
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

#ifndef __REG_CAN_H__
#define __REG_CAN_H__

#include "sys_common.h"



/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Can Register Frame Definition */
/** @struct canBase
*   @brief CAN Register Frame Definition
*
*   This type is used to access the CAN Registers.
*/
/** @typedef canBASE_t
*   @brief CAN Register Frame Type Definition
*
*   This type is used to access the CAN Registers.
*/
typedef volatile struct canBase
{
    uint32      CTL;          /**< 0x0000: Control Register                       */
    uint32      ES;           /**< 0x0004: Error and Status Register              */
    uint32      EERC;         /**< 0x0008: Error Counter Register                 */
    uint32      BTR;          /**< 0x000C: Bit Timing Register                    */
    uint32      INT;          /**< 0x0010: Interrupt Register                     */
    uint32      TEST;         /**< 0x0014: Test Register                          */
    uint32        rsvd1;      /**< 0x0018: Reserved                               */
    uint32      PERR;         /**< 0x001C: Parity/SECDED Error Code Register      */
    uint32      REL;          /**< 0x0020: Core Release Register                  */
    uint32      ECCDIAG;      /**< 0x0024: ECC Diagnostic Register                */
    uint32      ECCDIADSTAT;  /**< 0x0028: ECC Diagnostic Status Register         */
    uint32        rsvd2[21];  /**< 0x002C: Reserved                               */
    uint32      ABOTR;        /**< 0x0080: Auto Bus On Time Register              */
    uint32      TXRQX;        /**< 0x0084: Transmission Request X Register        */
    uint32      TXRQx[4U];    /**< 0x0088-0x0094: Transmission Request Registers  */
    uint32      NWDATX;       /**< 0x0098: New Data X Register                    */
    uint32      NWDATx[4U];   /**< 0x009C-0x00A8: New Data Registers              */
    uint32      INTPNDX;      /**< 0x00AC: Interrupt Pending X Register           */
    uint32      INTPNDx[4U];  /**< 0x00B0-0x00BC: Interrupt Pending Registers     */
    uint32      MSGVALX;      /**< 0x00C0: Message Valid X Register               */
    uint32      MSGVALx[4U];  /**< 0x00C4-0x00D0: Message Valid Registers         */
    uint32        rsvd3;      /**< 0x00D4: Reserved                               */
    uint32      INTMUXx[4U];  /**< 0x00D8-0x00E4: Interrupt Multiplexer Registers */
    uint32        rsvd4[6];   /**< 0x00E8: Reserved                               */
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
    uint8 IF1NO;              /**< 0x0100: IF1 Command Register, Msg Number       */
    uint8 IF1STAT;            /**< 0x0100: IF1 Command Register, Status           */
    uint8 IF1CMD;             /**< 0x0100: IF1 Command Register, Command          */
    uint8   rsvd9;            /**< 0x0100: IF1 Command Register, Reserved         */
#else
    uint8   rsvd9;            /**< 0x0100: IF1 Command Register, Reserved         */
    uint8 IF1CMD;             /**< 0x0100: IF1 Command Register, Command          */
    uint8 IF1STAT;            /**< 0x0100: IF1 Command Register, Status           */
    uint8 IF1NO;              /**< 0x0100: IF1 Command Register, Msg Number       */
#endif
    uint32      IF1MSK;       /**< 0x0104: IF1 Mask Register                      */
    uint32      IF1ARB;       /**< 0x0108: IF1 Arbitration Register               */
    uint32      IF1MCTL;      /**< 0x010C: IF1 Message Control Register           */
    uint8 IF1DATx[8U];        /**< 0x0110-0x0114: IF1 Data A and B Registers      */
    uint32        rsvd5[2];   /**< 0x0118: Reserved                               */
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
    uint8 IF2NO;              /**< 0x0120: IF2 Command Register, Msg No           */
    uint8 IF2STAT;            /**< 0x0120: IF2 Command Register, Status           */
    uint8 IF2CMD;             /**< 0x0120: IF2 Command Register, Command          */
    uint8   rsvd10;           /**< 0x0120: IF2 Command Register, Reserved         */
#else
    uint8   rsvd10;            /**< 0x0120: IF2 Command Register, Reserved         */
    uint8 IF2CMD;             /**< 0x0120: IF2 Command Register, Command          */
    uint8 IF2STAT;            /**< 0x0120: IF2 Command Register, Status           */
    uint8 IF2NO;              /**< 0x0120: IF2 Command Register, Msg Number       */
#endif
    uint32      IF2MSK;       /**< 0x0124: IF2 Mask Register                      */
    uint32      IF2ARB;       /**< 0x0128: IF2 Arbitration Register               */
    uint32      IF2MCTL;      /**< 0x012C: IF2 Message Control Register           */
    uint8 IF2DATx[8U];        /**< 0x0130-0x0134: IF2 Data A and B Registers      */
    uint32        rsvd6[2];   /**< 0x0138: Reserved                               */
    uint32      IF3OBS;       /**< 0x0140: IF3 Observation Register               */
    uint32      IF3MSK;       /**< 0x0144: IF3 Mask Register                      */
    uint32      IF3ARB;       /**< 0x0148: IF3 Arbitration Register               */
    uint32      IF3MCTL;      /**< 0x014C: IF3 Message Control Register           */
    uint8 IF3DATx[8U];        /**< 0x0150-0x0154: IF3 Data A and B Registers      */
    uint32        rsvd7[2];   /**< 0x0158: Reserved                               */
    uint32      IF3UEy[4U];   /**< 0x0160-0x016C: IF3 Update Enable Registers     */
    uint32        rsvd8[28];  /**< 0x0170: Reserved                               */
    uint32      TIOC;         /**< 0x01E0: TX IO Control Register                 */
    uint32      RIOC;         /**< 0x01E4: RX IO Control Register                 */
} canBASE_t;


/** @def canREG1
*   @brief CAN1 Register Frame Pointer
*
*   This pointer is used by the CAN driver to access the CAN1 registers.
*/
#define canREG1 ((canBASE_t *)0xFFF7DC00U)

/** @def canREG2
*   @brief CAN2 Register Frame Pointer
*
*   This pointer is used by the CAN driver to access the CAN2 registers.
*/
#define canREG2 ((canBASE_t *)0xFFF7DE00U)

/** @def canREG3
*   @brief CAN3 Register Frame Pointer
*
*   This pointer is used by the CAN driver to access the CAN3 registers.
*/
#define canREG3 ((canBASE_t *)0xFFF7E000U)

/** @def canRAM1
*   @brief CAN1 Mailbox RAM Pointer
*
*   This pointer is used by the CAN driver to access the CAN1 RAM.
*/
#define canRAM1 (*(volatile uint32 *)0xFF1E0000U)

/** @def canRAM2
*   @brief CAN2 Mailbox RAM Pointer
*
*   This pointer is used by the CAN driver to access the CAN2 RAM.
*/
#define canRAM2 (*(volatile uint32 *)0xFF1C0000U)

/** @def canRAM3
*   @brief CAN3 Mailbox RAM Pointer
*
*   This pointer is used by the CAN driver to access the CAN3 RAM.
*/
#define canRAM3 (*(volatile uint32 *)0xFF1A0000U)

/** @def canPARRAM1
*   @brief CAN1 Mailbox Parity RAM Pointer
*
*   This pointer is used by the CAN driver to access the CAN1 Parity RAM
*   for testing RAM parity error detect logic.
*/
#define canPARRAM1 (*(volatile uint32 *)(0xFF1E0000U + 0x10U))

/** @def canPARRAM2
*   @brief CAN2 Mailbox Parity RAM Pointer
*
*   This pointer is used by the CAN driver to access the CAN2 Parity RAM
*   for testing RAM parity error detect logic.
*/
#define canPARRAM2 (*(volatile uint32 *)(0xFF1C0000U + 0x10U))

/** @def canPARRAM3
*   @brief CAN3 Mailbox Parity RAM Pointer
*
*   This pointer is used by the CAN driver to access the CAN3 Parity RAM
*   for testing RAM parity error detect logic.
*/
#define canPARRAM3 (*(volatile uint32 *)(0xFF1A0000U + 0x10U))

/* USER CODE BEGIN (1) */
/* USER CODE END */


#endif
