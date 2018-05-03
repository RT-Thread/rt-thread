/*!
    \file  gd32f4xx_can.h
    \brief definitions for the CAN
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/

#ifndef GD32F4XX_CAN_H
#define GD32F4XX_CAN_H

#include "gd32f4xx.h"

/* CAN definitions */
#define CAN0                               CAN_BASE                      /*!< CAN0 base address */
#define CAN1                               (CAN0 + 0x00000400U)          /*!< CAN1 base address */

/* registers definitions */
#define CAN_CTL(canx)                      REG32((canx) + 0x00U)         /*!< CAN control register */
#define CAN_STAT(canx)                     REG32((canx) + 0x04U)         /*!< CAN status register */
#define CAN_TSTAT(canx)                    REG32((canx) + 0x08U)         /*!< CAN transmit status register*/
#define CAN_RFIFO0(canx)                   REG32((canx) + 0x0CU)         /*!< CAN receive FIFO0 register */
#define CAN_RFIFO1(canx)                   REG32((canx) + 0x10U)         /*!< CAN receive FIFO1 register */
#define CAN_INTEN(canx)                    REG32((canx) + 0x14U)         /*!< CAN interrupt enable register */
#define CAN_ERR(canx)                      REG32((canx) + 0x18U)         /*!< CAN error register */
#define CAN_BT(canx)                       REG32((canx) + 0x1CU)         /*!< CAN bit timing register */
#define CAN_TMI0(canx)                     REG32((canx) + 0x180U)        /*!< CAN transmit mailbox0 identifier register */
#define CAN_TMP0(canx)                     REG32((canx) + 0x184U)        /*!< CAN transmit mailbox0 property register */
#define CAN_TMDATA00(canx)                 REG32((canx) + 0x188U)        /*!< CAN transmit mailbox0 data0 register */
#define CAN_TMDATA10(canx)                 REG32((canx) + 0x18CU)        /*!< CAN transmit mailbox0 data1 register */
#define CAN_TMI1(canx)                     REG32((canx) + 0x190U)        /*!< CAN transmit mailbox1 identifier register */
#define CAN_TMP1(canx)                     REG32((canx) + 0x194U)        /*!< CAN transmit mailbox1 property register */
#define CAN_TMDATA01(canx)                 REG32((canx) + 0x198U)        /*!< CAN transmit mailbox1 data0 register */
#define CAN_TMDATA11(canx)                 REG32((canx) + 0x19CU)        /*!< CAN transmit mailbox1 data1 register */
#define CAN_TMI2(canx)                     REG32((canx) + 0x1A0U)        /*!< CAN transmit mailbox2 identifier register */
#define CAN_TMP2(canx)                     REG32((canx) + 0x1A4U)        /*!< CAN transmit mailbox2 property register */
#define CAN_TMDATA02(canx)                 REG32((canx) + 0x1A8U)        /*!< CAN transmit mailbox2 data0 register */
#define CAN_TMDATA12(canx)                 REG32((canx) + 0x1ACU)        /*!< CAN transmit mailbox2 data1 register */
#define CAN_RFIFOMI0(canx)                 REG32((canx) + 0x1B0U)        /*!< CAN receive FIFO0 mailbox identifier register */
#define CAN_RFIFOMP0(canx)                 REG32((canx) + 0x1B4U)        /*!< CAN receive FIFO0 mailbox property register */
#define CAN_RFIFOMDATA00(canx)             REG32((canx) + 0x1B8U)        /*!< CAN receive FIFO0 mailbox data0 register */
#define CAN_RFIFOMDATA10(canx)             REG32((canx) + 0x1CCU)        /*!< CAN receive FIFO0 mailbox data1 register */
#define CAN_RFIFOMI1(canx)                 REG32((canx) + 0x1C0U)        /*!< CAN receive FIFO1 mailbox identifier register */
#define CAN_RFIFOMP1(canx)                 REG32((canx) + 0x1C4U)        /*!< CAN receive FIFO1 mailbox property register */
#define CAN_RFIFOMDATA01(canx)             REG32((canx) + 0x1C8U)        /*!< CAN receive FIFO1 mailbox data0 register */
#define CAN_RFIFOMDATA11(canx)             REG32((canx) + 0x1CCU)        /*!< CAN receive FIFO1 mailbox data1 register */
#define CAN_FCTL(canx)                     REG32((canx) + 0x200U)        /*!< CAN filter control register */
#define CAN_FMCFG(canx)                    REG32((canx) + 0x204U)        /*!< CAN filter mode register */
#define CAN_FSCFG(canx)                    REG32((canx) + 0x20CU)        /*!< CAN filter scale register */
#define CAN_FAFIFO(canx)                   REG32((canx) + 0x214U)        /*!< CAN filter associated FIFO register */
#define CAN_FW(canx)                       REG32((canx) + 0x21CU)        /*!< CAN filter working register */
#define CAN_F0DATA0(canx)                  REG32((canx) + 0x240U)        /*!< CAN filter 0 data 0 register */
#define CAN_F1DATA0(canx)                  REG32((canx) + 0x248U)        /*!< CAN filter 1 data 0 register */
#define CAN_F2DATA0(canx)                  REG32((canx) + 0x250U)        /*!< CAN filter 2 data 0 register */
#define CAN_F3DATA0(canx)                  REG32((canx) + 0x258U)        /*!< CAN filter 3 data 0 register */
#define CAN_F4DATA0(canx)                  REG32((canx) + 0x260U)        /*!< CAN filter 4 data 0 register */
#define CAN_F5DATA0(canx)                  REG32((canx) + 0x268U)        /*!< CAN filter 5 data 0 register */
#define CAN_F6DATA0(canx)                  REG32((canx) + 0x270U)        /*!< CAN filter 6 data 0 register */
#define CAN_F7DATA0(canx)                  REG32((canx) + 0x278U)        /*!< CAN filter 7 data 0 register */
#define CAN_F8DATA0(canx)                  REG32((canx) + 0x280U)        /*!< CAN filter 8 data 0 register */
#define CAN_F9DATA0(canx)                  REG32((canx) + 0x288U)        /*!< CAN filter 9 data 0 register */
#define CAN_F10DATA0(canx)                 REG32((canx) + 0x290U)        /*!< CAN filter 10 data 0 register */
#define CAN_F11DATA0(canx)                 REG32((canx) + 0x298U)        /*!< CAN filter 11 data 0 register */
#define CAN_F12DATA0(canx)                 REG32((canx) + 0x2A0U)        /*!< CAN filter 12 data 0 register */
#define CAN_F13DATA0(canx)                 REG32((canx) + 0x2A8U)        /*!< CAN filter 13 data 0 register */
#define CAN_F14DATA0(canx)                 REG32((canx) + 0x2B0U)        /*!< CAN filter 14 data 0 register */
#define CAN_F15DATA0(canx)                 REG32((canx) + 0x2B8U)        /*!< CAN filter 15 data 0 register */
#define CAN_F16DATA0(canx)                 REG32((canx) + 0x2C0U)        /*!< CAN filter 16 data 0 register */
#define CAN_F17DATA0(canx)                 REG32((canx) + 0x2C8U)        /*!< CAN filter 17 data 0 register */
#define CAN_F18DATA0(canx)                 REG32((canx) + 0x2D0U)        /*!< CAN filter 18 data 0 register */
#define CAN_F19DATA0(canx)                 REG32((canx) + 0x2D8U)        /*!< CAN filter 19 data 0 register */
#define CAN_F20DATA0(canx)                 REG32((canx) + 0x2E0U)        /*!< CAN filter 20 data 0 register */
#define CAN_F21DATA0(canx)                 REG32((canx) + 0x2E8U)        /*!< CAN filter 21 data 0 register */
#define CAN_F22DATA0(canx)                 REG32((canx) + 0x2F0U)        /*!< CAN filter 22 data 0 register */
#define CAN_F23DATA0(canx)                 REG32((canx) + 0x3F8U)        /*!< CAN filter 23 data 0 register */
#define CAN_F24DATA0(canx)                 REG32((canx) + 0x300U)        /*!< CAN filter 24 data 0 register */
#define CAN_F25DATA0(canx)                 REG32((canx) + 0x308U)        /*!< CAN filter 25 data 0 register */
#define CAN_F26DATA0(canx)                 REG32((canx) + 0x310U)        /*!< CAN filter 26 data 0 register */
#define CAN_F27DATA0(canx)                 REG32((canx) + 0x318U)        /*!< CAN filter 27 data 0 register */
#define CAN_F0DATA1(canx)                  REG32((canx) + 0x244U)        /*!< CAN filter 0 data 1 register */
#define CAN_F1DATA1(canx)                  REG32((canx) + 0x24CU)        /*!< CAN filter 1 data 1 register */
#define CAN_F2DATA1(canx)                  REG32((canx) + 0x254U)        /*!< CAN filter 2 data 1 register */
#define CAN_F3DATA1(canx)                  REG32((canx) + 0x25CU)        /*!< CAN filter 3 data 1 register */
#define CAN_F4DATA1(canx)                  REG32((canx) + 0x264U)        /*!< CAN filter 4 data 1 register */
#define CAN_F5DATA1(canx)                  REG32((canx) + 0x26CU)        /*!< CAN filter 5 data 1 register */
#define CAN_F6DATA1(canx)                  REG32((canx) + 0x274U)        /*!< CAN filter 6 data 1 register */
#define CAN_F7DATA1(canx)                  REG32((canx) + 0x27CU)        /*!< CAN filter 7 data 1 register */
#define CAN_F8DATA1(canx)                  REG32((canx) + 0x284U)        /*!< CAN filter 8 data 1 register */
#define CAN_F9DATA1(canx)                  REG32((canx) + 0x28CU)        /*!< CAN filter 9 data 1 register */
#define CAN_F10DATA1(canx)                 REG32((canx) + 0x294U)        /*!< CAN filter 10 data 1 register */
#define CAN_F11DATA1(canx)                 REG32((canx) + 0x29CU)        /*!< CAN filter 11 data 1 register */
#define CAN_F12DATA1(canx)                 REG32((canx) + 0x2A4U)        /*!< CAN filter 12 data 1 register */
#define CAN_F13DATA1(canx)                 REG32((canx) + 0x2ACU)        /*!< CAN filter 13 data 1 register */
#define CAN_F14DATA1(canx)                 REG32((canx) + 0x2B4U)        /*!< CAN filter 14 data 1 register */
#define CAN_F15DATA1(canx)                 REG32((canx) + 0x2BCU)        /*!< CAN filter 15 data 1 register */
#define CAN_F16DATA1(canx)                 REG32((canx) + 0x2C4U)        /*!< CAN filter 16 data 1 register */
#define CAN_F17DATA1(canx)                 REG32((canx) + 0x24CU)        /*!< CAN filter 17 data 1 register */
#define CAN_F18DATA1(canx)                 REG32((canx) + 0x2D4U)        /*!< CAN filter 18 data 1 register */
#define CAN_F19DATA1(canx)                 REG32((canx) + 0x2DCU)        /*!< CAN filter 19 data 1 register */
#define CAN_F20DATA1(canx)                 REG32((canx) + 0x2E4U)        /*!< CAN filter 20 data 1 register */
#define CAN_F21DATA1(canx)                 REG32((canx) + 0x2ECU)        /*!< CAN filter 21 data 1 register */
#define CAN_F22DATA1(canx)                 REG32((canx) + 0x2F4U)        /*!< CAN filter 22 data 1 register */
#define CAN_F23DATA1(canx)                 REG32((canx) + 0x2FCU)        /*!< CAN filter 23 data 1 register */
#define CAN_F24DATA1(canx)                 REG32((canx) + 0x304U)        /*!< CAN filter 24 data 1 register */
#define CAN_F25DATA1(canx)                 REG32((canx) + 0x30CU)        /*!< CAN filter 25 data 1 register */
#define CAN_F26DATA1(canx)                 REG32((canx) + 0x314U)        /*!< CAN filter 26 data 1 register */
#define CAN_F27DATA1(canx)                 REG32((canx) + 0x31CU)        /*!< CAN filter 27 data 1 register */

