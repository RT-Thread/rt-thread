/*
 * Copyright (c) 2021-2025 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * @file drv_can.c
 * @brief CAN driver implementation for RT-Thread
 *
 * This file implements the CAN (Controller Area Network) driver for HPM6700
 * and HPM6300 series, providing a complete interface between RT-Thread's CAN
 * framework and the HPM CAN hardware.
 *
 * Features:
 * - Support for up to 4 CAN controllers (CAN0-CAN3)
 * - CAN 2.0A/B and CAN FD support
 * - Hardware filtering with up to 16 filters
 * - Interrupt-driven operation
 * - Error handling and status reporting
 * - Configurable baud rates and timing parameters
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-08     HPMicro      the first version
 * 2023-05-08     HPMicro      Adapt RT-Thread v5.0.0

 * 2025/03-25     HPMicro      Add configurable interrupt priority support
 * 2025-09-01     HPMicro      Revised the code, reduced repetitive codes
 */

#include "rtconfig.h"

#ifdef RT_USING_CAN

/* RT-Thread includes */
#include <rtthread.h>
#include <rtdevice.h>

/* HPM SDK includes */
#include "board.h"
#include "hpm_can_drv.h"
#include "hpm_clock_drv.h"
#include <rthw.h>

/* CAN Driver Configuration Constants */
#define CAN_SEND_WAIT_MS_MAX (1000U)    /* Maximum wait time for transmission (ms) */
#define CAN_SENDBOX_NUM (1U)            /* Number of hardware transmission buffers */
#define CAN_FILTER_NUM_MAX (16U)        /* Maximum number of hardware filters */


/*
 * Interrupt Priority Configuration Macros
 * These macros handle the configuration of interrupt priorities for each CAN controller.
 * If a specific priority is defined in the board configuration, it will be used;
 * otherwise, a default priority of 1 is applied.
 */

/* CAN IRQ Priority Configuration Macros */
#ifdef BSP_CAN0_IRQ_PRIORITY
#define CAN_IRQ_PRI_VAL_0 BSP_CAN0_IRQ_PRIORITY
#else
#define CAN_IRQ_PRI_VAL_0 1
#endif

#ifdef BSP_CAN1_IRQ_PRIORITY
#define CAN_IRQ_PRI_VAL_1 BSP_CAN1_IRQ_PRIORITY
#else
#define CAN_IRQ_PRI_VAL_1 1
#endif

#ifdef BSP_CAN2_IRQ_PRIORITY
#define CAN_IRQ_PRI_VAL_2 BSP_CAN2_IRQ_PRIORITY
#else
#define CAN_IRQ_PRI_VAL_2 1
#endif

#ifdef BSP_CAN3_IRQ_PRIORITY
#define CAN_IRQ_PRI_VAL_3 BSP_CAN3_IRQ_PRIORITY
#else
#define CAN_IRQ_PRI_VAL_3 1
#endif

#define CAN_IRQ_PRI_VAL(n) CAN_IRQ_PRI_VAL_##n

#define CAN_UNITED   (0UL)
#define CAN_INITED   (1UL)
#define CAN_RUNNING  (2UL)
#define CAN_STOPPED  (3UL)

/*
 * CAN Device Definition Macro
 * This macro creates a complete CAN device structure and its associated ISR.
 * It reduces code duplication by generating device-specific code for each CAN controller.
 *
 * @param n CAN controller number (0-3)
 */
