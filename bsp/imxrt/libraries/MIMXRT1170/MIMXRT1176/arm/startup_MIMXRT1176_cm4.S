/* ------------------------------------------------------------------------- */
/*  @file:    startup_MIMXRT1176_cm4.s                                       */
/*  @purpose: CMSIS Cortex-M4 Core Device Startup File                       */
/*            MIMXRT1176_cm4                                                 */
/*  @version: 1.0                                                            */
/*  @date:    2020-12-29                                                     */
/*  @build:   b211122                                                        */
/* ------------------------------------------------------------------------- */
/*                                                                           */
/* Copyright 1997-2016 Freescale Semiconductor, Inc.                         */
/* Copyright 2016-2021 NXP                                                   */
/* All rights reserved.                                                      */
/*                                                                           */
/* SPDX-License-Identifier: BSD-3-Clause                                     */
/*****************************************************************************/
/* Version: GCC for ARM Embedded Processors                                  */
/*****************************************************************************/
    .syntax unified
    .arch armv7-m
    .eabi_attribute Tag_ABI_align_preserved, 1 /*8-byte alignment */

    .section .isr_vector, "a"
    .align 2
    .globl __Vectors
__Vectors:
    .long   Image$$ARM_LIB_STACK$$ZI$$Limit                 /* Top of Stack */
    .long   Reset_Handler                                   /* Reset Handler */
    .long   NMI_Handler                                     /* NMI Handler*/
    .long   HardFault_Handler                               /* Hard Fault Handler*/
    .long   MemManage_Handler                               /* MPU Fault Handler*/
    .long   BusFault_Handler                                /* Bus Fault Handler*/
    .long   UsageFault_Handler                              /* Usage Fault Handler*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   SVC_Handler                                     /* SVCall Handler*/
    .long   DebugMon_Handler                                /* Debug Monitor Handler*/
    .long   0                                               /* Reserved*/
    .long   PendSV_Handler                                  /* PendSV Handler*/
    .long   SysTick_Handler                                 /* SysTick Handler*/

                                                            /* External Interrupts*/
    .long   DMA0_DMA16_IRQHandler                           /* DMA channel 0/16 transfer complete*/
    .long   DMA1_DMA17_IRQHandler                           /* DMA channel 1/17 transfer complete*/
    .long   DMA2_DMA18_IRQHandler                           /* DMA channel 2/18 transfer complete*/
    .long   DMA3_DMA19_IRQHandler                           /* DMA channel 3/19 transfer complete*/
    .long   DMA4_DMA20_IRQHandler                           /* DMA channel 4/20 transfer complete*/
    .long   DMA5_DMA21_IRQHandler                           /* DMA channel 5/21 transfer complete*/
    .long   DMA6_DMA22_IRQHandler                           /* DMA channel 6/22 transfer complete*/
    .long   DMA7_DMA23_IRQHandler                           /* DMA channel 7/23 transfer complete*/
    .long   DMA8_DMA24_IRQHandler                           /* DMA channel 8/24 transfer complete*/
    .long   DMA9_DMA25_IRQHandler                           /* DMA channel 9/25 transfer complete*/
    .long   DMA10_DMA26_IRQHandler                          /* DMA channel 10/26 transfer complete*/
    .long   DMA11_DMA27_IRQHandler                          /* DMA channel 11/27 transfer complete*/
    .long   DMA12_DMA28_IRQHandler                          /* DMA channel 12/28 transfer complete*/
    .long   DMA13_DMA29_IRQHandler                          /* DMA channel 13/29 transfer complete*/
    .long   DMA14_DMA30_IRQHandler                          /* DMA channel 14/30 transfer complete*/
    .long   DMA15_DMA31_IRQHandler                          /* DMA channel 15/31 transfer complete*/
    .long   DMA_ERROR_IRQHandler                            /* DMA error interrupt channels 0-15 / 16-31*/
    .long   Reserved33_IRQHandler                           /* Reserved interrupt*/
    .long   Reserved34_IRQHandler                           /* Reserved interrupt*/
    .long   CORE_IRQHandler                                 /* CorePlatform exception IRQ*/
    .long   LPUART1_IRQHandler                              /* LPUART1 TX interrupt and RX interrupt*/
    .long   LPUART2_IRQHandler                              /* LPUART2 TX interrupt and RX interrupt*/
    .long   LPUART3_IRQHandler                              /* LPUART3 TX interrupt and RX interrupt*/
    .long   LPUART4_IRQHandler                              /* LPUART4 TX interrupt and RX interrupt*/
    .long   LPUART5_IRQHandler                              /* LPUART5 TX interrupt and RX interrupt*/
    .long   LPUART6_IRQHandler                              /* LPUART6 TX interrupt and RX interrupt*/
    .long   LPUART7_IRQHandler                              /* LPUART7 TX interrupt and RX interrupt*/
    .long   LPUART8_IRQHandler                              /* LPUART8 TX interrupt and RX interrupt*/
    .long   LPUART9_IRQHandler                              /* LPUART9 TX interrupt and RX interrupt*/
    .long   LPUART10_IRQHandler                             /* LPUART10 TX interrupt and RX interrupt*/
    .long   LPUART11_IRQHandler                             /* LPUART11 TX interrupt and RX interrupt*/
    .long   LPUART12_IRQHandler                             /* LPUART12 TX interrupt and RX interrupt*/
    .long   LPI2C1_IRQHandler                               /* LPI2C1 interrupt*/
    .long   LPI2C2_IRQHandler                               /* LPI2C2 interrupt*/
    .long   LPI2C3_IRQHandler                               /* LPI2C3 interrupt*/
    .long   LPI2C4_IRQHandler                               /* LPI2C4 interrupt*/
    .long   LPI2C5_IRQHandler                               /* LPI2C5 interrupt*/
    .long   LPI2C6_IRQHandler                               /* LPI2C6 interrupt*/
    .long   LPSPI1_IRQHandler                               /* LPSPI1 interrupt request line to the core*/
    .long   LPSPI2_IRQHandler                               /* LPSPI2 interrupt request line to the core*/
    .long   LPSPI3_IRQHandler                               /* LPSPI3 interrupt request line to the core*/
    .long   LPSPI4_IRQHandler                               /* LPSPI4 interrupt request line to the core*/
    .long   LPSPI5_IRQHandler                               /* LPSPI5 interrupt request line to the core*/
    .long   LPSPI6_IRQHandler                               /* LPSPI6 interrupt request line to the core*/
    .long   CAN1_IRQHandler                                 /* CAN1 interrupt*/
    .long   CAN1_ERROR_IRQHandler                           /* CAN1 error interrupt*/
    .long   CAN2_IRQHandler                                 /* CAN2 interrupt*/
    .long   CAN2_ERROR_IRQHandler                           /* CAN2 error interrupt*/
    .long   CAN3_IRQHandler                                 /* CAN3 interrupt*/
    .long   CAN3_ERROR_IRQHandler                           /* CAN3 erro interrupt*/
    .long   Reserved66_IRQHandler                           /* Reserved interrupt*/
    .long   KPP_IRQHandler                                  /* Keypad nterrupt*/
    .long   Reserved68_IRQHandler                           /* Reserved interrupt*/
    .long   GPR_IRQ_IRQHandler                              /* GPR interrupt*/
    .long   eLCDIF_IRQHandler                               /* eLCDIF interrupt*/
    .long   LCDIFv2_IRQHandler                              /* LCDIFv2 interrupt*/
    .long   CSI_IRQHandler                                  /* CSI interrupt*/
    .long   PXP_IRQHandler                                  /* PXP interrupt*/
    .long   MIPI_CSI_IRQHandler                             /* MIPI_CSI interrupt*/
    .long   MIPI_DSI_IRQHandler                             /* MIPI_DSI interrupt*/
    .long   GPU2D_IRQHandler                                /* GPU2D interrupt*/
    .long   GPIO12_Combined_0_15_IRQHandler                 /* Combined interrupt indication for GPIO12 signal 0 throughout 15*/
    .long   GPIO12_Combined_16_31_IRQHandler                /* Combined interrupt indication for GPIO13 signal 16 throughout 31*/
    .long   DAC_IRQHandler                                  /* DAC interrupt*/
    .long   KEY_MANAGER_IRQHandler                          /* PUF interrupt*/
    .long   WDOG2_IRQHandler                                /* WDOG2 interrupt*/
    .long   SNVS_HP_NON_TZ_IRQHandler                       /* SRTC Consolidated Interrupt. Non TZ*/
    .long   SNVS_HP_TZ_IRQHandler                           /* SRTC Security Interrupt. TZ*/
    .long   SNVS_PULSE_EVENT_IRQHandler                     /* ON-OFF button press shorter than 5 secs (pulse event)*/
    .long   CAAM_IRQ0_IRQHandler                            /* CAAM interrupt queue for JQ0*/
    .long   CAAM_IRQ1_IRQHandler                            /* CAAM interrupt queue for JQ1*/
    .long   CAAM_IRQ2_IRQHandler                            /* CAAM interrupt queue for JQ2*/
    .long   CAAM_IRQ3_IRQHandler                            /* CAAM interrupt queue for JQ3*/
    .long   CAAM_RECORVE_ERRPR_IRQHandler                   /* CAAM interrupt for recoverable error*/
    .long   CAAM_RTIC_IRQHandler                            /* CAAM interrupt for RTIC*/
    .long   CDOG_IRQHandler                                 /* CDOG interrupt*/
    .long   SAI1_IRQHandler                                 /* SAI1 interrupt*/
    .long   SAI2_IRQHandler                                 /* SAI1 interrupt*/
    .long   SAI3_RX_IRQHandler                              /* SAI3 interrupt*/
    .long   SAI3_TX_IRQHandler                              /* SAI3 interrupt*/
    .long   SAI4_RX_IRQHandler                              /* SAI4 interrupt*/
    .long   SAI4_TX_IRQHandler                              /* SAI4 interrupt*/
    .long   SPDIF_IRQHandler                                /* SPDIF interrupt*/
    .long   TMPSNS_INT_IRQHandler                           /* TMPSNS interrupt*/
    .long   TMPSNS_LOW_HIGH_IRQHandler                      /* TMPSNS low high interrupt*/
    .long   TMPSNS_PANIC_IRQHandler                         /* TMPSNS panic interrupt*/
    .long   LPSR_LP8_BROWNOUT_IRQHandler                    /* LPSR 1p8 brownout interrupt*/
    .long   LPSR_LP0_BROWNOUT_IRQHandler                    /* LPSR 1p0 brownout interrupt*/
    .long   ADC1_IRQHandler                                 /* ADC1 interrupt*/
    .long   ADC2_IRQHandler                                 /* ADC2 interrupt*/
    .long   USBPHY1_IRQHandler                              /* USBPHY1 interrupt*/
    .long   USBPHY2_IRQHandler                              /* USBPHY2 interrupt*/
    .long   RDC_IRQHandler                                  /* RDC interrupt*/
    .long   GPIO13_Combined_0_31_IRQHandler                 /* Combined interrupt indication for GPIO13 signal 0 throughout 31*/
    .long   Reserved110_IRQHandler                          /* Reserved interrupt*/
    .long   DCIC1_IRQHandler                                /* DCIC1 interrupt*/
    .long   DCIC2_IRQHandler                                /* DCIC2 interrupt*/
    .long   ASRC_IRQHandler                                 /* ASRC interrupt*/
    .long   FLEXRAM_ECC_IRQHandler                          /* FlexRAM ECC fatal interrupt*/
    .long   GPIO7_8_9_10_11_IRQHandler                      /* GPIO7, GPIO8, GPIO9, GPIO10, GPIO11 interrupt*/
    .long   GPIO1_Combined_0_15_IRQHandler                  /* Combined interrupt indication for GPIO1 signal 0 throughout 15*/
    .long   GPIO1_Combined_16_31_IRQHandler                 /* Combined interrupt indication for GPIO1 signal 16 throughout 31*/
    .long   GPIO2_Combined_0_15_IRQHandler                  /* Combined interrupt indication for GPIO2 signal 0 throughout 15*/
    .long   GPIO2_Combined_16_31_IRQHandler                 /* Combined interrupt indication for GPIO2 signal 16 throughout 31*/
    .long   GPIO3_Combined_0_15_IRQHandler                  /* Combined interrupt indication for GPIO3 signal 0 throughout 15*/
    .long   GPIO3_Combined_16_31_IRQHandler                 /* Combined interrupt indication for GPIO3 signal 16 throughout 31*/
    .long   GPIO4_Combined_0_15_IRQHandler                  /* Combined interrupt indication for GPIO4 signal 0 throughout 15*/
    .long   GPIO4_Combined_16_31_IRQHandler                 /* Combined interrupt indication for GPIO4 signal 16 throughout 31*/
    .long   GPIO5_Combined_0_15_IRQHandler                  /* Combined interrupt indication for GPIO5 signal 0 throughout 15*/
    .long   GPIO5_Combined_16_31_IRQHandler                 /* Combined interrupt indication for GPIO5 signal 16 throughout 31*/
    .long   FLEXIO1_IRQHandler                              /* FLEXIO1 interrupt*/
    .long   FLEXIO2_IRQHandler                              /* FLEXIO2 interrupt*/
    .long   WDOG1_IRQHandler                                /* WDOG1 interrupt*/
    .long   RTWDOG4_IRQHandler                              /* RTWDOG4 interrupt*/
    .long   EWM_IRQHandler                                  /* EWM interrupt*/
    .long   OCOTP_READ_FUSE_ERROR_IRQHandler                /* OCOTP read fuse error interrupt*/
    .long   OCOTP_READ_DONE_ERROR_IRQHandler                /* OCOTP read fuse done interrupt*/
    .long   GPC_IRQHandler                                  /* GPC interrupt*/
    .long   MUB_IRQHandler                                  /* MUB interrupt*/
    .long   GPT1_IRQHandler                                 /* GPT1 interrupt*/
    .long   GPT2_IRQHandler                                 /* GPT2 interrupt*/
    .long   GPT3_IRQHandler                                 /* GPT3 interrupt*/
    .long   GPT4_IRQHandler                                 /* GPT4 interrupt*/
    .long   GPT5_IRQHandler                                 /* GPT5 interrupt*/
    .long   GPT6_IRQHandler                                 /* GPT6 interrupt*/
    .long   PWM1_0_IRQHandler                               /* PWM1 capture 0, compare 0, or reload 0 interrupt*/
    .long   PWM1_1_IRQHandler                               /* PWM1 capture 1, compare 1, or reload 0 interrupt*/
    .long   PWM1_2_IRQHandler                               /* PWM1 capture 2, compare 2, or reload 0 interrupt*/
    .long   PWM1_3_IRQHandler                               /* PWM1 capture 3, compare 3, or reload 0 interrupt*/
    .long   PWM1_FAULT_IRQHandler                           /* PWM1 fault or reload error interrupt*/
    .long   FLEXSPI1_IRQHandler                             /* FlexSPI1 interrupt*/
    .long   FLEXSPI2_IRQHandler                             /* FlexSPI2 interrupt*/
    .long   SEMC_IRQHandler                                 /* SEMC interrupt*/
    .long   USDHC1_IRQHandler                               /* USDHC1 interrupt*/
    .long   USDHC2_IRQHandler                               /* USDHC2 interrupt*/
    .long   USB_OTG2_IRQHandler                             /* USBO2 USB OTG2*/
    .long   USB_OTG1_IRQHandler                             /* USBO2 USB OTG1*/
    .long   ENET_IRQHandler                                 /* ENET interrupt*/
    .long   ENET_1588_Timer_IRQHandler                      /* ENET_1588_Timer interrupt*/
    .long   ENET_1G_MAC0_Tx_Rx_1_IRQHandler                 /* ENET 1G MAC0 transmit/receive 1*/
    .long   ENET_1G_MAC0_Tx_Rx_2_IRQHandler                 /* ENET 1G MAC0 transmit/receive 2*/
    .long   ENET_1G_IRQHandler                              /* ENET 1G interrupt*/
    .long   ENET_1G_1588_Timer_IRQHandler                   /* ENET_1G_1588_Timer interrupt*/
    .long   XBAR1_IRQ_0_1_IRQHandler                        /* XBAR1 interrupt*/
    .long   XBAR1_IRQ_2_3_IRQHandler                        /* XBAR1 interrupt*/
    .long   ADC_ETC_IRQ0_IRQHandler                         /* ADCETC IRQ0 interrupt*/
    .long   ADC_ETC_IRQ1_IRQHandler                         /* ADCETC IRQ1 interrupt*/
    .long   ADC_ETC_IRQ2_IRQHandler                         /* ADCETC IRQ2 interrupt*/
    .long   ADC_ETC_IRQ3_IRQHandler                         /* ADCETC IRQ3 interrupt*/
    .long   ADC_ETC_ERROR_IRQ_IRQHandler                    /* ADCETC Error IRQ interrupt*/
    .long   Reserved166_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved167_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved168_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved169_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved170_IRQHandler                          /* Reserved interrupt*/
    .long   PIT1_IRQHandler                                 /* PIT1 interrupt*/
    .long   PIT2_IRQHandler                                 /* PIT2 interrupt*/
    .long   ACMP1_IRQHandler                                /* ACMP interrupt*/
    .long   ACMP2_IRQHandler                                /* ACMP interrupt*/
    .long   ACMP3_IRQHandler                                /* ACMP interrupt*/
    .long   ACMP4_IRQHandler                                /* ACMP interrupt*/
    .long   Reserved177_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved178_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved179_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved180_IRQHandler                          /* Reserved interrupt*/
    .long   ENC1_IRQHandler                                 /* ENC1 interrupt*/
    .long   ENC2_IRQHandler                                 /* ENC2 interrupt*/
    .long   ENC3_IRQHandler                                 /* ENC3 interrupt*/
    .long   ENC4_IRQHandler                                 /* ENC4 interrupt*/
    .long   Reserved185_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved186_IRQHandler                          /* Reserved interrupt*/
    .long   TMR1_IRQHandler                                 /* TMR1 interrupt*/
    .long   TMR2_IRQHandler                                 /* TMR2 interrupt*/
    .long   TMR3_IRQHandler                                 /* TMR3 interrupt*/
    .long   TMR4_IRQHandler                                 /* TMR4 interrupt*/
    .long   SEMA4_CP0_IRQHandler                            /* SEMA4 CP0 interrupt*/
    .long   SEMA4_CP1_IRQHandler                            /* SEMA4 CP1 interrupt*/
    .long   PWM2_0_IRQHandler                               /* PWM2 capture 0, compare 0, or reload 0 interrupt*/
    .long   PWM2_1_IRQHandler                               /* PWM2 capture 1, compare 1, or reload 0 interrupt*/
    .long   PWM2_2_IRQHandler                               /* PWM2 capture 2, compare 2, or reload 0 interrupt*/
    .long   PWM2_3_IRQHandler                               /* PWM2 capture 3, compare 3, or reload 0 interrupt*/
    .long   PWM2_FAULT_IRQHandler                           /* PWM2 fault or reload error interrupt*/
    .long   PWM3_0_IRQHandler                               /* PWM3 capture 0, compare 0, or reload 0 interrupt*/
    .long   PWM3_1_IRQHandler                               /* PWM3 capture 1, compare 1, or reload 0 interrupt*/
    .long   PWM3_2_IRQHandler                               /* PWM3 capture 2, compare 2, or reload 0 interrupt*/
    .long   PWM3_3_IRQHandler                               /* PWM3 capture 3, compare 3, or reload 0 interrupt*/
    .long   PWM3_FAULT_IRQHandler                           /* PWM3 fault or reload error interrupt*/
    .long   PWM4_0_IRQHandler                               /* PWM4 capture 0, compare 0, or reload 0 interrupt*/
    .long   PWM4_1_IRQHandler                               /* PWM4 capture 1, compare 1, or reload 0 interrupt*/
    .long   PWM4_2_IRQHandler                               /* PWM4 capture 2, compare 2, or reload 0 interrupt*/
    .long   PWM4_3_IRQHandler                               /* PWM4 capture 3, compare 3, or reload 0 interrupt*/
    .long   PWM4_FAULT_IRQHandler                           /* PWM4 fault or reload error interrupt*/
    .long   Reserved208_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved209_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved210_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved211_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved212_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved213_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved214_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved215_IRQHandler                          /* Reserved interrupt*/
    .long   PDM_HWVAD_EVENT_IRQHandler                      /* HWVAD event interrupt*/
    .long   PDM_HWVAD_ERROR_IRQHandler                      /* HWVAD error interrupt*/
    .long   PDM_EVENT_IRQHandler                            /* PDM event interrupt*/
    .long   PDM_ERROR_IRQHandler                            /* PDM error interrupt*/
    .long   EMVSIM1_IRQHandler                              /* EMVSIM1 interrupt*/
    .long   EMVSIM2_IRQHandler                              /* EMVSIM2 interrupt*/
    .long   MECC1_INT_IRQHandler                            /* MECC1 int*/
    .long   MECC1_FATAL_INT_IRQHandler                      /* MECC1 fatal int*/
    .long   MECC2_INT_IRQHandler                            /* MECC2 int*/
    .long   MECC2_FATAL_INT_IRQHandler                      /* MECC2 fatal int*/
    .long   XECC_FLEXSPI1_INT_IRQHandler                    /* XECC int*/
    .long   XECC_FLEXSPI1_FATAL_INT_IRQHandler              /* XECC fatal int*/
    .long   XECC_FLEXSPI2_INT_IRQHandler                    /* XECC int*/
    .long   XECC_FLEXSPI2_FATAL_INT_IRQHandler              /* XECC fatal int*/
    .long   XECC_SEMC_INT_IRQHandler                        /* XECC int*/
    .long   XECC_SEMC_FATAL_INT_IRQHandler                  /* XECC fatal int*/
    .long   ENET_QOS_IRQHandler                             /* ENET_QOS interrupt*/
    .long   ENET_QOS_PMT_IRQHandler                         /* ENET_QOS_PMT interrupt*/
    .long   DefaultISR                                      /* 234*/
    .long   DefaultISR                                      /* 235*/
    .long   DefaultISR                                      /* 236*/
    .long   DefaultISR                                      /* 237*/
    .long   DefaultISR                                      /* 238*/
    .long   DefaultISR                                      /* 239*/
    .long   DefaultISR                                      /* 240*/
    .long   DefaultISR                                      /* 241*/
    .long   DefaultISR                                      /* 242*/
    .long   DefaultISR                                      /* 243*/
    .long   DefaultISR                                      /* 244*/
    .long   DefaultISR                                      /* 245*/
    .long   DefaultISR                                      /* 246*/
    .long   DefaultISR                                      /* 247*/
    .long   DefaultISR                                      /* 248*/
    .long   DefaultISR                                      /* 249*/
    .long   DefaultISR                                      /* 250*/
    .long   DefaultISR                                      /* 251*/
    .long   DefaultISR                                      /* 252*/
    .long   DefaultISR                                      /* 253*/
    .long   DefaultISR                                      /* 254*/
    .long   0xFFFFFFFF                                      /*  Reserved for user TRIM value*/

    .size    __Vectors, . - __Vectors

    .text
    .thumb