/* CAN transmit mailbox bank */
#define CAN_TMI(canx, bank)                REG32((canx) + 0x180U + ((bank) * 0x10U))      /*!< CAN transmit mailbox identifier register */
#define CAN_TMP(canx, bank)                REG32((canx) + 0x184U + ((bank) * 0x10U))      /*!< CAN transmit mailbox property register */
#define CAN_TMDATA0(canx, bank)            REG32((canx) + 0x188U + ((bank) * 0x10U))      /*!< CAN transmit mailbox data0 register */
#define CAN_TMDATA1(canx, bank)            REG32((canx) + 0x18CU + ((bank) * 0x10U))      /*!< CAN transmit mailbox data1 register */

/* CAN filter bank */
#define CAN_FDATA0(canx, bank)             REG32((canx) + 0x240U + ((bank) * 0x8U) + 0x0U) /*!< CAN filter data 0 register */
#define CAN_FDATA1(canx, bank)             REG32((canx) + 0x240U + ((bank) * 0x8U) + 0x4U) /*!< CAN filter data 1 register */

/* CAN receive fifo mailbox bank */
#define CAN_RFIFOMI(canx, bank)            REG32((canx) + 0x1B0U + ((bank) * 0x10U))      /*!< CAN receive FIFO mailbox identifier register */
#define CAN_RFIFOMP(canx, bank)            REG32((canx) + 0x1B4U + ((bank) * 0x10U))      /*!< CAN receive FIFO mailbox property register */
#define CAN_RFIFOMDATA0(canx, bank)        REG32((canx) + 0x1B8U + ((bank) * 0x10U))      /*!< CAN receive FIFO mailbox data0 register */
#define CAN_RFIFOMDATA1(canx, bank)        REG32((canx) + 0x1BCU + ((bank) * 0x10U))      /*!< CAN receive FIFO mailbox data1 register */

