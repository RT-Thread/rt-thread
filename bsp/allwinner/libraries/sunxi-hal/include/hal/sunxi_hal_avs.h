/*
* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
*
* Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
* the the People's Republic of China and other countries.
* All Allwinner Technology Co.,Ltd. trademarks are used with permission.
*
* DISCLAIMER
* THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
* IF YOU NEED TO INTEGRATE THIRD PARTY¡¯S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
* IN ALLWINNERS¡¯SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
* ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
* ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
* COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
* YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY¡¯S TECHNOLOGY.
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

#ifndef SUNXI_HAL_AVS_H
#define SUNXI_HAL_AVS_H

#include "hal_interrupt.h"
#include "sunxi_hal_common.h"
#include <timer/platform_timer.h>
#include <interrupt.h>
#include <stdio.h>
#include <hal_osal.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CONFIG_DRIVERS_TMR_DEBUG

#ifdef CONFIG_DRIVERS_TMR_DEBUG
#define AVS_INFO(fmt, arg...) hal_log_info(fmt, ##arg)
#else
#define AVS_INFO(fmt, arg...) do {}while(0)
#endif

#define AVS_ERR(fmt, arg...) hal_log_err(fmt, ##arg)

#define AVS_CNT_CTRL_REG    (0x00C0)
#define AVS_CNT_REG(n)      (0x00C4 + 0x0004 * n)
#define AVS_CNT_DIV_REG     (0x00CC)
#define AVS_DIV_MASK        0xfff

typedef enum
{
    AVS_ENABLE = 0,
    AVS_DISABLE,
    AVS_PAUSE,
    AVS_CONTINUE,
    AVS_GET_COUNTER,
    AVS_SET_COUNTER,
    AVS_SET_DIV,
} hal_avs_cmd_t;

typedef enum
{
    AVS0 = 0,
    AVS1,
    AVS_NUM,
} hal_avs_id_t;

typedef struct
{
    hal_avs_id_t id;
    unsigned long base;
    hal_clk_t clk;
    u8 enable;
} hal_sunxi_avs;

int hal_avs_continue(hal_avs_id_t id);
int hal_avs_pause(hal_avs_id_t id);
int hal_avs_disable(hal_avs_id_t id);
int hal_avs_enable(hal_avs_id_t id);
int hal_avs_get_counter(hal_avs_id_t id, u32 *counter);
int hal_avs_set_counter(hal_avs_id_t id, u32 counter);
int hal_avs_set_cnt_div(hal_avs_id_t id, u32 div);
int hal_avs_init(hal_avs_id_t id);
int hal_avs_uninit(hal_avs_id_t id);
int hal_avs_control(hal_avs_id_t id, hal_avs_cmd_t cmd, void *arg);

#ifdef __cplusplus
}
#endif
#endif
