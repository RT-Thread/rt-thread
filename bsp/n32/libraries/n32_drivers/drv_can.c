/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file drv_can.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
 
#include <drv_can.h>
#include "board.h"

#ifdef RT_USING_CAN

#if defined(BSP_USING_CAN1) || defined(BSP_USING_CAN2)
    /* this driver can be disabled at menuconfig -> Hardware Drivers Config -> On-chip Peripheral Drivers -> Enable ADC */


CanRxMessage RxMessage;

#ifdef BSP_USING_CAN1
static struct n32_can drv_can1 =
{
    .name = "bxcan1",
    .CanHandle.Instance = CAN1,
};
#endif

#ifdef BSP_USING_CAN2
static struct n32_can drv_can2 =
{
    .name = "bxcan2",
    .CanHandle.Instance = CAN2,
};
#endif

static rt_err_t setfilter(struct n32_can *pbxcan, CAN_FilterInitType *pconfig)
{
    CAN_FilterInitType CAN_FilterInitStruct;
        
    CAN_Module* CANx;
    CANx = pbxcan->CanHandle.Instance;   
    
    CAN_FilterInitStruct.Filter_Num            = pconfig->Filter_Num;
    CAN_FilterInitStruct.Filter_Mode           = pconfig->Filter_Mode;
    CAN_FilterInitStruct.Filter_Scale          = pconfig->Filter_Scale;
    CAN_FilterInitStruct.Filter_HighId         = pconfig->Filter_HighId;
    CAN_FilterInitStruct.Filter_LowId          = pconfig->Filter_LowId;
    CAN_FilterInitStruct.FilterMask_HighId     = pconfig->FilterMask_HighId;;
    CAN_FilterInitStruct.FilterMask_LowId      = pconfig->FilterMask_LowId;;
    CAN_FilterInitStruct.Filter_FIFOAssignment = pconfig->Filter_FIFOAssignment;;
    CAN_FilterInitStruct.Filter_Act            = pconfig->Filter_Act;
    if(CANx == CAN1)
    {
        CAN1_InitFilter(&CAN_FilterInitStruct);
    }
    else
    {
        CAN2_InitFilter(&CAN_FilterInitStruct);
    }
    
    return RT_EOK;
}

static void bxcan_init(struct rt_can_device *can, struct can_configure *cfg)
{
    CAN_InitType       CAN_InitStructure;

    struct n32_can *drv_can;
    CAN_Module *pbxcan;

    drv_can = (struct n32_can *)can->parent.user_data;
    pbxcan  = drv_can->CanHandle.Instance;
    
    uint32_t bps ;
    
    /* CAN register init */
    CAN_DeInit(pbxcan);
    
    /* Struct init*/
    CAN_InitStruct(&CAN_InitStructure);
    switch(cfg->baud_rate)
    {
        case CAN1MBaud:
            bps = CAN_BAUDRATE_1M;
            break;
        case CAN500kBaud:
            bps = CAN_BAUDRATE_500K;
            break;
        case CAN250kBaud:
            bps = CAN_BAUDRATE_250K;
            break;
        case CAN125kBaud:
            bps = CAN_BAUDRATE_125K;
            break;
        case CAN100kBaud:
            bps = CAN_BAUDRATE_100K;
            break;
        case CAN50kBaud:
            bps = CAN_BAUDRATE_50K;
            break;
        case CAN20kBaud:
            bps = CAN_BAUDRATE_20K;
            break;
        case CAN10kBaud:
            bps = CAN_BAUDRATE_10K;
            break;
        
        default:
            bps = CAN_BAUDRATE_100K;
            break;
    }
    
    CAN_InitStructure.BaudRatePrescaler = (uint32_t)(CAN_BTR_CALCULATE / bps);
    
    switch (cfg->mode)
    {
        case RT_CAN_MODE_NORMAL:
            CAN_InitStructure.OperatingMode = CAN_Normal_Mode;
            break;
        case RT_CAN_MODE_LISEN:
            CAN_InitStructure.OperatingMode = CAN_Silent_Mode;
            break;
        case RT_CAN_MODE_LOOPBACK:
            CAN_InitStructure.OperatingMode = CAN_LoopBack_Mode;
            break;
        case RT_CAN_MODE_LOOPBACKANLISEN:
            CAN_InitStructure.OperatingMode = CAN_Silent_LoopBack_Mode;
            break;
        
        default:
            CAN_InitStructure.OperatingMode = CAN_Normal_Mode;
            break;
    }
    
    CAN_InitStructure.TTCM          = DISABLE;
    CAN_InitStructure.ABOM          = DISABLE;
    CAN_InitStructure.AWKUM         = DISABLE;
    CAN_InitStructure.NART          = DISABLE;
    CAN_InitStructure.RFLM          = DISABLE;
    CAN_InitStructure.TXFP          = ENABLE;

    CAN_InitStructure.RSJW          = CAN_RSJW_1tq;
    CAN_InitStructure.TBS1          = CAN_TBS1_3tq;
    CAN_InitStructure.TBS2          = CAN_TBS2_2tq;
    
    /*Initializes the CAN */
    CAN_Init(pbxcan, &CAN_InitStructure);
    
    /* CAN filter init */
    setfilter(drv_can, &drv_can->FilterConfig);

}

