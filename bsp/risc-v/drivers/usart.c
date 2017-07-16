#include <rtdevice.h>
#include "usart.h"
/**
 * @brief set uartdbg buard 
 *
 * @param buard
 */
static usart_init(int buard)
{
	return;
}
static void usart_handler(int vector, void *param)
{
	rt_hw_serial_isr((struct rt_serial_device*)param, RT_SERIAL_EVENT_RX_IND);
	return;
}
static rt_err_t usart_configure(struct rt_serial_device *serial,
                                struct serial_configure *cfg)
{
		return RT_EOK;
}
static rt_err_t usart_control(struct rt_serial_device *serial,
                              int cmd, void *arg)
{
	RT_ASSERT(serial != RT_NULL);
	switch(cmd){
	case RT_DEVICE_CTRL_CLR_INT:
		break;
	case RT_DEVICE_CTRL_SET_INT:
		break;
	}
	return RT_EOK;
}
static int usart_putc(struct rt_serial_device *serial, char c)
{
	return 0;
}
static int usart_getc(struct rt_serial_device *serial)
{
	return 0;
}
static struct rt_uart_ops ops = {
	usart_configure,
	usart_control,
	usart_putc,
	usart_getc,
};
static struct rt_serial_device serial = {
	.ops = &ops,
	.config.baud_rate = BAUD_RATE_115200,
	.config.bit_order = BIT_ORDER_LSB,
	.config.data_bits = DATA_BITS_8,
	.config.parity    = PARITY_NONE,
	.config.stop_bits = STOP_BITS_1,
	.config.invert    = NRZ_NORMAL,
	.config.bufsz     = RT_SERIAL_RB_BUFSZ,
};
void rt_hw_uart_init(void)
{
	rt_hw_serial_register(&serial, "dusart", RT_DEVICE_FLAG_STREAM | RT_DEVICE_FLAG_RDWR
			| RT_DEVICE_FLAG_INT_RX, RT_NULL);
	return;
}
