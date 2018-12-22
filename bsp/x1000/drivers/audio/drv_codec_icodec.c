#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <drivers/audio.h>

#ifdef RT_USING_FINSH
#include <finsh.h>
#endif

#include "board.h"
#include "dma.h"

#ifdef RT_USING_ICODEC

#include "drv_gpio.h"
#include "drv_clock.h"
#include "drv_aic.h"
#include "drv_aic_i2s.h"
#include "drv_codec_icodec.h"

#define CODEC_DEBUG   0
#if CODEC_DEBUG
#define CODEC_DBG(...)     rt_kprintf("[CODEC]"),rt_kprintf(__VA_ARGS__)
#else
#define CODEC_DBG(...)
#endif

/*
 * Sampling rate
 */
const int sample_attr[] =
{
	  8000,  11025,  12000,  16000,
	 22050,  24000,  32000,  44100,
	 48000,  88200,  96000, 176400,
	192000,
};

static uint8_t _g_icodec_reg_defcache[SCODA_MAX_REG_NUM] =
{
#if 1
    /* reg 0x0 ... 0x9 */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03,
    /* reg 0xa ... 0x13 */
    0x00,0x40,0x30,0x80,0x01,0x00,0x00,0x00,0x0f,0x40,
    /* reg 0x14 ... 0x1d */
    0x07,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0xff,
    /* reg 0x1e ... 0x27 */
    0x00,0x06,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    /* reg 0x28 ... 0x31 */
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    /* reg 0x32 ... 0x39 */
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    /* extern reg */
    0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x34,0x07,0x44,0x1f,0x00,
#else
	/* reg 0x0 ... 0x9 */
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03,
	/* reg 0xa ... 0x13 */
			0x00,0x00,0x30,0xb0,0x01,0x00,0x00,0x00,0x0F,0x40,
	/* reg 0x14 ... 0x1d */
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0xff,
	/* reg 0x1e ... 0x27 */
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	/* reg 0x28 ... 0x31 */
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	/* reg 0x32 ... 0x39 */
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	/* extern reg */
			0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,
			0x34,0x07,0x44,0x1f,0x00,
#endif
};

static int jz_icodec_reg_volatile(uint32_t reg)
{
    if (reg > SCODA_MAX_REG_NUM)
        return 1;

    switch (reg)
    {
    case SCODA_REG_SR:
    case SCODA_REG_SR2:
    case SCODA_REG_SIGR:
    case SCODA_REG_SIGR3:
    case SCODA_REG_SIGR5:
    case SCODA_REG_SIGR7:
    case SCODA_REG_MR:
    case SCODA_REG_IFR:
    case SCODA_REG_IFR2:
    case SCODA_REG_SR_ADC_AGCDGL:
    case SCODA_REG_SR_ADC_AGCDGR:
    case SCODA_REG_SR_ADC_AGCAGL:
    case SCODA_REG_SR_ADC_AGCAGR:
    case SCODA_REG_SR_TR1:
    case SCODA_REG_SR_TR2:
    case SCODA_REG_SR_TR_SRCDAC:
        return 1;
    default:
        return 0;
    }
}

static int jz_icodec_reg_writable(uint32_t reg)
{
    if (reg > SCODA_MAX_REG_NUM)
        return 0;

    switch (reg) {
    case SCODA_REG_SR:
    case SCODA_REG_SR2:
    case SCODA_REG_SIGR:
    case SCODA_REG_SIGR3:
    case SCODA_REG_SIGR5:
    case SCODA_REG_SIGR7:
    case SCODA_REG_MR:
    case SCODA_REG_SR_ADC_AGCDGL:
    case SCODA_REG_SR_ADC_AGCDGR:
    case SCODA_REG_SR_ADC_AGCAGL:
    case SCODA_REG_SR_ADC_AGCAGR:
    case SCODA_REG_SR_TR1:
    case SCODA_REG_SR_TR2:
    case SCODA_REG_SR_TR_SRCDAC:
        return 0;
    default:
        return 1;
    }
}

static int jz_icodec_reg_readable(uint32_t reg)
{
    if (reg > SCODA_MAX_REG_NUM)
        return 0;
    else
        return 1;
}

