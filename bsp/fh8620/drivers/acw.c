/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
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
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include "acw.h"
#include "fh_def.h"
#include "fh_dma.h"
#include "dma.h"
#ifdef RT_USING_FH_ACW
#if 1
typedef struct 
{
	unsigned int 			base;
	void 					*vbase;
	unsigned int 			size;
	unsigned int 			align;
}MEM_DESC;
#define ACW_SELFTEST 0
int buffer_malloc_withname(MEM_DESC *mem, int size, int align,  char* name);
#endif

#define NR_DESCS_PER_CHANNEL 64

#define FIX_SAMPLE_BIT       32

#define ACW_HW_NUM_RX  0
#define ACW_HW_NUM_TX  1
#define ACW_DMA_CAP_CHANNEL 3
#define ACW_DMA_PAY_CHANNEL 2

#define ACW_CTRL                         0x0
#define ACW_TXFIFO_CTRL         0x4
#define ACW_RXFIFO_CTRL         0x8
#define ACW_STATUS                     0x0c
#define ACW_DIG_IF_CTRL          0x10
#define ACW_ADC_PATH_CTRL      0x14
#define ACW_ADC_ALC_CTRL      0x18
#define ACW_DAC_PATH_CTRL     0x1c
#define ACW_MISC_CTRL              0x20
#define ACW_TXFIFO                      0xf0a00100
#define ACW_RXFIFO                      0xf0a00200
typedef char bool;
#define AUDIO_DMA_PREALLOC_SIZE 128*1024

#define ACW_INTR_RX_UNDERFLOW   0x10000
#define ACW_INTR_RX_OVERFLOW    0x20000
#define ACW_INTR_TX_UNDERFLOW   0x40000
#define ACW_INTR_TX_OVERFLOW    0x80000
#define PAGE_SIZE 0x1000

enum audio_type
{
    capture = 0,
    playback,
};

enum audio_state
{
    normal = 0,
    xrun,
    stopping,
    running,
};

struct infor_record_t
{
    int record_pid;
    int play_pid;
}; // infor_record;

struct audio_config_t {
    int rate;
    int volume;
    enum io_select io_type;
    int frame_bit;
    int channels;
    int buffer_size;
    int period_size;
    int buffer_bytes;
    int period_bytes;
    int start_threshold;
    int stop_threshold;
};

struct audio_ptr_t
{
    struct audio_config_t cfg;
    enum audio_state state;
    long size;
    int hw_ptr;
    int appl_ptr;
    struct rt_mutex lock;
    struct device_acw dev;
    void *area; /*virtual pointer*/
    dma_addr_t addr; /*physical address*/
    unsigned char * mmap_addr;
};

struct fh_audio_cfg
{
    struct rt_dma_device *capture_dma;
    struct rt_dma_device *playback_dma;
    struct dma_transfer *capture_trans;
    struct dma_transfer *plauback_trans;
    struct audio_ptr_t capture;
    struct audio_ptr_t playback;
    wait_queue_head_t readqueue;
    wait_queue_head_t writequeue;
    struct rt_semaphore sem_capture;
    struct rt_semaphore sem_playback;
};
typedef int            s32;
typedef s32            dma_cookie_t;
struct fh_dma_chan
{
    struct dma_chan     *chan;
    void    *ch_regs;
    unsigned char          mask;
    unsigned char          priority;
    bool           paused;
    bool                initialized;
    struct rt_mutex      lock;
    /* these other elements are all protected by lock */
    unsigned long       flags;
    dma_cookie_t        completed;
    struct list_head    active_list;
    struct list_head    queue;
    struct list_head    free_list;
    struct fh_cyclic_desc   *cdesc;
    unsigned int        descs_allocated;
};

struct fh_acw_dma_transfer
{
    struct dma_chan *chan;
    struct dma_transfer cfg;
    struct scatterlist sgl;
    struct dma_async_tx_descriptor *desc;
};

struct channel_assign
{
    int capture_channel;
    int playback_channel;
};

struct audio_dev_mod
{
    int reg_base;
    struct channel_assign channel_assign;
    struct fh_audio_cfg   *audio_config;

}audio_dev;
static struct work_struct playback_wq;
#define WORK_QUEUE_STACK_SIZE         512
#if ACW_SELFTEST
#define WORK_QUEUE_PRIORITY           (12)
#else
#define WORK_QUEUE_PRIORITY           (128+12)
#endif
static struct rt_workqueue* playback_queue;


void audio_prealloc_dma_buffer(int aiaotype,struct fh_audio_cfg  *audio_config);
#if ACW_SELFTEST
#define BUFF_SIZE            1024*8
#define TEST_PER_NO         1024
#endif
static void audio_callback(){
    rt_kprintf("# \n");
}

static void audio_callback_capture(){
    rt_kprintf("$ \n");
}


static struct audio_param_store_t
{
    int input_volume;
    enum io_select input_io_type;
} audio_param_store;
void reset_dma_buff(enum audio_type type, struct fh_audio_cfg *audio_config);
static void fh_acw_tx_dma_done(void *arg);
static void fh_acw_rx_dma_done(struct fh_audio_cfg *arg);
static bool  fh_acw_dma_chan_filter(struct dma_chan *chan, void *filter_param);
#define writel(v,a)  SET_REG(a,v)
void fh_acw_stop_playback(struct fh_audio_cfg *audio_config)
{
    if(audio_config->playback.state == stopping)
    {
        return;
    }

    unsigned int rx_status;
    rx_status = readl( audio_dev.reg_base + ACW_TXFIFO_CTRL);//clear rx fifo
    rx_status =  rx_status|(1<<4);
    writel(rx_status,audio_dev.reg_base + ACW_TXFIFO_CTRL);

    audio_config->playback.state = stopping;
    writel(0, audio_dev.reg_base + ACW_TXFIFO_CTRL);//tx fifo disable
    if(audio_config->plauback_trans->channel_number != ACW_PLY_DMA_CHAN)
    	goto free_mem;
    if(!audio_config->plauback_trans->first_lli)
    	goto free_channel;
    audio_config->playback_dma->ops->control(audio_config->playback_dma,RT_DEVICE_CTRL_DMA_CYCLIC_STOP,audio_config->plauback_trans);
    audio_config->playback_dma->ops->control(audio_config->playback_dma,RT_DEVICE_CTRL_DMA_CYCLIC_FREE,audio_config->plauback_trans);
free_channel:
    audio_config->playback_dma->ops->control(audio_config->playback_dma,RT_DEVICE_CTRL_DMA_RELEASE_CHANNEL,audio_config->plauback_trans);
    if(&audio_config->sem_playback)
    rt_sem_release(&audio_config->sem_playback);
    if(&audio_config->playback.lock)
    rt_mutex_release(&audio_config->playback.lock);
    if(&playback_wq)
    rt_workqueue_cancel_work(playback_queue,&playback_wq);
    if(playback_queue)
    rt_workqueue_destroy(playback_queue);
free_mem:
    if(audio_config->playback.area)
    fh_dma_mem_free(audio_config->playback.area);

}

