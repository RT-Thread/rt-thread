/**
 * \file IfxQspi_regdef.h
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
 * \defgroup IfxLld_Qspi Qspi
 * \ingroup IfxLld
 * 
 * \defgroup IfxLld_Qspi_Bitfields Bitfields
 * \ingroup IfxLld_Qspi
 * 
 * \defgroup IfxLld_Qspi_union Union
 * \ingroup IfxLld_Qspi
 * 
 * \defgroup IfxLld_Qspi_struct Struct
 * \ingroup IfxLld_Qspi
 * 
 */
#ifndef IFXQSPI_REGDEF_H
#define IFXQSPI_REGDEF_H 1
/******************************************************************************/
#include "Ifx_TypesReg.h"
/******************************************************************************/
/** \addtogroup IfxLld_Qspi_Bitfields
 * \{  */

/** \brief  Access Enable Register 0 */
typedef struct _Ifx_QSPI_ACCEN0_Bits
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
} Ifx_QSPI_ACCEN0_Bits;

/** \brief  Access Enable Register 1 */
typedef struct _Ifx_QSPI_ACCEN1_Bits
{
    unsigned int reserved_0:32;             /**< \brief \internal Reserved */
} Ifx_QSPI_ACCEN1_Bits;

/** \brief  Basic Configuration Register */
typedef struct _Ifx_QSPI_BACON_Bits
{
    unsigned int LAST:1;                    /**< \brief [0:0] Last Word in a Frame (rh) */
    unsigned int IPRE:3;                    /**< \brief [3:1] Prescaler for the Idle Delay (rh) */
    unsigned int IDLE:3;                    /**< \brief [6:4] Idle Delay Length (rh) */
    unsigned int LPRE:3;                    /**< \brief [9:7] Prescaler for the Leading Delay (rh) */
    unsigned int LEAD:3;                    /**< \brief [12:10] Leading Delay Length (rh) */
    unsigned int TPRE:3;                    /**< \brief [15:13] Prescaler for the Trailing Delay (rh) */
    unsigned int TRAIL:3;                   /**< \brief [18:16] Trailing Delay Length (rh) */
    unsigned int PARTYP:1;                  /**< \brief [19:19] Parity Type (rh) */
    unsigned int UINT:1;                    /**< \brief [20:20] User Interrupt at the PT1 Event in the Subsequent Frames (rh) */
    unsigned int MSB:1;                     /**< \brief [21:21] Shift MSB or LSB First (rh) */
    unsigned int BYTE:1;                    /**< \brief [22:22] Byte (rh) */
    unsigned int DL:5;                      /**< \brief [27:23] Data Length (rh) */
    unsigned int CS:4;                      /**< \brief [31:28] Channel Select (rh) */
} Ifx_QSPI_BACON_Bits;

/** \brief  BACON_ENTRY Register */
typedef struct _Ifx_QSPI_BACONENTRY_Bits
{
    unsigned int E:32;                      /**< \brief [31:0] Entry Point to the TxFIFO (w) */
} Ifx_QSPI_BACONENTRY_Bits;

/** \brief  Capture Control Register */
typedef struct _Ifx_QSPI_CAPCON_Bits
{
    unsigned int CAP:15;                    /**< \brief [14:0] Captured Value (rh) */
    unsigned int OVF:1;                     /**< \brief [15:15] Overflow Flag (rh) */
    unsigned int EDGECON:2;                 /**< \brief [17:16] Edge Configuration (rw) */
    unsigned int INS:2;                     /**< \brief [19:18] Input Selection (rw) */
    unsigned int EN:1;                      /**< \brief [20:20] Enable Bit of the Capture Timer (rw) */
    unsigned int reserved_21:7;             /**< \brief \internal Reserved */
    unsigned int CAPC:1;                    /**< \brief [28:28] Capture Flag Clear (w) */
    unsigned int CAPS:1;                    /**< \brief [29:29] Capture Flag Set (w) */
    unsigned int CAPF:1;                    /**< \brief [30:30] Capture Flag (rh) */
    unsigned int CAPSEL:1;                  /**< \brief [31:31] Capture Interrupt Select Bit (rw) */
} Ifx_QSPI_CAPCON_Bits;

