/*
 * Copyright (c) 2023-2025 HPMicro
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
        HPM_PIOC->PAD[IOC_PAD_PY07].FUNC_CTL = PIOC_PY07_FUNC_CTL_SOC_GPIO_Y_07;
        HPM_PIOC->PAD[IOC_PAD_PY06].FUNC_CTL = PIOC_PY06_FUNC_CTL_SOC_GPIO_Y_06;
    } else if (ptr == HPM_UART1) {
        HPM_IOC->PAD[IOC_PAD_PC24].FUNC_CTL = IOC_PC24_FUNC_CTL_UART1_TXD;
        HPM_IOC->PAD[IOC_PAD_PC25].FUNC_CTL = IOC_PC25_FUNC_CTL_UART1_RXD;
    } else if (ptr == HPM_UART2) {
        HPM_IOC->PAD[IOC_PAD_PC26].FUNC_CTL = IOC_PC26_FUNC_CTL_UART2_TXD;
        HPM_IOC->PAD[IOC_PAD_PC27].FUNC_CTL = IOC_PC27_FUNC_CTL_UART2_RXD;
    } else if (ptr == HPM_PUART) {
        HPM_PIOC->PAD[IOC_PAD_PY07].FUNC_CTL = PIOC_PY07_FUNC_CTL_UART_RXD;
        HPM_PIOC->PAD[IOC_PAD_PY06].FUNC_CTL = PIOC_PY06_FUNC_CTL_UART_TXD;
    }
}

/* for uart_lin case, need to configure pin as gpio to sent break signal */
void init_uart_pin_as_gpio(UART_Type *ptr)
{
    /* pull-up */
    uint32_t pad_ctl = IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);

    if (ptr == HPM_UART2) {
        HPM_IOC->PAD[IOC_PAD_PC26].PAD_CTL = pad_ctl;
        HPM_IOC->PAD[IOC_PAD_PC27].PAD_CTL = pad_ctl;
        HPM_IOC->PAD[IOC_PAD_PC26].FUNC_CTL = IOC_PC26_FUNC_CTL_GPIO_C_26;
        HPM_IOC->PAD[IOC_PAD_PC27].FUNC_CTL = IOC_PC27_FUNC_CTL_GPIO_C_27;
    }
}

void init_i2c_pins_as_gpio(I2C_Type *ptr)
{
    if (ptr == HPM_I2C0) {
        /* I2C0 */
        HPM_IOC->PAD[IOC_PAD_PB22].FUNC_CTL = IOC_PB22_FUNC_CTL_GPIO_B_22;
        HPM_IOC->PAD[IOC_PAD_PB23].FUNC_CTL = IOC_PB23_FUNC_CTL_GPIO_B_23;
    } else if (ptr == HPM_I2C3) {
        /* I2C3 */
        HPM_IOC->PAD[IOC_PAD_PB20].FUNC_CTL = IOC_PB20_FUNC_CTL_GPIO_B_20;
        HPM_IOC->PAD[IOC_PAD_PB21].FUNC_CTL = IOC_PB21_FUNC_CTL_GPIO_B_21;
    } else {
        while (1) {
        }
    }
}

void init_i2c_pins(I2C_Type *ptr)
{
    if (ptr == HPM_I2C0) {
        HPM_IOC->PAD[IOC_PAD_PB22].FUNC_CTL = IOC_PB22_FUNC_CTL_I2C0_SCL
                                            | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;
        HPM_IOC->PAD[IOC_PAD_PB23].FUNC_CTL = IOC_PB23_FUNC_CTL_I2C0_SDA
                                            | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;
        HPM_IOC->PAD[IOC_PAD_PB22].PAD_CTL = IOC_PAD_PAD_CTL_OD_SET(1) | IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);
        HPM_IOC->PAD[IOC_PAD_PB23].PAD_CTL = IOC_PAD_PAD_CTL_OD_SET(1) | IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);
    } else if (ptr == HPM_I2C3) {
        HPM_IOC->PAD[IOC_PAD_PB20].FUNC_CTL = IOC_PB20_FUNC_CTL_I2C3_SCL
                                            | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;
        HPM_IOC->PAD[IOC_PAD_PB21].FUNC_CTL = IOC_PB21_FUNC_CTL_I2C3_SDA
                                            | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;
        HPM_IOC->PAD[IOC_PAD_PB20].PAD_CTL = IOC_PAD_PAD_CTL_OD_SET(1) | IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);
        HPM_IOC->PAD[IOC_PAD_PB21].PAD_CTL = IOC_PAD_PAD_CTL_OD_SET(1) | IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);
    } else {
        while (1) {
        }
    }
}

