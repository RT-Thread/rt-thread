/*
 * ===========================================================================================
 *
 *       Filename:  hal_uart.c
 *
 *    Description:  hal impl. of uart.
 *
 *        Version:  Melis3.0
 *         Create:  2019-11-14 14:20:56
 *       Revision:  none
 *       Compiler:  GCC:version 9.2.1 20170904 (release),ARM/embedded-7-branch revision 255204
 *
 *         Author:  bantao@allwinnertech.com
 *   Organization:  SWC-BPD
 *  Last Modified:  2020-04-29 15:17:36
 *
 * ===========================================================================================
 */

#include <hal_uart.h>
#include <hal_interrupt.h>
#include <hal_queue.h>
#include <hal_clk.h>
#include <hal_reset.h>
#include <hal_gpio.h>
#ifdef CONFIG_DRIVER_SYSCONFIG
#include <hal_cfg.h>
#include <script.h>
#endif
#include "uart.h"

#if (0)
#define UART_LOG_DEBUG
#endif
#define UART_INIT(fmt, ...) printf("uart: "fmt, ##__VA_ARGS__)
#define UART_ERR(fmt, ...)  printf("uart: "fmt, ##__VA_ARGS__)

#ifdef UART_LOG_DEBUG
#define UART_INFO(fmt, ...) printf("[%s %d]"fmt, __func__, __LINE__, ##__VA_ARGS__)
#define UART_INFO_IRQ(fmt, ...) printf("[%s %d]"fmt, __func__, __LINE__, ##__VA_ARGS__)
#else
#define UART_INFO(fmt, ...)
#define UART_INFO_IRQ(fmt, ...)
#endif

static unsigned long sunxi_uart_port[] =
{
    SUNXI_UART0_BASE, SUNXI_UART1_BASE, SUNXI_UART2_BASE, SUNXI_UART3_BASE
};
static const uint32_t g_uart_irqn[] = {SUNXI_IRQ_UART0, SUNXI_IRQ_UART1,
                                       SUNXI_IRQ_UART2, SUNXI_IRQ_UART3
                                      };
static sunxi_hal_version_t hal_uart_driver =
{
    SUNXI_HAL_UART_API_VERSION,
    SUNXI_HAL_UART_DRV_VERSION
};
static uart_priv_t g_uart_priv[UART_MAX];

static hal_mailbox_t uart_mailbox[UART_MAX];

static const uint32_t g_uart_baudrate_map[] =
{
    300,
    600,
    1200,
    2400,
    4800,
    9600,
    19200,
    38400,
    57600,
    115200,
    230400,
    576000,
    921600,
    500000,
    1000000,
    1500000,
    3000000,
    4000000,
};

//driver capabilities, support uart function only.
static const sunxi_hal_uart_capabilities_t driver_capabilities =
{
    1, /* supports UART (Asynchronous) mode */
    0, /* supports Synchronous Master mode */
    0, /* supports Synchronous Slave mode */
    0, /* supports UART Single-wire mode */
    0, /* supports UART IrDA mode */
    0, /* supports UART Smart Card mode */
    0, /* Smart Card Clock generator available */
    0, /* RTS Flow Control available */
    0, /* CTS Flow Control available */
    0, /* Transmit completed event: \ref ARM_UARTx_EVENT_TX_COMPLETE */
    0, /* Signal receive character timeout event: \ref ARM_UARTx_EVENT_RX_TIMEOUT */
    0, /* RTS Line: 0=not available, 1=available */
    0, /* CTS Line: 0=not available, 1=available */
    0, /* DTR Line: 0=not available, 1=available */
    0, /* DSR Line: 0=not available, 1=available */
    0, /* DCD Line: 0=not available, 1=available */
    0, /* RI Line: 0=not available, 1=available */
    0, /* Signal CTS change event: \ref ARM_UARTx_EVENT_CTS */
    0, /* Signal DSR change event: \ref ARM_UARTx_EVENT_DSR */
    0, /* Signal DCD change event: \ref ARM_UARTx_EVENT_DCD */
    0, /* Signal RI change event: \ref ARM_UARTx_EVENT_RI */
    0  /* Reserved */
};

