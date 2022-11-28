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

#include "common_ccmu.h"
//#include "platform_clk.h"
#include <hal_clk.h>

#define clk_driver_version "v_1_0_2"

typedef struct clk_base
{
    hal_clk_id_t clk;
    hal_clk_id_t parent;
    u32 clk_rate;
} clk_base_t, *clk_base_pt;

typedef struct clk_core
{
    hal_clk_id_t clk;
    hal_clk_type_t clk_type;
    hal_clk_id_t current_parent;
    hal_clk_type_t current_parent_type;
    u32 clk_rate;
    u32 parent_rate;
    hal_clk_status_t clk_enbale;
} clk_core_t, *clk_core_pt;

typedef struct clk_fix_factor
{
    clk_core_t clk_core;
    u32 clk_mult;
    u32 clk_div;
} clk_fixed_factor_t, *clk_fixed_factor_pt ;

typedef struct clk_factor
{
    clk_core_t clk_core;
    struct factor_init_data *factor_data ;
} clk_factor_t, *clk_factor_pt ;

typedef struct clk_periph
{
    clk_core_t clk_core;
    hal_clk_id_t *parent_arry;
    u32 parent_arry_size;
    struct sunxi_clk_periph *config;
} clk_periph_t, *clk_periph_pt ;

#define SETMASK(width, shift)   ((width?((-1U) >> (32-width)):0)  << (shift))
#define CLRMASK(width, shift)   (~(SETMASK(width, shift)))

#define SET_BITS(shift, width, reg, val)    \
    (((reg) & CLRMASK(width, shift)) | (val << (shift)))

#define GET_BITS(shift, width, reg)     \
    (((reg) & SETMASK(width, shift)) >> (shift))

#define CLK_LOCKBIT(x) x

#define do_div(n,base) ({                   \
        u32 __base = (base);                \
        u32 __rem;                      \
        __rem = ((u64)(n)) % __base;            \
        (n) = ((u64)(n)) / __base;              \
        if (__rem > __base / 2) \
            ++(n); \
        __rem;                          \
    })

/************************************************************************************************
* Macro definition SUNXI_CLK_FIXED_SRC
* @Description: This definition used to defining a Soc fixed-src-clk type clock structure variable and statically initialized
*************************************************************************************************/
#define SUNXI_CLK_FIXED_SRC(_name, _clk, _current_parent, _current_parent_type, _clk_rate, _parent_rate) \
    clk_core_t sunxi_clk_fixed_src_##_name  = { \
                                                .clk = _clk,    \
                                                .clk_type = HAL_CLK_FIXED_SRC,  \
                                                .current_parent = _current_parent,  \
                                                .current_parent_type = _current_parent_type, \
                                                .clk_rate = _clk_rate,      \
                                                .parent_rate = _parent_rate,    \
                                                .clk_enbale = HAL_CLK_STATUS_ENABLED,    \
                                              }

/************************************************************************************************
* Macro definition SUNXI_CLK_FIXED_FACTOR
* @Description: This definition used to defining a Soc fixed-factor-clk type clock structure variable and statically initialized
*************************************************************************************************/
#define SUNXI_CLK_FIXED_FACTOR(_name, _clk, _current_parent, _current_parent_type, _mult, _div) \
    clk_fixed_factor_t sunxi_clk_fixed_factor_##_name  = {   \
                                                             .clk_core = {   \
                                                                             .clk = _clk,    \
                                                                             .clk_type = HAL_CLK_FIXED_FACTOR,   \
                                                                             .current_parent = _current_parent,  \
                                                                             .current_parent_type = _current_parent_type, \
                                                                             .clk_rate = 0,     \
                                                                             .parent_rate = 0,      \
                                                                             .clk_enbale = HAL_CLK_STATUS_DISABLED,   \
                                                                         },  \
                                                             .clk_mult = _mult,  \
                                                             .clk_div = _div,    \
                                                         }

#define SUNXI_CLK_FACTOR_PERI1_MAX_FREQ (636000000U)

/************************************************************************************************
* @Function: clk_udelay
* @Description: implement for seting delay time
* @Parameters:
* # us: delay time of us unit
* @Return values:
* # void: No parameters returned
* @Attention: .etc
*************************************************************************************************/
void clk_udelay(u32 us);

/************************************************************************************************
* @Function: clk_get_core
* @Description: implement to find clock structure variable pointer of clock-id
* @Parameters:
* # clk: clock-id of soc specific clock
* @Return values:
* # NULL: input parameter of clock-id defined in hal but not defined by soc clock driver
* # others :  clk_core_pt structure variable pointer of clock-id
* @Attention: .etc
*************************************************************************************************/
clk_core_pt clk_get_core(hal_clk_id_t clk);


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

hal_clk_id_t clk_get(hal_clk_type_t type, hal_clk_id_t id);

hal_clk_status_t clk_put(hal_clk_id_t id);

/************************************************************************************************
* @Function: clk_get_rate
* @Description: implement for factor-clk, bus-clk and periph-clk get current rate cached witch may not current Runtime rate
* @Parameters:
* # clk: clock-id of soc specific clock
* @Return values:
* # HAL_CLK_STATUS_INVALID_PARAMETER: input parameter of clock-id undefined in hal ot rate value is invalid
* # 0 : input parameter of clock-id defined in hal but not defined by soc clock driver or clock disbaled
* # others: return rate cached successed
* @Attention: .etc
*************************************************************************************************/
hal_clk_status_t clk_get_rate(hal_clk_id_t clk, u32 *rate);


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
hal_clk_status_t clk_set_rate(hal_clk_id_t clk, u32 rate);


/************************************************************************************************
* @Function: clk_recalc_rate
* @Description: implement for factor-clk, bus-clk and periph-clk to recalculate current Runtime rate
* @Parameters:
* # clk: clock-id of soc specific clock
* @Return values:
* # HAL_CLK_STATUS_INVALID_PARAMETER: input parameter of clock-id undefined in hal
* # 0 : input parameter of clock-id defined in hal but not defined by soc clock driver or clock disbaled
* # others: return current clock rate successed
* @Attention: .etc
*************************************************************************************************/
hal_clk_status_t clk_recalc_rate(hal_clk_id_t clk, u32 *prate);


/************************************************************************************************
* @Function: clk_round_rate
* @Description: implement for for factor-clk, bus-clk and periph-clk round target rate to the most suitable rate
* @Parameters:
* # clk: clock-id of soc specific clock
* # rate: the target rate form API-User
* @Return values:
* # HAL_CLK_STATUS_INVALID_PARAMETER: input parameter of clock-id undefined in hal ot rate value is invalid
* # 0 : input parameter of clock-id defined in hal but not defined by soc clock driver or clock disbaled
* # others: return round rate successed
* @Attention: .etc
*************************************************************************************************/
hal_clk_status_t clk_round_rate(hal_clk_id_t clk, u32 rate, u32 *prate);


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
hal_clk_status_t clk_is_enabled(hal_clk_id_t clk);


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
hal_clk_status_t clk_prepare_enable(hal_clk_id_t clk);


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
hal_clk_status_t clk_disable_unprepare(hal_clk_id_t clk);


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
hal_clk_id_t clk_get_parent(hal_clk_id_t clk);


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
hal_clk_status_t clk_set_parent(hal_clk_id_t clk, hal_clk_id_t parent_clk);


#endif /* __HAL_CLOCK_H__ */

