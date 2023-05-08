/**
  ******************************************************************************
  * @file    bflb_sdio2.c
  * @version V1.0
  * @date    2022-10-12
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

#include "../include/bflb_sdio2.h"
#include "../include/hardware/sdio2_reg.h"

//#define SDIO2_DRV_DBG(a, ...) printf(a, ##__VA_ARGS__)
#define SDIO2_DRV_DBG(a, ...)
#ifndef BOOTROM
#define SDIO2_DRV_ERR(a, ...) printf("[Error]:" a, ##__VA_ARGS__)
#else
extern void bflb_bootrom_printf(char *fmt, ...);
#define SDIO2_DRV_ERR(a, ...) bflb_bootrom_printf("[Error]:" a, ##__VA_ARGS__)
#endif
#define SDU_INT_HOST 0

static uintptr_t local_tx_buf[SDIO2_MAX_PORT_NUM][SDIO2_BYTE_PER_BUF / sizeof(uintptr_t)] ATTR_NOCACHE_RAM_SECTION;
static uintptr_t local_rx_buf[SDIO2_MAX_PORT_NUM][SDIO2_BYTE_PER_BUF / sizeof(uintptr_t)] ATTR_NOCACHE_RAM_SECTION;

/****************************************************************************/ /**
 * @brief  Get sdio2 block size
 *
 * @param  dev  SDIO device pointer
 *
 * @return Block size
 *
*******************************************************************************/
uint32_t bflb_sdio2_get_block_size(struct bflb_device_s *dev)
{
    uint16_t blk_size = 0;
    uint32_t reg_base = dev->reg_base;

    blk_size = getreg8(reg_base + SDIO2_FN1_BLK_SIZE_0_OFFSET);
    blk_size |= ((getreg8(reg_base + SDIO2_FN1_BLK_SIZE_1_OFFSET) & SDIO2_FN1_BLK_SIZE_1_MASK) << 8);

    return blk_size;
}

/****************************************************************************/ /**
 * @brief  sdio2 init
 *
 * @param  dev: SDIO device pointer
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
int bflb_sdio2_init(struct bflb_device_s *dev)
{
    uint32_t reg_base = dev->reg_base;
    uint32_t regval = 0;

    putreg16(0, reg_base + SDIO2_RD_BIT_MAP_OFFSET);
    putreg16(0, reg_base + SDIO2_WR_BIT_MAP_OFFSET);

    /* toggle SDIO_CCR_CIC_DnLdOvr on WL_SDIO_CCR_CARD_INT_CAUSE */
    putreg8(SDIO2_CCR_CIC_DnLdOvr, reg_base + SDIO2_CARD_INT_STATUS_OFFSET);
    putreg8(0, reg_base + SDIO2_CARD_INT_STATUS_OFFSET);

    if (1) {
        /* multiport */
        regval = getreg32(reg_base + SDIO2_CONFIG2_OFFSET);
        putreg32(regval | SDIO2_CONFIG2_MSK, reg_base + SDIO2_CONFIG2_OFFSET);
        regval = getreg8(reg_base + SDIO2_CONFIG_OFFSET);
        putreg8(regval | 0x00000010, reg_base + SDIO2_CONFIG_OFFSET);
    }

    /* unmask the interrupts */
    putreg8(SDIO2_CCR_CIM_MASK, reg_base + SDIO2_CARD_INT_MASK_OFFSET);
    /* select interrupt reset mode */
    putreg8(0, reg_base + SDIO2_CARD_INT_MODE_OFFSET);

    bflb_sdio2_tx_rx_queue_init(dev);

    bflb_irq_attach(dev->irq_num, bflb_sdio2_isr, dev);
    bflb_irq_enable(dev->irq_num);

    return 0;
}

/****************************************************************************/ /**
 * @brief  SDIO2 tx and rx queue init
 *
 * @param  dev: SDIO device pointer
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
int bflb_sdio2_tx_rx_queue_init(struct bflb_device_s *dev)
{
    uint32_t reg_base = dev->reg_base;
    uint16_t wr_bit_map = getreg16(reg_base + SDIO2_WR_BIT_MAP_OFFSET);

    for (uint8_t i = 0; i < SDIO2_MAX_PORT_NUM; i++) {
        if (!(wr_bit_map & (1 << i))) {
            /* attach new buffer */
            putreg8(i, reg_base + SDIO2_WRITE_INDEX_OFFSET);
            putreg32((uint32_t)&local_rx_buf[i][0], reg_base + SDIO2_SQ_WRITE_BASE_OFFSET);
            putreg16(1 << i, reg_base + SDIO2_WR_BIT_MAP_OFFSET);
#if SDU_INT_HOST
            putreg8((SDIO2_CCR_CS_ReadCISRdy | SDIO2_CCR_CS_DnLdRdy | SDIO2_CCR_CS_IORdy),
                    reg_base + SDIO2_CARD_TO_HOST_EVENT_OFFSET);
#endif
        }
    }
    return 0;
}

/****************************************************************************/ /**
 * @brief  SDIO2 check host ready
 *
 * @param  dev:   SDIO device pointer
 *
 * @return 1 for host ready, 0 for not
 *
*******************************************************************************/
int bflb_sdio2_check_host_ready(struct bflb_device_s *dev)
{
    uint32_t reg_base = dev->reg_base;
    uint32_t regval = 0;

    regval = getreg8(reg_base + SDIO2_SCRATCH_OFFSET);

    if (regval != 0) {
        return 1;

    } else {
        return 0;
    }
}

