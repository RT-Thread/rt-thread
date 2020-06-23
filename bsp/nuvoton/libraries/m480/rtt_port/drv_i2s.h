/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-2-7        Wayne            First version
*
******************************************************************************/

#ifndef __DRV_I2S_H__
#define __DRV_I2S_H__

#include <rtdevice.h>
#include <NuMicro.h>
#include <drv_pdma.h>

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
    int16_t pdma_perp;
    int8_t  pdma_chanid;
    rt_uint8_t *fifo;
    int16_t  fifo_block_idx;
    nu_pdma_desc_t pdma_descs[NU_I2S_DMA_BUF_BLOCK_NUMBER];
};
typedef struct nu_i2s_dai *nu_i2s_dai_t;

struct nu_i2s
{
    struct rt_audio_device audio;
    struct rt_audio_configure config;

    char *name;
    I2S_T *i2s_base;
    uint32_t i2s_rst;

    struct nu_i2s_dai i2s_dais[NU_I2S_DAI_CNT];
    nu_acodec_ops_t AcodecOps;
};
typedef struct nu_i2s *nu_i2s_t;

#endif // __DRV_I2S_H___
