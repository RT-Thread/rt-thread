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

#ifndef __COMMON_TPADC_H__
#define __COMMON_TPADC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* SET_BITS */
#define SETMASK(width, shift)   ((width?((-1U) >> (32-width)):0)  << (shift))
#define CLRMASK(width, shift)   (~(SETMASK(width, shift)))
#define GET_BITS(shift, width, reg)     \
    (((reg) & SETMASK(width, shift)) >> (shift))
#define SET_BITS(shift, width, reg, val) \
    (((reg) & CLRMASK(width, shift)) | (val << (shift)))

#define TPADC_WIDTH     4095  /*12bit 0XFFF*/
#define TPADC_CLK_IN        (12000000)
#define DCXO24M         (24000000)

/* TPADC register offset */
#define TP_CTRL0        0x00
#define TP_CTRL1        0x04
#define TP_CTRL2        0x08
#define TP_CTRL3        0x0c
#define TP_INT_FIFOC    0x10
#define TP_INT_FIFOS    0x14
#define TP_TPR          0x18
#define TP_CDAT         0x1c
#define TP_DATA     0x24

/* tpadc regsiter offset and width */
#define FIFO_OVERRUN_PENDING    17
#define FIFO_OVERRUN_PENDIN_WIDTH 1

#define FIFO_DATA_PENDING   16
#define FIFO_DATA_PENDING_WIDTH 1

#define TP_FIFO_FLUSH   4
#define TP_FIFO_FLUSH_WIDTH 1

#define TACQ    0
#define TACQ_WIDTH  16

#define FS_DIV  16
#define FS_DIV_WIDTH    4

#define ADC_CLK_DIVIDER 20
#define ADC_CLK_DIVIDER_WIDTH   2

#define ADC_FIRST_DLY_MODE  23
#define ADC_FIRST_DLY_MODE_WIDTH    1

#define ADC_FIRST_DLY   24
#define ADC_FIRST_DLY_WIDTH 8

#define TP_MODE_SELECT  4
#define TP_MODE_SELECT_WIDTH    1

#define TP_EN   5
#define TP_EN_WIDTH 1

#define TP_DEBOUNCE 12
#define TP_DEBOUNCE_WIDTH   8

#define PRE_MEA 0
#define PRE_MEA_WIDTH   24

#define PRE_MEA_EN  24
#define PRE_MEA_EN_WIDTH    1

#define TP_FIFO_MODE    26
#define TP_FIFO_MODE_WIDTH  2

#define TP_SENSITIVE    28
#define TP_SENSITIVE_WIDTH  4

#define FILTER_TYPE 0
#define FILTER_TYPE_WIDTH   2

#define FILTER_EN   2
#define FILTER_EN_WIDTH 1

#define TP_DOWN_IRQ_EN  0
#define TP_DOWN_IRQ_ENWIDTH 1

#define TP_UP_IRQ_EN    1
#define TP_UP_IRQ_EN_WIDTH  1

#define TP_DATA_DRQ_EN  7
#define TP_DATA_DRQ_EN_WIDTH    1

#define TP_FIFO_TRIG 8
#define TP_FIFO_TRIG_WIDTH  5

#define TP_DATA_XY_CHANGE   13
#define TP_DATA_XY_CHANGE_WIDTH 1

#define TP_DATA_IRQ_EN  16
#define TP_DATA_IRQ_EN_WIDTH    1

#define TP_FIFO_OVERRUN_IRQ 17
#define TP_FIFO_OVERRUN_IRQ_WIDTH   1

#define TP_DATAPEND     (1<<16)
#define TP_UPPEND       (1<<1)
#define TP_DOWNPEND     (1<<0)

#define OSC_FREQUENCY       24000000
#define HOSC            1
#define TP_IO_INPUT_MODE    0xfffff

#define TP_CH3_SELECT       (1 << 3) /* channale 3 select enable,  0:disable, 1:enable */
#define TP_CH2_SELECT       (1 << 2) /* channale 2 select enable,  0:disable, 1:enable */
#define TP_CH1_SELECT       (1 << 1) /* channale 1 select enable,  0:disable, 1:enable */
#define TP_CH0_SELECT       (1 << 0) /* channale 0 select enable,  0:disable, 1:enable */

#ifdef __cplusplus
}
#endif

#endif /* __COMMON_TPADC_I_H__ */
