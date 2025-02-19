/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
 * be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
 * Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
 * the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
 * intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
 * copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
 * THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
 * TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
 * INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
 * SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
 * DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
 * INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
 * LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_clocks.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Key code for writing PRCR register. */
#define BSP_PRV_PRCR_KEY                                    (0xA500U)
#define BSP_PRV_PRCR_CGC_UNLOCK                             ((BSP_PRV_PRCR_KEY) | 0x1U)
#define BSP_PRV_PRCR_LOCK                                   ((BSP_PRV_PRCR_KEY) | 0x0U)

/* Key code for writing  PCMD register. */
#define BSP_PRV_PCMD_KEY                                    (0xA5U)

/* Calculate the value to write to SCKCR. */
#define BSP_PRV_STARTUP_SCKCR_FSELXSPI0_DIVSELXSPI0_BITS    (BSP_CFG_FSELXSPI0_DIVSELXSPI0 & 0x47U)
#define BSP_PRV_STARTUP_SCKCR_FSELXSPI1_DIVSELXSPI1_BITS    ((BSP_CFG_FSELXSPI1_DIVSELXSPI1 & 0x47U) << 8U)
#define BSP_PRV_STARTUP_SCKCR_CKIO_BITS                     ((BSP_CFG_CKIO & 7U) << 16U)
#define BSP_PRV_STARTUP_SCKCR_FSELCANFD_BITS                ((BSP_CFG_FSELCANFD & 1U) << 20U)
#define BSP_PRV_STARTUP_SCKCR_PHYSEL_BITS                   ((BSP_CFG_PHYSEL & 1U) << 21U)
#define BSP_PRV_STARTUP_SCKCR_CLMASEL_BITS                  ((BSP_CFG_CLMASEL & 1U) << 22U)
#define BSP_PRV_STARTUP_SCKCR_SPI0ASYNCSEL_BITS             ((BSP_CFG_SPI0ASYNCCLK & 1U) << 24U)
#define BSP_PRV_STARTUP_SCKCR_SPI1ASYNCSEL_BITS             ((BSP_CFG_SPI1ASYNCCLK & 1U) << 25U)
#define BSP_PRV_STARTUP_SCKCR_SPI2ASYNCSEL_BITS             ((BSP_CFG_SPI2ASYNCCLK & 1U) << 26U)
#define BSP_PRV_STARTUP_SCKCR_SCI0ASYNCSEL_BITS             ((BSP_CFG_SCI0ASYNCCLK & 1U) << 27U)
#define BSP_PRV_STARTUP_SCKCR_SCI1ASYNCSEL_BITS             ((BSP_CFG_SCI1ASYNCCLK & 1U) << 28U)
#define BSP_PRV_STARTUP_SCKCR_SCI2ASYNCSEL_BITS             ((BSP_CFG_SCI2ASYNCCLK & 1U) << 29U)
#define BSP_PRV_STARTUP_SCKCR_SCI3ASYNCSEL_BITS             ((BSP_CFG_SCI3ASYNCCLK & 1U) << 30U)
#define BSP_PRV_STARTUP_SCKCR_SCI4ASYNCSEL_BITS             ((BSP_CFG_SCI4ASYNCCLK & 1U) << 31U)

/* Calculate the value to write to SCKCR2. */
#define BSP_PRV_STARTUP_SCKCR2_FSELCPU0_BITS                (BSP_CFG_FSELCPU0 & 3U)
#define BSP_PRV_STARTUP_SCKCR2_RESERVED_BIT4_BITS           (1U << 4U) // The write value should be 1.
#define BSP_PRV_STARTUP_SCKCR2_DIVSELSUB_BITS               ((BSP_CFG_DIVSELSUB & 1U) << 5U)
#define BSP_PRV_STARTUP_SCKCR2_SPI3ASYNCSEL_BITS            ((BSP_CFG_SPI3ASYNCCLK & 1U) << 24U)
#define BSP_PRV_STARTUP_SCKCR2_SCI5ASYNCSEL_BITS            ((BSP_CFG_SCI5ASYNCCLK & 1U) << 25U)

