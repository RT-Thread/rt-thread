/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "bsp_pd.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/* System Wakeup Source */
uint32_t SystemCoreWakeupSource BSP_SECTION_EARLY_INIT;

/* System Wakeup Pin */
uint32_t SystemCoreWakeupSourcePin BSP_SECTION_EARLY_INIT;

/* RTC Brown-out and Black-out callback types */
BSP_RTC_BOD_CALLBACK_TYPE bsp_rtc_brown_callback, bsp_rtc_black_callback;

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
void RTC_IF_BLACK_Handler(void);
void RTC_IF_BROWN_Handler(void);

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

/**
 * @brief Get the SLEEP/IS_UP register-field masks of a power domain.
 *
 * @param [in]  power_domain    power domain
 * @param [out] sleep_mask      mask for the power domain's SLEEP status bit
 * @param [out] is_up_mask      mask for the power domain's IS_UP status bit
 *
 * @note    If \p power_domain is invalid, 0 is returned for both masks
 */
void bsp_prv_pd_masks_get (bsp_power_domain_t power_domain, uint32_t * sleep_mask, uint32_t * is_up_mask)
{
    switch (power_domain)
    {
        case BSP_PD_PHY:
        {
            *sleep_mask = CRG_TOP_PMU_CTRL_REG_PHY_SLEEP_Msk;
            *is_up_mask = CRG_TOP_SYS_STATUS_REG_PHY_IS_UP_Msk;
            break;
        }

        case BSP_PD_MAC:
        {
            *sleep_mask = CRG_TOP_PMU_CTRL_REG_MAC_SLEEP_Msk;
            *is_up_mask = CRG_TOP_SYS_STATUS_REG_MAC_IS_UP_Msk;
            break;
        }

        default:
        {
            *sleep_mask = 0;
            *is_up_mask = 0;
            break;
        }
    }
}

/*******************************************************************************************************************//**
 * Updates the SystemCoreWakeupSource and SystemCoreWakeupSourcePin variables based on the current state
 * of the RTC registers.
 **********************************************************************************************************************/
BSP_PLACE_CODE_IN_RAM void SystemWakeupSourceUpdate (void)
{
    SystemCoreWakeupSource = 0;
    SystemCoreWakeupSource = RTC->WAKEUP_SRC_CLR_SIG_REG & 0x7f;

    /* Clear wakeup source */
    RTC->DCDC_CNTL_OFF_REG_b.DCDC_PWR_OFF      = 0;
    RTC->ENABLE_CTRL_REG_b.SLEEP3_EN           = 0;
    RTC->ENABLE_CTRL_REG_b.WATCHDOG_OUT_INT_EN = 0;

    if (SystemCoreWakeupSource & 0x30)
    {
        SystemCoreWakeupSource = (SystemCoreWakeupSource & ~(0x30U)) | BSP_WAKEUP_SOURCE_SENSOR;
    }

    SystemCoreWakeupSource |= (RTC->RTM_CONTROL_REG_b.RTM_INFO << 7);

    if (SystemCoreWakeupSource & BSP_WAKEUP_SOURCE_POR)
    {
        if (!bsp_is_chip_revision_a())
        {
            RTC->LDO_ENABLE_REG_b.CTRL_ST_PA_DCDC = 0x18;
        }

        SystemCoreWakeupSource = BSP_WAKEUP_SOURCE_POR;
    }

    SystemCoreWakeupSourcePin = 0;
    SystemCoreWakeupSourcePin = RTC->GPIO_WAKEUP1_REG_b.GPIO_WAKEUP_SRC;
}

/*******************************************************************************************************************//**
 * Gets the wakeup source stored in the SystemCoreWakeupSource variable.
 *
 * @return The wakeup source.
 *
 * @note Since the wakeup source may change after booting, the value is stored in SystemCoreWakeupSource during the
 *       initialization process (through SystemWakeupSourceUpdate), and it is checked as a static value.
 **********************************************************************************************************************/