/* bits definitions */
/* CAN_CTL */
#define CAN_CTL_IWMOD                      BIT(0)                       /*!< initial working mode */
#define CAN_CTL_SLPWMOD                    BIT(1)                       /*!< sleep working mode */
#define CAN_CTL_TFO                        BIT(2)                       /*!< transmit FIFO order */
#define CAN_CTL_RFOD                       BIT(3)                       /*!< receive FIFO overwrite disable */
#define CAN_CTL_ARD                        BIT(4)                       /*!< automatic retransmission disable */
#define CAN_CTL_AWU                        BIT(5)                       /*!< automatic wakeup */
#define CAN_CTL_ABOR                       BIT(6)                       /*!< automatic bus-off recovery */
#define CAN_CTL_TTC                        BIT(7)                       /*!< time triggered communication */
#define CAN_CTL_SWRST                      BIT(15)                      /*!< CAN software reset */
#define CAN_CTL_DFZ                        BIT(16)                      /*!< CAN debug freeze */

/* CAN_STAT */
#define CAN_STAT_IWS                       BIT(0)                       /*!< initial working state */
#define CAN_STAT_SLPWS                     BIT(1)                       /*!< sleep working state */
#define CAN_STAT_ERRIF                     BIT(2)                       /*!< error interrupt flag*/
#define CAN_STAT_WUIF                      BIT(3)                       /*!< status change interrupt flag of wakeup from sleep working mode */
#define CAN_STAT_SLPIF                     BIT(4)                       /*!< status change interrupt flag of sleep working mode entering */
#define CAN_STAT_TS                        BIT(8)                       /*!< transmitting state */
#define CAN_STAT_RS                        BIT(9)                       /*!< receiving state */
#define CAN_STAT_LASTRX                    BIT(10)                      /*!< last sample value of rx pin */
#define CAN_STAT_RXL                       BIT(11)                      /*!< CAN rx signal */

/* CAN_TSTAT */
#define CAN_TSTAT_MTF0                     BIT(0)                       /*!< mailbox0 transmit finished */
#define CAN_TSTAT_MTFNERR0                 BIT(1)                       /*!< mailbox0 transmit finished and no error */
#define CAN_TSTAT_MAL0                     BIT(2)                       /*!< mailbox0 arbitration lost */
#define CAN_TSTAT_MTE0                     BIT(3)                       /*!< mailbox0 transmit error */
#define CAN_TSTAT_MST0                     BIT(7)                       /*!< mailbox0 stop transmitting */
#define CAN_TSTAT_MTF1                     BIT(8)                       /*!< mailbox1 transmit finished */
#define CAN_TSTAT_MTFNERR1                 BIT(9)                       /*!< mailbox1 transmit finished and no error */
#define CAN_TSTAT_MAL1                     BIT(10)                      /*!< mailbox1 arbitration lost */
#define CAN_TSTAT_MTE1                     BIT(11)                      /*!< mailbox1 transmit error */
#define CAN_TSTAT_MST1                     BIT(15)                      /*!< mailbox1 stop transmitting */
#define CAN_TSTAT_MTF2                     BIT(16)                      /*!< mailbox2 transmit finished */
#define CAN_TSTAT_MTFNERR2                 BIT(17)                      /*!< mailbox2 transmit finished and no error */
#define CAN_TSTAT_MAL2                     BIT(18)                      /*!< mailbox2 arbitration lost */
#define CAN_TSTAT_MTE2                     BIT(19)                      /*!< mailbox2 transmit error */
#define CAN_TSTAT_MST2                     BIT(23)                      /*!< mailbox2 stop transmitting */
#define CAN_TSTAT_NUM                      BITS(24,25)                  /*!< mailbox number */
#define CAN_TSTAT_TME0                     BIT(26)                      /*!< transmit mailbox0 empty */
#define CAN_TSTAT_TME1                     BIT(27)                      /*!< transmit mailbox1 empty */
#define CAN_TSTAT_TME2                     BIT(28)                      /*!< transmit mailbox2 empty */
#define CAN_TSTAT_TMLS0                    BIT(29)                      /*!< last sending priority flag for mailbox0 */
#define CAN_TSTAT_TMLS1                    BIT(30)                      /*!< last sending priority flag for mailbox1 */
#define CAN_TSTAT_TMLS2                    BIT(31)                      /*!< last sending priority flag for mailbox2 */

