/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"

#ifdef UNIT_TESTING
 #include "fake_regs.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define ASCII_3095    (('3' << 24) | ('0' << 16) | ('9' << 8) | '5') /* 0x33303935 = '3' '0' '9' '5' */

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

static uint32_t bsp_prv_chip_revision BSP_PLACE_IN_SECTION(BSP_SECTION_NOINIT);

/*******************************************************************************************************************//**
 * Check whether we are running on RA6W1 revision A.
 *
 * @retval true if we are running on RA6W1 revision A, false otherwise.
 **********************************************************************************************************************/
bool bsp_is_chip_revision_a (void)
{
    return bsp_prv_chip_revision == 0;
}

/*******************************************************************************************************************//**
 * Initialize chip revision and check whether we are running on RA6W1 chip.
 *
 * @retval true if we are running on RA6W1 chip, false otherwise.
 **********************************************************************************************************************/
bool bsp_device_info_init (void)
{
    union
    {
        uint8_t  arr[4];
        uint32_t value;
    } device_chip_id;

    /* Initial chip revision is 'A'. Subtract 'A' to get numeric value. */
    bsp_prv_chip_revision = CHIP_VERSION->CHIP_REVISION_REG_b.CHIP_REVISION - 'A';

    device_chip_id.arr[3] = CHIP_VERSION->CHIP_ID1_REG_b.CHIP_ID1;
    device_chip_id.arr[2] = CHIP_VERSION->CHIP_ID2_REG_b.CHIP_ID2;
    device_chip_id.arr[1] = CHIP_VERSION->CHIP_ID3_REG_b.CHIP_ID3;
    device_chip_id.arr[0] = CHIP_VERSION->CHIP_ID4_REG_b.CHIP_ID4;

    return device_chip_id.value == ASCII_3095;
}

/** @} (end addtogroup BSP_MCU_PRV) */
