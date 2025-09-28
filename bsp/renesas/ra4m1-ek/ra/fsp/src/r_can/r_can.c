/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_can.h"
#include "r_can_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define CAN_OPEN                            (0x5243414EU)
#define CAN_TEST_NORMAL                     (0U)
#define CAN_TEST_LISTEN_ONLY                (3U)
#define CAN_TEST_LOOPBACK_EXTERNAL          (5U)
#define CAN_TEST_LOOPBACK_INTERNAL          (7U)
#define CAN_MAX_DATA_LENGTH                 (8)

#if CAN_CFG_FIFO_SUPPORT
 #define CAN_MAX_NO_MAILBOXES               (24U)
#else
 #define CAN_MAX_NO_MAILBOXES               (32U)
#endif

#define CAN_BAUD_RATE_PRESCALER_MIN         (1U)
#define CAN_BAUD_RATE_PRESCALER_MAX         (1024U)

#define CAN_SID_MASK                        (0x000007FFU) /* Maximum Standard ID*/
#define CAN_XID_MASK                        (0x1FFFFFFFU) /* Maximum Extended ID*/
#define CAN_INVALID_MASK                    (0xFFFFFFFFU) /* Mask used to determine invalid masks in MKRk*/
#define CAN_GROUP_MASK                      (0x0000000FU)
#define CAN_MAILBOX_GROUP_SIZE              (4U)
#define CAN_DEFAULT_MASK                    (0x1FFFFFFFU)
#define CAN_MAILBOX_RX                      (0x40U)
#define CAN_MAILBOX_RX_MASK_MSGLOST         (0x44U)
#define CAN_MAILBOX_TX                      (0x80U)
#define CAN_ERROR_MASK                      (0x7FU) /* Ignore Error Display Mode Select Bit*/
#define CAN_ACCUMULATED_ERROR_CODE          (0x80U) /* Set Error Display Mode to Accumulated Error Code*/
#define CAN_ERROR_SEARCH                    (2U)
#define CAN_RECEIVE_SEARCH                  (0U)
#define CAN_TRANSMIT_SEARCH                 (1U)
#define CAN_RECOVERY_NORMAL                 (0U)
#define CAN_MAILBOX_MODE_NORMAL             (0U)
#define CAN_ID_PRIORITY_TRANSMIT            (0U)
#define CAN_TIMESTAMP_RESET                 (1U)
#define CAN_TIMESTAMP_RUNNING               (0U)

#define CAN_CHECK_MODE_MASK                 (0x0700U)

#define CAN_MKIVLR_FIFO_MASK                (0x00FFFFFFU)

#define CAN_CANM_SETTING_MASK               (0x03U)
#define CAN_PCLKB_RATIO                     (2U) /* The ratio between PCLKA or ICLK and PCLKB*/

#define CAN_TRANSMIT_CLEAR                  (0U)
#define CAN_TX_RX_INTERRUPTS_ENABLE         (0xFFFFFFFFU)
#define CAN_TX_RX_INTERRUPTS_ENABLE_FIFO    (0x00FFFFFFU)

#define CAN_BAUD_RATE_PRESCALER_MASK        (0x3FFU)

#define CAN_TIMESTAMP_PRESCALER_8BITTIME    (0x3)

/* Error-Warning | Error-Passive | Bus-Off Entry | Bus-Off Recovery | Overrun */
#define CAN_ERROR_INTERRUPTS_ENABLE         (0x3EU)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef enum e_can_sleep
{
    CAN_SLEEP_AWAKEN,
    CAN_SLEEP_SLEEP
} can_sleep_t;

typedef union
{
    uint32_t status;
    struct st_int_status_b
    {
        uint32_t bus_error        : 1;
        uint32_t error_warning    : 1;
        uint32_t error_passive    : 1;
        uint32_t bus_off_entry    : 1;
        uint32_t bus_off_recovery : 1;
        uint32_t receive_overrun  : 1;
        uint32_t overload_frame   : 1;
        uint32_t bus_lock         : 1;
        uint32_t reserved_3       : 24;
    } int_status_b;
} can_error_interrrupt_status_t;

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * can_prv_ns_callback)(can_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile can_prv_ns_callback)(can_callback_args_t * p_args);
#endif

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void r_can_mailbox_id_set(can_extended_cfg_t * p_extend, volatile uint32_t * p_reg, can_mailbox_t * p_id_data);
static void r_can_mailbox_read(can_instance_ctrl_t * p_ctrl, uint32_t mailbox, can_frame_t * p_frame);
static void r_can_call_callback(can_instance_ctrl_t * p_ctrl, can_callback_args_t * p_args);
static void r_can_switch_to_operation_mode(can_instance_ctrl_t * p_ctrl, can_operation_mode_t canm_mode_setting);
static void r_can_mode_transition(can_instance_ctrl_t * p_ctrl,
                                  can_operation_mode_t  operation_mode,
                                  can_test_mode_t       test_mode);

/***********************************************************************************************************************
 * ISR prototypes
 **********************************************************************************************************************/
void can_error_isr(void);
void can_rx_isr(void);
void can_tx_isr(void);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* CAN function pointers   */
const can_api_t g_can_on_can =
{
    .open           = R_CAN_Open,
    .close          = R_CAN_Close,
    .write          = R_CAN_Write,
    .read           = R_CAN_Read,
    .modeTransition = R_CAN_ModeTransition,
    .infoGet        = R_CAN_InfoGet,
    .callbackSet    = R_CAN_CallbackSet,
};

/*******************************************************************************************************************//**
 * @addtogroup CAN
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/***************************************************************************************************************//**
 * Open and configure the CAN channel for operation.
 *
 * Example:
 * @snippet r_can_example.c R_CAN_Open
 *
 * @retval FSP_SUCCESS                      Channel opened successfully
 * @retval FSP_ERR_ALREADY_OPEN             Driver already open.
 * @retval FSP_ERR_CAN_INIT_FAILED          Channel failed to initialize.
 * @retval FSP_ERR_ASSERTION                Null pointer presented.
 *****************************************************************************************************************/