void init_sdm_pins(void)
{
    /* channel 3 */
    HPM_IOC->PAD[IOC_PAD_PA06].FUNC_CTL = IOC_PA06_FUNC_CTL_SDM0_CLK_3;
    HPM_IOC->PAD[IOC_PAD_PA07].FUNC_CTL = IOC_PA07_FUNC_CTL_SDM0_DAT_3;
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
    HPM_BIOC->PAD[IOC_PAD_PZ02].FUNC_CTL = BIOC_PZ02_FUNC_CTL_SOC_GPIO_Z_02;
#endif
}

void init_spi_pins(SPI_Type *ptr)
{
    if (ptr == HPM_SPI1) {
        HPM_IOC->PAD[IOC_PAD_PB02].FUNC_CTL = IOC_PB02_FUNC_CTL_SPI1_CSN;
        HPM_IOC->PAD[IOC_PAD_PB05].FUNC_CTL = IOC_PB05_FUNC_CTL_SPI1_MOSI;
        HPM_IOC->PAD[IOC_PAD_PB03].FUNC_CTL = IOC_PB03_FUNC_CTL_SPI1_MISO;
        HPM_IOC->PAD[IOC_PAD_PB04].FUNC_CTL = IOC_PB04_FUNC_CTL_SPI1_SCLK | IOC_PAD_FUNC_CTL_LOOP_BACK_SET(1);

        /* set max frequency slew rate(200M) */
        HPM_IOC->PAD[IOC_PAD_PB02].PAD_CTL = IOC_PAD_PAD_CTL_SR_MASK | IOC_PAD_PAD_CTL_SPD_SET(3) | IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1) | IOC_PAD_PAD_CTL_PRS_SET(1);
        HPM_IOC->PAD[IOC_PAD_PB05].PAD_CTL = IOC_PAD_PAD_CTL_SR_MASK | IOC_PAD_PAD_CTL_SPD_SET(3);
        HPM_IOC->PAD[IOC_PAD_PB03].PAD_CTL = IOC_PAD_PAD_CTL_SR_MASK | IOC_PAD_PAD_CTL_SPD_SET(3);
        HPM_IOC->PAD[IOC_PAD_PB04].PAD_CTL = IOC_PAD_PAD_CTL_SR_MASK | IOC_PAD_PAD_CTL_SPD_SET(3);
    }
}

void init_spi_pins_with_gpio_as_cs(SPI_Type *ptr)
{
    if (ptr == HPM_SPI1) {
        HPM_IOC->PAD[IOC_PAD_PB02].FUNC_CTL = IOC_PB02_FUNC_CTL_GPIO_B_02;
        HPM_IOC->PAD[IOC_PAD_PB05].FUNC_CTL = IOC_PB05_FUNC_CTL_SPI1_MOSI;
        HPM_IOC->PAD[IOC_PAD_PB03].FUNC_CTL = IOC_PB03_FUNC_CTL_SPI1_MISO;
        HPM_IOC->PAD[IOC_PAD_PB04].FUNC_CTL = IOC_PB04_FUNC_CTL_SPI1_SCLK | IOC_PAD_FUNC_CTL_LOOP_BACK_SET(1);

        /* set max frequency slew rate(200M) */
        HPM_IOC->PAD[IOC_PAD_PB02].PAD_CTL = IOC_PAD_PAD_CTL_SR_MASK | IOC_PAD_PAD_CTL_SPD_SET(3) | IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1) | IOC_PAD_PAD_CTL_PRS_SET(1);
        HPM_IOC->PAD[IOC_PAD_PB05].PAD_CTL = IOC_PAD_PAD_CTL_SR_MASK | IOC_PAD_PAD_CTL_SPD_SET(3);
        HPM_IOC->PAD[IOC_PAD_PB03].PAD_CTL = IOC_PAD_PAD_CTL_SR_MASK | IOC_PAD_PAD_CTL_SPD_SET(3);
        HPM_IOC->PAD[IOC_PAD_PB04].PAD_CTL = IOC_PAD_PAD_CTL_SR_MASK | IOC_PAD_PAD_CTL_SPD_SET(3);
    }
}

void init_pins(void)
{
#ifdef BOARD_CONSOLE_UART_BASE
    init_uart_pins(BOARD_CONSOLE_UART_BASE);
#endif
}

