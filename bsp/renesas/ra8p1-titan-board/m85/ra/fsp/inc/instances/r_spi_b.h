/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_SPI_B_H
#define R_SPI_B_H

/*******************************************************************************************************************//**
 * @addtogroup SPI_B
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_spi_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/*************************************************************************************************
 * Type defines for the SPI interface API
 *************************************************************************************************/

/** 3-Wire or 4-Wire mode. */
typedef enum e_spi_b_ssl_mode
{
    SPI_B_SSL_MODE_SPI,                ///< SPI operation (4-wire method)
    SPI_B_SSL_MODE_CLK_SYN             ///< Clock Synchronous operation (3-wire method)
} spi_b_ssl_mode_t;

/** Transmit Only (Half Duplex), or Full Duplex. */
typedef enum e_spi_b_communication
{
    SPI_B_COMMUNICATION_FULL_DUPLEX,   ///< Full-Duplex synchronous serial communication
    SPI_B_COMMUNICATION_TRANSMIT_ONLY, ///< Transit only serial communication
} spi_b_communication_t;

/** Slave Select Polarity. */
typedef enum e_spi_b_sslp
{
    SPI_B_SSLP_LOW,                    ///< SSLP signal polarity active low
    SPI_B_SSLP_HIGH                    ///< SSLP signal polarity active high
} spi_b_ssl_polarity_t;

/** The Slave Select Line */
typedef enum e_spi_b_ssl_select
{
    SPI_B_SSL_SELECT_SSL0,             ///< Select SSL0
    SPI_B_SSL_SELECT_SSL1,             ///< Select SSL1
    SPI_B_SSL_SELECT_SSL2,             ///< Select SSL2
    SPI_B_SSL_SELECT_SSL3              ///< Select SSL3
} spi_b_ssl_select_t;

/** MOSI Idle Behavior. */
typedef enum e_spi_b_mosi_idle_value_fixing
{
    SPI_B_MOSI_IDLE_VALUE_FIXING_DISABLE, ///< MOSI output value=value set in MOIFV bit
    SPI_B_MOSI_IDLE_VALUE_FIXING_LOW,     ///< MOSIn level low during MOSI idling
    SPI_B_MOSI_IDLE_VALUE_FIXING_HIGH     ///< MOSIn level high during MOSI idling
} spi_b_mosi_idle_value_fixing_t;

/** Parity Mode */
typedef enum e_spi_b_parity_mode
{
    SPI_B_PARITY_MODE_DISABLE,         ///< Disable parity
    SPI_B_PARITY_MODE_ODD,             ///< Select even parity
    SPI_B_PARITY_MODE_EVEN             ///< Select odd parity
} spi_b_parity_t;

/** Byte Swapping Enable/Disable. */
typedef enum
{
    SPI_B_BYTE_SWAP_DISABLE = 0,       ///< Disable Byte swapping for 16/32-Bit transfers
    SPI_B_BYTE_SWAP_ENABLE             ///< Enable Byte swapping for 16/32-Bit transfers
} spi_b_byte_swap_t;

/** Delay count for SPI delay settings. */
typedef enum e_spi_b_clock_delay_count
{
    SPI_B_DELAY_COUNT_1,               ///< Set RSPCK delay count to 1 RSPCK
    SPI_B_DELAY_COUNT_2,               ///< Set RSPCK delay count to 2 RSPCK
    SPI_B_DELAY_COUNT_3,               ///< Set RSPCK delay count to 3 RSPCK
    SPI_B_DELAY_COUNT_4,               ///< Set RSPCK delay count to 4 RSPCK
    SPI_B_DELAY_COUNT_5,               ///< Set RSPCK delay count to 5 RSPCK
    SPI_B_DELAY_COUNT_6,               ///< Set RSPCK delay count to 6 RSPCK
    SPI_B_DELAY_COUNT_7,               ///< Set RSPCK delay count to 7 RSPCK
    SPI_B_DELAY_COUNT_8                ///< Set RSPCK delay count to 8 RSPCK
} spi_b_delay_count_t;

/** SPI communication clock source. */
typedef enum e_spi_b_clock_source
{
    SPI_B_CLOCK_SOURCE_SCISPICLK,
    SPI_B_CLOCK_SOURCE_PCLK
} spi_b_clock_source_t;

