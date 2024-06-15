/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author               Notes
 * 2022-04-28     CDT                  first version
 * 2022-06-07     xiaoxiaolisunny      add hc32f460 series
 * 2022-06-08     CDT                  fix a bug of RT_CAN_CMD_SET_FILTER
 * 2022-06-15     lianghongquan        fix bug, FILTER_COUNT, RT_CAN_CMD_SET_FILTER, interrupt setup and processing.
 */

#include "drv_can.h"
#include <drv_config.h>
#include <board_config.h>

#if defined(BSP_USING_CAN)
#define LOG_TAG    "drv_can"

#if defined(BSP_USING_CAN1) || defined(BSP_USING_CAN2)

#if defined(RT_CAN_USING_CANFD) && defined(HC32F460)
    #error "Selected mcu does not support canfd!"
#endif

#define TSEG1_MIN_FOR_CAN2_0                                (2U)
#define TSEG1_MAX_FOR_CAN2_0                                (65U)
#define TSEG1_MIN_FOR_CANFD_ARBITRATION                     (2U)
#define TSEG1_MAX_FOR_CANFD_ARBITRATION                     (65U)
#define TSEG1_MIN_FOR_CANFD_DATA                            (2U)
#define TSEG1_MAX_FOR_CANFD_DATA                            (17U)

#define TSEG2_MIN_FOR_CAN2_0                                (1U)
#define TSEG2_MAX_FOR_CAN2_0                                (8U)
#define TSEG2_MIN_FOR_CANFD_ARBITRATION                     (1U)
#define TSEG2_MAX_FOR_CANFD_ARBITRATION                     (32U)
#define TSEG2_MIN_FOR_CANFD_DATA                            (1U)
#define TSEG2_MAX_FOR_CANFD_DATA                            (8U)

#define TSJW_MIN_FOR_CAN2_0                                 (1U)
#define TSJW_MAX_FOR_CAN2_0                                 (16U)
#define TSJW_MIN_FOR_CANFD_ARBITRATION                      (1U)
#define TSJW_MAX_FOR_CANFD_ARBITRATION                      (16U)
#define TSJW_MIN_FOR_CANFD_DATA                             (1U)
#define TSJW_MAX_FOR_CANFD_DATA                             (8U)

#define NUM_TQ_MIN_FOR_CAN2_0                               (8U)
#define NUM_TQ_MAX_FOR_CAN2_0                               (TSEG1_MAX_FOR_CAN2_0 + TSEG2_MAX_FOR_CAN2_0)
#define NUM_TQ_MIN_FOR_CANFD_ARBITRATION                    (8U)
#define NUM_TQ_MAX_FOR_CANFD_ARBITRATION                    (TSEG1_MAX_FOR_CANFD_ARBITRATION + TSEG2_MAX_FOR_CANFD_ARBITRATION)
#define NUM_TQ_MIN_FOR_CANFD_DATA                           (8U)
#define NUM_TQ_MAX_FOR_CANFD_DATA                           (TSEG1_MAX_FOR_CANFD_DATA + TSEG2_MAX_FOR_CANFD_DATA)

#define NUM_PRESCALE_MAX                                    (256U)
#define MIN_TQ_MUL_PRESCALE                                 (4U)

#define CAN_BIT_TIMING_CAN2_0                               (1U << 0)
#define CAN_BIT_TIMING_CANFD_ARBITRATION                    (1U << 1)
#define CAN_BIT_TIMING_CANFD_DATA                           (1U << 2)

#if defined(HC32F4A0)
    #define FILTER_COUNT                                    (16U)
    #define CAN1_INT_SRC                                    (INT_SRC_CAN1_HOST)
    #define CAN2_INT_SRC                                    (INT_SRC_CAN2_HOST)
#endif

#if defined (HC32F460)
    #define FILTER_COUNT                                    (8U)
    #define CAN1_INT_SRC                                    (INT_SRC_CAN_INT)
#endif

#define IS_VALID_PRIV_MODE(mode)                            ((mode == RT_CAN_MODE_PRIV) || (mode == RT_CAN_MODE_NOPRIV))
#define IS_VALID_WORK_MODE(mode)                            (mode <= RT_CAN_MODE_LOOPBACKANLISTEN)
#define IS_VALID_BAUD_RATE_CAN2_0(baud)                     (baud == (CAN10kBaud)    \
                                                            || baud == (CAN20kBaud)  \
                                                            || baud == (CAN50kBaud)  \
                                                            || baud == (CAN125kBaud) \
                                                            || baud == (CAN250kBaud) \
                                                            || baud == (CAN500kBaud) \
                                                            || baud == (CAN1MBaud)   \
                                                            )
#define IS_VALID_BAUD_RATE_CANFD_ARBITRATION(baud)             IS_VALID_BAUD_RATE_CAN2_0(baud)
#define IS_VALID_BAUD_RATE_CANFD_DATA(baud)                 (baud == (CANFD_DATA_BAUD_1M)   \
                                                            || baud == (CANFD_DATA_BAUD_2M) \
                                                            || baud == (CANFD_DATA_BAUD_4M) \
                                                            || baud == (CANFD_DATA_BAUD_5M) \
                                                            || baud == (CANFD_DATA_BAUD_8M) \
                                                            )

enum
{
#ifdef BSP_USING_CAN1
    CAN1_INDEX,
#endif
#ifdef BSP_USING_CAN2
    CAN2_INDEX,
#endif
    CAN_INDEX_MAX,
};

struct can_baud_rate_tab
{
    rt_uint32_t baud_rate;
    stc_can_bit_time_config_t ll_sbt;
};

struct canfd_baud_rate_tab
{
    rt_uint32_t clk_src;
    rt_uint8_t phase;
    rt_uint32_t baud;
    stc_can_bit_time_config_t ll_bt;
};

typedef struct
{
    uint8_t tq_min;
    uint8_t tq_max;
    uint8_t seg1_min;
    uint8_t seg1_max;
    uint8_t seg2_min;
    uint8_t seg2_max;
    uint8_t sjw_min;
    uint8_t sjw_max;
    uint8_t min_diff_seg1_minus_seg2;
} can_bit_timing_table_t;

#ifndef RT_CAN_USING_CANFD
static const struct can_baud_rate_tab _g_baudrate_tab[] =
{
    {CAN1MBaud,   CAN_BIT_TIME_CONFIG_1M_BAUD},
    {CAN800kBaud, CAN_BIT_TIME_CONFIG_800K_BAUD},
    {CAN500kBaud, CAN_BIT_TIME_CONFIG_500K_BAUD},
    {CAN250kBaud, CAN_BIT_TIME_CONFIG_250K_BAUD},
    {CAN125kBaud, CAN_BIT_TIME_CONFIG_125K_BAUD},
    {CAN100kBaud, CAN_BIT_TIME_CONFIG_100K_BAUD},
    {CAN50kBaud,  CAN_BIT_TIME_CONFIG_50K_BAUD},
    {CAN20kBaud,  CAN_BIT_TIME_CONFIG_20K_BAUD},
    {CAN10kBaud,  CAN_BIT_TIME_CONFIG_10K_BAUD},
};
#endif

