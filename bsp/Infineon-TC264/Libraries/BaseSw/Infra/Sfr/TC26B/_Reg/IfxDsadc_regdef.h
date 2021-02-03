/**
 * \file IfxDsadc_regdef.h
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
 * \defgroup IfxLld_Dsadc Dsadc
 * \ingroup IfxLld
 * 
 * \defgroup IfxLld_Dsadc_Bitfields Bitfields
 * \ingroup IfxLld_Dsadc
 * 
 * \defgroup IfxLld_Dsadc_union Union
 * \ingroup IfxLld_Dsadc
 * 
 * \defgroup IfxLld_Dsadc_struct Struct
 * \ingroup IfxLld_Dsadc
 * 
 */
#ifndef IFXDSADC_REGDEF_H
#define IFXDSADC_REGDEF_H 1
/******************************************************************************/
#include "Ifx_TypesReg.h"
/******************************************************************************/
/** \addtogroup IfxLld_Dsadc_Bitfields
 * \{  */

/** \brief  Access Enable Register 0 */
typedef struct _Ifx_DSADC_ACCEN0_Bits
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
} Ifx_DSADC_ACCEN0_Bits;

/** \brief  Access Protection Register */
typedef struct _Ifx_DSADC_ACCPROT_Bits
{
    unsigned int RG00:1;                    /**< \brief [0:0] Register Group 0, Channels 0, 2, 3 (rw) */
    unsigned int RG01:1;                    /**< \brief [1:1] Register Group 1, Channels 0, 2, 3 (rw) */
    unsigned int RG02:1;                    /**< \brief [2:2] Register Group 2, Channels 0, 2, 3 (rw) */
    unsigned int RG03:1;                    /**< \brief [3:3] Register Group 3, Channels 0, 2, 3 (rw) */
    unsigned int RG04:1;                    /**< \brief [4:4] Register Group 4, Channels 0, 2, 3 (rw) */
    unsigned int reserved_5:9;              /**< \brief \internal Reserved */
    unsigned int RG10:1;                    /**< \brief [14:14] Register Group 0/1, General Control (rw) */
    unsigned int RG11:1;                    /**< \brief [15:15] Register Group 0/1, General Control (rw) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_DSADC_ACCPROT_Bits;

/** \brief  Carrier Generator Configuration Register */
typedef struct _Ifx_DSADC_CGCFG_Bits
{
    unsigned int CGMOD:2;                   /**< \brief [1:0] Carrier Generator Operating Mode (rw) */
    unsigned int BREV:1;                    /**< \brief [2:2] Bit-Reverse PWM Generation (rw) */
    unsigned int SIGPOL:1;                  /**< \brief [3:3] Signal Polarity (rw) */
    unsigned int DIVCG:4;                   /**< \brief [7:4] Divider Factor for the PWM Pattern Signal Generator (rw) */
    unsigned int reserved_8:7;              /**< \brief \internal Reserved */
    unsigned int RUN:1;                     /**< \brief [15:15] Run Indicator (rh) */
    unsigned int BITCOUNT:5;                /**< \brief [20:16] Bit Counter (rh) */
    unsigned int reserved_21:3;             /**< \brief \internal Reserved */
    unsigned int STEPCOUNT:4;               /**< \brief [27:24] Step Counter (rh) */
    unsigned int STEPS:1;                   /**< \brief [28:28] Step Counter Sign (rh) */
    unsigned int STEPD:1;                   /**< \brief [29:29] Step Counter Direction (rh) */
    unsigned int SGNCG:1;                   /**< \brief [30:30] Sign Signal from Carrier Generator (rh) */
    unsigned int reserved_31:1;             /**< \brief \internal Reserved */
} Ifx_DSADC_CGCFG_Bits;

/** \brief  Boundary Select Register */
typedef struct _Ifx_DSADC_CH_BOUNDSEL_Bits
{
    unsigned int BOUNDARYL:16;              /**< \brief [15:0] Lower Boundary Value for Limit Checking (rw) */
    unsigned int BOUNDARYU:16;              /**< \brief [31:16] Upper Boundary Value for Limit Checking (rw) */
} Ifx_DSADC_CH_BOUNDSEL_Bits;

/** \brief  Carrier Generator Synchronization Register */
typedef struct _Ifx_DSADC_CH_CGSYNC_Bits
{
    unsigned int SDCOUNT:8;                 /**< \brief [7:0] Sign Delay Counter (rh) */
    unsigned int SDCAP:8;                   /**< \brief [15:8] Sign Delay Capture Value (rh) */
    unsigned int SDPOS:8;                   /**< \brief [23:16] Sign Delay Value for Positive Halfwave (rw) */
    unsigned int SDNEG:8;                   /**< \brief [31:24] Sign Delay Value for Negative Halfwave (rw) */
} Ifx_DSADC_CH_CGSYNC_Bits;

/** \brief  Demodulator Input Configuration Register */
typedef struct _Ifx_DSADC_CH_DICFG_Bits
{
    unsigned int DSRC:4;                    /**< \brief [3:0] Input Data Source Select (rw) */
    unsigned int reserved_4:3;              /**< \brief \internal Reserved */
    unsigned int DSWC:1;                    /**< \brief [7:7] Write Control for Data Selection (w) */
    unsigned int ITRMODE:2;                 /**< \brief [9:8] Integrator Trigger Mode (rw) */
    unsigned int TSTRMODE:2;                /**< \brief [11:10] Timestamp Trigger Mode (rw) */
    unsigned int TRSEL:3;                   /**< \brief [14:12] Trigger Select (rw) */
    unsigned int TRWC:1;                    /**< \brief [15:15] Write Control for Trigger Parameters (w) */
    unsigned int CSRC:4;                    /**< \brief [19:16] Sample Clock Source Select (rw) */
    unsigned int STROBE:4;                  /**< \brief [23:20] Data Strobe Generation Mode (rw) */
    unsigned int reserved_24:7;             /**< \brief \internal Reserved */
    unsigned int SCWC:1;                    /**< \brief [31:31] Write Control for Strobe/Clock Selection (w) */
} Ifx_DSADC_CH_DICFG_Bits;

/** \brief  Filter Configuration Register, Auxiliary Filter */
typedef struct _Ifx_DSADC_CH_FCFGA_Bits
{
    unsigned int CFADF:8;                   /**< \brief [7:0] CIC Filter (Auxiliary) Decimation Factor (rw) */
    unsigned int CFAC:2;                    /**< \brief [9:8] CIC Filter (Auxiliary) Configuration (rw) */
    unsigned int SRGA:2;                    /**< \brief [11:10] Service Request Generation Auxiliary Filter (rw) */
    unsigned int ESEL:2;                    /**< \brief [13:12] Event Select (rw) */
    unsigned int EGT:1;                     /**< \brief [14:14] Event Gating (rw) */
    unsigned int reserved_15:1;             /**< \brief \internal Reserved */
    unsigned int AFSC:2;                    /**< \brief [17:16] Auxiliary Filter Shift Control (rw) */
    unsigned int reserved_18:6;             /**< \brief \internal Reserved */
    unsigned int CFADCNT:8;                 /**< \brief [31:24] CIC Filter (Auxiliary) Decimation Counter (rh) */
} Ifx_DSADC_CH_FCFGA_Bits;

/** \brief  Filter Configuration Register, Main CIC Filter */
typedef struct _Ifx_DSADC_CH_FCFGC_Bits
{
    unsigned int CFMDF:8;                   /**< \brief [7:0] CIC Filter (Main Chain) Decimation Factor (rw) */
    unsigned int CFMC:2;                    /**< \brief [9:8] CIC Filter (Main Chain) Configuration (rw) */
    unsigned int CFEN:1;                    /**< \brief [10:10] CIC Filter Enable (rw) */
    unsigned int reserved_11:1;             /**< \brief \internal Reserved */
    unsigned int MFSC:2;                    /**< \brief [13:12] Main Filter Shift Control (rw) */
    unsigned int SRGM:2;                    /**< \brief [15:14] Service Request Generation Main Chain (rw) */
    unsigned int CFMSV:8;                   /**< \brief [23:16] CIC Filter (Main Chain) Start Value (rw) */
    unsigned int CFMDCNT:8;                 /**< \brief [31:24] CIC Filter (Main Chain) Decimation Counter (rh) */
} Ifx_DSADC_CH_FCFGC_Bits;

/** \brief  Filter Configuration Register, Main Filter Chain */
typedef struct _Ifx_DSADC_CH_FCFGM_Bits
{
    unsigned int FIR0EN:1;                  /**< \brief [0:0] FIR Filter 0 Enable (rw) */
    unsigned int FIR1EN:1;                  /**< \brief [1:1] FIR Filter 1 Enable (rw) */
    unsigned int OCEN:1;                    /**< \brief [2:2] Offset Compensation Filter Enable (rw) */
    unsigned int DSH:2;                     /**< \brief [4:3] Data Shift Control (rw) */
    unsigned int FSH:1;                     /**< \brief [5:5] FIR Shift Control (rw) */
    unsigned int reserved_6:26;             /**< \brief \internal Reserved */
} Ifx_DSADC_CH_FCFGM_Bits;

/** \brief  Initial Channel Config. Reg. 0 */
typedef struct _Ifx_DSADC_CH_ICCFG_Bits
{
    unsigned int DI0:1;                     /**< \brief [0:0] Dithering Function Enable (rw) */
    unsigned int DI1:1;                     /**< \brief [1:1] Dithering Function Enable (rw) */
    unsigned int reserved_2:2;              /**< \brief \internal Reserved */
    unsigned int IREN:1;                    /**< \brief [4:4] Integrator Reset Enable (rw) */
    unsigned int reserved_5:3;              /**< \brief \internal Reserved */
    unsigned int TWINSP:6;                  /**< \brief [13:8] Setup Parameters for this Twin Modulator (rw) */
    unsigned int reserved_14:17;            /**< \brief \internal Reserved */
    unsigned int WREN:1;                    /**< \brief [31:31] Write Enable (rw) */
} Ifx_DSADC_CH_ICCFG_Bits;

/** \brief  Integration Window Control Register */
typedef struct _Ifx_DSADC_CH_IWCTR_Bits
{
    unsigned int NVALCNT:6;                 /**< \brief [5:0] Number of Values Counted (rh) */
    unsigned int reserved_6:1;              /**< \brief \internal Reserved */
    unsigned int INTEN:1;                   /**< \brief [7:7] Integration Enable (rh) */
    unsigned int REPCNT:4;                  /**< \brief [11:8] Integration Cycle Counter (rh) */
    unsigned int REPVAL:4;                  /**< \brief [15:12] Number of Integration Cycles (rw) */
    unsigned int NVALDIS:6;                 /**< \brief [21:16] Number of Values Discarded (rw) */
    unsigned int reserved_22:1;             /**< \brief \internal Reserved */
    unsigned int IWS:1;                     /**< \brief [23:23] Integration Window Size (rw) */
    unsigned int NVALINT:6;                 /**< \brief [29:24] Number of Values Integrated (rw) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_DSADC_CH_IWCTR_Bits;

/** \brief  Modulator Configuration Register */
typedef struct _Ifx_DSADC_CH_MODCFG_Bits
{
    unsigned int INCFGP:2;                  /**< \brief [1:0] Configuration of Positive Input Line (rw) */
    unsigned int INCFGN:2;                  /**< \brief [3:2] Configuration of Negative Input Line (rw) */
    unsigned int GAINSEL:4;                 /**< \brief [7:4] Gain Select of Analog Input Path (rw) */
    unsigned int INSEL:2;                   /**< \brief [9:8] Input Pin Selection (rw) */
    unsigned int INMUX:2;                   /**< \brief [11:10] Input Multiplexer Setting (rh) */
    unsigned int INMODE:2;                  /**< \brief [13:12] Input Multiplexer Control Mode (rw) */
    unsigned int INMAC:1;                   /**< \brief [14:14] Input Multiplexer Action Control (rw) */
    unsigned int INCWC:1;                   /**< \brief [15:15] Write Control for Input Parameters (w) */
    unsigned int DIVM:4;                    /**< \brief [19:16] Divider Factor for Modulator Clock (rw) */
    unsigned int reserved_20:3;             /**< \brief \internal Reserved */
    unsigned int DWC:1;                     /**< \brief [23:23] Write Control for Divider Factor (w) */
    unsigned int CMVS:2;                    /**< \brief [25:24] Common Mode Voltage Selection (rw) */
    unsigned int MCFG:2;                    /**< \brief [27:26] Modulator Configuration (rw) */
    unsigned int GCEN:1;                    /**< \brief [28:28] Gain Calibration Enable (rw) */
    unsigned int APC:1;                     /**< \brief [29:29] Automatic Power Control (rw) */
    unsigned int reserved_30:1;             /**< \brief \internal Reserved */
    unsigned int MWC:1;                     /**< \brief [31:31] Write Control for Mode Selection (w) */
} Ifx_DSADC_CH_MODCFG_Bits;

/** \brief  Offset Register Main Filter */
typedef struct _Ifx_DSADC_CH_OFFM_Bits
{
    unsigned int OFFSET:16;                 /**< \brief [15:0] Offset Value (rw) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_DSADC_CH_OFFM_Bits;

/** \brief  Rectification Configuration Register */
typedef struct _Ifx_DSADC_CH_RECTCFG_Bits
{
    unsigned int RFEN:1;                    /**< \brief [0:0] Rectification Enable (rw) */
    unsigned int reserved_1:3;              /**< \brief \internal Reserved */
    unsigned int SSRC:2;                    /**< \brief [5:4] Sign Source (rw) */
    unsigned int reserved_6:9;              /**< \brief \internal Reserved */
    unsigned int SDCVAL:1;                  /**< \brief [15:15] Sign Delay Capture Valid Flag (rh) */
    unsigned int reserved_16:14;            /**< \brief \internal Reserved */
    unsigned int SGNCS:1;                   /**< \brief [30:30] Selected Carrier Sign Signal (rh) */
    unsigned int SGND:1;                    /**< \brief [31:31] Sign Signal Delayed (rh) */
} Ifx_DSADC_CH_RECTCFG_Bits;

/** \brief  Result Register Auxiliary Filter */
typedef struct _Ifx_DSADC_CH_RESA_Bits
{
    unsigned int RESULT:16;                 /**< \brief [15:0] Result of most recent conversion (rh) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_DSADC_CH_RESA_Bits;

/** \brief  Result Register Main Filter */
typedef struct _Ifx_DSADC_CH_RESM_Bits
{
    unsigned int RESULT:16;                 /**< \brief [15:0] Result of most recent conversion (rh) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_DSADC_CH_RESM_Bits;

/** \brief  Time-Stamp Register */
typedef struct _Ifx_DSADC_CH_TSTMP_Bits
{
    unsigned int RESULT:16;                 /**< \brief [15:0] Result of most recent conversion (rh) */
    unsigned int CFMDCNT:8;                 /**< \brief [23:16] CIC Filter (Main Chain) Decimation Counter (rh) */
    unsigned int NVALCNT:6;                 /**< \brief [29:24] Number of Values Counted (rh) */
    unsigned int TSVAL:1;                   /**< \brief [30:30] Timestamp Valid (rh) */
    unsigned int TSSR:1;                    /**< \brief [31:31] Timestamp Service Request (rw) */
} Ifx_DSADC_CH_TSTMP_Bits;

/** \brief  Clock Control Register */
typedef struct _Ifx_DSADC_CLC_Bits
{
    unsigned int DISR:1;                    /**< \brief [0:0] Module Disable Request Bit (rw) */
    unsigned int DISS:1;                    /**< \brief [1:1] Module Disable Status Bit (r) */
    unsigned int reserved_2:1;              /**< \brief \internal Reserved */
    unsigned int EDIS:1;                    /**< \brief [3:3] Sleep Mode Enable Control (rw) */
    unsigned int reserved_4:28;             /**< \brief \internal Reserved */
} Ifx_DSADC_CLC_Bits;

/** \brief  Event Flag Register */
typedef struct _Ifx_DSADC_EVFLAG_Bits
{
    unsigned int RESEV0:1;                  /**< \brief [0:0] Result Event (rwh) */
    unsigned int reserved_1:1;              /**< \brief \internal Reserved */
    unsigned int RESEV2:1;                  /**< \brief [2:2] Result Event (rwh) */
    unsigned int RESEV3:1;                  /**< \brief [3:3] Result Event (rwh) */
    unsigned int reserved_4:12;             /**< \brief \internal Reserved */
    unsigned int ALEV0:1;                   /**< \brief [16:16] Alarm Event (rwh) */
    unsigned int reserved_17:1;             /**< \brief \internal Reserved */
    unsigned int ALEV2:1;                   /**< \brief [18:18] Alarm Event (rwh) */
    unsigned int ALEV3:1;                   /**< \brief [19:19] Alarm Event (rwh) */
    unsigned int reserved_20:12;            /**< \brief \internal Reserved */
} Ifx_DSADC_EVFLAG_Bits;

/** \brief  Event Flag Clear Register */
typedef struct _Ifx_DSADC_EVFLAGCLR_Bits
{
    unsigned int RESEC0:1;                  /**< \brief [0:0] Result Event Clear (w) */
    unsigned int reserved_1:1;              /**< \brief \internal Reserved */
    unsigned int RESEC2:1;                  /**< \brief [2:2] Result Event Clear (w) */
    unsigned int RESEC3:1;                  /**< \brief [3:3] Result Event Clear (w) */
    unsigned int reserved_4:12;             /**< \brief \internal Reserved */
    unsigned int ALEC0:1;                   /**< \brief [16:16] Alarm Event Clear (w) */
    unsigned int reserved_17:1;             /**< \brief \internal Reserved */
    unsigned int ALEC2:1;                   /**< \brief [18:18] Alarm Event Clear (w) */
    unsigned int ALEC3:1;                   /**< \brief [19:19] Alarm Event Clear (w) */
    unsigned int reserved_20:12;            /**< \brief \internal Reserved */
} Ifx_DSADC_EVFLAGCLR_Bits;

/** \brief  Global Configuration Register */
typedef struct _Ifx_DSADC_GLOBCFG_Bits
{
    unsigned int MCSEL:3;                   /**< \brief [2:0] Modulator Clock Select (rw) */
    unsigned int reserved_3:8;              /**< \brief \internal Reserved */
    unsigned int IRM0:1;                    /**< \brief [11:11] Internal Resistance Measurement Control (rw) */
    unsigned int reserved_12:4;             /**< \brief \internal Reserved */
    unsigned int IBSEL:4;                   /**< \brief [19:16] Bias Current Select (rw) */
    unsigned int LOSUP:1;                   /**< \brief [20:20] Low Power Supply Voltage Select (rw) */
    unsigned int reserved_21:1;             /**< \brief \internal Reserved */
    unsigned int ICT:1;                     /**< \brief [22:22] Internal Channel Test (rw) */
    unsigned int PSWC:1;                    /**< \brief [23:23] Write Control for Power Supply Parameters (w) */
    unsigned int reserved_24:8;             /**< \brief \internal Reserved */
} Ifx_DSADC_GLOBCFG_Bits;

/** \brief  Global Run Control Register */
typedef struct _Ifx_DSADC_GLOBRC_Bits
{
    unsigned int CH0RUN:1;                  /**< \brief [0:0] Channel 0 Run Control (rw) */
    unsigned int reserved_1:1;              /**< \brief \internal Reserved */
    unsigned int CH2RUN:1;                  /**< \brief [2:2] Channel 2 Run Control (rw) */
    unsigned int CH3RUN:1;                  /**< \brief [3:3] Channel 3 Run Control (rw) */
    unsigned int reserved_4:12;             /**< \brief \internal Reserved */
    unsigned int M0RUN:1;                   /**< \brief [16:16] Modulator 0 Run Control (rw) */
    unsigned int reserved_17:1;             /**< \brief \internal Reserved */
    unsigned int M2RUN:1;                   /**< \brief [18:18] Modulator 2 Run Control (rw) */
    unsigned int M3RUN:1;                   /**< \brief [19:19] Modulator 3 Run Control (rw) */
    unsigned int reserved_20:12;            /**< \brief \internal Reserved */
} Ifx_DSADC_GLOBRC_Bits;

/** \brief  Common Mode Hold Voltage Register 0 */
typedef struct _Ifx_DSADC_GLOBVCMH0_Bits
{
    unsigned int IN0PVC0:1;                 /**< \brief [0:0] Voltage Control of Positive Inputs 0-1 of CH0 (rw) */
    unsigned int IN0PVC1:1;                 /**< \brief [1:1] Voltage Control of Positive Inputs 0-1 of CH0 (rw) */
    unsigned int reserved_2:2;              /**< \brief \internal Reserved */
    unsigned int IN0NVC0:1;                 /**< \brief [4:4] Voltage Control of Negative Inputs 0-1 of CH0 (rw) */
    unsigned int IN0NVC1:1;                 /**< \brief [5:5] Voltage Control of Negative Inputs 0-1 of CH0 (rw) */
    unsigned int reserved_6:10;             /**< \brief \internal Reserved */
    unsigned int IN2PVC0:1;                 /**< \brief [16:16] Voltage Control of Positive Input 0 of CH2 (rw) */
    unsigned int reserved_17:3;             /**< \brief \internal Reserved */
    unsigned int IN2NVC0:1;                 /**< \brief [20:20] Voltage Control of Negative Input 0 of CH2 (rw) */
    unsigned int reserved_21:3;             /**< \brief \internal Reserved */
    unsigned int IN3PVC0:1;                 /**< \brief [24:24] Voltage Control of Positive Inputs 0-3 of CH3 (rw) */
    unsigned int IN3PVC1:1;                 /**< \brief [25:25] Voltage Control of Positive Inputs 0-3 of CH3 (rw) */
    unsigned int IN3PVC2:1;                 /**< \brief [26:26] Voltage Control of Positive Inputs 0-3 of CH3 (rw) */
    unsigned int IN3PVC3:1;                 /**< \brief [27:27] Voltage Control of Positive Inputs 0-3 of CH3 (rw) */
    unsigned int IN3NVC0:1;                 /**< \brief [28:28] Voltage Control of Negative Inputs 0-3 of CH3 (rw) */
    unsigned int IN3NVC1:1;                 /**< \brief [29:29] Voltage Control of Negative Inputs 0-3 of CH3 (rw) */
    unsigned int IN3NVC2:1;                 /**< \brief [30:30] Voltage Control of Negative Inputs 0-3 of CH3 (rw) */
    unsigned int IN3NVC3:1;                 /**< \brief [31:31] Voltage Control of Negative Inputs 0-3 of CH3 (rw) */
} Ifx_DSADC_GLOBVCMH0_Bits;

/** \brief  Common Mode Hold Voltage Register 2 */
typedef struct _Ifx_DSADC_GLOBVCMH2_Bits
{
    unsigned int reserved_0:29;             /**< \brief \internal Reserved */
    unsigned int VHON:1;                    /**< \brief [29:29] Common Mode Hold Voltage On (rw) */
    unsigned int VCMHS:2;                   /**< \brief [31:30] Common Mode Hold Voltage Selection (rw) */
} Ifx_DSADC_GLOBVCMH2_Bits;

/** \brief  Module Identification Register */
typedef struct _Ifx_DSADC_ID_Bits
{
    unsigned int MODREV:8;                  /**< \brief [7:0] Module Revision Number (r) */
    unsigned int MODTYPE:8;                 /**< \brief [15:8] Module Type (r) */
    unsigned int MODNUMBER:16;              /**< \brief [31:16] Module Number Value (r) */
} Ifx_DSADC_ID_Bits;

/** \brief  Initial Global Config. Register */
typedef struct _Ifx_DSADC_IGCFG_Bits
{
    unsigned int DITRIM:3;                  /**< \brief [2:0] Trimming Value for the Dithering Function (rw) */
    unsigned int reserved_3:13;             /**< \brief \internal Reserved */
    unsigned int GLOBSP:10;                 /**< \brief [25:16] Global Setup Parameters for the MultiADC (rw) */
    unsigned int reserved_26:5;             /**< \brief \internal Reserved */
    unsigned int WREN:1;                    /**< \brief [31:31] Write Enable (rw) */
} Ifx_DSADC_IGCFG_Bits;

/** \brief  Kernel Reset Register 0 */
typedef struct _Ifx_DSADC_KRST0_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int RSTSTAT:1;                 /**< \brief [1:1] Kernel Reset Status (rh) */
    unsigned int reserved_2:30;             /**< \brief \internal Reserved */
} Ifx_DSADC_KRST0_Bits;

/** \brief  Kernel Reset Register 1 */
typedef struct _Ifx_DSADC_KRST1_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_DSADC_KRST1_Bits;

/** \brief  Kernel Reset Status Clear Register */
typedef struct _Ifx_DSADC_KRSTCLR_Bits
{
    unsigned int CLR:1;                     /**< \brief [0:0] Kernel Reset Status Clear (w) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_DSADC_KRSTCLR_Bits;

/** \brief  OCDS Control and Status Register */
typedef struct _Ifx_DSADC_OCS_Bits
{
    unsigned int reserved_0:24;             /**< \brief \internal Reserved */
    unsigned int SUS:4;                     /**< \brief [27:24] OCDS Suspend Control (rw) */
    unsigned int SUS_P:1;                   /**< \brief [28:28] SUS Write Protection (w) */
    unsigned int SUSSTA:1;                  /**< \brief [29:29] Suspend State (rh) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_DSADC_OCS_Bits;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Dsadc_union
 * \{  */

/** \brief  Access Enable Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DSADC_ACCEN0_Bits B;                /**< \brief Bitfield access */
} Ifx_DSADC_ACCEN0;

/** \brief  Access Protection Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DSADC_ACCPROT_Bits B;               /**< \brief Bitfield access */
} Ifx_DSADC_ACCPROT;

/** \brief  Carrier Generator Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DSADC_CGCFG_Bits B;                 /**< \brief Bitfield access */
} Ifx_DSADC_CGCFG;

/** \brief  Boundary Select Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DSADC_CH_BOUNDSEL_Bits B;           /**< \brief Bitfield access */
} Ifx_DSADC_CH_BOUNDSEL;

/** \brief  Carrier Generator Synchronization Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DSADC_CH_CGSYNC_Bits B;             /**< \brief Bitfield access */
} Ifx_DSADC_CH_CGSYNC;

/** \brief  Demodulator Input Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DSADC_CH_DICFG_Bits B;              /**< \brief Bitfield access */
} Ifx_DSADC_CH_DICFG;

