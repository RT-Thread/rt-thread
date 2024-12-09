/*
 * Copyright 2019-2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_smartdma.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lpc_smartdma"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

typedef void (*smartdma_func_t)(void);

#define SMARTDMA_HANDSHAKE_EVENT  0U
#define SMARTDMA_HANDSHAKE_ENABLE 1U
#define SMARTDMA_MASK_RESP        2U
#define SMARTDMA_ENABLE_AHBBUF    3U
#define SMARTDMA_ENABLE_GPISYNCH  4U

#if defined(SMARTDMA0) && !(defined(SMARTDMA))
#define SMARTDMA SMARTDMA0
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/
static smartdma_func_t *s_smartdmaApiTable;
static smartdma_callback_t s_smartdmaCallback;
static void *s_smartdmaCallbackParam;
static smartdma_param_t s_smartdmaParam;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Codes
 ******************************************************************************/
/*!
 * brief Initialize the SMARTDMA.
 *
 * param apiMemAddr The address firmware will be copied to.
 * param firmware The firmware to use.
 * param firmwareSizeByte Size of firmware.
 */
void SMARTDMA_Init(uint32_t apiMemAddr, const void *firmware, uint32_t firmwareSizeByte)
{
    SMARTDMA_InitWithoutFirmware();
    SMARTDMA_InstallFirmware(apiMemAddr, firmware, firmwareSizeByte);
}

/*!
 * brief Initialize the SMARTDMA.
 *
 * This function is similar with SMARTDMA_Init, the difference is this function
 * does not install the firmware, the firmware could be installed using
 * SMARTDMA_InstallFirmware.
 */
void SMARTDMA_InitWithoutFirmware(void)
{
    /* Clear Smart DMA RAM */
    RESET_PeripheralReset(kSMART_DMA_RST_SHIFT_RSTn);
    CLOCK_EnableClock(kCLOCK_Smartdma);
}

/*!
 * @brief Install the firmware.
 *
 * param apiMemAddr The address firmware will be copied to.
 * param firmware The firmware to use.
 * param firmwareSizeByte Size of firmware.
 */
void SMARTDMA_InstallFirmware(uint32_t apiMemAddr, const void *firmware, uint32_t firmwareSizeByte)
{
    (void)memcpy((void *)(uint8_t *)apiMemAddr, firmware, firmwareSizeByte);
    SMARTDMA->CTRL     = (0xC0DE0000U | (1U << SMARTDMA_ENABLE_GPISYNCH));
    s_smartdmaApiTable = (smartdma_func_t *)apiMemAddr;
}

/*!
 * brief Install the complete callback function..
 *
 * param callback The callback called when smartdma program finished.
 */
void SMARTDMA_InstallCallback(smartdma_callback_t callback, void *param)
{
    s_smartdmaCallback      = callback;
    s_smartdmaCallbackParam = param;
}

/*!
 * brief Boot the SMARTDMA to run program.
 *
 * param apiIndex Index of the API to call.
 * param pParam Pointer to the parameter allocated by caller.
 * param mask Value set to SMARTDMA_ARM2SMARTDMA[0:1].
 */
void SMARTDMA_Boot(uint32_t apiIndex, void *pParam, uint8_t mask)
{
    SMARTDMA->ARM2EZH = (uint32_t)(uint8_t *)pParam | (uint32_t)mask;
    SMARTDMA->BOOTADR = (uint32_t)(s_smartdmaApiTable[apiIndex]);
    SMARTDMA->CTRL    = 0xC0DE0011U | (0U << SMARTDMA_MASK_RESP) | (0U << SMARTDMA_ENABLE_AHBBUF); /* BOOT */
};

/*
 * brief Copy SMARTDMA params and Boot to run program.
 *
 * This function is similar with SMARTDMA_Boot, the only difference
 * is, this function copies the *pParam to a local variable, upper layer
 * can free the pParam's memory before the SMARTDMA execution finished,
 * for example, upper layer can define the param as a local variable.
 *
 * param apiIndex Index of the API to call.
 * param pParam Pointer to the parameter.
 * param mask Value set to SMARTDMA_ARM2SMARTDMA[0:1].
 * note Only call this function when SMARTDMA is not busy.
 */
void SMARTDMA_Boot1(uint32_t apiIndex, const smartdma_param_t *pParam, uint8_t mask)
{
    (void)memcpy(&s_smartdmaParam, pParam, sizeof(smartdma_param_t));
    SMARTDMA_Boot(apiIndex, &s_smartdmaParam, mask);
}

/*!
 * brief Deinitialize the SMARTDMA.
 */
void SMARTDMA_Deinit(void)
{
    SMARTDMA->CTRL = 0xC0DE0000U;
    CLOCK_DisableClock(kCLOCK_Smartdma);
}

/*!
 * brief Reset the SMARTDMA.
 */
void SMARTDMA_Reset(void)
{
    RESET_PeripheralReset(kSMART_DMA_RST_SHIFT_RSTn);
    SMARTDMA->CTRL = (0xC0DE0000U | (1U << SMARTDMA_ENABLE_GPISYNCH));
}

/*!
 * brief SMARTDMA IRQ.
 */
void SMARTDMA_HandleIRQ(void)
{
    if (NULL != s_smartdmaCallback)
    {
        s_smartdmaCallback(s_smartdmaCallbackParam);
    }
}
