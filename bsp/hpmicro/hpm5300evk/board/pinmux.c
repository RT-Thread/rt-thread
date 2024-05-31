/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

/*
 * Note:
 *  PY and PZ IOs: if any SOC pin function needs to be routed to these IOs,
 *  besides of IOC, PIOC/BIOC needs to be configured SOC_GPIO_X_xx, so that
 *  expected SoC function can be enabled on these IOs.
 *
 */
#include "board.h"
#include "pinmux.h"

void init_xtal_pins(void)
{
    /* Package QFN32 should be set PA30 and PA31 pins as analog type to enable xtal. */
    /*
     * HPM_IOC->PAD[IOC_PAD_PA30].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
     * HPM_IOC->PAD[IOC_PAD_PA31].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
     */
}

void init_py_pins_as_pgpio(void)
{
    /* Set PY00-PY05 default function to PGPIO */
    HPM_PIOC->PAD[IOC_PAD_PY00].FUNC_CTL = PIOC_PY00_FUNC_CTL_PGPIO_Y_00;
    HPM_PIOC->PAD[IOC_PAD_PY01].FUNC_CTL = PIOC_PY01_FUNC_CTL_PGPIO_Y_01;
    HPM_PIOC->PAD[IOC_PAD_PY02].FUNC_CTL = PIOC_PY02_FUNC_CTL_PGPIO_Y_02;
    HPM_PIOC->PAD[IOC_PAD_PY03].FUNC_CTL = PIOC_PY03_FUNC_CTL_PGPIO_Y_03;
    HPM_PIOC->PAD[IOC_PAD_PY04].FUNC_CTL = PIOC_PY04_FUNC_CTL_PGPIO_Y_04;
    HPM_PIOC->PAD[IOC_PAD_PY05].FUNC_CTL = PIOC_PY05_FUNC_CTL_PGPIO_Y_05;
}

void init_uart_pins(UART_Type *ptr)
{
    if (ptr == HPM_UART0) {
        HPM_IOC->PAD[IOC_PAD_PA00].FUNC_CTL = IOC_PA00_FUNC_CTL_UART0_TXD;
        HPM_IOC->PAD[IOC_PAD_PA01].FUNC_CTL = IOC_PA01_FUNC_CTL_UART0_RXD;
    } else if (ptr == HPM_UART2) {
        HPM_IOC->PAD[IOC_PAD_PB08].FUNC_CTL = IOC_PB08_FUNC_CTL_UART2_TXD;
        HPM_IOC->PAD[IOC_PAD_PB09].FUNC_CTL = IOC_PB09_FUNC_CTL_UART2_RXD;
        HPM_IOC->PAD[IOC_PAD_PB10].FUNC_CTL = IOC_PB10_FUNC_CTL_UART2_DE;
    } else if (ptr == HPM_UART3) {
        /* using for uart_lin function */
        HPM_IOC->PAD[IOC_PAD_PA14].FUNC_CTL = IOC_PA14_FUNC_CTL_UART3_RXD;
        HPM_IOC->PAD[IOC_PAD_PA15].FUNC_CTL = IOC_PA15_FUNC_CTL_UART3_TXD;
    } else if (ptr == HPM_UART7) {
        /* using for uart_lin function */
        HPM_IOC->PAD[IOC_PAD_PA31].FUNC_CTL = IOC_PA31_FUNC_CTL_UART7_TXD;
        HPM_IOC->PAD[IOC_PAD_PA30].FUNC_CTL = IOC_PA30_FUNC_CTL_UART7_RXD;
    } else {
        ;
    }
}

void init_lin_transceiver_ctrl_pin(void)
{
    /* PA24 is used to control the 12V power supply of the LIN transceiver */
    HPM_IOC->PAD[IOC_PAD_PA24].FUNC_CTL = IOC_PA24_FUNC_CTL_GPIO_A_24;
    /* PA13 is used to control the LIN transceiver not to enter sleep mode */
    HPM_IOC->PAD[IOC_PAD_PA13].FUNC_CTL = IOC_PA13_FUNC_CTL_GPIO_A_13;
}

