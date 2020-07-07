#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "mss_gpio.h"
#include "mss_uart.h"

#include <rthw.h>
#include <rtthread.h>

void sw0_isr(void *args);
void sw1_isr(void *args);
void boardInit(void);
void sayHello(void);

#endif
