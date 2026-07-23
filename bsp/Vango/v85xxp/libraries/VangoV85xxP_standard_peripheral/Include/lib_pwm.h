/**
  ******************************************************************************
  * @file    lib_pwm.h 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
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

/**************  Bits definition for PWMx_CTL register       ******************/
#define PWM_CTL_TESL_APBDIV128        (0x0U << PWM_CTL_TSEL_Pos)               /*!< 0x00000000 */
#define PWM_CTL_TESL_APBDIV1          (0x1U << PWM_CTL_TSEL_Pos)               /*!< 0x00000008 */
#define PWM_CTL_MC_STOP               (0x0U << PWM_CTL_MC_Pos)                 /*!< 0x00000000 */
#define PWM_CTL_MC_UP                 (0x1U << PWM_CTL_MC_Pos)                 /*!< 0x00000010 */
#define PWM_CTL_MC_CONTINUE           (0x2U << PWM_CTL_MC_Pos)                 /*!< 0x00000020 */
#define PWM_CTL_MC_UPDOWN             (0x3U << PWM_CTL_MC_Pos)                 /*!< 0x00000030 */
#define PWM_CTL_ID_DIV2               (0x0U << PWM_CTL_ID_Pos)                 /*!< 0x00000000 */
#define PWM_CTL_ID_DIV4               (0x1U << PWM_CTL_ID_Pos)                 /*!< 0x00000040 */
#define PWM_CTL_ID_DIV8               (0x2U << PWM_CTL_ID_Pos)                 /*!< 0x00000080 */
#define PWM_CTL_ID_DIV16              (0x3U << PWM_CTL_ID_Pos)                 /*!< 0x000000C0 */

/**************  Bits definition for PWMx_TAR register       ******************/

/**************  Bits definition for PWMx_CCTLy register     ******************/
////////////#define PWM_CCTL_OUTMOD_CONST         (0x00UL << PWM_CCTL_OUTMOD_Pos) 
#define PWM_CCTL_OUTMOD_SET           (0x01UL << PWM_CCTL_OUTMOD_Pos) 
#define PWM_CCTL_OUTMOD_TOGGLE_RESET  (0x02UL << PWM_CCTL_OUTMOD_Pos) 
#define PWM_CCTL_OUTMOD_SET_RESET     (0x03UL << PWM_CCTL_OUTMOD_Pos) 
#define PWM_CCTL_OUTMOD_TOGGLE        (0x04UL << PWM_CCTL_OUTMOD_Pos) 
#define PWM_CCTL_OUTMOD_RESET         (0x05UL << PWM_CCTL_OUTMOD_Pos) 
#define PWM_CCTL_OUTMOD_TOGGLE_SET    (0x06UL << PWM_CCTL_OUTMOD_Pos) 
#define PWM_CCTL_OUTMOD_RESET_SET     (0x07UL << PWM_CCTL_OUTMOD_Pos) 
////////////////////

//ClockDivision
#define PWM_CLKDIV_2                  (0x0U << PWM_CTL_ID_Pos)
#define PWM_CLKDIV_4                  (0x1U << PWM_CTL_ID_Pos)
#define PWM_CLKDIV_8                  (0x2U << PWM_CTL_ID_Pos)
#define PWM_CLKDIV_16                 (0x3U << PWM_CTL_ID_Pos)
#define IS_PWM_CLKDIV(__CLKDIV__)    (((__CLKDIV__) == PWM_CLKDIV_2) ||\
                                      ((__CLKDIV__) == PWM_CLKDIV_4) ||\
                                      ((__CLKDIV__) == PWM_CLKDIV_8) ||\
                                      ((__CLKDIV__) == PWM_CLKDIV_16))

//Mode
#define PWM_MODE_STOP                 (0x0U << PWM_CTL_MC_Pos)
#define PWM_MODE_UPCOUNT              (0x1U << PWM_CTL_MC_Pos)
#define PWM_MODE_CONTINUOUS           (0x2U << PWM_CTL_MC_Pos)
#define PWM_MODE_UPDOWN               (0x3U << PWM_CTL_MC_Pos)
#define IS_PWM_CNTMODE(__CNTMODE__)  (((__CNTMODE__) == PWM_MODE_STOP)       ||\
                                      ((__CNTMODE__) == PWM_MODE_UPCOUNT)    ||\
                                      ((__CNTMODE__) == PWM_MODE_CONTINUOUS) ||\
                                      ((__CNTMODE__) == PWM_MODE_UPDOWN))

//ClockSource
#define PWM_CLKSRC_APB                (0x1U << PWM_CTL_TSEL_Pos)
#define PWM_CLKSRC_APBD128            (0x0U << PWM_CTL_TSEL_Pos)
#define IS_PWM_CLKSRC(__CLKSRC__)    (((__CLKSRC__) == PWM_CLKSRC_APB) ||\
                                      ((__CLKSRC__) == PWM_CLKSRC_APBD128))

