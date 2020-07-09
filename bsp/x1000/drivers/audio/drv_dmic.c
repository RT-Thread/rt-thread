/*
 * File      : drv_dmic.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2012, RT-Thread Development Team
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
 * 2015-11-19     Urey         the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/audio.h>

#ifdef RT_USING_FINSH
#   include <finsh.h>
#endif

#include "board.h"
#include "drv_gpio.h"
#include "drv_dma.h"
#include "drv_aic.h"
#include "drv_clock.h"
#include "drv_dmic.h"
#include "dma.h"
#include "audio_pipe.h"

#define DMIC_DEBUG   0
#if DMIC_DEBUG
#	define DMIC_DBG(...)     rt_kprintf("[DMIC]"),rt_kprintf(__VA_ARGS__)
#else
#	define DMIC_DBG(...)
#endif

#define DMIC_DMA_RX_CHAN        4
#define DMIC_FIFO_DEPTH         64
#define JZ_DMIC_FORMATS         16
#define JZ_DMIC_RATE            (8000)
ALIGN(32) rt_uint32_t    _g_dmic_dma_buffer[DMIC_DMA_PAGE_NUM*DMIC_DMA_PAGE_SIZE/sizeof(rt_uint32_t)];
static struct jz_dmic _g_jz_dmic=
{
    .io_base    =   DMIC_BASE,
    .dma_buf    =   (rt_uint8_t *)_g_dmic_dma_buffer,
    .dma_offset =   0,
};

static void dump_dmic_registers(void)
{
    struct jz_dmic *jz_dmic = &_g_jz_dmic;
    rt_kprintf("DMICCR0      %p : 0x%08x\n", (jz_dmic->io_base+DMICCR0),dmic_read_reg(jz_dmic, DMICCR0));
    rt_kprintf("DMICGCR      %p : 0x%08x\n", (jz_dmic->io_base+DMICGCR),dmic_read_reg(jz_dmic, DMICGCR));
    rt_kprintf("DMICIMR      %p : 0x%08x\n", (jz_dmic->io_base+DMICIMR),dmic_read_reg(jz_dmic, DMICIMR));
    rt_kprintf("DMICINTCR    %p : 0x%08x\n", (jz_dmic->io_base+DMICINTCR),dmic_read_reg(jz_dmic, DMICINTCR));
    rt_kprintf("DMICTRICR    %p : 0x%08x\n", (jz_dmic->io_base+DMICTRICR),dmic_read_reg(jz_dmic, DMICTRICR));
    rt_kprintf("DMICTHRH     %p : 0x%08x\n", (jz_dmic->io_base+DMICTHRH),dmic_read_reg(jz_dmic, DMICTHRH));
    rt_kprintf("DMICTHRL     %p : 0x%08x\n", (jz_dmic->io_base+DMICTHRL),dmic_read_reg(jz_dmic, DMICTHRL));
    rt_kprintf("DMICTRIMMAX  %p : 0x%08x\n", (jz_dmic->io_base+DMICTRIMMAX),dmic_read_reg(jz_dmic, DMICTRIMMAX));
    rt_kprintf("DMICTRINMAX  %p : 0x%08x\n", (jz_dmic->io_base+DMICTRINMAX),dmic_read_reg(jz_dmic, DMICTRINMAX));
    rt_kprintf("DMICDR       %p : 0x%08x\n", (jz_dmic->io_base+DMICDR),dmic_read_reg(jz_dmic, DMICDR));
    rt_kprintf("DMICFTHR     %p : 0x%08x\n", (jz_dmic->io_base+DMICFTHR),dmic_read_reg(jz_dmic, DMICFTHR));
    rt_kprintf("DMICFSR      %p : 0x%08x\n", (jz_dmic->io_base+DMICFSR),dmic_read_reg(jz_dmic, DMICFSR));
    rt_kprintf("DMICCGDIS    %p : 0x%08x\n", (jz_dmic->io_base+DMICCGDIS),dmic_read_reg(jz_dmic, DMICCGDIS));
    return;
}
MSH_CMD_EXPORT(dump_dmic_registers,"dump dmic regs...\n");

int jz_dmic_set_rate(struct jz_dmic*   dmic, int rate)
{
    // rt_kprintf("rate = %d\n",rate);
    switch (rate)
    {
    case 8000:
        __dmic_set_sr_8k(dmic);
        break;
    case 16000:
        __dmic_set_sr_16k(dmic);
        break;
    case 48000:
        __dmic_set_sr_48k(dmic);
        break;
    default:
        DMIC_DBG("dmic unsupport rate %d\n", rate);
    }
    return 0;
}

int jz_dmic_set_channels(struct jz_dmic*   dmic, int channels)
{
    if (channels > 4)
        channels = 4;
    if (channels <= 1)
        channels = 1;

    __dmic_set_chnum(dmic,channels - 1);
}


int jz_dmic_set_record_volume(struct jz_dmic*   dmic, int vol)
{
    if(vol >= 32)
        vol = 31;
    __dmic_set_gcr(dmic,vol);

    dmic->record_gain = vol;
}

static void jz_dmic_dma_complete(struct rt_dma_channel *dmac, struct dma_message *msg)
{
    rt_base_t   level;
    if(msg->complete_cb)
    	msg->complete_cb(msg->complete_arg,msg->dst_addr);

    /* restart DMA Job */
    rt_dma_trans_message(dmac,msg);
}


