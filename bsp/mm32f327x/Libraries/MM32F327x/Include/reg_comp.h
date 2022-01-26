////////////////////////////////////////////////////////////////////////////////
/// @file     reg_comp.h
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

#ifndef __REG_COMP_H
#define __REG_COMP_H

// Files includes

#include <stdint.h>
#include <stdbool.h>
#include "types.h"




#if defined ( __CC_ARM )
#pragma anon_unions
#endif







////////////////////////////////////////////////////////////////////////////////
/// @brief COMP Base Address Definition
////////////////////////////////////////////////////////////////////////////////
#define COMP_BASE                       (APB2PERIPH_BASE + 0x4000)              ///< Base Address: 0x40014000

////////////////////////////////////////////////////////////////////////////////
/// @brief Comparators Register Structure Definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {



    __IO u32 RESERVED1;                                                         ///<                                                offset: 0x00
    __IO u32 RESERVED2;                                                         ///<                                                offset: 0x04
    __IO u32 RESERVED3;                                                         ///<                                                offset: 0x08
    union {
        __IO u32 CSR1;                                                          ///< COMP1 Control Status Register                  offset: 0x0C
        __IO u32 COMP1_CSR;
    };
    union {
        __IO u32 CSR2;                                                          ///< COMP2 Control Status Register                  offset: 0x10
        __IO u32 COMP2_CSR;
    };
    __IO u32 RESERVED4;                                                         ///<                                                offset: 0x14
    union {
        __IO u32 CRV;                                                           ///< COMP external reference voltage register       offset: 0x18
        __IO u32 COMP_CRV;
    };
    union {
        __IO u32 POLL1;                                                         ///< COMP1 polling register                         offset: 0x1C
        __IO u32 COMP1_POLL;
    };
    union {
        __IO u32 POLL2;                                                         ///< COMP2 polling register                         offset: 0x20
        __IO u32 COMP2_POLL;
    };
} COMP_TypeDef;


////////////////////////////////////////////////////////////////////////////////
/// @brief COMP type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define COMP                            ((COMP_TypeDef*) COMP_BASE)





////////////////////////////////////////////////////////////////////////////////
/// @brief COMP_CSR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define COMP_CSR_EN_Pos             (0)
#define COMP_CSR_EN                 (0x01U << COMP_CSR_EN_Pos)              ///< Comparator enable
#define COMP_CSR_MODE_Pos           (2)
#define COMP_CSR_MODE               (0x03U << COMP_CSR_MODE_Pos)            ///< Comparator mode
#define COMP_CSR_MODE_LOWESTPOWER   (0x00U << COMP_CSR_MODE_Pos)            ///< Comparator lowest power mode
#define COMP_CSR_MODE_LOWPOWER      (0x01U << COMP_CSR_MODE_Pos)            ///< Comparator low power mode
#define COMP_CSR_MODE_MEDIUMRATE    (0x02U << COMP_CSR_MODE_Pos)            ///< Comparator medium rate mode
#define COMP_CSR_MODE_HIGHRATE      (0x03U << COMP_CSR_MODE_Pos)            ///< Comparator high rate mode

#define COMP_CSR_INM_Pos            (4)
#define COMP_CSR_INM                (0x03U << COMP_CSR_INM_Pos)             ///< Comparator inverting input selection
#define COMP_CSR_INM_0              (0x00U << COMP_CSR_INM_Pos)             ///< INM0 as COMP inverting input
#define COMP_CSR_INM_1              (0x01U << COMP_CSR_INM_Pos)             ///< INM1 as COMP inverting input
#define COMP_CSR_INM_2              (0x02U << COMP_CSR_INM_Pos)             ///< INM2 as COMP inverting input
#define COMP_CSR_INM_3              (0x03U << COMP_CSR_INM_Pos)             ///< INM3 as COMP inverting input

#define COMP_CSR_INP_Pos            (7)
#define COMP_CSR_INP                (0x03U << COMP_CSR_INP_Pos)             ///< Comparator non-inverting input selection
#define COMP_CSR_INP_INP0           (0x00U << COMP_CSR_INP_Pos)             ///< INP0 as COMP non-inverting input
#define COMP_CSR_INP_INP1           (0x01U << COMP_CSR_INP_Pos)             ///< INP1 as COMP non-inverting input
#define COMP_CSR_INP_INP2           (0x02U << COMP_CSR_INP_Pos)             ///< INP2 as COMP non-inverting input
#define COMP_CSR_INP_INP3           (0x03U << COMP_CSR_INP_Pos)             ///< INP3 as COMP non-inverting input

