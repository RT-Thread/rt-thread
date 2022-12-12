/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2010-12-23   onelife     Initial creation for EFM32
 */

/***************************************************************************//**
 * @addtogroup efm32
 * @{
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "drv_dma.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/** DMA control block, requires proper alignment. */
#if defined (__ICCARM__)
#pragma data_alignment=256
DMA_DESCRIPTOR_TypeDef dmaControlBlock[DMA_CHAN_COUNT * 2];
#elif defined (__CC_ARM)
DMA_DESCRIPTOR_TypeDef dmaControlBlock[DMA_CHAN_COUNT * 2] __attribute__ ((aligned(256)));
#elif defined (__GNUC__)
DMA_DESCRIPTOR_TypeDef dmaControlBlock[DMA_CHAN_COUNT * 2] __attribute__ ((aligned(256)));
#else
#error Undefined toolkit, need to define alignment
#endif

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/***************************************************************************//**
 * @brief
 *    Initialize DMA hardware
 *
 * @details
 *
 * @note
 ******************************************************************************/
void rt_hw_dma_init(void)
{
    DMA_Init_TypeDef        dmaInit;

    /* Reset */
    DMA_Reset();

    dmaInit.hprot           = 0;
    dmaInit.controlBlock    = (DMA_DESCRIPTOR_TypeDef *)&dmaControlBlock;
    DMA_Init(&dmaInit);
    NVIC_SetPriority(DMA_IRQn, EFM32_IRQ_PRI_DEFAULT);
}

/***************************************************************************//**
 * @}
 ******************************************************************************/
