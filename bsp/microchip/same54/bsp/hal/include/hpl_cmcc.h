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

#ifndef HPL_CMCC_H_
#define HPL_CMCC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/**
 * \Cache driver MACROS
 */
#define CMCC_DISABLE 0U
#define CMCC_ENABLE 1U
#define IS_CMCC_DISABLED 0U
#define IS_CMCC_ENABLED 1U
#define CMCC_WAY_NOS 4U
#define CMCC_LINE_NOS 64U
#define CMCC_MONITOR_DISABLE 0U

/**
 * \brief Cache size configurations
 */
enum conf_cache_size { CONF_CSIZE_1KB = 0u, CONF_CSIZE_2KB, CONF_CSIZE_4KB };

/**
 * \brief Way Numbers
 */
enum way_num_index { WAY0 = 1u, WAY1 = 2u, WAY2 = 4u, WAY3 = 8 };

/**
 * \brief Cache monitor configurations
 */
enum conf_cache_monitor { CYCLE_COUNT = 0u, IHIT_COUNT, DHIT_COUNT };

/**
 * \brief Cache configuration structure
 */
struct _cache_cfg {
	enum conf_cache_size cache_size;
	bool                 data_cache_disable;
	bool                 inst_cache_disable;
	bool                 gclk_gate_disable;
};

/**
 * \brief Cache enable status
 */
static inline bool _is_cache_enabled(const void *hw)
{
	return (hri_cmcc_get_SR_CSTS_bit(hw) == IS_CMCC_ENABLED ? true : false);
}

/**
 * \brief Cache disable status
 */
static inline bool _is_cache_disabled(const void *hw)
{
	return (hri_cmcc_get_SR_CSTS_bit(hw) == IS_CMCC_DISABLED ? true : false);
}

/**
 * \brief Cache enable
 */
static inline int32_t _cmcc_enable(const void *hw)
{
	int32_t return_value;

	if (_is_cache_disabled(hw)) {
		hri_cmcc_write_CTRL_reg(hw, CMCC_CTRL_CEN);
		return_value = _is_cache_enabled(hw) == true ? ERR_NONE : ERR_FAILURE;
	} else {
		return_value = ERR_NO_CHANGE;
	}

	return return_value;
}

/**
 * \brief Cache disable
 */
static inline int32_t _cmcc_disable(const void *hw)
{
	hri_cmcc_write_CTRL_reg(hw, (CMCC_DISABLE << CMCC_CTRL_CEN_Pos));
	while (!(_is_cache_disabled(hw)))
		;

	return ERR_NONE;
}

/**
 * \brief Initialize Cache Module
 *
 * This function initialize low level cmcc module configuration.
 *
 * \return initialize status
 */
int32_t _cmcc_init(void);

/**
 * \brief Configure CMCC module
 *
 * \param[in] pointer pointing to the starting address of CMCC module
 * \param[in] cache configuration structure pointer
 *
 * \return status of operation
 */
int32_t _cmcc_configure(const void *hw, struct _cache_cfg *cache_ctrl);

/**
 * \brief Enable data cache in CMCC module
 *
 * \param[in] pointer pointing to the starting address of CMCC module
 * \param[in] boolean 1 -> Enable the data cache, 0 -> disable the data cache
 *
 * \return status of operation
 */
int32_t _cmcc_enable_data_cache(const void *hw, bool value);

/**
 * \brief Enable instruction cache in CMCC module
 *
 * \param[in] pointer pointing to the starting address of CMCC module
 * \param[in] boolean 1 -> Enable the inst cache, 0 -> disable the inst cache
 *
 * \return status of operation
 */
int32_t _cmcc_enable_inst_cache(const void *hw, bool value);

/**
 * \brief Enable clock gating in CMCC module
 *
 * \param[in] pointer pointing to the starting address of CMCC module
 * \param[in] boolean 1 -> Enable the clock gate, 0 -> disable the clock gate
 *
 * \return status of operation
 */
int32_t _cmcc_enable_clock_gating(const void *hw, bool value);

/**
 * \brief Configure the cache size in CMCC module
 *
 * \param[in] pointer pointing to the starting address of CMCC module
 * \param[in] element from cache size configuration enumerator
 *				0->1K, 1->2K, 2->4K(default)
 *
 * \return status of operation
 */
int32_t _cmcc_configure_cache_size(const void *hw, enum conf_cache_size size);

/**
 * \brief Lock the mentioned WAY in CMCC module
 *
 * \param[in] pointer pointing to the starting address of CMCC module
 * \param[in] element from "way_num_index" enumerator
 *
 * \return status of operation
 */
int32_t _cmcc_lock_way(const void *hw, enum way_num_index);

/**
 * \brief Unlock the mentioned WAY in CMCC module
 *
 * \param[in] pointer pointing to the starting address of CMCC module
 * \param[in] element from "way_num_index" enumerator
 *
 * \return status of operation
 */
int32_t _cmcc_unlock_way(const void *hw, enum way_num_index);

/**
 * \brief Invalidate the mentioned cache line in CMCC module
 *
 * \param[in] pointer pointing to the starting address of CMCC module
 * \param[in] element from "way_num" enumerator (valid arg is 0-3)
 * \param[in] line number (valid arg is 0-63 as each way will have 64 lines)
 *
 * \return status of operation
 */
int32_t _cmcc_invalidate_by_line(const void *hw, uint8_t way_num, uint8_t line_num);

/**
 * \brief Invalidate entire cache entries in CMCC module
 *
 * \param[in] pointer pointing to the starting address of CMCC module
 *
 * \return status of operation
 */
int32_t _cmcc_invalidate_all(const void *hw);

/**
 * \brief Configure cache monitor in CMCC module
 *
 * \param[in] pointer pointing to the starting address of CMCC module
 * \param[in] element from cache monitor configurations enumerator
 *
 * \return status of operation
 */
int32_t _cmcc_configure_monitor(const void *hw, enum conf_cache_monitor monitor_cfg);

/**
 * \brief Enable cache monitor in CMCC module
 *
 * \param[in] pointer pointing to the starting address of CMCC module
 *
 * \return status of operation
 */
int32_t _cmcc_enable_monitor(const void *hw);

/**
 * \brief Disable cache monitor in CMCC module
 *
 * \param[in] pointer pointing to the starting address of CMCC module
 *
 * \return status of operation
 */
int32_t _cmcc_disable_monitor(const void *hw);

/**
 * \brief Reset cache monitor in CMCC module
 *
 * \param[in] pointer pointing to the starting address of CMCC module
 *
 * \return status of operation
 */
int32_t _cmcc_reset_monitor(const void *hw);

/**
 * \brief Get cache monitor event counter value from CMCC module
 *
 * \param[in] pointer pointing to the starting address of CMCC module
 *
 * \return event counter value
 */
uint32_t _cmcc_get_monitor_event_count(const void *hw);

#ifdef __cplusplus
}
#endif
#endif /* HPL_CMCC_H_ */
