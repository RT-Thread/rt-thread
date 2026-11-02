/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_SPI_W_H
#define R_SPI_W_H

/*******************************************************************************************************************//**
 * @addtogroup SPI_W
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_spi_api.h"
#include "r_spi_w_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** Offset to make the SPI HW channels 0-based for the r_spi driver. */
#if (BSP_FEATURE_SPI_VALID_CHANNEL_MASK & 0x1)
 #define SPI_W_CHANNEL_OFFSET                0
#elif (BSP_FEATURE_SPI_VALID_CHANNEL_MASK & 0x2)
 #define SPI_W_CHANNEL_OFFSET                1
#endif

#if BSP_MCU_GROUP_RA6W3
 /* Maximum Tx FIFO buffer size (SPI1) */
 #define SPI_W_TX_FIFO_MAX_SIZE_BYTE_SPI1    (256)

 /* Maximum Tx FIFO buffer size (SPI2, SPI3) */
 #define SPI_W_TX_FIFO_MAX_SIZE_BYTE         (32)

 /* Maximum Rx FIFO buffer size (SPI1, SPI2, SPI3) */
 #define SPI_W_RX_FIFO_MAX_SIZE_BYTE         (32)
#else
 /* Maximum RX FIFO buffer size. */
 #define SPI_W_RX_FIFO_MAX_SIZE_BYTE         (32)
#endif

#if SPI_W_CFG_FAST_MODE_ENABLE
#define SPI_W_FAST_READ_HEADER_SIZE          8
#endif

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** The Chip Select Line. */
typedef enum e_spi_w_cs_select
{
    SPI_W_CS_SELECT_CS0 = 1,           ///< Select CS0
    SPI_W_CS_SELECT_CS1 = 2,           ///< Select CS1
} spi_w_cs_select_t;

/** Byte Swapping Enable/Disable. */
typedef enum e_spi_w_byte_swap
{
    SPI_W_BYTE_SWAP_DISABLE = 0,       ///< Disable Byte swapping for 16/32-Bit transfers.
    SPI_W_BYTE_SWAP_ENABLE,            ///< Enable Byte swapping for 16/32-Bit transfers.
} spi_w_byte_swap_t;

/** Capture data at current/next clock edge. */
typedef enum e_spi_w_capture_edge
{
    SPI_W_CAPTURE_CURRENT_EDGE = 0,    ///< SPI captures data at current clock edge.
    SPI_W_CAPTURE_NEXT_EDGE,           ///< SPI captures data at next clock edge. (only for Master mode & high bitrate).
} spi_w_capture_edge_t;

/** Extended SPI interface configuration */
typedef struct st_spi_w_extended_cfg
{
    spi_w_cs_select_t     cs_select;         ///< Select which slave to use: 0-CS0, 1-CS1.
    spi_w_byte_swap_t     byte_swap;         ///< Select byte swap mode.
    spi_w_capture_edge_t  cap_edge;          ///< Select capture clock edge.
    uint32_t              rx_fifo_lvl_thres; ///< Set fifo level threshold for rx.
    uint32_t              tx_fifo_lvl_thres; ///< Set fifo level threshold for tx.
    uint8_t               spck_div;          ///< Register value for configuring the SPI Clock Divider.
    uint8_t               gen_ipl;           ///< Generic interrupt priority.
    IRQn_Type             gen_irq;           ///< Generic interrrupt IRQ number.
#if SPI_W_CFG_FAST_MODE_ENABLE
    bool                  skip_disable;      ///< SPI will not be disabled after a read/write cycle for fast reaction.
#endif
    bool                  skip_busy_check;   ///< If true, SPI will not check for busy state on read.
} spi_w_extended_cfg_t;

#if SPI_W_CFG_FAST_MODE_ENABLE
/** Add descryption for fast mode */
typedef enum e_spi_w_fast_mode
{
    SPI_W_FAST_MODE_OFF         = 0,   ///< Set SPI fast mode disable
    SPI_W_FAST_MODE_ON                 ///< Set SPI fast mode for read sequence
} spi_w_fast_mode_t;
#endif

/** Channel control block. DO NOT INITIALIZE.  Initialization occurs when @ref spi_api_t::open is called. */
typedef struct st_spi_w_instance_ctrl
{
    uint32_t          open;            ///< Indicates whether the open() API has been successfully called.
    spi_cfg_t const * p_cfg;           ///< Pointer to instance configuration.
    SPI_Type        * p_regs;          ///< Base register for this channel.
    void const      * p_tx_data;       ///< Buffer to transmit.
    void            * p_rx_data;       ///< Buffer to receive.
    uint32_t          tx_count;        ///< Number of Data Frames to transmit (8-bit, 16-bit, 32-bit).
    uint32_t          rx_count;        ///< Number of Data Frames to receive (8-bit, 16-bit, 32-bit).
    uint32_t          count;           ///< Number of Data Frames to transfer (8-bit, 16-bit, 32-bit).
    spi_bit_width_t   bit_width;       ///< Bits per Data frame.
    uint32_t          mask_width;      ///< Bit width mask for data.
    uint8_t           wordsize;        ///< Word size of current transmit.
#if SPI_W_CFG_FAST_MODE_ENABLE
    uint8_t           fast_mode_st;    ///< State the data transfer mode.
    uint32_t          fast_max_count;  ///< Number of Data Frames to transfer in fast mode.
    uint8_t           fast_mode_buffer[SPI_W_FAST_READ_HEADER_SIZE]; ///< Buffer receive header.
#endif

    /* Pointer to callback and optional working memory */
    void (* p_callback)(spi_callback_args_t *);
    spi_callback_args_t * p_callback_memory;

    /* Pointer to context to be passed into callback function */
    void * p_context;
} spi_w_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const spi_api_t g_spi_on_spi_w;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_SPI_W_Open(spi_ctrl_t * p_api_ctrl, spi_cfg_t const * const p_cfg);

fsp_err_t R_SPI_W_Read(spi_ctrl_t * const    p_api_ctrl,
                       void                * p_dest,
                       uint32_t const        length,
                       spi_bit_width_t const bit_width);

fsp_err_t R_SPI_W_Write(spi_ctrl_t * const    p_api_ctrl,
                        void const          * p_src,
                        uint32_t const        length,
                        spi_bit_width_t const bit_width);

fsp_err_t R_SPI_W_WriteRead(spi_ctrl_t * const    p_api_ctrl,
                            void const          * p_src,
                            void                * p_dest,
                            uint32_t const        length,
                            spi_bit_width_t const bit_width);

fsp_err_t R_SPI_W_Close(spi_ctrl_t * const p_api_ctrl);

fsp_err_t R_SPI_W_CalculateBitrate(uint32_t bitrate, uint8_t * spck_div, uint8_t channel);

fsp_err_t R_SPI_W_CallbackSet(spi_ctrl_t * const          p_api_ctrl,
                              void (                    * p_callback)(spi_callback_args_t *),
                              void * const                p_context,
                              spi_callback_args_t * const p_callback_memory);

#if SPI_W_CFG_FAST_MODE_ENABLE
fsp_err_t R_SPI_W_FastRead(spi_ctrl_t * const    p_api_ctrl,
                           void                * p_dest,
                           uint32_t const        length,
                           uint32_t const        max_count,
                           spi_bit_width_t const bit_width);
#endif

/*******************************************************************************************************************//**
 * @} (end ingroup SPI_W)
 **********************************************************************************************************************/

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_SPI_W_H
