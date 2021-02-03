/**
 * \file IfxSbcu_regdef.h
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
 * \defgroup IfxLld_Sbcu Sbcu
 * \ingroup IfxLld
 * 
 * \defgroup IfxLld_Sbcu_Bitfields Bitfields
 * \ingroup IfxLld_Sbcu
 * 
 * \defgroup IfxLld_Sbcu_union Union
 * \ingroup IfxLld_Sbcu
 * 
 * \defgroup IfxLld_Sbcu_struct Struct
 * \ingroup IfxLld_Sbcu
 * 
 */
#ifndef IFXSBCU_REGDEF_H
#define IFXSBCU_REGDEF_H 1
/******************************************************************************/
#include "Ifx_TypesReg.h"
/******************************************************************************/
/** \addtogroup IfxLld_Sbcu_Bitfields
 * \{  */

/** \brief  Access Enable Register 0 */
typedef struct _Ifx_SBCU_ACCEN0_Bits
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
} Ifx_SBCU_ACCEN0_Bits;

/** \brief  Access Enable Register 1 */
typedef struct _Ifx_SBCU_ACCEN1_Bits
{
    unsigned int reserved_0:32;             /**< \brief \internal Reserved */
} Ifx_SBCU_ACCEN1_Bits;

/** \brief  SBCU Control Register */
typedef struct _Ifx_SBCU_CON_Bits
{
    unsigned int TOUT:16;                   /**< \brief [15:0] SBCU Bus Time-Out Value (rw) */
    unsigned int DBG:1;                     /**< \brief [16:16] SBCU Debug Trace Enable (rw) */
    unsigned int reserved_17:7;             /**< \brief \internal Reserved */
    unsigned int SPC:8;                     /**< \brief [31:24] Starvation Period Control (rw) */
} Ifx_SBCU_CON_Bits;

/** \brief  SBCU Debug Address 1 Register */
typedef struct _Ifx_SBCU_DBADR1_Bits
{
    unsigned int ADR1:32;                   /**< \brief [31:0] Debug Trigger Address 1 (rw) */
} Ifx_SBCU_DBADR1_Bits;

/** \brief  SBCU Debug Address 2 Register */
typedef struct _Ifx_SBCU_DBADR2_Bits
{
    unsigned int ADR2:32;                   /**< \brief [31:0] Debug Trigger Address 2 (rw) */
} Ifx_SBCU_DBADR2_Bits;

/** \brief  SBCU Debug Trapped Address Register */
typedef struct _Ifx_SBCU_DBADRT_Bits
{
    unsigned int FPIADR:32;                 /**< \brief [31:0] FPI Bus Address Status (rh) */
} Ifx_SBCU_DBADRT_Bits;

/** \brief  SBCU Debug Bus Operation Signals Register */
typedef struct _Ifx_SBCU_DBBOS_Bits
{
    unsigned int OPC:4;                     /**< \brief [3:0] Opcode for Signal Status Debug Trigger (rw) */
    unsigned int SVM:1;                     /**< \brief [4:4] SVM Signal for Status Debug Trigger (rw) */
    unsigned int reserved_5:3;              /**< \brief \internal Reserved */
    unsigned int WR:1;                      /**< \brief [8:8] Write Signal for Status Debug Trigger (rw) */
    unsigned int reserved_9:3;              /**< \brief \internal Reserved */
    unsigned int RD:1;                      /**< \brief [12:12] Write Signal for Status Debug Trigger (rw) */
    unsigned int reserved_13:19;            /**< \brief \internal Reserved */
} Ifx_SBCU_DBBOS_Bits;

