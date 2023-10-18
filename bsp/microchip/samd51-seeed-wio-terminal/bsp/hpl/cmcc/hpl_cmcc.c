/**
 * \file
 *
 * \brief Generic CMCC(Cortex M Cache Controller) related functionality.
 *
 * Copyright (c)2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <compiler.h>
#include <hpl_cmcc.h>
#include <hpl_cmcc_config.h>

/**
 * \brief Initialize Cache Module
 *
 * This function does low level cache configuration.
 *
 * \return initialize status
 */
int32_t _cmcc_init(void)
{
	int32_t return_value;

	_cmcc_disable(CMCC);

	if (_is_cache_disabled(CMCC)) {
		hri_cmcc_write_CFG_reg(
		    CMCC,
		    (CMCC_CFG_CSIZESW(CONF_CMCC_CACHE_SIZE) | (CONF_CMCC_DATA_CACHE_DISABLE << CMCC_CFG_DCDIS_Pos)
		     | (CONF_CMCC_INST_CACHE_DISABLE << CMCC_CFG_ICDIS_Pos) | (CONF_CMCC_CLK_GATING_DISABLE)));

		_cmcc_enable(CMCC);
		return_value = _is_cache_enabled(CMCC) == true ? ERR_NONE : ERR_FAILURE;
	} else {
		return_value = ERR_NOT_INITIALIZED;
	}

	return return_value;
}

/**
 * \brief Configure CMCC module
 *
 * \param[in] pointer pointing to the starting address of CMCC module
 * \param[in] cache configuration structure pointer
 *
 * \return status of operation
 */
int32_t _cmcc_configure(const void *hw, struct _cache_cfg *cache_ctrl)
{
	int32_t return_value;

	_cmcc_disable(hw);

	if (_is_cache_disabled(hw)) {
		hri_cmcc_write_CFG_reg(
		    hw,
		    (CMCC_CFG_CSIZESW(cache_ctrl->cache_size) | (cache_ctrl->data_cache_disable << CMCC_CFG_DCDIS_Pos)
		     | (cache_ctrl->inst_cache_disable << CMCC_CFG_ICDIS_Pos) | (cache_ctrl->gclk_gate_disable)));

		return_value = ERR_NONE;
	} else {
		return_value = ERR_NOT_INITIALIZED;
	}

	return return_value;
}

/**
 * \brief Enable data cache in CMCC module
 *
 * \param[in] pointer pointing to the starting address of CMCC module
 * \param[in] boolean 1 -> Enable the data cache, 0 -> disable the data cache
 *
 * \return status of operation
 */
int32_t _cmcc_enable_data_cache(const void *hw, bool value)
{
	uint32_t tmp;
	int32_t  ret;

	tmp = hri_cmcc_read_CFG_reg(hw);
	tmp &= ~CMCC_CFG_DCDIS;
	tmp |= ((!value) << CMCC_CFG_DCDIS_Pos);

	ret = _cmcc_disable(hw);
	hri_cmcc_write_CFG_reg(hw, tmp);
	ret = _cmcc_enable(hw);

	return ret;
}

/**
 * \brief Enable instruction cache in CMCC module
 *
 * \param[in] pointer pointing to the starting address of CMCC module
 * \param[in] boolean 1 -> Enable the inst cache, 0 -> disable the inst cache
 *
 * \return status of operation
 */
int32_t _cmcc_enable_inst_cache(const void *hw, bool value)
{
	uint32_t tmp;
	int32_t  ret;

	tmp = hri_cmcc_read_CFG_reg(hw);
	tmp &= ~CMCC_CFG_ICDIS;
	tmp |= ((!value) << CMCC_CFG_ICDIS_Pos);

	ret = _cmcc_disable(hw);
	hri_cmcc_write_CFG_reg(hw, tmp);
	ret = _cmcc_enable(hw);

	return ret;
}

/**
 * \brief Enable clock gating in CMCC module
 *
 * \param[in] pointer pointing to the starting address of CMCC module
 * \param[in] boolean 1 -> Enable the clock gate, 0 -> disable the clock gate
 *
 * \return status of operation
 */
int32_t _cmcc_enable_clock_gating(const void *hw, bool value)
{
	uint32_t tmp;
	int32_t  ret;

	tmp = hri_cmcc_read_CFG_reg(hw);
	tmp |= value;

	ret = _cmcc_disable(hw);
	hri_cmcc_write_CFG_reg(hw, tmp);
	ret = _cmcc_enable(hw);

	return ret;
}

/**
 * \brief Configure the cache size in CMCC module
 *
 * \param[in] pointer pointing to the starting address of CMCC module
 * \param[in] element from cache size configuration enumerator
 *				0->1K, 1->2K, 2->4K(default)
 *
 * \return status of operation
 */
int32_t _cmcc_configure_cache_size(const void *hw, enum conf_cache_size size)
{
	uint32_t tmp;
	int32_t  ret;

	tmp = hri_cmcc_read_CFG_reg(hw);
	tmp &= (~CMCC_CFG_CSIZESW_Msk);
	tmp |= (size << CMCC_CFG_CSIZESW_Pos);

	ret = _cmcc_disable(hw);
	hri_cmcc_write_CFG_reg(hw, tmp);
	ret = _cmcc_enable(hw);

	return ret;
}

