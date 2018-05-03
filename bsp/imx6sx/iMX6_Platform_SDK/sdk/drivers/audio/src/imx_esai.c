/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 * @file imx_esai.c
 * @brief Enhanced Serial Audio Interface(ESAI) driver.
 *
 * @ingroup diag_audio
 */

#include "sdk.h"
#include "audio/audio.h"
#include "imx_esai.h"
#include "imx_esai_priv.h"
#include "registers/regsesai.h"
#include "profile/profile.h"

#define ESAI_DEBUG	1
#if ESAI_DEBUG
#define TRACE(fmt,args...) printf(fmt, ## args)
#else
#define TRACE(fmt,args...)
#endif

#define UNUSED_VARIABLE(x) (x) = (x)

extern void esai_clk_sel_gate_on(void);

////////////////////////////////////Local variables and functions/////////////////////////// 
/*!
 * Dump the esai registers which can be readable. 
 * @param  	ctrl	a pointer of audio controller(audio_ctrl_t) which presents the esai module itself
 *			
 * @return	0 if succeeded
 *		-1 if failed   
 */
static int32_t esai_dump(audio_ctrl_p ctrl)
{
    uint32_t instance = ctrl->instance;
    UNUSED_VARIABLE(instance);

    printf("=========%s DUMP=========\n", ctrl->name);
    printf("ECR:0x%08x\n", HW_ESAI_ECR_RD());
    printf("ESR:0x%08x\n", HW_ESAI_ESR_RD());
    printf("TFCR:0x%08x\n", HW_ESAI_TFCR_RD());
    printf("TFSR:0x%08x\n", HW_ESAI_TFSR_RD());
    printf("TCR:0x%08x\n", HW_ESAI_TCR_RD());
    printf("TCCR:0x%08x\n", HW_ESAI_TCCR_RD());
    printf("RCR:0x%08x\n", HW_ESAI_RCR_RD());
    printf("RCCR:0x%08x\n", HW_ESAI_RCCR_RD());
    printf("TSMA:0x%08x\n", HW_ESAI_TSMA_RD());
    printf("TSMB:0x%08x\n", HW_ESAI_TSMB_RD());

    return 0;
}

/*! 
 * Put the esai to soft-reset mode, and then can be configured.
 * @param       ctrl    a pointer of audio controller(audio_ctrl_t) which presents the esai module
 *
 * @return      0 if succeeded
 *              -1 if failed
 */
static int32_t esai_reset(audio_ctrl_p ctrl)
{
    uint32_t instance = ctrl->instance;
    uint32_t val;

    UNUSED_VARIABLE(instance);

    //First put ESAI in Reset state then enable it
    HW_ESAI_ECR_WR(BM_ESAI_ECR_ERST);
    HW_ESAI_ECR_WR(BM_ESAI_ECR_ESAIEN);

    //reset tx fifo
    val = HW_ESAI_TFCR_RD();
    val |= BM_ESAI_TFCR_TFR;
    HW_ESAI_TFCR_WR(val);
    val &= ~BM_ESAI_TFCR_TFR;
    HW_ESAI_TFCR_WR(val);

    //reset rx fifo
    val = HW_ESAI_RFCR_RD();
    val |= BM_ESAI_RFCR_RFR;
    HW_ESAI_RFCR_WR(val);
    val &= ~BM_ESAI_RFCR_RFR;
    HW_ESAI_RFCR_WR(val);

    //put tx to personal reset state
    val = HW_ESAI_TCR_RD();
    val |= BM_ESAI_TCR_TPR;
    HW_ESAI_TCR_WR(val);

    //put rx to personal reset state
    val = HW_ESAI_RCR_RD();
    val |= BM_ESAI_RCR_RPR;
    HW_ESAI_RCR_WR(val);

    return 0;
}

/*!
 * Set parameters of esai
 * @param       ctrl    a pointer of audio controller(audio_ctrl_t) which presents the esai module
 * @param       type    the parameter type want to set, refer esai_hw_para_type_e for details.
 * @param       val     the parameter value to be set.
 *
 * @return      0 if succeeded
 *              -1 if failed
 */
