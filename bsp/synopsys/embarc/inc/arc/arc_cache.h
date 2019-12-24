/* ------------------------------------------
 * Copyright (c) 2016, Synopsys, Inc. All rights reserved.

 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:

 * 1) Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.

 * 2) Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.

 * 3) Neither the name of the Synopsys, Inc., nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * \version 2016.05
 * \date 2014-07-15
 * \author Wayne Ren(Wei.Ren@synopsys.com)
--------------------------------------------- */

/**
 * \file
 * \ingroup	ARC_HAL_MISC_CACHE
 * \brief header file of cache module
 */

#ifndef _ARC_HAL_CACHE_H_
#define _ARC_HAL_CACHE_H_

#include "inc/embARC_toolchain.h"
#include "inc/arc/arc.h"
#include "inc/arc/arc_builtin.h"
#include "inc/arc/arc_exception.h"

/**
 * \name instruction cache control register related definition
 * \todo this definitions will be reviewed.
 * @{
 */
#define IC_CTRL_IC_ENABLE			0x0	/*!< enable instruction cache */
#define IC_CTRL_IC_DISABLE			0x1	/*!< disable instruction cache */
#define IC_CTRL_DIRECT_ACCESS			0x0	/*!< direct access mode */
#define IC_CTRL_INDIRECT_ACCESS			0x20	/*!< indirect access mode */
#define IC_CTRL_OP_SUCCEEDED			0x8	/*!< instruction cache operation succeeded */
/** @} */

/**
 * \name data cache control register related definition
 * \todo this definition will be reviewed.
 * @{
 */
#define IC_CTRL_I
#define DC_CTRL_DC_ENABLE			0x0	/*!< enable data cache */
#define DC_CTRL_DC_DISABLE			0x1	/*!< disable data cache */
#define DC_CTRL_INVALID_ONLY			0x0	/*!< invalid data cache only */
#define DC_CTRL_INVALID_FLUSH			0x40	/*!< invalid and flush data cache */
#define DC_CTRL_ENABLE_FLUSH_LOCKED		0x80	/*!< the locked data cache can be flushed */
#define DC_CTRL_DISABLE_FLUSH_LOCKED		0x0	/*!< the locked data cache cannot be flushed */
#define DC_CTRL_FLUSH_STATUS			0x100	/*!< flush status */
#define DC_CTRL_DIRECT_ACCESS			0x0	/*!< direct access mode  */
#define DC_CTRL_INDIRECT_ACCESS			0x20	/*!< indirect access mode */
#define DC_CTRL_OP_SUCCEEDED			0x4	/*!< data cache operation succeeded */
/** @} */

/**
 * \name instruction cache related inline function
 * @{
 */

/**
 * \brief  check whether instruction cache is available,
 * 0 for not available, >0 for available
 */
Inline uint8_t icache_available(void)
{
	return (_arc_aux_read(AUX_BCR_I_CACHE) & 0xF);
}

/**
 * \brief  enable instruction cache
 * \param[in] icache_en_mask operation mask
 */
Inline void icache_enable(uint32_t icache_en_mask)
{
	if (!icache_available()) return;
	_arc_aux_write(AUX_IC_CTRL, icache_en_mask);
}

/**
 * \brief  disable instruction cache
 */
Inline void icache_disable(void)
{
	if (!icache_available()) return;
	_arc_aux_write(AUX_IC_CTRL, IC_CTRL_IC_DISABLE);
}

/**
 * \brief  invalidate the entire instruction cache
 */
Inline void icache_invalidate(void)
{
	if (!icache_available()) return;
	/* invalidate the entire icache */
	_arc_aux_write(AUX_IC_IVIC, 0);
	Asm("nop_s");
	Asm("nop_s");
	Asm("nop_s");
}

/**
 * \brief  invalidate specific cache line
 * \param[in] address memory address
 */
Inline void icache_invalidate_line(uint32_t address)
{
	if (!icache_available()) return;
	_arc_aux_write(AUX_IC_IVIL, address);
	/* the 3 nops are required by ARCv2 ISA */
	Asm("nop_s");
	Asm("nop_s");
	Asm("nop_s");
}

/**
 * \brief  lock specific cache line
 * \param[in] address memory address
 * \return 0, succeeded, -1, failed
 */
Inline int32_t icache_lock_line(uint32_t address)
{
	if (!icache_available()) return -1;
	_arc_aux_write(AUX_IC_LIL, address);
	if(_arc_aux_read(AUX_IC_CTRL) & IC_CTRL_OP_SUCCEEDED) {
		return 0;
	} else {
		return -1;
	}
}

/**
 * \brief  set icache access mode
 * \param[in] mode, access mode, 1: indirect access 0:direct access
 */
Inline void icache_access_mode(uint32_t mode)
{
	if (!icache_available()) return;
	if (mode) {
		_arc_aux_write(AUX_IC_CTRL, _arc_aux_read(AUX_IC_CTRL) | IC_CTRL_INDIRECT_ACCESS);
	} else {
		_arc_aux_write(AUX_IC_CTRL, _arc_aux_read(AUX_IC_CTRL) & (~IC_CTRL_INDIRECT_ACCESS));
	}
}


