/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-09-14     xjy198903    the first version for 1170
 * 2026-06-03     CoreBoxer    support IMXRT1180-EVK
 * 2026-07-03     Jasontek     support hyperflash in IMXRT1180-EVK
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

#ifdef BSP_USING_DMA
#include "fsl_flexspi_edma.h"

volatile bool g_completionFlag = false;
flexspi_edma_handle_t flexspiHandle;

static void flexspi_callback(FLEXSPI_Type *base, flexspi_edma_handle_t *handle, status_t status, void *userData)
{
    /* Signal transfer success when received success status. */
    if (status == kStatus_Success)
    {
        g_completionFlag = true;
    }
}
#endif

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
#ifndef BSP_USING_OSPI_FLASH
    .flexspiRootClk       = 12000000,
#else
	.flexspiRootClk       = 200000000,
#endif
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
#ifndef BSP_USING_OSPI_FLASH	
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
#else
	/*  OPI DDR read */
    [4 * NOR_CMD_LUT_SEQ_IDX_READ + 0] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xCC, 
                        kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xCC),
    [4 * NOR_CMD_LUT_SEQ_IDX_READ + 1] = 
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20, 
                        kFLEXSPI_Command_DUMMY_DDR, kFLEXSPI_8PAD, 0x20),
    [4 * NOR_CMD_LUT_SEQ_IDX_READ + 2] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_DDR, kFLEXSPI_8PAD, 0x04, 
                        kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0x0),

    /* Read ID */
    [4 * NOR_CMD_LUT_SEQ_IDX_READID_OPI] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x9F, 
                        kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x9F),
    [4 * NOR_CMD_LUT_SEQ_IDX_READID_OPI + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DUMMY_DDR, kFLEXSPI_8PAD, 0x10, 
                        kFLEXSPI_Command_READ_DDR, kFLEXSPI_8PAD, 0x04),

    /*  Write Enable */
    [4 * NOR_CMD_LUT_SEQ_IDX_WRITEENABLE_OPI] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x06, 
                        kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x06),

    /*  Erase Sector */
    [4 * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x21, 
                        kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x21),
    [4 * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20, 
                        kFLEXSPI_Command_STOP, kFLEXSPI_8PAD, 0),

    /*  Erase Chip */
    [4 * NOR_CMD_LUT_SEQ_IDX_CHIPERASE] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xC4, 
                        kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xC4),
    [4 * NOR_CMD_LUT_SEQ_IDX_CHIPERASE + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20, 
                        kFLEXSPI_Command_STOP, kFLEXSPI_8PAD, 0),

    /*  Program */
    [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x8E, 
                        kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x8E),
    [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM + 1] = 
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20, 
                        kFLEXSPI_Command_WRITE_DDR, kFLEXSPI_8PAD, 0x04),

    /*  Dummy write, do nothing when AHB write command is triggered. */
    [4 * NOR_CMD_LUT_SEQ_IDX_WRITE] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0x0, 
                        kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0x0),

    /*  Read status register using Octal DDR read */
    [4 * NOR_CMD_LUT_SEQ_IDX_READSTATUS_OPI] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x05, 
                        kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x05),
    [4 * NOR_CMD_LUT_SEQ_IDX_READSTATUS_OPI + 1] = 
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DUMMY_DDR, kFLEXSPI_8PAD, 0x10, 
                        kFLEXSPI_Command_READ_DDR, kFLEXSPI_8PAD, 0x04),
#endif
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
    //Set root clk 80MHz for QSPI, 200MHz for OSPI
    flexspi_clock_init(kCLOCK_Root_Flexspi1, CLOCK_SRC, CLOCK_DIV);
#else
    base = FLEXSPI2_CONTROL_BASE;
    s_flexspi_handle.base     = FLEXSPI2_CONTROL_BASE;
    s_flexspi_handle.port     = FLASH_PORT;
    s_flexspi_handle.ahb_base = FLEXSPI2_AHB_DATA_ADDRESS;
    flexspi_clock_init(kCLOCK_Root_Flexspi2, CLOCK_SRC, CLOCK_DIV);
