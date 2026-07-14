/*
 * @copyright (C) 2026 Nuvoton Technology Corp. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __DRV_LLSI_H__
#define __DRV_LLSI_H__
#include "NuMicro.h"

typedef enum
{
    evR,
    evG,
    evB,
    evCNT
} E_COLOR;

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} S_LLSI_RGB;

/* Default config for serial_configure structure */
#define DEFAULT_PIXEL_COUNT  8             /* Number of LEDs in the strip */
#define NU_LLSI_CONFIG_DEFAULT                                           \
{                                                                        \
    .u32LLSIMode = LLSI_MODE_PDMA,         /*!< Transfer mode */         \
    .u32OutputFormat = LLSI_FORMAT_GRB,    /*!< Output format */         \
    .sTimeInfo = {                         /*!< Timing information */    \
        .u32BusClock         = __HSI,      /*!< Bus clock in HZ */       \
        .u32TransferTimeNsec = 1200,       /*!< Transfer time in nsec */ \
        .u32T0HTimeNsec      = 300,        /*!< T0H time in nsec */      \
        .u32T1HTimeNsec      = 900,        /*!< T1H time in nsec */      \
        .u32ResetTimeNsec    = 50000       /*!< Reset time in nsec */    \
    },                                                                   \
    .u32PCNT = DEFAULT_PIXEL_COUNT,        /*!< Frame size */            \
    .u32IDOS = LLSI_IDLE_LOW,              /*!< Idle output state */     \
}

typedef void (*nu_llsi_event_handler_t)(void *pvData, uint32_t u32EvtMask);
#endif /* __DRV_LLSI_H__ */