/**
 * \file IfxFlash_regdef.h
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
 * \defgroup IfxLld_Flash Flash
 * \ingroup IfxLld
 * 
 * \defgroup IfxLld_Flash_Bitfields Bitfields
 * \ingroup IfxLld_Flash
 * 
 * \defgroup IfxLld_Flash_union Union
 * \ingroup IfxLld_Flash
 * 
 * \defgroup IfxLld_Flash_struct Struct
 * \ingroup IfxLld_Flash
 * 
 */
#ifndef IFXFLASH_REGDEF_H
#define IFXFLASH_REGDEF_H 1
/******************************************************************************/
#include "Ifx_TypesReg.h"
/******************************************************************************/
/** \addtogroup IfxLld_Flash_Bitfields
 * \{  */

/** \brief  Access Enable Register 0 */
typedef struct _Ifx_FLASH_ACCEN0_Bits
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
} Ifx_FLASH_ACCEN0_Bits;

/** \brief  Access Enable Register 1 */
typedef struct _Ifx_FLASH_ACCEN1_Bits
{
    unsigned int reserved_0:32;             /**< \brief \internal Reserved */
} Ifx_FLASH_ACCEN1_Bits;

/** \brief  CBAB Configuration */
typedef struct _Ifx_FLASH_CBAB_CFG_Bits
{
    unsigned int SEL:6;                     /**< \brief [5:0] Select Bit-Errors (rw) */
    unsigned int reserved_6:2;              /**< \brief \internal Reserved */
    unsigned int CLR:1;                     /**< \brief [8:8] Clear (w) */
    unsigned int DIS:1;                     /**< \brief [9:9] Disable (rw) */
    unsigned int reserved_10:22;            /**< \brief \internal Reserved */
} Ifx_FLASH_CBAB_CFG_Bits;

/** \brief  CBAB Status */
typedef struct _Ifx_FLASH_CBAB_STAT_Bits
{
    unsigned int VLD0:1;                    /**< \brief [0:0] Filling Level (rh) */
    unsigned int VLD1:1;                    /**< \brief [1:1] Filling Level (rh) */
    unsigned int VLD2:1;                    /**< \brief [2:2] Filling Level (rh) */
    unsigned int VLD3:1;                    /**< \brief [3:3] Filling Level (rh) */
    unsigned int VLD4:1;                    /**< \brief [4:4] Filling Level (rh) */
    unsigned int VLD5:1;                    /**< \brief [5:5] Filling Level (rh) */
    unsigned int VLD6:1;                    /**< \brief [6:6] Filling Level (rh) */
    unsigned int VLD7:1;                    /**< \brief [7:7] Filling Level (rh) */
    unsigned int VLD8:1;                    /**< \brief [8:8] Filling Level (rh) */
    unsigned int VLD9:1;                    /**< \brief [9:9] Filling Level (rh) */
    unsigned int reserved_10:22;            /**< \brief \internal Reserved */
} Ifx_FLASH_CBAB_STAT_Bits;

/** \brief  CBAB FIFO TOP Entry */
typedef struct _Ifx_FLASH_CBAB_TOP_Bits
{
    unsigned int reserved_0:5;              /**< \brief \internal Reserved */
    unsigned int ADDR:19;                   /**< \brief [23:5] Address (rh) */
    unsigned int ERR:6;                     /**< \brief [29:24] Error Type (rh) */
    unsigned int VLD:1;                     /**< \brief [30:30] Valid (rh) */
    unsigned int CLR:1;                     /**< \brief [31:31] Clear (w) */
} Ifx_FLASH_CBAB_TOP_Bits;

/** \brief  FSI Communication Register 0 */
typedef struct _Ifx_FLASH_COMM0_Bits
{
    unsigned int STATUS:8;                  /**< \brief [7:0] Status (rh) */
    unsigned int reserved_8:24;             /**< \brief \internal Reserved */
} Ifx_FLASH_COMM0_Bits;