void jz_dmic_start_recv(struct jz_dmic* dmic,void (*rx_callback)(void *,void *), void *rx_arg)
{
    rt_base_t   level;
    rt_uint32_t i;
    struct dma_message         message;
    __dmic_enable_rdms(dmic);
    __dmic_enable(dmic);
    level = rt_hw_interrupt_disable();
    dmic->dma_offset    = 0;
    dmic->dma_buf       = (rt_uint8_t *)_g_dmic_dma_buffer;

    for (i = 0; i < DMIC_DMA_PAGE_NUM; ++i)
    {
        message.src_addr    = (uint8_t *) (DMIC_BASE + DMICDR);
        message.src_option  = RT_DMA_ADDR_FIX;
        message.dst_addr    = (uint8_t *) (dmic->dma_buf + DMIC_DMA_PAGE_SIZE * i);
        message.dst_option  = RT_DMA_ADDR_INC;
        message.t_size      = DMIC_DMA_PAGE_SIZE;
        message.t_mode      = JZDMA_REQ_DMIC_RX;
        /* init callback */
        message.complete_cb  = rx_callback;
        message.complete_arg = rx_arg;
        rt_dma_trans_message(dmic->rx_dmac,&message);
    }
    rt_hw_interrupt_enable(level);
    return ;
}

void jz_dmic_stop_recv(struct jz_dmic* dmic)
{
    if (__dmic_is_enable_rdms(dmic))
    {
        __dmic_disable_rdms(dmic);
    }
    __dmic_disable(dmic);
}


void  dmic_rx_complete(void *data,void *pbuf)
{
    struct jz_dmic *dmic =  (struct jz_dmic *)data;

    rt_device_write(RT_DEVICE(&dmic->pipe),0,pbuf,DMIC_DMA_PAGE_SIZE);
}

#define CFG_DMIC_PIPE_SIZE      (2 * 1024)
struct jz_dmic* rt_hw_dmic_init(void)
{
    struct jz_dmic  *dmic = &_g_jz_dmic;

    //init pipe for record
    {
        rt_uint8_t *buf = rt_malloc(CFG_DMIC_PIPE_SIZE);

        if(buf == RT_NULL)
        {
            rt_kprintf("request pipe memory error\n");

            return RT_NULL;
        }

        rt_audio_pipe_init(&dmic->pipe,"recdmic",RT_PIPE_FLAG_FORCE_WR | RT_PIPE_FLAG_BLOCK_RD,buf,(CFG_DMIC_PIPE_SIZE));

        rt_device_open(RT_DEVICE(&dmic->pipe),RT_DEVICE_OFLAG_RDONLY);
    }

