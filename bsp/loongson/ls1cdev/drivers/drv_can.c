/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2018-01-06     sundm75       first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <rthw.h>

#include <drv_can.h>

#include "ls1c.h"
#include "../libraries/ls1c_public.h"
#include "../libraries/ls1c_regs.h"
#include "../libraries/ls1c_clock.h"
#include "../libraries/ls1c_can.h"
#include "../libraries/ls1c_pin.h"


#ifdef RT_USING_CAN

CanRxMsg RxMessage;

struct ls1c_bxcan
{
    CAN_TypeDef *reg;
    void * irq;
};

static rt_err_t bxmodifyfilter(struct ls1c_bxcan *pbxcan, struct rt_can_filter_item *pitem, rt_uint32_t actived)
{
    rt_int32_t fcase;
    rt_err_t res;
    rt_int32_t hdr, fbase, foff;
    CAN_TypeDef* CANx;
    CANx = pbxcan->reg;

    /*pitem->mode     1-掩码模式; 0- 滤波器模式 SJA1000中使用以下方式*/
    /*SJA1000中AFM    1-单滤波器模式; 0- 双滤波器模式 */

    fcase = pitem->mode;/*1-单滤波器模式; 0- 双滤波器模式*/
    {
        if (!actived)
        {
            return RT_EOK;
        }
        else if (pitem->hdr_bank == -1)
        {
            res = -1;
            if (res != RT_EOK)
            {
                return res;
            }
        }
        else if (pitem->hdr_bank >= 0)
        {
            rt_enter_critical();
            res = RT_EOK;
            if (res != RT_EOK)
            {
                return res;
            }
            hdr = pitem->hdr_bank;
            rt_exit_critical();
        }
    }

    CAN_FilterInitTypeDef   CAN_FilterInitStruct;
    unsigned char ide, rtr, id , idmask, mode;
    ide =  (unsigned char) pitem->ide;
    rtr = (unsigned char)  pitem->rtr;
    id = pitem->id;
    idmask = pitem->mask;
    mode = (unsigned char) pitem->mode;
    CAN_FilterInitStruct.IDE = ide;
    CAN_FilterInitStruct.RTR = rtr;
    CAN_FilterInitStruct.ID = id;
    CAN_FilterInitStruct.IDMASK = idmask;
    CAN_FilterInitStruct.MODE = mode;
    CAN_FilterInit(CANx, &CAN_FilterInitStruct);

    return RT_EOK;
}

static rt_err_t setfilter(struct ls1c_bxcan *pbxcan, struct rt_can_filter_config *pconfig)
{
    struct rt_can_filter_item *pitem = pconfig->items;
    rt_uint32_t count = pconfig->count;
    rt_err_t res;
    while (count)
    {
        res = bxmodifyfilter(pbxcan, pitem, pconfig->actived);
        if (res != RT_EOK)
        {
            return res;
        }
        pitem++;
        count--;
    }
    return RT_EOK;
}

static void bxcan0_filter_init(struct rt_can_device *can)
{
        struct ls1c_bxcan *pbxcan;
        pbxcan = (struct ls1c_bxcan *) can->parent.user_data;

}

static void bxcan1_filter_init(struct rt_can_device *can)
{
        struct ls1c_bxcan *pbxcan;
        pbxcan = (struct ls1c_bxcan *) can->parent.user_data;

}

