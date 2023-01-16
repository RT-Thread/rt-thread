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
#include "bl_audio.h"

#include "bl808.h"
#include "bl808_audio.h"
#include "bl808_glb.h"
#include "bl808_hbn.h"
#include "bl808_dma.h"
#include "bl_irq.h"
// #include <FreeRTOS.h>
// #include <portable.h>

static bl_audio_dev_t *gp_audio_dac_dev = NULL;

#define AUDIO_DMA_ID       DMA0_ID
#define AUDIO_TX_DMA_CHANNLE  DMA_CH0
#define AUDIO_RX_DMA_CHANNLE  DMA_CH1

static struct DMA_Control_Reg dmaCtrlRegVal={
    .TransferSize = 1000,
    .SBSize = DMA_BURST_SIZE_8,
    .DBSize = DMA_BURST_SIZE_8,
    .SWidth = DMA_TRNS_WIDTH_16BITS,
    .DWidth = DMA_TRNS_WIDTH_16BITS,
    .SI = DMA_MINC_ENABLE,
    .DI = DMA_MINC_DISABLE,
    .dst_min_mode = DISABLE,
    .dst_add_mode = DISABLE,
    .fix_cnt = 0,
    .I = 1,
};

static DMA_LLI_Cfg_Type lliCfg={
    DMA_TRNS_M2P,
    DMA_REQ_NONE,
    DMA_REQ_AUDIO_TX,
};

