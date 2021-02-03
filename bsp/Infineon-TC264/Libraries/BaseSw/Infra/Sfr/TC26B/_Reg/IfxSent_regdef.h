/**
 * \file IfxSent_regdef.h
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
 * \defgroup IfxLld_Sent Sent
 * \ingroup IfxLld
 * 
 * \defgroup IfxLld_Sent_Bitfields Bitfields
 * \ingroup IfxLld_Sent
 * 
 * \defgroup IfxLld_Sent_union Union
 * \ingroup IfxLld_Sent
 * 
 * \defgroup IfxLld_Sent_struct Struct
 * \ingroup IfxLld_Sent
 * 
 */
#ifndef IFXSENT_REGDEF_H
#define IFXSENT_REGDEF_H 1
/******************************************************************************/
#include "Ifx_TypesReg.h"
/******************************************************************************/
/** \addtogroup IfxLld_Sent_Bitfields
 * \{  */

/** \brief  Access Enable Register 0 */
typedef struct _Ifx_SENT_ACCEN0_Bits
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
} Ifx_SENT_ACCEN0_Bits;

/** \brief  Access Enable Register 1 */
typedef struct _Ifx_SENT_ACCEN1_Bits
{
    unsigned int reserved_0:32;             /**< \brief \internal Reserved */
} Ifx_SENT_ACCEN1_Bits;

/** \brief  Channel Fractional Divider Register */
typedef struct _Ifx_SENT_CH_CFDR_Bits
{
    unsigned int DIV:12;                    /**< \brief [11:0] Divider Value (rw) */
    unsigned int reserved_12:4;             /**< \brief \internal Reserved */
    unsigned int DIVM:12;                   /**< \brief [27:16] Measured Divider Value (rh) */
    unsigned int reserved_28:4;             /**< \brief \internal Reserved */
} Ifx_SENT_CH_CFDR_Bits;

/** \brief  Channel Pre Divider Register */
typedef struct _Ifx_SENT_CH_CPDR_Bits
{
    unsigned int PDIV:12;                   /**< \brief [11:0] Divider Factor of Pre Divider for Channel x (rw) */
    unsigned int reserved_12:20;            /**< \brief \internal Reserved */
} Ifx_SENT_CH_CPDR_Bits;

/** \brief  Interrupt Node Pointer Register */
typedef struct _Ifx_SENT_CH_INP_Bits
{
    unsigned int RSI:4;                     /**< \brief [3:0] Interrupt Node Pointer for Interrupt RSI (rw) */
    unsigned int RDI:4;                     /**< \brief [7:4] Interrupt Node Pointer for Interrupt RDI (rw) */
    unsigned int RBI:4;                     /**< \brief [11:8] Interrupt Node Pointer for Interrupt RBI (rw) */
    unsigned int TDI:4;                     /**< \brief [15:12] Interrupt Node Pointer for Interrupt TDI (rw) */
    unsigned int TBI:4;                     /**< \brief [19:16] Interrupt Node Pointer for Interrupt TBI (rw) */
    unsigned int ERRI:4;                    /**< \brief [23:20] Interrupt Node Pointer for Interrupt FRI, FDI, NNI, NVI, CRCI, WSI, SCRI (rw) */
    unsigned int SDI:4;                     /**< \brief [27:24] Interrupt Node Pointer for Interrupt SDI (rw) */
    unsigned int WDI:4;                     /**< \brief [31:28] Interrupt Node Pointer for Interrupt WDI (rw) */
} Ifx_SENT_CH_INP_Bits;

