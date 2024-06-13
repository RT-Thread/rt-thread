/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_OPAMP_DRV_H
#define HPM_OPAMP_DRV_H

#include "hpm_common.h"
#include "hpm_opamp_regs.h"
#include "hpm_soc_feature.h"

/**
 * @brief OPMAP driver APIs
 * @defgroup opamp_interface OPAMP driver APIs
 * @ingroup io_interfaces
 * @{
 *
 */
#define OPAMP_MODE_FOLLOW_KEY   (0x06)
#define OPAMP_MODE_INVERT_INDEX0_KEY   (0x08)
#define OPAMP_MODE_INVERT_INDEX1_KEY   (0x18)
#define OPAMP_MODE_NON_INVERT_INDEX0_KEY   (0x01)
#define OPAMP_MODE_NON_INVERT_INDEX1_KEY   (0x09)
#define OPAMP_MODE_NON_INVERT_INDEX2_KEY   (0x11)
#define OPAMP_MODE_NON_INVERT_INDEX3_KEY   (0x19)
#define OPAMP_MODE_NON_INVERT_INDEX4_KEY   (0x09)
#define OPAMP_MODE_USER_DEFINE_KEY  (0x04)

/**
 * @brief Reverse Input Pin Selection
 *
 */
typedef enum {
    inm_pad_vim0 = 0,    /**< Connect pad vim0 */
    inm_pad_vim1 = 1,    /**< Connect pad vim1 */
    inm_pad_vim2 = 2,    /**< Connect pad vim2 */
    inm_pad_dac = 3,    /**< Connect pad vim dac */
    inm_pad_floating = 4    /**< Connect inm floating */
} opamp_inm_pad_t;

/**
 * @brief Gain multiplier selection
 *
 */
typedef enum {
    gain_x_2 = 0,     /**< gain x2 */
    gain_x_4 = 1,
    gain_x_8 = 2,
    gain_x_16 = 3,
    gain_x_32 = 4,
    gain_x_64 = 5,
    gain_x_128 = 6,   /**< gain x128 */
} opamp_gain_t;

/**
 * @brief Miller Capacitor Selection
 *
 */
typedef enum {
    miller_cap_x_7 = 0, /**< 7 unit cap */
    miller_cap_x_8 = 1,
    miller_cap_x_10 = 2,
    miller_cap_x_13 = 3,
    miller_cap_x_15 = 4,    /**< 15 unit cap */
    miller_cap_x_18 = 5,
    miller_cap_x_5 = 6,
    miller_cap_x_6 = 7, /**< 6 unit cap */
} opamp_miller_cap_t;

/**
 * @brief Positive Input Pin Selection
 *
 */
typedef enum {
    inp_pad_vip0 = 0,    /**< Connect pad vip0 */
    inp_pad_vip1 = 1,    /**< Connect pad vip1 */
    inp_pad_vip2 = 2,    /**< Connect pad vip2 */
    inp_pad_dac = 3,    /**< Connect pad vip dac */
    inp_pad_vsupply_x_0_25 = 4,    /**< Connect reference = 0.25 * vsupply */
    inp_pad_vsupply_x_0_5 = 5,    /**< Connect reference = 0.5 * vsupply */
    inp_pad_vsupply_x_0_75 = 6,    /**< Connect reference = 0.75 * vsupply */
    inp_pad_floating = 7    /**< Connect inp floating */
} opamp_inp_pad_t;

/**
 * @brief opamp preset channel
 *
 */
typedef enum {
    cfg_preset_0 = OPAMP_CFG_PRESET0,
    cfg_preset_1 = OPAMP_CFG_PRESET1,
    cfg_preset_2 = OPAMP_CFG_PRESET2,
    cfg_preset_3 = OPAMP_CFG_PRESET3,
    cfg_preset_4 = OPAMP_CFG_PRESET4,
    cfg_preset_5 = OPAMP_CFG_PRESET5,
    cfg_preset_6 = OPAMP_CFG_PRESET6,
    cfg_preset_7 = OPAMP_CFG_PRESET7,
} opamp_cfg_preset_chn_t;

