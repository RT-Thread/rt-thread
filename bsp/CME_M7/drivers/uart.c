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

static rt_err_t CME_M7_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
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
    init.UART_RxEn = TRUE;
    init.UART_CtsEn = FALSE;

    UART_Init(uart->uart_device, &init);
    uart->uart_device->RX_RESET = 1;
    UART_Enable(uart->uart_device, TRUE);
    uart->uart_device->RX_RESET = 0;

    return RT_EOK;
}

static rt_err_t CME_M7_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct CME_M7_uart* uart;
    NVIC_InitTypeDef NVIC_InitStructure;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct CME_M7_uart *)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_InitStructure.NVIC_IRQChannel = uart->irq;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelCmd = FALSE;
        NVIC_Init(&NVIC_InitStructure);

        UART_EnableInt(uart->uart_device, UART_Int_RxNotEmpty, FALSE);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_InitStructure.NVIC_IRQChannel = uart->irq;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelCmd = TRUE;
        NVIC_Init(&NVIC_InitStructure);

        UART_ClearInt(uart->uart_device, UART_Int_RxNotEmpty);
        UART_EnableInt(uart->uart_device, UART_Int_RxNotEmpty, TRUE);
        break;
    }

    return RT_EOK;
}

static int CME_M7_putc(struct rt_serial_device *serial, char ch)
{
    struct CME_M7_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct CME_M7_uart *)serial->parent.user_data;

    while(uart->uart_device->STATUS_b.TF); //waits for transmitter FIFO not full.
    uart->uart_device->TX_BUF = ch;

    return 1;
}

static int CME_M7_getc(struct rt_serial_device *serial)
{
    int ch;
    struct CME_M7_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct CME_M7_uart *)serial->parent.user_data;

    ch = -1;

    if(uart->uart_device->STATUS_b.RNE)
    {
        ch = uart->uart_device->RX_BUF & 0x00FF; /* Get Data from UART RX  */
    }

    return ch;
}

static const struct rt_uart_ops CME_M7_uart_ops =
{
    CME_M7_configure,
    CME_M7_control,
    CME_M7_putc,
    CME_M7_getc,
};

int rt_hw_uart_init(void)
{
    struct CME_M7_uart* uart;
    struct rt_serial_device *serial;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef RT_USING_UART0
    uart = &uart0;
    serial = &serial0;

    serial->ops    = &CME_M7_uart_ops;
    serial->config = config;

    /* register UART device */
    rt_hw_serial_register(serial,
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

static void CME_UART_IRQHandler(struct rt_serial_device *serial)
{
    struct CME_M7_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct CME_M7_uart *)serial->parent.user_data;

    if(UART_GetIntStatus(uart->uart_device, UART_Int_RxNotEmpty))
    {
        UART_ClearInt(uart->uart_device, UART_Int_RxNotEmpty);
        rt_hw_serial_isr(&serial2, RT_SERIAL_EVENT_RX_IND);
    }

    if(UART_GetIntStatus(uart->uart_device, UART_Int_RxThresholdReach))
    {
        UART_ClearInt(uart->uart_device, UART_Int_RxThresholdReach);
    }

    if(UART_GetIntStatus(uart->uart_device, UART_Int_OverrunError))
    {
        UART_ClearInt(uart->uart_device, UART_Int_OverrunError);
    }

    if(UART_GetIntStatus(uart->uart_device, UART_Int_FrameError))
    {
        UART_ClearInt(uart->uart_device, UART_Int_FrameError);
    }

    if(UART_GetIntStatus(uart->uart_device, UART_Int_ParityError))
    {
        UART_ClearInt(uart->uart_device, UART_Int_ParityError);
    }
}

#ifdef RT_USING_UART0
void UART0_IRQHandler(void)
{
    CME_UART_IRQHandler(&serial0);
}
#endif /* RT_USING_UART0 */

#ifdef RT_USING_UART2
void UART2_IRQHandler(void)
{
    CME_UART_IRQHandler(&serial2);
}
#endif /* RT_USING_UART2 */
