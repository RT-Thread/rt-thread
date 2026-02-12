/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_tim.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32H76x_78x_TIM_H
#define __N32H76x_78x_TIM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h76x_78x.h"

/*** TIM Structure Definition Start ***/

/** TIM Init structure definition is used with ATIM and GPTIM. **/
typedef struct
{
    uint32_t Prescaler;         /* Specifies the prescaler value used to divide the TIM clock.
                                                                 This parameter can be a number between 0x0000 and 0xFFFF */

    uint32_t CounterMode;       /* Specifies the counter mode.
                                                                 This parameter can be a value of TIM_Counter_Mode */

    uint32_t Period;            /* Specifies the period value to be loaded into the active
                                                                 Auto-Reload Register at the next update event.
                                                                 This parameter must be a number between 0x0000 and 0xFFFF.  */

    uint32_t ClkDiv;            /* Specifies the clock division.
                                                                This parameter can be a value of TIM_Clock_Division_CKD */

    uint32_t RepetCnt;           /* Specifies the repetition counter value. Each time the RCR downcounter
                                                                 reaches zero, an update event is generated and counting restarts
                                                                 from the RCR value (N).
                                                                 This means in PWM mode that (N+1) corresponds to:
                                                                        - the number of PWM periods in edge-aligned mode
                                                                        - the number of half PWM period in center-aligned mode
                                                                 This parameter must be a number between 0x00 and 0xFF.
                                                                 This parameter is valid only for ATIM. */

    uint32_t CapCh1Sel;         /* Channel 1 select capture in */

    uint32_t CapCh2Sel;         /* Channel 2 select capture in */

    uint32_t CapCh3Sel;         /* Channel 3 select capture in */

    uint32_t CapCh4Sel;         /* Channel 4 select capture in */

    uint32_t EtrOrClr;          /* ETR or CLR select as ocrefclear source */
    
    uint32_t CapEtrClrSel;      /* ocrefclear(ETR/CLR) select capture in */
} TIM_TimeBaseInitType;

/** TIM Output Compare Init structure definition **/
typedef struct
{
    uint32_t OCMode;       		  /* Specifies the TIM mode.
                                                             This parameter can be a value of TIM_Output_Compare_and_PWM_modes */

    uint32_t OutputState;  		  /* Specifies the TIM Output Compare state.
                                                             This parameter can be a value of TIM_Output_Compare_state */

    uint32_t OutputNState; 		  /* Specifies the TIM complementary Output Compare state.
                                                             This parameter can be a value of TIM_Output_Compare_N_state
                                                             This parameter is valid for ATIM and GTIMB1-10. */

    uint32_t Pulse;       		  /* Specifies the pulse value to be loaded into the Capture_Compare_Register.
                                                             This parameter can be a number between 0x0000 and 0xFFFF */

    uint32_t OCPolarity;   		  /* Specifies the output polarity.
                                                             This parameter can be a value of TIM_Output_Compare_Polarity */

    uint32_t OCNPolarity;       /* Specifies the complementary output polarity.
                                                             This parameter can be a value of TIM_Output_Compare_N_Polarity
                                                             This parameter is valid for ATIM and GTIMB1-10. */

    uint32_t OCIdleState;       /* Specifies the TIM Output Compare pin state during Idle state.
                                                             This parameter can be a value of TIM_Output_Compare_Idle_State
                                                             This parameter is valid for ATIM and GTIMB1-10. */

    uint32_t OCNIdleState;      /* Specifies the TIM Output Compare pin state during Idle state.
                                                             This parameter can be a value of TIM_Output_Compare_N_Idle_State
                                                             This parameter is valid for ATIM and GTIMB1-10. */
} OCInitType;

/** TIM Input Capture Init structure definition **/
typedef struct
{

    uint32_t Channel;           /* Specifies the TIM channel.
                                                             This parameter can be a value of TIM_Channel */

    uint32_t ICPolarity;        /* Specifies the active edge of the input signal.
                                                             This parameter can be a value of TIM_Input_Capture_Polarity */

    uint32_t ICSelection;       /* Specifies the input.
                                                             This parameter can be a value of TIM_Input_Capture_Selection */

    uint32_t ICPrescaler;       /* Specifies the Input Capture Prescaler.
                                                             This parameter can be a value of TIM_Input_Capture_Prescaler */

    uint32_t ICFilter;          /* Specifies the input capture filter.
                                                             This parameter can be a number between 0x0 and 0xF */
} TIM_ICInitType;

/** BDTR structure definition is used only with TIM1	**/
typedef struct
{

    uint32_t OSSRState;         /* Specifies the Off-State selection used in Run mode.
                                                                 This parameter can be a value of OSSR_Off_State_Selection_for_Run_mode_state */

    uint32_t OSSIState;         /* Specifies the Off-State used in Idle state.
                                                                 This parameter can be a value of OSSI_Off_State_Selection_for_Idle_mode_state */

    uint32_t LOCKLevel;         /* Specifies the LOCK level parameters.
                                                                 This parameter can be a value of Lock_level */

    uint32_t DeadTime;          /* Specifies the delay time between the switching-off and the
                                                                 switching-on of the outputs.
                                                                 This parameter can be a number between 0x00 and 0xFF  */

    uint32_t Break;             /* Specifies whether the TIM Break input is enabled or not.
                                                                 This parameter can be a value of Break_Input_enable_disable */

    uint32_t BreakPolarity;     /* Specifies the TIM Break Input pin polarity.
                                                                 This parameter can be a value of Break_Polarity */

    uint32_t AutomaticOutput;   /* Specifies whether the TIM Automatic Output feature is enabled or not.
                                                                 This parameter can be a value of TIM_AOE_Bit_Set_Reset */

    uint32_t Bidirection;         /* Specifies whether the bidirectional break input enabled or disabled.
                                                                 This parameter can be a value of Enable or disable */

    uint32_t Break2;             /* Specifies whether the TIM Break2 input is enabled or not.
                                                                 This parameter can be a value of Break2_Input_enable_disable */

    uint32_t Break2Polarity;     /* Specifies the TIM Break2 Input pin polarity.
                                                                 This parameter can be a value of Break2_Polarity */

    uint32_t Bidirection2;         /* Specifies whether the bidirectional break2 input enabled or disabled.
                                                                 This parameter can be a value of Enable or disable */   

} TIM_BDTRInitType;

/** Filter structure definition	**/
typedef struct
{
    uint32_t ThreshHold;        /* Specifies the threshold value of filter, the range is [0, 64]. */

    uint32_t WindowSize;        /* Specifies the window size value of filter, the range is [0, 63]. */

    uint32_t Prescaler;         /* Specifies the prescaler value of filter, the range is [0, 65535] */
}TIM_FiltInitType;

/*** TIM Structure Definition End ***/

/*** TIM Macro Definition Start ***/

/** TIM register bit mask definition **/
#define TIM_REG_BIT_MASK                   ((uint32_t)0x00000000)

/** Whether it is an ATIM1-3 device **/
#define IS_ATIM1_4_DEVICE(DEVICE)          (((DEVICE) == ATIM1)  || \
                                            ((DEVICE) == ATIM2)  || \
                                            ((DEVICE) == ATIM3)  || \
                                            ((DEVICE) == ATIM4))

/** Whether it is an GTIMA1-7 device **/
#define IS_GTIMA1_7_DEVICE(DEVICE)          (((DEVICE) == GTIMA1)  || \
                                            ((DEVICE) == GTIMA2)  || \
                                            ((DEVICE) == GTIMA3)  || \
                                            ((DEVICE) == GTIMA4)  || \
                                            ((DEVICE) == GTIMA5)  || \
                                            ((DEVICE) == GTIMA6)  || \
                                            ((DEVICE) == GTIMA7))

/** Whether it is an GTIMB1-10 device **/
#define IS_GTIMB1_3_DEVICE(DEVICE)         (((DEVICE) == GTIMB1)  || \
                                            ((DEVICE) == GTIMB2)  || \
                                            ((DEVICE) == GTIMB3))                                            
/** Whether it is an BTIM1-2 device **/
#define IS_BTIM1_2_DEVICE(DEVICE)          (((DEVICE) == BTIM1)  || \
                                            ((DEVICE) == BTIM2))  
                   
/** TIM_External_Trigger_Prescaler **/
#define TIM_EXT_TRG_PSC_OFF                (TIM_REG_BIT_MASK)
#define TIM_EXT_TRG_PSC_DIV2               (TIM_SMCTRL_EXTPS_0)
#define TIM_EXT_TRG_PSC_DIV4               (TIM_SMCTRL_EXTPS_1)
#define TIM_EXT_TRG_PSC_DIV8               (TIM_SMCTRL_EXTPS)

/** TIM_External_Trigger_Polarity **/
#define TIM_EXT_TRIG_POLARITY_INVERTED     (TIM_SMCTRL_EXTP)
#define TIM_EXT_TRIG_POLARITY_NONINVERTED  (TIM_REG_BIT_MASK)


/** TIM_Counter_Mode **/
#define TIM_CNT_MODE_UP                    (TIM_REG_BIT_MASK) 
#define TIM_CNT_MODE_DOWN                  (TIM_CTRL1_DIR) 
#define TIM_CNT_MODE_CENTER_ALIGN1         (TIM_CTRL1_CAMSEL_0) 
#define TIM_CNT_MODE_CENTER_ALIGN2         (TIM_CTRL1_CAMSEL_1) 
#define TIM_CNT_MODE_CENTER_ALIGN3         (TIM_CTRL1_CAMSEL) 

