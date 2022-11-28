/* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
 *
 * Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
 *the the People's Republic of China and other countries.
 * All Allwinner Technology Co.,Ltd. trademarks are used with permission.
 *
 * DISCLAIMER
 * THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
 * IF YOU NEED TO INTEGRATE THIRD PARTY’S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
 * IN ALLWINNERS’SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
 * ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
 * ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
 * COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
 * YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY’S TECHNOLOGY.
 *
 *
 * THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
 * PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
 * THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
 * OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __SUNXI_HAL_CLK_H__
#define __SUNXI_HAL_CLK_H__


#include <stdio.h>
#include <string.h>
#include <sunxi_hal_common.h>
#include <common_ccmu.h>
#include <platform_ccmu.h>

#define hal_clk_api_version "hal_clk_api_version_1_1_0"

/************************************************************************************************
* Macro definition readl 、writel hal_read_xxx and hal_write_xxx
* @Description:  These definitions used to CCMU Drivers to read and write Physical I/O register
*************************************************************************************************/
#define hal_write_reg8(addr ,data)     ((*(volatile u8 *)(addr)) = (u8)(data))
#define hal_write_reg16(addr ,data)     ((*(volatile u16 *)(addr)) = (u16)(data))
#define hal_write_reg32(addr ,data)     ((*(volatile u32 *)(addr)) = (u32)(data))
#define hal_read_reg8(x)                (*(volatile u8 *)(x))
#define hal_read_reg16(x)                (*(volatile u16 *)(x))
#define hal_read_reg32(x)                (*(volatile u32 *)(x))

#undef readl
#undef writel
#define readl(x) hal_read_reg32(x)
#define writel(val, reg) hal_write_reg32(reg, val)
/************************************************************************************************
* Macro definition CCMU_XXX
* @Description: These definitions used to CCMU HAL-API and Drivers source code debug
*************************************************************************************************/
//#define CCMU_DBG_EN 1

#if defined(CCMU_DBG_LEAVE_TINY) || defined(CCMU_DBG_LEAVE_HIGH)
#define CCMU_DBG(fmt,args...)       printf("[CCMU:dbg..] %-*s:%d "fmt ,30, __func__, __LINE__, ##args)
#define CCMU_ERR(fmt,args...)       printf("[CCMU:err**] %-*s:%d "fmt ,30, __func__, __LINE__, ##args)
#else
#define CCMU_DBG(fmt,args...)   do{} while(0)
#define CCMU_ERR(fmt,args...)   do{} while(0)
#endif
#if defined(CCMU_DBG_LEAVE_HIGH)
#define CCMU_TRACE()                printf("[CCMU:trace] %-*s:%d \n",30, __func__, __LINE__)
#define CCMU_TRACE_CLK(tpye, clk)   printf("CCMU:trace %s:%d CLK "#tpye" id %d\n",__func__, __LINE__, clk)
#else
#define CCMU_TRACE()            do{} while(0)
#define CCMU_TRACE_CLK(clk, rate)   do{} while(0)
#endif

/************************************************************************************************
* @Function: hal_clock_init
* @Description: provide HAL API for initialize soc clocks during the system power-on startup phase
* @Parameters:
* # void: No parameters required
* @Return values:
* # HAL_CLK_STATUS_OK: soc clocks initialize successed
* # others : soc clocks initialization may have some abnormal problems
* @Attention: clock initialize timing depands on specific soc platform clock design
*************************************************************************************************/
void hal_clock_init(void);

/************************************************************************************************
* @Function: hal_clock_init
* @Description: provide HAL API for initialize soc clocks during the system power-on startup phase
* @Parameters:
* # void: No parameters required
* @Return values:
* # HAL_CLK_STATUS_OK: soc clocks initialize successed
* # others : soc clocks initialization may have some abnormal problems
* @Attention: clock initialize timing depands on specific soc platform clock design
*************************************************************************************************/
hal_clk_t hal_clock_get(hal_clk_type_t type, hal_clk_id_t id);