void fh_acw_stop_capture(struct fh_audio_cfg *audio_config)
{
    unsigned int rx_status;

    if(audio_config->capture.state == stopping)
    {
          rt_kprintf(" capture is stopped \n");
        return;
    }
    rx_status = readl( audio_dev.reg_base + ACW_RXFIFO_CTRL);//clear rx fifo
    rx_status =  rx_status|(1<<4);
    writel(rx_status,audio_dev.reg_base + ACW_RXFIFO_CTRL);
    audio_config->capture.state = stopping;

    writel(0, audio_dev.reg_base + 8);//rx fifo disable
    if(audio_config->capture_trans->channel_number != ACW_CAP_DMA_CHAN)
    	goto free_mem;
    if(!audio_config->capture_trans->first_lli)
    	goto free_channel;
    audio_config->capture_dma->ops->control(audio_config->capture_dma,RT_DEVICE_CTRL_DMA_CYCLIC_STOP,audio_config->capture_trans);

    audio_config->capture_dma->ops->control(audio_config->capture_dma,RT_DEVICE_CTRL_DMA_CYCLIC_FREE,audio_config->capture_trans);
free_channel:
    audio_config->capture_dma->ops->control(audio_config->capture_dma,RT_DEVICE_CTRL_DMA_RELEASE_CHANNEL,audio_config->capture_trans);
    if(&audio_config->sem_capture)
    rt_sem_release(&audio_config->sem_capture);
    if(&audio_config->capture.lock)
    rt_mutex_release(&audio_config->capture.lock);
free_mem:
    if(audio_config->capture.area)
    fh_dma_mem_free( audio_config->capture.area);
}

void switch_io_type(enum audio_type type, enum io_select io_type)
{
    int reg;
    if (capture == type)
    {
        reg = readl(audio_dev.reg_base + ACW_ADC_PATH_CTRL);
        if (mic_in == io_type)
        {
            rt_kprintf("audio input changed to mic_in\n");
            writel( reg & (~(1<<1)),audio_dev.reg_base + ACW_ADC_PATH_CTRL);
        	reg = readl(audio_dev.reg_base + ACW_ADC_PATH_CTRL);
       	    reg = reg & (~(1<<3));
       	    reg |=(0x1<<3);
       	    writel(reg, audio_dev.reg_base + ACW_ADC_PATH_CTRL);
        }
        else if (line_in == io_type)
        {
            rt_kprintf("audio input changed to line_in\n");
            writel(reg | (1<<1), audio_dev.reg_base + ACW_ADC_PATH_CTRL);
        }
    }
    else
    {
        reg = readl(audio_dev.reg_base + ACW_DAC_PATH_CTRL);
        if (speaker_out == io_type)
        {
            rt_kprintf("audio output changed to speaker_out\n");
            reg = reg & (~(3<<21));
            reg = reg & (~(3<<30));
            writel(reg, audio_dev.reg_base + ACW_DAC_PATH_CTRL);
            reg = reg | (1<<21);
            writel(reg,audio_dev.reg_base + ACW_DAC_PATH_CTRL);
            reg = reg | (1<<18);
            writel(reg, audio_dev.reg_base + ACW_DAC_PATH_CTRL);/*unmute speaker*/
            reg = reg | (3<<30);
            writel(reg,audio_dev.reg_base + ACW_DAC_PATH_CTRL);/*mute line out*/
        }
        else if (line_out == io_type)
        {
            rt_kprintf("audio output changed to line_out\n");
            reg = reg & (~(3<<21));
            writel(reg, audio_dev.reg_base + ACW_DAC_PATH_CTRL);/*mute speaker*/
            reg = reg & (~(3<<30));
            writel(reg, audio_dev.reg_base + ACW_DAC_PATH_CTRL);/*unmute line out*/
        }
    }
}

int get_factor_from_table(int rate)
{
    int factor;
    switch(rate)
    {
        case 8000:
            factor = 4;
            break;
        case 16000:
            factor = 1;
            break;
        case 32000:
            factor = 0;
            break;
        case 44100:
            factor = 13;
            break;
        case 48000:
            factor = 6;
            break;
        default:
            factor = -EFAULT;
            break;
    }
    return factor;
}

void switch_rate(enum audio_type type, int rate)
{
    int reg, factor;
    factor = get_factor_from_table(rate);
    if (factor < 0)
    {
        rt_kprintf( "unsupported sample rate\n");
        return;
    }
    reg = readl(audio_dev.reg_base + ACW_DIG_IF_CTRL);
    if (capture == type)
    {
        rt_kprintf("capture rate set to %d\n", rate);
        reg = reg & (~(0xf<<0));
        writel(reg, audio_dev.reg_base + ACW_DIG_IF_CTRL);/*adc and dac sample rate*/
        reg = reg | (factor<<0);
        writel(reg,audio_dev.reg_base + ACW_DIG_IF_CTRL);
    }
    else
    {
        rt_kprintf("playback rate set to %d\n", rate);
        reg = reg & (~(0xf<<8));
        writel(reg, audio_dev.reg_base + ACW_DIG_IF_CTRL);/*adc and dac sample rate*/
        reg = reg | (factor<<8);
        writel(reg, audio_dev.reg_base + ACW_DIG_IF_CTRL);
    }
}

int get_param_from_volume(int volume)
{
    if(volume < 0)
        volume = 0;
    else if(volume > 100)
        volume = 100;

    volume = volume * 63 / 100;
    return volume;

}

