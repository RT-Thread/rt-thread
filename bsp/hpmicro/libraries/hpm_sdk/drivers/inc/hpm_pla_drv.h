/*
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_PLA_DRV_H
#define HPM_PLA_DRV_H

#include "hpm_common.h"
#include "hpm_pla_regs.h"

/**
 * @brief PLA driver APIs
 * @defgroup pla_interface PLA driver APIs
 * @ingroup io_interfaces
 * @{
 */

#define PLA_AOI_16TO8_SIGNAL_NUM    (16U)
#define PLA_AOI_8TO7_SIGNAL_NUM    (8U)
#define PLA_CHN_CFG_ACTIVE_WORD     (0xF00DU)

#define PLA_AOI_16TO8_CONNECT_(input, value) \
                PLA_CHN_AOI_16TO8_AOI_16TO8_##input##_SET(value)
/**
 * @brief Input signal configuration for synthetic aoi_16to8
 *
 */
#define PLA_AOI_16TO8_CONNECT(input_signal, operation) \
                PLA_AOI_16TO8_CONNECT_(input_signal, operation)

/**
 * @brief aoi_16to8 operation on input signals
 *
 */
typedef enum pla_aoi_signal_operation_type {
    pla_aoi_operation_and_0 = 0,      /**< signal & 0 */
    pla_aoi_operation_and_1 = 1,      /**< signal & 1 */
    pla_aoi_operation_xor_1 = 2,      /**< signal xor 1 */
    pla_aoi_operation_or_1 = 3,       /**< signal | 1 */
} pla_aoi_signal_operation_type_t;

typedef enum pla_filter_sw_inject_type {
    pla_filter_sw_inject_low = 0,
    pla_filter_sw_inject_height = 1,
    pla_filter_sw_inject_disable = 2,
} pla_filter_sw_inject_type_t;

/**
 * @brief aoi channel index
 *
 */
typedef enum pla_channel_type {
    pla_chn_0 = PLA_CHN_0,      /**< channel 0 */
    pla_chn_1 = PLA_CHN_1,      /**< channel 1 */
    pla_chn_2 = PLA_CHN_2,      /**< channel 2 */
    pla_chn_3 = PLA_CHN_3,      /**< channel 3 */
    pla_chn_4 = PLA_CHN_4,      /**< channel 4 */
    pla_chn_5 = PLA_CHN_5,      /**< channel 5 */
    pla_chn_6 = PLA_CHN_6,      /**< channel 6 */
    pla_chn_7 = PLA_CHN_7,      /**< channel 7 */
} pla_channel_type_t;

/**
 * @brief Raw input signal for aoi16to8 module
 *
 */
typedef enum pla_aoi_16to8_input_signal_type {
    pla_level1_filter_out_0 = 0,
    pla_level1_filter_out_1 = 1,
    pla_level1_filter_out_2 = 2,
    pla_level1_filter_out_3 = 3,
    pla_level1_filter_out_4 = 4,
    pla_level1_filter_out_5 = 5,
    pla_level1_filter_out_6 = 6,
    pla_level1_filter_out_7 = 7,
    pla_level1_filter_out_8 = 8,
    pla_level1_filter_out_9 = 9,
    pla_level1_filter_out_10 = 10,
    pla_level1_filter_out_11 = 11,
    pla_level1_filter_out_12 = 12,
    pla_level1_filter_out_13 = 13,
    pla_level1_filter_out_14 = 14,
    pla_level1_filter_out_15 = 15,
} pla_aoi_16to8_input_signal_type_t;

/**
 * @brief aoi_16to8 channel index
 *
 */
