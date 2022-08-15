
/**
* \cond INTERNAL
*/

#include "cy_device.h"

//These are all items that should be part of the PDL, but aren't there yet
bool Cy_SysClk_PeriPclkGetDividerEnabled(en_clk_dst_t ipBlock, cy_en_divider_types_t dividerType, uint32_t dividerNum);

#if defined(CY_IP_MXS28SRSS)
#define Cy_SysPm_RegisterCallback(handler)              (false)
#define Cy_SysPm_SystemEnterLp()                        (CY_RSLT_SUCCESS)
#define Cy_SysPm_SystemEnterUlp()                       (CY_RSLT_SUCCESS)
#define Cy_SysPm_IoUnfreeze()
#define Cy_SysPm_IoIsFrozen()                           (false)
#else
#if !defined(CY_SAR_NUM_CHANNELS)
#define CY_SAR_NUM_CHANNELS (16)
#define CY_SAR_SEQ_NUM_CHANNELS (16)
#define CY_SAR_MAX_NUM_CHANNELS (16)
#endif

#define CY_SAR_INTR_EOS                 (0)

#define Cy_SysAnalog_Init(config)                       (CY_RSLT_SUCCESS)
#define Cy_SysAnalog_DeInit(void)
#define Cy_SysAnalog_Enable(void)
#define Cy_SysAnalog_Disable(void)

typedef enum
{
    CY_SYSANALOG_STARTUP_NORMAL     = 0UL,
    CY_SYSANALOG_STARTUP_FAST       = 1UL,
} cy_en_sysanalog_startup_t;
typedef enum
{
    CY_SYSANALOG_IZTAT_SOURCE_SRSS       = 0UL,
    CY_SYSANALOG_IZTAT_SOURCE_LOCAL      = 1UL
} cy_en_sysanalog_iztat_source_t;
typedef enum
{
    CY_SYSANALOG_VREF_SOURCE_SRSS        = 0UL,
    CY_SYSANALOG_VREF_SOURCE_LOCAL_1_2V  = 1UL,
    CY_SYSANALOG_VREF_SOURCE_EXTERNAL    = 2UL
} cy_en_sysanalog_vref_source_t;
typedef enum
{
    CY_SYSANALOG_DEEPSLEEP_DISABLE             = 0UL,
    CY_SYSANALOG_DEEPSLEEP_IPTAT_1             = 1UL,
    CY_SYSANALOG_DEEPSLEEP_IPTAT_2             = 2UL,
    CY_SYSANALOG_DEEPSLEEP_IPTAT_IZTAT_VREF    = 3UL
} cy_en_sysanalog_deep_sleep_t;
typedef struct
{
    cy_en_sysanalog_startup_t                   startup;
    cy_en_sysanalog_iztat_source_t              iztat;
    cy_en_sysanalog_vref_source_t               vref;
    cy_en_sysanalog_deep_sleep_t                deepSleep;
} cy_stc_sysanalog_config_t;
extern const cy_stc_sysanalog_config_t Cy_SysAnalog_Fast_Local;