/** TIM_Clock_Division_CKD **/
#define TIM_CLK_DIV1                       (TIM_REG_BIT_MASK) 
#define TIM_CLK_DIV2                       (TIM_CTRL1_CLKD_0) 
#define TIM_CLK_DIV4                       (TIM_CTRL1_CLKD_1) 

/** TIM_Prescaler_Reload_Mode **/
#define TIM_PSC_RELOAD_MODE_UPDATE         (TIM_REG_BIT_MASK) 
#define TIM_PSC_RELOAD_MODE_IMMEDIATE      (TIM_EVTGEN_UDGN) 

/** Channel 1/2/3/4 & OCxclr select capture in **/
#define TIM_CAPCH1SEL_0                    (TIM_REG_BIT_MASK) 
#define TIM_CAPCH1SEL_1                    (TIM_INSEL_TI1S_0) 
#define TIM_CAPCH1SEL_2                    (TIM_INSEL_TI1S_1) 
#define TIM_CAPCH1SEL_3                    (TIM_INSEL_TI1S_0 | TIM_INSEL_TI1S_1) 
#define TIM_CAPCH1SEL_4                    (TIM_INSEL_TI1S_2) 
#define TIM_CAPCH1SEL_5                    (TIM_INSEL_TI1S_0 | TIM_INSEL_TI1S_2) 
#define TIM_CAPCH1SEL_6                    (TIM_INSEL_TI1S_1 | TIM_INSEL_TI1S_2) 
#define TIM_CAPCH1SEL_7                    (TIM_INSEL_TI1S_0 | TIM_INSEL_TI1S_1 | TIM_INSEL_TI1S_2) 

#define TIM_CAPCH2SEL_0                    (TIM_REG_BIT_MASK) 
#define TIM_CAPCH2SEL_1                    (TIM_INSEL_TI2S_0) 
#define TIM_CAPCH2SEL_2                    (TIM_INSEL_TI2S_1) 
#define TIM_CAPCH2SEL_3                    (TIM_INSEL_TI2S_0 | TIM_INSEL_TI2S_1) 
#define TIM_CAPCH2SEL_4                    (TIM_INSEL_TI2S_2) 
#define TIM_CAPCH2SEL_TIMXCAPLSE           (TIM_CTRL1_C2SEL) 

#define TIM_CAPCH3SEL_0                    (TIM_REG_BIT_MASK) 
#define TIM_CAPCH3SEL_1                    (TIM_INSEL_TI3S_0) 
#define TIM_CAPCH3SEL_TIMXCAPLSI           (TIM_CTRL1_C3SEL) 

#define TIM_CAPCH4SEL_0                    (TIM_REG_BIT_MASK) 
#define TIM_CAPCH4SEL_1                    (TIM_INSEL_TI4S_0) 
#define TIM_CAPCH4SEL_2                    (TIM_INSEL_TI4S_1) 
#define TIM_CAPCH4SEL_TIMXCAPHSEDIV128     (TIM_CTRL1_C4SEL) 

#define TIM_CAPETRSEL_0                    (TIM_REG_BIT_MASK) 
#define TIM_CAPETRSEL_1                    (TIM_INSEL_ETRS_0) 
#define TIM_CAPETRSEL_2                    (TIM_INSEL_ETRS_1) 
#define TIM_CAPETRSEL_3                    (TIM_INSEL_ETRS_0 | TIM_INSEL_ETRS_1) 
#define TIM_CAPETRSEL_4                    (TIM_INSEL_ETRS_2) 
#define TIM_CAPETRSEL_5                    (TIM_INSEL_ETRS_0 | TIM_INSEL_ETRS_2) 
#define TIM_CAPETRSEL_6                    (TIM_INSEL_ETRS_1 | TIM_INSEL_ETRS_2) 
#define TIM_CAPETRSEL_7                    (TIM_INSEL_ETRS_0 | TIM_INSEL_ETRS_1 | TIM_INSEL_ETRS_2) 
#define TIM_CAPETRSEL_8                    (TIM_INSEL_ETRS_3) 
#define TIM_CAPETRSEL_9                    (TIM_INSEL_ETRS_0 | TIM_INSEL_ETRS_3) 
#define TIM_CAPETRSEL_10                   (TIM_INSEL_ETRS_1 | TIM_INSEL_ETRS_3) 
#define TIM_CAPETRSEL_11                   (TIM_INSEL_ETRS_0 | TIM_INSEL_ETRS_1 | TIM_INSEL_ETRS_3) 
#define TIM_CAPETRSEL_12                   (TIM_INSEL_ETRS_2 | TIM_INSEL_ETRS_3) 
#define TIM_CAPETRSEL_13                   (TIM_INSEL_ETRS_0 | TIM_INSEL_ETRS_2 | TIM_INSEL_ETRS_3) 

#define TIM_OCCLRSEL_0                     (TIM_REG_BIT_MASK) 
#define TIM_OCCLRSEL_1                     (TIM_INSEL_CLRS_0) 
#define TIM_OCCLRSEL_2                     (TIM_INSEL_CLRS_1) 
#define TIM_OCCLRSEL_3                     (TIM_INSEL_CLRS_0 | TIM_INSEL_CLRS_1) 
#define TIM_OCCLRSEL_4                     (TIM_INSEL_CLRS_2) 
#define TIM_OCCLRSEL_5                     (TIM_INSEL_CLRS_0 | TIM_INSEL_CLRS_2) 
#define TIM_OCCLRSEL_6                     (TIM_INSEL_CLRS_1 | TIM_INSEL_CLRS_2) 
#define TIM_OCCLRSEL_7                     (TIM_INSEL_CLRS_0 | TIM_INSEL_CLRS_1 | TIM_INSEL_CLRS_2) 
#define TIM_OCCLRSEL_COMP                  (TIM_CTRL1_CLRSEL) 

/** ETR input selection **/
#define TIM_ETRSEL                         (TIM_REG_BIT_MASK) 
#define TIM_CLRSEL                         (TIM_CTRL1_CLRSEL)                                               

/** ITR input selection **/
#define TIM_TRIG_SEL_IN_TR0                (TIM_REG_BIT_MASK) 
#define TIM_TRIG_SEL_IN_TR1                (TIM_INSEL_ITRS_0) 
#define TIM_TRIG_SEL_IN_TR2                (TIM_INSEL_ITRS_1) 
#define TIM_TRIG_SEL_IN_TR3                (TIM_INSEL_ITRS_0 | TIM_INSEL_ITRS_1) 
#define TIM_TRIG_SEL_IN_TR4                (TIM_INSEL_ITRS_2) 
#define TIM_TRIG_SEL_IN_TR5                (TIM_INSEL_ITRS_0 | TIM_INSEL_ITRS_2) 
#define TIM_TRIG_SEL_IN_TR6                (TIM_INSEL_ITRS_1 | TIM_INSEL_ITRS_2) 
#define TIM_TRIG_SEL_IN_TR7                (TIM_INSEL_ITRS_0 | TIM_INSEL_ITRS_1 | TIM_INSEL_ITRS_2) 
#define TIM_TRIG_SEL_IN_TR8                (TIM_INSEL_ITRS_3) 
#define TIM_TRIG_SEL_IN_TR9                (TIM_INSEL_ITRS_0 | TIM_INSEL_ITRS_3) 
#define TIM_TRIG_SEL_IN_TR10               (TIM_INSEL_ITRS_1 | TIM_INSEL_ITRS_3) 
#define TIM_TRIG_SEL_IN_TR11               (TIM_INSEL_ITRS_0 | TIM_INSEL_ITRS_1 | TIM_INSEL_ITRS_3) 
#define TIM_TRIG_SEL_IN_TR12               (TIM_INSEL_ITRS_2 | TIM_INSEL_ITRS_3) 
#define TIM_TRIG_SEL_IN_TR13               (TIM_INSEL_ITRS_0 | TIM_INSEL_ITRS_2 | TIM_INSEL_ITRS_3) 
#define TIM_TRIG_SEL_IN_TR14               (TIM_INSEL_ITRS_1 | TIM_INSEL_ITRS_2 | TIM_INSEL_ITRS_3) 

/** OCCLR input selection **/
#define IS_ITR_SEL(IMPORT)                 (((IMPORT) == TIM_TRIG_SEL_IN_TR0)  || \
                                            ((IMPORT) == TIM_TRIG_SEL_IN_TR1)  || \
                                            ((IMPORT) == TIM_TRIG_SEL_IN_TR2)  || \
                                            ((IMPORT) == TIM_TRIG_SEL_IN_TR3)  || \
                                            ((IMPORT) == TIM_TRIG_SEL_IN_TR4)  || \
                                            ((IMPORT) == TIM_TRIG_SEL_IN_TR5)  || \
                                            ((IMPORT) == TIM_TRIG_SEL_IN_TR6)  || \
                                            ((IMPORT) == TIM_TRIG_SEL_IN_TR7)  || \
                                            ((IMPORT) == TIM_TRIG_SEL_IN_TR8)  || \
                                            ((IMPORT) == TIM_TRIG_SEL_IN_TR9)  || \
                                            ((IMPORT) == TIM_TRIG_SEL_IN_TR10)  || \
                                            ((IMPORT) == TIM_TRIG_SEL_IN_TR11)  || \
                                            ((IMPORT) == TIM_TRIG_SEL_IN_TR12)  || \
                                            ((IMPORT) == TIM_TRIG_SEL_IN_TR13)  || \
                                            ((IMPORT) == TIM_TRIG_SEL_IN_TR14))  

