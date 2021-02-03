/**
 * \file IfxAsclin_regdef.h
 * \brief
 * \copyright Copyright (c) 2015 Infineon Technologies AG. All rights reserved.
 *
 * Version: TC26XB_UM_V1.2.R0
 * Specification: tc26xB_um_v1.2_MCSFR.xml (Revision: UM_V1.2)
 * MAY BE CHANGED BY USER [yes/no]: No
 *
 *                                 IMPORTANT NOTICE
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * \defgroup IfxLld_Asclin Asclin
 * \ingroup IfxLld
 * 
 * \defgroup IfxLld_Asclin_Bitfields Bitfields
 * \ingroup IfxLld_Asclin
 * 
 * \defgroup IfxLld_Asclin_union Union
 * \ingroup IfxLld_Asclin
 * 
 * \defgroup IfxLld_Asclin_struct Struct
 * \ingroup IfxLld_Asclin
 * 
 */
#ifndef IFXASCLIN_REGDEF_H
#define IFXASCLIN_REGDEF_H 1
/******************************************************************************/
#include "Ifx_TypesReg.h"
/******************************************************************************/
/** \addtogroup IfxLld_Asclin_Bitfields
 * \{  */

/** \brief  Access Enable Register 0 */
typedef struct _Ifx_ASCLIN_ACCEN0_Bits
{
    unsigned int EN0:1;                     /**< \brief [0:0] Access Enable for Master TAG ID 0 (rw) */
    unsigned int EN1:1;                     /**< \brief [1:1] Access Enable for Master TAG ID 1 (rw) */
    unsigned int EN2:1;                     /**< \brief [2:2] Access Enable for Master TAG ID 2 (rw) */
    unsigned int EN3:1;                     /**< \brief [3:3] Access Enable for Master TAG ID 3 (rw) */
    unsigned int EN4:1;                     /**< \brief [4:4] Access Enable for Master TAG ID 4 (rw) */
    unsigned int EN5:1;                     /**< \brief [5:5] Access Enable for Master TAG ID 5 (rw) */
    unsigned int EN6:1;                     /**< \brief [6:6] Access Enable for Master TAG ID 6 (rw) */
    unsigned int EN7:1;                     /**< \brief [7:7] Access Enable for Master TAG ID 7 (rw) */
    unsigned int EN8:1;                     /**< \brief [8:8] Access Enable for Master TAG ID 8 (rw) */
    unsigned int EN9:1;                     /**< \brief [9:9] Access Enable for Master TAG ID 9 (rw) */
    unsigned int EN10:1;                    /**< \brief [10:10] Access Enable for Master TAG ID 10 (rw) */
    unsigned int EN11:1;                    /**< \brief [11:11] Access Enable for Master TAG ID 11 (rw) */
    unsigned int EN12:1;                    /**< \brief [12:12] Access Enable for Master TAG ID 12 (rw) */
    unsigned int EN13:1;                    /**< \brief [13:13] Access Enable for Master TAG ID 13 (rw) */
    unsigned int EN14:1;                    /**< \brief [14:14] Access Enable for Master TAG ID 14 (rw) */
    unsigned int EN15:1;                    /**< \brief [15:15] Access Enable for Master TAG ID 15 (rw) */
    unsigned int EN16:1;                    /**< \brief [16:16] Access Enable for Master TAG ID 16 (rw) */
    unsigned int EN17:1;                    /**< \brief [17:17] Access Enable for Master TAG ID 17 (rw) */
    unsigned int EN18:1;                    /**< \brief [18:18] Access Enable for Master TAG ID 18 (rw) */
    unsigned int EN19:1;                    /**< \brief [19:19] Access Enable for Master TAG ID 19 (rw) */
    unsigned int EN20:1;                    /**< \brief [20:20] Access Enable for Master TAG ID 20 (rw) */
    unsigned int EN21:1;                    /**< \brief [21:21] Access Enable for Master TAG ID 21 (rw) */
    unsigned int EN22:1;                    /**< \brief [22:22] Access Enable for Master TAG ID 22 (rw) */
    unsigned int EN23:1;                    /**< \brief [23:23] Access Enable for Master TAG ID 23 (rw) */
    unsigned int EN24:1;                    /**< \brief [24:24] Access Enable for Master TAG ID 24 (rw) */
    unsigned int EN25:1;                    /**< \brief [25:25] Access Enable for Master TAG ID 25 (rw) */
    unsigned int EN26:1;                    /**< \brief [26:26] Access Enable for Master TAG ID 26 (rw) */
    unsigned int EN27:1;                    /**< \brief [27:27] Access Enable for Master TAG ID 27 (rw) */
    unsigned int EN28:1;                    /**< \brief [28:28] Access Enable for Master TAG ID 28 (rw) */
    unsigned int EN29:1;                    /**< \brief [29:29] Access Enable for Master TAG ID 29 (rw) */
    unsigned int EN30:1;                    /**< \brief [30:30] Access Enable for Master TAG ID 30 (rw) */
    unsigned int EN31:1;                    /**< \brief [31:31] Access Enable for Master TAG ID 31 (rw) */
} Ifx_ASCLIN_ACCEN0_Bits;