typedef enum
{
    CY_SAR_RANGE_LOW_SHIFT,
    CY_SAR_RANGE_HIGH_SHIFT,
} cy_en_sar_range_thres_shift_t;
typedef enum
{
    CY_SAR_RANGE_COND_BELOW     = 0UL,
    CY_SAR_RANGE_COND_INSIDE    = 1UL,
    CY_SAR_RANGE_COND_ABOVE     = 2UL,
    CY_SAR_RANGE_COND_OUTSIDE   = 3UL,
} cy_en_sar_range_detect_condition_t;
typedef enum
{
    CY_SAR_CLK_PERI       = 0UL,
    CY_SAR_CLK_DEEPSLEEP  = 1UL
} cy_en_sar_clock_source_t;
typedef struct
{
    bool chanId;
    bool chainToNext;
    bool clrTrIntrOnRead;
    uint32_t level;
    bool trOut;
} cy_stc_sar_fifo_config_t;
typedef enum
{
    CY_SAR_MUX_SQ_CTRL_P0           = 0,
    CY_SAR_MUX_SQ_CTRL_P1           = 1,
    CY_SAR_MUX_SQ_CTRL_P2           = 2,
    CY_SAR_MUX_SQ_CTRL_P3           = 3,
    CY_SAR_MUX_SQ_CTRL_P4           = 4,
    CY_SAR_MUX_SQ_CTRL_P5           = 5,
    CY_SAR_MUX_SQ_CTRL_P6           = 6,
    CY_SAR_MUX_SQ_CTRL_P7           = 7,
    CY_SAR_MUX_SQ_CTRL_VSSA         = 8,
    CY_SAR_MUX_SQ_CTRL_TEMP         = 9,
    CY_SAR_MUX_SQ_CTRL_AMUXBUSA     = 10,
    CY_SAR_MUX_SQ_CTRL_AMUXBUSB     = 11,
    CY_SAR_MUX_SQ_CTRL_SARBUS0      = 12,
    CY_SAR_MUX_SQ_CTRL_SARBUS1      = 13,
} cy_en_sar_mux_switch_sq_ctrl_t;
typedef enum
{
    CY_SAR_MUX_FW_P0_VPLUS         = 0,
    CY_SAR_MUX_FW_P1_VPLUS         = 0,
    CY_SAR_MUX_FW_P2_VPLUS         = 0,
    CY_SAR_MUX_FW_P3_VPLUS         = 0,
    CY_SAR_MUX_FW_P4_VPLUS         = 0,
    CY_SAR_MUX_FW_P5_VPLUS         = 0,
    CY_SAR_MUX_FW_P6_VPLUS         = 0,
    CY_SAR_MUX_FW_P7_VPLUS         = 0,
    CY_SAR_MUX_FW_P0_VMINUS        = 0,
    CY_SAR_MUX_FW_P1_VMINUS        = 0,
    CY_SAR_MUX_FW_P2_VMINUS        = 0,
    CY_SAR_MUX_FW_P3_VMINUS        = 0,
    CY_SAR_MUX_FW_P4_VMINUS        = 0,
    CY_SAR_MUX_FW_P5_VMINUS        = 0,
    CY_SAR_MUX_FW_P6_VMINUS        = 0,
    CY_SAR_MUX_FW_P7_VMINUS        = 0,
    CY_SAR_MUX_FW_VSSA_VMINUS      = 0,
    CY_SAR_MUX_FW_TEMP_VPLUS       = 0,
    CY_SAR_MUX_FW_AMUXBUSA_VPLUS   = 0,
    CY_SAR_MUX_FW_AMUXBUSB_VPLUS   = 0,
    CY_SAR_MUX_FW_AMUXBUSA_VMINUS  = 0,
    CY_SAR_MUX_FW_AMUXBUSB_VMINUS  = 0,
    CY_SAR_MUX_FW_SARBUS0_VPLUS    = 0,
    CY_SAR_MUX_FW_SARBUS1_VPLUS    = 0,
    CY_SAR_MUX_FW_SARBUS0_VMINUS   = 0,
    CY_SAR_MUX_FW_SARBUS1_VMINUS   = 0,
    CY_SAR_MUX_FW_P4_COREIO0       = 0,
    CY_SAR_MUX_FW_P5_COREIO1       = 0,
    CY_SAR_MUX_FW_P6_COREIO2       = 0,
    CY_SAR_MUX_FW_P7_COREIO3       = 0,
} cy_en_sar_mux_switch_fw_ctrl_t;
typedef enum
{
    CY_SAR_CHAN_POS_PIN_ADDR_0     = 0UL,
    CY_SAR_CHAN_POS_PIN_ADDR_1     = 1UL,
    CY_SAR_CHAN_POS_PIN_ADDR_2     = 2UL,
    CY_SAR_CHAN_POS_PIN_ADDR_3     = 3UL,
    CY_SAR_CHAN_POS_PIN_ADDR_4     = 4UL,
    CY_SAR_CHAN_POS_PIN_ADDR_5     = 5UL,
    CY_SAR_CHAN_POS_PIN_ADDR_6     = 6UL,
    CY_SAR_CHAN_POS_PIN_ADDR_7     = 7UL,
} cy_en_sar_chan_config_pos_pin_addr_t;
typedef enum
{
    CY_SAR_CHAN_NEG_PIN_ADDR_0     = 0UL,
    CY_SAR_CHAN_NEG_PIN_ADDR_1     = 1UL,
    CY_SAR_CHAN_NEG_PIN_ADDR_2     = 2UL,
    CY_SAR_CHAN_NEG_PIN_ADDR_3     = 3UL,
    CY_SAR_CHAN_NEG_PIN_ADDR_4     = 4UL,
    CY_SAR_CHAN_NEG_PIN_ADDR_5     = 5UL,
    CY_SAR_CHAN_NEG_PIN_ADDR_6     = 6UL,
    CY_SAR_CHAN_NEG_PIN_ADDR_7     = 7UL,
} cy_en_sar_chan_config_neg_pin_addr_t;
typedef enum
{
    CY_SAR_NEG_PORT_ADDR_SARMUX         = 0UL,
    CY_SAR_NEG_PORT_ADDR_AROUTE_VIRT2   = 5UL,
    CY_SAR_NEG_PORT_ADDR_AROUTE_VIRT1   = 6UL,
    CY_SAR_NEG_PORT_ADDR_SARMUX_VIRT    = 7UL,
} cy_en_sar_chan_config_neg_port_addr_t;
typedef enum
{
    CY_SAR_POS_PORT_ADDR_SARMUX         = 0UL,
    CY_SAR_POS_PORT_ADDR_CTB0           = 1UL,
    CY_SAR_POS_PORT_ADDR_CTB1           = 2UL,
    CY_SAR_POS_PORT_ADDR_CTB2           = 3UL,
    CY_SAR_POS_PORT_ADDR_CTB3           = 4UL,
    CY_SAR_POS_PORT_ADDR_AROUTE_VIRT2   = 5UL,
    CY_SAR_POS_PORT_ADDR_AROUTE_VIRT1   = 6UL,
    CY_SAR_POS_PORT_ADDR_SARMUX_VIRT    = 7UL,
} cy_en_sar_chan_config_pos_port_addr_t;
typedef enum
{
    CY_SAR_VREF_SEL_BGR         = 4UL,
    CY_SAR_VREF_SEL_EXT         = 5UL,
    CY_SAR_VREF_SEL_VDDA_DIV_2  = 6UL,
    CY_SAR_VREF_SEL_VDDA        = 7UL,
} cy_en_sar_ctrl_vref_sel_t;
typedef enum
{
    CY_SAR_AVG_CNT_2          = 0UL,
    CY_SAR_AVG_CNT_4          = 1UL,
    CY_SAR_AVG_CNT_8          = 2UL,
    CY_SAR_AVG_CNT_16         = 3UL,
    CY_SAR_AVG_CNT_32         = 4UL,
    CY_SAR_AVG_CNT_64         = 5UL,
    CY_SAR_AVG_CNT_128        = 6UL,
    CY_SAR_AVG_CNT_256        = 7UL,
} cy_en_sar_sample_ctrl_avg_cnt_t;
typedef enum
{
    CY_SAR_AVG_MODE_SEQUENTIAL_ACCUM    = 0UL,
    CY_SAR_AVG_MODE_SEQUENTIAL_FIXED    = 1UL,
    CY_SAR_AVG_MODE_INTERLEAVED         = 2UL,
} cy_en_sar_sample_ctrl_avg_mode_t;
typedef enum
{
    CY_SAR_NEG_SEL_VSSA_KELVIN  = 0UL,
    CY_SAR_NEG_SEL_P1           = 2UL,
    CY_SAR_NEG_SEL_P3           = 3UL,
    CY_SAR_NEG_SEL_P5           = 4UL,
    CY_SAR_NEG_SEL_P7           = 5UL,
    CY_SAR_NEG_SEL_ACORE        = 6UL,
    CY_SAR_NEG_SEL_VREF         = 7UL,
} cy_en_sar_ctrl_neg_sel_t;
typedef enum
{
    CY_SAR_COMP_PWR_100     = 0UL,
    CY_SAR_COMP_PWR_80      = 1UL,
    CY_SAR_COMP_PWR_60      = 2UL,
    CY_SAR_COMP_PWR_50      = 3UL,
    CY_SAR_COMP_PWR_40      = 4UL,
    CY_SAR_COMP_PWR_30      = 5UL,
    CY_SAR_COMP_PWR_20      = 6UL,
    CY_SAR_COMP_PWR_10      = 7UL,
} cy_en_sar_ctrl_comp_pwr_t;
typedef enum
{
    CY_SAR_CTRL_NEGVREF_FW_ONLY = 0UL,
    CY_SAR_CTRL_NEGVREF_HW      = 1UL,
} cy_en_sar_ctrl_hw_ctrl_negvref_t;
typedef enum
{
    CY_SAR_DEEPSLEEP_SARMUX_OFF = 0UL,
    CY_SAR_DEEPSLEEP_SARMUX_ON  = 1UL,
} cy_en_sar_ctrl_sarmux_deep_sleep_t;
typedef enum
{
    CY_SAR_SARSEQ_SWITCH_ENABLE    = 0UL,
    CY_SAR_SARSEQ_SWITCH_DISABLE   = 1UL,
} cy_en_sar_ctrl_sarseq_routing_switches_t;
typedef enum
{
    CY_SAR_DIFFERENTIAL_UNSIGNED  = 0UL,
    CY_SAR_DIFFERENTIAL_SIGNED    = 1UL,
} cy_en_sar_sample_ctrl_differential_format_t;
typedef enum
{
    CY_SAR_TRIGGER_MODE_FW_ONLY        = 0UL,
    CY_SAR_TRIGGER_MODE_FW_AND_HWEDGE  = 1UL,
    CY_SAR_TRIGGER_MODE_FW_AND_HWLEVEL = 2UL,
} cy_en_sar_sample_ctrl_trigger_mode_t;
typedef enum
{
    CY_SAR_RIGHT_ALIGN  = 0UL,
    CY_SAR_LEFT_ALIGN   = 1UL,
} cy_en_sar_sample_ctrl_result_align_t;
typedef enum
{
    CY_SAR_SINGLE_ENDED_UNSIGNED  = 0UL,
    CY_SAR_SINGLE_ENDED_SIGNED    = 1UL,
} cy_en_sar_sample_ctrl_single_ended_format_t;
typedef enum
{
    CY_SAR_VREF_PWR_100     = 0UL,
    CY_SAR_VREF_PWR_80      = 1UL,
    CY_SAR_VREF_PWR_60      = 2UL,
    CY_SAR_VREF_PWR_50      = 3UL,
    CY_SAR_VREF_PWR_40      = 4UL,
    CY_SAR_VREF_PWR_30      = 5UL,
    CY_SAR_VREF_PWR_20      = 6UL,
    CY_SAR_VREF_PWR_10      = 7UL,
} cy_en_sar_ctrl_pwr_ctrl_vref_t;
typedef enum
{
    CY_SAR_CTRL_COMP_DLY_2P5    = 0UL,
    CY_SAR_CTRL_COMP_DLY_4      = 1UL,
    CY_SAR_CTRL_COMP_DLY_10     = 2UL,
    CY_SAR_CTRL_COMP_DLY_12     = 3UL,
} cy_en_sar_ctrl_comp_delay_t;
typedef enum
{
    CY_SAR_SWITCH_SEQ_CTRL_DISABLE = 0UL,
    CY_SAR_SWITCH_SEQ_CTRL_ENABLE  = 1UL
} cy_en_sar_switch_sar_seq_ctrl_t;
typedef enum
{
    CY_SAR_BYPASS_CAP_DISABLE = 0UL,
    CY_SAR_BYPASS_CAP_ENABLE  = 1UL,
} cy_en_sar_ctrl_bypass_cap_t;
typedef enum
{
    CY_SAR_SWITCH_OPEN      = 0UL,
    CY_SAR_SWITCH_CLOSE     = 1UL
} cy_en_sar_switch_state_t;
typedef enum
{
    CY_SAR_CHAN_SINGLE_ENDED            = 0UL,
    CY_SAR_CHAN_DIFFERENTIAL_PAIRED     = 1UL,
    CY_SAR_CHAN_DIFFERENTIAL_UNPAIRED   = 2UL,
} cy_en_sar_chan_config_input_mode_t;
typedef enum
{
    CY_SAR_MUX_SWITCH0  = 0UL,
} cy_en_sar_switch_register_sel_t;
typedef struct
{
    uint32_t ctrl;
    uint32_t sampleCtrl;
    uint32_t sampleTime01;
    uint32_t sampleTime23;
    uint32_t rangeThres;
    cy_en_sar_range_detect_condition_t rangeCond;
    uint32_t chanEn;
    uint32_t chanConfig[CY_SAR_NUM_CHANNELS];
    uint32_t intrMask;
    uint32_t satIntrMask;
    uint32_t rangeIntrMask;
    uint32_t muxSwitch;
    uint32_t muxSwitchSqCtrl;
    bool configRouting;
    uint32_t vrefMvValue;
    cy_en_sar_clock_source_t clock;
    cy_stc_sar_fifo_config_t const * fifoCfgPtr;
    bool trTimer;
    bool scanCnt;
    bool scanCntIntr;
} cy_stc_sar_config_t;