/** \brief  Interrupt Clear Register */
typedef struct _Ifx_SENT_CH_INTCLR_Bits
{
    unsigned int RSI:1;                     /**< \brief [0:0] Clear Interrupt Request Flag RSI (w) */
    unsigned int RDI:1;                     /**< \brief [1:1] Clear Interrupt Request Flag RDI (w) */
    unsigned int RBI:1;                     /**< \brief [2:2] Clear Interrupt Request Flag RBI (w) */
    unsigned int TDI:1;                     /**< \brief [3:3] Clear Interrupt Request Flag TDI (w) */
    unsigned int TBI:1;                     /**< \brief [4:4] Clear Interrupt Request Flag TBI (w) */
    unsigned int FRI:1;                     /**< \brief [5:5] Clear Interrupt Request Flag FRI (w) */
    unsigned int FDI:1;                     /**< \brief [6:6] Clear Interrupt Request Flag FDI (w) */
    unsigned int NNI:1;                     /**< \brief [7:7] Clear Interrupt Request Flag NMI (w) */
    unsigned int NVI:1;                     /**< \brief [8:8] Clear Interrupt Request Flag NVI (w) */
    unsigned int CRCI:1;                    /**< \brief [9:9] Clear Interrupt Request Flag CRCI (w) */
    unsigned int WSI:1;                     /**< \brief [10:10] Clear Interrupt Request Flag WSI (w) */
    unsigned int SDI:1;                     /**< \brief [11:11] Clear Interrupt Request Flag SDI (w) */
    unsigned int SCRI:1;                    /**< \brief [12:12] Clear Interrupt Request Flag SCRI (w) */
    unsigned int WDI:1;                     /**< \brief [13:13] Clear Interrupt Request Flag WDI (w) */
    unsigned int reserved_14:18;            /**< \brief \internal Reserved */
} Ifx_SENT_CH_INTCLR_Bits;

/** \brief  Interrupt Enable Register */
typedef struct _Ifx_SENT_CH_INTEN_Bits
{
    unsigned int RSI:1;                     /**< \brief [0:0] Enable Interrupt Request RSI (rw) */
    unsigned int RDI:1;                     /**< \brief [1:1] Enable Interrupt Request RDI (rw) */
    unsigned int RBI:1;                     /**< \brief [2:2] Enable Interrupt Request RBI (rw) */
    unsigned int TDI:1;                     /**< \brief [3:3] Enable Interrupt Request TDI (rw) */
    unsigned int TBI:1;                     /**< \brief [4:4] Enable Interrupt Request TBI (rw) */
    unsigned int FRI:1;                     /**< \brief [5:5] Enable Interrupt Request FRI (rw) */
    unsigned int FDI:1;                     /**< \brief [6:6] Enable Interrupt Request FDI (rw) */
    unsigned int NNI:1;                     /**< \brief [7:7] Enable Interrupt Request NNI (rw) */
    unsigned int NVI:1;                     /**< \brief [8:8] Enable Interrupt Request NVI (rw) */
    unsigned int CRCI:1;                    /**< \brief [9:9] Enable Interrupt Request CRCI (rw) */
    unsigned int WSI:1;                     /**< \brief [10:10] Enable Interrupt Request WSI (rw) */
    unsigned int SDI:1;                     /**< \brief [11:11] Enable Interrupt Request SDI (rw) */
    unsigned int SCRI:1;                    /**< \brief [12:12] Enable Interrupt Request SCRI (rw) */
    unsigned int WDI:1;                     /**< \brief [13:13] Enable Interrupt Request WDI (rw) */
    unsigned int reserved_14:18;            /**< \brief \internal Reserved */
} Ifx_SENT_CH_INTEN_Bits;

/** \brief  Interrupt Set Register */
typedef struct _Ifx_SENT_CH_INTSET_Bits
{
    unsigned int RSI:1;                     /**< \brief [0:0] Set Interrupt Request Flag RSI (w) */
    unsigned int RDI:1;                     /**< \brief [1:1] Set Interrupt Request Flag RDI (w) */
    unsigned int RBI:1;                     /**< \brief [2:2] Set Interrupt Request Flag RBI (w) */
    unsigned int TDI:1;                     /**< \brief [3:3] Set Interrupt Request Flag TDI (w) */
    unsigned int TBI:1;                     /**< \brief [4:4] Set Interrupt Request Flag TBI (w) */
    unsigned int FRI:1;                     /**< \brief [5:5] Set Interrupt Request Flag FRI (w) */
    unsigned int FDI:1;                     /**< \brief [6:6] Set Interrupt Request Flag FDI (w) */
    unsigned int NNI:1;                     /**< \brief [7:7] Set Interrupt Request Flag NNI (w) */
    unsigned int NVI:1;                     /**< \brief [8:8] Set Interrupt Request Flag NVI (w) */
    unsigned int CRCI:1;                    /**< \brief [9:9] Set Interrupt Request Flag CRCI (w) */
    unsigned int WSI:1;                     /**< \brief [10:10] Set Interrupt Request Flag WSI (w) */
    unsigned int SDI:1;                     /**< \brief [11:11] Set Interrupt Request Flag SDI (w) */
    unsigned int SCRI:1;                    /**< \brief [12:12] Set Interrupt Request Flag SCRI (w) */
    unsigned int WDI:1;                     /**< \brief [13:13] Set Interrupt Request Flag WDI (w) */
    unsigned int reserved_14:18;            /**< \brief \internal Reserved */
} Ifx_SENT_CH_INTSET_Bits;

