/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-12-12      Wayne            First version
*
******************************************************************************/

#ifndef __DRV_I2S_H__
#define __DRV_I2S_H__

#include <rtthread.h>
#include <drv_sys.h>
#include "NuMicro.h"

#if !defined(NU_I2S_DMA_FIFO_SIZE)
    #define NU_I2S_DMA_FIFO_SIZE (2048)
#endif

#if !defined(NU_I2S_DMA_BUF_BLOCK_NUMBER)
    #define NU_I2S_DMA_BUF_BLOCK_NUMBER (2)
#endif

#if ( (NU_I2S_DMA_FIFO_SIZE % NU_I2S_DMA_BUF_BLOCK_NUMBER) != 0 )
    #error "Please give an aligned definition"
#endif
#if ( NU_I2S_DMA_FIFO_SIZE < 2048 )
    #warning "DMA FIFO too small, miss voice?"
#endif

#define NU_I2S_DMA_BUF_BLOCK_SIZE (NU_I2S_DMA_FIFO_SIZE/NU_I2S_DMA_BUF_BLOCK_NUMBER)

#if ( NU_I2S_DMA_BUF_BLOCK_SIZE > RT_AUDIO_RECORD_PIPE_SIZE )
    #error "Specified I2S DMA buffer size is small than PIPE size in RT driver."
    #error "You should enlarge RT_AUDIO_RECORD_PIPE_SIZE. "
#endif

typedef enum
{
    NU_I2S_DAI_PLAYBACK,
    NU_I2S_DAI_CAPTURE,
    NU_I2S_DAI_CNT
} E_NU_I2S_DAI;

typedef enum
{
    NU_ACODEC_ROLE_MASTER,
    NU_ACODEC_ROLE_SLAVE,
} E_NU_ACODEC_ROLE;

typedef struct
{
    char *name;

    E_NU_ACODEC_ROLE role;

    struct rt_audio_configure config;

    rt_err_t (*nu_acodec_init)(void);

    rt_err_t (*nu_acodec_reset)(void);

    rt_err_t (*nu_acodec_dsp_control)(struct rt_audio_configure *config);

    rt_err_t (*nu_acodec_mixer_control)(rt_uint32_t ui32Item, rt_uint32_t ui32Value);

    rt_err_t (*nu_acodec_mixer_query)(rt_uint32_t ui32Item, rt_uint32_t *ui32Value);

} nu_acodec_ops;

typedef nu_acodec_ops *nu_acodec_ops_t;

struct nu_i2s_dai
{
    rt_uint8_t *fifo;
};
typedef struct nu_i2s_dai *nu_i2s_dai_t;

struct nu_i2s
{
    struct rt_audio_device audio;
    struct rt_audio_configure config;

    char *name;
    IRQn_Type irqn;
    E_SYS_IPRST rstidx;
    E_SYS_IPCLK clkidx;

    struct nu_i2s_dai i2s_dais[NU_I2S_DAI_CNT];
    nu_acodec_ops_t AcodecOps;
};
typedef struct nu_i2s *nu_i2s_t;

#endif // __DRV_I2S_H___
