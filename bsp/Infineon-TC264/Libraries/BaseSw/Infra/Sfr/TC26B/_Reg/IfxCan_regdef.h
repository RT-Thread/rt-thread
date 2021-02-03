/**
 * \file IfxCan_regdef.h
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
 * \defgroup IfxLld_Can Can
 * \ingroup IfxLld
 * 
 * \defgroup IfxLld_Can_Bitfields Bitfields
 * \ingroup IfxLld_Can
 * 
 * \defgroup IfxLld_Can_union Union
 * \ingroup IfxLld_Can
 * 
 * \defgroup IfxLld_Can_struct Struct
 * \ingroup IfxLld_Can
 * 
 */
#ifndef IFXCAN_REGDEF_H
#define IFXCAN_REGDEF_H 1
/******************************************************************************/
#if defined (__TASKING__)
#pragma warning 586
#endif
/******************************************************************************/
#include "Ifx_TypesReg.h"
/******************************************************************************/
/** \addtogroup IfxLld_Can_Bitfields
 * \{  */

/** \brief  Access Enable Register 0 */
typedef struct _Ifx_CAN_ACCEN0_Bits
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
} Ifx_CAN_ACCEN0_Bits;

/** \brief  Access Enable Register 1 */
typedef struct _Ifx_CAN_ACCEN1_Bits
{
    unsigned int reserved_0:32;             /**< \brief \internal Reserved */
} Ifx_CAN_ACCEN1_Bits;

/** \brief  CAN Clock Control Register */
typedef struct _Ifx_CAN_CLC_Bits
{
    unsigned int DISR:1;                    /**< \brief [0:0] Module Disable Request Bit (rw) */
    unsigned int DISS:1;                    /**< \brief [1:1] Module Disable Status Bit (rh) */
    unsigned int reserved_2:1;              /**< \brief \internal Reserved */
    unsigned int EDIS:1;                    /**< \brief [3:3] Sleep Mode Enable Control (rw) */
    unsigned int reserved_4:28;             /**< \brief \internal Reserved */
} Ifx_CAN_CLC_Bits;

/** \brief  CAN Fractional Divider Register */
typedef struct _Ifx_CAN_FDR_Bits
{
    unsigned int STEP:10;                   /**< \brief [9:0] Step Value (rw) */
    unsigned int reserved_10:4;             /**< \brief \internal Reserved */
    unsigned int DM:2;                      /**< \brief [15:14] Divider Mode (rw) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_CAN_FDR_Bits;

/** \brief  Module Identification Register */
typedef struct _Ifx_CAN_ID_Bits
{
    unsigned int MODREV:8;                  /**< \brief [7:0] Module Revision Number (r) */
    unsigned int MODTYPE:8;                 /**< \brief [15:8] Module Type (r) */
    unsigned int MODNUMBER:16;              /**< \brief [31:16] Module Number Value (r) */
} Ifx_CAN_ID_Bits;

/** \brief  Kernel Reset Register 0 */
typedef struct _Ifx_CAN_KRST0_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int RSTSTAT:1;                 /**< \brief [1:1] Kernel Reset Status (rw) */
    unsigned int reserved_2:30;             /**< \brief \internal Reserved */
} Ifx_CAN_KRST0_Bits;

/** \brief  Kernel Reset Register 1 */
typedef struct _Ifx_CAN_KRST1_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_CAN_KRST1_Bits;

