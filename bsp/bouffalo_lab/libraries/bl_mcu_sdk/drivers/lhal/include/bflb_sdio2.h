/**
  ******************************************************************************
  * @file    bflb_sdio2.h
  * @version V1.0
  * @date    2022-09-27
  * @brief   This file is the low hardware abstraction layer file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2022 Bouffalo Lab</center></h2>
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
  *
  ******************************************************************************
  */

#ifndef _BFLB_SDIO2_H
#define _BFLB_SDIO2_H

//#define BFLB_SDIO2_ENUM 1

#ifndef BFLB_SDIO2_ENUM
#include "bflb_core.h"
#else
#include "stdio.h"
#include "stdint.h"
struct bflb_device_s {
    const char *name;
    uint32_t reg_base;
    uint8_t irq_num;
    uint8_t idx;
    uint8_t sub_idx;
    uint8_t dev_type;
    void *user_data;
};
#endif

/* SDIO2 buffer size */
#define SDIO2_BYTE_PER_BUF (1024 * 2)
#define SDIO2_MAX_PORT_NUM 16
#define SDIO2_MAX_FUNC     1

int bflb_sdio2_init(struct bflb_device_s *dev);
int bflb_sdio2_check_host_ready(struct bflb_device_s *dev);
uint32_t bflb_sdio2_get_block_size(struct bflb_device_s *dev);
int bflb_sdio2_tx_rx_queue_init(struct bflb_device_s *dev);
int bflb_sdio2_send_data(struct bflb_device_s *dev, int qos, uintptr_t *buff, int len);
int bflb_sdio2_recv_data(struct bflb_device_s *dev, int qos, uintptr_t *buff, int *len);
void bflb_sdio2_isr(int irq, void *arg);

#endif /* _BFLB_SDIO3_H */
