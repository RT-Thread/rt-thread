/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

#include "r_ioport.h"
#include "bsp_cfg.h"
#include "bsp_pin_cfg.h"

#include <rtthread.h>

#define DRV_DEBUG
#define LOG_TAG         "drv_sdram"
#include <drv_log.h>

/*
 * Set ACTIVE-to-PRECHARGE command (tRAS) timing
 * e.g. tRAS = 42ns -> 6cycles are needed at SDCLK 120MHz
 *      tRAS = 37ns -> 5cycles are needed at SDCLK 120MHz
 */
#define BSP_PRV_SDRAM_TRAS                     (6U)

/*
 * Set ACTIVE-to-READ or WRITE delay tRCD (tRCD) timing
 * e.g. tRCD = 18ns -> 3cycles are needed at SDCLK 120MHz
 *      tRCD = 15ns -> 2cycles are needed at SDCLK 120MHz
 */
#define BSP_PRV_SDRAM_TRCD                     (3U)

/*
 * Set PRECHARGE command period (tRP) timing
 * e.g. tRP  = 18ns -> 3cycles are needed at SDCLK 120MHz
 *      tRP  = 15ns -> 2cycles are needed at SDCLK 120MHz
 */
#define BSP_PRV_SDRAM_TRP                      (3U)

/*
 * Set WRITE recovery time (tWR) timing
 * e.g. tWR  = 1CLK + 6ns -> 2cycles are needed at SDCLK 120MHz
 *      tWR  = 1CLK + 7ns -> 2cycles are needed at SDCLK 120MHz
 */
#define BSP_PRV_SDRAM_TWR                      (2U)

/*
 * Set CAS (READ) latency (CL) timing
 * e.g. CL = 18ns -> 3cycles are needed at SDCLK 120MHz
 * e.g. CL = 15ns -> 2cycles are needed at SDCLK 120MHz
 */
#define BSP_PRV_SDRAM_CL                       (3U)

/*
 * Set AUTO REFRESH period (tRFC) timing
 * e.g. tRFC = 60nS -> 8cycles are needed at SDCLK 120MHz
 *      tRFC = 66nS -> 8cycles are needed at SDCLK 120MHz
 */
#define BSP_PRV_SDRAM_TRFC                     (8U)

/*
 * Set Average Refresh period
 * e.g. tREF = 64ms/8192rows -> 7.8125us/each row.  937cycles are needed at SDCLK 120MHz
 */
#define BSP_PRV_SDRAM_REF_CMD_INTERVAL         (937U)

/*
 * Set Auto-Refresh issue times in initialization sequence needed for SDRAM device
 * Typical SDR SDRAM device needs twice of Auto-Refresh command issue
 */
#define BSP_PRV_SDRAM_SDIR_REF_TIMES           (2U)

/*
 * Set RAW address offset
 * Available settings are
 * 8  : 8-bit
 * 9  : 9-bit
 * 10 : 10-bit
 * 11 : 11-bit
 */
#define BSP_PRV_SDRAM_SDADR_ROW_ADDR_OFFSET    (9U)

/*
 * Select endian mode for SDRAM address space
 * 0 : Endian of SDRAM address space is the same as the endian of operating mode
 * 1 : Endian of SDRAM address space is not the endian of operating mode
 */
#define BSP_PRV_SDRAM_ENDIAN_MODE              (0U)

/*
 * Select access mode
 * Typically Continuous access should be enabled to get better SDRAM bandwidth
 * 0: Continuous access is disabled
 * 1: Continuous access is enabled
 */
#define BSP_PRV_SDRAM_CONTINUOUS_ACCESSMODE    (1U)

/*
 * Select bus width
 * 0: 16-bit
 * 1: 32-bit
 * 2: 8-bit
 */
#define BSP_PRV_SDRAM_BUS_WIDTH                (0U)