typedef enum pla_aoi_16to8_channel_type {
    pla_aoi_16to8_chn_0 = PLA_CHN_AOI_16TO8_AOI_16TO8_00,      /**< channel 0 */
    pla_aoi_16to8_chn_1 = PLA_CHN_AOI_16TO8_AOI_16TO8_01,      /**< channel 1 */
    pla_aoi_16to8_chn_2 = PLA_CHN_AOI_16TO8_AOI_16TO8_02,      /**< channel 2 */
    pla_aoi_16to8_chn_3 = PLA_CHN_AOI_16TO8_AOI_16TO8_03,      /**< channel 3 */
    pla_aoi_16to8_chn_4 = PLA_CHN_AOI_16TO8_AOI_16TO8_04,      /**< channel 4 */
    pla_aoi_16to8_chn_5 = PLA_CHN_AOI_16TO8_AOI_16TO8_05,      /**< channel 5 */
    pla_aoi_16to8_chn_6 = PLA_CHN_AOI_16TO8_AOI_16TO8_06,      /**< channel 6 */
    pla_aoi_16to8_chn_7 = PLA_CHN_AOI_16TO8_AOI_16TO8_07,      /**< channel 7 */
} pla_aoi_16to8_channel_type_t;

/**
 * @brief aoi_16to8 config unit
 *
 */
typedef struct pla_aoi_16to8_cfg_unit {
    pla_aoi_16to8_input_signal_type_t signal;
    pla_aoi_signal_operation_type_t op;
} pla_aoi_16to8_cfg_unit_t;

/**
 * @brief aoi_16to8 channel config
 *
 */
typedef struct pla_aoi_16to8_chn_cfg {
    pla_channel_type_t chn;     /**< pla channel */
    pla_aoi_16to8_channel_type_t aoi_16to8_chn;     /**< aoi_16to8 channel */
    pla_aoi_16to8_cfg_unit_t input[PLA_AOI_16TO8_SIGNAL_NUM]; /**< Configuration of each aoi_16to8 input signal */
} pla_aoi_16to8_chn_cfg_t;

/**
 * @brief aoi_8_to_7 input signal
 *
 */
typedef enum pla_aoi_8to7_input_signal_type {
    pla_level2_filter_out_0 = 0,
    pla_level2_filter_out_1 = 1,
    pla_level2_filter_out_2 = 2,
    pla_level2_filter_out_3 = 3,
    pla_level2_filter_out_4 = 4,
    pla_level2_filter_out_5 = 5,
    pla_level2_filter_out_6 = 6,
    pla_level2_filter_out_7 = 7,
} pla_aoi_8to7_input_signal_type_t;

/**
 * @brief aoi_8to7 channel number
 *
 */
typedef enum pla_aoi_8to7_channel_type {
    pla_aoi_8to7_chn_0 = 0,      /**< channel 0 */
    pla_aoi_8to7_chn_1 = 1,      /**< channel 1 */
    pla_aoi_8to7_chn_2 = 2,      /**< channel 2 */
    pla_aoi_8to7_chn_3 = 3,      /**< channel 3 */
    pla_aoi_8to7_chn_4 = 4,      /**< channel 4 */
    pla_aoi_8to7_chn_5 = 5,      /**< channel 5 */
    pla_aoi_8to7_chn_6 = 6,      /**< channel 6 */
} pla_aoi_8to7_channel_type_t;


/**
 * @brief aoi_8to7 config unit
 *
 */
typedef struct pla_aoi_8to7_cfg_unit {
    pla_aoi_8to7_input_signal_type_t signal;
    pla_aoi_signal_operation_type_t op;
} pla_aoi_8to7_cfg_unit_t;

/**
 * @brief aoi_8_to_7 channel config
 *
 */
typedef struct pla_aoi_8to7_chn_cfg {
    pla_channel_type_t chn;     /**< pla channel */
    pla_aoi_8to7_channel_type_t aoi_8to7_chn;     /**< aoi_16to8 channel */
    pla_aoi_8to7_cfg_unit_t input[PLA_AOI_8TO7_SIGNAL_NUM]; /**< Configuration of each aoi_16to8 input signal */
} pla_aoi_8to7_chn_cfg_t;

/**
 * @brief pla filter config
 *
 */
