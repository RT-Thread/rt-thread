/*
  ******************************************************************************
  * @file    HAL_COMP.h
  * @version V1.0.0
  * @date    2020
  * @brief   Header file of COMP HAL module.
  ******************************************************************************
*/
#ifndef __HAL_COMP_H__
#define __HAL_COMP_H__

#include "ACM32Fxx_HAL.h"

#define COMP1        (0x01)
#define COMP2        (0x02)

/****************  Bit definition for COMP_CR1 and COMP_CR2 register  **************************/
#define COMP_CR_LOCK                            (BIT31)
#define COMP_CR_BLANKTIME_POS                   (29U)
#define COMP_CR_BLANKTIME_MASK                  (BIT30|BIT29)
#define COMP_CR_CRV_CFG_POS                     (25U)
#define COMP_CR_CRV_CFG_MASK                    (BIT28|BIT27|BIT26|BIT25)
#define COMP_CR_CRV_SEL                         (BIT24)
#define COMP_CR_CRV_EN                          (BIT23)
#define COMP_CR_WINMODE                         (BIT22)
#define COMP_CR_WINOUT                          (BIT21)
#define COMP_CR_POLARITY                        (BIT20)
#define COMP_CR_FLTEN                           (BIT19)
#define COMP_CR_FLTTIME_POS                     (16U)
#define COMP_CR_FLTTIME_MASK                    (BIT18|BIT17|BIT16)
#define COMP_CR_BLANKSEL_POS                    (12U)
#define COMP_CR_BLANKSEL_MASK                   (BIT15|BIT14|BIT13|BIT12)
#define COMP_CR_INPSEL_POS                      (8U)
#define COMP_CR_INPSEL_MASK                     (BIT11|BIT10|BIT9|BIT8)
#define COMP_CR_INMSEL_POS                      (4U)
#define COMP_CR_INMSEL_MASK                     (BIT7|BIT6|BIT5|BIT4)
#define COMP_CR_HYS_POS                         (1U)
#define COMP_CR_HYS_MASK                        (BIT3|BIT2|BIT1)
#define COMP_CR_EN                              (BIT0)

/****************  Bit definition for COMP_SR register  **************************/
#define COMP_SR_VCOUT2_ORG                      (BIT3)
#define COMP_SR_VCOUT1_ORG                      (BIT2)
#define COMP_SR_VCOUT2                          (BIT1)
#define COMP_SR_VCOUT1                          (BIT0)

/**
  * @brief  COMP Configuration Structure definition
  */
typedef struct
{
    uint8_t             Comparator;        /*!< Specify witch comparator be selected */
    uint32_t            Crv_En;
    uint32_t            BlankTime;
    uint32_t            Crv_Sel;
    uint32_t            Crv_Cfg;
    uint32_t            WinMode;
    uint32_t            WinOut;
    uint32_t            Polarity;
    uint32_t            FltEn;
    uint32_t            FltTime;
    uint32_t            BlankSel;
    uint32_t            InPSel;
    uint32_t            InMSel;
    uint32_t            HYS;
}COMP_InitTypeDef;

/**
  * @brief  COMP handle Structure definition
  */
typedef struct
{
  COMP_TypeDef       *Instance;       /*!< Register base address    */
  COMP_InitTypeDef   Init;            /*!< COMP required parameters */
  uint8_t            OutputLevel_Org; /*!< COMP OutputLevel original */
  uint8_t            OutputLevel;     /*!< COMP OutputLevel with filter */
} COMP_HandleTypeDef;

#define COMP_CR_CRV_EN_DISABLE           (0U)
#define COMP_CR_CRV_EN_ENABLE            (1U)

#define COMP_CR_CRV_SEL_AVDD             (0U)
#define COMP_CR_CRV_SEL_VREF             (1U)

#define COMP_CR1_WINMODE_COMP1_INPSEL           (0U)
#define COMP_CR1_WINMODE_COMP2_INPSEL           (1U)

#define COMP_CR2_WINMODE_COMP2_INPSEL           (0U)
#define COMP_CR2_WINMODE_COMP1_INPSEL           (1U)

