/**
  *********************************************************************************
  *
  * @file    ald_lcd.h
  * @brief   Header file of LCD module driver.
  *
  * @version V1.0
  * @date    29 Nov 2017
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  ********************************************************************************
  */

#ifndef __ALD_LCD_H__
#define __ALD_LCD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "utils.h"
#include "ald_cmu.h"

/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup LCD
  * @{
  */

/** @defgroup LCD_Public_Types LCD Public Types
  * @{
  */
/**
  * @brief Lcd vlcd voltage type
  */
typedef enum
{
    LCD_VCHPS_3V2 = 0,	/**< 3.2V */
    LCD_VCHPS_3V8 = 1,	/**< 3.8V */
    LCD_VCHPS_4V8 = 2,	/**< 4.8V */
    LCD_VCHPS_5V4 = 3,	/**< 5.4V */
} lcd_vchps_t;

/**
  * @brief Lcd function type
  */
typedef enum
{
    LCD_FUNC_DISABLE = 0,	/**< Lcd's function disable */
    LCD_FUNC_ENABLE  = 1,	/**< Lcd's function enable */
} lcd_func_t;

/**
  * @brief Lcd voltage type
  */
typedef enum
{
    LCD_VSEL_VDD  = 0,	/**< VDD */
    LCD_VSEL_CP   = 1,	/**< Charge pump output */
    LCD_VSEL_VLCD = 2,	/**< VLCD input */
} lcd_vsel_t;

/**
  * @brief Lcd resistance select bit
  */
typedef enum
{
    LCD_RES_1MOHM = 0,	/**< 1M ohm */
    LCD_RES_2MOHM = 1,	/**< 2M ohm */
    LCD_RES_3MOHM = 2,	/**< 3M ohm */
} lcd_res_t;

/**
  * @brief Lcd bias selector
  */
typedef enum
{
    LCD_BIAS_1_4 = 0,	/**< 1/4 bias */
    LCD_BIAS_1_2 = 2,	/**< 1/2 bias */
    LCD_BIAS_1_3 = 3,	/**< 1/3 bias */
} lcd_bias_t;

/**
  * @brief Lcd duty
  */
typedef enum
{
    LCD_DUTY_STATIC = 0,	/**< Static duty (COM0) */
    LCD_DUTY_1_2    = 1,	/**< 1/2 duty (COM0~COM1) */
    LCD_DUTY_1_3    = 2,	/**< 1/3 duty (COM0~COM2) */
    LCD_DUTY_1_4    = 3,	/**< 1/4 duty (COM0~COM3) */
    LCD_DUTY_1_6    = 4,	/**< 1/6 duty (COM0~COM5) */
    LCD_DUTY_1_8    = 5,	/**< 1/8 duty (COM0~COM7) */
} lcd_duty_t;

/**
  * @brief Lcd prescaler
  */
typedef enum
{
    LCD_PRS_1     = 0, 	/**< CLKPRS = LCDCLK / 1 */
    LCD_PRS_2     = 1, 	/**< CLKPRS = LCDCLK / 2 */
    LCD_PRS_4     = 2, 	/**< CLKPRS = LCDCLK / 4 */
    LCD_PRS_8     = 3, 	/**< CLKPRS = LCDCLK / 8 */
    LCD_PRS_16    = 4, 	/**< CLKPRS = LCDCLK / 16 */
    LCD_PRS_32    = 5, 	/**< CLKPRS = LCDCLK / 32 */
    LCD_PRS_64    = 6, 	/**< CLKPRS = LCDCLK / 64 */
    LCD_PRS_128   = 7, 	/**< CLKPRS = LCDCLK / 128 */
    LCD_PRS_256   = 8, 	/**< CLKPRS = LCDCLK / 256 */
    LCD_PRS_512   = 9, 	/**< CLKPRS = LCDCLK / 512 */
    LCD_PRS_1024  = 10,	/**< CLKPRS = LCDCLK / 1024 */
    LCD_PRS_2048  = 11,	/**< CLKPRS = LCDCLK / 2048 */
    LCD_PRS_4096  = 12,	/**< CLKPRS = LCDCLK / 4096 */
    LCD_PRS_8192  = 13,	/**< CLKPRS = LCDCLK / 8192 */
    LCD_PRS_16384 = 14,	/**< CLKPRS = LCDCLK / 16384 */
    LCD_PRS_32768 = 15,	/**< CLKPRS = LCDCLK / 32768 */
} lcd_prs_t;

/**
  * @brief Lcd divider
  */
typedef enum
{
    LCD_DIV_16 = 0, 	/**< DIVCLK = CLKPRS / 16 */
    LCD_DIV_17 = 1, 	/**< DIVCLK = CLKPRS / 17 */
    LCD_DIV_18 = 2, 	/**< DIVCLK = CLKPRS / 18 */
    LCD_DIV_19 = 3, 	/**< DIVCLK = CLKPRS / 19 */
    LCD_DIV_20 = 4, 	/**< DIVCLK = CLKPRS / 20 */
    LCD_DIV_21 = 5, 	/**< DIVCLK = CLKPRS / 21 */
    LCD_DIV_22 = 6, 	/**< DIVCLK = CLKPRS / 22 */
    LCD_DIV_23 = 7, 	/**< DIVCLK = CLKPRS / 23 */
    LCD_DIV_24 = 8, 	/**< DIVCLK = CLKPRS / 24 */
    LCD_DIV_25 = 9, 	/**< DIVCLK = CLKPRS / 25 */
    LCD_DIV_26 = 10,	/**< DIVCLK = CLKPRS / 26 */
    LCD_DIV_27 = 11,	/**< DIVCLK = CLKPRS / 27 */
    LCD_DIV_28 = 12,	/**< DIVCLK = CLKPRS / 28 */
    LCD_DIV_29 = 13,	/**< DIVCLK = CLKPRS / 29 */
    LCD_DIV_30 = 14,	/**< DIVCLK = CLKPRS / 30 */
    LCD_DIV_31 = 15,	/**< DIVCLK = CLKPRS / 31 */
} lcd_div_t;

/**
  * @brief Lcd blink mode
  */
typedef enum
{
    LCD_BLINK_OFF           = 0,	/**< Blink disabled */
    LCD_BLINK_SEG0_COM0     = 1,	/**< Blink enabled on SEG0, COM0 */
    LCD_BLINK_SEG0_COMX2    = 2,	/**< Blink enabled on SEG0, COMx2 */
    LCD_BLINK_ALLSEG_ALLCOM = 3,	/**< Blink enabled on all SEG and all COM */
} lcd_blink_t;

/**
  * @brief Lcd blink frequency
  */
typedef enum
{
    LCD_BLFRQ_8    = 0,	/**< DIVCLK / 8 */
    LCD_BLFRQ_16   = 1,	/**< DIVCLK / 16 */
    LCD_BLFRQ_32   = 2,	/**< DIVCLK / 32 */
    LCD_BLFRQ_64   = 3,	/**< DIVCLK / 64 */
    LCD_BLFRQ_128  = 4,	/**< DIVCLK / 128 */
    LCD_BLFRQ_256  = 5,	/**< DIVCLK / 256 */
    LCD_BLFRQ_512  = 6,	/**< DIVCLK / 512 */
    LCD_BLFRQ_1024 = 7,	/**< DIVCLK / 1024 */
} lcd_blfrq_t;

/**
  * @brief Lcd dead time
  */
typedef enum
{
    LCD_DEAD_TIME_NONE     = 0,	/**< No dead time */
    LCD_DEAD_TIME_1_DIVCLK = 1,	/**< Dead time is 1 divclk */
    LCD_DEAD_TIME_2_DIVCLK = 2,	/**< Dead time is 2 divclk */
    LCD_DEAD_TIME_3_DIVCLK = 3,	/**< Dead time is 3 divclk */
    LCD_DEAD_TIME_4_DIVCLK = 4,	/**< Dead time is 4 divclk */
    LCD_DEAD_TIME_5_DIVCLK = 5,	/**< Dead time is 5 divclk */
    LCD_DEAD_TIME_6_DIVCLK = 6,	/**< Dead time is 6 divclk */
    LCD_DEAD_TIME_7_DIVCLK = 7,	/**< Dead time is 7 divclk */
} lcd_dead_t;

/**
  * @brief Lcd pulse keep time
  */
typedef enum
{
    LCD_PON_NONE     = 0,	/**< No pulse keep time */
    LCD_PON_1_PRSCLK = 1,	/**< Pulse keep 1 prsclk */
    LCD_PON_2_PRSCLK = 2,	/**< Pulse keep 2 prsclk */
    LCD_PON_3_PRSCLK = 3,	/**< Pulse keep 3 prsclk */
    LCD_PON_4_PRSCLK = 4,	/**< Pulse keep 4 prsclk */
    LCD_PON_5_PRSCLK = 5,	/**< Pulse keep 5 prsclk */
    LCD_PON_6_PRSCLK = 6,	/**< Pulse keep 6 prsclk */
    LCD_PON_7_PRSCLK = 7,	/**< Pulse keep 7 prsclk */
} lcd_pluse_on_t;

/**
  * @brief Lcd vgs select
  */
typedef enum
{
    LCD_VGS_0  = 0, 	/**< Grey level display voltage is 30/45 vlcd */
    LCD_VGS_1  = 1, 	/**< Grey level display voltage is 31/45 vlcd */
    LCD_VGS_2  = 2, 	/**< Grey level display voltage is 32/45 vlcd */
    LCD_VGS_3  = 3, 	/**< Grey level display voltage is 33/45 vlcd */
    LCD_VGS_4  = 4, 	/**< Grey level display voltage is 34/45 vlcd */
    LCD_VGS_5  = 5, 	/**< Grey level display voltage is 35/45 vlcd */
    LCD_VGS_6  = 6, 	/**< Grey level display voltage is 36/45 vlcd */
    LCD_VGS_7  = 7, 	/**< Grey level display voltage is 37/45 vlcd */
    LCD_VGS_8  = 8, 	/**< Grey level display voltage is 38/45 vlcd */
    LCD_VGS_9  = 9, 	/**< Grey level display voltage is 39/45 vlcd */
    LCD_VGS_10 = 10,	/**< Grey level display voltage is 40/45 vlcd */
    LCD_VGS_11 = 11,	/**< Grey level display voltage is 41/45 vlcd */
    LCD_VGS_12 = 12,	/**< Grey level display voltage is 42/45 vlcd */
    LCD_VGS_13 = 13,	/**< Grey level display voltage is 43/45 vlcd */
    LCD_VGS_14 = 14,	/**< Grey level display voltage is 44/45 vlcd */
    LCD_VGS_15 = 15,	/**< Grey level display voltage is equal to vlcd */
} lcd_vgs_t;

/**
  * @brief Lcd wave choose
  */
typedef enum
{
    LCD_WAVE_A = 0,	/**< Wave type is A */
    LCD_WAVE_B = 1,	/**< Wave type is B */
} lcd_wfs_t;

/**
  * @brief Lcd status select bit
  */
typedef enum
{
    LCD_STATUS_RDY   = (1U << 0),	/**< VLCD voltage state flag */
    LCD_STATUS_ENS   = (1U << 1),	/**< LCD Enable state flag*/
    LCD_STATUS_UDR   = (1U << 2),	/**< Update display request state flag */
    LCD_STATUS_FCRSF = (1U << 3),	/**< LCD frame control sync flag */
    LCD_STATUS_ALL   = 0xFFFFFFF,	/**< All flag */
} lcd_status_t;

/**
  * @brief Lcd interrupt type
  */
typedef enum
{
    LCD_IT_SOF = (1U << 0),	/**< Start of frame interrupt enable */
    LCD_IT_UDD = (1U << 1),	/**< Update display done interrupt enable*/
} lcd_it_t;

/**
  * @brief Lcd interrupt flag
  */
typedef enum
{
    LCD_FLAG_SOF = (1U << 0), /**< Start of frame interrupt enable flag*/
    LCD_FLAG_UDD = (1U << 1), /**< Update display done interrupt enable flag*/
} lcd_flag_t;

/**
  * @brief Lcd interrupt type
  */
typedef enum
{
    SEG_0_TO_31  = 0,	/**< Segment 0 to 31 to be set */
    SEG_32_TO_59 = 1,	/**< Segment 32 to 59 to be set */
} lcd_seg_t;

/**
  * @brief Lcd configure
  */
typedef struct
{
    lcd_vsel_t lcd_vsel;      	/**< Lcd power choose */
    lcd_vchps_t lcd_vchps;    	/**< Charge pump voltage choose */
    lcd_func_t lcd_vbufld;    	/**< Low drive mode function */
    lcd_func_t lcd_vbufhd;    	/**< High drive mode function */
    uint32_t lcd_dsld;        	/**< Low drive mode level */
    uint32_t lcd_dshd;        	/**< High drive mode level */
    lcd_res_t lcd_resld;      	/**< Low dirve mode resistance choose */
    lcd_res_t lcd_reshd;      	/**< High dirve mode resistance choose */
    lcd_bias_t lcd_bias;      	/**< LCD bias */
    lcd_duty_t lcd_duty;      	/**< LCD duty */
    lcd_wfs_t lcd_wfs;        	/**< Wave choose */
    lcd_prs_t lcd_prs;        	/**< Lcd clock prs */
    lcd_div_t lcd_div;        	/**< Lcd div */
    lcd_dead_t lcd_dead;      	/**< Lcd dead time */
    lcd_pluse_on_t lcd_pon;   	/**< Lcd pluse on time */
    lcd_vgs_t lcd_vgs;        	/**< Lcd gray level display voltage */
    cmu_lcd_clock_sel_t clock;	/**< Lcd clock choose */
} lcd_init_t;

/**
  * @brief  Lcd handle Structure definition
  */
typedef struct lcd_handle_s
{
    LCD_TypeDef *perh;	/**< LCD registers base address */
    lcd_init_t init;  	/**< LCD initialize parameters */
    lock_state_t lock;	/**< Locking object */

    void (*display_cplt_cbk)(struct lcd_handle_s *arg);	/**< Display completed callback */
    void (*frame_start_cbk)(struct lcd_handle_s *arg); 	/**< Frame start callback */
} lcd_handle_t;

/**
  * @}
  */

/** @defgroup LCD_Public_Macro LCD Public Macros
  * @{
  */
#define LCD_HD_ENABLE(x)	(SET_BIT((x)->perh->FCR, LCD_FCR_HD_MSK))
#define LCD_HD_DISABLE(x)	(CLEAR_BIT((x)->perh->FCR, LCD_FCR_HD_MSK))
/**
  * @}
  */

/**
  * @defgroup LCD_Private_Macros LCD Private Macros
  * @{
  */
#define IS_LCD_PERH_TYPE(x)	((x) == LCD)
#define IS_LCD_VCHPS_TYPE(x)    (((x) == LCD_VCHPS_3V2) || \
                                 ((x) == LCD_VCHPS_3V8) || \
                                 ((x) == LCD_VCHPS_4V8) || \
                                 ((x) == LCD_VCHPS_5V4))
