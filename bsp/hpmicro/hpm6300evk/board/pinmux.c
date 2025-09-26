/*
 * Copyright (c) 2022-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

/*
 * Note:
 *   PY and PZ IOs: if any SOC pin function needs to be routed to these IOs,
 *  besides of IOC, PIOC/BIOC needs to be configured SOC_GPIO_X_xx, so that
 *  expected SoC function can be enabled on these IOs.
 *
 */
#include "board.h"

void init_uart_pins(UART_Type *ptr)
{
    if (ptr == HPM_UART0) {
        HPM_IOC->PAD[IOC_PAD_PY07].FUNC_CTL = IOC_PY07_FUNC_CTL_UART0_RXD;
        HPM_IOC->PAD[IOC_PAD_PY06].FUNC_CTL = IOC_PY06_FUNC_CTL_UART0_TXD;
        /* PY port IO needs to configure PIOC */
        HPM_PIOC->PAD[IOC_PAD_PY07].FUNC_CTL = PIOC_PY07_FUNC_CTL_SOC_PY_07;
        HPM_PIOC->PAD[IOC_PAD_PY06].FUNC_CTL = PIOC_PY06_FUNC_CTL_SOC_PY_06;
    } else if (ptr == HPM_UART1) {
        HPM_IOC->PAD[IOC_PAD_PC24].FUNC_CTL = IOC_PC24_FUNC_CTL_UART1_TXD;
        HPM_IOC->PAD[IOC_PAD_PC25].FUNC_CTL = IOC_PC25_FUNC_CTL_UART1_RXD;
    } else if (ptr == HPM_UART2) {
        HPM_IOC->PAD[IOC_PAD_PC26].FUNC_CTL = IOC_PC26_FUNC_CTL_UART2_TXD;
        HPM_IOC->PAD[IOC_PAD_PC27].FUNC_CTL = IOC_PC27_FUNC_CTL_UART2_RXD;
    } else if (ptr == HPM_PUART) {
        HPM_PIOC->PAD[IOC_PAD_PY07].FUNC_CTL = PIOC_PY07_FUNC_CTL_PUART_RXD;
        HPM_PIOC->PAD[IOC_PAD_PY06].FUNC_CTL = PIOC_PY06_FUNC_CTL_PUART_TXD;
    }
}

void init_uart_pin_as_gpio(UART_Type *ptr)
{
    if (ptr == HPM_UART2) {
        /* pull-up */
        HPM_IOC->PAD[IOC_PAD_PC26].PAD_CTL = IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);
        HPM_IOC->PAD[IOC_PAD_PC27].PAD_CTL = IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);

        HPM_IOC->PAD[IOC_PAD_PC26].FUNC_CTL = IOC_PC26_FUNC_CTL_GPIO_C_26;
        HPM_IOC->PAD[IOC_PAD_PC27].FUNC_CTL = IOC_PC27_FUNC_CTL_GPIO_C_27;
    }
}

void init_i2c_pins_as_gpio(I2C_Type *ptr)
{
    if (ptr == HPM_I2C0) {
        /* I2C0 */
        HPM_IOC->PAD[IOC_PAD_PC13].FUNC_CTL = IOC_PC13_FUNC_CTL_GPIO_C_13;
        HPM_IOC->PAD[IOC_PAD_PC14].FUNC_CTL = IOC_PC14_FUNC_CTL_GPIO_C_14;
    } else {
        while (1) {
        }
    }
}