void init_gptmr_pins(GPTMR_Type *ptr)
{
    if (ptr == HPM_GPTMR1) {
        HPM_IOC->PAD[IOC_PAD_PA23].FUNC_CTL = IOC_PA23_FUNC_CTL_GPTMR1_CAPT_0;
        /* TMR1 compare 0 */
        HPM_IOC->PAD[IOC_PAD_PA25].FUNC_CTL = IOC_PA25_FUNC_CTL_GPTMR1_COMP_0;
        /* TMR1 compare 1 */
        HPM_IOC->PAD[IOC_PAD_PA26].FUNC_CTL = IOC_PA26_FUNC_CTL_GPTMR1_COMP_1;
        /* TMR1 compare 2 */
        HPM_IOC->PAD[IOC_PAD_PA20].FUNC_CTL = IOC_PA20_FUNC_CTL_TRGM1_P_00;
        trgm_output_t trgm1_io_config0 = {0};
        trgm1_io_config0.invert = 0;
        trgm1_io_config0.type = trgm_output_same_as_input;
        trgm1_io_config0.input = HPM_TRGM1_INPUT_SRC_GPTMR1_OUT2;
        trgm_output_config(HPM_TRGM1, HPM_TRGM1_OUTPUT_SRC_TRGM1_P0, &trgm1_io_config0);
        trgm_enable_io_output(HPM_TRGM1, 1 << 0);
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
    HPM_IOC->PAD[IOC_PAD_PB26].FUNC_CTL = IOC_PB26_FUNC_CTL_TRGM0_P_06;
    HPM_IOC->PAD[IOC_PAD_PB27].FUNC_CTL = IOC_PB27_FUNC_CTL_TRGM0_P_07;
}

void init_butn_pins(void)
{
    /* HPM_BIOC->PAD[IOC_PAD_PZ02].FUNC_CTL = IOC_PZ02_FUNC_CTL_PBUTN; */
    /* HPM_BIOC->PAD[IOC_PAD_PZ03].FUNC_CTL = IOC_PZ03_FUNC_CTL_WBUTN; */
}

void init_acmp_pins(void)
{
    /* configure to CMP1_INN5 function */
    HPM_IOC->PAD[IOC_PAD_PC16].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
    /* configure to ACMP_COMP_1 function */
    HPM_IOC->PAD[IOC_PAD_PC15].FUNC_CTL = IOC_PC15_FUNC_CTL_ACMP_COMP_1;
}

void init_pwm_pins(PWM_Type *ptr)
{
    if (ptr == HPM_PWM0) {
        HPM_IOC->PAD[IOC_PAD_PB17].FUNC_CTL = IOC_PB17_FUNC_CTL_PWM0_P_5;
        HPM_IOC->PAD[IOC_PAD_PB15].FUNC_CTL = IOC_PB15_FUNC_CTL_PWM0_P_3;
        HPM_IOC->PAD[IOC_PAD_PB13].FUNC_CTL = IOC_PB13_FUNC_CTL_PWM0_P_1;
        HPM_IOC->PAD[IOC_PAD_PB16].FUNC_CTL = IOC_PB16_FUNC_CTL_PWM0_P_4;
        HPM_IOC->PAD[IOC_PAD_PB14].FUNC_CTL = IOC_PB14_FUNC_CTL_PWM0_P_2;
        HPM_IOC->PAD[IOC_PAD_PB12].FUNC_CTL = IOC_PB12_FUNC_CTL_PWM0_P_0;
    }
}

void init_hrpwm_pins(PWM_Type *ptr)
{
    if (ptr == HPM_PWM1) {
        HPM_IOC->PAD[IOC_PAD_PB00].FUNC_CTL = IOC_PB00_FUNC_CTL_PWM1_P_0;
        HPM_IOC->PAD[IOC_PAD_PB02].FUNC_CTL = IOC_PB02_FUNC_CTL_PWM1_P_2;
    }
}

void init_adc_pins(void)
{
    /* ADC0.INA8 */
    HPM_IOC->PAD[IOC_PAD_PC12].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
}

void init_adc_bldc_pins(void)
{
   HPM_IOC->PAD[IOC_PAD_PC15].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
   HPM_IOC->PAD[IOC_PAD_PC16].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
   HPM_IOC->PAD[IOC_PAD_PC17].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
}

void init_usb_pins(USB_Type *ptr)
{
    if (ptr == HPM_USB0) {
        HPM_IOC->PAD[IOC_PAD_PC00].FUNC_CTL = IOC_PC00_FUNC_CTL_USB0_ID;
        HPM_IOC->PAD[IOC_PAD_PC01].FUNC_CTL = IOC_PC01_FUNC_CTL_USB0_PWR;
        HPM_IOC->PAD[IOC_PAD_PC02].FUNC_CTL = IOC_PC02_FUNC_CTL_USB0_OC;
    }
}

void  init_can_pins(MCAN_Type *ptr)
{
    if (ptr == HPM_MCAN0) {
        HPM_IOC->PAD[IOC_PAD_PB19].FUNC_CTL = IOC_PB19_FUNC_CTL_MCAN0_STBY | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;
        HPM_IOC->PAD[IOC_PAD_PB20].FUNC_CTL = IOC_PB20_FUNC_CTL_MCAN0_TXD | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;
        HPM_IOC->PAD[IOC_PAD_PB21].FUNC_CTL = IOC_PB21_FUNC_CTL_MCAN0_RXD | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;

        HPM_IOC->PAD[IOC_PAD_PB19].PAD_CTL = IOC_PAD_PAD_CTL_PS_SET(1) | IOC_PAD_PAD_CTL_PE_SET(1);
        HPM_IOC->PAD[IOC_PAD_PB20].PAD_CTL = IOC_PAD_PAD_CTL_PS_SET(1) | IOC_PAD_PAD_CTL_PE_SET(1);
        HPM_IOC->PAD[IOC_PAD_PB21].PAD_CTL = IOC_PAD_PAD_CTL_PS_SET(1) | IOC_PAD_PAD_CTL_PE_SET(1);
    }
}

void init_clk_obs_pins(void)
{
    /* HPM_IOC->PAD[IOC_PAD_PB02].FUNC_CTL = IOC_PB02_FUNC_CTL_SYSCTL_CLK_OBS_0; */
}

void init_led_pins_as_gpio(void)
{
    HPM_IOC->PAD[IOC_PAD_PB19].FUNC_CTL = IOC_PB19_FUNC_CTL_GPIO_B_19;
    HPM_IOC->PAD[IOC_PAD_PB01].FUNC_CTL = IOC_PB01_FUNC_CTL_GPIO_B_01;
    HPM_IOC->PAD[IOC_PAD_PA27].FUNC_CTL = IOC_PA27_FUNC_CTL_GPIO_A_27;
}

void init_dac_pins(DAC_Type *ptr)
{
    if (ptr == HPM_DAC0) {
        HPM_IOC->PAD[IOC_PAD_PC03].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;  /* DAC0.OUT */
    } else if (ptr == HPM_DAC1) {
        HPM_IOC->PAD[IOC_PAD_PC04].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;  /* DAC1.OUT */
    }
}

void init_trgmux_pins(uint32_t pin)
{
    /* all trgmux pin ALT_SELECT fixed to 16*/
    HPM_IOC->PAD[pin].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(17);
}

void init_pla_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PB25].FUNC_CTL = IOC_PB25_FUNC_CTL_TRGM0_P_05;
}

