/* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.

 * Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
 * the the People's Republic of China and other countries.
 * All Allwinner Technology Co.,Ltd. trademarks are used with permission.

 * DISCLAIMER
 * THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
 * IF YOU NEED TO INTEGRATE THIRD PARTY’S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
 * IN ALLWINNERS’SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
 * ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
 * ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
 * COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
 * YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY’S TECHNOLOGY.


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

#include <stdlib.h>
#include <string.h>
#include <interrupt.h>
#include <hal_cache.h>
#include <hal_mem.h>
#include <hal_osal.h>
#include <hal_sem.h>
#include <hal_timer.h>
#include <sunxi_hal_ce.h>
#include "ce_common.h"
#include "hal_ce.h"
#include "ce_reg.h"
#include "platform_ce.h"

//#define CE_NO_IRQ
#define CE_WAIT_TIME    (50000)

#ifndef CE_NO_IRQ
static hal_sem_t ce_sem;
#endif
//static rt_wqueue_t ce_wqueue;

void ce_print_hex(char *_data, int _len, void *_addr)
{
    int i, j;
    char last[128] = {0};

    CE_DBG("---------------- The valid len = %d ----------------\n",
        _len);
    for (i = 0; i < _len/8; i++) {
        CE_DBG("%p: %02X %02X %02X %02X %02X %02X %02X %02X\n",
            i*8 + _addr,
            _data[i*8+0], _data[i*8+1], _data[i*8+2], _data[i*8+3],
            _data[i*8+4], _data[i*8+5], _data[i*8+6], _data[i*8+7]);
    }
    for (j = 0; j < _len%8; j++) {
        if (j == 0)
            snprintf(last, 12, "%p:", i * 8 + _addr);
        snprintf(last + 11 + j*3, 4, " %02X", _data[i*8 + j]);
        if (j == _len % 8 - 1)
            CE_DBG("%s\n", last);
    }
    CE_DBG("----------------------------------------------------\n");
}

void ce_print_task_info(ce_task_desc_t *task)
{
    CE_DBG("-----------task_info------\n");
    CE_DBG("task = 0x%lx\n", (uint32_t)task);
    CE_DBG("task->comm_ctl = 0x%lx\n", task->comm_ctl);
    CE_DBG("task->sym_ctl = 0x%lx\n", task->sym_ctl);
    CE_DBG("task->asym_ctl = 0x%lx\n", task->asym_ctl);
    CE_DBG("task->chan_id = 0x%lx\n", task->chan_id);
    CE_DBG("task->ctr_addr = 0x%lx\n", task->ctr_addr);
    CE_DBG("task->data_len = 0x%lx\n", task->data_len);
    CE_DBG("task->iv_addr = 0x%lx\n", task->iv_addr);
    CE_DBG("task->key_addr = 0x%lx\n", task->key_addr);
    CE_DBG("task->src[0].addr = 0x%lx\n", task->src[0].addr);
    CE_DBG("task->src[0].len = 0x%lx\n", task->src[0].len);
    CE_DBG("task->dst[0].addr = 0x%lx\n", task->dst[0].addr);
    CE_DBG("task->dst[0].len = 0x%lx\n", task->dst[0].len);
}

#ifndef CE_NO_IRQ
static hal_irqreturn_t ce_irq_handler(void *data)
{
    int i;
    int ret;
    int pending = 0;

    pending = hal_ce_pending_get();
    for (i = 0; i < CE_FLOW_NUM; i++) {
        if (pending & (CE_CHAN_PENDING << i)) {
            CE_DBG("Chan %d completed. pending: %#x\n", i, pending);
            hal_ce_pending_clear(i);
            ret = hal_sem_post(ce_sem);
            if (ret == 0) {
                ;
            } else {
                CE_ERR("hal_sem_post FAIL \n");
            }
#if 0
            rt_wqueue_wakeup(&ce_wqueue, NULL);
#endif
        }
    }

    return HAL_IRQ_OK;
}

static int ce_irq_request(void)
{
#ifdef CONFIG_ARCH_SUN20IW2P1
    uint32_t irqn = SUNXI_IRQ_CE_NS;

    if (hal_request_irq(irqn, ce_irq_handler, "ce", NULL) < 0) {
        CE_ERR("request irq error\n");
        return -1;
    }

    hal_enable_irq(irqn);
#else
    uint32_t irqn = SUNXI_IRQ_CE;

    if (request_irq(irqn, ce_irq_handler, 0, "crypto", NULL) < 0) {
        CE_ERR("Cannot request IRQ\n");
        return -1;
    }

    enable_irq(irqn);
#endif

    return 0;
}
#endif

int sunxi_ce_init(void)
{
    int ret = 0;

    hal_ce_clock_init();
#ifndef CE_NO_IRQ
    ret = ce_irq_request();
    if (ret < 0) {
        return -1;
    }

    ce_sem = hal_sem_create(0);
    if (ce_sem == NULL) {
        CE_ERR("hal_sem_create fail\n");
        return -1;
    }
#endif

#if 0
    rt_wqueue_init(&ce_wqueue);
#endif

    return 0;
}

int sunxi_ce_uninit(void)
{
#ifndef CE_NO_IRQ
    if (ce_sem)
        hal_sem_delete(ce_sem);

#ifdef CONFIG_ARCH_SUN20IW2P1
    hal_free_irq(SUNXI_IRQ_CE_NS);
#else
    hal_free_irq(SUNXI_IRQ_CE);
#endif
#endif

    return 0;
}

static void ce_task_desc_init(ce_task_desc_t *task, uint32_t flow)
{
    memset((void *)task, 0x0, sizeof(ce_task_desc_t));
    task->chan_id = flow;
    hal_ce_task_enable(task);
}

static ce_task_desc_t *ce_aes_config(uint32_t dir, uint32_t type, uint32_t mode,
                uint8_t *key_buf, uint32_t key_length)
{
    ce_task_desc_t *task = NULL;
    uint32_t flow = 1;

    task = (ce_task_desc_t *)hal_malloc(sizeof(ce_task_desc_t));
    if (task == NULL) {
        CE_ERR("hal_malloc fail\n");
        return NULL;
    }

    ce_task_desc_init(task, flow);
    hal_ce_method_set(dir, type, task);
    hal_ce_aes_mode_set(mode, task);
    hal_ce_key_set(key_buf, key_length, task);
    hal_dcache_clean((unsigned long)key_buf, key_length);

    return task;
}

static uint32_t ce_aes_sw_padding(crypto_aes_req_ctx_t *ctx)
{
    uint32_t blk_num = 0;
    uint32_t padding_size = 0;
    uint32_t last_blk_size = 0;

    blk_num = ctx->src_length / AES_BLOCK_SIZE;
    last_blk_size = ctx->src_length % AES_BLOCK_SIZE;

    if (last_blk_size) {
        padding_size = AES_BLOCK_SIZE - last_blk_size;
        memcpy(ctx->padding, ctx->src_buffer + blk_num * AES_BLOCK_SIZE, last_blk_size);
        memset(ctx->padding + last_blk_size, padding_size, padding_size);
        ctx->padding_len = AES_BLOCK_SIZE;
    } else {
        ctx->padding_len = 0;
    }

    return blk_num * AES_BLOCK_SIZE;
}

static int ce_aes_start(crypto_aes_req_ctx_t *req_ctx)
{
    int ret = 0;
    ce_task_desc_t *task;
    uint32_t src_len = 0;
    uint32_t src_word_len = 0;

    src_len = ce_aes_sw_padding(req_ctx);
    src_word_len = src_len >> 2;

    /*ce task config*/

    task = ce_aes_config(req_ctx->dir, CE_METHOD_AES, req_ctx->mode, req_ctx->key, req_ctx->key_length);
    if (task == NULL) {
        CE_ERR("ce_aes_config fail\n");
        return HAL_AES_INPUT_ERROR;
    }

    hal_ce_pending_clear(task->chan_id);

    if (req_ctx->iv) {
        hal_ce_iv_set(req_ctx->iv, AES_BLOCK_SIZE, task);
        hal_dcache_clean((unsigned long)req_ctx->iv, AES_BLOCK_SIZE);
    }
    if (CE_AES_MODE_CTR == req_ctx->mode) {
        hal_ce_cnt_set(req_ctx->iv_next, req_ctx->key_length, task);
        hal_dcache_clean((unsigned long)req_ctx->iv_next, req_ctx->key_length);
    } else if (CE_AES_MODE_CTS == req_ctx->mode) {
        hal_ce_cts_last(task);
    } else if (CE_AES_MODE_CFB == req_ctx->mode) {
        hal_ce_cfb_bitwidth_set(req_ctx->bitwidth,task);
    }

    if ((task->sym_ctl & 0xF00) == (CE_AES_MODE_CTS << CE_SYM_CTL_OP_MODE_SHIFT))
        task->data_len = src_len + req_ctx->padding_len;
    else
        hal_ce_data_len_set(src_len + req_ctx->padding_len, task);

    if (src_len) {
        task->src[0].addr = (uint32_t)__va_to_pa((unsigned long)req_ctx->src_buffer);
        task->src[0].len = src_word_len;

        if (req_ctx->padding_len) {
            task->src[1].addr = (uint32_t)__va_to_pa((unsigned long)req_ctx->padding);
            task->src[1].len = req_ctx->padding_len >> 2;
        }
    } else {
        task->src[0].addr = (uint32_t)__va_to_pa((unsigned long)req_ctx->padding);
        task->src[0].len = req_ctx->padding_len >> 2;
    }

    task->dst[0].addr = (uint32_t)__va_to_pa((unsigned long)req_ctx->dst_buffer);
    task->dst[0].len = (src_len + req_ctx->padding_len) >> 2;

    task->next = 0;
    hal_dcache_clean((unsigned long)task, sizeof(ce_task_desc_t));
    if (src_len) {
        hal_dcache_clean((unsigned long)req_ctx->src_buffer, src_len);
    }
    if (req_ctx->padding_len) {
        hal_dcache_clean((unsigned long)req_ctx->padding, req_ctx->padding_len);
    }
    hal_dcache_clean((unsigned long)req_ctx->dst_buffer, src_len + req_ctx->padding_len);
    //ce_print_task_info(task);
    hal_ce_set_task((unsigned long)task);
    hal_ce_irq_enable(task->chan_id);
    hal_ce_ctrl_start();

