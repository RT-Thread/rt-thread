/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-09-14     xjy198903    the first version for 1170
 */

#include <rtthread.h>
#ifdef BSP_USING_FLEXSPI
#include "board.h"
#include <rtdevice.h>

#ifdef RT_USING_FINSH
#include <finsh.h>
#endif

#include "flexspi_port.h"
#include "fsl_flexspi.h"

#define FLEXSPI_DEBUG
#define LOG_TAG             "drv.flexspi"
#include <drv_log.h>

flexspi_device_config_t deviceconfig = {
    .flexspiRootClk       = 200000000,
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

const uint32_t customLUTOctalMode[CUSTOM_LUT_LENGTH] = {

	/*  OPI DDR read */
    [4 * NOR_CMD_LUT_SEQ_IDX_READ + 0] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xCC, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xCC),
    [4 * NOR_CMD_LUT_SEQ_IDX_READ + 1] = FLEXSPI_LUT_SEQ(
        kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20, kFLEXSPI_Command_DUMMY_DDR, kFLEXSPI_8PAD, 0x20),
    [4 * NOR_CMD_LUT_SEQ_IDX_READ + 2] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_DDR, kFLEXSPI_8PAD, 0x04, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0x0),

    /* Read ID */
    [4 * NOR_CMD_LUT_SEQ_IDX_READID_OPI] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x9F, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x9F),
    [4 * NOR_CMD_LUT_SEQ_IDX_READID_OPI + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DUMMY_DDR, kFLEXSPI_8PAD, 0x10, kFLEXSPI_Command_READ_DDR, kFLEXSPI_8PAD, 0x04),

    /*  Write Enable */
    [4 * NOR_CMD_LUT_SEQ_IDX_WRITEENABLE_OPI] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x06, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x06),

    /*  Erase Sector */
    [4 * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x21, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x21),
    [4 * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20, kFLEXSPI_Command_STOP, kFLEXSPI_8PAD, 0),

    /*  Erase Chip */
    [4 * NOR_CMD_LUT_SEQ_IDX_CHIPERASE] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xC4, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xC4),
    [4 * NOR_CMD_LUT_SEQ_IDX_CHIPERASE + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20, kFLEXSPI_Command_STOP, kFLEXSPI_8PAD, 0),

    /*  Program */
    [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x8E, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x8E),
    [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM + 1] = FLEXSPI_LUT_SEQ(
        kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20, kFLEXSPI_Command_WRITE_DDR, kFLEXSPI_8PAD, 0x04),

    /*  Dummy write, do nothing when AHB write command is triggered. */
    [4 * NOR_CMD_LUT_SEQ_IDX_WRITE] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0x0, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0x0),

    /*  Read status register using Octal DDR read */
    [4 * NOR_CMD_LUT_SEQ_IDX_READSTATUS_OPI] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x05, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x05),
    [4 * NOR_CMD_LUT_SEQ_IDX_READSTATUS_OPI + 1] = FLEXSPI_LUT_SEQ(
        kFLEXSPI_Command_DUMMY_DDR, kFLEXSPI_8PAD, 0x10, kFLEXSPI_Command_READ_DDR, kFLEXSPI_8PAD, 0x04),

};

static void flexspi_clock_init(clock_root_t root, uint8_t src, uint8_t div)
{
    /*Clock setting for flexspi1*/
    CLOCK_SetRootClockDiv(root, div);
    CLOCK_SetRootClockMux(root, src);
}

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
extern status_t flexspi_nor_flash_erase_sector(FLEXSPI_Type *base, uint32_t address);
extern status_t flexspi_nor_flash_page_program(FLEXSPI_Type *base, uint32_t dstAddr, const uint32_t *src);
extern status_t flexspi_nor_get_vendor_id(FLEXSPI_Type *base, uint8_t *vendorId);
extern status_t flexspi_nor_enable_octal_mode(FLEXSPI_Type *base);
extern void flexspi_nor_flash_init(FLEXSPI_Type *base);

static int rt_hw_imxrt_flexspi_init(void)
{
    FLEXSPI_Type *base;

#ifdef BSP_USING_FLEXSPI1
    base = FLEXSPI1_CONTROL_BASE;
#else
    base = FLEXSPI2_CONTROL_BASE;
#endif

    //Set root clk 200MHz
    flexspi_clock_init(kCLOCK_Root_Flexspi1, CLOCK_SRC, CLOCK_DIV);
	
	flexspi_nor_flash_init(base);

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_imxrt_flexspi_init);

