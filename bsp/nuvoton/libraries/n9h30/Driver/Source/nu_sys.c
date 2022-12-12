/**************************************************************************//**
* @file     sys.c
* @brief    N9H30 SYS driver source file
*
* @note
* SPDX-License-Identifier: Apache-2.0
* Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include "N9H30.h"
#include "nu_sys.h"

/// @cond HIDDEN_SYMBOLS

#define SYS_MIN_INT_SOURCE       1
#define SYS_MAX_INT_SOURCE       62
#define SYS_NUM_OF_AICREG        16

/* Global variables */
BOOL volatile _sys_bIsAICInitial = FALSE;

/* declaration the function prototype */
extern void SYS_Interrupt_Shell(void);

/* Interrupt Handler Table */
//typedef void (*sys_pvFunPtr)();   /* function pointer */
sys_pvFunPtr sysIrqHandlerTable[] = { 0,                /* 0 */
                                      SYS_Interrupt_Shell,   /* 1 */
                                      SYS_Interrupt_Shell,   /* 2 */
                                      SYS_Interrupt_Shell,   /* 3 */
                                      SYS_Interrupt_Shell,   /* 4 */
                                      SYS_Interrupt_Shell,   /* 5 */
                                      SYS_Interrupt_Shell,   /* 6 */
                                      SYS_Interrupt_Shell,   /* 7 */
                                      SYS_Interrupt_Shell,   /* 8 */
                                      SYS_Interrupt_Shell,   /* 9 */
                                      SYS_Interrupt_Shell,   /* 10 */
                                      SYS_Interrupt_Shell,   /* 11 */
                                      SYS_Interrupt_Shell,   /* 12 */
                                      SYS_Interrupt_Shell,   /* 13 */
                                      SYS_Interrupt_Shell,   /* 14 */
                                      SYS_Interrupt_Shell,   /* 15 */
                                      SYS_Interrupt_Shell,   /* 16 */
                                      SYS_Interrupt_Shell,   /* 17 */
                                      SYS_Interrupt_Shell,   /* 18 */
                                      SYS_Interrupt_Shell,   /* 19 */
                                      SYS_Interrupt_Shell,   /* 20 */
                                      SYS_Interrupt_Shell,   /* 21 */
                                      SYS_Interrupt_Shell,   /* 22 */
                                      SYS_Interrupt_Shell,   /* 23 */
                                      SYS_Interrupt_Shell,   /* 24 */
                                      SYS_Interrupt_Shell,   /* 25 */
                                      SYS_Interrupt_Shell,   /* 26 */
                                      SYS_Interrupt_Shell,   /* 27 */
                                      SYS_Interrupt_Shell,   /* 28 */
                                      SYS_Interrupt_Shell,   /* 29 */
                                      SYS_Interrupt_Shell,   /* 30 */
                                      SYS_Interrupt_Shell,   /* 31 */
                                      SYS_Interrupt_Shell,   /* 32 */
                                      SYS_Interrupt_Shell,   /* 33 */
                                      SYS_Interrupt_Shell,   /* 34 */
                                      SYS_Interrupt_Shell,   /* 35 */
                                      SYS_Interrupt_Shell,   /* 36 */
                                      SYS_Interrupt_Shell,   /* 37 */
                                      SYS_Interrupt_Shell,   /* 38 */
                                      SYS_Interrupt_Shell,   /* 39 */
                                      SYS_Interrupt_Shell,   /* 40 */
                                      SYS_Interrupt_Shell,   /* 41 */
                                      SYS_Interrupt_Shell,   /* 42 */
                                      SYS_Interrupt_Shell,   /* 43 */
                                      SYS_Interrupt_Shell,   /* 44 */
                                      SYS_Interrupt_Shell,   /* 45 */
                                      SYS_Interrupt_Shell,   /* 46 */
                                      SYS_Interrupt_Shell,   /* 47 */
                                      SYS_Interrupt_Shell,   /* 48 */
                                      SYS_Interrupt_Shell,   /* 49 */
                                      SYS_Interrupt_Shell,   /* 50 */
                                      SYS_Interrupt_Shell,   /* 51 */
                                      SYS_Interrupt_Shell,   /* 52 */
                                      SYS_Interrupt_Shell,   /* 53 */
                                      SYS_Interrupt_Shell,   /* 54 */
                                      SYS_Interrupt_Shell,   /* 55 */
                                      SYS_Interrupt_Shell,   /* 56 */
                                      SYS_Interrupt_Shell,   /* 57 */
                                      SYS_Interrupt_Shell,   /* 58 */
                                      SYS_Interrupt_Shell,   /* 59 */
                                      SYS_Interrupt_Shell,   /* 60 */
                                      SYS_Interrupt_Shell    /* 61 */
                                    };

