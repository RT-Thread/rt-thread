/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifdef __IAR_SYSTEMS_ASM__

IRQ_HANDLER macro
    dc32 default_isr_\1
    endm

IRQ_DEFAULT_HANDLER macro
    PUBWEAK default_isr_\1
default_isr_\1
    j default_irq_handler
    endm

    SECTION `.isr_vector`:CODE:ROOT(9)
    PUBWEAK default_irq_handler
default_irq_handler
    j default_irq_handler
    IRQ_DEFAULT_HANDLER 1 /* GPIO0_A IRQ handler */
    IRQ_DEFAULT_HANDLER 2 /* GPIO0_B IRQ handler */
    IRQ_DEFAULT_HANDLER 3 /* GPIO0_C IRQ handler */
    IRQ_DEFAULT_HANDLER 4 /* GPIO0_D IRQ handler */
    IRQ_DEFAULT_HANDLER 5 /* GPIO0_X IRQ handler */
    IRQ_DEFAULT_HANDLER 6 /* GPIO0_Y IRQ handler */
    IRQ_DEFAULT_HANDLER 7 /* GPIO0_Z IRQ handler */
    IRQ_DEFAULT_HANDLER 8 /* GPIO1_A IRQ handler */
    IRQ_DEFAULT_HANDLER 9 /* GPIO1_B IRQ handler */
    IRQ_DEFAULT_HANDLER 10 /* GPIO1_C IRQ handler */
    IRQ_DEFAULT_HANDLER 11 /* GPIO1_D IRQ handler */
    IRQ_DEFAULT_HANDLER 12 /* GPIO1_X IRQ handler */
    IRQ_DEFAULT_HANDLER 13 /* GPIO1_Y IRQ handler */
    IRQ_DEFAULT_HANDLER 14 /* GPIO1_Z IRQ handler */
    IRQ_DEFAULT_HANDLER 15 /* ADC0 IRQ handler */
    IRQ_DEFAULT_HANDLER 16 /* ADC1 IRQ handler */
    IRQ_DEFAULT_HANDLER 17 /* ADC2 IRQ handler */
    IRQ_DEFAULT_HANDLER 18 /* SDFM IRQ handler */
    IRQ_DEFAULT_HANDLER 19 /* DAC0 IRQ handler */
    IRQ_DEFAULT_HANDLER 20 /* DAC1 IRQ handler */
    IRQ_DEFAULT_HANDLER 21 /* ACMP[0] IRQ handler */
    IRQ_DEFAULT_HANDLER 22 /* ACMP[1] IRQ handler */
    IRQ_DEFAULT_HANDLER 23 /* ACMP[2] IRQ handler */
    IRQ_DEFAULT_HANDLER 24 /* ACMP[3] IRQ handler */
    IRQ_DEFAULT_HANDLER 25 /* SPI0 IRQ handler */
    IRQ_DEFAULT_HANDLER 26 /* SPI1 IRQ handler */
    IRQ_DEFAULT_HANDLER 27 /* SPI2 IRQ handler */
    IRQ_DEFAULT_HANDLER 28 /* SPI3 IRQ handler */
    IRQ_DEFAULT_HANDLER 29 /* UART0 IRQ handler */
    IRQ_DEFAULT_HANDLER 30 /* UART1 IRQ handler */
    IRQ_DEFAULT_HANDLER 31 /* UART2 IRQ handler */
    IRQ_DEFAULT_HANDLER 32 /* UART3 IRQ handler */
    IRQ_DEFAULT_HANDLER 33 /* UART4 IRQ handler */
    IRQ_DEFAULT_HANDLER 34 /* UART5 IRQ handler */
    IRQ_DEFAULT_HANDLER 35 /* UART6 IRQ handler */
    IRQ_DEFAULT_HANDLER 36 /* UART7 IRQ handler */
    IRQ_DEFAULT_HANDLER 37 /* MCAN0 IRQ handler */
    IRQ_DEFAULT_HANDLER 38 /* MCAN1 IRQ handler */
    IRQ_DEFAULT_HANDLER 39 /* MCAN2 IRQ handler */
    IRQ_DEFAULT_HANDLER 40 /* MCAN3 IRQ handler */
    IRQ_DEFAULT_HANDLER 41 /* PTPC IRQ handler */
    IRQ_DEFAULT_HANDLER 42 /* WDG0 IRQ handler */
    IRQ_DEFAULT_HANDLER 43 /* WDG1 IRQ handler */
    IRQ_DEFAULT_HANDLER 44 /* TSNS IRQ handler */
    IRQ_DEFAULT_HANDLER 45 /* MBX0A IRQ handler */
    IRQ_DEFAULT_HANDLER 46 /* MBX0B IRQ handler */
    IRQ_DEFAULT_HANDLER 47 /* MBX1A IRQ handler */
    IRQ_DEFAULT_HANDLER 48 /* MBX1B IRQ handler */
    IRQ_DEFAULT_HANDLER 49 /* GPTMR0 IRQ handler */
    IRQ_DEFAULT_HANDLER 50 /* GPTMR1 IRQ handler */
    IRQ_DEFAULT_HANDLER 51 /* GPTMR2 IRQ handler */
    IRQ_DEFAULT_HANDLER 52 /* GPTMR3 IRQ handler */
    IRQ_DEFAULT_HANDLER 53 /* I2C0 IRQ handler */
    IRQ_DEFAULT_HANDLER 54 /* I2C1 IRQ handler */
    IRQ_DEFAULT_HANDLER 55 /* I2C2 IRQ handler */
    IRQ_DEFAULT_HANDLER 56 /* I2C3 IRQ handler */
    IRQ_DEFAULT_HANDLER 57 /* PWM0 IRQ handler */
    IRQ_DEFAULT_HANDLER 58 /* HALL0 IRQ handler */
    IRQ_DEFAULT_HANDLER 59 /* QEI0 IRQ handler */
    IRQ_DEFAULT_HANDLER 60 /* PWM1 IRQ handler */
    IRQ_DEFAULT_HANDLER 61 /* HALL1 IRQ handler */
    IRQ_DEFAULT_HANDLER 62 /* QEI1 IRQ handler */
    IRQ_DEFAULT_HANDLER 63 /* PWM2 IRQ handler */
    IRQ_DEFAULT_HANDLER 64 /* HALL2 IRQ handler */
    IRQ_DEFAULT_HANDLER 65 /* QEI2 IRQ handler */
    IRQ_DEFAULT_HANDLER 66 /* PWM3 IRQ handler */
    IRQ_DEFAULT_HANDLER 67 /* HALL3 IRQ handler */
    IRQ_DEFAULT_HANDLER 68 /* QEI3 IRQ handler */
    IRQ_DEFAULT_HANDLER 69 /* SDP IRQ handler */
    IRQ_DEFAULT_HANDLER 70 /* XPI0 IRQ handler */
    IRQ_DEFAULT_HANDLER 71 /* XDMA IRQ handler */
    IRQ_DEFAULT_HANDLER 72 /* HDMA IRQ handler */
    IRQ_DEFAULT_HANDLER 73 /* RNG IRQ handler */
    IRQ_DEFAULT_HANDLER 74 /* USB0 IRQ handler */
    IRQ_DEFAULT_HANDLER 75 /* PSEC IRQ handler */
    IRQ_DEFAULT_HANDLER 76 /* PGPIO IRQ handler */
    IRQ_DEFAULT_HANDLER 77 /* PWDG IRQ handler */
    IRQ_DEFAULT_HANDLER 78 /* PTMR IRQ handler */
    IRQ_DEFAULT_HANDLER 79 /* PUART IRQ handler */
    IRQ_DEFAULT_HANDLER 80 /* FUSE IRQ handler */
    IRQ_DEFAULT_HANDLER 81 /* SECMON IRQ handler */
    IRQ_DEFAULT_HANDLER 82 /* RTC IRQ handler */
    IRQ_DEFAULT_HANDLER 83 /* BUTN IRQ handler */
    IRQ_DEFAULT_HANDLER 84 /* BGPIO IRQ handler */
    IRQ_DEFAULT_HANDLER 85 /* BVIO IRQ handler */
    IRQ_DEFAULT_HANDLER 86 /* BROWNOUT IRQ handler */
    IRQ_DEFAULT_HANDLER 87 /* SYSCTL IRQ handler */
    IRQ_DEFAULT_HANDLER 88 /* DEBUG[0] IRQ handler */
    IRQ_DEFAULT_HANDLER 89 /* DEBUG[1] IRQ handler */
    IRQ_DEFAULT_HANDLER 90 /* LIN0 IRQ handler */
    IRQ_DEFAULT_HANDLER 91 /* LIN1 IRQ handler */
    IRQ_DEFAULT_HANDLER 92 /* LIN2 IRQ handler */
    IRQ_DEFAULT_HANDLER 93 /* LIN3 IRQ handler */

    EXTERN irq_handler_trap
    SECTION `.vector_table`:CODE:ROOT(9)
    PUBLIC __vector_table
    DATA

