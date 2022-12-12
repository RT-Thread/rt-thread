////////////////////////////////////////////////////////////////////////////////
/// @file     reg_dbg.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE SERIES OF
///           MM32 FIRMWARE LIBRARY.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion

#ifndef __REG_DBG_H
#define __REG_DBG_H

// Files includes

#include <stdint.h>
#include <stdbool.h>
#include "types.h"




#if defined ( __CC_ARM )
#pragma anon_unions
#endif








////////////////////////////////////////////////////////////////////////////////
/// @brief DBG Base Address Definition
////////////////////////////////////////////////////////////////////////////////

#define DBG_BASE                        (0x40007080UL)                         ///< Base Address: 0x40007080
////////////////////////////////////////////////////////////////////////////////
/// @brief DEBUG Registers Structure Definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    __IO u32 IDCODE;                                                            ///< Code ID                                        offset: 0x00
    __IO u32 CR;                                                                ///< Control Register                               offset: 0x04
} DBGMCU_TypeDef;



////////////////////////////////////////////////////////////////////////////////
/// @brief DBGMCU type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define DBGMCU                          ((DBGMCU_TypeDef*) DBG_BASE)



////////////////////////////////////////////////////////////////////////////////
/// @brief DBGMCU_IDCODE Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define DBGMCU_IDCODE_DEV_ID_Pos        (0)
#define DBGMCU_IDCODE_DEV_ID            (0xFFFFFFFFU << DBGMCU_IDCODE_DEV_ID_Pos)   ///< Device identifier

////////////////////////////////////////////////////////////////////////////////
/// @brief DBGMCU_CR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define DBGMCU_CR_SLEEP_Pos             (0)
#define DBGMCU_CR_SLEEP                 (0x01U << DBGMCU_CR_SLEEP_Pos)          ///< Debug Sleep mode
#define DBGMCU_CR_STOP_Pos              (1)
#define DBGMCU_CR_STOP                  (0x01U << DBGMCU_CR_STOP_Pos)           ///< Debug Stop mode
#define DBGMCU_CR_STANDBY_Pos           (2)
#define DBGMCU_CR_STANDBY               (0x01U << DBGMCU_CR_STANDBY_Pos)        ///< Debug Standby mode
#define DBGMCU_CR_TRACE_IOEN_Pos        (5)
#define DBGMCU_CR_TRACE_IOEN            (0x01U << DBGMCU_CR_TRACE_IOEN_Pos)     ///< Trace pin assignment
#define DBGMCU_CR_TRACE_MODE_Pos        (6)
#define DBGMCU_CR_TRACE_MODE_Msk        (0x03U << DBGMCU_CR_TRACE_MODE_Pos)     ///< TRACE_MODE[1:0] bits (Trace Pin Assignment Control)
#define DBGMCU_CR_TRACE_MODE_0          (0x01U << DBGMCU_CR_TRACE_MODE_Pos)     ///< Bit 0
#define DBGMCU_CR_TRACE_MODE_1          (0x02U << DBGMCU_CR_TRACE_MODE_Pos)     ///< Bit 1
#define DBGMCU_CR_TRACE_MODE_ASYNC      (0x00U << DBGMCU_CR_TRACE_MODE_Pos)     ///< Tracking pin uses asynchronous mode
#define DBGMCU_CR_TRACE_MODE_SYNC1      (0x01U << DBGMCU_CR_TRACE_MODE_Pos)     ///< The trace pin uses synchronous mode, and the data length is 1
#define DBGMCU_CR_TRACE_MODE_SYNC2      (0x02U << DBGMCU_CR_TRACE_MODE_Pos)     ///< The trace pin uses synchronous mode, and the data length is 2

#define DBGMCU_CR_IWDG_STOP_Pos         (8)
#define DBGMCU_CR_IWDG_STOP             (0x01U << DBGMCU_CR_IWDG_STOP_Pos)      ///< Debug independent watchdog stopped when core is halted
#define DBGMCU_CR_WWDG_STOP_Pos         (9)
#define DBGMCU_CR_WWDG_STOP             (0x01U << DBGMCU_CR_WWDG_STOP_Pos)      ///< Debug window watchdog stopped when core is halted
#define DBGMCU_CR_TIM_STOP_Pos          (10)
#define DBGMCU_CR_TIM1_STOP             (0x01U << DBGMCU_CR_TIM_STOP_Pos)       ///< TIM1 counter stopped when core is halted
#define DBGMCU_CR_TIM2_STOP             (0x02U << DBGMCU_CR_TIM_STOP_Pos)       ///< TIM2 counter stopped when core is halted
#define DBGMCU_CR_TIM3_STOP             (0x04U << DBGMCU_CR_TIM_STOP_Pos)       ///< TIM3 counter stopped when core is halted
#define DBGMCU_CR_TIM4_STOP             (0x08U << DBGMCU_CR_TIM_STOP_Pos)       ///< TIM4 counter stopped when core is halted





/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