/* Reset Handler */

    .thumb_func
    .align 2
    .weak    Reset_Handler
    .type    Reset_Handler, %function
Reset_Handler:
    cpsid   i               /* Mask interrupts */
    .equ    VTOR, 0xE000ED08
    ldr     r0, =VTOR
    ldr     r1, =__Vectors
    str     r1, [r0]
    ldr     r2, [r1]
    msr     msp, r2
    ldr   r0,=SystemInit
    blx   r0
    cpsie   i               /* Unmask interrupts */
    ldr   r0,=__main
    bx    r0

    .pool
    .size Reset_Handler, . - Reset_Handler

    .align  1
    .thumb_func
    .weak DefaultISR
    .type DefaultISR, %function
DefaultISR:
    b DefaultISR
    .size DefaultISR, . - DefaultISR

    .align 1
    .thumb_func
    .weak NMI_Handler
    .type NMI_Handler, %function
NMI_Handler:
    ldr   r0,=NMI_Handler
    bx    r0
    .size NMI_Handler, . - NMI_Handler

    .align 1
    .thumb_func
    .weak HardFault_Handler
    .type HardFault_Handler, %function
HardFault_Handler:
    ldr   r0,=HardFault_Handler
    bx    r0
    .size HardFault_Handler, . - HardFault_Handler

    .align 1
    .thumb_func
    .weak SVC_Handler
    .type SVC_Handler, %function
