/**
 * \file IfxXbar_regdef.h
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
 * \defgroup IfxLld_Xbar Xbar
 * \ingroup IfxLld
 * 
 * \defgroup IfxLld_Xbar_Bitfields Bitfields
 * \ingroup IfxLld_Xbar
 * 
 * \defgroup IfxLld_Xbar_union Union
 * \ingroup IfxLld_Xbar
 * 
 * \defgroup IfxLld_Xbar_struct Struct
 * \ingroup IfxLld_Xbar
 * 
 */
#ifndef IFXXBAR_REGDEF_H
#define IFXXBAR_REGDEF_H 1
/******************************************************************************/
#include "Ifx_TypesReg.h"
/******************************************************************************/
/** \addtogroup IfxLld_Xbar_Bitfields
 * \{  */

/** \brief  Access Enable Register 0 */
typedef struct _Ifx_XBAR_ACCEN0_Bits
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
} Ifx_XBAR_ACCEN0_Bits;

/** \brief  Access Enable Register 1 */
typedef struct _Ifx_XBAR_ACCEN1_Bits
{
    unsigned int reserved_0:32;             /**< \brief \internal Reserved */
} Ifx_XBAR_ACCEN1_Bits;

/** \brief  Arbiter Control Register */
typedef struct _Ifx_XBAR_ARBCON_Bits
{
    unsigned int PRERREN:1;                 /**< \brief [0:0] SRI Protocol Error Enable (rw) */
    unsigned int SCERREN:1;                 /**< \brief [1:1] SRI Starvation Error Enable (rw) */
    unsigned int SETPRINT:1;                /**< \brief [2:2] Set SRI Protocol Interrupt (rwh) */
    unsigned int SETSCINT:1;                /**< \brief [3:3] Set SRI Starvation Interrupt (rwh) */
    unsigned int INTACK:1;                  /**< \brief [4:4] Interrupt Acknowledge (rwh) */
    unsigned int reserved_5:15;             /**< \brief \internal Reserved */
    unsigned int SPC:12;                    /**< \brief [31:20] Starvation Protection Counter Reload Value (rw) */
} Ifx_XBAR_ARBCON_Bits;

/** \brief  Debug Address Register */
typedef struct _Ifx_XBAR_ARBITER0_DBADD_Bits
{
    unsigned int reserved_0:27;             /**< \brief \internal Reserved */
    unsigned int ADDRESS:1;                 /**< \brief [27:27] Debug Address Boundary (rw) */
    unsigned int reserved_28:4;             /**< \brief \internal Reserved */
} Ifx_XBAR_ARBITER0_DBADD_Bits;

/** \brief  Debug Mask Address Register */
typedef struct _Ifx_XBAR_ARBITER0_DBMADD_Bits
{
    unsigned int reserved_0:2;              /**< \brief \internal Reserved */
    unsigned int ADDRESS:19;                /**< \brief [20:2] Debug Address Boundary (rw) */
    unsigned int reserved_21:11;            /**< \brief \internal Reserved */
} Ifx_XBAR_ARBITER0_DBMADD_Bits;

/** \brief  Debug Address Register */
typedef struct _Ifx_XBAR_ARBITER1_DBADD_Bits
{
    unsigned int reserved_0:31;             /**< \brief \internal Reserved */
    unsigned int ADDRESS:1;                 /**< \brief [31:31] Debug Address Boundary (rw) */
} Ifx_XBAR_ARBITER1_DBADD_Bits;

/** \brief  Debug Mask Address Register */
typedef struct _Ifx_XBAR_ARBITER1_DBMADD_Bits
{
    unsigned int reserved_0:31;             /**< \brief \internal Reserved */
    unsigned int ADDRESS:1;                 /**< \brief [31:31] Debug Address Boundary (rw) */
} Ifx_XBAR_ARBITER1_DBMADD_Bits;

/** \brief  Debug Address Register */
typedef struct _Ifx_XBAR_ARBITER4_DBADD_Bits
{
    unsigned int reserved_0:2;              /**< \brief \internal Reserved */
    unsigned int ADDRESS:29;                /**< \brief [30:2] Debug Address Boundary (rw) */
    unsigned int reserved_31:1;             /**< \brief \internal Reserved */
} Ifx_XBAR_ARBITER4_DBADD_Bits;

/** \brief  Debug Mask Address Register */
typedef struct _Ifx_XBAR_ARBITER4_DBMADD_Bits
{
    unsigned int reserved_0:2;              /**< \brief \internal Reserved */
    unsigned int ADDRESS:29;                /**< \brief [30:2] Debug Address Boundary (rw) */
    unsigned int reserved_31:1;             /**< \brief \internal Reserved */
} Ifx_XBAR_ARBITER4_DBMADD_Bits;