BSP_PLACE_CODE_IN_RAM bsp_wakeup_source_mask_t R_BSP_WakeupSourceGet (void)
{
    return (bsp_wakeup_source_mask_t) SystemCoreWakeupSource;
}

/*******************************************************************************************************************//**
 * Clears the specified wakeup source.
 *
 * @param[in] clear  Boolean indicating whether to clear the wakeup source.
 **********************************************************************************************************************/
void R_BSP_WakeupSourceClear (bool clear)
{
    uint32_t regtemp = 0xFE;
    if (clear)
    {
        RTC->WAKEUP_SRC_CLR_SIG_REG = regtemp;
    }

    RTC->ENABLE_CTRL_REG   &= ~(RTC_ENABLE_CTRL_REG_SLEEP3_EN_Msk | RTC_ENABLE_CTRL_REG_WATCHDOG_OUT_INT_EN_Msk);
    RTC->DCDC_CNTL_OFF_REG &= ~(RTC_DCDC_CNTL_OFF_REG_DCDC_PWR_OFF_Msk);
}

/*******************************************************************************************************************//**
 * Gets the wakeup source pin mask stored in the SystemCoreWakeupSourcePin variable.
 *
 * @return The wakeup pin mask.
 *
 * @note Since the wakeup pin may change after booting, the value is stored in SystemCoreWakeupSourcePin during the
 *       initialization process (through SystemWakeupSourceUpdate), and it is checked as a static value.
 **********************************************************************************************************************/
bsp_io_wakeup_pin_t R_BSP_WakeupSourcePinGet (void)
{
    return (bsp_io_wakeup_pin_t) SystemCoreWakeupSourcePin;
}

/*******************************************************************************************************************//**
 * Clears the wakeup source pin mask.
 **********************************************************************************************************************/
void R_BSP_WakeupSourcePinClear (void)
{
    RTC->WAKEUP_SRC_CLR_SIG_REG_b.GPIO_WAKE_UP_DETECT = 1;
}

/*******************************************************************************************************************//**
 * Sets the specified GPIO pin as a wakeup source.
 *
 * @param[in] pin   The GPIO pin to set as a wakeup source.
 * @param[in] edge  The edge type (active high or active low) for the wakeup source.
 **********************************************************************************************************************/
void R_BSP_WakeupSourcePinSet (bsp_io_wakeup_pin_t pin, bsp_io_wakeup_edge_t edge)
{
    uint32_t temp;
    temp  = RTC->GPIO_WAKEUP1_REG_b.GPIO_WAKEUP_EN_SEL;
    temp |= pin;
    RTC->GPIO_WAKEUP1_REG_b.GPIO_WAKEUP_EN_SEL = temp & 0x7FFU;

    temp  = RTC->GPIO_WAKEUP0_REG_b.GPIO_WAKEUP_EDGE_INVERSION_SEL;
    temp &= ~pin;
    temp |= (edge == 0) ? pin : 0;
    RTC->GPIO_WAKEUP0_REG_b.GPIO_WAKEUP_EDGE_INVERSION_SEL = temp & 0x7FFU;
}

/*******************************************************************************************************************//**
 * Sets the specified GPIO pin as a wakeup source.
 *
 * @param[in] pin   The GPIO pin to set as a wakeup source.
 * @param[in] edge  The edge type (active high or active low) for the wakeup source.
 **********************************************************************************************************************/
void R_BSP_WakeupSourcePinSetRetained (bsp_io_wakeup_pin_t pin, bsp_io_wakeup_edge_t edge)
{
    bsp_io_port_pin_t port_pin = bsp_prv_wakeup_pin_to_port_pin(pin);
    R_BSP_RetainedIoSet(port_pin);
    R_BSP_WakeupSourcePinSet(pin, edge);
}

/*******************************************************************************************************************//**
 * Unsets the specified GPIO pin as a wakeup source.
 *
 * @param[in] pin  The GPIO pin to unset as a wakeup source.
 **********************************************************************************************************************/