static void bxcan_init(CAN_TypeDef *pcan, rt_uint32_t baud, rt_uint32_t mode)
{
    CAN_InitTypeDef        CAN_InitStructure;

    Ls1c_CanBPS_t bps ;

         switch(baud)
            {
                case CAN1MBaud:
                    bps = LS1C_CAN1MBaud;
          break;
                case CAN800kBaud:
                    bps = LS1C_CAN800kBaud;
          break;
                case CAN500kBaud:
                    bps = LS1C_CAN500kBaud;
          break;
                case CAN250kBaud:
                    bps = LS1C_CAN250kBaud;
          break;
                case CAN125kBaud:
                    bps = LS1C_CAN125kBaud;
          break;
                case CAN50kBaud:
                    bps = LS1C_CAN40kBaud;
          break;
                default:
                    bps = LS1C_CAN250kBaud;
          break;
            }

    switch (mode)
    {
    case RT_CAN_MODE_NORMAL:
        CAN_InitStructure.CAN_Mode = 0x00;
        break;
    case RT_CAN_MODE_LISTEN:
        CAN_InitStructure.CAN_Mode = CAN_Mode_LOM;
        break;
    case RT_CAN_MODE_LOOPBACK:
        CAN_InitStructure.CAN_Mode = CAN_Mode_STM;

        break;
    case RT_CAN_MODE_LOOPBACKANLISTEN:
        CAN_InitStructure.CAN_Mode = CAN_Mode_STM|CAN_Mode_LOM;
        break;
    }
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;

    switch (bps)
    {
        case LS1C_CAN1MBaud:
            CAN_InitStructure.CAN_Prescaler = 9;
            CAN_InitStructure.CAN_BS1 = CAN_BS1_4tq;
            CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;
        break;
        case LS1C_CAN800kBaud:
            CAN_InitStructure.CAN_Prescaler = 8;
            CAN_InitStructure.CAN_BS1 = CAN_BS1_7tq;
            CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;
        break;
        case LS1C_CAN500kBaud:
            CAN_InitStructure.CAN_Prescaler = 9;
            CAN_InitStructure.CAN_BS1 = CAN_BS1_11tq;
            CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;
        break;
        case LS1C_CAN250kBaud:
            CAN_InitStructure.CAN_Prescaler = 36;
            CAN_InitStructure.CAN_BS1 = CAN_BS1_4tq;
            CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;
        break;
        case LS1C_CAN125kBaud:
            CAN_InitStructure.CAN_Prescaler = 36;
            CAN_InitStructure.CAN_BS1 = CAN_BS1_11tq;
            CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;
        break;
        case LS1C_CAN100kBaud:
            CAN_InitStructure.CAN_Prescaler = 63;
            CAN_InitStructure.CAN_BS1 = CAN_BS1_7tq;
            CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;
        break;
        case LS1C_CAN50kBaud:
            CAN_InitStructure.CAN_Prescaler = 63;
            CAN_InitStructure.CAN_BS1 = CAN_BS1_16tq;
            CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;
        break;
        default: //250K
            CAN_InitStructure.CAN_Prescaler = 36;
            CAN_InitStructure.CAN_BS1 = CAN_BS1_4tq;
            CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;
        break;
    }

    CAN_Init(pcan, &CAN_InitStructure);
}

#ifdef USING_BXCAN0
static void bxcan0_hw_init(void)
{
    pin_set_purpose(54, PIN_PURPOSE_OTHER);
    pin_set_purpose(55, PIN_PURPOSE_OTHER);
    pin_set_remap(54, PIN_REMAP_THIRD);
    pin_set_remap(55, PIN_REMAP_THIRD);
}
#endif

#ifdef USING_BXCAN1
static void bxcan1_hw_init(void)
{
    pin_set_purpose(56, PIN_PURPOSE_OTHER);
    pin_set_purpose(57, PIN_PURPOSE_OTHER);
    pin_set_remap(56, PIN_REMAP_THIRD);
    pin_set_remap(57, PIN_REMAP_THIRD);
}
#endif

static rt_err_t configure(struct rt_can_device *can, struct can_configure *cfg)
{
    CAN_TypeDef *pbxcan;

    pbxcan = ((struct ls1c_bxcan *) can->parent.user_data)->reg;
    if (pbxcan == CAN0)
    {
#ifdef USING_BXCAN0
        bxcan0_hw_init();
        bxcan_init(pbxcan, cfg->baud_rate, cfg->mode);
#endif
    }
    else  if (pbxcan == CAN1)
    {
#ifdef USING_BXCAN1
        bxcan1_hw_init();
        bxcan_init(pbxcan, cfg->baud_rate, cfg->mode);
#endif
    }
    return RT_EOK;
}