void init_i2c_pins(I2C_Type *ptr)
{
    if (ptr == HPM_I2C0) {
        HPM_IOC->PAD[IOC_PAD_PC13].FUNC_CTL = IOC_PC13_FUNC_CTL_I2C0_SCL
                                            | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;
        HPM_IOC->PAD[IOC_PAD_PC14].FUNC_CTL = IOC_PC14_FUNC_CTL_I2C0_SDA
                                            | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;
        HPM_IOC->PAD[IOC_PAD_PC13].PAD_CTL = IOC_PAD_PAD_CTL_OD_SET(1) | IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);
        HPM_IOC->PAD[IOC_PAD_PC14].PAD_CTL = IOC_PAD_PAD_CTL_OD_SET(1) | IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);
    } else if (ptr == HPM_I2C3) {
        HPM_IOC->PAD[IOC_PAD_PC11].FUNC_CTL = IOC_PC11_FUNC_CTL_I2C3_SCL
                                            | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;
        HPM_IOC->PAD[IOC_PAD_PC12].FUNC_CTL = IOC_PC12_FUNC_CTL_I2C3_SDA
                                            | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;
        HPM_IOC->PAD[IOC_PAD_PC11].PAD_CTL = IOC_PAD_PAD_CTL_OD_SET(1) | IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);
        HPM_IOC->PAD[IOC_PAD_PC12].PAD_CTL = IOC_PAD_PAD_CTL_OD_SET(1) | IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);
    } else {
        while (1) {
        }
    }
}

void init_femc_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PA25].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PA26].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PA27].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PA28].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PA29].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PA30].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PA31].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PB00].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PB01].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* SRAM #UB */
    HPM_IOC->PAD[IOC_PAD_PB02].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PB03].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PB04].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PB05].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PB06].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PB07].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PB08].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);

    HPM_IOC->PAD[IOC_PAD_PB09].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PB10].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* SRAM #LB */
    HPM_IOC->PAD[IOC_PAD_PB11].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PB12].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PB13].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PB14].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PB15].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PB16].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* SRAM #ADV */
    HPM_IOC->PAD[IOC_PAD_PB17].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PB18].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PB19].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PB20].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PB21].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PB22].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PB23].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PB24].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* SRAM #OE */

    HPM_IOC->PAD[IOC_PAD_PB25].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* SRAM #WE */
    HPM_IOC->PAD[IOC_PAD_PB26].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PB27].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PB28].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PB29].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PB30].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);
    HPM_IOC->PAD[IOC_PAD_PB31].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);

    HPM_IOC->PAD[IOC_PAD_PX07].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12) | IOC_PAD_FUNC_CTL_LOOP_BACK_SET(1);    /* DQS */

    HPM_IOC->PAD[IOC_PAD_PA23].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* SRAM #CE */
}

void init_gpio_pins(void)
{
    /* configure pad setting: pull enable and pull up, schmitt trigger enable */
    /* enable schmitt trigger to eliminate jitter of pin used as button */
    uint32_t pad_ctl = IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1) | IOC_PAD_PAD_CTL_HYS_SET(1);

    /* Button */
#ifdef USING_GPIO0_FOR_GPIOZ
    HPM_IOC->PAD[IOC_PAD_PZ02].FUNC_CTL = IOC_PZ02_FUNC_CTL_GPIO_Z_02;
    HPM_IOC->PAD[IOC_PAD_PZ02].PAD_CTL = pad_ctl;
    /* PZ port IO needs to configure BIOC as well */
    HPM_BIOC->PAD[IOC_PAD_PZ02].FUNC_CTL = BIOC_PZ02_FUNC_CTL_SOC_PZ_02;
#endif
}

void init_spi_pins(SPI_Type *ptr)
{
    if (ptr == HPM_SPI3) {
        HPM_IOC->PAD[IOC_PAD_PC18].FUNC_CTL = IOC_PC18_FUNC_CTL_SPI3_CSN;
        HPM_IOC->PAD[IOC_PAD_PC21].FUNC_CTL = IOC_PC21_FUNC_CTL_SPI3_MOSI;
        HPM_IOC->PAD[IOC_PAD_PC19].FUNC_CTL = IOC_PC19_FUNC_CTL_SPI3_MISO;
        HPM_IOC->PAD[IOC_PAD_PC20].FUNC_CTL = IOC_PC20_FUNC_CTL_SPI3_SCLK | IOC_PAD_FUNC_CTL_LOOP_BACK_SET(1);

        /* set max frequency slew rate(200M) */
        HPM_IOC->PAD[IOC_PAD_PC18].PAD_CTL = IOC_PAD_PAD_CTL_SR_MASK | IOC_PAD_PAD_CTL_SPD_SET(3) | IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1) | IOC_PAD_PAD_CTL_PRS_SET(1);
        HPM_IOC->PAD[IOC_PAD_PC21].PAD_CTL = IOC_PAD_PAD_CTL_SR_MASK | IOC_PAD_PAD_CTL_SPD_SET(3);
        HPM_IOC->PAD[IOC_PAD_PC19].PAD_CTL = IOC_PAD_PAD_CTL_SR_MASK | IOC_PAD_PAD_CTL_SPD_SET(3);
        HPM_IOC->PAD[IOC_PAD_PC20].PAD_CTL = IOC_PAD_PAD_CTL_SR_MASK | IOC_PAD_PAD_CTL_SPD_SET(3);
    }
}

