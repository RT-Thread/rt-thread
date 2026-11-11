/*
 * Copyright (c) 2022-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * @file drv_uart_v2.c
 * @brief UART driver implementation for RT-Thread on HPMicro Microcontrollers
 *
 * This file implements the UART (Universal Asynchronous Receiver-Transmitter) driver
 * for HPMicro microcontrollers, providing a complete interface
 * between RT-Thread's serial framework and the HPM UART hardware.
 *
 * Features:
 * - Support for up to 16 UART controllers (UART0-UART15)
 * - Interrupt-driven and DMA-based data transfer
 * - Configurable baud rates, data bits, stop bits, and parity
 * - Hardware flow control support
 * - Ring buffer management for efficient data handling
 * - Cache coherency support for DMA operations
 * - RX idle detection for improved DMA efficiency
 *
 * Architecture:
 * - Each UART controller is represented by a hpm_uart structure
 * - ISR functions handle interrupt-driven operations
 * - DMA channels are dynamically allocated and managed
 * - Configuration macros reduce code duplication
 *
 * Change Logs:
 * Date         Author      Notes
 * 2022-03-08   HPMicro     First version
 * 2022-07-28   HPMicro     Fix compiling warning if RT_SERIAL_USING_DMA was not defined
 * 2022-08-08   HPMicro     Integrate DMA Manager and support dynamic DMA resource assignment
 * 2023-03-07   HPMicro     Fix the issue that the data_width was not initialized before setup dma handshake
 * 2024-06-10   HPMicro     Fix memory leakage issue
 * 2025-09-01   HPMicro     Added comprehensive macros to reduce code duplication
 * 2025-12-10   HPMicro     Added DMA ping-pong buffer support for RX DMA mode
 *
 */

/* RT-Thread configuration */
#include "rtconfig.h"

#ifdef RT_USING_SERIAL_V2

/* RT-Thread core includes */
#include <rtthread.h>        /* RT-Thread kernel and threading support */
#include <rtdevice.h>        /* RT-Thread device framework */

/* Board and driver specific includes */
#include "board.h"           /* Board configuration and pin definitions */
#include "drv_uart_v2.h"     /* UART driver header file */

/* HPM SDK includes */
#include "hpm_uart_drv.h"    /* HPM UART driver API */
#include "hpm_l1c_drv.h"     /* L1 cache driver for DMA coherency */
#include "hpm_dma_mgr.h"     /* DMA manager for resource allocation */
#include "hpm_soc.h"         /* HPM SoC definitions and register maps */
#include "hpm_clock_drv.h"   /* Clock driver for UART clock configuration */
#include "hpm_sysctl_drv.h"


/* ============================================================================
 * DMA Configuration and Definitions
 * ============================================================================
 */

#ifdef RT_SERIAL_USING_DMA

/* DMA hardware configuration */
#define BOARD_UART_DMAMUX  HPM_DMAMUX        /* DMA multiplexer base address */
#define UART_DMA_TRIGGER_LEVEL (1U)          /* DMA trigger level for UART operations */

/**
 * @brief DMA channel handle structure for UART operations
 *
 * This structure manages DMA channel resources and callbacks for UART operations.
 * It provides a complete interface for DMA-based UART data transfer with proper
 * error handling and completion notification.
 */
typedef struct dma_channel {
    struct rt_serial_device *serial;          /* Associated RT-Thread serial device */
    dma_resource_t resource;                  /* DMA resource (base, channel, IRQ) */
    void (*transfer_done)(struct rt_serial_device *serial);   /* Transfer completion callback */
#ifdef HPMSOC_HAS_HPMSDK_DMAV2
    void (*halftransfer_cb)(struct rt_serial_device *serial);     /* Half transfer callback */
#endif
    void (*transfer_abort)(struct rt_serial_device *serial);  /* Transfer abort callback */
    void (*transfer_error)(struct rt_serial_device *serial);  /* Transfer error callback */
    void *ringbuf_ptr;                        /* Pointer to ring buffer for DMA operations */
} hpm_dma_channel_handle_t;

//static struct dma_channel dma_channels[DMA_SOC_CHANNEL_NUM];
static int hpm_uart_dma_config(struct rt_serial_device *serial, void *arg);
static void hpm_uart_receive_dma_next(struct rt_serial_device *serial);
#endif

/**
 * @brief UART device structure for HPM microcontrollers
 *
 * This structure contains all the necessary information to manage a UART controller,
 * including hardware registers, DMA configuration, interrupt settings, and device
 * identification. It serves as the primary data structure for UART operations.
 */
struct hpm_uart {
    /* Hardware configuration */
    UART_Type *uart_base;                     /* UART hardware register base address */
    rt_uint32_t txbuf_size;                   /* Transmit buffer size in bytes */
    rt_uint32_t rxbuf_size;                   /* Receive buffer size in bytes */
    rt_uint32_t irq_num;                      /* UART interrupt number */
    rt_uint8_t irq_priority;                  /* UART interrupt priority */

    /* DMA configuration */
    bool enable_dma;                          /* Overall DMA enable flag */
    bool enable_tx_dma;                       /* Transmit DMA enable flag */
    bool enable_rx_dma;                       /* Receive DMA enable flag */

    /* Clock and device configuration */
    clock_name_t clk_name;                    /* UART clock source name */
    struct rt_serial_device *serial;          /* Associated RT-Thread serial device */
    char *device_name;                        /* Device name string (e.g., "uart0") */

    /* DMA multiplexer configuration */
    uint32_t tx_dma_mux;                      /* TX DMA multiplexer source */
    uint32_t rx_dma_mux;                      /* RX DMA multiplexer source */
    uint32_t dma_flags;                       /* DMA operation flags */

#ifdef RT_SERIAL_USING_DMA
    /* DMA channel contexts */
    hpm_dma_channel_handle_t tx_chn_ctx;      /* TX DMA channel context */
    hpm_dma_channel_handle_t rx_chn_ctx;      /* RX DMA channel context */
    bool tx_resource_allocated;               /* TX DMA resource allocation status */
    bool rx_resource_allocated;               /* RX DMA resource allocation status */
    rt_uint32_t dma_pingpong_size;                /* DMA ping buffer size */
    rt_uint32_t dma_rx_remain_size;           /* Remaining size for RX DMA operations */
#endif
    rt_uint32_t rx_buffer_size;              /* RX buffer size */
    rt_uint32_t rx_fifo_index;               /* RX FIFO index */
};

/* ============================================================================
 * Function Declarations
 * ============================================================================
 */

/* External functions */
extern void init_uart_pins(UART_Type *ptr);   /* Initialize UART pins (defined in board.c) */

/* UART driver function prototypes */
#ifndef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
static void hpm_uart_isr(struct rt_serial_device *serial);                    /* UART interrupt service routine */
#else
static void hpm_uart_isr(int vector, struct rt_serial_device *serial);                    /* UART interrupt service routine */
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */
static rt_err_t hpm_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg);  /* Configure UART parameters */
static rt_err_t hpm_uart_control(struct rt_serial_device *serial, int cmd, void *arg);              /* Control UART operations */
static int hpm_uart_putc(struct rt_serial_device *serial, char ch);           /* Send single character */
static int hpm_uart_getc(struct rt_serial_device *serial);                    /* Receive single character */