/** \brief  Filter Configuration Register, Auxiliary Filter */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DSADC_CH_FCFGA_Bits B;              /**< \brief Bitfield access */
} Ifx_DSADC_CH_FCFGA;

/** \brief  Filter Configuration Register, Main CIC Filter */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DSADC_CH_FCFGC_Bits B;              /**< \brief Bitfield access */
} Ifx_DSADC_CH_FCFGC;

/** \brief  Filter Configuration Register, Main Filter Chain */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DSADC_CH_FCFGM_Bits B;              /**< \brief Bitfield access */
} Ifx_DSADC_CH_FCFGM;

/** \brief  Initial Channel Config. Reg. 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DSADC_CH_ICCFG_Bits B;              /**< \brief Bitfield access */
} Ifx_DSADC_CH_ICCFG;

/** \brief  Integration Window Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DSADC_CH_IWCTR_Bits B;              /**< \brief Bitfield access */
} Ifx_DSADC_CH_IWCTR;

/** \brief  Modulator Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DSADC_CH_MODCFG_Bits B;             /**< \brief Bitfield access */
} Ifx_DSADC_CH_MODCFG;

/** \brief  Offset Register Main Filter */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DSADC_CH_OFFM_Bits B;               /**< \brief Bitfield access */
} Ifx_DSADC_CH_OFFM;