/** \brief  Clock Control Register */
typedef struct _Ifx_QSPI_CLC_Bits
{
    unsigned int DISR:1;                    /**< \brief [0:0] Module Disable Request Bit (rw) */
    unsigned int DISS:1;                    /**< \brief [1:1] Module Disable Status Bit (rh) */
    unsigned int reserved_2:1;              /**< \brief \internal Reserved */
    unsigned int EDIS:1;                    /**< \brief [3:3] Sleep Mode Enable Control (rw) */
    unsigned int reserved_4:28;             /**< \brief \internal Reserved */
} Ifx_QSPI_CLC_Bits;

/** \brief  DATA_ENTRY Register */
typedef struct _Ifx_QSPI_DATAENTRY_Bits
{
    unsigned int E:32;                      /**< \brief [31:0] Entry Point to the TxFIFO (w) */
} Ifx_QSPI_DATAENTRY_Bits;

/** \brief  Configuration Extension */
typedef struct _Ifx_QSPI_ECON_Bits
{
    unsigned int Q:6;                       /**< \brief [5:0] Time Quantum (rw) */
    unsigned int A:2;                       /**< \brief [7:6] Bit Segment 1 (rw) */
    unsigned int B:2;                       /**< \brief [9:8] Bit Segment 2 (rw) */
    unsigned int C:2;                       /**< \brief [11:10] Bit Segment 3 (rw) */
    unsigned int CPH:1;                     /**< \brief [12:12] Clock Phase (rw) */
    unsigned int CPOL:1;                    /**< \brief [13:13] Clock Polarity (rw) */
    unsigned int PAREN:1;                   /**< \brief [14:14] Enable Parity Check (rw) */
    unsigned int reserved_15:15;            /**< \brief \internal Reserved */
    unsigned int BE:2;                      /**< \brief [31:30] Permutate bytes to / from Big Endian (rw) */
} Ifx_QSPI_ECON_Bits;

