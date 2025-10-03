/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * File Name    : board_init.h
 * Description  : This module calls any initialization code specific to this BSP.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @ingroup BOARD_EK_RA4M1
 * @defgroup BOARD_EK_RA4M1_INIT Board Specific Code
 * @brief Board specific code for the EK_RA4M1 Board
 *
 * This include file is specific to the EK_RA4M1 board.
 *
 * @{
 **********************************************************************************************************************/

#ifndef BOARD_INIT_H
#define BOARD_INIT_H

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/
void bsp_init(void * p_args);

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/** @} (end defgroup BOARD_RA4M1_EK_INIT) */
