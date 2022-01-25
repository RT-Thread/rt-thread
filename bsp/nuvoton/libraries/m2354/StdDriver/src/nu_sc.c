/**************************************************************************//**
 * @file     sc.c
 * @version  V3.00
 * @brief    Smartcard(SC) driver source file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include "NuMicro.h"


/* Below are variables used locally by SC driver and does not want to parse by doxygen unless HIDDEN_SYMBOLS is defined */
/** @cond HIDDEN_SYMBOLS */
static uint32_t g_u32CardStateIgnore[SC_INTERFACE_NUM] = {0UL, 0UL, 0UL};

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
  * @brief      Indicates specified smartcard slot status
  *
  * @param[in]  sc      The pointer of smartcard module.
  *
  * @return     Card insert status
  * @retval     TRUE    Card insert
  * @retval     FALSE   Card remove
  *
  * @details    This function is used to check if specified smartcard slot is presented.
  */
uint32_t SC_IsCardInserted(SC_T *sc)
{
    uint32_t u32Ret;

    /* put conditions into two variable to remove IAR compilation warning */
    uint32_t cond1 = ((sc->STATUS & SC_STATUS_CDPINSTS_Msk) >> SC_STATUS_CDPINSTS_Pos);
    uint32_t cond2 = ((sc->CTL & SC_CTL_CDLV_Msk) >> SC_CTL_CDLV_Pos);

    if(((sc == SC0) || (sc == SC0_NS)) && (g_u32CardStateIgnore[0] == 1UL))
    {
        u32Ret = (uint32_t)TRUE;
    }
    else if(((sc == SC1) || (sc == SC1_NS)) && (g_u32CardStateIgnore[1] == 1UL))
    {
        u32Ret = (uint32_t)TRUE;
    }
    else if(((sc == SC2) || (sc == SC2_NS)) && (g_u32CardStateIgnore[2] == 1UL))
    {
        u32Ret = (uint32_t)TRUE;
    }
    else if(cond1 != cond2)
    {
        u32Ret = (uint32_t)FALSE;
    }
    else
    {
        u32Ret = (uint32_t)TRUE;
    }

    return u32Ret;
}

/*
  * @brief      Reset the Tx and Rx FIFO of smartcard module
  *
  * @param[in]  sc      The pointer of smartcard module.
  *
  * @return     None
  *
  * @details    This function reset both transmit and receive FIFO of specified smartcard module.
  */
void SC_ClearFIFO(SC_T *sc)
{
    while((sc->ALTCTL & SC_ALTCTL_SYNC_Msk) == SC_ALTCTL_SYNC_Msk) {}
    sc->ALTCTL |= (SC_ALTCTL_TXRST_Msk | SC_ALTCTL_RXRST_Msk);
}

/**
  * @brief      Disable specified smartcard module
  *
  * @param[in]  sc      The pointer of smartcard module.
  *
  * @return     None
  *
  * @details    This function disable specified smartcard module, and force all transition to IDLE state.
  */
void SC_Close(SC_T *sc)
{
    sc->INTEN = 0UL;

    while((sc->PINCTL & SC_PINCTL_SYNC_Msk) == SC_PINCTL_SYNC_Msk) {}
    sc->PINCTL = 0UL;
    sc->ALTCTL = 0UL;

    while((sc->CTL & SC_CTL_SYNC_Msk) == SC_CTL_SYNC_Msk) {}
    sc->CTL = 0UL;
}

/**
  * @brief      Initialized smartcard module
  *
  * @param[in]  sc          The pointer of smartcard module.
  * @param[in]  u32CardDet  Card detect polarity, select the SC_CD pin state which indicates card absent. Could be:
  *                         -\ref SC_PIN_STATE_HIGH
  *                         -\ref SC_PIN_STATE_LOW
  *                         -\ref SC_PIN_STATE_IGNORE, no card detect pin, always assumes card present.
  * @param[in]  u32PWR      Power off polarity, select the SC_PWR pin state which could set smartcard VCC to high level. Could be:
  *                         -\ref SC_PIN_STATE_HIGH
  *                         -\ref SC_PIN_STATE_LOW
  *
  * @return     None
  *
  * @details    This function initialized smartcard module.
  */
void SC_Open(SC_T *sc, uint32_t u32CardDet, uint32_t u32PWR)
{
    uint32_t u32Reg = 0UL, u32Intf;

    if((sc == SC0) || (sc == SC0_NS))
    {
        u32Intf = 0UL;
    }
    else if((sc == SC1) || (sc == SC1_NS))
    {
        u32Intf = 1UL;
    }
    else
    {
        u32Intf = 2UL;
    }

    if(u32CardDet != SC_PIN_STATE_IGNORE)
    {
        u32Reg = u32CardDet ? 0UL : SC_CTL_CDLV_Msk;
        g_u32CardStateIgnore[u32Intf] = 0UL;
    }
    else
    {
        g_u32CardStateIgnore[u32Intf] = 1UL;
    }
    sc->PINCTL = u32PWR ? 0UL : SC_PINCTL_PWRINV_Msk;

    while((sc->CTL & SC_CTL_SYNC_Msk) == SC_CTL_SYNC_Msk) {}
    sc->CTL = SC_CTL_SCEN_Msk | SC_CTL_TMRSEL_Msk | u32Reg;
}