#endif

#ifdef BSP_USING_DMA
    edma_config_t userConfig;
	edma_handle_t dmaTxHandle;
    edma_handle_t dmaRxHandle;

    /* EDMA init */
    /*
     * userConfig.enableRoundRobinArbitration = false;
     * userConfig.enableHaltOnError = true;
     * userConfig.enableContinuousLinkMode = false;
     * userConfig.enableDebugMode = false;
     */
    EDMA_GetDefaultConfig(&userConfig);
#if defined(BOARD_GetEDMAConfig)
    BOARD_GetEDMAConfig(userConfig);
#endif
    EDMA_Init(FLEXSPI_DMA, &userConfig);
    /* Set request */
    EDMA_SetChannelMux(FLEXSPI_DMA, FLEXSPI_TX_DMA_CHANNEL, FLEXSPI_TX_DMA_REQUEST_SOURCE);
    EDMA_SetChannelMux(FLEXSPI_DMA, FLEXSPI_RX_DMA_CHANNEL, FLEXSPI_RX_DMA_REQUEST_SOURCE);
    /* Create the EDMA channel handles */
    EDMA_CreateHandle(&dmaTxHandle, FLEXSPI_DMA, FLEXSPI_TX_DMA_CHANNEL);
    EDMA_CreateHandle(&dmaRxHandle, FLEXSPI_DMA, FLEXSPI_RX_DMA_CHANNEL);
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
#ifdef BSP_USING_DMA
    /* Create handle for flexspi. */
    FLEXSPI_TransferCreateHandleEDMA(FLEXSPI1_CONTROL_BASE, &flexspiHandle, flexspi_callback, NULL, &dmaTxHandle,
                                     &dmaRxHandle);
#endif

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_imxrt_flexspi_init);

#ifdef FLEXSPI_DEBUG
#ifdef FINSH_USING_MSH

#ifndef BSP_USING_OSPI_FLASH

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

#else

#define EXAMPLE_SECTOR                  20
/*******************************************************************************
 * Variables
 ******************************************************************************/
#ifdef BSP_USING_DMA
AT_NONCACHEABLE_SECTION_ALIGN(static uint8_t s_nor_program_buffer[256], 4);
#else
static uint8_t s_nor_program_buffer[256];
#endif
static uint8_t s_nor_read_buffer[256];
extern status_t flexspi_nor_flash_erase_sector(FLEXSPI_Type *base, uint32_t address);
extern status_t flexspi_nor_flash_page_program(FLEXSPI_Type *base, uint32_t dstAddr, const uint32_t *src);
extern status_t flexspi_nor_get_vendor_id(FLEXSPI_Type *base, uint8_t *vendorId);
extern status_t flexspi_nor_enable_octal_mode(FLEXSPI_Type *base);

