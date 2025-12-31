/**
  ******************************************************************************
  * @file               ft32f4xx_opamp.c
  * @author             FMD AE
  * @brief              This file provides firmware functions to manage the following
  *                     functionalities of the comparators (OPA1 and OPA2) peripheral
  *                     applicable only on FT32F030 devices:
  *                 + Comparators configuration
  *                 + Window mode control
  * @version            V1.0.0
  * @data                   2025-03-31
    ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_OPAMP_H
#define __FT32F4XX_OPAMP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"
/* Exported types ------------------------------------------------------------*/
/** @defgroup opamp Exported_Types opamp Exported Types
  * @{
  */
/**
  * @brief  opamp Init structure definition
  */
typedef struct
{

    uint32_t OPA_VPSEL;          /*!< Select the 1 level positive input of the OPA.
                               This parameter can be a value of @ref OPA_VPSEL */

    uint32_t OPA_VMSEL;          /*!< Select the 1 level negative input of the OPA.
                               This parameter can be a value of @ref OPA_VMSEL */

    uint32_t OPA_VPSSEL;         /*!< Select the 2 level positive input of the OPA.
                               This parameter can be a value of @ref OPA_VPSSEL */

    uint32_t OPA_VMSSEL;         /*!< Select the 2 level negative input of the OPA.
                               This parameter can be a value of @ref OPA_VMSSEL */

    uint32_t T8_CM;             /*!< Select the VM SEL of 1 or 2 level input by time8.
                               This parameter can be a value of @ref  T8_CM*/

    uint32_t T1_CM;             /*!< Select the VM SEL of 1 or 2 level input by time1.
                               This parameter can be a value of @ref  T1_CM */

    uint32_t OPAHSM;            /*!< Select the high or low speed of the OPA.
                               This parameter can be a value of @ref  OPAHSM*/

    uint32_t OPINTOEN;          /*!< Select the output to pad or ADC inside.
                               This parameter can be a value of @ref OPINTOEN  */

    uint32_t O2PADSEL;          /*!< Select the output pad of the OPA1 or OPA2.
                               This parameter can be a value of @ref  O2PADSEL*/

    uint32_t OPA_PGAGAIN;       /*!< Select the amplification value.
                               This parameter can be a value of @ref OPA_PGAGAIN */

} OPA_InitTypeDef;


/** @defgroup OPAMP_Selection
  * @{
  */
#define  OPAMP_1            ((uint32_t)0x00000001) /*!< OPAMP1 Selection */
#define  OPAMP_2            ((uint32_t)0x00000010) /*!< OPAMP2 Selection */
#define  OPAMP_3            ((uint32_t)0x00000100) /*!< OPAMP3 Selection */

#define IS_OPAX_PERIPH(PERIPH) (((PERIPH) == OPAMP_1) || \
                               ((PERIPH) == OPAMP_2) || \
                               ((PERIPH) == OPAMP_3))


/** @defgroup OPA_VPSEL
  * @{
  */
#define OPA1_VIP_SEL_PA0            ((uint32_t)0x00000000)    /*opamp1*/
#define OPA1_VIP_SEL_PC3            ((uint32_t)0x00000002)
#define OPA1_VIP_SEL_PA6            ((uint32_t)0x00000004)
#define OPA1_VIP_SEL_PA2            ((uint32_t)0x00000006)
#define OPA1_VIP_SEL_DAC1           ((uint32_t)0x00000008)
#define OPA1_VIP_SEL_TRIM         ((uint32_t)0x0000000a)
#define OPA1_VIP_SEL_VSSA           ((uint32_t)0x0000000c)

#define OPA2_VIP_SEL_PA6            ((uint32_t)0x00000000)    /*opamp2*/
#define OPA2_VIP_SEL_PB1            ((uint32_t)0x00000002)
#define OPA2_VIP_SEL_TRIM         ((uint32_t)0x0000000a)
#define OPA2_VIP_SEL_VSSA           ((uint32_t)0x0000000c)

#define OPA3_VIP_SEL_PB11           ((uint32_t)0x00000000)    /*opamp3*/
#define OPA3_VIP_SEL_PB2            ((uint32_t)0x00000002)
#define OPA3_VIP_SEL_PC5            ((uint32_t)0x00000004)
#define OPA3_VIP_SEL_DAC2           ((uint32_t)0x00000008)
#define OPA3_VIP_SEL_TRIM         ((uint32_t)0x0000000a)
#define OPA3_VIP_SEL_VSSA           ((uint32_t)0x0000000c)