/**
  * @brief      Reset specified smartcard module
  *
  * @param[in]  sc      The pointer of smartcard module.
  *
  * @return     None
  *
  * @details    This function reset specified smartcard module to its default state for activate smartcard.
  */
void SC_ResetReader(SC_T *sc)
{
    uint32_t u32Intf;

    if((sc == SC0) || (sc == SC0_NS))
    {
        u32Intf = 0UL;
    }
    else if((sc == SC1) || (sc == SC1_NS))
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
    while((sc->CTL & SC_CTL_SYNC_Msk) == SC_CTL_SYNC_Msk) {}
    sc->CTL &= ~(SC_CTL_RXTRGLV_Msk |
                 SC_CTL_CDDBSEL_Msk |
                 SC_CTL_TXRTY_Msk |
                 SC_CTL_TXRTYEN_Msk |
                 SC_CTL_RXRTY_Msk |
                 SC_CTL_RXRTYEN_Msk);
    while((sc->CTL & SC_CTL_SYNC_Msk) == SC_CTL_SYNC_Msk) {}
    /* Enable auto convention, and all three smartcard internal timers */
    sc->CTL |= SC_CTL_AUTOCEN_Msk | SC_CTL_TMRSEL_Msk;
    /* Disable Rx timeout */
    sc->RXTOUT = 0UL;
    /* 372 clocks per ETU by default */
    sc->ETUCTL = 371UL;

    /* Enable necessary interrupt for smartcard operation */
    if(g_u32CardStateIgnore[u32Intf])   /* Do not enable card detect interrupt if card present state ignore */
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
                     SC_INTEN_ACERRIEN_Msk |
                     SC_INTEN_CDIEN_Msk);
    }

    return;
}

/**
  * @brief      Set Block Guard Time (BGT)
  *
  * @param[in]  sc      The pointer of smartcard module.
  * @param[in]  u32BGT  Block guard time using ETU as unit, valid range are between 1 ~ 32.
  *
  * @return     None
  *
  * @details    This function is used to configure block guard time (BGT) of specified smartcard module.
  */
void SC_SetBlockGuardTime(SC_T *sc, uint32_t u32BGT)
{
    sc->CTL = (sc->CTL & ~SC_CTL_BGT_Msk) | ((u32BGT - 1UL) << SC_CTL_BGT_Pos);
}

/**
  * @brief      Set Character Guard Time (CGT)
  *
  * @param[in]  sc      The pointer of smartcard module.
  * @param[in]  u32CGT  Character guard time using ETU as unit, valid range are between 11 ~ 267.
  *
  * @return     None
  *
  * @details    This function is used to configure character guard time (CGT) of specified smartcard module.
  * @note       Before using this API, user should set the correct stop bit length first.
  */
void SC_SetCharGuardTime(SC_T *sc, uint32_t u32CGT)
{
    /* CGT is "START bit" + "8-bits" + "Parity bit" + "STOP bit(s)" + "EGT counts" */
    u32CGT -= ((sc->CTL & SC_CTL_NSB_Msk) == SC_CTL_NSB_Msk) ? 11UL : 12UL;
    sc->EGT = u32CGT;
}

/**
  * @brief      Stop all smartcard timer
  *
  * @param[in]  sc      The pointer of smartcard module.
  *
  * @return     None
  *
  * @note       This function stop the timers within specified smartcard module, \b not timer module.
  */
void SC_StopAllTimer(SC_T *sc)
{
    while((sc->ALTCTL & SC_ALTCTL_SYNC_Msk) == SC_ALTCTL_SYNC_Msk) {}
    sc->ALTCTL &= ~(SC_ALTCTL_CNTEN0_Msk | SC_ALTCTL_CNTEN1_Msk | SC_ALTCTL_CNTEN2_Msk);
}

/**
  * @brief      Configure and start smartcard timer
  *
  * @param[in]  sc          The pointer of smartcard module.
  * @param[in] u32TimerNum  Timer to start. Valid values are 0, 1, 2.
  * @param[in]  u32Mode     Timer operating mode, valid values are:
  *                             - \ref SC_TMR_MODE_0
  *                             - \ref SC_TMR_MODE_1
  *                             - \ref SC_TMR_MODE_2
  *                             - \ref SC_TMR_MODE_3
  *                             - \ref SC_TMR_MODE_4
  *                             - \ref SC_TMR_MODE_5
  *                             - \ref SC_TMR_MODE_6
  *                             - \ref SC_TMR_MODE_7
  *                             - \ref SC_TMR_MODE_8
  *                             - \ref SC_TMR_MODE_F
  * @param[in]  u32ETUCount Timer timeout duration, ETU based. For timer 0, valid  range are between 1 ~ 0x1000000 ETUs.
  *                         For timer 1 and timer 2, valid range are between 1 ~ 0x100 ETUs.
  *
  * @return     None
  *
  * @note       This function start the timer within specified smartcard module, \b not timer module.
  * @note       Depend on the timer operating mode, timer may not start counting immediately and starts when condition match.
  */