/** \brief  Flags Clear Register */
typedef struct _Ifx_QSPI_FLAGSCLEAR_Bits
{
    unsigned int ERRORCLEARS:9;             /**< \brief [8:0] Write Only Bits for Clearing the Error Flags (w) */
    unsigned int TXC:1;                     /**< \brief [9:9] Transmit Event Flag Clear (w) */
    unsigned int RXC:1;                     /**< \brief [10:10] Receive Event Flag Clear (w) */
    unsigned int PT1C:1;                    /**< \brief [11:11] PT1 Event Flag Clear (w) */
    unsigned int PT2C:1;                    /**< \brief [12:12] PT2 Event Flag Clear (w) */
    unsigned int reserved_13:2;             /**< \brief \internal Reserved */
    unsigned int USRC:1;                    /**< \brief [15:15] User Event Flag Clear (w) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_QSPI_FLAGSCLEAR_Bits;

/** \brief  Global Configuration Register 1 */
typedef struct _Ifx_QSPI_GLOBALCON1_Bits
{
    unsigned int ERRORENS:9;                /**< \brief [8:0] Error Enable Bits (rw) */
    unsigned int TXEN:1;                    /**< \brief [9:9] Tx Interrupt Event Enable (rw) */
    unsigned int RXEN:1;                    /**< \brief [10:10] RX Interrupt Event Enable (rw) */
    unsigned int PT1EN:1;                   /**< \brief [11:11] Interrupt on PT1 Event Enable (rw) */
    unsigned int PT2EN:1;                   /**< \brief [12:12] Interrupt on PT2 Event Enable (rw) */
    unsigned int reserved_13:2;             /**< \brief \internal Reserved */
    unsigned int USREN:1;                   /**< \brief [15:15] Interrupt on USR Event Enable (rw) */
    unsigned int TXFIFOINT:2;               /**< \brief [17:16] Transmit FIFO Interrupt Threshold (rw) */
    unsigned int RXFIFOINT:2;               /**< \brief [19:18] Receive FIFO Interrupt Threshold (rw) */
    unsigned int PT1:3;                     /**< \brief [22:20] Phase Transition Event 1 (rw) */
    unsigned int PT2:3;                     /**< \brief [25:23] Phase Transition Event 2 (rw) */
    unsigned int TXFM:2;                    /**< \brief [27:26] TXFIFO Mode (rw) */
    unsigned int RXFM:2;                    /**< \brief [29:28] RXFIFO Mode (rw) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_QSPI_GLOBALCON1_Bits;

/** \brief  Global Configuration Register */
typedef struct _Ifx_QSPI_GLOBALCON_Bits
{
    unsigned int TQ:8;                      /**< \brief [7:0] Global Time Quantum Length (rw) */
    unsigned int reserved_8:1;              /**< \brief \internal Reserved */
    unsigned int SI:1;                      /**< \brief [9:9] Status Injection (rw) */
    unsigned int EXPECT:4;                  /**< \brief [13:10] Time-Out Value for the Expect Phase (rw) */
    unsigned int LB:1;                      /**< \brief [14:14] Loop-Back Control (rw) */
    unsigned int DEL0:1;                    /**< \brief [15:15] Delayed Mode for SLSO0 (rw) */
    unsigned int STROBE:5;                  /**< \brief [20:16] Strobe Delay for SLSO0 in Delayed Mode (rw) */
    unsigned int SRF:1;                     /**< \brief [21:21] Stop on RxFIFO Full (rw) */
    unsigned int STIP:1;                    /**< \brief [22:22] Slave Transmit Idle State Polarity (rw) */
    unsigned int reserved_23:1;             /**< \brief \internal Reserved */
    unsigned int EN:1;                      /**< \brief [24:24] Enable Bit (rwh) */
    unsigned int MS:2;                      /**< \brief [26:25] Master Slave Mode (rw) */
    unsigned int AREN:1;                    /**< \brief [27:27] Automatic Reset Enable (rw) */
    unsigned int RESETS:4;                  /**< \brief [31:28] Bits for resetting sub-modules per software (w) */
} Ifx_QSPI_GLOBALCON_Bits;

/** \brief  Module Identification Register */
typedef struct _Ifx_QSPI_ID_Bits
{
    unsigned int MODREV:8;                  /**< \brief [7:0] Module Revision Number (r) */
    unsigned int MODTYPE:8;                 /**< \brief [15:8] Module Type (r) */
    unsigned int MODNUMBER:16;              /**< \brief [31:16] Module Number Value (r) */
} Ifx_QSPI_ID_Bits;

/** \brief  Kernel Reset Register 0 */
typedef struct _Ifx_QSPI_KRST0_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int RSTSTAT:1;                 /**< \brief [1:1] Kernel Reset Status (rh) */
    unsigned int reserved_2:30;             /**< \brief \internal Reserved */
} Ifx_QSPI_KRST0_Bits;

/** \brief  Kernel Reset Register 1 */
typedef struct _Ifx_QSPI_KRST1_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_QSPI_KRST1_Bits;

/** \brief  Kernel Reset Status Clear Register */
typedef struct _Ifx_QSPI_KRSTCLR_Bits
{
    unsigned int CLR:1;                     /**< \brief [0:0] Kernel Reset Status Clear (w) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_QSPI_KRSTCLR_Bits;

/** \brief  MIX_ENTRY Register */
typedef struct _Ifx_QSPI_MIXENTRY_Bits
{
    unsigned int E:32;                      /**< \brief [31:0] Entry Point to the TxFIFO (w) */
} Ifx_QSPI_MIXENTRY_Bits;

/** \brief  OCDS Control and Status */
typedef struct _Ifx_QSPI_OCS_Bits
{
    unsigned int reserved_0:24;             /**< \brief \internal Reserved */
    unsigned int SUS:4;                     /**< \brief [27:24] OCDS Suspend Control (rw) */
    unsigned int SUS_P:1;                   /**< \brief [28:28] SUS Write Protection (w) */
    unsigned int SUSSTA:1;                  /**< \brief [29:29] Suspend State (rh) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_QSPI_OCS_Bits;

/** \brief  Port Input Select Register */
typedef struct _Ifx_QSPI_PISEL_Bits
{
    unsigned int MRIS:3;                    /**< \brief [2:0] Master Mode Receive Input Select (rw) */
    unsigned int reserved_3:1;              /**< \brief \internal Reserved */
    unsigned int SRIS:3;                    /**< \brief [6:4] Slave Mode Receive Input Select (rw) */
    unsigned int reserved_7:1;              /**< \brief \internal Reserved */
    unsigned int SCIS:3;                    /**< \brief [10:8] Slave Mode Clock Input Select (rw) */
    unsigned int reserved_11:1;             /**< \brief \internal Reserved */
    unsigned int SLSIS:3;                   /**< \brief [14:12] Slave Mode Slave Select Input Selection (rw) */
    unsigned int reserved_15:17;            /**< \brief \internal Reserved */
} Ifx_QSPI_PISEL_Bits;

/** \brief  RX_EXIT Register */
typedef struct _Ifx_QSPI_RXEXIT_Bits
{
    unsigned int E:32;                      /**< \brief [31:0] Read Point from the RxFIFO (r) */
} Ifx_QSPI_RXEXIT_Bits;

/** \brief  RX_EXIT Debug Register */
typedef struct _Ifx_QSPI_RXEXITD_Bits
{
    unsigned int E:32;                      /**< \brief [31:0] Read Point from the RxFIFO (r) */
} Ifx_QSPI_RXEXITD_Bits;

/** \brief  Slave Select Output Control Register */
typedef struct _Ifx_QSPI_SSOC_Bits
{
    unsigned int AOL:16;                    /**< \brief [15:0] Active Output Level for the SLSO Outputs (rw) */
    unsigned int OEN:16;                    /**< \brief [31:16] Enable Bits for the SLSO Outputs (rw) */
} Ifx_QSPI_SSOC_Bits;

/** \brief  Status Register 1 */
typedef struct _Ifx_QSPI_STATUS1_Bits
{
    unsigned int BITCOUNT:8;                /**< \brief [7:0] Number of the bit shifted out (r) */
    unsigned int reserved_8:20;             /**< \brief \internal Reserved */
    unsigned int BRDEN:1;                   /**< \brief [28:28] Baud Rate Deviation Enable (rw) */
    unsigned int BRD:1;                     /**< \brief [29:29] Baud Rate Deviation Flag (rwh) */
    unsigned int SPDEN:1;                   /**< \brief [30:30] Spike Detection Enable (rw) */
    unsigned int SPD:1;                     /**< \brief [31:31] Spike Detection Flag (rwh) */
} Ifx_QSPI_STATUS1_Bits;

/** \brief  Status Register */
typedef struct _Ifx_QSPI_STATUS_Bits
{
    unsigned int ERRORFLAGS:9;              /**< \brief [8:0] Sticky Flags Signalling Errors (rwh) */
    unsigned int TXF:1;                     /**< \brief [9:9] Transmit Interrupt Request Flag (rwh) */
    unsigned int RXF:1;                     /**< \brief [10:10] Receive Interrupt Request Flag (rwh) */
    unsigned int PT1F:1;                    /**< \brief [11:11] Phase Transition 1 Flag (rwh) */
    unsigned int PT2F:1;                    /**< \brief [12:12] Phase Transition 2 Flag (rwh) */
    unsigned int reserved_13:2;             /**< \brief \internal Reserved */
    unsigned int USRF:1;                    /**< \brief [15:15] User Interrupt Request Flag (rwh) */
    unsigned int TXFIFOLEVEL:3;             /**< \brief [18:16] TXFIFO Filling Level (rh) */
    unsigned int RXFIFOLEVEL:3;             /**< \brief [21:19] RXFIFO Filling Level (rh) */
    unsigned int SLAVESEL:4;                /**< \brief [25:22] Currently Active Slave Select Flag (rh) */
    unsigned int RPV:1;                     /**< \brief [26:26] Received Parity Value (rh) */
    unsigned int TPV:1;                     /**< \brief [27:27] Transmitted Parity Value (rh) */
    unsigned int PHASE:4;                   /**< \brief [31:28] Flags the ongoing phase (rh) */
} Ifx_QSPI_STATUS_Bits;

/** \brief  Extra Large Data Configuration Register */
typedef struct _Ifx_QSPI_XXLCON_Bits
{
    unsigned int XDL:16;                    /**< \brief [15:0] Extended Data Length (rw) */
    unsigned int BYTECOUNT:16;              /**< \brief [31:16] Extended Data Length (r) */
} Ifx_QSPI_XXLCON_Bits;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Qspi_union
 * \{  */

/** \brief  Access Enable Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_QSPI_ACCEN0_Bits B;                 /**< \brief Bitfield access */
} Ifx_QSPI_ACCEN0;

/** \brief  Access Enable Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_QSPI_ACCEN1_Bits B;                 /**< \brief Bitfield access */
} Ifx_QSPI_ACCEN1;

/** \brief  Basic Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_QSPI_BACON_Bits B;                  /**< \brief Bitfield access */
} Ifx_QSPI_BACON;

/** \brief  BACON_ENTRY Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_QSPI_BACONENTRY_Bits B;             /**< \brief Bitfield access */
} Ifx_QSPI_BACONENTRY;

