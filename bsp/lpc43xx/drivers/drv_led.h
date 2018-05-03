#ifndef __DRV_LED_H
#define __DRV_LED_H

/* Clock Control Unit register bits */
#define CCU_CLK_CFG_RUN   (1 << 0)
#define CCU_CLK_CFG_AUTO  (1 << 1)
#define CCU_CLK_STAT_RUN  (1 << 0)

#define LED_DEVICE_CTRL     0x81        /*LED control command*/

int rt_led_hw_init(void);
#endif
