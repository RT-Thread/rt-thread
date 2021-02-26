/**************************************************************************//**
 * @file     uart.h
 * @version  V3.00
 * @brief    NUC980 series UART driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#ifndef __NU_UART_H__
#define __NU_UART_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nuc980.h"


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup UART_Driver UART Driver
  @{
*/

/** @addtogroup UART_EXPORTED_CONSTANTS UART Exported Constants
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/* UART FIFO size constants definitions                                                                    */
/*---------------------------------------------------------------------------------------------------------*/

#define UART0_FIFO_SIZE 16ul /*!< UART0 supports separated receive/transmit 16/16 bytes entry FIFO \hideinitializer */
#define UART1_FIFO_SIZE 16ul /*!< UART1 supports separated receive/transmit 16/16 bytes entry FIFO \hideinitializer */
#define UART2_FIFO_SIZE 16ul /*!< UART2 supports separated receive/transmit 16/16 bytes entry FIFO \hideinitializer */
#define UART3_FIFO_SIZE 16ul /*!< UART3 supports separated receive/transmit 16/16 bytes entry FIFO \hideinitializer */
#define UART4_FIFO_SIZE 16ul /*!< UART3 supports separated receive/transmit 16/16 bytes entry FIFO \hideinitializer */
#define UART5_FIFO_SIZE 16ul /*!< UART3 supports separated receive/transmit 16/16 bytes entry FIFO \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/* UART_FIFO constants definitions                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#define UART_FIFO_RFITL_1BYTE      (0x0ul << UART_FIFO_RFITL_Pos)   /*!< UART_FIFO setting to set RX FIFO Trigger Level to 1 byte \hideinitializer */
#define UART_FIFO_RFITL_4BYTES     (0x1ul << UART_FIFO_RFITL_Pos)   /*!< UART_FIFO setting to set RX FIFO Trigger Level to 4 bytes \hideinitializer */
#define UART_FIFO_RFITL_8BYTES     (0x2ul << UART_FIFO_RFITL_Pos)   /*!< UART_FIFO setting to set RX FIFO Trigger Level to 8 bytes \hideinitializer */
#define UART_FIFO_RFITL_14BYTES    (0x3ul << UART_FIFO_RFITL_Pos)   /*!< UART_FIFO setting to set RX FIFO Trigger Level to 14 bytes \hideinitializer */

#define UART_FIFO_RTSTRGLV_1BYTE      (0x0ul << UART_FIFO_RTSTRGLV_Pos)  /*!< UART_FIFO setting to set RTS Trigger Level to 1 byte \hideinitializer */
#define UART_FIFO_RTSTRGLV_4BYTES     (0x1ul << UART_FIFO_RTSTRGLV_Pos)  /*!< UART_FIFO setting to set RTS Trigger Level to 4 bytes \hideinitializer */
#define UART_FIFO_RTSTRGLV_8BYTES     (0x2ul << UART_FIFO_RTSTRGLV_Pos)  /*!< UART_FIFO setting to set RTS Trigger Level to 8 bytes \hideinitializer */
#define UART_FIFO_RTSTRGLV_14BYTES    (0x3ul << UART_FIFO_RTSTRGLV_Pos)  /*!< UART_FIFO setting to set RTS Trigger Level to 14 bytes \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/* UART_LINE constants definitions                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#define UART_WORD_LEN_5     (0ul) /*!< UART_LINE setting to set UART word length to 5 bits \hideinitializer */
#define UART_WORD_LEN_6     (1ul) /*!< UART_LINE setting to set UART word length to 6 bits \hideinitializer */
#define UART_WORD_LEN_7     (2ul) /*!< UART_LINE setting to set UART word length to 7 bits \hideinitializer */
#define UART_WORD_LEN_8     (3ul) /*!< UART_LINE setting to set UART word length to 8 bits \hideinitializer */

#define UART_PARITY_NONE    (0x0ul << UART_LINE_PBE_Pos) /*!< UART_LINE setting to set UART as no parity   \hideinitializer */
#define UART_PARITY_ODD     (0x1ul << UART_LINE_PBE_Pos) /*!< UART_LINE setting to set UART as odd parity  \hideinitializer */
#define UART_PARITY_EVEN    (0x3ul << UART_LINE_PBE_Pos) /*!< UART_LINE setting to set UART as even parity \hideinitializer */
#define UART_PARITY_MARK    (0x5ul << UART_LINE_PBE_Pos) /*!< UART_LINE setting to keep parity bit as '1'  \hideinitializer */
#define UART_PARITY_SPACE   (0x7ul << UART_LINE_PBE_Pos) /*!< UART_LINE setting to keep parity bit as '0'  \hideinitializer */

#define UART_STOP_BIT_1     (0x0ul << UART_LINE_NSB_Pos) /*!< UART_LINE setting for one stop bit  \hideinitializer */
#define UART_STOP_BIT_1_5   (0x1ul << UART_LINE_NSB_Pos) /*!< UART_LINE setting for 1.5 stop bit when 5-bit word length  \hideinitializer */
#define UART_STOP_BIT_2     (0x1ul << UART_LINE_NSB_Pos) /*!< UART_LINE setting for two stop bit when 6, 7, 8-bit word length \hideinitializer */


/*---------------------------------------------------------------------------------------------------------*/
/* UART RTS ACTIVE LEVEL constants definitions                                                             */
/*---------------------------------------------------------------------------------------------------------*/
#define UART_RTS_IS_LOW_LEV_ACTIVE   (0x1ul << UART_MODEM_RTSACTLV_Pos) /*!< Set RTS is Low Level Active \hideinitializer */
#define UART_RTS_IS_HIGH_LEV_ACTIVE  (0x0ul << UART_MODEM_RTSACTLV_Pos) /*!< Set RTS is High Level Active \hideinitializer */


/*---------------------------------------------------------------------------------------------------------*/
/* UART_IRDA constants definitions                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#define UART_IRDA_TXEN      (0x1ul << UART_IRDA_TXEN_Pos) /*!< Set IrDA function Tx mode \hideinitializer */
#define UART_IRDA_RXEN      (0x0ul << UART_IRDA_TXEN_Pos) /*!< Set IrDA function Rx mode \hideinitializer */


/*---------------------------------------------------------------------------------------------------------*/
/* UART_FUNCSEL constants definitions                                                                      */
/*---------------------------------------------------------------------------------------------------------*/
#define UART_FUNCSEL_UART  (0x0ul << UART_FUNCSEL_FUNCSEL_Pos) /*!< UART_FUNCSEL setting to set UART Function  (Default) \hideinitializer */
#define UART_FUNCSEL_LIN   (0x1ul << UART_FUNCSEL_FUNCSEL_Pos) /*!< UART_FUNCSEL setting to set LIN Function             \hideinitializer */
#define UART_FUNCSEL_IrDA  (0x2ul << UART_FUNCSEL_FUNCSEL_Pos) /*!< UART_FUNCSEL setting to set IrDA Function            \hideinitializer */
#define UART_FUNCSEL_RS485 (0x3ul << UART_FUNCSEL_FUNCSEL_Pos) /*!< UART_FUNCSEL setting to set RS485 Function           \hideinitializer */


/*---------------------------------------------------------------------------------------------------------*/
/* UART_LINCTL constants definitions                                                                       */
/*---------------------------------------------------------------------------------------------------------*/
#define UART_LINCTL_BRKFL(x)    (((x)-1) << UART_LINCTL_BRKFL_Pos)  /*!< UART_LINCTL setting to set LIN Break Field Length, x = 10 ~ 15, default value is 12 \hideinitializer */
#define UART_LINCTL_BSL(x)      (((x)-1) << UART_LINCTL_BSL_Pos)    /*!< UART_LINCTL setting to set LIN Break/Sync Delimiter Length, x = 1 ~ 4 \hideinitializer */
#define UART_LINCTL_HSEL_BREAK             (0x0UL << UART_LINCTL_HSEL_Pos)    /*!< UART_LINCTL setting to set LIN Header Select to break field \hideinitializer */
#define UART_LINCTL_HSEL_BREAK_SYNC        (0x1UL << UART_LINCTL_HSEL_Pos)    /*!< UART_LINCTL setting to set LIN Header Select to break field and sync field \hideinitializer */
#define UART_LINCTL_HSEL_BREAK_SYNC_ID     (0x2UL << UART_LINCTL_HSEL_Pos)    /*!< UART_LINCTL setting to set LIN Header Select to break field, sync field and ID field \hideinitializer */
#define UART_LINCTL_PID(x)      ((x) << UART_LINCTL_PID_Pos)       /*!< UART_LINCTL setting to set LIN PID value \hideinitializer */


