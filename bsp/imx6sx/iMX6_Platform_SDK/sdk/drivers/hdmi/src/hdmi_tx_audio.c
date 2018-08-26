
/*
 * Copyright (c) 2010-2012, Freescale Semiconductor, Inc.
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

#include "sdk.h"
#include "hdmi_tx.h"
#include "registers/regshdmi.h"

///////////////////////////////////////////////////////////////////////////////////
// CODE
///////////////////////////////////////////////////////////////////////////////////

uint32_t hdmi_audio_mute(uint32_t en)
{
    HW_HDMI_FC_AUDSCONF.B.AUD_PACKET_SAMPFIT = (en == TRUE) ? 0xF : 0;
    return TRUE;
}

void audio_PacketLayout(uint8_t bit)
{
    HW_HDMI_FC_AUDSCONF.B.AUD_PACKET_LAYOUT = bit;
}

void audio_DMA_InterruptMask(uint8_t value)
{
    HW_HDMI_AHB_DMA_MASK.U = value;
}

void audio_DMA_InterruptPolarity(uint8_t value)
{
    HW_HDMI_AHB_DMA_POL.U = value;
}

void audio_DMA_ResetFIFO()
{
    HW_HDMI_AHB_DMA_CONF0.B.SW_FIFO_RST = 1;
}

void audio_clk_N(uint32_t value)
{
    HW_HDMI_AUD_N1.U = value >> 0;
    HW_HDMI_AUD_N2.U = value >> 8;
    HW_HDMI_AUD_N3.U = value >> 16;
}

void audio_clk_CTS(uint32_t value)
{
    HW_HDMI_AUD_CTS1.U = value >> 0;
    HW_HDMI_AUD_CTS2.U = value >> 8;
    HW_HDMI_AUD_CTS3.B.AUDCTS = value >> 16;
    HW_HDMI_AUD_CTS3.B.RESERVED0 = (value != 0) ? 1 : 0;
}

unsigned audio_ComputeN(uint32_t freq, uint16_t pixelClk, unsigned ratioClk)
{
    uint32_t n = (128 * freq) / 1000;

    switch (freq) {
    case 32000:
        if (pixelClk == 2517) {
            n = (ratioClk == 150) ? 9152 : 4576;
        } else if (pixelClk == 2702) {
            n = (ratioClk == 150) ? 8192 : 4096;
        } else if (pixelClk == 7417 || pixelClk == 14835) {
            n = 11648;
        } else {
            n = 4096;
        }
        break;
    case 44100:
        if (pixelClk == 2517) {
            n = 7007;
        } else if (pixelClk == 7417) {
            n = 17836;
        } else if (pixelClk == 14835) {
            n = (ratioClk == 150) ? 17836 : 8918;
        } else {
            n = 6272;
        }
        break;
    case 48000:
        if (pixelClk == 2517) {
            n = (ratioClk == 150) ? 9152 : 6864;
        } else if (pixelClk == 2702) {
            n = (ratioClk == 150) ? 8192 : 6144;
        } else if (pixelClk == 7417) {
            n = 11648;
        } else if (pixelClk == 14835) {
            n = (ratioClk == 150) ? 11648 : 5824;
        } else {
            n = 6144;
        }
        break;
    case 88200:
        n = audio_ComputeN(44100, pixelClk, ratioClk) * 2;
        break;
    case 96000:
        n = audio_ComputeN(48000, pixelClk, ratioClk) * 2;
        break;
    case 176400:
        n = audio_ComputeN(44100, pixelClk, ratioClk) * 4;
        break;
    case 192000:
        n = audio_ComputeN(48000, pixelClk, ratioClk) * 4;
        break;
    default:
        break;
    }
    return n;
}

unsigned audio_ComputeCTS(uint32_t freq, uint16_t pixelClk, unsigned ratioClk)
{
    uint32_t cts = 0;
    switch (freq) {
    case 32000:
        if (pixelClk == 29700) {
            cts = 222750;
            break;
        }
    case 48000:
    case 96000:
    case 192000:
        switch (pixelClk) {
        case 2520:
        case 2700:
        case 5400:
        case 7425:
        case 14850:
            cts = pixelClk * 10;
            break;
        case 29700:
            cts = 247500;
            break;
        default:
            //All other TMDS clocks are not supported by DWC_hdmi_tx
            //the TMDS clocks divided or multiplied by 1,001
            //coefficients are not supported.
            break;
        }
        break;
    case 44100:
    case 88200:
    case 176400:
        switch (pixelClk) {
        case 2520:
            cts = 28000;
            break;
        case 2700:
            cts = 30000;
            break;
        case 5400:
            cts = 60000;
            break;
        case 7425:
            cts = 82500;
            break;
        case 14850:
            cts = 165000;
            break;
        case 29700:
            cts = 247500;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    return (cts * ratioClk) / 100;
}

void audio_DMA_StartAddr(uint32_t value)
{
    HW_HDMI_AHB_DMA_STRADDR0.U = value >> 0;
    HW_HDMI_AHB_DMA_STRADDR1.U = value >> 8;
    HW_HDMI_AHB_DMA_STRADDR2.U = value >> 16;
    HW_HDMI_AHB_DMA_STRADDR3.U = value >> 24;
}

void audio_DMA_StopAddr(uint32_t value)
{
    HW_HDMI_AHB_DMA_STPADDR0.U = value >> 0;
    HW_HDMI_AHB_DMA_STPADDR1.U = value >> 8;
    HW_HDMI_AHB_DMA_STPADDR2.U = value >> 16;
    HW_HDMI_AHB_DMA_STPADDR3.U = value >> 24;
}

void audio_DMA_LockEnable(uint8_t bit)
{
    HW_HDMI_AHB_DMA_CONF0.B.ENABLE_HLOCK = bit;
}

void audio_DMA_BurstMode(uint8_t bit)
{
    HW_HDMI_AHB_DMA_CONF0.B.BURST_MODE = bit;
}

void audio_DMA_IncrType(uint8_t value)
{
    HW_HDMI_AHB_DMA_CONF0.B.INCR_TYPE = value;
}

void audio_DMA_Threshold(uint8_t value)
{
    HW_HDMI_AHB_DMA_THRSLD.U = value;
}

void audio_DMA_SetCONF1(uint8_t value)
{
    HW_HDMI_AHB_DMA_CONF1.U = value;
}

void audio_DMA_Start(void)
{
    HW_HDMI_AHB_DMA_START.B.DATA_BUFFER_READY = 1;
}

int audio_Configure(hdmi_audioparam_s hdmi_audioparam_instance, uint16_t pixelClk,
                    unsigned ratioClk)
{
    audio_PacketLayout((Audio_ChannelCount(hdmi_audioparam_instance.ChannelAllocation) >
                        2) ? 1 : 0);

    audio_DMA_InterruptMask(0x7f);
    audio_DMA_InterruptPolarity(0xFF);
    audio_DMA_ResetFIFO();

    audio_clk_N(audio_ComputeN(hdmi_audioparam_instance.SamplingFrequency, pixelClk, ratioClk));
    audio_clk_CTS(audio_ComputeCTS(hdmi_audioparam_instance.SamplingFrequency, pixelClk, ratioClk));    // automatic mode
    audio_info_config();
    return hdmi_audio_mute(FALSE);
}

uint8_t Audio_ChannelCount(uint8_t mChannelAllocation)
{
    switch (mChannelAllocation) {
    case 0x00:
        return 1;
    case 0x01:
    case 0x02:
    case 0x04:
        return 2;
    case 0x03:
    case 0x05:
    case 0x06:
    case 0x08:
    case 0x14:
        return 3;
    case 0x07:
    case 0x09:
    case 0x0A:
    case 0x0C:
    case 0x15:
    case 0x16:
    case 0x18:
        return 4;
    case 0x0B:
    case 0x0D:
    case 0x0E:
    case 0x10:
    case 0x17:
    case 0x19:
    case 0x1A:
    case 0x1C:
        return 5;
    case 0x0F:
    case 0x11:
    case 0x12:
    case 0x1B:
    case 0x1D:
    case 0x1E:
        return 6;
    case 0x13:
    case 0x1F:
        return 7;
    default:
        return 0;
    }
}

void audio_Configure_DMA(uint32_t startAddr, uint32_t stopAddr, uint8_t hlockEn, uint8_t incrType,
                         uint8_t threshold, uint32_t audioChnl, uint8_t intMask)
{
    audio_DMA_StartAddr(startAddr);
    audio_DMA_StopAddr(stopAddr);
    audio_DMA_LockEnable(hlockEn);

    switch (incrType) {
    case 1:
        audio_DMA_BurstMode(0);
        audio_DMA_IncrType(0);
        break;
    case 4:
        audio_DMA_BurstMode(1);
        audio_DMA_IncrType(0);
        break;
    case 8:
        audio_DMA_BurstMode(1);
        audio_DMA_IncrType(1);
        break;
    case 16:
        audio_DMA_BurstMode(1);
        audio_DMA_IncrType(2);
        break;
    default:
        printf("invalid incrType: 0x%x\n", incrType);
        break;
    }
    audio_DMA_Threshold(threshold);
    audio_DMA_InterruptMask(intMask);
    audio_DMA_InterruptPolarity(0xFF);

    switch (audioChnl) {
    case 2:
        audio_DMA_SetCONF1(0x3);
        break;
    case 4:
        audio_DMA_SetCONF1(0xF);
        break;
    case 6:
        audio_DMA_SetCONF1(0x3F);
        break;
    case 8:
        audio_DMA_SetCONF1(0xFF);
        break;
    default:
        printf("invalid auduo channel number: 0x%x\n", audioChnl);
        break;
    }

    audio_DMA_Start();
}

void audio_info_config(void)
{
    HW_HDMI_FC_AUDICONF0.U = 0x10;
    HW_HDMI_FC_AUDICONF1.U = 0x00;
    HW_HDMI_FC_AUDICONF2.U = 0x00;
}

///////////////////////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////////////////////
