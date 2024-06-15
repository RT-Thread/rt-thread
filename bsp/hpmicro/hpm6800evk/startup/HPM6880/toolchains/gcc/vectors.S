/*
 * Copyright (c) 2021-2023 HPMicro
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
    IRQ_HANDLER 7 /* GPIO0_X IRQ handler */
    IRQ_HANDLER 8 /* GPIO0_Y IRQ handler */
    IRQ_HANDLER 9 /* GPIO0_Z IRQ handler */
    IRQ_HANDLER 10 /* CAN0 IRQ handler */
    IRQ_HANDLER 11 /* CAN1 IRQ handler */
    IRQ_HANDLER 12 /* CAN2 IRQ handler */
    IRQ_HANDLER 13 /* CAN3 IRQ handler */
    IRQ_HANDLER 14 /* CAN4 IRQ handler */
    IRQ_HANDLER 15 /* CAN5 IRQ handler */
    IRQ_HANDLER 16 /* CAN6 IRQ handler */
    IRQ_HANDLER 17 /* CAN7 IRQ handler */
    IRQ_HANDLER 18 /* PTPC IRQ handler */
    IRQ_HANDLER 19 /* Reserved */
    IRQ_HANDLER 20 /* Reserved */
    IRQ_HANDLER 21 /* Reserved */
    IRQ_HANDLER 22 /* Reserved */
    IRQ_HANDLER 23 /* Reserved */
    IRQ_HANDLER 24 /* Reserved */
    IRQ_HANDLER 25 /* Reserved */
    IRQ_HANDLER 26 /* Reserved */
    IRQ_HANDLER 27 /* UART0 IRQ handler */
    IRQ_HANDLER 28 /* UART1 IRQ handler */
    IRQ_HANDLER 29 /* UART2 IRQ handler */
    IRQ_HANDLER 30 /* UART3 IRQ handler */
    IRQ_HANDLER 31 /* UART4 IRQ handler */
    IRQ_HANDLER 32 /* UART5 IRQ handler */
    IRQ_HANDLER 33 /* UART6 IRQ handler */
    IRQ_HANDLER 34 /* UART7 IRQ handler */
    IRQ_HANDLER 35 /* I2C0 IRQ handler */
    IRQ_HANDLER 36 /* I2C1 IRQ handler */
    IRQ_HANDLER 37 /* I2C2 IRQ handler */
    IRQ_HANDLER 38 /* I2C3 IRQ handler */
    IRQ_HANDLER 39 /* SPI0 IRQ handler */
    IRQ_HANDLER 40 /* SPI1 IRQ handler */
    IRQ_HANDLER 41 /* SPI2 IRQ handler */
    IRQ_HANDLER 42 /* SPI3 IRQ handler */
    IRQ_HANDLER 43 /* GPTMR0 IRQ handler */
    IRQ_HANDLER 44 /* GPTMR1 IRQ handler */
    IRQ_HANDLER 45 /* GPTMR2 IRQ handler */
    IRQ_HANDLER 46 /* GPTMR3 IRQ handler */
    IRQ_HANDLER 47 /* GPTMR4 IRQ handler */
    IRQ_HANDLER 48 /* GPTMR5 IRQ handler */
    IRQ_HANDLER 49 /* GPTMR6 IRQ handler */
    IRQ_HANDLER 50 /* GPTMR7 IRQ handler */
    IRQ_HANDLER 51 /* WDG0 IRQ handler */
    IRQ_HANDLER 52 /* WDG1 IRQ handler */
    IRQ_HANDLER 53 /* MBX0A IRQ handler */
    IRQ_HANDLER 54 /* MBX0B IRQ handler */
    IRQ_HANDLER 55 /* MBX1A IRQ handler */
    IRQ_HANDLER 56 /* MBX1B IRQ handler */
    IRQ_HANDLER 57 /* RNG IRQ handler */
    IRQ_HANDLER 58 /* HDMA IRQ handler */
    IRQ_HANDLER 59 /* ADC0 IRQ handler */
    IRQ_HANDLER 60 /* ADC1 IRQ handler */
    IRQ_HANDLER 61 /* SDM IRQ handler */
    IRQ_HANDLER 62 /* OPAMP IRQ handler */
    IRQ_HANDLER 63 /* I2S0 IRQ handler */
    IRQ_HANDLER 64 /* I2S1 IRQ handler */
    IRQ_HANDLER 65 /* I2S2 IRQ handler */
    IRQ_HANDLER 66 /* I2S3 IRQ handler */
    IRQ_HANDLER 67 /* DAO IRQ handler */
    IRQ_HANDLER 68 /* PDM IRQ handler */
    IRQ_HANDLER 69 /* SMIX_DMA IRQ handler */
    IRQ_HANDLER 70 /* SMIX_ASRC IRQ handler */
    IRQ_HANDLER 71 /* CAM0 IRQ handler */
    IRQ_HANDLER 72 /* CAM1 IRQ handler */
    IRQ_HANDLER 73 /* LCDC IRQ handler */
    IRQ_HANDLER 74 /* LCDC1 IRQ handler */
    IRQ_HANDLER 75 /* PDMA IRQ handler */
    IRQ_HANDLER 76 /* JPEG IRQ handler */
    IRQ_HANDLER 77 /* GWCK0_FUNC IRQ handler */
    IRQ_HANDLER 78 /* GWCK0_ERR IRQ handler */
    IRQ_HANDLER 79 /* GWCK1_FUNC IRQ handler */
    IRQ_HANDLER 80 /* GWCK1_ERR IRQ handler */
    IRQ_HANDLER 81 /* MIPI_DSI0 IRQ handler */
    IRQ_HANDLER 82 /* MIPI_DSI1 IRQ handler */
    IRQ_HANDLER 83 /* MIPI_CSI0 IRQ handler */
    IRQ_HANDLER 84 /* MIPI_CSI0_AP IRQ handler */
    IRQ_HANDLER 85 /* MIPI_CSI0_DIAG IRQ handler */
    IRQ_HANDLER 86 /* MIPI_CSI1_AP IRQ handler */
    IRQ_HANDLER 87 /* MIPI_CSI1_DIAG IRQ handler */
    IRQ_HANDLER 88 /* MIPI_CSI1 IRQ handler */
    IRQ_HANDLER 89 /* LCB0 IRQ handler */
    IRQ_HANDLER 90 /* LCB1 IRQ handler */
    IRQ_HANDLER 91 /* GPU IRQ handler */
    IRQ_HANDLER 92 /* ENET0 IRQ handler */
    IRQ_HANDLER 93 /* NTMR0 IRQ handler */
    IRQ_HANDLER 94 /* USB0 IRQ handler */
    IRQ_HANDLER 95 /* SDXC0 IRQ handler */
    IRQ_HANDLER 96 /* SDXC1 IRQ handler */
    IRQ_HANDLER 97 /* SDP IRQ handler */
    IRQ_HANDLER 98 /* XPI0 IRQ handler */
    IRQ_HANDLER 99 /* XDMA IRQ handler */
    IRQ_HANDLER 100 /* DDR IRQ handler */
    IRQ_HANDLER 101 /* FFA IRQ handler */
    IRQ_HANDLER 102 /* PSEC IRQ handler */
    IRQ_HANDLER 103 /* TSNS IRQ handler */
    IRQ_HANDLER 104 /* VAD IRQ handler */
    IRQ_HANDLER 105 /* PGPIO IRQ handler */
    IRQ_HANDLER 106 /* PWDG IRQ handler */
    IRQ_HANDLER 107 /* PTMR IRQ handler */
    IRQ_HANDLER 108 /* PUART IRQ handler */
    IRQ_HANDLER 109 /* FUSE IRQ handler */
    IRQ_HANDLER 110 /* SECMON IRQ handler */
    IRQ_HANDLER 111 /* RTC IRQ handler */
    IRQ_HANDLER 112 /* BGPIO IRQ handler */
    IRQ_HANDLER 113 /* BVIO IRQ handler */
    IRQ_HANDLER 114 /* BROWNOUT IRQ handler */
    IRQ_HANDLER 115 /* SYSCTL IRQ handler */
    IRQ_HANDLER 116 /* DEBUG0 IRQ handler */
    IRQ_HANDLER 117 /* DEBUG1 IRQ handler */