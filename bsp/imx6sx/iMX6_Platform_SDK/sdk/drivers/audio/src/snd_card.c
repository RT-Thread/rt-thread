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
 * @file snd_card.c
 * @brief Sound card driver.
 *
 * @ingroup diag_audio
 */

#include "sdk.h"
#include "audio/audio.h"

#define DEBUG_ENABLE	1
#if DEBUG_ENABLE
#define TRACE(fmt, args...)	printf(fmt,##args)
#else
#define TRACE(fmt, args...)
#endif

extern audio_ctrl_t imx_ssi_2;
extern audio_codec_t sgtl5000;
extern audio_codec_t wm8958;
extern audio_codec_t wm8962;

#if !defined (CHIP_MX6SL)
extern audio_ctrl_t imx_esai_1;
#endif
extern audio_codec_t cs42888;

extern audio_ctrl_t imx_spdif;

static int32_t snd_card_init(void *priv)
{
    audio_card_p card = (audio_card_p) priv;
    audio_ctrl_p ctrl = card->ctrl;
    audio_codec_p codec = card->codec;

    if (NULL == priv)
        return -1;

    // Some snd card has no codec, such as spdif
    if (NULL != codec) {
        if (0 != codec->ops->init((void *)codec)) {
            TRACE("Initialize %s failed.\n", codec->name);
            return -3;
        }
    }


    if (0 != ctrl->ops->init((void *)ctrl)) {
        TRACE("Initialize %s failed.\n", ctrl->name);
        return -2;
    }
    return 0;
}

static int32_t snd_card_deinit(void *priv)
{
    audio_card_p card = (audio_card_p) priv;
    audio_ctrl_p ctrl = card->ctrl;
    audio_codec_p codec = card->codec;

    if (NULL == priv)
        return -1;

    if (0 != ctrl->ops->deinit((void *)ctrl)) {
        TRACE("De-initialize %s failed.\n", ctrl->name);
        return -2;
    }
    // Some snd card has no codec, such as spdif
    if (NULL != codec) {
        if (0 != codec->ops->deinit((void *)codec)) {
            TRACE("De-initialize %s failed.\n", codec->name);
            return -3;
        }
    }

    return 0;
}

/*!
 *  Default config function for sound card.
 * &para	para 	the parameters passed by the app, dedicated to the audio 
 *			controller, the parameters for codec should be set according it.
 */
static int32_t snd_card_config(void *priv, audio_dev_para_p para)
{
    audio_card_p card = (audio_card_p) priv;
    audio_ctrl_p ctrl = card->ctrl;
    audio_codec_p codec = card->codec;

    if (NULL == priv)
        return -1;

    if (0 != ctrl->ops->config((void *)ctrl, para)) {
        TRACE("Configure %s failed.\n", ctrl->name);
        return -2;
    }
    //Set the parameters for codec according para
    //if audio controller is master, the codec should be slave.
    if (AUDIO_BUS_MODE_MASTER == para->bus_mode)
        para->bus_mode = AUDIO_BUS_MODE_SLAVE;
    else if (AUDIO_BUS_MODE_SLAVE == para->bus_mode)
        para->bus_mode = AUDIO_BUS_MODE_MASTER;
    //if audio controller transmits, the codec should receive.
    if (AUDIO_TRANS_DIR_TX == para->trans_dir)
        para->trans_dir = AUDIO_TRANS_DIR_RX;
    else if (AUDIO_TRANS_DIR_RX == para->trans_dir)
        para->trans_dir = AUDIO_TRANS_DIR_TX;

    // Some snd card has no codec, such as spdif
    if (NULL != codec) {
        if (0 != codec->ops->config((void *)codec, para)) {
            TRACE("Configure %s failed.\n", codec->name);
            return -3;
        }
    }

    return 0;
}

static int32_t snd_card_ioctl(void *priv, uint32_t cmd, void *para)
{
    //audio_card_p card = (audio_card_p) priv;
    //audio_ctrl_p ctrl = card->ctrl;
    //audio_codec_p codec = card->codec;

    if (NULL == priv)
        return -1;

    return 0;
}

static int32_t snd_card_write(void *priv, uint8_t * buf, uint32_t bytes2write,
                              uint32_t * bytes_written)
{
    audio_card_p card = (audio_card_p) priv;
    audio_ctrl_p ctrl = card->ctrl;

    ctrl->ops->write((void *)ctrl, buf, bytes2write, bytes_written);

    return 0;
}

static int32_t snd_card_read(void *priv, uint8_t * buf, uint32_t bytes2read,
                              uint32_t * bytes_read)
{
    audio_card_p card = (audio_card_p) priv;
    audio_ctrl_p ctrl = card->ctrl;
    
    ctrl->ops->read((void *)ctrl, buf, bytes2read, bytes_read);

    return 0;
}

static audio_dev_ops_t snd_card_ops = {
    .init = snd_card_init,
    .deinit = snd_card_deinit,
    .config = snd_card_config,
    .ioctl = snd_card_ioctl,
    .write = snd_card_write,
    .read = snd_card_read,
};

#if !defined (CHIP_MX6SL)
audio_card_t snd_card_esai = {
    .name = "i.MX ESAI sound card - cs42888",
    .codec = &cs42888,
    .ctrl = &imx_esai_1,
    .ops = &snd_card_ops,
};
#endif
audio_card_t snd_card_spdif = {
    .name = "i.MX SPDIF sound card",
    .codec = NULL,
    .ctrl = &imx_spdif,
    .ops = &snd_card_ops,
};

#if !defined (CHIP_MX6SL)
audio_card_t snd_card_ssi_sgtl5000 = {
    .name = "i.MX SSI sound card - sgtl5000",
    .codec = &sgtl5000,
    .ctrl = &imx_ssi_2,
    .ops = &snd_card_ops,
};

audio_card_t snd_card_ssi_wm8958 = {
    .name = "i.MX SSI sound card - wm8958",
    .codec = &wm8958,
    .ctrl = &imx_ssi_2,
    .ops = &snd_card_ops,
};
#endif
audio_card_t snd_card_ssi_wm8962 = {
    .name = "i.MX SSI sound card - wm8962",
    .codec = &wm8962,
    .ctrl = &imx_ssi_2,
    .ops = &snd_card_ops,
};