/** \brief  SBCU Debug Trapped Bus Operation Signals Register */
typedef struct _Ifx_SBCU_DBBOST_Bits
{
    unsigned int FPIOPC:4;                  /**< \brief [3:0] FPI Bus Opcode Status (rh) */
    unsigned int FPISVM:1;                  /**< \brief [4:4] FPI Bus Supervisor Mode Status (rh) */
    unsigned int FPIACK:2;                  /**< \brief [6:5] FPI Bus Acknowledge Status (rh) */
    unsigned int FPIRDY:1;                  /**< \brief [7:7] FPI Bus Ready Status (rh) */
    unsigned int FPIWR:1;                   /**< \brief [8:8] FPI Bus Write Indication Status (rh) */
    unsigned int FPIRST:2;                  /**< \brief [10:9] FPI Bus Reset Status (rh) */
    unsigned int FPIOPS:1;                  /**< \brief [11:11] FPI Bus OCDS Suspend Status (rh) */
    unsigned int FPIRD:1;                   /**< \brief [12:12] FPI Bus Read Indication Status (rh) */
    unsigned int FPIABORT:1;                /**< \brief [13:13] FPI Bus Abort Status (rh) */
    unsigned int FPITOUT:1;                 /**< \brief [14:14] FPI Bus Time-out Status (rh) */
    unsigned int ENDINIT:1;                 /**< \brief [15:15] FPI Bus Endinit Status (rh) */
    unsigned int FPITAG:6;                  /**< \brief [21:16] FPI Bus Master TAG Status (rh) */
    unsigned int reserved_22:10;            /**< \brief \internal Reserved */
} Ifx_SBCU_DBBOST_Bits;

/** \brief  SBCU Debug Control Register */
typedef struct _Ifx_SBCU_DBCNTL_Bits
{
    unsigned int EO:1;                      /**< \brief [0:0] Status of SBCU Debug Support Enable (r) */
    unsigned int OA:1;                      /**< \brief [1:1] Status of SBCU Breakpoint Logic (r) */
    unsigned int reserved_2:2;              /**< \brief \internal Reserved */
    unsigned int RA:1;                      /**< \brief [4:4] Rearm SBCU Breakpoint Logic (w) */
    unsigned int reserved_5:7;              /**< \brief \internal Reserved */
    unsigned int CONCOM0:1;                 /**< \brief [12:12] Grant and Address Trigger Relation (rw) */
    unsigned int CONCOM1:1;                 /**< \brief [13:13] Address 1 and Address 2 Trigger Relation (rw) */
    unsigned int CONCOM2:1;                 /**< \brief [14:14] Address and Signal Trigger Relation (rw) */
    unsigned int reserved_15:1;             /**< \brief \internal Reserved */
    unsigned int ONG:1;                     /**< \brief [16:16] Grant Trigger Enable (rw) */
    unsigned int reserved_17:3;             /**< \brief \internal Reserved */
    unsigned int ONA1:2;                    /**< \brief [21:20] Address 1 Trigger Control (rw) */
    unsigned int reserved_22:2;             /**< \brief \internal Reserved */
    unsigned int ONA2:2;                    /**< \brief [25:24] Address 2 Trigger Control (rw) */
    unsigned int reserved_26:2;             /**< \brief \internal Reserved */
    unsigned int ONBOS0:1;                  /**< \brief [28:28] Opcode Signal Status Trigger Condition (rw) */
    unsigned int ONBOS1:1;                  /**< \brief [29:29] Supervisor Mode Signal Trigger Condition (rw) */
    unsigned int ONBOS2:1;                  /**< \brief [30:30] Write Signal Trigger Condition (rw) */
    unsigned int ONBOS3:1;                  /**< \brief [31:31] Read Signal Trigger Condition (rw) */
} Ifx_SBCU_DBCNTL_Bits;

/** \brief  SBCU Debug Data Status Register */
typedef struct _Ifx_SBCU_DBDAT_Bits
{
    unsigned int FPIDATA:32;                /**< \brief [31:0] FPI Bus Data Status (rh) */
} Ifx_SBCU_DBDAT_Bits;