sys_pvFunPtr sysFiqHandlerTable[] = { 0,
                                      SYS_Interrupt_Shell,   /* 1 */
                                      SYS_Interrupt_Shell,   /* 2 */
                                      SYS_Interrupt_Shell,   /* 3 */
                                      SYS_Interrupt_Shell,   /* 4 */
                                      SYS_Interrupt_Shell,   /* 5 */
                                      SYS_Interrupt_Shell,   /* 6 */
                                      SYS_Interrupt_Shell,   /* 7 */
                                      SYS_Interrupt_Shell,   /* 8 */
                                      SYS_Interrupt_Shell,   /* 9 */
                                      SYS_Interrupt_Shell,   /* 10 */
                                      SYS_Interrupt_Shell,   /* 11 */
                                      SYS_Interrupt_Shell,   /* 12 */
                                      SYS_Interrupt_Shell,   /* 13 */
                                      SYS_Interrupt_Shell,   /* 14 */
                                      SYS_Interrupt_Shell,   /* 15 */
                                      SYS_Interrupt_Shell,   /* 16 */
                                      SYS_Interrupt_Shell,   /* 17 */
                                      SYS_Interrupt_Shell,   /* 18 */
                                      SYS_Interrupt_Shell,   /* 19 */
                                      SYS_Interrupt_Shell,   /* 20 */
                                      SYS_Interrupt_Shell,   /* 21 */
                                      SYS_Interrupt_Shell,   /* 22 */
                                      SYS_Interrupt_Shell,   /* 23 */
                                      SYS_Interrupt_Shell,   /* 24 */
                                      SYS_Interrupt_Shell,   /* 25 */
                                      SYS_Interrupt_Shell,   /* 26 */
                                      SYS_Interrupt_Shell,   /* 27 */
                                      SYS_Interrupt_Shell,   /* 28 */
                                      SYS_Interrupt_Shell,   /* 29 */
                                      SYS_Interrupt_Shell,   /* 30 */
                                      SYS_Interrupt_Shell,   /* 31 */
                                      SYS_Interrupt_Shell,   /* 32 */
                                      SYS_Interrupt_Shell,   /* 33 */
                                      SYS_Interrupt_Shell,   /* 34 */
                                      SYS_Interrupt_Shell,   /* 35 */
                                      SYS_Interrupt_Shell,   /* 36 */
                                      SYS_Interrupt_Shell,   /* 37 */
                                      SYS_Interrupt_Shell,   /* 38 */
                                      SYS_Interrupt_Shell,   /* 39 */
                                      SYS_Interrupt_Shell,   /* 40 */
                                      SYS_Interrupt_Shell,   /* 41 */
                                      SYS_Interrupt_Shell,   /* 42 */
                                      SYS_Interrupt_Shell,   /* 43 */
                                      SYS_Interrupt_Shell,   /* 44 */
                                      SYS_Interrupt_Shell,   /* 45 */
                                      SYS_Interrupt_Shell,   /* 46 */
                                      SYS_Interrupt_Shell,   /* 47 */
                                      SYS_Interrupt_Shell,   /* 48 */
                                      SYS_Interrupt_Shell,   /* 49 */
                                      SYS_Interrupt_Shell,   /* 50 */
                                      SYS_Interrupt_Shell,   /* 51 */
                                      SYS_Interrupt_Shell,   /* 52 */
                                      SYS_Interrupt_Shell,   /* 53 */
                                      SYS_Interrupt_Shell,   /* 54 */
                                      SYS_Interrupt_Shell,   /* 55 */
                                      SYS_Interrupt_Shell,   /* 56 */
                                      SYS_Interrupt_Shell,   /* 57 */
                                      SYS_Interrupt_Shell,   /* 58 */
                                      SYS_Interrupt_Shell,   /* 59 */
                                      SYS_Interrupt_Shell,   /* 60 */
                                      SYS_Interrupt_Shell    /* 61 */
                                    };

