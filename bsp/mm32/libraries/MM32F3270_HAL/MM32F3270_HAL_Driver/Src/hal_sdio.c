/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hal_sdio.h"

static void SDIO_SetPeriphClockBaseClock(SDIO_Type * SDIOx, uint32_t busclk_hz, uint32_t periph_1mhz);

void SDIO_Init(SDIO_Type * SDIOx, SDIO_Init_Type * init)
{
    SDIO_Enable(SDIOx, true);

    SDIOx->MMCCTRL = SDIO_MMCCTRL_OPMSEL(1) /* SD mode as default. */
                   | SDIO_MMCCTRL_SELSM(1)   /* hardware auto mode. */
                   | SDIO_MMCCTRL_OUTM(0)    /* open drain io mode. */
                   | SDIO_MMCCTRL_CLKSP(init->ClkLineSpeedDiv)
                   | SDIO_MMCCTRL_SELPTSM(init->BaseClkSrc)
                   | SDIO_MMCCTRL_DATWT(0)   /* use 1b data width as default. */
                   | SDIO_MMCCTRL_MDEN(0)    /* SD card as default. */
                   | SDIO_MMCCTRL_INTEN(0)   /* unlock the interrupt switchers. */
                   | SDIO_MMCCTRL_RDWTEN(0)  /* disable the read wait signal. */
                   ;

    SDIOx->MMCCTRL |= SDIO_MMCCTRL_SELSM_MASK;

    if (init->BaseClkSrc == SDIO_BaseClkSrc_1MHz)
    {
        SDIO_SetPeriphClockBaseClock(SDIOx, init->BusClkHz, 1000000u);
    }

    SDIO_SetDataBusWidth(SDIOx, SDIO_DataBusWidth_1b);

    SDIOx->MMCCRCCTL = 0u; /* disable all the crc feature. */
    SDIOx->MMCIOMBCTL = 0u;
    SDIOx->MMCCRCCTL   = SDIO_MMCCRCCTL_CMDCRCEN_MASK | SDIO_MMCCRCCTL_DATCRCEN_MASK;
}

void SDIO_Enable(SDIO_Type * SDIOx, bool enable)
{
    if (enable)
    {
        SDIOx->MMCCARDSEL |= SDIO_MMCCARDSEL_CTREN_MASK  /* enable the card controller. */
                           | SDIO_MMCCARDSEL_ENPCLK_MASK /* enable the card clk. */
                           ;
    }
    else
    {
        SDIOx->MMCCARDSEL &= ~(SDIO_MMCCARDSEL_CTREN_MASK | SDIO_MMCCARDSEL_ENPCLK_MASK);
    }
}

static void SDIO_SetPeriphClockBaseClock(SDIO_Type * SDIOx, uint32_t busclk_hz, uint32_t periph_1mhz)
{
    uint32_t div = busclk_hz / periph_1mhz / 2 - 1u;

    SDIOx->MMCCARDSEL = (SDIOx->MMCCARDSEL & ~SDIO_MMCCARDSEL_TSCALE_MASK) | SDIO_MMCCARDSEL_TSCALE(div);
}

void SDIO_SetDataBusWidth(SDIO_Type *SDIOx, SDIO_DataBusWidth_Type width)
{
    if (width == SDIO_DataBusWidth_1b)
    {
        SDIOx->MMCCTRL &= ~SDIO_MMCCTRL_DATWT_MASK;
    }
    else if (width == SDIO_DataBusWidth_4b)
    {
        SDIOx->MMCCTRL |= SDIO_MMCCTRL_DATWT_MASK;
    }
}

/* return "SDIO_FLAG_XXXX." */
uint32_t SDIO_GetStatus(SDIO_Type * SDIOx)
{
    uint32_t flags = SDIOx->CLRMMCINT;

    /* add the flags for data fifo. */
    if (SDIOx->BUFCTL & SDIO_BUFCTL_DBF_MASK)
    {
        flags |= SDIO_STATUS_DAT_BUF_FULL;
    }
    if (SDIOx->BUFCTL & SDIO_BUFCTL_DBE_MASK)
    {
        flags |= SDIO_STATUS_DAT_BUF_EMPTY;
    }

    return flags;
}

/* parameter flgas, refre to "SDIO_FLAG_XXXX." */
void SDIO_ClearStatus(SDIO_Type * SDIOx, uint32_t flags)
{
    SDIOx->CLRMMCINT = (SDIO_STATUS_DAT0_BUSY - 1u) & flags;

    /* SDIO_STATUS_DAT_BUF_FULL and SDIO_STATUS_DAT_BUF_EMPYT would be cleared by hardware automatically. */
}

/* parameter interrupts, refre to "SDIO_INT_XXXX." */
void SDIO_EnableInterrupts(SDIO_Type * SDIOx, uint32_t interrupts, bool enable)
{
    if (enable)
    {
        SDIOx->MMCINTMASK |= interrupts;
    }
    else
    {
        SDIOx->MMCINTMASK &= ~interrupts;
    }

}