/**
 * @brief operational amplifier
 *
 */
typedef enum {
    mode_follow = 0,  /**< opamp follow mode */
    mode_invert_intern_vol = 1,   /**< inverting opamp */
    mode_invert_extern_vol = 2,   /**< inverted amplification mode, external reference voltage */
    mode_invert_dac_vol = 3,      /**< inverted amplification mode, DAC output reference voltage */
    mode_non_invert_gnd_vol = 4,   /**< forward amplification mode, GND is the reference voltage */
    mode_non_invert_extern_vol = 5,   /**< forward amplification mode, external reference voltage */
    mode_non_invert_dac_vol = 6,  /**< forward amplification mode, DAC output reference voltage */
    mode_user = 7,    /**< custom Mode */
} opamp_mode_t;

/**
 * @brief opamp configuration preset0
 *
 */
typedef union opamp_cfg_preset0 {
    struct {
        uint32_t vip_select: 3;
        uint32_t vim_select: 3;
        uint32_t vswitch_select: 3;
        uint32_t cap_select: 4;
        uint32_t reserve: 19;
    };
    uint32_t val;
} opamp_ctrl_cfg_preset0_t;

/**
 * @brief opamp configuration preset1
 *
 */
typedef union opamp_cfg_preset1 {
    struct {
        uint32_t res_select: 3;
        uint32_t function_mode: 5;
        uint32_t iref_select: 2;
        uint32_t opaout_select: 2;
        uint32_t is_vssa_disconnect: 1;
        uint32_t en_lv: 1;
        uint32_t hw_trig_en: 1;
        uint32_t reserve: 17;
    };
    uint32_t val;
} opamp_ctrl_cfg_preset1_t;

typedef struct opamp_cfg {
    opamp_mode_t mode;
    opamp_inm_pad_t negative_input_pin;
    opamp_inp_pad_t positive_input_pin;
    opamp_gain_t gain;
    opamp_miller_cap_t miller_cap;
    bool enable_extern_filter_cap;
    bool enable_phase_margin_cap;
} opamp_cfg_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief opamp initialisation functions
 *      Use this function to initialise the op-amp to different modes
 * @param opamp @ref OPAMP_Type
 * @param cfg @ref opamp_cfg_t
 * @return  @ref hpm_stat_t
 */
hpm_stat_t opamp_init(OPAMP_Type *opamp, opamp_cfg_t *cfg);
/**
 * @brief enable opamp function
 *
 * @param opamp @ref OPAMP_Type
 */
static inline void opamp_enable(OPAMP_Type *opamp)
{
    opamp->CTRL0 |= OPAMP_CTRL0_EN_LV_MASK;
}

/**
 * @brief preset enable opamp function
 *
 * @param opamp @ref OPAMP_Type
 * @param preset_chn preset channel
 */
static inline void opamp_preset_opamp_enable(OPAMP_Type *opamp, uint8_t preset_chn)
{
    opamp->CFG[preset_chn].CFG1 |= OPAMP_CFG_CFG1_EN_LV_MASK;
}

/**
 * @brief disable opamp function
 *
 * @param opamp @ref OPAMP_Type
 */
static inline void opamp_disable(OPAMP_Type *opamp)
{
    opamp->CTRL0 &= ~OPAMP_CTRL0_EN_LV_MASK;
}

/**
 * @brief preset disable opamp function
 *
 * @param opamp @ref OPAMP_Type
 * @param preset_chn preset channel
 */
static inline void opamp_preset_opamp_disable(OPAMP_Type *opamp, uint8_t preset_chn)
{
    opamp->CFG[preset_chn].CFG1 &= ~OPAMP_CFG_CFG1_EN_LV_MASK;
}

/**
 * @brief opamp miller cap selection
 *
 * @param opamp @ref OPAMP_Type
 * @param select @ref opamp_miller_cap_t
 */
