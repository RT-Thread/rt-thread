/* generated common header file - do not edit */
#ifndef COMMON_DATA_H_
#define COMMON_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "r_gpio_w.h"
#include "bsp_pin_cfg.h"
FSP_HEADER
#define IOPORT_CFG_NAME g_bsp_pin_cfg
#define IOPORT_CFG_OPEN R_GPIO_W_Open
#define IOPORT_CFG_CTRL g_gpio_w_ctrl

/* GPIO_W Instance */
extern const ioport_instance_t g_gpio_w;

/* GPIO_W control structure. */
extern gpio_w_instance_ctrl_t g_gpio_w_ctrl;
void g_common_init(void);
FSP_FOOTER
#endif /* COMMON_DATA_H_ */
