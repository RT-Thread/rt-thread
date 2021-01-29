/**
  ******************************************************************************
  * @file    stm32wlxx_hal_gtzc.h
  * @author  MCD Application Team
  * @brief   Header file of GTZC HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32WLxx_HAL_GTZC_H
#define STM32WLxx_HAL_GTZC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wlxx_hal_def.h"

#if defined(GTZC_TZSC)

/** @addtogroup STM32WLxx_HAL_Driver
  * @{
  */

/** @addtogroup GTZC
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup GTZC_Exported_Types GTZC Exported Types
  * @{
  */
/**
  * @brief  GTZC TZSC MPCWM structure
  */
typedef struct
{
  uint32_t AreaId; /*!< Area identifier field. It can be a value of @ref 
                        GTZC_MPCWM_AreaId */
  uint32_t Length; /*!< length of the unprivileged area starting from selected
                        memory base address. It must be aligned on 2kB for Flash
                        areas and 1kB for Sram ones. */
} MPCWM_ConfigTypeDef;
/**
  * @}
  */


/* Private constants --------------------------------------------------------*/
/** @defgroup GTZC_Private_Constants GTZC Private Constants
  * @{
  */
/**
  * @brief  GTZC structure definitions for IP identifier parameter (PeriphId)
  *         used in HAL_GTZC_TZSC_ConfigPeriphAttributes and 
  *         HAL_GTZC_TZSC_GetConfigPeriphAttributes functions and also in all
  *        HAL_GTZC_TZIC related functions bitmap:
  *         bits[31:28] Field "register". Define the register an IP belongs to.
  *                     Each bit is dedicated to a single register.
  *         bit[5]      Field "all Ips". If this bit is set then the PeriphId
  *                     targets all Ips within register.
  *         bits[4:0]   Field "bit position". Define the bit position within
  *                     the register dedicated to the IP, value from 0 to 31.
  */
#define GTZC_PERIPH_REG_Pos                 (28U)
#define GTZC_PERIPH_REG_Msk                 (0xFUL << GTZC_PERIPH_REG_Pos)        /*0 xF0000000 */
#define GTZC_PERIPH_REG1                    (0x0UL << GTZC_PERIPH_REG_Pos)
#define GTZC_PERIPH_ALLPERIPH_Pos           (5U)
#define GTZC_PERIPH_ALLPERIPH_Msk           (0x1UL << GTZC_PERIPH_ALLPERIPH_Pos)  /* 0x00000020 */
#define GTZC_PERIPH_BITPOS_Pos              (0U)
#define GTZC_PERIPH_BITPOS_Msk              (0x1FUL << GTZC_PERIPH_BITPOS_Pos)    /* 0x0000001F */

/**
  * @brief GTZC TZSC MPCWM Watermark granularity depending on area
  */
#define GTZC_TZSC_MPCWM_GRANULARITY_FLASH_OFFSET  11U
#define GTZC_TZSC_MPCWM_GRANULARITY_FLASH         (1UL << GTZC_TZSC_MPCWM_GRANULARITY_FLASH_OFFSET)  /* 2 kB */
#define GTZC_TZSC_MPCWM_GRANULARITY_SRAM1_OFFSET  10U
#define GTZC_TZSC_MPCWM_GRANULARITY_SRAM1         (1UL << GTZC_TZSC_MPCWM_GRANULARITY_SRAM1_OFFSET)  /* 1 kB */
#define GTZC_TZSC_MPCWM_GRANULARITY_SRAM2_OFFSET  10U
#define GTZC_TZSC_MPCWM_GRANULARITY_SRAM2         (1UL << GTZC_TZSC_MPCWM_GRANULARITY_SRAM2_OFFSET)  /* 1 kB */

/**
  * @}
  */


/** @defgroup GTZC_Exported_Constants GTZC Exported Constants
  * @{
  */

/** @defgroup GTZC_TZSC_Peripheral_Attribute GTZC TZSC Peripheral Attribute
  *           bitmap: bit0 : Sec Attr (0 = Ns, 1 = Sec)
  *                   bit1 : PrivAttr (0 = NonPriv, 1 = Priv)
  * @{
  */