/*---------------------------------------------------------------------------------------------------------*/
/* UART BAUDRATE MODE constants definitions                                                                */
/*---------------------------------------------------------------------------------------------------------*/
#define UART_BAUD_MODE0     (0ul) /*!< Set UART Baudrate Mode is Mode0 \hideinitializer */
#define UART_BAUD_MODE2     (UART_BAUD_BAUDM1_Msk | UART_BAUD_BAUDM0_Msk) /*!< Set UART Baudrate Mode is Mode2 \hideinitializer */


/*@}*/ /* end of group UART_EXPORTED_CONSTANTS */

typedef struct
{
    __IO uint32_t DAT;                   /*!< [0x0000] UART Receive/Transmit Buffer Register                            */
    __IO uint32_t INTEN;                 /*!< [0x0004] UART Interrupt Enable Register                                   */
    __IO uint32_t FIFO;                  /*!< [0x0008] UART FIFO Control Register                                       */
    __IO uint32_t LINE;                  /*!< [0x000c] UART Line Control Register                                       */
    __IO uint32_t MODEM;                 /*!< [0x0010] UART Modem Control Register                                      */
    __IO uint32_t MODEMSTS;              /*!< [0x0014] UART Modem Status Register                                       */
    __IO uint32_t FIFOSTS;               /*!< [0x0018] UART FIFO Status Register                                        */
    __IO uint32_t INTSTS;                /*!< [0x001c] UART Interrupt Status Register                                   */
    __IO uint32_t TOUT;                  /*!< [0x0020] UART Time-out Register                                           */
    __IO uint32_t BAUD;                  /*!< [0x0024] UART Baud Rate Divider Register                                  */
    __IO uint32_t IRDA;                  /*!< [0x0028] UART IrDA Control Register                                       */
    __IO uint32_t ALTCTL;                /*!< [0x002c] UART Alternate Control/Status Register                           */
    __IO uint32_t FUNCSEL;               /*!< [0x0030] UART Function Select Register                                    */
    __IO uint32_t LINCTL;                /*!< [0x0034] UART LIN Control Register                                        */
    __IO uint32_t LINSTS;                /*!< [0x0038] UART LIN Status Register                                         */
    __IO uint32_t BRCOMP;                /*!< [0x003c] UART Baud Rate Compensation Register                             */
    __IO uint32_t WKCTL;                 /*!< [0x0040] UART Wake-up Control Register                                    */
    __IO uint32_t WKSTS;                 /*!< [0x0044] UART Wake-up Status Register                                     */
    __IO uint32_t DWKCOMP;               /*!< [0x0048] UART Incoming Data Wake-up Compensation Register                 */

} UART_T;

#define UART_DAT_DAT_Pos                 (0)                                               /*!< UART_T::DAT: DAT Position              */
#define UART_DAT_DAT_Msk                 (0xfful << UART_DAT_DAT_Pos)                      /*!< UART_T::DAT: DAT Mask                  */

#define UART_DAT_PARITY_Pos              (8)                                               /*!< UART_T::DAT: PARITY Position           */
#define UART_DAT_PARITY_Msk              (0x1ul << UART_DAT_PARITY_Pos)                    /*!< UART_T::DAT: PARITY Mask               */

#define UART_INTEN_RDAIEN_Pos            (0)                                               /*!< UART_T::INTEN: RDAIEN Position         */
#define UART_INTEN_RDAIEN_Msk            (0x1ul << UART_INTEN_RDAIEN_Pos)                  /*!< UART_T::INTEN: RDAIEN Mask             */

#define UART_INTEN_THREIEN_Pos           (1)                                               /*!< UART_T::INTEN: THREIEN Position        */
#define UART_INTEN_THREIEN_Msk           (0x1ul << UART_INTEN_THREIEN_Pos)                 /*!< UART_T::INTEN: THREIEN Mask            */

#define UART_INTEN_RLSIEN_Pos            (2)                                               /*!< UART_T::INTEN: RLSIEN Position         */
#define UART_INTEN_RLSIEN_Msk            (0x1ul << UART_INTEN_RLSIEN_Pos)                  /*!< UART_T::INTEN: RLSIEN Mask             */

#define UART_INTEN_MODEMIEN_Pos          (3)                                               /*!< UART_T::INTEN: MODEMIEN Position       */
#define UART_INTEN_MODEMIEN_Msk          (0x1ul << UART_INTEN_MODEMIEN_Pos)                /*!< UART_T::INTEN: MODEMIEN Mask           */

#define UART_INTEN_RXTOIEN_Pos           (4)                                               /*!< UART_T::INTEN: RXTOIEN Position        */
#define UART_INTEN_RXTOIEN_Msk           (0x1ul << UART_INTEN_RXTOIEN_Pos)                 /*!< UART_T::INTEN: RXTOIEN Mask            */

#define UART_INTEN_BUFERRIEN_Pos         (5)                                               /*!< UART_T::INTEN: BUFERRIEN Position      */
#define UART_INTEN_BUFERRIEN_Msk         (0x1ul << UART_INTEN_BUFERRIEN_Pos)               /*!< UART_T::INTEN: BUFERRIEN Mask          */

#define UART_INTEN_WKIEN_Pos             (6)                                               /*!< UART_T::INTEN: WKIEN Position          */
#define UART_INTEN_WKIEN_Msk             (0x1ul << UART_INTEN_WKIEN_Pos)                   /*!< UART_T::INTEN: WKIEN Mask              */

#define UART_INTEN_LINIEN_Pos            (8)                                               /*!< UART_T::INTEN: LINIEN Position         */
#define UART_INTEN_LINIEN_Msk            (0x1ul << UART_INTEN_LINIEN_Pos)                  /*!< UART_T::INTEN: LINIEN Mask             */

#define UART_INTEN_TOCNTEN_Pos           (11)                                              /*!< UART_T::INTEN: TOCNTEN Position        */
#define UART_INTEN_TOCNTEN_Msk           (0x1ul << UART_INTEN_TOCNTEN_Pos)                 /*!< UART_T::INTEN: TOCNTEN Mask            */

#define UART_INTEN_ATORTSEN_Pos          (12)                                              /*!< UART_T::INTEN: ATORTSEN Position       */
#define UART_INTEN_ATORTSEN_Msk          (0x1ul << UART_INTEN_ATORTSEN_Pos)                /*!< UART_T::INTEN: ATORTSEN Mask           */

#define UART_INTEN_ATOCTSEN_Pos          (13)                                              /*!< UART_T::INTEN: ATOCTSEN Position       */
#define UART_INTEN_ATOCTSEN_Msk          (0x1ul << UART_INTEN_ATOCTSEN_Pos)                /*!< UART_T::INTEN: ATOCTSEN Mask           */

#define UART_INTEN_TXPDMAEN_Pos          (14)                                              /*!< UART_T::INTEN: TXPDMAEN Position       */
#define UART_INTEN_TXPDMAEN_Msk          (0x1ul << UART_INTEN_TXPDMAEN_Pos)                /*!< UART_T::INTEN: TXPDMAEN Mask           */

#define UART_INTEN_RXPDMAEN_Pos          (15)                                              /*!< UART_T::INTEN: RXPDMAEN Position       */
#define UART_INTEN_RXPDMAEN_Msk          (0x1ul << UART_INTEN_RXPDMAEN_Pos)                /*!< UART_T::INTEN: RXPDMAEN Mask           */

#define UART_INTEN_ABRIEN_Pos            (18)                                              /*!< UART_T::INTEN: ABRIEN Position         */
#define UART_INTEN_ABRIEN_Msk            (0x1ul << UART_INTEN_ABRIEN_Pos)                  /*!< UART_T::INTEN: ABRIEN Mask             */

#define UART_INTEN_TXENDIEN_Pos          (22)                                              /*!< UART_T::INTEN: TXENDIEN Position       */
#define UART_INTEN_TXENDIEN_Msk          (0x1ul << UART_INTEN_TXENDIEN_Pos)                /*!< UART_T::INTEN: TXENDIEN Mask           */

#define UART_FIFO_RXRST_Pos              (1)                                               /*!< UART_T::FIFO: RXRST Position           */
#define UART_FIFO_RXRST_Msk              (0x1ul << UART_FIFO_RXRST_Pos)                    /*!< UART_T::FIFO: RXRST Mask               */

#define UART_FIFO_TXRST_Pos              (2)                                               /*!< UART_T::FIFO: TXRST Position           */
#define UART_FIFO_TXRST_Msk              (0x1ul << UART_FIFO_TXRST_Pos)                    /*!< UART_T::FIFO: TXRST Mask               */

#define UART_FIFO_RFITL_Pos              (4)                                               /*!< UART_T::FIFO: RFITL Position           */
#define UART_FIFO_RFITL_Msk              (0xful << UART_FIFO_RFITL_Pos)                    /*!< UART_T::FIFO: RFITL Mask               */

