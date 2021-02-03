/**
 * \file IfxSrc_regdef.h
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
 * \defgroup IfxLld_Src Src
 * \ingroup IfxLld
 * 
 * \defgroup IfxLld_Src_Bitfields Bitfields
 * \ingroup IfxLld_Src
 * 
 * \defgroup IfxLld_Src_union Union
 * \ingroup IfxLld_Src
 * 
 * \defgroup IfxLld_Src_struct Struct
 * \ingroup IfxLld_Src
 * 
 */
#ifndef IFXSRC_REGDEF_H
#define IFXSRC_REGDEF_H 1
/******************************************************************************/
#include "Ifx_TypesReg.h"
/******************************************************************************/
/** \addtogroup IfxLld_Src_Bitfields
 * \{  */

/** \brief  Service request register */
typedef struct _Ifx_SRC_SRCR_Bits
{
    unsigned int SRPN:8;                    /**< \brief [7:0] Service Request Priority Number (rw) */
    unsigned int reserved_8:2;              /**< \brief \internal Reserved */
    unsigned int SRE:1;                     /**< \brief [10:10] Service Request Enable (rw) */
    unsigned int TOS:2;                     /**< \brief [12:11] Type of Service Control (rw) */
    unsigned int reserved_13:3;             /**< \brief \internal Reserved */
    unsigned int ECC:6;                     /**< \brief [21:16] ECC (rwh) */
    unsigned int reserved_22:2;             /**< \brief \internal Reserved */
    unsigned int SRR:1;                     /**< \brief [24:24] Service Request Flag (rh) */
    unsigned int CLRR:1;                    /**< \brief [25:25] Request Clear Bit (w) */
    unsigned int SETR:1;                    /**< \brief [26:26] Request Set Bit (w) */
    unsigned int IOV:1;                     /**< \brief [27:27] Interrupt Trigger Overflow Bit (rh) */
    unsigned int IOVCLR:1;                  /**< \brief [28:28] Interrupt Trigger Overflow Clear Bit (w) */
    unsigned int SWS:1;                     /**< \brief [29:29] SW Sticky Bit (rh) */
    unsigned int SWSCLR:1;                  /**< \brief [30:30] SW Sticky Clear Bit (w) */
    unsigned int reserved_31:1;             /**< \brief \internal Reserved */
} Ifx_SRC_SRCR_Bits;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Src_union
 * \{  */

/** \brief  Service request register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SRC_SRCR_Bits B;                    /**< \brief Bitfield access */
} Ifx_SRC_SRCR;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Src_struct
 * \{  */
/******************************************************************************/
/** \name Object L2
 * \{  */

/** \brief  AGBT Service requests */
typedef volatile struct _Ifx_SRC_AGBT
{
    Ifx_SRC_SRCR SR;                        /**< \brief 0, AGBT Service Request */
} Ifx_SRC_AGBT;

/** \brief  ASCLIN Service requests */
typedef volatile struct _Ifx_SRC_ASCLIN
{
    Ifx_SRC_SRCR TX;                        /**< \brief 0, ASCLIN Transmit Service Request */
    Ifx_SRC_SRCR RX;                        /**< \brief 4, ASCLIN Receive Service Request */
    Ifx_SRC_SRCR ERR;                       /**< \brief 8, ASCLIN Error Service Request */
} Ifx_SRC_ASCLIN;

/** \brief  SPB Service requests */
typedef volatile struct _Ifx_SRC_BCUSPB
{
    Ifx_SRC_SRCR SBSRC;                     /**< \brief 0, Bus Control Unit SPB Service Request */
} Ifx_SRC_BCUSPB;

/** \brief  CAN Service requests */
typedef volatile struct _Ifx_SRC_CAN
{
    Ifx_SRC_SRCR INT[16];                   /**< \brief 0, MULTICAN+ Service Request */
} Ifx_SRC_CAN;

/** \brief  CCU6 Service requests */
typedef volatile struct _Ifx_SRC_CCU6
{
    Ifx_SRC_SRCR SR0;                       /**< \brief 0, CCU6 Service Request 0 */
    Ifx_SRC_SRCR SR1;                       /**< \brief 4, CCU6 Service Request 1 */
    Ifx_SRC_SRCR SR2;                       /**< \brief 8, CCU6 Service Request 2 */
    Ifx_SRC_SRCR SR3;                       /**< \brief C, CCU6 Service Request 3 */
} Ifx_SRC_CCU6;

/** \brief  CERBERUS Service requests */
typedef volatile struct _Ifx_SRC_CERBERUS
{
    Ifx_SRC_SRCR SR[2];                     /**< \brief 0, Cerberus Service Request */
} Ifx_SRC_CERBERUS;

/** \brief  CIF Service requests */
typedef volatile struct _Ifx_SRC_CIF
{
    Ifx_SRC_SRCR MI;                        /**< \brief 0, CIF MI Service Request */
    Ifx_SRC_SRCR MIEP;                      /**< \brief 4, CIF MI EP Service Request */
    Ifx_SRC_SRCR ISP;                       /**< \brief 8, CIF ISP Service Request */
    Ifx_SRC_SRCR MJPEG;                     /**< \brief C, CIF MJPEG Service Request */
} Ifx_SRC_CIF;

/** \brief  CPU Service requests */
typedef volatile struct _Ifx_SRC_CPU
{
    Ifx_SRC_SRCR SBSRC;                     /**< \brief 0, CPU Software Breakpoint Service Request */
} Ifx_SRC_CPU;

/** \brief  DMA Service requests */
typedef volatile struct _Ifx_SRC_DMA
{
    Ifx_SRC_SRCR ERR;                       /**< \brief 0, DMA Error Service Request */
    unsigned char reserved_4[12];           /**< \brief 4, \internal Reserved */
    Ifx_SRC_SRCR CH[48];                    /**< \brief 10, DMA Channel Service Request */
} Ifx_SRC_DMA;

/** \brief  DSADC Service requests */
typedef volatile struct _Ifx_SRC_DSADC
{
    Ifx_SRC_SRCR SRM;                       /**< \brief 0, DSADC SRM Service Request */
    Ifx_SRC_SRCR SRA;                       /**< \brief 4, DSADC SRA Service Request */
} Ifx_SRC_DSADC;

/** \brief  EMEM Service requests */
typedef volatile struct _Ifx_SRC_EMEM
{
    Ifx_SRC_SRCR SR;                        /**< \brief 0, Emulation Memory Service Request */
} Ifx_SRC_EMEM;

/** \brief  ERAY Service requests */
typedef volatile struct _Ifx_SRC_ERAY
{
    Ifx_SRC_SRCR INT[2];                    /**< \brief 0, E-RAY Service Request */
    Ifx_SRC_SRCR TINT[2];                   /**< \brief 8, E-RAY Timer Interrupt Service Request */
    Ifx_SRC_SRCR NDAT[2];                   /**< \brief 10, E-RAY New Data Service Request */
    Ifx_SRC_SRCR MBSC[2];                   /**< \brief 18, E-RAY Message Buffer Status Changed Service Request */
    Ifx_SRC_SRCR OBUSY;                     /**< \brief 20, E-RAY Output Buffer Busy Service Request */
    Ifx_SRC_SRCR IBUSY;                     /**< \brief 24, E-RAY Input Buffer Busy Service Request */
    unsigned char reserved_28[40];          /**< \brief 28, \internal Reserved */
} Ifx_SRC_ERAY;

/** \brief  ETH Service requests */
typedef volatile struct _Ifx_SRC_ETH
{
    Ifx_SRC_SRCR SR;                        /**< \brief 0, Ethernet Service Request */
} Ifx_SRC_ETH;

/** \brief  FCE Service requests */
typedef volatile struct _Ifx_SRC_FCE
{
    Ifx_SRC_SRCR SR;                        /**< \brief 0, FCE Error Service Request */
} Ifx_SRC_FCE;

/** \brief  FFT Service requests */
typedef volatile struct _Ifx_SRC_FFT
{
    Ifx_SRC_SRCR DONE;                      /**< \brief 0, FFT Done Service Request */
    Ifx_SRC_SRCR ERR;                       /**< \brief 4, FFT Error Service Request */
    Ifx_SRC_SRCR RFS;                       /**< \brief 8, FFT Ready For Start Service Request */
} Ifx_SRC_FFT;

/** \brief  GPSR Service requests */
typedef volatile struct _Ifx_SRC_GPSR
{
    Ifx_SRC_SRCR SR0;                       /**< \brief 0, General Purpose Service Request 0 */
    Ifx_SRC_SRCR SR1;                       /**< \brief 4, General Purpose Service Request 1 */
    Ifx_SRC_SRCR SR2;                       /**< \brief 8, General Purpose Service Request 2 */
    Ifx_SRC_SRCR SR3;                       /**< \brief C, General Purpose Service Request 3 */
    unsigned char reserved_10[16];          /**< \brief 10, \internal Reserved */
} Ifx_SRC_GPSR;

/** \brief  GPT12 Service requests */
typedef volatile struct _Ifx_SRC_GPT12
{
    Ifx_SRC_SRCR CIRQ;                      /**< \brief 0, GPT12 CAPREL Service Request */
    Ifx_SRC_SRCR T2;                        /**< \brief 4, GPT12 T2 Overflow/Underflow Service Request */
    Ifx_SRC_SRCR T3;                        /**< \brief 8, GPT12 T3 Overflow/Underflow Service Request */
    Ifx_SRC_SRCR T4;                        /**< \brief C, GPT12 T4 Overflow/Underflow Service Request */
    Ifx_SRC_SRCR T5;                        /**< \brief 10, GPT12 T5 Overflow/Underflow Service Request */
    Ifx_SRC_SRCR T6;                        /**< \brief 14, GPT12 T6 Overflow/Underflow Service Request */
    unsigned char reserved_18[24];          /**< \brief 18, \internal Reserved */
} Ifx_SRC_GPT12;

/** \brief  GTM Service requests */
typedef volatile struct _Ifx_SRC_GTM
{
    Ifx_SRC_SRCR AEIIRQ;                    /**< \brief 0, GTM AEI Shared Service Request */
    Ifx_SRC_SRCR ARUIRQ[3];                 /**< \brief 4, GTM ARU Shared Service Request */
    unsigned char reserved_10[4];           /**< \brief 10, \internal Reserved */
    Ifx_SRC_SRCR BRCIRQ;                    /**< \brief 14, GTM BRC Shared Service Request */
    Ifx_SRC_SRCR CMPIRQ;                    /**< \brief 18, GTM CMP Shared Service Request */
    Ifx_SRC_SRCR SPEIRQ[2];                 /**< \brief 1C, GTM SPE Shared Service Request */
    unsigned char reserved_24[8];           /**< \brief 24, \internal Reserved */
    Ifx_SRC_SRCR PSM[1][8];                 /**< \brief 2C, GTM PSM Shared Service Request */
    unsigned char reserved_4C[88];          /**< \brief 4C, \internal Reserved */
    Ifx_SRC_SRCR DPLL[27];                  /**< \brief A4, GTM DPLL Service Request */
    unsigned char reserved_110[96];         /**< \brief 110, \internal Reserved */
    Ifx_SRC_SRCR ERR;                       /**< \brief 170, GTM Error Service Request */
    unsigned char reserved_174[12];         /**< \brief 174, \internal Reserved */
    Ifx_SRC_SRCR TIM[3][8];                 /**< \brief 180, GTM TIM Shared Service Request */
    unsigned char reserved_1E0[416];        /**< \brief 1E0, \internal Reserved */
    Ifx_SRC_SRCR MCS[3][8];                 /**< \brief 380, GTM MCS Shared Service Request */
    unsigned char reserved_3E0[416];        /**< \brief 3E0, \internal Reserved */
    Ifx_SRC_SRCR TOM[2][8];                 /**< \brief 580, GTM TOM Shared Service Request */
    unsigned char reserved_5C0[448];        /**< \brief 5C0, \internal Reserved */
    Ifx_SRC_SRCR ATOM[4][4];                /**< \brief 780, GTM ATOM Shared Service Request */
    unsigned char reserved_7C0[320];        /**< \brief 7C0, \internal Reserved */
    Ifx_SRC_SRCR MCSW0[3];                  /**< \brief 900, GTM Multi Channel Sequencer 0 Service Request */
    unsigned char reserved_90C[52];         /**< \brief 90C, \internal Reserved */
    Ifx_SRC_SRCR MCSW1[3];                  /**< \brief 940, GTM Multi Channel Sequencer 1 Service Request */
} Ifx_SRC_GTM;

/** \brief  HSCT Service requests */
typedef volatile struct _Ifx_SRC_HSCT
{
    Ifx_SRC_SRCR SR;                        /**< \brief 0, HSCT Service Request */
} Ifx_SRC_HSCT;

/** \brief  HSSL Service requests */
typedef volatile struct _Ifx_SRC_HSSL
{
    Ifx_SRC_SRCR COK;                       /**< \brief 0, Channel OK Service Request m */
    Ifx_SRC_SRCR RDI;                       /**< \brief 4, Channel Read Data Service Request m */
    Ifx_SRC_SRCR ERR;                       /**< \brief 8, Channel Error ServiceRequest m */
    Ifx_SRC_SRCR TRG;                       /**< \brief C, Channel Trigger Service Request m */
} Ifx_SRC_HSSL;

/** \brief  I2C Service requests */
typedef volatile struct _Ifx_SRC_I2C
{
    Ifx_SRC_SRCR BREQ;                      /**< \brief 0, I2C Burst Data Transfer Request */
    Ifx_SRC_SRCR LBREQ;                     /**< \brief 4, I2C Last Burst Data Transfer Service Request */
    Ifx_SRC_SRCR SREQ;                      /**< \brief 8, I2C Single Data Transfer Service Request */
    Ifx_SRC_SRCR LSREQ;                     /**< \brief C, I2C Last Single Data Transfer Service Request */
    Ifx_SRC_SRCR ERR;                       /**< \brief 10, I2C Error Service Request */
    Ifx_SRC_SRCR P;                         /**< \brief 14, I2C Kernel Service Request */
    unsigned char reserved_18[56];          /**< \brief 18, \internal Reserved */
} Ifx_SRC_I2C;

/** \brief  LMU Service requests */
typedef volatile struct _Ifx_SRC_LMU
{
    Ifx_SRC_SRCR SR;                        /**< \brief 0, LMU Service Request */
} Ifx_SRC_LMU;

/** \brief  MSC Service requests */
typedef volatile struct _Ifx_SRC_MSC
{
    Ifx_SRC_SRCR SR0;                       /**< \brief 0, MSC Service Request 0 */
    Ifx_SRC_SRCR SR1;                       /**< \brief 4, MSC Service Request 1 */
    Ifx_SRC_SRCR SR2;                       /**< \brief 8, MSC Service Request 2 */
    Ifx_SRC_SRCR SR3;                       /**< \brief C, MSC Service Request 3 */
    Ifx_SRC_SRCR SR4;                       /**< \brief 10, MSC Service Request 4 */
} Ifx_SRC_MSC;

/** \brief  PMU Service requests */
typedef volatile struct _Ifx_SRC_PMU
{
    Ifx_SRC_SRCR SR;                        /**< \brief 0, PMU  Service Request */
} Ifx_SRC_PMU;

/** \brief  PSI5 Service requests */
typedef volatile struct _Ifx_SRC_PSI5
{
    Ifx_SRC_SRCR SR[8];                     /**< \brief 0, PSI5 Service Request */
} Ifx_SRC_PSI5;

/** \brief  PSI5S Service requests */
typedef volatile struct _Ifx_SRC_PSI5S
{
    Ifx_SRC_SRCR SR[8];                     /**< \brief 0, PSI5-S Service Request */
} Ifx_SRC_PSI5S;

/** \brief  QSPI Service requests */
typedef volatile struct _Ifx_SRC_QSPI
{
    Ifx_SRC_SRCR TX;                        /**< \brief 0, QSPI Transmit Service Request */
    Ifx_SRC_SRCR RX;                        /**< \brief 4, QSPI Receive Service Request */
    Ifx_SRC_SRCR ERR;                       /**< \brief 8, QSPI Error Service Request */
    Ifx_SRC_SRCR PT;                        /**< \brief C, QSPI Phase Transition Service Request */
    Ifx_SRC_SRCR HC;                        /**< \brief 10, QSPI High Speed Capture Service Request */
    Ifx_SRC_SRCR U;                         /**< \brief 14, QSPI User Defined Service Request */
} Ifx_SRC_QSPI;

/** \brief  SCR Service requests */
typedef volatile struct _Ifx_SRC_SCR
{
    Ifx_SRC_SRCR SR;                        /**< \brief 0, Stand By Controller Service Request */
} Ifx_SRC_SCR;

/** \brief  SCU Service requests */
typedef volatile struct _Ifx_SRC_SCU
{
    Ifx_SRC_SRCR DTS;                       /**< \brief 0, SCU DTS Busy Service Request */
    Ifx_SRC_SRCR ERU[4];                    /**< \brief 4, SCU ERU Service Request */
} Ifx_SRC_SCU;

/** \brief  SENT Service requests */
typedef volatile struct _Ifx_SRC_SENT
{
    Ifx_SRC_SRCR SR[6];                     /**< \brief 0, SENT TRIG Service Request */
} Ifx_SRC_SENT;

/** \brief  SMU Service requests */
typedef volatile struct _Ifx_SRC_SMU
{
    Ifx_SRC_SRCR SR[3];                     /**< \brief 0, SMU Service Request */
} Ifx_SRC_SMU;

/** \brief  STM Service requests */
typedef volatile struct _Ifx_SRC_STM
{
    Ifx_SRC_SRCR SR0;                       /**< \brief 0, System Timer  Service Request 0 */
    Ifx_SRC_SRCR SR1;                       /**< \brief 4, System Timer  Service Request 1 */
} Ifx_SRC_STM;

/** \brief  VADCCG Service requests */
typedef volatile struct _Ifx_SRC_VADCCG
{
    Ifx_SRC_SRCR SR0;                       /**< \brief 0, VADC Common Group  Service Request 0 */
    Ifx_SRC_SRCR SR1;                       /**< \brief 4, VADC Common Group  Service Request 1 */
    Ifx_SRC_SRCR SR2;                       /**< \brief 8, VADC Common Group  Service Request 2 */
    Ifx_SRC_SRCR SR3;                       /**< \brief C, VADC Common Group  Service Request 3 */
} Ifx_SRC_VADCCG;

/** \brief  VADCG Service requests */
typedef volatile struct _Ifx_SRC_VADCG
{
    Ifx_SRC_SRCR SR0;                       /**< \brief 0, VADC Group  Service Request 0 */
    Ifx_SRC_SRCR SR1;                       /**< \brief 4, VADC Group  Service Request 1 */
    Ifx_SRC_SRCR SR2;                       /**< \brief 8, VADC Group  Service Request 2 */
    Ifx_SRC_SRCR SR3;                       /**< \brief C, VADC Group  Service Request 3 */
} Ifx_SRC_VADCG;

/** \brief  XBAR Service requests */
typedef volatile struct _Ifx_SRC_XBAR
{
    Ifx_SRC_SRCR SRC;                       /**< \brief 0, XBAR_SRI Service Request */
} Ifx_SRC_XBAR;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Src_struct
 * \{  */
/******************************************************************************/
/** \name Object L1
 * \{  */

/** \brief  AGBT Service requests */
typedef volatile struct _Ifx_SRC_GAGBT
{
    Ifx_SRC_AGBT AGBT[1];                   /**< \brief 0, AGBT Service requests */
} Ifx_SRC_GAGBT;

/** \brief  ASCLIN Service requests */
typedef volatile struct _Ifx_SRC_GASCLIN
{
    Ifx_SRC_ASCLIN ASCLIN[4];               /**< \brief 0, ASCLIN Service requests */
} Ifx_SRC_GASCLIN;

/** \brief  BCU Service requests */
typedef volatile struct _Ifx_SRC_GBCU
{
    Ifx_SRC_BCUSPB SPB;                     /**< \brief 0, SPB Service requests */
} Ifx_SRC_GBCU;

/** \brief  CAN Service requests */
typedef volatile struct _Ifx_SRC_GCAN
{
    Ifx_SRC_CAN CAN[1];                     /**< \brief 0, CAN Service requests */
} Ifx_SRC_GCAN;

/** \brief  CCU6 Service requests */
typedef volatile struct _Ifx_SRC_GCCU6
{
    Ifx_SRC_CCU6 CCU6[2];                   /**< \brief 0, CCU6 Service requests */
} Ifx_SRC_GCCU6;

/** \brief  CERBERUS Service requests */
typedef volatile struct _Ifx_SRC_GCERBERUS
{
    Ifx_SRC_CERBERUS CERBERUS;              /**< \brief 0, CERBERUS Service requests */
} Ifx_SRC_GCERBERUS;

/** \brief  CIF Service requests */
typedef volatile struct _Ifx_SRC_GCIF
{
    Ifx_SRC_CIF CIF[1];                     /**< \brief 0, CIF Service requests */
} Ifx_SRC_GCIF;

/** \brief  CPU Service requests */
typedef volatile struct _Ifx_SRC_GCPU
{
    Ifx_SRC_CPU CPU[2];                     /**< \brief 0, CPU Service requests */
} Ifx_SRC_GCPU;

/** \brief  DMA Service requests */
typedef volatile struct _Ifx_SRC_GDMA
{
    Ifx_SRC_DMA DMA[1];                     /**< \brief 0, DMA Service requests */
} Ifx_SRC_GDMA;

/** \brief  DSADC Service requests */
typedef volatile struct _Ifx_SRC_GDSADC
{
    Ifx_SRC_DSADC DSADC0;                   /**< \brief 0, DSADC Service requests */
    unsigned char reserved_8[8];            /**< \brief 8, \internal Reserved */
    Ifx_SRC_DSADC DSADC2;                   /**< \brief 10, DSADC Service requests */
    Ifx_SRC_DSADC DSADC3;                   /**< \brief 18, DSADC Service requests */
} Ifx_SRC_GDSADC;

/** \brief  EMEM Service requests */
typedef volatile struct _Ifx_SRC_GEMEM
{
    Ifx_SRC_EMEM EMEM[1];                   /**< \brief 0, EMEM Service requests */
} Ifx_SRC_GEMEM;

/** \brief  ERAY Service requests */
typedef volatile struct _Ifx_SRC_GERAY
{
    Ifx_SRC_ERAY ERAY[1];                   /**< \brief 0, ERAY Service requests */
} Ifx_SRC_GERAY;

/** \brief  ETH Service requests */
typedef volatile struct _Ifx_SRC_GETH
{
    Ifx_SRC_ETH ETH[1];                     /**< \brief 0, ETH Service requests */
} Ifx_SRC_GETH;

/** \brief  FCE Service requests */
typedef volatile struct _Ifx_SRC_GFCE
{
    Ifx_SRC_FCE FCE[1];                     /**< \brief 0, FCE Service requests */
} Ifx_SRC_GFCE;

/** \brief  FFT Service requests */
typedef volatile struct _Ifx_SRC_GFFT
{
    Ifx_SRC_FFT FFT[1];                     /**< \brief 0, FFT Service requests */
} Ifx_SRC_GFFT;

/** \brief  GPSR Service requests */
typedef volatile struct _Ifx_SRC_GGPSR
{
    Ifx_SRC_GPSR GPSR[2];                   /**< \brief 0, GPSR Service requests */
} Ifx_SRC_GGPSR;

/** \brief  GPT12 Service requests */
typedef volatile struct _Ifx_SRC_GGPT12
{
    Ifx_SRC_GPT12 GPT12[1];                 /**< \brief 0, GPT12 Service requests */
} Ifx_SRC_GGPT12;

/** \brief  GTM Service requests */
typedef volatile struct _Ifx_SRC_GGTM
{
    Ifx_SRC_GTM GTM[1];                     /**< \brief 0, GTM Service requests */
} Ifx_SRC_GGTM;

/** \brief  HSCT Service requests */
typedef volatile struct _Ifx_SRC_GHSCT
{
    Ifx_SRC_HSCT HSCT[1];                   /**< \brief 0, HSCT Service requests */
} Ifx_SRC_GHSCT;

/** \brief  HSSL Service requests */
typedef volatile struct _Ifx_SRC_GHSSL
{
    Ifx_SRC_HSSL HSSL[4];                   /**< \brief 0, HSSL Service requests */
    Ifx_SRC_SRCR EXI;                       /**< \brief 40, Exception Service Request */
} Ifx_SRC_GHSSL;

/** \brief  I2C Service requests */
typedef volatile struct _Ifx_SRC_GI2C
{
    Ifx_SRC_I2C I2C[1];                     /**< \brief 0, I2C Service requests */
} Ifx_SRC_GI2C;

/** \brief  LMU Service requests */
typedef volatile struct _Ifx_SRC_GLMU
{
    Ifx_SRC_LMU LMU[1];                     /**< \brief 0, LMU Service requests */
} Ifx_SRC_GLMU;

/** \brief  MSC Service requests */
typedef volatile struct _Ifx_SRC_GMSC
{
    Ifx_SRC_MSC MSC[2];                     /**< \brief 0, MSC Service requests */
} Ifx_SRC_GMSC;

/** \brief  PMU Service requests */
typedef volatile struct _Ifx_SRC_GPMU
{
    Ifx_SRC_PMU PMU[2];                     /**< \brief 0, PMU Service requests */
} Ifx_SRC_GPMU;

/** \brief  PSI5 Service requests */
typedef volatile struct _Ifx_SRC_GPSI5
{
    Ifx_SRC_PSI5 PSI5[1];                   /**< \brief 0, PSI5 Service requests */
} Ifx_SRC_GPSI5;

/** \brief  PSI5S Service requests */
typedef volatile struct _Ifx_SRC_GPSI5S
{
    Ifx_SRC_PSI5S PSI5S[1];                 /**< \brief 0, PSI5S Service requests */
} Ifx_SRC_GPSI5S;

/** \brief  QSPI Service requests */
typedef volatile struct _Ifx_SRC_GQSPI
{
    Ifx_SRC_QSPI QSPI[4];                   /**< \brief 0, QSPI Service requests */
} Ifx_SRC_GQSPI;

/** \brief  SCR Service requests */
typedef volatile struct _Ifx_SRC_GSCR
{
    Ifx_SRC_SCR SCR[1];                     /**< \brief 0, SCR Service requests */
} Ifx_SRC_GSCR;

/** \brief  SCU Service requests */
typedef volatile struct _Ifx_SRC_GSCU
{
    Ifx_SRC_SCU SCU;                        /**< \brief 0, SCU Service requests */
} Ifx_SRC_GSCU;

/** \brief  SENT Service requests */
typedef volatile struct _Ifx_SRC_GSENT
{
    Ifx_SRC_SENT SENT[1];                   /**< \brief 0, SENT Service requests */
} Ifx_SRC_GSENT;

/** \brief  SMU Service requests */
typedef volatile struct _Ifx_SRC_GSMU
{
    Ifx_SRC_SMU SMU[1];                     /**< \brief 0, SMU Service requests */
} Ifx_SRC_GSMU;

/** \brief  STM Service requests */
typedef volatile struct _Ifx_SRC_GSTM
{
    Ifx_SRC_STM STM[2];                     /**< \brief 0, STM Service requests */
} Ifx_SRC_GSTM;

/** \brief  VADC Service requests */
typedef volatile struct _Ifx_SRC_GVADC
{
    Ifx_SRC_VADCG G[4];                     /**< \brief 0, VADCG Service requests */
    unsigned char reserved_40[224];         /**< \brief 40, \internal Reserved */
    Ifx_SRC_VADCCG CG[2];                   /**< \brief 120, VADCCG Service requests */
} Ifx_SRC_GVADC;

/** \brief  XBAR Service requests */
typedef volatile struct _Ifx_SRC_GXBAR
{
    Ifx_SRC_XBAR XBAR;                      /**< \brief 0, XBAR Service requests */
} Ifx_SRC_GXBAR;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Src_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \brief  SRC object */
typedef volatile struct _Ifx_SRC
{
    Ifx_SRC_GCPU CPU;                       /**< \brief 0, CPU Service requests */
    unsigned char reserved_8[24];           /**< \brief 8, \internal Reserved */
    Ifx_SRC_GEMEM EMEM;                     /**< \brief 20, EMEM Service requests */
    Ifx_SRC_GAGBT AGBT;                     /**< \brief 24, AGBT Service requests */
    unsigned char reserved_28[24];          /**< \brief 28, \internal Reserved */
    Ifx_SRC_GBCU BCU;                       /**< \brief 40, BCU Service requests */
    unsigned char reserved_44[4];           /**< \brief 44, \internal Reserved */
    Ifx_SRC_GXBAR XBAR;                     /**< \brief 48, XBAR Service requests */
    unsigned char reserved_4C[4];           /**< \brief 4C, \internal Reserved */
    Ifx_SRC_GCERBERUS CERBERUS;             /**< \brief 50, CERBERUS Service requests */
    unsigned char reserved_58[40];          /**< \brief 58, \internal Reserved */
    Ifx_SRC_GASCLIN ASCLIN;                 /**< \brief 80, ASCLIN Service requests */
    unsigned char reserved_B0[224];         /**< \brief B0, \internal Reserved */
    Ifx_SRC_GQSPI QSPI;                     /**< \brief 190, QSPI Service requests */
    unsigned char reserved_1F0[160];        /**< \brief 1F0, \internal Reserved */
    Ifx_SRC_GHSCT HSCT;                     /**< \brief 290, HSCT Service requests */
    unsigned char reserved_294[12];         /**< \brief 294, \internal Reserved */
    Ifx_SRC_GHSSL HSSL;                     /**< \brief 2A0, HSSL Service requests */
    unsigned char reserved_2E4[28];         /**< \brief 2E4, \internal Reserved */
    Ifx_SRC_GI2C I2C;                       /**< \brief 300, I2C Service requests */
    Ifx_SRC_GSENT SENT;                     /**< \brief 350, SENT Service requests */
    unsigned char reserved_368[120];        /**< \brief 368, \internal Reserved */
    Ifx_SRC_GMSC MSC;                       /**< \brief 3E0, MSC Service requests */
    unsigned char reserved_408[24];         /**< \brief 408, \internal Reserved */
    Ifx_SRC_GCCU6 CCU6;                     /**< \brief 420, CCU6 Service requests */
    unsigned char reserved_440[32];         /**< \brief 440, \internal Reserved */
    Ifx_SRC_GGPT12 GPT12;                   /**< \brief 460, GPT12 Service requests */
    Ifx_SRC_GSTM STM;                       /**< \brief 490, STM Service requests */
    unsigned char reserved_4A0[16];         /**< \brief 4A0, \internal Reserved */
    Ifx_SRC_GFCE FCE;                       /**< \brief 4B0, FCE Service requests */
    unsigned char reserved_4B4[60];         /**< \brief 4B4, \internal Reserved */
    Ifx_SRC_GDMA DMA;                       /**< \brief 4F0, DMA Service requests */
    unsigned char reserved_5C0[816];        /**< \brief 5C0, \internal Reserved */
    Ifx_SRC_GETH ETH;                       /**< \brief 8F0, ETH Service requests */
    unsigned char reserved_8F4[12];         /**< \brief 8F4, \internal Reserved */
    Ifx_SRC_GCAN CAN;                       /**< \brief 900, CAN Service requests */
    unsigned char reserved_940[64];         /**< \brief 940, \internal Reserved */
    Ifx_SRC_GVADC VADC;                     /**< \brief 980, VADC Service requests */
    unsigned char reserved_AC0[144];        /**< \brief AC0, \internal Reserved */
    Ifx_SRC_GDSADC DSADC;                   /**< \brief B50, DSADC Service requests */
    unsigned char reserved_B70[112];        /**< \brief B70, \internal Reserved */
    Ifx_SRC_GERAY ERAY;                     /**< \brief BE0, ERAY Service requests */
    Ifx_SRC_GPMU PMU;                       /**< \brief C30, PMU Service requests */
    unsigned char reserved_C38[152];        /**< \brief C38, \internal Reserved */
    Ifx_SRC_GSCU SCU;                       /**< \brief CD0, SCU Service requests */
    unsigned char reserved_CE4[28];         /**< \brief CE4, \internal Reserved */
    Ifx_SRC_GSCR SCR;                       /**< \brief D00, SCR Service requests */
    unsigned char reserved_D04[12];         /**< \brief D04, \internal Reserved */
    Ifx_SRC_GSMU SMU;                       /**< \brief D10, SMU Service requests */
    unsigned char reserved_D1C[20];         /**< \brief D1C, \internal Reserved */
    Ifx_SRC_GPSI5 PSI5;                     /**< \brief D30, PSI5 Service requests */
    unsigned char reserved_D50[80];         /**< \brief D50, \internal Reserved */
    Ifx_SRC_GCIF CIF;                       /**< \brief DA0, CIF Service requests */
    unsigned char reserved_DB0[48];         /**< \brief DB0, \internal Reserved */
    Ifx_SRC_GLMU LMU;                       /**< \brief DE0, LMU Service requests */
    unsigned char reserved_DE4[12];         /**< \brief DE4, \internal Reserved */
    Ifx_SRC_GPSI5S PSI5S;                   /**< \brief DF0, PSI5S Service requests */
    unsigned char reserved_E10[432];        /**< \brief E10, \internal Reserved */
    Ifx_SRC_GFFT FFT;                       /**< \brief FC0, FFT Service requests */
    unsigned char reserved_FCC[52];         /**< \brief FCC, \internal Reserved */
    Ifx_SRC_GGPSR GPSR;                     /**< \brief 1000, GPSR Service requests */
    unsigned char reserved_1040[1472];      /**< \brief 1040, \internal Reserved */
    Ifx_SRC_GGTM GTM;                       /**< \brief 1600, GTM Service requests */
    unsigned char reserved_1F4C[180];       /**< \brief 1F4C, \internal Reserved */
} Ifx_SRC;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXSRC_REGDEF_H */
