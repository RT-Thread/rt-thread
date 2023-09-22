/**
 * \file
 *
 * Copyright (c) 2019 Microchip Technology Inc.
 *
 * \asf_license_start
 *
 * \page License
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the Licence at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * \asf_license_stop
 *
 */

#include "samd51.h"

typedef void (*intfunc)(void);
typedef union {
	intfunc __fun;
	void *  __ptr;
} intvec_elem;

void __iar_program_start(void);
int  __low_level_init(void);

/* Default empty handler */
void Dummy_Handler(void);

/* Cortex-M4 core handlers */
#pragma weak NonMaskableInt_Handler = Dummy_Handler
#pragma weak HardFault_Handler      = Dummy_Handler
#pragma weak MemManagement_Handler  = Dummy_Handler
#pragma weak BusFault_Handler       = Dummy_Handler
#pragma weak UsageFault_Handler     = Dummy_Handler
#pragma weak SVCall_Handler         = Dummy_Handler
#pragma weak DebugMonitor_Handler   = Dummy_Handler
#pragma weak PendSV_Handler         = Dummy_Handler
#pragma weak SysTick_Handler        = Dummy_Handler

/* Peripherals handlers */
#pragma weak PM_Handler        = Dummy_Handler
#pragma weak MCLK_Handler      = Dummy_Handler
#pragma weak OSCCTRL_0_Handler = Dummy_Handler /* OSCCTRL_XOSCFAIL_0, OSCCTRL_XOSCRDY_0 */
#pragma weak OSCCTRL_1_Handler = Dummy_Handler /* OSCCTRL_XOSCFAIL_1, OSCCTRL_XOSCRDY_1 */
#pragma weak OSCCTRL_2_Handler                                                                                         \
    = Dummy_Handler /* OSCCTRL_DFLLLOCKC, OSCCTRL_DFLLLOCKF, OSCCTRL_DFLLOOB, OSCCTRL_DFLLRCS, OSCCTRL_DFLLRDY */
#pragma weak OSCCTRL_3_Handler                                                                                         \
    = Dummy_Handler /* OSCCTRL_DPLLLCKF_0, OSCCTRL_DPLLLCKR_0, OSCCTRL_DPLLLDRTO_0, OSCCTRL_DPLLLTO_0 */
#pragma weak OSCCTRL_4_Handler                                                                                         \
    = Dummy_Handler /* OSCCTRL_DPLLLCKF_1, OSCCTRL_DPLLLCKR_1, OSCCTRL_DPLLLDRTO_1, OSCCTRL_DPLLLTO_1 */
#pragma weak OSC32KCTRL_Handler = Dummy_Handler
#pragma weak SUPC_0_Handler                                                                                            \
    = Dummy_Handler /* SUPC_B12SRDY, SUPC_B33SRDY, SUPC_BOD12RDY, SUPC_BOD33RDY, SUPC_VCORERDY, SUPC_VREGRDY */
#pragma weak SUPC_1_Handler = Dummy_Handler /* SUPC_BOD12DET, SUPC_BOD33DET */
#pragma weak WDT_Handler    = Dummy_Handler
#pragma weak RTC_Handler    = Dummy_Handler
#pragma weak EIC_0_Handler  = Dummy_Handler /* EIC_EXTINT_0 */
#pragma weak EIC_1_Handler  = Dummy_Handler /* EIC_EXTINT_1 */
#pragma weak EIC_2_Handler  = Dummy_Handler /* EIC_EXTINT_2 */
#pragma weak EIC_3_Handler  = Dummy_Handler /* EIC_EXTINT_3 */
#pragma weak EIC_4_Handler  = Dummy_Handler /* EIC_EXTINT_4 */
#pragma weak EIC_5_Handler  = Dummy_Handler /* EIC_EXTINT_5 */
#pragma weak EIC_6_Handler  = Dummy_Handler /* EIC_EXTINT_6 */
#pragma weak EIC_7_Handler  = Dummy_Handler /* EIC_EXTINT_7 */
#pragma weak EIC_8_Handler  = Dummy_Handler /* EIC_EXTINT_8 */
#pragma weak EIC_9_Handler  = Dummy_Handler /* EIC_EXTINT_9 */
#pragma weak EIC_10_Handler = Dummy_Handler /* EIC_EXTINT_10 */
#pragma weak EIC_11_Handler = Dummy_Handler /* EIC_EXTINT_11 */
#pragma weak EIC_12_Handler = Dummy_Handler /* EIC_EXTINT_12 */
#pragma weak EIC_13_Handler = Dummy_Handler /* EIC_EXTINT_13 */
#pragma weak EIC_14_Handler = Dummy_Handler /* EIC_EXTINT_14 */
#pragma weak EIC_15_Handler = Dummy_Handler /* EIC_EXTINT_15 */
#pragma weak FREQM_Handler  = Dummy_Handler
#pragma weak NVMCTRL_0_Handler                                                                                         \
    = Dummy_Handler /* NVMCTRL_0, NVMCTRL_1, NVMCTRL_2, NVMCTRL_3, NVMCTRL_4, NVMCTRL_5, NVMCTRL_6, NVMCTRL_7 */