#define UART_FIFO_RXOFF_Pos              (8)                                               /*!< UART_T::FIFO: RXOFF Position           */
#define UART_FIFO_RXOFF_Msk              (0x1ul << UART_FIFO_RXOFF_Pos)                    /*!< UART_T::FIFO: RXOFF Mask               */

#define UART_FIFO_RTSTRGLV_Pos           (16)                                              /*!< UART_T::FIFO: RTSTRGLV Position        */
#define UART_FIFO_RTSTRGLV_Msk           (0xful << UART_FIFO_RTSTRGLV_Pos)                 /*!< UART_T::FIFO: RTSTRGLV Mask            */

#define UART_LINE_WLS_Pos                (0)                                               /*!< UART_T::LINE: WLS Position             */
#define UART_LINE_WLS_Msk                (0x3ul << UART_LINE_WLS_Pos)                      /*!< UART_T::LINE: WLS Mask                 */

#define UART_LINE_NSB_Pos                (2)                                               /*!< UART_T::LINE: NSB Position             */
#define UART_LINE_NSB_Msk                (0x1ul << UART_LINE_NSB_Pos)                      /*!< UART_T::LINE: NSB Mask                 */

#define UART_LINE_PBE_Pos                (3)                                               /*!< UART_T::LINE: PBE Position             */
#define UART_LINE_PBE_Msk                (0x1ul << UART_LINE_PBE_Pos)                      /*!< UART_T::LINE: PBE Mask                 */

#define UART_LINE_EPE_Pos                (4)                                               /*!< UART_T::LINE: EPE Position             */
#define UART_LINE_EPE_Msk                (0x1ul << UART_LINE_EPE_Pos)                      /*!< UART_T::LINE: EPE Mask                 */

#define UART_LINE_SPE_Pos                (5)                                               /*!< UART_T::LINE: SPE Position             */
#define UART_LINE_SPE_Msk                (0x1ul << UART_LINE_SPE_Pos)                      /*!< UART_T::LINE: SPE Mask                 */

#define UART_LINE_BCB_Pos                (6)                                               /*!< UART_T::LINE: BCB Position             */
#define UART_LINE_BCB_Msk                (0x1ul << UART_LINE_BCB_Pos)                      /*!< UART_T::LINE: BCB Mask                 */

#define UART_LINE_PSS_Pos                (7)                                               /*!< UART_T::LINE: PSS Position             */
#define UART_LINE_PSS_Msk                (0x1ul << UART_LINE_PSS_Pos)                      /*!< UART_T::LINE: PSS Mask                 */

#define UART_LINE_TXDINV_Pos             (8)                                               /*!< UART_T::LINE: TXDINV Position          */
#define UART_LINE_TXDINV_Msk             (0x1ul << UART_LINE_TXDINV_Pos)                   /*!< UART_T::LINE: TXDINV Mask              */

#define UART_LINE_RXDINV_Pos             (9)                                               /*!< UART_T::LINE: RXDINV Position          */
#define UART_LINE_RXDINV_Msk             (0x1ul << UART_LINE_RXDINV_Pos)                   /*!< UART_T::LINE: RXDINV Mask              */

#define UART_MODEM_RTS_Pos               (1)                                               /*!< UART_T::MODEM: RTS Position            */
#define UART_MODEM_RTS_Msk               (0x1ul << UART_MODEM_RTS_Pos)                     /*!< UART_T::MODEM: RTS Mask                */

#define UART_MODEM_RTSACTLV_Pos          (9)                                               /*!< UART_T::MODEM: RTSACTLV Position       */
#define UART_MODEM_RTSACTLV_Msk          (0x1ul << UART_MODEM_RTSACTLV_Pos)                /*!< UART_T::MODEM: RTSACTLV Mask           */

#define UART_MODEM_RTSSTS_Pos            (13)                                              /*!< UART_T::MODEM: RTSSTS Position         */
#define UART_MODEM_RTSSTS_Msk            (0x1ul << UART_MODEM_RTSSTS_Pos)                  /*!< UART_T::MODEM: RTSSTS Mask             */

#define UART_MODEMSTS_CTSDETF_Pos        (0)                                               /*!< UART_T::MODEMSTS: CTSDETF Position     */
#define UART_MODEMSTS_CTSDETF_Msk        (0x1ul << UART_MODEMSTS_CTSDETF_Pos)              /*!< UART_T::MODEMSTS: CTSDETF Mask         */

#define UART_MODEMSTS_CTSSTS_Pos         (4)                                               /*!< UART_T::MODEMSTS: CTSSTS Position      */
#define UART_MODEMSTS_CTSSTS_Msk         (0x1ul << UART_MODEMSTS_CTSSTS_Pos)               /*!< UART_T::MODEMSTS: CTSSTS Mask          */

#define UART_MODEMSTS_CTSACTLV_Pos       (8)                                               /*!< UART_T::MODEMSTS: CTSACTLV Position    */
#define UART_MODEMSTS_CTSACTLV_Msk       (0x1ul << UART_MODEMSTS_CTSACTLV_Pos)             /*!< UART_T::MODEMSTS: CTSACTLV Mask        */

#define UART_FIFOSTS_RXOVIF_Pos          (0)                                               /*!< UART_T::FIFOSTS: RXOVIF Position       */
#define UART_FIFOSTS_RXOVIF_Msk          (0x1ul << UART_FIFOSTS_RXOVIF_Pos)                /*!< UART_T::FIFOSTS: RXOVIF Mask           */

#define UART_FIFOSTS_ABRDIF_Pos          (1)                                               /*!< UART_T::FIFOSTS: ABRDIF Position       */
#define UART_FIFOSTS_ABRDIF_Msk          (0x1ul << UART_FIFOSTS_ABRDIF_Pos)                /*!< UART_T::FIFOSTS: ABRDIF Mask           */

#define UART_FIFOSTS_ABRDTOIF_Pos        (2)                                               /*!< UART_T::FIFOSTS: ABRDTOIF Position     */
#define UART_FIFOSTS_ABRDTOIF_Msk        (0x1ul << UART_FIFOSTS_ABRDTOIF_Pos)              /*!< UART_T::FIFOSTS: ABRDTOIF Mask         */

#define UART_FIFOSTS_ADDRDETF_Pos        (3)                                               /*!< UART_T::FIFOSTS: ADDRDETF Position     */
#define UART_FIFOSTS_ADDRDETF_Msk        (0x1ul << UART_FIFOSTS_ADDRDETF_Pos)              /*!< UART_T::FIFOSTS: ADDRDETF Mask         */

#define UART_FIFOSTS_PEF_Pos             (4)                                               /*!< UART_T::FIFOSTS: PEF Position          */
#define UART_FIFOSTS_PEF_Msk             (0x1ul << UART_FIFOSTS_PEF_Pos)                   /*!< UART_T::FIFOSTS: PEF Mask              */

#define UART_FIFOSTS_FEF_Pos             (5)                                               /*!< UART_T::FIFOSTS: FEF Position          */
#define UART_FIFOSTS_FEF_Msk             (0x1ul << UART_FIFOSTS_FEF_Pos)                   /*!< UART_T::FIFOSTS: FEF Mask              */

#define UART_FIFOSTS_BIF_Pos             (6)                                               /*!< UART_T::FIFOSTS: BIF Position          */
#define UART_FIFOSTS_BIF_Msk             (0x1ul << UART_FIFOSTS_BIF_Pos)                   /*!< UART_T::FIFOSTS: BIF Mask              */

#define UART_FIFOSTS_RXPTR_Pos           (8)                                               /*!< UART_T::FIFOSTS: RXPTR Position        */
#define UART_FIFOSTS_RXPTR_Msk           (0x3ful << UART_FIFOSTS_RXPTR_Pos)                /*!< UART_T::FIFOSTS: RXPTR Mask            */

#define UART_FIFOSTS_RXEMPTY_Pos         (14)                                              /*!< UART_T::FIFOSTS: RXEMPTY Position      */
#define UART_FIFOSTS_RXEMPTY_Msk         (0x1ul << UART_FIFOSTS_RXEMPTY_Pos)               /*!< UART_T::FIFOSTS: RXEMPTY Mask          */

#define UART_FIFOSTS_RXFULL_Pos          (15)                                              /*!< UART_T::FIFOSTS: RXFULL Position       */
#define UART_FIFOSTS_RXFULL_Msk          (0x1ul << UART_FIFOSTS_RXFULL_Pos)                /*!< UART_T::FIFOSTS: RXFULL Mask           */

#define UART_FIFOSTS_TXPTR_Pos           (16)                                              /*!< UART_T::FIFOSTS: TXPTR Position        */
#define UART_FIFOSTS_TXPTR_Msk           (0x3ful << UART_FIFOSTS_TXPTR_Pos)                /*!< UART_T::FIFOSTS: TXPTR Mask            */