static uint8_t jz_icodec_reg_read(struct jz_icodec *icodec, uint32_t reg)
{
    int     ret = 0;
    uint8_t val = 0;

	if (!jz_icodec_reg_volatile(reg))
	{
		val = icodec_hw_read(icodec, reg);
		if ((reg == SCODA_REG_GCR_DACL) || (reg == SCODA_REG_GCR_DACR)) {
			if (val < 32)
				val = 31 - val;
			else
				val = 95 - val;
		}
		return val;
	}

	if (jz_icodec_reg_readable(reg))
		return icodec_hw_read(icodec, reg);

	return 0;
}

static int jz_icodec_reg_write(struct jz_icodec *codec, uint16_t reg, int value)
{
    int ret = 0;
    int val = value;

    if (jz_icodec_reg_writable(reg))
    {
		if (!jz_icodec_reg_volatile(reg))
		{
			if((reg == SCODA_REG_GCR_DACL)||(reg == SCODA_REG_GCR_DACR))
			{
				if(val < 32)
					val = 31 - val;
				else
					val = 95 - val;
			}
			_g_icodec_reg_defcache[reg] = val;
		}

		return icodec_hw_write(codec, reg, val);
    }

    return 0;
}


static int jz_icodec_reg_update_bits(struct jz_icodec *icodec, uint16_t reg, uint32_t mask, uint16_t value)
{
    uint8_t change;
    uint8_t old, new;

    int ret;

    ret = jz_icodec_reg_read(icodec, reg);
    if (ret < 0)
        return ret;

    old = ret;
    new = (old & ~mask) | (value & mask);
    change = old != new;
    if (change)
        ret = jz_icodec_reg_write(icodec, reg, new);

    if (ret < 0)
        return ret;

    return change;
}

static int jz_icodec_set_sampling_rate(struct jz_icodec *icodec, int rate)
{
    /* sampling rate */
    int speed_sel = 0;
    if(rate == icodec->replay_config.samplerate)
        return rate;

    /* set sampling rate */
    for (speed_sel = 0; rate > sample_attr[speed_sel]; speed_sel++) ;

    jz_icodec_reg_update_bits(icodec, SCODA_REG_FCR_DAC, SCODA_FCR_FREQ_MASK, (speed_sel << SCODA_FCR_FREQ_SHIFT));
    jz_icodec_reg_update_bits(icodec, SCODA_REG_FCR_ADC, SCODA_FCR_FREQ_MASK, (speed_sel << SCODA_FCR_FREQ_SHIFT));

    rate = sample_attr[speed_sel];
    icodec->replay_config.samplerate = rate;
    return rate;
}

static void jz_icodec_hw_params(struct jz_icodec* icodec,int stream)
{
	int playback = (stream == AUDIO_STREAM_REPLAY);
    int speed_sel = 0;
	int bit_width_sel = 3;
	int aicr_reg = playback ? SCODA_REG_AICR_DAC : SCODA_REG_AICR_ADC;
	int fcr_reg = playback ? SCODA_REG_FCR_DAC : SCODA_REG_FCR_ADC;

	/* bit width */
	switch (icodec->replay_config.samplefmt)
	{
	case AUDIO_FMT_PCM_S16_LE:
		bit_width_sel = 0;
		break;
	case AUDIO_FMT_PCM_S24_LE:
		bit_width_sel = 3;
		break;
	}

	/*sample rate*/
	for (speed_sel = 0; icodec->replay_config.samplerate > sample_attr[speed_sel]; speed_sel++);

	jz_icodec_reg_update_bits(icodec, aicr_reg, SCODA_AICR_DAC_ADWL_MASK,(bit_width_sel << SCODA_AICR_DAC_ADWL_SHIFT));
	jz_icodec_reg_update_bits(icodec, fcr_reg, SCODA_FCR_FREQ_MASK,(speed_sel << SCODA_FCR_FREQ_SHIFT));
}


static int jz_icodec_digital_mute(struct jz_icodec *icodec, int mute)
{
    jz_icodec_reg_update_bits(icodec, SCODA_REG_CR_DAC, SCODA_CR_DAC_SMUTE_MASK, (!!mute) << SCODA_CR_DAC_SMUTE_SHIFT);
    jz_icodec_reg_update_bits(icodec, SCODA_REG_CR_ADC, SCODA_CR_ADC_SMUTE_MASK, (!!mute) << SCODA_CR_ADC_SMUTE_SHIFT);

    return 0;
}