/** \brief  FSI Communication Register 1 */
typedef struct _Ifx_FLASH_COMM1_Bits
{
    unsigned int STATUS:8;                  /**< \brief [7:0] Status (rh) */
    unsigned int DATA:8;                    /**< \brief [15:8] Data (rwh) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_FLASH_COMM1_Bits;

/** \brief  FSI Communication Register 2 */
typedef struct _Ifx_FLASH_COMM2_Bits
{
    unsigned int STATUS:8;                  /**< \brief [7:0] Status (rh) */
    unsigned int DATA:8;                    /**< \brief [15:8] Data (rwh) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_FLASH_COMM2_Bits;

/** \brief  ECC Read Register DF */
typedef struct _Ifx_FLASH_ECCRD_Bits
{
    unsigned int RCODE:22;                  /**< \brief [21:0] Error Correction Read Code (rh) */
    unsigned int reserved_22:8;             /**< \brief \internal Reserved */
    unsigned int EDCERRINJ:1;               /**< \brief [30:30] EDC Error Injection (rw) */
    unsigned int ECCORDIS:1;                /**< \brief [31:31] ECC Correction Disable (rw) */
} Ifx_FLASH_ECCRD_Bits;

/** \brief  ECC Read Register */
typedef struct _Ifx_FLASH_ECCRP_Bits
{
    unsigned int RCODE:22;                  /**< \brief [21:0] Error Correction Read Code (rh) */
    unsigned int reserved_22:8;             /**< \brief \internal Reserved */
    unsigned int EDCERRINJ:1;               /**< \brief [30:30] EDC Error Injection (rw) */
    unsigned int ECCORDIS:1;                /**< \brief [31:31] ECC Correction Disable (rw) */
} Ifx_FLASH_ECCRP_Bits;

/** \brief  ECC Write Register */
typedef struct _Ifx_FLASH_ECCW_Bits
{
    unsigned int WCODE:22;                  /**< \brief [21:0] Error Correction Write Code (rw) */
    unsigned int reserved_22:8;             /**< \brief \internal Reserved */
    unsigned int DECENCDIS:1;               /**< \brief [30:30] DF_EEPROM ECC Encoding Disable (rw) */
    unsigned int PECENCDIS:1;               /**< \brief [31:31] PFlash ECC Encoding Disable (rw) */
} Ifx_FLASH_ECCW_Bits;

/** \brief  Flash Configuration Register */
typedef struct _Ifx_FLASH_FCON_Bits
{
    unsigned int WSPFLASH:4;                /**< \brief [3:0] Wait States for read access to PFlash (rw) */
    unsigned int WSECPF:2;                  /**< \brief [5:4] Wait States for Error Correction of PFlash (rw) */
    unsigned int WSDFLASH:6;                /**< \brief [11:6] Wait States for read access to DFlash (rw) */
    unsigned int WSECDF:3;                  /**< \brief [14:12] Wait State for Error Correction of DFlash (rw) */
    unsigned int IDLE:1;                    /**< \brief [15:15] Dynamic Flash Idle (rw) */
    unsigned int ESLDIS:1;                  /**< \brief [16:16] External Sleep Request Disable (rw) */
    unsigned int SLEEP:1;                   /**< \brief [17:17] Flash SLEEP (rw) */
    unsigned int NSAFECC:1;                 /**< \brief [18:18] Non-Safety PFlash ECC (rw) */
    unsigned int STALL:1;                   /**< \brief [19:19] Stall SRI (rw) */
    unsigned int RES21:2;                   /**< \brief [21:20] Reserved (rh) */
    unsigned int RES23:2;                   /**< \brief [23:22] Reserved (rh) */
    unsigned int VOPERM:1;                  /**< \brief [24:24] Verify and Operation Error Interrupt Mask (rw) */
    unsigned int SQERM:1;                   /**< \brief [25:25] Command Sequence Error Interrupt Mask (rw) */
    unsigned int PROERM:1;                  /**< \brief [26:26] Protection Error Interrupt Mask (rw) */
    unsigned int reserved_27:3;             /**< \brief \internal Reserved */
    unsigned int PR5V:1;                    /**< \brief [30:30] Programming Supply 5V (rw) */
    unsigned int EOBM:1;                    /**< \brief [31:31] End of Busy Interrupt Mask (rw) */
} Ifx_FLASH_FCON_Bits;

/** \brief  Flash Protection Control and Status Register */
typedef struct _Ifx_FLASH_FPRO_Bits
{
    unsigned int PROINP:1;                  /**< \brief [0:0] PFlash Protection (rh) */
    unsigned int PRODISP:1;                 /**< \brief [1:1] PFlash Protection Disabled (rh) */
    unsigned int PROIND:1;                  /**< \brief [2:2] DFlash Protection (rh) */
    unsigned int PRODISD:1;                 /**< \brief [3:3] DFlash Protection Disabled (rh) */
    unsigned int PROINHSMCOTP:1;            /**< \brief [4:4] HSM OTP Protection (rh) */
    unsigned int RES5:1;                    /**< \brief [5:5] Reserved (rh) */
    unsigned int PROINOTP:1;                /**< \brief [6:6] OTP and Write-Once Protection (rh) */
    unsigned int RES7:1;                    /**< \brief [7:7] Reserved (rh) */
    unsigned int PROINDBG:1;                /**< \brief [8:8] Debug Interface Password Protection (rh) */
    unsigned int PRODISDBG:1;               /**< \brief [9:9] Debug Interface Password Protection Disabled (rh) */
    unsigned int PROINHSM:1;                /**< \brief [10:10] HSM Configuration (rh) */
    unsigned int reserved_11:5;             /**< \brief \internal Reserved */
    unsigned int DCFP:1;                    /**< \brief [16:16] Disable Code Fetch from PFlash Memory for CPU0 PMI (rwh) */
    unsigned int DDFP:1;                    /**< \brief [17:17] Disable Read from PFlash for CPU0 DMI (rwh) */
    unsigned int DDFPX:1;                   /**< \brief [18:18] Disable Read from PFlash for Other Masters (rwh) */
    unsigned int reserved_19:1;             /**< \brief \internal Reserved */
    unsigned int DDFD:1;                    /**< \brief [20:20] Disable Data Fetch from DFlash Memory (rwh) */
    unsigned int reserved_21:1;             /**< \brief \internal Reserved */
    unsigned int ENPE:2;                    /**< \brief [23:22] Enable Program/Erase (rw) */
    unsigned int reserved_24:8;             /**< \brief \internal Reserved */
} Ifx_FLASH_FPRO_Bits;

/** \brief  Flash Status Register */
typedef struct _Ifx_FLASH_FSR_Bits
{
    unsigned int FABUSY:1;                  /**< \brief [0:0] Flash Array Busy (rh) */
    unsigned int D0BUSY:1;                  /**< \brief [1:1] Data Flash Bank 0 Busy (rh) */
    unsigned int RES1:1;                    /**< \brief [2:2] Reserved for Data Flash Bank 1 Busy (rh) */
    unsigned int P0BUSY:1;                  /**< \brief [3:3] Program Flash PF0 Busy (rh) */
    unsigned int P1BUSY:1;                  /**< \brief [4:4] Program Flash PF1 Busy (rh) */
    unsigned int RES5:1;                    /**< \brief [5:5] Reserved for Program Flash PF2 Busy (rh) */
    unsigned int RES6:1;                    /**< \brief [6:6] Reserved for Program Flash PF3 Busy (rh) */
    unsigned int PROG:1;                    /**< \brief [7:7] Programming State (rwh) */
    unsigned int ERASE:1;                   /**< \brief [8:8] Erase State (rwh) */
    unsigned int PFPAGE:1;                  /**< \brief [9:9] Program Flash in Page Mode (rh) */
    unsigned int DFPAGE:1;                  /**< \brief [10:10] Data Flash in Page Mode (rh) */
    unsigned int OPER:1;                    /**< \brief [11:11] Flash Operation Error (rwh) */
    unsigned int SQER:1;                    /**< \brief [12:12] Command Sequence Error (rwh) */
    unsigned int PROER:1;                   /**< \brief [13:13] Protection Error (rwh) */
    unsigned int PFSBER:1;                  /**< \brief [14:14] PFlash Single-Bit Error and Correction (rwh) */
    unsigned int PFDBER:1;                  /**< \brief [15:15] PFlash Double-Bit Error (rwh) */
    unsigned int PFMBER:1;                  /**< \brief [16:16] PFlash Uncorrectable Error (rwh) */
    unsigned int RES17:1;                   /**< \brief [17:17] Reserved (rwh) */
    unsigned int DFSBER:1;                  /**< \brief [18:18] DFlash Single-Bit Error (rwh) */
    unsigned int DFDBER:1;                  /**< \brief [19:19] DFlash Double-Bit Error (rwh) */
    unsigned int DFTBER:1;                  /**< \brief [20:20] DFlash Triple-Bit Error (rwh) */
    unsigned int DFMBER:1;                  /**< \brief [21:21] DFlash Uncorrectable Error (rwh) */
    unsigned int SRIADDERR:1;               /**< \brief [22:22] SRI Bus Address ECC Error (rwh) */
    unsigned int reserved_23:2;             /**< \brief \internal Reserved */
    unsigned int PVER:1;                    /**< \brief [25:25] Program Verify Error (rwh) */
    unsigned int EVER:1;                    /**< \brief [26:26] Erase Verify Error (rwh) */
    unsigned int SPND:1;                    /**< \brief [27:27] Operation Suspended (rwh) */
    unsigned int SLM:1;                     /**< \brief [28:28] Flash Sleep Mode (rh) */
    unsigned int reserved_29:1;             /**< \brief \internal Reserved */
    unsigned int ORIER:1;                   /**< \brief [30:30] Original Error (rh) */
    unsigned int reserved_31:1;             /**< \brief \internal Reserved */
} Ifx_FLASH_FSR_Bits;

/** \brief  Flash Module Identification Register */
typedef struct _Ifx_FLASH_ID_Bits
{
    unsigned int MODREV:8;                  /**< \brief [7:0] Module Revision Number (r) */
    unsigned int MODTYPE:8;                 /**< \brief [15:8] Module Type (r) */
    unsigned int MODNUMBER:16;              /**< \brief [31:16] Module Number Value (r) */
} Ifx_FLASH_ID_Bits;

/** \brief  Margin Control Register DFlash */
typedef struct _Ifx_FLASH_MARD_Bits
{
    unsigned int HMARGIN:1;                 /**< \brief [0:0] Hard Margin Selection (rw) */
    unsigned int SELD0:1;                   /**< \brief [1:1] DFLASH Bank Selection (rw) */
    unsigned int reserved_2:1;              /**< \brief \internal Reserved */
    unsigned int SPND:1;                    /**< \brief [3:3] Suspend (rwh) */
    unsigned int SPNDERR:1;                 /**< \brief [4:4] Suspend Error (rwh) */
    unsigned int reserved_5:10;             /**< \brief \internal Reserved */
    unsigned int TRAPDIS:1;                 /**< \brief [15:15] DFLASH Uncorrectable Bit Error Trap Disable (rw) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_FLASH_MARD_Bits;

/** \brief  Margin Control Register PFlash */
typedef struct _Ifx_FLASH_MARP_Bits
{
    unsigned int SELP0:1;                   /**< \brief [0:0] PFLASH Bank PF0 Selection (rw) */
    unsigned int SELP1:1;                   /**< \brief [1:1] PFLASH Bank PF1 Selection (rw) */
    unsigned int RES2:1;                    /**< \brief [2:2] Reserved (rw) */
    unsigned int RES3:1;                    /**< \brief [3:3] Reserved (rw) */
    unsigned int reserved_4:11;             /**< \brief \internal Reserved */
    unsigned int TRAPDIS:1;                 /**< \brief [15:15] PFLASH Uncorrectable Bit Error Trap Disable (rw) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_FLASH_MARP_Bits;

/** \brief  DFlash Protection Configuration */
typedef struct _Ifx_FLASH_PROCOND_Bits
{
    unsigned int L:1;                       /**< \brief [0:0] DF_EEPROM Locked for Write Protection (rh) */
    unsigned int NSAFECC:1;                 /**< \brief [1:1] Non-Safety PFlash ECC (rh) */
    unsigned int RAMIN:2;                   /**< \brief [3:2] RAM Initialization by SSW Control (rh) */
    unsigned int RAMINSEL:4;                /**< \brief [7:4] RAM Initialization Selection (rh) */
    unsigned int OSCCFG:1;                  /**< \brief [8:8] OSC Configuration by SSW (rh) */
    unsigned int MODE:2;                    /**< \brief [10:9] OSC Mode (rh) */
    unsigned int APREN:1;                   /**< \brief [11:11] OSC Amplitude Regulation Enable (rh) */
    unsigned int CAP0EN:1;                  /**< \brief [12:12] OSC Capacitance 0 Enable (rh) */
    unsigned int CAP1EN:1;                  /**< \brief [13:13] OSC Capacitance 1 Enable (rh) */
    unsigned int CAP2EN:1;                  /**< \brief [14:14] OSC Capacitance 2 Enable (rh) */
    unsigned int CAP3EN:1;                  /**< \brief [15:15] OSC Capacitance 3 Enable (rh) */
    unsigned int ESR0CNT:12;                /**< \brief [27:16] ESR0 Prolongation Counter (rh) */
    unsigned int RES29:2;                   /**< \brief [29:28] Reserved (rh) */
    unsigned int RES30:1;                   /**< \brief [30:30] Reserved (rh) */
    unsigned int RPRO:1;                    /**< \brief [31:31] Read Protection Configuration (rh) */
} Ifx_FLASH_PROCOND_Bits;

/** \brief  Debug Interface Protection Configuration */
typedef struct _Ifx_FLASH_PROCONDBG_Bits
{
    unsigned int OCDSDIS:1;                 /**< \brief [0:0] OCDS Disabled (rh) */
    unsigned int DBGIFLCK:1;                /**< \brief [1:1] Debug Interface Locked (rh) */
    unsigned int EDM:2;                     /**< \brief [3:2] Entered Debug Mode (rh) */
    unsigned int reserved_4:28;             /**< \brief \internal Reserved */
} Ifx_FLASH_PROCONDBG_Bits;

/** \brief  HSM Interface Configuration */
typedef struct _Ifx_FLASH_PROCONHSM_Bits
{
    unsigned int HSMDBGDIS:1;               /**< \brief [0:0] HSM Debug Disable (rh) */
    unsigned int DBGIFLCK:1;                /**< \brief [1:1] Debug Interface Locked (rh) */
    unsigned int TSTIFLCK:1;                /**< \brief [2:2] Test Interface Locked (rh) */
    unsigned int HSMTSTDIS:1;               /**< \brief [3:3] HSM Test Disable (rh) */
    unsigned int RES15:12;                  /**< \brief [15:4] Reserved (rh) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_FLASH_PROCONHSM_Bits;

/** \brief  HSM Code Flash OTP Protection Configuration */
typedef struct _Ifx_FLASH_PROCONHSMCOTP_Bits
{
    unsigned int HSMBOOTEN:1;               /**< \brief [0:0] HSM Boot Enable (rh) */
    unsigned int SSWWAIT:1;                 /**< \brief [1:1] SSW Wait (rh) */
    unsigned int HSMDX:1;                   /**< \brief [2:2] HSM Data Sectors Exclusive (rh) */
    unsigned int HSM6X:1;                   /**< \brief [3:3] HSM Code Sector 6 Exclusive (rh) */
    unsigned int HSM16X:1;                  /**< \brief [4:4] HSM Code Sector 16 Exclusive (rh) */
    unsigned int HSM17X:1;                  /**< \brief [5:5] HSM Code Sector 17 Exclusive (rh) */
    unsigned int S6ROM:1;                   /**< \brief [6:6] HSM Code Sector 6 Locked Forever (rh) */
    unsigned int HSMENPINS:2;               /**< \brief [8:7] Enable HSM Forcing of Pins HSM1/2 (rh) */
    unsigned int HSMENRES:2;                /**< \brief [10:9] Enable HSM Triggering Resets (rh) */
    unsigned int DESTDBG:2;                 /**< \brief [12:11] Destructive Debug Entry (rh) */
    unsigned int BLKFLAN:1;                 /**< \brief [13:13] Block Flash Analysis (rh) */
    unsigned int reserved_14:2;             /**< \brief \internal Reserved */
    unsigned int S16ROM:1;                  /**< \brief [16:16] HSM Code Sector 16 Locked Forever (rh) */
    unsigned int S17ROM:1;                  /**< \brief [17:17] HSM Code Sector 17 Locked Forever (rh) */
    unsigned int reserved_18:14;            /**< \brief \internal Reserved */
} Ifx_FLASH_PROCONHSMCOTP_Bits;

/** \brief  OTP Protection Configuration */
typedef struct _Ifx_FLASH_PROCONOTP_Bits
{
    unsigned int S0ROM:1;                   /**< \brief [0:0] PFlash p Sector 0 Locked Forever (rh) */
    unsigned int S1ROM:1;                   /**< \brief [1:1] PFlash p Sector 1 Locked Forever (rh) */
    unsigned int S2ROM:1;                   /**< \brief [2:2] PFlash p Sector 2 Locked Forever (rh) */
    unsigned int S3ROM:1;                   /**< \brief [3:3] PFlash p Sector 3 Locked Forever (rh) */
    unsigned int S4ROM:1;                   /**< \brief [4:4] PFlash p Sector 4 Locked Forever (rh) */
    unsigned int S5ROM:1;                   /**< \brief [5:5] PFlash p Sector 5 Locked Forever (rh) */
    unsigned int S6ROM:1;                   /**< \brief [6:6] PFlash p Sector 6 Locked Forever (rh) */
    unsigned int S7ROM:1;                   /**< \brief [7:7] PFlash p Sector 7 Locked Forever (rh) */
    unsigned int S8ROM:1;                   /**< \brief [8:8] PFlash p Sector 8 Locked Forever (rh) */
    unsigned int S9ROM:1;                   /**< \brief [9:9] PFlash p Sector 9 Locked Forever (rh) */
    unsigned int S10ROM:1;                  /**< \brief [10:10] PFlash p Sector 10 Locked Forever (rh) */
    unsigned int S11ROM:1;                  /**< \brief [11:11] PFlash p Sector 11 Locked Forever (rh) */
    unsigned int S12ROM:1;                  /**< \brief [12:12] PFlash p Sector 12 Locked Forever (rh) */
    unsigned int S13ROM:1;                  /**< \brief [13:13] PFlash p Sector 13 Locked Forever (rh) */
    unsigned int S14ROM:1;                  /**< \brief [14:14] PFlash p Sector 14 Locked Forever (rh) */
    unsigned int S15ROM:1;                  /**< \brief [15:15] PFlash p Sector 15 Locked Forever (rh) */
    unsigned int S16ROM:1;                  /**< \brief [16:16] PFlash p Sector 16 Locked Forever (rh) */
    unsigned int S17ROM:1;                  /**< \brief [17:17] PFlash p Sector 17 Locked Forever (rh) */
    unsigned int S18ROM:1;                  /**< \brief [18:18] PFlash p Sector 18 Locked Forever (rh) */
    unsigned int S19ROM:1;                  /**< \brief [19:19] PFlash p Sector 19 Locked Forever (rh) */
    unsigned int S20ROM:1;                  /**< \brief [20:20] PFlash p Sector 20 Locked Forever (rh) */
    unsigned int S21ROM:1;                  /**< \brief [21:21] PFlash p Sector 21 Locked Forever (rh) */
    unsigned int S22ROM:1;                  /**< \brief [22:22] PFlash p Sector 22 Locked Forever (rh) */
    unsigned int S23ROM:1;                  /**< \brief [23:23] PFlash p Sector 23 Locked Forever (rh) */
    unsigned int S24ROM:1;                  /**< \brief [24:24] PFlash p Sector 24 Locked Forever (rh) */
    unsigned int S25ROM:1;                  /**< \brief [25:25] PFlash p Sector 25 Locked Forever (rh) */
    unsigned int S26ROM:1;                  /**< \brief [26:26] PFlash p Sector 26 Locked Forever (rh) */
    unsigned int reserved_27:2;             /**< \brief \internal Reserved */
    unsigned int BML:2;                     /**< \brief [30:29] Boot Mode Lock (rh) */
    unsigned int TP:1;                      /**< \brief [31:31] Tuning Protection (rh) */
} Ifx_FLASH_PROCONOTP_Bits;

/** \brief  PFlash Protection Configuration */
typedef struct _Ifx_FLASH_PROCONP_Bits
{
    unsigned int S0L:1;                     /**< \brief [0:0] PFlash p Sector 0 Locked for Write Protection (rh) */
    unsigned int S1L:1;                     /**< \brief [1:1] PFlash p Sector 1 Locked for Write Protection (rh) */
    unsigned int S2L:1;                     /**< \brief [2:2] PFlash p Sector 2 Locked for Write Protection (rh) */
    unsigned int S3L:1;                     /**< \brief [3:3] PFlash p Sector 3 Locked for Write Protection (rh) */
    unsigned int S4L:1;                     /**< \brief [4:4] PFlash p Sector 4 Locked for Write Protection (rh) */
    unsigned int S5L:1;                     /**< \brief [5:5] PFlash p Sector 5 Locked for Write Protection (rh) */
    unsigned int S6L:1;                     /**< \brief [6:6] PFlash p Sector 6 Locked for Write Protection (rh) */
    unsigned int S7L:1;                     /**< \brief [7:7] PFlash p Sector 7 Locked for Write Protection (rh) */
    unsigned int S8L:1;                     /**< \brief [8:8] PFlash p Sector 8 Locked for Write Protection (rh) */
    unsigned int S9L:1;                     /**< \brief [9:9] PFlash p Sector 9 Locked for Write Protection (rh) */
    unsigned int S10L:1;                    /**< \brief [10:10] PFlash p Sector 10 Locked for Write Protection (rh) */
    unsigned int S11L:1;                    /**< \brief [11:11] PFlash p Sector 11 Locked for Write Protection (rh) */
    unsigned int S12L:1;                    /**< \brief [12:12] PFlash p Sector 12 Locked for Write Protection (rh) */
    unsigned int S13L:1;                    /**< \brief [13:13] PFlash p Sector 13 Locked for Write Protection (rh) */
    unsigned int S14L:1;                    /**< \brief [14:14] PFlash p Sector 14 Locked for Write Protection (rh) */
    unsigned int S15L:1;                    /**< \brief [15:15] PFlash p Sector 15 Locked for Write Protection (rh) */
    unsigned int S16L:1;                    /**< \brief [16:16] PFlash p Sector 16 Locked for Write Protection (rh) */
    unsigned int S17L:1;                    /**< \brief [17:17] PFlash p Sector 17 Locked for Write Protection (rh) */
    unsigned int S18L:1;                    /**< \brief [18:18] PFlash p Sector 18 Locked for Write Protection (rh) */
    unsigned int S19L:1;                    /**< \brief [19:19] PFlash p Sector 19 Locked for Write Protection (rh) */
    unsigned int S20L:1;                    /**< \brief [20:20] PFlash p Sector 20 Locked for Write Protection (rh) */
    unsigned int S21L:1;                    /**< \brief [21:21] PFlash p Sector 21 Locked for Write Protection (rh) */
    unsigned int S22L:1;                    /**< \brief [22:22] PFlash p Sector 22 Locked for Write Protection (rh) */
    unsigned int S23L:1;                    /**< \brief [23:23] PFlash p Sector 23 Locked for Write Protection (rh) */
    unsigned int S24L:1;                    /**< \brief [24:24] PFlash p Sector 24 Locked for Write Protection (rh) */
    unsigned int S25L:1;                    /**< \brief [25:25] PFlash p Sector 25 Locked for Write Protection (rh) */
    unsigned int S26L:1;                    /**< \brief [26:26] PFlash p Sector 26 Locked for Write Protection (rh) */
    unsigned int reserved_27:4;             /**< \brief \internal Reserved */
    unsigned int RPRO:1;                    /**< \brief [31:31] Read Protection Configuration (rh) */
} Ifx_FLASH_PROCONP_Bits;

/** \brief  Write-Once Protection Configuration */
typedef struct _Ifx_FLASH_PROCONWOP_Bits
{
    unsigned int S0WOP:1;                   /**< \brief [0:0] PFlash p Sector 0 Configured for Write-Once Protection (rh) */
    unsigned int S1WOP:1;                   /**< \brief [1:1] PFlash p Sector 1 Configured for Write-Once Protection (rh) */
    unsigned int S2WOP:1;                   /**< \brief [2:2] PFlash p Sector 2 Configured for Write-Once Protection (rh) */
    unsigned int S3WOP:1;                   /**< \brief [3:3] PFlash p Sector 3 Configured for Write-Once Protection (rh) */
    unsigned int S4WOP:1;                   /**< \brief [4:4] PFlash p Sector 4 Configured for Write-Once Protection (rh) */
    unsigned int S5WOP:1;                   /**< \brief [5:5] PFlash p Sector 5 Configured for Write-Once Protection (rh) */
    unsigned int S6WOP:1;                   /**< \brief [6:6] PFlash p Sector 6 Configured for Write-Once Protection (rh) */
    unsigned int S7WOP:1;                   /**< \brief [7:7] PFlash p Sector 7 Configured for Write-Once Protection (rh) */
    unsigned int S8WOP:1;                   /**< \brief [8:8] PFlash p Sector 8 Configured for Write-Once Protection (rh) */
    unsigned int S9WOP:1;                   /**< \brief [9:9] PFlash p Sector 9 Configured for Write-Once Protection (rh) */
    unsigned int S10WOP:1;                  /**< \brief [10:10] PFlash p Sector 10 Configured for Write-Once Protection (rh) */
    unsigned int S11WOP:1;                  /**< \brief [11:11] PFlash p Sector 11 Configured for Write-Once Protection (rh) */
    unsigned int S12WOP:1;                  /**< \brief [12:12] PFlash p Sector 12 Configured for Write-Once Protection (rh) */
    unsigned int S13WOP:1;                  /**< \brief [13:13] PFlash p Sector 13 Configured for Write-Once Protection (rh) */
    unsigned int S14WOP:1;                  /**< \brief [14:14] PFlash p Sector 14 Configured for Write-Once Protection (rh) */
    unsigned int S15WOP:1;                  /**< \brief [15:15] PFlash p Sector 15 Configured for Write-Once Protection (rh) */
    unsigned int S16WOP:1;                  /**< \brief [16:16] PFlash p Sector 16 Configured for Write-Once Protection (rh) */
    unsigned int S17WOP:1;                  /**< \brief [17:17] PFlash p Sector 17 Configured for Write-Once Protection (rh) */
    unsigned int S18WOP:1;                  /**< \brief [18:18] PFlash p Sector 18 Configured for Write-Once Protection (rh) */
    unsigned int S19WOP:1;                  /**< \brief [19:19] PFlash p Sector 19 Configured for Write-Once Protection (rh) */
    unsigned int S20WOP:1;                  /**< \brief [20:20] PFlash p Sector 20 Configured for Write-Once Protection (rh) */
    unsigned int S21WOP:1;                  /**< \brief [21:21] PFlash p Sector 21 Configured for Write-Once Protection (rh) */
    unsigned int S22WOP:1;                  /**< \brief [22:22] PFlash p Sector 22 Configured for Write-Once Protection (rh) */
    unsigned int S23WOP:1;                  /**< \brief [23:23] PFlash p Sector 23 Configured for Write-Once Protection (rh) */
    unsigned int S24WOP:1;                  /**< \brief [24:24] PFlash p Sector 24 Configured for Write-Once Protection (rh) */
    unsigned int S25WOP:1;                  /**< \brief [25:25] PFlash p Sector 25 Configured for Write-Once Protection (rh) */
    unsigned int S26WOP:1;                  /**< \brief [26:26] PFlash p Sector 26 Configured for Write-Once Protection (rh) */
    unsigned int reserved_27:4;             /**< \brief \internal Reserved */
    unsigned int DATM:1;                    /**< \brief [31:31] Disable ATM (rh) */
} Ifx_FLASH_PROCONWOP_Bits;

/** \brief  Read Buffer Cfg 0 */
typedef struct _Ifx_FLASH_RDB_CFG0_Bits
{
    unsigned int TAG:6;                     /**< \brief [5:0] Master Tag (rw) */
    unsigned int reserved_6:26;             /**< \brief \internal Reserved */
} Ifx_FLASH_RDB_CFG0_Bits;

/** \brief  Read Buffer Cfg 1 */
typedef struct _Ifx_FLASH_RDB_CFG1_Bits
{
    unsigned int TAG:6;                     /**< \brief [5:0] Master Tag (rw) */
    unsigned int reserved_6:26;             /**< \brief \internal Reserved */
} Ifx_FLASH_RDB_CFG1_Bits;

/** \brief  Read Buffer Cfg 2 */
typedef struct _Ifx_FLASH_RDB_CFG2_Bits
{
    unsigned int TAG:6;                     /**< \brief [5:0] Master Tag (rw) */
    unsigned int reserved_6:26;             /**< \brief \internal Reserved */
} Ifx_FLASH_RDB_CFG2_Bits;

/** \brief  Requested Read Address Register */
typedef struct _Ifx_FLASH_RRAD_Bits
{
    unsigned int reserved_0:3;              /**< \brief \internal Reserved */
    unsigned int ADD:29;                    /**< \brief [31:3] Address (rwh) */
} Ifx_FLASH_RRAD_Bits;

/** \brief  Requested Read Control Register */
typedef struct _Ifx_FLASH_RRCT_Bits
{
    unsigned int STRT:1;                    /**< \brief [0:0] Start Request (rwh) */
    unsigned int STP:1;                     /**< \brief [1:1] Stop (w) */
    unsigned int BUSY:1;                    /**< \brief [2:2] Flash Read Busy (rh) */
    unsigned int DONE:1;                    /**< \brief [3:3] Flash Read Done (rh) */
    unsigned int ERR:1;                     /**< \brief [4:4] Error (rh) */
    unsigned int reserved_5:3;              /**< \brief \internal Reserved */
    unsigned int EOBM:1;                    /**< \brief [8:8] End of Busy Interrupt Mask (rw) */
    unsigned int reserved_9:7;              /**< \brief \internal Reserved */
    unsigned int CNT:16;                    /**< \brief [31:16] Count (rwh) */
} Ifx_FLASH_RRCT_Bits;

/** \brief  Requested Read Data Register 0 */
typedef struct _Ifx_FLASH_RRD0_Bits
{
    unsigned int DATA:32;                   /**< \brief [31:0] Read Data (rh) */
} Ifx_FLASH_RRD0_Bits;

/** \brief  Requested Read Data Register 1 */
typedef struct _Ifx_FLASH_RRD1_Bits
{
    unsigned int DATA:32;                   /**< \brief [31:0] Read Data (rh) */
} Ifx_FLASH_RRD1_Bits;

/** \brief  UBAB Configuration */
typedef struct _Ifx_FLASH_UBAB_CFG_Bits
{
    unsigned int SEL:6;                     /**< \brief [5:0] Select Bit-Errors (rw) */
    unsigned int reserved_6:2;              /**< \brief \internal Reserved */
    unsigned int CLR:1;                     /**< \brief [8:8] Clear (w) */
    unsigned int DIS:1;                     /**< \brief [9:9] Disable (rw) */
    unsigned int reserved_10:22;            /**< \brief \internal Reserved */
} Ifx_FLASH_UBAB_CFG_Bits;

/** \brief  UBAB Status */
typedef struct _Ifx_FLASH_UBAB_STAT_Bits
{
    unsigned int VLD0:1;                    /**< \brief [0:0] Filling Level (rh) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_FLASH_UBAB_STAT_Bits;

/** \brief  UBAB FIFO TOP Entry */
typedef struct _Ifx_FLASH_UBAB_TOP_Bits
{
    unsigned int reserved_0:5;              /**< \brief \internal Reserved */
    unsigned int ADDR:19;                   /**< \brief [23:5] Address (rh) */
    unsigned int ERR:6;                     /**< \brief [29:24] Error Type (rh) */
    unsigned int VLD:1;                     /**< \brief [30:30] Valid (rh) */
    unsigned int CLR:1;                     /**< \brief [31:31] Clear (w) */
} Ifx_FLASH_UBAB_TOP_Bits;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Flash_union
 * \{  */

/** \brief  Access Enable Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_ACCEN0_Bits B;                /**< \brief Bitfield access */
} Ifx_FLASH_ACCEN0;

/** \brief  Access Enable Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_ACCEN1_Bits B;                /**< \brief Bitfield access */
} Ifx_FLASH_ACCEN1;

/** \brief  CBAB Configuration */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_CBAB_CFG_Bits B;              /**< \brief Bitfield access */
} Ifx_FLASH_CBAB_CFG;

/** \brief  CBAB Status */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_CBAB_STAT_Bits B;             /**< \brief Bitfield access */
} Ifx_FLASH_CBAB_STAT;

/** \brief  CBAB FIFO TOP Entry */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_CBAB_TOP_Bits B;              /**< \brief Bitfield access */
} Ifx_FLASH_CBAB_TOP;

/** \brief  FSI Communication Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_COMM0_Bits B;                 /**< \brief Bitfield access */
} Ifx_FLASH_COMM0;

/** \brief  FSI Communication Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_COMM1_Bits B;                 /**< \brief Bitfield access */
} Ifx_FLASH_COMM1;