/** \brief  Debug Address Register */
typedef struct _Ifx_XBAR_ARBITER6_DBADD_Bits
{
    unsigned int reserved_0:28;             /**< \brief \internal Reserved */
    unsigned int ADDRESS:3;                 /**< \brief [30:28] Debug Address Boundary (rw) */
    unsigned int reserved_31:1;             /**< \brief \internal Reserved */
} Ifx_XBAR_ARBITER6_DBADD_Bits;

/** \brief  Debug Mask Address Register */
typedef struct _Ifx_XBAR_ARBITER6_DBMADD_Bits
{
    unsigned int reserved_0:28;             /**< \brief \internal Reserved */
    unsigned int ADDRESS:3;                 /**< \brief [30:28] Debug Address Boundary (rw) */
    unsigned int reserved_31:1;             /**< \brief \internal Reserved */
} Ifx_XBAR_ARBITER6_DBMADD_Bits;

/** \brief  Debug Address Register */
typedef struct _Ifx_XBAR_ARBITER7_DBADD_Bits
{
    unsigned int reserved_0:29;             /**< \brief \internal Reserved */
    unsigned int ADDRESS:1;                 /**< \brief [29:29] Debug Address Boundary (rw) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_XBAR_ARBITER7_DBADD_Bits;

/** \brief  Debug Mask Address Register */
typedef struct _Ifx_XBAR_ARBITER7_DBMADD_Bits
{
    unsigned int reserved_0:29;             /**< \brief \internal Reserved */
    unsigned int ADDRESS:1;                 /**< \brief [29:29] Debug Address Boundary (rw) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_XBAR_ARBITER7_DBMADD_Bits;

/** \brief  Debug Address Register */
typedef struct _Ifx_XBAR_ARBITER8_DBADD_Bits
{
    unsigned int reserved_0:29;             /**< \brief \internal Reserved */
    unsigned int ADDRESS:1;                 /**< \brief [29:29] Debug Address Boundary (rw) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_XBAR_ARBITER8_DBADD_Bits;

/** \brief  Debug Mask Address Register */
typedef struct _Ifx_XBAR_ARBITER8_DBMADD_Bits
{
    unsigned int reserved_0:29;             /**< \brief \internal Reserved */
    unsigned int ADDRESS:1;                 /**< \brief [29:29] Debug Address Boundary (rw) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_XBAR_ARBITER8_DBMADD_Bits;

/** \brief  Debug Address Register */
typedef struct _Ifx_XBAR_ARBITERD_DBADD_Bits
{
    unsigned int reserved_0:2;              /**< \brief \internal Reserved */
    unsigned int ADDRESS:30;                /**< \brief [31:2] Debug Address Boundary (rw) */
} Ifx_XBAR_ARBITERD_DBADD_Bits;

/** \brief  Debug Mask Address Register */
typedef struct _Ifx_XBAR_ARBITERD_DBMADD_Bits
{
    unsigned int ADDRESS:32;                /**< \brief [31:0] Debug Address Boundary (rw) */
} Ifx_XBAR_ARBITERD_DBMADD_Bits;

/** \brief  Debug Control Register */
typedef struct _Ifx_XBAR_DBCON_Bits
{
    unsigned int DBEN:1;                    /**< \brief [0:0] Status of OCDS Enable Signal (r) */
    unsigned int DBSAT:1;                   /**< \brief [1:1] Debug (OCDS) Trigger Status (rh) */
    unsigned int REARM:1;                   /**< \brief [2:2] Rearm Debug (OCDS) Trigger (w) */
    unsigned int SETDBEVT:1;                /**< \brief [3:3] Set Debug Event (w) */
    unsigned int reserved_4:12;             /**< \brief \internal Reserved */
    unsigned int RDEN:1;                    /**< \brief [16:16] Read Trigger Enable (rw) */
    unsigned int WREN:1;                    /**< \brief [17:17] Write Trigger Enable (rw) */
    unsigned int SVMEN:1;                   /**< \brief [18:18] SVM Trigger Enable (rw) */
    unsigned int ADDEN:1;                   /**< \brief [19:19] Address Trigger Enable (rw) */
    unsigned int ERREN:1;                   /**< \brief [20:20] Error Trigger Enable (rw) */
    unsigned int reserved_21:2;             /**< \brief \internal Reserved */
    unsigned int MASEN:1;                   /**< \brief [23:23] Master Trigger Enable (rw) */
    unsigned int MASTER:6;                  /**< \brief [29:24] Master TAG ID Trigger Selector (rw) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_XBAR_DBCON_Bits;

/** \brief  Debug Trigger Event Status Register */
typedef struct _Ifx_XBAR_DBSAT_Bits
{
    unsigned int SCI0:1;                    /**< \brief [0:0] SCI Debug Trigger Event Status (rwh) */
    unsigned int SCI1:1;                    /**< \brief [1:1] SCI Debug Trigger Event Status (rwh) */
    unsigned int reserved_2:2;              /**< \brief \internal Reserved */
    unsigned int SCI4:1;                    /**< \brief [4:4] SCI Debug Trigger Event Status (rwh) */
    unsigned int reserved_5:1;              /**< \brief \internal Reserved */
    unsigned int SCI6:1;                    /**< \brief [6:6] SCI Debug Trigger Event Status (rwh) */
    unsigned int SCI7:1;                    /**< \brief [7:7] SCI Debug Trigger Event Status (rwh) */
    unsigned int SCI8:1;                    /**< \brief [8:8] SCI Debug Trigger Event Status (rwh) */
    unsigned int reserved_9:6;              /**< \brief \internal Reserved */
    unsigned int SCID:1;                    /**< \brief [15:15] Default Slave Debug Trigger Event Status (rwh) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_XBAR_DBSAT_Bits;

/** \brief  Error/Debug Capture Register */
typedef struct _Ifx_XBAR_ERR_Bits
{
    unsigned int RD:1;                      /**< \brief [0:0] Read Indication Status (rh) */
    unsigned int WR:1;                      /**< \brief [1:1] Write Indication Status (rh) */
    unsigned int SVM:1;                     /**< \brief [2:2] Supervisor Mode Indication Status (rh) */
    unsigned int reserved_3:1;              /**< \brief \internal Reserved */
    unsigned int OPC:4;                     /**< \brief [7:4] Operation Code (rh) */
    unsigned int TR_ID:8;                   /**< \brief [15:8] Transaction ID (rh) */
    unsigned int ADDR_ECC:8;                /**< \brief [23:16] SRI Address Phase ECC (rh) */
    unsigned int MCI_SBS:8;                 /**< \brief [31:24] MCI Sideband Signals [7:0] (rh) */
} Ifx_XBAR_ERR_Bits;

/** \brief  Error/Debug Address Capture Register */
typedef struct _Ifx_XBAR_ERRADDR_Bits
{
    unsigned int ADDR:32;                   /**< \brief [31:0] Transaction Address (rh) */
} Ifx_XBAR_ERRADDR_Bits;

/** \brief  External Control Register D */
typedef struct _Ifx_XBAR_EXTCOND_Bits
{
    unsigned int reserved_0:3;              /**< \brief \internal Reserved */
    unsigned int WFWD:1;                    /**< \brief [3:3] Wait for FPI Write Data (rw) */
    unsigned int reserved_4:2;              /**< \brief \internal Reserved */
    unsigned int FREQDISF:1;                /**< \brief [6:6] Disable Fast Request Feature for FPI to SRI Transactions (rw) */
    unsigned int reserved_7:2;              /**< \brief \internal Reserved */
    unsigned int NODELTR:1;                 /**< \brief [9:9] Control Signal for deferred transactions (rw) */
    unsigned int NORMW:1;                   /**< \brief [10:10] Control Signal for deferred transactions (rw) */
    unsigned int reserved_11:2;             /**< \brief \internal Reserved */
    unsigned int MAX_WS:7;                  /**< \brief [19:13] FPI-Bus Wait State Retry Ratio (rw) */
    unsigned int reserved_20:12;            /**< \brief \internal Reserved */
} Ifx_XBAR_EXTCOND_Bits;

/** \brief  Module Identification Register */
typedef struct _Ifx_XBAR_ID_Bits
{
    unsigned int MODREV:8;                  /**< \brief [7:0] Module Revision Number (r) */
    unsigned int MODTYPE:8;                 /**< \brief [15:8] Module Type (r) */
    unsigned int MODNUMBER:16;              /**< \brief [31:16] Module Number Value (r) */
} Ifx_XBAR_ID_Bits;

/** \brief  Transaction ID Interrupt Enable Register */
typedef struct _Ifx_XBAR_IDINTEN_Bits
{
    unsigned int ENSCI0:1;                  /**< \brief [0:0] Enable ID Error from SCI0 (rw) */
    unsigned int ENSCI1:1;                  /**< \brief [1:1] Enable ID Error from SCI1 (rw) */
    unsigned int reserved_2:2;              /**< \brief \internal Reserved */
    unsigned int ENSCI4:1;                  /**< \brief [4:4] Enable ID Error from SCI4 (rw) */
    unsigned int reserved_5:1;              /**< \brief \internal Reserved */
    unsigned int ENSCI6:1;                  /**< \brief [6:6] Enable ID Error from SCI6 (rw) */
    unsigned int ENSCI7:1;                  /**< \brief [7:7] Enable ID Error from SCI7 (rw) */
    unsigned int ENSCI8:1;                  /**< \brief [8:8] Enable ID Error from SCI8 (rw) */
    unsigned int reserved_9:6;              /**< \brief \internal Reserved */
    unsigned int ENSCID:1;                  /**< \brief [15:15] Enable ID Error from Default Slave (rw) */
    unsigned int ENMCI0:1;                  /**< \brief [16:16] Enable ID Error from MCI0 (rw) */
    unsigned int reserved_17:3;             /**< \brief \internal Reserved */
    unsigned int ENMCI4:1;                  /**< \brief [20:20] Enable ID Error from MCI4 (rw) */
    unsigned int ENMCI5:1;                  /**< \brief [21:21] Enable ID Error from MCI5 (rw) */
    unsigned int reserved_22:2;             /**< \brief \internal Reserved */
    unsigned int ENMCI8:1;                  /**< \brief [24:24] Enable ID Error from MCI8 (rw) */
    unsigned int ENMCI9:1;                  /**< \brief [25:25] Enable ID Error from MCI9 (rw) */
    unsigned int reserved_26:2;             /**< \brief \internal Reserved */
    unsigned int ENMCI12:1;                 /**< \brief [28:28] Enable ID Error from MCI12 (rw) */
    unsigned int ENMCI13:1;                 /**< \brief [29:29] Enable ID Error from MCI13 (rw) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_XBAR_IDINTEN_Bits;

/** \brief  Transaction ID Interrupt Status Register */
typedef struct _Ifx_XBAR_IDINTSAT_Bits
{
    unsigned int IDSCI0:1;                  /**< \brief [0:0] Transaction ID Error from SCI0 Status (rwh) */
    unsigned int IDSCI1:1;                  /**< \brief [1:1] Transaction ID Error from SCI1 Status (rwh) */
    unsigned int reserved_2:2;              /**< \brief \internal Reserved */
    unsigned int IDCSCI4:1;                 /**< \brief [4:4] Transaction ID Error from SCI4 Status (rwh) */
    unsigned int reserved_5:1;              /**< \brief \internal Reserved */
    unsigned int IDSCI6:1;                  /**< \brief [6:6] Transaction ID Error from SCI6 Status (rwh) */
    unsigned int IDSCI7:1;                  /**< \brief [7:7] Transaction ID Error from SCI7 Status (rwh) */
    unsigned int IDSCI8:1;                  /**< \brief [8:8] Transaction ID Error from SCI8 Status (rwh) */
    unsigned int reserved_9:6;              /**< \brief \internal Reserved */
    unsigned int IDSCID:1;                  /**< \brief [15:15] Transaction ID Error from Default Slave Status (rwh) */
    unsigned int IDMCI0:1;                  /**< \brief [16:16] Transaction ID Error from MCI0 Status (rwh) */
    unsigned int reserved_17:3;             /**< \brief \internal Reserved */
    unsigned int IDMCI4:1;                  /**< \brief [20:20] Transaction ID Error from MCI4 Status (rwh) */
    unsigned int IDMCI5:1;                  /**< \brief [21:21] Transaction ID Error from MCI5 Status (rwh) */
    unsigned int reserved_22:2;             /**< \brief \internal Reserved */
    unsigned int IDMCI8:1;                  /**< \brief [24:24] Transaction ID Error from MCI8 Status (rwh) */
    unsigned int IDMCI9:1;                  /**< \brief [25:25] Transaction ID Error from MCI9 Status (rwh) */
    unsigned int reserved_26:2;             /**< \brief \internal Reserved */
    unsigned int IDMCI12:1;                 /**< \brief [28:28] Transaction ID Error from MCI12 Status (rwh) */
    unsigned int IDMCI13:1;                 /**< \brief [29:29] Transaction ID Error from MCI13 Status (rwh) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_XBAR_IDINTSAT_Bits;

/** \brief  Arbiter Interrupt Status Register */
typedef struct _Ifx_XBAR_INTSAT_Bits
{
    unsigned int SCSCI0:1;                  /**< \brief [0:0] Starvation Error from SCI0 Status (rwh) */
    unsigned int SCSCI1:1;                  /**< \brief [1:1] Starvation Error from SCI1 Status (rwh) */
    unsigned int reserved_2:2;              /**< \brief \internal Reserved */
    unsigned int SCSCI4:1;                  /**< \brief [4:4] Starvation Error from SCI4 Status (rwh) */
    unsigned int reserved_5:1;              /**< \brief \internal Reserved */
    unsigned int SCSCI6:1;                  /**< \brief [6:6] Starvation Error from SCI6 Status (rwh) */
    unsigned int SCSCI7:1;                  /**< \brief [7:7] Starvation Error from SCI7 Status (rwh) */
    unsigned int SCSCI8:1;                  /**< \brief [8:8] Starvation Error from SCI8 Status (rwh) */
    unsigned int reserved_9:6;              /**< \brief \internal Reserved */
    unsigned int SCSCID:1;                  /**< \brief [15:15] Starvation Error from Default Slave Status (rwh) */
    unsigned int PRSCI0:1;                  /**< \brief [16:16] Protocol Error from SCI0 Status (rwh) */
    unsigned int PRSCI1:1;                  /**< \brief [17:17] Protocol Error from SCI1 Status (rwh) */
    unsigned int reserved_18:2;             /**< \brief \internal Reserved */
    unsigned int PRSCI4:1;                  /**< \brief [20:20] Protocol Error from SCI4 Status (rwh) */
    unsigned int reserved_21:1;             /**< \brief \internal Reserved */
    unsigned int PRSCI6:1;                  /**< \brief [22:22] Protocol Error from SCI6 Status (rwh) */
    unsigned int PRSCI7:1;                  /**< \brief [23:23] Protocol Error from SCI7 Status (rwh) */
    unsigned int PRSCI8:1;                  /**< \brief [24:24] Protocol Error from SCI8 Status (rwh) */
    unsigned int reserved_25:6;             /**< \brief \internal Reserved */
    unsigned int PRSCID:1;                  /**< \brief [31:31] Protocol Error from Default Slave Status (rwh) */
} Ifx_XBAR_INTSAT_Bits;

/** \brief  Arbiter Priority Register */
typedef struct _Ifx_XBAR_PRIOH_Bits
{
    unsigned int MASTER8:3;                 /**< \brief [2:0] Master 8 Priority (rw) */
    unsigned int reserved_3:1;              /**< \brief \internal Reserved */
    unsigned int MASTER9:3;                 /**< \brief [6:4] Master 9 Priority (rw) */
    unsigned int reserved_7:9;              /**< \brief \internal Reserved */
    unsigned int MASTER12:3;                /**< \brief [18:16] Master 12 Priority (rw) */
    unsigned int reserved_19:1;             /**< \brief \internal Reserved */
    unsigned int MASTER13:3;                /**< \brief [22:20] Master 13 Priority (rw) */
    unsigned int reserved_23:9;             /**< \brief \internal Reserved */
} Ifx_XBAR_PRIOH_Bits;

/** \brief  Arbiter Priority Register */
typedef struct _Ifx_XBAR_PRIOL_Bits
{
    unsigned int MASTER0:3;                 /**< \brief [2:0] Master 0 Priority (rw) */
    unsigned int reserved_3:13;             /**< \brief \internal Reserved */
    unsigned int MASTER4:3;                 /**< \brief [18:16] Master 4 Priority (rw) */
    unsigned int reserved_19:1;             /**< \brief \internal Reserved */
    unsigned int MASTER5:3;                 /**< \brief [22:20] Master 5 Priority (rw) */
    unsigned int reserved_23:9;             /**< \brief \internal Reserved */
} Ifx_XBAR_PRIOL_Bits;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Xbar_union
 * \{  */

/** \brief  Access Enable Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_XBAR_ACCEN0_Bits B;                 /**< \brief Bitfield access */
} Ifx_XBAR_ACCEN0;

/** \brief  Access Enable Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_XBAR_ACCEN1_Bits B;                 /**< \brief Bitfield access */
} Ifx_XBAR_ACCEN1;

/** \brief  Arbiter Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_XBAR_ARBCON_Bits B;                 /**< \brief Bitfield access */
} Ifx_XBAR_ARBCON;

/** \brief  Debug Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_XBAR_ARBITER0_DBADD_Bits B;         /**< \brief Bitfield access */
} Ifx_XBAR_ARBITER0_DBADD;

/** \brief  Debug Mask Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_XBAR_ARBITER0_DBMADD_Bits B;        /**< \brief Bitfield access */
} Ifx_XBAR_ARBITER0_DBMADD;

/** \brief  Debug Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_XBAR_ARBITER1_DBADD_Bits B;         /**< \brief Bitfield access */
} Ifx_XBAR_ARBITER1_DBADD;

/** \brief  Debug Mask Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_XBAR_ARBITER1_DBMADD_Bits B;        /**< \brief Bitfield access */
} Ifx_XBAR_ARBITER1_DBMADD;

/** \brief  Debug Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_XBAR_ARBITER4_DBADD_Bits B;         /**< \brief Bitfield access */
} Ifx_XBAR_ARBITER4_DBADD;

/** \brief  Debug Mask Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_XBAR_ARBITER4_DBMADD_Bits B;        /**< \brief Bitfield access */
} Ifx_XBAR_ARBITER4_DBMADD;