/** \brief  Access Enable Register 1 */
typedef struct _Ifx_ASCLIN_ACCEN1_Bits
{
    unsigned int reserved_0:32;             /**< \brief \internal Reserved */
} Ifx_ASCLIN_ACCEN1_Bits;

/** \brief  Bit Configuration Register */
typedef struct _Ifx_ASCLIN_BITCON_Bits
{
    unsigned int PRESCALER:12;              /**< \brief [11:0] Prescaling of the Fractional Divider (rw) */
    unsigned int reserved_12:4;             /**< \brief \internal Reserved */
    unsigned int OVERSAMPLING:4;            /**< \brief [19:16] Oversampling Factor (rw) */
    unsigned int reserved_20:4;             /**< \brief \internal Reserved */
    unsigned int SAMPLEPOINT:4;             /**< \brief [27:24] Sample Point Position (rw) */
    unsigned int reserved_28:3;             /**< \brief \internal Reserved */
    unsigned int SM:1;                      /**< \brief [31:31] Sample Mode (rw) */
} Ifx_ASCLIN_BITCON_Bits;

/** \brief  Baud Rate Detection Register */
typedef struct _Ifx_ASCLIN_BRD_Bits
{
    unsigned int LOWERLIMIT:8;              /**< \brief [7:0] Lower Limit (rw) */
    unsigned int UPPERLIMIT:8;              /**< \brief [15:8] Upper Limit (rw) */
    unsigned int MEASURED:12;               /**< \brief [27:16] Measured Value of the Denominator (rh) */
    unsigned int reserved_28:4;             /**< \brief \internal Reserved */
} Ifx_ASCLIN_BRD_Bits;

/** \brief  Baud Rate Generation Register */
typedef struct _Ifx_ASCLIN_BRG_Bits
{
    unsigned int DENOMINATOR:12;            /**< \brief [11:0] Denominator (rw) */
    unsigned int reserved_12:4;             /**< \brief \internal Reserved */
    unsigned int NUMERATOR:12;              /**< \brief [27:16] Numerator (rw) */
    unsigned int reserved_28:4;             /**< \brief \internal Reserved */
} Ifx_ASCLIN_BRG_Bits;

/** \brief  Clock Control Register */
typedef struct _Ifx_ASCLIN_CLC_Bits
{
    unsigned int DISR:1;                    /**< \brief [0:0] Module Disable Request Bit (rw) */
    unsigned int DISS:1;                    /**< \brief [1:1] Module Disable Status Bit (rh) */
    unsigned int reserved_2:1;              /**< \brief \internal Reserved */
    unsigned int EDIS:1;                    /**< \brief [3:3] Sleep Mode Enable Control (rw) */
    unsigned int reserved_4:28;             /**< \brief \internal Reserved */
} Ifx_ASCLIN_CLC_Bits;

/** \brief  Clock Selection Register */
typedef struct _Ifx_ASCLIN_CSR_Bits
{
    unsigned int CLKSEL:5;                  /**< \brief [4:0] Baud Rate Logic Clock Select (rw) */
    unsigned int reserved_5:26;             /**< \brief \internal Reserved */
    unsigned int CON:1;                     /**< \brief [31:31] Clock On Flag (rh) */
} Ifx_ASCLIN_CSR_Bits;

/** \brief  Data Configuration Register */
typedef struct _Ifx_ASCLIN_DATCON_Bits
{
    unsigned int DATLEN:4;                  /**< \brief [3:0] Data Length (rw) */
    unsigned int reserved_4:9;              /**< \brief \internal Reserved */
    unsigned int HO:1;                      /**< \brief [13:13] Header Only (rw) */
    unsigned int RM:1;                      /**< \brief [14:14] Response Mode (rw) */
    unsigned int CSM:1;                     /**< \brief [15:15] Checksum Mode (rw) */
    unsigned int RESPONSE:8;                /**< \brief [23:16] Response Timeout Threshold Value (rw) */
    unsigned int reserved_24:8;             /**< \brief \internal Reserved */
} Ifx_ASCLIN_DATCON_Bits;

