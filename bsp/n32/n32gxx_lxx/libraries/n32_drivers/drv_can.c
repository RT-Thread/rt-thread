/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-19     Nations      first version
 */

#include <drv_can.h>

#ifdef RT_USING_CAN

#if defined(BSP_USING_CAN) || defined(BSP_USING_CAN1) || defined(BSP_USING_CAN2)

#if defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
#ifdef BSP_USING_CAN
static struct n32_can drv_can =
{
    .name = "bxcan",
    .CANx = CAN,
};
#endif
#endif

#ifdef BSP_USING_CAN1
static struct n32_can drv_can1 =
{
    .name = "bxcan1",
    .CANx = CAN1,
};
#endif

#ifdef BSP_USING_CAN2
static struct n32_can drv_can2 =
{
    .name = "bxcan2",
    .CANx = CAN2,
};
#endif

#if defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
#ifdef BSP_USING_CAN
static void bxcan_hw_init(void)
{
    GPIO_InitType GPIO_InitStructure;

    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_CAN, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_AFIO, ENABLE);

    GPIO_InitStruct(&GPIO_InitStructure);

    /* Configure CAN_TX PB9 and CAN_RX PB8 */
    GPIO_InitStructure.Pin            = GPIO_PIN_9;
    GPIO_InitStructure.GPIO_Mode      = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pull      = GPIO_Pull_Up;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF5_CAN;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.Pin            = GPIO_PIN_8;
    GPIO_InitStructure.GPIO_Mode      = GPIO_Mode_Input;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
}
#endif
#endif

#ifdef BSP_USING_CAN1
static void bxcan1_hw_init(void)
{
    GPIO_InitType GPIO_InitStructure;

    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_AFIO, ENABLE);
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_CAN1, ENABLE);

    GPIO_InitStruct(&GPIO_InitStructure);
    /* Configure CAN1_TX PB9 and CAN1_RX PB8 */
    GPIO_InitStructure.Pin        = GPIO_PIN_8;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.Pin        = GPIO_PIN_9;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);

    /* Remap CAN1 GPIOs */
    GPIO_ConfigPinRemap(GPIO_RMP2_CAN1, ENABLE);
}
#endif /* BSP_USING_CAN1 */

#ifdef BSP_USING_CAN2
static void bxcan2_hw_init(void)
{
    GPIO_InitType GPIO_InitStructure;

    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_CAN2, ENABLE);

    GPIO_InitStruct(&GPIO_InitStructure);
    /* Configure CAN2_TX PB13 and CAN2_RX PB12 */
    GPIO_InitStructure.Pin        = GPIO_PIN_12;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.Pin        = GPIO_PIN_13;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
}
#endif /* BSP_USING_CAN2 */


/* baud calculation example: Tclk / ((ss + bs1 + bs2) * brp), 36 / ((1 + 8 + 3) * 3) = 1MHz*/
#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR) /* APB1 36MHz(max) */
static const struct n32_baud_rate_tab can_baud_rate_tab[] =
{
    N32_CAN_BAUD_DEF(CAN1MBaud,   CAN_RSJW_1tq, CAN_TBS1_5tq, CAN_TBS2_3tq, 4),
    N32_CAN_BAUD_DEF(CAN800kBaud, CAN_RSJW_1tq, CAN_TBS1_5tq, CAN_TBS2_3tq, 5),
    N32_CAN_BAUD_DEF(CAN500kBaud, CAN_RSJW_1tq, CAN_TBS1_5tq, CAN_TBS2_3tq, 8),
    N32_CAN_BAUD_DEF(CAN250kBaud, CAN_RSJW_1tq, CAN_TBS1_5tq, CAN_TBS2_3tq, 16),
    N32_CAN_BAUD_DEF(CAN125kBaud, CAN_RSJW_1tq, CAN_TBS1_5tq, CAN_TBS2_3tq, 32),
    N32_CAN_BAUD_DEF(CAN100kBaud, CAN_RSJW_2tq, CAN_TBS1_9tq, CAN_TBS2_8tq, 20),
    N32_CAN_BAUD_DEF(CAN50kBaud,  CAN_RSJW_2tq, CAN_TBS1_9tq, CAN_TBS2_8tq, 40),
    N32_CAN_BAUD_DEF(CAN20kBaud,  CAN_RSJW_2tq, CAN_TBS1_9tq, CAN_TBS2_8tq, 100),
    N32_CAN_BAUD_DEF(CAN10kBaud,  CAN_RSJW_2tq, CAN_TBS1_9tq, CAN_TBS2_8tq, 200),
};
#endif /* SOC_N32G45X  SOC_N32WB452 */

#if defined(SOC_N32L43X) || defined(SOC_N32G43X) /* APB1 27MHz(max) */
static const struct n32_baud_rate_tab can_baud_rate_tab[] =
{
    N32_CAN_BAUD_DEF(CAN1MBaud,   CAN_RSJW_1tq, CAN_TBS1_6tq, CAN_TBS2_2tq, 3),
    N32_CAN_BAUD_DEF(CAN500kBaud, CAN_RSJW_1tq, CAN_TBS1_6tq, CAN_TBS2_2tq, 6),
    N32_CAN_BAUD_DEF(CAN250kBaud, CAN_RSJW_1tq, CAN_TBS1_9tq, CAN_TBS2_8tq, 6),
    N32_CAN_BAUD_DEF(CAN125kBaud, CAN_RSJW_1tq, CAN_TBS1_9tq, CAN_TBS2_8tq, 12),
    N32_CAN_BAUD_DEF(CAN100kBaud, CAN_RSJW_2tq, CAN_TBS1_5tq, CAN_TBS2_3tq, 30),
    N32_CAN_BAUD_DEF(CAN50kBaud,  CAN_RSJW_2tq, CAN_TBS1_5tq, CAN_TBS2_3tq, 60),
    N32_CAN_BAUD_DEF(CAN20kBaud,  CAN_RSJW_2tq, CAN_TBS1_5tq, CAN_TBS2_3tq, 150),
    N32_CAN_BAUD_DEF(CAN10kBaud,  CAN_RSJW_1tq, CAN_TBS1_9tq, CAN_TBS2_8tq, 150),
};
#endif /* SOC_N32L43X */