#define COMP_CSR_OUT_Pos            (10)
#define COMP_CSR_OUT                (0x0FU << COMP_CSR_OUT_Pos)             ///< Comparator output selection
#define COMP_CSR_OUT_TIM1_BRAKE     (0x02U << COMP_CSR_OUT_Pos)             ///< Timer1 brake input
#define COMP_CSR_OUT_TIM8_BRAKE     (0x03U << COMP_CSR_OUT_Pos)             ///< Timer8 brake input
#define COMP_CSR_OUT_TIM1_OCREFCLR  (0x06U << COMP_CSR_OUT_Pos)             ///< Timer1 ocrefclear input
#define COMP_CSR_OUT_TIM1_CAPTURE1  (0x07U << COMP_CSR_OUT_Pos)             ///< Timer1 input capture 1
#define COMP_CSR_OUT_TIM2_CAPTURE4  (0x08U << COMP_CSR_OUT_Pos)             ///< Timer2 input capture 4
#define COMP_CSR_OUT_TIM2_OCREFCLR  (0x09U << COMP_CSR_OUT_Pos)             ///< Timer2 ocrefclear input
#define COMP_CSR_OUT_TIM3_CAPTURE1  (0x0AU << COMP_CSR_OUT_Pos)             ///< Timer3 input capture 1
#define COMP_CSR_OUT_TIM3_OCREFCLR  (0x0BU << COMP_CSR_OUT_Pos)             ///< Timer3 ocrefclear input
#define COMP_CSR_OUT_TIM8_OCREFCLR  (0x0FU << COMP_CSR_OUT_Pos)             ///< Timer8 ocrefclear input

#define COMP_CSR_POL_Pos            (15)
#define COMP_CSR_POL                (0x01U << COMP_CSR_POL_Pos)             ///< Comparator output polarity
#define COMP_CSR_HYST_Pos           (16)
#define COMP_CSR_HYST               (0x03U << COMP_CSR_HYST_Pos)            ///< Comparator hysteresis
#define COMP_CSR_HYST_0             (0x00U << COMP_CSR_HYST_Pos)            ///< Hysteresis Voltage: 0mV
#define COMP_CSR_HYST_15            (0x01U << COMP_CSR_HYST_Pos)            ///< Hysteresis Voltage: 15mV
#define COMP_CSR_HYST_30            (0x02U << COMP_CSR_HYST_Pos)            ///< Hysteresis Voltage: 30mV
#define COMP_CSR_HYST_90            (0x03U << COMP_CSR_HYST_Pos)            ///< Hysteresis Voltage: 90mV

#define COMP_CSR_OFLT_Pos           (18)
#define COMP_CSR_OFLT               (0x07U << COMP_CSR_OFLT_Pos)            ///< Comparator output filter
#define COMP_CSR_OFLT_0             (0x00U << COMP_CSR_OFLT_Pos)            ///< 0 clock cycle
#define COMP_CSR_OFLT_1             (0x01U << COMP_CSR_OFLT_Pos)            ///< 2 clock cycle
#define COMP_CSR_OFLT_2             (0x02U << COMP_CSR_OFLT_Pos)            ///< 4 clock cycle
#define COMP_CSR_OFLT_3             (0x03U << COMP_CSR_OFLT_Pos)            ///< 8 clock cycle
#define COMP_CSR_OFLT_4             (0x04U << COMP_CSR_OFLT_Pos)            ///< 16 clock cycle
#define COMP_CSR_OFLT_5             (0x05U << COMP_CSR_OFLT_Pos)            ///< 32 clock cycle
#define COMP_CSR_OFLT_6             (0x06U << COMP_CSR_OFLT_Pos)            ///< 64 clock cycle
#define COMP_CSR_OFLT_7             (0x07U << COMP_CSR_OFLT_Pos)            ///< 128 clock cycle

#define COMP_CSR_STA_Pos            (30)
#define COMP_CSR_STA                (0x01U << COMP_CSR_STA_Pos)             ///< Comparator output status
#define COMP_CSR_LOCK_Pos           (31)
#define COMP_CSR_LOCK               (0x01U << COMP_CSR_LOCK_Pos)            ///< Comparator lock


////////////////////////////////////////////////////////////////////////////////
/// @brief COMP_CRV Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define COMP_CRV_Pos                (0)
#define COMP_CRV_MASK               (0x0FU << COMP_CRV_Pos)                 ///< Comparator external reference voltage select
#define COMP_CRV_1_20               (0x00U << COMP_CRV_Pos)                 ///< Comparator external reference voltage select
#define COMP_CRV_2_20               (0x01U << COMP_CRV_Pos)                 ///< Comparator external reference voltage select
#define COMP_CRV_3_20               (0x02U << COMP_CRV_Pos)                 ///< Comparator external reference voltage select
#define COMP_CRV_4_20               (0x03U << COMP_CRV_Pos)                 ///< Comparator external reference voltage select
#define COMP_CRV_5_20               (0x04U << COMP_CRV_Pos)                 ///< Comparator external reference voltage select
#define COMP_CRV_6_20               (0x05U << COMP_CRV_Pos)                 ///< Comparator external reference voltage select
#define COMP_CRV_7_20               (0x06U << COMP_CRV_Pos)                 ///< Comparator external reference voltage select
#define COMP_CRV_8_20               (0x07U << COMP_CRV_Pos)                 ///< Comparator external reference voltage select
#define COMP_CRV_9_20               (0x08U << COMP_CRV_Pos)                 ///< Comparator external reference voltage select
#define COMP_CRV_10_20              (0x09U << COMP_CRV_Pos)                 ///< Comparator external reference voltage select
#define COMP_CRV_11_20              (0x0AU << COMP_CRV_Pos)                 ///< Comparator external reference voltage select
#define COMP_CRV_12_20              (0x0BU << COMP_CRV_Pos)                 ///< Comparator external reference voltage select
#define COMP_CRV_13_20              (0x0CU << COMP_CRV_Pos)                 ///< Comparator external reference voltage select
#define COMP_CRV_14_20              (0x0DU << COMP_CRV_Pos)                 ///< Comparator external reference voltage select
#define COMP_CRV_15_20              (0x0EU << COMP_CRV_Pos)                 ///< Comparator external reference voltage select
#define COMP_CRV_16_20              (0x0FU << COMP_CRV_Pos)                 ///< Comparator external reference voltage select