/** \brief  Capture Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_QSPI_CAPCON_Bits B;                 /**< \brief Bitfield access */
} Ifx_QSPI_CAPCON;

/** \brief  Clock Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_QSPI_CLC_Bits B;                    /**< \brief Bitfield access */
} Ifx_QSPI_CLC;

/** \brief  DATA_ENTRY Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_QSPI_DATAENTRY_Bits B;              /**< \brief Bitfield access */
} Ifx_QSPI_DATAENTRY;

/** \brief  Configuration Extension */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_QSPI_ECON_Bits B;                   /**< \brief Bitfield access */
} Ifx_QSPI_ECON;

/** \brief  Flags Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_QSPI_FLAGSCLEAR_Bits B;             /**< \brief Bitfield access */
} Ifx_QSPI_FLAGSCLEAR;

/** \brief  Global Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_QSPI_GLOBALCON_Bits B;              /**< \brief Bitfield access */
} Ifx_QSPI_GLOBALCON;

/** \brief  Global Configuration Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_QSPI_GLOBALCON1_Bits B;             /**< \brief Bitfield access */
} Ifx_QSPI_GLOBALCON1;

/** \brief  Module Identification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_QSPI_ID_Bits B;                     /**< \brief Bitfield access */
} Ifx_QSPI_ID;

/** \brief  Kernel Reset Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_QSPI_KRST0_Bits B;                  /**< \brief Bitfield access */
} Ifx_QSPI_KRST0;