typedef union pla_filter_cfg {
    struct {
        uint32_t sync_edge_filter_disable:1;
        uint32_t software_inject:2;
        uint32_t filter_reverse:1;
        uint32_t edge_dect_en:1;
        uint32_t nege_edge_dect_en:1;
        uint32_t pose_edge_dect_en:1;
        uint32_t filter_sync_level:1;
        uint32_t filter_ext_en:1;
        uint32_t reserved0:3;
        uint32_t filter_ext_type:3;
        uint32_t reserved1:1;
        uint32_t filter_ext_counter:16;
    };
    uint32_t val;
} pla_filter_cfg_t;

/**
 * @brief pla function selection config
 *
 */
typedef union pla_ff_cfg {
    struct {
        uint32_t sel_cfg_ff_type:3;
        uint32_t sel_clk_source:1;
        uint32_t sel_adder_minus:1;
        uint32_t reserved0:11;
        uint32_t dis_osc_loop_clamp:1;
        uint32_t osc_loop_clamp_value:1;
        uint32_t reserved1:14;
    };
    uint32_t val;
} pla_ff_cfg_t;

/**
 * @brief pla configurable functions
 *
 */
typedef enum pla_ff_type {
    pla_ff_type_dff = 0,
    pla_ff_type_level3_filter0 = 1,
    pla_ff_type_dual_edge_DFF = 2,
    pla_ff_type_trigger_ff = 3,
    pla_ff_type_jk_ff = 4,
    pla_ff_type_latch = 5,
    pla_ff_type_adder_minus = 6
} pla_ff_type_t;


typedef enum pla_filter1_inchannel_type {
    pla_filter1_inchn0 = PLA_FILTER_1ST_PLA_IN_FRIST_FILTER_PLA_IN_0,
    pla_filter1_inchn1 = PLA_FILTER_1ST_PLA_IN_FRIST_FILTER_PLA_IN_1,
    pla_filter1_inchn2 = PLA_FILTER_1ST_PLA_IN_FRIST_FILTER_PLA_IN_2,
    pla_filter1_inchn3 = PLA_FILTER_1ST_PLA_IN_FRIST_FILTER_PLA_IN_3,
    pla_filter1_inchn4 = PLA_FILTER_1ST_PLA_IN_FRIST_FILTER_PLA_IN_4,
    pla_filter1_inchn5 = PLA_FILTER_1ST_PLA_IN_FRIST_FILTER_PLA_IN_5,
    pla_filter1_inchn6 = PLA_FILTER_1ST_PLA_IN_FRIST_FILTER_PLA_IN_6,
    pla_filter1_inchn7 = PLA_FILTER_1ST_PLA_IN_FRIST_FILTER_PLA_IN_7,
} pla_filter1_inchannel_type_t;

typedef enum pla_filter1_outchannel_type {
    pla_filter1_outchn0 = PLA_FILTER_1ST_PLA_OUT_FRIST_FILTER_PLA_OUT_0,
    pla_filter1_outchn1 = PLA_FILTER_1ST_PLA_OUT_FRIST_FILTER_PLA_OUT_1,
    pla_filter1_outchn2 = PLA_FILTER_1ST_PLA_OUT_FRIST_FILTER_PLA_OUT_2,
    pla_filter1_outchn3 = PLA_FILTER_1ST_PLA_OUT_FRIST_FILTER_PLA_OUT_3,
    pla_filter1_outchn4 = PLA_FILTER_1ST_PLA_OUT_FRIST_FILTER_PLA_OUT_4,
    pla_filter1_outchn5 = PLA_FILTER_1ST_PLA_OUT_FRIST_FILTER_PLA_OUT_5,
    pla_filter1_outchn6 = PLA_FILTER_1ST_PLA_OUT_FRIST_FILTER_PLA_OUT_6,
    pla_filter1_outchn7 = PLA_FILTER_1ST_PLA_OUT_FRIST_FILTER_PLA_OUT_7,
} pla_filter1_outchannel_type_t;


