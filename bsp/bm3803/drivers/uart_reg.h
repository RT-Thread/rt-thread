#ifndef SERIAL_REG_H
#define SERIAL_REG_H

struct uart_reg
{
	unsigned int uartdata;
	unsigned int uartstatus;
	unsigned int uartctrl;
	unsigned int uartscaler;
};

#endif /* end of include guard: SERIAL_REG_H */
