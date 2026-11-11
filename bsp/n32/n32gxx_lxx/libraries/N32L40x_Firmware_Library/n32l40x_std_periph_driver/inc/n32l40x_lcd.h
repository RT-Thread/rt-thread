/*****************************************************************************
 * Copyright (c) 2022, Nations Technologies Inc.
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
 * @file n32l40x_lcd.hd
 * @author Nations
 * @version v1.2.0
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */

#ifndef __N32L40X_LCD_H__
#define __N32L40X_LCD_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "n32l40x.h"
/** @addtogroup N32L40x_StdPeriph_Driver
 * @{
 */

/** @addtogroup LCD
 * @{
 */

/* LCD Exported constants --------------------------------------------------------*/
/** @addtogroup LCD_Exported_Constants LCD Exported Constants
  * @{
  */

/**
 * @brief   LCD error code
 */
typedef enum {
    LCD_ERROR_OK        = 0x00,     /*!< No error */
    LCD_ERROR_FCRSF     = 0x01,     /*!< Synchro flag error */
    LCD_ERROR_UDR       = 0x02,     /*!< Update display request flag error */
    LCD_ERROR_UDD       = 0x03,     /*!< Update display done flag error */
    LCD_ERROR_ENSTS     = 0x04,     /*!< LCD enabled status flag error */
    LCD_ERROR_RDY       = 0x05,     /*!< LCD VLCD ready flag error */
    LCD_ERROR_PARAM     = 0x06,     /*!< LCD function parameter error */
    LCD_ERROR_CLK       = 0x07,     /*!< LCD clock source fail error */
}LCD_ErrorTypeDef;

/**
* @brief    LCD normal timeout
*/
#define LCD_TIME_OUT    (0x01000000)

/**
 * @defgroup   LCD_Clock_Source
 */
#define LCD_CLK_SRC_LSI                 (RCC_RTCCLK_SRC_LSI)                        /*!< LSI*/
#define LCD_CLK_SRC_LSE                 (RCC_LSE_ENABLE|RCC_RTCCLK_SRC_LSE)         /*!< LSE */
#define LCD_CLK_SRC_LSE_BYPASS          (RCC_LSE_BYPASS|RCC_RTCCLK_SRC_LSE)         /*!< LSE bypass */
#define LCD_CLK_SRC_HSE_DIV32           (RCC_HSE_ENABLE|RCC_RTCCLK_SRC_HSE_DIV32)   /*!< HSE */
#define LCD_CLK_SRC_HSE_BYPASS_DIV32    (RCC_HSE_BYPASS|RCC_RTCCLK_SRC_HSE_DIV32)   /*!< HSE bypass */

/**
  * @}
  */

/**
 * @defgroup   LCD_RAMRegister
 */
#define LCD_RAM1_COM0   (0x00000000U)
#define LCD_RAM2_COM0   (0x00000001U)
#define LCD_RAM1_COM1   (0x00000002U)
#define LCD_RAM2_COM1   (0x00000003U)
#define LCD_RAM1_COM2   (0x00000004U)
#define LCD_RAM2_COM2   (0x00000005U)
#define LCD_RAM1_COM3   (0x00000006U)
#define LCD_RAM2_COM3   (0x00000007U)
#define LCD_RAM1_COM4   (0x00000008U)
#define LCD_RAM2_COM4   (0x00000009U)
#define LCD_RAM1_COM5   (0x0000000AU)
#define LCD_RAM2_COM5   (0x0000000BU)
#define LCD_RAM1_COM6   (0x0000000CU)
#define LCD_RAM2_COM6   (0x0000000DU)
#define LCD_RAM1_COM7   (0x0000000EU)
#define LCD_RAM2_COM7   (0x0000000FU)
/**
  * @}
  */

/**
 * @defgroup   LCD_Prescaler
 */
#define LCD_PRESCALER_1         (0x00000000U)                   /*!< CLKPS = LCDCLK         */
#define LCD_PRESCALER_2         (0x1UL << LCD_FCTRL_PRES_Pos)   /*!< 0x00400000U  CLKPS = LCDCLK/2      */
#define LCD_PRESCALER_4         (0x2UL << LCD_FCTRL_PRES_Pos)   /*!< 0x00800000U  CLKPS = LCDCLK/4      */
#define LCD_PRESCALER_8         (0x3UL << LCD_FCTRL_PRES_Pos)   /*!< 0x00C00000U  CLKPS = LCDCLK/8      */
#define LCD_PRESCALER_16        (0x4UL << LCD_FCTRL_PRES_Pos)   /*!< 0x01000000U  CLKPS = LCDCLK/16     */
#define LCD_PRESCALER_32        (0x5UL << LCD_FCTRL_PRES_Pos)   /*!< 0x01400000U  CLKPS = LCDCLK/32     */
#define LCD_PRESCALER_64        (0x6UL << LCD_FCTRL_PRES_Pos)   /*!< 0x01800000U  CLKPS = LCDCLK/64     */
#define LCD_PRESCALER_128       (0x7UL << LCD_FCTRL_PRES_Pos)   /*!< 0x01C00000U  CLKPS = LCDCLK/128    */
#define LCD_PRESCALER_256       (0x8UL << LCD_FCTRL_PRES_Pos)   /*!< 0x02000000U  CLKPS = LCDCLK/256    */
#define LCD_PRESCALER_512       (0x9UL << LCD_FCTRL_PRES_Pos)   /*!< 0x02400000U  CLKPS = LCDCLK/512    */
#define LCD_PRESCALER_1024      (0xAUL << LCD_FCTRL_PRES_Pos)   /*!< 0x02800000U  CLKPS = LCDCLK/1024   */
#define LCD_PRESCALER_2048      (0xBUL << LCD_FCTRL_PRES_Pos)   /*!< 0x02C00000U  CLKPS = LCDCLK/2048   */
#define LCD_PRESCALER_4096      (0xCUL << LCD_FCTRL_PRES_Pos)   /*!< 0x03000000U  CLKPS = LCDCLK/4096   */
#define LCD_PRESCALER_8192      (0xDUL << LCD_FCTRL_PRES_Pos)   /*!< 0x03400000U  CLKPS = LCDCLK/8192   */
#define LCD_PRESCALER_16384     (0xEUL << LCD_FCTRL_PRES_Pos)   /*!< 0x03800000U  CLKPS = LCDCLK/16384  */
#define LCD_PRESCALER_32768     (0xFUL << LCD_FCTRL_PRES_Pos)   /*!< 0x03C00000U  CLKPS = LCDCLK/32768  */
/**
  * @}
  */