typedef enum pla_filter2_channel_type {
    pla_filter2_chn0 = PLA_CHN_FILTER_2ND_SECOND_FILTER_0,
    pla_filter2_chn1 = PLA_CHN_FILTER_2ND_SECOND_FILTER_1,
    pla_filter2_chn2 = PLA_CHN_FILTER_2ND_SECOND_FILTER_2,
    pla_filter2_chn3 = PLA_CHN_FILTER_2ND_SECOND_FILTER_3,
    pla_filter2_chn4 = PLA_CHN_FILTER_2ND_SECOND_FILTER_4,
    pla_filter2_chn5 = PLA_CHN_FILTER_2ND_SECOND_FILTER_5,
    pla_filter2_chn6 = PLA_CHN_FILTER_2ND_SECOND_FILTER_6,
    pla_filter2_chn7 = PLA_CHN_FILTER_2ND_SECOND_FILTER_7,
} pla_filter2_channel_type_t;

typedef enum pla_filter3_channel_type {
    pla_filter3_chn0 = PLA_CHN_FILTER_3RD_THIRD_FILTER_0,
    pla_filter3_chn1 = PLA_CHN_FILTER_3RD_THIRD_FILTER_1,
    pla_filter3_chn2 = PLA_CHN_FILTER_3RD_THIRD_FILTER_2,
    pla_filter3_chn3 = PLA_CHN_FILTER_3RD_THIRD_FILTER_3,
    pla_filter3_chn4 = PLA_CHN_FILTER_3RD_THIRD_FILTER_4,
    pla_filter3_chn5 = PLA_CHN_FILTER_3RD_THIRD_FILTER_5,
    pla_filter3_chn6 = PLA_CHN_FILTER_3RD_THIRD_FILTER_6,
} pla_filter3_channel_type_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Configure one channel of aoi_16to8
 *
 * @param pla @ref PLA_Type
 * @param cfg @ref pla_aoi_16to8_cfg_t
 */
void pla_set_aoi_16to8_one_channel(PLA_Type * pla,
                                    pla_aoi_16to8_chn_cfg_t *cfg);

/**
 * @brief Get one channel of aoi_16to8
 *
 * @param pla @ref PLA_Type
 * @param chn @ref pla_channel_type_t
 * @param aoi_16to8_chn @ref pla_aoi_16to8_channel_type_t
 * @param cfg @ref pla_aoi_16to8_chn_cfg_t
 */
void pla_get_aoi_16to8_one_channel(PLA_Type *pla,
                                    pla_channel_type_t chn,
                                    pla_aoi_16to8_channel_type_t aoi_16to8_chn,
                                    pla_aoi_16to8_chn_cfg_t *cfg);

/**
 * @brief Set one signal of aoi_16to8
 *
 * @param pla @ref PLA_Type
 * @param chn @ref pla_channel_type_t
 * @param aoi_16to8_chn @ref pla_aoi_16to8_channel_type_t
 * @param cfg @ref pla_aoi_16to8_cfg_unit_t
 */
static inline void pla_set_aoi_16to8_input_signal(PLA_Type *pla,
                                    pla_channel_type_t chn,
                                    pla_aoi_16to8_channel_type_t aoi_16to8_chn,
                                    pla_aoi_16to8_cfg_unit_t *cfg)
{
    pla->CHN[chn].AOI_16TO8[aoi_16to8_chn] = pla->CHN[chn].AOI_16TO8[aoi_16to8_chn] &
                            ~(((uint32_t)cfg->op) << (cfg->signal << 1));
}

/**
 * @brief Get one signal of aoi_16to8
 *
 * @param pla @ref PLA_Type
 * @param chn @ref pla_channel_type_t
 * @param aoi_16to8_chn @ref pla_aoi_16to8_channel_type_t
 * @param signal @ref pla_aoi_16to8_input_signal_type_t
 * @param cfg @ref pla_aoi_16to8_cfg_unit_t
 */
static inline void pla_get_aoi_16to8_input_signal(PLA_Type *pla,
                                    pla_channel_type_t chn,
                                    pla_aoi_16to8_channel_type_t aoi_16to8_chn,
                                    pla_aoi_16to8_input_signal_type_t signal,
                                    pla_aoi_16to8_cfg_unit_t *cfg)
{
    cfg->op = (pla->CHN[chn].AOI_16TO8[aoi_16to8_chn] >> (signal << 1)) & 0x03;
    cfg->signal = signal;
}