/** \brief  Rectification Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DSADC_CH_RECTCFG_Bits B;            /**< \brief Bitfield access */
} Ifx_DSADC_CH_RECTCFG;

/** \brief  Result Register Auxiliary Filter */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DSADC_CH_RESA_Bits B;               /**< \brief Bitfield access */
} Ifx_DSADC_CH_RESA;

/** \brief  Result Register Main Filter */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DSADC_CH_RESM_Bits B;               /**< \brief Bitfield access */
} Ifx_DSADC_CH_RESM;

/** \brief  Time-Stamp Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DSADC_CH_TSTMP_Bits B;              /**< \brief Bitfield access */
} Ifx_DSADC_CH_TSTMP;

/** \brief  Clock Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DSADC_CLC_Bits B;                   /**< \brief Bitfield access */
} Ifx_DSADC_CLC;

/** \brief  Event Flag Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DSADC_EVFLAG_Bits B;                /**< \brief Bitfield access */
} Ifx_DSADC_EVFLAG;

/** \brief  Event Flag Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DSADC_EVFLAGCLR_Bits B;             /**< \brief Bitfield access */
} Ifx_DSADC_EVFLAGCLR;

/** \brief  Global Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DSADC_GLOBCFG_Bits B;               /**< \brief Bitfield access */
} Ifx_DSADC_GLOBCFG;

