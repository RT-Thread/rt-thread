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

/****************  Bit definition for OPA_CR1 and OPA_CR2 register  **************************/
#define OPA_CSR_LOCK                           (BIT31)
#define OPA_CSR_HSM                            (BIT28)
#define OPA_CSR_GAIN_SEL_POS                   (23U)
#define OPA_CSR_GAIN_SEL_MASK                  (BIT27|BIT26|BIT25|BIT24|BIT23)
#define OPA_CSR_POL_SEL_POS                    (21U)
#define OPA_CSR_POL_SEL_MASK                   (BIT22|BIT21)
#define OPA_CSR_VINM0_SEL_POS                  (BIT20)
#define OPA_CSR_MODE_SEL_POS                   (18U)
#define OPA_CSR_MODE_SEL_MASK                  (BIT19|BIT18)
#define OPA_CSR_VINP_SEL_POS                   (16U)
#define OPA_CSR_VINP_SEL_MASK                  (BIT17|BIT16)
#define OPA_CSR_OUT_SEL_POS                    (14U)
#define OPA_CSR_OUT_SEL_MASK                   (BIT14|BIT15)
#define OPA_CSR_TRIM_OSN_POS                   (9U)
#define OPA_CSR_TRIM_OSN_MASK                  (BIT13|BIT12|BIT11|BIT10|BIT9)
#define OPA_CSR_TRIM_OSP_POS                   (4U)
#define OPA_CSR_TRIM_OSP_MASK                  (BIT8|BIT7|BIT6|BIT5|BIT4)
#define OPA_CSR_CAL_OUT                        (BIT3)
#define OPA_CSR_CAL_NEN                        (BIT2)
#define OPA_CSR_CAL_PEN                        (BIT1)
#define OPA_CSR_EN                             (BIT0)

/** @defgroup OPAx Index
  * @{
  */
#define OPA1        (0x01)
#define OPA2        (0x02)
#define OPA3        (0x03)

/** @defgroup HSM driver mode
  * @{
  */
#define OPA_HSM_LOW         (0u)
#define OPA_HSM_HIGH        (1u)

/** @defgroup OPA Gain select.
  * @{
  */
#define OPA_GAIN_64_63           (0u)
#define OPA_GAIN_32_31           (1u)
#define OPA_GAIN_16_15           (2u)
#define OPA_GAIN_8_7             (4u)
#define OPA_GAIN_4_3             (8u)
#define OPA_GAIN_2_1             (16u)

/** @defgroup Polarity select.
  * @{
  */
#define OPA_POL_NONINVERT        (0u)
#define OPA_POL_INVERT           (1u)

/** @defgroup OPA work mode select.
  * @{
  */
#define OPA_MODE_SA              (0u)
#define OPA_MODE_UG              (1u)
#define OPA_MODE_PGA             (2u)
#define OPA_MODE_SA1             (3u)

/** @defgroup OPA VINP vin p select.
  * @{
  */
#define OPA_VINP_0           (0u)
#define OPA_VINP_1           (1u)
#define OPA_VINP_2           (2u)
#define OPA_VINP_3             (3u)

/** @defgroup OPA output select.
  * @{
  */
#define OPA_OUT_GPIO             (0u)
#define OPA_OUT_INTERNAL         (1u)

/** @defgroup OPA VINM0 enable.
  * @{
  */
#define OPA_CSR_VINM0_DISABLE           (0U)   
#define OPA_CSR_VINM0_ENABLE            (1U)

/** @defgroup OPA trim enable.
  * @{
  */
#define OPA_CSR_TRIM_DISABLE           (0U)   
#define OPA_CSR_TRIM_ENABLE            (1U)   

/**
  * @brief  OPA Configuration Structure definition
  */
typedef struct
{
    uint8_t             OpaX;       /*!< Specify witch opa be selected */
    uint8_t             Hsm;        /*!< Specify the opa HSM driver mode:OPA_HSM_LOW or OPA_HSM_HIGH */
    uint8_t             Gain;       /*!< Specify the opa gain select */
    uint8_t             PolSel;     /*!< Specify the opa Polarity select */
    uint8_t             VinM0En;    /*!< Specify the opa VinM0 enable */     
    uint8_t             OpaMode;    /*!< Specify the opa work mode select */
    uint8_t             VinPSel;    /*!< Specify the opa VINP vin p select */       
    uint8_t             OutSel;     /*!< Specify the opa output select */  
    uint8_t             TrimEn;     /*!< Specify if the opa auto trim */  
}OPA_InitTypeDef;

