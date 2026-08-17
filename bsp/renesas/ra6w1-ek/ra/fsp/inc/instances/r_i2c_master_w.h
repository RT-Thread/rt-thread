/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup I2C_MASTER_W
 * @{
 **********************************************************************************************************************/

#ifndef R_I2C_MASTER_W_H
#define R_I2C_MASTER_W_H

#include "r_i2c_master_w_cfg.h"
#include "r_i2c_master_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**
 *  I2C high speed master code.
 *  This bit field holds the value of the I2C HS mode master code.
 *  HS-mode master codes are reserved 8-bit codes (00001xxx)
 *  that are not used for slave addressing or other purposes.
 *  Each master has its unique master code.
 *  Up to eight high-speed mode masters can be present on the same I2C bus system.
 *  Valid values are from 0 to 7.
 *  This can be written only when the I2C interface is disabled,
 *  which corresponds to the IC_ENABLE[0] register being set to 0.
 *  Writes at other times have no effect.
 *
 */
#define I2C_MASTER_W_I2C1_MADDR         0x01
#define I2C_MASTER_W_I2C2_MADDR         0x05
#define I2C_MASTER_W_I2C3_MADDR         0x07

/**  TX/RX FIFO depth */
#define I2C_MASTER_W_FIFO_DEPTH         (32)

/** Offset to make the I2C HW channels 0-based for the r_i2c_master_w driver. */
#if (BSP_FEATURE_I2C_VALID_CHANNEL_MASK & 0x1)
 #define I2C_MASTER_W_CHANNEL_OFFSET    0
#elif (BSP_FEATURE_I2C_VALID_CHANNEL_MASK & 0x2)
 #define I2C_MASTER_W_CHANNEL_OFFSET    1
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** I2C interrupt source */
typedef enum e_i2c_master_w_int
{
    I2C_MASTER_W_INT_RX_UNDERFLOW   = I2C_I2C_INTR_STAT_REG_R_RX_UNDER_Msk,  ///< Attempt to read from empty RX FIFO has been made
    I2C_MASTER_W_INT_RX_OVERFLOW    = I2C_I2C_INTR_STAT_REG_R_RX_OVER_Msk,   ///< RX FIFO is full but new data are incoming and being discarded
    I2C_MASTER_W_INT_RX_FULL        = I2C_I2C_INTR_STAT_REG_R_RX_FULL_Msk,   ///< RX FIFO level is equal or above threshold
    I2C_MASTER_W_INT_TX_OVERFLOW    = I2C_I2C_INTR_STAT_REG_R_TX_OVER_Msk,   ///< Attempt to write to TX FIFO which is already full
    I2C_MASTER_W_INT_TX_EMPTY       = I2C_I2C_INTR_STAT_REG_R_TX_EMPTY_Msk,  ///< TX FIFO level is  equal or below threshold
    I2C_MASTER_W_INT_READ_REQUEST   = I2C_I2C_INTR_STAT_REG_R_RD_REQ_Msk,    ///< I2C master attempts to read data(slave only)
    I2C_MASTER_W_INT_TX_ABORT       = I2C_I2C_INTR_STAT_REG_R_TX_ABRT_Msk,   ///< TX cannot be completed
    I2C_MASTER_W_INT_RX_DONE        = I2C_I2C_INTR_STAT_REG_R_RX_DONE_Msk,   ///< I2C master did not acknowledge transmitted byte(slave only)
    I2C_MASTER_W_INT_ACTIVITY       = I2C_I2C_INTR_STAT_REG_R_ACTIVITY_Msk,  ///< Any I2C activity occurred
    I2C_MASTER_W_INT_STOP_DETECTED  = I2C_I2C_INTR_STAT_REG_R_STOP_DET_Msk,  ///< STOP condition occurred
    I2C_MASTER_W_INT_START_DETECTED = I2C_I2C_INTR_STAT_REG_R_START_DET_Msk, ///< START/RESTART condition occurred
    I2C_MASTER_W_INT_GENERAL_CALL   = I2C_I2C_INTR_STAT_REG_R_GEN_CALL_Msk   ///< General Call address received(slave only)
} i2c_master_w_int_t;

/** I2C clock settings */
typedef struct i2c_master_w_clock_settings
{
    uint16_t scl_hcnt;                 ///< I2C clock (SCL) high count
    uint16_t scl_lcnt;                 ///< I2C clock (SCL) low count
} i2c_master_w_clock_settings_t;

/** I2C control structure. DO NOT INITIALIZE. */
typedef struct st_i2c_master_w_instance_ctrl
{
    i2c_master_cfg_t const * p_cfg;                                                // Pointer to the configuration structure
    uint32_t                 slave;                                                // The address of the slave device
    i2c_master_addr_mode_t   addr_mode;                                            // Indicates how slave fields should be interpreted

    uint32_t   open;                                                               // Flag to determine if the device is open
    I2C_Type * p_reg;                                                              // Base register for this channel

    /* Current transfer information. */
    uint8_t * p_buff;                                                              // Holds the data associated with the transfer
#if (I2C_MASTER_W_CFG_DTC_ENABLE) || (I2C_MASTER_W_CFG_DMA_ENABLE)
    uint16_t p_transfer_api_tx_buff[I2C_MASTER_W_CFG_TRANSFER_API_TX_BUFFER_SIZE]; // Holds the data associated with the DTC/DMA transfer
#endif
    uint32_t total;                                                                // Holds the total number of data bytes to transfer
    uint32_t nof_bytes;                                                            // Tracks the read bytes in a tranfer
    uint32_t loaded;                                                               // Tracks the number of data bytes written to the register

    volatile bool read;                                                            // Holds the direction of the data byte transfer
    volatile bool restart;                                                         // Holds whether or not the restart should be issued when done
    volatile bool restarted;                                                       // Tracks whether or not a restart was issued during the previous transfer

    /* Pointer to callback and optional working memory */
    void (* p_callback)(i2c_master_callback_args_t *);
    i2c_master_callback_args_t * p_callback_memory;

    /* Pointer to context to be passed into callback function */
    void * p_context;
} i2c_master_w_instance_ctrl_t;

/** R_I2C extended configuration */
typedef struct st_i2c_master_w_extended_cfg
{
#if I2C_MASTER_W_CFG_DMA_ENABLE
    bool enable_dma_bursts_tx;                    ///< Enable DMA Burst TX Transactions when the transaction length is 4- or 8-byte aligned
    bool enable_dma_bursts_rx;                    ///< Enable DMA Burst RX Transactions when the transaction length is 4- or 8-byte aligned
#endif
    i2c_master_w_clock_settings_t clock_settings; ///< I2C Clock settings
    bool      select_divn;                        ///< Select the clock source (DIVN/DIV1 clock)
    IRQn_Type gen_irq;                            ///< Generic I2C Interrupt IRQ number.
    uint8_t   gen_ipl;                            ///< Generic I2C Interrupt Priority.
} i2c_master_w_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern i2c_master_api_t const g_i2c_master_on_i2c_w;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_I2C_MASTER_W_Open(i2c_master_ctrl_t * const p_api_ctrl, i2c_master_cfg_t const * const p_cfg);

fsp_err_t R_I2C_MASTER_W_Read(i2c_master_ctrl_t * const p_api_ctrl,
                              uint8_t * const           p_dest,
                              uint32_t const            bytes,
                              bool const                restart);
fsp_err_t R_I2C_MASTER_W_Write(i2c_master_ctrl_t * const p_api_ctrl,
                               uint8_t * const           p_src,
                               uint32_t const            bytes,
                               bool const                restart);
fsp_err_t R_I2C_MASTER_W_Abort(i2c_master_ctrl_t * const p_api_ctrl);
fsp_err_t R_I2C_MASTER_W_SlaveAddressSet(i2c_master_ctrl_t * const    p_api_ctrl,
                                         uint32_t const               slave,
                                         i2c_master_addr_mode_t const addr_mode);
fsp_err_t R_I2C_MASTER_W_Close(i2c_master_ctrl_t * const p_api_ctrl);
fsp_err_t R_I2C_MASTER_W_CallbackSet(i2c_master_ctrl_t * const          p_api_ctrl,
                                     void (                           * p_callback)(i2c_master_callback_args_t *),
                                     void * const                       p_context,
                                     i2c_master_callback_args_t * const p_callback_memory);
fsp_err_t R_I2C_MASTER_W_StatusGet(i2c_master_ctrl_t * const p_api_ctrl, i2c_master_status_t * p_status);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_I2C_MASTER_W_H

/*******************************************************************************************************************//**
 * @} (end defgroup I2C_MASTER_W)
 **********************************************************************************************************************/
