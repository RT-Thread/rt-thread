#ifndef __DRV_UART_H__
#define __DRV_UART_H__

extern int drv_uart_init(void);
extern int drv_uart_set_baudrate(int baudrate);
extern int drv_uart_is_kbd_hit(void);
extern int drv_uart_get_char(void);
extern void drv_uart_put_char(int ch);

extern int  __drv_uart_init           (unsigned int regbase, int baudrate);
extern int  __drv_uart_set_baudrate   (unsigned int regbase, int baudrate);
extern int  __drv_uart_is_kbd_hit     (unsigned int regbase);
extern int  __drv_uart_get_char       (unsigned int regbase);
extern void __drv_uart_put_char       (unsigned int regbase, int ch);
extern void __drv_uart_put_char_nowait(unsigned int regbase, int ch);

#endif /* __DRV_UART_H__ */