#define UART_FIFOSTS_TXEMPTY_Pos         (22)                                              /*!< UART_T::FIFOSTS: TXEMPTY Position      */
#define UART_FIFOSTS_TXEMPTY_Msk         (0x1ul << UART_FIFOSTS_TXEMPTY_Pos)               /*!< UART_T::FIFOSTS: TXEMPTY Mask          */

#define UART_FIFOSTS_TXFULL_Pos          (23)                                              /*!< UART_T::FIFOSTS: TXFULL Position       */
#define UART_FIFOSTS_TXFULL_Msk          (0x1ul << UART_FIFOSTS_TXFULL_Pos)                /*!< UART_T::FIFOSTS: TXFULL Mask           */

#define UART_FIFOSTS_TXOVIF_Pos          (24)                                              /*!< UART_T::FIFOSTS: TXOVIF Position       */
#define UART_FIFOSTS_TXOVIF_Msk          (0x1ul << UART_FIFOSTS_TXOVIF_Pos)                /*!< UART_T::FIFOSTS: TXOVIF Mask           */

#define UART_FIFOSTS_TXEMPTYF_Pos        (28)                                              /*!< UART_T::FIFOSTS: TXEMPTYF Position     */
#define UART_FIFOSTS_TXEMPTYF_Msk        (0x1ul << UART_FIFOSTS_TXEMPTYF_Pos)              /*!< UART_T::FIFOSTS: TXEMPTYF Mask         */

#define UART_FIFOSTS_RXIDLE_Pos          (29)                                              /*!< UART_T::FIFOSTS: RXIDLE Position       */
#define UART_FIFOSTS_RXIDLE_Msk          (0x1ul << UART_FIFOSTS_RXIDLE_Pos)                /*!< UART_T::FIFOSTS: RXIDLE Mask           */

#define UART_FIFOSTS_TXRXACT_Pos         (31)                                              /*!< UART_T::FIFOSTS: TXRXACT Position      */
#define UART_FIFOSTS_TXRXACT_Msk         (0x1ul << UART_FIFOSTS_TXRXACT_Pos)               /*!< UART_T::FIFOSTS: TXRXACT Mask          */

#define UART_INTSTS_RDAIF_Pos            (0)                                               /*!< UART_T::INTSTS: RDAIF Position         */
#define UART_INTSTS_RDAIF_Msk            (0x1ul << UART_INTSTS_RDAIF_Pos)                  /*!< UART_T::INTSTS: RDAIF Mask             */

#define UART_INTSTS_THREIF_Pos           (1)                                               /*!< UART_T::INTSTS: THREIF Position        */
#define UART_INTSTS_THREIF_Msk           (0x1ul << UART_INTSTS_THREIF_Pos)                 /*!< UART_T::INTSTS: THREIF Mask            */

#define UART_INTSTS_RLSIF_Pos            (2)                                               /*!< UART_T::INTSTS: RLSIF Position         */
#define UART_INTSTS_RLSIF_Msk            (0x1ul << UART_INTSTS_RLSIF_Pos)                  /*!< UART_T::INTSTS: RLSIF Mask             */

#define UART_INTSTS_MODEMIF_Pos          (3)                                               /*!< UART_T::INTSTS: MODEMIF Position       */
#define UART_INTSTS_MODEMIF_Msk          (0x1ul << UART_INTSTS_MODEMIF_Pos)                /*!< UART_T::INTSTS: MODEMIF Mask           */

#define UART_INTSTS_RXTOIF_Pos           (4)                                               /*!< UART_T::INTSTS: RXTOIF Position        */
#define UART_INTSTS_RXTOIF_Msk           (0x1ul << UART_INTSTS_RXTOIF_Pos)                 /*!< UART_T::INTSTS: RXTOIF Mask            */

#define UART_INTSTS_BUFERRIF_Pos         (5)                                               /*!< UART_T::INTSTS: BUFERRIF Position      */
#define UART_INTSTS_BUFERRIF_Msk         (0x1ul << UART_INTSTS_BUFERRIF_Pos)               /*!< UART_T::INTSTS: BUFERRIF Mask          */

#define UART_INTSTS_WKIF_Pos             (6)                                               /*!< UART_T::INTSTS: WKIF Position          */
#define UART_INTSTS_WKIF_Msk             (0x1ul << UART_INTSTS_WKIF_Pos)                   /*!< UART_T::INTSTS: WKIF Mask              */

#define UART_INTSTS_LINIF_Pos            (7)                                               /*!< UART_T::INTSTS: LINIF Position         */
#define UART_INTSTS_LINIF_Msk            (0x1ul << UART_INTSTS_LINIF_Pos)                  /*!< UART_T::INTSTS: LINIF Mask             */

#define UART_INTSTS_RDAINT_Pos           (8)                                               /*!< UART_T::INTSTS: RDAINT Position        */
#define UART_INTSTS_RDAINT_Msk           (0x1ul << UART_INTSTS_RDAINT_Pos)                 /*!< UART_T::INTSTS: RDAINT Mask            */

#define UART_INTSTS_THREINT_Pos          (9)                                               /*!< UART_T::INTSTS: THREINT Position       */
#define UART_INTSTS_THREINT_Msk          (0x1ul << UART_INTSTS_THREINT_Pos)                /*!< UART_T::INTSTS: THREINT Mask           */

#define UART_INTSTS_RLSINT_Pos           (10)                                              /*!< UART_T::INTSTS: RLSINT Position        */
#define UART_INTSTS_RLSINT_Msk           (0x1ul << UART_INTSTS_RLSINT_Pos)                 /*!< UART_T::INTSTS: RLSINT Mask            */

#define UART_INTSTS_MODEMINT_Pos         (11)                                              /*!< UART_T::INTSTS: MODEMINT Position      */
#define UART_INTSTS_MODEMINT_Msk         (0x1ul << UART_INTSTS_MODEMINT_Pos)               /*!< UART_T::INTSTS: MODEMINT Mask          */

#define UART_INTSTS_RXTOINT_Pos          (12)                                              /*!< UART_T::INTSTS: RXTOINT Position       */
#define UART_INTSTS_RXTOINT_Msk          (0x1ul << UART_INTSTS_RXTOINT_Pos)                /*!< UART_T::INTSTS: RXTOINT Mask           */

#define UART_INTSTS_BUFERRINT_Pos        (13)                                              /*!< UART_T::INTSTS: BUFERRINT Position     */
#define UART_INTSTS_BUFERRINT_Msk        (0x1ul << UART_INTSTS_BUFERRINT_Pos)              /*!< UART_T::INTSTS: BUFERRINT Mask         */

#define UART_INTSTS_WKINT_Pos            (14)                                              /*!< UART_T::INTSTS: WKINT Position         */
#define UART_INTSTS_WKINT_Msk            (0x1ul << UART_INTSTS_WKINT_Pos)                  /*!< UART_T::INTSTS: WKINT Mask             */

#define UART_INTSTS_LININT_Pos           (15)                                              /*!< UART_T::INTSTS: LININT Position        */
#define UART_INTSTS_LININT_Msk           (0x1ul << UART_INTSTS_LININT_Pos)                 /*!< UART_T::INTSTS: LININT Mask            */

#define UART_INTSTS_HWRLSIF_Pos          (18)                                              /*!< UART_T::INTSTS: HWRLSIF Position       */
#define UART_INTSTS_HWRLSIF_Msk          (0x1ul << UART_INTSTS_HWRLSIF_Pos)                /*!< UART_T::INTSTS: HWRLSIF Mask           */

#define UART_INTSTS_HWMODIF_Pos          (19)                                              /*!< UART_T::INTSTS: HWMODIF Position       */
#define UART_INTSTS_HWMODIF_Msk          (0x1ul << UART_INTSTS_HWMODIF_Pos)                /*!< UART_T::INTSTS: HWMODIF Mask           */

#define UART_INTSTS_HWTOIF_Pos           (20)                                              /*!< UART_T::INTSTS: HWTOIF Position        */
#define UART_INTSTS_HWTOIF_Msk           (0x1ul << UART_INTSTS_HWTOIF_Pos)                 /*!< UART_T::INTSTS: HWTOIF Mask            */

#define UART_INTSTS_HWBUFEIF_Pos         (21)                                              /*!< UART_T::INTSTS: HWBUFEIF Position      */
#define UART_INTSTS_HWBUFEIF_Msk         (0x1ul << UART_INTSTS_HWBUFEIF_Pos)               /*!< UART_T::INTSTS: HWBUFEIF Mask          */

#define UART_INTSTS_TXENDIF_Pos          (22)                                              /*!< UART_T::INTSTS: TXENDIF Position       */
#define UART_INTSTS_TXENDIF_Msk          (0x1ul << UART_INTSTS_TXENDIF_Pos)                /*!< UART_T::INTSTS: TXENDIF Mask           */