#ifdef CONFIG_SUNXI_UART_SUPPORT_POLL

static poll_wakeup_func uart_drv_poll_wakeup = NULL;

int32_t hal_uart_check_poll_state(int32_t dev_id, short key)
{
    int ret = -1;
    int32_t mask = 0;

    if (key & POLLIN)
    {
        ret = hal_is_mailbox_empty((hal_mailbox_t)uart_mailbox[dev_id]);
        if (ret == 1)
        {
            mask = 0;
        }
        else
        {
            mask |= POLLIN;
        }
    }

    if (key & POLLOUT)
    {
        mask |= POLLOUT;
    }
    return mask;
}

int32_t hal_uart_poll_wakeup(int32_t dev_id, short key)
{
    int ret = -1;

    if (uart_drv_poll_wakeup)
    {
        ret = uart_drv_poll_wakeup(dev_id, key);
    }

    return ret;
}

int32_t hal_uart_register_poll_wakeup(poll_wakeup_func poll_wakeup)
{
    uart_drv_poll_wakeup = poll_wakeup;

    return 0;
}

#endif

static bool uart_port_is_valid(uart_port_t uart_port)
{
    return (uart_port < UART_MAX);
}

static bool uart_config_is_valid(const _uart_config_t *config)
{
    return ((config->baudrate < UART_BAUDRATE_MAX) &&
            (config->word_length <= UART_WORD_LENGTH_8) &&
            (config->stop_bit <= UART_STOP_BIT_2) &&
            (config->parity <= UART_PARITY_EVEN));
}

sunxi_hal_version_t hal_uart_get_version(int32_t dev)
{
    HAL_ARG_UNUSED(dev);
    return hal_uart_driver;
}

sunxi_hal_uart_capabilities_t hal_uart_get_capabilities(int32_t dev)
{
    HAL_ARG_UNUSED(dev);
    return driver_capabilities;
}

static void uart_set_format(uart_port_t uart_port, uart_word_length_t word_length,
                            uart_stop_bit_t stop_bit, uart_parity_t parity)
{
    const unsigned long uart_base = sunxi_uart_port[uart_port];
    uart_priv_t *uart_priv = &g_uart_priv[uart_port];
    uint32_t value;

    value = hal_readb(uart_base + UART_LCR);

    /* set word length */
    value &= ~(UART_LCR_DLEN_MASK);
    switch (word_length)
    {
        case UART_WORD_LENGTH_5:
            value |= UART_LCR_WLEN5;
            break;
        case UART_WORD_LENGTH_6:
            value |= UART_LCR_WLEN6;
            break;
        case UART_WORD_LENGTH_7:
            value |= UART_LCR_WLEN7;
            break;
        case UART_WORD_LENGTH_8:
        default:
            value |= UART_LCR_WLEN8;
            break;
    }

    /* set stop bit */
    switch (stop_bit)
    {
        case UART_STOP_BIT_1:
        default:
            value &= ~(UART_LCR_STOP);
            break;
        case UART_STOP_BIT_2:
            value |= UART_LCR_STOP;
            break;
    }

    /* set parity bit */
    value &= ~(UART_LCR_PARITY_MASK);
    switch (parity)
    {
        case UART_PARITY_NONE:
            value &= ~(UART_LCR_PARITY);
            break;
        case UART_PARITY_ODD:
            value |= UART_LCR_PARITY;
            break;
        case UART_PARITY_EVEN:
            value |= UART_LCR_PARITY;
            value |= UART_LCR_EPAR;
            break;
    }

    uart_priv->lcr = value;
    hal_writeb(uart_priv->lcr, uart_base + UART_LCR);
}

