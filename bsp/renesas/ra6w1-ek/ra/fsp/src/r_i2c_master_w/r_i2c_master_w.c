/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_i2c_master_w.h"
#if I2C_MASTER_W_CFG_DTC_ENABLE
 #include "r_dtc_w.h"
#elif I2C_MASTER_W_CFG_DMA_ENABLE
 #if BSP_FEATURE_DMAC_W_B
  #include "r_dmac_w_b.h"
 #elif BSP_FEATURE_DMAC_W
  #include "r_dmac_w.h"
 #endif
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "I2CW" in ASCII, used to determine if channel is open. */
#define I2C_MASTER_W_OPEN                         (0x49324357U)

#if (I2C_MASTER_W_CFG_DTC_ENABLE) || (I2C_MASTER_W_CFG_DMA_ENABLE)
 #define I2C_MASTER_W_DTC_RX_TRANSFER_SETTINGS    ((TRANSFER_MODE_NORMAL << TRANSFER_SETTINGS_MODE_BITS) |         \
                                                   (TRANSFER_SIZE_1_BYTE << TRANSFER_SETTINGS_SIZE_BITS) |         \
                                                   (TRANSFER_ADDR_MODE_FIXED << TRANSFER_SETTINGS_SRC_ADDR_BITS) | \
                                                   (TRANSFER_IRQ_END << TRANSFER_SETTINGS_IRQ_BITS) |              \
                                                   (TRANSFER_ADDR_MODE_INCREMENTED <<                              \
                                                    TRANSFER_SETTINGS_DEST_ADDR_BITS))
 #define I2C_MASTER_W_DTC_TX_TRANSFER_SETTINGS    ((TRANSFER_MODE_NORMAL << TRANSFER_SETTINGS_MODE_BITS) | \
                                                   (TRANSFER_SIZE_2_BYTE << TRANSFER_SETTINGS_SIZE_BITS) | \
                                                   (TRANSFER_ADDR_MODE_INCREMENTED <<                      \
                                                    TRANSFER_SETTINGS_SRC_ADDR_BITS) |                     \
                                                   (TRANSFER_IRQ_END << TRANSFER_SETTINGS_IRQ_BITS) |      \
                                                   (TRANSFER_ADDR_MODE_FIXED << TRANSFER_SETTINGS_DEST_ADDR_BITS))
#endif

#define I2C_ENABLE_LOOP_LIMIT                     (0x10)
#define I2C_ENABLE_STATUS_INTERVAL                (0x200)

#if defined(CRG_COM_RESET_CLK_COM_REG_I2C_CLK_SEL_Msk)
 #define RESET_CLK_COM_REG                        CRG_COM->RESET_CLK_COM_REG
 #define SET_CLK_COM_REG                          CRG_COM->SET_CLK_COM_REG
 #define RESET_CLK_COM_I2C_CLK_SEL                CRG_COM_RESET_CLK_COM_REG_I2C_CLK_SEL_Msk
 #define SET_CLK_COM_I2C_CLK_SEL                  CRG_COM_SET_CLK_COM_REG_I2C_CLK_SEL_Msk
 #define RESET_CLK_COM_I2C_ENABLE                 CRG_COM_RESET_CLK_COM_REG_I2C_ENABLE_Msk
 #define SET_CLK_COM_I2C_ENABLE                   CRG_COM_SET_CLK_COM_REG_I2C_ENABLE_Msk
#elif defined(CRG_PER_RESET_CLK_COM_REG_I2C_CLK_SEL_Msk)
 #define RESET_CLK_COM_REG                        CRG_PER->RESET_CLK_COM_REG
 #define SET_CLK_COM_REG                          CRG_PER->SET_CLK_COM_REG
 #define RESET_CLK_COM_I2C_CLK_SEL                CRG_PER_RESET_CLK_COM_REG_I2C_CLK_SEL_Msk
 #define SET_CLK_COM_I2C_CLK_SEL                  CRG_PER_SET_CLK_COM_REG_I2C_CLK_SEL_Msk
 #define RESET_CLK_COM_I2C_ENABLE                 CRG_PER_RESET_CLK_COM_REG_I2C_ENABLE_Msk
 #define SET_CLK_COM_I2C_ENABLE                   CRG_PER_SET_CLK_COM_REG_I2C_ENABLE_Msk
#endif

#if I2C_MASTER_W_CFG_DMA_ENABLE
 #if BSP_FEATURE_DMAC_W_B
  #define DMAC_EXTENDED_CONFIG                    dmac_w_b_extended_cfg_t
  #define DMAC_BURST_MODE_NONE                    DMAC_W_B_BURST_MODE_DISABLED
  #define DMAC_BURST_MODE_8X                      DMAC_W_B_BURST_MODE_8x
  #define DMAC_BURST_MODE_4X                      DMAC_W_B_BURST_MODE_4x
 #elif BSP_FEATURE_DMAC_W
  #define DMAC_EXTENDED_CONFIG                    dmac_extended_cfg_t
  #define DMAC_BURST_MODE_NONE                    DMAC_BURST_MODE_DISABLED
  #define DMAC_BURST_MODE_8X                      DMAC_BURST_MODE_8x
  #define DMAC_BURST_MODE_4X                      DMAC_BURST_MODE_4x
 #endif
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Hardware errors and events that can occur on the I2C */
typedef enum e_i2c_master_w_err
{
    I2C_MASTER_W_ERR_EVENT_NONE             = 0,
    I2C_MASTER_W_ERR_EVENT_TIMEOUT          = 1,
    I2C_MASTER_W_ERR_EVENT_ARBITRATION_LOSS = 2,
    I2C_MASTER_W_ERR_EVENT_START            = 4,
    I2C_MASTER_W_ERR_EVENT_STOP             = 8,
    I2C_MASTER_W_ERR_EVENT_NACK             = 16
} i2c_master_w_err_t;

/* I2C read/write enumeration */
typedef enum e_i2c_master_w_transfer_dir
{
    I2C_MASTER_W_TRANSFER_DIR_WRITE = 0x0,
    I2C_MASTER_W_TRANSFER_DIR_READ  = 0x1
} i2c_master_w_transfer_dir_t;

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * i2c_master_w_prv_ns_callback)(i2c_master_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile i2c_master_w_prv_ns_callback)(i2c_master_callback_args_t * p_args);
#endif

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/* Internal helper functions */
static fsp_err_t i2c_master_w_read_write(i2c_master_ctrl_t * const   p_api_ctrl,
                                         uint8_t * const             p_buffer,
                                         uint32_t const              bytes,
                                         i2c_master_w_transfer_dir_t direction);
static void i2c_master_w_isr_tx_handler(i2c_master_w_instance_ctrl_t * p_ctrl);
static void i2c_master_w_isr_rx_handler(i2c_master_w_instance_ctrl_t * p_ctrl, uint32_t event);
static void i2c_master_w_notify(i2c_master_w_instance_ctrl_t * const p_ctrl, i2c_master_event_t const event);

/* Functions that manipulate hardware */
static fsp_err_t i2c_master_w_open_hw_master(i2c_master_w_instance_ctrl_t * const p_ctrl);
static fsp_err_t i2c_master_w_disable(i2c_master_w_instance_ctrl_t * const p_ctrl);
static fsp_err_t i2c_master_w_mode_address_set(i2c_master_w_instance_ctrl_t * const p_ctrl);
static fsp_err_t i2c_master_w_set_target_address(i2c_master_w_instance_ctrl_t * const p_ctrl);
static void      i2c_master_w_enable_clk(uint8_t channel, bool select_divn);
static void      i2c_master_w_disable_clk(uint8_t channel);
static void      i2c_master_w_abort_transfer(i2c_master_w_instance_ctrl_t * const p_ctrl);
static void      i2c_master_w_configure_speed(i2c_master_w_instance_ctrl_t * const p_ctrl);
static void      i2c_master_w_read_configure(i2c_master_w_instance_ctrl_t * const p_ctrl);
static void      i2c_master_w_write_configure(i2c_master_w_instance_ctrl_t * const p_ctrl);

#if (I2C_MASTER_W_CFG_DTC_ENABLE) || (I2C_MASTER_W_CFG_DMA_ENABLE)
static fsp_err_t i2c_master_w_transfer_open(i2c_master_cfg_t const * const p_cfg);
static fsp_err_t i2c_master_w_transfer_configure(transfer_instance_t const * p_transfer,
                                                 i2c_master_w_transfer_dir_t direction);

#endif

/* ISR function prototypes. */
void i2c_master_w_gen_isr(void);

#if !I2C_MASTER_W_CFG_GENERIC_ONLY
void i2c_master_w_rxi_isr(void);
void i2c_master_w_txi_isr(void);
void i2c_master_w_tei_isr(void);

#endif

#if (I2C_MASTER_W_CFG_DMA_ENABLE)
void i2c_master_w_rx_dmac_callback(i2c_master_w_instance_ctrl_t * const p_ctrl);
void i2c_master_w_tx_dmac_callback(i2c_master_w_instance_ctrl_t * const p_ctrl);

#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

/* I2C_W Implementation of I2C device master interface */
i2c_master_api_t const g_i2c_master_on_i2c_w =
{
    .open            = R_I2C_MASTER_W_Open,
    .read            = R_I2C_MASTER_W_Read,
    .write           = R_I2C_MASTER_W_Write,
    .abort           = R_I2C_MASTER_W_Abort,
    .slaveAddressSet = R_I2C_MASTER_W_SlaveAddressSet,
    .close           = R_I2C_MASTER_W_Close,
    .statusGet       = R_I2C_MASTER_W_StatusGet,
    .callbackSet     = R_I2C_MASTER_W_CallbackSet
};

