/*
* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
*
* Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
* the the People's Republic of China and other countries.
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

#ifndef __COMMON_CCMU_H__
#define __COMMON_CCMU_H__


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
* Enum hal_clk_status_t
* @Description: This enum defines the return status of Clock APIs. User should check the return value after calling the APIs
*************************************************************************************************/
typedef enum
{

    HAL_CLK_STATUS_DISABLED = -1,
    HAL_CLK_STATUS_ENABLED = 0,
    HAL_CLK_STATUS_ERROR_CLK_FACTOR_REFUSED = -11,
    HAL_CLK_STATUS_ERROR_CLK_NEED_DISABLED  = -10,
    HAL_CLK_STATUS_ERROR_CLK_PARENT_DISABLED  = -9,
    HAL_CLK_STATUS_ERROR_CLK_ENABLED_FAILED  = -8,
    HAL_CLK_STATUS_ERROR_CLK_ROUND_FAILED = -7,
    HAL_CLK_STATUS_ERROR_CLK_SET_RATE_REFUSED = -6,
    HAL_CLK_STATUS_ERROR_CLK_NOT_FOUND  = -5,
    HAL_CLK_STATUS_ERROT_CLK_UNDEFINED  = -4,
    HAL_CLK_STATUS_UNINITIALIZED = -3,        /**< Uninitialized clock driver. */
    HAL_CLK_STATUS_INVALID_PARAMETER = -2,    /**< Invalid parameter. */
    HAL_CLK_STATUS_ERROR = -1,                /**< Unknown error. */
    HAL_CLK_STATUS_OK = 0,                    /**< Successful. */
} hal_clk_status_t;

#if defined(CONFIG_DRIVERS_SUNXI_CLK)

#define HAL_SUNXI_CCU (0)
typedef unsigned int hal_clk_id_t;
typedef hal_clk_id_t hal_clk_t;

#include "sunxi/clk.h"

#endif

#if defined(CONFIG_DRIVERS_SUNXI_CCU)
/************************************************************************************************
* Enum hal_clk_type_t
* @Description: This enum defines the type of Clock
*************************************************************************************************/
typedef enum
{
    HAL_SUNXI_FIXED_CCU = 0,
    HAL_SUNXI_RTC_CCU,
    HAL_SUNXI_CCU,
    HAL_SUNXI_R_CCU,
    HAL_SUNXI_CCU_NUMBER,
} hal_clk_type_t;

typedef u32 hal_clk_id_t;

#include "sunxi-ng/clk.h"

typedef struct clk *hal_clk_t;
#endif

#endif /* __COMMON_CCMU_H__ */

