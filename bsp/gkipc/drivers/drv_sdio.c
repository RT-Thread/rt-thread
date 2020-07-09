#include <rtdef.h>
#include <rtdevice.h>
#include <drivers/mmcsd_core.h>

#include <string.h>
#include <gd_int.h>
#include <gd_timer.h>
#include <gh_sdio_all.h>

#include "drv_sdio.h"
#include "platform.h"

/*
*interrupt config
*/
#define SDIO_USE_DMA    (0)
#define SDIO_INT_STATUS_EN  (1 | 1<<1 | 1<<3 | 1<<4 |1<<5 | 1<<6 | 1<<7)
#define SDIO_INT_SIG_EN     (1 | 1<<1 | 1<<3 | 1<<4 |1<<5 | 1<<6 | 1<<7)

/*config for dma*/
/* 7 -> 512Kbyte 6->256 5->128 4->64 3->32 2->16 1->8 0->4*/
#define SDIO_DEFAULT_BOUNDARY_SIZE    (64* 1024)//support max 512Kbyte,for memory issue,use 64kbyte
#define SDIO_DEFAULT_BOUNDARY_ARG     (4)

#define MMC_NOREP          (1<<0)        /* no response*/
#define MMC_REP_136        (1<<1)        /* 136 bit response */
#define MMC_REP_48         (1<<2)        /* 48 bit response */
#define MMC_REP_48_BUSY    (1<<3)        /* card may send busy */
#define MMC_REP_CRC        (1<<4)        /* expect valid crc */
#define MMC_COM_INDEX_CHEC (1<<5)        /* command index check enable */
#define MMC_DATE_PRES      (1<<6)        /* data present select */


#define MMC_RSP_NONE  (0)
#define MMC_RSP_R1    (MMC_REP_48|MMC_REP_CRC|MMC_COM_INDEX_CHEC)
#define MMC_RSP_R1B   (MMC_REP_48_BUSY|MMC_REP_CRC|MMC_COM_INDEX_CHEC)
#define MMC_RSP_R2    (MMC_REP_136|MMC_REP_CRC)
#define MMC_RSP_R3    (MMC_REP_48)
#define MMC_RSP_R4    (MMC_REP_48)
#define MMC_RSP_R5    (MMC_REP_48|MMC_REP_CRC|MMC_COM_INDEX_CHEC)
#define MMC_RSP_R6    (MMC_REP_48|MMC_REP_CRC|MMC_COM_INDEX_CHEC)
#define MMC_RSP_R7    (MMC_REP_48)

#define SDIO_IRQ_CMD_COMPLETE        0x0001
#define SDIO_IRQ_BLOCK_GAP_EVENT     0x0002
#define SDIO_IRQ_DMA                 0x0004
#define SDIO_IRQ_TRANSFER_COMPLETE   0x0008
#define SDIO_IRQ_WRITE_READY         0x0010
#define SDIO_IRQ_CARD_INSERTED       0x0020
#define SDIO_IRQ_READ_READY          0x0040
#define SDIO_IRQ_CARD_REMOVED        0x0080
#define SDIO_IRQ_CARD_INT            0x0100
#define SDIO_ERROR_IRQ               0x8000

#define MMC_STOP_TRANSMISSION    12   /* ac                      R1b         */

#ifdef CODEC_710XS
#define SDIO_SLOT_COUNT       2              /* total handle count */
#else
#define SDIO_SLOT_COUNT       1              /* total handle count */
#endif

#define SDIO_CMD_DEFAULT_TIMEOUT  3     /* FIXME, default 3s for one sdio cmd */

static GD_HANDLE inthandleArray[SDIO_SLOT_COUNT*2];
static struct gk_sdio *sdioInstancePtr[SDIO_SLOT_COUNT] = {RT_NULL};

#if SDIO_USE_DMA
static rt_uint8_t  dmBuf[SDIO_SLOT_COUNT][SDIO_DEFAULT_BOUNDARY_SIZE] __attribute__((aligned(32))) __attribute__ ((section(".nocache_buffer"))) = {0,};//64kbyte
#endif

static void sdio_soft_reset(rt_uint32_t index)
{
#ifdef CODEC_710X
    GH_SDIO_set_Control01Reg_SoftwareResetAll(index, 1);
    GH_SDIO_set_Control01Reg_SoftwareResetCmdLine(index, 1);
    GH_SDIO_set_Control01Reg_SoftwareResetDatLine(index, 1);

#elif defined GK7102C

    GH_SDIO_set_SoftResetReg_SoftwareResetAll(index,1);
    GH_SDIO_set_SoftResetReg_SoftwareResetCmdLine(index,1);
    GH_SDIO_set_SoftResetReg_SoftwareResetDatLine(index,1);
#elif defined CODEC_710XS
    GH_SDIO_set_Control01Reg_SoftwareResetAll(index,1);
    GH_SDIO_set_Control01Reg_SoftwareResetCmdLine(index,1);
    GH_SDIO_set_Control01Reg_SoftwareResetDatLine(index,1);
#endif
}

static void sdio_clock_onoff(rt_uint32_t index, rt_uint32_t on)
{
#ifdef CODEC_710X
    if (on == 0)
    {
        GH_SDIO_set_Control01Reg_SdClkEn(index, 0);
    }
    else
    {
        GH_SDIO_set_Control01Reg_SdClkEn(index, 1);
    }

#elif defined GK7102C

    if (on == 0)
    {
        GH_SDIO_set_ClkControlReg_SdClkEn(index, 0);
    }
    else
    {
        GH_SDIO_set_ClkControlReg_SdClkEn(index, 1);
    }
#elif defined CODEC_710XS

    if (on == 0)
    {
        GH_SDIO_set_Control01Reg_SdClkEn(index, 0);
    }
    else
    {
        GH_SDIO_set_Control01Reg_SdClkEn(index, 1);
    }

#endif
}

static void sdio_set_clockdiv(rt_uint32_t index, rt_uint8_t div)
{
#ifdef CODEC_710X

    GH_SDIO_set_Control01Reg_SdclkFreSelect(index, div);
    GH_SDIO_set_Control01Reg_InternalClkEn(index, 1);

    while(1)
    {
        if(GH_SDIO_get_Control01Reg_InternalClkStable(index)&0x1)
              break;
    }
    sdio_clock_onoff(index, 1);

#elif defined GK7102C
    GH_SDIO_set_ClkControlReg_SdclkFreSelect(index, div);
    GH_SDIO_set_ClkControlReg_InternalClkEn(index, 1);

    while(1)
    {
        if(GH_SDIO_get_ClkControlReg_InternalClkStable(index)&0x1)
              break;
    }
    sdio_clock_onoff(index, 1);

#elif defined CODEC_710XS

    GH_SDIO_set_Control01Reg_SdclkFreSelect(index, div);
    GH_SDIO_set_Control01Reg_InternalClkEn(index, 1);

    while(1)
    {
        if(GH_SDIO_get_Control01Reg(index)&(0x1<<16))
              break;
    }
    sdio_clock_onoff(index, 1);

#endif
}

static void sdio_select_voltage(rt_uint32_t index)
{
    rt_uint32_t caps = 0;
    caps=GH_SDIO_get_CapReg(index);

    if(caps & 0x1<<24)
    {
        GH_SDIO_set_Control00Reg_SdBusVoltageSelect(index, 0x7);
        GH_SDIO_set_Control00Reg_SdBusPower(index, 1);
    }
    else if(caps & 0x1<<25)
    {
        GH_SDIO_set_Control00Reg_SdBusVoltageSelect(index, 0x6);
        GH_SDIO_set_Control00Reg_SdBusPower(index, 1);
    }
    else if(caps & 0x1<<26)
    {
        GH_SDIO_set_Control00Reg_SdBusVoltageSelect(index, 0x5);
        GH_SDIO_set_Control00Reg_SdBusPower(index, 1);
    }

}

static void sdio_set_timeout_control(rt_uint32_t index,rt_uint8_t timeout)
{
#ifdef CODEC_710X
    GH_SDIO_set_Control01Reg_DataTimeoutCounterValue(index, timeout);
#elif defined GK7102C
    GH_SDIO_set_SoftResetReg_DataTimeoutCounterValue(index,timeout);
#elif defined CODEC_710XS
    GH_SDIO_set_SoftResetReg_DataTimeoutCounterValue(index,timeout);
#endif
}