void switch_input_volume(int volume)
{
    int reg, param;
    param = get_param_from_volume(volume);
    if (param < 0)
    {
    	rt_kprintf("capture volume error\n");
        return;
    }

    reg = readl(audio_dev.reg_base + ACW_ADC_PATH_CTRL);
    reg = reg & (~(0x3f<<8));
    writel(reg, audio_dev.reg_base + ACW_ADC_PATH_CTRL);
    reg = reg | (param<<8);
    writel(reg,audio_dev.reg_base + ACW_ADC_PATH_CTRL);
}

void init_audio(enum audio_type type,struct fh_audio_cfg  *audio_config)
{
    int reg;
    reg = readl(audio_dev.reg_base + ACW_CTRL);
    if ((reg & 0x80000000) == 0)
    {
        writel(0x80000000, audio_dev.reg_base + ACW_CTRL);/*enable audio*/
    }
    reg = readl(audio_dev.reg_base + ACW_MISC_CTRL);
    if (0x40400 != reg)
    {
        writel(0x40400,audio_dev.reg_base + ACW_MISC_CTRL);/*misc ctl*/
    }
    if (capture == type)
    {
        writel(0x61141b06,audio_dev.reg_base + ACW_ADC_PATH_CTRL);/*adc cfg*/
        writel(0x167f2307, audio_dev.reg_base + ACW_ADC_ALC_CTRL);/*adc alc*/
        writel(0, audio_dev.reg_base + ACW_RXFIFO_CTRL);/*rx fifo disable*/
        switch_input_volume(audio_config->capture.cfg.volume);
        switch_rate(capture, audio_config->capture.cfg.rate);
        switch_io_type(capture, audio_config->capture.cfg.io_type);
    }
    else
    {
        writel(0x3b403f09, audio_dev.reg_base + ACW_DAC_PATH_CTRL);/*dac cfg*/
        writel(0, audio_dev.reg_base + ACW_TXFIFO_CTRL);/*tx fifo disable*/
        switch_rate(playback, audio_config->playback.cfg.rate);
        switch_io_type(playback, audio_config->playback.cfg.io_type);
    }

}

static inline long bytes_to_frames(int frame_bit, int bytes)
{
    return bytes * 8 /frame_bit;
}

static inline long  frames_to_bytes(int frame_bit, int frames)
{
    return frames * frame_bit / 8;
}

int avail_data_len(enum audio_type type,struct fh_audio_cfg *stream)
{
    int delta;
    if (capture == type)
    {


        delta = stream->capture.hw_ptr - stream->capture.appl_ptr;

        if (delta < 0)
        {
            delta += stream->capture.size;
        }
        return delta;
    }
    else
    {


        delta = stream->playback.appl_ptr - stream->playback.hw_ptr;

        if (delta < 0)
        {
            delta += stream->playback.size;
        }
        return stream->playback.size - delta;
    }
}

static rt_err_t fh_audio_close(rt_device_t dev)
{
    struct fh_audio_cfg  *audio_config = dev->user_data;
    unsigned int reg;

    //disable interrupts
    reg = readl(audio_dev.reg_base + ACW_CTRL);
    reg &= ~(0x3ff);
    writel(reg, audio_dev.reg_base + ACW_CTRL);

        fh_acw_stop_playback(audio_config);

        fh_acw_stop_capture(audio_config);

}

int register_tx_dma(struct fh_audio_cfg  *audio_config)
{
    int ret;
    struct dma_transfer *playback_trans;
    playback_trans = audio_config->plauback_trans;
    struct rt_dma_device *rt_dma_dev;
    rt_dma_dev = audio_config->playback_dma;
    if ((audio_config->playback.cfg.buffer_bytes < audio_config->playback.cfg.period_bytes) ||
        (audio_config->playback.cfg.buffer_bytes <= 0) || (audio_config->playback.cfg.period_bytes <= 0))
    {
        rt_kprintf( "buffer_size and  period_size are invalid\n");
        return RT_ERROR;
    }

    if(playback_trans->channel_number == ACW_PLY_DMA_CHAN){

    	ret = rt_dma_dev->ops->control(rt_dma_dev,RT_DEVICE_CTRL_DMA_CYCLIC_PREPARE,playback_trans);
    	if(ret){
    		rt_kprintf("can't playback cyclic prepare \n");
    		return RT_ERROR;
    	}
    	ret = 	rt_dma_dev->ops->control(rt_dma_dev,RT_DEVICE_CTRL_DMA_CYCLIC_START,playback_trans);
    	if(ret){
    		rt_kprintf("can't playback cyclic start \n");
    		return RT_ERROR;
    	}
    }
    else
    	return RT_ERROR;
    return 0;
}

int register_rx_dma( struct fh_audio_cfg  *audio_config)
{
	int ret;
    struct dma_transfer *capture_slave;
    capture_slave = audio_config->capture_trans;
    struct rt_dma_device *rt_dma_dev;
    rt_dma_dev = audio_config->capture_dma;
    if (!capture_slave)
    {
        return -ENOMEM;
    }

    if ((audio_config->capture.cfg.buffer_bytes < audio_config->capture.cfg.period_bytes) ||
       (audio_config->capture.cfg.buffer_bytes <= 0) ||(audio_config->capture.cfg.period_bytes <= 0) )
    {
        rt_kprintf( "buffer_size and  period_size are invalid\n");
        return RT_ERROR;
    }
    if(capture_slave->channel_number==ACW_CAP_DMA_CHAN){
    	ret = rt_dma_dev->ops->control(rt_dma_dev,RT_DEVICE_CTRL_DMA_CYCLIC_PREPARE,capture_slave);
    	if(ret){
    		rt_kprintf("can't capture cyclic prepare \n");
    		return RT_ERROR;
    	}
    	ret = rt_dma_dev->ops->control(rt_dma_dev,RT_DEVICE_CTRL_DMA_CYCLIC_START,capture_slave);
    	if(ret){
    		rt_kprintf("can't capture cyclic start \n");
    		return RT_ERROR;
    	}
    }
    else
    	return RT_ERROR;
    writel(0x11,audio_dev.reg_base  + ACW_RXFIFO_CTRL);//clear rx fifo
    writel(0x30029,audio_dev.reg_base + ACW_RXFIFO_CTRL);/*enable rx fifo*/

    return 0;

}