/** \brief  Global Run Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DSADC_GLOBRC_Bits B;                /**< \brief Bitfield access */
} Ifx_DSADC_GLOBRC;

/** \brief  Common Mode Hold Voltage Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DSADC_GLOBVCMH0_Bits B;             /**< \brief Bitfield access */
} Ifx_DSADC_GLOBVCMH0;

/** \brief  Common Mode Hold Voltage Register 2 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DSADC_GLOBVCMH2_Bits B;             /**< \brief Bitfield access */
} Ifx_DSADC_GLOBVCMH2;

/** \brief  Module Identification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DSADC_ID_Bits B;                    /**< \brief Bitfield access */
} Ifx_DSADC_ID;

/** \brief  Initial Global Config. Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DSADC_IGCFG_Bits B;                 /**< \brief Bitfield access */
} Ifx_DSADC_IGCFG;

/** \brief  Kernel Reset Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DSADC_KRST0_Bits B;                 /**< \brief Bitfield access */
} Ifx_DSADC_KRST0;

/** \brief  Kernel Reset Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DSADC_KRST1_Bits B;                 /**< \brief Bitfield access */
} Ifx_DSADC_KRST1;

/** \brief  Kernel Reset Status Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DSADC_KRSTCLR_Bits B;               /**< \brief Bitfield access */
} Ifx_DSADC_KRSTCLR;