/*******************************************************************************************************************//**
 * @addtogroup I2C_MASTER_W
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Opens the I2C device.
 *
 * @param[in]  p_api_ctrl                     Pointer to control block.
 * @param[in]  p_cfg                          Pointer to I2C specific configuration structure.
 *
 * @retval  FSP_SUCCESS                       I2C slave device opened successfully.
 * @retval  FSP_ERR_ALREADY_OPEN              Module is already open.
 * @retval  FSP_ERR_IP_CHANNEL_NOT_PRESENT    Channel is not available on this MCU.
 * @retval  FSP_ERR_INVALID_HW_CONDITION      I2C's power domain is not enabled.
 * @retval  FSP_ERR_ASSERTION                 Parameter check failure due to one or more reasons below:
 *                                            1. p_api_ctrl or p_cfg is NULL.
 *                                            2. p_extend parameter is NULL.
 *                                            3. Invalid IRQ number assigned. Please refer to the documentation
 *                                               of I2C_MASTER_W_CFG_GENERIC_ONLY
 *                                            4. Invalid driver configuration.
 * @retval  FSP_ERR_TIMEOUT                   Device is stuck & cannot be disabled. To recover from such an
 *                                            issue you can:
 *                                              - reset the SCLK & SDA pins,
 *                                              - disable PD_COM,
 *                                              - perform a HW reset.
 * @return  See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes. This
 *          function calls: @ref transfer_api_t::open.
 **********************************************************************************************************************/
