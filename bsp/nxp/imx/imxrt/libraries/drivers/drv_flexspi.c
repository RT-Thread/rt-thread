/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-09-14     xjy198903    the first version for 1170
 * 2026-06-03     CoreBoxer    support IMXRT1180-EVK
 */

#include <rtthread.h>
#if defined(BSP_USING_FLEXSPI) && \
    (defined(SOC_IMXRT1170_SERIES) || defined(SOC_IMXRT1180_SERIES))
#include "board.h"
#include <rtdevice.h>

#ifdef RT_USING_FINSH
#include <finsh.h>
#endif

#include "drv_flexspi.h"
#include "flexspi_port.h"
#include "fsl_flexspi.h"

#ifndef COMBINATION_MODE
#define COMBINATION_MODE 1U
#endif

#ifndef FREE_RUNNING_MODE
#define FREE_RUNNING_MODE 1U
#endif

#define FLEXSPI_DEBUG
#define LOG_TAG             "drv.flexspi"
#include <drv_log.h>

#if defined(SOC_IMXRT1170_SERIES)
static flexspi_device_config_t deviceconfig = {
    .flexspiRootClk       = 12000000,
    .flashSize            = FLASH_SIZE,
    .CSIntervalUnit       = kFLEXSPI_CsIntervalUnit1SckCycle,
    .CSInterval           = 2,
    .CSHoldTime           = 3,
    .CSSetupTime          = 3,
    .dataValidTime        = 0,
    .columnspace          = 0,
    .enableWordAddress    = 0,
    .AWRSeqIndex          = AWR_SEQ_INDEX,
    .AWRSeqNumber         = AWR_SEQ_NUMBER,
    .ARDSeqIndex          = ARD_SEQ_INDEX,
    .ARDSeqNumber         = ARD_SEQ_NUMBER,
    .AHBWriteWaitUnit     = kFLEXSPI_AhbWriteWaitUnit2AhbCycle,
    .AHBWriteWaitInterval = 0,
};

const uint32_t customLUT[CUSTOM_LUT_LENGTH] = {
    /* 8bit mode */
    [4 * ARD_SEQ_INDEX] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_DDR, kFLEXSPI_8PAD, 0x04, kFLEXSPI_Command_STOP, kFLEXSPI_8PAD, 0),
};
#elif defined(SOC_IMXRT1180_SERIES)
static flexspi_device_config_t deviceconfig = {
    .flexspiRootClk       = 12000000,
    .flashSize            = FLASH_SIZE,
    .CSIntervalUnit       = kFLEXSPI_CsIntervalUnit1SckCycle,
    .CSInterval           = 2,
    .CSHoldTime           = 3,
    .CSSetupTime          = 3,
    .dataValidTime        = 0,
    .columnspace          = 0,
    .enableWordAddress    = 0,
    .AWRSeqIndex          = AWR_SEQ_INDEX,
    .AWRSeqNumber         = AWR_SEQ_NUMBER,
    .ARDSeqIndex          = ARD_SEQ_INDEX,
    .ARDSeqNumber         = ARD_SEQ_NUMBER,
    .AHBWriteWaitUnit     = kFLEXSPI_AhbWriteWaitUnit2AhbCycle,
    .AHBWriteWaitInterval = 0,
};