/**
 * @defgroup   LCD_Divider
 */
#define LCD_DIV_16      (0x00000000U)   /*!< CLKDIV = CLKPS/(16) */
#define LCD_DIV_17      (0x1UL << LCD_FCTRL_DIV_Pos)    /*!< 0x00040000U  CLKDIV = CLKPS/(17) */
#define LCD_DIV_18      (0x2UL << LCD_FCTRL_DIV_Pos)    /*!< 0x00080000U  CLKDIV = CLKPS/(18) */
#define LCD_DIV_19      (0x3UL << LCD_FCTRL_DIV_Pos)    /*!< 0x000C0000U  CLKDIV = CLKPS/(19) */
#define LCD_DIV_20      (0x4UL << LCD_FCTRL_DIV_Pos)    /*!< 0x00100000U  CLKDIV = CLKPS/(20) */
#define LCD_DIV_21      (0x5UL << LCD_FCTRL_DIV_Pos)    /*!< 0x00140000U  CLKDIV = CLKPS/(21) */
#define LCD_DIV_22      (0x6UL << LCD_FCTRL_DIV_Pos)    /*!< 0x00180000U  CLKDIV = CLKPS/(22) */
#define LCD_DIV_23      (0x7UL << LCD_FCTRL_DIV_Pos)    /*!< 0x001C0000U  CLKDIV = CLKPS/(23) */
#define LCD_DIV_24      (0x8UL << LCD_FCTRL_DIV_Pos)    /*!< 0x00200000U  CLKDIV = CLKPS/(24) */
#define LCD_DIV_25      (0x9UL << LCD_FCTRL_DIV_Pos)    /*!< 0x00240000U  CLKDIV = CLKPS/(25) */
#define LCD_DIV_26      (0xAUL << LCD_FCTRL_DIV_Pos)    /*!< 0x00280000U  CLKDIV = CLKPS/(26) */
#define LCD_DIV_27      (0xBUL << LCD_FCTRL_DIV_Pos)    /*!< 0x002C0000U  CLKDIV = CLKPS/(27) */
#define LCD_DIV_28      (0xCUL << LCD_FCTRL_DIV_Pos)    /*!< 0x00300000U  CLKDIV = CLKPS/(28) */
#define LCD_DIV_29      (0xDUL << LCD_FCTRL_DIV_Pos)    /*!< 0x00340000U  CLKDIV = CLKPS/(29) */
#define LCD_DIV_30      (0xEUL << LCD_FCTRL_DIV_Pos)    /*!< 0x00380000U  CLKDIV = CLKPS/(30) */
#define LCD_DIV_31      (0xFUL << LCD_FCTRL_DIV_Pos)    /*!< 0x003C0000U  CLKDIV = CLKPS/(31) */
/**
  * @}
  */

/**
 * @defgroup   LCD_Duty
 */
#define LCD_DUTY_STATIC (0x00000000U)                   /*!< Static duty */
#define LCD_DUTY_1_2    (0x1UL << LCD_CTRL_DUTY_Pos)    /*!< 0x00000004U  1/2 duty    */
#define LCD_DUTY_1_3    (0x2UL << LCD_CTRL_DUTY_Pos)    /*!< 0x00000004U  1/3 duty    */
#define LCD_DUTY_1_4    (0x3UL << LCD_CTRL_DUTY_Pos)    /*!< 0x00000004U  1/4 duty    */
#define LCD_DUTY_1_8    (0x4UL << LCD_CTRL_DUTY_Pos)    /*!< 0x00000004U  1/8 duty    */
/**
  * @}
  */

/**
 * @defgroup   LCD_Bias
 */
#define LCD_BIAS_1_2    (0x00000000U)                   /*!< 1/2 Bias */
#define LCD_BIAS_1_3    (0x1UL << LCD_CTRL_BIAS_Pos)    /*!< 0x00000020U  1/3 Bias */
#define LCD_BIAS_1_4    (0x2UL << LCD_CTRL_BIAS_Pos)    /*!< 0x00000040U  1/4 Bias */
/**
  * @}
  */

/**
 * @defgroup   LCD_Voltage_source
 */
#define LCD_VOLTAGESOURCE_INTERNAL  (0x00000000U)   /*!< Internal voltage source for the LCD  */
#define LCD_VOLTAGESOURCE_EXTERNAL  (LCD_CTRL_VSEL) /*!< External voltage source for the LCD   */
/**
  * @}
  */

/**
 * @defgroup   LCD_Contrast
 */