void playback_start_wq_handler(struct work_struct *work)
{
    int avail;
    unsigned int rx_status;
    while(1)
    {
        if (stopping == audio_dev.audio_config->playback.state)
        {
            return;
        }
        avail = avail_data_len(playback, audio_dev.audio_config);
        if (avail < audio_dev.audio_config->playback.cfg.period_bytes)
        {
            rt_thread_sleep(0);
        }
        else
        {
            rx_status = readl( audio_dev.reg_base + ACW_TXFIFO_CTRL);//clear rx fifo
            rx_status =  rx_status|(1<<4);
            writel(rx_status,audio_dev.reg_base + ACW_TXFIFO_CTRL);
            writel(0x30029, audio_dev.reg_base + ACW_TXFIFO_CTRL);
            break;
        }
    }
}

int fh_acw_start_playback(struct fh_audio_cfg *audio_config)
{
    int ret;

    if(audio_config->playback.state == running)
    {
        rt_kprintf("playback is running \n");
        return 0;
    }

    if (audio_config->playback.cfg.buffer_bytes >= AUDIO_DMA_PREALLOC_SIZE)
    {
        rt_kprintf("DMA prealloc buffer is smaller than  audio_config->buffer_bytes %x\n",audio_config->playback.cfg.buffer_bytes);
        return -ENOMEM;
    }
    reset_dma_buff(playback,audio_config);
    rt_memset(audio_config->playback.area, 0, audio_config->playback.cfg.buffer_bytes);
    audio_config->playback.size = audio_config->playback.cfg.buffer_bytes;
    audio_config->playback.state = running;
    ret =  audio_request_playback_channel(audio_config);
    if(ret){
    	rt_kprintf("can't request playback channel\n");
    	return ret;
    }
    ret = register_tx_dma(audio_config);
    if (ret < 0)
    {
    	rt_kprintf("can't register tx dma\n");
        return ret;
    }
    rt_list_init(&(playback_wq.list));
    playback_wq.work_func = (void *)playback_start_wq_handler;
    playback_wq.work_data = RT_NULL;
    playback_queue = rt_workqueue_create("play_workqueue",WORK_QUEUE_STACK_SIZE,WORK_QUEUE_PRIORITY);
    if(!playback_queue){

        rt_kprintf("init work_queue error....\n");
        return -1;
    }
    rt_workqueue_dowork(playback_queue,&playback_wq);
    return 0;
}

int fh_acw_start_capture(struct fh_audio_cfg *audio_config)
{
	int ret;
    if(audio_config->capture.state == running)
    {
        return 0;
    }
    if (audio_config->capture.cfg.buffer_bytes >= AUDIO_DMA_PREALLOC_SIZE)
    {
        rt_kprintf("DMA prealloc buffer is smaller than  audio_config->buffer_bytes %x\n",audio_config->capture.cfg.buffer_bytes);
        return -ENOMEM;
    }
    reset_dma_buff(capture,audio_config);
    rt_memset(audio_config->capture.area, 0, audio_config->capture.cfg.buffer_bytes);
    audio_config->capture.size = audio_config->capture.cfg.buffer_bytes;
    audio_config->capture.state = running;
    ret = audio_request_capture_channel(audio_config);
    if(ret){
    	rt_kprintf("can't request capture channel \n");
    	return ret;
    }

    return register_rx_dma(audio_config);
}

static void fh_acw_rx_dma_done(struct fh_audio_cfg *arg)
{
#if 1
    struct fh_audio_cfg *audio_config;
    audio_config = arg;

    audio_config->capture.hw_ptr += audio_config->capture.cfg.period_bytes;

    if (audio_config->capture.hw_ptr > audio_config->capture.size ) // TBD_WAIT ...
    {
        audio_config->capture.hw_ptr = audio_config->capture.hw_ptr - audio_config->capture.size;

    }

    int avail = avail_data_len(capture,audio_config);
    if (avail > audio_config->capture.cfg.period_bytes)
    {
        rt_sem_release(&audio_config->sem_capture);
    }
#endif
}

static void fh_acw_tx_dma_done(void *arg)
{
#if 1
    struct fh_audio_cfg *audio_config;
    audio_config = ( struct fh_audio_cfg *)arg;


    audio_config->playback.hw_ptr +=  audio_config->playback.cfg.period_bytes;

    if (audio_config->playback.hw_ptr > audio_config->playback.size )
    {

        audio_config->playback.hw_ptr = audio_config->playback.hw_ptr - audio_config->playback.size;
    }

	int avail = avail_data_len(playback,audio_config);
	if (avail > audio_config->playback.cfg.period_bytes)
	{

		rt_sem_release(&audio_config->sem_playback);
	}

#endif
}

bool  fh_acw_dma_chan_filter(struct dma_chan *chan, void *filter_param)
{

}

int arg_config_support(struct fh_audio_cfg_arg * cfg)
{
    int ret;

    ret = get_param_from_volume(cfg->volume);
    if (ret < 0) {
    	rt_kprintf("invalid volume\n");
        return -EINVAL;
    }
    ret = get_factor_from_table(cfg->rate);
    if (ret < 0) {
    	rt_kprintf("invalid rate\n");
        return -EINVAL;
    }
    return 0;
}

void reset_dma_buff(enum audio_type type, struct fh_audio_cfg *audio_config)
{
    if (capture == type)
    {
        audio_config->capture.appl_ptr = 0;
        audio_config->capture.hw_ptr = 0;
    }
    else
    {
        audio_config->playback.appl_ptr = 0;
        audio_config->playback.hw_ptr = 0;
    }
}