typedef struct
{
    struct rt_can_device rt_can;
    struct can_dev_init_params init;
    CM_CAN_TypeDef *instance;
    stc_can_init_t ll_init;
} can_device;

#ifdef RT_CAN_USING_CANFD
static const can_bit_timing_table_t _g_can_bit_timing_tbl[3] =
{
    {
        .tq_min = NUM_TQ_MIN_FOR_CAN2_0,
        .tq_max = NUM_TQ_MAX_FOR_CAN2_0,
        .seg1_min = TSEG1_MIN_FOR_CAN2_0,
        .seg1_max = TSEG1_MAX_FOR_CAN2_0,
        .seg2_min = TSEG2_MIN_FOR_CAN2_0,
        .seg2_max = TSEG2_MAX_FOR_CAN2_0,
        .sjw_min = TSJW_MIN_FOR_CAN2_0,
        .sjw_max = TSJW_MAX_FOR_CAN2_0,
        .min_diff_seg1_minus_seg2 = 2,
    },
    {
        .tq_min = NUM_TQ_MIN_FOR_CANFD_ARBITRATION,
        .tq_max = NUM_TQ_MAX_FOR_CANFD_ARBITRATION,
        .seg1_min = TSEG1_MIN_FOR_CANFD_ARBITRATION,
        .seg1_max = TSEG1_MAX_FOR_CANFD_ARBITRATION,
        .seg2_min = TSEG2_MIN_FOR_CANFD_ARBITRATION,
        .seg2_max = TSEG2_MAX_FOR_CANFD_ARBITRATION,
        .sjw_min = TSJW_MIN_FOR_CANFD_ARBITRATION,
        .sjw_max = TSJW_MAX_FOR_CANFD_ARBITRATION,
        .min_diff_seg1_minus_seg2 = 2,
    },
    {
        .tq_min = NUM_TQ_MIN_FOR_CANFD_DATA,
        .tq_max = NUM_TQ_MAX_FOR_CANFD_DATA,
        .seg1_min = TSEG1_MIN_FOR_CANFD_DATA,
        .seg1_max = TSEG1_MAX_FOR_CANFD_DATA,
        .seg2_min = TSEG2_MIN_FOR_CANFD_DATA,
        .seg2_max = TSEG2_MAX_FOR_CANFD_DATA,
        .sjw_min = TSJW_MIN_FOR_CANFD_DATA,
        .sjw_max = TSJW_MAX_FOR_CANFD_DATA,
        .min_diff_seg1_minus_seg2 = 1,
    }
};

static const struct canfd_baud_rate_tab _g_baudrate_fd[] =
{
    {CAN_CLOCK_SRC_20M, CAN_BIT_TIMING_CANFD_ARBITRATION, CANFD_ARBITRATION_BAUD_250K, 1U, 64U, 16U, 16U},
    {CAN_CLOCK_SRC_20M, CAN_BIT_TIMING_CANFD_ARBITRATION, CANFD_ARBITRATION_BAUD_500K, 1U, 32U, 8U, 8U},
    {CAN_CLOCK_SRC_20M, CAN_BIT_TIMING_CANFD_ARBITRATION | CAN_BIT_TIMING_CANFD_DATA, CANFD_DATA_BAUD_1M, 1U, 16U, 4U, 4U},
    {CAN_CLOCK_SRC_20M, CAN_BIT_TIMING_CANFD_ARBITRATION | CAN_BIT_TIMING_CANFD_DATA, CANFD_DATA_BAUD_2M, 1U, 8U, 2U, 2U},
    {CAN_CLOCK_SRC_20M, CAN_BIT_TIMING_CANFD_ARBITRATION | CAN_BIT_TIMING_CANFD_DATA, CANFD_DATA_BAUD_4M, 1U, 4U, 1U, 1U},
    {CAN_CLOCK_SRC_20M, CAN_BIT_TIMING_CANFD_ARBITRATION | CAN_BIT_TIMING_CANFD_DATA, CANFD_DATA_BAUD_5M, 1U, 3U, 1U, 1U},
    {CAN_CLOCK_SRC_40M, CAN_BIT_TIMING_CANFD_ARBITRATION, CANFD_ARBITRATION_BAUD_250K, 2U, 64U, 16U, 16U},
    {CAN_CLOCK_SRC_40M, CAN_BIT_TIMING_CANFD_ARBITRATION, CANFD_ARBITRATION_BAUD_500K, 1U, 64U, 16U, 16U},
    {CAN_CLOCK_SRC_40M, CAN_BIT_TIMING_CANFD_ARBITRATION, CANFD_DATA_BAUD_1M, 1U, 32U, 8U, 8U},
    {CAN_CLOCK_SRC_40M, CAN_BIT_TIMING_CANFD_ARBITRATION | CAN_BIT_TIMING_CANFD_DATA, CANFD_DATA_BAUD_2M, 1U, 16U, 4U, 4U},
    {CAN_CLOCK_SRC_40M, CAN_BIT_TIMING_CANFD_ARBITRATION | CAN_BIT_TIMING_CANFD_DATA, CANFD_DATA_BAUD_4M, 1U, 8U, 2U, 2U},
    {CAN_CLOCK_SRC_40M, CAN_BIT_TIMING_CANFD_ARBITRATION | CAN_BIT_TIMING_CANFD_DATA, CANFD_DATA_BAUD_5M, 1U, 6U, 2U, 2U},
    {CAN_CLOCK_SRC_40M, CAN_BIT_TIMING_CANFD_ARBITRATION | CAN_BIT_TIMING_CANFD_DATA, CANFD_DATA_BAUD_8M, 1U, 4U, 1U, 1U},
    {CAN_CLOCK_SRC_80M, CAN_BIT_TIMING_CANFD_ARBITRATION, CANFD_ARBITRATION_BAUD_250K, 4U, 64U, 16U},
    {CAN_CLOCK_SRC_80M, CAN_BIT_TIMING_CANFD_ARBITRATION, CANFD_ARBITRATION_BAUD_500K, 2U, 64U, 16U},
    {CAN_CLOCK_SRC_80M, CAN_BIT_TIMING_CANFD_ARBITRATION, CANFD_DATA_BAUD_1M, 2U, 32U, 8U, 8U},
    {CAN_CLOCK_SRC_80M, CAN_BIT_TIMING_CANFD_ARBITRATION | CAN_BIT_TIMING_CANFD_DATA, CANFD_DATA_BAUD_2M, 2U, 16U, 4U, 4U},
    {CAN_CLOCK_SRC_80M, CAN_BIT_TIMING_CANFD_ARBITRATION | CAN_BIT_TIMING_CANFD_DATA, CANFD_DATA_BAUD_4M, 1U, 16U, 4U, 4U},
    {CAN_CLOCK_SRC_80M, CAN_BIT_TIMING_CANFD_ARBITRATION | CAN_BIT_TIMING_CANFD_DATA, CANFD_DATA_BAUD_5M, 1U, 12U, 4U, 4U},
    {CAN_CLOCK_SRC_80M, CAN_BIT_TIMING_CANFD_ARBITRATION | CAN_BIT_TIMING_CANFD_DATA, CANFD_DATA_BAUD_8M, 1U, 8U, 2U, 2U},
};
#endif