#define BSP_PRV_STARTUP_SCKCR                               (BSP_PRV_STARTUP_SCKCR_FSELXSPI0_DIVSELXSPI0_BITS | \
                                                             BSP_PRV_STARTUP_SCKCR_FSELXSPI1_DIVSELXSPI1_BITS | \
                                                             BSP_PRV_STARTUP_SCKCR_CKIO_BITS |                  \
                                                             BSP_PRV_STARTUP_SCKCR_FSELCANFD_BITS |             \
                                                             BSP_PRV_STARTUP_SCKCR_PHYSEL_BITS |                \
                                                             BSP_PRV_STARTUP_SCKCR_CLMASEL_BITS |               \
                                                             BSP_PRV_STARTUP_SCKCR_SPI0ASYNCSEL_BITS |          \
                                                             BSP_PRV_STARTUP_SCKCR_SPI1ASYNCSEL_BITS |          \
                                                             BSP_PRV_STARTUP_SCKCR_SPI2ASYNCSEL_BITS |          \
                                                             BSP_PRV_STARTUP_SCKCR_SCI0ASYNCSEL_BITS |          \
                                                             BSP_PRV_STARTUP_SCKCR_SCI1ASYNCSEL_BITS |          \
                                                             BSP_PRV_STARTUP_SCKCR_SCI2ASYNCSEL_BITS |          \
                                                             BSP_PRV_STARTUP_SCKCR_SCI3ASYNCSEL_BITS |          \
                                                             BSP_PRV_STARTUP_SCKCR_SCI4ASYNCSEL_BITS)

#define BSP_PRV_STARTUP_SCKCR2                              (BSP_PRV_STARTUP_SCKCR2_FSELCPU0_BITS |      \
                                                             BSP_PRV_STARTUP_SCKCR2_RESERVED_BIT4_BITS | \
                                                             BSP_PRV_STARTUP_SCKCR2_DIVSELSUB_BITS |     \
                                                             BSP_PRV_STARTUP_SCKCR2_SPI3ASYNCSEL_BITS |  \
                                                             BSP_PRV_STARTUP_SCKCR2_SCI5ASYNCSEL_BITS)

#define BSP_PRV_STARTUP_SCKCR2_FSELCPU0_ICLK_MUL2           (BSP_CLOCKS_FSELCPU0_ICLK_MUL2 << \
                                                             R_SYSC_S_SCKCR2_FSELCPU0_Pos)

/* Calculate the value to write to HIZCTRLEN. */
#define BSP_PRV_STARTUP_HIZCTRLEN                           ((BSP_CFG_CLMA1MASK << 2) | (BSP_CFG_CLMA0MASK << 1) | \
                                                             BSP_CFG_CLMA3MASK)

/* Frequencies of clocks. */
#define BSP_PRV_CPU_FREQ_200_MHZ                            (200000000U) // CPU frequency is 200 MHz
#define BSP_PRV_CPU_FREQ_150_MHZ                            (150000000U) // CPU frequency is 150 MHz

/* Command sequence for enabling CLMA. */
#define BSP_PRV_CTL0_ENABLE_TARGET_CMD                      (0x01)
#define BSP_PRV_CTL0_ENABLE_REVERSED_CMD                    (0xFE)

#define BSP_PRV_LOCO_STABILIZATION_COUNT                    (40000)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
#if !BSP_CFG_SOFT_RESET_SUPPORTED
static void bsp_prv_clock_set_hard_reset(void);

#endif

/*******************************************************************************************************************//**
 * @internal
 * @addtogroup BSP_MCU_PRV Internal BSP Documentation
 * @ingroup RENESAS_INTERNAL
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Update SystemCoreClock variable based on current clock settings.
 **********************************************************************************************************************/
void SystemCoreClockUpdate (void)
{
    uint32_t devselsub = R_SYSC_S->SCKCR2_b.DIVSELSUB;
    uint32_t fselcpu   = (R_SYSC_S->SCKCR2_b.FSELCPU0 & 1U);

    if (0U == devselsub)
    {
        SystemCoreClock = BSP_PRV_CPU_FREQ_200_MHZ << fselcpu;
    }
    else
    {
        SystemCoreClock = BSP_PRV_CPU_FREQ_150_MHZ << fselcpu;
    }
}

/*******************************************************************************************************************//**
 * Applies system core clock source and divider changes.  The MCU is expected to be in high speed mode during this
 * configuration and the CGC registers are expected to be unlocked in PRCR.
 *
 * @param[in] sckcr                  Value to set in SCKCR register
 * @param[in] sckcr2                 Value to set in SCKCR2 register
 **********************************************************************************************************************/
