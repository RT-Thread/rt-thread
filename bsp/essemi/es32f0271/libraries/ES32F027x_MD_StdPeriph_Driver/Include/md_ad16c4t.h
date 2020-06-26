/**
  **************************************************************************************
  * @file    md_AD16C4T.h
  * @brief   ES32F0271 Header file of MD AD16C4T module.
  *
  * @version V0.01
  * @date    3/12/2018
  * @author  Eastsoft AE Team
  * @note
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. AMD rights reserved.
  *
  **************************************************************************************
  */
 /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MD_AD16C4T_H__
#define __MD_AD16C4T_H__

#ifdef __cplusplus
extern "C"{
#endif

/* Includes -------------------------------------------------------*/
#include "es32f0271.h"
#include "reg_ad16c4t.h"
 

/** @addtogroup Micro_Driver
  * @{
  */
#if defined (AD16C4T1)

/** @defgroup AD16C4T AD16C4T
  * @brief AD16C4T module driver
  * @{
  */


/* Private types --------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------*/
/* Private constants ----------------------------------------------------------*/
/* Private Macros ----------------------------------------------------------*/



/* Public Constants -----------------------------------------------------------*/

/** @defgroup MD_AD16C4T_Public_Constants Public Constants
  * @brief AD16C4T module driver
  * @{
  */
/* AD16C4T_CON1 macros define*/
#define MD_AD16C4T_DEBUGSELECT_INPUT        (0 << AD16C4T_CON1_DBGSEL_POS)      /*!<  Channel input*/
#define MD_AD16C4T_DEBUGSELECT_OUTPUT       (1 << AD16C4T_CON1_DBGSEL_POS)      /*!<  Channel output*/

#define MD_AD16C4T_COMPAREINPUT_DISABLE     (0 << AD16C4T_CON1_CMPSEL_POSS)     /*!<  Compare input is disabled*/
#define MD_AD16C4T_COMPAREINPUT_0           (1 << AD16C4T_CON1_CMPSEL_POSS)     /*!<  Compare input(CMP_IN)=Compare output 0*/
#define MD_AD16C4T_COMPAREINPUT_1           (2 << AD16C4T_CON1_CMPSEL_POSS)     /*!<  Compare input(CMP_IN)=Compare output 1*/
#define MD_AD16C4T_COMPAREINPUT_2           (3 << AD16C4T_CON1_CMPSEL_POSS)     /*!<  Compare input(CMP_IN)=Compare output 2*/
#define MD_AD16C4T_COMPAREINPUT_3           (4 << AD16C4T_CON1_CMPSEL_POSS)     /*!<  Compare input(CMP_IN)=Compare output 3*/

#define MD_AD16C4T_COMPAREPOLARITY_LOW      (0 << AD16C4T_CON1_CMPSELP_POS)     /*!<  Compare input is active low*/
#define MD_AD16C4T_COMPAREPOLARITY_HIGH     (1 << AD16C4T_CON1_CMPSELP_POS)     /*!<  Compare input is active high*/

#define MD_AD16C4T_CLOCKDIVSION_DIV1        (0 << AD16C4T_CON1_DFCKSEL_POSS)    /*!<  tDTS=tCK_INT*/
#define MD_AD16C4T_CLOCKDIVSION_DIV2        (1 << AD16C4T_CON1_DFCKSEL_POSS)    /*!<  tDTS=2*tCK_INT*/
#define MD_AD16C4T_CLOCKDIVSION_DIV4        (2 << AD16C4T_CON1_DFCKSEL_POSS)    /*!<  tDTS=4*tCK_INT*/

#define MD_AD16C4T_CENTERALIGNED_DISABLE    (0 << AD16C4T_CON1_CMSEL_POSS)      /*!<  Edge-aligned mode*/
#define MD_AD16C4T_CENTERALIGNED_DOWN       (1 << AD16C4T_CON1_CMSEL_POSS)      /*!<  Center-aligned mode 1*/
#define MD_AD16C4T_CENTERALIGNED_UP         (2 << AD16C4T_CON1_CMSEL_POSS)      /*!<  Center-aligned mode 2*/
#define MD_AD16C4T_CENTERALIGNED_BOTH       (3 << AD16C4T_CON1_CMSEL_POSS)      /*!<  Center-aligned mode 3*/

#define MD_AD16C4T_UPCOUNTER                (0 << AD16C4T_CON1_DIRSEL_POS)      /*!<  Counter used as upcounter*/
#define MD_AD16C4T_DOWNCOUNTER              (1 << AD16C4T_CON1_DIRSEL_POS)      /*!<  Counter used as downcounter*/

#define MD_AD16C4T_ONEPULSEMODE_DISABLE     (0 << AD16C4T_CON1_SPMEN_POS)       /*!<  Counter is not stopped at update event*/
#define MD_AD16C4T_ONEPULSEMODE_ENABLE      (1 << AD16C4T_CON1_SPMEN_POS)       /*!<  Counter stops counting at the next update event*/

#define MD_AD16C4T_UPDATESOURCE_NORMAL      (0 << AD16C4T_CON1_UERSEL_POS)      /*!<  Counter overflow/underflow, Setting the UG bit, Update generation through the slave mode controller generate an update interrupt*/
#define MD_AD16C4T_UPDATESOURCE_COUNTER     (1 << AD16C4T_CON1_UERSEL_POS)      /*!<  Only counter overflow/underflow generates an update interrupt or DMA request if Enabled*/

/* AD16C4T_CON2 macros define*/
#define MD_AD16C4T_IDLEOUTPUT_LOW           0                                   /*!<  OC1=0 (after a dead-time if OC1N is implemented) when MOE=0*/
#define MD_AD16C4T_IDLEOUTPUT_HIGH          1                                   /*!<  OC1=1 (after a dead-time if OC1N is implemented) when MOE=0*/

#define MD_AD16C4T_TI1INPUT_CH1             (0 << AD16C4T_CON2_I1SEL_POS)       /*!<  The TIMx_CH1 pin is connected to TI1 input*/
#define MD_AD16C4T_TI1INPUT_XOR             (1 << AD16C4T_CON2_I1SEL_POS)       /*!<  The TIMx_CH1, CH2 and CH3 pins are connected to the TI1 input (XOR combination)*/

#define MD_AD16C4T_MASTERMODE_RESET         (0 << AD16C4T_CON2_MMSEL_POSS)      /*!<  Reset mode*/
#define MD_AD16C4T_MASTERMODE_ENABLE        (1 << AD16C4T_CON2_MMSEL_POSS)      /*!<  Enable mode*/
#define MD_AD16C4T_MASTERMODE_UPDATE        (2 << AD16C4T_CON2_MMSEL_POSS)      /*!<  Update mode*/
#define MD_AD16C4T_MASTERMODE_COMPAREPULSE  (3 << AD16C4T_CON2_MMSEL_POSS)      /*!<  Compare Pulse mode*/
#define MD_AD16C4T_MASTERMODE_COMPARE1      (4 << AD16C4T_CON2_MMSEL_POSS)      /*!<  Compare 1 mode*/
#define MD_AD16C4T_MASTERMODE_COMPARE2      (5 << AD16C4T_CON2_MMSEL_POSS)      /*!<  Compare 2 mode*/
#define MD_AD16C4T_MASTERMODE_COMPARE3      (6 << AD16C4T_CON2_MMSEL_POSS)      /*!<  Compare 3 mode*/
#define MD_AD16C4T_MASTERMODE_COMPARE4      (7 << AD16C4T_CON2_MMSEL_POSS)      /*!<  Compare 4 mode*/

#define MD_AD16C4T_DMASELECTION_COMPARE     (0 << AD16C4T_CON2_CCDMASEL_POS)    /*!<  CCx DMA request sent when CCx event occurs*/
#define MD_AD16C4T_DMASELECTION_UPDATE      (1 << AD16C4T_CON2_CCDMASEL_POS)    /*!<  CCx DMA requests sent when update event occurs*/

#define MD_AD16C4T_UPDATESELECTION_COMG     (0 << AD16C4T_CON2_CCUSEL_POS)      /*!<  When capture/compare control bits are preloaded (CCPC=1), they are updated by setting the COMG bit only*/
#define MD_AD16C4T_UPDATESELECTION_BOTH     (1 << AD16C4T_CON2_CCUSEL_POS)      /*!<  When capture/compare control bits are preloaded (CCPC=1), they are updated by setting the COMG bit or when an rising edge occurs on TRGI*/

#define MD_AD16C4T_CCPRELOAD_DISABLE        (0 << AD16C4T_CON2_CCPCEN_POS)      /*!<  CCxE, CCxNE and OCxM bits are not preloaded*/
#define MD_AD16C4T_CCPRELOAD_ENABLE         (1 << AD16C4T_CON2_CCPCEN_POS)      /*!<  CCxE, CCxNE and OCxM bits are preloaded*/

/* AD16C4T_SMCON macros define*/
#define MD_AD16C4T_ETRPOLARITY_NONINVERTED  (0 << AD16C4T_SMCON_ETPOL_POS)      /*!<  ETR is non-inverted*/
#define MD_AD16C4T_ETRPOLARITY_INVERTED     (1 << AD16C4T_SMCON_ETPOL_POS)      /*!<  ETR is inverted*/

#define MD_AD16C4T_ETRFILTER_FDIV1          (0 << AD16C4T_SMCON_ETFLT_POSS)     /*!<  No filter*/
#define MD_AD16C4T_ETRFILTER_FDIV1N2        (1 << AD16C4T_SMCON_ETFLT_POSS)     /*!<  fSAMPLING = fCK_INT, N = 2*/
#define MD_AD16C4T_ETRFILTER_FDIV1N4        (2 << AD16C4T_SMCON_ETFLT_POSS)     /*!<  fSAMPLING = fCK_INT, N = 4*/
#define MD_AD16C4T_ETRFILTER_FDIV1N8        (3 << AD16C4T_SMCON_ETFLT_POSS)     /*!<  fSAMPLING = fCK_INT, N = 8*/
#define MD_AD16C4T_ETRFILTER_FDIV2N6        (4 << AD16C4T_SMCON_ETFLT_POSS)     /*!<  fSAMPLING = fDTS / 2, N = 6*/
#define MD_AD16C4T_ETRFILTER_FDIV2N8        (5 << AD16C4T_SMCON_ETFLT_POSS)     /*!<  fSAMPLING = fDTS / 2, N = 8*/
#define MD_AD16C4T_ETRFILTER_FDIV4N6        (6 << AD16C4T_SMCON_ETFLT_POSS)     /*!<  fSAMPLING = fDTS / 4, N = 6*/
#define MD_AD16C4T_ETRFILTER_FDIV4N8        (7 << AD16C4T_SMCON_ETFLT_POSS)     /*!<  fSAMPLING = fDTS / 4, N = 8*/
#define MD_AD16C4T_ETRFILTER_FDIV8N6        (8 << AD16C4T_SMCON_ETFLT_POSS)     /*!<  fSAMPLING = fDTS / 8, N = 6*/
#define MD_AD16C4T_ETRFILTER_FDIV8N8        (9 << AD16C4T_SMCON_ETFLT_POSS)     /*!<  fSAMPLING = fDTS / 8, N = 8*/
#define MD_AD16C4T_ETRFILTER_FDIV16N5       (10 << AD16C4T_SMCON_ETFLT_POSS)    /*!<  fSAMPLING = fDTS / 16, N = 5*/
#define MD_AD16C4T_ETRFILTER_FDIV16N6       (11 << AD16C4T_SMCON_ETFLT_POSS)    /*!<  fSAMPLING = fDTS / 16, N = 6*/
#define MD_AD16C4T_ETRFILTER_FDIV16N8       (12 << AD16C4T_SMCON_ETFLT_POSS)    /*!<  fSAMPLING = fDTS / 16, N = 8*/
#define MD_AD16C4T_ETRFILTER_FDIV32N5       (13 << AD16C4T_SMCON_ETFLT_POSS)    /*!<  fSAMPLING = fDTS / 32, N = 5*/
#define MD_AD16C4T_ETRFILTER_FDIV32N6       (14 << AD16C4T_SMCON_ETFLT_POSS)    /*!<  fSAMPLING = fDTS / 32, N = 6*/
#define MD_AD16C4T_ETRFILTER_FDIV32N8       (15 << AD16C4T_SMCON_ETFLT_POSS)    /*!<  fSAMPLING = fDTS / 32, N = 8*/

#define MD_AD16C4T_MASTERSLAVE_NODELAY      (0 << AD16C4T_SMCON_MSCFG_POS)      /*!<  No action*/
#define MD_AD16C4T_MASTERSLAVE_DELAY        (1 << AD16C4T_SMCON_MSCFG_POS)      /*!<  The effect of an event on the trigger input (TRGI) is delayed to allow a perfect*/

#define MD_AD16C4T_TRIGGERSELECT_ITR0       (0 << AD16C4T_SMCON_TSSEL_POSS)     /*!<  Internal Trigger 0*/
#define MD_AD16C4T_TRIGGERSELECT_ITR1       (1 << AD16C4T_SMCON_TSSEL_POSS)     /*!<  Internal Trigger 1*/
#define MD_AD16C4T_TRIGGERSELECT_ITR2       (2 << AD16C4T_SMCON_TSSEL_POSS)     /*!<  Internal Trigger 2*/
#define MD_AD16C4T_TRIGGERSELECT_ITR3       (3 << AD16C4T_SMCON_TSSEL_POSS)     /*!<  Internal Trigger 3*/
#define MD_AD16C4T_TRIGGERSELECT_TI1FED     (4 << AD16C4T_SMCON_TSSEL_POSS)     /*!<  TI1 Edge Detector*/
#define MD_AD16C4T_TRIGGERSELECT_TI1FP1     (5 << AD16C4T_SMCON_TSSEL_POSS)     /*!<  Filtered Timer Input 1*/
#define MD_AD16C4T_TRIGGERSELECT_TI2FP2     (6 << AD16C4T_SMCON_TSSEL_POSS)     /*!<  Filtered Timer Input 2*/
#define MD_AD16C4T_TRIGGERSELECT_ETRF       (7 << AD16C4T_SMCON_TSSEL_POSS)     /*!<  External Trigger input*/

#define MD_AD16C4T_OCREFCLEAR_CMP           (0 << AD16C4T_SMCON_CHCSEL_POS)     /*!<  OCREF_CLR is connected to the CMP_IN input*/
#define MD_AD16C4T_OCREFCLEAR_ETRF          (1 << AD16C4T_SMCON_CHCSEL_POS)     /*!<  OCREF_CLR is connected to ETRF*/

#define MD_AD16C4T_SLAVEMODE_DISABLE        (0 << AD16C4T_SMCON_SMODS_POSS)     /*!<  Slave mode disabled*/
#define MD_AD16C4T_SLAVEMODE_ENCODER1       (1 << AD16C4T_SMCON_SMODS_POSS)     /*!<  Encoder mode 1*/
#define MD_AD16C4T_SLAVEMODE_ENCODER2       (2 << AD16C4T_SMCON_SMODS_POSS)     /*!<  Encoder mode 2*/
#define MD_AD16C4T_SLAVEMODE_ENCODER3       (3 << AD16C4T_SMCON_SMODS_POSS)     /*!<  Encoder mode 3*/
#define MD_AD16C4T_SLAVEMODE_RESET          (4 << AD16C4T_SMCON_SMODS_POSS)     /*!<  Reset Mode*/
#define MD_AD16C4T_SLAVEMODE_GATED          (5 << AD16C4T_SMCON_SMODS_POSS)     /*!<  Gated Mode*/
#define MD_AD16C4T_SLAVEMODE_TRIGGER        (6 << AD16C4T_SMCON_SMODS_POSS)     /*!<  Trigger Mode*/
#define MD_AD16C4T_SLAVEMODE_EXTERNALCLOCK  (7 << AD16C4T_SMCON_SMODS_POSS)     /*!<  External Clock Mode 1*/

/* AD16C4T_IER IDR IVS RIF IFM ICR macros define*/
#define MD_AD16C4T_INTERRUPTFALG_CC4OI      (1 << AD16C4T_IER_CH4OVI_POS)       /*!<  Capture/Compare 4 overcapture interrupt*/
#define MD_AD16C4T_INTERRUPTFALG_CC3OI      (1 << AD16C4T_IER_CH3OVI_POS)       /*!<  Capture/Compare 3 overcapture interrupt*/
#define MD_AD16C4T_INTERRUPTFALG_CC2OI      (1 << AD16C4T_IER_CH2OVI_POS)       /*!<  Capture/Compare 2 overcapture interrupt*/
#define MD_AD16C4T_INTERRUPTFALG_CC1OI      (1 << AD16C4T_IER_CH1OVI_POS)       /*!<  Capture/Compare 1 overcapture interrupt*/
#define MD_AD16C4T_INTERRUPTFALG_BI         (1 << AD16C4T_IER_BRKI_POS)         /*!<  Break interrupt*/
#define MD_AD16C4T_INTERRUPTFALG_TI         (1 << AD16C4T_IER_TRGI_POS)         /*!<  Trigger interrupt*/
#define MD_AD16C4T_INTERRUPTFALG_COMI       (1 << AD16C4T_IER_COMI_POS)         /*!<  COM interrupt*/
#define MD_AD16C4T_INTERRUPTFALG_CC4I       (1 << AD16C4T_IER_CH4I_POS)         /*!<  Capture/Compare 4 interrupt*/
#define MD_AD16C4T_INTERRUPTFALG_CC3I       (1 << AD16C4T_IER_CH3I_POS)         /*!<  Capture/Compare 3 interrupt*/
#define MD_AD16C4T_INTERRUPTFALG_CC2I       (1 << AD16C4T_IER_CH2I_POS)         /*!<  Capture/Compare 2 interrupt*/
#define MD_AD16C4T_INTERRUPTFALG_CC1I       (1 << AD16C4T_IER_CH1I_POS)         /*!<  Capture/Compare 1 interrupt*/
#define MD_AD16C4T_INTERRUPTFALG_UI         (1 << AD16C4T_IER_UI_POS)           /*!<  Update interrupt*/

/* AD16C4T_SGE macros define*/
#define MD_AD16C4T_EVENTGENERATION_BG       (1 << AD16C4T_SGE_SGBRK_POS)        /*!<  Break generation*/  
#define MD_AD16C4T_EVENTGENERATION_TG       (1 << AD16C4T_SGE_SGTRG_POS)        /*!<  Trigger generation*/  
#define MD_AD16C4T_EVENTGENERATION_COMG     (1 << AD16C4T_SGE_SGCOM_POS)        /*!<  Capture/Compare control update generation*/
#define MD_AD16C4T_EVENTGENERATION_CC4G     (1 << AD16C4T_SGE_SGCH4_POS)        /*!<  Capture/Compare 4 generation*/
#define MD_AD16C4T_EVENTGENERATION_CC3G     (1 << AD16C4T_SGE_SGCH3_POS)        /*!<  Capture/Compare 3 generation*/
#define MD_AD16C4T_EVENTGENERATION_CC2G     (1 << AD16C4T_SGE_SGCH2_POS)        /*!<  Capture/Compare 2 generation*/
#define MD_AD16C4T_EVENTGENERATION_CC1G     (1 << AD16C4T_SGE_SGCH1_POS)        /*!<  Capture/Compare 1 generation*/
#define MD_AD16C4T_EVENTGENERATION_UG       (1 << AD16C4T_SGE_SGU_POS)          /*!<  Update generation*/

/* AD16C4T_CHMR1 CHMR2 output macros define*/
#define MD_AD16C4T_OUTPUTMODE_DISABLE       0                                   /*!<  Frozen*/
#define MD_AD16C4T_OUTPUTMODE_HIGHONMSTCH   1                                   /*!<  Set channel 1 to active level on match*/
#define MD_AD16C4T_OUTPUTMODE_LOWONMSTCH    2                                   /*!<  Set channel 1 to inactive level on match*/
#define MD_AD16C4T_OUTPUTMODE_TOGGLE        3                                   /*!<  Toggle*/
#define MD_AD16C4T_OUTPUTMODE_FORCELOW      4                                   /*!<  Force inactive level*/
#define MD_AD16C4T_OUTPUTMODE_FORCEHIGH     5                                   /*!<  Force active level*/
#define MD_AD16C4T_OUTPUTMODE_PWMMODE1      6                                   /*!<  PWM mode 1*/
#define MD_AD16C4T_OUTPUTMODE_PWMMODE2      7                                   /*!<  PWM mode 2*/

#define MD_AD16C4T_CHMODE_OUTPUT            0                                   /*!<  CCx channel is configured as output*/
#define MD_AD16C4T_CHMODE_INPUT_DIRECT      1                                   /*!<  CCx channel is configured as input, ICx is mapped direct*/
#define MD_AD16C4T_CHMODE_INPUT_INDIRECT    2                                   /*!<  CCx channel is configured as input, ICx is mapped indirect*/
#define MD_AD16C4T_CHMODE_INPUT_TRC         3                                   /*!<  CCx channel is configured as input, ICx is mapped TRC*/

/* AD16C4T_CHMR1 CHMR2 input macros define*/
#define MD_AD16C4T_INPUTFILTER_FDIV1        0                                   /*!<  No filter*/
#define MD_AD16C4T_INPUTFILTER_FDIV1N2      1                                   /*!<  fSAMPLING = fCK_INT, N = 2*/
#define MD_AD16C4T_INPUTFILTER_FDIV1N4      2                                   /*!<  fSAMPLING = fCK_INT, N = 4*/
#define MD_AD16C4T_INPUTFILTER_FDIV1N8      3                                   /*!<  fSAMPLING = fCK_INT, N = 8*/
#define MD_AD16C4T_INPUTFILTER_FDIV2N6      4                                   /*!<  fSAMPLING = fDTS / 2, N = 6*/
#define MD_AD16C4T_INPUTFILTER_FDIV2N8      5                                   /*!<  fSAMPLING = fDTS / 2, N = 8*/
#define MD_AD16C4T_INPUTFILTER_FDIV4N6      6                                   /*!<  fSAMPLING = fDTS / 4, N = 6*/
#define MD_AD16C4T_INPUTFILTER_FDIV4N8      7                                   /*!<  fSAMPLING = fDTS / 4, N = 8*/
#define MD_AD16C4T_INPUTFILTER_FDIV8N6      8                                   /*!<  fSAMPLING = fDTS / 8, N = 6*/
#define MD_AD16C4T_INPUTFILTER_FDIV8N8      9                                   /*!<  fSAMPLING = fDTS / 8, N = 8*/
#define MD_AD16C4T_INPUTFILTER_FDIV16N5     10                                  /*!<  fSAMPLING = fDTS / 16, N = 5*/
#define MD_AD16C4T_INPUTFILTER_FDIV16N6     11                                  /*!<  fSAMPLING = fDTS / 16, N = 6*/
#define MD_AD16C4T_INPUTFILTER_FDIV16N8     12                                  /*!<  fSAMPLING = fDTS / 16, N = 8*/
#define MD_AD16C4T_INPUTFILTER_FDIV32N5     13                                  /*!<  fSAMPLING = fDTS / 32, N = 5*/
#define MD_AD16C4T_INPUTFILTER_FDIV32N6     14                                  /*!<  fSAMPLING = fDTS / 32, N = 6*/
#define MD_AD16C4T_INPUTFILTER_FDIV32N8     15                                  /*!<  fSAMPLING = fDTS / 32, N = 8*/

#define MD_AD16C4T_INPUTPRESCALE_DIV1       0                                   /*!<  no prescaler*/
#define MD_AD16C4T_INPUTPRESCALE_DIV2       1                                   /*!<  capture is done once every 2 events*/
#define MD_AD16C4T_INPUTPRESCALE_DIV4       2                                   /*!<  capture is done once every 4 events*/
#define MD_AD16C4T_INPUTPRESCALE_DIV8       3                                   /*!<  capture is done once every 8 events*/

/* AD16C4T_CCEP input macros define*/
#define MD_AD16C4T_OUTPUTPOLARITY_HIGH      0                                   /*!<  active high*/
#define MD_AD16C4T_OUTPUTPOLARITY_LOW       1                                   /*!<  active low*/

/* AD16C4T_BDCFG input macros define*/
#define MD_AD16C4T_BREAKPOLARITY_LOW        (0 << AD16C4T_BDCFG_BRKP_POS)       /*!<  Break input BRK is active low*/
#define MD_AD16C4T_BREAKPOLARITY_HIGH       (1 << AD16C4T_BDCFG_BRKP_POS)       /*!<  Break input BRK is active high */

#define MD_AD16C4T_OFFSTATERUN_DISABLE      (0 << AD16C4T_BDCFG_OFFSSR_POS)     /*!<  This bit is used when MOE=1, when inactive, OC/OCN outputs are disabled*/
#define MD_AD16C4T_OFFSTATERUN_ENABLE       (1 << AD16C4T_BDCFG_OFFSSR_POS)     /*!<  This bit is used when MOE=1, when inactive, OC/OCN outputs are enabled*/

#define MD_AD16C4T_OFFSTATEIDLE_DISABLE     (0 << AD16C4T_BDCFG_OFFSSI_POS)     /*!<  This bit is used when MOE=0, when inactive, OC/OCN outputs are disabled*/
#define MD_AD16C4T_OFFSTATEIDLE_ENABLE      (1 << AD16C4T_BDCFG_OFFSSI_POS)     /*!<  This bit is used when MOE=0, when inactive, OC/OCN outputs are forced*/

#define MD_AD16C4T_LOCKLEVEL_0              (0 << AD16C4T_BDCFG_LOCKLVL_POSS)   /*!<  LOCK OFF*/
#define MD_AD16C4T_LOCKLEVEL_1              (1 << AD16C4T_BDCFG_LOCKLVL_POSS)   /*!<  LOCK Level 1*/
#define MD_AD16C4T_LOCKLEVEL_2              (2 << AD16C4T_BDCFG_LOCKLVL_POSS)   /*!<  LOCK Level 2*/
#define MD_AD16C4T_LOCKLEVEL_3              (3 << AD16C4T_BDCFG_LOCKLVL_POSS)   /*!<  LOCK Level 3*/

/**
  * @} MD_AD16C4T_Public_Constants
  */

/* Public Macro ------------------------------------------------------------*/
/** @defgroup MD_AD16C4T_Public_Macro Public Macro
  * @brief AD16C4T module driver
  * @{
  */
  
/**
  * @brief  Timer CON1 setup.
  * @param  timx AD16C4T instance
  * @param  value (DBGSEL | CMPSEL | CMPSELP | DFCKSEL | ARPEN | CMSEL | DIRSEL | SPMEN | UERSEL | DISUE | CNTEN)
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_con1(AD16C4T_TypeDef *timx, uint32_t value)
{
  WRITE_REG(timx->CON1, value);
}

/**
  * @brief  GET Timer CON1 register value.
  * @param  timx AD16C4T instance
  * @retval Timer CON1 register value.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_con1(AD16C4T_TypeDef *timx)
{
  return (READ_REG(timx->CON1));
}

/**
  * @brief  Timer debug mode select.
  * @param  timx AD16C4T instance
  * @param  DebugSelect Debug mode output select
            @arg @ref MD_AD16C4T_DEBUGSELECT_INPUT
            @arg @ref MD_AD16C4T_DEBUGSELECT_OUTPUT
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_con1_dbgsel(AD16C4T_TypeDef *timx, uint32_t DebugSelect)
{
  MODIFY_REG(timx->CON1, AD16C4T_CON1_DBGSEL_MSK, DebugSelect);
}

/**
  * @brief  Get timer debug mode select.
  * @param  timx AD16C4T instance
  * @retval Timer debug mode select.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_con1_dbgsel(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CON1, AD16C4T_CON1_DBGSEL_MSK) >> AD16C4T_CON1_DBGSEL_POS);
}

/**
  * @brief  Timer compare input selection.
  * @param  timx AD16C4T instance
  * @param  CompareSelection Compare input selection
            @arg @ref MD_AD16C4T_COMPAREINPUT_DISABLE
            @arg @ref MD_AD16C4T_COMPAREINPUT_0
            @arg @ref MD_AD16C4T_COMPAREINPUT_1
            @arg @ref MD_AD16C4T_COMPAREINPUT_2
            @arg @ref MD_AD16C4T_COMPAREINPUT_3
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_con1_cmpsel(AD16C4T_TypeDef *timx, uint32_t CompareSelection)
{
  MODIFY_REG(timx->CON1, AD16C4T_CON1_CMPSEL_MSK, CompareSelection);
}

/**
  * @brief  Get timer compare input selection.
  * @param  timx AD16C4T instance
  * @retval Timer compare input selection.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_con1_cmpsel(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CON1, AD16C4T_CON1_CMPSEL_MSK) >> AD16C4T_CON1_CMPSEL_POSS);
}

/**
  * @brief  Timer compare input selection polarity setup.
  * @param  timx AD16C4T instance
  * @param  ComparePolarity compare input selection polarity
            @arg @ref MD_AD16C4T_COMPAREPOLARITY_LOW
            @arg @ref MD_AD16C4T_COMPAREPOLARITY_HIGH
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_con1_cmpselp(AD16C4T_TypeDef *timx, uint32_t ComparePolarity)
{
  MODIFY_REG(timx->CON1, AD16C4T_CON1_CMPSELP_MSK, ComparePolarity);
}

/**
  * @brief  Get timer compare input selection polarity.
  * @param  timx AD16C4T instance
  * @retval Timer compare input selection polarity.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_con1_cmpselp(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CON1, AD16C4T_CON1_CMPSELP_MSK) >> AD16C4T_CON1_CMPSELP_POS);
}

/**
  * @brief  Timer clock division setup.
  * @param  timx AD16C4T instance
  * @param  ClockDivision Clock division
            @arg @ref MD_AD16C4T_CLOCKDIVSION_DIV1
            @arg @ref MD_AD16C4T_CLOCKDIVSION_DIV2
            @arg @ref MD_AD16C4T_CLOCKDIVSION_DIV4
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_con1_dfcksel(AD16C4T_TypeDef *timx, uint32_t ClockDivision)
{
  MODIFY_REG(timx->CON1, AD16C4T_CON1_DFCKSEL_MSK, ClockDivision);
}

/**
  * @brief  Get timer Clock division.
  * @param  timx AD16C4T instance
  * @retval Timer Clock division.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_con1_dfcksel(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CON1, AD16C4T_CON1_DFCKSEL_MSK) >> AD16C4T_CON1_DFCKSEL_POSS);
}

/**
  * @brief  Timer auto-reload preload enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_con1_arpen(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->CON1, AD16C4T_CON1_ARPEN_MSK);
}

/**
  * @brief  Timer auto-reload preload disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_con1_arpen(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->CON1, AD16C4T_CON1_ARPEN_MSK);
}

/**
  * @brief  Indicates whether the timer auto-reload preload is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_con1_arpen(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CON1, AD16C4T_CON1_ARPEN_MSK) == (AD16C4T_CON1_ARPEN_MSK));
}

/**
  * @brief  Timer center-aligned mode selection setup.
  * @param  timx AD16C4T instance
  * @param  CenterAlignedMode center-aligned mode selection
            @arg @ref MD_AD16C4T_CENTERALIGNED_DISABLE
            @arg @ref MD_AD16C4T_CENTERALIGNED_DOWN
            @arg @ref MD_AD16C4T_CENTERALIGNED_UP
            @arg @ref MD_AD16C4T_CENTERALIGNED_BOTH
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_con1_cmsel(AD16C4T_TypeDef *timx, uint32_t CenterAlignedMode)
{
  MODIFY_REG(timx->CON1, AD16C4T_CON1_CMSEL_MSK, CenterAlignedMode);
}

/**
  * @brief  Get timer center-aligned mode selection.
  * @param  timx AD16C4T instance
  * @retval Timer center-aligned mode selection.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_con1_cmsel(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CON1, AD16C4T_CON1_CMSEL_MSK) >> AD16C4T_CON1_CMSEL_POSS);
}

/**
  * @brief  Timer counting direction setup.
  * @param  timx AD16C4T instance
  * @param  direction Counting direction
            @arg @ref MD_AD16C4T_UPCOUNTER
            @arg @ref MD_AD16C4T_DOWNCOUNTER
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_con1_dirsel(AD16C4T_TypeDef *timx, uint32_t direction)
{
  MODIFY_REG(timx->CON1, AD16C4T_CON1_DIRSEL_MSK, direction);
}

/**
  * @brief  Get timer counting direction.
  * @param  timx AD16C4T instance
  * @retval Timer counting direction.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_con1_dirsel(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CON1, AD16C4T_CON1_DIRSEL_MSK) >> AD16C4T_CON1_DIRSEL_POS);
}

/**
  * @brief  Timer one pulse mode enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_con1_spmen(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->CON1, AD16C4T_CON1_SPMEN_MSK);
}

/**
  * @brief  Timer one pulse mode disable.
  * @param  timx AD16C4T instance
  * @retval None.
  */

__STATIC_INLINE void md_ad16c4t_disable_con1_spmen(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->CON1, AD16C4T_CON1_SPMEN_MSK);
}