/** \brief  Kernel Reset Status Clear Register */
typedef struct _Ifx_CAN_KRSTCLR_Bits
{
    unsigned int CLR:1;                     /**< \brief [0:0] Kernel Reset Status Clear (w) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_CAN_KRSTCLR_Bits;

/** \brief  List Register */
typedef struct _Ifx_CAN_LIST_Bits
{
    unsigned int BEGIN:8;                   /**< \brief [7:0] List Begin (rh) */
    unsigned int END:8;                     /**< \brief [15:8] List End (rh) */
    unsigned int SIZE:8;                    /**< \brief [23:16] List Size (rh) */
    unsigned int EMPTY:1;                   /**< \brief [24:24] List Empty Indication (rh) */
    unsigned int reserved_25:7;             /**< \brief \internal Reserved */
} Ifx_CAN_LIST_Bits;

/** \brief  Module Control Register */
typedef struct _Ifx_CAN_MCR_Bits
{
    unsigned int CLKSEL:4;                  /**< \brief [3:0] Baud Rate Logic Clock Select (rw) */
    unsigned int reserved_4:8;              /**< \brief \internal Reserved */
    unsigned int MPSEL:4;                   /**< \brief [15:12] Message Pending Selector (rw) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_CAN_MCR_Bits;

/** \brief  Measure Control Register */
typedef struct _Ifx_CAN_MECR_Bits
{
    unsigned int TH:16;                     /**< \brief [15:0] Threshold (rw) */
    unsigned int INP:4;                     /**< \brief [19:16] Interrupt Node Pointer (rw) */
    unsigned int NODE:3;                    /**< \brief [22:20] Node (rw) */
    unsigned int reserved_23:1;             /**< \brief \internal Reserved */
    unsigned int ANYED:1;                   /**< \brief [24:24] Any Edge (rw) */
    unsigned int CAPEIE:1;                  /**< \brief [25:25] Capture Event Interrupt Enable (rw) */
    unsigned int reserved_26:1;             /**< \brief \internal Reserved */
    unsigned int DEPTH:3;                   /**< \brief [29:27] Digital Glitch Filter Depth (rw) */
    unsigned int SOF:1;                     /**< \brief [30:30] Start Of Frame (rw) */
    unsigned int reserved_31:1;             /**< \brief \internal Reserved */
} Ifx_CAN_MECR_Bits;

/** \brief  Measure Status Register */
typedef struct _Ifx_CAN_MESTAT_Bits
{
    unsigned int CAPT:16;                   /**< \brief [15:0] Captured Timer (rh) */
    unsigned int CAPRED:1;                  /**< \brief [16:16] Captured Rising Edge (rh) */
    unsigned int CAPE:1;                    /**< \brief [17:17] Capture Event (rwh) */
    unsigned int reserved_18:14;            /**< \brief \internal Reserved */
} Ifx_CAN_MESTAT_Bits;

/** \brief  Module Interrupt Trigger Register */
typedef struct _Ifx_CAN_MITR_Bits
{
    unsigned int IT:16;                     /**< \brief [15:0] Interrupt Trigger (w) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_CAN_MITR_Bits;

/** \brief  Message Object  Acceptance Mask Register */
typedef struct _Ifx_CAN_MO_AMR_Bits
{
    unsigned int AM:29;                     /**< \brief [28:0] Acceptance Mask for Message Identifier (rw) */
    unsigned int MIDE:1;                    /**< \brief [29:29] Acceptance Mask Bit for Message IDE Bit (rw) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_CAN_MO_AMR_Bits;

/** \brief  Message Object  Arbitration Register */
typedef struct _Ifx_CAN_MO_AR_Bits
{
    unsigned int ID:29;                     /**< \brief [28:0] CAN Identifier of Message Object n (rwh) */
    unsigned int IDE:1;                     /**< \brief [29:29] Identifier Extension Bit of Message Object n (rwh) */
    unsigned int PRI:2;                     /**< \brief [31:30] Priority Class (rw) */
} Ifx_CAN_MO_AR_Bits;

/** \brief  Message Object  Control Register */
typedef struct _Ifx_CAN_MO_CTR_Bits
{
    unsigned int RESRXPND:1;                /**< \brief [0:0] Reset/Set Receive Pending (w) */
    unsigned int RESTXPND:1;                /**< \brief [1:1] Reset/Set Transmit Pending (w) */
    unsigned int RESRXUPD:1;                /**< \brief [2:2] Reset/Set Receive Updating (w) */
    unsigned int RESNEWDAT:1;               /**< \brief [3:3] Reset/Set New Data (w) */
    unsigned int RESMSGLST:1;               /**< \brief [4:4] Reset/Set Message Lost (w) */
    unsigned int RESMSGVAL:1;               /**< \brief [5:5] Reset/Set Message Valid (w) */
    unsigned int RESRTSEL:1;                /**< \brief [6:6] Reset/Set Receive/Transmit Selected (w) */
    unsigned int RESRXEN:1;                 /**< \brief [7:7] Reset/Set Receive Enable (w) */
    unsigned int RESTXRQ:1;                 /**< \brief [8:8] Reset/Set Transmit Request (w) */
    unsigned int RESTXEN0:1;                /**< \brief [9:9] Reset/Set Transmit Enable 0 (w) */
    unsigned int RESTXEN1:1;                /**< \brief [10:10] Reset/Set Transmit Enable 1 (w) */
    unsigned int RESDIR:1;                  /**< \brief [11:11] Reset/Set Message Direction (w) */
    unsigned int reserved_12:4;             /**< \brief \internal Reserved */
    unsigned int SETRXPND:1;                /**< \brief [16:16] Reset/Set Receive Pending (w) */
    unsigned int SETTXPND:1;                /**< \brief [17:17] Reset/Set Transmit Pending (w) */
    unsigned int SETRXUPD:1;                /**< \brief [18:18] Reset/Set Receive Updating (w) */
    unsigned int SETNEWDAT:1;               /**< \brief [19:19] Reset/Set New Data (w) */
    unsigned int SETMSGLST:1;               /**< \brief [20:20] Reset/Set Message Lost (w) */
    unsigned int SETMSGVAL:1;               /**< \brief [21:21] Reset/Set Message Valid (w) */
    unsigned int SETRTSEL:1;                /**< \brief [22:22] Reset/Set Receive/Transmit Selected (w) */
    unsigned int SETRXEN:1;                 /**< \brief [23:23] Reset/Set Receive Enable (w) */
    unsigned int SETTXRQ:1;                 /**< \brief [24:24] Reset/Set Transmit Request (w) */
    unsigned int SETTXEN0:1;                /**< \brief [25:25] Reset/Set Transmit Enable 0 (w) */
    unsigned int SETTXEN1:1;                /**< \brief [26:26] Reset/Set Transmit Enable 1 (w) */
    unsigned int SETDIR:1;                  /**< \brief [27:27] Reset/Set Message Direction (w) */
    unsigned int reserved_28:4;             /**< \brief \internal Reserved */
} Ifx_CAN_MO_CTR_Bits;

/** \brief  Message Object  Data Register High */
typedef struct _Ifx_CAN_MO_DATAH_Bits
{
    unsigned int DB4:8;                     /**< \brief [7:0] Data Byte 4 of Message Object n (rwh) */
    unsigned int DB5:8;                     /**< \brief [15:8] Data Byte 5 of Message Object n (rwh) */
    unsigned int DB6:8;                     /**< \brief [23:16] Data Byte 6 of Message Object n (rwh) */
    unsigned int DB7:8;                     /**< \brief [31:24] Data Byte 7 of Message Object n (rwh) */
} Ifx_CAN_MO_DATAH_Bits;

/** \brief  Message Object  Data Register Low */
typedef struct _Ifx_CAN_MO_DATAL_Bits
{
    unsigned int DB0:8;                     /**< \brief [7:0] Data Byte 0 of Message Object n (rwh) */
    unsigned int DB1:8;                     /**< \brief [15:8] Data Byte 1 of Message Object n (rwh) */
    unsigned int DB2:8;                     /**< \brief [23:16] Data Byte 2 of Message Object n (rwh) */
    unsigned int DB3:8;                     /**< \brief [31:24] Data Byte 3 of Message Object n (rwh) */
} Ifx_CAN_MO_DATAL_Bits;

/** \brief  Extended Message Object  Data 0 Register */
typedef struct _Ifx_CAN_MO_EDATA0_Bits
{
    unsigned int DB0:8;                     /**< \brief [7:0] Data Byte 0 of Message Object n (rwh) */
    unsigned int DB1:8;                     /**< \brief [15:8] Data Byte 1 of Message Object n (rwh) */
    unsigned int DB2:8;                     /**< \brief [23:16] Data Byte 2 of Message Object n (rwh) */
    unsigned int DB3:8;                     /**< \brief [31:24] Data Byte 3 of Message Object n (rwh) */
} Ifx_CAN_MO_EDATA0_Bits;

/** \brief  Extended Message Object  Data 1 Register */
typedef struct _Ifx_CAN_MO_EDATA1_Bits
{
    unsigned int DB0:8;                     /**< \brief [7:0] Data Byte 0 of Message Object n (rwh) */
    unsigned int DB1:8;                     /**< \brief [15:8] Data Byte 1 of Message Object n (rwh) */
    unsigned int DB2:8;                     /**< \brief [23:16] Data Byte 2 of Message Object n (rwh) */
    unsigned int DB3:8;                     /**< \brief [31:24] Data Byte 3 of Message Object n (rwh) */
} Ifx_CAN_MO_EDATA1_Bits;

/** \brief  Extended Message Object  Data 2 Register */
typedef struct _Ifx_CAN_MO_EDATA2_Bits
{
    unsigned int DB0:8;                     /**< \brief [7:0] Data Byte 0 of Message Object n (rwh) */
    unsigned int DB1:8;                     /**< \brief [15:8] Data Byte 1 of Message Object n (rwh) */
    unsigned int DB2:8;                     /**< \brief [23:16] Data Byte 2 of Message Object n (rwh) */
    unsigned int DB3:8;                     /**< \brief [31:24] Data Byte 3 of Message Object n (rwh) */
} Ifx_CAN_MO_EDATA2_Bits;

/** \brief  Extended Message Object  Data 3 Register */
typedef struct _Ifx_CAN_MO_EDATA3_Bits
{
    unsigned int DB0:8;                     /**< \brief [7:0] Data Byte 0 of Message Object n (rwh) */
    unsigned int DB1:8;                     /**< \brief [15:8] Data Byte 1 of Message Object n (rwh) */
    unsigned int DB2:8;                     /**< \brief [23:16] Data Byte 2 of Message Object n (rwh) */
    unsigned int DB3:8;                     /**< \brief [31:24] Data Byte 3 of Message Object n (rwh) */
} Ifx_CAN_MO_EDATA3_Bits;

/** \brief  Extended Message Object  Data 4 Register */
typedef struct _Ifx_CAN_MO_EDATA4_Bits
{
    unsigned int DB0:8;                     /**< \brief [7:0] Data Byte 0 of Message Object n (rwh) */
    unsigned int DB1:8;                     /**< \brief [15:8] Data Byte 1 of Message Object n (rwh) */
    unsigned int DB2:8;                     /**< \brief [23:16] Data Byte 2 of Message Object n (rwh) */
    unsigned int DB3:8;                     /**< \brief [31:24] Data Byte 3 of Message Object n (rwh) */
} Ifx_CAN_MO_EDATA4_Bits;

/** \brief  Extended Message Object  Data 5 Register */
typedef struct _Ifx_CAN_MO_EDATA5_Bits
{
    unsigned int DB0:8;                     /**< \brief [7:0] Data Byte 0 of Message Object n (rwh) */
    unsigned int DB1:8;                     /**< \brief [15:8] Data Byte 1 of Message Object n (rwh) */
    unsigned int DB2:8;                     /**< \brief [23:16] Data Byte 2 of Message Object n (rwh) */
    unsigned int DB3:8;                     /**< \brief [31:24] Data Byte 3 of Message Object n (rwh) */
} Ifx_CAN_MO_EDATA5_Bits;

/** \brief  Extended Message Object  Data 6 Register */
typedef struct _Ifx_CAN_MO_EDATA6_Bits
{
    unsigned int DB0:8;                     /**< \brief [7:0] Data Byte 0 of Message Object n (rwh) */
    unsigned int DB1:8;                     /**< \brief [15:8] Data Byte 1 of Message Object n (rwh) */
    unsigned int DB2:8;                     /**< \brief [23:16] Data Byte 2 of Message Object n (rwh) */
    unsigned int DB3:8;                     /**< \brief [31:24] Data Byte 3 of Message Object n (rwh) */
} Ifx_CAN_MO_EDATA6_Bits;

/** \brief  Message Object  Function Control Register */
typedef struct _Ifx_CAN_MO_FCR_Bits
{
    unsigned int MMC:4;                     /**< \brief [3:0] Message Mode Control (rw) */
    unsigned int RXTOE:1;                   /**< \brief [4:4] Receive Time-Out Enable (rw) */
    unsigned int BRS:1;                     /**< \brief [5:5] Bit Rate Switch (rwh) */
    unsigned int FDF:1;                     /**< \brief [6:6] CAN FD Frame Format (rwh) */
    unsigned int reserved_7:1;              /**< \brief \internal Reserved */
    unsigned int GDFS:1;                    /**< \brief [8:8] Gateway Data Frame Send (rw) */
    unsigned int IDC:1;                     /**< \brief [9:9] Identifier Copy (rw) */
    unsigned int DLCC:1;                    /**< \brief [10:10] Data Length Code Copy (rw) */
    unsigned int DATC:1;                    /**< \brief [11:11] Data Copy (rw) */
    unsigned int reserved_12:4;             /**< \brief \internal Reserved */
    unsigned int RXIE:1;                    /**< \brief [16:16] Receive Interrupt Enable (rw) */
    unsigned int TXIE:1;                    /**< \brief [17:17] Transmit Interrupt Enable (rw) */
    unsigned int OVIE:1;                    /**< \brief [18:18] Overflow Interrupt Enable (rw) */
    unsigned int reserved_19:1;             /**< \brief \internal Reserved */
    unsigned int FRREN:1;                   /**< \brief [20:20] Foreign Remote Request Enable (rw) */
    unsigned int RMM:1;                     /**< \brief [21:21] Transmit Object Remote Monitoring (rw) */
    unsigned int SDT:1;                     /**< \brief [22:22] Single Data Transfer (rw) */
    unsigned int STT:1;                     /**< \brief [23:23] Single Transmit Trial (rw) */
    unsigned int DLC:4;                     /**< \brief [27:24] Data Length Code (rwh) */
    unsigned int reserved_28:4;             /**< \brief \internal Reserved */
} Ifx_CAN_MO_FCR_Bits;

/** \brief  Message Object  FIFO/Gateway Pointer Register */
typedef struct _Ifx_CAN_MO_FGPR_Bits
{
    unsigned int BOT:8;                     /**< \brief [7:0] Bottom Pointer (rw) */
    unsigned int TOP:8;                     /**< \brief [15:8] Top Pointer (rw) */
    unsigned int CUR:8;                     /**< \brief [23:16] Current Object Pointer (rwh) */
    unsigned int SEL:8;                     /**< \brief [31:24] Object Select Pointer (rw) */
} Ifx_CAN_MO_FGPR_Bits;

/** \brief  Message Object  Interrupt Pointer Register */
typedef struct _Ifx_CAN_MO_IPR_Bits
{
    unsigned int RXINP:4;                   /**< \brief [3:0] Receive Interrupt Node Pointer (rw) */
    unsigned int TXINP:4;                   /**< \brief [7:4] Transmit Interrupt Node Pointer (rw) */
    unsigned int MPN:8;                     /**< \brief [15:8] Message Pending Number (rw) */
    unsigned int CFCVAL:16;                 /**< \brief [31:16] CAN Frame Counter Value (rwh) */
} Ifx_CAN_MO_IPR_Bits;

/** \brief  Message Object  Status Register */
typedef struct _Ifx_CAN_MO_STAT_Bits
{
    unsigned int RXPND:1;                   /**< \brief [0:0] Receive Pending (rh) */
    unsigned int TXPND:1;                   /**< \brief [1:1] Transmit Pending (rh) */
    unsigned int RXUPD:1;                   /**< \brief [2:2] Receive Updating (rh) */
    unsigned int NEWDAT:1;                  /**< \brief [3:3] New Data (rh) */
    unsigned int MSGLST:1;                  /**< \brief [4:4] Message Lost (rh) */
    unsigned int MSGVAL:1;                  /**< \brief [5:5] Message Valid (rh) */
    unsigned int RTSEL:1;                   /**< \brief [6:6] Receive/Transmit Selected (rh) */
    unsigned int RXEN:1;                    /**< \brief [7:7] Receive Enable (rh) */
    unsigned int TXRQ:1;                    /**< \brief [8:8] Transmit Request (rh) */
    unsigned int TXEN0:1;                   /**< \brief [9:9] Transmit Enable 0 (rh) */
    unsigned int TXEN1:1;                   /**< \brief [10:10] Transmit Enable 1 (rh) */
    unsigned int DIR:1;                     /**< \brief [11:11] Message Direction (rh) */
    unsigned int LIST:4;                    /**< \brief [15:12] List Allocation (rh) */
    unsigned int PPREV:8;                   /**< \brief [23:16] Pointer to Previous Message Object (rh) */
    unsigned int PNEXT:8;                   /**< \brief [31:24] Pointer to Next Message Object (rh) */
} Ifx_CAN_MO_STAT_Bits;

/** \brief  Message Index Register */
typedef struct _Ifx_CAN_MSID_Bits
{
    unsigned int INDEX:6;                   /**< \brief [5:0] Message Pending Index (rh) */
    unsigned int reserved_6:26;             /**< \brief \internal Reserved */
} Ifx_CAN_MSID_Bits;

/** \brief  Message Index Mask Register */
typedef struct _Ifx_CAN_MSIMASK_Bits
{
    unsigned int IM:32;                     /**< \brief [31:0] Message Index Mask (rw) */
} Ifx_CAN_MSIMASK_Bits;

/** \brief  Message Pending Register */
typedef struct _Ifx_CAN_MSPND_Bits
{
    unsigned int PND:32;                    /**< \brief [31:0] Message Pending (rwh) */
} Ifx_CAN_MSPND_Bits;

/** \brief  Node Bit Timing Extended View Register */
typedef struct _Ifx_CAN_N_BTEVR_Bits
{
    unsigned int BRP:6;                     /**< \brief [5:0] Baud Rate Prescaler (rw) */
    unsigned int reserved_6:2;              /**< \brief \internal Reserved */
    unsigned int SJW:4;                     /**< \brief [11:8] (Re) Synchronization Jump Width (rw) */
    unsigned int reserved_12:3;             /**< \brief \internal Reserved */
    unsigned int DIV8:1;                    /**< \brief [15:15] Divide Prescaler Clock by 8 (rw) */
    unsigned int TSEG2:5;                   /**< \brief [20:16] Time Segment After Sample Point (rw) */
    unsigned int reserved_21:1;             /**< \brief \internal Reserved */
    unsigned int TSEG1:6;                   /**< \brief [27:22] Time Segment Before Sample Point (rw) */
    unsigned int reserved_28:4;             /**< \brief \internal Reserved */
} Ifx_CAN_N_BTEVR_Bits;

/** \brief  Node Bit Timing Register */
typedef struct _Ifx_CAN_N_BTR_Bits
{
    unsigned int BRP:6;                     /**< \brief [5:0] Baud Rate Prescaler (rw) */
    unsigned int SJW:2;                     /**< \brief [7:6] (Re) Synchronization Jump Width (rw) */
    unsigned int TSEG1:4;                   /**< \brief [11:8] Time Segment Before Sample Point (rw) */
    unsigned int TSEG2:3;                   /**< \brief [14:12] Time Segment After Sample Point (rw) */
    unsigned int DIV8:1;                    /**< \brief [15:15] Divide Prescaler Clock by 8 (rw) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_CAN_N_BTR_Bits;

/** \brief  Node Control Register */
typedef struct _Ifx_CAN_N_CR_Bits
{
    unsigned int INIT:1;                    /**< \brief [0:0] Node Initialization (rwh) */
    unsigned int TRIE:1;                    /**< \brief [1:1] Transfer Interrupt Enable (rw) */
    unsigned int LECIE:1;                   /**< \brief [2:2] LEC Indicated Error Interrupt Enable (rw) */
    unsigned int ALIE:1;                    /**< \brief [3:3] Alert Interrupt Enable (rw) */
    unsigned int CANDIS:1;                  /**< \brief [4:4] CAN Disable (rw) */
    unsigned int TXDIS:1;                   /**< \brief [5:5] Transmit Disable (rw) */
    unsigned int CCE:1;                     /**< \brief [6:6] Configuration Change Enable (rw) */
    unsigned int CALM:1;                    /**< \brief [7:7] CAN Analyzer Mode (rw) */
    unsigned int SUSEN:1;                   /**< \brief [8:8] Suspend Enable (rw) */
    unsigned int FDEN:1;                    /**< \brief [9:9] CAN Flexible Data-Rate Enable (rw) */
    unsigned int reserved_10:22;            /**< \brief \internal Reserved */
} Ifx_CAN_N_CR_Bits;

/** \brief  Node Error Counter Register */
typedef struct _Ifx_CAN_N_ECNT_Bits
{
    unsigned int REC:8;                     /**< \brief [7:0] Receive Error Counter (rwh) */
    unsigned int TEC:8;                     /**< \brief [15:8] Transmit Error Counter (rwh) */
    unsigned int EWRNLVL:8;                 /**< \brief [23:16] Error Warning Level (rw) */
    unsigned int LETD:1;                    /**< \brief [24:24] Last Error Transfer Direction (rh) */
    unsigned int LEINC:1;                   /**< \brief [25:25] Last Error Increment (rh) */
    unsigned int reserved_26:6;             /**< \brief \internal Reserved */
} Ifx_CAN_N_ECNT_Bits;

/** \brief  Fast Node Bit Timing Register */
typedef struct _Ifx_CAN_N_FBTR_Bits
{
    unsigned int FBRP:6;                    /**< \brief [5:0] Fast Baud Rate Prescaler (rw) */
    unsigned int FSJW:2;                    /**< \brief [7:6] Fast (Re) Synchronization Jump Width (rw) */
    unsigned int FTSEG1:4;                  /**< \brief [11:8] Fast Time Segment Before Sample Point (rw) */
    unsigned int FTSEG2:3;                  /**< \brief [14:12] Fast Time Segment After Sample Point (rw) */
    unsigned int reserved_15:17;            /**< \brief \internal Reserved */
} Ifx_CAN_N_FBTR_Bits;

/** \brief  Node Frame Counter Register */
typedef struct _Ifx_CAN_N_FCR_Bits
{
    unsigned int CFC:16;                    /**< \brief [15:0] CAN Frame Counter (rwh) */
    unsigned int CFSEL:3;                   /**< \brief [18:16] CAN Frame Count Selection (rw) */
    unsigned int CFMOD:2;                   /**< \brief [20:19] CAN Frame Counter Mode (rw) */
    unsigned int reserved_21:1;             /**< \brief \internal Reserved */
    unsigned int CFCIE:1;                   /**< \brief [22:22] CAN Frame Count Interrupt Enable (rw) */
    unsigned int CFCOV:1;                   /**< \brief [23:23] CAN Frame Counter Overflow Flag (rwh) */
    unsigned int reserved_24:8;             /**< \brief \internal Reserved */
} Ifx_CAN_N_FCR_Bits;

/** \brief  Node Interrupt Pointer Register */
typedef struct _Ifx_CAN_N_IPR_Bits
{
    unsigned int ALINP:4;                   /**< \brief [3:0] Alert Interrupt Node Pointer (rw) */
    unsigned int LECINP:4;                  /**< \brief [7:4] Last Error Code Interrupt Node Pointer (rw) */
    unsigned int TRINP:4;                   /**< \brief [11:8] Transfer OK Interrupt Node Pointer (rw) */
    unsigned int CFCINP:4;                  /**< \brief [15:12] Frame Counter Interrupt Node Pointer (rw) */
    unsigned int TEINP:4;                   /**< \brief [19:16] Timer Event Interrupt Node Pointer (rw) */
    unsigned int reserved_20:12;            /**< \brief \internal Reserved */
} Ifx_CAN_N_IPR_Bits;

/** \brief  Node Port Control Register */
typedef struct _Ifx_CAN_N_PCR_Bits
{
    unsigned int RXSEL:3;                   /**< \brief [2:0] Receive Select (rw) */
    unsigned int reserved_3:5;              /**< \brief \internal Reserved */
    unsigned int LBM:1;                     /**< \brief [8:8] Loop-Back Mode (rw) */
    unsigned int reserved_9:23;             /**< \brief \internal Reserved */
} Ifx_CAN_N_PCR_Bits;

/** \brief  Node Status Register */
typedef struct _Ifx_CAN_N_SR_Bits
{
    unsigned int LEC:3;                     /**< \brief [2:0] Last Error Code (rwh) */
    unsigned int TXOK:1;                    /**< \brief [3:3] Message Transmitted Successfully (rwh) */
    unsigned int RXOK:1;                    /**< \brief [4:4] Message Received Successfully (rwh) */
    unsigned int ALERT:1;                   /**< \brief [5:5] Alert Warning (rwh) */
    unsigned int EWRN:1;                    /**< \brief [6:6] Error Warning Status (rh) */
    unsigned int BOFF:1;                    /**< \brief [7:7] Bus-off Status (rh) */
    unsigned int LLE:1;                     /**< \brief [8:8] List Length Error (rwh) */
    unsigned int LOE:1;                     /**< \brief [9:9] List Object Error (rwh) */
    unsigned int SUSACK:1;                  /**< \brief [10:10] Suspend Acknowledge (rh) */
    unsigned int RESI:1;                    /**< \brief [11:11] Received Error State Indicator Flag This bit is an error flag that is set when the ESI flag in a received CAN FD frame is set. (rh) */
    unsigned int FLEC:3;                    /**< \brief [14:12] Fast Last Error Code (rwh) */
    unsigned int reserved_15:17;            /**< \brief \internal Reserved */
} Ifx_CAN_N_SR_Bits;

/** \brief  Node Timer Clock Control Register */
typedef struct _Ifx_CAN_N_TCCR_Bits
{
    unsigned int reserved_0:8;              /**< \brief \internal Reserved */
    unsigned int TPSC:4;                    /**< \brief [11:8] Timer Prescaler (rw) */
    unsigned int reserved_12:6;             /**< \brief \internal Reserved */
    unsigned int TRIGSRC:3;                 /**< \brief [20:18] Trigger Source (rw) */
    unsigned int reserved_21:11;            /**< \brief \internal Reserved */
} Ifx_CAN_N_TCCR_Bits;

/** \brief  Node Transmitter Delay Compensation Register */
typedef struct _Ifx_CAN_N_TDCR_Bits
{
    unsigned int TDCV:5;                    /**< \brief [4:0] Transmitter Delay Compensation Value (r) */
    unsigned int reserved_5:3;              /**< \brief \internal Reserved */
    unsigned int TDCO:4;                    /**< \brief [11:8] Transmitter Delay Compensation Offset (rw) */
    unsigned int reserved_12:3;             /**< \brief \internal Reserved */
    unsigned int TDC:1;                     /**< \brief [15:15] Transmitter Delay Compensation Enable (rw) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_CAN_N_TDCR_Bits;

/** \brief  Node Timer Receive Timeout Register */
typedef struct _Ifx_CAN_N_TRTR_Bits
{
    unsigned int RELOAD:16;                 /**< \brief [15:0] Reload Value (rw) */
    unsigned int reserved_16:6;             /**< \brief \internal Reserved */
    unsigned int TEIE:1;                    /**< \brief [22:22] Timer Event Interrupt Enable (rw) */
    unsigned int TE:1;                      /**< \brief [23:23] Timer Event (rwh) */
    unsigned int reserved_24:8;             /**< \brief \internal Reserved */
} Ifx_CAN_N_TRTR_Bits;

/** \brief  Node Timer Transmit Trigger Register */
typedef struct _Ifx_CAN_N_TTTR_Bits
{
    unsigned int RELOAD:16;                 /**< \brief [15:0] Reload Value (rw) */
    unsigned int TXMO:8;                    /**< \brief [23:16] Transmit Message Object (rw) */
    unsigned int STRT:1;                    /**< \brief [24:24] Timer Start (rw) */
    unsigned int reserved_25:7;             /**< \brief \internal Reserved */
} Ifx_CAN_N_TTTR_Bits;

/** \brief  OCDS Control and Status */
typedef struct _Ifx_CAN_OCS_Bits
{
    unsigned int TGS:2;                     /**< \brief [1:0] Trigger Set for OTGB0/1 (rw) */
    unsigned int TGB:1;                     /**< \brief [2:2] OTGB0/1 Bus Select (rw) */
    unsigned int TG_P:1;                    /**< \brief [3:3] TGS, TGB Write Protection (w) */
    unsigned int reserved_4:20;             /**< \brief \internal Reserved */
    unsigned int SUS:4;                     /**< \brief [27:24] OCDS Suspend Control (rw) */
    unsigned int SUS_P:1;                   /**< \brief [28:28] SUS Write Protection (w) */
    unsigned int SUSSTA:1;                  /**< \brief [29:29] Suspend State (rh) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_CAN_OCS_Bits;

/** \brief  Panel Control Register */
typedef struct _Ifx_CAN_PANCTR_Bits
{
    unsigned int PANCMD:8;                  /**< \brief [7:0] Panel Command (rwh) */
    unsigned int BUSY:1;                    /**< \brief [8:8] Panel Busy Flag (rh) */
    unsigned int RBUSY:1;                   /**< \brief [9:9] Result Busy Flag (rh) */
    unsigned int reserved_10:6;             /**< \brief \internal Reserved */
    unsigned int PANAR1:8;                  /**< \brief [23:16] Panel Argument 1 (rwh) */
    unsigned int PANAR2:8;                  /**< \brief [31:24] Panel Argument 2 (rwh) */
} Ifx_CAN_PANCTR_Bits;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Can_union
 * \{  */

/** \brief  Access Enable Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_ACCEN0_Bits B;                  /**< \brief Bitfield access */
} Ifx_CAN_ACCEN0;

/** \brief  Access Enable Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_ACCEN1_Bits B;                  /**< \brief Bitfield access */
} Ifx_CAN_ACCEN1;

/** \brief  CAN Clock Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_CLC_Bits B;                     /**< \brief Bitfield access */
} Ifx_CAN_CLC;

/** \brief  CAN Fractional Divider Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_FDR_Bits B;                     /**< \brief Bitfield access */
} Ifx_CAN_FDR;

/** \brief  Module Identification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_ID_Bits B;                      /**< \brief Bitfield access */
} Ifx_CAN_ID;

/** \brief  Kernel Reset Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_KRST0_Bits B;                   /**< \brief Bitfield access */
} Ifx_CAN_KRST0;

/** \brief  Kernel Reset Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_KRST1_Bits B;                   /**< \brief Bitfield access */
} Ifx_CAN_KRST1;

/** \brief  Kernel Reset Status Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_KRSTCLR_Bits B;                 /**< \brief Bitfield access */
} Ifx_CAN_KRSTCLR;