SVC_Handler:
    ldr   r0,=SVC_Handler
    bx    r0
    .size SVC_Handler, . - SVC_Handler

    .align 1
    .thumb_func
    .weak PendSV_Handler
    .type PendSV_Handler, %function
PendSV_Handler:
    ldr   r0,=PendSV_Handler
    bx    r0
    .size PendSV_Handler, . - PendSV_Handler

    .align 1
    .thumb_func
    .weak SysTick_Handler
    .type SysTick_Handler, %function
SysTick_Handler:
    ldr   r0,=SysTick_Handler
    bx    r0
    .size SysTick_Handler, . - SysTick_Handler

    .align 1
    .thumb_func
    .weak DMA0_DMA16_IRQHandler
    .type DMA0_DMA16_IRQHandler, %function
DMA0_DMA16_IRQHandler:
    ldr   r0,=DMA0_DMA16_DriverIRQHandler
    bx    r0
    .size DMA0_DMA16_IRQHandler, . - DMA0_DMA16_IRQHandler

    .align 1
    .thumb_func
    .weak DMA1_DMA17_IRQHandler
    .type DMA1_DMA17_IRQHandler, %function
DMA1_DMA17_IRQHandler:
    ldr   r0,=DMA1_DMA17_DriverIRQHandler
    bx    r0
    .size DMA1_DMA17_IRQHandler, . - DMA1_DMA17_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_DMA18_IRQHandler
    .type DMA2_DMA18_IRQHandler, %function