#define CCM_UART_RST_OFFSET       (16)
#define CCM_UART_GATING_OFFSET    (0)
static void uart_reset(uart_port_t uart_port)
{
    int i;
    unsigned int reg_val = 0;

    /* 0x3001000(CCU) + 0x90c(UART_BGR_REG: UART Bus Gating Reset Register) */
    /* reset */
    reg_val = readl(0x0300190c);
    reg_val &= ~(1 << (CCM_UART_RST_OFFSET + uart_port));
    writel(reg_val, 0x0300190c);
    for (i = 0; i < 100; i++)
    ;

    reg_val = readl(0x300190c);
    reg_val |= (1 << (CCM_UART_RST_OFFSET + uart_port));
    writel(reg_val, 0x300190c);

    /* gating */
    reg_val = readl(0x300190c);
    reg_val &= ~(1 << (CCM_UART_GATING_OFFSET + uart_port));
    writel(reg_val, 0x300190c);
    for (i = 0; i < 100; i++)
    ;
    reg_val = readl(0x300190c);
    reg_val |= (1 << (CCM_UART_GATING_OFFSET + uart_port));
    writel(reg_val, 0x300190c);
}

static void uart_set_baudrate(uart_port_t uart_port, uart_baudrate_t baudrate)
{
    const unsigned long uart_base = sunxi_uart_port[uart_port];
    uart_priv_t *uart_priv = &g_uart_priv[uart_port];
    uint32_t actual_baudrate = g_uart_baudrate_map[baudrate];
    uint32_t quot, uart_clk;

    uart_clk = 24000000; /* FIXME: fixed to 24MHz */

    quot = (uart_clk + 8 * actual_baudrate) / (16 * actual_baudrate);

    UART_INFO("baudrate: %d, quot = %d\r\n", actual_baudrate, quot);

    uart_priv->dlh = quot >> 8;
    uart_priv->dll = quot & 0xff;

    /* hold tx so that uart will update lcr and baud in the gap of tx */
    hal_writeb(UART_HALT_HTX | UART_HALT_FORCECFG, uart_base + UART_HALT);
    hal_writeb(uart_priv->lcr | UART_LCR_DLAB, uart_base + UART_LCR);
    hal_writeb(uart_priv->dlh, uart_base + UART_DLH);
    hal_writeb(uart_priv->dll, uart_base + UART_DLL);
    hal_writeb(UART_HALT_HTX | UART_HALT_FORCECFG | UART_HALT_LCRUP, uart_base + UART_HALT);
    /* FIXME: implement timeout */
    while (hal_readb(uart_base + UART_HALT) & UART_HALT_LCRUP)
        ;

    /* In fact there are two DLABs(DLAB and DLAB_BAK) in the hardware implementation.
     * The DLAB_BAK is sellected only when SW_UART_HALT_FORCECFG is set to 1,
     * and this bit can be access no matter uart is busy or not.
     * So we select the DLAB_BAK always by leaving SW_UART_HALT_FORCECFG to be 1. */
    hal_writeb(uart_priv->lcr, uart_base + UART_LCR);
    hal_writeb(UART_HALT_FORCECFG, uart_base + UART_HALT);
}

static void uart_set_fifo(uart_port_t uart_port, uint32_t value)
{
    const unsigned long uart_base = sunxi_uart_port[uart_port];
    uart_priv_t *uart_priv = &g_uart_priv[uart_port];

    uart_priv->fcr = value;
    hal_writeb(uart_priv->fcr, uart_base + UART_FCR);
}