/** \brief  Interrupt Status Register */
typedef struct _Ifx_SENT_CH_INTSTAT_Bits
{
    unsigned int RSI:1;                     /**< \brief [0:0] Receive Success Interrupt Request Flag (rh) */
    unsigned int RDI:1;                     /**< \brief [1:1] Receive Data Interrupt Request Flag (rh) */
    unsigned int RBI:1;                     /**< \brief [2:2] Receive Buffer Overflow Interrupt Request Flag (rh) */
    unsigned int TDI:1;                     /**< \brief [3:3] Transfer Data Interrupt Request Flag (rh) */
    unsigned int TBI:1;                     /**< \brief [4:4] Transmit Buffer Underflow Interrupt Request Flag (rh) */
    unsigned int FRI:1;                     /**< \brief [5:5] Frequency Range Interrupt Request Flag (rh) */
    unsigned int FDI:1;                     /**< \brief [6:6] Frequency Drift Interrupt Request Flag (rh) */
    unsigned int NNI:1;                     /**< \brief [7:7] Number of Nibbles Wrong Request Flag (rh) */
    unsigned int NVI:1;                     /**< \brief [8:8] Nibbles Value out of Range Request Flag (rh) */
    unsigned int CRCI:1;                    /**< \brief [9:9] CRC Error Request Flag (rh) */
    unsigned int WSI:1;                     /**< \brief [10:10] Wrong Status and Communication Nibble Error Request Flag (rh) */
    unsigned int SDI:1;                     /**< \brief [11:11] Serial Data Receive Interrupt Request Flag (rh) */
    unsigned int SCRI:1;                    /**< \brief [12:12] Serial Data CRC Error Request Flag (rh) */
    unsigned int WDI:1;                     /**< \brief [13:13] Watch Dog Error Request Flag (rh) */
    unsigned int reserved_14:18;            /**< \brief \internal Reserved */
} Ifx_SENT_CH_INTSTAT_Bits;

/** \brief  Input and Output Control Register */
typedef struct _Ifx_SENT_CH_IOCR_Bits
{
    unsigned int ALTI:2;                    /**< \brief [1:0] Alternate Input Select (rw) */
    unsigned int reserved_2:2;              /**< \brief \internal Reserved */
    unsigned int DEPTH:4;                   /**< \brief [7:4] Digital Glitch Filter Depth (rw) */
    unsigned int OIE:1;                     /**< \brief [8:8] Output Inverter Enable Channel x (rw) */
    unsigned int IIE:1;                     /**< \brief [9:9] Input Inverter Enable Channel x (rw) */
    unsigned int CEC:1;                     /**< \brief [10:10] Clear Edge Counter (w) */
    unsigned int reserved_11:1;             /**< \brief \internal Reserved */
    unsigned int REG:1;                     /**< \brief [12:12] Rising Edge Glitch Flag for Channel x (rh) */
    unsigned int FEG:1;                     /**< \brief [13:13] Falling Edge Glitch Flag for Channel x (rh) */
    unsigned int CREG:1;                    /**< \brief [14:14] Clear Rising Edge Glitch Flag for Channel x (rw) */
    unsigned int CFEG:1;                    /**< \brief [15:15] Clear Falling Edge Glitch Flag for Channel x (rw) */
    unsigned int ETS:4;                     /**< \brief [19:16] External Trigger Select (rw) */
    unsigned int EC:8;                      /**< \brief [27:20] Edge Counter (rh) */
    unsigned int CTR:1;                     /**< \brief [28:28] Clear Trigger Monitor Flag for Channel x (rw) */
    unsigned int TRM:1;                     /**< \brief [29:29] Trigger Monitor Flag for Channel x (rh) */
    unsigned int RXM:1;                     /**< \brief [30:30] Receive Monitor for Channel x (rh) */
    unsigned int TXM:1;                     /**< \brief [31:31] Transmit Monitor for Channel x (rh) */
} Ifx_SENT_CH_IOCR_Bits;

