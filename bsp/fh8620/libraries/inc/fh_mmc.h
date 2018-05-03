/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef FH_MMC_H_
#define FH_MMC_H_

#include "fh_def.h"


#define     OFFSET_SDC_CTRL                         (0x0000)
#define     OFFSET_SDC_PWREN                        (0x0004)
#define     OFFSET_SDC_CLKDIV                       (0x0008)
#define     OFFSET_SDC_CLKSRC                       (0x000C)
#define     OFFSET_SDC_CLKENA                       (0x0010)
#define     OFFSET_SDC_TMOUT                        (0x0014)
#define     OFFSET_SDC_CTYPE                        (0x0018)
#define     OFFSET_SDC_BLKSIZ                       (0x001C)
#define     OFFSET_SDC_BYTCNT                       (0x0020)
#define     OFFSET_SDC_INTMASK                      (0x0024)
#define     OFFSET_SDC_CMDARG                       (0x0028)
#define     OFFSET_SDC_CMD                          (0x002C)
#define     OFFSET_SDC_RESP0                        (0x0030)
#define     OFFSET_SDC_RESP1                        (0x0034)
#define     OFFSET_SDC_RESP2                        (0x0038)
#define     OFFSET_SDC_RESP3                        (0x003C)
#define     OFFSET_SDC_MINTSTS                      (0x0040)
#define     OFFSET_SDC_RINTSTS                      (0x0044)
#define     OFFSET_SDC_STATUS                       (0x0048)
#define     OFFSET_SDC_FIFOTH                       (0x004C)
#define     OFFSET_SDC_CDETECT                      (0x0050)
#define     OFFSET_SDC_WRTPRT                       (0x0054)
#define     OFFSET_SDC_GPIO                         (0x0058)
#define     OFFSET_SDC_TCBCNT                       (0x005C)
#define     OFFSET_SDC_TBBCNT                       (0x0060)
#define     OFFSET_SDC_DEBNCE                       (0x0064)
#define     OFFSET_SDC_USRID                        (0x0068)
#define     OFFSET_SDC_VERID                        (0x006C)
#define     OFFSET_SDC_HCON                         (0x0070)
#define     OFFSET_SDC_UHS_REG                      (0x0074)
#define     OFFSET_SDC_RST_N                        (0x0078)
#define     OFFSET_SDC_BMOD                         (0x0080)
#define     OFFSET_SDC_PLDMND                       (0x0084)
#define     OFFSET_SDC_DBADDR                       (0x0088)
#define     OFFSET_SDC_IDSTS                        (0x008C)
#define     OFFSET_SDC_IDINTEN                      (0x0090)
#define     OFFSET_SDC_DSCADDR                      (0x0094)
#define     OFFSET_SDC_BUFADDR                      (0x0098)
#define     OFFSET_SDC_CARDTHRCTL                   (0x0100)
#define     OFFSET_SDC_BACK_END_POWER               (0x0104)
#define     OFFSET_SDC_FIFO                         (0x0200)

#define     MMC_FIFO_DEPTH                      (16)

#define     MMC_CMD_FLAG_RESPONSE_EXPECTED      BIT(6)
#define     MMC_CMD_FLAG_LONG_RESPONSE          BIT(7)
#define     MMC_CMD_FLAG_CHECK_RESP_CRC         BIT(8)
#define     MMC_CMD_FLAG_DATA_EXPECTED          BIT(9)
#define     MMC_CMD_FLAG_WRITE_TO_CARD          BIT(10)
#define     MMC_CMD_FLAG_DATA_STREAM            BIT(11)
#define     MMC_CMD_FLAG_AUTO_STOP              BIT(12)
#define     MMC_CMD_FLAG_WAIT_PREV_DATA         BIT(13)
#define     MMC_CMD_FLAG_STOP_TRANSFER          BIT(14)
#define     MMC_CMD_FLAG_SEND_INIT              BIT(15)
#define     MMC_CMD_FLAG_SWITCH_VOLTAGE         BIT(28)

#define     MMC_STATUS_DATA_BUSY                BIT(9)
#define     MMC_CTRL_CONTROLLER_RESET           BIT(0)
#define     MMC_CTRL_FIFO_RESET                 BIT(1)
#define     MMC_CTRL_DMA_RESET                  BIT(2)
#define     MMC_CTRL_INT_ENABLE                 BIT(4)
#define     MMC_CTRL_USE_DMA                    BIT(25)
#define     MMC_CMD_START_CMD                   BIT(31)
#define     MMC_BMOD_RESET                      BIT(0)

#define     MMC_CLOCK_IN                        (50000000)

#define     MMC_CARD_WIDTH_1BIT                 (0)
#define     MMC_CARD_WIDTH_4BIT                 (1)

