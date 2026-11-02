/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-21     chenbin      the first version
 */
#include <stdint.h>
#include <board.h>
#include <rtdevice.h>
#include "drv_can.h"
#ifdef BSP_USING_CAN

#define DBG_TAG "drv_can"
#define DBG_LVL DBG_INFO
#define DBG_ENABLE
#include <rtdbg.h>

//兼容老版的can宏定义
#ifndef RT_CAN_MODE_LISTEN
#define RT_CAN_MODE_LISTEN    RT_CAN_MODE_LISEN
#endif
#ifndef RT_CAN_MODE_LOOPBACKANLISTEN
#define RT_CAN_MODE_LOOPBACKANLISTEN    RT_CAN_MODE_LOOPBACKANLISEN
#endif

struct ch32v307x_can_baud_info
{
    rt_uint32_t baud_rate;
    rt_uint16_t prescaler;
    rt_uint8_t  tsjw;        //CAN synchronisation jump width.
    rt_uint8_t  tbs1;       //CAN time quantum in bit segment 1.
    rt_uint8_t  tbs2;       //CAN time quantum in bit segment 2.
    rt_uint8_t  notused;
};

#define CH32V307X_CAN_BAUD_DEF(xrate, xsjw, xbs1, xbs2, xprescale) \
    {                                                      \
        .baud_rate = xrate,                                 \
        .tsjw = xsjw,                                      \
        .tbs1 = xbs1,                                      \
        .tbs2 = xbs2,                                      \
        .prescaler = xprescale                               \
    }

/* CH32V307X can device object */
struct ch32v307x_can_obj
{
    char                   * name;
    CAN_TypeDef            * can_base;
    CAN_InitTypeDef          can_init;
    CAN_FilterInitTypeDef    can_filter_init;
    struct rt_can_device     device; /* inherit from can device */
};

/*
* CH32V307x CAN1 CAN2 used APB1 (PCLK1 72MHz)
*
* baud calculation example:
* baud =  PCLK1 / ((sjw + tbs1 + tbs2) * brp)
* 1MHz = 72MHz / ((1 + 15 + 2) * 4)
*
* sample calculation example:
* sample = ( sjw + tbs1) / (sjw + tbs1 + tbs2)
* sample = 87.5%  at baud <= 500K
* sample = 80%    at baud > 500K
* sample = 75%    at baud > 800K
*/
#if defined(CH32V30x_D8C) /* APB1 (PCLK1 72MHz) */
static const struct ch32v307x_can_baud_info  can_baud_rate_tab[] =
{
    CH32V307X_CAN_BAUD_DEF(  CAN1MBaud, CAN_SJW_1tq, CAN_BS1_15tq, CAN_BS2_2tq, 4),
    CH32V307X_CAN_BAUD_DEF(CAN800kBaud, CAN_SJW_1tq, CAN_BS1_12tq, CAN_BS2_2tq, 6),
    CH32V307X_CAN_BAUD_DEF(CAN500kBaud, CAN_SJW_1tq, CAN_BS1_15tq, CAN_BS2_2tq, 8),
    CH32V307X_CAN_BAUD_DEF(CAN250kBaud, CAN_SJW_1tq, CAN_BS1_15tq, CAN_BS2_2tq, 16),
    CH32V307X_CAN_BAUD_DEF(CAN125kBaud, CAN_SJW_1tq, CAN_BS1_15tq, CAN_BS2_2tq, 32),
    CH32V307X_CAN_BAUD_DEF(CAN100kBaud, CAN_SJW_1tq, CAN_BS1_15tq, CAN_BS2_2tq, 40),
    CH32V307X_CAN_BAUD_DEF( CAN50kBaud, CAN_SJW_1tq, CAN_BS1_15tq, CAN_BS2_2tq, 80),
    CH32V307X_CAN_BAUD_DEF( CAN20kBaud, CAN_SJW_1tq, CAN_BS1_15tq, CAN_BS2_2tq, 200),
    CH32V307X_CAN_BAUD_DEF( CAN10kBaud, CAN_SJW_1tq, CAN_BS1_15tq, CAN_BS2_2tq, 400),
};
#endif

#ifdef BSP_USING_CAN1
static struct ch32v307x_can_obj  drv_can1 =
{
    .name = "can1",
    .can_base = CAN1,
};
#endif

#ifdef BSP_USING_CAN2
static struct ch32v307x_can_obj  drv_can2 =
{
    .name = "can2",
    .can_base = CAN2,
};
#endif

#ifdef BSP_USING_CAN
rt_weak void ch32v307x_can_gpio_init(CAN_TypeDef *can_base)
{
    GPIO_InitTypeDef GPIO_InitSturcture={0};
#ifdef BSP_USING_CAN1
    if (CAN1 == can_base)
    {
        RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE );
        RCC_APB1PeriphClockCmd( RCC_APB1Periph_CAN1, ENABLE );
        GPIO_PinRemapConfig( GPIO_Remap1_CAN1, ENABLE);
        // CAN1 TXD --> PB9         CAN1 RXD --> PB8
        GPIO_InitSturcture.GPIO_Pin = GPIO_Pin_9;
        GPIO_InitSturcture.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitSturcture.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init( GPIOB, &GPIO_InitSturcture);
        GPIO_InitSturcture.GPIO_Pin = GPIO_Pin_8;
        GPIO_InitSturcture.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_Init( GPIOB, &GPIO_InitSturcture);
        /*
        RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE );
        RCC_APB1PeriphClockCmd( RCC_APB1Periph_CAN1, ENABLE );
        // CAN1 TXD --> PA12    CAN1 RXD --> PA11
        GPIO_InitSturcture.GPIO_Pin = GPIO_Pin_12;
        GPIO_InitSturcture.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitSturcture.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init( GPIOA, &GPIO_InitSturcture);

        GPIO_InitSturcture.GPIO_Pin = GPIO_Pin_11;
        GPIO_InitSturcture.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_Init( GPIOA, &GPIO_InitSturcture);
        */
    }
#endif
#ifdef BSP_USING_CAN2
    if (CAN2 == can_base)
    {
        RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE );
        RCC_APB1PeriphClockCmd( RCC_APB1Periph_CAN2, ENABLE );
        // CAN2 TXD --> PB13        CAN2 RXD --> PB12
        GPIO_InitSturcture.GPIO_Pin = GPIO_Pin_13;
        GPIO_InitSturcture.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitSturcture.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init( GPIOB, &GPIO_InitSturcture);
        GPIO_InitSturcture.GPIO_Pin = GPIO_Pin_12;
        GPIO_InitSturcture.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_Init( GPIOB, &GPIO_InitSturcture);
        /*
        RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE );
        RCC_APB1PeriphClockCmd( RCC_APB1Periph_CAN2, ENABLE );
        GPIO_PinRemapConfig( GPIO_Remap_CAN2, ENABLE);
        // CAN2 TXD --> PB6        CAN2 RXD --> PB5
        GPIO_InitSturcture.GPIO_Pin = GPIO_Pin_6;
        GPIO_InitSturcture.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitSturcture.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init( GPIOB, &GPIO_InitSturcture);
        GPIO_InitSturcture.GPIO_Pin = GPIO_Pin_5;
        GPIO_InitSturcture.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_Init( GPIOB, &GPIO_InitSturcture);
        */
    }
