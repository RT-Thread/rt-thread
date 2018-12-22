/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-17     ZYH          first implementation
 */

#include "drv_sdram.h"
#include <rtthread.h>
#ifdef BSP_USING_SDRAM
SDRAM_HandleTypeDef hsdram;
static void BSP_SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *Command);
/* FMC initialization function */
void MX_FMC_Init(void)
{
    FMC_SDRAM_TimingTypeDef SdramTiming;
    FMC_SDRAM_CommandTypeDef command;
    /** Perform the SDRAM1 memory initialization sequence
    */
    hsdram.Instance = FMC_SDRAM_DEVICE;
    /* hsdram.Init */
    hsdram.Init.SDBank             = FMC_SDRAM_BANK1;
    hsdram.Init.ColumnBitsNumber   = FMC_SDRAM_COLUMN_BITS_NUM_8;
    hsdram.Init.RowBitsNumber      = FMC_SDRAM_ROW_BITS_NUM_12;
    hsdram.Init.MemoryDataWidth    = FMC_SDRAM_MEM_BUS_WIDTH_32;
    hsdram.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
    hsdram.Init.CASLatency         = FMC_SDRAM_CAS_LATENCY_2;
    hsdram.Init.WriteProtection    = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
    hsdram.Init.SDClockPeriod      = FMC_SDRAM_CLOCK_PERIOD_2;
    hsdram.Init.ReadBurst          = FMC_SDRAM_RBURST_ENABLE;
    hsdram.Init.ReadPipeDelay      = FMC_SDRAM_RPIPE_DELAY_0;
    /* SdramTiming */
    SdramTiming.LoadToActiveDelay = 2;
    SdramTiming.ExitSelfRefreshDelay = 6;
    SdramTiming.SelfRefreshTime = 4;
    SdramTiming.RowCycleDelay = 6;
    SdramTiming.WriteRecoveryTime = 2;
    SdramTiming.RPDelay = 2;
    SdramTiming.RCDDelay = 2;

    HAL_SDRAM_Init(&hsdram, &SdramTiming);
    BSP_SDRAM_Initialization_Sequence(&hsdram, &command);
}

static uint32_t FMC_Initialized = 0;