/** @} */

/**
 * \name data cache related inline functions
 * @{
 */

/**
 * \brief  check whether data cache is available,
 * 0 for not available, >0 for available
 */
Inline uint8_t dcache_available(void)
{
	return (_arc_aux_read(AUX_BCR_D_CACHE) & 0xF);
}

/**
 * \brief 	invalidate the entire data cache
 */
Inline void dcache_invalidate(void)
{
	if (!dcache_available()) return;
	uint32_t status;

	status = cpu_lock_save();
	_arc_aux_write(AUX_DC_IVDC, 1);
	/* wait for flush completion */
	while (_arc_aux_read(AUX_DC_CTRL) & DC_CTRL_FLUSH_STATUS);
	cpu_unlock_restore(status);
}

/**
 * \brief invalidate the specific cache line
 * \param[in] address memory address
 */
Inline void dcache_invalidate_line(uint32_t address)
{
	if (!dcache_available()) return;
	_arc_aux_write(AUX_DC_IVDL, address);
	Asm("nop_s");
	Asm("nop_s");
	Asm("nop_s");
}

/**
 * \brief enable data cache
 * \param[in] dcache_en_mask operation mask
 */
Inline void dcache_enable(uint32_t dcache_en_mask)
{
	if (!dcache_available()) return;
	_arc_aux_write(AUX_DC_CTRL, dcache_en_mask);
}

/**
 * \brief disable data cache
 */
Inline void dcache_disable(void)
{
	if (!dcache_available()) return;
	_arc_aux_write(AUX_DC_CTRL, DC_CTRL_DC_DISABLE);
}

/**
 * \brief flush data cache
 */
Inline void dcache_flush(void)
{
	if (!dcache_available()) return;
	uint32_t status;

	status = cpu_lock_save();
	_arc_aux_write(AUX_DC_FLSH, 1);
	/* wait for flush completion */
	while (_arc_aux_read(AUX_DC_CTRL) & DC_CTRL_FLUSH_STATUS);
	cpu_unlock_restore(status);
}

/**
 * \brief  flush the specific data cache line
 * \param[in] address memory address
 */
Inline void dcache_flush_line(uint32_t address)
{
	if (!dcache_available()) return;

	uint32_t status;

	status = cpu_lock_save();
	_arc_aux_write(AUX_DC_FLDL, address);
	while (_arc_aux_read(AUX_DC_CTRL) & DC_CTRL_FLUSH_STATUS);
	cpu_unlock_restore(status);
}

/**
 * \brief  lock the specific data cache line
 * \param[in] address memory address
 * \return 0, succeeded, -1, failed
 */
Inline int dcache_lock_line(uint32_t address)
{
	if (!dcache_available()) return -1;
	_arc_aux_write(AUX_DC_LDL, address);
	if(_arc_aux_read(AUX_DC_CTRL) & DC_CTRL_OP_SUCCEEDED) {
		return 0;
	} else {
		return -1;
	}
}

/**
 * \brief  set dcache access mode
 * \param[in] mode, access mode, 1: indirect access 0:direct access
 */
Inline void dcache_access_mode(uint32_t mode)
{
	if (!dcache_available()) return;
	if (mode) {
		_arc_aux_write(AUX_DC_CTRL, _arc_aux_read(AUX_DC_CTRL) | DC_CTRL_INDIRECT_ACCESS);
	} else {
		_arc_aux_write(AUX_DC_CTRL, _arc_aux_read(AUX_DC_CTRL) & (~DC_CTRL_INDIRECT_ACCESS));
	}
}

/** @} */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name declarations of cache related functions
 * @{
 */
extern int32_t icache_invalidate_mlines(uint32_t start_addr, uint32_t size);
extern int32_t icache_lock_mlines(uint32_t start_addr, uint32_t size);
extern int32_t icache_direct_write(uint32_t cache_addr, uint32_t tag, uint32_t data);
extern int32_t icache_direct_read(uint32_t cache_addr, uint32_t *tag, uint32_t *data);
extern int32_t icache_indirect_read(uint32_t mem_addr, uint32_t *tag, uint32_t *data);
extern int32_t dcache_invalidate_mlines(uint32_t start_addr, uint32_t size);
extern int32_t dcache_flush_mlines(uint32_t start_addr, uint32_t size);
extern int32_t dcache_lock_mlines(uint32_t start_addr, uint32_t size);
extern int32_t dcache_direct_write(uint32_t cache_addr, uint32_t tag, uint32_t data);
extern int32_t dcache_direct_read(uint32_t cache_addr, uint32_t *tag, uint32_t *data);
extern int32_t dcache_indirect_read(uint32_t mem_addr, uint32_t *tag, uint32_t *data);
extern void arc_cache_init(void);

#ifdef __cplusplus
}
#endif

/** @} */
#endif	/* _ARC_HAL_CACHE_H_ */