#endif
}
#endif /* BSP_USING_CAN */

static uint32_t get_can_baud_index(rt_uint32_t baud)
{
    rt_uint32_t len, index;

    len = sizeof(can_baud_rate_tab) / sizeof(can_baud_rate_tab[0]);
    for (index = 0; index < len; index++)
    {
        if (can_baud_rate_tab[index].baud_rate == baud)
            return index;
    }
    return 0; /* default baud is CAN1MBaud */
}

static rt_uint8_t get_can_mode_rtt2n32(rt_uint8_t rtt_can_mode)
{
    rt_uint8_t mode = CAN_Mode_Normal;
    switch (rtt_can_mode)
    {
    case RT_CAN_MODE_NORMAL:
        mode = CAN_Mode_Normal;
        break;
    case RT_CAN_MODE_LISTEN:
        mode = CAN_Mode_Silent;
        break;
    case RT_CAN_MODE_LOOPBACK:
        mode = CAN_Mode_LoopBack;
        break;
    case RT_CAN_MODE_LOOPBACKANLISTEN:
        mode = CAN_Mode_Silent_LoopBack;
        break;
    }
    return mode;
}

static rt_err_t _can_filter_config(struct ch32v307x_can_obj *drv_can_obj)
{
    if (drv_can_obj->can_base == CAN1)
    {
        CAN_FilterInit( &(drv_can_obj->can_filter_init) );
    }
    else if (drv_can_obj->can_base == CAN2)
    {
        CAN_FilterInit( &(drv_can_obj->can_filter_init) );
    }
    else
    {
        LOG_E("can filter config error");
        return -RT_EINVAL;
    }
    return RT_EOK;
}


static rt_err_t _can_config(struct rt_can_device *can, struct can_configure *cfg)
{
    struct ch32v307x_can_obj *drv_can_obj;
    rt_uint32_t baud_index;
    int smaple = 0;

    RT_ASSERT(can);
    RT_ASSERT(cfg);
    drv_can_obj = (struct ch32v307x_can_obj *)can->parent.user_data;
    RT_ASSERT(drv_can_obj);

    CAN_DeInit(drv_can_obj->can_base);

    /* Configure CAN gpio clk */
    if (drv_can_obj->can_base == CAN1)
    {
        ch32v307x_can_gpio_init(CAN1);
    }
    else if (drv_can_obj->can_base == CAN2)
    {
        ch32v307x_can_gpio_init(CAN2);
    }
    else
    {
        LOG_E("can gpio init error");
        return -RT_EINVAL;
    }

    drv_can_obj->can_init.CAN_TTCM = DISABLE;
    drv_can_obj->can_init.CAN_ABOM = DISABLE;
    drv_can_obj->can_init.CAN_AWUM = DISABLE;
    drv_can_obj->can_init.CAN_NART = ENABLE;
    drv_can_obj->can_init.CAN_RFLM = DISABLE;
    drv_can_obj->can_init.CAN_TXFP = ENABLE;

    //mode
    drv_can_obj->can_init.CAN_Mode = get_can_mode_rtt2n32(cfg->mode);

    //baud
    baud_index = get_can_baud_index(cfg->baud_rate);
    drv_can_obj->can_init.CAN_SJW = can_baud_rate_tab[baud_index].tsjw;
    drv_can_obj->can_init.CAN_BS1 = can_baud_rate_tab[baud_index].tbs1;
    drv_can_obj->can_init.CAN_BS2 = can_baud_rate_tab[baud_index].tbs2;
    drv_can_obj->can_init.CAN_Prescaler = can_baud_rate_tab[baud_index].prescaler;
    /* init can */
    if (CAN_Init( drv_can_obj->can_base, &(drv_can_obj->can_init) ) != CAN_InitStatus_Success )
    {
        LOG_E("can init error");
        return -RT_ERROR;
    }

    smaple = (can_baud_rate_tab[baud_index].tsjw + can_baud_rate_tab[baud_index].tbs1)*100 * 100 ;
    smaple = smaple / (can_baud_rate_tab[baud_index].tsjw + can_baud_rate_tab[baud_index].tbs1 + can_baud_rate_tab[baud_index].tbs2);
    LOG_D("can[%08X] init baud:%d sjw:%d tbs1:%d tbs2:%d prescaler:%d sample:%d.%d",
            drv_can_obj->can_base,  cfg->baud_rate,
            can_baud_rate_tab[baud_index].tsjw,  can_baud_rate_tab[baud_index].tbs1, can_baud_rate_tab[baud_index].tbs2,
            can_baud_rate_tab[baud_index].prescaler , smaple/100, smaple%100);

    /* default filter config */
    _can_filter_config(drv_can_obj);
    return RT_EOK;
}