/* CAN_RFIFO0 */
#define CAN_RFIFO0_RFL0                    BITS(0,1)                    /*!< receive FIFO0 length */
#define CAN_RFIFO0_RFF0                    BIT(3)                       /*!< receive FIFO0 full */
#define CAN_RFIFO0_RFO0                    BIT(4)                       /*!< receive FIFO0 overfull */
#define CAN_RFIFO0_RFD0                    BIT(5)                       /*!< receive FIFO0 dequeue */

/* CAN_RFIFO1 */
#define CAN_RFIFO1_RFL1                    BITS(0,1)                    /*!< receive FIFO1 length */
#define CAN_RFIFO1_RFF1                    BIT(3)                       /*!< receive FIFO1 full */
#define CAN_RFIFO1_RFO1                    BIT(4)                       /*!< receive FIFO1 overfull */
#define CAN_RFIFO1_RFD1                    BIT(5)                       /*!< receive FIFO1 dequeue */

/* CAN_INTEN */
#define CAN_INTEN_TMEIE                    BIT(0)                       /*!< transmit mailbox empty interrupt enable */
#define CAN_INTEN_RFNEIE0                  BIT(1)                       /*!< receive FIFO0 not empty interrupt enable */
#define CAN_INTEN_RFFIE0                   BIT(2)                       /*!< receive FIFO0 full interrupt enable */
#define CAN_INTEN_RFOIE0                   BIT(3)                       /*!< receive FIFO0 overfull interrupt enable */
#define CAN_INTEN_RFNEIE1                  BIT(4)                       /*!< receive FIFO1 not empty interrupt enable */
#define CAN_INTEN_RFFIE1                   BIT(5)                       /*!< receive FIFO1 full interrupt enable */
#define CAN_INTEN_RFOIE1                   BIT(6)                       /*!< receive FIFO1 overfull interrupt enable */
#define CAN_INTEN_WERRIE                   BIT(8)                       /*!< warning error interrupt enable */
#define CAN_INTEN_PERRIE                   BIT(9)                       /*!< passive error interrupt enable */
#define CAN_INTEN_BOIE                     BIT(10)                      /*!< bus-off interrupt enable */
#define CAN_INTEN_ERRNIE                   BIT(11)                      /*!< error number interrupt enable */
#define CAN_INTEN_ERRIE                    BIT(15)                      /*!< error interrupt enable */
#define CAN_INTEN_WUIE                     BIT(16)                      /*!< wakeup interrupt enable */
#define CAN_INTEN_SLPWIE                   BIT(17)                      /*!< sleep working interrupt enable */

/* CAN_ERR */
#define CAN_ERR_WERR                       BIT(0)                       /*!< warning error */
#define CAN_ERR_PERR                       BIT(1)                       /*!< passive error */
#define CAN_ERR_BOERR                      BIT(2)                       /*!< bus-off error */
#define CAN_ERR_ERRN                       BITS(4,6)                    /*!< error number */
#define CAN_ERR_TECNT                      BITS(16,23)                  /*!< transmit error count */
#define CAN_ERR_RECNT                      BITS(24,31)                  /*!< receive error count */

/* CAN_BT */
#define CAN_BT_BAUDPSC                     BITS(0,9)                    /*!< baudrate prescaler */
#define CAN_BT_BS1                         BITS(16,19)                  /*!< bit segment 1 */
#define CAN_BT_BS2                         BITS(20,22)                  /*!< bit segment 2 */
#define CAN_BT_SJW                         BITS(24,25)                  /*!< resynchronization jump width */
#define CAN_BT_LCMOD                       BIT(30)                      /*!< loopback communication mode */
#define CAN_BT_SCMOD                       BIT(31)                      /*!< silent communication mode */

/* CAN_TMIx */
#define CAN_TMI_TEN                        BIT(0)                       /*!< transmit enable */
#define CAN_TMI_FT                         BIT(1)                       /*!< frame type */
#define CAN_TMI_FF                         BIT(2)                       /*!< frame format */
#define CAN_TMI_EFID                       BITS(3,31)                   /*!< the frame identifier */
#define CAN_TMI_SFID                       BITS(21,31)                  /*!< the frame identifier */

/* CAN_TMPx */
#define CAN_TMP_DLENC                      BITS(0,3)                    /*!< data length code */
#define CAN_TMP_TSEN                       BIT(8)                       /*!< time stamp enable */
#define CAN_TMP_TS                         BITS(16,31)                  /*!< time stamp */

/* CAN_TMDATA0x */
#define CAN_TMDATA0_DB0                    BITS(0,7)                    /*!< transmit data byte 0 */
#define CAN_TMDATA0_DB1                    BITS(8,15)                   /*!< transmit data byte 1 */
#define CAN_TMDATA0_DB2                    BITS(16,23)                  /*!< transmit data byte 2 */
#define CAN_TMDATA0_DB3                    BITS(24,31)                  /*!< transmit data byte 3 */

/* CAN_TMDATA1x */
#define CAN_TMDATA1_DB4                    BITS(0,7)                    /*!< transmit data byte 4 */
#define CAN_TMDATA1_DB5                    BITS(8,15)                   /*!< transmit data byte 5 */
#define CAN_TMDATA1_DB6                    BITS(16,23)                  /*!< transmit data byte 6 */
#define CAN_TMDATA1_DB7                    BITS(24,31)                  /*!< transmit data byte 7 */

/* CAN_RFIFOMIx */
#define CAN_RFIFOMI_FT                     BIT(1)                       /*!< frame type */
#define CAN_RFIFOMI_FF                     BIT(2)                       /*!< frame format */
#define CAN_RFIFOMI_EFID                   BITS(3,31)                   /*!< the frame identifier */
#define CAN_RFIFOMI_SFID                   BITS(21,31)                  /*!< the frame identifier */

/* CAN_RFIFOMPx */
#define CAN_RFIFOMP_DLENC                  BITS(0,3)                    /*!< receive data length code */
#define CAN_RFIFOMP_FI                     BITS(8,15)                   /*!< filter index */
#define CAN_RFIFOMP_TS                     BITS(16,31)                  /*!< time stamp */

