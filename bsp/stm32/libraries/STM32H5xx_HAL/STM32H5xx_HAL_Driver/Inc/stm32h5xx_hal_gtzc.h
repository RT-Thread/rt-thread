/**
  ******************************************************************************
  * @file    stm32h5xx_hal_gtzc.h
  * @author  MCD Application Team
  * @brief   Header file of GTZC HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H5xx_HAL_GTZC_H
#define STM32H5xx_HAL_GTZC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h5xx_hal_def.h"

/** @addtogroup STM32H5xx_HAL_Driver
  * @{
  */

/** @addtogroup GTZC
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup GTZC_Exported_Types GTZC Exported Types
  * @{
  */

/*!< Values needed for MPCBB_Attribute_ConfigTypeDef structure sizing */
#define GTZC_MPCBB_NB_VCTR_REG_MAX      (32U)
#define GTZC_MPCBB_NB_LCK_VCTR_REG_MAX  (1U)
typedef struct
{
  uint32_t MPCBB_SecConfig_array[GTZC_MPCBB_NB_VCTR_REG_MAX];  /*!< Each element specifies secure access mode for
                                                                    a super-block. Each bit corresponds to a block
                                                                    inside the super-block. 0 means non-secure,
                                                                    1 means secure */
  uint32_t MPCBB_PrivConfig_array[GTZC_MPCBB_NB_VCTR_REG_MAX]; /*!< Each element specifies privilege access mode for
                                                                    a super-block. Each bit corresponds to a block
                                                                    inside the super-block. 0 means non-privilege,
                                                                    1 means privilege */
  uint32_t MPCBB_LockConfig_array[GTZC_MPCBB_NB_LCK_VCTR_REG_MAX]; /*!< Each bit specifies the lock configuration of
                                                                        a super-block (32 blocks). 0 means unlocked,
                                                                        1 means locked */
} MPCBB_Attribute_ConfigTypeDef;

typedef struct
{
  uint32_t SecureRWIllegalMode; /*!< Secure read/write illegal access
                                     field. It can be a value of @ref GTZC_MPCBB_SecureRWIllegalMode */
  uint32_t InvertSecureState;   /*!< Default security state field (can be inverted or not).
                                     It can be a value of @ref GTZC_MPCBB_InvertSecureState */
  MPCBB_Attribute_ConfigTypeDef AttributeConfig; /*!< MPCBB attribute configuration sub-structure */
} MPCBB_ConfigTypeDef;

typedef struct
{
  uint32_t AreaId;     /*!< Area identifier field. It can be a value of @ref
                            GTZC_MPCWM_AreaId */
  uint32_t Offset;     /*!< Offset of the watermark area, starting from the selected
                            memory base address. It must aligned on 128KB for FMC
                            and OCTOSPI memories, and on 32-byte for BKPSRAM */
  uint32_t Length;     /*!< Length of the watermark area, starting from the selected
                            Offset. It must aligned on 128KB for FMC and OCTOSPI
                            memories, and on 32-byte for BKPSRAM */
  uint32_t Attribute;  /*!< Attributes of the watermark area. It can be a value
                            of @ref GTZC_MPCWM_Attribute */
  uint32_t Lock;       /*!< Lock of the watermark area. It can be a value
                            of @ref GTZC_MPCWM_Lock */
  uint32_t AreaStatus; /*!< Status of the watermark area. It can be set to
                            ENABLE or DISABLE */
} MPCWM_ConfigTypeDef;

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/

/** @defgroup GTZC_Private_Constants GTZC Private Constants
  * @{
  */

/** @defgroup GTZC_Private_PeriphId_composition GTZC Peripheral identifier composition
  * @{
  */

/* composition definition for Peripheral identifier parameter (PeriphId) used in
 * HAL_GTZC_TZSC_ConfigPeriphAttributes() and HAL_GTZC_TZSC_GetConfigPeriphAttributes()
 * functions and also in all HAL_GTZC_TZIC relative functions.
 * Bitmap Definition
 *   bits[31:28] Field "register". Define the register index a peripheral belongs to.
 *               Each bit is dedicated to a single register.
 *   bit[5]      Field "all peripherals". If this bit is set then the PeriphId targets
 *               all peripherals within all registers.
 *   bits[4:0]   Field "bit position". Define the bit position within the
 *               register dedicated to the peripheral, value from 0 to 31.
 */