static rt_err_t _can_control(struct rt_can_device *can, int cmd, void *arg)
{
    rt_uint32_t argval;
    struct ch32v307x_can_obj *drv_can_obj;
    struct rt_can_filter_config *filter_cfg;

    RT_ASSERT(can != RT_NULL);
    drv_can_obj = (struct ch32v307x_can_obj *)can->parent.user_data;
    RT_ASSERT(drv_can_obj != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        argval = (rt_uint32_t)arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            if (CAN1 == drv_can_obj->can_base)
            {
                NVIC_DisableIRQ(USB_LP_CAN1_RX0_IRQn);
                NVIC_DisableIRQ(CAN1_RX1_IRQn);
            }
            if (CAN2 == drv_can_obj->can_base)
            {
                NVIC_DisableIRQ(CAN2_RX0_IRQn);
                NVIC_DisableIRQ(CAN2_RX1_IRQn);
            }
//            CAN_ClearITPendingBit( drv_can_obj->can_base, CAN_IT_FMP0 );
//            CAN_ClearITPendingBit( drv_can_obj->can_base, CAN_IT_FF0 );
//            CAN_ClearITPendingBit( drv_can_obj->can_base, CAN_IT_FOV0 );
//            CAN_ClearITPendingBit( drv_can_obj->can_base, CAN_IT_FMP1 );
//            CAN_ClearITPendingBit( drv_can_obj->can_base, CAN_IT_FF1 );
//            CAN_ClearITPendingBit( drv_can_obj->can_base, CAN_IT_FOV1 );

            CAN_ITConfig(drv_can_obj->can_base, CAN_IT_FMP0, DISABLE); /* FIFO 0 message pending Interrupt*/
            CAN_ITConfig(drv_can_obj->can_base, CAN_IT_FF0,  DISABLE);  /* FIFO 0 full Interrupt*/
            CAN_ITConfig(drv_can_obj->can_base, CAN_IT_FOV0, DISABLE); /* FIFO 0 overrun Interrupt*/
            CAN_ITConfig(drv_can_obj->can_base, CAN_IT_FMP1, DISABLE); /* FIFO 1 message pending Interrupt*/
            CAN_ITConfig(drv_can_obj->can_base, CAN_IT_FF1,  DISABLE);  /* FIFO 1 full Interrupt*/
            CAN_ITConfig(drv_can_obj->can_base, CAN_IT_FOV1, DISABLE); /* FIFO 1 overrun Interrupt*/
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            if (CAN1 == drv_can_obj->can_base)
            {
                NVIC_DisableIRQ(USB_HP_CAN1_TX_IRQn);
            }
            if (CAN2 == drv_can_obj->can_base)
            {
                NVIC_DisableIRQ(CAN2_TX_IRQn);
            }
            CAN_ITConfig(drv_can_obj->can_base, CAN_IT_TME, DISABLE); /*!< Transmit mailbox empty Interrupt*/
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            if (CAN1 == drv_can_obj->can_base)
            {
                NVIC_DisableIRQ(CAN1_SCE_IRQn);
            }
            if (CAN2 == drv_can_obj->can_base)
            {
                NVIC_DisableIRQ(CAN2_SCE_IRQn);
            }
            CAN_ClearITPendingBit( drv_can_obj->can_base, CAN_IT_EWG );
            CAN_ClearITPendingBit( drv_can_obj->can_base, CAN_IT_EPV );
            CAN_ClearITPendingBit( drv_can_obj->can_base, CAN_IT_BOF );
            CAN_ClearITPendingBit( drv_can_obj->can_base, CAN_IT_LEC );
            CAN_ClearITPendingBit( drv_can_obj->can_base, CAN_IT_ERR );

            CAN_ITConfig(drv_can_obj->can_base, CAN_IT_EWG, DISABLE); /*!< Error warning Interrupt*/
            CAN_ITConfig(drv_can_obj->can_base, CAN_IT_EPV, DISABLE); /*!< Error passive Interrupt*/
            CAN_ITConfig(drv_can_obj->can_base, CAN_IT_BOF, DISABLE); /*!< Bus-off Interrupt*/
            CAN_ITConfig(drv_can_obj->can_base, CAN_IT_LEC, DISABLE); /*!< Last error code Interrupt*/
            CAN_ITConfig(drv_can_obj->can_base, CAN_IT_ERR, DISABLE); /*!< Error Interrupt*/
        }
        break;
    case RT_DEVICE_CTRL_SET_INT:
        argval = (rt_uint32_t)arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            CAN_ClearITPendingBit( drv_can_obj->can_base, CAN_IT_FMP0 );
            CAN_ClearITPendingBit( drv_can_obj->can_base, CAN_IT_FF0 );
            CAN_ClearITPendingBit( drv_can_obj->can_base, CAN_IT_FOV0 );
            CAN_ClearITPendingBit( drv_can_obj->can_base, CAN_IT_FMP1 );
            CAN_ClearITPendingBit( drv_can_obj->can_base, CAN_IT_FF1 );
            CAN_ClearITPendingBit( drv_can_obj->can_base, CAN_IT_FOV1 );

            CAN_ITConfig(drv_can_obj->can_base, CAN_IT_FMP0, ENABLE); /* FIFO 0 message pending Interrupt*/
            CAN_ITConfig(drv_can_obj->can_base, CAN_IT_FF0,  ENABLE);  /* FIFO 0 full Interrupt*/
            CAN_ITConfig(drv_can_obj->can_base, CAN_IT_FOV0, ENABLE); /* FIFO 0 overrun Interrupt*/
            CAN_ITConfig(drv_can_obj->can_base, CAN_IT_FMP1, ENABLE); /* FIFO 1 message pending Interrupt*/
            CAN_ITConfig(drv_can_obj->can_base, CAN_IT_FF1,  ENABLE);  /* FIFO 1 full Interrupt*/
            CAN_ITConfig(drv_can_obj->can_base, CAN_IT_FOV1, ENABLE); /* FIFO 1 overrun Interrupt*/

            if (CAN1 == drv_can_obj->can_base)
            {
                NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn, 1);
                NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
                NVIC_SetPriority(CAN1_RX1_IRQn, 1);
                NVIC_EnableIRQ(CAN1_RX1_IRQn);
            }
            if (CAN2 == drv_can_obj->can_base)
            {
                NVIC_SetPriority(CAN2_RX0_IRQn, 1);
                NVIC_EnableIRQ(CAN2_RX0_IRQn);
                NVIC_SetPriority(CAN2_RX1_IRQn, 1);
                NVIC_EnableIRQ(CAN2_RX1_IRQn);
            }
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            CAN_ClearITPendingBit( drv_can_obj->can_base, CAN_IT_TME );
            CAN_ITConfig(drv_can_obj->can_base, CAN_IT_TME, ENABLE); /*!< Transmit mailbox empty Interrupt*/

            if (CAN1 == drv_can_obj->can_base)
            {
                NVIC_SetPriority(USB_HP_CAN1_TX_IRQn, 1);
                NVIC_EnableIRQ(USB_HP_CAN1_TX_IRQn);
            }
            if (CAN2 == drv_can_obj->can_base)
            {
                NVIC_SetPriority(CAN2_TX_IRQn, 1);
                NVIC_EnableIRQ(CAN2_TX_IRQn);
            }
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            CAN_ITConfig(drv_can_obj->can_base, CAN_IT_EWG, ENABLE); /*!< Error warning Interrupt*/
            CAN_ITConfig(drv_can_obj->can_base, CAN_IT_EPV, ENABLE); /*!< Error passive Interrupt*/
            CAN_ITConfig(drv_can_obj->can_base, CAN_IT_BOF, ENABLE); /*!< Bus-off Interrupt*/
            CAN_ITConfig(drv_can_obj->can_base, CAN_IT_LEC, ENABLE); /*!< Last error code Interrupt*/
            CAN_ITConfig(drv_can_obj->can_base, CAN_IT_ERR, ENABLE); /*!< Error Interrupt*/

            if (CAN1 == drv_can_obj->can_base)
            {
                NVIC_SetPriority(CAN1_SCE_IRQn, 1);
                NVIC_EnableIRQ(CAN1_SCE_IRQn);
            }
            if (CAN2 == drv_can_obj->can_base)
            {
                NVIC_SetPriority(CAN2_SCE_IRQn, 1);
                NVIC_EnableIRQ(CAN2_SCE_IRQn);
            }
        }
        break;
    case RT_CAN_CMD_SET_FILTER:
    {
        rt_uint32_t id_h = 0;
        rt_uint32_t id_l = 0;
        rt_uint32_t mask_h = 0;
        rt_uint32_t mask_l = 0;

        if (RT_NULL == arg)
        {
            /* default filter config */
            _can_filter_config(drv_can_obj);
        }
        else
        {
            filter_cfg = (struct rt_can_filter_config *)arg;
            /* get default filter */
            for (int i = 0; i < filter_cfg->count; i++)
            {
                if (filter_cfg->items[i].hdr_bank == -1)
                {
                    drv_can_obj->can_filter_init.CAN_FilterNumber = i;
                }
                else
                {
                    /* use user-defined filter bank settings */
                    drv_can_obj->can_filter_init.CAN_FilterNumber = filter_cfg->items[i].hdr_bank;
                }

                if (filter_cfg->items[i].mode == 0x00)  //CAN_FILTERMODE_IDMASK
                {
                    drv_can_obj->can_filter_init.CAN_FilterMode = CAN_FilterMode_IdMask;
                }
                else if (filter_cfg->items[i].mode == 0x01)  //CAN_FILTERMODE_IDLIST
                {
                    drv_can_obj->can_filter_init.CAN_FilterMode = CAN_FilterMode_IdList;
                }

                if (filter_cfg->items[i].ide == RT_CAN_STDID)
                {
                    id_h = ((filter_cfg->items[i].id << 18) >> 13) & 0xFFFF;
                    id_l = ((filter_cfg->items[i].id << 18) |
                            (filter_cfg->items[i].ide << 2) |
                            (filter_cfg->items[i].rtr << 1)) & 0xFFFF;
                    mask_h = ((filter_cfg->items[i].mask << 21) >> 16) & 0xFFFF;
                    mask_l = ((filter_cfg->items[i].mask << 21)) & 0xFFFF;
                }
                else if (filter_cfg->items[i].ide == RT_CAN_EXTID)
                {
                    id_h = (filter_cfg->items[i].id >> 13) & 0xFFFF;
                    id_l = ((filter_cfg->items[i].id << 3) |
                            (filter_cfg->items[i].ide << 2) |
                            (filter_cfg->items[i].rtr << 1)) & 0xFFFF;
                    mask_h = ((filter_cfg->items[i].mask << 3) >> 16) & 0xFFFF;
                    mask_l = ((filter_cfg->items[i].mask << 3) ) & 0xFFFF;
                }
                drv_can_obj->can_filter_init.CAN_FilterScale = CAN_FilterScale_32bit;
                drv_can_obj->can_filter_init.CAN_FilterIdHigh = id_h;
                drv_can_obj->can_filter_init.CAN_FilterIdLow  = id_l;
                drv_can_obj->can_filter_init.CAN_FilterMaskIdHigh = mask_h;
                drv_can_obj->can_filter_init.CAN_FilterMaskIdLow  = mask_l;
                drv_can_obj->can_filter_init.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
                drv_can_obj->can_filter_init.CAN_FilterActivation = ENABLE;

                /* Filter conf */
                _can_filter_config(drv_can_obj);
            }
        }
        break;
    }
    case RT_CAN_CMD_SET_MODE:
        argval = (rt_uint32_t)arg;
        if (argval != RT_CAN_MODE_NORMAL &&
            argval != RT_CAN_MODE_LISTEN &&
            argval != RT_CAN_MODE_LOOPBACK &&
            argval != RT_CAN_MODE_LOOPBACKANLISTEN)
        {
            return -RT_ERROR;
        }
        if (argval != drv_can_obj->device.config.mode)
        {
            drv_can_obj->device.config.mode = argval;
            return _can_config(&drv_can_obj->device, &drv_can_obj->device.config);
        }
        break;
    case RT_CAN_CMD_SET_BAUD:
        argval = (rt_uint32_t)arg;
        if (argval != CAN1MBaud &&
            argval != CAN800kBaud &&
            argval != CAN500kBaud &&
            argval != CAN250kBaud &&
            argval != CAN125kBaud &&
            argval != CAN100kBaud &&
            argval != CAN50kBaud &&
            argval != CAN20kBaud &&
            argval != CAN10kBaud)
        {
            return -RT_ERROR;
        }
        if (argval != drv_can_obj->device.config.baud_rate)
        {
            drv_can_obj->device.config.baud_rate = argval;
            return _can_config(&drv_can_obj->device, &drv_can_obj->device.config);
        }
        break;
    case RT_CAN_CMD_SET_PRIV:
        argval = (rt_uint32_t)arg;
        if (argval != RT_CAN_MODE_PRIV &&
            argval != RT_CAN_MODE_NOPRIV)
        {
            return -RT_ERROR;
        }
        if (argval != drv_can_obj->device.config.privmode)
        {
            drv_can_obj->device.config.privmode = argval;
            return _can_config(&drv_can_obj->device, &drv_can_obj->device.config);
        }
        break;
    case RT_CAN_CMD_GET_STATUS:
    {
        rt_uint32_t errval;
        errval = drv_can_obj->can_base->ERRSR;  //ERRSR
        drv_can_obj->device.status.rcverrcnt = errval >> 24;            //REC
        drv_can_obj->device.status.snderrcnt = (errval >> 16 & 0xFF);   //TEC
        drv_can_obj->device.status.lasterrtype = errval & 0x70;         //LEC
        drv_can_obj->device.status.errcode = errval & 0x07;

        rt_memcpy(arg, &drv_can_obj->device.status, sizeof(drv_can_obj->device.status));
    }
    break;
    }

    return RT_EOK;
}

