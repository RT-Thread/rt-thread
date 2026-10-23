/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <dt-bindings/clock/sun252i-f101-ccu.h>
#include <sunxi_ccu.h>

#define SUN252I_F101_UART_BGR        0x090c
#define SUN252I_F101_TWI_BGR         0x091c
#define SUN252I_F101_DE_CLK          0x0600
#define SUN252I_F101_DE_BGR          0x060c
#define SUN252I_F101_G2D_CLK         0x0630
#define SUN252I_F101_G2D_BGR         0x063c
#define SUN252I_F101_CE_CLK          0x0680
#define SUN252I_F101_CE_BGR          0x068c
#define SUN252I_F101_VE_CLK          0x0690
#define SUN252I_F101_VE_BGR          0x069c
#define SUN252I_F101_DMA_BGR         0x070c
#define SUN252I_F101_HSTIMER_BGR     0x073c
#define SUN252I_F101_PWM_BGR         0x07ac
#define SUN252I_F101_MBUS_BGR        0x0804
#define SUN252I_F101_SPI0_CLK        0x0940
#define SUN252I_F101_SPI1_CLK        0x0944
#define SUN252I_F101_SPI_BGR         0x096c
#define SUN252I_F101_SMHC0_CLK       0x0830
#define SUN252I_F101_SMHC2_CLK       0x0838
#define SUN252I_F101_SMHC_BGR        0x084c
#define SUN252I_F101_USB_BGR         0x0a8c
#define SUN252I_F101_COMBOPHY0_CLK   0x0aa0
#define SUN252I_F101_COMBOPHY0_BGR   0x0aa4
#define SUN252I_F101_DPSS_TOP_BGR    0x0abc
#define SUN252I_F101_IRRX_CLK        0x09c0
#define SUN252I_F101_IRRX_BGR        0x09cc
#define SUN252I_F101_GPADC_BGR       0x09ec
#define SUN252I_F101_THS_BGR         0x09fc
#define SUN252I_F101_I2S0_CLK        0x0a10
#define SUN252I_F101_I2S0_BGR        0x0a20
#define SUN252I_F101_OWA_TX_CLK      0x0a24
#define SUN252I_F101_OWA_RX_CLK      0x0a28
#define SUN252I_F101_OWA_BGR         0x0a2c
#define SUN252I_F101_AUDIO_DAC_CLK   0x0a50
#define SUN252I_F101_AUDIO_ADC_CLK   0x0a54
#define SUN252I_F101_AUDIO_BGR       0x0a5c
#define SUN252I_F101_DSI_CLK         0x0b24
#define SUN252I_F101_DSI_BGR         0x0b4c
#define SUN252I_F101_TCONLCD_CLK     0x0b60
#define SUN252I_F101_TCONLCD_BGR     0x0b7c
#define SUN252I_F101_TPADC_CLK       0x0c50
#define SUN252I_F101_TPADC_BGR       0x0c5c

#define SUN252I_F101_CLK(_id, _name, _property, _reg, _mask, _rate) \
    { .id = (_id), .name = (_name), .rate_property = (_property),    \
      .gate_reg = (_reg), .gate_mask = (_mask), .rate_default = (_rate) }

#define SUN252I_F101_MOD_CLK(_id, _name, _property, _reg, _rate) \
    { .id = (_id), .name = (_name), .rate_property = (_property), \
      .gate_reg = (_reg), .gate_mask = RT_BIT(31), .rate_default = (_rate), \
      .parent_rates = sun252i_f101_mod_parents, \
      .parent_rates_nr = RT_ARRAY_SIZE(sun252i_f101_mod_parents), \
      .m_shift = 0, .m_width = 4, .p_shift = 8, .p_width = 2, \
      .mux_shift = 24, .mux_width = 3 }

/* G2D can only use PERI_2X; its clock register has an M divider only. */
#define SUN252I_F101_G2D_MOD_CLK(_id, _name, _property, _reg, _rate) \
    { .id = (_id), .name = (_name), .rate_property = (_property), \
      .gate_reg = (_reg), .gate_mask = RT_BIT(31), .rate_default = (_rate), \
      .parent_rates = sun252i_f101_g2d_parents, \
      .parent_rates_nr = RT_ARRAY_SIZE(sun252i_f101_g2d_parents), \
      .m_shift = 0, .m_width = 5, .p_shift = 8, .p_width = 0, \
      .mux_shift = 24, .mux_width = 3 }

/* The oscillator and peripheral PLL rates are established by boot firmware. */
static const rt_ubase_t sun252i_f101_mod_parents[] =
{
    24000000,
    600000000,
    1200000000,
    300000000,
    120000000,
};

static const rt_ubase_t sun252i_f101_g2d_parents[] =
{
    1200000000,
};