#ifdef BSP_USING_CAN1
static void bxcan1_hw_init(void)
{
    /* Enable CAN1 reset state */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_CAN1, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
    GPIOInit(GPIOD, GPIO_Mode_IPU, GPIO_Speed_50MHz, GPIO_PIN_8);
    GPIOInit(GPIOD, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, GPIO_PIN_9);
    /* Remap CAN1 GPIOs */
    GPIO_ConfigPinRemap(GPIO_RMP1_CAN1, ENABLE);
}
#endif

#ifdef BSP_USING_CAN2
static void bxcan2_hw_init(void)
{
    /* Enable CAN2 reset state */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_CAN2, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
    GPIOInit(GPIOB, GPIO_Mode_IPU, GPIO_Speed_50MHz, GPIO_PIN_12);
    GPIOInit(GPIOB, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, GPIO_PIN_13);
}
#endif

static rt_err_t configure(struct rt_can_device *can, struct can_configure *cfg)
{
    struct n32_can *drv_can;
    CAN_Module *pbxcan;

    drv_can = (struct n32_can *)can->parent.user_data;
    pbxcan  = drv_can->CanHandle.Instance;
    
    if (pbxcan == CAN1)
    {
#ifdef BSP_USING_CAN1
        bxcan1_hw_init();  
        bxcan_init(&drv_can->device, &drv_can->device.config);
#endif
    }
    else  if (pbxcan == CAN2)
    {
#ifdef BSP_USING_CAN2
        bxcan2_hw_init();  
        bxcan_init(&drv_can->device, &drv_can->device.config);
#endif
    }
    return RT_EOK;
}

/**
 * @brief  Configures the NVIC for CAN.
 */
void CAN_NVIC_Config(IRQn_Type IRQn, uint8_t PreemptionPriority, uint8_t SubPriority,FunctionalState cmd)
{
    NVIC_InitType NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    NVIC_InitStructure.NVIC_IRQChannel                   = IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = cmd;
    if(cmd)
    {
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority        = SubPriority;
    }
    NVIC_Init(&NVIC_InitStructure);
}