#ifdef RT_SERIAL_USING_DMA
int hpm_uart_dma_register_channel(struct rt_serial_device *serial,
                                                 bool is_tx,
                                                     void (*done)(struct rt_serial_device *serial),
                                                     void (*htc)(struct rt_serial_device *serial),
                                                     void (*abort)(struct rt_serial_device *serial),
                                                     void (*error)(struct rt_serial_device *serial))
{

    struct hpm_uart *uart = (struct hpm_uart *)serial->parent.user_data;

    if (is_tx) {
        uart->tx_chn_ctx.serial = serial;
        uart->tx_chn_ctx.transfer_done = done;
#ifdef HPMSOC_HAS_HPMSDK_DMAV2
        uart->tx_chn_ctx.halftransfer_cb = htc;
#else
        (void)htc;
#endif
        uart->tx_chn_ctx.transfer_abort = abort;
        uart->tx_chn_ctx.transfer_error = error;
    } else {
        uart->rx_chn_ctx.serial = serial;
        uart->rx_chn_ctx.transfer_done = done;
#ifdef HPMSOC_HAS_HPMSDK_DMAV2
        uart->rx_chn_ctx.halftransfer_cb = htc;
#else
        (void)htc;
#endif
        uart->rx_chn_ctx.transfer_abort = abort;
        uart->rx_chn_ctx.transfer_error = error;
    }
    return RT_EOK;
}
#endif /* RT_SERIAL_USING_DMA */

#ifndef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
/* ============================================================================
 * UART ISR Function Macros
 * ============================================================================
 *
 * These macros generate UART interrupt service routine functions and device
 * declarations for each UART controller. They reduce code duplication by
 * automatically generating the necessary ISR functions and device structures.
 *
 * Each macro generates:
 * - A serial device structure (serial0, serial1, etc.)
 * - An ISR function declaration with proper interrupt mapping
 * - An ISR function implementation that calls the common ISR handler
 *
 * Usage: UART_ISR_DECLARE(n) where n is the UART number (0-15)
 */
