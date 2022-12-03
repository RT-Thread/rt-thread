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

#ifndef __HAL_CE_H__
#define __HAL_CE_H__

#ifdef __cplusplus
extern "C" {
#endif

void hal_ce_clock_init(void);
uint32_t hal_ce_reg_rd(uint32_t offset);
void hal_ce_reg_wr(uint32_t offset, uint32_t val);

void hal_ce_key_set(char *key, int size, ce_task_desc_t *task);

int hal_ce_pending_get(void);
void hal_ce_pending_clear(int flow);
void hal_ce_irq_enable(int flow);
void hal_ce_irq_disable(int flow);

void hal_ce_iv_set(char *iv, int size, ce_task_desc_t *task);
void hal_ce_iv_mode_set(int mode, ce_task_desc_t *task);

void hal_ce_cnt_set(char *cnt, int size, ce_task_desc_t *task);
void hal_ce_cnt_get(int flow, char *cnt, int size);

void hal_ce_md_get(char *dst, char *src, int size);
void hal_ce_sha_final(void);
void hal_ce_check_sha_end(void);

void hal_ce_rsa_width_set(int size, ce_task_desc_t *task);
void hal_ce_rsa_op_mode_set(int mode, ce_task_desc_t *task);

void hal_ce_ecc_width_set(int size, ce_task_desc_t *task);
void hal_ce_ecc_op_mode_set(int mode, ce_task_desc_t *task);

void hal_ce_cts_last(ce_task_desc_t *task);
void hal_ce_hmac_sha1_last(ce_task_desc_t *task);

void hal_ce_xts_first(ce_task_desc_t *task);
void hal_ce_xts_last(ce_task_desc_t *task);

void hal_ce_method_set(int dir, int type, ce_task_desc_t *task);

void hal_ce_aes_mode_set(int mode, ce_task_desc_t *task);
void hal_ce_cfb_bitwidth_set(int bitwidth, ce_task_desc_t *task);

int hal_ce_flow_err(int flow);

void hal_ce_data_len_set(int len, ce_task_desc_t *task);

int hal_ce_reg_print(char *buf, int len);
void hal_ce_keyselect_set(int select, ce_task_desc_t *task);
void hal_ce_keysize_set(int size, ce_task_desc_t *task);
void hal_ce_ctrl_start(void);

void hal_ce_wait_finish(uint32_t flow);
void hal_ce_set_task(uint32_t task_addr);
void hal_ce_task_enable(ce_task_desc_t *task);

uint32_t hal_ce_get_erro(void);
void hal_ce_reg_printf(void);


#ifdef __cplusplus
}
#endif

#endif /* __SUNXI_CE_H__ */