void hal_uart_set_hardware_flowcontrol(uart_port_t uart_port)
{
    const unsigned long uart_base = sunxi_uart_port[uart_port];
    uart_priv_t *uart_priv = &g_uart_priv[uart_port];
    uint32_t value;

    value = hal_readb(uart_base + UART_MCR);
    value |= UART_MCR_DTR | UART_MCR_RTS | UART_MCR_AFE;
    uart_priv->mcr = value;
    hal_writeb(uart_priv->mcr, uart_base + UART_MCR);

    /* enable with modem status interrupts */
    value = hal_readb(uart_base + UART_IER);
    value |= UART_IER_MSI;
    uart_priv->ier = value;
    hal_writeb(uart_priv->ier, uart_base + UART_IER);
}

void hal_uart_disable_flowcontrol(uart_port_t uart_port)
{
    const unsigned long uart_base = sunxi_uart_port[uart_port];
    uart_priv_t *uart_priv = &g_uart_priv[uart_port];
    uint32_t value;

    value = hal_readb(uart_base + UART_MCR);
    value &= ~(UART_MCR_DTR | UART_MCR_RTS | UART_MCR_AFE);
    uart_priv->mcr = value;
    hal_writeb(uart_priv->mcr, uart_base + UART_MCR);

    /* disable with modem status interrupts */
    value = hal_readb(uart_base + UART_IER);
    value &= ~(UART_IER_MSI);
    uart_priv->ier = value;
    hal_writeb(uart_priv->ier, uart_base + UART_IER);
}

static void uart_force_idle(uart_port_t uart_port)
{
    const unsigned long uart_base = sunxi_uart_port[uart_port];
    uart_priv_t *uart_priv = &g_uart_priv[uart_port];

    if (uart_priv->fcr & UART_FCR_FIFO_EN)
    {
        hal_writeb(UART_FCR_FIFO_EN, uart_base + UART_FCR);
        hal_writeb(UART_FCR_TXFIFO_RST
                   | UART_FCR_RXFIFO_RST
                   | UART_FCR_FIFO_EN, uart_base + UART_FCR);
        hal_writeb(0, uart_base + UART_FCR);
    }

    hal_writeb(uart_priv->fcr, uart_base + UART_FCR);
    (void)hal_readb(uart_base + UART_FCR);
}

static void uart_handle_busy(uart_port_t uart_port)
{
    const unsigned long uart_base = sunxi_uart_port[uart_port];
    uart_priv_t *uart_priv = &g_uart_priv[uart_port];

    (void)hal_readb(uart_base + UART_USR);

    /*
     * Before reseting lcr, we should ensure than uart is not in busy
     * state. Otherwise, a new busy interrupt will be introduced.
     * It is wise to set uart into loopback mode, since it can cut down the
     * serial in, then we should reset fifo(in my test, busy state
     * (UART_USR_BUSY) can't be cleard until the fifo is empty).
     */
    hal_writeb(uart_priv->mcr | UART_MCR_LOOP, uart_base + UART_MCR);
    uart_force_idle(uart_port);
    hal_writeb(uart_priv->lcr, uart_base + UART_LCR);
    hal_writeb(uart_priv->mcr, uart_base + UART_MCR);
}

rt_weak void hal_uart_handler_hook(uart_port_t uart_port)
{
}

static uint32_t uart_handle_rx(uart_port_t uart_port, uint32_t lsr)
{
    const unsigned long uart_base = sunxi_uart_port[uart_port];
    uint8_t ch = 0;

    UART_INFO("IRQ uart%d handle rx \n", uart_port);
    do
    {
        if (lsr & UART_LSR_DR)
        {
            ch = hal_readb(uart_base + UART_RBR);
            hal_mailbox_send((hal_mailbox_t)uart_mailbox[uart_port], ch);
#ifdef CONFIG_SUNXI_UART_SUPPORT_POLL
            hal_uart_poll_wakeup(uart_port, POLLIN);
#endif
        }
        lsr = hal_readb(uart_base + UART_LSR);
    } while ((lsr & (UART_LSR_DR | UART_LSR_BI)));

    /* wakeup console here */
    hal_uart_handler_hook(uart_port);

    return lsr;
}