#ifdef CE_NO_IRQ
    hal_ce_wait_finish(task->chan_id);
    hal_ce_pending_clear(task->chan_id);
#else
#if 1
    ret = hal_sem_timedwait(ce_sem, CE_WAIT_TIME);
    if (ret != 0) {
        CE_ERR("Timed out\n");
        hal_free(task);
        return HAL_AES_TIME_OUT;
    }
#else
    rt_wqueue_wait(&ce_wqueue, 0, RT_WAITING_FOREVER);
#endif
#endif

    hal_dcache_invalidate((uint32_t)req_ctx->dst_buffer, src_len + req_ctx->padding_len);

    hal_ce_irq_disable(task->chan_id);

    if (hal_ce_get_erro() > 0) {
        CE_ERR("error\n");
        hal_ce_reg_printf();
        hal_free(task);
        return HAL_AES_CRYPTO_ERROR;
    }

    CE_DBG("do_aes_crypto sucess\n");
    hal_free(task);
    return HAL_AES_STATUS_OK;
}

static int ce_aes_check_ctx_vaild(crypto_aes_req_ctx_t *req_ctx)
{
    if (req_ctx == NULL) {
        CE_ERR("aes req_ctx is NULL\n");
        return HAL_AES_INPUT_ERROR;
    }

    if ((req_ctx->src_buffer == NULL)
            || (req_ctx->dst_buffer == NULL)
            || (req_ctx->key == NULL)
            || ((req_ctx->mode != CE_AES_MODE_ECB) && (req_ctx->iv == NULL) )) {
            CE_ERR("input is NULL\n");
            return HAL_AES_INPUT_ERROR;
    }

    if ((req_ctx->key_length != AES_KEYSIZE_16)
            && (req_ctx->key_length != AES_KEYSIZE_24)
            && (req_ctx->key_length != AES_KEYSIZE_32)) {
        CE_ERR("key length is %ld, invalid\n", req_ctx->key_length);
        return HAL_AES_INPUT_ERROR;
    }

    if ((((u32)req_ctx->src_buffer & (CE_ALIGN_SIZE - 1)) != 0)
            || (((u32)req_ctx->dst_buffer & (CE_ALIGN_SIZE - 1)) != 0)
            || (((u32)req_ctx->key & (CE_ALIGN_SIZE - 1)) != 0)) {
        CE_ERR("input buffer is not %d align\n", CE_ALIGN_SIZE);
        return HAL_AES_INPUT_ERROR;
    }

    if (req_ctx->dir == CE_DIR_DECRYPT) {
        if (((req_ctx->mode == CE_AES_MODE_ECB)
            || (req_ctx->mode == CE_AES_MODE_CBC)
            || (req_ctx->mode == CE_AES_MODE_CTS))
            && (req_ctx->src_length % AES_BLOCK_SIZE != 0)) {
            CE_ERR("src_length: %d is not %d align\n",
                    req_ctx->src_length, AES_BLOCK_SIZE);
            return HAL_AES_INPUT_ERROR;
        }
        if (req_ctx->src_length > req_ctx->dst_length) {
            CE_ERR("src_length: %d should not bigger than dst_length: %d\n",
                    req_ctx->src_length, req_ctx->dst_length);
            return HAL_AES_INPUT_ERROR;
        }
    } else if (req_ctx->dir == CE_DIR_ENCRYPT) {
        if (req_ctx->dst_length < CE_ROUND_UP(req_ctx->src_length, AES_BLOCK_SIZE)) {
            CE_ERR("dst_length: %d should not smaller than %d\n",
                    req_ctx->dst_length,
                    CE_ROUND_UP(req_ctx->src_length, AES_BLOCK_SIZE));
            return HAL_AES_INPUT_ERROR;
        }
    } else {
        CE_ERR("input crypt dir: %d is error.\n", req_ctx->dir);
        return HAL_AES_INPUT_ERROR;
    }

    return HAL_AES_STATUS_OK;
}

