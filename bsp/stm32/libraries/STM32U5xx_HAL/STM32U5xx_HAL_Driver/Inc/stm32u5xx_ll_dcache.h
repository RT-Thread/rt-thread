/**
  ******************************************************************************
  * @file    stm32u5xx_ll_dcache.h
  * @author  MCD Application Team
  * @brief   Header file of DCACHE LL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef STM32U5xx_LL_DCACHE_H
#define STM32U5xx_LL_DCACHE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/
#include "stm32u5xx.h"

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */

#if defined (DCACHE1)

/** @defgroup DCACHE_LL DCACHE
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @addtogroup DCACHE_Private_Constants DCACHE Private Constants
  * @{
  */
#define LL_DCACHE_COMMAND_NO_OPERATION                    (0x00000000)
#define LL_DCACHE_COMMAND_CLEAN_BY_ADDR                   DCACHE_CR_CACHECMD_0
#define LL_DCACHE_COMMAND_INVALIDATE_BY_ADDR              DCACHE_CR_CACHECMD_1
#define LL_DCACHE_COMMAND_CLEAN_INVALIDATE_BY_ADDR        (DCACHE_CR_CACHECMD_0|DCACHE_CR_CACHECMD_1)
/**
  * @}
  */

/** @defgroup DCACHE_Read_Burst_Type Remapped Output burst type
  * @{
  */
#define LL_DCACHE_READ_BURST_WRAP         0U                  /*!< WRAP */
#define LL_DCACHE_READ_BURST_INCR         DCACHE_CR_HBURST    /*!< INCR */
/**
  * @}
  */

/** @defgroup DCACHE_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_DCACHE_ReadReg function
  * @{
  */
#define LL_DCACHE_SR_ERRF              DCACHE_SR_ERRF      /*!< Cache error flag */
#define LL_DCACHE_SR_BUSYF             DCACHE_SR_BUSYF     /*!< Busy flag */
#define LL_DCACHE_SR_CMDENDF           DCACHE_SR_CMDENDF   /*!< Command end flag */
#define LL_DCACHE_SR_BSYENDF           DCACHE_SR_BSYENDF   /*!< Full invalidate busy end flag */
#define LL_DCACHE_SR_BUSYCMDF          DCACHE_SR_BUSYCMDF  /*!< Command busy flag */
/**
  * @}
  */

/** @defgroup DCACHE_LL_EC_CLEAR_FLAG Clear Flags Defines
  * @brief    Flags defines which can be used with LL_DCACHE_WriteReg function
  * @{
  */
#define LL_DCACHE_FCR_CERRF            DCACHE_FCR_CERRF    /*!< Cache error flag */
#define LL_DCACHE_FCR_CBSYENDF         DCACHE_FCR_CBSYENDF /*!< Full invalidate busy end flag */
#define LL_DCACHE_FCR_CCMDENDF         DCACHE_FCR_CCMDENDF /*!< Command end flag*/
/**
  * @}
  */

/** @defgroup DCACHE_LL_EC_IT IT Defines
  * @brief    IT defines which can be used with LL_DCACHE_ReadReg and  LL_DCACHE_WriteReg functions
  * @{
  */
#define LL_DCACHE_IER_BSYENDIE         DCACHE_IER_BSYENDIE /*!< Busy end interrupt */
#define LL_DCACHE_IER_ERRIE            DCACHE_IER_ERRIE    /*!< Cache error interrupt */
#define LL_DCACHE_IER_CMDENDIE         DCACHE_IER_CMDENDIE /*!< Command end interrupt */
/**
  * @}
  */

/** @defgroup DCACHE_Monitor_Type Monitor type
  * @{
  */
#define LL_DCACHE_MONITOR_READ_HIT        DCACHE_CR_RHITMEN   /*!< Read Hit monitoring */
#define LL_DCACHE_MONITOR_READ_MISS       DCACHE_CR_RMISSMEN  /*!< Read Miss monitoring */
#define LL_DCACHE_MONITOR_WRITE_HIT       DCACHE_CR_WHITMEN   /*!< Write Hit monitoring */
#define LL_DCACHE_MONITOR_WRITE_MISS      DCACHE_CR_WMISSMEN  /*!< Write Miss monitoring */
#define LL_DCACHE_MONITOR_ALL             (DCACHE_CR_RHITMEN | DCACHE_CR_RMISSMEN \
                                           | DCACHE_CR_WHITMEN | DCACHE_CR_WMISSMEN)