static int32_t esai_set_hw_para(audio_ctrl_p ctrl, uint32_t type, uint32_t val)
{
    uint32_t instance = ctrl->instance;

    UNUSED_VARIABLE(instance);

    switch (type) {
    case ESAI_HW_PARA_ECR:
        HW_ESAI_ECR_WR(val);;
        break;
    case ESAI_HW_PARA_TCR:
        HW_ESAI_TCR_WR(val);;
        break;
    case ESAI_HW_PARA_RCR:
        HW_ESAI_RCR_WR(val);;
        break;
    case ESAI_HW_PARA_TCCR:
        HW_ESAI_TCCR_WR(val);;
        break;
    case ESAI_HW_PARA_RCCR:
        HW_ESAI_RCCR_WR(val);;
        break;
    case ESAI_HW_PARA_TFCR:
        HW_ESAI_TFCR_WR(val);;
        break;
    case ESAI_HW_PARA_RFCR:
        HW_ESAI_RFCR_WR(val);;
        break;
    case ESAI_HW_PARA_TSR:
        HW_ESAI_TSR_WR(val);;
        break;
    case ESAI_HW_PARA_SAICR:
        HW_ESAI_SAICR_WR(val);;
        break;
    case ESAI_HW_PARA_TSM:
        HW_ESAI_TSMA_WR(val & 0xFFFF);
        HW_ESAI_TSMB_WR((val >> 16) & 0xFFFF);
        break;
    case ESAI_HW_PARA_RSM:
        HW_ESAI_RSMA_WR(val & 0xFFFF);
        HW_ESAI_RSMB_WR((val >> 16) & 0xFFFF);
        break;
    }

    return 0;
}

/*!
 * Get parameters of esai
 * @param       ctrl    a pointer of audio controller(audio_ctrl_t) which presents the esai module
 * @param       type    the parameter type want to get, refer esai_hw_para_type_e for details.
 *
 * @return      parameter valuw
 */
static uint32_t esai_get_hw_para(audio_ctrl_p ctrl, uint32_t type)
{
    uint32_t instance = ctrl->instance;
    uint32_t val;

    UNUSED_VARIABLE(instance);

    switch (type) {
    case ESAI_HW_PARA_ECR:
        val = HW_ESAI_ECR_RD();
        break;
    case ESAI_HW_PARA_TCR:
        val = HW_ESAI_TCR_RD();
        break;
    case ESAI_HW_PARA_RCR:
        val = HW_ESAI_RCR_RD();
        break;
    case ESAI_HW_PARA_TCCR:
        val = HW_ESAI_TCCR_RD();
        break;
    case ESAI_HW_PARA_RCCR:
        val = HW_ESAI_RCCR_RD();
        break;
    case ESAI_HW_PARA_TFCR:
        val = HW_ESAI_TFCR_RD();
        break;
    case ESAI_HW_PARA_RFCR:
        val = HW_ESAI_RFCR_RD();
        break;
    case ESAI_HW_PARA_SAICR:
        val = HW_ESAI_SAICR_RD();
        break;
    case ESAI_HW_PARA_TSM:
        val = ((HW_ESAI_TSMB_RD() << 16) & 0xFFFF0000) | (HW_ESAI_TSMA_RD() & 0xFFFF);
        break;
    case ESAI_HW_PARA_RSM:
        val = ((HW_ESAI_RSMB_RD() << 16) & 0xFFFF0000) | (HW_ESAI_RSMA_RD() & 0xFFFF);
        break;
    case ESAI_HW_PARA_TX_WL:
	val = BG_ESAI_TFCR_TWA(HW_ESAI_TFCR_RD());
        val = 32 - val * 4;
        break;
    case ESAI_HW_PARA_RX_WL:
	val = BG_ESAI_RFCR_RWA(HW_ESAI_RFCR_RD());
        val = 32 - val * 4;
        break;
    }

    return val;
}

/*!
 * Get status of esai
 * @param       ctrl    a pointer of audio controller(audio_ctrl_t) which presents the esai module
 * @param       type    the status type want to get, refer esai_status_e for details.
 *
 * @return      status value
 */
static uint32_t esai_get_status(audio_ctrl_p ctrl, uint32_t type)
{
    uint32_t instance = ctrl->instance;
    uint32_t val;

    UNUSED_VARIABLE(instance);

    switch (type) {
    case ESAI_STATUS_ESR:
        val = HW_ESAI_ESR_RD();;
        break;
    case ESAI_STATUS_TFSR:
        val = HW_ESAI_TFSR_RD();
        break;
    case ESAI_STATUS_RFSR:
        val = HW_ESAI_RFSR_RD();
        break;
    case ESAI_STATUS_SAISR:
        val = HW_ESAI_SAISR_RD();
        break;
    }

    return val;
}