/** \brief  Debug Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_XBAR_ARBITER6_DBADD_Bits B;         /**< \brief Bitfield access */
} Ifx_XBAR_ARBITER6_DBADD;

/** \brief  Debug Mask Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_XBAR_ARBITER6_DBMADD_Bits B;        /**< \brief Bitfield access */
} Ifx_XBAR_ARBITER6_DBMADD;

/** \brief  Debug Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_XBAR_ARBITER7_DBADD_Bits B;         /**< \brief Bitfield access */
} Ifx_XBAR_ARBITER7_DBADD;

/** \brief  Debug Mask Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_XBAR_ARBITER7_DBMADD_Bits B;        /**< \brief Bitfield access */
} Ifx_XBAR_ARBITER7_DBMADD;

/** \brief  Debug Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_XBAR_ARBITER8_DBADD_Bits B;         /**< \brief Bitfield access */
} Ifx_XBAR_ARBITER8_DBADD;

/** \brief  Debug Mask Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_XBAR_ARBITER8_DBMADD_Bits B;        /**< \brief Bitfield access */
} Ifx_XBAR_ARBITER8_DBMADD;

/** \brief  Debug Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_XBAR_ARBITERD_DBADD_Bits B;         /**< \brief Bitfield access */
} Ifx_XBAR_ARBITERD_DBADD;