/** \brief  SBCU Debug Trapped Master Register */
typedef struct _Ifx_SBCU_DBGNTT_Bits
{
    unsigned int DMAH:1;                    /**< \brief [0:0] High-Priority DMA FPI Bus Master Status (rw) */
    unsigned int ONE0:1;                    /**< \brief [1:1] Reserved (rw) */
    unsigned int ETH:1;                     /**< \brief [2:2] Ethernet FPI Bus Master Status (rw) */
    unsigned int HSSL:1;                    /**< \brief [3:3] HSSL FPI Bus Master Status (rw) */
    unsigned int ONE1:1;                    /**< \brief [4:4] Reserved (rw) */
    unsigned int DMAM:1;                    /**< \brief [5:5] Medium-Priority DMA FPI Bus Master Status (rw) */
    unsigned int ONE2:1;                    /**< \brief [6:6] Reserved (rw) */
    unsigned int CPU0:1;                    /**< \brief [7:7] CPU0 FPI Bus Master Status (rw) */
    unsigned int CPU1:1;                    /**< \brief [8:8] CPU1 FPI Bus Master Status (rw) */
    unsigned int ONE3:6;                    /**< \brief [14:9] Reserved (rw) */
    unsigned int DMAL:1;                    /**< \brief [15:15] Low-Priority DMA FPI Bus Master Status (rw) */
    unsigned int DMACHNR:8;                 /**< \brief [23:16] DMA-FPI Channel Grant Status (rw) */
    unsigned int ONE4:8;                    /**< \brief [31:24] Reserved (rw) */
} Ifx_SBCU_DBGNTT_Bits;

/** \brief  SBCU Debug Grant Mask Register */
typedef struct _Ifx_SBCU_DBGRNT_Bits
{
    unsigned int DMAH:1;                    /**< \brief [0:0] DMA High Priority Trigger Enable (rw) */
    unsigned int ONE0:1;                    /**< \brief [1:1] Reserved (rw) */
    unsigned int ETH:1;                     /**< \brief [2:2] Ethernet Trigger Enable (rw) */
    unsigned int HSSL:1;                    /**< \brief [3:3] HSSL Trigger Enable (rw) */
    unsigned int ONE1:1;                    /**< \brief [4:4] Reserved (rw) */
    unsigned int DMAM:1;                    /**< \brief [5:5] DMA Grant Trigger Enable, Medium Priority (rw) */
    unsigned int ONE2:1;                    /**< \brief [6:6] Reserved (rw) */
    unsigned int CPU0:1;                    /**< \brief [7:7] CPU0 Grant Trigger Enable (rw) */
    unsigned int CPU1:1;                    /**< \brief [8:8] CPU1 Grant Trigger Enable (rw) */
    unsigned int ONE3:5;                    /**< \brief [13:9] Reserved (rw) */
    unsigned int ONE4:1;                    /**< \brief [14:14] Reserved (rw) */
    unsigned int DMAL:1;                    /**< \brief [15:15] DMA Grant Trigger Enable, Low Priority (rw) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_SBCU_DBGRNT_Bits;

/** \brief  SBCU Error Address Capture Register */
typedef struct _Ifx_SBCU_EADD_Bits
{
    unsigned int FPIADR:32;                 /**< \brief [31:0] Captured FPI Bus Address (rwh) */
} Ifx_SBCU_EADD_Bits;

/** \brief  SBCU Error Control Capture Register */
typedef struct _Ifx_SBCU_ECON_Bits
{
    unsigned int ERRCNT:14;                 /**< \brief [13:0] FPI Bus Error Counter (rwh) */
    unsigned int TOUT:1;                    /**< \brief [14:14] State of FPI Bus Time-Out Signal (rwh) */
    unsigned int RDY:1;                     /**< \brief [15:15] State of FPI Bus Ready Signal (rwh) */
    unsigned int ABT:1;                     /**< \brief [16:16] State of FPI Bus Abort Signal (rwh) */
    unsigned int ACK:2;                     /**< \brief [18:17] State of FPI Bus Acknowledge Signals (rwh) */
    unsigned int SVM:1;                     /**< \brief [19:19] State of FPI Bus Supervisor Mode Signal (rwh) */
    unsigned int WRN:1;                     /**< \brief [20:20] State of FPI Bus Write Signal (rwh) */
    unsigned int RDN:1;                     /**< \brief [21:21] State of FPI Bus Read Signal (rwh) */
    unsigned int TAG:6;                     /**< \brief [27:22] FPI Bus Master Tag Number Signals (rwh) */
    unsigned int OPC:4;                     /**< \brief [31:28] FPI Bus Operation Code Signals (rwh) */
} Ifx_SBCU_ECON_Bits;

/** \brief  SBCU Error Data Capture Register */
typedef struct _Ifx_SBCU_EDAT_Bits
{
    unsigned int FPIDAT:32;                 /**< \brief [31:0] Captured FPI Bus Data (rwh) */
} Ifx_SBCU_EDAT_Bits;

/** \brief  Module Identification Register */
typedef struct _Ifx_SBCU_ID_Bits
{
    unsigned int MODREV:8;                  /**< \brief [7:0] Module Revision Number (r) */
    unsigned int MODNUMBER:8;               /**< \brief [15:8] Module Number Value (r) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_SBCU_ID_Bits;

/** \brief  Arbiter Priority Register High */
typedef struct _Ifx_SBCU_PRIOH_Bits
{
    unsigned int CPU1:4;                    /**< \brief [3:0] Master 8 Priority (rw) */
    unsigned int RESERVED9:4;               /**< \brief [7:4] Reserved (rw) */
    unsigned int RESERVEDA:4;               /**< \brief [11:8] Reserved (rw) */
    unsigned int RESERVEDB:4;               /**< \brief [15:12] Reserved (rw) */
    unsigned int RESERVEDC:4;               /**< \brief [19:16] Reserved (rw) */
    unsigned int RESERVEDD:4;               /**< \brief [23:20] Reserved (rw) */
    unsigned int RESERVEDE:4;               /**< \brief [27:24] Reserved (rw) */
    unsigned int DMAL:4;                    /**< \brief [31:28] Master 15 Priority (rw) */
} Ifx_SBCU_PRIOH_Bits;

/** \brief  Arbiter Priority Register Low */
typedef struct _Ifx_SBCU_PRIOL_Bits
{
    unsigned int DMAH:4;                    /**< \brief [3:0] Master 0 Priority (rw) */
    unsigned int RESERVED1:4;               /**< \brief [7:4] Reserved (rw) */
    unsigned int ETH:4;                     /**< \brief [11:8] Master 2 Priority (rw) */
    unsigned int HSSL:4;                    /**< \brief [15:12] Master 3 Priority (rw) */
    unsigned int RESERVED4:4;               /**< \brief [19:16] Reserved (rw) */
    unsigned int DMAM:4;                    /**< \brief [23:20] Master 5 Priority (rw) */
    unsigned int RESERVED6:4;               /**< \brief [27:24] Reserved (rw) */
    unsigned int CPU0:4;                    /**< \brief [31:28] Master 7 Priority (rw) */
} Ifx_SBCU_PRIOL_Bits;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Sbcu_union
 * \{  */

/** \brief  Access Enable Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SBCU_ACCEN0_Bits B;                 /**< \brief Bitfield access */
} Ifx_SBCU_ACCEN0;

/** \brief  Access Enable Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SBCU_ACCEN1_Bits B;                 /**< \brief Bitfield access */
} Ifx_SBCU_ACCEN1;

/** \brief  SBCU Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SBCU_CON_Bits B;                    /**< \brief Bitfield access */
} Ifx_SBCU_CON;