#define IS_LCD_VSEL_TYPE(x)     (((x) == LCD_VSEL_VDD) || \
                                 ((x) == LCD_VSEL_CP)  || \
                                 ((x) == LCD_VSEL_VLCD))
#define IS_LCD_FUNC_TYPE(x)	(((x) == LCD_FUNC_DISABLE) || \
                             ((x) == LCD_FUNC_ENABLE))
#define IS_LCD_LEVEL_TYPE(x)	(((x) > 0) | ((x) <= 0xF))
#define IS_LCD_RES_TYPE(x)      (((x) == LCD_RES_1MOHM) || \
                                 ((x) == LCD_RES_2MOHM) || \
                                 ((x) == LCD_RES_3MOHM))
#define IS_LCD_BIAS_TYPE(x)     (((x) == LCD_BIAS_1_4) || \
                                 ((x) == LCD_BIAS_1_2) || \
                                 ((x) == LCD_BIAS_1_3))
#define IS_LCD_DUTY_TYPE(x)     (((x) == LCD_DUTY_STATIC) || \
                                 ((x) == LCD_DUTY_1_2)    || \
                                 ((x) == LCD_DUTY_1_3)    || \
                                 ((x) == LCD_DUTY_1_4)    || \
                                 ((x) == LCD_DUTY_1_6)    || \
                                 ((x) == LCD_DUTY_1_8))
