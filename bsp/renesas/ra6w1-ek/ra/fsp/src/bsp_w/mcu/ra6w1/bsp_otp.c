/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"
#ifdef UNIT_TESTING
 #include "fake_regs.h"
#endif

#include "bsp_otp.h"

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

static const uint32_t g_tim1[] =
{
    /* Default 40MHz */
    (39 << OTPC_OTPC_TIM1_REG_OTPC_TIM1_CC_T_1US_Pos) |
    (0 << OTPC_OTPC_TIM1_REG_OTPC_TIM1_CC_T_20NS_Pos) |
    (3 << OTPC_OTPC_TIM1_REG_OTPC_TIM1_CC_T_RD_Pos) |
    (0x09 << OTPC_OTPC_TIM1_REG_OTPC_TIM1_US_T_CS_Pos) |
    (0x09 << OTPC_OTPC_TIM1_REG_OTPC_TIM1_US_T_CSP_Pos),

    /* 80MHz */
    (80 << OTPC_OTPC_TIM1_REG_OTPC_TIM1_CC_T_1US_Pos) |
    (1 << OTPC_OTPC_TIM1_REG_OTPC_TIM1_CC_T_20NS_Pos) |
    (8 << OTPC_OTPC_TIM1_REG_OTPC_TIM1_CC_T_RD_Pos) |
    (0x09 << OTPC_OTPC_TIM1_REG_OTPC_TIM1_US_T_CS_Pos) |
    (0x09 << OTPC_OTPC_TIM1_REG_OTPC_TIM1_US_T_CSP_Pos),
};

/*******************************************************************************************************************//**
 * Set OTP cell timing parameters.
 *
 * @param[in] clk_speed    OTPC clock speed.
 **********************************************************************************************************************/
__STATIC_FORCEINLINE void bsp_otpc_set_speed (bsp_otpc_clk_freq_t clk_speed)
{
    OTPC->OTPC_TIM1_REG = g_tim1[clk_speed];
}

/*******************************************************************************************************************//**
 * Get OTP cell address.
 *
 * @param[in] cell_offset    OTP cell offset.
 * @return OTP cell address.
 **********************************************************************************************************************/
__STATIC_FORCEINLINE volatile uint32_t * bsp_prv_otpc_addr (uint32_t cell_offset)
{
    return (volatile uint32_t *) (MEMORY_OTP_BASE + (4 * cell_offset));
}

/*******************************************************************************************************************//**
 * Verify data stored in OTP.
 *
 * @param[in] p_data         A pointer to the data that is expected to be stored in the OTP.
 *                           It shall be at least of (num_words * 4) bytes long.
 * @param[in] cell_offset    OTP cell offset where data is expected to be stored.
 * @param[in] num_words      Number of words to verify.
 * @param[in] mode           OTP mode
 **********************************************************************************************************************/
static bool bsp_otp_read_verif (const uint32_t * p_data, uint32_t cell_offset, uint32_t num_words, bsp_otpc_mode_t mode)
{
    bsp_otp_mode_set(mode);

    for (uint32_t i = 0; i < num_words; i++)
    {
        if (*p_data != *bsp_prv_otpc_addr(cell_offset))
        {
            return false;
        }

        cell_offset++;
        p_data++;
    }

    return true;
}

#ifdef UNIT_TESTING

BSP_WEAK_REFERENCE void bsp_prv_otp_testable_busy_loop_hook (uintptr_t reg, uint32_t param)
{
    /* Do nothing */
    FSP_PARAMETER_NOT_USED(reg);
    FSP_PARAMETER_NOT_USED(param);
}

#endif

/*******************************************************************************************************************//**
 * Set OTP mode.
 *
 * @param[in] mode    The new OTP mode.
 **********************************************************************************************************************/
__STATIC_FORCEINLINE void bsp_prv_otp_mode_set (bsp_otpc_mode_t mode)
{
    /* Change mode only if new mode is different than the old one */
    if (mode != OTPC->OTPC_MODE_REG_b.OTPC_MODE_MODE)
    {
        OTPC->OTPC_MODE_REG_b.OTPC_MODE_MODE = mode;
    }
}

/*******************************************************************************************************************//**
 * Wait for OTP mode to be applied.
 **********************************************************************************************************************/