#define GTZC_TZSC_ATTRIBUTE_NSEC            0x00U
#define GTZC_TZSC_ATTRIBUTE_SEC             0x01U
#define GTZC_TZSC_ATTRIBUTE_NPRIV           0x00U
#define GTZC_TZSC_ATTRIBUTE_PRIV            0x02U
/**
  * @}
  */

/** @defgroup GTZC_Peripheral_Identification GTZC Peripheral Identification
  *           user-oriented definition for each IP identifier parameter (PeriphId)
  *           used in HAL_GTZC_TZSC_ConfigPeriphAttributes and HAL_GTZC_TZSC_GetConfigPeriphAttributes
  *           functions and also in all HAL_GTZC_TZIC relative functions.
  * @note     user can also select all IPs using specific define
  * @note     that two maximum values are also defined here:
  *           - max number of securable AHB/APB peripherals or masters (used in
  *           TZSC sub-block)
  *           - max number of securable and TrustZone-aware AHB/APB peripherals
  *           or masters (used in TZIC sub-block)
  * @{
  */
#define GTZC_PERIPH_TZIC                    (GTZC_PERIPH_REG1 | GTZC_CFGR1_TZIC_Pos)
#define GTZC_PERIPH_TZSC                    (GTZC_PERIPH_REG1 | GTZC_CFGR1_TZSC_Pos)
#define GTZC_PERIPH_AES                     (GTZC_PERIPH_REG1 | GTZC_CFGR1_AES_Pos)
#define GTZC_PERIPH_RNG                     (GTZC_PERIPH_REG1 | GTZC_CFGR1_RNG_Pos)
#define GTZC_PERIPH_SUBGHZSPI               (GTZC_PERIPH_REG1 | GTZC_CFGR1_SUBGHZSPI_Pos)
#define GTZC_PERIPH_PWR                     (GTZC_PERIPH_REG1 | GTZC_CFGR1_PWR_Pos)
#define GTZC_PERIPH_FLASHIF                 (GTZC_PERIPH_REG1 | GTZC_CFGR1_FLASHIF_Pos)
#define GTZC_PERIPH_DMA1                    (GTZC_PERIPH_REG1 | GTZC_CFGR1_DMA1_Pos)
#define GTZC_PERIPH_DMA2                    (GTZC_PERIPH_REG1 | GTZC_CFGR1_DMA2_Pos)
#define GTZC_PERIPH_DMAMUX                  (GTZC_PERIPH_REG1 | GTZC_CFGR1_DMAMUX_Pos)
#define GTZC_PERIPH_FLASH                   (GTZC_PERIPH_REG1 | GTZC_CFGR1_FLASH_Pos)
#define GTZC_PERIPH_SRAM1                   (GTZC_PERIPH_REG1 | GTZC_CFGR1_SRAM1_Pos)
#define GTZC_PERIPH_SRAM2                   (GTZC_PERIPH_REG1 | GTZC_CFGR1_SRAM2_Pos)
#define GTZC_PERIPH_PKA                     (GTZC_PERIPH_REG1 | GTZC_CFGR1_PKA_Pos)
#define GTZC_PERIPH_TZIC_MAX                GTZC_PERIPH_PKA
#define GTZC_PERIPH_ALL                     GTZC_PERIPH_ALLPERIPH_Msk


/* Note that two maximum values are also defined here:
 * - max number of securable peripherals
 *   (used in TZSC sub-block)
 * - max number of securable and TrustZone-aware peripherals or masters
 *   (used in TZIC sub-block)
 */
#define GTZC_TZSC_PERIPH_NUMBER             4U
#define GTZC_TZIC_PERIPH_NUMBER             (GTZC_GET_ARRAY_INDEX(GTZC_PERIPH_PKA + 1U))

/**
  * @}
  */

/** @defgroup GTZC_TZSC_Lock  GTZC TZSC Lock
  * @{
  */