#define IS_LCD_WFS_TYPE(x)	(((x) == LCD_WAVE_A) || \
                             ((x) == LCD_WAVE_B))
#define IS_LCD_PRS_TYPE(x)      (((x) == LCD_PRS_1)     || \
                                 ((x) == LCD_PRS_2)     || \
                                 ((x) == LCD_PRS_4)     || \
                                 ((x) == LCD_PRS_8)     || \
                                 ((x) == LCD_PRS_16)    || \
                                 ((x) == LCD_PRS_32)    || \
                                 ((x) == LCD_PRS_64)    || \
                                 ((x) == LCD_PRS_128)   || \
                                 ((x) == LCD_PRS_256)   || \
                                 ((x) == LCD_PRS_512)   || \
                                 ((x) == LCD_PRS_1024)  || \
                                 ((x) == LCD_PRS_2048)  || \
                                 ((x) == LCD_PRS_4096)  || \
                                 ((x) == LCD_PRS_8192)  || \
                                 ((x) == LCD_PRS_16384) || \
                                 ((x) == LCD_PRS_32768))
#define IS_LCD_DIV_TYPE(x)      (((x) == LCD_DIV_16) || \
                                 ((x) == LCD_DIV_17) || \
                                 ((x) == LCD_DIV_18) || \
                                 ((x) == LCD_DIV_19) || \
                                 ((x) == LCD_DIV_20) || \
                                 ((x) == LCD_DIV_21) || \
                                 ((x) == LCD_DIV_22) || \
                                 ((x) == LCD_DIV_23) || \
                                 ((x) == LCD_DIV_24) || \
                                 ((x) == LCD_DIV_25) || \
                                 ((x) == LCD_DIV_26) || \
                                 ((x) == LCD_DIV_27) || \
                                 ((x) == LCD_DIV_28) || \
                                 ((x) == LCD_DIV_29) || \
                                 ((x) == LCD_DIV_30) || \
                                 ((x) == LCD_DIV_31))