/**
  * @brief  Indicates whether the timer one pulse mode is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_con1_spmen(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CON1, AD16C4T_CON1_SPMEN_MSK) == (AD16C4T_CON1_SPMEN_MSK));
}

/**
  * @brief  Timer update request source setup.
  * @param  timx AD16C4T instance
  * @param  UpdateSource Update request source select
            @arg @ref MD_AD16C4T_UPDATESOURCE_NORMAL
            @arg @ref MD_AD16C4T_UPDATESOURCE_COUNTER
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_con1_uersel(AD16C4T_TypeDef *timx, uint32_t UpdateSource)
{
  MODIFY_REG(timx->CON1, AD16C4T_CON1_UERSEL_MSK, UpdateSource);
}

/**
  * @brief  Get timer update request source.
  * @param  timx AD16C4T instance
  * @retval Timer update request source.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_con1_uersel(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CON1, AD16C4T_CON1_UERSEL_MSK) >> AD16C4T_CON1_UERSEL_POS);
}

/**
  * @brief  Timer update event enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_con1_disue(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->CON1, AD16C4T_CON1_DISUE_MSK);
}

/**
  * @brief  Timer update event disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disble_con1_disue(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->CON1, AD16C4T_CON1_DISUE_MSK);
}

/**
  * @brief  Indicates whether the timer update event is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_con1_disue(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CON1, AD16C4T_CON1_DISUE_MSK) == (AD16C4T_CON1_DISUE_MSK));
}

/**
  * @brief  Timer counter enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_con1_cnten(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->CON1, AD16C4T_CON1_CNTEN_MSK);
}
  

/**
  * @brief  Timer counter disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_con1_cnten(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->CON1, AD16C4T_CON1_CNTEN_MSK);
}

/**
  * @brief  Indicates whether the timer counter is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_con1_cnten(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CON1, AD16C4T_CON1_CNTEN_MSK) == (AD16C4T_CON1_CNTEN_MSK));
}

/**
  * @brief  Timer CON2 setup.
  * @param  timx AD16C4T instance
  * @param  value (OISS4 | OISS3N | OISS3 | OISS2N | OISS2 | OISS1N | OISS1 | I1SEL | MMSEL | CCDMASEL | CCUSEL | CCPCEN)
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_con2(AD16C4T_TypeDef *timx, uint32_t value)
{
  WRITE_REG(timx->CON2, value);
}

/**
  * @brief  GET Timer CON2 register value.
  * @param  timx AD16C4T instance
  * @retval Timer CON2 register value.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_con2(AD16C4T_TypeDef *timx)
{
  return (READ_REG(timx->CON2));
}

/**
  * @brief  Timer output idle state 4 setup.
  * @param  timx AD16C4T instance
  * @param  IdleOutput Output idle state
            @arg @ref MD_AD16C4T_IDLEOUTPUT_LOW
            @arg @ref MD_AD16C4T_IDLEOUTPUT_HIGH
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_con2_oiss4(AD16C4T_TypeDef *timx, uint32_t IdleOutput)
{
  MODIFY_REG(timx->CON2, AD16C4T_CON2_OISS4_MSK, (IdleOutput << AD16C4T_CON2_OISS4_POS));
}

/**
  * @brief  Get timer output idle state 4.
  * @param  timx AD16C4T instance
  * @retval Timer output idle state 4.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_con2_oiss4(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CON2, AD16C4T_CON2_OISS4_MSK) >> AD16C4T_CON2_OISS4_POS);
}

/**
  * @brief  Timer output idle state 3N setup.
  * @param  timx AD16C4T instance
  * @param  IdleOutput Output idle state
            @arg @ref MD_AD16C4T_IDLEOUTPUT_LOW
            @arg @ref MD_AD16C4T_IDLEOUTPUT_HIGH
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_con2_oiss3n(AD16C4T_TypeDef *timx, uint32_t IdleOutput)
{
  MODIFY_REG(timx->CON2, AD16C4T_CON2_OISS3N_MSK, (IdleOutput << AD16C4T_CON2_OISS3N_POS));
}

/**
  * @brief  Get timer output idle state 3N.
  * @param  timx AD16C4T instance
  * @retval Timer output idle state 3N.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_con2_oiss3n(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CON2, AD16C4T_CON2_OISS3N_MSK) >> AD16C4T_CON2_OISS3N_POS);
}

/**
  * @brief  Timer output idle state 3 setup.
  * @param  timx AD16C4T instance
  * @param  IdleOutput Output idle state
            @arg @ref MD_AD16C4T_IDLEOUTPUT_LOW
            @arg @ref MD_AD16C4T_IDLEOUTPUT_HIGH
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_con2_oiss3(AD16C4T_TypeDef *timx, uint32_t IdleOutput)
{
  MODIFY_REG(timx->CON2, AD16C4T_CON2_OISS3_MSK, (IdleOutput << AD16C4T_CON2_OISS3_POS));
}

/**
  * @brief  Get timer output idle state 3.
  * @param  timx AD16C4T instance
  * @retval Timer output idle state 3.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_con2_oiss3(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CON2, AD16C4T_CON2_OISS3_MSK) >> AD16C4T_CON2_OISS3_POS);
}

/**
  * @brief  Timer output idle state 2N setup.
  * @param  timx AD16C4T instance
  * @param  IdleOutput Output idle state
            @arg @ref MD_AD16C4T_IDLEOUTPUT_LOW
            @arg @ref MD_AD16C4T_IDLEOUTPUT_HIGH
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_con2_oiss2n(AD16C4T_TypeDef *timx, uint32_t IdleOutput)
{
  MODIFY_REG(timx->CON2, AD16C4T_CON2_OISS2N_MSK, (IdleOutput << AD16C4T_CON2_OISS2N_POS));
}

/**
  * @brief  Get timer output idle state 2N.
  * @param  timx AD16C4T instance
  * @retval Timer output idle state 2N.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_con2_oiss2n(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CON2, AD16C4T_CON2_OISS2N_MSK) >> AD16C4T_CON2_OISS2N_POS);
}

/**
  * @brief  Timer output idle state 2 setup.
  * @param  timx AD16C4T instance
  * @param  IdleOutput Output idle state
            @arg @ref MD_AD16C4T_IDLEOUTPUT_LOW
            @arg @ref MD_AD16C4T_IDLEOUTPUT_HIGH
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_con2_oiss2(AD16C4T_TypeDef *timx, uint32_t IdleOutput)
{
  MODIFY_REG(timx->CON2, AD16C4T_CON2_OISS2_MSK, (IdleOutput << AD16C4T_CON2_OISS2_POS));
}

/**
  * @brief  Get timer output idle state 2.
  * @param  timx AD16C4T instance
  * @retval Timer output idle state 2.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_con2_oiss2(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CON2, AD16C4T_CON2_OISS2_MSK) >> AD16C4T_CON2_OISS2_POS);
}

/**
  * @brief  Timer output idle state 1N setup.
  * @param  timx AD16C4T instance
  * @param  IdleOutput Output idle state
            @arg @ref MD_AD16C4T_IDLEOUTPUT_LOW
            @arg @ref MD_AD16C4T_IDLEOUTPUT_HIGH
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_con2_oiss1n(AD16C4T_TypeDef *timx, uint32_t IdleOutput)
{
  MODIFY_REG(timx->CON2, AD16C4T_CON2_OISS1N_MSK, (IdleOutput << AD16C4T_CON2_OISS1N_POS));
}

/**
  * @brief  Get timer output idle state 1N.
  * @param  timx AD16C4T instance
  * @retval Timer output idle state 1N.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_con2_oiss1n(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CON2, AD16C4T_CON2_OISS1N_MSK) >> AD16C4T_CON2_OISS1N_POS);
}

/**
  * @brief  Timer output idle state 1 setup.
  * @param  timx AD16C4T instance
  * @param  IdleOutput Output idle state
            @arg @ref MD_AD16C4T_IDLEOUTPUT_LOW
            @arg @ref MD_AD16C4T_IDLEOUTPUT_HIGH
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_con2_oiss1(AD16C4T_TypeDef *timx, uint32_t IdleOutput)
{
  MODIFY_REG(timx->CON2, AD16C4T_CON2_OISS1_MSK, (IdleOutput << AD16C4T_CON2_OISS1_POS));
}

/**
  * @brief  Get timer output idle state 1.
  * @param  timx AD16C4T instance
  * @retval Timer output idle state 1.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_con2_oiss1(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CON2, AD16C4T_CON2_OISS1_MSK) >> AD16C4T_CON2_OISS1_POS);
}

/**
  * @brief  Timer TI1 selection setup.
  * @param  timx AD16C4T instance
  * @param  TI1Input TI1 input select
            @arg @ref MD_AD16C4T_TI1INPUT_CH1
            @arg @ref MD_AD16C4T_TI1INPUT_XOR
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_con2_i1sel(AD16C4T_TypeDef *timx, uint32_t TI1Input)
{
  MODIFY_REG(timx->CON2, AD16C4T_CON2_I1SEL_MSK, TI1Input);
}

/**
  * @brief  Get timer TI1 selection.
  * @param  timx AD16C4T instance
  * @retval Timer TI1 selection.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_con2_i1sel(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CON2, AD16C4T_CON2_I1SEL_MSK) >> AD16C4T_CON2_I1SEL_POS);
}

/**
  * @brief  Timer master mode selection setup.
  * @param  timx AD16C4T instance
  * @param  MasterMode Master mode selection
            @arg @ref MD_AD16C4T_MASTERMODE_RESET
            @arg @ref MD_AD16C4T_MASTERMODE_ENABLE
            @arg @ref MD_AD16C4T_MASTERMODE_UPDATE
            @arg @ref MD_AD16C4T_MASTERMODE_COMPAREPULSE
            @arg @ref MD_AD16C4T_MASTERMODE_COMPARE1
            @arg @ref MD_AD16C4T_MASTERMODE_COMPARE2
            @arg @ref MD_AD16C4T_MASTERMODE_COMPARE3
            @arg @ref MD_AD16C4T_MASTERMODE_COMPARE4
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_con2_mmsel(AD16C4T_TypeDef *timx, uint32_t MasterMode)
{
  MODIFY_REG(timx->CON2, AD16C4T_CON2_MMSEL_MSK, MasterMode);
}

/**
  * @brief  Get timer master mode selection.
  * @param  timx AD16C4T instance
  * @retval Timer master mode selection.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_con2_mmsel(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CON2, AD16C4T_CON2_MMSEL_MSK) >> AD16C4T_CON2_MMSEL_POSS);
}

/**
  * @brief  Timer capture/compare DMA selection setup.
  * @param  timx AD16C4T instance
  * @param  DMASelection Capture/compare DMA selection
            @arg @ref MD_AD16C4T_DMASELECTION_COMPARE
            @arg @ref MD_AD16C4T_DMASELECTION_UPDATE
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_con2_ccdmasel(AD16C4T_TypeDef *timx, uint32_t DMASelection)
{
  MODIFY_REG(timx->CON2, AD16C4T_CON2_CCDMASEL_MSK, DMASelection);
}

/**
  * @brief  Get timer capture/compare DMA selection.
  * @param  timx AD16C4T instance
  * @retval Timer capture/compare DMA selection.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_con2_ccdmasel(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CON2, AD16C4T_CON2_CCDMASEL_MSK) >> AD16C4T_CON2_CCDMASEL_POS);
}

/**
  * @brief  Timer capture/compare control update selection setup.
  * @param  timx AD16C4T instance
  * @param  UpdateSelection Capture/compare control update selection
            @arg @ref MD_AD16C4T_UPDATESELECTION_COMG
            @arg @ref MD_AD16C4T_UPDATESELECTION_BOTH
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_con2_ccusel(AD16C4T_TypeDef *timx, uint32_t UpdateSelection)
{
  MODIFY_REG(timx->CON2, AD16C4T_CON2_CCUSEL_MSK, UpdateSelection);
}

/**
  * @brief  Get timer capture/compare control update selection.
  * @param  timx AD16C4T instance
  * @retval Timer capture/compare control update selection.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_con2_ccusel(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CON2, AD16C4T_CON2_CCUSEL_MSK) >> AD16C4T_CON2_CCUSEL_POS);
}

/**
  * @brief  Timer capture/compare preloaded control enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_con2_ccpcen(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->CON2, AD16C4T_CON2_CCPCEN_MSK);
}

/**
  * @brief  Timer capture/compare preloaded control disable.
  * @param  timx AD16C4T instance
  * @retval None.
  */