#if defined(SOC_N32L40X) /* APB1 16MHz(max) */
static const struct n32_baud_rate_tab can_baud_rate_tab[] =
{
    N32_CAN_BAUD_DEF(CAN1MBaud,   CAN_RSJW_1tq, CAN_TBS1_5tq, CAN_TBS2_2tq, 2),
    N32_CAN_BAUD_DEF(CAN800kBaud, CAN_RSJW_1tq, CAN_TBS1_2tq, CAN_TBS2_1tq, 5),
    N32_CAN_BAUD_DEF(CAN500kBaud, CAN_RSJW_1tq, CAN_TBS1_5tq, CAN_TBS2_2tq, 4),
    N32_CAN_BAUD_DEF(CAN250kBaud, CAN_RSJW_1tq, CAN_TBS1_5tq, CAN_TBS2_2tq, 8),
    N32_CAN_BAUD_DEF(CAN125kBaud, CAN_RSJW_1tq, CAN_TBS1_5tq, CAN_TBS2_2tq, 16),
    N32_CAN_BAUD_DEF(CAN100kBaud, CAN_RSJW_1tq, CAN_TBS1_5tq, CAN_TBS2_2tq, 20),
    N32_CAN_BAUD_DEF(CAN50kBaud,  CAN_RSJW_1tq, CAN_TBS1_5tq, CAN_TBS2_2tq, 40),
    N32_CAN_BAUD_DEF(CAN20kBaud,  CAN_RSJW_1tq, CAN_TBS1_5tq, CAN_TBS2_2tq, 100),
    N32_CAN_BAUD_DEF(CAN10kBaud,  CAN_RSJW_1tq, CAN_TBS1_9tq, CAN_TBS2_6tq, 100),
};
#endif /* SOC_N32L40X */

static rt_uint32_t get_can_baud_index(rt_uint32_t baud)
{
    rt_uint32_t len, index;

    len = sizeof(can_baud_rate_tab) / sizeof(can_baud_rate_tab[0]);
    for(index = 0; index < len; index++)
    {
        if (can_baud_rate_tab[index].baud_rate == baud)
            return index;
    }

    return 0; /* default baud is CAN1MBaud */
}