static int __hw_init(bl_audio_dev_t *p_dev)
{
    Audio_FifoCfg_Type audioFifoCfg;

    Audio_Clock_CFG_Type audioClockCfg = {
        AUDIO_ADC_16_KHZ,
        AUDIO_DAC_16_KHZ,
        DISABLE,
        DISABLE,
        DISABLE,
    };

    Audio_Volume_Cfg_Type audioVolumeCfg = {
        AUIDO_MUTE_DIRECTLY,
        AUIDO_RAMP_RATE_2_FS,
        AUIDO_RAMP_RATE_2_FS,
        AUIDO_VOLUME_UPDATE_FORCE,
        AUIDO_ZERO_CROSS_RATE_2_FS,
        AUIDO_RAMP_RATE_2_FS,
        AUIDO_ZERO_CROSS_RATE_2_FS,
    };

    GLB_Config_AUDIO_PLL(GLB_XTAL_40M, audioPllCfg_451P584M);
    /* ungate audio */
    GLB_PER_Clock_UnGate(GLB_AHB_CLOCK_AUDIO);

    /* enable dac clock*/
    GLB_Set_Audio_DAC_CLK(ENABLE, 19);
    /* enable adc clock*/
    GLB_Set_Audio_ADC_CLK(ENABLE, 19);

    Audio_Poweron();

    switch (p_dev->samplerate) {
        case AUDIO_8_KHZ:
            audioClockCfg.dac_clock = AUDIO_DAC_8_KHZ;
            printf("samplerate 8K\r\n");
            break;
        case AUDIO_16_KHZ:
            audioClockCfg.dac_clock = AUDIO_DAC_16_KHZ;
            printf("samplerate 16K\r\n");
            break;
        case AUDIO_24_KHZ:
            audioClockCfg.dac_clock = AUDIO_DAC_24_KHZ;
            printf("samplerate 24K\r\n");
            break;
        case AUDIO_32_KHZ:
            audioClockCfg.dac_clock = AUDIO_DAC_32_KHZ;
            printf("samplerate 32K\r\n");
            break;
        case AUDIO_48_KHZ:
            audioClockCfg.dac_clock = AUDIO_DAC_48_KHZ;
            printf("samplerate 48K\r\n");
            break;
        case AUDIO_96_KHZ:
            audioClockCfg.dac_clock = AUDIO_DAC_96_KHZ;
            printf("samplerate 96K\r\n");
            break;
        case AUDIO_192_KHZ:
            audioClockCfg.dac_clock = AUDIO_DAC_192_KHZ;
            printf("samplerate 192K\r\n");
            break;
        default:
            printf("samplerate NULL\r\n");
            break;
    }

    Audio_Clock_Init(&audioClockCfg);
    //set mute ramp
    Audio_DAC_Software_Volume_Config(AUDIO_DAC_0, &audioVolumeCfg);
    if (p_dev->rx_channel == STEREO_CHANNEL) {
        Audio_DAC_Software_Volume_Config(AUDIO_DAC_1, &audioVolumeCfg);
    }

    Audio_DAC_Set_Volume_Reg(ENABLE, 0, AUDIO_PLAY_DEFAULT_INITIAL_VOLUME);

    Audio_DAC_Enable(AUDIO_DAC_0);
    if (p_dev->rx_channel == STEREO_CHANNEL) {
        Audio_DAC_Enable(AUDIO_DAC_1);
    }

    Audio_DAC_Set_Mute(ENABLE, 0, AUDIO_UNMUTE);

    switch (p_dev->playBitWidth) {
        case AUDIO_BIT_WIDTH_16:
            audioFifoCfg.resolution = AUDIO_RES_16_BITS;
            audioFifoCfg.ailgnMode = AUDIO_FIFO_AILGN_MSB_AT_BIT15;
            printf("BitWidth 16\r\n");
            break;
        case AUDIO_BIT_WIDTH_24:
            audioFifoCfg.resolution = AUDIO_RES_20_BITS;
            audioFifoCfg.ailgnMode = AUDIO_FIFO_AILGN_MSB_AT_BIT23;
            printf("BitWidth 24\r\n");
            break;
        case AUDIO_BIT_WIDTH_32:
            audioFifoCfg.resolution = AUDIO_RES_20_BITS;
            audioFifoCfg.ailgnMode = AUDIO_FIFO_AILGN_MSB_AT_BIT31;
            printf("BitWidth 32\r\n");
            break;
        default:
            printf("BitWidth NULL\r\n");
            break;
    }
    audioFifoCfg.FifoIntThreshold = AUDIO_DEFAULT_TX_DRQ_THR;
    audioFifoCfg.dmaThresholdMode = AUDIO_DRQ_EQUEL_TO_IRQ;
    audioFifoCfg.dmaEn = ENABLE;

    Audio_TxFifoConfig(&audioFifoCfg);

    Audio_TxFifoDisable(p_dev->tx_channel);

    if (p_dev->rx_enable) {
        Audio_ADC_Software_Volume_Config(AUDIO_ADC_0, &audioVolumeCfg);
        if (p_dev->rx_channel == STEREO_CHANNEL) {
            Audio_ADC_Software_Volume_Config(AUDIO_ADC_1, &audioVolumeCfg);
        }

        Audio_ADC_Set_Volume_Reg(ENABLE, 0, AUDIO_PLAY_DEFAULT_INITIAL_VOLUME);

        Audio_ADC_Enable(AUDIO_ADC_0);
        if (p_dev->rx_channel == STEREO_CHANNEL) {
            Audio_ADC_Enable(AUDIO_ADC_1);
        }

        Audio_ADC_Set_Mute(ENABLE, 0, AUDIO_UNMUTE);

        audioFifoCfg.FifoIntThreshold = AUDIO_DEFAULT_RX_DRQ_THR;
        Audio_RxFifoConfig(&audioFifoCfg);
        Audio_RxFifoDisable(p_dev->rx_channel);
    }
    Auido_IntMask(AUDIO_INT_NUM_ALL, MASK);

    return 0;
}