/* CAN_RFIFOMDATA0x */
#define CAN_RFIFOMDATA0_DB0                BITS(0,7)                    /*!< receive data byte 0 */
#define CAN_RFIFOMDATA0_DB1                BITS(8,15)                   /*!< receive data byte 1 */
#define CAN_RFIFOMDATA0_DB2                BITS(16,23)                  /*!< receive data byte 2 */
#define CAN_RFIFOMDATA0_DB3                BITS(24,31)                  /*!< receive data byte 3 */

/* CAN_RFIFOMDATA1x */
#define CAN_RFIFOMDATA1_DB4                BITS(0,7)                    /*!< receive data byte 4 */
#define CAN_RFIFOMDATA1_DB5                BITS(8,15)                   /*!< receive data byte 5 */
#define CAN_RFIFOMDATA1_DB6                BITS(16,23)                  /*!< receive data byte 6 */
#define CAN_RFIFOMDATA1_DB7                BITS(24,31)                  /*!< receive data byte 7 */

/* CAN_FCTL */
#define CAN_FCTL_FLD                       BIT(0)                       /*!< filter lock disable */
#define CAN_FCTL_HBC1F                     BITS(8,13)                   /*!< header bank of CAN1 filter */

/* CAN_FMCFG */
#define CAN_FMCFG_FMOD(regval)             BIT(regval)                  /*!< filter mode, list or mask*/

/* CAN_FSCFG */
#define CAN_FSCFG_FS(regval)               BIT(regval)                  /*!< filter scale, 32 bits or 16 bits*/

/* CAN_FAFIFO */
#define CAN_FAFIFOR_FAF(regval)            BIT(regval)                  /*!< filter associated with FIFO */

/* CAN_FW */
#define CAN_FW_FW(regval)                  BIT(regval)                  /*!< filter working */

/* consts definitions */
/* define the CAN bit position and its register index offset */
#define CAN_REGIDX_BIT(regidx, bitpos)    (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))
#define CAN_REG_VAL(canx, offset)         (REG32((canx) + ((uint32_t)(offset) >> 6)))
#define CAN_BIT_POS(val)                  ((uint32_t)(val) & 0x1FU)

/* register offset */
#define STAT_REG_OFFSET                    ((uint8_t)0x04U)             /*!< STAT register offset */
#define TSTAT_REG_OFFSET                   ((uint8_t)0x08U)             /*!< TSTAT register offset */
#define RFIFO0_REG_OFFSET                  ((uint8_t)0x0CU)             /*!< RFIFO0 register offset */
#define RFIFO1_REG_OFFSET                  ((uint8_t)0x10U)             /*!< RFIFO1 register offset */
#define ERR_REG_OFFSET                     ((uint8_t)0x18U)             /*!< ERR register offset */

/* CAN flags */
typedef enum
{
    /* flags in TSTAT register */
    CAN_FLAG_MTE2 = CAN_REGIDX_BIT(TSTAT_REG_OFFSET, 19U),              /*!< mailbox 2 transmit error */ 
    CAN_FLAG_MTE1 = CAN_REGIDX_BIT(TSTAT_REG_OFFSET, 11U),              /*!< mailbox 1 transmit error */ 
    CAN_FLAG_MTE0 = CAN_REGIDX_BIT(TSTAT_REG_OFFSET, 3U),               /*!< mailbox 0 transmit error */ 
    CAN_FLAG_MTF2 = CAN_REGIDX_BIT(TSTAT_REG_OFFSET, 16U),              /*!< mailbox 2 transmit finished */ 
    CAN_FLAG_MTF1 = CAN_REGIDX_BIT(TSTAT_REG_OFFSET, 8U),               /*!< mailbox 1 transmit finished */ 
    CAN_FLAG_MTF0 = CAN_REGIDX_BIT(TSTAT_REG_OFFSET, 0U),               /*!< mailbox 0 transmit finished */ 
    /* flags in RFIFO0 register */
    CAN_FLAG_RFO0 = CAN_REGIDX_BIT(RFIFO0_REG_OFFSET, 4U),              /*!< receive FIFO0 overfull */ 
    CAN_FLAG_RFF0 = CAN_REGIDX_BIT(RFIFO0_REG_OFFSET, 3U),              /*!< receive FIFO0 full */ 
    /* flags in RFIFO1 register */
    CAN_FLAG_RFO1 = CAN_REGIDX_BIT(RFIFO1_REG_OFFSET, 4U),              /*!< receive FIFO1 overfull */ 
    CAN_FLAG_RFF1 = CAN_REGIDX_BIT(RFIFO1_REG_OFFSET, 3U),              /*!< receive FIFO1 full */ 
    /* flags in ERR register */
    CAN_FLAG_BOERR = CAN_REGIDX_BIT(ERR_REG_OFFSET, 2U),                /*!< bus-off error */ 
    CAN_FLAG_PERR = CAN_REGIDX_BIT(ERR_REG_OFFSET, 1U),                 /*!< passive error */ 
    CAN_FLAG_WERR = CAN_REGIDX_BIT(ERR_REG_OFFSET, 0U),                 /*!< warning error */ 
}can_flag_enum;

/* CAN interrupt flags */
typedef enum
{
    /* interrupt flags in STAT register */
    CAN_INT_SLPIF = CAN_REGIDX_BIT(STAT_REG_OFFSET, 4U),                /*!< status change interrupt flag of sleep working mode entering */ 
    CAN_INT_WUIF = CAN_REGIDX_BIT(STAT_REG_OFFSET, 3U),                 /*!< status change interrupt flag of wakeup from sleep working mode */ 
    CAN_INT_ERRIF = CAN_REGIDX_BIT(STAT_REG_OFFSET, 2U),                /*!< error interrupt flag */ 
}can_interrupt_flag_enum;