void init_pla_tamagawa_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PB30].FUNC_CTL = IOC_PB30_FUNC_CTL_GPIO_B_30;
    HPM_IOC->PAD[IOC_PAD_PB31].FUNC_CTL = IOC_PB31_FUNC_CTL_GPIO_B_31;
    HPM_IOC->PAD[IOC_PAD_PB21].FUNC_CTL = IOC_PB21_FUNC_CTL_TRGM0_P_01;
    HPM_IOC->PAD[IOC_PAD_PB22].FUNC_CTL = IOC_PB22_FUNC_CTL_TRGM0_P_02;
    HPM_IOC->PAD[IOC_PAD_PB23].FUNC_CTL = IOC_PB23_FUNC_CTL_TRGM0_P_03;
    HPM_IOC->PAD[IOC_PAD_PC22].FUNC_CTL = IOC_PC22_FUNC_CTL_SPI2_CSN;
    HPM_IOC->PAD[IOC_PAD_PC23].FUNC_CTL = IOC_PC23_FUNC_CTL_SPI2_MOSI;
    HPM_IOC->PAD[IOC_PAD_PC24].FUNC_CTL = IOC_PC24_FUNC_CTL_SPI2_MISO;
    HPM_IOC->PAD[IOC_PAD_PC25].FUNC_CTL = IOC_PC25_FUNC_CTL_SPI2_SCLK;
}