static void __audio_lli_init(bl_audio_dev_t *p_dev)
{
    p_dev->lli_tx_buffer_size = p_dev->lli_tx_buffer_size / 2;

    switch (p_dev->playBitWidth) {
        case AUDIO_BIT_WIDTH_16:
            dmaCtrlRegVal.SWidth = DMA_TRNS_WIDTH_16BITS;
            dmaCtrlRegVal.DWidth = DMA_TRNS_WIDTH_16BITS;
            dmaCtrlRegVal.SBSize = DMA_BURST_SIZE_8;
            dmaCtrlRegVal.DBSize = DMA_BURST_SIZE_8;
            dmaCtrlRegVal.TransferSize = p_dev->lli_tx_buffer_size / 2;
            break;
        case AUDIO_BIT_WIDTH_24:
            dmaCtrlRegVal.SWidth = DMA_TRNS_WIDTH_32BITS;
            dmaCtrlRegVal.DWidth = DMA_TRNS_WIDTH_32BITS;
            dmaCtrlRegVal.SBSize = DMA_BURST_SIZE_4;
            dmaCtrlRegVal.DBSize = DMA_BURST_SIZE_4;
            dmaCtrlRegVal.TransferSize = p_dev->lli_tx_buffer_size / 4;
            break;
        case AUDIO_BIT_WIDTH_32:
            dmaCtrlRegVal.SWidth = DMA_TRNS_WIDTH_32BITS;
            dmaCtrlRegVal.DWidth = DMA_TRNS_WIDTH_32BITS;
            dmaCtrlRegVal.SBSize = DMA_BURST_SIZE_4;
            dmaCtrlRegVal.DBSize = DMA_BURST_SIZE_4;
            dmaCtrlRegVal.TransferSize = p_dev->lli_tx_buffer_size / 4;
            break;

        default:
            //private_bflb_platform_printf("BIT WIDTH Is Invaild\r\n");
            break;
    }

    p_dev->lli_tx_list[0].srcDmaAddr = (uint32_t)p_dev->lli_tx_buffer;
    p_dev->lli_tx_list[0].destDmaAddr = AUDIO_TX_FIFO_ADDR;
    p_dev->lli_tx_list[0].nextLLI = (uint32_t)&p_dev->lli_tx_list[1];
    p_dev->lli_tx_list[0].dmaCtrl= dmaCtrlRegVal;

    p_dev->lli_tx_list[1].srcDmaAddr = (uint32_t)p_dev->lli_tx_buffer + p_dev->lli_tx_buffer_size;
    p_dev->lli_tx_list[1].destDmaAddr = AUDIO_TX_FIFO_ADDR;
    p_dev->lli_tx_list[1].nextLLI=(uint32_t)&p_dev->lli_tx_list[0];
    p_dev->lli_tx_list[1].dmaCtrl= dmaCtrlRegVal;

    DMA_LLI_Init(AUDIO_DMA_ID, AUDIO_TX_DMA_CHANNLE, &lliCfg);
    DMA_LLI_Update(AUDIO_DMA_ID, AUDIO_TX_DMA_CHANNLE, (uint32_t)&gp_audio_dac_dev->lli_tx_list);

    if (p_dev->rx_enable) {
        p_dev->lli_rx_buffer_size = p_dev->lli_rx_buffer_size / 2;

        switch (p_dev->playBitWidth) {
            case AUDIO_BIT_WIDTH_16:
                dmaCtrlRegVal.SWidth = DMA_TRNS_WIDTH_16BITS;
                dmaCtrlRegVal.DWidth = DMA_TRNS_WIDTH_16BITS;
                dmaCtrlRegVal.SBSize = DMA_BURST_SIZE_8;
                dmaCtrlRegVal.DBSize = DMA_BURST_SIZE_8;
                dmaCtrlRegVal.TransferSize = p_dev->lli_rx_buffer_size / 2;
                break;
            case AUDIO_BIT_WIDTH_24:
                dmaCtrlRegVal.SWidth = DMA_TRNS_WIDTH_32BITS;
                dmaCtrlRegVal.DWidth = DMA_TRNS_WIDTH_32BITS;
                dmaCtrlRegVal.SBSize = DMA_BURST_SIZE_4;
                dmaCtrlRegVal.DBSize = DMA_BURST_SIZE_4;
                dmaCtrlRegVal.TransferSize = p_dev->lli_rx_buffer_size / 4;
                break;
            case AUDIO_BIT_WIDTH_32:
                dmaCtrlRegVal.SWidth = DMA_TRNS_WIDTH_32BITS;
                dmaCtrlRegVal.DWidth = DMA_TRNS_WIDTH_32BITS;
                dmaCtrlRegVal.SBSize = DMA_BURST_SIZE_4;
                dmaCtrlRegVal.DBSize = DMA_BURST_SIZE_4;
                dmaCtrlRegVal.TransferSize = p_dev->lli_rx_buffer_size / 4;
                break;

            default:
                //private_bflb_platform_printf("BIT WIDTH Is Invaild\r\n");
                break;
        }

        dmaCtrlRegVal.SI = DMA_MINC_DISABLE;
        dmaCtrlRegVal.DI = DMA_MINC_ENABLE;

        p_dev->lli_rx_list[0].srcDmaAddr = AUDIO_RX_FIFO_ADDR;
        p_dev->lli_rx_list[0].destDmaAddr = (uint32_t)p_dev->lli_rx_buffer;
        p_dev->lli_rx_list[0].nextLLI = (uint32_t)&p_dev->lli_rx_list[1];
        p_dev->lli_rx_list[0].dmaCtrl= dmaCtrlRegVal;

        p_dev->lli_rx_list[1].srcDmaAddr = AUDIO_RX_FIFO_ADDR;
        p_dev->lli_rx_list[1].destDmaAddr = (uint32_t)p_dev->lli_rx_buffer + p_dev->lli_rx_buffer_size;
        p_dev->lli_rx_list[1].nextLLI=(uint32_t)&p_dev->lli_rx_list[0];
        p_dev->lli_rx_list[1].dmaCtrl= dmaCtrlRegVal;

        lliCfg.dir = DMA_TRNS_P2M;
        lliCfg.srcPeriph = DMA_REQ_AUDIO_RX;
        lliCfg.dstPeriph = DMA_REQ_NONE;

        DMA_LLI_Init(AUDIO_DMA_ID, AUDIO_RX_DMA_CHANNLE, &lliCfg);
        DMA_LLI_Update(AUDIO_DMA_ID, AUDIO_RX_DMA_CHANNLE, (uint32_t)&gp_audio_dac_dev->lli_rx_list);
    }
}

