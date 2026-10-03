/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-27     Jiao         first version
 */

#include "board.h"

FL_ErrorStatus FL_UART_GPIO_Init(UART_Type *UARTx)
{
    FL_ErrorStatus status = FL_FAIL;
    FL_GPIO_InitTypeDef GPIO_InitStruct;
    if (UARTx == UART0)
    {
        GPIO_InitStruct.pin = FL_GPIO_PIN_13;
        GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
        GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
        GPIO_InitStruct.pull = FL_DISABLE;
        GPIO_InitStruct.remapPin = FL_DISABLE;

        status = FL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.pin = FL_GPIO_PIN_14;
        GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
        GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
        GPIO_InitStruct.pull = FL_DISABLE;
        GPIO_InitStruct.remapPin = FL_DISABLE;

        status = FL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
    else if (UARTx == UART1)
    {
        GPIO_InitStruct.pin = FL_GPIO_PIN_13;
        GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
        GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
        GPIO_InitStruct.pull = FL_DISABLE;
        GPIO_InitStruct.remapPin = FL_DISABLE;

        status = FL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        GPIO_InitStruct.pin = FL_GPIO_PIN_14;
        GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
        GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
        GPIO_InitStruct.pull = FL_DISABLE;
        GPIO_InitStruct.remapPin = FL_DISABLE;

        status = FL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    }
    else if (UARTx == UART4)
    {
        GPIO_InitStruct.pin = FL_GPIO_PIN_0;
        GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
        GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
        GPIO_InitStruct.pull = FL_DISABLE;
        GPIO_InitStruct.remapPin = FL_DISABLE;

        status = FL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.pin = FL_GPIO_PIN_1;
        GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
        GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
        GPIO_InitStruct.pull = FL_DISABLE;
        GPIO_InitStruct.remapPin = FL_DISABLE;

        status = FL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
    return status;
}

FL_ErrorStatus FL_SPI_GPIO_Init(SPI_Type *SPIx)
{
    FL_ErrorStatus status = FL_FAIL;
    FL_GPIO_InitTypeDef GPIO_InitStruct;
    if (SPIx == SPI1)
    {
        GPIO_InitStruct.pin = FL_GPIO_PIN_11 | FL_GPIO_PIN_10 | FL_GPIO_PIN_9;
        GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
        GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
        GPIO_InitStruct.pull = FL_DISABLE;
        GPIO_InitStruct.remapPin = FL_DISABLE;

        status = FL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    }
    else if (SPIx == SPI2)
    {
        GPIO_InitStruct.pin = FL_GPIO_PIN_8 | FL_GPIO_PIN_10 | FL_GPIO_PIN_9;
        GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
        GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
        GPIO_InitStruct.pull = FL_DISABLE;
        GPIO_InitStruct.remapPin = FL_DISABLE;

        status = FL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    }

    return status;
}

static void CMU_PLL_ConfigDomain_SYS(uint32_t Source, uint32_t PLL_R, uint32_t PLL_DB, uint32_t PLL_O)
{
    MODIFY_REG(CMU->PLLCR, CMU_PLLCR_DB_Msk | CMU_PLLCR_REFPRSC_Msk | CMU_PLLCR_OSEL_Msk | CMU_PLLCR_INSEL_Msk,
               (PLL_DB << CMU_PLLCR_DB_Pos) | PLL_R | PLL_O | Source);
}

static void RCHFInit(uint32_t clock)
{
    switch (clock)
    {
    case FL_CMU_RCHF_FREQUENCY_16MHZ:
        FL_CMU_RCHF_WriteTrimValue(RCHF16M_TRIM);
        break;

    case FL_CMU_RCHF_FREQUENCY_24MHZ:
        FL_CMU_RCHF_WriteTrimValue(RCHF24M_TRIM);
        break;

    case FL_CMU_RCHF_FREQUENCY_32MHZ:
        FL_CMU_RCHF_WriteTrimValue(RCHF32M_TRIM);
        break;

    default: /* 8MHz */
        FL_CMU_RCHF_WriteTrimValue(RCHF8M_TRIM);
        break;
    }

    FL_CMU_RCHF_SetFrequency(clock);
    FL_CMU_RCHF_Enable();
}

void SelRCHFToPLL(uint32_t rchf, uint32_t clock)
{
    uint32_t div = FL_CMU_PLL_PSC_DIV8;

    if (clock > 64)
    {
        return;
    }

    RCHFInit(rchf);

    switch (rchf)
    {
    case FL_CMU_RCHF_FREQUENCY_16MHZ:
        div = FL_CMU_PLL_PSC_DIV16;
        break;

    case FL_CMU_RCHF_FREQUENCY_24MHZ:
        div = FL_CMU_PLL_PSC_DIV24;
        break;

    case FL_CMU_RCHF_FREQUENCY_32MHZ:
        div = FL_CMU_PLL_PSC_DIV32;
        break;

    default:
        break;
    }

    /* Flash read wait: <=24MHz 0WS, <=48MHz 1WS, >48MHz 2WS */
    if (clock <= 24)
    {
        FL_FLASH_SetReadWait(FLASH, FL_FLASH_READ_WAIT_0CYCLE);
    }
    else if (clock <= 48)
    {
        FL_FLASH_SetReadWait(FLASH, FL_FLASH_READ_WAIT_1CYCLE);
    }
    else
    {
        FL_FLASH_SetReadWait(FLASH, FL_FLASH_READ_WAIT_2CYCLE);
    }

    /* PLL out = RCHF / REFPRSC * (DB + 1), REFPRSC keeps input at 1MHz */
    CMU_PLL_ConfigDomain_SYS(FL_CMU_PLL_CLK_SOURCE_RCHF, div, clock - 1, FL_CMU_PLL_OUTPUT_X1);
    FL_CMU_PLL_Enable();

    while (FL_CMU_IsActiveFlag_PLLReady() != FL_SET);

    FL_CMU_SetAHBPrescaler(FL_CMU_AHBCLK_PSC_DIV1);
    FL_CMU_SetAPBPrescaler(FL_CMU_APBCLK_PSC_DIV1);
    FL_CMU_SetSystemClockSource(FL_CMU_SYSTEM_CLK_SOURCE_PLL);
}
