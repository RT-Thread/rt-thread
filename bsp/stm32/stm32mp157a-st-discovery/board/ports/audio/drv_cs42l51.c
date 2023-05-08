/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-02     thread-liu   first version
 */

#include "board.h"

#if defined(BSP_USING_AUDIO)
#include <drv_cs42l51.h>

#define DRV_DEBUG
#define LOG_TAG             "drv.audio"
#include <drv_log.h>

/* CS42L51 address */
#define CHIP_ADDRESS 0x4A
/* reset pin, active low */
#define CS42L51_RESET_PIN   GET_PIN(G, 9)

static uint16_t CS42L51_Device             = OUT_HEADPHONE;
static struct rt_i2c_bus_device *audio_dev = RT_NULL;

/* i2c read reg */
static rt_err_t read_reg(struct rt_i2c_bus_device *bus, rt_uint8_t reg, rt_uint8_t len, rt_uint8_t *buf)
{
    struct rt_i2c_msg msg[2] = {0, 0};

    RT_ASSERT(bus != RT_NULL);

    msg[0].addr  = CHIP_ADDRESS;    /* Slave address */
    msg[0].flags = RT_I2C_WR;        /* Write flag */
    msg[0].buf   = &reg;             /* Slave register address */
    msg[0].len   = 1;                /* Number of bytes sent */

    msg[1].addr  = CHIP_ADDRESS;
    msg[1].flags = RT_I2C_RD;
    msg[1].len   = len;
    msg[1].buf   = buf;

    if (rt_i2c_transfer(bus, msg, 2) == 2)
    {
        return RT_EOK;
    }

    return -RT_ERROR;
}

/* i2c write reg */
static rt_err_t write_reg(struct rt_i2c_bus_device *bus, rt_uint8_t reg, rt_uint8_t data)
{
    rt_uint8_t buf[2];
    struct rt_i2c_msg msgs;

    RT_ASSERT(bus != RT_NULL);

    buf[0] = reg;
    buf[1] = data;

    msgs.addr  = CHIP_ADDRESS;
    msgs.flags = RT_I2C_WR;
    msgs.buf   = buf;
    msgs.len   = 2;

    if (rt_i2c_transfer(bus, &msgs, 1) == 1)
    {
        return RT_EOK;
    }

    return -RT_ERROR;
}

/**
  * @brief  deinitializes cs42l51 low level.
  * @retval none
  */
static void cs42l51_lowlevel_deinit(void)
{
    rt_uint8_t temp = 0;

    /* Mute DAC and ADC */
    read_reg(audio_dev, CS42L51_DAC_OUT_CTL, 1, &temp);
    write_reg(audio_dev, CS42L51_DAC_OUT_CTL, (temp | 0x03));
    read_reg(audio_dev, CS42L51_ADC_INPUT, 1, &temp);
    write_reg(audio_dev, CS42L51_ADC_INPUT, (temp | 0x03));

    /* Disable soft ramp and zero cross */
    read_reg(audio_dev, CS42L51_ADC_CTL, 1, &temp);
    write_reg(audio_dev, CS42L51_ADC_CTL, (temp & 0xF0));

    /* Set PDN to 1 */
    read_reg(audio_dev, CS42L51_POWER_CTL1, 1, &temp);
    write_reg(audio_dev, CS42L51_POWER_CTL1, (temp | 0x01));

    /* Set all power down bits to 1 */
    write_reg(audio_dev, CS42L51_POWER_CTL1, 0x7F);
    read_reg(audio_dev, CS42L51_MIC_POWER_CTL, 1, &temp);
    write_reg(audio_dev, CS42L51_MIC_POWER_CTL, (temp | 0x0E));

    /* Power off the codec */
    rt_pin_write(CS42L51_RESET_PIN, PIN_LOW);
}

/**
  * @brief  initializes cs42l51 low level.
  * @retval none
  */