static rt_err_t fh_audio_ioctl(rt_device_t dev, int cmd, void *arg)
{
    struct fh_audio_cfg_arg *cfg;

    struct fh_audio_cfg  *audio_config = (struct fh_audio_cfg *)dev->user_data;
    int ret;
    int reg;
    int value,pid;
    int  *p = (int  *)arg;
    int rx_status,tx_status;

    switch (cmd)
    {
        case AC_INIT_CAPTURE_MEM:

            cfg = (struct fh_audio_cfg_arg *)arg;
            if (0 == arg_config_support(cfg))
            {
                audio_config->capture.cfg.io_type = cfg->io_type;
                audio_config->capture.cfg.volume = cfg->volume;
                audio_config->capture.cfg.rate = cfg->rate;
                audio_config->capture.cfg.channels = cfg->channels;
                audio_config->capture.cfg.buffer_size = cfg->buffer_size;
                audio_config->capture.cfg.frame_bit = FIX_SAMPLE_BIT;
                audio_config->capture.cfg.period_size = cfg->period_size;
                audio_config->capture.cfg.buffer_bytes = frames_to_bytes(audio_config->capture.cfg.frame_bit,audio_config->capture.cfg.buffer_size);
                audio_config->capture.cfg.period_bytes = frames_to_bytes(audio_config->capture.cfg.frame_bit,audio_config->capture.cfg.period_size);
                audio_config->capture.cfg.start_threshold =audio_config->capture.cfg.buffer_bytes;
                audio_config->capture.cfg.stop_threshold = audio_config->capture.cfg.buffer_bytes;
                audio_prealloc_dma_buffer((int)cfg->io_type,audio_config);
                reset_dma_buff(capture, audio_config);

                rt_mutex_init(&audio_config->capture.lock, "audio_c", RT_IPC_FLAG_PRIO);
                init_audio(capture, audio_config);
                audio_param_store.input_io_type = audio_config->capture.cfg.io_type;
                audio_param_store.input_volume = audio_config->capture.cfg.volume;

            }
            else
            {
                return -EINVAL;
            }

            break;
        case AC_INIT_PLAYBACK_MEM:
            cfg = arg;

            if (0 == arg_config_support(cfg))
            {
                audio_config->playback.cfg.io_type = cfg->io_type;
                audio_config->playback.cfg.volume = cfg->volume;
                audio_config->playback.cfg.rate = cfg->rate;
                audio_config->playback.cfg.channels = cfg->channels;
                audio_config->playback.cfg.buffer_size = cfg->buffer_size;
                audio_config->playback.cfg.frame_bit = FIX_SAMPLE_BIT;
                audio_config->playback.cfg.period_size = cfg->period_size;
                audio_config->playback.cfg.buffer_bytes = frames_to_bytes(audio_config->playback.cfg.frame_bit,audio_config->playback.cfg.buffer_size);
                audio_config->playback.cfg.period_bytes = frames_to_bytes(audio_config->playback.cfg.frame_bit,audio_config->playback.cfg.period_size);
                audio_config->playback.cfg.start_threshold =audio_config->playback.cfg.buffer_bytes;
                audio_config->playback.cfg.stop_threshold = audio_config->playback.cfg.buffer_bytes;
                audio_prealloc_dma_buffer((int)cfg->io_type,audio_config); // TBD_WAIT ...
                reset_dma_buff(playback, audio_config);

                rt_mutex_init(&audio_config->playback.lock, "audio_p", RT_IPC_FLAG_PRIO);

                init_audio(playback, audio_config);

            }
            else
            {
                return -EINVAL;
            }
            break;
        case AC_AI_EN:
            return fh_acw_start_capture(audio_config);
        case AC_AO_EN:
            rt_kprintf("ao en \n");
            return fh_acw_start_playback(audio_config);

        case AC_SET_VOL:
            value = *(rt_uint32_t *)arg;
            ret = get_param_from_volume(value);
            if (ret < 0) {
                return -EINVAL;
            }
            audio_param_store.input_volume = value;
            switch_input_volume(audio_param_store.input_volume);
            break;
        case AC_SET_INPUT_MODE:

            value = *(rt_uint32_t *)arg;
            if (value != mic_in && value != line_in) {
                return -EINVAL;
            }
            audio_param_store.input_io_type = value;
            switch_io_type(capture, audio_param_store.input_io_type);
            break;
        case AC_SET_OUTPUT_MODE:
            value = *(rt_uint32_t *)arg;

            if (value != speaker_out && value != line_out) {
                return -EINVAL;
            }
            switch_io_type(playback, value);
            break;
        case AC_AI_DISABLE:
            rt_kprintf(" AC_AI_DISABLE\n");

            fh_acw_stop_capture(audio_config);
            if (audio_config->capture_trans != RT_NULL)
            {
                rt_free(audio_config->capture_trans);
                audio_config->capture_trans = NULL;
            }
            break;
        case AC_AO_DISABLE:
            rt_kprintf("[ac_driver]AC_AO_DISABLE\n");

            fh_acw_stop_playback(audio_config);
            if (audio_config->plauback_trans != RT_NULL)
            {
                rt_free(audio_config->plauback_trans);
                audio_config->plauback_trans = NULL;
            }
            rt_kprintf(" AC_AO_DISABLE\n");
            break;
        case AC_AI_PAUSE:

            rt_kprintf( "capture pause\n");
            rx_status = readl(audio_dev.reg_base + ACW_RXFIFO_CTRL);/*rx fifo disable*/
            rx_status =  rx_status&(~(1<<0));
            writel(rx_status, audio_dev.reg_base + ACW_RXFIFO_CTRL);/*rx fifo disable*/
            break;
        case AC_AI_RESUME:

            rt_kprintf( "capture resume\n");
            rx_status = readl( audio_dev.reg_base + ACW_RXFIFO_CTRL);//clear rx fifo
            rx_status =  rx_status|(1<<4);
            writel(rx_status,audio_dev.reg_base+ ACW_RXFIFO_CTRL);/*enable rx fifo*/
            rx_status =  rx_status&(~(1<<4));
            rx_status =  rx_status|(1<<0);
            writel(rx_status,audio_dev.reg_base + ACW_RXFIFO_CTRL);/*enable rx fifo*/
            break;
        case AC_AO_PAUSE:

            rt_kprintf( "playback pause\n");
            tx_status = readl(audio_dev.reg_base + ACW_TXFIFO_CTRL);/*rx fifo disable*/
            tx_status =  tx_status&(~(1<<0));
            writel(tx_status, audio_dev.reg_base + ACW_TXFIFO_CTRL);/*tx fifo disable*/
            break;
        case AC_AO_RESUME:

            rt_kprintf( "playback resume\n");
            tx_status = readl( audio_dev.reg_base + ACW_TXFIFO_CTRL);//clear rx fifo
            tx_status =  tx_status|(1<<0);
            writel(tx_status,audio_dev.reg_base + ACW_TXFIFO_CTRL); //enable tx fifo read enable
            break;
        default:
            return -ENOTTY;
    }
    return 0;
}

