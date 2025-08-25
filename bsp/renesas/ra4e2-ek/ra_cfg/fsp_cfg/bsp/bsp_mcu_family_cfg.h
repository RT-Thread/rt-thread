/* generated configuration header file - do not edit */
#ifndef BSP_MCU_FAMILY_CFG_H_
#define BSP_MCU_FAMILY_CFG_H_
#ifdef __cplusplus
extern "C" {
#endif

            #include "bsp_mcu_device_pn_cfg.h"
            #include "bsp_mcu_device_cfg.h"
            #include "../../../ra/fsp/src/bsp/mcu/ra4e2/bsp_mcu_info.h"
            #include "bsp_clock_cfg.h"
            #define BSP_MCU_GROUP_RA4E2 (1)
            #define BSP_LOCO_HZ                 (32768)
            #define BSP_MOCO_HZ                 (8000000)
            #define BSP_SUB_CLOCK_HZ            (32768)
            #if   BSP_CFG_HOCO_FREQUENCY == 0
                #define BSP_HOCO_HZ                 (16000000)
            #elif BSP_CFG_HOCO_FREQUENCY == 1
                #define BSP_HOCO_HZ                 (18000000)
            #elif BSP_CFG_HOCO_FREQUENCY == 2
                #define BSP_HOCO_HZ                 (20000000)
            #else
                #error "Invalid HOCO frequency chosen (BSP_CFG_HOCO_FREQUENCY) in bsp_clock_cfg.h"
            #endif

            #define BSP_CFG_FLL_ENABLE                 (0)

            #define BSP_CORTEX_VECTOR_TABLE_ENTRIES    (16U)
            #define BSP_VECTOR_TABLE_MAX_ENTRIES       (112U)
            #define BSP_CFG_INLINE_IRQ_FUNCTIONS       (1)

            #if defined(_RA_TZ_SECURE)
            #define BSP_TZ_SECURE_BUILD           (1)
            #define BSP_TZ_NONSECURE_BUILD        (0)
            #elif defined(_RA_TZ_NONSECURE)
            #define BSP_TZ_SECURE_BUILD           (0)
            #define BSP_TZ_NONSECURE_BUILD        (1)
            #else
            #define BSP_TZ_SECURE_BUILD           (0)
            #define BSP_TZ_NONSECURE_BUILD        (0)
            #endif

            /* TrustZone Settings */
            #define BSP_TZ_CFG_INIT_SECURE_ONLY       (BSP_CFG_CLOCKS_SECURE || (!BSP_CFG_CLOCKS_OVERRIDE))
            #define BSP_TZ_CFG_SKIP_INIT              (BSP_TZ_NONSECURE_BUILD && BSP_TZ_CFG_INIT_SECURE_ONLY)
            #define BSP_TZ_CFG_EXCEPTION_RESPONSE     (0)

            /* CMSIS TrustZone Settings */
            #define SCB_CSR_AIRCR_INIT                (1)
            #define SCB_AIRCR_BFHFNMINS_VAL           (0)
            #define SCB_AIRCR_SYSRESETREQS_VAL        (1)
            #define SCB_AIRCR_PRIS_VAL                (0)
            #define TZ_FPU_NS_USAGE                   (1)
#ifndef SCB_NSACR_CP10_11_VAL
            #define SCB_NSACR_CP10_11_VAL             (3U)
#endif

#ifndef FPU_FPCCR_TS_VAL
            #define FPU_FPCCR_TS_VAL                  (1U)
#endif
            #define FPU_FPCCR_CLRONRETS_VAL           (1)

#ifndef FPU_FPCCR_CLRONRET_VAL
            #define FPU_FPCCR_CLRONRET_VAL            (1)
#endif

            /* The C-Cache line size that is configured during startup. */
#ifndef BSP_CFG_C_CACHE_LINE_SIZE
            #define BSP_CFG_C_CACHE_LINE_SIZE   (1U)
#endif

            /* Type 1 Peripheral Security Attribution */

            /* Peripheral Security Attribution Register (PSAR) Settings */
#ifndef BSP_TZ_CFG_PSARB
#define BSP_TZ_CFG_PSARB (\
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 3) /* CEC */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 4) /* I3C0 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 11) /* USBFS */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 18) /* SPI1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 19) /* SPI0 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 22) /* SCI9 */ | \
            (((1 > 0) ? 0U : 1U) << 31) /* SCI0 */ | \
            0x7FB3F7E7) /* Unused */