#ifndef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
#define CAN_DEVICE_DEFINE(n)                                  \
    static hpm_can_t dev_can##n =                             \
    {                                                         \
        .can_base = HPM_CAN##n,                               \
        .name = "can" #n,                                     \
        .irq_num = IRQn_CAN##n,                               \
        .fifo_index = n,                                      \
        .clk_name = clock_can##n,                             \
        .irq_priority = CAN_IRQ_PRI_VAL(n),                   \
    };                                                        \
    SDK_DECLARE_EXT_ISR_M(IRQn_CAN##n, can##n##_isr);         \
    void can##n##_isr(void)                                   \
    {                                                         \
        hpm_can_isr(&dev_can##n);                             \
    }
#else
#define CAN_DEVICE_DEFINE(n)                                  \
    static hpm_can_t dev_can##n =                             \
    {                                                         \
        .can_base = HPM_CAN##n,                               \
        .name = "can" #n,                                     \
        .irq_num = IRQn_CAN##n,                               \
        .fifo_index = n,                                      \
        .clk_name = clock_can##n,                             \
        .irq_priority = CAN_IRQ_PRI_VAL(n),                   \
    };
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */

/*
 * Common Pattern Macros
 * These macros simplify repetitive code patterns throughout the driver.
 */

/* Macro to extract CAN driver context from RT-Thread device structure */
#define CAN_GET_DRV(can) \
    hpm_can_t *drv_can = (hpm_can_t*) can->parent.user_data; \
    RT_ASSERT(drv_can)

/* Interrupt mask definitions for different CAN event types */
#define CAN_RX_IRQ_MASK (CAN_EVENT_RECEIVE | CAN_EVENT_RX_BUF_ALMOST_FULL | CAN_EVENT_RX_BUF_FULL | CAN_EVENT_RX_BUF_OVERRUN)
#define CAN_TX_IRQ_MASK (CAN_EVENT_TX_PRIMARY_BUF | CAN_EVENT_TX_SECONDARY_BUF)
#define CAN_ERR_IRQ_MASK (CAN_ERROR_ARBITRATION_LOST_INT_ENABLE | CAN_ERROR_PASSIVE_INT_ENABLE | CAN_ERROR_BUS_ERROR_INT_ENABLE)

/**
 * @brief HPM CAN driver context structure
 *
 * This structure contains all the necessary information to manage a CAN controller,
 * including hardware registers, configuration, and RT-Thread device interface.
 */
typedef struct _hpm_can_struct
{
    CAN_Type *can_base;                                     /**< CAN hardware base address */
    const char *name;                                       /**< CAN device name (e.g., "can0", "can1") */
    rt_int32_t irq_num;                                        /**< CAN interrupt number */
    rt_uint8_t irq_priority;                                   /**< CAN interrupt priority */
    clock_name_t clk_name;                                  /**< CAN clock source name */
    rt_uint32_t fifo_index;                                    /**< FIFO index (used for RT-Thread framework compatibility) */
    can_config_t can_config;                                /**< HPM CAN hardware configuration */
    struct rt_can_device can_dev;                           /**< RT-Thread CAN device structure */
    rt_uint32_t filter_num;                                    /**< Number of active hardware filters */
    can_filter_config_t filter_list[CAN_FILTER_NUM_MAX];    /**< Array of hardware filter configurations */
    rt_uint8_t can_stat;                /**< CAN status */
} hpm_can_t;

/* ============================================================================
 * Function Declarations
 * ============================================================================ */

/**
 * @brief Configure CAN controller with specified parameters
 *
 * This function configures the CAN controller with the provided configuration
 * including baud rate, mode, timing parameters, and filter settings.
 *
 * @param [in/out] can Pointer to RT-Thread CAN device structure
 * @param [in] cfg Pointer to CAN configuration structure
 * @retval RT_EOK Configuration successful
 * @retval -RT_ERROR Configuration failed
 */
static rt_err_t hpm_can_configure(struct rt_can_device *can, struct can_configure *cfg);

/**
 * @brief Control CAN device and get/set various parameters
 *
 * This function handles various control commands including:
 * - Interrupt enable/disable
 * - Filter configuration
 * - Mode changes
 * - Baud rate changes
 * - Status retrieval
 *
 * @param [in/out] can Pointer to RT-Thread CAN device structure
 * @param [in] cmd Control command (see RT_CAN_CMD_* definitions)
 * @param [in/out] arg Command argument (input/output depending on command)
 * @retval RT_EOK Command executed successfully
 * @retval -RT_ERROR Invalid command or argument
 */
static rt_err_t hpm_can_control(struct rt_can_device *can, int cmd, void *arg);

/**
 * @brief Send CAN message
 *
 * This function transmits a CAN message using the hardware transmission buffers.
 * It supports both standard and extended frame formats, as well as CAN FD.
 *
 * @param [in] can Pointer to RT-Thread CAN device structure
 * @param [in] buf Pointer to CAN message structure
 * @param [in] boxno Mailbox number (not used in this implementation)
 * @retval RT_EOK Message sent successfully
 * @retval -RT_ETIMEOUT Transmission timeout
 * @retval -RT_EFULL Transmission buffer full
 */
static int hpm_can_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t boxno);

/**
 * @brief Receive CAN message
 *
 * This function receives a CAN message from the hardware receive FIFO.
 * It handles both standard and extended frame formats, as well as CAN FD.
 *
 * @param [in] can Pointer to RT-Thread CAN device structure
 * @param [out] buf Pointer to buffer for received CAN message
 * @param [in] boxno Mailbox number (not used in this implementation)
 * @retval RT_EOK Message received successfully
 * @retval -RT_ERROR Error during reception
 * @retval -RT_EMPTY No data available in receive FIFO
 */
static int hpm_can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t boxno);

