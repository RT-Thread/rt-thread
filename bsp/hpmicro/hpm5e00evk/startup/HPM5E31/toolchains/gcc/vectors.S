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
    IRQ_HANDLER 5 /* GPIO0_E IRQ handler */
    IRQ_HANDLER 6 /* GPIO0_F IRQ handler */
    IRQ_HANDLER 7 /* GPIO0_V IRQ handler */
    IRQ_HANDLER 8 /* GPIO0_W IRQ handler */
    IRQ_HANDLER 9 /* GPIO0_X IRQ handler */
    IRQ_HANDLER 10 /* GPIO0_Y IRQ handler */
    IRQ_HANDLER 11 /* GPTMR0 IRQ handler */
    IRQ_HANDLER 12 /* GPTMR1 IRQ handler */
    IRQ_HANDLER 13 /* GPTMR2 IRQ handler */
    IRQ_HANDLER 14 /* GPTMR3 IRQ handler */
    IRQ_HANDLER 15 /* OWR0 IRQ handler */
    IRQ_HANDLER 16 /* OWR1 IRQ handler */
    IRQ_HANDLER 17 /* EUI0 IRQ handler */
    IRQ_HANDLER 18 /* EUI1 IRQ handler */
    IRQ_HANDLER 19 /* UART0 IRQ handler */
    IRQ_HANDLER 20 /* UART1 IRQ handler */
    IRQ_HANDLER 21 /* UART2 IRQ handler */
    IRQ_HANDLER 22 /* UART3 IRQ handler */
    IRQ_HANDLER 23 /* UART4 IRQ handler */
    IRQ_HANDLER 24 /* UART5 IRQ handler */
    IRQ_HANDLER 25 /* UART6 IRQ handler */
    IRQ_HANDLER 26 /* UART7 IRQ handler */
    IRQ_HANDLER 27 /* I2C0 IRQ handler */
    IRQ_HANDLER 28 /* I2C1 IRQ handler */
    IRQ_HANDLER 29 /* I2C2 IRQ handler */
    IRQ_HANDLER 30 /* I2C3 IRQ handler */
    IRQ_HANDLER 31 /* SPI0 IRQ handler */
    IRQ_HANDLER 32 /* SPI1 IRQ handler */
    IRQ_HANDLER 33 /* SPI2 IRQ handler */
    IRQ_HANDLER 34 /* SPI3 IRQ handler */
    IRQ_HANDLER 35 /* TSNS IRQ handler */
    IRQ_HANDLER 36 /* MBX0A IRQ handler */
    IRQ_HANDLER 37 /* MBX0B IRQ handler */
    IRQ_HANDLER 38 /* EWDG0 IRQ handler */
    IRQ_HANDLER 39 /* EWDG1 IRQ handler */
    IRQ_HANDLER 40 /* HDMA IRQ handler */
    IRQ_HANDLER 41 /* LOBS IRQ handler */
    IRQ_HANDLER 42 /* ADC0 IRQ handler */
    IRQ_HANDLER 43 /* ADC1 IRQ handler */
    IRQ_HANDLER 44 /* ACMP0[0] IRQ handler */
    IRQ_HANDLER 45 /* ACMP0[1] IRQ handler */
    IRQ_HANDLER 46 /* MCAN0 IRQ handler */
    IRQ_HANDLER 47 /* MCAN1 IRQ handler */
    IRQ_HANDLER 48 /* MCAN2 IRQ handler */
    IRQ_HANDLER 49 /* MCAN3 IRQ handler */
    IRQ_HANDLER 50 /* PTPC IRQ handler */
    IRQ_HANDLER 51 /* QEI0 IRQ handler */
    IRQ_HANDLER 52 /* QEI1 IRQ handler */
    IRQ_HANDLER 53 /* PWM0 IRQ handler */
    IRQ_HANDLER 54 /* PWM1 IRQ handler */
    IRQ_HANDLER 55 /* SDM0 IRQ handler */
    IRQ_HANDLER 56 /* TRGM[0] IRQ handler */
    IRQ_HANDLER 57 /* TRGM[1] IRQ handler */
    IRQ_HANDLER 58 /* ENET0 IRQ handler */
    IRQ_HANDLER 59 /* NTMR0 IRQ handler */
    IRQ_HANDLER 60 /* USB0 IRQ handler */
    IRQ_HANDLER 61 /* ESC IRQ handler */
    IRQ_HANDLER 62 /* ESC_SYNC0 IRQ handler */
    IRQ_HANDLER 63 /* ESC_SYNC1 IRQ handler */
    IRQ_HANDLER 64 /* ESC_RESET IRQ handler */
    IRQ_HANDLER 65 /* XPI0 IRQ handler */
    IRQ_HANDLER 66 /* PPI IRQ handler */
    IRQ_HANDLER 67 /* XDMA IRQ handler */
    IRQ_HANDLER 68 /* PGPIO IRQ handler */
    IRQ_HANDLER 69 /* PEWDG IRQ handler */
    IRQ_HANDLER 70 /* PTMR IRQ handler */
    IRQ_HANDLER 71 /* PUART IRQ handler */
    IRQ_HANDLER 72 /* FUSE IRQ handler */
    IRQ_HANDLER 73 /* DGO_PAD_WAKEUP IRQ handler */
    IRQ_HANDLER 74 /* DGO_CNT_WAKEUP IRQ handler */
    IRQ_HANDLER 75 /* BROWNOUT IRQ handler */
    IRQ_HANDLER 76 /* SYSCTL IRQ handler */
    IRQ_HANDLER 77 /* CPU0 IRQ handler */
    IRQ_HANDLER 78 /* DEBUG0 IRQ handler */
    IRQ_HANDLER 79 /* DEBUG1 IRQ handler */