static void sdio_set_host_ctl_speed(rt_uint32_t index, rt_uint8_t mode)
{
    GH_SDIO_set_Control00Reg_HostSpeedEn(index, mode);
}

static void sdio_set_host_ctl_width(rt_uint32_t index,rt_uint8_t mode)
{
    GH_SDIO_set_Control00Reg_DataTraWidth(index, mode);
}

static void sdio_enable_int_status(rt_uint32_t index)
{
#ifdef CODEC_710X
    /*clear int*/
    if(GH_SDIO_get_NorIntStaReg_ErrInt(index) & 0x1)
    {
        GH_SDIO_set_NorIntStaReg(index, GH_SDIO_get_NorIntStaReg(index));
        GH_SDIO_set_ErrIntStaReg(index, GH_SDIO_get_ErrIntStaReg(index));
    }
    GH_SDIO_set_NorIntStaEnReg(index, 0x0000);
    GH_SDIO_set_NorIntStaEnReg(index, SDIO_INT_STATUS_EN);
    GH_SDIO_set_ErrIntStaEnReg(index, 0xffff);

#elif defined GK7102C
    if(GH_SDIO_get_NorIntStaReg_ErrInt(index) & 0x1)
    {
        GH_SDIO_set_ErrIntStatusReg(index, \
            GH_SDIO_get_ErrIntStatusReg(index));
    }
    GH_SDIO_set_NorIntStaEnReg(index, 0x0);
    GH_SDIO_set_ErrIntStaEnReg(index, 0x0);
    GH_SDIO_set_NorIntStaEnReg_CmdCompleteStatusEn(index, 1);
    GH_SDIO_set_NorIntStaEnReg_TraCompleteStatusEn(index, 1);
    GH_SDIO_set_NorIntStaEnReg_DmaIntStatusEn(index, 1);
    GH_SDIO_set_NorIntStaEnReg_BufWReadyStatusEn(index, 1);
    GH_SDIO_set_NorIntStaEnReg_BufRReadyStatusEn(index, 1);
    GH_SDIO_set_NorIntStaEnReg_CardInsertionStatusEn(index, 1);
    GH_SDIO_set_NorIntStaEnReg_CardRemStatusEn(index, 1);
    GH_SDIO_set_ErrIntStaEnReg(index, 0xffff);

#elif defined CODEC_710XS

    if(GH_SDIO_get_ErrIntStaEnNorIntStaReg_ErrInt(index) & 0x1)
    {
        GH_SDIO_set_ErrIntStaEnNorIntStaReg(index, \
        GH_SDIO_get_ErrIntStaEnNorIntStaReg(index));
    }
    GH_SDIO_set_BlkSizeNorIntStaEnReg(index, \
    GH_SDIO_get_BlkSizeNorIntStaEnReg(index)&0x0000ffff);
    GH_SDIO_set_BlkSizeNorIntStaEnReg(index, \
    (GH_SDIO_get_BlkSizeNorIntStaEnReg(index)&0x0000ffff)|(SDIO_INT_STATUS_EN<<16));
    GH_SDIO_set_ErrIntStaEnNorIntStaReg(index, \
    GH_SDIO_get_ErrIntStaEnNorIntStaReg(index)|0x0000ffff);
#endif
}

static void sdio_enable_intsig(rt_uint32_t index)
{
#ifdef CODEC_710X
    GH_SDIO_set_NorIntSigEnReg(index, 0x0000);
    GH_SDIO_set_NorIntSigEnReg(index, SDIO_INT_SIG_EN);
    GH_SDIO_set_ErrIntSigEnReg(index, 0xffff);

#elif defined GK7102C
    GH_SDIO_set_NorIntSigEnReg(index, 0x0);
    GH_SDIO_set_ErrIntSigEnReg(index, 0x0);
    GH_SDIO_set_NorIntSigEnReg_CmdCompleteSigEn(index, 1);
    GH_SDIO_set_NorIntSigEnReg_TraCompleteSigEn(index, 1);
    GH_SDIO_set_NorIntSigEnReg_DmaIntSigEn(index, 1);
    GH_SDIO_set_NorIntSigEnReg_BufWReadySigEn(index, 1);
    GH_SDIO_set_NorIntSigEnReg_BufRReadySigEn(index, 1);
    GH_SDIO_set_NorIntSigEnReg_CardInsertionSigEn(index, 1);
    GH_SDIO_set_NorIntSigEnReg_CardRemSigEn(index, 1);
    GH_SDIO_set_ErrIntSigEnReg(index, 0xffff);
#elif defined CODEC_710XS
    GH_SDIO_set_TranModeNorIntSigEnReg(index, \
    GH_SDIO_get_TranModeNorIntSigEnReg(index)&0x0000ffff);
    GH_SDIO_set_TranModeNorIntSigEnReg(index, \
    (GH_SDIO_get_TranModeNorIntSigEnReg(index)&0x0000ffff)|(SDIO_INT_SIG_EN<<16));
    GH_SDIO_set_ErrIntSigEnBlkCouReg(index, \
    GH_SDIO_get_ErrIntSigEnBlkCouReg(index)|0x0000ffff);
#endif
}


static void sdio_set_blksize_reg(rt_uint32_t index, U16 boundary,U16 blksize)
{
#ifdef CODEC_710X
    GH_SDIO_set_BlkSizeReg_HostSdmaBufSize(index, boundary);
    GH_SDIO_set_BlkSizeReg_TraBlkSize(index, blksize);
#elif defined GK7102C
    GH_SDIO_set_BlkSizeReg_HostSdmaBufSize(index, boundary);
    GH_SDIO_set_BlkSizeReg_TraBlkSize(index, blksize);
#elif defined CODEC_710XS
    GH_SDIO_set_BlkSizeNorIntStaEnReg_HostSdmaBufSize(index, boundary);
    GH_SDIO_set_BlkSizeNorIntStaEnReg_TraBlkSize(index, blksize);
#endif
}

static void sdio_set_blkcnt_reg(rt_uint32_t index, U16  blkcnt)
{
#ifdef CODEC_710X
    GH_SDIO_set_BlkCouReg_BlkCountForCurTra(index, blkcnt);
#elif defined GK7102C
    GH_SDIO_set_BlkCouReg_BlkCountForCurTra(index, blkcnt);
#elif defined CODEC_710XS
    GH_SDIO_set_ErrIntSigEnBlkCouReg_BlkCountForCurTra(index, blkcnt);
#endif
}

static void sdio_set_arg_reg (rt_uint32_t index, rt_uint32_t arg)
{
    GH_SDIO_set_ArgReg(index, arg);
}

static rt_uint32_t sdio_set_tramode_reg (rt_uint32_t index, rt_uint32_t  multblk, rt_uint32_t direction, rt_uint32_t  autocmd12en,
    rt_uint32_t  blkcnten, rt_uint32_t  dmaen)
{
#ifdef CODEC_710X
    rt_uint32_t modereg=GH_SDIO_get_TranModeReg(index);
    modereg=(modereg & ~0xffff) | (direction << 5)| (multblk << 4) | (dmaen << 2) | (autocmd12en << 1) | (blkcnten << 0) ;
    return modereg<<16;

#elif defined GK7102C

    GH_SDIO_TRANMODEREG_S tansModRegVal;
    rt_uint32_t retVal;

    tansModRegVal.bitc.msblkselect = multblk;
    tansModRegVal.bitc.datatradirselect = direction;
    tansModRegVal.bitc.dmaen = dmaen;
    tansModRegVal.bitc.autocmd12en = autocmd12en;
    tansModRegVal.bitc.blkcounten = blkcnten;

    retVal = ((U32)tansModRegVal.all) << 16;
    return retVal;

#elif defined CODEC_710XS
    rt_uint32_t modereg=GH_SDIO_get_TranModeNorIntSigEnReg(index);
    modereg=(modereg & ~0xffff) | (multblk << 4) | (direction << 5)| (dmaen << 2) | (autocmd12en << 1) | (blkcnten << 0) ;
    return modereg<<16;

#endif
}

