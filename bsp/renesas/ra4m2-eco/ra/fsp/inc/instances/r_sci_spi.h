/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

#ifndef R_SCI_SPI_H
#define R_SCI_SPI_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_spi_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*****************************************************************************************************************//**
 * @ingroup SCI_SPI
 * @{
 ********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Settings for adjusting the SPI CLK. */
typedef struct
{
    uint8_t brr;
    uint8_t cks : 2;
    uint8_t mddr;                      ///< Set to 0 to disable MDDR.
} sci_spi_div_setting_t;

/** SCI SPI extended configuration */
typedef struct st_sci_spi_extended_cfg
{
    sci_spi_div_setting_t clk_div;
} sci_spi_extended_cfg_t;

/** SPI instance control block. DO NOT INITIALIZE. */
typedef struct st_sci_spi_instance_ctrl
{
    uint32_t          open;
    spi_cfg_t const * p_cfg;
    R_SCI0_Type     * p_reg;
    uint8_t         * p_src;
    uint8_t         * p_dest;
    uint32_t          tx_count;
    uint32_t          rx_count;
    uint32_t          count;

    /* Pointer to callback and optional working memory */
    void (* p_callback)(spi_callback_args_t *);
    spi_callback_args_t * p_callback_memory;

    /* Pointer to context to be passed into callback function */
    void const * p_context;
} sci_spi_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const spi_api_t g_spi_on_sci;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t R_SCI_SPI_Open(spi_ctrl_t * p_api_ctrl, spi_cfg_t const * const p_cfg);
fsp_err_t R_SCI_SPI_Read(spi_ctrl_t * const    p_api_ctrl,
                         void                * p_dest,
                         uint32_t const        length,
                         spi_bit_width_t const bit_width);
fsp_err_t R_SCI_SPI_Write(spi_ctrl_t * const    p_api_ctrl,
                          void const          * p_src,
                          uint32_t const        length,
                          spi_bit_width_t const bit_width);
fsp_err_t R_SCI_SPI_WriteRead(spi_ctrl_t * const    p_api_ctrl,
                              void const          * p_src,
                              void                * p_dest,
                              uint32_t const        length,
                              spi_bit_width_t const bit_width);
fsp_err_t R_SCI_SPI_Close(spi_ctrl_t * const p_api_ctrl);
fsp_err_t R_SCI_SPI_CalculateBitrate(uint32_t bitrate, sci_spi_div_setting_t * sclk_div, bool use_mddr);
fsp_err_t R_SCI_SPI_CallbackSet(spi_ctrl_t * const          p_api_ctrl,
                                void (                    * p_callback)(spi_callback_args_t *),
                                void const * const          p_context,
                                spi_callback_args_t * const p_callback_memory);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end ingroup SCI_SPI)
 **********************************************************************************************************************/
