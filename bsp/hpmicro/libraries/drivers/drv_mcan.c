

/*
 * Copyright (c) 2023-2025 HPMicro
 * SPDX-License-Identifier: BSD-3-Clause
 * @file drv_mcan.c
 * @brief MCAN (CAN-FD) driver implementation for RT-Thread
 *
 * This file implements the MCAN (CAN with Flexible Data-rate) driver for HPMicro
 * microcontrollers, supporting up to 8 MCAN instances (MCAN0-MCAN7). The driver
 * provides both classic CAN and CAN-FD functionality with configurable bit rates,
 * message filtering, and interrupt handling.
 *
 * Features:
 * - Support for up to 8 MCAN controllers (MCAN0-MCAN7)
 * - CAN 2.0A/B and CAN FD support
 * - Hardware filtering with up to 128 standard and 64 extended filters
 * - Interrupt-driven operation
 * - Error handling and status reporting
 * - Configurable baud rates and timing parameters
 * - AHB RAM message buffer support for improved performance
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-07     HPMicro      the first version
 * 2024-05-31     HPMicro      add MCAN4-7 support
 * 2025-09-01     HPMicro      remove repetitive codes and optimize the implementation
 */

#include "rtconfig.h"

#ifdef RT_USING_CAN

/* ============================================================================
 * Include Files
 * ============================================================================ */

/* HPMicro SDK includes */
#include "board.h"                    /* Board support package definitions */
#include "hpm_clock_drv.h"            /* Clock management functions */
#include "hpm_mcan_drv.h"             /* MCAN hardware abstraction layer */

/* RT-Thread includes */
#include <rtdevice.h>                 /* RT-Thread device framework */
#include <rthw.h>                     /* RT-Thread hardware abstraction */
#include <rtthread.h>                 /* RT-Thread core services */

/* ============================================================================
 * Configuration Constants
 * ============================================================================ */

#define CAN_SEND_WAIT_MS_MAX   (1000U) /* CAN maximum wait time for transmission */
#define CAN_SENDBOX_NUM        (1U)    /* CAN Hardware Transmission buffer number */
#define CAN_STD_FILTER_NUM_MAX (128U)  /* std Filter number */
#define CAN_EXT_FILTER_NUM_MAX (64U)   /* ext Filter number */

#define CAN_STD_ID_MASK      (0x7FFU)
#define CAN_EXT_ID_MASK      (0x1FFFFFFFUL)

/* ============================================================================
 * IRQ Priority Configuration Macros
 * ============================================================================ */

/**
 * @brief MCAN IRQ Priority Configuration Macros
 *
 * These macros provide a flexible way to configure IRQ priorities for each MCAN
 * instance. Each macro checks if a BSP-specific priority is defined, otherwise
 * defaults to priority 1.
 *
 * Usage:
 * - MCAN_IRQ_PRI_VAL_0 through MCAN_IRQ_PRI_VAL_7: Get priority for specific instance
 * - MCAN_IRQ_PRI_VAL(n): Generic macro to get priority for instance n
 */

/* MCAN IRQ Priority Configuration Macros */
#ifdef BSP_MCAN0_IRQ_PRIORITY
#define MCAN_IRQ_PRI_VAL_0 BSP_MCAN0_IRQ_PRIORITY
#else
#define MCAN_IRQ_PRI_VAL_0 1
#endif

#ifdef BSP_MCAN1_IRQ_PRIORITY
#define MCAN_IRQ_PRI_VAL_1 BSP_MCAN1_IRQ_PRIORITY
#else
#define MCAN_IRQ_PRI_VAL_1 1
#endif

#ifdef BSP_MCAN2_IRQ_PRIORITY
#define MCAN_IRQ_PRI_VAL_2 BSP_MCAN2_IRQ_PRIORITY
#else
#define MCAN_IRQ_PRI_VAL_2 1
#endif

#ifdef BSP_MCAN3_IRQ_PRIORITY
#define MCAN_IRQ_PRI_VAL_3 BSP_MCAN3_IRQ_PRIORITY
#else
#define MCAN_IRQ_PRI_VAL_3 1
#endif

#ifdef BSP_MCAN4_IRQ_PRIORITY
#define MCAN_IRQ_PRI_VAL_4 BSP_MCAN4_IRQ_PRIORITY
#else
#define MCAN_IRQ_PRI_VAL_4 1
#endif

#ifdef BSP_MCAN5_IRQ_PRIORITY
#define MCAN_IRQ_PRI_VAL_5 BSP_MCAN5_IRQ_PRIORITY
#else
#define MCAN_IRQ_PRI_VAL_5 1
#endif

#ifdef BSP_MCAN6_IRQ_PRIORITY
#define MCAN_IRQ_PRI_VAL_6 BSP_MCAN6_IRQ_PRIORITY
#else
#define MCAN_IRQ_PRI_VAL_6 1
#endif

#ifdef BSP_MCAN7_IRQ_PRIORITY
#define MCAN_IRQ_PRI_VAL_7 BSP_MCAN7_IRQ_PRIORITY
#else
#define MCAN_IRQ_PRI_VAL_7 1
#endif

/** @brief Generic macro to get IRQ priority for MCAN instance n */
#define MCAN_IRQ_PRI_VAL(n) MCAN_IRQ_PRI_VAL_##n

#define CAN_UNITED   (0UL)
#define CAN_INITED   (1UL)
#define CAN_RUNNING  (2UL)
#define CAN_STOPPED  (3UL)


/* ============================================================================
 * Data Structures
 * ============================================================================ */

/**
 * @brief HPM MCAN device structure
 *
 * This structure contains all the necessary information for managing a single
 * MCAN instance, including hardware configuration, RT-Thread device integration,
 * and message filtering capabilities.
 */
typedef struct _hpm_can_struct {
    MCAN_Type *can_base;               /**< MCAN hardware base address */
    const char *name;                  /**< Device name (e.g., "can0", "can1") */
    rt_int32_t irq_num;                   /**< Interrupt number for this MCAN instance */
    rt_uint8_t irq_priority;              /**< Interrupt priority for this MCAN instance */
    clock_name_t clk_name;             /**< Clock source name for this MCAN instance */
    rt_uint32_t fifo_index;               /**< FIFO index (used for RT-Thread framework compatibility) */
    rt_uint32_t ram_base;                 /**< Message buffer RAM base address (NULL for HPM6200) */
    rt_uint32_t ram_size;                 /**< Message buffer RAM size (0 for HPM6200) */
    mcan_config_t can_config;          /**< MCAN hardware configuration structure */
    struct rt_can_device can_dev;      /**< RT-Thread CAN device structure */
    rt_uint32_t irq_txrx_err_enable_mask; /**< Bitmask for enabled TX/RX/Error interrupts */
    rt_uint32_t std_filter_num;           /**< Number of configured standard ID filters */
    mcan_filter_elem_t std_can_filters[CAN_STD_FILTER_NUM_MAX]; /**< Standard ID filter array */
    rt_uint32_t ext_filter_num;           /**< Number of configured extended ID filters */
    mcan_filter_elem_t ext_can_filters[CAN_EXT_FILTER_NUM_MAX]; /**< Extended ID filter array */
    rt_uint32_t can_tx_fifo_index;       /**< CAN TX FIFO index */
    rt_uint8_t can_stat;                /**< CAN status */
} hpm_can_t;

