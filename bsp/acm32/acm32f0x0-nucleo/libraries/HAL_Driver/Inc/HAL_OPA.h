/*
  ******************************************************************************
  * @file    HAL_OPA.h
  * @version V1.0.0
  * @date    2020
  * @brief   Header file of OPA HAL module.
  ******************************************************************************
*/
#ifndef __HAL_OPA_H__
#define __HAL_OPA_H__

#include "ACM32Fxx_HAL.h"

/** @defgroup OPAx Index
  * @{
  */
#define OPA1        (0x01)
#define OPA2        (0x02)
#define OPA3        (0x03)

/****************  Bit definition for OPA_CR1 and OPA_CR2 register  **************************/
#define OPA_CSR_VINPSEL_POS                    (20U)
#define OPA_CSR_VINPSEL_MASK                   (BIT23|BIT22|BIT21|BIT20)
#define OPA_CSR_VINMSEL_POS                    (16U)
#define OPA_CSR_VINMSEL_MASK                   (BIT19|BIT18|BIT17|BIT16)
#define OPA_CSR_TRIM_HIGH_POS                  (9U)
#define OPA_CSR_TRIM_HIGH_MASK                 (BIT13|BIT12|BIT11|BIT10|BIT9)
#define OPA_CSR_TRIM_LOW_POS                   (4U)
#define OPA_CSR_TRIM_LOW_MASK                  (BIT8|BIT7|BIT6|BIT5|BIT4)
#define OPA_CSR_CAL_OUT                        (BIT3)
#define OPA_CSR_CAL_H                          (BIT2)
#define OPA_CSR_CAL_L                          (BIT1)
#define OPA_CSR_EN                             (BIT0)

/**
  * @brief  OPA Configuration Structure definition
  */
typedef struct
{
    uint8_t            OpaX;        /*!< Specify witch opa be selected */
    uint8_t            VinPSel;     /*!< Specify the opa VINP vin p select */
    uint8_t            VinMSel;     /*!< Specify the opa VINM vin m select */
    uint8_t            TrimEn;      /*!< Specify if the opa auto trim */
}OPA_InitTypeDef;

/**
  * @brief  OPA handle Structure definition
  */
typedef struct
{
  OPA_TypeDef       *Instance;       /*!< Register base address    */
  OPA_InitTypeDef   Init;            /*!< OPA required parameters */
} OPA_HandleTypeDef;


#define OPA_CSR_VINPSEL_0               (0U)
#define OPA_CSR_VINPSEL_1               (1U)

#define OPA_CSR_VINMSEL_0               (0U)
#define OPA_CSR_VINMSEL_1               (1U)

#define OPA_CSR1_VINPSEL_PA4            (0U)
#define OPA_CSR1_VINPSEL_PB6            (1U)

#define OPA_CSR1_VINMSEL_PB5            (0U)
#define OPA_CSR1_VINMSEL_PD5            (1U)

#define OPA_CSR2_VINPSEL_PB3            (0U)
#define OPA_CSR2_VINPSEL_PB4            (1U)

#define OPA_CSR2_VINMSEL_PB1            (0U)
#define OPA_CSR2_VINMSEL_PD4            (1U)

#define OPA_CSR3_VINPSEL_PA7            (0U)
#define OPA_CSR3_VINPSEL_PB2            (1U)

#define OPA_CSR3_VINMSEL_PA5            (0U)
#define OPA_CSR3_VINMSEL_PC4            (1U)

#define OPA_CSR_TRIM_DISABLE           (0U)
#define OPA_CSR_TRIM_ENABLE            (1U)

/******************************** OPA Instances *******************************/
#define IS_OPA_ALL_INSTANCE(INSTANCE)      (((INSTANCE) == OPA))

/******************************** OPA OPAX definition*******************************/
#define IS_OPA_ALL_OPAX(_OPAX)             (((_OPAX) == OPA1) || \
                                            ((_OPAX) == OPA2) || \
                                            ((_OPAX) == OPA3))

/******************************** OPA VINP select definition*******************************/
#define IS_OPA_ALL_VINP(VINPSEL)           (((VINPSEL) == OPA_CSR_VINPSEL_0) || \
                                            ((VINPSEL) == OPA_CSR_VINPSEL_1))

/******************************** OPA VINM select definition*******************************/
#define IS_OPA_ALL_VINM(VINMSEL)           (((VINMSEL) == OPA_CSR_VINMSEL_0) || \
                                            ((VINMSEL) == OPA_CSR_VINMSEL_1))

/******************************** OPA trim enable definition*******************************/
#define IS_OPA_ALL_TRIM(_TRIM)             (((_TRIM) == OPA_CSR_TRIM_DISABLE) || \
                                            ((_TRIM) == OPA_CSR_TRIM_ENABLE))

/* Function : HAL_OPA */
void HAL_OPA_MspInit(OPA_HandleTypeDef* hopa);
void HAL_OPA_MspDeInit(OPA_HandleTypeDef* hopa);
HAL_StatusTypeDef HAL_OPA_Init(OPA_HandleTypeDef* hopa);
HAL_StatusTypeDef HAL_OPA_DeInit(OPA_HandleTypeDef* hopa);
HAL_StatusTypeDef HAL_OPA_Enable(OPA_HandleTypeDef* hopa);
HAL_StatusTypeDef HAL_OPA_Disable(OPA_HandleTypeDef* hopa);

#endif





