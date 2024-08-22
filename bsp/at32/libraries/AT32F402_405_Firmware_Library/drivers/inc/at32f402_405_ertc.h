/**
  **************************************************************************
  * @file     at32f402_405_ertc.h
  * @brief    at32f402_405 ertc header file
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F402_405_ERTC_H
#define __AT32F402_405_ERTC_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "at32f402_405.h"

/** @addtogroup AT32F402_405_periph_driver
  * @{
  */

/** @addtogroup ERTC
  * @{
  */

/** @defgroup ERTC_interrupts_definition
  * @brief ertc interrupt
  * @{
  */

#define ERTC_TP_INT                      ((uint32_t)0x00000004) /*!< ertc tamper interrupt */
#define ERTC_ALA_INT                     ((uint32_t)0x00001000) /*!< ertc alarm a interrupt */
#define ERTC_ALB_INT                     ((uint32_t)0x00002000) /*!< ertc alarm b interrupt */
#define ERTC_WAT_INT                     ((uint32_t)0x00004000) /*!< ertc wakeup timer interrupt */
#define ERTC_TS_INT                      ((uint32_t)0x00008000) /*!< ertc timestamp interrupt */

/**
  * @}
  */

/** @defgroup ERTC_flags_definition
  * @brief ertc flag
  * @{
  */

#define ERTC_ALAWF_FLAG                  ((uint32_t)0x00000001) /*!< ertc alarm a register allows write flag */
#define ERTC_ALBWF_FLAG                  ((uint32_t)0x00000002) /*!< ertc alarm b register allows write flag */
#define ERTC_WATWF_FLAG                  ((uint32_t)0x00000004) /*!< ertc wakeup timer register allows write flag */
#define ERTC_TADJF_FLAG                  ((uint32_t)0x00000008) /*!< ertc time adjustment flag */
#define ERTC_INITF_FLAG                  ((uint32_t)0x00000010) /*!< ertc calendar initialization flag */
#define ERTC_UPDF_FLAG                   ((uint32_t)0x00000020) /*!< ertc calendar update flag */
#define ERTC_IMF_FLAG                    ((uint32_t)0x00000040) /*!< ertc enter initialization mode flag */
#define ERTC_ALAF_FLAG                   ((uint32_t)0x00000100) /*!< ertc alarm clock a flag */
#define ERTC_ALBF_FLAG                   ((uint32_t)0x00000200) /*!< ertc alarm clock b flag */
#define ERTC_WATF_FLAG                   ((uint32_t)0x00000400) /*!< ertc wakeup timer flag */
#define ERTC_TSF_FLAG                    ((uint32_t)0x00000800) /*!< ertc timestamp flag */
#define ERTC_TSOF_FLAG                   ((uint32_t)0x00001000) /*!< ertc timestamp overflow flag */
#define ERTC_TP1F_FLAG                   ((uint32_t)0x00002000) /*!< ertc tamper detection 1 flag */
#define ERTC_TP2F_FLAG                   ((uint32_t)0x00004000) /*!< ertc tamper detection 2 flag */
#define ERTC_CALUPDF_FLAG                ((uint32_t)0x00010000) /*!< ertc calibration value update completed flag */

/**
  * @brief ertc alarm mask
  */
#define ERTC_ALARM_MASK_NONE             ((uint32_t)0x00000000) /*!< ertc alarm match all */
#define ERTC_ALARM_MASK_SEC              ((uint32_t)0x00000080) /*!< ertc alarm don't match seconds */
#define ERTC_ALARM_MASK_MIN              ((uint32_t)0x00008000) /*!< ertc alarm don't match minute */
#define ERTC_ALARM_MASK_HOUR             ((uint32_t)0x00800000) /*!< ertc alarm don't match hour */
#define ERTC_ALARM_MASK_DATE_WEEK        ((uint32_t)0x80000000) /*!< ertc alarm don't match date or week */
#define ERTC_ALARM_MASK_ALL              ((uint32_t)0x80808080) /*!< ertc alarm don't match all */

/**
  * @}
  */

/** @defgroup ERTC_exported_types
  * @{
  */

/**
  * @brief ertc hour mode
  */
typedef enum
{
  ERTC_HOUR_MODE_24                      = 0x00, /*!< 24-hour format */
  ERTC_HOUR_MODE_12                      = 0x01  /*!< 12-hour format */
} ertc_hour_mode_set_type;

/**
  * @brief ertc 12-hour format am/pm
  */
typedef enum
{
  ERTC_24H                               = 0x00, /*!< 24-hour format */
  ERTC_AM                                = 0x00, /*!< 12-hour format, ante meridiem */
  ERTC_PM                                = 0x01  /*!< 12-hour format, meridiem */
} ertc_am_pm_type;

/**
  * @brief ertc week or date select
  */
typedef enum
{
  ERTC_SLECT_DATE                        = 0x00, /*!< slect date mode */
  ERTC_SLECT_WEEK                        = 0x01  /*!< slect week mode */
} ertc_week_date_select_type;

/**
  * @brief ertc alarm x select
  */
typedef enum
{
  ERTC_ALA                               = 0x00, /*!< select alarm a */
  ERTC_ALB                               = 0x01  /*!< select alarm b */
} ertc_alarm_type;

/**
  * @brief ertc alarm sub second mask
  */