/**
  * @}
  */

/* Exported macros --------------------------------------------------------*/
/** @defgroup DCACHE_LL_Exported_Macros DCACHE Exported Macros
  * @{
  */

/** @defgroup DCACHE_LL_EM_WRITE_READ Common write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in DCACHE register
  * @param  __INSTANCE__ DCACHE Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_DCACHE_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in DCACHE register
  * @param  __INSTANCE__ DCACHE Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_DCACHE_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup DCACHE_LL_Exported_Functions DCACHE Exported Functions
  * @{
  */

/** @defgroup DCACHE_LL_EF_Configuration Configuration
  * @{
  */

/**
  * @brief  Enable the selected DCACHE instance.
  * @rmtoll CR       EN           LL_DCACHE_Enable
  * @param  DCACHEx DCACHE instance
  * @retval None
  */
__STATIC_INLINE void LL_DCACHE_Enable(DCACHE_TypeDef *DCACHEx)
{
  SET_BIT(DCACHEx->CR, DCACHE_CR_EN);
}

/**
  * @brief  Disable the selected DCACHE instance.
  * @rmtoll CR       EN           LL_DCACHE_Disable
  * @param  DCACHEx DCACHE instance
  * @retval None
  */
__STATIC_INLINE void LL_DCACHE_Disable(DCACHE_TypeDef *DCACHEx)
{
  CLEAR_BIT(DCACHEx->CR, DCACHE_CR_EN);
}

/**
  * @brief  Get the selected DCACHE instance enable state.
  * @rmtoll CR       EN           LL_DCACHE_IsEnabled
  * @param  DCACHEx DCACHE instance
  * @retval 0: DCACHE is disabled, 1: DCACHE is enabled.
  */
__STATIC_INLINE uint32_t LL_DCACHE_IsEnabled(DCACHE_TypeDef *DCACHEx)
{
  return ((READ_BIT(DCACHEx->CR, DCACHE_CR_EN) == (DCACHE_CR_EN)) ? 1UL : 0UL);
}

/**
  * @brief  Set the dcache instance start command address.
  * @rmtoll CR       CMDRSADDRR          LL_DCACHE_SetStartAddress
  * @param  addr dcache command start address(Clean, Invalidate or Clean and Invalidate).
  * @param  DCACHEx DCACHE instance
  * @retval None
  */
__STATIC_INLINE void LL_DCACHE_SetStartAddress(DCACHE_TypeDef *DCACHEx, uint32_t addr)
{
  WRITE_REG(DCACHEx->CMDRSADDRR, addr);
}

/**
  * @brief  Get the dcache command start address.
  * @rmtoll CR       CMDRSADDRR         LL_DCACHE_GetStartAddress
  * @param  DCACHEx DCACHE instance
  * @retval Start address of dcache command
  */
__STATIC_INLINE uint32_t LL_DCACHE_GetStartAddress(DCACHE_TypeDef *DCACHEx)
{
  return (uint32_t)(READ_REG(DCACHEx->CMDRSADDRR));
}

/**
  * @brief  Set the dcache instance End command address.
  * @rmtoll CR       CMDREADDRR          LL_DCACHE_SetEndAddress
  * @param  DCACHEx DCACHE instance
  * @param  addr dcache command end address(Clean, Invalidate or Clean and Invalidate).
  * @retval None
  */
__STATIC_INLINE void LL_DCACHE_SetEndAddress(DCACHE_TypeDef *DCACHEx, uint32_t addr)
{
  WRITE_REG(DCACHEx->CMDREADDRR, addr);
}

/**
  * @brief  Get the dcache command End address.
  * @rmtoll CR       CMDREADDRR          LL_DCACHE_GetEndAddress
  * @param  DCACHEx DCACHE instance
  * @retval End address of dcache command
  */
__STATIC_INLINE uint32_t LL_DCACHE_GetEndAddress(DCACHE_TypeDef *DCACHEx)
{
  return (uint32_t)(READ_REG(DCACHEx->CMDREADDRR));
}