static can_device _g_can_dev_array[] =
{
#if defined(HC32F4A0)
#ifdef BSP_USING_CAN1
    {
        {0},
        CAN1_INIT_PARAMS,
        .instance = CM_CAN1,
    },
#endif
#ifdef BSP_USING_CAN2
    {
        {0},
        CAN2_INIT_PARAMS,
        .instance = CM_CAN2,
    },
#endif
#endif

#if defined (HC32F460)
#ifdef BSP_USING_CAN1
    {
        {0},
        CAN1_INIT_PARAMS,
        .instance = CM_CAN,
    },
#endif
#endif
};

static void _init_ll_struct_filter(can_device *p_can_dev);

#ifndef RT_CAN_USING_CANFD
static rt_uint32_t _get_can_baud_index(rt_uint32_t baud)
{
    rt_uint32_t len, index;

    len = sizeof(_g_baudrate_tab) / sizeof(_g_baudrate_tab[0]);
    for (index = 0; index < len; index++)
    {
        if (_g_baudrate_tab[index].baud_rate == baud)
            return index;
    }

    return 0; /* default baud is CAN1MBaud */
}
#endif

static rt_uint32_t _get_can_work_mode(rt_uint32_t mode)
{
    rt_uint32_t work_mode;
    switch (mode)
    {
    case RT_CAN_MODE_NORMAL:
        work_mode = CAN_WORK_MD_NORMAL;
        break;
    case RT_CAN_MODE_LISTEN:
        work_mode = CAN_WORK_MD_SILENT;
        break;
    case RT_CAN_MODE_LOOPBACK:
        work_mode = CAN_WORK_MD_ELB;
        break;
    case RT_CAN_MODE_LOOPBACKANLISTEN:
        work_mode = CAN_WORK_MD_ELB_SILENT;
        break;
    default:
        work_mode = CAN_WORK_MD_NORMAL;
        break;
    }

    return work_mode;
}

static uint32_t _get_filter_idx(struct rt_can_filter_config *p_filter_in)
{
    uint32_t filter_selected = 0;

    for (int i = 0; i < p_filter_in->count; i++)
    {
        if (p_filter_in->items[i].hdr_bank != -1)
        {
            filter_selected |= 1 << p_filter_in->items[i].hdr_bank;
        }
    }

    for (int i = 0; i < p_filter_in->count; i++)
    {
        if (p_filter_in->items[i].hdr_bank == -1)
        {
            for (int j = 0; j < FILTER_COUNT; j++)
            {
                if ((filter_selected & 1 << j) == 0)
                {
                    p_filter_in->items[i].hdr_bank = j;
                    filter_selected |= 1 << p_filter_in->items[i].hdr_bank;
                    break;
                }
            }
        }
    }

    return filter_selected;
}

static uint8_t _get_can_data_bytes_len(uint32_t dlc)
{
    uint8_t data_bytes = 0;

    dlc &= 0xFU;
    if (dlc <= 8U)
    {
        data_bytes = dlc;
    }
    else
    {
        switch (dlc)
        {
        case CAN_DLC12:
            data_bytes = 12U;
            break;
        case CAN_DLC16:
            data_bytes = 16U;
            break;
        case CAN_DLC20:
            data_bytes = 20U;
            break;
        case CAN_DLC24:
            data_bytes = 24U;
            break;
        case CAN_DLC32:
            data_bytes = 32U;
            break;
        case CAN_DLC48:
            data_bytes = 48U;
            break;
        case CAN_DLC64:
            data_bytes = 64U;
            break;
        default:
            /* Code should never touch here */
            break;
        }
    }

    return data_bytes;
}

static rt_bool_t _check_filter_params(struct rt_can_filter_config *p_filter_in)
{
    RT_ASSERT(p_filter_in != NULL);
    RT_ASSERT(p_filter_in->count <= FILTER_COUNT);

    for (int i = 0; i < p_filter_in->count; i++)
    {
        if (p_filter_in->items[i].hdr_bank != -1 && p_filter_in->items[i].hdr_bank >= FILTER_COUNT)
        {
            RT_ASSERT(p_filter_in->items[i].hdr_bank < FILTER_COUNT);
            return RT_FALSE;
        }
        if (p_filter_in->items[i].mode == 1)
        {
            RT_ASSERT(p_filter_in->items[i].mode == 0);
            return RT_FALSE;
        }
        if (p_filter_in->items[i].rtr == 1)
        {
            RT_ASSERT(p_filter_in->items[i].rtr == 0);
            return RT_FALSE;
        }
    }

    return RT_TRUE;
}

#ifdef RT_CAN_USING_CANFD
static uint32_t _get_can_clk_src(CM_CAN_TypeDef *CANx)
{
    uint32_t can_clk = 0;
    switch ((rt_uint32_t)CANx)
    {
#ifdef BSP_USING_CAN1
    case (rt_uint32_t)CM_CAN1:
        can_clk = CAN1_CLOCK_SEL;
        break;
#endif
#ifdef BSP_USING_CAN2
    case (rt_uint32_t)CM_CAN2:
        can_clk = CAN2_CLOCK_SEL;
        break;
#endif
    default:
        break;
    }
    return can_clk;
}

static rt_bool_t _get_can_bit_timing_default(uint32_t can_clk, rt_uint32_t baud, rt_uint32_t option,
        stc_can_bit_time_config_t *p_stc_bit_cfg)
{
    rt_uint32_t len, index;
    rt_bool_t found = RT_FALSE;

    len = sizeof(_g_baudrate_fd) / sizeof(_g_baudrate_fd[0]);
    for (index = 0; index < len; index++)
    {
        if ((_g_baudrate_fd[index].clk_src == can_clk) && \
                ((_g_baudrate_fd[index].phase & option) == option) \
           )
        {
            if (_g_baudrate_fd[index].baud == baud)
            {
                found = RT_TRUE;
                break;
            }
        }
    }
    if (found)
    {
        rt_memcpy(p_stc_bit_cfg, &_g_baudrate_fd[index].ll_bt, sizeof(stc_can_bit_time_config_t));
    }

    return found;
}