/* CAN initiliaze parameters struct */
typedef struct
{
    uint8_t working_mode;                                               /*!< CAN working mode */ 
    uint8_t resync_jump_width;                                          /*!< CAN resynchronization jump width */
    uint8_t time_segment_1;                                             /*!< time segment 1 */
    uint8_t time_segment_2;                                             /*!< time segment 2 */
    ControlStatus time_triggered;                                       /*!< time triggered communication mode */
    ControlStatus auto_bus_off_recovery;                                /*!< automatic bus-off recovery */
    ControlStatus auto_wake_up;                                         /*!< automatic wake-up mode */
    ControlStatus auto_retrans;                                         /*!< automatic retransmission mode */
    ControlStatus rec_fifo_overwrite;                                   /*!< receive FIFO overwrite mode */
    ControlStatus trans_fifo_order;                                     /*!< transmit FIFO order */
    uint16_t prescaler;                                                 /*!< baudrate prescaler */
}can_parameter_struct;

/* CAN transmit message struct */
typedef struct
{
    uint32_t tx_sfid;                                                   /*!< standard format frame identifier */
    uint32_t tx_efid;                                                   /*!< extended format frame identifier */
    uint8_t tx_ff;                                                      /*!< format of frame, standard or extended format */
    uint8_t tx_ft;                                                      /*!< type of frame, data or remote */
    uint8_t tx_dlen;                                                    /*!< data length */
    uint8_t tx_data[8];                                                 /*!< transmit data */
}can_trasnmit_message_struct;

/* CAN receive message struct */
typedef struct
{
    uint32_t rx_sfid;                                                   /*!< standard format frame identifier */
    uint32_t rx_efid;                                                   /*!< extended format frame identifier */
    uint8_t rx_ff;                                                      /*!< format of frame, standard or extended format */
    uint8_t rx_ft;                                                      /*!< type of frame, data or remote */
    uint8_t rx_dlen;                                                    /*!< data length */
    uint8_t rx_data[8];                                                 /*!< receive data */
    uint8_t rx_fi;                                                      /*!< filtering index */
} can_receive_message_struct;

/* CAN filter parameters struct */
typedef struct
{
    uint16_t filter_list_high;                                          /*!< filter list number high bits*/
    uint16_t filter_list_low;                                           /*!< filter list number low bits */
    uint16_t filter_mask_high;                                          /*!< filter mask number high bits */
    uint16_t filter_mask_low;                                           /*!< filter mask number low bits */
    uint16_t filter_fifo_number;                                        /*!< receive FIFO associated with the filter */
    uint16_t filter_number;                                             /*!< filter number */
    uint16_t filter_mode;                                               /*!< filter mode, list or mask */
    uint16_t filter_bits;                                               /*!< filter scale */
    ControlStatus filter_enable;                                        /*!< filter work or not */
}can_filter_parameter_struct;

/* CAN errors */
typedef enum
{
    CAN_ERROR_NONE = 0,                                                 /*!< no error */
    CAN_ERROR_FILL,                                                     /*!< fill error */
    CAN_ERROR_FORMATE,                                                  /*!< format error */
    CAN_ERROR_ACK,                                                      /*!< ACK error */
    CAN_ERROR_BITRECESSIVE,                                             /*!< bit recessive error */
    CAN_ERROR_BITDOMINANTER,                                            /*!< bit dominant error */
    CAN_ERROR_CRC,                                                      /*!< CRC error */
    CAN_ERROR_SOFTWARECFG                                               /*!< software configure */
}can_error_enum;

/* transmit states */
typedef enum
{
    CAN_TRANSMIT_FAILED = 0,                                            /*!< CAN transmitted failure */
    CAN_TRANSMIT_OK = 1,                                                /*!< CAN transmitted success */
    CAN_TRANSMIT_PENDING = 2,                                           /*!< CAN transmitted pending */
    CAN_TRANSMIT_NOMAILBOX = 4,                                         /*!< no empty mailbox to be used for CAN */
}can_transmit_state_enum;

/* CAN baudrate prescaler*/
#define BT_BAUDPSC(regval)                 (BITS(0,9) & ((uint32_t)(regval) << 0))

/* CAN bit segment 1*/
#define BT_BS1(regval)                     (BITS(16,19) & ((uint32_t)(regval) << 16))

/* CAN bit segment 2*/
#define BT_BS2(regval)                     (BITS(20,22) & ((uint32_t)(regval) << 20))

/* CAN resynchronization jump width*/
#define BT_SJW(regval)                     (BITS(24,25) & ((uint32_t)(regval) << 24))

/* CAN communication mode*/
#define BT_MODE(regval)                    (BITS(30,31) & ((uint32_t)(regval) << 30))

/* CAN FDATA high 16 bits */
#define FDATA_MASK_HIGH(regval)            (BITS(16,31) & ((uint32_t)(regval) << 16))

/* CAN FDATA low 16 bits */
#define FDATA_MASK_LOW(regval)             (BITS(0,15) & ((uint32_t)(regval) << 0))

/* CAN1 filter start bank_number*/
#define FCTL_HBC1F(regval)                 (BITS(8,13) & ((uint32_t)(regval) << 8))

/* CAN transmit mailbox extended identifier*/
#define TMI_EFID(regval)                   (BITS(3,31) & ((uint32_t)(regval) << 3))

/* CAN transmit mailbox standard identifier*/
#define TMI_SFID(regval)                   (BITS(21,31) & ((uint32_t)(regval) << 21))

/* transmit data byte 0 */
#define TMDATA0_DB0(regval)                (BITS(0,7) & ((uint32_t)(regval) << 0))

/* transmit data byte 1 */
#define TMDATA0_DB1(regval)                (BITS(8,15) & ((uint32_t)(regval) << 8))

/* transmit data byte 2 */
#define TMDATA0_DB2(regval)                (BITS(16,23) & ((uint32_t)(regval) << 16))

/* transmit data byte 3 */                 
#define TMDATA0_DB3(regval)                (BITS(24,31) & ((uint32_t)(regval) << 24))

/* transmit data byte 4 */                 
#define TMDATA1_DB4(regval)                (BITS(0,7) & ((uint32_t)(regval) << 0))

/* transmit data byte 5 */                 
#define TMDATA1_DB5(regval)                (BITS(8,15) & ((uint32_t)(regval) << 8))

/* transmit data byte 6 */                 
#define TMDATA1_DB6(regval)                (BITS(16,23) & ((uint32_t)(regval) << 16))

