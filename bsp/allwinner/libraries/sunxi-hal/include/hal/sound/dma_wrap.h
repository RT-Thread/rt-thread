/*
* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
*
* Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
* the the people's Republic of China and other countries.
* All Allwinner Technology Co.,Ltd. trademarks are used with permission.
*
* DISCLAIMER
* THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
* IF YOU NEED TO INTEGRATE THIRD PARTY’S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
* IN ALLWINNERS’SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
* ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
* ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
* COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
* YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY’S TECHNOLOGY.
*
*
* THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
* PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
* THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
* OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
* NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef __DMA_WRAP_H_
#define __DMA_WRAP_H_
#include <hal_dma.h>
#include <hal_cache.h>
#include <hal_mem.h>

struct dma_chan {
    struct sunxi_dma_chan *dma_handle;
};

#if 0
static inline void dma_free_coherent(void *addr)
{
        void *malloc_ptr = NULL;
            if (!addr)
                    return;
            malloc_ptr = *(uint32_t *)((uint32_t *)addr - 1);
                hal_free(malloc_ptr);
}

static inline void *dma_alloc_coherent(size_t size)
{
        void *fake_ptr = NULL;
            void *malloc_ptr = NULL;

            malloc_ptr = hal_malloc(size + 64);
                if ((uint32_t)malloc_ptr & 0x3) {
                        snd_err("error: krhino_mm_alloc not align to 4 byte\r\n");
                        }
                fake_ptr = (uint32_t)(malloc_ptr + 64) & (~63);
                    *(uint32_t *)((uint32_t *)fake_ptr - 1) = malloc_ptr;

                    return fake_ptr;
}
#endif

static inline struct dma_chan *dma_request_channel(void)
{
    struct dma_chan *chan = NULL;
    hal_dma_chan_status_t status = 0;

    chan = calloc(1, sizeof(struct dma_chan));
    status = hal_dma_chan_request(&chan->dma_handle);
    if (status != HAL_DMA_CHAN_STATUS_FREE) {
        snd_err("request dma chan failed\n");
        free(chan);
        return NULL;
    }
    return chan;
}

static inline void dma_release_channel(struct dma_chan *chan)
{
    hal_dma_status_t status = 0;
    if (!chan)
        return;
    status = hal_dma_chan_free(chan->dma_handle);
    if (status != HAL_DMA_STATUS_OK)
        snd_err("free dma chan failed\n");
    free(chan);
}

static inline enum dma_status dmaengine_tx_status(struct dma_chan *chan,
            uint32_t *residue)
{
    return hal_dma_tx_status(chan->dma_handle, residue);
}

static inline int dmaengine_prep_dma_cyclic(
        struct dma_chan *chan, dma_addr_t buf_addr, size_t buf_len,
        size_t period_len, enum dma_transfer_direction dir)
{
    hal_dma_status_t status = 0;

    snd_print("[%s] line:%d buf_addr:0x%x, buf_len:0x%x, period_len:0x%x\n",
        __func__, __LINE__, buf_addr, buf_len, period_len);

    status = hal_dma_prep_cyclic(chan->dma_handle,
            (unsigned long)buf_addr, (unsigned long)buf_len,
            (unsigned long)period_len, dir);

    if (status != HAL_DMA_STATUS_OK) {
        snd_err("hal_dma_prep_cyclic failed\n");
        return -1;
    }
    return 0;
}

static inline int dmaengine_submit(struct dma_chan *chan,
            dma_callback callback, void *callback_param)
{
    hal_dma_status_t status = 0;

    snd_print("\n");
    status = hal_dma_callback_install(chan->dma_handle,
                callback, callback_param);
    if (status != HAL_DMA_STATUS_OK) {
        snd_err("hal_dma_prep_cyclic failed\n");
        return -1;
    }

    return 0;
}

static inline int dmaengine_slave_config(struct dma_chan *chan,
                                          struct dma_slave_config *config)
{
    hal_dma_status_t status = 0;

    snd_print("\n");
    status = hal_dma_slave_config(chan->dma_handle, config);
    if (status != HAL_DMA_STATUS_OK) {
        snd_err("hal_dma_slave_config failed\n");
        return -1;
    }

    return 0;
}

static inline void dma_async_issue_pending(struct dma_chan *chan)
{
    hal_dma_status_t status = 0;

    snd_print("\n");
    status = hal_dma_start(chan->dma_handle);
    if (status != HAL_DMA_STATUS_OK) {
        snd_err("hal_dma_start failed\n");
        return ;
    }

    return;
}

static inline int dmaengine_terminate_async(struct dma_chan *chan)
{
    hal_dma_status_t status = 0;

    status = hal_dma_stop(chan->dma_handle);
    if (status != HAL_DMA_STATUS_OK) {
        snd_err("hal_dma_stop failed\n");
        return -1;
    }

    status = hal_dma_chan_desc_free(chan->dma_handle);
    if (status != HAL_DMA_STATUS_OK) {
        snd_err("hal_dma_chan_desc_free failed, return:%d\n", status);
        return -1;
    }

    return 0;
}

static inline int dmaengine_pause(struct dma_chan *chan)
{
    printf("dma pause not support.\n");
    return -1;
}

static inline int dmaengine_resume(struct dma_chan *chan)
{
    printf("dma resume not support.\n");
    return -1;
}

#endif /* __DMA_WRAP_H_ */
