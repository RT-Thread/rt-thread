/**
  ******************************************************************************
  * @file    md_RTC.h
  * @brief   ES32F0271 RTC HEAD File.
  *
  * @version V1.00.02
  * @date    30/11/2018
  * @author  Eastsoft AE Team
  * @note
  * detailed description
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MD_RTC_H__
#define __MD_RTC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -------------------------------------------------------------------*/ 
#include <stdbool.h>
#include "es32f0271.h"
#include "reg_rtc.h"

/** @addtogroup Micro_Driver
  * @{
  */

#if defined (RTC)

/** @defgroup RTC RTC
  * @brief RTC micro driver
  * @{
  */
  
/* Private types --------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------*/
/* Private constants ----------------------------------------------------------*/
/* Private macros -------------------------------------------------------------*/

/* Public types ---------------------------------------------------------------*/
/** @defgroup MD_RTC_PT_INIT RTC Public Init structures
  * @{
  */

/**
  * @brief MD RTC Init Structure definition
  */


/**
  * @} MD_RTC_PT_INIT
  */

/* Public constants -----------------------------------------------------------*/
/** @defgroup MD_RTC_Public_Constants RTC Public Constants
  * @{
  */

/** @defgroup MD_RTC_CON_MODE_ RTC Clock Calibration Mode
  * @{
  */
#define MD_RTC_CON_MODE_INCR    (0x00000000UL)    /** @brief Increase calibration value when match calibration cycle. */
#define MD_RTC_CON_MODE_DECR    (0X00000001UL)    /** @brief DMA Decrease calibration value when match calibration cycle. */
/**
  * @} MD_RTC_CON_MODE_
  */

/** @defgroup MD_RTC_CON_CYCLE_ RTC Calibration Cycle Select
  * @{
  */
#define MD_RTC_CON_CYCLE_60S    (0x00000000UL)    /** @brief When enable Calibration Function, the calibrate cycle is 60s. */
#define MD_RTC_CON_CYCLE_1S     (0X00000001UL)    /** @brief When enable Calibration Function, the calibrate cycle is 1s. */
/**
  * @} MD_RTC_CON_CYCLE_
  */

/** @defgroup MD_RTC_CON_CKSEL_ RTC Clock Source Selection
  * @{
  */
#define MD_RTC_CON_CKSEL_NO     (0x00000000UL)    /** @brief No clock */
#define MD_RTC_CON_CKSEL_LOSC   (0X00000001UL)    /** @brief LOSC oscillator clock used as RTC clock */
#define MD_RTC_CON_CKSEL_LRC    (0x00000002UL)    /** @brief LRC oscillator clock used as RTC clock */
#define MD_RTC_CON_CKSEL_PLL    (0X00000003UL)    /** @brief PLL Reference clock source divided by 128 used as RTC clock */
/**
  * @} MD_RTC_CON_CKSEL_
  */

/** @defgroup MD_RTC_WKUP_WKSCAL RTC Wakeup Counter Scale Value
  * @{
  */
#define MD_RTC_WKUP_WKSCAL_DIV1    (0x00000000UL)    /** @brief Divide 1, wakeup counter will count each second. */
#define MD_RTC_WKUP_WKSCAL_DIV2    (0X00000001UL)    /** @brief Divide 2, wakeup counter will count each 1/2 second. */
#define MD_RTC_WKUP_WKSCAL_DIV4    (0x00000002UL)    /** @brief Divide 4, wakeup counter will count each 1/4 second. */
#define MD_RTC_WKUP_WKSCAL_DIV8    (0X00000003UL)    /** @brief Divide 8, wakeup counter will count each 1/8 second. */
#define MD_RTC_WKUP_WKSCAL_DIV16   (0X00000004UL)    /** @brief Divide 16, wakeup counter will count each 1/16 second. */
/**
  * @} MD_RTC_WKUP_WKSCAL
  */

/** @defgroup MD_RTC_WKUP_WKSEL RTC Wakeup Counter Events Select
  * @{
  */
#define MD_RTC_WKUP_WKSEL_OFF    (0x00000000UL)    /** @brief OFF */
#define MD_RTC_WKUP_WKSEL_RTC    (0X00000001UL)    /** @brief Start counter when RTC start. */
#define MD_RTC_WKUP_WKSEL_SLEEP  (0x00000002UL)    /** @brief Start counter when receive sleep flag. */
/**
  * @} MD_RTC_WKUP_WKSEL
  */

/** @defgroup MD_RTC_STAT_SYNDONE RTC Calendar Synchronization status
  * @{
  */
#define MD_RTC_STAT_SYNDONE_UNDER  (0x00000000UL)    /** @brief RTC is under Synchronization procedure */
#define MD_RTC_STAT_SYNDONE_CMP    (0X00000001UL)    /** @brief RTC Synchronization procedure is Completed */
/**
  * @} MD_RTC_STAT_SYNDONE
  */

/** @defgroup MD_RTC_BKEN_BKEN Read RTC Backup Register Enable
  * @{
  */
#define MD_RTC_BKEN_BKEN_CONTROL   (0x00000000UL)    /** @brief Read RTCTIME & RTCCAL From control register. */
#define MD_RTC_BKEN_BKEN_BACKUP    (0X00000001UL)    /** @brief Read RTCTIME & RTCCAL From backup register. */
/**
  * @} MD_RTC_BKEN_BKEN
  */

/**
  * @} MD_RTC_Public_Constants
  */

/* Public macro ---------------------------------------------------------------*/
/** @defgroup MD_RTC_Public_Macros RTC Public Macros
  * @{
  */

/**
  * @brief  Set RTC Clock Calibration Mode
  * @param  rtc RTC Instance
  * @param  mode can be one of the following values:
  *         @arg @ref MD_RTC_CON_MODE_INCR
  *         @arg @ref MD_RTC_CON_MODE_DECR
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_con_mode(RTC_TypeDef *rtc, uint32_t mode)
{
  MODIFY_REG(rtc->CON, RTC_CON_MODE_MSK, (mode<<RTC_CON_MODE_POS));
}
/**
  * @brief  Get RTC Clock Calibration Mode
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_RTC_CON_MODE_INCR
  *         @arg @ref MD_RTC_CON_MODE_DECR
  */
__STATIC_INLINE uint32_t md_rtc_get_con_mode(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->CON, RTC_CON_MODE_MSK)>>RTC_CON_MODE_POS);
}
/**
  * @brief  Set RTC Clock Calibration Value
  * @param  rtc RTC Instance
  * @param  calval Max calibration value is CALV.
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_con_calval(RTC_TypeDef *rtc, uint32_t calval)
{
  MODIFY_REG(rtc->CON, RTC_CON_CALVAL_MSK, (calval<<RTC_CON_CALVAL_POSS));
}
/**
  * @brief  Get RTC Clock Calibration Value
  * @param  rtc RTC Instance
  * @retval Max calibration value is CALV.
  */
__STATIC_INLINE uint32_t md_rtc_get_con_calval(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->CON, RTC_CON_CALVAL_MSK)>>RTC_CON_CALVAL_POSS);
}
/**
  * @brief  Set RTC Clock Counter Scale
  * @param  rtc RTC Instance
  * @param  scale Max divider of This counter is (SCALE+1).
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_con_scale(RTC_TypeDef *rtc, uint32_t scale)
{
  MODIFY_REG(rtc->CON, RTC_CON_SCALE_MSK, (scale<<RTC_CON_SCALE_POSS));
}
/**
  * @brief  Get RTC Clock Counter Scale
  * @param  rtc RTC Instance
  * @retval Max divider of This counter is (SCALE+1).
  */
__STATIC_INLINE uint32_t md_rtc_get_con_scale(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->CON, RTC_CON_SCALE_MSK)>>RTC_CON_SCALE_POSS);
}
/**
  * @brief  Set RTC Clock Counter Prescale
  * @param  rtc RTC Instance
  * @param  pscale Max divider of This counter is (PSCALE+1).
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_con_pscale(RTC_TypeDef *rtc, uint32_t pscale)
{
  MODIFY_REG(rtc->CON, RTC_CON_PSCALE_MSK, (pscale<<RTC_CON_PSCALE_POSS));
}
/**
  * @brief  Get RTC Clock Counter Prescale
  * @param  rtc RTC Instance
  * @retval Max divider of This counter is (PSCALE+1).
  */
__STATIC_INLINE uint32_t md_rtc_get_con_pscale(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->CON, RTC_CON_PSCALE_MSK)>>RTC_CON_PSCALE_POSS);
}
/**
  * @brief  Set RTC Calibration Cycle Select
  * @param  rtc RTC Instance
  * @param  cycle This parameter can be one of the following values:
  *         @arg @ref MD_RTC_CON_CYCLE_60S
  *         @arg @ref MD_RTC_CON_CYCLE_1S
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_con_cycle(RTC_TypeDef *rtc, uint32_t cycle)
{
  MODIFY_REG(rtc->CON, RTC_CON_CYCLE_MSK, (cycle<<RTC_CON_CYCLE_POS));
}
/**
  * @brief  Get RTC Calibration Cycle Select
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_RTC_CON_CYCLE_60S
  *         @arg @ref MD_RTC_CON_CYCLE_1S
  */
