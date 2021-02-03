/*
 * Copyright (c) 2020-2021, Bluetrum Development Team
 * 
 * SPDX-License-Identifier: Apache-2.0
 *
 * Date           Author       Notes
 * 2020-12-12     greedyhao    first implementation
 */

#include <board.h>

#define DBG_TAG              "drv.snd_dev"
#define DBG_LVL              DBG_INFO
#include <rtdbg.h>

#define SAI_AUDIO_FREQUENCY_44K         ((uint32_t)44100u)
#define SAI_AUDIO_FREQUENCY_48K         ((uint32_t)48000u)
#define TX_FIFO_SIZE         (1024)

struct sound_device
{
    struct rt_audio_device audio;
    struct rt_audio_configure replay_config;
    rt_uint8_t *tx_fifo;
    rt_uint8_t *rx_fifo;
    rt_uint8_t volume;
};

static struct sound_device snd_dev = {0};

//apll = 采样率*ADPLL_DIV*512
//audio pll init
void adpll_init(uint8_t out_spr)
{
    PLL1CON &= ~(BIT(16) | BIT(17));                //PLL1 refclk select xosc26m
    CLKCON2  &= ~(BIT(4)| BIT(5) | BIT(6) | BIT(7));

    PLL1CON &= ~(BIT(3) | BIT(4) | BIT(5));
    PLL1CON |= BIT(3);                              //Select PLL/VCO frequency band (PLL大于206M vcos = 0x01, 否则为0)

    PLL1CON |= BIT(12);                             //enable pll1 ldo
    hal_mdelay(1);
    PLL1CON |= BIT(18);                             //pll1 sdm enable

    if (out_spr) {
        CLKCON2  |= BIT(4) | BIT(7);                 //adpll_div = 10
        PLL1DIV = (245.76 * 65536) / 26;            //245.76Mhz for 48K
        // sys.aupll_type = 1;
    } else {
        CLKCON2  |= BIT(5) | BIT(7);                 //adpll_div = 11
        PLL1DIV = (248.3712 * 65536) / 26;          //248.3712MHz for 44.1k
        // sys.aupll_type = 0;
    }
    hal_mdelay(1);
    PLL1CON |= BIT(20);                             //update pll1div
    PLL1CON |= BIT(6);                              //enable analog pll1
    hal_mdelay(1);                                 //wait pll1 stable
}

void dac_start(void)
{
    AUANGCON0 |= BIT(0) | BIT(1) | BIT(3); // bg ldoh bias enable

    AUANGCON0 &= ~(BIT(6)|BIT(5)|BIT(4));  // LDOH voltage select：3bit
    AUANGCON0 |= (3<<4); // 2.4/2.5/2.7/2.9/3.1/3.2

    AUANGCON0 |= BIT(2);           // LDOL enable

    AUANGCON0 |= BIT(9); //VCM enable
    AUANGCON0 &= ~(BIT(13)|BIT(12)); // VCM voltage select, 2bit
    AUANGCON0 |= (2<<12);

    AUANGCON0 |= BIT(15) | BIT(16) | BIT(17) | BIT(18); // d2a lpf audpa audpa_dly

    AUANGCON0 &= ~BIT(11); //VCM type: 0-->res divider with off-chip cap; 1-->internal VCM
    //AUANGCON0 |= BIT(11);

    AUANGCON0 &= ~BIT(19); // dac type: 0-->SC; 1-->SR
    //AUANGCON0 |= BIT(19);

    AUANGCON0 |= BIT(20); // pa type: 0-->diff; 1-->3.3V single

    AUANGCON3 &= ~(0x7<<4); //BIT[6:4]=PA_GF[2:0]
    AUANGCON3 |= (0<<4);
    AUANGCON3 &= ~(0xf); //BIT[3:0]=PA_GX[3:0]
    AUANGCON3 |= 0;

    AUANGCON3 &= ~(0xF<<8); //BIT[11:8]=PA2_GX[3:0]
    AUANGCON3 |= (0<<8);
    AUANGCON3 &= ~(0x7<<12); //BIT[14:12]=PA2_GF[2:0]
    AUANGCON3 |= (0<<12);

    AUANGCON1 |= BIT(0) | BIT(1); // dac enable: BIT(0)-->right channel; BIT(1)-->left channel
    //AUANGCON1 &= ~BIT(1); //disable left channel

    AUANGCON1 |= BIT(12); // lpf2pa enable

    AUANGCON1 &= ~BIT(29); // vcmbuf enable: 0-->disable
    //AUANGCON1 |= BIT(29);

    //AUANGCON1 |= BIT(30); // mirror enable

    //AUANGCON2 |= BIT(29) | BIT(30); // adc mute

    //AUANGCON1 |= BIT(3);  // pa mute
}