/** \brief  List Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_LIST_Bits B;                    /**< \brief Bitfield access */
} Ifx_CAN_LIST;

/** \brief  Module Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_MCR_Bits B;                     /**< \brief Bitfield access */
} Ifx_CAN_MCR;

/** \brief  Measure Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_MECR_Bits B;                    /**< \brief Bitfield access */
} Ifx_CAN_MECR;

/** \brief  Measure Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_MESTAT_Bits B;                  /**< \brief Bitfield access */
} Ifx_CAN_MESTAT;

/** \brief  Module Interrupt Trigger Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_MITR_Bits B;                    /**< \brief Bitfield access */
} Ifx_CAN_MITR;

/** \brief  Message Object  Acceptance Mask Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_MO_AMR_Bits B;                  /**< \brief Bitfield access */
} Ifx_CAN_MO_AMR;

/** \brief  Message Object  Arbitration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_MO_AR_Bits B;                   /**< \brief Bitfield access */
} Ifx_CAN_MO_AR;

/** \brief  Message Object  Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_MO_CTR_Bits B;                  /**< \brief Bitfield access */
} Ifx_CAN_MO_CTR;

/** \brief  Message Object  Data Register High */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_MO_DATAH_Bits B;                /**< \brief Bitfield access */
} Ifx_CAN_MO_DATAH;