void R_BSP_WakeupSourcePinUnSet (bsp_io_wakeup_pin_t pin)
{
    uint32_t temp;
    temp  = RTC->GPIO_WAKEUP1_REG_b.GPIO_WAKEUP_EN_SEL;
    temp &= ~pin;
    RTC->GPIO_WAKEUP1_REG_b.GPIO_WAKEUP_EN_SEL = temp & 0x7FFU;
}

/*******************************************************************************************************************//**
 * @brief Convert PORT_PIN to WAKEUP_GPIO
 *
 * @param[in] port_pin bsp_io_port_pin_t
 *
 * @return bsp_io_wakeup_pin_t
 **********************************************************************************************************************/
bsp_io_wakeup_pin_t bsp_prv_port_pin_to_wakeup_gpio (bsp_io_port_pin_t port_pin)
{
    if (port_pin == BSP_IO_PORT_00_PIN_00)
    {
        return BSP_WAKEUP_GPIO_P0_00;
    }
    else if (port_pin == BSP_IO_PORT_00_PIN_08)
    {
        return BSP_WAKEUP_GPIO_P0_08;
    }
    else if (port_pin == BSP_IO_PORT_00_PIN_09)
    {
        return BSP_WAKEUP_GPIO_P0_09;
    }
    else if (port_pin == BSP_IO_PORT_00_PIN_10)
    {
        return BSP_WAKEUP_GPIO_P0_10;
    }
    else if (port_pin == BSP_IO_PORT_00_PIN_11)
    {
        return BSP_WAKEUP_GPIO_P0_11;
    }
    else if (port_pin == BSP_IO_PORT_00_PIN_12)
    {
        return BSP_WAKEUP_GPIO_P0_12;
    }
    else if (port_pin == BSP_IO_PORT_00_PIN_13)
    {
        return BSP_WAKEUP_GPIO_P0_13;
    }
    else if (port_pin == BSP_IO_PORT_01_PIN_10)
    {
        return BSP_WAKEUP_GPIO_P1_10;
    }
    else if (port_pin == BSP_IO_PORT_01_PIN_11)
    {
        return BSP_WAKEUP_GPIO_P1_11;
    }
    else if (port_pin == BSP_IO_PORT_01_PIN_12)
    {
        return BSP_WAKEUP_GPIO_P1_12;
    }
    else if (port_pin == BSP_IO_PORT_01_PIN_13)
    {
        return BSP_WAKEUP_GPIO_P1_13;
    }
    else
    {
        return 0;
    }
}

/*******************************************************************************************************************//**
 * @brief Convert WAKEUP_GPIO to PORT_PIN
 *
 * @param[in] wakeup_gpio bsp_io_wakeup_pin_t
 *
 * @return bsp_io_port_pin_t
 **********************************************************************************************************************/
bsp_io_port_pin_t bsp_prv_wakeup_pin_to_port_pin (bsp_io_wakeup_pin_t wakeup_gpio)
{
    if (wakeup_gpio == BSP_WAKEUP_GPIO_P0_00)
    {
        return BSP_IO_PORT_00_PIN_00;
    }
    else if (wakeup_gpio == BSP_WAKEUP_GPIO_P0_08)
    {
        return BSP_IO_PORT_00_PIN_08;
    }
    else if (wakeup_gpio == BSP_WAKEUP_GPIO_P0_09)
    {
        return BSP_IO_PORT_00_PIN_09;
    }
    else if (wakeup_gpio == BSP_WAKEUP_GPIO_P0_10)
    {
        return BSP_IO_PORT_00_PIN_10;
    }
    else if (wakeup_gpio == BSP_WAKEUP_GPIO_P0_11)
    {
        return BSP_IO_PORT_00_PIN_11;
    }
    else if (wakeup_gpio == BSP_WAKEUP_GPIO_P0_12)
    {
        return BSP_IO_PORT_00_PIN_12;
    }
    else if (wakeup_gpio == BSP_WAKEUP_GPIO_P0_13)
    {
        return BSP_IO_PORT_00_PIN_13;
    }
    else if (wakeup_gpio == BSP_WAKEUP_GPIO_P1_10)
    {
        return BSP_IO_PORT_01_PIN_10;
    }
    else if (wakeup_gpio == BSP_WAKEUP_GPIO_P1_11)
    {
        return BSP_IO_PORT_01_PIN_11;
    }
    else if (wakeup_gpio == BSP_WAKEUP_GPIO_P1_12)
    {
        return BSP_IO_PORT_01_PIN_12;
    }
    else if (wakeup_gpio == BSP_WAKEUP_GPIO_P1_13)
    {
        return BSP_IO_PORT_01_PIN_13;
    }
    else
    {
        return BSP_IO_PORT_FF_PIN_FF;
    }
}