/** \brief  Debug Mask Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_XBAR_ARBITERD_DBMADD_Bits B;        /**< \brief Bitfield access */
} Ifx_XBAR_ARBITERD_DBMADD;

/** \brief  Debug Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_XBAR_DBCON_Bits B;                  /**< \brief Bitfield access */
} Ifx_XBAR_DBCON;

/** \brief  Debug Trigger Event Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_XBAR_DBSAT_Bits B;                  /**< \brief Bitfield access */
} Ifx_XBAR_DBSAT;

/** \brief  Error/Debug Capture Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_XBAR_ERR_Bits B;                    /**< \brief Bitfield access */
} Ifx_XBAR_ERR;

/** \brief  Error/Debug Address Capture Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_XBAR_ERRADDR_Bits B;                /**< \brief Bitfield access */
} Ifx_XBAR_ERRADDR;

/** \brief  External Control Register D */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_XBAR_EXTCOND_Bits B;                /**< \brief Bitfield access */
} Ifx_XBAR_EXTCOND;

/** \brief  Module Identification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_XBAR_ID_Bits B;                     /**< \brief Bitfield access */
} Ifx_XBAR_ID;

/** \brief  Transaction ID Interrupt Enable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_XBAR_IDINTEN_Bits B;                /**< \brief Bitfield access */
} Ifx_XBAR_IDINTEN;

