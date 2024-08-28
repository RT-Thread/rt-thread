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

    SECTION `.isr_vector`:CODE:ROOT(10)
    PUBWEAK default_irq_handler
default_irq_handler
    j default_irq_handler
    IRQ_DEFAULT_HANDLER 1 /* GPIO0_A IRQ handler */
    IRQ_DEFAULT_HANDLER 2 /* GPIO0_B IRQ handler */
    IRQ_DEFAULT_HANDLER 3 /* GPIO0_C IRQ handler */
    IRQ_DEFAULT_HANDLER 4 /* GPIO0_D IRQ handler */
    IRQ_DEFAULT_HANDLER 5 /* GPIO0_E IRQ handler */
    IRQ_DEFAULT_HANDLER 6 /* GPIO0_F IRQ handler */
    IRQ_DEFAULT_HANDLER 7 /* GPIO0_V IRQ handler */
    IRQ_DEFAULT_HANDLER 8 /* GPIO0_W IRQ handler */
    IRQ_DEFAULT_HANDLER 9 /* GPIO0_X IRQ handler */
    IRQ_DEFAULT_HANDLER 10 /* GPIO0_Y IRQ handler */
    IRQ_DEFAULT_HANDLER 11 /* GPIO0_Z IRQ handler */
    IRQ_DEFAULT_HANDLER 12 /* GPIO1_A IRQ handler */
    IRQ_DEFAULT_HANDLER 13 /* GPIO1_B IRQ handler */
    IRQ_DEFAULT_HANDLER 14 /* GPIO1_C IRQ handler */
    IRQ_DEFAULT_HANDLER 15 /* GPIO1_D IRQ handler */
    IRQ_DEFAULT_HANDLER 16 /* GPIO1_E IRQ handler */
    IRQ_DEFAULT_HANDLER 17 /* GPIO1_F IRQ handler */
    IRQ_DEFAULT_HANDLER 18 /* GPIO1_V IRQ handler */
    IRQ_DEFAULT_HANDLER 19 /* GPIO1_W IRQ handler */
    IRQ_DEFAULT_HANDLER 20 /* GPIO1_X IRQ handler */
    IRQ_DEFAULT_HANDLER 21 /* GPIO1_Y IRQ handler */
    IRQ_DEFAULT_HANDLER 22 /* GPIO1_Z IRQ handler */
    IRQ_DEFAULT_HANDLER 23 /* GPTMR0 IRQ handler */
    IRQ_DEFAULT_HANDLER 24 /* GPTMR1 IRQ handler */
    IRQ_DEFAULT_HANDLER 25 /* GPTMR2 IRQ handler */
    IRQ_DEFAULT_HANDLER 26 /* GPTMR3 IRQ handler */
    IRQ_DEFAULT_HANDLER 27 /* GPTMR4 IRQ handler */
    IRQ_DEFAULT_HANDLER 28 /* GPTMR5 IRQ handler */
    IRQ_DEFAULT_HANDLER 29 /* GPTMR6 IRQ handler */
    IRQ_DEFAULT_HANDLER 30 /* GPTMR7 IRQ handler */
    IRQ_DEFAULT_HANDLER 31 /* UART0 IRQ handler */
    IRQ_DEFAULT_HANDLER 32 /* UART1 IRQ handler */
    IRQ_DEFAULT_HANDLER 33 /* UART2 IRQ handler */
    IRQ_DEFAULT_HANDLER 34 /* UART3 IRQ handler */
    IRQ_DEFAULT_HANDLER 35 /* UART4 IRQ handler */
    IRQ_DEFAULT_HANDLER 36 /* UART5 IRQ handler */
    IRQ_DEFAULT_HANDLER 37 /* UART6 IRQ handler */
    IRQ_DEFAULT_HANDLER 38 /* UART7 IRQ handler */
    IRQ_DEFAULT_HANDLER 39 /* I2C0 IRQ handler */
    IRQ_DEFAULT_HANDLER 40 /* I2C1 IRQ handler */
    IRQ_DEFAULT_HANDLER 41 /* I2C2 IRQ handler */
    IRQ_DEFAULT_HANDLER 42 /* I2C3 IRQ handler */
    IRQ_DEFAULT_HANDLER 43 /* SPI0 IRQ handler */
    IRQ_DEFAULT_HANDLER 44 /* SPI1 IRQ handler */
    IRQ_DEFAULT_HANDLER 45 /* SPI2 IRQ handler */
    IRQ_DEFAULT_HANDLER 46 /* SPI3 IRQ handler */
    IRQ_DEFAULT_HANDLER 47 /* TSNS IRQ handler */
    IRQ_DEFAULT_HANDLER 48 /* MBX0A IRQ handler */
    IRQ_DEFAULT_HANDLER 49 /* MBX0B IRQ handler */
    IRQ_DEFAULT_HANDLER 50 /* MBX1A IRQ handler */
    IRQ_DEFAULT_HANDLER 51 /* MBX1B IRQ handler */
    IRQ_DEFAULT_HANDLER 52 /* EWDG0 IRQ handler */
    IRQ_DEFAULT_HANDLER 53 /* EWDG1 IRQ handler */
    IRQ_DEFAULT_HANDLER 54 /* EWDG2 IRQ handler */
    IRQ_DEFAULT_HANDLER 55 /* EWDG3 IRQ handler */
    IRQ_DEFAULT_HANDLER 56 /* HDMA IRQ handler */
    IRQ_DEFAULT_HANDLER 57 /* LOBS IRQ handler */
    IRQ_DEFAULT_HANDLER 58 /* ADC0 IRQ handler */
    IRQ_DEFAULT_HANDLER 59 /* ADC1 IRQ handler */
    IRQ_DEFAULT_HANDLER 60 /* ADC2 IRQ handler */
    IRQ_DEFAULT_HANDLER 61 /* ADC3 IRQ handler */
    IRQ_DEFAULT_HANDLER 62 /* ACMP0[0] IRQ handler */
    IRQ_DEFAULT_HANDLER 63 /* ACMP0[1] IRQ handler */
    IRQ_DEFAULT_HANDLER 64 /* ACMP1[0] IRQ handler */
    IRQ_DEFAULT_HANDLER 65 /* ACMP1[1] IRQ handler */
    IRQ_DEFAULT_HANDLER 66 /* ACMP2[0] IRQ handler */
    IRQ_DEFAULT_HANDLER 67 /* ACMP2[1] IRQ handler */
    IRQ_DEFAULT_HANDLER 68 /* ACMP3[0] IRQ handler */
    IRQ_DEFAULT_HANDLER 69 /* ACMP3[1] IRQ handler */
    IRQ_DEFAULT_HANDLER 70 /* I2S0 IRQ handler */
    IRQ_DEFAULT_HANDLER 71 /* I2S1 IRQ handler */
    IRQ_DEFAULT_HANDLER 72 /* DAO IRQ handler */
    IRQ_DEFAULT_HANDLER 73 /* PDM IRQ handler */
    IRQ_DEFAULT_HANDLER 74 /* UART8 IRQ handler */
    IRQ_DEFAULT_HANDLER 75 /* UART9 IRQ handler */
    IRQ_DEFAULT_HANDLER 76 /* UART10 IRQ handler */
    IRQ_DEFAULT_HANDLER 77 /* UART11 IRQ handler */
    IRQ_DEFAULT_HANDLER 78 /* UART12 IRQ handler */
    IRQ_DEFAULT_HANDLER 79 /* UART13 IRQ handler */
    IRQ_DEFAULT_HANDLER 80 /* UART14 IRQ handler */
    IRQ_DEFAULT_HANDLER 81 /* UART15 IRQ handler */
    IRQ_DEFAULT_HANDLER 82 /* I2C4 IRQ handler */
    IRQ_DEFAULT_HANDLER 83 /* I2C5 IRQ handler */
    IRQ_DEFAULT_HANDLER 84 /* I2C6 IRQ handler */
    IRQ_DEFAULT_HANDLER 85 /* I2C7 IRQ handler */
    IRQ_DEFAULT_HANDLER 86 /* SPI4 IRQ handler */
    IRQ_DEFAULT_HANDLER 87 /* SPI5 IRQ handler */
    IRQ_DEFAULT_HANDLER 88 /* SPI6 IRQ handler */
    IRQ_DEFAULT_HANDLER 89 /* SPI7 IRQ handler */
    IRQ_DEFAULT_HANDLER 90 /* MCAN0 IRQ handler */
    IRQ_DEFAULT_HANDLER 91 /* MCAN1 IRQ handler */
    IRQ_DEFAULT_HANDLER 92 /* MCAN2 IRQ handler */
    IRQ_DEFAULT_HANDLER 93 /* MCAN3 IRQ handler */
    IRQ_DEFAULT_HANDLER 94 /* MCAN4 IRQ handler */
    IRQ_DEFAULT_HANDLER 95 /* MCAN5 IRQ handler */
    IRQ_DEFAULT_HANDLER 96 /* MCAN6 IRQ handler */
    IRQ_DEFAULT_HANDLER 97 /* MCAN7 IRQ handler */
    IRQ_DEFAULT_HANDLER 98 /* PTPC IRQ handler */
    IRQ_DEFAULT_HANDLER 99 /* QEI0 IRQ handler */
    IRQ_DEFAULT_HANDLER 100 /* QEI1 IRQ handler */
    IRQ_DEFAULT_HANDLER 101 /* QEI2 IRQ handler */
    IRQ_DEFAULT_HANDLER 102 /* QEI3 IRQ handler */
    IRQ_DEFAULT_HANDLER 103 /* PWM0 IRQ handler */
    IRQ_DEFAULT_HANDLER 104 /* PWM1 IRQ handler */
    IRQ_DEFAULT_HANDLER 105 /* PWM2 IRQ handler */
    IRQ_DEFAULT_HANDLER 106 /* PWM3 IRQ handler */
    IRQ_DEFAULT_HANDLER 107 /* RDC0 IRQ handler */
    IRQ_DEFAULT_HANDLER 108 /* RDC1 IRQ handler */
    IRQ_DEFAULT_HANDLER 109 /* SDM0 IRQ handler */
    IRQ_DEFAULT_HANDLER 110 /* SDM1 IRQ handler */
    IRQ_DEFAULT_HANDLER 111 /* SEI[0] IRQ handler */
    IRQ_DEFAULT_HANDLER 112 /* SEI[1] IRQ handler */
    IRQ_DEFAULT_HANDLER 113 /* SEI[2] IRQ handler */
    IRQ_DEFAULT_HANDLER 114 /* SEI[3] IRQ handler */
    IRQ_DEFAULT_HANDLER 115 /* MTG0 IRQ handler */
    IRQ_DEFAULT_HANDLER 116 /* MTG1 IRQ handler */
    IRQ_DEFAULT_HANDLER 117 /* VSC0 IRQ handler */
    IRQ_DEFAULT_HANDLER 118 /* VSC1 IRQ handler */
    IRQ_DEFAULT_HANDLER 119 /* CLC0[0] IRQ handler */
    IRQ_DEFAULT_HANDLER 120 /* CLC0[1] IRQ handler */
    IRQ_DEFAULT_HANDLER 121 /* CLC1[0] IRQ handler */
    IRQ_DEFAULT_HANDLER 122 /* CLC1[1] IRQ handler */
    IRQ_DEFAULT_HANDLER 123 /* TRGMUX0 IRQ handler */
    IRQ_DEFAULT_HANDLER 124 /* TRGMUX1 IRQ handler */
    IRQ_DEFAULT_HANDLER 125 /* ENET0 IRQ handler */
    IRQ_DEFAULT_HANDLER 126 /* NTMR0 IRQ handler */
    IRQ_DEFAULT_HANDLER 127 /* USB0 IRQ handler */
    IRQ_DEFAULT_HANDLER 128 /* TSW[0] IRQ handler */
    IRQ_DEFAULT_HANDLER 129 /* TSW[1] IRQ handler */
    IRQ_DEFAULT_HANDLER 130 /* TSW[2] IRQ handler */
    IRQ_DEFAULT_HANDLER 131 /* TSW[3] IRQ handler */
    IRQ_DEFAULT_HANDLER 132 /* TSW_PTP_EVT IRQ handler */
    IRQ_DEFAULT_HANDLER 133 /* ESC IRQ handler */
    IRQ_DEFAULT_HANDLER 134 /* ESC_SYNC0 IRQ handler */
    IRQ_DEFAULT_HANDLER 135 /* ESC_SYNC1 IRQ handler */
    IRQ_DEFAULT_HANDLER 136 /* ESC_RESET IRQ handler */
    IRQ_DEFAULT_HANDLER 137 /* XPI0 IRQ handler */
    IRQ_DEFAULT_HANDLER 138 /* FEMC IRQ handler */
    IRQ_DEFAULT_HANDLER 139 /* PPI IRQ handler */
    IRQ_DEFAULT_HANDLER 140 /* XDMA IRQ handler */
    IRQ_DEFAULT_HANDLER 141 /* FFA IRQ handler */
    IRQ_DEFAULT_HANDLER 142 /* SDP IRQ handler */
    IRQ_DEFAULT_HANDLER 143 /* RNG IRQ handler */
    IRQ_DEFAULT_HANDLER 144 /* PKA IRQ handler */
    IRQ_DEFAULT_HANDLER 145 /* PSEC IRQ handler */
    IRQ_DEFAULT_HANDLER 146 /* PGPIO IRQ handler */
    IRQ_DEFAULT_HANDLER 147 /* PEWDG IRQ handler */
    IRQ_DEFAULT_HANDLER 148 /* PTMR IRQ handler */
    IRQ_DEFAULT_HANDLER 149 /* PUART IRQ handler */
    IRQ_DEFAULT_HANDLER 150 /* FUSE IRQ handler */
    IRQ_DEFAULT_HANDLER 151 /* SECMON IRQ handler */
    IRQ_DEFAULT_HANDLER 152 /* RTC IRQ handler */
    IRQ_DEFAULT_HANDLER 153 /* PAD_WAKEUP IRQ handler */
    IRQ_DEFAULT_HANDLER 154 /* BGPIO IRQ handler */
    IRQ_DEFAULT_HANDLER 155 /* BVIO IRQ handler */
    IRQ_DEFAULT_HANDLER 156 /* BROWNOUT IRQ handler */
    IRQ_DEFAULT_HANDLER 157 /* SYSCTL IRQ handler */
    IRQ_DEFAULT_HANDLER 158 /* CPU0 IRQ handler */
    IRQ_DEFAULT_HANDLER 159 /* CPU1 IRQ handler */
    IRQ_DEFAULT_HANDLER 160 /* DEBUG0 IRQ handler */
    IRQ_DEFAULT_HANDLER 161 /* DEBUG1 IRQ handler */

    EXTERN irq_handler_trap
    SECTION `.vector_table`:CODE:ROOT(10)
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
    IRQ_HANDLER 5 /* GPIO0_E IRQ handler */
    IRQ_HANDLER 6 /* GPIO0_F IRQ handler */
    IRQ_HANDLER 7 /* GPIO0_V IRQ handler */
    IRQ_HANDLER 8 /* GPIO0_W IRQ handler */
    IRQ_HANDLER 9 /* GPIO0_X IRQ handler */
    IRQ_HANDLER 10 /* GPIO0_Y IRQ handler */
    IRQ_HANDLER 11 /* GPIO0_Z IRQ handler */
    IRQ_HANDLER 12 /* GPIO1_A IRQ handler */
    IRQ_HANDLER 13 /* GPIO1_B IRQ handler */
    IRQ_HANDLER 14 /* GPIO1_C IRQ handler */
    IRQ_HANDLER 15 /* GPIO1_D IRQ handler */
    IRQ_HANDLER 16 /* GPIO1_E IRQ handler */
    IRQ_HANDLER 17 /* GPIO1_F IRQ handler */
    IRQ_HANDLER 18 /* GPIO1_V IRQ handler */
    IRQ_HANDLER 19 /* GPIO1_W IRQ handler */
    IRQ_HANDLER 20 /* GPIO1_X IRQ handler */
    IRQ_HANDLER 21 /* GPIO1_Y IRQ handler */
    IRQ_HANDLER 22 /* GPIO1_Z IRQ handler */
    IRQ_HANDLER 23 /* GPTMR0 IRQ handler */
    IRQ_HANDLER 24 /* GPTMR1 IRQ handler */
    IRQ_HANDLER 25 /* GPTMR2 IRQ handler */
    IRQ_HANDLER 26 /* GPTMR3 IRQ handler */
    IRQ_HANDLER 27 /* GPTMR4 IRQ handler */
    IRQ_HANDLER 28 /* GPTMR5 IRQ handler */
    IRQ_HANDLER 29 /* GPTMR6 IRQ handler */
    IRQ_HANDLER 30 /* GPTMR7 IRQ handler */
    IRQ_HANDLER 31 /* UART0 IRQ handler */
    IRQ_HANDLER 32 /* UART1 IRQ handler */
    IRQ_HANDLER 33 /* UART2 IRQ handler */
    IRQ_HANDLER 34 /* UART3 IRQ handler */
    IRQ_HANDLER 35 /* UART4 IRQ handler */
    IRQ_HANDLER 36 /* UART5 IRQ handler */
    IRQ_HANDLER 37 /* UART6 IRQ handler */
    IRQ_HANDLER 38 /* UART7 IRQ handler */
    IRQ_HANDLER 39 /* I2C0 IRQ handler */
    IRQ_HANDLER 40 /* I2C1 IRQ handler */
    IRQ_HANDLER 41 /* I2C2 IRQ handler */
    IRQ_HANDLER 42 /* I2C3 IRQ handler */
    IRQ_HANDLER 43 /* SPI0 IRQ handler */
    IRQ_HANDLER 44 /* SPI1 IRQ handler */
    IRQ_HANDLER 45 /* SPI2 IRQ handler */
    IRQ_HANDLER 46 /* SPI3 IRQ handler */
    IRQ_HANDLER 47 /* TSNS IRQ handler */
    IRQ_HANDLER 48 /* MBX0A IRQ handler */
    IRQ_HANDLER 49 /* MBX0B IRQ handler */
    IRQ_HANDLER 50 /* MBX1A IRQ handler */
    IRQ_HANDLER 51 /* MBX1B IRQ handler */
    IRQ_HANDLER 52 /* EWDG0 IRQ handler */
    IRQ_HANDLER 53 /* EWDG1 IRQ handler */
    IRQ_HANDLER 54 /* EWDG2 IRQ handler */
    IRQ_HANDLER 55 /* EWDG3 IRQ handler */
    IRQ_HANDLER 56 /* HDMA IRQ handler */
    IRQ_HANDLER 57 /* LOBS IRQ handler */
    IRQ_HANDLER 58 /* ADC0 IRQ handler */
    IRQ_HANDLER 59 /* ADC1 IRQ handler */
    IRQ_HANDLER 60 /* ADC2 IRQ handler */
    IRQ_HANDLER 61 /* ADC3 IRQ handler */
    IRQ_HANDLER 62 /* ACMP0[0] IRQ handler */
    IRQ_HANDLER 63 /* ACMP0[1] IRQ handler */
    IRQ_HANDLER 64 /* ACMP1[0] IRQ handler */
    IRQ_HANDLER 65 /* ACMP1[1] IRQ handler */
    IRQ_HANDLER 66 /* ACMP2[0] IRQ handler */
    IRQ_HANDLER 67 /* ACMP2[1] IRQ handler */
    IRQ_HANDLER 68 /* ACMP3[0] IRQ handler */
    IRQ_HANDLER 69 /* ACMP3[1] IRQ handler */
    IRQ_HANDLER 70 /* I2S0 IRQ handler */
    IRQ_HANDLER 71 /* I2S1 IRQ handler */
    IRQ_HANDLER 72 /* DAO IRQ handler */
    IRQ_HANDLER 73 /* PDM IRQ handler */
    IRQ_HANDLER 74 /* UART8 IRQ handler */
    IRQ_HANDLER 75 /* UART9 IRQ handler */
    IRQ_HANDLER 76 /* UART10 IRQ handler */
    IRQ_HANDLER 77 /* UART11 IRQ handler */
    IRQ_HANDLER 78 /* UART12 IRQ handler */
    IRQ_HANDLER 79 /* UART13 IRQ handler */
    IRQ_HANDLER 80 /* UART14 IRQ handler */
    IRQ_HANDLER 81 /* UART15 IRQ handler */
    IRQ_HANDLER 82 /* I2C4 IRQ handler */
    IRQ_HANDLER 83 /* I2C5 IRQ handler */
    IRQ_HANDLER 84 /* I2C6 IRQ handler */
    IRQ_HANDLER 85 /* I2C7 IRQ handler */
    IRQ_HANDLER 86 /* SPI4 IRQ handler */
    IRQ_HANDLER 87 /* SPI5 IRQ handler */
    IRQ_HANDLER 88 /* SPI6 IRQ handler */
    IRQ_HANDLER 89 /* SPI7 IRQ handler */
    IRQ_HANDLER 90 /* MCAN0 IRQ handler */
    IRQ_HANDLER 91 /* MCAN1 IRQ handler */
    IRQ_HANDLER 92 /* MCAN2 IRQ handler */
    IRQ_HANDLER 93 /* MCAN3 IRQ handler */
    IRQ_HANDLER 94 /* MCAN4 IRQ handler */
    IRQ_HANDLER 95 /* MCAN5 IRQ handler */
    IRQ_HANDLER 96 /* MCAN6 IRQ handler */
    IRQ_HANDLER 97 /* MCAN7 IRQ handler */
    IRQ_HANDLER 98 /* PTPC IRQ handler */
    IRQ_HANDLER 99 /* QEI0 IRQ handler */
    IRQ_HANDLER 100 /* QEI1 IRQ handler */
    IRQ_HANDLER 101 /* QEI2 IRQ handler */
    IRQ_HANDLER 102 /* QEI3 IRQ handler */
    IRQ_HANDLER 103 /* PWM0 IRQ handler */
    IRQ_HANDLER 104 /* PWM1 IRQ handler */
    IRQ_HANDLER 105 /* PWM2 IRQ handler */
    IRQ_HANDLER 106 /* PWM3 IRQ handler */
    IRQ_HANDLER 107 /* RDC0 IRQ handler */
    IRQ_HANDLER 108 /* RDC1 IRQ handler */
    IRQ_HANDLER 109 /* SDM0 IRQ handler */
    IRQ_HANDLER 110 /* SDM1 IRQ handler */
    IRQ_HANDLER 111 /* SEI[0] IRQ handler */
    IRQ_HANDLER 112 /* SEI[1] IRQ handler */
    IRQ_HANDLER 113 /* SEI[2] IRQ handler */
    IRQ_HANDLER 114 /* SEI[3] IRQ handler */
    IRQ_HANDLER 115 /* MTG0 IRQ handler */
    IRQ_HANDLER 116 /* MTG1 IRQ handler */
    IRQ_HANDLER 117 /* VSC0 IRQ handler */
    IRQ_HANDLER 118 /* VSC1 IRQ handler */
    IRQ_HANDLER 119 /* CLC0[0] IRQ handler */
    IRQ_HANDLER 120 /* CLC0[1] IRQ handler */
    IRQ_HANDLER 121 /* CLC1[0] IRQ handler */
    IRQ_HANDLER 122 /* CLC1[1] IRQ handler */
    IRQ_HANDLER 123 /* TRGMUX0 IRQ handler */
    IRQ_HANDLER 124 /* TRGMUX1 IRQ handler */
    IRQ_HANDLER 125 /* ENET0 IRQ handler */
    IRQ_HANDLER 126 /* NTMR0 IRQ handler */
    IRQ_HANDLER 127 /* USB0 IRQ handler */
    IRQ_HANDLER 128 /* TSW[0] IRQ handler */
    IRQ_HANDLER 129 /* TSW[1] IRQ handler */
    IRQ_HANDLER 130 /* TSW[2] IRQ handler */
    IRQ_HANDLER 131 /* TSW[3] IRQ handler */
    IRQ_HANDLER 132 /* TSW_PTP_EVT IRQ handler */
    IRQ_HANDLER 133 /* ESC IRQ handler */
    IRQ_HANDLER 134 /* ESC_SYNC0 IRQ handler */
    IRQ_HANDLER 135 /* ESC_SYNC1 IRQ handler */
    IRQ_HANDLER 136 /* ESC_RESET IRQ handler */
    IRQ_HANDLER 137 /* XPI0 IRQ handler */
    IRQ_HANDLER 138 /* FEMC IRQ handler */
    IRQ_HANDLER 139 /* PPI IRQ handler */
    IRQ_HANDLER 140 /* XDMA IRQ handler */
    IRQ_HANDLER 141 /* FFA IRQ handler */
    IRQ_HANDLER 142 /* SDP IRQ handler */
    IRQ_HANDLER 143 /* RNG IRQ handler */
    IRQ_HANDLER 144 /* PKA IRQ handler */
    IRQ_HANDLER 145 /* PSEC IRQ handler */
    IRQ_HANDLER 146 /* PGPIO IRQ handler */
    IRQ_HANDLER 147 /* PEWDG IRQ handler */
    IRQ_HANDLER 148 /* PTMR IRQ handler */
    IRQ_HANDLER 149 /* PUART IRQ handler */
    IRQ_HANDLER 150 /* FUSE IRQ handler */
    IRQ_HANDLER 151 /* SECMON IRQ handler */
    IRQ_HANDLER 152 /* RTC IRQ handler */
    IRQ_HANDLER 153 /* PAD_WAKEUP IRQ handler */
    IRQ_HANDLER 154 /* BGPIO IRQ handler */
    IRQ_HANDLER 155 /* BVIO IRQ handler */
    IRQ_HANDLER 156 /* BROWNOUT IRQ handler */
    IRQ_HANDLER 157 /* SYSCTL IRQ handler */
    IRQ_HANDLER 158 /* CPU0 IRQ handler */
    IRQ_HANDLER 159 /* CPU1 IRQ handler */
    IRQ_HANDLER 160 /* DEBUG0 IRQ handler */
    IRQ_HANDLER 161 /* DEBUG1 IRQ handler */

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
.align 10

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
    IRQ_HANDLER 5 /* GPIO0_E IRQ handler */
    IRQ_HANDLER 6 /* GPIO0_F IRQ handler */
    IRQ_HANDLER 7 /* GPIO0_V IRQ handler */
    IRQ_HANDLER 8 /* GPIO0_W IRQ handler */
    IRQ_HANDLER 9 /* GPIO0_X IRQ handler */
    IRQ_HANDLER 10 /* GPIO0_Y IRQ handler */
    IRQ_HANDLER 11 /* GPIO0_Z IRQ handler */
    IRQ_HANDLER 12 /* GPIO1_A IRQ handler */
    IRQ_HANDLER 13 /* GPIO1_B IRQ handler */
    IRQ_HANDLER 14 /* GPIO1_C IRQ handler */
    IRQ_HANDLER 15 /* GPIO1_D IRQ handler */
    IRQ_HANDLER 16 /* GPIO1_E IRQ handler */
    IRQ_HANDLER 17 /* GPIO1_F IRQ handler */
    IRQ_HANDLER 18 /* GPIO1_V IRQ handler */
    IRQ_HANDLER 19 /* GPIO1_W IRQ handler */
    IRQ_HANDLER 20 /* GPIO1_X IRQ handler */
    IRQ_HANDLER 21 /* GPIO1_Y IRQ handler */
    IRQ_HANDLER 22 /* GPIO1_Z IRQ handler */
    IRQ_HANDLER 23 /* GPTMR0 IRQ handler */
    IRQ_HANDLER 24 /* GPTMR1 IRQ handler */
    IRQ_HANDLER 25 /* GPTMR2 IRQ handler */
    IRQ_HANDLER 26 /* GPTMR3 IRQ handler */
    IRQ_HANDLER 27 /* GPTMR4 IRQ handler */
    IRQ_HANDLER 28 /* GPTMR5 IRQ handler */
    IRQ_HANDLER 29 /* GPTMR6 IRQ handler */
    IRQ_HANDLER 30 /* GPTMR7 IRQ handler */
    IRQ_HANDLER 31 /* UART0 IRQ handler */
    IRQ_HANDLER 32 /* UART1 IRQ handler */
    IRQ_HANDLER 33 /* UART2 IRQ handler */
    IRQ_HANDLER 34 /* UART3 IRQ handler */
    IRQ_HANDLER 35 /* UART4 IRQ handler */
    IRQ_HANDLER 36 /* UART5 IRQ handler */
    IRQ_HANDLER 37 /* UART6 IRQ handler */
    IRQ_HANDLER 38 /* UART7 IRQ handler */
    IRQ_HANDLER 39 /* I2C0 IRQ handler */
    IRQ_HANDLER 40 /* I2C1 IRQ handler */
    IRQ_HANDLER 41 /* I2C2 IRQ handler */
    IRQ_HANDLER 42 /* I2C3 IRQ handler */
    IRQ_HANDLER 43 /* SPI0 IRQ handler */
    IRQ_HANDLER 44 /* SPI1 IRQ handler */
    IRQ_HANDLER 45 /* SPI2 IRQ handler */
    IRQ_HANDLER 46 /* SPI3 IRQ handler */
    IRQ_HANDLER 47 /* TSNS IRQ handler */
    IRQ_HANDLER 48 /* MBX0A IRQ handler */
    IRQ_HANDLER 49 /* MBX0B IRQ handler */
    IRQ_HANDLER 50 /* MBX1A IRQ handler */
    IRQ_HANDLER 51 /* MBX1B IRQ handler */
    IRQ_HANDLER 52 /* EWDG0 IRQ handler */
    IRQ_HANDLER 53 /* EWDG1 IRQ handler */
    IRQ_HANDLER 54 /* EWDG2 IRQ handler */
    IRQ_HANDLER 55 /* EWDG3 IRQ handler */
    IRQ_HANDLER 56 /* HDMA IRQ handler */
    IRQ_HANDLER 57 /* LOBS IRQ handler */
    IRQ_HANDLER 58 /* ADC0 IRQ handler */
    IRQ_HANDLER 59 /* ADC1 IRQ handler */
    IRQ_HANDLER 60 /* ADC2 IRQ handler */
    IRQ_HANDLER 61 /* ADC3 IRQ handler */
    IRQ_HANDLER 62 /* ACMP0[0] IRQ handler */
    IRQ_HANDLER 63 /* ACMP0[1] IRQ handler */
    IRQ_HANDLER 64 /* ACMP1[0] IRQ handler */
    IRQ_HANDLER 65 /* ACMP1[1] IRQ handler */
    IRQ_HANDLER 66 /* ACMP2[0] IRQ handler */
    IRQ_HANDLER 67 /* ACMP2[1] IRQ handler */
    IRQ_HANDLER 68 /* ACMP3[0] IRQ handler */
    IRQ_HANDLER 69 /* ACMP3[1] IRQ handler */
    IRQ_HANDLER 70 /* I2S0 IRQ handler */
    IRQ_HANDLER 71 /* I2S1 IRQ handler */
    IRQ_HANDLER 72 /* DAO IRQ handler */
    IRQ_HANDLER 73 /* PDM IRQ handler */
    IRQ_HANDLER 74 /* UART8 IRQ handler */
    IRQ_HANDLER 75 /* UART9 IRQ handler */
    IRQ_HANDLER 76 /* UART10 IRQ handler */
    IRQ_HANDLER 77 /* UART11 IRQ handler */
    IRQ_HANDLER 78 /* UART12 IRQ handler */
    IRQ_HANDLER 79 /* UART13 IRQ handler */
    IRQ_HANDLER 80 /* UART14 IRQ handler */
    IRQ_HANDLER 81 /* UART15 IRQ handler */
    IRQ_HANDLER 82 /* I2C4 IRQ handler */
    IRQ_HANDLER 83 /* I2C5 IRQ handler */
    IRQ_HANDLER 84 /* I2C6 IRQ handler */
    IRQ_HANDLER 85 /* I2C7 IRQ handler */
    IRQ_HANDLER 86 /* SPI4 IRQ handler */
    IRQ_HANDLER 87 /* SPI5 IRQ handler */
    IRQ_HANDLER 88 /* SPI6 IRQ handler */
    IRQ_HANDLER 89 /* SPI7 IRQ handler */
    IRQ_HANDLER 90 /* MCAN0 IRQ handler */
    IRQ_HANDLER 91 /* MCAN1 IRQ handler */
    IRQ_HANDLER 92 /* MCAN2 IRQ handler */
    IRQ_HANDLER 93 /* MCAN3 IRQ handler */
    IRQ_HANDLER 94 /* MCAN4 IRQ handler */
    IRQ_HANDLER 95 /* MCAN5 IRQ handler */
    IRQ_HANDLER 96 /* MCAN6 IRQ handler */
    IRQ_HANDLER 97 /* MCAN7 IRQ handler */
    IRQ_HANDLER 98 /* PTPC IRQ handler */
    IRQ_HANDLER 99 /* QEI0 IRQ handler */
    IRQ_HANDLER 100 /* QEI1 IRQ handler */
    IRQ_HANDLER 101 /* QEI2 IRQ handler */
    IRQ_HANDLER 102 /* QEI3 IRQ handler */
    IRQ_HANDLER 103 /* PWM0 IRQ handler */
    IRQ_HANDLER 104 /* PWM1 IRQ handler */
    IRQ_HANDLER 105 /* PWM2 IRQ handler */
    IRQ_HANDLER 106 /* PWM3 IRQ handler */
    IRQ_HANDLER 107 /* RDC0 IRQ handler */
    IRQ_HANDLER 108 /* RDC1 IRQ handler */
    IRQ_HANDLER 109 /* SDM0 IRQ handler */
    IRQ_HANDLER 110 /* SDM1 IRQ handler */
    IRQ_HANDLER 111 /* SEI[0] IRQ handler */
    IRQ_HANDLER 112 /* SEI[1] IRQ handler */
    IRQ_HANDLER 113 /* SEI[2] IRQ handler */
    IRQ_HANDLER 114 /* SEI[3] IRQ handler */
    IRQ_HANDLER 115 /* MTG0 IRQ handler */
    IRQ_HANDLER 116 /* MTG1 IRQ handler */
    IRQ_HANDLER 117 /* VSC0 IRQ handler */
    IRQ_HANDLER 118 /* VSC1 IRQ handler */
    IRQ_HANDLER 119 /* CLC0[0] IRQ handler */
    IRQ_HANDLER 120 /* CLC0[1] IRQ handler */
    IRQ_HANDLER 121 /* CLC1[0] IRQ handler */
    IRQ_HANDLER 122 /* CLC1[1] IRQ handler */
    IRQ_HANDLER 123 /* TRGMUX0 IRQ handler */
    IRQ_HANDLER 124 /* TRGMUX1 IRQ handler */
    IRQ_HANDLER 125 /* ENET0 IRQ handler */
    IRQ_HANDLER 126 /* NTMR0 IRQ handler */
    IRQ_HANDLER 127 /* USB0 IRQ handler */
    IRQ_HANDLER 128 /* TSW[0] IRQ handler */
    IRQ_HANDLER 129 /* TSW[1] IRQ handler */
    IRQ_HANDLER 130 /* TSW[2] IRQ handler */
    IRQ_HANDLER 131 /* TSW[3] IRQ handler */
    IRQ_HANDLER 132 /* TSW_PTP_EVT IRQ handler */
    IRQ_HANDLER 133 /* ESC IRQ handler */
    IRQ_HANDLER 134 /* ESC_SYNC0 IRQ handler */
    IRQ_HANDLER 135 /* ESC_SYNC1 IRQ handler */
    IRQ_HANDLER 136 /* ESC_RESET IRQ handler */
    IRQ_HANDLER 137 /* XPI0 IRQ handler */
    IRQ_HANDLER 138 /* FEMC IRQ handler */
    IRQ_HANDLER 139 /* PPI IRQ handler */
    IRQ_HANDLER 140 /* XDMA IRQ handler */
    IRQ_HANDLER 141 /* FFA IRQ handler */
    IRQ_HANDLER 142 /* SDP IRQ handler */
    IRQ_HANDLER 143 /* RNG IRQ handler */
    IRQ_HANDLER 144 /* PKA IRQ handler */
    IRQ_HANDLER 145 /* PSEC IRQ handler */
    IRQ_HANDLER 146 /* PGPIO IRQ handler */
    IRQ_HANDLER 147 /* PEWDG IRQ handler */
    IRQ_HANDLER 148 /* PTMR IRQ handler */
    IRQ_HANDLER 149 /* PUART IRQ handler */
    IRQ_HANDLER 150 /* FUSE IRQ handler */
    IRQ_HANDLER 151 /* SECMON IRQ handler */
    IRQ_HANDLER 152 /* RTC IRQ handler */
    IRQ_HANDLER 153 /* PAD_WAKEUP IRQ handler */
    IRQ_HANDLER 154 /* BGPIO IRQ handler */
    IRQ_HANDLER 155 /* BVIO IRQ handler */
    IRQ_HANDLER 156 /* BROWNOUT IRQ handler */
    IRQ_HANDLER 157 /* SYSCTL IRQ handler */
    IRQ_HANDLER 158 /* CPU0 IRQ handler */
    IRQ_HANDLER 159 /* CPU1 IRQ handler */
    IRQ_HANDLER 160 /* DEBUG0 IRQ handler */
    IRQ_HANDLER 161 /* DEBUG1 IRQ handler */

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

    SECTION `.isr_s_vector`:CODE:ROOT(10)
    PUBWEAK default_irq_s_handler
