/*****************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 */
/******************************************************************************/
/** \file hc32f460_event_port.h
 **
 ** A detailed description is available at
 ** @link EventPortGroup EventPort description @endlink
 **
 **   - 2018-12-07 CDT First version for Device Driver Library of EventPort.
 **
 ******************************************************************************/

#ifndef __HC32F460_EVENT_PORT_H__
#define __HC32F460_EVENT_PORT_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

#if (DDL_EVENT_PORT_ENABLE == DDL_ON)

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup EventPortGroup Event Port (EventPort)
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 *******************************************************************************
 ** \brief Event Port Index enumeration
 **
 ******************************************************************************/
typedef enum en_event_port
{
    EventPort1 = 0,                     ///< Event port 1
    EventPort2 = 1,                     ///< Event port 2
    EventPort3 = 2,                     ///< Event port 3
    EventPort4 = 3,                     ///< Event port 4
}en_event_port_t;

/**
 *******************************************************************************
 ** \brief Event Port Pin enumeration
 **
 ******************************************************************************/
typedef enum en_event_pin
{
    EventPin00 = 1u << 0,               ///< Event port Pin 00
    EventPin01 = 1u << 1,               ///< Event port Pin 01
    EventPin02 = 1u << 2,               ///< Event port Pin 02
    EventPin03 = 1u << 3,               ///< Event port Pin 03
    EventPin04 = 1u << 4,               ///< Event port Pin 04
    EventPin05 = 1u << 5,               ///< Event port Pin 05
    EventPin06 = 1u << 6,               ///< Event port Pin 06
    EventPin07 = 1u << 7,               ///< Event port Pin 07
    EventPin08 = 1u << 8,               ///< Event port Pin 08
    EventPin09 = 1u << 9,               ///< Event port Pin 09
    EventPin10 = 1u << 10,              ///< Event port Pin 10
    EventPin11 = 1u << 11,              ///< Event port Pin 11
    EventPin12 = 1u << 12,              ///< Event port Pin 12
    EventPin13 = 1u << 13,              ///< Event port Pin 13
    EventPin14 = 1u << 14,              ///< Event port Pin 14
    EventPin15 = 1u << 15,              ///< Event port Pin 15
    EventPinAll= 0xFFFF,                ///< All event pins are selected
}en_event_pin_t;

/**
 *******************************************************************************
 ** \brief  Event Port common trigger source select
 **
 ******************************************************************************/
typedef enum en_event_port_com_trigger
{
    EpComTrigger_1   = 0x1,            ///< Select common trigger 1.
    EpComTrigger_2   = 0x2,            ///< Select common trigger 2.
    EpComTrigger_1_2 = 0x3,            ///< Select common trigger 1 and 2.
} en_event_port_com_trigger_t;

/**
 *******************************************************************************
 ** \brief Event Port direction enumeration
 **
 ******************************************************************************/
typedef enum en_event_port_dir
{
    EventPortIn     = 0,                ///< Event Port direction 'IN'
    EventPortOut    = 1,                ///< Event Port direction 'OUT'
}en_event_port_dir_t;

/**
 *******************************************************************************
 ** \brief Enumeration to filter clock setting for Event port detect
 **
 ** \note
 ******************************************************************************/
typedef enum en_ep_flt_clk
{
    Pclk1Div1   = 0u,                   ///< PCLK1 as EP filter clock source
    Pclk1Div8   = 1u,                   ///< PCLK1 div8 as EP filter clock source
    Pclk1Div32  = 2u,                   ///< PCLK1 div32 as EP filter clock source
    Pclk1Div64  = 3u,                   ///< PCLK1 div64 as EP filter clock source
}en_ep_flt_clk_t;

/**
 *******************************************************************************
 ** \brief Event port init structure definition
 ******************************************************************************/
typedef struct stc_event_port_init
{
    en_event_port_dir_t     enDirection;    ///< Input/Output setting
    en_functional_state_t   enReset;        ///< Corresponding pin reset after triggered
    en_functional_state_t   enSet;          ///< Corresponding pin set after triggered
    en_functional_state_t   enRisingDetect; ///< Rising edge detect enable
    en_functional_state_t   enFallingDetect;///< Falling edge detect enable
    en_functional_state_t   enFilter;       ///< Filter clock source select
    en_ep_flt_clk_t         enFilterClk;    ///< Filter clock, ref@ en_ep_flt_clk_t for details
}stc_event_port_init_t;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
extern en_result_t EVENTPORT_Init(en_event_port_t enEventPort,                 \
        uint16_t u16EventPin, const stc_event_port_init_t *pstcEventPortInit);
extern en_result_t EVENTPORT_DeInit(void);
extern en_result_t EVENTPORT_SetTriggerSrc(en_event_port_t enEventPort,        \
                                           en_event_src_t enTriggerSrc);
void EVENTPORT_ComTriggerCmd(en_event_port_t enEventPort,                      \
                             en_event_port_com_trigger_t enComTrigger,         \
                             en_functional_state_t enState);
extern uint16_t EVENTPORT_GetData(en_event_port_t enEventPort);
extern en_flag_status_t EVENTPORT_GetBit(en_event_port_t enEventPort,          \
                                         en_event_pin_t enEventPin);
extern en_result_t EVENTPORT_SetBits(en_event_port_t enEventPort,              \
                                    en_event_pin_t u16EventPin);
extern en_result_t EVENTPORT_ResetBits(en_event_port_t enEventPort,            \
                                      en_event_pin_t u16EventPin);

//@} // EventPortGroup

#ifdef __cplusplus
}
#endif

#endif /* DDL_EVENT_PORT_ENABLE */

#endif /* __HC32F460_EVENT_PORT_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