static void bsp_prv_otp_mode_change_wait (void)
{
    while (0 == OTPC->OTPC_STAT_REG_b.OTPC_STAT_MRDY)
    {
#ifdef UNIT_TESTING
        bsp_prv_otp_testable_busy_loop_hook((uintptr_t) &OTPC->OTPC_STAT_REG, OTPC_OTPC_STAT_REG_OTPC_STAT_MRDY_Pos);
#endif
    }
}

/*******************************************************************************************************************//**
 * Set OTP mode and wait for it to be applied.
 *
 * @param[in] mode    The new OTP mode.
 **********************************************************************************************************************/
__STATIC_FORCEINLINE void bsp_prv_otp_mode_wait_until_set (bsp_otpc_mode_t mode)
{
    bsp_prv_otp_mode_set(mode);
    bsp_prv_otp_mode_change_wait();
}

/*******************************************************************************************************************//**
 * Wait for OTP programming to finish.
 **********************************************************************************************************************/
__STATIC_FORCEINLINE void bsp_otpc_wait_while_busy_programming (void)
{
    while (!OTPC->OTPC_STAT_REG_b.OTPC_STAT_PRDY)
    {
        ;
    }
}

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initialize the OTP controller.
 *
 * @note    Among other things, it enables the clock of the OTP controller.
 *          TODO this shall not be the case, see WIFISWTIN-1591.
 **********************************************************************************************************************/
void bsp_otp_init (void)
{
    uint32_t lock;
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    while (CC312->CC312_NVM_IS_IDLE_REG_b.CC312_NVM_IS_IDLE_STATUS != 1)
    {
        ;
    }

    /* Check PLL clock */
    if (CRG_TOP->CLK_CTRL_REG_b.PLL_PERI_ENABLE == 1)
    {
        bsp_otpc_set_speed(BSP_OTPC_CLK_FREQ_80MHz);
    }
    else
    {
        bsp_otpc_set_speed(BSP_OTPC_CLK_FREQ_40MHz);
    }

    /* Default read mode */
    bsp_otp_mode_set(BSP_OTP_MODE_READ);

    /* Read out OTP lock bit first without below read out, it can not write to the OTP */
    lock = *bsp_prv_otpc_addr(511);
    FSP_PARAMETER_NOT_USED(lock);

    FSP_CRITICAL_SECTION_EXIT;
}

/*******************************************************************************************************************//**
 * Set OTP timing for the given sysclk frequency.
 *
 * @param [in] sysclk_freq_MHz    The target sysclk frequency, in MHz.
 *
 * @note    Only specific frequencies are supported, depending on the device.
 *          TODO this function shall be updated/deleted, see WIFISWTIN-1591.
 **********************************************************************************************************************/
void bsp_otp_timings_set (uint32_t sysclk_freq_MHz)
{
    switch (sysclk_freq_MHz)
    {
        case 40:
        {
            bsp_otpc_set_speed(BSP_OTPC_CLK_FREQ_40MHz);
            break;
        }

        case 80:
        {
            bsp_otpc_set_speed(BSP_OTPC_CLK_FREQ_80MHz);
            break;
        }

        case 160:
        {
            /* TODO implement */
            break;
        }

        default:
        {
            BSP_CHECK_DEBUG(0);
        }
    }
}

/*******************************************************************************************************************//**
 * Set OTP mode and wait for the change to finish.
 *
 * @param [in] mode    The new OTP mode.
 **********************************************************************************************************************/
void bsp_otp_mode_set (uint32_t mode)
{
    bsp_prv_otp_mode_wait_until_set(mode);
}

/*******************************************************************************************************************//**
 * Read word from OTP.
 *
 * @param[in] cell_offset    OTP cell offset.
 * @return word read from OTP.
 **********************************************************************************************************************/
uint32_t bsp_otp_word_read (uint32_t cell_offset)
{
    bsp_otp_mode_set(BSP_OTP_MODE_READ);

    return *bsp_prv_otpc_addr(cell_offset);
}