#define IS_LCD_BLINK_MODE(x)    (((x) == LCD_BLINK_OFF)        || \
                                 ((x) == LCD_BLINK_SEG0_COM0)  || \
                                 ((x) == LCD_BLINK_SEG0_COMX2) || \
                                 ((x) == LCD_BLINK_ALLSEG_ALLCOM))
#define IS_LCD_BLFRQ_TYPE(x)    (((x) == LCD_BLFRQ_8)   || \
                                 ((x) == LCD_BLFRQ_16)  || \
                                 ((x) == LCD_BLFRQ_32)  || \
                                 ((x) == LCD_BLFRQ_64)  || \
                                 ((x) == LCD_BLFRQ_128) || \
                                 ((x) == LCD_BLFRQ_256) || \
                                 ((x) == LCD_BLFRQ_512) || \
                                 ((x) == LCD_BLFRQ_1024))
#define IS_LCD_STATUS_TYPE(x) 	(((x) == LCD_STATUS_RDY)   || \
                                 ((x) == LCD_STATUS_ENS)   || \
                                 ((x) == LCD_STATUS_UDR)   || \
                                 ((x) == LCD_STATUS_FCRSF) || \
                                 ((x) == LCD_STATUS_ALL))
#define IS_LCD_CLEARFLAG_TYPE(x)(((x) == LCD_FLAG_SOF) || \
                                 ((x) == LCD_FLAG_UDD) || \
                                 ((x) == LCD_STATUS_ALL))