/* ============================================================================
 * Default Filter Configurations
 * ============================================================================ */

/**
 * @brief Default standard ID filter configuration
 *
 * This filter accepts all standard ID messages and stores them in RXFIFO0.
 * Used when no specific filters are configured by the application.
 */
static const mcan_filter_elem_t k_default_std_id_filter = {
    .filter_type = MCAN_FILTER_TYPE_CLASSIC_FILTER,                    /**< Use classic filter type */
    .filter_config = MCAN_FILTER_ELEM_CFG_STORE_IN_RX_FIFO0_IF_MATCH, /**< Store in RXFIFO0 on match */
    .can_id_type = MCAN_CAN_ID_TYPE_STANDARD,                          /**< Standard 11-bit ID */
    .sync_message = 0U,                                                /**< Not a sync message */
    .filter_id = 0U,                                                   /**< Filter ID (don't care) */
    .filter_mask = 0U,                                                 /**< Accept all messages */
};

/**
 * @brief Default extended ID filter configuration
 *
 * This filter accepts all extended ID messages and stores them in RXFIFO0.
 * Used when no specific filters are configured by the application.
 */
static const mcan_filter_elem_t k_default_ext_id_filter = {
    .filter_type = MCAN_FILTER_TYPE_CLASSIC_FILTER,                    /**< Use classic filter type */
    .filter_config = MCAN_FILTER_ELEM_CFG_STORE_IN_RX_FIFO0_IF_MATCH, /**< Store in RXFIFO0 on match */
    .can_id_type = MCAN_CAN_ID_TYPE_EXTENDED,                          /**< Extended 29-bit ID */
    .sync_message = 0,                                                 /**< Not a sync message */
    .filter_id = 0,                                                    /**< Filter ID (don't care) */
    .filter_mask = 0U,                                                 /**< Accept all messages */
};

/* ============================================================================
 * Function Declarations
 * ============================================================================ */

/**
 * @brief Configure MCAN controller
 *
 * Initializes the MCAN hardware with the specified configuration including
 * baud rate, mode, and timing parameters.
 *
 * @param[in,out] can Pointer to RT-Thread CAN device structure
 * @param[in] cfg Pointer to CAN configuration structure
 * @return RT_EOK on success, -RT_ERROR on failure
 */
static rt_err_t hpm_mcan_configure(struct rt_can_device *can, struct can_configure *cfg);

/**
 * @brief Control MCAN device operations
 *
 * Handles various control commands including interrupt management, mode changes,
 * baud rate configuration, filter setup, and status retrieval.
 *
 * @param[in,out] can Pointer to RT-Thread CAN device structure
 * @param[in] cmd Control command (RT_DEVICE_CTRL_*, RT_CAN_CMD_*)
 * @param[in,out] arg Command-specific argument pointer
 * @return RT_EOK on success, -RT_ERROR on failure
 */
static rt_err_t hpm_mcan_control(struct rt_can_device *can, int cmd, void *arg);

/**
 * @brief Send CAN message
 *
 * Transmits a CAN message through the specified MCAN instance.
 * Supports both classic CAN and CAN-FD frames.
 *
 * @param[in] can Pointer to RT-Thread CAN device structure
 * @param[in] buf Pointer to CAN message buffer
 * @param[in] boxno Mailbox number (not used in this implementation)
 * @return RT_EOK on success, -RT_ETIMEOUT on timeout, -RT_EFULL if buffer full
 */
static rt_ssize_t hpm_mcan_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t boxno);

/**
 * @brief Receive CAN message
 *
 * Receives a CAN message from the MCAN RX FIFO.
 * Supports both classic CAN and CAN-FD frames.
 *
 * @param[in] can Pointer to RT-Thread CAN device structure
 * @param[out] buf Pointer to receive buffer for CAN message
 * @param[in] boxno Mailbox number (not used in this implementation)
 * @return RT_EOK on success, -RT_ERROR on error, -RT_EMPTY if no data
 */
static rt_ssize_t hpm_mcan_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t boxno);

/**
 * @brief MCAN interrupt service routine
 *
 * Handles all MCAN interrupts including transmission completion, reception,
 * FIFO overflow, and error conditions. Updates RT-Thread CAN device status.
 *
 * @param[in] hpm_can Pointer to HPM MCAN device structure
 */
#ifndef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
static void hpm_mcan_isr(hpm_can_t *hpm_can);
#else
static void hpm_mcan_isr(int vector, hpm_can_t *hpm_can);
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */

/**
 * @brief Convert DLC to data byte count
 *
 * Converts Data Length Code (DLC) to actual number of data bytes.
 * Handles both classic CAN (0-8 bytes) and CAN-FD (0-64 bytes) formats.
 *
 * @param[in] dlc Data Length Code value
 * @return Number of data bytes
 */
static uint8_t can_get_data_bytes_from_dlc(uint32_t dlc);

/* ============================================================================
 * Device Definition Macros
 * ============================================================================ */

/**
 * @brief Define MCAN device instance macro
 *
 * This macro creates a complete MCAN device instance including:
 * - Device structure initialization
 * - Interrupt service routine declaration
 * - ISR function implementation
 *
 * @param n MCAN instance number (0-7)
 */