/** \brief  Flags Register */
typedef struct _Ifx_ASCLIN_FLAGS_Bits
{
    unsigned int TH:1;                      /**< \brief [0:0] Transmit Header End Flag (rh) */
    unsigned int TR:1;                      /**< \brief [1:1] Transmit Response End Flag (rh) */
    unsigned int RH:1;                      /**< \brief [2:2] Receive Header End Flag (rh) */
    unsigned int RR:1;                      /**< \brief [3:3] Receive Response End Flag (rh) */
    unsigned int reserved_4:1;              /**< \brief \internal Reserved */
    unsigned int FED:1;                     /**< \brief [5:5] Falling Edge from Level 1 to Level 0 Detected (rh) */
    unsigned int RED:1;                     /**< \brief [6:6] Rising Edge from Level 0 to Level 1 Detected (rh) */
    unsigned int reserved_7:6;              /**< \brief \internal Reserved */
    unsigned int TWRQ:1;                    /**< \brief [13:13] Transmit Wake Request Flag (rh) */
    unsigned int THRQ:1;                    /**< \brief [14:14] Transmit Header Request Flag (rh) */
    unsigned int TRRQ:1;                    /**< \brief [15:15] Transmit Response Request Flag (rh) */
    unsigned int PE:1;                      /**< \brief [16:16] Parity Error Flag (rh) */
    unsigned int TC:1;                      /**< \brief [17:17] Transmission Completed Flag (rh) */
    unsigned int FE:1;                      /**< \brief [18:18] Framing Error Flag (rh) */
    unsigned int HT:1;                      /**< \brief [19:19] Header Timeout Flag (rh) */
    unsigned int RT:1;                      /**< \brief [20:20] Response Timeout Flag (rh) */
    unsigned int BD:1;                      /**< \brief [21:21] Break Detected Flag (rh) */
    unsigned int LP:1;                      /**< \brief [22:22] LIN Parity Error Flag (rh) */
    unsigned int LA:1;                      /**< \brief [23:23] LIN Autobaud Detection Error Flag (rh) */
    unsigned int LC:1;                      /**< \brief [24:24] LIN Checksum Error Flag (rh) */
    unsigned int CE:1;                      /**< \brief [25:25] Collision Detection Error Flag (rh) */
    unsigned int RFO:1;                     /**< \brief [26:26] Receive FIFO Overflow Flag (rh) */
    unsigned int RFU:1;                     /**< \brief [27:27] Receive FIFO Underflow Flag (rh) */
    unsigned int RFL:1;                     /**< \brief [28:28] Receive FIFO Level Flag (rh) */
    unsigned int reserved_29:1;             /**< \brief \internal Reserved */
    unsigned int TFO:1;                     /**< \brief [30:30] Transmit FIFO Overflow Flag (rh) */
    unsigned int TFL:1;                     /**< \brief [31:31] Transmit FIFO Level Flag (rh) */
} Ifx_ASCLIN_FLAGS_Bits;

/** \brief  Flags Clear Register */
typedef struct _Ifx_ASCLIN_FLAGSCLEAR_Bits
{
    unsigned int THC:1;                     /**< \brief [0:0] Flag Clear Bit (w) */
    unsigned int TRC:1;                     /**< \brief [1:1] Flag Clear Bit (w) */
    unsigned int RHC:1;                     /**< \brief [2:2] Flag Clear Bit (w) */
    unsigned int RRC:1;                     /**< \brief [3:3] Flag Clear Bit (w) */
    unsigned int reserved_4:1;              /**< \brief \internal Reserved */
    unsigned int FEDC:1;                    /**< \brief [5:5] Flag Clear Bit (w) */
    unsigned int REDC:1;                    /**< \brief [6:6] Flag Clear Bit (w) */
    unsigned int reserved_7:6;              /**< \brief \internal Reserved */
    unsigned int TWRQC:1;                   /**< \brief [13:13] Flag Clear Bit (w) */
    unsigned int THRQC:1;                   /**< \brief [14:14] Flag Clear Bit (w) */
    unsigned int TRRQC:1;                   /**< \brief [15:15] Flag Clear Bit (w) */
    unsigned int PEC:1;                     /**< \brief [16:16] Flag Clear Bit (w) */
    unsigned int TCC:1;                     /**< \brief [17:17] Flag Clear Bit (w) */
    unsigned int FEC:1;                     /**< \brief [18:18] Flag Clear Bit (w) */
    unsigned int HTC:1;                     /**< \brief [19:19] Flag Clear Bit (w) */
    unsigned int RTC:1;                     /**< \brief [20:20] Flag Clear Bit (w) */
    unsigned int BDC:1;                     /**< \brief [21:21] Flag Clear Bit (w) */
    unsigned int LPC:1;                     /**< \brief [22:22] Flag Clear Bit (w) */
    unsigned int LAC:1;                     /**< \brief [23:23] Flag Clear Bit (w) */
    unsigned int LCC:1;                     /**< \brief [24:24] Flag Clear Bit (w) */
    unsigned int CEC:1;                     /**< \brief [25:25] Flag Clear Bit (w) */
    unsigned int RFOC:1;                    /**< \brief [26:26] Flag Clear Bit (w) */
    unsigned int RFUC:1;                    /**< \brief [27:27] Flag Clear Bit (w) */
    unsigned int RFLC:1;                    /**< \brief [28:28] Flag Clear Bit (w) */
    unsigned int reserved_29:1;             /**< \brief \internal Reserved */
    unsigned int TFOC:1;                    /**< \brief [30:30] Flag Clear Bit (w) */
    unsigned int TFLC:1;                    /**< \brief [31:31] Flag Clear Bit (w) */
} Ifx_ASCLIN_FLAGSCLEAR_Bits;