#pragma weak NVMCTRL_1_Handler = Dummy_Handler /* NVMCTRL_10, NVMCTRL_8, NVMCTRL_9 */
#pragma weak DMAC_0_Handler    = Dummy_Handler /* DMAC_SUSP_0, DMAC_TCMPL_0, DMAC_TERR_0 */
#pragma weak DMAC_1_Handler    = Dummy_Handler /* DMAC_SUSP_1, DMAC_TCMPL_1, DMAC_TERR_1 */
#pragma weak DMAC_2_Handler    = Dummy_Handler /* DMAC_SUSP_2, DMAC_TCMPL_2, DMAC_TERR_2 */
#pragma weak DMAC_3_Handler    = Dummy_Handler /* DMAC_SUSP_3, DMAC_TCMPL_3, DMAC_TERR_3 */
#pragma weak DMAC_4_Handler    = Dummy_Handler /* DMAC_SUSP_10, DMAC_SUSP_11, DMAC_SUSP_12, DMAC_SUSP_13, DMAC_SUSP_14, \
                                                  DMAC_SUSP_15, DMAC_SUSP_16, DMAC_SUSP_17, DMAC_SUSP_18, DMAC_SUSP_19, \
                                                  DMAC_SUSP_20, DMAC_SUSP_21, DMAC_SUSP_22, DMAC_SUSP_23, DMAC_SUSP_24, \
                                                  DMAC_SUSP_25, DMAC_SUSP_26, DMAC_SUSP_27, DMAC_SUSP_28, DMAC_SUSP_29, \
                                                  DMAC_SUSP_30, DMAC_SUSP_31, DMAC_SUSP_4, DMAC_SUSP_5, DMAC_SUSP_6,    \
                                                  DMAC_SUSP_7, DMAC_SUSP_8, DMAC_SUSP_9, DMAC_TCMPL_10, DMAC_TCMPL_11,  \
                                                  DMAC_TCMPL_12, DMAC_TCMPL_13, DMAC_TCMPL_14, DMAC_TCMPL_15,           \
                                                  DMAC_TCMPL_16, DMAC_TCMPL_17, DMAC_TCMPL_18, DMAC_TCMPL_19,           \
                                                  DMAC_TCMPL_20, DMAC_TCMPL_21, DMAC_TCMPL_22, DMAC_TCMPL_23,           \
                                                  DMAC_TCMPL_24, DMAC_TCMPL_25, DMAC_TCMPL_26, DMAC_TCMPL_27,           \
                                                  DMAC_TCMPL_28, DMAC_TCMPL_29, DMAC_TCMPL_30, DMAC_TCMPL_31,           \
                                                  DMAC_TCMPL_4, DMAC_TCMPL_5, DMAC_TCMPL_6, DMAC_TCMPL_7, DMAC_TCMPL_8, \
                                                  DMAC_TCMPL_9, DMAC_TERR_10, DMAC_TERR_11, DMAC_TERR_12, DMAC_TERR_13, \
                                                  DMAC_TERR_14, DMAC_TERR_15, DMAC_TERR_16, DMAC_TERR_17, DMAC_TERR_18, \
                                                  DMAC_TERR_19, DMAC_TERR_20, DMAC_TERR_21, DMAC_TERR_22, DMAC_TERR_23, \
                                                  DMAC_TERR_24, DMAC_TERR_25, DMAC_TERR_26, DMAC_TERR_27, DMAC_TERR_28, \
                                                  DMAC_TERR_29, DMAC_TERR_30, DMAC_TERR_31, DMAC_TERR_4, DMAC_TERR_5,   \
                                                  DMAC_TERR_6, DMAC_TERR_7, DMAC_TERR_8, DMAC_TERR_9 */
#pragma weak EVSYS_0_Handler = Dummy_Handler   /* EVSYS_EVD_0, EVSYS_OVR_0 */
#pragma weak EVSYS_1_Handler = Dummy_Handler   /* EVSYS_EVD_1, EVSYS_OVR_1 */
#pragma weak EVSYS_2_Handler = Dummy_Handler   /* EVSYS_EVD_2, EVSYS_OVR_2 */
#pragma weak EVSYS_3_Handler = Dummy_Handler   /* EVSYS_EVD_3, EVSYS_OVR_3 */
#pragma weak EVSYS_4_Handler = Dummy_Handler   /* EVSYS_EVD_10, EVSYS_EVD_11, EVSYS_EVD_4, EVSYS_EVD_5, EVSYS_EVD_6,   \
                                                  EVSYS_EVD_7, EVSYS_EVD_8, EVSYS_EVD_9, EVSYS_OVR_10, EVSYS_OVR_11,   \
                                                  EVSYS_OVR_4, EVSYS_OVR_5, EVSYS_OVR_6, EVSYS_OVR_7, EVSYS_OVR_8,     \
                                                  EVSYS_OVR_9 */