#ifndef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
#define MCAN_DEFINE_DEVICE(n)                          \
    static hpm_can_t dev_can##n = {                    \
        .can_base = HPM_MCAN##n,                       \
        .name = "can" #n,                              \
        .irq_num = IRQn_MCAN##n,                       \
        .irq_priority = MCAN_IRQ_PRI_VAL(n),           \
        .fifo_index = n,                               \
        .clk_name = clock_can##n,                      \
        MCAN_RAM_PARAMS(n),                            \
    };                                                 \
    SDK_DECLARE_EXT_ISR_M(IRQn_MCAN##n, can##n##_isr); \
    void can##n##_isr(void)                            \
    {                                                  \
        hpm_mcan_isr(&dev_can##n);                     \
    }
#else
#define MCAN_DEFINE_DEVICE(n)                          \
    static hpm_can_t dev_can##n = {                    \
        .can_base = HPM_MCAN##n,                       \
        .name = "can" #n,                              \
        .irq_num = IRQn_MCAN##n,                       \
        .irq_priority = MCAN_IRQ_PRI_VAL(n),           \
        .fifo_index = n,                               \
        .clk_name = clock_can##n,                      \
        MCAN_RAM_PARAMS(n),                            \
    };
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */

/**
 * @brief RAM parameters macro for MCAN device
 *
 * Conditionally sets RAM base and size parameters based on SoC capabilities.
 * Some SoCs (like HPM6200) don't support AHB RAM message buffers.
 *
 * @param n MCAN instance number (0-7)
 */
#if defined(MCAN_SOC_MSG_BUF_IN_AHB_RAM) && (MCAN_SOC_MSG_BUF_IN_AHB_RAM == 1)
#define MCAN_RAM_PARAMS(n) .ram_base = (uint32_t)mcan##n##_msg_buf, .ram_size = mcan##n##_msg_buf_size
#else
#define MCAN_RAM_PARAMS(n) .ram_base = (uint32_t)NULL, .ram_size = 0
#endif

/**
 * @brief Initialize message buffer in AHB RAM macro
 *
 * Creates message buffer arrays in AHB RAM for SoCs that support it.
 * This improves performance by placing message buffers in faster memory.
 *
 * @param n MCAN instance number (0-7)
 */
#if defined(MCAN_SOC_MSG_BUF_IN_AHB_RAM) && (MCAN_SOC_MSG_BUF_IN_AHB_RAM == 1)
#define MCAN_INIT_MSG_BUF_IN_AHB_RAM(n)                     \
    ATTR_PLACE_AT(".ahb_sram")                              \
    uint32_t mcan##n##_msg_buf[MCAN_MSG_BUF_SIZE_IN_WORDS]; \
    const uint32_t mcan##n##_msg_buf_size = sizeof(mcan##n##_msg_buf);

/* ============================================================================
 * Message Buffer Allocation (AHB RAM)
 * ============================================================================ */

/**
 * @brief Allocate message buffers in AHB RAM for each enabled MCAN instance
 *
 * These buffers are placed in AHB RAM for improved performance on supported SoCs.
 * Each MCAN instance gets its own dedicated message buffer space.
 */

#if defined(HPM_MCAN0_BASE) && defined(BSP_USING_MCAN0)
MCAN_INIT_MSG_BUF_IN_AHB_RAM(0)
#endif

#if defined(HPM_MCAN1_BASE) && defined(BSP_USING_MCAN1)
MCAN_INIT_MSG_BUF_IN_AHB_RAM(1)
#endif

#if defined(HPM_MCAN2_BASE) && defined(BSP_USING_MCAN2)
MCAN_INIT_MSG_BUF_IN_AHB_RAM(2)
#endif

#if defined(HPM_MCAN3_BASE) && defined(BSP_USING_MCAN3)
MCAN_INIT_MSG_BUF_IN_AHB_RAM(3)
#endif

#if defined(HPM_MCAN4_BASE) && defined(BSP_USING_MCAN4)
MCAN_INIT_MSG_BUF_IN_AHB_RAM(4)
#endif

#if defined(HPM_MCAN5_BASE) && defined(BSP_USING_MCAN5)
MCAN_INIT_MSG_BUF_IN_AHB_RAM(5)
#endif

#if defined(HPM_MCAN6_BASE) && defined(BSP_USING_MCAN6)
MCAN_INIT_MSG_BUF_IN_AHB_RAM(6)
#endif

#if defined(HPM_MCAN7_BASE) && defined(BSP_USING_MCAN7)
MCAN_INIT_MSG_BUF_IN_AHB_RAM(7)
#endif

#endif /* MCAN_SOC_MSG_BUF_IN_AHB_RAM */

/* ============================================================================
 * MCAN Device Instances
 * ============================================================================ */

/**
 * @brief Create MCAN device instances for each enabled MCAN peripheral
 *
 * Each enabled MCAN instance gets its own device structure, interrupt handler,
 * and ISR function. The MCAN_DEFINE_DEVICE macro handles all the boilerplate
 * code for device initialization.
 */

#if defined(HPM_MCAN0_BASE) && defined(BSP_USING_MCAN0)
MCAN_DEFINE_DEVICE(0)
#endif

#if defined(HPM_MCAN1_BASE) && defined(BSP_USING_MCAN1)
MCAN_DEFINE_DEVICE(1)
#endif

#if defined(HPM_MCAN2_BASE) && defined(BSP_USING_MCAN2)
MCAN_DEFINE_DEVICE(2)
#endif

#if defined(HPM_MCAN3_BASE) && defined(BSP_USING_MCAN3)
MCAN_DEFINE_DEVICE(3)
#endif

#if defined(HPM_MCAN4_BASE) && defined(BSP_USING_MCAN4)
MCAN_DEFINE_DEVICE(4)
#endif

#if defined(HPM_MCAN5_BASE) && defined(BSP_USING_MCAN5)
MCAN_DEFINE_DEVICE(5)
#endif

#if defined(HPM_MCAN6_BASE) && defined(BSP_USING_MCAN6)
MCAN_DEFINE_DEVICE(6)
#endif

#if defined(HPM_MCAN7_BASE) && defined(BSP_USING_MCAN7)
MCAN_DEFINE_DEVICE(7)
#endif

/* ============================================================================
 * Device Management Arrays
 * ============================================================================ */

/**
 * @brief Array of pointers to all enabled MCAN device instances
 *
 * This array is used by the initialization function to iterate through
 * all enabled MCAN instances and register them with RT-Thread.
 */
static hpm_can_t *hpm_cans[] = {
#if defined(HPM_MCAN0_BASE) && defined(BSP_USING_MCAN0)
    &dev_can0,
#endif
#if defined(HPM_MCAN1_BASE) && defined(BSP_USING_MCAN1)
    &dev_can1,
#endif
#if defined(HPM_MCAN2_BASE) && defined(BSP_USING_MCAN2)
    &dev_can2,
#endif
#if defined(HPM_MCAN3_BASE) && defined(BSP_USING_MCAN3)
    &dev_can3,
#endif
#if defined(HPM_MCAN4_BASE) && defined(BSP_USING_MCAN4)
    &dev_can4,
#endif
#if defined(HPM_MCAN5_BASE) && defined(BSP_USING_MCAN5)
    &dev_can5,
#endif
#if defined(HPM_MCAN6_BASE) && defined(BSP_USING_MCAN6)
    &dev_can6,
#endif
#if defined(HPM_MCAN7_BASE) && defined(BSP_USING_MCAN7)
    &dev_can7,
#endif
};

/**
 * @brief RT-Thread CAN device operations structure
 *
 * This structure defines the function pointers that RT-Thread uses to
 * interact with the MCAN driver. It implements the standard CAN device
 * interface for RT-Thread.
 */
static const struct rt_can_ops hpm_can_ops = {
    .configure = hpm_mcan_configure,  /**< Configure MCAN controller */
    .control = hpm_mcan_control,      /**< Control MCAN device operations */
    .sendmsg = hpm_mcan_sendmsg,      /**< Send CAN message */
    .recvmsg = hpm_mcan_recvmsg,      /**< Receive CAN message */
};

/* ============================================================================
 * Interrupt Service Routine
 * ============================================================================ */

/**
 * @brief MCAN interrupt service routine
 *
 * Handles all MCAN interrupts including transmission completion, reception,
 * FIFO overflow, and error conditions. Updates RT-Thread CAN device status
 * and notifies the framework of events.
 *
 * @param[in] hpm_can Pointer to HPM MCAN device structure
 */
#ifndef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
static void hpm_mcan_isr(hpm_can_t *hpm_can)
#else
static void hpm_mcan_isr(int vector, hpm_can_t *hpm_can)
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */
{
    uint8_t error_flags = mcan_get_last_error_code(hpm_can->can_base);
    uint32_t flags = mcan_get_interrupt_flags(hpm_can->can_base);
    mcan_error_count_t err_cnt;

    /* Handle transmission completion interrupt */
    if ((flags & (MCAN_EVENT_TRANSMIT)) != 0U) {
        rt_hw_can_isr(&hpm_can->can_dev, RT_CAN_EVENT_TX_DONE | (0UL << 8));
    }

    /* Handle reception interrupt - data available in FIFO */
    if (((flags & MCAN_EVENT_RECEIVE) != 0) && ((hpm_can->can_stat != CAN_STOPPED) || (hpm_can->can_stat != CAN_UNITED))) {
        rt_hw_can_isr(&hpm_can->can_dev, RT_CAN_EVENT_RX_IND | (hpm_can->fifo_index << 8));
    }

    /* Handle RX FIFO overflow interrupts */
    if (((flags & MCAN_INT_RXFIFO0_FULL) != 0U) && ((hpm_can->can_stat != CAN_STOPPED) || (hpm_can->can_stat != CAN_UNITED))) {
        rt_hw_can_isr(&hpm_can->can_dev, RT_CAN_EVENT_RXOF_IND | (hpm_can->fifo_index << 8));
    }

    if (((flags & MCAN_INT_RXFIFO1_FULL) != 0U) && ((hpm_can->can_stat != CAN_STOPPED) || (hpm_can->can_stat != CAN_UNITED))) {
        rt_hw_can_isr(&hpm_can->can_dev, RT_CAN_EVENT_RXOF_IND | (hpm_can->fifo_index << 8));
    }

    /* Handle CAN bus error conditions */
    if (((flags & MCAN_EVENT_ERROR) != 0U) || (error_flags != 0U)) {
        mcan_get_error_counter(hpm_can->can_base, &err_cnt);

        /* Update specific error counters based on error type */
        switch (error_flags) {
        case 3:  /* Acknowledgment error */
            hpm_can->can_dev.status.ackerrcnt++;
            break;
        case 4:  /* Bit error */
            hpm_can->can_dev.status.biterrcnt++;
            break;
        case 6:  /* CRC error */
            hpm_can->can_dev.status.crcerrcnt++;
            break;
        case 2:  /* Form error */
            hpm_can->can_dev.status.formaterrcnt++;
            break;
        case 1:  /* Bit padding error */
            hpm_can->can_dev.status.bitpaderrcnt++;
            break;
        }

        /* Update error status information */
        hpm_can->can_dev.status.rcverrcnt = err_cnt.receive_error_count;
        hpm_can->can_dev.status.snderrcnt = err_cnt.transmit_error_count;
        hpm_can->can_dev.status.lasterrtype = mcan_get_last_error_code(hpm_can->can_base);
        hpm_can->can_dev.status.errcode = 0;

        /* Set error state flags */
        if ((error_flags & MCAN_INT_WARNING_STATUS) != 0U) {
            hpm_can->can_dev.status.errcode |= ERRWARNING;
        }
        if ((error_flags & MCAN_INT_ERROR_PASSIVE) != 0U) {
            hpm_can->can_dev.status.errcode |= ERRPASSIVE;
        }
        if (mcan_is_in_busoff_state(hpm_can->can_base)) {
            hpm_can->can_dev.status.errcode |= BUSOFF;
        }
    }

    /* Clear all processed interrupt flags */
    mcan_clear_interrupt_flags(hpm_can->can_base, flags);
}

/* ============================================================================
 * Configuration Functions
 * ============================================================================ */

/**
 * @brief Configure MCAN controller
 *
 * Initializes the MCAN hardware with the specified configuration including
 * baud rate, mode, timing parameters, and message filters. This function
 * is called during device initialization and when configuration changes
 * are requested.
 *
 * @param[in,out] can Pointer to RT-Thread CAN device structure
 * @param[in] cfg Pointer to CAN configuration structure
 * @return RT_EOK on success, -RT_ERROR on failure
 */
static rt_err_t hpm_mcan_configure(struct rt_can_device *can, struct can_configure *cfg)
{
    RT_ASSERT(can);
    RT_ASSERT(cfg);

    hpm_can_t *drv_can = (hpm_can_t *)can->parent.user_data;
    RT_ASSERT(drv_can);

#ifdef RT_CAN_USING_CANFD
    /* Configure CAN-FD settings if supported */
    drv_can->can_config.enable_canfd = (cfg->enable_canfd != 0) ? true : false;
    /* Keep the existing MCAN config, only rebuild the RAM layout for current frame format. */
    mcan_get_default_ram_config(drv_can->can_base,
                                &drv_can->can_config.ram_config,
                                drv_can->can_config.enable_canfd);

    /* Configure bit timing parameters if custom timing is used */
    if (cfg->use_bit_timing != 0U) {
        drv_can->can_config.use_lowlevel_timing_setting = true;

        /* Configure classic CAN timing parameters */
        drv_can->can_config.can_timing.prescaler = cfg->can_timing.prescaler;
        drv_can->can_config.can_timing.num_seg1 = cfg->can_timing.num_seg1;
        drv_can->can_config.can_timing.num_seg2 = cfg->can_timing.num_seg2;
        drv_can->can_config.can_timing.num_sjw = cfg->can_timing.num_sjw;

        /* Configure CAN-FD timing parameters */
        drv_can->can_config.canfd_timing.prescaler = cfg->canfd_timing.prescaler;
        drv_can->can_config.canfd_timing.num_seg1 = cfg->canfd_timing.num_seg1;
        drv_can->can_config.canfd_timing.num_seg2 = cfg->canfd_timing.num_seg2;
        drv_can->can_config.canfd_timing.num_sjw = cfg->canfd_timing.num_sjw;
    } else
#endif
    {
        /* Use automatic baud rate calculation */
        drv_can->can_config.use_lowlevel_timing_setting = false;
        drv_can->can_config.baudrate = cfg->baud_rate;
#ifdef RT_CAN_USING_CANFD
        drv_can->can_config.baudrate_fd = cfg->baud_rate_fd;
#endif
    }

    /* Configure CAN operation mode */
    switch (cfg->mode) {
    case RT_CAN_MODE_NORMAL:
        drv_can->can_config.mode = mcan_mode_normal;
        break;
    case RT_CAN_MODE_LISTEN:
        drv_can->can_config.mode = mcan_mode_listen_only;
        break;
    case RT_CAN_MODE_LOOPBACK:
        drv_can->can_config.mode = mcan_mode_loopback_internal;
        break;
    default:
        return -RT_ERROR;
        break;
    }

    /* Initialize CAN pins and clock */
    init_can_pins(drv_can->can_base);
    clock_add_to_group(drv_can->clk_name, BOARD_RUNNING_CORE & 0x1);
    uint32_t can_clk = clock_get_frequency(drv_can->clk_name);

    /* Configure message filters */
    drv_can->can_config.all_filters_config.std_id_filter_list.filter_elem_list = &drv_can->std_can_filters[0];
    drv_can->can_config.all_filters_config.std_id_filter_list.mcan_filter_elem_count = drv_can->std_filter_num;
    drv_can->can_config.all_filters_config.ext_id_filter_list.filter_elem_list = &drv_can->ext_can_filters[0];
    drv_can->can_config.all_filters_config.ext_id_filter_list.mcan_filter_elem_count = drv_can->ext_filter_num;
    drv_can->can_config.all_filters_config.ext_id_mask = (1UL << 29) - 1UL;
    drv_can->can_config.txbuf_trans_interrupt_mask = ~0UL;

    /* Initialize MCAN hardware with configuration */
    hpm_stat_t status = mcan_init(drv_can->can_base, &drv_can->can_config, can_clk);
    if (status != status_success) {
        return -RT_ERROR;
    }
    drv_can->can_stat = CAN_INITED;

    return RT_EOK;
}

/**
 * @brief Control MCAN device operations
 *
 * Handles various control commands including interrupt management, mode changes,
 * baud rate configuration, filter setup, and status retrieval. This function
 * implements the RT-Thread device control interface for CAN devices.
 *
 * @param[in,out] can Pointer to RT-Thread CAN device structure
 * @param[in] cmd Control command (RT_DEVICE_CTRL_*, RT_CAN_CMD_*)
 * @param[in,out] arg Command-specific argument pointer
 * @return RT_EOK on success, -RT_ERROR on failure
 */
static rt_err_t hpm_mcan_control(struct rt_can_device *can, int cmd, void *arg)
{
    RT_ASSERT(can);

    hpm_can_t *drv_can = (hpm_can_t *)can->parent.user_data;
    RT_ASSERT(drv_can);

    uint32_t arg_val;
    rt_err_t err = RT_EOK;

    uint32_t temp;
    uint32_t irq_txrx_mask;

    switch (cmd) {
    case RT_DEVICE_CTRL_CLR_INT:
        /* Disable specific interrupt types */
        arg_val = (uint32_t)arg;
        intc_m_disable_irq(drv_can->irq_num);
        if (arg_val & RT_DEVICE_FLAG_INT_RX) {
            /* Disable receive interrupt */
            irq_txrx_mask = MCAN_EVENT_RECEIVE;
            drv_can->irq_txrx_err_enable_mask &= ~irq_txrx_mask;
            drv_can->can_config.interrupt_mask &= ~irq_txrx_mask;
            mcan_disable_interrupts(drv_can->can_base, drv_can->irq_txrx_err_enable_mask);
        }
        if (arg_val & RT_DEVICE_FLAG_INT_TX) {
            /* Disable transmit interrupt */
            irq_txrx_mask = MCAN_EVENT_TRANSMIT;
            drv_can->irq_txrx_err_enable_mask &= ~irq_txrx_mask;
            drv_can->can_config.interrupt_mask &= ~irq_txrx_mask;
            mcan_disable_interrupts(drv_can->can_base, drv_can->irq_txrx_err_enable_mask);
            mcan_disable_txbuf_interrupt(drv_can->can_base, ~0UL);
        }
        if (arg_val & RT_DEVICE_CAN_INT_ERR) {
            /* Disable error interrupt */
            irq_txrx_mask = MCAN_EVENT_ERROR;
            drv_can->irq_txrx_err_enable_mask &= ~irq_txrx_mask;
            drv_can->can_config.interrupt_mask &= ~irq_txrx_mask;
            mcan_disable_interrupts(drv_can->can_base, drv_can->irq_txrx_err_enable_mask);
        }
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* Enable specific interrupt types */
        arg_val = (uint32_t)arg;
        if (arg_val & RT_DEVICE_FLAG_INT_RX) {
            /* Enable receive interrupt */
            irq_txrx_mask = MCAN_EVENT_RECEIVE;
            drv_can->irq_txrx_err_enable_mask |= irq_txrx_mask;
            drv_can->can_config.interrupt_mask |= irq_txrx_mask;
            mcan_enable_interrupts(drv_can->can_base, drv_can->irq_txrx_err_enable_mask);
            intc_m_enable_irq_with_priority(drv_can->irq_num, drv_can->irq_priority);
        }
        if (arg_val & RT_DEVICE_FLAG_INT_TX) {
            /* Enable transmit interrupt */
            irq_txrx_mask = MCAN_EVENT_TRANSMIT;
            drv_can->irq_txrx_err_enable_mask |= irq_txrx_mask;
            drv_can->can_config.interrupt_mask |= irq_txrx_mask;
            mcan_enable_interrupts(drv_can->can_base, drv_can->irq_txrx_err_enable_mask);
            mcan_enable_txbuf_interrupt(drv_can->can_base, ~0UL);
            intc_m_enable_irq_with_priority(drv_can->irq_num, drv_can->irq_priority);
        }
        if (arg_val & RT_DEVICE_CAN_INT_ERR) {
            /* Enable error interrupt */
            irq_txrx_mask = MCAN_EVENT_ERROR;
            drv_can->irq_txrx_err_enable_mask |= irq_txrx_mask;
            drv_can->can_config.interrupt_mask |= irq_txrx_mask;
            mcan_enable_interrupts(drv_can->can_base, drv_can->irq_txrx_err_enable_mask);
            intc_m_enable_irq_with_priority(drv_can->irq_num, drv_can->irq_priority);
        }
        break;

    case RT_CAN_CMD_SET_FILTER: {
        /* Configure message filters for CAN reception */
        struct rt_can_filter_config *filter = (struct rt_can_filter_config *)arg;
        drv_can->std_filter_num = 0;
        drv_can->ext_filter_num = 0;

        if (filter != NULL) {
            /* Process each filter item in the configuration */
            for (uint32_t i = 0; i < filter->count; i++) {
                if (filter->items[i].ide != 0) {
                    /* Configure extended ID filter */
                    if (drv_can->ext_filter_num >= CAN_EXT_FILTER_NUM_MAX) {
                        return -RT_EFULL;
                    }
                    filter->items[i].mask &= CAN_EXT_ID_MASK; /* Ensure mask is within valid range */
                    drv_can->ext_can_filters[drv_can->ext_filter_num].filter_type = MCAN_FILTER_TYPE_CLASSIC_FILTER;
                    drv_can->ext_can_filters[drv_can->ext_filter_num].filter_config = MCAN_FILTER_ELEM_CFG_STORE_IN_RX_FIFO0_IF_MATCH;
                    drv_can->ext_can_filters[drv_can->ext_filter_num].can_id_type = MCAN_CAN_ID_TYPE_EXTENDED;
                    drv_can->ext_can_filters[drv_can->ext_filter_num].filter_id = filter->items[i].id;
                    drv_can->ext_can_filters[drv_can->ext_filter_num].filter_mask = filter->items[i].mask;
                    drv_can->ext_filter_num++;
                } else {
                    /* Configure standard ID filter */
                    if (drv_can->std_filter_num >= CAN_STD_FILTER_NUM_MAX) {
                        return -RT_EFULL;
                    }
                    filter->items[i].mask &= CAN_STD_ID_MASK; /* Ensure mask is within valid range */
                    drv_can->std_can_filters[drv_can->std_filter_num].filter_type = MCAN_FILTER_TYPE_CLASSIC_FILTER;
                    drv_can->std_can_filters[drv_can->std_filter_num].filter_config = MCAN_FILTER_ELEM_CFG_STORE_IN_RX_FIFO0_IF_MATCH;
                    drv_can->std_can_filters[drv_can->std_filter_num].can_id_type = MCAN_CAN_ID_TYPE_STANDARD;
                    drv_can->std_can_filters[drv_can->std_filter_num].filter_id = filter->items[i].id;
                    drv_can->std_can_filters[drv_can->std_filter_num].filter_mask = filter->items[i].mask;
                    drv_can->std_filter_num++;
                }
                /* Handle RTR (Remote Transmission Request) frame filtering */
                if (filter->items[i].rtr != 0) {
                    if (drv_can->ext_filter_num) {
                        drv_can->can_config.all_filters_config.global_filter_config.reject_remote_ext_frame = false;
                    } else {
                        drv_can->can_config.all_filters_config.global_filter_config.reject_remote_ext_frame = true;
                    }
                    if (drv_can->std_filter_num) {
                        drv_can->can_config.all_filters_config.global_filter_config.reject_remote_std_frame = false;
                    } else {
                        drv_can->can_config.all_filters_config.global_filter_config.reject_remote_std_frame = true;
                    }
                }
            }

            /* Configure filter activation behavior */
            if (filter->actived != 0U) {
                /* Reject non-matching frames when filters are active */
                drv_can->can_config.all_filters_config.global_filter_config.accept_non_matching_std_frame_option = MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_REJECT;
                drv_can->can_config.all_filters_config.global_filter_config.accept_non_matching_ext_frame_option = MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_REJECT;
            } else {
                /* Accept all frames when filters are not active */
                drv_can->can_config.all_filters_config.global_filter_config.accept_non_matching_std_frame_option =
                    MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_IN_RXFIFO0;
                drv_can->can_config.all_filters_config.global_filter_config.accept_non_matching_ext_frame_option =
                    MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_IN_RXFIFO0;
            }
        } else {
            /* Use default filters when no filter configuration provided */
            drv_can->can_config.all_filters_config.global_filter_config.reject_remote_ext_frame = false;
            drv_can->can_config.all_filters_config.global_filter_config.reject_remote_std_frame = false;
            drv_can->can_config.all_filters_config.global_filter_config.accept_non_matching_std_frame_option = MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_IN_RXFIFO0;
            drv_can->can_config.all_filters_config.global_filter_config.accept_non_matching_ext_frame_option = MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_IN_RXFIFO0;
            drv_can->can_config.all_filters_config.ext_id_mask = 0x1FFFFFFFUL;
            drv_can->can_config.all_filters_config.std_id_filter_list.filter_elem_list = &k_default_std_id_filter;
            drv_can->can_config.all_filters_config.std_id_filter_list.mcan_filter_elem_count = 1;
            drv_can->can_config.all_filters_config.ext_id_filter_list.filter_elem_list = &k_default_ext_id_filter;
            drv_can->can_config.all_filters_config.ext_id_filter_list.mcan_filter_elem_count = 1;
        }
        /* Apply filter configuration to hardware */
        err = hpm_mcan_configure(can, &drv_can->can_dev.config);
#ifdef RT_CAN_USING_HDR
        if (filter == RT_NULL) {
            /* Special case for HDR: return error when using default filters */
            err = -RT_ETRAP;
        }
#endif
    } break;

    case RT_CAN_CMD_SET_MODE:
        /* Set CAN operation mode */
        arg_val = (uint32_t)arg;
        if ((arg_val != RT_CAN_MODE_NORMAL) && (arg_val != RT_CAN_MODE_LISTEN) && (arg_val != RT_CAN_MODE_LOOPBACK)) {
            err = -RT_ERROR;
            break;
        }
        if (arg_val != drv_can->can_dev.config.mode) {
            drv_can->can_dev.config.mode = arg_val;
            err = hpm_mcan_configure(can, &drv_can->can_dev.config);
        }
        break;

    case RT_CAN_CMD_SET_BAUD:
        /* Set CAN baud rate */
        arg_val = (uint32_t)arg;
#ifdef RT_CAN_USING_CANFD
        drv_can->can_dev.config.use_bit_timing = 0U;
#endif
        if (arg_val != drv_can->can_dev.config.baud_rate) {
            drv_can->can_dev.config.baud_rate = arg_val;
        }
        err = hpm_mcan_configure(can, &drv_can->can_dev.config);
        break;
#ifdef RT_CAN_USING_CANFD
    case RT_CAN_CMD_SET_CANFD:
        /* Enable/disable CAN-FD mode */
        arg_val = (uint32_t)arg;
        if (arg_val != drv_can->can_dev.config.enable_canfd) {
            drv_can->can_dev.config.enable_canfd = arg_val;
            err = hpm_mcan_configure(can, &drv_can->can_dev.config);
        }
        break;

    case RT_CAN_CMD_SET_BAUD_FD:
        /* Set CAN-FD data phase baud rate */
        arg_val = (uint32_t)arg;
        drv_can->can_dev.config.use_bit_timing = 0U;
        if (arg_val != drv_can->can_dev.config.baud_rate_fd) {
            drv_can->can_dev.config.baud_rate_fd = arg_val;
            err = hpm_mcan_configure(can, &drv_can->can_dev.config);
        }
        break;

    case RT_CAN_CMD_SET_BITTIMING: {
        /* Set custom bit timing parameters */
        struct rt_can_bit_timing_config *timing_configs = (struct rt_can_bit_timing_config *)arg;
        if ((timing_configs == RT_NULL) || (timing_configs->count < 1) || (timing_configs->count > 2)) {
            return -RT_ERROR;
        }

        drv_can->can_dev.config.use_bit_timing = 1U;
        /* Configure classic CAN timing (first item) */
        if (timing_configs->count != 0U) {
            drv_can->can_dev.config.can_timing = timing_configs->items[0];
        }
        /* Configure CAN-FD timing (second item) */
        if (timing_configs->count == 2) {
            drv_can->can_dev.config.canfd_timing = timing_configs->items[1];
        }
        err = hpm_mcan_configure(can, &drv_can->can_dev.config);
    } break;
#endif
    case RT_CAN_CMD_SET_PRIV:
        /* Set privacy mode (privileged/non-privileged) */
        arg_val = (uint32_t)arg;
        if ((arg_val != RT_CAN_MODE_PRIV) && (arg_val != RT_CAN_MODE_NOPRIV)) {
            return -RT_ERROR;
        }
        if (arg_val != drv_can->can_dev.config.privmode) {
            drv_can->can_dev.config.privmode = arg_val;
            err = hpm_mcan_configure(can, &drv_can->can_dev.config);
        }
        break;

    case RT_CAN_CMD_GET_STATUS:
        /* Get CAN controller status and error information */
        mcan_error_count_t err_cnt;
        mcan_get_error_counter(drv_can->can_base, &err_cnt);
        drv_can->can_dev.status.rcverrcnt = err_cnt.receive_error_count;
        drv_can->can_dev.status.snderrcnt = err_cnt.transmit_error_count;
        drv_can->can_dev.status.lasterrtype = mcan_get_last_error_code(drv_can->can_base);
        temp = mcan_get_interrupt_flags(drv_can->can_base);
        drv_can->can_dev.status.errcode = 0;

        /* Set error state flags */
        if ((temp & MCAN_INT_WARNING_STATUS) != 0U) {
            drv_can->can_dev.status.errcode |= ERRWARNING;
        }
        if ((temp & MCAN_INT_ERROR_PASSIVE) != 0U) {
            drv_can->can_dev.status.errcode |= ERRPASSIVE;
        }
        if (mcan_is_in_busoff_state(drv_can->can_base)) {
            drv_can->can_dev.status.errcode |= BUSOFF;
        }
        rt_memcpy(arg, &drv_can->can_dev.status, sizeof(drv_can->can_dev.status));
        break;

    case RT_CAN_CMD_START:
        arg_val = (rt_uint32_t)arg;
        if (arg_val == 0) {
            /* Stop CAN (enter Init Mode) */
            mcan_enter_init_mode(drv_can->can_base);
            drv_can->can_stat = CAN_STOPPED;
        } else {
            /* 1. Clear all TX buffers */
            for (uint32_t i = 0; i < MCAN_TXBUF_SIZE_CAN_DEFAULT; i++) {
                if (mcan_is_transmit_request_pending(drv_can->can_base, i)) {
                    mcan_cancel_tx_buf_send_request(drv_can->can_base, i);
                }
            }
            rt_thread_mdelay(5);
            /* 2. Clear all interrupt flags */
            mcan_clear_interrupt_flags(drv_can->can_base, 0xFFFFFFFF);
            /* 3. Enter Normal Mode */
            mcan_enter_normal_mode(drv_can->can_base);
            rt_thread_mdelay(5);
            drv_can->can_stat = CAN_RUNNING;
        }
        break;
    }
    return err;
}

/* ============================================================================
 * Message Transmission and Reception Functions
 * ============================================================================ */

/**
 * @brief Send CAN message
 *
 * Transmits a CAN message through the specified MCAN instance.
 * Supports both classic CAN and CAN-FD frames with proper frame formatting
 * and transmission buffer management.
 *
 * @param[in] can Pointer to RT-Thread CAN device structure
 * @param[in] buf Pointer to CAN message buffer
 * @param[in] boxno Mailbox number (not used in this implementation)
 * @return RT_EOK on success, -RT_ETIMEOUT on timeout, -RT_EFULL if buffer full
 */
static rt_ssize_t hpm_mcan_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t boxno)
{
    RT_ASSERT(can);

    hpm_can_t *drv_can = (hpm_can_t *)can->parent.user_data;
    RT_ASSERT(drv_can);

    struct rt_can_msg *can_msg = (struct rt_can_msg *)buf;
    if ((drv_can->can_stat == CAN_UNITED) || (drv_can->can_stat == CAN_STOPPED)) {
        return -RT_ERROR;
    }

    /* Initialize transmission frame structure */
    mcan_tx_frame_t tx_frame = { 0 };
    memset(&tx_frame, 0, sizeof(tx_frame));

    /* Configure CAN ID (standard or extended) */
    if (can_msg->ide == RT_CAN_STDID) {
        tx_frame.use_ext_id = 0;
        tx_frame.std_id = can_msg->id;
    } else {
        tx_frame.use_ext_id = 1;
        tx_frame.ext_id = can_msg->id;
    }

    /* Configure RTR (Remote Transmission Request) flag */
    if (can_msg->rtr == RT_CAN_DTR) {
        tx_frame.rtr = false;
    } else {
        tx_frame.rtr = true;
    }

#ifdef RT_CAN_USING_CANFD
    /* Configure CAN-FD specific parameters */
    tx_frame.bitrate_switch = can_msg->brs;
    if (can_msg->fd_frame != 0) {
        tx_frame.canfd_frame = 1;
        RT_ASSERT(can_msg->len <= 15);  /* CAN-FD supports up to 64 bytes (DLC 15) */
    } else
#endif
    {
        RT_ASSERT(can_msg->len <= 8);   /* Classic CAN supports up to 8 bytes */
    }

    /* Copy message data to transmission frame */
    uint32_t msg_len = mcan_get_message_size_from_dlc(can_msg->len);
    for (uint32_t i = 0; i < msg_len; i++) {
        tx_frame.data_8[i] = can_msg->data[i];
    }
    tx_frame.dlc = can_msg->len;

    /* Wait for transmission buffer to become available */
    uint32_t delay_cnt = 0;
    while (mcan_is_txfifo_full(drv_can->can_base)) {
        rt_thread_mdelay(1);
        delay_cnt++;
        if (delay_cnt >= CAN_SEND_WAIT_MS_MAX) {
            return -RT_ETIMEOUT;
        }
    }

    /* Transmit through TX FIFO to avoid overwriting a still-pending dedicated buffer. */
    hpm_stat_t status = mcan_transmit_via_txfifo_nonblocking(drv_can->can_base, &tx_frame, &drv_can->can_tx_fifo_index);
    if (status != status_success) {
        return -RT_EFULL;
    }

    return RT_EOK;
}