/** \brief  Flags Enable Register */
typedef struct _Ifx_ASCLIN_FLAGSENABLE_Bits
{
    unsigned int THE:1;                     /**< \brief [0:0] Flag Enable Bit (rw) */
    unsigned int TRE:1;                     /**< \brief [1:1] Flag Enable Bit (rw) */
    unsigned int RHE:1;                     /**< \brief [2:2] Flag Enable Bit (rw) */
    unsigned int RRE:1;                     /**< \brief [3:3] Flag Enable Bit (rw) */
    unsigned int reserved_4:1;              /**< \brief \internal Reserved */
    unsigned int FEDE:1;                    /**< \brief [5:5] Flag Enable Bit (rw) */
    unsigned int REDE:1;                    /**< \brief [6:6] Flag Enable Bit (rw) */
    unsigned int reserved_7:9;              /**< \brief \internal Reserved */
    unsigned int PEE:1;                     /**< \brief [16:16] Flag Enable Bit (rw) */
    unsigned int TCE:1;                     /**< \brief [17:17] Flag Enable Bit (rw) */
    unsigned int FEE:1;                     /**< \brief [18:18] Flag Enable Bit (rw) */
    unsigned int HTE:1;                     /**< \brief [19:19] Flag Enable Bit (rw) */
    unsigned int RTE:1;                     /**< \brief [20:20] Flag Enable Bit (rw) */
    unsigned int BDE:1;                     /**< \brief [21:21] Flag Enable Bit (rw) */
    unsigned int LPE:1;                     /**< \brief [22:22] Flag Enable Bit (rw) */
    unsigned int ABE:1;                     /**< \brief [23:23] Flag Enable Bit (rw) */
    unsigned int LCE:1;                     /**< \brief [24:24] Flag Enable Bit (rw) */
    unsigned int CEE:1;                     /**< \brief [25:25] Flag Enable Bit (rw) */
    unsigned int RFOE:1;                    /**< \brief [26:26] Flag Enable Bit (rw) */
    unsigned int RFUE:1;                    /**< \brief [27:27] Flag Enable Bit (rw) */
    unsigned int RFLE:1;                    /**< \brief [28:28] Flag Enable Bit (rw) */
    unsigned int reserved_29:1;             /**< \brief \internal Reserved */
    unsigned int TFOE:1;                    /**< \brief [30:30] Flag Enable Bit (rw) */
    unsigned int TFLE:1;                    /**< \brief [31:31] Flag Enable Bit (rw) */
} Ifx_ASCLIN_FLAGSENABLE_Bits;

