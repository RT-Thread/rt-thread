/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-15     xjy198903    The first version for rt1170
 * 2026-06-03     CoreBoxer    support IMXRT1180-EVK
 */

#ifndef FLEXSPI_PORT_H__
#define FLEXSPI_PORT_H__

/* parameters for flexpsi peripheral */
#define FLEXSPI1_CONTROL_BASE FLEXSPI1
#define FLEXSPI2_CONTROL_BASE FLEXSPI2
#define FLEXSPI_ROOT_CLK (12000000U) /* serial root clk: 12MHz*/
#define FLASH_SIZE (16 * 1024) /* device size 16*1024(KB) = 16MB */
#define ARD_SEQ_NUMBER 1       /* Sequence number for AHB read command */
#define ARD_SEQ_INDEX 0        /* Sequence ID for AHB read command */
#define AWR_SEQ_NUMBER 0       /* Sequence number for AHB write command */
#define AWR_SEQ_INDEX 0        /* Sequence ID for AHB write command */
#define ARD_SEQ_CMD 0xBB       /* cmd for read */
#define AWR_SEQ_CMD 0xAA       /* cmd for write */
#define FLEXSPI_RX_SAMPLE_CLOCK kFLEXSPI_ReadSampleClkLoopbackFromDqsPad
#define FLASH_PORT kFLEXSPI_PortA1
#define CLOCK_SRC kCLOCK_FLEXSPI1_ClockRoot_MuxOscRc24M
#define CLOCK_DIV 2U
#define CUSTOM_LUT_LENGTH 60U
#define FLEXSPI1_AHB_DATA_ADDRESS (0x28000000U)
#define FLEXSPI2_AHB_DATA_ADDRESS (0x60000000U)

#define COMBINATION_MODE   0U
#define FREE_RUNNING_MODE  0U

#define EXAMPLE_FLEXSPI_AMBA_BASE       FlexSPI1_AMBA_BASE
#define FLASH_PAGE_SIZE                 256
#define SECTOR_SIZE                     0x1000 /* 4K */
#define EXAMPLE_FLEXSPI_CLOCK           kCLOCK_Flexspi1
#define FLASH_PORT                      kFLEXSPI_PortA1

#define NOR_CMD_LUT_SEQ_IDX_READ_NORMAL        7
#define NOR_CMD_LUT_SEQ_IDX_READ_FAST          13
#define NOR_CMD_LUT_SEQ_IDX_READ_FAST_QUAD     0
#define NOR_CMD_LUT_SEQ_IDX_READSTATUS         1
#define NOR_CMD_LUT_SEQ_IDX_WRITEENABLE        2
#define NOR_CMD_LUT_SEQ_IDX_ERASESECTOR        3
#define NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_SINGLE 6
#define NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_QUAD   4
#define NOR_CMD_LUT_SEQ_IDX_READID             8
#define NOR_CMD_LUT_SEQ_IDX_WRITESTATUSREG     9
#define NOR_CMD_LUT_SEQ_IDX_ENTERQPI           10
#define NOR_CMD_LUT_SEQ_IDX_EXITQPI            11
#define NOR_CMD_LUT_SEQ_IDX_READSTATUSREG      12
#define NOR_CMD_LUT_SEQ_IDX_ERASECHIP          5

#define FLASH_QUAD_ENABLE        0x40
#define FLASH_BUSY_STATUS_POL    1
#define FLASH_BUSY_STATUS_OFFSET 0

#endif /* FLEXSPI_PORT_H__ */