#define UART_INTSTS_HWRLSINT_Pos         (26)                                              /*!< UART_T::INTSTS: HWRLSINT Position      */
#define UART_INTSTS_HWRLSINT_Msk         (0x1ul << UART_INTSTS_HWRLSINT_Pos)               /*!< UART_T::INTSTS: HWRLSINT Mask          */

#define UART_INTSTS_HWMODINT_Pos         (27)                                              /*!< UART_T::INTSTS: HWMODINT Position      */
#define UART_INTSTS_HWMODINT_Msk         (0x1ul << UART_INTSTS_HWMODINT_Pos)               /*!< UART_T::INTSTS: HWMODINT Mask          */

#define UART_INTSTS_HWTOINT_Pos          (28)                                              /*!< UART_T::INTSTS: HWTOINT Position       */
#define UART_INTSTS_HWTOINT_Msk          (0x1ul << UART_INTSTS_HWTOINT_Pos)                /*!< UART_T::INTSTS: HWTOINT Mask           */

#define UART_INTSTS_HWBUFEINT_Pos        (29)                                              /*!< UART_T::INTSTS: HWBUFEINT Position     */
#define UART_INTSTS_HWBUFEINT_Msk        (0x1ul << UART_INTSTS_HWBUFEINT_Pos)              /*!< UART_T::INTSTS: HWBUFEINT Mask         */

#define UART_INTSTS_TXENDINT_Pos         (30)                                              /*!< UART_T::INTSTS: TXENDINT Position      */
#define UART_INTSTS_TXENDINT_Msk         (0x1ul << UART_INTSTS_TXENDINT_Pos)               /*!< UART_T::INTSTS: TXENDINT Mask          */

#define UART_INTSTS_ABRINT_Pos           (31)                                              /*!< UART_T::INTSTS: ABRINT Position        */
#define UART_INTSTS_ABRINT_Msk           (0x1ul << UART_INTSTS_ABRINT_Pos)                 /*!< UART_T::INTSTS: ABRINT Mask            */

#define UART_TOUT_TOIC_Pos               (0)                                               /*!< UART_T::TOUT: TOIC Position            */
#define UART_TOUT_TOIC_Msk               (0xfful << UART_TOUT_TOIC_Pos)                    /*!< UART_T::TOUT: TOIC Mask                */

#define UART_TOUT_DLY_Pos                (8)                                               /*!< UART_T::TOUT: DLY Position             */
#define UART_TOUT_DLY_Msk                (0xfful << UART_TOUT_DLY_Pos)                     /*!< UART_T::TOUT: DLY Mask                 */

#define UART_BAUD_BRD_Pos                (0)                                               /*!< UART_T::BAUD: BRD Position             */
#define UART_BAUD_BRD_Msk                (0xfffful << UART_BAUD_BRD_Pos)                   /*!< UART_T::BAUD: BRD Mask                 */

#define UART_BAUD_EDIVM1_Pos             (24)                                              /*!< UART_T::BAUD: EDIVM1 Position          */
#define UART_BAUD_EDIVM1_Msk             (0xful << UART_BAUD_EDIVM1_Pos)                   /*!< UART_T::BAUD: EDIVM1 Mask              */

#define UART_BAUD_BAUDM0_Pos             (28)                                              /*!< UART_T::BAUD: BAUDM0 Position          */
#define UART_BAUD_BAUDM0_Msk             (0x1ul << UART_BAUD_BAUDM0_Pos)                   /*!< UART_T::BAUD: BAUDM0 Mask              */

#define UART_BAUD_BAUDM1_Pos             (29)                                              /*!< UART_T::BAUD: BAUDM1 Position          */
#define UART_BAUD_BAUDM1_Msk             (0x1ul << UART_BAUD_BAUDM1_Pos)                   /*!< UART_T::BAUD: BAUDM1 Mask              */

#define UART_IRDA_TXEN_Pos               (1)                                               /*!< UART_T::IRDA: TXEN Position            */
#define UART_IRDA_TXEN_Msk               (0x1ul << UART_IRDA_TXEN_Pos)                     /*!< UART_T::IRDA: TXEN Mask                */

#define UART_IRDA_TXINV_Pos              (5)                                               /*!< UART_T::IRDA: TXINV Position           */
#define UART_IRDA_TXINV_Msk              (0x1ul << UART_IRDA_TXINV_Pos)                    /*!< UART_T::IRDA: TXINV Mask               */

#define UART_IRDA_RXINV_Pos              (6)                                               /*!< UART_T::IRDA: RXINV Position           */
#define UART_IRDA_RXINV_Msk              (0x1ul << UART_IRDA_RXINV_Pos)                    /*!< UART_T::IRDA: RXINV Mask               */

#define UART_ALTCTL_BRKFL_Pos            (0)                                               /*!< UART_T::ALTCTL: BRKFL Position         */
#define UART_ALTCTL_BRKFL_Msk            (0xful << UART_ALTCTL_BRKFL_Pos)                  /*!< UART_T::ALTCTL: BRKFL Mask             */

#define UART_ALTCTL_LINRXEN_Pos          (6)                                               /*!< UART_T::ALTCTL: LINRXEN Position       */
#define UART_ALTCTL_LINRXEN_Msk          (0x1ul << UART_ALTCTL_LINRXEN_Pos)                /*!< UART_T::ALTCTL: LINRXEN Mask           */

#define UART_ALTCTL_LINTXEN_Pos          (7)                                               /*!< UART_T::ALTCTL: LINTXEN Position       */
#define UART_ALTCTL_LINTXEN_Msk          (0x1ul << UART_ALTCTL_LINTXEN_Pos)                /*!< UART_T::ALTCTL: LINTXEN Mask           */

#define UART_ALTCTL_RS485NMM_Pos         (8)                                               /*!< UART_T::ALTCTL: RS485NMM Position      */
#define UART_ALTCTL_RS485NMM_Msk         (0x1ul << UART_ALTCTL_RS485NMM_Pos)               /*!< UART_T::ALTCTL: RS485NMM Mask          */

#define UART_ALTCTL_RS485AAD_Pos         (9)                                               /*!< UART_T::ALTCTL: RS485AAD Position      */
#define UART_ALTCTL_RS485AAD_Msk         (0x1ul << UART_ALTCTL_RS485AAD_Pos)               /*!< UART_T::ALTCTL: RS485AAD Mask          */

#define UART_ALTCTL_RS485AUD_Pos         (10)                                              /*!< UART_T::ALTCTL: RS485AUD Position      */
#define UART_ALTCTL_RS485AUD_Msk         (0x1ul << UART_ALTCTL_RS485AUD_Pos)               /*!< UART_T::ALTCTL: RS485AUD Mask          */

#define UART_ALTCTL_ADDRDEN_Pos          (15)                                              /*!< UART_T::ALTCTL: ADDRDEN Position       */
#define UART_ALTCTL_ADDRDEN_Msk          (0x1ul << UART_ALTCTL_ADDRDEN_Pos)                /*!< UART_T::ALTCTL: ADDRDEN Mask           */

#define UART_ALTCTL_ABRIF_Pos            (17)                                              /*!< UART_T::ALTCTL: ABRIF Position         */
#define UART_ALTCTL_ABRIF_Msk            (0x1ul << UART_ALTCTL_ABRIF_Pos)                  /*!< UART_T::ALTCTL: ABRIF Mask             */

#define UART_ALTCTL_ABRDEN_Pos           (18)                                              /*!< UART_T::ALTCTL: ABRDEN Position        */
#define UART_ALTCTL_ABRDEN_Msk           (0x1ul << UART_ALTCTL_ABRDEN_Pos)                 /*!< UART_T::ALTCTL: ABRDEN Mask            */

#define UART_ALTCTL_ABRDBITS_Pos         (19)                                              /*!< UART_T::ALTCTL: ABRDBITS Position      */
#define UART_ALTCTL_ABRDBITS_Msk         (0x3ul << UART_ALTCTL_ABRDBITS_Pos)               /*!< UART_T::ALTCTL: ABRDBITS Mask          */

#define UART_ALTCTL_ADDRMV_Pos           (24)                                              /*!< UART_T::ALTCTL: ADDRMV Position        */
#define UART_ALTCTL_ADDRMV_Msk           (0xfful << UART_ALTCTL_ADDRMV_Pos)                /*!< UART_T::ALTCTL: ADDRMV Mask            */

#define UART_FUNCSEL_FUNCSEL_Pos         (0)                                               /*!< UART_T::FUNCSEL: FUNCSEL Position      */
#define UART_FUNCSEL_FUNCSEL_Msk         (0x3ul << UART_FUNCSEL_FUNCSEL_Pos)               /*!< UART_T::FUNCSEL: FUNCSEL Mask          */

#define UART_FUNCSEL_TXRXDIS_Pos         (3)                                               /*!< UART_T::FUNCSEL: TXRXDIS Position      */
#define UART_FUNCSEL_TXRXDIS_Msk         (0x1ul << UART_FUNCSEL_TXRXDIS_Pos)               /*!< UART_T::FUNCSEL: TXRXDIS Mask          */