/**
  * @brief  Set Dcache command.
  * @rmtoll CR       CACHECMD          LL_DCACHE_SetCommand
  * @param  DCACHEx DCACHE instance
  * @param  Command command to be applied for the dcache
  *                       LL_DCACHE_COMMAND_INVALIDATE_BY_ADDR, LL_DCACHE_COMMAND_CLEAN_BY_ADDR,
  *                       LL_DCACHE_COMMAND_CLEAN_INVALIDATE_BY_ADDR,LL_DCACHE_COMMAND_NO_OPERATION
  * @retval None
  */
__STATIC_INLINE void LL_DCACHE_SetCommand(DCACHE_TypeDef *DCACHEx, uint32_t Command)
{
  /* Set dcache command */
  MODIFY_REG(DCACHEx->CR, DCACHE_CR_CACHECMD, Command);
}

/**
  * @brief  Set Dcache command.
  * @rmtoll CR       CACHECMD          LL_DCACHE_GetCommand
  * @param  DCACHEx DCACHE instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DCACHE_COMMAND_NO_OPERATION
  *         @arg @ref LL_DCACHE_COMMAND_CLEAN_BY_ADDR
  *         @arg @ref LL_DCACHE_COMMAND_INVALIDATE_BY_ADDR
  *         @arg @ref LL_DCACHE_COMMAND_CLEAN_INVALIDATE_BY_ADDR
  */
__STATIC_INLINE uint32_t LL_DCACHE_GetCommand(DCACHE_TypeDef *DCACHEx)
{
  /*Get Dcache Command */
  return (uint32_t)(READ_BIT(DCACHEx->CR, DCACHE_CR_CACHECMD));
}

/**
  * @brief  Launch Dcache Command.
  * @rmtoll CR       CACHECMD          LL_DCACHE_StartCommand
  * @param  DCACHEx DCACHE instance
  * @retval None
  */
__STATIC_INLINE void LL_DCACHE_StartCommand(DCACHE_TypeDef *DCACHEx)
{
  SET_BIT(DCACHEx->CR, DCACHE_CR_STARTCMD);
}

/**
  * @brief  Set requested read burst type.
  * @rmtoll CR       HBURST          LL_DCACHE_SetReadBurstType
  * @param  DCACHEx DCACHE instance
  * @param  ReadBurstType Burst type to be applied for Data Cache
  *                       LL_DCACHE_READ_BURST_WRAP, LL_DCACHE_READ_BURST_INCR.
  * @retval None
  */
__STATIC_INLINE void LL_DCACHE_SetReadBurstType(DCACHE_TypeDef *DCACHEx, uint32_t ReadBurstType)
{
  MODIFY_REG(DCACHEx->CR, DCACHE_CR_HBURST, ReadBurstType);
}

/**
  * @brief  Get requested read burst type.
  * @rmtoll CR       HBURST          LL_DCACHE_GetReadBurstType
  * @param  DCACHEx DCACHE instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DCACHE_READ_BURST_WRAP
  *         @arg @ref LL_DCACHE_READ_BURST_INCR
  */
__STATIC_INLINE uint32_t LL_DCACHE_GetReadBurstType(DCACHE_TypeDef *DCACHEx)
{
  return (uint32_t)(READ_BIT(DCACHEx->CR, DCACHE_CR_HBURST));
}

/**
  * @brief  Invalidate the Data cache.
  * @rmtoll CR       CACHEINV          LL_DCACHE_Invalidate
  * @param  DCACHEx DCACHE instance
  * @retval None
  */
__STATIC_INLINE void LL_DCACHE_Invalidate(DCACHE_TypeDef *DCACHEx)
{
  SET_BIT(DCACHEx->CR, DCACHE_CR_CACHEINV);
}

/**
  * @}
  */


/** @defgroup DCACHE_LL_EF_Monitor Monitor
  * @{
  */

/**
  * @brief  Enable the hit/miss monitor(s).
  * @rmtoll CR     (RMISSMEN/RHITMEN/WMISSMEN/WHITMEN)       LL_DCACHE_EnableMonitors
  * @param  DCACHEx DCACHE instance
  * @param  Monitors This parameter can be one or a combination of the following values:
  *            @arg LL_DCACHE_MONITOR_READ_HIT
  *            @arg LL_DCACHE_MONITOR_READ_MISS
  *            @arg LL_DCACHE_MONITOR_WRITE_HIT
  *            @arg LL_DCACHE_MONITOR_WRITE_MISS
  *            @arg LL_DCACHE_MONITOR_ALL
  * @retval None
  */