    /* GPIO config
     * PB05 -> FUNC1  DMIC1_IN
     * PB21 -> FUNC0  DMIC_CLK
     * PB22 -> FUNC0  DMIC0_IN
     * */
    gpio_set_func(GPIO_PORT_B,GPIO_Pin_5,GPIO_FUNC_1);
    gpio_set_func(GPIO_PORT_B,GPIO_Pin_21,GPIO_FUNC_0);
    gpio_set_func(GPIO_PORT_B,GPIO_Pin_22,GPIO_FUNC_0);

    /* enable clock */
    dmic->clk_gate = clk_get("dmic");
    if (dmic->clk_gate == RT_NULL)
    {
        DMIC_DBG("Failed to get dmic gate clock \n");
        return RT_NULL;
    }
    clk_enable(dmic->clk_gate);

    /*gain: 0, ..., e*/
    __dmic_reset(dmic);
    while (__dmic_get_reset(dmic)) ;

    jz_dmic_set_rate(dmic, 8000);
    __dmic_set_chnum(dmic,0);           //mono
    __dmic_enable_hpf1(dmic);
    __dmic_set_gcr(dmic, 27);
    __dmic_mask_all_int(dmic);
    __dmic_enable_pack(dmic);
    __dmic_enable_sw_lr(dmic);
    __dmic_enable_lp(dmic);
    __dmic_disable_lp(dmic);
    __dmic_set_request(dmic, 48);
    __dmic_enable_hpf2(dmic);
    __dmic_set_thr_high(dmic, 32);
    __dmic_set_thr_low(dmic, 16);
    __dmic_enable_tri(dmic);


    //config DMA
    {
        int trigger;

        /* DMA config */
        struct dma_config config;
        dmic->rx_dmac = rt_dma_get_channel(DMIC_DMA_RX_CHAN);
        if (dmic->rx_dmac != RT_NULL)
        {
            DMIC_DBG("config dmic dma rx channel...\n");
            config.direction        = RT_DMA_DEV_TO_MEM;
            config.src_addr_width   = RT_DMA_BUSWIDTH_2_BYTES;
            config.src_maxburst     = (DMIC_FIFO_DEPTH * RT_DMA_BUSWIDTH_2_BYTES) / 2;
            config.dst_addr_width   = RT_DMA_BUSWIDTH_2_BYTES;
            config.dst_maxburst     = (64 * 1024);
            rt_dma_configture(dmic->rx_dmac, &config);

            dmic->rx_dmac->start = RT_NULL;
            dmic->rx_dmac->complete = jz_dmic_dma_complete;
        }
        trigger = config.src_maxburst / config.src_addr_width;
        __dmic_set_request(dmic, trigger);
    }

    jz_dmic_start_recv(dmic,dmic_rx_complete,dmic);

    return dmic;

_error_exit:
    __dmic_disable(dmic);

    rt_audio_pipe_detach(&dmic->pipe);

    clk_disable(dmic->clk_gate);

    return RT_NULL;
}
//INIT_ENV_EXPORT(rt_hw_dmic_init);


struct speech_wav_header
{
    char riff_id[4];            //"RIFF"
    uint32_t size0;             //file len - 8
    char wave_fmt[8];           //"WAVEfmt "
    uint32_t size1;             //0x10
    uint16_t fmttag;            //0x01
    uint16_t channel;           //1
    uint32_t samplespersec;     //8000
    uint32_t bytepersec;        //8000 * 2
    uint16_t blockalign;        //1 * 16 / 8
    uint16_t bitpersamples;     //16
    char data_id[4];            //"data"
    uint32_t size2;             //file len - 44
};