static void jz_icodec_startup(struct jz_icodec *icodec)
{
	/*power on codec*/
	if (jz_icodec_reg_update_bits(icodec, SCODA_REG_CR_VIC, SCODA_CR_VIC_SB_MASK, 0))
		rt_thread_delay(rt_tick_from_millisecond(250));
	if (jz_icodec_reg_update_bits(icodec, SCODA_REG_CR_VIC, SCODA_CR_VIC_SB_SLEEP_MASK, 0))
		rt_thread_delay(rt_tick_from_millisecond(400));
}

static void jz_icodec_shutdown(struct jz_icodec *icodec)
{
	/*power off codec*/
	jz_icodec_reg_update_bits(icodec, SCODA_REG_CR_VIC, SCODA_CR_VIC_SB_SLEEP_MASK, 1);
	jz_icodec_reg_update_bits(icodec, SCODA_REG_CR_VIC, SCODA_CR_VIC_SB_MASK, 1);
}

static void jz_icodec_mute_stream(struct jz_icodec *icodec, int mute, int stream)
{

	if(stream == AUDIO_STREAM_REPLAY)
	{
		jz_icodec_reg_update_bits(icodec, SCODA_REG_CR_DAC, SCODA_CR_DAC_SMUTE_MASK, (!!mute) << SCODA_CR_DAC_SMUTE_SHIFT);
	}
	else if(stream == AUDIO_STREAM_RECORD)
	{
		jz_icodec_reg_update_bits(icodec, SCODA_REG_CR_ADC, SCODA_CR_ADC_SMUTE_MASK, (!!mute) << SCODA_CR_ADC_SMUTE_SHIFT);
	}
}

#define VOLUME_MIN		0
#define VOLUME_MAX 		100

#define REPLAY_REG_MAX	(63)
static int jz_icodec_set_replay_volume(struct jz_icodec *icodec,int val)
{
	int phyValue = 0;
    /* get current volume */
    if (val < VOLUME_MIN)
        val = VOLUME_MIN;
    else if(val >= VOLUME_MAX)
    	val = VOLUME_MAX;

	phyValue = (val* REPLAY_REG_MAX)  / VOLUME_MAX;

    CODEC_DBG("volume = %d\n",val);
    jz_icodec_reg_write(icodec,SCODA_REG_GCR_DACL,phyValue);
    jz_icodec_reg_write(icodec,SCODA_REG_GCR_DACR,phyValue);

    icodec->user_replay_volume = jz_icodec_reg_read(icodec,SCODA_REG_GCR_DACL);

    if (val == 0)
    {
        jz_icodec_digital_mute(icodec,1);
    }
    else
    {
        jz_icodec_digital_mute(icodec,0);
    }

    return val;
}

#define REPLAY_MIXER_REG_MAX	31
int jz_icodec_set_replay_mixer_volume(struct jz_icodec *icodec,int val)
{
	int phyValue = 0;
    /* get current volume */
    if (val < VOLUME_MIN)
        val = VOLUME_MIN;
    else if(val >= VOLUME_MAX)
    	val = VOLUME_MAX;

	phyValue = (val * REPLAY_MIXER_REG_MAX)  / VOLUME_MAX;

    jz_icodec_reg_write(icodec,SCODA_REG_GCR_MIXDACL,phyValue);
    jz_icodec_reg_write(icodec,SCODA_REG_GCR_MIXDACR,phyValue);

    return val;
}

#define DIGITAL_CAP_REG_MAX	43
int jz_icodec_set_digital_capture_volume(struct jz_icodec *icodec,int val)
{
	int phyValue = 0;
    /* get current volume */
    if (val < VOLUME_MIN)
        val = VOLUME_MIN;
    else if(val >= VOLUME_MAX)
    	val = VOLUME_MAX;

	phyValue = (val * DIGITAL_CAP_REG_MAX) / VOLUME_MAX;

    jz_icodec_reg_write(icodec,SCODA_REG_GCR_ADCL,phyValue);
    jz_icodec_reg_write(icodec,SCODA_REG_GCR_ADCR,phyValue);

    return val;
}

