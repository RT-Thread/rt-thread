/* generated configuration header file - do not edit */
#ifndef BSP_MCU_FAMILY_CFG_H_
#define BSP_MCU_FAMILY_CFG_H_
#include "bsp_mcu_device_pn_cfg.h"
#include "bsp_mcu_device_cfg.h"
#include "../../../ra/fsp/src/bsp/mcu/ra8p1/bsp_override.h"
#include "../../../ra/fsp/src/bsp/mcu/ra8p1/bsp_mcu_info.h"
#include "../../../ra/fsp/src/bsp/mcu/ra8p1/r_adc_device_types.h"
#include "bsp_clock_cfg.h"
#define BSP_MCU_GROUP_RA8P1 (1)
#define BSP_MCU_GROUP_RA8_GEN2 (1)

#define CPU0                                     (0)
#define CPU1                                     (1)

#if (_RA_CORE == CPU1)
                #define BSP_CFG_CPU_CORE                     (1)
                #define BSP_CFG_SKIP_INIT                    (1)
                #define BSP_SECONDARY_CORE_BUILD             (1)
            #else
#define BSP_CFG_CPU_CORE                     (0)
#endif

#define BSP_LOCO_HZ                 (32768)
#define BSP_MOCO_HZ                 (8000000)
#define BSP_SUB_CLOCK_HZ            (0)
#if   BSP_CFG_HOCO_FREQUENCY == 0
#define BSP_HOCO_HZ                 (16000000)
#elif BSP_CFG_HOCO_FREQUENCY == 1
                #define BSP_HOCO_HZ                 (18000000)
            #elif BSP_CFG_HOCO_FREQUENCY == 2
                #define BSP_HOCO_HZ                 (20000000)
            #elif BSP_CFG_HOCO_FREQUENCY == 4
                #define BSP_HOCO_HZ                 (32000000)
            #elif BSP_CFG_HOCO_FREQUENCY == 7
                #define BSP_HOCO_HZ                 (48000000)
            #else
                #error "Invalid HOCO frequency chosen (BSP_CFG_HOCO_FREQUENCY) in bsp_clock_cfg.h"
            #endif

#define BSP_CFG_FLL_ENABLE                   (0)

#define BSP_CFG_CLOCK_SETTLING_DELAY_ENABLE  (1)
#define BSP_CFG_SLEEP_MODE_DELAY_ENABLE      (1)
#define BSP_CFG_MSTP_CHANGE_DELAY_ENABLE     (1)
#define BSP_CFG_RTOS_SLEEP_MODE_DELAY_ENABLE (1)
#define BSP_CFG_CLOCK_SETTLING_DELAY_US      (30)

#if defined(BSP_PACKAGE_HLQFP)
                #define BSP_MAX_CLOCK_CHANGE_THRESHOLD (300000000U)
            #else
#define BSP_MAX_CLOCK_CHANGE_THRESHOLD (500000000U)
#endif

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

/* Type 1 Peripheral Security Attribution */

/* Peripheral Security Attribution Register (PSAR) Settings */
#ifndef BSP_TZ_CFG_PSARB
#define BSP_TZ_CFG_PSARB (\
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 4) /* I3C */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 7) /* IIC2 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 8) /* IIC1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 9) /* IIC0 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 11) /* USBFS */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 12) /* USBHS */ | \
            (1 << 16) /* OSPI0 */ | \
            (1 << 17) /* OSPI1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 18) /* SPI1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 19) /* SPI0 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 22) /* SCI9 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 23) /* SCI8 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 24) /* SCI7 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 25) /* SCI6 */ | \
            (((1 > 0) ? 0U : 1U) << 26) /* SCI5 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 27) /* SCI4 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 28) /* SCI3 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 29) /* SCI2 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 30) /* SCI1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 31) /* SCI0 */)