/** \brief  Receiver Control Register */
typedef struct _Ifx_SENT_CH_RCR_Bits
{
    unsigned int CEN:1;                     /**< \brief [0:0] Channel Enable (rw) */
    unsigned int IEP:1;                     /**< \brief [1:1] Ignore End Pulse (rw) */
    unsigned int ACE:1;                     /**< \brief [2:2] Alternative CRC Mode Enable (rw) */
    unsigned int SNI:1;                     /**< \brief [3:3] Status Nibble Included in CRC (rw) */
    unsigned int SDP:1;                     /**< \brief [4:4] Serial Data Processing Mode (rw) */
    unsigned int SCDIS:1;                   /**< \brief [5:5] CRC for Serial Data Disabled Mode (rw) */
    unsigned int CDIS:1;                    /**< \brief [6:6] CRC Disabled Mode (rw) */
    unsigned int CFC:1;                     /**< \brief [7:7] Consecutive Frame Check (rw) */
    unsigned int FRL:8;                     /**< \brief [15:8] Frame Length (rw) */
    unsigned int CRZ:1;                     /**< \brief [16:16] CRC with Zero Nibble for Serial Data (rw) */
    unsigned int ESF:1;                     /**< \brief [17:17] Extended Serial Frame Mode (rw) */
    unsigned int IDE:1;                     /**< \brief [18:18] Ignore Drift Error Mode (rw) */
    unsigned int SUSEN:1;                   /**< \brief [19:19] Suspend Enable (rw) */
    unsigned int reserved_20:12;            /**< \brief \internal Reserved */
} Ifx_SENT_CH_RCR_Bits;

/** \brief  Receive Status Register */
typedef struct _Ifx_SENT_CH_RSR_Bits
{
    unsigned int CRC:4;                     /**< \brief [3:0] CRC (r) */
    unsigned int CST:2;                     /**< \brief [5:4] Channel Status (r) */
    unsigned int reserved_6:2;              /**< \brief \internal Reserved */
    unsigned int SCN:4;                     /**< \brief [11:8] Status and Communication Nibble (r) */
    unsigned int reserved_12:20;            /**< \brief \internal Reserved */
} Ifx_SENT_CH_RSR_Bits;

