/**
  ******************************************************************************
  * @file               ft32f0xx_opa.h
  * @author             FMD AE
  * @brief              This file contains all the functions prototypes for the OPA firmware
  *                     library.
  * @version            V1.0.0
  * @data                   2021-07-01
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F0XX_OPA_H
#define __FT32F0XX_OPA_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f0xx.h"



/** @addtogroup OPA
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  OPA Init structure definition
  */

typedef struct
{

  uint32_t OPA_OP0PSel;     /*!< Select the positive input of the OPA.
                                          This parameter can be a value of @ref OPA_OP0PSel */

  uint32_t OPA_OP0NSel;             /*!< Select the negative input of the OPA.
                                          This parameter can be a value of @ref OPA_OP0NSel */

  uint32_t OPA_OP0FR;          /*!< Selects The feedback resister of the OPA.
                                          This parameter can be a value of @ref OPA_OP0FR */

  uint32_t OPA_OP0FCAPE;   /*!< Selects The compensate cap of the OPA.
                                          This parameter can be a value of @ref OPA_OP0FCAPE */

 uint32_t OPA_OPTODIG;  /*!< Selects The output to REG of the OPA.
                                          This parameter can be a value of @ref OPA_OPTODIG */

 uint32_t OPA_OPTOIO;   /*!< Selects The output to PA0 of the OPA.
                                          This parameter can be a value of @ref OPA_OPTOIO */

}OPA_InitTypeDef;

/* Exported constants --------------------------------------------------------*/
/**
  * @}
  */
/** @defgroup OPA_Exported_Constants
  * @{
  */
#define IS_OPA_ALL_PERIPH(PERIPH) (((PERIPH) == OPA) || ((PERIPH) == OPA2))

/** @defgroup OPA_OP0PSel
  * @{
  */

#define OPA_VIP_SEL_PA1         ((uint32_t)0x00000000)
#define OPA_VIP_SEL_GND         ((uint32_t)0x00008000)

#define OPA1_VIP_SEL_PA1        OPA_VIP_SEL_PA1
#define OPA1_VIP_SEL_GND        OPA_VIP_SEL_GND

#define OPA2_VIP_SEL_PA3        ((uint32_t)0x00000000)
#define OPA2_VIP_SEL_PA4        ((uint32_t)0x00020000)
#define OPA2_VIP_SEL_GND        ((uint32_t)0x00008000)

#define IS_OPA_VIP_SEL(INPUT)   (  ((INPUT) == OPA_VIP_SEL_PA1)     || \
                                    ((INPUT) == OPA2_VIP_SEL_PA4)   || \
                                    ((INPUT) == OPA_VIP_SEL_GND) )

/**
  * @}
  */

/** @defgroup OPA_OP0NSel
  * @{
  */
#define OPA_VIN_SEL_GND         ((uint32_t)0x00000000)
#define OPA_VIN_SEL_PA2         ((uint32_t)0x00002000)
#define OPA_VIN_SEL_R4K_PA2     ((uint32_t)0x00004000)
#define OPA_VIN_SEL_R4K_GND     ((uint32_t)0x00006000)

#define OPA2_VIN_SEL_GND            ((uint32_t)0x00000000)
#define OPA2_VIN_SEL_PF4            ((uint32_t)0x00002000)
#define OPA2_VIN_SEL_R4K_PF4        ((uint32_t)0x00004000)
#define OPA2_VIN_SEL_R4K_GND        ((uint32_t)0x00006000)

#define IS_OPA_VIN_SEL(INPUT)   ( ((INPUT) == OPA_VIN_SEL_GND)      || \
                                  ((INPUT) == OPA_VIN_SEL_PA2)      || \
                                  ((INPUT) == OPA_VIN_SEL_R4K_PA2)  || \
                                  ((INPUT) == OPA_VIN_SEL_R4K_GND) )

/**
  * @}
  */

/** @defgroup OPA_OP0FR
  * @{
  */

