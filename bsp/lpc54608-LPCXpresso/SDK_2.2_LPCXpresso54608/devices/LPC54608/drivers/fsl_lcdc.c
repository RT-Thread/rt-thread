/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_lcdc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Max value of LCD_POL[PCD]. */
#define LCD_PCD_MAX                                  \
    ((LCD_POL_PCD_LO_MASK >> LCD_POL_PCD_LO_SHIFT) | \
     (LCD_POL_PCD_HI_MASK >> (LCD_POL_PCD_HI_SHIFT - LCD_POL_PCD_LO_SHIFT)))

/* Macro to contruct the LCD_POL[PCD]. */
#if (LCD_POL_PCD_LO_MASK != 0x1F)
#error LCD_POL_PCD_LO is not 5-bit. The macro LCD_POL_PCD_LO_WIDTH should be updated.
#endif
#define LCD_POL_PCD_LO_WIDTH 5U
#define LCD_POL_PCD(pcd) (LCD_POL_PCD_LO(pcd) | LCD_POL_PCD_HI((pcd) >> LCD_POL_PCD_LO_WIDTH))

/* Cursor interrupt. */
#define LCDC_CURSOR_INT_MASK LCD_CRSR_INTMSK_CRSRIM_MASK

/* Interrupts except cursor interrupt. */
#define LCDC_NORMAL_INT_MASK \
    (LCD_INTMSK_FUFIM_MASK | LCD_INTMSK_LNBUIM_MASK | LCD_INTMSK_VCOMPIM_MASK | LCD_INTMSK_BERIM_MASK)

/* Detect the cursor interrupt and normal interrupt bits overlap. */
#if (LCDC_CURSOR_INT_MASK & LCDC_NORMAL_INT_MASK)
#error Cursor interrupt and normal interrupt overlap. The driver should be updated.
#endif

/* The max cursor clip value. */
#define LCDC_CLIP_MAX (LCD_CRSR_CLIP_CRSRCLIPX_MASK >> LCD_CRSR_CLIP_CRSRCLIPX_SHIFT)

/*******************************************************************************
 * Variables
 ******************************************************************************/
static LCD_Type *const s_lcdBases[] = LCD_BASE_PTRS;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
static const clock_ip_name_t s_lcdClocks[] = LCD_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
static const reset_ip_name_t s_lcdResets[] = LCD_RSTS;

/*******************************************************************************
* Prototypes
******************************************************************************/

/*!
 * @brief Gets the LCD instance according to the LCD base
 *
 * @param base LCD peripheral base address.
 * @return LCD instance.
 */
static uint32_t LCDC_GetInstance(LCD_Type *base);

/*!
 * @brief Calculate the clock divider to generate desired panel clock.
 *
 * @param config Pointer to the LCD configuration.
 * @param srcClock_Hz The LCD input clock (LCDCLK) frequency in Hz.
 * @param divider The divider result.
 * @return Return false if no divider available to generate the desired clock,
 * otherwise return true;
 */
static bool LCDC_GetClockDivider(const lcdc_config_t *config, uint32_t srcClock_Hz, uint32_t *divider);

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t LCDC_GetInstance(LCD_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_lcdBases); instance++)
    {
        if (s_lcdBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_lcdBases));

    return instance;
}

static bool LCDC_GetClockDivider(const lcdc_config_t *config, uint32_t srcClock_Hz, uint32_t *divider)
{
    uint16_t cpl;
    uint32_t pcd;

    *divider = 0U;

    /* Find the PCD. */
    pcd = (srcClock_Hz + (config->panelClock_Hz / 2U)) / config->panelClock_Hz;

    if (pcd <= 1U)
    {
        if (kLCDC_DisplayTFT == config->display)
        {
            pcd = 0U;
            *divider = LCD_POL_BCD_MASK;
        }
        else
        {
            return false;
        }
    }
    else
    {
        pcd -= 2U;

        /* Verify the PCD value. */
        if (pcd > LCD_PCD_MAX)
        {
            return false;
        }

        if (((kLCDC_DisplaySingleColorSTN8Bit == config->display) && (pcd < 1U)) ||
            ((kLCDC_DisplayDualColorSTN8Bit == config->display) && (pcd < 4U)) ||
            ((kLCDC_DisplaySingleMonoSTN4Bit == config->display) && (pcd < 2U)) ||
            ((kLCDC_DisplaySingleMonoSTN8Bit == config->display) && (pcd < 8U)) ||
            ((kLCDC_DisplayDualMonoSTN4Bit == config->display) && (pcd < 8U)) ||
            ((kLCDC_DisplayDualMonoSTN8Bit == config->display) && (pcd < 14U)))
        {
            return false;
        }
    }

    if (config->display & LCD_CTRL_LCDTFT_MASK)
    {
        /* TFT panel. */
        cpl = config->ppl - 1U;
    }
    else
    {
        if (config->display & LCD_CTRL_LCDBW_MASK)
        {
            if (config->display & LCD_CTRL_LCDMONO8_MASK)
            {
                /* 8-bit monochrome STN panel. */
                cpl = (config->ppl / 8U) - 1U;
            }
            else
            {
                /* 4-bit monochrome STN panel. */
                cpl = (config->ppl / 4U) - 1U;
            }
        }
        else
        {
            /* Color STN panel. */
            cpl = ((config->ppl * 3U) / 8U) - 1U;
        }
    }

    *divider |= (LCD_POL_CPL(cpl) | LCD_POL_PCD(pcd));

    return true;
}

