/*
 * Copyright (c) 2006-2020, YICHIP Development Team
 * @file     yc_wdt.c
 * @brief    This file provides all the WDT firmware functions.
 *
 * Change Logs:
 * Date           Author             Version        Notes
 * 2021-01-04     yangzhengfeng      V1.0.0         the first version
 */
#include "yc_wdt.h"

/**
 * @brief  Set WDT Clk Div
 * @param  Wdtclkdiv: Wdtclkdiv value equal 1 to 16
 * @retval none
 */
void WDT_CLKDIV(uint32_t Wdtclkdiv)
{
    _ASSERT(IS_WDT_CLKDI(Wdtclkdiv));

    MWDT->CONFIG.bit.CLK_DIV = Wdtclkdiv;
}

/**
 * @brief  Set reload counter
 * @param  Reload: Reload counter equal to 2 to 31
 * @retval none
 */
void WDT_SetReload(uint32_t Reload)
{
    _ASSERT(IS_WDT_RELOAD(Reload));

    MWDT->CONFIG.bit.RELOAD = Reload;
}

/**
 * @brief  Feed the watchdog function
 * @param  none
 * @retval none
 */
void WDT_ReloadCounter(void)
{
    MWDT->KICK.reg = COUNTER_RELOAD_KEY;
}

/**
 * @brief  Enable WDT
 * @param  none
 * @retval none
 */
void WDT_Enable(void)
{
    MWDT->CONFIG.bit.EN = ENABLE;
}

/**
 * @brief Set WDT  mode
 * @param WDT_Mode : Select the following values :
 *        WDT_CPUReset
 *        WDT_Interrupt.
 * @retval none
 * @description If Select WDT_CPUReset Mode,the bit for WDT RESET will be set;if
 *              Select WDT_Interrupt the bit for WDT RESET will
 */
void WDT_ModeConfig(WDT_ModeTypeDef WDT_Mode)
{
    _ASSERT(IS_WDT_MODE(WDT_Mode));

    if(WDT_CPUReset == WDT_Mode)
    {
        MWDT->CONFIG.bit.MODE = WDT_CPUReset;
        MRSTGEN->RST_EN.bit.WDT = ENABLE;
    }
    else if(WDT_Interrupt == WDT_Mode)
    {
        MWDT->CONFIG.bit.MODE = WDT_Interrupt;
        MRSTGEN->RST_EN.bit.WDT = DISABLE;
    }
}

/**
 * @brief  Get interrupt Status
 * @param  none
 * @retval SET:interrupt ocuured.
 */
uint8_t WDT_GetITStatus(void)
{
    uint16_t ret;

    ret = MWDT->IRQ_STATUS.bit.STATE;

    return ret ;
}

/**
 * @brief  Clear interrupt
 * @param  none
 * @retval none
 */
void WDT_ClearITPendingBit(void)
{
    MWDT->CLEAR.reg = 1;
}

/************************ (C) COPYRIGHT Yichip Microelectronics *****END OF FILE****/
