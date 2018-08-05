/*
 * File      : drv_audio.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-26     RT-Thread    the first version
 */

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include <string.h>
#include "drv_pl041.h"
#include "drv_ac97.h"
#include "drv_audio.h"

#define DATA_NODE_MAX          (10)
#define CODEC_TX_FIFO_SIZE     (256)

#define AUDIO_DEVICE_DECODE_MP_SIZE  (4096)
#define AUDIO_DEVICE_DECODE_MP_CONUT (4)

struct codec_data_node
{
    char *data_ptr;
    rt_size_t  data_size;
};

struct audio_buff_des
{
    struct codec_data_node *data_list;
    void (*free_fun)(void *);
    rt_uint32_t read_offset;
    rt_uint16_t node_num;
    rt_uint16_t read_index, put_index;
};

struct audio_device
{
    /* inherit from rt_device */
    struct rt_device parent;
};

static struct audio_device audio_device_drive;
static struct audio_buff_des *audio_buff;
static int irq_flag = 0;

static void _audio_buff_cb(void *buff)
{
    if (audio_device_drive.parent.tx_complete != RT_NULL)
    {
        audio_device_drive.parent.tx_complete(&audio_device_drive.parent, buff);
    }
}

static rt_size_t _audio_buff_push(struct audio_buff_des *hdle, void *buff, int size)
{
    struct codec_data_node *node;
    rt_uint16_t next_index;
    rt_uint32_t level;

    if ((buff == RT_NULL) || (size == 0))
    {
        return 0;
    }

    next_index = hdle->put_index + 1;
    if (next_index >= hdle->node_num)
        next_index = 0;
    /* check data_list full */
    if (next_index == hdle->read_index)
    {
        rt_kprintf("data_list full\n");
        rt_set_errno(-RT_EFULL);
        return 0;
    }

    level = rt_hw_interrupt_disable();
    node = &hdle->data_list[hdle->put_index];
    hdle->put_index = next_index;

    /* set node attribute */
    node->data_ptr = (char *) buff;
    node->data_size = size;
    rt_hw_interrupt_enable(level);

    return size;
}

static rt_size_t _audio_buff_pop(struct audio_buff_des *hdle, void *buff, int size)
{
    struct codec_data_node *node;
    rt_uint32_t next_index, count = 0, cp_size = 0, offset = 0;

    node = &hdle->data_list[hdle->read_index];
    if ((hdle->read_index == hdle->put_index) && (node->data_ptr == RT_NULL))
    {
        memset(buff, 0xff, size);
        return 0;
    }

    while (count < size)
    {
        node = &hdle->data_list[hdle->read_index];
        offset = hdle->read_offset;
        cp_size = (node->data_size - offset) > (size - count) ? (size - count) : (node->data_size - offset);

        if (node->data_ptr == RT_NULL)
        {
            memset(buff, 0, size - count);
            return count;
        }

        memcpy((rt_uint8_t *)buff + count, (rt_uint8_t *)(node->data_ptr) + offset, cp_size);
        hdle->read_offset += cp_size;
        count += cp_size;

        if (hdle->read_offset >= node->data_size)
        {
            /* notify transmitted complete. */
            if (hdle->free_fun != RT_NULL)
            {
                hdle->free_fun(node->data_ptr);
            }
            /* clear current node */
            memset(node, 0, sizeof(struct codec_data_node));
            next_index = hdle->read_index + 1;
            if (next_index >= hdle->node_num)
            {
                next_index = 0;
            }
            hdle->read_offset = 0;
            hdle->read_index = next_index;
        }
    }

    return count;
}

static void transit_wav_data(rt_uint32_t status)
{
    rt_uint16_t sample[CODEC_TX_FIFO_SIZE];
    int i = 0, size;

    size = _audio_buff_pop(audio_buff, sample, CODEC_TX_FIFO_SIZE * sizeof(rt_uint16_t));
    if ((size == 0) && (irq_flag == 1))
    {
        aaci_pl041_irq_disable(0, AACI_IE_UR | AACI_IE_TX | AACI_IE_TXC);
        irq_flag = 0;
    }

    for (i = 0; i < (size >> 1); i++)
    {
        aaci_pl041_channle_write(0, &sample[i], 1);
    }
}