#define LCD_CONTRASTLEVEL_0     (0x00000000U)                       /*!< Maximum Voltage = 2.60V    */
#define LCD_CONTRASTLEVEL_1     (0x1UL << LCD_FCTRL_CONTRAST_Pos)   /*!< 0x00000400U  Maximum Voltage = 2.73V    */
#define LCD_CONTRASTLEVEL_2     (0x2UL << LCD_FCTRL_CONTRAST_Pos)   /*!< 0x00000800U  Maximum Voltage = 2.86V    */
#define LCD_CONTRASTLEVEL_3     (0x3UL << LCD_FCTRL_CONTRAST_Pos)   /*!< 0x00000C00U  Maximum Voltage = 2.99V    */
#define LCD_CONTRASTLEVEL_4     (0x4UL << LCD_FCTRL_CONTRAST_Pos)   /*!< 0x00001000U  Maximum Voltage = 3.12V    */
#define LCD_CONTRASTLEVEL_5     (0x5UL << LCD_FCTRL_CONTRAST_Pos)   /*!< 0x00001400U  Maximum Voltage = 3.26V    */
#define LCD_CONTRASTLEVEL_6     (0x6UL << LCD_FCTRL_CONTRAST_Pos)   /*!< 0x00001800U  Maximum Voltage = 3.40V    */
#define LCD_CONTRASTLEVEL_7     (0x7UL << LCD_FCTRL_CONTRAST_Pos)   /*!< 0x00001C00U  Maximum Voltage = 3.55V    */
/**
  * @}
  */

/**
 * @defgroup   LCD_DeadTime
 */
#define LCD_DEADTIME_0      (0x00000000U)                   /*!< No dead Time      */
#define LCD_DEADTIME_1      (0x1UL << LCD_FCTRL_DEAD_Pos)   /*!< 0x00000080U One Phase between different couple of Frame   */
#define LCD_DEADTIME_2      (0x2UL << LCD_FCTRL_DEAD_Pos)   /*!< 0x00000100U Two Phase between different couple of Frame   */
#define LCD_DEADTIME_3      (0x3UL << LCD_FCTRL_DEAD_Pos)   /*!< 0x00000180UThree Phase between different couple of Frame */
#define LCD_DEADTIME_4      (0x4UL << LCD_FCTRL_DEAD_Pos)   /*!< 0x00000200UFour Phase between different couple of Frame  */
#define LCD_DEADTIME_5      (0x5UL << LCD_FCTRL_DEAD_Pos)   /*!< 0x00000280UFive Phase between different couple of Frame  */
#define LCD_DEADTIME_6      (0x6UL << LCD_FCTRL_DEAD_Pos)   /*!< 0x00000300USix Phase between different couple of Frame   */
#define LCD_DEADTIME_7      (0x7UL << LCD_FCTRL_DEAD_Pos)   /*!< 0x00000380USeven Phase between different couple of Frame */
/**
  * @}
  */

/**
 * @defgroup   LCD_PulseOnDuration
 */
#define LCD_PULSEONDURATION_0   (0x00000000U)                   /*!<  Pulse ON duration = 0 pulse  */
#define LCD_PULSEONDURATION_1   (0x1U << LCD_FCTRL_PULSEON_Pos) /*!< 0x00000010U Pulse ON duration = 1/CK_PS  */
#define LCD_PULSEONDURATION_2   (0x2U << LCD_FCTRL_PULSEON_Pos) /*!< 0x00000020U Pulse ON duration = 2/CK_PS  */
#define LCD_PULSEONDURATION_3   (0x3U << LCD_FCTRL_PULSEON_Pos) /*!< 0x00000030U Pulse ON duration = 3/CK_PS  */
#define LCD_PULSEONDURATION_4   (0x4U << LCD_FCTRL_PULSEON_Pos) /*!< 0x00000040U Pulse ON duration = 4/CK_PS  */
#define LCD_PULSEONDURATION_5   (0x5U << LCD_FCTRL_PULSEON_Pos) /*!< 0x00000050U Pulse ON duration = 5/CK_PS  */
#define LCD_PULSEONDURATION_6   (0x6U << LCD_FCTRL_PULSEON_Pos) /*!< 0x00000060U Pulse ON duration = 6/CK_PS  */
#define LCD_PULSEONDURATION_7   (0x7U << LCD_FCTRL_PULSEON_Pos) /*!< 0x00000070U Pulse ON duration = 7/CK_PS  */
/**
  * @}
  */

/**
 * @defgroup   LCD_HighDrive
 */
#define LCD_HIGHDRIVE_DISABLE  (0x00000000U)       /*!< High drive disabled */
#define LCD_HIGHDRIVE_ENABLE   (LCD_FCTRL_HDEN)    /*!< High drive enabled  */
/**
  * @}
  */

/**
 * @defgroup   LCD_HighDrive_Buffer
 */
#define LCD_HIGHDRIVEBUFFER_DISABLE    (0x00000000U)       /*!< High drive buffer disabled */
#define LCD_HIGHDRIVEBUFFER_ENABLE     (LCD_CTRL_BUFEN)    /*!< High drive buffer enabled  */
/**
  * @}
  */

/**
 * @defgroup   LCD_Blink_Mode
 */
#define LCD_BLINKMODE_OFF           (0x00000000U)                   /*!< Blink disable  */
#define LCD_BLINKMODE_SEG0_COM0     (0x1UL << LCD_FCTRL_BLINK_Pos)  /*!< 0x00010000U Blink enabled on SEG[0], COM[0] (1 pixel)          */
#define LCD_BLINKMODE_SEG0_ALLCOM   (0x2UL << LCD_FCTRL_BLINK_Pos)  /*!< 0x00020000U Blink enabled on SEG[0], all COM (up to 8 pixels according to the programmed duty)          */
#define LCD_BLINKMODE_ALLSEG_ALLCOM (0x3UL << LCD_FCTRL_BLINK_Pos)  /*!< 0x00030000U Blink enabled on all SEG and all COM (all pixels)  */
/**
  * @}
  */

/**
 * @defgroup   LCD_Blink_Frequency
 */