#define GTZC_TZSC_LOCK_OFF                  (0U)
#define GTZC_TZSC_LOCK_ON                   (1U)
/**
  * @}
  */

/** @defgroup GTZC_MPCWM_AreaId GTZC MPCWM area identifier values
  * @{
  */
#define GTZC_TZSC_MPCWM_AREAID_UNPRIV              (0U)
#define GTZC_TZSC_MPCWM_AREAID_UNPRIV_WRITABLE     (1U)
/**
  * @}
  */


/** @defgroup GTZC_TZIC_ILA_Pending GTZC TZIC ILA Pending
  * @{
  */
#define GTZC_TZIC_NO_ILA_EVENT              (0U)
#define GTZC_TZIC_ILA_EVENT_PENDING         (1U)
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup GTZC_Exported_Functions
  * @{
  */

/** @addtogroup GTZC_Exported_Functions_Group1
  * @{
  */
/* TZSC Initialization and Configuration functions ****************************/
HAL_StatusTypeDef HAL_GTZC_TZSC_ConfigPeriphAttributes(uint32_t PeriphId, uint32_t PeriphAttributes);
HAL_StatusTypeDef HAL_GTZC_TZSC_GetConfigPeriphAttributes(uint32_t PeriphId, uint32_t *PeriphAttributes);
/**
  * @}
  */

/** @addtogroup GTZC_Exported_Functions_Group2
  * @{
  */
/* MPCWM Initialization and Configuration functions ***************************/
HAL_StatusTypeDef HAL_GTZC_TZSC_MPCWM_ConfigMemAttributes(uint32_t MemBaseAddress, MPCWM_ConfigTypeDef *pMPCWM_Desc);
HAL_StatusTypeDef HAL_GTZC_TZSC_MPCWM_GetConfigMemAttributes(uint32_t MemBaseAddress, MPCWM_ConfigTypeDef *pMPCWM_Desc);
/**
  * @}
  */

/** @addtogroup GTZC_Exported_Functions_Group3
  * @{
  */
/* TZSC and TZSC-MPCWM Lock functions *****************************************/
uint32_t          HAL_GTZC_TZSC_GetLock(GTZC_TZSC_TypeDef *TZSCx);
#if defined(CORE_CM0PLUS)
void              HAL_GTZC_TZSC_Lock(GTZC_TZSC_TypeDef *TZSCx);
/**
  * @}
  */

/** @addtogroup GTZC_Exported_Functions_Group4
  * @{
  */
/* TZIC Initialization and Configuration functions ****************************/
HAL_StatusTypeDef HAL_GTZC_TZIC_DisableIT(uint32_t PeriphId);
HAL_StatusTypeDef HAL_GTZC_TZIC_EnableIT(uint32_t PeriphId);
HAL_StatusTypeDef HAL_GTZC_TZIC_GetFlag(uint32_t PeriphId, uint32_t *Flag);
HAL_StatusTypeDef HAL_GTZC_TZIC_ClearFlag(uint32_t PeriphId);
/**
  * @}
  */

/** @addtogroup GTZC_Exported_Functions_Group5
  * @{
  */
void              HAL_GTZC_IRQHandler(void);
void              HAL_GTZC_TZIC_Callback(uint32_t PeriphId);
#endif /* CORE_CM0PLUS */
/**
  * @}
  */

/**
  * @}
  */


/* Private macro ------------------------------------------------------------*/
/** @defgroup GTZC_Private_Macros GTZC Private Macros
  * @{
  */
/**
  * @brief  GTZC private macros usable to retrieve information to access register
  *         for a specific PeriphId
  */
#define GTZC_GET_REG_INDEX(__PERIPHERAL__)    (((__PERIPHERAL__) & GTZC_PERIPH_REG_Msk) >> GTZC_PERIPH_REG_Pos)
#define GTZC_GET_PERIPH_POS(__PERIPHERAL__)   ((__PERIPHERAL__) & GTZC_PERIPH_BITPOS_Msk)

/**
  * @brief  GTZC private macro to get array index of a specific PeriphId
  *         in case of GTZC_PERIPH_ALL usage in the two following functions:
  *         HAL_GTZC_TZSC_ConfigPeriphAttributes and HAL_GTZC_TZSC_GetConfigPeriphAttributes
  */
#define GTZC_GET_ARRAY_INDEX(__PERIPHERAL__)  ((GTZC_GET_REG_INDEX(__PERIPHERAL__) * 32U) + GTZC_GET_PERIPH_POS(__PERIPHERAL__))


/**
  * @brief  GTZC private macros to check function input parameters
  */
#define IS_GTZC_ATTRIBUTE(__ATTRIBUTES__)   (((__ATTRIBUTES__) & ~(GTZC_TZSC_ATTRIBUTE_SEC | GTZC_TZSC_ATTRIBUTE_PRIV)) == 0x00u)

#define IS_GTZC_TZSC_PERIPHERAL(__PERIPHERAL__)  (((__PERIPHERAL__) == GTZC_PERIPH_AES) || ((__PERIPHERAL__) == GTZC_PERIPH_RNG) || \
                                                  ((__PERIPHERAL__) == GTZC_PERIPH_SUBGHZSPI) || ((__PERIPHERAL__) == GTZC_PERIPH_PKA) ||\
                                                  ((__PERIPHERAL__) == GTZC_PERIPH_ALL))

