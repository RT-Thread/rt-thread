/**
  ******************************************************************************
  * @file    lib_pwm.h 
  * @author  Application Team
  * @version V4.4.0
  * @date    2018-09-27
  * @brief   PWM library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_PWM_H
#define __LIB_PWM_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"
   
typedef struct
{
  uint32_t ClockDivision;
  uint32_t Mode;
  uint32_t ClockSource;
} PWM_BaseInitType;
//ClockDivision
#define PWM_CLKDIV_2     PWM_CTL_ID_DIV2
#define PWM_CLKDIV_4     PWM_CTL_ID_DIV4
#define PWM_CLKDIV_8     PWM_CTL_ID_DIV8
#define PWM_CLKDIV_16    PWM_CTL_ID_DIV16
//Mode
#define PWM_MODE_STOP           PWM_CTL_MC_STOP
#define PWM_MODE_UPCOUNT        PWM_CTL_MC_UP
#define PWM_MODE_CONTINUOUS     PWM_CTL_MC_CONTINUE
#define PWM_MODE_UPDOWN         PWM_CTL_MC_UPDOWN
//ClockSource
#define PWM_CLKSRC_APB          PWM_CTL_TESL_APBDIV1
#define PWM_CLKSRC_APBD128      PWM_CTL_TESL_APBDIV128

typedef struct
{
  uint32_t Period;
  uint32_t OutMode;
} PWM_OCInitType;
//OUTMOD
#define PWM_OUTMOD_CONST        PWM_CCTL_OUTMOD_CONST
#define PWM_OUTMOD_SET          PWM_CCTL_OUTMOD_SET
#define PWM_OUTMOD_TOGGLE_RESET PWM_CCTL_OUTMOD_TOGGLE_RESET
#define PWM_OUTMOD_SET_RESET    PWM_CCTL_OUTMOD_SET_RESET
#define PWM_OUTMOD_TOGGLE       PWM_CCTL_OUTMOD_TOGGLE      
#define PWM_OUTMOD_RESET        PWM_CCTL_OUTMOD_RESET       
#define PWM_OUTMOD_TOGGLE_SET   PWM_CCTL_OUTMOD_TOGGLE_SET  
#define PWM_OUTMOD_RESET_SET    PWM_CCTL_OUTMOD_RESET_SET

//PWM CHANNEL
#define PWM_CHANNEL_0           0
#define PWM_CHANNEL_1           1
#define PWM_CHANNEL_2           2

#define PWM_OSEL0_T0O0 (0<<0)
#define PWM_OSEL0_T0O1 (1<<0)
#define PWM_OSEL0_T0O2 (2<<0)
#define PWM_OSEL0_T1O0 (4<<0)
#define PWM_OSEL0_T1O1 (5<<0)
#define PWM_OSEL0_T1O2 (6<<0)
#define PWM_OSEL0_T2O0 (8<<0)
#define PWM_OSEL0_T2O1 (9<<0)
#define PWM_OSEL0_T2O2 (10<<0)
#define PWM_OSEL0_T3O0 (12<<0)
#define PWM_OSEL0_T3O1 (13<<0)
#define PWM_OSEL0_T3O2 (14<<0)
//outline
#define PWM_OLINE_0       1
#define PWM_OLINE_1       2
#define PWM_OLINE_2       4
#define PWM_OLINE_3       8
#define PWM_OLINE_Msk     0xF
//PWM output selection
#define PWM0_OUT0        PWM_OSEL0_T0O0
#define PWM0_OUT1        PWM_OSEL0_T0O1
#define PWM0_OUT2        PWM_OSEL0_T0O2
#define PWM1_OUT0        PWM_OSEL0_T1O0
#define PWM1_OUT1        PWM_OSEL0_T1O1
#define PWM1_OUT2        PWM_OSEL0_T1O2
#define PWM2_OUT0        PWM_OSEL0_T2O0
#define PWM2_OUT1        PWM_OSEL0_T2O1
#define PWM2_OUT2        PWM_OSEL0_T2O2
#define PWM3_OUT0        PWM_OSEL0_T3O0
#define PWM3_OUT1        PWM_OSEL0_T3O1
#define PWM3_OUT2        PWM_OSEL0_T3O2

//Level
#define PWM_LEVEL_HIGH  PWM_CCTL_OUT
#define PWM_LEVEL_LOW   0

/* Private macros ------------------------------------------------------------*/
#define IS_PWM_CLKDIV(__CLKDIV__)  (((__CLKDIV__) == PWM_CLKDIV_2) ||\
                                    ((__CLKDIV__) == PWM_CLKDIV_4) ||\
                                    ((__CLKDIV__) == PWM_CLKDIV_8) ||\
                                    ((__CLKDIV__) == PWM_CLKDIV_16))

#define IS_PWM_CNTMODE(__CNTMODE__)  (((__CNTMODE__) == PWM_MODE_STOP)       ||\
                                      ((__CNTMODE__) == PWM_MODE_UPCOUNT)    ||\
                                      ((__CNTMODE__) == PWM_MODE_CONTINUOUS) ||\
                                      ((__CNTMODE__) == PWM_MODE_UPDOWN))