static inline void opamp_miller_cap_select(OPAMP_Type *opamp, opamp_miller_cap_t select)
{
    opamp->CTRL0 = (opamp->CTRL0 & (~OPAMP_CTRL0_MILLER_SEL_MASK)) | OPAMP_CTRL0_MILLER_SEL_SET(select);
}

/**
 * @brief opamp miller cap selection preset
 *
 * @param opamp @ref OPAMP_Type
 * @param preset_chn preset channel
 * @param select @ref opamp_miller_cap_t
 */
static inline void opamp_preset_miller_cap_select(OPAMP_Type *opamp, uint8_t preset_chn, opamp_miller_cap_t select)
{
    opamp->CFG[preset_chn].CFG0 = (opamp->CFG[preset_chn].CFG0 & (~OPAMP_CFG_CFG0_MILLER_SEL_MASK)) | OPAMP_CFG_CFG0_MILLER_SEL_SET(select);
}

/**
 * @brief enable phase margin compensation cap
 *
 * @param opamp @ref OPAMP_Type
 */
static inline void opamp_phase_margin_cap_enable(OPAMP_Type *opamp)
{
    opamp->CTRL0 &= ~OPAMP_CTRL0_DISABLE_PM_CAP_MASK;
}

/**
 * @brief enable phase margin compensation cap preset
 *
 * @param opamp @ref OPAMP_Type
 * @param preset_chn preset channel
 */
static inline void opamp_preset_phase_margin_cap_enable(OPAMP_Type *opamp, uint8_t preset_chn)
{
    opamp->CFG[preset_chn].CFG0 &= ~OPAMP_CFG_CFG0_DISABLE_PM_CAP_MASK;
}

/**
 * @brief disable phase margin compensation cap
 *
 * @param opamp @ref OPAMP_Type
 */
static inline void opamp_phase_margin_cap_disable(OPAMP_Type *opamp)
{
    opamp->CTRL0 |= OPAMP_CTRL0_DISABLE_PM_CAP_MASK;
}

/**
 * @brief disable phase margin compensation cap preset
 *
 * @param opamp @ref OPAMP_Type
 * @param preset_chn preset channel
 */
static inline void opamp_preset_phase_margin_cap_disable(OPAMP_Type *opamp, uint8_t preset_chn)
{
    opamp->CFG[preset_chn].CFG0 |= OPAMP_CFG_CFG0_DISABLE_PM_CAP_MASK;
}

/**
 * @brief opamp core inm connect pad
 *
 * @param opamp @ref OPAMP_Type
 * @param select @ref opamp_inm_pad_t
 */
static inline void opamp_inn_pad_select(OPAMP_Type *opamp, opamp_inm_pad_t select)
{
    opamp->CTRL0 = (opamp->CTRL0 & (~OPAMP_CTRL0_VIM_SEL_MASK)) | OPAMP_CTRL0_VIM_SEL_SET(select);
}

/**
 * @brief opamp core inm connect pad preset
 *
 * @param opamp @ref OPAMP_Type
 * @param preset_chn preset channel
 * @param select @ref opamp_inm_pad_t
 */
static inline void opamp_preset_inn_pad_select(OPAMP_Type *opamp, uint8_t preset_chn, opamp_inm_pad_t select)
{
    opamp->CFG[preset_chn].CFG0 = (opamp->CFG[preset_chn].CFG0 & (~OPAMP_CFG_CFG0_VIM_SEL_MASK)) | OPAMP_CFG_CFG0_VIM_SEL_SET(select);
}

/**
 * @brief main string resistor selection
 *
 * @param opamp @ref OPAMP_Type
 * @param select @ref opamp_gain_t
 *
 */
static inline void opamp_gain_select(OPAMP_Type *opamp, opamp_gain_t select)
{
    opamp->CTRL0 = (opamp->CTRL0 & (~OPAMP_CTRL0_GAIN_SEL_MASK)) | OPAMP_CTRL0_GAIN_SEL_SET(select);
}

/**
 * @brief main string resistor selection preset
 *
 * @param opamp @ref OPAMP_Type
 * @param preset_chn preset channel
 * @param select @ref opamp_gain_t
 *
 */