__STATIC_INLINE void LL_DCACHE_EnableMonitors(DCACHE_TypeDef *DCACHEx, uint32_t Monitors)
{
  SET_BIT(DCACHEx->CR, Monitors);
}

/**
  * @brief  Disable the hit/miss monitor(s).
  * @rmtoll CR     (RMISSMEN/RHITMEN/WMISSMEN/WHITMEN)       LL_DCACHE_DisableMonitors
  * @param  DCACHEx DCACHE instance
  * @param  Monitors This parameter can be one or a combination of the following values:
  *            @arg LL_DCACHE_MONITOR_READ_HIT
  *            @arg LL_DCACHE_MONITOR_READ_MISS
  *            @arg LL_DCACHE_MONITOR_WRITE_HIT
  *            @arg LL_DCACHE_MONITOR_WRITE_MISS
  *            @arg LL_DCACHE_MONITOR_ALL
  * @retval None
  */
__STATIC_INLINE void LL_DCACHE_DisableMonitors(DCACHE_TypeDef *DCACHEx, uint32_t Monitors)
{
  CLEAR_BIT(DCACHEx->CR, Monitors);
}

/**
  * @brief  Return the hit/miss monitor(s) enable state.
  * @rmtoll CR     (RMISSMEN/RHITMEN/WMISSMEN/WHITMEN)     LL_DCACHE_IsEnabledMonitors
  * @param  DCACHEx DCACHE instance
  * @param  Monitors This parameter can be one or a combination of the following values:
  *            @arg LL_DCACHE_MONITOR_READ_HIT
  *            @arg LL_DCACHE_MONITOR_READ_MISS
  *            @arg LL_DCACHE_MONITOR_WRITE_HIT
  *            @arg LL_DCACHE_MONITOR_WRITE_MISS
  *            @arg LL_DCACHE_MONITOR_ALL
  * @retval State of parameter value (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DCACHE_IsEnabledMonitors(DCACHE_TypeDef *DCACHEx, uint32_t Monitors)
{
  return (((READ_BIT(DCACHEx->CR, (DCACHE_CR_WMISSMEN | DCACHE_CR_WHITMEN | DCACHE_CR_RMISSMEN | DCACHE_CR_RHITMEN))\
            & Monitors) == (Monitors)) ? 1UL : 0UL);
}

/**
  * @brief  Reset the Data Cache performance monitoring.
  * @rmtoll CR     (RHITMRST/RMISSMRST/WHITMRST/WMISSMRST)     LL_DCACHE_ResetMonitors
  * @param  DCACHEx DCACHE instance
  * @param  Monitors Monitoring type
  *         This parameter can be a combination of the following values:
  *            @arg LL_DCACHE_MONITOR_READ_HIT
  *            @arg LL_DCACHE_MONITOR_READ_MISS
  *            @arg LL_DCACHE_MONITOR_WRITE_HIT
  *            @arg LL_DCACHE_MONITOR_WRITE_MISS
  *            @arg LL_DCACHE_MONITOR_ALL
  * @retval None
  */
__STATIC_INLINE void LL_DCACHE_ResetMonitors(DCACHE_TypeDef *DCACHEx, uint32_t Monitors)
{
  /* Reset */
  SET_BIT(DCACHEx->CR, (Monitors << 2U));

  /* Release reset */
  CLEAR_BIT(DCACHEx->CR, (Monitors << 2U));
}

/**
  * @brief  Get the Read Hit monitor Value
  * @rmtoll RHMONR       LL_DCACHE_Monitor_GetReadHitValue
  * @param  DCACHEx DCACHE instance
  * @retval Value between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_DCACHE_Monitor_GetReadHitValue(DCACHE_TypeDef *DCACHEx)
{
  return DCACHEx->RHMONR;
}

/**
  * @brief  Get the Read Miss monitor Value
  * @rmtoll RMMONR       LL_DCACHE_Monitor_GetReadMissValue
  * @param  DCACHEx DCACHE instance
  * @retval Value between Min_Data=0 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t LL_DCACHE_Monitor_GetReadMissValue(DCACHE_TypeDef *DCACHEx)
{
  return DCACHEx->RMMONR;
}

/**
  * @brief  Get the Write Hit monitor Value
  * @rmtoll WHMONR       LL_DCACHE_Monitor_GetWriteHitValue
  * @param  DCACHEx DCACHE instance
  * @retval Value between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_DCACHE_Monitor_GetWriteHitValue(DCACHE_TypeDef *DCACHEx)
{
  return DCACHEx->WHMONR;
}

/**
  * @brief  Get the Write Miss monitor Value
  * @rmtoll WMMONR       LL_DCACHE_Monitor_GetWriteMissValue
  * @param  DCACHEx DCACHE instance
  * @retval Value between Min_Data=0 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t LL_DCACHE_Monitor_GetWriteMissValue(DCACHE_TypeDef *DCACHEx)
{
  return DCACHEx->WMMONR;
}

/**
  * @}
  */