static rt_err_t setfilter(struct n32_can *drv_can)
{
#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
    if (drv_can->CANx == CAN1)
    {
        CAN1_InitFilter(&(drv_can->FilterConfig));
    }
#ifdef CAN2
    else if (drv_can->CANx == CAN2)
    {
        CAN2_InitFilter(&(drv_can->FilterConfig));
    }
#endif
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
    if (drv_can->CANx == CAN)
    {
        CAN_InitFilter(&(drv_can->FilterConfig));
    }
#endif
    else
    {
        rt_kprintf("Can filter config error\n");
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t bxcan_init(struct rt_can_device *can, struct can_configure *cfg)
{
    struct n32_can *drv_can;
    rt_uint32_t baud_index;

    RT_ASSERT(can);
    RT_ASSERT(cfg);
    drv_can = (struct n32_can *)can->parent.user_data;
    RT_ASSERT(drv_can);

    /* Struct init*/
    CAN_InitStruct(&(drv_can->can_init));

    drv_can->can_init.TTCM  = DISABLE;
    drv_can->can_init.ABOM  = DISABLE;
    drv_can->can_init.AWKUM = DISABLE;
    drv_can->can_init.NART  = DISABLE;
    drv_can->can_init.RFLM  = DISABLE;
    drv_can->can_init.TXFP  = ENABLE;

    // Mode
    switch (cfg->mode)
    {
        case RT_CAN_MODE_NORMAL:
                drv_can->can_init.OperatingMode = CAN_Normal_Mode;
                break;

        case RT_CAN_MODE_LISTEN:
                drv_can->can_init.OperatingMode = CAN_Silent_Mode;
                break;

        case RT_CAN_MODE_LOOPBACK:
                drv_can->can_init.OperatingMode = CAN_LoopBack_Mode;
                break;

        case RT_CAN_MODE_LOOPBACKANLISTEN:
                drv_can->can_init.OperatingMode = CAN_Silent_LoopBack_Mode;
                break;

        default:
                drv_can->can_init.OperatingMode = CAN_Normal_Mode;
                break;
    }

    // Baud
    baud_index                          = get_can_baud_index(cfg->baud_rate);
    drv_can->can_init.RSJW              = can_baud_rate_tab[baud_index].RSJW;
    drv_can->can_init.TBS1              = can_baud_rate_tab[baud_index].TBS1;
    drv_can->can_init.TBS2              = can_baud_rate_tab[baud_index].TBS2;
    drv_can->can_init.BaudRatePrescaler = can_baud_rate_tab[baud_index].PRESCALE;

    /* init can */
    if (CAN_Init(drv_can->CANx, &(drv_can->can_init)) != CAN_InitSTS_Success)
    {
        rt_kprintf("Can init error\n");
        return -RT_ERROR;
    }

    /* default filter config */
    setfilter(drv_can);

    return RT_EOK;
}

static rt_err_t configure(struct rt_can_device *can, struct can_configure *cfg)
{
    struct n32_can *drv_can;
    CAN_Module *pbxcan;

    drv_can = (struct n32_can *)can->parent.user_data;
    pbxcan  = drv_can->CANx;

#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
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
#endif

#if defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
    if (pbxcan == CAN)
    {
#ifdef BSP_USING_CAN
    bxcan_hw_init();
    bxcan_init(&drv_can->device, &drv_can->device.config);
#endif
    }
#endif
    return RT_EOK;
}

/**
 * @brief  Configures the NVIC for CAN.
 */
void CAN_NVIC_Config(IRQn_Type IRQn, uint8_t PreemptionPriority, uint8_t SubPriority,FunctionalState cmd)
{
    NVIC_InitType NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    NVIC_InitStructure.NVIC_IRQChannel    = IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = cmd;
    if (cmd)
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
#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
            if (CAN1 == drv_can->CANx)
            {
                NVIC_DisableIRQ(USB_LP_CAN1_RX0_IRQn);
                NVIC_DisableIRQ(CAN1_RX1_IRQn);
            }
#ifdef CAN2
            if (CAN2 == drv_can->CANx)
            {
                NVIC_DisableIRQ(CAN2_RX0_IRQn);
                NVIC_DisableIRQ(CAN2_RX1_IRQn);
            }
#endif
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
            if (CAN == drv_can->CANx)
            {
                NVIC_DisableIRQ(CAN_RX0_IRQn);
                NVIC_DisableIRQ(CAN_RX1_IRQn);
            }
#endif
            CAN_INTConfig(drv_can->CANx, CAN_INT_FMP0, DISABLE); /* DATFIFO 0 message pending Interrupt */
            CAN_INTConfig(drv_can->CANx, CAN_INT_FF0, DISABLE);  /* DATFIFO 0 full Interrupt */
            CAN_INTConfig(drv_can->CANx, CAN_INT_FOV0, DISABLE); /* DATFIFO 0 overrun Interrupt */
            CAN_INTConfig(drv_can->CANx, CAN_INT_FMP1, DISABLE); /* DATFIFO 1 message pending Interrupt */
            CAN_INTConfig(drv_can->CANx, CAN_INT_FF1, DISABLE);  /* DATFIFO 1 full Interrupt */
            CAN_INTConfig(drv_can->CANx, CAN_INT_FOV1, DISABLE); /* DATFIFO 1 overrun Interrupt */
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
#if defined(SOC_N32G45X) || defined(SOC_N32WB452)
            if (CAN1 == drv_can->CANx)
            {
                NVIC_DisableIRQ(USB_HP_CAN1_TX_IRQn);
            }
#ifdef CAN2
            if (CAN2 == drv_can->CANx)
            {
                NVIC_DisableIRQ(CAN2_TX_IRQn);
            }
#endif
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
            if (CAN == drv_can->CANx)
            {
                  NVIC_DisableIRQ(CAN_TX_IRQn);
            }
#endif
            CAN_INTConfig(drv_can->CANx, CAN_INT_TME, DISABLE); /* Transmit mailbox empty Interrupt */
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
            if (CAN1 == drv_can->CANx)
            {
                NVIC_DisableIRQ(CAN1_SCE_IRQn);
            }
#ifdef CAN2
            if (CAN2 == drv_can->CANx)
            {
                NVIC_DisableIRQ(CAN2_SCE_IRQn);
            }
#endif
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
            if (CAN == drv_can->CANx)
            {
                NVIC_DisableIRQ(CAN_SCE_IRQn);
            }
#endif
            CAN_INTConfig(drv_can->CANx, CAN_INT_EWG, DISABLE); /* Error warning Interrupt */
            CAN_INTConfig(drv_can->CANx, CAN_INT_EPV, DISABLE); /* Error passive Interrupt */
            CAN_INTConfig(drv_can->CANx, CAN_INT_BOF, DISABLE); /* Bus-off Interrupt */
            CAN_INTConfig(drv_can->CANx, CAN_INT_LEC, DISABLE); /* Last error code Interrupt */
            CAN_INTConfig(drv_can->CANx, CAN_INT_ERR, DISABLE); /* Error Interrupt */
        }
        break;

        case RT_DEVICE_CTRL_SET_INT:
        argval = (rt_uint32_t) arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            CAN_INTConfig(drv_can->CANx, CAN_INT_FMP0, ENABLE); /* DATFIFO 0 message pending Interrupt */
            CAN_INTConfig(drv_can->CANx, CAN_INT_FF0, ENABLE);  /* DATFIFO 0 full Interrupt */
            CAN_INTConfig(drv_can->CANx, CAN_INT_FOV0, ENABLE); /* DATFIFO 0 overrun Interrupt */
            CAN_INTConfig(drv_can->CANx, CAN_INT_FMP1, ENABLE); /* DATFIFO 1 message pending Interrupt */
            CAN_INTConfig(drv_can->CANx, CAN_INT_FF1, ENABLE);  /* DATFIFO 1 full Interrupt */
            CAN_INTConfig(drv_can->CANx, CAN_INT_FOV1, ENABLE); /* DATFIFO 1 overrun Interrupt */

#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
            if (CAN1 == drv_can->CANx)
            {
                CAN_NVIC_Config(USB_LP_CAN1_RX0_IRQn, 1, 0, ENABLE);
                CAN_NVIC_Config(CAN1_RX1_IRQn, 1, 0, ENABLE);
            }
#ifdef CAN2
            if (CAN2 == drv_can->CANx)
            {
                CAN_NVIC_Config(CAN2_RX0_IRQn, 1, 0, ENABLE);
                CAN_NVIC_Config(CAN2_RX1_IRQn, 1, 0, ENABLE);
            }
#endif
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
            if (CAN == drv_can->CANx)
            {
                CAN_NVIC_Config(CAN_RX0_IRQn, 1, 0, ENABLE);
                CAN_NVIC_Config(CAN_RX1_IRQn, 1, 0, ENABLE);
            }
#endif
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            CAN_INTConfig(drv_can->CANx, CAN_INT_TME, ENABLE); /* Transmit mailbox empty Interrupt */

#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
            if (CAN1 == drv_can->CANx)
            {
                CAN_NVIC_Config(USB_HP_CAN1_TX_IRQn, 1, 0, ENABLE);
            }
#ifdef CAN2
            if (CAN2 == drv_can->CANx)
            {
                CAN_NVIC_Config(CAN2_TX_IRQn, 1, 0, ENABLE);
            }
#endif
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
            if (CAN == drv_can->CANx)
            {
                CAN_NVIC_Config(CAN_TX_IRQn, 1, 0, ENABLE);
            }
#endif
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            CAN_INTConfig(drv_can->CANx, CAN_INT_EWG, ENABLE); /* Error warning Interrupt */
            CAN_INTConfig(drv_can->CANx, CAN_INT_EPV, ENABLE); /* Error passive Interrupt */
            CAN_INTConfig(drv_can->CANx, CAN_INT_BOF, ENABLE); /* Bus-off Interrupt */
            CAN_INTConfig(drv_can->CANx, CAN_INT_LEC, ENABLE); /* Last error code Interrupt */
            CAN_INTConfig(drv_can->CANx, CAN_INT_ERR, ENABLE); /* Error Interrupt */

#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
            if (CAN1 == drv_can->CANx)
            {
                CAN_NVIC_Config(CAN1_SCE_IRQn, 1, 0, ENABLE);
            }
#ifdef CAN2
            if (CAN2 == drv_can->CANx)
            {
                CAN_NVIC_Config(CAN2_SCE_IRQn, 1, 0, ENABLE);
            }
#endif
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
            if (CAN == drv_can->CANx)
            {
                CAN_NVIC_Config(CAN_SCE_IRQn, 1, 0, ENABLE);
            }
#endif
        }
        break;

        case RT_CAN_CMD_SET_FILTER:
        {
            rt_uint32_t id_h        = 0;
            rt_uint32_t id_l        = 0;
            rt_uint32_t mask_h      = 0;
            rt_uint32_t mask_l      = 0;
            rt_uint32_t mask_l_tail = 0;  //CAN_FxR2 bit [2:0]

            if (RT_NULL == arg)
            {
                /* Default filter config */
                setfilter(drv_can);
            }
            else
            {
                filter_cfg = (struct rt_can_filter_config *)arg;
                /* Get default filter */
                for(int i = 0; i < filter_cfg->count; i++)
                {
                    if (filter_cfg->items[i].hdr_bank == -1)
                    {
                        /* Can banks 0~13 */
                        drv_can->FilterConfig.Filter_Num = i;
                    }
                    else
                    {
                        /* Use user-defined filter bank settings */
                        drv_can->FilterConfig.Filter_Num = filter_cfg->items[i].hdr_bank;
                    }

                    /* Filter groups work in identifier masking bit mode */
                    if (filter_cfg->items[i].mode == CAN_Filter_IdMaskMode)
                    {
                        /* make sure the IDE and RTR work */
                        mask_l_tail = 0x06;
                        drv_can->FilterConfig.Filter_Mode = CAN_Filter_IdMaskMode;
                    }
                    /* Filter groups work in identifier list mode */
                    else if (filter_cfg->items[i].mode == CAN_Filter_IdListMode)
                    {
                        mask_l_tail = (filter_cfg->items[i].ide << 2) | (filter_cfg->items[i].rtr << 1);
                        drv_can->FilterConfig.Filter_Mode = CAN_Filter_IdListMode;
                    }

                    if (filter_cfg->items[i].ide == RT_CAN_STDID)
                    {
                        id_h   = ((filter_cfg->items[i].id << 18) >> 13) & 0xFFFF;
                        id_l   = ((filter_cfg->items[i].id << 18) |
                                (filter_cfg->items[i].ide << 2) |
                                (filter_cfg->items[i].rtr << 1)) & 0xFFFF;
                        mask_h = ((filter_cfg->items[i].mask << 21) >> 16) & 0xFFFF;
                        mask_l = ((filter_cfg->items[i].mask << 21) | mask_l_tail) & 0xFFFF;
                    }
                    else if (filter_cfg->items[i].ide == RT_CAN_EXTID)
                    {
                        id_h   = (filter_cfg->items[i].id >> 13) & 0xFFFF;
                        id_l   = ((filter_cfg->items[i].id << 3)  |
                                    (filter_cfg->items[i].ide << 2) |
                                    (filter_cfg->items[i].rtr << 1)) & 0xFFFF;
                        mask_h = ((filter_cfg->items[i].mask << 3) >> 16) & 0xFFFF;
                        mask_l = ((filter_cfg->items[i].mask << 3) | mask_l_tail) & 0xFFFF;
                    }

                    drv_can->FilterConfig.Filter_HighId         = id_h;
                    drv_can->FilterConfig.Filter_LowId          = id_l;
                    drv_can->FilterConfig.FilterMask_HighId     = mask_h;
                    drv_can->FilterConfig.FilterMask_LowId      = mask_l;
                    drv_can->FilterConfig.Filter_FIFOAssignment = CAN_FIFO0;
                    drv_can->FilterConfig.Filter_Scale          = CAN_Filter_32bitScale;
                    drv_can->FilterConfig.Filter_Act            = ENABLE;

                    /* Filter conf */
                    setfilter(drv_can);
                }
            }
            break;
        }

        case RT_CAN_CMD_SET_MODE:
            argval = (rt_uint32_t) arg;
            if (argval != RT_CAN_MODE_NORMAL &&
                argval != RT_CAN_MODE_LISTEN &&
                argval != RT_CAN_MODE_LOOPBACK &&
                argval != RT_CAN_MODE_LOOPBACKANLISTEN)
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
                argval != CAN800kBaud &&
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
            errtype = drv_can->CANx->ESTS;
            drv_can->device.status.rcverrcnt   = errtype >> 24;
            drv_can->device.status.snderrcnt   = (errtype >> 16 & 0xFF);
            drv_can->device.status.lasterrtype = errtype & 0x70;
            drv_can->device.status.errcode     = errtype & 0x07;

            rt_memcpy(arg, &drv_can->device.status, sizeof(drv_can->device.status));
        }
        break;
    }
  return RT_EOK;
}