void SDIO_EnableFifoDMA(SDIO_Type * SDIOx, bool enable)
{
    uint32_t bufctl = SDIOx->BUFCTL & ~(SDIO_BUFCTL_DRM_MASK | SDIO_BUFCTL_DMAHEN_MASK);

    if (enable)
    {
        SDIOx->BUFCTL  = bufctl | SDIO_BUFCTL_DMAHEN_MASK ;
    }
    else
    {
        SDIOx->BUFCTL = SDIOx->BUFCTL | SDIO_BUFCTL_DRM_MASK;
    }
}

/* parameter flgas, refre to "SDIO_CMD_FLAG_XXXX." */
void SDIO_ExecuteCmd(SDIO_Type * SDIOx, uint8_t cmd_index, uint32_t param, uint32_t flags)
{
    /* setup parameter. */
    SDIOx->CMDBUF[4] = 0x40 | cmd_index;
    SDIOx->CMDBUF[3] = ((param & 0xff000000) >> 24);
    SDIOx->CMDBUF[2] = ((param & 0xff0000  ) >> 16);
    SDIOx->CMDBUF[1] = ((param & 0xff00    ) >> 8);
    SDIOx->CMDBUF[0] = ( param & 0xff      );

    /* prepare the command. */
    uint32_t cmd_io = SDIO_MMCIO_AUTOTR_MASK;
    uint32_t cmd_io_ext = SDIOx->MMCIOMBCTL
                        & ~(  SDIO_MMCIOMBCTL_SPMBDTR_MASK
                            | SDIO_MMCIOMBCTL_SMBDTD_MASK
                            | SDIO_MMCIOMBCTL_PAUTOTR_MASK );

    if (0u != (flags & (SDIO_CMD_FLAG_READ_BLOCKS | SDIO_CMD_FLAG_READ_BLOCKS) ) )
    {
        if (0u != (flags & SDIO_CMD_FLAG_READ_BLOCKS))
        {
            cmd_io_ext |= SDIO_MMCIOMBCTL_SMBDTD_MASK;
        }

        /* write MMCIO and MMCIOMBCTL to execute the cmd. */
        SDIOx->MMCIO = 0u;
        SDIOx->MMCIOMBCTL = cmd_io_ext | SDIO_MMCIOMBCTL_SPMBDTR_MASK;
    }
    else
    {
        if (0u != (flags & SDIO_CMD_FLAG_READ_BLOCK) )
        {
            cmd_io |= SDIO_MMCIO_TRANSFDIR_MASK;
        }
        if (0u != (flags & SDIO_CMD_FLAG_READ_CID_CSD) )
        {
            cmd_io |= SDIO_MMCIO_CIDCSDRD_MASK;
        }
        //if (0u != (flags & SDIO_CMD_FLAG_FOLLOWED_DATA_BLOCK) )
        //{
        //    cmd_io |= SDIO_MMCIO_CMDCH_MASK;
        //}
        //if (0u != (flags & SDIO_CMD_FLAG_STOP_TRAN) )
        //{
        //    cmd_io |= SDIO_MMCIO_CMDAF_MASK;
        //}
        if (0u != (flags & SDIO_CMD_FLAG_ENABLE_DATA_XFER) )
        {
            cmd_io |= SDIO_MMCIO_AUTODATTR_MASK;
        }
        SDIOx->MMCIOMBCTL = cmd_io_ext;
        SDIOx->MMCIO = cmd_io;
    }

    /* pending for the xfer done. */
    while ( 0u == (SDIO_STATUS_CMD_DONE & SDIO_GetStatus(SDIOx)) )
    {}
    SDIO_ClearStatus(SDIOx, SDIO_STATUS_CMD_DONE);
}