static rt_err_t fh_audio_open(rt_device_t dev, rt_uint16_t oflag)
{

    unsigned int reg;
    struct fh_audio_cfg  *audio_config = dev->user_data;
    //enable interrupts
    reg = readl(audio_dev.reg_base + ACW_CTRL);
    reg |= 0xa;
    writel(reg, audio_dev.reg_base + ACW_CTRL);

    return 0;
}

static rt_err_t fh_audio_tx_poll(rt_device_t dev, void *buffer){
    struct fh_audio_cfg  *audio_config = dev->user_data;
      unsigned int mask = 0;
        long avail;

        if (running == audio_config->playback.state)
        {

            rt_sem_take(&audio_config->sem_playback, RT_WAITING_FOREVER);
            avail = avail_data_len(playback, audio_config);
            if (avail >  audio_config->playback.cfg.period_bytes)
            {
                mask |=  POLLOUT | POLLWRNORM;
            }
        }

        return mask;
}

static rt_err_t fh_audio_rx_poll(rt_device_t dev, rt_size_t size){

    struct fh_audio_cfg  *audio_config = dev->user_data;
      unsigned int mask = 0;
        long avail;
        if (running == audio_config->capture.state)
        {
            rt_sem_take(&audio_config->sem_capture, RT_WAITING_FOREVER);
            avail = avail_data_len(capture, audio_config);
            if (avail >  audio_config->capture.cfg.period_bytes)
            {
                mask |=  POLLIN | POLLRDNORM;
            }
        }
        return mask;
}
static dma_complete_callback mem_complete(void *p){

    struct rt_completion *completion = (struct rt_completion *)p;

    rt_completion_done(completion);
}

static rt_size_t fh_audio_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{

    int ret;
    struct fh_audio_cfg  *audio_config = dev->user_data;
    int after,left;
    int pid,avail;



    avail = avail_data_len(capture, audio_config);
    if (avail > size)
    {
        avail = size;
    }
    after = avail + audio_config->capture.appl_ptr;
    if(after  > audio_config->capture.size)
    {
        left = avail - (audio_config->capture.size - audio_config->capture.appl_ptr);
        rt_memcpy(buffer, audio_config->capture.area+audio_config->capture.appl_ptr, audio_config->capture.size-audio_config->capture.appl_ptr);
        rt_memcpy(buffer+audio_config->capture.size-audio_config->capture.appl_ptr,audio_config->capture.area,left);
        rt_mutex_take(&audio_config->capture.lock, RT_WAITING_FOREVER);
        audio_config->capture.appl_ptr = left;
        rt_mutex_release(&audio_config->capture.lock);

    }
    else
    {
        rt_memcpy(buffer,audio_config->capture.area+audio_config->capture.appl_ptr,avail);
        rt_mutex_take(&audio_config->capture.lock, RT_WAITING_FOREVER);
        audio_config->capture.appl_ptr += avail;
        rt_mutex_release(&audio_config->capture.lock);

    }
    return avail;

}

static rt_size_t fh_audio_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{

    struct fh_audio_cfg  *audio_config = dev->user_data;
    int  ret;
    int after,left;
    int pid,avail;

    avail = avail_data_len(playback,audio_config);
    if (0 == avail)
    {
        return 0;
    }
    if (avail > size)
    {
        avail = size;
    }
    after = avail+audio_config->playback.appl_ptr;
    if(after  > audio_config->playback.size)
    {
        left = avail - (audio_config->playback.size-audio_config->playback.appl_ptr);
        rt_memcpy(audio_config->playback.area+audio_config->playback.appl_ptr,buffer,audio_config->playback.size-audio_config->playback.appl_ptr);
        rt_memcpy(audio_config->playback.area,buffer+audio_config->playback.size-audio_config->playback.appl_ptr,left);
        rt_mutex_take(&audio_config->playback.lock, RT_WAITING_FOREVER);
        audio_config->playback.appl_ptr = left;
        rt_mutex_release(&audio_config->playback.lock);

    }
    else
    {
        rt_memcpy(audio_config->playback.area+audio_config->playback.appl_ptr,buffer,avail);
        rt_mutex_take(&audio_config->playback.lock, RT_WAITING_FOREVER);
        audio_config->playback.appl_ptr += avail;
        rt_mutex_release(&audio_config->playback.lock);
    }
     return avail;
}

static void fh_audio_interrupt(int irq, void *param)
{
    unsigned int interrupts, reg;
    struct fh_audio_cfg  *audio_config = audio_dev.audio_config;

    interrupts = readl(audio_dev.reg_base + ACW_CTRL);
    writel(interrupts, audio_dev.reg_base + ACW_CTRL);

    if(interrupts & ACW_INTR_RX_UNDERFLOW)
    {
        fh_acw_stop_capture(audio_config);
        fh_acw_start_capture(audio_config);
        rt_kprintf("ACW_INTR_RX_UNDERFLOW\n");
    }

    if(interrupts & ACW_INTR_RX_OVERFLOW)
    {
        fh_acw_stop_capture(audio_config);
        fh_acw_start_capture(audio_config);
        rt_kprintf("ACW_INTR_RX_OVERFLOW\n");
    }

    if(interrupts & ACW_INTR_TX_UNDERFLOW)
    {
        fh_acw_stop_capture(audio_config);
        fh_acw_start_capture(audio_config);
        rt_kprintf("ACW_INTR_TX_UNDERFLOW\n");
    }

    if(interrupts & ACW_INTR_TX_OVERFLOW)
    {
        fh_acw_stop_capture(audio_config);
        fh_acw_start_capture(audio_config);
        rt_kprintf("ACW_INTR_TX_OVERFLOW\n");
    }

    rt_kprintf("interrupts: 0x%x\n", interrupts);


}