/**
 * @brief Receive CAN message
 *
 * Receives a CAN message from the MCAN RX FIFO.
 * Supports both classic CAN and CAN-FD frames with proper frame parsing
 * and data extraction.
 *
 * @param[in] can Pointer to RT-Thread CAN device structure
 * @param[out] buf Pointer to receive buffer for CAN message
 * @param[in] boxno Mailbox number (not used in this implementation)
 * @return RT_EOK on success, -RT_ERROR on error, -RT_EMPTY if no data
 */
static rt_ssize_t hpm_mcan_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t boxno)
{
    RT_ASSERT(can);

    hpm_can_t *drv_can = (hpm_can_t *)can->parent.user_data;
    RT_ASSERT(drv_can);

    rt_can_msg_t can_msg = (rt_can_msg_t)buf;
    mcan_rx_message_t rx_buf = { 0 };

    /* Read message from RX FIFO */
    hpm_stat_t status = mcan_read_rxfifo(drv_can->can_base, 0, &rx_buf);
    if (status == status_success) {
        /* Extract CAN ID information */
        if (rx_buf.use_ext_id) {
            can_msg->ide = RT_CAN_EXTID;
            can_msg->id = rx_buf.ext_id;
        } else {
            can_msg->ide = RT_CAN_STDID;
            can_msg->id = rx_buf.std_id;
        }

        /* Extract RTR flag */
        if (rx_buf.rtr != 0) {
            can_msg->rtr = RT_CAN_RTR;
        } else {
            can_msg->rtr = RT_CAN_DTR;
        }

#ifdef RT_CAN_USING_CANFD
        /* Extract CAN-FD specific information */
        can_msg->fd_frame = rx_buf.canfd_frame;
        can_msg->brs = rx_buf.bitrate_switch;
#endif

        /* Extract message length and data */
        can_msg->len = rx_buf.dlc;
        uint32_t msg_len = mcan_get_message_size_from_dlc(can_msg->len);
        memset(can_msg->data, 0, sizeof(can_msg->data));
        for (uint32_t i = 0; i < msg_len; i++) {
            can_msg->data[i] = rx_buf.data_8[i];
        }

#ifdef RT_CAN_USING_HDR
        /* Update hardware filter status for HDR support */
        can_msg->hdr_index = boxno;
        can->hdr[can_msg->hdr_index].connected = 1;
#endif
    } else {
        return -RT_EEMPTY;
    }

    return RT_EOK;
}

