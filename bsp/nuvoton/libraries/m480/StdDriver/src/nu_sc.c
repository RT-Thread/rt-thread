/**************************************************************************//**
 * @file     sc.c
 * @version  V3.00
 * @brief    M480 Smartcard(SC) driver source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include "NuMicro.h"

/* Below are variables used locally by SC driver and does not want to parse by doxygen unless HIDDEN_SYMBOLS is defined */
/** @cond HIDDEN_SYMBOLS */
static uint32_t u32CardStateIgnore[SC_INTERFACE_NUM] = {0UL, 0UL, 0UL};

/** @endcond HIDDEN_SYMBOLS */

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup SC_Driver SC Driver
  @{
*/

/** @addtogroup SC_EXPORTED_FUNCTIONS SC Exported Functions
  @{
*/

/**
  * @brief This function indicates specified smartcard slot status
  * @param[in] sc Base address of smartcard module
  * @return Card insert status
  * @retval TRUE Card insert
  * @retval FALSE Card remove
  */
uint32_t SC_IsCardInserted(SC_T *sc)
{
    uint32_t ret;
    /* put conditions into two variable to remove IAR compilation warning */
    uint32_t cond1 = ((sc->STATUS & SC_STATUS_CDPINSTS_Msk) >> SC_STATUS_CDPINSTS_Pos);
    uint32_t cond2 = ((sc->CTL & SC_CTL_CDLV_Msk) >> SC_CTL_CDLV_Pos);

    if((sc == SC0) && (u32CardStateIgnore[0] == 1UL))
    {
        ret = (uint32_t)TRUE;
    }
    else if((sc == SC1) && (u32CardStateIgnore[1] == 1UL))
    {
        ret = (uint32_t)TRUE;
    }
    else if((sc == SC2) && (u32CardStateIgnore[2] == 1UL))
    {
        ret = (uint32_t)TRUE;
    }
    else if(cond1 != cond2)
    {
        ret = (uint32_t)FALSE;
    }
    else
    {
        ret = (uint32_t)TRUE;
    }
    return ret;
}

/**
  * @brief This function reset both transmit and receive FIFO of specified smartcard module
  * @param[in] sc Base address of smartcard module
  * @return None
  */
void SC_ClearFIFO(SC_T *sc)
{
    while(sc->ALTCTL & SC_ALTCTL_SYNC_Msk)
    {
        ;
    }
    sc->ALTCTL |= (SC_ALTCTL_TXRST_Msk | SC_ALTCTL_RXRST_Msk);
}

/**
  * @brief This function disable specified smartcard module
  * @param[in] sc Base address of smartcard module
  * @return None
  */
void SC_Close(SC_T *sc)
{
    sc->INTEN = 0UL;
    while(sc->PINCTL & SC_PINCTL_SYNC_Msk)
    {
        ;
    }
    sc->PINCTL = 0UL;
    sc->ALTCTL = 0UL;
    while(sc->CTL & SC_CTL_SYNC_Msk)
    {
        ;
    }
    sc->CTL = 0UL;
}

/**
  * @brief This function initialized smartcard module
  * @param[in] sc Base address of smartcard module
  * @param[in] u32CardDet Card detect polarity, select the CD pin state which indicates card absent. Could be
  *                 -\ref SC_PIN_STATE_HIGH
  *                 -\ref SC_PIN_STATE_LOW
  *                 -\ref SC_PIN_STATE_IGNORE, no card detect pin, always assumes card present
  * @param[in] u32PWR Power on polarity, select the PWR pin state which could set smartcard VCC to high level. Could be
  *                 -\ref SC_PIN_STATE_HIGH
  *                 -\ref SC_PIN_STATE_LOW
  * @return None
  */
void SC_Open(SC_T *sc, uint32_t u32CardDet, uint32_t u32PWR)
{
    uint32_t u32Reg = 0UL, u32Intf;

    if(sc == SC0)
    {
        u32Intf = 0UL;
    }
    else if(sc == SC1)
    {
        u32Intf = 1UL;
    }
    else
    {
        u32Intf = 2UL;
    }

    if(u32CardDet != SC_PIN_STATE_IGNORE)
    {
        u32Reg = u32CardDet ? 0UL: SC_CTL_CDLV_Msk;
        u32CardStateIgnore[u32Intf] = 0UL;
    }
    else
    {
        u32CardStateIgnore[u32Intf] = 1UL;
    }
    sc->PINCTL = u32PWR ? 0UL : SC_PINCTL_PWRINV_Msk;
    while(sc->CTL & SC_CTL_SYNC_Msk)
    {
        ;
    }
    sc->CTL = SC_CTL_SCEN_Msk | SC_CTL_TMRSEL_Msk | u32Reg;
}

/**
  * @brief This function reset specified smartcard module to its default state for activate smartcard
  * @param[in] sc Base address of smartcard module
  * @return None
  */
void SC_ResetReader(SC_T *sc)
{
    uint32_t u32Intf;

    if(sc == SC0)
    {
        u32Intf = 0UL;
    }
    else if(sc == SC1)
    {
        u32Intf = 1UL;
    }
    else
    {
        u32Intf = 2UL;
    }

    /* Reset FIFO, enable auto de-activation while card removal */
    sc->ALTCTL |= (SC_ALTCTL_TXRST_Msk | SC_ALTCTL_RXRST_Msk | SC_ALTCTL_ADACEN_Msk);
    /* Set Rx trigger level to 1 character, longest card detect debounce period, disable error retry (EMV ATR does not use error retry) */
    while(sc->CTL & SC_CTL_SYNC_Msk)
    {
        ;
    }
    sc->CTL &= ~(SC_CTL_RXTRGLV_Msk |
                 SC_CTL_CDDBSEL_Msk |
                 SC_CTL_TXRTY_Msk |
                 SC_CTL_TXRTYEN_Msk |
                 SC_CTL_RXRTY_Msk |
                 SC_CTL_RXRTYEN_Msk);
    while(sc->CTL & SC_CTL_SYNC_Msk)
    {
        ;
    }
    /* Enable auto convention, and all three smartcard internal timers */
    sc->CTL |= SC_CTL_AUTOCEN_Msk | SC_CTL_TMRSEL_Msk;
    /* Disable Rx timeout */
    sc->RXTOUT = 0UL;
    /* 372 clocks per ETU by default */
    sc->ETUCTL= 371UL;


    /* Enable necessary interrupt for smartcard operation */
    if(u32CardStateIgnore[u32Intf])  /* Do not enable card detect interrupt if card present state ignore */
    {
        sc->INTEN = (SC_INTEN_RDAIEN_Msk |
                     SC_INTEN_TERRIEN_Msk |
                     SC_INTEN_TMR0IEN_Msk |
                     SC_INTEN_TMR1IEN_Msk |
                     SC_INTEN_TMR2IEN_Msk |
                     SC_INTEN_BGTIEN_Msk |
                     SC_INTEN_ACERRIEN_Msk);
    }
    else
    {
        sc->INTEN = (SC_INTEN_RDAIEN_Msk |
                     SC_INTEN_TERRIEN_Msk |
                     SC_INTEN_TMR0IEN_Msk |
                     SC_INTEN_TMR1IEN_Msk |
                     SC_INTEN_TMR2IEN_Msk |
                     SC_INTEN_BGTIEN_Msk |
                     SC_INTEN_CDIEN_Msk |
                     SC_INTEN_ACERRIEN_Msk);
    }
    return;
}

/**
  * @brief This function block guard time (BGT) of specified smartcard module
  * @param[in] sc Base address of smartcard module
  * @param[in] u32BGT Block guard time using ETU as unit, valid range are between 1 ~ 32
  * @return None
  */
void SC_SetBlockGuardTime(SC_T *sc, uint32_t u32BGT)
{
    sc->CTL = (sc->CTL & ~SC_CTL_BGT_Msk) | ((u32BGT - 1UL) << SC_CTL_BGT_Pos);
}

/**
  * @brief This function character guard time (CGT) of specified smartcard module
  * @param[in] sc Base address of smartcard module
  * @param[in] u32CGT Character guard time using ETU as unit, valid range are between 11 ~ 267
  * @return None
  */
void SC_SetCharGuardTime(SC_T *sc, uint32_t u32CGT)
{
    u32CGT -= sc->CTL & SC_CTL_NSB_Msk ? 11UL: 12UL;
    sc->EGT = u32CGT;
}

/**
  * @brief This function stop all smartcard timer of specified smartcard module
  * @param[in] sc Base address of smartcard module
  * @return None
  * @note This function stop the timers within smartcard module, \b not timer module
  */
void SC_StopAllTimer(SC_T *sc)
{
    while(sc->ALTCTL & SC_ALTCTL_SYNC_Msk)
    {
        ;
    }
    sc->ALTCTL &= ~(SC_ALTCTL_CNTEN0_Msk | SC_ALTCTL_CNTEN1_Msk | SC_ALTCTL_CNTEN2_Msk);
}

/**
  * @brief This function configure and start a smartcard timer of specified smartcard module
  * @param[in] sc Base address of smartcard module
  * @param[in] u32TimerNum Timer to start. Valid values are 0, 1, 2.
  * @param[in] u32Mode Timer operating mode, valid values are:
  *             - \ref SC_TMR_MODE_0
  *             - \ref SC_TMR_MODE_1
  *             - \ref SC_TMR_MODE_2
  *             - \ref SC_TMR_MODE_3
  *             - \ref SC_TMR_MODE_4
  *             - \ref SC_TMR_MODE_5
  *             - \ref SC_TMR_MODE_6
  *             - \ref SC_TMR_MODE_7
  *             - \ref SC_TMR_MODE_8
  *             - \ref SC_TMR_MODE_F
  * @param[in] u32ETUCount Timer timeout duration, ETU based. For timer 0, valid  range are between 1~0x1000000ETUs.
  *                        For timer 1 and timer 2, valid range are between 1 ~ 0x100 ETUs
  * @return None
  * @note This function start the timer within smartcard module, \b not timer module
  * @note Depend on the timer operating mode, timer may not start counting immediately
  */
void SC_StartTimer(SC_T *sc, uint32_t u32TimerNum, uint32_t u32Mode, uint32_t u32ETUCount)
{
    uint32_t reg = u32Mode | (SC_TMRCTL0_CNT_Msk & (u32ETUCount - 1UL));
    while(sc->ALTCTL & SC_ALTCTL_SYNC_Msk)
    {
        ;
    }
    if(u32TimerNum == 0UL)
    {
        while(sc->TMRCTL0 & SC_TMRCTL0_SYNC_Msk)
        {
            ;
        }
        sc->TMRCTL0 = reg;
        sc->ALTCTL |= SC_ALTCTL_CNTEN0_Msk;
    }
    else if(u32TimerNum == 1UL)
    {
        while(sc->TMRCTL1 & SC_TMRCTL1_SYNC_Msk)
        {
            ;
        }
        sc->TMRCTL1 = reg;
        sc->ALTCTL |= SC_ALTCTL_CNTEN1_Msk;
    }
    else       /* timer 2 */
    {
        while(sc->TMRCTL2 & SC_TMRCTL2_SYNC_Msk)
        {
            ;
        }
        sc->TMRCTL2 = reg;
        sc->ALTCTL |= SC_ALTCTL_CNTEN2_Msk;
    }
}

/**
  * @brief This function stop a smartcard timer of specified smartcard module
  * @param[in] sc Base address of smartcard module
  * @param[in] u32TimerNum Timer to stop. Valid values are 0, 1, 2.
  * @return None
  * @note This function stop the timer within smartcard module, \b not timer module
  */
void SC_StopTimer(SC_T *sc, uint32_t u32TimerNum)
{
    while(sc->ALTCTL & SC_ALTCTL_SYNC_Msk)
    {
        ;
    }
    if(u32TimerNum == 0UL)
    {
        sc->ALTCTL &= ~SC_ALTCTL_CNTEN0_Msk;
    }
    else if(u32TimerNum == 1UL)
    {
        sc->ALTCTL &= ~SC_ALTCTL_CNTEN1_Msk;
    }
    else        /* timer 2 */
    {
        sc->ALTCTL &= ~SC_ALTCTL_CNTEN2_Msk;
    }
}

/**
  * @brief  This function gets smartcard clock frequency.
  * @param[in] sc Base address of smartcard module
  * @return Smartcard frequency in kHz
  */
uint32_t SC_GetInterfaceClock(SC_T *sc)
{
    uint32_t u32ClkSrc, u32Num, u32Clk;

    if(sc == SC0)
    {
        u32Num = 0UL;
    }
    else if(sc == SC1)
    {
        u32Num = 1UL;
    }
    else
    {
        u32Num = 2UL;
    }

    u32ClkSrc = (CLK->CLKSEL3 >> (2UL * u32Num)) & CLK_CLKSEL3_SC0SEL_Msk;

    /* Get smartcard module clock */
    if(u32ClkSrc == 0UL)
    {
        u32Clk = __HXT;
    }
    else if(u32ClkSrc == 1UL)
    {
        u32Clk = CLK_GetPLLClockFreq();
    }
    else if(u32ClkSrc == 2UL)
    {
        if(u32Num == 1UL)
        {
            u32Clk = CLK_GetPCLK1Freq();
        }
        else
        {
            u32Clk = CLK_GetPCLK0Freq();
        }
    }
    else
    {
        u32Clk = __HIRC;
    }

    u32Clk /= (((CLK->CLKDIV1 >> (8UL * u32Num)) & CLK_CLKDIV1_SC0DIV_Msk) + 1UL) * 1000UL;
    return u32Clk;
}

/*@}*/ /* end of group SC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group SC_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