#endif
#ifndef BSP_TZ_CFG_PSARC
#define BSP_TZ_CFG_PSARC (\
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 0) /* CAC */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 1) /* CRC */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 8) /* SSIE0 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 13) /* DOC */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 20) /* TFU */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 27) /* CANFD0 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 28) /* TRNG */ | \
            0xE7FFDEFC) /* Unused */
#endif
#ifndef BSP_TZ_CFG_PSARD
#define BSP_TZ_CFG_PSARD (\
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 2) /* AGT1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 3) /* AGT0 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 11) /* POEG3 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 12) /* POEG2 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 13) /* POEG1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 14) /* POEG0 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 16) /* ADC0 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 20) /* DAC */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 22) /* TSN */ | \
            0xFFAE87F3) /* Unused */
#endif
#ifndef BSP_TZ_CFG_PSARE
#define BSP_TZ_CFG_PSARE (\
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 0) /* WDT */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 1) /* IWDT */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 2) /* RTC */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 26) /* GPT5 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 27) /* GPT4 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 30) /* GPT1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 31) /* GPT0 */ | \
            0x33FFFFF8) /* Unused */
#endif
#ifndef BSP_TZ_CFG_MSSAR
#define BSP_TZ_CFG_MSSAR (\
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 0) /* ELC */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 1) /* DTC_DMAC */ | \
            0xfffffffc) /* Unused */
#endif

            /* Type 2 Peripheral Security Attribution */

            /* Security attribution for Cache registers. */
#ifndef BSP_TZ_CFG_CSAR
#define BSP_TZ_CFG_CSAR (0xFFFFFFFFU)
#endif

            /* Security attribution for RSTSRn registers. */
#ifndef BSP_TZ_CFG_RSTSAR
#define BSP_TZ_CFG_RSTSAR (0xFFFFFFFFU)
#endif

            /* Security attribution for registers of LVD channels. */
#ifndef BSP_TZ_CFG_LVDSAR
            /* The LVD driver needs to access both channels. This means that the security attribution for both channels must be the same. */
#if (RA_NOT_DEFINED > 0) || (RA_NOT_DEFINED > 0)
#define BSP_TZ_CFG_LVDSAR (0U)
#else
#define BSP_TZ_CFG_LVDSAR (3U)
#endif
#endif

            /* Security attribution for LPM registers. */
#ifndef BSP_TZ_CFG_LPMSAR
#define BSP_TZ_CFG_LPMSAR ((RA_NOT_DEFINED > 0) ? 0xFFFFDCEAU : 0xFFFFFFFFU)
#endif
            /* Deep Standby Interrupt Factor Security Attribution Register. */
#ifndef BSP_TZ_CFG_DPFSAR
#define BSP_TZ_CFG_DPFSAR ((RA_NOT_DEFINED > 0) ? 0xFAE0A00CU : 0xFFFFFFFFU)
#endif

            /* Security attribution for CGC registers. */
#ifndef BSP_TZ_CFG_CGFSAR
#if BSP_CFG_CLOCKS_SECURE
/* Protect all CGC registers from Non-secure write access. */
#define BSP_TZ_CFG_CGFSAR (0xFFEAF602U)
#else
/* Allow Secure and Non-secure write access. */
#define BSP_TZ_CFG_CGFSAR (0xFFFFFFFFU)
#endif
#endif

            /* Security attribution for registers for IRQ channels. */
#ifndef BSP_TZ_CFG_ICUSARA
#define BSP_TZ_CFG_ICUSARA (\
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 0U) /* External IRQ0 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 1U) /* External IRQ1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 2U) /* External IRQ2 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 3U) /* External IRQ3 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 4U) /* External IRQ4 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 5U) /* External IRQ5 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 6U) /* External IRQ6 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 7U) /* External IRQ7 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 8U) /* External IRQ8 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 9U) /* External IRQ9 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 10U) /* External IRQ10 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 11U) /* External IRQ11 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 12U) /* External IRQ12 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 13U) /* External IRQ13 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 14U) /* External IRQ14 */ | \
            0xFFFF8000U)
#endif

            /* Security attribution for NMI registers. */
#ifndef BSP_TZ_CFG_ICUSARB
#define BSP_TZ_CFG_ICUSARB (0 | 0xFFFFFFFEU) /* Should match AIRCR.BFHFNMINS. */
#endif

            /* Security attribution for registers for DMAC channels */