static const struct sunxi_clk_desc sun252i_f101_clks[] =
{
    SUN252I_F101_CLK(SUN252I_F101_CLK_APB0, "apb0", "allwinner,apb0-rate",
            0, 0, 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_APB1, "apb1", "allwinner,apb1-rate",
            0, 0, 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_APB_UART, "apb-uart",
            "allwinner,apb-uart-rate", 0, 0, 100000000),

    /*
     * The PLL parent rates below are set by firmware.  Keep these clocks
     * gate-only until the CCU can discover those rates instead of exposing
     * a set_rate operation based on guessed parent frequencies.
     */
    SUN252I_F101_CLK(SUN252I_F101_CLK_DE, "de", RT_NULL,
            SUN252I_F101_DE_CLK, RT_BIT(31), 300000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_DE, "de-bus",
            "allwinner,apb0-rate", SUN252I_F101_DE_BGR, RT_BIT(0), 100000000),

    SUN252I_F101_G2D_MOD_CLK(SUN252I_F101_CLK_G2D, "g2d", RT_NULL,
            SUN252I_F101_G2D_CLK, 300000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_G2D, "g2d-bus",
            "allwinner,apb0-rate", SUN252I_F101_G2D_BGR, RT_BIT(0), 100000000),
    SUN252I_F101_MOD_CLK(SUN252I_F101_CLK_CE, "ce", RT_NULL,
            SUN252I_F101_CE_CLK, 300000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_CE, "ce-bus",
            "allwinner,apb0-rate", SUN252I_F101_CE_BGR, RT_BIT(0), 100000000),

    SUN252I_F101_CLK(SUN252I_F101_CLK_VE, "ve", RT_NULL,
            SUN252I_F101_VE_CLK, RT_BIT(31), 300000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_VE, "ve-bus",
            "allwinner,apb0-rate", SUN252I_F101_VE_BGR, RT_BIT(0), 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_DMA, "dma-bus",
            "allwinner,apb0-rate", SUN252I_F101_DMA_BGR, RT_BIT(0), 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_HSTIMER, "hstimer-bus",
            "allwinner,apb0-rate", SUN252I_F101_HSTIMER_BGR, RT_BIT(0), 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_PWM, "pwm-bus",
            "allwinner,apb0-rate", SUN252I_F101_PWM_BGR, RT_BIT(0), 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_G2D_M, "g2d-m-bus",
            "allwinner,apb0-rate", SUN252I_F101_MBUS_BGR, RT_BIT(10), 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_VE_M, "ve-m-bus",
            "allwinner,apb0-rate", SUN252I_F101_MBUS_BGR, RT_BIT(1), 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_DMA_M, "dma-m-bus",
            "allwinner,apb0-rate", SUN252I_F101_MBUS_BGR, RT_BIT(0), 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_DPSS_TOP, "dpss-top-bus",
            "allwinner,apb0-rate", SUN252I_F101_DPSS_TOP_BGR, RT_BIT(0), 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_COMBOPHY0, "combophy0", RT_NULL,
            SUN252I_F101_COMBOPHY0_CLK, RT_BIT(31), 300000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_COMBOPHY0, "combophy0-bus",
            "allwinner,apb0-rate", SUN252I_F101_COMBOPHY0_BGR, RT_BIT(0), 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_DSI, "dsi", RT_NULL,
            SUN252I_F101_DSI_CLK, RT_BIT(31), 300000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_DSI, "dsi-bus",
            "allwinner,apb0-rate", SUN252I_F101_DSI_BGR, RT_BIT(0), 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_TCONLCD, "tcon-lcd", RT_NULL,
            SUN252I_F101_TCONLCD_CLK, RT_BIT(31), 300000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_TCONLCD, "tcon-lcd-bus",
            "allwinner,apb0-rate", SUN252I_F101_TCONLCD_BGR, RT_BIT(0), 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_TPADC, "tpadc", RT_NULL,
            SUN252I_F101_TPADC_CLK, RT_BIT(31), 24000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_TPADC, "tpadc-bus",
            "allwinner,apb0-rate", SUN252I_F101_TPADC_BGR, RT_BIT(0), 100000000),

    SUN252I_F101_MOD_CLK(SUN252I_F101_CLK_SMHC0, "smhc0", "allwinner,smhc-rate",
            SUN252I_F101_SMHC0_CLK, 100000000),
    SUN252I_F101_MOD_CLK(SUN252I_F101_CLK_SMHC2, "smhc2", "allwinner,smhc-rate",
            SUN252I_F101_SMHC2_CLK, 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_SMHC0, "smhc0-bus",
            "allwinner,apb0-rate", SUN252I_F101_SMHC_BGR, RT_BIT(0), 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_SMHC2, "smhc2-bus",
            "allwinner,apb0-rate", SUN252I_F101_SMHC_BGR, RT_BIT(2), 100000000),

    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_UART0, "uart0-bus",
            "allwinner,apb-uart-rate", SUN252I_F101_UART_BGR, RT_BIT(0), 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_UART1, "uart1-bus",
            "allwinner,apb-uart-rate", SUN252I_F101_UART_BGR, RT_BIT(1), 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_UART2, "uart2-bus",
            "allwinner,apb-uart-rate", SUN252I_F101_UART_BGR, RT_BIT(2), 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_UART3, "uart3-bus",
            "allwinner,apb-uart-rate", SUN252I_F101_UART_BGR, RT_BIT(3), 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_UART4, "uart4-bus",
            "allwinner,apb-uart-rate", SUN252I_F101_UART_BGR, RT_BIT(4), 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_UART5, "uart5-bus",
            "allwinner,apb-uart-rate", SUN252I_F101_UART_BGR, RT_BIT(5), 100000000),

    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_TWI0, "twi0-bus",
            "allwinner,apb1-rate", SUN252I_F101_TWI_BGR, RT_BIT(0), 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_TWI1, "twi1-bus",
            "allwinner,apb1-rate", SUN252I_F101_TWI_BGR, RT_BIT(1), 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_TWI2, "twi2-bus",
            "allwinner,apb1-rate", SUN252I_F101_TWI_BGR, RT_BIT(2), 100000000),

    SUN252I_F101_MOD_CLK(SUN252I_F101_CLK_SPI0, "spi0", "allwinner,spi-rate",
            SUN252I_F101_SPI0_CLK, 100000000),
    SUN252I_F101_MOD_CLK(SUN252I_F101_CLK_SPI1, "spi1", "allwinner,spi-rate",
            SUN252I_F101_SPI1_CLK, 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_SPI0, "spi0-bus",
            "allwinner,apb0-rate", SUN252I_F101_SPI_BGR, RT_BIT(0), 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_SPI1, "spi1-bus",
            "allwinner,apb0-rate", SUN252I_F101_SPI_BGR, RT_BIT(1), 100000000),

    SUN252I_F101_CLK(SUN252I_F101_CLK_IRRX, "irrx", RT_NULL,
            SUN252I_F101_IRRX_CLK, RT_BIT(31), 24000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_IRRX, "irrx-bus",
            "allwinner,apb0-rate", SUN252I_F101_IRRX_BGR, RT_BIT(0), 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_GPADC, "gpadc-bus",
            "allwinner,apb0-rate", SUN252I_F101_GPADC_BGR, RT_BIT(0), 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_THS, "ths-bus",
            "allwinner,apb0-rate", SUN252I_F101_THS_BGR, RT_BIT(0), 100000000),

    SUN252I_F101_CLK(SUN252I_F101_CLK_I2S0, "i2s0", RT_NULL,
            SUN252I_F101_I2S0_CLK, RT_BIT(31), 24576000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_I2S0, "i2s0-bus",
            "allwinner,apb0-rate", SUN252I_F101_I2S0_BGR, RT_BIT(0), 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_OWA_TX, "owa-tx", RT_NULL,
            SUN252I_F101_OWA_TX_CLK, RT_BIT(31), 24576000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_OWA_RX, "owa-rx", RT_NULL,
            SUN252I_F101_OWA_RX_CLK, RT_BIT(31), 24576000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_OWA, "owa-bus",
            "allwinner,apb0-rate", SUN252I_F101_OWA_BGR, RT_BIT(0), 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_AUDIO_CODEC_DAC, "audio-dac", RT_NULL,
            SUN252I_F101_AUDIO_DAC_CLK, RT_BIT(31), 24576000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_AUDIO_CODEC_ADC, "audio-adc", RT_NULL,
            SUN252I_F101_AUDIO_ADC_CLK, RT_BIT(31), 24576000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_AUDIO_CODEC, "audio-bus",
            "allwinner,apb0-rate", SUN252I_F101_AUDIO_BGR, RT_BIT(0), 100000000),

    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_USB, "usb-bus",
            "allwinner,apb0-rate", 0x0a70, RT_BIT(31), 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_USBOTG0, "usb-otg",
            "allwinner,apb0-rate", SUN252I_F101_USB_BGR, RT_BIT(8), 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_USBEHCI0, "usb-ehci",
            "allwinner,apb0-rate", SUN252I_F101_USB_BGR, RT_BIT(4), 100000000),
    SUN252I_F101_CLK(SUN252I_F101_CLK_BUS_USBOHCI0, "usb-ohci",
            "allwinner,apb0-rate", SUN252I_F101_USB_BGR, RT_BIT(0), 100000000),
};

const struct sunxi_ccu_data sun252i_f101_ccu_data =
{
    .clks = sun252i_f101_clks,
    .clks_nr = RT_ARRAY_SIZE(sun252i_f101_clks),
    .cells_nr = SUN252I_F101_CLK_NUMBER,
};