int do_aes_crypto(crypto_aes_req_ctx_t *req_ctx)
{
    uint32_t last_block_size = 0;
    uint32_t block_num = 0;
    uint32_t padding_size = 0;
    uint32_t first_encypt_size = 0;
    uint8_t data_block[AES_BLOCK_SIZE] = {0};
    uint8_t *iv;
    uint8_t *init_vector2;
    ce_task_desc_t *task;
    int ret;

    ret = ce_aes_check_ctx_vaild(req_ctx);
    if (ret) {
        CE_ERR("ce_aes_check_ctx_vaild fail\n");
        return ret;
    }

    ret = ce_aes_start(req_ctx);
    if (ret < 0) {
        CE_ERR("aes crypto fail\n");
        return ret;
    }

    return ret;
}

static uint32_t ce_hash_endian4(uint32_t data)
{
    uint32_t d1, d2, d3, d4;

    d1 = (data & 0xff) << 24;
    d2 = (data & 0xff00) << 8;
    d3 = (data & 0xff0000) >> 8;
    d4 = (data & 0xff000000) >> 24;

    return (d1 | d2 | d3 | d4);
}

static uint32_t ce_hash_blk_size(int type)
{
        if ((type == CE_METHOD_SHA384) || (type == CE_METHOD_SHA512))
                return SHA512_BLOCK_SIZE;
        return SHA1_BLOCK_SIZE;
}