/* CAN Mailbox Transmit Request */
#define TMIDxR_TXRQ         ((rt_uint32_t)0x00000001)

static int _can_send_rtmsg(CAN_TypeDef *can_base, struct rt_can_msg *pmsg, rt_uint32_t mailbox_index)
{
    CanTxMsg CAN_TxMessage = {0};
    CanTxMsg *TxMessage = &CAN_TxMessage;
    /* Select one empty transmit mailbox */
    switch (mailbox_index)
    {
    case 0:
        if ((can_base->TSTATR & CAN_TSTATR_TME0) != CAN_TSTATR_TME0)
        {
            /* Return function status */
            return -RT_ERROR;
        }
        break;
    case 1:
        if ((can_base->TSTATR & CAN_TSTATR_TME1) != CAN_TSTATR_TME1)
        {
            /* Return function status */
            return -RT_ERROR;
        }
        break;
    case 2:
        if ((can_base->TSTATR & CAN_TSTATR_TME2) != CAN_TSTATR_TME2)
        {
            /* Return function status */
            return -RT_ERROR;
        }
        break;
    default:
        RT_ASSERT(0);
        return -RT_ERROR;
        break;
    }

    if (RT_CAN_STDID == pmsg->ide)
    {
        TxMessage->IDE = CAN_Id_Standard;
        TxMessage->StdId = pmsg->id;
    }
    else
    {
        TxMessage->IDE = CAN_Id_Extended;
        TxMessage->ExtId = pmsg->id;
    }

    if (RT_CAN_DTR == pmsg->rtr)
    {
        TxMessage->RTR = CAN_RTR_Data;
    }
    else
    {
        TxMessage->RTR = CAN_RTR_Remote;
    }

    if (mailbox_index != CAN_TxStatus_NoMailBox)
    {
        /* Set Id */
        can_base->sTxMailBox[mailbox_index].TXMIR  &= TMIDxR_TXRQ;
        if (TxMessage->IDE == CAN_Id_Standard)
        {
            can_base->sTxMailBox[mailbox_index].TXMIR |= ((TxMessage->StdId << 21) | TxMessage->RTR);
        }
        else
        {
            can_base->sTxMailBox[mailbox_index].TXMIR |= ((TxMessage->ExtId << 3) | TxMessage->IDE | TxMessage->RTR);
        }

        /* Set DLC */
        TxMessage->DLC = pmsg->len & 0x0FU;
        can_base->sTxMailBox[mailbox_index].TXMDTR &= (rt_uint32_t)0xFFFFFFF0;
        can_base->sTxMailBox[mailbox_index].TXMDTR |= TxMessage->DLC;

        /* Set data */
        can_base->sTxMailBox[mailbox_index].TXMDHR =
            (((rt_uint32_t)pmsg->data[7] << 24) |
             ((rt_uint32_t)pmsg->data[6] << 16) |
             ((rt_uint32_t)pmsg->data[5] << 8) |
             ((rt_uint32_t)pmsg->data[4]));
        can_base->sTxMailBox[mailbox_index].TXMDLR =
            (((rt_uint32_t)pmsg->data[3] << 24) |
             ((rt_uint32_t)pmsg->data[2] << 16) |
             ((rt_uint32_t)pmsg->data[1] << 8) |
             ((rt_uint32_t)pmsg->data[0]));
        /* Request transmission */
        can_base->sTxMailBox[mailbox_index].TXMIR |= TMIDxR_TXRQ;

        //CAN_Transmit();
        return RT_EOK;
    }
    return -RT_ERROR;
}