/**
 * @brief Configure one channel of aoi_8to7
 *
 * @param pla @ref PLA_Type
 * @param cfg @ref pla_aoi_8to7_chn_cfg_t
 */
void pla_set_aoi_8to7_one_channel(PLA_Type *pla,
                                    pla_aoi_8to7_chn_cfg_t *cfg);

/**
 * @brief Get one channel of aoi_8to7
 *
 * @param pla @ref PLA_Type
 * @param cfg @ref pla_aoi_8to7_chn_cfg_t
 */
void pla_get_aoi_8to7_one_channel(PLA_Type *pla,
                                    pla_aoi_8to7_chn_cfg_t *cfg);

/**
 * @brief Configure one signal of aoi_8to7
 *
 * @param pla @ref PLA_Type
 * @param chn @ref pla_channel_type_t
 * @param aoi_16to8_chn @ref pla_aoi_8to7_channel_type_t
 * @param cfg @ref pla_aoi_8to7_cfg_unit_t
 */
void pla_set_aoi_8to7_input_signal(PLA_Type *pla,
                                    pla_channel_type_t chn,
                                    pla_aoi_8to7_channel_type_t aoi_8to7_chn,
                                    pla_aoi_8to7_cfg_unit_t *cfg);

/**
 * @brief Get one signal of aoi_8to7
 *
 * @param pla @ref PLA_Type
 * @param chn @ref pla_channel_type_t
 * @param aoi_8to7_chn @ref pla_aoi_8to7_channel_type_t
 * @param signal @ref pla_aoi_8to7_input_signal_type_t
 * @param cfg @ref pla_aoi_8to7_cfg_unit_t
 */
void pla_get_aoi_8to7_input_signal(PLA_Type *pla,
                                    pla_channel_type_t chn,
                                    pla_aoi_8to7_channel_type_t aoi_8to7_chn,
                                    pla_aoi_8to7_input_signal_type_t signal,
                                    pla_aoi_8to7_cfg_unit_t *cfg);

/**
 * @brief Configure filter1 out
 *
 * @param pla @ref PLA_Type
 * @param filter1_out_chn @ref pla_filter1_outchannel_type_t
 * @param cfg @ref pla_filter_cfg_t
 */
static inline void pla_set_filter1_out(PLA_Type *pla,
                                    pla_filter1_outchannel_type_t filter1_out_chn,
                                    pla_filter_cfg_t *cfg)
{
    pla->FILTER_1ST_PLA_OUT[filter1_out_chn] = cfg->val;
}

/**
 * @brief Get filter1 out
 *
 * @param pla @ref PLA_Type
 * @param filter1_out_chn @ref pla_filter1_outchannel_type_t
 * @param cfg @ref pla_filter_cfg_t
 */
static inline void pla_get_filter1_out(PLA_Type *pla,
                                    pla_filter1_outchannel_type_t filter1_out_chn,
                                    pla_filter_cfg_t *cfg)
{
    cfg->val = pla->FILTER_1ST_PLA_OUT[filter1_out_chn];
}

/**
 * @brief Configure filter1 in
 *
 * @param pla @ref PLA_Type
 * @param filter1_in_chn @ref pla_filter1_inchannel_type_t
 * @param cfg @ref pla_filter_cfg_t
 */
static inline void pla_set_filter1_in(PLA_Type *pla,
                                    pla_filter1_inchannel_type_t filter1_in_chn,
                                    pla_filter_cfg_t *cfg)
{
    pla->FILTER_1ST_PLA_IN[filter1_in_chn] = cfg->val;
}

/**
 * @brief Get filter 1
 *
 * @param pla @ref PLA_Type
 * @param filter1_in_chn @ref pla_filter1_inchannel_type_t
 * @param cfg @ref pla_filter_cfg_t
 */