default_irq_s_handler
    j default_irq_s_handler
    IRQ_DEFAULT_S_HANDLER 1 /* GPIO0_A IRQ handler */
    IRQ_DEFAULT_S_HANDLER 2 /* GPIO0_B IRQ handler */
    IRQ_DEFAULT_S_HANDLER 3 /* GPIO0_C IRQ handler */
    IRQ_DEFAULT_S_HANDLER 4 /* GPIO0_D IRQ handler */
    IRQ_DEFAULT_S_HANDLER 5 /* GPIO0_E IRQ handler */
    IRQ_DEFAULT_S_HANDLER 6 /* GPIO0_F IRQ handler */
    IRQ_DEFAULT_S_HANDLER 7 /* GPIO0_V IRQ handler */
    IRQ_DEFAULT_S_HANDLER 8 /* GPIO0_W IRQ handler */
    IRQ_DEFAULT_S_HANDLER 9 /* GPIO0_X IRQ handler */
    IRQ_DEFAULT_S_HANDLER 10 /* GPIO0_Y IRQ handler */
    IRQ_DEFAULT_S_HANDLER 11 /* GPIO0_Z IRQ handler */
    IRQ_DEFAULT_S_HANDLER 12 /* GPIO1_A IRQ handler */
    IRQ_DEFAULT_S_HANDLER 13 /* GPIO1_B IRQ handler */
    IRQ_DEFAULT_S_HANDLER 14 /* GPIO1_C IRQ handler */
    IRQ_DEFAULT_S_HANDLER 15 /* GPIO1_D IRQ handler */
    IRQ_DEFAULT_S_HANDLER 16 /* GPIO1_E IRQ handler */
    IRQ_DEFAULT_S_HANDLER 17 /* GPIO1_F IRQ handler */
    IRQ_DEFAULT_S_HANDLER 18 /* GPIO1_V IRQ handler */
    IRQ_DEFAULT_S_HANDLER 19 /* GPIO1_W IRQ handler */
    IRQ_DEFAULT_S_HANDLER 20 /* GPIO1_X IRQ handler */
    IRQ_DEFAULT_S_HANDLER 21 /* GPIO1_Y IRQ handler */
    IRQ_DEFAULT_S_HANDLER 22 /* GPIO1_Z IRQ handler */
    IRQ_DEFAULT_S_HANDLER 23 /* GPTMR0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 24 /* GPTMR1 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 25 /* GPTMR2 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 26 /* GPTMR3 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 27 /* GPTMR4 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 28 /* GPTMR5 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 29 /* GPTMR6 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 30 /* GPTMR7 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 31 /* UART0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 32 /* UART1 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 33 /* UART2 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 34 /* UART3 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 35 /* UART4 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 36 /* UART5 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 37 /* UART6 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 38 /* UART7 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 39 /* I2C0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 40 /* I2C1 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 41 /* I2C2 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 42 /* I2C3 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 43 /* SPI0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 44 /* SPI1 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 45 /* SPI2 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 46 /* SPI3 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 47 /* TSNS IRQ handler */
    IRQ_DEFAULT_S_HANDLER 48 /* MBX0A IRQ handler */
    IRQ_DEFAULT_S_HANDLER 49 /* MBX0B IRQ handler */
    IRQ_DEFAULT_S_HANDLER 50 /* MBX1A IRQ handler */
    IRQ_DEFAULT_S_HANDLER 51 /* MBX1B IRQ handler */
    IRQ_DEFAULT_S_HANDLER 52 /* EWDG0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 53 /* EWDG1 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 54 /* EWDG2 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 55 /* EWDG3 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 56 /* HDMA IRQ handler */
    IRQ_DEFAULT_S_HANDLER 57 /* LOBS IRQ handler */
    IRQ_DEFAULT_S_HANDLER 58 /* ADC0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 59 /* ADC1 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 60 /* ADC2 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 61 /* ADC3 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 62 /* ACMP0[0] IRQ handler */
    IRQ_DEFAULT_S_HANDLER 63 /* ACMP0[1] IRQ handler */
    IRQ_DEFAULT_S_HANDLER 64 /* ACMP1[0] IRQ handler */
    IRQ_DEFAULT_S_HANDLER 65 /* ACMP1[1] IRQ handler */
    IRQ_DEFAULT_S_HANDLER 66 /* ACMP2[0] IRQ handler */
    IRQ_DEFAULT_S_HANDLER 67 /* ACMP2[1] IRQ handler */
    IRQ_DEFAULT_S_HANDLER 68 /* ACMP3[0] IRQ handler */
    IRQ_DEFAULT_S_HANDLER 69 /* ACMP3[1] IRQ handler */
    IRQ_DEFAULT_S_HANDLER 70 /* I2S0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 71 /* I2S1 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 72 /* DAO IRQ handler */
    IRQ_DEFAULT_S_HANDLER 73 /* PDM IRQ handler */
    IRQ_DEFAULT_S_HANDLER 74 /* UART8 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 75 /* UART9 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 76 /* UART10 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 77 /* UART11 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 78 /* UART12 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 79 /* UART13 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 80 /* UART14 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 81 /* UART15 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 82 /* I2C4 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 83 /* I2C5 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 84 /* I2C6 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 85 /* I2C7 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 86 /* SPI4 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 87 /* SPI5 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 88 /* SPI6 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 89 /* SPI7 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 90 /* MCAN0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 91 /* MCAN1 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 92 /* MCAN2 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 93 /* MCAN3 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 94 /* MCAN4 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 95 /* MCAN5 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 96 /* MCAN6 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 97 /* MCAN7 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 98 /* PTPC IRQ handler */
    IRQ_DEFAULT_S_HANDLER 99 /* QEI0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 100 /* QEI1 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 101 /* QEI2 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 102 /* QEI3 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 103 /* PWM0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 104 /* PWM1 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 105 /* PWM2 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 106 /* PWM3 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 107 /* RDC0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 108 /* RDC1 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 109 /* SDM0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 110 /* SDM1 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 111 /* SEI[0] IRQ handler */
    IRQ_DEFAULT_S_HANDLER 112 /* SEI[1] IRQ handler */
    IRQ_DEFAULT_S_HANDLER 113 /* SEI[2] IRQ handler */
    IRQ_DEFAULT_S_HANDLER 114 /* SEI[3] IRQ handler */
    IRQ_DEFAULT_S_HANDLER 115 /* MTG0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 116 /* MTG1 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 117 /* VSC0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 118 /* VSC1 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 119 /* CLC0[0] IRQ handler */
    IRQ_DEFAULT_S_HANDLER 120 /* CLC0[1] IRQ handler */
    IRQ_DEFAULT_S_HANDLER 121 /* CLC1[0] IRQ handler */
    IRQ_DEFAULT_S_HANDLER 122 /* CLC1[1] IRQ handler */
    IRQ_DEFAULT_S_HANDLER 123 /* TRGMUX0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 124 /* TRGMUX1 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 125 /* ENET0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 126 /* NTMR0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 127 /* USB0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 128 /* TSW[0] IRQ handler */
    IRQ_DEFAULT_S_HANDLER 129 /* TSW[1] IRQ handler */
    IRQ_DEFAULT_S_HANDLER 130 /* TSW[2] IRQ handler */
    IRQ_DEFAULT_S_HANDLER 131 /* TSW[3] IRQ handler */
    IRQ_DEFAULT_S_HANDLER 132 /* TSW_PTP_EVT IRQ handler */
    IRQ_DEFAULT_S_HANDLER 133 /* ESC IRQ handler */
    IRQ_DEFAULT_S_HANDLER 134 /* ESC_SYNC0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 135 /* ESC_SYNC1 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 136 /* ESC_RESET IRQ handler */
    IRQ_DEFAULT_S_HANDLER 137 /* XPI0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 138 /* FEMC IRQ handler */
    IRQ_DEFAULT_S_HANDLER 139 /* PPI IRQ handler */
    IRQ_DEFAULT_S_HANDLER 140 /* XDMA IRQ handler */
    IRQ_DEFAULT_S_HANDLER 141 /* FFA IRQ handler */
    IRQ_DEFAULT_S_HANDLER 142 /* SDP IRQ handler */
    IRQ_DEFAULT_S_HANDLER 143 /* RNG IRQ handler */
    IRQ_DEFAULT_S_HANDLER 144 /* PKA IRQ handler */
    IRQ_DEFAULT_S_HANDLER 145 /* PSEC IRQ handler */
    IRQ_DEFAULT_S_HANDLER 146 /* PGPIO IRQ handler */
    IRQ_DEFAULT_S_HANDLER 147 /* PEWDG IRQ handler */
    IRQ_DEFAULT_S_HANDLER 148 /* PTMR IRQ handler */
    IRQ_DEFAULT_S_HANDLER 149 /* PUART IRQ handler */
    IRQ_DEFAULT_S_HANDLER 150 /* FUSE IRQ handler */
    IRQ_DEFAULT_S_HANDLER 151 /* SECMON IRQ handler */
    IRQ_DEFAULT_S_HANDLER 152 /* RTC IRQ handler */
    IRQ_DEFAULT_S_HANDLER 153 /* PAD_WAKEUP IRQ handler */
    IRQ_DEFAULT_S_HANDLER 154 /* BGPIO IRQ handler */
    IRQ_DEFAULT_S_HANDLER 155 /* BVIO IRQ handler */
    IRQ_DEFAULT_S_HANDLER 156 /* BROWNOUT IRQ handler */
    IRQ_DEFAULT_S_HANDLER 157 /* SYSCTL IRQ handler */
    IRQ_DEFAULT_S_HANDLER 158 /* CPU0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 159 /* CPU1 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 160 /* DEBUG0 IRQ handler */
    IRQ_DEFAULT_S_HANDLER 161 /* DEBUG1 IRQ handler */

    EXTERN irq_handler_s_trap
    SECTION `.vector_s_table`:CODE:ROOT(10)
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
    IRQ_S_HANDLER 5 /* GPIO0_E IRQ handler */
    IRQ_S_HANDLER 6 /* GPIO0_F IRQ handler */
    IRQ_S_HANDLER 7 /* GPIO0_V IRQ handler */
    IRQ_S_HANDLER 8 /* GPIO0_W IRQ handler */
    IRQ_S_HANDLER 9 /* GPIO0_X IRQ handler */
    IRQ_S_HANDLER 10 /* GPIO0_Y IRQ handler */
    IRQ_S_HANDLER 11 /* GPIO0_Z IRQ handler */
    IRQ_S_HANDLER 12 /* GPIO1_A IRQ handler */
    IRQ_S_HANDLER 13 /* GPIO1_B IRQ handler */
    IRQ_S_HANDLER 14 /* GPIO1_C IRQ handler */
    IRQ_S_HANDLER 15 /* GPIO1_D IRQ handler */
    IRQ_S_HANDLER 16 /* GPIO1_E IRQ handler */
    IRQ_S_HANDLER 17 /* GPIO1_F IRQ handler */
    IRQ_S_HANDLER 18 /* GPIO1_V IRQ handler */
    IRQ_S_HANDLER 19 /* GPIO1_W IRQ handler */
    IRQ_S_HANDLER 20 /* GPIO1_X IRQ handler */
    IRQ_S_HANDLER 21 /* GPIO1_Y IRQ handler */
    IRQ_S_HANDLER 22 /* GPIO1_Z IRQ handler */
    IRQ_S_HANDLER 23 /* GPTMR0 IRQ handler */
    IRQ_S_HANDLER 24 /* GPTMR1 IRQ handler */
    IRQ_S_HANDLER 25 /* GPTMR2 IRQ handler */
    IRQ_S_HANDLER 26 /* GPTMR3 IRQ handler */
    IRQ_S_HANDLER 27 /* GPTMR4 IRQ handler */
    IRQ_S_HANDLER 28 /* GPTMR5 IRQ handler */
    IRQ_S_HANDLER 29 /* GPTMR6 IRQ handler */
    IRQ_S_HANDLER 30 /* GPTMR7 IRQ handler */
    IRQ_S_HANDLER 31 /* UART0 IRQ handler */
    IRQ_S_HANDLER 32 /* UART1 IRQ handler */
    IRQ_S_HANDLER 33 /* UART2 IRQ handler */
    IRQ_S_HANDLER 34 /* UART3 IRQ handler */
    IRQ_S_HANDLER 35 /* UART4 IRQ handler */
    IRQ_S_HANDLER 36 /* UART5 IRQ handler */
    IRQ_S_HANDLER 37 /* UART6 IRQ handler */
    IRQ_S_HANDLER 38 /* UART7 IRQ handler */
    IRQ_S_HANDLER 39 /* I2C0 IRQ handler */
    IRQ_S_HANDLER 40 /* I2C1 IRQ handler */
    IRQ_S_HANDLER 41 /* I2C2 IRQ handler */
    IRQ_S_HANDLER 42 /* I2C3 IRQ handler */
    IRQ_S_HANDLER 43 /* SPI0 IRQ handler */
    IRQ_S_HANDLER 44 /* SPI1 IRQ handler */
    IRQ_S_HANDLER 45 /* SPI2 IRQ handler */
    IRQ_S_HANDLER 46 /* SPI3 IRQ handler */
    IRQ_S_HANDLER 47 /* TSNS IRQ handler */
    IRQ_S_HANDLER 48 /* MBX0A IRQ handler */
    IRQ_S_HANDLER 49 /* MBX0B IRQ handler */
    IRQ_S_HANDLER 50 /* MBX1A IRQ handler */
    IRQ_S_HANDLER 51 /* MBX1B IRQ handler */
    IRQ_S_HANDLER 52 /* EWDG0 IRQ handler */
    IRQ_S_HANDLER 53 /* EWDG1 IRQ handler */
    IRQ_S_HANDLER 54 /* EWDG2 IRQ handler */
    IRQ_S_HANDLER 55 /* EWDG3 IRQ handler */
    IRQ_S_HANDLER 56 /* HDMA IRQ handler */
    IRQ_S_HANDLER 57 /* LOBS IRQ handler */
    IRQ_S_HANDLER 58 /* ADC0 IRQ handler */
    IRQ_S_HANDLER 59 /* ADC1 IRQ handler */
    IRQ_S_HANDLER 60 /* ADC2 IRQ handler */
    IRQ_S_HANDLER 61 /* ADC3 IRQ handler */
    IRQ_S_HANDLER 62 /* ACMP0[0] IRQ handler */
    IRQ_S_HANDLER 63 /* ACMP0[1] IRQ handler */
    IRQ_S_HANDLER 64 /* ACMP1[0] IRQ handler */
    IRQ_S_HANDLER 65 /* ACMP1[1] IRQ handler */
    IRQ_S_HANDLER 66 /* ACMP2[0] IRQ handler */
    IRQ_S_HANDLER 67 /* ACMP2[1] IRQ handler */
    IRQ_S_HANDLER 68 /* ACMP3[0] IRQ handler */
    IRQ_S_HANDLER 69 /* ACMP3[1] IRQ handler */
    IRQ_S_HANDLER 70 /* I2S0 IRQ handler */
    IRQ_S_HANDLER 71 /* I2S1 IRQ handler */
    IRQ_S_HANDLER 72 /* DAO IRQ handler */
    IRQ_S_HANDLER 73 /* PDM IRQ handler */
    IRQ_S_HANDLER 74 /* UART8 IRQ handler */
    IRQ_S_HANDLER 75 /* UART9 IRQ handler */
    IRQ_S_HANDLER 76 /* UART10 IRQ handler */
    IRQ_S_HANDLER 77 /* UART11 IRQ handler */
    IRQ_S_HANDLER 78 /* UART12 IRQ handler */
    IRQ_S_HANDLER 79 /* UART13 IRQ handler */
    IRQ_S_HANDLER 80 /* UART14 IRQ handler */
    IRQ_S_HANDLER 81 /* UART15 IRQ handler */
    IRQ_S_HANDLER 82 /* I2C4 IRQ handler */
    IRQ_S_HANDLER 83 /* I2C5 IRQ handler */
    IRQ_S_HANDLER 84 /* I2C6 IRQ handler */
    IRQ_S_HANDLER 85 /* I2C7 IRQ handler */
    IRQ_S_HANDLER 86 /* SPI4 IRQ handler */
    IRQ_S_HANDLER 87 /* SPI5 IRQ handler */
    IRQ_S_HANDLER 88 /* SPI6 IRQ handler */
    IRQ_S_HANDLER 89 /* SPI7 IRQ handler */
    IRQ_S_HANDLER 90 /* MCAN0 IRQ handler */
    IRQ_S_HANDLER 91 /* MCAN1 IRQ handler */
    IRQ_S_HANDLER 92 /* MCAN2 IRQ handler */
    IRQ_S_HANDLER 93 /* MCAN3 IRQ handler */
    IRQ_S_HANDLER 94 /* MCAN4 IRQ handler */
    IRQ_S_HANDLER 95 /* MCAN5 IRQ handler */
    IRQ_S_HANDLER 96 /* MCAN6 IRQ handler */
    IRQ_S_HANDLER 97 /* MCAN7 IRQ handler */
    IRQ_S_HANDLER 98 /* PTPC IRQ handler */
    IRQ_S_HANDLER 99 /* QEI0 IRQ handler */
    IRQ_S_HANDLER 100 /* QEI1 IRQ handler */
    IRQ_S_HANDLER 101 /* QEI2 IRQ handler */
    IRQ_S_HANDLER 102 /* QEI3 IRQ handler */
    IRQ_S_HANDLER 103 /* PWM0 IRQ handler */
    IRQ_S_HANDLER 104 /* PWM1 IRQ handler */
    IRQ_S_HANDLER 105 /* PWM2 IRQ handler */
    IRQ_S_HANDLER 106 /* PWM3 IRQ handler */
    IRQ_S_HANDLER 107 /* RDC0 IRQ handler */
    IRQ_S_HANDLER 108 /* RDC1 IRQ handler */
    IRQ_S_HANDLER 109 /* SDM0 IRQ handler */
    IRQ_S_HANDLER 110 /* SDM1 IRQ handler */
    IRQ_S_HANDLER 111 /* SEI[0] IRQ handler */
    IRQ_S_HANDLER 112 /* SEI[1] IRQ handler */
    IRQ_S_HANDLER 113 /* SEI[2] IRQ handler */
    IRQ_S_HANDLER 114 /* SEI[3] IRQ handler */
    IRQ_S_HANDLER 115 /* MTG0 IRQ handler */
    IRQ_S_HANDLER 116 /* MTG1 IRQ handler */
    IRQ_S_HANDLER 117 /* VSC0 IRQ handler */
    IRQ_S_HANDLER 118 /* VSC1 IRQ handler */
    IRQ_S_HANDLER 119 /* CLC0[0] IRQ handler */
    IRQ_S_HANDLER 120 /* CLC0[1] IRQ handler */
    IRQ_S_HANDLER 121 /* CLC1[0] IRQ handler */
    IRQ_S_HANDLER 122 /* CLC1[1] IRQ handler */
    IRQ_S_HANDLER 123 /* TRGMUX0 IRQ handler */
    IRQ_S_HANDLER 124 /* TRGMUX1 IRQ handler */
    IRQ_S_HANDLER 125 /* ENET0 IRQ handler */
    IRQ_S_HANDLER 126 /* NTMR0 IRQ handler */
    IRQ_S_HANDLER 127 /* USB0 IRQ handler */
    IRQ_S_HANDLER 128 /* TSW[0] IRQ handler */
    IRQ_S_HANDLER 129 /* TSW[1] IRQ handler */
    IRQ_S_HANDLER 130 /* TSW[2] IRQ handler */
    IRQ_S_HANDLER 131 /* TSW[3] IRQ handler */
    IRQ_S_HANDLER 132 /* TSW_PTP_EVT IRQ handler */
    IRQ_S_HANDLER 133 /* ESC IRQ handler */
    IRQ_S_HANDLER 134 /* ESC_SYNC0 IRQ handler */
    IRQ_S_HANDLER 135 /* ESC_SYNC1 IRQ handler */
    IRQ_S_HANDLER 136 /* ESC_RESET IRQ handler */
    IRQ_S_HANDLER 137 /* XPI0 IRQ handler */
    IRQ_S_HANDLER 138 /* FEMC IRQ handler */
    IRQ_S_HANDLER 139 /* PPI IRQ handler */
    IRQ_S_HANDLER 140 /* XDMA IRQ handler */
    IRQ_S_HANDLER 141 /* FFA IRQ handler */
    IRQ_S_HANDLER 142 /* SDP IRQ handler */
    IRQ_S_HANDLER 143 /* RNG IRQ handler */
    IRQ_S_HANDLER 144 /* PKA IRQ handler */
    IRQ_S_HANDLER 145 /* PSEC IRQ handler */
    IRQ_S_HANDLER 146 /* PGPIO IRQ handler */
    IRQ_S_HANDLER 147 /* PEWDG IRQ handler */
    IRQ_S_HANDLER 148 /* PTMR IRQ handler */
    IRQ_S_HANDLER 149 /* PUART IRQ handler */
    IRQ_S_HANDLER 150 /* FUSE IRQ handler */
    IRQ_S_HANDLER 151 /* SECMON IRQ handler */
    IRQ_S_HANDLER 152 /* RTC IRQ handler */
    IRQ_S_HANDLER 153 /* PAD_WAKEUP IRQ handler */
    IRQ_S_HANDLER 154 /* BGPIO IRQ handler */
    IRQ_S_HANDLER 155 /* BVIO IRQ handler */
    IRQ_S_HANDLER 156 /* BROWNOUT IRQ handler */
    IRQ_S_HANDLER 157 /* SYSCTL IRQ handler */
    IRQ_S_HANDLER 158 /* CPU0 IRQ handler */
    IRQ_S_HANDLER 159 /* CPU1 IRQ handler */
    IRQ_S_HANDLER 160 /* DEBUG0 IRQ handler */
    IRQ_S_HANDLER 161 /* DEBUG1 IRQ handler */

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
.align 10

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
    IRQ_S_HANDLER 5 /* GPIO0_E IRQ handler */
    IRQ_S_HANDLER 6 /* GPIO0_F IRQ handler */
    IRQ_S_HANDLER 7 /* GPIO0_V IRQ handler */
    IRQ_S_HANDLER 8 /* GPIO0_W IRQ handler */
    IRQ_S_HANDLER 9 /* GPIO0_X IRQ handler */
    IRQ_S_HANDLER 10 /* GPIO0_Y IRQ handler */
    IRQ_S_HANDLER 11 /* GPIO0_Z IRQ handler */
    IRQ_S_HANDLER 12 /* GPIO1_A IRQ handler */
    IRQ_S_HANDLER 13 /* GPIO1_B IRQ handler */
    IRQ_S_HANDLER 14 /* GPIO1_C IRQ handler */
    IRQ_S_HANDLER 15 /* GPIO1_D IRQ handler */
    IRQ_S_HANDLER 16 /* GPIO1_E IRQ handler */
    IRQ_S_HANDLER 17 /* GPIO1_F IRQ handler */
    IRQ_S_HANDLER 18 /* GPIO1_V IRQ handler */
    IRQ_S_HANDLER 19 /* GPIO1_W IRQ handler */
    IRQ_S_HANDLER 20 /* GPIO1_X IRQ handler */
    IRQ_S_HANDLER 21 /* GPIO1_Y IRQ handler */
    IRQ_S_HANDLER 22 /* GPIO1_Z IRQ handler */
    IRQ_S_HANDLER 23 /* GPTMR0 IRQ handler */
    IRQ_S_HANDLER 24 /* GPTMR1 IRQ handler */
    IRQ_S_HANDLER 25 /* GPTMR2 IRQ handler */
    IRQ_S_HANDLER 26 /* GPTMR3 IRQ handler */
    IRQ_S_HANDLER 27 /* GPTMR4 IRQ handler */
    IRQ_S_HANDLER 28 /* GPTMR5 IRQ handler */
    IRQ_S_HANDLER 29 /* GPTMR6 IRQ handler */
    IRQ_S_HANDLER 30 /* GPTMR7 IRQ handler */
    IRQ_S_HANDLER 31 /* UART0 IRQ handler */
    IRQ_S_HANDLER 32 /* UART1 IRQ handler */
    IRQ_S_HANDLER 33 /* UART2 IRQ handler */
    IRQ_S_HANDLER 34 /* UART3 IRQ handler */
    IRQ_S_HANDLER 35 /* UART4 IRQ handler */
    IRQ_S_HANDLER 36 /* UART5 IRQ handler */
    IRQ_S_HANDLER 37 /* UART6 IRQ handler */
    IRQ_S_HANDLER 38 /* UART7 IRQ handler */
    IRQ_S_HANDLER 39 /* I2C0 IRQ handler */
    IRQ_S_HANDLER 40 /* I2C1 IRQ handler */
    IRQ_S_HANDLER 41 /* I2C2 IRQ handler */
    IRQ_S_HANDLER 42 /* I2C3 IRQ handler */
    IRQ_S_HANDLER 43 /* SPI0 IRQ handler */
    IRQ_S_HANDLER 44 /* SPI1 IRQ handler */
    IRQ_S_HANDLER 45 /* SPI2 IRQ handler */
    IRQ_S_HANDLER 46 /* SPI3 IRQ handler */
    IRQ_S_HANDLER 47 /* TSNS IRQ handler */
    IRQ_S_HANDLER 48 /* MBX0A IRQ handler */
    IRQ_S_HANDLER 49 /* MBX0B IRQ handler */
    IRQ_S_HANDLER 50 /* MBX1A IRQ handler */
    IRQ_S_HANDLER 51 /* MBX1B IRQ handler */
    IRQ_S_HANDLER 52 /* EWDG0 IRQ handler */
    IRQ_S_HANDLER 53 /* EWDG1 IRQ handler */
    IRQ_S_HANDLER 54 /* EWDG2 IRQ handler */
    IRQ_S_HANDLER 55 /* EWDG3 IRQ handler */
    IRQ_S_HANDLER 56 /* HDMA IRQ handler */
    IRQ_S_HANDLER 57 /* LOBS IRQ handler */
    IRQ_S_HANDLER 58 /* ADC0 IRQ handler */
    IRQ_S_HANDLER 59 /* ADC1 IRQ handler */
    IRQ_S_HANDLER 60 /* ADC2 IRQ handler */
    IRQ_S_HANDLER 61 /* ADC3 IRQ handler */
    IRQ_S_HANDLER 62 /* ACMP0[0] IRQ handler */
    IRQ_S_HANDLER 63 /* ACMP0[1] IRQ handler */
    IRQ_S_HANDLER 64 /* ACMP1[0] IRQ handler */
    IRQ_S_HANDLER 65 /* ACMP1[1] IRQ handler */
    IRQ_S_HANDLER 66 /* ACMP2[0] IRQ handler */
    IRQ_S_HANDLER 67 /* ACMP2[1] IRQ handler */
    IRQ_S_HANDLER 68 /* ACMP3[0] IRQ handler */
    IRQ_S_HANDLER 69 /* ACMP3[1] IRQ handler */
    IRQ_S_HANDLER 70 /* I2S0 IRQ handler */
    IRQ_S_HANDLER 71 /* I2S1 IRQ handler */
    IRQ_S_HANDLER 72 /* DAO IRQ handler */
    IRQ_S_HANDLER 73 /* PDM IRQ handler */
    IRQ_S_HANDLER 74 /* UART8 IRQ handler */
    IRQ_S_HANDLER 75 /* UART9 IRQ handler */
    IRQ_S_HANDLER 76 /* UART10 IRQ handler */
    IRQ_S_HANDLER 77 /* UART11 IRQ handler */
    IRQ_S_HANDLER 78 /* UART12 IRQ handler */
    IRQ_S_HANDLER 79 /* UART13 IRQ handler */
    IRQ_S_HANDLER 80 /* UART14 IRQ handler */
    IRQ_S_HANDLER 81 /* UART15 IRQ handler */
    IRQ_S_HANDLER 82 /* I2C4 IRQ handler */
    IRQ_S_HANDLER 83 /* I2C5 IRQ handler */
    IRQ_S_HANDLER 84 /* I2C6 IRQ handler */
    IRQ_S_HANDLER 85 /* I2C7 IRQ handler */
    IRQ_S_HANDLER 86 /* SPI4 IRQ handler */
    IRQ_S_HANDLER 87 /* SPI5 IRQ handler */
    IRQ_S_HANDLER 88 /* SPI6 IRQ handler */
    IRQ_S_HANDLER 89 /* SPI7 IRQ handler */
    IRQ_S_HANDLER 90 /* MCAN0 IRQ handler */
    IRQ_S_HANDLER 91 /* MCAN1 IRQ handler */
    IRQ_S_HANDLER 92 /* MCAN2 IRQ handler */
    IRQ_S_HANDLER 93 /* MCAN3 IRQ handler */
    IRQ_S_HANDLER 94 /* MCAN4 IRQ handler */
    IRQ_S_HANDLER 95 /* MCAN5 IRQ handler */
    IRQ_S_HANDLER 96 /* MCAN6 IRQ handler */
    IRQ_S_HANDLER 97 /* MCAN7 IRQ handler */
    IRQ_S_HANDLER 98 /* PTPC IRQ handler */
    IRQ_S_HANDLER 99 /* QEI0 IRQ handler */
    IRQ_S_HANDLER 100 /* QEI1 IRQ handler */
    IRQ_S_HANDLER 101 /* QEI2 IRQ handler */
    IRQ_S_HANDLER 102 /* QEI3 IRQ handler */
    IRQ_S_HANDLER 103 /* PWM0 IRQ handler */
    IRQ_S_HANDLER 104 /* PWM1 IRQ handler */
    IRQ_S_HANDLER 105 /* PWM2 IRQ handler */
    IRQ_S_HANDLER 106 /* PWM3 IRQ handler */
    IRQ_S_HANDLER 107 /* RDC0 IRQ handler */
    IRQ_S_HANDLER 108 /* RDC1 IRQ handler */
    IRQ_S_HANDLER 109 /* SDM0 IRQ handler */
    IRQ_S_HANDLER 110 /* SDM1 IRQ handler */
    IRQ_S_HANDLER 111 /* SEI[0] IRQ handler */
    IRQ_S_HANDLER 112 /* SEI[1] IRQ handler */
    IRQ_S_HANDLER 113 /* SEI[2] IRQ handler */
    IRQ_S_HANDLER 114 /* SEI[3] IRQ handler */
    IRQ_S_HANDLER 115 /* MTG0 IRQ handler */
    IRQ_S_HANDLER 116 /* MTG1 IRQ handler */
    IRQ_S_HANDLER 117 /* VSC0 IRQ handler */
    IRQ_S_HANDLER 118 /* VSC1 IRQ handler */
    IRQ_S_HANDLER 119 /* CLC0[0] IRQ handler */
    IRQ_S_HANDLER 120 /* CLC0[1] IRQ handler */
    IRQ_S_HANDLER 121 /* CLC1[0] IRQ handler */
    IRQ_S_HANDLER 122 /* CLC1[1] IRQ handler */
    IRQ_S_HANDLER 123 /* TRGMUX0 IRQ handler */
    IRQ_S_HANDLER 124 /* TRGMUX1 IRQ handler */
    IRQ_S_HANDLER 125 /* ENET0 IRQ handler */
    IRQ_S_HANDLER 126 /* NTMR0 IRQ handler */
    IRQ_S_HANDLER 127 /* USB0 IRQ handler */
    IRQ_S_HANDLER 128 /* TSW[0] IRQ handler */
    IRQ_S_HANDLER 129 /* TSW[1] IRQ handler */
    IRQ_S_HANDLER 130 /* TSW[2] IRQ handler */
    IRQ_S_HANDLER 131 /* TSW[3] IRQ handler */
    IRQ_S_HANDLER 132 /* TSW_PTP_EVT IRQ handler */
    IRQ_S_HANDLER 133 /* ESC IRQ handler */
    IRQ_S_HANDLER 134 /* ESC_SYNC0 IRQ handler */
    IRQ_S_HANDLER 135 /* ESC_SYNC1 IRQ handler */
    IRQ_S_HANDLER 136 /* ESC_RESET IRQ handler */
    IRQ_S_HANDLER 137 /* XPI0 IRQ handler */
    IRQ_S_HANDLER 138 /* FEMC IRQ handler */
    IRQ_S_HANDLER 139 /* PPI IRQ handler */
    IRQ_S_HANDLER 140 /* XDMA IRQ handler */
    IRQ_S_HANDLER 141 /* FFA IRQ handler */
    IRQ_S_HANDLER 142 /* SDP IRQ handler */
    IRQ_S_HANDLER 143 /* RNG IRQ handler */
    IRQ_S_HANDLER 144 /* PKA IRQ handler */
    IRQ_S_HANDLER 145 /* PSEC IRQ handler */
    IRQ_S_HANDLER 146 /* PGPIO IRQ handler */
    IRQ_S_HANDLER 147 /* PEWDG IRQ handler */
    IRQ_S_HANDLER 148 /* PTMR IRQ handler */
    IRQ_S_HANDLER 149 /* PUART IRQ handler */
    IRQ_S_HANDLER 150 /* FUSE IRQ handler */
    IRQ_S_HANDLER 151 /* SECMON IRQ handler */
    IRQ_S_HANDLER 152 /* RTC IRQ handler */
    IRQ_S_HANDLER 153 /* PAD_WAKEUP IRQ handler */
    IRQ_S_HANDLER 154 /* BGPIO IRQ handler */
    IRQ_S_HANDLER 155 /* BVIO IRQ handler */
    IRQ_S_HANDLER 156 /* BROWNOUT IRQ handler */
    IRQ_S_HANDLER 157 /* SYSCTL IRQ handler */
    IRQ_S_HANDLER 158 /* CPU0 IRQ handler */
    IRQ_S_HANDLER 159 /* CPU1 IRQ handler */
    IRQ_S_HANDLER 160 /* DEBUG0 IRQ handler */
    IRQ_S_HANDLER 161 /* DEBUG1 IRQ handler */

#endif