void saia_frequency_set(uint32_t frequency)
{
    if (frequency == SAI_AUDIO_FREQUENCY_48K) {
        DACDIGCON0 |= BIT(1);
        DACDIGCON0 &= ~(0xf << 2);
        DACDIGCON0 |= BIT(6);
    } else if (frequency == SAI_AUDIO_FREQUENCY_44K) {
        DACDIGCON0 &= ~BIT(1);
        DACDIGCON0 &= ~(0xf << 2);
        DACDIGCON0 |= BIT(1);
        DACDIGCON0 |= BIT(6);
    }
}

void saia_channels_set(uint8_t channels)
{
    LOG_D("saia_channels_set=%d", channels);
    if (channels == 1) {
        AU0LMIXCOEF = 0x00007FFF;
        AU1LMIXCOEF = 0x00007FFF;
        DACDIGCON0 |= BIT(7);
        DACDIGCON0 |= BIT(8);
        AUANGCON1 &= ~BIT(0);
    } else {
        AUANGCON1 |= BIT(0);
        DACDIGCON0 &= ~BIT(7);
        DACDIGCON0 &= ~BIT(8);
    }
}

void saia_volume_set(rt_uint8_t volume)
{
    if (volume > 100)
        volume = 100;
    
    uint32_t dvol = volume * 327; // max is 0x7ffff
    LOG_D("dvol=0x%x", dvol);
    DACVOLCON = dvol | (0x02 << 16); // dac fade in
}

uint8_t saia_volume_get(void)
{
    return ((DACVOLCON & 0xffff) / 327);
}

static rt_err_t sound_getcaps(struct rt_audio_device *audio, struct rt_audio_caps *caps)
{
    rt_err_t result = RT_EOK;
    struct sound_device *snd_dev = RT_NULL;

    RT_ASSERT(audio != RT_NULL); 
    snd_dev = (struct sound_device *)audio->parent.user_data;

    switch (caps->main_type)
    {
    case AUDIO_TYPE_QUERY: /* qurey the types of hw_codec device */
    {
        switch (caps->sub_type)
        {
        case AUDIO_TYPE_QUERY:
            caps->udata.mask = AUDIO_TYPE_OUTPUT | AUDIO_TYPE_MIXER;
            break;

        default:
            result = -RT_ERROR;
            break;
        }

        break;
    }

    case AUDIO_TYPE_OUTPUT: /* Provide capabilities of OUTPUT unit */
    {
        switch (caps->sub_type)
        {
        case AUDIO_DSP_PARAM:
            caps->udata.config.samplerate   = snd_dev->replay_config.samplerate;
            caps->udata.config.channels     = snd_dev->replay_config.channels;
            caps->udata.config.samplebits   = snd_dev->replay_config.samplebits;
            break;

        case AUDIO_DSP_SAMPLERATE:
            caps->udata.config.samplerate   = snd_dev->replay_config.samplerate;
            break;

        case AUDIO_DSP_CHANNELS:
            caps->udata.config.channels     = snd_dev->replay_config.channels;
            break;

        case AUDIO_DSP_SAMPLEBITS:
            caps->udata.config.samplebits   = snd_dev->replay_config.samplebits;
            break;

        default:
            result = -RT_ERROR;
            break;
        }

        break;
    }

    case AUDIO_TYPE_MIXER: /* report the Mixer Units */
    {
        switch (caps->sub_type)
        {
        case AUDIO_MIXER_QUERY:
            caps->udata.mask = AUDIO_MIXER_VOLUME;
            break;

        case AUDIO_MIXER_VOLUME:
            caps->udata.value =  saia_volume_get();
            break;

        default:
            result = -RT_ERROR;
            break;
        }

        break;
    }

    default:
        result = -RT_ERROR;
        break;
    }

    return RT_EOK; 
}

