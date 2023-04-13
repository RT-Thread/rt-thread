/**
  ******************************************************************************
  * @file    sdio2.h
  * @version V1.0
  * @date    2022-08-03
  * @brief   This file is the description of.IP register
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
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
#ifndef __HARDWARE_SDIO2_H__
#define __HARDWARE_SDIO2_H__

/****************************************************************************
 * Pre-processor Definitions
****************************************************************************/

/* Register offsets *********************************************************/

#define SDIO2_IO_ENABLE_OFFSET          (0x0002) /* SDIO I/O Enable */
#define SDIO2_FN1_BLK_SIZE_0_OFFSET     (0x0028) /* SDIO block size infor */
#define SDIO2_FN1_BLK_SIZE_1_OFFSET     (0x0029) /* SDIO block size infor */
#define SDIO2_DEV_SLEEP_OFFSET          (0x0092) /* SDIO Device Sleep */
#define SDIO2_CCR_FUNC_OFFSET           (0x0100) /* Address offset of CCR between two functions */
#define SDIO2_HOST_TO_CARD_EVENT_OFFSET (0x0100)
#define SDIO2_HOST_INT_CAUSE_OFFSET     (0x0101)
#define SDIO2_HOST_INT_MASK_OFFSET      (0x0102)
#define SDIO2_HOST_INT_STATUS_OFFSET    (0x0103)
#define SDIO2_RD_BIT_MAP_OFFSET         (0x0104)
#define SDIO2_WR_BIT_MAP_OFFSET         (0x0106)
#define SDIO2_RD_LEN_OFFSET             (0x0108)
#define SDIO2_HOST_TRANS_STATUS_OFFSET  (0x0128)
#define SDIO2_CARD_TO_HOST_EVENT_OFFSET (0x0130)
#define SDIO2_CARD_INT_MASK_OFFSET      (0x0134)
#define SDIO2_CARD_INT_STATUS_OFFSET    (0x0138)
#define SDIO2_CARD_INT_MODE_OFFSET      (0x013C)
#define SDIO2_SQ_READ_BASE_OFFSET       (0x0140)
#define SDIO2_SQ_WRITE_BASE_OFFSET      (0x0144)
#define SDIO2_READ_INDEX_OFFSET         (0x0148)
#define SDIO2_WRITE_INDEX_OFFSET        (0x0149)
#define SDIO2_DNLD_QUEUE_WRPTR_OFFSET   (0x014A)
#define SDIO2_UPLD_QUEUE_WRPTR_OFFSET   (0x014B)
#define SDIO2_DNLD_QUEUE_OFFSET         (0x014C)
#define SDIO2_UPLD_QUEUE_OFFSET         (0x0154)
#define SDIO2_CHIP_VERSION_OFFSET       (0x015C)
#define SDIO2_IP_VERSION0_OFFSET        (0x015E)
#define SDIO2_IP_VERSION1_OFFSET        (0x015F)
#define SDIO2_SCRATCH2_OFFSET           (0x0164)
#define SDIO2_SCRATCH1_OFFSET           (0x0166)
#define SDIO2_OCR0_OFFSET               (0x0168)
#define SDIO2_OCR1_OFFSET               (0x0169)
#define SDIO2_OCR2_OFFSET               (0x016A)
#define SDIO2_CONFIG_OFFSET             (0x016B)
#define SDIO2_CONFIG2_OFFSET            (0x016C)
#define SDIO2_DEBUG_OFFSET              (0x0170)
#define SDIO2_DMA_ADDR_OFFSET           (0x0174)
#define SDIO2_IO_PORT_OFFSET            (0x0178)


// Bit Def. Scratch register 0
#define SDIO2_SCRATCH_OFFSET           (0x0160)

// Bit Def. Block size 1 mask (Offset 0x29)
#define SDIO2_FN1_BLK_SIZE_1_MASK 0x01

// Bit Def. Host To Card Interrupt Event (Offset 0x100/200)
#define SDIO2_HCR_CONFIG_HostPwrUp (1 << 1)

// Bit Def. Host Transfer Status (Offset 0x128/228)
#define SDIO2_CCR_HOST_INT_DnLdReStart (1 << 0)
#define SDIO2_CCR_HOST_INT_UpLdReStart (1 << 1)
#define SDIO2_CCR_HOST_INT_DnLdCRC_err (1 << 2)

// Bit Def. Card To Host Interrupt Event (Offset 0x130/230)
#define SDIO2_CCR_CS_DnLdRdy    (1 << 0)
#define SDIO2_CCR_CS_UpLdRdy    (1 << 1)
#define SDIO2_CCR_CS_ReadCISRdy (1 << 2)
#define SDIO2_CCR_CS_IORdy      (1 << 3)

// Bit Def. Card Interrupt Mask (Offset 0x134/234)
#define SDIO2_CCR_CIM_DnLdOvr (1 << 0)
#define SDIO2_CCR_CIM_UpLdOvr (1 << 1)
#define SDIO2_CCR_CIM_Abort   (1 << 2)
#define SDIO2_CCR_CIM_PwrDn   (1 << 3)
#define SDIO2_CCR_CIM_PwrUp   (1 << 4)

#define SDIO2_CCR_CIM_MASK 0x0007

// Bit Def. Card Interrupt Status (Offset 0x138/238)
#define SDIO2_CCR_CIC_DnLdOvr (1 << 0)
#define SDIO2_CCR_CIC_UpLdOvr (1 << 1)
#define SDIO2_CCR_CIC_Abort   (1 << 2)
#define SDIO2_CCR_CIC_PwrDn   (1 << 3)
#define SDIO2_CCR_CIC_PwrUp   (1 << 4)

#define SDIO2_CCR_CIC_MASK 0x001F

// Bit Def. Card Interrupt RSR (Offset 0x13C/23C)
#define SDIO2_CCR_CIO_DnLdOvr (1 << 0)
#define SDIO2_CCR_CIO_UpLdOvr (1 << 1)
#define SDIO2_CCR_CIO_Abort   (1 << 2)
#define SDIO2_CCR_CIO_PwrDn   (1 << 3)
#define SDIO2_CCR_CIO_PwrUp   (1 << 4)
#define SDIO2_CCR_CIO_MASK    0x001F

//Config2 register mask
#define SDIO2_CONFIG2_MSK 0x00000C00

//CardIntMode register mask

#define SDIO2_CARD_INT_MODE_MSK 0x00000003
#define SDIO2_HOST_INT_MSK      0x00000002

#endif /* __HARDWARE_SDIO2_H__ */