void init_lin_pins(LIN_Type *ptr)
{
    /** enable open drain and pull up */
    uint32_t pad_ctl = IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1) | IOC_PAD_PAD_CTL_OD_SET(1);
    if (ptr == HPM_LIN0) {
        HPM_IOC->PAD[IOC_PAD_PA10].FUNC_CTL = IOC_PA10_FUNC_CTL_LIN0_TXD;
        HPM_IOC->PAD[IOC_PAD_PA10].PAD_CTL = pad_ctl;
        HPM_IOC->PAD[IOC_PAD_PA11].FUNC_CTL = IOC_PA11_FUNC_CTL_LIN0_RXD;
        HPM_IOC->PAD[IOC_PAD_PA11].PAD_CTL = pad_ctl;
        HPM_IOC->PAD[IOC_PAD_PA15].FUNC_CTL = IOC_PA15_FUNC_CTL_LIN0_TREN;
        HPM_IOC->PAD[IOC_PAD_PA15].PAD_CTL = pad_ctl;
    } else if (ptr == HPM_LIN2) {
        HPM_IOC->PAD[IOC_PAD_PA07].FUNC_CTL = IOC_PA07_FUNC_CTL_LIN2_RXD;
        HPM_IOC->PAD[IOC_PAD_PA07].PAD_CTL = pad_ctl;
        HPM_IOC->PAD[IOC_PAD_PA06].FUNC_CTL = IOC_PA06_FUNC_CTL_LIN2_TXD;
        HPM_IOC->PAD[IOC_PAD_PA06].PAD_CTL = pad_ctl;
        /* missing TREN pin */
    }
}

void init_motor_over_zero_sensorless_adc_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PC06].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
    HPM_IOC->PAD[IOC_PAD_PC07].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
    HPM_IOC->PAD[IOC_PAD_PC08].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
}

void init_led_pins_as_pwm(void)
{
    /* Blue */
    HPM_IOC->PAD[IOC_PAD_PB19].FUNC_CTL = IOC_PB19_FUNC_CTL_PWM0_P_7;
    /* Green */
    HPM_IOC->PAD[IOC_PAD_PB01].FUNC_CTL = IOC_PB01_FUNC_CTL_PWM1_P_1;
    /* Red */
    HPM_IOC->PAD[IOC_PAD_PA27].FUNC_CTL = IOC_PA27_FUNC_CTL_PWM3_P_07;
}

void init_tamper_pins(void)
{
    HPM_BIOC->PAD[IOC_PAD_PZ04].FUNC_CTL = BIOC_PZ04_FUNC_CTL_BATT_TAMPER_04 | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;
    HPM_BIOC->PAD[IOC_PAD_PZ05].FUNC_CTL = BIOC_PZ05_FUNC_CTL_BATT_TAMPER_05;
    HPM_BIOC->PAD[IOC_PAD_PZ06].FUNC_CTL = BIOC_PZ06_FUNC_CTL_BATT_TAMPER_06;

    HPM_BIOC->PAD[IOC_PAD_PZ04].PAD_CTL &= ~IOC_PAD_PAD_CTL_OD_MASK;
    HPM_BIOC->PAD[IOC_PAD_PZ05].PAD_CTL &= ~IOC_PAD_PAD_CTL_OD_MASK;
}

/* for uart_rx_line_status case, need to a gpio pin to sent break signal */
void init_uart_break_signal_pin(void)
{
    HPM_IOC->PAD[IOC_PAD_PB02].PAD_CTL = IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);
    HPM_IOC->PAD[IOC_PAD_PB02].FUNC_CTL = IOC_PB02_FUNC_CTL_GPIO_B_02;
}

void init_gptmr_channel_pin(GPTMR_Type *ptr, uint32_t channel, bool as_comp)
{
    if (ptr == HPM_GPTMR1) {
        if (as_comp) {
            switch (channel) {
            case 0:
                HPM_IOC->PAD[IOC_PAD_PA25].FUNC_CTL = IOC_PA25_FUNC_CTL_GPTMR1_COMP_0;
                break;
            case 1:
                HPM_IOC->PAD[IOC_PAD_PA26].FUNC_CTL = IOC_PA26_FUNC_CTL_GPTMR1_COMP_1;
                break;
            case 2:
                HPM_IOC->PAD[IOC_PAD_PA20].FUNC_CTL = IOC_PA20_FUNC_CTL_TRGM1_P_00;
                trgm_output_t trgm1_io_config0 = {0};
                trgm1_io_config0.invert = 0;
                trgm1_io_config0.type = trgm_output_same_as_input;
                trgm1_io_config0.input = HPM_TRGM1_INPUT_SRC_GPTMR1_OUT2;
                trgm_output_config(HPM_TRGM1, HPM_TRGM1_OUTPUT_SRC_TRGM1_P0, &trgm1_io_config0);
                trgm_enable_io_output(HPM_TRGM1, 1 << 0);
                break;
            default:
                break;
            }
        } else {
            if (channel == 0) {
                HPM_IOC->PAD[IOC_PAD_PA23].FUNC_CTL = IOC_PA23_FUNC_CTL_GPTMR1_CAPT_0;
            }
        }
    }
}

void init_clk_ref_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PA14].FUNC_CTL = IOC_PA14_FUNC_CTL_SOC_REF0;
}