/** TIM_Trigger_Selection **/     
#define TIM_TRIG_SEL_IN_TR                 (TIM_SMCTRL_TSEL_0)
#define TIM_TRIG_SEL_TI1F_ED               (TIM_SMCTRL_TSEL_2)
#define TIM_TRIG_SEL_TI1FP1                (TIM_SMCTRL_TSEL_0 | TIM_SMCTRL_TSEL_2)
#define TIM_TRIG_SEL_TI2FP2                (TIM_SMCTRL_TSEL_1 | TIM_SMCTRL_TSEL_2)
#define TIM_TRIG_SEL_ETRF                  (TIM_SMCTRL_TSEL_0 | TIM_SMCTRL_TSEL_1 | TIM_SMCTRL_TSEL_2)

/** TIM_Output_Compare_and_PWM_modes **/
#define TIM_OCMODE_TIMING                  (TIM_REG_BIT_MASK) 
#define TIM_OCMODE_ACTIVE                  (TIM_CCMOD1_OC1MD_0) 
#define TIM_OCMODE_INACTIVE                (TIM_CCMOD1_OC1MD_1) 
#define TIM_OCMODE_TOGGLE                  (TIM_CCMOD1_OC1MD_0 | TIM_CCMOD1_OC1MD_1) 
#define TIM_FORCED_ACTION_INACTIVE         (TIM_CCMOD1_OC1MD_2) 
#define TIM_FORCED_ACTION_ACTIVE           (TIM_CCMOD1_OC1MD_0 | TIM_CCMOD1_OC1MD_2) 
#define TIM_OCMODE_PWM1                    (TIM_CCMOD1_OC1MD_1 | TIM_CCMOD1_OC1MD_2) 
#define TIM_OCMODE_PWM2                    (TIM_CCMOD1_OC1MD_0 | TIM_CCMOD1_OC1MD_1 | TIM_CCMOD1_OC1MD_2) 
#define TIM_OCMODE_OPMOD_RETRIG1           (TIM_CCMOD1_OC1MD_3) 
#define TIM_OCMODE_OPMOD_RETRIG2           (TIM_CCMOD1_OC1MD_0 | TIM_CCMOD1_OC1MD_3) 
#define TIM_OCMODE_COMBI_PWM1              (TIM_CCMOD1_OC1MD_1 | TIM_CCMOD1_OC1MD_2 | TIM_CCMOD1_OC1MD_3) 
#define TIM_OCMODE_COMBI_PWM2              (TIM_CCMOD1_OC1MD_0 | TIM_CCMOD1_OC1MD_1 | TIM_CCMOD1_OC1MD_2 | TIM_CCMOD1_OC1MD_3) 

/** TIM_Output_Compare_state **/
#define TIM_OUTPUT_STATE_DISABLE           (TIM_REG_BIT_MASK)
#define TIM_OUTPUT_STATE_ENABLE            (TIM_CCEN_CC1EN)

/** TIM_Output_Compare_N_state **/
#define TIM_OUTPUT_NSTATE_DISABLE          (TIM_REG_BIT_MASK)
#define TIM_OUTPUT_NSTATE_ENABLE           (TIM_CCEN_CC1NEN)

/** TIM_Output_Compare_Polarity **/
#define TIM_OC_POLARITY_HIGH               (TIM_REG_BIT_MASK)
#define TIM_OC_POLARITY_LOW                (TIM_CCEN_CC1P)

/** TIM_Output_Compare_N_Polarity **/
#define TIM_OCN_POLARITY_HIGH              (TIM_REG_BIT_MASK)
#define TIM_OCN_POLARITY_LOW               (TIM_CCEN_CC1NP)

/** TIM_Output_Compare_Idle_State **/
#define TIM_OC_IDLE_STATE_SET              (TIM_CTRL2_OI1)
#define TIM_OC_IDLE_STATE_RESET            (TIM_REG_BIT_MASK)

/** TIM_Output_Compare_N_Idle_State **/
#define TIM_OCN_IDLE_STATE_SET             (TIM_CTRL2_OI1N)
#define TIM_OCN_IDLE_STATE_RESET           (TIM_REG_BIT_MASK)

/** TIM_Channel **/
#define TIM_CH_1                           ((uint32_t)0x00000000)
#define TIM_CH_2                           ((uint32_t)0x00000004)
#define TIM_CH_3                           ((uint32_t)0x00000008)
#define TIM_CH_4                           ((uint32_t)0x0000000C)
#define TIM_CH_5                           ((uint32_t)0x00000010)
#define TIM_CH_6                           ((uint32_t)0x00000014)

/** TIM_Iutput_Capture_Polarity **/
#define TIM_IC_POLARITY_RISING             (TIM_REG_BIT_MASK)
#define TIM_IC_POLARITY_FALLING            (TIM_CCEN_CC1P)

/** TIM_Input_Capture_Selection **/
#define TIM_IC_SELECTION_DIRECTTI          (TIM_CCMOD1_CC1SEL_0) /* TIM Input 1, 2, 3 or 4 is selected to be 
                                                                    connected to IC1, IC2, IC3 or IC4, respectively */
#define TIM_IC_SELECTION_INDIRECTTI        (TIM_CCMOD1_CC1SEL_1) /* TIM Input 1, 2, 3 or 4 is selected to be 
                                                                    connected to IC2, IC1, IC4 or IC3, respectively. */
#define TIM_IC_SELECTION_TRC               (TIM_CCMOD1_CC1SEL) /* TIM Input 1, 2, 3 or 4 is selected to be connected to TRC. */

/** TIM_Input_Capture_Prescaler **/
#define TIM_IC_PSC_DIV1                    (TIM_REG_BIT_MASK) /* Capture performed each time an edge is detected on the capture input. */
#define TIM_IC_PSC_DIV2                    (TIM_CCMOD1_IC1PSC_0) /* Capture performed once every 2 events. */
#define TIM_IC_PSC_DIV4                    (TIM_CCMOD1_IC1PSC_1) /* Capture performed once every 4 events. */
#define TIM_IC_PSC_DIV8                    (TIM_CCMOD1_IC1PSC) /* Capture performed once every 8 events. */

/** OSSR_Off_State_Selection_for_Run_mode_state **/
#define TIM_OSSR_STATE_ENABLE              (TIM_BKDT_OSSR)
#define TIM_OSSR_STATE_DISABLE             (TIM_REG_BIT_MASK)

/** OSSI_Off_State_Selection_for_Idle_mode_state **/
#define TIM_OSSI_STATE_ENABLE               (TIM_BKDT_OSSI)
#define TIM_OSSI_STATE_DISABLE              (TIM_REG_BIT_MASK)

/** Lock_level **/
#define TIM_LOCK_LEVEL_OFF                  (TIM_REG_BIT_MASK)
#define TIM_LOCK_LEVEL_1                    (TIM_BKDT_LCKCFG_0)
#define TIM_LOCK_LEVEL_2                    (TIM_BKDT_LCKCFG_1)
#define TIM_LOCK_LEVEL_3                    (TIM_BKDT_LCKCFG)

/** Break_Input_enable_disable **/
#define TIM_BREAK_IN_ENABLE                 (TIM_BKDT_BKEN)
#define TIM_BREAK_IN_DISABLE                (TIM_REG_BIT_MASK)
#define TIM_BREAK2_IN_ENABLE                (TIM_BKDT_BK2EN)
#define TIM_BREAK2_IN_DISABLE               (TIM_REG_BIT_MASK)

/** Break_Polarity **/
#define TIM_BREAK_POLARITY_LOW              (TIM_REG_BIT_MASK)
#define TIM_BREAK_POLARITY_HIGH             (TIM_BKDT_BKP)
#define TIM_BREAK2_POLARITY_LOW             (TIM_REG_BIT_MASK)
#define TIM_BREAK2_POLARITY_HIGH            (TIM_BKDT_BK2P)

/** TIM_AOEN_Bit_Set_Reset **/
#define TIM_AUTO_OUTPUT_ENABLE              (TIM_BKDT_AOEN)
#define TIM_AUTO_OUTPUT_DISABLE             (TIM_REG_BIT_MASK)

/** Bidirectional break input enabled or disabled **/
#define TIM_BREAK_BID_ENABLE                (TIM_BKDT_BRKBID)
#define TIM_BREAK_BID_DISABLE               (TIM_REG_BIT_MASK)

/** Bidirectional break2 input enabled or disabled **/
#define TIM_BREAK2_BID_ENABLE               (TIM_BKDT_BRK2BID)
#define TIM_BREAK2_BID_DISABLE              (TIM_REG_BIT_MASK)