/** @defgroup DCACHE_LL_EF_IT_Management IT-Management
  * @{
  */

/**
  * @brief  Enable BusyEnd interrupt.
  * @rmtoll IER         BSYENDIE          LL_DCACHE_EnableIT_BSYEND
  * @param  DCACHEx DCACHE instance
  * @retval None
  */
__STATIC_INLINE void LL_DCACHE_EnableIT_BSYEND(DCACHE_TypeDef *DCACHEx)
{
  SET_BIT(DCACHEx->IER, DCACHE_IER_BSYENDIE);
}

/**
  * @brief  Disable BusyEnd interrupt.
  * @rmtoll IER         BSYENDIE          LL_DCACHE_DisableIT_BSYEND
  * @param  DCACHEx DCACHE instance
  * @retval None
  */
__STATIC_INLINE void LL_DCACHE_DisableIT_BSYEND(DCACHE_TypeDef *DCACHEx)
{
  CLEAR_BIT(DCACHEx->IER, DCACHE_IER_BSYENDIE);
}

/**
  * @brief  Indicates whether the Busyend interrupt is enabled.
  * @rmtoll IER         BSYENDIE          LL_DCACHE_IsEnabledIT_BSYEND
  * @param  DCACHEx DCACHE instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DCACHE_IsEnabledIT_BSYEND(DCACHE_TypeDef *DCACHEx)
{
  return ((READ_BIT(DCACHEx->IER, DCACHE_IER_BSYENDIE) == (DCACHE_IER_BSYENDIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Error interrupt.
  * @rmtoll IER         ERRIE          LL_DCACHE_EnableIT_ERR
  * @param  DCACHEx DCACHE instance
  * @retval None
  */
__STATIC_INLINE void LL_DCACHE_EnableIT_ERR(DCACHE_TypeDef *DCACHEx)
{
  SET_BIT(DCACHEx->IER, DCACHE_IER_ERRIE);
}

/**
  * @brief  Disable Error interrupt.
  * @rmtoll IER         ERRIE          LL_DCACHE_DisableIT_ERR
  * @param  DCACHEx DCACHE instance
  * @retval None
  */
__STATIC_INLINE void LL_DCACHE_DisableIT_ERR(DCACHE_TypeDef *DCACHEx)
{
  CLEAR_BIT(DCACHEx->IER, DCACHE_IER_ERRIE);
}

/**
  * @brief  Indicates whether the Error interrupt is enabled.
  * @rmtoll IER         ERRIE          LL_DCACHE_IsEnabledIT_ERR
  * @param  DCACHEx DCACHE instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DCACHE_IsEnabledIT_ERR(DCACHE_TypeDef *DCACHEx)
{
  return ((READ_BIT(DCACHEx->IER, DCACHE_IER_ERRIE) == (DCACHE_IER_ERRIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable command end interrupt.
  * @rmtoll IER         CMDENDIE         LL_DCACHE_EnableIT_CMDEND
  * @param  DCACHEx DCACHE instance
  * @retval None
  */
__STATIC_INLINE void LL_DCACHE_EnableIT_CMDEND(DCACHE_TypeDef *DCACHEx)
{
  SET_BIT(DCACHEx->IER, DCACHE_IER_CMDENDIE);
}

/**
  * @brief  Disable command end interrupt.
  * @rmtoll IER         CMDENDIE         LL_DCACHE_DisableIT_CMDEND
  * @param  DCACHEx DCACHE instance
  * @retval None
  */