#define UART_ISR_DECLARE(n) \
    struct rt_serial_device serial##n; \
    SDK_DECLARE_EXT_ISR_M(IRQn_UART##n,uart##n##_isr) \
    void uart##n##_isr(void) \
    { \
        hpm_uart_isr(&serial##n); \
    } \

#ifdef BSP_USING_UART0
UART_ISR_DECLARE(0)
#endif

#ifdef BSP_USING_UART1
UART_ISR_DECLARE(1)
#endif

#ifdef BSP_USING_UART2
UART_ISR_DECLARE(2)
#endif

#ifdef BSP_USING_UART3
UART_ISR_DECLARE(3)
#endif

#ifdef BSP_USING_UART4
UART_ISR_DECLARE(4)
#endif

#ifdef BSP_USING_UART5
UART_ISR_DECLARE(5)
#endif

#ifdef BSP_USING_UART6
UART_ISR_DECLARE(6)
#endif

#ifdef BSP_USING_UART7
UART_ISR_DECLARE(7)
#endif

#ifdef BSP_USING_UART8
UART_ISR_DECLARE(8)
#endif

#ifdef BSP_USING_UART9
UART_ISR_DECLARE(9)
#endif

#ifdef BSP_USING_UART10
UART_ISR_DECLARE(10)
#endif

#ifdef BSP_USING_UART11
UART_ISR_DECLARE(11)
#endif

#ifdef BSP_USING_UART12
UART_ISR_DECLARE(12)
#endif

#ifdef BSP_USING_UART13
UART_ISR_DECLARE(13)
#endif

#ifdef BSP_USING_UART14
UART_ISR_DECLARE(14)
#endif

#ifdef BSP_USING_UART15
UART_ISR_DECLARE(15)
#endif

#ifdef BSP_USING_PUART
struct rt_serial_device serial_puart;
SDK_DECLARE_EXT_ISR_M(IRQn_PUART, puart_isr)
void puart_isr(void)
{
    hpm_uart_isr(&serial_puart);
}
#endif

#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */

/* ============================================================================
 * UART Structure Initialization Macro
 * ============================================================================
 *
 * This macro initializes a UART device structure with all necessary configuration
 * parameters. It automatically sets up hardware addresses, buffer sizes, interrupt
 * priorities, DMA configuration, and device identification.
 *
 * The macro handles:
 * - Hardware register base addresses
 * - Buffer size configuration from board definitions
 * - Interrupt number and priority assignment
 * - DMA enable flags based on configuration
 * - Clock source assignment
 * - Device name generation
 * - DMA multiplexer source configuration
 * - DMA resource allocation status initialization
 *
 * Usage: UART_INIT_STRUCT(n) where n is the UART number (0-15)
 */

#ifdef RT_SERIAL_USING_DMA
#define UART_INIT_STRUCT(n) \
    { \
        .uart_base = HPM_UART##n, \
        .txbuf_size = BSP_UART##n##_TX_BUFSIZE, \
        .rxbuf_size = BSP_UART##n##_RX_BUFSIZE, \
        .irq_num = IRQn_UART##n, \
        .irq_priority = UART_IRQ_PRI_VAL(n), \
        .enable_dma = (UART_TX_USING_DMA_VAL(n) || UART_RX_USING_DMA_VAL(n)), \
        .enable_tx_dma = UART_TX_USING_DMA_VAL(n), \
        .enable_rx_dma = UART_RX_USING_DMA_VAL(n), \
        .clk_name = clock_uart##n, \
        .serial = &serial##n, \
        .device_name = "uart" #n, \
        .tx_dma_mux = HPM_DMA_SRC_UART##n##_TX, \
        .rx_dma_mux = HPM_DMA_SRC_UART##n##_RX, \
        .dma_flags = 0, \
        .dma_pingpong_size = BSP_UART##n##_DMA_PINGPONG_BUFSIZE, \
        .rx_buffer_size = BSP_UART##n##_RX_BUFSIZE, \
        .rx_fifo_index = 0, \
    }
#else
#define UART_INIT_STRUCT(n) \
    { \
        .uart_base = HPM_UART##n, \
        .txbuf_size = BSP_UART##n##_TX_BUFSIZE, \
        .rxbuf_size = BSP_UART##n##_RX_BUFSIZE, \
        .irq_num = IRQn_UART##n, \
        .irq_priority = UART_IRQ_PRI_VAL(n), \
        .clk_name = clock_uart##n, \
        .serial = &serial##n, \
        .device_name = "uart" #n, \
        .rx_buffer_size = BSP_UART##n##_RX_BUFSIZE, \
        .rx_fifo_index = 0, \
    }
#endif


/* ============================================================================
 * UART Device Array
 * ============================================================================
 *
 * This array contains all configured UART device structures. Each entry is
 * conditionally compiled based on the BSP_USING_UARTx configuration macros.
 * The array is used by the driver to manage multiple UART controllers.
 */
#ifdef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
#if defined(BSP_USING_UART0)
struct rt_serial_device serial0;
#endif
#if defined(BSP_USING_UART1)
struct rt_serial_device serial1;
#endif
#if defined(BSP_USING_UART2)
struct rt_serial_device serial2;
#endif
#if defined(BSP_USING_UART3)
struct rt_serial_device serial3;
#endif
#if defined(BSP_USING_UART4)
struct rt_serial_device serial4;
#endif
#if defined(BSP_USING_UART5)
struct rt_serial_device serial5;
#endif
#if defined(BSP_USING_UART6)
struct rt_serial_device serial6;
#endif
#if defined(BSP_USING_UART7)
struct rt_serial_device serial7;
#endif
#if defined(BSP_USING_UART8)
struct rt_serial_device serial8;
#endif
#if defined(BSP_USING_UART9)
struct rt_serial_device serial9;
#endif
#if defined(BSP_USING_UART10)
struct rt_serial_device serial10;
#endif
#if defined(BSP_USING_UART11)
struct rt_serial_device serial11;
#endif
#if defined(BSP_USING_UART12)
struct rt_serial_device serial12;
#endif
#if defined(BSP_USING_UART13)
struct rt_serial_device serial13;
#endif
#if defined(BSP_USING_UART14)
struct rt_serial_device serial14;
#endif
#if defined(BSP_USING_UART15)
struct rt_serial_device serial15;
#endif
#if defined(BSP_USING_PUART)
struct rt_serial_device serial_puart;
#endif
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */

static struct hpm_uart uarts[] =
{
#if defined(BSP_USING_UART0)
    UART_INIT_STRUCT(0),
#endif

#if defined(BSP_USING_UART1)
    UART_INIT_STRUCT(1),
#endif

#if defined(BSP_USING_UART2)
    UART_INIT_STRUCT(2),
#endif

#if defined(BSP_USING_UART3)
    UART_INIT_STRUCT(3),
#endif

#if defined(BSP_USING_UART4)
    UART_INIT_STRUCT(4),
#endif

#if defined(BSP_USING_UART5)
    UART_INIT_STRUCT(5),
#endif

#if defined(BSP_USING_UART6)
    UART_INIT_STRUCT(6),
#endif

#if defined(BSP_USING_UART7)
    UART_INIT_STRUCT(7),
#endif

#if defined(BSP_USING_UART8)
    UART_INIT_STRUCT(8),
#endif

#if defined(BSP_USING_UART9)
    UART_INIT_STRUCT(9),
#endif

#if defined(BSP_USING_UART10)
    UART_INIT_STRUCT(10),
#endif

#if defined(BSP_USING_UART11)
    UART_INIT_STRUCT(11),
#endif

#if defined(BSP_USING_UART12)
    UART_INIT_STRUCT(12),
#endif

#if defined(BSP_USING_UART13)
    UART_INIT_STRUCT(13),
#endif

#if defined(BSP_USING_UART14)
    UART_INIT_STRUCT(14),
#endif

#if defined(BSP_USING_UART15)
    UART_INIT_STRUCT(15),
#endif

#if defined(BSP_USING_PUART)
    {
        .uart_base = HPM_PUART,
        .txbuf_size = BSP_PUART_TX_BUFSIZE,
        .rxbuf_size = BSP_PUART_RX_BUFSIZE,
        .irq_num = IRQn_PUART,
        .irq_priority = BSP_PUART_IRQ_PRIORITY,
        .clk_name = clock_puart,
        .serial = &serial_puart,
        .device_name = "puart",
        .rx_buffer_size = BSP_PUART_RX_BUFSIZE,
        .rx_fifo_index = 0,
    }
#endif
};



#if defined(RT_SERIAL_USING_DMA)

/**
 * @brief DMA transfer completion callback
 *
 * This function is called when a DMA transfer completes successfully.
 * It validates the DMA resource and calls the appropriate completion callback.
 *
 * @param base DMA controller base address
 * @param channel DMA channel number
 * @param user_data Pointer to DMA channel handle
 */
static void uart_dma_tc_callback(DMA_Type *base, uint32_t channel, void *user_data)
{
    hpm_dma_channel_handle_t *dma_handle = (hpm_dma_channel_handle_t*)user_data;

    /* Validate DMA resource to ensure this callback is for the correct channel */
    if ((dma_handle->resource.base != base) || (dma_handle->resource.channel != channel))
    {
        return;
    }

    /* Call the transfer completion callback */
    if (dma_handle->transfer_done != RT_NULL) {
        dma_handle->transfer_done(dma_handle->serial);
    }
}

#ifdef HPMSOC_HAS_HPMSDK_DMAV2
/**
 * @brief DMA half transfer completion callback
 *
 * This function is called when a DMA transfer reaches half completion.
 * It validates the DMA resource and calls the appropriate half transfer callback.
 *
 * @param base DMA controller base address
 * @param channel DMA channel number
 * @param user_data Pointer to DMA channel handle
 */
static void uart_dma_htc_callback(DMA_Type *base, uint32_t channel, void *user_data)
{
    hpm_dma_channel_handle_t *dma_handle = (hpm_dma_channel_handle_t*)user_data;

    /* Validate DMA resource to ensure this callback is for the correct channel */
    if ((dma_handle->resource.base != base) || (dma_handle->resource.channel != channel))
    {
        return;
    }

    /* Call the half transfer completion callback */
    if (dma_handle->halftransfer_cb != RT_NULL) {
        dma_handle->halftransfer_cb(dma_handle->serial);
    }
}

#endif

/**
 * @brief DMA receive interrupt service routine
 *
 * This function handles DMA receive interrupts, processes received data,
 * and notifies the RT-Thread serial framework about the received data.
 *
 * @param serial Pointer to the serial device structure
 * @param isr_flag Interrupt flag indicating the type of interrupt
 */
static void dma_recv_isr(struct rt_serial_device *serial, rt_uint8_t isr_flag)
{
    rt_size_t          recv_len, counter;
    rt_base_t level;
    RT_ASSERT(serial != RT_NULL);
    struct hpm_uart *uart = (struct hpm_uart *)serial->parent.user_data;
    
    /* Skip processing if ping buffer is not configured */
    if (serial->config.dma_ping_bufsz == 0) {
        return;
    }
    
    if (isr_flag == UART_RX_DMA_IT_TC_FLAG) {
        level = rt_hw_interrupt_disable();
        dma_mgr_disable_channel(&uart->rx_chn_ctx.resource);
    }
    counter = dma_get_remaining_transfer_size(uart->rx_chn_ctx.resource.base, uart->rx_chn_ctx.resource.channel);
    if (counter <= uart->dma_rx_remain_size) {
        recv_len = uart->dma_rx_remain_size - counter;
    } else {
        recv_len = serial->config.dma_ping_bufsz + uart->dma_rx_remain_size - counter;
    }
    if (recv_len > 0) {
        rt_uint8_t *ptr = NULL;
        rt_hw_serial_control_isr(serial, RT_HW_SERIAL_CTRL_GET_DMA_PING_BUF, (void *)&ptr);
        if (l1c_dc_is_enabled()) {
            uint32_t aligned_start = HPM_L1C_CACHELINE_ALIGN_DOWN((uint32_t)ptr);
            uint32_t aligned_end = HPM_L1C_CACHELINE_ALIGN_UP((uint32_t)ptr + serial->config.dma_ping_bufsz);
            uint32_t aligned_size = aligned_end - aligned_start;
            l1c_dc_invalidate(aligned_start, aligned_size);
        }
        uart->dma_rx_remain_size = counter;
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_DMADONE | (recv_len << 8));
    }
    if (isr_flag == UART_RX_DMA_IT_TC_FLAG) {
        rt_hw_interrupt_enable(level);
        dma_mgr_enable_channel(&uart->rx_chn_ctx.resource);
    }
}

/**
 * @brief DMA transfer abort callback
 *
 * This function is called when a DMA transfer is aborted.
 * It validates the DMA resource and calls the appropriate abort callback.
 *
 * @param base DMA controller base address
 * @param channel DMA channel number
 * @param user_data Pointer to DMA channel handle
 */
static void uart_dma_abort_callback(DMA_Type *base, uint32_t channel, void *user_data)
{
    hpm_dma_channel_handle_t *dma_handle = (hpm_dma_channel_handle_t*)user_data;

    /* Validate DMA resource to ensure this callback is for the correct channel */
    if ((dma_handle->resource.base != base) || (dma_handle->resource.channel != channel))
    {
        return;
    }

    /* Call the transfer abort callback */
    if (dma_handle->transfer_abort != RT_NULL) {
        dma_handle->transfer_abort(dma_handle->serial);
    }
}

/**
 * @brief DMA transfer error callback
 *
 * This function is called when a DMA transfer encounters an error.
 * It validates the DMA resource and calls the appropriate error callback.
 *
 * @param base DMA controller base address
 * @param channel DMA channel number
 * @param user_data Pointer to DMA channel handle
 */
static void uart_dma_error_callback(DMA_Type *base, uint32_t channel, void *user_data)
{
    hpm_dma_channel_handle_t *dma_handle = (hpm_dma_channel_handle_t*)user_data;

    /* Validate DMA resource to ensure this callback is for the correct channel */
    if ((dma_handle->resource.base != base) || (dma_handle->resource.channel != channel))
    {
        return;
    }

    /* Call the transfer error callback */
    if (dma_handle->transfer_error != RT_NULL) {
        dma_handle->transfer_error(dma_handle->serial);
    }
}

/**
 * @brief UART TX DMA transfer completion handler
 *
 * This function is called when a TX DMA transfer completes.
 * It notifies the RT-Thread serial framework about the completion.
 *
 * @param serial Pointer to the serial device structure
 */
static void uart_tx_done(struct rt_serial_device *serial)
{
    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DMADONE);
}

