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
#include <drv_wm8994.h>

#define DRV_DEBUG
#define LOG_TAG     "drv.wm8994"
#include <drv_log.h>

#define CHIP_ADDRESS    0x1B     /* wm8994 address */
#define I2C_NAME       "i2c2"

struct wm8994_dev
{
    struct rt_device dev;
    struct rt_i2c_bus_device *i2c_bus;
    rt_uint16_t id;
    rt_uint16_t type;
};
static struct wm8994_dev rt_wm8994 = {0};

/* i2c read reg */
static rt_err_t read_reg(struct rt_i2c_bus_device *bus, rt_uint16_t reg, rt_uint8_t len, rt_uint8_t *buf)
{
    struct rt_i2c_msg msg[2] = {0, 0};
    static rt_uint8_t i2c_reg[2] = {0, 0};

    RT_ASSERT(bus != RT_NULL);

    i2c_reg[0] = ((uint16_t)(reg >> 8) & 0xFF);
    i2c_reg[1] = ((uint16_t)(reg) & 0xFF);

    msg[0].addr  = CHIP_ADDRESS;
    msg[0].flags = RT_I2C_WR;
    msg[0].buf   = i2c_reg;
    msg[0].len   = 2;

    msg[1].addr  = CHIP_ADDRESS;
    msg[1].flags = RT_I2C_RD;
    msg[1].len   = len;
    msg[1].buf   = buf;

    if (rt_i2c_transfer(bus, msg, 2) == 2)
    {
        return RT_EOK;
    }

    return RT_ERROR;
}

/* i2c write reg */
static rt_err_t write_reg(struct rt_i2c_bus_device *bus, rt_uint16_t reg, rt_uint16_t data)
{
    rt_uint8_t buf[4];
    struct rt_i2c_msg msgs;

    RT_ASSERT(bus != RT_NULL);

    buf[0] = ((uint16_t)(reg >> 8) & 0xFF);
    buf[1] = ((uint16_t)(reg) & 0xFF);

    buf[2] = ((uint16_t)(data >> 8) & 0xFF);
    buf[3] = ((uint16_t)(data) & 0xFF);

    msgs.addr  = CHIP_ADDRESS;
    msgs.flags = RT_I2C_WR;
    msgs.buf   = buf;
    msgs.len   = 4;

    if (rt_i2c_transfer(bus, &msgs, 1) == 1)
    {
        return RT_EOK;
    }

    return RT_ERROR;
}

static rt_err_t wm8994_set_output_mode(struct rt_i2c_bus_device *bus, rt_uint16_t mode)
{
    switch (mode & 0x000F)
    {
    case OUTPUT_DEVICE_SPEAKER:
        /* Enable DAC1 (Left), Enable DAC1 (Right),
         * Disable DAC2 (Left), Disable DAC2 (Right) */
        write_reg(bus, 0x0005, 0x0C0C);

        /* Enable the AIF1 Timeslot 0 (Left) to DAC 1 (Left) mixer path */
        write_reg(bus, 0x0601, 0x0000);

        /* Enable the AIF1 Timeslot 0 (Right) to DAC 1 (Right) mixer path */
        write_reg(bus, 0x0602, 0x0000);

        /* Disable the AIF1 Timeslot 1 (Left) to DAC 2 (Left) mixer path */
        write_reg(bus, 0x0604, 0x0002);

        /* Disable the AIF1 Timeslot 1 (Right) to DAC 2 (Right) mixer path */
        write_reg(bus, 0x0605, 0x0002);
        break;

    case OUTPUT_DEVICE_HEADPHONE:
        /* Disable DAC1 (Left), Disable DAC1 (Right),
        Enable DAC2 (Left), Enable DAC2 (Right)*/
        write_reg(bus, 0x05, 0x0303);

        /* Enable the AIF1 Timeslot 0 (Left) to DAC 1 (Left) mixer path */
        write_reg(bus, 0x0601, 0x01);

        /* Enable the AIF1 Timeslot 0 (Right) to DAC 1 (Right) mixer path */
        write_reg(bus, 0x0602, 0x01);

        /* Disable the AIF1 Timeslot 1 (Left) to DAC 2 (Left) mixer path */
        write_reg(bus, 0x0604, 0x00);

        /* Disable the AIF1 Timeslot 1 (Right) to DAC 2 (Right) mixer path */
        write_reg(bus, 0x0605, 0x00);
        break;

    case OUTPUT_DEVICE_BOTH:
    default:
        break;
    }

    return RT_EOK;
}