#define IS_GTZC_TZIC_PERIPHERAL(__PERIPHERAL__)  (((((__PERIPHERAL__) & ~(GTZC_PERIPH_REG_Pos | GTZC_PERIPH_BITPOS_Msk)) == 0x00u) && \
                                                  ((GTZC_GET_ARRAY_INDEX(__PERIPHERAL__) <= GTZC_GET_ARRAY_INDEX(GTZC_PERIPH_TZIC_MAX)))) || \
                                                  ((__PERIPHERAL__) == GTZC_PERIPH_ALLPERIPH_Msk))

#define IS_GTZC_MPCWM_MEMORY_BASEADDRESS(__BASE_ADDRESS__)   (((__BASE_ADDRESS__) == FLASH_BASE) || \
                                                              ((__BASE_ADDRESS__) == SRAM1_BASE) || \
                                                              ((__BASE_ADDRESS__) == SRAM2_BASE))

#define IS_GTZC_MPCWM_FLASH_AREAID(__AREAID__)  (((__AREAID__) == GTZC_TZSC_MPCWM_AREAID_UNPRIV) || \
                                                 ((__AREAID__) == GTZC_TZSC_MPCWM_AREAID_UNPRIV_WRITABLE))

#define IS_GTZC_MPCWM_SRAM1_AREAID(__AREAID__)  ((__AREAID__) == GTZC_TZSC_MPCWM_AREAID_UNPRIV)

#define IS_GTZC_MPCWM_SRAM2_AREAID(__AREAID__)  ((__AREAID__) == GTZC_TZSC_MPCWM_AREAID_UNPRIV)

#define IS_GTZC_MPCWM_FLASH_LENGTH(__LENGTH__)  ((((__LENGTH__) % GTZC_TZSC_MPCWM_GRANULARITY_FLASH) == 0x00u) && \
                                                  ((__LENGTH__) <= FLASH_SIZE))

#define IS_GTZC_MPCWM_SRAM1_LENGTH(__LENGTH__)  ((((__LENGTH__) % GTZC_TZSC_MPCWM_GRANULARITY_SRAM1) == 0x00u) && \
                                                  ((__LENGTH__) <= SRAM1_SIZE))

#define IS_GTZC_MPCWM_SRAM2_LENGTH(__LENGTH__)  ((((__LENGTH__) % GTZC_TZSC_MPCWM_GRANULARITY_SRAM2) == 0x00u) && \
                                                  ((__LENGTH__) <= SRAM2_SIZE))

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#endif /* GTZC_TZSC */

#ifdef __cplusplus
}
#endif

#endif /* STM32WLxx_HAL_GTZC_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
