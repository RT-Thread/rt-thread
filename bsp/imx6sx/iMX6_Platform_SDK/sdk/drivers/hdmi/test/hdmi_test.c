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
 * @file hdmi_test.c
 * @brief Unit test for the HDMI controller driver.
 *
 * @ingroup diag_hdmi
 */

#include "sdk.h"
#include "hdmi/src/hdmi_tx.h"
#include "registers/regshdmi.h"
#include "ipu/ipu_common.h"

extern int ips_hdmi_stream(void);
extern int ips_hdmi_1080P60_stream(int ipu_index);
extern int ips_hdmi_720P60_stream(int ipu_index);
//extern void init_data(unsigned int enc_in_format,int height, int width);
extern int init_dma_data(int sample_rate, int ch);
extern const unsigned char gAudio_sample[];
void init_hdmi_interrupt(void);
void hdmi_tx_ISR(void);

/*! ------------------------------------------------------------
 * HDMI TX Video Test (force output of FSL logo)
 *  ------------------------------------------------------------
 */
void hdmi_test(void)
{

    printf("\n---- Running HDMI_TX test ----\n");

    hdmi_data_info_s myHDMI_info = { 0 };   // declare new hdmi module object instance
    hdmi_vmode_s myHDMI_vmode_info = { 0 }; // declare new hdmi module object instance
    myHDMI_info.video_mode = &myHDMI_vmode_info;
    hdmi_audioparam_s myHDMI_audio_info = { 0 };    // declare new hdmi audio object instance

    myHDMI_info.enc_in_format = eRGB;
    myHDMI_info.enc_out_format = eRGB;
    myHDMI_info.enc_color_depth = 8;
    myHDMI_info.colorimetry = eITU601;
    myHDMI_info.pix_repet_factor = 0;
    myHDMI_info.hdcp_enable = 0;
//    myHDMI_info.video_mode->mCode = 4;  //1280x720p @ 59.94/60Hz 16:9
    myHDMI_info.video_mode->mCode = 16; //1920x1080p @ 59.94/60Hz 16:9
    myHDMI_info.video_mode->mHdmiDviSel = TRUE;
    myHDMI_info.video_mode->mRVBlankInOSC = FALSE;
    myHDMI_info.video_mode->mRefreshRate = 60000;
    myHDMI_info.video_mode->mDataEnablePolarity = TRUE;

    myHDMI_audio_info.IecCgmsA = 0;
    myHDMI_audio_info.IecCopyright = TRUE;
    myHDMI_audio_info.IecCategoryCode = 0;
    myHDMI_audio_info.IecPcmMode = 0;
    myHDMI_audio_info.IecSourceNumber = 1;
    myHDMI_audio_info.IecClockAccuracy = 0;
    myHDMI_audio_info.OriginalSamplingFrequency = 0;
    myHDMI_audio_info.ChannelAllocation = 0xf;
    myHDMI_audio_info.SamplingFrequency = 32000;
    myHDMI_audio_info.SampleSize = 16;

    hdmi_av_frame_composer(&myHDMI_info);
    hdmi_video_packetize(myHDMI_info);
    hdmi_video_csc(myHDMI_info);
    hdmi_video_sample(myHDMI_info);

    hdmi_audio_mute(TRUE);
    hdmi_tx_hdcp_config(myHDMI_info.video_mode->mDataEnablePolarity);

    hdmi_phy_init(TRUE, myHDMI_info.video_mode->mPixelClock);

    hdmi_config_input_source(IPU1_DI0); // configure input source to HDMI block

    // set-up Audio for test
    init_dma_data(32000, 4);
    //enable HDMI_TX interrupt for audio DMA
    register_interrupt_routine(IMX_INT_HDMI_TX, hdmi_tx_ISR);
    init_hdmi_interrupt();      //interrupt_init(0xff);
    enable_interrupt(IMX_INT_HDMI_TX, CPU_0, 0);    // to cpu0, max priority (0)

    audio_Configure(myHDMI_audio_info, 14850, 100); //audio_Configure(14850,100);
    HW_HDMI_IH_MUTE_AHBDMAAUD_STAT0.U = 0x00;
    audio_Configure_DMA(HDMI_AUDIO_BUF_START, (HDMI_AUDIO_BUF_START + 0x17ff), 1, 4, 64, 4, 0x7f);

    HW_HDMI_IH_MUTE.U = 0x2;

    // configure IPU to output stream for hdmi input
    if (ips_hdmi_stream()) {    // set up ipu1 disp0  1080P60 display stream 
        printf("HDMI video test PASS\n");
        printf("Audio will play for 2 more seconds\n");
        hal_delay_us(2000000);  // play hdmi audio for 3 seconds
        disable_interrupt(IMX_INT_HDMI_TX, CPU_0);
        printf("---- END of HDMI_TX test ----\n");
    } else {
        printf("HDMI video test FAIL\n");
        disable_interrupt(IMX_INT_HDMI_TX, CPU_0);
        printf("---- END of HDMI_TX test ----\n");
    }
}