__vector_table
#if (!defined(USE_NONVECTOR_MODE) || (USE_NONVECTOR_MODE == 0)) && defined(CONFIG_FREERTOS)
    dc32 freertos_risc_v_trap_handler
#else
    dc32 irq_handler_trap
#endif
    IRQ_HANDLER 1 /* GPIO0_A IRQ handler */
    IRQ_HANDLER 2 /* GPIO0_B IRQ handler */
    IRQ_HANDLER 3 /* GPIO0_C IRQ handler */
    IRQ_HANDLER 4 /* GPIO0_D IRQ handler */
    IRQ_HANDLER 5 /* GPIO0_X IRQ handler */
    IRQ_HANDLER 6 /* GPIO0_Y IRQ handler */
    IRQ_HANDLER 7 /* GPIO0_Z IRQ handler */
    IRQ_HANDLER 8 /* GPIO1_A IRQ handler */
    IRQ_HANDLER 9 /* GPIO1_B IRQ handler */
    IRQ_HANDLER 10 /* GPIO1_C IRQ handler */
    IRQ_HANDLER 11 /* GPIO1_D IRQ handler */
    IRQ_HANDLER 12 /* GPIO1_X IRQ handler */
    IRQ_HANDLER 13 /* GPIO1_Y IRQ handler */
    IRQ_HANDLER 14 /* GPIO1_Z IRQ handler */
    IRQ_HANDLER 15 /* ADC0 IRQ handler */
    IRQ_HANDLER 16 /* ADC1 IRQ handler */
    IRQ_HANDLER 17 /* ADC2 IRQ handler */
    IRQ_HANDLER 18 /* SDFM IRQ handler */
    IRQ_HANDLER 19 /* DAC0 IRQ handler */
    IRQ_HANDLER 20 /* DAC1 IRQ handler */
    IRQ_HANDLER 21 /* ACMP[0] IRQ handler */
    IRQ_HANDLER 22 /* ACMP[1] IRQ handler */
    IRQ_HANDLER 23 /* ACMP[2] IRQ handler */
    IRQ_HANDLER 24 /* ACMP[3] IRQ handler */
    IRQ_HANDLER 25 /* SPI0 IRQ handler */
    IRQ_HANDLER 26 /* SPI1 IRQ handler */
    IRQ_HANDLER 27 /* SPI2 IRQ handler */
    IRQ_HANDLER 28 /* SPI3 IRQ handler */
    IRQ_HANDLER 29 /* UART0 IRQ handler */
    IRQ_HANDLER 30 /* UART1 IRQ handler */
    IRQ_HANDLER 31 /* UART2 IRQ handler */
    IRQ_HANDLER 32 /* UART3 IRQ handler */
    IRQ_HANDLER 33 /* UART4 IRQ handler */
    IRQ_HANDLER 34 /* UART5 IRQ handler */
    IRQ_HANDLER 35 /* UART6 IRQ handler */
    IRQ_HANDLER 36 /* UART7 IRQ handler */
    IRQ_HANDLER 37 /* MCAN0 IRQ handler */
    IRQ_HANDLER 38 /* MCAN1 IRQ handler */
    IRQ_HANDLER 39 /* MCAN2 IRQ handler */
    IRQ_HANDLER 40 /* MCAN3 IRQ handler */
    IRQ_HANDLER 41 /* PTPC IRQ handler */
    IRQ_HANDLER 42 /* WDG0 IRQ handler */
    IRQ_HANDLER 43 /* WDG1 IRQ handler */
    IRQ_HANDLER 44 /* TSNS IRQ handler */
    IRQ_HANDLER 45 /* MBX0A IRQ handler */
    IRQ_HANDLER 46 /* MBX0B IRQ handler */
    IRQ_HANDLER 47 /* MBX1A IRQ handler */
    IRQ_HANDLER 48 /* MBX1B IRQ handler */
    IRQ_HANDLER 49 /* GPTMR0 IRQ handler */
    IRQ_HANDLER 50 /* GPTMR1 IRQ handler */
    IRQ_HANDLER 51 /* GPTMR2 IRQ handler */
    IRQ_HANDLER 52 /* GPTMR3 IRQ handler */
    IRQ_HANDLER 53 /* I2C0 IRQ handler */
    IRQ_HANDLER 54 /* I2C1 IRQ handler */
    IRQ_HANDLER 55 /* I2C2 IRQ handler */
    IRQ_HANDLER 56 /* I2C3 IRQ handler */
    IRQ_HANDLER 57 /* PWM0 IRQ handler */
    IRQ_HANDLER 58 /* HALL0 IRQ handler */
    IRQ_HANDLER 59 /* QEI0 IRQ handler */
    IRQ_HANDLER 60 /* PWM1 IRQ handler */
    IRQ_HANDLER 61 /* HALL1 IRQ handler */
    IRQ_HANDLER 62 /* QEI1 IRQ handler */
    IRQ_HANDLER 63 /* PWM2 IRQ handler */
    IRQ_HANDLER 64 /* HALL2 IRQ handler */
    IRQ_HANDLER 65 /* QEI2 IRQ handler */
    IRQ_HANDLER 66 /* PWM3 IRQ handler */
    IRQ_HANDLER 67 /* HALL3 IRQ handler */
    IRQ_HANDLER 68 /* QEI3 IRQ handler */
    IRQ_HANDLER 69 /* SDP IRQ handler */
    IRQ_HANDLER 70 /* XPI0 IRQ handler */
    IRQ_HANDLER 71 /* XDMA IRQ handler */
    IRQ_HANDLER 72 /* HDMA IRQ handler */
    IRQ_HANDLER 73 /* RNG IRQ handler */
    IRQ_HANDLER 74 /* USB0 IRQ handler */
    IRQ_HANDLER 75 /* PSEC IRQ handler */
    IRQ_HANDLER 76 /* PGPIO IRQ handler */
    IRQ_HANDLER 77 /* PWDG IRQ handler */
    IRQ_HANDLER 78 /* PTMR IRQ handler */
    IRQ_HANDLER 79 /* PUART IRQ handler */
    IRQ_HANDLER 80 /* FUSE IRQ handler */
    IRQ_HANDLER 81 /* SECMON IRQ handler */
    IRQ_HANDLER 82 /* RTC IRQ handler */
    IRQ_HANDLER 83 /* BUTN IRQ handler */
    IRQ_HANDLER 84 /* BGPIO IRQ handler */
    IRQ_HANDLER 85 /* BVIO IRQ handler */
    IRQ_HANDLER 86 /* BROWNOUT IRQ handler */
    IRQ_HANDLER 87 /* SYSCTL IRQ handler */
    IRQ_HANDLER 88 /* DEBUG[0] IRQ handler */
    IRQ_HANDLER 89 /* DEBUG[1] IRQ handler */
    IRQ_HANDLER 90 /* LIN0 IRQ handler */
    IRQ_HANDLER 91 /* LIN1 IRQ handler */
    IRQ_HANDLER 92 /* LIN2 IRQ handler */
    IRQ_HANDLER 93 /* LIN3 IRQ handler */