void init_spi_pins_with_gpio_as_cs(SPI_Type *ptr)
{
    if (ptr == HPM_SPI3) {
        HPM_IOC->PAD[IOC_PAD_PC18].FUNC_CTL = IOC_PC18_FUNC_CTL_GPIO_C_18;
        HPM_IOC->PAD[IOC_PAD_PC21].FUNC_CTL = IOC_PC21_FUNC_CTL_SPI3_MOSI;
        HPM_IOC->PAD[IOC_PAD_PC19].FUNC_CTL = IOC_PC19_FUNC_CTL_SPI3_MISO;
        HPM_IOC->PAD[IOC_PAD_PC20].FUNC_CTL = IOC_PC20_FUNC_CTL_SPI3_SCLK | IOC_PAD_FUNC_CTL_LOOP_BACK_SET(1);

        /* set max frequency slew rate(200M) */
        HPM_IOC->PAD[IOC_PAD_PC18].PAD_CTL = IOC_PAD_PAD_CTL_SR_MASK | IOC_PAD_PAD_CTL_SPD_SET(3) | IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1) | IOC_PAD_PAD_CTL_PRS_SET(1);
        HPM_IOC->PAD[IOC_PAD_PC21].PAD_CTL = IOC_PAD_PAD_CTL_SR_MASK | IOC_PAD_PAD_CTL_SPD_SET(3);
        HPM_IOC->PAD[IOC_PAD_PC19].PAD_CTL = IOC_PAD_PAD_CTL_SR_MASK | IOC_PAD_PAD_CTL_SPD_SET(3);
        HPM_IOC->PAD[IOC_PAD_PC20].PAD_CTL = IOC_PAD_PAD_CTL_SR_MASK | IOC_PAD_PAD_CTL_SPD_SET(3);
    }
}

void init_pins(void)
{
#ifdef BOARD_CONSOLE_UART_BASE
    init_uart_pins(BOARD_CONSOLE_UART_BASE);
#endif
    init_femc_pins();
}

void init_gptmr_pins(GPTMR_Type *ptr)
{
    if (ptr == HPM_GPTMR2) {
        HPM_IOC->PAD[IOC_PAD_PC06].FUNC_CTL = IOC_PC06_FUNC_CTL_GPTMR2_CAPT_0;
        /* TMR2 compare 0 */
        HPM_IOC->PAD[IOC_PAD_PC08].FUNC_CTL = IOC_PC08_FUNC_CTL_GPTMR2_COMP_0;
        /* TMR2 compare 1 */
        HPM_IOC->PAD[IOC_PAD_PC09].FUNC_CTL = IOC_PC09_FUNC_CTL_GPTMR2_COMP_1;
        /* TMR2 compare 2 */
        HPM_IOC->PAD[IOC_PAD_PA24].FUNC_CTL = IOC_PA24_FUNC_CTL_TRGM1_P_04;
        trgm_output_t trgm1_io_config0 = {0};
        trgm1_io_config0.invert = 0;
        trgm1_io_config0.type = trgm_output_same_as_input;
        trgm1_io_config0.input = HPM_TRGM1_INPUT_SRC_GPTMR2_OUT2;
        trgm_output_config(HPM_TRGM1, HPM_TRGM1_OUTPUT_SRC_TRGM1_P4, &trgm1_io_config0);
        trgm_enable_io_output(HPM_TRGM1, 1 << 4);
    }
}