/** \brief  Message Object  Data Register Low */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_MO_DATAL_Bits B;                /**< \brief Bitfield access */
} Ifx_CAN_MO_DATAL;

/** \brief  Extended Message Object  Data 0 Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_MO_EDATA0_Bits B;               /**< \brief Bitfield access */
} Ifx_CAN_MO_EDATA0;

/** \brief  Extended Message Object  Data 1 Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_MO_EDATA1_Bits B;               /**< \brief Bitfield access */
} Ifx_CAN_MO_EDATA1;

/** \brief  Extended Message Object  Data 2 Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_MO_EDATA2_Bits B;               /**< \brief Bitfield access */
} Ifx_CAN_MO_EDATA2;

/** \brief  Extended Message Object  Data 3 Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_MO_EDATA3_Bits B;               /**< \brief Bitfield access */
} Ifx_CAN_MO_EDATA3;

/** \brief  Extended Message Object  Data 4 Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_MO_EDATA4_Bits B;               /**< \brief Bitfield access */
} Ifx_CAN_MO_EDATA4;

/** \brief  Extended Message Object  Data 5 Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_MO_EDATA5_Bits B;               /**< \brief Bitfield access */
} Ifx_CAN_MO_EDATA5;

/** \brief  Extended Message Object  Data 6 Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_MO_EDATA6_Bits B;               /**< \brief Bitfield access */
} Ifx_CAN_MO_EDATA6;