static void sdio_set_system_address_reg(rt_uint32_t index,rt_uint32_t addr)
{
    GH_SDIO_set_SysAddrReg(index, addr);
}
static void sdio_set_hostctl8BitMode(rt_uint8_t channel,rt_uint8_t mode)
{
#ifdef CODEC_710X
    GH_SDIO_set_Control00Reg_Sd8BitMode(channel,mode);
#elif defined GK7102C

#elif defined CODEC_710XS

#endif
}

static void sdio_reset(rt_uint8_t index)
{
    sdio_soft_reset(index);
    sdio_clock_onoff(index, 0);
#ifdef CODEC_710X
    sdio_set_clockdiv(index, 1);
#elif defined GK7102C
    sdio_set_clockdiv(index, 0x40);
#elif defined CODEC_710XS
    sdio_set_clockdiv(index, 0x02);
#endif
    sdio_select_voltage(index);
    sdio_set_timeout_control(index, 0xe);
    sdio_set_host_ctl_speed(index, 0);
    sdio_set_host_ctl_width(index, 0);
    /*clear interrupt status*/

#ifdef CODEC_710X
    GH_SDIO_set_NorIntStaReg(index, GH_SDIO_get_NorIntStaReg(index));
    GH_SDIO_set_ErrIntStaReg(index, GH_SDIO_get_ErrIntStaReg(index));
#elif defined GK7102C
    GH_SDIO_set_NorIntStaReg(index, GH_SDIO_get_NorIntStaReg(index));
    GH_SDIO_set_ErrIntStatusReg(index,  GH_SDIO_get_ErrIntStatusReg(index));
#elif defined CODEC_710XS
    GH_SDIO_set_ErrIntStaEnNorIntStaReg(index, GH_SDIO_get_ErrIntStaEnNorIntStaReg(index));
#endif
    /*card remove*/
    sdio_enable_int_status(index);
    sdio_enable_intsig(index);
}

static void sdio_power_on(rt_uint32_t index)
{
    /* Bus power on */
    GH_SDIO_set_Control00Reg_SdBusPower(index, 1);

    /* Enable SDIO interrupt */
    sdio_enable_int_status(index);
    sdio_enable_intsig(index);

#ifdef CODEC_710X
    GH_SDIO_set_NorIntStaEnReg_CardIntStatusEn(index, 1);
    GH_SDIO_set_NorIntSigEnReg_CardIntSigEN(index, 1);
#elif GK7102C
    GH_SDIO_set_NorIntStaEnReg_CardIntStatusEn(index, 1);
    GH_SDIO_set_NorIntSigEnReg_CardIntSigEN(index, 1);
#elif defined(CODEC_710XS)
    GH_SDIO_set_TranModeNorIntSigEnReg_CardIntSigEN(index, 1);
    GH_SDIO_set_BlkSizeNorIntStaEnReg_CardIntStatusEn(index, 1);
#endif

}


static void sdio_power_off(rt_uint32_t index)
{
    /* Disable SDIO interrupt */

#ifdef CODEC_710X
    GH_SDIO_set_NorIntStaReg(index, 0);
    GH_SDIO_set_ErrIntStaReg(index, 0);
#elif defined GK7102C
    GH_SDIO_set_NorIntStaReg(index, 0);
    GH_SDIO_set_ErrIntStatusReg(index,  0);
#elif defined CODEC_710XS
    GH_SDIO_set_ErrIntStaEnNorIntStaReg(index, 0);
#endif

    /* Bus power off */
    GH_SDIO_set_Control00Reg_SdBusPower(index, 0);
}

static void sdio_set_dma(rt_uint32_t index, struct rt_mmcsd_data *data,rt_uint8_t isDmaEnd)
{
#if SDIO_USE_DMA

    rt_uint32_t total_len = data->blks * data->blksize;
    rt_int32_t dma_len = 0,left_len = 0;
    rt_uint32_t offset = 0;
    rt_uint32_t read_len = 0;

    if(!data)
        return;

    offset = data->bytes_xfered;

    read_len = ((total_len - data->bytes_xfered) > SDIO_DEFAULT_BOUNDARY_SIZE)?\
            SDIO_DEFAULT_BOUNDARY_SIZE:(total_len - data->bytes_xfered);

    left_len = total_len - data->bytes_xfered;

    if(left_len <= 0 && (data->flags & DATA_DIR_WRITE))
        return;

    dma_len = (left_len > SDIO_DEFAULT_BOUNDARY_SIZE)?SDIO_DEFAULT_BOUNDARY_SIZE:left_len;

    if(data->flags & DATA_DIR_WRITE)
    {
        rt_memcpy((void *)&dmBuf[index][0],(void *)((rt_uint32_t)data->buf + offset),dma_len);
        sdio_set_system_address_reg(index,(rt_uint32_t)&dmBuf[index][0]);

        data->bytes_xfered += dma_len;
    }
    else if(data->flags & DATA_DIR_READ)
    {
        if(isDmaEnd)
        {
            rt_memcpy((void *)((rt_uint8_t *)data->buf + offset),(void *)&dmBuf[index][0],read_len);
            data->bytes_xfered += dma_len;
        }

        if(dma_len <= 0)
            return;

        //rt_memset((void *)&dmBuf[index][0],0x0,SDIO_DEFAULT_BOUNDARY_SIZE);
        sdio_set_system_address_reg(index,(rt_uint32_t)&dmBuf[index][0]);
    }

#endif

}
static void sdio_isr0(void)
{
    rt_int32_t   ret = RT_EOK;
    rt_uint32_t  index = 0;
    rt_uint32_t  bufferpos= 0,*pdata = NULL;
#ifdef CODEC_710X
    rt_uint32_t  irq_status_reg =(GH_SDIO_get_NorIntStaReg(index)| GH_SDIO_get_ErrIntStaReg(index)<<16);
#elif defined GK7102C
    rt_uint32_t irq_status_reg=(GH_SDIO_get_NorIntStaReg(index) | GH_SDIO_get_ErrIntStatusReg(index)<<16);
#elif defined CODEC_710XS
    rt_uint32_t  irq_status_reg=(((GH_SDIO_get_ErrIntStaEnNorIntStaReg(index)&0xffff0000)>>16) | \
    ((GH_SDIO_get_ErrIntStatusCommondReg(index)&0x0000ffff)<<16));
#endif

    //rt_kprintf("%s, irq_status_reg = 0x%x\n", __func__,irq_status_reg);
    if( irq_status_reg & SDIO_ERROR_IRQ )
    {

#ifdef CODEC_710X
        GH_SDIO_set_NorIntStaReg(index,GH_SDIO_get_NorIntStaReg(index));
        GH_SDIO_set_ErrIntStaReg(index,GH_SDIO_get_ErrIntStaReg(index));
        GH_SDIO_set_Control01Reg_SoftwareResetDatLine(index,1);
        GH_SDIO_set_Control01Reg_SoftwareResetCmdLine(index,1);
#elif defined GK7102C
        GH_SDIO_set_NorIntStaReg(index,GH_SDIO_get_NorIntStaReg(index));
        GH_SDIO_set_ErrIntStatusReg(index,GH_SDIO_get_ErrIntStatusReg(index));
        GH_SDIO_set_SoftResetReg_SoftwareResetDatLine(index,1);
        GH_SDIO_set_SoftResetReg_SoftwareResetCmdLine(index,1);
#elif defined CODEC_710XS
        GH_SDIO_set_ErrIntStaEnNorIntStaReg(index,GH_SDIO_get_ErrIntStaEnNorIntStaReg(index));
        *(volatile rt_int16_t *)(0x90000000+0x14) = *(volatile U16 *)(0x90000000+0x14);
        GH_SDIO_set_Control01Reg_SoftwareResetDatLine(index,1);
        GH_SDIO_set_Control01Reg_SoftwareResetCmdLine(index,1);
#endif
        rt_kprintf("%s,error irq\n",__FUNCTION__);
        ret = RT_ERROR;

        goto EXIT;

    }

    if( irq_status_reg & SDIO_IRQ_CMD_COMPLETE )
    {

#ifdef CODEC_710X
        if(GH_SDIO_get_CmdReg_RepTypeSelect(index)==1)
#elif defined GK7102C
        if(GH_SDIO_get_CommondReg_RepTypeSelect(index)==1)
#elif defined CODEC_710XS
        if(GH_SDIO_get_ErrIntStatusCommondReg_RepTypeSelect(index)==1)
#endif
        {
            sdioInstancePtr[index]->cmd->resp[0] = GH_SDIO_get_Resp3Reg(index)<<8 | (GH_SDIO_get_Resp2Reg(index) & 0xff000000)>>24;
            sdioInstancePtr[index]->cmd->resp[1] = GH_SDIO_get_Resp2Reg(index)<<8 | (GH_SDIO_get_Resp1Reg(index) & 0xff000000)>>24;
            sdioInstancePtr[index]->cmd->resp[2] = GH_SDIO_get_Resp1Reg(index)<<8 | (GH_SDIO_get_Resp0Reg(index) & 0xff000000)>>24;
            sdioInstancePtr[index]->cmd->resp[3] = GH_SDIO_get_Resp0Reg(index)<<8;
        }
        else
            sdioInstancePtr[index]->cmd->resp[0] = GH_SDIO_get_Resp0Reg(index);

#ifdef CODEC_710X
        GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_CMD_COMPLETE);
#elif defined GK7102C
        GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_CMD_COMPLETE);