void SC_StartTimer(SC_T *sc, uint32_t u32TimerNum, uint32_t u32Mode, uint32_t u32ETUCount)
{
    uint32_t u32Reg = u32Mode | (SC_TMRCTL0_CNT_Msk & (u32ETUCount - 1UL));
    while((sc->ALTCTL & SC_ALTCTL_SYNC_Msk) == SC_ALTCTL_SYNC_Msk) {}
    if(u32TimerNum == 0UL)
    {
        while((sc->TMRCTL0 & SC_TMRCTL0_SYNC_Msk) == SC_TMRCTL0_SYNC_Msk) {}
        sc->TMRCTL0 = u32Reg;
        sc->ALTCTL |= SC_ALTCTL_CNTEN0_Msk;
    }
    else if(u32TimerNum == 1UL)
    {
        while((sc->TMRCTL1 & SC_TMRCTL1_SYNC_Msk) == SC_TMRCTL1_SYNC_Msk) {}
        sc->TMRCTL1 = u32Reg;
        sc->ALTCTL |= SC_ALTCTL_CNTEN1_Msk;
    }
    else       /* timer 2 */
    {
        while((sc->TMRCTL2 & SC_TMRCTL2_SYNC_Msk) == SC_TMRCTL2_SYNC_Msk) {}
        sc->TMRCTL2 = u32Reg;
        sc->ALTCTL |= SC_ALTCTL_CNTEN2_Msk;
    }
}

/**
  * @brief      Stop a smartcard timer
  *
  * @param[in]  sc          The pointer of smartcard module.
  * @param[in] u32TimerNum  Timer to stop. Valid values are 0, 1, 2.
  *
  * @return     None
  *
  * @note       This function stop the timer within specified smartcard module, \b not timer module.
  */
void SC_StopTimer(SC_T *sc, uint32_t u32TimerNum)
{
    while(sc->ALTCTL & SC_ALTCTL_SYNC_Msk) {}

    if(u32TimerNum == 0UL)      /* timer 0 */
    {
        sc->ALTCTL &= ~SC_ALTCTL_CNTEN0_Msk;
    }
    else if(u32TimerNum == 1UL) /* timer 1 */
    {
        sc->ALTCTL &= ~SC_ALTCTL_CNTEN1_Msk;
    }
    else                        /* timer 2 */
    {
        sc->ALTCTL &= ~SC_ALTCTL_CNTEN2_Msk;
    }
}

/**
  * @brief      Get smartcard clock frequency
  *
  * @param[in]  sc      The pointer of smartcard module.
  *
  * @return     Smartcard frequency in kHZ
  *
  * @details    This function is used to get specified smartcard module clock frequency in kHz.
  */
uint32_t SC_GetInterfaceClock(SC_T *sc)
{
    uint32_t u32ClkSrc = 0, u32Num = 0, u32ClkFreq = __HIRC, u32Div = 0;

    /* Get smartcard module clock source and divider */
    if((sc == SC0) || (sc == SC0_NS))
    {
        u32Num = 0UL;
        u32ClkSrc = CLK_GetModuleClockSource(SC0_MODULE);
        u32Div = CLK_GetModuleClockDivider(SC0_MODULE);
    }
    else if((sc == SC1) || (sc == SC1_NS))
    {
        u32Num = 1UL;
        u32ClkSrc = CLK_GetModuleClockSource(SC1_MODULE);
        u32Div = CLK_GetModuleClockDivider(SC1_MODULE);
    }
    else if((sc == SC2) || (sc == SC2_NS))
    {
        u32Num = 2UL;
        u32ClkSrc = CLK_GetModuleClockSource(SC2_MODULE);
        u32Div = CLK_GetModuleClockDivider(SC2_MODULE);
    }
    else
    {
        u32ClkFreq = 0UL;
    }

    if(u32ClkFreq != 0UL)
    {
        /* Get smartcard module clock */
        if(u32ClkSrc == 0UL)
        {
            u32ClkFreq = __HXT;
        }
        else if(u32ClkSrc == 1UL)
        {
            u32ClkFreq = CLK_GetPLLClockFreq();
        }
        else if(u32ClkSrc == 2UL)
        {
            if(u32Num == 1UL)
            {
                u32ClkFreq = CLK_GetPCLK1Freq();
            }
            else
            {
                u32ClkFreq = CLK_GetPCLK0Freq();
            }
        }
        else
        {
            u32ClkFreq = __HIRC;
        }

        u32ClkFreq /= (u32Div + 1UL) * 1000UL;
    }

    return u32ClkFreq;
}

/**@}*/ /* end of group SC_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group SC_Driver */

/**@}*/ /* end of group Standard_Driver */