fsp_err_t R_CAN_Open (can_ctrl_t * const p_api_ctrl, can_cfg_t const * const p_cfg)
{
    can_instance_ctrl_t * p_ctrl = (can_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t             err    = FSP_SUCCESS;

#if CAN_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ASSERT(NULL != p_cfg->p_callback);
    FSP_ASSERT(NULL != p_cfg->p_bit_timing);
    FSP_ASSERT(p_cfg->error_irq >= (IRQn_Type) 0);
    FSP_ASSERT(p_cfg->rx_irq >= (IRQn_Type) 0);
    FSP_ASSERT(p_cfg->tx_irq >= (IRQn_Type) 0);

    can_extended_cfg_t * p_extend = (can_extended_cfg_t *) p_cfg->p_extend;

    /* Check for valid mailbox count. Must be a multiple of 4 and maximum of 32. */
    FSP_ERROR_RETURN(p_extend->mailbox_count <= CAN_MAX_NO_MAILBOXES, FSP_ERR_CAN_INIT_FAILED);
    FSP_ERROR_RETURN((p_extend->mailbox_count % CAN_MAILBOX_GROUP_SIZE) == 0, FSP_ERR_CAN_INIT_FAILED);

    /* Check control block isn't already open */
    FSP_ERROR_RETURN(p_ctrl->open != CAN_OPEN, FSP_ERR_ALREADY_OPEN);

    for (uint32_t i = 0U; i < (p_extend->mailbox_count / CAN_MAILBOX_GROUP_SIZE); i++)
    {
        FSP_ERROR_RETURN(p_extend->p_mailbox_mask[i] <= CAN_DEFAULT_MASK, FSP_ERR_CAN_INIT_FAILED);
    }

    /* Check the bit timing settings are within range. */
    /* Check baud Rate Pre-scaler. */
    FSP_ERROR_RETURN(p_cfg->p_bit_timing->baud_rate_prescaler <= CAN_BAUD_RATE_PRESCALER_MAX, FSP_ERR_CAN_INIT_FAILED);
    FSP_ERROR_RETURN(p_cfg->p_bit_timing->baud_rate_prescaler >= CAN_BAUD_RATE_PRESCALER_MIN, FSP_ERR_CAN_INIT_FAILED);

    /* 'Setting of TSEG1 and TSEG2: TSEG1 > TSEG2 > SJW' as described in hardware manual (see Section 37.4.2
     * 'Bit Time Setting' of the RA6M3 manual R01UH0886EJ0100). */

    /* Check Time Segment 1 is greater than Time Segment 2. */
    FSP_ERROR_RETURN((uint32_t) p_cfg->p_bit_timing->time_segment_1 > (uint32_t) p_cfg->p_bit_timing->time_segment_2,
                     FSP_ERR_CAN_INIT_FAILED);

    /* Check Time Segment 2 is greater than or equal to the synchronization jump width */
    FSP_ERROR_RETURN(
        (uint32_t) p_cfg->p_bit_timing->time_segment_2 >= (uint32_t) p_cfg->p_bit_timing->synchronization_jump_width,
        FSP_ERR_CAN_INIT_FAILED);

    /* Get the frequency of pclkb for later validation */
    uint32_t pclkb_frequency = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKB);
 #if BSP_FEATURE_CAN_CHECK_PCLKB_RATIO

    /* Check the hardware manual usage note requirements are met. */
    uint32_t pclka_iclk_frequency = 0U;

    /* 'The clock frequency ratio of ICLK and PCLKB must be 2:1' - Refer hardware manual (see Section 29.9.2
     * 'Settings for the Operating Clock' of the RA2A1 manual R01UH0888EJ0100). */

    /* 'The clock frequency ratio of PCLKA and PCLKB must be 2:1' - Refer hardware manual (see Section 30.9.2
     * 'Settings for the Operating Clock' of the RA4M1 manual R01UH0886EJ0100). */

    /* Get the other clock defined by the hardware manual from the bsp and verify there is a 2:1 ratio */
    pclka_iclk_frequency = R_FSP_SystemClockHzGet(BSP_FEATURE_CAN_CLOCK);
    FSP_ERROR_RETURN((pclka_iclk_frequency / pclkb_frequency) == CAN_PCLKB_RATIO, FSP_ERR_CAN_INIT_FAILED);
 #endif
 #if BSP_FEATURE_CAN_MCLOCK_ONLY
    FSP_ERROR_RETURN(CAN_CLOCK_SOURCE_CANMCLK == ((can_extended_cfg_t *) p_cfg->p_extend)->clock_source,
                     FSP_ERR_CAN_INIT_FAILED);
 #endif

    /* If the device is configured for CANMCLK or supports only CANMCLK */
    if (CAN_CLOCK_SOURCE_CANMCLK == ((can_extended_cfg_t *) p_cfg->p_extend)->clock_source)
    {
        /* 'fPCLKB >= fCANMCLK' - Refer hardware manual (see Section 29.9.2
         * 'Settings for the Operating Clock' of the RA2A1 manual R01UH0888EJ0100). */

        /* 'fPCLKB >= fCANMCLK' - Refer hardware manual (see Section 30.9.2
         * 'Settings for the Operating Clock' of the RA4M1 manual R01UH0886EJ0100). */

        /* 'fPCLKB >= fCANMCLK' - Refer hardware manual (see Section 37.9.2
         * 'Settings for the Operating Clock' of the RA6M3 manual R01UH0886EJ0100). */
        FSP_ERROR_RETURN(pclkb_frequency >= (BSP_CFG_XTAL_HZ), FSP_ERR_CAN_INIT_FAILED);
    }

 #if BSP_FEATURE_CGC_HAS_PLL
    else
    {
        /* Otherwise the device is configured for PCLKB. Verify the source clock is the PLL */

        /* Refer hardware manual (see Section 30.4.1
         * 'Clock Setting' of the RA4M1 manual R01UH0886EJ0100). */

        /* Refer hardware manual (see Section 37.4.1
         * 'Clock Setting' of the RA6M3 manual R01UH0886EJ0100). */
        FSP_ERROR_RETURN(R_SYSTEM->SCKSCR == BSP_CLOCKS_SOURCE_CLOCK_PLL, FSP_ERR_CAN_INIT_FAILED);
    }
 #endif
#else
    can_extended_cfg_t * p_extend = (can_extended_cfg_t *) p_cfg->p_extend;
#endif

    R_CAN0_Type * p_reg =
        (R_CAN0_Type *) ((uint32_t) R_CAN0 + (p_cfg->channel * ((uint32_t) R_CAN1 - (uint32_t) R_CAN0)));
    p_ctrl->p_reg = p_reg;

    R_BSP_MODULE_START(FSP_IP_CAN, p_cfg->channel);

    /* Initialize the control block */
    p_ctrl->p_cfg = p_cfg;

    /* Set callback and context pointers, if configured */
    p_ctrl->p_callback        = p_cfg->p_callback;
    p_ctrl->p_context         = p_cfg->p_context;
    p_ctrl->p_callback_memory = NULL;

    /* Set the clock source to the user configured source. */
    p_ctrl->clock_source = p_extend->clock_source;

    r_can_mode_transition(p_ctrl, CAN_OPERATION_MODE_RESET, CAN_TEST_MODE_DISABLED);

    /* Set up control register fields in reset mode as described in the hardware manual.
     * (See Note 1.under Section 37.2.1 'Control Register (CTLR)' of the RA6M3 manual R01UH0886EJ0100)
     *
     * MBM: Select requested mailbox mode
     * Select ID mode. Standard or extended
     * Select message overwrite or overrun mode
     * TPM: ID priority mode
     * Set time stamp, Time Stamp Pre Scaler: Update every 8 bit times
     * BOM:    Bus Off recovery mode acc. to IEC11898-1
     * Retain awaken state and reset mode
     */
    p_reg->CTLR = (uint16_t) ((CAN_CFG_FIFO_SUPPORT << R_CAN0_CTLR_MBM_Pos) |
                              (p_extend->global_id_mode << R_CAN0_CTLR_IDFM_Pos) |
                              (p_extend->message_mode << R_CAN0_CTLR_MLM_Pos) |
                              (CAN_TIMESTAMP_PRESCALER_8BITTIME << R_CAN0_CTLR_TSPS_Pos) |
                              (CAN_OPERATION_MODE_RESET << R_CAN0_CTLR_CANM_Pos));

    /* Set timing bits */
    can_bit_timing_cfg_t * p_bit_timing = p_cfg->p_bit_timing;
    p_reg->BCR =
        (uint32_t) (((p_bit_timing->baud_rate_prescaler - 1) & CAN_BAUD_RATE_PRESCALER_MASK) << R_CAN0_BCR_BRP_Pos) |
        ((p_bit_timing->time_segment_1 - 1U) << R_CAN0_BCR_TSEG1_Pos) |
        ((p_bit_timing->time_segment_2 - 1U) << R_CAN0_BCR_TSEG2_Pos) |
        (uint32_t) ((p_bit_timing->synchronization_jump_width - 1U) << R_CAN0_BCR_SJW_Pos) |
        (uint32_t) (p_ctrl->clock_source << R_CAN0_BCR_CCLKS_Pos);

    /* Enter Halt mode */
    r_can_mode_transition(p_ctrl, CAN_OPERATION_MODE_HALT, CAN_TEST_MODE_DISABLED);

    /* Set Error Display mode in Halt mode. */
    p_reg->ECSR = CAN_ACCUMULATED_ERROR_CODE;

    /* Configure mailboxes. */

    /* Clear all mailboxes in Halt mode (FIFO mailboxes are cleared automatically). */
    memset((void *) p_reg->MB, 0, sizeof(R_CAN0_MB_Type) * CAN_MAX_NO_MAILBOXES);

    /* Set the direction and ID (if applicable) for each mailbox. */
    for (uint32_t i = 0U; i < CAN_MAX_NO_MAILBOXES; i++)
    {
        uint8_t mctl;

        if ((CAN_MAILBOX_RECEIVE == (p_extend->p_mailbox[i].mailbox_type)) && (i < p_extend->mailbox_count))
        {
            r_can_mailbox_id_set(p_extend, &p_reg->MB[i].ID, &p_extend->p_mailbox[i]);

            /* Configure mailbox for receive */
            mctl = CAN_MAILBOX_RX;
        }
        else
        {
            /* Clear NEWDATA if set */
            mctl = 0U;
        }

        /* Configure mailbox for transmit or receive (MCTL_RX and MCTL_TX are the same array) */
        p_reg->MCTL_RX[i] = mctl;
    }

    /* Set all masks to disabled. */
    uint32_t mask_enabled = 0;

    /* Set the masks for each mailbox group and initialize the mask invalid register. */
    for (uint32_t i = 0; i < p_extend->mailbox_count / CAN_MAILBOX_GROUP_SIZE; i++)
    {
        /*  If the user has defined a mask */
        if (p_extend->p_mailbox_mask[i] < CAN_DEFAULT_MASK)
        {
            uint32_t mask = p_extend->p_mailbox_mask[i];

            /* In Mixed ID mode the Standard ID mask (SID) is the upper 11 bits of the full Extended ID (SID+XID) */
            if (CAN_GLOBAL_ID_MODE_STANDARD == p_extend->global_id_mode)
            {
                /* Set standard ID mask. Set unused bits low */
                mask = (mask & CAN_SID_MASK) << R_CAN0_MB_ID_SID_Pos;
            }

            p_reg->MKR[i] = mask;

            /* Enable the mask for this group */
            mask_enabled |= CAN_GROUP_MASK << (i << 2);
        }
    }

#if CAN_CFG_FIFO_SUPPORT

    /* Set the Mask as invalid for mailboxes that do not use the mask.
     * Bits 24:31 in MKIVLR must not be set in FIFO mode (see Note 1 in Section 37.2.5 "Mask Invalid Register (MKIVLR)
     * of the RA6M3 User's Manual (R01UH0886EJ0120)). */
    p_reg->MKIVLR = ~(mask_enabled) & CAN_MKIVLR_FIFO_MASK;

    /* Get pointer to RX FIFO configuration */
    can_rx_fifo_cfg_t * p_rx_fifo_cfg = p_extend->p_rx_fifo_cfg;

    /* Set RX FIFO ID and mask registers */
    r_can_mailbox_id_set(p_extend, &p_reg->FIDCR[0], &p_rx_fifo_cfg->rx_fifo_id1);
    r_can_mailbox_id_set(p_extend, &p_reg->FIDCR[1], &p_rx_fifo_cfg->rx_fifo_id2);

    uint32_t mask1 = p_rx_fifo_cfg->rx_fifo_mask1;
    uint32_t mask2 = p_rx_fifo_cfg->rx_fifo_mask2;

    /* In Mixed ID mode the Standard ID mask (SID) is the upper 11 bits of the full Extended ID (SID+XID) */
    if (CAN_GLOBAL_ID_MODE_STANDARD == p_extend->global_id_mode)
    {
        /* Set standard ID mask. Set unused bits low */
        mask1 = (mask1 & CAN_SID_MASK) << R_CAN0_MB_ID_SID_Pos;
        mask2 = (mask2 & CAN_SID_MASK) << R_CAN0_MB_ID_SID_Pos;
    }

    p_reg->MKR[6] = mask1;
    p_reg->MKR[7] = mask2;
#else

    /* Set the Mask as invalid for mailboxes that do not use the mask. */
    p_reg->MKIVLR = ~(mask_enabled);
#endif

    /* Go to normal operation. */
    r_can_mode_transition(p_ctrl, CAN_OPERATION_MODE_NORMAL, CAN_TEST_MODE_DISABLED);

    /* Time Stamp Counter reset. Set the TSRC bit to 1 in CAN Operation mode. */

    /* 'Set the TSRC bit to 1 in CAN operation mode.' - Refer hardware manual (see Section 37.2.1
     * 'Control Register (CTLR)'- 'Note 4' of the RA4M1 manual R01UH0886EJ0100). */
    p_reg->CTLR_b.TSRC = CAN_TIMESTAMP_RESET; /* Set Timestamp counter reset command */
    FSP_HARDWARE_REGISTER_WAIT(p_reg->CTLR_b.TSRC, !CAN_TIMESTAMP_RESET);

    /* If successful, Lookup and store IRQ numbers. Enable interrupts. */
    R_BSP_IrqCfgEnable(p_cfg->error_irq, p_cfg->ipl, p_ctrl);
    R_BSP_IrqCfgEnable(p_cfg->rx_irq, p_cfg->ipl, p_ctrl);
    R_BSP_IrqCfgEnable(p_cfg->tx_irq, p_cfg->ipl, p_ctrl);

    /* Error-Warning | Error-Passive | Bus-Off Entry | Bus-Off Recovery | Overrun */
    p_reg->EIER = CAN_ERROR_INTERRUPTS_ENABLE;

#if CAN_CFG_FIFO_SUPPORT

    /* Get pointer to FIFO interrupt config */
    can_fifo_interrupt_cfg_t const * p_fifo_int_cfg = p_extend->p_fifo_int_cfg;

    /* Enable interrupts */
    R_BSP_IrqCfgEnable(p_fifo_int_cfg->rx_fifo_irq, p_cfg->ipl, p_ctrl);
    R_BSP_IrqCfgEnable(p_fifo_int_cfg->tx_fifo_irq, p_cfg->ipl, p_ctrl);

    /* Set FIFO interrupt mode and enable mailbox interrupts */
    p_reg->MIER = p_fifo_int_cfg->fifo_int_mode | CAN_TX_RX_INTERRUPTS_ENABLE_FIFO;

    /* Set FIFO enable bits */
    p_reg->TFCR = 1U;
    p_reg->RFCR = 1U;
#else

    /* Set interrupt enable bits */
    p_reg->MIER = CAN_TX_RX_INTERRUPTS_ENABLE;
#endif

    /* If successful, Mark the control block as open */
    p_ctrl->open = CAN_OPEN;

    return err;
}