typedef enum
{
  ERTC_ALARM_SBS_MASK_ALL                = 0x00, /*!< do not match the sub-second */
  ERTC_ALARM_SBS_MASK_14_1               = 0x01, /*!< only compare bit [0] */
  ERTC_ALARM_SBS_MASK_14_2               = 0x02, /*!< only compare bit [1:0] */
  ERTC_ALARM_SBS_MASK_14_3               = 0x03, /*!< only compare bit [2:0] */
  ERTC_ALARM_SBS_MASK_14_4               = 0x04, /*!< only compare bit [3:0] */
  ERTC_ALARM_SBS_MASK_14_5               = 0x05, /*!< only compare bit [4:0] */
  ERTC_ALARM_SBS_MASK_14_6               = 0x06, /*!< only compare bit [5:0] */
  ERTC_ALARM_SBS_MASK_14_7               = 0x07, /*!< only compare bit [6:0] */
  ERTC_ALARM_SBS_MASK_14_8               = 0x08, /*!< only compare bit [7:0] */
  ERTC_ALARM_SBS_MASK_14_9               = 0x09, /*!< only compare bit [8:0] */
  ERTC_ALARM_SBS_MASK_14_10              = 0x0A, /*!< only compare bit [9:0] */
  ERTC_ALARM_SBS_MASK_14_11              = 0x0B, /*!< only compare bit [10:0] */
  ERTC_ALARM_SBS_MASK_14_12              = 0x0C, /*!< only compare bit [11:0] */
  ERTC_ALARM_SBS_MASK_14_13              = 0x0D, /*!< only compare bit [12:0] */
  ERTC_ALARM_SBS_MASK_14                 = 0x0E, /*!< only compare bit [13:0] */
  ERTC_ALARM_SBS_MASK_NONE               = 0x0F  /*!< compare bit [14:0] */
} ertc_alarm_sbs_mask_type;

/**
  * @brief ertc wakeup timer clock select
  */
typedef enum
{
  ERTC_WAT_CLK_ERTCCLK_DIV16             = 0x00, /*!< the wake up timer clock is ERTC_CLK / 16 */
  ERTC_WAT_CLK_ERTCCLK_DIV8              = 0x01, /*!< the wake up timer clock is ERTC_CLK / 8 */
  ERTC_WAT_CLK_ERTCCLK_DIV4              = 0x02, /*!< the wake up timer clock is ERTC_CLK / 4 */
  ERTC_WAT_CLK_ERTCCLK_DIV2              = 0x03, /*!< the wake up timer clock is ERTC_CLK / 2 */
  ERTC_WAT_CLK_CK_B_16BITS               = 0x04, /*!< the wake up timer clock is CK_B, wakeup counter = ERTC_WAT */
  ERTC_WAT_CLK_CK_B_17BITS               = 0x06  /*!< the wake up timer clock is CK_B, wakeup counter = ERTC_WAT + 65535 */
} ertc_wakeup_clock_type;

/**
  * @brief ertc smooth calibration period
  */
typedef enum
{
  ERTC_SMOOTH_CAL_PERIOD_32              = 0x00, /*!< 32 second calibration period */
  ERTC_SMOOTH_CAL_PERIOD_16              = 0x01, /*!< 16 second calibration period */
  ERTC_SMOOTH_CAL_PERIOD_8               = 0x02  /*!< 8 second calibration period */
} ertc_smooth_cal_period_type;

/**
  * @brief ertc smooth calibration clock add mode
  */
typedef enum
{
  ERTC_SMOOTH_CAL_CLK_ADD_0              = 0x00, /*!< do not increase clock */
  ERTC_SMOOTH_CAL_CLK_ADD_512            = 0x01  /*!< add 512 clocks */
} ertc_smooth_cal_clk_add_type;

/**
  * @brief ertc calibration direction mode
  */
typedef enum
{
  ERTC_CAL_DIR_POSITIVE                  = 0x00, /*!< positive calibration */
  ERTC_CAL_DIR_NEGATIVE                  = 0x01  /*!< negative calibration */
} ertc_cal_direction_type;

/**
  * @brief ertc calibration output mode
  */
typedef enum
{
  ERTC_CAL_OUTPUT_512HZ                  = 0x00, /*!< output 512 hz */
  ERTC_CAL_OUTPUT_1HZ                    = 0x01  /*!< output 1 hz */
} ertc_cal_output_select_type;

/**
  * @brief time adjust add mode
  */
typedef enum
{
  ERTC_TIME_ADD_NONE                     = 0x00, /*!< none operation */
  ERTC_TIME_ADD_1S                       = 0x01  /*!< add 1 second */
} ertc_time_adjust_type;

/**
  * @brief ertc daylight saving time hour adjustment mode
  */
typedef enum
{
  ERTC_DST_ADD_1H                        = 0x00, /*!< add 1 hour */
  ERTC_DST_DEC_1H                        = 0x01  /*!< dec 1 hour */
} ertc_dst_operation_type;

/**
  * @brief ertc daylight saving time store operation mode
  */
typedef enum
{
  ERTC_DST_SAVE_0                        = 0x00, /*!< set the bpr register value to 0 */
  ERTC_DST_SAVE_1                        = 0x01  /*!< set the bpr register value to 1 */
} ertc_dst_save_type;

/**
  * @brief output source
  */