static int _can_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t box_num)
{
    struct ch32v307x_can_obj *drv_can_obj;

    RT_ASSERT(can != RT_NULL);
    RT_ASSERT(buf != RT_NULL);
    drv_can_obj = (struct ch32v307x_can_obj *)can->parent.user_data;
    RT_ASSERT(drv_can_obj != RT_NULL);

    //start send msg
    return _can_send_rtmsg(drv_can_obj->can_base, ((struct rt_can_msg *)buf), box_num);
}

static int _can_recv_rtmsg(CAN_TypeDef *can_base, struct rt_can_msg *pmsg, rt_uint32_t FIFONum)
{
    CanRxMsg CAN_RxMessage = {0};
    CanRxMsg *RxMessage = &CAN_RxMessage;

    /* Check the Rx FIFO */
    if( CAN_MessagePending( can_base, FIFONum ) == 0)
    {
        return -RT_ERROR;
    }
    /* Get the Id */
    RxMessage->IDE = (rt_uint8_t)(0x04 & can_base->sFIFOMailBox[FIFONum].RXMIR);
    if (RxMessage->IDE == CAN_Id_Standard)
    {
        RxMessage->StdId = (rt_uint32_t)0x000007FF & (can_base->sFIFOMailBox[FIFONum].RXMIR >> 21);
    }
    else
    {
        RxMessage->ExtId = (rt_uint32_t)0x1FFFFFFF & (can_base->sFIFOMailBox[FIFONum].RXMIR >> 3);
    }
    RxMessage->RTR = (rt_uint8_t)0x02 & can_base->sFIFOMailBox[FIFONum].RXMIR;
    /* Get the DLC */
    RxMessage->DLC = (rt_uint8_t)0x0F & can_base->sFIFOMailBox[FIFONum].RXMDTR;
    /* Get the FMI */
    RxMessage->FMI = (rt_uint8_t)0xFF & (can_base->sFIFOMailBox[FIFONum].RXMDTR >> 8);

    /* Get the data field */
    pmsg->data[0] = (rt_uint8_t)0xFF &  can_base->sFIFOMailBox[FIFONum].RXMDLR;
    pmsg->data[1] = (rt_uint8_t)0xFF & (can_base->sFIFOMailBox[FIFONum].RXMDLR >> 8);
    pmsg->data[2] = (rt_uint8_t)0xFF & (can_base->sFIFOMailBox[FIFONum].RXMDLR >> 16);
    pmsg->data[3] = (rt_uint8_t)0xFF & (can_base->sFIFOMailBox[FIFONum].RXMDLR >> 24);
    pmsg->data[4] = (rt_uint8_t)0xFF &  can_base->sFIFOMailBox[FIFONum].RXMDHR;
    pmsg->data[5] = (rt_uint8_t)0xFF & (can_base->sFIFOMailBox[FIFONum].RXMDHR >> 8);
    pmsg->data[6] = (rt_uint8_t)0xFF & (can_base->sFIFOMailBox[FIFONum].RXMDHR >> 16);
    pmsg->data[7] = (rt_uint8_t)0xFF & (can_base->sFIFOMailBox[FIFONum].RXMDHR >> 24);

    /* get len */
    pmsg->len = RxMessage->DLC;

    /* get id */
    if (RxMessage->IDE == CAN_Id_Standard)
    {
        pmsg->ide = RT_CAN_STDID;
        pmsg->id = RxMessage->StdId;
    }
    else
    {
        pmsg->ide = RT_CAN_EXTID;
        pmsg->id = RxMessage->ExtId;
    }
    /* get type */
    if (CAN_RTR_Data == RxMessage->RTR)
    {
        pmsg->rtr = RT_CAN_DTR;
    }
    else
    {
        pmsg->rtr = RT_CAN_RTR;
    }

    /* get hdr_index */
    if (can_base == CAN1)
    {
        pmsg->hdr_index = (RxMessage->FMI + 1) >> 1;
    }
    else if (can_base == CAN2)
    {
        pmsg->hdr_index = (RxMessage->FMI >> 1) + 14;
    }
    /* Release FIFO */
    CAN_FIFORelease(can_base,FIFONum);
    return RT_EOK;
}