static rt_err_t wm8994_set_input_mode(struct rt_i2c_bus_device *bus, rt_uint16_t mode)
{
    switch (mode & 0x01F0)
    {
    case INPUT_DEVICE_DIGITAL_MICROPHONE_2:
       /* Enable AIF1ADC2 (Left), Enable AIF1ADC2 (Right)
        * Enable DMICDAT2 (Left), Enable DMICDAT2 (Right)
        * Enable Left ADC, Enable Right ADC */
        write_reg(bus, 0x04, 0x0C30);

        /* Enable AIF1 DRC2 Signal Detect & DRC in AIF1ADC2 Left/Right Timeslot 1 */
        write_reg(bus, 0x0450, 0x00DB);

        /* Disable IN1L, IN1R, IN2L, IN2R, Enable Thermal sensor & shutdown */
        write_reg(bus, 0x02, 0x6000);

        /* Enable the DMIC2(Left) to AIF1 Timeslot 1 (Left) mixer path */
        write_reg(bus, 0x0608, 0x0002);

        /* Enable the DMIC2(Right) to AIF1 Timeslot 1 (Right) mixer path */
        write_reg(bus, 0x0609, 0x0002);

        /* GPIO1 pin configuration GP1_DIR = output, GP1_FN = AIF1 DRC2 signal detect */
        write_reg(bus, 0x0700, 0x000E);
        break;

    case INPUT_DEVICE_INPUT_LINE_1:
        /* IN1LN_TO_IN1L, IN1LP_TO_VMID, IN1RN_TO_IN1R, IN1RP_TO_VMID */
        write_reg(bus, 0x28, 0x0011);

        /* Disable mute on IN1L_TO_MIXINL and +30dB on IN1L PGA output */
        write_reg(bus, 0x29, 0x0035);

        /* Disable mute on IN1R_TO_MIXINL, Gain = +30dB */
        write_reg(bus, 0x2A, 0x0035);

        /* Enable AIF1ADC1 (Left), Enable AIF1ADC1 (Right)
         * Enable Left ADC, Enable Right ADC */
        write_reg(bus, 0x04, 0x0303);

        /* Enable AIF1 DRC1 Signal Detect & DRC in AIF1ADC1 Left/Right Timeslot 0 */
        write_reg(bus, 0x0440, 0x00DB);

        /* Enable IN1L and IN1R, Disable IN2L and IN2R, Enable Thermal sensor & shutdown */
        write_reg(bus, 0x02, 0x6350);

        /* Enable the ADCL(Left) to AIF1 Timeslot 0 (Left) mixer path */
        write_reg(bus, 0x0606, 0x0002);

        /* Enable the ADCR(Right) to AIF1 Timeslot 0 (Right) mixer path */
        write_reg(bus, 0x0607, 0x0002);

        /* GPIO1 pin configuration GP1_DIR = output, GP1_FN = AIF1 DRC1 signal detect */
        write_reg(bus, 0x0700, 0x000D);
        break;

    case INPUT_DEVICE_DIGITAL_MICROPHONE_1:
       /* Enable AIF1ADC1 (Left), Enable AIF1ADC1 (Right)
        * Enable DMICDAT1 (Left), Enable DMICDAT1 (Right)
        * Enable Left ADC, Enable Right ADC */
        write_reg(bus, 0x04, 0x030C);

        /* Enable AIF1 DRC2 Signal Detect & DRC in AIF1ADC1 Left/Right Timeslot 0 */
        write_reg(bus, 0x0440, 0x00DB);

        /* Disable IN1L, IN1R, IN2L, IN2R, Enable Thermal sensor & shutdown */
        write_reg(bus, 0x02, 0x6350);

        /* Enable the DMIC2(Left) to AIF1 Timeslot 0 (Left) mixer path */
        write_reg(bus, 0x0606, 0x0002);

        /* Enable the DMIC2(Right) to AIF1 Timeslot 0 (Right) mixer path */
        write_reg(bus, 0x0607, 0x0002);

        /* GPIO1 pin configuration GP1_DIR = output, GP1_FN = AIF1 DRC1 signal detect */
        write_reg(bus, 0x0700, 0x000D);
        break;

    case INPUT_DEVICE_DIGITAL_MIC1_MIC2:
       /* Enable AIF1ADC1 (Left), Enable AIF1ADC1 (Right)
        * Enable DMICDAT1 (Left), Enable DMICDAT1 (Right)
        * Enable Left ADC, Enable Right ADC */
        write_reg(bus, 0x04, 0x0F3C);

        /* Enable AIF1 DRC2 Signal Detect & DRC in AIF1ADC2 Left/Right Timeslot 1 */
        write_reg(bus, 0x0450, 0x00DB);

        /* Enable AIF1 DRC2 Signal Detect & DRC in AIF1ADC1 Left/Right Timeslot 0 */
        write_reg(bus, 0x0440, 0x00DB);

        /* Disable IN1L, IN1R, Enable IN2L, IN2R, Thermal sensor & shutdown */
        write_reg(bus, 0x02, 0x63A0);

        /* Enable the DMIC2(Left) to AIF1 Timeslot 0 (Left) mixer path */
        write_reg(bus, 0x0606, 0x0002);

        /* Enable the DMIC2(Right) to AIF1 Timeslot 0 (Right) mixer path */
        write_reg(bus, 0x0607, 0x0002);

        /* Enable the DMIC2(Left) to AIF1 Timeslot 1 (Left) mixer path */
        write_reg(bus, 0x0608, 0x0002);

        /* Enable the DMIC2(Right) to AIF1 Timeslot 1 (Right) mixer path */
        write_reg(bus, 0x0609, 0x0002);

        /* GPIO1 pin configuration GP1_DIR = output, GP1_FN = AIF1 DRC1 signal detect */
        write_reg(bus, 0x0700, 0x000D);
        break;

    case INPUT_DEVICE_INPUT_LINE_2:
    default:
        /* Actually, no other input devices supported */
        break;
    }

    return RT_EOK;
}