typedef struct
{
  uint32_t Channel;
  uint32_t Period;
  uint32_t OutMode;
} PWM_OCInitType;
typedef struct
{
  uint32_t Channel;
  uint32_t CaptureMode;
} PWM_ICInitType;
//Channel
#define PWM_CHANNEL_0                 (0UL)
#define PWM_CHANNEL_1                 (1UL)
#define PWM_CHANNEL_2                 (2UL)
#define IS_PWM_CHANNEL(__CHANNEL__)  (((__CHANNEL__) == PWM_CHANNEL_0) ||\
                                      ((__CHANNEL__) == PWM_CHANNEL_1) ||\
                                      ((__CHANNEL__) == PWM_CHANNEL_2))
//OutMode
#define PWM_OUTMOD_CONST              (0x0U << PWM_CCTL_OUTMOD_Pos)
#define PWM_OUTMOD_SET                (0x1U << PWM_CCTL_OUTMOD_Pos)
#define PWM_OUTMOD_TOGGLE_RESET       (0x2U << PWM_CCTL_OUTMOD_Pos)
#define PWM_OUTMOD_SET_RESET          (0x3U << PWM_CCTL_OUTMOD_Pos)
#define PWM_OUTMOD_TOGGLE             (0x4U << PWM_CCTL_OUTMOD_Pos)
#define PWM_OUTMOD_RESET              (0x5U << PWM_CCTL_OUTMOD_Pos)
#define PWM_OUTMOD_TOGGLE_SET         (0x6U << PWM_CCTL_OUTMOD_Pos)
#define PWM_OUTMOD_RESET_SET          (0x7U << PWM_CCTL_OUTMOD_Pos)
#define IS_PWM_OUTMODE(__OUTMODE__)  (((__OUTMODE__) == PWM_OUTMOD_CONST)        ||\
                                      ((__OUTMODE__) == PWM_OUTMOD_SET)          ||\
                                      ((__OUTMODE__) == PWM_OUTMOD_TOGGLE_RESET) ||\
                                      ((__OUTMODE__) == PWM_OUTMOD_SET_RESET)    ||\
                                      ((__OUTMODE__) == PWM_OUTMOD_TOGGLE)       ||\
                                      ((__OUTMODE__) == PWM_OUTMOD_RESET)        ||\
                                      ((__OUTMODE__) == PWM_OUTMOD_TOGGLE_SET)   ||\
                                      ((__OUTMODE__) == PWM_OUTMOD_RESET_SET))

//CaptureMode
#define PWM_CM_DISABLE                (0x0U << PWM_CCTL_CM_Pos)
#define PWM_CM_RISING                 (0x1U << PWM_CCTL_CM_Pos)
#define PWM_CM_FALLING                (0x2U << PWM_CCTL_CM_Pos)
#define PWM_CM_BOTH                   (0x3U << PWM_CCTL_CM_Pos)
#define IS_PWM_CAPMODE(__CAPMODE__)  (((__CAPMODE__) == PWM_CM_DISABLE) ||\
                                      ((__CAPMODE__) == PWM_CM_RISING)  ||\
                                      ((__CAPMODE__) == PWM_CM_FALLING) ||\
                                      ((__CAPMODE__) == PWM_CM_BOTH))

//Interrupt
#define PWM_INT_CCIFG                 PWM_CCTL_CCIFG
#define PWM_INT_COV                   PWM_CCTL_COV
#define PWM_INT_Msk                   (PWM_INT_CCIFG | PWM_INT_COV)
#define IS_PWM_INTFLAGR(__INTFLAGR__) (((__INTFLAGR__) == PWM_INT_CCIFG) ||\
                                       ((__INTFLAGR__) == PWM_INT_COV))
#define IS_PWM_INTFLAGC(__INTFLAGC__)  ((((__INTFLAGC__) & PWM_INT_Msk) != 0U) &&\
                                        (((__INTFLAGC__) & ~PWM_INT_Msk) == 0U))

//PWM output selection
#define PWM0_OUT0                  0
#define PWM0_OUT1                  1
#define PWM0_OUT2                  2
#define PWM1_OUT0                  4
#define PWM1_OUT1                  5
#define PWM1_OUT2                  6
#define PWM2_OUT0                  8
#define PWM2_OUT1                  9
#define PWM2_OUT2                  10
#define PWM3_OUT0                  12
#define PWM3_OUT1                  13
#define PWM3_OUT2                  14
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

//outline
#define PWM_OLINE_0       1
#define PWM_OLINE_1       2
#define PWM_OLINE_2       4
#define PWM_OLINE_3       8
#define PWM_OLINE_Msk     0xF
#define IS_PWM_OUTLINE(__OUTLINE__)  ((((__OUTLINE__) & PWM_OLINE_Msk) != 0U) &&\
                                      (((__OUTLINE__) & ~PWM_OLINE_Msk) == 0U))

