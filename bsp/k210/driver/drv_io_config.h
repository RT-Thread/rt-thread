#ifndef __DRV_IO_CONFIG_H__
#define __DRV_IO_CONFIG_H__

enum HS_GPIO_CONFIG
{
#ifdef BSP_USING_LCD
    LCD_DC_PIN = 0,     /* LCD DC PIN */
#endif

#ifdef BSP_USING_SDCARD
    SD_CS_PIN,          /* SD_CS_PIN */
#endif
};

extern int io_config_init(void);

#endif