#define LCD_BLINKFREQ_DIV_8     (0x00000000U)                       /*!< The Blink frequency = fck_div/8    */
#define LCD_BLINKFREQ_DIV_16    (0x1UL << LCD_FCTRL_BLINKF_Pos)     /*!< 0x00002000U The Blink frequency = fck_div/16   */
#define LCD_BLINKFREQ_DIV_32    (0x2UL << LCD_FCTRL_BLINKF_Pos)     /*!< 0x00004000U The Blink frequency = fck_div/32   */
#define LCD_BLINKFREQ_DIV_64    (0x3UL << LCD_FCTRL_BLINKF_Pos)     /*!< 0x00006000U The Blink frequency = fck_div/64   */
#define LCD_BLINKFREQ_DIV_128   (0x4UL << LCD_FCTRL_BLINKF_Pos)     /*!< 0x00008000U The Blink frequency = fck_div/128  */
#define LCD_BLINKFREQ_DIV_256   (0x5UL << LCD_FCTRL_BLINKF_Pos)     /*!< 0x0000A000U The Blink frequency = fck_div/256  */
#define LCD_BLINKFREQ_DIV_512   (0x6UL << LCD_FCTRL_BLINKF_Pos)     /*!< 0x0000C000U The Blink frequency = fck_div/512  */
#define LCD_BLINKFREQ_DIV_1024  (0x7UL << LCD_FCTRL_BLINKF_Pos)     /*!< 0x0000E000U The Blink frequency = fck_div/1024 */
/**
  * @}
  */

/**
 * @defgroup   LCD_MuxSegment
 */
#define LCD_MUXSEGMENT_DISABLE  (0x00000000U)       /*!< Mux segment disabled */
#define LCD_MUXSEGMENT_ENABLE   (LCD_CTRL_MUXSEG)   /*!< Mux segment enabled  */
/**
  * @}
  */

/**
 * @defgroup   LCD_Interrupt
 */
#define LCD_IT_UDD       (LCD_FCTRL_UDDIE)   /*!< Update display done interrupt */
#define LCD_IT_SOF       (LCD_FCTRL_SOFIE)   /*!< Start of frame interrupt */
/**
  * @}
  */

/**
 * @defgroup   LCD_Flag
 */
#define LCD_FLAG_ENSTS  (LCD_STS_ENSTS)     /*!< LCD enable flag*/
#define LCD_FLAG_SOF    (LCD_STS_SOF)       /*!< LCD start of frame event flag*/
#define LCD_FLAG_UDR    (LCD_STS_UDR)       /*!< Update display request Flag*/
#define LCD_FLAG_UDD    (LCD_STS_UDD)       /*!< Update display done event flag */
#define LCD_FLAG_RDY    (LCD_STS_RDY)       /*!< Ready flag */
#define LCD_FLAG_FCRSF  (LCD_STS_FCRSF)     /*!< LCD frame control register synchronization flag */
/**
  * @}
  */

/**
 * @defgroup   LCD_Flag_Clear
 */
#define LCD_FLAG_SOF_CLEAR  (LCD_CLR_SOFCLR)    /*!< Clear LCD start of frame event flag*/
#define LCD_FLAG_UDD_CLEAR  (LCD_CLR_UDDCLR)    /*!< Clear Update display done event flag */
/**
  * @}
  */


/* LCD Exported macros -----------------------------------------------------------*/
/** @defgroup LCD_Exported_Macros LCD Exported Macros
  * @{
  */

/** @brief Enable the LCD peripheral.
  * @param  None
  * @retval None
  */
#define __LCD_ENABLE()      SET_BIT(LCD->CTRL, LCD_CTRL_LCDEN)

/** @brief Disable the LCD peripheral.
  * @param  None
  * @retval None
  */
#define __LCD_DISABLE()      CLEAR_BIT(LCD->CTRL, LCD_CTRL_LCDEN)

/** @brief Enable the LCD voltage output buffer.
  * @param  None
  * @retval None
  */
#define __LCD_HIGHDRIVE_BUF_ENABLE()        SET_BIT(LCD->CTRL, LCD_CTRL_BUFEN)

/** @brief Disable the LCD voltage output buffer.
  * @param  None
  * @retval None
  */
#define __LCD_HIGHDRIVE_BUF_DISABLE()       CLEAR_BIT(LCD->CTRL, LCD_CTRL_BUFEN)

/** @brief Enable the LCD mux segment.
  * @param  None
  * @retval None
  */
#define __LCD_MUXSEG_ENABLE()               SET_BIT(LCD->CTRL, LCD_CTRL_MUXSEG)

/** @brief Disable the LCD mux segment.
  * @param  None
  * @retval None
  */
#define __LCD_MUXSEG_DISABLE()              CLEAR_BIT(LCD->CTRL, LCD_CTRL_MUXSEG)

/** @brief Select internal VLCD as LCD voltage source
  * @param  None
  * @retval None
  */
#define __LCD_SELECT_INTERNAL_VLCD()        CLEAR_BIT(LCD->CTRL, LCD_CTRL_VSEL)

/** @brief Select external VLCD as LCD voltage source
  * @param  None
  * @retval None
  */
#define __LCD_SELECT_EXTERNAL_VLCD()        SET_BIT(LCD->CTRL, LCD_CTRL_VSEL)

/** @brief Enable the LCD high driver mode.
  * @param  None
  * @retval None
  */
#define __LCD_HIGHDRIVE_ENABLE()            SET_BIT(LCD->FCTRL, LCD_FCTRL_HDEN)

/** @brief Disable the LCD high driver mode.
  * @param  None
  * @retval None
  */
#define __LCD_HIGHDRIVE_DISABLE()           CLEAR_BIT(LCD->FCTRL, LCD_FCTRL_HDEN)