#define IS_OPA_VIP_SEL(INPUT)   (((INPUT) ==OPA1_VIP_SEL_PA0 )  || \
                                                  ((INPUT) ==OPA1_VIP_SEL_PC3 )   || \
                                                  ((INPUT) ==OPA1_VIP_SEL_PA6 )   || \
                                                  ((INPUT) ==OPA1_VIP_SEL_PA2 )   || \
                                                  ((INPUT) ==OPA1_VIP_SEL_DAC1 )    || \
                                                  ((INPUT) ==OPA1_VIP_SEL_TRIM )    || \
                                                  ((INPUT) ==OPA1_VIP_SEL_VSSA )    || \
                                                  ((INPUT) ==OPA2_VIP_SEL_PA6 )   || \
                                                  ((INPUT) ==OPA2_VIP_SEL_PB1 )   || \
                                                  ((INPUT) ==OPA2_VIP_SEL_TRIM )    || \
                                                  ((INPUT) ==OPA2_VIP_SEL_VSSA )    || \
                                                  ((INPUT) ==OPA3_VIP_SEL_PB11 )    || \
                                                  ((INPUT) ==OPA3_VIP_SEL_PB2  )    || \
                                                  ((INPUT) ==OPA3_VIP_SEL_PC5  )    || \
                                                  ((INPUT) ==OPA3_VIP_SEL_DAC2 )    || \
                                                  ((INPUT) ==OPA3_VIP_SEL_TRIM )    || \
                                                  ((INPUT) ==OPA3_VIP_SEL_VSSA ) )

/** @defgroup OPA_VMSEL
  * @{
  */
#define OPA1_VIM_SEL_PA1            ((uint32_t)0x00000000)  /*opamp1*/
#define OPA1_VIM_SEL_PC2            ((uint32_t)0x00000010)
#define OPA1_VIM_SEL_PA2            ((uint32_t)0x00000020)
#define OPA1_VIM_SEL_PA4            ((uint32_t)0x00000030)
#define OPA1_VIM_SEL_FOLLOW   ((uint32_t)0x00000040)
#define OPA1_VIM_SEL_PGA          ((uint32_t)0x00000050)

#define OPA2_VIM_SEL_PA7            ((uint32_t)0x00000000)  /*opamp2*/
#define OPA2_VIM_SEL_PA4            ((uint32_t)0x00000010)
#define OPA2_VIM_SEL_FOLLOW   ((uint32_t)0x00000040)
#define OPA2_VIM_SEL_PGA          ((uint32_t)0x00000050)

#define OPA3_VIM_SEL_PB11           ((uint32_t)0x00000000)  /*opamp3*/
#define OPA3_VIM_SEL_PB2        ((uint32_t)0x00000010)
#define OPA3_VIM_SEL_PC5            ((uint32_t)0x00000020)
#define OPA3_VIM_SEL_FOLLOW     ((uint32_t)0x00000040)
#define OPA3_VIM_SEL_PGA            ((uint32_t)0x00000050)

#define IS_OPA_VIM_SEL(INPUT)   (((INPUT)== OPA1_VIM_SEL_PA1            ) || \
                                                  ((INPUT) == OPA1_VIM_SEL_PC2          )   || \
                                                  ((INPUT) == OPA1_VIM_SEL_PA2          )   || \
                                                  ((INPUT) == OPA1_VIM_SEL_PA4          )   || \
                                                  ((INPUT) == OPA1_VIM_SEL_FOLLOW     ) || \
                                                  ((INPUT) == OPA1_VIM_SEL_PGA        ) || \
                                                  ((INPUT) == OPA2_VIM_SEL_PA7        ) || \
                                                  ((INPUT) == OPA2_VIM_SEL_PA4        ) || \
                                                  ((INPUT) == OPA2_VIM_SEL_FOLLOW   )   || \
                                                  ((INPUT) == OPA2_VIM_SEL_PGA        ) || \
                                                  ((INPUT) == OPA3_VIM_SEL_PB11       ) || \
                                                  ((INPUT) == OPA3_VIM_SEL_PB2      )   || \
                                                  ((INPUT) == OPA3_VIM_SEL_PC5        ) || \
                                                  ((INPUT) == OPA3_VIM_SEL_FOLLOW     ) || \
                                                  ((INPUT) == OPA3_VIM_SEL_PGA          ))


/** @defgroup OPA_VPSSEL
  * @{
  */