/** \brief  Transaction ID Interrupt Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_XBAR_IDINTSAT_Bits B;               /**< \brief Bitfield access */
} Ifx_XBAR_IDINTSAT;

/** \brief  Arbiter Interrupt Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_XBAR_INTSAT_Bits B;                 /**< \brief Bitfield access */
} Ifx_XBAR_INTSAT;

/** \brief  Arbiter Priority Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_XBAR_PRIOH_Bits B;                  /**< \brief Bitfield access */
} Ifx_XBAR_PRIOH;

/** \brief  Arbiter Priority Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_XBAR_PRIOL_Bits B;                  /**< \brief Bitfield access */
} Ifx_XBAR_PRIOL;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Xbar_struct
 * \{  */
/******************************************************************************/
/** \name Object L1
 * \{  */

/** \brief  Arbiter objects */
typedef volatile struct _Ifx_XBAR_ARBITER0
{
    Ifx_XBAR_ARBCON ARBCON;                 /**< \brief 0, Arbiter Control Register */
    Ifx_XBAR_PRIOH PRIOH;                   /**< \brief 4, Arbiter Priority Register */
    Ifx_XBAR_PRIOL PRIOL;                   /**< \brief 8, Arbiter Priority Register */
    Ifx_XBAR_ERRADDR ERRADDR;               /**< \brief C, Error/Debug Address Capture Register */
    Ifx_XBAR_ERR ERR;                       /**< \brief 10, Error/Debug Capture Register */
    Ifx_XBAR_DBCON DBCON;                   /**< \brief 14, Debug Control Register */
    Ifx_XBAR_ARBITER0_DBADD DBADD;          /**< \brief 18, Debug Address Register */
    Ifx_XBAR_ARBITER0_DBMADD DBMADD;        /**< \brief 1C, Debug Mask Address Register */
} Ifx_XBAR_ARBITER0;

/** \brief  Arbiter objects */
typedef volatile struct _Ifx_XBAR_ARBITER1
{
    Ifx_XBAR_ARBCON ARBCON;                 /**< \brief 0, Arbiter Control Register */
    Ifx_XBAR_PRIOH PRIOH;                   /**< \brief 4, Arbiter Priority Register */
    Ifx_XBAR_PRIOL PRIOL;                   /**< \brief 8, Arbiter Priority Register */
    Ifx_XBAR_ERRADDR ERRADDR;               /**< \brief C, Error/Debug Address Capture Register */
    Ifx_XBAR_ERR ERR;                       /**< \brief 10, Error/Debug Capture Register */
    Ifx_XBAR_DBCON DBCON;                   /**< \brief 14, Debug Control Register */
    Ifx_XBAR_ARBITER1_DBADD DBADD;          /**< \brief 18, Debug Address Register */
    Ifx_XBAR_ARBITER1_DBMADD DBMADD;        /**< \brief 1C, Debug Mask Address Register */
} Ifx_XBAR_ARBITER1;

/** \brief  Arbiter objects */
typedef volatile struct _Ifx_XBAR_ARBITER4
{
    Ifx_XBAR_ARBCON ARBCON;                 /**< \brief 0, Arbiter Control Register */
    Ifx_XBAR_PRIOH PRIOH;                   /**< \brief 4, Arbiter Priority Register */
    Ifx_XBAR_PRIOL PRIOL;                   /**< \brief 8, Arbiter Priority Register */
    Ifx_XBAR_ERRADDR ERRADDR;               /**< \brief C, Error/Debug Address Capture Register */
    Ifx_XBAR_ERR ERR;                       /**< \brief 10, Error/Debug Capture Register */
    Ifx_XBAR_DBCON DBCON;                   /**< \brief 14, Debug Control Register */
    Ifx_XBAR_ARBITER4_DBADD DBADD;          /**< \brief 18, Debug Address Register */
    Ifx_XBAR_ARBITER4_DBMADD DBMADD;        /**< \brief 1C, Debug Mask Address Register */
} Ifx_XBAR_ARBITER4;

/** \brief  Arbiter objects */
typedef volatile struct _Ifx_XBAR_ARBITER6
{
    Ifx_XBAR_ARBCON ARBCON;                 /**< \brief 0, Arbiter Control Register */
    Ifx_XBAR_PRIOH PRIOH;                   /**< \brief 4, Arbiter Priority Register */
    Ifx_XBAR_PRIOL PRIOL;                   /**< \brief 8, Arbiter Priority Register */
    Ifx_XBAR_ERRADDR ERRADDR;               /**< \brief C, Error/Debug Address Capture Register */
    Ifx_XBAR_ERR ERR;                       /**< \brief 10, Error/Debug Capture Register */
    Ifx_XBAR_DBCON DBCON;                   /**< \brief 14, Debug Control Register */
    Ifx_XBAR_ARBITER6_DBADD DBADD;          /**< \brief 18, Debug Address Register */
    Ifx_XBAR_ARBITER6_DBMADD DBMADD;        /**< \brief 1C, Debug Mask Address Register */
} Ifx_XBAR_ARBITER6;

/** \brief  Arbiter objects */
typedef volatile struct _Ifx_XBAR_ARBITER7
{
    Ifx_XBAR_ARBCON ARBCON;                 /**< \brief 0, Arbiter Control Register */
    Ifx_XBAR_PRIOH PRIOH;                   /**< \brief 4, Arbiter Priority Register */
    Ifx_XBAR_PRIOL PRIOL;                   /**< \brief 8, Arbiter Priority Register */
    Ifx_XBAR_ERRADDR ERRADDR;               /**< \brief C, Error/Debug Address Capture Register */
    Ifx_XBAR_ERR ERR;                       /**< \brief 10, Error/Debug Capture Register */
    Ifx_XBAR_DBCON DBCON;                   /**< \brief 14, Debug Control Register */
    Ifx_XBAR_ARBITER7_DBADD DBADD;          /**< \brief 18, Debug Address Register */
    Ifx_XBAR_ARBITER7_DBMADD DBMADD;        /**< \brief 1C, Debug Mask Address Register */
} Ifx_XBAR_ARBITER7;

/** \brief  Arbiter objects */
typedef volatile struct _Ifx_XBAR_ARBITER8
{
    Ifx_XBAR_ARBCON ARBCON;                 /**< \brief 0, Arbiter Control Register */
    Ifx_XBAR_PRIOH PRIOH;                   /**< \brief 4, Arbiter Priority Register */
    Ifx_XBAR_PRIOL PRIOL;                   /**< \brief 8, Arbiter Priority Register */
    Ifx_XBAR_ERRADDR ERRADDR;               /**< \brief C, Error/Debug Address Capture Register */
    Ifx_XBAR_ERR ERR;                       /**< \brief 10, Error/Debug Capture Register */
    Ifx_XBAR_DBCON DBCON;                   /**< \brief 14, Debug Control Register */
    Ifx_XBAR_ARBITER8_DBADD DBADD;          /**< \brief 18, Debug Address Register */
    Ifx_XBAR_ARBITER8_DBMADD DBMADD;        /**< \brief 1C, Debug Mask Address Register */
} Ifx_XBAR_ARBITER8;

/** \brief  Arbiter objects */
typedef volatile struct _Ifx_XBAR_ARBITERD
{
    Ifx_XBAR_ARBCON ARBCON;                 /**< \brief 0, Arbiter Control Register */
    Ifx_XBAR_PRIOH PRIOH;                   /**< \brief 4, Arbiter Priority Register */
    Ifx_XBAR_PRIOL PRIOL;                   /**< \brief 8, Arbiter Priority Register */
    Ifx_XBAR_ERRADDR ERRADDR;               /**< \brief C, Error/Debug Address Capture Register */
    Ifx_XBAR_ERR ERR;                       /**< \brief 10, Error/Debug Capture Register */
    Ifx_XBAR_DBCON DBCON;                   /**< \brief 14, Debug Control Register */
    Ifx_XBAR_ARBITERD_DBADD DBADD;          /**< \brief 18, Debug Address Register */
    Ifx_XBAR_ARBITERD_DBMADD DBMADD;        /**< \brief 1C, Debug Mask Address Register */
} Ifx_XBAR_ARBITERD;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Xbar_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \brief  XBAR object */
typedef volatile struct _Ifx_XBAR
{
    Ifx_XBAR_EXTCOND EXTCOND;               /**< \brief 0, External Control Register D */
    Ifx_XBAR_ARBITERD ARBITERD;             /**< \brief 4, Arbiter objects */
    unsigned char reserved_24[32];          /**< \brief 24, \internal Reserved */
    Ifx_XBAR_ARBITER0 ARBITER0;             /**< \brief 44, Arbiter objects */
    unsigned char reserved_64[32];          /**< \brief 64, \internal Reserved */
    Ifx_XBAR_ARBITER1 ARBITER1;             /**< \brief 84, Arbiter objects */
    unsigned char reserved_A4[160];         /**< \brief A4, \internal Reserved */
    Ifx_XBAR_ARBITER4 ARBITER4;             /**< \brief 144, Arbiter objects */
    unsigned char reserved_164[96];         /**< \brief 164, \internal Reserved */
    Ifx_XBAR_ARBITER6 ARBITER6;             /**< \brief 1C4, Arbiter objects */
    unsigned char reserved_1E4[32];         /**< \brief 1E4, \internal Reserved */
    Ifx_XBAR_ARBITER7 ARBITER7;             /**< \brief 204, Arbiter objects */
    unsigned char reserved_224[32];         /**< \brief 224, \internal Reserved */
    Ifx_XBAR_ARBITER8 ARBITER8;             /**< \brief 244, Arbiter objects */
    unsigned char reserved_264[420];        /**< \brief 264, \internal Reserved */
    Ifx_XBAR_ID ID;                         /**< \brief 408, Module Identification Register */
    Ifx_XBAR_DBSAT DBSAT;                   /**< \brief 40C, Debug Trigger Event Status Register */
    Ifx_XBAR_INTSAT INTSAT;                 /**< \brief 410, Arbiter Interrupt Status Register */
    Ifx_XBAR_IDINTSAT IDINTSAT;             /**< \brief 414, Transaction ID Interrupt Status Register */
    Ifx_XBAR_IDINTEN IDINTEN;               /**< \brief 418, Transaction ID Interrupt Enable Register */
    unsigned char reserved_41C[220];        /**< \brief 41C, \internal Reserved */
    Ifx_XBAR_ACCEN1 ACCEN1;                 /**< \brief 4F8, Access Enable Register 1 */
    Ifx_XBAR_ACCEN0 ACCEN0;                 /**< \brief 4FC, Access Enable Register 0 */
} Ifx_XBAR;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXXBAR_REGDEF_H */