/** \brief  FSI Communication Register 2 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_COMM2_Bits B;                 /**< \brief Bitfield access */
} Ifx_FLASH_COMM2;

/** \brief  ECC Read Register DF */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_ECCRD_Bits B;                 /**< \brief Bitfield access */
} Ifx_FLASH_ECCRD;

/** \brief  ECC Read Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_ECCRP_Bits B;                 /**< \brief Bitfield access */
} Ifx_FLASH_ECCRP;

/** \brief  ECC Write Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_ECCW_Bits B;                  /**< \brief Bitfield access */
} Ifx_FLASH_ECCW;

/** \brief  Flash Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_FCON_Bits B;                  /**< \brief Bitfield access */
} Ifx_FLASH_FCON;

/** \brief  Flash Protection Control and Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_FPRO_Bits B;                  /**< \brief Bitfield access */
} Ifx_FLASH_FPRO;

/** \brief  Flash Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_FSR_Bits B;                   /**< \brief Bitfield access */
} Ifx_FLASH_FSR;

/** \brief  Flash Module Identification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_ID_Bits B;                    /**< \brief Bitfield access */
} Ifx_FLASH_ID;

/** \brief  Margin Control Register DFlash */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_MARD_Bits B;                  /**< \brief Bitfield access */
} Ifx_FLASH_MARD;