/** \brief  SPC Control Register */
typedef struct _Ifx_SENT_CH_SCR_Bits
{
    unsigned int PLEN:6;                    /**< \brief [5:0] Pulse Length (rw) */
    unsigned int TRIG:2;                    /**< \brief [7:6] Trigger Source and Mode Selection (rw) */
    unsigned int DEL:6;                     /**< \brief [13:8] Delay Length (rw) */
    unsigned int BASE:1;                    /**< \brief [14:14] Time Base (rw) */
    unsigned int TRQ:1;                     /**< \brief [15:15] Transfer Request in Progress (r) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_SENT_CH_SCR_Bits;

/** \brief  Serial Data and Status Register */
typedef struct _Ifx_SENT_CH_SDS_Bits
{
    unsigned int SD:16;                     /**< \brief [15:0] Serial Data (r) */
    unsigned int MID:8;                     /**< \brief [23:16] Message ID (r) */
    unsigned int SCRC:6;                    /**< \brief [29:24] SCRC (r) */
    unsigned int reserved_30:1;             /**< \brief \internal Reserved */
    unsigned int CON:1;                     /**< \brief [31:31] Configuration bit (r) */
} Ifx_SENT_CH_SDS_Bits;

/** \brief  Receive Data View Register */
typedef struct _Ifx_SENT_CH_VIEW_Bits
{
    unsigned int RDNP0:3;                   /**< \brief [2:0] Receive Data Target Nibble Pointer 0 (rw) */
    unsigned int reserved_3:1;              /**< \brief \internal Reserved */
    unsigned int RDNP1:3;                   /**< \brief [6:4] Receive Data Target Nibble Pointer 1 (rw) */
    unsigned int reserved_7:1;              /**< \brief \internal Reserved */
    unsigned int RDNP2:3;                   /**< \brief [10:8] Receive Data Target Nibble Pointer 2 (rw) */
    unsigned int reserved_11:1;             /**< \brief \internal Reserved */
    unsigned int RDNP3:3;                   /**< \brief [14:12] Receive Data Target Nibble Pointer 3 (rw) */
    unsigned int reserved_15:1;             /**< \brief \internal Reserved */
    unsigned int RDNP4:3;                   /**< \brief [18:16] Receive Data Target Nibble Pointer 4 (rw) */
    unsigned int reserved_19:1;             /**< \brief \internal Reserved */
    unsigned int RDNP5:3;                   /**< \brief [22:20] Receive Data Target Nibble Pointer 5 (rw) */
    unsigned int reserved_23:1;             /**< \brief \internal Reserved */
    unsigned int RDNP6:3;                   /**< \brief [26:24] Receive Data Target Nibble Pointer 6 (rw) */
    unsigned int reserved_27:1;             /**< \brief \internal Reserved */
    unsigned int RDNP7:3;                   /**< \brief [30:28] Receive Data Target Nibble Pointer 7 (rw) */
    unsigned int reserved_31:1;             /**< \brief \internal Reserved */
} Ifx_SENT_CH_VIEW_Bits;

/** \brief  Watch Dog Timer Register */
typedef struct _Ifx_SENT_CH_WDT_Bits
{
    unsigned int WDLx:16;                   /**< \brief [15:0] Watch Dog Timer Limit (rw) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_SENT_CH_WDT_Bits;

/** \brief  Clock Control Register */
typedef struct _Ifx_SENT_CLC_Bits
{
    unsigned int DISR:1;                    /**< \brief [0:0] Module Disable Request Bit (rw) */
    unsigned int DISS:1;                    /**< \brief [1:1] Module Disable Status Bit (rh) */
    unsigned int reserved_2:1;              /**< \brief \internal Reserved */
    unsigned int EDIS:1;                    /**< \brief [3:3] Sleep Mode Enable Control (rw) */
    unsigned int reserved_4:4;              /**< \brief \internal Reserved */
    unsigned int RMC:8;                     /**< \brief [15:8] 8-bit Clock Divider Value in RUN Mode (rw) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_SENT_CLC_Bits;

/** \brief  SENT Fractional Divider Register */
typedef struct _Ifx_SENT_FDR_Bits
{
    unsigned int STEP:10;                   /**< \brief [9:0] Step Value (rw) */
    unsigned int reserved_10:4;             /**< \brief \internal Reserved */
    unsigned int DM:2;                      /**< \brief [15:14] Divider Mode (rw) */
    unsigned int RESULT:10;                 /**< \brief [25:16] Result Value (rh) */
    unsigned int reserved_26:6;             /**< \brief \internal Reserved */
} Ifx_SENT_FDR_Bits;

/** \brief  Module Identification Register */
typedef struct _Ifx_SENT_ID_Bits
{
    unsigned int MODREV:8;                  /**< \brief [7:0] Module Revision Number (r) */
    unsigned int MODTYPE:8;                 /**< \brief [15:8] Module Type (r) */
    unsigned int MODNUMBER:16;              /**< \brief [31:16] Module Number Value (r) */
} Ifx_SENT_ID_Bits;

/** \brief  Interrupt Overview Register */
typedef struct _Ifx_SENT_INTOV_Bits
{
    unsigned int IPC0:1;                    /**< \brief [0:0] Interrupt Pending on Channel 0 (rh) */
    unsigned int IPC1:1;                    /**< \brief [1:1] Interrupt Pending on Channel 1 (rh) */
    unsigned int IPC2:1;                    /**< \brief [2:2] Interrupt Pending on Channel 2 (rh) */
    unsigned int IPC3:1;                    /**< \brief [3:3] Interrupt Pending on Channel 3 (rh) */
    unsigned int IPC4:1;                    /**< \brief [4:4] Interrupt Pending on Channel 4 (rh) */
    unsigned int IPC5:1;                    /**< \brief [5:5] Interrupt Pending on Channel 5 (rh) */
    unsigned int reserved_6:26;             /**< \brief \internal Reserved */
} Ifx_SENT_INTOV_Bits;

/** \brief  Kernel Reset Register 0 */
typedef struct _Ifx_SENT_KRST0_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int RSTSTAT:1;                 /**< \brief [1:1] Kernel Reset Status (rh) */
    unsigned int reserved_2:30;             /**< \brief \internal Reserved */
} Ifx_SENT_KRST0_Bits;

/** \brief  Kernel Reset Register 1 */
typedef struct _Ifx_SENT_KRST1_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_SENT_KRST1_Bits;

/** \brief  Kernel Reset Status Clear Register */
typedef struct _Ifx_SENT_KRSTCLR_Bits
{
    unsigned int CLR:1;                     /**< \brief [0:0] Kernel Reset Status Clear (w) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_SENT_KRSTCLR_Bits;

/** \brief  OCDS Control and Status */
typedef struct _Ifx_SENT_OCS_Bits
{
    unsigned int reserved_0:24;             /**< \brief \internal Reserved */
    unsigned int SUS:4;                     /**< \brief [27:24] OCDS Suspend Control (rw) */
    unsigned int SUS_P:1;                   /**< \brief [28:28] SUS Write Protection (w) */
    unsigned int SUSSTA:1;                  /**< \brief [29:29] Suspend State (rh) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_SENT_OCS_Bits;

/** \brief  Receive Data Register */
typedef struct _Ifx_SENT_RDR_Bits
{
    unsigned int RD0:4;                     /**< \brief [3:0] Receive Data Nibble 0 (rh) */
    unsigned int RD1:4;                     /**< \brief [7:4] Receive Data Nibble 1 (rh) */
    unsigned int RD2:4;                     /**< \brief [11:8] Receive Data Nibble 2 (rh) */
    unsigned int RD3:4;                     /**< \brief [15:12] Receive Data Nibble 3 (rh) */
    unsigned int RD4:4;                     /**< \brief [19:16] Receive Data Nibble 4 (rh) */
    unsigned int RD5:4;                     /**< \brief [23:20] Receive Data Nibble 5 (rh) */
    unsigned int RD6:4;                     /**< \brief [27:24] Receive Data Nibble 6 (rh) */
    unsigned int RD7:4;                     /**< \brief [31:28] Receive Data Nibble 7 (rh) */
} Ifx_SENT_RDR_Bits;

/** \brief  Receive Time Stamp Register */
typedef struct _Ifx_SENT_RTS_Bits
{
    unsigned int LTS:32;                    /**< \brief [31:0] Last Receive Time Stamp for Channel x (r) */
} Ifx_SENT_RTS_Bits;

/** \brief  Time Stamp Predivider Register */
typedef struct _Ifx_SENT_TPD_Bits
{
    unsigned int TDIV:20;                   /**< \brief [19:0] Divider Factor of Pre Divider for TSR (rw) */
    unsigned int reserved_20:12;            /**< \brief \internal Reserved */
} Ifx_SENT_TPD_Bits;

/** \brief  Time Stamp Register */
typedef struct _Ifx_SENT_TSR_Bits
{
    unsigned int CTS:32;                    /**< \brief [31:0] Current Time Stamp for the Module (r) */
} Ifx_SENT_TSR_Bits;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Sent_union
 * \{  */

/** \brief  Access Enable Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SENT_ACCEN0_Bits B;                 /**< \brief Bitfield access */
} Ifx_SENT_ACCEN0;

/** \brief  Access Enable Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SENT_ACCEN1_Bits B;                 /**< \brief Bitfield access */
} Ifx_SENT_ACCEN1;

/** \brief  Channel Fractional Divider Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SENT_CH_CFDR_Bits B;                /**< \brief Bitfield access */
} Ifx_SENT_CH_CFDR;

/** \brief  Channel Pre Divider Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SENT_CH_CPDR_Bits B;                /**< \brief Bitfield access */
} Ifx_SENT_CH_CPDR;

/** \brief  Interrupt Node Pointer Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SENT_CH_INP_Bits B;                 /**< \brief Bitfield access */
} Ifx_SENT_CH_INP;

