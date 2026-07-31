/* generated common source file - do not edit */
#include "common_data.h"
gpio_w_instance_ctrl_t g_gpio_w_ctrl;
const ioport_instance_t g_gpio_w = { .p_api = &g_ioport_on_gpio_w, .p_ctrl =
		&g_gpio_w_ctrl, .p_cfg = &g_bsp_pin_cfg, };
void g_common_init(void) {
}