//inline
#define PWM_ILINE_0     0
#define PWM_ILINE_1     1
#define PWM_ILINE_2     2
#define PWM_ILINE_3     3
#define IS_PWM_INLINE(__INLINE__)  (((__INLINE__) == PWM_ILINE_0) ||\
                                    ((__INLINE__) == PWM_ILINE_1) ||\
                                    ((__INLINE__) == PWM_ILINE_2) ||\
                                    ((__INLINE__) == PWM_ILINE_3))

//PWM input selection
#define PWM1_IN2         0x014
#define PWM1_IN1         0x012
#define PWM1_IN0         0x010
#define PWM0_IN2         0x004
#define PWM0_IN1         0x002
#define PWM0_IN0         0x000
#define PWM3_IN2         0x114
#define PWM3_IN1         0x112
#define PWM3_IN0         0x110
#define PWM2_IN2         0x104
#define PWM2_IN1         0x102
#define PWM2_IN0         0x100
#define IS_PWM_INSEL(__INSEL__)  (((__INSEL__) == PWM1_IN2) ||\
                                  ((__INSEL__) == PWM1_IN1) ||\
                                  ((__INSEL__) == PWM1_IN0) ||\
                                  ((__INSEL__) == PWM0_IN2) ||\
                                  ((__INSEL__) == PWM0_IN1) ||\
                                  ((__INSEL__) == PWM0_IN0) ||\
                                  ((__INSEL__) == PWM3_IN2) ||\
                                  ((__INSEL__) == PWM3_IN1) ||\
                                  ((__INSEL__) == PWM3_IN0) ||\
                                  ((__INSEL__) == PWM2_IN2) ||\
                                  ((__INSEL__) == PWM2_IN1) ||\
                                  ((__INSEL__) == PWM2_IN0))

//Level
#define PWM_LEVEL_HIGH  (0x1U << PWM_CCTL_OUT_Pos)
#define PWM_LEVEL_LOW   0
#define IS_PWM_OUTLVL(__OUTLVL__)  (((__OUTLVL__) == PWM_LEVEL_HIGH) ||\
                                    ((__OUTLVL__) == PWM_LEVEL_LOW))

#define IS_PWM_CCR(__CCR__)  ((__CCR__) < 0x10000U)


/****************************** PWM Instances *********************************/
#define IS_PWM_ALL_INSTANCE(INSTANCE) (((INSTANCE) == PWM0) || \
                                       ((INSTANCE) == PWM1) || \
                                       ((INSTANCE) == PWM2) || \
                                       ((INSTANCE) == PWM3))

#define IS_PWMMUX_ALL_INSTANCE(INSTANCE) ((INSTANCE) == PWMMUX)

/* Exported Functions ------------------------------------------------------- */
/* PWM Exported Functions Group1: 
                                   Initialization ----------------------------*/
void PWM_BaseInit(PWM_Type *PWMx, PWM_BaseInitType *InitStruct);
void PWM_BaseStructInit(PWM_BaseInitType *InitStruct);
void PWM_OCStructInit(PWM_OCInitType *OCInitType);
void PWM_OCInit(PWM_Type *PWMx, PWM_OCInitType *OCInitType);
void PWM_ICStructInit(PWM_ICInitType *ICInitType);
void PWM_ICInit(PWM_Type *PWMx, PWM_ICInitType *ICInitType);
/* PWM Exported Functions Group2: 
                                   Interrupt ---------------------------------*/
void PWM_BaseINTConfig(PWM_Type *PWMx, uint32_t NewState);
uint8_t PWM_GetBaseINTStatus(PWM_Type *PWMx);
void PWM_ClearBaseINTStatus(PWM_Type *PWMx);
void PWM_ChannelINTConfig(PWM_Type *PWMx, uint32_t Channel, uint32_t NewState);
uint8_t PWM_GetChannelINTStatus(PWM_Type *PWMx, uint32_t Channel, uint32_t IntMask);
void PWM_ClearChannelINTStatus(PWM_Type *PWMx, uint32_t Channel, uint32_t IntMask);
/* PWM Exported Functions Group3: 
                                   MISC --------------------------------------*/
void PWM_ClearCounter(PWM_Type *PWMx);
void PWM_CCRConfig(PWM_Type *PWMx, uint32_t Channel, uint16_t Period);
//Compare output
void PWM_OLineConfig(uint32_t OutSelection, uint32_t OLine);
void PWM_OutputCmd(PWM_Type *PWMx, uint32_t Channel, uint32_t NewState);
void PWM_SetOutLevel(PWM_Type *PWMx, uint32_t Channel, uint32_t Level);
void PWM_ILineConfig(uint32_t InSelection, uint32_t ILine);
uint8_t PWM_GetSCCI(PWM_Type *PWMx, uint32_t Channel);
uint32_t PWM_GetCapture(PWM_Type *PWMx, uint32_t Channel);

#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_PWM_H */

/*********************************** END OF FILE ******************************/