/** \brief  Interrupt Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SENT_CH_INTCLR_Bits B;              /**< \brief Bitfield access */
} Ifx_SENT_CH_INTCLR;

/** \brief  Interrupt Enable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SENT_CH_INTEN_Bits B;               /**< \brief Bitfield access */
} Ifx_SENT_CH_INTEN;

/** \brief  Interrupt Set Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SENT_CH_INTSET_Bits B;              /**< \brief Bitfield access */
} Ifx_SENT_CH_INTSET;

/** \brief  Interrupt Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SENT_CH_INTSTAT_Bits B;             /**< \brief Bitfield access */
} Ifx_SENT_CH_INTSTAT;

/** \brief  Input and Output Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SENT_CH_IOCR_Bits B;                /**< \brief Bitfield access */
} Ifx_SENT_CH_IOCR;

/** \brief  Receiver Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SENT_CH_RCR_Bits B;                 /**< \brief Bitfield access */
} Ifx_SENT_CH_RCR;

/** \brief  Receive Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SENT_CH_RSR_Bits B;                 /**< \brief Bitfield access */
} Ifx_SENT_CH_RSR;

/** \brief  SPC Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SENT_CH_SCR_Bits B;                 /**< \brief Bitfield access */
} Ifx_SENT_CH_SCR;

/** \brief  Serial Data and Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SENT_CH_SDS_Bits B;                 /**< \brief Bitfield access */
} Ifx_SENT_CH_SDS;