#define OPA1_VIPS_SEL_PA0           ((uint32_t)0x00000000)    /*opamp1*/
#define OPA1_VIPS_SEL_PC3           ((uint32_t)0x00000004)
#define OPA1_VIPS_SEL_PA6           ((uint32_t)0x00000008)
#define OPA1_VIPS_SEL_PA2           ((uint32_t)0x0000000c)
#define OPA1_VIPS_SEL_DAC1      ((uint32_t)0x00000010)
#define OPA1_VIPS_SEL_VSSA      ((uint32_t)0x0000001c)

#define OPA2_VIPS_SEL_PA6           ((uint32_t)0x00000000)    /*opamp2*/
#define OPA2_VIPS_SEL_PB1           ((uint32_t)0x00000002)
#define OPA2_VIPS_SEL_VSSA      ((uint32_t)0x0000001c)

#define OPA3_VIPS_SEL_PB11      ((uint32_t)0x00000000)    /*opamp3*/
#define OPA3_VIPS_SEL_PB2           ((uint32_t)0x00000002)
#define OPA3_VIPS_SEL_PC5           ((uint32_t)0x00000004)
#define OPA3_VIPS_SEL_DAC2      ((uint32_t)0x00000008)
#define OPA3_VIPS_SEL_VSSA      ((uint32_t)0x0000000c)

#define IS_OPA_VIPS_SEL(INPUT)  (((INPUT) ==OPA1_VIPS_SEL_PA0 )     || \
                                                  ((INPUT) ==OPA1_VIPS_SEL_PC3  )     || \
                                                  ((INPUT) ==OPA1_VIPS_SEL_PA6  )     || \
                                                  ((INPUT) ==OPA1_VIPS_SEL_PA2  )     || \
                                                  ((INPUT) ==OPA1_VIPS_SEL_DAC1)      || \
                                                  ((INPUT) ==OPA1_VIPS_SEL_VSSA)      || \
                                                  ((INPUT) ==OPA2_VIPS_SEL_PA6)     || \
                                                  ((INPUT) ==OPA2_VIPS_SEL_PB1)     || \
                                                  ((INPUT) ==OPA2_VIPS_SEL_VSSA)      || \
                                                  ((INPUT) ==OPA3_VIPS_SEL_PB11)      || \
                                                  ((INPUT) ==OPA3_VIPS_SEL_PB2)     || \
                                                  ((INPUT) ==OPA3_VIPS_SEL_PC5)     || \
                                                  ((INPUT) ==OPA3_VIPS_SEL_DAC2)      || \
                                                  ((INPUT) ==OPA3_VIPS_SEL_VSSA))

/** @defgroup OPA_VMSSEL
  * @{
  */
#define OPA1_VIMS_SEL_00            ((uint32_t)0x00000000)  /*opamp1*/
#define OPA1_VIMS_SEL_01            ((uint32_t)0x00000001)
#define OPA1_VIMS_SEL_10            ((uint32_t)0x00000002)
#define OPA1_VIMS_SEL_11            ((uint32_t)0x00000003)

#define OPA2_VIMS_SEL_00            ((uint32_t)0x00000000)  /*opamp2*/
#define OPA2_VIMS_SEL_01            ((uint32_t)0x00000001)
#define OPA2_VIMS_SEL_10        ((uint32_t)0x00000002)
#define OPA2_VIMS_SEL_11          ((uint32_t)0x00000003)

#define OPA3_VIMS_SEL_00        ((uint32_t)0x00000000)  /*opamp3*/
#define OPA3_VIMS_SEL_01            ((uint32_t)0x00000001)
#define OPA3_VIMS_SEL_10          ((uint32_t)0x00000002)
#define OPA3_VIMS_SEL_11            ((uint32_t)0x00000003)

#define IS_OPA_VIMS_SEL(INPUT)  (((INPUT)==OPA1_VIMS_SEL_00)  || \
                                                  ((INPUT) ==OPA1_VIMS_SEL_01)  || \
                                                  ((INPUT) ==OPA1_VIMS_SEL_10)  || \
                                                  ((INPUT) ==OPA1_VIMS_SEL_11)  || \
                                                  ((INPUT) ==OPA2_VIMS_SEL_00)  || \
                                                  ((INPUT) ==OPA2_VIMS_SEL_01)  || \
                                                  ((INPUT) ==OPA2_VIMS_SEL_10)  || \
                                                  ((INPUT) ==OPA2_VIMS_SEL_11)  || \
                                                  ((INPUT) ==OPA3_VIMS_SEL_00)  || \
                                                  ((INPUT) ==OPA3_VIMS_SEL_01)  || \
                                                  ((INPUT) ==OPA3_VIMS_SEL_10)  || \
                                                  ((INPUT) ==OPA3_VIMS_SEL_11))