static rt_err_t _wm8994_init(struct wm8994_dev *dev)
{
    RT_ASSERT(dev != RT_NULL);

    /* wm8994 Errata Work-Arounds */
    write_reg(dev->i2c_bus, 0x0102, 0x0003);
    write_reg(dev->i2c_bus, 0x0817, 0x0000);
    write_reg(dev->i2c_bus, 0x0102, 0x0000);

    /* Enable VMID soft start (fast), Start-up Bias Current Enabled */
    write_reg(dev->i2c_bus, 0x0039, 0x006C);

    /* Enable bias generator, Enable VMID */
    if ((dev->type & 0x01F0) != 0)
    {
        /* audio input */
        write_reg(dev->i2c_bus, 0x0001, 0x0013);
    }
    else
    {
        /* audio output */
        write_reg(dev->i2c_bus, 0x0001, 0x0003);
    }
    rt_thread_mdelay(50);

    if ((dev->type & 0x000F) != 0 )
    {
        /* Path Configurations for output */
        wm8994_set_output_mode(dev->i2c_bus, dev->type);
    }
    if ((dev->type & 0x01F0) != 0 )
    {
        /* Path Configurations for input */
        wm8994_set_input_mode(dev->i2c_bus, dev->type);
    }

    if (dev->type & INPUT_DEVICE_DIGITAL_MIC1_MIC2)
    {
        /* AIF1 Word Length = 16-bits, AIF1 Format = DSP mode */
        write_reg(dev->i2c_bus, 0x0300, 0x4018);
    }
    else
    {
        /* AIF1 Word Length = 16-bits, AIF1 Format = I2S (Default Register Value) */
        write_reg(dev->i2c_bus, 0x0300, 0x4010);
    }

    /* slave mode */
    write_reg(dev->i2c_bus, 0x0302, 0x0000);

    /* Enable the DSP processing clock for AIF1, Enable the core clock */
    write_reg(dev->i2c_bus, 0x0208, 0x000A);

    /* Enable AIF1 Clock, AIF1 Clock Source = MCLK1 pin */
    write_reg(dev->i2c_bus, 0x0200, 0x0001);

    /* Audio output selected */
    if ((dev->type & 0x000F) != 0 )
    {
        if (dev->type & OUTPUT_DEVICE_HEADPHONE)
        {
            /* Select DAC1 (Left) to Left Headphone Output PGA (HPOUT1LVOL) path */
            write_reg(dev->i2c_bus, 0x2D, 0x0100);

            /* Select DAC1 (Right) to Right Headphone Output PGA (HPOUT1RVOL) path */
            write_reg(dev->i2c_bus, 0x2E, 0x0100);

            /* Startup sequence for Headphone */
            write_reg(dev->i2c_bus, 0x0110, 0x8100);

            rt_thread_mdelay(300);

            /* Soft un-Mute the AIF1 Timeslot 0 DAC1 path L&R */
            write_reg(dev->i2c_bus, 0x0420, 0x0000);
        }

        /* Enable SPKRVOL PGA, Enable SPKMIXR, Enable SPKLVOL PGA, Enable SPKMIXL */
        write_reg(dev->i2c_bus, 0x03, 0x0300);

        /* Left Speaker Mixer Volume = 0dB */
        write_reg(dev->i2c_bus, 0x22, 0x0000);

        /* Speaker output mode = Class D, Right Speaker Mixer Volume = 0dB ((0x23, 0x0100) = class AB)*/
        write_reg(dev->i2c_bus, 0x23, 0x0000);

        /* Unmute DAC2 (Left) to Left Speaker Mixer (SPKMIXL) path,
        Unmute DAC2 (Right) to Right Speaker Mixer (SPKMIXR) path */
        write_reg(dev->i2c_bus, 0x36, 0x0300);

        /* Enable bias generator, Enable VMID, Enable SPKOUTL, Enable SPKOUTR */
        write_reg(dev->i2c_bus, 0x01, 0x3003);

        /* Headphone/Speaker Enable */

        if (dev->type & INPUT_DEVICE_DIGITAL_MIC1_MIC2)
        {
            /* Enable Class W, Class W Envelope Tracking = AIF1 Timeslots 0 and 1 */
            write_reg(dev->i2c_bus, 0x51, 0x0205);
        }
        else
        {
            /* Enable Class W, Class W Envelope Tracking = AIF1 Timeslot 0 */
            write_reg(dev->i2c_bus, 0x51, 0x0005);
        }

        /* Enable bias generator, Enable VMID, Enable HPOUT1 (Left) and Enable HPOUT1 (Right) input stages */
        /* idem for Speaker */
        write_reg(dev->i2c_bus, 0x01, 0x3303);

        /* Enable HPOUT1 (Left) and HPOUT1 (Right) intermediate stages */
        write_reg(dev->i2c_bus, 0x60, 0x0022);

        /* Enable Charge Pump */
        write_reg(dev->i2c_bus, 0x4C, 0x9F25);

        /* Add Delay */
        rt_thread_mdelay(15);

        /* Select DAC1 (Left) to Left Headphone Output PGA (HPOUT1LVOL) path */
        write_reg(dev->i2c_bus, 0x2D, 0x0001);

        /* Select DAC1 (Right) to Right Headphone Output PGA (HPOUT1RVOL) path */
        write_reg(dev->i2c_bus, 0x2E, 0x0001);

        /* Enable Left Output Mixer (MIXOUTL), Enable Right Output Mixer (MIXOUTR) */
        /* idem for SPKOUTL and SPKOUTR */
        write_reg(dev->i2c_bus, 0x03, 0x0330);

        /* Enable DC Servo and trigger start-up mode on left and right channels */
        write_reg(dev->i2c_bus, 0x54, 0x0033);

        /* Add Delay */
        rt_thread_mdelay(200);

        /* Enable HPOUT1 (Left) and HPOUT1 (Right) intermediate and output stages. Remove clamps */
        write_reg(dev->i2c_bus, 0x60, 0x00EE);

        /* Unmute DAC 1 (Left) */
        write_reg(dev->i2c_bus, 0x0610, 0x00C0);

        /* Unmute DAC 1 (Right) */
        write_reg(dev->i2c_bus, 0x0611, 0x00C0);

        /* Unmute the AIF1 Timeslot 0 DAC path */
        write_reg(dev->i2c_bus, 0x0420, 0x0000);

        /* Unmute DAC 2 (Left) */
        write_reg(dev->i2c_bus, 0x0612, 0x00C0);

        /* Unmute DAC 2 (Right) */
        write_reg(dev->i2c_bus, 0x0613, 0x00C0);

        /* Unmute the AIF1 Timeslot 1 DAC2 path */
        write_reg(dev->i2c_bus, 0x0422, 0x0000);

    }

    /* Audio input selected */
    if ((dev->type & 0x01F0) != 0 )
    {
        if ((dev->type & INPUT_DEVICE_DIGITAL_MICROPHONE_1) || (dev->type & INPUT_DEVICE_DIGITAL_MICROPHONE_2))
        {
            /* Enable Microphone bias 1 generator, Enable VMID */
            write_reg(dev->i2c_bus, 0x01, 0x0013);

            /* ADC oversample enable */
            write_reg(dev->i2c_bus, 0x0620, 0x0002);

            /* AIF ADC2 HPF enable, HPF cut = voice mode 1 fc=127Hz at fs=8kHz */
            write_reg(dev->i2c_bus, 0x0411, 0x3800);
        }
        else if (dev->type & INPUT_DEVICE_DIGITAL_MIC1_MIC2)
        {
            /* Enable Microphone bias 1 generator, Enable VMID */
            write_reg(dev->i2c_bus, 0x01, 0x0013);

            /* ADC oversample enable */
            write_reg(dev->i2c_bus, 0x0620, 0x0002);

            /* AIF ADC1 HPF enable, HPF cut = voice mode 1 fc=127Hz at fs=8kHz */
            write_reg(dev->i2c_bus, 0x0410, 0x1800);

            /* AIF ADC2 HPF enable, HPF cut = voice mode 1 fc=127Hz at fs=8kHz */
            write_reg(dev->i2c_bus, 0x0411, 0x1800);
        }
        else if ((dev->type & INPUT_DEVICE_INPUT_LINE_1) || (dev->type & INPUT_DEVICE_INPUT_LINE_2))
        {

            /* Disable mute on IN1L, IN1L Volume = +0dB */
            write_reg(dev->i2c_bus, 0x18, 0x000B);

            /* Disable mute on IN1R, IN1R Volume = +0dB */
            write_reg(dev->i2c_bus, 0x1A, 0x000B);

            /* AIF ADC1 HPF enable, HPF cut = hifi mode fc=4Hz at fs=48kHz */
            write_reg(dev->i2c_bus, 0x0410, 0x1800);
        }
    }

    /* Return communication control value */
    return RT_EOK;

}