/* CAN Mailbox Transmit Request */
#define TMIDxR_TXRQ ((uint32_t)0x00000001)

static int can_sendmsg_rtmsg(CAN_Module *CANx, struct rt_can_msg *pmsg, uint32_t mailbox_index)
{
    CanTxMessage CAN_TxMessage = {0};
    CanTxMessage *TxMessage = &CAN_TxMessage;

    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));

    if (RT_CAN_STDID == pmsg->ide)
    {
        TxMessage->IDE = CAN_Standard_Id;
        RT_ASSERT(IS_CAN_STDID(pmsg->id));
        TxMessage->StdId = pmsg->id;
    }
    else
    {
        TxMessage->IDE = CAN_Extended_Id;
        RT_ASSERT(IS_CAN_EXTID(pmsg->id));
        TxMessage->ExtId = pmsg->id;
    }

    if (RT_CAN_DTR == pmsg->rtr)
    {
        TxMessage->RTR = CAN_RTRQ_DATA;
    }
    else
    {
        TxMessage->RTR = CAN_RTRQ_REMOTE;
    }

    if (mailbox_index != CAN_TxSTS_NoMailBox)
    {
        /* Set up the Id */
        CANx->sTxMailBox[mailbox_index].TMI &= TMIDxR_TXRQ;
        if (TxMessage->IDE == CAN_Standard_Id)
        {
            assert_param(IS_CAN_STDID(TxMessage->StdId));
            CANx->sTxMailBox[mailbox_index].TMI |= ((TxMessage->StdId << 21) | TxMessage->RTR);
        }
        else
        {
            assert_param(IS_CAN_EXTID(TxMessage->ExtId));
            CANx->sTxMailBox[mailbox_index].TMI |= ((TxMessage->ExtId << 3) | TxMessage->IDE | TxMessage->RTR);
        }

        /* Set up the DLC */
        TxMessage->DLC = pmsg->len & 0x0FU;
        CANx->sTxMailBox[mailbox_index].TMDT &= (uint32_t)0xFFFFFFF0;
        CANx->sTxMailBox[mailbox_index].TMDT |= TxMessage->DLC;

        /* Set up the data field */
        CANx->sTxMailBox[mailbox_index].TMDH = (((uint32_t)pmsg->data[7] << 24) |
                                                ((uint32_t)pmsg->data[6] << 16) |
                                                ((uint32_t)pmsg->data[5] << 8)  |
                                                ((uint32_t)pmsg->data[4]));
        CANx->sTxMailBox[mailbox_index].TMDL = (((uint32_t)pmsg->data[3] << 24) |
                                                ((uint32_t)pmsg->data[2] << 16) |
                                                ((uint32_t)pmsg->data[1] << 8)  |
                                                ((uint32_t)pmsg->data[0]));
        /* Request transmission */
        CANx->sTxMailBox[mailbox_index].TMI |= TMIDxR_TXRQ;

        return RT_EOK;
    }
    return -RT_ERROR;
}