const uint32_t customLUT[CUSTOM_LUT_LENGTH] = {
    /* Normal read mode - SDR */
    [4 * NOR_CMD_LUT_SEQ_IDX_READ_NORMAL] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x03,
                        kFLEXSPI_Command_RADDR_SDR,  kFLEXSPI_1PAD, 0x18),
    [4 * NOR_CMD_LUT_SEQ_IDX_READ_NORMAL + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_SDR,  kFLEXSPI_1PAD, 0x04,
                        kFLEXSPI_Command_STOP,       kFLEXSPI_1PAD, 0),

    /* Fast read mode - SDR */
    [4 * NOR_CMD_LUT_SEQ_IDX_READ_FAST] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x0B,
                        kFLEXSPI_Command_RADDR_SDR,  kFLEXSPI_1PAD, 0x18),
    [4 * NOR_CMD_LUT_SEQ_IDX_READ_FAST + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DUMMY_SDR, kFLEXSPI_1PAD, 0x08,
                        kFLEXSPI_Command_READ_SDR,   kFLEXSPI_1PAD, 0x04),

    /* Fast read quad mode - SDR */
    [4 * NOR_CMD_LUT_SEQ_IDX_READ_FAST_QUAD] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0xEB,
                        kFLEXSPI_Command_RADDR_SDR,  kFLEXSPI_4PAD, 0x18),
    [4 * NOR_CMD_LUT_SEQ_IDX_READ_FAST_QUAD + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DUMMY_SDR, kFLEXSPI_4PAD, 0x06,
                        kFLEXSPI_Command_READ_SDR,   kFLEXSPI_4PAD, 0x04),

    /* Write Enable */
    [4 * NOR_CMD_LUT_SEQ_IDX_WRITEENABLE] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,  kFLEXSPI_1PAD, 0x06,
                        kFLEXSPI_Command_STOP,  kFLEXSPI_1PAD, 0),

    /* Erase Sector */
    [4 * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x20,
                        kFLEXSPI_Command_RADDR_SDR,  kFLEXSPI_1PAD, 0x18),

    /* Page Program - single mode */
    [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_SINGLE] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x02,
                        kFLEXSPI_Command_RADDR_SDR,  kFLEXSPI_1PAD, 0x18),
    [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_SINGLE + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_1PAD, 0x04,
                        kFLEXSPI_Command_STOP,       kFLEXSPI_1PAD, 0),

    /* Page Program - quad mode */
    [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_QUAD] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x32,
                        kFLEXSPI_Command_RADDR_SDR,  kFLEXSPI_1PAD, 0x18),
    [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_QUAD + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_4PAD, 0x04,
                        kFLEXSPI_Command_STOP,       kFLEXSPI_1PAD, 0),

    /* Read ID */
    [4 * NOR_CMD_LUT_SEQ_IDX_READID] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,      kFLEXSPI_1PAD, 0x9F,
                        kFLEXSPI_Command_READ_SDR,  kFLEXSPI_1PAD, 0x04),

    /* Write Status Register */
    [4 * NOR_CMD_LUT_SEQ_IDX_WRITESTATUSREG] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,        kFLEXSPI_1PAD, 0x01,
                        kFLEXSPI_Command_WRITE_SDR,   kFLEXSPI_1PAD, 0x04),

    /* Read status register */
    [4 * NOR_CMD_LUT_SEQ_IDX_READSTATUSREG] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,      kFLEXSPI_1PAD, 0x05,
                        kFLEXSPI_Command_READ_SDR,  kFLEXSPI_1PAD, 0x04),

    /* Erase whole chip */
    [4 * NOR_CMD_LUT_SEQ_IDX_ERASECHIP] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,  kFLEXSPI_1PAD, 0xC7,
                        kFLEXSPI_Command_STOP,  kFLEXSPI_1PAD, 0),
};
#else
#error "Unsupported SOC for drv_flexspi"
#endif

/* --------------------------------------------------------------------------
 * Internal handle
 * -------------------------------------------------------------------------- */
static imxrt_flexspi_handle_t s_flexspi_handle =
{
    .base     = FLEXSPI1_CONTROL_BASE,
    .port     = FLASH_PORT,
    .ahb_base = FLEXSPI1_AHB_DATA_ADDRESS
};

imxrt_flexspi_handle_t *imxrt_flexspi_get_handle(void)
{
    return &s_flexspi_handle;
}

static void flexspi_clock_init(clock_root_t root, uint8_t src, uint8_t div)
{
    /*Clock setting for flexspi1*/
    CLOCK_SetRootClockDiv(root, div);
    CLOCK_SetRootClockMux(root, src);
}

