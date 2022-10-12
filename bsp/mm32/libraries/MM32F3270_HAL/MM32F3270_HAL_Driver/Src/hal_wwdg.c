/* hal_wwdg.h */
#include "hal_wwdg.h"

void WWDG_Init(WWDG_Type * WWDGx, WWDG_Init_Type * init)
{
    if (NULL != init)
    {
        WWDGx->CFGR = WWDG_CFGR_WDGTB(init->Prescaler)
                    | WWDG_CFGR_W(init->UpperLimit);
    }
}

void WWDG_Start(WWDG_Type * WWDGx)
{
    WWDGx->CR |=  WWDG_CR_WDGA_MASK;
}

void WWDG_Reload(WWDG_Type * WWDGx, uint32_t value)
{
    if (value > WWDG_LOWER_LIMIT)
    {
        WWDGx->CR = (WWDGx->CR & ~WWDG_CR_T_MASK) | WWDG_CR_T(value);
    }
}

void WWDG_EnableInterrupts(WWDG_Type * WWDGx, uint32_t interrupts, bool enable)
{
    if ( (true == enable) && (WWDG_INT_ALMOST_TIMEOUT == interrupts) )
    {
        WWDGx->CFGR |= WWDG_CFGR_EWI_MASK;
    }
    else
    {
        /* if WWDG_INT_ALMOST_TIMEOUT interrupt is enabled, only MCU reset can close it. */
    }
}


uint32_t WWDG_GetStatus(WWDG_Type * WWDGx)
{
    return WWDGx->SR;
}

void WWDG_ClearStatus(WWDG_Type * WWDGx, uint32_t status)
{
    WWDGx->SR &= ~status;
}


/* EOF. */