static rt_err_t control(struct rt_can_device *can, int cmd, void *arg)
{
    rt_uint32_t argval;
    struct n32_can *drv_can;
    struct rt_can_filter_config *filter_cfg;

    RT_ASSERT(can != RT_NULL);
    drv_can = (struct n32_can *)can->parent.user_data;
    RT_ASSERT(drv_can != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        argval = (rt_uint32_t) arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            if (CAN1 == drv_can->CanHandle.Instance)
            {
                CAN_NVIC_Config(USB_LP_CAN1_RX0_IRQn, 1, 0, ENABLE);
                CAN_NVIC_Config(CAN1_RX1_IRQn, 1, 0, ENABLE);
            }
#ifdef CAN2
            if (CAN2 == drv_can->CanHandle.Instance)
            {
                CAN_NVIC_Config(CAN2_RX0_IRQn, 0, 0, DISABLE);
                CAN_NVIC_Config(CAN2_RX1_IRQn, 0, 0, DISABLE);
            }
#endif
            CAN_INTConfig(drv_can->CanHandle.Instance, CAN_INT_FMP0, DISABLE);
            CAN_INTConfig(drv_can->CanHandle.Instance, CAN_INT_FF0, DISABLE);
            CAN_INTConfig(drv_can->CanHandle.Instance, CAN_INT_FOV0, DISABLE);
            CAN_INTConfig(drv_can->CanHandle.Instance, CAN_INT_FMP1, DISABLE);
            CAN_INTConfig(drv_can->CanHandle.Instance, CAN_INT_FF1, DISABLE);
            CAN_INTConfig(drv_can->CanHandle.Instance, CAN_INT_FOV1, DISABLE);
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            if (CAN1 == drv_can->CanHandle.Instance)
            {
                CAN_NVIC_Config(USB_HP_CAN1_TX_IRQn, 0, 0, DISABLE);
            }
#ifdef CAN2
            if (CAN2 == drv_can->CanHandle.Instance)
            {
                CAN_NVIC_Config(CAN2_TX_IRQn, 0, 0, DISABLE);
            }
#endif
            CAN_INTConfig(drv_can->CanHandle.Instance, CAN_INT_TME, DISABLE);
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            if (CAN1 == drv_can->CanHandle.Instance)
            {
                CAN_NVIC_Config(CAN1_SCE_IRQn, 0, 0, DISABLE);
                
            }
#ifdef CAN2
            if (CAN2 == drv_can->CanHandle.Instance)
            {
                CAN_NVIC_Config(CAN2_SCE_IRQn, 0, 0, DISABLE);
            }
#endif
            CAN_ClearFlag(drv_can->CanHandle.Instance, CAN_FLAG_EWGFL);
            CAN_ClearFlag(drv_can->CanHandle.Instance, CAN_FLAG_EPVFL);
            CAN_ClearFlag(drv_can->CanHandle.Instance, CAN_FLAG_BOFFL);
            CAN_ClearFlag(drv_can->CanHandle.Instance, CAN_FLAG_LEC);
            CAN_ClearINTPendingBit(drv_can->CanHandle.Instance, CAN_INT_ERR);
        }
        break;
    case RT_DEVICE_CTRL_SET_INT:
        argval = (rt_uint32_t) arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            CAN_INTConfig(drv_can->CanHandle.Instance, CAN_INT_FMP0, ENABLE);
            CAN_INTConfig(drv_can->CanHandle.Instance, CAN_INT_FF0, ENABLE);
            CAN_INTConfig(drv_can->CanHandle.Instance, CAN_INT_FOV0, ENABLE);
            CAN_INTConfig(drv_can->CanHandle.Instance, CAN_INT_FMP1, ENABLE);
            CAN_INTConfig(drv_can->CanHandle.Instance, CAN_INT_FF1, ENABLE);
            CAN_INTConfig(drv_can->CanHandle.Instance, CAN_INT_FOV1, ENABLE);

            if (CAN1 == drv_can->CanHandle.Instance)
            {
                CAN_NVIC_Config(USB_LP_CAN1_RX0_IRQn, 1, 0, ENABLE);
                CAN_NVIC_Config(CAN1_RX1_IRQn, 1, 0, ENABLE);
            }
#ifdef CAN2
            if (CAN2 == drv_can->CanHandle.Instance)
            {
                CAN_NVIC_Config(CAN2_RX0_IRQn, 1, 0, ENABLE);
                CAN_NVIC_Config(CAN2_RX1_IRQn, 1, 0, ENABLE);
            }
#endif
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            CAN_INTConfig(drv_can->CanHandle.Instance, CAN_INT_TME, ENABLE);

            if (CAN1 == drv_can->CanHandle.Instance)
            {
                CAN_NVIC_Config(USB_HP_CAN1_TX_IRQn, 1, 0, ENABLE);
            }
#ifdef CAN2
            if (CAN2 == drv_can->CanHandle.Instance)
            {
                CAN_NVIC_Config(CAN2_TX_IRQn, 1, 0, ENABLE);
            }
#endif
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            CAN_INTConfig(drv_can->CanHandle.Instance, CAN_INT_EWG, ENABLE);
            CAN_INTConfig(drv_can->CanHandle.Instance, CAN_INT_EPV, ENABLE);
            CAN_INTConfig(drv_can->CanHandle.Instance, CAN_INT_BOF, ENABLE);
            CAN_INTConfig(drv_can->CanHandle.Instance, CAN_INT_LEC, ENABLE);
            CAN_INTConfig(drv_can->CanHandle.Instance, CAN_INT_ERR, ENABLE);

            if (CAN1 == drv_can->CanHandle.Instance)
            {
                CAN_NVIC_Config(CAN1_SCE_IRQn, 1, 0, ENABLE);
            }
#ifdef CAN2
            if (CAN2 == drv_can->CanHandle.Instance)
            {
                CAN_NVIC_Config(CAN2_SCE_IRQn, 1, 0, ENABLE);
            }
#endif
        }
        break;
    case RT_CAN_CMD_SET_FILTER:
        if (RT_NULL == arg)
        {
            /* default filter config */
            setfilter(drv_can, &drv_can->FilterConfig);
        }
        else
        {
            filter_cfg = (struct rt_can_filter_config *)arg;
            /* get default filter */
            for (int i = 0; i < filter_cfg->count; i++)
            {
                drv_can->FilterConfig.Filter_Num = filter_cfg->items[i].hdr;
                drv_can->FilterConfig.Filter_HighId = (filter_cfg->items[i].id >> 13) & 0xFFFF;
                drv_can->FilterConfig.Filter_LowId = ((filter_cfg->items[i].id << 3) | 
                                                    (filter_cfg->items[i].ide << 2) | 
                                                    (filter_cfg->items[i].rtr << 1)) & 0xFFFF;
                drv_can->FilterConfig.FilterMask_HighId = (filter_cfg->items[i].mask >> 16) & 0xFFFF;
                drv_can->FilterConfig.FilterMask_LowId = filter_cfg->items[i].mask & 0xFFFF;
                drv_can->FilterConfig.Filter_Mode = filter_cfg->items[i].mode;
                /* Filter conf */
                setfilter(drv_can, &drv_can->FilterConfig);
            }
        }
        break;
    case RT_CAN_CMD_SET_MODE:
        argval = (rt_uint32_t) arg;
        if (argval != RT_CAN_MODE_NORMAL &&
                argval != RT_CAN_MODE_LISEN &&
                argval != RT_CAN_MODE_LOOPBACK &&
                argval != RT_CAN_MODE_LOOPBACKANLISEN)
        {
            return -RT_ERROR;
        }
        if (argval != drv_can->device.config.mode)
        {
            drv_can->device.config.mode = argval;
            return configure(&drv_can->device, &drv_can->device.config);
        }
        break;
    case RT_CAN_CMD_SET_BAUD:
        argval = (rt_uint32_t) arg;
        if (argval != CAN1MBaud &&
                argval != CAN500kBaud &&
                argval != CAN250kBaud &&
                argval != CAN125kBaud &&
                argval != CAN100kBaud &&
                argval != CAN50kBaud  &&
                argval != CAN20kBaud  &&
                argval != CAN10kBaud)
        {
            return -RT_ERROR;
        }
        if (argval != drv_can->device.config.baud_rate)
        {
            drv_can->device.config.baud_rate = argval;
            return configure(&drv_can->device, &drv_can->device.config);
        }
        break;
    case RT_CAN_CMD_SET_PRIV:
        argval = (rt_uint32_t) arg;
        if (argval != RT_CAN_MODE_PRIV &&
                argval != RT_CAN_MODE_NOPRIV)
        {
            return -RT_ERROR;
        }
        if (argval != drv_can->device.config.privmode)
        {
            drv_can->device.config.privmode = argval;
            return configure(&drv_can->device, &drv_can->device.config);
        }
        break;
    case RT_CAN_CMD_GET_STATUS:
    {
        rt_uint32_t errtype;
        errtype = drv_can->CanHandle.Instance->ESTS;
        drv_can->device.status.rcverrcnt = errtype >> 24;
        drv_can->device.status.snderrcnt = (errtype >> 16 & 0xFF);
        drv_can->device.status.lasterrtype = errtype & 0x70;
        drv_can->device.status.errcode = errtype & 0x07;

        rt_memcpy(arg, &drv_can->device.status, sizeof(drv_can->device.status));
    }
    break;
    }

    return RT_EOK;
}