/** SPI Clock Divider settings. */
typedef struct
{
    uint8_t spbr;                      ///< SPBR register setting
    uint8_t brdv : 2;                  ///< BRDV setting in SPCMD0
} rspck_div_setting_t;

/** Extended SPI interface configuration */
typedef struct st_spi_b_extended_cfg
{
    spi_b_ssl_mode_t               spi_clksyn;         ///< Select SPI or Clock Synchronous mode operation
    spi_b_communication_t          spi_comm;           ///< Select full-duplex or transmit-only communication
    spi_b_ssl_polarity_t           ssl_polarity;       ///< Select SSLn signal polarity
    spi_b_ssl_select_t             ssl_select;         ///< Select which slave to use: 0-SSL0, 1-SSL1, 2-SSL2, 3-SSL3
    spi_b_mosi_idle_value_fixing_t mosi_idle;          ///< Select MOSI idle fixed value and selection
    spi_b_parity_t                 parity;             ///< Select parity and enable/disable parity
    spi_b_byte_swap_t              byte_swap;          ///< Select byte swap mode
    spi_b_clock_source_t           clock_source;       ///< Communication clock source (TCLK).
    rspck_div_setting_t            spck_div;           ///< Register values for configuring the SPI Clock Divider.
    spi_b_delay_count_t            spck_delay;         ///< SPI Clock Delay Register Setting
    spi_b_delay_count_t            ssl_negation_delay; ///< SPI Slave Select Negation Delay Register Setting
    spi_b_delay_count_t            next_access_delay;  ///< SPI Next-Access Delay Register Setting
} spi_b_extended_cfg_t;

/** Channel control block. DO NOT INITIALIZE.  Initialization occurs when @ref spi_api_t::open is called. */
typedef struct st_spi_b_instance_ctrl
{
    uint32_t          open;            ///< Indicates whether the open() API has been successfully called.
    spi_cfg_t const * p_cfg;           ///< Pointer to instance configuration
    R_SPI_B0_Type   * p_regs;          ///< Base register for this channel
    void const      * p_tx_data;       ///< Buffer to transmit
    void            * p_rx_data;       ///< Buffer to receive
    uint32_t          tx_count;        ///< Number of Data Frames to transfer (8-bit, 16-bit, 32-bit)
    uint32_t          rx_count;        ///< Number of Data Frames to transfer (8-bit, 16-bit, 32-bit)
    uint32_t          count;           ///< Number of Data Frames to transfer (8-bit, 16-bit, 32-bit)
    spi_bit_width_t   bit_width;       ///< Bits per Data frame (8-bit, 16-bit, 32-bit)

    /* Pointer to callback and optional working memory */
    void (* p_callback)(spi_callback_args_t *);
    spi_callback_args_t * p_callback_memory;

    /* Pointer to context to be passed into callback function */
    void * p_context;
} spi_b_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const spi_api_t g_spi_on_spi_b;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_SPI_B_Open(spi_ctrl_t * p_api_ctrl, spi_cfg_t const * const p_cfg);

fsp_err_t R_SPI_B_Read(spi_ctrl_t * const    p_api_ctrl,
                       void                * p_dest,
                       uint32_t const        length,
                       spi_bit_width_t const bit_width);

fsp_err_t R_SPI_B_Write(spi_ctrl_t * const    p_api_ctrl,
                        void const          * p_src,
                        uint32_t const        length,
                        spi_bit_width_t const bit_width);

fsp_err_t R_SPI_B_WriteRead(spi_ctrl_t * const    p_api_ctrl,
                            void const          * p_src,
                            void                * p_dest,
                            uint32_t const        length,
                            spi_bit_width_t const bit_width);

fsp_err_t R_SPI_B_Close(spi_ctrl_t * const p_api_ctrl);

fsp_err_t R_SPI_B_CalculateBitrate(uint32_t bitrate, spi_b_clock_source_t clock_source, rspck_div_setting_t * spck_div);
fsp_err_t R_SPI_B_CallbackSet(spi_ctrl_t * const          p_api_ctrl,
                              void (                    * p_callback)(spi_callback_args_t *),
                              void * const                p_context,
                              spi_callback_args_t * const p_callback_memory);

/*******************************************************************************************************************//**
 * @} (end ingroup SPI_B)
 **********************************************************************************************************************/

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