static inline void _get_can_bit_timing(stc_can_bit_time_config_t *p_ll_time, struct rt_can_bit_timing *p_cfg_time)
{
    p_ll_time->u32Prescaler = p_cfg_time->prescaler;
    p_ll_time->u32TimeSeg1 = p_cfg_time->num_seg1;
    p_ll_time->u32TimeSeg2 = p_cfg_time->num_seg2;
    p_ll_time->u32SJW = p_cfg_time->num_sjw;
}

static inline void _get_can_bit_timing_fd(stc_canfd_config_t *p_ll_time, struct rt_can_bit_timing *p_cfg_time)
{
    p_ll_time->stcBitCfg.u32Prescaler = p_cfg_time->prescaler;
    p_ll_time->stcBitCfg.u32TimeSeg1 = p_cfg_time->num_seg1;
    p_ll_time->stcBitCfg.u32TimeSeg2 = p_cfg_time->num_seg2;
    p_ll_time->stcBitCfg.u32SJW = p_cfg_time->num_sjw;
    p_ll_time->u8SSPOffset = p_cfg_time->num_sspoff;
    if (p_cfg_time->num_sspoff)
    {
        p_ll_time->u8TDC = CAN_FD_TDC_ENABLE;
    }
}

static rt_err_t _get_can_closest_prescaler(uint32_t num_tq_mul_prescaler, uint32_t start_prescaler,
        uint32_t max_tq, uint32_t min_tq)
{
    rt_bool_t has_found = RT_FALSE;
    uint32_t prescaler = start_prescaler;

    while (!has_found)
    {
        if ((num_tq_mul_prescaler / prescaler > max_tq) || (num_tq_mul_prescaler % prescaler != 0))
        {
            ++prescaler;
            continue;
        }
        else
        {
            has_found = RT_TRUE;
            break;
        }
    }

    uint32_t tq = num_tq_mul_prescaler / prescaler;
    if (tq * prescaler == num_tq_mul_prescaler)
    {
        has_found = RT_TRUE;
    }
    else if (tq < min_tq)
    {
        has_found = RT_FALSE;
    }

    return has_found ? prescaler : 0U;
}

static rt_err_t _calc_can_bit_timing(CM_CAN_TypeDef *CANx, int option, uint32_t baudrate,
                                     stc_can_bit_time_config_t *p_stc_bit_cfg)
{
    rt_err_t status = -RT_ERROR;
    uint32_t can_clk = _get_can_clk_src(CANx);
    if (_get_can_bit_timing_default(can_clk, baudrate, option, p_stc_bit_cfg) == RT_TRUE)
    {
        status = RT_EOK;
        return status;
    }

    do
    {
        uint8_t idx = 0;
        for (int i = 0; i < 3; i++)
        {
            if (option & (1 << i))
            {
                idx = (uint8_t)i;
                break;
            }
        }
        if ((idx >= 3) || (baudrate == 0U) ||
                (can_clk / baudrate < MIN_TQ_MUL_PRESCALE) || (p_stc_bit_cfg == NULL))
        {
            break;
        }

        const can_bit_timing_table_t *tbl = &_g_can_bit_timing_tbl[idx];
        if (can_clk / baudrate < tbl->tq_min)
        {
            break;
        }

        uint32_t num_tq_mul_prescaler = can_clk / baudrate;
        uint32_t start_prescaler = 1U;
        uint32_t num_seg1, num_seg2;
        rt_bool_t has_found = RT_FALSE;

        /* Find out the minimum prescaler */
        uint32_t current_prescaler;
        while (!has_found)
        {
            current_prescaler = _get_can_closest_prescaler(num_tq_mul_prescaler, start_prescaler,
                                tbl->tq_max,
                                tbl->tq_min);
            if ((current_prescaler < start_prescaler) || (current_prescaler > NUM_PRESCALE_MAX))
            {
                break;
            }
            uint32_t num_tq = num_tq_mul_prescaler / current_prescaler;

            num_seg2 = (num_tq - tbl->min_diff_seg1_minus_seg2) / 2U;
            num_seg1 = num_tq - num_seg2;
            while (num_seg2 > tbl->seg2_max)
            {
                num_seg2--;
                num_seg1++;
            }

            /* Recommended sample point is 75% - 80% */
            while ((num_seg1 * 1000U) / num_tq < CAN_SAMPLEPOINT_MIN)
            {
                ++num_seg1;
                --num_seg2;
            }

            if ((num_seg1 * 1000U) / num_tq > CAN_SAMPLEPOINT_MAX)
            {
                break;
            }

            if ((num_seg2 >= tbl->seg2_min) && (num_seg1 <= tbl->seg1_max))
            {
                has_found = RT_TRUE;
            }
            else
            {
                start_prescaler = current_prescaler + 1U;
            }
        }

        if (has_found)
        {
            uint32_t num_sjw = LL_MIN(tbl->sjw_max, num_seg2);
            p_stc_bit_cfg->u32TimeSeg1 = num_seg1;
            p_stc_bit_cfg->u32TimeSeg2 = num_seg2;
            p_stc_bit_cfg->u32SJW = num_sjw;
            p_stc_bit_cfg->u32Prescaler = current_prescaler;
            status = RT_EOK;
        }
    }
    while (RT_FALSE);

    return status;
}
#else
static rt_err_t _config_can20_baud(can_device *p_can_dev, void *arg)
{
    rt_uint32_t argval = (rt_uint32_t)arg;
    rt_uint32_t baud_index;
    rt_err_t rt_ret = RT_EOK;

    RT_ASSERT(IS_VALID_BAUD_RATE_CAN2_0(argval));
    if (argval == p_can_dev->rt_can.config.baud_rate)
    {
        return rt_ret;
    }

    baud_index = _get_can_baud_index(argval);
    p_can_dev->ll_init.stcBitCfg = _g_baudrate_tab[baud_index].ll_sbt;

    /* init can */
    CAN_Init(p_can_dev->instance, &p_can_dev->ll_init);
    p_can_dev->rt_can.config.baud_rate = argval;

    return rt_ret;
}
#endif

static rt_err_t _config_can_filter(can_device *p_can_dev, void *arg)
{
    struct rt_can_filter_config *p_filter_in = (struct rt_can_filter_config *)arg;
    if (_check_filter_params(p_filter_in) == RT_FALSE)
    {
        return -RT_EINVAL;
    }

    _init_ll_struct_filter(p_can_dev);
    uint32_t filter_select = _get_filter_idx(p_filter_in);
    p_can_dev->ll_init.u16FilterSelect = filter_select;
    for (int i = 0; i < p_filter_in->count; i++)
    {
        p_can_dev->ll_init.pstcFilter[i].u32ID = p_filter_in->items[i].id & 0x1FFFFFFF;
        /* rt-thread CAN mask, 1 mean filer, 0 mean ignore. *
            * HDSC HC32 CAN mask, 0 mean filer, 1 mean ignore. */
        p_can_dev->ll_init.pstcFilter[i].u32IDMask = (~p_filter_in->items[i].mask) & 0x1FFFFFFF;
        switch (p_filter_in->items[i].ide)
        {
        case (RT_CAN_STDID):
            p_can_dev->ll_init.pstcFilter[i].u32IDType = CAN_ID_STD;
            break;
        case (RT_CAN_EXTID):
            p_can_dev->ll_init.pstcFilter[i].u32IDType = CAN_ID_EXT;
            break;
        default:
            p_can_dev->ll_init.pstcFilter[i].u32IDType = CAN_ID_STD_EXT;
            break;
        }
    }
    (void)CAN_Init(p_can_dev->instance, &p_can_dev->ll_init);

    return RT_EOK;
}