#define COMP_CR1_WINOUT_VCOUT1                 (0U)
#define COMP_CR2_WINOUT_VCOUT2                 (0U)
#define COMP_CR_WINOUT_VCOUT12                 (1U)

#define COMP_CR_POLARITY_P                     (0U)
#define COMP_CR_POLARITY_N                     (1U)

#define COMP_CR_FLTEN_DISABLE                  (0U)
#define COMP_CR_FLTEN_ENABLE                   (1U)

#define COMP_CR_FLTTIME_1_CLK                  (0U)
#define COMP_CR_FLTTIME_2_CLK                  (1U)
#define COMP_CR_FLTTIME_4_CLK                  (2U)
#define COMP_CR_FLTTIME_16_CLK                 (3U)
#define COMP_CR_FLTTIME_64_CLK                 (4U)
#define COMP_CR_FLTTIME_256_CLK                (5U)
#define COMP_CR_FLTTIME_1024_CLK               (6U)
#define COMP_CR_FLTTIME_4095_CLK               (7U)

#define COMP_CR_BLANKTIME_32_CLK               (0U)
#define COMP_CR_BLANKTIME_64_CLK               (1U)
#define COMP_CR_BLANKTIME_128_CLK              (2U)
#define COMP_CR_BLANKTIME_256_CLK              (3U)

#define COMP_CR_BLANKSEL_NONE                  (0U)
#define COMP_CR_BLANKSEL_1                     (1U)
#define COMP_CR_BLANKSEL_2                     (2U)
#define COMP_CR_BLANKSEL_3                     (4U)
#define COMP_CR_BLANKSEL_4                     (8U)

#define COMP_CR_INPSEL_0                      (0U)
#define COMP_CR_INPSEL_1                      (1U)
#define COMP_CR_INPSEL_2                      (2U)

#define COMP_CR_INMSEL_0                      (0U)
#define COMP_CR_INMSEL_1                      (1U)
#define COMP_CR_INMSEL_2                      (2U)
#define COMP_CR_INMSEL_3                      (3U)

#define COMP_CR_HYS_DISABLE                   (0U)
#define COMP_CR_HYS_1                         (4U)
#define COMP_CR_HYS_2                         (5U)
#define COMP_CR_HYS_3                         (6U)
#define COMP_CR_HYS_4                         (7U)

/******************************** COMP Instances *******************************/
#define IS_COMP_ALL_INSTANCE(INSTANCE)    ((INSTANCE) == COMP)
#define IS_COMP_ALL_COMP(_COMP)     (((_COMP) == COMP1) || \
                                  ((_COMP) == COMP2))

#define IS_COMP_ALL_CRV_EN(_CRV_EN)        (((_CRV_EN) == COMP_CR_CRV_EN_DISABLE) || \
                                           ((_CRV_EN) == COMP_CR_CRV_EN_ENABLE))

#define IS_COMP_ALL_CRV_SEL(_CRV_SEL)      (((_CRV_SEL) == COMP_CR_CRV_SEL_AVDD) || \
                                           ((_CRV_SEL) == COMP_CR_CRV_SEL_VREF))

#define IS_COMP_ALL_CRV_CFG(_CRV_CFG)      ((_CRV_CFG) <= 15U)

#define IS_COMP_ALL_WINMODE(WINMODE)       (((WINMODE) == COMP_CR1_WINMODE_COMP1_INPSEL) || \
                                           ((WINMODE) == COMP_CR1_WINMODE_COMP2_INPSEL) || \
                                           ((WINMODE) == COMP_CR2_WINMODE_COMP2_INPSEL) || \
                                           ((WINMODE) == COMP_CR2_WINMODE_COMP1_INPSEL))

#define IS_COMP_ALL_WINOUT(_WINOUT)        (((_WINOUT) == COMP_CR1_WINOUT_VCOUT1) || \
                                           ((_WINOUT) == COMP_CR2_WINOUT_VCOUT2) || \
                                           ((_WINOUT) == COMP_CR_WINOUT_VCOUT12))

#define IS_COMP_ALL_POLARITY(POLARITY)     (((POLARITY) == COMP_CR_POLARITY_N) || \
                                           ((POLARITY) == COMP_CR_POLARITY_P))

