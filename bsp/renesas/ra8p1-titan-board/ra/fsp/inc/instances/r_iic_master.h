/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup IIC_MASTER
 * @{
 **********************************************************************************************************************/

#ifndef R_IIC_MASTER_H
#define R_IIC_MASTER_H

#include "bsp_api.h"
#include "r_iic_master_cfg.h"
#include "r_i2c_master_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** I2C Timeout mode parameter definition */
typedef enum e_iic_master_timeout_mode
{
    IIC_MASTER_TIMEOUT_MODE_LONG  = 0, ///< Timeout Detection Time Select: Long Mode -> TMOS = 0
    IIC_MASTER_TIMEOUT_MODE_SHORT = 1  ///< Timeout Detection Time Select: Short Mode -> TMOS = 1
} iic_master_timeout_mode_t;

typedef enum e_iic_master_timeout_scl_low
{
    IIC_MASTER_TIMEOUT_SCL_LOW_DISABLED = 0, ///< Timeout detection during SCL low disabled
    IIC_MASTER_TIMEOUT_SCL_LOW_ENABLED  = 1  ///< Timeout detection during SCL low enabled
} iic_master_timeout_scl_low_t;

/** I2C clock settings */
typedef struct iic_master_clock_settings
{
    uint8_t cks_value;                 ///< Internal Reference Clock Select
    uint8_t brh_value;                 ///< High-level period of SCL clock
    uint8_t brl_value;                 ///< Low-level period of SCL clock
    uint8_t sddl_value;                // < SDA Output Delay Counter
    bool    dlcs_value;                // < SDA Output Delay Clock Source
} iic_master_clock_settings_t;

/** I2C control structure. DO NOT INITIALIZE. */
typedef struct st_iic_master_instance_ctrl
{
    i2c_master_cfg_t const * p_cfg;     // Pointer to the configuration structure
    uint32_t                 slave;     // The address of the slave device
    i2c_master_addr_mode_t   addr_mode; // Indicates how slave fields should be interpreted

    uint32_t      open;                 // Flag to determine if the device is open
    R_IIC0_Type * p_reg;                // Base register for this channel

    /* Current transfer information. */
    uint8_t * p_buff;                   // Holds the data associated with the transfer
    uint32_t  total;                    // Holds the total number of data bytes to transfer
    uint32_t  remain;                   // Tracks the remaining data bytes to transfer
    uint32_t  loaded;                   // Tracks the number of data bytes written to the register

    uint8_t addr_low;                   // Holds the last address byte to issue
    uint8_t addr_high;                  // Holds the first address byte to issue in 10-bit mode
    uint8_t addr_total;                 // Holds the total number of address bytes to transfer
    uint8_t addr_remain;                // Tracks the remaining address bytes to transfer
    uint8_t addr_loaded;                // Tracks the number of address bytes written to the register

    volatile bool read;                 // Holds the direction of the data byte transfer
    volatile bool restart;              // Holds whether or not the restart should be issued when done
    volatile bool err;                  // Tracks whether or not an error occurred during processing
    volatile bool restarted;            // Tracks whether or not a restart was issued during the previous transfer
    volatile bool dummy_read_completed; // Tracks whether the dummy read is performed
    volatile bool activation_on_rxi;    // Tracks whether the transfer is activated on RXI interrupt
    volatile bool activation_on_txi;    // Tracks whether the transfer is activated on TXI interrupt
    volatile bool address_restarted;    // Tracks whether the restart condition is send on 10 bit read

    /* Pointer to callback and optional working memory */
    void (* p_callback)(i2c_master_callback_args_t *);
    i2c_master_callback_args_t * p_callback_memory;

    /* Pointer to context to be passed into callback function */
    void * p_context;
} iic_master_instance_ctrl_t;

/** R_IIC extended configuration */
typedef struct st_iic_master_extended_cfg
{
    iic_master_timeout_mode_t    timeout_mode;    ///< Timeout Detection Time Select: Long Mode = 0 and Short Mode = 1.
    iic_master_timeout_scl_low_t timeout_scl_low; ///< Allows timeouts to occur when SCL is held low.
    iic_master_clock_settings_t  clock_settings;  ///< I2C Clock settings
    bool smbus_operation;                         ///< SMBus operation on I2C bus
} iic_master_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern i2c_master_api_t const g_i2c_master_on_iic;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_IIC_MASTER_Open(i2c_master_ctrl_t * const p_api_ctrl, i2c_master_cfg_t const * const p_cfg);

fsp_err_t R_IIC_MASTER_Read(i2c_master_ctrl_t * const p_api_ctrl,
                            uint8_t * const           p_dest,
                            uint32_t const            bytes,
                            bool const                restart);
fsp_err_t R_IIC_MASTER_Write(i2c_master_ctrl_t * const p_api_ctrl,
                             uint8_t * const           p_src,
                             uint32_t const            bytes,
                             bool const                restart);
fsp_err_t R_IIC_MASTER_Abort(i2c_master_ctrl_t * const p_api_ctrl);
fsp_err_t R_IIC_MASTER_SlaveAddressSet(i2c_master_ctrl_t * const    p_api_ctrl,
                                       uint32_t const               slave,
                                       i2c_master_addr_mode_t const addr_mode);
fsp_err_t R_IIC_MASTER_Close(i2c_master_ctrl_t * const p_api_ctrl);
fsp_err_t R_IIC_MASTER_CallbackSet(i2c_master_ctrl_t * const          p_api_ctrl,
                                   void (                           * p_callback)(i2c_master_callback_args_t *),
                                   void * const                       p_context,
                                   i2c_master_callback_args_t * const p_callback_memory);
fsp_err_t R_IIC_MASTER_StatusGet(i2c_master_ctrl_t * const p_api_ctrl, i2c_master_status_t * p_status);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_IIC_MASTER_H

/*******************************************************************************************************************//**
 * @} (end defgroup IIC_MASTER)
 **********************************************************************************************************************/
