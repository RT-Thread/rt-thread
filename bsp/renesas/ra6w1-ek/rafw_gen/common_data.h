/* generated common header file - do not edit */
#ifndef COMMON_DATA_H_
#define COMMON_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "r_gpio_w.h"
#include "bsp_pin_cfg.h"

#define R_IOPORT_Open R_GPIO_W_Open
#define R_IOPORT_Close R_GPIO_W_Close
#define R_IOPORT_PinsCfg R_GPIO_W_PinsCfg
#define R_IOPORT_PinCfg R_GPIO_W_PinCfg
#define R_IOPORT_PinRead R_GPIO_W_PinRead
#define R_IOPORT_PinWrite R_GPIO_W_PinWrite
#define R_IOPORT_PortDirectionSet R_GPIO_W_PortDirectionSet
#define R_IOPORT_PortEventInputRead R_GPIO_W_PortEventInputRead
#define R_IOPORT_PortEventOutputWrite R_GPIO_W_PortEventOutputWrite
#define R_IOPORT_PortRead R_GPIO_W_PortRead
#define R_IOPORT_PortWrite R_GPIO_W_PortWrite
#ifndef IOPORT_CFG_NMOS_ENABLE
#define IOPORT_CFG_NMOS_ENABLE BSP_IO_DIRECTION_OUTPUT
#endif
#ifndef IOPORT_CFG_NAME
#define IOPORT_CFG_NAME g_bsp_pin_cfg
#endif

FSP_HEADER
extern const ioport_instance_t g_ioport;
extern gpio_w_instance_ctrl_t g_ioport_ctrl;
void g_common_init(void);
FSP_FOOTER
#endif /* COMMON_DATA_H_ */