static int sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t boxno)
{
    CAN_Module *pbxcan;
    CanTxMessage TxMessage;
    struct rt_can_msg *pmsg = (struct rt_can_msg *) buf;
    int i;

    pbxcan = ((struct n32_can *) can->parent.user_data)->CanHandle.Instance;

    if(pmsg->ide)
    {
        TxMessage.ExtId = pmsg->id;
        TxMessage.StdId = 0;
    }
    else
    {
        TxMessage.StdId = pmsg->id;
        TxMessage.ExtId = 0;
    }
    
    TxMessage.RTR = pmsg->rtr;
    TxMessage.IDE = pmsg->ide;
    TxMessage.DLC = pmsg->len;
    for( i=0; i<TxMessage.DLC ;i++)
    {
      TxMessage.Data[i] = pmsg->data[i];
    }
    CAN_TransmitMessage(pbxcan, &TxMessage); 

    return RT_EOK;
}

static int recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t boxno)
{    
    struct rt_can_msg *pmsg = (struct rt_can_msg *) buf;
    int i;

    pmsg->ide = (rt_uint32_t) RxMessage.IDE; 
    if(RxMessage.IDE == 1)
        pmsg->id = RxMessage.ExtId;
    else
        pmsg->id = RxMessage.StdId;
    pmsg->len = RxMessage.DLC;
    pmsg->rtr = RxMessage.RTR;
    pmsg->hdr = 0;
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

#ifdef BSP_USING_CAN1

struct rt_can_device bxcan1;

void n32_can1_irqhandler(void *param)  
{    
    CAN_Module* CANx;

    CANx =  CAN1;
   
    /* receive data interrupt */
    if (CAN_GetIntStatus(CANx, CAN_INT_FMP0)) 
    {
        CAN_ReceiveMessage(CANx, CAN_FIFO0, &RxMessage);
        rt_hw_can_isr(&drv_can1.device, RT_CAN_EVENT_RX_IND);
        CAN_ClearINTPendingBit(CANx, CAN_INT_FMP0);
        rt_kprintf("\r\nCan1 int RX happened!\r\n");
    }
    /* send data interrupt */
    else if (CAN_GetFlagSTS(CANx, CAN_FLAG_RQCPM0)) 
    {
       rt_hw_can_isr(&drv_can1.device, RT_CAN_EVENT_TX_DONE | 0 << 8);
       CAN_ClearFlag(CANx, CAN_FLAG_RQCPM0);
    }
    /* data overflow interrupt */
    else if (CAN_GetIntStatus(CANx, CAN_INT_FOV0)) 
    {
       rt_hw_can_isr(&drv_can1.device, RT_CAN_EVENT_RXOF_IND);
       rt_kprintf("\r\nCan1 int RX OF happened!\r\n");
    }
}

void USB_HP_CAN1_TX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    n32_can1_irqhandler(&drv_can1.device);
    
    /* leave interrupt */
    rt_interrupt_leave();
}