/* for uart_lin case, need to configure pin as gpio to sent break signal */
void init_uart_pin_as_gpio(UART_Type *ptr)
{
    /* pull-up */
    uint32_t pad_ctl = IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);

    if (ptr == HPM_UART3) {
        HPM_IOC->PAD[IOC_PAD_PA14].PAD_CTL = pad_ctl;
        HPM_IOC->PAD[IOC_PAD_PA15].PAD_CTL = pad_ctl;
        HPM_IOC->PAD[IOC_PAD_PA14].FUNC_CTL = IOC_PA14_FUNC_CTL_GPIO_A_14;
        HPM_IOC->PAD[IOC_PAD_PA15].FUNC_CTL = IOC_PA15_FUNC_CTL_GPIO_A_15;
    }
}

void init_i2c_pins(I2C_Type *ptr)
{
    if (ptr == HPM_I2C0) {
        HPM_IOC->PAD[IOC_PAD_PB02].FUNC_CTL = IOC_PB02_FUNC_CTL_I2C0_SCL | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;
        HPM_IOC->PAD[IOC_PAD_PB03].FUNC_CTL = IOC_PB03_FUNC_CTL_I2C0_SDA | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;
        HPM_IOC->PAD[IOC_PAD_PB02].PAD_CTL = IOC_PAD_PAD_CTL_OD_SET(1) | IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);
        HPM_IOC->PAD[IOC_PAD_PB03].PAD_CTL = IOC_PAD_PAD_CTL_OD_SET(1) | IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);
    } else if (ptr == HPM_I2C1) {
        HPM_IOC->PAD[IOC_PAD_PB06].FUNC_CTL = IOC_PB06_FUNC_CTL_I2C1_SDA | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;
        HPM_IOC->PAD[IOC_PAD_PB07].FUNC_CTL = IOC_PB07_FUNC_CTL_I2C1_SCL | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;
        HPM_IOC->PAD[IOC_PAD_PB06].PAD_CTL = IOC_PAD_PAD_CTL_OD_SET(1) | IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);
        HPM_IOC->PAD[IOC_PAD_PB07].PAD_CTL = IOC_PAD_PAD_CTL_OD_SET(1) | IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);
    } else {
        ;
    }
}

void init_gpio_pins(void)
{
    /* configure pad setting: pull enable and pull up, schmitt trigger enable */
    /* enable schmitt trigger to eliminate jitter of pin used as button */

    /* Button */
    uint32_t pad_ctl = IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1) | IOC_PAD_PAD_CTL_HYS_SET(1);
    HPM_IOC->PAD[IOC_PAD_PA09].FUNC_CTL = IOC_PA09_FUNC_CTL_GPIO_A_09;
    HPM_IOC->PAD[IOC_PAD_PA09].PAD_CTL = pad_ctl;
}

void init_spi_pins(SPI_Type *ptr)
{
    if (ptr == HPM_SPI1) {
        HPM_IOC->PAD[IOC_PAD_PA25].FUNC_CTL = IOC_PA25_FUNC_CTL_SPI1_CS_1;
        HPM_IOC->PAD[IOC_PAD_PA26].FUNC_CTL = IOC_PA26_FUNC_CTL_SPI1_CS_0;
        HPM_IOC->PAD[IOC_PAD_PA27].FUNC_CTL = IOC_PA27_FUNC_CTL_SPI1_SCLK | IOC_PAD_FUNC_CTL_LOOP_BACK_SET(1);
        HPM_IOC->PAD[IOC_PAD_PA28].FUNC_CTL = IOC_PA28_FUNC_CTL_SPI1_MISO;
        HPM_IOC->PAD[IOC_PAD_PA29].FUNC_CTL = IOC_PA29_FUNC_CTL_SPI1_MOSI;
    }
}