#define UART_LINCTL_SLVEN_Pos            (0)                                               /*!< UART_T::LINCTL: SLVEN Position         */
#define UART_LINCTL_SLVEN_Msk            (0x1ul << UART_LINCTL_SLVEN_Pos)                  /*!< UART_T::LINCTL: SLVEN Mask             */

#define UART_LINCTL_SLVHDEN_Pos          (1)                                               /*!< UART_T::LINCTL: SLVHDEN Position       */
#define UART_LINCTL_SLVHDEN_Msk          (0x1ul << UART_LINCTL_SLVHDEN_Pos)                /*!< UART_T::LINCTL: SLVHDEN Mask           */

#define UART_LINCTL_SLVAREN_Pos          (2)                                               /*!< UART_T::LINCTL: SLVAREN Position       */
#define UART_LINCTL_SLVAREN_Msk          (0x1ul << UART_LINCTL_SLVAREN_Pos)                /*!< UART_T::LINCTL: SLVAREN Mask           */

#define UART_LINCTL_SLVDUEN_Pos          (3)                                               /*!< UART_T::LINCTL: SLVDUEN Position       */
#define UART_LINCTL_SLVDUEN_Msk          (0x1ul << UART_LINCTL_SLVDUEN_Pos)                /*!< UART_T::LINCTL: SLVDUEN Mask           */

#define UART_LINCTL_MUTE_Pos             (4)                                               /*!< UART_T::LINCTL: MUTE Position          */
#define UART_LINCTL_MUTE_Msk             (0x1ul << UART_LINCTL_MUTE_Pos)                   /*!< UART_T::LINCTL: MUTE Mask              */

#define UART_LINCTL_SENDH_Pos            (8)                                               /*!< UART_T::LINCTL: SENDH Position         */
#define UART_LINCTL_SENDH_Msk            (0x1ul << UART_LINCTL_SENDH_Pos)                  /*!< UART_T::LINCTL: SENDH Mask             */

#define UART_LINCTL_IDPEN_Pos            (9)                                               /*!< UART_T::LINCTL: IDPEN Position         */
#define UART_LINCTL_IDPEN_Msk            (0x1ul << UART_LINCTL_IDPEN_Pos)                  /*!< UART_T::LINCTL: IDPEN Mask             */

#define UART_LINCTL_BRKDETEN_Pos         (10)                                              /*!< UART_T::LINCTL: BRKDETEN Position      */
#define UART_LINCTL_BRKDETEN_Msk         (0x1ul << UART_LINCTL_BRKDETEN_Pos)               /*!< UART_T::LINCTL: BRKDETEN Mask          */

#define UART_LINCTL_LINRXOFF_Pos         (11)                                              /*!< UART_T::LINCTL: LINRXOFF Position      */
#define UART_LINCTL_LINRXOFF_Msk         (0x1ul << UART_LINCTL_LINRXOFF_Pos)               /*!< UART_T::LINCTL: LINRXOFF Mask          */

#define UART_LINCTL_BITERREN_Pos         (12)                                              /*!< UART_T::LINCTL: BITERREN Position      */
#define UART_LINCTL_BITERREN_Msk         (0x1ul << UART_LINCTL_BITERREN_Pos)               /*!< UART_T::LINCTL: BITERREN Mask          */

#define UART_LINCTL_BRKFL_Pos            (16)                                              /*!< UART_T::LINCTL: BRKFL Position         */
#define UART_LINCTL_BRKFL_Msk            (0xful << UART_LINCTL_BRKFL_Pos)                  /*!< UART_T::LINCTL: BRKFL Mask             */

#define UART_LINCTL_BSL_Pos              (20)                                              /*!< UART_T::LINCTL: BSL Position           */
#define UART_LINCTL_BSL_Msk              (0x3ul << UART_LINCTL_BSL_Pos)                    /*!< UART_T::LINCTL: BSL Mask               */

#define UART_LINCTL_HSEL_Pos             (22)                                              /*!< UART_T::LINCTL: HSEL Position          */
#define UART_LINCTL_HSEL_Msk             (0x3ul << UART_LINCTL_HSEL_Pos)                   /*!< UART_T::LINCTL: HSEL Mask              */

#define UART_LINCTL_PID_Pos              (24)                                              /*!< UART_T::LINCTL: PID Position           */
#define UART_LINCTL_PID_Msk              (0xfful << UART_LINCTL_PID_Pos)                   /*!< UART_T::LINCTL: PID Mask               */

#define UART_LINSTS_SLVHDETF_Pos         (0)                                               /*!< UART_T::LINSTS: SLVHDETF Position      */
#define UART_LINSTS_SLVHDETF_Msk         (0x1ul << UART_LINSTS_SLVHDETF_Pos)               /*!< UART_T::LINSTS: SLVHDETF Mask          */

#define UART_LINSTS_SLVHEF_Pos           (1)                                               /*!< UART_T::LINSTS: SLVHEF Position        */
#define UART_LINSTS_SLVHEF_Msk           (0x1ul << UART_LINSTS_SLVHEF_Pos)                 /*!< UART_T::LINSTS: SLVHEF Mask            */

#define UART_LINSTS_SLVIDPEF_Pos         (2)                                               /*!< UART_T::LINSTS: SLVIDPEF Position      */
#define UART_LINSTS_SLVIDPEF_Msk         (0x1ul << UART_LINSTS_SLVIDPEF_Pos)               /*!< UART_T::LINSTS: SLVIDPEF Mask          */

#define UART_LINSTS_SLVSYNCF_Pos         (3)                                               /*!< UART_T::LINSTS: SLVSYNCF Position      */
#define UART_LINSTS_SLVSYNCF_Msk         (0x1ul << UART_LINSTS_SLVSYNCF_Pos)               /*!< UART_T::LINSTS: SLVSYNCF Mask          */

#define UART_LINSTS_BRKDETF_Pos          (8)                                               /*!< UART_T::LINSTS: BRKDETF Position       */
#define UART_LINSTS_BRKDETF_Msk          (0x1ul << UART_LINSTS_BRKDETF_Pos)                /*!< UART_T::LINSTS: BRKDETF Mask           */

#define UART_LINSTS_BITEF_Pos            (9)                                               /*!< UART_T::LINSTS: BITEF Position         */
#define UART_LINSTS_BITEF_Msk            (0x1ul << UART_LINSTS_BITEF_Pos)                  /*!< UART_T::LINSTS: BITEF Mask             */

#define UART_BRCOMP_BRCOMP_Pos           (0)                                               /*!< UART_T::BRCOMP: BRCOMP Position        */
#define UART_BRCOMP_BRCOMP_Msk           (0x1fful << UART_BRCOMP_BRCOMP_Pos)               /*!< UART_T::BRCOMP: BRCOMP Mask            */

#define UART_BRCOMP_BRCOMPDEC_Pos        (31)                                              /*!< UART_T::BRCOMP: BRCOMPDEC Position     */
#define UART_BRCOMP_BRCOMPDEC_Msk        (0x1ul << UART_BRCOMP_BRCOMPDEC_Pos)              /*!< UART_T::BRCOMP: BRCOMPDEC Mask         */

#define UART_WKCTL_WKCTSEN_Pos           (0)                                               /*!< UART_T::WKCTL: WKCTSEN Position        */
#define UART_WKCTL_WKCTSEN_Msk           (0x1ul << UART_WKCTL_WKCTSEN_Pos)                 /*!< UART_T::WKCTL: WKCTSEN Mask            */

#define UART_WKCTL_WKDATEN_Pos           (1)                                               /*!< UART_T::WKCTL: WKDATEN Position        */
#define UART_WKCTL_WKDATEN_Msk           (0x1ul << UART_WKCTL_WKDATEN_Pos)                 /*!< UART_T::WKCTL: WKDATEN Mask            */

#define UART_WKCTL_WKRFRTEN_Pos          (2)                                               /*!< UART_T::WKCTL: WKRFRTEN Position       */
#define UART_WKCTL_WKRFRTEN_Msk          (0x1ul << UART_WKCTL_WKRFRTEN_Pos)                /*!< UART_T::WKCTL: WKRFRTEN Mask           */

#define UART_WKCTL_WKRS485EN_Pos         (3)                                               /*!< UART_T::WKCTL: WKRS485EN Position      */
#define UART_WKCTL_WKRS485EN_Msk         (0x1ul << UART_WKCTL_WKRS485EN_Pos)               /*!< UART_T::WKCTL: WKRS485EN Mask          */

#define UART_WKCTL_WKTOUTEN_Pos          (4)                                               /*!< UART_T::WKCTL: WKTOUTEN Position       */
#define UART_WKCTL_WKTOUTEN_Msk          (0x1ul << UART_WKCTL_WKTOUTEN_Pos)                /*!< UART_T::WKCTL: WKTOUTEN Mask           */