/** \brief  Receive Data View Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SENT_CH_VIEW_Bits B;                /**< \brief Bitfield access */
} Ifx_SENT_CH_VIEW;

/** \brief  Watch Dog Timer Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SENT_CH_WDT_Bits B;                 /**< \brief Bitfield access */
} Ifx_SENT_CH_WDT;

/** \brief  Clock Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SENT_CLC_Bits B;                    /**< \brief Bitfield access */
} Ifx_SENT_CLC;

/** \brief  SENT Fractional Divider Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SENT_FDR_Bits B;                    /**< \brief Bitfield access */
} Ifx_SENT_FDR;

/** \brief  Module Identification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SENT_ID_Bits B;                     /**< \brief Bitfield access */
} Ifx_SENT_ID;

/** \brief  Interrupt Overview Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SENT_INTOV_Bits B;                  /**< \brief Bitfield access */
} Ifx_SENT_INTOV;

/** \brief  Kernel Reset Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SENT_KRST0_Bits B;                  /**< \brief Bitfield access */
} Ifx_SENT_KRST0;

/** \brief  Kernel Reset Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SENT_KRST1_Bits B;                  /**< \brief Bitfield access */
} Ifx_SENT_KRST1;

/** \brief  Kernel Reset Status Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SENT_KRSTCLR_Bits B;                /**< \brief Bitfield access */
} Ifx_SENT_KRSTCLR;

/** \brief  OCDS Control and Status */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SENT_OCS_Bits B;                    /**< \brief Bitfield access */
} Ifx_SENT_OCS;

/** \brief  Receive Data Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SENT_RDR_Bits B;                    /**< \brief Bitfield access */
} Ifx_SENT_RDR;

/** \brief  Receive Time Stamp Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SENT_RTS_Bits B;                    /**< \brief Bitfield access */
} Ifx_SENT_RTS;

/** \brief  Time Stamp Predivider Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SENT_TPD_Bits B;                    /**< \brief Bitfield access */
} Ifx_SENT_TPD;