__STATIC_INLINE uint32_t md_rtc_get_con_cycle(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->CON, RTC_CON_CYCLE_MSK)>>RTC_CON_CYCLE_POS);
}
/**
  * @brief  Set RTC Calibration Function Enable
  * @param  rtc RTC Instance
  * @param  calib This parameter can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_con_calib(RTC_TypeDef *rtc, uint32_t calib)
{
  MODIFY_REG(rtc->CON, RTC_CON_CALIB_MSK, (calib<<RTC_CON_CALIB_POS));
}
/**
  * @brief  Get RTC Calibration Function Enable
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_con_calib(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->CON, RTC_CON_CALIB_MSK)>>RTC_CON_CALIB_POS);
}
/**
  * @brief  Set RTC Clock Source Selection
  * @param  rtc RTC Instance
  * @param  cksel This parameter can be one of the following values:
  *         @arg @ref MD_RTC_CON_CKSEL_NO
  *         @arg @ref MD_RTC_CON_CKSEL_LOSC
  *         @arg @ref MD_RTC_CON_CKSEL_LRC
  *         @arg @ref MD_RTC_CON_CKSEL_PLL
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_con_cksel(RTC_TypeDef *rtc, uint32_t cksel)
{
  MODIFY_REG(rtc->CON, RTC_CON_CKSEL_MSK, (cksel<<RTC_CON_CKSEL_POSS));
}
/**
  * @brief  Get RTC Clock Source Selection
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_RTC_CON_CKSEL_NO
  *         @arg @ref MD_RTC_CON_CKSEL_LOSC
  *         @arg @ref MD_RTC_CON_CKSEL_LRC
  *         @arg @ref MD_RTC_CON_CKSEL_PLL
  */
__STATIC_INLINE uint32_t md_rtc_get_con_cksel(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->CON, RTC_CON_CKSEL_MSK)>>RTC_CON_CKSEL_POSS);
}
/**
  * @brief  Set RTC Counter Enable bit
  * @param  rtc RTC Instance
  * @param  rtcen This parameter can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_con_rtcen(RTC_TypeDef *rtc, uint32_t rtcen)
{
  MODIFY_REG(rtc->CON, RTC_CON_RTCEN_MSK, (rtcen<<RTC_CON_RTCEN_POS));
}
/**
  * @brief  Get RTC Counter Enable bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_con_rtcen(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->CON, RTC_CON_RTCEN_MSK)>>RTC_CON_RTCEN_POS);
}

/** @defgroup MD_RTC_CON_MODE MODE
  * @brief  Set RTC Clock Calibration Mode bit for md_rtc_set_con() function used
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref MD_RTC_CON_MODE_INCR
  *         @arg @ref MD_RTC_CON_MODE_DECR
  * @{
  */
#define md_rtc_set_con_mode_fun(mode)  (mode<<RTC_CON_MODE_POS)
/**
  * @} MD_RTC_CON_MODE
  */
/** @defgroup MD_RTC_CON_CALVAL CALVAL
  * @brief  Set RTC Clock Calibration Value bit for md_rtc_set_con() function used
  * @param  calval Max calibration value is CALV.
  * @{
  */
#define md_rtc_set_con_calval_fun(calval)  (calval<<RTC_CON_CALVAL_POSS)
/**
  * @} MD_RTC_CON_CALVAL
  */
/** @defgroup MD_RTC_CON_SCALE SCALE
  * @brief  Set RTC Clock Counter Scale bit for md_rtc_set_con() function used
  * @param  scale Max divider of This counter is (SCALE+1).
  * @{
  */
#define md_rtc_set_con_scale_fun(scale)  (scale<<RTC_CON_SCALE_POSS)
/**
  * @} MD_RTC_CON_SCALE
  */
/** @defgroup MD_RTC_CON_PSCALE PSCALE
  * @brief  Set RTC Clock Counter Prescale bit for md_rtc_set_con() function used
  * @param  pscale Max divider of This counter is (PSCALE+1).
  * @{
  */
#define md_rtc_set_con_pscale_fun(pscale)  (pscale<<RTC_CON_PSCALE_POSS)
/**
  * @} MD_RTC_CON_PSCALE
  */
/** @defgroup MD_RTC_CON_CYCLE CYCLE
  * @brief  Set RTC Calibration Cycle Select bit for md_rtc_set_con() function used
  * @param  cycle This parameter can be one of the following values:
  *         @arg @ref MD_RTC_CON_CYCLE_60S
  *         @arg @ref MD_RTC_CON_CYCLE_1S
  * @{
  */
#define md_rtc_set_con_cycle_fun(cycle)  (cycle<<RTC_CON_CYCLE_POS)
/**
  * @} MD_RTC_CON_CYCLE
  */
/** @defgroup MD_RTC_CON_CALIB CALIB
  * @brief  Set RTC Calibration Function Enable bit for md_rtc_set_con() function used
  * @param  calib This parameter can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @{
  */
#define md_rtc_set_con_calib_fun(calib)  (calib<<RTC_CON_CALIB_POS)
/**
  * @} MD_RTC_CON_CALIB
  */
/** @defgroup MD_RTC_CON_CKSEL CKSEL
  * @brief  Set RTC Clock Source Selection bit for md_rtc_set_con() function used
  * @param  cksel This parameter can be one of the following values:
  *         @arg @ref MD_RTC_CON_CKSEL_NO
  *         @arg @ref MD_RTC_CON_CKSEL_LOSC
  *         @arg @ref MD_RTC_CON_CKSEL_LRC
  *         @arg @ref MD_RTC_CON_CKSEL_PLL
  * @{
  */
#define md_rtc_set_con_cksel_fun(cksel)  (cksel<<RTC_CON_CKSEL_POSS)
/**
  * @} MD_RTC_CON_CKSEL
  */
/** @defgroup MD_RTC_CON_RTCEN RTCEN
  * @brief  Set RTC Counter Enable bit bit for md_rtc_set_con() function used
  * @param  rtcen This parameter can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @{
  */
#define md_rtc_set_con_rtcen_fun(rtcen)  (rtcen<<RTC_CON_RTCEN_POS)
/**
  * @} MD_RTC_CON_RTCEN
  */
/**
  * @brief  Set RTC Control Register
  * @param  rtc RTC Instance
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref md_rtc_set_con_mode_fun(mode)
  * @param  calval This parameter can be one of the following values:
  *         @arg @ref md_rtc_set_con_calval_fun(calval)
  * @param  scale This parameter can be one of the following values:
  *         @arg @ref md_rtc_set_con_scale_fun(scale)
  * @param  pscale This parameter can be one of the following values:
  *         @arg @ref md_rtc_set_con_pscale_fun(pscale)
  * @param  cycle This parameter can be one of the following values:
  *         @arg @ref md_rtc_set_con_cycle_fun(cycle)
  * @param  calib This parameter can be one of the following values:
  *         @arg @ref md_rtc_set_con_calib_fun(calib)
  * @param  cksel This parameter can be one of the following values:
  *         @arg @ref md_rtc_set_con_cksel_fun(cksel)
  * @param  rtcen This parameter can be one of the following values:
  *         @arg @ref md_rtc_set_con_rtcen_fun(rtcen)
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_con(RTC_TypeDef *rtc, uint32_t mode,  uint32_t calval,  uint32_t scale,
                                                      uint32_t pscale,uint32_t cycle,   uint32_t calib,
                                                      uint32_t cksel, uint32_t rtcen)
{
  WRITE_REG(rtc->CON, (mode|calval|scale|pscale|cycle|calib|cksel|rtcen));
}


/**
  * @brief  Set RTC Wakeup Counter Scale Value
  * @param  rtc RTC Instance
  * @param  wkscal This parameter can be one of the following values:
  *         @arg @ref MD_RTC_WKUP_WKSCAL_DIV1
  *         @arg @ref MD_RTC_WKUP_WKSCAL_DIV2
  *         @arg @ref MD_RTC_WKUP_WKSCAL_DIV4
  *         @arg @ref MD_RTC_WKUP_WKSCAL_DIV8
  *         @arg @ref MD_RTC_WKUP_WKSCAL_DIV16
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_wkup_wkscal(RTC_TypeDef *rtc, uint32_t wkscal)
{
  MODIFY_REG(rtc->WKUP, RTC_WKUP_WKSCAL_MSK, (wkscal<<RTC_WKUP_WKSCAL_POSS));
}
/**
  * @brief  Get RTC Wakeup Counter Scale Value
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_RTC_WKUP_WKSCAL_DIV1
  *         @arg @ref MD_RTC_WKUP_WKSCAL_DIV2
  *         @arg @ref MD_RTC_WKUP_WKSCAL_DIV4
  *         @arg @ref MD_RTC_WKUP_WKSCAL_DIV8
  *         @arg @ref MD_RTC_WKUP_WKSCAL_DIV16
  */
__STATIC_INLINE uint32_t md_rtc_get_wkup_wkscal(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->WKUP, RTC_WKUP_WKSCAL_MSK)>>RTC_WKUP_WKSCAL_POSS);
}
/**
  * @brief  Set RTC Wakeup Counter Events Select
  * @param  rtc RTC Instance
  * @param  wksel This parameter can be one of the following values:
  *         @arg @ref MD_RTC_WKUP_WKSEL_OFF
  *         @arg @ref MD_RTC_WKUP_WKSEL_RTC
  *         @arg @ref MD_RTC_WKUP_WKSEL_SLEEP
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_wkup_wksel(RTC_TypeDef *rtc, uint32_t wksel)
{
  MODIFY_REG(rtc->WKUP, RTC_WKUP_WKSEL_MSK, (wksel<<RTC_WKUP_WKSEL_POSS));
}
/**
  * @brief  Get RTC Wakeup Counter Events Select
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_RTC_WKUP_WKSEL_OFF
  *         @arg @ref MD_RTC_WKUP_WKSEL_RTC
  *         @arg @ref MD_RTC_WKUP_WKSEL_SLEEP
  */
__STATIC_INLINE uint32_t md_rtc_get_wkup_wksel(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->WKUP, RTC_WKUP_WKSEL_MSK)>>RTC_WKUP_WKSEL_POSS);
}
/**
  * @brief  Set RTC Wakeup Counter setting value
  * @param  rtc RTC Instance
  * @param  wkcal Max value is WKCAL seconds
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_wkup_wkcal(RTC_TypeDef *rtc, uint32_t wkcal)
{
  MODIFY_REG(rtc->WKUP, RTC_WKUP_WKCAL_MSK, (wkcal<<RTC_WKUP_WKCAL_POSS));
}
/**
  * @brief  Get RTC Wakeup Counter setting value
  * @param  rtc RTC Instance
  * @retval Max value is WKCAL seconds
  */
__STATIC_INLINE uint32_t md_rtc_get_wkup_wkcal(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->WKUP, RTC_WKUP_WKCAL_MSK)>>RTC_WKUP_WKCAL_POSS);
}