/** @brief Config the prescaler factor
  * @param  __PRES__ specifies the LCD prescaler
  *   This parameter can be one of the following values:
  *     @arg LCD_PRESCALER_1:       CLKPS = LCDCLK
  *     @arg LCD_PRESCALER_2:       CLKPS = LCDCLK/2
  *     @arg LCD_PRESCALER_4:       CLKPS = LCDCLK/4
  *     @arg LCD_PRESCALER_8:       CLKPS = LCDCLK/8
  *     @arg LCD_PRESCALER_16:      CLKPS = LCDCLK/16
  *     @arg LCD_PRESCALER_32:      CLKPS = LCDCLK/32
  *     @arg LCD_PRESCALER_64:      CLKPS = LCDCLK/64
  *     @arg LCD_PRESCALER_128:     CLKPS = LCDCLK/128
  *     @arg LCD_PRESCALER_256:     CLKPS = LCDCLK/256
  *     @arg LCD_PRESCALER_512:     CLKPS = LCDCLK/512
  *     @arg LCD_PRESCALER_1024:    CLKPS = LCDCLK/1024
  *     @arg LCD_PRESCALER_2048:    CLKPS = LCDCLK/2048
  *     @arg LCD_PRESCALER_4096:    CLKPS = LCDCLK/4096
  *     @arg LCD_PRESCALER_8192:    CLKPS = LCDCLK/8192
  *     @arg LCD_PRESCALER_16384:   CLKPS = LCDCLK/16384
  *     @arg LCD_PRESCALER_32768:   CLKPS = LCDCLK/32768
  * @retval None
  */
#define __LCD_PRESCALER_CONFIG(__PRES__)    MODIFY_REG(LCD->FCTRL, LCD_FCTRL_PRES,__PRES__)

/** @brief Config the divider factor
  * @param  __DIV__ specifies the LCD divider
  *   This parameter can be one of the following values:
  *     @arg LCD_DIV_16:   CLKDIV = CLKPS/(16)
  *     @arg LCD_DIV_17:   CLKDIV = CLKPS/(17)
  *     @arg LCD_DIV_18:   CLKDIV = CLKPS/(18)
  *     @arg LCD_DIV_19:   CLKDIV = CLKPS/(19)
  *     @arg LCD_DIV_20:   CLKDIV = CLKPS/(20)
  *     @arg LCD_DIV_21:   CLKDIV = CLKPS/(21)
  *     @arg LCD_DIV_22:   CLKDIV = CLKPS/(22)
  *     @arg LCD_DIV_23:   CLKDIV = CLKPS/(23)
  *     @arg LCD_DIV_24:   CLKDIV = CLKPS/(24)
  *     @arg LCD_DIV_25:   CLKDIV = CLKPS/(25)
  *     @arg LCD_DIV_26:   CLKDIV = CLKPS/(26)
  *     @arg LCD_DIV_27:   CLKDIV = CLKPS/(27)
  *     @arg LCD_DIV_28:   CLKDIV = CLKPS/(28)
  *     @arg LCD_DIV_29:   CLKDIV = CLKPS/(29)
  *     @arg LCD_DIV_30:   CLKDIV = CLKPS/(30)
  *     @arg LCD_DIV_31:   CLKDIV = CLKPS/(31)
  * @retval None
  */
#define __LCD_DIVIDER_CONFIG(__DIV__)       MODIFY_REG(LCD->FCTRL, LCD_FCTRL_DIV,__DIV__)

/** @brief Config the blink mode and frequency
  * @param  __BLINKMODE__ specifies the LCD blink mode
  *   This parameter can be one of the following values:
  *     @arg LCD_DIV_16:   CLKDIV = CLKPS/(16)
  *     @arg LCD_BLINKMODE_OFF:             Blink disable
  *     @arg LCD_BLINKMODE_SEG0_COM0:       Blink enabled on SEG[0], COM[0] (1 pixel)
  *     @arg LCD_BLINKMODE_SEG0_ALLCOM:     Blink enabled on SEG[0], all COM (up to 8 pixels according to the programmed duty)
  *     @arg LCD_BLINKMODE_ALLSEG_ALLCOM:   Blink enabled on all SEG and all COM (all pixels)
  * @param  __BLINKFREQUENCY__ specifies the LCD blink frequency
  *   This parameter can be one of the following values:
  *     @arg LCD_BLINKFREQ_DIV_8:       The Blink frequency = fck_div/8
  *     @arg LCD_BLINKFREQ_DIV_16:      The Blink frequency = fck_div/16
  *     @arg LCD_BLINKFREQ_DIV_32:      The Blink frequency = fck_div/32
  *     @arg LCD_BLINKFREQ_DIV_64:      The Blink frequency = fck_div/64
  *     @arg LCD_BLINKFREQ_DIV_128:     The Blink frequency = fck_div/128
  *     @arg LCD_BLINKFREQ_DIV_256:     The Blink frequency = fck_div/256
  *     @arg LCD_BLINKFREQ_DIV_512:     The Blink frequency = fck_div/512
  *     @arg LCD_BLINKFREQ_DIV_1024:    The Blink frequency = fck_div/1024
  * @retval None
  */
#define __LCD_BLINK_CONFIG(__BLINKMODE__,__BLINKFREQUENCY__)    MODIFY_REG(LCD->FCTRL, (LCD_FCTRL_BLINK|LCD_FCTRL_BLINKF),(__BLINKMODE__|__BLINKFREQUENCY__))


/** @brief Config the contrast
  * @param  __CONTRAST__ specifies the LCD contrast
  *   This parameter can be one of the following values:
  *     @arg LCD_CONTRASTLEVEL_0:   Maximum Voltage = 2.60V
  *     @arg LCD_CONTRASTLEVEL_1:   Maximum Voltage = 2.73V
  *     @arg LCD_CONTRASTLEVEL_2:   Maximum Voltage = 2.86V
  *     @arg LCD_CONTRASTLEVEL_3:   Maximum Voltage = 2.99V
  *     @arg LCD_CONTRASTLEVEL_4:   Maximum Voltage = 3.12V
  *     @arg LCD_CONTRASTLEVEL_5:   Maximum Voltage = 3.26V
  *     @arg LCD_CONTRASTLEVEL_6:   Maximum Voltage = 3.40V
  *     @arg LCD_CONTRASTLEVEL_7:   Maximum Voltage = 3.55V
  * @retval None
  */
#define __LCD_CONTRAST_CONFIG(__CONTRAST__)    MODIFY_REG(LCD->FCTRL, LCD_FCTRL_CONTRAST,__CONTRAST__)

