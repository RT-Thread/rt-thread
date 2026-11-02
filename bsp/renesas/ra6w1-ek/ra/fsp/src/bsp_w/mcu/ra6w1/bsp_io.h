/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @defgroup BSP_IO BSP I/O access
 * @ingroup RENESAS_COMMON
 * @brief This module provides basic read/write access to port pins.
 *
 * @{
 **********************************************************************************************************************/

#ifndef BSP_IO_RA6W1_H
#define BSP_IO_RA6W1_H

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define BSP_IO_PXX_SEL_REG(_port)        *(&(GPIO->GPIO_SEL_P0_REG) + (_port))
#define BSP_IO_PXX_SEL1_REG(_port)       *(&(GPIO->GPIO_SEL1_P0_REG) + (_port))
#define BSP_IO_PXX_POL_REG(_port)        *(&(GPIO->GPIO_INT_POL_P0_REG) + (_port))
#define BSP_IO_PXX_INT_STS_REG(_port)    *(&(GPIO->GPIO_INT_STS_P0_REG) + (_port))
#define BSP_IO_PXX_INT_CLR_REG(_port)    *(&(GPIO->GPIO_INT_CLR_P0_REG) + (_port))

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
 
/** Clocks that can be mapped to dedicated BSP_IO */
typedef enum e_bsp_io_clk_output_ra6w1
{
    BSP_IO_CLK_XTAL40M_OUT  = (GPIO_GPIO_CLK_SEL_REG_XTAL40M_OUTPUT_EN_Msk >> 4),  /**< Map clock XTAL40M to dedicated GPIO */
    BSP_IO_CLK_RC10M_OUT    = (GPIO_GPIO_CLK_SEL_REG_RC10M_OUTPUT_EN_Msk >> 4),    /**< Map clock RC10M to dedicated GPIO */
    BSP_IO_CLK_XTAL32K_OUT  = (GPIO_GPIO_CLK_SEL_REG_XTAL32K_OUTPUT_EN_Msk >> 4),  /**< Map clock XTAL32K to dedicated GPIO */
    BSP_IO_CLK_OSC32K_OUT   = (GPIO_GPIO_CLK_SEL_REG_OSC32K_OUTPUT_EN_Msk >> 4),   /**< Map clock OSC32K to dedicated GPIO */
    BSP_IO_CLK_FPLL98M_OUT  = (GPIO_GPIO_CLK_SEL_REG_FPLL98M_OUTPUT_EN_Msk >> 4),  /**< Map clock FPLL98M to dedicated GPIO */
    BSP_IO_CLK_DPLL480M_OUT = (GPIO_GPIO_CLK_SEL_REG_DPLL480M_OUTPUT_EN_Msk >> 4), /**< Map clock FPLL98M to dedicated GPIO */
    BSP_IO_CLK_MCLK_OUT     = (GPIO_GPIO_CLK_SEL_REG_MCLK_OUTPUT_EN_Msk >> 4),     /**< Map clock MCLK to dedicated GPIO */
    BSP_IO_CLK_NONE_OUT     = 0,
} bsp_io_clk_output_t;

/** Clocks that can be mapped to GPIO function FUNC_CLOCK */
typedef enum e_bsp_io_clk_func_ra6w1
{
    BSP_IO_CLK_XTAL40M_FUNC  = 1,      /**< Map clock XTAL40M to GPIO function FUNC_CLOCK */
    BSP_IO_CLK_RC10M_FUNC    = 2,      /**< Map clock RC10M to GPIO function FUNC_CLOCK */
    BSP_IO_CLK_XTAL32K_FUNC  = 3,      /**< Map clock XTAL32K to GPIO function FUNC_CLOCK */
    BSP_IO_CLK_OSC32K_FUNC   = 4,      /**< Map clock OSC32K to GPIO function FUNC_CLOCK */
    BSP_IO_CLK_FPLL98M_FUNC  = 5,      /**< Map clock FPLL98M to GPIO function FUNC_CLOCK */
    BSP_IO_CLK_DPLL480M_FUNC = 6,      /**< Map clock DPLL480M to GPIO function FUNC_CLOCK */
    BSP_IO_CLK_DIVN_FUNC     = 7,      /**< Map clock DIVn to GPIO function FUNC_CLOCK */
} bsp_io_clk_func_t;

/** @} (end addtogroup BSP_IO) */
/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