/**
  * @brief  Set Week Value
  * @param  rtc RTC Instance
  * @param  week value in RTC timer, in BCD format.
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_time_week(RTC_TypeDef *rtc, uint32_t week)
{
  MODIFY_REG(rtc->TIME, RTC_TIME_WEEK_MSK, (week<<RTC_TIME_WEEK_POSS));
}
/**
  * @brief  Get Week Value
  * @param  rtc RTC Instance
  * @retval Week value in RTC timer, in BCD format.
  */
__STATIC_INLINE uint32_t md_rtc_get_time_week(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->TIME, RTC_TIME_WEEK_MSK)>>RTC_TIME_WEEK_POSS);
}
/**
  * @brief  Set Hour Tens Value
  * @param  rtc RTC Instance
  * @param  hour_t Hour tens value in RTC timer, in BCD format.
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_time_hour_t(RTC_TypeDef *rtc, uint32_t hour_t)
{
  MODIFY_REG(rtc->TIME, RTC_TIME_HOUR_T_MSK, (hour_t<<RTC_TIME_HOUR_T_POSS));
}
/**
  * @brief  Get Hour Tens Value
  * @param  rtc RTC Instance
  * @retval Hour tens value in RTC timer, in BCD format.
  */
__STATIC_INLINE uint32_t md_rtc_get_time_hour_t(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->TIME, RTC_TIME_HOUR_T_MSK)>>RTC_TIME_HOUR_T_POSS);
}
/**
  * @brief  Set Hour Units Value
  * @param  rtc RTC Instance
  * @param  hour_u Hour units value in RTC timer, in BCD format.
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_time_hour_u(RTC_TypeDef *rtc, uint32_t hour_u)
{
  MODIFY_REG(rtc->TIME, RTC_TIME_HOUR_U_MSK, (hour_u<<RTC_TIME_HOUR_U_POSS));
}
/**
  * @brief  Get Hour Units Value
  * @param  rtc RTC Instance
  * @retval Hour units value in RTC timer, in BCD format.
  */
__STATIC_INLINE uint32_t md_rtc_get_time_hour_u(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->TIME, RTC_TIME_HOUR_U_MSK)>>RTC_TIME_HOUR_U_POSS);
}
/**
  * @brief  Set Minute Tens Value
  * @param  rtc RTC Instance
  * @param  min_t Minute tens value in RTC timer, in BCD format.
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_time_min_t(RTC_TypeDef *rtc, uint32_t min_t)
{
  MODIFY_REG(rtc->TIME, RTC_TIME_MIN_T_MSK, (min_t<<RTC_TIME_MIN_T_POSS));
}
/**
  * @brief  Get Minute Tens Value
  * @param  rtc RTC Instance
  * @retval Minute tens value in RTC timer, in BCD format.
  */
__STATIC_INLINE uint32_t md_rtc_get_time_min_t(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->TIME, RTC_TIME_MIN_T_MSK)>>RTC_TIME_MIN_T_POSS);
}
/**
  * @brief  Set Minute Units Value
  * @param  rtc RTC Instance
  * @param  min_u Minute units value in RTC timer, in BCD format.
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_time_min_u(RTC_TypeDef *rtc, uint32_t min_u)
{
  MODIFY_REG(rtc->TIME, RTC_TIME_MIN_U_MSK, (min_u<<RTC_TIME_MIN_U_POSS));
}
/**
  * @brief  Get Minute Units Value
  * @param  rtc RTC Instance
  * @retval Minute units value in RTC timer, in BCD format.
  */
__STATIC_INLINE uint32_t md_rtc_get_time_min_u(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->TIME, RTC_TIME_MIN_U_MSK)>>RTC_TIME_MIN_U_POSS);
}
/**
  * @brief  Set Second Tens Value
  * @param  rtc RTC Instance
  * @param  sec_t Second tens value in RTC timer, in BCD format.
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_time_sec_t(RTC_TypeDef *rtc, uint32_t sec_t)
{
  MODIFY_REG(rtc->TIME, RTC_TIME_SEC_T_MSK, (sec_t<<RTC_TIME_SEC_T_POSS));
}
/**
  * @brief  Get Second Tens Value
  * @param  rtc RTC Instance
  * @retval Second tens value in RTC timer, in BCD format.
  */
__STATIC_INLINE uint32_t md_rtc_get_time_sec_t(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->TIME, RTC_TIME_SEC_T_MSK)>>RTC_TIME_SEC_T_POSS);
}
/**
  * @brief  Set Second Units Value
  * @param  rtc RTC Instance
  * @param  sec_u Second units value in RTC timer, in BCD format.
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_time_sec_u(RTC_TypeDef *rtc, uint32_t sec_u)
{
  MODIFY_REG(rtc->TIME, RTC_TIME_SEC_U_MSK, (sec_u<<RTC_TIME_SEC_U_POSS));
}
/**
  * @brief  Get Second Units Value
  * @param  rtc RTC Instance
  * @retval Second units value in RTC timer, in BCD format.
  */
__STATIC_INLINE uint32_t md_rtc_get_time_sec_u(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->TIME, RTC_TIME_SEC_U_MSK)>>RTC_TIME_SEC_U_POSS);
}

/** @defgroup MD_RTC_TIME_WEEK WEEK
  * @brief  Set Week Value bit bit for md_rtc_set_time() function used
  * @param  week value in RTC timer, in BCD format.
  * @{
  */
#define md_rtc_set_time_week_fun(week)  (week<<RTC_TIME_WEEK_POSS)
/**
  * @} MD_RTC_TIME_WEEK
  */
/** @defgroup MD_RTC_TIME_HOUR_T HOUR_T
  * @brief  Set Hour Tens Value bit bit for md_rtc_set_time() function used
  * @param  hour_t Hour tens value in RTC timer, in BCD format.
  * @{
  */
#define md_rtc_set_time_hour_t_fun(hour_t)  (hour_t<<RTC_TIME_HOUR_T_POSS)
/**
  * @} MD_RTC_TIME_HOUR_T
  */
/** @defgroup MD_RTC_TIME_HOUR_U HOUR_U
  * @brief  Set Hour Units Value bit bit for md_rtc_set_time() function used
  * @param  hour_u Hour units value in RTC timer, in BCD format.
  * @{
  */
#define md_rtc_set_time_hour_u_fun(hour_u)  (hour_u<<RTC_TIME_HOUR_U_POSS)
/**
  * @} MD_RTC_TIME_HOUR_U
  */
/** @defgroup MD_RTC_TIME_MIN_T MIN_T
  * @brief  Set Minute Tens Value bit bit for md_rtc_set_time() function used
  * @param  min_t Minute tens value in RTC timer, in BCD format.
  * @{
  */
#define md_rtc_set_time_min_t_fun(min_t)  (min_t<<RTC_TIME_MIN_T_POSS)
/**
  * @} MD_RTC_TIME_MIN_T
  */
/** @defgroup MD_RTC_TIME_MIN_U MIN_U
  * @brief  Set Minute Units Value bit bit for md_rtc_set_time() function used
  * @param  min_u Minute units value in RTC timer, in BCD format.
  * @{
  */
#define md_rtc_set_time_min_u_fun(min_u)  (min_u<<RTC_TIME_MIN_U_POSS)
/**
  * @} MD_RTC_TIME_MIN_U
  */
/** @defgroup MD_RTC_TIME_SEC_T SEC_T
  * @brief  Set Second Tens Value bit bit for md_rtc_set_time() function used
  * @param  sec_t Second tens value in RTC timer, in BCD format.
  * @{
  */
#define md_rtc_set_time_sec_t_fun(sec_t)  (sec_t<<RTC_TIME_SEC_T_POSS)
/**
  * @} MD_RTC_TIME_SEC_T
  */
/** @defgroup MD_RTC_TIME_SEC_U SEC_U
  * @brief  Set Second Units Value bit bit for md_rtc_set_time() function used
  * @param  sec_u Second units value in RTC timer, in BCD format.
  * @{
  */
#define md_rtc_set_time_sec_u_fun(sec_u)  (sec_u<<RTC_TIME_SEC_U_POSS)
/**
  * @} MD_RTC_TIME_SEC_U
  */
/**
  * @brief  Set RTC Control Register
  * @param  rtc RTC Instance
  * @param  week This parameter can be one of the following values:
  *         @arg @ref md_rtc_set_time_week_fun(week)
  * @param  hour_t This parameter can be one of the following values:
  *         @arg @ref md_rtc_set_time_hour_t_fun(hour_t)
  * @param  hour_u This parameter can be one of the following values:
  *         @arg @ref md_rtc_set_time_hour_u_fun(hour_u)
  * @param  min_t This parameter can be one of the following values:
  *         @arg @ref md_rtc_set_time_min_t_fun(min_t)
  * @param  min_u This parameter can be one of the following values:
  *         @arg @ref md_rtc_set_time_min_u_fun(min_u)
  * @param  sec_t This parameter can be one of the following values:
  *         @arg @ref md_rtc_set_time_sec_t_fun(sec_t)
  * @param  sec_u This parameter can be one of the following values:
  *         @arg @ref md_rtc_set_time_sec_u_fun(sec_u)
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_time(RTC_TypeDef *rtc,  uint32_t week,  uint32_t hour_t,  uint32_t hour_u,
                                                        uint32_t min_t, uint32_t min_u,   uint32_t sec_t,
                                                        uint32_t sec_u)
{
  WRITE_REG(rtc->TIME, (week|hour_t|hour_u|min_t|min_u|sec_t|sec_u));
}










/**
  * @brief  Set Year Tens Value
  * @param  rtc RTC Instance
  * @param  year_t Year tens value in RTC timer, in BCD format.
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_cal_year_t(RTC_TypeDef *rtc, uint32_t year_t)
{
  MODIFY_REG(rtc->CAL, RTC_CAL_YEAR_T_MSK, (year_t<<RTC_CAL_YEAR_T_POSS));
}
/**
  * @brief  Get Year Tens Value
  * @param  rtc RTC Instance
  * @retval Year tens value in RTC timer, in BCD format.
  */
