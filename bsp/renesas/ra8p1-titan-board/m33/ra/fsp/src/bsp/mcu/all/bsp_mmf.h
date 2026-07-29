/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_MMF_H
#define BSP_MMF_H

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define MEMORY_MIRROR_REG_KEY      (0xDBU)
#define MEMORY_MIRROR_BOUNDARY     (0x80U) // 128 bytes
#define MEMORY_MIRROR_ADDR_MASK    (0x007FFFFFU)

/* The highest address which MMF able to support is the last address of code flash area which aligns with 128. */
#define MEMORY_MIRROR_MAX_ADDR     (BSP_FEATURE_FLASH_CODE_FLASH_START + BSP_ROM_SIZE_BYTES - MEMORY_MIRROR_BOUNDARY)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Enum for state of Memory Mirror Function. */
typedef enum e_mmf_state
{
    MEMORY_MIRROR_DISABLED = 0,
    MEMORY_MIRROR_ENABLED  = 1,
} mmf_state_t;

/** Status instance of Memory Mirror Function. */
typedef struct st_mmf_status
{
    mmf_state_t mmf_state;             // Current state of Memory Mirror Region.
    uint32_t    mmf_cur_addr;          // Current address in register MMSFR.
} mmf_status_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 *               Get the current status of Memory Mirror.
 *
 * @param[out]   p_mmf_status Pointer to instance which used for storing the state of MMF after invoked this function.
 *
 * @retval  FSP_SUCCESS             MMF status retrieved successfully.
 * @retval  FSP_ERR_UNSUPPORTED     MCU does not support MMF.
 * @retval  FSP_ERR_ASSERTION       NULL pointer passed as argument.
 *
 * This function retrieves the current state of the MMF and the mirrored address into a user provided structure.
 **********************************************************************************************************************/
__STATIC_INLINE fsp_err_t R_BSP_MemoryMirrorStatusGet (mmf_status_t * p_mmf_status)
{
#if BSP_FEATURE_BSP_MMF_SUPPORTED
 #if BSP_CFG_PARAM_CHECKING_ENABLE

    /* Ensure that variable for storing the status of MMF was provided. */
    if (NULL == p_mmf_status)
    {
        return FSP_ERR_ASSERTION;
    }
 #endif

    p_mmf_status->mmf_state    = (mmf_state_t) R_MMF->MMEN_b.EN;
    p_mmf_status->mmf_cur_addr = R_MMF->MMSFR & MEMORY_MIRROR_ADDR_MASK;

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_mmf_status);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 *              Set address for MMF region.
 *
 * @param[in]   addr Address of memory region to be mirrored into MMF region.
 *
 * @retval  FSP_SUCCESS                 Address is set successfully.
 * @retval  FSP_ERR_UNSUPPORTED         MCU does not support MMF.
 * @retval  FSP_ERR_INVALID_ADDRESS     Requested address is out of supported range.
 *
 * This function sets the memory address to be mirrored by MMF.
 **********************************************************************************************************************/
__STATIC_INLINE fsp_err_t R_BSP_MemoryMirrorAddrSet (const uint32_t addr)
{
#if BSP_FEATURE_BSP_MMF_SUPPORTED
 #if BSP_CFG_PARAM_CHECKING_ENABLE

    /* Ensure that requested address is in supported range and must align with 128 */
    if ((MEMORY_MIRROR_MAX_ADDR < addr) || (0 != addr % MEMORY_MIRROR_BOUNDARY))
    {
        return FSP_ERR_INVALID_ADDRESS;
    }
 #endif

    /* If MMF is enabled, disable MMF before updating the address register.
     * For disabling MMF, write 0xDB00 to register MMEN. */
    if (1U == R_MMF->MMEN_b.EN)
    {
        R_MMF->MMEN = ((uint32_t) (MEMORY_MIRROR_REG_KEY << R_MMF_MMSFR_KEY_Pos) | 0U);
    }

    R_MMF->MMSFR = ((uint32_t) (MEMORY_MIRROR_REG_KEY << R_MMF_MMSFR_KEY_Pos) | addr);

    /* Enable MMF by writing 0xDB01 to register MMEN. After this point target memory address will be reflected into
     * MMF region. */
    R_MMF->MMEN = ((uint32_t) (MEMORY_MIRROR_REG_KEY << R_MMF_MMSFR_KEY_Pos) | 1U);

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(addr);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER
#endif

/** @} (end addtogroup BSP_MCU) */
