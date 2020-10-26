/**
  ******************************************************************************
  * @file    md_HDIV.h
  * @brief   ES32F0271 HDIV HEAD File.
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
#ifndef __MD_HDIV_H__
#define __MD_HDIV_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -------------------------------------------------------------------*/
#include "es32f0271.h"
#include "reg_hdiv.h"

/** @addtogroup Micro_Driver
  * @{
  */

#if defined (HDIV)

/** @defgroup HDIV HDIV
  * @brief HDIV micro driver
  * @{
  */

/* Private types --------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------*/
/* Private constants ----------------------------------------------------------*/
/* Private macros -------------------------------------------------------------*/

/* Public types ---------------------------------------------------------------*/

/**
  * @brief MD HDIV Parameter Structure definition
  */

/* Public constants -----------------------------------------------------------*/
/** @defgroup MD_HDIV_Public_Constants HDIV Public Constants
  * @{
  */

/**
  * @} MD_HDIV_Public_Constants
  */

/* Public macro ---------------------------------------------------------------*/
/** @defgroup MD_HDIV_Public_Macros HDIV Public Macros
  * @{
  */

/** @defgroup MD_HDIV_PM_WRITE_READ Common write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in HDIV register
  * @param  __INSTANCE__ HDIV Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define MD_HDIV_WRITEREG(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in HDIV register
  * @param  __INSTANCE__ HDIV Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define MD_HDIV_READREG(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)

/**
  * @brief  Modify value in HDIV register
  * @param  __INSTANCE__ HDIV Instance
  * @param  __REG__ Register to be written
  * @param  __MASK__ Mask value to be written in the register
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define MD_HDIV_MODIFYREG(__INSTANCE__, __REG__, __MASK__, __VALUE__) MODIFY_REG(__INSTANCE__->__REG__, __MASK__, (__VALUE__))

/**
  * @brief  Set bit value in HDIV register
  * @param  __INSTANCE__ HDIV Instance
  * @param  __REG__ Register to be read
  * @param  __MASK__ Mask value to be set in the register
  * @retval None
  */
#define MD_HDIV_SET_BIT(__INSTANCE__, __REG__, __MASK__) SET_BIT(__INSTANCE__->__REG__, __MASK__)

/**
  * @brief  Clear bit value in HDIV register
  * @param  __INSTANCE__ HDIV Instance
  * @param  __REG__ Register to be read
  * @param  __MASK__ Mask value to be cleased in the register
  * @retval None
  */
#define MD_HDIV_CLEAR_BIT(__INSTANCE__, __REG__, __MASK__) CLEAR_BIT(__INSTANCE__->__REG__, __MASK__)

/**
  * @brief  Read bit value in HDIV register
  * @param  __INSTANCE__ HDIV Instance
  * @param  __REG__ Register to be read
  * @param  __MASK__ Mask value to be read in the register
  * @retval Register bit value
  */
#define MD_HDIV_READBIT(__INSTANCE__, __REG__, __MASK__) READ_BIT(__INSTANCE__->__REG__, __MASK__)

/**
  * @} MD_HDIV_PM_WRITE_READ
  */

/** @defgroup MD_HDIV_Macro_Drivers HDIV Public Macro Drivers
  * @{
  */

/**
  * @brief  Set HDIV DIVDR
  * @note  This register is given the dividend of divider before calculation starting
  * @note  When this register is written, hardware divider will start calculate
  * @param  @arg Max Value 0xffffffff
  *         @arg Min Value 0x0
  * @retval None
  */
__STATIC_INLINE void md_hdiv_set_divdr(uint32_t U32)
{
  MD_HDIV_WRITEREG(HDIV, DIVDR, U32);
}

/**
  * @brief  Get HDIV DIVIDEND
  * @note  This register is given the dividend of divider before calculation starting
  * @note  When this register is written, hardware divider will start calculate
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xffffffff
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_hdiv_get_divdr(void)
{
  return (MD_HDIV_READREG(HDIV, DIVDR));
}

/**
  * @brief  Set HDIV DIVSR
  * @note  This register is given the divisor of divider before calculation starts
  * @note  When this register is written, hardware divider will start calculate
  * @param  @arg Max Value 0xffffffff
  *         @arg Min Value 0x0
  * @retval None
  */
__STATIC_INLINE void md_hdiv_set_divsr(uint32_t U32)
{
  MD_HDIV_WRITEREG(HDIV, DIVSR, U32);
}

/**
  * @brief  Get HDIV DIVSR
  * @note  This register is given the divisor of divider before calculation starts.
  * @note  When this register is written, hardware divider will start calculate
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xffffffff
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_hdiv_get_divsr(void)
{
  return (MD_HDIV_READREG(HDIV, DIVSR));
}

/**
  * @brief  Get HDIV DIVQR
  * @note  This register holds the quotient result of divider after calculation complete
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xffffffff
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_hdiv_get_divqr(void)
{
  return (MD_HDIV_READREG(HDIV, DIVQR));
}

/**
  * @brief  Get HDIV DIVRR
  * @note  This register holds the remainder result of divider after calculation complete
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xffffffff
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_hdiv_get_divrr(void)
{
  return (MD_HDIV_READREG(HDIV, DIVRR));
}

/**
  * @brief  Get HDIV DIVSTAT
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0x7
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_hdiv_get_divstat(void)
{
  return (MD_HDIV_READREG(HDIV, DIVSTAT));
}

/**
  * @brief  Is HDIV DIVSTAT SIGN Active
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0x1 : Signed
  *         @arg Min Value 0x0 : Unsigned
  */
__STATIC_INLINE uint8_t md_hdiv_get_divsts_sign(void)
{
  return (MD_HDIV_READBIT(HDIV, DIVSTAT, HDIV_DIVSTAT_SIGN_MSK)>>HDIV_DIVSTAT_SIGN_POS);
}

/**
  * @brief  Is HDIV DIVSTAT DIV0 Active
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0x1 : The divisor is 0
  *         @arg Min Value 0x0 : The divisor is not 0
  */
__STATIC_INLINE uint8_t md_hdiv_get_divsts_div0(void)
{
  return (MD_HDIV_READBIT(HDIV, DIVSTAT, HDIV_DIVSTAT_DIV0_MSK)>>HDIV_DIVSTAT_DIV0_POS);
}

/**
  * @brief  Is HDIV DIVSTAT BUSY Active
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0x1 : The divider is busy
  *         @arg Min Value 0x0 : The divider is not busy
  */
__STATIC_INLINE uint8_t md_hdiv_get_divsts_busy(void)
{
  return (MD_HDIV_READBIT(HDIV, DIVSTAT, HDIV_DIVSTAT_BUSY_MSK)>>HDIV_DIVSTAT_BUSY_POS);
}

/**
  * @} MD_HDIV_Macro_Drivers
  */

/**
  * @} MD_HDIV_Public_Macros
  */

/* Public functions -----------------------------------------------------------*/
/** @defgroup MD_HDIV_Public_Functions HDIV Public Functions
  * @{
  */

/**
  * @} MD_HDIV_Public_Functions
  */

#endif

/**
  * @}  HDIV
  */

/** 
  * @}  Micro_Driver
  */

#ifdef __cplusplus
}
#endif

#endif

/******************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
