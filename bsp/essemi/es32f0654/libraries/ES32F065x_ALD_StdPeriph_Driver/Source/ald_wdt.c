/**
 *********************************************************************************
 *
 * @file    ald_wdt.c
 * @brief   WDT module driver.
 *
 * @version V1.0
 * @date    18 Dec 2017
 * @author  AE Team
 * @note
 *
 * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
 *
 *********************************************************************************
 */
#include "ald_conf.h"
#include "ald_wdt.h"


/** @addtogroup ES32FXXX_ALD
 * @{
 */

/** @defgroup WDT WDT
 * @brief WDT module driver
 * @{
 */
#ifdef ALD_WDT


/** @defgroup WWDT_Public_Functions WWDT Public Functions
 * @brief Init and configure WWDT function
 * @{
 */
/**
 * @brief Initializes the WWDT according to the specified parameters.
 * @param load: Specifies the free-running downcounter value.
 * @param win: specifics the no dog windows,
 *        the parameter can be one of the following values:
 *        @arg @ref WWDT_WIN_25 No dog window size: 25%
 *        @arg @ref WWDT_WIN_50 No dog window size: 50%
 *        @arg @ref WWDT_WIN_75 No dog window size: 75%
 *        @arg @ref WWDT_WIN_00 No dog window size: 0%
 * @param interrupt: Enable or disable interrupt.
 * @retval None
 */
void ald_wwdt_init(uint32_t load, wwdt_win_t win, type_func_t interrupt)
{
    assert_param(IS_WWDT_WIN_TYPE(win));
    assert_param(IS_FUNC_STATE(interrupt));

    WWDT_UNLOCK();
    WRITE_REG(WWDT->LOAD, load);
    MODIFY_REG(WWDT->CON, WWDT_CON_WWDTWIN_MSK, win << WWDT_CON_WWDTWIN_POSS);
    SET_BIT(WWDT->CON, WWDT_CON_CLKS_MSK);
    SET_BIT(WWDT->CON, WWDT_CON_RSTEN_MSK);
    MODIFY_REG(WWDT->CON, WWDT_CON_IE_MSK, interrupt << WWDT_CON_IE_POS);
    WWDT_LOCK();

    return;
}

/**
 * @brief Start the WWDT
 * @retval None
 */
void ald_wwdt_start(void)
{
    WWDT_UNLOCK();
    SET_BIT(WWDT->CON, WWDT_CON_EN_MSK);
    WWDT_LOCK();

    return;
}

/**
 * @brief Get the free-running downcounter value
 * @retval Value
 */
uint32_t ald_wwdt_get_value(void)
{
    return WWDT->VALUE;
}

/**
 * @brief Get interrupt state
 * @retval Value
 */
it_status_t ald_wwdt_get_flag_status(void)
{
    if (READ_BIT(WWDT->RIS, WWDT_RIS_WWDTIF_MSK))
        return SET;

    return RESET;
}

/**
 * @brief Clear interrupt state
 * @retval None
 */
void ald_wwdt_clear_flag_status(void)
{
    WRITE_REG(WWDT->INTCLR, 1);
    return;
}

/**
 * @brief Refreshes the WWDT
 * @retval None
 */
void ald_wwdt_feed_dog(void)
{
    WWDT_UNLOCK();
    WRITE_REG(WWDT->INTCLR, 0x1);
    WWDT_LOCK();

    return;
}
/**
 * @}
 */

/** @defgroup IWDT_Public_Functions IWDT Public Functions
 * @brief Init and configure IWDT function
 * @{
 */
/**
 * @brief Initializes the IWDG according to the specified parameters.
 * @param load: Specifies the free-running downcounter value.
 * @param interrupt: Enable or disable interrupt.
 * @retval None
 */
void ald_iwdt_init(uint32_t load, type_func_t interrupt)
{
    assert_param(IS_FUNC_STATE(interrupt));

    IWDT_UNLOCK();
    WRITE_REG(IWDT->LOAD, load);
    SET_BIT(IWDT->CON, IWDT_CON_CLKS_MSK);
    SET_BIT(IWDT->CON, IWDT_CON_RSTEN_MSK);
    MODIFY_REG(IWDT->CON, IWDT_CON_IE_MSK, interrupt << IWDT_CON_IE_POS);
    IWDT_LOCK();

    return;
}

/**
 * @brief Start the IWDT
 * @retval None
 */
void ald_iwdt_start(void)
{
    IWDT_UNLOCK();
    SET_BIT(IWDT->CON, IWDT_CON_EN_MSK);
    IWDT_LOCK();

    return;
}

/**
 * @brief Get the free-running downcounter value
 * @retval Value
 */
uint32_t ald_iwdt_get_value(void)
{
    return IWDT->VALUE;
}

/**
 * @brief Get interrupt state
 * @retval Value
 */
it_status_t ald_iwdt_get_flag_status(void)
{
    if (READ_BIT(IWDT->RIS, IWDT_RIS_WDTIF_MSK))
        return SET;

    return RESET;
}

/**
 * @brief Clear interrupt state
 * @retval None
 */
void ald_iwdt_clear_flag_status(void)
{
    WRITE_REG(IWDT->INTCLR, 1);
    return;
}

/**
 * @brief Refreshes the WWDT
 * @retval None
 */
void ald_iwdt_feed_dog(void)
{
    IWDT_UNLOCK();
    WRITE_REG(IWDT->INTCLR, 1);
    IWDT_LOCK();

    return;
}
/**
 * @}
 */

#endif /* ALD_WDT */
/**
 * @}
 */

/**
 * @}
 */
