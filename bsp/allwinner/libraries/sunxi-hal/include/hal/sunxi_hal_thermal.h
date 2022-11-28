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

#ifndef SUXNI_HAL_THERMAL_H
#define SUXNI_HAL_THERMAL_H

#include "sunxi_hal_common.h"
#include <interrupt.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#if (defined(CONFIG_ARCH_SUN8IW20) || defined(CONFIG_SOC_SUN20IW1))
#define THS_BASE            0x02009400
#else
#define THS_BASE            0x05070400
#endif

#define THS_NUM             1

#define OFFSET              -2794
#define SCALE               -67

#define THS_CTL             (THS_BASE + 0x0)
#define THS_EN              (THS_BASE + 0x4)
#define THS_PCTL            (THS_BASE + 0x8)
#define THS_DICTL           (THS_BASE + 0x10)
#define THS_SICTL           (THS_BASE + 0x14)
#define THS_AICTL           (THS_BASE + 0x18)
#define THS_DIS             (THS_BASE + 0x20)
#define THS_SIS             (THS_BASE + 0x24)
#define THS_AOIS            (THS_BASE + 0x28)
#define THS_AIS             (THS_BASE + 0x2C)
#define THS_MFC             (THS_BASE + 0x30)
#define THS_ATC             (THS_BASE + 0x40)
#define THS_STC             (THS_BASE + 0x80)
#define THS_CALIB           (THS_BASE + 0xA0)
#define THS_DATA            (THS_BASE + 0xC0)

#define THS_CTRL_T_ACQ(x)           ((0xffff & (x)) << 16)
#define THS_FILTER_EN               0x4
#define THS_FILTER_TYPE(x)          (0x3 & (x))
#define THS_PC_TEMP_PERIOD(x)           ((0xfffff & (x)) << 12)
#define TEMP_CALIB_MASK             0xfff

#define FT_TEMP_MASK                0xfff
#define TEMP_TO_REG             672
#define CALIBRATE_DEFAULT           0x800

int hal_ths_init(void);
int hal_ths_uninit(void);
int hal_ths_get_temp(unsigned int num, int *temp);

#ifdef __cplusplus
}
#endif
#endif