/****************************************************************************/ /**
 * @brief  SDIO2 send data,this function can be in user app context
 *
 * @param  dev:   SDIO device pointer
 * @param  qos:   qos number for this data buffer to send
 * @param  buff:  data buffer pointer
 * @param  len:   data length
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
int bflb_sdio2_send_data(struct bflb_device_s *dev, int qos, uintptr_t *buff, int len)
{
    uint32_t reg_base = dev->reg_base;
    uint16_t rd_bit_map = getreg16(reg_base + SDIO2_RD_BIT_MAP_OFFSET);
    static uint8_t curr_upld_port = 0; 

    if (rd_bit_map & (1 << curr_upld_port)) {
        return -1;
    }
    arch_memcpy_fast(local_tx_buf[curr_upld_port], buff, len);
    SDIO2_DRV_DBG("Copy port=%d,index=%d\r\n",curr_upld_port,local_tx_buf[curr_upld_port][0]);
    putreg8(curr_upld_port, reg_base + SDIO2_READ_INDEX_OFFSET);
    putreg16(SDIO2_BYTE_PER_BUF, reg_base + SDIO2_RD_LEN_OFFSET + curr_upld_port * 2);
    putreg32((uint32_t)&local_tx_buf[curr_upld_port][0], reg_base + SDIO2_SQ_READ_BASE_OFFSET);
    putreg16(1 << curr_upld_port, reg_base + SDIO2_RD_BIT_MAP_OFFSET);
#if SDU_INT_HOST
    putreg8(SDIO2_CCR_CS_UpLdRdy, reg_base + SDIO2_CARD_TO_HOST_EVENT_OFFSET);
#endif     
    curr_upld_port++;
    if(curr_upld_port == SDIO2_MAX_PORT_NUM){
        curr_upld_port = 0;
    }
    return 0;
}

/****************************************************************************/ /**
 * @brief  SDIO2 receive data,this function can be in user app context
 *
 * @param  dev:   SDIO device pointer
 * @param  qos:   qos number for this data buffer to receive
 * @param  buff:  data buffer pointer
 * @param  len:   data length
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
int bflb_sdio2_recv_data(struct bflb_device_s *dev, int qos, uintptr_t *buff, int *len)
{
    static uint16_t curr_dnld_port = 0;
    uint32_t reg_base = dev->reg_base;
    uint16_t wr_bit_map = getreg16(reg_base + SDIO2_WR_BIT_MAP_OFFSET);    
    uint8_t crcerror = 0;
#if 0
    uint8_t card_status = 0;

    /* get card status */
    card_status = getreg8(reg_base + SDIO2_CARD_INT_STATUS_OFFSET);
#endif

    /* get erro */
    crcerror = getreg8(reg_base + SDIO2_HOST_TRANS_STATUS_OFFSET);

#if 0
    if (!(card_status & SDIO2_CCR_CIC_DnLdOvr)){
        SDIO2_DRV_DBG("No data come from host\r\n");
        return -1;
    }
#endif
    if (crcerror & SDIO2_CCR_HOST_INT_DnLdCRC_err) {
        SDIO2_DRV_ERR("RX CRC error\r\n");
    }

    if (!(wr_bit_map & (1 << curr_dnld_port))) {
        arch_memcpy_fast(buff, local_rx_buf[curr_dnld_port], SDIO2_BYTE_PER_BUF);
        SDIO2_DRV_DBG("Copy port=%d,index=%d\r\n",curr_dnld_port,buff[0]);
        *len = SDIO2_BYTE_PER_BUF;
        /* attach new buffer */
        putreg8(curr_dnld_port, reg_base + SDIO2_WRITE_INDEX_OFFSET);
        putreg32((uint32_t)&local_rx_buf[curr_dnld_port][0], reg_base + SDIO2_SQ_WRITE_BASE_OFFSET);
        putreg16(1 << curr_dnld_port, reg_base + SDIO2_WR_BIT_MAP_OFFSET);
#if SDU_INT_HOST
        putreg8((SDIO2_CCR_CS_ReadCISRdy | SDIO2_CCR_CS_DnLdRdy | SDIO2_CCR_CS_IORdy),
                reg_base + SDIO2_CARD_TO_HOST_EVENT_OFFSET);
#endif
        /* go to next */
        curr_dnld_port++;
        if (curr_dnld_port == SDIO2_MAX_PORT_NUM) {
            curr_dnld_port = 0;
        }
        return 0;
    }else{
        return -1;
    }
}

/****************************************************************************/ /**
 * @brief  sdio2 irq handler
 *
 * @param  irq: sdio3 interrupt type
 * @param  arg: arg for callback
 *
 * @return None
 *
*******************************************************************************/
void bflb_sdio2_isr(int irq, void *arg)
{
    struct bflb_device_s *dev = (struct bflb_device_s *)arg;
    uint32_t reg_base = 0;
    uint32_t regval = 0;
    uint8_t crcerror = 0;

    reg_base = dev->reg_base;
    regval = getreg8(reg_base + SDIO2_CARD_INT_STATUS_OFFSET);

    /* clear interrupt */
    putreg8(~regval | SDIO2_CCR_CIC_PwrUp, reg_base + SDIO2_CARD_INT_STATUS_OFFSET);
    /* get erro */
    crcerror = getreg8(reg_base + SDIO2_HOST_TRANS_STATUS_OFFSET);

    if ((regval & SDIO2_CCR_CIC_UpLdOvr)) {
        SDIO2_DRV_DBG("TX interrupt come\r\n");
    }

    if ((regval & SDIO2_CCR_CIC_DnLdOvr) &&
        !(crcerror & SDIO2_CCR_HOST_INT_DnLdCRC_err)) {
        SDIO2_DRV_DBG("RX interrupt come\r\n");
    }

    if (crcerror & SDIO2_CCR_HOST_INT_DnLdCRC_err) {
        SDIO2_DRV_ERR("RX CRC error\r\n");
    }
}
