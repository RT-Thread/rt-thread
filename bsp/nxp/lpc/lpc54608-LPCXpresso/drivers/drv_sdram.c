/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-02     Yang        the first version
 */

#include "drv_sdram.h"

#include <fsl_emc.h>
#include "fsl_iocon.h"


/*******************************************************************************************
* @函数名：sdram_gpio_config()
* @参数  ：void
* @返回值：void
* @描述  ：SDRAM管脚配置函数，内部调用
*********************************************************************************************/
static void  sdram_gpio_config(void)
{
//    CLOCK_EnableClock(kCLOCK_Iocon);                           /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */

    const uint32_t port0_pin15_config = (
                                            IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_WEN */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN15_IDX, port0_pin15_config); /* PORT0 PIN15 (coords: L4) is configured as EMC_WEN */
    const uint32_t port0_pin18_config = (
                                            IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_A(0) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN18_IDX, port0_pin18_config); /* PORT0 PIN18 (coords: C14) is configured as EMC_A(0) */
    const uint32_t port0_pin19_config = (
                                            IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_A(1) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN19_IDX, port0_pin19_config); /* PORT0 PIN19 (coords: C6) is configured as EMC_A(1) */
    const uint32_t port0_pin2_config = (
                                           IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_D(0) */
                                           IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                           IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                           IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                           IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                           IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                           IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                       );
    IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN2_IDX, port0_pin2_config); /* PORT0 PIN2 (coords: E9) is configured as EMC_D(0) */
    const uint32_t port0_pin20_config = (
                                            IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_A(2) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN20_IDX, port0_pin20_config); /* PORT0 PIN20 (coords: D13) is configured as EMC_A(2) */
    const uint32_t port0_pin21_config = (
                                            IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_A(3) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN21_IDX, port0_pin21_config); /* PORT0 PIN21 (coords: C13) is configured as EMC_A(3) */
    const uint32_t port0_pin3_config = (
                                           IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_D(1) */
                                           IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                           IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                           IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                           IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                           IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                           IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                       );
    IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN3_IDX, port0_pin3_config); /* PORT0 PIN3 (coords: A10) is configured as EMC_D(1) */
    const uint32_t port0_pin4_config = (
                                           IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_D(2) */
                                           IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                           IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                           IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                           IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                           IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                           IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                       );
    IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN4_IDX, port0_pin4_config); /* PORT0 PIN4 (coords: C8) is configured as EMC_D(2) */
    const uint32_t port0_pin5_config = (
                                           IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_D(3) */
                                           IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                           IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                           IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                           IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                           IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                           IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                       );
    IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN5_IDX, port0_pin5_config); /* PORT0 PIN5 (coords: E7) is configured as EMC_D(3) */
    const uint32_t port0_pin6_config = (
                                           IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_D(4) */
                                           IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                           IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                           IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                           IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                           IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                           IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                       );
    IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN6_IDX, port0_pin6_config); /* PORT0 PIN6 (coords: A5) is configured as EMC_D(4) */
    const uint32_t port0_pin7_config = (
                                           IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_D(5) */
                                           IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                           IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                           IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                           IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                           IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                           IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                       );
    IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN7_IDX, port0_pin7_config); /* PORT0 PIN7 (coords: H12) is configured as EMC_D(5) */
    const uint32_t port0_pin8_config = (
                                           IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_D(6) */
                                           IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                           IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                           IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                           IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                           IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                           IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                       );
    IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN8_IDX, port0_pin8_config); /* PORT0 PIN8 (coords: H10) is configured as EMC_D(6) */
    const uint32_t port0_pin9_config = (
                                           IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_D(7) */
                                           IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                           IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                           IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                           IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                           IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                           IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                       );
    IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN9_IDX, port0_pin9_config); /* PORT0 PIN9 (coords: G12) is configured as EMC_D(7) */
    const uint32_t port1_pin10_config = (
                                            IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_RASN */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN10_IDX, port1_pin10_config); /* PORT1 PIN10 (coords: N9) is configured as EMC_RASN */
    const uint32_t port1_pin11_config = (
                                            IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_CLK(0) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN11_IDX, port1_pin11_config); /* PORT1 PIN11 (coords: B4) is configured as EMC_CLK(0) */
    const uint32_t port1_pin12_config = (
                                            IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_DYCSN(0) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN12_IDX, port1_pin12_config); /* PORT1 PIN12 (coords: K9) is configured as EMC_DYCSN(0) */
    const uint32_t port1_pin13_config = (
                                            IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_DQM(0) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN13_IDX, port1_pin13_config); /* PORT1 PIN13 (coords: G10) is configured as EMC_DQM(0) */
    const uint32_t port1_pin14_config = (
                                            IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_DQM(1) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN14_IDX, port1_pin14_config); /* PORT1 PIN14 (coords: C12) is configured as EMC_DQM(1) */
    const uint32_t port1_pin15_config = (
                                            IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_CKE(0) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN15_IDX, port1_pin15_config); /* PORT1 PIN15 (coords: A11) is configured as EMC_CKE(0) */
    const uint32_t port1_pin16_config = (
                                            IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_A(10) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN16_IDX, port1_pin16_config); /* PORT1 PIN16 (coords: B7) is configured as EMC_A(10) */
    const uint32_t port1_pin19_config = (
                                            IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_D(8) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN19_IDX, port1_pin19_config); /* PORT1 PIN19 (coords: L1) is configured as EMC_D(8) */
    const uint32_t port1_pin20_config = (
                                            IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_D(9) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN20_IDX, port1_pin20_config); /* PORT1 PIN20 (coords: M1) is configured as EMC_D(9) */
    const uint32_t port1_pin21_config = (
                                            IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_D(10) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN21_IDX, port1_pin21_config); /* PORT1 PIN21 (coords: N8) is configured as EMC_D(10) */
    const uint32_t port1_pin23_config = (
                                            IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_A(11) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN23_IDX, port1_pin23_config); /* PORT1 PIN23 (coords: M10) is configured as EMC_A(11) */
    const uint32_t port1_pin24_config = (
                                            IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_A(12) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN24_IDX, port1_pin24_config); /* PORT1 PIN24 (coords: N14) is configured as EMC_A(12) */
    const uint32_t port1_pin25_config = (
                                            IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_A(13) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN25_IDX, port1_pin25_config); /* PORT1 PIN25 (coords: M12) is configured as EMC_A(13) */
    const uint32_t port1_pin26_config = (
                                            IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_A(8) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN26_IDX, port1_pin26_config); /* PORT1 PIN26 (coords: J10) is configured as EMC_A(8) */
    const uint32_t port1_pin27_config = (
                                            IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_A(9) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN27_IDX, port1_pin27_config); /* PORT1 PIN27 (coords: F10) is configured as EMC_A(9) */
    const uint32_t port1_pin28_config = (
                                            IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_D(12) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN28_IDX, port1_pin28_config); /* PORT1 PIN28 (coords: E12) is configured as EMC_D(12) */
    const uint32_t port1_pin29_config = (
                                            IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_D(13) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN29_IDX, port1_pin29_config); /* PORT1 PIN29 (coords: C11) is configured as EMC_D(13) */
    const uint32_t port1_pin30_config = (
                                            IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_D(14) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN30_IDX, port1_pin30_config); /* PORT1 PIN30 (coords: A8) is configured as EMC_D(14) */
    const uint32_t port1_pin31_config = (
                                            IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_D(15) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN31_IDX, port1_pin31_config); /* PORT1 PIN31 (coords: C5) is configured as EMC_D(15) */
    const uint32_t port1_pin4_config = (
                                           IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_D(11) */
                                           IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                           IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                           IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                           IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                           IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                           IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                       );
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN4_IDX, port1_pin4_config); /* PORT1 PIN4 (coords: D4) is configured as EMC_D(11) */
    const uint32_t port1_pin5_config = (
                                           IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_A(4) */
                                           IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                           IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                           IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                           IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                           IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                           IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                       );
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN5_IDX, port1_pin5_config); /* PORT1 PIN5 (coords: E4) is configured as EMC_A(4) */
    const uint32_t port1_pin6_config = (
                                           IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_A(5) */
                                           IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                           IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                           IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                           IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                           IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                           IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                       );
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN6_IDX, port1_pin6_config); /* PORT1 PIN6 (coords: G4) is configured as EMC_A(5) */
    const uint32_t port1_pin7_config = (
                                           IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_A(6) */
                                           IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                           IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                           IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                           IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                           IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                           IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                       );
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN7_IDX, port1_pin7_config); /* PORT1 PIN7 (coords: N1) is configured as EMC_A(6) */
    const uint32_t port1_pin8_config = (
                                           IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_A(7) */
                                           IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                           IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                           IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                           IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                           IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                           IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                       );
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN8_IDX, port1_pin8_config); /* PORT1 PIN8 (coords: P8) is configured as EMC_A(7) */
    const uint32_t port1_pin9_config = (
                                           IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_CASN */
                                           IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                           IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                           IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                           IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                           IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                           IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                       );
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN9_IDX, port1_pin9_config); /* PORT1 PIN9 (coords: K6) is configured as EMC_CASN */
    const uint32_t port3_pin25_config = (
                                            IOCON_PIO_FUNC6 |                                        /* Pin is configured as EMC_A(14) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT3_IDX, PIN25_IDX, port3_pin25_config); /* PORT3 PIN25 (coords: P9) is configured as EMC_A(14) */
}

