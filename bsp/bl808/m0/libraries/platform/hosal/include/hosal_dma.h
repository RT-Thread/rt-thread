/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __HOSAL_DMA_H__
#define __HOSAL_DMA_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup hosal_dma DMA
 *  HOSAL DMA API
 *
 *  @{
 */

#include <stdint.h>
#include <stdio.h>

/**
 * @brief DMA irq callback function flag
 */
#define HOSAL_DMA_INT_TRANS_COMPLETE      0
#define HOSAL_DMA_INT_TRANS_ERROR         1

/**
 * @brief DMA irq callback function
 */
typedef void (*hosal_dma_irq_t)(void *p_arg, uint32_t flag);

/**
 * @brief DMA channel describe
 */
struct hosal_dma_chan {
    uint8_t used;
    hosal_dma_irq_t callback;
    void *p_arg;
};

/**
 * @brief DMA device type
 */
typedef struct hosal_dma_dev {
    int max_chans;
    struct hosal_dma_chan *used_chan;
    void *priv;
} hosal_dma_dev_t;

/**
 * @brief DMA channel
 */
typedef int hosal_dma_chan_t;

/**
 * @brief Initialises a DMA interface
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int hosal_dma_init(void);

/**
 * @brief Request a DMA channel
 *
 * @param[in] flag : DMA CHAN REQUEST FLAG
 *
 * @return  < 0 : an error occurred with any step, otherwise is DMA channel number
 */
hosal_dma_chan_t hosal_dma_chan_request(int flag);

/**
 * @brief Release a DMA channel
 *
 * @param[in]  chan  DMA channel number
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int hosal_dma_chan_release(hosal_dma_chan_t chan);

/**
 * @brief DMA channel trans start
 *
 * @param[in]  chan  DMA channel number
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int hosal_dma_chan_start(hosal_dma_chan_t chan);

/**
 * @brief DMA channel trans stop
 *
 * @param[in]  chan  DMA channel number
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int hosal_dma_chan_stop(hosal_dma_chan_t chan);

/**
 * @brief DMA irq callback set
 *
 * @param[in] chan : DMA channel number
 * @param[in] pfn : callback function
 * @param[in] arg : callback function parameter
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int hosal_dma_irq_callback_set(hosal_dma_chan_t chan, hosal_dma_irq_t pfn, void *p_arg);

/**
 * @brief Deinitialises a DMA interface
 *
 * @param[in]  DMA the interface which should be deinitialised
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int hosal_dma_finalize(void);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __HOSAL_DMA_H__ */

/* end of file */