#if ((BSP_PRV_SDRAM_SDADR_ROW_ADDR_OFFSET != 8U) && (BSP_PRV_SDRAM_SDADR_ROW_ADDR_OFFSET != 9U) \
    && (BSP_PRV_SDRAM_SDADR_ROW_ADDR_OFFSET != 10U) && (BSP_PRV_SDRAM_SDADR_ROW_ADDR_OFFSET > 11U))
#error "BSP_PRV_SDRAM_SDADR_ROW_ADDR_OFFSET must be either of 8,9,10 or 11"
#endif

#if ((BSP_PRV_SDRAM_BUS_WIDTH != 0) && (BSP_PRV_SDRAM_BUS_WIDTH != 1U) && (BSP_PRV_SDRAM_BUS_WIDTH != 2U))
    #error "BSP_PRV_SDRAM_BUS_WIDTH must be either of 0(16-bit) or 1(32-bit) or 2(8-bit)"
#endif

#if ((BSP_PRV_SDRAM_ENDIAN_MODE != 0) && (BSP_PRV_SDRAM_ENDIAN_MODE != 1))
    #error \
    "BSP_PRV_SDRAM_ENDIAN_MODE must be either of 0(same endian as operating mode) or 2(another endian against operating mode)"
#endif

#if ((BSP_PRV_SDRAM_CONTINUOUS_ACCESSMODE != 0) && (BSP_PRV_SDRAM_CONTINUOUS_ACCESSMODE != 1))
    #error \
    "BSP_PRV_SDRAM_CONTINUOUS_ACCESSMODE must be either of 0(continuous access is disabled) or 1(continuous access is enabled)"
#endif

#define BSP_PRV_SDRAM_MR_WB_SINGLE_LOC_ACC    (1U) /* MR.M9                : Single Location Access */
#define BSP_PRV_SDRAM_MR_OP_MODE              (0U) /* MR.M8:M7             : Standard Operation */
#define BSP_PRV_SDRAM_MR_BT_SEQUENCTIAL       (0U) /* MR.M3 Burst Type     : Sequential */
#define BSP_PRV_SDRAM_MR_BURST_LENGTH         (0U) /* MR.M2:M0 Burst Length: 0(1 burst) */

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