static rt_err_t sound_configure(struct rt_audio_device *audio, struct rt_audio_caps *caps)
{
    rt_err_t result = RT_EOK;
    struct sound_device *snd_dev = RT_NULL;

    RT_ASSERT(audio != RT_NULL);
    snd_dev = (struct sound_device *)audio->parent.user_data;

    switch (caps->main_type)
    {
    case AUDIO_TYPE_MIXER:
    {
        switch (caps->sub_type)
        {
        case AUDIO_MIXER_VOLUME:
        {
            rt_uint8_t volume = caps->udata.value;

            saia_volume_set(volume);
            snd_dev->volume = volume;
            LOG_D("set volume %d", volume);
            break;
        }

        default:
            result = -RT_ERROR;
            break;
        }

        break;
    }

    case AUDIO_TYPE_OUTPUT:
    {
        switch (caps->sub_type)
        {
        case AUDIO_DSP_PARAM:
        {
            /* set samplerate */
            saia_frequency_set(caps->udata.config.samplerate);
            /* set channels */
            saia_channels_set(caps->udata.config.channels);

            /* save configs */
            snd_dev->replay_config.samplerate = caps->udata.config.samplerate;
            snd_dev->replay_config.channels   = caps->udata.config.channels;
            snd_dev->replay_config.samplebits = caps->udata.config.samplebits;
            LOG_D("set samplerate %d", snd_dev->replay_config.samplerate);
            break;
        }

        case AUDIO_DSP_SAMPLERATE:
        {
            saia_frequency_set(caps->udata.config.samplerate);
            snd_dev->replay_config.samplerate = caps->udata.config.samplerate;
            LOG_D("set samplerate %d", snd_dev->replay_config.samplerate);
            break;
        }

        case AUDIO_DSP_CHANNELS:
        {
            saia_channels_set(caps->udata.config.channels);
            snd_dev->replay_config.channels   = caps->udata.config.channels;
            LOG_D("set channels %d", snd_dev->replay_config.channels);
            break;
        }

        case AUDIO_DSP_SAMPLEBITS:
        {
            /* not support */
            snd_dev->replay_config.samplebits = caps->udata.config.samplebits;
            break;
        }

        default:
            result = -RT_ERROR;
            break;
        }

        break;
    }

    default:
        break;
    }

    return RT_EOK; 
}

static rt_err_t sound_init(struct rt_audio_device *audio)
{
    struct sound_device *snd_dev = RT_NULL;

    RT_ASSERT(audio != RT_NULL); 
    snd_dev = (struct sound_device *)audio->parent.user_data;

    adpll_init(0);
    dac_start();

    /* set default params */
    saia_frequency_set(snd_dev->replay_config.samplerate);
    saia_channels_set(snd_dev->replay_config.channels);

    return RT_EOK; 
}

static rt_err_t sound_start(struct rt_audio_device *audio, int stream)
{
    struct sound_device *snd_dev = RT_NULL;

    RT_ASSERT(audio != RT_NULL); 
    snd_dev = (struct sound_device *)audio->parent.user_data;

    if (stream == AUDIO_STREAM_REPLAY)
    {
        LOG_D("open sound device");

        AUBUFSIZE       = (TX_FIFO_SIZE / 4 - 1);
        AUBUFSIZE       |= (TX_FIFO_SIZE / 8) << 16;
        AUBUFSTARTADDR  = DMA_ADR(snd_dev->rx_fifo);

        DACDIGCON0  = BIT(0) | BIT(10); // (0x01<<2)
        DACVOLCON   = 0x7fff; // -60DB
        DACVOLCON  |= BIT(20);

        AUBUFCON |= BIT(1) | BIT(4);
    }

    return RT_EOK;
}

