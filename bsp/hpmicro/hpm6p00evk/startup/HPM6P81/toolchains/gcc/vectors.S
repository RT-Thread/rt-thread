/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
    .section .vector_table, "a"
    .global __vector_table
    .align 9
__vector_table:
    .weak default_isr_trap
    .set default_isr_trap, SW_handler
    .long default_isr_trap
    IRQ_HANDLER 1 /* GPIO0_A IRQ handler */
    IRQ_HANDLER 2 /* GPIO0_B IRQ handler */
    IRQ_HANDLER 3 /* GPIO0_C IRQ handler */
    IRQ_HANDLER 4 /* GPIO0_D IRQ handler */
    IRQ_HANDLER 5 /* GPIO0_X IRQ handler */
    IRQ_HANDLER 6 /* GPIO0_Y IRQ handler */
    IRQ_HANDLER 7 /* GPIO1_A IRQ handler */
    IRQ_HANDLER 8 /* GPIO1_B IRQ handler */
    IRQ_HANDLER 9 /* GPIO1_C IRQ handler */
    IRQ_HANDLER 10 /* GPIO1_D IRQ handler */
    IRQ_HANDLER 11 /* GPIO1_X IRQ handler */
    IRQ_HANDLER 12 /* GPIO1_Y IRQ handler */
    IRQ_HANDLER 13 /* GPTMR0 IRQ handler */
    IRQ_HANDLER 14 /* GPTMR1 IRQ handler */
    IRQ_HANDLER 15 /* GPTMR2 IRQ handler */
    IRQ_HANDLER 16 /* GPTMR3 IRQ handler */
    IRQ_HANDLER 17 /* Reserved */
    IRQ_HANDLER 18 /* Reserved */
    IRQ_HANDLER 19 /* Reserved */
    IRQ_HANDLER 20 /* Reserved */
    IRQ_HANDLER 21 /* UART0 IRQ handler */
    IRQ_HANDLER 22 /* UART1 IRQ handler */
    IRQ_HANDLER 23 /* UART2 IRQ handler */
    IRQ_HANDLER 24 /* UART3 IRQ handler */
    IRQ_HANDLER 25 /* UART4 IRQ handler */
    IRQ_HANDLER 26 /* UART5 IRQ handler */
    IRQ_HANDLER 27 /* UART6 IRQ handler */
    IRQ_HANDLER 28 /* UART7 IRQ handler */
    IRQ_HANDLER 29 /* I2C0 IRQ handler */
    IRQ_HANDLER 30 /* I2C1 IRQ handler */
    IRQ_HANDLER 31 /* I2C2 IRQ handler */
    IRQ_HANDLER 32 /* I2C3 IRQ handler */
    IRQ_HANDLER 33 /* SPI0 IRQ handler */
    IRQ_HANDLER 34 /* SPI1 IRQ handler */
    IRQ_HANDLER 35 /* SPI2 IRQ handler */
    IRQ_HANDLER 36 /* SPI3 IRQ handler */
    IRQ_HANDLER 37 /* TSNS IRQ handler */
    IRQ_HANDLER 38 /* MBX0A IRQ handler */
    IRQ_HANDLER 39 /* MBX0B IRQ handler */
    IRQ_HANDLER 40 /* MBX1A IRQ handler */
    IRQ_HANDLER 41 /* MBX1B IRQ handler */
    IRQ_HANDLER 42 /* EWDG0 IRQ handler */
    IRQ_HANDLER 43 /* EWDG1 IRQ handler */
    IRQ_HANDLER 44 /* EWDG2 IRQ handler */
    IRQ_HANDLER 45 /* EWDG3 IRQ handler */
    IRQ_HANDLER 46 /* HDMA IRQ handler */
    IRQ_HANDLER 47 /* LOBS IRQ handler */
    IRQ_HANDLER 48 /* ADC0 IRQ handler */
    IRQ_HANDLER 49 /* ADC1 IRQ handler */
    IRQ_HANDLER 50 /* ADC2 IRQ handler */
    IRQ_HANDLER 51 /* ADC3 IRQ handler */
    IRQ_HANDLER 52 /* DAC0 IRQ handler */
    IRQ_HANDLER 53 /* DAC1 IRQ handler */
    IRQ_HANDLER 54 /* ACMP0[0] IRQ handler */
    IRQ_HANDLER 55 /* ACMP0[1] IRQ handler */
    IRQ_HANDLER 56 /* ACMP1[0] IRQ handler */
    IRQ_HANDLER 57 /* ACMP1[1] IRQ handler */
    IRQ_HANDLER 58 /* ACMP2[0] IRQ handler */
    IRQ_HANDLER 59 /* ACMP2[1] IRQ handler */
    IRQ_HANDLER 60 /* ACMP3[0] IRQ handler */
    IRQ_HANDLER 61 /* ACMP3[1] IRQ handler */
    IRQ_HANDLER 62 /* I2S0 IRQ handler */
    IRQ_HANDLER 63 /* I2S1 IRQ handler */
    IRQ_HANDLER 64 /* DAO IRQ handler */
    IRQ_HANDLER 65 /* PDM IRQ handler */
    IRQ_HANDLER 66 /* MCAN0 IRQ handler */
    IRQ_HANDLER 67 /* MCAN1 IRQ handler */
    IRQ_HANDLER 68 /* MCAN2 IRQ handler */
    IRQ_HANDLER 69 /* MCAN3 IRQ handler */
    IRQ_HANDLER 70 /* PTPC IRQ handler */
    IRQ_HANDLER 71 /* QEI0 IRQ handler */
    IRQ_HANDLER 72 /* QEI1 IRQ handler */
    IRQ_HANDLER 73 /* PWM0 IRQ handler */
    IRQ_HANDLER 74 /* PWM1 IRQ handler */
    IRQ_HANDLER 75 /* PWM2 IRQ handler */
    IRQ_HANDLER 76 /* PWM3 IRQ handler */
    IRQ_HANDLER 77 /* RDC0 IRQ handler */
    IRQ_HANDLER 78 /* SDM0 IRQ handler */
    IRQ_HANDLER 79 /* SEI0[0] IRQ handler */
    IRQ_HANDLER 80 /* SEI0[1] IRQ handler */
    IRQ_HANDLER 81 /* MTG0 IRQ handler */
    IRQ_HANDLER 82 /* VSC0 IRQ handler */
    IRQ_HANDLER 83 /* CLC0[0] IRQ handler */
    IRQ_HANDLER 84 /* CLC0[1] IRQ handler */
    IRQ_HANDLER 85 /* TRGMUX0 IRQ handler */
    IRQ_HANDLER 86 /* TRGMUX1 IRQ handler */
    IRQ_HANDLER 87 /* ENET0 IRQ handler */
    IRQ_HANDLER 88 /* NTMR0 IRQ handler */
    IRQ_HANDLER 89 /* USB0 IRQ handler */
    IRQ_HANDLER 90 /* XPI0 IRQ handler */
    IRQ_HANDLER 91 /* FEMC IRQ handler */
    IRQ_HANDLER 92 /* PPI IRQ handler */
    IRQ_HANDLER 93 /* XDMA IRQ handler */
    IRQ_HANDLER 94 /* FFA IRQ handler */
    IRQ_HANDLER 95 /* SDP IRQ handler */
    IRQ_HANDLER 96 /* RNG IRQ handler */
    IRQ_HANDLER 97 /* PSEC IRQ handler */
    IRQ_HANDLER 98 /* PGPIO IRQ handler */
    IRQ_HANDLER 99 /* PEWDG IRQ handler */
    IRQ_HANDLER 100 /* PTMR IRQ handler */
    IRQ_HANDLER 101 /* PUART IRQ handler */
    IRQ_HANDLER 102 /* FUSE IRQ handler */
    IRQ_HANDLER 103 /* SECMON IRQ handler */
    IRQ_HANDLER 104 /* PAD_WAKEUP IRQ handler */
    IRQ_HANDLER 105 /* BROWNOUT IRQ handler */
    IRQ_HANDLER 106 /* SYSCTL IRQ handler */
    IRQ_HANDLER 107 /* CPU0 IRQ handler */
    IRQ_HANDLER 108 /* CPU1 IRQ handler */
    IRQ_HANDLER 109 /* DEBUG0 IRQ handler */
    IRQ_HANDLER 110 /* DEBUG1 IRQ handler */