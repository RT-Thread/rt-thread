

#ifndef __CH57x_COMM_H__
#define __CH57x_COMM_H__

#ifdef __cplusplus
 extern "C" {
#endif


#define  NULL           0
#define  ALL            0xFFFF

#ifndef  SUCCESS
#define  SUCCESS        0
#define  FAILED         (!SUCCESS)
#endif

#ifndef  ENABLE
#define  DISABLE        0
#define  ENABLE         (!DISABLE)
#endif

#define Debug_UART0        0
#define Debug_UART1        1
#define Debug_UART2        2
#define Debug_UART3        3

#ifdef DEBUG
#include <stdio.h>
#endif

#ifndef  FREQ_SYS
#define  FREQ_SYS       32000000
#endif

#if ( CLK_OSC32K == 1 )
#define CAB_LSIFQ       32000
#else
#define CAB_LSIFQ       32768
#endif

#include <string.h>
#include "CH57x_clk.h"
#include "CH57x_uart.h"
#include "CH57x_gpio.h"
#include "CH57x_lcd.h"
#include "CH57x_flash.h"
#include "CH57x_pwr.h"
#include "CH57x_pwm.h"
#include "CH57x_adc.h"
#include "CH57x_sys.h"
#include "CH57x_timer.h"
#include "CH57x_spi.h"
#include "CH57x_usbdev.h"
#include "CH57x_usbhost.h"





#define DelayMs(x)      mDelaymS(x)
#define DelayUs(x)      mDelayuS(x)


#ifdef __cplusplus
}
#endif

#endif  // __CH57x_COMM_H__