DMA2_DMA18_IRQHandler:
    ldr   r0,=DMA2_DMA18_DriverIRQHandler
    bx    r0
    .size DMA2_DMA18_IRQHandler, . - DMA2_DMA18_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_DMA19_IRQHandler
    .type DMA3_DMA19_IRQHandler, %function
DMA3_DMA19_IRQHandler:
    ldr   r0,=DMA3_DMA19_DriverIRQHandler
    bx    r0
    .size DMA3_DMA19_IRQHandler, . - DMA3_DMA19_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_DMA20_IRQHandler
    .type DMA4_DMA20_IRQHandler, %function
DMA4_DMA20_IRQHandler:
    ldr   r0,=DMA4_DMA20_DriverIRQHandler
    bx    r0
    .size DMA4_DMA20_IRQHandler, . - DMA4_DMA20_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_DMA21_IRQHandler
    .type DMA5_DMA21_IRQHandler, %function
DMA5_DMA21_IRQHandler:
    ldr   r0,=DMA5_DMA21_DriverIRQHandler
    bx    r0
    .size DMA5_DMA21_IRQHandler, . - DMA5_DMA21_IRQHandler

    .align 1
    .thumb_func
    .weak DMA6_DMA22_IRQHandler
    .type DMA6_DMA22_IRQHandler, %function
DMA6_DMA22_IRQHandler:
    ldr   r0,=DMA6_DMA22_DriverIRQHandler
    bx    r0
    .size DMA6_DMA22_IRQHandler, . - DMA6_DMA22_IRQHandler

    .align 1
    .thumb_func
    .weak DMA7_DMA23_IRQHandler
    .type DMA7_DMA23_IRQHandler, %function
DMA7_DMA23_IRQHandler:
    ldr   r0,=DMA7_DMA23_DriverIRQHandler
    bx    r0
    .size DMA7_DMA23_IRQHandler, . - DMA7_DMA23_IRQHandler

    .align 1
    .thumb_func
    .weak DMA8_DMA24_IRQHandler
    .type DMA8_DMA24_IRQHandler, %function
DMA8_DMA24_IRQHandler:
    ldr   r0,=DMA8_DMA24_DriverIRQHandler
    bx    r0
    .size DMA8_DMA24_IRQHandler, . - DMA8_DMA24_IRQHandler

    .align 1
    .thumb_func
    .weak DMA9_DMA25_IRQHandler
    .type DMA9_DMA25_IRQHandler, %function
DMA9_DMA25_IRQHandler:
    ldr   r0,=DMA9_DMA25_DriverIRQHandler
    bx    r0
    .size DMA9_DMA25_IRQHandler, . - DMA9_DMA25_IRQHandler

    .align 1
    .thumb_func
    .weak DMA10_DMA26_IRQHandler
    .type DMA10_DMA26_IRQHandler, %function
DMA10_DMA26_IRQHandler:
    ldr   r0,=DMA10_DMA26_DriverIRQHandler
    bx    r0
    .size DMA10_DMA26_IRQHandler, . - DMA10_DMA26_IRQHandler

    .align 1
    .thumb_func
    .weak DMA11_DMA27_IRQHandler
    .type DMA11_DMA27_IRQHandler, %function
DMA11_DMA27_IRQHandler:
    ldr   r0,=DMA11_DMA27_DriverIRQHandler
    bx    r0
    .size DMA11_DMA27_IRQHandler, . - DMA11_DMA27_IRQHandler

    .align 1
    .thumb_func
    .weak DMA12_DMA28_IRQHandler
    .type DMA12_DMA28_IRQHandler, %function
DMA12_DMA28_IRQHandler:
    ldr   r0,=DMA12_DMA28_DriverIRQHandler
    bx    r0
    .size DMA12_DMA28_IRQHandler, . - DMA12_DMA28_IRQHandler

    .align 1
    .thumb_func
    .weak DMA13_DMA29_IRQHandler
    .type DMA13_DMA29_IRQHandler, %function
DMA13_DMA29_IRQHandler:
    ldr   r0,=DMA13_DMA29_DriverIRQHandler
    bx    r0
    .size DMA13_DMA29_IRQHandler, . - DMA13_DMA29_IRQHandler

    .align 1
    .thumb_func
    .weak DMA14_DMA30_IRQHandler
    .type DMA14_DMA30_IRQHandler, %function
DMA14_DMA30_IRQHandler:
    ldr   r0,=DMA14_DMA30_DriverIRQHandler
    bx    r0
    .size DMA14_DMA30_IRQHandler, . - DMA14_DMA30_IRQHandler

    .align 1
    .thumb_func
    .weak DMA15_DMA31_IRQHandler
    .type DMA15_DMA31_IRQHandler, %function
DMA15_DMA31_IRQHandler:
    ldr   r0,=DMA15_DMA31_DriverIRQHandler
    bx    r0
    .size DMA15_DMA31_IRQHandler, . - DMA15_DMA31_IRQHandler

    .align 1
    .thumb_func
    .weak DMA_ERROR_IRQHandler
    .type DMA_ERROR_IRQHandler, %function
DMA_ERROR_IRQHandler:
    ldr   r0,=DMA_ERROR_DriverIRQHandler
    bx    r0
    .size DMA_ERROR_IRQHandler, . - DMA_ERROR_IRQHandler

    .align 1
    .thumb_func
    .weak LPUART1_IRQHandler
    .type LPUART1_IRQHandler, %function
LPUART1_IRQHandler:
    ldr   r0,=LPUART1_DriverIRQHandler
    bx    r0
    .size LPUART1_IRQHandler, . - LPUART1_IRQHandler

    .align 1
    .thumb_func
    .weak LPUART2_IRQHandler
    .type LPUART2_IRQHandler, %function
LPUART2_IRQHandler:
    ldr   r0,=LPUART2_DriverIRQHandler
    bx    r0
    .size LPUART2_IRQHandler, . - LPUART2_IRQHandler

    .align 1
    .thumb_func
    .weak LPUART3_IRQHandler
    .type LPUART3_IRQHandler, %function
LPUART3_IRQHandler:
    ldr   r0,=LPUART3_DriverIRQHandler
    bx    r0
    .size LPUART3_IRQHandler, . - LPUART3_IRQHandler

    .align 1
    .thumb_func
    .weak LPUART4_IRQHandler
    .type LPUART4_IRQHandler, %function
LPUART4_IRQHandler:
    ldr   r0,=LPUART4_DriverIRQHandler
    bx    r0
    .size LPUART4_IRQHandler, . - LPUART4_IRQHandler

    .align 1
    .thumb_func
    .weak LPUART5_IRQHandler
    .type LPUART5_IRQHandler, %function
LPUART5_IRQHandler:
    ldr   r0,=LPUART5_DriverIRQHandler
    bx    r0
    .size LPUART5_IRQHandler, . - LPUART5_IRQHandler

    .align 1
    .thumb_func
    .weak LPUART6_IRQHandler
    .type LPUART6_IRQHandler, %function
LPUART6_IRQHandler:
    ldr   r0,=LPUART6_DriverIRQHandler
    bx    r0
    .size LPUART6_IRQHandler, . - LPUART6_IRQHandler

    .align 1
    .thumb_func
    .weak LPUART7_IRQHandler
    .type LPUART7_IRQHandler, %function