/* ============================================================================
 * Initialization Function
 * ============================================================================ */

/**
 * @brief Initialize MCAN hardware and register devices with RT-Thread
 *
 * This function initializes all enabled MCAN instances, configures their
 * default settings, and registers them with the RT-Thread device framework.
 * It is called during system startup through the INIT_BOARD_EXPORT macro.
 *
 * @return RT_EOK on success
 */
int rt_hw_mcan_init(void)
{
    /* Initialize default CAN configuration */
    struct can_configure config = CANDEFAULTCONFIG;
    config.privmode = RT_CAN_MODE_NOPRIV;
    config.sndboxnumber = CAN_SENDBOX_NUM;
    config.ticks = 50;
#ifdef RT_CAN_USING_HDR
    config.maxhdr = 32;
#endif

    /* Initialize each enabled MCAN instance */
    for (uint32_t i = 0; i < ARRAY_SIZE(hpm_cans); i++) {
        /* Set default configuration */
        hpm_cans[i]->can_dev.config = config;
        hpm_cans[i]->ext_filter_num = 0;
        hpm_cans[i]->std_filter_num = 0;
        hpm_cans[i]->can_stat = CAN_UNITED;

#if defined(MCAN_SOC_MSG_BUF_IN_AHB_RAM) && (MCAN_SOC_MSG_BUF_IN_AHB_RAM == 1)
        /* Configure message buffer attributes for AHB RAM */
        mcan_msg_buf_attr_t attr = { hpm_cans[i]->ram_base, hpm_cans[i]->ram_size };
        hpm_stat_t status = mcan_set_msg_buf_attr(hpm_cans[i]->can_base, &attr);
#endif

        /* Get default MCAN configuration from hardware */
        mcan_get_default_config(hpm_cans[i]->can_base, &hpm_cans[i]->can_config);

        /* Register device with RT-Thread */
        rt_hw_can_register(&hpm_cans[i]->can_dev, hpm_cans[i]->name, &hpm_can_ops, hpm_cans[i]);
#ifdef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
        /* Register MCAN device to irq table */
        rt_hw_interrupt_install(hpm_cans[i]->irq_num, (rt_isr_handler_t)hpm_mcan_isr, hpm_cans[i], hpm_cans[i]->name);
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */
    }
    return RT_EOK;
}

/* Register initialization function to be called during board startup */
INIT_BOARD_EXPORT(rt_hw_mcan_init);

#endif /* RT_USING_CAN */