static rt_err_t _read_id(struct rt_i2c_bus_device *bus, rt_uint16_t *id)
{
    rt_uint8_t read_value[2];

    read_reg(bus, 0x0000, 2, read_value);
    *id  = ((uint16_t)(read_value[0] << 8) & 0xFF00);
    *id |= ((uint16_t)(read_value[1])& 0x00FF);

    if (*id != WM8994_ID)
    {
        LOG_E("error id: 0x%04x", *id);
        return RT_ERROR;
    }

    LOG_I("wm8994 init success, id: %04x", *id);

    return RT_EOK;
}

static rt_err_t _set_mute(struct rt_i2c_bus_device *bus, uint32_t cmd)
{
    /* Set the Mute mode */
    if (cmd == AUDIO_MUTE_ON)
    {
        /* Soft Mute the AIF1 Timeslot 0 DAC1 path L&R */
        write_reg(bus, 0x420, 0x0200);

        /* Soft Mute the AIF1 Timeslot 1 DAC2 path L&R */
        write_reg(bus, 0x422, 0x0200);
    }
    else /* AUDIO_MUTE_OFF Disable the Mute */
    {
        /* Unmute the AIF1 Timeslot 0 DAC1 path L&R */
        write_reg(bus, 0x420, 0x0010);

        /* Unmute the AIF1 Timeslot 1 DAC2 path L&R */
        write_reg(bus, 0x422, 0x0010);
    }

    return RT_EOK;
}

