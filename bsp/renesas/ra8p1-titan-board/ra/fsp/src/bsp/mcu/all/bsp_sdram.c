/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @defgroup BSP_SDRAM BSP SDRAM support
 * @ingroup RENESAS_COMMON
 * @brief Code that initializes the SDRAMC and SDR SDRAM device memory.
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Due to hardware limitations of the SDRAM peripheral,
 * it is not expected any of these need to be changeable by end user.
 * Only sequential, single access at a time is supported. */
#define BSP_PRV_SDRAM_MR_WB_SINGLE_LOC_ACC    (1U) /* MR.M9                : Single Location Access */
#define BSP_PRV_SDRAM_MR_OP_MODE              (0U) /* MR.M8:M7             : Standard Operation */
#define BSP_PRV_SDRAM_MR_BT_SEQUENTIAL        (0U) /* MR.M3 Burst Type     : Sequential */
#define BSP_PRV_SDRAM_MR_BURST_LENGTH         (0U) /* MR.M2:M0 Burst Length: 0(1 burst) */

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

#if 0 != BSP_FEATURE_SDRAM_START_ADDRESS

/*******************************************************************************************************************//**
 * @brief   Initializes SDRAM.
 * @param   init_memory  If true, this function will execute the initialization of the external modules.
 *                       Otherwise, it will only initialize the SDRAMC and leave the memory in self-refresh mode.
 *
 * This function initializes SDRAMC and SDR SDRAM device.
 *
 * @note This function must only be called once after reset.
 **********************************************************************************************************************/
void R_BSP_SdramInit (bool init_memory)
{
    /** Setting for SDRAM initialization sequence */
    while (R_BUS->SDRAM.SDSR)
    {
        /* According to h/w manual, need to confirm that all the status bits in SDSR are 0 before SDICR modification. */
    }

    /* Must only write to SDIR once after reset. */
    R_BUS->SDRAM.SDIR = ((BSP_CFG_SDRAM_INIT_ARFI - 3U) << R_BUS_SDRAM_SDIR_ARFI_Pos) |
                        (BSP_CFG_SDRAM_INIT_ARFC << R_BUS_SDRAM_SDIR_ARFC_Pos) |
                        ((BSP_CFG_SDRAM_INIT_PRC - 3U) << R_BUS_SDRAM_SDIR_PRC_Pos);

    R_BUS->SDRAM.SDCCR = (BSP_CFG_SDRAM_BUS_WIDTH << R_BUS_SDRAM_SDCCR_BSIZE_Pos); /* set SDRAM bus width */

    if (init_memory)
    {
        /* Enable the SDCLK output. */
        R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_CGC);
        R_SYSTEM->SDCKOCR = 1;
        R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_CGC);

        /** If requested, start SDRAM initialization sequence. */
        R_BUS->SDRAM.SDICR = 1U;
        while (R_BUS->SDRAM.SDSR_b.INIST)
        {
            /* Wait the end of initialization sequence. */
        }
    }

    /** Setting for SDRAM controller */
    R_BUS->SDRAM.SDAMOD = BSP_CFG_SDRAM_ACCESS_MODE; /* enable continuous access */
    R_BUS->SDRAM.SDCMOD = BSP_CFG_SDRAM_ENDIAN_MODE; /* set endian mode for SDRAM address space */

    while (R_BUS->SDRAM.SDSR)
    {
        /* According to h/w manual, need to confirm that all the status bits in SDSR are 0 before SDMOD modification. */
    }

    if (init_memory)
    {
        /** Using LMR command, program the mode register */
        R_BUS->SDRAM.SDMOD = (BSP_PRV_SDRAM_MR_WB_SINGLE_LOC_ACC << 9) |
                             (BSP_PRV_SDRAM_MR_OP_MODE << 7) |
                             (BSP_CFG_SDRAM_TCL << 4) |
                             (BSP_PRV_SDRAM_MR_BT_SEQUENTIAL << 3) |
                             (BSP_PRV_SDRAM_MR_BURST_LENGTH << 0);

        /** wait at least tMRD time */
        while (R_BUS->SDRAM.SDSR_b.MRSST)
        {
            /* Wait until Mode Register setting done. */
        }
    }

    /** Set timing parameters for SDRAM. Must do in single write. */
    R_BUS->SDRAM.SDTR = ((BSP_CFG_SDRAM_TRAS - 1U) << R_BUS_SDRAM_SDTR_RAS_Pos) |
                        ((BSP_CFG_SDRAM_TRCD - 1U) << R_BUS_SDRAM_SDTR_RCD_Pos) |
                        ((BSP_CFG_SDRAM_TRP - 1U) << R_BUS_SDRAM_SDTR_RP_Pos) |
                        ((BSP_CFG_SDRAM_TWR - 1U) << R_BUS_SDRAM_SDTR_WR_Pos) |
                        (BSP_CFG_SDRAM_TCL << R_BUS_SDRAM_SDTR_CL_Pos);

    /** Set row address offset for target SDRAM */
    R_BUS->SDRAM.SDADR = BSP_CFG_SDRAM_MULTIPLEX_ADDR_SHIFT;

    /* Set Auto-Refresh timings. */
    R_BUS->SDRAM.SDRFCR = ((BSP_CFG_SDRAM_TREFW - 1U) << R_BUS_SDRAM_SDRFCR_REFW_Pos) |
                          ((BSP_CFG_SDRAM_TRFC - 1U) << R_BUS_SDRAM_SDRFCR_RFC_Pos);

    /** Start Auto-refresh */
    R_BUS->SDRAM.SDRFEN = 1U;

    if (init_memory)
    {
        /** Enable SDRAM access */
        R_BUS->SDRAM.SDCCR = R_BUS_SDRAM_SDCCR_EXENB_Msk | (BSP_CFG_SDRAM_BUS_WIDTH << R_BUS_SDRAM_SDCCR_BSIZE_Pos);
    }
    else
    {
        /* If not initializing memory modules, start in self-refresh mode. */
        while (R_BUS->SDRAM.SDCCR_b.EXENB || (0U != R_BUS->SDRAM.SDSR))
        {
            /* Wait for access to be disabled and no status bits set. */
        }

        /* Enable the self-refresh mode. */
        R_BUS->SDRAM.SDSELF = 1U;
    }
}

