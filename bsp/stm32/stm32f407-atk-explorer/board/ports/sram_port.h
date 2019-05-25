/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-05-25     zylx         The first version for STM32F4xx
 */

#ifndef __SDRAM_PORT_H__
#define __SDRAM_PORT_H__

/* parameters for sdram peripheral */
#define SRAM_BANK_ADDR                  ((uint32_t)0x68000000)
/* data width: 8, 16, 32 */
#define SRAM_DATA_WIDTH                 16
/* sram size */
#define SRAM_SIZE                       ((uint32_t)0x100000)

#ifndef SRAM_CONFIG
#define SRAM_CONFIG                                                     \
    {                                                                   \
        .Instance  = FMC_NORSRAM_DEVICE,                                \
        .Extended  = FMC_NORSRAM_EXTENDED_DEVICE,                       \
        .Init.NSBank             = FSMC_NORSRAM_BANK3,                  \
        .Init.DataAddressMux     = FSMC_DATA_ADDRESS_MUX_DISABLE,       \
        .Init.MemoryType         = FSMC_MEMORY_TYPE_SRAM,               \
        .Init.MemoryDataWidth    = FMC_NORSRAM_MEM_BUS_WIDTH_16,        \
        .Init.BurstAccessMode    = FSMC_BURST_ACCESS_MODE_DISABLE,      \
        .Init.WriteOperation     = FSMC_WRITE_OPERATION_ENABLE,         \
        .Init.WaitSignal         = FSMC_WAIT_SIGNAL_DISABLE,            \
        .Init.WaitSignalActive   = FSMC_WAIT_TIMING_BEFORE_WS,          \
        .Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW,       \
        .Init.WrapMode           = FSMC_WRAP_MODE_DISABLE,              \
        .Init.ExtendedMode       = FSMC_EXTENDED_MODE_DISABLE,          \
        .Init.AsynchronousWait   = FSMC_ASYNCHRONOUS_WAIT_DISABLE,      \
        .Init.WriteBurst         = FSMC_WRITE_BURST_DISABLE,            \
    }
#endif /* SRAM_CONFIG */

/* Timing configuration for IS62WV51216 */
#ifndef SRAM_TIMING_CONFIG
#define SRAM_TIMING_CONFIG                                  \
    {                                                       \
        .AddressSetupTime       = 0,                        \
        .AddressHoldTime        = 0,                        \
        .DataSetupTime          = 8,                        \
        .BusTurnAroundDuration  = 0,                        \
        .CLKDivision            = 0,                        \
        .DataLatency            = 0,                        \
        .AccessMode             = FSMC_ACCESS_MODE_A,       \
    }
#endif /* SRAM_TIMING_CONFIG */

#endif