/* Interrupt Handler */
#if defined ( __GNUC__ ) && !(__CC_ARM)
    static void __attribute__((interrupt("IRQ"))) sysIrqHandler(void)
#else
    __irq void sysIrqHandler()
#endif
{
    UINT32 volatile _mIPER, _mISNR;

    _mIPER = (inpw(REG_AIC_IPER) >> 2) & 0x3f;
    _mISNR = inpw(REG_AIC_ISNR);
    if (_mIPER != 0)
    {
        if (_mISNR != 0)
            (*sysIrqHandlerTable[_mIPER])();
        outpw(REG_AIC_EOSCR, 1);
    }
}

#if defined ( __GNUC__ ) && !(__CC_ARM)
    static void __attribute__((interrupt("FIQ"))) sysFiqHandler(void)
#else
    __irq void sysFiqHandler()
#endif
{
    UINT32 volatile _mIPER, _mISNR;

    _mIPER = (inpw(REG_AIC_IPER) >> 2) & 0x3f;
    _mISNR = inpw(REG_AIC_ISNR);
    if (_mIPER != 0)
    {
        if (_mISNR != 0)
            (*sysFiqHandlerTable[_mIPER])();
        outpw(REG_AIC_EOSCR, 1);
    }
}

void SYS_Interrupt_Shell()
{
    //sysprintf("ISR not found! ISNR=%d\n", inpw(REG_AIC_ISNR));
}

void sysInitializeAIC()
{
    *(unsigned int volatile *)0x38 = (unsigned int)sysIrqHandler;

    *(unsigned int volatile *)0x3C = (unsigned int)sysFiqHandler;
}
/// @endcond HIDDEN_SYMBOLS


/* Interrupt library functions */
/**
 *  @brief  system AIC - disable interrupt
 *
 *  @param[in]  eIntNo  Select interrupt source.  \ref IRQn_Type
 *
 *  @return   0
 */
INT32 sysDisableInterrupt(IRQn_Type eIntNo)
{
    if ((eIntNo > SYS_MAX_INT_SOURCE) || (eIntNo < SYS_MIN_INT_SOURCE))
        return 1;

    if (eIntNo < 32)
        outpw(REG_AIC_MDCR, (1 << eIntNo));
    else
        outpw(REG_AIC_MDCRH, (1 << (eIntNo - 32)));

    return 0;
}


/**
 *  @brief  system AIC - enable interrupt
 *
 *  @param[in]  eIntNo  Select interrupt source.  \ref IRQn_Type
 *
 *  @return   0
 */
INT32 sysEnableInterrupt(IRQn_Type eIntNo)
{
    if ((eIntNo > SYS_MAX_INT_SOURCE) || (eIntNo < SYS_MIN_INT_SOURCE))
        return 1;

    if (eIntNo < 32)
        outpw(REG_AIC_MECR, (1 << eIntNo));
    else
        outpw(REG_AIC_MECRH, (1 << (eIntNo - 32)));

    return 0;
}


/**
 *  @brief  system AIC - install exception handler
 *
 *  @param[in]  nExceptType  exception type. ( \ref SYS_SWI / \ref SYS_D_ABORT / \ref SYS_I_ABORT / \ref SYS_UNDEFINE)
 *  @param[in]  pvNewHandler  own exception handler
 *
 *  @return   old handler
 */
