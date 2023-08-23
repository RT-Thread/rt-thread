#include "stdio.h"
#include "xparameters.h"
#include "xscugic.h"
#include "xuartps.h"
#include "zynq7000.h"

#include "board.h"
#include <rtdevice.h>
#include <rthw.h>

struct hw_uart_device
{
    XUartPs uart;
    rt_uint32_t irqno;
    uint16_t dev_id;
    u32 base_addr;
    rt_bool_t inited;
};

#ifdef BSP_USING_UART0
static struct hw_uart_device _uart_device0 = {
    .dev_id = XPAR_PS7_UART_0_DEVICE_ID,
    .irqno = IRQ_Zynq7000_UART0,
    .base_addr = XPAR_PS7_UART_0_BASEADDR,
    .inited = RT_FALSE,
};
#endif

#ifdef BSP_USING_UART1
static struct hw_uart_device _uart_device1 = {
    .dev_id = XPAR_PS7_UART_1_DEVICE_ID,
    .irqno = IRQ_Zynq7000_UART1,
    .base_addr = XPAR_PS7_UART_1_BASEADDR,
    .inited = RT_FALSE,
};
#endif

rt_inline rt_err_t _uart_init(struct hw_uart_device *device)
{
    XUartPs_Config *uart_cfg = XUartPs_LookupConfig(device->dev_id);
    if (NULL == uart_cfg)
        return XST_FAILURE;
    int status = XUartPs_CfgInitialize(&device->uart, uart_cfg,
                                       uart_cfg->BaseAddress);
    if (status != XST_SUCCESS)
        return XST_FAILURE;

    status = XUartPs_SelfTest(&device->uart);
    if (status != XST_SUCCESS)
        return XST_FAILURE;

    XUartPs_SetOperMode(&device->uart, XUARTPS_OPER_MODE_NORMAL);

    XUartPs_SetFifoThreshold(&device->uart, 1);

    return RT_EOK;
}

rt_inline void _uart_set_fmt(struct hw_uart_device *device,
                             struct serial_configure *cfg)
{
    XUartPsFormat uart_format;
    uart_format.BaudRate = cfg->baud_rate;
    switch (cfg->data_bits)
    {
    case 7:
        uart_format.DataBits = XUARTPS_FORMAT_7_BITS;
        break;
    case 6:
        uart_format.DataBits = XUARTPS_FORMAT_6_BITS;
        break;
    default: /* 8 */
        uart_format.DataBits = XUARTPS_FORMAT_8_BITS;
        break;
    }
    // cfg->bit_order ?
    switch (cfg->parity)
    {
    case PARITY_ODD:
        uart_format.Parity = XUARTPS_FORMAT_ODD_PARITY;
        break;
    case PARITY_EVEN:
        uart_format.Parity = XUARTPS_FORMAT_EVEN_PARITY;
        break;
    default: /** None */
        uart_format.Parity = XUARTPS_FORMAT_NO_PARITY;
        break;
    }
    switch (cfg->stop_bits)
    {
    case STOP_BITS_2:
        uart_format.StopBits = XUARTPS_FORMAT_2_STOP_BIT;
        break;
    default:
        uart_format.StopBits = XUARTPS_FORMAT_1_STOP_BIT;
        break;
    }

    XUartPs_SetDataFormat(&device->uart, &uart_format);
}

static rt_err_t uart_configure(struct rt_serial_device *serial,
                               struct serial_configure *cfg)
{
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    struct hw_uart_device *device
        = (struct hw_uart_device *)serial->parent.user_data;
    RT_ASSERT(device != RT_NULL);

    if (!device->inited)
    {
        int err = _uart_init(device);
        if (err != RT_EOK)
            return err;

        device->inited = RT_TRUE;
    }

    _uart_set_fmt(device, cfg);

    return RT_EOK;
}