static inline void pla_get_filter1_in(PLA_Type *pla,
                                    pla_filter1_inchannel_type_t filter1_in_chn,
                                    pla_filter_cfg_t *cfg)
{
    cfg->val = pla->FILTER_1ST_PLA_IN[filter1_in_chn];
}

/**
 * @brief Configure filter 2
 *
 * @param pla @ref PLA_Type
 * @param chn @ref pla_channel_type_t
 * @param filter2_chn @ref pla_filter2_channel_type_t
 * @param cfg @ref pla_filter_cfg_t
 */
static inline void pla_set_filter2(PLA_Type *pla,
                                    pla_channel_type_t chn,
                                    pla_filter2_channel_type_t filter2_chn,
                                    pla_filter_cfg_t *cfg)
{
    pla->CHN[chn].FILTER_2ND[filter2_chn] = cfg->val;
}

/**
 * @brief Get filter2
 *
 * @param pla @ref PLA_Type
 * @param chn @ref pla_channel_type_t
 * @param filter2_chn @ref pla_filter2_channel_type_t
 * @param cfg @ref pla_filter_cfg_t
 */
static inline void pla_get_filter2(PLA_Type *pla,
                                    pla_channel_type_t chn,
                                    pla_filter2_channel_type_t filter2_chn,
                                    pla_filter_cfg_t *cfg)
{
    cfg->val = pla->CHN[chn].FILTER_2ND[filter2_chn];
}

/**
 * @brief Configure filter3
 *
 * @param pla @ref PLA_Type
 * @param chn @ref pla_channel_type_t
 * @param filter3_chn @ref pla_filter3_channel_type_t
 * @param cfg @ref pla_filter_cfg_t
 */
static inline void pla_set_filter3(PLA_Type *pla,
                                    pla_channel_type_t chn,
                                    pla_filter3_channel_type_t filter3_chn,
                                    pla_filter_cfg_t *cfg)
{
    pla->CHN[chn].FILTER_3RD[filter3_chn] = cfg->val;
}

/**
 * @brief Get filter3
 *
 * @param pla @ref PLA_Type
 * @param chn @ref pla_channel_type_t
 * @param filter3_chn @ref pla_filter3_channel_type_t
 * @param cfg @ref pla_filter_cfg_t
 */
static inline void pla_get_filter3(PLA_Type *pla,
                                    pla_channel_type_t chn,
                                    pla_filter3_channel_type_t filter3_chn,
                                    pla_filter_cfg_t *cfg)
{
    cfg->val = pla->CHN[chn].FILTER_3RD[filter3_chn];
}

/**
 * @brief Set ff function
 *
 * @param pla @ref PLA_Type
 * @param chn @ref pla_channel_type_t
 * @param cfg @ref pla_ff_cfg_t
 */
static inline void pla_set_ff(PLA_Type *pla,
                                pla_channel_type_t chn,
                                pla_ff_cfg_t *cfg)
{
    pla->CHN[chn].CFG_FF = cfg->val;
}

/**
 * @brief Get ff function
 *
 * @param pla @ref PLA_Type
 * @param chn @ref pla_channel_type_t
 * @param cfg @ref pla_ff_cfg_t
 */
static inline void pla_get_ff(PLA_Type *pla,
                                pla_channel_type_t chn,
                                pla_ff_cfg_t *cfg)
{
    cfg->val = pla->CHN[chn].CFG_FF;
}

/**
 * @brief enable pla channel
 *
 * @param pla @ref PLA_Type
 * @param chn @ref pla_channel_type_t
 */
static inline void pla_channel_enable(PLA_Type *pla,
                                    pla_channel_type_t chn)
{
    pla->CHN_CFG_ACTIVE[chn] = PLA_CHN_CFG_ACTIVE_WORD;
}

/**
 * @brief disable pla channel
 *
 * @param pla @ref PLA_Type
 * @param chn @ref pla_channel_type_t
 */
static inline void pla_channel_disable(PLA_Type *pla,
                                    pla_channel_type_t chn)
{
    pla->CHN_CFG_ACTIVE[chn] = false;
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* HPM_PLA_DRV_H */