PVOID sysInstallExceptionHandler(INT32 nExceptType, PVOID pvNewHandler)
{
    PVOID _mOldVect = NULL;

    switch (nExceptType)
    {
    case SYS_SWI:
        _mOldVect = *(PVOID volatile *)0x28;
        *(PVOID volatile *)0x28 = pvNewHandler;
        break;

    case SYS_D_ABORT:
        _mOldVect = *(PVOID volatile *)0x30;
        *(PVOID volatile *)0x30 = pvNewHandler;
        break;

    case SYS_I_ABORT:
        _mOldVect = *(PVOID volatile *)0x2C;
        *(PVOID volatile *)0x2C = pvNewHandler;
        break;

    case SYS_UNDEFINE:
        _mOldVect = *(PVOID volatile *)0x24;
        *(PVOID volatile *)0x24 = pvNewHandler;
        break;

    default:
        ;
    }
    return _mOldVect;
}

/**
 *  @brief  system AIC - install FIQ handler
 *
 *  @param[in]  pvNewISR  own fiq handler
 *
 *  @return   old handler
 */
PVOID sysInstallFiqHandler(PVOID pvNewISR)
{
    PVOID _mOldVect;

    _mOldVect = *(PVOID volatile *)0x3C;
    *(PVOID volatile *)0x3C = pvNewISR;
    return _mOldVect;
}

/**
 *  @brief  system AIC - install IRQ handler
 *
 *  @param[in]  pvNewISR  own irq handler
 *
 *  @return   old handler
 */
PVOID sysInstallIrqHandler(PVOID pvNewISR)
{
    PVOID _mOldVect;

    _mOldVect = *(PVOID volatile *)0x38;
    *(PVOID volatile *)0x38 = pvNewISR;
    return _mOldVect;
}


/**
 *  @brief  system AIC - install Own IRQ service routine
 *
 *  @param[in]  nIntTypeLevel   Interrupt Level. ( \ref FIQ_LEVEL_0 / \ref IRQ_LEVEL_1 / \ref IRQ_LEVEL_2 / \ref IRQ_LEVEL_3 /
 *                                                 \ref IRQ_LEVEL_4 / \ref IRQ_LEVEL_5 / \ref IRQ_LEVEL_6 / \ref IRQ_LEVEL_7 )
 *  @param[in]  eIntNo  Interrupt number. \ref IRQn_Type
 *  @param[in]  pvNewISR  own irq handler
 *
 *  @return   old handler
 */
PVOID sysInstallISR(INT32 nIntTypeLevel, IRQn_Type eIntNo, PVOID pvNewISR)
{
    PVOID   _mOldVect;
    UINT32  _mRegAddr/*, _mRegValue*/;
    INT     shift;

    if (!_sys_bIsAICInitial)
    {
        sysInitializeAIC();
        _sys_bIsAICInitial = TRUE;
    }

    _mRegAddr = REG_AIC_SCR1 + ((eIntNo / 4) * 4);
    shift = (eIntNo % 4) * 8;
    nIntTypeLevel &= 0xff;
    outpw(_mRegAddr, (inpw(_mRegAddr) & ~(0x07 << shift)) | (nIntTypeLevel << shift));

    if ((nIntTypeLevel & 0x7) == FIQ_LEVEL_0)
    {
        _mOldVect = (PVOID) sysFiqHandlerTable[eIntNo];
        sysFiqHandlerTable[eIntNo] = (sys_pvFunPtr)pvNewISR;
    }
    else
    {
        _mOldVect = (PVOID) sysIrqHandlerTable[eIntNo];
        sysIrqHandlerTable[eIntNo] = (sys_pvFunPtr)pvNewISR;
    }
    return _mOldVect;
}


INT32 sysSetGlobalInterrupt(INT32 nIntState)
{
    switch (nIntState)
    {
    case ENABLE_ALL_INTERRUPTS:
        outpw(REG_AIC_MECR, 0xFFFFFFFF);
        outpw(REG_AIC_MECRH, 0xFFFFFFFF);
        break;

    case DISABLE_ALL_INTERRUPTS:
        outpw(REG_AIC_MDCR, 0xFFFFFFFF);
        outpw(REG_AIC_MDCRH, 0xFFFFFFFF);
        break;

    default:
        ;
    }
    return 0;
}