hal_clk_status_t hal_clock_put(hal_clk_t clk);

/************************************************************************************************
* @Function: hal_clock_is_enabled
* @Description: provide HAL API for bus-clk and periph-clk to get clock enabled statue
* @Parameters:
* # clk: clock-id of soc specific clock
* @Return values:
* # HAL_CLK_STATUS_INVALID_PARAMETER: input parameter of clock-id undefined in hal ot rate value is invalid
* # HAL_CLK_STATUS_ERROR_CLK_SET_RATE_REFUSED: fixed-clk and factor clk not allowed User to change rate because of stability
* # HAL_CLK_STATUS_ERROT_CLK_UNDEFINED: input parameter of clock-id defined in hal but not defined by soc clock driver
* # HAL_CLK_STATUS_ERROR_CLK_NOT_FOUND: input parameter of clock-id defined in hal but not defined by soc clock driver
* # HAL_CLK_STATUS_ENABLED: clock current status is enabled
* # HAL_CLK_STATUS_DISABLED: clock current status is disabled
* @Attention: .etc
*************************************************************************************************/
hal_clk_status_t hal_clock_is_enabled(hal_clk_t clk);

/************************************************************************************************
* @Function: hal_clock_enable
* @Description: provide HAL API for bus-clk and periph-clk to enable clock
* @Parameters:
* # clk: clock-id of soc specific clock
* @Return values:
* # HAL_CLK_STATUS_INVALID_PARAMETER: input parameter of clock-id undefined in hal ot rate value is invalid
* # HAL_CLK_STATUS_ERROR_CLK_SET_RATE_REFUSED: fixed-clk and factor clk not allowed User to change rate because of stability
* # HAL_CLK_STATUS_ERROT_CLK_UNDEFINED: input parameter of clock-id defined in hal but not defined by soc clock driver
* # HAL_CLK_STATUS_ERROR_CLK_NOT_FOUND: input parameter of clock-id defined in hal but not defined by soc clock driver
* # HAL_CLK_STATUS_ENABLED: clock current status is enabled
* # HAL_CLK_STATUS_DISABLED: clock current status is disabled
* @Attention: .etc
*************************************************************************************************/
hal_clk_status_t hal_clock_enable(hal_clk_t clk);


/************************************************************************************************
* @Function: hal_clock_disable
* @Description: provide HAL API for bus-clk and periph-clk to disable clock
* @Parameters:
* # clk: clock-id of soc specific clock
* @Return values:
* # HAL_CLK_STATUS_INVALID_PARAMETER: input parameter of clock-id undefined in hal ot rate value is invalid
* # HAL_CLK_STATUS_ERROR_CLK_SET_RATE_REFUSED: fixed-clk and factor clk not allowed User to change rate because of stability
* # HAL_CLK_STATUS_ERROT_CLK_UNDEFINED: input parameter of clock-id defined in hal but not defined by soc clock driver
* # HAL_CLK_STATUS_ERROR_CLK_NOT_FOUND: input parameter of clock-id defined in hal but not defined by soc clock driver
* # HAL_CLK_STATUS_OK: clock current status disabled successed
* @Attention: .etc
*************************************************************************************************/
hal_clk_status_t hal_clock_disable(hal_clk_t clk);


/************************************************************************************************
* @Function: hal_clk_recalc_rate
* @Description: provide HAL API for factor-clk, bus-clk and periph-clk to recalculate current Runtime rate
* @Parameters:
* # clk: clock-id of soc specific clock
* @Return values:
* # HAL_CLK_STATUS_INVALID_PARAMETER: input parameter of clock-id undefined in hal
* # HAL_CLK_RATE_UNINITIALIZED : input parameter of clock-id defined in hal but not defined by soc clock driver or clock disbaled
* # others: return current clock rate successed
* @Attention: .etc
*************************************************************************************************/
u32 hal_clk_recalc_rate(hal_clk_t clk);