/** @defgroup T8_CM
  * @{
  */
#define  OPAMP_TIM8_EN                ((uint32_t)0x00000000) /*!< DISABLE tim8  */
#define  OPAMP_TIM8_DIS               ((uint32_t)0x00000040) /*!< ENABLE tim8 to AUTOchange */

#define IS_OPAX_TIM8_EN(SEL) (((SEL) == OPAMP_TIM8_EN) || \
                              ((SEL) == OPAMP_TIM8_DIS))

/** @defgroup T1_CM
  * @{
  */
#define  OPAMP_TIM1_EN                ((uint32_t)0x00000000) /*!< DISABLE tim1  */
#define  OPAMP_TIM1_DIS               ((uint32_t)0x00000020) /*!< ENABLE tim1 to AUTOchange */

#define IS_OPAX_TIM1_EN(SEL) (((SEL) == OPAMP_TIM1_EN) || \
                              ((SEL) == OPAMP_TIM1_DIS))



/** @defgroup  OPAHSM
  * @{
  */
#define OPAHSM_ENABLE             ((uint32_t)0x00000080)
#define OPAHSM_DISABLE            ((uint32_t)0x00000000)
#define IS_OPAX_OPAHSM(OPAHSM)    (((OPAHSM) == OPAHSM_ENABLE ) || \
                                   ((OPAHSM) == OPAHSM_DISABLE))

/** @defgroup  OPINTOEN
  * @{
  */
#define OPINTOEN_ENABLE            ((uint32_t)0x00000100)//to ADC 
#define OPINTOEN_DISABLE           ((uint32_t)0x00000000)//to output pad and need O2PADSEL to select
#define IS_OPAX_OPINTOEN(OPINTOEN) (((OPINTOEN) == OPAHSM_ENABLE ) || \
                                    ((OPINTOEN) == OPAHSM_DISABLE))

/** @defgroup  O2PADSEL
  * @{
  */
#define O2PADSEL_SEL_PAD1           ((uint32_t)0x00000200)//select pad1 
#define O2PADSEL_SEL_PAD2           ((uint32_t)0x00000000)//select pad2
#define IS_OPAX_O2PADSEL(O2PADSEL) (((O2PADSEL) == O2PADSEL_SEL_PAD1 ) || \
                                    ((O2PADSEL) == O2PADSEL_SEL_PAD2))

/** @defgroup  OPA_PGAGAIN
  * @{
  */
#define OPA_PGAGAIN_GAIN_P2                     ((uint32_t)0x00000000)
#define OPA_PGAGAIN_GAIN_P4                     ((uint32_t)0x00004000)
#define OPA_PGAGAIN_GAIN_P8                     ((uint32_t)0x00008000)
#define OPA_PGAGAIN_GAIN_P16                    ((uint32_t)0x0000C000)
#define OPA_PGAGAIN_GAIN_P32                    ((uint32_t)0x00010000)
#define OPA_PGAGAIN_GAIN_P64                    ((uint32_t)0x00014000)

#define OPA_PGAGAIN_GAIN_M2_VINM0               ((uint32_t)0x00020000)
#define OPA_PGAGAIN_GAIN_M4_VINM0               ((uint32_t)0x00024000)
#define OPA_PGAGAIN_GAIN_M8_VINM0               ((uint32_t)0x00028000)
#define OPA_PGAGAIN_GAIN_M16_VINM0              ((uint32_t)0x0002c000)
#define OPA_PGAGAIN_GAIN_M32_VINM0              ((uint32_t)0x00030000)
#define OPA_PGAGAIN_GAIN_M64_VINM0              ((uint32_t)0x00034000)

#define OPA_PGAGAIN_GAIN_FILTER_P2              ((uint32_t)0x00040000)
#define OPA_PGAGAIN_GAIN_FILTER_P4              ((uint32_t)0x00044000)
#define OPA_PGAGAIN_GAIN_FILTER_P8              ((uint32_t)0x00048000)
#define OPA_PGAGAIN_GAIN_FILTER_P16             ((uint32_t)0x0004c000)
#define OPA_PGAGAIN_GAIN_FILTER_P32             ((uint32_t)0x00050000)
#define OPA_PGAGAIN_GAIN_FILTER_P64             ((uint32_t)0x00054000)