#define DIGITAL_CAP_MIX_REG_MAX		31
int jz_icodec_set_digital_capture_mixer_volume(struct jz_icodec *icodec,int val)
{
	int phyValue = 0;
    /* get current volume */
    if (val < VOLUME_MIN)
        val = VOLUME_MIN;
    else if(val >= VOLUME_MAX)
    	val = VOLUME_MAX;

	phyValue = (val * DIGITAL_CAP_MIX_REG_MAX) / VOLUME_MAX;

    jz_icodec_reg_write(icodec,SCODA_REG_GCR_MIXADCL,phyValue);
    jz_icodec_reg_write(icodec,SCODA_REG_GCR_MIXADCR,phyValue);

    return val;
}

#define MIC_REG_MAX	4
int aic_icodec_set_mic_volume(struct jz_icodec *icodec,int val)
{
	int phyValue = 0;
    /* get current volume */
    if (val < VOLUME_MIN)
        val = VOLUME_MIN;
    else if(val >= VOLUME_MAX)
    	val = VOLUME_MAX;

	phyValue = MIC_REG_MAX - (val) * MIC_REG_MAX / VOLUME_MAX;

    jz_icodec_reg_write(icodec,SCODA_REG_GCR_MIC1,phyValue);

    return val;
}


enum
{
	AMIC_ON = 0,
	DMIC_ON = 1,
};
void jz_icodec_adc_mic_select(struct jz_icodec *icodec, int dmic)
{
	if(dmic == DMIC_ON)
	{
	    jz_icodec_reg_update_bits(icodec, SCODA_REG_CR_ADC, SCODA_CR_ADC_MIC_SEL_MASK, (1 << SCODA_CR_ADC_MIC_SEL_SHIFT));
	}
	else
	{
		jz_icodec_reg_update_bits(icodec, SCODA_REG_CR_ADC, SCODA_CR_ADC_MIC_SEL_MASK, (0 << SCODA_CR_ADC_MIC_SEL_SHIFT));
	}
}

void jz_icodec_adc_capture_enable(struct jz_icodec *icodec,int enable)
{
	if(enable)
	{
	    jz_icodec_reg_update_bits(icodec, SCODA_REG_AICR_ADC, SCODA_AICR_ADC_SB_MASK, (0 << SCODA_AICR_ADC_SB_SHIFT));
	}
	else
	{
	    jz_icodec_reg_update_bits(icodec, SCODA_REG_AICR_ADC, SCODA_AICR_ADC_SB_MASK, (1 << SCODA_AICR_ADC_SB_SHIFT));
	}
}




/*********************************************************************************************************
**   Audio device
*********************************************************************************************************/

static rt_err_t icodec_getcaps		(struct rt_audio_device *audio,struct rt_audio_caps *caps)
{
	rt_err_t result = RT_EOK;
	struct jz_icodec *icodec = (struct jz_icodec *)audio->parent.user_data;
	CODEC_DBG("type = %d\n",caps->main_type);

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
            switch (caps->sub_type)
            {
                case AUDIO_DSP_PARAM:
                    if (audio->replay == NULL)
                    {
                        result = -RT_ERROR;
                        break;
                    }
                    caps->udata.config.channels     = icodec->replay_config.channels;
                    caps->udata.config.samplefmt    = icodec->replay_config.samplefmt;
                    caps->udata.config.samplerate   = icodec->replay_config.samplerate;
                    caps->udata.config.samplefmts   = icodec->replay_config.samplefmts;
                    break;
                default:
                    result = -RT_ERROR;
                    break;
            }
            break;
        case AUDIO_TYPE_MIXER: /* report the Mixer Units */
            switch (caps->sub_type)
            {
                case AUDIO_MIXER_QUERY:
                    caps->udata.mask = AUDIO_MIXER_VOLUME | AUDIO_MIXER_DIGITAL | AUDIO_MIXER_LINE;
                    break;
                case AUDIO_MIXER_VOLUME:
                    caps->udata.value = icodec->user_replay_volume;
                    break;
                case AUDIO_MIXER_DIGITAL:

                    break;
                case AUDIO_MIXER_LINE:

                    break;
                default:
                    result = -RT_ERROR;
                    break;
            }
            break;
        default:
            result = -RT_ERROR;
            break;
    }

    return result;
}