FLEXSPI_RAM_CODE static int rt_hw_imxrt_flexspi_init(void)
{
    flexspi_config_t config;
    FLEXSPI_Type *base;

#ifdef BSP_USING_FLEXSPI1
    base = FLEXSPI1_CONTROL_BASE;
    s_flexspi_handle.base     = FLEXSPI1_CONTROL_BASE;
    s_flexspi_handle.port     = FLASH_PORT;
    s_flexspi_handle.ahb_base = FLEXSPI1_AHB_DATA_ADDRESS;
    //Set root clk 80MHz
    flexspi_clock_init(kCLOCK_Root_Flexspi1, CLOCK_SRC, CLOCK_DIV);
#else
    base = FLEXSPI2_CONTROL_BASE;
    s_flexspi_handle.base     = FLEXSPI2_CONTROL_BASE;
    s_flexspi_handle.port     = FLASH_PORT;
    s_flexspi_handle.ahb_base = FLEXSPI2_AHB_DATA_ADDRESS;
    flexspi_clock_init(kCLOCK_Root_Flexspi2, CLOCK_SRC, CLOCK_DIV);
#endif


    /*Get FLEXSPI default settings and configure the flexspi. */
    FLEXSPI_GetDefaultConfig(&config);

    /*Set AHB buffer size for reading data through AHB bus. */
    config.ahbConfig.enableAHBPrefetch = true;
    config.ahbConfig.enableAHBBufferable = true;
    config.ahbConfig.enableReadAddressOpt = true;
    config.ahbConfig.enableAHBCachable = true;
    config.ahbConfig.enableClearAHBBufferOpt    = true;
    config.rxSampleClock = FLEXSPI_RX_SAMPLE_CLOCK;
    if(COMBINATION_MODE)
    {
        config.enableCombination = true;
    }
    if(FREE_RUNNING_MODE)
    {
        config.enableSckFreeRunning = true;
    }
    FLEXSPI_Init(base, &config);

    /* Configure flash settings according to serial flash feature. */
    FLEXSPI_SetFlashConfig(base, &deviceconfig, FLASH_PORT);

    /* Update LUT table. */
    FLEXSPI_UpdateLUT(base, 0, customLUT, CUSTOM_LUT_LENGTH);

    /* Do software reset. */
    FLEXSPI_SoftwareReset(base);

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_imxrt_flexspi_init);

#ifdef FLEXSPI_DEBUG
#ifdef FINSH_USING_MSH

#define FLEXSPI_DATALEN 4U
static rt_uint32_t send_buf[FLEXSPI_DATALEN] = {0x11223344, 0x55667788, 0x12345678, 0x9900aabb};
static uint32_t recv_buf[FLEXSPI_DATALEN];

/* read write 32bit test */
static void flexspi_test(void)
{
    volatile rt_uint32_t *flexspi = (rt_uint32_t *)FLEXSPI1_AHB_DATA_ADDRESS; /* FLEXSPI1 start address. */

    LOG_D("FLEXSPI Memory 32 bit Write Start\n");
    *(flexspi + 15) = send_buf[3];
    *(flexspi + 8) = send_buf[1];
    *(flexspi + 11) = send_buf[2];
    *(flexspi + 3) = send_buf[0];
    LOG_D("FLEXSPI Memory 32 bit Write End\n");

    rt_memset(recv_buf, 0, sizeof(recv_buf));

    LOG_D("FLEXSPI Memory 32 bit Read Start\n");
    recv_buf[2] = *(flexspi + 11);
    recv_buf[3] = *(flexspi + 15);
    recv_buf[1] = *(flexspi + 8);
    recv_buf[0] = *(flexspi + 3);
    LOG_D("FLEXSPI Memory 32 bit Read End\n");

    LOG_D("addr12 is 0x%x\n", recv_buf[0]);
    LOG_D("addr32 is 0x%x\n", recv_buf[1]);
    LOG_D("addr44 is 0x%x\n", recv_buf[2]);
    LOG_D("addr60 is 0x%x\n", recv_buf[3]);
}
MSH_CMD_EXPORT(flexspi_test, flexspi test)

#endif /* FLEXSPI_DEBUG */
#endif /* FINSH_USING_MSH */
#endif /* BSP_USING_FLEXSPI */