void bsp_prv_clock_set (uint32_t sckcr, uint32_t sckcr2)
{
    volatile uint32_t dummy;
    sckcr  = sckcr & BSP_PRV_SCKCR_MASK;
    sckcr2 = sckcr2 & BSP_PRV_SCKCR2_MASK;

    /* Set the system source clock */
    R_SYSC_S->SCKCR2 = sckcr2;

    /** In order to secure processing after clock frequency is changed,
     *  dummy read the same register at least eight times.
     *  Refer to "Notes on Clock Generation Circuit" in the RZ microprocessor manual. */
    dummy = R_SYSC_S->SCKCR2;
    dummy = R_SYSC_S->SCKCR2;
    dummy = R_SYSC_S->SCKCR2;
    dummy = R_SYSC_S->SCKCR2;
    dummy = R_SYSC_S->SCKCR2;
    dummy = R_SYSC_S->SCKCR2;
    dummy = R_SYSC_S->SCKCR2;
    dummy = R_SYSC_S->SCKCR2;

    R_SYSC_NS->SCKCR = sckcr;

    /** In order to secure processing after clock frequency is changed,
     *  dummy read the same register at least eight times.
     *  Refer to "Notes on Clock Generation Circuit" in the RZ microprocessor manual. */
    dummy = R_SYSC_NS->SCKCR;
    dummy = R_SYSC_NS->SCKCR;
    dummy = R_SYSC_NS->SCKCR;
    dummy = R_SYSC_NS->SCKCR;
    dummy = R_SYSC_NS->SCKCR;
    dummy = R_SYSC_NS->SCKCR;
    dummy = R_SYSC_NS->SCKCR;
    dummy = R_SYSC_NS->SCKCR;

    FSP_PARAMETER_NOT_USED(dummy);

    /* Clock is now at requested frequency. */

    /* Update the CMSIS core clock variable so that it reflects the new ICLK frequency. */
    SystemCoreClockUpdate();
}

#if !BSP_CFG_SOFT_RESET_SUPPORTED

static void bsp_prv_clock_set_hard_reset (void)
{
    volatile uint32_t dummy;
    uint32_t          sckcr  = BSP_PRV_STARTUP_SCKCR & BSP_PRV_SCKCR_MASK;
    uint32_t          sckcr2 = BSP_PRV_STARTUP_SCKCR2 & BSP_PRV_SCKCR2_MASK;

    /* Set the system source clock */
    R_SYSC_S->SCKCR2 = sckcr2;

    /** In order to secure processing after clock frequency is changed,
     *  dummy read the same register at least eight times.
     *  Refer to "Notes on Clock Generation Circuit" in the RZ microprocessor manual. */
    dummy = R_SYSC_S->SCKCR2;
    dummy = R_SYSC_S->SCKCR2;
    dummy = R_SYSC_S->SCKCR2;
    dummy = R_SYSC_S->SCKCR2;
    dummy = R_SYSC_S->SCKCR2;
    dummy = R_SYSC_S->SCKCR2;
    dummy = R_SYSC_S->SCKCR2;
    dummy = R_SYSC_S->SCKCR2;

    R_SYSC_NS->SCKCR = sckcr;

    /** In order to secure processing after clock frequency is changed,
     *  dummy read the same register at least eight times.
     *  Refer to "Notes on Clock Generation Circuit" in the RZ microprocessor manual. */
    dummy = R_SYSC_NS->SCKCR;
    dummy = R_SYSC_NS->SCKCR;
    dummy = R_SYSC_NS->SCKCR;
    dummy = R_SYSC_NS->SCKCR;
    dummy = R_SYSC_NS->SCKCR;
    dummy = R_SYSC_NS->SCKCR;
    dummy = R_SYSC_NS->SCKCR;
    dummy = R_SYSC_NS->SCKCR;

    FSP_PARAMETER_NOT_USED(dummy);

    /* Clock is now at requested frequency. */

    /* Update the CMSIS core clock variable so that it reflects the new ICLK frequency. */
    SystemCoreClockUpdate();
}

#endif

/*******************************************************************************************************************//**
 * Initializes system clocks.  Makes no assumptions about current register settings.
 **********************************************************************************************************************/