/** \brief  Flags Set Register */
typedef struct _Ifx_ASCLIN_FLAGSSET_Bits
{
    unsigned int THS:1;                     /**< \brief [0:0] Flag Set Bit (w) */
    unsigned int TRS:1;                     /**< \brief [1:1] Flag Set Bit (w) */
    unsigned int RHS:1;                     /**< \brief [2:2] Flag Set Bit (w) */
    unsigned int RRS:1;                     /**< \brief [3:3] Flag Set Bit (w) */
    unsigned int reserved_4:1;              /**< \brief \internal Reserved */
    unsigned int FEDS:1;                    /**< \brief [5:5] Flag Set Bit (w) */
    unsigned int REDS:1;                    /**< \brief [6:6] Flag Set Bit (w) */
    unsigned int reserved_7:6;              /**< \brief \internal Reserved */
    unsigned int TWRQS:1;                   /**< \brief [13:13] Flag Set Bit (w) */
    unsigned int THRQS:1;                   /**< \brief [14:14] Flag Set Bit (w) */
    unsigned int TRRQS:1;                   /**< \brief [15:15] Flag Set Bit (w) */
    unsigned int PES:1;                     /**< \brief [16:16] Flag Set Bit (w) */
    unsigned int TCS:1;                     /**< \brief [17:17] Flag Set Bit (w) */
    unsigned int FES:1;                     /**< \brief [18:18] Flag Set Bit (w) */
    unsigned int HTS:1;                     /**< \brief [19:19] Flag Set Bit (w) */
    unsigned int RTS:1;                     /**< \brief [20:20] Flag Set Bit (w) */
    unsigned int BDS:1;                     /**< \brief [21:21] Flag Set Bit (w) */
    unsigned int LPS:1;                     /**< \brief [22:22] Flag Set Bit (w) */
    unsigned int LAS:1;                     /**< \brief [23:23] Flag Set Bit (w) */
    unsigned int LCS:1;                     /**< \brief [24:24] Flag Set Bit (w) */
    unsigned int CES:1;                     /**< \brief [25:25] Flag Set Bit (w) */
    unsigned int RFOS:1;                    /**< \brief [26:26] Flag Set Bit (w) */
    unsigned int RFUS:1;                    /**< \brief [27:27] Flag Set Bit (w) */
    unsigned int RFLS:1;                    /**< \brief [28:28] Flag Set Bit (w) */
    unsigned int reserved_29:1;             /**< \brief \internal Reserved */
    unsigned int TFOS:1;                    /**< \brief [30:30] Flag Set Bit (w) */
    unsigned int TFLS:1;                    /**< \brief [31:31] Flag Set Bit (w) */
} Ifx_ASCLIN_FLAGSSET_Bits;

/** \brief  Frame Control Register */
typedef struct _Ifx_ASCLIN_FRAMECON_Bits
{
    unsigned int reserved_0:6;              /**< \brief \internal Reserved */
    unsigned int IDLE:3;                    /**< \brief [8:6] Duration of the IDLE delay (rw) */
    unsigned int STOP:3;                    /**< \brief [11:9] Number of Stop Bits (rw) */
    unsigned int LEAD:3;                    /**< \brief [14:12] Duration of the Leading Delay (rw) */
    unsigned int reserved_15:1;             /**< \brief \internal Reserved */
    unsigned int MODE:2;                    /**< \brief [17:16] Mode Selection (rw) */
    unsigned int reserved_18:10;            /**< \brief \internal Reserved */
    unsigned int MSB:1;                     /**< \brief [28:28] Shift Direction (rw) */
    unsigned int CEN:1;                     /**< \brief [29:29] Collision Detection Enable (rw) */
    unsigned int PEN:1;                     /**< \brief [30:30] Parity Enable (rw) */
    unsigned int ODD:1;                     /**< \brief [31:31] Parity Type (rw) */
} Ifx_ASCLIN_FRAMECON_Bits;

/** \brief  Module Identification Register */
typedef struct _Ifx_ASCLIN_ID_Bits
{
    unsigned int MODREV:8;                  /**< \brief [7:0] Module Revision Number (r) */
    unsigned int MODTYPE:8;                 /**< \brief [15:8] Module Type (r) */
    unsigned int MODNUMBER:16;              /**< \brief [31:16] Module Number Value (r) */
} Ifx_ASCLIN_ID_Bits;

/** \brief  Input and Output Control Register */
typedef struct _Ifx_ASCLIN_IOCR_Bits
{
    unsigned int ALTI:3;                    /**< \brief [2:0] Alternate Input Select (rw) */
    unsigned int reserved_3:1;              /**< \brief \internal Reserved */
    unsigned int DEPTH:6;                   /**< \brief [9:4] Digital Glitch Filter Depth (rw) */
    unsigned int reserved_10:6;             /**< \brief \internal Reserved */
    unsigned int CTS:2;                     /**< \brief [17:16] CTS Select (rw) */
    unsigned int reserved_18:7;             /**< \brief \internal Reserved */
    unsigned int RCPOL:1;                   /**< \brief [25:25] RTS CTS Polarity (rw) */
    unsigned int CPOL:1;                    /**< \brief [26:26] Clock Polarity in Synchronous Mode (rw) */
    unsigned int SPOL:1;                    /**< \brief [27:27] Slave Polarity in Synchronous Mode (rw) */
    unsigned int LB:1;                      /**< \brief [28:28] Loop Back Mode (rw) */
    unsigned int CTSEN:1;                   /**< \brief [29:29] Input Signal CTS Enable (rw) */
    unsigned int RXM:1;                     /**< \brief [30:30] Receive Monitor (rh) */
    unsigned int TXM:1;                     /**< \brief [31:31] Transmit Monitor (rh) */
} Ifx_ASCLIN_IOCR_Bits;