static rt_err_t icodec_configure	(struct rt_audio_device *audio,struct rt_audio_caps *caps)
{
    rt_err_t result = RT_EOK;
    struct jz_icodec *icodec = (struct jz_icodec *) audio->parent.user_data;
    CODEC_DBG("type = %d\n",caps->main_type);

    switch (caps->main_type)
    {
        case AUDIO_TYPE_MIXER:
            switch (caps->sub_type)
            {
                case AUDIO_MIXER_VOLUME:
                {
                    int volume = caps->udata.value;

                    jz_icodec_set_replay_volume(icodec, volume);
                }
                    break;
                case AUDIO_MIXER_DIGITAL:
                {
                    int gain = caps->udata.value;
                    jz_icodec_set_replay_mixer_volume(icodec, gain);
                }
                    break;
                case AUDIO_MIXER_LINE:
                {
                    int gain = caps->udata.value;

                    //set linein valume...
                }
                    break;
                case AUDIO_MIXER_EXTEND:

                    break;
                default:
                    result = -RT_ERROR;
                    break;
            }
            break;
        case AUDIO_TYPE_OUTPUT:
        {
            switch (caps->sub_type)
            {
                case AUDIO_DSP_PARAM:
                {
                    CODEC_DBG("  AUDIO_TYPE_OUTPUT:\n");CODEC_DBG("    Number of channels: %u\n", caps->udata.config.channels);CODEC_DBG("    Sample rate:        %u\n", caps->udata.config.samplerate);CODEC_DBG("    Sample format:      %u\n", caps->udata.config.samplefmt);

                    //upgrate codec chip
                    icodec->i2s->channels = caps->udata.config.channels;
                    icodec->i2s->rates = caps->udata.config.samplerate;
                    icodec->i2s->fmt_width = rt_audio_format_to_bits(caps->udata.config.samplefmt);

                    aic_i2s_hw_params(icodec->i2s, AUDIO_STREAM_REPLAY);
                    aic_i2s_set_sysclk(icodec->i2s, icodec->i2s->rates);

                    //save config
                    icodec->replay_config.channels = caps->udata.config.channels;
                    icodec->replay_config.samplefmt = caps->udata.config.samplefmt;
                    icodec->replay_config.samplerate = caps->udata.config.samplerate;
                    icodec->replay_config.samplefmts = caps->udata.config.samplefmts;
                    break;
                }
                case AUDIO_DSP_SAMPLERATE:
                {
                    int rate = caps->udata.value;

                    jz_icodec_set_sampling_rate(icodec, rate);
                    break;
                }

                default:
                    result = -RT_ERROR;
                    break;
            }
        }
            break;
        default:
            result = -RT_ERROR;
            break;
    }

    return result;
}