#elif defined CODEC_710XS
        GH_SDIO_set_ErrIntStaEnNorIntStaReg(index, \
            (GH_SDIO_get_ErrIntStaEnNorIntStaReg(index)&0x0000ffff)|(SDIO_IRQ_CMD_COMPLETE<<16));

#endif

        if(!sdioInstancePtr[index]->cmd->data)
        {
            sdioInstancePtr[index]->cmd->err = RT_EOK;
            rt_completion_done(&(sdioInstancePtr[index]->completion));
        }

    }

    if( irq_status_reg & SDIO_IRQ_CARD_REMOVED )
    {
        sdio_reset(index);

#ifdef CODEC_710X
        GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_CARD_REMOVED);
#elif defined GK7102C
        GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_CARD_REMOVED);
#elif defined CODEC_710XS
    GH_SDIO_set_ErrIntStaEnNorIntStaReg(index, \
        (GH_SDIO_get_ErrIntStaEnNorIntStaReg(index)&0x0000ffff)|SDIO_IRQ_CARD_REMOVED<<16);
#endif
        if(sdioInstancePtr[index]->cmd)
        {
            sdioInstancePtr[index]->cmd->err = ret;
            if(sdioInstancePtr[index]->cmd->data)
                sdioInstancePtr[index]->cmd->data->err = ret;
        }

        rt_completion_done(&(sdioInstancePtr[index]->completion));
        mmcsd_change(sdioInstancePtr[index]->host);

    }
    else if( irq_status_reg & SDIO_IRQ_CARD_INSERTED )
    {
#ifdef CODEC_710X
        GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_CARD_INSERTED);
#elif defined GK7102C
        GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_CARD_INSERTED);
#elif defined CODEC_710XS
        GH_SDIO_set_ErrIntStaEnNorIntStaReg(index, \
            (GH_SDIO_get_ErrIntStaEnNorIntStaReg(index)&0x0000ffff)|(SDIO_IRQ_CARD_INSERTED<<16));

#endif
        mmcsd_change(sdioInstancePtr[index]->host);
    }

    if( irq_status_reg & SDIO_IRQ_READ_READY )
    {

#ifdef CODEC_710X
        if (!(GH_SDIO_get_PresentStateReg(index) & 0x1<<11))
#elif defined GK7102C
        if (!(GH_SDIO_get_PresentStateReg_BufREn(index)))
#elif defined CODEC_710XS
        if (!(GH_SDIO_get_PresentStateReg(index) & 0x1<<11))
#endif
        {
            ret = RT_EBUSY;
            goto EXIT;
        }
        else
        {
#ifdef CODEC_710X
            GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_READ_READY);
#elif defined GK7102C
            GH_SDIO_set_NorIntStaReg(index,SDIO_IRQ_READ_READY);
#elif defined CODEC_710XS
            GH_SDIO_set_ErrIntStaEnNorIntStaReg(index, \
            (GH_SDIO_get_ErrIntStaEnNorIntStaReg(index)&0x0000ffff)|(SDIO_IRQ_READ_READY<<16));

#endif

            if(!sdioInstancePtr[index]->cmd)
                return;

            if(!sdioInstancePtr[index]->cmd->data)
                return;

            if(!sdioInstancePtr[index]->cmd->data->buf)
                return;

            pdata = sdioInstancePtr[index]->cmd->data->buf + sdioInstancePtr[index]->cmd->data->bytes_xfered/4;
            while( bufferpos < sdioInstancePtr[index]->cmd->data->blksize)
            {
                *pdata++ = GH_SDIO_get_BufferDataPortReg(index);
                bufferpos += 4;
                sdioInstancePtr[index]->cmd->data->bytes_xfered += 4;
            }

        }

    }

    if( irq_status_reg & SDIO_IRQ_WRITE_READY )
    {

#ifdef CODEC_710X
        if (!(GH_SDIO_get_PresentStateReg(index) & 0x1<<10))
#elif defined GK7102C
        if (!(GH_SDIO_get_PresentStateReg_BufWEn(index)))
#elif defined CODEC_710XS
        if (!(GH_SDIO_get_PresentStateReg(index) & 0x1<<10))
#endif
        {
            ret = RT_EBUSY;
            goto EXIT;
        }
        else
        {
#ifdef CODEC_710X
            GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_WRITE_READY);
#elif defined GK7102C
            GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_WRITE_READY);//|(SDIO_IRQ_WRITE_READY<<16));
#elif defined CODEC_710XS
            GH_SDIO_set_ErrIntStaEnNorIntStaReg(index, \
                (GH_SDIO_get_ErrIntStaEnNorIntStaReg(index)&0x0000ffff)|(SDIO_IRQ_WRITE_READY<<16));//|(SDIO_IRQ_WRITE_READY<<16));

#endif
            if(!sdioInstancePtr[index]->cmd)
                return;

            if(!sdioInstancePtr[index]->cmd->data)
                return;

            if(!sdioInstancePtr[index]->cmd->data->buf)
                return;

            pdata = sdioInstancePtr[index]->cmd->data->buf + sdioInstancePtr[index]->cmd->data->bytes_xfered/4;
            while( bufferpos < sdioInstancePtr[index]->cmd->data->blksize )
            {
                GH_SDIO_set_BufferDataPortReg(index, *pdata++);
                bufferpos += 4;
                sdioInstancePtr[index]->cmd->data->bytes_xfered += 4;
            }

        }
    }

    if(irq_status_reg & SDIO_IRQ_DMA)//FIXME,need check
    {
#ifdef CODEC_710X
        GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_DMA);
#elif defined GK7102C
        GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_DMA);
#elif defined CODEC_710XS
        GH_SDIO_set_ErrIntStaEnNorIntStaReg(index, \
            (GH_SDIO_get_ErrIntStaEnNorIntStaReg(index)&0x0000ffff)|(SDIO_IRQ_DMA<<16));
#endif

        if(!sdioInstancePtr[index]->cmd)
            return;

        if(!sdioInstancePtr[index]->cmd->data)
            return;

        if(!sdioInstancePtr[index]->cmd->data->buf)
            return;

        sdio_set_dma(index,sdioInstancePtr[index]->cmd->data,1);

    }

    if( irq_status_reg & SDIO_IRQ_TRANSFER_COMPLETE )
    {
#ifdef CODEC_710X
        GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_TRANSFER_COMPLETE);
#elif defined GK7102C
        GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_TRANSFER_COMPLETE);
#elif defined CODEC_710XS
        GH_SDIO_set_ErrIntStaEnNorIntStaReg(index, \
            (GH_SDIO_get_ErrIntStaEnNorIntStaReg(index)&0x0000ffff)|(SDIO_IRQ_TRANSFER_COMPLETE<<16));