/** \brief  Kernel Reset Register 0 */
typedef struct _Ifx_ASCLIN_KRST0_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int RSTSTAT:1;                 /**< \brief [1:1] Kernel Reset Status (rh) */
    unsigned int reserved_2:30;             /**< \brief \internal Reserved */
} Ifx_ASCLIN_KRST0_Bits;

/** \brief  Kernel Reset Register 1 */
typedef struct _Ifx_ASCLIN_KRST1_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_ASCLIN_KRST1_Bits;

/** \brief  Kernel Reset Status Clear Register */
typedef struct _Ifx_ASCLIN_KRSTCLR_Bits
{
    unsigned int CLR:1;                     /**< \brief [0:0] Kernel Reset Status Clear (w) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_ASCLIN_KRSTCLR_Bits;

/** \brief  LIN Break Timer Register */
typedef struct _Ifx_ASCLIN_LIN_BTIMER_Bits
{
    unsigned int BREAK:6;                   /**< \brief [5:0] Break Pulse Generation and Detection (rw) */
    unsigned int reserved_6:26;             /**< \brief \internal Reserved */
} Ifx_ASCLIN_LIN_BTIMER_Bits;

/** \brief  LIN Control Register */
typedef struct _Ifx_ASCLIN_LIN_CON_Bits
{
    unsigned int reserved_0:23;             /**< \brief \internal Reserved */
    unsigned int CSI:1;                     /**< \brief [23:23] Checksum Injection (rw) */
    unsigned int reserved_24:1;             /**< \brief \internal Reserved */
    unsigned int CSEN:1;                    /**< \brief [25:25] Hardware Checksum Enable (rw) */
    unsigned int MS:1;                      /**< \brief [26:26] Master Slave Mode (rw) */
    unsigned int ABD:1;                     /**< \brief [27:27] Autobaud Detection (rw) */
    unsigned int reserved_28:4;             /**< \brief \internal Reserved */
} Ifx_ASCLIN_LIN_CON_Bits;

/** \brief  LIN Header Timer Register */
typedef struct _Ifx_ASCLIN_LIN_HTIMER_Bits
{
    unsigned int HEADER:8;                  /**< \brief [7:0] Header Timeout Threshold Value (rw) */
    unsigned int reserved_8:24;             /**< \brief \internal Reserved */
} Ifx_ASCLIN_LIN_HTIMER_Bits;

/** \brief  OCDS Control and Status */
typedef struct _Ifx_ASCLIN_OCS_Bits
{
    unsigned int reserved_0:24;             /**< \brief \internal Reserved */
    unsigned int SUS:4;                     /**< \brief [27:24] OCDS Suspend Control (rw) */
    unsigned int SUS_P:1;                   /**< \brief [28:28] SUS Write Protection (w) */
    unsigned int SUSSTA:1;                  /**< \brief [29:29] Suspend State (rh) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_ASCLIN_OCS_Bits;

/** \brief  Receive Data Register */
typedef struct _Ifx_ASCLIN_RXDATA_Bits
{
    unsigned int DATA:32;                   /**< \brief [31:0] Data (rh) */
} Ifx_ASCLIN_RXDATA_Bits;

/** \brief  Receive Data Debug Register */
typedef struct _Ifx_ASCLIN_RXDATAD_Bits
{
    unsigned int DATA:32;                   /**< \brief [31:0] Data (rh) */
} Ifx_ASCLIN_RXDATAD_Bits;

/** \brief  RX FIFO Configuration Register */
typedef struct _Ifx_ASCLIN_RXFIFOCON_Bits
{
    unsigned int FLUSH:1;                   /**< \brief [0:0] Flush the receive FIFO (w) */
    unsigned int ENI:1;                     /**< \brief [1:1] Receive FIFO Inlet Enable (rwh) */
    unsigned int reserved_2:4;              /**< \brief \internal Reserved */
    unsigned int OUTW:2;                    /**< \brief [7:6] Receive FIFO Outlet Width (rw) */
    unsigned int INTLEVEL:4;                /**< \brief [11:8] FIFO Interrupt Level (rw) */
    unsigned int reserved_12:4;             /**< \brief \internal Reserved */
    unsigned int FILL:5;                    /**< \brief [20:16] FIFO Filling Level (rh) */
    unsigned int reserved_21:10;            /**< \brief \internal Reserved */
    unsigned int BUF:1;                     /**< \brief [31:31] Receive Buffer Mode (rw) */
} Ifx_ASCLIN_RXFIFOCON_Bits;

/** \brief  Transmit Data Register */
typedef struct _Ifx_ASCLIN_TXDATA_Bits
{
    unsigned int DATA:32;                   /**< \brief [31:0] Data (w) */
} Ifx_ASCLIN_TXDATA_Bits;

/** \brief  TX FIFO Configuration Register */
typedef struct _Ifx_ASCLIN_TXFIFOCON_Bits
{
    unsigned int FLUSH:1;                   /**< \brief [0:0] Flush the transmit FIFO (w) */
    unsigned int ENO:1;                     /**< \brief [1:1] Transmit FIFO Outlet Enable (rw) */
    unsigned int reserved_2:4;              /**< \brief \internal Reserved */
    unsigned int INW:2;                     /**< \brief [7:6] Transmit FIFO Inlet Width (rw) */
    unsigned int INTLEVEL:4;                /**< \brief [11:8] FIFO Interrupt Level (rw) */
    unsigned int reserved_12:4;             /**< \brief \internal Reserved */
    unsigned int FILL:5;                    /**< \brief [20:16] FIFO Filling Level (rh) */
    unsigned int reserved_21:11;            /**< \brief \internal Reserved */
} Ifx_ASCLIN_TXFIFOCON_Bits;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Asclin_union
 * \{  */

/** \brief  Access Enable Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ASCLIN_ACCEN0_Bits B;               /**< \brief Bitfield access */
} Ifx_ASCLIN_ACCEN0;

/** \brief  Access Enable Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ASCLIN_ACCEN1_Bits B;               /**< \brief Bitfield access */
} Ifx_ASCLIN_ACCEN1;

/** \brief  Bit Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ASCLIN_BITCON_Bits B;               /**< \brief Bitfield access */
} Ifx_ASCLIN_BITCON;