#define OPA_PGAGAIN_GAIN_M2_VINM0_VINM1FIL      ((uint32_t)0x00060000)
#define OPA_PGAGAIN_GAIN_M4_VINM0_VINM1FIL      ((uint32_t)0x00064000)
#define OPA_PGAGAIN_GAIN_M8_VINM0_VINM1FIL      ((uint32_t)0x00068000)
#define OPA_PGAGAIN_GAIN_M16_VINM0_VINM1FIL     ((uint32_t)0x0006c000)
#define OPA_PGAGAIN_GAIN_M32_VINM0_VINM1FIL     ((uint32_t)0x00070000)
#define OPA_PGAGAIN_GAIN_M64_VINM0_VINM1FIL     ((uint32_t)0x00074000)

#define IS_OPA_PGAGAIN(INPUT)       (((INPUT)==OPA_PGAGAIN_GAIN_P2              ) || \
                                      ((INPUT)==OPA_PGAGAIN_GAIN_P4             ) || \
                                      ((INPUT)==OPA_PGAGAIN_GAIN_P8             ) || \
                                      ((INPUT)==OPA_PGAGAIN_GAIN_P16            ) || \
                                      ((INPUT)==OPA_PGAGAIN_GAIN_P32            ) || \
                                      ((INPUT)==OPA_PGAGAIN_GAIN_P64            ) || \
                                      ((INPUT)==OPA_PGAGAIN_GAIN_M2_VINM0           ) || \
                                      ((INPUT)==OPA_PGAGAIN_GAIN_M4_VINM0           ) || \
                                      ((INPUT)==OPA_PGAGAIN_GAIN_M8_VINM0           ) || \
                                      ((INPUT)==OPA_PGAGAIN_GAIN_M16_VINM0          ) || \
                                      ((INPUT)==OPA_PGAGAIN_GAIN_M32_VINM0          ) || \
                                      ((INPUT)==OPA_PGAGAIN_GAIN_M64_VINM0          ) || \
                                      ((INPUT)==OPA_PGAGAIN_GAIN_FILTER_P2              ) || \
                                      ((INPUT)==OPA_PGAGAIN_GAIN_FILTER_P4              ) || \
                                      ((INPUT)==OPA_PGAGAIN_GAIN_FILTER_P8              ) || \
                                      ((INPUT)==OPA_PGAGAIN_GAIN_FILTER_P16             ) || \
                                      ((INPUT)==OPA_PGAGAIN_GAIN_FILTER_P32             ) || \
                                      ((INPUT)==OPA_PGAGAIN_GAIN_FILTER_P64             ) || \
                                      ((INPUT)==OPA_PGAGAIN_GAIN_M2_VINM0_VINM1FIL ) || \
                                      ((INPUT)==OPA_PGAGAIN_GAIN_M4_VINM0_VINM1FIL ) || \
                                      ((INPUT)==OPA_PGAGAIN_GAIN_M8_VINM0_VINM1FIL ) || \
                                      ((INPUT)==OPA_PGAGAIN_GAIN_M16_VINM0_VINM1FIL) || \
                                      ((INPUT)==OPA_PGAGAIN_GAIN_M32_VINM0_VINM1FIL) || \
                                      ((INPUT)==OPA_PGAGAIN_GAIN_M64_VINM0_VINM1FIL))



/** @defgroup OPAMP_CALSEL_SEL
  * @{
  */
#define  OPAMP_VDDA003_CAL            ((uint32_t)0x00000000) /*!<  Selection:0.03VDDA */
#define  OPAMP_PMOS_CAL               ((uint32_t)0x00001000) /*!< PMOS Selection:0.1VDDA */
#define  OPAMP_VDDA05_CAL             ((uint32_t)0x00002000) /*!<  Selection:0.5VDDA */
#define  OPAMP_NMOS_CAL               ((uint32_t)0x00003000) /*!< NMOS Selection:0.9VDDA */

#define IS_OPAX_NPMOS(VOL) (((VOL) ==OPAMP_VDDA003_CAL ) || \
                               ((VOL) ==OPAMP_PMOS_CAL ) || \
                               ((VOL) ==OPAMP_VDDA05_CAL) || \
                               ((VOL) ==OPAMP_NMOS_CAL ))


/* Initialization and Configuration functions *********************************/
void OPA_Init(OPA_InitTypeDef* OPA_InitStruct, uint32_t OPAMP_Selection);
void OPA_DeInit(uint32_t OPAMP_Selection);
void OPA_Cmd(uint32_t OPAMP_Selection, FunctionalState NewState);
/*  Function used to set the COMP configuration to the default reset state ****/
void OPAMP_Calibration(uint32_t OPAMP_Selection);


#ifdef __cplusplus
}
#endif

#endif /* __FT32F0XX_OPAMP_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