#define IS_LCD_IT_TYPE(x)      	(((x) == LCD_IT_SOF) || \
                                 ((x) == LCD_IT_UDD))
#define IS_LCD_FLAG_TYPE(x)	(((x) == LCD_FLAG_SOF) || \
                             ((x) == LCD_FLAG_UDD))
#define IS_LCD_SEG_TYPE(x)	(((x) == SEG_0_TO_31) || \
                             ((x) == SEG_32_TO_59))
#define IS_LCD_DEAD_TYPE(x)	(((x) == LCD_DEAD_TIME_NONE)     || \
                             ((x) == LCD_DEAD_TIME_1_DIVCLK) || \
                             ((x) == LCD_DEAD_TIME_2_DIVCLK) || \
                             ((x) == LCD_DEAD_TIME_3_DIVCLK) || \
                             ((x) == LCD_DEAD_TIME_4_DIVCLK) || \
                             ((x) == LCD_DEAD_TIME_5_DIVCLK) || \
                             ((x) == LCD_DEAD_TIME_6_DIVCLK) || \
                             ((x) == LCD_DEAD_TIME_7_DIVCLK))
#define IS_LCD_PON_TYPE(x)	(((x) == LCD_PON_NONE)     || \
                             ((x) == LCD_PON_1_PRSCLK) || \
                             ((x) == LCD_PON_2_PRSCLK) || \
                             ((x) == LCD_PON_3_PRSCLK) || \
                             ((x) == LCD_PON_4_PRSCLK) || \
                             ((x) == LCD_PON_5_PRSCLK) || \
                             ((x) == LCD_PON_6_PRSCLK) || \
                             ((x) == LCD_PON_7_PRSCLK))