/**
 * \brief Lock the mentioned WAY in CMCC module
 *
 * \param[in] pointer pointing to the starting address of CMCC module
 * \param[in] element from "way_num_index" enumerator
 *
 * \return status of operation
 */
int32_t _cmcc_lock_way(const void *hw, enum way_num_index num)
{
	uint32_t tmp;
	int32_t  ret;

	tmp = hri_cmcc_read_LCKWAY_reg(hw);
	tmp |= CMCC_LCKWAY_LCKWAY(num);

	ret = _cmcc_disable(hw);
	hri_cmcc_write_LCKWAY_reg(hw, tmp);
	ret = _cmcc_enable(hw);

	return ret;
}

/**
 * \brief Unlock the mentioned WAY in CMCC module
 *
 * \param[in] pointer pointing to the starting address of CMCC module
 * \param[in] element from "way_num_index" enumerator
 *
 * \return status of operation
 */
int32_t _cmcc_unlock_way(const void *hw, enum way_num_index num)
{
	uint32_t tmp;
	int32_t  ret;

	tmp = hri_cmcc_read_LCKWAY_reg(hw);
	tmp &= (~CMCC_LCKWAY_LCKWAY(num));

	ret = _cmcc_disable(hw);
	hri_cmcc_write_LCKWAY_reg(hw, tmp);
	ret = _cmcc_enable(hw);

	return ret;
}

/**
 * \brief Invalidate the mentioned cache line in CMCC module
 *
 * \param[in] pointer pointing to the starting address of CMCC module
 * \param[in] element from "way_num" enumerator (valid arg is 0-3)
 * \param[in] line number (valid arg is 0-63 as each way will have 64 lines)
 *
 * \return status of operation
 */
int32_t _cmcc_invalidate_by_line(const void *hw, uint8_t way_num, uint8_t line_num)
{
	int32_t return_value;

	if ((way_num < CMCC_WAY_NOS) && (line_num < CMCC_LINE_NOS)) {
		_cmcc_disable(hw);
		while (!(_is_cache_disabled(hw)))
			;
		hri_cmcc_write_MAINT1_reg(hw, (CMCC_MAINT1_INDEX(line_num) | CMCC_MAINT1_WAY(way_num)));
		return_value = ERR_NONE;
	} else {
		return_value = ERR_INVALID_ARG;
	}

	return return_value;
}

/**
 * \brief Invalidate entire cache entries in CMCC module
 *
 * \param[in] pointer pointing to the starting address of CMCC module
 *
 * \return status of operation
 */
int32_t _cmcc_invalidate_all(const void *hw)
{
	int32_t return_value;

	_cmcc_disable(hw);
	if (_is_cache_disabled(hw)) {
		hri_cmcc_write_MAINT0_reg(hw, CMCC_MAINT0_INVALL);
		return_value = ERR_NONE;
	} else {
		return_value = ERR_FAILURE;
	}

	return return_value;
}

/**
 * \brief Configure cache monitor in CMCC module
 *
 * \param[in] pointer pointing to the starting address of CMCC module
 * \param[in] element from cache monitor configurations enumerator
 *
 * \return status of operation
 */
int32_t _cmcc_configure_monitor(const void *hw, enum conf_cache_monitor monitor_cfg)
{
	hri_cmcc_write_MCFG_reg(hw, CMCC_MCFG_MODE(monitor_cfg));

	return ERR_NONE;
}

/**
 * \brief Enable cache monitor in CMCC module
 *
 * \param[in] pointer pointing to the starting address of CMCC module
 *
 * \return status of operation
 */
int32_t _cmcc_enable_monitor(const void *hw)
{
	hri_cmcc_write_MEN_reg(hw, CMCC_MEN_MENABLE);

	return ERR_NONE;
}

/**
 * \brief Disable cache monitor in CMCC module
 *
 * \param[in] pointer pointing to the starting address of CMCC module
 *
 * \return status of operation
 */
int32_t _cmcc_disable_monitor(const void *hw)
{
	hri_cmcc_write_MEN_reg(hw, (CMCC_MONITOR_DISABLE << CMCC_MEN_MENABLE_Pos));

	return ERR_NONE;
}

/**
 * \brief Reset cache monitor in CMCC module
 *
 * \param[in] pointer pointing to the starting address of CMCC module
 *
 * \return status of operation
 */
int32_t _cmcc_reset_monitor(const void *hw)
{
	hri_cmcc_write_MCTRL_reg(hw, CMCC_MCTRL_SWRST);

	return ERR_NONE;
}

/**
 * \brief Get cache monitor event counter value from CMCC module
 *
 * \param[in] pointer pointing to the starting address of CMCC module
 *
 * \return event counter value
 */
uint32_t _cmcc_get_monitor_event_count(const void *hw)
{
	return hri_cmcc_read_MSR_reg(hw);
}