typedef enum
{
  ERTC_OUTPUT_DISABLE                    = 0x00, /*!< diable output */
  ERTC_OUTPUT_ALARM_A                    = 0x01, /*!< output alarm a event */
  ERTC_OUTPUT_ALARM_B                    = 0x02, /*!< output alarm b event */
  ERTC_OUTPUT_WAKEUP                     = 0x03  /*!< output wakeup event */
} ertc_output_source_type;

/**
  * @brief output polarity
  */
typedef enum
{
  ERTC_OUTPUT_POLARITY_HIGH              = 0x00, /*!< when the event occurs, the output is high */
  ERTC_OUTPUT_POLARITY_LOW               = 0x01  /*!< when the event occurs, the output is low */
} ertc_output_polarity_type;

/**
  * @brief output type
  */
typedef enum
{
  ERTC_OUTPUT_TYPE_OPEN_DRAIN            = 0x00, /*!< open drain output */
  ERTC_OUTPUT_TYPE_PUSH_PULL             = 0x01  /*!< push pull output */
} ertc_output_type;

/**
  * @brief timestamp/ tamper detection pin selection
  */
typedef enum
{
  ERTC_PIN_PC13                          = 0x00, /*!< pc13 is used as timestamp detection pin */
  ERTC_PIN_PA0                           = 0x01  /*!< pa0 is used as timestamp detection pin */
} ertc_pin_select_type;

/**
  * @brief ertc timestamp valid edge
  */
typedef enum
{
  ERTC_TIMESTAMP_EDGE_RISING             = 0x00, /*!< rising edge trigger */
  ERTC_TIMESTAMP_EDGE_FALLING            = 0x01  /*!< falling edge trigger */
} ertc_timestamp_valid_edge_type;

/**
  * @brief ertc tamper x select
  */
typedef enum
{
  ERTC_TAMPER_1                          = 0x00, /*!< tamper 1 */
  ERTC_TAMPER_2                          = 0x01  /*!< tamper 2 */
} ertc_tamper_select_type;

/**
  * @brief tamper detection pre-charge time
  */
typedef enum
{
  ERTC_TAMPER_PR_1_ERTCCLK               = 0x00, /*!< pre-charge time is 1 ERTC_CLK */
  ERTC_TAMPER_PR_2_ERTCCLK               = 0x01, /*!< pre-charge time is 2 ERTC_CLK */
  ERTC_TAMPER_PR_4_ERTCCLK               = 0x02, /*!< pre-charge time is 4 ERTC_CLK */
  ERTC_TAMPER_PR_8_ERTCCLK               = 0x03  /*!< pre-charge time is 8 ERTC_CLK */
} ertc_tamper_precharge_type;

/**
  * @brief ertc tamper filter
  */
typedef enum
{
  ERTC_TAMPER_FILTER_DISABLE             = 0x00, /*!< disable filter function */
  ERTC_TAMPER_FILTER_2                   = 0x01, /*!< 2 consecutive samples arw valid, effective tamper event */
  ERTC_TAMPER_FILTER_4                   = 0x02, /*!< 4 consecutive samples arw valid, effective tamper event */
  ERTC_TAMPER_FILTER_8                   = 0x03  /*!< 8 consecutive samples arw valid, effective tamper event */
} ertc_tamper_filter_type;

/**
  * @brief ertc tamper detection frequency
  */
typedef enum
{
  ERTC_TAMPER_FREQ_DIV_32768             = 0x00, /*!< ERTC_CLK / 32768 */
  ERTC_TAMPER_FREQ_DIV_16384             = 0x01, /*!< ERTC_CLK / 16384 */
  ERTC_TAMPER_FREQ_DIV_8192              = 0x02, /*!< ERTC_CLK / 8192 */
  ERTC_TAMPER_FREQ_DIV_4096              = 0x03, /*!< ERTC_CLK / 4096 */
  ERTC_TAMPER_FREQ_DIV_2048              = 0x04, /*!< ERTC_CLK / 2048 */
  ERTC_TAMPER_FREQ_DIV_1024              = 0x05, /*!< ERTC_CLK / 1024 */
  ERTC_TAMPER_FREQ_DIV_512               = 0x06, /*!< ERTC_CLK / 512 */
  ERTC_TAMPER_FREQ_DIV_256               = 0x07  /*!< ERTC_CLK / 256 */
} ertc_tamper_detect_freq_type;

/**
  * @brief ertc tamper valid edge
  */
typedef enum
{
  ERTC_TAMPER_EDGE_RISING                = 0x00, /*!< rising gedge */
  ERTC_TAMPER_EDGE_FALLING               = 0x01, /*!< falling gedge */
  ERTC_TAMPER_EDGE_LOW                   = 0x00, /*!< low level */
  ERTC_TAMPER_EDGE_HIGH                  = 0x01  /*!< high level */
} ertc_tamper_valid_edge_type;

/**
  * @brief ertc bpr register
  */