static int __dma_int_clear(DMA_ID_Type dma_id, int ch)
{
    uint32_t tmpVal;
    uint32_t intClr;
    /* Get DMA register */

    const uint32_t dmaAddr[] = { DMA0_BASE, DMA1_BASE, DMA2_BASE };
    uint32_t DMAChs = dmaAddr[dma_id];

    tmpVal = BL_RD_REG(DMAChs, DMA_INTTCSTATUS);
    if((BL_GET_REG_BITS_VAL(tmpVal, DMA_INTTCSTATUS) & (1 << ch)) != 0) {
        /* Clear interrupt */
        tmpVal = BL_RD_REG(DMAChs, DMA_INTTCCLEAR);
        intClr = BL_GET_REG_BITS_VAL(tmpVal, DMA_INTTCCLEAR);
        intClr |= (1 << ch);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA_INTTCCLEAR, intClr);
        BL_WR_REG(DMAChs, DMA_INTTCCLEAR, tmpVal);
    }

    tmpVal = BL_RD_REG(DMAChs, DMA_INTERRORSTATUS);
    if((BL_GET_REG_BITS_VAL(tmpVal, DMA_INTERRORSTATUS) & (1 << ch)) != 0) {
        /*Clear interrupt */
        tmpVal = BL_RD_REG(DMAChs, DMA_INTERRCLR);
        intClr = BL_GET_REG_BITS_VAL(tmpVal, DMA_INTERRCLR);
        intClr |= (1 << ch);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA_INTERRCLR, intClr);
        BL_WR_REG(DMAChs, DMA_INTERRCLR, tmpVal);
    }

    return 0;
}