static inline void opamp_preset_gain_select(OPAMP_Type *opamp, uint8_t preset_chn, opamp_gain_t select)
{
    opamp->CFG[preset_chn].CFG1 = (opamp->CFG[preset_chn].CFG1 & (~OPAMP_CFG_CFG1_GAIN_SEL_MASK)) | OPAMP_CFG_CFG1_GAIN_SEL_SET(select);
}

/**
 * @brief disconnect the main series resistor and VSSA
 *
 * @param opamp @ref OPAMP_Type
 */
static inline void opamp_disconnect_vssa(OPAMP_Type *opamp)
{
    opamp->CTRL0 |= OPAMP_CTRL0_VBYPASS_MASK;
}

/**
 * @brief disconnect the main series resistor and VSSA preset
 *
 * @param opamp @ref OPAMP_Type
 * @param preset_chn preset channel
 */
static inline void opamp_preset_disconnect_vssa(OPAMP_Type *opamp, uint8_t preset_chn)
{
    opamp->CFG[preset_chn].CFG1 |= OPAMP_CFG_CFG1_VBYPASS_LV_MASK;
}

/**
 * @brief connect the main series resistor and VSSA
 *
 * @param opamp @ref OPAMP_Type
 */
static inline void opamp_connect_vssa(OPAMP_Type *opamp)
{
    opamp->CTRL0 &= ~OPAMP_CTRL0_VBYPASS_MASK;
}

/**
 * @brief connect the main series resistor and VSSA preset
 *
 * @param opamp @ref OPAMP_Type
 * @param preset_chn preset channel
 */
static inline void opamp_preset_connect_vssa(OPAMP_Type *opamp, uint8_t preset_chn)
{
    opamp->CFG[preset_chn].CFG1 &= ~OPAMP_CFG_CFG1_VBYPASS_LV_MASK;
}

/**
 * @brief opamp inp select
 *
 * @param opamp @ref OPAMP_Type
 * @param select @ref opamp_inp_pad_t
 */
static inline void opamp_inp_pad_select(OPAMP_Type *opamp, opamp_inp_pad_t select)
{
    opamp->CTRL0 = (opamp->CTRL0 & (~OPAMP_CTRL0_VIP_SEL_MASK)) | OPAMP_CTRL0_VIP_SEL_SET(select);
}

/**
 * @brief opamp inp select preset
 *
 * @param opamp @ref OPAMP_Type
 * @param preset_chn preset channel
 * @param select @ref opamp_inp_pad_t
 */
static inline void opamp_preset_inp_pad_select(OPAMP_Type *opamp, uint8_t preset_chn, opamp_inp_pad_t select)
{
    opamp->CFG[preset_chn].CFG0 = (opamp->CFG[preset_chn].CFG0 & (~OPAMP_CFG_CFG0_VIP_SEL_MASK)) | OPAMP_CFG_CFG0_VIP_SEL_SET(select);
}


/**
 * @brief opamp get current preset
 *
 * @param opamp @ref OPAMP_Type
 * @return value
 */
static inline uint8_t opamp_get_cur_preset(OPAMP_Type *opamp)
{
    return OPAMP_STATUS_CUR_PRESET_GET(opamp->STATUS);
}

/**
 * @brief get the current preset value
 *
 * @param opamp @ref OPAMP_Type
 * @return true one of cur_preset is selected for opamp
 * @return false opamp use cfg0 parameters
 */
static inline bool opamp_get_is_preset(OPAMP_Type *opamp)
{
    return OPAMP_STATUS_PRESET_ACT_GET(opamp->STATUS);
}

/**
 * @brief Get the trigger conflict status
 *
 * @param opamp @ref OPAMP_Type
 * @return  if more than one hardware trigger is set, will put all trigger input there.
 */
static inline uint8_t opamp_get_trig_conflict_status(OPAMP_Type *opamp)
{
    return OPAMP_STATUS_TRIG_CONFLICT_GET(opamp->STATUS);
}

/**
 * @brief Clear the trigger conflict status
 *
 * @param opamp @ref OPAMP_Type
 */