static rt_err_t sound_stop(struct rt_audio_device *audio, int stream)
{
    struct sound_device *snd_dev = RT_NULL;

    RT_ASSERT(audio != RT_NULL); 
    snd_dev = (struct sound_device *)audio->parent.user_data; 

    if (stream == AUDIO_STREAM_REPLAY)
    {
        AUBUFCON &= ~BIT(4);
        LOG_D("close sound device");
    }

    return RT_EOK;
}

rt_size_t sound_transmit(struct rt_audio_device *audio, const void *writeBuf, void *readBuf, rt_size_t size)
{
    struct sound_device *snd_dev = RT_NULL;
    rt_size_t tmp_size = size / 4;
    rt_size_t count = 0;

    RT_ASSERT(audio != RT_NULL); 
    snd_dev = (struct sound_device *)audio->parent.user_data;

    while (tmp_size-- > 0) {
        while(AUBUFCON & BIT(8)); // aubuf full
        AUBUFDATA = ((const uint32_t *)writeBuf)[count++];
    }

    return size; 
}

static void sound_buffer_info(struct rt_audio_device *audio, struct rt_audio_buf_info *info)
{
    struct sound_device *snd_dev = RT_NULL;

    RT_ASSERT(audio != RT_NULL); 
    snd_dev = (struct sound_device *)audio->parent.user_data;

    /**
     *               TX_FIFO
     * +----------------+----------------+
     * |     block1     |     block2     |
     * +----------------+----------------+
     *  \  block_size  /
     */
    info->buffer      = snd_dev->tx_fifo;
    info->total_size  = TX_FIFO_SIZE;
    info->block_size  = TX_FIFO_SIZE / 2;
    info->block_count = 2;
}

static struct rt_audio_ops ops =
{
    .getcaps     = sound_getcaps,
    .configure   = sound_configure,
    .init        = sound_init,
    .start       = sound_start,
    .stop        = sound_stop,
    .transmit    = sound_transmit, 
    .buffer_info = sound_buffer_info,
};

void audio_isr(int vector, void *param)
{
    rt_interrupt_enter();

    //Audio buffer pend
    if (AUBUFCON & BIT(5)) {
        AUBUFCON |= BIT(1);         //Audio Buffer Pend Clear
        rt_audio_tx_complete(&snd_dev.audio);
    }
    rt_interrupt_leave();
}

static int rt_hw_sound_init(void)
{
    rt_uint8_t *tx_fifo = RT_NULL; 
    rt_uint8_t *rx_fifo = RT_NULL; 

    /* 分配 DMA 搬运 buffer */ 
    tx_fifo = rt_calloc(1, TX_FIFO_SIZE); 
    if(tx_fifo == RT_NULL)
    {
        return -RT_ENOMEM;
    }

    rt_memset(tx_fifo, 0, TX_FIFO_SIZE);
    snd_dev.tx_fifo = tx_fifo;

    /* 分配 DMA 搬运 buffer */ 
    rx_fifo = rt_calloc(1, TX_FIFO_SIZE); 
    if(rx_fifo == RT_NULL)
    {
        return -RT_ENOMEM;
    }

    rt_memset(rx_fifo, 0, TX_FIFO_SIZE);
    snd_dev.rx_fifo = rx_fifo;

    /* init default configuration */
    {
        snd_dev.replay_config.samplerate = 48000;
        snd_dev.replay_config.channels   = 2;
        snd_dev.replay_config.samplebits = 16;
        snd_dev.volume                   = 55;
    }

    /* register snd_dev device */
    snd_dev.audio.ops = &ops;
    rt_audio_register(&snd_dev.audio, "sound0", RT_DEVICE_FLAG_WRONLY, &snd_dev);

    rt_hw_interrupt_install(IRQ_AUBUF0_1_VECTOR, audio_isr, RT_NULL, "au_isr");

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_sound_init);