/** \brief  Baud Rate Detection Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ASCLIN_BRD_Bits B;                  /**< \brief Bitfield access */
} Ifx_ASCLIN_BRD;

/** \brief  Baud Rate Generation Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ASCLIN_BRG_Bits B;                  /**< \brief Bitfield access */
} Ifx_ASCLIN_BRG;

/** \brief  Clock Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ASCLIN_CLC_Bits B;                  /**< \brief Bitfield access */
} Ifx_ASCLIN_CLC;

/** \brief  Clock Selection Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ASCLIN_CSR_Bits B;                  /**< \brief Bitfield access */
} Ifx_ASCLIN_CSR;

/** \brief  Data Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ASCLIN_DATCON_Bits B;               /**< \brief Bitfield access */
} Ifx_ASCLIN_DATCON;

/** \brief  Flags Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ASCLIN_FLAGS_Bits B;                /**< \brief Bitfield access */
} Ifx_ASCLIN_FLAGS;

/** \brief  Flags Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ASCLIN_FLAGSCLEAR_Bits B;           /**< \brief Bitfield access */
} Ifx_ASCLIN_FLAGSCLEAR;

/** \brief  Flags Enable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ASCLIN_FLAGSENABLE_Bits B;          /**< \brief Bitfield access */
} Ifx_ASCLIN_FLAGSENABLE;

/** \brief  Flags Set Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ASCLIN_FLAGSSET_Bits B;             /**< \brief Bitfield access */
} Ifx_ASCLIN_FLAGSSET;

/** \brief  Frame Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ASCLIN_FRAMECON_Bits B;             /**< \brief Bitfield access */
} Ifx_ASCLIN_FRAMECON;

/** \brief  Module Identification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ASCLIN_ID_Bits B;                   /**< \brief Bitfield access */
} Ifx_ASCLIN_ID;

/** \brief  Input and Output Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ASCLIN_IOCR_Bits B;                 /**< \brief Bitfield access */
} Ifx_ASCLIN_IOCR;

/** \brief  Kernel Reset Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ASCLIN_KRST0_Bits B;                /**< \brief Bitfield access */
} Ifx_ASCLIN_KRST0;

/** \brief  Kernel Reset Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ASCLIN_KRST1_Bits B;                /**< \brief Bitfield access */
} Ifx_ASCLIN_KRST1;

/** \brief  Kernel Reset Status Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ASCLIN_KRSTCLR_Bits B;              /**< \brief Bitfield access */
} Ifx_ASCLIN_KRSTCLR;

/** \brief  LIN Break Timer Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ASCLIN_LIN_BTIMER_Bits B;           /**< \brief Bitfield access */
} Ifx_ASCLIN_LIN_BTIMER;

/** \brief  LIN Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ASCLIN_LIN_CON_Bits B;              /**< \brief Bitfield access */
} Ifx_ASCLIN_LIN_CON;

/** \brief  LIN Header Timer Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ASCLIN_LIN_HTIMER_Bits B;           /**< \brief Bitfield access */
} Ifx_ASCLIN_LIN_HTIMER;

/** \brief  OCDS Control and Status */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ASCLIN_OCS_Bits B;                  /**< \brief Bitfield access */
} Ifx_ASCLIN_OCS;