static rt_err_t _config_can_work_mode(can_device *p_can_dev, void *arg)
{
    rt_err_t rt_ret = RT_EOK;
    rt_uint32_t argval = (rt_uint32_t) arg;

    if (argval == p_can_dev->rt_can.config.mode)
    {
        return rt_ret;
    }
    RT_ASSERT(IS_VALID_WORK_MODE(argval));

    p_can_dev->ll_init.u8WorkMode = _get_can_work_mode(argval);
    CAN_Init(p_can_dev->instance, &p_can_dev->ll_init);
    p_can_dev->rt_can.config.mode = argval;

    return rt_ret;
}

static rt_err_t _config_can_priv_mode(can_device *p_can_dev, void *arg)
{
    rt_err_t rt_ret = RT_EOK;
    rt_uint32_t argval = (rt_uint32_t) arg;

    RT_ASSERT(IS_VALID_PRIV_MODE(argval));
    p_can_dev->rt_can.config.privmode = argval;

    return rt_ret;
}

static void _config_can_int(can_device *p_can_dev, int cmd, void *arg)
{
    en_functional_state_t stat = ENABLE;
    rt_uint32_t flag = (rt_uint32_t)arg;

    if (cmd == RT_DEVICE_CTRL_CLR_INT)
    {
        if (flag == RT_DEVICE_CAN_INT_ERR)
        {
            RT_ASSERT(p_can_dev->init.single_trans_mode == RT_FALSE);
        }
        stat = DISABLE;
    }
    switch (flag)
    {
    case RT_DEVICE_FLAG_INT_RX:
        CAN_IntCmd(p_can_dev->instance, CAN_INT_RX, stat);
        CAN_IntCmd(p_can_dev->instance, CAN_INT_RX_BUF_WARN, stat);
        CAN_IntCmd(p_can_dev->instance, CAN_INT_RX_BUF_FULL, stat);
        CAN_IntCmd(p_can_dev->instance, CAN_INT_RX_OVERRUN, stat);
        break;
    case RT_DEVICE_FLAG_INT_TX:
        CAN_IntCmd(p_can_dev->instance, CAN_INT_STB_TX, stat);
        CAN_IntCmd(p_can_dev->instance, CAN_INT_PTB_TX, stat);
        break;
    case RT_DEVICE_CAN_INT_ERR:
        CAN_IntCmd(p_can_dev->instance, CAN_INT_ERR_INT, stat);
        CAN_IntCmd(p_can_dev->instance, CAN_INT_ARBITR_LOST, stat);
        CAN_IntCmd(p_can_dev->instance, CAN_INT_ERR_PASSIVE, stat);
        CAN_IntCmd(p_can_dev->instance, CAN_INT_BUS_ERR, stat);
        break;
    default:
        break;
    }
}

#ifdef RT_CAN_USING_CANFD
static void _init_ll_struct_canfd(can_device *p_can_dev)
{
    if (p_can_dev->ll_init.pstcCanFd == NULL)
    {
        p_can_dev->ll_init.pstcCanFd = (stc_canfd_config_t *)rt_malloc(sizeof(stc_canfd_config_t));
    }
    RT_ASSERT((p_can_dev->ll_init.pstcCanFd != RT_NULL));
    CAN_FD_StructInit(p_can_dev->ll_init.pstcCanFd);
    switch ((rt_uint32_t)p_can_dev->instance)
    {
#ifdef BSP_USING_CAN1
    case (rt_uint32_t)CM_CAN1:
        p_can_dev->ll_init.pstcCanFd->u8Mode = CAN1_CANFD_MODE;
        break;
#endif
#ifdef BSP_USING_CAN2
    case (rt_uint32_t)CM_CAN2:
        p_can_dev->ll_init.pstcCanFd->u8Mode = CAN2_CANFD_MODE;
        break;
#endif
    default:
        break;
    }
}

static rt_err_t _config_can_bit_timing(can_device *p_can_dev, void *arg)
{
    rt_err_t rt_ret = RT_EOK;

    struct rt_can_bit_timing_config *timing_configs = (struct rt_can_bit_timing_config *)arg;
    RT_ASSERT(timing_configs != RT_NULL);
    RT_ASSERT(timing_configs->count == 1 || timing_configs->count == 2);
    RT_ASSERT(timing_configs->items[0].num_sspoff == 0);

    _get_can_bit_timing(&p_can_dev->ll_init.stcBitCfg, &timing_configs->items[0]);
    if (timing_configs->count == 2)
    {
        _get_can_bit_timing_fd(p_can_dev->ll_init.pstcCanFd, &timing_configs->items[1]);
    }
    /* init can */
    CAN_Init(p_can_dev->instance, &p_can_dev->ll_init);
    p_can_dev->rt_can.config.can_timing = timing_configs->items[0];
    if (timing_configs->count == 2)
    {
        p_can_dev->rt_can.config.canfd_timing = timing_configs->items[1];
    }
    return rt_ret;
}