static void rt_hw_aaci_isr(rt_uint32_t status, void *user_data)
{
    if (status & AACI_SR_TXHE)
    {
        transit_wav_data(status);
    }
}

static rt_err_t codec_init(rt_device_t dev)
{
    struct pl041_cfg _cfg;

    _cfg.itype = PL041_CHANNLE_LEFT_ADC | PL041_CHANNLE_RIGHT_ADC;
    _cfg.otype = PL041_CHANNLE_LEFT_DAC | PL041_CHANNLE_RIGHT_DAC;
    _cfg.vol = 50;
    _cfg.rate = 8000;

    ac97_reset();
    aaci_pl041_channle_cfg(0, &_cfg);
    aaci_pl041_irq_register(0, rt_hw_aaci_isr, RT_NULL);

    return RT_EOK;
}

static rt_err_t codec_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t codec_close(rt_device_t dev)
{
    rt_uint16_t temp = 0, i = 1024 * 10;

    while (PL041->sr1 & AACI_SR_TXB);
    while (i)
    {
        if (aaci_pl041_channle_write(0, &temp, 1) != 0)
        {
            i--;
        }
    }
    return RT_EOK;
}

static rt_size_t codec_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    return 0;
}

static rt_size_t codec_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    _audio_buff_push(audio_buff, (void *)buffer, size);

    if (irq_flag == 0)
    {
        //open irq
        irq_flag = 1;
        aaci_pl041_channle_enable(0);
        aaci_pl041_irq_enable(0, AACI_IE_UR | AACI_IE_TX | AACI_IE_TXC);
    }
    return 0;
}

static rt_err_t codec_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t result = RT_EOK;

    switch (cmd)
    {
    case CODEC_CMD_RESET:
    {
        break;
    }
    case CODEC_CMD_SET_VOLUME:
    {
        uint32_t v;

        v = *(rt_uint32_t *)args;
        result = ac97_set_vol(v);
        break;
    }
    case CODEC_CMD_GET_VOLUME:
    {
        int *v = args;
        *v = ac97_get_vol();
        break;
    }
    case CODEC_CMD_SAMPLERATE:
    {
        int v;

        v = *(rt_uint32_t *)args;
        ac97_set_rate(v);
        break;
    }

    default:
        result = RT_ERROR;
    }

    return result;
}

int audio_hw_init(void)
{
    struct audio_device *codec = &audio_device_drive;

    codec->parent.type        = RT_Device_Class_Sound;
    codec->parent.rx_indicate = RT_NULL;
    codec->parent.tx_complete = RT_NULL;

    codec->parent.init    = codec_init;
    codec->parent.open    = codec_open;
    codec->parent.close   = codec_close;
    codec->parent.read    = codec_read;
    codec->parent.write   = codec_write;
    codec->parent.control = codec_control;

    codec->parent.user_data   = RT_NULL;

    audio_buff = rt_malloc(sizeof(struct audio_buff_des) + sizeof(struct codec_data_node) * DATA_NODE_MAX);
    if (audio_buff == RT_NULL)
    {
        rt_kprintf("audio buff malloc fail\n");
        return -1;
    }
    rt_memset(audio_buff, 0, sizeof(struct audio_buff_des) + sizeof(struct codec_data_node) * DATA_NODE_MAX);
    audio_buff->data_list = (struct codec_data_node *)((rt_uint8_t *)audio_buff + sizeof(struct audio_buff_des));
    audio_buff->free_fun = _audio_buff_cb;
    audio_buff->node_num = DATA_NODE_MAX;
    /* register the device */
    rt_device_register(&codec->parent, "sound", RT_DEVICE_FLAG_WRONLY | RT_DEVICE_FLAG_DMA_TX);

    aaci_pl041_init();
    rt_device_init(&codec->parent);

    return 0;
}
INIT_DEVICE_EXPORT(audio_hw_init);
