/**
  ******************************************************************************
  * @file    md_TICK.h
  * @brief   ES32F0271 TICK HEAD File.
  *
  * @version V1.00.01
  * @date    11/20/2018
  * @author  Eastsoft AE Team
  * @note
  * detailed description
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *
  *******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MD_TICK_H__
#define __MD_TICK_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -------------------------------------------------------------------*/
#include "es32f0271.h"
#include "reg_tick.h"

/** @addtogroup Micro_Driver
  * @{
  */

#if defined (TICK)

/** @defgroup TICK TICK
  * @brief TICK micro driver
  * @{
  */

/* Private types --------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------*/
/* Private constants ----------------------------------------------------------*/
/* Private macros -------------------------------------------------------------*/

/* Public types ---------------------------------------------------------------*/

/**
  * @brief MD TICK Parameter Structure definition
  */

/* Public constants -----------------------------------------------------------*/
/** @defgroup MD_TICK_Public_Constants TICK Public Constants
  * @{
  */

/**
  * @} MD_TICK_Public_Constants
  */

/* Public macro ---------------------------------------------------------------*/
/** @defgroup MD_TICK_Public_Macros TICK Public Macros
  * @{
  */

/** @defgroup MD_TICK_PM_WRITE_READ Common write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in TICK register
  * @param  __INSTANCE__ TICK Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define MD_TICK_WRITEREG(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in TICK register
  * @param  __INSTANCE__ TICK Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define MD_TICK_READREG(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)

/**
  * @brief  Modify value in TICK register
  * @param  __INSTANCE__ TICK Instance
  * @param  __REG__ Register to be written
  * @param  __MASK__ Mask value to be written in the register
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define MD_TICK_MODIFYREG(__INSTANCE__, __REG__, __MASK__, __VALUE__) MODIFY_REG(__INSTANCE__->__REG__, __MASK__, (__VALUE__))

/**
  * @brief  Set bit value in TICK register
  * @param  __INSTANCE__ TICK Instance
  * @param  __REG__ Register to be read
  * @param  __MASK__ Mask value to be set in the register
  * @retval None
  */
#define MD_TICK_SET_BIT(__INSTANCE__, __REG__, __MASK__) SET_BIT(__INSTANCE__->__REG__, __MASK__)

/**
  * @brief  Clear bit value in TICK register
  * @param  __INSTANCE__ TICK Instance
  * @param  __REG__ Register to be read
  * @param  __MASK__ Mask value to be cleased in the register
  * @retval None
  */
#define MD_TICK_CLEAR_BIT(__INSTANCE__, __REG__, __MASK__) CLEAR_BIT(__INSTANCE__->__REG__, __MASK__)

/**
  * @brief  Read bit value in TICK register
  * @param  __INSTANCE__ TICK Instance
  * @param  __REG__ Register to be read
  * @param  __MASK__ Mask value to be read in the register
  * @retval Register bit value
  */
#define MD_TICK_READBIT(__INSTANCE__, __REG__, __MASK__) READ_BIT(__INSTANCE__->__REG__, __MASK__)

/**
  * @} MD_TICK_PM_WRITE_READ
  */

/** @defgroup MD_TICK_Macro_Drivers TICK Public Macro Drivers
  * @{
  */

/**
  * @brief  Set TICK CSR
  * @param  @arg Max Value 0x7
  *         @arg Min Value 0x0
  * @retval None
  */
__STATIC_INLINE void md_tick_set_csr(uint32_t U32)
{
  MD_TICK_WRITEREG(TICK, CSR, U32);
}

/**
  * @brief  Get TICK CSR
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0x10007
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_tick_get_csr(void)
{
  return (MD_TICK_READREG(TICK, CSR));
}

/**
  * @brief  Get TICK CSR Count Flag
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0x1
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint8_t md_tick_is_active_csr_countflag(void)
{
  return (MD_TICK_READBIT(TICK, CSR, TICK_CSR_COUNTFLAG_MSK)>>TICK_CSR_COUNTFLAG_POS);
}

/**
  * @brief  Set TICK CSR Clock Source
  * @param  @arg Max Value 0x1
  *         @arg Min Value 0x0
  * @retval None
  */
__STATIC_INLINE void md_tick_set_csr_clksource(uint32_t ClkSource)
{
  MD_TICK_MODIFYREG(TICK, CSR, TICK_CSR_CLKSOURCE_MSK, (ClkSource<<TICK_CSR_CLKSOURCE_POS));
}

/**
  * @brief  Get TICK CSR Clock Source
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0x1
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint8_t md_tick_get_csr_clksource(void)
{
  return (MD_TICK_READBIT(TICK, CSR, TICK_CSR_CLKSOURCE_MSK)>>TICK_CSR_CLKSOURCE_POS);
}

/**
  * @brief  Enable TICK CSR Tick Interrupt
  * @param None
  * @retval None
  */
__STATIC_INLINE void md_tick_enable_csr_tickint(void)
{
  MD_TICK_SET_BIT(TICK, CSR, TICK_CSR_TICKINT_MSK);
}

/**
  * @brief  Disable TICK CSR Tick Interrupt
  * @param None
  * @retval None
  */
__STATIC_INLINE void md_tick_disable_csr_tickint(void)
{
  MD_TICK_CLEAR_BIT(TICK, CSR, TICK_CSR_TICKINT_MSK);
}