/** @brief Config the dead time
  * @param  __CONTRAST__ specifies the LCD dead time
  *   This parameter can be one of the following values:
  *     @arg LCD_DEADTIME_0: No dead Time
  *     @arg LCD_DEADTIME_1: One Phase between different couple of Frame
  *     @arg LCD_DEADTIME_2: Two Phase between different couple of Frame
  *     @arg LCD_DEADTIME_3: Three Phase between different couple of Frame
  *     @arg LCD_DEADTIME_4: Four Phase between different couple of Frame
  *     @arg LCD_DEADTIME_5: Five Phase between different couple of Frame
  *     @arg LCD_DEADTIME_6: Six Phase between different couple of Frame
  *     @arg LCD_DEADTIME_7: Seven Phase between different couple of Frame
  * @retval None
  */
#define __LCD_DEADTIME_CONFIG(__DEADTIME__)    MODIFY_REG(LCD->FCTRL, LCD_FCTRL_DEAD,__DEADTIME__)

/** @brief Config the pulse on duration
  * @param __PULSEON__ specifies the LCD pulse on duration in terms of
  *         CK_PS (prescaled LCD clock period) pulses.
  *   This parameter can be one of the following values:
  *     @arg LCD_PULSEONDURATION_0: 0 pulse
  *     @arg LCD_PULSEONDURATION_1: Pulse ON duration = 1/CK_PS
  *     @arg LCD_PULSEONDURATION_2: Pulse ON duration = 2/CK_PS
  *     @arg LCD_PULSEONDURATION_3: Pulse ON duration = 3/CK_PS
  *     @arg LCD_PULSEONDURATION_4: Pulse ON duration = 4/CK_PS
  *     @arg LCD_PULSEONDURATION_5: Pulse ON duration = 5/CK_PS
  *     @arg LCD_PULSEONDURATION_6: Pulse ON duration = 6/CK_PS
  *     @arg LCD_PULSEONDURATION_7: Pulse ON duration = 7/CK_PS
  * @retval None
  */
#define __LCD_PULSEONDURATION_CONFIG(__PULSEON__)       MODIFY_REG(LCD->FCTRL, LCD_FCTRL_PULSEON,__PULSEON__)

/** @brief  Enable the specified LCD interrupt.
  * @param __INTERRUPT__ specifies the LCD interrupt source to be enabled.
  *          This parameter can be one of the following values:
  *     @arg LCD_IT_SOF: Start of Frame Interrupt
  *     @arg LCD_IT_UDD: Update Display Done Interrupt
  * @retval None
  */
#define __LCD_ENABLE_IT(__INTERRUPT__)                  SET_BIT(LCD->FCTRL, __INTERRUPT__)

/** @brief  Disable the specified LCD interrupt.
  * @param __INTERRUPT__ specifies the LCD interrupt source to be disabled.
  *          This parameter can be one of the following values:
  *     @arg LCD_IT_SOF: Start of Frame Interrupt
  *     @arg LCD_IT_UDD: Update Display Done Interrupt
  * @retval None
  */
#define __LCD_DISABLE_IT(__INTERRUPT__)                 CLEAR_BIT(LCD->FCTRL, __INTERRUPT__)

/** @brief  Check whether the specified LCD interrupt source is enabled or not.
  * @param __INTERRUPT__ specifies the LCD interrupt source to check.
  *        This parameter can be one of the following values:
  *        @arg LCD_IT_SOF: Start of Frame Interrupt
  *        @arg LCD_IT_UDD: Update Display Done Interrupt.
  * @retval The state of __INTERRUPT__
  */
#define __LCD_GET_IT_SOURCE(__INTERRUPT__)              ((LCD->FCTRL) & (__INTERRUPT__))

/** @brief  Set LCD UDR flag for update dispaly request
  * @param  None
  * @retval None
  */
#define __LCD_UPDATE_REQUEST()              SET_BIT(LCD->STS, LCD_FLAG_UDR)

/** @brief  Check whether the specified LCD flag is set or not.
  * @param __FLAG__ specifies the flag to check.
  *        This parameter can be one of the following values:
  *        @arg LCD_FLAG_ENS: LCD Enabled flag. It indicates the LCD controller status.
  * @note  The ENS bit is set immediately when the LCDEN bit in the LCD_CR
  *             goes from 0 to 1. On deactivation it reflects the real status of
  *             LCD so it becomes 0 at the end of the last displayed frame.
  *        @arg LCD_FLAG_SOF: Start of Frame flag. This flag is set by hardware at
  *             the beginning of a new frame, at the same time as the display data is
  *             updated.
  *        @arg LCD_FLAG_UDR: Update Display Request flag.
  *        @arg LCD_FLAG_UDD: Update Display Done flag.
  *        @arg LCD_FLAG_RDY: Step_up converter Ready flag. It indicates the status
  *             of the step-up converter.
  *        @arg LCD_FLAG_FCRSF: LCD Frame Control Register Synchronization Flag.
  *             This flag is set by hardware each time the LCD_FCR register is updated
  *             in the LCDCLK domain.
  * @retval The new state of __FLAG__
  */
#define __LCD_GET_FLAG(__FLAG__)            (((LCD->STS) & (__FLAG__)) == (__FLAG__))

/** @brief  Clear the specified LCD pending flag.
  * @param __FLAG__ specifies the flag to clear.
  *        This parameter can be any combination of the following values:
  *        @arg LCD_FLAG_SOF_CLEAR: Start of Frame Interrupt
  *        @arg LCD_FLAG_UDD_CLEAR: Update Display Done Interrupt
  * @retval None
  */
#define __LCD_CLEAR_FLAG(__FLAG__)                                  \
                    do  {                                           \
                            SET_BIT((LCD->CLR), (__FLAG__));        \
                            CLEAR_BIT((LCD->CLR), (__FLAG__));      \
                        }while (0)