static int _can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t fifo)
{
    struct ch32v307x_can_obj *drv_can_obj;

    RT_ASSERT(can != RT_NULL);
    RT_ASSERT(buf != RT_NULL);
    drv_can_obj = (struct ch32v307x_can_obj *)can->parent.user_data;
    RT_ASSERT(drv_can_obj != RT_NULL);

    /* get data */
    return _can_recv_rtmsg(drv_can_obj->can_base, ((struct rt_can_msg *)buf), fifo);
}

static const struct rt_can_ops _can_ops =
{
    _can_config,
    _can_control,
    _can_sendmsg,
    _can_recvmsg,
};

static void _can_rx_isr(struct rt_can_device *can, rt_uint32_t fifo)
{
    struct ch32v307x_can_obj *drv_can_obj;
    RT_ASSERT(can != RT_NULL);
    drv_can_obj = (struct ch32v307x_can_obj *)can->parent.user_data;
    RT_ASSERT(drv_can_obj != RT_NULL);

    CAN_TypeDef * can_base = drv_can_obj->can_base;

    switch (fifo)
    {
    case CAN_FIFO0:
        if( ((can_base->RFIFO0 & CAN_RFIFO0_FMP0) ) && ((can_base->INTENR & CAN_IT_FMP0) == CAN_IT_FMP0) )
        {
            rt_hw_can_isr(can, RT_CAN_EVENT_RX_IND | fifo << 8);
        }
        if( ((can_base->RFIFO0 & CAN_RFIFO0_FULL0)) && ((can_base->INTENR & CAN_IT_FF0) == CAN_IT_FF0) )
        {
            can_base->RFIFO0 |= CAN_RFIFO0_FULL0;  //clear
        }
        if( ((can_base->RFIFO0 & CAN_RFIFO0_FOVR0)) && ((can_base->INTENR & CAN_IT_FOV0) == CAN_IT_FOV0) )
        {
            can_base->RFIFO0 |= CAN_RFIFO0_FOVR0;  //clear
            rt_hw_can_isr(can, RT_CAN_EVENT_RXOF_IND | fifo << 8);
        }
        break;
    case CAN_FIFO1:
        if( ((can_base->RFIFO1 & CAN_RFIFO1_FMP1)) && ((can_base->INTENR & CAN_IT_FMP1) == CAN_IT_FMP1) )
        {
            rt_hw_can_isr(can, RT_CAN_EVENT_RX_IND | fifo << 8);
        }
        if( ((can_base->RFIFO1 & CAN_RFIFO1_FULL1)) && ((can_base->INTENR & CAN_IT_FF1) == CAN_IT_FF1) )
        {
            can_base->RFIFO1 |= CAN_RFIFO1_FULL1;  //clear
        }
        if( ((can_base->RFIFO1 & CAN_RFIFO1_FOVR1)) && ((can_base->INTENR & CAN_IT_FOV1) == CAN_IT_FOV1) )
        {
            can_base->RFIFO1 |= CAN_RFIFO1_FOVR1;  //clear
            rt_hw_can_isr(can, RT_CAN_EVENT_RXOF_IND | fifo << 8);
        }
        break;
    }
}

#ifdef BSP_USING_CAN1
/**
 * @brief This function handles CAN1 TX interrupts. transmit fifo0/1/2 is empty can trigger this interrupt
 */
void USB_HP_CAN1_TX_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USB_HP_CAN1_TX_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    struct ch32v307x_can_obj *drv_can_obj = &drv_can1;

    CAN_TypeDef * can_base = drv_can_obj->can_base;

    if((can_base->INTENR & CAN_IT_TME) == CAN_IT_TME)
    {
        if( (can_base->TSTATR & CAN_TSTATR_RQCP0) == CAN_TSTATR_RQCP0)
        {
            //Request Completed Mailbox0
            if( ( can_base->TSTATR & CAN_TSTATR_TXOK0) == CAN_TSTATR_TXOK0)
            {
                can_base->TSTATR |= CAN_TSTATR_TXOK0; // set 1 clear
                rt_hw_can_isr(&drv_can_obj->device, RT_CAN_EVENT_TX_DONE | (0x00 << 8));
            }
            if( ( ( can_base->TSTATR & CAN_TSTATR_ALST0) == CAN_TSTATR_ALST0)
                || (( can_base->TSTATR & CAN_TSTATR_TERR0) == CAN_TSTATR_TERR0) )
            {
                can_base->TSTATR |= (CAN_TSTATR_ALST0 | CAN_TSTATR_TERR0); // set 1 clear
                rt_hw_can_isr(&drv_can_obj->device, RT_CAN_EVENT_TX_FAIL | (0x00 << 8));
            }
            can_base->TSTATR |= CAN_TSTATR_RQCP0; // set 1 clear
        }
        if( (can_base->TSTATR & CAN_TSTATR_RQCP1) == CAN_TSTATR_RQCP1)
        {
            //Request Completed Mailbox1
            if( ( can_base->TSTATR & CAN_TSTATR_TXOK1) == CAN_TSTATR_TXOK1)
            {
                can_base->TSTATR |= CAN_TSTATR_TXOK1; // set 1 clear
                rt_hw_can_isr(&drv_can_obj->device, RT_CAN_EVENT_TX_DONE | (0x01 << 8));
            }
            if( ( ( can_base->TSTATR & CAN_TSTATR_ALST1) == CAN_TSTATR_ALST1)
                || (( can_base->TSTATR & CAN_TSTATR_TERR1) == CAN_TSTATR_TERR1) )
            {
                can_base->TSTATR |= (CAN_TSTATR_ALST1 | CAN_TSTATR_TERR1); // set 1 clear
                rt_hw_can_isr(&drv_can_obj->device, RT_CAN_EVENT_TX_FAIL | (0x01 << 8));
            }
            can_base->TSTATR |= CAN_TSTATR_RQCP1; // set 1 clear
        }
        if( (can_base->TSTATR & CAN_TSTATR_RQCP2) == CAN_TSTATR_RQCP2)
        {
            //Request Completed Mailbox2
            if( ( can_base->TSTATR & CAN_TSTATR_TXOK2) == CAN_TSTATR_TXOK2)
            {
                can_base->TSTATR |= CAN_TSTATR_TXOK2; // set 1 clear
                rt_hw_can_isr(&drv_can_obj->device, RT_CAN_EVENT_TX_DONE | (0x02 << 8));
            }
            if( ( ( can_base->TSTATR & CAN_TSTATR_ALST2) == CAN_TSTATR_ALST2)
                || (( can_base->TSTATR & CAN_TSTATR_TERR2) == CAN_TSTATR_TERR2) )
            {
                can_base->TSTATR |= (CAN_TSTATR_ALST2 | CAN_TSTATR_TERR2); // set 1 clear
                rt_hw_can_isr(&drv_can_obj->device, RT_CAN_EVENT_TX_FAIL | (0x02 << 8));
            }
            can_base->TSTATR |= CAN_TSTATR_RQCP2; // set 1 clear
        }
        CAN_ClearITPendingBit( can_base, CAN_IT_TME );
    }
    rt_interrupt_leave();
    FREE_INT_SP();
}

