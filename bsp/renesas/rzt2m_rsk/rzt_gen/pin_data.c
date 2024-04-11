/* generated pin source file - do not edit */
#include "bsp_api.h"
#include "r_ioport_api.h"
#include "r_ioport.h"

extern const ioport_extend_cfg_t  g_ioport_cfg_extend;


const ioport_pin_cfg_t g_bsp_pin_cfg_data[] = {
    {
        .pin = BSP_IO_PORT_00_PIN_0,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P000_PFC_00_ETH2_RXD3)
    },
    {
        .pin = BSP_IO_PORT_00_PIN_1,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P001_PFC_01_ETH2_RXDV)
    },
    {
        .pin = BSP_IO_PORT_00_PIN_2,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P002_PFC_00_ETH2_TXEN)
    },
    {
        .pin = BSP_IO_PORT_00_PIN_3,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P003_PFC_01_ETH2_REFCLK)
    },
    {
        .pin = BSP_IO_PORT_00_PIN_5,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P005_PFC_00_ETHSW_PHYLINK2)
    },
    {
        .pin = BSP_IO_PORT_00_PIN_6,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P006_PFC_00_ETH2_TXCLK)
    },
    {
        .pin = BSP_IO_PORT_01_PIN_2,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P012_PFC_01_ETH2_TXD3)
    },
    {
        .pin = BSP_IO_PORT_01_PIN_3,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P013_PFC_00_ETH2_TXD2)
    },
    {
        .pin = BSP_IO_PORT_01_PIN_4,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P014_PFC_01_ETH2_TXD1)
    },
    {
        .pin = BSP_IO_PORT_01_PIN_5,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P015_PFC_00_ETH2_TXD0)
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
        .pin = BSP_IO_PORT_03_PIN_7,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P037_PFC_02_TRACEDATA5)
    },
    {
        .pin = BSP_IO_PORT_04_PIN_2,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT)
    },
    {
        .pin = BSP_IO_PORT_05_PIN_2,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P052_PFC_09_CANRX0)
    },
    {
        .pin = BSP_IO_PORT_05_PIN_3,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P053_PFC_0A_CANTX0)
    },
    {
        .pin = BSP_IO_PORT_05_PIN_5,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P055_PFC_00_ETHSW_PHYLINK1)
    },
    {
        .pin = BSP_IO_PORT_05_PIN_7,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P057_PFC_00_ETH1_TXD2)
    },
    {
        .pin = BSP_IO_PORT_06_PIN_0,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P060_PFC_00_ETH1_TXD3)
    },
    {
        .pin = BSP_IO_PORT_06_PIN_1,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P061_PFC_00_ETH1_REFCLK)
    },
    {
        .pin = BSP_IO_PORT_06_PIN_2,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P062_PFC_00_ETH1_TXD1)
    },
    {
        .pin = BSP_IO_PORT_06_PIN_3,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P063_PFC_00_ETH1_TXD0)
    },
    {
        .pin = BSP_IO_PORT_06_PIN_4,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P064_PFC_00_ETH1_TXCLK)
    },
    {
        .pin = BSP_IO_PORT_06_PIN_5,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P065_PFC_00_ETH1_TXEN)
    },
    {
        .pin = BSP_IO_PORT_06_PIN_6,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P066_PFC_00_ETH1_RXD0)
    },
    {
        .pin = BSP_IO_PORT_06_PIN_7,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P067_PFC_00_ETH1_RXD1)
    },
    {
        .pin = BSP_IO_PORT_07_PIN_0,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P070_PFC_00_ETH1_RXD2)
    },
    {
        .pin = BSP_IO_PORT_07_PIN_1,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P071_PFC_00_ETH1_RXD3)
    },
    {
        .pin = BSP_IO_PORT_07_PIN_2,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P072_PFC_00_ETH1_RXDV)
    },
    {
        .pin = BSP_IO_PORT_07_PIN_3,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P073_PFC_00_ETH1_RXCLK)
    },
    {
        .pin = BSP_IO_PORT_07_PIN_4,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P074_PFC_02_USB_VBUSIN)
    },
    {
        .pin = BSP_IO_PORT_08_PIN_2,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW)
    },
    {
        .pin = BSP_IO_PORT_08_PIN_4,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P084_PFC_00_ETH0_RXD3)
    },
    {
        .pin = BSP_IO_PORT_08_PIN_5,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P085_PFC_00_ETH0_RXDV)
    },
    {
        .pin = BSP_IO_PORT_08_PIN_6,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P086_PFC_00_ETH0_RXCLK)
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
        .pin = BSP_IO_PORT_09_PIN_1,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P091_PFC_00_ETH0_REFCLK)
    },
    {
        .pin = BSP_IO_PORT_09_PIN_3,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P093_PFC_00_ETH0_TXD3)
    },
    {
        .pin = BSP_IO_PORT_09_PIN_4,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P094_PFC_00_ETH0_TXD2)
    },
    {
        .pin = BSP_IO_PORT_09_PIN_5,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P095_PFC_00_ETH0_TXD1)
    },
    {
        .pin = BSP_IO_PORT_09_PIN_6,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P096_PFC_00_ETH0_TXD0)
    },
    {
        .pin = BSP_IO_PORT_09_PIN_7,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P097_PFC_00_ETH0_TXCLK)
    },
    {
        .pin = BSP_IO_PORT_10_PIN_0,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P100_PFC_00_ETH0_TXEN)
    },
    {
        .pin = BSP_IO_PORT_10_PIN_1,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P101_PFC_00_ETH0_RXD0)
    },
    {
        .pin = BSP_IO_PORT_10_PIN_2,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P102_PFC_00_ETH0_RXD1)
    },
    {
        .pin = BSP_IO_PORT_10_PIN_3,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P103_PFC_00_ETH0_RXD2)
    },
    {
        .pin = BSP_IO_PORT_10_PIN_4,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P104_PFC_01_ETHSW_PHYLINK0)
    },
    {
        .pin = BSP_IO_PORT_10_PIN_5,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT)
    },
    {
        .pin = BSP_IO_PORT_10_PIN_6,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT)
    },
    {
        .pin = BSP_IO_PORT_11_PIN_0,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT)
    },
    {
        .pin = BSP_IO_PORT_11_PIN_3,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT)
    },
    {
        .pin = BSP_IO_PORT_11_PIN_4,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT)
    },
    {
        .pin = BSP_IO_PORT_11_PIN_6,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT)
    },
    {
        .pin = BSP_IO_PORT_11_PIN_7,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P117_PFC_00_XSPI1_DS)
    },
    {
        .pin = BSP_IO_PORT_12_PIN_0,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P120_PFC_00_XSPI1_IO7)
    },
    {
        .pin = BSP_IO_PORT_12_PIN_1,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P121_PFC_00_XSPI1_IO6)
    },
    {
        .pin = BSP_IO_PORT_12_PIN_2,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P122_PFC_00_XSPI1_IO5)
    },
    {
        .pin = BSP_IO_PORT_12_PIN_3,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P123_PFC_00_XSPI1_IO4)
    },
    {
        .pin = BSP_IO_PORT_12_PIN_4,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P124_PFC_00_XSPI1_RESET0)
    },
    {
        .pin = BSP_IO_PORT_12_PIN_5,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P125_PFC_00_XSPI1_IO3)
    },
    {
        .pin = BSP_IO_PORT_12_PIN_6,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P126_PFC_01_XSPI1_IO2)
    },
    {
        .pin = BSP_IO_PORT_12_PIN_7,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P127_PFC_01_XSPI1_IO1)
    },
    {
        .pin = BSP_IO_PORT_13_PIN_0,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P130_PFC_00_XSPI1_IO0)
    },
    {
        .pin = BSP_IO_PORT_13_PIN_1,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P131_PFC_00_XSPI1_CS0)
    },
    {
        .pin = BSP_IO_PORT_13_PIN_2,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT)
    },
    {
        .pin = BSP_IO_PORT_13_PIN_3,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P133_PFC_00_XSPI1_CKP)
    },
    {
        .pin = BSP_IO_PORT_13_PIN_4,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P134_PFC_00_XSPI1_CKN)
    },
    {
        .pin = BSP_IO_PORT_13_PIN_7,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT)
    },
    {
        .pin = BSP_IO_PORT_14_PIN_1,
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
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT)
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
        .pin = BSP_IO_PORT_17_PIN_2,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P172_PFC_00_IRQ9)
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
        .pin = BSP_IO_PORT_18_PIN_7,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT_INPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW)
    },
    {
        .pin = BSP_IO_PORT_19_PIN_0,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P190_PFC_00_USB_VBUSEN)
    },
    {
        .pin = BSP_IO_PORT_19_PIN_3,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW)
    },
    {
        .pin = BSP_IO_PORT_19_PIN_4,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW)
    },
    {
        .pin = BSP_IO_PORT_19_PIN_6,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW)
    },
    {
        .pin = BSP_IO_PORT_19_PIN_7,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW)
    },
    {
        .pin = BSP_IO_PORT_20_PIN_0,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW)
    },
    {
        .pin = BSP_IO_PORT_20_PIN_1,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW)
    },
    {
        .pin = BSP_IO_PORT_20_PIN_2,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW)
    },
    {
        .pin = BSP_IO_PORT_20_PIN_3,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW)
    },
    {
        .pin = BSP_IO_PORT_20_PIN_4,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW)
    },
    {
        .pin = BSP_IO_PORT_20_PIN_5,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P205_PFC_02_IIC_SCL0)
    },
    {
        .pin = BSP_IO_PORT_20_PIN_6,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P206_PFC_02_IIC_SDA0)
    },
    {
        .pin = BSP_IO_PORT_20_PIN_7,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW)
    },
    {
        .pin = BSP_IO_PORT_21_PIN_0,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW)
    },
    {
        .pin = BSP_IO_PORT_21_PIN_1,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P211_PFC_00_TRACEDATA0)
    },
    {
        .pin = BSP_IO_PORT_21_PIN_2,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P212_PFC_00_TRACEDATA1)
    },
    {
        .pin = BSP_IO_PORT_21_PIN_3,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P213_PFC_00_TRACEDATA2)
    },
    {
        .pin = BSP_IO_PORT_21_PIN_4,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P214_PFC_00_TRACEDATA3)
    },
    {
        .pin = BSP_IO_PORT_21_PIN_5,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P215_PFC_01_TRACEDATA4)
    },
    {
        .pin = BSP_IO_PORT_21_PIN_7,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P217_PFC_01_TRACEDATA6)
    },
    {
        .pin = BSP_IO_PORT_22_PIN_0,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P220_PFC_01_TRACEDATA7)
    },
    {
        .pin = BSP_IO_PORT_22_PIN_1,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P221_PFC_00_TRACECTL)
    },
    {
        .pin = BSP_IO_PORT_22_PIN_2,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P222_PFC_01_TRACECLK)
    },
    {
        .pin = BSP_IO_PORT_22_PIN_6,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P226_PFC_02_IIC_SCL1)
    },
    {
        .pin = BSP_IO_PORT_22_PIN_7,
        .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P227_PFC_02_IIC_SDA1)
    },
    {
        .pin = BSP_IO_PORT_23_PIN_4,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW)
    },
    {
        .pin = BSP_IO_PORT_23_PIN_6,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_HIGH)
    },
    {
        .pin = BSP_IO_PORT_23_PIN_7,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P237_PFC_00_ETH2_RXD0)
    },
    {
        .pin = BSP_IO_PORT_24_PIN_0,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P240_PFC_00_ETH2_RXD1)
    },
    {
        .pin = BSP_IO_PORT_24_PIN_1,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P241_PFC_00_ETH2_RXCLK)
    },
    {
        .pin = BSP_IO_PORT_24_PIN_2,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI | (uint32_t) IOPORT_PIN_P242_PFC_00_ETH2_RXD2)
    },
};

const ioport_cfg_t g_bsp_pin_cfg = {
    .number_of_pins = sizeof(g_bsp_pin_cfg_data)/sizeof(ioport_pin_cfg_t),
    .p_pin_cfg_data = &g_bsp_pin_cfg_data[0],
    .p_extend = &g_ioport_cfg_extend,
};