#define OPA_FR_SEL_NORES        ((uint32_t)0x00000000)
#define OPA_FR_SEL_40K          ((uint32_t)0x00001000)
#define OPA_FR_SEL_80K          ((uint32_t)0x00001400)
#define OPA_FR_SEL_160K         ((uint32_t)0x00001800)
#define OPA_FR_SEL_320K         ((uint32_t)0x00001C00)

#define OPA2_FR_SEL_NORES       ((uint32_t)0x00000000)
#define OPA2_FR_SEL_40K         ((uint32_t)0x00001000)
#define OPA2_FR_SEL_80K         ((uint32_t)0x00001400)
#define OPA2_FR_SEL_160K        ((uint32_t)0x00001800)
#define OPA2_FR_SEL_320K        ((uint32_t)0x00001C00)

#define IS_OPA_FR_SEL(INPUT)    (   ((INPUT) == OPA_FR_SEL_NORES)   || \
                                        ((INPUT) == OPA_FR_SEL_40K)     || \
                                        ((INPUT) == OPA_FR_SEL_80K)     || \
                                        ((INPUT) == OPA_FR_SEL_160K)    || \
                                        ((INPUT) == OPA_FR_SEL_320K)    )

/**
  * @}
  */

/** @defgroup OPA_OP0FCAPE
  * @{
  */

#define OPA_FCAP_SEL_EN             ((uint32_t)0x00000000)
#define OPA_FCAP_SEL_DIS            ((uint32_t)0x00000200)

#define OPA2_FCAP_SEL_EN            ((uint32_t)0x00000000)
#define OPA2_FCAP_SEL_DIS           ((uint32_t)0x00000200)

#define IS_OPA_FCAP_SEL(INPUT)  (((INPUT) == OPA_FCAP_SEL_EN) || \
                                             ((INPUT) == OPA_FCAP_SEL_DIS))


/**
  * @}
  */

/** @defgroup OPA_OPTODIG
  * @{
  */

#define OPA_ODIG_SEL_DIS            ((uint32_t)0x00000000)
#define OPA_ODIG_SEL_EN             ((uint32_t)0x00000080)

#define OPA2_ODIG_SEL_DIS           ((uint32_t)0x00000000)
#define OPA2_ODIG_SEL_EN            ((uint32_t)0x00000080)

#define IS_OPA_ODIG_SEL(INPUT)      (((INPUT) == OPA_ODIG_SEL_DIS) || \
                                             ((INPUT) == OPA_ODIG_SEL_EN))


/**
  * @}
  */

/** @defgroup OPA_OPTOIO
  * @{
  */

#define OPA_OIO_SEL_DIS         ((uint32_t)0x00000000)
#define OPA_OIO_SEL_EN          ((uint32_t)0x00000040)

#define OPA2_OIO_SEL_DIS        ((uint32_t)0x00000000)
#define OPA2_OIO_SEL_EN         ((uint32_t)0x00000040)

#define IS_OPA_OIO_SEL(INPUT)               (((INPUT) == OPA_OIO_SEL_DIS) || \
                                             ((INPUT) == OPA_OIO_SEL_EN))


#define OPA_OutputLevel_High                   ((uint32_t)0x00010000)
#define OPA_OutputLevel_Low                    ((uint32_t)0x00000000)


#define IS_OPA_OUTPUT_LEVEL(LEVEL)          (   ((LEVEL) == OPA_OutputLevel_High) || \
                                                ((LEVEL) == OPA_OutputLevel_Low))




/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*  Function used to set the OPA configuration to the default reset state ****/
void OPA_DeInit(OPA_TypeDef* OPAx);

/* Initialization and Configuration functions *********************************/
void OPA_Init(OPA_TypeDef* OPAx, OPA_InitTypeDef* OPA_InitStruct);
void OPA_StructInit(OPA_InitTypeDef* OPA_InitStruct);
void OPA_Cmd(OPA_TypeDef* OPAx, FunctionalState NewState);
uint32_t OPA_GetOutputLevel(OPA_TypeDef* OPAx, uint32_t OPA_OutLevel);
uint8_t OPA_Cali(OPA_TypeDef* OPAx);

#ifdef __cplusplus
}
#endif

#endif /*__FT32F0XX_OPA_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