#pragma weak PAC_Handler       = Dummy_Handler
#pragma weak RAMECC_Handler    = Dummy_Handler
#pragma weak SERCOM0_0_Handler = Dummy_Handler /* SERCOM0_0 */
#pragma weak SERCOM0_1_Handler = Dummy_Handler /* SERCOM0_1 */
#pragma weak SERCOM0_2_Handler = Dummy_Handler /* SERCOM0_2 */
#pragma weak SERCOM0_3_Handler = Dummy_Handler /* SERCOM0_3, SERCOM0_4, SERCOM0_5, SERCOM0_6 */
#pragma weak SERCOM1_0_Handler = Dummy_Handler /* SERCOM1_0 */
#pragma weak SERCOM1_1_Handler = Dummy_Handler /* SERCOM1_1 */
#pragma weak SERCOM1_2_Handler = Dummy_Handler /* SERCOM1_2 */
#pragma weak SERCOM1_3_Handler = Dummy_Handler /* SERCOM1_3, SERCOM1_4, SERCOM1_5, SERCOM1_6 */
#pragma weak SERCOM2_0_Handler = Dummy_Handler /* SERCOM2_0 */
#pragma weak SERCOM2_1_Handler = Dummy_Handler /* SERCOM2_1 */
#pragma weak SERCOM2_2_Handler = Dummy_Handler /* SERCOM2_2 */
#pragma weak SERCOM2_3_Handler = Dummy_Handler /* SERCOM2_3, SERCOM2_4, SERCOM2_5, SERCOM2_6 */
#pragma weak SERCOM3_0_Handler = Dummy_Handler /* SERCOM3_0 */
#pragma weak SERCOM3_1_Handler = Dummy_Handler /* SERCOM3_1 */
#pragma weak SERCOM3_2_Handler = Dummy_Handler /* SERCOM3_2 */
#pragma weak SERCOM3_3_Handler = Dummy_Handler /* SERCOM3_3, SERCOM3_4, SERCOM3_5, SERCOM3_6 */
#ifdef ID_SERCOM4
#pragma weak SERCOM4_0_Handler = Dummy_Handler /* SERCOM4_0 */
#pragma weak SERCOM4_1_Handler = Dummy_Handler /* SERCOM4_1 */
#pragma weak SERCOM4_2_Handler = Dummy_Handler /* SERCOM4_2 */
#pragma weak SERCOM4_3_Handler = Dummy_Handler /* SERCOM4_3, SERCOM4_4, SERCOM4_5, SERCOM4_6 */
#endif
#ifdef ID_SERCOM5
#pragma weak SERCOM5_0_Handler = Dummy_Handler /* SERCOM5_0 */
#pragma weak SERCOM5_1_Handler = Dummy_Handler /* SERCOM5_1 */
#pragma weak SERCOM5_2_Handler = Dummy_Handler /* SERCOM5_2 */
#pragma weak SERCOM5_3_Handler = Dummy_Handler /* SERCOM5_3, SERCOM5_4, SERCOM5_5, SERCOM5_6 */
#endif
#ifdef ID_SERCOM6
#pragma weak SERCOM6_0_Handler = Dummy_Handler /* SERCOM6_0 */
#pragma weak SERCOM6_1_Handler = Dummy_Handler /* SERCOM6_1 */
#pragma weak SERCOM6_2_Handler = Dummy_Handler /* SERCOM6_2 */
#pragma weak SERCOM6_3_Handler = Dummy_Handler /* SERCOM6_3, SERCOM6_4, SERCOM6_5, SERCOM6_6 */
#endif
#ifdef ID_SERCOM7
#pragma weak SERCOM7_0_Handler = Dummy_Handler /* SERCOM7_0 */
#pragma weak SERCOM7_1_Handler = Dummy_Handler /* SERCOM7_1 */
#pragma weak SERCOM7_2_Handler = Dummy_Handler /* SERCOM7_2 */
#pragma weak SERCOM7_3_Handler = Dummy_Handler /* SERCOM7_3, SERCOM7_4, SERCOM7_5, SERCOM7_6 */
#endif
#ifdef ID_CAN0
#pragma weak CAN0_Handler = Dummy_Handler
#endif
#ifdef ID_CAN1
#pragma weak CAN1_Handler = Dummy_Handler
#endif
#ifdef ID_USB
#pragma weak USB_0_Handler = Dummy_Handler /* USB_EORSM_DNRSM, USB_EORST_RST, USB_LPMSUSP_DDISC, USB_LPM_DCONN,        \
                                              USB_MSOF, USB_RAMACER, USB_RXSTP_TXSTP_0, USB_RXSTP_TXSTP_1,             \
                                              USB_RXSTP_TXSTP_2, USB_RXSTP_TXSTP_3, USB_RXSTP_TXSTP_4,                 \
                                              USB_RXSTP_TXSTP_5, USB_RXSTP_TXSTP_6, USB_RXSTP_TXSTP_7,                 \
                                              USB_STALL0_STALL_0, USB_STALL0_STALL_1, USB_STALL0_STALL_2,              \
                                              USB_STALL0_STALL_3, USB_STALL0_STALL_4, USB_STALL0_STALL_5,              \
                                              USB_STALL0_STALL_6, USB_STALL0_STALL_7, USB_STALL1_0, USB_STALL1_1,      \
                                              USB_STALL1_2, USB_STALL1_3, USB_STALL1_4, USB_STALL1_5, USB_STALL1_6,    \
                                              USB_STALL1_7, USB_SUSPEND, USB_TRFAIL0_TRFAIL_0, USB_TRFAIL0_TRFAIL_1,   \
                                              USB_TRFAIL0_TRFAIL_2, USB_TRFAIL0_TRFAIL_3, USB_TRFAIL0_TRFAIL_4,        \
                                              USB_TRFAIL0_TRFAIL_5, USB_TRFAIL0_TRFAIL_6, USB_TRFAIL0_TRFAIL_7,        \
                                              USB_TRFAIL1_PERR_0, USB_TRFAIL1_PERR_1, USB_TRFAIL1_PERR_2,              \
                                              USB_TRFAIL1_PERR_3, USB_TRFAIL1_PERR_4, USB_TRFAIL1_PERR_5,              \
                                              USB_TRFAIL1_PERR_6, USB_TRFAIL1_PERR_7, USB_UPRSM, USB_WAKEUP */
#pragma weak USB_1_Handler = Dummy_Handler /* USB_SOF_HSOF */
#pragma weak USB_2_Handler = Dummy_Handler /* USB_TRCPT0_0, USB_TRCPT0_1, USB_TRCPT0_2, USB_TRCPT0_3, USB_TRCPT0_4,    \
                                              USB_TRCPT0_5, USB_TRCPT0_6, USB_TRCPT0_7 */
#pragma weak USB_3_Handler = Dummy_Handler /* USB_TRCPT1_0, USB_TRCPT1_1, USB_TRCPT1_2, USB_TRCPT1_3, USB_TRCPT1_4,    \
                                              USB_TRCPT1_5, USB_TRCPT1_6, USB_TRCPT1_7 */
#endif
#ifdef ID_GMAC
#pragma weak GMAC_Handler = Dummy_Handler
#endif
#pragma weak TCC0_0_Handler = Dummy_Handler /* TCC0_CNT_A, TCC0_DFS_A, TCC0_ERR_A, TCC0_FAULT0_A, TCC0_FAULT1_A,       \
                                               TCC0_FAULTA_A, TCC0_FAULTB_A, TCC0_OVF, TCC0_TRG, TCC0_UFS_A */
#pragma weak TCC0_1_Handler = Dummy_Handler /* TCC0_MC_0 */
#pragma weak TCC0_2_Handler = Dummy_Handler /* TCC0_MC_1 */
#pragma weak TCC0_3_Handler = Dummy_Handler /* TCC0_MC_2 */
#pragma weak TCC0_4_Handler = Dummy_Handler /* TCC0_MC_3 */
#pragma weak TCC0_5_Handler = Dummy_Handler /* TCC0_MC_4 */
#pragma weak TCC0_6_Handler = Dummy_Handler /* TCC0_MC_5 */
#pragma weak TCC1_0_Handler = Dummy_Handler /* TCC1_CNT_A, TCC1_DFS_A, TCC1_ERR_A, TCC1_FAULT0_A, TCC1_FAULT1_A,       \
                                               TCC1_FAULTA_A, TCC1_FAULTB_A, TCC1_OVF, TCC1_TRG, TCC1_UFS_A */
