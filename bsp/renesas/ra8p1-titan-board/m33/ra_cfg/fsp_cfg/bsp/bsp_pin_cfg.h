/* generated configuration header file - do not edit */
#ifndef BSP_PIN_CFG_H_
#define BSP_PIN_CFG_H_
#include "r_ioport.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

#define USER_SW_CFG_INT (BSP_IO_PORT_00_PIN_00)
#define ARDUINO_AN0 (BSP_IO_PORT_00_PIN_01) /* Enable when connected */
#define GROVE2_AN0 (BSP_IO_PORT_00_PIN_02) /* Reference E42 / E40 */
#define ARDUINO_AN2 (BSP_IO_PORT_00_PIN_03) /* Enable when connected */
#define ARDUINO_AN3 (BSP_IO_PORT_00_PIN_04) /* Enable when connected */
#define GROVE2_AN1 (BSP_IO_PORT_00_PIN_05) /* Reference E41 / E39 */
#define PMOD1_IRQ (BSP_IO_PORT_00_PIN_06)
#define ARDUINO_AN1 (BSP_IO_PORT_00_PIN_07) /* Enable when connected */
#define USER_SW2 (BSP_IO_PORT_00_PIN_08)
#define USER_SW1 (BSP_IO_PORT_00_PIN_09)
#define CAMERA_IRQ (BSP_IO_PORT_00_PIN_10) /* Enable when connected */
#define ARDUINO_D2_INT0 (BSP_IO_PORT_00_PIN_11) /* Enable when connected */
#define PMOD2_INT (BSP_IO_PORT_00_PIN_12)
#define I3C_SCL_PU (BSP_IO_PORT_00_PIN_13) /* Enable I3C_SEL_L to use */
#define ARDUINO_AN4 (BSP_IO_PORT_00_PIN_14) /* Enable when connected */
#define ARDUINO_AN5 (BSP_IO_PORT_00_PIN_15) /* Enable when connected */
#define OSPI_SIO0_ARDUINO_MISO (BSP_IO_PORT_01_PIN_00) /* See SW4 in manual */
#define OSPI_SIO3_ARDUINO_MOSI (BSP_IO_PORT_01_PIN_01) /* See SW4 in manual */
#define OSPI_SIO4_ARDUINO_D13_SCK (BSP_IO_PORT_01_PIN_02) /* See SW4 in manual */
#define OSPI_SIO2_ARDUINO_D10_SS (BSP_IO_PORT_01_PIN_03) /* See SW4 in manual */
#define OSPI_CS_ARDUINO_D5 (BSP_IO_PORT_01_PIN_04) /* See SW4 in manual */
#define OSPI_ECS_ARDUINO_D6 (BSP_IO_PORT_01_PIN_05) /* See SW4 in manual */
#define OSPI_RESET (BSP_IO_PORT_01_PIN_06) /* See SW4 in manual */
#define ETHERNET_MDINT (BSP_IO_PORT_01_PIN_07)
#define J2_30 (BSP_IO_PORT_01_PIN_08) /* Enable when connected */
#define I3C_SDA_PU (BSP_IO_PORT_01_PIN_09) /* Enable I3C_SEL_L to use */
#define ARDUINO_D9 (BSP_IO_PORT_01_PIN_10) /* Enable when connected */
#define MIPI_INT (BSP_IO_PORT_01_PIN_11) /* See SW4 in manual */
#define SDRAM_DQ3 (BSP_IO_PORT_01_PIN_12)
#define SDRAM_DQ4 (BSP_IO_PORT_01_PIN_13)
#define SDRAM_DQ5 (BSP_IO_PORT_01_PIN_14)
#define SDRAM_DQ6 (BSP_IO_PORT_01_PIN_15)
#define NMI (BSP_IO_PORT_02_PIN_00)
#define BOOT_MODE (BSP_IO_PORT_02_PIN_01) /* See Manual */
#define ETHERNET_RXCTL (BSP_IO_PORT_02_PIN_06) /* Reference E38 in manual */
#define PARLCD_D9G1 (BSP_IO_PORT_02_PIN_07)
#define JTAG_SWD_TDI (BSP_IO_PORT_02_PIN_08)
#define JTAG_SWD_TDO (BSP_IO_PORT_02_PIN_09)
#define JTAG_SWD_TMS (BSP_IO_PORT_02_PIN_10)
#define JTAG_SWD_TCK (BSP_IO_PORT_02_PIN_11)
#define EXTAL (BSP_IO_PORT_02_PIN_12) /* Main clock */
#define XTAL (BSP_IO_PORT_02_PIN_13) /* Main clock */
#define XCOUT (BSP_IO_PORT_02_PIN_14) /* Subclock */
#define XCIN (BSP_IO_PORT_02_PIN_15) /* Subclock */
#define SDRAM_DQ2 (BSP_IO_PORT_03_PIN_00)
#define SDRAM_DQ1 (BSP_IO_PORT_03_PIN_01)
#define SDRAM_DQ0 (BSP_IO_PORT_03_PIN_02)
#define USER_LED_GREEN (BSP_IO_PORT_03_PIN_03)
#define ETHERNET_TXD3_TDATA3 (BSP_IO_PORT_03_PIN_04) /* Reference SW4 /  E44 / E18 in manual */
#define ETHERNET_TXD2_TDATA2 (BSP_IO_PORT_03_PIN_05) /* Reference SW4 /  E45 / E19 in manual */
#define ETHERNET_TXD1_TDATA1 (BSP_IO_PORT_03_PIN_06) /* Reference SW4 /  E46 / E20 in manual */
#define ETHERNET_TXD0_TDATA0 (BSP_IO_PORT_03_PIN_07) /* Reference SW4 /  E47 / E21 in manual */
#define TCLK (BSP_IO_PORT_03_PIN_08) /* Reference SW4 /  E48 in manual */
#define ETHERNET_TCLK (BSP_IO_PORT_03_PIN_09) /* Reference SW4 /  E23 in manual */
#define ETHERNET_TCTL (BSP_IO_PORT_03_PIN_10) /* Reference SW4 /  E22 in manual */
#define ARDUINO_D7 (BSP_IO_PORT_03_PIN_12) /* Enable when connected */
#define I3C_SCL (BSP_IO_PORT_04_PIN_00)
#define I3C_SDA (BSP_IO_PORT_04_PIN_01)
#define PMOD1_RST (BSP_IO_PORT_04_PIN_02) /* Enable when connected */
#define AUDIO_BCLK (BSP_IO_PORT_04_PIN_03)
#define AUDIO_WCLK (BSP_IO_PORT_04_PIN_04)
#define AUDIO_SSITX (BSP_IO_PORT_04_PIN_05) /* See J41 in manual */
#define AUDIO_SSIRX_DCAM_D2 (BSP_IO_PORT_04_PIN_06) /* See J41 in manual */
#define USB_FS_VBUS (BSP_IO_PORT_04_PIN_07)
#define USB_HS_VBUS (BSP_IO_PORT_04_PIN_08)
#define PMOD2_GPIO1 (BSP_IO_PORT_04_PIN_09) /* Enable when connected */
#define PMOD2_RST (BSP_IO_PORT_04_PIN_10) /* Enable when connected */
#define MIPI_TE (BSP_IO_PORT_04_PIN_11)
#define PMOD1_GPIO1 (BSP_IO_PORT_04_PIN_12) /* Enable when connected */
#define PMOD1_GPIO2 (BSP_IO_PORT_04_PIN_13) /* Enable when connected */
#define ETHERNET_MDIO (BSP_IO_PORT_04_PIN_14)
#define ETHERNET_MDC (BSP_IO_PORT_04_PIN_15)
#define USB_FS_VBUSEN (BSP_IO_PORT_05_PIN_00)
#define CAM_XCLK (BSP_IO_PORT_05_PIN_01) /* Required for communication / operation */
#define MIC_DAT (BSP_IO_PORT_05_PIN_02)
#define SDRAM_A4_32BIT (BSP_IO_PORT_05_PIN_03)
#define SDRAM_A5_32BIT (BSP_IO_PORT_05_PIN_04)
#define SDRAM_A6_32BIT (BSP_IO_PORT_05_PIN_05)
#define SDRAM_A7_32BIT (BSP_IO_PORT_05_PIN_06)
#define SDRAM_A8_32BIT (BSP_IO_PORT_05_PIN_07)
#define SDRAM_A9_32BIT (BSP_IO_PORT_05_PIN_08)
#define SDRAM_A10_32BIT (BSP_IO_PORT_05_PIN_09)
#define SDRAM_A11_32BIT (BSP_IO_PORT_05_PIN_10)
#define SYS_I2C_SDA (BSP_IO_PORT_05_PIN_11)
#define SYS_I2C_SCL (BSP_IO_PORT_05_PIN_12)
#define DISP_TCON3 (BSP_IO_PORT_05_PIN_13)
#define DISP_BLEN (BSP_IO_PORT_05_PIN_14)
#define DISP_CLK (BSP_IO_PORT_05_PIN_15) /* Enable when connected */
#define USER_LED_BLUE (BSP_IO_PORT_06_PIN_00)
#define PMOD2_RTS_SSL (BSP_IO_PORT_06_PIN_01) /* See E16 / E14 in manual */
#define PMOD2_RX (BSP_IO_PORT_06_PIN_02)
#define PMOD2_TX (BSP_IO_PORT_06_PIN_03)
#define PMOD2_CTS (BSP_IO_PORT_06_PIN_04) /* See E14 / E15 in manual */
#define PMOD2_SSL (BSP_IO_PORT_06_PIN_05) /* See E10 in manual */
#define DISP_RESET (BSP_IO_PORT_06_PIN_06)
#define SDRAM_DQ31 (BSP_IO_PORT_06_PIN_07)
#define SDRAM_A12_32BIT (BSP_IO_PORT_06_PIN_08)
#define SDRAM_DQ7 (BSP_IO_PORT_06_PIN_09)
#define SDRAM_DQ12 (BSP_IO_PORT_06_PIN_10)
#define SDRAM_DQ13 (BSP_IO_PORT_06_PIN_11)
#define SDRAM_DQ14 (BSP_IO_PORT_06_PIN_12)
#define SDRAM_DQ15 (BSP_IO_PORT_06_PIN_13)
#define SDRAM_DQM0 (BSP_IO_PORT_06_PIN_14)
#define SDRAM_DQM2 (BSP_IO_PORT_06_PIN_15)
#define DCAM_D4 (BSP_IO_PORT_07_PIN_00) /* See SW4 in manual */
#define DCAM_D5 (BSP_IO_PORT_07_PIN_01) /* See SW4 in manual */
#define DCAM_D6 (BSP_IO_PORT_07_PIN_02) /* See SW4 in manual */
#define DCAM_D7 (BSP_IO_PORT_07_PIN_03) /* See SW4 in manual */
#define PMOD2_GPIO2 (BSP_IO_PORT_07_PIN_04) /* Enable when connected */
#define PARLCD_D18R2 (BSP_IO_PORT_07_PIN_07)
#define ETHERNET_RST (BSP_IO_PORT_07_PIN_08)
#define CAMERA_RESET (BSP_IO_PORT_07_PIN_09)
#define PARLCD_EXTCLK (BSP_IO_PORT_07_PIN_10)
#define PARLCD_D19R3 (BSP_IO_PORT_07_PIN_11)
#define PARLCD_D20R4 (BSP_IO_PORT_07_PIN_12)
#define PARLCD_D21R5 (BSP_IO_PORT_07_PIN_13)
#define PARLCD_D22R6 (BSP_IO_PORT_07_PIN_14)
#define PARLCD_D23R7 (BSP_IO_PORT_07_PIN_15)
#define OSPI_SIO5_PMOD1_CTS_IRQ (BSP_IO_PORT_08_PIN_00) /* See SW4 in manual */
#define OSPI_DQS_PMOD1_TXD_MOSI (BSP_IO_PORT_08_PIN_01) /* See SW4 in manual */
#define OSPI_SIO6_PMOD1_RXD_MISO (BSP_IO_PORT_08_PIN_02) /* See SW4 in manual */
#define OSPI_SIO1_PMOD1_SCK (BSP_IO_PORT_08_PIN_03) /* See SW4 in manual */
#define OSPI_SIO7_PMOD1_CTSRTS_SS (BSP_IO_PORT_08_PIN_04) /* See SW4 in manual */
#define PARLCD_HSYNC (BSP_IO_PORT_08_PIN_05) /* See SW4 in manual */
#define PARLCD_VSYNC (BSP_IO_PORT_08_PIN_06) /* See SW4 in manual */
#define PARLCD_DE (BSP_IO_PORT_08_PIN_07) /* See SW4 in manual */
#define OSPI_CLK_ARDUINO_MISO (BSP_IO_PORT_08_PIN_08) /* See SW4 in manual */
#define ARDUINO_D1TX_MIKROBUS_TX (BSP_IO_PORT_08_PIN_09) /* Enable when connected */
#define ARDUINO_D4_MIKROBUS_PWM (BSP_IO_PORT_08_PIN_10) /* Enable when connected */
#define ARDUINO_D3 (BSP_IO_PORT_08_PIN_11) /* Enable when connected */
#define MIC_CLK (BSP_IO_PORT_08_PIN_12)
#define SDRAM_CS (BSP_IO_PORT_08_PIN_13) /* See E50 in manual */
#define USB_FS_DP (BSP_IO_PORT_08_PIN_14)
#define USB_FS_DM (BSP_IO_PORT_08_PIN_15)
#define PARLCD_D3B3_PARCAM_D1 (BSP_IO_PORT_09_PIN_02) /* See SW4 in manual */
#define PARLCD_D2B2 (BSP_IO_PORT_09_PIN_03)
#define PARLCD_D8G0 (BSP_IO_PORT_09_PIN_04)
#define ETHERNET_RXC (BSP_IO_PORT_09_PIN_05) /* See E37 in manual */
#define ETHERNET_RXD0 (BSP_IO_PORT_09_PIN_06) /* See E36 in manual */
#define ETHERNET_RXD1 (BSP_IO_PORT_09_PIN_07) /* See E34 in manual */
#define ETHERNET_RXD2 (BSP_IO_PORT_09_PIN_08) /* See E33 in manual */
#define ETHERNET_RXD3 (BSP_IO_PORT_09_PIN_09) /* See E24 in manual */
#define PARLCD_D4B4 (BSP_IO_PORT_09_PIN_10) /* See SW4 in manual */
#define PARLCD_D5B5 (BSP_IO_PORT_09_PIN_11) /* See SW4 in manual */
#define PARLCD_D6B6 (BSP_IO_PORT_09_PIN_12) /* See SW4 in manual */
#define PARLCD_D7B7 (BSP_IO_PORT_09_PIN_13) /* See SW4 in manual */
#define PARLCD_D0B0 (BSP_IO_PORT_09_PIN_14) /* See SW4 in manual */
#define PARLCD_D1B1 (BSP_IO_PORT_09_PIN_15) /* See SW4 in manual */
#define SDRAM_A3_32BIT (BSP_IO_PORT_10_PIN_00)
#define SDRAM_A2_32BIT (BSP_IO_PORT_10_PIN_01)
#define SDRAM_A1_32BIT (BSP_IO_PORT_10_PIN_02)
#define SDRAM_A0_32BIT (BSP_IO_PORT_10_PIN_03)
#define SDRAM_DQM3 (BSP_IO_PORT_10_PIN_04)
#define SDRAM_DQM1 (BSP_IO_PORT_10_PIN_05)
#define SDRAM_CKE (BSP_IO_PORT_10_PIN_06)
#define USER_LED_RED (BSP_IO_PORT_10_PIN_07)
#define SDRAM_WE (BSP_IO_PORT_10_PIN_08)
#define SDRAM_CAS (BSP_IO_PORT_10_PIN_09)
#define SDRAM_RAS (BSP_IO_PORT_10_PIN_10)
#define SDRAM_DQ8 (BSP_IO_PORT_10_PIN_11)
#define SDRAM_DQ9 (BSP_IO_PORT_10_PIN_12)
#define SDRAM_DQ10 (BSP_IO_PORT_10_PIN_13)
#define SDRAM_DQ11 (BSP_IO_PORT_10_PIN_14)
#define SDRAM_CLK (BSP_IO_PORT_10_PIN_15)
#define PARLCD_D17R1 (BSP_IO_PORT_11_PIN_00)
#define PARLCD_D13G5 (BSP_IO_PORT_11_PIN_01)
#define PARLCD_D16R0_PARCAM_VSYNC (BSP_IO_PORT_11_PIN_02) /* See SW4 in manual */
#define PARLCD_D15G7_PARCAM_HSYNC (BSP_IO_PORT_11_PIN_03) /* See SW4 in manual */
#define PARLCD_D14G6_PARCAM_PCLK (BSP_IO_PORT_11_PIN_04) /* See SW4 in manual */
#define PARLCD_D12G4 (BSP_IO_PORT_11_PIN_05)
#define PARLCD_D11G3 (BSP_IO_PORT_11_PIN_06)
#define PARLCD_D10G2 (BSP_IO_PORT_11_PIN_07)
#define SDRAM_DQ30 (BSP_IO_PORT_12_PIN_00)
#define SDRAM_DQ29 (BSP_IO_PORT_12_PIN_01)
#define SDRAM_DQ28 (BSP_IO_PORT_12_PIN_02)
#define SDRAM_DQ27 (BSP_IO_PORT_12_PIN_03)
#define SDRAM_DQ26 (BSP_IO_PORT_12_PIN_04)
#define SDRAM_DQ25 (BSP_IO_PORT_12_PIN_05)
#define SDRAM_DQ24 (BSP_IO_PORT_12_PIN_06)
#define SDRAM_DQ23 (BSP_IO_PORT_12_PIN_07)
#define SDRAM_DQ22 (BSP_IO_PORT_12_PIN_08)
#define SDRAM_DQ21 (BSP_IO_PORT_12_PIN_09)
#define SDRAM_DQ20 (BSP_IO_PORT_12_PIN_10)
#define SDRAM_DQ19 (BSP_IO_PORT_12_PIN_11)
#define SDRAM_DQ18 (BSP_IO_PORT_12_PIN_12)
#define SDRAM_DQ17 (BSP_IO_PORT_12_PIN_13)
#define SDRAM_DQ16 (BSP_IO_PORT_12_PIN_14)
#define SDRAM_BA1 (BSP_IO_PORT_12_PIN_15)
#define SDRAM_BA0 (BSP_IO_PORT_13_PIN_00)
#define ARDUINO_D8_MIKROBUS_INT (BSP_IO_PORT_13_PIN_01) /* Enable when connected */
#define VCOMM_TXD_TO_EXT (BSP_IO_PORT_13_PIN_02)
#define VCOMM_RXD_FROM_EXT (BSP_IO_PORT_13_PIN_03)
#define VCOMM_RTS_FROM_EXT (BSP_IO_PORT_13_PIN_04) /* See E17 in manual */
#define VCOMM_CTS_TO_EXT (BSP_IO_PORT_13_PIN_05) /* See E9 in manual */
#define AUDIO_MCLK (BSP_IO_PORT_13_PIN_06) /* Enable when connected */
#define USB_HS_VBUSEN (BSP_IO_PORT_13_PIN_07)

extern const ioport_cfg_t g_bsp_pin_cfg; /* Titan_Board */

void BSP_PinConfigSecurityInit();

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER
#endif /* BSP_PIN_CFG_H_ */