/* transmit data byte 7 */                 
#define TMDATA1_DB7(regval)                (BITS(24,31) & ((uint32_t)(regval) << 24))

/* receive mailbox extended identifier*/
#define RFIFOMI_EFID(regval)               GET_BITS((uint32_t)(regval), 3, 31)

/* receive mailbox standrad identifier*/
#define RFIFOMI_SFID(regval)               GET_BITS((uint32_t)(regval), 21, 31)

/* receive data length */
#define RFIFOMP_DLENC(regval)              GET_BITS((uint32_t)(regval), 0, 3)

#define RFIFOMP_FI(regval)                 GET_BITS((uint32_t)(regval), 8, 15)

/* receive data byte 0 */
#define RFIFOMDATA0_DB0(regval)            GET_BITS((uint32_t)(regval), 0, 7)

/* receive data byte 1 */
#define RFIFOMDATA0_DB1(regval)            GET_BITS((uint32_t)(regval), 8, 15)

/* receive data byte 2 */
#define RFIFOMDATA0_DB2(regval)            GET_BITS((uint32_t)(regval), 16, 23)

/* receive data byte 3 */
#define RFIFOMDATA0_DB3(regval)            GET_BITS((uint32_t)(regval), 24, 31)

/* receive data byte 4 */
#define RFIFOMDATA1_DB4(regval)            GET_BITS((uint32_t)(regval), 0, 7)

/* receive data byte 5 */
#define RFIFOMDATA1_DB5(regval)            GET_BITS((uint32_t)(regval), 8, 15)

/* receive data byte 6 */
#define RFIFOMDATA1_DB6(regval)            GET_BITS((uint32_t)(regval), 16, 23)

/* receive data byte 7 */
#define RFIFOMDATA1_DB7(regval)            GET_BITS((uint32_t)(regval), 24, 31)

/* CAN errors */
#define ERR_ERRN(regval)                   (BITS(4,6) & ((uint32_t)(regval) << 4))
#define CAN_ERRN_0                         ERR_ERRN(0)                  /* no error */
#define CAN_ERRN_1                         ERR_ERRN(1)                  /*!< fill error */
#define CAN_ERRN_2                         ERR_ERRN(2)                  /*!< format error */
#define CAN_ERRN_3                         ERR_ERRN(3)                  /*!< ACK error */
#define CAN_ERRN_4                         ERR_ERRN(4)                  /*!< bit recessive error */
#define CAN_ERRN_5                         ERR_ERRN(5)                  /*!< bit dominant error */
#define CAN_ERRN_6                         ERR_ERRN(6)                  /*!< CRC error */
#define CAN_ERRN_7                         ERR_ERRN(7)                  /*!< software error */

#define CAN_STATE_PENDING                  ((uint32_t)0x00000000U)      /*!< CAN pending */

/* CAN communication mode */
#define CAN_NORMAL_MODE                    ((uint8_t)0x00U)             /*!< normal communication mode */
#define CAN_LOOPBACK_MODE                  ((uint8_t)0x01U)             /*!< loopback communication mode */
#define CAN_SILENT_MODE                    ((uint8_t)0x02U)             /*!< silent communication mode */
#define CAN_SILENT_LOOPBACK_MODE           ((uint8_t)0x03U)             /*!< loopback and silent communication mode */

/* CAN resynchronisation jump width */
#define CAN_BT_SJW_1TQ                     ((uint8_t)0x00U)             /*!< 1 time quanta */
#define CAN_BT_SJW_2TQ                     ((uint8_t)0x01U)             /*!< 2 time quanta */
#define CAN_BT_SJW_3TQ                     ((uint8_t)0x02U)             /*!< 3 time quanta */
#define CAN_BT_SJW_4TQ                     ((uint8_t)0x03U)             /*!< 4 time quanta */

/* CAN time segment 1 */
#define CAN_BT_BS1_1TQ                     ((uint8_t)0x00U)             /*!< 1 time quanta */
#define CAN_BT_BS1_2TQ                     ((uint8_t)0x01U)             /*!< 2 time quanta */
#define CAN_BT_BS1_3TQ                     ((uint8_t)0x02U)             /*!< 3 time quanta */
#define CAN_BT_BS1_4TQ                     ((uint8_t)0x03U)             /*!< 4 time quanta */
#define CAN_BT_BS1_5TQ                     ((uint8_t)0x04U)             /*!< 5 time quanta */
#define CAN_BT_BS1_6TQ                     ((uint8_t)0x05U)             /*!< 6 time quanta */
#define CAN_BT_BS1_7TQ                     ((uint8_t)0x06U)             /*!< 7 time quanta */
#define CAN_BT_BS1_8TQ                     ((uint8_t)0x07U)             /*!< 8 time quanta */
#define CAN_BT_BS1_9TQ                     ((uint8_t)0x08U)             /*!< 9 time quanta */
#define CAN_BT_BS1_10TQ                    ((uint8_t)0x09U)             /*!< 10 time quanta */
#define CAN_BT_BS1_11TQ                    ((uint8_t)0x0AU)             /*!< 11 time quanta */
#define CAN_BT_BS1_12TQ                    ((uint8_t)0x0BU)             /*!< 12 time quanta */
#define CAN_BT_BS1_13TQ                    ((uint8_t)0x0CU)             /*!< 13 time quanta */
#define CAN_BT_BS1_14TQ                    ((uint8_t)0x0DU)             /*!< 14 time quanta */
#define CAN_BT_BS1_15TQ                    ((uint8_t)0x0EU)             /*!< 15 time quanta */
#define CAN_BT_BS1_16TQ                    ((uint8_t)0x0FU)             /*!< 16 time quanta */

