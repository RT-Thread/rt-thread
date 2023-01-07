/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

//FIXME no BL808/BL606p header file including is Allowed here
#ifdef BL808
#include <bl808.h>
#include <bl808_dma.h>
#include <bl808_adc.h>
#include <bl808_glb.h>
#elif defined(BL606P)
#include <bl606p.h>
#include <bl606p_dma.h>
#include <bl606p_adc.h>
#include <bl606p_glb.h>
#else
#error "Use CHIP BL808/BL606P for this module"
#endif

#include <bl_irq.h>
#include <blog.h>
#include <hosal_dma.h>
#include <hosal_adc.h>

#define ADC_CLOCK_FREQ    40000000
#define ADC_GPIO_NUM        12
#define ADC_CHANNEL_MAX     12

typedef struct adc_ctx {
    uint32_t *channel_data;
    void *adc_lli;
    void *llibuf;
    int lli_flag;
    uint32_t chan_init_table;
    uint32_t data_size;
}hosal_adc_ctx_t;

static hosal_adc_dev_t *pgdevice;

void adc_data_update (void *p_arg, uint32_t flag)
{
    hosal_adc_dev_t *adc = (hosal_adc_dev_t *)p_arg;
    hosal_adc_ctx_t *pstctx = (hosal_adc_ctx_t *)adc->priv;

    if (pstctx->lli_flag == 0) {
        pstctx->channel_data = (uint32_t *)((DMA_LLI_Ctrl_Type *)(pstctx->adc_lli))[0].destDmaAddr;
        pstctx->lli_flag = 1;
    } else {
        pstctx->channel_data = (uint32_t *)((DMA_LLI_Ctrl_Type *)(pstctx->adc_lli))[1].destDmaAddr;
        pstctx->lli_flag = 0;
    }
}

static int adc_check_gpio_valid(GLB_GPIO_Type pin)
{
    int i;

    GLB_GPIO_Type gpio_arr[ADC_GPIO_NUM] =
    {
        GLB_GPIO_PIN_4, GLB_GPIO_PIN_5, GLB_GPIO_PIN_6,
        GLB_GPIO_PIN_11, GLB_GPIO_PIN_12, GLB_GPIO_PIN_13,
        GLB_GPIO_PIN_16, GLB_GPIO_PIN_17, GLB_GPIO_PIN_18,
        GLB_GPIO_PIN_19, GLB_GPIO_PIN_34, GLB_GPIO_PIN_40
    };

    for (i = 0; i < ADC_GPIO_NUM; i++) {
        if (pin == gpio_arr[i]) {
            return 0;
        }
    }

    blog_error("gpio %d can not used as adc\r\n", pin);

    return -1;
}

static int adc_get_channel_by_gpio(GLB_GPIO_Type pin)
{
    int channel = -1;

    switch (pin) {
        case GLB_GPIO_PIN_4:
            channel = 2;
            break;
        case GLB_GPIO_PIN_5:
            channel = 1;
            break;
        case GLB_GPIO_PIN_6:
            channel = 4;
            break;
        case GLB_GPIO_PIN_11:
            channel = 3;
            break;
        case GLB_GPIO_PIN_12:
            channel = 6;
            break;
        case GLB_GPIO_PIN_13:
            channel = 7;
            break;
        case GLB_GPIO_PIN_16:
            channel = 8;
            break;
        case GLB_GPIO_PIN_17:
            channel = 0;
            break;
        case GLB_GPIO_PIN_18:
            channel = 9;
            break;
        case GLB_GPIO_PIN_19:
            channel = 10;
            break;
        case GLB_GPIO_PIN_34:
            channel = 11;
            break;
        case GLB_GPIO_PIN_40:
            channel = 5;
            break;
        
        default :
            channel = -1;
            break;
    }

    return channel;
}

