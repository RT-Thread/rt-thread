#ifndef _DRV_GPIO_H_
#define _DRV_GPIO_H_

#include <stdint.h>
#include <rtthread.h>

#define _TM4C_PIN(index, gpioport, gpio_index)                          \
        {                                                               \
				     index, GPIO_PORT##gpioport##_BASE, GPIO_PIN_##gpio_index   \
				}
				
#define _TM4C_PIN_RESERVE                                              \
        {                                                               \
				    -1, 0, 0                                                    \
				}
				

/* TM4C123 GPIO driver*/
struct pin_index
{
    int index;
    uint32_t gpioBaseAddress;
    uint32_t pin;
};

extern int rt_hw_pin_init(void);

#endif  /*_DRV_GPIO_H_*/