/** \brief  Receive Data Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ASCLIN_RXDATA_Bits B;               /**< \brief Bitfield access */
} Ifx_ASCLIN_RXDATA;

/** \brief  Receive Data Debug Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ASCLIN_RXDATAD_Bits B;              /**< \brief Bitfield access */
} Ifx_ASCLIN_RXDATAD;

/** \brief  RX FIFO Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ASCLIN_RXFIFOCON_Bits B;            /**< \brief Bitfield access */
} Ifx_ASCLIN_RXFIFOCON;

/** \brief  Transmit Data Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ASCLIN_TXDATA_Bits B;               /**< \brief Bitfield access */
} Ifx_ASCLIN_TXDATA;

/** \brief  TX FIFO Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ASCLIN_TXFIFOCON_Bits B;            /**< \brief Bitfield access */
} Ifx_ASCLIN_TXFIFOCON;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Asclin_struct
 * \{  */
/******************************************************************************/
/** \name Object L1
 * \{  */

/** \brief  LIN */
typedef volatile struct _Ifx_ASCLIN_LIN
{
    Ifx_ASCLIN_LIN_CON CON;                 /**< \brief 0, LIN Control Register */
    Ifx_ASCLIN_LIN_BTIMER BTIMER;           /**< \brief 4, LIN Break Timer Register */
    Ifx_ASCLIN_LIN_HTIMER HTIMER;           /**< \brief 8, LIN Header Timer Register */
} Ifx_ASCLIN_LIN;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Asclin_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \brief  ASCLIN object */
typedef volatile struct _Ifx_ASCLIN
{
    Ifx_ASCLIN_CLC CLC;                     /**< \brief 0, Clock Control Register */
    Ifx_ASCLIN_IOCR IOCR;                   /**< \brief 4, Input and Output Control Register */
    Ifx_ASCLIN_ID ID;                       /**< \brief 8, Module Identification Register */
    Ifx_ASCLIN_TXFIFOCON TXFIFOCON;         /**< \brief C, TX FIFO Configuration Register */
    Ifx_ASCLIN_RXFIFOCON RXFIFOCON;         /**< \brief 10, RX FIFO Configuration Register */
    Ifx_ASCLIN_BITCON BITCON;               /**< \brief 14, Bit Configuration Register */
    Ifx_ASCLIN_FRAMECON FRAMECON;           /**< \brief 18, Frame Control Register */
    Ifx_ASCLIN_DATCON DATCON;               /**< \brief 1C, Data Configuration Register */
    Ifx_ASCLIN_BRG BRG;                     /**< \brief 20, Baud Rate Generation Register */
    Ifx_ASCLIN_BRD BRD;                     /**< \brief 24, Baud Rate Detection Register */
    Ifx_ASCLIN_LIN LIN;                     /**< \brief 28, LIN */
    Ifx_ASCLIN_FLAGS FLAGS;                 /**< \brief 34, Flags Register */
    Ifx_ASCLIN_FLAGSSET FLAGSSET;           /**< \brief 38, Flags Set Register */
    Ifx_ASCLIN_FLAGSCLEAR FLAGSCLEAR;       /**< \brief 3C, Flags Clear Register */
    Ifx_ASCLIN_FLAGSENABLE FLAGSENABLE;     /**< \brief 40, Flags Enable Register */
    Ifx_ASCLIN_TXDATA TXDATA;               /**< \brief 44, Transmit Data Register */
    Ifx_ASCLIN_RXDATA RXDATA;               /**< \brief 48, Receive Data Register */
    Ifx_ASCLIN_CSR CSR;                     /**< \brief 4C, Clock Selection Register */
    Ifx_ASCLIN_RXDATAD RXDATAD;             /**< \brief 50, Receive Data Debug Register */
    unsigned char reserved_54[148];         /**< \brief 54, \internal Reserved */
    Ifx_ASCLIN_OCS OCS;                     /**< \brief E8, OCDS Control and Status */
    Ifx_ASCLIN_KRSTCLR KRSTCLR;             /**< \brief EC, Kernel Reset Status Clear Register */
    Ifx_ASCLIN_KRST1 KRST1;                 /**< \brief F0, Kernel Reset Register 1 */
    Ifx_ASCLIN_KRST0 KRST0;                 /**< \brief F4, Kernel Reset Register 0 */
    Ifx_ASCLIN_ACCEN1 ACCEN1;               /**< \brief F8, Access Enable Register 1 */
    Ifx_ASCLIN_ACCEN0 ACCEN0;               /**< \brief FC, Access Enable Register 0 */
} Ifx_ASCLIN;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXASCLIN_REGDEF_H */