/* read write hyper flase test */
static void flexspi_test(void)
{
    uint32_t i = 0;
    status_t status;
    uint8_t vendorID = 0;
#ifdef BSP_USING_DMA
    LOG_W("\r\nFLEXSPI example started! -- DMA mode\r\n");
#else
    LOG_W("\r\nFLEXSPI example started!\r\n");
#endif
#if defined(FLASH_ENABLE_OCTAL_CMD)
    /* Enter octal mode unless the FLASH boots in octal mode after reset */
    status = flexspi_nor_enable_octal_mode(FLEXSPI1_CONTROL_BASE);
    if (status != kStatus_Success)
    {
    #ifdef BSP_USING_DMA
        LOG_E("Enable octal mode failure ! -- DMA mode\r\n");
    #else
        LOG_E("Enable octal mode failure !\r\n");
    #endif
        return ;
    }
#ifdef BSP_USING_DMA
    LOG_W("Enabled octal mode. -- DMA mode\r\n");
#else
    LOG_W("Enabled octal mode.\r\n");
#endif
#endif

    /* Get vendor ID. */
    status = flexspi_nor_get_vendor_id(FLEXSPI1_CONTROL_BASE, &vendorID);
    if (status != kStatus_Success)
    {
    #ifdef BSP_USING_DMA
        LOG_E("Get vendor id failure ! -- DMA mode\r\n");
    #else
        LOG_E("Get vendor id failure !\r\n");
    #endif
        return ;
    }
#ifdef BSP_USING_DMA
    LOG_W("Vendor ID: 0x%x -- DMA mode\r\n", vendorID);
    /* Erase sectors. */
    LOG_W("Erasing Serial NOR over FlexSPI... -- DMA mode\r\n");
#else
    LOG_W("Vendor ID: 0x%x\r\n", vendorID);
    /* Erase sectors. */
    LOG_W("Erasing Serial NOR over FlexSPI...\r\n");
#endif

    status = flexspi_nor_flash_erase_sector(FLEXSPI1_CONTROL_BASE, EXAMPLE_SECTOR * SECTOR_SIZE);
    if (status != kStatus_Success)
    {
    #ifdef BSP_USING_DMA
        LOG_E("Erase sector failure ! -- DMA mode\r\n");
    #else
        LOG_E("Erase sector failure !\r\n");
    #endif
        return ;
    }

#if defined(CACHE_MAINTAIN) && CACHE_MAINTAIN
    DCACHE_InvalidateByRange(FlexSPI1_AMBA_BASE + EXAMPLE_SECTOR * SECTOR_SIZE, FLASH_PAGE_SIZE);
#endif

    memset(s_nor_program_buffer, 0xFFU, sizeof(s_nor_program_buffer));
    memcpy(s_nor_read_buffer, (void *)(FlexSPI1_AMBA_BASE + EXAMPLE_SECTOR * SECTOR_SIZE),
           sizeof(s_nor_read_buffer));

    if (memcmp(s_nor_program_buffer, s_nor_read_buffer, sizeof(s_nor_program_buffer)))
    {
    #ifdef BSP_USING_DMA
        LOG_E("Erase data -  read out data value incorrect ! -- DMA mode\r\n ");
    #else
        LOG_E("Erase data -  read out data value incorrect !\r\n ");
    #endif
        return ;
    }
    else
    {
    #ifdef BSP_USING_DMA
        LOG_W("Erase data - successfully. -- DMA mode\r\n");
    #else
        LOG_W("Erase data - successfully. \r\n");
    #endif
    }

    for (i = 0; i < 0xFFU; i++)
    {
        s_nor_program_buffer[i] = i;
    }

    status =
        flexspi_nor_flash_page_program(FLEXSPI1_CONTROL_BASE, EXAMPLE_SECTOR * SECTOR_SIZE, (void *)s_nor_program_buffer);
    if (status != kStatus_Success)
    {
    #ifdef BSP_USING_DMA
        LOG_E("Page program failure ! -- DMA mode\r\n");
    #else
        LOG_E("Page program failure !\r\n");
    #endif
        return ;
    }

#if defined(CACHE_MAINTAIN) && CACHE_MAINTAIN
    DCACHE_InvalidateByRange(FlexSPI1_AMBA_BASE + EXAMPLE_SECTOR * SECTOR_SIZE, FLASH_PAGE_SIZE);
#endif

    memcpy(s_nor_read_buffer, (void *)(FlexSPI1_AMBA_BASE + EXAMPLE_SECTOR * SECTOR_SIZE),
           sizeof(s_nor_read_buffer));

    if (memcmp(s_nor_read_buffer, s_nor_program_buffer, sizeof(s_nor_program_buffer)) != 0)
    {
    #ifdef BSP_USING_DMA
        LOG_E("Program data -  read out data value incorrect ! -- DMA mode\r\n ");
    #else
        LOG_E("Program data -  read out data value incorrect !\r\n ");
    #endif
        return ;
    }
    else
    {
    #ifdef BSP_USING_DMA
        LOG_W("Program data - successfully. -- DMA mode\r\n");
    #else
        LOG_W("Program data - successfully. \r\n");
    #endif
    }

}
#endif
MSH_CMD_EXPORT(flexspi_test, flexspi test)

#endif /* FLEXSPI_DEBUG */
#endif /* FINSH_USING_MSH */
#endif /* BSP_USING_FLEXSPI */