#pragma weak TCC1_1_Handler = Dummy_Handler /* TCC1_MC_0 */
#pragma weak TCC1_2_Handler = Dummy_Handler /* TCC1_MC_1 */
#pragma weak TCC1_3_Handler = Dummy_Handler /* TCC1_MC_2 */
#pragma weak TCC1_4_Handler = Dummy_Handler /* TCC1_MC_3 */
#pragma weak TCC2_0_Handler = Dummy_Handler /* TCC2_CNT_A, TCC2_DFS_A, TCC2_ERR_A, TCC2_FAULT0_A, TCC2_FAULT1_A,       \
                                               TCC2_FAULTA_A, TCC2_FAULTB_A, TCC2_OVF, TCC2_TRG, TCC2_UFS_A */
#pragma weak TCC2_1_Handler = Dummy_Handler /* TCC2_MC_0 */
#pragma weak TCC2_2_Handler = Dummy_Handler /* TCC2_MC_1 */
#pragma weak TCC2_3_Handler = Dummy_Handler /* TCC2_MC_2 */
#ifdef ID_TCC3
#pragma weak TCC3_0_Handler = Dummy_Handler /* TCC3_CNT_A, TCC3_DFS_A, TCC3_ERR_A, TCC3_FAULT0_A, TCC3_FAULT1_A,       \
                                               TCC3_FAULTA_A, TCC3_FAULTB_A, TCC3_OVF, TCC3_TRG, TCC3_UFS_A */
#pragma weak TCC3_1_Handler = Dummy_Handler /* TCC3_MC_0 */
#pragma weak TCC3_2_Handler = Dummy_Handler /* TCC3_MC_1 */
#endif
#ifdef ID_TCC4
#pragma weak TCC4_0_Handler = Dummy_Handler /* TCC4_CNT_A, TCC4_DFS_A, TCC4_ERR_A, TCC4_FAULT0_A, TCC4_FAULT1_A,       \
                                               TCC4_FAULTA_A, TCC4_FAULTB_A, TCC4_OVF, TCC4_TRG, TCC4_UFS_A */
#pragma weak TCC4_1_Handler = Dummy_Handler /* TCC4_MC_0 */
#pragma weak TCC4_2_Handler = Dummy_Handler /* TCC4_MC_1 */
#endif
#pragma weak TC0_Handler = Dummy_Handler
#pragma weak TC1_Handler = Dummy_Handler
#pragma weak TC2_Handler = Dummy_Handler
#pragma weak TC3_Handler = Dummy_Handler
#ifdef ID_TC4
#pragma weak TC4_Handler = Dummy_Handler
#endif
#ifdef ID_TC5
#pragma weak TC5_Handler = Dummy_Handler
#endif
#ifdef ID_TC6
#pragma weak TC6_Handler = Dummy_Handler
#endif
#ifdef ID_TC7
#pragma weak TC7_Handler = Dummy_Handler
#endif
#pragma weak PDEC_0_Handler = Dummy_Handler /* PDEC_DIR_A, PDEC_ERR_A, PDEC_OVF, PDEC_VLC_A */
#pragma weak PDEC_1_Handler = Dummy_Handler /* PDEC_MC_0 */
#pragma weak PDEC_2_Handler = Dummy_Handler /* PDEC_MC_1 */
#pragma weak ADC0_0_Handler = Dummy_Handler /* ADC0_OVERRUN, ADC0_WINMON */
#pragma weak ADC0_1_Handler = Dummy_Handler /* ADC0_RESRDY */
#pragma weak ADC1_0_Handler = Dummy_Handler /* ADC1_OVERRUN, ADC1_WINMON */
#pragma weak ADC1_1_Handler = Dummy_Handler /* ADC1_RESRDY */
#pragma weak AC_Handler     = Dummy_Handler
#pragma weak DAC_0_Handler  = Dummy_Handler /* DAC_OVERRUN_A_0, DAC_OVERRUN_A_1, DAC_UNDERRUN_A_0, DAC_UNDERRUN_A_1 */
#pragma weak DAC_1_Handler  = Dummy_Handler /* DAC_EMPTY_0 */
#pragma weak DAC_2_Handler  = Dummy_Handler /* DAC_EMPTY_1 */
#pragma weak DAC_3_Handler  = Dummy_Handler /* DAC_RESRDY_0 */
#pragma weak DAC_4_Handler  = Dummy_Handler /* DAC_RESRDY_1 */
#ifdef ID_I2S
#pragma weak I2S_Handler = Dummy_Handler
#endif
#pragma weak PCC_Handler  = Dummy_Handler
#pragma weak AES_Handler  = Dummy_Handler
#pragma weak TRNG_Handler = Dummy_Handler
#ifdef ID_ICM
#pragma weak ICM_Handler = Dummy_Handler
#endif
#ifdef ID_PUKCC
#pragma weak PUKCC_Handler = Dummy_Handler
#endif
#pragma weak QSPI_Handler = Dummy_Handler
#ifdef ID_SDHC0
#pragma weak SDHC0_Handler = Dummy_Handler
#endif
#ifdef ID_SDHC1
#pragma weak SDHC1_Handler = Dummy_Handler
#endif

/* Exception Table */
#pragma language = extended
#pragma segment  = "CSTACK"

/* The name "__vector_table" has special meaning for C-SPY: */
/* it is where the SP start value is found, and the NVIC vector */
/* table register (VTOR) is initialized to this address if != 0 */