/**
 *  @brief  system AIC - Change interrupt level
 *
 *  @param[in]  eIntNo  Interrupt number. \ref IRQn_Type
 *  @param[in]  uIntLevel   Interrupt Level. ( \ref FIQ_LEVEL_0 / \ref IRQ_LEVEL_1 / \ref IRQ_LEVEL_2 / \ref IRQ_LEVEL_3 /
 *                                             \ref IRQ_LEVEL_4 / \ref IRQ_LEVEL_5 / \ref IRQ_LEVEL_6 / \ref IRQ_LEVEL_7 )
 *
 *  @return   0
 */
INT32 sysSetInterruptPriorityLevel(IRQn_Type eIntNo, UINT32 uIntLevel)
{
    UINT32  _mRegAddr;
    INT     shift;

    if ((eIntNo > SYS_MAX_INT_SOURCE) || (eIntNo < SYS_MIN_INT_SOURCE))
        return 1;

    _mRegAddr = REG_AIC_SCR1 + ((eIntNo / 4) * 4);
    shift = (eIntNo % 4) * 8;
    uIntLevel &= 0x7;
    outpw(_mRegAddr, (inpw(_mRegAddr) & ~(0x07 << shift)) | (uIntLevel << shift));

    return 0;
}


INT32 sysSetInterruptType(IRQn_Type eIntNo, UINT32 uIntSourceType)
{
    UINT32 _mRegAddr;
    INT     shift;

    if ((eIntNo > SYS_MAX_INT_SOURCE) || (eIntNo < SYS_MIN_INT_SOURCE))
        return 1;

    _mRegAddr = REG_AIC_SCR1 + ((eIntNo / 4) * 4);
    shift = (eIntNo % 4) * 8;
    uIntSourceType &= 0xC0;
    outpw(_mRegAddr, (inpw(_mRegAddr) & ~(0xC0 << shift)) | (uIntSourceType << shift));

    return 0;
}


/**
 *  @brief  system AIC - Set CP15 Interrupt Type
 *
 *  @param[in]  nIntState   Interrupt state. ( \ref ENABLE_IRQ / \ref ENABLE_FIQ / \ref ENABLE_FIQ_IRQ /
 *                                             \ref DISABLE_IRQ / \ref DISABLE_FIQ / \ref DISABLE_FIQ_IRQ)
 *
 *  @return   0
 */
INT32 sysSetLocalInterrupt(INT32 nIntState)
{
#if defined ( __GNUC__ ) && !(__CC_ARM)

# else
    INT32 temp;
#endif

    switch (nIntState)
    {
    case ENABLE_IRQ:
    case ENABLE_FIQ:
    case ENABLE_FIQ_IRQ:
#if defined ( __GNUC__ ) && !(__CC_ARM)
        asm
        (
            "mrs    r0, CPSR  \n"
            "bic    r0, r0, #0x80  \n"
            "msr    CPSR_c, r0  \n"
        );
#else
        __asm
        {
            MRS    temp, CPSR
            AND    temp, temp, nIntState
            MSR    CPSR_c, temp
        }
#endif
        break;
    case DISABLE_IRQ:
    case DISABLE_FIQ:
    case DISABLE_FIQ_IRQ:
#if defined ( __GNUC__ ) && !(__CC_ARM)
        asm
        (
            "MRS    r0, CPSR  \n"
            "ORR    r0, r0, #0x80  \n"
            "MSR    CPSR_c, r0  \n"
        );
#else
        __asm
        {
            MRS    temp, CPSR
            ORR    temp, temp, nIntState
            MSR    CPSR_c, temp
        }
#endif
        break;

    default:
        ;
    }
    return 0;
}

UINT32  sysGetInterruptEnableStatus(void)
{
    return (inpw(REG_AIC_IMR));
}


UINT32  sysGetInterruptEnableStatusH(void)
{
    return (inpw(REG_AIC_IMRH));
}

/// @cond HIDDEN_SYMBOLS
BOOL sysGetIBitState()
{
    INT32 temp;

#if defined ( __GNUC__ ) && !(__CC_ARM)
    asm
    (
        "MRS %0, CPSR   \n"
        :"=r"(temp) : :
    );
#else
    __asm
    {
        MRS temp, CPSR
    }
#endif

    if (temp & 0x80)
        return FALSE;
    else
        return TRUE;
}