/**
  * @brief  is TICK CSR Tick Interrupt Enabled
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0x1
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint8_t md_tick_is_enabled_csr_tickint(void)
{
  return (MD_TICK_READBIT(TICK, CSR, TICK_CSR_TICKINT_MSK)>>TICK_CSR_TICKINT_POS);
}

/**
  * @brief  Enable TICK CSR Enable
  * @param  None
  * @retval None
  */
__STATIC_INLINE void md_tick_enable_csr_enable(void)
{
  MD_TICK_SET_BIT(TICK, CSR, TICK_CSR_ENABLE_MSK);
}

/**
  * @brief  Disable TICK CSR Enable
  * @param  None
  * @retval None
  */
__STATIC_INLINE void md_tick_disable_csr_enable(void)
{
  MD_TICK_CLEAR_BIT(TICK, CSR, TICK_CSR_ENABLE_MSK);
}

/**
  * @brief  is TICK CSR Enable Enabled
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0x1
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint8_t md_tick_is_enabled_csr_enable(void)
{
  return (MD_TICK_READBIT(TICK, CSR, TICK_CSR_ENABLE_MSK)>>TICK_CSR_ENABLE_POS);
}

/**
  * @brief  Set TICK RVR
  * @param  @arg Max Value 0xffffff
  *         @arg Min Value 0x0
  * @retval None
  */
__STATIC_INLINE void md_tick_set_rvr(uint32_t U32)
{
  MD_TICK_WRITEREG(TICK, RVR, U32);
}

/**
  * @brief  Get TICK RVR
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xffffff
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_tick_get_rvr(void)
{
  return (MD_TICK_READREG(TICK, RVR));
}

/**
  * @brief  Set TICK RVR Reload
  * @param  @arg Max Value 0xfffffff
  *         @arg Min Value 0x0
  * @retval None
  */
__STATIC_INLINE void md_tick_set_rvr_reload(uint32_t Reload)
{
  MD_TICK_MODIFYREG(TICK, RVR, TICK_RVR_RELOAD_MSK, (Reload<<TICK_RVR_RELOAD_POSS));
}

/**
  * @brief  Get TICK RVR Reload
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xfffffff
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_tick_get_rvr_reload(void)
{
  return (MD_TICK_READBIT(TICK, RVR, TICK_RVR_RELOAD_MSK)>>TICK_RVR_RELOAD_POSS);
}

/**
  * @brief  Set TICK CVR
  * @param  @arg Max Value 0xffffff
  *         @arg Min Value 0x0
  * @retval None
  */
__STATIC_INLINE void md_tick_set_cvr(uint32_t U32)
{
  MD_TICK_WRITEREG(TICK, CVR, U32);
}

/**
  * @brief  Get TICK CVR
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xffffff
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_tick_get_cvr(void)
{
  return (MD_TICK_READREG(TICK, CVR));
}

/**
  * @brief  Set TICK CVR Current
  * @param  @arg Max Value 0xfffffff
  *         @arg Min Value 0x0
  * @retval None
  */
__STATIC_INLINE void md_tick_set_cvr_current(uint32_t Current)
{
  MD_TICK_MODIFYREG(TICK, CVR, TICK_CVR_CURRENT_MSK, (Current<<TICK_CVR_CURRENT_POSS));
}

/**
  * @brief  Get TICK CVR Current
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xfffffff
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_tick_get_cvr_current(void)
{
  return (MD_TICK_READBIT(TICK, CVR, TICK_CVR_CURRENT_MSK)>>TICK_CVR_CURRENT_POSS);
}

/**
  * @brief  Get TICK CALIB
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xffffffff
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_tick_get_calib(void)
{
  return (MD_TICK_READREG(TICK, CALIB));
}

/**
  * @brief  Get TICK CALIB NOREF
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0x1
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint8_t md_tick_get_calib_noref(void)
{
  return (MD_TICK_READBIT(TICK, CALIB, TICK_CALIB_NOREF_MSK)>>TICK_CALIB_NOREF_POS);
}

/**
  * @brief  Get TICK CALIB SKEW
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0x1
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint8_t md_tick_get_calib_skew(void)
{
  return (MD_TICK_READBIT(TICK, CALIB, TICK_CALIB_SKEW_MSK)>>TICK_CALIB_SKEW_POS);
}

/**
  * @brief  Get TICK CALIB 10ms Value
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xfffffff
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_tick_get_calib_tenms(void)
{
  return (MD_TICK_READBIT(TICK, CALIB, TICK_CALIB_TENMS_MSK)>>TICK_CALIB_TENMS_POSS);
}


/**
  * @} MD_TICK_Macro_Drivers
  */

/**
  * @} MD_TICK_Public_Macros
  */

/* Public functions -----------------------------------------------------------*/
/** @defgroup MD_TICK_Public_Functions TICK Public Functions
  * @{
  */
void    md_tick_init(void);
uint32_t  md_tick_get_mscnt(void);
uint32_t  md_tick_get_100uscnt(void);
uint32_t  md_tick_get_10uscnt(void);
void    md_tick_waitms(uint8_t Unit, uint16_t msCnt);
void    md_tick_wait100us(uint16_t Unit, uint16_t usCnt);
void    md_tick_wait10us(uint16_t Unit, uint16_t usCnt);
/**
  * @} MD_TICK_Public_Functions
  */

#endif

/**
  * @}  TICK
  */

/** 
  * @}  Micro_Driver
  */

#ifdef __cplusplus
}
#endif

#endif

/******************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
