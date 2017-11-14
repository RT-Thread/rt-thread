/*
 * drv_aic_i2s.h
 *
 *  Created on: 2016年4月1日
 *      Author: Urey
 */

#ifndef DRIVER_DRV_AIC_I2S_H_
#define DRIVER_DRV_AIC_I2S_H_

#include "board.h"


#ifdef RT_USING_ICODEC
#	define CODEC_AS_MASTER

#define CODEC_DEF_RATE    (24000000)
#else
//#	undef CODEC_AS_MASTER
//#	define CODEC_AS_MASTER

#define CODEC_DEF_RATE    (44100)
#endif

#ifdef RT_USING_ECODEC_WM8978
#	define CFG_AIC_I2S_EXT_CODEC
#endif

#define CFG_AIC_SOC_CLKOUT
//#define CFG_AIC_SOC_CLKIN

#define CFG_I2S_DMA_PAGE_SIZE	(32 * 1024)
#define CFG_I2S_DMA_PAGE_NUM	8

enum
{
    I2S_TRIGGER_STOP  = 0,
    I2S_TRIGGER_START ,
	I2S_TRIGGER_PAUSE_PUSH ,
	I2S_TRIGGER_PAUSE_RELEASE ,
    I2S_TRIGGER_SUSPEND ,
    I2S_TRIGGER_RESUME,
};



/*********************************************************************************************************
**   数据结构
*********************************************************************************************************/
struct jz_i2s
{
    struct jz_aic   *aic;
    int i2s_init;
#define I2S_WRITE 0x1
#define I2S_READ  0x2
#define I2S_INCODEC (0x1 <<4)
#define I2S_EXCODEC (0x2 <<4)
#define I2S_SLAVE (0x1 << 8)
#define I2S_MASTER (0x2 << 8)
    int i2s_mode;
    uint32_t    tx_dr_base;

	int channels;
	int fmt_width;
	int rates;

    /* used for DMA transform */
    struct rt_dma_channel *tx_dmac;
    struct rt_dma_channel *rx_dmac;
};

/*********************************************************************************************************
**   函数申明
*********************************************************************************************************/
int aic_set_rate(struct jz_aic *aic, uint32_t freq);

struct jz_i2s *rt_hw_aic_i2s_init(void);

//void aic_i2s_start_substream(struct jz_i2s *i2s,int stream);
//void aic_i2s_stop_substream(struct jz_i2s *i2s,int stream);
int aic_i2s_set_sysclk(struct jz_i2s *i2s,uint32_t freq);
int aic_i2s_set_clkdiv(struct jz_i2s *i2s,int div_id, int div);
int aic_i2s_startup(struct jz_i2s *i2s,int stream);
int aic_i2s_trigger(struct jz_i2s* i2s,int cmd,int stream);

int aic_i2s_hw_params(struct jz_i2s* i2s,int stream);
void aic_i2s_shutdown(struct jz_i2s *i2s,int stream);

rt_size_t aic_i2s_send(struct jz_i2s *i2s, const void* buffer, rt_size_t size,void (*tx_callback)(void *,void *), void *tx_arg);
rt_size_t aic_i2s_recv(struct jz_i2s *i2s,        void* buffer, rt_size_t size,void (*rx_callback)(void *,void *), void *rx_arg);


void aic_i2s_set_rate(struct jz_i2s *i2s,int rate);
#endif /* DRIVER_DRV_AIC_I2S_H_ */