/** \brief  Kernel Reset Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_QSPI_KRST1_Bits B;                  /**< \brief Bitfield access */
} Ifx_QSPI_KRST1;

/** \brief  Kernel Reset Status Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_QSPI_KRSTCLR_Bits B;                /**< \brief Bitfield access */
} Ifx_QSPI_KRSTCLR;

/** \brief  MIX_ENTRY Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_QSPI_MIXENTRY_Bits B;               /**< \brief Bitfield access */
} Ifx_QSPI_MIXENTRY;

/** \brief  OCDS Control and Status */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_QSPI_OCS_Bits B;                    /**< \brief Bitfield access */
} Ifx_QSPI_OCS;

/** \brief  Port Input Select Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_QSPI_PISEL_Bits B;                  /**< \brief Bitfield access */
} Ifx_QSPI_PISEL;

/** \brief  RX_EXIT Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_QSPI_RXEXIT_Bits B;                 /**< \brief Bitfield access */
} Ifx_QSPI_RXEXIT;

/** \brief  RX_EXIT Debug Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_QSPI_RXEXITD_Bits B;                /**< \brief Bitfield access */
} Ifx_QSPI_RXEXITD;

/** \brief  Slave Select Output Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_QSPI_SSOC_Bits B;                   /**< \brief Bitfield access */
} Ifx_QSPI_SSOC;