void init_hdmi_interrupt(void)
{
    HW_HDMI_IH_MUTE_FC_STAT0.U = 0xFF;
    HW_HDMI_IH_MUTE_FC_STAT1.U = 0xFF;
    HW_HDMI_IH_MUTE_FC_STAT2.U = 0xFF;
    HW_HDMI_IH_MUTE_AS_STAT0.U = 0xFF;
    HW_HDMI_IH_MUTE_PHY_STAT0.U = 0xFF;
    HW_HDMI_IH_MUTE_I2CM_STAT0.U = 0xFF;
    HW_HDMI_IH_MUTE_CEC_STAT0.U = 0xFF;
    HW_HDMI_IH_MUTE_VP_STAT0.U = 0xFF;
    HW_HDMI_IH_MUTE_I2CMPHY_STAT0.U = 0xFF;
    HW_HDMI_IH_MUTE_AHBDMAAUD_STAT0.U = 0xFF;
}

void hdmi_tx_ISR(void)
{
    char status;

    status = HW_HDMI_IH_AHBDMAAUD_STAT0.U;
    init_hdmi_interrupt();

    HW_HDMI_IH_MUTE_AHBDMAAUD_STAT0.U = 0x00;

    if (status & 0x4) {
        HW_HDMI_IH_AHBDMAAUD_STAT0.U = 0x4;
        audio_Configure_DMA(HDMI_AUDIO_BUF_START, (HDMI_AUDIO_BUF_START + 0x17ff), 1, 4, 64, 4,
                            0x7f);
    }
}

void hdmi_1080P60_video_output(int ipu_index, int ipu_di)
{
    int hdmi_src = ((ipu_index - 1) << 1) | ipu_di;
    // configure IPU to output stream for hdmi input
    ips_hdmi_1080P60_stream(ipu_index);

    hdmi_data_info_s myHDMI_info = { 0 };   // declare new hdmi module object instance
    hdmi_vmode_s myHDMI_vmode_info = { 0 }; // declare new hdmi module object instance
    myHDMI_info.video_mode = &myHDMI_vmode_info;

    myHDMI_info.enc_in_format = eRGB;
    myHDMI_info.enc_out_format = eRGB;
    myHDMI_info.enc_color_depth = 8;
    myHDMI_info.colorimetry = eITU601;
    myHDMI_info.pix_repet_factor = 0;
    myHDMI_info.hdcp_enable = 0;
    myHDMI_info.video_mode->mCode = 16; //1920x1080p @ 59.94/60Hz 16:9
    myHDMI_info.video_mode->mHdmiDviSel = TRUE;
    myHDMI_info.video_mode->mRVBlankInOSC = FALSE;
    myHDMI_info.video_mode->mRefreshRate = 60000;
    myHDMI_info.video_mode->mDataEnablePolarity = TRUE;

    hdmi_av_frame_composer(&myHDMI_info);
    hdmi_video_packetize(myHDMI_info);
    hdmi_video_csc(myHDMI_info);
    hdmi_video_sample(myHDMI_info);

    hdmi_audio_mute(TRUE);
    hdmi_tx_hdcp_config(myHDMI_info.video_mode->mDataEnablePolarity);

    hdmi_phy_init(TRUE, myHDMI_info.video_mode->mPixelClock);

    hdmi_config_input_source(hdmi_src); // configure input source to HDMI block

}

void hdmi_720P60_video_output(int ipu_index, int ipu_di)
{
    int hdmi_src = ((ipu_index - 1) << 1) | ipu_di;
    // configure IPU to output stream for hdmi input
    ips_hdmi_720P60_stream(ipu_index);

    hdmi_data_info_s myHDMI_info = { 0 };   // declare new hdmi module object instance
    hdmi_vmode_s myHDMI_vmode_info = { 0 }; // declare new hdmi module object instance
    myHDMI_info.video_mode = &myHDMI_vmode_info;

    myHDMI_info.enc_in_format = eRGB;
    myHDMI_info.enc_out_format = eRGB;
    myHDMI_info.enc_color_depth = 8;
    myHDMI_info.colorimetry = eITU601;
    myHDMI_info.pix_repet_factor = 0;
    myHDMI_info.hdcp_enable = 0;
    myHDMI_info.video_mode->mCode = 4;  //1280x720p @ 59.94/60Hz 16:9
    myHDMI_info.video_mode->mHdmiDviSel = TRUE;
    myHDMI_info.video_mode->mRVBlankInOSC = FALSE;
    myHDMI_info.video_mode->mRefreshRate = 60000;
    myHDMI_info.video_mode->mDataEnablePolarity = TRUE;

    hdmi_av_frame_composer(&myHDMI_info);
    hdmi_video_packetize(myHDMI_info);
    hdmi_video_csc(myHDMI_info);
    hdmi_video_sample(myHDMI_info);

    hdmi_audio_mute(TRUE);
    hdmi_tx_hdcp_config(myHDMI_info.video_mode->mDataEnablePolarity);

    hdmi_phy_init(TRUE, myHDMI_info.video_mode->mPixelClock);

    hdmi_config_input_source(hdmi_src); // configure input source to HDMI block

}