/*******************************************************************************************************************//**
 * Read data from OTP.
 *
 * @param[out] p_data        A pointer to the buffer to store OTP data into.
 *                           It shall be at least of (num_words * 4) bytes long.
 * @param[in] cell_offset    OTP cell offset to start reading from.
 * @param[in] num_words      Number of words to read from OTP.
 **********************************************************************************************************************/
void bsp_otp_read (uint32_t * p_data, uint32_t cell_offset, uint32_t num_words)
{
    bsp_otp_mode_set(BSP_OTP_MODE_READ);

    for (uint32_t i = 0; i < num_words; i++)
    {
        *p_data = *bsp_prv_otpc_addr(cell_offset + i);
        p_data++;
    }
}

/*******************************************************************************************************************//**
 * Program word to OTP.
 *
 * @param[in] data           A word to be programmed to OTP.
 * @param[in] cell_offset    OTP cell offset to start programming into.
 **********************************************************************************************************************/
uint32_t bsp_otp_word_prog (uint32_t data, uint32_t cell_offset)
{
    bsp_otp_mode_set(BSP_OTP_MODE_PROG);
    *bsp_prv_otpc_addr(cell_offset) = data;
    bsp_otpc_wait_while_busy_programming();

    return bsp_otp_word_read(cell_offset);
}

/*******************************************************************************************************************//**
 * Program data to OTP.
 *
 * @param[in] p_data         A pointer to the data to be programmed to OTP.
 *                           It shall be at least of (num_words * 4) bytes long.
 * @param[in] cell_offset    OTP cell offset to start programming into.
 * @param[in] num_words      Number of words to program to OTP.
 **********************************************************************************************************************/
void bsp_otp_prog (const uint32_t * p_data, uint32_t cell_offset, uint32_t num_words)
{
    uint32_t i;
    bsp_otp_mode_set(BSP_OTP_MODE_PROG);

    for (i = 0; i < num_words; i++)
    {
        *bsp_prv_otpc_addr(cell_offset + i) = *p_data++;
        bsp_otpc_wait_while_busy_programming();
    }
}

/*******************************************************************************************************************//**
 * Program data to OTP and verify it has been programmed successfully.
 *
 * @param[in] p_data         A pointer to the data to be programmed to OTP.
 *                           It shall be at least of (num_words * 4) bytes long.
 * @param[in] cell_offset    OTP cell offset to start programming into.
 * @param[in] num_words      Number of words to program to OTP.
 **********************************************************************************************************************/
bool bsp_otp_prog_and_verify (const uint32_t * p_data, uint32_t cell_offset, uint32_t num_words)
{
    bsp_otp_prog(p_data, cell_offset, num_words);

    if (!bsp_otp_read_verif(p_data, cell_offset, num_words, BSP_OTP_MODE_PVFY))
    {
        return false;
    }

    if (!bsp_otp_read_verif(p_data, cell_offset, num_words, BSP_OTP_MODE_RINI))
    {
        return false;
    }

    bsp_otp_mode_set(BSP_OTP_MODE_PROG);

    return true;
}

/*******************************************************************************************************************//**
 * Lock OTP cell region.
 *
 * @param[in] cell_region    OTP cell region to lock.
 * @return OTP lock region > 0 on success, 0 on failure (invalid cell_region).
 **********************************************************************************************************************/
uint32_t bsp_otp_lock (uint8_t cell_region)
{
    uint32_t otp_lock_region;

    if (cell_region > 30)
    {
        return 0;
    }

    otp_lock_region = 0x01 << (cell_region);
    bsp_otp_prog(&otp_lock_region, BSP_OTP_LOCK_OFFSET, 1);

    return bsp_otp_get_lock_region();
}

/*******************************************************************************************************************//**
 * Get OTP lock region.
 *
 * @return OTP lock region > 0.
 **********************************************************************************************************************/
uint32_t bsp_otp_get_lock_region (void)
{
    return bsp_otp_word_read(BSP_OTP_LOCK_OFFSET);
}

/*******************************************************************************************************************//**
 * Put OTP controller in standby mode and disable it.
 **********************************************************************************************************************/
void bsp_otp_close (void)
{
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    bsp_prv_otp_mode_wait_until_set(BSP_OTP_MODE_DSTBY);

    FSP_CRITICAL_SECTION_EXIT;
}

/** @} (end addtogroup BSP_MCU) */
