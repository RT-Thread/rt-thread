/**
  ******************************************************************************
  * @file    md_tick.c
  * @brief   ES32F0271 TICK Source File.
   *
 * @version V1.00.01
  * @date    day/mon/year
  * @author  Eastsoft AE Team
  * @note
  * detailed description
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *
  *******************************************************************************
  */

/* Includes -------------------------------------------------------------------*/
#include "md_rcu.h"
#include "md_tick.h"

/** @addtogroup Micro_Driver
  * @{
  */

#if defined (TICK)

/** @addtogroup TICK TICK
  * @brief TICK micro driver
  * @{
  */

/* Private types --------------------------------------------------------------*/
/* Private constants ----------------------------------------------------------*/
/* Private macros -------------------------------------------------------------*/

/* Private function prototypes ------------------------------------------------*/

#define  HDIVON  0

/* Private variables ----------------------------------------------------------*/
/** @defgroup MD_TICK_Private_Variables TICK Private Variables
  * @{
  */
static  uint32_t  TICKms;
static  uint32_t  TICK100us;
static  uint32_t  TICK10us;

/**
  * @} MD_TICK_Private_Variables
  */
/* Public functions -----------------------------------------------------------*/
/** @defgroup MD_TICK_Public_Functions TICK Public Functions
  * @{
  */

/**
  * @brief  Tick Initialization
  * @note  This function set the maximun load and enable TICK counter
  * @note  This function also calculate ms, 100us ans 10us counter
  * @param  None
  * @retval  None
  */
void  md_tick_init(void)
{
#if  HDIVON
  HDIV->DIVIDEND = SystemFrequency_SysClk;
  HDIV->DIVISOR = 1000;
  TICKms = HDIV->QUOTIENT;
  HDIV->DIVISOR = 10000;
  TICK100us = HDIV->QUOTIENT;
  HDIV->DIVISOR = 100000;
  TICK10us = HDIV->QUOTIENT;
#else
  TICKms = SystemFrequency_SysClk / 1000;
  TICK100us = SystemFrequency_SysClk / 10000;
  TICK10us = SystemFrequency_SysClk / 100000;
#endif

  md_tick_set_rvr_reload((1 << 24) - 1); /*  Maximun ReLoad  */
  md_tick_set_cvr_current(0);        /*  Reset CVR  */
  md_tick_set_csr_clksource(1);      /*  MCU Clock  */
  md_tick_enable_csr_enable();      /*  Counter Enable  */
}

/**
  * @brief  Retrive the TICK counter and converted to millisecond
  * @param  None
  * @retval  The ms value converted by TICK counter
  */
uint32_t  md_tick_get_mscnt(void)
{
#if  HDIVON
  HDIV->DIVIDEND = md_tick_get_cvr_current();
  HDIV->DIVISOR = TICKms;
  return (HDIV->QUOTIENT);
#else
  return (md_tick_get_cvr_current() / TICKms);
#endif
}

/**
  * @brief  Retrive the TICK counter and converted to 100 microseconds
  * @param  None
  * @retval  The 100 microseconds value converted by TICK counter
  */
uint32_t  md_tick_get_100uscnt(void)
{
#if  HDIVON
  HDIV->DIVIDEND = md_tick_get_cvr_current();
  HDIV->DIVISOR = TICK100us;
  return (HDIV->QUOTIENT);
#else
  return (md_tick_get_cvr_current() / TICK100us);
#endif
}

/**
  * @brief  Retrive the TICK counter and converted to 10 microseconds
  * @param  None
  * @retval  The 10 microseconds value converted by TICK counter
  */
uint32_t  md_tick_get_10uscnt(void)
{
#if  HDIVON
  HDIV->DIVIDEND = md_tick_get_cvr_current();
  HDIV->DIVISOR = TICK10us;
  return (HDIV->QUOTIENT);
#else
  return (md_tick_get_cvr_current() / TICK10us);
#endif
}

/**
  * @brief  Delay based on milliseconds
  * @param  Unit The number of ms in one delay period
  * @param  msCnt The counter of delay period
  * @etVal  None
  */
void  md_tick_waitms(uint8_t Unit, uint16_t msCnt)
{
  uint32_t  mstime;

  mstime = (1 << 24) - (Unit * TICKms);

  while (msCnt--)
  {
    md_tick_set_cvr_current((1 << 24) - 1); /*  Reset CVR  */

    while (md_tick_get_cvr_current() > mstime);
  }
}

/**
  * @brief  Delay based on 100 microseconds
  * @param  Unit The number of 100 microseconds in one delay period
  * @param  msCnt The counter of delay period
  * @etVal  None
  */
void  md_tick_wait100us(uint16_t Unit, uint16_t usCnt)
{
  uint32_t  ustime;

  ustime = (1 << 24) - (Unit * TICK100us);

  while (usCnt--)
  {
    md_tick_set_cvr_current((1 << 24) - 1); /*  Reset CVR  */

    while (md_tick_get_cvr_current() > ustime);
  }
}

/**
  * @brief  Delay based on 10 microseconds
  * @param  Unit The number of 10 microseconds in one delay period
  * @param  msCnt The counter of delay period
  * @etVal  None
  */
void  md_tick_wait10us(uint16_t Unit, uint16_t usCnt)
{
  uint32_t  ustime;

  ustime = (1 << 24) - (Unit * TICK10us);

  while (usCnt--)
  {
    md_tick_set_cvr_current((1 << 24) - 1); /*  Reset CVR  */

    while (md_tick_get_cvr_current() > ustime);
  }
}


/**
  * @} MD_TICK_Public_Functions
  */

/**
  * @} TICK
  */
#endif

/**
  * @} Micro_Driver
  */

/******************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