__STATIC_INLINE uint32_t md_rtc_get_cal_year_t(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->CAL, RTC_CAL_YEAR_T_MSK)>>RTC_CAL_YEAR_T_POSS);
}
/**
  * @brief  Set Year Units Value
  * @param  rtc RTC Instance
  * @param  year_u Year units value in RTC timer, in BCD format.
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_cal_year_u(RTC_TypeDef *rtc, uint32_t year_u)
{
  MODIFY_REG(rtc->CAL, RTC_CAL_YEAR_U_MSK, (year_u<<RTC_CAL_YEAR_U_POSS));
}
/**
  * @brief  Get Year Units Value
  * @param  rtc RTC Instance
  * @retval Year units value in RTC timer, in BCD format.
  */
__STATIC_INLINE uint32_t md_rtc_get_cal_year_u(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->CAL, RTC_CAL_YEAR_U_MSK)>>RTC_CAL_YEAR_U_POSS);
}
/**
  * @brief  Set Month Tens Value
  * @param  rtc RTC Instance
  * @param  mon_t Month tens value in RTC timer, in BCD format.
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_cal_mon_t(RTC_TypeDef *rtc, uint32_t mon_t)
{
  MODIFY_REG(rtc->CAL, RTC_CAL_MON_T_MSK, (mon_t<<RTC_CAL_MON_T_POS));
}
/**
  * @brief  Get Month Tens Value
  * @param  rtc RTC Instance
  * @retval Month tens value in RTC timer, in BCD format.
  */
__STATIC_INLINE uint32_t md_rtc_get_cal_mon_t(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->CAL, RTC_CAL_MON_T_MSK)>>RTC_CAL_MON_T_POS);
}
/**
  * @brief  Set Month Units Value
  * @param  rtc RTC Instance
  * @param  mon_u Month units value in RTC timer, in BCD format.
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_cal_mon_u(RTC_TypeDef *rtc, uint32_t mon_u)
{
  MODIFY_REG(rtc->CAL, RTC_CAL_MON_U_MSK, (mon_u<<RTC_CAL_MON_U_POSS));
}
/**
  * @brief  Get Month Units Value
  * @param  rtc RTC Instance
  * @retval Month units value in RTC timer, in BCD format.
  */
__STATIC_INLINE uint32_t md_rtc_get_cal_mon_u(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->CAL, RTC_CAL_MON_U_MSK)>>RTC_CAL_MON_U_POSS);
}
/**
  * @brief  Set Date Tens Value
  * @param  rtc RTC Instance
  * @param  date_t Date tens value in RTC timer, in BCD format.
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_cal_date_t(RTC_TypeDef *rtc, uint32_t date_t)
{
  MODIFY_REG(rtc->CAL, RTC_CAL_DATE_T_MSK, (date_t<<RTC_CAL_DATE_T_POSS));
}
/**
  * @brief  Get Date Tens Value
  * @param  rtc RTC Instance
  * @retval Date tens value in RTC timer, in BCD format.
  */
__STATIC_INLINE uint32_t md_rtc_get_cal_date_t(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->CAL, RTC_CAL_DATE_T_MSK)>>RTC_CAL_DATE_T_POSS);
}
/**
  * @brief  Set Date Units Value
  * @param  rtc RTC Instance
  * @param  date_u Date units value in RTC timer, in BCD format.
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_cal_date_u(RTC_TypeDef *rtc, uint32_t date_u)
{
  MODIFY_REG(rtc->CAL, RTC_CAL_DATE_U_MSK, (date_u<<RTC_CAL_DATE_U_POSS));
}
/**
  * @brief  Get Date Units Value
  * @param  rtc RTC Instance
  * @retval Date units value in RTC timer, in BCD format.
  */
__STATIC_INLINE uint32_t md_rtc_get_cal_date_u(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->CAL, RTC_CAL_DATE_U_MSK)>>RTC_CAL_DATE_U_POSS);
}

/**
  * @brief  Set Alarm Week Value
  * @param  rtc RTC Instance
  * @param  week Alarm Week value in RTC timer, in BCD format.
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_altime_week(RTC_TypeDef *rtc, uint32_t week)
{
  MODIFY_REG(rtc->ALTIME, RTC_ALTIME_WEEK_MSK, (week<<RTC_ALTIME_WEEK_POSS));
}
/**
  * @brief  Get Alarm Week Value
  * @param  rtc RTC Instance
  * @retval Alarm Week value in RTC timer, in BCD format.
  */
__STATIC_INLINE uint32_t md_rtc_get_altime_alweek(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->ALTIME, RTC_ALTIME_WEEK_MSK)>>RTC_ALTIME_WEEK_POSS);
}
/**
  * @brief  Set Alarm Hour Tens Value
  * @param  rtc RTC Instance
  * @param  hour_t Alarm Hour tens value in RTC timer, in BCD format.
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_altime_hour_t(RTC_TypeDef *rtc, uint32_t hour_t)
{
  MODIFY_REG(rtc->ALTIME, RTC_ALTIME_HOUR_T_MSK, (hour_t<<RTC_ALTIME_HOUR_T_POSS));
}
/**
  * @brief  Get Alarm Hour Tens Value
  * @param  rtc RTC Instance
  * @retval Alarm Hour tens value in RTC timer, in BCD format.
  */
__STATIC_INLINE uint32_t md_rtc_get_altime_hour_t(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->ALTIME, RTC_ALTIME_HOUR_T_MSK)>>RTC_ALTIME_HOUR_T_POSS);
}
/**
  * @brief  Set Alarm Hour Units Value
  * @param  rtc RTC Instance
  * @param  hour_u Alarm Hour units value in RTC timer, in BCD format.
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_altime_hour_u(RTC_TypeDef *rtc, uint32_t hour_u)
{
  MODIFY_REG(rtc->ALTIME, RTC_ALTIME_HOUR_U_MSK, (hour_u<<RTC_ALTIME_HOUR_U_POSS));
}
/**
  * @brief  Get Alarm Hour Units Value
  * @param  rtc RTC Instance
  * @retval Alarm Hour units value in RTC timer, in BCD format.
  */
__STATIC_INLINE uint32_t md_rtc_get_altime_hour_u(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->ALTIME, RTC_ALTIME_HOUR_U_MSK)>>RTC_ALTIME_HOUR_U_POSS);
}
/**
  * @brief  Set Alarm Minute Tens Value
  * @param  rtc RTC Instance
  * @param  min_t Alarm Minute tens value in RTC timer, in BCD format.
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_altime_min_t(RTC_TypeDef *rtc, uint32_t min_t)
{
  MODIFY_REG(rtc->ALTIME, RTC_ALTIME_MIN_T_MSK, (min_t<<RTC_ALTIME_MIN_T_POSS));
}
/**
  * @brief  Get Alarm Minute Tens Value
  * @param  rtc RTC Instance
  * @retval Alarm Minute tens value in RTC timer, in BCD format.
  */
__STATIC_INLINE uint32_t md_rtc_get_altime_min_t(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->ALTIME, RTC_ALTIME_MIN_T_MSK)>>RTC_ALTIME_MIN_T_POSS);
}
/**
  * @brief  Set Alarm Minute Units Value
  * @param  rtc RTC Instance
  * @param  min_u Alarm Minute units value in RTC timer, in BCD format.
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_altime_min_u(RTC_TypeDef *rtc, uint32_t min_u)
{
  MODIFY_REG(rtc->ALTIME, RTC_ALTIME_MIN_U_MSK, (min_u<<RTC_ALTIME_MIN_U_POSS));
}
/**
  * @brief  Get Alarm Minute Units Value
  * @param  rtc RTC Instance
  * @retval Alarm Minute units value in RTC timer, in BCD format.
  */
__STATIC_INLINE uint32_t md_rtc_get_altime_min_u(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->ALTIME, RTC_ALTIME_MIN_U_MSK)>>RTC_ALTIME_MIN_U_POSS);
}
/**
  * @brief  Set Alarm Second Tens Value
  * @param  rtc RTC Instance
  * @param  sec_t Alarm Second tens value in RTC timer, in BCD format.
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_altime_sec_t(RTC_TypeDef *rtc, uint32_t sec_t)
{
  MODIFY_REG(rtc->ALTIME, RTC_ALTIME_SEC_T_MSK, (sec_t<<RTC_ALTIME_SEC_T_POSS));
}
/**
  * @brief  Get Alarm Second Tens Value
  * @param  rtc RTC Instance
  * @retval Alarm Second tens value in RTC timer, in BCD format.
  */
__STATIC_INLINE uint32_t md_rtc_get_altime_sec_t(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->ALTIME, RTC_ALTIME_SEC_T_MSK)>>RTC_ALTIME_SEC_T_POSS);
}
/**
  * @brief  Set Alarm Second Units Value
  * @param  rtc RTC Instance
  * @param  sec_u Alarm Second units value in RTC timer, in BCD format.
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_altime_sec_u(RTC_TypeDef *rtc, uint32_t sec_u)
{
  MODIFY_REG(rtc->ALTIME, RTC_ALTIME_SEC_U_MSK, (sec_u<<RTC_ALTIME_SEC_U_POSS));
}
/**
  * @brief  Get Alarm Second Units Value
  * @param  rtc RTC Instance
  * @retval Alarm Second units value in RTC timer, in BCD format.
  */
__STATIC_INLINE uint32_t md_rtc_get_altime_sec_u(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->ALTIME, RTC_ALTIME_SEC_U_MSK)>>RTC_ALTIME_SEC_U_POSS);
}

/**
  * @brief  Set Alarm Year Tens Value
  * @param  rtc RTC Instance
  * @param  year_t Alarm Year tens value in RTC timer, in BCD format.
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_alcal_year_t(RTC_TypeDef *rtc, uint32_t year_t)
{
  MODIFY_REG(rtc->ALCAL, RTC_ALCAL_YEAR_T_MSK, (year_t<<RTC_ALCAL_YEAR_T_POSS));
}
/**
  * @brief  Get Alarm Year Tens Value
  * @param  rtc RTC Instance
  * @retval Alarm Year tens value in RTC timer, in BCD format.
  */