/*!
 * Enable or disable sub-modules of ESAI.
 * @param       ctrl    a pointer of audio controller(audio_ctrl_t) which presents the esai module
 * @param       type    the sub-module to be set, please refer esai_sub_enable_type_e for details.
 * @param       val     the parameter value to be set.
 *
 * @return      0 if succeeded
 *              -1 if failed
 */
static int32_t esai_sub_enable(audio_ctrl_p ctrl, uint32_t type, uint32_t val)
{
    uint32_t instance = ctrl->instance;
    uint32_t v;

    UNUSED_VARIABLE(instance);

    switch (type) {
    case ESAI_SUB_ENABLE_TYPE_TX:
        v = HW_ESAI_TCR_RD();
        v &= ~(BM_ESAI_TCR_TE0 | BM_ESAI_TCR_TE1 | BM_ESAI_TCR_TE2 |
		BM_ESAI_TCR_TE3 | BM_ESAI_TCR_TE4 | BM_ESAI_TCR_TE5);
        v |= ESAI_TCR_TE(val);
        HW_ESAI_TCR_WR(v);
        break;
    case ESAI_SUB_ENABLE_TYPE_RX:
        v = HW_ESAI_RCR_RD();
        v &= ~ESAI_RCR_RE_MSK;
        v |= ESAI_RCR_RE(val);
        HW_ESAI_RCR_WR(v);
        break;
    }

    return 0;
}

/*!
 * Connect all ESAI pins, and this will make the ESAI out of personal reset state. 
 *
 * @param       ctrl    a pointer of audio controller(audio_ctrl_t) which presents the esai module
 * 
 * @return      0 if succeeded
 *              -1 if failed
 */
static int32_t esai_connect_pins(audio_ctrl_p ctrl)
{
    uint32_t instance = ctrl->instance;

    UNUSED_VARIABLE(instance);

    HW_ESAI_PCRC_WR(ESAI_GPIO_ESAI);
    HW_ESAI_PRRC_WR(ESAI_GPIO_ESAI);

    return 0;
}

/*!
 * Fill zeros to esai tx fifo to avoid noise data transfered.
 *
 * @param       ctrl    a pointer of audio controller(audio_ctrl_t) which presents the esai module
 * 
 * @return      0 if succeeded
 *              -1 if failed
 */
static int32_t esai_stuff_tx_fifo(audio_ctrl_p ctrl)
{
    uint32_t i;
    uint32_t instance = ctrl->instance;

    UNUSED_VARIABLE(instance);

    //stuff fifo
    for (i = 0; i < ESAI_TX_FIFO_SIZE; i++) {
        HW_ESAI_ETDR_WR(0);
    }

    return 0;
}

////////////////////////////// APIs /////////////////////////////////////