#define GTZC_PERIPH_REG_SHIFT     (28U)
#define GTZC_PERIPH_REG           (0xF0000000U)
#define GTZC1_PERIPH_REG1         (0x00000000U)
#define GTZC1_PERIPH_REG2         (0x10000000U)
#define GTZC1_PERIPH_REG3         (0x20000000U)
#if defined (GTZC_TZIC1)
#define GTZC1_PERIPH_REG4         (0x30000000U)
#endif /* defined (GTZC_TZIC1) */
#define GTZC_PERIPH_BIT_POSITION  (0x0000001FU)

/**
  * @}
  */

/** @defgroup GTZC_Private_Attributes_Msk GTZC Attributes Masks
  * @{
  */
#define GTZC_ATTR_SEC_MASK         0x100U
#define GTZC_ATTR_PRIV_MASK        0x200U

/**
  * @}
  */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup GTZC_Exported_Constants GTZC Exported Constants
  * @{
  */

/** @defgroup GTZC_MPCBB_SecureRWIllegalMode GTZC MPCBB SRWILADIS values
  * @{
  */

#define GTZC_MPCBB_SRWILADIS_ENABLE  (0U)
#define GTZC_MPCBB_SRWILADIS_DISABLE (GTZC_MPCBB_CR_SRWILADIS_Msk)

/**
  * @}
  */

/** @defgroup GTZC_MPCBB_InvertSecureState GTZC MPCBB INVSECSTATE values
  * @{
  */

#define GTZC_MPCBB_INVSECSTATE_NOT_INVERTED  (0U)
#define GTZC_MPCBB_INVSECSTATE_INVERTED      (GTZC_MPCBB_CR_INVSECSTATE_Msk)

/**
  * @}
  */

/** @defgroup GTZC_MPCWM_AreaId GTZC MPCWM area identifier values
  * @{
  */

#define GTZC_TZSC_MPCWM_ID1  (0U)
#define GTZC_TZSC_MPCWM_ID2  (1U)

/**
  * @}
  */

/** @defgroup GTZC_TZSC_TZIC_PeriphId GTZC TZSC and TZIC Peripheral identifier values
  * @{
  */
#define GTZC_PERIPH_TIM2          (GTZC1_PERIPH_REG1 | GTZC_CFGR1_TIM2_Pos)
#define GTZC_PERIPH_TIM3          (GTZC1_PERIPH_REG1 | GTZC_CFGR1_TIM3_Pos)
#if defined (TIM4)
#define GTZC_PERIPH_TIM4          (GTZC1_PERIPH_REG1 | GTZC_CFGR1_TIM4_Pos)
#endif /* defined (TIM4) */
#if defined (TIM5)
#define GTZC_PERIPH_TIM5          (GTZC1_PERIPH_REG1 | GTZC_CFGR1_TIM5_Pos)
#endif /* defined (TIM5) */
#define GTZC_PERIPH_TIM6          (GTZC1_PERIPH_REG1 | GTZC_CFGR1_TIM6_Pos)
#define GTZC_PERIPH_TIM7          (GTZC1_PERIPH_REG1 | GTZC_CFGR1_TIM7_Pos)
#if defined (TIM12)
#define GTZC_PERIPH_TIM12         (GTZC1_PERIPH_REG1 | GTZC_CFGR1_TIM12_Pos)
#endif /* defined (TIM12) */
#if defined (TIM13)
#define GTZC_PERIPH_TIM13         (GTZC1_PERIPH_REG1 | GTZC_CFGR1_TIM13_Pos)
#endif /* defined (TIM13) */
#if defined (TIM14)
#define GTZC_PERIPH_TIM14         (GTZC1_PERIPH_REG1 | GTZC_CFGR1_TIM14_Pos)
#endif /* defined (TIM14) */
#define GTZC_PERIPH_WWDG          (GTZC1_PERIPH_REG1 | GTZC_CFGR1_WWDG_Pos)
#define GTZC_PERIPH_IWDG          (GTZC1_PERIPH_REG1 | GTZC_CFGR1_IWDG_Pos)
#define GTZC_PERIPH_SPI2          (GTZC1_PERIPH_REG1 | GTZC_CFGR1_SPI2_Pos)
#define GTZC_PERIPH_SPI3          (GTZC1_PERIPH_REG1 | GTZC_CFGR1_SPI3_Pos)
#define GTZC_PERIPH_USART2        (GTZC1_PERIPH_REG1 | GTZC_CFGR1_USART2_Pos)
#define GTZC_PERIPH_USART3        (GTZC1_PERIPH_REG1 | GTZC_CFGR1_USART3_Pos)
#if defined (UART4)
#define GTZC_PERIPH_UART4         (GTZC1_PERIPH_REG1 | GTZC_CFGR1_UART4_Pos)
#endif /* defined (UART4) */
#if defined (UART5)
#define GTZC_PERIPH_UART5         (GTZC1_PERIPH_REG1 | GTZC_CFGR1_UART5_Pos)
#endif /* defined (UART5) */
#define GTZC_PERIPH_I2C1          (GTZC1_PERIPH_REG1 | GTZC_CFGR1_I2C1_Pos)
#define GTZC_PERIPH_I2C2          (GTZC1_PERIPH_REG1 | GTZC_CFGR1_I2C2_Pos)
#define GTZC_PERIPH_I3C1          (GTZC1_PERIPH_REG1 | GTZC_CFGR1_I3C1_Pos)
#define GTZC_PERIPH_CRS           (GTZC1_PERIPH_REG1 | GTZC_CFGR1_CRS_Pos)
#if defined (USART6)
#define GTZC_PERIPH_USART6        (GTZC1_PERIPH_REG1 | GTZC_CFGR1_USART6_Pos)
#endif /* defined (USART6) */
#if defined (USART10)
#define GTZC_PERIPH_USART10       (GTZC1_PERIPH_REG1 | GTZC_CFGR1_USART10_Pos)
#endif /* defined (USART10) */
#if defined (USART11)
#define GTZC_PERIPH_USART11       (GTZC1_PERIPH_REG1 | GTZC_CFGR1_USART11_Pos)
#endif /* defined (USART11) */
#if defined (CEC)
#define GTZC_PERIPH_HDMICEC       (GTZC1_PERIPH_REG1 | GTZC_CFGR1_HDMICEC_Pos)
#endif /* defined (CEC) */
#define GTZC_PERIPH_DAC1          (GTZC1_PERIPH_REG1 | GTZC_CFGR1_DAC1_Pos)
#if defined (UART7)
#define GTZC_PERIPH_UART7         (GTZC1_PERIPH_REG1 | GTZC_CFGR1_UART7_Pos)
#endif /* defined (UART7) */
#if defined (UART8)
#define GTZC_PERIPH_UART8         (GTZC1_PERIPH_REG1 | GTZC_CFGR1_UART8_Pos)
#endif /* defined (UART8) */
#if defined (UART9)
#define GTZC_PERIPH_UART9         (GTZC1_PERIPH_REG1 | GTZC_CFGR1_UART9_Pos)
#endif /* defined (UART9) */
#if defined (UART12)
#define GTZC_PERIPH_UART12        (GTZC1_PERIPH_REG1 | GTZC_CFGR1_UART12_Pos)
#endif /* defined (UART12) */
#define GTZC_PERIPH_DTS           (GTZC1_PERIPH_REG1 | GTZC_CFGR1_DTS_Pos)
#define GTZC_PERIPH_LPTIM2        (GTZC1_PERIPH_REG1 | GTZC_CFGR1_LPTIM2_Pos)

#define GTZC_PERIPH_FDCAN1        (GTZC1_PERIPH_REG2 | GTZC_CFGR2_FDCAN1_Pos)
#if defined (FDCAN2)
#define GTZC_PERIPH_FDCAN2        (GTZC1_PERIPH_REG2 | GTZC_CFGR2_FDCAN2_Pos)
#endif /* defined (FDCAN2) */
#if defined (UCPD1)
#define GTZC_PERIPH_UCPD1         (GTZC1_PERIPH_REG2 | GTZC_CFGR2_UCPD1_Pos)
#endif /* defined (UCPD1) */
#if defined (OPAMP1)
#define GTZC_PERIPH_OPAMP         (GTZC1_PERIPH_REG2 | GTZC_CFGR2_OPAMP_Pos)
#endif /* defined (OPAMP1) */
#if defined (COMP1)
#define GTZC_PERIPH_COMP          (GTZC1_PERIPH_REG2 | GTZC_CFGR2_COMP_Pos)
#endif /* defined (COMP1) */
#define GTZC_PERIPH_TIM1          (GTZC1_PERIPH_REG2 | GTZC_CFGR2_TIM1_Pos)
#define GTZC_PERIPH_SPI1          (GTZC1_PERIPH_REG2 | GTZC_CFGR2_SPI1_Pos)
#if defined (TIM8)
#define GTZC_PERIPH_TIM8          (GTZC1_PERIPH_REG2 | GTZC_CFGR2_TIM8_Pos)
#endif /* defined (TIM8) */
#define GTZC_PERIPH_USART1        (GTZC1_PERIPH_REG2 | GTZC_CFGR2_USART1_Pos)
#if defined (TIM15)
#define GTZC_PERIPH_TIM15         (GTZC1_PERIPH_REG2 | GTZC_CFGR2_TIM15_Pos)
#endif /* defined (TIM15) */
#if defined (TIM16)
#define GTZC_PERIPH_TIM16         (GTZC1_PERIPH_REG2 | GTZC_CFGR2_TIM16_Pos)
#endif /* defined (TIM16) */
#if defined (TIM17)
#define GTZC_PERIPH_TIM17         (GTZC1_PERIPH_REG2 | GTZC_CFGR2_TIM17_Pos)
#endif /* defined (TIM17) */
#if defined (SPI4)
#define GTZC_PERIPH_SPI4          (GTZC1_PERIPH_REG2 | GTZC_CFGR2_SPI4_Pos)
#endif /* defined (SPI4) */
#if defined (SPI6)
#define GTZC_PERIPH_SPI6          (GTZC1_PERIPH_REG2 | GTZC_CFGR2_SPI6_Pos)
#endif /* defined (SPI6) */
#if defined (SAI1)
#define GTZC_PERIPH_SAI1          (GTZC1_PERIPH_REG2 | GTZC_CFGR2_SAI1_Pos)
#endif /* defined (SAI1) */
#if defined (SAI2)
#define GTZC_PERIPH_SAI2          (GTZC1_PERIPH_REG2 | GTZC_CFGR2_SAI2_Pos)
#endif /* defined (SAI2) */
#define GTZC_PERIPH_USB           (GTZC1_PERIPH_REG2 | GTZC_CFGR2_USB_Pos)
#if defined (SPI5)
#define GTZC_PERIPH_SPI5          (GTZC1_PERIPH_REG2 | GTZC_CFGR2_SPI5_Pos)
#endif /* defined (SPI5) */
#define GTZC_PERIPH_LPUART1       (GTZC1_PERIPH_REG2 | GTZC_CFGR2_LPUART1_Pos)
#if defined (I2C3)
#define GTZC_PERIPH_I2C3          (GTZC1_PERIPH_REG2 | GTZC_CFGR2_I2C3_Pos)
#endif /* defined (I2C3) */
#if defined (I2C4)
#define GTZC_PERIPH_I2C4          (GTZC1_PERIPH_REG2 | GTZC_CFGR2_I2C4_Pos)
#endif /* defined (I2C4) */
#define GTZC_PERIPH_LPTIM1        (GTZC1_PERIPH_REG2 | GTZC_CFGR2_LPTIM1_Pos)
#if defined (LPTIM3)
#define GTZC_PERIPH_LPTIM3        (GTZC1_PERIPH_REG2 | GTZC_CFGR2_LPTIM3_Pos)
#endif /* defined (LPTIM3) */
#if defined (LPTIM4)
#define GTZC_PERIPH_LPTIM4        (GTZC1_PERIPH_REG2 | GTZC_CFGR2_LPTIM4_Pos)
#endif /* defined (LPTIM4) */
#if defined (LPTIM5)
#define GTZC_PERIPH_LPTIM5        (GTZC1_PERIPH_REG2 | GTZC_CFGR2_LPTIM5_Pos)
#endif /* defined (LPTIM5) */

#if defined (LPTIM6)
#define GTZC_PERIPH_LPTIM6        (GTZC1_PERIPH_REG3 | GTZC_CFGR3_LPTIM6_Pos)
#endif /* defined (LPTIM6) */
#if defined (VREFBUF)
#define GTZC_PERIPH_VREFBUF       (GTZC1_PERIPH_REG3 | GTZC_CFGR3_VREFBUF_Pos)
#endif /* defined (VREFBUF) */
#if defined (I3C2)
#define GTZC_PERIPH_I3C2          (GTZC1_PERIPH_REG3 | GTZC_CFGR3_I3C2_Pos)
#endif /* defined (I3C2) */
#define GTZC_PERIPH_CRC           (GTZC1_PERIPH_REG3 | GTZC_CFGR3_CRC_Pos)
#if defined (CORDIC)
#define GTZC_PERIPH_CORDIC        (GTZC1_PERIPH_REG3 | GTZC_CFGR3_CORDIC_Pos)
#endif /* defined (CORDIC) */
#if defined (FMAC)
#define GTZC_PERIPH_FMAC          (GTZC1_PERIPH_REG3 | GTZC_CFGR3_FMAC_Pos)
#endif /* defined (FMAC) */
#if defined (ETH)
#define GTZC_PERIPH_ETHERNET      (GTZC1_PERIPH_REG3 | GTZC_CFGR3_ETHERNET_Pos)
#endif /* defined (ETH) */
#define GTZC_PERIPH_ICACHE_REG    (GTZC1_PERIPH_REG3 | GTZC_CFGR3_ICACHE_REG_Pos)
#if defined (DCACHE1)
#define GTZC_PERIPH_DCACHE1_REG   (GTZC1_PERIPH_REG3 | GTZC_CFGR3_DCACHE1_REG_Pos)
#endif /* defined (DCACHE1) */
#define GTZC_PERIPH_ADC           (GTZC1_PERIPH_REG3 | GTZC_CFGR3_ADC_Pos)
#if defined (DCMI)
#define GTZC_PERIPH_DCMI_PSSI     (GTZC1_PERIPH_REG3 | GTZC_CFGR3_DCMI_PSSI_Pos)
#endif /* defined (DCMI) */
#if defined (AES)
#define GTZC_PERIPH_AES           (GTZC1_PERIPH_REG3 | GTZC_CFGR3_AES_Pos)
#endif /* defined (AES) */
#if defined (HASH)
#define GTZC_PERIPH_HASH          (GTZC1_PERIPH_REG3 | GTZC_CFGR3_HASH_Pos)
#endif /* defined (HASH) */
#define GTZC_PERIPH_RNG           (GTZC1_PERIPH_REG3 | GTZC_CFGR3_RNG_Pos)
#if defined (PKA)
#define GTZC_PERIPH_PKA           (GTZC1_PERIPH_REG3 | GTZC_CFGR3_PKA_Pos)
#endif /* defined (PKA) */
#if defined (SAES)
#define GTZC_PERIPH_SAES          (GTZC1_PERIPH_REG3 | GTZC_CFGR3_SAES_Pos)
#endif /* defined (SAES) */
#if defined (SDMMC1)
#define GTZC_PERIPH_SDMMC1        (GTZC1_PERIPH_REG3 | GTZC_CFGR3_SDMMC1_Pos)
#endif /* defined (SDMMC1) */
#if defined (SDMMC2)
#define GTZC_PERIPH_SDMMC2        (GTZC1_PERIPH_REG3 | GTZC_CFGR3_SDMMC2_Pos)
#endif /* defined (SDMMC2) */
#if defined (FMC_Bank1_R)
#define GTZC_PERIPH_FMC_REG       (GTZC1_PERIPH_REG3 | GTZC_CFGR3_FMC_REG_Pos)
#endif /* defined (FMC_Bank1_R) */
#if defined (OCTOSPI1)
#define GTZC_PERIPH_OCTOSPI1      (GTZC1_PERIPH_REG3 | GTZC_CFGR3_OCTOSPI1_Pos)
#endif /* defined (OCTOSPI1) */
#define GTZC_PERIPH_RAMCFG        (GTZC1_PERIPH_REG3 | GTZC_CFGR3_RAMCFG_Pos)

#if defined (GTZC_TZIC1)
#define GTZC_PERIPH_GPDMA1        (GTZC1_PERIPH_REG4 | GTZC_CFGR4_GPDMA1_Pos)
#define GTZC_PERIPH_GPDMA2        (GTZC1_PERIPH_REG4 | GTZC_CFGR4_GPDMA2_Pos)
#define GTZC_PERIPH_FLASH         (GTZC1_PERIPH_REG4 | GTZC_CFGR4_FLASH_Pos)
#define GTZC_PERIPH_FLASH_REG     (GTZC1_PERIPH_REG4 | GTZC_CFGR4_FLASH_REG_Pos)
#define GTZC_PERIPH_OTFDEC2       (GTZC1_PERIPH_REG4 | GTZC_CFGR4_OTFDEC2_Pos)
#define GTZC_PERIPH_OTFDEC1       (GTZC1_PERIPH_REG4 | GTZC_CFGR4_OTFDEC1_Pos)
#define GTZC_PERIPH_SBS           (GTZC1_PERIPH_REG4 | GTZC_CFGR4_SBS_Pos)
#define GTZC_PERIPH_RTC           (GTZC1_PERIPH_REG4 | GTZC_CFGR4_RTC_Pos)
#define GTZC_PERIPH_TAMP          (GTZC1_PERIPH_REG4 | GTZC_CFGR4_TAMP_Pos)
#define GTZC_PERIPH_PWR           (GTZC1_PERIPH_REG4 | GTZC_CFGR4_PWR_Pos)
#define GTZC_PERIPH_RCC           (GTZC1_PERIPH_REG4 | GTZC_CFGR4_RCC_Pos)
#define GTZC_PERIPH_EXTI          (GTZC1_PERIPH_REG4 | GTZC_CFGR4_EXTI_Pos)
#define GTZC_PERIPH_TZSC          (GTZC1_PERIPH_REG4 | GTZC_CFGR4_TZSC_Pos)
#define GTZC_PERIPH_TZIC          (GTZC1_PERIPH_REG4 | GTZC_CFGR4_TZIC_Pos)
#define GTZC_PERIPH_OCTOSPI1_MEM  (GTZC1_PERIPH_REG4 | GTZC_CFGR4_OCTOSPI1_MEM_Pos)
#define GTZC_PERIPH_FMC_MEM       (GTZC1_PERIPH_REG4 | GTZC_CFGR4_FMC_MEM_Pos)
#define GTZC_PERIPH_BKPSRAM       (GTZC1_PERIPH_REG4 | GTZC_CFGR4_BKPSRAM_Pos)
#define GTZC_PERIPH_SRAM1         (GTZC1_PERIPH_REG4 | GTZC_CFGR4_SRAM1_Pos)
#define GTZC_PERIPH_MPCBB1_REG    (GTZC1_PERIPH_REG4 | GTZC_CFGR4_MPCBB1_REG_Pos)
#define GTZC_PERIPH_SRAM2         (GTZC1_PERIPH_REG4 | GTZC_CFGR4_SRAM2_Pos)
#define GTZC_PERIPH_MPCBB2_REG    (GTZC1_PERIPH_REG4 | GTZC_CFGR4_MPCBB2_REG_Pos)
#define GTZC_PERIPH_SRAM3         (GTZC1_PERIPH_REG4 | GTZC_CFGR4_SRAM3_Pos)
#define GTZC_PERIPH_MPCBB3_REG    (GTZC1_PERIPH_REG4 | GTZC_CFGR4_MPCBB3_REG_Pos)
#endif /* defined (GTZC_TZIC1) */

#define GTZC_PERIPH_ALL           (0x00000020U)

/* Note that two maximum values are also defined here:
 * - max number of securable AHB/APB peripherals or masters
 *   (used in TZSC sub-block)
 * - max number of securable and TrustZone-aware AHB/APB peripherals or masters
 *   (used in TZIC sub-block)
 */
#define GTZC_TZSC_PERIPH_NUMBER   (HAL_GTZC_GET_ARRAY_INDEX(GTZC_PERIPH_RAMCFG + 1U))
#if defined (GTZC_TZIC1)
#define GTZC_TZIC_PERIPH_NUMBER   (HAL_GTZC_GET_ARRAY_INDEX(GTZC_PERIPH_MPCBB3_REG + 1U))
#endif /* defined (GTZC_TZIC1) */

/**
  * @}
  */

/** @defgroup GTZC_TZSC_PeriphAttributes GTZC TZSC peripheral attribute values
  * @note secure and non-secure attributes are only available from secure state when the system
  *       implement the security (TZEN=1)
  * @{
  */

/* user-oriented definitions for attribute parameter (PeriphAttributes) used in
 * HAL_GTZC_TZSC_ConfigPeriphAttributes() and HAL_GTZC_TZSC_GetConfigPeriphAttributes()
 * functions
 */
#if defined (GTZC_TZIC1)
#define GTZC_TZSC_PERIPH_SEC    (GTZC_ATTR_SEC_MASK | 0x00000001U)  /*!< Secure attribute        */
#define GTZC_TZSC_PERIPH_NSEC   (GTZC_ATTR_SEC_MASK | 0x00000000U)  /*!< Non-secure attribute    */
#endif /* (GTZC_TZIC1) */
#define GTZC_TZSC_PERIPH_PRIV   (GTZC_ATTR_PRIV_MASK | 0x00000002U) /*!< Privilege attribute     */
#define GTZC_TZSC_PERIPH_NPRIV  (GTZC_ATTR_PRIV_MASK | 0x00000000U) /*!< Non-privilege attribute */

/**
  * @}
  */

#if defined (GTZC_TZSC_CR_LCK_Msk)
/** @defgroup GTZC_TZSC_Lock GTZC TZSC lock values
  * @{
  */

/* user-oriented definitions for HAL_GTZC_TZSC_GetLock() returned value */
#define GTZC_TZSC_LOCK_OFF  (0U)
#define GTZC_TZSC_LOCK_ON   GTZC_TZSC_CR_LCK_Msk

/**
  * @}
  */
#endif /* (GTZC_TZSC_CR_LCK_Msk) */

/** @defgroup GTZC_MPCWM_Group GTZC MPCWM values
  * @{
  */

/* user-oriented definitions for TZSC_MPCWM */
#define GTZC_TZSC_MPCWM_GRANULARITY_1    0x00020000U /* OCTOSPI & FMC granularity: 128 kbytes */
#define GTZC_TZSC_MPCWM_GRANULARITY_2    0x00000020U /* BKPSRAM granularity: 32 bytes         */

/**
  * @}
  */

/** @defgroup GTZC_MPCWM_Lock GTZC MPCWM Lock values
  * @{
  */

/* user-oriented definitions for TZSC_MPCWM */
#define GTZC_TZSC_MPCWM_LOCK_OFF  (0U)
#define GTZC_TZSC_MPCWM_LOCK_ON   GTZC_TZSC_MPCWM_CFGR_SRLOCK_Msk

/**
  * @}
  */

/** @defgroup GTZC_MPCWM_Attribute GTZC MPCWM Attribute values
  * @{
  */

/* user-oriented definitions for TZSC_MPCWM */
#define GTZC_TZSC_MPCWM_REGION_NSEC  (0U)
#define GTZC_TZSC_MPCWM_REGION_SEC   (1U)
#define GTZC_TZSC_MPCWM_REGION_NPRIV (0U)
#define GTZC_TZSC_MPCWM_REGION_PRIV  (2U)

/**
  * @}
  */

/** @defgroup GTZC_MPCBB_Group GTZC MPCBB values
  * @{
  */

/* user-oriented definitions for MPCBB */
#define GTZC_MPCBB_BLOCK_SIZE           0x200U                        /* 512 Bytes */
#define GTZC_MPCBB_SUPERBLOCK_SIZE      (GTZC_MPCBB_BLOCK_SIZE * 32U) /* 16 KBytes */
#define GTZC_MPCBB_SUPERBLOCK_UNLOCKED  (0U)
#define GTZC_MPCBB_SUPERBLOCK_LOCKED    (1U)

#define GTZC_MPCBB_BLOCK_NSEC           (GTZC_ATTR_SEC_MASK  | 0U)
#define GTZC_MPCBB_BLOCK_SEC            (GTZC_ATTR_SEC_MASK  | 1U)
#define GTZC_MPCBB_BLOCK_NPRIV          (GTZC_ATTR_PRIV_MASK | 0U)
#define GTZC_MPCBB_BLOCK_PRIV           (GTZC_ATTR_PRIV_MASK | 2U)

/* user-oriented definitions for HAL_GTZC_MPCBB_GetLock() returned value */
#define GTZC_MPCBB_LOCK_OFF  (0U)
#define GTZC_MPCBB_LOCK_ON   (1U)

/**
  * @}
  */

/** @defgroup GTZC_TZIC_Flag GTZC TZIC flag values
  * @{
  */

/* user-oriented definitions for HAL_GTZC_TZIC_GetFlag() flag parameter */
#define GTZC_TZIC_NO_ILA_EVENT       (0U)
#define GTZC_TZIC_ILA_EVENT_PENDING  (1U)

/**
  * @}
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/** @defgroup GTZC_Private_Macros GTZC Private Macros
  * @{
  */

/* retrieve information to access register for a specific PeriphId */
#define GTZC_GET_REG_INDEX(periph_id)\
  (((periph_id) & GTZC_PERIPH_REG) >> GTZC_PERIPH_REG_SHIFT)

#define GTZC_GET_PERIPH_POS(periph_id)     ((periph_id) & GTZC_PERIPH_BIT_POSITION)

#if defined (GTZC_TZIC1)
#define IS_GTZC_BASE_ADDRESS(mem, address)\
  ( ( (uint32_t)(address) == (uint32_t)GTZC_BASE_ADDRESS_NS(mem) ) || \
    ( (uint32_t)(address) == (uint32_t)GTZC_BASE_ADDRESS_S(mem) ) )
#else
#define IS_GTZC_BASE_ADDRESS(mem, address)\
  ( (uint32_t)(address) == (uint32_t)GTZC_BASE_ADDRESS_NS(mem) )
#endif /* defined (GTZC_TZIC1) */

#define GTZC_MEM_SIZE(mem)\
  ( mem ## _SIZE )

#if defined (GTZC_TZIC1)
#define GTZC_BASE_ADDRESS_S(mem)\
  ( mem ## _BASE_S )
#endif /* defined (GTZC_TZIC1) */

#define GTZC_BASE_ADDRESS_NS(mem)\
  ( mem ## _BASE_NS )

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/** @defgroup GTZC_Exported_Macros GTZC Exported Macros
  * @{
  */

/* user-oriented macro to get array index of a specific PeriphId
 * in case of GTZC_PERIPH_ALL usage in the two following functions:
 * HAL_GTZC_TZSC_ConfigPeriphAttributes() and HAL_GTZC_TZSC_GetConfigPeriphAttributes()
 */
#define HAL_GTZC_GET_ARRAY_INDEX(periph_id)\
  ( (GTZC_GET_REG_INDEX((periph_id)) * 32U) + GTZC_GET_PERIPH_POS((periph_id)) )

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @addtogroup GTZC_Exported_Functions
  * @{
  */

/** @addtogroup GTZC_Exported_Functions_Group1
  * @brief    TZSC Initialization and Configuration functions
  * @{
  */

HAL_StatusTypeDef HAL_GTZC_TZSC_ConfigPeriphAttributes(uint32_t PeriphId,
                                                       uint32_t PeriphAttributes);
HAL_StatusTypeDef HAL_GTZC_TZSC_GetConfigPeriphAttributes(uint32_t PeriphId,
                                                          uint32_t *PeriphAttributes);

/**
  * @}
  */

/** @addtogroup GTZC_Exported_Functions_Group2
  * @brief    MPCWM Initialization and Configuration functions
  * @{
  */

HAL_StatusTypeDef HAL_GTZC_TZSC_MPCWM_ConfigMemAttributes(uint32_t MemBaseAddress,
                                                          const MPCWM_ConfigTypeDef *pMPCWM_Desc);
HAL_StatusTypeDef HAL_GTZC_TZSC_MPCWM_GetConfigMemAttributes(uint32_t MemBaseAddress,
                                                             MPCWM_ConfigTypeDef *pMPCWM_Desc);
/**
  * @}
  */

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)

/** @addtogroup GTZC_Exported_Functions_Group3
  * @brief    TZSC and TZSC-MPCWM Lock functions
  * @{
  */

void     HAL_GTZC_TZSC_Lock(GTZC_TZSC_TypeDef *TZSC_Instance);
uint32_t HAL_GTZC_TZSC_GetLock(const GTZC_TZSC_TypeDef *TZSC_Instance);

/**
  * @}
  */
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
/** @addtogroup GTZC_Exported_Functions_Group4
  * @brief    MPCBB Initialization and Configuration functions
  * @{
  */

HAL_StatusTypeDef HAL_GTZC_MPCBB_ConfigMem(uint32_t MemBaseAddress,
                                           const MPCBB_ConfigTypeDef *pMPCBB_desc);
HAL_StatusTypeDef HAL_GTZC_MPCBB_GetConfigMem(uint32_t MemBaseAddress,
                                              MPCBB_ConfigTypeDef *pMPCBB_desc);
HAL_StatusTypeDef HAL_GTZC_MPCBB_ConfigMemAttributes(uint32_t MemAddress,
                                                     uint32_t NbBlocks,
                                                     const uint32_t *pMemAttributes);
HAL_StatusTypeDef HAL_GTZC_MPCBB_GetConfigMemAttributes(uint32_t MemAddress,
                                                        uint32_t NbBlocks,
                                                        uint32_t *pMemAttributes);

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
HAL_StatusTypeDef HAL_GTZC_MPCBB_LockConfig(uint32_t MemAddress,
                                            uint32_t NbSuperBlocks,
                                            const uint32_t *pLockAttributes);
HAL_StatusTypeDef HAL_GTZC_MPCBB_GetLockConfig(uint32_t MemAddress,
                                               uint32_t NbSuperBlocks,
                                               uint32_t *pLockAttributes);
HAL_StatusTypeDef HAL_GTZC_MPCBB_Lock(uint32_t MemBaseAddress);
HAL_StatusTypeDef HAL_GTZC_MPCBB_GetLock(uint32_t MemBaseAddress,
                                         uint32_t *pLockState);
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/**
  * @}
  */

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)

/** @addtogroup GTZC_Exported_Functions_Group5
  * @brief    TZIC functions
  * @{
  */

HAL_StatusTypeDef HAL_GTZC_TZIC_DisableIT(uint32_t PeriphId);
HAL_StatusTypeDef HAL_GTZC_TZIC_EnableIT(uint32_t PeriphId);
HAL_StatusTypeDef HAL_GTZC_TZIC_GetFlag(uint32_t PeriphId, uint32_t *pFlag);
HAL_StatusTypeDef HAL_GTZC_TZIC_ClearFlag(uint32_t PeriphId);

/**
  * @}
  */

/** @addtogroup GTZC_Exported_Functions_Group6
  * @brief    IRQ related Functions
  * @{
  */

void HAL_GTZC_IRQHandler(void);
void HAL_GTZC_TZIC_Callback(uint32_t PeriphId);

/**
  * @}
  */

#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H5xx_HAL_GTZC_H */

