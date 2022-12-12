/**
  ******************************************************************************
  * @file               ft32f0xx_comp.h
  * @author             FMD AE
  * @brief              This file contains all the functions prototypes for the COMP firmware
  *                     library
  * @version            V1.0.0
  * @data                   2021-07-01
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F0XX_COMP_H
#define __FT32F0XX_COMP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f0xx.h"

/** @addtogroup COMP
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  COMP Init structure definition
  */

typedef struct
{

  uint32_t COMP_VipSel;                     /*!< Select the positive input of the comparator.
                                          This parameter can be a value of @ref COMP_VipSel */

  uint32_t COMP_VinSel;             /*!< Select the negative input of the comparator.
                                          This parameter can be a value of @ref COMP_VinSel */

  uint32_t COMP_OutputSel;          /*!< Selects The output selection of the comparator.
                                          This parameter can be a value of @ref COMP_OutputSel */

  uint32_t COMP_Pol;                        /*!< Select the output polarity of the comparator.
                                          This parameter can be a value of @ref COMP_Pol */

}COMP_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup COMP_Exported_Constants
  * @{
  */

/** @defgroup COMP_Selection
  * @{
  */

#define NCOMP_Selection_COMP                    ((uint32_t)0x00000000) /*!< NCOMP Selection */
#define PCOMP_Selection_COMP                    ((uint32_t)0x00000010) /*!< PCOMP Selection */
#define COMP_Selection_COMP3                    ((uint32_t)0x00000001) /*!< PCOMP Selection */

#define IS_COMP_ALL_PERIPH(PERIPH) (((PERIPH) == NCOMP_Selection_COMP) || \
                                    ((PERIPH) == PCOMP_Selection_COMP))


#define COMP_Selection_COMP1                    NCOMP_Selection_COMP
#define COMP_Selection_COMP2                    PCOMP_Selection_COMP
/**
  * @}
  */

/** @defgroup COMP_VipSel
  * @{
  */

#define NCOMP_VIP_SEL_1WIRE             ((uint32_t)0x00000000)
#define NCOMP_VIP_SEL_PAD_PA1           ((uint32_t)0x00000002)
#define NCOMP_VIP_SEL_PAD_PA4           ((uint32_t)0x00000004)
#define NCOMP_VIP_SEL_PAD_PA13          ((uint32_t)0x00000006)
#define NCOMP_VIP_SEL_PAD_PB12          ((uint32_t)0x00000008)

#define PCOMP_VIP_SEL_PAD_PA3           ((uint32_t)0x00000000)
#define PCOMP_VIP_SEL_PAD_PA4           ((uint32_t)0x00020000)
#define PCOMP_VIP_SEL_PAD_PA13          ((uint32_t)0x00040000)
#define PCOMP_VIP_SEL_PAD_PB12          ((uint32_t)0x00060000)

#define COMP3_VIP_SEL_PAD_PF5           ((uint32_t)0x00000000)
#define COMP3_VIP_SEL_PAD_PB12          ((uint32_t)0x00000002)
#define COMP3_VIP_SEL_PAD_PA13          ((uint32_t)0x00000004)
#define COMP3_VIP_SEL_PAD_PA4           ((uint32_t)0x00000006)

#define IS_COMP_VIP_SEL(INPUT)  (((INPUT) == NCOMP_VIP_SEL_1WIRE) || \
                                        ((INPUT) == NCOMP_VIP_SEL_PAD_PA1)  || \
                                        ((INPUT) == NCOMP_VIP_SEL_PAD_PA4)  || \
                                        ((INPUT) == NCOMP_VIP_SEL_PAD_PA13) || \
                                        ((INPUT) == NCOMP_VIP_SEL_PAD_PB12) || \
                                        ((INPUT) == PCOMP_VIP_SEL_PAD_PA3)  || \
                                        ((INPUT) == PCOMP_VIP_SEL_PAD_PA4)  || \
                                        ((INPUT) == PCOMP_VIP_SEL_PAD_PA13) || \
                                        ((INPUT) == PCOMP_VIP_SEL_PAD_PB12)  )
/**
  * @}
  */

/** @defgroup COMP_VinSel
  * @{
  */

#define NCOMP_VIN_SEL_DAC1_OUT                  ((uint32_t)0x00000000)
#define NCOMP_VIN_SEL_PAD_PA0                   ((uint32_t)0x00000010)
#define NCOMP_VIN_SEL_PAD_PA4                   ((uint32_t)0x00000020)
#define NCOMP_VIN_SEL_PAD_PA5                   ((uint32_t)0x00000030)

#define PCOMP_VIN_SEL_DAC2_OUT                  ((uint32_t)0x00000000)
#define PCOMP_VIN_SEL_PAD_PA2                   ((uint32_t)0x00080000)
#define PCOMP_VIN_SEL_PAD_PA4                   ((uint32_t)0x00100000)
#define PCOMP_VIN_SEL_PAD_PA5                   ((uint32_t)0x00180000)

#define COMP3_VIN_SEL_PAD_PF4                   ((uint32_t)0x00000000)
#define COMP3_VIN_SEL_DAC2_OUT                  ((uint32_t)0x00000010)
#define COMP3_VIN_SEL_PAD_PA4                   ((uint32_t)0x00000020)
#define COMP3_VIN_SEL_PAD_PA5                   ((uint32_t)0x00000030)