int32_t esai_config(void *priv, audio_dev_para_p para)
{
    uint32_t val;
    audio_ctrl_p ctrl = (audio_ctrl_p) priv;
    uint32_t instance = ctrl->instance;

    UNUSED_VARIABLE(instance);

    if (para->bus_protocol == AUDIO_BUS_PROTOCOL_AC97) {
        /*
         * Just for customer support purpose, since no mx6x reference board consists of AC97 codec
         *
         * For AC97:
         *  48KHz sample rate, so the frame sync freq should be 48KHz and the bit freq should be 48K*256 = 12.288 MHz. 
         *  13 slots;
         *  20bits per slot except slot0(16bit);
         *  word width: 20bit except slot0;
         *  FS : one word length and alligned with word
         */
        printf("Configure ESAI module as AC97 mode.\n");

    val = BM_ESAI_TCR_PADC |       //TX ZERO PADDING ,BIT17  1: pad 0, 0:repeat
            ESAI_TCR_TSWS_STL20_WDL20 | ESAI_TCR_TMOD_AC97;
        esai_set_hw_para(ctrl, ESAI_HW_PARA_TCR, val);

        val = BM_ESAI_TCCR_THCKD |  //HCKT is output (bit23=1)
            BM_ESAI_TCCR_TFSD | //FST is output (bit22=1) 
            BM_ESAI_TCCR_TCKD | //SCKT is output (bit21=1)
            BM_ESAI_TCCR_TCKP | //tX clock polarity bit 18, clock out on falling edge
            ESAI_TCCR_TDC(12);  //frame rate devider

        /*
         * Tx_Clk = 133/2/(5*1) = HCKT = 133/2/5 = 13.3MHz, not very accurate but enough for demo.
         */
        val |= ESAI_TCCR_TFP(0) | ESAI_TCCR_TPSR_BYPASS | ESAI_TCCR_TPM(4);
        esai_set_hw_para(ctrl, ESAI_HW_PARA_TCCR, val);

        esai_set_hw_para(ctrl, ESAI_HW_PARA_TSM, ESAI_TSM_NUM(13)); //13 tx slot unmask

        //reset tx fifo
        val = HW_ESAI_TFCR_RD();
        val |= BM_ESAI_TFCR_TFR;
        HW_ESAI_TFCR_WR(val);

        val = BM_ESAI_TFCR_TIEN | ESAI_TFCR_TFWM(ESAI_WATERMARK) | BM_ESAI_TFCR_TE0 |   //enable tx0 only.
            BM_ESAI_TFCR_TFE;
        if (WL_16 == para->word_length)
            val |= ESAI_WORD_LEN_16;
        else if (WL_20 == para->word_length)
            val |= ESAI_WORD_LEN_20;
        esai_set_hw_para(ctrl, ESAI_HW_PARA_TFCR, val);

        esai_stuff_tx_fifo(ctrl);

//        esai_sub_enable(ctrl, ESAI_SUB_ENABLE_TYPE_TX, 1);
    } else {
        val = BM_ESAI_TCR_PADC |    //TX ZERO PADDING ,BIT17  1: pad 0, 0:repeat
        ESAI_TCR_TSWS_STL32_WDL24 | //32bit slot len, 24bit word len
        ESAI_TCR_TMOD_NETWORK;  //network mode
    esai_set_hw_para(ctrl, ESAI_HW_PARA_TCR, val);

    /*
     * FixMe: CS42888 driver supports 48/44.1KHz only, although it was 
     * expected to support all sample rates.  When lower sample rate used,
     * no audio input.
     */
    if (AUDIO_BUS_MODE_MASTER == para->bus_mode) {
        val = BM_ESAI_TCCR_THCKD | //HCKT is output (bit23=1)
            BM_ESAI_TCCR_TFSD |    //FST is output (bit22=1) 
            BM_ESAI_TCCR_TCKD |    //SCKT is output (bit21=1)
            BM_ESAI_TCCR_TCKP |    //tX clock polarity bit 18, clock out on falling edge
            ESAI_TCCR_TDC(para->channel_number - 1);    //frame rate devider
        if (SAMPLERATE_44_1KHz == para->sample_rate) {
  	    /*
             * So the Tx_CLK = Fsys/2/((TPM+1) + (TFP+1)) = 133/2/(6*4) = 2.771MHz.
             * the HCKT = Fsys/2/((TPM+1) = 133/2/6 = 11.08MHz.
             * The Tx_CLK is not very accurate for 44.1K sample rate(2.822MHz).
             */
            val |= ESAI_TCCR_TFP(3) |   // clk div 4
                ESAI_TCCR_TPSR_BYPASS | //bypass
                ESAI_TCCR_TPM(5);
        } else if(SAMPLERATE_16KHz == para->sample_rate){
	    /*
	     * Tx_Clk = 133/2/(13*5) = 1.023MHz(1.024MHz expected), HCKT = 133/2/5 = 13.2MHz 
             */
            val |= ESAI_TCCR_TFP(12) |   // clk div 11
		ESAI_TCCR_TPSR_BYPASS | //bypass
		ESAI_TCCR_TPM(4);
        }else if(SAMPLERATE_32KHz == para->sample_rate){
	    /*
 	     * Tx_Clk = 133/2/(4*8) = 2.031MHz(32*2*32 = 2.048MHz was expected). HCKT = 133/2/4 = 16.625MHz
	     */
                val |= ESAI_TCCR_TFP(7) | ESAI_TCCR_TPSR_BYPASS | ESAI_TCCR_TPM(3);
	}else if(SAMPLERATE_48KHz == para->sample_rate){
            /*
             * Tx_Clk = 133/2/(5*4) = 3.3MHz(48*2*32 = 3.08MHz was expected). HCKT = 133/2/5 = 13.3MHz
             */
                val |= ESAI_TCCR_TFP(3) | ESAI_TCCR_TPSR_BYPASS | ESAI_TCCR_TPM(4);
	}
    } else {
        val = BM_ESAI_TCCR_TCKP | ESAI_TCCR_TDC(para->channel_number - 1); //frame rate devider
    }
    esai_set_hw_para(ctrl, ESAI_HW_PARA_TCCR, val);

    esai_set_hw_para(ctrl, ESAI_HW_PARA_TSM, ESAI_TSM_NUM(para->channel_number));

    val = HW_ESAI_TFCR_RD();
    val |= BM_ESAI_TFCR_TFR;
    HW_ESAI_TFCR_WR(val);

    val = BM_ESAI_TFCR_TIEN |
        ESAI_TFCR_TFWM(ESAI_WATERMARK) | ESAI_TFCR_TE(para->channel_number) | BM_ESAI_TFCR_TFE;
    if (WL_16 == para->word_length)
        val |= ESAI_WORD_LEN_16;
    else if (WL_24 == para->word_length)
        val |= ESAI_WORD_LEN_24;
    else if (WL_20 == para->word_length)
        val |= ESAI_WORD_LEN_20;
    esai_set_hw_para(ctrl, ESAI_HW_PARA_TFCR, val);

    esai_stuff_tx_fifo(ctrl);

    esai_sub_enable(ctrl, ESAI_SUB_ENABLE_TYPE_TX, para->channel_number);
    }

    esai_connect_pins(ctrl);

    esai_dump(ctrl);

    return 0;
}