#define UART_WKSTS_CTSWKF_Pos            (0)                                               /*!< UART_T::WKSTS: CTSWKF Position         */
#define UART_WKSTS_CTSWKF_Msk            (0x1ul << UART_WKSTS_CTSWKF_Pos)                  /*!< UART_T::WKSTS: CTSWKF Mask             */

#define UART_WKSTS_DATWKF_Pos            (1)                                               /*!< UART_T::WKSTS: DATWKF Position         */
#define UART_WKSTS_DATWKF_Msk            (0x1ul << UART_WKSTS_DATWKF_Pos)                  /*!< UART_T::WKSTS: DATWKF Mask             */

#define UART_WKSTS_RFRTWKF_Pos           (2)                                               /*!< UART_T::WKSTS: RFRTWKF Position        */
#define UART_WKSTS_RFRTWKF_Msk           (0x1ul << UART_WKSTS_RFRTWKF_Pos)                 /*!< UART_T::WKSTS: RFRTWKF Mask            */

#define UART_WKSTS_RS485WKF_Pos          (3)                                               /*!< UART_T::WKSTS: RS485WKF Position       */
#define UART_WKSTS_RS485WKF_Msk          (0x1ul << UART_WKSTS_RS485WKF_Pos)                /*!< UART_T::WKSTS: RS485WKF Mask           */

#define UART_WKSTS_TOUTWKF_Pos           (4)                                               /*!< UART_T::WKSTS: TOUTWKF Position        */
#define UART_WKSTS_TOUTWKF_Msk           (0x1ul << UART_WKSTS_TOUTWKF_Pos)                 /*!< UART_T::WKSTS: TOUTWKF Mask            */

#define UART_DWKCOMP_STCOMP_Pos          (0)                                               /*!< UART_T::DWKCOMP: STCOMP Position       */
#define UART_DWKCOMP_STCOMP_Msk          (0xfffful << UART_DWKCOMP_STCOMP_Pos)             /*!< UART_T::DWKCOMP: STCOMP Mask           */


#define UART0                 ((UART_T *)   UART0_BA)
#define UART1                 ((UART_T *)   UART1_BA)
#define UART2                 ((UART_T *)   UART2_BA)
#define UART3                 ((UART_T *)   UART3_BA)
#define UART4                 ((UART_T *)   UART4_BA)
#define UART5                 ((UART_T *)   UART5_BA)
#define UART6                 ((UART_T *)   UART6_BA)
#define UART7                 ((UART_T *)   UART7_BA)
#define UART8                 ((UART_T *)   UART8_BA)
#define UART9                 ((UART_T *)   UART9_BA)


/** @addtogroup UART_EXPORTED_FUNCTIONS UART Exported Functions
  @{
*/


/**
 *    @brief        Calculate UART baudrate mode0 divider
 *
 *    @param[in]    u32SrcFreq      UART clock frequency
 *    @param[in]    u32BaudRate     Baudrate of UART module
 *
 *    @return       UART baudrate mode0 divider
 *
 *    @details      This macro calculate UART baudrate mode0 divider.
 *    \hideinitializer
 */
#define UART_BAUD_MODE0_DIVIDER(u32SrcFreq, u32BaudRate)    ((((u32SrcFreq) + ((u32BaudRate)*8ul)) / (u32BaudRate) >> 4ul)-2ul)


/**
 *    @brief        Calculate UART baudrate mode2 divider
 *
 *    @param[in]    u32SrcFreq      UART clock frequency
 *    @param[in]    u32BaudRate     Baudrate of UART module
 *
 *    @return       UART baudrate mode2 divider
 *
 *    @details      This macro calculate UART baudrate mode2 divider.
 *    \hideinitializer
 */
#define UART_BAUD_MODE2_DIVIDER(u32SrcFreq, u32BaudRate)    ((((u32SrcFreq) + ((u32BaudRate)/2ul)) / (u32BaudRate))-2ul)


/**
 *    @brief        Write UART data
 *
 *    @param[in]    uart    The pointer of the specified UART module
 *    @param[in]    u8Data  Data byte to transmit.
 *
 *    @return       None
 *
 *    @details      This macro write Data to Tx data register.
 *    \hideinitializer
 */
#define UART_WRITE(uart, u8Data)    ((uart)->DAT = (u8Data))


/**
 *    @brief        Read UART data
 *
 *    @param[in]    uart    The pointer of the specified UART module
 *
 *    @return       The oldest data byte in RX FIFO.
 *
 *    @details      This macro read Rx data register.
 *    \hideinitializer
 */
#define UART_READ(uart)    ((uart)->DAT)


/**
 *    @brief        Get Tx empty
 *
 *    @param[in]    uart    The pointer of the specified UART module
 *
 *    @retval       0   Tx FIFO is not empty
 *    @retval       >=1 Tx FIFO is empty
 *
 *    @details      This macro get Transmitter FIFO empty register value.
 *    \hideinitializer
 */
#define UART_GET_TX_EMPTY(uart)    ((uart)->FIFOSTS & UART_FIFOSTS_TXEMPTY_Msk)


/**
 *    @brief        Get Rx empty
 *
 *    @param[in]    uart    The pointer of the specified UART module
 *
 *    @retval       0   Rx FIFO is not empty
 *    @retval       >=1 Rx FIFO is empty
 *
 *    @details      This macro get Receiver FIFO empty register value.
 *    \hideinitializer
 */
#define UART_GET_RX_EMPTY(uart)    ((uart)->FIFOSTS & UART_FIFOSTS_RXEMPTY_Msk)


/**
 *    @brief        Check specified UART port transmission is over.
 *
 *    @param[in]    uart    The pointer of the specified UART module
 *
 *    @retval       0 Tx transmission is not over
 *    @retval       1 Tx transmission is over
 *
 *    @details      This macro return Transmitter Empty Flag register bit value.
 *                  It indicates if specified UART port transmission is over nor not.
 *    \hideinitializer
 */
#define UART_IS_TX_EMPTY(uart)    (((uart)->FIFOSTS & UART_FIFOSTS_TXEMPTYF_Msk) >> UART_FIFOSTS_TXEMPTYF_Pos)


/**
 *    @brief        Wait specified UART port transmission is over
 *
 *    @param[in]    uart    The pointer of the specified UART module
 *
 *    @return       None
 *
 *    @details      This macro wait specified UART port transmission is over.
 *    \hideinitializer
 */
#define UART_WAIT_TX_EMPTY(uart)    while(!((((uart)->FIFOSTS) & UART_FIFOSTS_TXEMPTYF_Msk) >> UART_FIFOSTS_TXEMPTYF_Pos))


/**
 *    @brief        Check RX is ready or not
 *
 *    @param[in]    uart    The pointer of the specified UART module
 *
 *    @retval       0 The number of bytes in the RX FIFO is less than the RFITL
 *    @retval       1 The number of bytes in the RX FIFO equals or larger than RFITL
 *
 *    @details      This macro check receive data available interrupt flag is set or not.
 *    \hideinitializer
 */
#define UART_IS_RX_READY(uart)    (((uart)->INTSTS & UART_INTSTS_RDAIF_Msk)>>UART_INTSTS_RDAIF_Pos)


/**
 *    @brief        Check TX FIFO is full or not
 *
 *    @param[in]    uart    The pointer of the specified UART module
 *
 *    @retval       1 TX FIFO is full
 *    @retval       0 TX FIFO is not full
 *
 *    @details      This macro check TX FIFO is full or not.
 *    \hideinitializer
 */
#define UART_IS_TX_FULL(uart)    (((uart)->FIFOSTS & UART_FIFOSTS_TXFULL_Msk)>>UART_FIFOSTS_TXFULL_Pos)


/**
 *    @brief        Check RX FIFO is full or not
 *
 *    @param[in]    uart    The pointer of the specified UART module
 *
 *    @retval       1 RX FIFO is full
 *    @retval       0 RX FIFO is not full
 *
 *    @details      This macro check RX FIFO is full or not.
 *    \hideinitializer
 */
#define UART_IS_RX_FULL(uart)    (((uart)->FIFOSTS & UART_FIFOSTS_RXFULL_Msk)>>UART_FIFOSTS_RXFULL_Pos)


/**
 *    @brief        Get Tx full register value
 *
 *    @param[in]    uart    The pointer of the specified UART module
 *
 *    @retval       0   Tx FIFO is not full.
 *    @retval       >=1 Tx FIFO is full.
 *
 *    @details      This macro get Tx full register value.
 *    \hideinitializer
 */
#define UART_GET_TX_FULL(uart)    ((uart)->FIFOSTS & UART_FIFOSTS_TXFULL_Msk)