void init_hall_trgm_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PB26].FUNC_CTL = IOC_PB26_FUNC_CTL_TRGM0_P_06;
    HPM_IOC->PAD[IOC_PAD_PB27].FUNC_CTL = IOC_PB27_FUNC_CTL_TRGM0_P_07;
    HPM_IOC->PAD[IOC_PAD_PB28].FUNC_CTL = IOC_PB28_FUNC_CTL_TRGM0_P_08;
}

void init_qei_trgm_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PB29].FUNC_CTL = IOC_PB29_FUNC_CTL_TRGM0_P_09;
    HPM_IOC->PAD[IOC_PAD_PB30].FUNC_CTL = IOC_PB30_FUNC_CTL_TRGM0_P_10;
}

void init_butn_pins(void)
{
    /* HPM_BIOC->PAD[IOC_PAD_PZ02].FUNC_CTL = BIOC_PZ02_FUNC_CTL_PBUTN; */
    /* HPM_BIOC->PAD[IOC_PAD_PZ03].FUNC_CTL = BIOC_PZ03_FUNC_CTL_WBUTN; */
}

void init_acmp_pins(void)
{
    /* configure to CMP1_INN5 function */
    HPM_IOC->PAD[IOC_PAD_PC16].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
    /* configure to ACMP_COMP_1 function */
    HPM_IOC->PAD[IOC_PAD_PC15].FUNC_CTL = IOC_PC15_FUNC_CTL_ACMP_COMP_1;
}

void init_enet_pins(ENET_Type *ptr)
{
    if (ptr == HPM_ENET0) {
        HPM_IOC->PAD[IOC_PAD_PA16].FUNC_CTL = IOC_PA16_FUNC_CTL_ETH0_MDC;
        HPM_IOC->PAD[IOC_PAD_PA15].FUNC_CTL = IOC_PA15_FUNC_CTL_ETH0_MDIO;

        HPM_IOC->PAD[IOC_PAD_PA18].FUNC_CTL = IOC_PA18_FUNC_CTL_ETH0_RXD_0;
        HPM_IOC->PAD[IOC_PAD_PA17].FUNC_CTL = IOC_PA17_FUNC_CTL_ETH0_RXD_1;
        HPM_IOC->PAD[IOC_PAD_PA19].FUNC_CTL = IOC_PA19_FUNC_CTL_ETH0_RXDV;

        HPM_IOC->PAD[IOC_PAD_PA20].FUNC_CTL = IOC_PA20_FUNC_CTL_ETH0_TXD_0;
        HPM_IOC->PAD[IOC_PAD_PA21].FUNC_CTL = IOC_PA21_FUNC_CTL_ETH0_TXD_1;
        HPM_IOC->PAD[IOC_PAD_PA23].FUNC_CTL = IOC_PA23_FUNC_CTL_ETH0_TXEN;

        HPM_IOC->PAD[IOC_PAD_PA22].FUNC_CTL = IOC_PAD_FUNC_CTL_LOOP_BACK_MASK | IOC_PA22_FUNC_CTL_ETH0_REFCLK;
    }
}

void init_pwm_pins(PWM_Type *ptr)
{
    if (ptr == HPM_PWM0) {
        HPM_IOC->PAD[IOC_PAD_PC05].FUNC_CTL = IOC_PC05_FUNC_CTL_PWM0_P_5;
        HPM_IOC->PAD[IOC_PAD_PC03].FUNC_CTL = IOC_PC03_FUNC_CTL_PWM0_P_3;
        HPM_IOC->PAD[IOC_PAD_PC01].FUNC_CTL = IOC_PC01_FUNC_CTL_PWM0_P_1;
        HPM_IOC->PAD[IOC_PAD_PC04].FUNC_CTL = IOC_PC04_FUNC_CTL_PWM0_P_4;
        HPM_IOC->PAD[IOC_PAD_PC02].FUNC_CTL = IOC_PC02_FUNC_CTL_PWM0_P_2;
        HPM_IOC->PAD[IOC_PAD_PC00].FUNC_CTL = IOC_PC00_FUNC_CTL_PWM0_P_0;
    }
}

void init_adc_pins(void)
{
    /* ADC0.INA6 */
    HPM_IOC->PAD[IOC_PAD_PC10].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
}