/*******************************************************************************************************************//**
 * Sets the retention flag in the RTC register to indicate that retention memory is being used.
 *
 * @note During sleep, the RTC register is always on. The software records the status in the RTM_INFO register to
 *       indicate whether retention memory is being used. When reading the wakeup source, set RTM_INFO to bit 7 to
 *       check this.
 **********************************************************************************************************************/
BSP_PLACE_CODE_IN_RAM void R_BSP_RetainedMemFlagSet (void)
{
    RTC->RTM_CONTROL_REG_b.RTM_INFO = 1;
}

/*******************************************************************************************************************//**
 * Clears the retention memory flag in the RTC register.
 **********************************************************************************************************************/
BSP_PLACE_CODE_IN_RAM void R_BSP_RetainedMemFlagClear (void)
{
    RTC->RTM_CONTROL_REG_b.RTM_INFO = 0;
}

/*******************************************************************************************************************//**
 * Gets the retention memory flag.
 *
 * @return The retention memory flag.
 **********************************************************************************************************************/
BSP_PLACE_CODE_IN_RAM uint32_t R_BSP_RetainedMemFlagGet (void)
{
    return RTC->RTM_CONTROL_REG_b.RTM_INFO;
}

/** @} (end addtogroup BSP_MCU) */

/*******************************************************************************************************************//**
 * @brief Gets the sleep ID used when the system enters sleep mode.
 *
 * @return The sleep ID.
 **********************************************************************************************************************/
BSP_PLACE_CODE_IN_RAM uint32_t bsp_prv_pd_sleep_id_get (void)
{
    return RTC->RTM_CONTROL_REG_b.RTM_CTRL_PWR_DN_INFO;
}

/*******************************************************************************************************************//**
 * Sets the target wakeup time and sleep ID.
 *
 * @param[in] sleep_id      The sleep ID for which to set the wakeup time.
 * @param[in] wakeup_time   The target wakeup time.
 **********************************************************************************************************************/
BSP_PLACE_CODE_IN_RAM void bsp_prv_pd_wakeup_counter_set (uint32_t sleep_id, uint64_t wakeup_time)
{
    RTC->RTM_CONTROL_REG_b.RTM_CTRL_PWR_DN_INFO = sleep_id & 0xf;
    RTC->WAKEUP_CNT_1_REG_b.WAKEUP_CNT_1        = (uint32_t) (wakeup_time >> 32) & 0xf;
    RTC->WAKEUP_CNT_0_REG_b.WAKEUP_CNT_0        = (uint32_t) (wakeup_time) & 0xffffffff;
}

/*******************************************************************************************************************//**
 * Gets the current value of the wake-up counter, which operates at 32kHz.
 *
 * @return The current wakeup time, represented as a 64-bit value.
 **********************************************************************************************************************/
