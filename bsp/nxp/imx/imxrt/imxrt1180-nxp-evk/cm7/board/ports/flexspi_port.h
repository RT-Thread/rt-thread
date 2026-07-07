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

#include "fsl_cache.h"

/* parameters for flexpsi peripheral */
#define FLEXSPI1_CONTROL_BASE       FLEXSPI1
#define FLEXSPI_ROOT_CLK            (400000000U) /* serial root clk: 400MHz*/
#define FLASH_SIZE                  (64 * 1024)  /* device size 64*1024(KB) = 64MB */
#define FLASH_PAGE_SIZE              256
#define SECTOR_SIZE                  0x1000      /* 4K */

#define ARD_SEQ_NUMBER               1           /* Sequence number for AHB read command */
#define ARD_SEQ_INDEX                0           /* Sequence ID for AHB read command */
#define AWR_SEQ_NUMBER               0           /* Sequence number for AHB write command */
#define AWR_SEQ_INDEX                0           /* Sequence ID for AHB write command */
#define FLEXSPI_RX_SAMPLE_CLOCK      kFLEXSPI_ReadSampleClkExternalInputFromDqsPad

#define FLASH_PORT                   kFLEXSPI_PortA1
#define CLOCK_SRC                    kCLOCK_FLEXSPI2_ClockRoot_MuxOscRc400M
#define CLOCK_DIV                    2U
#define CUSTOM_LUT_LENGTH            60U
#define FLEXSPI1_AHB_DATA_ADDRESS (0x28000000U)
#define FLEXSPI2_AHB_DATA_ADDRESS (0x60000000U)

#define COMBINATION_MODE   0U
#define FREE_RUNNING_MODE  0U

/* DMA related. */
#define FLEXSPI_DMA (DMA4)
#define FLEXSPI_TX_DMA_REQUEST_SOURCE kDma4RequestMuxFlexSPI1Tx
#define FLEXSPI_RX_DMA_REQUEST_SOURCE kDma4RequestMuxFlexSPI1Rx
#define FLEXSPI_TX_DMA_CHANNEL 0U
#define FLEXSPI_RX_DMA_CHANNEL 2U


#define NOR_CMD_LUT_SEQ_IDX_READ            0
#define NOR_CMD_LUT_SEQ_IDX_READSTATUS      1
#define NOR_CMD_LUT_SEQ_IDX_WRITEENABLE     2
#define NOR_CMD_LUT_SEQ_IDX_READID_OPI      3
#define NOR_CMD_LUT_SEQ_IDX_WRITEENABLE_OPI 4
#define NOR_CMD_LUT_SEQ_IDX_ERASESECTOR     5
#define NOR_CMD_LUT_SEQ_IDX_CHIPERASE       6
#define NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM     7
#define NOR_CMD_LUT_SEQ_IDX_ENTEROPI        8
/* NOTE: Workaround for debugger.
   Must define AHB write FlexSPI sequence index to 9 to avoid debugger issue.
   Debugger can attach to the CM33 core only when ROM executes to certain place.
   At that point, AHB write FlexSPI sequence index is set to 9, but in LUT, the
   command is not filled by ROM. If the debugger sets software breakpoint at flash
   after reset/attachment, FlexSPI AHB write command will be triggered. It may
   cause AHB bus hang if the command in LUT sequence index 9 is any read opeartion.
   So we need to ensure at any time, the FlexSPI LUT sequence 9 for the flash must
   be set to STOP command to avoid unexpected debugger behaivor.
 */
#define NOR_CMD_LUT_SEQ_IDX_WRITE          9
#define NOR_CMD_LUT_SEQ_IDX_READSTATUS_OPI 10

#define FLASH_BUSY_STATUS_POL    1
#define FLASH_BUSY_STATUS_OFFSET 0
#define FLASH_ERROR_STATUS_MASK  0x0e

/*
 * If cache is enabled, this example should maintain the cache to make sure
 * CPU core accesses the memory, not cache only.
 */
#define CACHE_MAINTAIN 1

/*${macro:end}*/

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*${variable:start}*/
#if (defined CACHE_MAINTAIN) && (CACHE_MAINTAIN == 1)
typedef struct _flexspi_cache_status
{
    volatile bool DCacheEnableFlag;
    volatile bool ICacheEnableFlag;
} flexspi_cache_status_t;
#endif




#endif /* FLEXSPI_PORT_H__ */