#define     MMC_INT_STATUS_CARD_DETECT          BIT(0)
#define     MMC_INT_STATUS_RESPONSE_ERROR       BIT(1)
#define     MMC_INT_STATUS_CMD_DONE             BIT(2)
#define     MMC_INT_STATUS_TRANSFER_OVER        BIT(3)
#define     MMC_INT_STATUS_TX_REQUEST           BIT(4)
#define     MMC_INT_STATUS_RX_REQUEST           BIT(5)
#define     MMC_INT_STATUS_RESP_CRC_ERROR       BIT(6)
#define     MMC_INT_STATUS_DATA_CRC_ERROR       BIT(7)
#define     MMC_INT_STATUS_RESPONSE_TIMEOUT     BIT(8)
#define     MMC_INT_STATUS_READ_TIMEOUT         BIT(9)
#define     MMC_INT_STATUS_STARVATION_TIMEOUT   BIT(10)
#define     MMC_INT_STATUS_OVERRUN_UNDERRUN     BIT(11)
#define     MMC_INT_STATUS_HARDWARE_LOCKED      BIT(12)
#define     MMC_INT_STATUS_START_BIT_ERROR      BIT(13)
#define     MMC_INT_STATUS_AUTO_CMD_DONE        BIT(14)
#define     MMC_INT_STATUS_END_BIT_ERROR        BIT(15)
#define     MMC_INT_STATUS_SDIO                 BIT(16)
#define     MMC_INT_STATUS_ALL                  (~0)

#define     MMC_INIT_STATUS_DATA_ERROR          (MMC_INT_STATUS_DATA_CRC_ERROR \
                                                | MMC_INT_STATUS_START_BIT_ERROR | MMC_INT_STATUS_END_BIT_ERROR)

#define     MMC_USE_DMA

#ifdef      MMC_USE_DMA
#define     MMC_INT_STATUS_DATA                 (MMC_INT_STATUS_TRANSFER_OVER | MMC_INIT_STATUS_DATA_ERROR)
#else
#define     MMC_INT_STATUS_DATA                 (MMC_INT_STATUS_TRANSFER_OVER | MMC_INIT_STATUS_DATA_ERROR \
                                                | MMC_INT_STATUS_TX_REQUEST | MMC_INT_STATUS_RX_REQUEST)
#endif

#define     MMC_DMA_DESC_BUFF_SIZE              (0x1f00)


typedef union
{
    struct
    {
        UINT32  reserved                            :1; //0~15
        UINT32  disable_interrupt_on_completion     :1; //16~31
        UINT32  last_descriptor                     :1; //0~15
        UINT32  first_descriptor                    :1; //16~31
        UINT32  sencond_address_chained             :1; //0~15
        UINT32  end_of_ring                         :1; //16~31
        UINT32  reserved_29_6                       :24; //0~15
        UINT32  card_error_summary                  :1; //16~31
        UINT32  own                                 :1; //16~31
    }bit;
    UINT32 dw;
}MMC_DMA_Descriptor0;

typedef union
{
    struct
    {
        UINT32  buffer1_size                        :13; //0~15
        UINT32  buffer2_size                        :13; //16~31
        UINT32  reserved_26_31                      :6; //0~15
    }bit;
    UINT32 dw;
}MMC_DMA_Descriptor1;

typedef union
{
    struct
    {
        UINT32  buffer_addr0                     :32; //0~15
    }bit;
    UINT32 dw;
}MMC_DMA_Descriptor2;

typedef union
{
    struct
    {
        UINT32  buffer_addr1                     :32; //0~15
    }bit;
    UINT32 dw;
}MMC_DMA_Descriptor3;

typedef struct
{
    MMC_DMA_Descriptor0 desc0;       /* control and status information of descriptor */
    MMC_DMA_Descriptor1 desc1;       /* buffer sizes                                 */
    MMC_DMA_Descriptor2 desc2;       /* physical address of the buffer 1             */
    MMC_DMA_Descriptor3 desc3;       /* physical address of the buffer 2             */
}MMC_DMA_Descriptors;

struct fh_mmc_obj
{
    rt_uint32_t             id;
    rt_uint32_t             irq;
    rt_uint32_t             base;
    rt_uint32_t             power_pin_gpio;
    MMC_DMA_Descriptors     *descriptors;
    void                    (*mmc_reset)(struct fh_mmc_obj *);
};

rt_inline rt_uint32_t MMC_GetCardStatus(struct fh_mmc_obj *mmc_obj)
{
    rt_uint32_t card_status = GET_REG(mmc_obj->base + OFFSET_SDC_CDETECT);

    return card_status & 0x1;
}