static rt_err_t _play(struct rt_i2c_bus_device *bus)
{
    _set_mute(bus, AUDIO_MUTE_OFF);

    return RT_EOK;
}

static rt_err_t _set_volume(struct rt_i2c_bus_device *bus, rt_uint16_t type, rt_uint8_t volume)
{
    rt_uint8_t convertedvol = VOLUME_CONVERT(volume);

    if (type & 0x000F)
    {
        /* Output volume */
        if(convertedvol > 0x3E)
        {
            /* Unmute audio codec */
            _set_mute(bus, AUDIO_MUTE_OFF);

            /* Left Headphone Volume */
            write_reg(bus, 0x1C, 0x3F | 0x140);

            /* Right Headphone Volume */
            write_reg(bus, 0x1D, 0x3F | 0x140);

            /* Left Speaker Volume */
            write_reg(bus, 0x26, 0x3F | 0x140);

            /* Right Speaker Volume */
            write_reg(bus, 0x27, 0x3F | 0x140);
        }
        else if (volume == 0)
        {
            /* Mute audio codec */
            _set_mute(bus, AUDIO_MUTE_ON);
        }
        else
        {
            /* Unmute audio codec */
            _set_mute(bus, AUDIO_MUTE_OFF);

            /* Left Headphone Volume */
            write_reg(bus, 0x1C, convertedvol | 0x140);

            /* Right Headphone Volume */
            write_reg(bus, 0x1D, convertedvol | 0x140);

            /* Left Speaker Volume */
            write_reg(bus, 0x26, convertedvol | 0x140);

            /* Right Speaker Volume */
            write_reg(bus, 0x27, convertedvol | 0x140);
        }
    }
    /* Input volume */
    else
    {
        convertedvol = VOLUME_IN_CONVERT(volume);

        /* Left AIF1 ADC1 volume */
        write_reg(bus, 0x400, convertedvol | 0x100);

        /* Right AIF1 ADC1 volume */
        write_reg(bus, 0x401, convertedvol | 0x100);

        /* Left AIF1 ADC2 volume */
        write_reg(bus, 0x404, convertedvol | 0x100);

        /* Right AIF1 ADC2 volume */
        write_reg(bus, 0x405, convertedvol | 0x100);
    }

    return RT_EOK;
}