#define IS_COMP_VINSEL(INPUT) (((INPUT) == NCOMP_VIN_SEL_DAC1_OUT) || \
                                ((INPUT) == NCOMP_VIN_SEL_PAD_PA0) || \
                                ((INPUT) == NCOMP_VIN_SEL_PAD_PA4) || \
                                ((INPUT) == NCOMP_VIN_SEL_PAD_PA5) || \
                                ((INPUT) == PCOMP_VIN_SEL_DAC2_OUT)|| \
                                ((INPUT) == PCOMP_VIN_SEL_PAD_PA2) || \
                                ((INPUT) == PCOMP_VIN_SEL_PAD_PA4) || \
                                ((INPUT) == PCOMP_VIN_SEL_PAD_PA5) )
/**
  * @}
  */

/** @defgroup COMP_OutputSel
  * @{
  */

#define COMP_OUTPUT_NO_SELECTION                    ((uint32_t)0x00000000)
#define NCOMP_OUTPUT_SEL_TIM1_CAPTURE1              ((uint32_t)0x00000200)
#define NCOMP_OUTPUT_SEL_TIM1_OCREFCLEAR            ((uint32_t)0x00000300)
#define NCOMP_OUTPUT_SEL_TIM3_CAPTURE1              ((uint32_t)0x00000600)
#define NCOMP_OUTPUT_SEL_TIM3_OCREFCLEAR            ((uint32_t)0x00000700)

#define PCOMP_OUTPUT_SEL_TIM1_BREAK                 ((uint32_t)0x01000000)
#define PCOMP_OUTPUT_SEL_TIM1_CAPTURE1              ((uint32_t)0x02000000)
#define PCOMP_OUTPUT_SEL_TIM1_OCREFCLEAR            ((uint32_t)0x03000000)
#define PCOMP_OUTPUT_SEL_TIM3_CAPTURE1              ((uint32_t)0x06000000)
#define PCOMP_OUTPUT_SEL_TIM3_OCREFCLEAR            ((uint32_t)0x07000000)

#define COMP3_OUTPUT_SEL_TIM1_CAPTURE1              ((uint32_t)0x00000200)
#define COMP3_OUTPUT_SEL_TIM1_OCREFCLEAR            ((uint32_t)0x00000300)
#define COMP3_OUTPUT_SEL_TIM3_CAPTURE1              ((uint32_t)0x00000600)
#define COMP3_OUTPUT_SEL_TIM3_OCREFCLEAR            ((uint32_t)0x00000700)

#define IS_COMP_OUTPUT_SEL(SEL) (   ((SEL) == NCOMP_OUTPUT_SEL_TIM1_CAPTURE1)   || \
                                    ((SEL) == NCOMP_OUTPUT_SEL_TIM1_OCREFCLEAR) ||\
                                    ((SEL) == NCOMP_OUTPUT_SEL_TIM3_CAPTURE1)   ||\
                                    ((SEL) == NCOMP_OUTPUT_SEL_TIM3_OCREFCLEAR) ||\
                                    ((SEL) == PCOMP_OUTPUT_SEL_TIM1_BREAK)      ||\
                                    ((SEL) == PCOMP_OUTPUT_SEL_TIM1_CAPTURE1)   ||\
                                    ((SEL) == PCOMP_OUTPUT_SEL_TIM1_OCREFCLEAR) ||\
                                    ((SEL) == PCOMP_OUTPUT_SEL_TIM3_CAPTURE1)   ||\
                                    ((SEL) == PCOMP_OUTPUT_SEL_TIM3_OCREFCLEAR) ||\
                                    ((SEL) == COMP_OUTPUT_NO_SELECTION)         )

/**
  * @}
  */

/** @defgroup COMP_Pol
  * @{
  */

#define NCOMP_POL_NOT_INVERT                ((uint32_t)0x00000000)
#define NCOMP_POL_INVERT                    ((uint32_t)0x00000800)

#define PCOMP_POL_NOT_INVERT                ((uint32_t)0x00000000)
#define PCOMP_POL_INVERT                    ((uint32_t)0x08000000)

#define COMP3_POL_NOT_INVERT                ((uint32_t)0x00000000)
#define COMP3_POL_INVERT                    ((uint32_t)0x00000800)

#define IS_COMP_POL(POL)                 (  ((POL) == NCOMP_POL_NOT_INVERT) || \
                                            ((POL) == NCOMP_POL_INVERT)     || \
                                            ((POL) == PCOMP_POL_NOT_INVERT) || \
                                            ((POL) == PCOMP_POL_INVERT)     )


/**
  * @}
  */

/**
  * @}
  */

/** @defgroup COMP_OutputLevel
  * @{
  */
/* When output polarity is not inverted, comparator output is high when
   the non-inverting input is at a higher voltage than the inverting input */
#define COMP_OutputLevel_High                   COMP_CSR_COMP1OUT
/* When output polarity is not inverted, comparator output is low when
   the non-inverting input is at a lower voltage than the inverting input*/
#define COMP_OutputLevel_Low                    ((uint32_t)0x00000000)


#define IS_COMP_OUTPUT_LEVEL(LEVEL)         (((LEVEL) == COMP_CSR_COMP1OUT) || \
                                             ((LEVEL) == COMP_CSR_COMP2OUT))
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*  Function used to set the COMP configuration to the default reset state ****/
void COMP_DeInit(void);

/* Initialization and Configuration functions *********************************/
void COMP_Init(uint32_t COMP_Selection, COMP_InitTypeDef* COMP_InitStruct);
void COMP_StructInit(COMP_InitTypeDef* COMP_InitStruct);
void COMP_Cmd(uint32_t COMP_Selection, FunctionalState NewState);
uint32_t COMP_GetOutputLevel(uint32_t COMP_Selection);

/* Window mode control function ***********************************************/
void COMP_WindowCmd(FunctionalState NewState);

/* COMP configuration locking function ****************************************/
void COMP_LockConfig(uint32_t COMP_Selection);

#ifdef __cplusplus
}
#endif

#endif /*__FT32F0XX_COMP_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