#else

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

#if (!defined(USE_NONVECTOR_MODE) || (USE_NONVECTOR_MODE == 0)) && defined(CONFIG_FREERTOS)
    .set default_isr_trap, freertos_risc_v_trap_handler
#else
    .set default_isr_trap, irq_handler_trap
#endif

__vector_table:
    .weak default_isr_trap
    .long default_isr_trap
    IRQ_HANDLER 1 /* GPIO0_A IRQ handler */
    IRQ_HANDLER 2 /* GPIO0_B IRQ handler */
    IRQ_HANDLER 3 /* GPIO0_C IRQ handler */
    IRQ_HANDLER 4 /* GPIO0_D IRQ handler */
    IRQ_HANDLER 5 /* GPIO0_X IRQ handler */
    IRQ_HANDLER 6 /* GPIO0_Y IRQ handler */
    IRQ_HANDLER 7 /* GPIO0_Z IRQ handler */
    IRQ_HANDLER 8 /* GPIO1_A IRQ handler */
    IRQ_HANDLER 9 /* GPIO1_B IRQ handler */
    IRQ_HANDLER 10 /* GPIO1_C IRQ handler */
    IRQ_HANDLER 11 /* GPIO1_D IRQ handler */
    IRQ_HANDLER 12 /* GPIO1_X IRQ handler */
    IRQ_HANDLER 13 /* GPIO1_Y IRQ handler */
    IRQ_HANDLER 14 /* GPIO1_Z IRQ handler */
    IRQ_HANDLER 15 /* ADC0 IRQ handler */
    IRQ_HANDLER 16 /* ADC1 IRQ handler */
    IRQ_HANDLER 17 /* ADC2 IRQ handler */
    IRQ_HANDLER 18 /* SDFM IRQ handler */
    IRQ_HANDLER 19 /* DAC0 IRQ handler */
    IRQ_HANDLER 20 /* DAC1 IRQ handler */
    IRQ_HANDLER 21 /* ACMP[0] IRQ handler */
    IRQ_HANDLER 22 /* ACMP[1] IRQ handler */
    IRQ_HANDLER 23 /* ACMP[2] IRQ handler */
    IRQ_HANDLER 24 /* ACMP[3] IRQ handler */
    IRQ_HANDLER 25 /* SPI0 IRQ handler */
    IRQ_HANDLER 26 /* SPI1 IRQ handler */
    IRQ_HANDLER 27 /* SPI2 IRQ handler */
    IRQ_HANDLER 28 /* SPI3 IRQ handler */
    IRQ_HANDLER 29 /* UART0 IRQ handler */
    IRQ_HANDLER 30 /* UART1 IRQ handler */
    IRQ_HANDLER 31 /* UART2 IRQ handler */
    IRQ_HANDLER 32 /* UART3 IRQ handler */
    IRQ_HANDLER 33 /* UART4 IRQ handler */
    IRQ_HANDLER 34 /* UART5 IRQ handler */
    IRQ_HANDLER 35 /* UART6 IRQ handler */
    IRQ_HANDLER 36 /* UART7 IRQ handler */
    IRQ_HANDLER 37 /* MCAN0 IRQ handler */
    IRQ_HANDLER 38 /* MCAN1 IRQ handler */
    IRQ_HANDLER 39 /* MCAN2 IRQ handler */
    IRQ_HANDLER 40 /* MCAN3 IRQ handler */
    IRQ_HANDLER 41 /* PTPC IRQ handler */
    IRQ_HANDLER 42 /* WDG0 IRQ handler */
    IRQ_HANDLER 43 /* WDG1 IRQ handler */
    IRQ_HANDLER 44 /* TSNS IRQ handler */
    IRQ_HANDLER 45 /* MBX0A IRQ handler */
    IRQ_HANDLER 46 /* MBX0B IRQ handler */
    IRQ_HANDLER 47 /* MBX1A IRQ handler */
    IRQ_HANDLER 48 /* MBX1B IRQ handler */
    IRQ_HANDLER 49 /* GPTMR0 IRQ handler */
    IRQ_HANDLER 50 /* GPTMR1 IRQ handler */
    IRQ_HANDLER 51 /* GPTMR2 IRQ handler */
    IRQ_HANDLER 52 /* GPTMR3 IRQ handler */
    IRQ_HANDLER 53 /* I2C0 IRQ handler */
    IRQ_HANDLER 54 /* I2C1 IRQ handler */
    IRQ_HANDLER 55 /* I2C2 IRQ handler */
    IRQ_HANDLER 56 /* I2C3 IRQ handler */
    IRQ_HANDLER 57 /* PWM0 IRQ handler */
    IRQ_HANDLER 58 /* HALL0 IRQ handler */
    IRQ_HANDLER 59 /* QEI0 IRQ handler */
    IRQ_HANDLER 60 /* PWM1 IRQ handler */
    IRQ_HANDLER 61 /* HALL1 IRQ handler */
    IRQ_HANDLER 62 /* QEI1 IRQ handler */
    IRQ_HANDLER 63 /* PWM2 IRQ handler */
    IRQ_HANDLER 64 /* HALL2 IRQ handler */
    IRQ_HANDLER 65 /* QEI2 IRQ handler */
    IRQ_HANDLER 66 /* PWM3 IRQ handler */
    IRQ_HANDLER 67 /* HALL3 IRQ handler */
    IRQ_HANDLER 68 /* QEI3 IRQ handler */
    IRQ_HANDLER 69 /* SDP IRQ handler */
    IRQ_HANDLER 70 /* XPI0 IRQ handler */
    IRQ_HANDLER 71 /* XDMA IRQ handler */
    IRQ_HANDLER 72 /* HDMA IRQ handler */
    IRQ_HANDLER 73 /* RNG IRQ handler */
    IRQ_HANDLER 74 /* USB0 IRQ handler */
    IRQ_HANDLER 75 /* PSEC IRQ handler */
    IRQ_HANDLER 76 /* PGPIO IRQ handler */
    IRQ_HANDLER 77 /* PWDG IRQ handler */
    IRQ_HANDLER 78 /* PTMR IRQ handler */
    IRQ_HANDLER 79 /* PUART IRQ handler */
    IRQ_HANDLER 80 /* FUSE IRQ handler */
    IRQ_HANDLER 81 /* SECMON IRQ handler */
    IRQ_HANDLER 82 /* RTC IRQ handler */
    IRQ_HANDLER 83 /* BUTN IRQ handler */
    IRQ_HANDLER 84 /* BGPIO IRQ handler */
    IRQ_HANDLER 85 /* BVIO IRQ handler */
    IRQ_HANDLER 86 /* BROWNOUT IRQ handler */
    IRQ_HANDLER 87 /* SYSCTL IRQ handler */
    IRQ_HANDLER 88 /* DEBUG[0] IRQ handler */
    IRQ_HANDLER 89 /* DEBUG[1] IRQ handler */
    IRQ_HANDLER 90 /* LIN0 IRQ handler */
    IRQ_HANDLER 91 /* LIN1 IRQ handler */
    IRQ_HANDLER 92 /* LIN2 IRQ handler */
    IRQ_HANDLER 93 /* LIN3 IRQ handler */