/**
  * @brief  OPA handle Structure definition
  */
typedef struct
{
  OPA_TypeDef       *Instance;       /*!< Register base address    */
  OPA_InitTypeDef   Init;            /*!< OPA required parameters */
} OPA_HandleTypeDef;

/******************************** OPA Instances *******************************/
#define IS_OPA_ALL_INSTANCE(INSTANCE)      (((INSTANCE) == OPA))

/******************************** OPA OPAX definition*******************************/
#define IS_OPA_ALL_OPAX(_OPAX)         (((_OPAX) == OPA1) || \
                                        ((_OPAX) == OPA2) || \
                                        ((_OPAX) == OPA3))

/******************************** OPA HSM definition*******************************/
#define IS_OPA_ALL_HSM(_HSM)           (((_HSM) == OPA_HSM_LOW) || \
                                        ((_HSM) == OPA_HSM_HIGH))

/******************************** OPA GAIN definition*******************************/
#define IS_OPA_ALL_GAIN(_GAIN)         (((_GAIN) == OPA_GAIN_64_63) || \
                                        ((_GAIN) == OPA_GAIN_32_31) || \
                                        ((_GAIN) == OPA_GAIN_16_15) || \
                                        ((_GAIN) == OPA_GAIN_8_7) || \
                                        ((_GAIN) == OPA_GAIN_4_3) || \
                                        ((_GAIN) == OPA_GAIN_2_1))

/******************************** OPA Polarity definition*******************************/
#define IS_OPA_ALL_POL(_POL)           (((_POL) == OPA_POL_NONINVERT) || \
                                        ((_POL) == OPA_POL_INVERT))

/******************************** OPA work mode definition*******************************/
#define IS_OPA_ALL_MODE(_MODE)         (((_MODE) == OPA_MODE_SA) || \
                                        ((_MODE) == OPA_MODE_UG) || \
                                        ((_MODE) == OPA_MODE_PGA) || \
                                        ((_MODE) == OPA_MODE_SA1))
                                        
/******************************** OPA VINP select definition*******************************/
#define IS_OPA_ALL_VINP(_VINP)         (((_VINP) == OPA_VINP_0) || \
                                        ((_VINP) == OPA_VINP_1) || \
                                        ((_VINP) == OPA_VINP_2) || \
                                        ((_VINP) == OPA_VINP_3))
                                        
/******************************** OPA OUT select definition*******************************/
#define IS_OPA_ALL_OUT(_OUT)           (((_OUT) == OPA_OUT_GPIO) || \
                                        ((_OUT) == OPA_OUT_INTERNAL))

/******************************** OPA VINM0 enable definition*******************************/
#define IS_OPA_ALL_VINM0(_VINM0)       (((_VINM0) == OPA_CSR_VINM0_DISABLE) || \
                                        ((_VINM0) == OPA_CSR_VINM0_ENABLE))
                                        
/******************************** OPA trim enable definition*******************************/
#define IS_OPA_ALL_TRIM(_TRIM)         (((_TRIM) == OPA_CSR_TRIM_DISABLE) || \
                                        ((_TRIM) == OPA_CSR_TRIM_ENABLE))

/* Function : HAL_OPA */
void HAL_OPA_MspInit(OPA_HandleTypeDef* hopa);
void HAL_OPA_MspDeInit(OPA_HandleTypeDef* hopa);
HAL_StatusTypeDef HAL_OPA_Init(OPA_HandleTypeDef* hopa);
HAL_StatusTypeDef HAL_OPA_DeInit(OPA_HandleTypeDef* hopa);
HAL_StatusTypeDef HAL_OPA_Enable(OPA_HandleTypeDef* hopa);
HAL_StatusTypeDef HAL_OPA_Disable(OPA_HandleTypeDef* hopa);
HAL_StatusTypeDef HAL_OPA_Lock(OPA_HandleTypeDef* hopa);

#endif