/**
 * @brief This function handles CAN1 RX0 interrupts.
 */
void USB_LP_CAN1_RX0_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USB_LP_CAN1_RX0_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    _can_rx_isr(&drv_can1.device, CAN_FIFO0);
    rt_interrupt_leave();
    FREE_INT_SP();
}

/**
 * @brief This function handles CAN1 RX1 interrupts.
 */
void CAN1_RX1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void CAN1_RX1_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    _can_rx_isr(&drv_can1.device, CAN_FIFO1);
    rt_interrupt_leave();
    FREE_INT_SP();
}

/**
 * @brief This function handles CAN1 SCE interrupts.
 */
void CAN1_SCE_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void CAN1_SCE_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();

    struct ch32v307x_can_obj *drv_can_obj = &drv_can1;
    CAN_TypeDef * can_base = drv_can_obj->can_base;
    rt_uint32_t errval = can_base->ERRSR;  //ERRSR

    switch ((errval & 0x70) >> 4)
    {
    case RT_CAN_BUS_BIT_PAD_ERR:
        drv_can_obj->device.status.bitpaderrcnt++;
        break;
    case RT_CAN_BUS_FORMAT_ERR:
        drv_can_obj->device.status.formaterrcnt++;
        break;
    case RT_CAN_BUS_ACK_ERR:
        drv_can_obj->device.status.ackerrcnt++;
        if( (can_base->TSTATR & CAN_TSTATR_TXOK0) == CAN_TSTATR_TXOK0)
        {
            rt_hw_can_isr(&drv_can_obj->device, RT_CAN_EVENT_TX_FAIL | 0x00 << 8);
        }else
        if( (can_base->TSTATR & CAN_TSTATR_TXOK1) == CAN_TSTATR_TXOK1)
        {
            rt_hw_can_isr(&drv_can_obj->device, RT_CAN_EVENT_TX_FAIL | 0x01 << 8);
        }else
        if( (can_base->TSTATR & CAN_TSTATR_TXOK2) == CAN_TSTATR_TXOK2)
        {
            rt_hw_can_isr(&drv_can_obj->device, RT_CAN_EVENT_TX_FAIL | 0x02 << 8);
        }
        break;
    case RT_CAN_BUS_IMPLICIT_BIT_ERR:
    case RT_CAN_BUS_EXPLICIT_BIT_ERR:
        drv_can_obj->device.status.biterrcnt++;
        break;
    case RT_CAN_BUS_CRC_ERR:
        drv_can_obj->device.status.crcerrcnt++;
        break;
    }
    drv_can_obj->device.status.lasterrtype = errval & 0x70;
    drv_can_obj->device.status.rcverrcnt = errval >> 24;
    drv_can_obj->device.status.snderrcnt = (errval >> 16 & 0xFF);
    drv_can_obj->device.status.errcode = errval & 0x07;

    can_base->STATR |= CAN_STATR_ERRI;

    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif /* BSP_USING_CAN1 */

#ifdef BSP_USING_CAN2
/**
 * @brief This function handles CAN2 TX interrupts.
 */
void CAN2_TX_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void CAN2_TX_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    struct ch32v307x_can_obj *drv_can_obj = &drv_can2;

    CAN_TypeDef * can_base = drv_can_obj->can_base;

    if((can_base->INTENR & CAN_IT_TME) == CAN_IT_TME)
    {
        if( (can_base->TSTATR & CAN_TSTATR_RQCP0) == CAN_TSTATR_RQCP0)
        {
            //Request Completed Mailbox0
            if( ( can_base->TSTATR & CAN_TSTATR_TXOK0) == CAN_TSTATR_TXOK0)
            {
                can_base->TSTATR |= CAN_TSTATR_TXOK0; // set 1 clear
                rt_hw_can_isr(&drv_can_obj->device, RT_CAN_EVENT_TX_DONE | (0x00 << 8));
            }
            if( ( ( can_base->TSTATR & CAN_TSTATR_ALST0) == CAN_TSTATR_ALST0)
                || (( can_base->TSTATR & CAN_TSTATR_TERR0) == CAN_TSTATR_TERR0) )
            {
                can_base->TSTATR |= (CAN_TSTATR_ALST0 | CAN_TSTATR_TERR0); // set 1 clear
                rt_hw_can_isr(&drv_can_obj->device, RT_CAN_EVENT_TX_FAIL | (0x00 << 8));
            }
            can_base->TSTATR |= CAN_TSTATR_RQCP0; // set 1 clear
        }
        if( (can_base->TSTATR & CAN_TSTATR_RQCP1) == CAN_TSTATR_RQCP1)
        {
            //Request Completed Mailbox1
            if( ( can_base->TSTATR & CAN_TSTATR_TXOK1) == CAN_TSTATR_TXOK1)
            {
                can_base->TSTATR |= CAN_TSTATR_TXOK1; // set 1 clear
                rt_hw_can_isr(&drv_can_obj->device, RT_CAN_EVENT_TX_DONE | (0x01 << 8));
            }
            if( ( ( can_base->TSTATR & CAN_TSTATR_ALST1) == CAN_TSTATR_ALST1)
                || (( can_base->TSTATR & CAN_TSTATR_TERR1) == CAN_TSTATR_TERR1) )
            {
                can_base->TSTATR |= (CAN_TSTATR_ALST1 | CAN_TSTATR_TERR1); // set 1 clear
                rt_hw_can_isr(&drv_can_obj->device, RT_CAN_EVENT_TX_FAIL | (0x01 << 8));
            }
            can_base->TSTATR |= CAN_TSTATR_RQCP1; // set 1 clear
        }
        if( (can_base->TSTATR & CAN_TSTATR_RQCP2) == CAN_TSTATR_RQCP2)
        {
            //Request Completed Mailbox2
            if( ( can_base->TSTATR & CAN_TSTATR_TXOK2) == CAN_TSTATR_TXOK2)
            {
                can_base->TSTATR |= CAN_TSTATR_TXOK2; // set 1 clear
                rt_hw_can_isr(&drv_can_obj->device, RT_CAN_EVENT_TX_DONE | (0x02 << 8));
            }
            if( ( ( can_base->TSTATR & CAN_TSTATR_ALST2) == CAN_TSTATR_ALST2)
                || (( can_base->TSTATR & CAN_TSTATR_TERR2) == CAN_TSTATR_TERR2) )
            {
                can_base->TSTATR |= (CAN_TSTATR_ALST2 | CAN_TSTATR_TERR2); // set 1 clear
                rt_hw_can_isr(&drv_can_obj->device, RT_CAN_EVENT_TX_FAIL | (0x02 << 8));
            }
            can_base->TSTATR |= CAN_TSTATR_RQCP2; // set 1 clear
        }
        CAN_ClearITPendingBit( can_base, CAN_IT_TME );
    }
    rt_interrupt_leave();
    FREE_INT_SP();
}