/** Break1 input source **/
#define TIM_BREAK_LOCKUP                    (TIM_CTRL1_LBKPEN)
#define TIM_BREAK_PVD                       (TIM_CTRL1_PBKPEN)
#define TIM_BREAK_SMPAR                     (TIM_CTRL1_SMPARERREN)
#define TIM_BREAK_SMECC                     (TIM_CTRL1_SMECCERREN)
#define TIM_BREAK_IOM                       (TIM_AF1_IOMBRKEN)
#define TIM_BREAK_COMP1                     (TIM_AF1_COMP1BRKEN)
#define TIM_BREAK_COMP2                     (TIM_AF1_COMP2BRKEN)
#define TIM_BREAK_COMP3                     (TIM_AF1_COMP3BRKEN)
#define TIM_BREAK_COMP4                     (TIM_AF1_COMP4BRKEN)
#define TIM_BREAK_DSMU0                     (TIM_AF1_DSMU0BRKEN)
#define TIM_BREAK_DSMU1                     (TIM_AF1_DSMU1BRKEN)
#define TIM_BREAK_DSMU2                     (TIM_AF1_DSMU2BRKEN)
#define TIM_BREAK_DSMU3                     (TIM_AF1_DSMU3BRKEN)

/** System break input **/
#define IS_SYS_BREAK(SOURCE)                (((SOURCE) == TIM_BREAK_LOCKUP)  || \
                                             ((SOURCE) == TIM_BREAK_PVD)     || \
                                             ((SOURCE) == TIM_BREAK_SMPAR)   || \
                                             ((SOURCE) == TIM_BREAK_SMECC)) 
                                            
 /** Polarity of break input from IOM **/
#define TIM_BREAK_SOURCE_POLARITY_INVERT    (TIM_AF1_IOMBRKP | TIM_AF1_COMP1BRKP | TIM_AF1_COMP2BRKP | TIM_AF1_COMP3BRKP | TIM_AF1_COMP4BRKP )
#define TIM_BREAK_SOURCE_POLARITY_NONINVERT (TIM_REG_BIT_MASK)

/** IOM as break2 input **/
#define TIM_BREAK2_IOM                      (TIM_AF2_IOMBRK2EN)
#define TIM_BREAK2_COMP1                    (TIM_AF2_COMP1BRK2EN)
#define TIM_BREAK2_COMP2                    (TIM_AF2_COMP2BRK2EN)
#define TIM_BREAK2_COMP3                    (TIM_AF2_COMP3BRK2EN)
#define TIM_BREAK2_COMP4                    (TIM_AF2_COMP4BRK2EN)
#define TIM_BREAK2_DSMU0                    (TIM_AF2_DSMU0BRK2EN)
#define TIM_BREAK2_DSMU1                    (TIM_AF2_DSMU1BRK2EN)
#define TIM_BREAK2_DSMU2                    (TIM_AF2_DSMU2BRK2EN)
#define TIM_BREAK2_DSMU3                    (TIM_AF2_DSMU3BRK2EN)

 /** Polarity of break2 input from IOM **/
#define TIM_BREAK2_SOURCE_POLARITY_INVERT    (TIM_AF2_IOMBRK2P | TIM_AF2_COMP1BRK2P | TIM_AF2_COMP2BRK2P | TIM_AF2_COMP3BRK2P | TIM_AF2_COMP4BRK2P)
#define TIM_BREAK2_SOURCE_POLARITY_NONINVERT (TIM_REG_BIT_MASK)

/** TIM_interrupt_sources **/
#define TIM_INT_CC1                         (TIM_DINTEN_CC1IEN)
#define TIM_INT_CC2                         (TIM_DINTEN_CC2IEN)
#define TIM_INT_CC3                         (TIM_DINTEN_CC3IEN)
#define TIM_INT_CC4                         (TIM_DINTEN_CC4IEN)
#define TIM_INT_CC5                         (TIM_DINTEN_CC5IEN)
#define TIM_INT_CC6                         (TIM_DINTEN_CC6IEN)
#define TIM_INT_CC7                         (TIM_DINTEN_CC7IEN)
#define TIM_INT_CC8                         (TIM_DINTEN_CC8IEN)
#define TIM_INT_CC9                         (TIM_DINTEN_CC9IEN)
#define TIM_INT_UPDATE                      (TIM_DINTEN_UIEN)
#define TIM_INT_TRIG                        (TIM_DINTEN_TIEN)
#define TIM_INT_BREAK                       (TIM_DINTEN_BIEN)
#define TIM_INT_COM                         (TIM_DINTEN_COMIEN)

/** TIM_interrupt extra flag **/
#define TIM_INT_BREAK2                     (TIM_STS_BITF2)
#define TIM_INT_SYS_BREAK                  (TIM_STS_SBITF)

/** TIM_Event_Source **/
#define TIM_EVT_SRC_CC1                     (TIM_EVTGEN_CC1GN)
#define TIM_EVT_SRC_CC2                     (TIM_EVTGEN_CC2GN)
#define TIM_EVT_SRC_CC3                     (TIM_EVTGEN_CC3GN)
#define TIM_EVT_SRC_CC4                     (TIM_EVTGEN_CC4GN)
#define TIM_EVT_SRC_UPDATE                  (TIM_EVTGEN_UDGN)
#define TIM_EVT_SRC_COM                     (TIM_EVTGEN_CCUDGN)
#define TIM_EVT_SRC_TRIG                    (TIM_EVTGEN_TGN)
#define TIM_EVT_SRC_BREAK                   (TIM_EVTGEN_BGN)
#define TIM_EVT_SRC_BREAK2                  (TIM_EVTGEN_BGN2)

/** TIM_DMA_Base_address **/
#define TIM_DMABASE_CTRL1                   (TIM_REG_BIT_MASK)
#define TIM_DMABASE_CTRL2                   (TIM_DCTRL_DBADDR_0)
#define TIM_DMABASE_STS                     (TIM_DCTRL_DBADDR_1)
#define TIM_DMABASE_EVTGEN                  (TIM_DCTRL_DBADDR_0 | TIM_DCTRL_DBADDR_1)
#define TIM_DMABASE_SMCTRL                  (TIM_DCTRL_DBADDR_2)
#define TIM_DMABASE_DMAINTEN                (TIM_DCTRL_DBADDR_0 | TIM_DCTRL_DBADDR_2)
#define TIM_DMABASE_CAPCMPMOD1              (TIM_DCTRL_DBADDR_1 | TIM_DCTRL_DBADDR_2)
#define TIM_DMABASE_CAPCMPMOD2              (TIM_DCTRL_DBADDR_0 | TIM_DCTRL_DBADDR_1 | TIM_DCTRL_DBADDR_2)
#define TIM_DMABASE_CAPCMPMOD3              (TIM_DCTRL_DBADDR_3)
#define TIM_DMABASE_CAPCMPEN                (TIM_DCTRL_DBADDR_0 | TIM_DCTRL_DBADDR_3)
#define TIM_DMABASE_CAPCMPDAT1              (TIM_DCTRL_DBADDR_1 | TIM_DCTRL_DBADDR_3)
#define TIM_DMABASE_CAPCMPDAT2              (TIM_DCTRL_DBADDR_0 | TIM_DCTRL_DBADDR_1 | TIM_DCTRL_DBADDR_3)
#define TIM_DMABASE_CAPCMPDAT3              (TIM_DCTRL_DBADDR_2 | TIM_DCTRL_DBADDR_3)
#define TIM_DMABASE_CAPCMPDAT4              (TIM_DCTRL_DBADDR_0 | TIM_DCTRL_DBADDR_2 | TIM_DCTRL_DBADDR_3)
#define TIM_DMABASE_CAPCMPDAT5              (TIM_DCTRL_DBADDR_1 | TIM_DCTRL_DBADDR_2 | TIM_DCTRL_DBADDR_3)
#define TIM_DMABASE_CAPCMPDAT6              (TIM_DCTRL_DBADDR_0 | TIM_DCTRL_DBADDR_1 | TIM_DCTRL_DBADDR_2 | TIM_DCTRL_DBADDR_3)
#define TIM_DMABASE_PSC                     (TIM_DCTRL_DBADDR_4)
#define TIM_DMABASE_AR                      (TIM_DCTRL_DBADDR_0 | TIM_DCTRL_DBADDR_4)
#define TIM_DMABASE_CNT                     (TIM_DCTRL_DBADDR_1 | TIM_DCTRL_DBADDR_4)
#define TIM_DMABASE_REPCNT                  (TIM_DCTRL_DBADDR_0 | TIM_DCTRL_DBADDR_1 | TIM_DCTRL_DBADDR_4)
#define TIM_DMABASE_BKDT                    (TIM_DCTRL_DBADDR_2 | TIM_DCTRL_DBADDR_4)
#define TIM_DMABASE_CAPCMPDAT7              (TIM_DCTRL_DBADDR_0 | TIM_DCTRL_DBADDR_2 | TIM_DCTRL_DBADDR_4)
#define TIM_DMABASE_CAPCMPDAT8              (TIM_DCTRL_DBADDR_1 | TIM_DCTRL_DBADDR_2 | TIM_DCTRL_DBADDR_4)
#define TIM_DMABASE_CAPCMPDAT9              (TIM_DCTRL_DBADDR_0 | TIM_DCTRL_DBADDR_1 | TIM_DCTRL_DBADDR_2 | TIM_DCTRL_DBADDR_4)
#define TIM_DMABASE_BKFR                    (TIM_DCTRL_DBADDR_3 | TIM_DCTRL_DBADDR_4)
#define TIM_DMABASE_C1FILT                  (TIM_DCTRL_DBADDR_0 | TIM_DCTRL_DBADDR_3 | TIM_DCTRL_DBADDR_4)
#define TIM_DMABASE_C2FILT                  (TIM_DCTRL_DBADDR_1 | TIM_DCTRL_DBADDR_3 | TIM_DCTRL_DBADDR_4)
#define TIM_DMABASE_C3FILT                  (TIM_DCTRL_DBADDR_0 | TIM_DCTRL_DBADDR_1 | TIM_DCTRL_DBADDR_3 | TIM_DCTRL_DBADDR_4)
#define TIM_DMABASE_C4FILT                  (TIM_DCTRL_DBADDR_2 | TIM_DCTRL_DBADDR_3 | TIM_DCTRL_DBADDR_4)
#define TIM_DMABASE_FILTO                   (TIM_DCTRL_DBADDR_0 | TIM_DCTRL_DBADDR_2 | TIM_DCTRL_DBADDR_3 | TIM_DCTRL_DBADDR_4)
#define TIM_DMABASE_INSEL                   (TIM_DCTRL_DBADDR_1 | TIM_DCTRL_DBADDR_2 | TIM_DCTRL_DBADDR_3 | TIM_DCTRL_DBADDR_4)
#define TIM_DMABASE_AF1                     (TIM_DCTRL_DBADDR_0 | TIM_DCTRL_DBADDR_1 | TIM_DCTRL_DBADDR_2 | TIM_DCTRL_DBADDR_3 | TIM_DCTRL_DBADDR_4)
#define TIM_DMABASE_AF2                     (TIM_DCTRL_DBADDR_5)
#define TIM_DMABASE_BKFR2                   (TIM_DCTRL_DBADDR_0 | TIM_DCTRL_DBADDR_5)
#define TIM_DMABASE_SLIDFPSC                (TIM_DCTRL_DBADDR_1 | TIM_DCTRL_DBADDR_5)

