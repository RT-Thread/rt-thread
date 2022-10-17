/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-15     xjy198903    The first version for rt1170
 */

#ifndef FLEXSPI_PORT_H__
#define FLEXSPI_PORT_H__

/* parameters for flexpsi peripheral */
#define FLEXSPI1_CONTROL_BASE FLEXSPI1
#define FLEXSPI2_CONTROL_BASE FLEXSPI2
#define FLEXSPI_ROOT_CLK (80000000U) /* serial root clk: 80MHz*/
#define FLASH_SIZE (32 * 1024) /* device size 32*1024(KB) = 32MB */
#define ARD_SEQ_NUMBER 1       /* Sequence number for AHB read command */
#define ARD_SEQ_INDEX 0        /* Sequence ID for AHB read command */
#define AWR_SEQ_NUMBER 1       /* Sequence number for AHB write command */
#define AWR_SEQ_INDEX 1        /* Sequence ID for AHB write command */
#define ARD_SEQ_CMD 0xBB       /* cmd for read */
#define AWR_SEQ_CMD 0xAA       /* cmd for write */
#define FLEXSPI_RX_SAMPLE_CLOCK kFLEXSPI_ReadSampleClkExternalInputFromDqsPad
#define FLASH_PORT kFLEXSPI_PortA1
#define CLOCK_SRC kCLOCK_FLEXSPI2_ClockRoot_MuxOscRc400M
#define CLOCK_DIV 5U
#define CUSTOM_LUT_LENGTH 64U
#define FLEXSPI1_AHB_DATA_ADDRESS (0x30000000U)
#define FLEXSPI2_AHB_DATA_ADDRESS (0x60000000U)
#endif /* FLEXSPI_PORT_H__ */