#endif
        ret = RT_EOK;

        if(!sdioInstancePtr[index]->cmd)
            goto EXIT;

        if(!sdioInstancePtr[index]->cmd->data)
            goto EXIT;

        if(!sdioInstancePtr[index]->cmd->data->buf)
            goto EXIT;

        if(sdioInstancePtr[index]->cmd->data->flags & DATA_DIR_READ)
            sdio_set_dma(index,sdioInstancePtr[index]->cmd->data,1);

        goto EXIT;
    }

    if( irq_status_reg & SDIO_IRQ_CARD_INT )
    {
        do
        {
            if(!sdioInstancePtr[index])
                goto CASE2;

            if(!sdioInstancePtr[index]->host)
                goto CASE2;

            if(!sdioInstancePtr[index]->host->sdio_irq_sem)
                goto CASE2;

        CASE1:
            sdio_irq_wakeup(sdioInstancePtr[index]->host);
            break;

        CASE2:
#ifdef CODEC_710X
            GH_SDIO_set_NorIntStaEnReg_CardIntStatusEn(index, 0);
            GH_SDIO_set_NorIntSigEnReg_CardIntSigEN(index, 0);
#elif GK7102C
            GH_SDIO_set_NorIntStaEnReg_CardIntStatusEn(index, 0);
            GH_SDIO_set_NorIntSigEnReg_CardIntSigEN(index, 0);
#elif defined(CODEC_710XS)
            GH_SDIO_set_TranModeNorIntSigEnReg_CardIntSigEN(index, 0);
            GH_SDIO_set_BlkSizeNorIntStaEnReg_CardIntStatusEn(index, 0);
#endif

        }while(0);

    }

    return;

EXIT:

    if(sdioInstancePtr[index]->cmd)
    {
        sdioInstancePtr[index]->cmd->err = ret;
        if(sdioInstancePtr[index]->cmd->data)
            sdioInstancePtr[index]->cmd->data->err = ret;
    }

    rt_completion_done(&(sdioInstancePtr[index]->completion));
}

#ifdef CODEC_710X

static void sdio_isr1(void)
{

}

#else
static void sdio_isr1(void)
{
    rt_int32_t   ret = RT_EOK;
    rt_uint8_t   index = 1;
    rt_uint32_t  bufferpos= 0;
    rt_uint32_t  *pdata;

#ifdef GK7102C
    rt_uint32_t irq_status_reg=(GH_SDIO_get_NorIntStaReg(index) | \
        GH_SDIO_get_ErrIntStatusReg(index)<<16);
#else
    rt_uint32_t  irq_status_reg=(((GH_SDIO_get_ErrIntStaEnNorIntStaReg(index)&0xffff0000)>>16) | \
        ((GH_SDIO_get_ErrIntStatusCommondReg(index)&0x0000ffff)<<16));

#endif

    //rt_kprintf("%s, irq_status_reg = 0x%x\n", __func__,irq_status_reg);

    if( irq_status_reg & SDIO_ERROR_IRQ )
    {
#ifdef GK7102C
        GH_SDIO_set_NorIntStaReg(index,GH_SDIO_get_NorIntStaReg(index));
        GH_SDIO_set_ErrIntStatusReg(index,GH_SDIO_get_ErrIntStatusReg(index));
        GH_SDIO_set_SoftResetReg_SoftwareResetDatLine(index,1);
        GH_SDIO_set_SoftResetReg_SoftwareResetCmdLine(index,1);
#else
        GH_SDIO_set_ErrIntStaEnNorIntStaReg(index,GH_SDIO_get_ErrIntStaEnNorIntStaReg(index));
        *(volatile U16 *)(0x90010000+0x14) = *(volatile U16 *)(0x90010000+0x14);
        GH_SDIO_set_Control01Reg_SoftwareResetDatLine(index,1);
        GH_SDIO_set_Control01Reg_SoftwareResetCmdLine(index,1);

#endif
        ret = RT_ERROR;

        goto EXIT;

    }

    if( irq_status_reg & SDIO_IRQ_CMD_COMPLETE )
    {
#ifdef GK7102C
        if(GH_SDIO_get_CommondReg_RepTypeSelect(index)==1)
#else
        if(GH_SDIO_get_ErrIntStatusCommondReg_RepTypeSelect(index)==1)
#endif
        {
            sdioInstancePtr[index]->cmd->resp[0] = GH_SDIO_get_Resp3Reg(index)<<8 | (GH_SDIO_get_Resp2Reg(index) & 0xff000000)>>24;
            sdioInstancePtr[index]->cmd->resp[1] = GH_SDIO_get_Resp2Reg(index)<<8 | (GH_SDIO_get_Resp1Reg(index) & 0xff000000)>>24;
            sdioInstancePtr[index]->cmd->resp[2] = GH_SDIO_get_Resp1Reg(index)<<8 | (GH_SDIO_get_Resp0Reg(index) & 0xff000000)>>24;
            sdioInstancePtr[index]->cmd->resp[3] = GH_SDIO_get_Resp0Reg(index)<<8;
        }
        else
            sdioInstancePtr[index]->cmd->resp[0] = GH_SDIO_get_Resp0Reg(index);
#ifdef GK7102C
        GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_CMD_COMPLETE);
#else
        GH_SDIO_set_ErrIntStaEnNorIntStaReg(index, \
            (GH_SDIO_get_ErrIntStaEnNorIntStaReg(index)&0x0000ffff)|(SDIO_IRQ_CMD_COMPLETE<<16));

#endif
        if(!sdioInstancePtr[index]->cmd->data)
        {
            sdioInstancePtr[index]->cmd->err = RT_EOK;
            rt_completion_done(&(sdioInstancePtr[index]->completion));
        }

    }

    if( irq_status_reg & SDIO_IRQ_CARD_REMOVED )
    {
        sdio_reset(index);

#ifdef GK7102C
        GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_CARD_REMOVED);
#else
        GH_SDIO_set_ErrIntStaEnNorIntStaReg(index, \
            (GH_SDIO_get_ErrIntStaEnNorIntStaReg(index)&0x0000ffff)|SDIO_IRQ_CARD_REMOVED<<16);

#endif
        if(sdioInstancePtr[index]->cmd)
        {
            sdioInstancePtr[index]->cmd->err = ret;
            if(sdioInstancePtr[index]->cmd->data)
                sdioInstancePtr[index]->cmd->data->err = ret;
        }

        rt_completion_done(&(sdioInstancePtr[index]->completion));
        mmcsd_change(sdioInstancePtr[index]->host);
    }
    else if( irq_status_reg & SDIO_IRQ_CARD_INSERTED )
    {
#ifdef GK7102C
        GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_CARD_INSERTED);
#else
        GH_SDIO_set_ErrIntStaEnNorIntStaReg(index, \
            (GH_SDIO_get_ErrIntStaEnNorIntStaReg(index)&0x0000ffff)|(SDIO_IRQ_CARD_INSERTED<<16));