void audio_prealloc_dma_buffer(int aiaotype,struct fh_audio_cfg  *audio_config)
{

	 if(aiaotype == mic_in || aiaotype == line_in){
    audio_config->capture.area  = (void *)fh_dma_mem_malloc(audio_config->capture.cfg.buffer_bytes \
            + audio_config->capture.cfg.period_bytes);

    if (!audio_config->capture.area)
    {
        rt_kprintf("no enough mem for capture  buffer alloc\n");
        return ;
    }
	 }
	 if(aiaotype == speaker_out || aiaotype == line_out){
    audio_config->playback.area  = (void *)fh_dma_mem_malloc(audio_config->playback.cfg.buffer_bytes \
            + audio_config->playback.cfg.period_bytes);

    if (!audio_config->playback.area)
    {
        rt_kprintf("no enough mem for  playback buffer alloc\n");
        return ;
    }}

}

void audio_free_prealloc_dma_buffer(struct fh_audio_cfg  *audio_config)
{

    rt_free( audio_config->capture.area);
    rt_free( audio_config->playback.area);
}

static void init_audio_mutex(struct fh_audio_cfg  *audio_config)
{
    rt_sem_init(&audio_config->sem_capture, "sem_capture", 0, RT_IPC_FLAG_FIFO);
    rt_sem_init(&audio_config->sem_playback, "sem_playback", 0, RT_IPC_FLAG_FIFO);
}
int audio_request_capture_channel(struct fh_audio_cfg  *audio_config){
    struct rt_dma_device *rt_dma_dev;
    /*request audio rx dma channel*/
    struct dma_transfer *dma_rx_transfer;
    int ret;
    dma_rx_transfer = rt_malloc(sizeof(struct dma_transfer));

    if (!dma_rx_transfer)
    {
        rt_kprintf("alloc  dma_rx_transfer failed\n");
        return RT_ENOMEM;
    }

    rt_memset(dma_rx_transfer, 0, sizeof(struct dma_transfer));
    rt_dma_dev = (struct rt_dma_device *)rt_device_find("fh81_dma");

    if(rt_dma_dev == RT_NULL){
        rt_kprintf("can't find dma dev\n");

        return -1;
    }
    audio_config->capture_dma = rt_dma_dev;
    audio_config->capture_trans = dma_rx_transfer;
    rt_dma_dev->ops->init(rt_dma_dev);

    dma_rx_transfer->channel_number = ACW_CAP_DMA_CHAN;

    dma_rx_transfer->dma_number = 0;

    dma_rx_transfer->dst_add = (rt_uint32_t)audio_config->capture.area;//audio_config->capture.area;//(rt_uint32_t)&tx_buff[0];
    dma_rx_transfer->dst_inc_mode = DW_DMA_SLAVE_INC;
    dma_rx_transfer->dst_msize = DW_DMA_SLAVE_MSIZE_32;

    dma_rx_transfer->dst_width = DW_DMA_SLAVE_WIDTH_32BIT;
    dma_rx_transfer->fc_mode = DMA_P2M;

    dma_rx_transfer->src_add = (rt_uint32_t)ACW_RXFIFO;

    dma_rx_transfer->src_inc_mode = DW_DMA_SLAVE_FIX;
    dma_rx_transfer->src_msize = DW_DMA_SLAVE_MSIZE_32;
    dma_rx_transfer->src_hs = DMA_HW_HANDSHAKING;
    dma_rx_transfer->src_width = DW_DMA_SLAVE_WIDTH_32BIT;
    dma_rx_transfer->trans_len = (audio_config->capture.cfg.buffer_bytes / 4); // DW_DMA_SLAVE_WIDTH_32BIT BUFF_SIZE;
    dma_rx_transfer->src_per =ACODEC_RX;
    dma_rx_transfer->period_len = audio_config->capture.cfg.period_bytes / 4;// (audio_config->capture.cfg.period_bytes / 4); // TEST_PER_NO;
    dma_rx_transfer->complete_callback =(dma_complete_callback)fh_acw_rx_dma_done;
    dma_rx_transfer->complete_para = audio_config;

    rt_dma_dev->ops->control(rt_dma_dev,RT_DEVICE_CTRL_DMA_OPEN,dma_rx_transfer);
    ret = rt_dma_dev->ops->control(rt_dma_dev,RT_DEVICE_CTRL_DMA_REQUEST_CHANNEL,dma_rx_transfer);
    if(ret){
    	rt_kprintf("can't request capture channel\n");
    	dma_rx_transfer->channel_number =0xff;
    	return -ret;
    }

}

int audio_request_playback_channel(struct fh_audio_cfg  *audio_config)
{
    struct rt_dma_device *rt_dma_dev;
    int ret;
    struct dma_transfer *dma_tx_transfer;
    dma_tx_transfer = rt_malloc(sizeof(struct dma_transfer));
    if (!dma_tx_transfer)
    {
        rt_kprintf("alloc  dma_tx_transfer failed\n");
        return RT_ENOMEM;

    }
    audio_config->plauback_trans = dma_tx_transfer;
    rt_dma_dev = (struct rt_dma_device *)rt_device_find("fh81_dma");

    if(rt_dma_dev == RT_NULL){
        rt_kprintf("can't find dma dev\n");
        return -1;
    }
    rt_dma_dev->ops->init(rt_dma_dev);
    audio_config->playback_dma = rt_dma_dev;

    rt_memset(dma_tx_transfer, 0, sizeof(struct dma_transfer));
    dma_tx_transfer->channel_number = ACW_PLY_DMA_CHAN;
    dma_tx_transfer->dma_number = 0;
    dma_tx_transfer->dst_add = (rt_uint32_t)ACW_TXFIFO;
    dma_tx_transfer->dst_hs = DMA_HW_HANDSHAKING;
    dma_tx_transfer->dst_inc_mode = DW_DMA_SLAVE_FIX;
    dma_tx_transfer->dst_msize = DW_DMA_SLAVE_MSIZE_32;
    dma_tx_transfer->dst_per = ACODEC_TX;
    dma_tx_transfer->dst_width = DW_DMA_SLAVE_WIDTH_32BIT;
    dma_tx_transfer->fc_mode = DMA_M2P;
    dma_tx_transfer->src_add = (rt_uint32_t)audio_config->playback.area;
    dma_tx_transfer->src_inc_mode = DW_DMA_SLAVE_INC;
    dma_tx_transfer->src_msize = DW_DMA_SLAVE_MSIZE_32;
    dma_tx_transfer->src_width = DW_DMA_SLAVE_WIDTH_32BIT;
    dma_tx_transfer->trans_len = (audio_config->playback.cfg.buffer_bytes / 4);// BUFF_SIZE;
    dma_tx_transfer->period_len =  (audio_config->playback.cfg.period_bytes / 4); // TEST_PER_NO;
    dma_tx_transfer->complete_callback =(dma_complete_callback)fh_acw_tx_dma_done;
    dma_tx_transfer->complete_para = audio_config;
    rt_dma_dev->ops->control(rt_dma_dev,RT_DEVICE_CTRL_DMA_OPEN,dma_tx_transfer);
    ret = rt_dma_dev->ops->control(rt_dma_dev,RT_DEVICE_CTRL_DMA_REQUEST_CHANNEL,dma_tx_transfer);
    if(ret){
    	rt_kprintf("can't request playbak channel\n");
    	dma_tx_transfer->channel_number = 0xff;
    	return -ret;
    }
    return 0;

}