static irqreturn_t uart_irq_handler(int irq, void *dev_id)
{
    uart_priv_t *uart_priv = dev_id;
    uart_port_t uart_port = uart_priv->uart_port;
    const unsigned long uart_base = sunxi_uart_port[uart_port];
    uint32_t iir, lsr;

    iir = hal_readb(uart_base + UART_IIR) & UART_IIR_IID_MASK;
    lsr = hal_readb(uart_base + UART_LSR);

    UART_INFO_IRQ("IRQ uart%d lsr is %08x \n", uart_port, lsr);
    if (iir == UART_IIR_IID_BUSBSY)
    {
        uart_handle_busy(uart_port);
    }
    else
    {
        if (lsr & (UART_LSR_DR | UART_LSR_BI))
        {
            lsr = uart_handle_rx(uart_port, lsr);
        }
        else if (iir & UART_IIR_IID_CHARTO)
            /* has charto irq but no dr lsr? just read and ignore */
        {
            hal_readb(uart_base + UART_RBR);
        }

        /* if (lsr & UART_LSR_THRE)
    {
        uart_handle_tx(uart_port);
    }*/
    }
    return 0;
}

static void uart_enable_irq(uart_port_t uart_port, uint32_t irq_type)
{
    const unsigned long uart_base = sunxi_uart_port[uart_port];
    uint32_t value;

    value = hal_readb(uart_base + UART_IER);
    value |= irq_type;
    hal_writeb(value, uart_base + UART_IER);

}

static void uart_enable_busy_cfg(uart_port_t uart_port)
{
    const unsigned long uart_base = sunxi_uart_port[uart_port];
    uint32_t value;

    value = hal_readb(uart_base + UART_HALT);
    value |= UART_HALT_FORCECFG;
    hal_writeb(value, uart_base + UART_HALT);
}

static int uart_clk_init(int bus, bool enable)
{
    hal_clk_status_t ret;
    hal_reset_type_t reset_type = HAL_SUNXI_RESET;
    u32  reset_id;
    hal_clk_type_t clk_type = HAL_SUNXI_CCU;
    hal_clk_id_t clk_id;
    hal_clk_t clk;
    struct reset_control *reset;

    switch (bus)
    {
        case 0:
        clk_id = SUNXI_CLK_UART0;
        reset_id = SUNXI_RST_UART0;
            break;
        case 1:
        clk_id = SUNXI_CLK_UART1;
        reset_id = SUNXI_RST_UART1;
            break;
        case 2:
        clk_id = SUNXI_CLK_UART2;
        reset_id = SUNXI_RST_UART2;
            break;
        case 3:
        clk_id = SUNXI_CLK_UART3;
        reset_id = SUNXI_RST_UART3;
            break;
        default:
            UART_ERR("uart%d is invalid\n", bus);
            return -1;
    }
    if (enable)
    {
    reset = hal_reset_control_get(reset_type, reset_id);
    hal_reset_control_deassert(reset);
    hal_reset_control_put(reset);

    clk = hal_clock_get(clk_type, clk_id);
        ret = hal_clock_enable(clk);
        if (ret)
        {
            UART_ERR("[uart%d] couldn't enable clk!\n", bus);
            return -1;
        }
    }
    else
    {
        clk = hal_clock_get(clk_type, clk_id);
        ret = hal_clock_disable(clk);
        if (ret)
        {
            UART_ERR("[uart%d] couldn't disable clk!\n", bus);
            return -1;
        }
    }
    return 0;
}