#endif

#ifdef __IAR_SYSTEMS_ASM__

IRQ_S_HANDLER macro
    dc32 default_isr_s_\1
    endm

IRQ_DEFAULT_S_HANDLER macro
    PUBWEAK default_isr_s_\1
default_isr_s_\1
    j default_irq_s_handler
    endm

    SECTION `.isr_s_vector`:CODE:ROOT(9)
    PUBWEAK default_irq_s_handler
default_irq_s_handler
    j default_irq_s_handler
    IRQ_DEFAULT_S_HANDLER 1 /* GPIO0_A IRQ handler */
    IRQ_DEFAULT_S_HANDLER 2 /* GPIO0_B IRQ handler */
    IRQ_DEFAULT_S_HANDLER 3 /* GPIO0_C IRQ handler */
    IRQ_DEFAULT_S_HANDLER 4 /* GPIO0_D IRQ handler */
    IRQ_DEFAULT_S_HANDLER 5 /* GPIO0_X IRQ handler */
    IRQ_DEFAULT_S_HANDLER 6 /* GPIO0_Y IRQ handler */
    IRQ_DEFAULT_S_HANDLER 7 /* GPIO0_Z IRQ handler */
    IRQ_DEFAULT_S_HANDLER 8 /* GPIO1_A IRQ handler */
    IRQ_DEFAULT_S_HANDLER 9 /* GPIO1_B IRQ handler */
    IRQ_DEFAULT_S_HANDLER 10 /* GPIO1_C IRQ handler */
    IRQ_DEFAULT_S_HANDLER 11 /* GPIO1_D IRQ handler */
    IRQ_DEFAULT_S_HANDLER 12 /* GPIO1_X IRQ handler */
    IRQ_DEFAULT_S_HANDLER 13 /* GPIO1_Y IRQ handler */
    IRQ_DEFAULT_S_HANDLER 14 /* GPIO1_Z IRQ handler */
    IRQ_DEFAULT_S_HANDLER 15 /* ADC0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 16 /* ADC1 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 17 /* ADC2 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 18 /* SDFM IRQ handler */
    IRQ_DEFAULT_S_HANDLER 19 /* DAC0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 20 /* DAC1 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 21 /* ACMP[0] IRQ handler */
    IRQ_DEFAULT_S_HANDLER 22 /* ACMP[1] IRQ handler */
    IRQ_DEFAULT_S_HANDLER 23 /* ACMP[2] IRQ handler */
    IRQ_DEFAULT_S_HANDLER 24 /* ACMP[3] IRQ handler */
    IRQ_DEFAULT_S_HANDLER 25 /* SPI0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 26 /* SPI1 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 27 /* SPI2 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 28 /* SPI3 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 29 /* UART0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 30 /* UART1 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 31 /* UART2 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 32 /* UART3 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 33 /* UART4 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 34 /* UART5 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 35 /* UART6 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 36 /* UART7 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 37 /* MCAN0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 38 /* MCAN1 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 39 /* MCAN2 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 40 /* MCAN3 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 41 /* PTPC IRQ handler */
    IRQ_DEFAULT_S_HANDLER 42 /* WDG0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 43 /* WDG1 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 44 /* TSNS IRQ handler */
    IRQ_DEFAULT_S_HANDLER 45 /* MBX0A IRQ handler */
    IRQ_DEFAULT_S_HANDLER 46 /* MBX0B IRQ handler */
    IRQ_DEFAULT_S_HANDLER 47 /* MBX1A IRQ handler */
    IRQ_DEFAULT_S_HANDLER 48 /* MBX1B IRQ handler */
    IRQ_DEFAULT_S_HANDLER 49 /* GPTMR0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 50 /* GPTMR1 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 51 /* GPTMR2 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 52 /* GPTMR3 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 53 /* I2C0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 54 /* I2C1 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 55 /* I2C2 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 56 /* I2C3 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 57 /* PWM0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 58 /* HALL0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 59 /* QEI0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 60 /* PWM1 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 61 /* HALL1 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 62 /* QEI1 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 63 /* PWM2 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 64 /* HALL2 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 65 /* QEI2 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 66 /* PWM3 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 67 /* HALL3 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 68 /* QEI3 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 69 /* SDP IRQ handler */
    IRQ_DEFAULT_S_HANDLER 70 /* XPI0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 71 /* XDMA IRQ handler */
    IRQ_DEFAULT_S_HANDLER 72 /* HDMA IRQ handler */
    IRQ_DEFAULT_S_HANDLER 73 /* RNG IRQ handler */
    IRQ_DEFAULT_S_HANDLER 74 /* USB0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 75 /* PSEC IRQ handler */
    IRQ_DEFAULT_S_HANDLER 76 /* PGPIO IRQ handler */
    IRQ_DEFAULT_S_HANDLER 77 /* PWDG IRQ handler */
    IRQ_DEFAULT_S_HANDLER 78 /* PTMR IRQ handler */
    IRQ_DEFAULT_S_HANDLER 79 /* PUART IRQ handler */
    IRQ_DEFAULT_S_HANDLER 80 /* FUSE IRQ handler */
    IRQ_DEFAULT_S_HANDLER 81 /* SECMON IRQ handler */
    IRQ_DEFAULT_S_HANDLER 82 /* RTC IRQ handler */
    IRQ_DEFAULT_S_HANDLER 83 /* BUTN IRQ handler */
    IRQ_DEFAULT_S_HANDLER 84 /* BGPIO IRQ handler */
    IRQ_DEFAULT_S_HANDLER 85 /* BVIO IRQ handler */
    IRQ_DEFAULT_S_HANDLER 86 /* BROWNOUT IRQ handler */
    IRQ_DEFAULT_S_HANDLER 87 /* SYSCTL IRQ handler */
    IRQ_DEFAULT_S_HANDLER 88 /* DEBUG[0] IRQ handler */
    IRQ_DEFAULT_S_HANDLER 89 /* DEBUG[1] IRQ handler */
    IRQ_DEFAULT_S_HANDLER 90 /* LIN0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 91 /* LIN1 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 92 /* LIN2 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 93 /* LIN3 IRQ handler */

    EXTERN irq_handler_s_trap
    SECTION `.vector_s_table`:CODE:ROOT(9)
    PUBLIC __vector_s_table
    DATA