/** TIM_DMA_Burst_Length **/
#define TIM_DMABURST_LENGTH_1TRANSFER       (TIM_REG_BIT_MASK)
#define TIM_DMABURST_LENGTH_2TRANSFERS      (TIM_DCTRL_DBLEN_0)
#define TIM_DMABURST_LENGTH_3TRANSFERS      (TIM_DCTRL_DBLEN_1)
#define TIM_DMABURST_LENGTH_4TRANSFERS      (TIM_DCTRL_DBLEN_0 | TIM_DCTRL_DBLEN_1)
#define TIM_DMABURST_LENGTH_5TRANSFERS      (TIM_DCTRL_DBLEN_2)
#define TIM_DMABURST_LENGTH_6TRANSFERS      (TIM_DCTRL_DBLEN_0 | TIM_DCTRL_DBLEN_2)
#define TIM_DMABURST_LENGTH_7TRANSFERS      (TIM_DCTRL_DBLEN_1 | TIM_DCTRL_DBLEN_2)
#define TIM_DMABURST_LENGTH_8TRANSFERS      (TIM_DCTRL_DBLEN_0 | TIM_DCTRL_DBLEN_1 | TIM_DCTRL_DBLEN_2)
#define TIM_DMABURST_LENGTH_9TRANSFERS      (TIM_DCTRL_DBLEN_3)
#define TIM_DMABURST_LENGTH_10TRANSFERS     (TIM_DCTRL_DBLEN_0 | TIM_DCTRL_DBLEN_3)
#define TIM_DMABURST_LENGTH_11TRANSFERS     (TIM_DCTRL_DBLEN_1 | TIM_DCTRL_DBLEN_3)
#define TIM_DMABURST_LENGTH_12TRANSFERS     (TIM_DCTRL_DBLEN_0 | TIM_DCTRL_DBLEN_1 | TIM_DCTRL_DBLEN_3)
#define TIM_DMABURST_LENGTH_13TRANSFERS     (TIM_DCTRL_DBLEN_2 | TIM_DCTRL_DBLEN_3)
#define TIM_DMABURST_LENGTH_14TRANSFERS     (TIM_DCTRL_DBLEN_0 | TIM_DCTRL_DBLEN_2 | TIM_DCTRL_DBLEN_3)
#define TIM_DMABURST_LENGTH_15TRANSFERS     (TIM_DCTRL_DBLEN_1 | TIM_DCTRL_DBLEN_2 | TIM_DCTRL_DBLEN_3)
#define TIM_DMABURST_LENGTH_16TRANSFERS     (TIM_DCTRL_DBLEN_0 | TIM_DCTRL_DBLEN_1 | TIM_DCTRL_DBLEN_2 | TIM_DCTRL_DBLEN_3)
#define TIM_DMABURST_LENGTH_17TRANSFERS     (TIM_DCTRL_DBLEN_4)
#define TIM_DMABURST_LENGTH_18TRANSFERS     (TIM_DCTRL_DBLEN_0 | TIM_DCTRL_DBLEN_4)
#define TIM_DMABURST_LENGTH_19TRANSFERS     (TIM_DCTRL_DBLEN_1 | TIM_DCTRL_DBLEN_4)
#define TIM_DMABURST_LENGTH_20TRANSFERS     (TIM_DCTRL_DBLEN_0 | TIM_DCTRL_DBLEN_1 | TIM_DCTRL_DBLEN_4)
#define TIM_DMABURST_LENGTH_21TRANSFERS     (TIM_DCTRL_DBLEN_2 | TIM_DCTRL_DBLEN_4)
#define TIM_DMABURST_LENGTH_22TRANSFERS     (TIM_DCTRL_DBLEN_0 | TIM_DCTRL_DBLEN_2 | TIM_DCTRL_DBLEN_4)
#define TIM_DMABURST_LENGTH_23TRANSFERS     (TIM_DCTRL_DBLEN_1 | TIM_DCTRL_DBLEN_2 | TIM_DCTRL_DBLEN_4)
#define TIM_DMABURST_LENGTH_24TRANSFERS     (TIM_DCTRL_DBLEN_0 | TIM_DCTRL_DBLEN_1 | TIM_DCTRL_DBLEN_2 | TIM_DCTRL_DBLEN_4)
#define TIM_DMABURST_LENGTH_25TRANSFERS     (TIM_DCTRL_DBLEN_3 | TIM_DCTRL_DBLEN_4)
#define TIM_DMABURST_LENGTH_26TRANSFERS     (TIM_DCTRL_DBLEN_0 | TIM_DCTRL_DBLEN_3 | TIM_DCTRL_DBLEN_4)
#define TIM_DMABURST_LENGTH_27TRANSFERS     (TIM_DCTRL_DBLEN_1 | TIM_DCTRL_DBLEN_3 | TIM_DCTRL_DBLEN_4)
#define TIM_DMABURST_LENGTH_28TRANSFERS     (TIM_DCTRL_DBLEN_0 | TIM_DCTRL_DBLEN_1 | TIM_DCTRL_DBLEN_3 | TIM_DCTRL_DBLEN_4)
#define TIM_DMABURST_LENGTH_29TRANSFERS     (TIM_DCTRL_DBLEN_2 | TIM_DCTRL_DBLEN_3 | TIM_DCTRL_DBLEN_4)
#define TIM_DMABURST_LENGTH_30TRANSFERS     (TIM_DCTRL_DBLEN_0 | TIM_DCTRL_DBLEN_2 | TIM_DCTRL_DBLEN_3 | TIM_DCTRL_DBLEN_4)
#define TIM_DMABURST_LENGTH_31TRANSFERS     (TIM_DCTRL_DBLEN_1 | TIM_DCTRL_DBLEN_2 | TIM_DCTRL_DBLEN_3 | TIM_DCTRL_DBLEN_4)
#define TIM_DMABURST_LENGTH_32TRANSFERS     (TIM_DCTRL_DBLEN_0 | TIM_DCTRL_DBLEN_1 | TIM_DCTRL_DBLEN_2 | TIM_DCTRL_DBLEN_3 | TIM_DCTRL_DBLEN_4)
#define TIM_DMABURST_LENGTH_33TRANSFERS     (TIM_DCTRL_DBLEN_5)
#define TIM_DMABURST_LENGTH_34TRANSFERS     (TIM_DCTRL_DBLEN_0 | TIM_DCTRL_DBLEN_5)
#define TIM_DMABURST_LENGTH_35TRANSFERS     (TIM_DCTRL_DBLEN_1 | TIM_DCTRL_DBLEN_5)

/** TIM_DMA_sources **/
#define TIM_DMA_CC1                         (TIM_DINTEN_CC1DEN)
#define TIM_DMA_CC2                         (TIM_DINTEN_CC2DEN)
#define TIM_DMA_CC3                         (TIM_DINTEN_CC3DEN)
#define TIM_DMA_CC4                         (TIM_DINTEN_CC4DEN)
#define TIM_DMA_UPDATE                      (TIM_DINTEN_UDEN)
#define TIM_DMA_COM                         (TIM_DINTEN_COMDEN)
#define TIM_DMA_TRIG                        (TIM_DINTEN_TDEN)