/** \brief  Margin Control Register PFlash */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_MARP_Bits B;                  /**< \brief Bitfield access */
} Ifx_FLASH_MARP;

/** \brief  DFlash Protection Configuration */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_PROCOND_Bits B;               /**< \brief Bitfield access */
} Ifx_FLASH_PROCOND;

/** \brief  Debug Interface Protection Configuration */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_PROCONDBG_Bits B;             /**< \brief Bitfield access */
} Ifx_FLASH_PROCONDBG;

/** \brief  HSM Interface Configuration */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_PROCONHSM_Bits B;             /**< \brief Bitfield access */
} Ifx_FLASH_PROCONHSM;

/** \brief  HSM Code Flash OTP Protection Configuration */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_PROCONHSMCOTP_Bits B;         /**< \brief Bitfield access */
} Ifx_FLASH_PROCONHSMCOTP;

/** \brief  OTP Protection Configuration */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_PROCONOTP_Bits B;             /**< \brief Bitfield access */
} Ifx_FLASH_PROCONOTP;

/** \brief  PFlash Protection Configuration */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_PROCONP_Bits B;               /**< \brief Bitfield access */
} Ifx_FLASH_PROCONP;

/** \brief  Write-Once Protection Configuration */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_PROCONWOP_Bits B;             /**< \brief Bitfield access */
} Ifx_FLASH_PROCONWOP;