static void adc_freq_init(hosal_adc_sample_mode_t mode, uint32_t freq)
{
    uint32_t div;
    uint32_t source_freq;
    uint32_t mode_freq;

    if (mode == HOSAL_ADC_ONE_SHOT) {
        mode_freq = ADC_CHANNEL_MAX;
    } else {
        mode_freq = 1;
    }

    source_freq = ADC_CLOCK_FREQ / (128 * 24 * mode_freq);

    div = source_freq / freq;
    if (((div + 1) * freq - source_freq) < (source_freq - freq * div)) {
        div = div + 1;
    }

    if (div > 64) {
        div = 64; 
    }

    /*adc clk can not more than 2M*/
    /*when adc work at scan mode, adc clk can not more than 1M*/
    blog_info("ADC freq: %ldHz. ,div:%lu\r\n", (int)(source_freq / div), div);

    /* set clk */
    GLB_PER_Clock_UnGate(GLB_AHB_CLOCK_GPIP | GLB_AHB_CLOCK_DMA_0);
    GLB_Set_ADC_CLK(ENABLE, GLB_ADC_CLK_XCLK, div-1);
}

static void adc_dma_lli_init(DMA_LLI_Ctrl_Type *pstlli, uint32_t *buf, uint32_t data_num)
{
    struct DMA_Control_Reg dma_ctrl_reg={
        .TransferSize=0,
        .SBSize=DMA_BURST_SIZE_1,
        .dst_min_mode=DISABLE,
        .DBSize=DMA_BURST_SIZE_1,
        .dst_add_mode=DISABLE,
        .SWidth=DMA_TRNS_WIDTH_32BITS,
        .DWidth=DMA_TRNS_WIDTH_32BITS,
        .fix_cnt=0,
        .SI=DMA_MINC_DISABLE,
        .DI=DMA_MINC_ENABLE,
        .I=1,
    };
    dma_ctrl_reg.TransferSize = data_num;

    pstlli[0].srcDmaAddr = GPIP_BASE+GPIP_GPADC_DMA_RDATA_OFFSET;
    pstlli[0].destDmaAddr = (uint32_t)&buf[0];
    pstlli[0].nextLLI = (uint32_t)&pstlli[1]; 
    pstlli[0].dmaCtrl= dma_ctrl_reg;

    pstlli[1].srcDmaAddr = GPIP_BASE+GPIP_GPADC_DMA_RDATA_OFFSET;
    pstlli[1].destDmaAddr = (uint32_t)&buf[ADC_CHANNEL_MAX];
    pstlli[1].nextLLI = (uint32_t)&pstlli[0];
    pstlli[1].dmaCtrl= dma_ctrl_reg;
}

static int adc_dma_init(hosal_adc_dev_t *adc, uint32_t data_num)
{
    DMA_LLI_Ctrl_Type *pstlli;
    uint32_t *llibuf;
    DMA_LLI_Cfg_Type llicfg = {
        .dir = DMA_TRNS_P2M,
        .srcPeriph = DMA_REQ_GPADC_RX,
        .dstPeriph = DMA_REQ_NONE,
    };
    
    hosal_adc_ctx_t *pstctx = (hosal_adc_ctx_t *)adc->priv;

    if (data_num < 1) {
        blog_error("illegal para. \r\n");
        return -1;
    }

    adc->dma_chan = hosal_dma_chan_request(0);

    pstlli = pvPortMalloc(sizeof(DMA_LLI_Ctrl_Type) * 2);
    if (NULL == pstlli) {
        blog_error("malloc lli failed. \r\n");
        return -1;
    }

    llibuf = pvPortMalloc(sizeof(uint32_t) * data_num * 2);
    if (NULL == llibuf) {
        blog_error("malloc lli buf failed. \r\n");
        return -1;
    }

    adc_dma_lli_init(pstlli, llibuf, data_num);
    DMA_LLI_Init(DMA0_ID, adc->dma_chan, &llicfg);
    DMA_LLI_Update(DMA0_ID, adc->dma_chan, (uint32_t)&(pstlli[0]));

    pstctx->llibuf = llibuf;
    pstctx->adc_lli = pstlli;
    pstctx->lli_flag = 0;
    pstctx->chan_init_table = 0;
    pstctx->channel_data = NULL;
    pstctx->data_size = data_num;

    hosal_dma_irq_callback_set(adc->dma_chan, adc_data_update, adc);

    return 0;
}