static inline void opamp_clear_conflict_status(OPAMP_Type *opamp)
{
    opamp->STATUS = OPAMP_STATUS_TRIG_CONFLICT_MASK;
}

/**
 * @brief Set opamp preset value
 *
 * @param opamp @ref OPAMP_Type
 * @param val @ref opamp_cfg_preset_chn_t
 */
static inline void opamp_set_sw_preset_val(OPAMP_Type *opamp, opamp_cfg_preset_chn_t val)
{
    opamp->CTRL1 = (opamp->CTRL1 & (~OPAMP_CTRL1_SW_SEL_MASK)) | OPAMP_CTRL1_SW_SEL_SET(val);
}

/**
 * @brief Enable software preset
 *
 * @param opamp @ref OPAMP_Type
 */
static inline void opamp_enable_sw_preset(OPAMP_Type *opamp)
{
    opamp->CTRL1 |= OPAMP_CTRL1_SW_PRESET_MASK;
}

/**
 * @brief Disable software preset
 *
 * @param opamp @ref OPAMP_Type
 */
static inline void opamp_disable_sw_preset(OPAMP_Type *opamp)
{
    opamp->CTRL1 &= ~OPAMP_CTRL1_SW_PRESET_MASK;
}


/**
 * @brief Set preset x channel value
 *
 * @param opamp @ref OPAMP_Type
 * @param preset_chn preset channel
 * @param chn channel
 */
static inline void opamp_set_preset_x_chn(OPAMP_Type *opamp, uint8_t preset_chn, uint8_t chn)
{
    opamp->CFG[preset_chn].CFG2 = OPAMP_CFG_CFG2_CHANNEL_SET(chn);
}

/**
 * @brief Set preset cfg
 *
 * @param opamp @ref OPAMP_Type
 * @param preset_chn preset channel
 * @param cfg @ref opamp_cfg_t
 * @return hpm_stat_t
 */
hpm_stat_t opamp_set_preset_cfg(OPAMP_Type *opamp, uint8_t preset_chn, opamp_cfg_t *cfg);

/**
 * @brief opamp enable preset hardware trig
 *
 * @param opamp @ref OPAMP_Type
 * @param preset_chn preset channel
 */
static inline void opamp_preset_enable_hw_trig(OPAMP_Type *opamp, uint8_t preset_chn)
{
    opamp->CFG[preset_chn].CFG1 |= OPAMP_CFG_CFG1_HW_TRIG_EN_MASK;
}

/**
 * @brief opamp disable preset hardware trig
 *
 * @param opamp @ref OPAMP_Type
 * @param preset_chn preset channel
 */
static inline void opamp_preset_disable_hw_trig(OPAMP_Type *opamp, uint8_t preset_chn)
{
    opamp->CFG[preset_chn].CFG1 &= ~OPAMP_CFG_CFG1_HW_TRIG_EN_MASK;
}

/**
 * @brief opamp set mode
 *
 * @param opamp @ref OPAMP_Type
 * @param mode OPAMP_MODE_XX
 */
static inline void opamp_mode_set(OPAMP_Type *opamp, uint8_t mode)
{
    opamp->CTRL0 = (opamp->CTRL0 & (~OPAMP_CTRL0_MODE_MASK)) | OPAMP_CTRL0_MODE_SET(mode);
}

/**
 * @brief opamp preset set mode
 *
 * @param opamp @ref OPAMP_Type
 * @param preset_chn preset channel
 * @param mode OPAMP_MODE_XX
 */
static inline void opamp_preset_mode_set(OPAMP_Type *opamp, uint8_t preset_chn, uint8_t mode)
{
    opamp->CFG[preset_chn].CFG1 = (opamp->CFG[preset_chn].CFG1 & (~OPAMP_CFG_CFG1_MODE_MASK)) | OPAMP_CFG_CFG1_MODE_SET(mode);
}

/**
 * @}
 *
 */

#ifdef __cplusplus
}
#endif

#endif /* HPM_ACMP_DRV_H */
