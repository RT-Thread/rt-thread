/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-19     ZYH          first version
 */

#include <rtthread.h>
#include <fpioa.h>
#include <drv_io_config.h>
#include <sysctl.h>

#define HS_GPIO(n) (FUNC_GPIOHS0 + n)

#define IOCONFIG(pin,func)  {pin, func, #func}

static struct io_config
{
    int io_num;
    fpioa_function_t func;
    const char * func_name;
} io_config[] = 
{
#ifdef BSP_USING_LCD
    IOCONFIG(BSP_LCD_CS_PIN, FUNC_SPI0_SS0),                 /* LCD CS PIN */
    IOCONFIG(BSP_LCD_WR_PIN, FUNC_SPI0_SCLK),                /* LCD WR PIN */
    IOCONFIG(BSP_LCD_DC_PIN, HS_GPIO(LCD_DC_PIN)),     /* LCD DC PIN */
#endif

#ifdef BSP_USING_CAMERA
    IOCONFIG(BSP_CAMERA_SCCB_SDA_PIN, FUNC_SCCB_SDA),
    IOCONFIG(BSP_CAMERA_SCCB_SCLK_PIN, FUNC_SCCB_SCLK),
    IOCONFIG(BSP_CAMERA_CMOS_RST_PIN, FUNC_CMOS_RST),
    IOCONFIG(BSP_CAMERA_CMOS_VSYNC_PIN, FUNC_CMOS_VSYNC),
    IOCONFIG(BSP_CAMERA_CMOS_PWDN_PIN, FUNC_CMOS_PWDN),
    IOCONFIG(BSP_CAMERA_CMOS_XCLK_PIN, FUNC_CMOS_XCLK),
    IOCONFIG(BSP_CAMERA_CMOS_PCLK_PIN, FUNC_CMOS_PCLK),
    IOCONFIG(BSP_CAMERA_CMOS_HREF_PIN, FUNC_CMOS_HREF),
#endif

#ifdef BSP_USING_SPI1
    IOCONFIG(BSP_SPI1_CLK_PIN, FUNC_SPI1_SCLK),
    IOCONFIG(BSP_SPI1_D0_PIN, FUNC_SPI1_D0),
    IOCONFIG(BSP_SPI1_D1_PIN, FUNC_SPI1_D1),
#ifdef BSP_USING_SPI1_AS_QSPI
    IOCONFIG(BSP_SPI1_D2_PIN, FUNC_SPI1_D2),
    IOCONFIG(BSP_SPI1_D3_PIN, FUNC_SPI1_D3),
#endif
#ifdef BSP_SPI1_USING_SS0
    IOCONFIG(BSP_SPI1_SS0_PIN, HS_GPIO(SPI1_CS0_PIN)),
#endif
#ifdef BSP_SPI1_USING_SS1
    IOCONFIG(BSP_SPI1_SS1_PIN, HS_GPIO(SPI1_CS1_PIN)),
#endif
#ifdef BSP_SPI1_USING_SS2
    IOCONFIG(BSP_SPI1_SS2_PIN, HS_GPIO(SPI1_CS2_PIN)),
#endif
#ifdef BSP_SPI1_USING_SS3
    IOCONFIG(BSP_SPI1_SS3_PIN, HS_GPIO(SPI1_CS3_PIN)),
#endif
#endif

#ifdef BSP_USING_UART1
    IOCONFIG(BSP_UART1_TXD_PIN, FUNC_UART1_TX),
    IOCONFIG(BSP_UART1_RXD_PIN, FUNC_UART1_RX),
#endif
#ifdef BSP_USING_UART2
    IOCONFIG(BSP_UART2_TXD_PIN, FUNC_UART2_TX),
    IOCONFIG(BSP_UART2_RXD_PIN, FUNC_UART2_RX),
#endif
#ifdef BSP_USING_UART3
    IOCONFIG(BSP_UART3_TXD_PIN, FUNC_UART3_TX),
    IOCONFIG(BSP_UART3_RXD_PIN, FUNC_UART3_RX),
#endif
};

static int print_io_config()
{
    int i;
    rt_kprintf("IO Configuration Table\n");
    rt_kprintf("┌───────┬────────────────────────┐\n");
    rt_kprintf("│Pin    │Function                │\n");
    rt_kprintf("├───────┼────────────────────────┤\n");
    for(i = 0; i < sizeof io_config / sizeof io_config[0]; i++)
    {
        rt_kprintf("│%-2d     │%-24.24s│\n", io_config[i].io_num, io_config[i].func_name);
    }
    rt_kprintf("└───────┴────────────────────────┘\n");
    return 0;
}
MSH_CMD_EXPORT_ALIAS(print_io_config, io, print io config);

int io_config_init(void)
{
    int count = sizeof(io_config) / sizeof(io_config[0]);
    int i;

    sysctl_set_power_mode(SYSCTL_POWER_BANK0, SYSCTL_POWER_V18);
    sysctl_set_power_mode(SYSCTL_POWER_BANK1, SYSCTL_POWER_V18);
    sysctl_set_power_mode(SYSCTL_POWER_BANK2, SYSCTL_POWER_V18);
#ifdef BSP_USING_UART2
    // for IO-27/28
    sysctl_set_power_mode(SYSCTL_POWER_BANK4, SYSCTL_POWER_V33);
#endif
#if  defined(BSP_USING_UART1) || defined(BSP_USING_UART3)
    // for IO-20~23
    sysctl_set_power_mode(SYSCTL_POWER_BANK3, SYSCTL_POWER_V33);
#endif

    for(i = 0; i < count; i++)
    {
        fpioa_set_function(io_config[i].io_num, io_config[i].func);
    }

#if defined(BSP_USING_CAMERA) || defined(BSP_USING_LCD)
    sysctl_set_spi0_dvp_data(1);
#endif

}
INIT_BOARD_EXPORT(io_config_init);

