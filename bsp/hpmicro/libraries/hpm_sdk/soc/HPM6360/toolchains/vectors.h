/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
.global default_irq_handler
.weak default_irq_handler
.align 2
default_irq_handler:
1:    j 1b

.macro IRQ_HANDLER irq
  .weak default_isr_\irq
  .set default_isr_\irq, default_irq_handler
  .long default_isr_\irq
.endm

.section .vector_table, "a"
.global __vector_table
.align 9

__vector_table:
    .weak default_isr_trap
    .set default_isr_trap, irq_handler_trap
    .long default_isr_trap
    IRQ_HANDLER 1 /* GPIO0_A IRQ handler */
    IRQ_HANDLER 2 /* GPIO0_B IRQ handler */
    IRQ_HANDLER 3 /* GPIO0_C IRQ handler */
    IRQ_HANDLER 4 /* GPIO0_D IRQ handler */
    IRQ_HANDLER 5 /* GPIO0_X IRQ handler */
    IRQ_HANDLER 6 /* GPIO0_Y IRQ handler */
    IRQ_HANDLER 7 /* GPIO0_Z IRQ handler */
    IRQ_HANDLER 8 /* ADC0 IRQ handler */
    IRQ_HANDLER 9 /* ADC1 IRQ handler */
    IRQ_HANDLER 10 /* ADC2 IRQ handler */
    IRQ_HANDLER 11 /* DAC IRQ handler */
    IRQ_HANDLER 12 /* ACMP[0] IRQ handler */
    IRQ_HANDLER 13 /* ACMP[1] IRQ handler */
    IRQ_HANDLER 14 /* SPI0 IRQ handler */
    IRQ_HANDLER 15 /* SPI1 IRQ handler */
    IRQ_HANDLER 16 /* SPI2 IRQ handler */
    IRQ_HANDLER 17 /* SPI3 IRQ handler */
    IRQ_HANDLER 18 /* UART0 IRQ handler */
    IRQ_HANDLER 19 /* UART1 IRQ handler */
    IRQ_HANDLER 20 /* UART2 IRQ handler */
    IRQ_HANDLER 21 /* UART3 IRQ handler */
    IRQ_HANDLER 22 /* UART4 IRQ handler */
    IRQ_HANDLER 23 /* UART5 IRQ handler */
    IRQ_HANDLER 24 /* UART6 IRQ handler */
    IRQ_HANDLER 25 /* UART7 IRQ handler */
    IRQ_HANDLER 26 /* CAN0 IRQ handler */
    IRQ_HANDLER 27 /* CAN1 IRQ handler */
    IRQ_HANDLER 28 /* PTPC IRQ handler */
    IRQ_HANDLER 29 /* WDG0 IRQ handler */
    IRQ_HANDLER 30 /* WDG1 IRQ handler */
    IRQ_HANDLER 31 /* TSNS IRQ handler */
    IRQ_HANDLER 32 /* MBX0A IRQ handler */
    IRQ_HANDLER 33 /* MBX0B IRQ handler */
    IRQ_HANDLER 34 /* GPTMR0 IRQ handler */
    IRQ_HANDLER 35 /* GPTMR1 IRQ handler */
    IRQ_HANDLER 36 /* GPTMR2 IRQ handler */
    IRQ_HANDLER 37 /* GPTMR3 IRQ handler */
    IRQ_HANDLER 38 /* I2C0 IRQ handler */
    IRQ_HANDLER 39 /* I2C1 IRQ handler */
    IRQ_HANDLER 40 /* I2C2 IRQ handler */
    IRQ_HANDLER 41 /* I2C3 IRQ handler */
    IRQ_HANDLER 42 /* PWM0 IRQ handler */
    IRQ_HANDLER 43 /* HALL0 IRQ handler */
    IRQ_HANDLER 44 /* QEI0 IRQ handler */
    IRQ_HANDLER 45 /* PWM1 IRQ handler */
    IRQ_HANDLER 46 /* HALL1 IRQ handler */
    IRQ_HANDLER 47 /* QEI1 IRQ handler */
    IRQ_HANDLER 48 /* SDP IRQ handler */
    IRQ_HANDLER 49 /* XPI0 IRQ handler */
    IRQ_HANDLER 50 /* XPI1 IRQ handler */
    IRQ_HANDLER 51 /* XDMA IRQ handler */
    IRQ_HANDLER 52 /* HDMA IRQ handler */
    IRQ_HANDLER 53 /* FEMC IRQ handler */
    IRQ_HANDLER 54 /* RNG IRQ handler */
    IRQ_HANDLER 55 /* I2S0 IRQ handler */
    IRQ_HANDLER 56 /* I2S1 IRQ handler */
    IRQ_HANDLER 57 /* DAO IRQ handler */
    IRQ_HANDLER 58 /* PDM IRQ handler */
    IRQ_HANDLER 59 /* FFA IRQ handler */
    IRQ_HANDLER 60 /* NTMR0 IRQ handler */
    IRQ_HANDLER 61 /* USB0 IRQ handler */
    IRQ_HANDLER 62 /* ENET0 IRQ handler */
    IRQ_HANDLER 63 /* SDXC0 IRQ handler */
    IRQ_HANDLER 64 /* PSEC IRQ handler */
    IRQ_HANDLER 65 /* PGPIO IRQ handler */
    IRQ_HANDLER 66 /* PWDG IRQ handler */
    IRQ_HANDLER 67 /* PTMR IRQ handler */
    IRQ_HANDLER 68 /* PUART IRQ handler */
    IRQ_HANDLER 69 /* FUSE IRQ handler */
    IRQ_HANDLER 70 /* SECMON IRQ handler */
    IRQ_HANDLER 71 /* RTC IRQ handler */
    IRQ_HANDLER 72 /* BUTN IRQ handler */
    IRQ_HANDLER 73 /* BGPIO IRQ handler */
    IRQ_HANDLER 74 /* BVIO IRQ handler */
    IRQ_HANDLER 75 /* BROWNOUT IRQ handler */
    IRQ_HANDLER 76 /* SYSCTL IRQ handler */
    IRQ_HANDLER 77 /* DEBUG[0] IRQ handler */
    IRQ_HANDLER 78 /* DEBUG[1] IRQ handler */