__vector_s_table
#if (!defined(USE_NONVECTOR_MODE) || (USE_NONVECTOR_MODE == 0)) && defined(CONFIG_FREERTOS)
    dc32 freertos_risc_v_trap_handler
#else
    dc32 irq_handler_s_trap
#endif
    IRQ_S_HANDLER 1 /* GPIO0_A IRQ handler */
    IRQ_S_HANDLER 2 /* GPIO0_B IRQ handler */
    IRQ_S_HANDLER 3 /* GPIO0_C IRQ handler */
    IRQ_S_HANDLER 4 /* GPIO0_D IRQ handler */
    IRQ_S_HANDLER 5 /* GPIO0_X IRQ handler */
    IRQ_S_HANDLER 6 /* GPIO0_Y IRQ handler */
    IRQ_S_HANDLER 7 /* GPIO0_Z IRQ handler */
    IRQ_S_HANDLER 8 /* GPIO1_A IRQ handler */
    IRQ_S_HANDLER 9 /* GPIO1_B IRQ handler */
    IRQ_S_HANDLER 10 /* GPIO1_C IRQ handler */
    IRQ_S_HANDLER 11 /* GPIO1_D IRQ handler */
    IRQ_S_HANDLER 12 /* GPIO1_X IRQ handler */
    IRQ_S_HANDLER 13 /* GPIO1_Y IRQ handler */
    IRQ_S_HANDLER 14 /* GPIO1_Z IRQ handler */
    IRQ_S_HANDLER 15 /* ADC0 IRQ handler */
    IRQ_S_HANDLER 16 /* ADC1 IRQ handler */
    IRQ_S_HANDLER 17 /* ADC2 IRQ handler */
    IRQ_S_HANDLER 18 /* SDFM IRQ handler */
    IRQ_S_HANDLER 19 /* DAC0 IRQ handler */
    IRQ_S_HANDLER 20 /* DAC1 IRQ handler */
    IRQ_S_HANDLER 21 /* ACMP[0] IRQ handler */
    IRQ_S_HANDLER 22 /* ACMP[1] IRQ handler */
    IRQ_S_HANDLER 23 /* ACMP[2] IRQ handler */
    IRQ_S_HANDLER 24 /* ACMP[3] IRQ handler */
    IRQ_S_HANDLER 25 /* SPI0 IRQ handler */
    IRQ_S_HANDLER 26 /* SPI1 IRQ handler */
    IRQ_S_HANDLER 27 /* SPI2 IRQ handler */
    IRQ_S_HANDLER 28 /* SPI3 IRQ handler */
    IRQ_S_HANDLER 29 /* UART0 IRQ handler */
    IRQ_S_HANDLER 30 /* UART1 IRQ handler */
    IRQ_S_HANDLER 31 /* UART2 IRQ handler */
    IRQ_S_HANDLER 32 /* UART3 IRQ handler */
    IRQ_S_HANDLER 33 /* UART4 IRQ handler */
    IRQ_S_HANDLER 34 /* UART5 IRQ handler */
    IRQ_S_HANDLER 35 /* UART6 IRQ handler */
    IRQ_S_HANDLER 36 /* UART7 IRQ handler */
    IRQ_S_HANDLER 37 /* MCAN0 IRQ handler */
    IRQ_S_HANDLER 38 /* MCAN1 IRQ handler */
    IRQ_S_HANDLER 39 /* MCAN2 IRQ handler */
    IRQ_S_HANDLER 40 /* MCAN3 IRQ handler */
    IRQ_S_HANDLER 41 /* PTPC IRQ handler */
    IRQ_S_HANDLER 42 /* WDG0 IRQ handler */
    IRQ_S_HANDLER 43 /* WDG1 IRQ handler */
    IRQ_S_HANDLER 44 /* TSNS IRQ handler */
    IRQ_S_HANDLER 45 /* MBX0A IRQ handler */
    IRQ_S_HANDLER 46 /* MBX0B IRQ handler */
    IRQ_S_HANDLER 47 /* MBX1A IRQ handler */
    IRQ_S_HANDLER 48 /* MBX1B IRQ handler */
    IRQ_S_HANDLER 49 /* GPTMR0 IRQ handler */
    IRQ_S_HANDLER 50 /* GPTMR1 IRQ handler */
    IRQ_S_HANDLER 51 /* GPTMR2 IRQ handler */
    IRQ_S_HANDLER 52 /* GPTMR3 IRQ handler */
    IRQ_S_HANDLER 53 /* I2C0 IRQ handler */
    IRQ_S_HANDLER 54 /* I2C1 IRQ handler */
    IRQ_S_HANDLER 55 /* I2C2 IRQ handler */
    IRQ_S_HANDLER 56 /* I2C3 IRQ handler */
    IRQ_S_HANDLER 57 /* PWM0 IRQ handler */
    IRQ_S_HANDLER 58 /* HALL0 IRQ handler */
    IRQ_S_HANDLER 59 /* QEI0 IRQ handler */
    IRQ_S_HANDLER 60 /* PWM1 IRQ handler */
    IRQ_S_HANDLER 61 /* HALL1 IRQ handler */
    IRQ_S_HANDLER 62 /* QEI1 IRQ handler */
    IRQ_S_HANDLER 63 /* PWM2 IRQ handler */
    IRQ_S_HANDLER 64 /* HALL2 IRQ handler */
    IRQ_S_HANDLER 65 /* QEI2 IRQ handler */
    IRQ_S_HANDLER 66 /* PWM3 IRQ handler */
    IRQ_S_HANDLER 67 /* HALL3 IRQ handler */
    IRQ_S_HANDLER 68 /* QEI3 IRQ handler */
    IRQ_S_HANDLER 69 /* SDP IRQ handler */
    IRQ_S_HANDLER 70 /* XPI0 IRQ handler */
    IRQ_S_HANDLER 71 /* XDMA IRQ handler */
    IRQ_S_HANDLER 72 /* HDMA IRQ handler */
    IRQ_S_HANDLER 73 /* RNG IRQ handler */
    IRQ_S_HANDLER 74 /* USB0 IRQ handler */
    IRQ_S_HANDLER 75 /* PSEC IRQ handler */
    IRQ_S_HANDLER 76 /* PGPIO IRQ handler */
    IRQ_S_HANDLER 77 /* PWDG IRQ handler */
    IRQ_S_HANDLER 78 /* PTMR IRQ handler */
    IRQ_S_HANDLER 79 /* PUART IRQ handler */
    IRQ_S_HANDLER 80 /* FUSE IRQ handler */
    IRQ_S_HANDLER 81 /* SECMON IRQ handler */
    IRQ_S_HANDLER 82 /* RTC IRQ handler */
    IRQ_S_HANDLER 83 /* BUTN IRQ handler */
    IRQ_S_HANDLER 84 /* BGPIO IRQ handler */
    IRQ_S_HANDLER 85 /* BVIO IRQ handler */
    IRQ_S_HANDLER 86 /* BROWNOUT IRQ handler */
    IRQ_S_HANDLER 87 /* SYSCTL IRQ handler */
    IRQ_S_HANDLER 88 /* DEBUG[0] IRQ handler */
    IRQ_S_HANDLER 89 /* DEBUG[1] IRQ handler */
    IRQ_S_HANDLER 90 /* LIN0 IRQ handler */
    IRQ_S_HANDLER 91 /* LIN1 IRQ handler */
    IRQ_S_HANDLER 92 /* LIN2 IRQ handler */
    IRQ_S_HANDLER 93 /* LIN3 IRQ handler */