static void uart_pinctrl_init(uart_port_t uart_port)
{
#ifdef CONFIG_DRIVER_SYSCONFIG
    user_gpio_set_t gpio_cfg[4];
    int count, i;
    char uart_name[16];
    gpio_pin_t uart_pin[4];
    gpio_muxsel_t uart_muxsel[4];

    memset(gpio_cfg, 0, sizeof(gpio_cfg));
    sprintf(uart_name, "uart%d", uart_port);
    count = Hal_Cfg_GetGPIOSecKeyCount(uart_name);
    if (!count)
    {
        UART_ERR("[uart%d] not support in sys_config\n", uart_port);
    return ;
    }
    Hal_Cfg_GetGPIOSecData(uart_name, gpio_cfg, count);


    for (i = 0; i < count; i++)
    {
    uart_pin[i] = (gpio_cfg[i].port - 1) * 32 + gpio_cfg[i].port_num;
    uart_muxsel[i] = gpio_cfg[i].mul_sel;
        hal_gpio_pinmux_set_function(uart_pin[i], uart_muxsel[i]);
    }
#else
/* TODO:use sys_config instead it, but DSP does not support sys_config */
    switch (uart_port)
    {
        case UART_0:
            hal_gpio_set_pull(UART0_RX, GPIO_PULL_UP);
            hal_gpio_pinmux_set_function(UART0_TX, UART0_GPIO_FUNCTION);//TX
            hal_gpio_pinmux_set_function(UART0_RX, UART0_GPIO_FUNCTION);//RX
            break;
        case UART_1:
            hal_gpio_set_pull(UART1_RX, GPIO_PULL_UP);
            hal_gpio_pinmux_set_function(UART1_TX, UART1_GPIO_FUNCTION);//TX
            hal_gpio_pinmux_set_function(UART1_RX, UART1_GPIO_FUNCTION);//RX
            break;
        case UART_2:
            hal_gpio_set_pull(UART2_RX, GPIO_PULL_UP);
            hal_gpio_pinmux_set_function(UART2_TX, UART2_GPIO_FUNCTION);//TX
            hal_gpio_pinmux_set_function(UART2_RX, UART2_GPIO_FUNCTION);//RX
            break;
        case UART_3:
            hal_gpio_set_pull(UART3_RX, GPIO_PULL_UP);
            hal_gpio_pinmux_set_function(UART3_TX, UART3_GPIO_FUNCTION);//TX
            hal_gpio_pinmux_set_function(UART3_RX, UART3_GPIO_FUNCTION);//RX
            break;
        default:
            UART_ERR("[uart%d] not support \n", uart_port);
            break;
    }
#endif
}

static void uart_pinctrl_uninit(uart_port_t uart_port)
{
    switch (uart_port)
    {
        case UART_0:
            hal_gpio_pinmux_set_function(UART0_TX, GPIO_MUXSEL_DISABLED);//TX
            hal_gpio_pinmux_set_function(UART0_RX, GPIO_MUXSEL_DISABLED);//RX
            break;
        case UART_1:
            hal_gpio_pinmux_set_function(UART1_TX, GPIO_MUXSEL_DISABLED);//TX
            hal_gpio_pinmux_set_function(UART1_RX, GPIO_MUXSEL_DISABLED);//RX
            break;
        case UART_2:
            hal_gpio_pinmux_set_function(UART2_TX, GPIO_MUXSEL_DISABLED);//TX
            hal_gpio_pinmux_set_function(UART2_RX, GPIO_MUXSEL_DISABLED);//RX
            break;
        case UART_3:
            hal_gpio_pinmux_set_function(UART3_TX, GPIO_MUXSEL_DISABLED);//TX
            hal_gpio_pinmux_set_function(UART3_RX, GPIO_MUXSEL_DISABLED);//RX
            break;
        default:
            UART_ERR("[uart%d] not support \n", uart_port);
            break;
    }
}

/* default uart config */
_uart_config_t uart_defconfig =
{
    .baudrate    = UART_BAUDRATE_115200,
    .word_length = UART_WORD_LENGTH_8,
    .stop_bit    = UART_STOP_BIT_1,
    .parity      = UART_PARITY_NONE,
};

