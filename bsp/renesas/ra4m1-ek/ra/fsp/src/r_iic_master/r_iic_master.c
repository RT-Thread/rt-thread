/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_iic_master.h"
#if IIC_MASTER_CFG_DTC_ENABLE
 #include "r_dtc.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "IIC" in ASCII, used to determine if channel is open. */
#define IIC_MASTER_OPEN                             (0x52494943U)

#define I2C_CODE_READ                               (0x01U)
#define I2C_CODE_10BIT                              (0xF0U)

/* The timeout interrupt enable bit */
#define IIC_MASTER_TMO_EN_BIT                       (0x01)

/* The arbitration loss detection interrupt enable bit */
#define IIC_MASTER_ALD_EN_BIT                       (0x02)

/* The start condition detection interrupt enable bit */
#define IIC_MASTER_STR_EN_BIT                       (0x04)

/* The stop condition detection interrupt enable bit */
#define IIC_MASTER_STP_EN_BIT                       (0x08)

/* The NAK reception interrupt enable bit */
#define IIC_MASTER_NAK_EN_BIT                       (0x10)

/* The receive data full interrupt enable bit */
#define IIC_MASTER_RXI_EN_BIT                       (0x20)

/* The transmit end interrupt enable bit */
#define IIC_MASTER_TEI_EN_BIT                       (0x40)

/* The transmit data empty interrupt enable bit */
#define IIC_MASTER_TXI_EN_BIT                       (0x80)

/* Bit position for STOP condition flag in ICSR2 */
#define IIC_MASTER_ICSR2_STOP_BIT                   (0x08U)

#define IIC_MASTER_BUS_RATE_REG_RESERVED_BITS       (0xE0U)
#define IIC_MASTER_INTERNAL_REF_CLOCK_SELECT_MAX    (0x07U)

#define IIC_MASTER_SLAVE_10_BIT_ADDR_LEN_ADJUST     (2U)

#define IIC_MASTER_DTC_RX_TRANSFER_SETTINGS         ((TRANSFER_MODE_NORMAL << TRANSFER_SETTINGS_MODE_BITS) |         \
                                                     (TRANSFER_SIZE_1_BYTE << TRANSFER_SETTINGS_SIZE_BITS) |         \
                                                     (TRANSFER_ADDR_MODE_FIXED << TRANSFER_SETTINGS_SRC_ADDR_BITS) | \
                                                     (TRANSFER_IRQ_END << TRANSFER_SETTINGS_IRQ_BITS) |              \
                                                     (TRANSFER_ADDR_MODE_INCREMENTED <<                              \
                                                      TRANSFER_SETTINGS_DEST_ADDR_BITS))
#define IIC_MASTER_DTC_TX_TRANSFER_SETTINGS         ((TRANSFER_MODE_NORMAL << TRANSFER_SETTINGS_MODE_BITS) | \
                                                     (TRANSFER_SIZE_1_BYTE << TRANSFER_SETTINGS_SIZE_BITS) | \
                                                     (TRANSFER_ADDR_MODE_INCREMENTED <<                      \
                                                      TRANSFER_SETTINGS_SRC_ADDR_BITS) |                     \
                                                     (TRANSFER_IRQ_END << TRANSFER_SETTINGS_IRQ_BITS) |      \
                                                     (TRANSFER_ADDR_MODE_FIXED << TRANSFER_SETTINGS_DEST_ADDR_BITS))
#define IIC_MASTER_FUNCTION_ENABLE_REG_VAL          (0x02U)
#define IIC_MASTER_INTERRUPT_ENABLE_INIT_MASK       (0xB3U)
#define IIC_MASTER_FUNCTION_ENABLE_INIT_SETTINGS    (0x77U)
#define IIC_MASTER_STATUS_REGISTER_2_ERR_MASK       (0x1FU)
#define IIC_MASTER_BUS_MODE_REGISTER_1_MASK         (0x08U)
#define IIC_MASTER_BUS_MODE_REGISTER_2_MASK         (0x04U)
#define IIC_MASTER_SYSDIVCK_ICLK_MASK               (0x0F000000U)
#define IIC_MASTER_SYSDIVCK_PCLKB_MASK              (0x00000F00U)
#define IIC_MASTER_PRV_SCL_SDA_NOT_DRIVEN           (0x1FU)
#define IIC_MASTER_ICCR1_ICE_BIT_MASK               (0x80)
#define IIC_MASTER_ICCR1_IICRST_BIT_MASK            (0x40)
#define IIC_MASTER_ICCR2_SP_BIT_MASK                (0x08)
#define IIC_MASTER_ICCR2_RS_BIT_MASK                (0x04)
#define IIC_MASTER_ICCR2_ST_BIT_MASK                (0x02)

/* Worst case ratio of (ICLK/PCLKB) = 64 bytes approximately.
 * 3 PCLKB cycles is the number of cycles to wait for IICn.
 * Refer "Table 3.2 Access cycles (1 of 2)" of the RA6M3 manual R01UH0886EJ0100)
 */
#define IIC_MASTER_PERIPHERAL_REG_MAX_WAIT          (0x40U * 0x03U)

#define IIC_MASTER_HARDWARE_REGISTER_WAIT(reg, required_value, timeout) \
    while ((timeout))                                                   \
    {                                                                   \
        if ((required_value) == (reg))                                  \
        {                                                               \
            break;                                                      \
        }                                                               \
        (timeout)--;                                                    \
    }

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Hardware errors and events that can occur on the IIC */
typedef enum e_iic_master_err_event
{
    IIC_MASTER_ERR_EVENT_NONE             = 0,
    IIC_MASTER_ERR_EVENT_TIMEOUT          = 1,
    IIC_MASTER_ERR_EVENT_ARBITRATION_LOSS = 2,
    IIC_MASTER_ERR_EVENT_START            = 4,
    IIC_MASTER_ERR_EVENT_STOP             = 8,
    IIC_MASTER_ERR_EVENT_NACK             = 16
} iic_master_err_t;

/* IIC read/write enumeration */
typedef enum e_iic_master_transfer_dir_option
{
    IIC_MASTER_TRANSFER_DIR_WRITE = 0x0,
    IIC_MASTER_TRANSFER_DIR_READ  = 0x1
} iic_master_transfer_dir_t;

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * iic_master_prv_ns_callback)(i2c_master_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile iic_master_prv_ns_callback)(i2c_master_callback_args_t * p_args);
#endif

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

void iic_master_rxi_isr(void);
void iic_master_txi_isr(void);
void iic_master_tei_isr(void);
void iic_master_eri_isr(void);

/* Internal helper functions */
static void      iic_master_abort_seq_master(iic_master_instance_ctrl_t * const p_ctrl, bool iic_reset);
static fsp_err_t iic_master_read_write(i2c_master_ctrl_t * const p_api_ctrl,
                                       uint8_t * const           p_buffer,
                                       uint32_t const            bytes,
                                       iic_master_transfer_dir_t direction);
static void iic_master_notify(iic_master_instance_ctrl_t * const p_ctrl, i2c_master_event_t const event);

#if IIC_MASTER_CFG_DTC_ENABLE
static fsp_err_t iic_master_transfer_open(i2c_master_cfg_t const * const p_cfg);
static fsp_err_t iic_master_transfer_configure(transfer_instance_t const * p_transfer,
                                               iic_master_transfer_dir_t   direction);

#endif

/* Interrupt handlers */
static void iic_master_rxi_master(iic_master_instance_ctrl_t * p_ctrl);
static void iic_master_txi_master(iic_master_instance_ctrl_t * p_ctrl);
static void iic_master_tei_master(iic_master_instance_ctrl_t * p_ctrl);
static void iic_master_err_master(iic_master_instance_ctrl_t * p_ctrl);

/* Functions that manipulate hardware */
static void iic_master_open_hw_master(iic_master_instance_ctrl_t * const p_ctrl,
                                      i2c_master_cfg_t const * const     p_cfg);
static fsp_err_t iic_master_run_hw_master(iic_master_instance_ctrl_t * const p_ctrl);
static void      iic_master_rxi_read_data(iic_master_instance_ctrl_t * const p_ctrl);
static void      iic_master_txi_send_address(iic_master_instance_ctrl_t * const p_ctrl);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

/* IIC Implementation of I2C device master interface */
i2c_master_api_t const g_i2c_master_on_iic =
{
    .open            = R_IIC_MASTER_Open,
    .read            = R_IIC_MASTER_Read,
    .write           = R_IIC_MASTER_Write,
    .abort           = R_IIC_MASTER_Abort,
    .slaveAddressSet = R_IIC_MASTER_SlaveAddressSet,
    .close           = R_IIC_MASTER_Close,
    .statusGet       = R_IIC_MASTER_StatusGet,
    .callbackSet     = R_IIC_MASTER_CallbackSet
};