/**
 * @brief UART RX DMA transfer completion handler
 *
 * This function is called when an RX DMA transfer completes.
 * It handles cache coherency, processes received data, and notifies
 * the RT-Thread serial framework about the completion.
 *
 * @param serial Pointer to the serial device structure
 */
static void uart_rx_done(struct rt_serial_device *serial)
{
    struct rt_serial_rx_fifo *rx_fifo;
    rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;
#if defined(HPM_IP_FEATURE_UART_RX_IDLE_DETECT) && (HPM_IP_FEATURE_UART_RX_IDLE_DETECT == 1) && defined(RT_SERIAL_USING_DMA)
    dma_recv_isr(serial, UART_RX_DMA_IT_TC_FLAG);
#ifdef HPMSOC_HAS_HPMSDK_DMAV2
    /* DMAV2 supports circular mode, no need to reconfigure DMA, can return directly */
    return;
#endif
#else
    if (l1c_dc_is_enabled()) {
        uint32_t aligned_start = HPM_L1C_CACHELINE_ALIGN_DOWN((uint32_t)rx_fifo->rb.buffer_ptr);
        uint32_t aligned_end = HPM_L1C_CACHELINE_ALIGN_UP((uint32_t)rx_fifo->rb.buffer_ptr + serial->config.rx_bufsz);
        uint32_t aligned_size = aligned_end - aligned_start;
        l1c_dc_invalidate(aligned_start, aligned_size);
    }
    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_DMADONE | (serial->config.rx_bufsz << 8));
    /* prepare for next read */
#endif
    hpm_uart_receive_dma_next(serial);
}

#ifdef HPMSOC_HAS_HPMSDK_DMAV2
/**
 * @brief UART RX DMA half transfer completion handler
 *
 * This function is called when an RX DMA transfer reaches half completion.
 * It handles cache coherency and processes received data.
 *
 * @param serial Pointer to the serial device structure
 */
static void uart_rx_half_done(struct rt_serial_device *serial)
{
    dma_recv_isr(serial, UART_RX_DMA_IT_HT_FLAG);
}
#endif
#endif /* RT_SERIAL_USING_DMA */

/**
 * @brief UART common interrupt service routine
 *
 * This function handles all UART interrupt events including:
 * - RX data available: Reads data from UART FIFO and stores in ring buffer
 * - RX timeout: Handles timeout conditions and overrun errors
 * - TX slot available: Transmits data from ring buffer to UART FIFO
 * - RX idle detection: Handles DMA-based RX idle detection (if supported)
 *
 * The function processes interrupts efficiently by reading multiple bytes
 * when possible and managing ring buffer operations.
 *
 * @param serial Pointer to the serial device structure
 */
#ifndef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
static void hpm_uart_isr(struct rt_serial_device *serial)
#else
static void hpm_uart_isr(int vector, struct rt_serial_device *serial)
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */
{
    struct hpm_uart *uart;
    rt_uint32_t stat, enabled_irq;
    rt_uint8_t irq_id;
    rt_uint8_t count = 0;
    rt_uint8_t put_char = 0;

    RT_ASSERT(serial != RT_NULL);

    uart = (struct hpm_uart *)serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    struct rt_serial_rx_fifo *rx_fifo;
    rx_fifo = (struct rt_serial_rx_fifo *) serial->serial_rx;
    stat = uart_get_status(uart->uart_base);
    irq_id = uart_get_irq_id(uart->uart_base);

    if (irq_id == uart_intr_id_rx_data_avail) {
        while (uart_check_status(uart->uart_base, uart_stat_data_ready)) {
            count++;
            uart->rx_fifo_index++;
            put_char = uart_read_byte(uart->uart_base);
            rt_ringbuffer_putchar(&(rx_fifo->rb), put_char);
            /*in order to ensure rx fifo there are remaining bytes*/
            if (count > 12) {
                break;
            }
        }
    }
    /* check if RX FIFO index has reached minimum buffer size */
    if (uart->rx_fifo_index >= RT_SERIAL_RX_MINBUFSZ) {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        uart->rx_fifo_index = 0;
    }
    if (irq_id == uart_intr_id_rx_timeout) {
        while ((uart_check_status(uart->uart_base, uart_stat_data_ready)) || (uart_check_status(uart->uart_base, uart_stat_overrun_error))) {
            put_char= uart_read_byte(uart->uart_base);
            rt_ringbuffer_putchar(&(rx_fifo->rb), put_char);
        }
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        uart->rx_fifo_index = 0;
    }

    if ((irq_id == uart_intr_tx_slot_avail) && (stat & uart_stat_tx_slot_avail)) {
        /* UART in mode Transmitter */
        struct rt_serial_tx_fifo *tx_fifo;
        tx_fifo = (struct rt_serial_tx_fifo *) serial->serial_tx;
        RT_ASSERT(tx_fifo != RT_NULL);
        rt_uint8_t put_char = 0;
        uint32_t fifo_size = 0, ringbuffer_data_len = 0, tx_size = 0;
        fifo_size = uart_get_fifo_size(uart->uart_base);
        ringbuffer_data_len = rt_ringbuffer_data_len(&tx_fifo->rb);
        if (ringbuffer_data_len == 0) {
            uart_disable_irq(uart->uart_base, uart_intr_tx_slot_avail);
            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DONE);
        } else {
            tx_size = (ringbuffer_data_len > fifo_size) ? fifo_size : ringbuffer_data_len;
            for (uint32_t i = 0; i < tx_size; i++) {
                rt_ringbuffer_getchar(&tx_fifo->rb, &put_char);
                uart_write_byte(uart->uart_base, put_char);
            }
        }
    }
#if defined(HPM_IP_FEATURE_UART_RX_IDLE_DETECT) && (HPM_IP_FEATURE_UART_RX_IDLE_DETECT == 1) && defined(RT_SERIAL_USING_DMA)
    if (uart_is_rxline_idle(uart->uart_base)) {
        uart_clear_rxline_idle_flag(uart->uart_base);
        dma_recv_isr(serial, UART_RX_DMA_IT_IDLE_FLAG);
    }