static rt_err_t _canfd_control(can_device *p_can_dev, int cmd, void *arg)
{
    rt_uint32_t argval;
    rt_err_t timing_stat;

    switch (cmd)
    {
    case RT_CAN_CMD_SET_BAUD:
        argval = (rt_uint32_t) arg;
        RT_ASSERT(IS_VALID_BAUD_RATE_CANFD_ARBITRATION(argval));
        if (p_can_dev->rt_can.config.baud_rate == argval)
        {
            break;
        }
        timing_stat = _calc_can_bit_timing(p_can_dev->instance, \
                                           CAN_BIT_TIMING_CANFD_ARBITRATION, \
                                           argval, \
                                           &p_can_dev->ll_init.stcBitCfg);
        if (timing_stat != RT_EOK)
        {
            return timing_stat;
        }
        CAN_Init(p_can_dev->instance, &p_can_dev->ll_init);
        p_can_dev->rt_can.config.baud_rate = argval;
        break;
    case RT_CAN_CMD_SET_CANFD:
        if (p_can_dev->rt_can.config.enable_canfd == argval)
        {
            break;
        }
        p_can_dev->rt_can.config.enable_canfd = (rt_uint32_t) argval;
        break;
    case RT_CAN_CMD_SET_BAUD_FD:
        argval = (rt_uint32_t) arg;
        RT_ASSERT(IS_VALID_BAUD_RATE_CANFD_DATA(argval));
        if (p_can_dev->rt_can.config.baud_rate_fd == argval)
        {
            break;
        }
        timing_stat = _calc_can_bit_timing(p_can_dev->instance, \
                                           CAN_BIT_TIMING_CANFD_DATA, \
                                           argval, \
                                           &p_can_dev->ll_init.pstcCanFd->stcBitCfg);
        if (timing_stat != RT_EOK)
        {
            return timing_stat;
        }
        p_can_dev->ll_init.pstcCanFd->u8SSPOffset = p_can_dev->ll_init.pstcCanFd->stcBitCfg.u32TimeSeg1;
        CAN_Init(p_can_dev->instance, &p_can_dev->ll_init);
        p_can_dev->rt_can.config.baud_rate_fd = argval;
        break;
    case RT_CAN_CMD_SET_BITTIMING:
        return _config_can_bit_timing(p_can_dev, arg);
    default:
        break;
    }

    return RT_EOK;
}
#endif

static rt_err_t _can_config(struct rt_can_device *can, struct can_configure *cfg)
{
    can_device *p_can_dev;
    rt_err_t rt_ret = RT_EOK;

    RT_ASSERT(can);
    RT_ASSERT(cfg);
    p_can_dev = (can_device *)rt_container_of(can, can_device, rt_can);
    RT_ASSERT(p_can_dev);
    RT_ASSERT(IS_VALID_WORK_MODE(cfg->mode));

    p_can_dev->ll_init.u8WorkMode = _get_can_work_mode(cfg->mode);
#ifdef RT_CAN_USING_CANFD
    if (cfg->use_bit_timing)
    {
        _get_can_bit_timing(&p_can_dev->ll_init.stcBitCfg, &cfg->can_timing);
        _get_can_bit_timing_fd(p_can_dev->ll_init.pstcCanFd, &cfg->canfd_timing);
    }
    else
    {
        RT_ASSERT(IS_VALID_BAUD_RATE_CANFD_ARBITRATION(cfg->baud_rate));
        RT_ASSERT(IS_VALID_BAUD_RATE_CANFD_DATA(cfg->baud_rate_fd));
        rt_ret = _calc_can_bit_timing(p_can_dev->instance, \
                                      CAN_BIT_TIMING_CANFD_ARBITRATION, \
                                      cfg->baud_rate, \
                                      &p_can_dev->ll_init.stcBitCfg);
        if (rt_ret != RT_EOK)
        {
            return rt_ret;
        }
        rt_ret = _calc_can_bit_timing(p_can_dev->instance, \
                                      CAN_BIT_TIMING_CANFD_DATA, \
                                      cfg->baud_rate_fd, \
                                      &p_can_dev->ll_init.pstcCanFd->stcBitCfg);
        if (rt_ret != RT_EOK)
        {
            return rt_ret;
        }
    }
    p_can_dev->ll_init.pstcCanFd->u8SSPOffset = p_can_dev->ll_init.pstcCanFd->stcBitCfg.u32TimeSeg1;
#else
    RT_ASSERT(IS_VALID_BAUD_RATE_CAN2_0(cfg->baud_rate));
    rt_uint32_t baud_index = _get_can_baud_index(cfg->baud_rate);
    p_can_dev->ll_init.stcBitCfg = _g_baudrate_tab[baud_index].ll_sbt;
#endif

    /* init can */
    CAN_Init(p_can_dev->instance, &p_can_dev->ll_init);

    struct can_configure pre_config = p_can_dev->rt_can.config;
    rt_memcpy(&p_can_dev->rt_can.config, cfg, sizeof(struct can_configure));
    /* restore unmodifiable member */
    if ((p_can_dev->rt_can.parent.open_flag & RT_DEVICE_OFLAG_OPEN) == RT_DEVICE_OFLAG_OPEN)
    {
        p_can_dev->rt_can.config.msgboxsz =  pre_config.msgboxsz;
        p_can_dev->rt_can.config.ticks = pre_config.ticks;
    }
#ifdef RT_CAN_USING_HDR
    p_can_dev->rt_can.config.maxhdr = pre_config.maxhdr;
#endif
    p_can_dev->rt_can.config.sndboxnumber = pre_config.sndboxnumber;

    return rt_ret;
}

static rt_err_t _can_control(struct rt_can_device *can, int cmd, void *arg)
{
    can_device *p_can_dev;

    RT_ASSERT(can != RT_NULL);
    p_can_dev = (can_device *)rt_container_of(can, can_device, rt_can);
    RT_ASSERT(p_can_dev);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
    case RT_DEVICE_CTRL_SET_INT:
        _config_can_int(p_can_dev, cmd, arg);
        break;
    case RT_CAN_CMD_SET_FILTER:
        return _config_can_filter(p_can_dev, arg);
    case RT_CAN_CMD_SET_MODE:
        return _config_can_work_mode(p_can_dev, arg);
    case RT_CAN_CMD_SET_BAUD:
#ifdef RT_CAN_USING_CANFD
        return _canfd_control(p_can_dev, cmd, arg);
#else
        return _config_can20_baud(p_can_dev, arg);
#endif
    case RT_CAN_CMD_SET_PRIV:
        return _config_can_priv_mode(p_can_dev, arg);
    case RT_CAN_CMD_GET_STATUS:
    {
        struct rt_can_status *rt_can_stat = (struct rt_can_status *)arg;
        stc_can_error_info_t stcErr = {0};
        CAN_GetErrorInfo(p_can_dev->instance, &stcErr);
        rt_can_stat->rcverrcnt = stcErr.u8RxErrorCount;
        rt_can_stat->snderrcnt = stcErr.u8TxErrorCount;
        rt_can_stat->lasterrtype = stcErr.u8ErrorType;
        rt_can_stat->errcode = CAN_GetStatusValue(p_can_dev->instance);
    }
    break;
#ifdef RT_CAN_USING_CANFD
    case RT_CAN_CMD_SET_CANFD:
    case RT_CAN_CMD_SET_BAUD_FD:
    case RT_CAN_CMD_SET_BITTIMING:
        return _canfd_control(p_can_dev, cmd, arg);
#endif
    default:
        return -(RT_EINVAL);

    }
    return RT_EOK;
}

