/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-16     shelton      first version
 * 2023-01-31     shelton      add support f425
 * 2023-04-08     shelton      add support f423
 * 2023-10-18     shelton      add support f402/f405
 * 2024-04-12     shelton      add support a403a and a423
 */

#include "drv_can.h"

#ifdef BSP_USING_CAN

#define LOG_TAG    "drv_can"
#include <drv_log.h>

#ifdef SOC_SERIES_AT32A403A
/* attention !!! baud calculation example: apbclk / ((ss + bs1 + bs2) * brp), ep: 96 / ((1 + 8 + 3) * 8) = 1MHz*/
/* attention !!! default apbclk 96 mhz */
static const struct at32_baud_rate can_baud_rate_tab[] =
{
    {CAN1MBaud,   {8 ,  CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN800kBaud, {20,  CAN_RSAW_1TQ, CAN_BTS1_3TQ,  CAN_BTS2_2TQ}},
    {CAN500kBaud, {16,  CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN250kBaud, {32,  CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN125kBaud, {64,  CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN100kBaud, {160, CAN_RSAW_1TQ, CAN_BTS1_3TQ,  CAN_BTS2_2TQ}},
    {CAN50kBaud,  {320, CAN_RSAW_1TQ, CAN_BTS1_3TQ,  CAN_BTS2_2TQ}},
    {CAN20kBaud,  {800, CAN_RSAW_1TQ, CAN_BTS1_3TQ,  CAN_BTS2_2TQ}},
    {CAN10kBaud,  {800, CAN_RSAW_1TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
};
#endif
#ifdef SOC_SERIES_AT32A423
/* attention !!! baud calculation example: apbclk / ((ss + bs1 + bs2) * brp), ep: 72 / ((1 + 8 + 3) * 10) = 1MHz*/
/* attention !!! default apbclk 72 mhz */
static const struct at32_baud_rate can_baud_rate_tab[] =
{
    {CAN1MBaud,   {6 ,  CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN800kBaud, {10 , CAN_RSAW_2TQ, CAN_BTS1_6TQ,  CAN_BTS2_2TQ}},
    {CAN500kBaud, {12 , CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN250kBaud, {24 , CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN125kBaud, {48 , CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN100kBaud, {60 , CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN50kBaud,  {120, CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN20kBaud,  {300, CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN10kBaud,  {600, CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}}
};
#endif
#ifdef SOC_SERIES_AT32F402
/* attention !!! baud calculation example: apbclk / ((ss + bs1 + bs2) * brp), ep: 108 / ((1 + 8 + 3) * 9) = 1MHz*/
/* attention !!! default apbclk 108 mhz */
static const struct at32_baud_rate can_baud_rate_tab[] =
{
    {CAN1MBaud,   {9 ,  CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN800kBaud, {15 , CAN_RSAW_2TQ, CAN_BTS1_6TQ,  CAN_BTS2_2TQ}},
    {CAN500kBaud, {18 , CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN250kBaud, {36 , CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN125kBaud, {72 , CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN100kBaud, {90 , CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN50kBaud,  {180, CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN20kBaud,  {450, CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN10kBaud,  {900, CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}}
};
#endif
#ifdef SOC_SERIES_AT32F403A
/* attention !!! baud calculation example: apbclk / ((ss + bs1 + bs2) * brp), ep: 120 / ((1 + 8 + 3) * 10) = 1MHz*/
/* attention !!! default apbclk 120 mhz */
static const struct at32_baud_rate can_baud_rate_tab[] =
{
    {CAN1MBaud,   {10 , CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN800kBaud, {15 , CAN_RSAW_2TQ, CAN_BTS1_7TQ,  CAN_BTS2_2TQ}},
    {CAN500kBaud, {20 , CAN_RSAW_2TQ, CAN_BTS1_9TQ,  CAN_BTS2_2TQ}},
    {CAN250kBaud, {40 , CAN_RSAW_2TQ, CAN_BTS1_9TQ,  CAN_BTS2_2TQ}},
    {CAN125kBaud, {80 , CAN_RSAW_2TQ, CAN_BTS1_9TQ,  CAN_BTS2_2TQ}},
    {CAN100kBaud, {75 , CAN_RSAW_2TQ, CAN_BTS1_13TQ, CAN_BTS2_2TQ}},
    {CAN50kBaud,  {150, CAN_RSAW_2TQ, CAN_BTS1_13TQ, CAN_BTS2_2TQ}},
    {CAN20kBaud,  {375, CAN_RSAW_2TQ, CAN_BTS1_13TQ, CAN_BTS2_2TQ}},
    {CAN10kBaud,  {750, CAN_RSAW_2TQ, CAN_BTS1_13TQ, CAN_BTS2_2TQ}}
};
#endif
#ifdef SOC_SERIES_AT32F405
/* attention !!! baud calculation example: apbclk / ((ss + bs1 + bs2) * brp), ep: 108 / ((1 + 8 + 3) * 9) = 1MHz*/
/* attention !!! default apbclk 108 mhz */
static const struct at32_baud_rate can_baud_rate_tab[] =
{
    {CAN1MBaud,   {9 ,  CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN800kBaud, {15 , CAN_RSAW_2TQ, CAN_BTS1_6TQ,  CAN_BTS2_2TQ}},
    {CAN500kBaud, {18 , CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN250kBaud, {36 , CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN125kBaud, {72 , CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN100kBaud, {90 , CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN50kBaud,  {180, CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN20kBaud,  {450, CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN10kBaud,  {900, CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}}
};
#endif
#ifdef SOC_SERIES_AT32F407
/* attention !!! baud calculation example: apbclk / ((ss + bs1 + bs2) * brp), ep: 100 / ((1 + 7 + 2) * 10) = 1MHz*/
/* attention !!! default apbclk 100 mhz */
static const struct at32_baud_rate can_baud_rate_tab[] =
{
    {CAN1MBaud,   {10 , CAN_RSAW_3TQ, CAN_BTS1_7TQ,  CAN_BTS2_2TQ}},
    {CAN800kBaud, {25,  CAN_RSAW_1TQ, CAN_BTS1_3TQ,  CAN_BTS2_1TQ}},
    {CAN500kBaud, {10,  CAN_RSAW_3TQ, CAN_BTS1_16TQ, CAN_BTS2_3TQ}},
    {CAN250kBaud, {20,  CAN_RSAW_3TQ, CAN_BTS1_16TQ, CAN_BTS2_3TQ}},
    {CAN125kBaud, {40,  CAN_RSAW_3TQ, CAN_BTS1_16TQ, CAN_BTS2_3TQ}},
    {CAN100kBaud, {50,  CAN_RSAW_3TQ, CAN_BTS1_16TQ, CAN_BTS2_3TQ}},
    {CAN50kBaud,  {100, CAN_RSAW_2TQ, CAN_BTS1_16TQ, CAN_BTS2_3TQ}},
    {CAN20kBaud,  {250, CAN_RSAW_2TQ, CAN_BTS1_16TQ, CAN_BTS2_3TQ}},
    {CAN10kBaud,  {500, CAN_RSAW_2TQ, CAN_BTS1_16TQ, CAN_BTS2_3TQ}}
};
#endif
#ifdef SOC_SERIES_AT32F413
/* attention !!! baud calculation example: apbclk / ((ss + bs1 + bs2) * brp), ep: 96 / ((1 + 8 + 3) * 8) = 1MHz*/
/* attention !!! default apbclk 96 mhz */
static const struct at32_baud_rate can_baud_rate_tab[] =
{
    {CAN1MBaud,   {8 ,  CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN800kBaud, {20,  CAN_RSAW_1TQ, CAN_BTS1_3TQ,  CAN_BTS2_2TQ}},
    {CAN500kBaud, {16,  CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN250kBaud, {32,  CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN125kBaud, {64,  CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN100kBaud, {160, CAN_RSAW_1TQ, CAN_BTS1_3TQ,  CAN_BTS2_2TQ}},
    {CAN50kBaud,  {320, CAN_RSAW_1TQ, CAN_BTS1_3TQ,  CAN_BTS2_2TQ}},
    {CAN20kBaud,  {800, CAN_RSAW_1TQ, CAN_BTS1_3TQ,  CAN_BTS2_2TQ}},
    {CAN10kBaud,  {800, CAN_RSAW_1TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
};
#endif
#ifdef SOC_SERIES_AT32F415
/* attention !!! baud calculation example: apbclk / ((ss + bs1 + bs2) * brp), ep: 72 / ((1 + 8 + 3) * 6) = 1MHz*/
/* attention !!! default apbclk 72 mhz */
static const struct at32_baud_rate can_baud_rate_tab[] =
{
    {CAN1MBaud,   {6 ,  CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN800kBaud, {10 , CAN_RSAW_2TQ, CAN_BTS1_6TQ,  CAN_BTS2_2TQ}},
    {CAN500kBaud, {12 , CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN250kBaud, {24 , CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN125kBaud, {48 , CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN100kBaud, {60 , CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN50kBaud,  {120, CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN20kBaud,  {300, CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN10kBaud,  {600, CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}}
};
#endif
#ifdef SOC_SERIES_AT32F423
/* attention !!! baud calculation example: apbclk / ((ss + bs1 + bs2) * brp), ep: 72 / ((1 + 8 + 3) * 10) = 1MHz*/
/* attention !!! default apbclk 72 mhz */
static const struct at32_baud_rate can_baud_rate_tab[] =
{
    {CAN1MBaud,   {6 ,  CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN800kBaud, {10 , CAN_RSAW_2TQ, CAN_BTS1_6TQ,  CAN_BTS2_2TQ}},
    {CAN500kBaud, {12 , CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN250kBaud, {24 , CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN125kBaud, {48 , CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN100kBaud, {60 , CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN50kBaud,  {120, CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN20kBaud,  {300, CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN10kBaud,  {600, CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}}
};
#endif
#ifdef SOC_SERIES_AT32F425
/* attention !!! baud calculation example: apbclk / ((ss + bs1 + bs2) * brp), ep: 96 / ((1 + 8 + 3) * 8) = 1MHz*/
/* attention !!! default apbclk 96 mhz */
static const struct at32_baud_rate can_baud_rate_tab[] =
{
    {CAN1MBaud,   {8 ,  CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN800kBaud, {10 , CAN_RSAW_2TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN500kBaud, {16 , CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN250kBaud, {32 , CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN125kBaud, {64 , CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN100kBaud, {80 , CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN50kBaud,  {160, CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN20kBaud,  {400, CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN10kBaud,  {800, CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}}
};
#endif
#ifdef SOC_SERIES_AT32F435
/* attention !!! baud calculation example: apbclk / ((ss + bs1 + bs2) * brp), ep: 144 / ((1 + 8 + 3) * 12) = 1MHz*/
/* attention !!! default apbclk 144 mhz */
static const struct at32_baud_rate can_baud_rate_tab[] =
{
    {CAN1MBaud,   {12 , CAN_RSAW_3TQ, CAN_BTS1_8TQ,  CAN_BTS2_3TQ}},
    {CAN800kBaud, {18 , CAN_RSAW_2TQ, CAN_BTS1_7TQ,  CAN_BTS2_2TQ}},
    {CAN500kBaud, {24 , CAN_RSAW_2TQ, CAN_BTS1_9TQ,  CAN_BTS2_2TQ}},
    {CAN250kBaud, {48 , CAN_RSAW_2TQ, CAN_BTS1_9TQ,  CAN_BTS2_2TQ}},
    {CAN125kBaud, {96 , CAN_RSAW_2TQ, CAN_BTS1_9TQ,  CAN_BTS2_2TQ}},
    {CAN100kBaud, {90 , CAN_RSAW_2TQ, CAN_BTS1_13TQ, CAN_BTS2_2TQ}},
    {CAN50kBaud,  {180, CAN_RSAW_2TQ, CAN_BTS1_13TQ, CAN_BTS2_2TQ}},
    {CAN20kBaud,  {450, CAN_RSAW_2TQ, CAN_BTS1_13TQ, CAN_BTS2_2TQ}},
    {CAN10kBaud,  {900, CAN_RSAW_2TQ, CAN_BTS1_13TQ, CAN_BTS2_2TQ}}
};
#endif
#ifdef SOC_SERIES_AT32F437
/* attention !!! baud calculation example: apbclk / ((ss + bs1 + bs2) * brp), ep: 125 / ((1 + 3 + 1) * 25) = 1MHz*/
/* attention !!! default apbclk 125 mhz */
static const struct at32_baud_rate can_baud_rate_tab[] =
{
    {CAN1MBaud,   {25 , CAN_RSAW_1TQ, CAN_BTS1_3TQ,  CAN_BTS2_1TQ}},
    //none
    {CAN500kBaud, {25 , CAN_RSAW_2TQ, CAN_BTS1_7TQ,  CAN_BTS2_2TQ}},
    {CAN250kBaud, {25 , CAN_RSAW_3TQ, CAN_BTS1_16TQ, CAN_BTS2_3TQ}},
    {CAN125kBaud, {50 , CAN_RSAW_2TQ, CAN_BTS1_16TQ, CAN_BTS2_3TQ}},
    {CAN100kBaud, {125, CAN_RSAW_1TQ, CAN_BTS1_8TQ,  CAN_BTS2_1TQ}},
    {CAN50kBaud,  {125, CAN_RSAW_2TQ, CAN_BTS1_16TQ, CAN_BTS2_3TQ}},
    {CAN20kBaud,  {625, CAN_RSAW_1TQ, CAN_BTS1_8TQ,  CAN_BTS2_1TQ}},
    {CAN10kBaud,  {625, CAN_RSAW_2TQ, CAN_BTS1_16TQ, CAN_BTS2_3TQ}}
};
#endif

#if defined (SOC_SERIES_AT32F425)
#define CAN1_RX0_IRQ_NUM        CAN1_IRQn
#define CAN1_RX1_IRQ_NUM        CAN1_IRQn
#define CAN1_TX_IRQ_NUM         CAN1_IRQn
#define CAN1_SE_IRQ_NUM         CAN1_IRQn
#elif defined (SOC_SERIES_AT32F415) || defined (SOC_SERIES_AT32F435) || \
      defined (SOC_SERIES_AT32F437) || defined (SOC_SERIES_AT32F423) || \
      defined (SOC_SERIES_AT32F402) || defined (SOC_SERIES_AT32F405) || \
      defined (SOC_SERIES_AT32A423)
#define CAN1_RX0_IRQ_NUM        CAN1_RX0_IRQn
#define CAN1_RX1_IRQ_NUM        CAN1_RX1_IRQn
#define CAN1_TX_IRQ_NUM         CAN1_TX_IRQn
#define CAN1_SE_IRQ_NUM         CAN1_SE_IRQn
#define CAN1_RX0_IRQ_HANDLER    CAN1_RX0_IRQHandler
#define CAN1_RX1_IRQ_HANDLER    CAN1_RX1_IRQHandler
#define CAN1_TX_IRQ_HANDLER     CAN1_TX_IRQHandler
#define CAN1_SE_IRQ_HANDLER     CAN1_SE_IRQHandler
#else
#define CAN1_RX0_IRQ_NUM        USBFS_L_CAN1_RX0_IRQn
#define CAN1_RX1_IRQ_NUM        CAN1_RX1_IRQn
#define CAN1_TX_IRQ_NUM         USBFS_H_CAN1_TX_IRQn
#define CAN1_SE_IRQ_NUM         CAN1_SE_IRQn
#define CAN1_RX0_IRQ_HANDLER    USBFS_L_CAN1_RX0_IRQHandler
#define CAN1_RX1_IRQ_HANDLER    CAN1_RX1_IRQHandler
#define CAN1_TX_IRQ_HANDLER     USBFS_H_CAN1_TX_IRQHandler
#define CAN1_SE_IRQ_HANDLER     CAN1_SE_IRQHandler
#endif

#ifdef BSP_USING_CAN1
static struct at32_can can_instance1 =
{
    .name = "can1",
    .config.can_x = CAN1,
};
#endif

#ifdef BSP_USING_CAN2
static struct at32_can can_instance2 =
{
    .name = "can2",
    .config.can_x = CAN2,
};
#endif

static rt_uint32_t get_can_baud_index(rt_uint32_t baud)
{
    rt_uint32_t len, index;

    len = sizeof(can_baud_rate_tab) / sizeof(can_baud_rate_tab[0]);
    for (index = 0; index < len; index++)
    {
        if (can_baud_rate_tab[index].baud_rate == baud)
            return index;
    }
    /* default baud is CAN1MBaud */
    return 0;
}

static rt_err_t _can_config(struct rt_can_device *can, struct can_configure *cfg)
{
    struct at32_can *can_instance;
    rt_uint32_t baud_index;

    RT_ASSERT(can);
    RT_ASSERT(cfg);

    can_instance = (struct at32_can *)can->parent.user_data;
    RT_ASSERT(can_instance);

    at32_msp_can_init((void *)can_instance->config.can_x);

    baud_index = get_can_baud_index(cfg->baud_rate);
    /* get baudrate parameters */
    can_baudrate_default_para_init(&can_instance->config.baudrate_init_struct);
    can_instance->config.baudrate_init_struct.rsaw_size = can_baud_rate_tab[baud_index].baud_struct.rsaw_size;
    can_instance->config.baudrate_init_struct.bts1_size = can_baud_rate_tab[baud_index].baud_struct.bts1_size;
    can_instance->config.baudrate_init_struct.bts2_size = can_baud_rate_tab[baud_index].baud_struct.bts2_size;
    can_instance->config.baudrate_init_struct.baudrate_div = can_baud_rate_tab[baud_index].baud_struct.baudrate_div;
    /* config can baudrate */
    if(can_baudrate_set(can_instance->config.can_x, &(can_instance->config.baudrate_init_struct)) != SUCCESS)
    {
        return -RT_ERROR;
    }

    /* config can base parameters */
    can_default_para_init(&(can_instance->config.base_init_struct));
    switch (cfg->mode)
    {
    case RT_CAN_MODE_NORMAL:
        can_instance->config.base_init_struct.mode_selection = CAN_MODE_COMMUNICATE;
        break;
    case RT_CAN_MODE_LISTEN:
        can_instance->config.base_init_struct.mode_selection = CAN_MODE_LISTENONLY;
        break;
    case RT_CAN_MODE_LOOPBACK:
        can_instance->config.base_init_struct.mode_selection = CAN_MODE_LOOPBACK;
        break;
    case RT_CAN_MODE_LOOPBACKANLISTEN:
        can_instance->config.base_init_struct.mode_selection = CAN_MODE_LISTENONLY_LOOPBACK;
        break;
    }

    can_instance->config.base_init_struct.aebo_enable = TRUE;
    can_instance->config.base_init_struct.aed_enable = TRUE;
    can_instance->config.base_init_struct.prsf_enable = FALSE;
    can_instance->config.base_init_struct.mdrsel_selection = CAN_DISCARDING_FIRST_RECEIVED;
    can_instance->config.base_init_struct.mmssr_selection = CAN_SENDING_BY_REQUEST;
    /* init can base function */
    if (can_base_init(can_instance->config.can_x, &(can_instance->config.base_init_struct)) != SUCCESS)
    {
        return -RT_ERROR;
    }

    /* config filter parameters */
    can_filter_init(can_instance->config.can_x, &can_instance->config.filter_init_struct);

    return RT_EOK;
}

static rt_err_t _can_control(struct rt_can_device *can, int cmd, void *arg)
{
    rt_uint32_t argval;
    struct at32_can *can_instance;
    struct rt_can_filter_config *filter_cfg;

    RT_ASSERT(can != RT_NULL);
    can_instance = (struct at32_can *)can->parent.user_data;
    RT_ASSERT(can_instance != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        argval = (rt_uint32_t) arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            if (CAN1 == can_instance->config.can_x)
            {
                nvic_irq_disable(CAN1_RX0_IRQ_NUM);
                nvic_irq_disable(CAN1_RX1_IRQ_NUM);
            }
#if defined (CAN2)
            if (CAN2 == can_instance->config.can_x)
            {
                nvic_irq_disable(CAN2_RX0_IRQn);
                nvic_irq_disable(CAN2_RX1_IRQn);
            }
#endif
            /* disable interrupt */
            can_interrupt_enable(can_instance->config.can_x, CAN_RF0MIEN_INT, FALSE);
            can_interrupt_enable(can_instance->config.can_x, CAN_RF0FIEN_INT, FALSE);
            can_interrupt_enable(can_instance->config.can_x, CAN_RF0OIEN_INT, FALSE);
            can_interrupt_enable(can_instance->config.can_x, CAN_RF1MIEN_INT, FALSE);
            can_interrupt_enable(can_instance->config.can_x, CAN_RF1FIEN_INT, FALSE);
            can_interrupt_enable(can_instance->config.can_x, CAN_RF1OIEN_INT, FALSE);
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            if (CAN1 == can_instance->config.can_x)
            {
                nvic_irq_disable(CAN1_TX_IRQ_NUM);
            }
#if defined (CAN2)
            if (CAN2 == can_instance->config.can_x)
            {
                nvic_irq_disable(CAN2_TX_IRQn);
            }
#endif
            can_interrupt_enable(can_instance->config.can_x, CAN_TCIEN_INT, FALSE);
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            if (CAN1 == can_instance->config.can_x)
            {
                nvic_irq_disable(CAN1_SE_IRQ_NUM);
            }
#if defined (CAN2)
            if (CAN2 == can_instance->config.can_x)
            {
                nvic_irq_disable(CAN2_SE_IRQn);
            }
#endif
            can_interrupt_enable(can_instance->config.can_x, CAN_EAIEN_INT, FALSE);
            can_interrupt_enable(can_instance->config.can_x, CAN_EPIEN_INT, FALSE);
            can_interrupt_enable(can_instance->config.can_x, CAN_BOIEN_INT, FALSE);
            can_interrupt_enable(can_instance->config.can_x, CAN_ETRIEN_INT, FALSE);
            can_interrupt_enable(can_instance->config.can_x, CAN_EOIEN_INT, FALSE);
        }

        break;
    case RT_DEVICE_CTRL_SET_INT:
        argval = (rt_uint32_t) arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            can_interrupt_enable(can_instance->config.can_x, CAN_RF0MIEN_INT, TRUE);
            can_interrupt_enable(can_instance->config.can_x, CAN_RF0FIEN_INT, TRUE);
            can_interrupt_enable(can_instance->config.can_x, CAN_RF0OIEN_INT, TRUE);
            can_interrupt_enable(can_instance->config.can_x, CAN_RF1MIEN_INT, TRUE);
            can_interrupt_enable(can_instance->config.can_x, CAN_RF1FIEN_INT, TRUE);
            can_interrupt_enable(can_instance->config.can_x, CAN_RF1OIEN_INT, TRUE);

            if (CAN1 == can_instance->config.can_x)
            {
                nvic_irq_enable(CAN1_RX0_IRQ_NUM, 1, 0);
                nvic_irq_enable(CAN1_RX1_IRQ_NUM, 1, 0);
            }
#if defined (CAN2)
            if (CAN2 == can_instance->config.can_x)
            {
                nvic_irq_enable(CAN2_RX0_IRQn, 1, 0);
                nvic_irq_enable(CAN2_RX1_IRQn, 1, 0);
            }
#endif
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            can_interrupt_enable(can_instance->config.can_x, CAN_TCIEN_INT, TRUE);

            if (CAN1 == can_instance->config.can_x)
            {
                nvic_irq_enable(CAN1_TX_IRQ_NUM, 1, 0);
            }
#if defined (CAN2)
            if (CAN2 == can_instance->config.can_x)
            {
                nvic_irq_enable(CAN2_TX_IRQn, 1, 0);
            }
#endif
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            can_interrupt_enable(can_instance->config.can_x, CAN_EAIEN_INT, TRUE);
            can_interrupt_enable(can_instance->config.can_x, CAN_EPIEN_INT, TRUE);
            can_interrupt_enable(can_instance->config.can_x, CAN_BOIEN_INT, TRUE);
            can_interrupt_enable(can_instance->config.can_x, CAN_ETRIEN_INT, TRUE);
            can_interrupt_enable(can_instance->config.can_x, CAN_EOIEN_INT, TRUE);

            if (CAN1 == can_instance->config.can_x)
            {
                nvic_irq_enable(CAN1_SE_IRQ_NUM, 1, 0);
            }
#if defined (CAN2)
            if (CAN2 == can_instance->config.can_x)
            {
                nvic_irq_enable(CAN2_SE_IRQn, 1, 0);
            }
#endif
        }
        break;
    case RT_CAN_CMD_SET_FILTER:
    {
        rt_uint32_t id_h = 0;
        rt_uint32_t id_l = 0;
        rt_uint32_t mask_h = 0;
        rt_uint32_t mask_l = 0;
        rt_uint32_t mask_l_tail = 0;

        if (RT_NULL == arg)
        {
            /* default filter config */
            can_filter_init(can_instance->config.can_x, &can_instance->config.filter_init_struct);
        }
        else
        {
            filter_cfg = (struct rt_can_filter_config *)arg;
            /* get default filter */
            for (int i = 0; i < filter_cfg->count; i++)
            {
                if (filter_cfg->items[i].hdr_bank == -1)
                {
                    can_instance->config.filter_init_struct.filter_number = i;
                }
                else
                {
                    can_instance->config.filter_init_struct.filter_number = filter_cfg->items[i].hdr_bank;
                }
                 /**
                 * ID     | CAN_FxR1[31:24] | CAN_FxR1[23:16] | CAN_FxR1[15:8] | CAN_FxR1[7:0]       |
                 * MASK   | CAN_FxR2[31:24] | CAN_FxR1[23:16] | CAN_FxR1[15:8] | CAN_FxR1[7:0]       |
                 * STD ID |     STID[10:3]  | STDID[2:0] |<-                21bit                  ->|
                 * EXT ID |    EXTID[28:21] | EXTID[20:13]    | EXTID[12:5]    | EXTID[4:0] IDE RTR 0|
                 * @note the 32bit STD ID must << 21 to fill CAN_FxR1[31:21] and EXT ID must << 3,
                 *       -> but the id bit of struct rt_can_filter_item is 29,
                 *       -> so STD id << 18 and EXT id Don't need << 3, when get the high 16bit.
                 *       -> FilterIdHigh : (((STDid << 18) or (EXT id)) >> 13) & 0xFFFF,
                 *       -> FilterIdLow:   ((STDid << 18) or (EXT id << 3)) & 0xFFFF.
                 * @note the mask bit of struct rt_can_filter_item is 32,
                 *       -> FilterMaskIdHigh: (((STD mask << 21) or (EXT mask <<3)) >> 16) & 0xFFFF
                 *       -> FilterMaskIdLow: ((STD mask << 21) or (EXT mask <<3)) & 0xFFFF
                 */
                if (filter_cfg->items[i].mode == CAN_FILTER_MODE_ID_MASK)
                {
                    mask_l_tail = 0x06;
                }
                else if (filter_cfg->items[i].mode == CAN_FILTER_MODE_ID_LIST)
                {
                    mask_l_tail = (filter_cfg->items[i].ide << 2) |
                                   (filter_cfg->items[i].rtr << 1);
                }
                if (filter_cfg->items[i].ide == RT_CAN_STDID)
                {
                    id_h = ((filter_cfg->items[i].id << 18) >> 13) & 0xFFFF;
                    id_l = ((filter_cfg->items[i].id << 18) |
                            (filter_cfg->items[i].ide << 2) |
                            (filter_cfg->items[i].rtr << 1)) & 0xFFFF;
                    mask_h = ((filter_cfg->items[i].mask << 21) >> 16) & 0xFFFF;
                    mask_l = ((filter_cfg->items[i].mask << 21) | mask_l_tail) & 0xFFFF;
                }
                else if (filter_cfg->items[i].ide == RT_CAN_EXTID)
                {
                    id_h = (filter_cfg->items[i].id >> 13) & 0xFFFF;
                    id_l = ((filter_cfg->items[i].id << 3)   |
                            (filter_cfg->items[i].ide << 2)  |
                            (filter_cfg->items[i].rtr << 1)) & 0xFFFF;
                    mask_h = ((filter_cfg->items[i].mask << 3) >> 16) & 0xFFFF;
                    mask_l = ((filter_cfg->items[i].mask << 3) | mask_l_tail) & 0xFFFF;
                }
                can_instance->config.filter_init_struct.filter_id_high = id_h;
                can_instance->config.filter_init_struct.filter_id_low = id_l;
                can_instance->config.filter_init_struct.filter_mask_high = mask_h;
                can_instance->config.filter_init_struct.filter_mask_low = mask_l;
                can_instance->config.filter_init_struct.filter_mode = (can_filter_mode_type)filter_cfg->items[i].mode;

                /* filter conf */
                can_filter_init(can_instance->config.can_x, &can_instance->config.filter_init_struct);
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
        if (argval != can_instance->device.config.mode)
        {
            can_instance->device.config.mode = argval;
            return _can_config(&can_instance->device, &can_instance->device.config);
        }
        break;
    case RT_CAN_CMD_SET_BAUD:
        argval = (rt_uint32_t) arg;
        if (argval != CAN1MBaud   &&
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
        if (argval != can_instance->device.config.baud_rate)
        {
            can_instance->device.config.baud_rate = argval;
            return _can_config(&can_instance->device, &can_instance->device.config);
        }
        break;
    case RT_CAN_CMD_SET_PRIV:
        argval = (rt_uint32_t) arg;
        if (argval != RT_CAN_MODE_PRIV &&
            argval != RT_CAN_MODE_NOPRIV)
        {
            return -RT_ERROR;
        }
        if (argval != can_instance->device.config.privmode)
        {
            can_instance->device.config.privmode = argval;
            return _can_config(&can_instance->device, &can_instance->device.config);
        }
        break;
    case RT_CAN_CMD_GET_STATUS:
    {
        rt_uint32_t errtype;
        errtype = can_instance->config.can_x->ests;
        can_instance->device.status.rcverrcnt = errtype >> 24;
        can_instance->device.status.snderrcnt = (errtype >> 16 & 0xFF);
        can_instance->device.status.lasterrtype = errtype & 0x70;
        can_instance->device.status.errcode = errtype & 0x07;

        rt_memcpy(arg, &can_instance->device.status, sizeof(can_instance->device.status));
    }
    break;
    }

    return RT_EOK;
}

static rt_ssize_t _can_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t box_num)
{
    struct can_config *hcan;
    hcan = &((struct at32_can *) can->parent.user_data)->config;
    struct rt_can_msg *pmsg = (struct rt_can_msg *) buf;
    can_tx_message_type tx_message;

    /* check select mailbox is empty */
    switch (box_num)
    {
      case CAN_TX_MAILBOX0:
        if (hcan->can_x->tsts_bit.tm0ef != 1)
        {
            /* return function status */
            return -RT_ERROR;
        }
        break;
    case CAN_TX_MAILBOX1:
        if (hcan->can_x->tsts_bit.tm1ef != 1)
        {
            /* return function status */
            return -RT_ERROR;
        }
        break;
    case CAN_TX_MAILBOX2:
        if (hcan->can_x->tsts_bit.tm2ef != 1)
        {
            /* return function status */
            return -RT_ERROR;
        }
        break;
    default:
        RT_ASSERT(0);
        break;
    }

    if (RT_CAN_STDID == pmsg->ide)
    {
        tx_message.id_type = CAN_ID_STANDARD;
        tx_message.standard_id = pmsg->id;
    }
    else
    {
        tx_message.id_type = CAN_ID_EXTENDED;
        tx_message.extended_id = pmsg->id;
    }

    if (RT_CAN_DTR == pmsg->rtr)
    {
        tx_message.frame_type = CAN_TFT_DATA;
    }
    else
    {
        tx_message.frame_type = CAN_TFT_REMOTE;
    }

    /* set up the dlc */
    tx_message.dlc = pmsg->len & 0x0FU;
    /* set up the data field */
    tx_message.data[0] = (uint32_t)pmsg->data[0];
    tx_message.data[1] = (uint32_t)pmsg->data[1];
    tx_message.data[2] = (uint32_t)pmsg->data[2];
    tx_message.data[3] = (uint32_t)pmsg->data[3];
    tx_message.data[4] = (uint32_t)pmsg->data[4];
    tx_message.data[5] = (uint32_t)pmsg->data[5];
    tx_message.data[6] = (uint32_t)pmsg->data[6];
    tx_message.data[7] = (uint32_t)pmsg->data[7];

    can_message_transmit(hcan->can_x, &tx_message);

    return RT_EOK;
}

static rt_ssize_t _can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t fifo)
{
    struct can_config *hcan;
    hcan = &((struct at32_can *) can->parent.user_data)->config;
    struct rt_can_msg *pmsg = (struct rt_can_msg *) buf;
    can_rx_message_type rx_message;

    RT_ASSERT(can);

    /* get data */
    can_message_receive(hcan->can_x, (can_rx_fifo_num_type)fifo, &rx_message);

    pmsg->data[0] = rx_message.data[0];
    pmsg->data[1] = rx_message.data[1];
    pmsg->data[2] = rx_message.data[2];
    pmsg->data[3] = rx_message.data[3];
    pmsg->data[4] = rx_message.data[4];
    pmsg->data[5] = rx_message.data[5];
    pmsg->data[6] = rx_message.data[6];
    pmsg->data[7] = rx_message.data[7];

    pmsg->len = rx_message.dlc;

    if (rx_message.id_type == CAN_ID_STANDARD)
    {
        pmsg->id = rx_message.standard_id;
        pmsg->ide = RT_CAN_STDID;
    }
    else
    {
        pmsg->id = rx_message.extended_id;
        pmsg->ide = RT_CAN_EXTID;
    }

    pmsg->rtr = rx_message.frame_type;
    pmsg->hdr_index = rx_message.filter_index;

    return RT_EOK;
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
    struct can_config *hcan;
    RT_ASSERT(can);
    hcan = &((struct at32_can *) can->parent.user_data)->config;

    switch (fifo)
    {
    case CAN_RX_FIFO0:
        /* save to user list */
        if (can_receive_message_pending_get(hcan->can_x, CAN_RX_FIFO0) && \
            can_flag_get(hcan->can_x, CAN_RF0MN_FLAG))
        {
            rt_hw_can_isr(can, RT_CAN_EVENT_RX_IND | fifo << 8);
        }
        /* check full flag for fifo0 */
        if (can_flag_get(hcan->can_x, CAN_RF0FF_FLAG) == SET)
        {
            /* clear fifo0 full flag */
            can_flag_clear(hcan->can_x, CAN_RF0FF_FLAG);
        }

        /* check overrun flag for fifo0 */
        if (can_flag_get(hcan->can_x, CAN_RF0OF_FLAG) == SET)
        {
            /* clear fifo0 overrun flag */
            can_flag_clear(hcan->can_x, CAN_RF0OF_FLAG);
            rt_hw_can_isr(can, RT_CAN_EVENT_RXOF_IND | fifo << 8);
        }
        break;
    case CAN_RX_FIFO1:
        /* save to user list */
        if (can_receive_message_pending_get(hcan->can_x, CAN_RX_FIFO1) && \
            can_flag_get(hcan->can_x, CAN_RF1MN_FLAG))
        {
            rt_hw_can_isr(can, RT_CAN_EVENT_RX_IND | fifo << 8);
        }
        /* check full flag for fifo1 */
        if (can_flag_get(hcan->can_x, CAN_RF1FF_FLAG) == SET)
        {
            /* clear fifo1 full flag */
            can_flag_clear(hcan->can_x, CAN_RF1FF_FLAG);
        }

        /* check overrun flag for fifo1 */
        if (can_flag_get(hcan->can_x, CAN_RF1OF_FLAG) == SET)
        {
            /* clear fifo1 overrun flag */
            can_flag_clear(hcan->can_x, CAN_RF1OF_FLAG);
            rt_hw_can_isr(can, RT_CAN_EVENT_RXOF_IND | fifo << 8);
        }
        break;
    }
}

#ifdef BSP_USING_CAN1
/**
 * @brief this function handles can1 tx interrupts. transmit fifo0/1/2 is empty can trigger this interrupt
 */
void CAN1_TX_IRQ_HANDLER(void)
{
    rt_interrupt_enter();
    struct can_config *hcan;
    hcan = &can_instance1.config;
    if (can_flag_get(hcan->can_x, CAN_TM0TCF_FLAG) == SET)
    {
        if (hcan->can_x->tsts_bit.tm0tsf == 1)
        {
            rt_hw_can_isr(&can_instance1.device, RT_CAN_EVENT_TX_DONE | 0 << 8);
        }
        else
        {
            rt_hw_can_isr(&can_instance1.device, RT_CAN_EVENT_TX_FAIL | 0 << 8);
        }
        /* write 0 to clear transmission status flag */
        can_flag_clear(hcan->can_x, CAN_TM0TCF_FLAG);
    }
    else if (can_flag_get(hcan->can_x, CAN_TM1TCF_FLAG) == SET)
    {
        if (hcan->can_x->tsts_bit.tm1tsf == 1)
        {
            rt_hw_can_isr(&can_instance1.device, RT_CAN_EVENT_TX_DONE | 1 << 8);
        }
        else
        {
            rt_hw_can_isr(&can_instance1.device, RT_CAN_EVENT_TX_FAIL | 1 << 8);
        }
        /* write 0 to clear transmission status flag */
        can_flag_clear(hcan->can_x, CAN_TM1TCF_FLAG);
    }
    else if (can_flag_get(hcan->can_x, CAN_TM2TCF_FLAG) == SET)
    {
        if (hcan->can_x->tsts_bit.tm2tsf == 1)
        {
            rt_hw_can_isr(&can_instance1.device, RT_CAN_EVENT_TX_DONE | 2 << 8);
        }
        else
        {
            rt_hw_can_isr(&can_instance1.device, RT_CAN_EVENT_TX_FAIL | 2 << 8);
        }
        /* write 0 to clear transmission status flag */
        can_flag_clear(hcan->can_x, CAN_TM2TCF_FLAG);
    }
    rt_interrupt_leave();
}

/**
 * @brief this function handles can1 rx0 interrupts.
 */
void CAN1_RX0_IRQ_HANDLER(void)
{
    rt_interrupt_enter();
    _can_rx_isr(&can_instance1.device, CAN_RX_FIFO0);
    rt_interrupt_leave();
}

/**
 * @brief this function handles can1 rx1 interrupts.
 */
void CAN1_RX1_IRQ_HANDLER(void)
{
    rt_interrupt_enter();
    _can_rx_isr(&can_instance1.device, CAN_RX_FIFO1);
    rt_interrupt_leave();
}

/**
 * @brief this function handles can1 sce interrupts.
 */
void CAN1_SE_IRQ_HANDLER(void)
{
    rt_uint32_t errtype;
    struct can_config *hcan;

    hcan = &can_instance1.config;
    errtype = hcan->can_x->ests;

    rt_interrupt_enter();

    switch ((errtype & 0x70) >> 4)
    {
    case RT_CAN_BUS_BIT_PAD_ERR:
        can_instance1.device.status.bitpaderrcnt++;
        break;
    case RT_CAN_BUS_FORMAT_ERR:
        can_instance1.device.status.formaterrcnt++;
        break;
    case RT_CAN_BUS_ACK_ERR:/* attention !!! test ack err's unit is transmit unit */
        can_instance1.device.status.ackerrcnt++;
        if (!(can_instance1.config.can_x->tsts_bit.tm0tsf == 1))
            rt_hw_can_isr(&can_instance1.device, RT_CAN_EVENT_TX_FAIL | 0 << 8);
        else if (!(can_instance1.config.can_x->tsts_bit.tm1tsf == 1))
            rt_hw_can_isr(&can_instance1.device, RT_CAN_EVENT_TX_FAIL | 1 << 8);
        else if (!(can_instance1.config.can_x->tsts_bit.tm2tsf == 1))
            rt_hw_can_isr(&can_instance1.device, RT_CAN_EVENT_TX_FAIL | 2 << 8);
        break;
    case RT_CAN_BUS_IMPLICIT_BIT_ERR:
    case RT_CAN_BUS_EXPLICIT_BIT_ERR:
        can_instance1.device.status.biterrcnt++;
        break;
    case RT_CAN_BUS_CRC_ERR:
        can_instance1.device.status.crcerrcnt++;
        break;
    }

    can_instance1.device.status.lasterrtype = errtype & 0x70;
    can_instance1.device.status.rcverrcnt = errtype >> 24;
    can_instance1.device.status.snderrcnt = (errtype >> 16 & 0xFF);
    can_instance1.device.status.errcode = errtype & 0x07;
    /* clear error flags */
    can_flag_clear(hcan->can_x, CAN_ETR_FLAG);
    rt_interrupt_leave();
}
#endif

#if defined (SOC_SERIES_AT32F425)
void CAN1_IRQHandler(void)
{
    CAN1_TX_IRQ_HANDLER();
    CAN1_RX0_IRQ_HANDLER();
    CAN1_RX1_IRQ_HANDLER();
    CAN1_SE_IRQ_HANDLER();
}
#endif

#ifdef BSP_USING_CAN2
/**
 * @brief this function handles can2 tx interrupts.
 */
void CAN2_TX_IRQHandler(void)
{
    rt_interrupt_enter();
    struct can_config *hcan;
    hcan = &can_instance2.config;
    if (can_flag_get(hcan->can_x, CAN_TM0TCF_FLAG) == SET)
    {
        if (hcan->can_x->tsts_bit.tm0tsf == 1)
        {
            rt_hw_can_isr(&can_instance2.device, RT_CAN_EVENT_TX_DONE | 0 << 8);
        }
        else
        {
            rt_hw_can_isr(&can_instance2.device, RT_CAN_EVENT_TX_FAIL | 0 << 8);
        }
        /* write 0 to clear transmission status flag rqcpx */
        can_flag_clear(hcan->can_x, CAN_TM0TCF_FLAG);
    }
    else if (can_flag_get(hcan->can_x, CAN_TM1TCF_FLAG) == SET)
    {
        if (hcan->can_x->tsts_bit.tm1tsf == 1)
        {
            rt_hw_can_isr(&can_instance2.device, RT_CAN_EVENT_TX_DONE | 1 << 8);
        }
        else
        {
            rt_hw_can_isr(&can_instance2.device, RT_CAN_EVENT_TX_FAIL | 1 << 8);
        }
        /* write 0 to clear transmission status flag rqcpx */
        can_flag_clear(hcan->can_x, CAN_TM1TCF_FLAG);
    }
    else if (can_flag_get(hcan->can_x, CAN_TM2TCF_FLAG) == SET)
    {
        if (hcan->can_x->tsts_bit.tm2tsf == 1)
        {
            rt_hw_can_isr(&can_instance2.device, RT_CAN_EVENT_TX_DONE | 2 << 8);
        }
        else
        {
            rt_hw_can_isr(&can_instance2.device, RT_CAN_EVENT_TX_FAIL | 2 << 8);
        }
        /* write 0 to clear transmission status flag rqcpx */
        can_flag_clear(hcan->can_x, CAN_TM2TCF_FLAG);
    }
    rt_interrupt_leave();
}

/**
 * @brief this function handles can2 rx0 interrupts.
 */
void CAN2_RX0_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_rx_isr(&can_instance2.device, CAN_RX_FIFO0);
    rt_interrupt_leave();
}

/**
 * @brief this function handles can2 rx1 interrupts.
 */
void CAN2_RX1_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_rx_isr(&can_instance2.device, CAN_RX_FIFO1);
    rt_interrupt_leave();
}

/**
 * @brief this function handles can2 sce interrupts.
 */
void CAN2_SE_IRQHandler(void)
{
    rt_uint32_t errtype;
    struct can_config *hcan;

    hcan = &can_instance2.config;
    errtype = hcan->can_x->ests;

    rt_interrupt_enter();

    switch ((errtype & 0x70) >> 4)
    {
    case RT_CAN_BUS_BIT_PAD_ERR:
        can_instance2.device.status.bitpaderrcnt++;
        break;
    case RT_CAN_BUS_FORMAT_ERR:
        can_instance2.device.status.formaterrcnt++;
        break;
    case RT_CAN_BUS_ACK_ERR:
        can_instance2.device.status.ackerrcnt++;
        if (!(can_instance2.config.can_x->tsts_bit.tm0tsf == 1))
            rt_hw_can_isr(&can_instance2.device, RT_CAN_EVENT_TX_FAIL | 0 << 8);
        else if (!(can_instance2.config.can_x->tsts_bit.tm1tsf == 1))
            rt_hw_can_isr(&can_instance2.device, RT_CAN_EVENT_TX_FAIL | 1 << 8);
        else if (!(can_instance2.config.can_x->tsts_bit.tm2tsf == 1))
            rt_hw_can_isr(&can_instance2.device, RT_CAN_EVENT_TX_FAIL | 2 << 8);
        break;
    case RT_CAN_BUS_IMPLICIT_BIT_ERR:
    case RT_CAN_BUS_EXPLICIT_BIT_ERR:
        can_instance2.device.status.biterrcnt++;
        break;
    case RT_CAN_BUS_CRC_ERR:
        can_instance2.device.status.crcerrcnt++;
        break;
    }

    can_instance2.device.status.lasterrtype = errtype & 0x70;
    can_instance2.device.status.rcverrcnt = errtype >> 24;
    can_instance2.device.status.snderrcnt = (errtype >> 16 & 0xFF);
    can_instance2.device.status.errcode = errtype & 0x07;
    /* clear error flags */
    can_flag_clear(hcan->can_x, CAN_ETR_FLAG);
    rt_interrupt_leave();
}
#endif

int rt_hw_can_init(void)
{
    struct can_configure config = CANDEFAULTCONFIG;
    config.privmode = RT_CAN_MODE_NOPRIV;
    config.ticks = 50;
#ifdef RT_CAN_USING_HDR
    config.maxhdr = 14;
#endif
    /* config default filter */
    can_filter_init_type filter_conf;
    can_filter_default_para_init(&filter_conf);
    filter_conf.filter_activate_enable = TRUE;
    filter_conf.filter_bit = CAN_FILTER_32BIT;

#ifdef BSP_USING_CAN1
    filter_conf.filter_number = 0;
    can_instance1.config.filter_init_struct = filter_conf;
    can_instance1.device.config = config;

    /* register can1 device */
    rt_hw_can_register(&can_instance1.device,
                       can_instance1.name,
                       &_can_ops,
                       &can_instance1);
#endif /* BSP_USING_CAN1 */

#ifdef BSP_USING_CAN2
    filter_conf.filter_number = 0;
    can_instance2.config.filter_init_struct = filter_conf;
    can_instance2.device.config = config;

    /* register can2 device */
    rt_hw_can_register(&can_instance2.device,
                       can_instance2.name,
                       &_can_ops,
                       &can_instance2);
#endif /* BSP_USING_CAN2 */

    return 0;
}

INIT_BOARD_EXPORT(rt_hw_can_init);

#endif /* BSP_USING_CAN */