void init_adc_bldc_pins(void)
{
   HPM_IOC->PAD[IOC_PAD_PC16].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
   HPM_IOC->PAD[IOC_PAD_PC17].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
   HPM_IOC->PAD[IOC_PAD_PC22].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
}

void init_usb_pins(USB_Type *ptr)
{
    if (ptr == HPM_USB0) {
        ;
    }
}

void init_can_pins(CAN_Type *ptr)
{
    if (ptr == HPM_CAN1) {
        HPM_IOC->PAD[IOC_PAD_PZ04].FUNC_CTL = IOC_PZ04_FUNC_CTL_CAN1_TXD;
        HPM_IOC->PAD[IOC_PAD_PZ05].FUNC_CTL = IOC_PZ05_FUNC_CTL_CAN1_RXD;
        /* PZ port IO needs to configure BIOC as well */
        HPM_BIOC->PAD[IOC_PAD_PZ04].FUNC_CTL = BIOC_PZ04_FUNC_CTL_SOC_PZ_04;
        HPM_BIOC->PAD[IOC_PAD_PZ05].FUNC_CTL = BIOC_PZ05_FUNC_CTL_SOC_PZ_05;
    }
}

void init_sdxc_cmd_pin(SDXC_Type *ptr, bool open_drain, bool is_1v8)
{
    (void) is_1v8;
    if (ptr == HPM_SDXC0) {
        uint32_t cmd_func_ctl = IOC_PA10_FUNC_CTL_SDC0_CMD | IOC_PAD_FUNC_CTL_LOOP_BACK_SET(1);
        uint32_t cmd_pad_ctl = IOC_PAD_PAD_CTL_DS_SET(7) | IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);
        if (open_drain) {
            cmd_pad_ctl |= IOC_PAD_PAD_CTL_OD_MASK;
        }
        /* SDXC0.CMD */
        HPM_IOC->PAD[IOC_PAD_PA10].FUNC_CTL = cmd_func_ctl;
        HPM_IOC->PAD[IOC_PAD_PA10].PAD_CTL = cmd_pad_ctl;
    }
}

void init_sdxc_cd_pin(SDXC_Type  *ptr, bool as_gpio)
{
    if (ptr == HPM_SDXC0) {
        uint32_t cd_func_alt = as_gpio ?  IOC_PA14_FUNC_CTL_GPIO_A_14 : IOC_PA14_FUNC_CTL_SDC0_CDN;
        uint32_t cd_pad_ctl = IOC_PAD_PAD_CTL_DS_SET(7) | IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);
        /* SDXC0.CD */
        HPM_IOC->PAD[IOC_PAD_PA14].FUNC_CTL = cd_func_alt;
        HPM_IOC->PAD[IOC_PAD_PA14].PAD_CTL = cd_pad_ctl;
    }
}

void init_sdxc_clk_data_pins(SDXC_Type *ptr, uint32_t width, bool is_1v8)
{
    (void) is_1v8;
    if (ptr == HPM_SDXC0) {
        uint32_t func_ctl = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(17) | IOC_PAD_FUNC_CTL_LOOP_BACK_SET(1);
        uint32_t clk_pad_ctl =  IOC_PAD_PAD_CTL_DS_SET(7);
        uint32_t pad_ctl = IOC_PAD_PAD_CTL_DS_SET(7) | IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);

        /* SDXC0.CLK */
        HPM_IOC->PAD[IOC_PAD_PA11].FUNC_CTL = func_ctl;
        HPM_IOC->PAD[IOC_PAD_PA11].PAD_CTL = clk_pad_ctl;

        /* SDXC0.DATA0 */
        HPM_IOC->PAD[IOC_PAD_PA12].FUNC_CTL = func_ctl;
        HPM_IOC->PAD[IOC_PAD_PA12].PAD_CTL = pad_ctl;

        if (width == 4) {
            /* SDXC0.DATA1 */
            HPM_IOC->PAD[IOC_PAD_PA13].FUNC_CTL = func_ctl;
            HPM_IOC->PAD[IOC_PAD_PA13].PAD_CTL = pad_ctl;
            /* SDXC0.DATA2 */
            HPM_IOC->PAD[IOC_PAD_PA08].FUNC_CTL = func_ctl;
            HPM_IOC->PAD[IOC_PAD_PA08].PAD_CTL = pad_ctl;
            /* SDXC0.DATA3 */
            HPM_IOC->PAD[IOC_PAD_PA09].FUNC_CTL = func_ctl;
            HPM_IOC->PAD[IOC_PAD_PA09].PAD_CTL = pad_ctl;
        }
    }
}