static int sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t box_num)
{
    struct n32_can *drv_can;

    RT_ASSERT(can != RT_NULL);
    RT_ASSERT(buf != RT_NULL);
    drv_can = (struct n32_can *)can->parent.user_data;
    RT_ASSERT(drv_can != RT_NULL);

    /* Select one empty transmit mailbox */
    switch (box_num)
    {
        case 0:
            if ((drv_can->CANx->TSTS & CAN_TSTS_TMEM0) != CAN_TSTS_TMEM0)
            {
                    /* Return function status */
                    return -RT_ERROR;
            }
            break;
        case 1:
            if ((drv_can->CANx->TSTS & CAN_TSTS_TMEM1) != CAN_TSTS_TMEM1)
            {
                    /* Return function status */
                    return -RT_ERROR;
            }
            break;
        case 2:
            if ((drv_can->CANx->TSTS & CAN_TSTS_TMEM2) != CAN_TSTS_TMEM2)
            {
                    /* Return function status */
                    return -RT_ERROR;
            }
            break;
        default:
            RT_ASSERT(0);
            break;
    }

    // Start send msg
    return can_sendmsg_rtmsg(drv_can->CANx, ((struct rt_can_msg *)buf), box_num);
}

static int can_recvmsg_rtmsg(CAN_Module *CANx, struct rt_can_msg *pmsg, uint32_t FIFONum)
{
    CanRxMessage CAN_RxMessage = {0};
    CanRxMessage *RxMessage = &CAN_RxMessage;

    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_FIFO(FIFONum));

    /* Check the Rx FIFO */
    if (FIFONum == CAN_FIFO0) /* Rx element is assigned to Rx FIFO 0 */
    {
        /* Check that the Rx FIFO 0 is not empty */
        if ((CANx->RFF0 & CAN_RFF0_FFMP0) == 0U)
        {
            return -RT_ERROR;
        }
    }
    else /* Rx element is assigned to Rx FIFO 1 */
    {
        /* Check that the Rx FIFO 1 is not empty */
        if ((CANx->RFF1 & CAN_RFF1_FFMP1) == 0U)
        {
            return -RT_ERROR;
        }
    }

    /* Get the Id */
    RxMessage->IDE = (uint8_t)0x04 & CANx->sFIFOMailBox[FIFONum].RMI;
    if (RxMessage->IDE == CAN_Standard_Id)
    {
        RxMessage->StdId = (uint32_t)0x000007FF & (CANx->sFIFOMailBox[FIFONum].RMI >> 21);
    }
    else
    {
        RxMessage->ExtId = (uint32_t)0x1FFFFFFF & (CANx->sFIFOMailBox[FIFONum].RMI >> 3);
    }

    RxMessage->RTR = (uint8_t)0x02 & CANx->sFIFOMailBox[FIFONum].RMI;
    /* Get the DLC */
    RxMessage->DLC = (uint8_t)0x0F & CANx->sFIFOMailBox[FIFONum].RMDT;
    /* Get the FMI */
    RxMessage->FMI = (uint8_t)0xFF & (CANx->sFIFOMailBox[FIFONum].RMDT >> 8);

    /* Get the data field */
    pmsg->data[0] = (uint8_t)0xFF & CANx->sFIFOMailBox[FIFONum].RMDL;
    pmsg->data[1] = (uint8_t)0xFF & (CANx->sFIFOMailBox[FIFONum].RMDL >> 8);
    pmsg->data[2] = (uint8_t)0xFF & (CANx->sFIFOMailBox[FIFONum].RMDL >> 16);
    pmsg->data[3] = (uint8_t)0xFF & (CANx->sFIFOMailBox[FIFONum].RMDL >> 24);
    pmsg->data[4] = (uint8_t)0xFF & CANx->sFIFOMailBox[FIFONum].RMDH;
    pmsg->data[5] = (uint8_t)0xFF & (CANx->sFIFOMailBox[FIFONum].RMDH >> 8);
    pmsg->data[6] = (uint8_t)0xFF & (CANx->sFIFOMailBox[FIFONum].RMDH >> 16);
    pmsg->data[7] = (uint8_t)0xFF & (CANx->sFIFOMailBox[FIFONum].RMDH >> 24);

    /* get len */
    pmsg->len = RxMessage->DLC;

    /* get id */
    if (RxMessage->IDE == CAN_Standard_Id)
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
    if (CAN_RTRQ_Data == RxMessage->RTR)
    {
        pmsg->rtr = RT_CAN_DTR;
    }
    else
    {
        pmsg->rtr = RT_CAN_RTR;
    }

    /* get hdr_index */