__STATIC_INLINE void md_ad16c4t_disable_con2_ccpcen(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->CON2, AD16C4T_CON2_CCPCEN_MSK);
}

/**
  * @brief  Indicates whether the timer capture/compare preloaded control is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_con2_ccpcen(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CON2, AD16C4T_CON2_CCPCEN_MSK) == (AD16C4T_CON2_CCPCEN_MSK));
}

/**
  * @brief  Timer SMCON setup.
  * @param  timx AD16C4T instance
  * @param  value (ETPOL | ECM2EN | ETFLT | MSCFG | TSSEL | CHCSEL | SMODS)
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_smcon(AD16C4T_TypeDef *timx, uint32_t value)
{
  WRITE_REG(timx->SMCON, value);
}

/**
  * @brief  GET Timer SMCON register value.
  * @param  timx AD16C4T instance
  * @retval Timer SMCON register value.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_smcon(AD16C4T_TypeDef *timx)
{
  return (READ_REG(timx->SMCON));
}

/**
  * @brief  Timer external trigger polarity setup.
  * @param  timx AD16C4T instance
  * @param  ETRPolarity External trigger polarity
            @arg @ref MD_AD16C4T_ETRPOLARITY_NONINVERTED
            @arg @ref MD_AD16C4T_ETRPOLARITY_INVERTED
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_smcon_etpol(AD16C4T_TypeDef *timx, uint32_t ETRPolarity)
{
  MODIFY_REG(timx->SMCON, AD16C4T_SMCON_ETPOL_MSK, ETRPolarity);
}

/**
  * @brief  Get timer external trigger polarity.
  * @param  timx AD16C4T instance
  * @retval Timer external trigger polarity.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_smcon_etpol(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->SMCON, AD16C4T_SMCON_ETPOL_MSK) >> AD16C4T_SMCON_ETPOL_POS);
}

/**
  * @brief  Timer external clock enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_smcon_ecm2en(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->SMCON, AD16C4T_SMCON_ECM2EN_MSK);
}
  

/**
  * @brief  Timer external clock disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_smcon_ecm2en(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->SMCON, AD16C4T_SMCON_ECM2EN_MSK);
}

/**
  * @brief  Indicates whether the timer external clock is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_smcon_ecm2en(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->SMCON, AD16C4T_SMCON_ECM2EN_MSK) == (AD16C4T_SMCON_ECM2EN_MSK));
}

/**
  * @brief  Timer external trigger filter setup.
  * @param  timx AD16C4T instance 
  * @param  ETRFilter External trigger filter
            @arg @ref MD_AD16C4T_ETRFILTER_FDIV1
            @arg @ref MD_AD16C4T_ETRFILTER_FDIV1N2
            @arg @ref MD_AD16C4T_ETRFILTER_FDIV1N4
            @arg @ref MD_AD16C4T_ETRFILTER_FDIV1N8
            @arg @ref MD_AD16C4T_ETRFILTER_FDIV2N6
            @arg @ref MD_AD16C4T_ETRFILTER_FDIV2N8
            @arg @ref MD_AD16C4T_ETRFILTER_FDIV4N6
            @arg @ref MD_AD16C4T_ETRFILTER_FDIV4N8
            @arg @ref MD_AD16C4T_ETRFILTER_FDIV8N6
            @arg @ref MD_AD16C4T_ETRFILTER_FDIV8N8
            @arg @ref MD_AD16C4T_ETRFILTER_FDIV16N5
            @arg @ref MD_AD16C4T_ETRFILTER_FDIV16N6
            @arg @ref MD_AD16C4T_ETRFILTER_FDIV16N8
            @arg @ref MD_AD16C4T_ETRFILTER_FDIV32N5
            @arg @ref MD_AD16C4T_ETRFILTER_FDIV32N6
            @arg @ref MD_AD16C4T_ETRFILTER_FDIV32N8
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_smcon_etflt(AD16C4T_TypeDef *timx, uint32_t ETRFilter)
{
  MODIFY_REG(timx->SMCON, AD16C4T_SMCON_ETFLT_MSK, ETRFilter);
}

/**
  * @brief  Get timer external trigger filter.
  * @param  timx AD16C4T instance
  * @retval Timer external trigger filter.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_smcon_etflt(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->SMCON, AD16C4T_SMCON_ETFLT_MSK) >> AD16C4T_SMCON_ETFLT_POSS);
}

/**
  * @brief  Timer master/slave mode setup.
  * @param  timx AD16C4T instance 
  * @param  MSMode master/slave mode
            @arg @ref MD_AD16C4T_MASTERSLAVE_NODELAY
            @arg @ref MD_AD16C4T_MASTERSLAVE_DELAY
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_smcon_mscfg(AD16C4T_TypeDef *timx, uint32_t MSMode)
{
  MODIFY_REG(timx->SMCON, AD16C4T_SMCON_MSCFG_MSK, MSMode);
}

/**
  * @brief  Get timer master/slave mode.
  * @param  timx AD16C4T instance
  * @retval Timer master/slave mode.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_smcon_mscfg(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->SMCON, AD16C4T_SMCON_MSCFG_MSK) >> AD16C4T_SMCON_MSCFG_POS);
}

/**
  * @brief  Timer trigger selection setup.
  * @param  timx AD16C4T instance 
  * @param  TriggerSelect Trigger selection
            @arg @ref MD_AD16C4T_TRIGGERSELECT_ITR0
            @arg @ref MD_AD16C4T_TRIGGERSELECT_ITR1
            @arg @ref MD_AD16C4T_TRIGGERSELECT_ITR2
            @arg @ref MD_AD16C4T_TRIGGERSELECT_ITR3
            @arg @ref MD_AD16C4T_TRIGGERSELECT_TI1FED
            @arg @ref MD_AD16C4T_TRIGGERSELECT_TI1FP1
            @arg @ref MD_AD16C4T_TRIGGERSELECT_TI2FP2
            @arg @ref MD_AD16C4T_TRIGGERSELECT_ETRF
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_smcon_tssel(AD16C4T_TypeDef *timx, uint32_t TriggerSelect)
{
  MODIFY_REG(timx->SMCON, AD16C4T_SMCON_TSSEL_MSK, TriggerSelect);
}

/**
  * @brief  Get timer trigger selection.
  * @param  timx AD16C4T instance
  * @retval Timer trigger selection.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_smcon_tssel(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->SMCON, AD16C4T_SMCON_TSSEL_MSK) >> AD16C4T_SMCON_TSSEL_POSS);
}

/**
  * @brief  Timer OCREF clear selection setup.
  * @param  timx AD16C4T instance 
  * @param  OCREFSelect OCREF clear selection
            @arg @ref MD_AD16C4T_OCREFCLEAR_CMP
            @arg @ref MD_AD16C4T_OCREFCLEAR_ETRF
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_smcon_chcsel(AD16C4T_TypeDef *timx, uint32_t OCREFSelect)
{
  MODIFY_REG(timx->SMCON, AD16C4T_SMCON_CHCSEL_MSK, OCREFSelect);
}

/**
  * @brief  Get timer OCREF clear selection.
  * @param  timx AD16C4T instance
  * @retval Timer OCREF clear selection.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_smcon_chcsel(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->SMCON, AD16C4T_SMCON_CHCSEL_MSK) >> AD16C4T_SMCON_CHCSEL_POS);
}

/**
  * @brief  Timer slave mode selection setup.
  * @param  timx AD16C4T instance 
  * @param  SlaveMode Slave mode selection
            @arg @ref MD_AD16C4T_SLAVEMODE_DISABLE
            @arg @ref MD_AD16C4T_SLAVEMODE_ENCODER1
            @arg @ref MD_AD16C4T_SLAVEMODE_ENCODER2
            @arg @ref MD_AD16C4T_SLAVEMODE_ENCODER3
            @arg @ref MD_AD16C4T_SLAVEMODE_RESET
            @arg @ref MD_AD16C4T_SLAVEMODE_GATED
            @arg @ref MD_AD16C4T_SLAVEMODE_TRIGGER
            @arg @ref MD_AD16C4T_SLAVEMODE_EXTERNALCLOCK
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_smcon_smods(AD16C4T_TypeDef *timx, uint32_t SlaveMode)
{
  MODIFY_REG(timx->SMCON, AD16C4T_SMCON_SMODS_MSK, SlaveMode);
}

/**
  * @brief  Get timer slave mode selection.
  * @param  timx AD16C4T instance
  * @retval Timer slave mode selection.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_smcon_smods(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->SMCON, AD16C4T_SMCON_SMODS_MSK) >> AD16C4T_SMCON_SMODS_POSS);
}

/**
  * @brief  Timer IER setup.
  * @param  timx AD16C4T instance
  * @param  value (CH4OVI | CH3OVI | CH2OVI | CH1OVI | BRKI | TRGI | COMI | CH4I | CH3I | CH2I | CH1I | UI)
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_ier(AD16C4T_TypeDef *timx, uint32_t value)
{
  WRITE_REG(timx->IER, value);
}

/**
  * @brief  Timer cpture/compare 4 overcapture interrupt enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_ier_ch4ovi(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->IER, AD16C4T_IER_CH4OVI_MSK);
}

/**
  * @brief  Timer cpture/compare 3 overcapture interrupt enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_ier_ch3ovi(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->IER, AD16C4T_IER_CH3OVI_MSK);
}

/**
  * @brief  Timer cpture/compare 2 overcapture interrupt enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_ier_ch2ovi(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->IER, AD16C4T_IER_CH2OVI_MSK);
}

/**
  * @brief  Timer cpture/compare 1 overcapture interrupt enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_ier_ch1ovi(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->IER, AD16C4T_IER_CH1OVI_MSK);
}

/**
  * @brief  Timer break interrupt enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_ier_brki(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->IER, AD16C4T_IER_BRKI_MSK);
}

/**
  * @brief  Timer trigger interrupt enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_ier_trgi(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->IER, AD16C4T_IER_TRGI_MSK);
}

/**
  * @brief  Timer COM interrupt enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_ier_comi(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->IER, AD16C4T_IER_COMI_MSK);
}

/**
  * @brief  Timer capture/compare 4 interrupt enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_ier_ch4i(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->IER, AD16C4T_IER_CH4I_MSK);
}

/**
  * @brief  Timer capture/compare 3 interrupt enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_ier_ch3i(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->IER, AD16C4T_IER_CH3I_MSK);
}

/**
  * @brief  Timer capture/compare 2 interrupt enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_ier_ch2i(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->IER, AD16C4T_IER_CH2I_MSK);
}

/**
  * @brief  Timer capture/compare 1 interrupt enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_ier_ch1i(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->IER, AD16C4T_IER_CH1I_MSK);
}

/**
  * @brief  Timer update interrupt enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_ier_ui(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->IER, AD16C4T_IER_UI_MSK);
}

/**
  * @brief  Timer IDR setup.
  * @param  timx AD16C4T instance
  * @param  value (CH4OVI | CH3OVI | CH2OVI | CH1OVI | BRKI | TRGI | COMI | CH4I | CH3I | CH2I | CH1I | UI)
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_idr(AD16C4T_TypeDef *timx, uint32_t value)
{
  WRITE_REG(timx->IDR, value);
}

/**
  * @brief  Timer cpture/compare 4 overcapture interrupt disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_idr_ch4ovi(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->IDR, AD16C4T_IDR_CH4OVI_MSK);
}

/**
  * @brief  Timer cpture/compare 3 overcapture interrupt disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_idr_ch3ovi(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->IDR, AD16C4T_IDR_CH3OVI_MSK);
}

/**
  * @brief  Timer cpture/compare 2 overcapture interrupt disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_idr_ch2ovi(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->IDR, AD16C4T_IDR_CH2OVI_MSK);
}

/**
  * @brief  Timer cpture/compare 1 overcapture interrupt disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_idr_ch1ovi(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->IDR, AD16C4T_IDR_CH1OVI_MSK);
}

/**
  * @brief  Timer break interrupt disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_idr_brki(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->IDR, AD16C4T_IDR_BRKI_MSK);
}

/**
  * @brief  Timer trigger interrupt disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_idr_trgi(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->IDR, AD16C4T_IDR_TRGI_MSK);
}

/**
  * @brief  Timer COM interrupt disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_idr_comi(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->IDR, AD16C4T_IDR_COMI_MSK);
}

/**
  * @brief  Timer capture/compare 4 interrupt disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_idr_ch4i(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->IDR, AD16C4T_IDR_CH4I_MSK);
}

/**
  * @brief  Timer capture/compare 3 interrupt disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_idr_ch3i(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->IDR, AD16C4T_IDR_CH3I_MSK);
}

/**
  * @brief  Timer capture/compare 2 interrupt disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_idr_ch2i(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->IDR, AD16C4T_IDR_CH2I_MSK);
}

/**
  * @brief  Timer capture/compare 1 interrupt disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_idr_ch1i(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->IDR, AD16C4T_IDR_CH1I_MSK);
}

/**
  * @brief  Timer update interrupt disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_idr_ui(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->IDR, AD16C4T_IDR_UI_MSK);
}

/**
  * @brief  Get timer IVS setup.
  * @param  timx AD16C4T instance
  * @retval Timer IVS setup.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_ivs(AD16C4T_TypeDef *timx)
{
  return (READ_REG(timx->IVS));
}

/**
  * @brief  Indicates whether the timer capture/compare 4 overcapture interrupt is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_ivs_ch4ovi(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->IVS, AD16C4T_IVS_CH4OVI_MSK) == (AD16C4T_IVS_CH4OVI_MSK));
}

/**
  * @brief  Indicates whether the timer capture/compare 3 overcapture interrupt is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_ivs_ch3ovi(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->IVS, AD16C4T_IVS_CH3OVI_MSK) == (AD16C4T_IVS_CH3OVI_MSK));
}

/**
  * @brief  Indicates whether the timer cpture/compare 2 overcapture interrupt is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_ivs_ch2ovi(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->IVS, AD16C4T_IVS_CH2OVI_MSK) == (AD16C4T_IVS_CH2OVI_MSK));
}

/**
  * @brief  Indicates whether the timer capture/compare 1 overcapture interrupt is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_ivs_ch1ovi(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->IVS, AD16C4T_IVS_CH1OVI_MSK) == (AD16C4T_IVS_CH1OVI_MSK));
}

/**
  * @brief  Indicates whether the timer break interrupt is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_ivs_brki(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->IVS, AD16C4T_IVS_BRKI_MSK) == (AD16C4T_IVS_BRKI_MSK));
}

/**
  * @brief  Indicates whether the timer trigger interrupt is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_ivs_trgi(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->IVS, AD16C4T_IVS_TRGI_MSK) == (AD16C4T_IVS_TRGI_MSK));
}

/**
  * @brief  Indicates whether the timer COM interrupt is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_ivs_comi(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->IVS, AD16C4T_IVS_COMI_MSK) == (AD16C4T_IVS_COMI_MSK));
}

/**
  * @brief  Indicates whether the timer Capture/Compare 4 interrupt is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_ivs_ch4i(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->IVS, AD16C4T_IVS_CH4I_MSK) == (AD16C4T_IVS_CH4I_MSK));
}

/**
  * @brief  Indicates whether the timer Capture/Compare 3 interrupt is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_ivs_ch3i(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->IVS, AD16C4T_IVS_CH3I_MSK) == (AD16C4T_IVS_CH3I_MSK));
}

/**
  * @brief  Indicates whether the timer Capture/Compare 2 interrupt is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_ivs_ch2i(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->IVS, AD16C4T_IVS_CH2I_MSK) == (AD16C4T_IVS_CH2I_MSK));
}

/**
  * @brief  Indicates whether the timer Capture/Compare 1 interrupt is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_ivs_ch1i(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->IVS, AD16C4T_IVS_CH1I_MSK) == (AD16C4T_IVS_CH1I_MSK));
}

/**
  * @brief  Indicates whether the timer update interrupt is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_ivs_ui(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->IVS, AD16C4T_IVS_UI_MSK) == (AD16C4T_IVS_UI_MSK));
}

/**
  * @brief  Get timer RIF flag.
  * @param  timx AD16C4T instance
  * @retval Timer RIF flag.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_rif(AD16C4T_TypeDef *timx)
{
  return (READ_REG(timx->RIF));
}

/**
  * @brief  Get timer capture/compare 4 overcapture interrupt flag.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_ad16c4t_is_active_flag_rif_ch4ovi(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->RIF, AD16C4T_RIF_CH4OVI_MSK) == (AD16C4T_RIF_CH4OVI_MSK));
}

/**
  * @brief  Get timer capture/compare 3 overcapture interrupt flag.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_ad16c4t_is_active_flag_rif_ch3ovi(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->RIF, AD16C4T_RIF_CH3OVI_MSK) == (AD16C4T_RIF_CH3OVI_MSK));
}

/**
  * @brief  Get timer capture/compare 2 overcapture interrupt flag.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_ad16c4t_is_active_flag_rif_ch2ovi(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->RIF, AD16C4T_RIF_CH2OVI_MSK) == (AD16C4T_RIF_CH2OVI_MSK));
}

/**
  * @brief  Get timer capture/compare 1 overcapture interrupt flag.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_ad16c4t_is_active_flag_rif_ch1ovi(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->RIF, AD16C4T_RIF_CH1OVI_MSK) == (AD16C4T_RIF_CH1OVI_MSK));
}

/**
  * @brief  Get timer break interrupt flag. 
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_ad16c4t_is_active_flag_rif_brki(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->RIF, AD16C4T_RIF_BRKI_MSK) == (AD16C4T_RIF_BRKI_MSK));
}

/**
  * @brief  Get timer trigger interrupt flag. 
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_ad16c4t_is_active_flag_rif_trgi(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->RIF, AD16C4T_RIF_TRGI_MSK) == (AD16C4T_RIF_TRGI_MSK));
}

/**
  * @brief  Get timer COM interrupt flag. 
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_ad16c4t_is_active_flag_rif_comi(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->RIF, AD16C4T_RIF_COMI_MSK) == (AD16C4T_RIF_COMI_MSK));
}

/**
  * @brief  Get timer capture/compare 4 interrupt flag.  
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_ad16c4t_is_active_flag_rif_ch4i(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->RIF, AD16C4T_RIF_CH4I_MSK) == (AD16C4T_RIF_CH4I_MSK));
}

/**
  * @brief  Get timer capture/compare 3 interrupt flag.  
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_ad16c4t_is_active_flag_rif_ch3i(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->RIF, AD16C4T_RIF_CH3I_MSK) == (AD16C4T_RIF_CH3I_MSK));
}

/**
  * @brief  Get timer capture/compare 2 interrupt flag.  
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_ad16c4t_is_active_flag_rif_ch2i(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->RIF, AD16C4T_RIF_CH2I_MSK) == (AD16C4T_RIF_CH2I_MSK));
}

/**
  * @brief  Get timer capture/compare 1 interrupt flag.  
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_ad16c4t_is_active_flag_rif_ch1i(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->RIF, AD16C4T_RIF_CH1I_MSK) == (AD16C4T_RIF_CH1I_MSK));
}

/**
  * @brief  Get timer update interrupt flag.  
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_ad16c4t_is_active_flag_rif_ui(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->RIF, AD16C4T_RIF_UI_MSK) == (AD16C4T_RIF_UI_MSK));
}

/**
  * @brief  Get timer IFM flag.
  * @param  timx AD16C4T instance
  * @retval Timer IFM flag.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_ifm(AD16C4T_TypeDef *timx)
{
  return (READ_REG(timx->IFM));
}

/**
  * @brief  Get timer capture/compare 4 overcapture interrupt flag masked.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_ad16c4t_is_active_flag_ifm_ch4ovi(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->IFM, AD16C4T_IFM_CH4OVI_MSK) == (AD16C4T_IFM_CH4OVI_MSK));
}

/**
  * @brief  Get timer capture/compare 3 overcapture interrupt flag masked.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_ad16c4t_is_active_flag_ifm_ch3ovi(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->IFM, AD16C4T_IFM_CH3OVI_MSK) == (AD16C4T_IFM_CH3OVI_MSK));
}

/**
  * @brief  Get timer capture/compare 2 overcapture interrupt flag masked.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_ad16c4t_is_active_flag_ifm_ch2ovi(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->IFM, AD16C4T_IFM_CH2OVI_MSK) == (AD16C4T_IFM_CH2OVI_MSK));
}

/**
  * @brief  Get timer capture/compare 1 overcapture interrupt flag masked.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_ad16c4t_is_active_flag_ifm_ch1ovi(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->IFM, AD16C4T_IFM_CH1OVI_MSK) == (AD16C4T_IFM_CH1OVI_MSK));
}

/**
  * @brief  Get timer break interrupt flag masked. 
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_ad16c4t_is_active_flag_ifm_brki(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->IFM, AD16C4T_IFM_BRKI_MSK) == (AD16C4T_IFM_BRKI_MSK));
}

/**
  * @brief  Get timer trigger interrupt flag masked. 
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_ad16c4t_is_active_flag_ifm_trgi(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->IFM, AD16C4T_IFM_TRGI_MSK) == (AD16C4T_IFM_TRGI_MSK));
}

/**
  * @brief  Get timer COM interrupt flag masked. 
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_ad16c4t_is_active_flag_ifm_comi(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->IFM, AD16C4T_IFM_COMI_MSK) == (AD16C4T_IFM_COMI_MSK));
}

/**
  * @brief  Get timer capture/compare 4 interrupt flag masked.  
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_ad16c4t_is_active_flag_ifm_ch4i(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->IFM, AD16C4T_IFM_CH4I_MSK) == (AD16C4T_IFM_CH4I_MSK));
}

/**
  * @brief  Get timer capture/compare 3 interrupt flag masked.  
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_ad16c4t_is_active_flag_ifm_ch3i(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->IFM, AD16C4T_IFM_CH3I_MSK) == (AD16C4T_IFM_CH3I_MSK));
}

/**
  * @brief  Get timer capture/compare 2 interrupt flag masked.  
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_ad16c4t_is_active_flag_ifm_ch2i(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->IFM, AD16C4T_IFM_CH2I_MSK) == (AD16C4T_IFM_CH2I_MSK));
}

/**
  * @brief  Get timer capture/compare 1 interrupt flag masked.  
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_ad16c4t_is_active_flag_ifm_ch1i(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->IFM, AD16C4T_IFM_CH1I_MSK) == (AD16C4T_IFM_CH1I_MSK));
}

/**
  * @brief  Get timer update interrupt flag masked.  
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_ad16c4t_is_active_flag_ifm_ui(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->IFM, AD16C4T_IFM_UI_MSK) == (AD16C4T_IFM_UI_MSK));
}

/**
  * @brief  Timer ICR setup.
  * @param  timx AD16C4T instance
  * @param  value (CC4OI | CC3OI | CC2OI | CC1OI | BI | TI | COMI | CC4I | CC3I | CC2I | CC1I | UI)
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_icr(AD16C4T_TypeDef *timx, uint32_t value)
{
  WRITE_REG(timx->ICR, value);
}

/**
  * @brief  Clear timer cpture/compare 4 overcapture interrupt flag.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_clear_flag_icr_ch4ovi(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->ICR, AD16C4T_ICR_CH4OVI_MSK);
}

/**
  * @brief  Clear timer cpture/compare 3 overcapture interrupt flag.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_clear_flag_icr_ch3ovi(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->ICR, AD16C4T_ICR_CH3OVI_MSK);
}

/**
  * @brief  Clear timer cpture/compare 2 overcapture interrupt flag.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_clear_flag_icr_ch2ovi(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->ICR, AD16C4T_ICR_CH2OVI_MSK);
}

/**
  * @brief  Clear timer cpture/compare 1 overcapture interrupt flag.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_clear_flag_icr_ch1ovi(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->ICR, AD16C4T_ICR_CH1OVI_MSK);
}

/**
  * @brief  Clear timer break interrupt flag.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_clear_flag_icr_brki(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->ICR, AD16C4T_ICR_BRKI_MSK);
}

/**
  * @brief  Clear timer trigger interrupt flag.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_clear_flag_icr_trgi(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->ICR, AD16C4T_ICR_TRGI_MSK);
}

/**
  * @brief  Clear timer COM interrupt flag.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_clear_flag_icr_comi(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->ICR, AD16C4T_ICR_COMI_MSK);
}

/**
  * @brief  Clear timer capture/compare 4 interrupt flag.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_clear_flag_icr_ch4i(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->ICR, AD16C4T_ICR_CH4I_MSK);
}

/**
  * @brief  Clear timer capture/compare 3 interrupt flag.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_clear_flag_icr_ch3i(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->ICR, AD16C4T_ICR_CH3I_MSK);
}

/**
  * @brief  Clear timer capture/compare 2 interrupt flag.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_clear_flag_icr_ch2i(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->ICR, AD16C4T_ICR_CH2I_MSK);
}

/**
  * @brief  Clear timer capture/compare 1 interrupt flag.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_clear_flag_icr_ch1i(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->ICR, AD16C4T_ICR_CH1I_MSK);
}

/**
  * @brief  Clear timer upadte flag.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_clear_flag_icr_ui(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->ICR, AD16C4T_ICR_UI_MSK);
}

/**
  * @brief  Timer SGE setup.
  * @param  timx AD16C4T instance
  * @param  value (SGBRK | SGTRG | SGCOM | SGCH4 | SGCH3 | SGCH2 | SGCH1 | SGU)
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_sge(AD16C4T_TypeDef *timx, uint32_t value)
{
  WRITE_REG(timx->SGE, value);
}

/**
  * @brief  Timer break generation.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_sge_sgbrk(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->SGE, AD16C4T_SGE_SGBRK_MSK);
}

/**
  * @brief  Timer trigger generation.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_sge_sgtrg(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->SGE, AD16C4T_SGE_SGTRG_MSK);
}

/**
  * @brief  Timer COM generation.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_sge_sgcom(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->SGE, AD16C4T_SGE_SGCOM_MSK);
}

/**
  * @brief  Timer Capture/Compare 4 generation.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_sge_sgch4(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->SGE, AD16C4T_SGE_SGCH4_MSK);
}

/**
  * @brief  Timer Capture/Compare 3 generation.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_sge_sgch3(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->SGE, AD16C4T_SGE_SGCH3_MSK);
}

/**
  * @brief  Timer Capture/Compare 2 generation.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_sge_sgch2(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->SGE, AD16C4T_SGE_SGCH2_MSK);
}

/**
  * @brief  Timer Capture/Compare 1 generation.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_sge_sgch1(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->SGE, AD16C4T_SGE_SGCH1_MSK);
}

/**
  * @brief  Timer update generation.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_sge_sgu(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->SGE, AD16C4T_SGE_SGU_MSK);
}

/**
  * @brief  Timer CHMR1 setup.
  * @param  timx AD16C4T instance
  * @param  value output (CH2OCLREN | CH2MOD | CH2PEN | CH2FEN | CC2SSEL | CH1OCLREN | CH1MOD | CH1PEN | CH1FEN | CC1SSEL)
  *               input  (I2FLT | I2PRES | CC2SSEL | I1FLT | I1PRES | CC1SSEL)
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_chmr1(AD16C4T_TypeDef *timx, uint32_t value)
{
  WRITE_REG(timx->CHMR1, value);
}

/**
  * @brief  GET Timer CHMR1 register value.
  * @param  timx AD16C4T instance
  * @retval Timer CHMR1 register value.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_chmr1(AD16C4T_TypeDef *timx)
{
  return (READ_REG(timx->CHMR1));
}

/**
  * @brief  Timer output compare 2 clear enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_chmr1_output_ch2oclren(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->CHMR1, AD16C4T_CHMR1_OUTPUT_CH2OCLREN_MSK);
}

/**
  * @brief  Timer output compare 2 clear disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_chmr1_output_ch2oclren(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->CHMR1, AD16C4T_CHMR1_OUTPUT_CH2OCLREN_MSK);
}

/**
  * @brief  Indicates whether the timer output compare 2 clear is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_chmr1_output_ch2oclren(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR1, AD16C4T_CHMR1_OUTPUT_CH2OCLREN_MSK) == (AD16C4T_CHMR1_OUTPUT_CH2OCLREN_MSK));
}

/**
  * @brief  Timer output compare 2 mode setup.
  * @param  timx AD16C4T instance
  * @param  OutputMode Output compare mode
            @arg @ref MD_AD16C4T_OUTPUTMODE_DISABLE
            @arg @ref MD_AD16C4T_OUTPUTMODE_HIGHONMSTCH
            @arg @ref MD_AD16C4T_OUTPUTMODE_LOWONMSTCH
            @arg @ref MD_AD16C4T_OUTPUTMODE_TOGGLE
            @arg @ref MD_AD16C4T_OUTPUTMODE_FORCELOW
            @arg @ref MD_AD16C4T_OUTPUTMODE_FORCEHIGH
            @arg @ref MD_AD16C4T_OUTPUTMODE_PWMMODE1
            @arg @ref MD_AD16C4T_OUTPUTMODE_PWMMODE2
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_chmr1_output_ch2mod(AD16C4T_TypeDef *timx, uint32_t OutputMode)
{
  MODIFY_REG(timx->CHMR1, AD16C4T_CHMR1_OUTPUT_CH2MOD_MSK, (OutputMode << AD16C4T_CHMR1_OUTPUT_CH2MOD_POSS));
}

/**
  * @brief  Get timer output compare 2 mode.
  * @param  timx AD16C4T instance
  * @retval Timer output compare 2 mode.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_chmr1_output_ch2mod(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR1, AD16C4T_CHMR1_OUTPUT_CH2MOD_MSK) >> AD16C4T_CHMR1_OUTPUT_CH2MOD_POSS);
}

/**
  * @brief  Timer output compare 2 preload enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_chmr1_output_ch2pen(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->CHMR1, AD16C4T_CHMR1_OUTPUT_CH2PEN_MSK);
}

/**
  * @brief  Timer output compare 2 preload disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_chmr1_output_ch2pen(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->CHMR1, AD16C4T_CHMR1_OUTPUT_CH2PEN_MSK);
}

/**
  * @brief  Indicates whether the timer output compare 2 preload is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_chmr1_output_ch2pen(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR1, AD16C4T_CHMR1_OUTPUT_CH2PEN_MSK) == (AD16C4T_CHMR1_OUTPUT_CH2PEN_MSK));
}

/**
  * @brief  Timer output compare 2 fast enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_chmr1_output_ch2fen(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->CHMR1, AD16C4T_CHMR1_OUTPUT_CH2FEN_MSK);
}

/**
  * @brief  Timer output compare 2 fast disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_chmr1_output_ch2fen(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->CHMR1, AD16C4T_CHMR1_OUTPUT_CH2FEN_MSK);
}

/**
  * @brief  Indicates whether the timer output compare 2 fast is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_chmr1_output_ch2fen(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR1, AD16C4T_CHMR1_OUTPUT_CH2FEN_MSK) == (AD16C4T_CHMR1_OUTPUT_CH2FEN_MSK));
}

/** 
  * @brief  Timer cpture/compare 2 selection setup.
  * @param  timx AD16C4T instance
  * @param  ChannelMode Channel mode selection
            @arg @ref MD_AD16C4T_CHMODE_OUTPUT
            @arg @ref MD_AD16C4T_CHMODE_INPUT_DIRECT
            @arg @ref MD_AD16C4T_CHMODE_INPUT_INDIRECT
            @arg @ref MD_AD16C4T_CHMODE_INPUT_TRC
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_chmr1_output_cc2ssel(AD16C4T_TypeDef *timx, uint32_t ChannelMode)
{
  MODIFY_REG(timx->CHMR1, AD16C4T_CHMR1_OUTPUT_CC2SSEL_MSK, (ChannelMode << AD16C4T_CHMR1_OUTPUT_CC2SSEL_POSS));
}

/**
  * @brief  Get timer cpture/compare 2 selection.
  * @param  timx AD16C4T instance
  * @retval Timer cpture/compare 2 selection.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_chmr1_output_cc2ssel(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR1, AD16C4T_CHMR1_OUTPUT_CC2SSEL_MSK) >> AD16C4T_CHMR1_OUTPUT_CC2SSEL_POSS);
}

/**
  * @brief  Timer output compare 1 clear enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_chmr1_output_ch1oclren(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->CHMR1, AD16C4T_CHMR1_OUTPUT_CH1OCLREN_MSK);
}

/**
  * @brief  Timer output compare 1 clear disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_chmr1_output_ch1oclren(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->CHMR1, AD16C4T_CHMR1_OUTPUT_CH1OCLREN_MSK);
}

/**
  * @brief  Indicates whether the timer output compare 1 clear is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_chmr1_output_ch1oclren(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR1, AD16C4T_CHMR1_OUTPUT_CH1OCLREN_MSK) == (AD16C4T_CHMR1_OUTPUT_CH1OCLREN_MSK));
}

/**
  * @brief  Timer output compare 1 mode setup.
  * @param  timx AD16C4T instance
  * @param  OutputMode Output compare mode
            @arg @ref MD_AD16C4T_OUTPUTMODE_DISABLE
            @arg @ref MD_AD16C4T_OUTPUTMODE_HIGHONMSTCH
            @arg @ref MD_AD16C4T_OUTPUTMODE_LOWONMSTCH
            @arg @ref MD_AD16C4T_OUTPUTMODE_TOGGLE
            @arg @ref MD_AD16C4T_OUTPUTMODE_FORCELOW
            @arg @ref MD_AD16C4T_OUTPUTMODE_FORCEHIGH
            @arg @ref MD_AD16C4T_OUTPUTMODE_PWMMODE1
            @arg @ref MD_AD16C4T_OUTPUTMODE_PWMMODE2
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_chmr1_output_ch1mod(AD16C4T_TypeDef *timx, uint32_t OutputMode)
{
  MODIFY_REG(timx->CHMR1, AD16C4T_CHMR1_OUTPUT_CH1MOD_MSK, (OutputMode << AD16C4T_CHMR1_OUTPUT_CH1MOD_POSS));
}

/**
  * @brief  Get timer output compare 1 mode.
  * @param  timx AD16C4T instance
  * @retval Timer output compare 1 mode.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_chmr1_output_ch1mod(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR1, AD16C4T_CHMR1_OUTPUT_CH1MOD_MSK) >> AD16C4T_CHMR1_OUTPUT_CH1MOD_POSS);
}

/**
  * @brief  Timer output compare 1 preload enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_chmr1_output_ch1pen(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->CHMR1, AD16C4T_CHMR1_OUTPUT_CH1PEN_MSK);
}

/**
  * @brief  Timer output compare 1 preload disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_chmr1_output_ch1pen(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->CHMR1, AD16C4T_CHMR1_OUTPUT_CH1PEN_MSK);
}

/**
  * @brief  Indicates whether the timer output compare 1 preload is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_chmr1_output_ch1pen(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR1, AD16C4T_CHMR1_OUTPUT_CH1PEN_MSK) == (AD16C4T_CHMR1_OUTPUT_CH1PEN_MSK));
}

/**
  * @brief  Timer output compare 1 fast enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_chmr1_output_ch1fen(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->CHMR1, AD16C4T_CHMR1_OUTPUT_CH1FEN_MSK);
}

/**
  * @brief  Timer output compare 1 fast disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_chmr1_output_ch1fen(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->CHMR1, AD16C4T_CHMR1_OUTPUT_CH1FEN_MSK);
}

/**
  * @brief  Indicates whether the timer output compare 1 fast is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_chmr1_output_ch1fen(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR1, AD16C4T_CHMR1_OUTPUT_CH1FEN_MSK) == (AD16C4T_CHMR1_OUTPUT_CH1FEN_MSK));
}

/** 
  * @brief  Timer cpture/compare 1 selection setup.
  * @param  timx AD16C4T instance
  * @param  ChannelMode Channel mode selection
            @arg @ref MD_AD16C4T_CHMODE_OUTPUT
            @arg @ref MD_AD16C4T_CHMODE_INPUT_DIRECT
            @arg @ref MD_AD16C4T_CHMODE_INPUT_INDIRECT
            @arg @ref MD_AD16C4T_CHMODE_INPUT_TRC
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_chmr1_output_cc1ssel(AD16C4T_TypeDef *timx, uint32_t ChannelMode)
{
  MODIFY_REG(timx->CHMR1, AD16C4T_CHMR1_OUTPUT_CC1SSEL_MSK, (ChannelMode << AD16C4T_CHMR1_OUTPUT_CC1SSEL_POSS));
}

/**
  * @brief  Get timer cpture/compare 1 selection.
  * @param  timx AD16C4T instance
  * @retval Timer cpture/compare 1 selection.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_chmr1_output_cc1ssel(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR1, AD16C4T_CHMR1_OUTPUT_CC1SSEL_MSK) >> AD16C4T_CHMR1_OUTPUT_CC1SSEL_POSS);
}

/** 
  * @brief  Timer input capture 2 filter setup.
  * @param  timx AD16C4T instance
  * @param  InputFliter Input capture filter
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV1
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV1N2
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV1N4
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV1N8
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV2N6
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV2N8
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV4N6
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV4N8
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV8N6
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV8N8
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV16N5
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV16N6
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV16N8
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV32N5
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV32N6
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV32N8
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_chmr1_input_i2flt(AD16C4T_TypeDef *timx, uint32_t InputFliter)
{
  MODIFY_REG(timx->CHMR1, AD16C4T_CHMR1_INPUT_I2FLT_MSK, (InputFliter << AD16C4T_CHMR1_INPUT_I2FLT_POSS));
}

/**
  * @brief  Get timer input capture 2 filter.
  * @param  timx AD16C4T instance
  * @retval Timer input capture 2 filter.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_chmr1_input_i2flt(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR1, AD16C4T_CHMR1_INPUT_I2FLT_MSK) >> AD16C4T_CHMR1_INPUT_I2FLT_POSS);
}

/** 
  * @brief  Timer input capture 2 prescaler setup.
  * @param  timx AD16C4T instance
  * @param  InputPrescale Input capture prescaler
            @arg @ref MD_AD16C4T_INPUTPRESCALE_DIV1
            @arg @ref MD_AD16C4T_INPUTPRESCALE_DIV2
            @arg @ref MD_AD16C4T_INPUTPRESCALE_DIV4
            @arg @ref MD_AD16C4T_INPUTPRESCALE_DIV8
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_chmr1_input_i2pres(AD16C4T_TypeDef *timx, uint32_t InputPrescale)
{
  MODIFY_REG(timx->CHMR1, AD16C4T_CHMR1_INPUT_I2PRES_MSK, (InputPrescale << AD16C4T_CHMR1_INPUT_I2PRES_POSS));
}

/**
  * @brief  Get timer input capture 2 prescaler.
  * @param  timx AD16C4T instance
  * @retval Timer input capture 2 prescaler.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_chmr1_input_i2pres(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR1, AD16C4T_CHMR1_INPUT_I2PRES_MSK) >> AD16C4T_CHMR1_INPUT_I2PRES_POSS);
}

/** 
  * @brief  Timer cpture/compare 2 selection setup.
  * @param  timx AD16C4T instance
  * @param  ChannelMode Channel mode selection
            @arg @ref MD_AD16C4T_CHMODE_OUTPUT
            @arg @ref MD_AD16C4T_CHMODE_INPUT_DIRECT
            @arg @ref MD_AD16C4T_CHMODE_INPUT_INDIRECT
            @arg @ref MD_AD16C4T_CHMODE_INPUT_TRC
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_chmr1_input_cc2ssel(AD16C4T_TypeDef *timx, uint32_t ChannelMode)
{
  MODIFY_REG(timx->CHMR1, AD16C4T_CHMR1_INPUT_CC2SSEL_MSK, (ChannelMode << AD16C4T_CHMR1_INPUT_CC2SSEL_POSS));
}

/**
  * @brief  Get timer cpture/compare 2 selection.
  * @param  timx AD16C4T instance
  * @retval Timer cpture/compare 2 selection.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_chmr1_input_cc2ssel(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR1, AD16C4T_CHMR1_INPUT_CC2SSEL_MSK) >> AD16C4T_CHMR1_INPUT_CC2SSEL_POSS);
}

/** 
  * @brief  Timer input capture 1 filter setup.
  * @param  timx AD16C4T instance
  * @param  InputFliter Input capture filter
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV1
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV1N2
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV1N4
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV1N8
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV2N6
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV2N8
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV4N6
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV4N8
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV8N6
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV8N8
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV16N5
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV16N6
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV16N8
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV32N5
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV32N6
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV32N8
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_chmr1_input_i1flt(AD16C4T_TypeDef *timx, uint32_t InputFliter)
{
  MODIFY_REG(timx->CHMR1, AD16C4T_CHMR1_INPUT_I1FLT_MSK, (InputFliter << AD16C4T_CHMR1_INPUT_I1FLT_POSS));
}

/**
  * @brief  Get timer input capture 1 filter.
  * @param  timx AD16C4T instance
  * @retval Timer input capture 1 filter.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_chmr1_input_i1flt(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR1, AD16C4T_CHMR1_INPUT_I1FLT_MSK) >> AD16C4T_CHMR1_INPUT_I1FLT_POSS);
}

/** 
  * @brief  Timer input capture 1 prescaler setup.
  * @param  timx AD16C4T instance
  * @param  InputPrescale Input capture prescaler
            @arg @ref MD_AD16C4T_INPUTPRESCALE_DIV1
            @arg @ref MD_AD16C4T_INPUTPRESCALE_DIV2
            @arg @ref MD_AD16C4T_INPUTPRESCALE_DIV4
            @arg @ref MD_AD16C4T_INPUTPRESCALE_DIV8
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_chmr1_input_i1pres(AD16C4T_TypeDef *timx, uint32_t InputPrescale)
{
  MODIFY_REG(timx->CHMR1, AD16C4T_CHMR1_INPUT_I1PRES_MSK, (InputPrescale << AD16C4T_CHMR1_INPUT_I1PRES_POSS));
}

/**
  * @brief  Get timer input capture 1 prescaler.
  * @param  timx AD16C4T instance
  * @retval Timer input capture 1 prescaler.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_chmr1_input_i1pres(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR1, AD16C4T_CHMR1_INPUT_I1PRES_MSK) >> AD16C4T_CHMR1_INPUT_I1PRES_POSS);
}

/** 
  * @brief  Timer cpture/compare 1 selection setup.
  * @param  timx AD16C4T instance
  * @param  ChannelMode Channel mode selection
            @arg @ref MD_AD16C4T_CHMODE_OUTPUT
            @arg @ref MD_AD16C4T_CHMODE_INPUT_DIRECT
            @arg @ref MD_AD16C4T_CHMODE_INPUT_INDIRECT
            @arg @ref MD_AD16C4T_CHMODE_INPUT_TRC
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_chmr1_input_cc1ssel(AD16C4T_TypeDef *timx, uint32_t ChannelMode)
{
  MODIFY_REG(timx->CHMR1, AD16C4T_CHMR1_INPUT_CC1SSEL_MSK, (ChannelMode << AD16C4T_CHMR1_INPUT_CC1SSEL_POSS));
}

/**
  * @brief  Get timer cpture/compare 1 selection.
  * @param  timx AD16C4T instance
  * @retval Timer cpture/compare 1 selection.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_chmr1_input_cc1ssel(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR1, AD16C4T_CHMR1_INPUT_CC1SSEL_MSK) >> AD16C4T_CHMR1_INPUT_CC1SSEL_POSS);
}

/**
  * @brief  Timer CHMR2 setup.

  * @param  timx AD16C4T instance
  * @param  value output (CH4OCLREN | CH4MOD | CH4PEN | CH4FEN | CC4SSEL | CH3OCLREN | CH3MOD | CH3PEN | CH3FEN | CC3SSEL)
  *               input  (I4FLT | I4PRES | CC4SSEL | I3FLT | I3PRES | CC3SSEL)
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_chmr2(AD16C4T_TypeDef *timx, uint32_t value)
{
  WRITE_REG(timx->CHMR2, value);
}

/**
  * @brief  GET Timer CHMR2 register value.
  * @param  timx AD16C4T instance
  * @retval Timer CHMR2 register value.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_chmr2(AD16C4T_TypeDef *timx)
{
  return (READ_REG(timx->CHMR2));
}

/**
  * @brief  Timer output compare 4 clear enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_chmr2_output_ch4oclren(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->CHMR2, AD16C4T_CHMR2_OUTPUT_CH4OCLREN_MSK);
}

/**
  * @brief  Timer output compare 4 clear disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_chmr2_output_ch4oclren(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->CHMR2, AD16C4T_CHMR2_OUTPUT_CH4OCLREN_MSK);
}

/**
  * @brief  Indicates whether the timer output compare 4 clear is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_chmr2_output_ch4oclren(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR2, AD16C4T_CHMR2_OUTPUT_CH4OCLREN_MSK) == (AD16C4T_CHMR2_OUTPUT_CH4OCLREN_MSK));
}

/**
  * @brief  Timer output compare 4 mode setup.
  * @param  timx AD16C4T instance
  * @param  OutputMode Output compare mode
            @arg @ref MD_AD16C4T_OUTPUTMODE_DISABLE
            @arg @ref MD_AD16C4T_OUTPUTMODE_HIGHONMSTCH
            @arg @ref MD_AD16C4T_OUTPUTMODE_LOWONMSTCH
            @arg @ref MD_AD16C4T_OUTPUTMODE_TOGGLE
            @arg @ref MD_AD16C4T_OUTPUTMODE_FORCELOW
            @arg @ref MD_AD16C4T_OUTPUTMODE_FORCEHIGH
            @arg @ref MD_AD16C4T_OUTPUTMODE_PWMMODE1
            @arg @ref MD_AD16C4T_OUTPUTMODE_PWMMODE2
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_chmr2_output_ch4mod(AD16C4T_TypeDef *timx, uint32_t OutputMode)
{
  MODIFY_REG(timx->CHMR2, AD16C4T_CHMR2_OUTPUT_CH4MOD_MSK, (OutputMode << AD16C4T_CHMR2_OUTPUT_CH4MOD_POSS));
}

/**
  * @brief  Get timer output compare 4 mode.
  * @param  timx AD16C4T instance
  * @retval Timer output compare 4 mode.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_chmr2_output_ch4mod(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR2, AD16C4T_CHMR2_OUTPUT_CH4MOD_MSK) >> AD16C4T_CHMR2_OUTPUT_CH4MOD_POSS);
}

/**
  * @brief  Timer output compare 4 preload enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_chmr2_output_ch4pen(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->CHMR2, AD16C4T_CHMR2_OUTPUT_CH4PEN_MSK);
}

/**
  * @brief  Timer output compare 4 preload disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_chmr2_output_ch4pen(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->CHMR2, AD16C4T_CHMR2_OUTPUT_CH4PEN_MSK);
}

/**
  * @brief  Indicates whether the timer output compare 4 preload is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_chmr2_output_ch4pen(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR2, AD16C4T_CHMR2_OUTPUT_CH4PEN_MSK) == (AD16C4T_CHMR2_OUTPUT_CH4PEN_MSK));
}

/**
  * @brief  Timer output compare 4 fast enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_chmr2_output_ch4fen(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->CHMR2, AD16C4T_CHMR2_OUTPUT_CH4FEN_MSK);
}

/**
  * @brief  Timer output compare 4 fast disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_chmr2_output_ch4fen(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->CHMR2, AD16C4T_CHMR2_OUTPUT_CH4FEN_MSK);
}

/**
  * @brief  Indicates whether the timer output compare 4 fast is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_chmr2_output_ch4fen(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR2, AD16C4T_CHMR2_OUTPUT_CH4FEN_MSK) == (AD16C4T_CHMR2_OUTPUT_CH4FEN_MSK));
}

/** 
  * @brief  Timer cpture/compare 4 selection setup.
  * @param  timx AD16C4T instance
  * @param  ChannelMode Channel mode selection
            @arg @ref MD_AD16C4T_CHMODE_OUTPUT
            @arg @ref MD_AD16C4T_CHMODE_INPUT_DIRECT
            @arg @ref MD_AD16C4T_CHMODE_INPUT_INDIRECT
            @arg @ref MD_AD16C4T_CHMODE_INPUT_TRC
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_chmr2_output_cc4ssel(AD16C4T_TypeDef *timx, uint32_t ChannelMode)
{
  MODIFY_REG(timx->CHMR2, AD16C4T_CHMR2_OUTPUT_CC4SSEL_MSK, (ChannelMode << AD16C4T_CHMR2_OUTPUT_CC4SSEL_POSS));
}

/**
  * @brief  Get timer cpture/compare 4 selection.
  * @param  timx AD16C4T instance
  * @retval Timer cpture/compare 4 selection.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_chmr2_output_cc4ssel(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR2, AD16C4T_CHMR2_OUTPUT_CC4SSEL_MSK) >> AD16C4T_CHMR2_OUTPUT_CC4SSEL_POSS);
}

/**
  * @brief  Timer output compare 3 clear enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_chmr2_output_ch3oclren(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->CHMR2, AD16C4T_CHMR2_OUTPUT_CH3OCLREN_MSK);
}

/**
  * @brief  Timer output compare 3 clear disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_chmr2_output_ch3oclren(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->CHMR2, AD16C4T_CHMR2_OUTPUT_CH3OCLREN_MSK);
}

/**
  * @brief  Indicates whether the timer output compare 3 clear is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_chmr2_output_ch3oclren(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR2, AD16C4T_CHMR2_OUTPUT_CH3OCLREN_MSK) == (AD16C4T_CHMR2_OUTPUT_CH3OCLREN_MSK));
}

/**
  * @brief  Timer output compare 3 mode setup.
  * @param  timx AD16C4T instance
  * @param  OutputMode Output compare mode
            @arg @ref MD_AD16C4T_OUTPUTMODE_DISABLE
            @arg @ref MD_AD16C4T_OUTPUTMODE_HIGHONMSTCH
            @arg @ref MD_AD16C4T_OUTPUTMODE_LOWONMSTCH
            @arg @ref MD_AD16C4T_OUTPUTMODE_TOGGLE
            @arg @ref MD_AD16C4T_OUTPUTMODE_FORCELOW
            @arg @ref MD_AD16C4T_OUTPUTMODE_FORCEHIGH
            @arg @ref MD_AD16C4T_OUTPUTMODE_PWMMODE1
            @arg @ref MD_AD16C4T_OUTPUTMODE_PWMMODE2
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_chmr2_output_ch3mod(AD16C4T_TypeDef *timx, uint32_t OutputMode)
{
  MODIFY_REG(timx->CHMR2, AD16C4T_CHMR2_OUTPUT_CH3MOD_MSK, (OutputMode << AD16C4T_CHMR2_OUTPUT_CH3MOD_POSS));
}

/**
  * @brief  Get timer output compare 3 mode.
  * @param  timx AD16C4T instance
  * @retval Timer output compare 3 mode.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_chmr2_output_ch3mod(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR2, AD16C4T_CHMR2_OUTPUT_CH3MOD_MSK) >> AD16C4T_CHMR2_OUTPUT_CH3MOD_POSS);
}

/**
  * @brief  Timer output compare 3 preload enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_chmr2_output_ch3pen(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->CHMR2, AD16C4T_CHMR2_OUTPUT_CH3PEN_MSK);
}

/**
  * @brief  Timer output compare 3 preload disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_chmr2_output_ch3pen(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->CHMR2, AD16C4T_CHMR2_OUTPUT_CH3PEN_MSK);
}

/**
  * @brief  Indicates whether the timer output compare 3 preload is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_chmr2_output_ch3pen(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR2, AD16C4T_CHMR2_OUTPUT_CH3PEN_MSK) == (AD16C4T_CHMR2_OUTPUT_CH3PEN_MSK));
}

/**
  * @brief  Timer output compare 3 fast enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_chmr2_output_ch3fen(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->CHMR2, AD16C4T_CHMR2_OUTPUT_CH3FEN_MSK);
}

/**
  * @brief  Timer output compare 3 fast disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_chmr2_output_ch3fen(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->CHMR2, AD16C4T_CHMR2_OUTPUT_CH3FEN_MSK);
}

/**
  * @brief  Indicates whether the timer output compare 3 fast is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_chmr2_output_ch3fen(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR2, AD16C4T_CHMR2_OUTPUT_CH3FEN_MSK) == (AD16C4T_CHMR2_OUTPUT_CH3FEN_MSK));
}

/** 
  * @brief  Timer cpture/compare 3 selection setup.
  * @param  timx AD16C4T instance
  * @param  ChannelMode Channel mode selection
            @arg @ref MD_AD16C4T_CHMODE_OUTPUT
            @arg @ref MD_AD16C4T_CHMODE_INPUT_DIRECT
            @arg @ref MD_AD16C4T_CHMODE_INPUT_INDIRECT
            @arg @ref MD_AD16C4T_CHMODE_INPUT_TRC
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_chmr2_output_cc3ssel(AD16C4T_TypeDef *timx, uint32_t ChannelMode)
{
  MODIFY_REG(timx->CHMR2, AD16C4T_CHMR2_OUTPUT_CC3SSEL_MSK, (ChannelMode << AD16C4T_CHMR2_OUTPUT_CC3SSEL_POSS));
}

/**
  * @brief  Get timer cpture/compare 3 selection.
  * @param  timx AD16C4T instance
  * @retval Timer cpture/compare 3 selection.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_chmr2_output_cc3ssel(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR2, AD16C4T_CHMR2_OUTPUT_CC3SSEL_MSK) >> AD16C4T_CHMR2_OUTPUT_CC3SSEL_POSS);
}

/** 
  * @brief  Timer input capture 4 filter setup.
  * @param  timx AD16C4T instance
  * @param  InputFliter Input capture filter
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV1
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV1N2
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV1N4
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV1N8
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV2N6
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV2N8
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV4N6
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV4N8
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV8N6
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV8N8
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV16N5
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV16N6
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV16N8
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV32N5
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV32N6
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV32N8
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_chmr2_input_i4flt(AD16C4T_TypeDef *timx, uint32_t InputFliter)
{
  MODIFY_REG(timx->CHMR2, AD16C4T_CHMR2_INPUT_I4FLT_MSK, (InputFliter << AD16C4T_CHMR2_INPUT_I4FLT_POSS));
}

/**
  * @brief  Get timer input capture 4 filter.
  * @param  timx AD16C4T instance
  * @retval Timer input capture 4 filter.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_chmr2_input_i4flt(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR2, AD16C4T_CHMR2_INPUT_I4FLT_MSK) >> AD16C4T_CHMR2_INPUT_I4FLT_POSS);
}

/** 
  * @brief  Timer input capture 4 prescaler setup.
  * @param  timx AD16C4T instance
  * @param  InputPrescale Input capture prescaler
            @arg @ref MD_AD16C4T_INPUTPRESCALE_DIV1
            @arg @ref MD_AD16C4T_INPUTPRESCALE_DIV2
            @arg @ref MD_AD16C4T_INPUTPRESCALE_DIV4
            @arg @ref MD_AD16C4T_INPUTPRESCALE_DIV8
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_chmr2_input_i4pres(AD16C4T_TypeDef *timx, uint32_t InputPrescale)
{
  MODIFY_REG(timx->CHMR2, AD16C4T_CHMR2_INPUT_I4PRES_MSK, (InputPrescale << AD16C4T_CHMR2_INPUT_I4PRES_POSS));
}

/**
  * @brief  Get timer input capture 4 prescaler.
  * @param  timx AD16C4T instance
  * @retval Timer input capture 4 prescaler.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_chmr2_input_i4pres(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR2, AD16C4T_CHMR2_INPUT_I4PRES_MSK) >> AD16C4T_CHMR2_INPUT_I4PRES_POSS);
}

/** 
  * @brief  Timer cpture/compare 4 selection setup.
  * @param  timx AD16C4T instance
  * @param  ChannelMode Channel mode selection
            @arg @ref MD_AD16C4T_CHMODE_OUTPUT
            @arg @ref MD_AD16C4T_CHMODE_INPUT_DIRECT
            @arg @ref MD_AD16C4T_CHMODE_INPUT_INDIRECT
            @arg @ref MD_AD16C4T_CHMODE_INPUT_TRC
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_chmr2_input_cc4ssel(AD16C4T_TypeDef *timx, uint32_t ChannelMode)
{
  MODIFY_REG(timx->CHMR2, AD16C4T_CHMR2_INPUT_CC4SSEL_MSK, (ChannelMode << AD16C4T_CHMR2_INPUT_CC4SSEL_POSS));
}

/**
  * @brief  Get timer cpture/compare 4 selection.
  * @param  timx AD16C4T instance
  * @retval Timer cpture/compare 4 selection.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_chmr2_input_cc4ssel(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR2, AD16C4T_CHMR2_INPUT_CC4SSEL_MSK) >> AD16C4T_CHMR2_INPUT_CC4SSEL_POSS);
}

/** 
  * @brief  Timer input capture 3 filter setup.
  * @param  timx AD16C4T instance
  * @param  InputFliter Input capture filter
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV1
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV1N2
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV1N4
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV1N8
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV2N6
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV2N8
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV4N6
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV4N8
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV8N6
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV8N8
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV16N5
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV16N6
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV16N8
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV32N5
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV32N6
            @arg @ref MD_AD16C4T_INPUTFILTER_FDIV32N8
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_chmr2_input_i3flt(AD16C4T_TypeDef *timx, uint32_t InputFliter)
{
  MODIFY_REG(timx->CHMR2, AD16C4T_CHMR2_INPUT_I3FLT_MSK, (InputFliter << AD16C4T_CHMR2_INPUT_I3FLT_POSS));
}

/**
  * @brief  Get timer input capture 3 filter.
  * @param  timx AD16C4T instance
  * @retval Timer input capture 3 filter.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_chmr2_input_i3flt(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR2, AD16C4T_CHMR2_INPUT_I3FLT_MSK) >> AD16C4T_CHMR2_INPUT_I3FLT_POSS);
}

/** 
  * @brief  Timer input capture 3 prescaler setup.
  * @param  timx AD16C4T instance
  * @param  InputPrescale Input capture prescaler
            @arg @ref MD_AD16C4T_INPUTPRESCALE_DIV1
            @arg @ref MD_AD16C4T_INPUTPRESCALE_DIV2
            @arg @ref MD_AD16C4T_INPUTPRESCALE_DIV4
            @arg @ref MD_AD16C4T_INPUTPRESCALE_DIV8
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_chmr2_input_i3pres(AD16C4T_TypeDef *timx, uint32_t InputPrescale)
{
  MODIFY_REG(timx->CHMR2, AD16C4T_CHMR2_INPUT_I3PRES_MSK, (InputPrescale << AD16C4T_CHMR2_INPUT_I3PRES_POSS));
}

/**
  * @brief  Get timer input capture 3 prescaler.
  * @param  timx AD16C4T instance
  * @retval Timer input capture 3 prescaler.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_chmr2_input_i3pres(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR2, AD16C4T_CHMR2_INPUT_I3PRES_MSK) >> AD16C4T_CHMR2_INPUT_I3PRES_POSS);
}

/** 
  * @brief  Timer cpture/compare 3 selection setup.
  * @param  timx AD16C4T instance
  * @param  ChannelMode Channel mode selection
            @arg @ref MD_AD16C4T_CHMODE_OUTPUT
            @arg @ref MD_AD16C4T_CHMODE_INPUT_DIRECT
            @arg @ref MD_AD16C4T_CHMODE_INPUT_INDIRECT
            @arg @ref MD_AD16C4T_CHMODE_INPUT_TRC
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_chmr2_input_cc3ssel(AD16C4T_TypeDef *timx, uint32_t ChannelMode)
{
  MODIFY_REG(timx->CHMR2, AD16C4T_CHMR2_INPUT_CC3SSEL_MSK, (ChannelMode << AD16C4T_CHMR2_INPUT_CC3SSEL_POSS));
}

/**
  * @brief  Get timer cpture/compare 3 selection.
  * @param  timx AD16C4T instance
  * @retval Timer cpture/compare 3 selection.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_chmr2_input_cc3ssel(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CHMR2, AD16C4T_CHMR2_INPUT_CC3SSEL_MSK) >> AD16C4T_CHMR2_INPUT_CC3SSEL_POSS);
}

/**
  * @brief  Timer CCEP setup.
  * @param  timx AD16C4T instance
  * @param  value (CC4NPOL | CC4POL | CC4EN | CC3NPOL | CC3NEN | CC3POL | CC3EN | CC2NPOL |
  *                CC2NEN | CC2POL | CC2EN | CC1NPOL | CC1NEN | CC1POL | CC1EN )
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_ccep(AD16C4T_TypeDef *timx, uint32_t value)
{
  WRITE_REG(timx->CCEP, value);
}

/**
  * @brief  GET Timer CCEP register value.
  * @param  timx AD16C4T instance
  * @retval Timer CCEP register value.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_ccep(AD16C4T_TypeDef *timx)
{
  return (READ_REG(timx->CCEP));
}

/** 
  * @brief  Timer capture/compare 4 complementary output polarity setup.
  * @param  timx AD16C4T instance
  * @param  OutputPolarity Output polarity
            @arg @ref MD_AD16C4T_OUTPUTPOLARITY_HIGH
            @arg @ref MD_AD16C4T_OUTPUTPOLARITY_LOW
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_ccep_cc4npol(AD16C4T_TypeDef *timx, uint32_t OutputPolarity)
{
  MODIFY_REG(timx->CCEP, AD16C4T_CCEP_CC4NPOL_MSK, (OutputPolarity << AD16C4T_CCEP_CC4NPOL_POS));
}

/**
  * @brief  Get timer capture/compare 4 complementary output polarity.
  * @param  timx AD16C4T instance
  * @retval Timer capture/compare 4 complementary output polarity.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_ccep_cc4npol(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CCEP, AD16C4T_CCEP_CC4NPOL_MSK) >> AD16C4T_CCEP_CC4NPOL_POS);
}

/** 
  * @brief  Timer capture/compare 4 output polarity setup.
  * @param  timx AD16C4T instance
  * @param  OutputPolarity Output polarity
            @arg @ref MD_AD16C4T_OUTPUTPOLARITY_HIGH
            @arg @ref MD_AD16C4T_OUTPUTPOLARITY_LOW
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_ccep_cc4pol(AD16C4T_TypeDef *timx, uint32_t OutputPolarity)
{
  MODIFY_REG(timx->CCEP, AD16C4T_CCEP_CC4POL_MSK, (OutputPolarity << AD16C4T_CCEP_CC4POL_POS));
}

/**
  * @brief  Get timer capture/compare 4 output polarity.
  * @param  timx AD16C4T instance
  * @retval Timer capture/compare 4 output polarity.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_ccep_cc4pol(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CCEP, AD16C4T_CCEP_CC4POL_MSK) >> AD16C4T_CCEP_CC4POL_POS);
}

/**
  * @brief  Timer Capture/Compare 4 output enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_ccep_cc4en(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->CCEP, AD16C4T_CCEP_CC4EN_MSK);
}

/**
  * @brief  Timer Capture/Compare 4 output disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_ccep_cc4en(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->CCEP, AD16C4T_CCEP_CC4EN_MSK);
}

/**
  * @brief  Indicates whether the timer Capture/Compare 4 output is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_ccep_cc4en(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CCEP, AD16C4T_CCEP_CC4EN_MSK) == (AD16C4T_CCEP_CC4EN_MSK));
}

/** 
  * @brief  Timer capture/compare 3 complementary output polarity setup.
  * @param  timx AD16C4T instance
  * @param  OutputPolarity Output polarity
            @arg @ref MD_AD16C4T_OUTPUTPOLARITY_HIGH
            @arg @ref MD_AD16C4T_OUTPUTPOLARITY_LOW
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_ccep_cc3npol(AD16C4T_TypeDef *timx, uint32_t OutputPolarity)
{
  MODIFY_REG(timx->CCEP, AD16C4T_CCEP_CC3NPOL_MSK, (OutputPolarity << AD16C4T_CCEP_CC3NPOL_POS));
}

/**
  * @brief  Get timer capture/compare 3 complementary output polarity.
  * @param  timx AD16C4T instance
  * @retval Timer capture/compare 3 complementary output polarity.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_ccep_cc3npol(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CCEP, AD16C4T_CCEP_CC3NPOL_MSK) >> AD16C4T_CCEP_CC3NPOL_POS);
}

/**
  * @brief  Timer Capture/Compare 3 complementary output enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_ccep_cc3nen(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->CCEP, AD16C4T_CCEP_CC3NEN_MSK);
}

/**
  * @brief  Timer Capture/Compare 3 complementary output disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_ccep_cc3nen(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->CCEP, AD16C4T_CCEP_CC3NEN_MSK);
}

/**
  * @brief  Indicates whether the timer Capture/Compare 3 complementary output is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_ccep_cc3nen(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CCEP, AD16C4T_CCEP_CC3NEN_MSK) == (AD16C4T_CCEP_CC3NEN_MSK));
}

/** 
  * @brief  Timer capture/compare 3 output polarity setup.
  * @param  timx AD16C4T instance
  * @param  OutputPolarity Output polarity
            @arg @ref MD_AD16C4T_OUTPUTPOLARITY_HIGH
            @arg @ref MD_AD16C4T_OUTPUTPOLARITY_LOW
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_ccep_cc3pol(AD16C4T_TypeDef *timx, uint32_t OutputPolarity)
{
  MODIFY_REG(timx->CCEP, AD16C4T_CCEP_CC3POL_MSK, (OutputPolarity << AD16C4T_CCEP_CC3POL_POS));
}

/**
  * @brief  Get timer capture/compare 3 output polarity.
  * @param  timx AD16C4T instance
  * @retval Timer capture/compare 3 output polarity.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_ccep_cc3pol(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CCEP, AD16C4T_CCEP_CC3POL_MSK) >> AD16C4T_CCEP_CC3POL_POS);
}

/**
  * @brief  Timer Capture/Compare 3 output enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_ccep_cc3en(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->CCEP, AD16C4T_CCEP_CC3EN_MSK);
}

/**
  * @brief  Timer Capture/Compare 3 output disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_ccep_cc3en(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->CCEP, AD16C4T_CCEP_CC3EN_MSK);
}

/**
  * @brief  Indicates whether the timer Capture/Compare 3 output is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_ccep_cc3en(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CCEP, AD16C4T_CCEP_CC3EN_MSK) == (AD16C4T_CCEP_CC3EN_MSK));
}

/** 
  * @brief  Timer capture/compare 2 complementary output polarity setup.
  * @param  timx AD16C4T instance
  * @param  OutputPolarity Output polarity
            @arg @ref MD_AD16C4T_OUTPUTPOLARITY_HIGH
            @arg @ref MD_AD16C4T_OUTPUTPOLARITY_LOW
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_ccep_cc2npol(AD16C4T_TypeDef *timx, uint32_t OutputPolarity)
{
  MODIFY_REG(timx->CCEP, AD16C4T_CCEP_CC2NPOL_MSK, (OutputPolarity << AD16C4T_CCEP_CC2NPOL_POS));
}

/**
  * @brief  Get timer capture/compare 2 complementary output polarity.
  * @param  timx AD16C4T instance
  * @retval Timer capture/compare 2 complementary output polarity.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_ccep_cc2npol(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CCEP, AD16C4T_CCEP_CC2NPOL_MSK) >> AD16C4T_CCEP_CC2NPOL_POS);
}

/**
  * @brief  Timer Capture/Compare 2 complementary output enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_ccep_cc2nen(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->CCEP, AD16C4T_CCEP_CC2NEN_MSK);
}

/**
  * @brief  Timer Capture/Compare 2 complementary output disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_ccep_cc2nen(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->CCEP, AD16C4T_CCEP_CC2NEN_MSK);
}

/**
  * @brief  Indicates whether the timer Capture/Compare 2 complementary output is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_ccep_cc2nen(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CCEP, AD16C4T_CCEP_CC2NEN_MSK) == (AD16C4T_CCEP_CC2NEN_MSK));
}

/** 
  * @brief  Timer capture/compare 2 output polarity setup.
  * @param  timx AD16C4T instance
  * @param  OutputPolarity Output polarity
            @arg @ref MD_AD16C4T_OUTPUTPOLARITY_HIGH
            @arg @ref MD_AD16C4T_OUTPUTPOLARITY_LOW
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_ccep_cc2pol(AD16C4T_TypeDef *timx, uint32_t OutputPolarity)
{
  MODIFY_REG(timx->CCEP, AD16C4T_CCEP_CC2POL_MSK, (OutputPolarity << AD16C4T_CCEP_CC2POL_POS));
}

/**
  * @brief  Get timer capture/compare 2 output polarity.
  * @param  timx AD16C4T instance
  * @retval Timer capture/compare 2 output polarity.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_ccep_cc2pol(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CCEP, AD16C4T_CCEP_CC2POL_MSK) >> AD16C4T_CCEP_CC2POL_POS);
}

/**
  * @brief  Timer Capture/Compare 2 output enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_ccep_cc2en(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->CCEP, AD16C4T_CCEP_CC2EN_MSK);
}

/**
  * @brief  Timer Capture/Compare 2 output disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_ccep_cc2en(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->CCEP, AD16C4T_CCEP_CC2EN_MSK);
}

/**
  * @brief  Indicates whether the timer Capture/Compare 2 output is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_ccep_cc2en(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CCEP, AD16C4T_CCEP_CC2EN_MSK) == (AD16C4T_CCEP_CC2EN_MSK));
}

/** 
  * @brief  Timer capture/compare 1 complementary output polarity setup.
  * @param  timx AD16C4T instance
  * @param  OutputPolarity Output polarity
            @arg @ref MD_AD16C4T_OUTPUTPOLARITY_HIGH
            @arg @ref MD_AD16C4T_OUTPUTPOLARITY_LOW
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_ccep_cc1npol(AD16C4T_TypeDef *timx, uint32_t OutputPolarity)
{
  MODIFY_REG(timx->CCEP, AD16C4T_CCEP_CC1NPOL_MSK, (OutputPolarity << AD16C4T_CCEP_CC1NPOL_POS));
}

/**
  * @brief  Get timer capture/compare 1 complementary output polarity.
  * @param  timx AD16C4T instance
  * @retval Timer capture/compare 1 complementary output polarity.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_ccep_cc1npol(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CCEP, AD16C4T_CCEP_CC1NPOL_MSK) >> AD16C4T_CCEP_CC1NPOL_POS);
}

/**
  * @brief  Timer Capture/Compare 1 complementary output enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_ccep_cc1nen(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->CCEP, AD16C4T_CCEP_CC1NEN_MSK);
}

/**
  * @brief  Timer Capture/Compare 1 complementary output disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_ccep_cc1nen(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->CCEP, AD16C4T_CCEP_CC1NEN_MSK);
}

/**
  * @brief  Indicates whether the timer Capture/Compare 1 complementary output is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_ccep_cc1nen(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CCEP, AD16C4T_CCEP_CC1NEN_MSK) == (AD16C4T_CCEP_CC1NEN_MSK));
}

/** 
  * @brief  Timer capture/compare 1 output polarity setup.
  * @param  timx AD16C4T instance
  * @param  OutputPolarity Output polarity
            @arg @ref MD_AD16C4T_OUTPUTPOLARITY_HIGH
            @arg @ref MD_AD16C4T_OUTPUTPOLARITY_LOW
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_ccep_cc1pol(AD16C4T_TypeDef *timx, uint32_t OutputPolarity)
{
  MODIFY_REG(timx->CCEP, AD16C4T_CCEP_CC1POL_MSK, (OutputPolarity << AD16C4T_CCEP_CC1POL_POS));
}

/**
  * @brief  Get timer capture/compare 1 output polarity.
  * @param  timx AD16C4T instance
  * @retval Timer capture/compare 1 output polarity.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_ccep_cc1pol(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CCEP, AD16C4T_CCEP_CC1POL_MSK) >> AD16C4T_CCEP_CC1POL_POS);
}

/**
  * @brief  Timer Capture/Compare 1 output enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_ccep_cc1en(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->CCEP, AD16C4T_CCEP_CC1EN_MSK);
}

/**
  * @brief  Timer Capture/Compare 1 output disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_ccep_cc1en(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->CCEP, AD16C4T_CCEP_CC1EN_MSK);
}

/**
  * @brief  Indicates whether the timer Capture/Compare 1 output is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_ccep_cc1en(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CCEP, AD16C4T_CCEP_CC1EN_MSK) == (AD16C4T_CCEP_CC1EN_MSK));
}

/**
  * @brief  Timer COUNT setup.
  * @param  timx AD16C4T instance
  * @param  value COUNT
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_count(AD16C4T_TypeDef *timx, uint32_t value)
{
  WRITE_REG(timx->COUNT, value);
}

/**
  * @brief  GET Timer COUNT register value.
  * @param  timx AD16C4T instance
  * @retval Timer COUNT register value.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_count(AD16C4T_TypeDef *timx)
{
  return (READ_REG(timx->COUNT));
}

/** 
  * @brief  Timer counter value setup.
  * @param  timx AD16C4T instance
  * @param  counter Counter value (between Min_Data=0 and Max_Data=0xFFFF)
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_count_cntv(AD16C4T_TypeDef *timx, uint32_t counter)
{
  MODIFY_REG(timx->COUNT, AD16C4T_COUNT_CNTV_MSK, counter);
}

/**
  * @brief  Get timer counter value.
  * @param  timx AD16C4T instance
  * @retval Timer counter value.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_cnt_cntv(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->COUNT, AD16C4T_COUNT_CNTV_MSK) >> AD16C4T_COUNT_CNTV_POSS);
}

/**
  * @brief  Timer PRES setup.
  * @param  timx AD16C4T instance
  * @param  value PRES
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_pres(AD16C4T_TypeDef *timx, uint32_t value)
{
  WRITE_REG(timx->PRES, value);
}

/**
  * @brief  GET Timer PRES register value.
  * @param  timx AD16C4T instance
  * @retval Timer PRES register value.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_pres(AD16C4T_TypeDef *timx)
{
  return (READ_REG(timx->PRES));
}

/** 
  * @brief  Timer prescaler value setup.
  * @param  timx AD16C4T instance
  * @param  prescaler Prescaler value (between Min_Data=0 and Max_Data=0xFFFF)
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_pres_pscv(AD16C4T_TypeDef *timx, uint32_t prescaler)
{
  MODIFY_REG(timx->PRES, AD16C4T_PRES_PSCV_MSK, prescaler);
}

/**
  * @brief  Get timer prescaler value.
  * @param  timx AD16C4T instance
  * @retval Timer prescaler value.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_pres_pscv(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->PRES, AD16C4T_PRES_PSCV_MSK) >> AD16C4T_PRES_PSCV_POSS);
}

/**
  * @brief  Timer AR setup.
  * @param  timx AD16C4T instance
  * @param  value AR
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_ar(AD16C4T_TypeDef *timx, uint32_t value)
{
  WRITE_REG(timx->AR, value);
}

/**
  * @brief  GET Timer AR register value.
  * @param  timx AD16C4T instance
  * @retval Timer AR register value.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_ar(AD16C4T_TypeDef *timx)
{
  return (READ_REG(timx->AR));
}

/** 
  * @brief  Timer auto-reload value setup.
  * @param  timx AD16C4T instance
  * @param  reload Auto-reload value (between Min_Data=0 and Max_Data=0xFFFF)
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_ar_arv(AD16C4T_TypeDef *timx, uint32_t reload)
{
  MODIFY_REG(timx->AR, AD16C4T_AR_ARV_MSK, reload);
}

/**
  * @brief  Get timer auto-reload value.
  * @param  timx AD16C4T instance
  * @retval Timer auto-reload value.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_ar_arv(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->AR, AD16C4T_AR_ARV_MSK) >> AD16C4T_AR_ARV_POSS);
}

/**
  * @brief  Timer REPAR setup.
  * @param  timx AD16C4T instance
  * @param  value REPAR
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_rcr(AD16C4T_TypeDef *timx, uint32_t value)
{
  WRITE_REG(timx->REPAR, value);
}

/**
  * @brief  GET Timer REPAR register value.
  * @param  timx AD16C4T instance
  * @retval Timer REPAR register value.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_repar(AD16C4T_TypeDef *timx)
{
  return (READ_REG(timx->REPAR));
}

/** 
  * @brief  Timer repetition counter value setup.
  * @param  timx AD16C4T instance
  * @param  repetition Repetition counter value (between Min_Data=0 and Max_Data=0xFF)
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_repar_repv(AD16C4T_TypeDef *timx, uint32_t repetition)
{
  MODIFY_REG(timx->REPAR, AD16C4T_REPAR_REPV_MSK, repetition);
}

/**
  * @brief  Get timer repetition counter value.
  * @param  timx AD16C4T instance
  * @retval Timer repetition counter value.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_repar_repv(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->REPAR, AD16C4T_REPAR_REPV_MSK) >> AD16C4T_REPAR_REPV_POSS);
}

/**
  * @brief  Timer CCVAL1 setup.
  * @param  timx AD16C4T instance
  * @param  value CCVAL1
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_ccval1(AD16C4T_TypeDef *timx, uint32_t value)
{
  WRITE_REG(timx->CCVAL1, value);
}

/**
  * @brief  GET Timer CCVAL1 register value.
  * @param  timx AD16C4T instance
  * @retval Timer CCVAL1 register value.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_ccval1(AD16C4T_TypeDef *timx)
{
  return (READ_REG(timx->CCVAL1));
}

/** 
  * @brief  Timer capture/compare value 1 setup.
  * @param  timx AD16C4T instance
  * @param  CapCompValue Capture/Compare value 1 (between Min_Data=0 and Max_Data=0xFFFF)
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_ccval1_ccrv1(AD16C4T_TypeDef *timx, uint32_t CapCompValue)
{
  MODIFY_REG(timx->CCVAL1, AD16C4T_CCVAL1_CCRV1_MSK, CapCompValue);
}

/**
  * @brief  Get timer capture/compare value 1.
  * @param  timx AD16C4T instance
  * @retval Timer capture/compare value 1.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_ccval1_ccrv1(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CCVAL1, AD16C4T_CCVAL1_CCRV1_MSK) >> AD16C4T_CCVAL1_CCRV1_POSS);
}

/**
  * @brief  Timer CCVAL2 setup.
  * @param  timx AD16C4T instance
  * @param  value CCVAL2
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_ccval2(AD16C4T_TypeDef *timx, uint32_t value)
{
  WRITE_REG(timx->CCVAL2, value);
}

/**
  * @brief  GET Timer CCVAL2 register value.
  * @param  timx AD16C4T instance
  * @retval Timer CCVAL2 register value.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_ccval2(AD16C4T_TypeDef *timx)
{
  return (READ_REG(timx->CCVAL2));
}

/** 
  * @brief  Timer capture/compare value 2 setup.
  * @param  timx AD16C4T instance
  * @param  CapCompValue Capture/Compare value 2 (between Min_Data=0 and Max_Data=0xFFFF)
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_ccval2_ccrv2(AD16C4T_TypeDef *timx, uint32_t CapCompValue)
{
  MODIFY_REG(timx->CCVAL2, AD16C4T_CCVAL2_CCRV2_MSK, CapCompValue);
}

/**
  * @brief  Get timer capture/compare value 2.
  * @param  timx AD16C4T instance
  * @retval Timer capture/compare value 2.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_ccval2_ccrv2(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CCVAL2, AD16C4T_CCVAL2_CCRV2_MSK) >> AD16C4T_CCVAL2_CCRV2_POSS);
}

/**
  * @brief  Timer CCVAL3 setup.
  * @param  timx AD16C4T instance
  * @param  value CCVAL3
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_ccval3(AD16C4T_TypeDef *timx, uint32_t value)
{
  WRITE_REG(timx->CCVAL3, value);
}

/**
  * @brief  GET Timer CCVAL3 register value.
  * @param  timx AD16C4T instance
  * @retval Timer CCVAL3 register value.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_ccval3(AD16C4T_TypeDef *timx)
{
  return (READ_REG(timx->CCVAL3));
}

/** 
  * @brief  Timer capture/compare value 3 setup.
  * @param  timx AD16C4T instance
  * @param  CapCompValue Capture/Compare value 3 (between Min_Data=0 and Max_Data=0xFFFF)
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_ccval3_ccrv3(AD16C4T_TypeDef *timx, uint32_t CapCompValue)
{
  MODIFY_REG(timx->CCVAL3, AD16C4T_CCVAL3_CCRV3_MSK, CapCompValue);
}

/**
  * @brief  Get timer capture/compare value 3.
  * @param  timx AD16C4T instance
  * @retval Timer capture/compare value 3.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_ccval3_ccrv3(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CCVAL3, AD16C4T_CCVAL3_CCRV3_MSK) >> AD16C4T_CCVAL3_CCRV3_POSS);
}

/**
  * @brief  Timer CCVAL4 setup.
  * @param  timx AD16C4T instance
  * @param  value CCVAL4
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_ccval4(AD16C4T_TypeDef *timx, uint32_t value)
{
  WRITE_REG(timx->CCVAL4, value);
}

/**
  * @brief  GET Timer CCVAL4 register value.
  * @param  timx AD16C4T instance
  * @retval Timer CCVAL4 register value.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_ccval4(AD16C4T_TypeDef *timx)
{
  return (READ_REG(timx->CCVAL4));
}

/** 
  * @brief  Timer capture/compare value 4 setup.
  * @param  timx AD16C4T instance
  * @param  CapCompValue Capture/Compare value 4 (between Min_Data=0 and Max_Data=0xFFFF)
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_ccval4_ccrv4(AD16C4T_TypeDef *timx, uint32_t CapCompValue)
{
  MODIFY_REG(timx->CCVAL4, AD16C4T_CCVAL4_CCRV4_MSK, CapCompValue);
}

/**
  * @brief  Get timer capture/compare value 4.
  * @param  timx AD16C4T instance
  * @retval Timer capture/compare value 4.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_ccval4_ccrv4(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->CCVAL4, AD16C4T_CCVAL4_CCRV4_MSK) >> AD16C4T_CCVAL4_CCRV4_POSS);
}

/**
  * @brief  Timer BDCFG setup.
  * @param  timx AD16C4T instance
  * @param  value (GOEN | AOEN | BRKP | BRKEN | OFFSSR | OFFSSI | LOCKLVL | DT)
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_bdcfg(AD16C4T_TypeDef *timx, uint32_t value)
{
  WRITE_REG(timx->BDCFG, value);
}

/**
  * @brief  GET Timer BDCFG register value.
  * @param  timx AD16C4T instance
  * @retval Timer BDCFG register value.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_bdcfg(AD16C4T_TypeDef *timx)
{
  return (READ_REG(timx->BDCFG));
}

/**
  * @brief  Timer main output enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_bdcfg_goen(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->BDCFG, AD16C4T_BDCFG_GOEN_MSK);
}

/**
  * @brief  Timer main output disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_bdcfg_goen(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->BDCFG, AD16C4T_BDCFG_GOEN_MSK);
}

/**
  * @brief  Indicates whether the timer main output is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_bdcfg_goen(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->BDCFG, AD16C4T_BDCFG_GOEN_MSK) == (AD16C4T_BDCFG_GOEN_MSK));
}

/**
  * @brief  Timer automatic output enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_bdcfg_aoen(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->BDCFG, AD16C4T_BDCFG_AOEN_MSK);
}

/**
  * @brief  Timer automatic output disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_bdcfg_aoen(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->BDCFG, AD16C4T_BDCFG_AOEN_MSK);
}

/**
  * @brief  Indicates whether the timer automatic output is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_bdcfg_aoen(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->BDCFG, AD16C4T_BDCFG_AOEN_MSK) == (AD16C4T_BDCFG_AOEN_MSK));
}

/** 
  * @brief  Timer break polarity setup.
  * @param  timx AD16C4T instance
  * @param  BreakPolarity Break polarity
  *         @arg @ref MD_AD16C4T_BREAKPOLARITY_LOW
  *         @arg @ref MD_AD16C4T_BREAKPOLARITY_HIGH
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_bdcfg_brkp(AD16C4T_TypeDef *timx, uint32_t BreakPolarity)
{
  MODIFY_REG(timx->BDCFG, AD16C4T_BDCFG_BRKP_MSK, BreakPolarity);
}

/**
  * @brief  Get timer break polarity.
  * @param  timx AD16C4T instance
  * @retval Timer break polarity.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_bdcfg_brkp(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->BDCFG, AD16C4T_BDCFG_BRKP_MSK) >> AD16C4T_BDCFG_BRKP_POS);
}

/**
  * @brief  Timer break enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_bdcfg_brken(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->BDCFG, AD16C4T_BDCFG_BRKEN_MSK);
}

/**
  * @brief  Timer break disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_bdcfg_brken(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->BDCFG, AD16C4T_BDCFG_BRKEN_MSK);
}

/**
  * @brief  Indicates whether the timer break is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_bdcfg_brken(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->BDCFG, AD16C4T_BDCFG_BRKEN_MSK) == (AD16C4T_BDCFG_BRKEN_MSK));
}

/** 
  * @brief  Timer off-state selection for run mode setup.
  * @param  timx AD16C4T instance
  * @param  OffStateRun Off-state selection for run mode
  *         @arg @ref MD_AD16C4T_OFFSTATERUN_DISABLE
  *         @arg @ref MD_AD16C4T_OFFSTATERUN_ENABLE
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_bdcfg_offssr(AD16C4T_TypeDef *timx, uint32_t OffStateRun)
{
  MODIFY_REG(timx->BDCFG, AD16C4T_BDCFG_OFFSSR_MSK, OffStateRun);
}

/**
  * @brief  Get timer off-state selection for run mode.
  * @param  timx AD16C4T instance
  * @retval Timer off-state selection for run mode.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_bdcfg_offssr(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->BDCFG, AD16C4T_BDCFG_OFFSSR_MSK) >> AD16C4T_BDCFG_OFFSSR_POS);
}

/** 
  * @brief  Timer off-state selection for idle mode setup.
  * @param  timx AD16C4T instance
  * @param  OffStateIdle Off-state selection for idle mode
  *         @arg @ref MD_AD16C4T_OFFSTATEIDLE_DISABLE
  *         @arg @ref MD_AD16C4T_OFFSTATEIDLE_ENABLE
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_bdcfg_offssi(AD16C4T_TypeDef *timx, uint32_t OffStateIdle)
{
  MODIFY_REG(timx->BDCFG, AD16C4T_BDCFG_OFFSSI_MSK, OffStateIdle);
}

/**
  * @brief  Get timer off-state selection for idle mode.
  * @param  timx AD16C4T instance
  * @retval Timer off-state selection for idle mode.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_bdcfg_offssi(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->BDCFG, AD16C4T_BDCFG_OFFSSI_MSK) >> AD16C4T_BDCFG_OFFSSI_POS);
}

/** 
  * @brief  Timer lock configuration setup.
  * @param  timx AD16C4T instance
  * @param  LockLevel Lock configuration
  *         @arg @ref MD_AD16C4T_LOCKLEVEL_0
  *         @arg @ref MD_AD16C4T_LOCKLEVEL_1
  *         @arg @ref MD_AD16C4T_LOCKLEVEL_2
  *         @arg @ref MD_AD16C4T_LOCKLEVEL_3
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_bdcfg_locklvl(AD16C4T_TypeDef *timx, uint32_t LockLevel)
{
  MODIFY_REG(timx->BDCFG, AD16C4T_BDCFG_LOCKLVL_MSK, LockLevel);
}

/**
  * @brief  Get timer lock configuration.
  * @param  timx AD16C4T instance
  * @retval Timer lock configuration.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_bdcfg_locklvl(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->BDCFG, AD16C4T_BDCFG_LOCKLVL_MSK) >> AD16C4T_BDCFG_LOCKLVL_POSS);
}

/** 
  * @brief  Timer dead-time generator setup.
  * @param  timx AD16C4T instance
  * @param  DeadTime Dead-time generator (between Min_Data=0 and Max_Data=0xFF)
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_bdcfg_dt(AD16C4T_TypeDef *timx, uint32_t DeadTime)
{
  MODIFY_REG(timx->BDCFG, AD16C4T_BDCFG_DT_MSK, DeadTime);
}

/**
  * @brief  Get timer dead-time generator.
  * @param  timx AD16C4T instance
  * @retval Timer dead-time generator.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_bdcfg_dt(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->BDCFG, AD16C4T_BDCFG_DT_MSK) >> AD16C4T_BDCFG_DT_POSS);
}

/**
  * @brief  Timer DMAEN setup.
  * @param  timx AD16C4T instance
  * @param  value (TRGIDE | COMDE | CH4DE | CH3DE | CH2DE | CH1DE | UDE)
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_set_dmaen(AD16C4T_TypeDef *timx, uint32_t value)
{
  WRITE_REG(timx->DMAEN, value);
}

/**
  * @brief  GET Timer DMAEN register value.
  * @param  timx AD16C4T instance
  * @retval Timer DMAEN register value.
  */