rt_inline void MMC_StartDma(struct fh_mmc_obj *mmc_obj)
{
    rt_uint32_t reg;

    SET_REG(mmc_obj->base + OFFSET_SDC_DBADDR, (rt_uint32_t)mmc_obj->descriptors);
    reg = GET_REG(mmc_obj->base + OFFSET_SDC_BMOD);
    reg |= 1 << 7;
    SET_REG(mmc_obj->base + OFFSET_SDC_BMOD, reg);
}

rt_inline void MMC_StopDma(struct fh_mmc_obj *mmc_obj)
{
    rt_uint32_t reg;

    reg = GET_REG(mmc_obj->base + OFFSET_SDC_BMOD);
    reg &= ~(1 << 7);
    SET_REG(mmc_obj->base + OFFSET_SDC_BMOD, reg);
}

rt_inline rt_uint32_t MMC_GetWaterlevel(struct fh_mmc_obj *mmc_obj)
{
    return (GET_REG(mmc_obj->base + OFFSET_SDC_STATUS) >> 17) & 0x1fff;
}

rt_inline rt_uint32_t MMC_GetStatus(struct fh_mmc_obj *mmc_obj)
{
    return GET_REG(mmc_obj->base + OFFSET_SDC_STATUS);
}

rt_inline rt_uint32_t MMC_GetRawInterrupt(struct fh_mmc_obj *mmc_obj)
{
    return GET_REG(mmc_obj->base + OFFSET_SDC_RINTSTS);
}

rt_inline rt_uint32_t MMC_GetUnmaskedInterrupt(struct fh_mmc_obj *mmc_obj)
{
    return GET_REG(mmc_obj->base + OFFSET_SDC_MINTSTS);
}

rt_inline rt_uint32_t MMC_ClearRawInterrupt(struct fh_mmc_obj *mmc_obj, rt_uint32_t interrupts)
{
    return SET_REG(mmc_obj->base + OFFSET_SDC_RINTSTS, interrupts);
}

rt_inline rt_uint32_t MMC_GetInterruptMask(struct fh_mmc_obj *mmc_obj)
{
    return GET_REG(mmc_obj->base + OFFSET_SDC_INTMASK);
}

rt_inline rt_uint32_t MMC_SetInterruptMask(struct fh_mmc_obj *mmc_obj, rt_uint32_t mask)
{
    return SET_REG(mmc_obj->base + OFFSET_SDC_INTMASK, mask);
}

rt_inline void MMC_SetByteCount(struct fh_mmc_obj *mmc_obj, rt_uint32_t bytes)
{
    SET_REG(mmc_obj->base + OFFSET_SDC_BYTCNT, bytes);
}

rt_inline void MMC_SetBlockSize(struct fh_mmc_obj *mmc_obj, rt_uint32_t size)
{
    SET_REG(mmc_obj->base + OFFSET_SDC_BLKSIZ, size);
}

rt_inline rt_uint32_t MMC_GetResponse(struct fh_mmc_obj *mmc_obj, int resp_num)
{
    return GET_REG(mmc_obj->base + OFFSET_SDC_RESP0 + resp_num * 4);
}

rt_inline rt_uint32_t MMC_IsFifoEmpty(struct fh_mmc_obj *mmc_obj)
{
    return (GET_REG(mmc_obj->base + OFFSET_SDC_STATUS) >> 2) & 0x1;
}

rt_inline rt_uint32_t MMC_IsDataStateBusy(struct fh_mmc_obj *mmc_obj)
{
    return (GET_REG(mmc_obj->base + OFFSET_SDC_STATUS) >> 10) & 0x1;
}

void MMC_Init(struct fh_mmc_obj *mmc_obj);
int MMC_ResetFifo(struct fh_mmc_obj *mmc_obj);
int MMC_SetCardWidth(struct fh_mmc_obj *mmc_obj, int width);
int MMC_UpdateClockRegister(struct fh_mmc_obj *mmc_obj, int div);
int MMC_SendCommand(struct fh_mmc_obj *mmc_obj, rt_uint32_t cmd, rt_uint32_t arg, rt_uint32_t flags);
int MMC_WriteData(struct fh_mmc_obj *mmc_obj, rt_uint32_t *buf, rt_uint32_t size);
int MMC_ReadData(struct fh_mmc_obj *mmc_obj, rt_uint32_t *buf, rt_uint32_t size);

inline void MMC_StartDma(struct fh_mmc_obj *mmc_obj);
inline void MMC_StopDma(struct fh_mmc_obj *mmc_obj);
void MMC_InitDescriptors(struct fh_mmc_obj *mmc_obj, rt_uint32_t *buf, rt_uint32_t size);

#endif /* FH_MMC_H_ */