static uint32_t ce_hash_sw_padding(crypto_hash_req_ctx_t *ctx)
{
        uint32_t blk_size = ce_hash_blk_size(ctx->type);
        uint32_t len_threshold = (blk_size == SHA512_BLOCK_SIZE) ? 112 : 56;
        uint32_t n = ctx->src_length % blk_size;
        uint8_t *p = ctx->padding;
        uint32_t len_l = ctx->src_length << 3;  /* total len, in bits. */
        uint32_t len_h = ctx->src_length >> 29;
        uint32_t big_endian = (ctx->type == CE_METHOD_MD5) ? 0 : 1;

    memset(ctx->padding, 0, 256);

    if (n) {
        memcpy(ctx->padding, ctx->src_buffer + ctx->src_length - n, n);
    }

        CE_DBG("ctx->type = %d, n = %d, ctx->src_length = %d\n", ctx->type, n, ctx->src_length);
        p[n] = 0x80;
        n++;

        if (n > len_threshold) { /* The pad data need two blocks. */
                memset(p+n, 0, blk_size*2 - n);
                p += blk_size*2 - 8;
        } else {
                memset(p+n, 0, blk_size - n);
                p += blk_size - 8;
        }

        if (big_endian == 1) {
#if 0
                /* The length should use bit64 in SHA384/512 case.
                 * The OpenSSL package is always small than 8K,
                 * so we use still bit32.
                 */
                if (blk_size == SHA512_BLOCK_SIZE) {
                        int len_hh = ctx->cnt >> 61;
                        *(int *)(p-4) = ce_hash_endian4(len_hh);
                }
#endif
                *(int *)p = ce_hash_endian4(len_h);
                *(int *)(p+4) = ce_hash_endian4(len_l);
        } else {
                *(int *)p = len_l;
                *(int *)(p+4) = len_h;
        }

    ctx->padding_len = (uint32_t)(p + 8 - ctx->padding);

    CE_DBG("After padding %d: %02x %02x %02x %02x   %02x %02x %02x %02x\n",
        ctx->padding_len,
        p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);

        return ctx->src_length - (ctx->src_length % blk_size);
}