int32_t hal_uart_init(int32_t uart_port)
{
    uart_priv_t *uart_priv = &g_uart_priv[uart_port];
    uint32_t irqn = g_uart_irqn[uart_port];
    uint32_t value = 0;
    _uart_config_t *uart_config = &uart_defconfig;
    char uart_name[12] = {0};

    if ((!uart_port_is_valid(uart_port)) ||
        (!uart_config_is_valid(uart_config)))
    {
        return HAL_UART_STATUS_ERROR_PARAMETER;
    }

    /* enable clk */
    uart_clk_init(uart_port, true);

    /* request gpio */
    uart_pinctrl_init(uart_port);

    /* config uart attributes */
    uart_set_format(uart_port, uart_config->word_length,
                    uart_config->stop_bit, uart_config->parity);

    /* force reset controller to disable transfer */
    uart_reset(uart_port);

    uart_set_baudrate(uart_port, uart_config->baudrate);

    value |= UART_FCR_RXTRG_1_2 | UART_FCR_TXTRG_1_2 | UART_FCR_FIFO_EN;
    uart_set_fifo(uart_port, value);

    sprintf(uart_name, "uart%d", (int)uart_port);
    if (uart_priv->uart_port == uart_port && uart_priv->irqn == irqn)
    {
        UART_ERR("irq for uart%ld already enabled\n", (long int)uart_port);
    }
    else
    {
        uart_priv->uart_port = uart_port;
        uart_priv->irqn = irqn;

        #if 1
        if (request_irq(irqn, uart_irq_handler, 0, uart_name, uart_priv) < 0)
        {
            UART_ERR("request irq error\n");
            return -1;
        }
        enable_irq(irqn);
        #endif

        #if 0
        rt_hw_interrupt_install(irqn, uart_irq_handler, uart_priv, uart_name);
        rt_hw_interrupt_umask(irqn);
        #endif
    }

    uart_mailbox[uart_port] = hal_mailbox_create(uart_name, UART_FIFO_SIZE);
    if (uart_mailbox[uart_port] == NULL)
    {
        UART_ERR("create mailbox fail\n");
        return HAL_UART_STATUS_ERROR;
    }

    /* set uart IER */
    uart_enable_irq(uart_port, UART_IER_RDI | UART_IER_RLSI);

    /* force config */
    uart_enable_busy_cfg(uart_port);

    return SUNXI_HAL_OK;
}

int32_t hal_uart_deinit(int32_t uart_port)
{
    /* disable clk */
    uart_clk_init(uart_port, false);
    uart_pinctrl_uninit(uart_port);

    return SUNXI_HAL_OK;
}

int32_t hal_uart_power_control(int32_t dev, sunxi_hal_power_state_e state)
{
    return SUNXI_HAL_OK;
}

static int _uart_putc(int devid, char c)
{
    volatile uint32_t *sed_buf;
    volatile uint32_t *sta;

    sed_buf = (uint32_t *)(sunxi_uart_port[devid] + UART_THR);
    sta = (uint32_t *)(sunxi_uart_port[devid] + UART_USR);

    /* FIFO status, contain valid data */
    while (!(*sta & 0x02));
    *sed_buf = c;

    return 1;
}

int32_t hal_uart_put_char(int32_t dev, char c)
{
    return _uart_putc(dev, c);
}

int32_t hal_uart_send(int32_t dev, const uint8_t *data, uint32_t num)
{
    int size;

    hal_assert(data != NULL);

    size = num;
    while (num)
    {
        _uart_putc(dev, *data);

        ++ data;
        -- num;
    }

    return size - num;
}

static int _uart_getc(int devid)
{
    int ch = -1;
    volatile uint32_t *rec_buf;
    volatile uint32_t *sta;
    volatile uint32_t *fifo;

    rec_buf = (uint32_t *)(sunxi_uart_port[devid] + UART_RHB);
    sta = (uint32_t *)(sunxi_uart_port[devid] + UART_USR);
    fifo = (uint32_t *)(sunxi_uart_port[devid] + UART_RFL);

    while (!(*fifo & 0x1ff));

    /* Receive Data Available */
    if (*sta & 0x08)
    {
        ch = *rec_buf & 0xff;
    }

    return ch;
}