#pragma section                      = ".intvec"
#pragma location                     = ".intvec"
const DeviceVectors __vector_table[] = {
    (void *)__sfe("CSTACK"),
    (void *)Reset_Handler,
    (void *)NonMaskableInt_Handler,
    (void *)HardFault_Handler,
    (void *)MemManagement_Handler,
    (void *)BusFault_Handler,
    (void *)UsageFault_Handler,
    (void *)(0UL), /* Reserved */
    (void *)(0UL), /* Reserved */
    (void *)(0UL), /* Reserved */
    (void *)(0UL), /* Reserved */
    (void *)SVCall_Handler,
    (void *)DebugMonitor_Handler,
    (void *)(0UL), /* Reserved */
    (void *)PendSV_Handler,
    (void *)SysTick_Handler,

    /* Configurable interrupts */
    (void *)PM_Handler,         /*  0 Power Manager */
    (void *)MCLK_Handler,       /*  1 Main Clock */
    (void *)OSCCTRL_0_Handler,  /*  2 OSCCTRL_XOSCFAIL_0, OSCCTRL_XOSCRDY_0 */
    (void *)OSCCTRL_1_Handler,  /*  3 OSCCTRL_XOSCFAIL_1, OSCCTRL_XOSCRDY_1 */
    (void *)OSCCTRL_2_Handler,  /*  4 OSCCTRL_DFLLLOCKC, OSCCTRL_DFLLLOCKF, OSCCTRL_DFLLOOB, OSCCTRL_DFLLRCS,
                                   OSCCTRL_DFLLRDY */
    (void *)OSCCTRL_3_Handler,  /*  5 OSCCTRL_DPLLLCKF_0, OSCCTRL_DPLLLCKR_0, OSCCTRL_DPLLLDRTO_0, OSCCTRL_DPLLLTO_0 */
    (void *)OSCCTRL_4_Handler,  /*  6 OSCCTRL_DPLLLCKF_1, OSCCTRL_DPLLLCKR_1, OSCCTRL_DPLLLDRTO_1, OSCCTRL_DPLLLTO_1 */
    (void *)OSC32KCTRL_Handler, /*  7 32kHz Oscillators Control */
    (void *)
        SUPC_0_Handler, /*  8 SUPC_B12SRDY, SUPC_B33SRDY, SUPC_BOD12RDY, SUPC_BOD33RDY, SUPC_VCORERDY, SUPC_VREGRDY */
    (void *)SUPC_1_Handler,    /*  9 SUPC_BOD12DET, SUPC_BOD33DET */
    (void *)WDT_Handler,       /* 10 Watchdog Timer */
    (void *)RTC_Handler,       /* 11 Real-Time Counter */
    (void *)EIC_0_Handler,     /* 12 EIC_EXTINT_0 */
    (void *)EIC_1_Handler,     /* 13 EIC_EXTINT_1 */
    (void *)EIC_2_Handler,     /* 14 EIC_EXTINT_2 */
    (void *)EIC_3_Handler,     /* 15 EIC_EXTINT_3 */
    (void *)EIC_4_Handler,     /* 16 EIC_EXTINT_4 */
    (void *)EIC_5_Handler,     /* 17 EIC_EXTINT_5 */
    (void *)EIC_6_Handler,     /* 18 EIC_EXTINT_6 */
    (void *)EIC_7_Handler,     /* 19 EIC_EXTINT_7 */
    (void *)EIC_8_Handler,     /* 20 EIC_EXTINT_8 */
    (void *)EIC_9_Handler,     /* 21 EIC_EXTINT_9 */
    (void *)EIC_10_Handler,    /* 22 EIC_EXTINT_10 */
    (void *)EIC_11_Handler,    /* 23 EIC_EXTINT_11 */
    (void *)EIC_12_Handler,    /* 24 EIC_EXTINT_12 */
    (void *)EIC_13_Handler,    /* 25 EIC_EXTINT_13 */
    (void *)EIC_14_Handler,    /* 26 EIC_EXTINT_14 */
    (void *)EIC_15_Handler,    /* 27 EIC_EXTINT_15 */
    (void *)FREQM_Handler,     /* 28 Frequency Meter */
    (void *)NVMCTRL_0_Handler, /* 29 NVMCTRL_0, NVMCTRL_1, NVMCTRL_2, NVMCTRL_3, NVMCTRL_4, NVMCTRL_5, NVMCTRL_6,
                                  NVMCTRL_7 */
    (void *)NVMCTRL_1_Handler, /* 30 NVMCTRL_10, NVMCTRL_8, NVMCTRL_9 */
    (void *)DMAC_0_Handler,    /* 31 DMAC_SUSP_0, DMAC_TCMPL_0, DMAC_TERR_0 */
    (void *)DMAC_1_Handler,    /* 32 DMAC_SUSP_1, DMAC_TCMPL_1, DMAC_TERR_1 */
    (void *)DMAC_2_Handler,    /* 33 DMAC_SUSP_2, DMAC_TCMPL_2, DMAC_TERR_2 */
    (void *)DMAC_3_Handler,    /* 34 DMAC_SUSP_3, DMAC_TCMPL_3, DMAC_TERR_3 */
    (void *)
        DMAC_4_Handler,        /* 35 DMAC_SUSP_10, DMAC_SUSP_11, DMAC_SUSP_12, DMAC_SUSP_13, DMAC_SUSP_14, DMAC_SUSP_15,
                                  DMAC_SUSP_16, DMAC_SUSP_17, DMAC_SUSP_18, DMAC_SUSP_19, DMAC_SUSP_20, DMAC_SUSP_21,
                                  DMAC_SUSP_22, DMAC_SUSP_23, DMAC_SUSP_24, DMAC_SUSP_25, DMAC_SUSP_26, DMAC_SUSP_27,
                                  DMAC_SUSP_28, DMAC_SUSP_29, DMAC_SUSP_30, DMAC_SUSP_31, DMAC_SUSP_4, DMAC_SUSP_5,
                                  DMAC_SUSP_6, DMAC_SUSP_7, DMAC_SUSP_8, DMAC_SUSP_9, DMAC_TCMPL_10, DMAC_TCMPL_11,
                                  DMAC_TCMPL_12, DMAC_TCMPL_13, DMAC_TCMPL_14, DMAC_TCMPL_15, DMAC_TCMPL_16, DMAC_TCMPL_17,
                                  DMAC_TCMPL_18, DMAC_TCMPL_19, DMAC_TCMPL_20, DMAC_TCMPL_21, DMAC_TCMPL_22, DMAC_TCMPL_23,
                                  DMAC_TCMPL_24, DMAC_TCMPL_25, DMAC_TCMPL_26, DMAC_TCMPL_27, DMAC_TCMPL_28, DMAC_TCMPL_29,
                                  DMAC_TCMPL_30, DMAC_TCMPL_31, DMAC_TCMPL_4, DMAC_TCMPL_5, DMAC_TCMPL_6, DMAC_TCMPL_7,
                                  DMAC_TCMPL_8, DMAC_TCMPL_9, DMAC_TERR_10, DMAC_TERR_11, DMAC_TERR_12, DMAC_TERR_13,
                                  DMAC_TERR_14, DMAC_TERR_15, DMAC_TERR_16, DMAC_TERR_17, DMAC_TERR_18, DMAC_TERR_19,
                                  DMAC_TERR_20, DMAC_TERR_21, DMAC_TERR_22, DMAC_TERR_23, DMAC_TERR_24, DMAC_TERR_25,
                                  DMAC_TERR_26, DMAC_TERR_27, DMAC_TERR_28, DMAC_TERR_29, DMAC_TERR_30, DMAC_TERR_31,
                                  DMAC_TERR_4, DMAC_TERR_5, DMAC_TERR_6, DMAC_TERR_7, DMAC_TERR_8, DMAC_TERR_9 */
    (void *)EVSYS_0_Handler,   /* 36 EVSYS_EVD_0, EVSYS_OVR_0 */
    (void *)EVSYS_1_Handler,   /* 37 EVSYS_EVD_1, EVSYS_OVR_1 */
    (void *)EVSYS_2_Handler,   /* 38 EVSYS_EVD_2, EVSYS_OVR_2 */
    (void *)EVSYS_3_Handler,   /* 39 EVSYS_EVD_3, EVSYS_OVR_3 */
    (void *)EVSYS_4_Handler,   /* 40 EVSYS_EVD_10, EVSYS_EVD_11, EVSYS_EVD_4, EVSYS_EVD_5, EVSYS_EVD_6, EVSYS_EVD_7,
                                  EVSYS_EVD_8, EVSYS_EVD_9, EVSYS_OVR_10, EVSYS_OVR_11, EVSYS_OVR_4, EVSYS_OVR_5,
                                  EVSYS_OVR_6, EVSYS_OVR_7, EVSYS_OVR_8, EVSYS_OVR_9 */
    (void *)PAC_Handler,       /* 41 Peripheral Access Controller */
    (void *)(0UL),             /* 42 Reserved */
    (void *)(0UL),             /* 43 Reserved */
    (void *)(0UL),             /* 44 Reserved */
    (void *)RAMECC_Handler,    /* 45 RAM ECC */
    (void *)SERCOM0_0_Handler, /* 46 SERCOM0_0 */
    (void *)SERCOM0_1_Handler, /* 47 SERCOM0_1 */
    (void *)SERCOM0_2_Handler, /* 48 SERCOM0_2 */
    (void *)SERCOM0_3_Handler, /* 49 SERCOM0_3, SERCOM0_4, SERCOM0_5, SERCOM0_6 */
    (void *)SERCOM1_0_Handler, /* 50 SERCOM1_0 */
    (void *)SERCOM1_1_Handler, /* 51 SERCOM1_1 */
    (void *)SERCOM1_2_Handler, /* 52 SERCOM1_2 */
    (void *)SERCOM1_3_Handler, /* 53 SERCOM1_3, SERCOM1_4, SERCOM1_5, SERCOM1_6 */
    (void *)SERCOM2_0_Handler, /* 54 SERCOM2_0 */
    (void *)SERCOM2_1_Handler, /* 55 SERCOM2_1 */
    (void *)SERCOM2_2_Handler, /* 56 SERCOM2_2 */
    (void *)SERCOM2_3_Handler, /* 57 SERCOM2_3, SERCOM2_4, SERCOM2_5, SERCOM2_6 */
    (void *)SERCOM3_0_Handler, /* 58 SERCOM3_0 */
    (void *)SERCOM3_1_Handler, /* 59 SERCOM3_1 */
    (void *)SERCOM3_2_Handler, /* 60 SERCOM3_2 */
    (void *)SERCOM3_3_Handler, /* 61 SERCOM3_3, SERCOM3_4, SERCOM3_5, SERCOM3_6 */
#ifdef ID_SERCOM4
    (void *)SERCOM4_0_Handler, /* 62 SERCOM4_0 */
    (void *)SERCOM4_1_Handler, /* 63 SERCOM4_1 */
    (void *)SERCOM4_2_Handler, /* 64 SERCOM4_2 */
    (void *)SERCOM4_3_Handler, /* 65 SERCOM4_3, SERCOM4_4, SERCOM4_5, SERCOM4_6 */
#else
    (void *)(0UL), /* 62 Reserved */
    (void *)(0UL), /* 63 Reserved */
    (void *)(0UL), /* 64 Reserved */
    (void *)(0UL), /* 65 Reserved */
#endif
#ifdef ID_SERCOM5
    (void *)SERCOM5_0_Handler, /* 66 SERCOM5_0 */
    (void *)SERCOM5_1_Handler, /* 67 SERCOM5_1 */
    (void *)SERCOM5_2_Handler, /* 68 SERCOM5_2 */
    (void *)SERCOM5_3_Handler, /* 69 SERCOM5_3, SERCOM5_4, SERCOM5_5, SERCOM5_6 */
#else
    (void *)(0UL), /* 66 Reserved */
    (void *)(0UL), /* 67 Reserved */
    (void *)(0UL), /* 68 Reserved */
    (void *)(0UL), /* 69 Reserved */
#endif
#ifdef ID_SERCOM6
    (void *)SERCOM6_0_Handler, /* 70 SERCOM6_0 */
    (void *)SERCOM6_1_Handler, /* 71 SERCOM6_1 */
    (void *)SERCOM6_2_Handler, /* 72 SERCOM6_2 */
    (void *)SERCOM6_3_Handler, /* 73 SERCOM6_3, SERCOM6_4, SERCOM6_5, SERCOM6_6 */
#else
    (void *)(0UL), /* 70 Reserved */
    (void *)(0UL), /* 71 Reserved */
    (void *)(0UL), /* 72 Reserved */
    (void *)(0UL), /* 73 Reserved */
#endif
#ifdef ID_SERCOM7
    (void *)SERCOM7_0_Handler, /* 74 SERCOM7_0 */
    (void *)SERCOM7_1_Handler, /* 75 SERCOM7_1 */
    (void *)SERCOM7_2_Handler, /* 76 SERCOM7_2 */
    (void *)SERCOM7_3_Handler, /* 77 SERCOM7_3, SERCOM7_4, SERCOM7_5, SERCOM7_6 */
#else
    (void *)(0UL), /* 74 Reserved */
    (void *)(0UL), /* 75 Reserved */
    (void *)(0UL), /* 76 Reserved */
    (void *)(0UL), /* 77 Reserved */
#endif
#ifdef ID_CAN0
    (void *)CAN0_Handler, /* 78 Control Area Network 0 */
#else
    (void *)(0UL), /* 78 Reserved */
#endif
#ifdef ID_CAN1
    (void *)CAN1_Handler, /* 79 Control Area Network 1 */
#else
    (void *)(0UL), /* 79 Reserved */
#endif
#ifdef ID_USB
    (void *)USB_0_Handler, /* 80 USB_EORSM_DNRSM, USB_EORST_RST, USB_LPMSUSP_DDISC, USB_LPM_DCONN, USB_MSOF,
                              USB_RAMACER, USB_RXSTP_TXSTP_0, USB_RXSTP_TXSTP_1, USB_RXSTP_TXSTP_2, USB_RXSTP_TXSTP_3,
                              USB_RXSTP_TXSTP_4, USB_RXSTP_TXSTP_5, USB_RXSTP_TXSTP_6, USB_RXSTP_TXSTP_7,
                              USB_STALL0_STALL_0, USB_STALL0_STALL_1, USB_STALL0_STALL_2, USB_STALL0_STALL_3,
                              USB_STALL0_STALL_4, USB_STALL0_STALL_5, USB_STALL0_STALL_6, USB_STALL0_STALL_7,
                              USB_STALL1_0, USB_STALL1_1, USB_STALL1_2, USB_STALL1_3, USB_STALL1_4, USB_STALL1_5,
                              USB_STALL1_6, USB_STALL1_7, USB_SUSPEND, USB_TRFAIL0_TRFAIL_0, USB_TRFAIL0_TRFAIL_1,
                              USB_TRFAIL0_TRFAIL_2, USB_TRFAIL0_TRFAIL_3, USB_TRFAIL0_TRFAIL_4, USB_TRFAIL0_TRFAIL_5,
                              USB_TRFAIL0_TRFAIL_6, USB_TRFAIL0_TRFAIL_7, USB_TRFAIL1_PERR_0, USB_TRFAIL1_PERR_1,
                              USB_TRFAIL1_PERR_2, USB_TRFAIL1_PERR_3, USB_TRFAIL1_PERR_4, USB_TRFAIL1_PERR_5,
                              USB_TRFAIL1_PERR_6, USB_TRFAIL1_PERR_7, USB_UPRSM, USB_WAKEUP */
    (void *)USB_1_Handler, /* 81 USB_SOF_HSOF */
    (void *)USB_2_Handler, /* 82 USB_TRCPT0_0, USB_TRCPT0_1, USB_TRCPT0_2, USB_TRCPT0_3, USB_TRCPT0_4, USB_TRCPT0_5,
                              USB_TRCPT0_6, USB_TRCPT0_7 */
    (void *)USB_3_Handler, /* 83 USB_TRCPT1_0, USB_TRCPT1_1, USB_TRCPT1_2, USB_TRCPT1_3, USB_TRCPT1_4, USB_TRCPT1_5,
                              USB_TRCPT1_6, USB_TRCPT1_7 */
#else
    (void *)(0UL), /* 80 Reserved */
    (void *)(0UL), /* 81 Reserved */
    (void *)(0UL), /* 82 Reserved */
    (void *)(0UL), /* 83 Reserved */
#endif
#ifdef ID_GMAC
    (void *)GMAC_Handler, /* 84 Ethernet MAC */
#else
    (void *)(0UL), /* 84 Reserved */
#endif
    (void *)TCC0_0_Handler, /* 85 TCC0_CNT_A, TCC0_DFS_A, TCC0_ERR_A, TCC0_FAULT0_A, TCC0_FAULT1_A, TCC0_FAULTA_A,
                               TCC0_FAULTB_A, TCC0_OVF, TCC0_TRG, TCC0_UFS_A */
    (void *)TCC0_1_Handler, /* 86 TCC0_MC_0 */
    (void *)TCC0_2_Handler, /* 87 TCC0_MC_1 */
    (void *)TCC0_3_Handler, /* 88 TCC0_MC_2 */
    (void *)TCC0_4_Handler, /* 89 TCC0_MC_3 */
    (void *)TCC0_5_Handler, /* 90 TCC0_MC_4 */
    (void *)TCC0_6_Handler, /* 91 TCC0_MC_5 */
    (void *)TCC1_0_Handler, /* 92 TCC1_CNT_A, TCC1_DFS_A, TCC1_ERR_A, TCC1_FAULT0_A, TCC1_FAULT1_A, TCC1_FAULTA_A,
                               TCC1_FAULTB_A, TCC1_OVF, TCC1_TRG, TCC1_UFS_A */
    (void *)TCC1_1_Handler, /* 93 TCC1_MC_0 */
    (void *)TCC1_2_Handler, /* 94 TCC1_MC_1 */
    (void *)TCC1_3_Handler, /* 95 TCC1_MC_2 */
    (void *)TCC1_4_Handler, /* 96 TCC1_MC_3 */
    (void *)TCC2_0_Handler, /* 97 TCC2_CNT_A, TCC2_DFS_A, TCC2_ERR_A, TCC2_FAULT0_A, TCC2_FAULT1_A, TCC2_FAULTA_A,
                               TCC2_FAULTB_A, TCC2_OVF, TCC2_TRG, TCC2_UFS_A */
    (void *)TCC2_1_Handler, /* 98 TCC2_MC_0 */
    (void *)TCC2_2_Handler, /* 99 TCC2_MC_1 */
    (void *)TCC2_3_Handler, /* 100 TCC2_MC_2 */
#ifdef ID_TCC3
    (void *)TCC3_0_Handler, /* 101 TCC3_CNT_A, TCC3_DFS_A, TCC3_ERR_A, TCC3_FAULT0_A, TCC3_FAULT1_A, TCC3_FAULTA_A,
                               TCC3_FAULTB_A, TCC3_OVF, TCC3_TRG, TCC3_UFS_A */
    (void *)TCC3_1_Handler, /* 102 TCC3_MC_0 */
    (void *)TCC3_2_Handler, /* 103 TCC3_MC_1 */
#else
    (void *)(0UL), /* 101 Reserved */
    (void *)(0UL), /* 102 Reserved */
    (void *)(0UL), /* 103 Reserved */
#endif
#ifdef ID_TCC4
    (void *)TCC4_0_Handler, /* 104 TCC4_CNT_A, TCC4_DFS_A, TCC4_ERR_A, TCC4_FAULT0_A, TCC4_FAULT1_A, TCC4_FAULTA_A,
                               TCC4_FAULTB_A, TCC4_OVF, TCC4_TRG, TCC4_UFS_A */
    (void *)TCC4_1_Handler, /* 105 TCC4_MC_0 */
    (void *)TCC4_2_Handler, /* 106 TCC4_MC_1 */
#else
    (void *)(0UL), /* 104 Reserved */
    (void *)(0UL), /* 105 Reserved */
    (void *)(0UL), /* 106 Reserved */
#endif
    (void *)TC0_Handler, /* 107 Basic Timer Counter 0 */
    (void *)TC1_Handler, /* 108 Basic Timer Counter 1 */
    (void *)TC2_Handler, /* 109 Basic Timer Counter 2 */
    (void *)TC3_Handler, /* 110 Basic Timer Counter 3 */
#ifdef ID_TC4
    (void *)TC4_Handler, /* 111 Basic Timer Counter 4 */
#else
    (void *)(0UL), /* 111 Reserved */
#endif
#ifdef ID_TC5
    (void *)TC5_Handler, /* 112 Basic Timer Counter 5 */
#else
    (void *)(0UL), /* 112 Reserved */
#endif
#ifdef ID_TC6
    (void *)TC6_Handler, /* 113 Basic Timer Counter 6 */
#else
    (void *)(0UL), /* 113 Reserved */
#endif
#ifdef ID_TC7
    (void *)TC7_Handler, /* 114 Basic Timer Counter 7 */
#else
    (void *)(0UL), /* 114 Reserved */
#endif
    (void *)PDEC_0_Handler, /* 115 PDEC_DIR_A, PDEC_ERR_A, PDEC_OVF, PDEC_VLC_A */
    (void *)PDEC_1_Handler, /* 116 PDEC_MC_0 */
    (void *)PDEC_2_Handler, /* 117 PDEC_MC_1 */
    (void *)ADC0_0_Handler, /* 118 ADC0_OVERRUN, ADC0_WINMON */
    (void *)ADC0_1_Handler, /* 119 ADC0_RESRDY */
    (void *)ADC1_0_Handler, /* 120 ADC1_OVERRUN, ADC1_WINMON */
    (void *)ADC1_1_Handler, /* 121 ADC1_RESRDY */
    (void *)AC_Handler,     /* 122 Analog Comparators */
    (void *)DAC_0_Handler,  /* 123 DAC_OVERRUN_A_0, DAC_OVERRUN_A_1, DAC_UNDERRUN_A_0, DAC_UNDERRUN_A_1 */
    (void *)DAC_1_Handler,  /* 124 DAC_EMPTY_0 */
    (void *)DAC_2_Handler,  /* 125 DAC_EMPTY_1 */
    (void *)DAC_3_Handler,  /* 126 DAC_RESRDY_0 */
    (void *)DAC_4_Handler,  /* 127 DAC_RESRDY_1 */
#ifdef ID_I2S
    (void *)I2S_Handler, /* 128 Inter-IC Sound Interface */
#else
    (void *)(0UL), /* 128 Reserved */
#endif
    (void *)PCC_Handler,  /* 129 Parallel Capture Controller */
    (void *)AES_Handler,  /* 130 Advanced Encryption Standard */
    (void *)TRNG_Handler, /* 131 True Random Generator */
#ifdef ID_ICM
    (void *)ICM_Handler, /* 132 Integrity Check Monitor */
#else
    (void *)(0UL), /* 132 Reserved */
#endif
#ifdef ID_PUKCC
    (void *)PUKCC_Handler, /* 133 PUblic-Key Cryptography Controller */
#else
    (void *)(0UL), /* 133 Reserved */
#endif
    (void *)QSPI_Handler, /* 134 Quad SPI interface */
#ifdef ID_SDHC0
    (void *)SDHC0_Handler, /* 135 SD/MMC Host Controller 0 */
#else
    (void *)(0UL), /* 135 Reserved */
#endif
#ifdef ID_SDHC1
    (void *)SDHC1_Handler /* 136 SD/MMC Host Controller 1 */
#else
    (void *)(0UL)  /* 136 Reserved */
#endif
};

/**------------------------------------------------------------------------------
 * This is the code that gets called on processor reset. To initialize the
 * device.
 *------------------------------------------------------------------------------*/
int __low_level_init(void)
{
	uint32_t *pSrc = __section_begin(".intvec");

	SCB->VTOR = ((uint32_t)pSrc & SCB_VTOR_TBLOFF_Msk);

	return 1; /* if return 0, the data sections will not be initialized */
}

/**------------------------------------------------------------------------------
 * This is the code that gets called on processor reset. To initialize the
 * device.
 *------------------------------------------------------------------------------*/
void Reset_Handler(void)
{
	__iar_program_start();
}

/**
 * \brief Default interrupt handler for unused IRQs.
 */
void Dummy_Handler(void)
{
	while (1) {
	}
}