void init_spi_pins_with_gpio_as_cs(SPI_Type *ptr)
{
    if (ptr == HPM_SPI1) {
        HPM_IOC->PAD[IOC_PAD_PA25].FUNC_CTL = IOC_PA25_FUNC_CTL_GPIO_A_25;
        HPM_IOC->PAD[IOC_PAD_PA26].FUNC_CTL = IOC_PA26_FUNC_CTL_GPIO_A_26;
        HPM_IOC->PAD[IOC_PAD_PA27].FUNC_CTL = IOC_PA27_FUNC_CTL_SPI1_SCLK | IOC_PAD_FUNC_CTL_LOOP_BACK_SET(1);
        HPM_IOC->PAD[IOC_PAD_PA28].FUNC_CTL = IOC_PA28_FUNC_CTL_SPI1_MISO;
        HPM_IOC->PAD[IOC_PAD_PA29].FUNC_CTL = IOC_PA29_FUNC_CTL_SPI1_MOSI;
    }
}


void init_gptmr_pins(GPTMR_Type *ptr)
{
    if (ptr == HPM_GPTMR0) {
        HPM_IOC->PAD[IOC_PAD_PB06].FUNC_CTL = IOC_PB06_FUNC_CTL_GPTMR0_CAPT_0;
        HPM_IOC->PAD[IOC_PAD_PB07].FUNC_CTL = IOC_PB07_FUNC_CTL_GPTMR0_COMP_0;
        HPM_IOC->PAD[IOC_PAD_PB08].FUNC_CTL = IOC_PB08_FUNC_CTL_GPTMR0_COMP_1;
    }
}

void init_hall_trgm_pins(void)
{
    init_qeiv2_uvw_pins(HPM_QEI1);
}

void init_qei_trgm_pins(void)
{
    init_qeiv2_ab_pins(HPM_QEI1);
}

void init_butn_pins(void)
{
    /* configure pad setting: pull enable and pull up, schmitt trigger enable */
    /* enable schmitt trigger to eliminate jitter of pin used as button */

    /* Button */
    uint32_t pad_ctl = IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1) | IOC_PAD_PAD_CTL_HYS_SET(1);
    HPM_IOC->PAD[IOC_PAD_PA09].FUNC_CTL = IOC_PA09_FUNC_CTL_GPIO_A_09;
    HPM_IOC->PAD[IOC_PAD_PA09].PAD_CTL = pad_ctl;
}

void init_acmp_pins(void)
{
    /* configure to ACMP_COMP_1(ALT16) function */
    HPM_IOC->PAD[IOC_PAD_PB09].FUNC_CTL = IOC_PB09_FUNC_CTL_ACMP_COMP_1;
    /* configure to CMP1_INN4 function */
    HPM_IOC->PAD[IOC_PAD_PB11].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
}

void init_pwm_pins(PWM_Type *ptr)
{
    if (ptr == HPM_PWM0) {
        HPM_IOC->PAD[IOC_PAD_PA26].FUNC_CTL = IOC_PA26_FUNC_CTL_PWM0_P_2;
        HPM_IOC->PAD[IOC_PAD_PA27].FUNC_CTL = IOC_PA27_FUNC_CTL_PWM0_P_3;
        HPM_IOC->PAD[IOC_PAD_PA28].FUNC_CTL = IOC_PA28_FUNC_CTL_PWM0_P_4;
        HPM_IOC->PAD[IOC_PAD_PA29].FUNC_CTL = IOC_PA29_FUNC_CTL_PWM0_P_5;
        HPM_IOC->PAD[IOC_PAD_PA30].FUNC_CTL = IOC_PA30_FUNC_CTL_PWM0_P_6;
        HPM_IOC->PAD[IOC_PAD_PA31].FUNC_CTL = IOC_PA31_FUNC_CTL_PWM0_P_7;
    }
}

