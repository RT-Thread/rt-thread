/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_OTP_RA6W1_H
#define BSP_OTP_RA6W1_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"
#ifdef UNIT_TESTING
 #include "fake_regs.h"
#endif

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define BSP_OTP_CELL_NUM       (0x1FF) /* Max number of OTP cells, each cell size is 4 bytes last offset is used for OTP lock */
#define BSP_OTP_LOCK_OFFSET    (0x1FF) /* Max number of OTP cells, each cell size is 4 bytes last offset is used for OTP lock */
#define MEMORY_OTP_BASE        0x400F2000UL
#define MEMORY_OTP_END         0x400F2800UL

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** OTP Controller modes */
typedef enum e_bsp_otpc_mode
{
    BSP_OTP_MODE_DSTBY = 0,            /**< OTP cell is powered on LDO is inactive*/
    BSP_OTP_MODE_STBY  = 1,            /**< OTP cell and LDO are powered on, chip select is deactivated*/
    BSP_OTP_MODE_READ  = 2,            /**< OTP cell can be read*/
    BSP_OTP_MODE_PROG  = 3,            /**< OTP cell can be programmed*/
    BSP_OTP_MODE_PVFY  = 4,            /**< OTP cell can be read in PVFY margin read mode*/
    BSP_OTP_MODE_RINI  = 5             /**< OTP cell can be read in RINI margin read mode*/
} bsp_otpc_mode_t;

/** System clock frequency in MHz */
typedef enum e_bsp_otpc_clk_freq
{
    BSP_OTPC_CLK_FREQ_40MHz = 0,
    BSP_OTPC_CLK_FREQ_80MHz = 1,
} bsp_otpc_clk_freq_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

uint32_t bsp_otp_word_read(uint32_t cell_offset);
void     bsp_otp_read(uint32_t * p_data, uint32_t cell_offset, uint32_t num_words);
uint32_t bsp_otp_word_prog(uint32_t data, uint32_t cell_offset);
void     bsp_otp_prog(const uint32_t * p_data, uint32_t cell_offset, uint32_t num_words);
bool     bsp_otp_prog_and_verify(const uint32_t * p_data, uint32_t cell_offset, uint32_t num_words);
uint32_t bsp_otp_lock(uint8_t cell_region);
uint32_t bsp_otp_get_lock_region(void);

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