/** \brief  OCDS Control and Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DSADC_OCS_Bits B;                   /**< \brief Bitfield access */
} Ifx_DSADC_OCS;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Dsadc_struct
 * \{  */
/******************************************************************************/
/** \name Object L1
 * \{  */

/** \brief  Channel objects */
typedef volatile struct _Ifx_DSADC_CH
{
    Ifx_DSADC_CH_MODCFG MODCFG;             /**< \brief 0, Modulator Configuration Register */
    unsigned char reserved_4[4];            /**< \brief 4, \internal Reserved */
    Ifx_DSADC_CH_DICFG DICFG;               /**< \brief 8, Demodulator Input Configuration Register */
    unsigned char reserved_C[4];            /**< \brief C, \internal Reserved */
    Ifx_DSADC_CH_FCFGM FCFGM;               /**< \brief 10, Filter Configuration Register, Main Filter Chain */
    Ifx_DSADC_CH_FCFGC FCFGC;               /**< \brief 14, Filter Configuration Register, Main CIC Filter */
    Ifx_DSADC_CH_FCFGA FCFGA;               /**< \brief 18, Filter Configuration Register, Auxiliary Filter */
    unsigned char reserved_1C[4];           /**< \brief 1C, \internal Reserved */
    Ifx_DSADC_CH_IWCTR IWCTR;               /**< \brief 20, Integration Window Control Register */
    unsigned char reserved_24[4];           /**< \brief 24, \internal Reserved */
    Ifx_DSADC_CH_BOUNDSEL BOUNDSEL;         /**< \brief 28, Boundary Select Register */
    unsigned char reserved_2C[4];           /**< \brief 2C, \internal Reserved */
    Ifx_DSADC_CH_RESM RESM;                 /**< \brief 30, Result Register Main Filter */
    unsigned char reserved_34[4];           /**< \brief 34, \internal Reserved */
    Ifx_DSADC_CH_OFFM OFFM;                 /**< \brief 38, Offset Register Main Filter */
    unsigned char reserved_3C[4];           /**< \brief 3C, \internal Reserved */
    Ifx_DSADC_CH_RESA RESA;                 /**< \brief 40, Result Register Auxiliary Filter */
    unsigned char reserved_44[12];          /**< \brief 44, \internal Reserved */
    Ifx_DSADC_CH_TSTMP TSTMP;               /**< \brief 50, Time-Stamp Register */
    unsigned char reserved_54[76];          /**< \brief 54, \internal Reserved */
    Ifx_DSADC_CH_CGSYNC CGSYNC;             /**< \brief A0, Carrier Generator Synchronization Register */
    unsigned char reserved_A4[4];           /**< \brief A4, \internal Reserved */
    Ifx_DSADC_CH_RECTCFG RECTCFG;           /**< \brief A8, Rectification Configuration Register */
    unsigned char reserved_AC[36];          /**< \brief AC, \internal Reserved */
    Ifx_DSADC_CH_ICCFG ICCFG;               /**< \brief D0, Initial Channel Config. Reg. 0 */
    unsigned char reserved_D4[44];          /**< \brief D4, \internal Reserved */
} Ifx_DSADC_CH;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Dsadc_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \brief  DSADC object */
typedef volatile struct _Ifx_DSADC
{
    Ifx_DSADC_CLC CLC;                      /**< \brief 0, Clock Control Register */
    unsigned char reserved_4[4];            /**< \brief 4, \internal Reserved */
    Ifx_DSADC_ID ID;                        /**< \brief 8, Module Identification Register */
    unsigned char reserved_C[28];           /**< \brief C, \internal Reserved */
    Ifx_DSADC_OCS OCS;                      /**< \brief 28, OCDS Control and Status Register */
    Ifx_DSADC_KRSTCLR KRSTCLR;              /**< \brief 2C, Kernel Reset Status Clear Register */
    Ifx_DSADC_KRST1 KRST1;                  /**< \brief 30, Kernel Reset Register 1 */
    Ifx_DSADC_KRST0 KRST0;                  /**< \brief 34, Kernel Reset Register 0 */
    unsigned char reserved_38[4];           /**< \brief 38, \internal Reserved */
    Ifx_DSADC_ACCEN0 ACCEN0;                /**< \brief 3C, Access Enable Register 0 */
    unsigned char reserved_40[64];          /**< \brief 40, \internal Reserved */
    Ifx_DSADC_GLOBCFG GLOBCFG;              /**< \brief 80, Global Configuration Register */
    unsigned char reserved_84[4];           /**< \brief 84, \internal Reserved */
    Ifx_DSADC_GLOBRC GLOBRC;                /**< \brief 88, Global Run Control Register */
    unsigned char reserved_8C[4];           /**< \brief 8C, \internal Reserved */
    Ifx_DSADC_ACCPROT ACCPROT;              /**< \brief 90, Access Protection Register */
    unsigned char reserved_94[12];          /**< \brief 94, \internal Reserved */
    Ifx_DSADC_CGCFG CGCFG;                  /**< \brief A0, Carrier Generator Configuration Register */
    unsigned char reserved_A4[12];          /**< \brief A4, \internal Reserved */
    Ifx_DSADC_GLOBVCMH0 GLOBVCMH0;          /**< \brief B0, Common Mode Hold Voltage Register 0 */
    unsigned char reserved_B4[4];           /**< \brief B4, \internal Reserved */
    Ifx_DSADC_GLOBVCMH2 GLOBVCMH2;          /**< \brief B8, Common Mode Hold Voltage Register 2 */
    unsigned char reserved_BC[20];          /**< \brief BC, \internal Reserved */
    Ifx_DSADC_IGCFG IGCFG;                  /**< \brief D0, Initial Global Config. Register */
    unsigned char reserved_D4[12];          /**< \brief D4, \internal Reserved */
    Ifx_DSADC_EVFLAG EVFLAG;                /**< \brief E0, Event Flag Register */
    Ifx_DSADC_EVFLAGCLR EVFLAGCLR;          /**< \brief E4, Event Flag Clear Register */
    unsigned char reserved_E8[24];          /**< \brief E8, \internal Reserved */
    Ifx_DSADC_CH CH[4];                     /**< \brief 100, Channel objects */
    unsigned char reserved_500[2816];       /**< \brief 500, \internal Reserved */
} Ifx_DSADC;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXDSADC_REGDEF_H */