#ifdef FLEXSPI_DEBUG
#ifdef FINSH_USING_MSH

#define EXAMPLE_SECTOR                  20
#define EXAMPLE_FLEXSPI_AMBA_BASE       FlexSPI1_AMBA_BASE

/*******************************************************************************
 * Variables
 ******************************************************************************/
static uint8_t s_nor_program_buffer[256];
static uint8_t s_nor_read_buffer[256];

/* read write hyper flase test */
static void flexspi_test(void)
{
	uint32_t i = 0;
    status_t status;
    uint8_t vendorID = 0;
    LOG_I("\r\nFLEXSPI example started!\r\n");

#if defined(FLASH_ENABLE_OCTAL_CMD)
    /* Enter octal mode unless the FLASH boots in octal mode after reset */
    status = flexspi_nor_enable_octal_mode(FLEXSPI1_CONTROL_BASE);
    if (status != kStatus_Success)
    {
        LOG_W("Enable octal mode failure !\r\n");
        return ;
    }
	LOG_I("Enabled octal mode.\r\n");
#endif

#if !(defined(FLASH_ADESTO) && FLASH_ADESTO)
    /* Get vendor ID. */
    status = flexspi_nor_get_vendor_id(FLEXSPI1_CONTROL_BASE, &vendorID);
    if (status != kStatus_Success)
    {
		LOG_W("Get vendor id failure !\r\n");
        return ;
    }
    LOG_I("Vendor ID: 0x%x\r\n", vendorID);
#endif

    /* Erase sectors. */
    LOG_I("Erasing Serial NOR over FlexSPI...\r\n");
    status = flexspi_nor_flash_erase_sector(FLEXSPI1_CONTROL_BASE, EXAMPLE_SECTOR * SECTOR_SIZE);
    if (status != kStatus_Success)
    {
        LOG_W("Erase sector failure !\r\n");
        return ;
    }

#if defined(CACHE_MAINTAIN) && CACHE_MAINTAIN
    DCACHE_InvalidateByRange(EXAMPLE_FLEXSPI_AMBA_BASE + EXAMPLE_SECTOR * SECTOR_SIZE, FLASH_PAGE_SIZE);
#endif

    memset(s_nor_program_buffer, 0xFFU, sizeof(s_nor_program_buffer));
    memcpy(s_nor_read_buffer, (void *)(EXAMPLE_FLEXSPI_AMBA_BASE + EXAMPLE_SECTOR * SECTOR_SIZE),
           sizeof(s_nor_read_buffer));

    if (memcmp(s_nor_program_buffer, s_nor_read_buffer, sizeof(s_nor_program_buffer)))
    {
        LOG_W("Erase data -  read out data value incorrect !\r\n ");
        return ;
    }
    else
    {
        LOG_I("Erase data - successfully. \r\n");
    }

    for (i = 0; i < 0xFFU; i++)
    {
        s_nor_program_buffer[i] = i;
    }

    status =
        flexspi_nor_flash_page_program(FLEXSPI1_CONTROL_BASE, EXAMPLE_SECTOR * SECTOR_SIZE, (void *)s_nor_program_buffer);
    if (status != kStatus_Success)
    {
        LOG_W("Page program failure !\r\n");
        return ;
    }

#if defined(CACHE_MAINTAIN) && CACHE_MAINTAIN
    DCACHE_InvalidateByRange(EXAMPLE_FLEXSPI_AMBA_BASE + EXAMPLE_SECTOR * SECTOR_SIZE, FLASH_PAGE_SIZE);
#endif

    memcpy(s_nor_read_buffer, (void *)(EXAMPLE_FLEXSPI_AMBA_BASE + EXAMPLE_SECTOR * SECTOR_SIZE),
           sizeof(s_nor_read_buffer));

    if (memcmp(s_nor_read_buffer, s_nor_program_buffer, sizeof(s_nor_program_buffer)) != 0)
    {
        LOG_W("Program data -  read out data value incorrect !\r\n ");
        return ;
    }
    else
    {
        LOG_I("Program data - successfully. \r\n");
    }
	
}
MSH_CMD_EXPORT(flexspi_test, flexspi test)

#endif /* FLEXSPI_DEBUG */
#endif /* FINSH_USING_MSH */
#endif /* BSP_USING_FLEXSPI */