LPUART7_IRQHandler:
    ldr   r0,=LPUART7_DriverIRQHandler
    bx    r0
    .size LPUART7_IRQHandler, . - LPUART7_IRQHandler

    .align 1
    .thumb_func
    .weak LPUART8_IRQHandler
    .type LPUART8_IRQHandler, %function
LPUART8_IRQHandler:
    ldr   r0,=LPUART8_DriverIRQHandler
    bx    r0
    .size LPUART8_IRQHandler, . - LPUART8_IRQHandler

    .align 1
    .thumb_func
    .weak LPUART9_IRQHandler
    .type LPUART9_IRQHandler, %function
LPUART9_IRQHandler:
    ldr   r0,=LPUART9_DriverIRQHandler
    bx    r0
    .size LPUART9_IRQHandler, . - LPUART9_IRQHandler

    .align 1
    .thumb_func
    .weak LPUART10_IRQHandler
    .type LPUART10_IRQHandler, %function
LPUART10_IRQHandler:
    ldr   r0,=LPUART10_DriverIRQHandler
    bx    r0
    .size LPUART10_IRQHandler, . - LPUART10_IRQHandler

    .align 1
    .thumb_func
    .weak LPUART11_IRQHandler
    .type LPUART11_IRQHandler, %function
LPUART11_IRQHandler:
    ldr   r0,=LPUART11_DriverIRQHandler
    bx    r0
    .size LPUART11_IRQHandler, . - LPUART11_IRQHandler

    .align 1
    .thumb_func
    .weak LPUART12_IRQHandler
    .type LPUART12_IRQHandler, %function
LPUART12_IRQHandler:
    ldr   r0,=LPUART12_DriverIRQHandler
    bx    r0
    .size LPUART12_IRQHandler, . - LPUART12_IRQHandler

    .align 1
    .thumb_func
    .weak LPI2C1_IRQHandler
    .type LPI2C1_IRQHandler, %function
LPI2C1_IRQHandler:
    ldr   r0,=LPI2C1_DriverIRQHandler
    bx    r0
    .size LPI2C1_IRQHandler, . - LPI2C1_IRQHandler

    .align 1
    .thumb_func
    .weak LPI2C2_IRQHandler
    .type LPI2C2_IRQHandler, %function
LPI2C2_IRQHandler:
    ldr   r0,=LPI2C2_DriverIRQHandler
    bx    r0
    .size LPI2C2_IRQHandler, . - LPI2C2_IRQHandler

    .align 1
    .thumb_func
    .weak LPI2C3_IRQHandler
    .type LPI2C3_IRQHandler, %function
LPI2C3_IRQHandler:
    ldr   r0,=LPI2C3_DriverIRQHandler
    bx    r0
    .size LPI2C3_IRQHandler, . - LPI2C3_IRQHandler

    .align 1
    .thumb_func
    .weak LPI2C4_IRQHandler
    .type LPI2C4_IRQHandler, %function
LPI2C4_IRQHandler:
    ldr   r0,=LPI2C4_DriverIRQHandler
    bx    r0
    .size LPI2C4_IRQHandler, . - LPI2C4_IRQHandler

    .align 1
    .thumb_func
    .weak LPI2C5_IRQHandler
    .type LPI2C5_IRQHandler, %function
LPI2C5_IRQHandler:
    ldr   r0,=LPI2C5_DriverIRQHandler
    bx    r0
    .size LPI2C5_IRQHandler, . - LPI2C5_IRQHandler

    .align 1
    .thumb_func
    .weak LPI2C6_IRQHandler
    .type LPI2C6_IRQHandler, %function
LPI2C6_IRQHandler:
    ldr   r0,=LPI2C6_DriverIRQHandler
    bx    r0
    .size LPI2C6_IRQHandler, . - LPI2C6_IRQHandler

    .align 1
    .thumb_func
    .weak LPSPI1_IRQHandler
    .type LPSPI1_IRQHandler, %function
LPSPI1_IRQHandler:
    ldr   r0,=LPSPI1_DriverIRQHandler
    bx    r0
    .size LPSPI1_IRQHandler, . - LPSPI1_IRQHandler

    .align 1
    .thumb_func
    .weak LPSPI2_IRQHandler
    .type LPSPI2_IRQHandler, %function
LPSPI2_IRQHandler:
    ldr   r0,=LPSPI2_DriverIRQHandler
    bx    r0
    .size LPSPI2_IRQHandler, . - LPSPI2_IRQHandler

    .align 1
    .thumb_func
    .weak LPSPI3_IRQHandler
    .type LPSPI3_IRQHandler, %function
LPSPI3_IRQHandler:
    ldr   r0,=LPSPI3_DriverIRQHandler
    bx    r0
    .size LPSPI3_IRQHandler, . - LPSPI3_IRQHandler

    .align 1
    .thumb_func
    .weak LPSPI4_IRQHandler
    .type LPSPI4_IRQHandler, %function
LPSPI4_IRQHandler:
    ldr   r0,=LPSPI4_DriverIRQHandler
    bx    r0
    .size LPSPI4_IRQHandler, . - LPSPI4_IRQHandler

    .align 1
    .thumb_func
    .weak LPSPI5_IRQHandler
    .type LPSPI5_IRQHandler, %function
LPSPI5_IRQHandler:
    ldr   r0,=LPSPI5_DriverIRQHandler
    bx    r0
    .size LPSPI5_IRQHandler, . - LPSPI5_IRQHandler

    .align 1
    .thumb_func
    .weak LPSPI6_IRQHandler
    .type LPSPI6_IRQHandler, %function
LPSPI6_IRQHandler:
    ldr   r0,=LPSPI6_DriverIRQHandler
    bx    r0
    .size LPSPI6_IRQHandler, . - LPSPI6_IRQHandler

    .align 1
    .thumb_func
    .weak CAN1_IRQHandler
    .type CAN1_IRQHandler, %function
CAN1_IRQHandler:
    ldr   r0,=CAN1_DriverIRQHandler
    bx    r0
    .size CAN1_IRQHandler, . - CAN1_IRQHandler

    .align 1
    .thumb_func
    .weak CAN1_ERROR_IRQHandler
    .type CAN1_ERROR_IRQHandler, %function
CAN1_ERROR_IRQHandler:
    ldr   r0,=CAN1_ERROR_DriverIRQHandler
    bx    r0
    .size CAN1_ERROR_IRQHandler, . - CAN1_ERROR_IRQHandler

    .align 1
    .thumb_func
    .weak CAN2_IRQHandler
    .type CAN2_IRQHandler, %function
CAN2_IRQHandler:
    ldr   r0,=CAN2_DriverIRQHandler
    bx    r0
    .size CAN2_IRQHandler, . - CAN2_IRQHandler

    .align 1
    .thumb_func
    .weak CAN2_ERROR_IRQHandler
    .type CAN2_ERROR_IRQHandler, %function
CAN2_ERROR_IRQHandler:
    ldr   r0,=CAN2_ERROR_DriverIRQHandler
    bx    r0
    .size CAN2_ERROR_IRQHandler, . - CAN2_ERROR_IRQHandler

    .align 1
    .thumb_func
    .weak CAN3_IRQHandler
    .type CAN3_IRQHandler, %function
CAN3_IRQHandler:
    ldr   r0,=CAN3_DriverIRQHandler
    bx    r0
    .size CAN3_IRQHandler, . - CAN3_IRQHandler

    .align 1
    .thumb_func
    .weak CAN3_ERROR_IRQHandler
    .type CAN3_ERROR_IRQHandler, %function
CAN3_ERROR_IRQHandler:
    ldr   r0,=CAN3_ERROR_DriverIRQHandler
    bx    r0
    .size CAN3_ERROR_IRQHandler, . - CAN3_ERROR_IRQHandler

    .align 1
    .thumb_func
    .weak CDOG_IRQHandler
    .type CDOG_IRQHandler, %function
CDOG_IRQHandler:
    ldr   r0,=CDOG_DriverIRQHandler
    bx    r0
    .size CDOG_IRQHandler, . - CDOG_IRQHandler

    .align 1
    .thumb_func
    .weak SAI1_IRQHandler
    .type SAI1_IRQHandler, %function
SAI1_IRQHandler:
    ldr   r0,=SAI1_DriverIRQHandler
    bx    r0
    .size SAI1_IRQHandler, . - SAI1_IRQHandler

    .align 1
    .thumb_func
    .weak SAI2_IRQHandler
    .type SAI2_IRQHandler, %function