/**
 * @brief CAN interrupt service routine
 *
 * This function handles all CAN-related interrupts including:
 * - Transmission completion
 * - Reception of new messages
 * - Error conditions
 * - FIFO overflow
 *
 * @param [in] hpm_can Pointer to HPM CAN driver context
 */
#ifndef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
static void hpm_can_isr(hpm_can_t *hpm_can);
#else
static void hpm_can_isr(int vector, hpm_can_t *hpm_can);
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */

/**
 * @brief Convert DLC (Data Length Code) to actual data bytes
 *
 * This function converts the CAN DLC field to the actual number of data bytes.
 * It handles both CAN 2.0 (up to 8 bytes) and CAN FD (up to 64 bytes) formats.
 *
 * @param [in] dlc Data Length Code from CAN frame
 * @return Number of actual data bytes
 */
static uint8_t can_get_data_bytes_from_dlc(uint32_t dlc);

/**
 * @brief Update CAN error status from hardware registers
 *
 * This function reads the current error status from the CAN hardware registers
 * and updates the driver's error status structure with the latest information.
 *
 * @param [in] hpm_can Pointer to HPM CAN driver context
 */
static void can_update_error_status(hpm_can_t *hpm_can);

/* ============================================================================
 * CAN Device Instances
 * ============================================================================ */

/* CAN0 device instance - created if HPM_CAN0_BASE is defined and BSP_USING_CAN0 is enabled */
#if defined(HPM_CAN0_BASE) && defined(BSP_USING_CAN0)
CAN_DEVICE_DEFINE(0)
#endif

/* CAN1 device instance - created if HPM_CAN1_BASE is defined and BSP_USING_CAN1 is enabled */
#if defined(HPM_CAN1_BASE) && defined(BSP_USING_CAN1)
CAN_DEVICE_DEFINE(1)
#endif

/* CAN2 device instance - created if HPM_CAN2_BASE is defined and BSP_USING_CAN2 is enabled */
#if defined(HPM_CAN2_BASE) && defined(BSP_USING_CAN2)
CAN_DEVICE_DEFINE(2)
#endif

/* CAN3 device instance - created if HPM_CAN3_BASE is defined and BSP_USING_CAN3 is enabled */
#if defined(HPM_CAN3_BASE) && defined(BSP_USING_CAN3)
CAN_DEVICE_DEFINE(3)
#endif

/* Array of CAN device pointers - used for initialization and management */
static hpm_can_t *hpm_cans[] = {
#if defined(HPM_CAN0_BASE) && defined(BSP_USING_CAN0)
        &dev_can0,
#endif
#if defined(HPM_CAN1_BASE) && defined(BSP_USING_CAN1)
        &dev_can1,
#endif
#if defined(HPM_CAN2_BASE) && defined(BSP_USING_CAN2)
        &dev_can2,
#endif
#if defined(HPM_CAN3_BASE) && defined(BSP_USING_CAN3)
        &dev_can3,
#endif
        };

/* RT-Thread CAN operations structure - defines the interface between RT-Thread and this driver */
static const struct rt_can_ops hpm_can_ops = {
        .configure = hpm_can_configure,    /* Configure CAN controller */
        .control = hpm_can_control,        /* Control CAN device operations */
        .sendmsg = hpm_can_sendmsg,        /* Send CAN message */
        .recvmsg = hpm_can_recvmsg,        /* Receive CAN message */
};



/* ============================================================================
 * Function Implementations
 * ============================================================================ */

/**
 * @brief CAN interrupt service routine
 *
 * This function is called when a CAN interrupt occurs. It handles various
 * interrupt types including transmission completion, reception, and errors.
 *
 * @param [in] hpm_can Pointer to HPM CAN driver context
 */