/** TIM_Slave_Mode **/
#define TIM_SLAVE_MODE_DISABLE              (TIM_REG_BIT_MASK)
#define TIM_SLAVE_MODE_RESET                (TIM_SMCTRL_SMSEL_2)
#define TIM_SLAVE_MODE_GATED                (TIM_SMCTRL_SMSEL_0 | TIM_SMCTRL_SMSEL_2)
#define TIM_SLAVE_MODE_TRIG                 (TIM_SMCTRL_SMSEL_1 | TIM_SMCTRL_SMSEL_2)
#define TIM_SLAVE_MODE_EXT1                 (TIM_SMCTRL_SMSEL_0 | TIM_SMCTRL_SMSEL_1 | TIM_SMCTRL_SMSEL_2)
#define TIM_SLAVE_MODE_GATED_RESET          (TIM_SMCTRL_SMSEL_0 | TIM_SMCTRL_SMSEL_2 | TIM_SMCTRL_SMSEL_3)
#define TIM_SLAVE_MODE_TRIG_RESET           (TIM_SMCTRL_SMSEL_1 | TIM_SMCTRL_SMSEL_2 | TIM_SMCTRL_SMSEL_3)

/** TIM_EncoderMode **/
#define TIM_ENCODE_QUA_MODE_TI1             (TIM_SMCTRL_SMSEL_0)    
#define TIM_ENCODE_QUA_MODE_TI2             (TIM_SMCTRL_SMSEL_1)
#define TIM_ENCODE_QUA_MODE_TI12            (TIM_SMCTRL_SMSEL_0 | TIM_SMCTRL_SMSEL_1)
#define TIM_ENCODE_QUA_MODE_SINGLE_TI1      (TIM_SMCTRL_SMSEL_0 | TIM_SMCTRL_SMSEL_3)
#define TIM_ENCODE_QUA_MODE_SINGLE_TI2      (TIM_SMCTRL_SMSEL_1 | TIM_SMCTRL_SMSEL_3)
#define TIM_ENCODE_DUL_CLKPLUS_MODE1        (TIM_SMCTRL_SMSEL_0 | TIM_SMCTRL_SMSEL_1 | TIM_SMCTRL_SMSEL_2 | TIM_SMCTRL_SMSEL_3)
#define TIM_ENCODE_DUL_CLKPLUS_MODE2        (TIM_SMCTRL_SMSEL_3)    
#define TIM_ENCODE_SINGLE_CLKPLUS_MODE1     (TIM_SMCTRL_SMSEL_2 | TIM_SMCTRL_SMSEL_3)
#define TIM_ENCODE_SINGLE_CLKPLUS_MODE2     (TIM_SMCTRL_SMSEL_0 | TIM_SMCTRL_SMSEL_1 | TIM_SMCTRL_SMSEL_3) 

/** TIM_Output_Compare_Preload_State **/
#define TIM_OC_PRE_LOAD_ENABLE              (TIM_CCMOD1_OC1PEN)
#define TIM_OC_PRE_LOAD_DISABLE             (TIM_REG_BIT_MASK)

/** TIM_Output_Compare_Fast_State **/
#define TIM_OC_FAST_ENABLE                  (TIM_CCMOD1_OC1FEN)
#define TIM_OC_FAST_DISABLE                 (TIM_REG_BIT_MASK)

/** TIM_Output_Compare_Clear_State **/
#define TIM_OC_CLR_ENABLE                   (TIM_CCMOD1_OC1CEN)
#define TIM_OC_CLR_DISABLE                  (TIM_REG_BIT_MASK)

/** Capture compare enable **/
#define CAPCMPEN_CCE_SET                    (TIM_CCEN_CC1EN)
#define CAPCMPEN_CCNE_SET                   (TIM_CCEN_CC1NEN)

/** TIM_Capture_Compare_state **/
#define TIM_CAP_CMP_ENABLE                  (TIM_CCEN_CC1EN)
#define TIM_CAP_CMP_DISABLE                 (TIM_REG_BIT_MASK)

/** TIM_Capture_Compare_N_state **/
#define TIM_CAP_CMP_N_ENABLE                (TIM_CCEN_CC1NEN)
#define TIM_CAP_CMP_N_DISABLE               (TIM_REG_BIT_MASK)

/** TIMx_CCOMD1 register address offset **/
#define CAPCMPMOD_OFFSET                    ((uint32_t)0x00000018)

/** TIM_Update_Source **/
#define TIM_UPDATE_SRC_GLOBAL               (TIM_REG_BIT_MASK) /* Source of update is the counter overflow/underflow \
                                                                 or the setting of UG bit, or an update generation \
                                                                 through the slave mode controller. */
#define TIM_UPDATE_SRC_REGULAR              (TIM_CTRL1_UPRS) /* Source of update is counter overflow/underflow. */

/** TIM_One_Pulse_Mode **/
#define TIM_OPMODE_SINGLE                   (TIM_CTRL1_ONEPM)
#define TIM_OPMODE_REPET                    (TIM_REG_BIT_MASK)

/** TIM_Trigger_Output_Source **/
#define TIM_TRGO_SRC_RESET                  (TIM_REG_BIT_MASK)
#define TIM_TRGO_SRC_ENABLE                 (TIM_CTRL2_MMSEL_0)
#define TIM_TRGO_SRC_UPDATE                 (TIM_CTRL2_MMSEL_1)
#define TIM_TRGO_SRC_OC1                    (TIM_CTRL2_MMSEL_0 | TIM_CTRL2_MMSEL_1)
#define TIM_TRGO_SRC_OC1REF                 (TIM_CTRL2_MMSEL_2)
#define TIM_TRGO_SRC_OC2REF                 (TIM_CTRL2_MMSEL_0 | TIM_CTRL2_MMSEL_2)
#define TIM_TRGO_SRC_OC3REF                 (TIM_CTRL2_MMSEL_1 | TIM_CTRL2_MMSEL_2)
#define TIM_TRGO_SRC_OC4REF                 (TIM_CTRL2_MMSEL_0 | TIM_CTRL2_MMSEL_1 | TIM_CTRL2_MMSEL_2)
#define TIM_TRGO_SRC_OC4_7_8_9REF           (TIM_CTRL2_MMSEL_3)

/** TIM_Trigger_Output2_Source **/
#define TIM_TRGO2_SRC_RESET                  (TIM_REG_BIT_MASK)
#define TIM_TRGO2_SRC_ENABLE                 (TIM_CTRL2_MMSEL2_0)
#define TIM_TRGO2_SRC_UPDATE                 (TIM_CTRL2_MMSEL2_1)
#define TIM_TRGO2_SRC_OC1                    (TIM_CTRL2_MMSEL2_0 | TIM_CTRL2_MMSEL2_1)
#define TIM_TRGO2_SRC_OC1REF                 (TIM_CTRL2_MMSEL2_2)
#define TIM_TRGO2_SRC_OC2REF                 (TIM_CTRL2_MMSEL2_0 | TIM_CTRL2_MMSEL2_2)
#define TIM_TRGO2_SRC_OC3REF                 (TIM_CTRL2_MMSEL2_1 | TIM_CTRL2_MMSEL2_2)
#define TIM_TRGO2_SRC_OC4REF                 (TIM_CTRL2_MMSEL2_0 | TIM_CTRL2_MMSEL2_1 | TIM_CTRL2_MMSEL2_2)
#define TIM_TRGO2_SRC_OC5REF                 (TIM_CTRL2_MMSEL2_3)
#define TIM_TRGO2_SRC_OC6REF                 (TIM_CTRL2_MMSEL2_0 | TIM_CTRL2_MMSEL2_3)
#define LL_TIM_TRGO2_OC4_RISINGFALLING       (TIM_CTRL2_MMSEL2_1 | TIM_CTRL2_MMSEL2_3)
#define LL_TIM_TRGO2_OC6_RISINGFALLING       (TIM_CTRL2_MMSEL2_0 | TIM_CTRL2_MMSEL2_1 | TIM_CTRL2_MMSEL2_3)
#define LL_TIM_TRGO2_OC4_RISING_OC6_RISING   (TIM_CTRL2_MMSEL2_2 | TIM_CTRL2_MMSEL2_3)
#define LL_TIM_TRGO2_OC4_RISING_OC6_FALLING  (TIM_CTRL2_MMSEL2_0 | TIM_CTRL2_MMSEL2_2 | TIM_CTRL2_MMSEL2_3)
#define LL_TIM_TRGO2_OC5_RISING_OC6_RISING   (TIM_CTRL2_MMSEL2_1 | TIM_CTRL2_MMSEL2_2 | TIM_CTRL2_MMSEL2_3)
#define LL_TIM_TRGO2_OC5_RISING_OC6_FALLING  (TIM_CTRL2_MMSEL2_0 | TIM_CTRL2_MMSEL2_1 | TIM_CTRL2_MMSEL2_2 | TIM_CTRL2_MMSEL2_3)



/** TIM_Master_Slave_Mode **/
#define TIM_MASTER_SLAVE_MODE_ENABLE        (TIM_SMCTRL_MSMD)
#define TIM_MASTER_SLAVE_MODE_DISABLE       (TIM_REG_BIT_MASK)

/** TIM_Legacy **/
#define TIM_CC1EN                           (TIM_CCEN_CC1EN)
#define TIM_CC1NEN                          (TIM_CCEN_CC1NEN)
#define TIM_CC2EN                           (TIM_CCEN_CC2EN)
#define TIM_CC2NEN                          (TIM_CCEN_CC2NEN)
#define TIM_CC3EN                           (TIM_CCEN_CC3EN)
#define TIM_CC3NEN                          (TIM_CCEN_CC3NEN)
#define TIM_CC4EN                           (TIM_CCEN_CC4EN)
#define TIM_CC4NEN                          (TIM_CCEN_CC4NEN)
#define TIM_CC5EN                           (TIM_CCEN_CC5EN)
#define TIM_CC6EN                           (TIM_CCEN_CC6EN)