//mode = 0, for normal adc. freq 20HZ~1302HZ
static void adc_init(hosal_adc_dev_t *adc)
{
    int i, chan;
    uint8_t channel_table[ADC_CHANNEL_MAX] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    
    hosal_adc_sample_mode_t mode = adc->config.mode;
    GLB_GPIO_Type pin = adc->config.pin;

    ADC_CFG_Type adccfg;
    ADC_Chan_Type pos_chlist_single[ADC_CHANNEL_MAX];
    ADC_Chan_Type neg_chlist_single[ADC_CHANNEL_MAX];
    ADC_FIFO_Cfg_Type adc_fifo_cfg = {
        /*dma request will happend when fifo count up to fifoThreshold.*/
        .fifoThreshold = ADC_FIFO_THRESHOLD_1,
        .dmaEn = ENABLE,
    };

    adccfg.v18Sel=ADC_V18_SEL_1P82V;
    adccfg.v11Sel=ADC_V11_SEL_1P1V;
    adccfg.clkDiv=ADC_CLK_DIV_24;
    /* one shot mode */
    if (mode == HOSAL_ADC_ONE_SHOT) {
        adccfg.gain1=ADC_PGA_GAIN_NONE;
        adccfg.gain2=ADC_PGA_GAIN_NONE;
        adccfg.chopMode=ADC_CHOP_MOD_AZ_PGA_ON;
    } else {
        adccfg.gain1=ADC_PGA_GAIN_1;
        adccfg.gain2=ADC_PGA_GAIN_1;
        adccfg.chopMode=ADC_CHOP_MOD_AZ_PGA_ON;
    }
    adccfg.biasSel=ADC_BIAS_SEL_MAIN_BANDGAP;
    adccfg.vcm=ADC_PGA_VCM_1V;
    adccfg.vref=ADC_VREF_3P2V;
    adccfg.inputMode=ADC_INPUT_SINGLE_END;
    adccfg.resWidth = ADC_DATA_WIDTH_16_WITH_128_AVERAGE;
    adccfg.offsetCalibEn=0;
    adccfg.offsetCalibVal=0;

    ADC_Disable();
    ADC_Enable();
    ADC_Reset();

    ADC_Init(&adccfg);
 
    if (mode == HOSAL_ADC_ONE_SHOT) {
        for (i = 0; i < ADC_CHANNEL_MAX; i++) {
            pos_chlist_single[i] = channel_table[i];;
            neg_chlist_single[i] = ADC_CHAN_GND;
        }

        ADC_Scan_Channel_Config(pos_chlist_single, neg_chlist_single, ADC_CHANNEL_MAX, ENABLE);
    } 
    else {
        chan = adc_get_channel_by_gpio(pin);
        ADC_Channel_Config(chan, ADC_CHAN_GND, ENABLE);
        ADC_Mic_Init(NULL);
    }

    ADC_FIFO_Cfg(&adc_fifo_cfg);
}

static void adc_dma_start(hosal_dma_chan_t chan)
{
    ADC_Start();

    /* refresh cache */
    L1C_DCache_Clean_Invalid_All();
    hosal_dma_chan_start(chan);
}

static int adc_parse_data(uint32_t *parr, int data_size, int channel)
{
    int i;
    int32_t data;

    for (i = 0; i < data_size; i++) {
        if (parr[i] >> 21 == channel) {
            data = parr[i] & 0xFFFF;
            data = (data * 3200) >> 16;

            return data;
        }
    }   
    blog_error("error!\r\n");
    return -1;
}

int hosal_adc_init(hosal_adc_dev_t *adc)
{
    int res = -1;
    int freq;
    GLB_GPIO_Type pin;
    hosal_adc_ctx_t *pstctx;

    if (NULL == adc) {
        blog_error("parameter is error!\r\n");
        return -1;
    }

    freq = adc->config.sampling_freq;
    pin = (GLB_GPIO_Type)adc->config.pin;

    /* check adc pin*/
    res = adc_check_gpio_valid(pin);
    if (res) {
        blog_error("pin is error!\r\n");
        return -1;
    }
    
    pstctx = (hosal_adc_ctx_t *)pvPortMalloc(sizeof(hosal_adc_ctx_t));
    if (NULL == pstctx) {
        blog_error("not have enough memory!\r\n");
        return -1;
    }

    memset(pstctx, 0, sizeof(hosal_adc_ctx_t));
    adc->priv = pstctx;

    if (adc->config.mode == HOSAL_ADC_ONE_SHOT) {
        if (freq < 20 || freq > 1250) {
            blog_error("illegal freq. for mode0, freq 20HZ ~ 1250HZ \r\n");
            return -1;
        }
        /* init gpio */ 
        GLB_GPIO_Func_Init(GPIO_FUN_ANALOG, &pin, 1);

        /* init freq */
        adc_freq_init(adc->config.mode, freq);
        adc_init(adc);
        adc_dma_init(adc, ADC_CHANNEL_MAX);
        adc_dma_start(adc->dma_chan);
    } else {
        blog_error("not support continue mode!\r\n");
        return -1;
    }
    
    pgdevice = adc;

    return 0;
}

