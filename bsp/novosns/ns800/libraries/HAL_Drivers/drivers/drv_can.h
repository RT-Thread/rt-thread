/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-05     Xeon Xu      the first version
 * 2019-01-22     YLZ          port from stm324xx-HAL to bsp stm3210x-HAL
 * 2019-01-26     YLZ          redefine `struct stm32_drv_can` add member `Rx1Message`
 * 2019-02-19     YLZ          port to BSP [stm32]
 * 2019-06-17     YLZ          modify struct stm32_drv_can.
 */

#ifndef __DRV_CAN_H__
#define __DRV_CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <board.h>
#include <rtdevice.h>

#define CAN_FILTER_NUM_MAX (16U)
#define NS800RT7_CAN_RX_MB_COUNT    (2U)
#define NS800RT7_CAN_TX_MB_COUNT    (1U)
#define NS800RT7_CAN_TOTAL_MB_COUNT (NS800RT7_CAN_TX_MB_COUNT + NS800RT7_CAN_RX_MB_COUNT)

enum _can_state
{
    StateIdle = 0x0,     /*!< MB idle.*/
    StateRxData = 0x1,   /*!< MB receiving.*/
    StateRxRemote = 0x2, /*!< MB receiving remote reply.*/
    StateTxData = 0x3,   /*!< MB transmitting.*/
    StateTxRemote = 0x4, /*!< MB transmitting remote request.*/
};

struct ns800rt7_baud_rate_tab
{
    rt_uint32_t baud_rate;
    rt_uint32_t config_data;
};
#define BAUD_DATA(NO)       (can_baud_rate_tab[NO].config_data)

typedef enum
{
    NS800RT7_CAN_INSTANCE_CAN1 = 0U,
    NS800RT7_CAN_INSTANCE_CANFD1,
    NS800RT7_CAN_INSTANCE_CANFD2,
} ns800rt7_can_instance;

typedef struct
{
    GPIO_TypeDef *port;
    GPIO_PinNum pin;
    GPIO_AltFunc alt_func;
} ns800rt7_can_pin;

typedef void (*ns800rt7_can_irq_handler)(void);


typedef struct
{
    const char                   *name;
    ns800rt7_can_instance        instance;
    FLEXCANDRV_ControllerCfgType CanCfg;
    IRQn_Type                    irqn1;
    IRQn_Type                    irqn2;
    ns800rt7_can_irq_handler     irq_handler;
    ns800rt7_can_irq_handler     err_irq_handler;
    FLEXCANDRV_Type              CanHandle;
    ns800rt7_can_pin             tx_pin;
    ns800rt7_can_pin             rx_pin;
    rt_uint8_t                   can_instance_idx;
    rt_uint8_t                   can_ram_num;
    rt_bool_t                    fd_capable;
    rt_uint32_t                  clock_freq;
    FLEXCANDRV_MsgCfgType        FilterConfig[CAN_FILTER_NUM_MAX];
    FLEXCANDRV_MsgObjType        rx_frame[NS800RT7_CAN_RX_MB_COUNT];
    uint8_t                      FilterNum;
    volatile uint8_t             mbState[128];
    struct rt_can_device         device;     /* inherit from can device */
} ns800rt7_can;

int rt_hw_can_init(void);

#ifdef __cplusplus
}
#endif

#endif /*__DRV_CAN_H__ */

/************************** end of file ******************/

