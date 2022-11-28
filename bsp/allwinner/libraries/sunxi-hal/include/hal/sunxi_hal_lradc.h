/* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.

 * Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
 * the the People's Republic of China and other countries.
 * All Allwinner Technology Co.,Ltd. trademarks are used with permission.

 * DISCLAIMER
 * THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
 * IF YOU NEED TO INTEGRATE THIRD PARTY’S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
 * IN ALLWINNERS’SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
 * ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
 * ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
 * COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
 * YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY’S TECHNOLOGY.


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

#ifndef __HAL_LRADC_H__
#define __HAL_LRADC_H__

#include <sunxi_hal_common.h>
#include <interrupt.h>
#include <hal_interrupt.h>
#include <lradc/platform_lradc.h>
#include <lradc/common_lradc.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*lradc_callback_t)(uint32_t irq_status, uint32_t data);

typedef struct {
    lradc_callback_t func;
    void *arg;
} lradc_func_data;

/*****************************************************************************
 * Enums
 *****************************************************************************/
typedef enum{
    HAL_ADC_STATUS_ERROR_PARAMETER = -3,
    HAL_ADC_STATUS_ERROR_CHANNEL = -2,
    HAL_ADC_STATUS_ERROR = -1,
    HAL_ADC_STATUS_OK = 0
} hal_lradc_status_t;

/*****************************************************************************
 * Functions
 *****************************************************************************/
hal_lradc_status_t hal_lradc_init(void);

hal_lradc_status_t hal_lradc_deinit(void);

hal_lradc_status_t hal_lradc_register_callback(lradc_callback_t callback);

#ifdef __cplusplus
}
#endif

#endif /*__HAL_LRADC_H__*/
