/**
  ******************************************************************************
  * @file    ald_rtchw.c
  * @brief   RTCHW module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the RTC peripheral:
  *           + Calibration functions
  * @version V1.0
  * @date    25 Apr 2019
  * @author  AE Team
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  ********************************************************************************
  */

#include "ald_rtchw.h"

/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup RTCHW RTCHW
  * @brief RTCHW module driver
  * @{
  */
#ifdef ALD_RTC

/** @addtogroup RTCHW_Private_Functions  RTCHW Private Functions
  * @{
  */
/**
  * @brief  delay losc clock
  * @param  u: clock numbers.
  * @retval None.
  */
static void delay_losc_clk(uint16_t u)
{
	uint16_t i, j;

	for (i = 0; i < u; i++) {
                for (j = 0; j < 60; j++) {
                        __ASM volatile ("nop");
                }
	}
}

/**
  * @brief  Check parameter for calibation
  * @param  config: pointer to rtc_hw_cali_offset_t structure.
  * @param  mode: Running mode, see @ref rtc_hw_cali_mode_t.
  * @retval Status.
  */
static uint8_t rtc_hw_auto_check(rtc_hw_cali_offset_t *config, rtc_hw_cali_mode_t mode)
{
	uint8_t tom = READ_BITS(TSENSE->CR, TSENSE_CR_TOM_MSK, TSENSE_CR_TOM_POSS);
	uint8_t shift[8] = {0, 2, 4, 6, 8, 8, 8, 8};

	if (mode == RTC_CALI_MODE_NORMAL) {
		if ((RTC->CALCON & 0x1F3000F) != (RTCINFO->RTC_CALCR & 0x1F3000F))
			return 1;
	}
	else {
		if ((RTC->CALCON & 0x183000F) != (RTCINFO->RTC_CALCR & 0x183000F))
			return 1;

		if (READ_BITS(RTC->CALCON, RTC_CALCON_TCP_MSK, RTC_CALCON_TCP_POSS) != 7)	/* when sleep mode */ 
			return 1;
	}

	if ((TSENSE->CR & 0x7702) != (RTCINFO->TEMP_CR & 0x7702))
		return 1;
	if (RTC->TEMPBDR != RTCINFO->RTC_TEMPBDR + config->offset_rtc_bdr)
		return 1;
	if (RTC->LTAXR != RTCINFO->RTC_LTAXR + config->offset_ltaxr)
		return 1;
	if (RTC->HTAXR != RTCINFO->RTC_HTAXR + config->offset_htaxr)
		return 1;
	if (RTC->HTAXR != RTCINFO->RTC_HTCAR + config->offset_htcar)
		return 1;
	if (RTC->HTCBR != RTCINFO->RTC_HTCBR + config->offset_htcbr)
		return 1;
	if (RTC->HTCCR != RTCINFO->RTC_HTCCR + config->offset_htccr)
		return 1;
	if (RTC->HTCDR != RTCINFO->RTC_HTCDR + config->offset_htcdr)
		return 1;
	if (RTC->HTCER != RTCINFO->RTC_HTCER + config->offset_htcer)
		return 1;
	if (RTC->LTAXR != RTCINFO->RTC_LTCAR + config->offset_ltcar)
		return 1;
	if (RTC->LTCBR != RTCINFO->RTC_LTCBR + config->offset_ltcbr)
		return 1;
	if (RTC->LTCCR != RTCINFO->RTC_LTCCR + config->offset_ltccr)
		return 1;
	if (RTC->LTCDR != RTCINFO->RTC_LTCDR + config->offset_ltcdr)
		return 1;
	if (RTC->LTCER != RTCINFO->RTC_LTCER + config->offset_ltcer)
		return 1;
	if (TSENSE->TBDR != (RTCINFO->TEMP_TBDR & 0xFFFF) + config->offset_temp_bdr)
		return 1;
	if (TSENSE->LTGR != RTCINFO->TEMP_LTGR + config->offset_ltgr)
		return 1;
	if (TSENSE->HTGR != RTCINFO->TEMP_HTGR + config->offset_htgr)
		return 1;
	if (TSENSE->TCALBDR != (((RTCINFO->TEMP_TCALBDR & 0x1FFFFFF) >> shift[tom]) & 0x1FFFF)
				 + config->offset_tcalbdr)
		return 1;

	return 0;
}
/**
  * @}
  */

/** @defgroup RTCHW_Public_Functions RTCHW Public Functions
  * @{
  */
/**
  * @brief  Hardware automatic calibate
  * @param  config: pointer to rtc_hw_cali_offset_t structure.
  * @param  mode: Running mode, see @ref rtc_hw_cali_mode_t
  * @retval None
  */
void ald_rtc_hw_auto_cali(rtc_hw_cali_offset_t *config, rtc_hw_cali_mode_t mode)
{
	uint8_t shift[8] = {0, 2, 4, 6, 8, 8, 8, 8};
	uint8_t tmp;
	uint32_t v = 0;
	uint16_t temp_calf;

	if (!(rtc_hw_auto_check(config, mode)))
		return;

	RTC_UNLOCK();
	RTC_CALI_UNLOCK();
	TSENSE_UNLOCK();

	temp_calf = (uint16_t)RTC->CALDR;
	while ((READ_BITS(RTC->IFR, RTC_IFR_TCCF_MSK, RTC_IFR_TCCF_POS) == 1) && (v < 0x20000))		/* no usr trig */
		v++;

	MODIFY_REG(RTC->CALCON, RTC_CALCON_TCM_MSK, 0 << RTC_CALCON_TCM_POSS);		/* disable auto compensation */
	MODIFY_REG(TSENSE->CR, TSENSE_CR_REQEN_MSK, 0 << TSENSE_CR_REQEN_POS);		/* disable temp */

	RTC->CALDR = temp_calf;
	delay_losc_clk(3);

	if (mode == RTC_CALI_MODE_NORMAL) {
		v           = RTC->CALCON & ~0x01F0000F;
		RTC->CALCON = v | (RTCINFO->RTC_CALCR & 0x01F0000F);
	}
	else {
		v           = RTC->CALCON & ~0x0180000F;
		RTC->CALCON = v | (RTCINFO->RTC_CALCR & 0x0180000F);
		MODIFY_REG(RTC->CALCON, RTC_CALCON_TCP_MSK, 7 << RTC_CALCON_TCP_POSS);        // when sleep mode, caluate once in 1h
	}

	RTC->TEMPBDR  = RTCINFO->RTC_TEMPBDR + config->offset_rtc_bdr;
	RTC->LTAXR    = RTCINFO->RTC_LTAXR + config->offset_ltaxr;
	RTC->HTAXR    = RTCINFO->RTC_HTAXR + config->offset_htaxr;
	RTC->LTCAR    = RTCINFO->RTC_LTCAR + config->offset_ltcar;
	RTC->LTCBR    = RTCINFO->RTC_LTCBR + config->offset_ltcbr;
	RTC->LTCCR    = RTCINFO->RTC_LTCCR + config->offset_ltccr;
	RTC->LTCDR    = RTCINFO->RTC_LTCDR + config->offset_ltcdr;
	RTC->LTCER    = RTCINFO->RTC_LTCER + config->offset_ltcer;
	RTC->HTCAR    = RTCINFO->RTC_HTCAR + config->offset_htcar;
	RTC->HTCBR    = RTCINFO->RTC_HTCBR + config->offset_htcbr;
	RTC->HTCCR    = RTCINFO->RTC_HTCCR + config->offset_htccr;
	RTC->HTCDR    = RTCINFO->RTC_HTCDR + config->offset_htcdr;
	RTC->HTCER    = RTCINFO->RTC_HTCER + config->offset_htcer;
	MODIFY_REG(RTC->CON, RTC_CON_CKOS_MSK, 5 << RTC_CON_CKOS_POSS);		/* output accuracy 1Hz */

	v               = TSENSE->CR & ~0x00007700;
	TSENSE->CR      = v | (RTCINFO->TEMP_CR & 0x00007700);
	TSENSE->HTGR    = RTCINFO->TEMP_HTGR + config->offset_htgr;
	TSENSE->LTGR    = RTCINFO->TEMP_LTGR + config->offset_ltgr;
	tmp             = READ_BITS(RTCINFO->TEMP_CR, TSENSE_CR_TOM_MSK, TSENSE_CR_TOM_POSS);
	TSENSE->TCALBDR = ((RTCINFO->TEMP_TCALBDR & 0x1FFFFFF) >> shift[tmp]) + config->offset_tcalbdr;
	TSENSE->TBDR    = RTCINFO->TEMP_TBDR + config->offset_temp_bdr;

	delay_losc_clk(3);
	tmp = READ_BITS(RTCINFO->TEMP_CR, TSENSE_CR_REQEN_MSK, TSENSE_CR_REQEN_POS);
	MODIFY_REG(TSENSE->CR, TSENSE_CR_REQEN_MSK, tmp << TSENSE_CR_REQEN_POS);
	MODIFY_REG(RTC->CALCON, RTC_CALCON_TCM_MSK, 3 << RTC_CALCON_TCM_POSS);	/* usr trig */

	delay_losc_clk(3);
	MODIFY_REG(RTC->TEMPR, RTC_TEMPR_VAL_MSK, 1 << RTC_TEMPR_VAL_POSS);	/* trig immediate*/

	delay_losc_clk(3);
	tmp           = READ_BITS(RTCINFO->RTC_CALCR, RTC_CALCON_TCM_MSK, RTC_CALCON_TCM_POSS);
	MODIFY_REG(RTC->CALCON, RTC_CALCON_TCM_MSK, tmp << RTC_CALCON_TCM_POSS);

	RTC_CALI_LOCK();
	RTC_LOCK();
	TSENSE_LOCK();
	return;
}
/**
  * @}
  */
#endif /* ALD_RTC */
/**
  * @}
  */
/**
  * @}
  */
