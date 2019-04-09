/* ------------------------------------------
 * Copyright (c) 2017, Synopsys, Inc. All rights reserved.

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
 * \version 2017.03
 * \date 2014-07-01
 * \author Huaqi Fang(Huaqi.Fang@synopsys.com)
--------------------------------------------- */

/**
 * \file
 * \ingroup	DEVICE_DW_IIC
 * \brief	DesignWare IIC driver hardware description
 * 	related header file configuration file
 * \details	configuration file to enable or disable some function of iic
 */

#ifndef _DEVICE_DW_IIC_HAL_CFG_H_
#define _DEVICE_DW_IIC_HAL_CFG_H_

#ifndef DW_IIC_ALLOW_RESTART
#define DW_IIC_ALLOW_RESTART			(1)	/*!< allow restart configuration */
#endif

#ifdef DW_IIC_SPECIAL_START_BYTE
#define DW_IIC_SPECIAL_START_BYTE		(0)	/*!< SPECIAL bit enable in IC_TAR */
#endif

#ifndef DW_IIC_MST_10_BIT_ADDR_SUPPORT
#define DW_IIC_MST_10_BIT_ADDR_SUPPORT		(1)	/*!< enable 10-bit address mode */
#endif

#ifdef DW_IIC_SLV_10_BIT_ADDR_SUPPORT
#define DW_IIC_SLV_10_BIT_ADDR_SUPPORT		(1)	/*!< slave 10-bit addressing mode */
#endif

#ifndef DW_IIC_DYNAMIC_TAR_UPDATE_SUPPORT
#define DW_IIC_DYNAMIC_TAR_UPDATE_SUPPORT	(0)	/*!< Dynamic target address update support */
#endif

#ifndef DW_IIC_DISABLE_MAX_T_POLL_CNT
#define DW_IIC_DISABLE_MAX_T_POLL_CNT		(1250)	/*!< Timeout count, approximate to be 25us in 50MHz CPU @ Standard mode */
#endif

#ifndef DW_IIC_CALC_FIFO_LEN_ENABLE
#define DW_IIC_CALC_FIFO_LEN_ENABLE		(1)	/*!< Default enable calculate fifo length */
#endif

#ifndef DW_IIC_USE_IC_CLK_MHZ
#define DW_IIC_USE_IC_CLK_MHZ			(50)	/*!< Default use 50MHz IC_CLK */
#endif

#ifndef DW_IIC_USE_HS_BUS_LOADING_100PF
#define DW_IIC_USE_HS_BUS_LOADING_100PF		(1)	/*!< Use bus loading 100pf */
#endif

#endif /* _DEVICE_DW_IIC_HAL_CFG_H_ */