static rt_err_t _get_volume(struct rt_i2c_bus_device *bus, rt_uint32_t *value)
{
    rt_uint8_t read_value[2];

    read_reg(bus, 0x001C, 2, read_value);

    *value  = ((uint16_t)(read_value[0] << 8) & 0xFF00);
    *value |= ((uint16_t)(read_value[1])& 0x00FF);

    return RT_EOK;
}

static rt_err_t _set_frequency(struct rt_i2c_bus_device *bus, rt_uint32_t freq)
{
    switch (freq)
    {
        case AUDIO_FREQUENCY_8K:
            write_reg(bus, 0x210, 0x0003);
        break;

        case AUDIO_FREQUENCY_16K:
            write_reg(bus, 0x210, 0x0033);
        break;

        case AUDIO_FREQUENCY_32K:
            write_reg(bus, 0x210, 0x0063);
        break;

        case AUDIO_FREQUENCY_48K:
            write_reg(bus, 0x210, 0x0083);
        break;

        case AUDIO_FREQUENCY_96K:
            write_reg(bus, 0x210, 0x00A3);
        break;

        case AUDIO_FREQUENCY_11K:
            write_reg(bus, 0x210, 0x0013);
        break;

        case AUDIO_FREQUENCY_22K:
            write_reg(bus, 0x210, 0x0043);
        break;

        case AUDIO_FREQUENCY_44K:
            write_reg(bus, 0x210, 0x0073);
        break;

        default:
            write_reg(bus, 0x210, 0x0083);
        break;
    }

    return RT_EOK;
}

static rt_err_t _reset(struct rt_i2c_bus_device *bus)
{
    /* Reset Codec by writing in 0x0000 address register */
    write_reg(bus, 0x0000, 0x0000);

    return RT_EOK;
}