static int ce_hash_start(crypto_hash_req_ctx_t *req_ctx)
{
    int ret = 0;
    int i = 0;
    uint8_t chan_id = 1;
    ce_task_desc_t *task = NULL;
    uint32_t src_word_len = 0;
    uint32_t src_length = ce_hash_sw_padding(req_ctx);

    src_word_len = src_length >> 2;

    task = (ce_task_desc_t *)hal_malloc(sizeof(ce_task_desc_t));
    if (task == NULL) {
        CE_ERR("hal_malloc fail\n");
        return HAL_HASH_MALLOC_ERROR;
    }
    CE_DBG("task addr = 0x%lx\n", (uint32_t)task);

    ce_task_desc_init(task, chan_id);
    hal_ce_pending_clear(chan_id);
    hal_ce_method_set(req_ctx->dir, req_ctx->type, task);
    hal_ce_data_len_set(src_length + req_ctx->padding_len, task);
    if (req_ctx->md_size) {
        hal_ce_iv_set(req_ctx->md, req_ctx->md_size, task);
        hal_dcache_clean((unsigned long)req_ctx->md, req_ctx->md_size);
        hal_ce_iv_mode_set(CE_HASH_IV_INPUT, task);
    }

    if (src_word_len != 0) {
        task->src[0].addr = (uint32_t)__va_to_pa((uint32_t)req_ctx->src_buffer);
        task->src[0].len = src_word_len;
        task->src[1].addr = (uint32_t)__va_to_pa((uint32_t)req_ctx->padding);
        task->src[1].len = req_ctx->padding_len >> 2;
    } else {
        task->src[0].addr = (uint32_t)__va_to_pa((uint32_t)req_ctx->padding);
        task->src[0].len = req_ctx->padding_len >> 2;
    }
    task->dst[0].addr = (uint32_t)__va_to_pa((uint32_t)req_ctx->dst_buffer);
    task->dst[0].len = req_ctx->dst_length >> 2;
    task->next = 0;

    hal_dcache_clean((uint32_t)task, sizeof(ce_task_desc_t));
    hal_dcache_clean((uint32_t)req_ctx->src_buffer, req_ctx->src_length);
    hal_dcache_clean((uint32_t)req_ctx->padding, req_ctx->padding_len);
    hal_dcache_clean((uint32_t)req_ctx->dst_buffer, req_ctx->dst_length);
    //FlushCacheAll();
    //ce_print_task_info(task);
    hal_ce_set_task((uint32_t)task);
    hal_ce_irq_enable(task->chan_id);
    hal_ce_ctrl_start();

#ifdef CE_NO_IRQ
    hal_ce_wait_finish(task->chan_id);
    hal_ce_pending_clear(task->chan_id);
#else
    ret = hal_sem_timedwait(ce_sem, CE_WAIT_TIME);
    if (ret != 0) {
        CE_ERR("Timed out\n");
        ret = HAL_HASH_TIME_OUT;
        goto fail;
    }
#endif
    hal_dcache_invalidate((uint32_t)req_ctx->dst_buffer, req_ctx->dst_length);

    if (hal_ce_get_erro() > 0) {
        hal_ce_reg_printf();
        ret = HAL_HASH_CRYPTO_ERROR;
        goto fail;
    }
    //ce_print_hex((char *)task->dst[0].addr, (task->dst[0].len * 4), (char *)task->dst[0].addr);
    //hal_ce_reg_printf();

    hal_ce_irq_disable(task->chan_id);
    memcpy(req_ctx->md, req_ctx->dst_buffer, req_ctx->dst_length);
    req_ctx->md_size = req_ctx->dst_length;
    hal_free(task);

    return HAL_HASH_STATUS_OK;

fail:
    if (task) {
        hal_free(task);
    }
    return ret;
}

static int ce_hash_check_ctx_valid(crypto_hash_req_ctx_t *req_ctx)
{
    if (req_ctx == NULL) {
        CE_ERR("sha req_ctx is NULL\n");
        return HAL_HASH_INPUT_ERROR;
    }

    if ((((u32)req_ctx->dst_buffer & (CE_ALIGN_SIZE - 1)) != 0)
        || (((u32)req_ctx->src_buffer & (CE_ALIGN_SIZE - 1)) != 0)) {
        CE_ERR("input buffer addr is not %d align\n", CE_ALIGN_SIZE);
        return HAL_HASH_INPUT_ERROR;
    }

    if (req_ctx->type == CE_METHOD_MD5) {
        if ((req_ctx->dst_length != MD5_DIGEST_SIZE)
            || ((req_ctx->md_size != 0)
                && (req_ctx->md_size != MD5_DIGEST_SIZE))) {
            CE_ERR("output length is not %d\n", MD5_DIGEST_SIZE);
            return HAL_HASH_INPUT_ERROR;
        }
    } else if (req_ctx->type == CE_METHOD_SHA1) {
        if ((req_ctx->dst_length != SHA1_DIGEST_SIZE)
            || ((req_ctx->md_size != 0)
                && (req_ctx->md_size != SHA1_DIGEST_SIZE))) {
            CE_ERR("output length is not %d\n", SHA1_DIGEST_SIZE);
            return HAL_HASH_INPUT_ERROR;
        }
    } else if (req_ctx->type == CE_METHOD_SHA224) {
        if ((req_ctx->dst_length != SHA256_DIGEST_SIZE)
            || ((req_ctx->md_size != 0)
                && (req_ctx->md_size != SHA256_DIGEST_SIZE))) {
            CE_ERR("output length is not %d\n", SHA256_DIGEST_SIZE);
            return HAL_HASH_INPUT_ERROR;
        }
    } else if (req_ctx->type == CE_METHOD_SHA256) {
        if ((req_ctx->dst_length != SHA256_DIGEST_SIZE)
            || ((req_ctx->md_size != 0)
                && (req_ctx->md_size != SHA256_DIGEST_SIZE))) {
            CE_ERR("output length is not %d\n", SHA256_DIGEST_SIZE);
            return HAL_HASH_INPUT_ERROR;
        }
    } else if (req_ctx->type == CE_METHOD_SHA384) {
        if ((req_ctx->dst_length != SHA512_DIGEST_SIZE)
            || ((req_ctx->md_size != 0)
                && (req_ctx->md_size != SHA512_DIGEST_SIZE))) {
            CE_ERR("output length is not %d\n", SHA512_DIGEST_SIZE);
            return HAL_HASH_INPUT_ERROR;
        }
    } else if (req_ctx->type == CE_METHOD_SHA512) {
        if ((req_ctx->dst_length != SHA512_DIGEST_SIZE)
            || ((req_ctx->md_size != 0)
                && (req_ctx->md_size != SHA512_DIGEST_SIZE))) {
            CE_ERR("output length is not %d\n", SHA512_DIGEST_SIZE);
            return HAL_HASH_INPUT_ERROR;
        }
    } else {
        CE_ERR("ce don't support hash mode: %d\n", req_ctx->type);
        return HAL_HASH_INPUT_ERROR;
    }

    return HAL_HASH_STATUS_OK;
}