static void HAL_FMC_MspInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    if (FMC_Initialized)
    {
        return;
    }
    FMC_Initialized = 1;
    /* Peripheral clock enable */
    __HAL_RCC_FMC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOI_CLK_ENABLE();
    /** FMC GPIO Configuration
    PE1   ------> FMC_NBL1
    PE0   ------> FMC_NBL0
    PG15   ------> FMC_SDNCAS
    PD0   ------> FMC_D2
    PI4   ------> FMC_NBL2
    PD1   ------> FMC_D3
    PI3   ------> FMC_D27
    PI2   ------> FMC_D26
    PF0   ------> FMC_A0
    PI5   ------> FMC_NBL3
    PI7   ------> FMC_D29
    PI10   ------> FMC_D31
    PI6   ------> FMC_D28
    PH15   ------> FMC_D23
    PI1   ------> FMC_D25
    PF1   ------> FMC_A1
    PI9   ------> FMC_D30
    PH13   ------> FMC_D21
    PH14   ------> FMC_D22
    PI0   ------> FMC_D24
    PF2   ------> FMC_A2
    PF3   ------> FMC_A3
    PG8   ------> FMC_SDCLK
    PF4   ------> FMC_A4
    PH5   ------> FMC_SDNWE
    PH3   ------> FMC_SDNE0
    PF5   ------> FMC_A5
    PH2   ------> FMC_SDCKE0
    PD15   ------> FMC_D1
    PD10   ------> FMC_D15
    PD14   ------> FMC_D0
    PD9   ------> FMC_D14
    PD8   ------> FMC_D13
    PF12   ------> FMC_A6
    PG1   ------> FMC_A11
    PF15   ------> FMC_A9
    PH12   ------> FMC_D20
    PF13   ------> FMC_A7
    PG0   ------> FMC_A10
    PE8   ------> FMC_D5
    PG5   ------> FMC_BA1
    PG4   ------> FMC_BA0
    PH9   ------> FMC_D17
    PH11   ------> FMC_D19
    PF14   ------> FMC_A8
    PF11   ------> FMC_SDNRAS
    PE9   ------> FMC_D6
    PE11   ------> FMC_D8
    PE14   ------> FMC_D11
    PH8   ------> FMC_D16
    PH10   ------> FMC_D18
    PE7   ------> FMC_D4
    PE10   ------> FMC_D7
    PE12   ------> FMC_D9
    PE15   ------> FMC_D12
    PE13   ------> FMC_D10
    */
    /* GPIO_InitStruct */
    GPIO_InitStruct.Pin = GPIO_PIN_1 | GPIO_PIN_0 | GPIO_PIN_8 | GPIO_PIN_9
                          | GPIO_PIN_11 | GPIO_PIN_14 | GPIO_PIN_7 | GPIO_PIN_10
                          | GPIO_PIN_12 | GPIO_PIN_15 | GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    /* GPIO_InitStruct */
    GPIO_InitStruct.Pin = GPIO_PIN_15 | GPIO_PIN_8 | GPIO_PIN_1 | GPIO_PIN_0
                          | GPIO_PIN_5 | GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    /* GPIO_InitStruct */
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_15 | GPIO_PIN_10
                          | GPIO_PIN_14 | GPIO_PIN_9 | GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* GPIO_InitStruct */
    GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_5
                          | GPIO_PIN_7 | GPIO_PIN_10 | GPIO_PIN_6 | GPIO_PIN_1
                          | GPIO_PIN_9 | GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    /* GPIO_InitStruct */
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3
                          | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_12 | GPIO_PIN_15
                          | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    /* GPIO_InitStruct */
    GPIO_InitStruct.Pin = GPIO_PIN_15 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_5
                          | GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_12 | GPIO_PIN_9
                          | GPIO_PIN_11 | GPIO_PIN_8 | GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
}

void HAL_SDRAM_MspInit(SDRAM_HandleTypeDef *sdramHandle)
{
    HAL_FMC_MspInit();
}

static uint32_t FMC_DeInitialized = 0;