#endif

        mmcsd_change(sdioInstancePtr[index]->host);
    }

    if( irq_status_reg & SDIO_IRQ_READ_READY )
    {
#ifdef GK7102C
        if (!(GH_SDIO_get_PresentStateReg_BufREn(index)))
#else
        if (!(GH_SDIO_get_PresentStateReg(index) & 0x1<<11))
#endif
        {
            ret = RT_EBUSY;

            goto EXIT;
        }
        else
        {
#ifdef GK7102C
            GH_SDIO_set_NorIntStaReg(index,SDIO_IRQ_READ_READY);
#else
            GH_SDIO_set_ErrIntStaEnNorIntStaReg(index, \
                (GH_SDIO_get_ErrIntStaEnNorIntStaReg(index)&0x0000ffff)|(SDIO_IRQ_READ_READY<<16));
#endif
            if(!sdioInstancePtr[index]->cmd)
                return;

            if(!sdioInstancePtr[index]->cmd->data)
                return;

            if(!sdioInstancePtr[index]->cmd->data->buf)
                return;

            pdata = sdioInstancePtr[index]->cmd->data->buf + sdioInstancePtr[index]->cmd->data->bytes_xfered/4;
            while( bufferpos < sdioInstancePtr[index]->cmd->data->blksize)
            {
                *pdata++ = GH_SDIO_get_BufferDataPortReg(index);
                bufferpos += 4;
                sdioInstancePtr[index]->cmd->data->bytes_xfered += 4;
            }
        }

    }

    if( irq_status_reg & SDIO_IRQ_WRITE_READY )
    {
#ifdef GK7102C
        if (!(GH_SDIO_get_PresentStateReg_BufWEn(index)))
#else
        if (!(GH_SDIO_get_PresentStateReg(index) & 0x1<<10))
#endif
        {
            ret = RT_EBUSY;

            goto EXIT;
        }
        else
        {
#ifdef GK7102C
            GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_WRITE_READY);//|(SDIO_IRQ_WRITE_READY<<16));
#else
            GH_SDIO_set_ErrIntStaEnNorIntStaReg(index, \
                (GH_SDIO_get_ErrIntStaEnNorIntStaReg(index)&0x0000ffff)|(SDIO_IRQ_WRITE_READY<<16));//|(SDIO_IRQ_WRITE_READY<<16));

#endif
            if(!sdioInstancePtr[index]->cmd)
                return;

            if(!sdioInstancePtr[index]->cmd->data)
                return;

            if(!sdioInstancePtr[index]->cmd->data->buf)
                return;

            pdata = sdioInstancePtr[index]->cmd->data->buf + sdioInstancePtr[index]->cmd->data->bytes_xfered/4;
            while( bufferpos < sdioInstancePtr[index]->cmd->data->blksize)
            {
                GH_SDIO_set_BufferDataPortReg(index, *pdata++);
                bufferpos += 4;
                sdioInstancePtr[index]->cmd->data->bytes_xfered += 4;
            }

        }
    }

    if(irq_status_reg & SDIO_IRQ_DMA)//FIXME,need check
    {
#ifdef GK7102C
        GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_DMA);
#else
        GH_SDIO_set_ErrIntStaEnNorIntStaReg(index, \
            (GH_SDIO_get_ErrIntStaEnNorIntStaReg(index)&0x0000ffff)|(SDIO_IRQ_DMA<<16));
#endif
        if(!sdioInstancePtr[index]->cmd)
            return;

        if(!sdioInstancePtr[index]->cmd->data)
            return;

        if(!sdioInstancePtr[index]->cmd->data->buf)
            return;

        sdio_set_dma(index,sdioInstancePtr[index]->cmd->data,1);
    }

    if( irq_status_reg & SDIO_IRQ_TRANSFER_COMPLETE )
    {
#ifdef GK7102C
        GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_TRANSFER_COMPLETE);
#else
        GH_SDIO_set_ErrIntStaEnNorIntStaReg(index, \
            (GH_SDIO_get_ErrIntStaEnNorIntStaReg(index)&0x0000ffff)|(SDIO_IRQ_TRANSFER_COMPLETE<<16));
#endif
        ret = RT_EOK;

        if(!sdioInstancePtr[index]->cmd)
            goto EXIT;

        if(!sdioInstancePtr[index]->cmd->data)
            goto EXIT;

        if(!sdioInstancePtr[index]->cmd->data->buf)
            goto EXIT;

        if(sdioInstancePtr[index]->cmd->data->flags & DATA_DIR_READ)
            sdio_set_dma(index,sdioInstancePtr[index]->cmd->data,1);

        goto EXIT;
    }

    if( irq_status_reg & SDIO_IRQ_CARD_INT )
    {
        do
        {
            if(!sdioInstancePtr[index])
                goto CASE2;

            if(!sdioInstancePtr[index]->host)
                goto CASE2;

            if(!sdioInstancePtr[index]->host->sdio_irq_sem)
                goto CASE2;

        CASE1:
            sdio_irq_wakeup(sdioInstancePtr[index]->host);
            break;

        CASE2:
#ifdef CODEC_710X
            GH_SDIO_set_NorIntStaEnReg_CardIntStatusEn(index, 0);
            GH_SDIO_set_NorIntSigEnReg_CardIntSigEN(index, 0);
#elif GK7102C
            GH_SDIO_set_NorIntStaEnReg_CardIntStatusEn(index, 0);
            GH_SDIO_set_NorIntSigEnReg_CardIntSigEN(index, 0);
#elif defined(CODEC_710XS)
            GH_SDIO_set_TranModeNorIntSigEnReg_CardIntSigEN(index, 0);
            GH_SDIO_set_BlkSizeNorIntStaEnReg_CardIntStatusEn(index, 0);
#endif

        }while(0);

    }

    return;

EXIT:

    if(sdioInstancePtr[index]->cmd)
    {
        sdioInstancePtr[index]->cmd->err = ret;
        if(sdioInstancePtr[index]->cmd->data)
            sdioInstancePtr[index]->cmd->data->err = ret;
    }

    rt_completion_done(&(sdioInstancePtr[index]->completion));
}

#endif