int32_t esai_init(void *priv)
{
    audio_ctrl_p ctrl = (audio_ctrl_p) priv;

    esai_clk_sel_gate_on();

    esai_iomux_config();

    esai_reset(ctrl);

    return 0;
}

/*!
 * Close the ESAI module
 * @param       priv    a pointer passed by audio card driver, ESAI driver should change it
 *                      to a audio_ctrl_p pointer which presents the ESAI controller.
 *
 * @return      0 if succeeded
 *              -1 if failed
 */
int32_t esai_deinit(void *priv)
{
    //ESAI clk can be gate off here

    return 0;
}

int32_t esai_write_fifo(void *priv, uint8_t * buf, uint32_t size, uint32_t * bytes_written)
{
    audio_ctrl_p ctrl = (audio_ctrl_p) priv;
    uint32_t instance = ctrl->instance;
    uint32_t i = 0, j = 0;
    uint32_t wl = 0;
    uint32_t val = 0;

    UNUSED_VARIABLE(instance);
    UNUSED_VARIABLE(wl);

    wl = esai_get_hw_para(ctrl, ESAI_HW_PARA_TX_WL);

    HW_ESAI_TCR_WR(HW_ESAI_TCR_RD() | BM_ESAI_TCR_TE0);
    while (!(HW_ESAI_SAISR_RD() & BM_ESAI_SAISR_TUE)) ;
#ifdef ESAI_AC97_SUPPORT
    /*
     * A easy way to make sure AC97 frame alligned with the frame sync.
     */
    while (!(HW_ESAI_SAISR_RD() & BM_ESAI_SAISR_TFS)) ;
    for (i = 0; i < 12; i++) {
        HW_ESAI_ETDR_WR(0);
    }
#endif

    i = 0;
    while (i < size) {
        for (j = 0; (j < ESAI_WATERMARK) && (i < size); j++) {
        if (wl <= 8) {
            val = *((uint8_t *) (buf + i));
            i++;
        } else if (wl <= 16) {
            val = *((uint16_t *) (buf + i));
            i = i + 2;
        } else {
            val = *((uint32_t *) (buf + i));
            i = i + 4;
        }

        HW_ESAI_ETDR_WR(val);
    }

        while (!(HW_ESAI_ESR_RD() & BM_ESAI_ESR_TFE)) ;
    }
    *bytes_written = size;

    while (!(HW_ESAI_SAISR_RD() & BM_ESAI_SAISR_TUE)) ;
    HW_ESAI_TCR_WR(HW_ESAI_TCR_RD() & (~BM_ESAI_TCR_TE0));

    return 0;
}

static audio_dev_ops_t esai_ops = {
    .init = esai_init,
    .deinit = esai_deinit,
    .config = esai_config,
    .ioctl = NULL,
    .write = esai_write_fifo,
};

audio_ctrl_t imx_esai_1 = {
    .name = "imx ESAI audio controller 1",
    .instance = 1,
    .ops = &esai_ops,
};