static rt_ssize_t _can_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t box_num)
{
    struct rt_can_msg *pmsg = (struct rt_can_msg *) buf;
    stc_can_tx_frame_t stc_tx_frame = {0};
    int32_t ll_ret;

    RT_ASSERT(can != RT_NULL);
    can_device *p_can_dev = (can_device *)rt_container_of(can, can_device, rt_can);
    RT_ASSERT(p_can_dev);

    stc_tx_frame.u32ID = pmsg->id;
    if (RT_CAN_DTR == pmsg->rtr)
    {
        stc_tx_frame.RTR = 0;
    }
    else
    {
        stc_tx_frame.RTR = 1;
    }
#ifdef RT_CAN_USING_CANFD
    if (pmsg->fd_frame != 0)
    {
        RT_ASSERT(pmsg->len <= CAN_DLC64);
    }
    else
    {
        RT_ASSERT(pmsg->len <= CAN_DLC8);
    }
    stc_tx_frame.FDF = pmsg->fd_frame;
    stc_tx_frame.BRS = pmsg->brs;
#endif
    stc_tx_frame.DLC = pmsg->len & 0x0FU;
    /* Set up the IDE */
    stc_tx_frame.IDE = pmsg->ide;
    /* Set up the data field */
    uint32_t msg_len = _get_can_data_bytes_len(stc_tx_frame.DLC);
    rt_memcpy(&stc_tx_frame.au8Data, pmsg->data, msg_len);

    ll_ret = CAN_FillTxFrame(p_can_dev->instance, CAN_TX_BUF_PTB, &stc_tx_frame);
    if (ll_ret != LL_OK)
    {
        return -RT_ERROR;
    }
    /* Request transmission */
    CAN_StartTx(p_can_dev->instance, CAN_TX_REQ_PTB);

    return RT_EOK;
}

static rt_ssize_t _can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t fifo)
{
    int32_t ll_ret;
    struct rt_can_msg *pmsg;
    stc_can_rx_frame_t ll_rx_frame;

    RT_ASSERT(can != RT_NULL);
    can_device *p_can_dev = (can_device *)rt_container_of(can, can_device, rt_can);
    RT_ASSERT(p_can_dev);

    pmsg = (struct rt_can_msg *) buf;
    /* get data */
    ll_ret = CAN_GetRxFrame(p_can_dev->instance, &ll_rx_frame);
    if (ll_ret != LL_OK)
        return -RT_ERROR;

    /* get id */
    if (0 == ll_rx_frame.IDE)
    {
        pmsg->ide = RT_CAN_STDID;
    }
    else
    {
        pmsg->ide = RT_CAN_EXTID;
    }
    pmsg->id = ll_rx_frame.u32ID;
    /* get type */
    if (0 == ll_rx_frame.RTR)
    {
        pmsg->rtr = RT_CAN_DTR;
    }
    else
    {
        pmsg->rtr = RT_CAN_RTR;
    }
    /* get len */
    pmsg->len = ll_rx_frame.DLC;
    /* get hdr_index */
    pmsg->hdr_index = 0;
    pmsg->priv = 0;
#ifdef RT_CAN_USING_CANFD
    pmsg->fd_frame = ll_rx_frame.FDF;
    pmsg->brs = ll_rx_frame.BRS;
#endif
    uint32_t msg_len = _get_can_data_bytes_len(ll_rx_frame.DLC);
    rt_memcpy(pmsg->data, &ll_rx_frame.au8Data, msg_len);

    return RT_EOK;
}

static const struct rt_can_ops _can_ops =
{
    _can_config,
    _can_control,
    _can_sendmsg,
    _can_recvmsg,
};

rt_inline void _isr_can_rx(can_device *p_can_dev)
{
    if (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_RX_BUF_OVF) == SET)
    {
        /* RX overflow. */
        rt_hw_can_isr(&p_can_dev->rt_can, RT_CAN_EVENT_RXOF_IND);
        CAN_ClearStatus(p_can_dev->instance, CAN_FLAG_RX_BUF_OVF);
    }

    if (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_RX) == SET)
    {
        /* Received a frame. */
        CAN_ClearStatus(p_can_dev->instance, CAN_FLAG_RX);
        rt_hw_can_isr(&p_can_dev->rt_can, RT_CAN_EVENT_RX_IND);
    }

    if (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_RX_BUF_WARN) == SET)
    {
        /* RX buffer warning. */
        CAN_ClearStatus(p_can_dev->instance, CAN_FLAG_RX_BUF_WARN);
    }

    if (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_RX_BUF_FULL) == SET)
    {
        /* RX buffer full. */
        CAN_ClearStatus(p_can_dev->instance, CAN_FLAG_RX_BUF_FULL);
    }

    if (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_RX_OVERRUN) == SET)
    {
        /* RX buffer overrun. */
        CAN_ClearStatus(p_can_dev->instance, CAN_FLAG_RX_OVERRUN);
    }
}

rt_inline void _isr_can_tx(can_device *p_can_dev)
{
    rt_bool_t is_tx_done = RT_FALSE;
    rt_bool_t need_check_single_trans = RT_FALSE;

    if (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_TX_BUF_FULL) == SET)
    {
        /* TX buffer full. */
    }

    if (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_TX_ABORTED) == SET)
    {
        /* TX aborted. */
        CAN_ClearStatus(p_can_dev->instance, CAN_FLAG_TX_ABORTED);
    }

    if (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_PTB_TX) == SET)
    {
        /* PTB transmitted. */
        CAN_ClearStatus(p_can_dev->instance, CAN_FLAG_PTB_TX);
        if (p_can_dev->ll_init.u8PTBSingleShotTx == CAN_PTB_SINGLESHOT_TX_ENABLE)
        {
            need_check_single_trans = RT_TRUE;
        }
        else
        {
            is_tx_done = RT_TRUE;
        }
    }
    if (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_STB_TX) == SET)
    {
        /* STB transmitted. */
        CAN_ClearStatus(p_can_dev->instance, CAN_FLAG_STB_TX);
        if (p_can_dev->ll_init.u8STBSingleShotTx == CAN_STB_SINGLESHOT_TX_ENABLE)
        {
            need_check_single_trans = RT_TRUE;
        }
        else
        {
            is_tx_done = RT_TRUE;
        }
    }
    if (need_check_single_trans)
    {
        if ((CAN_GetStatus(p_can_dev->instance, CAN_FLAG_BUS_ERR) != SET) \
                || (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_ARBITR_LOST) != SET))
        {
            is_tx_done = RT_TRUE;
        }
    }
    if (is_tx_done)
    {
        rt_hw_can_isr(&p_can_dev->rt_can, RT_CAN_EVENT_TX_DONE);
    }


    if (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_ARBITR_LOST) == SET)
    {
        rt_hw_can_isr(&p_can_dev->rt_can, RT_CAN_EVENT_TX_FAIL);
        CAN_ClearStatus(p_can_dev->instance, CAN_FLAG_ARBITR_LOST);
    }


}