/** TIM_Flags **/
#define TIM_FLAG_UPDATE                     (TIM_STS_UDITF)
#define TIM_FLAG_CC1                        (TIM_STS_CC1ITF)
#define TIM_FLAG_CC2                        (TIM_STS_CC2ITF)
#define TIM_FLAG_CC3                        (TIM_STS_CC3ITF)
#define TIM_FLAG_CC4                        (TIM_STS_CC4ITF)
#define TIM_FLAG_CC5                        (TIM_STS_CC5ITF)
#define TIM_FLAG_CC6                        (TIM_STS_CC6ITF)
#define TIM_FLAG_CC7                        (TIM_STS_CC7ITF)
#define TIM_FLAG_CC8                        (TIM_STS_CC8ITF)
#define TIM_FLAG_CC9                        (TIM_STS_CC9ITF)
#define TIM_FLAG_COM                        (TIM_STS_COMITF)
#define TIM_FLAG_TRIG                       (TIM_STS_TITF)
#define TIM_FLAG_BREAK                      (TIM_STS_BITF)
#define TIM_FLAG_BREAK2                     (TIM_STS_BITF2)
#define TIM_FLAG_SYS_BREAK                  (TIM_STS_SBITF)
#define TIM_FLAG_CC1OF                      (TIM_STS_CC1OCF)
#define TIM_FLAG_CC2OF                      (TIM_STS_CC2OCF)
#define TIM_FLAG_CC3OF                      (TIM_STS_CC3OCF)
#define TIM_FLAG_CC4OF                      (TIM_STS_CC4OCF)

/* TIM_CenterAlignTriggerSource */
#define TIM_UP_COUNTING                     (TIM_REG_BIT_MASK)
#define TIM_DOWN_COUNTING                   (TIM_CTRL1_CMODE_0)
#define TIM_UP_DOWN_COUNTING                (TIM_CTRL1_CMODE_1)

/** TIM_Flags **/
#define TIM_C1FILTO                         (TIM_FILTO_C1FILTO)
#define TIM_C2FILTO                         (TIM_FILTO_C2FILTO)
#define TIM_C3FILTO                         (TIM_FILTO_C3FILTO)
#define TIM_C4FILTO                         (TIM_FILTO_C4FILTO)

/*** TIM Macro Definition End ***/


/** TIM_Exported_Functions Start **/

