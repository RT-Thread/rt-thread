 /**
   *********************************************************************************
   *
   * @file    ald_lcd.c
   * @brief   LCD module driver.
   *
   * @version V1.0
   * @date    29 Nov 2017
   * @author  AE Team
   * @note
   *
   * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
   *
   *********************************************************************************
   */

#include "ald_lcd.h"

/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup LCD LCD
  * @brief LCD module library
  * @{
  */
#ifdef ALD_LCD

/** @defgroup LCD_Public_Functions LCD Public Functions
  * @{
  */

/** @defgroup LCD_Public_Functions_Group1 Initialize and Enable functions
  * @brief Initialize and Enable Functions
  * @{
  */

/**
  * @brief Initializes the LCD Peripheral according to the specified parameters.
  * @note This function can be used only when the LCD is disabled.
  * @param hperh: Pointer to a lcd_handle_t structure that contains
  *               the configuration information for the specified LCD.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_lcd_init(lcd_handle_t *hperh)
{
	uint16_t delay = 0;

	assert_param(IS_LCD_PERH_TYPE(hperh->perh));
	assert_param(IS_LCD_VCHPS_TYPE(hperh->init.lcd_vchps));
	assert_param(IS_LCD_VSEL_TYPE(hperh->init.lcd_vsel));
	assert_param(IS_LCD_FUNC_TYPE(hperh->init.lcd_vbufld));
	assert_param(IS_LCD_FUNC_TYPE(hperh->init.lcd_vbufhd));
	assert_param(IS_LCD_LEVEL_TYPE(hperh->init.lcd_dsld));
	assert_param(IS_LCD_LEVEL_TYPE(hperh->init.lcd_dshd));
	assert_param(IS_LCD_RES_TYPE(hperh->init.lcd_resld));
	assert_param(IS_LCD_RES_TYPE(hperh->init.lcd_reshd));
	assert_param(IS_LCD_BIAS_TYPE(hperh->init.lcd_bias));
	assert_param(IS_LCD_DUTY_TYPE(hperh->init.lcd_duty));
	assert_param(IS_LCD_WFS_TYPE(hperh->init.lcd_wfs));
	assert_param(IS_LCD_PRS_TYPE(hperh->init.lcd_prs));
	assert_param(IS_LCD_DIV_TYPE(hperh->init.lcd_div));
	assert_param(IS_LCD_DEAD_TYPE(hperh->init.lcd_dead));
	assert_param(IS_LCD_PON_TYPE(hperh->init.lcd_pon));
	assert_param(IS_LCD_VGS_TYPE(hperh->init.lcd_vgs));

	__LOCK(hperh);

	ald_cmu_lcd_clock_select(hperh->init.clock);

	MODIFY_REG(hperh->perh->FCR, LCD_FCR_WFS_MSK, hperh->init.lcd_wfs << LCD_FCR_WFS_POS);
	MODIFY_REG(hperh->perh->FCR, LCD_FCR_PRS_MSK, hperh->init.lcd_prs << LCD_FCR_PRS_POSS);
	for (delay = 0; delay < 3000; delay++);
	MODIFY_REG(hperh->perh->FCR, LCD_FCR_DIV_MSK, hperh->init.lcd_div << LCD_FCR_DIV_POSS);
	MODIFY_REG(hperh->perh->FCR, LCD_FCR_DEAD_MSK, hperh->init.lcd_dead << LCD_FCR_DEAD_POSS);
	MODIFY_REG(hperh->perh->FCR, LCD_FCR_PON_MSK, hperh->init.lcd_pon << LCD_FCR_PON_POSS);
	MODIFY_REG(hperh->perh->FCR, LCD_FCR_VGS_MSK, hperh->init.lcd_vgs << LCD_FCR_VGS_POSS);

	MODIFY_REG(hperh->perh->CR, LCD_CR_DUTY_MSK, hperh->init.lcd_duty << LCD_CR_DUTY_POSS);
	MODIFY_REG(hperh->perh->CR, LCD_CR_BIAS_MSK, hperh->init.lcd_bias << LCD_CR_BIAS_POSS);
	MODIFY_REG(hperh->perh->CR, LCD_CR_VBUFHD_MSK, hperh->init.lcd_vbufhd << LCD_CR_VBUFHD_POS);
	MODIFY_REG(hperh->perh->CR, LCD_CR_VBUFLD_MSK, hperh->init.lcd_vbufld << LCD_CR_VBUFLD_POS);
	MODIFY_REG(hperh->perh->CR, LCD_CR_DSHD_MSK, hperh->init.lcd_dshd << LCD_CR_DSHD_POSS);
	MODIFY_REG(hperh->perh->CR, LCD_CR_DSLD_MSK, hperh->init.lcd_dsld << LCD_CR_DSLD_POSS);
	MODIFY_REG(hperh->perh->CR, LCD_CR_RESHD_MSK, hperh->init.lcd_reshd << LCD_CR_RESHD_POSS);
	MODIFY_REG(hperh->perh->CR, LCD_CR_RESLD_MSK, hperh->init.lcd_resld << LCD_CR_RESLD_POSS);
	MODIFY_REG(hperh->perh->CR, LCD_CR_VSEL_MSK, hperh->init.lcd_vsel << LCD_CR_VSEL_POSS);
	MODIFY_REG(hperh->perh->CR, LCD_CR_VCHPS_MSK, hperh->init.lcd_vchps << LCD_CR_VCHPS_POSS);

	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief Enables or disables the LCD controller.
  * @param hperh: Pointer to a lcd_handle_t structure that contains
  *               the configuration information for the specified LCD.
  * @param state: This parameter can be: ENABLE or DISABLE.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_lcd_cmd(lcd_handle_t *hperh, type_func_t state)
{
	assert_param(IS_LCD_PERH_TYPE(hperh->perh));
	assert_param(IS_FUNC_STATE(state));

	__LOCK(hperh);

	MODIFY_REG(hperh->perh->CR, LCD_CR_OE_MSK, state << LCD_CR_OE_POS);
	MODIFY_REG(hperh->perh->CR, LCD_CR_EN_MSK, state << LCD_CR_EN_POS);

	__UNLOCK(hperh);
	return OK;
}
/**
  * @}
  */

/** @defgroup LCD_Public_Functions_Group2 Config output functions
  * @brief Config output and blink functions
  * @{
  */

/**
  * @brief Configures the LCD blink mode and blink frequency.
  * @param hperh: Pointer to a lcd_handle_t structure that contains
  *               the configuration information for the specified LCD.
  * @param blink_mode: Specifies the LCD blink mode.
  * @param blink_freq: Specifies the LCD blink frequency.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_lcd_blink_config(lcd_handle_t *hperh, lcd_blink_t blink_mode, lcd_blfrq_t blink_freq)
{
	uint16_t delay = 0;
	assert_param(IS_LCD_PERH_TYPE(hperh->perh));
	assert_param(IS_LCD_BLINK_MODE(blink_mode));
	assert_param(IS_LCD_BLFRQ_TYPE(blink_freq));
	__LOCK(hperh);

	MODIFY_REG(hperh->perh->FCR, LCD_FCR_BLMOD_MSK, blink_mode << LCD_FCR_BLMOD_POSS);
	for (delay = 0; delay < 3000; delay++);
	MODIFY_REG(hperh->perh->FCR, LCD_FCR_BLFRQ_MSK, blink_freq << LCD_FCR_BLFRQ_POSS);

	__UNLOCK(hperh);
	return OK;
 }

/**
  * @brief Control segment port enable or disable
  * @param hperh: Pointer to a lcd_handle_t structure that contains
  *               the configuration information for the specified LCD.
  * @param seg: Specifies the LCD segment index
  * @param seg_data: Specifies LCD segment data to be written to control segment output enable.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_lcd_write_seg(lcd_handle_t *hperh, lcd_seg_t seg, uint32_t seg_data)
{
	assert_param(IS_LCD_PERH_TYPE(hperh->perh));
	assert_param(IS_LCD_SEG_TYPE(seg));
	__LOCK(hperh);

	if (seg == SEG_0_TO_31)
		WRITE_REG(hperh->perh->SEGCR0, seg_data);
	else
		WRITE_REG(hperh->perh->SEGCR1, seg_data);

	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief Writes a word in the specific LCD buffer to determine display.
  * @param hperh: Pointer to a lcd_handle_t structure that contains
  *               the configuration information for the specified LCD.
  * @param buf: Specifies the LCD buffer index.
  * @param buf_data: Specifies LCD buffer data to be written to control display.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_lcd_write(lcd_handle_t *hperh, uint8_t buf, uint32_t buf_data)
{
	assert_param(IS_LCD_PERH_TYPE(hperh->perh));
	assert_param(IS_LCD_BUFFER_TYPE(buf));

	__LOCK(hperh);
	WRITE_REG(hperh->perh->BUF[buf], buf_data);
	__UNLOCK(hperh);

	return OK;
}
/**
  * @}
  */

/** @defgroup LCD_Public_Functions_Group3 Peripheral State functions
  * @brief LCD State functions
  * @{
  */

/**
  * @brief Checks whether the specified LCD flag is set or not.
  * @param hperh: Pointer to a lcd_handle_t structure that contains
  *               the configuration information for the specified LCD.
  * @param lcd_status: Specifies the flag to check.
  * @retval The new state of LCD_STATUS
  */
uint32_t ald_lcd_get_status(lcd_handle_t *hperh, lcd_status_t lcd_status)
{
	assert_param(IS_LCD_PERH_TYPE(hperh->perh));
	assert_param(IS_LCD_STATUS_TYPE(lcd_status));

	if (lcd_status == LCD_STATUS_ALL)
		return hperh->perh->SR;
	else
		return hperh->perh->SR & lcd_status ? 1 : 0;
}
/**
  * @}
  */

/** @defgroup LCD_Public_Functions_Group4 Interrupt functions
  * @brief LCD Interrupt functions
  * @{
  */

/**
  * @brief Enable or disable the specified interrupt
  * @param hperh: Pointer to a lcd_handle_t structure that contains
  *               the configuration information for the specified LCD.
  * @param it: Specifies the interrupt type to be enabled or disabled
  *        @arg @ref LCD_IT_SOF Start of frame interrupt enable
  *        @arg @ref LCD_IT_UDD Update display done interrupt
  * @param state: New state of the specified interrupt.
  *        This parameter can be: ENABLE or DISABLE
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_lcd_interrupt_config(lcd_handle_t *hperh, lcd_it_t it, type_func_t state)
{
	assert_param(IS_LCD_PERH_TYPE(hperh->perh));
	assert_param(IS_LCD_IT_TYPE(it));
	assert_param(IS_FUNC_STATE(state));
	__LOCK(hperh);

	if (state)
		SET_BIT(hperh->perh->IE, it);
	else
		CLEAR_BIT(hperh->perh->IE, it);

	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief Checks whether the specified interrupt has set or not.
  * @param hperh: Pointer to a lcd_handle_t structure that contains
  *               the configuration information for the specified LCD.
  * @param it: Specifies the interrupt type to check
  *        This parameter can be one of the following values:
  *        @arg @ref LCD_IT_SOF Start of frame interrupt enable
  *        @arg @ref LCD_IT_UDD Update display done interrupt
  * @retval The new state of the LCD_IT
  */
flag_status_t ald_lcd_get_it_status(lcd_handle_t *hperh, lcd_it_t it)
{
	assert_param(IS_LCD_PERH_TYPE(hperh->perh));
	assert_param(IS_LCD_IT_TYPE(it));

	return hperh->perh->IE & it ? SET : RESET;
}

/**
  * @brief Checks whether the specified interrupt has occurred or not.
  * @param hperh: Pointer to a lcd_handle_t structure that contains
  *               the configuration information for the specified LCD.
  * @param flag: Specifies the interrupt type to check
  *        This parameter can be one of the following values:
  *        @arg @ref LCD_FLAG_SOF Start of frame interrupt enable
  *        @arg @ref LCD_FLAG_UDD Update display done interrupt
  * @retval The new state of the LCD_IT
  */
it_status_t ald_lcd_get_flag_status(lcd_handle_t *hperh, lcd_flag_t flag)
{
	assert_param(IS_LCD_PERH_TYPE(hperh->perh));
	assert_param(IS_LCD_FLAG_TYPE(flag));

	return hperh->perh->IF & flag ? SET : RESET;
}

/**
  * @brief Clear interrupt state flag
  * @param hperh: Pointer to a lcd_handle_t structure that contains
  *               the configuration information for the specified LCD.
  * @param flag: Specifies the interrupt type to clear
  *        This parameter can be one of the following values:
  *        @arg @ref LCD_FLAG_SOF Start of frame interrupt enable
  *        @arg @ref LCD_FLAG_UDD Update display done interrupt
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_lcd_clear_flag_status(lcd_handle_t *hperh, lcd_flag_t flag)
{
	assert_param(IS_LCD_PERH_TYPE(hperh->perh));
	assert_param(IS_LCD_FLAG_TYPE(flag));

	__LOCK(hperh);
	WRITE_REG(hperh->perh->IFCR, flag);
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  This function handles LCD event interrupt request.
  * @param hperh: Pointer to a lcd_handle_t structure that contains
  *               the configuration information for the specified LCD.
  * @retval None
  */
void ald_lcd_irq_handler(lcd_handle_t *hperh)
{
	if (ald_lcd_get_flag_status(hperh, LCD_FLAG_UDD)) {
		ald_lcd_clear_flag_status(hperh, LCD_FLAG_UDD);

		if (hperh->display_cplt_cbk)
			hperh->display_cplt_cbk(hperh);
	}

	if (ald_lcd_get_flag_status(hperh, LCD_FLAG_SOF)) {
		ald_lcd_clear_flag_status(hperh, LCD_FLAG_SOF);

		if (hperh->frame_start_cbk)
			hperh->frame_start_cbk(hperh);
	}

	return;
}
/**
  * @}
  */
/**
  * @}
  */
#endif /* ALD_LCD */
/**
  * @}
  */
/**
  * @}
  */