static rt_int32_t sdio_init(rt_uint32_t index)
{
    rt_int32_t ret;
    GD_INT_OPEN_PARAMS_S     intParams;

#ifdef CODEC_710XS
    rt_int8_t detect_irq[SDIO_SLOT_COUNT] = {GD_INT_SD_CARD_DETECT_IRQ, GD_INT_SD2_CARD_DETECT_IRQ};
    rt_int8_t ctl_irq[SDIO_SLOT_COUNT]  = {GD_INT_SD_CONTROLLER_IRQ, GD_INT_SD2_CONTROLLER_IRQ};
#else
    rt_int8_t detect_irq[SDIO_SLOT_COUNT] = {GD_INT_SD_CARD_DETECT_IRQ};
    rt_int8_t ctl_irq[SDIO_SLOT_COUNT]  = {GD_INT_SD_CONTROLLER_IRQ};
#endif
    rt_int8_t i = (index == 0)? 0:2;

    intParams.type           = ctl_irq[index];
    intParams.sensitivity    = GD_INT_LEVEL_HIGH;
    intParams.active         = GD_INT_INVERT_IRQ;
    intParams.priority       = GD_INT_MID_PRIORITY;
    intParams.isrFct.lowPrio = (index == 0)? sdio_isr0:sdio_isr1;
    ret = GD_INT_Open(&intParams, &inthandleArray[i]);
    if(ret != 0)
    {
        return -RT_ERROR;
    }

    GD_INT_Enable(&inthandleArray[i],GD_INT_ENABLED);
    /*open the sdio detec interrupt*/
    intParams.type           = detect_irq[index];
    intParams.sensitivity    = GD_INT_BOTH_EDGES;
    intParams.active         = GD_INT_INVERT_IRQ;
    intParams.priority       = GD_INT_MID_PRIORITY;
    intParams.isrFct.lowPrio = (index == 0)? sdio_isr0:sdio_isr1;
    ret = GD_INT_Open(&intParams, &inthandleArray[i+1]);
    if(ret != 0)
    {
        return -RT_ERROR;
    }

    GD_INT_Enable(&inthandleArray[i+1],GD_INT_ENABLED);
    if(ret != 0)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_uint8_t sdio_get_inserted_flag(rt_uint32_t index)
{
    return ((GH_SDIO_get_PresentStateReg(index)&0x00070000) == 0x00070000);
}

static void sdio_set_cmd_reg(rt_uint32_t index,rt_uint32_t cmdarg,rt_uint32_t data,rt_uint32_t flags)
{
#ifdef GK7102C

    rt_uint8_t cmd = cmdarg & 0x3f;
    rt_uint16_t transMod = cmdarg >> 16;
    GH_SDIO_COMMONDREG_S commRegVal;

    commRegVal.all = 0;
    commRegVal.bitc.cmdindex = cmd;

    if(cmd == 12)
    {
        /*abort cmd*/
        commRegVal.bitc.cmdtype = 3;
    }
    else
    {
        /*suspend/resume cmd(sdio)*/
    }

    if (flags & MMC_REP_136)                /* Long REP */
    {
        commRegVal.bitc.reptypeselect = 1;
    }
    else if (flags & MMC_REP_48_BUSY)        /* R1B */
    {
        commRegVal.bitc.reptypeselect = 3;
    }
    else if (flags & MMC_REP_48)            /* Normal REP */
    {
        commRegVal.bitc.reptypeselect = 2;
    }

    if (flags & MMC_COM_INDEX_CHEC)
    {
        commRegVal.bitc.cmdindexchecken = 1;
    }

    if (flags & MMC_REP_CRC)
    {
        commRegVal.bitc.cmdcrcchecken = 1;
    }

    if (data)
    {
        commRegVal.bitc.datapreselect = 1;
    }

    GH_SDIO_set_TranModeReg(index, transMod);
    GH_SDIO_set_CommondReg(index, commRegVal.all);
#else

    rt_uint8_t cmd=cmdarg & 0x3f;
    unsigned short cmdval=(cmd<<8);

    if(cmd == MMC_STOP_TRANSMISSION)
    {
        /*abort cmd*/
        cmdval |=(3<<6);
    }
    else
    {
        /*suspend/resume cmd(sdio)*/
    }

    if (flags & MMC_REP_136)                /* Long REP */
    {
        cmdval |= 0x01;
    }
    else if (flags & MMC_REP_48_BUSY)        /* R1B */
    {
        cmdval |= 0x03;
    }
    else if (flags & MMC_REP_48)            /* Normal REP */
    {
        cmdval |= 0x02;
    }

    if (flags & MMC_COM_INDEX_CHEC)
    {
        cmdval |= (1<<5);
    }

    if (flags & MMC_REP_CRC)
    {
        cmdval |= (1<<3);
    }

    if (data)
    {
        cmdval |= (1<<4);
    }

    #ifdef CODEC_710X

    GH_SDIO_set_TranModeReg(index, cmdarg>>16);
    GH_SDIO_set_CmdReg(index, cmdval);

    #elif defined(CODEC_710XS)

    GH_SDIO_set_TranModeNorIntSigEnReg(index, \
        (GH_SDIO_get_TranModeNorIntSigEnReg(index)&0xffff0000)|(cmdarg>>16));
    GH_SDIO_set_ErrIntStatusCommondReg(index, \
        (GH_SDIO_get_ErrIntStatusCommondReg(index)&0x0000ffff)|(cmdval<<16));

    #endif

#endif
}

static int sdio_issue_cmd(rt_uint8_t index,rt_uint32_t cmd, rt_uint32_t arg, rt_uint32_t data, rt_uint32_t flags)
{
    int i;

    if(data == 0)
    {
        /*wait for cmd line free */
        for(i = 0; i < 0x1000; i++)
        {
            if(!(GH_SDIO_get_PresentStateReg_CmdInhibitCmd(index)))
                break;
            GD_TIMER_Delay(10);
        }

        if (i >= 0x1000)
        {
            return -RT_EBUSY;
        }
    }
    else
    {
        /*wait for data line (Cmd_inhibit_dat) free */
        if(flags & MMC_REP_48_BUSY && cmd != MMC_STOP_TRANSMISSION)
        {
             for(i = 0; i < 0x1000; i++)
             {
                 if(!(GH_SDIO_get_PresentStateReg_CmdInhibitData(index)))
                     break;
                 GD_TIMER_Delay(10);
             }

             if (i >= 0x1000)
             {
                return -RT_EBUSY;
             }
        }
    }

    sdio_set_arg_reg(index, arg);
    sdio_set_cmd_reg(index,cmd,data,flags);

    return RT_EOK;
}

static void sdio_send_command(struct gk_sdio *sdiodrv, struct rt_mmcsd_cmd *cmd)
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t cmd_flags = 0,tmp_cmd = 0;
    rt_uint8_t multblk = 0,readop = 1,timeout = SDIO_CMD_DEFAULT_TIMEOUT;
    struct gk_sdio_info *sdio_info;
    struct rt_mmcsd_data *data;

    if (!sdiodrv || !cmd)
    {
        rt_kprintf("ERROR: %s, params is NULL\n", __func__);
        return;
    }

    sdio_info = (struct gk_sdio_info *)sdiodrv->priv;


    data = cmd->data;

    rt_enter_critical();
    sdiodrv->cmd = cmd;
    sdiodrv->req = cmd->mrq;
    rt_exit_critical();


    if (data)
    {
        data->bytes_xfered = 0;

        sdio_set_dma(sdio_info->id,data,0);
        sdio_set_blksize_reg(sdio_info->id, SDIO_DEFAULT_BOUNDARY_ARG,data->blksize);
        sdio_set_blkcnt_reg(sdio_info->id, data->blks);

        if(data->flags & DATA_DIR_WRITE)
            readop = 0;

        if(data->blks > 1)
            multblk = 1;

        if((data->stop != RT_NULL) && multblk)
        {
            if(data->stop->cmd_code == MMC_STOP_TRANSMISSION)
                tmp_cmd = sdio_set_tramode_reg(sdio_info->id,multblk,readop,1,multblk,SDIO_USE_DMA);
            else
                tmp_cmd = sdio_set_tramode_reg(sdio_info->id,multblk,readop,0,multblk,SDIO_USE_DMA);
        }
        else
            tmp_cmd = sdio_set_tramode_reg(sdio_info->id,multblk,readop,0,multblk,SDIO_USE_DMA);

    }

    switch (resp_type(cmd))
    {
        case RESP_NONE:
            cmd_flags = MMC_RSP_NONE;
            break;
        case RESP_R1:
            cmd_flags = MMC_RSP_R1;
            break;
        case RESP_R2:
            cmd_flags = MMC_RSP_R2;
            break;
        case RESP_R3:
            cmd_flags = MMC_RSP_R3;
            break;
        case RESP_R4:
            cmd_flags = MMC_RSP_R4;
            break;
        case RESP_R5:
            cmd_flags = MMC_RSP_R5;
            break;
        case RESP_R6:
            cmd_flags = MMC_RSP_R6;
            break;
        case RESP_R7:
            cmd_flags = MMC_RSP_R7;
            break;
        case RESP_R1B:
            cmd_flags = MMC_RSP_R1B;
            break;
        default:
            rt_kprintf("ERROR: %s, unknown cmd type %x\n", __func__, resp_type(cmd));
            return;
    }

    tmp_cmd |= cmd->cmd_code;

    ret = sdio_issue_cmd(sdio_info->id, tmp_cmd, cmd->arg, (data != RT_NULL), cmd_flags);

    if(ret != RT_EOK)
    {
        rt_kprintf("\n%s, issue cmd timeout!\n",__func__);
        rt_kprintf("\ntmp_cmd: %d, cmd code: %d, args: 0x%x, resp type: 0x%x, dataflag: 0x%x, cmdflag: 0x%x\n",tmp_cmd, cmd->cmd_code, cmd->arg, resp_type(cmd), (data != RT_NULL),cmd_flags);
        if(data == RT_NULL)
            cmd->err = RT_ETIMEOUT;

        return;
    }

    rt_completion_init(&sdiodrv->completion);
    ret = rt_completion_wait(&sdiodrv->completion, RT_TICK_PER_SECOND * timeout);
    if(ret != RT_EOK)
    {
        rt_kprintf("\n%s, cmd process timeout!\n",__func__);
        rt_kprintf("\ntmp_cmd: %d, cmd code: %d, args: 0x%x, resp type: 0x%x, dataflag: 0x%x, cmdflag: 0x%x\n",tmp_cmd, cmd->cmd_code, cmd->arg, resp_type(cmd), (data != RT_NULL),cmd_flags);
        if(data == RT_NULL)
            cmd->err = RT_ETIMEOUT;

        return;
    }

}


