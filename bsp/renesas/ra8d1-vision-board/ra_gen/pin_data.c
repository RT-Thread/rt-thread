/* generated pin source file - do not edit */
#include "bsp_api.h"
#if __has_include("r_ioport.h")
#include "r_ioport.h"
#elif __has_include("r_ioport_b.h")
#include "r_ioport_b.h"
#endif

const ioport_pin_cfg_t g_bsp_pin_cfg_data[] = {
    {
        .pin = BSP_IO_PORT_00_PIN_02,
        .pin_cfg = ((uint32_t) IOPORT_CFG_ANALOG_ENABLE)
    },
    {
        .pin = BSP_IO_PORT_00_PIN_03,
        .pin_cfg = ((uint32_t) IOPORT_CFG_ANALOG_ENABLE)
    },
    {
        .pin = BSP_IO_PORT_00_PIN_04,
        .pin_cfg = ((uint32_t) IOPORT_CFG_ANALOG_ENABLE)
    },
    {
        .pin = BSP_IO_PORT_00_PIN_05,
        .pin_cfg = ((uint32_t) IOPORT_CFG_ANALOG_ENABLE)
    },
    {
        .pin = BSP_IO_PORT_00_PIN_07,
        .pin_cfg = ((uint32_t) IOPORT_CFG_ANALOG_ENABLE)
    },
    {
        .pin = BSP_IO_PORT_00_PIN_08,
        .pin_cfg = ((uint32_t) IOPORT_CFG_IRQ_ENABLE | (uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT)
    },
    {
        .pin = BSP_IO_PORT_00_PIN_09,
        .pin_cfg = ((uint32_t) IOPORT_CFG_IRQ_ENABLE | (uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT)
    },
    {
        .pin = BSP_IO_PORT_00_PIN_11,
        .pin_cfg = ((uint32_t) IOPORT_CFG_ANALOG_ENABLE)
    },
    {
        .pin = BSP_IO_PORT_00_PIN_14,
        .pin_cfg = ((uint32_t) IOPORT_CFG_ANALOG_ENABLE)
    },
    {
        .pin = BSP_IO_PORT_00_PIN_15,
        .pin_cfg = ((uint32_t) IOPORT_CFG_ANALOG_ENABLE)
    },
    {
        .pin = BSP_IO_PORT_01_PIN_00,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_OSPI)
    },
    {
        .pin = BSP_IO_PORT_01_PIN_01,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_OSPI)
    },
    {
        .pin = BSP_IO_PORT_01_PIN_03,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_OSPI)
    },
    {
        .pin = BSP_IO_PORT_01_PIN_07,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_OSPI)
    },
    {
        .pin = BSP_IO_PORT_01_PIN_12,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_01_PIN_13,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_01_PIN_14,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_01_PIN_15,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_02_PIN_06,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_MIPI)
    },
    {
        .pin = BSP_IO_PORT_02_PIN_07,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_LCD_GRAPHICS)
    },
    {
        .pin = BSP_IO_PORT_02_PIN_08,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_SCI1_3_5_7_9)
    },
    {
        .pin = BSP_IO_PORT_02_PIN_09,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_SCI1_3_5_7_9)
    },
    {
        .pin = BSP_IO_PORT_02_PIN_10,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_DEBUG)
    },
    {
        .pin = BSP_IO_PORT_02_PIN_11,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_DEBUG)
    },
    {
        .pin = BSP_IO_PORT_03_PIN_00,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_03_PIN_01,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_03_PIN_02,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_03_PIN_03,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_03_PIN_04,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_03_PIN_05,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_03_PIN_06,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_03_PIN_07,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_03_PIN_08,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_03_PIN_09,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_03_PIN_10,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_03_PIN_11,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_03_PIN_12,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_04_PIN_00,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_CEU)
    },
    {
        .pin = BSP_IO_PORT_04_PIN_01,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_CEU)
    },
    {
        .pin = BSP_IO_PORT_04_PIN_02,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_CLKOUT_COMP_RTC)
    },
    {
        .pin = BSP_IO_PORT_04_PIN_05,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_CEU)
    },
    {
        .pin = BSP_IO_PORT_04_PIN_06,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_CFG_PULLUP_ENABLE | (uint32_t) IOPORT_PERIPHERAL_CEU)
    },
    {
        .pin = BSP_IO_PORT_04_PIN_07,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_USB_FS)
    },
    {
        .pin = BSP_IO_PORT_04_PIN_08,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_SCI1_3_5_7_9)
    },
    {
        .pin = BSP_IO_PORT_04_PIN_09,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_SCI1_3_5_7_9)
    },
    {
        .pin = BSP_IO_PORT_05_PIN_00,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_SDHI_MMC)
    },
    {
        .pin = BSP_IO_PORT_05_PIN_01,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_SDHI_MMC)
    },
    {
        .pin = BSP_IO_PORT_05_PIN_02,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_SDHI_MMC)
    },
    {
        .pin = BSP_IO_PORT_05_PIN_03,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_SDHI_MMC)
    },
    {
        .pin = BSP_IO_PORT_05_PIN_04,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT)
    },
    {
        .pin = BSP_IO_PORT_05_PIN_05,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT)
    },
    {
        .pin = BSP_IO_PORT_05_PIN_06,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT)
    },
    {
        .pin = BSP_IO_PORT_05_PIN_15,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_LCD_GRAPHICS)
    },
    {
        .pin = BSP_IO_PORT_06_PIN_00,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW)
    },
    {
        .pin = BSP_IO_PORT_06_PIN_01,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_06_PIN_02,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_06_PIN_03,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_06_PIN_04,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_06_PIN_05,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_06_PIN_06,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_06_PIN_07,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_06_PIN_09,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_06_PIN_10,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_06_PIN_11,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_06_PIN_12,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_06_PIN_13,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_06_PIN_14,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_06_PIN_15,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_07_PIN_00,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_CEU)
    },
    {
        .pin = BSP_IO_PORT_07_PIN_01,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_CEU)
    },
    {
        .pin = BSP_IO_PORT_07_PIN_02,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_CEU)
    },
    {
        .pin = BSP_IO_PORT_07_PIN_03,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_CEU)
    },
    {
        .pin = BSP_IO_PORT_07_PIN_08,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_CFG_PULLUP_ENABLE | (uint32_t) IOPORT_PERIPHERAL_CEU)
    },
    {
        .pin = BSP_IO_PORT_07_PIN_09,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_CFG_PULLUP_ENABLE | (uint32_t) IOPORT_PERIPHERAL_CEU)
    },
    {
        .pin = BSP_IO_PORT_07_PIN_10,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_CFG_PULLUP_ENABLE | (uint32_t) IOPORT_PERIPHERAL_CEU)
    },
    {
        .pin = BSP_IO_PORT_07_PIN_11,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_LCD_GRAPHICS)
    },
    {
        .pin = BSP_IO_PORT_07_PIN_12,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_LCD_GRAPHICS)
    },
    {
        .pin = BSP_IO_PORT_07_PIN_13,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_LCD_GRAPHICS)
    },
    {
        .pin = BSP_IO_PORT_07_PIN_14,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_LCD_GRAPHICS)
    },
    {
        .pin = BSP_IO_PORT_07_PIN_15,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_LCD_GRAPHICS)
    },
    {
        .pin = BSP_IO_PORT_08_PIN_03,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_OSPI)
    },
    {
        .pin = BSP_IO_PORT_08_PIN_05,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_LCD_GRAPHICS)
    },
    {
        .pin = BSP_IO_PORT_08_PIN_06,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_LCD_GRAPHICS)
    },
    {
        .pin = BSP_IO_PORT_08_PIN_07,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_LCD_GRAPHICS)
    },
    {
        .pin = BSP_IO_PORT_08_PIN_08,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_OSPI)
    },
    {
        .pin = BSP_IO_PORT_08_PIN_09,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW)
    },
    {
        .pin = BSP_IO_PORT_08_PIN_10,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_SDHI_MMC)
    },
    {
        .pin = BSP_IO_PORT_08_PIN_11,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_SDHI_MMC)
    },
    {
        .pin = BSP_IO_PORT_08_PIN_12,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_SDHI_MMC)
    },
    {
        .pin = BSP_IO_PORT_08_PIN_14,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_USB_FS)
    },
    {
        .pin = BSP_IO_PORT_08_PIN_15,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_USB_FS)
    },
    {
        .pin = BSP_IO_PORT_09_PIN_02,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_LCD_GRAPHICS)
    },
    {
        .pin = BSP_IO_PORT_09_PIN_03,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_LCD_GRAPHICS)
    },
    {
        .pin = BSP_IO_PORT_09_PIN_04,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_LCD_GRAPHICS)
    },
    {
        .pin = BSP_IO_PORT_09_PIN_05,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_09_PIN_06,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_09_PIN_08,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_09_PIN_09,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_09_PIN_10,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_LCD_GRAPHICS)
    },
    {
        .pin = BSP_IO_PORT_09_PIN_11,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_LCD_GRAPHICS)
    },
    {
        .pin = BSP_IO_PORT_09_PIN_12,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_LCD_GRAPHICS)
    },
    {
        .pin = BSP_IO_PORT_09_PIN_13,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_LCD_GRAPHICS)
    },
    {
        .pin = BSP_IO_PORT_09_PIN_14,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_LCD_GRAPHICS)
    },
    {
        .pin = BSP_IO_PORT_09_PIN_15,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_LCD_GRAPHICS)
    },
    {
        .pin = BSP_IO_PORT_10_PIN_00,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_10_PIN_02,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_SCI0_2_4_6_8)
    },
    {
        .pin = BSP_IO_PORT_10_PIN_03,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_SCI0_2_4_6_8)
    },
    {
        .pin = BSP_IO_PORT_10_PIN_08,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_10_PIN_09,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HS_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_10_PIN_10,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_BUS)
    },
    {
        .pin = BSP_IO_PORT_10_PIN_11,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_GPT1)
    },
    {
        .pin = BSP_IO_PORT_10_PIN_13,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_HIGH)
    },
    {
        .pin = BSP_IO_PORT_11_PIN_01,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_USB_HS)
    },
    {
        .pin = BSP_IO_PORT_11_PIN_05,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_LCD_GRAPHICS)
    },
    {
        .pin = BSP_IO_PORT_11_PIN_06,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_LCD_GRAPHICS)
    },
    {
        .pin = BSP_IO_PORT_11_PIN_07,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_LCD_GRAPHICS)
    },
};

const ioport_cfg_t g_bsp_pin_cfg = {
    .number_of_pins = sizeof(g_bsp_pin_cfg_data)/sizeof(ioport_pin_cfg_t),
    .p_pin_cfg_data = &g_bsp_pin_cfg_data[0],
};

#if __has_include("r_ioport.h")
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
#endif