SAI2_IRQHandler:
    ldr   r0,=SAI2_DriverIRQHandler
    bx    r0
    .size SAI2_IRQHandler, . - SAI2_IRQHandler

    .align 1
    .thumb_func
    .weak SAI3_RX_IRQHandler
    .type SAI3_RX_IRQHandler, %function
SAI3_RX_IRQHandler:
    ldr   r0,=SAI3_RX_DriverIRQHandler
    bx    r0
    .size SAI3_RX_IRQHandler, . - SAI3_RX_IRQHandler

    .align 1
    .thumb_func
    .weak SAI3_TX_IRQHandler
    .type SAI3_TX_IRQHandler, %function
SAI3_TX_IRQHandler:
    ldr   r0,=SAI3_TX_DriverIRQHandler
    bx    r0
    .size SAI3_TX_IRQHandler, . - SAI3_TX_IRQHandler

    .align 1
    .thumb_func
    .weak SAI4_RX_IRQHandler
    .type SAI4_RX_IRQHandler, %function
SAI4_RX_IRQHandler:
    ldr   r0,=SAI4_RX_DriverIRQHandler
    bx    r0
    .size SAI4_RX_IRQHandler, . - SAI4_RX_IRQHandler

    .align 1
    .thumb_func
    .weak SAI4_TX_IRQHandler
    .type SAI4_TX_IRQHandler, %function
SAI4_TX_IRQHandler:
    ldr   r0,=SAI4_TX_DriverIRQHandler
    bx    r0
    .size SAI4_TX_IRQHandler, . - SAI4_TX_IRQHandler

    .align 1
    .thumb_func
    .weak SPDIF_IRQHandler
    .type SPDIF_IRQHandler, %function
SPDIF_IRQHandler:
    ldr   r0,=SPDIF_DriverIRQHandler
    bx    r0
    .size SPDIF_IRQHandler, . - SPDIF_IRQHandler

    .align 1
    .thumb_func
    .weak ASRC_IRQHandler
    .type ASRC_IRQHandler, %function
ASRC_IRQHandler:
    ldr   r0,=ASRC_DriverIRQHandler
    bx    r0
    .size ASRC_IRQHandler, . - ASRC_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXIO1_IRQHandler
    .type FLEXIO1_IRQHandler, %function
FLEXIO1_IRQHandler:
    ldr   r0,=FLEXIO1_DriverIRQHandler
    bx    r0
    .size FLEXIO1_IRQHandler, . - FLEXIO1_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXIO2_IRQHandler
    .type FLEXIO2_IRQHandler, %function
FLEXIO2_IRQHandler:
    ldr   r0,=FLEXIO2_DriverIRQHandler
    bx    r0
    .size FLEXIO2_IRQHandler, . - FLEXIO2_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXSPI1_IRQHandler
    .type FLEXSPI1_IRQHandler, %function
FLEXSPI1_IRQHandler:
    ldr   r0,=FLEXSPI1_DriverIRQHandler
    bx    r0
    .size FLEXSPI1_IRQHandler, . - FLEXSPI1_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXSPI2_IRQHandler
    .type FLEXSPI2_IRQHandler, %function
FLEXSPI2_IRQHandler:
    ldr   r0,=FLEXSPI2_DriverIRQHandler
    bx    r0
    .size FLEXSPI2_IRQHandler, . - FLEXSPI2_IRQHandler

    .align 1
    .thumb_func
    .weak USDHC1_IRQHandler
    .type USDHC1_IRQHandler, %function
USDHC1_IRQHandler:
    ldr   r0,=USDHC1_DriverIRQHandler
    bx    r0
    .size USDHC1_IRQHandler, . - USDHC1_IRQHandler

    .align 1
    .thumb_func
    .weak USDHC2_IRQHandler
    .type USDHC2_IRQHandler, %function
USDHC2_IRQHandler:
    ldr   r0,=USDHC2_DriverIRQHandler
    bx    r0
    .size USDHC2_IRQHandler, . - USDHC2_IRQHandler

    .align 1
    .thumb_func
    .weak ENET_IRQHandler
    .type ENET_IRQHandler, %function
ENET_IRQHandler:
    ldr   r0,=ENET_DriverIRQHandler
    bx    r0
    .size ENET_IRQHandler, . - ENET_IRQHandler

    .align 1
    .thumb_func
    .weak ENET_1588_Timer_IRQHandler
    .type ENET_1588_Timer_IRQHandler, %function
ENET_1588_Timer_IRQHandler:
    ldr   r0,=ENET_1588_Timer_DriverIRQHandler
    bx    r0
    .size ENET_1588_Timer_IRQHandler, . - ENET_1588_Timer_IRQHandler

    .align 1
    .thumb_func
    .weak ENET_1G_MAC0_Tx_Rx_1_IRQHandler
    .type ENET_1G_MAC0_Tx_Rx_1_IRQHandler, %function
ENET_1G_MAC0_Tx_Rx_1_IRQHandler:
    ldr   r0,=ENET_1G_MAC0_Tx_Rx_1_DriverIRQHandler
    bx    r0
    .size ENET_1G_MAC0_Tx_Rx_1_IRQHandler, . - ENET_1G_MAC0_Tx_Rx_1_IRQHandler

    .align 1
    .thumb_func
    .weak ENET_1G_MAC0_Tx_Rx_2_IRQHandler
    .type ENET_1G_MAC0_Tx_Rx_2_IRQHandler, %function
ENET_1G_MAC0_Tx_Rx_2_IRQHandler:
    ldr   r0,=ENET_1G_MAC0_Tx_Rx_2_DriverIRQHandler
    bx    r0
    .size ENET_1G_MAC0_Tx_Rx_2_IRQHandler, . - ENET_1G_MAC0_Tx_Rx_2_IRQHandler

    .align 1
    .thumb_func
    .weak ENET_1G_IRQHandler
    .type ENET_1G_IRQHandler, %function
ENET_1G_IRQHandler:
    ldr   r0,=ENET_1G_DriverIRQHandler
    bx    r0
    .size ENET_1G_IRQHandler, . - ENET_1G_IRQHandler

    .align 1
    .thumb_func
    .weak ENET_1G_1588_Timer_IRQHandler
    .type ENET_1G_1588_Timer_IRQHandler, %function
ENET_1G_1588_Timer_IRQHandler:
    ldr   r0,=ENET_1G_1588_Timer_DriverIRQHandler
    bx    r0
    .size ENET_1G_1588_Timer_IRQHandler, . - ENET_1G_1588_Timer_IRQHandler

    .align 1
    .thumb_func
    .weak PDM_HWVAD_EVENT_IRQHandler
    .type PDM_HWVAD_EVENT_IRQHandler, %function
PDM_HWVAD_EVENT_IRQHandler:
    ldr   r0,=PDM_HWVAD_EVENT_DriverIRQHandler
    bx    r0
    .size PDM_HWVAD_EVENT_IRQHandler, . - PDM_HWVAD_EVENT_IRQHandler

    .align 1
    .thumb_func
    .weak PDM_HWVAD_ERROR_IRQHandler
    .type PDM_HWVAD_ERROR_IRQHandler, %function
PDM_HWVAD_ERROR_IRQHandler:
    ldr   r0,=PDM_HWVAD_ERROR_DriverIRQHandler
    bx    r0
    .size PDM_HWVAD_ERROR_IRQHandler, . - PDM_HWVAD_ERROR_IRQHandler

    .align 1
    .thumb_func
    .weak PDM_EVENT_IRQHandler
    .type PDM_EVENT_IRQHandler, %function
PDM_EVENT_IRQHandler:
    ldr   r0,=PDM_EVENT_DriverIRQHandler
    bx    r0
    .size PDM_EVENT_IRQHandler, . - PDM_EVENT_IRQHandler

    .align 1
    .thumb_func
    .weak PDM_ERROR_IRQHandler
    .type PDM_ERROR_IRQHandler, %function
PDM_ERROR_IRQHandler:
    ldr   r0,=PDM_ERROR_DriverIRQHandler
    bx    r0
    .size PDM_ERROR_IRQHandler, . - PDM_ERROR_IRQHandler

    .align 1
    .thumb_func
    .weak XECC_FLEXSPI1_INT_IRQHandler
    .type XECC_FLEXSPI1_INT_IRQHandler, %function