static void gk_sdio_set_iocfg(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg)
{
    int ret;
    rt_uint32_t clkdiv;
    struct gk_sdio *sdio_drv;
    struct gk_sdio_info *sdio_info;

    if(!host || !io_cfg)
        return;

    //rt_kprintf("\nclock: %d, vdd: %d, bus_mode: %d, bus_width: %d\n",io_cfg->clock,io_cfg->vdd,io_cfg->bus_mode,io_cfg->bus_width);
    sdio_drv = host->private_data;
    sdio_info = (struct gk_sdio_info *)sdio_drv->priv;

    switch (io_cfg->power_mode)
    {
        case MMCSD_POWER_OFF:
            sdio_power_off(sdio_info->id);
            break;
        case MMCSD_POWER_UP:
            break;
        case MMCSD_POWER_ON:
            sdio_power_on(sdio_info->id);
            break;
        default:
            break;
    }

    if (io_cfg->bus_width == MMCSD_BUS_WIDTH_1)
        sdio_set_host_ctl_width(sdio_info->id,0);
    else if(io_cfg->bus_width == MMCSD_BUS_WIDTH_4)
        sdio_set_host_ctl_width(sdio_info->id,1);
    else if(io_cfg->bus_width == MMCSD_BUS_WIDTH_8)
    {
        sdio_set_host_ctl_width(sdio_info->id,0);
        sdio_set_hostctl8BitMode(sdio_info->id,1);
    }

    if (io_cfg->vdd)
        sdio_select_voltage(sdio_info->id);

    if (io_cfg->clock > 25000000) //FIXME:need check
    {
#ifdef CODEC_710X
        sdio_set_host_ctl_speed(sdio_info->id,1);
        sdio_clock_onoff(sdio_info->id, 0);
        sdio_set_clockdiv(sdio_info->id, 0);
#else
        sdio_set_host_ctl_speed(sdio_info->id,0);
        sdio_clock_onoff(sdio_info->id, 0);
        sdio_set_clockdiv(sdio_info->id, 1);
#endif
    }
    else
    {
        sdio_set_host_ctl_speed(sdio_info->id,0);
        sdio_clock_onoff(sdio_info->id, 0);
        sdio_set_clockdiv(sdio_info->id, 1);
    }

}

static void gk_sdio_enable_sdio_irq(struct rt_mmcsd_host *host,rt_int32_t enable)
{
    int ret;
    struct gk_sdio *sdio_drv;
    struct gk_sdio_info *sdio_info;

    if(!host)
        return;

    sdio_drv = host->private_data;
    sdio_info = (struct gk_sdio_info *)sdio_drv->priv;

    //rt_kprintf("\n%s, enable:%d\n", __func__,enable);
#ifdef CODEC_710X
    GH_SDIO_set_NorIntStaEnReg_CardIntStatusEn(sdio_info->id, enable);
    GH_SDIO_set_NorIntSigEnReg_CardIntSigEN(sdio_info->id, enable);
#elif GK7102C
    GH_SDIO_set_NorIntStaEnReg_CardIntStatusEn(sdio_info->id, enable);
    GH_SDIO_set_NorIntSigEnReg_CardIntSigEN(sdio_info->id, enable);
#elif defined(CODEC_710XS)
    GH_SDIO_set_TranModeNorIntSigEnReg_CardIntSigEN(sdio_info->id, enable);
    GH_SDIO_set_BlkSizeNorIntStaEnReg_CardIntStatusEn(sdio_info->id, enable);
#endif

}

static void gk_sdio_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    int ret;

    struct gk_sdio *sdio_drv = (struct gk_sdio *)host->private_data;
    struct gk_sdio_info *sdio_info = (struct gk_sdio_info *)sdio_drv->priv;

    if (!host || !req || !sdio_drv)
    {
        rt_kprintf("ERROR: %s, params is NULL\n", __func__);
        return;
    }

    if(sdio_info->type != SDIO_DEVICE_TYPE_WIFI)
    {
        if (!sdio_get_inserted_flag(sdio_info->id))
        {
            if(req->cmd)
                req->cmd->err = -RT_EIO;

            mmcsd_req_complete(host);

            return;
        }
    }

    if(req->cmd)
        sdio_send_command(sdio_drv, req->cmd);

#if 0
    if(req->stop && req->stop != req->cmd )
        sdio_send_command(sdio_drv, req->stop);
#endif

    rt_enter_critical();
    sdio_drv->cmd = RT_NULL;
    sdio_drv->req = RT_NULL;
    rt_exit_critical();

    mmcsd_req_complete(host);

}

static rt_int32_t gk_sdio_get_card_status(struct rt_mmcsd_host *host)
{
    return 0;
}


static const struct rt_mmcsd_host_ops gk_sdio_ops = {

    .request         = gk_sdio_request,
    .set_iocfg       = gk_sdio_set_iocfg,
    .get_card_status = gk_sdio_get_card_status,
    .enable_sdio_irq = gk_sdio_enable_sdio_irq,
};

int gk_sdio_probe(void *priv_data)
{
    struct gk_sdio *sdio_drv;
    struct rt_mmcsd_host *host;
    struct gk_sdio_info *sdio_info = (struct gk_sdio_info *)priv_data;

    sdio_drv = (struct gk_sdio *)rt_malloc(sizeof(struct gk_sdio));

    if (!sdio_drv)
    {
        rt_kprintf("ERROR: %s,line:%d, failed to malloc host\n", __func__,__LINE__);
        return -RT_ENOMEM;
    }

    rt_memset(sdio_drv, 0, sizeof(struct gk_sdio));

    host = mmcsd_alloc_host();
    if (!host)
    {
        rt_kprintf("ERROR: %s,LINE:%d failed to malloc host\n", __func__,__LINE__);
        rt_free((void *)sdio_drv);
        return -RT_ENOMEM;
    }

    host->ops       = &gk_sdio_ops;
    host->freq_min  = 400*1000; ///FIXME:need check
    host->freq_max  = 50*1000000; ///FIXME:need check
    host->valid_ocr = VDD_32_33 | VDD_33_34 | VDD_165_195;

    host->flags = MMCSD_MUTBLKWRITE | MMCSD_SUP_HIGHSPEED | MMCSD_SUP_SDIO_IRQ | MMCSD_BUSWIDTH_4;
    host->max_seg_size  = SDIO_DEFAULT_BOUNDARY_SIZE;
    host->max_blk_size  = 1024;
    host->max_blk_count = 65535;
    host->private_data  = sdio_drv;

    sdio_drv->host = host;
    sdio_drv->priv = sdio_info;

    sdio_init(sdio_info->id);
    sdio_reset(sdio_info->id);

    sdioInstancePtr[sdio_info->id] = sdio_drv;

    mmcsd_change(host);

    return 0;
}

int gk_sdio_exit(void *priv_data)
{
    struct gk_sdio_info *sdio_info = (struct gk_sdio_info *)priv_data;
    rt_int8_t i;

    if(!sdio_info)
        return RT_EINVAL;

    if(!sdioInstancePtr[sdio_info->id])
        return RT_EINVAL;

    i = (sdio_info->id == 0)? 0:2;

    GD_INT_Close(&inthandleArray[i]);
    GD_INT_Close(&inthandleArray[i+1]);

    rt_completion_done(&(sdioInstancePtr[sdio_info->id]->completion));

    if(sdioInstancePtr[sdio_info->id]->host)
        mmcsd_free_host(sdioInstancePtr[sdio_info->id]->host);

    rt_free(sdioInstancePtr[sdio_info->id]);
    sdioInstancePtr[sdio_info->id] = RT_NULL;

    return 0;
}

struct gk_platform_driver sdio_driver_ops = {

    .name = "gk-sdio", .probe = gk_sdio_probe, .remove = gk_sdio_exit,

};

#if 0
#include "adi_types.h"
#include "adi_gpio.h"

static GADI_SYS_HandleT resetHandle = NULL;

void gk_sdio_wifi_reset_gpio_init(GADI_U8 num_gpio)
{
    rt_int32_t error;
    GADI_GPIO_OpenParam resetParam;

    if(num_gpio == 0)
    {
        resetHandle = NULL;
        return;
    }

    resetParam.active_low = 0;
    resetParam.direction = 1;
    resetParam.num_gpio = num_gpio;
    resetParam.value = 1;

    rt_kprintf("wifi reset num_gpio %d !\n", num_gpio);

    if(resetHandle == NULL)
    {
        resetHandle = gadi_gpio_open(&error, &resetParam);
        if(resetHandle == NULL)
        {
            rt_kprintf("open sensor reset GPIO failed %d !\n", error);
            return;
        }
    }
}

int gk_sdio_wifi_hw_reset(void)
{

    rt_int32_t error;

    if(resetHandle == NULL)
    {
        return 1;
    }

    error = gadi_gpio_clear(resetHandle);
    rt_thread_delay(20);
    error = gadi_gpio_set(resetHandle);
    rt_thread_delay(20);
    if(error != 0)
    {
        rt_kprintf("wifi reset failed %d !\n", error);
        return -1;
    }

    return 0;

}
#endif

void rt_hw_sdio_init(void)
{
    GH_SDIO_init();
    gk_platform_driver_init(&sdio_driver_ops);
}