void SDIO_ExecuteData(SDIO_Type * SDIOx, uint32_t cmd_flags)
{
    uint32_t cmd_io_ext = SDIOx->MMCIOMBCTL
                    & ~(  SDIO_MMCIOMBCTL_SPMBDTR_MASK
                        | SDIO_MMCIOMBCTL_SMBDTD_MASK
                        | SDIO_MMCIOMBCTL_PAUTOTR_MASK );
    uint32_t cmd_io = 0u;

    if (0u != (cmd_flags & SDIO_CMD_FLAG_WRITE_BLOCK) )
    {
        //SDIOx->MMCIO = SDIO_MMCIO_AUTODATTR_MASK;
        cmd_io |= SDIO_MMCIO_AUTODATTR_MASK;
    }
    if (0u != (cmd_flags & SDIO_CMD_FLAG_READ_BLOCK) )
    {
        //SDIOx->MMCIO = SDIO_MMCIO_AUTODATTR_MASK | SDIO_MMCIO_TRANSFDIR_MASK;
        cmd_io |= SDIO_MMCIO_AUTODATTR_MASK | SDIO_MMCIO_TRANSFDIR_MASK;
    }
    if (0u != (cmd_flags & SDIO_CMD_FLAG_WRITE_BLOCKS) )
    {
        cmd_io_ext |= SDIO_MMCIOMBCTL_SPMBDTR_MASK;
        //SDIOx->MMCIOMBCTL = cmd_io_ext;
    }
    else if (0u != (cmd_flags & SDIO_CMD_FLAG_READ_BLOCKS) )
    {
        //SDIOx->MMCIO = SDIO_MMCIO_RESPCMDSEL_MASK | SDIO_MMCIO_AUTOTR_MASK;
        //SDIOx->MMCIOMBCTL = cmd_io_ext | SDIO_MMCIOMBCTL_SPMBDTR_MASK | SDIO_MMCIOMBCTL_SMBDTD_MASK;
        cmd_io_ext |= SDIO_MMCIOMBCTL_SPMBDTR_MASK | SDIO_MMCIOMBCTL_SMBDTD_MASK;
    }

    SDIOx->MMCIO = cmd_io;
    SDIOx->MMCIOMBCTL = cmd_io_ext;

}

void SDIO_RequestResp(SDIO_Type * SDIOx, SDIO_RespType_Type type, uint32_t *resp)
{
    uint32_t cmd_io = SDIO_MMCIO_AUTOTR_MASK | SDIO_MMCIO_RESPCMDSEL_MASK;

    if (type == SDIO_RespType_R2)
    {
        cmd_io |= SDIO_MMCIO_CIDCSDRD_MASK;
    }

    SDIOx->MMCIO = cmd_io;

    /* pending for the xfer done. */
    while ( 0u == (SDIO_STATUS_CMD_DONE & SDIO_GetStatus(SDIOx)) )
    {}
    SDIO_ClearStatus(SDIOx, SDIO_STATUS_CMD_DONE | SDIO_STATUS_CMD_CRC_ERR);


    *resp = (SDIOx->CMDBUF[3] << 24)
          | (SDIOx->CMDBUF[2] << 16)
          | (SDIOx->CMDBUF[1] << 8 )
          | (SDIOx->CMDBUF[0]);

    if (type == SDIO_RespType_R2)
    {
        resp++;
        *resp = (SDIOx->CMDBUF[7] << 24)
              | (SDIOx->CMDBUF[6] << 16)
              | (SDIOx->CMDBUF[5] << 8 )
              | (SDIOx->CMDBUF[4]);
        resp++;
        *resp = (SDIOx->CMDBUF[11] << 24)
              | (SDIOx->CMDBUF[10] << 16)
              | (SDIOx->CMDBUF[9 ] << 8 )
              | (SDIOx->CMDBUF[8 ]);
        resp++;
        *resp = (SDIOx->CMDBUF[15] << 24)
              | (SDIOx->CMDBUF[14] << 16)
              | (SDIOx->CMDBUF[13] << 8 )
              | (SDIOx->CMDBUF[12]);
    }
}

void SDIO_PutFifoData(SDIO_Type * SDIOx, uint32_t dat)
{
    SDIOx->DATABUF[0] = dat;
}

uint32_t SDIO_GetFifoData(SDIO_Type * SDIOx)
{
    return SDIOx->DATABUF[0];
}

/* SDIO_BUFCTL_DBFEN bit would be cleared automatically by hardware. */
void SDIO_ClearFifoData(SDIO_Type * SDIOx)
{
    SDIOx->BUFCTL |= SDIO_BUFCTL_DBFEN_MASK;
}

/* the direction of fifo operation is read. need to switch to write before any write operation,
 * and back to read mannually before the read operation. */
void SDIO_SwitchFifoWrite(SDIO_Type * SDIOx, bool write)
{
    if (write)
    {
        SDIOx->BUFCTL |= SDIO_BUFCTL_SBAD_MASK;
    }
    else
    {
        SDIOx->BUFCTL &= ~SDIO_BUFCTL_SBAD_MASK;
    }
}

/* word_cnt is for 32-bit type. */
void SDIO_SetFifoWatermark(SDIO_Type * SDIOx, uint32_t word_cnt)
{
    SDIOx->BUFCTL = (SDIOx->BUFCTL & ~SDIO_BUFCTL_DBML_MASK) | SDIO_BUFCTL_DBML(word_cnt);
}

void SDIO_SetMultiBlockCount(SDIO_Type * SDIOx, uint32_t blk_cnt)
{
    SDIOx->MMCBLOCKCNT = blk_cnt;
}

void     SDIO_EnableFifoReadWait(SDIO_Type * SDIOx, bool enable)
{
    if (enable)
    {
        SDIOx->MMCCTRL |= SDIO_MMCCTRL_RDWTEN_MASK;
    }
    else
    {
        SDIOx->MMCCTRL &= ~SDIO_MMCCTRL_RDWTEN_MASK;
    }
}

/* EOF. */