/** \brief  SBCU Debug Address 1 Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SBCU_DBADR1_Bits B;                 /**< \brief Bitfield access */
} Ifx_SBCU_DBADR1;

/** \brief  SBCU Debug Address 2 Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SBCU_DBADR2_Bits B;                 /**< \brief Bitfield access */
} Ifx_SBCU_DBADR2;

/** \brief  SBCU Debug Trapped Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SBCU_DBADRT_Bits B;                 /**< \brief Bitfield access */
} Ifx_SBCU_DBADRT;

/** \brief  SBCU Debug Bus Operation Signals Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SBCU_DBBOS_Bits B;                  /**< \brief Bitfield access */
} Ifx_SBCU_DBBOS;

/** \brief  SBCU Debug Trapped Bus Operation Signals Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SBCU_DBBOST_Bits B;                 /**< \brief Bitfield access */
} Ifx_SBCU_DBBOST;

/** \brief  SBCU Debug Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SBCU_DBCNTL_Bits B;                 /**< \brief Bitfield access */
} Ifx_SBCU_DBCNTL;

/** \brief  SBCU Debug Data Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SBCU_DBDAT_Bits B;                  /**< \brief Bitfield access */
} Ifx_SBCU_DBDAT;

/** \brief  SBCU Debug Trapped Master Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SBCU_DBGNTT_Bits B;                 /**< \brief Bitfield access */
} Ifx_SBCU_DBGNTT;