#if defined(SOC_N32G45X) || defined(SOC_N32WB452)
    if (CANx == CAN1)
    {
        pmsg->hdr_index = (RxMessage->FMI + 1) >> 1;
    }
#ifdef CAN2
    else if (CANx == CAN2)
    {
        pmsg->hdr_index = (RxMessage->FMI + 1) >> 1;
    }
#endif
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
    if (CANx == CAN)
    {
        pmsg->hdr_index = (RxMessage->FMI + 1) >> 1;
    }
#endif

    /* Release the DATFIFO */
    /* Release FIFO0 */
    if (FIFONum == CAN_FIFO0)
    {
        CANx->RFF0 |= CAN_RFF0_RFFOM0;
    }
    /* Release FIFO1 */
    else /* FIFONum == CAN_FIFO1 */
    {
        CANx->RFF1 |= CAN_RFF1_RFFOM1;
    }
    return RT_EOK;
}

static int recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t fifo)
{
    struct n32_can *drv_can;

    RT_ASSERT(can != RT_NULL);
    RT_ASSERT(buf != RT_NULL);
    drv_can = (struct n32_can *)can->parent.user_data;
    RT_ASSERT(drv_can != RT_NULL);

    /* Get data */
    return can_recvmsg_rtmsg(drv_can->CANx, ((struct rt_can_msg *)buf), fifo);
}

static const struct rt_can_ops canops =
{
    configure,
    control,
    sendmsg,
    recvmsg,
};

static void can_rx_isr(struct rt_can_device *can, rt_uint32_t fifo)
{
    struct n32_can *drv_can;
    RT_ASSERT(can != RT_NULL);
    drv_can = (struct n32_can *)can->parent.user_data;
    RT_ASSERT(drv_can != RT_NULL);

    switch (fifo)
    {
        case CAN_FIFO0:
            /* save to user list */
            if (CAN_GetFlagSTS(drv_can->CANx, CAN_FLAG_FFMP0) && CAN_PendingMessage(drv_can->CANx, CAN_FIFO0))
            {
                    rt_hw_can_isr(can, RT_CAN_EVENT_RX_IND | fifo << 8);
            }
            /* Check FULL flag for FIFO0 */
            if (CAN_GetFlagSTS(drv_can->CANx, CAN_FLAG_FFULL0))
            {
                    /* Clear FIFO0 FULL Flag */
                    CAN_ClearFlag(drv_can->CANx, CAN_FLAG_FFULL0);
            }
            /* Check Overrun flag for FIFO0 */
            if (CAN_GetFlagSTS(drv_can->CANx, CAN_FLAG_FFOVR0))
            {
                    /* Clear FIFO0 Overrun Flag */
                    CAN_ClearFlag(drv_can->CANx, CAN_FLAG_FFOVR0);
                    rt_hw_can_isr(can, RT_CAN_EVENT_RXOF_IND | fifo << 8);
            }
            break;

        case CAN_FIFO1:
            /* save to user list */
            if (CAN_GetFlagSTS(drv_can->CANx, CAN_FLAG_FFMP1) && CAN_PendingMessage(drv_can->CANx, CAN_FIFO1))
            {
                    rt_hw_can_isr(can, RT_CAN_EVENT_RX_IND | fifo << 8);
            }
            /* Check FULL flag for FIFO1 */
            if (CAN_GetFlagSTS(drv_can->CANx, CAN_FLAG_FFULL1))
            {
                    /* Clear FIFO1 FULL Flag */
                    CAN_ClearFlag(drv_can->CANx, CAN_FLAG_FFULL1);
            }
            /* Check Overrun flag for FIFO1 */
            if (CAN_GetFlagSTS(drv_can->CANx, CAN_FLAG_FFOVR1))
            {
                    /* Clear FIFO1 Overrun Flag */
                    CAN_ClearFlag(drv_can->CANx, CAN_FLAG_FFOVR1);
                    rt_hw_can_isr(can, RT_CAN_EVENT_RXOF_IND | fifo << 8);
            }
            break;
    }
}

#ifdef BSP_USING_CAN1
void USB_HP_CAN1_TX_IRQHandler(void)
{
    rt_interrupt_enter();

    if (CAN_GetFlagSTS(drv_can1.CANx, CAN_FLAG_RQCPM0))
    {
        rt_hw_can_isr(&drv_can1.device, RT_CAN_EVENT_TX_DONE | (0x00 << 8));
        CAN_ClearFlag(drv_can1.CANx, CAN_FLAG_RQCPM0);
    }
    if (CAN_GetFlagSTS(drv_can1.CANx, CAN_FLAG_RQCPM1))
    {
        rt_hw_can_isr(&drv_can1.device, RT_CAN_EVENT_TX_DONE | (0x01 << 8));
        CAN_ClearFlag(drv_can1.CANx, CAN_FLAG_RQCPM1);
    }
    if (CAN_GetFlagSTS(drv_can1.CANx, CAN_FLAG_RQCPM2))
    {
        rt_hw_can_isr(&drv_can1.device, RT_CAN_EVENT_TX_DONE | (0x02 << 8));
        CAN_ClearFlag(drv_can1.CANx, CAN_FLAG_RQCPM2);
    }
    rt_interrupt_leave();
}

void USB_LP_CAN1_RX0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    can_rx_isr(&drv_can1.device, CAN_FIFO0);

    /* leave interrupt */
    rt_interrupt_leave();
}

void CAN1_RX1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    can_rx_isr(&drv_can1.device, CAN_FIFO1);

    /* leave interrupt */
    rt_interrupt_leave();
}