__STATIC_INLINE uint32_t md_ad16c4t_get_dmaen(AD16C4T_TypeDef *timx)
{
  return (READ_REG(timx->DMAEN));
}

/**
  * @brief  Timer trigger DMA request enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_dmaen_trgide(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->DMAEN, AD16C4T_DMAEN_TRGIDE_MSK);
}

/**
  * @brief  Timer trigger DMA request disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_dmaen_trgide(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->DMAEN, AD16C4T_DMAEN_TRGIDE_MSK);
}

/**
  * @brief  Indicates whether the timer trigger DMA request is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_dmaen_trgide(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->DMAEN, AD16C4T_DMAEN_TRGIDE_MSK) == (AD16C4T_DMAEN_TRGIDE_MSK));
}

/**
  * @brief  Timer COM DMA request enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_dmaen_comde(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->DMAEN, AD16C4T_DMAEN_COMDE_MSK);
}

/**
  * @brief  Timer COM DMA request disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_dmaen_comde(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->DMAEN, AD16C4T_DMAEN_COMDE_MSK);
}

/**
  * @brief  Indicates whether the timer trigger COM request is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_dmaen_comde(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->DMAEN, AD16C4T_DMAEN_COMDE_MSK) == (AD16C4T_DMAEN_COMDE_MSK));
}

/**
  * @brief  Timer Capture/Compare 4 DMA request enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_dmaen_ch4de(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->DMAEN, AD16C4T_DMAEN_CH4DE_MSK);
}

/**
  * @brief  Timer Capture/Compare 4 DMA request disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_dmaen_ch4de(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->DMAEN, AD16C4T_DMAEN_CH4DE_MSK);
}

/**
  * @brief  Indicates whether the timer Capture/Compare 4 DMA request is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_dmaen_ch4de(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->DMAEN, AD16C4T_DMAEN_CH4DE_MSK) == (AD16C4T_DMAEN_CH4DE_MSK));
}

/**
  * @brief  Timer Capture/Compare 3 DMA request enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_dmaen_ch3de(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->DMAEN, AD16C4T_DMAEN_CH3DE_MSK);
}

/**
  * @brief  Timer Capture/Compare 3 DMA request disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_dmaen_ch3de(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->DMAEN, AD16C4T_DMAEN_CH3DE_MSK);
}

/**
  * @brief  Indicates whether the timer Capture/Compare 3 DMA request is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_dmaen_ch3de(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->DMAEN, AD16C4T_DMAEN_CH3DE_MSK) == (AD16C4T_DMAEN_CH3DE_MSK));
}

/**
  * @brief  Timer Capture/Compare 2 DMA request enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_dmaen_ch2de(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->DMAEN, AD16C4T_DMAEN_CH2DE_MSK);
}

/**
  * @brief  Timer Capture/Compare 2 DMA request disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_dmaen_ch2de(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->DMAEN, AD16C4T_DMAEN_CH2DE_MSK);
}

/**
  * @brief  Indicates whether the timer Capture/Compare 2 DMA request is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_dmaen_ch2de(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->DMAEN, AD16C4T_DMAEN_CH2DE_MSK) == (AD16C4T_DMAEN_CH2DE_MSK));
}

/**
  * @brief  Timer Capture/Compare 1 DMA request enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_dmaen_ch1de(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->DMAEN, AD16C4T_DMAEN_CH1DE_MSK);
}

/**
  * @brief  Timer Capture/Compare 1 DMA request disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_dmaen_ch1de(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->DMAEN, AD16C4T_DMAEN_CH1DE_MSK);
}

/**
  * @brief  Indicates whether the timer Capture/Compare 1 DMA request is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_dmaen_ch1de(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->DMAEN, AD16C4T_DMAEN_CH1DE_MSK) == (AD16C4T_DMAEN_CH1DE_MSK));
}

/**
  * @brief  Timer update DMA request enable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_enable_dmaen_ude(AD16C4T_TypeDef *timx)
{
  SET_BIT(timx->DMAEN, AD16C4T_DMAEN_UDE_MSK);
}

/**
  * @brief  Timer update DMA request disable.
  * @param  timx AD16C4T instance
  * @retval None
  */

__STATIC_INLINE void md_ad16c4t_disable_dmaen_ude(AD16C4T_TypeDef *timx)
{
  CLEAR_BIT(timx->DMAEN, AD16C4T_DMAEN_UDE_MSK);
}

/**
  * @brief  Indicates whether the timer Capture/Compare update DMA request is enabled.
  * @param  timx AD16C4T instance
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t md_ad16c4t_is_enabled_dmaen_ude(AD16C4T_TypeDef *timx)
{
  return (READ_BIT(timx->DMAEN, AD16C4T_DMAEN_UDE_MSK) == (AD16C4T_DMAEN_UDE_MSK));
}
/**
  * @} MD_AD16C4T_Public_Macro
  */

/* Public functions -----------------------------------------------------------*/



/**
  * @} AD16C4T
  */


#endif

/**
  * @} Micro_Driver
  */


#ifdef __cplusplus
}
#endif

#endif