void USB_LP_CAN1_RX0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    n32_can1_irqhandler(&drv_can1.device);
    
    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /*BSP_USING_CAN1*/

#ifdef BSP_USING_CAN2
struct rt_can_device bxcan2;
void n32_can2_irqhandler(void *param)  
{  
    CAN_Module* CANx;

    CANx =  CAN2;
   
    /* receive data interrupt */
    if (CAN_GetIntStatus(CANx, CAN_INT_FMP0)) 
    {
        CAN_ReceiveMessage(CANx, CAN_FIFO0, &RxMessage);
        rt_hw_can_isr(&drv_can2.device, RT_CAN_EVENT_RX_IND);
        CAN_ClearINTPendingBit(CANx, CAN_INT_FMP0);
        rt_kprintf("\r\nCan2 int RX happened!\r\n");
    }
    /* send data interrupt */
    else if (CAN_GetFlagSTS(CANx, CAN_FLAG_RQCPM0)) 
    {
       rt_hw_can_isr(&drv_can2.device, RT_CAN_EVENT_TX_DONE | 0 << 8);
       CAN_ClearFlag(CANx, CAN_FLAG_RQCPM0);
    }
    /* data overflow interrupt */
    else if (CAN_GetIntStatus(CANx, CAN_INT_FOV0)) 
    {
       rt_hw_can_isr(&drv_can2.device, RT_CAN_EVENT_RXOF_IND);
       rt_kprintf("\r\nCan2 int RX OF happened!\r\n");
    }
}  

