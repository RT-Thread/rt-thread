#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <board.h>

/* CME-M7 uart driver */
struct CME_M7_uart
{
    UART0_Type* uart_device;
    IRQn_Type irq;
};

#ifdef RT_USING_UART0
struct CME_M7_uart uart0 =
{
    UART0,
    UART0_INT_IRQn,
};
static struct rt_serial_device serial0;
#endif /* RT_USING_UART0 */

#ifdef RT_USING_UART2
struct CME_M7_uart uart2 =
{
    UART2,
    UART2_INT_IRQn,
};
static struct rt_serial_device serial2;
#endif /* RT_USING_UART2 */

static rt_err_t nuc400_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct CME_M7_uart* uart;
	UART_InitTypeDef init;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = (struct CME_M7_uart *)serial->parent.user_data;

	init.UART_BaudRate = cfg->baud_rate;
	init.UART_StopBits = UART_StopBits_1;
    init.UART_Parity = UART_Parity_None;
	init.UART_LoopBack = FALSE;
	init.UART_RxEn = FALSE;
	init.UART_CtsEn = FALSE;

    UART_Init(uart->uart_device, &init);
	UART_Enable(uart->uart_device, TRUE);

    return RT_EOK;
}

static rt_err_t nuc400_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct CME_M7_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct CME_M7_uart *)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
//        UART_DisableInt(uart->uart_device, UART_INTEN_RDAIEN_Msk);
//        NVIC_DisableIRQ(uart->irq);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
//        UART_EnableInt(uart->uart_device, UART_INTEN_RDAIEN_Msk);
//        NVIC_EnableIRQ(uart->irq);
        break;
    }

    return RT_EOK;
}

static int nuc400_putc(struct rt_serial_device *serial, char ch)
{
    struct CME_M7_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct CME_M7_uart *)serial->parent.user_data;

    while (0 == UART_Write(uart->uart_device, 1, &ch)) ;

//    while(UART_GET_TX_FULL(uart->uart_device)); //waits for TXFULL bit is clear
//    uart->uart_device->DAT = ch;

    return 1;
}

static int nuc400_getc(struct rt_serial_device *serial)
{
    int ch;
    struct CME_M7_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct CME_M7_uart *)serial->parent.user_data;

    ch = -1;

//    if(!UART_GET_RX_EMPTY(uart->uart_device))
//    {
//        ch = uart->uart_device->DAT; /* Get Data from UART RX  */
//    }

    return ch;
}

static const struct rt_uart_ops CME_M7_uart_ops =
{
    nuc400_configure,
    nuc400_control,
    nuc400_putc,
    nuc400_getc,
};

int rt_hw_uart_init(void)
{
	struct CME_M7_uart* uart;
	struct rt_serial_device *serial;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef RT_USING_UART0
    CLK->APBCLK0 |= CLK_APBCLK0_UART0CKEN_Msk; // UART0 Clock Enable
    uart = &uart0;

    serial0.ops    = &CME_M7_uart_ops;
    serial0.config = config;

	/* register UART device */
    rt_hw_serial_register(&serial0,
                          "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* RT_USING_UART0 */

#ifdef RT_USING_UART2
    uart = &uart2;
    serial = &serial2;

    serial->ops    = &CME_M7_uart_ops;
    serial->config = config;

	/* register UART device */
    rt_hw_serial_register(serial,
                          "uart2",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* RT_USING_UART2 */

	return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);

#ifdef RT_USING_UART0
void UART0_IRQHandler(void)
{
    rt_hw_serial_isr(&serial0, RT_SERIAL_EVENT_RX_IND);
}
#endif /* RT_USING_UART0 */

#ifdef RT_USING_UART2
void UART2_IRQHandler(void)
{
    //rt_hw_serial_isr(&serial0, RT_SERIAL_EVENT_RX_IND);
}
#endif /* RT_USING_UART2 */