int do_hash_crypto(crypto_hash_req_ctx_t *req_ctx)
{
    uint8_t *src_tmp = NULL;
    uint32_t src_align_len = 0;
    int ret = 0;

    ret = ce_hash_check_ctx_valid(req_ctx);
    if (ret < 0) {
        CE_ERR("ce_hash_check_ctx_valid fail: %d\n", ret);
        return ret;
    }

    ret = ce_hash_start(req_ctx);
    if (ret < 0) {
        CE_ERR("caclu hash erro num is %d\n", ret);
        return HAL_HASH_CRYPTO_ERROR;
    }

    return HAL_HASH_STATUS_OK;
}

static void ce_rsa_sw_padding(uint8_t *dst_buf, uint8_t *src_buf, uint32_t data_len, uint32_t group_len)
{
    int i = 0;

    memset(dst_buf, 0, group_len);
    for (i = group_len - data_len; i < group_len; i++) {
        dst_buf[i] = src_buf[group_len - 1 - i];
    }
}

static int ce_rsa_start(crypto_rsa_req_ctx_t *req_ctx)
{
    int ret = 0;
    uint8_t chan_id = 2;
    uint8_t *p_src = NULL;
    uint8_t *p_n = NULL;
    uint8_t *p_d = NULL;
    uint8_t *p_dst = NULL;
    ce_task_desc_t *task = NULL;
    uint32_t bitwidth_byte_len = 0;
    uint32_t bitwidth_word_len = 0;

    bitwidth_byte_len = req_ctx->bitwidth >> 3;
    bitwidth_word_len = req_ctx->bitwidth >> 5;

    p_src = hal_malloc(bitwidth_byte_len);
    if (p_src == NULL) {
        CE_ERR("rsa src hal_malloc fail\n");
        ret =  HAL_RSA_MALLOC_ERROR;
        goto fail;
    }
    memset(p_src, 0x0, bitwidth_byte_len);
    ce_rsa_sw_padding(p_src, req_ctx->src_buffer, req_ctx->src_length, bitwidth_byte_len);

    p_n = hal_malloc(bitwidth_byte_len);
    if (p_n == NULL) {
        CE_ERR("rsa key n hal_malloc fail\n");
        ret =  HAL_RSA_MALLOC_ERROR;
        goto fail;
    }
    memset(p_n, 0x0, bitwidth_byte_len);
    ce_rsa_sw_padding(p_n, req_ctx->key_n, req_ctx->n_len, bitwidth_byte_len);

    if (req_ctx->key_d) {
        p_d = hal_malloc(bitwidth_byte_len);
        if (p_d == NULL) {
            CE_ERR("rsa key d hal_malloc fail\n");
            ret =  HAL_RSA_MALLOC_ERROR;
            goto fail;
        }
        memset(p_d, 0x0, bitwidth_byte_len);
        ce_rsa_sw_padding(p_d, req_ctx->key_d, req_ctx->d_len, bitwidth_byte_len);
        req_ctx->key_d = p_d;
    }

    p_dst = hal_malloc(bitwidth_byte_len);
    if (p_dst == NULL) {
        CE_ERR("hal_malloc fail\n");
        ret =  HAL_RSA_MALLOC_ERROR;
        goto fail;
    }
    memset(p_dst, 0x0, bitwidth_byte_len);

    task = (ce_task_desc_t *)hal_malloc(sizeof(ce_task_desc_t));
    if (task == NULL) {
        CE_ERR("rt_malloc_align fail\n");
        ret =  HAL_RSA_MALLOC_ERROR;
        goto fail;
    }
    CE_DBG("task addr = 0x%lx\n", (uint32_t)task);

    ce_task_desc_init(task, chan_id);
    hal_ce_pending_clear(chan_id);
    hal_ce_method_set(req_ctx->dir, req_ctx->type, task);
    hal_ce_rsa_width_set(req_ctx->bitwidth, task);
    task->iv_addr = (uint32_t)__va_to_pa((uint32_t)p_n);
    if (req_ctx->key_d)
        task->key_addr = (uint32_t)__va_to_pa((uint32_t)p_d);
    else
        task->key_addr = (uint32_t)__va_to_pa((uint32_t)req_ctx->key_e);

    hal_ce_data_len_set(bitwidth_byte_len, task);

    task->src[0].addr = (uint32_t)__va_to_pa((uint32_t)p_src);
    task->src[0].len = bitwidth_word_len;

    task->dst[0].addr = (uint32_t)__va_to_pa((uint32_t)p_dst);
    task->dst[0].len = bitwidth_word_len;
    task->next = 0;

    hal_dcache_clean((uint32_t)task, sizeof(ce_task_desc_t));
    hal_dcache_clean((uint32_t)p_src, bitwidth_byte_len);
    hal_dcache_clean((uint32_t)p_n, bitwidth_byte_len);
    if (req_ctx->key_d)
        hal_dcache_clean((uint32_t)p_d, bitwidth_byte_len);
    else
        hal_dcache_clean((uint32_t)req_ctx->key_e, bitwidth_byte_len);
    hal_dcache_clean((uint32_t)p_dst, bitwidth_byte_len);

    //FlushCacheAll();
    /*ce_print_task_info(task);*/
    hal_ce_set_task((uint32_t)task);
    hal_ce_irq_enable(task->chan_id);
    hal_ce_ctrl_start();

#ifdef CE_NO_IRQ
    hal_ce_wait_finish(task->chan_id);
    hal_ce_pending_clear(task->chan_id);
#else
    ret = hal_sem_timedwait(ce_sem, CE_WAIT_TIME);
    if (ret != 0) {
        CE_ERR("Timed out\n");
        ret =  HAL_RSA_CRYPTO_ERROR;
        goto fail;
    }
#endif

    hal_dcache_invalidate((uint32_t)p_dst, bitwidth_byte_len);

    /*ce_reg_printf();*/
    if (hal_ce_get_erro() > 0) {
        hal_ce_reg_printf();
        ret = HAL_RSA_CRYPTO_ERROR;
        goto fail;
    }

    hal_ce_irq_disable(task->chan_id);

    ce_rsa_sw_padding(req_ctx->dst_buffer, p_dst, req_ctx->dst_length, req_ctx->dst_length);

fail:
    if (p_src)
        hal_free(p_src);

    if (p_n)
        hal_free(p_n);

    if (p_d)
        hal_free(p_d);

    if (p_dst)
        hal_free(p_dst);

    if (task)
        hal_free(task);

    return ret;
}