void CAN2_TX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    n32_can2_irqhandler(&drv_can2.device);
    
    /* leave interrupt */
    rt_interrupt_leave();
}

void CAN2_RX0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    n32_can2_irqhandler(&drv_can2.device);
    
    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /*BSP_USING_CAN2*/

#define CANCONFIG \
{\
        CAN500kBaud,\
        RT_CANMSG_BOX_SZ,\
        RT_CANSND_BOX_NUM,\
        RT_CAN_MODE_LOOPBACK,\
};

int rt_hw_can_init(void)
{
    struct can_configure config = CANCONFIG;
    config.privmode = RT_CAN_MODE_NOPRIV;
    config.ticks = 50;
#ifdef RT_CAN_USING_HDR
    config.maxhdr = 14;
#ifdef CAN2
    config.maxhdr = 28;
#endif
#endif
    /* config default filter */
    CAN_FilterInitType filterConf = {0};
    filterConf.Filter_HighId = 0x0000;
    filterConf.Filter_LowId = 0x0000;
    filterConf.FilterMask_HighId = 0x0000;
    filterConf.FilterMask_LowId = 0x0000;
    filterConf.Filter_FIFOAssignment = CAN_FIFO0;
    filterConf.Filter_Num = CAN_FILTERNUM0;
    filterConf.Filter_Mode = CAN_Filter_IdMaskMode;
    filterConf.Filter_Scale = CAN_Filter_32bitScale;
    filterConf.Filter_Act = ENABLE;
        
#ifdef BSP_USING_CAN1
    filterConf.Filter_Num = 0;

    drv_can1.FilterConfig = filterConf;
    drv_can1.device.config = config;
    /* register CAN1 device */
    rt_hw_can_register(&drv_can1.device,
                       drv_can1.name,
                       &canops,
                       &drv_can1);
#endif /* BSP_USING_CAN1 */

#ifdef BSP_USING_CAN2
    filterConf.Filter_Num = 0;

    drv_can2.FilterConfig = filterConf;
    drv_can2.device.config = config;
    /* register CAN2 device */
    rt_hw_can_register(&drv_can2.device,
                       drv_can2.name,
                       &canops,
                       &drv_can2);
#endif /* BSP_USING_CAN2 */

    return 0;
}

INIT_BOARD_EXPORT(rt_hw_can_init);

#endif /* defined(BSP_USING_CAN1) || defined(BSP_USING_CAN2) */
#endif /*RT_USING_CAN*/