static rt_err_t    icodec_init         (struct rt_audio_device *audio)
{
	struct jz_icodec *icodec = (struct jz_icodec *)audio->parent.user_data;
	uint16_t i;

	/* disable shutdown */
	gpio_set_value(AUDIO_SHUTDOWN_PORT,AUDIO_SHUTDOWN_PIN,AUDIO_SHUTDOWN_MUTE);
	rt_thread_delay(RT_TICK_PER_SECOND / 4);
	gpio_set_value(AUDIO_SHUTDOWN_PORT,AUDIO_SHUTDOWN_PIN,!AUDIO_SHUTDOWN_MUTE);
    rt_thread_delay(RT_TICK_PER_SECOND / 4);

	/* write default value ... */
	for (i = 0; i < sizeof(_g_icodec_reg_defcache); ++i)
	{
		jz_icodec_reg_write(icodec, i, _g_icodec_reg_defcache[i]);
	}

	/* power off codec */
	jz_icodec_reg_update_bits(icodec, SCODA_REG_CR_VIC, SCODA_CR_VIC_SB_SLEEP_MASK, 1);
	jz_icodec_reg_update_bits(icodec, SCODA_REG_CR_VIC, SCODA_CR_VIC_SB_MASK, 1);

	/* codec select enable 24M clock*/
	jz_icodec_reg_update_bits(icodec, SCODA_REG_CR_CK , SCODA_CR_CK_MCLK_DIV_MASK, 1 << SCODA_CR_CK_MCLK_DIV_SHIFT);
	jz_icodec_reg_update_bits(icodec, SCODA_REG_CR_CK , SCODA_CR_CK_SDCLK_MASK, 0 << SCODA_CR_CK_SDCLK_SHIFT);
	jz_icodec_reg_update_bits(icodec, SCODA_REG_CR_CK , SCODA_CR_CRYSTAL_MASK, 0 << SCODA_CR_CRYSTAL_SHIFT);

	/*codec select Dac/Adc i2s interface*/
	jz_icodec_reg_update_bits(icodec, SCODA_REG_AICR_DAC, SCODA_AICR_DAC_SLAVE_MASK, 0);
	jz_icodec_reg_update_bits(icodec, SCODA_REG_AICR_DAC, SCODA_AICR_DAC_AUDIO_MASK, SCODA_AICR_DAC_AUDIOIF_I2S);

	jz_icodec_reg_update_bits(icodec, SCODA_REG_AICR_ADC, SCODA_AICR_ADC_AUDIO_MASK, 0);
	jz_icodec_reg_update_bits(icodec, SCODA_REG_AICR_ADC, SCODA_AICR_ADC_AUDIO_MASK, SCODA_AICR_ADC_AUDIOIF_I2S);

	/*codec generated IRQ is a high level */
	jz_icodec_reg_update_bits(icodec, SCODA_REG_ICR, SCODA_ICR_INT_FORM_MASK, SCODA_ICR_INT_FORM_LOW);

	/*codec irq mask*/
	jz_icodec_reg_write(icodec, SCODA_REG_IMR, SCODA_IMR_COMMON_MASK);
	jz_icodec_reg_write(icodec, SCODA_REG_IMR2, SCODA_IMR2_COMMON_MASK);

	/*codec clear all irq*/
	jz_icodec_reg_write(icodec, SCODA_REG_IFR, SCODA_IMR_COMMON_MASK);
	jz_icodec_reg_write(icodec, SCODA_REG_IFR2, SCODA_IMR2_COMMON_MASK);

	/* PCM Format */
#if (ICODEC_PCM_FORMAT == AUDIO_FMT_PCM_S16_LE)
	jz_icodec_reg_update_bits(icodec, SCODA_REG_AICR_DAC, SCODA_AICR_DAC_ADWL_MASK, (0 << SCODA_AICR_DAC_ADWL_SHIFT));
	jz_icodec_reg_update_bits(icodec, SCODA_REG_AICR_ADC, SCODA_AICR_ADC_ADWL_MASK, (0 << SCODA_AICR_ADC_ADWL_SHIFT));
#endif

	/* sampling rate */
	jz_icodec_set_sampling_rate(icodec,ICODEC_SAMPLING_RATE);

	/*power on codec*/
	jz_icodec_digital_mute(icodec,0);

	if (jz_icodec_reg_update_bits(icodec, SCODA_REG_CR_VIC, SCODA_CR_VIC_SB_MASK, 0))
		rt_thread_delay(rt_tick_from_millisecond(250));
	if (jz_icodec_reg_update_bits(icodec, SCODA_REG_CR_VIC, SCODA_CR_VIC_SB_SLEEP_MASK, 0))
		rt_thread_delay(rt_tick_from_millisecond(400));

	return RT_EOK;
}

static rt_err_t    icodec_shutdown    	(struct rt_audio_device *audio)
{
	struct jz_icodec *icodec = (struct jz_icodec *)audio->parent.user_data;

#ifdef AUDIO_SHUTDOWN_PORT
    gpio_set_value(AUDIO_SHUTDOWN_PORT,AUDIO_SHUTDOWN_PIN,AUDIO_SHUTDOWN_MUTE);
#endif
	return RT_EOK;
}

rt_err_t    icodec_start    	(struct rt_audio_device *audio,int stream)
{
	struct jz_icodec *icodec = (struct jz_icodec *)audio->parent.user_data;

	aic_i2s_trigger(icodec->i2s,I2S_TRIGGER_START,stream);

	return RT_EOK;
}

rt_err_t    icodec_stop    		(struct rt_audio_device *audio,int stream)
{
	struct jz_icodec *icodec = (struct jz_icodec *)audio->parent.user_data;

	aic_i2s_trigger(icodec->i2s,I2S_TRIGGER_STOP,stream);
	return RT_EOK;
}

static rt_err_t    icodec_suspend  	(struct rt_audio_device *audio,int stream)
{
	struct jz_icodec *icodec = (struct jz_icodec *)audio->parent.user_data;

	aic_i2s_trigger(icodec->i2s,I2S_TRIGGER_SUSPEND,stream);
	return RT_EOK;
}

