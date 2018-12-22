#ifndef __DRV_PCF8574_H
#define __DRV_PCF8574_H

#include <board.h>
#include <finsh.h>
#include <rtdevice.h>
#include <rthw.h>

//PCF8574各个IO的功能
#define BEEP_IO         0		//蜂鸣器控制引脚  	P0
#define AP_INT_IO       1   	//AP3216C中断引脚	P1
#define DCMI_PWDN_IO    2    	//DCMI的电源控制引脚	P2
#define USB_PWR_IO      3    	//USB电源控制引脚	P3
#define EX_IO      		4    	//扩展IO,自定义使用 	P4
#define MPU_INT_IO      5   	//MPU9250中断引脚	P5
#define RS485_RE_IO     6    	//RS485_RE引脚		P6
#define ETH_RESET_IO    7    	//以太网复位引脚		P7

rt_err_t rt_pcf8574_init(void);

void rt_pcf8574_write_bit(rt_uint8_t bit, rt_uint8_t state);
rt_uint8_t rt_pcf8574_read_bit(rt_uint8_t bit);

#endif