__STATIC_INLINE uint32_t md_rtc_get_alcal_year_t(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->ALCAL, RTC_ALCAL_YEAR_T_MSK)>>RTC_ALCAL_YEAR_T_POSS);
}
/**
  * @brief  Set Alarm Year Units Value
  * @param  rtc RTC Instance
  * @param  year_u Alarm Year units value in RTC timer, in BCD format.
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_alcal_year_u(RTC_TypeDef *rtc, uint32_t year_u)
{
  MODIFY_REG(rtc->ALCAL, RTC_ALCAL_YEAR_U_MSK, (year_u<<RTC_ALCAL_YEAR_U_POSS));
}
/**
  * @brief  Get Alarm Year Units Value
  * @param  rtc RTC Instance
  * @retval Alarm Year units value in RTC timer, in BCD format.
  */
__STATIC_INLINE uint32_t md_rtc_get_alcal_year_u(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->ALCAL, RTC_ALCAL_YEAR_U_MSK)>>RTC_ALCAL_YEAR_U_POSS);
}
/**
  * @brief  Set Alarm Month Tens Value
  * @param  rtc RTC Instance
  * @param  mon_t Alarm Month tens value in RTC timer, in BCD format.
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_alcal_mon_t(RTC_TypeDef *rtc, uint32_t mon_t)
{
  MODIFY_REG(rtc->ALCAL, RTC_ALCAL_MON_T_MSK, (mon_t<<RTC_ALCAL_MON_T_POS));
}
/**
  * @brief  Get Alarm Month Tens Value
  * @param  rtc RTC Instance
  * @retval Alarm Month tens value in RTC timer, in BCD format.
  */
__STATIC_INLINE uint32_t md_rtc_get_alcal_mon_t(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->ALCAL, RTC_ALCAL_MON_T_MSK)>>RTC_ALCAL_MON_T_POS);
}
/**
  * @brief  Set Alarm Month Units Value
  * @param  rtc RTC Instance
  * @param  mon_u Alarm Month units value in RTC timer, in BCD format.
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_alcal_mon_u(RTC_TypeDef *rtc, uint32_t mon_u)
{
  MODIFY_REG(rtc->ALCAL, RTC_ALCAL_MON_U_MSK, (mon_u<<RTC_ALCAL_MON_U_POSS));
}
/**
  * @brief  Get Alarm Month Units Value
  * @param  rtc RTC Instance
  * @retval Alarm Month units value in RTC timer, in BCD format.
  */
__STATIC_INLINE uint32_t md_rtc_get_alcal_mon_u(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->ALCAL, RTC_ALCAL_MON_U_MSK)>>RTC_ALCAL_MON_U_POSS);
}
/**
  * @brief  Set Alarm Date Tens Value
  * @param  rtc RTC Instance
  * @param  date_t Alarm Date tens value in RTC timer, in BCD format.
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_alcal_date_t(RTC_TypeDef *rtc, uint32_t date_t)
{
  MODIFY_REG(rtc->ALCAL, RTC_ALCAL_DATE_T_MSK, (date_t<<RTC_ALCAL_DATE_T_POSS));
}
/**
  * @brief  Get Alarm Date Tens Value
  * @param  rtc RTC Instance
  * @retval Alarm Date tens value in RTC timer, in BCD format.
  */
__STATIC_INLINE uint32_t md_rtc_get_alcal_date_t(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->ALCAL, RTC_ALCAL_DATE_T_MSK)>>RTC_ALCAL_DATE_T_POSS);
}
/**
  * @brief  Set Alarm Date Units Value
  * @param  rtc RTC Instance
  * @param  date_u Alarm Date units value in RTC timer, in BCD format.
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_alcal_date_u(RTC_TypeDef *rtc, uint32_t date_u)
{
  MODIFY_REG(rtc->ALCAL, RTC_ALCAL_DATE_U_MSK, (date_u<<RTC_ALCAL_DATE_U_POSS));
}
/**
  * @brief  Get Alarm Date Units Value
  * @param  rtc RTC Instance
  * @retval Alarm Date units value in RTC timer, in BCD format.
  */
__STATIC_INLINE uint32_t md_rtc_get_alcal_date_u(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->ALCAL, RTC_ALCAL_DATE_U_MSK)>>RTC_ALCAL_DATE_U_POSS);
}