void drv_sdram_init(void)
{
    /** Setting for SDRAM initialization sequence */
#if (BSP_PRV_SDRAM_TRP < 3)
    R_BUS->SDRAM.SDIR_b.PRC = 3U;
#else
    R_BUS->SDRAM.SDIR_b.PRC = BSP_PRV_SDRAM_TRP - 3U;
#endif

    while (R_BUS->SDRAM.SDSR)
    {
        /* According to h/w maual, need to confirm that all the status bits in SDSR are 0 before SDIR modification. */
    }

    R_BUS->SDRAM.SDIR_b.ARFC = BSP_PRV_SDRAM_SDIR_REF_TIMES;

    while (R_BUS->SDRAM.SDSR)
    {
        /* According to h/w maual, need to confirm that all the status bits in SDSR are 0 before SDIR modification. */
    }

#if (BSP_PRV_SDRAM_TRFC < 3)
    R_BUS->SDRAM.SDIR_b.ARFI = 0U;
#else
    R_BUS->SDRAM.SDIR_b.ARFI = BSP_PRV_SDRAM_TRFC - 3U;
#endif

    while (R_BUS->SDRAM.SDSR)
    {
        /* According to h/w maual, need to confirm that all the status bits in SDSR are 0 before SDICR modification. */
    }

    /** Start SDRAM initialization sequence.
     * Following operation is automatically done when set SDICR.INIRQ bit.
     * Perform a PRECHARGE ALL command and wait at least tRP time.
     * Issue an AUTO REFRESH command and wait at least tRFC time.
     * Issue an AUTO REFRESH command and wait at least tRFC time.
     */
    R_BUS->SDRAM.SDICR_b.INIRQ = 1U;
    while (R_BUS->SDRAM.SDSR_b.INIST)
    {
        /* Wait the end of initialization sequence. */
    }

    /** Setting for SDRAM controller */
    R_BUS->SDRAM.SDCCR_b.BSIZE  = BSP_PRV_SDRAM_BUS_WIDTH;             /* set SDRAM bus width */
    R_BUS->SDRAM.SDAMOD_b.BE    = BSP_PRV_SDRAM_CONTINUOUS_ACCESSMODE; /* enable continuous access */
    R_BUS->SDRAM.SDCMOD_b.EMODE = BSP_PRV_SDRAM_ENDIAN_MODE;           /* set endian mode for SDRAM address space */

    while (R_BUS->SDRAM.SDSR)
    {
        /* According to h/w maual, need to confirm that all the status bits in SDSR are 0 before SDMOD modification. */
    }

    /** Using LMR command, program the mode register */
    R_BUS->SDRAM.SDMOD = ((((uint16_t)(BSP_PRV_SDRAM_MR_WB_SINGLE_LOC_ACC << 9) |
                            (uint16_t)(BSP_PRV_SDRAM_MR_OP_MODE << 7)) |
                           (uint16_t)(BSP_PRV_SDRAM_CL << 4)) |
                          (uint16_t)(BSP_PRV_SDRAM_MR_BT_SEQUENCTIAL << 3)) |
                         (uint16_t)(BSP_PRV_SDRAM_MR_BURST_LENGTH << 0);

    /** wait at least tMRD time */
    while (R_BUS->SDRAM.SDSR_b.MRSST)
    {
        /* Wait until Mode Register setting done. */
    }

    /** Set timing parameters for SDRAM */
    R_BUS->SDRAM.SDTR_b.RAS = BSP_PRV_SDRAM_TRAS - 1U; /* set ACTIVE-to-PRECHARGE command cycles*/
    R_BUS->SDRAM.SDTR_b.RCD = BSP_PRV_SDRAM_TRCD - 1U; /* set ACTIVE to READ/WRITE delay cycles */
    R_BUS->SDRAM.SDTR_b.RP  = BSP_PRV_SDRAM_TRP - 1U;  /* set PRECHARGE command period cycles */
    R_BUS->SDRAM.SDTR_b.WR  = BSP_PRV_SDRAM_TWR - 1U;  /* set write recovery cycles */
    R_BUS->SDRAM.SDTR_b.CL  = BSP_PRV_SDRAM_CL;        /* set SDRAM column latency cycles */

    /** Set row address offset for target SDRAM */
    R_BUS->SDRAM.SDADR_b.MXC = BSP_PRV_SDRAM_SDADR_ROW_ADDR_OFFSET - 8U;

    R_BUS->SDRAM.SDRFCR_b.REFW = (uint16_t)(BSP_PRV_SDRAM_TRFC - 1U);  /* set Auto-Refresh issuing cycle */
    R_BUS->SDRAM.SDRFCR_b.RFC  = BSP_PRV_SDRAM_REF_CMD_INTERVAL - 1U;  /* set Auto-Refresh period */

    /** Start Auto-refresh */
    R_BUS->SDRAM.SDRFEN_b.RFEN = 1U;

    /** Enable SDRAM access */
    R_BUS->SDRAM.SDCCR_b.EXENB = 1U;
}

#ifdef BSP_USING_SDRAM
#ifdef RT_USING_MEMHEAP_AS_HEAP
    struct rt_memheap system_heap;
#endif

static int SDRAM_Init(void)
{
    drv_sdram_init();

    LOG_D("sdram init success, mapped at 0x%X, size is %d bytes, data width is %d", 0x68000000, BSP_USING_SDRAM_SIZE, 16);
#ifdef RT_USING_MEMHEAP_AS_HEAP
    /* If RT_USING_MEMHEAP_AS_HEAP is enabled, SDRAM is initialized to the heap */
    rt_memheap_init(&system_heap, "sdram", (void *)0x68000000, BSP_USING_SDRAM_SIZE);
#endif
    return RT_EOK;
}
INIT_BOARD_EXPORT(SDRAM_Init);
#endif