/**
 *    @brief        Get Rx full register value
 *
 *    @param[in]    uart    The pointer of the specified UART module
 *
 *    @retval       0   Rx FIFO is not full.
 *    @retval       >=1 Rx FIFO is full.
 *
 *    @details      This macro get Rx full register value.
 *    \hideinitializer
 */
#define UART_GET_RX_FULL(uart)    ((uart)->FIFOSTS & UART_FIFOSTS_RXFULL_Msk)


/**
 *    @brief        Enable specified UART interrupt
 *
 *    @param[in]    uart        The pointer of the specified UART module
 *    @param[in]    u32eIntSel  Interrupt type select
 *                              - \ref UART_INTEN_ABRIEN_Msk     : Auto baud rate interrupt
 *                              - \ref UART_INTEN_WKIEN_Msk      : Wakeup interrupt
 *                              - \ref UART_INTEN_LINIEN_Msk     : Lin bus interrupt
 *                              - \ref UART_INTEN_BUFERRIEN_Msk  : Buffer Error interrupt
 *                              - \ref UART_INTEN_RXTOIEN_Msk    : Rx time-out interrupt
 *                              - \ref UART_INTEN_MODEMIEN_Msk   : Modem interrupt
 *                              - \ref UART_INTEN_RLSIEN_Msk     : Rx Line status interrupt
 *                              - \ref UART_INTEN_THREIEN_Msk    : Tx empty interrupt
 *                              - \ref UART_INTEN_RDAIEN_Msk     : Rx ready interrupt
 *
 *    @return       None
 *
 *    @details      This macro enable specified UART interrupt.
 *    \hideinitializer
 */
#define UART_ENABLE_INT(uart, u32eIntSel)    ((uart)->INTEN |= (u32eIntSel))


/**
 *    @brief        Disable specified UART interrupt
 *
 *    @param[in]    uart        The pointer of the specified UART module
 *    @param[in]    u32eIntSel  Interrupt type select
 *                              - \ref UART_INTEN_ABRIEN_Msk     : Auto baud rate interrupt
 *                              - \ref UART_INTEN_WKIEN_Msk      : Wakeup interrupt
 *                              - \ref UART_INTEN_LINIEN_Msk     : Lin bus interrupt
 *                              - \ref UART_INTEN_BUFERRIEN_Msk  : Buffer Error interrupt
 *                              - \ref UART_INTEN_RXTOIEN_Msk    : Rx time-out interrupt
 *                              - \ref UART_INTEN_MODEMIEN_Msk   : Modem status interrupt
 *                              - \ref UART_INTEN_RLSIEN_Msk     : Receive Line status interrupt
 *                              - \ref UART_INTEN_THREIEN_Msk    : Tx empty interrupt
 *                              - \ref UART_INTEN_RDAIEN_Msk     : Rx ready interrupt
 *
 *    @return       None
 *
 *    @details      This macro enable specified UART interrupt.
 *    \hideinitializer
 */
#define UART_DISABLE_INT(uart, u32eIntSel)    ((uart)->INTEN &= ~ (u32eIntSel))


/**
 *    @brief        Get specified interrupt flag/status
 *
 *    @param[in]    uart            The pointer of the specified UART module
 *    @param[in]    u32eIntTypeFlag Interrupt Type Flag, should be
 *                                  - \ref UART_INTSTS_HWBUFEINT_Msk : In DMA Mode, Buffer Error Interrupt Indicator
 *                                  - \ref UART_INTSTS_HWTOINT_Msk   : In DMA Mode, Time-out Interrupt Indicator
 *                                  - \ref UART_INTSTS_HWMODINT_Msk  : In DMA Mode, MODEM Status Interrupt Indicator
 *                                  - \ref UART_INTSTS_HWRLSINT_Msk  : In DMA Mode, Receive Line Status Interrupt Indicator
 *                                  - \ref UART_INTSTS_HWBUFEIF_Msk  : In DMA Mode, Buffer Error Interrupt Flag
 *                                  - \ref UART_INTSTS_HWTOIF_Msk    : In DMA Mode, Time-out Interrupt Flag
 *                                  - \ref UART_INTSTS_HWMODIF_Msk   : In DMA Mode, MODEM Interrupt Flag
 *                                  - \ref UART_INTSTS_HWRLSIF_Msk   : In DMA Mode, Receive Line Status Flag
 *                                  - \ref UART_INTSTS_LININT_Msk    : LIN Bus Interrupt Indicator
 *                                  - \ref UART_INTSTS_BUFERRINT_Msk : Buffer Error Interrupt Indicator
 *                                  - \ref UART_INTSTS_RXTOINT_Msk   : Time-out Interrupt Indicator
 *                                  - \ref UART_INTSTS_MODEMINT_Msk  : Modem Status Interrupt Indicator
 *                                  - \ref UART_INTSTS_RLSINT_Msk    : Receive Line Status Interrupt Indicator
 *                                  - \ref UART_INTSTS_THREINT_Msk   : Transmit Holding Register Empty Interrupt Indicator
 *                                  - \ref UART_INTSTS_RDAINT_Msk    : Receive Data Available Interrupt Indicator
 *                                  - \ref UART_INTSTS_LINIF_Msk     : LIN Bus Flag
 *                                  - \ref UART_INTSTS_BUFERRIF_Msk  : Buffer Error Interrupt Flag
 *                                  - \ref UART_INTSTS_RXTOIF_Msk    : Rx Time-out Interrupt Flag
 *                                  - \ref UART_INTSTS_MODEMIF_Msk   : Modem Interrupt Flag
 *                                  - \ref UART_INTSTS_RLSIF_Msk     : Receive Line Status Interrupt Flag
 *                                  - \ref UART_INTSTS_THREIF_Msk    : Tx Empty Interrupt Flag
 *                                  - \ref UART_INTSTS_RDAIF_Msk     : Rx Ready Interrupt Flag
 *
 *    @retval       0 The specified interrupt is not happened.
 *                  1 The specified interrupt is happened.
 *
 *    @details      This macro get specified interrupt flag or interrupt indicator status.
 *    \hideinitializer
 */
#define UART_GET_INT_FLAG(uart,u32eIntTypeFlag)    (((uart)->INTSTS & (u32eIntTypeFlag))?1:0)


/**
 *    @brief        Clear RS-485 Address Byte Detection Flag
 *
 *    @param[in]    uart    The pointer of the specified UART module
 *
 *    @return       None
 *
 *    @details      This macro clear RS-485 address byte detection flag.
 *    \hideinitializer
 */
#define UART_RS485_CLEAR_ADDR_FLAG(uart)    ((uart)->FIFOSTS = UART_FIFOSTS_ADDRDETF_Msk)


/**
 *    @brief        Get RS-485 Address Byte Detection Flag
 *
 *    @param[in]    uart    The pointer of the specified UART module
 *
 *    @retval       0 Receiver detects a data that is not an address bit.
 *    @retval       1 Receiver detects a data that is an address bit.
 *
 *    @details      This macro get RS-485 address byte detection flag.
 *    \hideinitializer
 */
#define UART_RS485_GET_ADDR_FLAG(uart)    (((uart)->FIFOSTS  & UART_FIFOSTS_ADDRDETF_Msk) >> UART_FIFOSTS_ADDRDETF_Pos)

/* Declare these inline functions here to avoid MISRA C 2004 rule 8.1 error */
void UART_CLEAR_RTS(UART_T *uart);
void UART_SET_RTS(UART_T *uart);

void UART_ClearIntFlag(UART_T *uart, uint32_t u32InterruptFlag);
void UART_Close(UART_T *uart);
void UART_DisableFlowCtrl(UART_T *uart);
void UART_DisableInt(UART_T  *uart, uint32_t u32InterruptFlag);
void UART_EnableFlowCtrl(UART_T *uart);
void UART_EnableInt(UART_T  *uart, uint32_t u32InterruptFlag);
void UART_Open(UART_T *uart, uint32_t u32baudrate);
uint32_t UART_Read(UART_T *uart, uint8_t pu8RxBuf[], uint32_t u32ReadBytes);
void UART_SetLineConfig(UART_T *uart, uint32_t u32baudrate, uint32_t u32data_width, uint32_t u32parity, uint32_t  u32stop_bits);
void UART_SetTimeoutCnt(UART_T *uart, uint32_t u32TOC);
void UART_SelectIrDAMode(UART_T *uart, uint32_t u32Buadrate, uint32_t u32Direction);
void UART_SelectRS485Mode(UART_T *uart, uint32_t u32Mode, uint32_t u32Addr);
void UART_SelectLINMode(UART_T *uart, uint32_t u32Mode, uint32_t u32BreakLength);
uint32_t UART_Write(UART_T *uart, uint8_t pu8TxBuf[], uint32_t u32WriteBytes);




/*@}*/ /* end of group UART_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group UART_Driver */

/*@}*/ /* end of group Standard_Driver */


#endif /*__NU_UART_H__*/

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