__STATIC_INLINE void LL_DCACHE_DisableIT_CMDEND(DCACHE_TypeDef *DCACHEx)
{
  CLEAR_BIT(DCACHEx->IER, DCACHE_IER_CMDENDIE);
}

/**
  * @brief  Indicates whether the command end interrupt is enabled.
  * @rmtoll IER         CMDENDIE          LL_DCACHE_IsEnabledIT_CMDEND
  * @param  DCACHEx DCACHE instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DCACHE_IsEnabledIT_CMDEND(DCACHE_TypeDef *DCACHEx)
{
  return ((READ_BIT(DCACHEx->IER, DCACHE_IER_CMDENDIE) == (DCACHE_IER_CMDENDIE)) ? 1UL : 0UL);
}

/**
  * @brief  Clear full invalidate busy end flag.
  * @rmtoll FCR      CBSYENDF         LL_DCACHE_ClearFlag_BSYEND
  * @param  DCACHEx DCACHE instance
  * @retval None
  */
__STATIC_INLINE void LL_DCACHE_ClearFlag_BSYEND(DCACHE_TypeDef *DCACHEx)
{
  WRITE_REG(DCACHEx->FCR, DCACHE_FCR_CBSYENDF);
}

/**
  * @brief  Clear cache error flag.
  * @rmtoll FCR      CERRF        LL_DCACHE_ClearFlag_ERR
  * @param  DCACHEx DCACHE instance
  * @retval None
  */
__STATIC_INLINE void LL_DCACHE_ClearFlag_ERR(DCACHE_TypeDef *DCACHEx)
{
  WRITE_REG(DCACHEx->FCR, DCACHE_FCR_CERRF);
}

/**
  * @brief  Clear command end flag.
  * @rmtoll FCR      CCMDENDF        LL_DCACHE_ClearFlag_CMDEND
  * @param  DCACHEx DCACHE instance
  * @retval None
  */
__STATIC_INLINE void LL_DCACHE_ClearFlag_CMDEND(DCACHE_TypeDef *DCACHEx)
{
  WRITE_REG(DCACHEx->FCR, DCACHE_FCR_CCMDENDF);
}

/**
  * @brief  Get flag Dcache BUSY.
  * @rmtoll SR      BUSYF            LL_DCACHE_IsActiveFlag_BUSY
  * @param  DCACHEx DCACHE instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DCACHE_IsActiveFlag_BUSY(DCACHE_TypeDef *DCACHEx)
{
  return ((READ_BIT(DCACHEx->SR, DCACHE_SR_BUSYF) == (DCACHE_SR_BUSYF)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag Dcache Busyend.
  * @rmtoll SR      BSYENDF            LL_DCACHE_IsActiveFlag_BSYEND
  * @param  DCACHEx DCACHE instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DCACHE_IsActiveFlag_BSYEND(DCACHE_TypeDef *DCACHEx)
{
  return ((READ_BIT(DCACHEx->SR, DCACHE_SR_BSYENDF) == (DCACHE_SR_BSYENDF)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag Dcache Error.
  * @rmtoll SR      ERRF            LL_DCACHE_IsActiveFlag_ERR
  * @param  DCACHEx DCACHE instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DCACHE_IsActiveFlag_ERR(DCACHE_TypeDef *DCACHEx)
{
  return ((READ_BIT(DCACHEx->SR, DCACHE_SR_ERRF) == (DCACHE_SR_ERRF)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag Dcache Busy command.
  * @rmtoll SR      BUSYCMDF            LL_DCACHE_IsActiveFlag_BUSYCMD
  * @param  DCACHEx DCACHE instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DCACHE_IsActiveFlag_BUSYCMD(DCACHE_TypeDef *DCACHEx)
{
  return ((READ_BIT(DCACHEx->SR, DCACHE_SR_BUSYCMDF) == (DCACHE_SR_BUSYCMDF)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag Dcache command end.
  * @rmtoll SR      CMDENDF            LL_DCACHE_IsActiveFlag_CMDEND
  * @param  DCACHEx DCACHE instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DCACHE_IsActiveFlag_CMDEND(DCACHE_TypeDef *DCACHEx)
{
  return ((READ_BIT(DCACHEx->SR, DCACHE_SR_CMDENDF) == (DCACHE_SR_CMDENDF)) ? 1UL : 0UL);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined(DCACHE1) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32U5xx_LL_DCACHE_H */