/* CAN time segment 2 */
#define CAN_BT_BS2_1TQ                     ((uint8_t)0x00U)             /*!< 1 time quanta */
#define CAN_BT_BS2_2TQ                     ((uint8_t)0x01U)             /*!< 2 time quanta */
#define CAN_BT_BS2_3TQ                     ((uint8_t)0x02U)             /*!< 3 time quanta */
#define CAN_BT_BS2_4TQ                     ((uint8_t)0x03U)             /*!< 4 time quanta */
#define CAN_BT_BS2_5TQ                     ((uint8_t)0x04U)             /*!< 5 time quanta */
#define CAN_BT_BS2_6TQ                     ((uint8_t)0x05U)             /*!< 6 time quanta */
#define CAN_BT_BS2_7TQ                     ((uint8_t)0x06U)             /*!< 7 time quanta */
#define CAN_BT_BS2_8TQ                     ((uint8_t)0x07U)             /*!< 8 time quanta */

/* CAN mailbox number */
#define CAN_MAILBOX0                       ((uint8_t)0x00U)             /*!< mailbox0 */
#define CAN_MAILBOX1                       ((uint8_t)0x01U)             /*!< mailbox1 */
#define CAN_MAILBOX2                       ((uint8_t)0x02U)             /*!< mailbox2 */
#define CAN_NOMAILBOX                      ((uint8_t)0x03U)             /*!< no mailbox empty */

/* CAN frame format */
#define CAN_FF_STANDARD                    ((uint32_t)0x00000000U)      /*!< standard frame */
#define CAN_FF_EXTENDED                    ((uint32_t)0x00000004U)      /*!< extended frame */

/* CAN receive fifo */
#define CAN_FIFO0                          ((uint8_t)0x00U)             /*!< receive FIFO0 */
#define CAN_FIFO1                          ((uint8_t)0x01U)             /*!< receive FIFO1 */

/* frame number of receive fifo */
#define CAN_RFIFO_RFL0_MASK                ((uint32_t)0x00000003U)      /*!< mask for frame number in receive FIFO0 */

#define CAN_SFID_MASK                      ((uint32_t)0x000007FFU)      /*!< mask of standard identifier */
#define CAN_EFID_MASK                      ((uint32_t)0x1FFFFFFFU)      /*!< mask of extended identifier */

/* CAN working mode */
#define CAN_MODE_INITIALIZE                ((uint8_t)0x01U)             /*!< CAN initialize mode */
#define CAN_MODE_NORMAL                    ((uint8_t)0x02U)             /*!< CAN normal mode */
#define CAN_MODE_SLEEP                     ((uint8_t)0x04U)             /*!< CAN sleep mode */

/* filter bits */
#define CAN_FILTERBITS_16BIT               ((uint8_t)0x00U)             /*!< CAN filter 16 bits */
#define CAN_FILTERBITS_32BIT               ((uint8_t)0x01U)             /*!< CAN filter 32 bits */

/* filter mode */
#define CAN_FILTERMODE_MASK                ((uint8_t)0x00U)             /*!< mask mode */
#define CAN_FILTERMODE_LIST                ((uint8_t)0x01U)             /*!< list mode */

/* filter 16 bits mask */
#define CAN_FILTER_MASK_16BITS             ((uint32_t)0x0000FFFFU) 

/* frame type */
#define CAN_FT_DATA                        ((uint32_t)0x00000000U)      /*!< data frame */
#define CAN_FT_REMOTE                      ((uint32_t)0x00000002U)      /*!< remote frame */

/* CAN timeout */
#define CAN_TIMEOUT                        ((uint32_t)0x0000FFFFU)      /*!< timeout value */

/* function declarations */
/* initialization functions */
/* CAN deinit */
void can_deinit(uint32_t can_periph);
/* CAN init */
ErrStatus can_init(uint32_t can_periph, can_parameter_struct* can_parameter_init);

/* transmit functions */
/* CAN transmit message */
uint8_t can_message_transmit(uint32_t can_periph, can_trasnmit_message_struct* transmit_message);
/* CAN transmit state */
can_transmit_state_enum can_transmit_states(uint32_t can_periph, uint8_t mailbox_number);
/* CAN stop transmission */
void can_transmission_stop(uint32_t can_periph, uint8_t mailbox_number);
/* CAN transmit error number */
uint8_t can_transmit_error_number(uint32_t can_periph);

/* filter functions */
/* CAN filter init */
void can_filter_init(can_filter_parameter_struct* can_filter_parameter_init);
/* set can1 fliter start bank number */
void can1_filter_start_bank(uint8_t start_bank);

/* enable functions */
/* CAN debug freeze enable */
void can_debug_freeze_enable(uint32_t can_periph);
/* CAN debug freeze disable */
void can_debug_freeze_disable(uint32_t can_periph);
/* CAN time triggle mode enable */
void can_time_trigger_mode_enable(uint32_t can_periph);
/* CAN time triggle mode disable */
void can_time_trigger_mode_disable(uint32_t can_periph);
/* CAN interrupt enable */
void can_interrupt_enable(uint32_t can_periph, uint32_t interrupt);
/* CAN interrupt disable */
void can_interrupt_disable(uint32_t can_periph, uint32_t interrupt);

/* receive functions */
/* CAN receive message */
void can_message_receive(uint32_t can_periph, uint8_t fifo_number, can_receive_message_struct* receive_message);
/* CAN release fifo */
void can_fifo_release(uint32_t can_periph, uint8_t fifo_number);
/* CAN receive message length */
uint8_t can_receive_message_length(uint32_t can_periph, uint8_t fifo_number);
/* CAN receive error number */
uint8_t can_receive_error_number(uint32_t can_periph);

/* mode functions */
/* CAN working mode */
ErrStatus can_working_mode_set(uint32_t can_periph, uint8_t working_mode);
/* CAN wakeup from sleep mode */
ErrStatus can_wakeup(uint32_t can_periph);

/* flag functions */
/* CAN get error */
can_error_enum can_error_get(uint32_t can_periph);
/* CAN get flag state */
FlagStatus can_flag_get(uint32_t can_periph, can_flag_enum flag);
/* CAN clear flag state */
void can_flag_clear(uint32_t can_periph, can_flag_enum flag);
/* CAN get interrupt flag state */
FlagStatus can_interrupt_flag_get(uint32_t can_periph, can_interrupt_flag_enum flag);
/* CAN clear interrupt flag state */
void can_interrupt_flag_clear(uint32_t can_periph, can_interrupt_flag_enum flag);

#endif /* GD32F4XX_CAN_H */
