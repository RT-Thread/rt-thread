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

#ifndef __SUNXI_CE_H__
#define __SUNXI_CE_H__

#ifdef __cplusplus
extern "C" {
#endif

//#define CE_DEBUG
/* For debug */
#if defined(CE_DEBUG)
#define CE_DBG(fmt, arg...) hal_log_err("%s()%d - "fmt, __func__, __LINE__, ##arg)
#else
#define CE_DBG(fmt, arg...) do{} while(0)
#endif
#define CE_ERR(fmt, arg...) hal_log_err("%s()%d - "fmt, __func__, __LINE__, ##arg)

#define AES_KEYSIZE_16          (16)
#define AES_KEYSIZE_24          (24)
#define AES_KEYSIZE_32          (32)
#define AES_MAX_KEY_SIZE        (32)

/*ce flow*/
#define CE_FLOW_NUM     (4)
#define CE_FLOW_AVAILABLE   (0)
#define CE_FLOW_UNAVAILABLE (1)

typedef struct {
    uint32_t addr;
    uint32_t len; /* in word (4 bytes). Exception: in byte for AES_CTS */
} ce_scatter_t;

/*define the return value for aes*/
typedef enum{
    HAL_AES_STATUS_OK = 0,
    HAL_AES_INPUT_ERROR = -1,
    HAL_AES_MALLOC_ERROR = -2,
    HAL_AES_CRYPTO_ERROR = -3,
    HAL_AES_TIME_OUT = -4,
} hal_aes_status_t;

/*define the return value for hal_hash*/
typedef enum{
    HAL_HASH_STATUS_OK = 0,
    HAL_HASH_INPUT_ERROR = -1,
    HAL_HASH_MALLOC_ERROR = -2,
    HAL_HASH_CRYPTO_ERROR = -3,
    HAL_HASH_TIME_OUT = -4,
} hal_hash_status_t;

/*define the return value for hal_rsa*/
typedef enum{
    HAL_RSA_STATUS_OK = 0,
    HAL_RSA_INPUT_ERROR = -1,
    HAL_RSA_MALLOC_ERROR = -2,
    HAL_RSA_CRYPTO_ERROR = -3,
    HAL_RSA_TIME_OUT = -4,
} hal_rsa_status_t;


/*define the return value for hal_hash*/
typedef enum{
    HAL_RNG_STATUS_OK = 0,
    HAL_RNG_INPUT_ERROR = -1,
    HAL_RNG_MALLOC_ERROR = -2,
    HAL_RNG_CRYPTO_ERROR = -3,
    HAL_RNG_TIME_OUT = -4,
} hal_rng_status_t;

typedef struct ce_task_desc {
    uint32_t chan_id;
    uint32_t comm_ctl;
    uint32_t sym_ctl;
    uint32_t asym_ctl;
    uint32_t key_addr;
    uint32_t iv_addr;
    uint32_t ctr_addr;
    uint32_t data_len; /* in word(4 byte). Exception: in byte for AES_CTS */

    ce_scatter_t src[8];
    ce_scatter_t dst[8];

    struct ce_task_desc *next;
    uint32_t reserved[3];
} ce_task_desc_t;


#ifdef __cplusplus
}
#endif

#endif /* __SUNXI_CE_H__ */