#endif
}


/**
 * @brief Configure UART parameters
 *
 * This function configures the UART hardware with the specified parameters
 * including baud rate, data bits, stop bits, parity, and DMA settings.
 * It also initializes the UART pins and clock configuration.
 *
 * @param serial Pointer to the serial device structure
 * @param cfg Pointer to the serial configuration structure
 * @return RT_EOK on success, -RT_ERROR on failure
 */
static rt_err_t hpm_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    /* Validate input parameters */
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart_config_t uart_config;
    struct hpm_uart *uart  = (struct hpm_uart *)serial->parent.user_data;

    init_uart_pins(uart->uart_base);
    uart_default_config(uart->uart_base, &uart_config);
    clock_add_to_group(uart->clk_name, BOARD_RUNNING_CORE & 0x1);
    uart_config.src_freq_in_hz = clock_get_frequency(uart->clk_name);
    uart_config.baudrate = cfg->baud_rate;
    uart_config.num_of_stop_bits = cfg->stop_bits;
    uart_config.parity = cfg->parity;
    uart_config.rx_fifo_level = uart_rx_fifo_trg_gt_three_quarters;
#ifdef RT_SERIAL_USING_DMA
    if (uart->dma_flags & (RT_DEVICE_FLAG_DMA_TX | RT_DEVICE_FLAG_DMA_RX)) {
        uart_config.fifo_enable = true;
        uart_config.dma_enable = true;
        if (uart->dma_flags & RT_DEVICE_FLAG_DMA_TX) {
            uart_config.tx_fifo_level = uart_tx_fifo_trg_not_full;
        }
        if (uart->dma_flags & RT_DEVICE_FLAG_DMA_RX) {
            uart_config.rx_fifo_level = uart_rx_fifo_trg_not_empty;
        }
#if defined(HPM_IP_FEATURE_UART_RX_IDLE_DETECT) && (HPM_IP_FEATURE_UART_RX_IDLE_DETECT == 1)
        uart_config.rxidle_config.detect_enable = true;
        uart_config.rxidle_config.detect_irq_enable = true;
        uart_config.rxidle_config.idle_cond = uart_rxline_idle_cond_rxline_logic_one;
        uart_config.rxidle_config.threshold = 16U; /* 10bit */
#endif
    }

#endif

    uart_config.word_length = cfg->data_bits - DATA_BITS_5;
    hpm_stat_t status = uart_init(uart->uart_base, &uart_config);
    return (status != status_success) ? -RT_ERROR : RT_EOK;
}

#ifdef RT_SERIAL_USING_DMA

hpm_stat_t hpm_uart_dma_rx_init(struct hpm_uart *uart_ctx)
{
    hpm_stat_t status = status_fail;
    if (!uart_ctx->rx_resource_allocated)
    {
        status = dma_mgr_request_resource(&uart_ctx->rx_chn_ctx.resource);
        if (status == status_success)
        {
            uart_ctx->dma_flags |= RT_DEVICE_FLAG_DMA_RX;
            uart_ctx->rx_resource_allocated = true;
            dma_mgr_install_chn_tc_callback(&uart_ctx->rx_chn_ctx.resource, uart_dma_tc_callback, &uart_ctx->rx_chn_ctx);
#ifdef HPMSOC_HAS_HPMSDK_DMAV2
            dma_mgr_install_chn_half_tc_callback(&uart_ctx->rx_chn_ctx.resource, uart_dma_htc_callback, &uart_ctx->rx_chn_ctx);
#endif
            dma_mgr_install_chn_abort_callback(&uart_ctx->rx_chn_ctx.resource, uart_dma_abort_callback, &uart_ctx->rx_chn_ctx);
            dma_mgr_install_chn_error_callback(&uart_ctx->rx_chn_ctx.resource, uart_dma_error_callback, &uart_ctx->rx_chn_ctx);
        }
    }
    return status;
}

hpm_stat_t hpm_uart_dma_tx_init(struct hpm_uart *uart_ctx)
{
    hpm_stat_t status = status_fail;
    if (!uart_ctx->tx_resource_allocated)
    {
        status = dma_mgr_request_resource(&uart_ctx->tx_chn_ctx.resource);
        if (status == status_success)
        {
            uart_ctx->dma_flags |= RT_DEVICE_FLAG_DMA_TX;
            uart_ctx->tx_resource_allocated = true;
            dma_mgr_install_chn_tc_callback(&uart_ctx->tx_chn_ctx.resource, uart_dma_tc_callback, &uart_ctx->tx_chn_ctx);
            dma_mgr_install_chn_abort_callback(&uart_ctx->tx_chn_ctx.resource, uart_dma_abort_callback, &uart_ctx->tx_chn_ctx);
            dma_mgr_install_chn_error_callback(&uart_ctx->tx_chn_ctx.resource, uart_dma_error_callback, &uart_ctx->tx_chn_ctx);
        }
    }
    return status;
}