static void cs42l51_lowlevel_init(void)
{
    rt_uint8_t temp = 0;

    /* Initialized RESET IO */
    rt_pin_mode(CS42L51_RESET_PIN, PIN_MODE_OUTPUT);

    /* Power off the cs42l51 */
    rt_pin_write(CS42L51_RESET_PIN, PIN_LOW);

    /* wait until power supplies are stable */
    rt_thread_mdelay(10);

    /* Power on the cs42l51 */
    rt_pin_write(CS42L51_RESET_PIN, PIN_HIGH);

    /* Wait at least 500ns after reset */
    rt_thread_mdelay(1);

    /* Set the device in standby mode */
    read_reg(audio_dev, CS42L51_POWER_CTL1, 1, &temp);
    write_reg(audio_dev, CS42L51_POWER_CTL1, (temp | 0x01));

    /* Set all power down bits to 1 */
    write_reg(audio_dev, CS42L51_POWER_CTL1, 0x7F);
    read_reg(audio_dev, CS42L51_MIC_POWER_CTL, 1, &temp);
    write_reg(audio_dev, CS42L51_MIC_POWER_CTL, (temp | 0x0E));
}

/**
  * @brief Initializes CS42L51.
  * @param Device:     Audio type.
  * @param bus_name    I2C device name.
  * @param volume:     Initial output volume level (from 0 (-100dB) to 100 (0dB)).
  * @retval 0 if correct communication, else wrong communication
  */
static rt_err_t cs42l51_init(uint16_t device, const char *bus_name, uint8_t volume)
{
    static uint8_t init_flag  = 0;
    rt_uint8_t temp = 0;
    rt_uint8_t value = 0;

    /* check if codec is already initialized */
    if (init_flag == 0)
    {
        audio_dev = rt_i2c_bus_device_find(bus_name);

        if (audio_dev == RT_NULL)
        {
            LOG_E("%s bus not found\n", bus_name);
            return -RT_ERROR;
        }
        /* hard reset cs42l51 */
        cs42l51_drv.reset();
        /* Wait at least 500ns after reset */
        rt_thread_mdelay(1);
        /* Set the device in standby mode */
        read_reg(audio_dev, CS42L51_POWER_CTL1, 1, &temp);
        write_reg(audio_dev, CS42L51_POWER_CTL1, (temp | 0x01));
        /* Set all power down bits to 1 */
        write_reg(audio_dev, CS42L51_POWER_CTL1, 0x7F);
        read_reg(audio_dev, CS42L51_MIC_POWER_CTL, 1, &temp);
        write_reg(audio_dev, CS42L51_MIC_POWER_CTL, (temp | 0x0E));

        init_flag = 1;
    }
    else
    {
        /* Set all power down bits to 1 exept PDN to mute ADCs and DACs*/
        write_reg(audio_dev, CS42L51_POWER_CTL1, 0x7E);
        read_reg(audio_dev, CS42L51_MIC_POWER_CTL, 1, &temp);
        write_reg(audio_dev, CS42L51_MIC_POWER_CTL, (temp | 0x0E));
        /* Disable zero cross and soft ramp */
        read_reg(audio_dev, CS42L51_DAC_CTL, 1, &temp);
        write_reg(audio_dev, CS42L51_DAC_CTL, (temp & 0xFC));

        /* Power control : Enter standby (PDN = 1) */
        read_reg(audio_dev, CS42L51_POWER_CTL1, 1, &temp);
        write_reg(audio_dev, CS42L51_POWER_CTL1, (temp | 0x01));
    }
    /* Mic Power and Speed Control : Auto detect on, Speed mode SSM, tri state off, MCLK divide by 2 off */
    read_reg(audio_dev, CS42L51_MIC_POWER_CTL, 1, &temp);
    write_reg(audio_dev, CS42L51_MIC_POWER_CTL, ((temp & 0x0E) | 0xA0));
    /* Interface control : Loopback off, Slave, I2S (SDIN and SOUT), Digital mix off, Mic mix off */
    write_reg(audio_dev, CS42L51_INTF_CTL, 0x0C);
    /* Mic control : ADC single volume off, ADCB boost off, ADCA boost off, MicBias on AIN3B/MICIN2 pin, MicBias level 0.8xVA, MICB boost 16db, MICA boost 16dB */
    write_reg(audio_dev, CS42L51_MIC_CTL, 0x00);
    /* ADC control : ADCB HPF off, ADCB HPF freeze off, ADCA HPF off, ADCA HPF freeze off, Soft ramp B off, Zero cross B off, Soft ramp A off, Zero cross A off */
    write_reg(audio_dev, CS42L51_ADC_CTL, 0x00);
    /* ADC Input Select, Invert and Mute : AIN1B to PGAB, AIN3A to PreAmp to PGAA, ADCB invert off, ADCA invert off, ADCB mute on, ADCA mute off */
    write_reg(audio_dev, CS42L51_ADC_INPUT, 0x32);
    /* DAC output control : HP Gain to 1, Single volume control off, PCM invert signals polarity off, DAC channels mute on */
    write_reg(audio_dev, CS42L51_DAC_OUT_CTL, 0xC3);
    /* DAC control : Signal processing to DAC, Freeze off, De-emphasis off, Analog output auto mute off, DAC soft ramp */
    write_reg(audio_dev, CS42L51_DAC_CTL, 0x42);
    /* ALCA and PGAA Control : ALCA soft ramp disable on, ALCA zero cross disable on, PGA A Gain 0dB */
    write_reg(audio_dev, CS42L51_ALC_PGA_CTL, 0xC0);
    /* ALCB and PGAB Control : ALCB soft ramp disable on, ALCB zero cross disable on, PGA B Gain 0dB */
    write_reg(audio_dev, CS42L51_ALC_PGB_CTL, 0xC0);
    /* ADCA Attenuator : 0dB */
    write_reg(audio_dev, CS42L51_ADCA_ATT, 0x00);
    /* ADCB Attenuator : 0dB */
    write_reg(audio_dev, CS42L51_ADCB_ATT, 0x00);
    /* ADCA mixer volume control : ADCA mixer channel mute on, ADCA mixer volume 0dB */
    write_reg(audio_dev, CS42L51_ADCA_VOL, 0x80);
    /* ADCB mixer volume control : ADCB mixer channel mute on, ADCB mixer volume 0dB */
    write_reg(audio_dev, CS42L51_ADCB_VOL, 0x80);
    /* PCMA mixer volume control : PCMA mixer channel mute off, PCMA mixer volume 0dB */
    write_reg(audio_dev, CS42L51_PCMA_VOL, 0x00);
    /* PCMB mixer volume control : PCMB mixer channel mute off, PCMB mixer volume 0dB */
    write_reg(audio_dev, CS42L51_PCMB_VOL, 0x00);
    /* PCM channel mixer : AOUTA Left, AOUTB Right */
    write_reg(audio_dev, CS42L51_PCM_MIXER, 0x00);

    if(device & OUT_HEADPHONE)
    {
        value = VOLUME_CONVERT(volume);
        /* AOUTA volume control : AOUTA volume */
        write_reg(audio_dev, CS42L51_AOUTA_VOL, value);
        /* AOUTB volume control : AOUTB volume */
        write_reg(audio_dev, CS42L51_AOUTB_VOL, value);
    }

    CS42L51_Device = device;

    return RT_EOK;
}