static void __dma_irq_handler(void)
{
    uint32_t tmpVal, count;
    int ret, size;
    tmpVal = BL_RD_REG(DMA0_BASE, DMA_INTTCSTATUS);
    if ((BL_GET_REG_BITS_VAL(tmpVal, DMA_INTTCSTATUS) & (1 << AUDIO_TX_DMA_CHANNLE)) != 0) {
        __dma_int_clear(AUDIO_DMA_ID, AUDIO_TX_DMA_CHANNLE); //clear int first

        if ( NULL == gp_audio_dac_dev) {
            return;
        }
        size = gp_audio_dac_dev->lli_tx_buffer_size;
        /*FIXME: set dma chain resonable option first 2 chain*/
        if (gp_audio_dac_dev->usr_cb) {
            /* software count may reliable*/
            //if (++gp_audio_dac_dev->pingpang >= 2) {
            //    gp_audio_dac_dev->pingpang = 0;
            //}

            count = ((*(volatile uint32_t *)0x2000c110) & (0x3FF << 20)) >> 20;
            if (0x01 == (count & 0x01)) {
                ret = gp_audio_dac_dev->usr_cb(gp_audio_dac_dev->p_usr_arg,
                                               gp_audio_dac_dev->lli_tx_buffer,
                                               size,
                                               gp_audio_dac_dev->is_underrun);
            } else {
                ret = gp_audio_dac_dev->usr_cb(gp_audio_dac_dev->p_usr_arg,
                                               gp_audio_dac_dev->lli_tx_buffer + size,
                                               size,
                                               gp_audio_dac_dev->is_underrun);
            }
            if (ret != 0) {
                gp_audio_dac_dev->is_underrun = 1;
            } else {
                gp_audio_dac_dev->is_underrun = 0;
            }
        }
    }

    if((BL_GET_REG_BITS_VAL(tmpVal, DMA_INTTCSTATUS) & (1 << AUDIO_RX_DMA_CHANNLE)) != 0) {
        __dma_int_clear(AUDIO_DMA_ID, AUDIO_RX_DMA_CHANNLE); //clear int first
        if ( NULL == gp_audio_dac_dev) {
            return;
        }
        size = gp_audio_dac_dev->lli_rx_buffer_size;
        if (gp_audio_dac_dev->usr_rx_cb) {
            count = ((*(volatile uint32_t *)0x2000c210) & (0x3FF << 20)) >> 20;
            /*FIXME: set dma multi chains*/
            if (0x01 == (count & 0x01)) {
                ret = gp_audio_dac_dev->usr_rx_cb(gp_audio_dac_dev->p_usr_rx_arg,
                                               gp_audio_dac_dev->lli_rx_buffer,
                                               size,
                                               gp_audio_dac_dev->is_overflow);
            } else {
                ret = gp_audio_dac_dev->usr_rx_cb(gp_audio_dac_dev->p_usr_rx_arg,
                                               gp_audio_dac_dev->lli_rx_buffer + size,
                                               size,
                                               gp_audio_dac_dev->is_overflow);
            }
            if (ret != 0) {
                gp_audio_dac_dev->is_overflow = 1;
            } else {
                gp_audio_dac_dev->is_overflow = 0;
            }
        }
    }
}

int bl_audio_samplerate_set (bl_audio_dev_t *p_dev, Audio_Samplerate_Type samplerate)
{
    p_dev->samplerate = samplerate;

    return 0;
}

int bl_audio_tx_ready_config(bl_audio_dev_t *p_dev,
                              audio_callback_tx_ready_t cb,
                              void *p_arg)
{
    if (NULL == p_dev) {
        printf("tx ready config fail dev is null\r\n");
        return -1;
    }
    p_dev->usr_cb = cb;
    p_dev->p_usr_arg = p_arg;
    return 0;
}

int bl_audio_rx_ready_config(bl_audio_dev_t *p_dev,
                              audio_callback_rx_ready_t cb,
                              void *p_arg)
{
    if (NULL == p_dev) {
        printf("rx ready config fail dev is null\r\n");
        return -1;
    }
    p_dev->usr_rx_cb = cb;
    p_dev->p_usr_rx_arg = p_arg;
    return 0;
}

int bl_audio_tx_buffer_config (bl_audio_dev_t *p_dev, void **ptr_mem, uint32_t bufsize)
{
    if (NULL == p_dev->lli_tx_buffer) {
        p_dev->lli_tx_buffer = pvPortMalloc(bufsize);
    }

    if (NULL == p_dev->lli_tx_buffer) {
        printf("malloc tx buffer fail\r\n");
        return -1;
    }

    memset(p_dev->lli_tx_buffer, 0, bufsize);
    csi_dcache_clean_range((void *)(p_dev->lli_tx_buffer), bufsize);
    *ptr_mem = p_dev->lli_tx_buffer;
    p_dev->lli_tx_buffer_size = bufsize;

    return 0;
}