static int hpm_uart_dma_config(struct rt_serial_device *serial, void *arg)
{
    rt_ubase_t ctrl_arg = (rt_ubase_t) arg;
    struct hpm_uart *uart = (struct hpm_uart *)serial->parent.user_data;
    struct rt_serial_rx_fifo *rx_fifo;
    dma_mgr_chn_conf_t chg_config;
    dma_mgr_get_default_chn_config(&chg_config);
    if (ctrl_arg == RT_DEVICE_FLAG_DMA_RX) {
        rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;
        chg_config.dst_addr_ctrl = DMA_MGR_ADDRESS_CONTROL_INCREMENT;
        chg_config.dst_mode = DMA_MGR_HANDSHAKE_MODE_NORMAL;
        chg_config.dst_width = DMA_TRANSFER_WIDTH_BYTE;
        chg_config.en_dmamux = true;
        chg_config.dmamux_src = uart->rx_dma_mux;
        chg_config.src_addr = (uint32_t)&(uart->uart_base->RBR);
        chg_config.src_addr_ctrl = DMA_MGR_ADDRESS_CONTROL_FIXED;
        chg_config.src_mode = DMA_MGR_HANDSHAKE_MODE_HANDSHAKE;
        chg_config.src_width = DMA_TRANSFER_WIDTH_BYTE;

#if defined(HPM_IP_FEATURE_UART_RX_IDLE_DETECT) && (HPM_IP_FEATURE_UART_RX_IDLE_DETECT == 1)
#ifdef HPMSOC_HAS_HPMSDK_DMAV2
        chg_config.en_infiniteloop = true;
#endif
        uart->dma_rx_remain_size = serial->config.dma_ping_bufsz;
        rt_uint8_t *ptr = NULL;
        rt_hw_serial_control_isr(serial, RT_HW_SERIAL_CTRL_GET_DMA_PING_BUF, (void *)&ptr);
        chg_config.dst_addr = (uint32_t)ptr;
        chg_config.size_in_byte = serial->config.dma_ping_bufsz;
#else
        chg_config.dst_addr = (uint32_t)rx_fifo->rb.buffer_ptr;
        chg_config.size_in_byte = serial->config.rx_bufsz;
#endif
        if (status_success != dma_mgr_setup_channel(&uart->rx_chn_ctx.resource, &chg_config)) {
            return -RT_ERROR;
        }
        dma_mgr_enable_channel(&uart->rx_chn_ctx.resource);
#ifdef HPMSOC_HAS_HPMSDK_DMAV2
        dma_mgr_enable_chn_irq(&uart->rx_chn_ctx.resource, DMA_MGR_INTERRUPT_MASK_TC | DMA_MGR_INTERRUPT_MASK_HALF_TC);
        hpm_uart_dma_register_channel(serial, false, uart_rx_done, uart_rx_half_done, RT_NULL, RT_NULL);
#else
        dma_mgr_enable_chn_irq(&uart->rx_chn_ctx.resource, DMA_MGR_INTERRUPT_MASK_TC);
        hpm_uart_dma_register_channel(serial, false, uart_rx_done, RT_NULL, RT_NULL, RT_NULL);
#endif
        dma_mgr_enable_dma_irq_with_priority(&uart->rx_chn_ctx.resource, uart->irq_priority);
#if defined(HPM_IP_FEATURE_UART_RX_IDLE_DETECT) && (HPM_IP_FEATURE_UART_RX_IDLE_DETECT == 1)
        intc_m_enable_irq_with_priority(uart->irq_num, uart->irq_priority);
#endif
    } else if (ctrl_arg == RT_DEVICE_FLAG_DMA_TX) {
        chg_config.src_addr_ctrl = DMA_MGR_ADDRESS_CONTROL_INCREMENT;
        chg_config.src_mode = DMA_MGR_HANDSHAKE_MODE_NORMAL;
        chg_config.src_width = DMA_TRANSFER_WIDTH_BYTE;
        chg_config.dst_addr = (uint32_t)&uart->uart_base->THR;
        chg_config.dst_addr_ctrl = DMA_MGR_ADDRESS_CONTROL_FIXED;
        chg_config.dst_mode = DMA_MGR_HANDSHAKE_MODE_HANDSHAKE;
        chg_config.dst_width = DMA_TRANSFER_WIDTH_BYTE;
        chg_config.en_dmamux = true;
        chg_config.dmamux_src = uart->tx_dma_mux;
        if (status_success != dma_mgr_setup_channel(&uart->tx_chn_ctx.resource, &chg_config)) {
            return -RT_ERROR;
        }
        dma_mgr_enable_chn_irq(&uart->tx_chn_ctx.resource, DMA_MGR_INTERRUPT_MASK_TC);
        dma_mgr_enable_dma_irq_with_priority(&uart->tx_chn_ctx.resource, 1);
    }
    return RT_EOK;
}

static void hpm_uart_receive_dma_next(struct rt_serial_device *serial)
{
    uint32_t buf_addr;
    uint32_t buf_size;
    struct hpm_uart *uart = (struct hpm_uart *)serial->parent.user_data;
    struct rt_serial_rx_fifo *rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;
#if defined(HPM_IP_FEATURE_UART_RX_IDLE_DETECT) && (HPM_IP_FEATURE_UART_RX_IDLE_DETECT == 1)
        rt_uint8_t *ptr = NULL;
        uart->dma_rx_remain_size = serial->config.dma_ping_bufsz;
        rt_hw_serial_control_isr(serial, RT_HW_SERIAL_CTRL_GET_DMA_PING_BUF, (void *)&ptr);
        buf_addr = (uint32_t)ptr;
        buf_size = serial->config.dma_ping_bufsz;
#else
        buf_addr = (uint32_t)rx_fifo->rb.buffer_ptr;
        buf_size = serial->config.rx_bufsz;
#endif
    dma_mgr_set_chn_dst_addr(&uart->rx_chn_ctx.resource, buf_addr);
    dma_mgr_set_chn_transize(&uart->rx_chn_ctx.resource, buf_size);
    dma_mgr_enable_channel(&uart->rx_chn_ctx.resource);
}

static void hpm_uart_transmit_dma(struct rt_serial_device *serial, uint8_t *src, uint32_t size)
{
    struct hpm_uart *uart = (struct hpm_uart *)serial->parent.user_data;
    dma_mgr_set_chn_src_addr(&uart->tx_chn_ctx.resource, (uint32_t)src);
    dma_mgr_set_chn_transize(&uart->tx_chn_ctx.resource, size);
    dma_mgr_enable_channel(&uart->tx_chn_ctx.resource);
}

#endif /* RT_SERIAL_USING_DMA */

/**
 * @brief Control UART operations
 *
 * This function handles various UART control operations including:
 * - Interrupt enable/disable (RX/TX)
 * - DMA enable/disable and configuration
 * - Buffer allocation and management
 * - Operation mode checking
 *
 * @param serial Pointer to the serial device structure
 * @param cmd Control command (RT_DEVICE_CTRL_*)
 * @param arg Command argument
 * @return RT_EOK on success, -RT_ERROR on failure
 */