uint8_t hal_uart_get_char(int32_t dev)
{
    return _uart_getc(dev);
}

int32_t hal_uart_receive_polling(int32_t dev, uint8_t *data, uint32_t num)
{
    int ch;
    int size;

    hal_assert(data != NULL);
    size = num;

    while (num)
    {
        ch = _uart_getc(dev);
        if (ch == -1)
        {
            break;
        }

        *data = ch;
        data ++;
        num --;

    /* FIXME: maybe only used for console? move it away! */
        if (ch == '\n')
        {
            break;
        }
    }

    return size - num;
}

int32_t hal_uart_receive(int32_t dev, uint8_t *data, uint32_t num)
{
    unsigned int data_rev;
    int i = 0;
    int32_t ret = -1, rev_count = 0;

    hal_assert(data != NULL);

    for (i = 0; i < num; i++)
    {
        ret = hal_mailbox_recv((hal_mailbox_t)uart_mailbox[dev], &data_rev, -1);
        if (ret == 0)
        {
            rev_count++;
        *(data + i) = (uint8_t)data_rev;
        }
        else
        {
            UART_ERR("receive error");
            break;
        }
    }

    return rev_count;
}

int32_t hal_uart_receive_no_block(int32_t dev, uint8_t *data, uint32_t num, int32_t timeout)
{
    unsigned int data_rev;
    int i = 0;
    int32_t ret = -1, rev_count = 0;

    hal_assert(data != NULL);

    for (i = 0; i < num; i++)
    {
        ret = hal_mailbox_recv((hal_mailbox_t)uart_mailbox[dev], &data_rev, timeout);
        if (ret == 0)
        {
            rev_count++;
            *(data + i) = (uint8_t)data_rev;
        }
        else
        {
            break;
        }
    }

    return rev_count;
}


int32_t hal_uart_transfer(int32_t dev, const void *data_out,
                        void *data_in, uint32_t num)
{
    return SUNXI_HAL_OK;
}

uint32_t hal_uart_get_tx_count(int32_t dev)
{
    /* TODO: need verify */
    return 0;
}

uint32_t hal_uart_get_rx_count(int32_t dev)
{
    /* TODO: need verify */
    return 0;
}

int32_t hal_uart_control(int32_t uart_port, int cmd, void *args)
{
    _uart_config_t *uart_config;
    uart_config = (_uart_config_t *)args;

    /* config uart attributes */
    uart_set_format(uart_port, uart_config->word_length,
            uart_config->stop_bit, uart_config->parity);
    uart_set_baudrate(uart_port, uart_config->baudrate);

    return SUNXI_HAL_OK;
}

sunxi_hal_uart_status_t hal_uart_get_status(int32_t dev)
{
    sunxi_hal_uart_status_t status = {1, 1, 0, 0, 0, 0, 0, 0};

    return status;
}

int32_t hal_uart_set_modem_control(int32_t dev,
                        sunxi_hal_uart_modem_control_e control)
{
    return SUNXI_HAL_OK;
}

sunxi_hal_uart_modem_status_t hal_uart_get_modem_status(int32_t dev)
{
    sunxi_hal_uart_modem_status_t status = {0, 0, 0, 0, 0};

    return status;
}

void hal_uart_set_loopback(uart_port_t uart_port, bool enable)
{
    const unsigned long uart_base = sunxi_uart_port[uart_port];
    uint32_t value;

    value = hal_readb(uart_base + UART_MCR);
    if (enable)
        value |= UART_MCR_LOOP;
    else
        value &= ~(UART_MCR_LOOP);
    hal_writeb(value, uart_base + UART_MCR);

}

int serial_driver_init(void)
{
    UART_INFO("serial hal driver init");
    return 0;
}