static void speech_wav_init_header(struct speech_wav_header *header,rt_uint16_t Channels,int SamplesPerSec,int BitsPerSample)
{
    strcpy(header->riff_id, "RIFF");
    header->size0           = 0;                // Final file size not known yet, write 0
    strcpy(header->wave_fmt, "WAVEfmt ");
    header->size1           = 16;               // Sub-chunk size, 16 for PCM
    header->fmttag          = 1;                // AudioFormat, 1 for PCM
    header->channel         = Channels;         // Number of channels, 1 for mono, 2 for stereo
    header->samplespersec   = SamplesPerSec;    // Sample rate
    header->bytepersec      = SamplesPerSec * BitsPerSample * Channels / 8; //Byte rate
    header->blockalign      = Channels * BitsPerSample / 8;                 // Block align, NumberOfChannels*BitsPerSample/8
    header->bitpersamples   = BitsPerSample;
    strcpy(header->data_id, "data");
    header->size2           = 0;
}

static void speech_wav_upgrade_size(struct speech_wav_header *header,rt_uint32_t paylodSize)
{
    header->size0           = paylodSize + 36;
    header->size2           = paylodSize;
}


#include <finsh.h>
#include <dfs_posix.h>

rt_uint8_t  rec_buff[2048];
int dmic_record(int samplingrates)
{
    struct jz_dmic  *dmic = &_g_jz_dmic;
    rt_device_t dmic_pipe;
    struct speech_wav_header wav_header;
    rt_uint32_t wav_len = 0;
    char *file_name;
    int fd;
    int i = 0;
    int rdlen, wrlen;

    rt_kprintf("samplingrates = %d\n",samplingrates);
    if((samplingrates != 8000) && (samplingrates != 16000))
    {
        rt_kprintf("un-support this samplingrates\n");
        return -RT_EIO;
    }

    dmic_pipe = rt_device_find("recdmic");
    if(dmic_pipe == RT_NULL)
    {
        rt_kprintf("can't find the record device\n");
        return -RT_ERROR ;
    }

    rt_kprintf("pls hold WAKE key to start record...\n");
    while(gpio_get_value(GPIO_PORT_B, GPIO_Pin_31) == 1)
        rt_thread_delay(100);
    rt_kprintf("OK,start record....\n");
    if(samplingrates == 8000)
        file_name = "/appfs/dmic8k.wav";
    else
        file_name = "/appfs/dmic16k.wav";

    fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0);
    if (fd < 0)
    {
        rt_kprintf("open file for write failed\n");
        return -RT_EIO;
    }

    speech_wav_init_header(&wav_header,1,samplingrates,16);
    write(fd, &wav_header, wav_len);

    jz_dmic_set_rate(dmic,samplingrates);
    wav_len = 0;
    while(i++ < 1000)
    {
        rdlen = rt_device_read(dmic_pipe,0,rec_buff,sizeof(rec_buff));

        wrlen = write(fd, rec_buff, rdlen);
        if (wrlen != rdlen)
        {
            rt_kprintf("write data failed\n");
            close(fd);

            return -RT_EIO;
        }

        wav_len += wrlen;

        if(gpio_get_value(GPIO_PORT_B, GPIO_Pin_31) == 1)
            break;
    }
    rt_kprintf("record complete...\n");

    //upgrage wav header
    lseek(fd,0,SEEK_SET);
    speech_wav_upgrade_size(&wav_header,wav_len);
    write(fd, &wav_header, sizeof(struct speech_wav_header));

    close(fd);

    rt_kprintf("WAV file saved ok!\n");
}
FINSH_FUNCTION_EXPORT(dmic_record,dmic record test);

#if 0
int dmic_test(void)
{
    rt_device_t device;
    int i = 0;

    device = rt_device_find("recdmic");
    if(device == RT_NULL)
    {
        rt_kprintf("can't find the record device\n");
        return -RT_ERROR ;
    }

    audio_device_set_rate(8000);

    while(i++ < 1000)
    {
        int     len;
        uint8_t *sendBuf;

        sendBuf = audio_device_get_buffer(&len);
        len = rt_device_read(device,0,sendBuf,len);

        audio_device_write(sendBuf,len);
    }

    rt_kprintf("dmic test complete...\n");

    return 0;
}
MSH_CMD_EXPORT(dmic_test,dmic test ....);
#endif