#define COMP_CRV_EN_Pos             (4)
#define COMP_CRV_EN                 (0x01U << COMP_CRV_EN_Pos)              ///< Comparator external reference voltage enable
#define COMP_CRV_EN_DISABLE         (0x00U << COMP_CRV_EN_Pos)              ///< Disable comparator external reference voltage
#define COMP_CRV_EN_ENABLE          (0x01U << COMP_CRV_EN_Pos)              ///< Enable comparator external reference voltage
#define COMP_CRV_SRC_Pos            (5)
#define COMP_CRV_SRC                (0x01U << COMP_CRV_SRC_Pos)             ///< Comparator external reference voltage source select
#define COMP_CRV_SRC_VREF           (0x00U << COMP_CRV_SRC_Pos)             ///< Select VREF
#define COMP_CRV_SRC_AVDD           (0x01U << COMP_CRV_SRC_Pos)             ///< Select AVDD

////////////////////////////////////////////////////////////////////////////////
/// @brief COMP_POL Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define COMP_POLL_EN_Pos            (0)
#define COMP_POLL_EN                (0x01U << COMP_POLL_EN_Pos)              ///< Comparator polling enable
#define COMP_POLL_EN_DISABLE        (0x00U << COMP_POLL_EN_Pos)              ///< Disable comparator polling mode
#define COMP_POLL_EN_ENABLE         (0x01U << COMP_POLL_EN_Pos)              ///< Enable comparator polling mode
#define COMP_POLL_CH_Pos            (1)
#define COMP_POLL_CH                (0x01U << COMP_POLL_CH_Pos)              ///< Comparator polling channel
#define COMP_POLL_CH_1_2            (0x00U << COMP_POLL_CH_Pos)              ///< Polling channel 1/2
#define COMP_POLL_CH_1_2_3          (0x01U << COMP_POLL_CH_Pos)              ///< Polling channel 1/2/3
#define COMP_POLL_FIXN_Pos          (2)
#define COMP_POLL_FIXN              (0x01U << COMP_POLL_FIXN_Pos)            ///< Polling inverting input fix
#define COMP_POLL_FIXN_NOTFIXED     (0x00U << COMP_POLL_FIXN_Pos)            ///< Polling channel inverting input is not fixed
#define COMP_POLL_FIXN_FIXED        (0x01U << COMP_POLL_FIXN_Pos)            ///< Polling channel inverting input fixed
#define COMP_POLL_PERIOD_Pos        (4)
#define COMP_POLL_PERIOD            (0x07U << COMP_POLL_PERIOD_Pos)          ///< polling wait cycle
#define COMP_POLL_PERIOD_1          (0x00U << COMP_POLL_PERIOD_Pos)          ///< 1 clock cycle
#define COMP_POLL_PERIOD_2          (0x01U << COMP_POLL_PERIOD_Pos)          ///< 2 clock cycle
#define COMP_POLL_PERIOD_4          (0x02U << COMP_POLL_PERIOD_Pos)          ///< 4 clock cycle
#define COMP_POLL_PERIOD_8          (0x03U << COMP_POLL_PERIOD_Pos)          ///< 8 clock cycle
#define COMP_POLL_PERIOD_16         (0x04U << COMP_POLL_PERIOD_Pos)          ///< 16 clock cycle
#define COMP_POLL_PERIOD_32         (0x05U << COMP_POLL_PERIOD_Pos)          ///< 32 clock cycle
#define COMP_POLL_PERIOD_64         (0x06U << COMP_POLL_PERIOD_Pos)          ///< 64 clock cycle
#define COMP_POLL_PERIOD_128        (0x07U << COMP_POLL_PERIOD_Pos)          ///< 128 clock cycle
#define COMP_POLL_POUT_Pos          (8)
#define COMP_POLL_POUT              (0x07U << COMP_POLL_POUT_Pos)            ///< Polling output
#define COMP_POLL_POUT_Low          (0x00U << COMP_POLL_POUT_Pos)            ///< Non-inverting input is lower than inverting input
#define COMP_POLL_POUT_High         (0x01U << COMP_POLL_POUT_Pos)            ///< Non-inverting input is higher than inverting input





/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