static void HAL_FMC_MspDeInit(void)
{
    if (FMC_DeInitialized)
    {
        return;
    }
    FMC_DeInitialized = 1;
    /* Peripheral clock enable */
    __HAL_RCC_FMC_CLK_DISABLE();

    /** FMC GPIO Configuration
    PE1   ------> FMC_NBL1
    PE0   ------> FMC_NBL0
    PG15   ------> FMC_SDNCAS
    PD0   ------> FMC_D2
    PI4   ------> FMC_NBL2
    PD1   ------> FMC_D3
    PI3   ------> FMC_D27
    PI2   ------> FMC_D26
    PF0   ------> FMC_A0
    PI5   ------> FMC_NBL3
    PI7   ------> FMC_D29
    PI10   ------> FMC_D31
    PI6   ------> FMC_D28
    PH15   ------> FMC_D23
    PI1   ------> FMC_D25
    PF1   ------> FMC_A1
    PI9   ------> FMC_D30
    PH13   ------> FMC_D21
    PH14   ------> FMC_D22
    PI0   ------> FMC_D24
    PF2   ------> FMC_A2
    PF3   ------> FMC_A3
    PG8   ------> FMC_SDCLK
    PF4   ------> FMC_A4
    PH5   ------> FMC_SDNWE
    PH3   ------> FMC_SDNE0
    PF5   ------> FMC_A5
    PH2   ------> FMC_SDCKE0
    PD15   ------> FMC_D1
    PD10   ------> FMC_D15
    PD14   ------> FMC_D0
    PD9   ------> FMC_D14
    PD8   ------> FMC_D13
    PF12   ------> FMC_A6
    PG1   ------> FMC_A11
    PF15   ------> FMC_A9
    PH12   ------> FMC_D20
    PF13   ------> FMC_A7
    PG0   ------> FMC_A10
    PE8   ------> FMC_D5
    PG5   ------> FMC_BA1
    PG4   ------> FMC_BA0
    PH9   ------> FMC_D17
    PH11   ------> FMC_D19
    PF14   ------> FMC_A8
    PF11   ------> FMC_SDNRAS
    PE9   ------> FMC_D6
    PE11   ------> FMC_D8
    PE14   ------> FMC_D11
    PH8   ------> FMC_D16
    PH10   ------> FMC_D18
    PE7   ------> FMC_D4
    PE10   ------> FMC_D7
    PE12   ------> FMC_D9
    PE15   ------> FMC_D12
    PE13   ------> FMC_D10
    */

    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_1 | GPIO_PIN_0 | GPIO_PIN_8 | GPIO_PIN_9
                    | GPIO_PIN_11 | GPIO_PIN_14 | GPIO_PIN_7 | GPIO_PIN_10
                    | GPIO_PIN_12 | GPIO_PIN_15 | GPIO_PIN_13);

    HAL_GPIO_DeInit(GPIOG, GPIO_PIN_15 | GPIO_PIN_8 | GPIO_PIN_1 | GPIO_PIN_0
                    | GPIO_PIN_5 | GPIO_PIN_4);

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_15 | GPIO_PIN_10
                    | GPIO_PIN_14 | GPIO_PIN_9 | GPIO_PIN_8);

    HAL_GPIO_DeInit(GPIOI, GPIO_PIN_4 | GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_5
                    | GPIO_PIN_7 | GPIO_PIN_10 | GPIO_PIN_6 | GPIO_PIN_1
                    | GPIO_PIN_9 | GPIO_PIN_0);

    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3
                    | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_12 | GPIO_PIN_15
                    | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_11);

    HAL_GPIO_DeInit(GPIOH, GPIO_PIN_15 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_5
                    | GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_12 | GPIO_PIN_9
                    | GPIO_PIN_11 | GPIO_PIN_8 | GPIO_PIN_10);
}

void HAL_SDRAM_MspDeInit(SDRAM_HandleTypeDef *sdramHandle)
{
    HAL_FMC_MspDeInit();
}

static void BSP_SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *Command)
{
    __IO uint32_t tmpmrd = 0;
    int delay = 216000/3;
    /* Step 3:  Configure a clock configuration enable command */
    Command->CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
    Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
    Command->AutoRefreshNumber = 1;
    Command->ModeRegisterDefinition = 0;

    /* Send the command */
    HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);

    /* Step 4: Insert 100 us minimum delay */
    /* Inserted delay is equal to 1 ms due to systick time base unit (ms) */
    while(delay)
    {
        delay--;
    }

    /* Step 5: Configure a PALL (precharge all) command */
    Command->CommandMode = FMC_SDRAM_CMD_PALL;
    Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
    Command->AutoRefreshNumber = 1;
    Command->ModeRegisterDefinition = 0;

    /* Send the command */
    HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);

    /* Step 6 : Configure a Auto-Refresh command */
    Command->CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
    Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
    Command->AutoRefreshNumber = 8;
    Command->ModeRegisterDefinition = 0;

    /* Send the command */
    HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);

    /* Step 7: Program the external memory mode register */
    tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1          |
             SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
             SDRAM_MODEREG_CAS_LATENCY_2           |
             SDRAM_MODEREG_OPERATING_MODE_STANDARD |
             SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

    Command->CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
    Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
    Command->AutoRefreshNumber = 1;
    Command->ModeRegisterDefinition = tmpmrd;

    /* Send the command */
    HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);

    /* Step 8: Set the refresh rate counter */
    /* (15.62 us x Freq) - 20 */
    /* Set the device refresh counter */
    hsdram->Instance->SDRTR |= ((uint32_t)((1292) << 1));
}
int bsp_sdram_hw_init(void)
{
    MX_FMC_Init();
    return 0;
}
#endif