typedef enum
{
  ERTC_DT1                               = 0,  /*!< bpr data register 0 */
  ERTC_DT2                               = 1,  /*!< bpr data register 1 */
  ERTC_DT3                               = 2,  /*!< bpr data register 2 */
  ERTC_DT4                               = 3,  /*!< bpr data register 3 */
  ERTC_DT5                               = 4,  /*!< bpr data register 4 */
  ERTC_DT6                               = 5,  /*!< bpr data register 5 */
  ERTC_DT7                               = 6,  /*!< bpr data register 6 */
  ERTC_DT8                               = 7,  /*!< bpr data register 7 */
  ERTC_DT9                               = 8,  /*!< bpr data register 8 */
  ERTC_DT10                              = 9,  /*!< bpr data register 9 */
  ERTC_DT11                              = 10, /*!< bpr data register 10 */
  ERTC_DT12                              = 11, /*!< bpr data register 11 */
  ERTC_DT13                              = 12, /*!< bpr data register 12 */
  ERTC_DT14                              = 13, /*!< bpr data register 13 */
  ERTC_DT15                              = 14, /*!< bpr data register 14 */
  ERTC_DT16                              = 15, /*!< bpr data register 15 */
  ERTC_DT17                              = 16, /*!< bpr data register 16 */
  ERTC_DT18                              = 17, /*!< bpr data register 17 */
  ERTC_DT19                              = 18, /*!< bpr data register 18 */
  ERTC_DT20                              = 19  /*!< bpr data register 19 */
} ertc_dt_type;

/**
  * @brief ertc time
  */
typedef struct
{
  uint8_t year;                          /*!< year */
  uint8_t month;                         /*!< month */
  uint8_t day;                           /*!< date */
  uint8_t hour;                          /*!< hour */
  uint8_t min;                           /*!< minute */
  uint8_t sec;                           /*!< second */
  uint8_t week;                          /*!< week */
  ertc_am_pm_type ampm;                  /*!< ante meridiem / post meridiem */
} ertc_time_type;

/**
  * @brief ertc alarm
  */
typedef struct
{
  uint8_t day;                           /*!< date */
  uint8_t hour;                          /*!< hour */
  uint8_t min;                           /*!< minute */
  uint8_t sec;                           /*!< second */
  ertc_am_pm_type ampm;                  /*!< ante meridiem / post meridiem */
  uint32_t mask;                         /*!< alarm mask*/
  uint8_t week_date_sel;                 /*!< week or date mode */
  uint8_t week;                          /*!< week */
} ertc_alarm_value_type;

/**
  * @brief ertc time reg union
  */
typedef union
{
  __IO uint32_t time;
  struct
  {
    __IO uint32_t s                      : 7; /* [6:0] */
    __IO uint32_t reserved1              : 1; /* [7] */
    __IO uint32_t m                      : 7; /* [14:8] */
    __IO uint32_t reserved2              : 1; /* [15] */
    __IO uint32_t h                      : 6; /* [21:16] */
    __IO uint32_t ampm                   : 1; /* [22] */
    __IO uint32_t reserved3              : 9; /* [31:23] */
  } time_bit;
} ertc_reg_time_type;

/**
  * @brief ertc date reg union
  */
typedef union
{
  __IO uint32_t date;
  struct
  {
    __IO uint32_t d                      :6; /* [5:0] */
    __IO uint32_t reserved1              :2; /* [7:6] */
    __IO uint32_t m                      :5; /* [12:8] */
    __IO uint32_t wk                     :3; /* [15:13] */
    __IO uint32_t y                      :8; /* [23:16] */
    __IO uint32_t reserved2              :8; /* [31:24] */
  } date_bit;
} ertc_reg_date_type;

/**
  * @brief ertc alarm reg union
  */
typedef union
{
  __IO uint32_t ala;
  struct
  {
    __IO uint32_t s                      :7; /* [6:0] */
    __IO uint32_t mask1                  :1; /* [7] */
    __IO uint32_t m                      :7; /* [14:8] */
    __IO uint32_t mask2                  :1; /* [15] */
    __IO uint32_t h                      :6; /* [21:16] */
    __IO uint32_t ampm                   :1; /* [22] */
    __IO uint32_t mask3                  :1; /* [23] */
    __IO uint32_t d                      :6; /* [29:24] */
    __IO uint32_t wksel                  :1; /* [30] */
    __IO uint32_t mask4                  :1; /* [31] */
  } ala_bit;
} ertc_reg_alarm_type;

/**
  * @brief ertc scal reg union
  */
typedef union
{
  __IO uint32_t scal;
  struct
  {
    __IO uint32_t dec                    :9; /* [8:0] */
    __IO uint32_t reserved1              :4; /* [12:9] */
    __IO uint32_t cal16                  :1; /* [13] */
    __IO uint32_t cal8                   :1; /* [14] */
    __IO uint32_t add                    :1; /* [15] */
    __IO uint32_t reserved2              :16;/* [31:16] */
  } scal_bit;
} ertc_reg_scal_type;

/**
  * @brief ertc tadj reg union
  */
typedef union
{
  __IO uint32_t tadj;
  struct
  {
    __IO uint32_t decsbs                 :15;/* [14:0] */
    __IO uint32_t reserved1              :16;/* [30:15] */
    __IO uint32_t add1s                  :1; /* [31] */
  } tadj_bit;
} ertc_reg_tadj_type;

/**
  * @brief ertc tstm reg union
  */
typedef union
{
  __IO uint32_t tstm;
  struct
  {
    __IO uint32_t s                      :7; /* [6:0] */
    __IO uint32_t reserved1              :1; /* [7] */
    __IO uint32_t m                      :7; /* [14:8] */
    __IO uint32_t reserved2              :1; /* [15] */
    __IO uint32_t h                      :6; /* [21:16] */
    __IO uint32_t ampm                   :1; /* [22] */
    __IO uint32_t reserved3              :9; /* [31:23] */
  } tstm_bit;
} ertc_reg_tstm_type;