status_t LCDC_Init(LCD_Type *base, const lcdc_config_t *config, uint32_t srcClock_Hz)
{
    assert(config);
    assert(srcClock_Hz);
    assert((config->ppl & 0xFU) == 0U);
    assert((config->upperPanelAddr & 0x07U) == 0U);
    assert((config->lowerPanelAddr & 0x07U) == 0U);

    uint32_t reg;
    uint32_t divider;
    uint32_t instance;

    /* Verify the clock here. */
    if (!LCDC_GetClockDivider(config, srcClock_Hz, &divider))
    {
        return kStatus_InvalidArgument;
    }

    instance = LCDC_GetInstance(base);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_EnableClock(s_lcdClocks[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Reset the module */
    RESET_PeripheralReset(s_lcdResets[instance]);

    /* Set register CTRL. */
    reg = base->CTRL & (LCD_CTRL_LCDVCOMP_MASK | LCD_CTRL_WATERMARK_MASK);
    reg |= (uint32_t)(config->dataFormat) | (uint32_t)(config->display) | LCD_CTRL_LCDBPP(config->bpp);

    if (config->swapRedBlue)
    {
        reg |= LCD_CTRL_BGR_MASK;
    }

    base->CTRL = reg;

    /* Clean pending interrupts and disable all interrupts. */
    base->INTCLR = LCDC_NORMAL_INT_MASK;
    base->CRSR_INTCLR = LCDC_CURSOR_INT_MASK;
    base->INTMSK = 0U;
    base->CRSR_INTMSK = 0U;

    /* Configure timing. */
    base->TIMH = LCD_TIMH_PPL((config->ppl / 16U) - 1U) | LCD_TIMH_HSW(config->hsw - 1U) |
                 LCD_TIMH_HFP(config->hfp - 1U) | LCD_TIMH_HBP(config->hbp - 1U);

    base->TIMV = LCD_TIMV_LPP(config->lpp - 1U) | LCD_TIMV_VSW(config->vsw - 1U) | LCD_TIMV_VFP(config->vfp - 1U) |
                 LCD_TIMV_VBP(config->vbp - 1U);

    base->POL = (uint32_t)(config->polarityFlags) | LCD_POL_ACB(config->acBiasFreq - 1U) | divider;

    /* Line end configuration. */
    if (config->enableLineEnd)
    {
        base->LE = LCD_LE_LED(config->lineEndDelay - 1U) | LCD_LE_LEE_MASK;
    }
    else
    {
        base->LE = 0U;
    }

    /* Set panel frame base address. */
    base->UPBASE = config->upperPanelAddr;
    base->LPBASE = config->lowerPanelAddr;

    return kStatus_Success;
}

void LCDC_Deinit(LCD_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_EnableClock(s_lcdClocks[LCDC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

void LCDC_GetDefaultConfig(lcdc_config_t *config)
{
    config->panelClock_Hz = 0U;
    config->ppl = 0U;
    config->hsw = 0U;
    config->hfp = 0U;
    config->hbp = 0U;
    config->lpp = 0U;
    config->vsw = 0U;
    config->vfp = 0U;
    config->vbp = 0U;
    config->acBiasFreq = 1U;
    config->polarityFlags = 0U;
    config->enableLineEnd = false;
    config->lineEndDelay = 0U;
    config->upperPanelAddr = 0U;
    config->lowerPanelAddr = 0U;
    config->bpp = kLCDC_1BPP;
    config->dataFormat = kLCDC_LittleEndian;
    config->swapRedBlue = false;
    config->display = kLCDC_DisplayTFT;
}

void LCDC_SetPanelAddr(LCD_Type *base, lcdc_panel_t panel, uint32_t addr)
{
    /* The base address must be doubleword aligned. */
    assert((addr & 0x07U) == 0U);

    if (kLCDC_UpperPanel == panel)
    {
        base->UPBASE = addr;
    }
    else
    {
        base->LPBASE = addr;
    }
}

void LCDC_SetPalette(LCD_Type *base, const uint32_t *palette, uint8_t count_words)
{
    assert(count_words <= ARRAY_SIZE(base->PAL));

    uint32_t i;

    for (i = 0; i < count_words; i++)
    {
        base->PAL[i] = palette[i];
    }
}

void LCDC_EnableInterrupts(LCD_Type *base, uint32_t mask)
{
    uint32_t reg;

    reg = mask & LCDC_CURSOR_INT_MASK;
    if (reg)
    {
        base->CRSR_INTMSK |= reg;
    }

    reg = mask & LCDC_NORMAL_INT_MASK;
    if (reg)
    {
        base->INTMSK |= reg;
    }
}

void LCDC_DisableInterrupts(LCD_Type *base, uint32_t mask)
{
    uint32_t reg;

    reg = mask & LCDC_CURSOR_INT_MASK;
    if (reg)
    {
        base->CRSR_INTMSK &= ~reg;
    }

    reg = mask & LCDC_NORMAL_INT_MASK;
    if (reg)
    {
        base->INTMSK &= ~reg;
    }
}

uint32_t LCDC_GetInterruptsPendingStatus(LCD_Type *base)
{
    uint32_t reg;

    reg = base->CRSR_INTRAW;
    reg |= base->INTRAW;

    return reg;
}

uint32_t LCDC_GetEnabledInterruptsPendingStatus(LCD_Type *base)
{
    uint32_t reg;

    reg = base->CRSR_INTSTAT;
    reg |= base->INTSTAT;

    return reg;
}

void LCDC_ClearInterruptsStatus(LCD_Type *base, uint32_t mask)
{
    uint32_t reg;

    reg = mask & LCDC_CURSOR_INT_MASK;
    if (reg)
    {
        base->CRSR_INTCLR = reg;
    }

    reg = mask & LCDC_NORMAL_INT_MASK;
    if (reg)
    {
        base->INTCLR = reg;
    }
}

void LCDC_SetCursorConfig(LCD_Type *base, const lcdc_cursor_config_t *config)
{
    assert(config);

    uint32_t i;

    base->CRSR_CFG = LCD_CRSR_CFG_CRSRSIZE(config->size) | LCD_CRSR_CFG_FRAMESYNC(config->syncMode);

    /* Set position. */
    LCDC_SetCursorPosition(base, 0, 0);

    /* Palette. */
    base->CRSR_PAL0 = ((uint32_t)config->palette0.red << LCD_CRSR_PAL0_RED_SHIFT) |
                      ((uint32_t)config->palette0.blue << LCD_CRSR_PAL0_BLUE_SHIFT) |
                      ((uint32_t)config->palette0.green << LCD_CRSR_PAL0_GREEN_SHIFT);
    base->CRSR_PAL1 = ((uint32_t)config->palette1.red << LCD_CRSR_PAL1_RED_SHIFT) |
                      ((uint32_t)config->palette1.blue << LCD_CRSR_PAL1_BLUE_SHIFT) |
                      ((uint32_t)config->palette1.green << LCD_CRSR_PAL1_GREEN_SHIFT);

    /* Image of cursors. */
    if (kLCDC_CursorSize64 == config->size)
    {
        assert(config->image[0]);
        LCDC_SetCursorImage(base, config->size, 0, config->image[0]);
    }
    else
    {
        for (i = 0; i < LCDC_CURSOR_COUNT; i++)
        {
            if (config->image[i])
            {
                LCDC_SetCursorImage(base, config->size, i, config->image[i]);
            }
        }
    }
}

void LCDC_CursorGetDefaultConfig(lcdc_cursor_config_t *config)
{
    uint32_t i;

    config->size = kLCDC_CursorSize32;
    config->syncMode = kLCDC_CursorAsync;
    config->palette0.red = 0U;
    config->palette0.green = 0U;
    config->palette0.blue = 0U;
    config->palette1.red = 255U;
    config->palette1.green = 255U;
    config->palette1.blue = 255U;

    for (i = 0; i < LCDC_CURSOR_COUNT; i++)
    {
        config->image[i] = (uint32_t *)0;
    }
}

void LCDC_SetCursorPosition(LCD_Type *base, int32_t positionX, int32_t positionY)
{
    uint32_t clipX;
    uint32_t clipY;

    if (positionX < 0)
    {
        clipX = -positionX;
        positionX = 0U;

        /* If clip value too large, set to the max value. */
        if (clipX > LCDC_CLIP_MAX)
        {
            clipX = LCDC_CLIP_MAX;
        }
    }
    else
    {
        clipX = 0U;
    }

    if (positionY < 0)
    {
        clipY = -positionY;
        positionY = 0U;

        /* If clip value too large, set to the max value. */
        if (clipY > LCDC_CLIP_MAX)
        {
            clipY = LCDC_CLIP_MAX;
        }
    }
    else
    {
        clipY = 0U;
    }

    base->CRSR_CLIP = LCD_CRSR_CLIP_CRSRCLIPX(clipX) | LCD_CRSR_CLIP_CRSRCLIPY(clipY);
    base->CRSR_XY = LCD_CRSR_XY_CRSRX(positionX) | LCD_CRSR_XY_CRSRY(positionY);
}

void LCDC_SetCursorImage(LCD_Type *base, lcdc_cursor_size_t size, uint8_t index, const uint32_t *image)
{
    uint32_t regStart;
    uint32_t i;
    uint32_t len;

    if (kLCDC_CursorSize64 == size)
    {
        regStart = 0U;
        len = LCDC_CURSOR_IMG_64X64_WORDS;
    }
    else
    {
        regStart = index * LCDC_CURSOR_IMG_32X32_WORDS;
        len = LCDC_CURSOR_IMG_32X32_WORDS;
    }

    for (i = 0U; i < len; i++)
    {
        base->CRSR_IMG[regStart + i] = image[i];
    }
}
