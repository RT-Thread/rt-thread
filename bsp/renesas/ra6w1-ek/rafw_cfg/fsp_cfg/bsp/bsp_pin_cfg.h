/* generated configuration header file - do not edit */
#ifndef BSP_PIN_CFG_H_
#define BSP_PIN_CFG_H_
#include "r_gpio_w.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

extern const ioport_cfg_t g_bsp_pin_cfg; /* RRQ61xxx-EVB */
#if !defined(BSP_MCU_GROUP_RA6W1) //TIN-TODO
extern gpio_w_extended_cfg_t g_bsp_pin_cfg_extd; /* RRQ61xxx-EVB_extd */
#endif

void BSP_PinConfigSecurityInit();

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER
#endif /* BSP_PIN_CFG_H_ */