void lpc_sdram_hw_init(void)
{
    emc_basic_config_t basicConfig;
    emc_dynamic_timing_config_t dynTiming;
    emc_dynamic_chip_config_t dynChipConfig;

    sdram_gpio_config();

    /* Basic configuration. */
    basicConfig.endian = kEMC_LittleEndian;
    basicConfig.fbClkSrc = kEMC_IntloopbackEmcclk;
    /* EMC Clock = CPU FREQ/2 here can fit CPU freq from 12M ~ 180M.
     * If you change the divide to 0 and EMC clock is larger than 100M
     * please take refer to emc.dox to adjust EMC clock delay.
     */
    basicConfig.emcClkDiv = 1;
    /* Dynamic memory timing configuration. */
    dynTiming.readConfig = kEMC_Cmddelay;
    dynTiming.refreshPeriod_Nanosec = SDRAM_REFRESHPERIOD_NS;
    dynTiming.tRp_Ns = SDRAM_TRP_NS;
    dynTiming.tRas_Ns = SDRAM_TRAS_NS;
    dynTiming.tSrex_Ns = SDRAM_TSREX_NS;
    dynTiming.tApr_Ns = SDRAM_TAPR_NS;
    dynTiming.tWr_Ns = (1000000000 / CLOCK_GetFreq(kCLOCK_EMC) + SDRAM_TWRDELT_NS); /* one clk + 6ns */
    dynTiming.tDal_Ns = dynTiming.tWr_Ns + dynTiming.tRp_Ns;
    dynTiming.tRc_Ns = SDRAM_TRC_NS;
    dynTiming.tRfc_Ns = SDRAM_RFC_NS;
    dynTiming.tXsr_Ns = SDRAM_XSR_NS;
    dynTiming.tRrd_Ns = SDRAM_RRD_NS;
    dynTiming.tMrd_Nclk = SDRAM_MRD_NCLK;
    /* Dynamic memory chip specific configuration: Chip 0 - MTL48LC8M16A2B4-6A */
    dynChipConfig.chipIndex = 0;
    dynChipConfig.dynamicDevice = kEMC_Sdram;
    dynChipConfig.rAS_Nclk = SDRAM_RAS_NCLK;
    dynChipConfig.sdramModeReg = SDRAM_MODEREG_VALUE;
    dynChipConfig.sdramExtModeReg = 0; /* it has no use for normal sdram */
    dynChipConfig.devAddrMap = SDRAM_DEV_MEMORYMAP;
    /* EMC Basic configuration. */
    EMC_Init(EMC, &basicConfig);
    /* EMC Dynamc memory configuration. */
    EMC_DynamicMemInit(EMC, &dynTiming, &dynChipConfig, 1);
}