/** \brief  Message Object  Function Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_MO_FCR_Bits B;                  /**< \brief Bitfield access */
} Ifx_CAN_MO_FCR;

/** \brief  Message Object  FIFO/Gateway Pointer Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_MO_FGPR_Bits B;                 /**< \brief Bitfield access */
} Ifx_CAN_MO_FGPR;

/** \brief  Message Object  Interrupt Pointer Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_MO_IPR_Bits B;                  /**< \brief Bitfield access */
} Ifx_CAN_MO_IPR;

/** \brief  Message Object  Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_MO_STAT_Bits B;                 /**< \brief Bitfield access */
} Ifx_CAN_MO_STAT;

/** \brief  Message Index Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_MSID_Bits B;                    /**< \brief Bitfield access */
} Ifx_CAN_MSID;

/** \brief  Message Index Mask Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_MSIMASK_Bits B;                 /**< \brief Bitfield access */
} Ifx_CAN_MSIMASK;

/** \brief  Message Pending Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_MSPND_Bits B;                   /**< \brief Bitfield access */
} Ifx_CAN_MSPND;

/** \brief  Node Bit Timing Extended View Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_N_BTEVR_Bits B;                 /**< \brief Bitfield access */
} Ifx_CAN_N_BTEVR;

/** \brief  Node Bit Timing Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_N_BTR_Bits B;                   /**< \brief Bitfield access */
} Ifx_CAN_N_BTR;