void bsp_clock_init (void)
{
    volatile uint32_t dummy = 0;

    /* Unlock CGC protection registers. */
    R_RWP_NS->PRCRN = (uint16_t) BSP_PRV_PRCR_CGC_UNLOCK;
    R_RWP_S->PRCRS  = (uint16_t) BSP_PRV_PRCR_CGC_UNLOCK;

    /* The SystemCoreClock needs to be updated before calling R_BSP_SoftwareDelay. */
    SystemCoreClockUpdate();

    /* Set source clock and dividers. */
#if BSP_CFG_SOFT_RESET_SUPPORTED
    bsp_prv_clock_set(BSP_PRV_STARTUP_SCKCR, BSP_PRV_STARTUP_SCKCR2);
#else
    bsp_prv_clock_set_hard_reset();
#endif

#if (BSP_CLOCKS_PLL1_INITIAL != BSP_CFG_PLL1)
    R_SYSC_S->PLL1EN = BSP_CFG_PLL1;
#endif

#if (BSP_CLOCKS_LOCO_ENABLE == BSP_CFG_LOCO_ENABLE)
    R_SYSC_S->LOCOCR = BSP_CLOCKS_LOCO_ENABLE;

    /* Only start using the LOCO clock after
     * the LOCO oscillation stabilization time (tLOCOWT) has elapsed. */
    for (uint16_t i = 0; i < BSP_PRV_LOCO_STABILIZATION_COUNT; i++)
    {
        __asm volatile ("nop");
    }
#endif

    R_SYSC_S->HIZCTRLEN = BSP_PRV_STARTUP_HIZCTRLEN;

#if (BSP_CLOCKS_CLMA0_ENABLE == BSP_CFG_CLMA0_ENABLE)

    /* Set the lower and upper limit for comparing frequency domains. */
    R_CLMA0->CMPL = BSP_CFG_CLMA0_CMPL;
    R_CLMA0->CMPH = BSP_CFG_CLMA0_CMPH;

    /* Enabling CLMA0 operation. */
    do
    {
        R_CLMA0->PCMD = BSP_PRV_PCMD_KEY;

        R_CLMA0->CTL0 = BSP_PRV_CTL0_ENABLE_TARGET_CMD;
        R_CLMA0->CTL0 = BSP_PRV_CTL0_ENABLE_REVERSED_CMD;
        R_CLMA0->CTL0 = BSP_PRV_CTL0_ENABLE_TARGET_CMD;

        if (1 != R_CLMA0->CTL0)
        {
            /* Check the value of PROTSR register. */
            dummy = R_CLMA0->PROTSR;
        }
    } while (1 == R_CLMA0->PROTSR_b.PRERR);
#endif

#if (BSP_CLOCKS_CLMA1_ENABLE == BSP_CFG_CLMA1_ENABLE)

    /* Set the lower and upper limit for comparing frequency domains. */
    R_CLMA1->CMPL = BSP_CFG_CLMA1_CMPL;
    R_CLMA1->CMPH = BSP_CFG_CLMA1_CMPH;

    /* Enabling CLMA1 operation. */
    do
    {
        R_CLMA1->PCMD = BSP_PRV_PCMD_KEY;

        R_CLMA1->CTL0 = BSP_PRV_CTL0_ENABLE_TARGET_CMD;
        R_CLMA1->CTL0 = BSP_PRV_CTL0_ENABLE_REVERSED_CMD;
        R_CLMA1->CTL0 = BSP_PRV_CTL0_ENABLE_TARGET_CMD;

        if (1 != R_CLMA1->CTL0)
        {
            /* Check the value of PROTSR register. */
            dummy = R_CLMA1->PROTSR;
        }
    } while (1 == R_CLMA1->PROTSR_b.PRERR);
#endif

#if (BSP_CLOCKS_CLMA2_ENABLE == BSP_CFG_CLMA2_ENABLE)

    /* Set the lower and upper limit for comparing frequency domains. */
    R_CLMA2->CMPL = BSP_CFG_CLMA2_CMPL;
    R_CLMA2->CMPH = BSP_CFG_CLMA2_CMPH;

    /* Enabling CLMA2 operation. */
    do
    {
        R_CLMA2->PCMD = BSP_PRV_PCMD_KEY;

        R_CLMA2->CTL0 = BSP_PRV_CTL0_ENABLE_TARGET_CMD;
        R_CLMA2->CTL0 = BSP_PRV_CTL0_ENABLE_REVERSED_CMD;
        R_CLMA2->CTL0 = BSP_PRV_CTL0_ENABLE_TARGET_CMD;

        if (1 != R_CLMA2->CTL0)
        {
            /* Check the value of PROTSR register. */
            dummy = R_CLMA2->PROTSR;
        }
    } while (1 == R_CLMA2->PROTSR_b.PRERR);
#endif

#if (BSP_CLOCKS_CLMA3_ENABLE == BSP_CFG_CLMA3_ENABLE)

    /* Set the lower and upper limit for comparing frequency domains. */
    R_CLMA3->CMPL = BSP_CFG_CLMA3_CMPL;
    R_CLMA3->CMPH = BSP_CFG_CLMA3_CMPH;

    /* Enabling CLMA3 operation. */
    do
    {
        R_CLMA3->PCMD = BSP_PRV_PCMD_KEY;

        R_CLMA3->CTL0 = BSP_PRV_CTL0_ENABLE_TARGET_CMD;
        R_CLMA3->CTL0 = BSP_PRV_CTL0_ENABLE_REVERSED_CMD;
        R_CLMA3->CTL0 = BSP_PRV_CTL0_ENABLE_TARGET_CMD;

        if (1 != R_CLMA3->CTL0)
        {
            /* Check the value of PROTSR register. */
            dummy = R_CLMA3->PROTSR;
        }
    } while (1 == R_CLMA3->PROTSR_b.PRERR);
#endif

    /* Lock CGC and LPM protection registers. */
    R_RWP_NS->PRCRN = (uint16_t) BSP_PRV_PRCR_LOCK;
    R_RWP_S->PRCRS  = (uint16_t) BSP_PRV_PRCR_LOCK;

    FSP_PARAMETER_NOT_USED(dummy);
}

/** @} (end addtogroup BSP_MCU_PRV) */
