/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @brief 触控算法头文件.
 * 大概流程:(配置TIMER->定义回调API->初始化->启动)
 * @file n32xx_tsc_alg_api.h
 * @author Nations
 * @version v1.0.1
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32XX_TSC_ALG_API__
#define __N32XX_TSC_ALG_API__

#ifdef __cplusplus
extern "C" {
#endif // defined __cplusplus

#define TSC_ALG_VERSION_NUMBER "Ver1.0.4" //算法库版本号

#define TSC_ALG_HANDLER_STOP2_DATA_SIZE (144)  //用于在STOP2模式下保存触控唤醒功能相关的TSC数据。
#define TSC_ALG_HANDLER_PERIOD_PER_CHN  (400)  //触控算法单通道的处理周期因子。
#define TSC_ALG_WAKEUP_TIMES            (1000) //有关TSC唤醒功能的时间配置，不要随意修改
#define TSC_ALG_DEBUG_BUF_SIZE          (260)  //定义调试模式下的BUF大小
#define TSC_ALG_REF_SIZE_PER_CHN        (430)  //触控每通道的参考大小，实际大小以tsc_alg_need_sramsize()计算为准

/**
 * @brief 定义触控类型
 */
typedef enum tsc_alg_type_e
{
    TSC_ALG_BUTTON_TYPE = 0, ///< tsc application of simple button
    TSC_ALG_TYPE_MAX         ///<
} tsc_alg_type;

/**
 * @brief 按键事件
 */
typedef enum tsc_press_key_event_e
{
    TSC_PRESS_KEY_NORMAL = 0, //正常短按事件
    TSC_PRESS_KEY_MAX         ///<
} tsc_press_key_event;

/**
 * @brief 错误类型定义
 */
typedef enum tsc_ret_code_e
{
    TSC_SUCCESS = 0,               ///< 成功
    TSC_NOT_INIT_ERR,              ///< 模块未初始化错误
    TSC_NOT_REG_CHN_ERR,           ///< 模块注册无效的触控通道错误
    TSC_NOT_ACCORD_LIB_ERR,        ///< 算法库版本错误
    TSC_POINTER_NULL_ERR,          ///< 指针为空错误
    TSC_PARAM_ZERO_ERR,            ///< 参数错误
    TSC_REPEAT_REG_ERR,            ///< 重复注册错误
    TSC_CHN_NUM_ERR,               ///< 与初始化的通道总数不一致错误
    TSC_REG_CHANNEL_ENOUGH_ERR,    ///< 注册的通道号错误或超出系统总通道数
    TSC_REG_TIMX_ERR,              ///< 注册的Timer资源错误
    TSC_REG_DMA_ERR,               ///< 注册的DMA资源错误
    TSC_SOURCE_NOT_ENOUGH_ERR,     ///< 资源不足错误
    TSC_NOT_SUPPORT_ERR,           ///< 未实现或操作不支持错误
    TSC_LEVEL_CFG_ERR,             ///< 通道的灵明度配置错误
    TSC_AUTO_CALIB_TIMER_ERR,      ///< 自动校准时间小于2倍通道按键保持时间.
    TSC_DISTURB_ERR,               ///< 干扰错误.
    TSC_CHN_RAM_NOT_ENOUGH_ERR,    ///< 提供的TSC通道RAM为NULL或空间不足错误
    TSC_STOP2_NULL_OR_INVALID_ERR, ///< 提供的Stop2Data数据空间为NULL或不在16K retention区域内。
    TSC_DEBUG_BUF_ENOUGH_ERR       ///< 提供的调试缓存空间不足错误
} tsc_ret_code;

/**
 * @brief 触控按键持续等级
 * 持续等级越小:反应速度越快，抗瞬间的干扰也越弱；
 * 持续等级越大:反应速度相对弱，抗瞬间干扰能力越强
 */
typedef enum tsc_hld_lev_e
{
    TSC_HOLD_LEV1  = 1,  // HOLD等级1(5ms)
    TSC_HOLD_LEV2  = 2,  // HOLD等级2(7ms)
    TSC_HOLD_LEV3  = 3,  // HOLD等级3(11ms)
    TSC_HOLD_LEV4  = 4,  // HOLD等级4(17ms)
    TSC_HOLD_LEV5  = 5,  // HOLD等级5(25ms)
    TSC_HOLD_LEV6  = 6,  // HOLD等级6(35ms)
    TSC_HOLD_LEV7  = 7,  // HOLD等级7(47ms)
    TSC_HOLD_LEV8  = 8,  // HOLD等级8(61ms)
    TSC_HOLD_LEV9  = 9,  // HOLD等级9(77ms)
    TSC_HOLD_LEV10 = 10, // HOLD等级10(95ms)
    TSC_HOLD_LEV11 = 11, // HOLD等级11(115ms)
    TSC_HOLD_LEV12 = 12, // HOLD等级12(137ms)
    TSC_HOLD_LEV13 = 13, // HOLD等级13(161ms)
    TSC_HOLD_LEV14 = 14, // HOLD等级14(187ms)
    TSC_HOLD_LEV15 = 15, // HOLD等级15(215ms)
    TSC_HOLD_LEV16 = 16, // HOLD等级16(245ms)
    TSC_HOLD_LEV17 = 17, // HOLD等级17(277ms)
    TSC_HOLD_LEV18 = 18, // HOLD等级18(311ms)
    TSC_HOLD_LEV19 = 19, // HOLD等级19(347ms)
    TSC_HOLD_LEV20 = 20, // HOLD等级20(385ms)
    TSC_HOLD_MAX         ///< 无效
} tsc_hld_lev;

/**
 * @brief 在低功耗模式下，随环境变化而更新唤醒门限。
 * 因此设置一个变化量因子。
 * 小于此变化量因子的delta则认为是有效变化，则通过此接口更新TSC唤醒门限；
 * 大于此变化量因子的delta则认为是无效变化，则此接口忽略之，不更新唤醒门限。
 * 变化量因子越大，则表示变化量越大。一般设置为LEV15。
 */
typedef enum tsc_delta_limit_lev_e
{
    TSC_DELTA_LIMIT_LEV1  = 1,  //
    TSC_DELTA_LIMIT_LEV2  = 2,  //
    TSC_DELTA_LIMIT_LEV3  = 3,  //
    TSC_DELTA_LIMIT_LEV4  = 4,  //
    TSC_DELTA_LIMIT_LEV5  = 5,  //
    TSC_DELTA_LIMIT_LEV6  = 6,  //
    TSC_DELTA_LIMIT_LEV7  = 7,  //
    TSC_DELTA_LIMIT_LEV8  = 8,  //
    TSC_DELTA_LIMIT_LEV9  = 9,  //
    TSC_DELTA_LIMIT_LEV10 = 10, //
    TSC_DELTA_LIMIT_LEV11 = 11, //
    TSC_DELTA_LIMIT_LEV12 = 12, //
    TSC_DELTA_LIMIT_LEV13 = 13, //
    TSC_DELTA_LIMIT_LEV14 = 14, //
    TSC_DELTA_LIMIT_LEV15 = 15, //
    TSC_DELTA_LIMIT_LEV16 = 16, //
    TSC_DELTA_LIMIT_LEV17 = 17, //
    TSC_DELTA_LIMIT_LEV18 = 18, //
    TSC_DELTA_LIMIT_LEV19 = 19, //
    TSC_DELTA_LIMIT_LEV20 = 20, //
    TSC_DELTA_LIMIT_MAX         ///< 无效
} tsc_delta_limit_lev;

/**
 * @brief 抗干扰等级
 * 抗干扰等级,等级越高抗干扰越强，但也对板级环境要求越严苛.
 */
typedef enum tsc_resist_disturb_lev_e
{
    TSC_RESIST_DIS_LEV0 = 0, //默认等级，抗外部干扰一般。支持PCBA&亚克力触摸。
    TSC_RESIST_DIS_LEV1 = 1, //增强等级，抗外部干扰增强。亚克力情况下体验更好。
    TSC_RESIST_DIS_LEV2 = 2, //暂保留。
    TSC_RESIST_DIS_MAX       ///< 无效
} tsc_resist_disturb_lev;

/**
 * @brief TSC触控通道初始门限值配置
 */
typedef struct TSC_AlgInitThreValue_t
{
    uint16_t hold_level;     /* 按键触发持续等级 */
    uint16_t rate_of_change; /* 该通道按键变化率(如无压下为70,压下为77，则变化率为(77-70)/70 = 0.1即%10(注意:适当降低为8%)。默认为5,则变化率%5 */
    uint32_t chn;            /* 通道 */
} TSC_AlgInitThreValue;

/**
 * @brief TSC初始化配置参数
 */
typedef struct TSC_AlgInitTypeDef_t
{
    TIM_Module* TIMx;                      /* 触控算法使用的TIMER资源(仅支持TIMER2) */
    DMA_ChannelType* DMAyChx;              /* 触控算法使用的DMA资源(仅支持DMA1_CH5) */
    uint32_t DMARemapEnable;               /* 是否使能DMA 全局REMAP功能(如DMA1中其他通道有使能REMAP功能，则此处需配置为1) */
    TSC_AlgInitThreValue* pTScChannelList; /* 由触控通道组成列表的数组。目前暂支持1个列(可通过位或运算,将多个TSC通道组成一个列表)。 */
    uint32_t AutoCalibrateTimer;           /* 配置有覆盖物情况下的自动校准时间(无覆盖物或干扰时不会校准),一般设置1000ms即可,最大65535。单位ms。此值必须大于按键保持时间的2倍以上，否则初始化错误 */
    uint32_t ResistDisturbLev;             /* 抗干扰等级(tsc_resist_disturb_lev),等级越高抗干扰越强，但也对板级装配环境要求越高. */
    uint8_t* pTscSramAddr;                 /* 应用程序提供给TSC驱动库的触控通道RAM空间地址*/
    uint32_t TscSramSize;                  /* 应用程序提供给TSC驱动库的触控通道RAM空间大小.单位(bytes) */
    uint16_t* LogBuf;                      /* 用于调试模式下的buf缓存,非调试模式下则为0 */
    uint16_t LogBufSize;                   /* 每通道大小为u16 * 256.单位(bytes) */
    uint8_t* Stop2Data;                    /* 用于在STOP2模式下保存触控唤醒功能相关的TSC数据BUF。 */
    uint16_t Stop2DataSize;                /* 用于在STOP2模式下保存触控唤醒功能相关的TSC数据BUF大小。单位(bytes) */
} TSC_AlgInitTypeDef;

/**
 * @brief 触控算法实时分析处理函数(必须放在TIMER中断函数中)
 * @TIMER定时周期参考周期因子，定时器周期参考DEMO范例.
 * @param void
 * @return void
 */
void tsc_alg_analyze_handler(void);

/**
 * @brief 低功耗校准
 * @param uint32_t delta_limit_level 变化量限值等级tsc_delta_limit_lev
 * @uint32_t hse_or_hsi 0:HSI,  1:HSE;
 * @return
 * - `TSC_SUCCESS： 表示操作成功
 * - 其它值表示出错
 * - 注意：用于在STOP2低功耗模式下，定时校准。
 */
int32_t tsc_alg_set_powerdown_calibrate(tsc_delta_limit_lev delta_limit_level, uint32_t hse_or_hsi);

/**
 * @brief 低功耗模式下,检测是否被干扰唤醒
 * @param void
 * @return 0:正常唤醒；1:干扰唤醒
 */
int32_t tsc_alg_wakeup_disturb_check(uint32_t* wakeup_src);

/**
 * @brief 获取算法版本
 * @param void
 * @return void
 */
char* tsc_alg_get_version(void);

/**
 * @brief 触控算法系统滴答,默认1ms
 * @param void
 * @return void
 */
void tsc_alg_tick_count(void);

/**
 * @brief 获取TSC触控算法需要的SRAM大小
 * uint32_t      chn_totals; // 使用的TSC触控通道数
 * @return
 * - 0:     表示失败
 * - 非0:  表示成功
 */
uint32_t tsc_alg_need_sramsize(uint32_t chn_totals);

/**
 * @brief 触控算法初始化
 * @param tsc_init_parameter *ptsc_init_parameter 触控算法初始化结构体地址.
 * @param void
 * @return
 * - `TSC_SUCCESS： 表示操作成功
 * - 其它值表示出错
 */
int32_t tsc_alg_init(TSC_AlgInitTypeDef* TSC_AlgInitStruct);

/**
 * @brief 启动触控开始工作
 * @param void
 * @return
 * - `TSC_SUCCESS： 表示操作成功
 * - 其它值表示出错
 */
int32_t tsc_alg_start(void);

/**
 * @brief 设置TSC进入低功耗(用于低功耗唤醒模式)
 * @param uint32_t TScChannelList 保留参数。设置为0表示使能已注册的所有通道
 * @return
 * - `TSC_SUCCESS： 表示操作成功
 * - 其它值表示出错
 * - 注意：STOP2低功耗模式使用，正常模式下不关注。
 */
int32_t tsc_alg_set_powerdown(uint32_t TscChannelList);

////////////////////////////////////////////////////////////

/*****************上层应用提供的按键回调处理函数*********
 * @brief 注册按钮型、滑条型、转轮型触控的回调函数
 * @param tsc_touch_type type 产生的触控类型(暂只支持按键型)
 * @param uint32_t event 0:正常触摸事件；
 * @param uint32_t chn 表示触摸通道号；
 * @param uint32_t value 触摸状态：1压下；0松开；
 * @return
 * - `TSC_SUCCESS： 表示操作成功
 * - 其它值表示出错
 * 注意:此回调函数将在中断中调用，因此尽量减少回调函数的处理时间。
 ********************************************************/
int32_t tsc_alg_isr_callback(tsc_alg_type type, uint32_t event, uint32_t chn, uint32_t value);

/**
 * @brief 触控数据输出到PC的接口，以便于PC端工具观察，设定合理的触控阈值
 * @param uint32_t chn 触控通道
 * @return uint8_t data 该触控通道数据
 */
void tsc_alg_debug_output(uint32_t chn, uint8_t data);

#ifdef __cplusplus
}
#endif // defined __cplusplus

#endif //__N32XX_TSC_ALG_API__