/**
  * @brief  Set Year Alarm Function Enable
  * @param  rtc RTC Instance
  * @param  year can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_alen_year(RTC_TypeDef *rtc, uint32_t year)
{
  MODIFY_REG(rtc->ALEN, RTC_ALEN_YEAR_MSK, (year<<RTC_ALEN_YEAR_POS));
}
/**
  * @brief  Get Year Alarm Function Enable
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_alen_year(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->ALEN, RTC_ALEN_YEAR_MSK)>>RTC_ALEN_YEAR_POS);
}
/**
  * @brief  Set Month Alarm Function Enable
  * @param  rtc RTC Instance
  * @param  month can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_alen_month(RTC_TypeDef *rtc, uint32_t month)
{
  MODIFY_REG(rtc->ALEN, RTC_ALEN_MONTH_MSK, (month<<RTC_ALEN_MONTH_POS));
}
/**
  * @brief  Get Month Alarm Function Enable
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_alen_month(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->ALEN, RTC_ALEN_MONTH_MSK)>>RTC_ALEN_MONTH_POS);
}
/**
  * @brief  Set Date Alarm Function Enable
  * @param  rtc RTC Instance
  * @param  date can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_alen_date(RTC_TypeDef *rtc, uint32_t date)
{
  MODIFY_REG(rtc->ALEN, RTC_ALEN_DATE_MSK, (date<<RTC_ALEN_DATE_POS));
}
/**
  * @brief  Get Date Alarm Function Enable
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_alen_date(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->ALEN, RTC_ALEN_DATE_MSK)>>RTC_ALEN_DATE_POS);
}
/**
  * @brief  Set Week Alarm Function Enable
  * @param  rtc RTC Instance
  * @param  week can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_alen_week(RTC_TypeDef *rtc, uint32_t week)
{
  MODIFY_REG(rtc->ALEN, RTC_ALEN_WEEK_MSK, (week<<RTC_ALEN_WEEK_POS));
}
/**
  * @brief  Get Week Alarm Function Enable
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_alen_week(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->ALEN, RTC_ALEN_WEEK_MSK)>>RTC_ALEN_WEEK_POS);
}
/**
  * @brief  Set Hour Alarm Function Enable
  * @param  rtc RTC Instance
  * @param  hour can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_alen_hour(RTC_TypeDef *rtc, uint32_t hour)
{
  MODIFY_REG(rtc->ALEN, RTC_ALEN_HOUR_MSK, (hour<<RTC_ALEN_HOUR_POS));
}
/**
  * @brief  Get Hour Alarm Function Enable
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_alen_hour(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->ALEN, RTC_ALEN_HOUR_MSK)>>RTC_ALEN_HOUR_POS);
}
/**
  * @brief  Set Minute Alarm Function Enable
  * @param  rtc RTC Instance
  * @param  min can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_alen_min(RTC_TypeDef *rtc, uint32_t min)
{
  MODIFY_REG(rtc->ALEN, RTC_ALEN_MIN_MSK, (min<<RTC_ALEN_MIN_POS));
}
/**
  * @brief  Get Minute Alarm Function Enable
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_alen_min(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->ALEN, RTC_ALEN_MIN_MSK)>>RTC_ALEN_MIN_POS);
}
/**
  * @brief  Set Second Alarm Function Enable
  * @param  rtc RTC Instance
  * @param  sec can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_alen_sec(RTC_TypeDef *rtc, uint32_t sec)
{
  MODIFY_REG(rtc->ALEN, RTC_ALEN_SEC_MSK, (sec<<RTC_ALEN_SEC_POS));
}
/**
  * @brief  Get Second Alarm Function Enable
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_alen_sec(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->ALEN, RTC_ALEN_SEC_MSK)>>RTC_ALEN_SEC_POS);
}

/**
  * @brief  Set RTC Wakeup Counter Match Trigger Enable
  * @param  rtc RTC Instance
  * @param  wktm can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_trig_wktm(RTC_TypeDef *rtc, uint32_t wktm)
{
  MODIFY_REG(rtc->TRIG, RTC_TRIG_WKTM_MSK, (wktm<<RTC_TRIG_WKTM_POS));
}
/**
  * @brief  Get RTC Wakeup Counter Match Trigger Enable
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_trig_wktm(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->TRIG, RTC_TRIG_WKTM_MSK)>>RTC_TRIG_WKTM_POS);
}
/**
  * @brief  Set RTC 1 Hz Trigger Enable
  * @param  rtc RTC Instance
  * @param  f1hz can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_trig_f1hz(RTC_TypeDef *rtc, uint32_t f1hz)
{
  MODIFY_REG(rtc->TRIG, RTC_TRIG_F1HZ_MSK, (f1hz<<RTC_TRIG_F1HZ_POS));
}
/**
  * @brief  Get RTC 1 Hz Trigger Enable
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_trig_f1hz(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->TRIG, RTC_TRIG_F1HZ_MSK)>>RTC_TRIG_F1HZ_POS);
}
/**
  * @brief  Set RTC Year Roll Alarm Trigger Enable
  * @param  rtc RTC Instance
  * @param  ryear can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_trig_ryear(RTC_TypeDef *rtc, uint32_t ryear)
{
  MODIFY_REG(rtc->TRIG, RTC_TRIG_RYEAR_MSK, (ryear<<RTC_TRIG_RYEAR_POS));
}
/**
  * @brief  Get RTC Year Roll Alarm Trigger Enable
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_trig_ryear(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->TRIG, RTC_TRIG_RYEAR_MSK)>>RTC_TRIG_RYEAR_POS);
}
/**
  * @brief  Set RTC Month Roll Alarm Trigger Enable
  * @param  rtc RTC Instance
  * @param  rmon can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_trig_rmon(RTC_TypeDef *rtc, uint32_t rmon)
{
  MODIFY_REG(rtc->TRIG, RTC_TRIG_RMON_MSK, (rmon<<RTC_TRIG_RMON_POS));
}
/**
  * @brief  Get RTC Month Roll Alarm Trigger Enable
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_trig_rmon(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->TRIG, RTC_TRIG_RMON_MSK)>>RTC_TRIG_RMON_POS);
}
/**
  * @brief  Set RTC Date Roll Alarm Trigger Enable
  * @param  rtc RTC Instance
  * @param  rdate can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_trig_rdate(RTC_TypeDef *rtc, uint32_t rdate)
{
  MODIFY_REG(rtc->TRIG, RTC_TRIG_RDATE_MSK, (rdate<<RTC_TRIG_RDATE_POS));
}
/**
  * @brief  Get RTC Date Roll Alarm Trigger Enable
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_trig_rdate(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->TRIG, RTC_TRIG_RDATE_MSK)>>RTC_TRIG_RDATE_POS);
}
/**
  * @brief  Set RTC Week Roll Alarm Trigger Enable
  * @param  rtc RTC Instance
  * @param  rweek can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_trig_rweek(RTC_TypeDef *rtc, uint32_t rweek)
{
  MODIFY_REG(rtc->TRIG, RTC_TRIG_RWEEK_MSK, (rweek<<RTC_TRIG_RWEEK_POS));
}
/**
  * @brief  Get RTC Week Roll Alarm Trigger Enable
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_trig_rweek(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->TRIG, RTC_TRIG_RWEEK_MSK)>>RTC_TRIG_RWEEK_POS);
}
/**
  * @brief  Set RTC Hour Roll Alarm Trigger Enable
  * @param  rtc RTC Instance
  * @param  rhour can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_trig_rhour(RTC_TypeDef *rtc, uint32_t rhour)
{
  MODIFY_REG(rtc->TRIG, RTC_TRIG_RHOUR_MSK, (rhour<<RTC_TRIG_RHOUR_POS));
}
/**
  * @brief  Get RTC Hour Roll Alarm Trigger Enable
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_trig_rhour(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->TRIG, RTC_TRIG_RHOUR_MSK)>>RTC_TRIG_RHOUR_POS);
}
/**
  * @brief  Set RTC Minute Roll Alarm Trigger Enable
  * @param  rtc RTC Instance
  * @param  rmin can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_trig_rmin(RTC_TypeDef *rtc, uint32_t rmin)
{
  MODIFY_REG(rtc->TRIG, RTC_TRIG_RMIN_MSK, (rmin<<RTC_TRIG_RMIN_POS));
}
/**
  * @brief  Get RTC Minute Roll Alarm Trigger Enable
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_trig_rmin(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->TRIG, RTC_TRIG_RMIN_MSK)>>RTC_TRIG_RMIN_POS);
}
/**
  * @brief  Set RTC Second Roll Alarm Trigger Enable
  * @param  rtc RTC Instance
  * @param  rsec can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_trig_rsec(RTC_TypeDef *rtc, uint32_t rsec)
{
  MODIFY_REG(rtc->TRIG, RTC_TRIG_RSEC_MSK, (rsec<<RTC_TRIG_RSEC_POS));
}
/**
  * @brief  Get RTC Second Roll Alarm Trigger Enable
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_trig_rsec(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->TRIG, RTC_TRIG_RSEC_MSK)>>RTC_TRIG_RSEC_POS);
}
/**
  * @brief  Set RTC Match All Alarm Trigger Enable
  * @param  rtc RTC Instance
  * @param  amall can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_trig_amall(RTC_TypeDef *rtc, uint32_t amall)
{
  MODIFY_REG(rtc->TRIG, RTC_TRIG_AMALL_MSK, (amall<<RTC_TRIG_AMALL_POS));
}
/**
  * @brief  Get RTC Match All Alarm Trigger Enable
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_trig_amall(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->TRIG, RTC_TRIG_AMALL_MSK)>>RTC_TRIG_AMALL_POS);
}
/**
  * @brief  Set RTC Match Year Alarm Trigger Enable
  * @param  rtc RTC Instance
  * @param  ayear can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_trig_ayear(RTC_TypeDef *rtc, uint32_t ayear)
{
  MODIFY_REG(rtc->TRIG, RTC_TRIG_AYEAR_MSK, (ayear<<RTC_TRIG_AYEAR_POS));
}
/**
  * @brief  Get RTC Match Year Alarm Trigger Enable
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_trig_ayear(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->TRIG, RTC_TRIG_AYEAR_MSK)>>RTC_TRIG_AYEAR_POS);
}
/**
  * @brief  Set RTC Match Month Alarm Trigger Enable
  * @param  rtc RTC Instance
  * @param  amon can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_trig_amon(RTC_TypeDef *rtc, uint32_t amon)
{
  MODIFY_REG(rtc->TRIG, RTC_TRIG_AMON_MSK, (amon<<RTC_TRIG_AMON_POS));
}
/**
  * @brief  Get RTC Match Month Alarm Trigger Enable
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_trig_amon(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->TRIG, RTC_TRIG_AMON_MSK)>>RTC_TRIG_AMON_POS);
}
/**
  * @brief  Set RTC Match Date Alarm Trigger Enable
  * @param  rtc RTC Instance
  * @param  adate can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_trig_adate(RTC_TypeDef *rtc, uint32_t adate)
{
  MODIFY_REG(rtc->TRIG, RTC_TRIG_ADTAE_MSK, (adate<<RTC_TRIG_ADTAE_POS));
}
/**
  * @brief  Get RTC Match Date Alarm Trigger Enable
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_trig_adate(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->TRIG, RTC_TRIG_ADTAE_MSK)>>RTC_TRIG_ADTAE_POS);
}
/**
  * @brief  Set RTC Match Week Alarm Trigger Enable
  * @param  rtc RTC Instance
  * @param  aweek can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_trig_aweek(RTC_TypeDef *rtc, uint32_t aweek)
{
  MODIFY_REG(rtc->TRIG, RTC_TRIG_AWEEK_MSK, (aweek<<RTC_TRIG_AWEEK_POS));
}
/**
  * @brief  Get RTC Match Week Alarm Trigger Enable
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_trig_aweek(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->TRIG, RTC_TRIG_AWEEK_MSK)>>RTC_TRIG_AWEEK_POS);
}
/**
  * @brief  Set RTC Match Hour Alarm Trigger Enable
  * @param  rtc RTC Instance
  * @param  ahour can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_trig_ahour(RTC_TypeDef *rtc, uint32_t ahour)
{
  MODIFY_REG(rtc->TRIG, RTC_TRIG_AHOUR_MSK, (ahour<<RTC_TRIG_AHOUR_POS));
}
/**
  * @brief  Get RTC Match Hour Alarm Trigger Enable
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_trig_ahour(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->TRIG, RTC_TRIG_AHOUR_MSK)>>RTC_TRIG_AHOUR_POS);
}
/**
  * @brief  Set RTC Match Minute Alarm Trigger Enable
  * @param  rtc RTC Instance
  * @param  amin can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_trig_amin(RTC_TypeDef *rtc, uint32_t amin)
{
  MODIFY_REG(rtc->TRIG, RTC_TRIG_AMIN_MSK, (amin<<RTC_TRIG_AMIN_POS));
}
/**
  * @brief  Get RTC Match Minute Alarm Trigger Enable
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_trig_amin(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->TRIG, RTC_TRIG_AMIN_MSK)>>RTC_TRIG_AMIN_POS);
}
/**
  * @brief  Set RTC Match Second Alarm Trigger Enable
  * @param  rtc RTC Instance
  * @param  asec can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_trig_asec(RTC_TypeDef *rtc, uint32_t asec)
{
  MODIFY_REG(rtc->TRIG, RTC_TRIG_ASEC_MSK, (asec<<RTC_TRIG_ASEC_POS));
}
/**
  * @brief  Get RTC Match Second Alarm Trigger Enable
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_trig_asec(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->TRIG, RTC_TRIG_ASEC_MSK)>>RTC_TRIG_ASEC_POS);
}

/**
  * @brief  Set RTC Wakeup Counter Match Interrupt Enable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_ier_wktm(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IER, RTC_IER_WKTM_MSK);
}
/**
  * @brief  Set RTC 1 Hz Interrupt Enable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_ier_f1hz(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IER, RTC_IER_F1HZ_MSK);
}
/**
  * @brief  Set RTC Year Roll Alarm Interrupt Enable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_ier_ryear(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IER, RTC_IER_RYEAR_MSK);
}
/**
  * @brief  Set RTC Month Roll Alarm Interrupt Enable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_ier_rmon(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IER, RTC_IER_RMON_MSK);
}
/**
  * @brief  Set RTC Date Roll Alarm Interrupt Enable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_ier_rdate(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IER, RTC_IER_RDATE_MSK);
}
/**
  * @brief  Set RTC Week Roll Alarm Interrupt Enable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_ier_rweek(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IER, RTC_IER_RWEEK_MSK);
}
/**
  * @brief  Set RTC Hour Roll Alarm Interrupt Enable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_ier_rhour(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IER, RTC_IER_RHOUR_MSK);
}
/**
  * @brief  Set RTC Minute Roll Alarm Interrupt Enable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_ier_rmin(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IER, RTC_IER_RMIN_MSK);
}
/**
  * @brief  Set RTC Second Roll Alarm Interrupt Enable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_ier_rsec(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IER, RTC_IER_RSEC_MSK);
}
/**
  * @brief  Set RTC Match All Alarm Interrupt Enable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_ier_amall(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IER, RTC_IER_AMALL_MSK);
}
/**
  * @brief  Set RTC Match Year Alarm Interrupt Enable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_ier_ayear(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IER, RTC_IER_AYEAR_MSK);
}
/**
  * @brief  Set RTC Match Month Alarm Interrupt Enable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_ier_amon(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IER, RTC_IER_AMON_MSK);
}
/**
  * @brief  Set RTC Match Date Alarm Interrupt Enable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_ier_adate(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IER, RTC_IER_ADTAE_MSK);
}
/**
  * @brief  Set RTC Match Week Alarm Interrupt Enable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_ier_aweek(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IER, RTC_IER_AWEEK_MSK);
}
/**
  * @brief  Set RTC Match Hour Alarm Interrupt Enable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_ier_ahour(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IER, RTC_IER_AHOUR_MSK);
}
/**
  * @brief  Set RTC Match Minute Alarm Interrupt Enable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_ier_amin(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IER, RTC_IER_AMIN_MSK);
}
/**
  * @brief  Set RTC Match Second Alarm Interrupt Enable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_ier_asec(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IER, RTC_IER_ASEC_MSK);
}

/**
  * @brief  Set RTC Wakeup Counter Match Interrupt Disable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_idr_wktm(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IDR, RTC_IDR_WKTM_MSK);
}
/**
  * @brief  Set RTC 1 Hz Interrupt Disable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_idr_f1hz(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IDR, RTC_IDR_F1HZ_MSK);
}
/**
  * @brief  Set RTC Year Roll Alarm Interrupt Disable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_idr_ryear(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IDR, RTC_IDR_RYEAR_MSK);
}
/**
  * @brief  Set RTC Month Roll Alarm Interrupt Disable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_idr_rmon(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IDR, RTC_IDR_RMON_MSK);
}
/**
  * @brief  Set RTC Date Roll Alarm Interrupt Disable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_idr_rdate(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IDR, RTC_IDR_RDATE_MSK);
}
/**
  * @brief  Set RTC Week Roll Alarm Interrupt Disable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_idr_rweek(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IDR, RTC_IDR_RWEEK_MSK);
}
/**
  * @brief  Set RTC Hour Roll Alarm Interrupt Disable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_idr_rhour(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IDR, RTC_IDR_RHOUR_MSK);
}
/**
  * @brief  Set RTC Minute Roll Alarm Interrupt Disable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_idr_rmin(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IDR, RTC_IDR_RMIN_MSK);
}
/**
  * @brief  Set RTC Second Roll Alarm Interrupt Disable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_idr_rsec(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IDR, RTC_IDR_RSEC_MSK);
}
/**
  * @brief  Set RTC Match All Alarm Interrupt Disable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_idr_amall(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IDR, RTC_IDR_AMALL_MSK);
}
/**
  * @brief  Set RTC Match Year Alarm Interrupt Disable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_idr_ayear(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IDR, RTC_IDR_AYEAR_MSK);
}
/**
  * @brief  Set RTC Match Month Alarm Interrupt Disable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_idr_amon(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IDR, RTC_IDR_AMON_MSK);
}
/**
  * @brief  Set RTC Match Date Alarm Interrupt Disable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_idr_adate(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IDR, RTC_IDR_ADTAE_MSK);
}
/**
  * @brief  Set RTC Match Week Alarm Interrupt Disable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_idr_aweek(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IDR, RTC_IDR_AWEEK_MSK);
}
/**
  * @brief  Set RTC Match Hour Alarm Interrupt Disable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_idr_ahour(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IDR, RTC_IDR_AHOUR_MSK);
}
/**
  * @brief  Set RTC Match Minute Alarm Interrupt Disable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_idr_amin(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IDR, RTC_IDR_AMIN_MSK);
}
/**
  * @brief  Set RTC Match Second Alarm Interrupt Disable bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_idr_asec(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->IDR, RTC_IDR_ASEC_MSK);
}

/**
  * @brief  Get RTC Wakeup Counter Match Interrupt Valid Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ivs_wktm(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IVS, RTC_IVS_WKTM_MSK)>>RTC_IVS_WKTM_POS);
}
/**
  * @brief  Get RTC 1 Hz Interrupt Valid Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ivs_f1hz(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IVS, RTC_IVS_F1HZ_MSK)>>RTC_IVS_F1HZ_POS);
}
/**
  * @brief  Get RTC Year Roll Alarm Interrupt Valid Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ivs_ryear(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IVS, RTC_IVS_RYEAR_MSK)>>RTC_IVS_RYEAR_POS);
}
/**
  * @brief  Get RTC Month Roll Alarm Interrupt Valid Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ivs_rmon(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IVS, RTC_IVS_RMON_MSK)>>RTC_IVS_RMON_POS);
}
/**
  * @brief  Get RTC Date Roll Alarm Interrupt Valid Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ivs_rdate(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IVS, RTC_IVS_RDATE_MSK)>>RTC_IVS_RDATE_POS);
}
/**
  * @brief  Get RTC Week Roll Alarm Interrupt Valid Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ivs_rweek(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IVS, RTC_IVS_RWEEK_MSK)>>RTC_IVS_RWEEK_POS);
}
/**
  * @brief  Get RTC Hour Roll Alarm Interrupt Valid Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ivs_rhour(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IVS, RTC_IVS_RHOUR_MSK)>>RTC_IVS_RHOUR_POS);
}
/**
  * @brief  Get RTC Minute Roll Alarm Interrupt Valid Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ivs_rmin(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IVS, RTC_IVS_RMIN_MSK)>>RTC_IVS_RMIN_POS);
}
/**
  * @brief  Get RTC Second Roll Alarm Interrupt Valid Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ivs_rsec(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IVS, RTC_IVS_RSEC_MSK)>>RTC_IVS_RSEC_POS);
}
/**
  * @brief  Get RTC Match All Alarm Interrupt Valid Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ivs_amall(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IVS, RTC_IVS_AMALL_MSK)>>RTC_IVS_AMALL_POS);
}
/**
  * @brief  Get RTC Match Year Alarm Interrupt Valid Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ivs_ayear(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IVS, RTC_IVS_AYEAR_MSK)>>RTC_IVS_AYEAR_POS);
}
/**
  * @brief  Get RTC Match Month Alarm Interrupt Valid Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ivs_amon(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IVS, RTC_IVS_AMON_MSK)>>RTC_IVS_AMON_POS);
}
/**
  * @brief  Get RTC Match Date Alarm Interrupt Valid Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ivs_adate(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IVS, RTC_IVS_ADTAE_MSK)>>RTC_IVS_ADTAE_POS);
}
/**
  * @brief  Get RTC Match Week Alarm Interrupt Valid Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ivs_aweek(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IVS, RTC_IVS_AWEEK_MSK)>>RTC_IVS_AWEEK_POS);
}
/**
  * @brief  Get RTC Match Hour Alarm Interrupt Valid Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ivs_ahour(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IVS, RTC_IVS_AHOUR_MSK)>>RTC_IVS_AHOUR_POS);
}
/**
  * @brief  Get RTC Match Minute Alarm Interrupt Valid Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ivs_amin(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IVS, RTC_IVS_AMIN_MSK)>>RTC_IVS_AMIN_POS);
}
/**
  * @brief  Get RTC Match Second Alarm Interrupt Valid Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ivs_asec(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IVS, RTC_IVS_ASEC_MSK)>>RTC_IVS_ASEC_POS);
}

/**
  * @brief  Get RTC Wakeup Counter Match Raw Interrupt Flag Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_rif_wktm(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->RIF, RTC_RIF_WKTM_MSK)>>RTC_RIF_WKTM_POS);
}
/**
  * @brief  Get RTC 1 Hz Raw Interrupt Flag Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_rif_f1hz(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->RIF, RTC_RIF_F1HZ_MSK)>>RTC_RIF_F1HZ_POS);
}
/**
  * @brief  Get RTC Year Roll Alarm Raw Interrupt Flag Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_rif_ryear(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->RIF, RTC_RIF_RYEAR_MSK)>>RTC_RIF_RYEAR_POS);
}
/**
  * @brief  Get RTC Month Roll Alarm Raw Interrupt Flag Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_rif_rmon(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->RIF, RTC_RIF_RMON_MSK)>>RTC_RIF_RMON_POS);
}
/**
  * @brief  Get RTC Date Roll Alarm Raw Interrupt Flag Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_rif_rdate(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->RIF, RTC_RIF_RDATE_MSK)>>RTC_RIF_RDATE_POS);
}
/**
  * @brief  Get RTC Week Roll Alarm Raw Interrupt Flag Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_rif_rweek(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->RIF, RTC_RIF_RWEEK_MSK)>>RTC_RIF_RWEEK_POS);
}
/**
  * @brief  Get RTC Hour Roll Alarm Raw Interrupt Flag Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_rif_rhour(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->RIF, RTC_RIF_RHOUR_MSK)>>RTC_RIF_RHOUR_POS);
}
/**
  * @brief  Get RTC Minute Roll Alarm Raw Interrupt Flag Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_rif_rmin(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->RIF, RTC_RIF_RMIN_MSK)>>RTC_RIF_RMIN_POS);
}
/**
  * @brief  Get RTC Second Roll Alarm Raw Interrupt Flag Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_rif_rsec(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->RIF, RTC_RIF_RSEC_MSK)>>RTC_RIF_RSEC_POS);
}
/**
  * @brief  Get RTC Match All Alarm Raw Interrupt Flag Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_rif_amall(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->RIF, RTC_RIF_AMALL_MSK)>>RTC_RIF_AMALL_POS);
}
/**
  * @brief  Get RTC Match Year Alarm Raw Interrupt Flag Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_rif_ayear(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->RIF, RTC_RIF_AYEAR_MSK)>>RTC_RIF_AYEAR_POS);
}
/**
  * @brief  Get RTC Match Month Alarm Raw Interrupt Flag Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_rif_amon(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->RIF, RTC_RIF_AMON_MSK)>>RTC_RIF_AMON_POS);
}
/**
  * @brief  Get RTC Match Date Alarm Raw Interrupt Flag Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_rif_adate(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->RIF, RTC_RIF_ADTAE_MSK)>>RTC_RIF_ADTAE_POS);
}
/**
  * @brief  Get RTC Match Week Alarm Raw Interrupt Flag Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_rif_aweek(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->RIF, RTC_RIF_AWEEK_MSK)>>RTC_RIF_AWEEK_POS);
}
/**
  * @brief  Get RTC Match Hour Alarm Raw Interrupt Flag Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_rif_ahour(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->RIF, RTC_RIF_AHOUR_MSK)>>RTC_RIF_AHOUR_POS);
}
/**
  * @brief  Get RTC Match Minute Alarm Raw Interrupt Flag Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_rif_amin(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->RIF, RTC_RIF_AMIN_MSK)>>RTC_RIF_AMIN_POS);
}
/**
  * @brief  Get RTC Match Second Alarm Raw Interrupt Flag Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_rif_asec(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->RIF, RTC_RIF_ASEC_MSK)>>RTC_RIF_ASEC_POS);
}

/**
  * @brief  Get RTC Wakeup Counter Match Interrupt Flag Masked Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ifm_wktm(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IFM, RTC_IFM_WKTM_MSK)>>RTC_IFM_WKTM_POS);
}
/**
  * @brief  Get RTC 1 Hz Interrupt Flag Masked Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ifm_f1hz(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IFM, RTC_IFM_F1HZ_MSK)>>RTC_IFM_F1HZ_POS);
}
/**
  * @brief  Get RTC Year Roll Alarm Interrupt Flag Masked Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ifm_ryear(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IFM, RTC_IFM_RYEAR_MSK)>>RTC_IFM_RYEAR_POS);
}
/**
  * @brief  Get RTC Month Roll Alarm Interrupt Flag Masked Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ifm_rmon(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IFM, RTC_IFM_RMON_MSK)>>RTC_IFM_RMON_POS);
}
/**
  * @brief  Get RTC Date Roll Alarm Interrupt Flag Masked Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ifm_rdate(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IFM, RTC_IFM_RDATE_MSK)>>RTC_IFM_RDATE_POS);
}
/**
  * @brief  Get RTC Week Roll Alarm Interrupt Flag Masked Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ifm_rweek(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IFM, RTC_IFM_RWEEK_MSK)>>RTC_IFM_RWEEK_POS);
}
/**
  * @brief  Get RTC Hour Roll Alarm Interrupt Flag Masked Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ifm_rhour(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IFM, RTC_IFM_RHOUR_MSK)>>RTC_IFM_RHOUR_POS);
}
/**
  * @brief  Get RTC Minute Roll Alarm Interrupt Flag Masked Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ifm_rmin(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IFM, RTC_IFM_RMIN_MSK)>>RTC_IFM_RMIN_POS);
}
/**
  * @brief  Get RTC Second Roll Alarm Interrupt Flag Masked Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ifm_rsec(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IFM, RTC_IFM_RSEC_MSK)>>RTC_IFM_RSEC_POS);
}
/**
  * @brief  Get RTC Match All Alarm Interrupt Flag Masked Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ifm_amall(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IFM, RTC_IFM_AMALL_MSK)>>RTC_IFM_AMALL_POS);
}
/**
  * @brief  Get RTC Match Year Alarm Interrupt Flag Masked Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ifm_ayear(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IFM, RTC_IFM_AYEAR_MSK)>>RTC_IFM_AYEAR_POS);
}
/**
  * @brief  Get RTC Match Month Alarm Interrupt Flag Masked Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ifm_amon(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IFM, RTC_IFM_AMON_MSK)>>RTC_IFM_AMON_POS);
}
/**
  * @brief  Get RTC Match Date Alarm Interrupt Flag Masked Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ifm_adate(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IFM, RTC_IFM_ADTAE_MSK)>>RTC_IFM_ADTAE_POS);
}
/**
  * @brief  Get RTC Match Week Alarm Interrupt Flag Masked Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ifm_aweek(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IFM, RTC_IFM_AWEEK_MSK)>>RTC_IFM_AWEEK_POS);
}
/**
  * @brief  Get RTC Match Hour Alarm Interrupt Flag Masked Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ifm_ahour(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IFM, RTC_IFM_AHOUR_MSK)>>RTC_IFM_AHOUR_POS);
}
/**
  * @brief  Get RTC Match Minute Alarm Interrupt Flag Masked Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ifm_amin(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IFM, RTC_IFM_AMIN_MSK)>>RTC_IFM_AMIN_POS);
}
/**
  * @brief  Get RTC Match Second Alarm Interrupt Flag Masked Status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_get_ifm_asec(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->IFM, RTC_IFM_ASEC_MSK)>>RTC_IFM_ASEC_POS);
}

/**
  * @brief  Set RTC Wakeup Counter Match Interrupt Clear bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_icr_wktm(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->ICR, RTC_ICR_WKTM_MSK);
}
/**
  * @brief  Set RTC 1 Hz Interrupt Clear bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_icr_f1hz(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->ICR, RTC_ICR_F1HZ_MSK);
}
/**
  * @brief  Set RTC Year Roll Alarm Interrupt Clear bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_icr_ryear(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->ICR, RTC_ICR_RYEAR_MSK);
}
/**
  * @brief  Set RTC Month Roll Alarm Interrupt Clear bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_icr_rmon(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->ICR, RTC_ICR_RMON_MSK);
}
/**
  * @brief  Set RTC Date Roll Alarm Interrupt Clear bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_icr_rdate(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->ICR, RTC_ICR_RDATE_MSK);
}
/**
  * @brief  Set RTC Week Roll Alarm Interrupt Clear bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_icr_rweek(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->ICR, RTC_ICR_RWEEK_MSK);
}
/**
  * @brief  Set RTC Hour Roll Alarm Interrupt Clear bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_icr_rhour(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->ICR, RTC_ICR_RHOUR_MSK);
}
/**
  * @brief  Set RTC Minute Roll Alarm Interrupt Clear bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_icr_rmin(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->ICR, RTC_ICR_RMIN_MSK);
}
/**
  * @brief  Set RTC Second Roll Alarm Interrupt Clear bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_icr_rsec(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->ICR, RTC_ICR_RSEC_MSK);
}
/**
  * @brief  Set RTC Match All Alarm Interrupt Clear bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_icr_amall(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->ICR, RTC_ICR_AMALL_MSK);
}
/**
  * @brief  Set RTC Match Year Alarm Interrupt Clear bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_icr_ayear(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->ICR, RTC_ICR_AYEAR_MSK);
}
/**
  * @brief  Set RTC Match Month Alarm Interrupt Clear bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_icr_amon(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->ICR, RTC_ICR_AMON_MSK);
}
/**
  * @brief  Set RTC Match Date Alarm Interrupt Clear bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_icr_adate(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->ICR, RTC_ICR_ADTAE_MSK);
}
/**
  * @brief  Set RTC Match Week Alarm Interrupt Clear bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_icr_aweek(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->ICR, RTC_ICR_AWEEK_MSK);
}
/**
  * @brief  Set RTC Match Hour Alarm Interrupt Clear bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_icr_ahour(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->ICR, RTC_ICR_AHOUR_MSK);
}
/**
  * @brief  Set RTC Match Minute Alarm Interrupt Clear bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_icr_amin(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->ICR, RTC_ICR_AMIN_MSK);
}
/**
  * @brief  Set RTC Match Second Alarm Interrupt Clear bit
  * @param  rtc RTC Instance
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_icr_asec(RTC_TypeDef *rtc)
{
  SET_BIT(rtc->ICR, RTC_ICR_ASEC_MSK);
}

/**
  * @brief  Get RTC Calendar Synchronization status bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_RTC_STAT_SYNDONE_UNDER
  *         @arg @ref MD_RTC_STAT_SYNDONE_CMP
  */