#ifndef BSP_TZ_CFG_ICUSARC
#define BSP_TZ_CFG_ICUSARC (\
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 0U) /* DMAC Channel 0 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 1U) /* DMAC Channel 1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 2U) /* DMAC Channel 2 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 3U) /* DMAC Channel 3 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 4U) /* DMAC Channel 4 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 5U) /* DMAC Channel 5 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 6U) /* DMAC Channel 6 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 7U) /* DMAC Channel 7 */ | \
            0xFFFFFF00U)
#endif

            /* Security attribution registers for SELSR0. */
#ifndef BSP_TZ_CFG_ICUSARD
#define BSP_TZ_CFG_ICUSARD ((RA_NOT_DEFINED > 0) ? 0xFFFFFFFEU : 0xFFFFFFFFU)
#endif

            /* Security attribution registers for WUPEN0. */
#ifndef BSP_TZ_CFG_ICUSARE
#define BSP_TZ_CFG_ICUSARE ((RA_NOT_DEFINED > 0) ? 0x84F2FFFFU : 0xFFFFFFFFU)
#endif

            /* Security attribution registers for WUPEN1. */
#ifndef BSP_TZ_CFG_ICUSARF
#define BSP_TZ_CFG_ICUSARF ((RA_NOT_DEFINED > 0) ? 0xFFFFF7FFU : 0xFFFFFFFFU)
#endif

            /* Set DTCSTSAR if the Secure program uses the DTC. */
#if RA_NOT_DEFINED == RA_NOT_DEFINED
 #define BSP_TZ_CFG_DTC_USED (0U)
#else
 #define BSP_TZ_CFG_DTC_USED (1U)
#endif

            /* Security attribution of FLWT and FCKMHZ registers. */
#ifndef BSP_TZ_CFG_FSAR
/* If the CGC registers are only accessible in Secure mode, than there is no
 * reason for nonsecure applications to access FLWT and FCKMHZ. */
#if BSP_CFG_CLOCKS_SECURE
/* Protect FLWT and FCKMHZ registers from nonsecure write access. */
#define BSP_TZ_CFG_FSAR (0xFEFEU)
#else
/* Allow Secure and Non-secure write access. */
#define BSP_TZ_CFG_FSAR (0xFFFFU)
#endif
#endif

            /* Security attribution for SRAM registers. */
#ifndef BSP_TZ_CFG_SRAMSAR
/* If the CGC registers are only accessible in Secure mode, than there is no reason for Non Secure applications to access
 * SRAM0WTEN and therefore there is no reason to access PRCR2. */
    #define BSP_TZ_CFG_SRAMSAR (\
        1 | \
        ((BSP_CFG_CLOCKS_SECURE == 0) ? (1U << 1U) : 0U) | \
        4 | \
        0xFFFFFFF8U)
#endif

            /* Security attribution for Standby RAM registers. */
#ifndef BSP_TZ_CFG_STBRAMSAR
    #define BSP_TZ_CFG_STBRAMSAR (0 | 0xFFFFFFF0U)
#endif

            /* Security attribution for the DMAC Bus Master MPU settings. */
#ifndef BSP_TZ_CFG_MMPUSARA
    /* The DMAC Bus Master MPU settings should align with the DMAC channel settings. */
    #define BSP_TZ_CFG_MMPUSARA (BSP_TZ_CFG_ICUSARC)
#endif

            /* Security Attribution Register A for BUS Control registers. */
#ifndef BSP_TZ_CFG_BUSSARA
    #define BSP_TZ_CFG_BUSSARA (0xFFFFFFFFU)
#endif
            /* Security Attribution Register B for BUS Control registers. */
#ifndef BSP_TZ_CFG_BUSSARB
    #define BSP_TZ_CFG_BUSSARB (0xFFFFFFFFU)
#endif

            /* Enable Uninitialized Non-Secure Application Fallback. */
#ifndef BSP_TZ_CFG_NON_SECURE_APPLICATION_FALLBACK
    #define BSP_TZ_CFG_NON_SECURE_APPLICATION_FALLBACK (1U)
#endif
            /* Used to create IELS values for the interrupt initialization table g_interrupt_event_link_select. */
            #define BSP_PRV_IELS_ENUM(vector)    (ELC_ ## vector)

#ifndef BSP_CLOCK_CFG_MAIN_OSC_WAIT
            #define BSP_CLOCK_CFG_MAIN_OSC_WAIT (9)
#endif


#ifdef __cplusplus
}
#endif
#endif /* BSP_MCU_FAMILY_CFG_H_ */