int hosal_adc_add_channel(hosal_adc_dev_t *adc, uint32_t channel)
{
    hosal_adc_ctx_t *pstctx = (hosal_adc_ctx_t *)adc->priv;

    if (NULL == adc) {
        blog_error("parameter is error!\r\n");
        return -1;
    }

    if (channel > 11) {
        blog_error("channel is error!");
        return -1;
    }
    pstctx->chan_init_table |= 1 << channel;

    return 0;
}

int hosal_adc_remove_channel(hosal_adc_dev_t *adc, uint32_t channel)
{
    hosal_adc_ctx_t *pstctx = (hosal_adc_ctx_t *)adc->priv;

    if (NULL == adc) {
        blog_error("parameter is error!\r\n");
        return -1;
    }

    if (channel > 11) {
        blog_error("channel is error!\r\n");
        return -1;
    }

    pstctx->chan_init_table &= ~(1 << channel);

    return 0;
}

hosal_adc_dev_t *hosal_adc_device_get(void)
{
    if (NULL == pgdevice) {
        blog_error("please init adc first!\r\n");
        return NULL;
    }

    return pgdevice;
}

int hosal_adc_value_get(hosal_adc_dev_t *adc, uint32_t channel, uint32_t timeout)
{
    int val = -1;
    hosal_adc_ctx_t *pstctx = (hosal_adc_ctx_t *)adc->priv;
 
    if (NULL == adc) {
        blog_error("parameter is error!\r\n");
        return -1;
    }
    
    if (channel > 11) {
        blog_error("channel is error!\r\n");
        return -1;
    }
    
    if (((1 << channel) & pstctx->chan_init_table) == 0) {
        blog_error("channel = %d  not init as adc \r\n", channel);
        return -1;
    }
    
    if (pstctx->channel_data == NULL) {
        blog_error("adc sampling not finish. \r\n");
        return -1;
    }

    /* refresh cache */
    L1C_DCache_Invalid_By_Addr(pstctx->channel_data, sizeof(uint32_t)*ADC_CHANNEL_MAX);
    while ((val = adc_parse_data(pstctx->channel_data, ADC_CHANNEL_MAX, channel)) == -1) {
        if (timeout-- == 0) {
            return -1;
        }
        vTaskDelay(1);
    }
    
    return val;
}

int hosal_adc_tsen_value_get(hosal_adc_dev_t *adc)
{
    blog_error("not support now!\r\n"); 
    return -1;
}

int hosal_adc_sample_cb_reg(hosal_adc_dev_t *adc, hosal_adc_cb_t cb)
{
    blog_error("not support now!\r\n");
    return -1;
}

int hosal_adc_start(hosal_adc_dev_t *adc, void *data, uint32_t size)
{
    blog_error("not support now!\r\n");
    return -1;
}

int hosal_adc_stop(hosal_adc_dev_t *adc)
{
    return 0; 
}

int hosal_adc_finalize(hosal_adc_dev_t *adc)
{
    hosal_adc_ctx_t *pstctx = (hosal_adc_ctx_t *)adc->priv;

    if (NULL == adc) {
        blog_error("parm error!\r\n");
        return -1;
    }

    vPortFree(pstctx->llibuf);
    vPortFree(pstctx->adc_lli);
    vPortFree(pstctx);
    ADC_Stop();
    hosal_dma_chan_stop(adc->dma_chan);
    hosal_dma_chan_release(adc->dma_chan);

    return 0;
}