/*******************************************************************************************************************//**
 * @brief   Changes SDRAM from Auto-refresh to Self-refresh
 *
 * This function allows Software Standby and Deep Software Standby modes to be entered without data loss.
 *
 * @note SDRAM cannot be accessed after calling this function. Use @ref R_BSP_SdramSelfRefreshDisable to resume normal
 *  SDRAM operation.
 **********************************************************************************************************************/
void R_BSP_SdramSelfRefreshEnable (void)
{
    R_BUS->SDRAM.SDCCR = (BSP_CFG_SDRAM_BUS_WIDTH << R_BUS_SDRAM_SDCCR_BSIZE_Pos);
    while (R_BUS->SDRAM.SDCCR_b.EXENB || (0U != R_BUS->SDRAM.SDSR))
    {
        /* Wait for access to be disabled and no status bits set. */
    }

    /* Enable the self-refresh mode. */
    R_BUS->SDRAM.SDSELF = 1U;
}

/*******************************************************************************************************************//**
 * @brief   Changes SDRAM from Self-refresh to Auto-refresh
 *
 * This function changes back to Auto-refresh and allows normal SDRAM operation to resume.
 *
 **********************************************************************************************************************/
void R_BSP_SdramSelfRefreshDisable (void)
{
    if (0 == R_SYSTEM->SDCKOCR)
    {
        /* Enable the SDCLK output. It may not already be enabled here if recovering from Deep Software Standby. */
        R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_CGC);
        R_SYSTEM->SDCKOCR = 1;
        R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_CGC);
    }

    while (0U != R_BUS->SDRAM.SDSR)
    {
        /* Wait for all status bits to be cleared. */
    }

    /* Disable the self-refresh mode. */
    R_BUS->SDRAM.SDSELF = 0U;

    /* Reenable SDRAM bus access. */
    R_BUS->SDRAM.SDCCR = R_BUS_SDRAM_SDCCR_EXENB_Msk | (BSP_CFG_SDRAM_BUS_WIDTH << R_BUS_SDRAM_SDCCR_BSIZE_Pos);
}

#endif

/** @} (end addtogroup BSP_SDRAM) */