void init_adc_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PB05].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;         /* ADC0.13 */
}

void init_adc_bldc_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PB13].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;         /* ADC_IU:   ADC0.5 /ADC1.5  */
    HPM_IOC->PAD[IOC_PAD_PB14].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;         /* ADC_IV:   ADC0.6 /ADC1.6  */
}

void init_adc_qeiv2_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PB12].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;         /* ADC_IW:   ADC0.4 /ADC1.4  */
    HPM_IOC->PAD[IOC_PAD_PB13].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;         /* ADC_IU:   ADC0.5 /ADC1.5  */
}

void init_usb_pins(void)
{
    /* Package QFN48 and LQFP64 should be set PA24 and PA25 pins as analog type to enable USB_P and USB_N. */
    /*
     * HPM_IOC->PAD[IOC_PAD_PA24].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
     * HPM_IOC->PAD[IOC_PAD_PA25].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
     */

    /* Package QFN32 should be set PA26 and PA27 pins as analog type to enable USB_P and USB_N. */
    /*
     * HPM_IOC->PAD[IOC_PAD_PA26].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
     * HPM_IOC->PAD[IOC_PAD_PA27].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
     */

    /* USB0_ID */
    HPM_IOC->PAD[IOC_PAD_PY00].FUNC_CTL = IOC_PY00_FUNC_CTL_USB0_ID;
    /* USB0_OC */
    HPM_IOC->PAD[IOC_PAD_PY01].FUNC_CTL = IOC_PY01_FUNC_CTL_USB0_OC;
    /* USB0_PWR */
    HPM_IOC->PAD[IOC_PAD_PY02].FUNC_CTL = IOC_PY02_FUNC_CTL_USB0_PWR;

    /* PY port IO needs to configure PIOC as well */
    HPM_PIOC->PAD[IOC_PAD_PY00].FUNC_CTL = PIOC_PY00_FUNC_CTL_SOC_GPIO_Y_00;
    HPM_PIOC->PAD[IOC_PAD_PY01].FUNC_CTL = PIOC_PY01_FUNC_CTL_SOC_GPIO_Y_01;
    HPM_PIOC->PAD[IOC_PAD_PY02].FUNC_CTL = PIOC_PY02_FUNC_CTL_SOC_GPIO_Y_02;
}

void init_can_pins(MCAN_Type *ptr)
{
    if (ptr == HPM_MCAN3) {
        HPM_IOC->PAD[IOC_PAD_PY04].FUNC_CTL = IOC_PY04_FUNC_CTL_MCAN3_RXD;
        HPM_IOC->PAD[IOC_PAD_PY05].FUNC_CTL = IOC_PY05_FUNC_CTL_MCAN3_TXD;
        /* PY port IO needs to configure PIOC as well */
        HPM_PIOC->PAD[IOC_PAD_PY04].FUNC_CTL = PIOC_PY04_FUNC_CTL_SOC_GPIO_Y_04;
        HPM_PIOC->PAD[IOC_PAD_PY05].FUNC_CTL = PIOC_PY05_FUNC_CTL_SOC_GPIO_Y_05;
    }
}

void init_led_pins_as_gpio(void)
{
    HPM_IOC->PAD[IOC_PAD_PA23].FUNC_CTL = IOC_PA23_FUNC_CTL_GPIO_A_23;
}

void init_led_pins_as_pwm(void)
{
    HPM_IOC->PAD[IOC_PAD_PA23].FUNC_CTL = IOC_PA23_FUNC_CTL_TRGM0_P_03;
}

void init_dac_pins(DAC_Type *ptr)
{
    if (ptr == HPM_DAC0) {
        HPM_IOC->PAD[IOC_PAD_PB08].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;  /* DAC0.OUT */
    } else if (ptr == HPM_DAC1) {
        HPM_IOC->PAD[IOC_PAD_PB09].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;  /* DAC1.OUT */
    }
}