void TIM_DeInit(TIM_Module* TIMx);
void TIM_InitTimeBase(TIM_Module* TIMx, TIM_TimeBaseInitType* TIM_TimeBaseInitStruct);
void TIM_InitOc1(TIM_Module* TIMx, OCInitType* TIM_OCInitStruct);
void TIM_InitOc2(TIM_Module* TIMx, OCInitType* TIM_OCInitStruct);
void TIM_InitOc3(TIM_Module* TIMx, OCInitType* TIM_OCInitStruct);
void TIM_InitOc4(TIM_Module* TIMx, OCInitType* TIM_OCInitStruct);
void TIM_InitOc5(TIM_Module* TIMx, OCInitType* TIM_OCInitStruct);
void TIM_InitOc6(TIM_Module* TIMx, OCInitType* TIM_OCInitStruct);
void TIM_ICInit(TIM_Module* TIMx, TIM_ICInitType* TIM_ICInitStruct);
void TIM_ConfigPwmIc(TIM_Module* TIMx, TIM_ICInitType* TIM_ICInitStruct);
void TIM_ConfigBkdt(TIM_Module* TIMx, TIM_BDTRInitType* TIM_BDTRInitStruct);
void TIM_BreakFiltConfig(TIM_Module* TIMx, TIM_FiltInitType* TIM_FiltInitStruct);
void TIM_BreakFiltEnable(TIM_Module* TIMx,FunctionalState Cmd);
void TIM_Break2FiltEnable(TIM_Module* TIMx,FunctionalState Cmd);
void TIM_Break2FiltConfig(TIM_Module* TIMx, TIM_FiltInitType* TIM_FiltInitStruct);
void TIM_BreakInputSourceEnable(TIM_Module* TIMx, uint32_t Source, uint32_t Polarity, FunctionalState Cmd);
void TIM_Break2InputSourceEnable(TIM_Module* TIMx, uint32_t Source, uint32_t Polarity, FunctionalState Cmd);
void TIM_BidirectionDisarm(TIM_Module* TIMx);
void TIM_BidirectionRearm(TIM_Module* TIMx);
void TIM_Bidirection2Disarm(TIM_Module* TIMx);
void TIM_Bidirection2Rearm(TIM_Module* TIMx);
void TIM_InitTimBaseStruct(TIM_TimeBaseInitType* TIM_TimeBaseInitStruct);
void TIM_InitOcStruct(OCInitType* TIM_OCInitStruct);
void TIM_InitIcStruct(TIM_ICInitType* TIM_ICInitStruct);
void TIM_InitBkdtStruct(TIM_BDTRInitType* TIM_BDTRInitStruct);
void TIM_Enable(TIM_Module* TIMx, FunctionalState Cmd);
void TIM_EnableCtrlPwmOutputs(TIM_Module* TIMx, FunctionalState Cmd);
void TIM_ConfigInt(TIM_Module* TIMx, uint32_t TIM_IT, FunctionalState Cmd);
void TIM_GenerateEvent(TIM_Module* TIMx, uint32_t TIM_EventSource);
void TIM_ConfigDma(TIM_Module* TIMx, uint32_t TIM_DMABase, uint32_t TIM_DMABurstLength);
void TIM_EnableDma(TIM_Module* TIMx, uint32_t TIM_DMASource, FunctionalState Cmd);
void TIM_ConfigInternalClk(TIM_Module* TIMx);
void TIM_ConfigInternalTrigToExt(TIM_Module* TIMx, uint32_t TIM_InputTriggerSource);
void TIM_ConfigExtTrigAsClk(TIM_Module* TIMx, uint32_t TIM_TIxExternalCLKSource, uint32_t IcPolarity, uint32_t ICFilter);
void TIM_ConfigExtClkMode1(TIM_Module* TIMx,uint32_t TIM_ETRInputSource,uint32_t TIM_ExtTRGPrescaler,uint32_t TIM_ExtTRGPolarity,uint32_t ExtTRGFilter);
void TIM_ConfigExtClkMode2(TIM_Module* TIMx,uint32_t TIM_ETRInputSource,uint32_t TIM_ExtTRGPrescaler,uint32_t TIM_ExtTRGPolarity,uint32_t ExtTRGFilter);
void TIM_ConfigPrescaler(TIM_Module* TIMx, uint32_t Prescaler, uint32_t TIM_PSCReloadMode);
void TIM_ConfigCntMode(TIM_Module* TIMx, uint32_t CntMode);
void TIM_ConfigEncoderInterface(TIM_Module* TIMx,uint32_t TIM_EncoderMode,uint32_t TIM_IC1Polarity,uint32_t TIM_IC2Polarity);
void TIM_ConfigForcedOc1(TIM_Module* TIMx, uint32_t TIM_ForcedAction);
void TIM_ConfigForcedOc2(TIM_Module* TIMx, uint32_t TIM_ForcedAction);
void TIM_ConfigForcedOc3(TIM_Module* TIMx, uint32_t TIM_ForcedAction);
void TIM_ConfigForcedOc4(TIM_Module* TIMx, uint32_t TIM_ForcedAction);
void TIM_ConfigForcedOc5(TIM_Module* TIMx, uint32_t TIM_ForcedAction);
void TIM_ConfigForcedOc6(TIM_Module* TIMx, uint32_t TIM_ForcedAction);
void TIM_ConfigArPreload(TIM_Module* TIMx, FunctionalState Cmd);
void TIM_SelectComEvt(TIM_Module* TIMx, FunctionalState Cmd);
void TIM_SelectCapCmpDmaSrc(TIM_Module* TIMx, FunctionalState Cmd);
void TIM_EnableCapCmpPreloadControl(TIM_Module* TIMx, FunctionalState Cmd);
void TIM_ConfigOc1Preload(TIM_Module* TIMx, uint32_t TIM_OCPreload);
void TIM_ConfigOc2Preload(TIM_Module* TIMx, uint32_t TIM_OCPreload);
void TIM_ConfigOc3Preload(TIM_Module* TIMx, uint32_t TIM_OCPreload);
void TIM_ConfigOc4Preload(TIM_Module* TIMx, uint32_t TIM_OCPreload);
void TIM_ConfigOc5Preload(TIM_Module* TIMx, uint32_t TIM_OCPreload);
void TIM_ConfigOc6Preload(TIM_Module* TIMx, uint32_t TIM_OCPreload);
void TIM_ConfigOc7Preload(TIM_Module* TIMx, uint32_t TIM_OCPreload);
void TIM_ConfigOc8Preload(TIM_Module* TIMx, uint32_t TIM_OCPreload);
void TIM_ConfigOc9Preload(TIM_Module* TIMx, uint32_t TIM_OCPreload);
void TIM_ConfigOc1Fast(TIM_Module* TIMx, uint32_t TIM_OCFast);
void TIM_ConfigOc2Fast(TIM_Module* TIMx, uint32_t TIM_OCFast);
void TIM_ConfigOc3Fast(TIM_Module* TIMx, uint32_t TIM_OCFast);
void TIM_ConfigOc4Fast(TIM_Module* TIMx, uint32_t TIM_OCFast);
void TIM_ConfigOc5Fast(TIM_Module* TIMx, uint32_t TIM_OCFast);
void TIM_ConfigOc6Fast(TIM_Module* TIMx, uint32_t TIM_OCFast);
void TIM_ClrOc1Ref(TIM_Module* TIMx, uint32_t TIM_OCClear);
void TIM_ClrOc2Ref(TIM_Module* TIMx, uint32_t TIM_OCClear);
void TIM_ClrOc3Ref(TIM_Module* TIMx, uint32_t TIM_OCClear);
void TIM_ClrOc4Ref(TIM_Module* TIMx, uint32_t TIM_OCClear);
void TIM_ClrOc5Ref(TIM_Module* TIMx, uint32_t TIM_OCClear);
void TIM_ClrOc6Ref(TIM_Module* TIMx, uint32_t TIM_OCClear);
void TIM_ClrOcRefInputSource(TIM_Module* TIMx, uint32_t OCRefClearInputSelect,uint32_t OCRefClearInputSource);
void TIM_ConfigOc1Polarity(TIM_Module* TIMx, uint32_t OcPolarity);
void TIM_ConfigOc1NPolarity(TIM_Module* TIMx, uint32_t OcNPolarity);
void TIM_ConfigOc2Polarity(TIM_Module* TIMx, uint32_t OcPolarity);
void TIM_ConfigOc2NPolarity(TIM_Module* TIMx, uint32_t OcNPolarity);
void TIM_ConfigOc3Polarity(TIM_Module* TIMx, uint32_t OcPolarity);
void TIM_ConfigOc3NPolarity(TIM_Module* TIMx, uint32_t OcNPolarity);
void TIM_ConfigOc4Polarity(TIM_Module* TIMx, uint32_t OcPolarity);
void TIM_ConfigOc4NPolarity(TIM_Module* TIMx, uint32_t OcNPolarity);
void TIM_ConfigOc5Polarity(TIM_Module* TIMx, uint32_t OcPolarity);
void TIM_ConfigOc6Polarity(TIM_Module* TIMx, uint32_t OcPolarity);
void TIM_EnableCapCmpCh(TIM_Module* TIMx, uint32_t Channel, uint32_t TIM_CCx);
void TIM_EnableCapCmpChN(TIM_Module* TIMx, uint32_t Channel, uint32_t TIM_CCxN);
void TIM_SelectOcMode(TIM_Module* TIMx, uint32_t Channel, uint32_t OcMode);
void TIM_EnableUpdateEvt(TIM_Module* TIMx, FunctionalState Cmd);
void TIM_ConfigUpdateRequestIntSrc(TIM_Module* TIMx, uint32_t TIM_UpdateSource);
void TIM_SelectHallSensor(TIM_Module* TIMx, FunctionalState Cmd);
void TIM_SelectOnePulseMode(TIM_Module* TIMx, uint32_t TIM_OPMode);
void TIM_SelectOutputTrig(TIM_Module* TIMx, uint32_t TIM_TRGOSource);
void TIM_SelectOutputTrig2(TIM_Module* TIMx, uint32_t TIM_TRGO2Source);
void TIM_SelectSlaveMode(TIM_Module* TIMx, uint32_t TIM_SlaveMode);
void TIM_SelectMasterSlaveMode(TIM_Module* TIMx, uint32_t TIM_MasterSlaveMode);
void TIM_SetCnt(TIM_Module* TIMx, uint32_t Counter);
void TIM_SetAutoReload(TIM_Module* TIMx, uint32_t Autoreload);
void TIM_SetCmp1(TIM_Module* TIMx, uint16_t Compare1);
void TIM_SetCmp2(TIM_Module* TIMx, uint16_t Compare2);
void TIM_SetCmp3(TIM_Module* TIMx, uint16_t Compare3);
void TIM_SetCmp4(TIM_Module* TIMx, uint16_t Compare4);
void TIM_SetCmp5(TIM_Module* TIMx, uint16_t Compare5);
void TIM_SetCmp6(TIM_Module* TIMx, uint16_t Compare6);
void TIM_SetCmp7(TIM_Module* TIMx, uint16_t Compare7);
void TIM_SetCmp8(TIM_Module* TIMx, uint16_t Compare8);
void TIM_SetCmp9(TIM_Module* TIMx, uint16_t Compare9);
void TIM_SetCmp1D(TIM_Module* TIMx, uint16_t compare1D);
void TIM_SetCmp2D(TIM_Module* TIMx, uint16_t compare2D);
void TIM_SetCmp3D(TIM_Module* TIMx, uint16_t compare3D);
void TIM_SetCmp4D(TIM_Module* TIMx, uint16_t compare4D);
void ConfigTI1(TIM_Module* TIMx, uint32_t ICPolarity, uint32_t ICSelection, uint32_t ICFilter);
void ConfigTI2(TIM_Module* TIMx, uint32_t ICPolarity, uint32_t ICSelection, uint32_t ICFilter);
void ConfigTI3(TIM_Module* TIMx, uint32_t ICPolarity, uint32_t ICSelection, uint32_t ICFilter);
void ConfigTI4(TIM_Module* TIMx, uint32_t ICPolarity, uint32_t ICSelection, uint32_t ICFilter);
void TIM_SetInCap1Prescaler(TIM_Module* TIMx, uint32_t ICPrescaler);
void TIM_SetInCap2Prescaler(TIM_Module* TIMx, uint32_t ICPrescaler);
void TIM_SetInCap3Prescaler(TIM_Module* TIMx, uint32_t ICPrescaler);
void TIM_SetInCap4Prescaler(TIM_Module* TIMx, uint32_t ICPrescaler);
void TIM_SelectInputTrig(TIM_Module* TIMx, uint32_t TIM_InputTriggerSource);
void TIM_ConfigExtTrig(TIM_Module* TIMx,uint32_t TIM_ExtTRGPrescaler,uint32_t TIM_ExtTRGPolarity,uint32_t ExtTRGFilter);
void TIM_SelectETRInputSource(TIM_Module* TIMx, uint32_t TIM_ETRInputSource);
void TIM_SetClkDiv(TIM_Module* TIMx, uint32_t TIM_CKD);
uint16_t TIM_GetCap1(TIM_Module* TIMx);
uint16_t TIM_GetCap2(TIM_Module* TIMx);
uint16_t TIM_GetCap3(TIM_Module* TIMx);
uint16_t TIM_GetCap4(TIM_Module* TIMx);
uint16_t TIM_GetCap5(TIM_Module* TIMx);
uint16_t TIM_GetCap6(TIM_Module* TIMx);
uint16_t TIM_GetCap7(TIM_Module* TIMx);
uint16_t TIM_GetCap8(TIM_Module* TIMx);
uint16_t TIM_GetCap9(TIM_Module* TIMx);
uint16_t TIM_GetCap1D(TIM_Module* TIMx);
uint16_t TIM_GetCap2D(TIM_Module* TIMx);
uint16_t TIM_GetCap3D(TIM_Module* TIMx);
uint16_t TIM_GetCap4D(TIM_Module* TIMx);
uint32_t TIM_GetCnt(TIM_Module* TIMx);
uint16_t TIM_GetPrescaler(TIM_Module* TIMx);
uint32_t TIM_GetAutoReload(TIM_Module* TIMx);
FlagStatus TIM_GetCCENStatus(TIM_Module* TIMx, uint32_t TIM_CCEN);
FlagStatus TIM_GetFlagStatus(TIM_Module* TIMx, uint32_t TIM_FLAG);
void TIM_ClearFlag(TIM_Module* TIMx, uint32_t TIM_FLAG);
INTStatus TIM_GetIntStatus(TIM_Module* TIMx, uint32_t TIM_IT);
void TIM_ClrIntPendingBit(TIM_Module* TIMx, uint32_t TIM_IT);
void TIM_SelectCenterAlignTrig(TIM_Module* TIMx, uint32_t TIM_CenterAlignTriggerSource);
void TIM_AsymmetricEnable(TIM_Module* TIMx, FunctionalState Cmd);
void TIM_OCxRefTriggerADC(TIM_Module* TIMx, uint32_t OCxRef, FunctionalState Cmd);
void TIM_IC1FiltConfig(TIM_Module* TIMx, TIM_FiltInitType* TIM_FiltInitStruct);
void TIM_IC2FiltConfig(TIM_Module* TIMx, TIM_FiltInitType* TIM_FiltInitStruct);
void TIM_IC3FiltConfig(TIM_Module* TIMx, TIM_FiltInitType* TIM_FiltInitStruct);
void TIM_IC4FiltConfig(TIM_Module* TIMx, TIM_FiltInitType* TIM_FiltInitStruct);
void TIM_IC1FiltEnable(TIM_Module* TIMx,FunctionalState Cmd);
void TIM_IC2FiltEnable(TIM_Module* TIMx,FunctionalState Cmd);
void TIM_IC3FiltEnable(TIM_Module* TIMx,FunctionalState Cmd);
void TIM_IC4FiltEnable(TIM_Module* TIMx,FunctionalState Cmd);
FlagStatus TIM_GetFiltStatus(TIM_Module* TIMx, uint32_t TIM_FiltFlag);

/** TIM_Exported_Functions End **/

#ifdef __cplusplus
}

#endif

#endif /*__N32H76x_78x_TIM_H */
