BSP_PLACE_CODE_IN_RAM uint64_t bsp_prv_pd_wakeup_counter_get (void)
{
    uint64_t   ret_time;
    uint32_t * pret_time = (uint32_t *) &ret_time;
    uint32_t   temp1, temp2;

    /* Read wakeup counter */
    temp2 = RTC->WAKEUP_CNT_0_REG;
    temp1 = RTC->WAKEUP_CNT_1_REG & 0x0f;

    memcpy(pret_time, &temp2, 4);
    memcpy(pret_time + 1, &temp1, 4);

    return ret_time;
}

/*******************************************************************************************************************//**
 * @brief Enable RTC brown-out and black-out detection.
 *
 * This function enables the RTC brown-out and black-out detection circuits and sets the corresponding callback functions.
 *
 * @param[in] brown_callback  The callback function to be called on a brown-out event.
 * @param[in] black_callback  The callback function to be called on a black-out event.
 **********************************************************************************************************************/
void bsp_rtc_enable_bod (BSP_RTC_BOD_CALLBACK_TYPE brown_callback, BSP_RTC_BOD_CALLBACK_TYPE black_callback)
{
    FSP_PARAMETER_NOT_USED(brown_callback);
    FSP_PARAMETER_NOT_USED(black_callback);
#if BSP_DEVICE_REVISION == DEVICE_REV_A
    if (brown_callback)
    {
        bsp_rtc_brown_callback = brown_callback;
    }

    if (black_callback)
    {
        bsp_rtc_black_callback = black_callback;
    }

    NVIC_EnableIRQ(RTC_IF_BROWN_IRQn);
    NVIC_EnableIRQ(RTC_IF_BLACK_IRQn);

    RTC->BOR_CIRCUIT_REG_b.BR_OUT_CTRL = 0x05;
    RTC->BOR_CIRCUIT_REG_b.BL_OUT_CTRL = 0x04;

    RTC->BOR_CIRCUIT_REG_b.BR_OUT_EN = 0x01;
    RTC->BOR_CIRCUIT_REG_b.BL_OUT_EN = 0x01;

    RTC->ENABLE_CTRL_REG_b.BROWN_OUT_INT_EN = 0x01;
    RTC->ENABLE_CTRL_REG_b.BLACK_OUT_INT_EN = 0x01;
#endif
}

/*******************************************************************************************************************//**
 * @brief Disable RTC brown-out and black-out detection.
 *
 * This function disables the RTC brown-out and black-out detection circuits.
 **********************************************************************************************************************/
void bsp_rtc_disable_bod (void)
{
    NVIC_DisableIRQ(RTC_IF_BROWN_IRQn);
    NVIC_DisableIRQ(RTC_IF_BLACK_IRQn);

    RTC->BOR_CIRCUIT_REG_b.BR_OUT_EN = 0x00;
    RTC->BOR_CIRCUIT_REG_b.BL_OUT_EN = 0x00;
}

/*******************************************************************************************************************//**
 * @brief Get the brown-out status.
 *
 * This function returns the current status of the brown-out detection circuit.
 *
 * @return The brown-out status.
 **********************************************************************************************************************/
int bsp_rtc_get_brown_out_status (void)
{
    return (int) RTC->BOR_CIRCUIT_REG_b.BR_STATUS_READ;
}

/*******************************************************************************************************************//**
 * @brief RTC black-out interrupt handler.
 *
 * This function is the interrupt handler for the RTC black-out event. It calls the registered black-out callback function.
 **********************************************************************************************************************/
BSP_PLACE_CODE_IN_RAM void RTC_IF_BLACK_Handler (void)
{
    if (bsp_rtc_black_callback)
    {
        bsp_rtc_black_callback();
    }
}

/*******************************************************************************************************************//**
 * @brief RTC brown-out interrupt handler.
 *
 * This function is the interrupt handler for the RTC brown-out event. It calls the registered brown-out callback function.
 **********************************************************************************************************************/
BSP_PLACE_CODE_IN_RAM void RTC_IF_BROWN_Handler (void)
{
    if (bsp_rtc_brown_callback)
    {
        bsp_rtc_brown_callback();
    }
}