void init_clk_obs_pins(void)
{
    /* HPM_IOC->PAD[IOC_PAD_PB02].FUNC_CTL = IOC_PB02_FUNC_CTL_SYSCTL_CLK_OBS_0; */
}

void init_led_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PA07].FUNC_CTL = IOC_PA07_FUNC_CTL_GPIO_A_07;
}

void init_dac_pins(DAC_Type *ptr)
{
    if (ptr == HPM_DAC) {
        HPM_IOC->PAD[IOC_PAD_PC03].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
    }
}

void init_trgmux_pins(uint32_t pin)
{
    /* all trgmux pin ALT_SELECT fixed to 16*/
    HPM_IOC->PAD[pin].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(16);
}

void init_enet_pps_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PC21].FUNC_CTL = IOC_PC21_FUNC_CTL_ETH0_EVTO_0;
    HPM_IOC->PAD[IOC_PAD_PC20].FUNC_CTL = IOC_PC20_FUNC_CTL_ETH0_EVTO_1;
}

void init_enet_pps_capture_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PC27].FUNC_CTL = IOC_PC27_FUNC_CTL_ETH0_EVTI_0;
    HPM_IOC->PAD[IOC_PAD_PC26].FUNC_CTL = IOC_PC26_FUNC_CTL_ETH0_EVTI_1;
}

void init_tamper_pins(void)
{
    HPM_BIOC->PAD[IOC_PAD_PZ06].FUNC_CTL = BIOC_PZ06_FUNC_CTL_TAMP_06 | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;
    HPM_BIOC->PAD[IOC_PAD_PZ07].FUNC_CTL = BIOC_PZ07_FUNC_CTL_TAMP_07;
}

/* for uart_rx_line_status case, need to a gpio pin to sent break signal */
void init_uart_break_signal_pin(void)
{
    HPM_IOC->PAD[IOC_PAD_PC18].PAD_CTL = IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);
    HPM_IOC->PAD[IOC_PAD_PC18].FUNC_CTL = IOC_PC18_FUNC_CTL_GPIO_C_18;
}

void init_gptmr_channel_pin(GPTMR_Type *ptr, uint32_t channel, bool as_comp)
{
    if (ptr == HPM_GPTMR2) {
        if (as_comp) {
            switch (channel) {
            case 0:
                HPM_IOC->PAD[IOC_PAD_PC08].FUNC_CTL = IOC_PC08_FUNC_CTL_GPTMR2_COMP_0;
                break;
            case 1:
                HPM_IOC->PAD[IOC_PAD_PC09].FUNC_CTL = IOC_PC09_FUNC_CTL_GPTMR2_COMP_1;
                break;
            case 2:
                HPM_IOC->PAD[IOC_PAD_PA24].FUNC_CTL = IOC_PA24_FUNC_CTL_TRGM1_P_04;
                trgm_output_t trgm1_io_config0 = {0};
                trgm1_io_config0.invert = 0;
                trgm1_io_config0.type = trgm_output_same_as_input;
                trgm1_io_config0.input = HPM_TRGM1_INPUT_SRC_GPTMR2_OUT2;
                trgm_output_config(HPM_TRGM1, HPM_TRGM1_OUTPUT_SRC_TRGM1_P4, &trgm1_io_config0);
                trgm_enable_io_output(HPM_TRGM1, 1 << 4);
                break;
            default:
                break;
            }
        } else {
            if (channel == 0) {
                HPM_IOC->PAD[IOC_PAD_PC06].FUNC_CTL = IOC_PC06_FUNC_CTL_GPTMR2_CAPT_0;
            }
        }
    }
}