/** @brief  Config LCD to keep display in STOP2 mode.
  * @param  None
  * @retval None
  */
#define __LCD_DISPLAY_IN_STOP2()                                                        \
                    do  {                                                               \
                            SET_BIT(*(__IO uint32_t *)(PWR_BASE+0x08), (0x1UL << 21));  \
                            CLEAR_BIT(*(__IO uint32_t *)(PWR_BASE+0x1c), (0x1UL << 7)); \
                        }while (0)

/* Private macros ------------------------------------------------------------*/
/** @defgroup LCD_Private_Macros LCD Private Macros
  * @{
  */
#define IS_LCD_RAM_REGISTER_INDEX(__RAMRegIndex__)    ((__RAMRegIndex__)<=LCD_RAM2_COM7)

#define IS_LCD_PRESCALER(_PRESCALER_)   \
        (((_PRESCALER_)==LCD_PRESCALER_1)    ||((_PRESCALER_)==LCD_PRESCALER_2)     \
        ||((_PRESCALER_)==LCD_PRESCALER_4)   ||((_PRESCALER_)==LCD_PRESCALER_8)     \
        ||((_PRESCALER_)==LCD_PRESCALER_16)  ||((_PRESCALER_)==LCD_PRESCALER_32)    \
        ||((_PRESCALER_)==LCD_PRESCALER_64)  ||((_PRESCALER_)==LCD_PRESCALER_128)   \
        ||((_PRESCALER_)==LCD_PRESCALER_256) ||((_PRESCALER_)==LCD_PRESCALER_512)   \
        ||((_PRESCALER_)==LCD_PRESCALER_1024)||((_PRESCALER_)==LCD_PRESCALER_2048)  \
        ||((_PRESCALER_)==LCD_PRESCALER_4096)||((_PRESCALER_)==LCD_PRESCALER_8192)  \
        ||((_PRESCALER_)==LCD_PRESCALER_16384)||((_PRESCALER_)==LCD_PRESCALER_32768))

#define IS_LCD_DIVIDER(__DIVIDER__)   \
        (((__DIVIDER__)==LCD_DIV_16)||((__DIVIDER__)==LCD_DIV_17)||((__DIVIDER__)==LCD_DIV_18)      \
        ||((__DIVIDER__)==LCD_DIV_19)||((__DIVIDER__)==LCD_DIV_20)||((__DIVIDER__)==LCD_DIV_21)     \
        ||((__DIVIDER__)==LCD_DIV_22)||((__DIVIDER__)==LCD_DIV_23)||((__DIVIDER__)==LCD_DIV_24)     \
        ||((__DIVIDER__)==LCD_DIV_25)||((__DIVIDER__)==LCD_DIV_26)||((__DIVIDER__)==LCD_DIV_27)     \
        ||((__DIVIDER__)==LCD_DIV_28)||((__DIVIDER__)==LCD_DIV_29)||((__DIVIDER__)==LCD_DIV_30)     \
        ||((__DIVIDER__)==LCD_DIV_31))

#define IS_LCD_DUTY(__DUTY__)   \
        (((__DUTY__)==LCD_DUTY_STATIC)||((__DUTY__)==LCD_DUTY_1_2)    \
        ||((__DUTY__)==LCD_DUTY_1_3)   ||((__DUTY__)==LCD_DUTY_1_4)   \
        ||((__DUTY__)==LCD_DUTY_1_8) )

#define IS_LCD_BIAS(__BIAS__)   \
        (((__BIAS__)==LCD_BIAS_1_2)||((__BIAS__)==LCD_BIAS_1_3)||((__BIAS__)==LCD_BIAS_1_4))

#define IS_LCD_VOLTAGESOURCE(__SOURCE__)   \
        (((__SOURCE__)==LCD_VOLTAGESOURCE_INTERNAL)||((__SOURCE__)==LCD_VOLTAGESOURCE_EXTERNAL))

#define IS_LCD_CONTRASTLEVEL(__CONTRAST__)   \
        (((__CONTRAST__)==LCD_CONTRASTLEVEL_0) ||((__CONTRAST__)==LCD_CONTRASTLEVEL_1)    \
        ||((__CONTRAST__)==LCD_CONTRASTLEVEL_2) ||((__CONTRAST__)==LCD_CONTRASTLEVEL_3)   \
        ||((__CONTRAST__)==LCD_CONTRASTLEVEL_4) ||((__CONTRAST__)==LCD_CONTRASTLEVEL_5)   \
        ||((__CONTRAST__)==LCD_CONTRASTLEVEL_6) ||((__CONTRAST__)==LCD_CONTRASTLEVEL_7))

#define IS_LCD_DEADTIME(__DEADTIME__)   \
        (((__DEADTIME__)==LCD_DEADTIME_0) ||((__DEADTIME__)==LCD_DEADTIME_1)      \
        ||((__DEADTIME__)==LCD_DEADTIME_2) ||((__DEADTIME__)==LCD_DEADTIME_3)     \
        ||((__DEADTIME__)==LCD_DEADTIME_4) ||((__DEADTIME__)==LCD_DEADTIME_5)     \
        ||((__DEADTIME__)==LCD_DEADTIME_6) ||((__DEADTIME__)==LCD_DEADTIME_7))

#define IS_LCD_PULSEONDURATION(__PULSE__)   \
        (((__PULSE__)==LCD_PULSEONDURATION_0) ||((__PULSE__)==LCD_PULSEONDURATION_1)    \
        ||((__PULSE__)==LCD_PULSEONDURATION_2) ||((__PULSE__)==LCD_PULSEONDURATION_3)   \
        ||((__PULSE__)==LCD_PULSEONDURATION_4) ||((__PULSE__)==LCD_PULSEONDURATION_5)   \
        ||((__PULSE__)==LCD_PULSEONDURATION_6) ||((__PULSE__)==LCD_PULSEONDURATION_7))