/** \brief  Node Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_N_CR_Bits B;                    /**< \brief Bitfield access */
} Ifx_CAN_N_CR;

/** \brief  Node Error Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_N_ECNT_Bits B;                  /**< \brief Bitfield access */
} Ifx_CAN_N_ECNT;

/** \brief  Fast Node Bit Timing Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_N_FBTR_Bits B;                  /**< \brief Bitfield access */
} Ifx_CAN_N_FBTR;

/** \brief  Node Frame Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_N_FCR_Bits B;                   /**< \brief Bitfield access */
} Ifx_CAN_N_FCR;

/** \brief  Node Interrupt Pointer Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_N_IPR_Bits B;                   /**< \brief Bitfield access */
} Ifx_CAN_N_IPR;

/** \brief  Node Port Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_N_PCR_Bits B;                   /**< \brief Bitfield access */
} Ifx_CAN_N_PCR;

/** \brief  Node Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_N_SR_Bits B;                    /**< \brief Bitfield access */
} Ifx_CAN_N_SR;

/** \brief  Node Timer Clock Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_N_TCCR_Bits B;                  /**< \brief Bitfield access */
} Ifx_CAN_N_TCCR;

/** \brief  Node Transmitter Delay Compensation Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_N_TDCR_Bits B;                  /**< \brief Bitfield access */
} Ifx_CAN_N_TDCR;