/**
  * @brief  Deinitialize the audio codec.
  * @param  None
  * @retval  None
  */
static void cs42l51_deinit(void)
{
    /* Deinitialize Audio Codec interface */
    rt_uint8_t temp = 0;

    /* Mute DAC and ADC */
    read_reg(audio_dev, CS42L51_DAC_OUT_CTL, 1, &temp);
    write_reg(audio_dev, CS42L51_DAC_OUT_CTL, (temp | 0x03));
    read_reg(audio_dev, CS42L51_ADC_INPUT, 1, &temp);
    write_reg(audio_dev, CS42L51_ADC_INPUT, (temp | 0x03));

    /* Disable soft ramp and zero cross */
    read_reg(audio_dev, CS42L51_ADC_CTL, 1, &temp);
    write_reg(audio_dev, CS42L51_ADC_CTL, (temp & 0xF0));

    /* Set PDN to 1 */
    read_reg(audio_dev, CS42L51_POWER_CTL1, 1, &temp);
    write_reg(audio_dev, CS42L51_POWER_CTL1, (temp | 0x01));

    /* Set all power down bits to 1 */
    write_reg(audio_dev, CS42L51_POWER_CTL1, 0x7F);
    read_reg(audio_dev, CS42L51_MIC_POWER_CTL, 1, &temp);
    write_reg(audio_dev, CS42L51_MIC_POWER_CTL, (temp | 0x0E));

    /* Power off CS42L51*/
    rt_pin_write(CS42L51_RESET_PIN, PIN_LOW);
}

/**
  * @brief Verify that we have a CS42L51.
  * @retval 0 if correct communication, else wrong communication
  */