/***************************************************************************************************************//**
 * Close the CAN channel.
 * @retval FSP_SUCCESS          Channel closed successfully.
 * @retval FSP_ERR_NOT_OPEN     Control block not open.
 * @retval FSP_ERR_ASSERTION    Null pointer presented.
 *****************************************************************************************************************/
fsp_err_t R_CAN_Close (can_ctrl_t * const p_api_ctrl)
{
    can_instance_ctrl_t * p_ctrl = (can_instance_ctrl_t *) p_api_ctrl;

#if CAN_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(p_ctrl->open == CAN_OPEN, FSP_ERR_NOT_OPEN);
#endif

    p_ctrl->open = 0U;

    R_BSP_IrqDisable(p_ctrl->p_cfg->error_irq);
    R_BSP_IrqDisable(p_ctrl->p_cfg->rx_irq);
    R_BSP_IrqDisable(p_ctrl->p_cfg->tx_irq);

#if CAN_CFG_FIFO_SUPPORT
    can_extended_cfg_t             * p_extend       = (can_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    can_fifo_interrupt_cfg_t const * p_fifo_int_cfg = p_extend->p_fifo_int_cfg;
    R_BSP_IrqDisable(p_fifo_int_cfg->rx_fifo_irq);
    R_BSP_IrqDisable(p_fifo_int_cfg->tx_fifo_irq);
#endif

    R_CAN0_Type * p_reg = p_ctrl->p_reg;

#if CAN_CFG_FIFO_SUPPORT

    /* Clear FIFO enable bits */
    p_reg->TFCR = 0U;
    p_reg->RFCR = 0U;
#endif

    /* Clear interrupt enable bits */
    p_reg->EIER = 0U;
    p_reg->MIER = 0U;

    R_BSP_MODULE_STOP(FSP_IP_CAN, p_ctrl->p_cfg->channel);

    return FSP_SUCCESS;
}

/***************************************************************************************************************//**
 * Write data to the CAN channel. Write up to eight bytes to the channel mailbox.
 *
 * Example:
 * @snippet r_can_example.c R_CAN_Write
 *
 * @retval FSP_SUCCESS                      Operation succeeded.
 * @retval FSP_ERR_NOT_OPEN                 Control block not open.
 * @retval FSP_ERR_CAN_TRANSMIT_NOT_READY   Transmit in progress, cannot write data at this time.
 * @retval FSP_ERR_CAN_TRANSMIT_FIFO_FULL   Transmit FIFO is full.
 * @retval FSP_ERR_CAN_RECEIVE_MAILBOX      Mailbox is setup for receive and cannot send.
 * @retval FSP_ERR_INVALID_ARGUMENT         Data length or frame type invalid.
 * @retval FSP_ERR_ASSERTION                Null pointer presented
 *****************************************************************************************************************/
fsp_err_t R_CAN_Write (can_ctrl_t * const p_api_ctrl, uint32_t mailbox, can_frame_t * const p_frame)
{
    can_instance_ctrl_t * p_ctrl = (can_instance_ctrl_t *) p_api_ctrl;

#if CAN_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_frame);
    FSP_ERROR_RETURN(p_ctrl->open == CAN_OPEN, FSP_ERR_NOT_OPEN);

    can_extended_cfg_t * p_extend = (can_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
 #if CAN_CFG_FIFO_SUPPORT
    FSP_ERROR_RETURN(mailbox < p_extend->mailbox_count || (mailbox == CAN_MAILBOX_ID_TX_FIFO),
                     FSP_ERR_INVALID_ARGUMENT);
 #else
    FSP_ERROR_RETURN(mailbox < p_extend->mailbox_count, FSP_ERR_INVALID_ARGUMENT);
 #endif

    R_CAN0_Type * p_reg = p_ctrl->p_reg;
    FSP_ERROR_RETURN(1U != p_reg->MCTL_TX_b[mailbox].RECREQ, FSP_ERR_CAN_RECEIVE_MAILBOX);

    FSP_ERROR_RETURN((p_frame->data_length_code <= CAN_MAX_DATA_LENGTH), FSP_ERR_INVALID_ARGUMENT);
#else
    can_extended_cfg_t * p_extend = (can_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    R_CAN0_Type        * p_reg    = p_ctrl->p_reg;
#endif

#if CAN_CFG_FIFO_SUPPORT
    if (CAN_MAILBOX_ID_TX_FIFO == mailbox)
    {
        /* Check if FIFO is full */
        FSP_ERROR_RETURN(1U != p_reg->TFCR_b.TFFST, FSP_ERR_CAN_TRANSMIT_FIFO_FULL);
    }
    else
#endif
    {
        /* Check if MB is ready */
        FSP_ERROR_RETURN(0U == p_reg->MCTL_TX_b[mailbox].TRMREQ, FSP_ERR_CAN_TRANSMIT_NOT_READY);
    }

    /* Setup the frame to be transmitted. */

    /* Set the ID register */
    r_can_mailbox_id_set(p_extend, &p_reg->MB[mailbox].ID, (can_mailbox_t *) p_frame);

    /* Put mailbox data length code */
    p_reg->MB[mailbox].DL_b.DLC = (p_frame->data_length_code & 0x0FU);

    /* Put mailbox data. */
    uint32_t  len    = p_frame->data_length_code;
    uint8_t * p_dest = (uint8_t *) p_reg->MB[mailbox].D;
    uint8_t * p_src  = p_frame->data;
    while (len--)
    {
        *p_dest++ = *p_src++;
    }

#if CAN_CFG_FIFO_SUPPORT
    if (CAN_MAILBOX_ID_TX_FIFO == mailbox)
    {
        /* Increment the FIFO pointer */
        p_reg->TFPCR = UINT8_MAX;
    }
    else
#endif
    {
        /* Transmit the frame */
        p_reg->MCTL_TX[mailbox] = CAN_MAILBOX_TX;
    }

    return FSP_SUCCESS;
}

/***************************************************************************************************************//**
 * Read data from a mailbox or FIFO.
 *
 * @note This function is not supported.
 *
 * @retval FSP_ERR_UNSUPPORTED              Function not supported.
 *****************************************************************************************************************/
fsp_err_t R_CAN_Read (can_ctrl_t * const p_api_ctrl, uint32_t mailbox, can_frame_t * const p_frame)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(mailbox);
    FSP_PARAMETER_NOT_USED(p_frame);

    /* Normal mailbox mode is interrupt-driven only. */
    return FSP_ERR_UNSUPPORTED;
}

/***************************************************************************************************************//**
 * CAN Mode Transition is used to change CAN driver state.
 *
 * Example:
 * @snippet r_can_example.c R_CAN_ModeTransition
 *
 * @retval FSP_SUCCESS                      Operation succeeded.
 * @retval FSP_ERR_NOT_OPEN                 Control block not open.
 * @retval FSP_ERR_ASSERTION                Null pointer presented
 *****************************************************************************************************************/
fsp_err_t R_CAN_ModeTransition (can_ctrl_t * const   p_api_ctrl,
                                can_operation_mode_t operation_mode,
                                can_test_mode_t      test_mode)
{
    can_instance_ctrl_t * p_ctrl = (can_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t             err    = FSP_SUCCESS;
#if CAN_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(p_ctrl->open == CAN_OPEN, FSP_ERR_NOT_OPEN);
#endif

    r_can_mode_transition(p_ctrl, operation_mode, test_mode);

    return err;
}

/***************************************************************************************************************//**
 * Get CAN state and status information for the channel.
 * @retval  FSP_SUCCESS                     Operation succeeded.
 * @retval  FSP_ERR_NOT_OPEN                Control block not open.
 * @retval  FSP_ERR_ASSERTION               Null pointer presented
 *****************************************************************************************************************/
fsp_err_t R_CAN_InfoGet (can_ctrl_t * const p_api_ctrl, can_info_t * const p_info)
{
    can_instance_ctrl_t * p_ctrl = (can_instance_ctrl_t *) p_api_ctrl;

#if CAN_CFG_PARAM_CHECKING_ENABLE

    /* Check pointers for NULL values */
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_info);

    /* If channel is not open, return an error */
    FSP_ERROR_RETURN(p_ctrl->open == CAN_OPEN, FSP_ERR_NOT_OPEN);
#endif

    R_CAN0_Type * p_reg = p_ctrl->p_reg;

    p_info->status               = (can_status_t) p_reg->STR;                  /* Status register value*/
    p_info->error_count_receive  = p_reg->RECR;                                /* Report receive error count*/
    p_info->error_count_transmit = p_reg->TECR;                                /* Report transmit error count*/
    p_info->error_code           = (can_error_t) p_reg->ECSR & CAN_ERROR_MASK; /* Report error code*/

    /* Since the error flags were read, we clear them to ensure that we won't read them again
     * Because register is volatile, we clear only the flags that we already read. Preserve the value
     * of EDPM bit. Clear error bits by writing 0 to bits that were found to be 1
     */
    p_reg->ECSR = (uint8_t) (p_info->error_code) ^ CAN_ERROR_MASK;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the user callback with the option to provide memory for the callback argument structure.
 * Implements @ref can_api_t::callbackSet.
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t R_CAN_CallbackSet (can_ctrl_t * const          p_api_ctrl,
                             void (                    * p_callback)(can_callback_args_t *),
                             void * const                p_context,
                             can_callback_args_t * const p_callback_memory)
{
    can_instance_ctrl_t * p_ctrl = (can_instance_ctrl_t *) p_api_ctrl;

#if CAN_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(CAN_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if CAN_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    can_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                      CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD
    p_ctrl->p_callback = callback_is_secure ? p_callback :
                         (void (*)(can_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_ctrl->p_callback = p_callback;
#endif
    p_ctrl->p_context         = p_context;
    p_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup CAN)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Sets the ID register for a mailbox or FIFO.
 *
 * @param[in]     p_extend     Pointer to CAN extended config
 * @param[in]     p_reg        Pointer to target ID register
 * @param[in]     p_id_data    Pointer to ID settings
 **********************************************************************************************************************/
static void r_can_mailbox_id_set (can_extended_cfg_t * p_extend, volatile uint32_t * p_reg, can_mailbox_t * p_id_data)
{
    can_global_id_mode_t global_mode = p_extend->global_id_mode;

    uint32_t ide = 0U;
    uint32_t id;

    if ((CAN_GLOBAL_ID_MODE_STANDARD == global_mode) ||
        ((global_mode == CAN_GLOBAL_ID_MODE_MIXED) && (p_id_data->id_mode == CAN_ID_MODE_STANDARD)))
    {
        id = (uint32_t) ((p_id_data->mailbox_id & CAN_SID_MASK) << R_CAN0_MB_ID_SID_Pos);
    }
    else
    {
        if ((global_mode == CAN_GLOBAL_ID_MODE_MIXED) && (p_id_data->id_mode == CAN_ID_MODE_EXTENDED))
        {
            /* The IDE bit is only set when configuring an extended ID mailbox in Mixed ID mode. */
            ide = R_CAN0_MB_ID_IDE_Msk;
        }

        id = p_id_data->mailbox_id & CAN_XID_MASK;
    }

    uint32_t frame_type = (uint32_t) (p_id_data->frame_type << R_CAN0_MB_ID_RTR_Pos);

    *p_reg = (ide | frame_type | id);
}

/*******************************************************************************************************************//**
 * Read a mailbox or FIFO.
 *
 * @param[in]     p_ctrl       Pointer to CAN control struct
 * @param[in]     mailbox      CAN mailbox ID
 * @param[in]     p_frame      Pointer to destination frame
 **********************************************************************************************************************/
static inline void r_can_mailbox_read (can_instance_ctrl_t * p_ctrl, uint32_t mailbox, can_frame_t * p_frame)
{
    volatile R_CAN0_Type * p_reg = p_ctrl->p_reg;

    /* Get frame ID. */
    uint32_t mbox_id = p_reg->MB[mailbox].ID;

    /* Get the frame type */
    p_frame->type = (can_frame_type_t) ((mbox_id & R_CAN0_MB_ID_RTR_Msk) >> R_CAN0_MB_ID_RTR_Pos);

    /* Get the ID mode */
    can_extended_cfg_t * p_extend = (can_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    p_frame->id_mode = (can_id_mode_t) ((p_extend->global_id_mode | p_reg->MB[mailbox].ID_b.IDE) & 1);

    /* Get the ID based on the mode */
    if (CAN_ID_MODE_STANDARD == p_frame->id_mode)
    {
        p_frame->id = (mbox_id & R_CAN0_MB_ID_SID_Msk) >> R_CAN0_MB_ID_SID_Pos;
    }
    else
    {
        p_frame->id = mbox_id & (R_CAN0_MB_ID_SID_Msk | R_CAN0_MB_ID_EID_Msk);
    }

    /* Get the frame data length code */
    p_frame->data_length_code = p_reg->MB[mailbox].DL_b.DLC;

    /* Refer Note 1 about DLC[3:0] under Section 37.2.6
     * 'Mailbox Register j (MBj_ID, MBj_DL, MBj_Dm, MBj_TS) (j = 0 to 31; m = 0 to 7)'
     * of RA6M3 manual R01UH0886EJ010.
     */
    if (p_frame->data_length_code > CAN_MAX_DATA_LENGTH)
    {
        p_frame->data_length_code = CAN_MAX_DATA_LENGTH;
    }

    /* Be sure to check data_length_code in calling function */
    for (uint32_t i = 0U; i < p_frame->data_length_code; i++)
    {
        p_frame->data[i] = p_reg->MB[mailbox].D[i]; /* Copy receive data to buffer*/
    }

#if CAN_CFG_FIFO_SUPPORT
    if (CAN_MAILBOX_ID_RX_FIFO == mailbox)
    {
        /* Increment receive FIFO pointer */
        p_reg->RFPCR = UINT8_MAX;
    }
    else
#endif
    {
        /* Clear rx data flag. Do not modify message-lost flag as this keeps track of
         * error interrupts to be fired.
         * This flag will be cleared in the error isr.
         * Message Lost flag is written as 1 as that has no effect on this bit.
         * Refer 'Note 1. Write 0 only. Writing 1 has no effect.' under section
         * '29.2.10 Message Control Register for Receive (MCTL_RXj) (j = 0 to 31)'
         * or RA6M3 HW manual R01UH0886EJ0100.
         */
        p_reg->MCTL_RX[mailbox] = CAN_MAILBOX_RX_MASK_MSGLOST;
    }

    p_frame->options = 0;
}

/*******************************************************************************************************************//**
 * Calls user callback.
 *
 * @param[in]     p_ctrl     Pointer to CAN instance control block
 * @param[in]     p_args     Pointer to arguments on stack
 **********************************************************************************************************************/
static void r_can_call_callback (can_instance_ctrl_t * p_ctrl, can_callback_args_t * p_args)
{
    can_callback_args_t args;

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    can_callback_args_t * p_args_memory = p_ctrl->p_callback_memory;
    if (NULL == p_args_memory)
    {
        /* Use provided args struct on stack */
        p_args_memory = p_args;
    }
    else
    {
        /* Save current arguments on the stack in case this is a nested interrupt. */
        args = *p_args_memory;

        /* Copy the stacked args to callback memory */
        *p_args_memory = *p_args;
    }

#if BSP_TZ_SECURE_BUILD

    /* p_callback can point to a secure function or a non-secure function. */
    if (!cmse_is_nsfptr(p_ctrl->p_callback))
    {
        /* If p_callback is secure, then the project does not need to change security state. */
        p_ctrl->p_callback(p_args_memory);
    }
    else
    {
        /* If p_callback is Non-secure, then the project must change to Non-secure state in order to call the callback. */
        can_prv_ns_callback p_callback = (can_prv_ns_callback) (p_ctrl->p_callback);
        p_callback(p_args_memory);
    }

#else

    /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the callback. */
    p_ctrl->p_callback(p_args_memory);
#endif

    if (NULL != p_ctrl->p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_ctrl->p_callback_memory = args;
    }
}

/*******************************************************************************************************************//**
 * Error ISR.
 *
 * Saves context if RTOS is used, clears interrupts, calls common error function, and restores context if RTOS is used.
 **********************************************************************************************************************/
void can_error_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE
    /* Clear interrupt */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    IRQn_Type             irq    = R_FSP_CurrentIrqGet();
    can_instance_ctrl_t * p_ctrl = (can_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    can_callback_args_t args    = {0U};
    uint32_t            mailbox = 0U;

    R_CAN0_Type * p_reg = p_ctrl->p_reg;

    /* Get source of error interrupt. */
    args.event = (can_event_t) p_reg->EIFR; /* Read Error Interrupt Factor Judge register*/

    p_reg->EIFR = 0x00U;                    /* Clear Error Interrupt Factor Judge register*/

    /* Although NMLST detects both Overwrite and Overrun conditions,
     * in such a scenario this interrupt is fired only when the peripheral is in the overrun mode
     * (Either on its own or manually by setting NVIC_SetPendingIRQ below).
     * The receive_overrun bit may not be checked here.
     */
    if (p_reg->STR_b.NMLST)
    {
        args.event |= CAN_EVENT_MAILBOX_MESSAGE_LOST;
        uint8_t saved_msmr = p_reg->MSMR;       /* Save the current MSMR value*/
        p_reg->MSMR = CAN_ERROR_SEARCH;         /* search for lowest numbered mailbox with message lost*/
        mailbox     = p_reg->MSSR_b.MBNST;      /* get mailbox number*/
        p_reg->MSMR = saved_msmr;               /* Restore the previous MSMR value*/
        p_reg->MCTL_RX_b[mailbox].MSGLOST = 0U; /* Clear the error so that NMLST is not set again for an already handled error.*/
    }

    args.channel   = p_ctrl->p_cfg->channel;
    args.p_context = p_ctrl->p_context;
    args.mailbox   = mailbox;
    r_can_call_callback(p_ctrl, &args);

    /* Get extended config */
    can_extended_cfg_t * p_extend = (can_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    /* Check for mailboxes with data loss due to overrun,
     * if true, fire this interrupt again.
     * Do not re-trigger this interrupt due to message loss in overwrite mode.
     */
    if (p_reg->STR_b.NMLST && (CAN_MESSAGE_MODE_OVERWRITE != p_extend->message_mode))
    {
        NVIC_SetPendingIRQ(p_ctrl->p_cfg->error_irq);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * Receive ISR.
 *
 * Saves context if RTOS is used, clears interrupts, calls common receive function
 * and restores context if RTOS is used.
 **********************************************************************************************************************/
void can_rx_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE
    /* Clear interrupt */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    IRQn_Type             irq    = R_FSP_CurrentIrqGet();
    can_instance_ctrl_t * p_ctrl = (can_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    can_callback_args_t args;
    uint32_t            mailbox;

    args.event = CAN_EVENT_RX_COMPLETE;

    R_CAN0_Type * p_reg = p_ctrl->p_reg;

#if CAN_CFG_FIFO_SUPPORT
    can_extended_cfg_t             * p_extend       = (can_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    can_fifo_interrupt_cfg_t const * p_fifo_int_cfg = p_extend->p_fifo_int_cfg;
    if (irq == p_fifo_int_cfg->rx_fifo_irq)
    {
        /* Set the mailbox number to 28 (RX FIFO). */
        mailbox = CAN_MAILBOX_ID_RX_FIFO;

        uint8_t rfcr = p_reg->RFCR;
        if (rfcr & R_CAN0_RFCR_RFMLF_Msk)
        {
            /* Clear the Receive FIFO Message Lost Flag if set (see Section 37.2.12 'Receive FIFO Pointer Control
             * Register (RFPCR)' in the RA6M3 User's Manual (R01UH0886EJ0110))  */
            p_reg->RFCR_b.RFMLF = 0;

            /* Add a FIFO message lost flag to the event */
            args.event |= CAN_EVENT_FIFO_MESSAGE_LOST;
        }
    }
    else
#endif
    {
        uint8_t saved_msmr = p_reg->MSMR;  /* Save the current MSMR value*/
        p_reg->MSMR = CAN_RECEIVE_SEARCH;  /* search for lowest numbered &mailbox with message received*/
        mailbox     = p_reg->MSSR_b.MBNST; /* get mailbox number*/
        p_reg->MSMR = saved_msmr;          /* Restore the previous MSMR value*/
    }

    /* Read frame to args */
    r_can_mailbox_read(p_ctrl, mailbox, &args.frame);

    /* Save the receive mailbox number. */
    args.mailbox = mailbox;

    args.channel   = p_ctrl->p_cfg->channel;
    args.p_context = p_ctrl->p_context;
    r_can_call_callback(p_ctrl, &args);

#if CAN_CFG_FIFO_SUPPORT
    if (irq == p_fifo_int_cfg->rx_fifo_irq)
    {
        if (!p_reg->RFCR_b.RFEST)
        {
            /* Reset FIFO IRQ if the FIFO is not empty. */
            NVIC_SetPendingIRQ(irq);
        }
    }
    else
#endif
    {
        if (p_reg->STR_b.NDST)
        {
            /* Reset MB IRQ if another MB has requested it. */
            NVIC_SetPendingIRQ(irq);
        }
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * Transmit ISR.
 *
 * Saves context if RTOS is used, clears interrupts, calls common transmit function
 * and restores context if RTOS is used.
 **********************************************************************************************************************/
void can_tx_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE
    /* Clear interrupt */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    IRQn_Type             irq    = R_FSP_CurrentIrqGet();
    can_instance_ctrl_t * p_ctrl = (can_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    can_callback_args_t args;
    args.event = (can_event_t) 0;

    R_CAN0_Type * p_reg = p_ctrl->p_reg;

#if CAN_CFG_FIFO_SUPPORT
    can_extended_cfg_t             * p_extend       = (can_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    can_fifo_interrupt_cfg_t const * p_fifo_int_cfg = p_extend->p_fifo_int_cfg;

    if (irq == p_fifo_int_cfg->tx_fifo_irq)
    {
        /* Set the mailbox number to 24 (TX FIFO). */
        args.mailbox = CAN_MAILBOX_ID_TX_FIFO;

        if (p_fifo_int_cfg->fifo_int_mode & R_CAN0_MIER_FIFO_MB25_Msk)
        {
            /* When MB25 is set the TX FIFO ISR only fires when the last message has been transmitted. */
            args.event = CAN_EVENT_TX_FIFO_EMPTY;
        }
    }
    else
#endif
    {
        uint8_t saved_msmr = p_reg->MSMR;             /* Save the current MSMR value*/
        p_reg->MSMR = CAN_TRANSMIT_SEARCH;            /* search for lowest numbered &mailbox with message transmitted*/
        uint32_t mailbox = p_reg->MSSR_b.MBNST;       /* get mailbox number*/
        p_reg->MSMR = saved_msmr;                     /* Restore the previous MSMR value*/

        /* Clear SENTDATA.
         * Do a byte-write to avoid read-modify-write with HW writing another bit in between.
         * TRMREQ must be set to 0 (or will send again).
         * Do it twice since bits SENTDATA and TRMREQ cannot be set to 0 simultaneously
         * Refer Section 29.2.9 'Message Control Register for Transmit (MCTL_TXj) (j = 0 to 31)'
         * under "SENTDATA flag (Transmission Complete Flag)" of RA6M3 HW manual R01UH0886EJ0100.
         */
        p_reg->MCTL_TX[mailbox] = CAN_TRANSMIT_CLEAR;
        p_reg->MCTL_TX[mailbox] = CAN_TRANSMIT_CLEAR; /* Clear SENTDATA and TRMREQ.*/

        /* Save the transmit mailbox number. */
        args.mailbox = mailbox;
    }

    /*  Set event argument to transmit complete. */
    args.event |= CAN_EVENT_TX_COMPLETE;

    args.channel   = p_ctrl->p_cfg->channel;
    args.p_context = p_ctrl->p_context;
    r_can_call_callback(p_ctrl, &args);

    /* Check for other mailboxes with pending transmit complete flags. */
#if CAN_CFG_FIFO_SUPPORT
    if ((irq != p_fifo_int_cfg->tx_fifo_irq) && p_reg->STR_b.SDST)
#else
    if (p_reg->STR_b.SDST)
#endif
    {
        NVIC_SetPendingIRQ(p_ctrl->p_cfg->tx_irq);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * This function is used to switch the CAN peripheral operation and test modes.
 * @param[in]  p_ctrl            - pointer to control structure
 * @param[in]  operation_mode    - destination operation mode
 * @param[in]  test_mode         - destination test mode
 **********************************************************************************************************************/
static void r_can_mode_transition (can_instance_ctrl_t * p_ctrl,
                                   can_operation_mode_t  operation_mode,
                                   can_test_mode_t       test_mode)
{
    R_CAN0_Type * p_reg = p_ctrl->p_reg;

    if (p_ctrl->test_mode != test_mode)
    {
        /* Switch to halt mode */
        r_can_switch_to_operation_mode(p_ctrl, CAN_OPERATION_MODE_HALT);

        /* 'Write to TCR in CAN halt mode only.' - Refer hardware manual (see Section 37.2.26
         * 'Test Control Register (TCR)' of the RA6M3 manual R01UH0886EJ0100). */
        p_reg->TCR = (uint8_t) test_mode; /* Destination test mode */

        /* Set current test mode. */
        p_ctrl->test_mode      = test_mode;
        p_ctrl->operation_mode = CAN_OPERATION_MODE_HALT;
    }

    if (p_ctrl->operation_mode != operation_mode)
    {
        if (CAN_OPERATION_MODE_SLEEP == operation_mode)
        {
            r_can_switch_to_operation_mode(p_ctrl, CAN_OPERATION_MODE_HALT);

            /* 'Write to the SLPM bit in CAN reset mode and CAN halt mode.'
             * Refer hardware manual (see Section 37.3.3
             * 'CAN Sleep Mode' of the RA6M3 manual R01UH0886EJ0100)
             */
            p_reg->CTLR_b.SLPM = CAN_SLEEP_SLEEP;
            FSP_HARDWARE_REGISTER_WAIT(p_reg->STR_b.SLPST, 1U);
        }
        else
        {
            r_can_switch_to_operation_mode(p_ctrl, operation_mode);
        }

        /* Set current test mode. */
        p_ctrl->operation_mode = operation_mode;
    }
}

/*******************************************************************************************************************//**
 * This function causes the CAN peripheral to transition to operation mode
 * @param[in]  p_ctrl               - pointer to control structure
 * @param[in]  canm_mode_setting    - destination CAN mode
 **********************************************************************************************************************/
static void r_can_switch_to_operation_mode (can_instance_ctrl_t * p_ctrl, can_operation_mode_t canm_mode_setting)
{
    R_CAN0_Type * p_reg = p_ctrl->p_reg;

    p_reg->CTLR_b.SLPM = CAN_SLEEP_AWAKEN;
    p_reg->CTLR_b.CANM = (uint16_t) (canm_mode_setting & CAN_CANM_SETTING_MASK);

    /* Refer notes under Section '29.2.1 Control Register (CTLR)' of RA6M3 HW manual R01UH0886EJ0100 */
    FSP_HARDWARE_REGISTER_WAIT((p_reg->STR & CAN_CHECK_MODE_MASK),
                               (uint32_t) ((uint8_t) canm_mode_setting << R_CAN0_CTLR_CANM_Pos));
}