/** \brief  Time Stamp Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SENT_TSR_Bits B;                    /**< \brief Bitfield access */
} Ifx_SENT_TSR;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Sent_struct
 * \{  */
/******************************************************************************/
/** \name Object L1
 * \{  */

/** \brief  Channel objects */
typedef volatile struct _Ifx_SENT_CH
{
    Ifx_SENT_CH_CPDR CPDR;                  /**< \brief 0, Channel Pre Divider Register */
    Ifx_SENT_CH_CFDR CFDR;                  /**< \brief 4, Channel Fractional Divider Register */
    Ifx_SENT_CH_RCR RCR;                    /**< \brief 8, Receiver Control Register */
    Ifx_SENT_CH_RSR RSR;                    /**< \brief C, Receive Status Register */
    Ifx_SENT_CH_SDS SDS;                    /**< \brief 10, Serial Data and Status Register */
    Ifx_SENT_CH_IOCR IOCR;                  /**< \brief 14, Input and Output Control Register */
    Ifx_SENT_CH_SCR SCR;                    /**< \brief 18, SPC Control Register */
    Ifx_SENT_CH_VIEW VIEW;                  /**< \brief 1C, Receive Data View Register */
    Ifx_SENT_CH_INTSTAT INTSTAT;            /**< \brief 20, Interrupt Status Register */
    Ifx_SENT_CH_INTSET INTSET;              /**< \brief 24, Interrupt Set Register */
    Ifx_SENT_CH_INTCLR INTCLR;              /**< \brief 28, Interrupt Clear Register */
    Ifx_SENT_CH_INTEN INTEN;                /**< \brief 2C, Interrupt Enable Register */
    Ifx_SENT_CH_INP INP;                    /**< \brief 30, Interrupt Node Pointer Register */
    Ifx_SENT_CH_WDT WDT;                    /**< \brief 34, Watch Dog Timer Register */
    unsigned char reserved_38[8];           /**< \brief 38, \internal Reserved */
} Ifx_SENT_CH;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Sent_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \brief  SENT object */
typedef volatile struct _Ifx_SENT
{
    Ifx_SENT_CLC CLC;                       /**< \brief 0, Clock Control Register */
    unsigned char reserved_4[4];            /**< \brief 4, \internal Reserved */
    Ifx_SENT_ID ID;                         /**< \brief 8, Module Identification Register */
    Ifx_SENT_FDR FDR;                       /**< \brief C, SENT Fractional Divider Register */
    unsigned char reserved_10[4];           /**< \brief 10, \internal Reserved */
    Ifx_SENT_INTOV INTOV;                   /**< \brief 14, Interrupt Overview Register */
    Ifx_SENT_TSR TSR;                       /**< \brief 18, Time Stamp Register */
    Ifx_SENT_TPD TPD;                       /**< \brief 1C, Time Stamp Predivider Register */
    unsigned char reserved_20[96];          /**< \brief 20, \internal Reserved */
    Ifx_SENT_RDR RDR[6];                    /**< \brief 80, Receive Data Register */
    unsigned char reserved_98[80];          /**< \brief 98, \internal Reserved */
    Ifx_SENT_OCS OCS;                       /**< \brief E8, OCDS Control and Status */
    Ifx_SENT_KRSTCLR KRSTCLR;               /**< \brief EC, Kernel Reset Status Clear Register */
    Ifx_SENT_KRST1 KRST1;                   /**< \brief F0, Kernel Reset Register 1 */
    Ifx_SENT_KRST0 KRST0;                   /**< \brief F4, Kernel Reset Register 0 */
    Ifx_SENT_ACCEN1 ACCEN1;                 /**< \brief F8, Access Enable Register 1 */
    Ifx_SENT_ACCEN0 ACCEN0;                 /**< \brief FC, Access Enable Register 0 */
    Ifx_SENT_CH CH[6];                      /**< \brief 100, Channel objects */
    unsigned char reserved_280[2048];       /**< \brief 280, \internal Reserved */
    Ifx_SENT_RTS RTS[6];                    /**< \brief A80, Receive Time Stamp Register */
    unsigned char reserved_A98[104];        /**< \brief A98, \internal Reserved */
} Ifx_SENT;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXSENT_REGDEF_H */