#endif
#ifndef BSP_TZ_CFG_PSARC
#define BSP_TZ_CFG_PSARC (\
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 0) /* CAC */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 1) /* CRC */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 7) /* SSIE1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 8) /* SSIE0 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 11) /* SDHI1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 12) /* SDHI0 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 13) /* DOC */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 15) /* GLCDC/MIPI-DSI/DRW */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 15) /* MIPI_CSI */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 16) /* CEU */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 24) /* PDM */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 26) /* CANFD1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 27) /* CANFD0 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 28) /* ETHPHYCLK */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 30) /* ESWM */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 31) /* RSIP-E50D */)
#endif
#ifndef BSP_TZ_CFG_PSARD
#define BSP_TZ_CFG_PSARD (\
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 4) /* AGT1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 5) /* AGT0 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 6)  /* PDG */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 11) /* PGI3 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 12) /* PGI2 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 13) /* PGI1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 14) /* PGI0 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 19) /* DAC121 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 20) /* DAC120 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 21) /* ADC_B */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 22) /* TSN */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 25) /* ACMPHS3 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 26) /* ACMPHS2 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 27) /* ACMPHS1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 28) /* ACMPHS0 */)
#endif
#ifndef BSP_TZ_CFG_PSARE
#define BSP_TZ_CFG_PSARE (\
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 0) /* WDT1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 1) /* WDT0 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 2) /* IWDT */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 3) /* RTC */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 8) /* ULPT1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 9) /* ULPT0 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 15) /* GPT COMMON */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 18) /* GPT13 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 19) /* GPT12 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 20) /* GPT11 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 21) /* GPT10 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 27) /* GPT4 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 28) /* GPT3 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 29) /* GPT2 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 30) /* GPT1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 31) /* GPT0 */)
#endif
#ifndef BSP_TZ_CFG_MSSAR
#define BSP_TZ_CFG_MSSAR (\
            (1U << 0) /* SRAM0 */ | \
            (1U << 1) /* SRAM1 */ | \
            (1U << 2) /* SRAM2 */ | \
            (1U << 3) /* SRAM3 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 16) /* NPU */ | \
            (1U << 22) /* DTC0_DMAC0 */ | \
            (1U << 23) /* DTC1_DMAC1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 31) /* ELC */)
#endif

/* Type 2 Peripheral Security Attribution */

/* Security attribution for RSTSRn registers. */
#ifndef BSP_TZ_CFG_RSTSAR
#define BSP_TZ_CFG_RSTSAR (0x0000000FU)
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

/* Security attribution for LPM registers.
 * - OPCCR based on clock security.
 * - Set remaining registers based on LPM security.
 */
#ifndef BSP_TZ_CFG_LPMSAR
#define BSP_TZ_CFG_LPMSAR ((RA_NOT_DEFINED > 0) ? BSP_CFG_CLOCKS_SECURE == 0 : (\
                                                  0x002E0116U | \
                                                  (BSP_CFG_CLOCKS_SECURE == 0)))
#endif
/* Deep Standby Interrupt Factor Security Attribution Register. */
#ifndef BSP_TZ_CFG_DPFSAR
#define BSP_TZ_CFG_DPFSAR ((RA_NOT_DEFINED > 0) ? 0U : 0xEF1FFFFFU)
#endif
/* Deep Standby Interrupt Factor Security Attribution Register 1. */
#ifndef BSP_TZ_CFG_DPFSAR1
#define BSP_TZ_CFG_DPFSAR1 ((RA_NOT_DEFINED > 0) ? 0U : 0x0000FFFFU)
#endif
/* RAM Standby Control Security Attribution Register. */
#ifndef BSP_TZ_CFG_RSCSAR
#define BSP_TZ_CFG_RSCSAR ((RA_NOT_DEFINED > 0) ? 0U : 0x00037FFFU)
#endif
/* Power Gating Control Security Attribution Register */
#ifndef BSP_TZ_CFG_PGCSAR
#define BSP_TZ_CFG_PGCSAR 0
#endif

/* Security attribution for CGC registers. */
#ifndef BSP_TZ_CFG_CGFSAR
#if BSP_CFG_CLOCKS_SECURE
/* Protect all CGC registers from Non-secure write access. */
#define BSP_TZ_CFG_CGFSAR (0U)
#else
/* Allow Secure and Non-secure write access. */
#define BSP_TZ_CFG_CGFSAR (0x1F7F7FFDU)
#endif
#endif

/* Security attribution for Battery Backup registers. */
#ifndef BSP_TZ_CFG_BBFSAR
#if 0
#define BSP_TZ_CFG_BBFSAR   (0U)
#else
#define BSP_TZ_CFG_BBFSAR   (0x7FU)
#endif
#endif

/* Security attribution for Battery Backup registers (VBTBKRn). */
#ifndef BSP_TZ_CFG_VBRSABAR
#if 0
#define BSP_TZ_CFG_VBRSABAR (0xFFE0)
#else
#define BSP_TZ_CFG_VBRSABAR (0xED00)
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
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 15U) /* External IRQ15 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 16U) /* External IRQ16 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 17U) /* External IRQ17 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 18U) /* External IRQ18 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 19U) /* External IRQ19 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 20U) /* External IRQ20 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 21U) /* External IRQ21 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 22U) /* External IRQ22 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 23U) /* External IRQ23 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 24U) /* External IRQ24 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 25U) /* External IRQ25 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 26U) /* External IRQ26 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 27U) /* External IRQ27 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 28U) /* External IRQ28 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 29U) /* External IRQ29 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 30U) /* External IRQ30 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 31U) /* External IRQ31 */)
#endif

/* Security attribution for NMI registers. */
#ifndef BSP_TZ_CFG_ICUSARB
#define BSP_TZ_CFG_ICUSARB (0 ? 7U : 0U) /* Should follow the secure attribution set in AIRCR.BFHFNMINS. */
#endif

/* Security attribution for registers for DMAC channels */
#ifndef BSP_TZ_CFG_DMACCHSAR
#if (0 == BSP_CFG_CPU_CORE)
#define BSP_TZ_CFG_DMACCHSAR (\
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 0U) /* DMAC Channel 0 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 1U) /* DMAC Channel 1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 2U) /* DMAC Channel 2 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 3U) /* DMAC Channel 3 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 4U) /* DMAC Channel 4 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 5U) /* DMAC Channel 5 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 6U) /* DMAC Channel 6 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 7U) /* DMAC Channel 7 */)
#else
#define BSP_TZ_CFG_DMACCHSAR (\
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 16U) /* DMAC1 Channel 0 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 17U) /* DMAC1 Channel 1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 18U) /* DMAC1 Channel 2 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 19U) /* DMAC1 Channel 3 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 20U) /* DMAC1 Channel 4 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 21U) /* DMAC1 Channel 5 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 22U) /* DMAC1 Channel 6 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 23U) /* DMAC1 Channel 7 */)
#endif
#endif

/* Security attribution registers for WUPEN0. */
#ifndef BSP_TZ_CFG_ICUSARE
#define BSP_TZ_CFG_ICUSARE ((RA_NOT_DEFINED > 0) ? 0U : 0xFF1D0000U)
#endif

/* Security attribution registers for WUPEN1. */
#ifndef BSP_TZ_CFG_ICUSARF
#define BSP_TZ_CFG_ICUSARF ((RA_NOT_DEFINED > 0) ? 0U : 0x0000FF88U)
#endif

/* Trusted Event Route Control Register for IELSR, DMAC.DELSR and ELC.ELSR. Note that currently Trusted Event Route Control is not supported. */
#ifndef BSP_TZ_CFG_TEVTRCR
#define BSP_TZ_CFG_TEVTRCR (0)
#endif

/* Security attribution register for ELCR, ELSEGR0, ELSEGR1, ELSEGR2, ELSEGR3 Security Attribution. */
#ifndef BSP_TZ_CFG_ELCSARA
#define BSP_TZ_CFG_ELCSARA (0x0000001FU)
#endif

/* Set DTCSTSAR if the Secure program uses the DTC. */
#if RA_NOT_DEFINED == RA_NOT_DEFINED
#define BSP_TZ_CFG_DTC_USED (0U)
#else
 #define BSP_TZ_CFG_DTC_USED (1U)
#endif

/* Security attribution for IPC */
#ifndef BSP_TZ_CFG_IPCSAR
#define BSP_TZ_CFG_IPCSAR (\
            ((0) << 0U) | /* SAIPCSEM0 */\
            ((0) << 1U) | /* SAIPCSEM1 */\
            ((0) << 8U) | /* SAIPCNMI0 */\
            ((0) << 9U) | /* SAIPCNMI1 */\
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 16U) /* IPC 00 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 17U) /* IPC 01 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 18U) /* IPC 10 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 19U) /* IPC 11 */)
#endif

/* Security attribution of MRAM registers. */
#ifndef BSP_TZ_CFG_MSAR
#define BSP_TZ_CFG_MSAR (\
        ((BSP_CFG_CLOCKS_SECURE == 0) ? (1U << 1) : 0U) | /* MREFREQ */\
        ((BSP_CFG_CLOCKS_SECURE == 0) ? (1U << 3) : 0U) | /* MRCFREQ */\
        ((BSP_CFG_CLOCKS_SECURE == 0) ? (1U << 4) : 0U) /* MRCPFB */)
#endif

/* Security attribution for SRAM registers. */
#ifndef BSP_TZ_CFG_SRAMSAR
/* If the CGC registers are only accessible in Secure mode, than there is no reason for Non Secure applications to access
 * SRAM0WTEN and therefore there is no reason to access PRCR2. */
#define BSP_TZ_CFG_SRAMSAR (\
        ((1U) << 0U) | /* SRAMSA0 */\
        ((1U) << 1U) | /* SRAMSA1 */\
        ((1U) << 2U) | /* SRAMSA2 */\
        ((1U) << 3U) | /* SRAMSA3 */\
        ((BSP_CFG_CLOCKS_SECURE == 0) ? (1U << 8U) : 0U) /* SRAMWTSA */)
#endif

/* SRAM ECC Region Security Attribution Register. */
#ifndef BSP_TZ_CFG_SRAMESAR
#define BSP_TZ_CFG_SRAMESAR     (0x1U)
#endif

/* Security attribution for the DMAC Bus Master MPU settings. */
#ifndef BSP_TZ_CFG_MMPUSARA
/* The DMAC Bus Master MPU settings should align with the DMAC channel settings. */
#define BSP_TZ_CFG_MMPUSARA (BSP_TZ_CFG_DMACCHSAR)
#endif

/* Security Attribution Register A for BUS Control registers. */
#ifndef BSP_TZ_CFG_BUSSARA
#define BSP_TZ_CFG_BUSSARA (1U)
#endif
/* Security Attribution Register B for BUS Control registers. */
#ifndef BSP_TZ_CFG_BUSSARB
#define BSP_TZ_CFG_BUSSARB (1U)
#endif
/* Security Attribution Register C for BUS Control registers. */
#ifndef BSP_TZ_CFG_BUSSARC
#define BSP_TZ_CFG_BUSSARC (1U)
#endif

/* Enable Uninitialized Non-Secure Application Fallback. */
#ifndef BSP_TZ_CFG_NON_SECURE_APPLICATION_FALLBACK
#define BSP_TZ_CFG_NON_SECURE_APPLICATION_FALLBACK (1U)
#endif

/* Security attribution for Cache registers. */
#ifndef BSP_TZ_CFG_CACHESAR
#define BSP_TZ_CFG_CACHESAR (0x00000000U)
#endif

/* Used to create IELS values for the interrupt initialization table g_interrupt_event_link_select. */
#define BSP_PRV_IELS_ENUM(vector)    (ELC_ ## vector)

#ifndef BSP_CLOCK_CFG_MAIN_OSC_WAIT
#define BSP_CLOCK_CFG_MAIN_OSC_WAIT (9)
#endif

#ifndef BSP_CFG_DCACHE_ENABLED
#if (0U == BSP_CFG_CPU_CORE)
#define BSP_CFG_DCACHE_ENABLED (0)
#else
    #define BSP_CFG_DCACHE_ENABLED (0)
 #endif
#endif

#ifndef BSP_CFG_DCACHE_FORCE_WRITETHROUGH
#if (0U == BSP_CFG_CPU_CORE)
#define BSP_CFG_DCACHE_FORCE_WRITETHROUGH (0)
#else
    #define BSP_CFG_DCACHE_FORCE_WRITETHROUGH (0)
 #endif
#endif

#ifndef BSP_CFG_SDRAM_ENABLED
#define BSP_CFG_SDRAM_ENABLED  (0)
#endif

#ifndef BSP_CFG_SDRAM_TRAS
#define BSP_CFG_SDRAM_TRAS  (6)
#endif

#ifndef BSP_CFG_SDRAM_TRCD
#define BSP_CFG_SDRAM_TRCD  (3)
#endif

#ifndef BSP_CFG_SDRAM_TRP
#define BSP_CFG_SDRAM_TRP  (3)
#endif

#ifndef BSP_CFG_SDRAM_TWR
#define BSP_CFG_SDRAM_TWR  (2)
#endif

#ifndef BSP_CFG_SDRAM_TCL
#define BSP_CFG_SDRAM_TCL  (3)
#endif

#ifndef BSP_CFG_SDRAM_TRFC
#define BSP_CFG_SDRAM_TRFC  (937)
#endif

#ifndef BSP_CFG_SDRAM_TREFW
#define BSP_CFG_SDRAM_TREFW  (8)
#endif

#ifndef BSP_CFG_SDRAM_INIT_ARFI
#define BSP_CFG_SDRAM_INIT_ARFI  (10)
#endif

#ifndef BSP_CFG_SDRAM_INIT_ARFC
#define BSP_CFG_SDRAM_INIT_ARFC  (8)
#endif

#ifndef BSP_CFG_SDRAM_INIT_PRC
#define BSP_CFG_SDRAM_INIT_PRC  (3)
#endif

#ifndef BSP_CFG_SDRAM_MULTIPLEX_ADDR_SHIFT
#define BSP_CFG_SDRAM_MULTIPLEX_ADDR_SHIFT  (1)
#endif

#ifndef BSP_CFG_SDRAM_ENDIAN_MODE
#define BSP_CFG_SDRAM_ENDIAN_MODE  (0)
#endif

#ifndef BSP_CFG_SDRAM_ACCESS_MODE
#define BSP_CFG_SDRAM_ACCESS_MODE  (1)
#endif

#ifndef BSP_CFG_SDRAM_BUS_WIDTH
#define BSP_CFG_SDRAM_BUS_WIDTH  (1)
#endif
#endif /* BSP_MCU_FAMILY_CFG_H_ */