__STATIC_INLINE uint32_t md_rtc_get_stat_syndone(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->STAT, RTC_STAT_SYNDONE_MSK)>>RTC_STAT_SYNDONE_POS);
}
/**
  * @brief  Get RTC Calendar Status bit
  * @param  rtc RTC Instance
  * @retval State of bit (1 or 0).
  * @note   0 = RTC calendar is not empty
  *         1 = RTC calendar is empty
  */
__STATIC_INLINE uint32_t md_rtc_get_stat_empty(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->STAT, RTC_STAT_EMPTY_MSK)>>RTC_STAT_EMPTY_POS);
}

/**
  * @brief  Set Read RTC Backup Register Enable bit
  * @param  rtc RTC Instance
  * @param  bken can be one of the following values:
  *         @arg @ref MD_RTC_BKEN_BKEN_CONTROL
  *         @arg @ref MD_RTC_BKEN_BKEN_BACKUP
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_bken_bken(RTC_TypeDef *rtc, uint32_t bken)
{
  MODIFY_REG(rtc->BKEN, RTC_BKEN_BKEN_MSK, (bken<<RTC_BKEN_BKEN_POS));
}
/**
  * @brief  Get Read RTC Backup Register Enable bit
  * @param  rtc RTC Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_RTC_BKEN_BKEN_CONTROL
  *         @arg @ref MD_RTC_BKEN_BKEN_BACKUP
  */
__STATIC_INLINE uint32_t md_rtc_get_bken_bken(RTC_TypeDef *rtc)
{
  return (READ_BIT(rtc->BKEN, RTC_BKEN_BKEN_MSK)>>RTC_BKEN_BKEN_POS);
}

/**
  * @} MD_RTC_Public_Macros
  */

/* Public functions -----------------------------------------------------------*/
/** @defgroup MD_RTC_Public_Functions RTC Public Functions
  * @{
  */

/** @defgroup MD_RTC_PF_Basic_Configuration Basic Configuration
  * @{
  */

/**
  * @} MD_RTC_PF_Basic_Configuration
  */

/** @defgroup MD_RTC_PF_Data_Access Data Access
  * @{
  */

/**
  * @} MD_RTC_PF_Data_Access
  */

/** @defgroup MD_RTC_PF_Init Initialization and de-initialization functions
  * @{
  */

/**
  * @} MD_RTC_PF_Init
  */

/**
  * @} MD_RTC_Public_Functions
  */

#endif

/**
  * @} RTC
  */

/**
  * @} Micro_Driver
  */


#ifdef __cplusplus
}

#endif

#endif

/******************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