#define CY_SAR_WRK_MAX_12BIT            (0x00001000L)
#define SAR_SAMPLE_CTRL(x)  (SYSTICK_CTRL)
#define SAR_CHAN_EN(x)      (0)

#define Cy_SAR_Init(base, config) (CY_RSLT_SUCCESS)
#define Cy_SAR_DeInit(base, deInitRouting) (CY_RSLT_SUCCESS)
#define Cy_SAR_Enable(base)
#define Cy_SAR_Disable(base)
#define Cy_SAR_CountsTo_uVolts(base, chan, adcCounts) (0)
#define Cy_SAR_SetVssaSarSeqCtrl(base, ctrl)
#define Cy_SAR_ClearInterrupt(base, intrMask)
#define Cy_SAR_StartConvert(base, startSelect)
#define Cy_SAR_GetResult32(base, chan) (0)
#define Cy_SAR_SetInterruptMask(base, intrMask)

#define Cy_SAR_SetOffset(chan, offset) (CY_RSLT_SUCCESS)
#define Cy_SAR_SetVssaVminusSwitch(base, state)
#define Cy_SAR_StopConvert(base)
#define Cy_SAR_SetAnalogSwitch(base, switchSelect, switchMask, state)
#define Cy_SAR_SetChanMask(base, enableMask)
#define Cy_SAR_SetConvertMode(base, mode)
#define Cy_SAR_SetSwitchSarSeqCtrl(base, switchMask, ctrl)
#endif

/** \endcond */