XECC_FLEXSPI1_INT_IRQHandler:
    ldr   r0,=XECC_FLEXSPI1_INT_DriverIRQHandler
    bx    r0
    .size XECC_FLEXSPI1_INT_IRQHandler, . - XECC_FLEXSPI1_INT_IRQHandler

    .align 1
    .thumb_func
    .weak XECC_FLEXSPI1_FATAL_INT_IRQHandler
    .type XECC_FLEXSPI1_FATAL_INT_IRQHandler, %function
XECC_FLEXSPI1_FATAL_INT_IRQHandler:
    ldr   r0,=XECC_FLEXSPI1_FATAL_INT_DriverIRQHandler
    bx    r0
    .size XECC_FLEXSPI1_FATAL_INT_IRQHandler, . - XECC_FLEXSPI1_FATAL_INT_IRQHandler

    .align 1
    .thumb_func
    .weak XECC_FLEXSPI2_INT_IRQHandler
    .type XECC_FLEXSPI2_INT_IRQHandler, %function
XECC_FLEXSPI2_INT_IRQHandler:
    ldr   r0,=XECC_FLEXSPI2_INT_DriverIRQHandler
    bx    r0
    .size XECC_FLEXSPI2_INT_IRQHandler, . - XECC_FLEXSPI2_INT_IRQHandler

    .align 1
    .thumb_func
    .weak XECC_FLEXSPI2_FATAL_INT_IRQHandler
    .type XECC_FLEXSPI2_FATAL_INT_IRQHandler, %function
XECC_FLEXSPI2_FATAL_INT_IRQHandler:
    ldr   r0,=XECC_FLEXSPI2_FATAL_INT_DriverIRQHandler
    bx    r0
    .size XECC_FLEXSPI2_FATAL_INT_IRQHandler, . - XECC_FLEXSPI2_FATAL_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ENET_QOS_IRQHandler
    .type ENET_QOS_IRQHandler, %function
ENET_QOS_IRQHandler:
    ldr   r0,=ENET_QOS_DriverIRQHandler
    bx    r0
    .size ENET_QOS_IRQHandler, . - ENET_QOS_IRQHandler

    .align 1
    .thumb_func
    .weak ENET_QOS_PMT_IRQHandler
    .type ENET_QOS_PMT_IRQHandler, %function
ENET_QOS_PMT_IRQHandler:
    ldr   r0,=ENET_QOS_PMT_DriverIRQHandler
    bx    r0
    .size ENET_QOS_PMT_IRQHandler, . - ENET_QOS_PMT_IRQHandler


/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro def_irq_handler  handler_name
    .weak \handler_name
    .set  \handler_name, DefaultISR
    .endm

