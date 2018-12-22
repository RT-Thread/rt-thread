#ifndef GPIO_ALL_CFG_H
#define GPIO_ALL_CFG_H


#if defined(GK7101_OV2710_V10) || defined(GK7101_OV2710_V20) || defined(GK7101_OV2710_V21) || defined(GK7101_OV2710_V22) \
		|| defined(GK7101S_OV2710_V10) || defined(GK7101S_OV2710_V20) || defined(GK7101S_OV2710_V21) || defined(GK7101S_OV2710_V22)
#include "gpio_gk7101_ov2710.h"
#endif

#if defined(GK7101_IMX222) || defined(GK7101S_IMX222)
#include "gpio_gk7101_imx222.h"
#endif

#if defined(GK7101_EVB)
#include "gpio_gk7101_evb.h"
#endif

#if defined(GK7101_HZD_OV2710) || defined(GK7101S_HZD_OV2710) || defined(GK7102_HZD_JXH42) || defined(GK7102S_HZD_JXH42)
#include "gpio_gk710x_hzd.h"
#endif

#if defined(GK7102_JXH42_V10) || defined(GK7102_JXH42_V20) || defined(GK7101S_JXH42_V20)
#include "gpio_gk7102_jxh42.h"
#endif

#if defined(GK7102_JXH42_JOYHONEST)
#include "gpio_gk7102_jxh42_joyhonest.h"
#endif

#if defined(GK7102S_OV9732_JOYHONEST) || defined(GK7102S_QFN_OV9732_JH)
#include "gpio_gk7102s_ov9732_joyhonest.h"
#endif

#if defined(GK7102C_JH) 
#include "gpio_gk7102c_joyhonest.h"
#endif

#if defined(GK7102_SC1045_V20) || defined(GK7102_SC1035_V20)
#include "gpio_gk7102_sc1045.h"
#endif

#if defined(GK7102_SC2135)
#include "gpio_gk7102_sc2135.h"
#endif

#if defined(GK7102_RTOS) || defined(GK7102S_RTOS)
#include "gpio_gk7102_rtos.h"
#endif

#if defined(GK7101S_EVB)
#include "gpio_gk7101s_evb.h"
#endif

#if defined(GK7102S_SANZHONG_MAOYAN)
#include "gpio_gk7102s_maoyan_sanzhong.h"
#endif

#if defined(GK7102S_SANZHONG_MAOYAN)
#include "gpio_gk7102s_maoyan_sanzhong.h"
#endif

#if defined(GK7102S_TW9912)
#include "gpio_gk7102s_tw9912.h"
#endif

#if defined(BOARD_FPGA)
#include "gpio_gk7102c_fpga.h"
#endif

#if defined(GK7102s_ov9732)
#include "gpio_gk7102s_ov9732.h"
#endif

#if defined(GK7102C_EVB)
#include "gpio_gk7102c_evb.h"
#endif

#if defined(GK7102C_OV9750_V10)
#include "gpio_gk7102c_ov9750.h"
#endif

#if defined(GK7102CT_V10)
#include "gpio_gk7102c_t_rtos.h"
#endif

#endif