fsp_err_t R_I2C_MASTER_W_Open (i2c_master_ctrl_t * const p_api_ctrl, i2c_master_cfg_t const * const p_cfg)
{
    i2c_master_w_instance_ctrl_t * p_ctrl = (i2c_master_w_instance_ctrl_t *) p_api_ctrl;
#if I2C_MASTER_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_api_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);

    i2c_master_w_extended_cfg_t * p_extend = (i2c_master_w_extended_cfg_t *) p_cfg->p_extend;
    FSP_ASSERT(p_extend->gen_irq >= (IRQn_Type) 0);
 #if !I2C_MASTER_W_CFG_GENERIC_ONLY
    FSP_ASSERT(p_cfg->rxi_irq >= (IRQn_Type) 0);
    FSP_ASSERT(p_cfg->txi_irq >= (IRQn_Type) 0);
    FSP_ASSERT(p_cfg->tei_irq >= (IRQn_Type) 0);
 #endif
    FSP_ERROR_RETURN(I2C_MASTER_W_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
    FSP_ERROR_RETURN(BSP_FEATURE_I2C_VALID_CHANNEL_MASK & (1 << (p_cfg->channel + I2C_MASTER_W_CHANNEL_OFFSET)),
                     FSP_ERR_IP_CHANNEL_NOT_PRESENT);
 #if BSP_FEATURE_I2C_HAS_SEPARATE_PD
    FSP_ERROR_RETURN(bsp_pd_is_up_check(BSP_FEATURE_I2C_HAS_SEPARATE_PD), FSP_ERR_INVALID_HW_CONDITION);
 #endif
#endif

#if I2C_MASTER_W_CFG_GENERIC_ONLY
    FSP_ASSERT(I2C_MASTER_W_CFG_DTC_ENABLE == 0);
#endif

    fsp_err_t err = FSP_SUCCESS;

    p_ctrl->p_reg = (I2C_Type *) ((uint32_t) I2C + (p_cfg->channel * ((uint32_t) I2C2 - (uint32_t) I2C)));

    /* Record the pointer to the configuration structure for later use */
    p_ctrl->p_cfg             = p_cfg;
    p_ctrl->slave             = p_cfg->slave;
    p_ctrl->addr_mode         = p_cfg->addr_mode;
    p_ctrl->p_callback        = p_cfg->p_callback;
    p_ctrl->p_context         = p_cfg->p_context;
    p_ctrl->p_callback_memory = NULL;

    /* Open the hardware in master mode. Performs I2C initialization. */
    err = i2c_master_w_open_hw_master(p_ctrl);

#if (I2C_MASTER_W_CFG_DTC_ENABLE) || (I2C_MASTER_W_CFG_DMA_ENABLE)

    /* Open the I2C transfer interface if available. */
    err = i2c_master_w_transfer_open(p_cfg);
    if (FSP_SUCCESS != err)
    {
        return err;
    }
#endif

    p_ctrl->p_buff    = NULL;
    p_ctrl->total     = 0U;
    p_ctrl->nof_bytes = 0U;
    p_ctrl->loaded    = 0U;
    p_ctrl->read      = false;
    p_ctrl->restart   = false;
    p_ctrl->restarted = false;
    p_ctrl->open      = I2C_MASTER_W_OPEN;

    return err;
}

/*******************************************************************************************************************//**
 * Performs a read from the I2C device.
 * The caller will be notified when the operation has completed (successfully) by an
 * I2C_MASTER_EVENT_RX_COMPLETE in the callback.
 *
 * @param[in]   p_api_ctrl          Pointer to control block.
 * @param[out]  p_dest              Pointer to the destination buffer.
 * @param[in]   bytes               Number of bytes to be read.
 * @param[in]   restart             Restart information about this transfer.
 *
 * @retval  FSP_SUCCESS             Function executed without issue.
 * @retval  FSP_ERR_ASSERTION       p_api_ctrl, p_dest or bytes is NULL.
 * @retval  FSP_ERR_INVALID_SIZE    Provided number of bytes more than the configured TX buffer size or more than
 *                                  UINT16_MAX(= 65535) while DTC/DMAC is used for data transfer.
 * @retval  FSP_ERR_NOT_OPEN        Handle is not initialized.  Call R_I2C_MASTER_W_Open to initialize the control block.
 * @return  See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes. This
 *          function calls: @ref transfer_api_t::reset.
 **********************************************************************************************************************/
fsp_err_t R_I2C_MASTER_W_Read (i2c_master_ctrl_t * const p_api_ctrl,
                               uint8_t * const           p_dest,
                               uint32_t const            bytes,
                               bool const                restart)
{
#if I2C_MASTER_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_api_ctrl);
    FSP_ASSERT(0U != bytes);
#endif
    fsp_err_t err = FSP_SUCCESS;

    /* Record the restart information about this transfer.
     * This is done here to keep the parameter (argument) list of i2c_master_w_read_write to 4. */
    ((i2c_master_w_instance_ctrl_t *) p_api_ctrl)->restart = restart;

    /* Call the common helper function to perform I2C Read operation.*/
    err = i2c_master_w_read_write(p_api_ctrl, p_dest, bytes, I2C_MASTER_W_TRANSFER_DIR_READ);

    return err;
}

/*******************************************************************************************************************//**
 * Performs a write to the I2C device.
 * The caller will be notified when the operation has completed (successfully) by an
 * I2C_MASTER_EVENT_TX_COMPLETE in the callback.
 *
 * @param[in]  p_api_ctrl         Pointer to control block.
 * @param[in]  p_src              Pointer to the source buffer.
 * @param[in]  bytes              Number of bytes to be write.
 * @param[in]  restart            Restart information about this transfer.
 *
 * @retval  FSP_SUCCESS           Function executed without issue.
 * @retval  FSP_ERR_ASSERTION     p_api_ctrl or p_src is NULL.
 * @retval  FSP_ERR_INVALID_SIZE  Provided number of bytes more than the configured TX buffer size or more than
 *                                UINT16_MAX(= 65535) while DTC/DMAC is used for data transfer.
 * @retval  FSP_ERR_NOT_OPEN      Handle is not initialized.  Call R_I2C_MASTER_W_Open to initialize the control block.
 * @return  See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes. This
 *          function calls: @ref transfer_api_t::reset.
 **********************************************************************************************************************/
fsp_err_t R_I2C_MASTER_W_Write (i2c_master_ctrl_t * const p_api_ctrl,
                                uint8_t * const           p_src,
                                uint32_t const            bytes,
                                bool const                restart)
{
#if I2C_MASTER_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_api_ctrl);
#endif
    fsp_err_t err = FSP_SUCCESS;

    /* Record the restart information about this transfer.
     * This is done here to keep the parameter (argument) list of i2c_master_w_read_write to 4. */
    ((i2c_master_w_instance_ctrl_t *) p_api_ctrl)->restart = restart;

    /* Call the common helper function to perform I2C Write operation.*/
    err = i2c_master_w_read_write(p_api_ctrl, p_src, bytes, I2C_MASTER_W_TRANSFER_DIR_WRITE);

    return err;
}

/*******************************************************************************************************************//**
 * Safely aborts any in-progress transfer and forces the I2C peripheral into ready state.
 *
 * @param[in]  p_api_ctrl           Pointer to control block.
 *
 * @retval  FSP_SUCCESS             Channel was reset successfully.
 * @retval  FSP_ERR_ASSERTION       p_api_ctrl is NULL.
 * @retval  FSP_ERR_NOT_OPEN        Handle is not initialized.  Call R_I2C_MASTER_W_Open to initialize the control block.
 * @retval  FSP_ERR_TIMEOUT         Device is stuck & cannot be disabled. To recover from such an issue you can:
 *                                  - reset the SCLK & SDA pins,
 *                                  - disable PD_COM,
 *                                  - perform a HW reset.
 *
 * @note A callback will not be invoked in case an in-progress transfer gets aborted by calling this API.
 * @return  See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes. This
 *          function calls: @ref transfer_api_t::open.
 **********************************************************************************************************************/
fsp_err_t R_I2C_MASTER_W_Abort (i2c_master_ctrl_t * const p_api_ctrl)
{
    i2c_master_w_instance_ctrl_t * p_ctrl = (i2c_master_w_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t err = FSP_SUCCESS;

#if I2C_MASTER_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(I2C_MASTER_W_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Disable interrupts immediately. */
    p_ctrl->p_reg->I2C_INTR_MASK_REG = 0;
#if BSP_FEATURE_I2C_HAS_DEDICATED_IRQS
    p_ctrl->p_reg->I2C_MASK_REG = 0;
#endif

    /* This helper function would do a full I2C reset
     * followed by re-initializing the required peripheral registers. */
    err = i2c_master_w_open_hw_master(p_ctrl);

    /* Update the transfer descriptor to show no longer in-progress and an error */
    p_ctrl->nof_bytes = p_ctrl->total;

    /* Update the transfer descriptor to make sure interrupts no longer process */
    p_ctrl->loaded    = p_ctrl->total;
    p_ctrl->restart   = false;
    p_ctrl->restarted = false;

    return err;
}

/*******************************************************************************************************************//**
 * Sets address and addressing mode of the slave device.
 * This function is used to set the device address and addressing mode of the slave
 * without reconfiguring the entire bus.
 *
 * @param[in]  p_api_ctrl            Pointer to control block.
 * @param[in]  slave                 Denotes the slave device.
 * @param[in]  addr_mode             Addressing mode (7 bit or 10 bit).
 *
 * @retval  FSP_SUCCESS             Address of the slave is set correctly.
 * @retval  FSP_ERR_ASSERTION       Pointer to control structure is NULL.
 * @retval  FSP_ERR_IN_USE          Another transfer was in-progress.
 * @retval  FSP_ERR_NOT_OPEN        Handle is not initialized.  Call R_I2C_MASTER_W_Open to initialize the control
 *                                  block.
 * @retval  FSP_ERR_TIMEOUT         Device is stuck & cannot be disabled. To recover from such an issue you can:
 *                                  - reset the SCLK & SDA pins,
 *                                  - disable PD_COM,
 *                                  - perform a HW reset.
 **********************************************************************************************************************/
fsp_err_t R_I2C_MASTER_W_SlaveAddressSet (i2c_master_ctrl_t * const    p_api_ctrl,
                                          uint32_t const               slave,
                                          i2c_master_addr_mode_t const addr_mode)
{
    i2c_master_w_instance_ctrl_t * p_ctrl = (i2c_master_w_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t err = FSP_SUCCESS;

#if I2C_MASTER_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(I2C_MASTER_W_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Fail if there is already a transfer in progress. */
    FSP_ERROR_RETURN(((p_ctrl->loaded == p_ctrl->total) && (false == p_ctrl->restart)), FSP_ERR_IN_USE);
#endif

    /* Sets the address of the slave device. */
    p_ctrl->slave = slave;
    err           = i2c_master_w_set_target_address(p_ctrl);

    /* Sets the mode of addressing. */
    p_ctrl->addr_mode = addr_mode;

    /* Sets target addressing mode. */
    p_ctrl->p_reg->I2C_CON_REG_b.I2C_10BITADDR_MASTER =
        ((I2C_MASTER_ADDR_MODE_10BIT == p_ctrl->p_cfg->addr_mode) ? 1 : 0);

    return err;
}

/*******************************************************************************************************************//**
 * Updates the user callback and has option of providing memory for callback structure.
 * Implements i2c_master_api_t::callbackSet
 *
 * @param[in]  p_api_ctrl                 Pointer to control block.
 * @param[in]  p_callback                 Pointer to the callback.
 * @param[in]  p_context                  Pointer to context.
 * @param[in]  p_callback_memory          Pointer to the callback memory.
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t R_I2C_MASTER_W_CallbackSet (i2c_master_ctrl_t * const          p_api_ctrl,
                                      void (                           * p_callback)(i2c_master_callback_args_t *),
                                      void * const                       p_context,
                                      i2c_master_callback_args_t * const p_callback_memory)
{
    i2c_master_w_instance_ctrl_t * p_ctrl = (i2c_master_w_instance_ctrl_t *) p_api_ctrl;

#if I2C_MASTER_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(I2C_MASTER_W_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback. */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if I2C_MASTER_W_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure. */
    i2c_master_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                             CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context. */
#if BSP_TZ_SECURE_BUILD
    p_ctrl->p_callback = callback_is_secure ? p_callback :
                         (void (*)(i2c_master_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_ctrl->p_callback = p_callback;
#endif
    p_ctrl->p_context         = p_context;
    p_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Provides driver status.
 *
 * @param[in]   p_api_ctrl                   Pointer to control block.
 * @param[out]  p_status                     Pointer to the I2C status.
 *
 * @retval     FSP_SUCCESS                   Status stored in p_status.
 * @retval     FSP_ERR_ASSERTION             NULL pointer.
 **********************************************************************************************************************/
fsp_err_t R_I2C_MASTER_W_StatusGet (i2c_master_ctrl_t * const p_api_ctrl, i2c_master_status_t * p_status)
{
    i2c_master_w_instance_ctrl_t * p_ctrl = (i2c_master_w_instance_ctrl_t *) p_api_ctrl;

#if I2C_MASTER_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_status);
#endif

    p_status->open = (I2C_MASTER_W_OPEN == p_ctrl->open);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Closes the I2C device. May power down I2C peripheral.
 * This function will safely terminate any in-progress I2C transfers.
 *
 * @param[in]  p_api_ctrl       Pointer to control block.
 *
 * @retval  FSP_SUCCESS         Device closed without issue.
 * @retval  FSP_ERR_ASSERTION   p_api_ctrl is NULL.
 * @retval  FSP_ERR_NOT_OPEN    Handle is not initialized.  Call R_I2C_MASTER_W_Open to initialize the control block.
 * @retval  FSP_ERR_TIMEOUT     Device is stuck & cannot be disabled. To recover from such an issue you can:
 *                                  - reset the SCLK & SDA pins,
 *                                  - disable PD_COM,
 *                                  - perform a HW reset.
 *
 * @note A callback will not be invoked in case an in-progress transfer gets aborted by calling this API.
 **********************************************************************************************************************/
fsp_err_t R_I2C_MASTER_W_Close (i2c_master_ctrl_t * const p_api_ctrl)
{
    i2c_master_w_instance_ctrl_t * p_ctrl = (i2c_master_w_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t err = FSP_SUCCESS;

#if I2C_MASTER_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(I2C_MASTER_W_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Update the transfer descriptor to show no longer in-progress and an error. */
    p_ctrl->nof_bytes = 0U;

    /* Update the transfer descriptor to make sure interrupts no longer process. */
    p_ctrl->loaded    = p_ctrl->total;
    p_ctrl->restart   = false;
    p_ctrl->restarted = false;

    FSP_CRITICAL_SECTION_DEFINE;

    FSP_CRITICAL_SECTION_ENTER;

    /* Abort any ongoing transaction. */
    i2c_master_w_abort_transfer(p_ctrl);

    /* Disable events for both GEN & dedicated TXE, RX & TXR interrupts. */
    p_ctrl->p_reg->I2C_INTR_MASK_REG = 0;
#if BSP_FEATURE_I2C_HAS_DEDICATED_IRQS
    p_ctrl->p_reg->I2C_MASK_REG = 0;
#endif

    /* Disable I2C controller. */
    err = i2c_master_w_disable(p_ctrl);

    /* Disable I2C clock. */
    i2c_master_w_disable_clk(p_ctrl->p_cfg->channel);

    /* The device is now considered closed. */
    p_ctrl->open = 0U;

#if (I2C_MASTER_W_CFG_DTC_ENABLE) || (I2C_MASTER_W_CFG_DMA_ENABLE)

    /* Close the handles for the transfer interfaces. */
    if (NULL != p_ctrl->p_cfg->p_transfer_rx)
    {
        p_ctrl->p_cfg->p_transfer_rx->p_api->close(p_ctrl->p_cfg->p_transfer_rx->p_ctrl);
 #if I2C_MASTER_W_CFG_DTC_ENABLE
        R_BSP_IrqClearPending(p_ctrl->p_cfg->rxi_irq);
        R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);
 #endif
    }

    if (NULL != p_ctrl->p_cfg->p_transfer_tx)
    {
        p_ctrl->p_cfg->p_transfer_tx->p_api->close(p_ctrl->p_cfg->p_transfer_tx->p_ctrl);
 #if I2C_MASTER_W_CFG_DTC_ENABLE
        R_BSP_IrqClearPending(p_ctrl->p_cfg->txi_irq);
        R_BSP_IrqDisable(p_ctrl->p_cfg->txi_irq);
 #endif
    }
#endif

    i2c_master_w_extended_cfg_t * p_extend = (i2c_master_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    R_BSP_IrqDisable(p_extend->gen_irq);

    FSP_CRITICAL_SECTION_EXIT;

    return err;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup I2C_MASTER_W)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Helper function for handling I2C Read or Write.
 *
 * @param[in]  p_api_ctrl         Pointer to control block.
 * @param[in]  p_buffer           Pointer to the buffer to store read/write data.
 * @param[in]  bytes              Number of bytes to be read/written.
 * @param[in]  direction          I2C direction Read or Write.
 *
 * @retval  FSP_SUCCESS           Function executed successfully.
 * @retval  FSP_ERR_ASSERTION     p_api_ctrl or p_buffer is NULL.
 * @retval  FSP_ERR_INVALID_SIZE  Provided number of bytes more than the configured TX buffer size or more than
 *                                UINT16_MAX(= 65535) while DTC/DMAC is used for data transfer.
 * @retval  FSP_ERR_NOT_OPEN      Handle is not initialized. Call R_I2C_MASTER_W_Open to initialize the control block.
 **********************************************************************************************************************/
static fsp_err_t i2c_master_w_read_write (i2c_master_ctrl_t * const   p_api_ctrl,
                                          uint8_t * const             p_buffer,
                                          uint32_t const              bytes,
                                          i2c_master_w_transfer_dir_t direction)
{
    i2c_master_w_instance_ctrl_t * p_ctrl = (i2c_master_w_instance_ctrl_t *) p_api_ctrl;

#if I2C_MASTER_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_buffer);
    FSP_ERROR_RETURN((I2C_MASTER_W_OPEN == p_ctrl->open), FSP_ERR_NOT_OPEN);
    FSP_ASSERT(((i2c_master_w_instance_ctrl_t *) p_api_ctrl)->p_callback != NULL);
 #if (I2C_MASTER_W_CFG_DTC_ENABLE) || (I2C_MASTER_W_CFG_DMA_ENABLE)
    FSP_ERROR_RETURN((bytes <= UINT16_MAX), FSP_ERR_INVALID_SIZE);
    FSP_ERROR_RETURN((bytes <= I2C_MASTER_W_CFG_TRANSFER_API_TX_BUFFER_SIZE), FSP_ERR_INVALID_SIZE);
 #endif
#endif

    p_ctrl->p_buff = p_buffer;
    p_ctrl->total  = bytes;

    p_ctrl->read = (bool) direction;

    if (I2C_MASTER_W_TRANSFER_DIR_WRITE == p_ctrl->read)
    {
        i2c_master_w_write_configure(p_ctrl);
    }
    else
    {
        i2c_master_w_read_configure(p_ctrl);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Single point for managing the logic around notifying a transfer has finished.
 *
 * @param[in]       p_ctrl      Pointer to I2C specific control structure.
 * @param[in]       event       The event code to pass to the callback.
 **********************************************************************************************************************/
static void i2c_master_w_notify (i2c_master_w_instance_ctrl_t * const p_ctrl, i2c_master_event_t const event)
{
    i2c_master_callback_args_t args;

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    i2c_master_callback_args_t * p_args = p_ctrl->p_callback_memory;
    if (NULL == p_args)
    {
        /* Store on stack */
        p_args = &args;
    }
    else
    {
        /* Save current arguments on the stack in case this is a nested interrupt. */
        args = *p_args;
    }

    p_args->p_context = p_ctrl->p_context;
    p_args->event     = event;

#if (I2C_MASTER_W_CFG_DTC_ENABLE) || (I2C_MASTER_W_CFG_DMA_ENABLE)

    /* Stop any DTC assisted transfer for TX. */
    const transfer_instance_t * p_transfer_tx = p_ctrl->p_cfg->p_transfer_tx;
    if (!p_ctrl->read)
    {
        if (NULL != p_transfer_tx)
        {
            p_transfer_tx->p_api->disable(p_transfer_tx->p_ctrl);
        }
    }
    else
    {
        /* Stop any DTC assisted transfer for RX. */
        const transfer_instance_t * p_transfer_rx = p_ctrl->p_cfg->p_transfer_rx;
        if (NULL != p_transfer_rx)
        {
            p_transfer_rx->p_api->disable(p_transfer_rx->p_ctrl);
        }

        if (NULL != p_transfer_tx)
        {
            p_transfer_tx->p_api->disable(p_transfer_tx->p_ctrl);
        }
    }
#endif

    /* Disable all events for the Generic interrupt. */
    p_ctrl->p_reg->I2C_INTR_MASK_REG = 0;

    /* Disable all events for the dedicated interrupts. */
#if BSP_FEATURE_I2C_HAS_DEDICATED_IRQS
    p_ctrl->p_reg->I2C_MASK_REG = 0;
#endif
#if !I2C_MASTER_W_CFG_GENERIC_ONLY
    R_BSP_IrqClearPending(p_ctrl->p_cfg->txi_irq);
#endif

    /* Now do the callback here. */
#if BSP_TZ_SECURE_BUILD

    /* p_callback can point to a secure function or a non-secure function. */
    if (!cmse_is_nsfptr(p_ctrl->p_callback))
    {
        /* If p_callback is secure, then the project does not need to change security state. */
        p_ctrl->p_callback(p_args);
    }
    else
    {
        /* If p_callback is Non-secure, then the project must change to Non-secure state in order
         * to call the callback. */
        i2c_master_w_prv_ns_callback p_callback = (i2c_master_w_prv_ns_callback) (p_ctrl->p_callback);
        p_callback(p_args);
    }

#else

    /* If the project is not Trustzone Secure, then it will never need to change security state in
     * order to call the callback. */
    p_ctrl->p_callback(p_args);
#endif

    if (NULL != p_ctrl->p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_ctrl->p_callback_memory = args;
    }
}

/*******************************************************************************************************************//**
 * Performs the hardware initialization sequence when operating as a master.
 *
 * @param[in]  p_ctrl                Pointer to I2C specific control structure.
 *
 * @retval  FSP_SUCCESS           Function executed successfully.
 **********************************************************************************************************************/
static fsp_err_t i2c_master_w_open_hw_master (i2c_master_w_instance_ctrl_t * const p_ctrl)
{
    i2c_master_w_extended_cfg_t * p_extend = (i2c_master_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    fsp_err_t err = FSP_SUCCESS;

    /* Enable I2C clock. */
    i2c_master_w_enable_clk(p_ctrl->p_cfg->channel, p_extend->select_divn);

    /* Abort any ongoing transaction. */
    i2c_master_w_abort_transfer(p_ctrl);

    /* Disable I2C controller. */
    err = i2c_master_w_disable(p_ctrl);

    /* Disable events for both GEN & dedicated TXE, RX & TXR interrupts. */
    p_ctrl->p_reg->I2C_INTR_MASK_REG = 0;
#if BSP_FEATURE_I2C_HAS_DEDICATED_IRQS
    p_ctrl->p_reg->I2C_MASK_REG = 0;
#endif

    /* Configure master clock settings & communication speed. */
    i2c_master_w_configure_speed(p_ctrl);

    /* Set mode, addressing mode & target's address. */
    err = i2c_master_w_mode_address_set(p_ctrl);

    /* Enable the I2C Controller. */
    p_ctrl->p_reg->I2C_ENABLE_REG_b.I2C_EN = 1;

    /* Set valid interrupt contexts and user provided priority. Enable the interrupts at the NVIC.  */
    R_BSP_IrqCfgEnable(p_extend->gen_irq, p_extend->gen_ipl, p_ctrl);
#if I2C_MASTER_W_CFG_DTC_ENABLE
    if (NULL != p_ctrl->p_cfg->p_transfer_tx)
    {
        /* If DTC is used, configure TX FIFO threshold to "completely empty". */
        p_ctrl->p_reg->I2C_TX_TL_REG = 0;
    }
    else
#endif
    {
        /* Configure TX FIFO threshold to at least 1 empty entry. */
        p_ctrl->p_reg->I2C_TX_TL_REG = I2C_MASTER_W_FIFO_DEPTH - 1;
    }

    /* Configure RX FIFO threshold to at least one entry. */
    p_ctrl->p_reg->I2C_RX_TL_REG = 0;

#if !I2C_MASTER_W_CFG_GENERIC_ONLY
    R_BSP_IrqCfgEnable(p_ctrl->p_cfg->rxi_irq, p_ctrl->p_cfg->ipl, p_ctrl);
    R_BSP_IrqCfgEnable(p_ctrl->p_cfg->txi_irq, p_ctrl->p_cfg->ipl, p_ctrl);
    R_BSP_IrqCfgEnable(p_ctrl->p_cfg->tei_irq, p_ctrl->p_cfg->ipl, p_ctrl);
#endif

    return err;
}

/*******************************************************************************************************************//**
 * Disables I2C.
 *
 * @param[in]  p_ctrl             Pointer to I2C specific control structure.
 *
 * @retval  FSP_SUCCESS           Function executed successfully.
 * @retval  FSP_ERR_TIMEOUT       Timeout error.
 **********************************************************************************************************************/
static fsp_err_t i2c_master_w_disable (i2c_master_w_instance_ctrl_t * const p_ctrl)
{
    /* Disable I2C controller */
    p_ctrl->p_reg->I2C_ENABLE_REG_b.I2C_EN = 0;

    /* wait until controller is disabled. */
    uint32_t times = 0;
    while (1 == p_ctrl->p_reg->I2C_ENABLE_STATUS_REG_b.IC_EN)
    {
        /* We shouldn't get stuck here, the I2C block should eventually be disabled. */
        FSP_ERROR_RETURN((times++ < I2C_ENABLE_LOOP_LIMIT), FSP_ERR_TIMEOUT);
        R_BSP_SoftwareDelay(I2C_ENABLE_STATUS_INTERVAL, BSP_DELAY_UNITS_MICROSECONDS);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets I2C master mode, addressing mode & target's address.
 *
 * @param[in]  p_ctrl                Pointer to I2C specific control structure.
 *
 * @retval  FSP_SUCCESS              Function executed successfully.
 **********************************************************************************************************************/
static fsp_err_t i2c_master_w_mode_address_set (i2c_master_w_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Set master mode. */
    uint32_t tmp = p_ctrl->p_reg->I2C_CON_REG;
    FSP_REG_VAR_FIELD_SET(I2C, I2C_CON_REG, I2C_MASTER_MODE, tmp, 1);
    FSP_REG_VAR_FIELD_SET(I2C, I2C_CON_REG, I2C_SLAVE_DISABLE, tmp, 1);
    p_ctrl->p_reg->I2C_CON_REG = tmp;

    /* Set the Master HS Code ID. */
    if (0 == p_ctrl->p_cfg->channel)
    {
        p_ctrl->p_reg->I2C_HS_MADDR_REG_b.I2C_IC_HS_MAR = I2C_MASTER_W_I2C1_MADDR;
    }
    else if (1 == p_ctrl->p_cfg->channel)
    {
        p_ctrl->p_reg->I2C_HS_MADDR_REG_b.I2C_IC_HS_MAR = I2C_MASTER_W_I2C2_MADDR;
    }
    else
    {
        p_ctrl->p_reg->I2C_HS_MADDR_REG_b.I2C_IC_HS_MAR = I2C_MASTER_W_I2C3_MADDR;
    }

    /* Set target's addressing mode. */
    p_ctrl->p_reg->I2C_CON_REG_b.I2C_10BITADDR_MASTER =
        ((I2C_MASTER_ADDR_MODE_10BIT == p_ctrl->p_cfg->addr_mode) ? 1 : 0);

    /* Set target's address. */
    err = i2c_master_w_set_target_address(p_ctrl);

    FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->I2C_STATUS_REG_b.MST_ACTIVITY, 0);

    return err;
}

/*******************************************************************************************************************//**
 * Sets target address.
 *
 * @param[in]  p_ctrl                Pointer to I2C specific control structure.
 *
 * @retval  FSP_SUCCESS              Function executed successfully.
 **********************************************************************************************************************/
static fsp_err_t i2c_master_w_set_target_address (i2c_master_w_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Check if I2C is enabled. */
    if (p_ctrl->p_reg->I2C_ENABLE_STATUS_REG_b.IC_EN)
    {
        /* Check if master is busy. */
        FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->I2C_STATUS_REG_b.MST_ACTIVITY, 0);

        err = i2c_master_w_disable(p_ctrl);

        p_ctrl->p_reg->I2C_TAR_REG_b.IC_TAR = p_ctrl->slave & I2C_I2C_TAR_REG_IC_TAR_Msk;

        /* Enable I2C. */
        p_ctrl->p_reg->I2C_ENABLE_REG_b.I2C_EN = 1;
    }
    else
    {
        p_ctrl->p_reg->I2C_TAR_REG_b.IC_TAR = p_ctrl->slave & I2C_I2C_TAR_REG_IC_TAR_Msk;
    }

    return err;
}

/*******************************************************************************************************************//**
 * Enables I2C clock.
 *
 * @param [in] channel        I2C selected channel.
 * @param [in] select_divn    I2C selected DIVN.
 **********************************************************************************************************************/
static void i2c_master_w_enable_clk (uint8_t channel, bool select_divn)
{
    if (select_divn)
    {
        RESET_CLK_COM_REG = RESET_CLK_COM_I2C_CLK_SEL << (channel * 2);
        SET_CLK_COM_REG   = SET_CLK_COM_I2C_ENABLE << (channel * 2);
    }
    else
    {
        SET_CLK_COM_REG = (SET_CLK_COM_I2C_CLK_SEL << (channel * 2)) |
                          (SET_CLK_COM_I2C_ENABLE << (channel * 2));
    }
}

/*******************************************************************************************************************//**
 * Disables I2C clock.
 *
 * @param [in] channel        I2C selected channel.
 **********************************************************************************************************************/
static void i2c_master_w_disable_clk (uint8_t channel)
{
    RESET_CLK_COM_REG = RESET_CLK_COM_I2C_ENABLE << (channel * 2);
}

/*******************************************************************************************************************//**
 * Abort I2C transfer.
 *
 * @param[in]  p_ctrl                Pointer to I2C specific control structure.
 **********************************************************************************************************************/
static void i2c_master_w_abort_transfer (i2c_master_w_instance_ctrl_t * const p_ctrl)
{
    if (p_ctrl->p_reg->I2C_CON_REG_b.I2C_MASTER_MODE)
    {
        p_ctrl->p_reg->I2C_ENABLE_REG_b.I2C_ABORT = 1;
    }
}

/*******************************************************************************************************************//**
 * Configures I2C master clock settings & transaction speed.
 *
 * @param[in]  p_ctrl                Pointer to I2C specific control structure.
 **********************************************************************************************************************/
static void i2c_master_w_configure_speed (i2c_master_w_instance_ctrl_t * const p_ctrl)
{
    i2c_master_w_extended_cfg_t * p_extend = (i2c_master_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    switch (p_ctrl->p_cfg->rate)
    {
        case I2C_MASTER_RATE_HIGHSPEED:
        {
            p_ctrl->p_reg->I2C_HS_SCL_HCNT_REG     = p_extend->clock_settings.scl_hcnt;
            p_ctrl->p_reg->I2C_HS_SCL_LCNT_REG     = p_extend->clock_settings.scl_lcnt;
            p_ctrl->p_reg->I2C_CON_REG_b.I2C_SPEED = 3;
            break;
        }

        case I2C_MASTER_RATE_FASTPLUS:
        case I2C_MASTER_RATE_FAST:
        {
            p_ctrl->p_reg->I2C_FS_SCL_HCNT_REG     = p_extend->clock_settings.scl_hcnt;
            p_ctrl->p_reg->I2C_FS_SCL_LCNT_REG     = p_extend->clock_settings.scl_lcnt;
            p_ctrl->p_reg->I2C_CON_REG_b.I2C_SPEED = 2;
            break;
        }

        case I2C_MASTER_RATE_STANDARD:
        default:
        {
            p_ctrl->p_reg->I2C_SS_SCL_HCNT_REG     = p_extend->clock_settings.scl_hcnt;
            p_ctrl->p_reg->I2C_SS_SCL_LCNT_REG     = p_extend->clock_settings.scl_lcnt;
            p_ctrl->p_reg->I2C_CON_REG_b.I2C_SPEED = 1;
            break;
        }
    }
}

/*******************************************************************************************************************//**
 * Activates the required interrupt sources for read.
 *
 * It initiates an I2C read transmission.
 *
 * @param [in] p_ctrl    Pointer to I2C specific control structure.
 **********************************************************************************************************************/
static void i2c_master_w_read_configure (i2c_master_w_instance_ctrl_t * const p_ctrl)
{
    uint16_t mask = I2C_MASTER_W_INT_TX_ABORT;

    /* Clear TX ABORT interrupt status. */
    p_ctrl->p_reg->I2C_CLR_TX_ABRT_REG;

    if (0 == p_ctrl->restart)
    {
        mask |= I2C_MASTER_W_INT_STOP_DETECTED;

        /* Clear STOP DETECTED interrupt status. */
        p_ctrl->p_reg->I2C_CLR_STOP_DET_REG;
    }

    /* Initialize fields used during transfer. */
    p_ctrl->loaded    = 0U;
    p_ctrl->nof_bytes = 0U;

#if (I2C_MASTER_W_CFG_DTC_ENABLE) || (I2C_MASTER_W_CFG_DMA_ENABLE)
    transfer_instance_t * p_transfer_rx = (transfer_instance_t *) p_ctrl->p_cfg->p_transfer_rx;
    transfer_instance_t * p_transfer_tx = (transfer_instance_t *) p_ctrl->p_cfg->p_transfer_tx;

    /* Enable RX transfer support if possible. */
    if ((NULL != p_transfer_rx) && (p_ctrl->total > 0U))
    {
        uint32_t volatile const * p_i2c_master_w_rx_src_buf = &(p_ctrl->p_reg->I2C_DATA_CMD_REG);

 #if I2C_MASTER_W_CFG_DTC_ENABLE
        p_transfer_rx->p_api->reset(p_transfer_rx->p_ctrl, (uint8_t *) (p_i2c_master_w_rx_src_buf),
                                    (void *) (p_ctrl->p_buff), (uint16_t) (p_ctrl->total));
 #else
  #if !I2C_MASTER_W_CFG_GENERIC_ONLY

        /* RX operation will be handled by DMA. */
        R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);
  #endif

        /* Make sure I2C DMA is off so it's not unexpectedly triggered when channels are enabled. */
        p_ctrl->p_reg->I2C_DMA_CR_REG = 0;

        /* Configure RX DMA Channel and RX FIFO threshold level for I2C Master. */
        DMAC_EXTENDED_CONFIG        * p_dmac_extend = (DMAC_EXTENDED_CONFIG *) p_transfer_rx->p_cfg->p_extend;
        i2c_master_w_extended_cfg_t * p_extend      = (i2c_master_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

        if ((0 == (p_ctrl->total % 8)) && p_extend->enable_dma_bursts_rx)
        {
            p_dmac_extend->burst_mode       = DMAC_BURST_MODE_8X;
            p_ctrl->p_reg->I2C_DMA_RDLR_REG = 7;
        }
        else if ((0 == (p_ctrl->total % 4)) && p_extend->enable_dma_bursts_rx)
        {
            p_dmac_extend->burst_mode       = DMAC_BURST_MODE_4X;
            p_ctrl->p_reg->I2C_DMA_RDLR_REG = 3;
        }
        else
        {
            p_dmac_extend->burst_mode       = DMAC_BURST_MODE_NONE;
            p_ctrl->p_reg->I2C_DMA_RDLR_REG = 0;
        }

        p_transfer_rx->p_cfg->p_info->p_src  = (uint8_t *) p_i2c_master_w_rx_src_buf;
        p_transfer_rx->p_cfg->p_info->p_dest = (uint8_t *) p_ctrl->p_buff;
        p_transfer_rx->p_cfg->p_info->length = (uint16_t) p_ctrl->total;

        p_transfer_rx->p_api->reconfigure(p_transfer_rx->p_ctrl, p_transfer_rx->p_cfg->p_info);
        p_transfer_rx->p_api->enable(p_transfer_rx->p_ctrl);

        p_ctrl->p_reg->I2C_DMA_CR_REG_b.RDMAE = 1;
 #endif
        p_ctrl->nof_bytes = p_ctrl->total;
    }

 #if I2C_MASTER_W_CFG_GENERIC_ONLY
    else
    {
        mask |= I2C_MASTER_W_INT_RX_FULL;
    }
 #endif

    /* Enable TX transfer support if possible for the enqueueing of the READ commands. */
    if ((NULL != p_transfer_tx) && (p_ctrl->read) && (p_ctrl->total > 0U))
    {
        bool add_stop;
        bool add_restart;

        /* Pack commands with READ request, STOP/RESTART information. */
        while (p_ctrl->loaded < p_ctrl->total)
        {
            add_stop = (p_ctrl->loaded + 1 == p_ctrl->total) && (p_ctrl->restart == 0);
            add_restart = ((p_ctrl->loaded == 0) && (p_ctrl->restarted == 1));

            p_ctrl->p_transfer_api_tx_buff[p_ctrl->loaded] = I2C_I2C_DATA_CMD_REG_I2C_CMD_Msk |
                                                             (add_stop ? I2C_I2C_DATA_CMD_REG_I2C_STOP_Msk : 0) |
                                                             (add_restart ? I2C_I2C_DATA_CMD_REG_I2C_RESTART_Msk : 0);

            p_ctrl->loaded++;
        }

        uint32_t volatile const * p_i2c_master_w_tx_dest_buf = &(p_ctrl->p_reg->I2C_DATA_CMD_REG);

 #if I2C_MASTER_W_CFG_DTC_ENABLE
        p_transfer_tx->p_api->reset(p_transfer_tx->p_ctrl, (void *) (p_ctrl->p_transfer_api_tx_buff),
                                    (uint16_t *) (p_i2c_master_w_tx_dest_buf), (uint16_t) (p_ctrl->total));
 #else
  #if !I2C_MASTER_W_CFG_GENERIC_ONLY

        /* TX operation will be handled by DMA. */
        R_BSP_IrqDisable(p_ctrl->p_cfg->txi_irq);
  #endif

        /* Configure TX DMA Channel and TX FIFO threshold level for I2C. */
        DMAC_EXTENDED_CONFIG        * p_dmac_extend = (DMAC_EXTENDED_CONFIG *) p_transfer_tx->p_cfg->p_extend;
        i2c_master_w_extended_cfg_t * p_extend      = (i2c_master_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

        if ((p_ctrl->total < 4) || !(p_extend->enable_dma_bursts_tx))
        {
            p_dmac_extend->burst_mode       = DMAC_BURST_MODE_NONE;
            p_ctrl->p_reg->I2C_DMA_TDLR_REG = p_ctrl->total;
        }
        else if (p_ctrl->total < 8)
        {
            p_dmac_extend->burst_mode       = DMAC_BURST_MODE_4X;
            p_ctrl->p_reg->I2C_DMA_TDLR_REG = p_ctrl->total;
        }
        else
        {
            p_dmac_extend->burst_mode       = DMAC_BURST_MODE_8X;
            p_ctrl->p_reg->I2C_DMA_TDLR_REG = I2C_MASTER_W_FIFO_DEPTH - 8;
        }

        p_transfer_tx->p_cfg->p_info->p_src  = (uint16_t *) p_ctrl->p_transfer_api_tx_buff;
        p_transfer_tx->p_cfg->p_info->p_dest = (uint16_t *) p_i2c_master_w_tx_dest_buf;
        p_transfer_tx->p_cfg->p_info->length = (uint16_t) p_ctrl->total;

        p_transfer_tx->p_api->reconfigure(p_transfer_tx->p_ctrl, p_transfer_tx->p_cfg->p_info);
        p_transfer_tx->p_api->enable(p_transfer_tx->p_ctrl);

        p_ctrl->p_reg->I2C_DMA_CR_REG_b.TDMAE = 1;
 #endif
    }

 #if I2C_MASTER_W_CFG_GENERIC_ONLY
    else
    {
        mask |= I2C_MASTER_W_INT_TX_EMPTY;
    }
 #endif
#elif I2C_MASTER_W_CFG_GENERIC_ONLY
    mask |= (I2C_MASTER_W_INT_TX_EMPTY | I2C_MASTER_W_INT_RX_FULL);
#endif

    /* Enable the Generic interrupt events. */
    p_ctrl->p_reg->I2C_INTR_MASK_REG = mask;

#if BSP_FEATURE_I2C_HAS_DEDICATED_IRQS

    /* Unmask dedicated TXE & RX events. */
    p_ctrl->p_reg->I2C_MASK_REG = I2C_I2C_MASK_REG_I2C_RX_IRQ_MASK_Msk | I2C_I2C_MASK_REG_I2C_TXE_IRQ_MASK_Msk;
#endif
}

/*******************************************************************************************************************//**
 * Activates the required interrupt sources for write.
 *
 * It initiates an I2C write transmission.
 *
 * @param [in] p_ctrl    Pointer to I2C specific control structure.
 **********************************************************************************************************************/
static void i2c_master_w_write_configure (i2c_master_w_instance_ctrl_t * const p_ctrl)
{
    uint16_t mask = I2C_MASTER_W_INT_TX_ABORT;

    /* Clear TX ABORT interrupt status. */
    p_ctrl->p_reg->I2C_CLR_TX_ABRT_REG;

    if (0 == p_ctrl->restart)
    {
        mask |= I2C_MASTER_W_INT_STOP_DETECTED;

        /* Clear STOP DETECTED interrupt status. */
        p_ctrl->p_reg->I2C_CLR_STOP_DET_REG;
    }

    /* Initialize fields used during transfer. */
    p_ctrl->loaded = 0U;

#if (I2C_MASTER_W_CFG_DTC_ENABLE) || (I2C_MASTER_W_CFG_DMA_ENABLE)
    transfer_instance_t * p_transfer_tx = (transfer_instance_t *) p_ctrl->p_cfg->p_transfer_tx;

    /* Enable transfer support if possible */
    if ((NULL != p_transfer_tx) && (p_ctrl->total > 0U))
    {
        bool add_stop;
        bool add_restart;

        while (p_ctrl->loaded < p_ctrl->total)
        {
            add_stop = (p_ctrl->loaded + 1 == p_ctrl->total) && (p_ctrl->restart == 0);
            add_restart = (p_ctrl->loaded == 0) && (p_ctrl->restarted == 1);

            /* Add STOP or RESTART to write request for last or first byte if user requires it. */
            p_ctrl->p_transfer_api_tx_buff[p_ctrl->loaded] = (p_ctrl->p_buff[p_ctrl->loaded] |
                                                              (add_stop ? I2C_I2C_DATA_CMD_REG_I2C_STOP_Msk : 0) |
                                                              (add_restart ? I2C_I2C_DATA_CMD_REG_I2C_RESTART_Msk : 0));
            p_ctrl->loaded++;
        }

        uint32_t volatile const * p_i2c_master_w_tx_dest_buf = &(p_ctrl->p_reg->I2C_DATA_CMD_REG);

 #if I2C_MASTER_W_CFG_DTC_ENABLE
        p_transfer_tx->p_api->reset(p_transfer_tx->p_ctrl, (void *) (p_ctrl->p_transfer_api_tx_buff),
                                    (uint16_t *) (p_i2c_master_w_tx_dest_buf), (uint16_t) (p_ctrl->total));
 #else
  #if !I2C_MASTER_W_CFG_GENERIC_ONLY

        /* TX operation will be handled by DMA. */
        R_BSP_IrqDisable(p_ctrl->p_cfg->txi_irq);
  #endif

        /* Make sure I2C DMA is off so it's not unexpectedly triggered when channels are enabled. */
        p_ctrl->p_reg->I2C_DMA_CR_REG = 0;
        i2c_master_w_extended_cfg_t * p_extend = (i2c_master_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

        /* Configure TX DMA Channel and TX FIFO threshold level for I3C. */
        DMAC_EXTENDED_CONFIG * p_dmac_extend = (DMAC_EXTENDED_CONFIG *) p_transfer_tx->p_cfg->p_extend;

        if ((p_ctrl->total < 4) || !(p_extend->enable_dma_bursts_tx))
        {
            p_dmac_extend->burst_mode       = DMAC_BURST_MODE_NONE;
            p_ctrl->p_reg->I2C_DMA_TDLR_REG = p_ctrl->total;
        }
        else if (p_ctrl->total < 8)
        {
            p_dmac_extend->burst_mode       = DMAC_BURST_MODE_4X;
            p_ctrl->p_reg->I2C_DMA_TDLR_REG = p_ctrl->total;
        }
        else
        {
            p_dmac_extend->burst_mode       = DMAC_BURST_MODE_8X;
            p_ctrl->p_reg->I2C_DMA_TDLR_REG = I2C_MASTER_W_FIFO_DEPTH - 8;
        }

        p_transfer_tx->p_cfg->p_info->p_src  = (uint16_t *) p_ctrl->p_transfer_api_tx_buff;
        p_transfer_tx->p_cfg->p_info->p_dest = (uint16_t *) p_i2c_master_w_tx_dest_buf;
        p_transfer_tx->p_cfg->p_info->length = (uint16_t) p_ctrl->total;

        p_transfer_tx->p_api->reconfigure(p_transfer_tx->p_ctrl, p_transfer_tx->p_cfg->p_info);
        p_transfer_tx->p_api->enable(p_transfer_tx->p_ctrl);

        p_ctrl->p_reg->I2C_DMA_CR_REG = I2C_I2C_DMA_CR_REG_TDMAE_Msk;
 #endif
    }

 #if I2C_MASTER_W_CFG_GENERIC_ONLY
    else
    {
        mask |= I2C_MASTER_W_INT_TX_EMPTY;
    }
 #endif
#elif I2C_MASTER_W_CFG_GENERIC_ONLY
    mask |= I2C_MASTER_W_INT_TX_EMPTY;
#endif

#if BSP_FEATURE_I2C_HAS_DEDICATED_IRQS
 #if (BSP_FEATURE_I2C_VERSION == 1)

    /* Unmask dedicated TXE event. */
    p_ctrl->p_reg->I2C_MASK_REG = I2C_I2C_MASK_REG_I2C_TXE_IRQ_MASK_Msk;
 #elif (BSP_FEATURE_I2C_VERSION == 2)

    /* Unmask dedicated TXE and TXR events. */
    p_ctrl->p_reg->I2C_MASK_REG = I2C_I2C_MASK_REG_I2C_TXE_IRQ_MASK_Msk | I2C_I2C_MASK_REG_I2C_TXR_IRQ_MASK_Msk;
 #endif
#endif

    /* Enable the Generic interrupt events. */
    p_ctrl->p_reg->I2C_INTR_MASK_REG = mask;
}

#if (I2C_MASTER_W_CFG_DTC_ENABLE) || (I2C_MASTER_W_CFG_DMA_ENABLE)

/*******************************************************************************************************************//**
 * Configures I2C related transfer drivers (if enabled).
 *
 * @param[in]   p_cfg                      Pointer to I2C specific configuration structure.
 *
 * @retval      FSP_SUCCESS                Transfer interface initialized successfully.
 * @retval      FSP_ERR_ASSERTION          Pointer to transfer instance p_api, p_cfg or p_cfg->p_info are NULL.
 **********************************************************************************************************************/
static fsp_err_t i2c_master_w_transfer_open (i2c_master_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;

    if (NULL != p_cfg->p_transfer_rx)
    {
        err = i2c_master_w_transfer_configure(p_cfg->p_transfer_rx, I2C_MASTER_W_TRANSFER_DIR_READ);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    if (NULL != p_cfg->p_transfer_tx)
    {
        err = i2c_master_w_transfer_configure(p_cfg->p_transfer_tx, I2C_MASTER_W_TRANSFER_DIR_WRITE);
        if (FSP_SUCCESS != err)
        {
            if (NULL != p_cfg->p_transfer_rx)
            {
                p_cfg->p_transfer_rx->p_api->close(p_cfg->p_transfer_rx->p_ctrl);
            }

            return err;
        }
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configures I2C related transfer.
 * @param[in]     p_transfer                     Pointer to transfer instance.
 * @param[in]     direction                      I2C direction Read or Write.
 *
 * @retval        FSP_SUCCESS                    Transfer interface is configured with valid parameters.
 * @retval        FSP_ERR_ASSERTION              Pointer to transfer instance p_api, p_cfg or p_cfg->p_info are NULL.
 **********************************************************************************************************************/
static fsp_err_t i2c_master_w_transfer_configure (transfer_instance_t const * p_transfer,
                                                  i2c_master_w_transfer_dir_t direction)
{
    fsp_err_t err;

    /* Set default transfer info and open receive transfer module, if enabled. */
 #if I2C_MASTER_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_transfer->p_api);
    FSP_ASSERT(NULL != p_transfer->p_cfg);
    FSP_ASSERT(NULL != p_transfer->p_cfg->p_info);
 #endif
    transfer_info_t * p_cfg = p_transfer->p_cfg->p_info;
    if (I2C_MASTER_W_TRANSFER_DIR_READ == direction)
    {
        p_cfg->transfer_settings_word = I2C_MASTER_W_DTC_RX_TRANSFER_SETTINGS;
    }
    else
    {
        p_cfg->transfer_settings_word = I2C_MASTER_W_DTC_TX_TRANSFER_SETTINGS;
    }

    err = p_transfer->p_api->open(p_transfer->p_ctrl, p_transfer->p_cfg);
    FSP_ERROR_RETURN((FSP_SUCCESS == err), err);

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * Performs an I2C read transmission.
 *
 * @param [in] p_ctrl    Pointer to I2C specific control structure.
 * @param [in] event     Event from Interrupt Status Register.
 *
 **********************************************************************************************************************/
static void i2c_master_w_isr_rx_handler (i2c_master_w_instance_ctrl_t * p_ctrl, uint32_t event)
{
#if I2C_MASTER_W_CFG_GENERIC_ONLY
    bool add_stop;
    bool add_restart;

    /* Send CMDs to issue READ requests. */
    while ((p_ctrl->loaded < p_ctrl->total) && p_ctrl->p_reg->I2C_STATUS_REG_b.TFNF)
    {
        p_ctrl->loaded++;

        add_stop    = ((p_ctrl->loaded == p_ctrl->total) && (p_ctrl->restart == 0));
        add_restart = ((p_ctrl->loaded == 1) && (p_ctrl->restarted == 1));

        /* Add STOP or RESTART to read request for last or first byte. */
        p_ctrl->p_reg->I2C_DATA_CMD_REG = I2C_I2C_DATA_CMD_REG_I2C_CMD_Msk |
                                          (add_stop ? I2C_I2C_DATA_CMD_REG_I2C_STOP_Msk : 0) |
                                          (add_restart ? I2C_I2C_DATA_CMD_REG_I2C_RESTART_Msk : 0);;
    }

    /* All command data have been send. */
    if ((event & I2C_MASTER_W_INT_TX_EMPTY) && (p_ctrl->loaded == p_ctrl->total))
    {
        /* Mask TX Empty event both in Generic and dedicated TXE interrupts. */
        p_ctrl->p_reg->I2C_INTR_MASK_REG_b.M_TX_EMPTY = 0;
 #if BSP_FEATURE_I2C_HAS_DEDICATED_IRQS
        p_ctrl->p_reg->I2C_MASK_REG_b.I2C_TXE_IRQ_MASK = 0;
 #endif
    }

#else
    FSP_PARAMETER_NOT_USED(event);
#endif

    /* Read data from RX FIFO. */
    while (p_ctrl->p_reg->I2C_RXFLR_REG_b.RXFLR && p_ctrl->nof_bytes < p_ctrl->total)
    {
        p_ctrl->p_buff[p_ctrl->nof_bytes] = p_ctrl->p_reg->I2C_DATA_CMD_REG_b.I2C_DAT;
        p_ctrl->nof_bytes++;
    }

#if (I2C_MASTER_W_CFG_DTC_ENABLE) || (I2C_MASTER_W_CFG_DMA_ENABLE)
    if (NULL == p_ctrl->p_cfg->p_transfer_rx)
    {
#endif

    /* All data have been read. */
    if (p_ctrl->nof_bytes == p_ctrl->total)
    {
        if (p_ctrl->restart)
        {
            p_ctrl->restart   = false;
            p_ctrl->restarted = true;
        }

        /* Notify anyone waiting that the transfer is completed. */
        i2c_master_w_notify(p_ctrl, I2C_MASTER_EVENT_RX_COMPLETE);
    }

#if (I2C_MASTER_W_CFG_DTC_ENABLE) || (I2C_MASTER_W_CFG_DMA_ENABLE)
}
#endif
}

/*******************************************************************************************************************//**
 * Performs an I2C write transmission.
 *
 * @param [in] p_ctrl    Pointer to I2C specific control structure.
 *
 **********************************************************************************************************************/
static void i2c_master_w_isr_tx_handler (i2c_master_w_instance_ctrl_t * p_ctrl)
{
    bool add_stop;
    bool add_restart;

    while (p_ctrl->loaded < p_ctrl->total && p_ctrl->p_reg->I2C_STATUS_REG_b.TFNF)
    {
        add_stop    = ((p_ctrl->loaded + 1 == p_ctrl->total) && (p_ctrl->restart == 0));
        add_restart = ((p_ctrl->loaded == 0) && (p_ctrl->restarted == 1));

        /* Add STOP or RESTART to write request for last or first byte if user requires it. */
        p_ctrl->p_reg->I2C_DATA_CMD_REG = p_ctrl->p_buff[p_ctrl->loaded] |
                                          (add_stop ? I2C_I2C_DATA_CMD_REG_I2C_STOP_Msk : 0) |
                                          (add_restart ? I2C_I2C_DATA_CMD_REG_I2C_RESTART_Msk : 0);

        p_ctrl->loaded++;
    }

#if (I2C_MASTER_W_CFG_DTC_ENABLE) || (I2C_MASTER_W_CFG_DMA_ENABLE)
    if (NULL == p_ctrl->p_cfg->p_transfer_tx)
    {
#endif

    /* Trigger reply when all data were written to TX FIFO. */
    if (p_ctrl->loaded == p_ctrl->total)
    {
#if (BSP_FEATURE_I2C_HAS_DEDICATED_IRQS && (BSP_FEATURE_I2C_VERSION == 1))

        /* Enable the dedicated Transmit End event. */
        p_ctrl->p_reg->I2C_MASK_REG = I2C_I2C_MASK_REG_I2C_TXR_IRQ_MASK_Msk;
#endif
        if (p_ctrl->restart)
        {
            p_ctrl->restart   = false;
            p_ctrl->restarted = true;
#if (I2C_MASTER_W_CFG_GENERIC_ONLY || (BSP_FEATURE_I2C_VERSION == 2))

            /* Notify anyone waiting that the transfer is completed. */
            i2c_master_w_notify(p_ctrl, I2C_MASTER_EVENT_TX_COMPLETE);
#endif
        }

#if I2C_MASTER_W_CFG_GENERIC_ONLY
        else
        {
            /* Disable TX Empty Interrupt event. */
            p_ctrl->p_reg->I2C_INTR_MASK_REG_b.M_TX_EMPTY = 0;
        }
#endif
    }

#if (I2C_MASTER_W_CFG_DTC_ENABLE) || (I2C_MASTER_W_CFG_DMA_ENABLE)
}
#endif
}

/******************************************************************************************************************//**
 * Generic I2C Event interrupt routine.
 *
 * This function implements the Generic ISR routine.
 *********************************************************************************************************************/
void i2c_master_w_gen_isr (void)
{
    /* Save context if RTOS is used. */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    i2c_master_w_instance_ctrl_t * p_ctrl = (i2c_master_w_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
#if BSP_FEATURE_BSP_HAS_ICU

    /* Clear the IR flag in the ICU. */
    R_BSP_IrqStatusClear(irq);
#endif

    uint32_t mask = p_ctrl->p_reg->I2C_INTR_STAT_REG;

    if (mask & I2C_MASTER_W_INT_TX_ABORT)
    {
        /* Notify anyone waiting that the transfer is Aborted due to error. */
        i2c_master_w_notify(p_ctrl, I2C_MASTER_EVENT_ABORTED);

        /* Mark the transaction as completed. */
        p_ctrl->loaded = p_ctrl->total;

        /* Clear abort. */
        p_ctrl->p_reg->I2C_CLR_TX_ABRT_REG;

#if !I2C_MASTER_W_CFG_GENERIC_ONLY
        R_BSP_IrqClearPending(p_ctrl->p_cfg->tei_irq);
        p_ctrl->p_reg->I2C_MASK_REG = 0;
#endif

        /* Restore context if RTOS is used. */
        FSP_CONTEXT_RESTORE;

        return;
    }

    if (mask & I2C_MASTER_W_INT_STOP_DETECTED)
    {
#if I2C_MASTER_W_CFG_GENERIC_ONLY
        if (p_ctrl->loaded == p_ctrl->total)
        {
            /* Notify anyone waiting that the transfer is completed. */
            if (I2C_MASTER_W_TRANSFER_DIR_WRITE == p_ctrl->read)
            {
 #if BSP_FEATURE_I2C_HAS_DEDICATED_IRQS

                /* Enable the dedicated Transmit End event. */
                p_ctrl->p_reg->I2C_MASK_REG = I2C_I2C_MASK_REG_I2C_TXR_IRQ_MASK_Msk;
 #endif

                i2c_master_w_notify(p_ctrl, I2C_MASTER_EVENT_TX_COMPLETE);
            }
            else
            {
                i2c_master_w_notify(p_ctrl, I2C_MASTER_EVENT_RX_COMPLETE);
            }
        }
        else
        {
            /* Notify anyone waiting that the transfer is Aborted due to error. */
            i2c_master_w_notify(p_ctrl, I2C_MASTER_EVENT_ABORTED);

            /* Mark the transaction as completed. */
            p_ctrl->loaded = p_ctrl->total;
        }

#else
        if (I2C_MASTER_W_TRANSFER_DIR_WRITE == p_ctrl->read)
        {
 #if BSP_FEATURE_I2C_HAS_DEDICATED_IRQS

            /* Enable the dedicated Transmit End event. */
            p_ctrl->p_reg->I2C_MASK_REG = I2C_I2C_MASK_REG_I2C_TXR_IRQ_MASK_Msk;
 #endif
        }
        else
        {
            if (p_ctrl->loaded == p_ctrl->total)
            {
                /* Notify anyone waiting that the transfer is completed. */
                i2c_master_w_notify(p_ctrl, I2C_MASTER_EVENT_RX_COMPLETE);
            }
            else
            {
                /* Notify anyone waiting that the transfer is Aborted due to error. */
                i2c_master_w_notify(p_ctrl, I2C_MASTER_EVENT_ABORTED);

                /* Mark the transaction as completed. */
                p_ctrl->loaded = p_ctrl->total;
            }
        }
#endif

        /* Reset restarted status */
        if (p_ctrl->restarted)
        {
            p_ctrl->restarted = false;
        }

        /* Reset STOP_DETECTED interrupt state. */
        p_ctrl->p_reg->I2C_CLR_STOP_DET_REG;

        /* Restore context if RTOS is used. */
        FSP_CONTEXT_RESTORE;

        return;
    }

#if I2C_MASTER_W_CFG_GENERIC_ONLY

    /* Call handler. */
    if (I2C_MASTER_W_TRANSFER_DIR_WRITE == p_ctrl->read)
    {
        i2c_master_w_isr_tx_handler(p_ctrl);
    }
    else
    {
        i2c_master_w_isr_rx_handler(p_ctrl, mask);
    }
#endif

    /* Restore context if RTOS is used. */
    FSP_CONTEXT_RESTORE;
}

#if !I2C_MASTER_W_CFG_GENERIC_ONLY

/******************************************************************************************************************//**
 * I2C RX FIFO Full Event interrupt routine.
 *
 * This function implements the RXI ISR routine.
 *********************************************************************************************************************/
void i2c_master_w_rxi_isr (void)
{
    /* Save context if RTOS is used. */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    i2c_master_w_instance_ctrl_t * p_ctrl = (i2c_master_w_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

 #if BSP_FEATURE_I2C_IRQ_TRIGGER_EDGE

    /* Clear the IR flag in the ICU. */
    R_BSP_IrqStatusClear(irq);
 #endif

 #if I2C_MASTER_W_CFG_DTC_ENABLE
    transfer_instance_t * p_transfer_rx = (transfer_instance_t *) p_ctrl->p_cfg->p_transfer_rx;

    /* Check if DTC is enabled. */
    if (NULL != p_transfer_rx)
    {
        p_ctrl->p_reg->I2C_MASK_REG = 0;
        R_BSP_IrqClearPending(p_ctrl->p_cfg->rxi_irq);

        if (p_ctrl->restart)
        {
            p_ctrl->restart   = false;
            p_ctrl->restarted = true;

            /* Notify anyone waiting that the transfer is completed. */
            i2c_master_w_notify(p_ctrl, I2C_MASTER_EVENT_RX_COMPLETE);
        }

        /* Restore context if RTOS is used. */
        FSP_CONTEXT_RESTORE;

        return;
    }
 #endif

    /* Call handler. */
    if (I2C_MASTER_W_TRANSFER_DIR_READ == p_ctrl->read)
    {
        i2c_master_w_isr_rx_handler(p_ctrl, I2C_MASTER_W_INT_RX_FULL);
    }

 #if !BSP_FEATURE_I2C_IRQ_TRIGGER_EDGE

    /* Clear the IR flag in the ICU. */
    R_BSP_IrqStatusClear(irq);
 #endif

    /* Restore context if RTOS is used. */
    FSP_CONTEXT_RESTORE;
}

/******************************************************************************************************************//**
 * I2C TX FIFO Empty Event interrupt routine.
 *
 * This function implements the TXI ISR routine.
 *********************************************************************************************************************/
void i2c_master_w_txi_isr (void)
{
    /* Save context if RTOS is used. */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    i2c_master_w_instance_ctrl_t * p_ctrl = (i2c_master_w_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

 #if BSP_FEATURE_I2C_IRQ_TRIGGER_EDGE

    /* Clear the IR flag in the ICU. */
    R_BSP_IrqStatusClear(irq);
 #endif

 #if I2C_MASTER_W_CFG_DTC_ENABLE
    transfer_instance_t * p_transfer_tx = (transfer_instance_t *) p_ctrl->p_cfg->p_transfer_tx;

    /* Check if DTC is enabled. */
    if (NULL != p_transfer_tx)
    {
        p_ctrl->p_reg->I2C_MASK_REG_b.I2C_TXE_IRQ_MASK = 0;
        R_BSP_IrqClearPending(p_ctrl->p_cfg->txi_irq);

        if (!p_ctrl->read)
        {
            if (p_ctrl->restart)
            {
                p_ctrl->restart   = false;
                p_ctrl->restarted = true;

                /* Enable the dedicated Transmit End event. */
                p_ctrl->p_reg->I2C_MASK_REG = I2C_I2C_MASK_REG_I2C_TXR_IRQ_MASK_Msk;
            }
        }

        /* Restore context if RTOS is used. */
        FSP_CONTEXT_RESTORE;

        return;
    }
 #endif

    /* Call handler. */
    if (I2C_MASTER_W_TRANSFER_DIR_WRITE == p_ctrl->read)
    {
        i2c_master_w_isr_tx_handler(p_ctrl);
    }
    else
    {
        bool add_stop;
        bool add_restart;

        /* Send CMDs to issue READ requests. */
        while ((p_ctrl->loaded < p_ctrl->total) && p_ctrl->p_reg->I2C_STATUS_REG_b.TFNF)
        {
            p_ctrl->loaded++;
            add_stop = (p_ctrl->loaded == p_ctrl->total) && (p_ctrl->restart == 0);
            add_restart = (p_ctrl->loaded == 1) && (p_ctrl->restarted == 1);
            /* Add STOP or RESTART to read request for last or first byte. */
            p_ctrl->p_reg->I2C_DATA_CMD_REG = I2C_I2C_DATA_CMD_REG_I2C_CMD_Msk |
                                              (add_stop ? I2C_I2C_DATA_CMD_REG_I2C_STOP_Msk : 0) |
                                              (add_restart ? I2C_I2C_DATA_CMD_REG_I2C_RESTART_Msk : 0);
        }

        /* All command data have been send. */
        if (p_ctrl->loaded == p_ctrl->total)
        {
            /* Mask the dedicated TXE interrupt. */
            p_ctrl->p_reg->I2C_MASK_REG_b.I2C_TXE_IRQ_MASK = 0;
        }
    }

 #if !BSP_FEATURE_I2C_IRQ_TRIGGER_EDGE

    /* Clear the IR flag in the ICU. */
    R_BSP_IrqStatusClear(irq);
 #endif

    /* Restore context if RTOS is used. */
    FSP_CONTEXT_RESTORE;
}

/******************************************************************************************************************//**
 * I2C Transmission End Event interrupt routine.
 *
 * This function implements the TEI ISR routine.
 *********************************************************************************************************************/
void i2c_master_w_tei_isr (void)
{
    /* Save context if RTOS is used. */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    i2c_master_w_instance_ctrl_t * p_ctrl = (i2c_master_w_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Clear the IR flag in the ICU. */
    R_BSP_IrqStatusClear(irq);

    if (p_ctrl->loaded == p_ctrl->total)
    {
        /* Notify anyone waiting that the transfer is completed. */
        i2c_master_w_notify(p_ctrl, I2C_MASTER_EVENT_TX_COMPLETE);
    }
    else
    {
        /* Notify anyone waiting that the transfer is Aborted due to error. */
        i2c_master_w_notify(p_ctrl, I2C_MASTER_EVENT_ABORTED);

        /* Mark the transaction as completed. */
        p_ctrl->loaded = p_ctrl->total;
    }

    /* Restore context if RTOS is used. */
    FSP_CONTEXT_RESTORE;
}

#endif

#if (I2C_MASTER_W_CFG_DMA_ENABLE)

/*******************************************************************************************************************//**
 * Callback that must be called after a RX DMAC transfer completes with restart condition.
 *
 * @param[in]     p_ctrl     Pointer to I2C Master instance control block
 **********************************************************************************************************************/
void i2c_master_w_rx_dmac_callback (i2c_master_w_instance_ctrl_t * const p_ctrl)
{
 #if !I2C_MASTER_W_CFG_GENERIC_ONLY
    R_BSP_IrqEnable(p_ctrl->p_cfg->rxi_irq);
 #endif
    if (p_ctrl->restart)
    {
        p_ctrl->restart   = false;
        p_ctrl->restarted = true;

        /* Notify anyone waiting that the transfer is completed. */
        i2c_master_w_notify(p_ctrl, I2C_MASTER_EVENT_RX_COMPLETE);
    }
}

/*******************************************************************************************************************//**
 * Callback that must be called after a TX DMAC transfer completes with restart condition.
 *
 * @param[in]     p_ctrl     Pointer to I2C Master instance control block
 **********************************************************************************************************************/
void i2c_master_w_tx_dmac_callback (i2c_master_w_instance_ctrl_t * const p_ctrl)
{
 #if !I2C_MASTER_W_CFG_GENERIC_ONLY
    R_BSP_IrqEnable(p_ctrl->p_cfg->txi_irq);
 #endif
    if (p_ctrl->restart)
    {
        if (p_ctrl->read)
        {
 #if BSP_FEATURE_I2C_HAS_DEDICATED_IRQS

            /* Mask the dedicated TXE interrupt. */
            p_ctrl->p_reg->I2C_MASK_REG_b.I2C_TXE_IRQ_MASK = 0;
 #endif
        }
        else
        {
            p_ctrl->restart   = false;
            p_ctrl->restarted = true;
 #if BSP_FEATURE_I2C_HAS_DEDICATED_IRQS

            /* Enable the dedicated Transmit End event. */
            p_ctrl->p_reg->I2C_MASK_REG = I2C_I2C_MASK_REG_I2C_TXR_IRQ_MASK_Msk;
 #endif

 #if I2C_MASTER_W_CFG_GENERIC_ONLY

            /* Notify anyone waiting that the transfer is completed. */
            i2c_master_w_notify(p_ctrl, I2C_MASTER_EVENT_TX_COMPLETE);
 #endif
        }
    }
}

#endif