/** \brief  Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_QSPI_STATUS_Bits B;                 /**< \brief Bitfield access */
} Ifx_QSPI_STATUS;

/** \brief  Status Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_QSPI_STATUS1_Bits B;                /**< \brief Bitfield access */
} Ifx_QSPI_STATUS1;

/** \brief  Extra Large Data Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_QSPI_XXLCON_Bits B;                 /**< \brief Bitfield access */
} Ifx_QSPI_XXLCON;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Qspi_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \brief  QSPI object */
typedef volatile struct _Ifx_QSPI
{
    Ifx_QSPI_CLC CLC;                       /**< \brief 0, Clock Control Register */
    Ifx_QSPI_PISEL PISEL;                   /**< \brief 4, Port Input Select Register */
    Ifx_QSPI_ID ID;                         /**< \brief 8, Module Identification Register */
    unsigned char reserved_C[4];            /**< \brief C, \internal Reserved */
    Ifx_QSPI_GLOBALCON GLOBALCON;           /**< \brief 10, Global Configuration Register */
    Ifx_QSPI_GLOBALCON1 GLOBALCON1;         /**< \brief 14, Global Configuration Register 1 */
    Ifx_QSPI_BACON BACON;                   /**< \brief 18, Basic Configuration Register */
    unsigned char reserved_1C[4];           /**< \brief 1C, \internal Reserved */
    Ifx_QSPI_ECON ECON[8];                  /**< \brief 20, Configuration Extension */
    Ifx_QSPI_STATUS STATUS;                 /**< \brief 40, Status Register */
    Ifx_QSPI_STATUS1 STATUS1;               /**< \brief 44, Status Register 1 */
    Ifx_QSPI_SSOC SSOC;                     /**< \brief 48, Slave Select Output Control Register */
    unsigned char reserved_4C[8];           /**< \brief 4C, \internal Reserved */
    Ifx_QSPI_FLAGSCLEAR FLAGSCLEAR;         /**< \brief 54, Flags Clear Register */
    Ifx_QSPI_XXLCON XXLCON;                 /**< \brief 58, Extra Large Data Configuration Register */
    Ifx_QSPI_MIXENTRY MIXENTRY;             /**< \brief 5C, MIX_ENTRY Register */
    Ifx_QSPI_BACONENTRY BACONENTRY;         /**< \brief 60, BACON_ENTRY Register */
    Ifx_QSPI_DATAENTRY DATAENTRY[8];        /**< \brief 64, DATA_ENTRY Register */
    unsigned char reserved_84[12];          /**< \brief 84, \internal Reserved */
    Ifx_QSPI_RXEXIT RXEXIT;                 /**< \brief 90, RX_EXIT Register */
    Ifx_QSPI_RXEXITD RXEXITD;               /**< \brief 94, RX_EXIT Debug Register */
    unsigned char reserved_98[8];           /**< \brief 98, \internal Reserved */
    Ifx_QSPI_CAPCON CAPCON;                 /**< \brief A0, Capture Control Register */
    unsigned char reserved_A4[68];          /**< \brief A4, \internal Reserved */
    Ifx_QSPI_OCS OCS;                       /**< \brief E8, OCDS Control and Status */
    Ifx_QSPI_KRSTCLR KRSTCLR;               /**< \brief EC, Kernel Reset Status Clear Register */
    Ifx_QSPI_KRST1 KRST1;                   /**< \brief F0, Kernel Reset Register 1 */
    Ifx_QSPI_KRST0 KRST0;                   /**< \brief F4, Kernel Reset Register 0 */
    Ifx_QSPI_ACCEN1 ACCEN1;                 /**< \brief F8, Access Enable Register 1 */
    Ifx_QSPI_ACCEN0 ACCEN0;                 /**< \brief FC, Access Enable Register 0 */
} Ifx_QSPI;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXQSPI_REGDEF_H */