#define IS_LCD_VGS_TYPE(x)	(((x) == LCD_VGS_0)  || \
                             ((x) == LCD_VGS_1)  || \
                             ((x) == LCD_VGS_2)  || \
                             ((x) == LCD_VGS_3)  || \
                             ((x) == LCD_VGS_4)  || \
                             ((x) == LCD_VGS_5)  || \
                             ((x) == LCD_VGS_6)  || \
                             ((x) == LCD_VGS_7)  || \
                             ((x) == LCD_VGS_8)  || \
                             ((x) == LCD_VGS_9)  || \
                             ((x) == LCD_VGS_10) || \
                             ((x) == LCD_VGS_11) || \
                             ((x) == LCD_VGS_12) || \
                             ((x) == LCD_VGS_13) || \
                             ((x) == LCD_VGS_14) || \
                             ((x) == LCD_VGS_15))
#define IS_LCD_BUFFER_TYPE(x)	((x) <= 15)

/**
  * @}
  */

/** @addtogroup LCD_Public_Functions
  * @{
  */

/**
  * @addtogroup LCD_Public_Functions_Group1
  * @{
  */
/* Initialization and enable functions */
ald_status_t ald_lcd_init(lcd_handle_t *hperh);
ald_status_t ald_lcd_cmd(lcd_handle_t *hperh, type_func_t state);
/**
  * @}
  */

/**
  * @addtogroup LCD_Public_Functions_Group2
  * @{
  */
/* Config output and blink function */
ald_status_t ald_lcd_blink_config(lcd_handle_t *hperh, lcd_blink_t blink_mode, lcd_blfrq_t blink_freq);
ald_status_t ald_lcd_write(lcd_handle_t *hperh, uint8_t buf, uint32_t buf_data);
ald_status_t ald_lcd_write_seg(lcd_handle_t *hperh, lcd_seg_t seg, uint32_t seg_data);
/**
  * @}
  */

/**
  * @addtogroup LCD_Public_Functions_Group3
  * @{
  */
/* Query lcd status function */
uint32_t ald_lcd_get_status(lcd_handle_t *hperh, lcd_status_t lcd_flag);
/**
  * @}
  */

/**
  * @addtogroup LCD_Public_Functions_Group4
  * @{
  */
/* Interrupt function */
ald_status_t ald_lcd_interrupt_config(lcd_handle_t *hperh, lcd_it_t it, type_func_t state);
flag_status_t ald_lcd_get_it_status(lcd_handle_t *hperh, lcd_it_t it);
it_status_t ald_lcd_get_flag_status(lcd_handle_t *hperh, lcd_flag_t flag);
ald_status_t ald_lcd_clear_flag_status(lcd_handle_t *hperh, lcd_flag_t flag);
void ald_lcd_irq_handler(lcd_handle_t *hperh);
/**
  * @}
  */

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

#endif /* __ALD_LCD_H__ */