void CAN1_SCE_IRQHandler(void)
{
    uint32_t errtype;
    rt_interrupt_enter();

    if (CAN_GetIntStatus(drv_can1.CANx, CAN_INT_ERR))
    {
        errtype = drv_can1.CANx->ESTS;
        /* ESTS -> LEC */
        switch ((errtype & 0x70) >> 4)
        {
        case RT_CAN_BUS_BIT_PAD_ERR:
            break;

        case RT_CAN_BUS_FORMAT_ERR:
            drv_can1.device.status.formaterrcnt++;
            break;

        case RT_CAN_BUS_ACK_ERR:
            drv_can1.device.status.ackerrcnt++;
            if (!READ_BIT(drv_can1.CANx->TSTS, CAN_TSTS_TXOKM0))
            {
                rt_hw_can_isr(&drv_can1.device, RT_CAN_EVENT_TX_FAIL | 0 << 8);
            }
            else if (!READ_BIT(drv_can1.CANx->TSTS, CAN_TSTS_TXOKM1))
            {
                rt_hw_can_isr(&drv_can1.device, RT_CAN_EVENT_TX_FAIL | 1 << 8);
            }
            else if (!READ_BIT(drv_can1.CANx->TSTS, CAN_TSTS_TXOKM2))
            {
                rt_hw_can_isr(&drv_can1.device, RT_CAN_EVENT_TX_FAIL | 2 << 8);
            }
            break;

        case RT_CAN_BUS_IMPLICIT_BIT_ERR:
        case RT_CAN_BUS_EXPLICIT_BIT_ERR:
            drv_can1.device.status.biterrcnt++;
            break;

        case RT_CAN_BUS_CRC_ERR:
            drv_can1.device.status.crcerrcnt++;
            break;
        }

        drv_can1.device.status.lasterrtype = errtype & 0x70;
        drv_can1.device.status.rcverrcnt   = errtype >> 24;
        drv_can1.device.status.snderrcnt   = (errtype >> 16 & 0xFF);
        drv_can1.device.status.errcode     = errtype & 0x07;

        CAN_ClearINTPendingBit(drv_can1.CANx, CAN_INT_ERR);
    }
    rt_interrupt_leave();
}
#endif /*BSP_USING_CAN1*/

#ifdef BSP_USING_CAN2
void CAN2_TX_IRQHandler(void)
{
    rt_interrupt_enter();
    if (CAN_GetFlagSTS(drv_can2.CANx, CAN_FLAG_RQCPM0))
    {
        CAN_ClearFlag(drv_can2.CANx, CAN_FLAG_RQCPM0);
        rt_hw_can_isr(&drv_can2.device, RT_CAN_EVENT_TX_DONE | (0x00 << 8));
    }
    if (CAN_GetFlagSTS(drv_can2.CANx, CAN_FLAG_RQCPM1))
    {
        CAN_ClearFlag(drv_can2.CANx, CAN_FLAG_RQCPM1);
        rt_hw_can_isr(&drv_can2.device, RT_CAN_EVENT_TX_DONE | (0x01 << 8));
    }
    if (CAN_GetFlagSTS(drv_can2.CANx, CAN_FLAG_RQCPM2))
    {
        CAN_ClearFlag(drv_can2.CANx, CAN_FLAG_RQCPM2);
        rt_hw_can_isr(&drv_can2.device, RT_CAN_EVENT_TX_DONE | (0x02 << 8));
    }
    rt_interrupt_leave();
}

void CAN2_RX0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    can_rx_isr(&drv_can2.device, CAN_FIFO0);

    /* leave interrupt */
    rt_interrupt_leave();
}

void CAN2_RX1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    can_rx_isr(&drv_can2.device, CAN_FIFO1);

    /* leave interrupt */
    rt_interrupt_leave();
}

void CAN2_SCE_IRQHandler(void)
{
    uint32_t errtype;
    rt_interrupt_enter();

    if (CAN_GetIntStatus(drv_can2.CANx, CAN_INT_ERR))
    {
        errtype = drv_can2.CANx->ESTS;
        /* ESTS -> LEC */
        switch ((errtype & 0x70) >> 4)
        {
            case RT_CAN_BUS_BIT_PAD_ERR:
                break;

            case RT_CAN_BUS_FORMAT_ERR:
                drv_can2.device.status.formaterrcnt++;
                break;

            case RT_CAN_BUS_ACK_ERR:
                drv_can2.device.status.ackerrcnt++;
                if (!READ_BIT(drv_can2.CANx->TSTS, CAN_TSTS_TXOKM0))
                {
                    rt_hw_can_isr(&drv_can2.device, RT_CAN_EVENT_TX_FAIL | 0 << 8);
                }
                else if (!READ_BIT(drv_can2.CANx->TSTS, CAN_TSTS_TXOKM1))
                {
                    rt_hw_can_isr(&drv_can2.device, RT_CAN_EVENT_TX_FAIL | 1 << 8);
                }
                else if (!READ_BIT(drv_can2.CANx->TSTS, CAN_TSTS_TXOKM2))
                {
                    rt_hw_can_isr(&drv_can2.device, RT_CAN_EVENT_TX_FAIL | 2 << 8);
                }
                break;

            case RT_CAN_BUS_IMPLICIT_BIT_ERR:
            case RT_CAN_BUS_EXPLICIT_BIT_ERR:
                drv_can2.device.status.biterrcnt++;
                break;

            case RT_CAN_BUS_CRC_ERR:
                drv_can2.device.status.crcerrcnt++;
                break;
        }

        drv_can2.device.status.lasterrtype = errtype & 0x70;
        drv_can2.device.status.rcverrcnt   = errtype >> 24;
        drv_can2.device.status.snderrcnt   = (errtype >> 16 & 0xFF);
        drv_can2.device.status.errcode     = errtype & 0x07;

        CAN_ClearINTPendingBit(drv_can2.CANx, CAN_INT_ERR);
    }
    rt_interrupt_leave();
}
#endif /* BSP_USING_CAN2 */

#if defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
#ifdef BSP_USING_CAN
void CAN_TX_IRQHandler(void)
{
    rt_interrupt_enter();
    if (CAN_GetFlagSTS(drv_can.CANx, CAN_FLAG_RQCPM0))
    {
        CAN_ClearFlag(drv_can.CANx, CAN_FLAG_RQCPM0);
        rt_hw_can_isr(&drv_can.device, RT_CAN_EVENT_TX_DONE | (0x00 << 8));
    }
    if (CAN_GetFlagSTS(drv_can.CANx, CAN_FLAG_RQCPM1))
    {
        CAN_ClearFlag(drv_can.CANx, CAN_FLAG_RQCPM1);
        rt_hw_can_isr(&drv_can.device, RT_CAN_EVENT_TX_DONE | (0x01 << 8));
    }
    if (CAN_GetFlagSTS(drv_can.CANx, CAN_FLAG_RQCPM2))
    {
        CAN_ClearFlag(drv_can.CANx, CAN_FLAG_RQCPM2);
        rt_hw_can_isr(&drv_can.device, RT_CAN_EVENT_TX_DONE | (0x02 << 8));
    }
    rt_interrupt_leave();
}

