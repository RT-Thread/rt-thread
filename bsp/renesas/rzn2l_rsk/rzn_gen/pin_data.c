/* generated pin source file - do not edit */
#include "bsp_api.h"
#include "r_ioport_api.h"
#include "r_ioport.h"

extern const ioport_extend_cfg_t  g_ioport_cfg_extend;


const ioport_pin_cfg_t g_bsp_pin_cfg_data[] = {
    {
        .pin = BSP_IO_PORT_01_PIN_7,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P017_PFC_08_CANRX0)
    },
    {
        .pin = BSP_IO_PORT_02_PIN_2,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P022_PFC_08_CANTX0)
    },
    {
        .pin = BSP_IO_PORT_02_PIN_4,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P024_PFC_00_TDO)
    },
    {
        .pin = BSP_IO_PORT_02_PIN_5,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P025_PFC_01_TDI)
    },
    {
        .pin = BSP_IO_PORT_02_PIN_6,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P026_PFC_00_TMS_SWDIO)
    },
    {
        .pin = BSP_IO_PORT_02_PIN_7,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P027_PFC_00_TCK_SWCLK)
    },
    {
        .pin = BSP_IO_PORT_03_PIN_0,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW)
    },
    {
        .pin = BSP_IO_PORT_04_PIN_1,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW)
    },
    {
        .pin = BSP_IO_PORT_04_PIN_4,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW)
    },
    {
        .pin = BSP_IO_PORT_05_PIN_0,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW)
    },
    {
        .pin = BSP_IO_PORT_05_PIN_2,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P052_PFC_08_IIC_SCL1)
    },
    {
        .pin = BSP_IO_PORT_05_PIN_3,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P053_PFC_09_IIC_SDA1)
    },
    {
        .pin = BSP_IO_PORT_05_PIN_4,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT)
    },
    {
        .pin = BSP_IO_PORT_07_PIN_4,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P074_PFC_02_USB_VBUSIN)
    },
    {
        .pin = BSP_IO_PORT_08_PIN_7,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P087_PFC_00_GMAC_MDC)
    },
    {
        .pin = BSP_IO_PORT_09_PIN_0,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P090_PFC_00_GMAC_MDIO)
    },
    {
        .pin = BSP_IO_PORT_13_PIN_2,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P132_PFC_0B_IIC_SCL0)
    },
    {
        .pin = BSP_IO_PORT_13_PIN_3,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P133_PFC_0B_IIC_SDA0)
    },
    {
        .pin = BSP_IO_PORT_13_PIN_4,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW)
    },
    {
        .pin = BSP_IO_PORT_13_PIN_5,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT)
    },
    {
        .pin = BSP_IO_PORT_13_PIN_6,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT)
    },
    {
        .pin = BSP_IO_PORT_13_PIN_7,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT)
    },
    {
        .pin = BSP_IO_PORT_14_PIN_0,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT)
    },
    {
        .pin = BSP_IO_PORT_14_PIN_2,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P142_PFC_01_XSPI0_ECS0)
    },
    {
        .pin = BSP_IO_PORT_14_PIN_4,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P144_PFC_00_XSPI0_DS)
    },
    {
        .pin = BSP_IO_PORT_14_PIN_5,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P145_PFC_00_XSPI0_CKN)
    },
    {
        .pin = BSP_IO_PORT_14_PIN_6,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P146_PFC_00_XSPI0_CKP)
    },
    {
        .pin = BSP_IO_PORT_14_PIN_7,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P147_PFC_00_XSPI0_IO0)
    },
    {
        .pin = BSP_IO_PORT_15_PIN_0,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P150_PFC_00_XSPI0_IO1)
    },
    {
        .pin = BSP_IO_PORT_15_PIN_1,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P151_PFC_00_XSPI0_IO2)
    },
    {
        .pin = BSP_IO_PORT_15_PIN_2,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P152_PFC_00_XSPI0_IO3)
    },
    {
        .pin = BSP_IO_PORT_15_PIN_3,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P153_PFC_00_XSPI0_IO4)
    },
    {
        .pin = BSP_IO_PORT_15_PIN_4,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P154_PFC_00_XSPI0_IO5)
    },
    {
        .pin = BSP_IO_PORT_15_PIN_5,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P155_PFC_00_XSPI0_IO6)
    },
    {
        .pin = BSP_IO_PORT_15_PIN_6,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P156_PFC_00_XSPI0_IO7)
    },
    {
        .pin = BSP_IO_PORT_15_PIN_7,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P157_PFC_00_XSPI0_CS0)
    },
    {
        .pin = BSP_IO_PORT_16_PIN_0,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P160_PFC_00_XSPI0_CS1)
    },
    {
        .pin = BSP_IO_PORT_16_PIN_1,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P161_PFC_00_XSPI0_RESET0)
    },
    {
        .pin = BSP_IO_PORT_16_PIN_3,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT)
    },
    {
        .pin = BSP_IO_PORT_16_PIN_5,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P165_PFC_01_TXD0_SDA0_MOSI0)
    },
    {
        .pin = BSP_IO_PORT_16_PIN_6,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P166_PFC_02_RXD0_SCL0_MISO0)
    },
    {
        .pin = BSP_IO_PORT_17_PIN_3,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW)
    },
    {
        .pin = BSP_IO_PORT_17_PIN_5,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P175_PFC_05_USB_OVRCUR)
    },
    {
        .pin = BSP_IO_PORT_17_PIN_7,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P177_PFC_04_RXD3_SCL3_MISO3)
    },
    {
        .pin = BSP_IO_PORT_18_PIN_0,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P180_PFC_04_TXD3_SDA3_MOSI3)
    },
    {
        .pin = BSP_IO_PORT_18_PIN_2,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW)
    },
    {
        .pin = BSP_IO_PORT_18_PIN_4,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P184_PFC_03_SPI_RSPCK2)
    },
    {
        .pin = BSP_IO_PORT_18_PIN_5,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P185_PFC_03_SPI_MOSI2)
    },
    {
        .pin = BSP_IO_PORT_18_PIN_6,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P186_PFC_05_SPI_MISO2)
    },
    {
        .pin = BSP_IO_PORT_19_PIN_0,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P190_PFC_00_USB_VBUSEN)
    },
    {
        .pin = BSP_IO_PORT_21_PIN_1,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P211_PFC_06_SPI_SSL20)
    },
    {
        .pin = BSP_IO_PORT_22_PIN_1,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW)
    },
    {
        .pin = BSP_IO_PORT_22_PIN_3,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW)
    },
};

const ioport_cfg_t g_bsp_pin_cfg = {
    .number_of_pins = sizeof(g_bsp_pin_cfg_data)/sizeof(ioport_pin_cfg_t),
    .p_pin_cfg_data = &g_bsp_pin_cfg_data[0],
    .p_extend = &g_ioport_cfg_extend,
};
