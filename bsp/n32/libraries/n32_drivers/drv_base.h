#ifndef __DRV_BASE__
#define __DRV_BASE__
#include "board.h"
/**
 * @brief 使能对应GPIO的时钟
 */
 void n32_gpio_rcc_enable(GPIO_Module *gpio_grp);

 /**
 * @brief  定时器的时钟使能配置
 */
 void n32_time_rcc_config(TIM_Module *htim);

 /**定时器2的引脚涉及了SWD-JTAG的调试引脚，在复用时需要先设置jSWD-JTAG的复用
            * 复用功能 		GPIO端口
               JTMS/SWDIO 		PA13-----------swd
               JTCK/SWCLK 		A14------------swd
               JTDI 			PA15
               JTDO 			PB3
               NJTRST 			PB4

            * GPIO_ConfigPinRemap(GPIO_RMP_SW_JTAG_SW_ENABLE,ENABLE);
*/
void gpio_remap_JTAGOFF_SWDON(GPIO_Module *gpio_grp, uint16_t pin);
#endif