#ifndef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
static void hpm_can_isr(hpm_can_t *hpm_can)
#else
static void hpm_can_isr(int vector, hpm_can_t *hpm_can)
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */
{
    /* Read interrupt flags from hardware */
    uint8_t tx_rx_flags = can_get_tx_rx_flags(hpm_can->can_base);
    uint8_t error_flags = can_get_error_interrupt_flags(hpm_can->can_base);

    /* Handle high-priority message transmission completion */
    if ((tx_rx_flags & CAN_EVENT_TX_PRIMARY_BUF) != 0U)
    {
        rt_hw_can_isr(&hpm_can->can_dev, RT_CAN_EVENT_TX_DONE | (0UL << 8));
    }

    /* Handle normal priority message transmission completion */
    if ((tx_rx_flags & CAN_EVENT_TX_SECONDARY_BUF) != 0U)
    {
        rt_hw_can_isr(&hpm_can->can_dev, RT_CAN_EVENT_TX_DONE | (0UL << 8));
    }

    /* Handle new message reception */
    if (((tx_rx_flags & CAN_EVENT_RECEIVE) == CAN_EVENT_RECEIVE) && ((hpm_can->can_stat != CAN_STOPPED) || (hpm_can->can_stat != CAN_UNITED)))
    {
        rt_hw_can_isr(&hpm_can->can_dev, RT_CAN_EVENT_RX_IND | (hpm_can->fifo_index << 8));
    }

    /* Handle receive FIFO overflow */
    if (((tx_rx_flags & CAN_EVENT_RX_BUF_OVERRUN) != 0U) && ((hpm_can->can_stat != CAN_STOPPED) || (hpm_can->can_stat != CAN_UNITED)))
    {
        rt_hw_can_isr(&hpm_can->can_dev, RT_CAN_EVENT_RXOF_IND | (hpm_can->fifo_index << 8));
    }

    /* Handle CAN bus errors */
    if (((tx_rx_flags & CAN_EVENT_ERROR) != 0U) || (error_flags != 0U))
    {
        /* Get the specific error type and update error counters */
        uint8_t err_kind = can_get_last_error_kind(hpm_can->can_base);
        switch(err_kind)
        {
        case CAN_KIND_OF_ERROR_ACK_ERROR:
            hpm_can->can_dev.status.ackerrcnt++;
            break;
        case CAN_KIND_OF_ERROR_BIT_ERROR:
            hpm_can->can_dev.status.biterrcnt++;
            break;
        case CAN_KIND_OF_ERROR_CRC_ERROR:
            hpm_can->can_dev.status.crcerrcnt++;
            break;
        case CAN_KIND_OF_ERROR_FORM_ERROR:
            hpm_can->can_dev.status.formaterrcnt++;
            break;
        case CAN_KIND_OF_ERROR_STUFF_ERROR:
            hpm_can->can_dev.status.bitpaderrcnt++;
            break;
        }

        /* Update error status from hardware registers */
        can_update_error_status(hpm_can);
    }

    /* Clear processed interrupt flags */
    can_clear_tx_rx_flags(hpm_can->can_base, tx_rx_flags);
    can_clear_error_interrupt_flags(hpm_can->can_base, error_flags);
}

/**
 * @brief Configure CAN controller with specified parameters
 *
 * This function configures the CAN controller with the provided configuration
 * including baud rate, mode, timing parameters, and filter settings.
 *
 * @param [in/out] can Pointer to RT-Thread CAN device structure
 * @param [in] cfg Pointer to CAN configuration structure
 * @retval RT_EOK Configuration successful
 * @retval -RT_ERROR Configuration failed
 */