/** \brief  Read Buffer Cfg 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_RDB_CFG0_Bits B;              /**< \brief Bitfield access */
} Ifx_FLASH_RDB_CFG0;

/** \brief  Read Buffer Cfg 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_RDB_CFG1_Bits B;              /**< \brief Bitfield access */
} Ifx_FLASH_RDB_CFG1;

/** \brief  Read Buffer Cfg 2 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_RDB_CFG2_Bits B;              /**< \brief Bitfield access */
} Ifx_FLASH_RDB_CFG2;

/** \brief  Requested Read Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_RRAD_Bits B;                  /**< \brief Bitfield access */
} Ifx_FLASH_RRAD;

/** \brief  Requested Read Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_RRCT_Bits B;                  /**< \brief Bitfield access */
} Ifx_FLASH_RRCT;

/** \brief  Requested Read Data Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_RRD0_Bits B;                  /**< \brief Bitfield access */
} Ifx_FLASH_RRD0;

/** \brief  Requested Read Data Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_RRD1_Bits B;                  /**< \brief Bitfield access */
} Ifx_FLASH_RRD1;

/** \brief  UBAB Configuration */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_UBAB_CFG_Bits B;              /**< \brief Bitfield access */
} Ifx_FLASH_UBAB_CFG;

/** \brief  UBAB Status */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_UBAB_STAT_Bits B;             /**< \brief Bitfield access */
} Ifx_FLASH_UBAB_STAT;