static rt_err_t    icodec_resume       (struct rt_audio_device *audio,int stream)
{
	struct jz_icodec *icodec = (struct jz_icodec *)audio->parent.user_data;

	aic_i2s_trigger(icodec->i2s,I2S_TRIGGER_RESUME,stream);
	return RT_EOK;
}

static rt_err_t icodec_control (struct rt_audio_device *audio, int cmd, void *args)
{
	rt_err_t result = RT_EOK;
	struct jz_icodec *icodec = (struct jz_icodec *)audio->parent.user_data;

	switch (cmd)
	{
	case AUDIO_CTL_HWRESET:

		break;
	case AUDIO_CTL_GETBUFFERINFO:
	{
		struct rt_audio_buf_info *info = (struct rt_audio_buf_info *)args;

		if(info != RT_NULL)
		{
			info->buffer_count = CFG_I2S_DMA_PAGE_NUM;
			info->buffer_size  = CFG_I2S_DMA_PAGE_SIZE;
		}
	}
		break;
	default:
		result = -RT_ERROR;
		break;
	}

	return result;
}

static void  codec_write_complete(void *data, void *pbuf)
{
	struct rt_audio_device *audio = (struct rt_audio_device *)data;

	/* notify transmitted complete. */
	rt_audio_tx_complete(audio,pbuf);
}

static rt_size_t icodec_transmit		(struct rt_audio_device *audio,const void *writeBuf,void *readBuf, rt_size_t size)
{
	struct jz_icodec *icodec = (struct jz_icodec *)audio->parent.user_data;

	CODEC_DBG("writeBuf = %x,readBuf=%x,size=%d\n",(rt_uint32_t)writeBuf,(rt_uint32_t)readBuf,size);

	if(writeBuf != RT_NULL)
	{
	    return aic_i2s_send(icodec->i2s, writeBuf, size, codec_write_complete, (void *)audio);
	}
	return 0;
}


static struct jz_icodec _g_jz_icodec =
{
    .mapped_base        = AIC_BASE + 0xA0,
    .user_replay_volume = 31,
};

static struct rt_audio_device   	_g_audio_device;
const struct rt_audio_ops 			_g_audio_ops =
{
	.getcaps	= icodec_getcaps,
	.configure	= icodec_configure,

	.init       = icodec_init,
	.shutdown   = icodec_shutdown,
	.start		= icodec_start,
	.stop 		= icodec_stop,
	.suspend    = icodec_suspend ,
	.resume     = icodec_resume ,
    .control	= icodec_control,

    .transmit	= icodec_transmit,
};


int rt_hw_codec_init(void)
{
	int result;

	struct rt_audio_device *audio 	= &_g_audio_device;
	struct jz_icodec 	*icodec 	= &_g_jz_icodec;
	struct jz_i2s 		*i2s;

	rt_kprintf("init i2s....\n");
    i2s = rt_hw_aic_i2s_init();
    if(i2s == RT_NULL)
    {
        CODEC_DBG("i2s device not found!\r\n");
        return -RT_EIO;
    }
    icodec->i2s = i2s;

#ifdef AUDIO_DEVICE_USE_PRIVATE_BUFFER
    {
    	rt_uint8_t *mempool = (rt_uint8_t *)rt_malloc(CODEC_MP_SZ);

    	if(mempool == RT_NULL)
    	{
    		CODEC_DBG("no memory...\n");

    		return -RT_ENOMEM;
    	}
    	rt_mp_init(&icodec->mp,"codecbuf",mempool,CODEC_MP_SZ,CODEC_MP_BLOCK_SZ);
    }
#endif /* AUDIO_DEVICE_USE_PRIVATE_BUFFER */

    //init default configuration
	{
		icodec->replay_config.channels 		= 2;
		icodec->replay_config.samplefmt 	= AUDIO_FMT_PCM_S16_LE;
		icodec->replay_config.samplerate 	= 44100;
		icodec->replay_config.samplefmts 	= AUDIO_FMT_PCM_S16_LE;
	}

    audio->ops = (struct rt_audio_ops *)&_g_audio_ops;
    result = rt_audio_register(audio,"sound0",RT_DEVICE_FLAG_WRONLY,icodec);
    if(result != RT_EOK)
    {
    	CODEC_DBG("icodec device register error..\n");

    	return result;
    }

    rt_kprintf("codec initialization done!\n");
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_codec_init);
#endif /* RT_USING_ICODEC */