/**
  * @brief ertc tsdt register, offset:0x34
  */
typedef union
{
  __IO uint32_t tsdt;
  struct
  {
    __IO uint32_t d                      :6; /* [5:0] */
    __IO uint32_t reserved1              :2; /* [7:6] */
    __IO uint32_t m                      :5; /* [12:8] */
    __IO uint32_t wk                     :3; /* [15:13] */
    __IO uint32_t reserved2              :16;/* [31:16] */
  } tsdt_bit;
} ertc_reg_tsdt_type;

/**
  * @brief type define ertc register all
  */
typedef struct
{

  /**
    * @brief ertc time register, offset:0x00
    */
  union
  {
    __IO uint32_t time;
    struct
    {
      __IO uint32_t s                    : 7; /* [6:0] */
      __IO uint32_t reserved1            : 1; /* [7] */
      __IO uint32_t m                    : 7; /* [14:8] */
      __IO uint32_t reserved2            : 1; /* [15] */
      __IO uint32_t h                    : 6; /* [21:16] */
      __IO uint32_t ampm                 : 1; /* [22] */
      __IO uint32_t reserved3            : 9; /* [31:23] */
    } time_bit;
  };

  /**
    * @brief ertc date register, offset:0x04
    */
  union
  {
    __IO uint32_t date;
    struct
    {
      __IO uint32_t d                    :6; /* [5:0] */
      __IO uint32_t reserved1            :2; /* [7:6] */
      __IO uint32_t m                    :5; /* [12:8] */
      __IO uint32_t wk                   :3; /* [15:13] */
      __IO uint32_t y                    :8; /* [23:16] */
      __IO uint32_t reserved2            :8; /* [31:24] */
    } date_bit;
  };

  /**
    * @brief ertc ctrl register, offset:0x08
    */
  union
  {
    __IO uint32_t ctrl;
    struct
    {
      __IO uint32_t watclk               :3; /* [2:0] */
      __IO uint32_t tsedg                :1; /* [3] */
      __IO uint32_t rcden                :1; /* [4] */
      __IO uint32_t dren                 :1; /* [5] */
      __IO uint32_t hm                   :1; /* [6] */
      __IO uint32_t ccalen               :1; /* [7] */
      __IO uint32_t alaen                :1; /* [8] */
      __IO uint32_t alben                :1; /* [9] */
      __IO uint32_t waten                :1; /* [10] */
      __IO uint32_t tsen                 :1; /* [11] */
      __IO uint32_t alaien               :1; /* [12] */
      __IO uint32_t albien               :1; /* [13] */
      __IO uint32_t watien               :1; /* [14] */
      __IO uint32_t tsien                :1; /* [15] */
      __IO uint32_t add1h                :1; /* [16] */
      __IO uint32_t dec1h                :1; /* [17] */
      __IO uint32_t bpr                  :1; /* [18] */
      __IO uint32_t calosel              :1; /* [19] */
      __IO uint32_t outp                 :1; /* [20] */
      __IO uint32_t outsel               :2; /* [22:21] */
      __IO uint32_t caloen               :1; /* [23] */
      __IO uint32_t reserved1            :8; /* [31:24] */
    } ctrl_bit;
  };

  /**
    * @brief ertc sts register, offset:0x0C
    */
  union
  {
    __IO uint32_t sts;
    struct
    {
      __IO uint32_t alawf                :1; /* [0] */
      __IO uint32_t albwf                :1; /* [1] */
      __IO uint32_t watwf                :1; /* [2] */
      __IO uint32_t tadjf                :1; /* [3] */
      __IO uint32_t initf                :1; /* [4] */
      __IO uint32_t updf                 :1; /* [5] */
      __IO uint32_t imf                  :1; /* [6] */
      __IO uint32_t imen                 :1; /* [7] */
      __IO uint32_t alaf                 :1; /* [8] */
      __IO uint32_t albf                 :1; /* [9] */
      __IO uint32_t watf                 :1; /* [10] */
      __IO uint32_t tsf                  :1; /* [11] */
      __IO uint32_t tsof                 :1; /* [12] */
      __IO uint32_t tp1f                 :1; /* [13] */
      __IO uint32_t tp2f                 :1; /* [14] */
      __IO uint32_t reserved1            :1; /* [15] */
      __IO uint32_t calupdf              :1; /* [16] */
      __IO uint32_t reserved2            :15;/* [31:17] */
    } sts_bit;
  };

  /**
    * @brief ertc div register, offset:0x10
    */
  union
  {
    __IO uint32_t div;
    struct
    {
      __IO uint32_t divb                 :15;/* [14:0] */
      __IO uint32_t reserved1            :1; /* [15] */
      __IO uint32_t diva                 :7; /* [22:16] */
      __IO uint32_t reserved2            :9; /* [31:23] */
    } div_bit;
  };

  /**
    * @brief ertc wat register, offset:0x14
    */
  union
  {
    __IO uint32_t wat;
    struct
    {
      __IO uint32_t val                  :16;/* [15:0] */
      __IO uint32_t reserved1            :16;/* [31:16] */
    } wat_bit;
  };

  /**
    * @brief ertc ccal register, offset:0x18
    */
  union
  {
    __IO uint32_t ccal;
    struct
    {
      __IO uint32_t calval               :5; /* [4:0] */
      __IO uint32_t reserved1            :2; /* [6:5] */
      __IO uint32_t caldir               :1; /* [7] */
      __IO uint32_t reserved2            :24;/* [31:8] */
    } ccal_bit;
  };

  /**
    * @brief ertc ala register, offset:0x1C
    */
  union
  {
    __IO uint32_t ala;
    struct
    {
      __IO uint32_t s                    :7; /* [6:0] */
      __IO uint32_t mask1                :1; /* [7] */
      __IO uint32_t m                    :7; /* [14:8] */
      __IO uint32_t mask2                :1; /* [15] */
      __IO uint32_t h                    :6; /* [21:16] */
      __IO uint32_t ampm                 :1; /* [22] */
      __IO uint32_t mask3                :1; /* [23] */
      __IO uint32_t d                    :6; /* [29:24] */
      __IO uint32_t wksel                :1; /* [30] */
      __IO uint32_t mask4                :1; /* [31] */
    } ala_bit;
  };

  /**
    * @brief ertc alb register, offset:0x20
    */
  union
  {
    __IO uint32_t alb;
    struct
    {
      __IO uint32_t s                    :7; /* [6:0] */
      __IO uint32_t mask1                :1; /* [7] */
      __IO uint32_t m                    :7; /* [14:8] */
      __IO uint32_t mask2                :1; /* [15] */
      __IO uint32_t h                    :6; /* [21:16] */
      __IO uint32_t ampm                 :1; /* [22] */
      __IO uint32_t mask3                :1; /* [23] */
      __IO uint32_t d                    :6; /* [29:24] */
      __IO uint32_t wksel                :1; /* [30] */
      __IO uint32_t mask4                :1; /* [31] */
    } alb_bit;
  };

  /**
    * @brief ertc wp register, offset:0x24
    */
  union
  {
    __IO uint32_t wp;
    struct
    {
      __IO uint32_t cmd                  :8; /* [7:0] */
      __IO uint32_t reserved1            :24;/* [31:8] */
    } wp_bit;
  };

  /**
    * @brief ertc sbs register, offset:0x28
    */
  union
  {
    __IO uint32_t sbs;
    struct
    {
      __IO uint32_t sbs                  :16;/* [15:0] */
      __IO uint32_t reserved1            :16;/* [31:16] */
    } sbs_bit;
  };

  /**
    * @brief ertc tadj register, offset:0x2C
    */
  union
  {
    __IO uint32_t tadj;
    struct
    {
      __IO uint32_t decsbs               :15;/* [14:0] */
      __IO uint32_t reserved1            :16;/* [30:15] */
      __IO uint32_t add1s                :1; /* [31] */
    } tadj_bit;
  };

  /**
    * @brief ertc tstm register, offset:0x30
    */
  union
  {
    __IO uint32_t tstm;
    struct
    {
      __IO uint32_t s                    :7; /* [6:0] */
      __IO uint32_t reserved1            :1; /* [7] */
      __IO uint32_t m                    :7; /* [14:8] */
      __IO uint32_t reserved2            :1; /* [15] */
      __IO uint32_t h                    :6; /* [21:16] */
      __IO uint32_t ampm                 :1; /* [22] */
      __IO uint32_t reserved3            :9; /* [31:23] */
    } tstm_bit;
  };

  /**
    * @brief ertc tsdt register, offset:0x34
    */
  union
  {
    __IO uint32_t tsdt;
    struct
    {
      __IO uint32_t d                    :6; /* [5:0] */
      __IO uint32_t reserved1            :2; /* [7:6] */
      __IO uint32_t m                    :5; /* [12:8] */
      __IO uint32_t wk                   :3; /* [15:13] */
      __IO uint32_t reserved2            :16;/* [31:16] */
    } tsdt_bit;
  };

  /**
    * @brief ertc tssbs register, offset:0x38
    */
  union
  {
    __IO uint32_t tssbs;
    struct
    {
      __IO uint32_t sbs                  :16;/* [15:0] */
      __IO uint32_t reserved1            :16;/* [31:16] */
    } tssbs_bit;
  };

  /**
    * @brief ertc scal register, offset:0x3C
    */
  union
  {
    __IO uint32_t scal;
    struct
    {
      __IO uint32_t dec                  :9; /* [8:0] */
      __IO uint32_t reserved1            :4; /* [12:9] */
      __IO uint32_t cal16                :1; /* [13] */
      __IO uint32_t cal8                 :1; /* [14] */
      __IO uint32_t add                  :1; /* [15] */
      __IO uint32_t reserved2            :16;/* [31:16] */
    } scal_bit;
  };

  /**
    * @brief ertc tamp register, offset:0x40
    */
  union
  {
    __IO uint32_t tamp;
    struct
    {
      __IO uint32_t tp1en                :1; /* [0] */
      __IO uint32_t tp1edg               :1; /* [1] */
      __IO uint32_t tpien                :1; /* [2] */
      __IO uint32_t tp2en                :1; /* [3] */
      __IO uint32_t tp2edg               :1; /* [4] */
      __IO uint32_t reserved1            :2; /* [6:5] */
      __IO uint32_t tptsen               :1; /* [7] */
      __IO uint32_t tpfreq               :3; /* [10:8] */
      __IO uint32_t tpflt                :2; /* [12:11] */
      __IO uint32_t tppr                 :2; /* [14:13] */
      __IO uint32_t tppu                 :1; /* [15] */
      __IO uint32_t tp1pin               :1; /* [16] */
      __IO uint32_t tspin                :1; /* [17] */
      __IO uint32_t outtype              :1; /* [18] */
      __IO uint32_t reserved2            :13;/* [31:19] */
    } tamp_bit;
  };

  /**
    * @brief ertc alasbs register, offset:0x44
    */
  union
  {
    __IO uint32_t alasbs;
    struct
    {
      __IO uint32_t sbs                  :15;/* [14:0] */
      __IO uint32_t reserved1            :9; /* [23:15] */
      __IO uint32_t sbsmsk               :4; /* [27:24] */
      __IO uint32_t reserved2            :4; /* [31:28] */
    } alasbs_bit;
  };

  /**
    * @brief ertc albsbs register, offset:0x48
    */
  union
  {
    __IO uint32_t albsbs;
    struct
    {
      __IO uint32_t sbs                  :15;/* [14:0] */
      __IO uint32_t reserved1            :9; /* [23:15] */
      __IO uint32_t sbsmsk               :4; /* [27:24] */
      __IO uint32_t reserved2            :4; /* [31:28] */
    } albsbs_bit;
  };

  /**
    * @brief reserved register, offset:0x4c
    */
  __IO uint32_t reserved1;

  /**
    * @brief ertc dt1 register, offset:0x50
    */
  union
  {
    __IO uint32_t dt1;
    struct
    {
      __IO uint32_t dt                   :32;/* [31:0] */
    } dt1_bit;
  };

  /**
    * @brief ertc dt2 register, offset:0x54
    */
  union
  {
    __IO uint32_t dt2;
    struct
    {
      __IO uint32_t dt                   :32;/* [31:0] */
    } dt2_bit;
  };

  /**
    * @brief ertc dt3 register, offset:0x58
    */
  union
  {
    __IO uint32_t dt3;
    struct
    {
      __IO uint32_t dt                   :32;/* [31:0] */
    } dt3_bit;
  };

  /**
    * @brief ertc dt4 register, offset:0x5C
    */
  union
  {
    __IO uint32_t dt4;
    struct
    {
      __IO uint32_t dt                   :32;/* [31:0] */
    } dt4_bit;
  };

  /**
    * @brief ertc dt5 register, offset:0x60
    */
  union
  {
    __IO uint32_t dt5;
    struct
    {
      __IO uint32_t dt                   :32;/* [31:0] */
    } dt5_bit;
  };

  /**
    * @brief ertc dt6 register, offset:0x64
    */
  union
  {
    __IO uint32_t dt6;
    struct
    {
      __IO uint32_t dt                   :32;/* [31:0] */
    } dt6_bit;
  };

  /**
    * @brief ertc dt7 register, offset:0x68
    */
  union
  {
    __IO uint32_t dt7;
    struct
    {
      __IO uint32_t dt                   :32;/* [31:0] */
    } dt7_bit;
  };

  /**
    * @brief ertc dt8 register, offset:0x6C
    */
  union
  {
    __IO uint32_t dt8;
    struct
    {
      __IO uint32_t dt                   :32;/* [31:0] */
    } dt8_bit;
  };

  /**
    * @brief ertc dt9 register, offset:0x70
    */
  union
  {
    __IO uint32_t dt9;
    struct
    {
      __IO uint32_t dt                   :32;/* [31:0] */
    } dt9_bit;
  };

  /**
    * @brief ertc dt10 register, offset:0x74
    */
  union
  {
    __IO uint32_t dt10;
    struct
    {
      __IO uint32_t dt                   :32;/* [31:0] */
    } dt10_bit;
  };

  /**
    * @brief ertc dt11 register, offset:0x78
    */
  union
  {
    __IO uint32_t dt11;
    struct
    {
      __IO uint32_t dt                   :32;/* [31:0] */
    } dt11_bit;
  };

  /**
    * @brief ertc dt12 register, offset:0x7C
    */
  union
  {
    __IO uint32_t dt12;
    struct
    {
      __IO uint32_t dt                   :32;/* [31:0] */
    } dt12_bit;
  };

  /**
    * @brief ertc dt13 register, offset:0x80
    */
  union
  {
    __IO uint32_t dt13;
    struct
    {
      __IO uint32_t dt                   :32;/* [31:0] */
    } dt13_bit;
  };

  /**
    * @brief ertc dt14 register, offset:0x84
    */
  union
  {
    __IO uint32_t dt14;
    struct
    {
      __IO uint32_t dt                   :32;/* [31:0] */
    } dt14_bit;
  };

  /**
    * @brief ertc dt15 register, offset:0x88
    */
  union
  {
    __IO uint32_t dt15;
    struct
    {
      __IO uint32_t dt                   :32;/* [31:0] */
    } dt15_bit;
  };

  /**
    * @brief ertc dt16 register, offset:0x8C
    */
  union
  {
    __IO uint32_t dt16;
    struct
    {
      __IO uint32_t dt                   :32;/* [31:0] */
    } dt16_bit;
  };

  /**
    * @brief ertc dt17 register, offset:0x90
    */
  union
  {
    __IO uint32_t dt17;
    struct
    {
      __IO uint32_t dt                   :32;/* [31:0] */
    } dt17_bit;
  };

  /**
    * @brief ertc dt18 register, offset:0x94
    */
  union
  {
    __IO uint32_t dt18;
    struct
    {
      __IO uint32_t dt                   :32;/* [31:0] */
    } dt18_bit;
  };

  /**
    * @brief ertc dt19 register, offset:0x98
    */
  union
  {
    __IO uint32_t dt19;
    struct
    {
      __IO uint32_t dt                   :32;/* [31:0] */
    } dt19_bit;
  };

  /**
    * @brief ertc dt20 register, offset:0x9C
    */
  union
  {
    __IO uint32_t dt20;
    struct
    {
      __IO uint32_t dt                   :32;/* [31:0] */
    } dt20_bit;
  };


} ertc_type;