static rt_err_t hpm_can_configure(struct rt_can_device *can, struct can_configure *cfg)
{
    RT_ASSERT(can);
    RT_ASSERT(cfg);

    CAN_GET_DRV(can);

#ifdef RT_CAN_USING_CANFD
    drv_can->can_config.enable_canfd = (cfg->enable_canfd != 0) ? true : false;
    if (cfg->use_bit_timing != 0U)
    {
        drv_can->can_config.use_lowlevel_timing_setting = true;
        drv_can->can_config.can_timing.prescaler = cfg->can_timing.prescaler;
        drv_can->can_config.can_timing.num_seg1 = cfg->can_timing.num_seg1;
        drv_can->can_config.can_timing.num_seg2 = cfg->can_timing.num_seg2;
        drv_can->can_config.can_timing.num_sjw = cfg->can_timing.num_sjw;

        drv_can->can_config.canfd_timing.prescaler = cfg->canfd_timing.prescaler;
        drv_can->can_config.canfd_timing.num_seg1 = cfg->canfd_timing.num_seg1;
        drv_can->can_config.canfd_timing.num_seg2 = cfg->canfd_timing.num_seg2;
        drv_can->can_config.canfd_timing.num_sjw = cfg->canfd_timing.num_sjw;
    }
    else
#endif
    {
        drv_can->can_config.use_lowlevel_timing_setting = false;
        drv_can->can_config.baudrate = cfg->baud_rate;
#ifdef RT_CAN_USING_CANFD
        drv_can->can_config.baudrate_fd = cfg->baud_rate_fd;
#endif
    }


    switch (cfg->mode)
    {
    case RT_CAN_MODE_NORMAL:
        drv_can->can_config.mode = can_mode_normal;
        break;
    case RT_CAN_MODE_LISTEN:
        drv_can->can_config.mode = can_mode_listen_only;
        break;
    case RT_CAN_MODE_LOOPBACK:
        drv_can->can_config.mode = can_mode_loopback_internal;
        break;
    default:
        return -RT_ERROR;
        break;
    }

    drv_can->can_config.enable_tx_buffer_priority_mode = (cfg->privmode != 0U) ? true : false;
    init_can_pins(drv_can->can_base);
    clock_add_to_group(drv_can->clk_name, BOARD_RUNNING_CORE & 0x1);
    uint32_t can_clk = clock_get_frequency(drv_can->clk_name);
    drv_can->can_config.filter_list_num = drv_can->filter_num;
    drv_can->can_config.filter_list = &drv_can->filter_list[0];
    hpm_stat_t status = can_init(drv_can->can_base, &drv_can->can_config, can_clk);
    if (status != status_success)
    {
        return -RT_ERROR;
    }
    drv_can->can_stat = CAN_INITED;
    return RT_EOK;
}