#define IS_LCD_HIGHDRIVE(__HIGHDRIVE__)   \
        ((((__HIGHDRIVE__))==LCD_HIGHDRIVE_DISABLE)||(((__HIGHDRIVE__))==LCD_HIGHDRIVE_ENABLE))

#define IS_LCD_HIGHDRIVEBUFFER(__HIGHDRIVEBUF__)   \
        (((__HIGHDRIVEBUF__)==LCD_HIGHDRIVEBUFFER_DISABLE)||((__HIGHDRIVEBUF__)==LCD_HIGHDRIVEBUFFER_ENABLE))

#define IS_LCD_BLINKMODE(__BLINKMODE__)   \
        (((__BLINKMODE__)==LCD_BLINKMODE_OFF)          ||((__BLINKMODE__)==LCD_BLINKMODE_SEG0_COM0)         \
        ||((__BLINKMODE__)==LCD_BLINKMODE_SEG0_ALLCOM) ||((__BLINKMODE__)==LCD_BLINKMODE_ALLSEG_ALLCOM))

#define IS_LCD_BLINKFREQ(__BLINKFREQ__)   \
        (((__BLINKFREQ__)==LCD_BLINKFREQ_DIV_8)   ||((__BLINKFREQ__)==LCD_BLINKFREQ_DIV_16)     \
        ||((__BLINKFREQ__)==LCD_BLINKFREQ_DIV_32) ||((__BLINKFREQ__)==LCD_BLINKFREQ_DIV_64)     \
        ||((__BLINKFREQ__)==LCD_BLINKFREQ_DIV_128) ||((__BLINKFREQ__)==LCD_BLINKFREQ_DIV_256)   \
        ||((__BLINKFREQ__)==LCD_BLINKFREQ_DIV_512) ||((__BLINKFREQ__)==LCD_BLINKFREQ_DIV_1024))

#define IS_LCD_MUXSEGMENT(__MUXSEG__)   \
        (((__MUXSEG__)==LCD_MUXSEGMENT_DISABLE)||((__MUXSEG__)==LCD_MUXSEGMENT_ENABLE))

#define IS_LCD_FLAG(__FLAG__) \
        (((__FLAG__)==LCD_FLAG_ENSTS)||((__FLAG__)==LCD_FLAG_SOF)       \
        ||((__FLAG__)==LCD_FLAG_UDR)||((__FLAG__)==LCD_FLAG_UDD)      \
        ||((__FLAG__)==LCD_FLAG_RDY)||((__FLAG__)==LCD_FLAG_FCRSF))

#define IS_LCD_CLR_FLAG(__CLEARFLAG__)    (((__CLEARFLAG__)==LCD_FLAG_SOF_CLEAR)||((__CLEARFLAG__)==LCD_FLAG_UDD_CLEAR)


/**
  * @brief LCD Init structure definition
  */

typedef struct
{
  uint32_t  Prescaler;          /*!< Configures the LCD Prescaler.
                                    This parameter can be one value of @ref LCD_Prescaler */
  uint32_t  Divider;            /*!< Configures the LCD Divider.
                                    This parameter can be one value of @ref LCD_Divider */
  uint32_t  Duty;               /*!< Configures the LCD Duty.
                                    This parameter can be one value of @ref LCD_Duty */
  uint32_t  Bias;               /*!< Configures the LCD Bias.
                                    This parameter can be one value of @ref LCD_Bias */
  uint32_t  VoltageSource;      /*!< Selects the LCD Voltage source.
                                    This parameter can be one value of @ref LCD_Voltage_source */
  uint32_t  Contrast;           /*!< Configures the LCD Contrast.
                                    This parameter can be one value of @ref LCD_Contrast */
  uint32_t  DeadTime;           /*!< Configures the LCD Dead Time.
                                    This parameter can be one value of @ref LCD_DeadTime */
  uint32_t  PulseOnDuration;    /*!< Configures the LCD Pulse On Duration.
                                    This parameter can be one value of @ref LCD_PulseOnDuration */
  uint32_t  HighDrive;          /*!< Enable or disable the permanent high driver.
                                    This parameter can be one value of @ref LCD_HighDrive */
  uint32_t  HighDriveBuffer;    /*!< Enable or disable the high driver buffer.
                                    This parameter can be one value of @ref LCD_HighDrive_Buffer */
  uint32_t  BlinkMode;          /*!< Configures the LCD Blink Mode.
                                    This parameter can be one value of @ref LCD_Blink_Mode */
  uint32_t  BlinkFreq;          /*!< Configures the LCD Blink frequency.
                                    This parameter can be one value of @ref LCD_Blink_Frequency */
  uint32_t  MuxSegment;         /*!< Enable or disable mux segment.
                                    This parameter can be one value of @ref LCD_MuxSegment */
}LCD_InitType;


/** @addtogroup LCD_Exported_Functions
  * @{
  */
LCD_ErrorTypeDef LCD_Init(LCD_InitType *LCD_InitStructure );
void LCD_DeInit(void);

LCD_ErrorTypeDef LCD_ClockConfig(uint32_t LCD_ClkSource);

void LCD_RamClear(void);

LCD_ErrorTypeDef LCD_UpdateDisplayRequest(void);

LCD_ErrorTypeDef LCD_Write(uint32_t RAMRegisterIndex,uint32_t RAMRegisterMask,uint32_t RAMData);


LCD_ErrorTypeDef LCD_SetBit(uint32_t RAMRegisterIndex,uint32_t RAMData);

LCD_ErrorTypeDef LCD_ClearBit(uint32_t RAMRegisterIndex,uint32_t RAMData);

LCD_ErrorTypeDef LCD_WaitForSynchro(void);

/**
  * @}
  */



#ifdef __cplusplus
 }
#endif

#endif /* __N32L40X_LCD_H__ */
 /**
  * @}
  */

 /**
  * @}
  */

 /**
  * @}
  */