/**
  * @}
  */

#define ERTC                              ((ertc_type *) ERTC_BASE)

/** @defgroup ERTC_exported_functions
  * @{
  */

uint8_t ertc_num_to_bcd(uint8_t num);
uint8_t ertc_bcd_to_num(uint8_t bcd);
void ertc_write_protect_enable(void);
void ertc_write_protect_disable(void);
error_status ertc_wait_update(void);
error_status ertc_wait_flag(uint32_t flag, flag_status status);
error_status ertc_init_mode_enter(void);
void ertc_init_mode_exit(void);
error_status ertc_reset(void);
error_status ertc_divider_set(uint16_t div_a, uint16_t div_b);
error_status ertc_hour_mode_set(ertc_hour_mode_set_type mode);
error_status ertc_date_set(uint8_t year, uint8_t month, uint8_t date, uint8_t week);
error_status ertc_time_set(uint8_t hour, uint8_t min, uint8_t sec, ertc_am_pm_type ampm);
void ertc_calendar_get(ertc_time_type* time);
uint32_t ertc_sub_second_get(void);
void ertc_alarm_mask_set(ertc_alarm_type alarm_x, uint32_t mask);
void ertc_alarm_week_date_select(ertc_alarm_type alarm_x, ertc_week_date_select_type wk);
void ertc_alarm_set(ertc_alarm_type alarm_x, uint8_t week_date, uint8_t hour, uint8_t min, uint8_t sec, ertc_am_pm_type ampm);
void ertc_alarm_sub_second_set(ertc_alarm_type alarm_x, uint32_t value, ertc_alarm_sbs_mask_type mask);
error_status ertc_alarm_enable(ertc_alarm_type alarm_x, confirm_state new_state);
void ertc_alarm_get(ertc_alarm_type alarm_x, ertc_alarm_value_type* alarm);
uint32_t ertc_alarm_sub_second_get(ertc_alarm_type alarm_x);
void ertc_wakeup_clock_set(ertc_wakeup_clock_type clock);
void ertc_wakeup_counter_set(uint32_t counter);
uint16_t ertc_wakeup_counter_get(void);
error_status ertc_wakeup_enable(confirm_state new_state);
error_status ertc_smooth_calibration_config(ertc_smooth_cal_period_type period, ertc_smooth_cal_clk_add_type clk_add, uint32_t clk_dec);
error_status ertc_coarse_calibration_set(ertc_cal_direction_type dir, uint32_t value);
error_status ertc_coarse_calibration_enable(confirm_state new_state);
void ertc_cal_output_select(ertc_cal_output_select_type output);
void ertc_cal_output_enable(confirm_state new_state);
error_status ertc_time_adjust(ertc_time_adjust_type add1s, uint32_t decsbs);
void ertc_daylight_set(ertc_dst_operation_type operation, ertc_dst_save_type save);
uint8_t ertc_daylight_bpr_get(void);
error_status ertc_refer_clock_detect_enable(confirm_state new_state);
void ertc_direct_read_enable(confirm_state new_state);
void ertc_output_set(ertc_output_source_type source, ertc_output_polarity_type polarity, ertc_output_type type);
void ertc_timestamp_pin_select(ertc_pin_select_type pin);
void ertc_timestamp_valid_edge_set(ertc_timestamp_valid_edge_type edge);
void ertc_timestamp_enable(confirm_state new_state);
void ertc_timestamp_get(ertc_time_type* time);
uint32_t ertc_timestamp_sub_second_get(void);
void ertc_tamper_1_pin_select(ertc_pin_select_type pin);
void ertc_tamper_pull_up_enable(confirm_state new_state);
void ertc_tamper_precharge_set(ertc_tamper_precharge_type precharge);
void ertc_tamper_filter_set(ertc_tamper_filter_type filter);
void ertc_tamper_detect_freq_set(ertc_tamper_detect_freq_type freq);
void ertc_tamper_valid_edge_set(ertc_tamper_select_type tamper_x, ertc_tamper_valid_edge_type trigger);
void ertc_tamper_timestamp_enable(confirm_state new_state);
void ertc_tamper_enable(ertc_tamper_select_type tamper_x, confirm_state new_state);
void ertc_interrupt_enable(uint32_t source, confirm_state new_state);
flag_status ertc_interrupt_get(uint32_t source);
flag_status ertc_flag_get(uint32_t flag);
flag_status ertc_interrupt_flag_get(uint32_t flag);
void ertc_flag_clear(uint32_t flag);
void ertc_bpr_data_write(ertc_dt_type dt, uint32_t data);
uint32_t ertc_bpr_data_read(ertc_dt_type dt);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif
