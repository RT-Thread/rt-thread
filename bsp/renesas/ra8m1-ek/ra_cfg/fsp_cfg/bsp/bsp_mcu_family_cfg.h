/* generated configuration header file - do not edit */
#ifndef BSP_MCU_FAMILY_CFG_H_
#define BSP_MCU_FAMILY_CFG_H_
#include "bsp_mcu_device_pn_cfg.h"
            #include "bsp_mcu_device_cfg.h"
            #include "../../../ra/fsp/src/bsp/mcu/ra8m1/bsp_override.h"
            #include "../../../ra/fsp/src/bsp/mcu/ra8m1/bsp_mcu_info.h"
            #include "bsp_clock_cfg.h"
            #define BSP_MCU_GROUP_RA8M1 (1)
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
            #define BSP_CFG_CLOCK_SETTLING_DELAY_US      (150)

            #if defined(BSP_PACKAGE_LQFP) && (BSP_PACKAGE_PINS == 100)
                #define BSP_MAX_CLOCK_CHANGE_THRESHOLD (180000000U)
            #elif defined(BSP_PACKAGE_LQFP)
                #define BSP_MAX_CLOCK_CHANGE_THRESHOLD (200000000U)
            #else
                #define BSP_MAX_CLOCK_CHANGE_THRESHOLD (240000000U)
            #endif

            #define BSP_CORTEX_VECTOR_TABLE_ENTRIES    (16U)
            #define BSP_VECTOR_TABLE_MAX_ENTRIES       (112U)

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
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 8) /* IIC1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 9) /* IIC0 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 11) /* USBFS */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 12) /* USBHS */ | \
            (1 << 15) /* ETHERC/EDMAC */ | \
            (1 << 16) /* OSPI */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 18) /* SPI1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 19) /* SPI0 */ | \
            (((1 > 0) ? 0U : 1U) << 22) /* SCI9 */ | \
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
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 16) /* CEU */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 26) /* CANFD1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 27) /* CANFD0 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 31) /* RSIP7 */)
#endif
#ifndef BSP_TZ_CFG_PSARD
#define BSP_TZ_CFG_PSARD (\
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 4) /* AGT1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 5) /* AGT0 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 11) /* POEG3 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 12) /* POEG2 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 13) /* POEG1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 14) /* POEG0 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 15) /* ADC121 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 16) /* ADC120 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 20) /* DAC120 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 22) /* TSN */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 27) /* ACMPHS1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 28) /* ACMPHS0 */)
#endif
#ifndef BSP_TZ_CFG_PSARE
#define BSP_TZ_CFG_PSARE (\
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 1) /* WDT */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 2) /* IWDT */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 3) /* RTC */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 8) /* ULPT1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 9) /* ULPT0 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 18) /* GPT13 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 19) /* GPT12 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 20) /* GPT11 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 21) /* GPT10 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 22) /* GPT9 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 23) /* GPT8 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 24) /* GPT7 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 25) /* GPT6 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 26) /* GPT5 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 27) /* GPT4 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 28) /* GPT3 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 29) /* GPT2 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 30) /* GPT1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 31) /* GPT0 */)
#endif
#ifndef BSP_TZ_CFG_MSSAR
#define BSP_TZ_CFG_MSSAR (\
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 22) /* DTC_DMAC */ | \
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
                                                  0x002E0106U | \
                                                  (BSP_CFG_CLOCKS_SECURE == 0)))
#endif
            /* Deep Standby Interrupt Factor Security Attribution Register. */
#ifndef BSP_TZ_CFG_DPFSAR
#define BSP_TZ_CFG_DPFSAR ((RA_NOT_DEFINED > 0) ? 0U : 0xAF1FFFFFU)
#endif
            /* RAM Standby Control Security Attribution Register. */
#ifndef BSP_TZ_CFG_RSCSAR
#define BSP_TZ_CFG_RSCSAR ((RA_NOT_DEFINED > 0) ? 0U : 0x00037FFFU)
#endif

            /* Security attribution for CGC registers. */
#ifndef BSP_TZ_CFG_CGFSAR
#if BSP_CFG_CLOCKS_SECURE
/* Protect all CGC registers from Non-secure write access. */
#define BSP_TZ_CFG_CGFSAR (0U)
#else
/* Allow Secure and Non-secure write access. */
#define BSP_TZ_CFG_CGFSAR (0x047F3BFDU)
#endif
#endif

            /* Security attribution for Battery Backup registers. */
#ifndef BSP_TZ_CFG_BBFSAR
#define BSP_TZ_CFG_BBFSAR (0x0000001FU)
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
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 15U) /* External IRQ15 */)
#endif

            /* Security attribution for NMI registers. */
#ifndef BSP_TZ_CFG_ICUSARB
#define BSP_TZ_CFG_ICUSARB (0 | 0xFFFFFFFEU) /* Should match AIRCR.BFHFNMINS. */
#endif

            /* Security attribution for registers for DMAC channels */
#ifndef BSP_TZ_CFG_DMACCHSAR
#define BSP_TZ_CFG_DMACCHSAR (\
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 0U) /* DMAC Channel 0 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 1U) /* DMAC Channel 1 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 2U) /* DMAC Channel 2 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 3U) /* DMAC Channel 3 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 4U) /* DMAC Channel 4 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 5U) /* DMAC Channel 5 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 6U) /* DMAC Channel 6 */ | \
            (((RA_NOT_DEFINED > 0) ? 0U : 1U) << 7U) /* DMAC Channel 7 */)
#endif

            /* Security attribution registers for WUPEN0. */
#ifndef BSP_TZ_CFG_ICUSARE
#define BSP_TZ_CFG_ICUSARE ((RA_NOT_DEFINED > 0) ? 0U : 0xFF1D0000U)
#endif

            /* Security attribution registers for WUPEN1. */
#ifndef BSP_TZ_CFG_ICUSARF
#define BSP_TZ_CFG_ICUSARF ((RA_NOT_DEFINED > 0) ? 0U : 0x00007F08U)
#endif

            /* Trusted Event Route Control Register for IELSR, DMAC.DELSR and ELC.ELSR. Note that currently Trusted Event Route Control is not supported. */
#ifndef BSP_TZ_CFG_TEVTRCR
#define BSP_TZ_CFG_TEVTRCR (0)
#endif

            /* Security attribution register for ELCR, ELSEGR0, ELSEGR1 Security Attribution. */
#ifndef BSP_TZ_CFG_ELCSARA
 #define BSP_TZ_CFG_ELCSARA (0x00000007U)
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
#define BSP_TZ_CFG_FSAR (\
        ((BSP_CFG_CLOCKS_SECURE == 0) ? (1U << 0) : 0U) | /* FLWTSA */\
        ((RA_NOT_DEFINED) > 0 ? 0U: (1U << 1)) | /* FCACHESA */\
        ((BSP_CFG_CLOCKS_SECURE == 0) ? (1U << 8) : 0U) | /* FCKMHZSA */ \
        ((RA_NOT_DEFINED) > 0 ? 0U : (1U << 9U)) | /* FACICMISA */\
        ((RA_NOT_DEFINED) > 0 ? 0U: (1U << 10U)) /* FACICMRSA */)
#endif

            /* Security attribution for SRAM registers. */
#ifndef BSP_TZ_CFG_SRAMSAR
/* If the CGC registers are only accessible in Secure mode, than there is no reason for Non Secure applications to access
 * SRAM0WTEN and therefore there is no reason to access PRCR2. */
    #define BSP_TZ_CFG_SRAMSAR (\
        ((1U) << 0U) | /* SRAMSA0 */\
        ((1U) << 1U) | /* SRAMSA1 */\
        ((1U) << 7U) | /* STBRAMSA */\
        ((BSP_CFG_CLOCKS_SECURE == 0) ? (1U << 8U) : 0U) /* SRAMWTSA */)
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


            #define OFS_SEQ1 0xA001A001 | (1 << 1) | (3 << 2)
            #define OFS_SEQ2 (15 << 4) | (3 << 8) | (3 << 10)
            #define OFS_SEQ3 (1 << 12) | (1 << 14) | (1 << 17)
            #define OFS_SEQ4 (3 << 18) |(15 << 20) | (3 << 24) | (3 << 26)
            #define OFS_SEQ5 (1 << 28) | (1 << 30)
            #define BSP_CFG_ROM_REG_OFS0 (OFS_SEQ1 | OFS_SEQ2 | OFS_SEQ3 | OFS_SEQ4 | OFS_SEQ5)

            #define BSP_CFG_ROM_REG_OFS2 ((1 << 0) | 0xFFFFFFFEU)

            /* Option Function Select Register 1 Security Attribution */
#ifndef BSP_CFG_ROM_REG_OFS1_SEL
#if defined(_RA_TZ_SECURE) || defined(_RA_TZ_NONSECURE)
            #define BSP_CFG_ROM_REG_OFS1_SEL (0x00000000U | ((0U << 0U)) | ((0U << 3U)) | ((0U << 5U)) | ((BSP_CFG_CLOCKS_SECURE == 0) ? 0xF00U : 0U) | ((0U << 24U)) | ((0U << 25U)))
#else
            #define BSP_CFG_ROM_REG_OFS1_SEL (0x00000000U)
#endif
#endif
            #define BSP_CFG_ROM_REG_OFS1_INITECCEN (1 << 25)
            #define BSP_CFG_ROM_REG_OFS1 (0xFCFFFED0 | (1 << 3) | (7) | (1 << 5) |  (1 << 8) | (1 << 24) | (BSP_CFG_ROM_REG_OFS1_INITECCEN))

            /* Used to create IELS values for the interrupt initialization table g_interrupt_event_link_select. */
            #define BSP_PRV_IELS_ENUM(vector)    (ELC_ ## vector)

            /* Dual Mode Select Register */
#ifndef BSP_CFG_ROM_REG_DUALSEL
            #define BSP_CFG_ROM_REG_DUALSEL (0xFFFFFFF8U | (0x7U))
#endif

            /* Block Protection Register 0 */
#ifndef BSP_CFG_ROM_REG_BPS0
            #define BSP_CFG_ROM_REG_BPS0 (~( 0U))
#endif
            /* Block Protection Register 1 */
#ifndef BSP_CFG_ROM_REG_BPS1
            #define BSP_CFG_ROM_REG_BPS1 (~( 0U))
#endif
            /* Block Protection Register 2 */
#ifndef BSP_CFG_ROM_REG_BPS2
            #define BSP_CFG_ROM_REG_BPS2 (~( 0U))
#endif
            /* Block Protection Register 3 */
#ifndef BSP_CFG_ROM_REG_BPS3
            #define BSP_CFG_ROM_REG_BPS3 (~( 0U))
#endif
            /* Permanent Block Protection Register 0 */
#ifndef BSP_CFG_ROM_REG_PBPS0
            #define BSP_CFG_ROM_REG_PBPS0 (~( 0U))
#endif
            /* Permanent Block Protection Register 1 */
#ifndef BSP_CFG_ROM_REG_PBPS1
            #define BSP_CFG_ROM_REG_PBPS1 (~( 0U))
#endif
            /* Permanent Block Protection Register 2 */
#ifndef BSP_CFG_ROM_REG_PBPS2
            #define BSP_CFG_ROM_REG_PBPS2 (~( 0U))
#endif
            /* Permanent Block Protection Register 3 */
#ifndef BSP_CFG_ROM_REG_PBPS3
            #define BSP_CFG_ROM_REG_PBPS3 (~( 0U))
#endif
            /* Security Attribution for Block Protection Register 0 (If any blocks are marked as protected in the secure application, then mark them as secure) */
#ifndef BSP_CFG_ROM_REG_BPS_SEL0
            #define BSP_CFG_ROM_REG_BPS_SEL0 (BSP_CFG_ROM_REG_BPS0 & BSP_CFG_ROM_REG_PBPS0)
#endif
            /* Security Attribution for Block Protection Register 1 (If any blocks are marked as protected in the secure application, then mark them as secure) */
#ifndef BSP_CFG_ROM_REG_BPS_SEL1
            #define BSP_CFG_ROM_REG_BPS_SEL1 (BSP_CFG_ROM_REG_BPS1 & BSP_CFG_ROM_REG_PBPS1)
#endif
            /* Security Attribution for Block Protection Register 2 (If any blocks are marked as protected in the secure application, then mark them as secure) */
#ifndef BSP_CFG_ROM_REG_BPS_SEL2
            #define BSP_CFG_ROM_REG_BPS_SEL2 (BSP_CFG_ROM_REG_BPS2 & BSP_CFG_ROM_REG_PBPS2)
#endif
            /* Security Attribution for Block Protection Register 3 (If any blocks are marked as protected in the secure application, then mark them as secure) */
#ifndef BSP_CFG_ROM_REG_BPS_SEL3
            #define BSP_CFG_ROM_REG_BPS_SEL3 (BSP_CFG_ROM_REG_BPS3 & BSP_CFG_ROM_REG_PBPS3)
#endif
            /* Security Attribution for Bank Select Register */
#ifndef BSP_CFG_ROM_REG_BANKSEL_SEL
            #define BSP_CFG_ROM_REG_BANKSEL_SEL (0xFFFFFFFFU)
#endif
#ifndef BSP_CLOCK_CFG_MAIN_OSC_WAIT
            #define BSP_CLOCK_CFG_MAIN_OSC_WAIT (9)
#endif

            /* FSBL Control Register 0 */
#ifndef BSP_CFG_ROM_REG_FSBLCTRL0
#define BSP_CFG_ROM_REG_FSBLCTRL0 ( \
                (7 << R_OFS_DATAFLASH_FSBLCTRL0_FSBLEN_Pos) | \
                (7 << R_OFS_DATAFLASH_FSBLCTRL0_FSBLSKIPSW_Pos) | \
                (7 << R_OFS_DATAFLASH_FSBLCTRL0_FSBLSKIPDS_Pos) | \
                (7 << R_OFS_DATAFLASH_FSBLCTRL0_FSBLCLK_Pos) | \
                0xFFFFF000)
#endif

            /* FSBL Control Register 1 */
#ifndef BSP_CFG_ROM_REG_FSBLCTRL1
#define BSP_CFG_ROM_REG_FSBLCTRL1 ( \
                (3 << R_OFS_DATAFLASH_FSBLCTRL1_FSBLEXMD_Pos) | \
                0xFFFFFFFC)
#endif

            /* FSBL Control Register 2 */
#ifndef BSP_CFG_ROM_REG_FSBLCTRL2
#define BSP_CFG_ROM_REG_FSBLCTRL2 ( \
                (15 << R_OFS_DATAFLASH_FSBLCTRL2_PORTPN_Pos) | \
                (0x1F << R_OFS_DATAFLASH_FSBLCTRL2_PORTGN_Pos) | \
                0xFFFFFE00)
#endif

            /* Start Address of Code Certificate Register 0 */
#ifndef BSP_CFG_ROM_REG_SACC0
#define BSP_CFG_ROM_REG_SACC0 (0xFFFFFFFF)
#endif

            /* Start Address of Code Certificate Register 1 */
#ifndef BSP_CFG_ROM_REG_SACC1
#define BSP_CFG_ROM_REG_SACC1 (0xFFFFFFFF)
#endif

            /* Start Address of Measurement Report Register */
#ifndef BSP_CFG_ROM_REG_SAMR
#define BSP_CFG_ROM_REG_SAMR (0xFFFFFFFF)
#endif

            /* Hash of OEM_ROOT_PK Register */
#ifndef BSP_CFG_ROM_REG_HOEMRTPK
#define BSP_CFG_ROM_REG_HOEMRTPK (RA_NOT_DEFINED)
#endif

            /* Configuration Data 0 Lock Bit Register 0 */
#ifndef BSP_CFG_ROM_REG_CFGD0LOCK0
#define BSP_CFG_ROM_REG_CFGD0LOCK0 (RA_NOT_DEFINED)
#endif

            /* Configuration Data 0 Lock Bit Register 1 */
#ifndef BSP_CFG_ROM_REG_CFGD0LOCK1
#define BSP_CFG_ROM_REG_CFGD0LOCK1 (RA_NOT_DEFINED)
#endif

            /* Configuration Data 1 Lock Bit Register 0 */
#ifndef BSP_CFG_ROM_REG_CFGD1LOCK0
#define BSP_CFG_ROM_REG_CFGD1LOCK0 (RA_NOT_DEFINED)
#endif

            /* Configuration Data 1 Lock Bit Register 1 */
#ifndef BSP_CFG_ROM_REG_CFGD1LOCK1
#define BSP_CFG_ROM_REG_CFGD1LOCK1 (RA_NOT_DEFINED)
#endif

            /* Configuration Data 2 Lock Bit Register */
#ifndef BSP_CFG_ROM_REG_CFGD2LOCK
#define BSP_CFG_ROM_REG_CFGD2LOCK (RA_NOT_DEFINED)
#endif

            /* Anti-Rollback Counter Lock Setting Register */
#ifndef BSP_CFG_ROM_REG_ARCLS
#define BSP_CFG_ROM_REG_ARCLS ( \
            (RA_NOT_DEFINED << R_OFS_DATAFLASH_ARCLS_ARCS_LK_Pos) | \
            (RA_NOT_DEFINED << R_OFS_DATAFLASH_ARCLS_ARCNS_LK_Pos) | \
            (RA_NOT_DEFINED << R_OFS_DATAFLASH_ARCLS_ARCBL_LK_Pos) | \
            0xFFC0)
#endif

            /* Anti-Rollback Counter Configuration Setting for Non-secure Application Register */
#ifndef BSP_CFG_ROM_REG_ARCCS
#define BSP_CFG_ROM_REG_ARCCS (RA_NOT_DEFINED | 0xFFFC)
#endif

            /* Anti-Rollback Counter for Secure Application 0 Register */
#ifndef BSP_CFG_ROM_REG_ARC_SEC0
#define BSP_CFG_ROM_REG_ARC_SEC0              (0U)
#endif

            /* Anti-Rollback Counter for Secure Application 1 Register */
#ifndef BSP_CFG_ROM_REG_ARC_SEC1
#define BSP_CFG_ROM_REG_ARC_SEC1              (0U)
#endif

            /* Anti-Rollback Counter for Non-secure Application 0 Register */
#ifndef BSP_CFG_ROM_REG_ARC_NSEC0
#define BSP_CFG_ROM_REG_ARC_NSEC0             (0U)
#endif

            /* Anti-Rollback Counter for Non-secure Application 1 Register */
#ifndef BSP_CFG_ROM_REG_ARC_NSEC1
#define BSP_CFG_ROM_REG_ARC_NSEC1             (0U)
#endif

            /* Anti-Rollback Counter for Non-secure Application 2 Register */
#ifndef BSP_CFG_ROM_REG_ARC_NSEC2
#define BSP_CFG_ROM_REG_ARC_NSEC2             (0U)
#endif

            /* Anti-Rollback Counter for Non-secure Application 3 Register */
#ifndef BSP_CFG_ROM_REG_ARC_NSEC3
#define BSP_CFG_ROM_REG_ARC_NSEC3             (0U)
#endif

            /* Anti-Rollback Counter for Non-secure Application 4 Register */
#ifndef BSP_CFG_ROM_REG_ARC_NSEC4
#define BSP_CFG_ROM_REG_ARC_NSEC4             (0U)
#endif

            /* Anti-Rollback Counter for Non-secure Application 5 Register */
#ifndef BSP_CFG_ROM_REG_ARC_NSEC5
#define BSP_CFG_ROM_REG_ARC_NSEC5             (0U)
#endif

            /* Anti-Rollback Counter for Non-secure Application 6 Register */
#ifndef BSP_CFG_ROM_REG_ARC_NSEC6
#define BSP_CFG_ROM_REG_ARC_NSEC6             (0U)
#endif

            /* Anti-Rollback Counter for Non-secure Application 7 Register */
#ifndef BSP_CFG_ROM_REG_ARC_NSEC7
#define BSP_CFG_ROM_REG_ARC_NSEC7             (0U)
#endif

            /* Anti-Rollback Counter for OEMBL 0 Register */
#ifndef BSP_CFG_ROM_REG_ARC_OEMBL0
#define BSP_CFG_ROM_REG_ARC_OEMBL0            (0U)
#endif

            /* Anti-Rollback Counter for OEMBL 1 Register */
#ifndef BSP_CFG_ROM_REG_ARC_OEMBL1
#define BSP_CFG_ROM_REG_ARC_OEMBL1            (0U)
#endif

#ifndef BSP_CFG_DCACHE_ENABLED
#define BSP_CFG_DCACHE_ENABLED (0)
#endif
#endif /* BSP_MCU_FAMILY_CFG_H_ */