#define IS_COMP_ALL_FLTEN(FLTEN)           (((FLTEN) == COMP_CR_FLTEN_DISABLE) || \
                                           ((FLTEN) == COMP_CR_FLTEN_ENABLE))

#define IS_COMP_ALL_FLTTIME(FLTTIME)       (((FLTTIME) == COMP_CR_FLTTIME_1_CLK) || \
                                           ((FLTTIME) == COMP_CR_FLTTIME_2_CLK) || \
                                           ((FLTTIME) == COMP_CR_FLTTIME_4_CLK) || \
                                           ((FLTTIME) == COMP_CR_FLTTIME_16_CLK) || \
                                           ((FLTTIME) == COMP_CR_FLTTIME_64_CLK) || \
                                           ((FLTTIME) == COMP_CR_FLTTIME_256_CLK) || \
                                           ((FLTTIME) == COMP_CR_FLTTIME_1024_CLK) || \
                                           ((FLTTIME) == COMP_CR_FLTTIME_4095_CLK))

#define IS_COMP_ALL_BLANKTIME(BLANKTIME)   (((BLANKTIME) == COMP_CR_BLANKTIME_32_CLK) || \
                                           ((BLANKTIME) == COMP_CR_BLANKTIME_64_CLK) || \
                                           ((BLANKTIME) == COMP_CR_BLANKTIME_128_CLK) || \
                                           ((BLANKTIME) == COMP_CR_BLANKTIME_256_CLK))

#define IS_COMP_ALL_BLANKSEL(BLANKSEL)     (((BLANKSEL) == COMP_CR_BLANKSEL_NONE) || \
                                           ((BLANKSEL) == COMP_CR_BLANKSEL_1) || \
                                           ((BLANKSEL) == COMP_CR_BLANKSEL_2) || \
                                           ((BLANKSEL) == COMP_CR_BLANKSEL_3) || \
                                           ((BLANKSEL) == COMP_CR_BLANKSEL_4))

#define IS_COMP_ALL_INPSEL(INPSEL)         (((INPSEL) == COMP_CR_INPSEL_0) || \
                                           ((INPSEL) == COMP_CR_INPSEL_1) || \
                                           ((INPSEL) == COMP_CR_INPSEL_2))

#define IS_COMP_ALL_INMSEL(INMSEL)         (((INMSEL) == COMP_CR_INMSEL_0 ) || \
                                           ((INMSEL) == COMP_CR_INMSEL_1 ) || \
                                           ((INMSEL) == COMP_CR_INMSEL_2 ) || \
                                           ((INMSEL) == COMP_CR_INMSEL_3 ))

#define IS_COMP_ALL_HYS(_HYS)              (((_HYS) == COMP_CR_HYS_DISABLE) || \
                                           ((_HYS) == COMP_CR_HYS_1) || \
                                           ((_HYS) == COMP_CR_HYS_2) || \
                                           ((_HYS) == COMP_CR_HYS_3) || \
                                           ((_HYS) == COMP_CR_HYS_4))

/* Function */
void HAL_COMP_MspInit(COMP_HandleTypeDef* hcomp);
void HAL_COMP_MspDeInit(COMP_HandleTypeDef* hcomp);
HAL_StatusTypeDef HAL_COMP_Init(COMP_HandleTypeDef* hcomp);
HAL_StatusTypeDef HAL_COMP_DeInit(COMP_HandleTypeDef* hcomp);
HAL_StatusTypeDef HAL_COMP_Enable(COMP_HandleTypeDef* hcomp);
HAL_StatusTypeDef HAL_COMP_Disable(COMP_HandleTypeDef* hcomp);
HAL_StatusTypeDef HAL_COMP_GetOutputLevel(COMP_HandleTypeDef* hcomp);
HAL_StatusTypeDef HAL_COMP_Lock(COMP_HandleTypeDef* hcomp);
HAL_StatusTypeDef HAL_COMP_Start(COMP_HandleTypeDef *hcomp);
HAL_StatusTypeDef HAL_COMP_Stop(COMP_HandleTypeDef *hcomp);

#endif