.global default_irq_s_handler
.weak default_irq_s_handler
.align 2
default_irq_s_handler:
1:    j 1b

.macro IRQ_S_HANDLER irq
  .weak default_isr_s_\irq
  .set default_isr_s_\irq, default_irq_s_handler
  .long default_isr_s_\irq
.endm

.section .vector_s_table, "a"
.global __vector_s_table
.align 9

__vector_s_table:
    .weak default_isr_s_trap
    .set default_isr_s_trap, irq_handler_s_trap
    .long default_isr_s_trap
    IRQ_S_HANDLER 1 /* GPIO0_A IRQ handler */
    IRQ_S_HANDLER 2 /* GPIO0_B IRQ handler */
    IRQ_S_HANDLER 3 /* GPIO0_C IRQ handler */
    IRQ_S_HANDLER 4 /* GPIO0_D IRQ handler */
    IRQ_S_HANDLER 5 /* GPIO0_X IRQ handler */
    IRQ_S_HANDLER 6 /* GPIO0_Y IRQ handler */
    IRQ_S_HANDLER 7 /* GPIO0_Z IRQ handler */
    IRQ_S_HANDLER 8 /* ADC0 IRQ handler */
    IRQ_S_HANDLER 9 /* ADC1 IRQ handler */
    IRQ_S_HANDLER 10 /* ADC2 IRQ handler */
    IRQ_S_HANDLER 11 /* DAC IRQ handler */
    IRQ_S_HANDLER 12 /* ACMP[0] IRQ handler */
    IRQ_S_HANDLER 13 /* ACMP[1] IRQ handler */
    IRQ_S_HANDLER 14 /* SPI0 IRQ handler */
    IRQ_S_HANDLER 15 /* SPI1 IRQ handler */
    IRQ_S_HANDLER 16 /* SPI2 IRQ handler */
    IRQ_S_HANDLER 17 /* SPI3 IRQ handler */
    IRQ_S_HANDLER 18 /* UART0 IRQ handler */
    IRQ_S_HANDLER 19 /* UART1 IRQ handler */
    IRQ_S_HANDLER 20 /* UART2 IRQ handler */
    IRQ_S_HANDLER 21 /* UART3 IRQ handler */
    IRQ_S_HANDLER 22 /* UART4 IRQ handler */
    IRQ_S_HANDLER 23 /* UART5 IRQ handler */
    IRQ_S_HANDLER 24 /* UART6 IRQ handler */
    IRQ_S_HANDLER 25 /* UART7 IRQ handler */
    IRQ_S_HANDLER 26 /* CAN0 IRQ handler */
    IRQ_S_HANDLER 27 /* CAN1 IRQ handler */
    IRQ_S_HANDLER 28 /* PTPC IRQ handler */
    IRQ_S_HANDLER 29 /* WDG0 IRQ handler */
    IRQ_S_HANDLER 30 /* WDG1 IRQ handler */
    IRQ_S_HANDLER 31 /* TSNS IRQ handler */
    IRQ_S_HANDLER 32 /* MBX0A IRQ handler */
    IRQ_S_HANDLER 33 /* MBX0B IRQ handler */
    IRQ_S_HANDLER 34 /* GPTMR0 IRQ handler */
    IRQ_S_HANDLER 35 /* GPTMR1 IRQ handler */
    IRQ_S_HANDLER 36 /* GPTMR2 IRQ handler */
    IRQ_S_HANDLER 37 /* GPTMR3 IRQ handler */
    IRQ_S_HANDLER 38 /* I2C0 IRQ handler */
    IRQ_S_HANDLER 39 /* I2C1 IRQ handler */
    IRQ_S_HANDLER 40 /* I2C2 IRQ handler */
    IRQ_S_HANDLER 41 /* I2C3 IRQ handler */
    IRQ_S_HANDLER 42 /* PWM0 IRQ handler */
    IRQ_S_HANDLER 43 /* HALL0 IRQ handler */
    IRQ_S_HANDLER 44 /* QEI0 IRQ handler */
    IRQ_S_HANDLER 45 /* PWM1 IRQ handler */
    IRQ_S_HANDLER 46 /* HALL1 IRQ handler */
    IRQ_S_HANDLER 47 /* QEI1 IRQ handler */
    IRQ_S_HANDLER 48 /* SDP IRQ handler */
    IRQ_S_HANDLER 49 /* XPI0 IRQ handler */
    IRQ_S_HANDLER 50 /* XPI1 IRQ handler */
    IRQ_S_HANDLER 51 /* XDMA IRQ handler */
    IRQ_S_HANDLER 52 /* HDMA IRQ handler */
    IRQ_S_HANDLER 53 /* FEMC IRQ handler */
    IRQ_S_HANDLER 54 /* RNG IRQ handler */
    IRQ_S_HANDLER 55 /* I2S0 IRQ handler */
    IRQ_S_HANDLER 56 /* I2S1 IRQ handler */
    IRQ_S_HANDLER 57 /* DAO IRQ handler */
    IRQ_S_HANDLER 58 /* PDM IRQ handler */
    IRQ_S_HANDLER 59 /* FFA IRQ handler */
    IRQ_S_HANDLER 60 /* NTMR0 IRQ handler */
    IRQ_S_HANDLER 61 /* USB0 IRQ handler */
    IRQ_S_HANDLER 62 /* ENET0 IRQ handler */
    IRQ_S_HANDLER 63 /* SDXC0 IRQ handler */
    IRQ_S_HANDLER 64 /* PSEC IRQ handler */
    IRQ_S_HANDLER 65 /* PGPIO IRQ handler */
    IRQ_S_HANDLER 66 /* PWDG IRQ handler */
    IRQ_S_HANDLER 67 /* PTMR IRQ handler */
    IRQ_S_HANDLER 68 /* PUART IRQ handler */
    IRQ_S_HANDLER 69 /* FUSE IRQ handler */
    IRQ_S_HANDLER 70 /* SECMON IRQ handler */
    IRQ_S_HANDLER 71 /* RTC IRQ handler */
    IRQ_S_HANDLER 72 /* BUTN IRQ handler */
    IRQ_S_HANDLER 73 /* BGPIO IRQ handler */
    IRQ_S_HANDLER 74 /* BVIO IRQ handler */
    IRQ_S_HANDLER 75 /* BROWNOUT IRQ handler */
    IRQ_S_HANDLER 76 /* SYSCTL IRQ handler */
    IRQ_S_HANDLER 77 /* DEBUG[0] IRQ handler */
    IRQ_S_HANDLER 78 /* DEBUG[1] IRQ handler */