static rt_err_t rt_wm8994_init(rt_device_t dev)
{
    RT_ASSERT(dev != RT_NULL);
    rt_err_t result = RT_EOK;
    static rt_uint16_t old_type = DEVICE_NONE;

    struct wm8994_dev *device = (struct wm8994_dev *)dev;

    if (old_type == device->type)
    {
        return RT_EOK;
    }

    old_type = device->type;

    device->i2c_bus = rt_i2c_bus_device_find(I2C_NAME);
    if (device->i2c_bus == RT_NULL)
    {
        LOG_E("can't find %c deivce", I2C_NAME);
        return RT_ERROR;
    }

    result = _wm8994_init(device);
    /* set volume */
    _set_volume(device->i2c_bus, device->type, VOLUME_CONVERT(100));
    /* set frequency */
    _set_frequency(device->i2c_bus, AUDIO_FREQUENCY_44K);

    return result;
}

static rt_err_t rt_wm8994_open(rt_device_t dev, rt_uint16_t oflag)
{
    RT_ASSERT(dev != RT_NULL);

    return RT_EOK;
}

static rt_err_t rt_wm8994_close(rt_device_t dev)
{
    RT_ASSERT(dev != RT_NULL);
    struct wm8994_dev *device = (struct wm8994_dev *)dev;

    _set_mute(device->i2c_bus, AUDIO_MUTE_ON);

    /* Mute the AIF1 Timeslot 0 DAC1 path */
    write_reg(device->i2c_bus, 0x420, 0x0200);
    /* Mute the AIF1 Timeslot 1 DAC2 path */
    write_reg(device->i2c_bus, 0x422, 0x0200);
    /* Disable DAC1L_TO_HPOUT1L */
    write_reg(device->i2c_bus, 0x2D, 0x0000);
    /* Disable DAC1R_TO_HPOUT1R */
    write_reg(device->i2c_bus, 0x2E, 0x0000);
    /* Disable DAC1 and DAC2 */
    write_reg(device->i2c_bus, 0x05, 0x0000);
    /* Reset Codec by writing in 0x0000 address register */
    write_reg(device->i2c_bus, 0x0000, 0x0000);

    return RT_EOK;
}

static rt_size_t rt_wm8994_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    RT_ASSERT(dev != RT_NULL);

    return RT_EOK;
}

static rt_size_t rt_wm8994_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    RT_ASSERT(dev != RT_NULL);

    return RT_EOK;
}

static rt_err_t rt_wm8994_control(rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev != RT_NULL);
    struct wm8994_dev *device = (struct wm8994_dev *)dev;
    rt_err_t result = RT_EOK;
    switch (cmd)
    {
        case GET_ID:
            result = _read_id(device->i2c_bus, (rt_uint16_t*)args);
            break;

        case SET_FREQUENCE:
            result = _set_frequency(device->i2c_bus, (*(rt_uint32_t *)args));
            break;

        case SET_VOLUME:
            result = _set_volume(device->i2c_bus, device->type, (*(rt_uint8_t*)args));
            break;

        case GET_VOLUME:
            result = _get_volume(device->i2c_bus, (rt_uint32_t *)args);
            break;

        case SET_MUTE:
            result = _set_mute(device->i2c_bus, (*(rt_uint32_t*)args));
            break;

        case SET_RESET:
            result = _reset(device->i2c_bus);
            break;

        case START_PLAY:
            result = _play(device->i2c_bus);
            break;

        case SET_PLAY_TYPE:
            device->type = 0;
            device->type = *(rt_uint32_t *)args;
            rt_wm8994_init(dev);
            break;

        default:
            LOG_D("not support cmd");
            break;
    }

    return result;
}

int wm8994_init(void)
{
    rt_wm8994.dev.type      = RT_Device_Class_Sound;
    rt_wm8994.dev.init      = rt_wm8994_init;
    rt_wm8994.dev.open      = rt_wm8994_open;
    rt_wm8994.dev.close     = rt_wm8994_close;
    rt_wm8994.dev.read      = rt_wm8994_read;
    rt_wm8994.dev.write     = rt_wm8994_write;
    rt_wm8994.dev.control   = rt_wm8994_control;
    rt_wm8994.dev.user_data = RT_NULL;

    rt_device_register(&rt_wm8994.dev, "decoder", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE | RT_DEVICE_FLAG_STANDALONE);

    LOG_I("lowlevel decoder device init success!");

    return RT_EOK;
}
INIT_DEVICE_EXPORT(wm8994_init);

#endif