void audio_release_dma_channel(struct fh_audio_cfg  *audio_config)
{

    if (audio_config->plauback_trans != RT_NULL)
    {
        audio_config->playback_dma->ops->control(audio_config->playback_dma,RT_DEVICE_CTRL_DMA_RELEASE_CHANNEL,audio_config->plauback_trans);
        rt_free(audio_config->plauback_trans);
        audio_config->plauback_trans = NULL;
    }


    if (audio_config->capture_trans != RT_NULL)
    {
        audio_config->capture_dma->ops->control(audio_config->capture_dma,RT_DEVICE_CTRL_DMA_RELEASE_CHANNEL,audio_config->capture_trans);
        rt_free(audio_config->capture_trans);
        audio_config->capture_trans = NULL;
    }


}

void  fh_audio_init(void)
{

     struct fh_audio_cfg  *audio_config;
     audio_config = rt_malloc(sizeof(struct fh_audio_cfg));
     memset(audio_config,0,sizeof(struct fh_audio_cfg)); // new add

     audio_dev.reg_base = 0xf0a00000;
     init_audio_mutex(audio_config);

     rt_device_t audio ;
     audio = rt_malloc(sizeof(struct rt_device));
     if (audio == RT_NULL){
         rt_kprintf("%s no mem \n",__func__);
     }

     audio->user_data = audio_config;
     audio->open =fh_audio_open;
     audio->read = fh_audio_read;
     audio->write = fh_audio_write;
     audio->close = fh_audio_close;
     audio->control = fh_audio_ioctl;
     audio->rx_indicate =fh_audio_rx_poll;
     audio->tx_complete=fh_audio_tx_poll;
     audio_dev.audio_config = audio_config; // TBD_WAIT 2015.09.17 add

     rt_device_register(audio, "audio", RT_DEVICE_FLAG_RDWR);

}



#if ACW_SELFTEST

#define TEST_FN        "/audio.dat"

static rt_uint32_t rx_buff[BUFF_SIZE] __attribute__((aligned(32))) ;
static const rt_uint32_t tx_buff[BUFF_SIZE*2] __attribute__((aligned(32)))= {
        0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,
        0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,
        0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,
        0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,
        0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,

};





 struct fh_audio_cfg_arg cfg;

void fh_acw_test(){
    rt_device_t acw_dev ;
    int i;
    int output=3;
    int select;
    int select_rx_status =0;
    int select_tx_status =0;
    int fd;
    int index, length;
    int mic_boost=1;
    int ret;
    acw_dev = ( rt_device_t )rt_device_find("audio");
    for(i=0;i<BUFF_SIZE;i++)
        rx_buff[i] = i*0x500;
    acw_dev->open(acw_dev,0);
    cfg.buffer_size = BUFF_SIZE;
    cfg.channels =0;
    cfg.frame_bit = 16;

    cfg.io_type = mic_in;
    
    cfg.period_size = BUFF_SIZE/8;
    cfg.rate = 8000;
    cfg.volume = 80;

//    for(i=0;i<100;i++){
//    acw_dev->control(acw_dev,AC_INIT_CAPTURE_MEM,&cfg);
//
//    acw_dev->control(acw_dev,AC_AI_EN,&cfg);
//    cfg.io_type = line_out;
//    acw_dev->control(acw_dev,AC_INIT_PLAYBACK_MEM,&cfg);
//    acw_dev->control(acw_dev,AC_AO_EN,&cfg);
//    acw_dev->control(acw_dev,AC_SET_OUTPUT_MODE,&output);
//    acw_dev->control(acw_dev,AC_AI_DISABLE,&cfg);
//
//    acw_dev->control(acw_dev,AC_AO_DISABLE,&cfg);
//    rt_kprintf(" %d \n",i);
//    }

    cfg.io_type = mic_in;
    acw_dev->control(acw_dev,AC_INIT_CAPTURE_MEM,&cfg);

    ret = acw_dev->control(acw_dev,AC_AI_EN,&cfg);
    if(ret)
    	acw_dev->control(acw_dev,AC_AI_DISABLE,&cfg);
    cfg.io_type = line_out;
    acw_dev->control(acw_dev,AC_INIT_PLAYBACK_MEM,&cfg);
    ret = acw_dev->control(acw_dev,AC_AO_EN,&cfg);
    if(ret){
    	acw_dev->control(acw_dev,AC_AO_DISABLE,&cfg);
   // acw_dev->control(acw_dev,AC_SET_OUTPUT_MODE,&output);
    	return ;
    }


	 for(i=0;i<100;i++)
 {

rx:
        select = acw_dev->rx_indicate(acw_dev,RT_NULL);
        if(!select)
        goto rx;


        acw_dev->read(acw_dev,0,&rx_buff[0],1024*8);

tx:
        select = acw_dev->tx_complete(acw_dev , RT_NULL);
        if(!select)
        goto tx;

        acw_dev->write(acw_dev,0,&rx_buff[0],1024*8);

    }
 	acw_dev->close(acw_dev);

}
#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(fh_acw_test, fh_acw_test);
#endif
#endif
#endif