static uint32_t cs42l51_read_id(void)
{
    uint8_t temp;

    /* read cs42l51 id */
    read_reg(audio_dev, CS42L51_CHIP_REV_ID, 1, &temp);

    if ((temp != CS42L51_MK_CHIP_REV(CS42L51_CHIP_ID, CS42L51_CHIP_REV_A)) &&
        (temp != CS42L51_MK_CHIP_REV(CS42L51_CHIP_ID, CS42L51_CHIP_REV_B)))
    {
      LOG_E("device id : 0x%02x", temp);
        return -RT_ERROR;
    }

    LOG_D("device id : 0x%02x", temp);

    return RT_EOK;
}

/**
  * @brief Start the audio Codec play feature.
  * @note For this codec no Play options are required.
  * @retval 0 if correct communication, else wrong communication
  */
static uint32_t cs42l51_play(void)
{
    rt_uint8_t temp = 0;

    switch (CS42L51_Device)
    {
    case OUT_HEADPHONE:
        {
        /* Unmute the output first */
        cs42l51_drv.set_mute(AUDIO_MUTE_OFF);
        /* DAC control : Signal processing to DAC, Freeze off, De-emphasis off, Analog output auto mute off, DAC soft ramp */
        write_reg(audio_dev, CS42L51_DAC_CTL, 0x42);
        /* Power control 1 : PDN_DACA, PDN_DACB disable. */
        read_reg(audio_dev, CS42L51_POWER_CTL1, 1, &temp);
        write_reg(audio_dev, CS42L51_POWER_CTL1, (temp & 0x9F));
        break;
        }

    case IN_LINE1:
        {
        /* ADC Input Select, Invert and Mute : AIN1B to PGAB, AIN1A to PGAA, ADCB invert off, ADCA invert off, ADCB mute off, ADCA mute off */
        write_reg(audio_dev, CS42L51_ADC_INPUT, 0x00);
        /* Power control 1 : PDN_PGAA, PDN_PGAA, PDN_ADCB, PDN_ADCA disable. */
        read_reg(audio_dev, CS42L51_POWER_CTL1, 1, &temp);
        write_reg(audio_dev, CS42L51_POWER_CTL1, (temp & 0x9F));
        break;
        }

    case IN_MIC1:
        {
        /* ADC Input Select, Invert and Mute : AIN1B to PGAB, AIN3A to PreAmp to PGAA, ADCB invert off, ADCA invert off, ADCB mute on, ADCA mute off */
        write_reg(audio_dev, CS42L51_ADC_INPUT, 0x32);
        /* Power control 1 : PDN_PGAA, PDN_ADCA disable. */
        read_reg(audio_dev, CS42L51_POWER_CTL1, 1, &temp);
        write_reg(audio_dev, CS42L51_POWER_CTL1, (temp & 0xF5));
        /* Mic Power and Speed Control : PDN_MICA, PDN_MIC_BIAS disable. */
        read_reg(audio_dev, CS42L51_MIC_POWER_CTL, 1, &temp);
        write_reg(audio_dev, CS42L51_MIC_POWER_CTL,(temp & 0xF9));
        break;
        }

    case IN_MIC2:
        {
         /* Power control 1 : PDN_PGAB, PDN_ADCB disable. */
         read_reg(audio_dev, CS42L51_POWER_CTL1, 1, &temp);
         write_reg(audio_dev, CS42L51_POWER_CTL1, (temp & 0xEB));
         /* Mic Power and Speed Control : PDN_MICB, PDN_MIC_BIAS disable. */
         read_reg(audio_dev, CS42L51_MIC_POWER_CTL, 1, &temp);
         write_reg(audio_dev, CS42L51_MIC_POWER_CTL,(temp & 0xF5));
         break;
        }

    default:
        LOG_D("error audio play mode!");
        break;
    }

    /* Power control : Exit standby (PDN = 0) */
    read_reg(audio_dev, CS42L51_POWER_CTL1, 1, &temp);
    write_reg(audio_dev, CS42L51_POWER_CTL1, (temp & 0xFE));

    return RT_EOK;
}

/**
  * @brief Pause playing on the audio codec.
  * @param audio_dev: Device address on communication Bus.
  * @retval 0 if correct communication, else wrong communication
  */
static uint32_t cs42l51_pause(void)
{

  /* Pause the audio file playing */
  /* Mute the output first */
  return cs42l51_drv.set_mute(AUDIO_MUTE_ON);

}

/**
  * @brief Resume playing on the audio codec.
  * @param audio_dev: Device address on communication Bus.
  * @retval 0 if correct communication, else wrong communication
  */
static uint32_t cs42l51_resume(void)
{
  /* Unmute the output  */
  return cs42l51_drv.set_mute(AUDIO_MUTE_OFF);
}