static rt_err_t control(struct rt_can_device *can, int cmd, void *arg)
{
    struct ls1c_bxcan *pbxcan;
    rt_uint32_t argval;

    pbxcan = (struct ls1c_bxcan *) can->parent.user_data;
    switch (cmd)
    {
    case RT_CAN_CMD_SET_FILTER:
          return setfilter(pbxcan, (struct rt_can_filter_config *) arg);
        break;
    case RT_CAN_CMD_SET_MODE:
        argval = (rt_uint32_t) arg;
        if (argval != RT_CAN_MODE_NORMAL ||
                argval != RT_CAN_MODE_LISTEN ||
                argval != RT_CAN_MODE_LOOPBACK ||
                argval != RT_CAN_MODE_LOOPBACKANLISTEN)
        {
            return -RT_ERROR;
        }
        if (argval != can->config.mode)
        {
            can->config.mode = argval;
            return CAN_SetMode(pbxcan->reg, argval);
        }
        break;
    case RT_CAN_CMD_SET_BAUD:
        argval = (rt_uint32_t) arg;
        if (argval != CAN1MBaud &&
                argval != CAN800kBaud &&
                argval != CAN500kBaud &&
                argval != CAN250kBaud &&
                argval != CAN125kBaud &&
                argval != CAN100kBaud &&
                argval != CAN50kBaud  )
        {
            return -RT_ERROR;
        }
        if (argval != can->config.baud_rate)
        {
            can->config.baud_rate = argval;
         Ls1c_CanBPS_t bps;
         switch(argval)
            {
                case CAN1MBaud:
                    bps = LS1C_CAN1MBaud;
          break;
                case CAN800kBaud:
                    bps = LS1C_CAN800kBaud;
          break;
                case CAN500kBaud:
                    bps = LS1C_CAN500kBaud;
          break;
                case CAN250kBaud:
                    bps = LS1C_CAN250kBaud;
          break;
                case CAN125kBaud:
                    bps = LS1C_CAN125kBaud;
          break;
                case CAN50kBaud:
                    bps = LS1C_CAN40kBaud;
          break;
                default:
                    bps = LS1C_CAN250kBaud;
          break;
            }
            return CAN_SetBps( pbxcan->reg,  bps);
        }
        break;
    case RT_CAN_CMD_GET_STATUS:
    {
        rt_uint32_t errtype;

        errtype = pbxcan->reg->RXERR;
        can->status.rcverrcnt = errtype ;
        errtype = pbxcan->reg->TXERR;
        can->status.snderrcnt = errtype ;
        errtype = pbxcan->reg->ECC;
        can->status.errcode = errtype ;
        if (arg != &can->status)
        {
            rt_memcpy(arg, &can->status, sizeof(can->status));
        }
    }
    break;
    }

    return RT_EOK;
}

static int sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t boxno)
{
    CAN_TypeDef *pbxcan;
    CanTxMsg TxMessage;
    struct rt_can_msg *pmsg = (struct rt_can_msg *) buf;
    int i;

    pbxcan = ((struct ls1c_bxcan *) can->parent.user_data)->reg;

    TxMessage.StdId = pmsg->id;
    TxMessage.ExtId = pmsg->id;
    TxMessage.RTR = pmsg->rtr;
    TxMessage.IDE = pmsg->ide;
    TxMessage.DLC = pmsg->len;
    for( i=0; i<TxMessage.DLC ;i++)
    {
      TxMessage.Data[i] = pmsg->data[i];
    }
    CAN_Transmit(pbxcan, &TxMessage);

    return RT_EOK;
}

static int recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t boxno)
{
    CAN_TypeDef *pbxcan;

   struct rt_can_msg *pmsg = (struct rt_can_msg *) buf;
   int i;

    pbxcan = ((struct ls1c_bxcan *) can->parent.user_data)->reg;

    pmsg->ide = (rt_uint32_t) RxMessage.IDE;
    if(RxMessage.IDE == 1)
        pmsg->id = RxMessage.ExtId;
    else
        pmsg->id = RxMessage.StdId;
    pmsg->len = RxMessage.DLC;
    pmsg->rtr = RxMessage.RTR;
    pmsg->hdr_index = 0;
    for(i= 0;i< RxMessage.DLC; i++)
    {
      pmsg->data[i] = RxMessage.Data[i];
    }
     return RT_EOK;
}

static const struct rt_can_ops canops =
{
    configure,
    control,
    sendmsg,
    recvmsg,
};