void CAN_RX0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    can_rx_isr(&drv_can.device, CAN_FIFO0);

    /* leave interrupt */
    rt_interrupt_leave();
}

void CAN_RX1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    can_rx_isr(&drv_can.device, CAN_FIFO1);

    /* leave interrupt */
    rt_interrupt_leave();
}

void CAN_SCE_IRQHandler(void)
{
    uint32_t errtype;
    rt_interrupt_enter();

    if (CAN_GetIntStatus(drv_can.CANx, CAN_INT_ERR))
    {
        errtype = drv_can.CANx->ESTS;
        /* ESTS -> LEC */
        switch ((errtype & 0x70) >> 4)
        {
            case RT_CAN_BUS_BIT_PAD_ERR:
                break;

            case RT_CAN_BUS_FORMAT_ERR:
                drv_can.device.status.formaterrcnt++;
                break;

            case RT_CAN_BUS_ACK_ERR:
                drv_can.device.status.ackerrcnt++;
                if (!READ_BIT(drv_can.CANx->TSTS, CAN_TSTS_TXOKM0))
                {
                    rt_hw_can_isr(&drv_can.device, RT_CAN_EVENT_TX_FAIL | 0 << 8);
                }
                else if (!READ_BIT(drv_can.CANx->TSTS, CAN_TSTS_TXOKM1))
                {
                    rt_hw_can_isr(&drv_can.device, RT_CAN_EVENT_TX_FAIL | 1 << 8);
                }
                else if (!READ_BIT(drv_can.CANx->TSTS, CAN_TSTS_TXOKM2))
                {
                    rt_hw_can_isr(&drv_can.device, RT_CAN_EVENT_TX_FAIL | 2 << 8);
                }
                break;

            case RT_CAN_BUS_IMPLICIT_BIT_ERR:
            case RT_CAN_BUS_EXPLICIT_BIT_ERR:
                drv_can.device.status.biterrcnt++;
                break;

            case RT_CAN_BUS_CRC_ERR:
                drv_can.device.status.crcerrcnt++;
                break;
        }

        drv_can.device.status.lasterrtype = errtype & 0x70;
        drv_can.device.status.rcverrcnt   = errtype >> 24;
        drv_can.device.status.snderrcnt   = (errtype >> 16 & 0xFF);
        drv_can.device.status.errcode     = errtype & 0x07;

        CAN_ClearINTPendingBit(drv_can.CANx, CAN_INT_ERR);
    }
    rt_interrupt_leave();
}
#endif /* BSP_USING_CAN */
#endif

int rt_hw_can_init(void)
{
    struct can_configure config = CANDEFAULTCONFIG;
    config.privmode = RT_CAN_MODE_NOPRIV;
    config.ticks = 50;

#ifdef RT_CAN_USING_HDR
    config.maxhdr = 14;
#endif

#ifdef BSP_USING_CAN1
    /* config default filter */
    drv_can1.FilterConfig.Filter_Num            = 0;
    drv_can1.FilterConfig.Filter_Mode           = CAN_Filter_IdMaskMode;
    drv_can1.FilterConfig.Filter_Scale          = CAN_Filter_32bitScale;
    drv_can1.FilterConfig.Filter_HighId         = 0x0000;
    drv_can1.FilterConfig.Filter_LowId          = 0x0000;
    drv_can1.FilterConfig.FilterMask_HighId     = 0;
    drv_can1.FilterConfig.FilterMask_LowId      = 0;
    drv_can1.FilterConfig.Filter_FIFOAssignment = CAN_FIFO0; // CAN_FIFO1 CAN_FIFO0
    drv_can1.FilterConfig.Filter_Act            = ENABLE;

    drv_can1.device.config = config;
    /* register CAN1 device */
    rt_hw_can_register(&drv_can1.device, drv_can1.name, &canops, &drv_can1);
#endif /* BSP_USING_CAN1 */

#ifdef BSP_USING_CAN2
    /* config default filter */
    drv_can2.FilterConfig.Filter_Num            = 0;
    drv_can2.FilterConfig.Filter_Mode           = CAN_Filter_IdMaskMode;
    drv_can2.FilterConfig.Filter_Scale          = CAN_Filter_32bitScale;
    drv_can2.FilterConfig.Filter_HighId         = 0x0000;
    drv_can2.FilterConfig.Filter_LowId          = 0x0000;
    drv_can2.FilterConfig.FilterMask_HighId     = 0;
    drv_can2.FilterConfig.FilterMask_LowId      = 0;
    drv_can2.FilterConfig.Filter_FIFOAssignment = CAN_FIFO0;
    drv_can2.FilterConfig.Filter_Act            = ENABLE;

    drv_can2.device.config = config;
    /* register CAN2 device */
    rt_hw_can_register(&drv_can2.device, drv_can2.name, &canops, &drv_can2);
#endif /* BSP_USING_CAN2 */

#if defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
#ifdef BSP_USING_CAN
    /* config default filter */
    drv_can.FilterConfig.Filter_Num            = 0;
    drv_can.FilterConfig.Filter_Mode           = CAN_Filter_IdMaskMode;
    drv_can.FilterConfig.Filter_Scale          = CAN_Filter_32bitScale;
    drv_can.FilterConfig.Filter_HighId         = 0x0000;
    drv_can.FilterConfig.Filter_LowId          = 0x0000;
    drv_can.FilterConfig.FilterMask_HighId     = 0;
    drv_can.FilterConfig.FilterMask_LowId      = 0;
    drv_can.FilterConfig.Filter_FIFOAssignment = CAN_FIFO0;
    drv_can.FilterConfig.Filter_Act            = ENABLE;

    drv_can.device.config = config;
    /* register CAN2 device */
    rt_hw_can_register(&drv_can.device, drv_can.name, &canops, &drv_can);
#endif /* BSP_USING_CAN2 */
#endif

    return 0;
}

INIT_BOARD_EXPORT(rt_hw_can_init);

#endif /* defined(BSP_USING_CAN1) || defined(BSP_USING_CAN2) */
#endif /*RT_USING_CAN*/