/**
  * @brief Stop audio Codec playing. It powers down the codec.
  * @retval 0 if correct communication, else wrong communication
  */
static uint32_t cs42l51_stop(void)
{
    rt_uint8_t temp = 0;

    /* Set all power down bits to 1 exept PDN to mute ADCs and DACs*/
    write_reg(audio_dev, 0x02, 0x7E);
    read_reg(audio_dev, 0x03, 1, &temp);
    write_reg(audio_dev, 0x03, (temp | 0x0E));

    /* Disable zero cross and soft ramp */
    read_reg(audio_dev, 0x09, 1, &temp);
    write_reg(audio_dev, 0x09, (temp & 0xFC));

    /* Power control : Enter standby (PDN = 1) */
    read_reg(audio_dev, 0x02, 1, &temp);
    write_reg(audio_dev, 0x02, (temp | 0x01));

    return RT_EOK;
}

/**
  * @brief Set new frequency.
  * @param AudioFreq: Audio frequency used to play the audio stream.
  * @retval 0 if correct communication, else wrong communication
  */
static uint32_t cs42l51_set_frequency(uint32_t AudioFreq)
{
    return RT_EOK;
}

/**
  * @brief Set higher or lower the codec volume level.
  * @param Volume: output volume level (from 0 (-100dB) to 100 (0dB)).
  * @retval 0 if correct communication, else wrong communication
  */
static uint32_t cs42l51_set_volume(uint8_t Volume)
{
    uint8_t  convertedvol = VOLUME_CONVERT(Volume);

    /* AOUTA volume control : AOUTA volume */
    write_reg(audio_dev, CS42L51_AOUTA_VOL, convertedvol);
    /* AOUTB volume control : AOUTB volume */
    write_reg(audio_dev, CS42L51_AOUTB_VOL, convertedvol);

    return RT_EOK;
}

/**
  * @brief get higher or lower the codec volume level.
  * @retval value if correct communication
  */
static uint32_t cs42l51_get_volume(void)
{
    rt_uint8_t temp = 0;

    /* AOUTA volume control : AOUTA volume */
    read_reg(audio_dev, CS42L51_AOUTA_VOL, 1, &temp);

    temp = VOLUME_INVERT(temp);

    return temp;
}

/**
* @brief Enable or disable the mute feature on the audio codec.
* @param Cmd: AUDIO_MUTE_ON to enable the mute or AUDIO_MUTE_OFF to disable the
*             mute mode.
* @retval 0 if correct communication, else wrong communication
*/
static uint32_t cs42l51_set_mute(uint32_t cmd)
{
    rt_uint8_t temp = 0;

    /* Read DAC output control register */
    read_reg(audio_dev, 0x08, 1, &temp);

    /* Set the Mute mode */
    if(cmd == AUDIO_MUTE_ON)
    {
        /* Mute DAC channels */
        write_reg(audio_dev, CS42L51_DAC_OUT_CTL, (temp | 0x03));
    }
    else /* AUDIO_MUTE_OFF Disable the Mute */
    {
        /* Unmute DAC channels */
        write_reg(audio_dev, CS42L51_DAC_OUT_CTL, (temp & 0xFC));
    }

    return RT_EOK;
}

/**
  * @brief Switch dynamically (while audio file is played) the output target
  *         (speaker, headphone, etc).
  * @note This function is currently not used (only headphone output device).
  * @param Output: specifies the audio output device target.
  * @retval 0 if correct communication, else wrong communication
  */
static uint32_t cs42l51_set_output_mode(uint8_t Output)
{
    return RT_EOK;
}

/**
  * @brief Reset CS42L51 registers.
  * @retval 0 if correct communication, else wrong communication
  */
static uint32_t cs42l51_reset(void)
{
    cs42l51_lowlevel_deinit();

    cs42l51_lowlevel_init();

    return RT_EOK;
}

/* Audio codec driver structure initialization */
AUDIO_DrvTypeDef cs42l51_drv =
{
  cs42l51_init,
  cs42l51_deinit,
  cs42l51_read_id,

  cs42l51_play,
  cs42l51_pause,
  cs42l51_resume,
  cs42l51_stop,

  cs42l51_set_frequency,
  cs42l51_set_volume,
  cs42l51_get_volume,
  cs42l51_set_mute,
  cs42l51_set_output_mode,
  cs42l51_reset,
};

#endif