INT32 sysGetPLL(UINT32 reg)
{
    UINT32 N, M, P;

    N = ((inpw(reg) & 0x007F) >> 0) + 1;
    M = ((inpw(reg) & 0x1F80) >> 7) + 1;
    P = ((inpw(reg) & 0xE000) >> 13) + 1;

    return (12 * N / (M * P)); /* 12MHz HXT */
}
/// @endcond HIDDEN_SYMBOLS

/**
 *  @brief  system Timer - install WDT interrupt handler
 *
 *  @param[in]  clk   clock source. \ref CLK_Type
 *
 *  @return   MHz
 */
UINT32 sysGetClock(CLK_Type clk)
{
    UINT32 src, divS, divN, reg, div;

    switch (clk)
    {
    case SYS_UPLL:
        return sysGetPLL(REG_CLK_UPLLCON);

    case SYS_APLL:
        return sysGetPLL(REG_CLK_APLLCON);

    case SYS_SYSTEM:
    {
        reg = inpw(REG_CLK_DIVCTL0);
        switch (reg & 0x18)
        {
        case 0x0:
            src = 12;   /* HXT */
            break;
        case 0x10:
            src = sysGetPLL(REG_CLK_APLLCON);
            break;
        case 0x18:
            src = sysGetPLL(REG_CLK_UPLLCON);
            break;
        default:
            return 0;
        }
        divS = (reg & 0x7) + 1;
        divN = ((reg & 0xf00) >> 8) + 1;
        return (src / divS / divN);
    }

    case SYS_HCLK1:
    {
        reg = inpw(REG_CLK_DIVCTL0);
        switch (reg & 0x18)
        {
        case 0x0:
            src = 12;   /* HXT */
            break;
        case 0x10:
            src = sysGetPLL(REG_CLK_APLLCON);
            break;
        case 0x18:
            src = sysGetPLL(REG_CLK_UPLLCON);
            break;
        default:
            return 0;
        }
        divS = (reg & 0x7) + 1;
        divN = ((reg & 0xf00) >> 8) + 1;
        return (src / divS / divN / 2);
    }

    case SYS_HCLK234:
    {
        reg = inpw(REG_CLK_DIVCTL0);
        switch (reg & 0x18)
        {
        case 0x0:
            src = 12;   /* HXT */
            break;
        case 0x10:
            src = sysGetPLL(REG_CLK_APLLCON);
            break;
        case 0x18:
            src = sysGetPLL(REG_CLK_UPLLCON);
            break;
        default:
            return 0;
        }
        divS = (reg & 0x7) + 1;
        divN = ((reg & 0xf00) >> 8) + 1;
        div = ((reg & 0xf00000) >> 20) + 1;
        return (src / divS / divN / 2 / div);
    }

    case SYS_PCLK:
    {
        reg = inpw(REG_CLK_DIVCTL0);
        switch (reg & 0x18)
        {
        case 0x0:
            src = 12;   /* HXT */
            break;
        case 0x10:
            src = sysGetPLL(REG_CLK_APLLCON);
            break;
        case 0x18:
            src = sysGetPLL(REG_CLK_UPLLCON);
            break;
        default:
            return 0;
        }
        divS = (reg & 0x7) + 1;
        divN = ((reg & 0xf00) >> 8) + 1;
        div = ((reg & 0xf000000) >> 24) + 1;
        return (src / divS / divN / 2 / div);
    }
    case SYS_CPU:
    {
        reg = inpw(REG_CLK_DIVCTL0);
        switch (reg & 0x18)
        {
        case 0x0:
            src = 12;   /* HXT */
            break;
        case 0x10:
            src = sysGetPLL(REG_CLK_APLLCON);
            break;
        case 0x18:
            src = sysGetPLL(REG_CLK_UPLLCON);
            break;
        default:
            return 0;
        }
        divS = (reg & 0x7) + 1;
        divN = ((reg & 0xf00) >> 8) + 1;
        div = ((reg & 0xf0000) >> 16) + 1;
        return (src / divS / divN / div);
    }

    default:
        ;
    }
    return 0;
}


/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/