void init_plb_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PA26].FUNC_CTL = IOC_PA26_FUNC_CTL_TRGM0_P_02;
}

void init_qeo_pins(QEO_Type *ptr)
{
    if (ptr == HPM_QEO0) {
        HPM_IOC->PAD[IOC_PAD_PA20].FUNC_CTL = IOC_PA20_FUNC_CTL_QEO0_A;
        HPM_IOC->PAD[IOC_PAD_PA21].FUNC_CTL = IOC_PA21_FUNC_CTL_QEO0_B;
        HPM_IOC->PAD[IOC_PAD_PA22].FUNC_CTL = IOC_PA22_FUNC_CTL_QEO0_Z;
    }
}

void init_sei_pins(SEI_Type *ptr, uint8_t sei_ctrl_idx)
{
    if (ptr == HPM_SEI) {
        if (sei_ctrl_idx == SEI_CTRL_1) {
            HPM_IOC->PAD[IOC_PAD_PA16].FUNC_CTL = IOC_PA16_FUNC_CTL_SEI1_DE;
            HPM_IOC->PAD[IOC_PAD_PA17].FUNC_CTL = IOC_PA17_FUNC_CTL_SEI1_CK;
            HPM_IOC->PAD[IOC_PAD_PA18].FUNC_CTL = IOC_PA18_FUNC_CTL_SEI1_TX;
            HPM_IOC->PAD[IOC_PAD_PA19].FUNC_CTL = IOC_PA19_FUNC_CTL_SEI1_RX;
        }
    }
}

void init_rdc_pin(void)
{
    HPM_IOC->PAD[IOC_PAD_PA28].FUNC_CTL = IOC_PA28_FUNC_CTL_RDC0_EXC_P;
    HPM_IOC->PAD[IOC_PAD_PB13].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
    HPM_IOC->PAD[IOC_PAD_PB14].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;

/*The GPIO is designed for debug */
#ifdef RDC_SAMPLE_TEST_GPIO_OUTPUT
    HPM_IOC->PAD[IOC_PAD_PB04].FUNC_CTL = IOC_PB04_FUNC_CTL_TRGM0_P_00;
#endif
}

void init_qeiv2_uvw_pins(QEIV2_Type *ptr)
{
    if (ptr == HPM_QEI1) {
        HPM_IOC->PAD[IOC_PAD_PA10].FUNC_CTL = IOC_PA10_FUNC_CTL_QEI1_A;
        HPM_IOC->PAD[IOC_PAD_PA11].FUNC_CTL = IOC_PA11_FUNC_CTL_QEI1_B;
        HPM_IOC->PAD[IOC_PAD_PA12].FUNC_CTL = IOC_PA12_FUNC_CTL_QEI1_Z;
    }
}

void init_qeiv2_ab_pins(QEIV2_Type *ptr)
{
    if (ptr == HPM_QEI1) {
        HPM_IOC->PAD[IOC_PAD_PA10].FUNC_CTL = IOC_PA10_FUNC_CTL_QEI1_A;
        HPM_IOC->PAD[IOC_PAD_PA11].FUNC_CTL = IOC_PA11_FUNC_CTL_QEI1_B;
    }
}

void init_qeiv2_abz_pins(QEIV2_Type *ptr)
{
    if (ptr == HPM_QEI1) {
        HPM_IOC->PAD[IOC_PAD_PA10].FUNC_CTL = IOC_PA10_FUNC_CTL_QEI1_A;
        HPM_IOC->PAD[IOC_PAD_PA11].FUNC_CTL = IOC_PA11_FUNC_CTL_QEI1_B;
        HPM_IOC->PAD[IOC_PAD_PA12].FUNC_CTL = IOC_PA12_FUNC_CTL_QEI1_Z;
    }
}

void init_opamp_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PB00].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
    HPM_IOC->PAD[IOC_PAD_PB04].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
}