static rt_err_t hpm_can_control(struct rt_can_device *can, int cmd, void *arg)
{
    RT_ASSERT(can);

    CAN_GET_DRV(can);

    uint32_t arg_val;
    rt_err_t err = RT_EOK;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        arg_val = (uint32_t) arg;
        intc_m_disable_irq(drv_can->irq_num);
        if (arg_val & RT_DEVICE_FLAG_INT_RX) {
            drv_can->can_config.irq_txrx_enable_mask &= (uint8_t)~CAN_RX_IRQ_MASK;
            can_disable_tx_rx_irq(drv_can->can_base, CAN_RX_IRQ_MASK);
        }
        if (arg_val & RT_DEVICE_FLAG_INT_TX) {
            drv_can->can_config.irq_txrx_enable_mask &= (uint8_t)~CAN_TX_IRQ_MASK;
            can_disable_tx_rx_irq(drv_can->can_base, CAN_TX_IRQ_MASK);
        }
        if (arg_val & RT_DEVICE_CAN_INT_ERR) {
            uint8_t irq_txrx_mask = CAN_EVENT_ERROR;
            drv_can->can_config.irq_txrx_enable_mask &= (uint8_t)~irq_txrx_mask;
            drv_can->can_config.irq_error_enable_mask &= (uint8_t)~CAN_ERR_IRQ_MASK;
            can_disable_tx_rx_irq(drv_can->can_base, irq_txrx_mask);
            can_disable_error_irq(drv_can->can_base, CAN_ERR_IRQ_MASK);
        } else {
            err = -RT_ERROR;
        }
        break;
    case RT_DEVICE_CTRL_SET_INT:
        arg_val = (uint32_t) arg;
        if (arg_val & RT_DEVICE_FLAG_INT_RX) {
            drv_can->can_config.irq_txrx_enable_mask |= CAN_RX_IRQ_MASK;
            can_enable_tx_rx_irq(drv_can->can_base, CAN_RX_IRQ_MASK);
            intc_m_enable_irq_with_priority(drv_can->irq_num, drv_can->irq_priority);
        }
        if (arg_val & RT_DEVICE_FLAG_INT_TX) {
            drv_can->can_config.irq_txrx_enable_mask |= CAN_TX_IRQ_MASK;
            can_enable_tx_rx_irq(drv_can->can_base, CAN_TX_IRQ_MASK);
            intc_m_enable_irq_with_priority(drv_can->irq_num, drv_can->irq_priority);
        }
        if (arg_val & RT_DEVICE_CAN_INT_ERR) {
            uint8_t irq_txrx_mask = CAN_EVENT_ERROR;
            drv_can->can_config.irq_txrx_enable_mask |= irq_txrx_mask;
            drv_can->can_config.irq_error_enable_mask |= CAN_ERR_IRQ_MASK;
            can_enable_tx_rx_irq(drv_can->can_base, irq_txrx_mask);
            can_enable_error_irq(drv_can->can_base, CAN_ERR_IRQ_MASK);
            intc_m_enable_irq_with_priority(drv_can->irq_num, drv_can->irq_priority);
        } else {
            err = -RT_ERROR;
        }
        break;
    case RT_CAN_CMD_SET_FILTER:
        {
            /* Convert the RT-Thread Filter format to the filter format supported by HPM CAN */
            struct rt_can_filter_config *filter = (struct rt_can_filter_config*)arg;
            if (filter != NULL)
            {
                drv_can->filter_num = filter->count;
                RT_ASSERT(filter->count <= CAN_FILTER_NUM_MAX);
                for (uint32_t i=0; i<filter->count; i++)
                {
                    drv_can->filter_list[i].index = i;
                    drv_can->filter_list[i].enable = (filter->actived != 0U) ? true : false;
                    drv_can->filter_list[i].code = filter->items[i].id;
                    drv_can->filter_list[i].id_mode = (filter->items[i].ide != 0U) ? can_filter_id_mode_extended_frames : can_filter_id_mode_standard_frames;
                    drv_can->filter_list[i].mask = (~filter->items[i].mask) & ~(7UL <<29);
                }
            }
            else
            {
                drv_can->filter_num = 0;
            }
            err = hpm_can_configure(can, &drv_can->can_dev.config);
#ifdef RT_CAN_USING_HDR
            if (filter == RT_NULL) {
                /*if use RT_CAN_USING_HDR, but if want to receive everything without filtering, use default filter, need to return NO-RT-OK status*/
                err = -RT_ETRAP;
            }
#endif
        }
        break;
    case RT_CAN_CMD_SET_MODE:
        arg_val = (uint32_t) arg;
        if ((arg_val != RT_CAN_MODE_NORMAL) && (arg_val != RT_CAN_MODE_LISTEN) && (arg_val != RT_CAN_MODE_LOOPBACK))
        {
            err = -RT_ERROR;
            break;
        }
        if (arg_val != drv_can->can_dev.config.mode)
        {
            drv_can->can_dev.config.mode = arg_val;
            err = hpm_can_configure(can, &drv_can->can_dev.config);
        }

        break;
    case RT_CAN_CMD_SET_BAUD:
        arg_val = (uint32_t) arg;
        if (arg_val != drv_can->can_dev.config.baud_rate)
        {
            drv_can->can_dev.config.baud_rate = arg_val;
        }
        err = hpm_can_configure(can, &drv_can->can_dev.config);
        break;
#ifdef RT_CAN_USING_CANFD
    case RT_CAN_CMD_SET_CANFD:
        arg_val = (uint32_t) arg;
        if (arg_val != drv_can->can_dev.config.enable_canfd)
        {
            drv_can->can_dev.config.enable_canfd = arg_val;
            err = hpm_can_configure(can, &drv_can->can_dev.config);
        }
        break;
    case RT_CAN_CMD_SET_BAUD_FD:
        arg_val = (uint32_t) arg;
        if (arg_val != drv_can->can_dev.config.baud_rate_fd)
        {
            drv_can->can_dev.config.baud_rate_fd = arg_val;
            err = hpm_can_configure(can, &drv_can->can_dev.config);
        }
        break;
    case RT_CAN_CMD_SET_BITTIMING:
        {
            struct rt_can_bit_timing_config *timing_configs = (struct rt_can_bit_timing_config*)arg;
            if ((timing_configs == RT_NULL) || (timing_configs->count < 1) || (timing_configs->count > 2))
            {
                return -RT_ERROR;
            }

            if (timing_configs->count != 0U)
            {
                drv_can->can_dev.config.can_timing = timing_configs->items[0];
            }
            if (timing_configs->count == 2)
            {
                drv_can->can_dev.config.canfd_timing = timing_configs->items[1];
            }
            err = hpm_can_configure(can, &drv_can->can_dev.config);
        }
        break;
#endif
    case RT_CAN_CMD_SET_PRIV:
        arg_val = (uint32_t)arg;
        if ((arg_val != RT_CAN_MODE_PRIV) && (arg_val != RT_CAN_MODE_NOPRIV))
        {
            return -RT_ERROR;
        }
        if (arg_val != drv_can->can_dev.config.privmode)
        {
            drv_can->can_dev.config.privmode = arg_val;
            err = hpm_can_configure(can, &drv_can->can_dev.config);
        }
        break;
    case RT_CAN_CMD_GET_STATUS:
        can_update_error_status(drv_can);
        rt_memcpy(arg, &drv_can->can_dev.status, sizeof(drv_can->can_dev.status));
        break;
    case RT_CAN_CMD_START:
        arg_val = (rt_uint32_t)arg;
        if (arg_val == 0) {
            can_deinit(drv_can->can_base);
            drv_can->can_stat = CAN_STOPPED;
        } else {
            if (can_init(drv_can->can_base, &drv_can->can_config, clock_get_frequency(drv_can->clk_name)) != status_success) {
                err = -RT_ERROR;
            } else {
                drv_can->can_stat = CAN_RUNNING;
            }
        }
        break;
    }
    return err;
}