static void rt_hw_uart_isr(int irqno, void *param)
{
    struct rt_serial_device *serial = (struct rt_serial_device *)param;
    struct hw_uart_device *device
        = (struct hw_uart_device *)serial->parent.user_data;

    u32 isr_status;

    isr_status
        = XUartPs_ReadReg(device->uart.Config.BaseAddress, XUARTPS_IMR_OFFSET);
    isr_status &= XUartPs_ReadReg(device->uart.Config.BaseAddress,
                                  XUARTPS_ISR_OFFSET);

    if (isr_status & (u32)XUARTPS_IXR_RXOVR)
    {
        XUartPs_WriteReg(device->uart.Config.BaseAddress, XUARTPS_ISR_OFFSET,
                         XUARTPS_IXR_RXOVR);
    }

    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
}

static rt_err_t
uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct hw_uart_device *pdev;

    RT_ASSERT(serial != RT_NULL);

    pdev = serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        break;

    case RT_DEVICE_CTRL_SET_INT:
        rt_hw_interrupt_install(pdev->irqno, rt_hw_uart_isr, (void *)serial,
                                serial->parent.parent.name);
        rt_hw_interrupt_umask(pdev->irqno);

        XUartPs_SetInterruptMask(&pdev->uart, XUARTPS_IXR_RXOVR);
        break;
    }

    return RT_EOK;
}

static int uart_putc(struct rt_serial_device *serial, char c)
{
    struct hw_uart_device *dev;

    RT_ASSERT(serial != RT_NULL);
    dev = (struct hw_uart_device *)serial->parent.user_data;
    RT_ASSERT(dev != RT_NULL);

    XUartPs_SendByte(dev->base_addr, c);

    return 1;
}

static int uart_getc(struct rt_serial_device *serial)
{
    struct hw_uart_device *dev;

    RT_ASSERT(serial != RT_NULL);
    dev = (struct hw_uart_device *)serial->parent.user_data;

    u32 RecievedByte;
    if (!XUartPs_IsReceiveData(dev->base_addr))
    {
        return -1;
    }

    RecievedByte = XUartPs_ReadReg(dev->base_addr, XUARTPS_FIFO_OFFSET);
    /* Return the byte received */
    return RecievedByte;
}

#ifdef RT_SERIAL_USING_DMA
static rt_ssize_t dma_transmit(struct rt_serial_device *serial,
                              rt_uint8_t *buf,
                              rt_size_t size,
                              int direction)
{
    RT_ASSERT(serial != RT_NULL);
    struct hw_uart_device *dev
        = (struct hw_uart_device *)serial->parent.user_data;
    RT_ASSERT(dev != RT_NULL);

    for (int i = 0; i < size; i++)
        XUartPs_SendByte(dev->base_addr, buf[i]);
    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DMADONE);

    return size;
}
#endif

static const struct rt_uart_ops _uart_ops = {
    uart_configure,
    uart_control,
    uart_putc,
    uart_getc,
#ifdef RT_SERIAL_USING_DMA
    dma_transmit,
#endif
};

#include "rtthread.h"

#ifdef BSP_USING_UART0
static struct rt_serial_device _serial0;
#endif

#ifdef BSP_USING_UART1
static struct rt_serial_device _serial1;
#endif

int rt_hw_uart_init(void)
{
    struct serial_configure config;

    config.baud_rate = BAUD_RATE_115200;
    config.bit_order = BIT_ORDER_LSB;
    config.data_bits = DATA_BITS_8;
    config.parity = PARITY_NONE;
    config.stop_bits = STOP_BITS_1;
    config.invert = NRZ_NORMAL;
    config.bufsz = RT_SERIAL_RB_BUFSZ;

#ifdef BSP_USING_UART0
    _serial0.ops = &_uart_ops;
    _serial0.config = config;

    /* register uart device */
    rt_hw_serial_register(&_serial0, "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX
                              | RT_DEVICE_FLAG_DMA_TX,
                          &_uart_device0);
#endif

#ifdef BSP_USING_UART1
    _serial1.ops = &_uart_ops;
    _serial1.config = config;

    rt_hw_serial_register(&_serial1, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX
                              | RT_DEVICE_FLAG_DMA_TX,
                          &_uart_device1);
#endif

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);