#define IS_PWM_CLKSRC(__CLKSRC__)  (((__CLKSRC__) == PWM_CLKSRC_APB) ||\
                                    ((__CLKSRC__) == PWM_CLKSRC_APBD128))

#define IS_PWM_OUTMODE(__OUTMODE__)  (((__OUTMODE__) == PWM_OUTMOD_CONST)        ||\
                                      ((__OUTMODE__) == PWM_OUTMOD_SET)          ||\
                                      ((__OUTMODE__) == PWM_OUTMOD_TOGGLE_RESET) ||\
                                      ((__OUTMODE__) == PWM_OUTMOD_SET_RESET)    ||\
                                      ((__OUTMODE__) == PWM_OUTMOD_TOGGLE)       ||\
                                      ((__OUTMODE__) == PWM_OUTMOD_RESET)        ||\
                                      ((__OUTMODE__) == PWM_OUTMOD_TOGGLE_SET)   ||\
                                      ((__OUTMODE__) == PWM_OUTMOD_RESET_SET))

#define IS_PWM_CCR(__CCR__)  ((__CCR__) < 0x10000U)

#define IS_PWM_CHANNEL(__CHANNEL__)  (((__CHANNEL__) == PWM_CHANNEL_0) ||\
                                      ((__CHANNEL__) == PWM_CHANNEL_1) ||\
                                      ((__CHANNEL__) == PWM_CHANNEL_2))

#define IS_PWM_OUTLINE(__OUTLINE__)  ((((__OUTLINE__) & PWM_OLINE_Msk) != 0U) &&\
                                      (((__OUTLINE__) & ~PWM_OLINE_Msk) == 0U))

#define IS_PWM_OUTSEL(__OUTSEL__)  (((__OUTSEL__) == PWM0_OUT0) ||\
                                    ((__OUTSEL__) == PWM0_OUT1) ||\
                                    ((__OUTSEL__) == PWM0_OUT2) ||\
                                    ((__OUTSEL__) == PWM1_OUT0) ||\
                                    ((__OUTSEL__) == PWM1_OUT1) ||\
                                    ((__OUTSEL__) == PWM1_OUT2) ||\
                                    ((__OUTSEL__) == PWM2_OUT0) ||\
                                    ((__OUTSEL__) == PWM2_OUT1) ||\
                                    ((__OUTSEL__) == PWM2_OUT2) ||\
                                    ((__OUTSEL__) == PWM3_OUT0) ||\
                                    ((__OUTSEL__) == PWM3_OUT1) ||\
                                    ((__OUTSEL__) == PWM3_OUT2))

#define IS_PWM_OUTLVL(__OUTLVL__)  (((__OUTLVL__) == PWM_LEVEL_HIGH) ||\
                                    ((__OUTLVL__) == PWM_LEVEL_LOW))

/* Exported Functions ------------------------------------------------------- */
/* PWM Exported Functions Group1: 
                                   Initialization ----------------------------*/
void PWM_BaseInit(PWM_TypeDef *PWMx, PWM_BaseInitType *InitStruct);
void PWM_BaseStructInit(PWM_BaseInitType *InitStruct);
void PWM_OC0Init(PWM_TypeDef *PWMx, PWM_OCInitType *OCInitType);
void PWM_OC1Init(PWM_TypeDef *PWMx, PWM_OCInitType *OCInitType);
void PWM_OC2Init(PWM_TypeDef *PWMx, PWM_OCInitType *OCInitType);
void PWM_OCStructInit(PWM_OCInitType *OCInitType);
/* PWM Exported Functions Group2: 
                                   Interrupt ---------------------------------*/
void PWM_BaseINTConfig(PWM_TypeDef *PWMx, uint32_t NewState);
uint8_t PWM_GetBaseINTStatus(PWM_TypeDef *PWMx);
void PWM_ClearBaseINTStatus(PWM_TypeDef *PWMx);
void PWM_ChannelINTConfig(PWM_TypeDef *PWMx, uint32_t Channel, uint32_t NewState);
uint8_t PWM_GetChannelINTStatus(PWM_TypeDef *PWMx, uint32_t Channel);
void PWM_ClearChannelINTStatus(PWM_TypeDef *PWMx, uint32_t Channel);
/* PWM Exported Functions Group3: 
                                   MISC --------------------------------------*/
void PWM_ClearCounter(PWM_TypeDef *PWMx);
void PWM_CCRConfig(PWM_TypeDef *PWMx, uint32_t Channel, uint16_t Period);
//Compare output
void PWM_OLineConfig(uint32_t OutSelection, uint32_t OLine);
void PWM_OutputCmd(PWM_TypeDef *PWMx, uint32_t Channel, uint32_t NewState);
void PWM_SetOutLevel(PWM_TypeDef *PWMx, uint32_t Channel, uint32_t Level);

#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_PWM_H */

/*********************************** END OF FILE ******************************/