rt_inline void _isr_can_err(can_device *p_can_dev)
{
    if (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_ERR_INT) == SET)
    {
        /* ERROR. */
        CAN_ClearStatus(p_can_dev->instance, CAN_FLAG_ERR_INT);
    }
    if (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_BUS_ERR) == SET)
    {
        /* BUS ERROR. */
        CAN_ClearStatus(p_can_dev->instance, CAN_FLAG_BUS_ERR);
    }
    if (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_ERR_PASSIVE) == SET)
    {
        /* error-passive to error-active or error-active to error-passive. */
        CAN_ClearStatus(p_can_dev->instance, CAN_FLAG_ERR_PASSIVE);
    }

    if (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_TEC_REC_WARN) == SET)
    {
        /* TEC or REC reached warning limit. */
        CAN_ClearStatus(p_can_dev->instance, CAN_FLAG_TEC_REC_WARN);
    }

    if (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_BUS_OFF) == SET)
    {
        /* BUS OFF. */
    }
}

rt_inline void _isr_ttcan(can_device *p_can_dev)
{
    if (CAN_TTC_GetStatus(p_can_dev->instance, CAN_TTC_FLAG_TIME_TRIG) == SET)
    {
        /* Time trigger interrupt. */
        CAN_TTC_ClearStatus(p_can_dev->instance, CAN_TTC_FLAG_TIME_TRIG);
    }

    if (CAN_TTC_GetStatus(p_can_dev->instance, CAN_TTC_FLAG_TRIG_ERR) == SET)
    {
        /* Trigger error interrupt. */
    }

    if (CAN_TTC_GetStatus(p_can_dev->instance, CAN_TTC_FLAG_WATCH_TRIG) == SET)
    {
        /* Watch trigger interrupt. */
        CAN_TTC_ClearStatus(p_can_dev->instance, CAN_TTC_FLAG_WATCH_TRIG);
    }
}

static void _isr_can(can_device *p_can_dev)
{
    stc_can_error_info_t stcErr;

    (void)CAN_GetErrorInfo(p_can_dev->instance, &stcErr);
    _isr_can_rx(p_can_dev);
    _isr_can_tx(p_can_dev);
    _isr_can_err(p_can_dev);
    _isr_ttcan(p_can_dev);
}

#if defined(BSP_USING_CAN1)
static void _irq_handler_can1(void)
{
    rt_interrupt_enter();
    _isr_can(&_g_can_dev_array[CAN1_INDEX]);
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_CAN2)
static void _irq_handler_can2(void)
{
    rt_interrupt_enter();
    _isr_can(&_g_can_dev_array[CAN2_INDEX]);
    rt_interrupt_leave();
}
#endif

static void _enable_can_clock(void)
{
#if defined(HC32F4A0)
#if defined(BSP_USING_CAN1)
    FCG_Fcg1PeriphClockCmd(FCG1_PERIPH_CAN1, ENABLE);
#endif
#if   defined(BSP_USING_CAN2)
    FCG_Fcg1PeriphClockCmd(FCG1_PERIPH_CAN2, ENABLE);
#endif
#endif

#if defined(HC32F460)
#if defined(BSP_USING_CAN1)
    FCG_Fcg1PeriphClockCmd(FCG1_PERIPH_CAN, ENABLE);
#endif
#endif
}

static void _config_can_irq(void)
{
    struct hc32_irq_config irq_config;
#if defined(BSP_USING_CAN1)
    irq_config.irq_num = BSP_CAN1_IRQ_NUM;
    irq_config.int_src = CAN1_INT_SRC;
    irq_config.irq_prio = BSP_CAN1_IRQ_PRIO;
    /* register interrupt */
    hc32_install_irq_handler(&irq_config,
                             _irq_handler_can1,
                             RT_TRUE);
#endif
#if defined(BSP_USING_CAN2)
    irq_config.irq_num = BSP_CAN2_IRQ_NUM;
    irq_config.int_src = CAN2_INT_SRC;
    irq_config.irq_prio = BSP_CAN2_IRQ_PRIO;
    /* register interrupt */
    hc32_install_irq_handler(&irq_config,
                             _irq_handler_can2,
                             RT_TRUE);
#endif
}

static void _init_ll_struct_filter(can_device *p_can_dev)
{
    if (p_can_dev->ll_init.pstcFilter == RT_NULL)
    {
        p_can_dev->ll_init.pstcFilter = (stc_can_filter_config_t *)rt_malloc(sizeof(stc_can_filter_config_t) * FILTER_COUNT);
    }
    RT_ASSERT((p_can_dev->ll_init.pstcFilter != RT_NULL));

    rt_memset(p_can_dev->ll_init.pstcFilter, 0, sizeof(stc_can_filter_config_t) * FILTER_COUNT);
    p_can_dev->ll_init.pstcFilter[0].u32ID = 0U;
    p_can_dev->ll_init.pstcFilter[0].u32IDMask = 0x1FFFFFFF;
    p_can_dev->ll_init.pstcFilter[0].u32IDType = CAN_ID_STD_EXT;
    p_can_dev->ll_init.u16FilterSelect = CAN_FILTER1;
}

static void _init_struct_by_static_cfg(can_device *p_can_dev)
{
    struct can_configure rt_can_config  = CANDEFAULTCONFIG;

    rt_can_config.privmode = RT_CAN_MODE_NOPRIV;
    rt_can_config.ticks = 50;
#ifdef RT_CAN_USING_HDR
    rt_can_config.maxhdr = FILTER_COUNT;
#endif
#ifdef RT_CAN_USING_CANFD
    rt_can_config.baud_rate_fd = CANFD_DATA_BAUD_1M;
#endif
    rt_can_config.sndboxnumber = 1;
    p_can_dev->rt_can.config = rt_can_config;

    if (p_can_dev->init.single_trans_mode)
    {
        p_can_dev->ll_init.u8PTBSingleShotTx = CAN_PTB_SINGLESHOT_TX_ENABLE;
    }

#ifdef RT_CAN_USING_CANFD
    _init_ll_struct_canfd(p_can_dev);
#endif
    _init_ll_struct_filter(p_can_dev);

}

extern rt_err_t rt_hw_board_can_init(CM_CAN_TypeDef *CANx);
extern void CanPhyEnable(void);
int rt_hw_can_init(void)
{
    _config_can_irq();
    _enable_can_clock();
    CanPhyEnable();
    int result = RT_EOK;
    uint32_t i = 0;
    for (; i < CAN_INDEX_MAX; i++)
    {
        CAN_StructInit(&_g_can_dev_array[i].ll_init);
        _init_struct_by_static_cfg(&_g_can_dev_array[i]);

        /* register CAN device */
        rt_hw_board_can_init(_g_can_dev_array[i].instance);
        rt_hw_can_register(&_g_can_dev_array[i].rt_can, \
                           _g_can_dev_array[i].init.name,
                           &_can_ops,
                           &_g_can_dev_array[i]);
    }

    return result;
}

INIT_DEVICE_EXPORT(rt_hw_can_init);
#endif

#endif /* BSP_USING_CAN */

/************************** end of file ******************/