#else

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

#if (!defined(USE_NONVECTOR_MODE) || (USE_NONVECTOR_MODE == 0)) && defined(CONFIG_FREERTOS)
    .set default_isr_s_trap, freertos_risc_v_trap_handler
#else
    .set default_isr_s_trap, irq_handler_s_trap
#endif

__vector_s_table:
    .weak default_isr_s_trap
    .long default_isr_s_trap
    IRQ_S_HANDLER 1 /* GPIO0_A IRQ handler */
    IRQ_S_HANDLER 2 /* GPIO0_B IRQ handler */
    IRQ_S_HANDLER 3 /* GPIO0_C IRQ handler */
    IRQ_S_HANDLER 4 /* GPIO0_D IRQ handler */
    IRQ_S_HANDLER 5 /* GPIO0_X IRQ handler */
    IRQ_S_HANDLER 6 /* GPIO0_Y IRQ handler */
    IRQ_S_HANDLER 7 /* GPIO0_Z IRQ handler */
    IRQ_S_HANDLER 8 /* GPIO1_A IRQ handler */
    IRQ_S_HANDLER 9 /* GPIO1_B IRQ handler */
    IRQ_S_HANDLER 10 /* GPIO1_C IRQ handler */
    IRQ_S_HANDLER 11 /* GPIO1_D IRQ handler */
    IRQ_S_HANDLER 12 /* GPIO1_X IRQ handler */
    IRQ_S_HANDLER 13 /* GPIO1_Y IRQ handler */
    IRQ_S_HANDLER 14 /* GPIO1_Z IRQ handler */
    IRQ_S_HANDLER 15 /* ADC0 IRQ handler */
    IRQ_S_HANDLER 16 /* ADC1 IRQ handler */
    IRQ_S_HANDLER 17 /* ADC2 IRQ handler */
    IRQ_S_HANDLER 18 /* SDFM IRQ handler */
    IRQ_S_HANDLER 19 /* DAC0 IRQ handler */
    IRQ_S_HANDLER 20 /* DAC1 IRQ handler */
    IRQ_S_HANDLER 21 /* ACMP[0] IRQ handler */
    IRQ_S_HANDLER 22 /* ACMP[1] IRQ handler */
    IRQ_S_HANDLER 23 /* ACMP[2] IRQ handler */
    IRQ_S_HANDLER 24 /* ACMP[3] IRQ handler */
    IRQ_S_HANDLER 25 /* SPI0 IRQ handler */
    IRQ_S_HANDLER 26 /* SPI1 IRQ handler */
    IRQ_S_HANDLER 27 /* SPI2 IRQ handler */
    IRQ_S_HANDLER 28 /* SPI3 IRQ handler */
    IRQ_S_HANDLER 29 /* UART0 IRQ handler */
    IRQ_S_HANDLER 30 /* UART1 IRQ handler */
    IRQ_S_HANDLER 31 /* UART2 IRQ handler */
    IRQ_S_HANDLER 32 /* UART3 IRQ handler */
    IRQ_S_HANDLER 33 /* UART4 IRQ handler */
    IRQ_S_HANDLER 34 /* UART5 IRQ handler */
    IRQ_S_HANDLER 35 /* UART6 IRQ handler */
    IRQ_S_HANDLER 36 /* UART7 IRQ handler */
    IRQ_S_HANDLER 37 /* MCAN0 IRQ handler */
    IRQ_S_HANDLER 38 /* MCAN1 IRQ handler */
    IRQ_S_HANDLER 39 /* MCAN2 IRQ handler */
    IRQ_S_HANDLER 40 /* MCAN3 IRQ handler */
    IRQ_S_HANDLER 41 /* PTPC IRQ handler */
    IRQ_S_HANDLER 42 /* WDG0 IRQ handler */
    IRQ_S_HANDLER 43 /* WDG1 IRQ handler */
    IRQ_S_HANDLER 44 /* TSNS IRQ handler */
    IRQ_S_HANDLER 45 /* MBX0A IRQ handler */
    IRQ_S_HANDLER 46 /* MBX0B IRQ handler */
    IRQ_S_HANDLER 47 /* MBX1A IRQ handler */
    IRQ_S_HANDLER 48 /* MBX1B IRQ handler */
    IRQ_S_HANDLER 49 /* GPTMR0 IRQ handler */
    IRQ_S_HANDLER 50 /* GPTMR1 IRQ handler */
    IRQ_S_HANDLER 51 /* GPTMR2 IRQ handler */
    IRQ_S_HANDLER 52 /* GPTMR3 IRQ handler */
    IRQ_S_HANDLER 53 /* I2C0 IRQ handler */
    IRQ_S_HANDLER 54 /* I2C1 IRQ handler */
    IRQ_S_HANDLER 55 /* I2C2 IRQ handler */
    IRQ_S_HANDLER 56 /* I2C3 IRQ handler */
    IRQ_S_HANDLER 57 /* PWM0 IRQ handler */
    IRQ_S_HANDLER 58 /* HALL0 IRQ handler */
    IRQ_S_HANDLER 59 /* QEI0 IRQ handler */
    IRQ_S_HANDLER 60 /* PWM1 IRQ handler */
    IRQ_S_HANDLER 61 /* HALL1 IRQ handler */
    IRQ_S_HANDLER 62 /* QEI1 IRQ handler */
    IRQ_S_HANDLER 63 /* PWM2 IRQ handler */
    IRQ_S_HANDLER 64 /* HALL2 IRQ handler */
    IRQ_S_HANDLER 65 /* QEI2 IRQ handler */
    IRQ_S_HANDLER 66 /* PWM3 IRQ handler */
    IRQ_S_HANDLER 67 /* HALL3 IRQ handler */
    IRQ_S_HANDLER 68 /* QEI3 IRQ handler */
    IRQ_S_HANDLER 69 /* SDP IRQ handler */
    IRQ_S_HANDLER 70 /* XPI0 IRQ handler */
    IRQ_S_HANDLER 71 /* XDMA IRQ handler */
    IRQ_S_HANDLER 72 /* HDMA IRQ handler */
    IRQ_S_HANDLER 73 /* RNG IRQ handler */
    IRQ_S_HANDLER 74 /* USB0 IRQ handler */
    IRQ_S_HANDLER 75 /* PSEC IRQ handler */
    IRQ_S_HANDLER 76 /* PGPIO IRQ handler */
    IRQ_S_HANDLER 77 /* PWDG IRQ handler */
    IRQ_S_HANDLER 78 /* PTMR IRQ handler */
    IRQ_S_HANDLER 79 /* PUART IRQ handler */
    IRQ_S_HANDLER 80 /* FUSE IRQ handler */
    IRQ_S_HANDLER 81 /* SECMON IRQ handler */
    IRQ_S_HANDLER 82 /* RTC IRQ handler */
    IRQ_S_HANDLER 83 /* BUTN IRQ handler */
    IRQ_S_HANDLER 84 /* BGPIO IRQ handler */
    IRQ_S_HANDLER 85 /* BVIO IRQ handler */
    IRQ_S_HANDLER 86 /* BROWNOUT IRQ handler */
    IRQ_S_HANDLER 87 /* SYSCTL IRQ handler */
    IRQ_S_HANDLER 88 /* DEBUG[0] IRQ handler */
    IRQ_S_HANDLER 89 /* DEBUG[1] IRQ handler */
    IRQ_S_HANDLER 90 /* LIN0 IRQ handler */
    IRQ_S_HANDLER 91 /* LIN1 IRQ handler */
    IRQ_S_HANDLER 92 /* LIN2 IRQ handler */
    IRQ_S_HANDLER 93 /* LIN3 IRQ handler */

#endif
