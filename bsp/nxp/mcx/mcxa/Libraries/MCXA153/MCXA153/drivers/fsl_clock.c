/*
 * Copyright 2023, NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_clock.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.clock"
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/
/** External clock rate on the CLKIN pin in Hz. If not used,
    set this to 0. Otherwise, set it to the exact rate in Hz this pin is
    being driven at. */
volatile static uint32_t s_Ext_Clk_Freq = 16000000U;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/* Get FRO 12M Clk */
static uint32_t CLOCK_GetFro12MFreq(void);
/* Get CLK 1M Clk */
static uint32_t CLOCK_GetClk1MFreq(void);
/* Get HF FRO Clk */
static uint32_t CLOCK_GetFroHfFreq(void);
/* Get CLK 48M Clk */
static uint32_t CLOCK_GetClk48MFreq(void);
/* Get CLK 16K Clk */
static uint32_t CLOCK_GetClk16KFreq(uint8_t id);
/* Get EXT OSC Clk */
static uint32_t CLOCK_GetExtClkFreq(void);
/* Get Main_Clk */
uint32_t CLOCK_GetMainClk(void);
/* Get FRO_16K */
static uint32_t CLOCK_GetFRO16KFreq(void);

/* Check if DIV is halt */
static inline bool CLOCK_IsDivHalt(uint32_t div_value)
{
    if (0U != (div_value & (1UL << 30U)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*******************************************************************************
 * Code
 ******************************************************************************/

/* Clock Selection for IP */
/**
 * brief   Configure the clock selection muxes.
 * param   connection  : Clock to be configured.
 * return  Nothing
 */
void CLOCK_AttachClk(clock_attach_id_t connection)
{
    const uint32_t reg_offset = CLK_ATTACH_REG_OFFSET(connection);
    const uint32_t clk_sel    = CLK_ATTACH_CLK_SEL(connection);

    if (kNONE_to_NONE != connection)
    {
        CLOCK_SetClockSelect((clock_select_name_t)reg_offset, clk_sel);
    }
}

/* Return the actual clock attach id */
/**
 * brief   Get the actual clock attach id.
 * This fuction uses the offset in input attach id, then it reads the actual source value in
 * the register and combine the offset to obtain an actual attach id.
 * param   connection  : Clock attach id to get.
 * return  Clock source value.
 */
clock_attach_id_t CLOCK_GetClockAttachId(clock_attach_id_t connection)
{
    const uint32_t reg_offset = CLK_ATTACH_REG_OFFSET(connection);
    uint32_t actual_sel       = 0U;
    uint32_t clock_attach_id  = 0U;

    if (kNONE_to_NONE == connection)
    {
        return kNONE_to_NONE;
    }

    actual_sel      = CLOCK_GetClockSelect((clock_select_name_t)reg_offset);
    clock_attach_id = CLK_ATTACH_MUX(reg_offset, actual_sel);

    return (clock_attach_id_t)clock_attach_id;
}

/* Set the clock selection value */
void CLOCK_SetClockSelect(clock_select_name_t sel_name, uint32_t value)
{
    volatile uint32_t *pClkCtrl = (volatile uint32_t *)(MRCC0_BASE + (uint32_t)sel_name);
    assert(sel_name <= kCLOCK_SelMax);

    if (sel_name == kCLOCK_SelSCGSCS)
    {
        SCG0->RCCR = (SCG0->RCCR & ~(SCG_RCCR_SCS_MASK)) | SCG_RCCR_SCS(value);
        while ((SCG0->CSR & SCG_CSR_SCS_MASK) != SCG_CSR_SCS(value))
        {
        }
    }
    else
    {
        /* Unlock clock configuration */
        SYSCON->CLKUNLOCK &= ~SYSCON_CLKUNLOCK_UNLOCK_MASK;

        *pClkCtrl = value;

        /* Freeze clock configuration */
        SYSCON->CLKUNLOCK |= SYSCON_CLKUNLOCK_UNLOCK_MASK;
    }
}

/* Get the clock selection value */
uint32_t CLOCK_GetClockSelect(clock_select_name_t sel_name)
{
    volatile uint32_t *pClkCtrl = (volatile uint32_t *)(MRCC0_BASE + (uint32_t)sel_name);
    uint32_t actual_sel         = 0U;
    assert(sel_name <= kCLOCK_SelMax);

    if (sel_name == kCLOCK_SelSCGSCS)
    {
        actual_sel = (uint32_t)((SCG0->RCCR & SCG_RCCR_SCS_MASK) >> SCG_RCCR_SCS_SHIFT);
    }
    else
    {
        actual_sel = *pClkCtrl;
    }

    return actual_sel;
}

/* Set the clock divider value */
void CLOCK_SetClockDiv(clock_div_name_t div_name, uint32_t value)
{
    volatile uint32_t *pDivCtrl = (volatile uint32_t *)(MRCC0_BASE + (uint32_t)div_name);
    assert(div_name <= kCLOCK_DivMax);

    /* Unlock clock configuration */
    SYSCON->CLKUNLOCK &= ~SYSCON_CLKUNLOCK_UNLOCK_MASK;

    /* halt and reset clock dividers */
    *pDivCtrl = 0x3UL << 29U;

    if (value == 0U) /*!<  halt */
    {
        *pDivCtrl |= (1UL << 30U);
    }
    else
    {
        *pDivCtrl = (value - 1U);
    }

    /* Freeze clock configuration */
    SYSCON->CLKUNLOCK |= SYSCON_CLKUNLOCK_UNLOCK_MASK;
}

/* Get the clock divider value */
uint32_t CLOCK_GetClockDiv(clock_div_name_t div_name)
{
    volatile uint32_t *pDivCtrl = (volatile uint32_t *)(MRCC0_BASE + (uint32_t)div_name);
    assert(div_name <= kCLOCK_DivMax);

    if (((*pDivCtrl) & (1UL << 30U)) != 0U)
    {
        return 0;
    }
    else
    {
        return ((*pDivCtrl & 0xFFU) + 1U);
    }
}

/* Halt the clock divider value */
void CLOCK_HaltClockDiv(clock_div_name_t div_name)
{
    volatile uint32_t *pDivCtrl = (volatile uint32_t *)(MRCC0_BASE + (uint32_t)div_name);
    assert(div_name <= kCLOCK_DivMax);

    /* Unlock clock configuration */
    SYSCON->CLKUNLOCK &= ~SYSCON_CLKUNLOCK_UNLOCK_MASK;

    *pDivCtrl |= (1UL << 30U);

    /* Freeze clock configuration */
    SYSCON->CLKUNLOCK |= SYSCON_CLKUNLOCK_UNLOCK_MASK;
}

/* Initialize the FROHF to given frequency (48,64,96,192) */
status_t CLOCK_SetupFROHFClocking(uint32_t iFreq)
{
    uint8_t freq_select = 0x0U;
    switch (iFreq)
    {
        case 48000000U:
            freq_select = 1U;
            break;
        case 64000000U:
            freq_select = 3U;
            break;
        case 96000000U:
            freq_select = 5U;
            break;
        case 192000000U:
            freq_select = 7U;
            break;
        default:
            freq_select = 0xFU;
            break;
    }

    if (0xFU == freq_select)
    {
        return kStatus_Fail;
    }

    /* Set FIRC frequency */
    SCG0->FIRCCFG = SCG_FIRCCFG_FREQ_SEL(freq_select);

    /* Unlock FIRCCSR */
    SCG0->FIRCCSR &= ~SCG_FIRCCSR_LK_MASK;

    /* Enable CLK 48 MHz clock for peripheral use */
    SCG0->FIRCCSR |= SCG_FIRCCSR_FIRC_SCLK_PERIPH_EN_MASK;
    /* Enable FIRC HF clock for peripheral use */
    SCG0->FIRCCSR |= SCG_FIRCCSR_FIRC_FCLK_PERIPH_EN_MASK;
    /* Enable FIRC */
    SCG0->FIRCCSR |= SCG_FIRCCSR_FIRCEN_MASK;

    /* Lock FIRCCSR */
    SCG0->FIRCCSR |= SCG_FIRCCSR_LK_MASK;

    /* Wait for FIRC clock to be valid. */
    while ((SCG0->FIRCCSR & SCG_FIRCCSR_FIRCVLD_MASK) == 0U)
    {
    }

    return kStatus_Success;
}

/* Initialize the FRO12M. */
status_t CLOCK_SetupFRO12MClocking(void)
{
    /* Unlock SIRCCSR */
    SCG0->SIRCCSR &= ~SCG_SIRCCSR_LK_MASK;

    /* Enable FRO12M clock for peripheral use */
    SCG0->SIRCCSR |= SCG_SIRCCSR_SIRC_CLK_PERIPH_EN_MASK;

    /* Lock SIRCCSR */
    SCG0->SIRCCSR |= SCG_SIRCCSR_LK_MASK;

    /* Wait for SIRC clock to be valid. */
    while ((SCG0->SIRCCSR & SCG_SIRCCSR_SIRCVLD_MASK) == 0U)
    {
    }

    return kStatus_Success;
}

/*!
 * brief   Initialize the FRO16K.
 * This function turns on FRO16K.
 * return  returns success or fail status.
 */
status_t CLOCK_SetupFRO16KClocking(uint8_t clk_16k_enable_mask)
{
    VBAT0->FROCTLA |= VBAT_FROCTLA_FRO_EN_MASK;
    VBAT0->FROLCKA |= VBAT_FROLCKA_LOCK_MASK;

    /* enable clk_16k output clock to corresponding modules according to the enable_mask. */
    VBAT0->FROCLKE |= VBAT_FROCLKE_CLKE(((uint32_t)clk_16k_enable_mask));

    return kStatus_Success;
}

/*!
 * brief   Initialize the external osc clock to given frequency.
 * param   iFreq   : Desired frequency (must be equal to exact rate in Hz)
 * return  returns success or fail status.
 */
status_t CLOCK_SetupExtClocking(uint32_t iFreq)
{
    uint8_t range = 0U;

    if ((iFreq >= 8000000U) && (iFreq < 16000000U))
    {
        range = 0U;
    }
    else if ((iFreq >= 16000000U) && (iFreq < 25000000U))
    {
        range = 1U;
    }
    else if ((iFreq >= 25000000U) && (iFreq < 40000000U))
    {
        range = 2U;
    }
    else if ((iFreq >= 40000000U) && (iFreq <= 50000000U))
    {
        range = 3U;
    }
    else
    {
        return kStatus_InvalidArgument;
    }

    /* If configure register is locked, return error. */
    if ((SCG0->SOSCCSR & SCG_SOSCCSR_LK_MASK) != 0U)
    {
        return kStatus_ReadOnly;
    }

    /* De-initializes the SCG SOSC */
    SCG0->SOSCCSR = SCG_SOSCCSR_SOSCERR_MASK;

    /* Select SOSC source (internal crystal oscillator) and Configure SOSC range */
    SCG0->SOSCCFG = SCG_SOSCCFG_EREFS_MASK | SCG_SOSCCFG_RANGE(range);

    /* Unlock SOSCCSR */
    SCG0->SOSCCSR &= ~SCG_SOSCCSR_LK_MASK;

    /* Enable SOSC clock monitor and Enable SOSC */
    SCG0->SOSCCSR |= (SCG_SOSCCSR_SOSCCM_MASK | SCG_SOSCCSR_SOSCEN_MASK);

    /* Wait for SOSC clock to be valid. */
    while ((SCG0->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK) == 0U)
    {
    }

    s_Ext_Clk_Freq = iFreq;

    return kStatus_Success;
}

/*!
 * @brief   Initialize the external reference clock to given frequency.
 * param   iFreq   : Desired frequency (must be equal to exact rate in Hz)
 * return  returns success or fail status.
 */
status_t CLOCK_SetupExtRefClocking(uint32_t iFreq)
{
    
    if (iFreq > 50000000U)
    {
        return kStatus_InvalidArgument;
    }

    /* If configure register is locked, return error. */
    if ((SCG0->SOSCCSR & SCG_SOSCCSR_LK_MASK) != 0U)
    {
        return kStatus_ReadOnly;
    }

    /* De-initializes the SCG SOSC */
    SCG0->SOSCCSR = SCG_SOSCCSR_SOSCERR_MASK;

    /* Select SOSC source (external reference clock)*/
    SCG0->SOSCCFG &= ~SCG_SOSCCFG_EREFS_MASK;

    /* Unlock SOSCCSR */
    SCG0->SOSCCSR &= ~SCG_SOSCCSR_LK_MASK;

    /* Enable SOSC clock monitor and Enable SOSC */
    SCG0->SOSCCSR |= (SCG_SOSCCSR_SOSCCM_MASK | SCG_SOSCCSR_SOSCEN_MASK);

    /* Wait for SOSC clock to be valid. */
    while ((SCG0->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK) == 0U)
    {
    }

    s_Ext_Clk_Freq = iFreq;

    return kStatus_Success;
}

/* Get IP Clk */
/*! brief  Return Frequency of selected clock
 *  return Frequency of selected clock
 */
uint32_t CLOCK_GetFreq(clock_name_t clockName)
{
    uint32_t freq = 0U;

    switch (clockName)
    {
        case kCLOCK_MainClk: /* MAIN_CLK */
            freq = CLOCK_GetMainClk();
            break;
        case kCLOCK_CoreSysClk: /* Core/system clock(CPU_CLK) */
            freq = CLOCK_GetCoreSysClkFreq();
            break;
        case kCLOCK_SYSTEM_CLK: /* AHB clock */
            freq = CLOCK_GetCoreSysClkFreq();
            break;
        case kCLOCK_BusClk: /* Bus clock (AHB clock) */
            freq = CLOCK_GetCoreSysClkFreq();
            break;
        case kCLOCK_ExtClk: /* External Clock */
            freq = CLOCK_GetExtClkFreq();
            break;
        case kCLOCK_FroHf: /* FROHF */
            freq = CLOCK_GetFroHfFreq();
            break;
        case kCLOCK_FroHfDiv: /* Divided by FROHF */
            freq = CLOCK_GetFroHfFreq() / ((MRCC0->MRCC_FRO_HF_DIV_CLKDIV & 0xfU) + 1U);
            break;
        case kCLOCK_Clk48M: /* CLK48M */
            freq = CLOCK_GetClk48MFreq();
            break;
        case kCLOCK_Fro12M: /* FRO12M */
            freq = CLOCK_GetFro12MFreq();
            break;
        case kCLOCK_Clk1M: /* CLK1M */
            freq = CLOCK_GetClk1MFreq();
            break;
        case kCLOCK_Fro16K: /* FRO16K */
            freq = CLOCK_GetFRO16KFreq();
            break;
        case kCLOCK_Clk16K0: /* CLK16K[0] */
            freq = CLOCK_GetClk16KFreq(0);
            break;
        case kCLOCK_Clk16K1: /* CLK16K[1] */
            freq = CLOCK_GetClk16KFreq(1);
            break;
        case kCLOCK_SLOW_CLK: /* SYSTEM_CLK divided by 4 */
            freq = CLOCK_GetCoreSysClkFreq() >> 2;
            break;
        default:
            freq = 0U;
            break;
    }
    return freq;
}

/* Get FRO 12M Clk */
/*! brief  Return Frequency of FRO 12MHz
 *  return Frequency of FRO 12MHz
 */
static uint32_t CLOCK_GetFro12MFreq(void)
{
    return ((SCG0->SIRCCSR & SCG_SIRCCSR_SIRC_CLK_PERIPH_EN_MASK) != 0U) ? 12000000U : 0U;
}

/* Get CLK 1M Clk */
/*! brief  Return Frequency of CLK 1MHz
 *  return Frequency of CLK 1MHz
 */
static uint32_t CLOCK_GetClk1MFreq(void)
{
    return 1000000U;
}

/* Get HF FRO Clk */
/*! brief  Return Frequency of High-Freq output of FRO
 *  return Frequency of High-Freq output of FRO
 */
static uint32_t CLOCK_GetFroHfFreq(void)
{
    uint32_t freq;

    if (((SCG0->FIRCCSR & SCG_FIRCCSR_FIRCEN_MASK) == 0U) ||
        ((SCG0->FIRCCSR & SCG_FIRCCSR_FIRC_FCLK_PERIPH_EN_SHIFT) == 0U))
    {
        freq = 0U;
    }

    switch ((SCG0->FIRCCFG & SCG_FIRCCFG_FREQ_SEL_MASK) >> SCG_FIRCCFG_FREQ_SEL_SHIFT)
    {
        case 0U:
            freq = 36000000U;
            break;
        case 1U:
            freq = 48000000U;
            break;
        case 2U:
            freq = 48000000U;
            break;
        case 3U:
            freq = 64000000U;
            break;
        case 4U:
            freq = 72000000U;
            break;
        case 5U:
            freq = 96000000U;
            break;
        case 6U:
            freq = 144000000U;
            break;
        case 7U:
            freq = 192000000U;
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

/* Get CLK 48M Clk */
/*! brief  Return Frequency of CLK 48MHz
 *  return Frequency of CLK 48MHz
 */
static uint32_t CLOCK_GetClk48MFreq(void)
{
    return (((SCG0->FIRCCSR & SCG_FIRCCSR_FIRC_SCLK_PERIPH_EN_MASK) != 0U) ||
            ((SCG0->FIRCCSR & SCG_FIRCCSR_FIRC_SCLK_PERIPH_EN_SHIFT) == 0U)) ?
               48000000U :
               0U;
}

/*! brief  Return Frequency of FRO16K
 *  return Frequency of FRO_16K
 */
static uint32_t CLOCK_GetFRO16KFreq(void)
{
    return ((VBAT0->FROCTLA & VBAT_FROCTLA_FRO_EN_MASK) != 0U) ? 16000U : 0U;
}
/* Get CLK 16K Clk */
/*! brief  Return Frequency of CLK 16KHz
 *  return Frequency of CLK 16KHz
 */
static uint32_t CLOCK_GetClk16KFreq(uint8_t id)
{
    return (((VBAT0->FROCTLA & VBAT_FROCTLA_FRO_EN_MASK) != 0U) &&
            ((VBAT0->FROCLKE & VBAT_FROCLKE_CLKE((((uint32_t)id) << 1U))) != 0U)) ?
               16000U :
               0U;
}

/* Get EXT OSC Clk */
/*! brief  Return Frequency of External Clock
 *  return Frequency of External Clock. If no external clock is used returns 0.
 */
static uint32_t CLOCK_GetExtClkFreq(void)
{
    return ((SCG0->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK) != 0U) ? s_Ext_Clk_Freq : 0U;
}

/* Get MAIN Clk */
/*! brief  Return Frequency of Core System
 *  return Frequency of Core System
 */
uint32_t CLOCK_GetMainClk(void)
{
    uint32_t freq = 0U;

    switch ((SCG0->CSR & SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT)
    {
        case 1U:
            freq = CLOCK_GetExtClkFreq();
            break;
        case 2U:
            freq = CLOCK_GetFro12MFreq();
            break;
        case 3U:
            freq = CLOCK_GetFroHfFreq();
            break;
        case 4U:
            freq = CLOCK_GetClk16KFreq(1);
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

/*! brief  Return Frequency of core
 *  return Frequency of the core
 */
uint32_t CLOCK_GetCoreSysClkFreq(void)
{
    return CLOCK_GetMainClk() / ((SYSCON->AHBCLKDIV & 0xFFU) + 1U);
}

/* Get I3C Clk */
/*! brief  Return Frequency of I3C Clock
 *  return Frequency of I3C Clock
 */
uint32_t CLOCK_GetI3CFClkFreq(void)
{
    uint32_t freq   = 0U;
    uint32_t clksel = (MRCC0->MRCC_I3C0_FCLK_CLKSEL);
    uint32_t clkdiv = (MRCC0->MRCC_I3C0_FCLK_CLKDIV);

    if (true == CLOCK_IsDivHalt(clkdiv))
    {
        return 0;
    }

    switch (clksel)
    {
        case 0U:
            freq = CLOCK_GetFro12MFreq();
            break;
        case 2U:
            freq = CLOCK_GetFroHfFreq() / ((MRCC0->MRCC_FRO_HF_DIV_CLKDIV & 0xfU) + 1U);
            break;
        case 3U:
            freq = CLOCK_GetExtClkFreq();
            break;
        case 5U:
            freq = CLOCK_GetClk1MFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    return freq / ((clkdiv & 0xFFU) + 1U);
}

/* Get CTimer Clk */
/*! brief  Return Frequency of CTimer functional Clock
 *  return Frequency of CTimer functional Clock
 */
uint32_t CLOCK_GetCTimerClkFreq(uint32_t id)
{
    uint32_t freq   = 0U;
    uint32_t clksel = (0U == id) ? (MRCC0->MRCC_CTIMER0_CLKSEL) :
                                   (((1U == id)) ? (MRCC0->MRCC_CTIMER1_CLKSEL) : (MRCC0->MRCC_CTIMER2_CLKSEL));
    uint32_t clkdiv = (0U == id) ? (MRCC0->MRCC_CTIMER0_CLKDIV) :
                                   (((1U == id)) ? (MRCC0->MRCC_CTIMER1_CLKDIV) : (MRCC0->MRCC_CTIMER2_CLKDIV));

    if (true == CLOCK_IsDivHalt(clkdiv))
    {
        return 0;
    }

    switch (clksel)
    {
        case 0U:
            freq = CLOCK_GetFro12MFreq();
            break;
        case 1U:
            freq = CLOCK_GetFroHfFreq();
            break;
        case 3U:
            freq = CLOCK_GetExtClkFreq();
            break;
        case 4U:
            freq = CLOCK_GetClk16KFreq(1);
            break;
        case 5U:
            freq = CLOCK_GetClk1MFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    return freq / ((clkdiv & 0xFFU) + 1U);
}

/* Get LPI2C Clk */
/*! brief  Return Frequency of LPI2C functional Clock
 *  return Frequency of LPI2C functional Clock
 */
uint32_t CLOCK_GetLpi2cClkFreq(void)
{
    uint32_t freq   = 0U;
    uint32_t clksel = (MRCC0->MRCC_LPI2C0_CLKSEL);
    uint32_t clkdiv = (MRCC0->MRCC_LPI2C0_CLKDIV);

    if (true == CLOCK_IsDivHalt(clkdiv))
    {
        return 0;
    }

    switch (clksel)
    {
        case 0U:
            freq = CLOCK_GetFro12MFreq();
            break;
        case 2U:
            freq = CLOCK_GetFroHfFreq() / ((MRCC0->MRCC_FRO_HF_DIV_CLKDIV & 0xfU) + 1U);
            break;
        case 3U:
            freq = CLOCK_GetExtClkFreq();
            break;
        case 5U:
            freq = CLOCK_GetClk1MFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    return freq / ((clkdiv & 0xFFU) + 1U);
}

/*! brief  Return Frequency of LPSPI functional Clock
 *  return Frequency of LPSPI functional Clock
 */
uint32_t CLOCK_GetLpspiClkFreq(uint32_t id)
{
    uint32_t freq   = 0U;
    uint32_t clksel = (0U == id) ? (MRCC0->MRCC_LPSPI0_CLKSEL) : (MRCC0->MRCC_LPSPI1_CLKSEL);
    uint32_t clkdiv = (0U == id) ? (MRCC0->MRCC_LPSPI0_CLKDIV) : (MRCC0->MRCC_LPSPI1_CLKDIV);

    if (true == CLOCK_IsDivHalt(clkdiv))
    {
        return 0;
    }

    switch (clksel)
    {
        case 0U:
            freq = CLOCK_GetFro12MFreq();
            break;
        case 2U:
            freq = CLOCK_GetFroHfFreq() / ((MRCC0->MRCC_FRO_HF_DIV_CLKDIV & 0xfU) + 1U);
            break;
        case 3U:
            freq = CLOCK_GetExtClkFreq();
            break;
        case 5U:
            freq = CLOCK_GetClk1MFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    return freq / ((clkdiv & 0xFFU) + 1U);
}

/*! brief  Return Frequency of LPUART functional Clock
 *  return Frequency of LPUART functional Clock
 */
uint32_t CLOCK_GetLpuartClkFreq(uint32_t id)
{
    uint32_t freq   = 0U;
    uint32_t clksel = (0U == id) ? (MRCC0->MRCC_LPUART0_CLKSEL) :
                                   (((1U == id)) ? (MRCC0->MRCC_LPUART1_CLKSEL) : (MRCC0->MRCC_LPUART2_CLKSEL));
    uint32_t clkdiv = (0U == id) ? (MRCC0->MRCC_LPUART0_CLKDIV) :
                                   (((1U == id)) ? (MRCC0->MRCC_LPUART1_CLKDIV) : (MRCC0->MRCC_LPUART2_CLKDIV));

    if (true == CLOCK_IsDivHalt(clkdiv))
    {
        return 0;
    }

    switch (clksel)
    {
        case 0U:
            freq = CLOCK_GetFro12MFreq();
            break;
        case 2U:
            freq = CLOCK_GetFroHfFreq() / ((MRCC0->MRCC_FRO_HF_DIV_CLKDIV & 0xfU) + 1U);
            break;
        case 3U:
            freq = CLOCK_GetExtClkFreq();
            break;
        case 4U:
            freq = CLOCK_GetClk16KFreq(1);
            break;
        case 5U:
            freq = CLOCK_GetClk1MFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    return freq / ((clkdiv & 0xFFU) + 1U);
}

/*! brief  Return Frequency of LPTMR functional Clock
 *  return Frequency of LPTMR functional Clock
 */
uint32_t CLOCK_GetLptmrClkFreq(void)
{
    uint32_t freq   = 0U;
    uint32_t clksel = (MRCC0->MRCC_LPTMR0_CLKSEL);
    uint32_t clkdiv = (MRCC0->MRCC_LPTMR0_CLKDIV);

    if (true == CLOCK_IsDivHalt(clkdiv))
    {
        return 0;
    }

    switch (clksel)
    {
        case 0U:
            freq = CLOCK_GetFro12MFreq();
            break;
        case 2U:
            freq = CLOCK_GetFroHfFreq() / ((MRCC0->MRCC_FRO_HF_DIV_CLKDIV & 0xfU) + 1U);
            break;
        case 3U:
            freq = CLOCK_GetExtClkFreq();
            break;
        case 5U:
            freq = CLOCK_GetClk1MFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    return freq / ((clkdiv & 0xFFU) + 1U);
}

/*! brief  Return Frequency of OSTIMER
 *  return Frequency of OSTIMER Clock
 */
uint32_t CLOCK_GetOstimerClkFreq(void)
{
    uint32_t freq   = 0U;
    uint32_t clksel = (MRCC0->MRCC_OSTIMER0_CLKSEL);

    switch (clksel)
    {
        case 0U:
            freq = CLOCK_GetClk16KFreq(1);
            break;
        case 2U:
            freq = CLOCK_GetClk1MFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

/*! brief  Return Frequency of Adc Clock
 *  return Frequency of Adc.
 */
uint32_t CLOCK_GetAdcClkFreq(void)
{
    uint32_t freq   = 0U;
    uint32_t clksel = (MRCC0->MRCC_ADC0_CLKSEL);
    uint32_t clkdiv = (MRCC0->MRCC_ADC0_CLKDIV);

    if (true == CLOCK_IsDivHalt(clkdiv))
    {
        return 0;
    }

    switch (clksel)
    {
        case 0U:
            freq = CLOCK_GetFro12MFreq();
            break;
        case 1U:
            freq = CLOCK_GetFroHfFreq();
            break;
        case 3U:
            freq = CLOCK_GetExtClkFreq();
            break;
        case 5U:
            freq = CLOCK_GetClk1MFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    return freq / ((clkdiv & 0xFFU) + 1U);
}

/*! brief  Return Frequency of CMP Function Clock
 *  return Frequency of CMP Function.
 */
uint32_t CLOCK_GetCmpFClkFreq(uint32_t id)
{
    uint32_t freq   = 0U;
    uint32_t clksel = (0U == id) ? (MRCC0->MRCC_CMP0_RR_CLKSEL) : (MRCC0->MRCC_CMP1_RR_CLKSEL);
    uint32_t clkdiv = (0U == id) ? (MRCC0->MRCC_CMP0_FUNC_CLKDIV) : (MRCC0->MRCC_CMP1_FUNC_CLKDIV);

    if (true == CLOCK_IsDivHalt(clkdiv))
    {
        return 0;
    }

    switch (clksel)
    {
        case 0U:
            freq = CLOCK_GetFro12MFreq();
            break;
        case 2U:
            freq = CLOCK_GetFroHfFreq() / ((MRCC0->MRCC_FRO_HF_DIV_CLKDIV & 0xfU) + 1U);
            break;
        case 3U:
            freq = CLOCK_GetExtClkFreq();
            break;
        case 5U:
            freq = CLOCK_GetClk1MFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    return freq / ((clkdiv & 0xFFU) + 1U);
}

/*! brief  Return Frequency of CMP Round Robin Clock
 *  return Frequency of CMP Round Robin.
 */
uint32_t CLOCK_GetCmpRRClkFreq(uint32_t id)
{
    uint32_t freq   = 0U;
    uint32_t clksel = (0U == id) ? (MRCC0->MRCC_CMP0_RR_CLKSEL) : (MRCC0->MRCC_CMP1_RR_CLKSEL);
    uint32_t clkdiv = (0U == id) ? (MRCC0->MRCC_CMP0_RR_CLKDIV) : (MRCC0->MRCC_CMP1_RR_CLKDIV);

    if (true == CLOCK_IsDivHalt(clkdiv))
    {
        return 0;
    }

    switch (clksel)
    {
        case 0U:
            freq = CLOCK_GetFro12MFreq();
            break;
        case 2U:
            freq = CLOCK_GetFroHfFreq() / ((MRCC0->MRCC_FRO_HF_DIV_CLKDIV & 0xfU) + 1U);
            break;
        case 3U:
            freq = CLOCK_GetExtClkFreq();
            break;
        case 5U:
            freq = CLOCK_GetClk1MFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    return freq / ((clkdiv & 0xFFU) + 1U);
}

/*! brief  Return Frequency of Trace Clock
 *  return Frequency of Trace.
 */
uint32_t CLOCK_GetTraceClkFreq(void)
{
    uint32_t freq   = 0U;
    uint32_t clksel = (MRCC0->MRCC_DBG_TRACE_CLKSEL);
    uint32_t clkdiv = (MRCC0->MRCC_DBG_TRACE_CLKDIV);

    if (true == CLOCK_IsDivHalt(clkdiv))
    {
        return 0;
    }

    switch (clksel)
    {
        case 0U:
            freq = CLOCK_GetCoreSysClkFreq();
            break;
        case 1U:
            freq = CLOCK_GetClk1MFreq();
            break;
        case 2U:
            freq = CLOCK_GetClk16KFreq(1);
            break;
        default:
            freq = 0U;
            break;
    }

    return freq / ((clkdiv & 0xFFU) + 1U);
}

/*! brief  Return Frequency of CLKOUT Clock
 *  return Frequency of CLKOUT.
 */
uint32_t CLOCK_GetClkoutClkFreq(void)
{
    uint32_t freq   = 0U;
    uint32_t clksel = (MRCC0->MRCC_CLKOUT_CLKSEL);
    uint32_t clkdiv = (MRCC0->MRCC_CLKOUT_CLKDIV);

    if (true == CLOCK_IsDivHalt(clkdiv))
    {
        return 0;
    }

    switch (clksel)
    {
        case 0U:
            freq = CLOCK_GetFro12MFreq();
            break;
        case 1U:
            freq = CLOCK_GetFroHfFreq() / ((MRCC0->MRCC_FRO_HF_DIV_CLKDIV & 0xfU) + 1U);
            break;
        case 2U:
            freq = CLOCK_GetExtClkFreq();
            break;
        case 3U:
            freq = CLOCK_GetClk16KFreq(1);
            break;
        case 6U:
            freq = CLOCK_GetCoreSysClkFreq() >> 2;
            break;
        default:
            freq = 0U;
            break;
    }

    return freq / ((clkdiv & 0xFFU) + 1U);
}

/*! brief  Return Frequency of Systick Clock
 *  return Frequency of Systick.
 */
uint32_t CLOCK_GetSystickClkFreq(void)
{
    uint32_t freq   = 0U;
    uint32_t clksel = (MRCC0->MRCC_SYSTICK_CLKSEL);
    uint32_t clkdiv = (MRCC0->MRCC_SYSTICK_CLKDIV);

    if (true == CLOCK_IsDivHalt(clkdiv))
    {
        return 0;
    }

    switch (clksel)
    {
        case 0U:
            freq = CLOCK_GetCoreSysClkFreq();
            break;
        case 1U:
            freq = CLOCK_GetClk1MFreq();
            break;
        case 2U:
            freq = CLOCK_GetClk16KFreq(1);
            break;
        default:
            freq = 0U;
            break;
    }

    return freq / ((clkdiv & 0xFFU) + 1U);
}

/*! brief  Return Frequency of Systick Clock
 *  return Frequency of Systick.
 */
uint32_t CLOCK_GetWwdtClkFreq(void)
{
    uint32_t freq   = 0U;
    uint32_t clkdiv = (MRCC0->MRCC_WWDT0_CLKDIV);

    if (true == CLOCK_IsDivHalt(clkdiv))
    {
        return 0;
    }

    freq = CLOCK_GetClk1MFreq();

    return freq / ((clkdiv & 0xFFU) + 1U);
}

/**
 * @brief   Setup FROHF trim.
 * @param   config   : FROHF trim value
 * @return  returns success or fail status.
 */
status_t CLOCK_FROHFTrimConfig(firc_trim_config_t config)
{
    SCG0->FIRCTCFG = SCG_FIRCTCFG_TRIMDIV(config.trimDiv) | SCG_FIRCTCFG_TRIMSRC(config.trimSrc);

    if (kSCG_FircTrimNonUpdate == config.trimMode)
    {
        SCG0->FIRCSTAT = SCG_FIRCSTAT_TRIMFINE(config.trimFine);
    }

    /* Set trim mode. */
    SCG0->FIRCCSR = (uint32_t)config.trimMode;

    if ((SCG0->FIRCCSR & SCG_FIRCCSR_FIRCERR_MASK) == SCG_FIRCCSR_FIRCERR_MASK)
    {
        return (status_t)kStatus_Fail;
    }

    return (status_t)kStatus_Success;
}

/**
 * @brief   Setup FRO 12M trim.
 * @param   config   : FRO 12M trim value
 * @return  returns success or fail status.
 */
status_t CLOCK_FRO12MTrimConfig(sirc_trim_config_t config)
{
    SCG0->SIRCTCFG = SCG_SIRCTCFG_TRIMDIV(config.trimDiv) | SCG_SIRCTCFG_TRIMSRC(config.trimSrc);

    if (kSCG_SircTrimNonUpdate == config.trimMode)
    {
        SCG0->SIRCSTAT = SCG_SIRCSTAT_CCOTRIM(config.cltrim);
        SCG0->SIRCSTAT = SCG_SIRCSTAT_CCOTRIM(config.ccotrim);
    }

    /* Set trim mode. */
    SCG0->SIRCCSR = (uint32_t)config.trimMode;

    if ((SCG0->SIRCCSR & SCG_SIRCCSR_SIRCERR_MASK) == SCG_SIRCCSR_SIRCERR_MASK)
    {
        return (status_t)kStatus_Fail;
    }

    return (status_t)kStatus_Success;
}

/*!
 * @brief Sets the system OSC monitor mode.
 *
 * This function sets the system OSC monitor mode. The mode can be disabled,
 * it can generate an interrupt when the error is disabled, or reset when the error is detected.
 *
 * @param mode Monitor mode to set.
 */
void CLOCK_SetSysOscMonitorMode(scg_sosc_monitor_mode_t mode)
{
    uint32_t reg = SCG0->SOSCCSR;

    reg &= ~(SCG_SOSCCSR_SOSCCM_MASK | SCG_SOSCCSR_SOSCCMRE_MASK);

    reg |= (uint32_t)mode;

    SCG0->SOSCCSR = reg;
}

/*! brief Enable USB FS clock.
 * Enable USB Full Speed clock.
 */
bool CLOCK_EnableUsbfsClock(void)
{
    /* Enable USB clock */
    CLOCK_EnableClock(kCLOCK_GateUSB0);

    /* Enable FROHF with 48MHZ if it is disabled */
    if (0U == (SCG0->FIRCCSR & SCG_FIRCCSR_FIRCEN_MASK))
    {
        if (kStatus_Success != CLOCK_SetupFROHFClocking(48000000U))
        {
            return false;
        }
    }

    /* Enable CLK_48 MHz clock for peripheral use */
    SCG0->FIRCCSR |= SCG_FIRCCSR_FIRC_SCLK_PERIPH_EN_MASK;

    /* Use clk_48M for USB FS */
    CLOCK_AttachClk(kCLK_48M_to_USB0);

    return true;
}
