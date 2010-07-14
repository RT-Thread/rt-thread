/*
 * File      : interrupt.h
 * Change Logs:
 * Date           Author       Notes
 * 2010-05-17     swkyer       first version
 */
#ifndef __IRQ_H__
#define __IRQ_H__


/* Interrupt Numbers */
#define AXXXX_UART_INT				 0
#define AXXXX_USB_INT				 1
#define AXXXX_RTC_INT				 2
#define AXXXX_DMA_INT				 3
#define AXXXX_EXTERNAL_INT		     4
#define AXXXX_SPI_INT				 5
#define AXXXX_I2C1_INT			     6
#define AXXXX_I2C2_INT			     7
#define AXXXX_ADC_INT				 8
#define AXXXX_DAC_INT				 9
#define AXXXX_FLASH_INT			     10

#define AXXXX_CP0_COUNT_INT          11
#define AXXXX_MAX_INTR               12


#endif /* end of __IRQ_H__ */