static int ce_rsa_check_ctx_valid(crypto_rsa_req_ctx_t *req_ctx)
{
    if (req_ctx == NULL) {
        CE_ERR("rsa req_ctx is NULL\n");
        return HAL_RSA_INPUT_ERROR;
    }

    if ((((u32)req_ctx->key_n & (CE_ALIGN_SIZE - 1)) != 0)
        || (((u32)req_ctx->key_e & (CE_ALIGN_SIZE - 1)) != 0)
        || (((u32)req_ctx->key_d & (CE_ALIGN_SIZE - 1)) != 0)
        || (((u32)req_ctx->src_buffer & (CE_ALIGN_SIZE - 1)) != 0)
        || (((u32)req_ctx->dst_buffer & (CE_ALIGN_SIZE - 1)) != 0)) {
            printf("rsa req_ctx buffer is not %d align\n", CE_ALIGN_SIZE);
            return HAL_RSA_INPUT_ERROR;
    }

    if ((req_ctx->bitwidth == 512)
        || (req_ctx->bitwidth == 1024)
        || (req_ctx->bitwidth == 2048)) {
        if ((req_ctx->n_len > req_ctx->bitwidth / 8)
            || (req_ctx->e_len > req_ctx->bitwidth / 8)
            || (req_ctx->d_len > req_ctx->bitwidth / 8)
            || (req_ctx->src_length > req_ctx->bitwidth / 8)
            || (req_ctx->dst_length > req_ctx->bitwidth / 8)) {
            CE_ERR("rsa length should not bigger than %d\n", req_ctx->bitwidth / 8);
            return HAL_RSA_INPUT_ERROR;
        }
    } else {
        CE_ERR("invalid bitwidth: %d\n", req_ctx->bitwidth);
        return HAL_RSA_INPUT_ERROR;
    }

    return HAL_RSA_STATUS_OK;
}