/**
 * @brief This function handles CAN2 RX0 interrupts.
 */
void CAN2_RX0_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void CAN2_RX0_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    _can_rx_isr(&drv_can2.device, CAN_FIFO0);
    rt_interrupt_leave();
    FREE_INT_SP();
}

/**
 * @brief This function handles CAN2 RX1 interrupts.
 */
void CAN2_RX1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void CAN2_RX1_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    _can_rx_isr(&drv_can2.device, CAN_FIFO1);
    rt_interrupt_leave();
    FREE_INT_SP();
}

/**
 * @brief This function handles CAN2 SCE interrupts.
 */
void CAN2_SCE_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void CAN2_SCE_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    struct ch32v307x_can_obj *drv_can_obj = &drv_can2;
    CAN_TypeDef * can_base = drv_can_obj->can_base;
    rt_uint32_t errval = can_base->ERRSR;  //ERRSR

    switch ((errval & 0x70) >> 4)
    {
    case RT_CAN_BUS_BIT_PAD_ERR:
        drv_can_obj->device.status.bitpaderrcnt++;
        break;
    case RT_CAN_BUS_FORMAT_ERR:
        drv_can_obj->device.status.formaterrcnt++;
        break;
    case RT_CAN_BUS_ACK_ERR:
        drv_can_obj->device.status.ackerrcnt++;
        if( (can_base->TSTATR & CAN_TSTATR_TXOK0) == CAN_TSTATR_TXOK0)
        {
            rt_hw_can_isr(&drv_can_obj->device, RT_CAN_EVENT_TX_FAIL | 0x00 << 8);
        }else
        if( (can_base->TSTATR & CAN_TSTATR_TXOK1) == CAN_TSTATR_TXOK1)
        {
            rt_hw_can_isr(&drv_can_obj->device, RT_CAN_EVENT_TX_FAIL | 0x01 << 8);
        }else
        if( (can_base->TSTATR & CAN_TSTATR_TXOK2) == CAN_TSTATR_TXOK2)
        {
            rt_hw_can_isr(&drv_can_obj->device, RT_CAN_EVENT_TX_FAIL | 0x02 << 8);
        }
        break;
    case RT_CAN_BUS_IMPLICIT_BIT_ERR:
    case RT_CAN_BUS_EXPLICIT_BIT_ERR:
        drv_can_obj->device.status.biterrcnt++;
        break;
    case RT_CAN_BUS_CRC_ERR:
        drv_can_obj->device.status.crcerrcnt++;
        break;
    }
    drv_can_obj->device.status.lasterrtype = errval & 0x70;
    drv_can_obj->device.status.rcverrcnt = errval >> 24;
    drv_can_obj->device.status.snderrcnt = (errval >> 16 & 0xFF);
    drv_can_obj->device.status.errcode = errval & 0x07;

    can_base->STATR |= CAN_STATR_ERRI;
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif /* BSP_USING_CAN2 */

int rt_hw_can_init(void)
{
    struct can_configure config = CANDEFAULTCONFIG;
    config.privmode = RT_CAN_MODE_NOPRIV;
    config.ticks = 50;
#ifdef RT_CAN_USING_HDR
    config.maxhdr = 14;
#ifdef CAN2
    config.maxhdr = 28;
#endif
#endif

#ifdef BSP_USING_CAN1
    /* config default filter */
    drv_can1.can_filter_init.CAN_FilterNumber = 0;
    drv_can1.can_filter_init.CAN_FilterMode = CAN_FilterMode_IdMask;
    drv_can1.can_filter_init.CAN_FilterScale = CAN_FilterScale_32bit;
    drv_can1.can_filter_init.CAN_FilterIdHigh = 0x0000;
    drv_can1.can_filter_init.CAN_FilterIdLow = 0x0000;
    drv_can1.can_filter_init.CAN_FilterMaskIdHigh = 0;
    drv_can1.can_filter_init.CAN_FilterMaskIdLow = 0;
    drv_can1.can_filter_init.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
    drv_can1.can_filter_init.CAN_FilterActivation = ENABLE;
    drv_can1.device.config = config;
    /* register CAN1 device */
    rt_hw_can_register(&drv_can1.device, drv_can1.name, &_can_ops, &drv_can1);
#endif /* BSP_USING_CAN1 */

#ifdef BSP_USING_CAN2

    CAN_SlaveStartBank(14);

    /* config default filter */
    drv_can2.can_filter_init.CAN_FilterNumber = 14;
    drv_can2.can_filter_init.CAN_FilterMode = CAN_FilterMode_IdMask;
    drv_can2.can_filter_init.CAN_FilterScale = CAN_FilterScale_32bit;
    drv_can2.can_filter_init.CAN_FilterIdHigh = 0x0000;
    drv_can2.can_filter_init.CAN_FilterIdLow = 0x0000;
    drv_can2.can_filter_init.CAN_FilterMaskIdHigh = 0;
    drv_can2.can_filter_init.CAN_FilterMaskIdLow = 0;
    drv_can2.can_filter_init.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
    drv_can2.can_filter_init.CAN_FilterActivation = ENABLE;
    drv_can2.device.config = config;
    /* register CAN2 device */
    rt_hw_can_register(&drv_can2.device, drv_can2.name, &_can_ops, &drv_can2);
#endif /* BSP_USING_CAN2 */

    return 0;
}

INIT_BOARD_EXPORT(rt_hw_can_init);

#endif /* BSP_USING_CAN */

/************************** end of file ******************/