/** \brief  UBAB FIFO TOP Entry */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FLASH_UBAB_TOP_Bits B;              /**< \brief Bitfield access */
} Ifx_FLASH_UBAB_TOP;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Flash_struct
 * \{  */
/******************************************************************************/
/** \name Object L1
 * \{  */

/** \brief  Corrected Bits Address Buffer (CBAB) object */
typedef volatile struct _Ifx_FLASH_CBAB
{
    Ifx_FLASH_CBAB_CFG CFG;                 /**< \brief 0, CBAB Configuration */
    Ifx_FLASH_CBAB_STAT STAT;               /**< \brief 4, CBAB Status */
    Ifx_FLASH_CBAB_TOP TOP;                 /**< \brief 8, CBAB FIFO TOP Entry */
} Ifx_FLASH_CBAB;

/** \brief  Read Buffer Configuration object */
typedef volatile struct _Ifx_FLASH_RDB
{
    Ifx_FLASH_RDB_CFG0 CFG0;                /**< \brief 0, Read Buffer Cfg 0 */
    Ifx_FLASH_RDB_CFG1 CFG1;                /**< \brief 4, Read Buffer Cfg 1 */
    Ifx_FLASH_RDB_CFG2 CFG2;                /**< \brief 8, Read Buffer Cfg 2 */
} Ifx_FLASH_RDB;

/** \brief  Uncorrectable Bits Address Buffer (UBAB) object */
typedef volatile struct _Ifx_FLASH_UBAB
{
    Ifx_FLASH_UBAB_CFG CFG;                 /**< \brief 0, UBAB Configuration */
    Ifx_FLASH_UBAB_STAT STAT;               /**< \brief 4, UBAB Status */
    Ifx_FLASH_UBAB_TOP TOP;                 /**< \brief 8, UBAB FIFO TOP Entry */
} Ifx_FLASH_UBAB;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Flash_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \brief  FLASH object. */
typedef volatile struct _Ifx_FLASH
{
    Ifx_FLASH_COMM0 COMM0;                  /**< \brief 0, FSI Communication Register 0 */
    Ifx_FLASH_COMM1 COMM1;                  /**< \brief 4, FSI Communication Register 1 */
    Ifx_FLASH_COMM2 COMM2;                  /**< \brief 8, FSI Communication Register 2 */
    unsigned char reserved_C[4092];         /**< \brief C, \internal Reserved */
    Ifx_FLASH_ID ID;                        /**< \brief 1008, Flash Module Identification Register */
    unsigned char reserved_100C[4];         /**< \brief 100C, \internal Reserved */
    Ifx_FLASH_FSR FSR;                      /**< \brief 1010, Flash Status Register */
    Ifx_FLASH_FCON FCON;                    /**< \brief 1014, Flash Configuration Register */
    unsigned char reserved_1018[4];         /**< \brief 1018, \internal Reserved */
    Ifx_FLASH_FPRO FPRO;                    /**< \brief 101C, Flash Protection Control and Status Register */
    Ifx_FLASH_PROCONP PROCONP[2];           /**< \brief 1020, PFlash Protection Configuration for ports */
    unsigned char reserved_1028[8];         /**< \brief 1028, \internal Reserved */
    Ifx_FLASH_PROCOND PROCOND;              /**< \brief 1030, DFlash Protection Configuration */
    Ifx_FLASH_PROCONHSMCOTP PROCONHSMCOTP;  /**< \brief 1034, HSM Code Flash OTP Protection Configuration */
    Ifx_FLASH_PROCONOTP PROCONOTP[2];       /**< \brief 1038, OTP Protection Configuration for ports */
    unsigned char reserved_1040[8];         /**< \brief 1040, \internal Reserved */
    Ifx_FLASH_PROCONWOP PROCONWOP[2];       /**< \brief 1048, Write-Once Protection Configuration for ports */
    unsigned char reserved_1050[8];         /**< \brief 1050, \internal Reserved */
    Ifx_FLASH_PROCONDBG PROCONDBG;          /**< \brief 1058, Debug Interface Protection Configuration */
    Ifx_FLASH_PROCONHSM PROCONHSM;          /**< \brief 105C, HSM Interface Configuration */
    Ifx_FLASH_RDB RDBCFG[2];                /**< \brief 1060, Read Buffer Configuration for ports */
    unsigned char reserved_1078[24];        /**< \brief 1078, \internal Reserved */
    Ifx_FLASH_ECCW ECCW;                    /**< \brief 1090, ECC Write Register */
    Ifx_FLASH_ECCRP ECCRP[2];               /**< \brief 1094, ECC Read Register for ports */
    unsigned char reserved_109C[8];         /**< \brief 109C, \internal Reserved */
    Ifx_FLASH_ECCRD ECCRD;                  /**< \brief 10A4, ECC Read Register DF */
    Ifx_FLASH_MARP MARP;                    /**< \brief 10A8, Margin Control Register PFlash */
    Ifx_FLASH_MARD MARD;                    /**< \brief 10AC, Margin Control Register DFlash */
    unsigned char reserved_10B0[4];         /**< \brief 10B0, \internal Reserved */
    Ifx_FLASH_CBAB CBAB[2];                 /**< \brief 10B4, Corrected Bits Address Buffer for ports */
    unsigned char reserved_10CC[24];        /**< \brief 10CC, \internal Reserved */
    Ifx_FLASH_UBAB UBAB[2];                 /**< \brief 10E4, Uncorrectable Bits Address Buffer for ports */
    unsigned char reserved_10FC[68];        /**< \brief 10FC, \internal Reserved */
    Ifx_FLASH_RRCT RRCT;                    /**< \brief 1140, Requested Read Control Register */
    Ifx_FLASH_RRD0 RRD0;                    /**< \brief 1144, Requested Read Data Register 0 */
    Ifx_FLASH_RRD1 RRD1;                    /**< \brief 1148, Requested Read Data Register 1 */
    Ifx_FLASH_RRAD RRAD;                    /**< \brief 114C, Requested Read Address Register */
    unsigned char reserved_1150[680];       /**< \brief 1150, \internal Reserved */
    Ifx_FLASH_ACCEN1 ACCEN1;                /**< \brief 13F8, Access Enable Register 1 */
    Ifx_FLASH_ACCEN0 ACCEN0;                /**< \brief 13FC, Access Enable Register 0 */
} Ifx_FLASH;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXFLASH_REGDEF_H */