/* Exception Handlers */
    def_irq_handler    MemManage_Handler
    def_irq_handler    BusFault_Handler
    def_irq_handler    UsageFault_Handler
    def_irq_handler    DebugMon_Handler
    def_irq_handler    DMA0_DMA16_DriverIRQHandler
    def_irq_handler    DMA1_DMA17_DriverIRQHandler
    def_irq_handler    DMA2_DMA18_DriverIRQHandler
    def_irq_handler    DMA3_DMA19_DriverIRQHandler
    def_irq_handler    DMA4_DMA20_DriverIRQHandler
    def_irq_handler    DMA5_DMA21_DriverIRQHandler
    def_irq_handler    DMA6_DMA22_DriverIRQHandler
    def_irq_handler    DMA7_DMA23_DriverIRQHandler
    def_irq_handler    DMA8_DMA24_DriverIRQHandler
    def_irq_handler    DMA9_DMA25_DriverIRQHandler
    def_irq_handler    DMA10_DMA26_DriverIRQHandler
    def_irq_handler    DMA11_DMA27_DriverIRQHandler
    def_irq_handler    DMA12_DMA28_DriverIRQHandler
    def_irq_handler    DMA13_DMA29_DriverIRQHandler
    def_irq_handler    DMA14_DMA30_DriverIRQHandler
    def_irq_handler    DMA15_DMA31_DriverIRQHandler
    def_irq_handler    DMA_ERROR_DriverIRQHandler
    def_irq_handler    Reserved33_IRQHandler
    def_irq_handler    Reserved34_IRQHandler
    def_irq_handler    CORE_IRQHandler
    def_irq_handler    LPUART1_DriverIRQHandler
    def_irq_handler    LPUART2_DriverIRQHandler
    def_irq_handler    LPUART3_DriverIRQHandler
    def_irq_handler    LPUART4_DriverIRQHandler
    def_irq_handler    LPUART5_DriverIRQHandler
    def_irq_handler    LPUART6_DriverIRQHandler
    def_irq_handler    LPUART7_DriverIRQHandler
    def_irq_handler    LPUART8_DriverIRQHandler
    def_irq_handler    LPUART9_DriverIRQHandler
    def_irq_handler    LPUART10_DriverIRQHandler
    def_irq_handler    LPUART11_DriverIRQHandler
    def_irq_handler    LPUART12_DriverIRQHandler
    def_irq_handler    LPI2C1_DriverIRQHandler
    def_irq_handler    LPI2C2_DriverIRQHandler
    def_irq_handler    LPI2C3_DriverIRQHandler
    def_irq_handler    LPI2C4_DriverIRQHandler
    def_irq_handler    LPI2C5_DriverIRQHandler
    def_irq_handler    LPI2C6_DriverIRQHandler
    def_irq_handler    LPSPI1_DriverIRQHandler
    def_irq_handler    LPSPI2_DriverIRQHandler
    def_irq_handler    LPSPI3_DriverIRQHandler
    def_irq_handler    LPSPI4_DriverIRQHandler
    def_irq_handler    LPSPI5_DriverIRQHandler
    def_irq_handler    LPSPI6_DriverIRQHandler
    def_irq_handler    CAN1_DriverIRQHandler
    def_irq_handler    CAN1_ERROR_DriverIRQHandler
    def_irq_handler    CAN2_DriverIRQHandler
    def_irq_handler    CAN2_ERROR_DriverIRQHandler
    def_irq_handler    CAN3_DriverIRQHandler
    def_irq_handler    CAN3_ERROR_DriverIRQHandler
    def_irq_handler    Reserved66_IRQHandler
    def_irq_handler    KPP_IRQHandler
    def_irq_handler    Reserved68_IRQHandler
    def_irq_handler    GPR_IRQ_IRQHandler
    def_irq_handler    eLCDIF_IRQHandler
    def_irq_handler    LCDIFv2_IRQHandler
    def_irq_handler    CSI_IRQHandler
    def_irq_handler    PXP_IRQHandler
    def_irq_handler    MIPI_CSI_IRQHandler
    def_irq_handler    MIPI_DSI_IRQHandler
    def_irq_handler    GPU2D_IRQHandler
    def_irq_handler    GPIO12_Combined_0_15_IRQHandler
    def_irq_handler    GPIO12_Combined_16_31_IRQHandler
    def_irq_handler    DAC_IRQHandler
    def_irq_handler    KEY_MANAGER_IRQHandler
    def_irq_handler    WDOG2_IRQHandler
    def_irq_handler    SNVS_HP_NON_TZ_IRQHandler
    def_irq_handler    SNVS_HP_TZ_IRQHandler
    def_irq_handler    SNVS_PULSE_EVENT_IRQHandler
    def_irq_handler    CAAM_IRQ0_IRQHandler
    def_irq_handler    CAAM_IRQ1_IRQHandler
    def_irq_handler    CAAM_IRQ2_IRQHandler
    def_irq_handler    CAAM_IRQ3_IRQHandler
    def_irq_handler    CAAM_RECORVE_ERRPR_IRQHandler
    def_irq_handler    CAAM_RTIC_IRQHandler
    def_irq_handler    CDOG_DriverIRQHandler
    def_irq_handler    SAI1_DriverIRQHandler
    def_irq_handler    SAI2_DriverIRQHandler
    def_irq_handler    SAI3_RX_DriverIRQHandler
    def_irq_handler    SAI3_TX_DriverIRQHandler
    def_irq_handler    SAI4_RX_DriverIRQHandler
    def_irq_handler    SAI4_TX_DriverIRQHandler
    def_irq_handler    SPDIF_DriverIRQHandler
    def_irq_handler    TMPSNS_INT_IRQHandler
    def_irq_handler    TMPSNS_LOW_HIGH_IRQHandler
    def_irq_handler    TMPSNS_PANIC_IRQHandler
    def_irq_handler    LPSR_LP8_BROWNOUT_IRQHandler
    def_irq_handler    LPSR_LP0_BROWNOUT_IRQHandler
    def_irq_handler    ADC1_IRQHandler
    def_irq_handler    ADC2_IRQHandler
    def_irq_handler    USBPHY1_IRQHandler
    def_irq_handler    USBPHY2_IRQHandler
    def_irq_handler    RDC_IRQHandler
    def_irq_handler    GPIO13_Combined_0_31_IRQHandler
    def_irq_handler    Reserved110_IRQHandler
    def_irq_handler    DCIC1_IRQHandler
    def_irq_handler    DCIC2_IRQHandler
    def_irq_handler    ASRC_DriverIRQHandler
    def_irq_handler    FLEXRAM_ECC_IRQHandler
    def_irq_handler    GPIO7_8_9_10_11_IRQHandler
    def_irq_handler    GPIO1_Combined_0_15_IRQHandler
    def_irq_handler    GPIO1_Combined_16_31_IRQHandler
    def_irq_handler    GPIO2_Combined_0_15_IRQHandler
    def_irq_handler    GPIO2_Combined_16_31_IRQHandler
    def_irq_handler    GPIO3_Combined_0_15_IRQHandler
    def_irq_handler    GPIO3_Combined_16_31_IRQHandler
    def_irq_handler    GPIO4_Combined_0_15_IRQHandler
    def_irq_handler    GPIO4_Combined_16_31_IRQHandler
    def_irq_handler    GPIO5_Combined_0_15_IRQHandler
    def_irq_handler    GPIO5_Combined_16_31_IRQHandler
    def_irq_handler    FLEXIO1_DriverIRQHandler
    def_irq_handler    FLEXIO2_DriverIRQHandler
    def_irq_handler    WDOG1_IRQHandler
    def_irq_handler    RTWDOG4_IRQHandler
    def_irq_handler    EWM_IRQHandler
    def_irq_handler    OCOTP_READ_FUSE_ERROR_IRQHandler
    def_irq_handler    OCOTP_READ_DONE_ERROR_IRQHandler
    def_irq_handler    GPC_IRQHandler
    def_irq_handler    MUB_IRQHandler
    def_irq_handler    GPT1_IRQHandler
    def_irq_handler    GPT2_IRQHandler
    def_irq_handler    GPT3_IRQHandler
    def_irq_handler    GPT4_IRQHandler
    def_irq_handler    GPT5_IRQHandler
    def_irq_handler    GPT6_IRQHandler
    def_irq_handler    PWM1_0_IRQHandler
    def_irq_handler    PWM1_1_IRQHandler
    def_irq_handler    PWM1_2_IRQHandler
    def_irq_handler    PWM1_3_IRQHandler
    def_irq_handler    PWM1_FAULT_IRQHandler
    def_irq_handler    FLEXSPI1_DriverIRQHandler
    def_irq_handler    FLEXSPI2_DriverIRQHandler
    def_irq_handler    SEMC_IRQHandler
    def_irq_handler    USDHC1_DriverIRQHandler
    def_irq_handler    USDHC2_DriverIRQHandler
    def_irq_handler    USB_OTG2_IRQHandler
    def_irq_handler    USB_OTG1_IRQHandler
    def_irq_handler    ENET_DriverIRQHandler
    def_irq_handler    ENET_1588_Timer_DriverIRQHandler
    def_irq_handler    ENET_1G_MAC0_Tx_Rx_1_DriverIRQHandler
    def_irq_handler    ENET_1G_MAC0_Tx_Rx_2_DriverIRQHandler
    def_irq_handler    ENET_1G_DriverIRQHandler
    def_irq_handler    ENET_1G_1588_Timer_DriverIRQHandler
    def_irq_handler    XBAR1_IRQ_0_1_IRQHandler
    def_irq_handler    XBAR1_IRQ_2_3_IRQHandler
    def_irq_handler    ADC_ETC_IRQ0_IRQHandler
    def_irq_handler    ADC_ETC_IRQ1_IRQHandler
    def_irq_handler    ADC_ETC_IRQ2_IRQHandler
    def_irq_handler    ADC_ETC_IRQ3_IRQHandler
    def_irq_handler    ADC_ETC_ERROR_IRQ_IRQHandler
    def_irq_handler    Reserved166_IRQHandler
    def_irq_handler    Reserved167_IRQHandler
    def_irq_handler    Reserved168_IRQHandler
    def_irq_handler    Reserved169_IRQHandler
    def_irq_handler    Reserved170_IRQHandler
    def_irq_handler    PIT1_IRQHandler
    def_irq_handler    PIT2_IRQHandler
    def_irq_handler    ACMP1_IRQHandler
    def_irq_handler    ACMP2_IRQHandler
    def_irq_handler    ACMP3_IRQHandler
    def_irq_handler    ACMP4_IRQHandler
    def_irq_handler    Reserved177_IRQHandler
    def_irq_handler    Reserved178_IRQHandler
    def_irq_handler    Reserved179_IRQHandler
    def_irq_handler    Reserved180_IRQHandler
    def_irq_handler    ENC1_IRQHandler
    def_irq_handler    ENC2_IRQHandler
    def_irq_handler    ENC3_IRQHandler
    def_irq_handler    ENC4_IRQHandler
    def_irq_handler    Reserved185_IRQHandler
    def_irq_handler    Reserved186_IRQHandler
    def_irq_handler    TMR1_IRQHandler
    def_irq_handler    TMR2_IRQHandler
    def_irq_handler    TMR3_IRQHandler
    def_irq_handler    TMR4_IRQHandler
    def_irq_handler    SEMA4_CP0_IRQHandler
    def_irq_handler    SEMA4_CP1_IRQHandler
    def_irq_handler    PWM2_0_IRQHandler
    def_irq_handler    PWM2_1_IRQHandler
    def_irq_handler    PWM2_2_IRQHandler
    def_irq_handler    PWM2_3_IRQHandler
    def_irq_handler    PWM2_FAULT_IRQHandler
    def_irq_handler    PWM3_0_IRQHandler
    def_irq_handler    PWM3_1_IRQHandler
    def_irq_handler    PWM3_2_IRQHandler
    def_irq_handler    PWM3_3_IRQHandler
    def_irq_handler    PWM3_FAULT_IRQHandler
    def_irq_handler    PWM4_0_IRQHandler
    def_irq_handler    PWM4_1_IRQHandler
    def_irq_handler    PWM4_2_IRQHandler
    def_irq_handler    PWM4_3_IRQHandler
    def_irq_handler    PWM4_FAULT_IRQHandler
    def_irq_handler    Reserved208_IRQHandler
    def_irq_handler    Reserved209_IRQHandler
    def_irq_handler    Reserved210_IRQHandler
    def_irq_handler    Reserved211_IRQHandler
    def_irq_handler    Reserved212_IRQHandler
    def_irq_handler    Reserved213_IRQHandler
    def_irq_handler    Reserved214_IRQHandler
    def_irq_handler    Reserved215_IRQHandler
    def_irq_handler    PDM_HWVAD_EVENT_DriverIRQHandler
    def_irq_handler    PDM_HWVAD_ERROR_DriverIRQHandler
    def_irq_handler    PDM_EVENT_DriverIRQHandler
    def_irq_handler    PDM_ERROR_DriverIRQHandler
    def_irq_handler    EMVSIM1_IRQHandler
    def_irq_handler    EMVSIM2_IRQHandler
    def_irq_handler    MECC1_INT_IRQHandler
    def_irq_handler    MECC1_FATAL_INT_IRQHandler
    def_irq_handler    MECC2_INT_IRQHandler
    def_irq_handler    MECC2_FATAL_INT_IRQHandler
    def_irq_handler    XECC_FLEXSPI1_INT_DriverIRQHandler
    def_irq_handler    XECC_FLEXSPI1_FATAL_INT_DriverIRQHandler
    def_irq_handler    XECC_FLEXSPI2_INT_DriverIRQHandler
    def_irq_handler    XECC_FLEXSPI2_FATAL_INT_DriverIRQHandler
    def_irq_handler    XECC_SEMC_INT_IRQHandler
    def_irq_handler    XECC_SEMC_FATAL_INT_IRQHandler
    def_irq_handler    ENET_QOS_DriverIRQHandler
    def_irq_handler    ENET_QOS_PMT_DriverIRQHandler

    .end