int do_rsa_crypto(crypto_rsa_req_ctx_t *req_ctx)
{
    int ret = 0;

    ret = ce_rsa_check_ctx_valid(req_ctx);
    if (ret < 0) {
        CE_ERR("ce_rsa_check_ctx_valid fail: %d\n", ret);
        return ret;
    }

    ret = ce_rsa_start(req_ctx);
    if (ret < 0) {
        CE_ERR("calc rsa erro num is %d\n", ret);
        return ret;
    }

    return HAL_RSA_STATUS_OK;
}

int do_rng_gen(crypto_rng_req_ctx_t *req_ctx)
{
    int ret = 0;
    uint8_t chan_id = 2;
    uint32_t dst_len = 0;
    uint8_t *dst_buf = NULL;
    ce_task_desc_t *task = NULL;

    if (req_ctx->mode == CE_METHOD_TRNG) {
        dst_len = CE_ROUND_UP(req_ctx->rng_len, 32); /*align with 32 Bytes*/
    } else if (req_ctx->mode == CE_METHOD_PRNG) {
        dst_len = CE_ROUND_UP(req_ctx->rng_len, 20); /*align with 20 Bytes*/
    } else {
        CE_ERR("Error: do not support mode %d\n", req_ctx->mode);
        ret = HAL_RNG_INPUT_ERROR;
        goto fail;
    }

    if (dst_len > SS_RNG_MAX_LEN) {
        CE_ERR("Error: The RNG length is too large: %d\n", dst_len);
        ret = HAL_RNG_INPUT_ERROR;
        goto fail;
    }

    dst_buf = (uint8_t *)hal_malloc(dst_len);
    if (dst_buf == NULL) {
        CE_ERR("hal_malloc dst_buf fail\n");
        ret = HAL_RNG_MALLOC_ERROR;
        goto fail;
    }

    task = (ce_task_desc_t *)hal_malloc(sizeof(ce_task_desc_t));
    if (task == NULL) {
        CE_ERR("hal_malloc task fail\n");
        ret = HAL_RNG_MALLOC_ERROR;
        goto fail;
    }

    CE_DBG("task addr = 0x%lx, rng_buf = 0x%lx, rng_len = %d\n", (uint32_t)task, req_ctx->rng_buf, req_ctx->rng_len);

    ce_task_desc_init(task, chan_id);
    hal_ce_pending_clear(chan_id);
    hal_ce_method_set(0, req_ctx->mode, task);
    hal_ce_data_len_set(dst_len, task);

    if (req_ctx->mode == CE_METHOD_PRNG) {
        /* must set the seed add in prng */
        if (req_ctx->key && (req_ctx->key_len == 24)) {
            hal_ce_key_set(req_ctx->key, req_ctx->key_len, task);
            hal_dcache_clean((uint32_t)req_ctx->key, req_ctx->key_len);
        } else {
            CE_ERR("Error: RRNG must set seed, and the seed size must be 24!\n");
            ret = HAL_RNG_INPUT_ERROR;
            goto fail;
        }
    }

    task->src[0].addr = 0;
    task->src[0].len = 0;

    task->dst[0].addr = (uint32_t)__va_to_pa((uint32_t)dst_buf);
    task->dst[0].len = dst_len >> 2;

    hal_dcache_clean((uint32_t)task, sizeof(ce_task_desc_t));
    hal_dcache_clean((uint32_t)dst_buf, dst_len);

    //ce_print_task_info(task);
    hal_ce_set_task((uint32_t)task);
    hal_ce_irq_enable(task->chan_id);
    hal_ce_ctrl_start();

#ifdef CE_NO_IRQ
    hal_ce_wait_finish(task->chan_id);
    hal_ce_pending_clear(task->chan_id);
#else
    ret = hal_sem_timedwait(ce_sem, CE_WAIT_TIME);
    if (ret != 0) {
        CE_ERR("Timed out\n");
        ret = HAL_RNG_TIME_OUT;
        goto fail;
    }
#endif
    hal_dcache_invalidate((uint32_t)dst_buf, dst_len);

    if (req_ctx->mode == CE_METHOD_PRNG) {
        hal_dcache_invalidate((uint32_t)req_ctx->key, req_ctx->key_len);
    }

    if (hal_ce_get_erro() > 0) {
        hal_ce_reg_printf();
        ret = HAL_RNG_CRYPTO_ERROR;
        goto fail;
    }
    //ce_print_hex((char *)task->dst[0].addr, (task->dst[0].len * 4), (char *)task->dst[0].addr);
    /*ce_reg_printf();*/

    memcpy(req_ctx->rng_buf, dst_buf, req_ctx->rng_len);

    hal_ce_irq_disable(task->chan_id);

    hal_free(task);
    hal_free(dst_buf);
    return HAL_RNG_STATUS_OK;

fail:
    if (task) {
        hal_free(task);
    }

    if (dst_buf) {
        hal_free(task);
    }

    return ret;
}
