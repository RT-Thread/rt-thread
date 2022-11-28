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

#ifndef __CLK_H__
#define __CLK_H__

#include "ccu.h"
#include "../common_ccmu.h"

/************************************************************************************************
* @Function: clk_init
* @Description: implement for initialize soc clocks during the system power-on startup phase
* @Parameters:
* # void: No parameters required
* @Return values:
* # HAL_CLK_STATUS_OK: soc clocks initialize successed
* # others : soc clocks initialization may have some abnormal problems
* @Attention: clock initialize timing depands on specific soc platform clock design
*************************************************************************************************/

hal_clk_status_t clk_init(void);

struct clk *clk_get(hal_clk_type_t type, hal_clk_id_t id);

hal_clk_status_t clk_put(struct clk *clk);

/************************************************************************************************
* @Function: clk_get_rate
* @Description: implement for factor-clk, bus-clk and periph-clk get current rate cached witch may not current Runtime rate
* @Parameters:
* # clk: clock-id of soc specific clock
* @Return values:
* # HAL_CLK_STATUS_INVALID_PARAMETER: input parameter of clock-id undefined in hal ot rate value is invalid
* # HAL_CLK_RATE_UNINITIALIZED : input parameter of clock-id defined in hal but not defined by soc clock driver or clock disbaled
* # others: return rate cached successed
* @Attention: .etc
*************************************************************************************************/
hal_clk_status_t clk_get_rate(struct clk *clk, u32 *rate);

/************************************************************************************************
* @Function: clk_set_rate
* @Description: implement for bus-clk and periph-clk to set new rate
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
hal_clk_status_t clk_set_rate(struct clk *clk, u32 rate);


/************************************************************************************************
* @Function: clk_recalc_rate
* @Description: implement for factor-clk, bus-clk and periph-clk to recalculate current Runtime rate
* @Parameters:
* # clk: clock-id of soc specific clock
* @Return values:
* # HAL_CLK_STATUS_INVALID_PARAMETER: input parameter of clock-id undefined in hal
* # HAL_CLK_RATE_UNINITIALIZED : input parameter of clock-id defined in hal but not defined by soc clock driver or clock disbaled
* # others: return current clock rate successed
* @Attention: .etc
*************************************************************************************************/
hal_clk_status_t clk_recalc_rate(struct clk *clk, u32 *prate);


/************************************************************************************************
* @Function: clk_round_rate
* @Description: implement for for factor-clk, bus-clk and periph-clk round target rate to the most suitable rate
* @Parameters:
* # clk: clock-id of soc specific clock
* # rate: the target rate form API-User
* @Return values:
* # HAL_CLK_STATUS_INVALID_PARAMETER: input parameter of clock-id undefined in hal ot rate value is invalid
* # HAL_CLK_RATE_UNINITIALIZED : input parameter of clock-id defined in hal but not defined by soc clock driver or clock disbaled
* # others: return round rate successed
* @Attention: .etc
*************************************************************************************************/
hal_clk_status_t clk_round_rate(struct clk *clk, u32 rate, u32 *prate);

/************************************************************************************************
* @Function: clk_is_enabled
* @Description: implement for bus-clk and periph-clk to get clock enabled statue
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
hal_clk_status_t clk_is_enabled(struct clk *clk);


/************************************************************************************************
* @Function: clk_prepare_enable
* @Description: implement for bus-clk and periph-clk to enable clock
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
hal_clk_status_t clk_prepare_enable(struct clk *clk);

/************************************************************************************************
* @Function: clk_disable_unprepare
* @Description: implement for bus-clk and periph-clk to disable clock
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
hal_clk_status_t clk_disable_unprepare(struct clk *clk);

/************************************************************************************************
* @Function: clk_get_parent
* @Description: implement for factor-clk, bus-clk and periph-clk to select parent clock
* @Parameters:
* # clk: clock-id of soc specific clock witch nedds to adjust parent clock
* # parent: clock-id of soc specific clock's parent clock
* @Return values:
* # HAL_CLK_STATUS_OK: soc specific clock select and siwtch parent clock successed
* # others : soc specific clock select and siwtch parent clock may have some abnormal problems
* @Attention: soc specific clock and parent clock must be according to the SOC_User_Manual definition
*************************************************************************************************/
struct clk  *clk_get_parent(struct clk *clk);

/************************************************************************************************
* @Function: clk_set_parent
* @Description: implement for factor-clk, bus-clk and periph-clk to select parent clock
* @Parameters:
* # clk: clock-id of soc specific clock witch nedds to adjust parent clock
* # parent: clock-id of soc specific clock's parent clock
* @Return values:
* # HAL_CLK_STATUS_OK: soc specific clock select and siwtch parent clock successed
* # others : soc specific clock select and siwtch parent clock may have some abnormal problems
* @Attention: soc specific clock and parent clock must be according to the SOC_User_Manual definition
*************************************************************************************************/

hal_clk_status_t clk_set_parent(struct clk *clk, struct clk *p_clk);

#endif /* __HAL_CLOCK_H__ */

