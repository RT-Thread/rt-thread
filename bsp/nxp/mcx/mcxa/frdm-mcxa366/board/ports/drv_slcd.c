/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 * Copyright 2024-2025 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Board-level SLCD helper for FRDM-MCXA366, built on NXP fsl_slcd.
 *
 * Segment mapping (8 bits per front-plane pair in num_matrix):
 *   7 6 5 4 | 3 2 1 0
 *   E G F P | D C B A
 *
 * Front plane: digit6..digit1 use LCD_P27/P26 .. LCD_P17/P16
 * Back plane:  COM1..COM4 use LCD_P28..LCD_P31
 */

#include <rtthread.h>

#ifdef BSP_USING_SLCD

#include "drv_slcd.h"
#include "pin_mux.h"
#include "fsl_clock.h"
#include "fsl_reset.h"
#include "fsl_slcd.h"

#define BOARD_SLCD LCD0

#define SEGA 0x0001u
#define SEGB 0x0002u
#define SEGC 0x0004u
#define SEGD 0x0008u
#define SEGP 0x0100u
#define SEGF 0x0200u
#define SEGG 0x0400u
#define SEGE 0x0800u

/* Low byte -> pin_lo (A/B/C/D), high byte -> pin_hi (P/F/G/E). */
static const uint16_t num_matrix[] = {
    SEGA | SEGB | SEGC | SEGD | SEGE | SEGF,                 /* 0 */
    SEGB | SEGC,                                           /* 1 */
    SEGA | SEGB | SEGG | SEGE | SEGD,                       /* 2 */
    SEGA | SEGB | SEGG | SEGC | SEGD,                       /* 3 */
    SEGF | SEGG | SEGB | SEGC,                             /* 4 */
    SEGA | SEGF | SEGG | SEGC | SEGD,                       /* 5 */
    SEGA | SEGF | SEGE | SEGD | SEGC | SEGG,                /* 6 */
    SEGA | SEGB | SEGC,                                    /* 7 */
    SEGA | SEGB | SEGC | SEGD | SEGE | SEGF | SEGG,         /* 8 */
    SEGA | SEGF | SEGG | SEGB | SEGC | SEGD,                /* 9 */
    0                                                      /* space / blank */
};

/* digit 1..6 -> low front-plane pin (high pin is low+1) */
static const uint8_t digit_pin_lo[] = { 0, 16, 18, 20, 22, 24, 26 };

/* SLCD_Px point -> front-plane pin (phase A / SEGP) */
static const uint8_t point_pin[] = {
    23, /* P1 */
    21, /* P2 */
    19, /* P3 */
    25, /* P4 */
    27, /* P5 */
    17, /* P6 */
};

static rt_bool_t g_slcd_inited = RT_FALSE;

static void slcd_set_digit_segments(uint8_t digit, uint16_t seg)
{
    uint8_t pin_lo;

    if ((digit < 1U) || (digit > 6U))
    {
        return;
    }

    pin_lo = digit_pin_lo[digit];
    SLCD_SetFrontPlaneSegments(BOARD_SLCD, pin_lo, (uint8_t)(seg & 0xFFU));
    SLCD_SetFrontPlaneSegments(BOARD_SLCD, pin_lo + 1U, (uint8_t)((seg >> 8) & 0xFFU));
}

int rt_hw_slcd_init(void)
{
    slcd_config_t config;

    if (g_slcd_inited)
    {
        return RT_EOK;
    }

    BOARD_InitSLCDPins();

    /* SLCD function clock on MCXA366. */
    CLOCK_SetupFRO16KClocking(kCLKE_16K_COREMAIN);
    RESET_ReleasePeripheralReset(kSLCD0_RST_SHIFT_RSTn);

    SLCD_GetDefaultConfig(&config);
    config.dutyCycle = kSLCD_1Div4DutyCycle;
    config.slcdLowPinEnabled = 0xFFFF0000U;   /* LCD_P16~P31 */
    config.slcdHighPinEnabled = 0U;
    config.backPlaneLowPin = 0xF0000000U;     /* LCD_P28~P31 */
    config.backPlaneHighPin = 0U;
    config.faultConfig = RT_NULL;
    SLCD_Init(BOARD_SLCD, &config);

    SLCD_SetBackPlanePhase(BOARD_SLCD, 28U, kSLCD_PhaseAActivate);
    SLCD_SetBackPlanePhase(BOARD_SLCD, 29U, kSLCD_PhaseBActivate);
    SLCD_SetBackPlanePhase(BOARD_SLCD, 30U, kSLCD_PhaseCActivate);
    SLCD_SetBackPlanePhase(BOARD_SLCD, 31U, kSLCD_PhaseDActivate);

    SLCD_StartDisplay(BOARD_SLCD);

    g_slcd_inited = RT_TRUE;
    return RT_EOK;
}

void rt_hw_slcd_display_all(void)
{
    uint8_t pin;

    for (pin = 16U; pin <= 27U; pin++)
    {
        SLCD_SetFrontPlaneSegments(BOARD_SLCD, pin,
                                   (uint8_t)(kSLCD_PhaseAActivate | kSLCD_PhaseBActivate |
                                             kSLCD_PhaseCActivate | kSLCD_PhaseDActivate));
    }
}

void rt_hw_slcd_clear(void)
{
    uint8_t pin;

    for (pin = 16U; pin <= 27U; pin++)
    {
        SLCD_SetFrontPlaneSegments(BOARD_SLCD, pin, (uint8_t)kSLCD_NoPhaseActivate);
    }
}

void rt_hw_slcd_display_num(uint8_t digit, uint8_t num)
{
    uint16_t seg = (num <= 9U) ? num_matrix[num] : num_matrix[10];

    slcd_set_digit_segments(digit, seg);
}

void rt_hw_slcd_display_string(const char *str)
{
    uint8_t digit;
    uint8_t num;
    uint8_t points = 0U;

    if (str == RT_NULL)
    {
        return;
    }

    for (digit = 6U; digit >= 1U; digit--)
    {
        while ((*str == ':') || (*str == '.'))
        {
            if (*str == ':')
            {
                points |= SLCD_COLON;
            }
            else
            {
                points |= SLCD_DOT;
            }
            str++;
        }

        if (*str == '\0')
        {
            num = 10U;
        }
        else if (*str == ' ')
        {
            num = 10U;
            str++;
        }
        else
        {
            num = (uint8_t)(*str - '0');
            str++;
            if (num > 9U)
            {
                num = 10U;
            }
        }
        rt_hw_slcd_display_num(digit, num);
        if (digit == 1U)
        {
            break;
        }
    }

    if (points != 0U)
    {
        rt_hw_slcd_display_point(points);
    }
}

void rt_hw_slcd_display_time(uint8_t hour, uint8_t minute)
{
    char buf[8];

    if (hour > 99U)
    {
        hour = 99U;
    }
    if (minute > 99U)
    {
        minute = 99U;
    }

    rt_snprintf(buf, sizeof(buf), "%02u:%02u", hour, minute);
    rt_hw_slcd_clear();
    rt_hw_slcd_display_string(buf);
}

void rt_hw_slcd_display_point(uint8_t point)
{
    uint8_t i;

    for (i = 0U; i < 6U; i++)
    {
        if (point & (1U << i))
        {
            SLCD_SetFrontPlaneOnePhase(BOARD_SLCD, point_pin[i], kSLCD_PhaseAIndex, true);
        }
    }
}

#endif /* BSP_USING_SLCD */