/** \brief  Node Timer Receive Timeout Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_N_TRTR_Bits B;                  /**< \brief Bitfield access */
} Ifx_CAN_N_TRTR;

/** \brief  Node Timer Transmit Trigger Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_N_TTTR_Bits B;                  /**< \brief Bitfield access */
} Ifx_CAN_N_TTTR;

/** \brief  OCDS Control and Status */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_OCS_Bits B;                     /**< \brief Bitfield access */
} Ifx_CAN_OCS;

/** \brief  Panel Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CAN_PANCTR_Bits B;                  /**< \brief Bitfield access */
} Ifx_CAN_PANCTR;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Can_struct
 * \{  */
/******************************************************************************/
/** \name Object L1
 * \{  */

/** \brief  Message object */
typedef volatile struct _Ifx_CAN_MO
{
    union
    {
        Ifx_CAN_MO_EDATA0 EDATA0;           /**< \brief 0, Message Object  Function Control Register */
        Ifx_CAN_MO_FCR FCR;                 /**< \brief 0, Message Object  Function Control Register */
    };

    union
    {
        Ifx_CAN_MO_EDATA1 EDATA1;           /**< \brief 4, Message Object  FIFO/Gateway Pointer Register */
        Ifx_CAN_MO_FGPR FGPR;               /**< \brief 4, Message Object  FIFO/Gateway Pointer Register */
    };

    union
    {
        Ifx_CAN_MO_EDATA2 EDATA2;           /**< \brief 8, Message Object  Interrupt Pointer Register */
        Ifx_CAN_MO_IPR IPR;                 /**< \brief 8, Message Object  Interrupt Pointer Register */
    };

    union
    {
        Ifx_CAN_MO_AMR AMR;                 /**< \brief C, Message Object  Acceptance Mask Register */
        Ifx_CAN_MO_EDATA3 EDATA3;           /**< \brief C, Message Object  Acceptance Mask Register */
    };

    union
    {
        Ifx_CAN_MO_DATAL DATAL;             /**< \brief 10, Message Object  Data Register Low */
        Ifx_CAN_MO_EDATA4 EDATA4;           /**< \brief 10, Message Object  Data Register Low */
    };

    union
    {
        Ifx_CAN_MO_DATAH DATAH;             /**< \brief 14, Message Object  Data Register High */
        Ifx_CAN_MO_EDATA5 EDATA5;           /**< \brief 14, Message Object  Data Register High */
    };

    union
    {
        Ifx_CAN_MO_AR AR;                   /**< \brief 18, Message Object  Arbitration Register */
        Ifx_CAN_MO_EDATA6 EDATA6;           /**< \brief 18, Message Object  Arbitration Register */
    };

    union
    {
        Ifx_CAN_MO_CTR CTR;                 /**< \brief 1C, Message Object  Control Register */
        Ifx_CAN_MO_STAT STAT;               /**< \brief 1C, Message Object  Control Register */
    };

} Ifx_CAN_MO;

/** \brief  Node object */
typedef volatile struct _Ifx_CAN_N
{
    Ifx_CAN_N_CR CR;                        /**< \brief 0, Node Control Register */
    Ifx_CAN_N_SR SR;                        /**< \brief 4, Node Status Register */
    Ifx_CAN_N_IPR IPR;                      /**< \brief 8, Node Interrupt Pointer Register */
    Ifx_CAN_N_PCR PCR;                      /**< \brief C, Node Port Control Register */
    union
    {
        Ifx_CAN_N_BTEVR BTEVR;              /**< \brief 10, Node Bit Timing Register */
        Ifx_CAN_N_BTR BTR;                  /**< \brief 10, Node Bit Timing Register */
    };

    Ifx_CAN_N_ECNT ECNT;                    /**< \brief 14, Node Error Counter Register */
    Ifx_CAN_N_FCR FCR;                      /**< \brief 18, Node Frame Counter Register */
    Ifx_CAN_N_TCCR TCCR;                    /**< \brief 1C, Node Timer Clock Control Register */
    Ifx_CAN_N_TRTR TRTR;                    /**< \brief 20, Node Timer Receive Timeout Register */
    Ifx_CAN_N_TTTR TATTR;                   /**< \brief 24, Node Timer A Transmit Trigger Register */
    Ifx_CAN_N_TTTR TBTTR;                   /**< \brief 28, Node Timer B Transmit Trigger Register */
    Ifx_CAN_N_TTTR TCTTR;                   /**< \brief 2C, Node Timer C Transmit Trigger Register */
    unsigned char reserved_30[8];           /**< \brief 30, \internal Reserved */
    Ifx_CAN_N_FBTR FBTR;                    /**< \brief 38, Fast Node Bit Timing Register */
    Ifx_CAN_N_TDCR TDCR;                    /**< \brief 3C, Node Transmitter Delay Compensation Register */
    unsigned char reserved_40[192];         /**< \brief 40, \internal Reserved */
} Ifx_CAN_N;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Can_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \brief  CAN object */
typedef volatile struct _Ifx_CAN
{
    Ifx_CAN_CLC CLC;                        /**< \brief 0, CAN Clock Control Register */
    unsigned char reserved_4[4];            /**< \brief 4, \internal Reserved */
    Ifx_CAN_ID ID;                          /**< \brief 8, Module Identification Register */
    Ifx_CAN_FDR FDR;                        /**< \brief C, CAN Fractional Divider Register */
    unsigned char reserved_10[216];         /**< \brief 10, \internal Reserved */
    Ifx_CAN_OCS OCS;                        /**< \brief E8, OCDS Control and Status */
    Ifx_CAN_KRSTCLR KRSTCLR;                /**< \brief EC, Kernel Reset Status Clear Register */
    Ifx_CAN_KRST1 KRST1;                    /**< \brief F0, Kernel Reset Register 1 */
    Ifx_CAN_KRST0 KRST0;                    /**< \brief F4, Kernel Reset Register 0 */
    Ifx_CAN_ACCEN1 ACCEN1;                  /**< \brief F8, Access Enable Register 1 */
    Ifx_CAN_ACCEN0 ACCEN0;                  /**< \brief FC, Access Enable Register 0 */
    Ifx_CAN_LIST LIST[16];                  /**< \brief 100, List Register */
    Ifx_CAN_MSPND MSPND[8];                 /**< \brief 140, Message Pending Register */
    unsigned char reserved_160[32];         /**< \brief 160, \internal Reserved */
    Ifx_CAN_MSID MSID[8];                   /**< \brief 180, Message Index Register */
    unsigned char reserved_1A0[32];         /**< \brief 1A0, \internal Reserved */
    Ifx_CAN_MSIMASK MSIMASK;                /**< \brief 1C0, Message Index Mask Register */
    Ifx_CAN_PANCTR PANCTR;                  /**< \brief 1C4, Panel Control Register */
    Ifx_CAN_MCR MCR;                        /**< \brief 1C8, Module Control Register */
    Ifx_CAN_MITR MITR;                      /**< \brief 1CC, Module Interrupt Trigger Register */
    Ifx_CAN_MECR MECR;                      /**< \brief 1D0, Measure Control Register */
    Ifx_CAN_MESTAT MESTAT;                  /**< \brief 1D4, Measure Status Register */
    unsigned char reserved_1D8[40];         /**< \brief 1D8, \internal Reserved */
    Ifx_CAN_N N[5];                         /**< \brief 200, Node object */
    unsigned char reserved_700[2304];       /**< \brief 700, \internal Reserved */
    Ifx_CAN_MO MO[256];                     /**< \brief 1000, Message objects */
    unsigned char reserved_3000[4096];      /**< \brief 3000, \internal Reserved */
} Ifx_CAN;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
#if defined (__TASKING__)
#pragma warning restore
#endif
/******************************************************************************/
#endif /* IFXCAN_REGDEF_H */