/************************************************************************************************
* @Function: hal_clk_round_rate
* @Description: provide HAL API for factor-clk, bus-clk and periph-clk round target rate to the most suitable rate
* @Parameters:
* # clk: clock-id of soc specific clock
* # rate: the target rate form API-User
* @Return values:
* # HAL_CLK_STATUS_INVALID_PARAMETER: input parameter of clock-id undefined in hal ot rate value is invalid
* # HAL_CLK_RATE_UNINITIALIZED : input parameter of clock-id defined in hal but not defined by soc clock driver or clock disbaled
* # others: return round rate successed
* @Attention: .etc
*************************************************************************************************/
u32 hal_clk_round_rate(hal_clk_t clk, u32 rate);


/************************************************************************************************
* @Function: hal_clk_get_rate
* @Description: provide HAL API for factor-clk, bus-clk and periph-clk get current rate cached witch may not current Runtime rate
* @Parameters:
* # clk: clock-id of soc specific clock
* @Return values:
* # HAL_CLK_STATUS_INVALID_PARAMETER: input parameter of clock-id undefined in hal ot rate value is invalid
* # HAL_CLK_RATE_UNINITIALIZED : input parameter of clock-id defined in hal but not defined by soc clock driver or clock disbaled
* # others: return rate cached successed
* @Attention: .etc
*************************************************************************************************/
u32  hal_clk_get_rate(hal_clk_t clk);


/************************************************************************************************
* @Function: hal_clk_set_rate
* @Description: provide HAL API for bus-clk and periph-clk to set new rate
* @Parameters:
* # clk: clock-id of soc specific clock
* # rate: the new rate value
* @Return values:
* # HAL_CLK_STATUS_INVALID_PARAMETER: input parameter of clock-id undefined in hal ot rate value is invalid
* # HAL_CLK_STATUS_ERROR_CLK_SET_RATE_REFUSED: fixed-clk and factor clk not allowed User to change rate because of stability
* # HAL_CLK_STATUS_ERROT_CLK_UNDEFINED: input parameter of clock-id defined in hal but not defined by soc clock driver
* # HAL_CLK_STATUS_ERROR_CLK_NOT_FOUND: input parameter of clock-id defined in hal but not defined by soc clock driver
* # HAL_CLK_STATUS_OK: set new rate successed
* @Attention: .etc
*************************************************************************************************/
hal_clk_status_t hal_clk_set_rate(hal_clk_t clk,  u32 rate);


/************************************************************************************************
* @Function: hal_clk_set_parent
* @Description: provide HAL API for factor-clk, bus-clk and periph-clk to select parent clock
* @Parameters:
* # clk: clock-id of soc specific clock witch nedds to adjust parent clock
* # parent: clock-id of soc specific clock's parent clock
* @Return values:
* # HAL_CLK_STATUS_OK: soc specific clock select and siwtch parent clock successed
* # others : soc specific clock select and siwtch parent clock may have some abnormal problems
* @Attention: soc specific clock and parent clock must be according to the SOC_User_Manual definition
*************************************************************************************************/
hal_clk_status_t hal_clk_set_parent(hal_clk_t clk, hal_clk_t parent);


/************************************************************************************************
* @Function: hal_clk_get_parent
* @Description: provide HAL API for factor-clk, bus-clk and periph-clk to get current parent clock
* @Parameters:
* # clk: clock-id of soc specific clock
* @Return values:
* # HAL_CLK_STATUS_INVALID_PARAMETER: input parameter of clock-id undefined in hal
* # HAL_CLK_UNINITIALIZED : input parameter of clock-id defined in hal but not defined by soc clock driver
* # others: return current parent clock-id successed
* @Attention: soc specific clock and parent clock must be according to the SOC_User_Manual definition
*************************************************************************************************/
hal_clk_t hal_clk_get_parent(hal_clk_t clk);


#endif /* __HAL_CLOCK_H__ */

