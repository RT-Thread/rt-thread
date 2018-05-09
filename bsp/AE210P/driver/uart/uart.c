#include <nds32_intrinsic.h>

#define DEFAULT_BAUDRATE	115200 /* 8n1 */

#define IN8(reg) 		(uint8_t)((*(volatile unsigned long *)(reg)) & 0x000000FF)
#define READ_CLR(reg) 	(*(volatile unsigned long *)(reg))

int drv_uart_set_baudrate(int baudrate)
{
	unsigned long baud_div;	/* baud rate divisor */
	unsigned long temp_word;

	baud_div = (MB_UCLK / (16 * baudrate));

	/* Save LCR temporary */
	temp_word = IN8(STUARTC_BASE + UARTC_LCR_OFFSET);

	/* Setup dlab bit for baud rate setting */
	OUT8(STUARTC_BASE + UARTC_LCR_OFFSET, (temp_word | UARTC_LCR_DLAB));

	/* Apply baud rate */
	OUT8(STUARTC_BASE + UARTC_DLM_OFFSET, (unsigned char)(baud_div >> 8));
	OUT8(STUARTC_BASE + UARTC_DLL_OFFSET, (unsigned char)baud_div);
	OUT8(STUARTC_BASE + UARTC_PSR_OFFSET, (unsigned char)1);

	/* Restore LCR */
	OUT8(STUARTC_BASE + UARTC_LCR_OFFSET, temp_word);
	
	return 0;
}

int drv_uart_is_kbd_hit(void)
{
	return IN8(STUARTC_BASE + UARTC_LSR_OFFSET) & UARTC_LSR_RDR;
}

int drv_uart_get_char(void)
{
	while (!(IN8(STUARTC_BASE + UARTC_LSR_OFFSET) & UARTC_LSR_RDR))
		;

	return IN8(STUARTC_BASE + UARTC_RBR_OFFSET);
}

void drv_uart_put_char(int ch)
{
	while (!(IN8(STUARTC_BASE + UARTC_LSR_OFFSET) & UARTC_LSR_THRE))
		;

	OUT8(STUARTC_BASE + UARTC_THR_OFFSET, ch);
}

int drv_uart_init(void)
{
	/* Clear everything */
	OUT8(STUARTC_BASE + UARTC_IER_OFFSET, 0x0);
	OUT8(STUARTC_BASE + UARTC_LCR_OFFSET, 0x0);

	/* Setup baud rate */
	drv_uart_set_baudrate(DEFAULT_BAUDRATE);

	/* Setup parity, data bits, and stop bits */
	OUT8(STUARTC_BASE + UARTC_LCR_OFFSET, \
			(UARTC_LCR_PARITY_NONE | UARTC_LCR_BITS8 | UARTC_LCR_STOP1));

	return 0;
}

/**********************************************
 *
 * Archer Chang
 *
 * driver API with reg base
 *
***********************************************/
int __drv_uart_set_baudrate(unsigned int regbase, int baudrate)
{
	unsigned long baud_div;	/* baud rate divisor */
	unsigned long temp_word;

	baud_div = (MB_UCLK / (16 * baudrate));

	/* Save LCR temporary */
	temp_word = IN8(regbase + UARTC_LCR_OFFSET);

	/* Setup dlab bit for baud rate setting */
	OUT8(regbase + UARTC_LCR_OFFSET, (temp_word | UARTC_LCR_DLAB));

	/* Apply baud rate */
	OUT8(regbase + UARTC_DLM_OFFSET, (unsigned char)(baud_div >> 8));
	OUT8(regbase + UARTC_DLL_OFFSET, (unsigned char)baud_div);
	OUT8(regbase + UARTC_PSR_OFFSET, (unsigned char)1);

	/* Restore LCR */
	OUT8(regbase + UARTC_LCR_OFFSET, temp_word);

	return 0;
}

int __drv_uart_is_kbd_hit(unsigned int regbase)
{
	return IN8(regbase + UARTC_LSR_OFFSET) & UARTC_LSR_RDR;
}

int __drv_uart_get_char(unsigned int regbase)
{
	while (!(IN8(regbase + UARTC_LSR_OFFSET) & UARTC_LSR_RDR))
		;

	return IN8(regbase + UARTC_RBR_OFFSET);
}

void __drv_uart_put_char(unsigned int regbase, int ch)
{
	while (!(IN8(regbase + UARTC_LSR_OFFSET) & UARTC_LSR_THRE))
		;

	OUT8(regbase + UARTC_THR_OFFSET, ch);
}

int __drv_uart_put_char_nowait(unsigned int regbase, int ch)
{
	OUT8(regbase + UARTC_THR_OFFSET, ch);

	return 1;
}

int __drv_uart_init(unsigned int regbase, int baudrate)
{
	/* Clear everything */
	OUT8(regbase + UARTC_IER_OFFSET, 0x0);
	OUT8(regbase + UARTC_LCR_OFFSET, 0x0);

	/* Setup baud rate */
	__drv_uart_set_baudrate(regbase, baudrate);

	/* Setup parity, data bits, and stop bits */
	OUT8(regbase + UARTC_LCR_OFFSET, \
			(UARTC_LCR_PARITY_NONE | UARTC_LCR_BITS8 | UARTC_LCR_STOP1));

	return 0;
}