static rt_err_t hpm_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    /* Validate input parameters */
    RT_ASSERT(serial != RT_NULL);

    rt_ubase_t ctrl_arg = (rt_ubase_t) arg;
    uint8_t *tmp_buffer = NULL;
    struct rt_serial_rx_fifo *rx_fifo = (struct rt_serial_rx_fifo*)serial->serial_rx;
    struct rt_serial_tx_fifo *tx_fifo = (struct rt_serial_tx_fifo*)serial->serial_tx;
    struct hpm_uart *uart = (struct hpm_uart *)serial->parent.user_data;

    if(ctrl_arg & (RT_DEVICE_FLAG_RX_BLOCKING | RT_DEVICE_FLAG_RX_NON_BLOCKING))
    {
#ifdef RT_SERIAL_USING_DMA
        if (uart->dma_flags & RT_DEVICE_FLAG_DMA_RX)
        {
            ctrl_arg = RT_DEVICE_FLAG_DMA_RX;
        }
        else
#endif
        {
            ctrl_arg = RT_DEVICE_FLAG_INT_RX;
        }
    }
    else if(ctrl_arg & (RT_DEVICE_FLAG_TX_BLOCKING | RT_DEVICE_FLAG_TX_NON_BLOCKING))
    {
#ifdef RT_SERIAL_USING_DMA
        if (uart->dma_flags & RT_DEVICE_FLAG_DMA_TX)
        {
            ctrl_arg = RT_DEVICE_FLAG_DMA_TX;
        }
        else
#endif
        {
            ctrl_arg = RT_DEVICE_FLAG_INT_TX;
        }
    }

    switch (cmd) {
        case RT_DEVICE_CTRL_CLR_INT:
            if (ctrl_arg == RT_DEVICE_FLAG_INT_RX) {
                /* disable rx irq */
                uart_disable_irq(uart->uart_base, uart_intr_rx_data_avail_or_timeout);
                intc_m_disable_irq(uart->irq_num);
            }
            else if (ctrl_arg == RT_DEVICE_FLAG_INT_TX) {
                /* disable tx irq */
                uart_disable_irq(uart->uart_base, uart_intr_tx_slot_avail);
                intc_m_disable_irq(uart->irq_num);
            }
#ifdef RT_SERIAL_USING_DMA
            else if (ctrl_arg == RT_DEVICE_FLAG_DMA_TX) {
                dma_mgr_disable_chn_irq(&uart->tx_chn_ctx.resource, DMA_INTERRUPT_MASK_ALL);
                dma_abort_channel(uart->tx_chn_ctx.resource.base, uart->tx_chn_ctx.resource.channel);
                if (uart->tx_chn_ctx.ringbuf_ptr != RT_NULL) {
                    rt_free(uart->tx_chn_ctx.ringbuf_ptr);
                    uart->tx_chn_ctx.ringbuf_ptr = RT_NULL;
                }
            } else if (ctrl_arg == RT_DEVICE_FLAG_DMA_RX) {
                dma_mgr_disable_chn_irq(&uart->rx_chn_ctx.resource, DMA_INTERRUPT_MASK_ALL);
                dma_abort_channel(uart->rx_chn_ctx.resource.base, uart->rx_chn_ctx.resource.channel);
                if (uart->rx_chn_ctx.ringbuf_ptr != RT_NULL) {
                    rt_free(uart->rx_chn_ctx.ringbuf_ptr);
                    uart->rx_chn_ctx.ringbuf_ptr = RT_NULL;
                }
            }
#endif
            break;

        case RT_DEVICE_CTRL_SET_INT:
            if (ctrl_arg == RT_DEVICE_FLAG_INT_RX) {
                /* enable rx irq */
                uart_enable_irq(uart->uart_base, uart_intr_rx_data_avail_or_timeout);
                intc_m_enable_irq_with_priority(uart->irq_num, uart->irq_priority);
            } else if (ctrl_arg == RT_DEVICE_FLAG_INT_TX) {
                /* enable tx irq */
                intc_m_enable_irq_with_priority(uart->irq_num, uart->irq_priority);
            }
            break;

        case RT_DEVICE_CTRL_CONFIG:
#ifdef RT_SERIAL_USING_DMA
            if (ctrl_arg == RT_DEVICE_FLAG_DMA_RX) {
                    if ((!rx_fifo) || (((rt_uint32_t)rx_fifo->rb.buffer_ptr % HPM_L1C_CACHELINE_SIZE) || (rx_fifo->rb.buffer_size % HPM_L1C_CACHELINE_SIZE))) {
                    if (rx_fifo) {
                        rt_free(rx_fifo);
                    }
                    rx_fifo = RT_NULL;
                    rx_fifo = (struct rt_serial_rx_fifo *) rt_malloc(sizeof(struct rt_serial_rx_fifo));
                    RT_ASSERT(rx_fifo != RT_NULL);
                    
                    /* Calculate total buffer size needed for both ring buffers plus alignment padding */
                    rt_uint32_t rx_tmp_size = serial->config.rx_bufsz + serial->config.dma_ping_bufsz;
                    /* Allocate extra cacheline size for alignment:
                     * - 1x for main buffer alignment
                     * - 1x for ping buffer alignment (if ping buffer is used)
                     */
                    rt_uint32_t extra_align = (serial->config.dma_ping_bufsz > 0) ? 
                                              (2 * HPM_L1C_CACHELINE_SIZE) : HPM_L1C_CACHELINE_SIZE;
                    if (rx_tmp_size > (UINT32_MAX - extra_align)) {
                        return -RT_ERROR;
                    }
                    tmp_buffer = rt_malloc(rx_tmp_size + extra_align);
                    RT_ASSERT(tmp_buffer != RT_NULL);
                    
                    /* Free old buffer if exists */
                    if (uart->rx_chn_ctx.ringbuf_ptr != RT_NULL) {
                        rt_free(uart->rx_chn_ctx.ringbuf_ptr);
                    }
                    /* Save original pointer for later deallocation */
                    uart->rx_chn_ctx.ringbuf_ptr = (void *)tmp_buffer;
                    
                    /* Align first buffer (main RX ring buffer) */
                    tmp_buffer += (HPM_L1C_CACHELINE_SIZE - ((rt_ubase_t) tmp_buffer % HPM_L1C_CACHELINE_SIZE));
                    rt_ringbuffer_init(&rx_fifo->rb, tmp_buffer, serial->config.rx_bufsz);
                    rt_ringbuffer_reset(&rx_fifo->rb);
                    
                    /* Initialize DMA ping buffer only if size is non-zero */
                    if (serial->config.dma_ping_bufsz > 0) {
                        /* Move to next buffer position and align DMA ping buffer */
                        tmp_buffer += serial->config.rx_bufsz;  /* Move past the main buffer */
                        tmp_buffer += (HPM_L1C_CACHELINE_SIZE - ((rt_ubase_t) tmp_buffer % HPM_L1C_CACHELINE_SIZE));
                        rt_ringbuffer_init(&rx_fifo->dma_ping_rb, tmp_buffer, serial->config.dma_ping_bufsz);
                        rt_ringbuffer_reset(&rx_fifo->dma_ping_rb);
                    }
                    
                    serial->serial_rx = rx_fifo;
                }
            }

            if (ctrl_arg == RT_DEVICE_FLAG_DMA_TX) {
                    if ((!tx_fifo) || (((rt_uint32_t)tx_fifo->rb.buffer_ptr % HPM_L1C_CACHELINE_SIZE) || (tx_fifo->rb.buffer_size % HPM_L1C_CACHELINE_SIZE))) {
                    if (tx_fifo) {
                        rt_free(tx_fifo);
                    }
                    tx_fifo = RT_NULL;
                    tx_fifo = (struct rt_serial_tx_fifo *) rt_malloc(sizeof(struct rt_serial_tx_fifo));
                    RT_ASSERT(tx_fifo != RT_NULL);
                    tmp_buffer = rt_malloc(serial->config.tx_bufsz + HPM_L1C_CACHELINE_SIZE);
                    RT_ASSERT(tmp_buffer != RT_NULL);
                    if (uart->tx_chn_ctx.ringbuf_ptr != RT_NULL) {
                        rt_free(uart->tx_chn_ctx.ringbuf_ptr);
                    }
                    uart->tx_chn_ctx.ringbuf_ptr = (void *)tmp_buffer;
                    tmp_buffer += (HPM_L1C_CACHELINE_SIZE - ((rt_ubase_t) tmp_buffer % HPM_L1C_CACHELINE_SIZE));
                    rt_ringbuffer_init(&tx_fifo->rb, tmp_buffer, serial->config.tx_bufsz);
                    rt_ringbuffer_reset(&tx_fifo->rb);
                    tx_fifo->activated = RT_FALSE;
                    tx_fifo->put_size = 0;
                    serial->serial_tx = tx_fifo;
                }
            }

            if (ctrl_arg & (RT_DEVICE_FLAG_DMA_RX | RT_DEVICE_FLAG_DMA_TX)) {
                hpm_uart_dma_config(serial, (void *)ctrl_arg);
            } else
#endif
            {
                hpm_uart_control(serial, RT_DEVICE_CTRL_SET_INT, (void *)ctrl_arg);
            }
            break;
        case RT_DEVICE_CHECK_OPTMODE:
#ifdef RT_SERIAL_USING_DMA
            if ((ctrl_arg & RT_DEVICE_FLAG_DMA_TX)) {
                return RT_SERIAL_TX_BLOCKING_NO_BUFFER;
            } else
#endif
            {
                return RT_SERIAL_TX_BLOCKING_BUFFER;
            }
    }

    return RT_EOK;
}


/**
 * @brief Send a single character via UART
 *
 * This function sends a single character through the UART interface.
 * It uses blocking operation and flushes the UART buffer after transmission.
 *
 * @param serial Pointer to the serial device structure
 * @param ch Character to send
 * @return RT_EOK on success, -RT_ERROR on failure
 */
static int hpm_uart_putc(struct rt_serial_device *serial, char ch)
{
     hpm_stat_t stat;
     struct hpm_uart *uart = (struct hpm_uart *)serial->parent.user_data;

     /* Send the character and flush the UART buffer */
     stat = uart_send_byte(uart->uart_base, ch);
     if (stat == status_success) {
         stat = uart_flush(uart->uart_base);
     }
     return (stat == status_success) ? RT_EOK : -RT_ERROR;
}