static int hpm_can_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t boxno)
{
    RT_ASSERT(can);

    CAN_GET_DRV(can);

    struct rt_can_msg *can_msg = (struct rt_can_msg *) buf;

    if ((drv_can->can_stat == CAN_UNITED) || (drv_can->can_stat == CAN_STOPPED)) {
        return -RT_ERROR;
    }

    can_transmit_buf_t tx_buf = { 0 };
    tx_buf.id = can_msg->id;
    if (can_msg->ide == RT_CAN_STDID)
    {
        tx_buf.extend_id = false;
    }
    else
    {
        tx_buf.extend_id = true;
    }

    if (can_msg->rtr == RT_CAN_DTR)
    {
        tx_buf.remote_frame = false;
    }
    else
    {
        tx_buf.remote_frame = true;
    }

#ifdef RT_CAN_USING_CANFD
    tx_buf.bitrate_switch = can_msg->brs;
    if (can_msg->fd_frame != 0)
    {
        tx_buf.canfd_frame = 1;
        RT_ASSERT(can_msg->len <= 15);
    }
    else
#endif
    {
        RT_ASSERT(can_msg->len <= 8);
    }

    uint32_t msg_len = can_get_data_bytes_from_dlc(can_msg->len);
    for (uint32_t i = 0; i < msg_len; i++)
    {
        tx_buf.data[i] = can_msg->data[i];
    }
    tx_buf.dlc = can_msg->len;

    uint32_t delay_cnt = 0;

   if (can_msg->priv != 0U)
    {
        while (can_is_primary_transmit_buffer_full(drv_can->can_base))
        {
            rt_thread_mdelay(1);
            delay_cnt++;
            if (delay_cnt >= CAN_SEND_WAIT_MS_MAX)
            {
                return -RT_ETIMEOUT;
            }
        }
        hpm_stat_t status = can_send_message_nonblocking(drv_can->can_base, &tx_buf);
        if (status != status_success)
        {
            return -RT_EFULL;
        }
    }
    else
    {
        while (can_is_secondary_transmit_buffer_full(drv_can->can_base))
        {
            rt_thread_mdelay(1);
            delay_cnt++;
            if (delay_cnt >= CAN_SEND_WAIT_MS_MAX)
            {
                return -RT_ETIMEOUT;
            }
        }
        hpm_stat_t status = can_send_message_nonblocking(drv_can->can_base, &tx_buf);
        if (status != status_success)
        {
            return -RT_EFULL;
        }
    }

    return RT_EOK;
}

static int hpm_can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t boxno)
{
    RT_ASSERT(can);

    CAN_GET_DRV(can);

    rt_can_msg_t can_msg = (rt_can_msg_t)buf;

    if (can_is_data_available_in_receive_buffer(drv_can->can_base)) {
        can_receive_buf_t rx_buf;
        hpm_stat_t status = can_read_received_message(drv_can->can_base, &rx_buf);
        if (status != status_success) {
            return -RT_ERROR;
        }

        if (rx_buf.extend_id != 0) {
            can_msg->ide = RT_CAN_EXTID;
        }
        else {
            can_msg->ide = RT_CAN_STDID;
        }
        can_msg->id = rx_buf.id;

        if (rx_buf.remote_frame != 0) {
            can_msg->rtr = RT_CAN_RTR;
        }
        else {
            can_msg->rtr = RT_CAN_DTR;
        }
#ifdef RT_CAN_USING_CANFD
        can_msg->fd_frame = rx_buf.canfd_frame;
        can_msg->brs = rx_buf.bitrate_switch;
#endif
        can_msg->len = rx_buf.dlc;
        uint32_t msg_len = can_get_data_bytes_from_dlc(can_msg->len);
        for(uint32_t i = 0; i < msg_len; i++) {
            can_msg->data[i] = rx_buf.data[i];
        }
#ifdef RT_CAN_USING_HDR
        /* Hardware filter messages are valid */
        can_msg->hdr_index = boxno;
        can->hdr[can_msg->hdr_index].connected = 1;
#endif
    }
    else {
        return -RT_EEMPTY;
    }

    return RT_EOK;
}