/*******************************************************************************************************************//**
 * @addtogroup IIC_MASTER
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Opens the I2C device.
 *
 * @retval  FSP_SUCCESS                       Requested clock rate was set exactly.
 * @retval  FSP_ERR_ALREADY_OPEN              Module is already open.
 * @retval  FSP_ERR_IP_CHANNEL_NOT_PRESENT    Channel is not available on this MCU.
 * @retval  FSP_ERR_ASSERTION                 Parameter check failure due to one or more reasons below:
 *                                            1. p_api_ctrl or p_cfg is NULL.
 *                                            2. extended parameter is NULL.
 *                                            3. Callback parameter is NULL.
 *                                            4. Set the rate to fast mode plus on a channel which does not support it.
 *                                            5. Invalid IRQ number assigned
 **********************************************************************************************************************/
fsp_err_t R_IIC_MASTER_Open (i2c_master_ctrl_t * const p_api_ctrl, i2c_master_cfg_t const * const p_cfg)
{
    iic_master_instance_ctrl_t * p_ctrl = (iic_master_instance_ctrl_t *) p_api_ctrl;
#if IIC_MASTER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl != NULL);
    FSP_ASSERT(p_cfg != NULL);
    FSP_ASSERT(p_cfg->p_extend != NULL);
    FSP_ASSERT(p_cfg->rxi_irq >= (IRQn_Type) 0);
    FSP_ASSERT(p_cfg->txi_irq >= (IRQn_Type) 0);
    FSP_ASSERT(p_cfg->tei_irq >= (IRQn_Type) 0);
    FSP_ASSERT(p_cfg->eri_irq >= (IRQn_Type) 0);
    FSP_ERROR_RETURN(IIC_MASTER_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);

    FSP_ERROR_RETURN(BSP_FEATURE_IIC_VALID_CHANNEL_MASK & (1 << p_cfg->channel), FSP_ERR_IP_CHANNEL_NOT_PRESENT);

    /* If rate is configured as Fast mode plus, check whether the channel supports it */
    if (I2C_MASTER_RATE_FASTPLUS == p_cfg->rate)
    {
        FSP_ASSERT((BSP_FEATURE_IIC_FAST_MODE_PLUS & (1U << p_cfg->channel)));
    }
#endif

    p_ctrl->p_reg = (R_IIC0_Type *) ((uint32_t) R_IIC0 + (p_cfg->channel * ((uint32_t) R_IIC1 - (uint32_t) R_IIC0)));

    /* Record the pointer to the configuration structure for later use */
    p_ctrl->p_cfg             = p_cfg;
    p_ctrl->slave             = p_cfg->slave;
    p_ctrl->addr_mode         = p_cfg->addr_mode;
    p_ctrl->p_callback        = p_cfg->p_callback;
    p_ctrl->p_context         = p_cfg->p_context;
    p_ctrl->p_callback_memory = NULL;

    R_BSP_MODULE_START(FSP_IP_IIC, p_cfg->channel);

    /* Open the hardware in master mode. Performs IIC initialization as described in hardware manual (see Section 36.3.2
     * 'Initial Settings' of the RA6M3 manual R01UH0886EJ0100). */
    iic_master_open_hw_master(p_ctrl, p_cfg);

#if IIC_MASTER_CFG_DTC_ENABLE

    /* Open the IIC transfer interface if available */
    fsp_err_t err = iic_master_transfer_open(p_cfg);
    if (FSP_SUCCESS != err)
    {
        R_BSP_MODULE_STOP(FSP_IP_IIC, p_cfg->channel);

        return err;
    }
#endif

    p_ctrl->p_buff    = NULL;
    p_ctrl->total     = 0U;
    p_ctrl->remain    = 0U;
    p_ctrl->loaded    = 0U;
    p_ctrl->read      = false;
    p_ctrl->restart   = false;
    p_ctrl->err       = false;
    p_ctrl->restarted = false;
    p_ctrl->open      = IIC_MASTER_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Performs a read from the I2C device.
 * The caller will be notified when the operation has completed (successfully) by an
 * I2C_MASTER_EVENT_RX_COMPLETE in the callback.
 *
 * @retval  FSP_SUCCESS             Function executed without issue.
 * @retval  FSP_ERR_ASSERTION       p_api_ctrl, p_dest or bytes is NULL.
 * @retval  FSP_ERR_INVALID_SIZE    Provided number of bytes more than uint16_t size (65535) while DTC is used
 *                                  for data transfer.
 * @retval  FSP_ERR_IN_USE          Bus busy condition. Another transfer was in progress.
 * @retval  FSP_ERR_NOT_OPEN        Handle is not initialized.  Call R_IIC_MASTER_Open to initialize the control block.
 **********************************************************************************************************************/
fsp_err_t R_IIC_MASTER_Read (i2c_master_ctrl_t * const p_api_ctrl,
                             uint8_t * const           p_dest,
                             uint32_t const            bytes,
                             bool const                restart)
{
#if IIC_MASTER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl != NULL);
    FSP_ASSERT(bytes != 0U);
#endif
    fsp_err_t err = FSP_SUCCESS;

    /* Record the restart information about this transfer.
     * This is done here to keep the parameter (argument) list of iic_master_read_write to 4. */
    ((iic_master_instance_ctrl_t *) p_api_ctrl)->restart = restart;

    /* Call the common helper function to perform I2C Read operation.*/
    err = iic_master_read_write(p_api_ctrl, p_dest, bytes, IIC_MASTER_TRANSFER_DIR_READ);

    return err;
}

/*******************************************************************************************************************//**
 * Performs a write to the I2C device.
 * The caller will be notified when the operation has completed (successfully) by an
 * I2C_MASTER_EVENT_TX_COMPLETE in the callback.
 *
 * @retval  FSP_SUCCESS           Function executed without issue.
 * @retval  FSP_ERR_ASSERTION     p_api_ctrl or p_src is NULL.
 * @retval  FSP_ERR_INVALID_SIZE  Provided number of bytes more than uint16_t size (65535) while DTC is used
 *                                for data transfer.
 * @retval  FSP_ERR_IN_USE        Bus busy condition. Another transfer was in progress.
 * @retval  FSP_ERR_NOT_OPEN      Handle is not initialized.  Call R_IIC_MASTER_Open to initialize the control block.
 **********************************************************************************************************************/
fsp_err_t R_IIC_MASTER_Write (i2c_master_ctrl_t * const p_api_ctrl,
                              uint8_t * const           p_src,
                              uint32_t const            bytes,
                              bool const                restart)
{
#if IIC_MASTER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl != NULL);
#endif
    fsp_err_t err = FSP_SUCCESS;

    /* Record the restart information about this transfer.
     * This is done here to keep the parameter (argument) list of iic_master_read_write to 4. */
    ((iic_master_instance_ctrl_t *) p_api_ctrl)->restart = restart;

    /* Call the common helper function to perform I2C Write operation.*/
    err = iic_master_read_write(p_api_ctrl, p_src, bytes, IIC_MASTER_TRANSFER_DIR_WRITE);

    return err;
}

/*******************************************************************************************************************//**
 * Safely aborts any in-progress transfer and forces the IIC peripheral into ready state.
 *
 *
 * @retval  FSP_SUCCESS             Channel was reset successfully.
 * @retval  FSP_ERR_ASSERTION       p_api_ctrl is NULL.
 * @retval  FSP_ERR_NOT_OPEN        Handle is not initialized.  Call R_IIC_MASTER_Open to initialize the control block.
 *
 * @note A callback will not be invoked in case an in-progress transfer gets aborted by calling this API.
 **********************************************************************************************************************/
fsp_err_t R_IIC_MASTER_Abort (i2c_master_ctrl_t * const p_api_ctrl)
{
    iic_master_instance_ctrl_t * p_ctrl = (iic_master_instance_ctrl_t *) p_api_ctrl;

#if IIC_MASTER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ERROR_RETURN(IIC_MASTER_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Abort any transfer happening on the channel */
    iic_master_abort_seq_master(p_ctrl, true);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets address and addressing mode of the slave device.
 * This function is used to set the device address and addressing mode of the slave
 * without reconfiguring the entire bus.
 *
 * @retval  FSP_SUCCESS             Address of the slave is set correctly.
 * @retval  FSP_ERR_ASSERTION       Pointer to control structure is NULL.
 * @retval  FSP_ERR_IN_USE          Another transfer was in-progress.
 * @retval  FSP_ERR_NOT_OPEN        Handle is not initialized.  Call R_IIC_MASTER_Open to initialize the control block.
 **********************************************************************************************************************/
fsp_err_t R_IIC_MASTER_SlaveAddressSet (i2c_master_ctrl_t * const    p_api_ctrl,
                                        uint32_t const               slave,
                                        i2c_master_addr_mode_t const addr_mode)
{
    iic_master_instance_ctrl_t * p_ctrl = (iic_master_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err = FSP_SUCCESS;

#if IIC_MASTER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ERROR_RETURN(IIC_MASTER_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Fail if there is already a transfer in progress */
    FSP_ERROR_RETURN(((0 == p_ctrl->remain) && (false == p_ctrl->restart)), FSP_ERR_IN_USE);
#endif

    /* Sets the address of the slave device */
    p_ctrl->slave = slave;

    /* Sets the mode of addressing */
    p_ctrl->addr_mode = addr_mode;

    return err;
}

/*******************************************************************************************************************//**
 * Updates the user callback and has option of providing memory for callback structure.
 * Implements i2c_master_api_t::callbackSet
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t R_IIC_MASTER_CallbackSet (i2c_master_ctrl_t * const          p_api_ctrl,
                                    void (                           * p_callback)(i2c_master_callback_args_t *),
                                    void * const                       p_context,
                                    i2c_master_callback_args_t * const p_callback_memory)
{
    iic_master_instance_ctrl_t * p_ctrl = (iic_master_instance_ctrl_t *) p_api_ctrl;

#if (IIC_MASTER_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(IIC_MASTER_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if IIC_MASTER_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    i2c_master_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                             CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context */
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
 * @retval     FSP_SUCCESS                   Status stored in p_status.
 * @retval     FSP_ERR_ASSERTION             NULL pointer.
 **********************************************************************************************************************/
fsp_err_t R_IIC_MASTER_StatusGet (i2c_master_ctrl_t * const p_api_ctrl, i2c_master_status_t * p_status)
{
    iic_master_instance_ctrl_t * p_ctrl = (iic_master_instance_ctrl_t *) p_api_ctrl;

#if IIC_MASTER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ASSERT(p_status != NULL);
#endif

    p_status->open = (IIC_MASTER_OPEN == p_ctrl->open);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Closes the I2C device. May power down IIC peripheral.
 * This function will safely terminate any in-progress I2C transfers.
 *
 * @retval  FSP_SUCCESS         Device closed without issue.
 * @retval  FSP_ERR_ASSERTION   p_api_ctrl is NULL.
 * @retval  FSP_ERR_NOT_OPEN    Handle is not initialized.  Call R_IIC_MASTER_Open to initialize the control block.
 *
 * @note A callback will not be invoked in case an in-progress transfer gets aborted by calling this API.
 **********************************************************************************************************************/
fsp_err_t R_IIC_MASTER_Close (i2c_master_ctrl_t * const p_api_ctrl)
{
    iic_master_instance_ctrl_t * p_ctrl = (iic_master_instance_ctrl_t *) p_api_ctrl;

#if IIC_MASTER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ERROR_RETURN(IIC_MASTER_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Abort an in-progress transfer with this device only */
    iic_master_abort_seq_master(p_ctrl, true);

    /* Disable I2C interrupts. Described in hardware manual (see Section 36.2.8
     * 'I2C Bus Interrupt Enable Register (ICIER)' of the RA6M3 manual R01UH0886EJ0100). */
    p_ctrl->p_reg->ICIER = 0x00;

    /* The device is now considered closed */
    p_ctrl->open = 0U;

#if IIC_MASTER_CFG_DTC_ENABLE

    /* Close the handles for the transfer interfaces */
    if (NULL != p_ctrl->p_cfg->p_transfer_rx)
    {
        p_ctrl->p_cfg->p_transfer_rx->p_api->close(p_ctrl->p_cfg->p_transfer_rx->p_ctrl);
    }

    if (NULL != p_ctrl->p_cfg->p_transfer_tx)
    {
        p_ctrl->p_cfg->p_transfer_tx->p_api->close(p_ctrl->p_cfg->p_transfer_tx->p_ctrl);
    }
#endif

    R_BSP_IrqDisable(p_ctrl->p_cfg->eri_irq);
    R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);
    R_BSP_IrqDisable(p_ctrl->p_cfg->tei_irq);
    R_BSP_IrqDisable(p_ctrl->p_cfg->txi_irq);

    R_BSP_MODULE_STOP(FSP_IP_IIC, p_ctrl->p_cfg->channel);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup IIC_MASTER)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Helper function for handling I2C Read or Write.
 *
 * @param      p_api_ctrl      Pointer to control block
 * @param      p_buffer        Pointer to the buffer to store read/write data.
 * @param[in]  bytes           Number of bytes to be read/written.
 * @param[in]  direction       Read or Write
 *
 * @retval  FSP_SUCCESS           Function executed successfully.
 * @retval  FSP_ERR_ASSERTION     p_api_ctrl or p_buffer is NULL.
 * @retval  FSP_ERR_INVALID_SIZE  Provided number of bytes more than UINT16_MAX(= 65535) while DTC is used
 *                                for data transfer.
 * @retval  FSP_ERR_IN_USE        Another transfer was in progress.
 * @retval  FSP_ERR_NOT_OPEN      Handle is not initialized. Call R_IIC_MASTER_Open to initialize the control block.
 **********************************************************************************************************************/
static fsp_err_t iic_master_read_write (i2c_master_ctrl_t * const p_api_ctrl,
                                        uint8_t * const           p_buffer,
                                        uint32_t const            bytes,
                                        iic_master_transfer_dir_t direction)
{
    iic_master_instance_ctrl_t * p_ctrl = (iic_master_instance_ctrl_t *) p_api_ctrl;

#if IIC_MASTER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_buffer != NULL);
    FSP_ERROR_RETURN((p_ctrl->open == IIC_MASTER_OPEN), FSP_ERR_NOT_OPEN);
    FSP_ASSERT(((iic_master_instance_ctrl_t *) p_api_ctrl)->p_callback != NULL);
 #if IIC_MASTER_CFG_DTC_ENABLE

    /* DTC on RX could actually receive 65535+3 = 65538 bytes as 3 bytes are handled separately.
     * Forcing to 65535 to keep TX and RX uniform with respect to max transaction length via DTC.
     */
    FSP_ERROR_RETURN((bytes <= UINT16_MAX), FSP_ERR_INVALID_SIZE);
 #endif
#endif

    fsp_err_t err = FSP_SUCCESS;

    p_ctrl->p_buff = p_buffer;
    p_ctrl->total  = bytes;

    /* Handle the (different) addressing mode(s) */
    if (p_ctrl->addr_mode == I2C_MASTER_ADDR_MODE_7BIT)
    {
        /* Set the address bytes according to a 7-bit slave read command */
        p_ctrl->addr_high  = 0U;
        p_ctrl->addr_low   = (uint8_t) ((p_ctrl->slave << 1U) | (uint8_t) direction);
        p_ctrl->addr_total = 1U;
    }

#if IIC_MASTER_CFG_ADDR_MODE_10_BIT_ENABLE
    else
    {
        /* Set the address bytes according to a 10-bit slave read command */
        p_ctrl->addr_high = (uint8_t) (((p_ctrl->slave >> 7U) | I2C_CODE_10BIT) & (uint8_t) ~(I2C_CODE_READ));
        p_ctrl->addr_low  = (uint8_t) p_ctrl->slave;

        /* Addr total = 3 for Read and 2 for Write.
         * See Section 36.3.1 "Communication Data Format" of the RA6M3 manual R01UH0886EJ0100
         */
        p_ctrl->addr_total = (uint8_t) ((uint8_t) direction + IIC_MASTER_SLAVE_10_BIT_ADDR_LEN_ADJUST);
    }
#endif

    p_ctrl->read = (bool) direction;

    /* Kickoff the read operation as a master */
    err = iic_master_run_hw_master(p_ctrl);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Single point for managing the logic around notifying a transfer has finished.
 *
 * @param[in]       p_ctrl      Pointer to transfer that is ending.
 * @param[in]       event       The event code to pass to the callback.
 **********************************************************************************************************************/
static void iic_master_notify (iic_master_instance_ctrl_t * const p_ctrl, i2c_master_event_t const event)
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

#if IIC_MASTER_CFG_DTC_ENABLE

    /* Stop any DTC assisted transfer for tx */
    const transfer_instance_t * p_transfer_tx = p_ctrl->p_cfg->p_transfer_tx;
    if ((NULL != p_transfer_tx) && (!p_ctrl->read))
    {
        p_transfer_tx->p_api->disable(p_transfer_tx->p_ctrl);
    }

    /* Stop any DTC assisted transfer for rx */
    const transfer_instance_t * p_transfer_rx = p_ctrl->p_cfg->p_transfer_rx;
    if ((NULL != p_transfer_rx) && (p_ctrl->read))
    {
        p_transfer_rx->p_api->disable(p_transfer_rx->p_ctrl);
    }
#endif

    /* Now do the callback here */
#if BSP_TZ_SECURE_BUILD

    /* p_callback can point to a secure function or a non-secure function. */
    if (!cmse_is_nsfptr(p_ctrl->p_callback))
    {
        /* If p_callback is secure, then the project does not need to change security state. */
        p_ctrl->p_callback(p_args);
    }
    else
    {
        /* If p_callback is Non-secure, then the project must change to Non-secure state in order to call the callback. */
        iic_master_prv_ns_callback p_callback = (iic_master_prv_ns_callback) (p_ctrl->p_callback);
        p_callback(p_args);
    }

#else

    /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the callback. */
    p_ctrl->p_callback(p_args);
#endif

    if (NULL != p_ctrl->p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_ctrl->p_callback_memory = args;
    }

    /* Clear the err flags */
    p_ctrl->err = false;
}

/*******************************************************************************************************************//**
 * Single point for managing the logic around aborting a transfer when operating as a master.
 *
 * @param[in]       p_ctrl  Pointer to control structure of specific device.
 * @param[in]       iic_reset  Flag to enable IIC reset
 **********************************************************************************************************************/
static void iic_master_abort_seq_master (iic_master_instance_ctrl_t * const p_ctrl, bool iic_reset)
{
    /* Safely stop the hardware from operating. */

    /* Reset the peripheral */
    if (true == iic_reset)
    {
        /* Disable channel interrupts */
        p_ctrl->p_reg->ICIER = 0x00;

        /* This helper function would do a full IIC reset
         * followed by re-initializing the required peripheral registers. */
        iic_master_open_hw_master(p_ctrl, p_ctrl->p_cfg);
    }

    /* Update the transfer descriptor to show no longer in-progress and an error */
    p_ctrl->remain = 0U;

    /* Update the transfer descriptor to make sure interrupts no longer process */
    p_ctrl->addr_loaded = p_ctrl->addr_total;
    p_ctrl->loaded      = p_ctrl->total;
    p_ctrl->restarted   = false;
    p_ctrl->restart     = false;

    /* Enable Interrupts: TMOIE, ALIE, NAKIE, RIE, TIE.
     * Disable Interrupt: TEIE, STIE, SPIE
     * (see Section 36.2.8 'I2C Bus Interrupt Enable Register (ICIER)' of the RA6M3 manual R01UH0886EJ0100).
     */
    p_ctrl->p_reg->ICIER = IIC_MASTER_INTERRUPT_ENABLE_INIT_MASK;
}

/*******************************************************************************************************************//**
 * Performs the hardware initialization sequence when operating as a master (see Section 36.3.2
 * 'Initial Settings' of the RA6M3 manual R01UH0886EJ0100).
 *
 * @param[in]  p_ctrl                Pointer to IIC specific control structure
 * @param[in]  p_cfg                 Pointer to IIC specific configuration structure.
 **********************************************************************************************************************/
static void iic_master_open_hw_master (iic_master_instance_ctrl_t * const p_ctrl, i2c_master_cfg_t const * const p_cfg)
{
    /* Perform IIC reset */
    p_ctrl->p_reg->ICCR1 = (uint8_t) IIC_MASTER_PRV_SCL_SDA_NOT_DRIVEN;

    /* Reset */
    p_ctrl->p_reg->ICCR1 = (uint8_t) (IIC_MASTER_ICCR1_IICRST_BIT_MASK | IIC_MASTER_PRV_SCL_SDA_NOT_DRIVEN);

    /* Come out of IIC reset to internal reset */
    p_ctrl->p_reg->ICCR1 =
        (uint8_t) (IIC_MASTER_ICCR1_ICE_BIT_MASK | IIC_MASTER_ICCR1_IICRST_BIT_MASK |
                   IIC_MASTER_PRV_SCL_SDA_NOT_DRIVEN);

    /* Configure the clock settings. This is set in the configuration structure by the tooling. */
    /* Set the number of counts that the clock remains low, bit 7 to 5 should be written as 1 */
    p_ctrl->p_reg->ICBRL =
        (uint8_t) (IIC_MASTER_BUS_RATE_REG_RESERVED_BITS |
                   ((iic_master_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->clock_settings.brl_value);

    /* Set the number of counts that the clock remains high, bit 7 to 5 should be written as 1 */
    p_ctrl->p_reg->ICBRH = (uint8_t) (IIC_MASTER_BUS_RATE_REG_RESERVED_BITS |
                                      ((iic_master_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->clock_settings.brh_value);

    /* Set the internal reference clock source for generating IIC clock */
    p_ctrl->p_reg->ICMR1 = (uint8_t) (IIC_MASTER_BUS_MODE_REGISTER_1_MASK |
                                      (uint8_t) ((((iic_master_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->
                                                  clock_settings.
                                                  cks_value &
                                                  IIC_MASTER_INTERNAL_REF_CLOCK_SELECT_MAX) << 4U));

    /* Allow timeouts to be generated on the low value of SCL using either long or short mode */

    /* TMOL 'Timeout L Count Control' and TMOH 'Timeout H Count Control' will be set at the time of I2C reset.
     * This will enable time out detection for both SCLn high and low.
     * Only Set/Clear TMOS here to select long or short mode.
     * (see Section 36.2.4 'I2C Bus Mode Register 2 (ICMR2)' of the RA6M3 manual R01UH0886EJ0100).
     */
    p_ctrl->p_reg->ICMR2 = (uint8_t) (IIC_MASTER_BUS_MODE_REGISTER_2_MASK |
                                      (uint8_t) (IIC_MASTER_TIMEOUT_MODE_SHORT ==
                                                 ((iic_master_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->timeout_mode)
                                      |
                                      (uint8_t) (((iic_master_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->
                                                 timeout_scl_low << R_IIC0_ICMR2_TMOL_Pos));

    /* ICFER Register Settings:
     * 1. Enable timeout function.
     * 2. Enable master arbitration loss detection.
     * 3. Enable NACK arbitration loss detection.
     * 4. Disable Slave arbitration loss detection.
     * 5. Enable NACK reception transfer suspension.
     * 6. Use the digital noise filter circuit. Upon I2C reset, 'NF[1:0] Noise Filter Stage Select' will be set to 0x00
     * This would imply  'Filter out noise of up to 1 IIC cycle (single-stage filter)'
     * (see Section 36.2.5 'I2C Bus Mode Register 3 (ICMR3)' of the RA6M3 manual R01UH0886EJ0100)
     * 7. Do not use the SCL synchronous circuit.
     * 8. Enable FM+ slope circuit if fast mode plus is enabled.
     * (see Section 36.2.6 'I2C Bus Function Enable Register' of the RA6M3 manual R01UH0886EJ0100 for more details)
     */
    p_ctrl->p_reg->ICFER =
        (uint8_t) ((uint8_t) (I2C_MASTER_RATE_FASTPLUS ==
                              p_ctrl->p_cfg->rate) << 7U) | IIC_MASTER_FUNCTION_ENABLE_INIT_SETTINGS;

    /* Ensure the HW is in master mode and does not behave as a slave to another master on the same channel. */
    p_ctrl->p_reg->ICSER = 0x00;

    /* Enable Interrupts: TMOIE, ALIE, NAKIE, RIE, TIE.
     * Disable Interrupt: TEIE, STIE, SPIE
     * (see Section 36.2.8 'I2C Bus Interrupt Enable Register (ICIER)' of the RA6M3 manual R01UH0886EJ0100).
     */
    p_ctrl->p_reg->ICIER = IIC_MASTER_INTERRUPT_ENABLE_INIT_MASK;

    /* Set valid interrupt contexts and user provided priority. Enable the interrupts at the NVIC  */
    R_BSP_IrqCfgEnable(p_cfg->eri_irq, p_cfg->ipl, p_ctrl);
    R_BSP_IrqCfgEnable(p_cfg->txi_irq, p_cfg->ipl, p_ctrl);
    R_BSP_IrqCfgEnable(p_cfg->tei_irq, p_cfg->ipl, p_ctrl);
    R_BSP_IrqCfgEnable(p_cfg->rxi_irq, p_cfg->ipl, p_ctrl);

    /* Release IIC from internal reset */

    /* Reset */
    p_ctrl->p_reg->ICCR1 = (uint8_t) (IIC_MASTER_ICCR1_ICE_BIT_MASK | IIC_MASTER_PRV_SCL_SDA_NOT_DRIVEN);
}

/*******************************************************************************************************************//**
 * Performs the data transfer described by the parameters when operating as a master.
 * See 36.3.3 "Master Transmit Operation" and section 36.3.4 "Master Receive Operation"
 * of the RA6M3 manual R01UH0886EJ0100
 *
 * @param[in]       p_ctrl  Pointer to control structure of specific device.
 *
 * @retval  FSP_SUCCESS             Data transfer success.
 * @retval  FSP_ERR_IN_USE          If data transfer is in progress.
 **********************************************************************************************************************/
static fsp_err_t iic_master_run_hw_master (iic_master_instance_ctrl_t * const p_ctrl)
{
    /* IICn operates using PCLKB. The ratio ICLK (System Clock)/PCLKB gives the CPU cycles for 1 ICBRL count.
     * (ICLK/PCLKB)*ICBRL gives the CPU cycles for entire ICBRL count.
     * Since each time we loop the timeout count will be decremented by 1 this would require at least 4 CPU clocks,
     * making the final timeout count as:
     * Timeout = ((ICLK/PCLKB)*ICBRL)/4.
     */
    volatile uint32_t sysdiccr = FSP_STYPE3_REG8_READ(R_SYSTEM->SCKDIVCR, BSP_CFG_CLOCKS_SECURE);
    sysdiccr &= (IIC_MASTER_SYSDIVCK_ICLK_MASK | IIC_MASTER_SYSDIVCK_PCLKB_MASK);
    uint32_t pclkb         = (IIC_MASTER_SYSDIVCK_PCLKB_MASK & sysdiccr) >> 8U;
    uint32_t iclk          = sysdiccr >> 24U;
    uint32_t timeout_count = ((1U << (pclkb - iclk)) * p_ctrl->p_reg->ICBRL) >> 2U;

    /* Check if this is a new transaction or a continuation */
    if (!p_ctrl->restarted)
    {
        /* As per BBSY clearing conditions in section 36.2.2 of the RA6M3 manual R01UH0886EJ0100,
         * the BBSY bit is 0 after the bus free time (ICBRL setting)
         * if a start condition is not detected after a stop condition detection.
         */
        IIC_MASTER_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->ICCR2_b.BBSY, 0U, timeout_count);

        /* If bus is busy, return error */
        FSP_ERROR_RETURN((0U != timeout_count), FSP_ERR_IN_USE);

        /* This is not a restarted transaction. Enable TXI for the next transfer.
         * This had been disabled at the end of TXI interrupt.
         * The intention is to only enable IIC_MASTER_TXI_EN_BIT.
         * Writing the whole mask - IIC_MASTER_INTERRUPT_ENABLE_INIT_MASK saves cycles.
         */
        p_ctrl->p_reg->ICIER = IIC_MASTER_INTERRUPT_ENABLE_INIT_MASK;
    }

    /* Initialize fields used during transfer */
    p_ctrl->addr_loaded          = 0U;
    p_ctrl->loaded               = 0U;
    p_ctrl->remain               = p_ctrl->total;
    p_ctrl->addr_remain          = p_ctrl->addr_total;
    p_ctrl->err                  = false;
    p_ctrl->dummy_read_completed = false;
    p_ctrl->activation_on_rxi    = false;
    p_ctrl->activation_on_txi    = false;
    p_ctrl->address_restarted    = false;

    /* Allow timeouts to be generated on the low value of SCL using either short or long mode.
     * This gets disabled in case the previous transaction issues a restart.
     */

    /* TMOL 'Timeout L Count Control' and TMOH 'Timeout H Count Control' will be set at the time of I2C reset.
     * This will enable time out detection for both SCLn high and low.
     *
     * Register configuration:
     *  - Set/Clear TMOS here to select long or short mode.
     * (see Section 36.2.4 'I2C Bus Mode Register 2 (ICMR2)' of the RA6M3 manual R01UH0886EJ0100).
     *  - Set SDDL and DLCS. If SMBus is disabled, assign default value.
     */
    iic_master_extended_cfg_t * p_extend = (iic_master_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    p_ctrl->p_reg->ICMR2 = (uint8_t) (IIC_MASTER_BUS_MODE_REGISTER_2_MASK |
                                      (uint8_t) (IIC_MASTER_TIMEOUT_MODE_SHORT == (p_extend->timeout_mode))
                                      |
                                      (uint8_t) (p_extend->timeout_scl_low << R_IIC0_ICMR2_TMOL_Pos)
                                      |
                                      (uint8_t) (p_extend->clock_settings.sddl_value << R_IIC0_ICMR2_SDDL_Pos)
                                      |
                                      (uint8_t) (p_extend->clock_settings.dlcs_value << R_IIC0_ICMR2_DLCS_Pos));

    /* Set the response as ACK */
    p_ctrl->p_reg->ICMR3_b.ACKWP = 1;  /* Write Enable */
    p_ctrl->p_reg->ICMR3_b.ACKBT = 0;  /* Write */
    p_ctrl->p_reg->ICMR3_b.ACKWP = 0;

    /* Enable SMBus communication for I2C module if requested */
    p_ctrl->p_reg->ICMR3_b.SMBS = p_extend->smbus_operation;

    /* Enable timeout function */
    p_ctrl->p_reg->ICFER_b.TMOE = 1U;

    /* Enable TXI. This is treated differently to support restart functionality.
     * In case the previous IIC master transaction enabled restart, the queued TXI will fire a this point.
     *
     * The TXI had been NVIC-disabled (but Peripheral enabled) before setting the
     * RS bit by the previous restart enabled transaction.
     * The RS bit mimics a "stop" followed by a "start" and keeps the bus busy.
     * As a part of the previous transaction, TXI fires at the peripheral level and is queued at the CPU.
     *
     * If the previous transaction was not restart enabled -
     * NVIC-enable TXI which will fire after the start condition below.
     */
    NVIC_EnableIRQ(p_ctrl->p_cfg->txi_irq);

    /* Enable SPIE to detect unexpected STOP condition. This is disabled between communication events as it can lead
     * to undesired interrupts in multi-master setups. */
    p_ctrl->p_reg->ICIER = IIC_MASTER_INTERRUPT_ENABLE_INIT_MASK | R_IIC0_ICIER_STIE_Msk | R_IIC0_ICIER_SPIE_Msk;

    /* If previous transaction did not end with restart, send a start condition */
    if (!p_ctrl->restarted)
    {
        /* Request IIC to issue the start condition */
        p_ctrl->p_reg->ICCR2 = (uint8_t) IIC_MASTER_ICCR2_ST_BIT_MASK;
    }
    else
    {
        p_ctrl->restarted = false;
    }

    /*
     * The Flowchart under 36.3.3 "Master Transmit Operation" and section 36.3.4 "Master Receive Operation"
     * of the RA6M3 manual R01UH0886EJ0100 is covered in the interrupts:
     *
     * 1. NACKF processing is handled in the ERI interrupt.
     *    For receive, dummy reading ICDRR is not required because the NACK processing in this driver resets the IIC peripheral.
     * 2. Data is written to ICDRT in the transmit interrupt (TDRE is set when a transmit interrupt fires).
     * 3. For transmit, stop is issued in the transmit end interrupt (TEND is set when a transmit end interrupt fires).
     * 4. For transmit, ICSR2 is cleared in the transmit end interrupt.
     * 5. For receive, remaining processing including reading ICDRR happens in the receive interrupt (RDRF is set when a receive interrupt fires).
     */
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Handles the receive data full interrupt when operating as a master.
 *
 * @param[in]       p_ctrl     The target IIC block's control block.
 **********************************************************************************************************************/
static void iic_master_rxi_master (iic_master_instance_ctrl_t * p_ctrl)
{
    volatile uint8_t dummy_read;

    /* First receive interrupt: Handle the special case of 1 or 2 byte read here */
    if (false == p_ctrl->dummy_read_completed)
    {
        /* Enable WAIT for 1 or 2 byte read */
        if (2U >= p_ctrl->total)
        {
            p_ctrl->p_reg->ICMR3_b.WAIT = 1;
        }

        /* Enable NACK for 1 byte read */
        if (1U == p_ctrl->remain)
        {
            /* Writes to be done separately.
             * See Note 1 in Section 36.2.5 'I2C Bus Mode Register 3 (ICMR3)' of the RA6M3 manual R01UH0886EJ0100
             */
            p_ctrl->p_reg->ICMR3_b.ACKWP = 1; /* Write enable ACKBT */
            p_ctrl->p_reg->ICMR3_b.ACKBT = 1;
            p_ctrl->p_reg->ICMR3_b.ACKWP = 0;
        }

#if IIC_MASTER_CFG_DTC_ENABLE
        uint8_t volatile const * p_iic_master_rx_buffer = &(p_ctrl->p_reg->ICDRR);

        /* Enable transfer support if possible */
        if ((NULL != p_ctrl->p_cfg->p_transfer_rx) && (p_ctrl->read) && (p_ctrl->total > 3U))
        {
            p_ctrl->p_cfg->p_transfer_rx->p_api->reset(p_ctrl->p_cfg->p_transfer_rx->p_ctrl,
                                                       (uint8_t *) (p_iic_master_rx_buffer),
                                                       (void *) (p_ctrl->p_buff),
                                                       (uint16_t) (p_ctrl->total - 3U));

            p_ctrl->remain            = 3U;
            p_ctrl->loaded            = p_ctrl->total - 3U;
            p_ctrl->activation_on_rxi = true;
        }
#endif
        if (((iic_master_extended_cfg_t *) (p_ctrl->p_cfg->p_extend))->smbus_operation)
        {
            iic_master_notify(p_ctrl, I2C_MASTER_EVENT_BYTE_ACK);
        }

        /* Do a dummy read to clock the data into the ICDRR. */
        dummy_read = p_ctrl->p_reg->ICDRR;
        FSP_PARAMETER_NOT_USED(dummy_read);

        /* Update the counter */
        p_ctrl->dummy_read_completed = true;
    }

#if IIC_MASTER_CFG_DTC_ENABLE

    /* If this is the interrupt that got fired after DTC transfer,
     * ignore it as the DTC has already taken care of the data transfer */
    else if (true == p_ctrl->activation_on_rxi)
    {
        p_ctrl->activation_on_rxi = false;
    }
#endif

    /* ICDRR contain valid received data */
    else if (0U < p_ctrl->remain)
    {
        if (((iic_master_extended_cfg_t *) (p_ctrl->p_cfg->p_extend))->smbus_operation)
        {
            iic_master_notify(p_ctrl, I2C_MASTER_EVENT_BYTE_ACK);
        }

        iic_master_rxi_read_data(p_ctrl);
    }
    else
    {
        /* Do nothing */
    }
}

/*******************************************************************************************************************//**
 * Handles the transmit data empty interrupt when operating as a master.
 *
 * @param[in]       p_ctrl     The target IIC block's control block.
 **********************************************************************************************************************/
static void iic_master_txi_master (iic_master_instance_ctrl_t * p_ctrl)
{
    uint32_t timeout_count = IIC_MASTER_PERIPHERAL_REG_MAX_WAIT;

    /* Check if we are issuing the slave address */
    if (0U < p_ctrl->addr_remain)
    {
        iic_master_txi_send_address(p_ctrl);
    }
    else if (!p_ctrl->read)
    {
        /* If previous event is an error event and this TXI is triggered by ERI, do not invoke SMBus callback. Because
         * the internal function which used to issue callback will clear the error flag in the control block and cause
         * incorrect behavior at ERI event after this TXI.
         *
         * Number of loaded byte must larger or equal to 1 because it helps to ensure that SMBus callback only be invoked
         * after slave addess already transmitted (omit first 2 TDRE raise event).
         */
        if ((((iic_master_extended_cfg_t *) (p_ctrl->p_cfg->p_extend))->smbus_operation) &&
            ((!p_ctrl->err) && (0U < p_ctrl->loaded)))
        {
            iic_master_notify(p_ctrl, I2C_MASTER_EVENT_BYTE_ACK);
        }

#if IIC_MASTER_CFG_DTC_ENABLE

        /* If this is the interrupt that got fired after DTC transfer,
         * ignore it as the DTC has already taken care of the data transfer */
        if (true == p_ctrl->activation_on_txi)
        {
            p_ctrl->activation_on_txi = false;
        }
        else if (p_ctrl->remain > 0U)
#else
        if (p_ctrl->remain > 0U)
#endif
        {
            /* Write the data to ICDRT register */
            p_ctrl->p_reg->ICDRT = p_ctrl->p_buff[p_ctrl->loaded];

            /* Update the number of bytes remaining for next pass */
            p_ctrl->loaded++;
            p_ctrl->remain--;
        }
        else
        {
            /* Do nothing */
        }

        /* We are done loading ICDRT, wait for TEND to send a stop/restart */
        if (0U == p_ctrl->remain)
        {
            /* Disable the Transmit Data Empty Interrupt. */
            p_ctrl->p_reg->ICIER_b.TIE = 0U;

            /* Wait for the value to reflect at the peripheral.
             * See 'Note' under Table 36.10 "Interrupt sources" of the RA6M3 manual R01UH0886EJ0100 */
            IIC_MASTER_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->ICIER_b.TIE, 0U, timeout_count);

            /* Enable the transmit end IRQ, to issue a STOP or RESTART */
            /* Clear any pending TEND interrupts */
            R_BSP_IrqStatusClear(p_ctrl->p_cfg->tei_irq);
            NVIC_ClearPendingIRQ(p_ctrl->p_cfg->tei_irq);

            /* Enable the TXEND interrupt */
            p_ctrl->p_reg->ICIER_b.TEIE = 1U;

            /* No need to wait to check TEIE has actually become 1U; because if that's not the case,
             * no other operation can occur at this point */
        }
    }
    else
    {
        /* Do nothing */
    }
}

/*******************************************************************************************************************//**
 * Handles the transmit end interrupt when operating as a master.
 * @note This interrupt is configured to be generated at the end of last byte of the requested transfer.
 *
 * @param[in]       p_ctrl     The target IIC block's control block.
 **********************************************************************************************************************/
static void iic_master_tei_master (iic_master_instance_ctrl_t * p_ctrl)
{
    uint32_t timeout_count = IIC_MASTER_PERIPHERAL_REG_MAX_WAIT;

    if (((iic_master_extended_cfg_t *) (p_ctrl->p_cfg->p_extend))->smbus_operation)
    {
        iic_master_notify(p_ctrl, I2C_MASTER_EVENT_BYTE_ACK);
    }

    /* This is a 10 bit address read, issue a restart prior to the last address byte transmission  */
    if ((p_ctrl->read) && (p_ctrl->addr_remain == 1U) && (false == p_ctrl->address_restarted))
    {
#if IIC_MASTER_CFG_ADDR_MODE_10_BIT_ENABLE

        /* Enable TXI so that it fires after restart condition. */
        p_ctrl->p_reg->ICIER_b.TIE = 1U;

        /* Request IIC to issue the restart condition */
        p_ctrl->p_reg->ICCR2      = (uint8_t) IIC_MASTER_ICCR2_RS_BIT_MASK;
        p_ctrl->address_restarted = true;
#endif
    }
    /* We are done with the transfer, send STOP or RESTART */
    else if (0U == p_ctrl->remain)
    {
        /* Send RESTART */
        if (p_ctrl->restart)
        {
            /* NOTE:Only disable in NVIC, disabling in I2C would cause the
             * restart condition to fail because we are using the buffered
             * interrupt to start the next sequence */
            R_BSP_IrqDisable(p_ctrl->p_cfg->txi_irq);
            p_ctrl->p_reg->ICIER_b.TIE = 1U;

            /* Request IIC to issue the restart condition. At this point we will queue a TXI at the NVIC level. */
            p_ctrl->p_reg->ICCR2 = (uint8_t) IIC_MASTER_ICCR2_RS_BIT_MASK;

            /* Disable timeout function */
            p_ctrl->p_reg->ICFER_b.TMOE = 0;

            /* Remember that we issued a restart for the next transfer */
            p_ctrl->restarted = true;
        }
        /* Send STOP */
        else
        {
            /* Clear STOP flag and set SP.
             * It is ok to clear other status' as this transaction is over.
             */
            p_ctrl->p_reg->ICSR2 &= (uint8_t) ~(IIC_MASTER_ICSR2_STOP_BIT);

            /* Request IIC to issue the stop condition */
            p_ctrl->p_reg->ICCR2 = (uint8_t) IIC_MASTER_ICCR2_SP_BIT_MASK; /* It is safe to write 0's to other bits. */
        }
    }
    else
    {
        /* Do nothing */
    }

    /* Disable the interrupt as we are done with the transfer */
    p_ctrl->p_reg->ICIER_b.TEIE = 0U;

    /* Wait for the value to reflect at the peripheral.
     * See 'Note' under Table 36.10 "Interrupt sources" of the RA6M3 manual R01UH0886EJ0100 */
    IIC_MASTER_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->ICIER_b.TEIE, 0U, timeout_count);
}

/*******************************************************************************************************************//**
 * Handles the error interrupts when operating as a master.
 *
 * @param[in]       p_ctrl  Pointer to transfer control block
 **********************************************************************************************************************/
static void iic_master_err_master (iic_master_instance_ctrl_t * p_ctrl)
{
    /* Clear all the event flags except the receive data full, transmit end and transmit data empty flags*/
    uint8_t errs_events = IIC_MASTER_STATUS_REGISTER_2_ERR_MASK & p_ctrl->p_reg->ICSR2;
    p_ctrl->p_reg->ICSR2 &= (uint8_t) ~IIC_MASTER_STATUS_REGISTER_2_ERR_MASK;

    /* If the event was an error event, then handle it */
    if ((errs_events &
         (uint8_t) ((uint8_t) (IIC_MASTER_ERR_EVENT_TIMEOUT) | (uint8_t) (IIC_MASTER_ERR_EVENT_ARBITRATION_LOSS))) |
        ((errs_events & (uint8_t) (IIC_MASTER_ERR_EVENT_NACK)) && (1U != p_ctrl->p_reg->ICCR2_b.MST)))
    {
        /* Conditions to get here:
         * 1. This is Timeout and/or arbitration loss error during an ongoing transaction
         * 2. This is a NACK error and this device is no longer the active master on the bus.
         *    The MST bit here can get cleared:
         *     a. In case of an arbitration loss error.also occurs.
         *     b. If the slave timeout is lesser than master timeout and the slave releases
         *        the bus by performing an internal reset.
         *        Refer Section "I2C Bus Control Register 2 (ICCR2) - Clearing conditions for MST"
         *        of the RA6M3 manual R01UH0886EJ0100
         * 3. This is a Timeout error after attempting to issue a stop after detecting a NACK previously.
         *//* Set the error flag when an error event occurred */
        p_ctrl->err = true;

        /* Abort an in-progress transfer with the current device */
        iic_master_abort_seq_master(p_ctrl, true); /* This will reset the IIC Master driver */
        /* Notify anyone waiting that the transfer is Aborted due to error. */
        iic_master_notify(p_ctrl, I2C_MASTER_EVENT_ABORTED);
    }
    else if ((errs_events & (uint8_t) (IIC_MASTER_ERR_EVENT_NACK)) && (1U == p_ctrl->p_reg->ICCR2_b.MST))
    {
        /* MST bit must be set to issue a stop condition.
         * Refer Section "36.11.3 Issuing a Stop Condition" of the RA6M3 manual R01UH0886EJ0100
         */

        /* Set the error flag when an error event occurred
         * This will be checked after the stop condition is detected from the request below. */
        p_ctrl->err = true;

        /* The sequence below is to handle a NACK received from slave in the middle of a write.
         * See item '[4]' under 'Figure 36.6 Example master transmission flow' of the RA6M3 manual R01UH0886EJ0100 */

        /* Request IIC to issue the stop condition */
        p_ctrl->p_reg->ICCR2 = (uint8_t) IIC_MASTER_ICCR2_SP_BIT_MASK; /* It is safe to write 0's to other bits. */

        /* Allow timeouts to be generated on the low value of SCL using either long or short mode and re-assign value
         * of SDDL and DLCS. */
        p_ctrl->p_reg->ICMR2 = (uint8_t) 0x02U |
                               (uint8_t) (((iic_master_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->timeout_mode) |
                               (uint8_t) (((iic_master_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->
                                          clock_settings.sddl_value << R_IIC0_ICMR2_SDDL_Pos)
                               |
                               (uint8_t) (((iic_master_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->
                                          clock_settings.dlcs_value << R_IIC0_ICMR2_DLCS_Pos);
        p_ctrl->p_reg->ICFER_b.TMOE = 1;

        /* This interrupt will be fired again when wither stop condition is sent
         * or the hardware detects the line is stuck low causing a timeout */
    }
    /* This is a STOP, START or RESTART event. We need to process these events only at the
     * end of the requisite transfers.
     * NOTE: Do not use p_transfer->loaded or p_transfer->remain to check whether the transfer is
     * completed, since using them would lead to a race condition between txi and eri interrupts in case
     * of one byte transfer which will result in BUS arbitration loss error */
    else if ((errs_events & (uint8_t) IIC_MASTER_ERR_EVENT_STOP) ||
             ((p_ctrl->restarted) && (errs_events & (uint8_t) IIC_MASTER_ERR_EVENT_START)))
    {
        i2c_master_event_t event = I2C_MASTER_EVENT_ABORTED;
        if (false == p_ctrl->err)      /* Successful transaction */
        {
            /* Get the correct event to notify the user */
            event = (p_ctrl->read) ? I2C_MASTER_EVENT_RX_COMPLETE : I2C_MASTER_EVENT_TX_COMPLETE;

            /* Disable STIE/SPIE to prevent errant interrupts in multi-master scenarios */
            p_ctrl->p_reg->ICIER = IIC_MASTER_INTERRUPT_ENABLE_INIT_MASK;
        }
        else if ((errs_events & (uint8_t) IIC_MASTER_ERR_EVENT_STOP))
        {
            /* This is the STOP condition requested due to a NACK error earlier.
             * Since the stop condition is successfully issued there is no need to reset the driver.
             */
            iic_master_abort_seq_master(p_ctrl, false); /* Clear the transaction flags only */
        }
        else
        {
            /* Do nothing */
        }

        /* Notify anyone waiting */
        iic_master_notify(p_ctrl, event);
    }
    else if (errs_events & (uint8_t) IIC_MASTER_ERR_EVENT_START)
    {
        if (((iic_master_extended_cfg_t *) (p_ctrl->p_cfg->p_extend))->smbus_operation)
        {
            iic_master_notify(p_ctrl, I2C_MASTER_EVENT_START);
        }
    }
    else
    {
        /* Do nothing */
    }
}

/*******************************************************************************************************************//**
 * Check valid receive data and set WAIT, NACK and STOP/RESTART bit in RXI handler.
 *
 * @param[in]       p_ctrl  Pointer to transfer control block
 **********************************************************************************************************************/
static void iic_master_rxi_read_data (iic_master_instance_ctrl_t * const p_ctrl)
{
    /* If next data = (final byte - 2), enable WAIT */
    if (3U == p_ctrl->remain)
    {
        p_ctrl->p_reg->ICMR3_b.WAIT = 1;
    }
    /* If next data = (final byte - 1), enable NACK  */
    else if (2U == p_ctrl->remain)
    {
        /* Writes to be done separately.
         * See Note 1 in Section 36.2.5 'I2C Bus Mode Register 3 (ICMR3)' of the RA6M3 manual R01UH0886EJ0100
         */
        p_ctrl->p_reg->ICMR3_b.ACKWP = 1; /* Write enable ACKBT */
        p_ctrl->p_reg->ICMR3_b.ACKBT = 1;
        p_ctrl->p_reg->ICMR3_b.ACKWP = 0;
    }
    /* If next data = final byte, send STOP or RESTART */
    else if (1U == p_ctrl->remain)
    {
        if (p_ctrl->restart)
        {
            /* NOTE:Only disable in NVIC, disabling in I2C would cause the
             * restart condition to fail because we are using the buffered
             * interrupt to start the next sequence */
            R_BSP_IrqDisable(p_ctrl->p_cfg->txi_irq);
            p_ctrl->p_reg->ICIER_b.TIE = 1U;

            p_ctrl->p_reg->ICMR3_b.ACKWP = 1; /* Write enable ACKBT */

            /* This bit clears to 0 automatically by issuing stop condition.
             * For restart condition, clear bit by software.
             */
            p_ctrl->p_reg->ICMR3_b.ACKBT = 0;
            p_ctrl->p_reg->ICMR3_b.ACKWP = 0;

            /* Request IIC to issue the restart condition */
            p_ctrl->p_reg->ICCR2 = (uint8_t) IIC_MASTER_ICCR2_RS_BIT_MASK;

            /* Disable timeout function */
            p_ctrl->p_reg->ICFER_b.TMOE = 0;

            /* Remember that we issued a restart when doing the next transfer */
            p_ctrl->restarted = true;
        }
        else
        {
            /* Clear STOP flag and set SP.
             * It is ok to clear other status' as this transaction is over.
             */
            p_ctrl->p_reg->ICSR2 &= (uint8_t) ~(IIC_MASTER_ICSR2_STOP_BIT);

            /* Request IIC to issue the stop condition */
            p_ctrl->p_reg->ICCR2 = (uint8_t) IIC_MASTER_ICCR2_SP_BIT_MASK; /* It is safe to write 0's to other bits. */

            /* STOP flag will not be set just yet. STOP will be set only after reading the last byte from ICDRR and clearing the WAIT.
             * See Point #7 under '36.3.4 Master Receive Operation' of the RA6M3 manual R01UH0886EJ0100.
             */
        }
    }
    else
    {
        /* Do nothing */
    }

    p_ctrl->p_buff[p_ctrl->loaded] = p_ctrl->p_reg->ICDRR;

    /* Update the counter values */
    p_ctrl->loaded++;
    p_ctrl->remain--;

    /* If we are done with the reception, clear the WAIT bit */
    if (0U == p_ctrl->remain)
    {
        p_ctrl->p_reg->ICMR3_b.WAIT = 0;

        /* If this transaction does not have the restart flag set to true,
         * last byte has been read and WAIT has been cleared.
         * Callback will be issued by the ERI once the stop condition is detected
         * In case of restart flag set to true a callback will be issued by the ERI once the start
         * (from restart) condition is detected
         */
    }
}

/*******************************************************************************************************************//**
 * Write the address byte to the iic bus
 *
 * @param[in]       p_ctrl  Pointer to transfer control block
 **********************************************************************************************************************/
static void iic_master_txi_send_address (iic_master_instance_ctrl_t * const p_ctrl)
{
    /* This is a 10 bit read and we have transmitted the low byte, next is restart */
    if ((3U == p_ctrl->addr_total) && (2U == p_ctrl->addr_loaded) && (false == p_ctrl->address_restarted))
    {
#if IIC_MASTER_CFG_ADDR_MODE_10_BIT_ENABLE
        uint32_t timeout_count = IIC_MASTER_PERIPHERAL_REG_MAX_WAIT;

        /* For Read operation an extra address byte needs to be sent after issuing restart.
         * At this point we have sent the first 2 address bytes. Disable TXI.
         */
        p_ctrl->p_reg->ICIER_b.TIE = 0U;

        /* Wait for the value to reflect at the peripheral.
         * See 'Note' under Table 36.10 "Interrupt sources" of the RA6M3 manual R01UH0886EJ0100 */
        IIC_MASTER_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->ICIER_b.TIE, 0U, timeout_count);

        /* Enable the transmit end IRQ, so that we can generate a RESTART condition */
        /* Clear any pending TEND interrupts */
        R_BSP_IrqStatusClear(p_ctrl->p_cfg->tei_irq);
        NVIC_ClearPendingIRQ(p_ctrl->p_cfg->tei_irq);

        /* Enable the TXEND interrupt */
        p_ctrl->p_reg->ICIER_b.TEIE = 1U;

        /* No need to wait to check TEIE has actually become 1U; because if that's not the case,
         * no other operation can occur at this point */
#endif
    }
    else
    {
        /* Address low byte, this could either be a 7 bit address or low byte of 10 bit address */
        uint8_t address_byte = p_ctrl->addr_low;
#if IIC_MASTER_CFG_ADDR_MODE_10_BIT_ENABLE

        /* 10 bit address, handle accordingly */
        if (p_ctrl->addr_total > 1U)
        {
            /* MSB transfer, send address high byte with with R/W set to 0 */
            if (0U == p_ctrl->addr_loaded)
            {
                address_byte = p_ctrl->addr_high;
            }
            /* MSB transfer after restart of 10 bit read, send high byte with R/W set to 1 */
            else if ((2U == p_ctrl->addr_loaded) && (3U == p_ctrl->addr_total))
            {
                address_byte = p_ctrl->addr_high | (uint8_t) I2C_CODE_READ;
            }
            /* Low byte transfer */
            else
            {
                address_byte = p_ctrl->addr_low;
            }
        }
#endif

#if IIC_MASTER_CFG_DTC_ENABLE
        uint8_t volatile const * p_iic_master_tx_buffer = &(p_ctrl->p_reg->ICDRT);

        /* If this is the last address byte, enable transfer */
        if (1U == p_ctrl->addr_remain)
        {
            if ((NULL != p_ctrl->p_cfg->p_transfer_tx) && !(p_ctrl->read) && (p_ctrl->total > 0U))
            {
                p_ctrl->p_cfg->p_transfer_tx->p_api->reset(p_ctrl->p_cfg->p_transfer_tx->p_ctrl,
                                                           (void *) (p_ctrl->p_buff),
                                                           (uint8_t *) (p_iic_master_tx_buffer),
                                                           (uint16_t) (p_ctrl->remain));
                p_ctrl->remain            = 0U;
                p_ctrl->loaded            = p_ctrl->total;
                p_ctrl->activation_on_txi = true;
            }
        }
#endif

        /* Write the address byte */
        p_ctrl->p_reg->ICDRT = address_byte;

        /* Update the number of address bytes loaded for next pass */
        p_ctrl->addr_loaded++;
        p_ctrl->addr_remain--;
    }
}

#if IIC_MASTER_CFG_DTC_ENABLE

/*******************************************************************************************************************//**
 * Configures IIC related transfer drivers (if enabled).
 *
 * @param[in]   p_ctrl    Pointer to IIC specific control structure
 * @param[in]   p_cfg     Pointer to IIC specific configuration structure
 *
 * @retval      FSP_SUCCESS                Transfer interface initialized successfully.
 * @retval      FSP_ERR_ASSERTION          Pointer to transfer instance for I2C receive in p_cfg is NULL.
 **********************************************************************************************************************/
static fsp_err_t iic_master_transfer_open (i2c_master_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;

    if (NULL != p_cfg->p_transfer_rx)
    {
        err = iic_master_transfer_configure(p_cfg->p_transfer_rx, IIC_MASTER_TRANSFER_DIR_READ);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    if (NULL != p_cfg->p_transfer_tx)
    {
        err = iic_master_transfer_configure(p_cfg->p_transfer_tx, IIC_MASTER_TRANSFER_DIR_WRITE);
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
 * Configures  IIC RX related transfer.
 * @param[in]     p_ctrl                     Pointer to IIC specific control structure
 * @param[in]     p_cfg                      Pointer to IIC specific configuration structure
 *
 * @retval        FSP_SUCCESS                Transfer interface is configured with valid parameters.
 * @retval        FSP_ERR_ASSERTION          Pointer to transfer instance for I2C receive in p_cfg is NULL.
 **********************************************************************************************************************/
static fsp_err_t iic_master_transfer_configure (transfer_instance_t const * p_transfer,
                                                iic_master_transfer_dir_t   direction)
{
    fsp_err_t err;

    /* Set default transfer info and open receive transfer module, if enabled. */
 #if (IIC_MASTER_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_transfer->p_api);
    FSP_ASSERT(NULL != p_transfer->p_cfg);
    FSP_ASSERT(NULL != p_transfer->p_cfg->p_info);
 #endif
    transfer_info_t * p_cfg = p_transfer->p_cfg->p_info;
    if (IIC_MASTER_TRANSFER_DIR_READ == direction)
    {
        p_cfg->transfer_settings_word = IIC_MASTER_DTC_RX_TRANSFER_SETTINGS;
    }
    else
    {
        p_cfg->transfer_settings_word = IIC_MASTER_DTC_TX_TRANSFER_SETTINGS;
    }

    err = p_transfer->p_api->open(p_transfer->p_ctrl, p_transfer->p_cfg);
    FSP_ERROR_RETURN((FSP_SUCCESS == err), err);

    return FSP_SUCCESS;
}

#endif

/***********************************************************************************************************************
 * Interrupt Vectors
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Receive data full interrupt routine.
 *
 * This function implements the IIC Receive buffer full ISR routine.
 *
 **********************************************************************************************************************/
void iic_master_rxi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE
    /* Clear the IR flag */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    iic_master_instance_ctrl_t * p_ctrl = (iic_master_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    iic_master_rxi_master(p_ctrl);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * Transmit data empty interrupt routine.
 *
 * This function implements the Transmit buffer empty ISR routine.
 *
 **********************************************************************************************************************/
void iic_master_txi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE
    /* Clear the IR flag */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    iic_master_instance_ctrl_t * p_ctrl = (iic_master_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    iic_master_txi_master(p_ctrl);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * Transmit end interrupt routine.
 *
 * This function implements the IIC Transmission End ISR routine.
 *
 **********************************************************************************************************************/
void iic_master_tei_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    iic_master_instance_ctrl_t * p_ctrl = (iic_master_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    iic_master_tei_master(p_ctrl);

    /* Clear the IR flag */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * Error and event interrupt routine.
 *
 * This function implements the IIC Event/Error.
 *
 **********************************************************************************************************************/
void iic_master_eri_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    iic_master_instance_ctrl_t * p_ctrl = (iic_master_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    iic_master_err_master(p_ctrl);

    /* Clear the IR flag */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}