/**
 * @brief Receive a single character from UART
 *
 * This function receives a single character from the UART interface.
 * It checks if data is available before attempting to read.
 *
 * @param serial Pointer to the serial device structure
 * @return The received character, or -1 if no data is available
 */
static int hpm_uart_getc(struct rt_serial_device *serial)
{
    int result = -1;
    struct hpm_uart *uart  = (struct hpm_uart *)serial->parent.user_data;

    /* Check if data is available in the UART FIFO */
    if (uart_check_status(uart->uart_base, uart_stat_data_ready)) {
        uart_receive_byte(uart->uart_base, (uint8_t*)&result);
    }

    return result;
}

/**
 * @brief Transmit data via UART
 *
 * This function transmits data through the UART interface using either
 * DMA or interrupt-driven methods based on the configuration.
 *
 * @param serial Pointer to the serial device structure
 * @param buf Pointer to the data buffer to transmit
 * @param size Number of bytes to transmit
 * @param tx_flag Transmission flags
 * @return Number of bytes transmitted
 */
static rt_ssize_t hpm_uart_transmit(struct rt_serial_device *serial,
                                    rt_uint8_t *buf,
                                    rt_size_t size,
                                    rt_uint32_t tx_flag)
{
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(buf != RT_NULL);
    RT_ASSERT(size);
    uint32_t fifo_size = 0, tx_size = 0;
    uint32_t ringbuffer_data_len = 0;
    struct hpm_uart *uart = (struct hpm_uart *)serial->parent.user_data;
    struct rt_serial_tx_fifo *tx_fifo;
    tx_fifo = (struct rt_serial_tx_fifo *) serial->serial_tx;
    uint8_t ch = 0;
    RT_ASSERT(tx_fifo != RT_NULL);
#ifdef RT_SERIAL_USING_DMA
    if (uart->dma_flags & RT_DEVICE_FLAG_DMA_TX) {
        hpm_uart_dma_register_channel(serial, true, uart_tx_done, RT_NULL, RT_NULL, RT_NULL);
        intc_m_enable_irq(uart->tx_chn_ctx.resource.irq_num);
        if (l1c_dc_is_enabled()) {
            uint32_t aligned_start = HPM_L1C_CACHELINE_ALIGN_DOWN((uint32_t)buf);
            uint32_t aligned_end = HPM_L1C_CACHELINE_ALIGN_UP((uint32_t)buf + size);
            uint32_t aligned_size = aligned_end - aligned_start;
            l1c_dc_flush(aligned_start, aligned_size);
        }
        hpm_uart_transmit_dma(serial, buf, size);
        return size;
    } else {
#else
    {
#endif

        if (size > 0) {
            if (uart_check_status(uart->uart_base, uart_stat_tx_slot_avail)) {
                uart_disable_irq(uart->uart_base, uart_intr_tx_slot_avail);
                fifo_size = uart_get_fifo_size(uart->uart_base);
                ringbuffer_data_len = rt_ringbuffer_data_len(&tx_fifo->rb);
                tx_size = (ringbuffer_data_len > fifo_size) ? fifo_size : ringbuffer_data_len;
                for (uint32_t i = 0; i < tx_size; i++) {
                    rt_ringbuffer_getchar(&tx_fifo->rb, &ch);
                    uart_write_byte(uart->uart_base, ch);
                }
                uart_enable_irq(uart->uart_base, uart_intr_tx_slot_avail);
            }
        }
    }
    return size;
}

/**
 * @brief UART operations structure
 *
 * This structure defines the function pointers for all UART operations.
 * It provides the interface between RT-Thread's serial framework and
 * the HPM UART driver implementation.
 */
static const struct rt_uart_ops hpm_uart_ops = {
    .configure = hpm_uart_configure,    /* Configure UART parameters */
    .control = hpm_uart_control,        /* Control UART operations */
    .putc = hpm_uart_putc,             /* Send single character */
    .getc = hpm_uart_getc,             /* Receive single character */
    .transmit = hpm_uart_transmit,     /* Transmit data buffer */
};



/**
 * @brief Configure all UART devices
 *
 * This function configures all enabled UART devices with default settings
 * and initializes DMA resources if configured. It sets up buffer sizes,
 * DMA channels, and other device-specific parameters.
 *
 * @return RT_EOK on success, -RT_ERROR on failure
 */
static int hpm_uart_config(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;  /* Default serial configuration */
    hpm_stat_t status = status_success;                         /* DMA initialization status */

    for (uint32_t i=0; i < ARRAY_SIZE(uarts); i++) {
        struct hpm_uart *uart = &uarts[i];
        uart->serial->config = config;
        uart->serial->config.rx_bufsz = uart->rxbuf_size;
        uart->serial->config.tx_bufsz = uart->txbuf_size;
        uart->dma_flags = 0;
        if (uart->enable_rx_dma) {
#if defined (RT_SERIAL_USING_DMA)
            status = hpm_uart_dma_rx_init(uart);
            if (status != status_success) {
                return -RT_ERROR;
            }
#else
            return -RT_ERROR;
#endif
        } else {
            uart->dma_flags = (uart->dma_flags & ~RT_DEVICE_FLAG_DMA_RX) | RT_DEVICE_FLAG_INT_RX;
        }
        if (uart->enable_tx_dma) {
#if defined (RT_SERIAL_USING_DMA)
            status = hpm_uart_dma_tx_init(uart);
            if (status != status_success) {
                return -RT_ERROR;
            }
#else
            return -RT_ERROR;
#endif
        } else {
            uart->dma_flags = (uart->dma_flags & ~RT_DEVICE_FLAG_DMA_TX) | RT_DEVICE_FLAG_INT_TX;
        }
#ifdef RT_SERIAL_USING_DMA
        if (uart->enable_rx_dma) {
            uart->serial->config.dma_ping_bufsz = uart->dma_pingpong_size;
        }
#endif
    }

    return RT_EOK;
}

/**
 * @brief Initialize UART hardware
 *
 * This function initializes all configured UART devices and registers them
 * with the RT-Thread device framework. It includes protection against
 * multiple initialization calls.
 *
 * @return RT_EOK on success, -RT_ERROR on failure
 */
int rt_hw_uart_init(void)
{
    /* Protection against multiple initialization calls */
    static bool initialized;
    rt_err_t err = RT_EOK;

    if (initialized)
    {
        return err;
    }
    else
    {
        initialized = true;
    }

    if (RT_EOK != hpm_uart_config()) {
        return -RT_ERROR;
    }

    for (uint32_t i = 0; i < ARRAY_SIZE(uarts); i++) {
        uarts[i].serial->ops = &hpm_uart_ops;

        /* register UART device */
        err = rt_hw_serial_register(uarts[i].serial,
                            uarts[i].device_name,
                            RT_DEVICE_FLAG_RDWR,
                            (void*)&uarts[i]);
#ifdef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
        /* Register UART device to irq table */
        rt_hw_interrupt_install(uarts[i].irq_num, (rt_isr_handler_t)hpm_uart_isr, uarts[i].serial, uarts[i].device_name);
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */
    }

    return err;
}

/* Register UART initialization function to be called during board initialization */
INIT_BOARD_EXPORT(rt_hw_uart_init);

#endif /* RT_USING_SERIAL_V2 */