static void can_update_error_status(hpm_can_t *hpm_can)
{
    hpm_can->can_dev.status.rcverrcnt = can_get_receive_error_count(hpm_can->can_base);
    hpm_can->can_dev.status.snderrcnt = can_get_transmit_error_count(hpm_can->can_base);
    hpm_can->can_dev.status.lasterrtype = can_get_last_error_kind(hpm_can->can_base);
    hpm_can->can_dev.status.errcode = 0;

    uint32_t temp = can_get_error_interrupt_flags(hpm_can->can_base);
    if ((temp & CAN_ERROR_WARNING_LIMIT_FLAG) != 0U)
    {
        hpm_can->can_dev.status.errcode |= ERRWARNING;
    }
    if ((temp & CAN_ERROR_PASSIVE_INT_FLAG) != 0U)
    {
        hpm_can->can_dev.status.errcode |= ERRPASSIVE;
    }
    if (can_is_in_bus_off_mode(hpm_can->can_base))
    {
        hpm_can->can_dev.status.errcode |= BUSOFF;
    }
}

static uint8_t can_get_data_bytes_from_dlc(uint32_t dlc)
{
    uint32_t data_bytes = 0;

    dlc &= 0xFU;
    if (dlc <= 8U) {
        data_bytes = dlc;
    } else {
        switch (dlc) {
            case can_payload_size_12:
                data_bytes = 12U;
                break;
            case can_payload_size_16:
                data_bytes = 16U;
                break;
            case can_payload_size_20:
                data_bytes = 20U;
                break;
            case can_payload_size_24:
                data_bytes = 24U;
                break;
            case can_payload_size_32:
                data_bytes = 32U;
                break;
            case can_payload_size_48:
                data_bytes = 48U;
                break;
            case can_payload_size_64:
                data_bytes = 64U;
                break;
            default:
                /* Code should never touch here */
                break;
        }
    }

    return data_bytes;
}

/* ============================================================================
 * Driver Initialization
 * ============================================================================ */

/**
 * @brief Initialize CAN hardware drivers
 *
 * This function initializes all available CAN controllers and registers them
 * with the RT-Thread device framework. It sets up default configurations
 * and prepares the hardware for operation.
 *
 * @retval RT_EOK Initialization successful
 */
int rt_hw_can_init(void)
{
    /* Set up default CAN configuration */
    struct can_configure config = CANDEFAULTCONFIG;
    config.privmode = RT_CAN_MODE_NOPRIV;      /* Disable private mode by default */
    config.sndboxnumber = CAN_SENDBOX_NUM;     /* Set number of send mailboxes */
    config.ticks = 50;                         /* Set timeout ticks */

#ifdef RT_CAN_USING_HDR
    config.maxhdr = 16;                        /* Set maximum number of hardware filters */
#endif

    /* Initialize each available CAN controller */
    for (uint32_t i = 0; i < ARRAY_SIZE(hpm_cans); i++)
    {
        /* Set default configuration */
        hpm_cans[i]->can_dev.config = config;
        hpm_cans[i]->filter_num = 0;           /* No filters active initially */
        hpm_cans[i]->can_stat = CAN_UNITED; /* Set initial status */

        /* Get default hardware configuration from HPM SDK */
        can_get_default_config(&hpm_cans[i]->can_config);

        /* Register CAN device with RT-Thread */
        rt_hw_can_register(&hpm_cans[i]->can_dev, hpm_cans[i]->name, &hpm_can_ops, hpm_cans[i]);

#ifdef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
        /* Register CAN device to irq table */
        rt_hw_interrupt_install(hpm_cans[i]->irq_num, (rt_isr_handler_t)hpm_can_isr, hpm_cans[i], hpm_cans[i]->name);
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */
    }

    return RT_EOK;
}

/* Register initialization function to be called during system startup */
INIT_BOARD_EXPORT(rt_hw_can_init);

#endif /* RT_USING_CAN */