/** \brief  SBCU Debug Grant Mask Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SBCU_DBGRNT_Bits B;                 /**< \brief Bitfield access */
} Ifx_SBCU_DBGRNT;

/** \brief  SBCU Error Address Capture Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SBCU_EADD_Bits B;                   /**< \brief Bitfield access */
} Ifx_SBCU_EADD;

/** \brief  SBCU Error Control Capture Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SBCU_ECON_Bits B;                   /**< \brief Bitfield access */
} Ifx_SBCU_ECON;

/** \brief  SBCU Error Data Capture Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SBCU_EDAT_Bits B;                   /**< \brief Bitfield access */
} Ifx_SBCU_EDAT;

/** \brief  Module Identification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SBCU_ID_Bits B;                     /**< \brief Bitfield access */
} Ifx_SBCU_ID;

/** \brief  Arbiter Priority Register High */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SBCU_PRIOH_Bits B;                  /**< \brief Bitfield access */
} Ifx_SBCU_PRIOH;

/** \brief  Arbiter Priority Register Low */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SBCU_PRIOL_Bits B;                  /**< \brief Bitfield access */
} Ifx_SBCU_PRIOL;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Sbcu_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \brief  SBCU object */
typedef volatile struct _Ifx_SBCU
{
    unsigned char reserved_0[8];            /**< \brief 0, \internal Reserved */
    Ifx_SBCU_ID ID;                         /**< \brief 8, Module Identification Register */
    unsigned char reserved_C[4];            /**< \brief C, \internal Reserved */
    Ifx_SBCU_CON CON;                       /**< \brief 10, SBCU Control Register */
    Ifx_SBCU_PRIOH PRIOH;                   /**< \brief 14, Arbiter Priority Register High */
    Ifx_SBCU_PRIOL PRIOL;                   /**< \brief 18, Arbiter Priority Register Low */
    unsigned char reserved_1C[4];           /**< \brief 1C, \internal Reserved */
    Ifx_SBCU_ECON ECON;                     /**< \brief 20, SBCU Error Control Capture Register */
    Ifx_SBCU_EADD EADD;                     /**< \brief 24, SBCU Error Address Capture Register */
    Ifx_SBCU_EDAT EDAT;                     /**< \brief 28, SBCU Error Data Capture Register */
    unsigned char reserved_2C[4];           /**< \brief 2C, \internal Reserved */
    Ifx_SBCU_DBCNTL DBCNTL;                 /**< \brief 30, SBCU Debug Control Register */
    Ifx_SBCU_DBGRNT DBGRNT;                 /**< \brief 34, SBCU Debug Grant Mask Register */
    Ifx_SBCU_DBADR1 DBADR1;                 /**< \brief 38, SBCU Debug Address 1 Register */
    Ifx_SBCU_DBADR2 DBADR2;                 /**< \brief 3C, SBCU Debug Address 2 Register */
    Ifx_SBCU_DBBOS DBBOS;                   /**< \brief 40, SBCU Debug Bus Operation Signals Register */
    Ifx_SBCU_DBGNTT DBGNTT;                 /**< \brief 44, SBCU Debug Trapped Master Register */
    Ifx_SBCU_DBADRT DBADRT;                 /**< \brief 48, SBCU Debug Trapped Address Register */
    Ifx_SBCU_DBBOST DBBOST;                 /**< \brief 4C, SBCU Debug Trapped Bus Operation Signals Register */
    Ifx_SBCU_DBDAT DBDAT;                   /**< \brief 50, SBCU Debug Data Status Register */
    unsigned char reserved_54[164];         /**< \brief 54, \internal Reserved */
    Ifx_SBCU_ACCEN1 ACCEN1;                 /**< \brief F8, Access Enable Register 1 */
    Ifx_SBCU_ACCEN0 ACCEN0;                 /**< \brief FC, Access Enable Register 0 */
} Ifx_SBCU;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXSBCU_REGDEF_H */