int bl_audio_rx_buffer_config (bl_audio_dev_t *p_dev,
                                  void **ptr_mem,
                                  uint32_t bufsize)
{
    if (NULL == p_dev->lli_rx_buffer) {
        p_dev->lli_rx_buffer = pvPortMalloc(bufsize);
    }

    if (NULL == p_dev->lli_rx_buffer) {
        printf("malloc rx buffer fail\r\n");
        return -1;
    }

    memset(p_dev->lli_rx_buffer, 0, bufsize);
    csi_dcache_clean_range((void *)(p_dev->lli_rx_buffer), bufsize);
    *ptr_mem = p_dev->lli_rx_buffer;
    p_dev->lli_rx_buffer_size = bufsize;

    return 0;
}

int bl_audio_start (bl_audio_dev_t *p_dev)
{
    if (NULL == p_dev) {
        printf("audio start fail dev is NULL\r\n");
        return -1;
    }

    __hw_init(p_dev);

    GLB_Set_DMA_CLK(ENABLE, GLB_DMA0_CLK_CH0);
    GLB_PER_Clock_UnGate(GLB_AHB_CLOCK_DMA_0);

    DMA_Disable(AUDIO_DMA_ID);
    DMA_Channel_Disable(AUDIO_DMA_ID, AUDIO_TX_DMA_CHANNLE);
    DMA_Channel_Disable(AUDIO_DMA_ID, AUDIO_RX_DMA_CHANNLE);

    DMA_IntMask(AUDIO_DMA_ID, AUDIO_TX_DMA_CHANNLE, DMA_INT_ALL, MASK);
    DMA_IntMask(AUDIO_DMA_ID, AUDIO_TX_DMA_CHANNLE, DMA_INT_TCOMPLETED, UNMASK);
    DMA_IntMask(AUDIO_DMA_ID, AUDIO_RX_DMA_CHANNLE, DMA_INT_ALL, MASK);
    DMA_IntMask(AUDIO_DMA_ID, AUDIO_RX_DMA_CHANNLE, DMA_INT_TCOMPLETED, UNMASK);
    bl_irq_register(DMA0_ALL_IRQn, __dma_irq_handler);
    bl_irq_enable(DMA0_ALL_IRQn);

    __audio_lli_init(p_dev);

    csi_dcache_clean();
    DMA_Enable(AUDIO_DMA_ID);
    DMA_Channel_Enable(AUDIO_DMA_ID, AUDIO_TX_DMA_CHANNLE);

    Audio_TxFifoEnable(p_dev->tx_channel);

    if (p_dev->rx_enable) {
        DMA_Channel_Enable(AUDIO_DMA_ID, AUDIO_RX_DMA_CHANNLE);
        Audio_RxFifoEnable(p_dev->rx_channel);
    }
    return 0;
}

int bl_audio_stop (bl_audio_dev_t *p_dev)
{
    gp_audio_dac_dev->pingpang = 0;

    DMA_Disable(AUDIO_DMA_ID);
    DMA_Channel_Disable(AUDIO_DMA_ID, AUDIO_TX_DMA_CHANNLE);
    if (p_dev->rx_enable) {
        DMA_Channel_Disable(AUDIO_DMA_ID, AUDIO_RX_DMA_CHANNLE);
    }
    bl_irq_disable(DMA0_ALL_IRQn);

    return 0;
}

int bl_audio_init (bl_audio_dev_t *p_dev)
{
    if (NULL == p_dev) {
        printf("init audio fail dev is null\r\n");
        return -1;
    }
    memset(p_dev, 0, sizeof(bl_audio_dev_t));
    gp_audio_dac_dev = p_dev;

    return 0;
}

int bl_audio_deinit (bl_audio_dev_t *p_dev)
{
    vPortFree(p_dev->lli_tx_buffer);
    p_dev->lli_tx_buffer =  NULL;

    vPortFree(p_dev->lli_rx_buffer);
    p_dev->lli_tx_buffer =  NULL;
    return 0;
}