#ifdef USING_BXCAN0
struct rt_can_device bxcan0;
void ls1c_can0_irqhandler(int irq, void *param)
{
    CAN_TypeDef* CANx;
    unsigned char status;
    CANx =  CAN0;
    /*读寄存器清除中断*/
   status = CANx->IR;

    /*接收中断*/
    if (( status & CAN_IR_RI) == CAN_IR_RI)
    {
        /*清除RI 中断*/
       CAN_Receive(CANx, &RxMessage);
       CANx->CMR |= CAN_CMR_RRB;
       CANx->CMR |= CAN_CMR_CDO;
       rt_hw_can_isr(&bxcan0, RT_CAN_EVENT_RX_IND);
       rt_kprintf("\r\nCan0 int RX happened!\r\n");
    }
    /*发送中断*/
    else if (( status  & CAN_IR_TI) == CAN_IR_TI)
    {
       rt_hw_can_isr(&bxcan0, RT_CAN_EVENT_TX_DONE | 0 << 8);
       rt_kprintf("\r\nCan0 int TX happened!\r\n");
    }
    /*数据溢出中断*/
    else if (( status  & CAN_IR_DOI) == CAN_IR_DOI)
    {
       rt_hw_can_isr(&bxcan0, RT_CAN_EVENT_RXOF_IND);
       rt_kprintf("\r\nCan0 int RX OF happened!\r\n");
    }
}
static struct ls1c_bxcan bxcan0data =
{
    .reg = CAN0,
    .irq = ls1c_can0_irqhandler,
};
#endif /*USING_BXCAN0*/

#ifdef USING_BXCAN1
struct rt_can_device bxcan1;
void ls1c_can1_irqhandler(int irq, void *param)
{
    CAN_TypeDef* CANx;
    unsigned char status;
    CANx =  CAN1;
    /*读寄存器清除中断*/
   status = CANx->IR;

    /*接收中断*/
    if (( status & CAN_IR_RI) == CAN_IR_RI)
    {
        /*清除RI 中断*/
       CAN_Receive(CANx, &RxMessage);
       CANx->CMR |= CAN_CMR_RRB;
       CANx->CMR |= CAN_CMR_CDO;
       rt_hw_can_isr(&bxcan1, RT_CAN_EVENT_RX_IND);
       rt_kprintf("\r\nCan1 int RX happened!\r\n");
    }
    /*发送中断*/
    else if (( status  & CAN_IR_TI) == CAN_IR_TI)
    {
       rt_hw_can_isr(&bxcan1, RT_CAN_EVENT_TX_DONE | 0 << 8);
       rt_kprintf("\r\nCan1 int TX happened!\r\n");
    }
    /*数据溢出中断*/
    else if (( status  & CAN_IR_DOI) == CAN_IR_DOI)
    {
       rt_hw_can_isr(&bxcan1, RT_CAN_EVENT_RXOF_IND);
       rt_kprintf("\r\nCan1 int RX OF happened!\r\n");
    }
}
static struct ls1c_bxcan bxcan1data =
{
    .reg = CAN1,
    .irq = ls1c_can1_irqhandler,
};

#endif /*USING_BXCAN1*/

int ls1c_bxcan_init(void)
{

#ifdef USING_BXCAN0
    bxcan0.config.baud_rate = CAN250kBaud;
    bxcan0.config.msgboxsz = 1;
    bxcan0.config.sndboxnumber = 1;
    bxcan0.config.mode = RT_CAN_MODE_NORMAL;
    bxcan0.config.privmode = 0;
    bxcan0.config.ticks = 50;
#ifdef RT_CAN_USING_HDR
    bxcan0.config.maxhdr = 2;
#endif
    rt_hw_can_register(&bxcan0, "bxcan0", &canops, &bxcan0data);
    rt_kprintf("\r\ncan0 register! \r\n");

    rt_hw_interrupt_install(LS1C_CAN0_IRQ,( rt_isr_handler_t)bxcan0data.irq , RT_NULL, "can0");
    rt_hw_interrupt_umask(LS1C_CAN0_IRQ);
#endif
#ifdef USING_BXCAN1
    bxcan1.config.baud_rate = CAN250kBaud;
    bxcan1.config.msgboxsz = 1;
    bxcan1.config.sndboxnumber = 1;
    bxcan1.config.mode = RT_CAN_MODE_NORMAL;
    bxcan1.config.privmode = 0;
    bxcan1.config.ticks = 50;
#ifdef RT_CAN_USING_HDR
    bxcan1.config.maxhdr = 2;
#endif
    rt_hw_can_register(&bxcan1, "bxcan1", &canops, &bxcan1data);
    rt_kprintf("\r\ncan1 register! \r\n");

    rt_hw_interrupt_install(LS1C_CAN1_IRQ,( rt_isr_handler_t)bxcan1data.irq , RT_NULL, "can1");
    rt_hw_interrupt_umask(LS1C_CAN1_IRQ);
#endif
    return RT_EOK;
}

INIT_BOARD_EXPORT(ls1c_bxcan_init);

#endif /*RT_USING_CAN*/
