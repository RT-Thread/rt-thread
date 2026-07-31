/* generated pin source file - do not edit */
#include "bsp_api.h"
#include "r_gpio_w.h"

const ioport_pin_cfg_t g_bsp_pin_cfg_data[] = { { .pin = BSP_IO_PORT_00_PIN_00,
		.pin_cfg = (GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN
				| GPIO_W_CFG_PORT_DIRECTION_INPUT | GPIO_W_CFG_SLW_FAST
				| GPIO_W_PERIPHERAL_UART_RX) }, { .pin = BSP_IO_PORT_00_PIN_01,
		.pin_cfg = (GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN
				| GPIO_W_CFG_PORT_DIRECTION_OUTPUT | GPIO_W_CFG_SLW_SLOW
				| GPIO_W_PERIPHERAL_UART_TX) }, { .pin = BSP_IO_PORT_00_PIN_02,
		.pin_cfg = (GPIO_W_CFG_ANALOG_ENABLE | GPIO_W_CFG_DRV_8mA
				| GPIO_W_CFG_SLW_SLOW) }, { .pin = BSP_IO_PORT_00_PIN_03,
		.pin_cfg = (GPIO_W_CFG_ANALOG_ENABLE | GPIO_W_CFG_DRV_8mA
				| GPIO_W_CFG_SLW_SLOW) }, { .pin = BSP_IO_PORT_00_PIN_10,
		.pin_cfg = (GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PORT_DIRECTION_OUTPUT
				| GPIO_W_CFG_PORT_OUTPUT_LOW | GPIO_W_CFG_SLW_SLOW) }, { .pin =
		BSP_IO_PORT_01_PIN_00, .pin_cfg = (GPIO_W_CFG_DRV_8mA
		| GPIO_W_CFG_PORT_DIRECTION_OUTPUT | GPIO_W_CFG_PORT_OUTPUT_LOW
		| GPIO_W_CFG_SLW_SLOW) }, { .pin = BSP_IO_PORT_01_PIN_01, .pin_cfg =
		(GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PORT_DIRECTION_OUTPUT
				| GPIO_W_CFG_PORT_OUTPUT_LOW | GPIO_W_CFG_SLW_SLOW) }, { .pin =
		BSP_IO_PORT_01_PIN_02, .pin_cfg = (GPIO_W_CFG_DRV_8mA
		| GPIO_W_CFG_PORT_DIRECTION_OUTPUT | GPIO_W_CFG_PORT_OUTPUT_LOW
		| GPIO_W_CFG_SLW_SLOW) }, { .pin = BSP_IO_PORT_01_PIN_03, .pin_cfg =
		(GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PORT_DIRECTION_OUTPUT
				| GPIO_W_CFG_PORT_OUTPUT_LOW | GPIO_W_CFG_SLW_SLOW) }, { .pin =
		BSP_IO_PORT_01_PIN_16, .pin_cfg = (GPIO_W_CFG_PERIPHERAL_PIN
		| GPIO_W_CFG_PORT_DIRECTION_INPUT | GPIO_W_PERIPHERAL_SWCLK) }, { .pin =
		BSP_IO_PORT_01_PIN_17, .pin_cfg = (GPIO_W_CFG_PERIPHERAL_PIN
		| GPIO_W_CFG_PORT_DIRECTION_INPUT | GPIO_W_PERIPHERAL_SWDIO) }, };

#if !defined(BSP_MCU_GROUP_RA6W1) //TIN-TODO
gpio_w_extended_cfg_t g_bsp_pin_cfg_extd = { .power.p1_pwr =
		GPIO_W_CFG_SUPPLY_V30,
#if BSP_FEATURE_IO_HAS_WEAK_CONFIG_PER_PORT
    .weak_pad_power           =
    {
        .p0_pwr = GPIO_W_CFG_DRV_NORMAL,
        .p1_pwr = GPIO_W_CFG_DRV_NORMAL,
 #if BSP_FEATURE_IO_PORT2_GPIO_COUNT > 0
        .p2_pwr = GPIO_W_CFG_DRV_NORMAL,
 #endif
    },
#else
		.weak_pad_power.aggregate = GPIO_W_CFG_DRV_NORMAL,
#endif
		.fixed_pin_clk_out = BSP_IO_CLK_NONE_OUT,
#if BSP_CFG_CLKOUT_SOURCE
    .sel_pin_clk_out.clk_en  = 1,
    .sel_pin_clk_out.clk_sel = BSP_CFG_CLKOUT_SOURCE - 1,
#else
		.sel_pin_clk_out.clk_en = 0, .sel_pin_clk_out.clk_sel =
				(bsp_io_clk_func_t) 0,
#endif
		};
#endif

const ioport_cfg_t g_bsp_pin_cfg = { .number_of_pins =
		sizeof(g_bsp_pin_cfg_data) / sizeof(ioport_pin_cfg_t), .p_pin_cfg_data =
		&g_bsp_pin_cfg_data[0],
#if !defined(BSP_MCU_GROUP_RA6W1) //TIN-TODO
		.p_extend = &g_bsp_pin_cfg_extd,
#endif
		};

#if BSP_TZ_SECURE_BUILD

void R_BSP_PinCfgSecurityInit(void);

/* Initialize SAR registers for secure pins. */
void R_BSP_PinCfgSecurityInit(void)
{
 #if (2U == BSP_FEATURE_IOPORT_VERSION)
    uint32_t pmsar[BSP_FEATURE_BSP_NUM_PMSAR];
 #else
    uint16_t pmsar[BSP_FEATURE_BSP_NUM_PMSAR];
 #endif
    memset(pmsar, 0xFF, BSP_FEATURE_BSP_NUM_PMSAR * sizeof(R_PMISC->PMSAR[0]));


    for(uint32_t i = 0; i < g_bsp_pin_cfg.number_of_pins; i++)
    {
        uint32_t port_pin = g_bsp_pin_cfg.p_pin_cfg_data[i].pin;
        uint32_t port = port_pin >> 8U;
        uint32_t pin = port_pin & 0xFFU;
        pmsar[port] &= (uint16_t) ~(1U << pin);
    }

    for(uint32_t i = 0; i < BSP_FEATURE_BSP_NUM_PMSAR; i++)
    {
 #if (2U == BSP_FEATURE_IOPORT_VERSION)
        R_PMISC->PMSAR[i].PMSAR = (uint16_t) pmsar[i];
 #else
        R_PMISC->PMSAR[i].PMSAR = pmsar[i];
 #endif
    }

}
#endif
