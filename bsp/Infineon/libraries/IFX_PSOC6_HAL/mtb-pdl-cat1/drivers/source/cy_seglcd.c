/***************************************************************************//**
* \file cy_seglcd.c
* \version 1.10.1
*
* \brief
* Provides an API implementation of the SegLCD driver
*
********************************************************************************
* \copyright
* Copyright 2019-2020 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include "cy_device.h"

#if defined (CY_IP_MXLCD)

#include "cy_seglcd.h"
#include "cy_sysclk.h"

CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 11.3', 28, \
'LCD_Type will typecast to either LCD_V1_Type or LCD_V2_Type but not both on PDL initialization based on the target device at compile time.');

#define CY_SEGLCD_ENABLE_Msk                (LCD_CONTROL_LS_EN_Msk | LCD_CONTROL_HS_EN_Msk)
#define CY_SEGLCD_NIBBLE                    (4UL)

#define CY_SEGLCD_DIV_MAX                   (0x0000FFFFUL) /* The max. divider values */
#define CY_SEGLCD_DIV_MAX_LS_VER1           (0x000000FFUL) /* The max. divider values for Low Speed mode for MXLCD_ver1 */

#define CY_SEGLCD_SYM_BIT_IDX_Pos           (0U)
#define CY_SEGLCD_SYM_BIT_IDX_Msk           ((uint32_t) 0x00000007UL << CY_SEGLCD_SYM_BIT_IDX_Pos)
#define CY_SEGLCD_SYM_BYTE_IDX_Pos          (3U)
#define CY_SEGLCD_SYM_BYTE_IDX_Msk          ((uint32_t) 0x00001FFFUL << CY_SEGLCD_SYM_BYTE_IDX_Pos)

#define CY_SEGLCD_PIX_Pos(pixel)            ((CY_SEGLCD_EXTR_NBL(pixel) * CY_SEGLCD_NIBBLE) + \
                                             (CY_SEGLCD_EXTR_COM(pixel) % CY_SEGLCD_NIBBLE))
#define CY_SEGLCD_PIX_Msk(pixel)            ((uint32_t)(1UL << CY_SEGLCD_PIX_Pos(pixel)))

#define CY_SEGLCD_REVISION(base)            (_FLD2VAL(LCD_ID_REVISION, LCD_ID(base)))
#define CY_SEGLCD_REV_1(base)               (1UL == CY_SEGLCD_REVISION(base))
#define CY_SEGLCD_IS_ENABLED(base)          (0UL != (LCD_CONTROL(base) & CY_SEGLCD_ENABLE_Msk))
#define CY_SEGLCD_IS_MSK_VALID(pixel)       (0UL == ((pixel) & ~(CY_SEGLCD_COM_Msk | CY_SEGLCD_OCT_Msk | CY_SEGLCD_NBL_Msk)))
#define CY_SEGLCD_IS_COM_VALID(pixel)       (LCD_COM_NUM > CY_SEGLCD_EXTR_COM(pixel))
#define CY_SEGLCD_IS_PIX_VALID(pixel)       (CY_SEGLCD_IS_MSK_VALID(pixel) && CY_SEGLCD_IS_COM_VALID(pixel))


#define CY_SEGLCD_COM_NUM_MIN               (2U)
#define CY_SEGLCD_COM_NUM_MAX               (LCD_COM_NUM)
#define CY_SEGLCD_IS_COM_NUM_VALID(num)     ((CY_SEGLCD_COM_NUM_MIN <= (num)) && ((num) <= CY_SEGLCD_COM_NUM_MAX))

#define CY_SEGLCD_IS_BASIC(type)            (((uint16_t)CY_SEGLCD_7SEG  == (type)) || \
                                             ((uint16_t)CY_SEGLCD_14SEG == (type)) || \
                                             ((uint16_t)CY_SEGLCD_16SEG == (type)) || \
                                             ((uint16_t)CY_SEGLCD_5X8DM == (type)))

#define CY_SEGLCD_IS_PIXMAP(disp)           ((NULL != (disp)) && \
                                             (NULL != (disp)->pixMap))

#define CY_SEGLCD_IS_SYMBOLIC(disp, pos)    (CY_SEGLCD_IS_PIXMAP(disp) && \
                                             (NULL != (disp)->font) && \
                                             (NULL != (disp)->font->fontMap) && \
                                             ((uint32_t)CY_SEGLCD_BAR < (disp)->type) && \
                                             (((pos) < (disp)->symNum)))

#define CY_SEGLCD_IS_ASCII(disp, pos)       (CY_SEGLCD_IS_SYMBOLIC(disp, pos) && \
                                             ((disp)->font->ascii))

#define CY_SEGLCD_IS_BARGRAPH(disp, pos)    (CY_SEGLCD_IS_PIXMAP(disp) && \
                                             ((uint32_t)CY_SEGLCD_BAR == (disp)->type) && \
                                             (((pos) < (disp)->symNum)))

#define CY_SEGLCD_IS_SPEED_VALID(speed)     ((CY_SEGLCD_SPEED_LOW  == (speed)) || \
                                             (CY_SEGLCD_SPEED_HIGH == (speed)))

#define CY_SEGLCD_IS_WAVE_VALID(wave)       ((CY_SEGLCD_TYPE_A == (wave)) || \
                                             (CY_SEGLCD_TYPE_B == (wave)))

#define CY_SEGLCD_IS_DRIVE_VALID(drive)     ((CY_SEGLCD_PWM         == (drive)) || \
                                             (CY_SEGLCD_CORRELATION == (drive)))

#define CY_SEGLCD_IS_BIAS_4_5_SUPPORTED(base,speed) ((CY_SEGLCD_REV_1(base)) ? (CY_SEGLCD_SPEED_HIGH == (speed)) : true)

#define CY_SEGLCD_IS_BIAS_VALID(base,bias,speed) ((CY_SEGLCD_BIAS_HALF   == (bias))  || \
                                                  (CY_SEGLCD_BIAS_THIRD  == (bias))  || \
  (CY_SEGLCD_IS_BIAS_4_5_SUPPORTED(base,speed) && (CY_SEGLCD_BIAS_FOURTH == (bias))) || \
  (CY_SEGLCD_IS_BIAS_4_5_SUPPORTED(base,speed) && (CY_SEGLCD_BIAS_FIFTH  == (bias))))

#define CY_SEGLCD_IS_LSCLK_VALID(lsClk)     ((CY_SEGLCD_LSCLK_LF == (lsClk)) || \
                                             (CY_SEGLCD_LSCLK_MF == (lsClk)))

#define CY_SEGLCD_FR_RATE_MIN               (30U)
#define CY_SEGLCD_FR_RATE_MAX               (150U)
#define CY_SEGLCD_IS_RATE_VALID(frRate)     (((frRate) >= CY_SEGLCD_FR_RATE_MIN) && ((frRate) <= CY_SEGLCD_FR_RATE_MAX))

#define CY_SEGLCD_CNTR_MAX                  (100UL)
#define CY_SEGLCD_IS_CNTR_VALID(contrast)   (((uint32_t)(contrast)) <= CY_SEGLCD_CNTR_MAX)

#define CY_SEGLCD_FREQ_MIN                  (10000UL)
#define CY_SEGLCD_FREQ_MAX                  (100000000UL)
#define CY_SEGLCD_IS_FREQ_VALID(freq)       (((freq) >= CY_SEGLCD_FREQ_MIN) && ((freq) <= CY_SEGLCD_FREQ_MAX))

#define CY_SEGLCD_SPACE(disp)               (((disp)->font->ascii) ? ' ' : CY_SEGLCD_NUM_BLANK)

/* The timeout value for Low Speed mode enable/disable procedures, two ILO clock periods, in uSeconds */
#define CY_SEGLCD_TIMEOUT ((2U * 1000000UL) / CY_SYSCLK_ILO_FREQ)


static volatile uint32_t * GetDataRegPtr(LCD_Type * base, uint32_t pixel);
static void InvClrData(LCD_Type * base, bool inv);
static char_t NumToChar(uint32_t value);


static const uint8_t fontMap7[] = /* Apparently the 7-segment font character code fits into a single byte so the 'font map symbol size' is not used here */
/*'0'   '1'   '2'   '3'   '4'   '5'   '6'   '7'   '8'   '9'   'A'   'B'   'C'   'D'   'E'   'F' 'blank'*/
{0x3FU,0x06U,0x5BU,0x4FU,0x66U,0x6DU,0x7DU,0x07U,0x7FU,0x6FU,0x77U,0x7CU,0x39U,0x5EU,0x79U,0x71U,0x00U};

const cy_stc_seglcd_font_t cy_segLCD_7SegFont =
{
    .first   = '\0',
    .last    = CY_SEGLCD_NUM_BLANK,
    .ascii   = false,
    .fontMap = fontMap7
};


static const uint8_t fontMap14[][CY_SEGLCD_14SEG_FONTMAP_SIZE] =
{
    /*  space           !             "             #             $             %             &             '     */
    {0x00U,0x00U},{0x06U,0x00U},{0x20U,0x01U},{0xFFU,0x3FU},{0x6DU,0x15U},{0xE4U,0x2EU},{0x8DU,0x2AU},{0x00U,0x02U},
    /*    (             )             *             +             ,             -             .             /     */
    {0x00U,0x0AU},{0x80U,0x20U},{0xC0U,0x3FU},{0x40U,0x15U},{0x00U,0x20U},{0x40U,0x04U},{0x58U,0x10U},{0x00U,0x22U},
    /*    0             1             2             3             4             5             6             7     */
    {0x3FU,0x22U},{0x06U,0x02U},{0x5BU,0x04U},{0x0FU,0x04U},{0x66U,0x04U},{0x69U,0x08U},{0x7DU,0x04U},{0x01U,0x12U},
    /*    8             9             :             ;             <             =             >             ?     */
    {0x7FU,0x04U},{0x6FU,0x04U},{0x00U,0x11U},{0x00U,0x21U},{0x00U,0x0AU},{0x48U,0x04U},{0x80U,0x20U},{0x23U,0x14U},
    /*    @             A             B             C             D             E             F             G     */
    {0x3BU,0x05U},{0x77U,0x04U},{0x0FU,0x15U},{0x39U,0x00U},{0x0FU,0x11U},{0x79U,0x00U},{0x71U,0x00U},{0x3DU,0x04U},
    /*    H             I             J             K             L             M             N             O     */
    {0x76U,0x04U},{0x00U,0x11U},{0x1EU,0x00U},{0x70U,0x0AU},{0x38U,0x00U},{0xB6U,0x02U},{0xB6U,0x08U},{0x3FU,0x00U},
    /*    P             Q             R             S             T             U             V             W     */
    {0x73U,0x04U},{0x3FU,0x08U},{0x73U,0x0CU},{0x6DU,0x04U},{0x01U,0x11U},{0x3EU,0x00U},{0x30U,0x22U},{0x36U,0x28U},
    /*    X             Y             Z             [             \             ]             ^             _     */
    {0x80U,0x2AU},{0x80U,0x12U},{0x09U,0x22U},{0x39U,0x00U},{0x80U,0x08U},{0x0FU,0x00U},{0x03U,0x00U},{0x08U,0x00U},
    /*    `             a             b             c             d             e             f             g     */
    {0x00U,0x02U},{0x77U,0x04U},{0x0FU,0x15U},{0x39U,0x00U},{0x0FU,0x11U},{0x79U,0x00U},{0x71U,0x00U},{0x3DU,0x04U},
    /*    h             i             j             k             l             m             n             o     */
    {0x76U,0x04U},{0x00U,0x11U},{0x1EU,0x00U},{0x70U,0x0AU},{0x38U,0x00U},{0xB6U,0x02U},{0xB6U,0x08U},{0x3FU,0x00U},
    /*    p             q             r             s             t             u             v             w     */
    {0x73U,0x04U},{0x3FU,0x08U},{0x73U,0x0CU},{0x6DU,0x04U},{0x01U,0x11U},{0x3EU,0x00U},{0x30U,0x22U},{0x36U,0x28U},
    /*    x             y             z             {             |             }             ~    */
    {0x80U,0x2AU},{0x80U,0x12U},{0x09U,0x22U},{0x00U,0x0EU},{0x00U,0x11U},{0xC0U,0x20U},{0x52U,0x04U}
};

const cy_stc_seglcd_font_t cy_segLCD_14SegFont =
{
    .first   = ' ',
    .last    = '~',
    .ascii   = true,
    .fontMap = (uint8_t*)fontMap14
};


static const uint8_t fontMap16[][CY_SEGLCD_16SEG_FONTMAP_SIZE] =
{
    /*  space           !             "             #             $             %             &             '     */
    {0x00U,0x00U},{0x0CU,0x00U},{0x80U,0x04U},{0xFFU,0xFFU},{0xBBU,0x55U},{0x99U,0xDDU},{0x3BU,0xAAU},{0x00U,0x08U},
    /*    (             )             *             +             ,             -             .             /     */
    {0x00U,0x28U},{0x00U,0x82U},{0x00U,0xFFU},{0x00U,0x55U},{0x00U,0x80U},{0x00U,0x11U},{0x60U,0x41U},{0x00U,0x88U},
    /*    0             1             2             3             4             5             6             7     */
    {0xFFU,0x88U},{0x0CU,0x00U},{0x77U,0x11U},{0x3FU,0x10U},{0x8CU,0x11U},{0xB3U,0x21U},{0xFBU,0x11U},{0x03U,0x48U},
    /*    8             9             :             ;             <             =             >             ?     */
    {0xFFU,0x11U},{0xBFU,0x11U},{0x00U,0x44U},{0x00U,0x84U},{0x00U,0x28U},{0x30U,0x11U},{0x00U,0x82U},{0x87U,0x50U},
    /*    @             A             B             C             D             E             F             G     */
    {0xF7U,0x14U},{0xCFU,0x11U},{0x3FU,0x54U},{0xF3U,0x00U},{0x3FU,0x44U},{0xF3U,0x01U},{0xC3U,0x01U},{0xFBU,0x10U},
    /*    H             I             J             K             L             M             N             O     */
    {0xCCU,0x11U},{0x00U,0x44U},{0x7EU,0x00U},{0xC0U,0x29U},{0xF0U,0x00U},{0xCCU,0x0AU},{0xCCU,0x22U},{0xFFU,0x00U},
    /*    P             Q             R             S             T             U             V             W     */
    {0xC7U,0x11U},{0xFFU,0x20U},{0xC7U,0x31U},{0xBBU,0x11U},{0x03U,0x44U},{0xFCU,0x00U},{0xC0U,0x88U},{0xCCU,0xA0U},
    /*    X             Y             Z             [             \             ]             ^             _     */
    {0x00U,0xAAU},{0x00U,0x4AU},{0x33U,0x88U},{0x12U,0x44U},{0x00U,0x22U},{0x21U,0x44U},{0x06U,0x00U},{0x30U,0x00U},
    /*    `             a             b             c             d             e             f             g     */
    {0x00U,0x08U},{0xCFU,0x11U},{0x3FU,0x54U},{0xF3U,0x00U},{0x3FU,0x44U},{0xF3U,0x01U},{0xC3U,0x01U},{0xFBU,0x10U},
    /*    h             i             j             k             l             m             n             o     */
    {0xCCU,0x11U},{0x00U,0x44U},{0x7EU,0x00U},{0xC0U,0x29U},{0xF0U,0x00U},{0xCCU,0x0AU},{0xCCU,0x22U},{0xFFU,0x00U},
    /*    p             q             r             s             t             u             v             w     */
    {0xC7U,0x11U},{0xFFU,0x20U},{0xC7U,0x31U},{0xBBU,0x11U},{0x03U,0x44U},{0xFCU,0x00U},{0xC0U,0x88U},{0xCCU,0xA0U},
    /*    x             y             z             {             |             }             ~    */
    {0x00U,0xAAU},{0x00U,0x4AU},{0x33U,0x88U},{0x00U,0x38U},{0x00U,0x44U},{0x00U,0x83U},{0x44U,0x11U}
};

const cy_stc_seglcd_font_t cy_segLCD_16SegFont =
{
    .first   = ' ',
    .last    = '~',
    .ascii   = true,
    .fontMap = (uint8_t*)fontMap16
};


static const uint8_t fontMap5x8[][CY_SEGLCD_5X8DM_FONTMAP_SIZE] =
{
    /*           space                             !                               "                               #              */
    {0x00U,0x00U,0x00U,0x00U,0x00U},{0x00U,0x00U,0x4FU,0x00U,0x00U},{0x00U,0x07U,0x00U,0x07U,0x00U},{0x14U,0x7FU,0x14U,0x7FU,0x14U},
    /*             $                               %                               &                               '               */
    {0x24U,0x2AU,0x7FU,0x2AU,0x12U},{0x23U,0x13U,0x08U,0x64U,0x62U},{0x36U,0x49U,0x55U,0x22U,0x50U},{0x00U,0x05U,0x03U,0x00U,0x00U},
    /*             (                               )                               *                               +             */
    {0x00U,0x1CU,0x22U,0x41U,0x00U},{0x00U,0x41U,0x22U,0x1CU,0x00U},{0x14U,0x08U,0x3EU,0x08U,0x14U},{0x08U,0x08U,0x3EU,0x08U,0x08U},
    /*             ,                               -                               .                               /             */
    {0x00U,0x50U,0x30U,0x00U,0x00U},{0x08U,0x08U,0x08U,0x08U,0x08U},{0x00U,0x60U,0x60U,0x00U,0x00U},{0x20U,0x10U,0x08U,0x04U,0x02U},
    /*             0                               1                               2                               3             */
    {0x3EU,0x51U,0x49U,0x45U,0x3EU},{0x00U,0x42U,0x7FU,0x40U,0x00U},{0x42U,0x61U,0x51U,0x49U,0x46U},{0x21U,0x41U,0x45U,0x4BU,0x31U},
    /*             4                               5                               6                               7             */
    {0x18U,0x14U,0x12U,0x7FU,0x10U},{0x27U,0x45U,0x45U,0x45U,0x39U},{0x3CU,0x4AU,0x49U,0x49U,0x30U},{0x01U,0x71U,0x09U,0x05U,0x03U},
    /*             8                               9                               :                               ;             */
    {0x36U,0x49U,0x49U,0x49U,0x36U},{0x06U,0x49U,0x49U,0x29U,0x1EU},{0x00U,0x36U,0x36U,0x00U,0x00U},{0x00U,0x56U,0x36U,0x00U,0x00U},
    /*             <                               =                               >                               ?             */
    {0x08U,0x14U,0x22U,0x41U,0x00U},{0x14U,0x14U,0x14U,0x14U,0x14U},{0x00U,0x41U,0x22U,0x14U,0x08U},{0x02U,0x01U,0x51U,0x09U,0x06U},
    /*             @                               A                               B                               C             */
    {0x32U,0x49U,0x79U,0x41U,0x3EU},{0x7EU,0x11U,0x11U,0x11U,0x7EU},{0x7FU,0x49U,0x49U,0x49U,0x36U},{0x3EU,0x41U,0x41U,0x41U,0x22U},
    /*             D                               E                               F                               G             */
    {0x7FU,0x41U,0x41U,0x22U,0x1CU},{0x7FU,0x49U,0x49U,0x49U,0x41U},{0x7FU,0x09U,0x09U,0x09U,0x01U},{0x3EU,0x41U,0x49U,0x49U,0x3AU},
    /*             H                               I                               J                               K             */
    {0x7FU,0x08U,0x08U,0x08U,0x7FU},{0x00U,0x41U,0x7FU,0x41U,0x00U},{0x20U,0x40U,0x41U,0x3FU,0x01U},{0x7FU,0x08U,0x14U,0x22U,0x41U},
    /*             L                               M                               N                               O             */
    {0x7FU,0x40U,0x40U,0x40U,0x40U},{0x7FU,0x02U,0x0CU,0x02U,0x7FU},{0x7FU,0x04U,0x08U,0x10U,0x7FU},{0x3EU,0x41U,0x41U,0x41U,0x3EU},
    /*             P                               Q                               R                               S             */
    {0x7FU,0x09U,0x09U,0x09U,0x06U},{0x3EU,0x41U,0x51U,0x21U,0x5EU},{0x7FU,0x09U,0x19U,0x29U,0x46U},{0x46U,0x49U,0x49U,0x49U,0x31U},
    /*             T                               U                               V                               W             */
    {0x01U,0x01U,0x7FU,0x01U,0x01U},{0x3FU,0x40U,0x40U,0x40U,0x3FU},{0x1FU,0x20U,0x40U,0x20U,0x1FU},{0x3FU,0x40U,0x38U,0x40U,0x3FU},
    /*             X                               Y                               Z                               [             */
    {0x63U,0x14U,0x08U,0x14U,0x63U},{0x07U,0x08U,0x70U,0x08U,0x07U},{0x61U,0x51U,0x49U,0x45U,0x43U},{0x00U,0x7FU,0x41U,0x41U,0x00U},
    /*             \                               ]                               ^                               _             */
    {0x15U,0x16U,0x7CU,0x16U,0x15U},{0x00U,0x41U,0x41U,0x7FU,0x00U},{0x04U,0x02U,0x01U,0x02U,0x04U},{0x40U,0x40U,0x40U,0x40U,0x40U},
    /*             `                               a                               b                               c             */
    {0x00U,0x01U,0x02U,0x04U,0x00U},{0x20U,0x54U,0x54U,0x54U,0x78U},{0x7FU,0x48U,0x44U,0x44U,0x38U},{0x38U,0x44U,0x44U,0x44U,0x40U},
    /*             d                               e                               f                               g             */
    {0x38U,0x44U,0x44U,0x48U,0x7FU},{0x38U,0x54U,0x54U,0x54U,0x18U},{0x08U,0x7EU,0x09U,0x01U,0x02U},{0x0CU,0x52U,0x52U,0x52U,0x3EU},
    /*             h                               i                               j                               k             */
    {0x7FU,0x08U,0x04U,0x04U,0x78U},{0x00U,0x44U,0x7DU,0x40U,0x00U},{0x20U,0x40U,0x40U,0x3DU,0x00U},{0x7FU,0x10U,0x28U,0x44U,0x00U},
    /*             l                               m                               n                               o             */
    {0x00U,0x41U,0x7FU,0x40U,0x00U},{0x7CU,0x04U,0x18U,0x04U,0x78U},{0x7CU,0x08U,0x04U,0x04U,0x78U},{0x38U,0x44U,0x44U,0x44U,0x38U},
    /*             p                               q                               r                               s             */
    {0x7CU,0x14U,0x14U,0x14U,0x08U},{0x08U,0x14U,0x14U,0x18U,0x7CU},{0x7CU,0x08U,0x04U,0x04U,0x08U},{0x48U,0x54U,0x54U,0x54U,0x20U},
    /*             t                               u                               v                               w             */
    {0x04U,0x3FU,0x44U,0x40U,0x20U},{0x3CU,0x40U,0x40U,0x20U,0x7CU},{0x1CU,0x20U,0x40U,0x20U,0x1CU},{0x3CU,0x40U,0x30U,0x40U,0x3CU},
    /*             x                               y                               z                               {             */
    {0x44U,0x28U,0x10U,0x28U,0x44U},{0x0CU,0x50U,0x50U,0x50U,0x3CU},{0x44U,0x64U,0x54U,0x4CU,0x44U},{0x00U,0x08U,0x36U,0x41U,0x00U},
    /*             |                               }                               ~             */
    {0x00U,0x00U,0x7FU,0x00U,0x00U},{0x00U,0x41U,0x36U,0x08U,0x00U},{0x08U,0x04U,0x08U,0x10U,0x08U}
};

const cy_stc_seglcd_font_t cy_segLCD_5x8DmFont =
{
    .first   = ' ',
    .last    = '~',
    .ascii   = true,
    .fontMap = (uint8_t*)fontMap5x8
};


/*******************************************************************************
* Function Name: GetDataRegPtr
****************************************************************************//**
*
* Returns a pointer to the data frame register for a specified pixel.
* Used by \ref Cy_SegLCD_WritePixel and \ref Cy_SegLCD_ReadPixel functions.
*
* \param base  The base pointer to the LCD instance registers.
* \param pixel The predefined packed number that points to the pixel location
*              in the frame buffer.
*
*******************************************************************************/
static volatile uint32_t * GetDataRegPtr(LCD_Type * base, uint32_t pixel)
{
    volatile uint32_t * locDataPtr[] = {LCD_DATA0(base), LCD_DATA1(base), LCD_DATA2(base), LCD_DATA3(base)};

    return (&(locDataPtr[CY_SEGLCD_EXTR_COM(pixel) / CY_SEGLCD_NIBBLE][CY_SEGLCD_EXTR_OCT(pixel)]));
}


/*******************************************************************************
* Function Name: InvClrData
****************************************************************************//**
*
* Inverts or clears the Frame Data buffer.
* Used by \ref Cy_SegLCD_Deinit,
*         \ref Cy_SegLCD_ClrFrame and
*         \ref Cy_SegLCD_InvFrame functions.
*
* \param base  The base pointer to the LCD instance registers.
* \param inv:
*    - true - inverts the data buffer,
*    - false - clears the data buffer.
*
*******************************************************************************/
static void InvClrData(LCD_Type * base, bool inv)
{
    uint32_t i;

    for (i = 0UL; i < LCD_NUMPORTS; i++)
    {
        LCD_DATA0(base)[i] = (inv) ? (~LCD_DATA0(base)[i]) : 0UL;

        #if (0UL != LCD_NUMPORTS8)
            LCD_DATA1(base)[i] = (inv) ? (~LCD_DATA1(base)[i]) : 0UL;

            #if (0UL != LCD_NUMPORTS16)
                LCD_DATA2(base)[i] = (inv) ? (~LCD_DATA2(base)[i]) : 0UL;
                LCD_DATA3(base)[i] = (inv) ? (~LCD_DATA3(base)[i]) : 0UL;
            #endif /* LCD_NUMPORTS16 */
        #endif /* LCD_NUMPORTS8 */
    }
}


/*******************************************************************************
* Function Name: NumToChar
****************************************************************************//**
*
* Converts an one-digit hexadecimal numbers 0x0...0xF
* into the ASCII character codes.
* Used by the \ref Cy_SegLCD_WriteNumber function.
*
* \param value The value to be converted.
* \return The ASCII code of the 'value' character.
*
*******************************************************************************/
static char_t NumToChar(uint32_t value)
{
    uint32_t character;

    if (value < 10UL) /* For dec numbers 0...9 */
    {
        character = (uint32_t)'0' + value;
    }
    else if (value < 0x10UL) /* For hex numbers A...F */
    {
        character = ((uint32_t)'A' - 0xAUL) + value;
    }
    else
    {
        character = (uint32_t)' '; /* The blank/space character */
    }

    return ((char_t)character);
}


/*******************************************************************************
* Function Name: Cy_SegLCD_Init
****************************************************************************//**
*
* Initializes/restores the default Segment LCD block configuration.
*
* \param base   The base pointer to the LCD instance registers.
* \param config The pointer to a configuration structure.
* \return \ref cy_en_seglcd_status_t.
*
* Side Effects: The block is disabled to change the settings.
*
* \funcusage
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_Config
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_Init
*
*******************************************************************************/
cy_en_seglcd_status_t Cy_SegLCD_Init(LCD_Type * base, cy_stc_seglcd_config_t const * config)
{
    cy_en_seglcd_status_t retVal = CY_SEGLCD_BAD_PARAM;

    if (NULL != base)
    {
        CY_ASSERT_L3(CY_SEGLCD_IS_SPEED_VALID(config->speed));
        CY_ASSERT_L3(CY_SEGLCD_IS_WAVE_VALID (config->wave));
        CY_ASSERT_L3(CY_SEGLCD_IS_DRIVE_VALID(config->drive));
        CY_ASSERT_L3(CY_SEGLCD_IS_BIAS_VALID (base, config->bias, config->speed));
        CY_ASSERT_L2(CY_SEGLCD_IS_LSCLK_VALID (config->lsClk));
        CY_ASSERT_L1(CY_SEGLCD_IS_COM_NUM_VALID(config->comNum));
        CY_ASSERT_L2(CY_SEGLCD_IS_RATE_VALID (config->frRate));
        CY_ASSERT_L2(CY_SEGLCD_IS_CNTR_VALID (config->contrast));
        CY_ASSERT_L2(CY_SEGLCD_IS_FREQ_VALID (config->clkFreq));

        uint32_t locCheck = ((CY_SEGLCD_SPEED_LOW == config->speed) && (CY_SEGLCD_REV_1(base))) ? (CY_SEGLCD_DIV_MAX_LS_VER1) : (CY_SEGLCD_DIV_MAX);
        uint32_t locSubfr = CY_SYSLIB_DIV_ROUND((CY_SYSLIB_DIV_ROUND(config->clkFreq, config->frRate * 4UL * config->comNum) - 1UL) * config->contrast, 100UL);
        uint32_t locDead = CY_SYSLIB_DIV_ROUND(CY_SYSLIB_DIV_ROUND(config->clkFreq * ((uint32_t)(100UL - (uint32_t)config->contrast)), (uint32_t)config->frRate), 100UL);

        if ((locSubfr <= locCheck) && (locDead <= locCheck))
        {
            uint32_t locLsClk = (uint32_t)((CY_SEGLCD_REV_1(base)) ? CY_SEGLCD_LSCLK_LF : config->lsClk);

            Cy_SegLCD_Disable(base);

            /* Calculate the sub-frame and dead-time dividers */
            LCD_DIVIDER(base) = _VAL2FLD(LCD_DIVIDER_SUBFR_DIV, locSubfr) |
                                _VAL2FLD(LCD_DIVIDER_DEAD_DIV,  locDead);

            /* Set the rest of settings */
            LCD_CONTROL(base) = _VAL2FLD(LCD_CONTROL_LCD_MODE, config->speed) |
                                _VAL2FLD(LCD_CONTROL_TYPE,     config->wave)  |
                                _VAL2FLD(LCD_CONTROL_OP_MODE,  config->drive) |
                                _VAL2FLD(LCD_CONTROL_BIAS,     config->bias)  |
                        _VAL2FLD(LCD_V2_CONTROL_CLOCK_LS_SEL,  locLsClk)      |
            /* Convert the comNum from the user range (2-16) into the machine range (0-14). */
                                _VAL2FLD(LCD_CONTROL_COM_NUM,  config->comNum - 2UL);

            retVal = CY_SEGLCD_SUCCESS;
        }
    }

    return (retVal);
}


/*******************************************************************************
* Function Name: Cy_SegLCD_Contrast
****************************************************************************//**
*
* Sets a specified contrast.
*
* \param base   The base pointer to the LCD instance registers.
* \param contrast The contrast value to be set.
* \param config The pointer to a configuration structure.
* \return \ref cy_en_seglcd_status_t.
*
* Side Effects: The configuration structure contrast value is also updated.
*
* \funcusage
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_ContrastInit
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_Contrast
*
*******************************************************************************/
cy_en_seglcd_status_t Cy_SegLCD_Contrast(LCD_Type * base, uint32_t contrast, cy_stc_seglcd_config_t * config)
{
    cy_en_seglcd_status_t retVal = CY_SEGLCD_BAD_PARAM;

    if (CY_SEGLCD_IS_CNTR_VALID (contrast))
    {
        bool enabled = CY_SEGLCD_IS_ENABLED(base); /* Store the block state */

        config->contrast = (uint8_t)contrast;

        retVal = Cy_SegLCD_Init(base, config);

        if ((CY_SEGLCD_SUCCESS == retVal) && enabled)
        {
            Cy_SegLCD_Enable(base); /* Restore the block state */
        }
    }

    return (retVal);
}


/*******************************************************************************
* Function Name: Cy_SegLCD_Deinit
****************************************************************************//**
*
* De-initializes the LCD block (resets the block registers to default state).
*
* \param base   The base pointer to the LCD instance registers.
*
* \funcusage
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_Deinit
*
*******************************************************************************/
void Cy_SegLCD_Deinit(LCD_Type * base)
{
    Cy_SegLCD_Disable(base);

    LCD_CONTROL(base) = 0UL;
    LCD_DIVIDER(base) = 0UL;

    InvClrData(base, false); /* Clear the entire frame buffer to all zeroes */
}


/*******************************************************************************
* Function Name: Cy_SegLCD_Enable
****************************************************************************//**
*
* Enables the Segment LCD block.
*
* \param base The base pointer to the LCD instance registers.
*
* \funcusage
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_Config
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_Init
*
*******************************************************************************/
void Cy_SegLCD_Enable(LCD_Type * base)
{
    if (_FLD2BOOL(LCD_CONTROL_LCD_MODE, LCD_CONTROL(base)))
    {
        LCD_CONTROL(base) |= LCD_CONTROL_HS_EN_Msk;
    }
    else /* CY_SEGLCD_SPEED_HIGH */
    {
        uint32_t timeout;

        LCD_CONTROL(base) |= LCD_CONTROL_LS_EN_Msk;

        for (timeout = CY_SEGLCD_TIMEOUT; (_FLD2BOOL(LCD_CONTROL_LS_EN_STAT, LCD_CONTROL(base))) && (0UL != timeout); timeout--)
        {
            /* Waiting for enabling takes effect in the ILO clock domain.
             * The timeout status does not affect anything,
             * the timeout is to avoid a deadlock here.
             */
            Cy_SysLib_DelayUs(1U);
        }
    }
}


/*******************************************************************************
* Function Name: Cy_SegLCD_Disable
****************************************************************************//**
*
* Disables the Segment LCD block.
*
* \param base The base pointer to the LCD instance registers.
*
* \funcusage
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_Disable
*
*******************************************************************************/
void Cy_SegLCD_Disable(LCD_Type * base)
{
    if (_FLD2BOOL(LCD_CONTROL_LCD_MODE, LCD_CONTROL(base))) /* CY_SEGLCD_SPEED_HIGH */
    {
        LCD_CONTROL(base) &= ~LCD_CONTROL_HS_EN_Msk;
    }
    else /* CY_SEGLCD_SPEED_LOW */
    {
        if (_FLD2BOOL(LCD_CONTROL_LS_EN, LCD_CONTROL(base)))
        {
            uint32_t timeout;

            for (timeout = CY_SEGLCD_TIMEOUT; (!_FLD2BOOL(LCD_CONTROL_LS_EN_STAT, LCD_CONTROL(base))) && (0UL != timeout); timeout--)
            {
                 Cy_SysLib_DelayUs(1U); /* Waiting for enabling takes effect in the ILO clock domain. */
            }

            LCD_CONTROL(base) &= ~LCD_CONTROL_LS_EN_Msk;

            for (timeout = CY_SEGLCD_TIMEOUT; (_FLD2BOOL(LCD_CONTROL_LS_EN_STAT, LCD_CONTROL(base))) && (0UL != timeout); timeout--)
            {
                Cy_SysLib_DelayUs(1U); /* Waiting for disabling takes effect in the ILO clock domain. */
            }

            /* The timeout status does not affect anything, the timeout is to avoid a deadlock */
        }
    }
}


/*******************************************************************************
* Function Name: Cy_SegLCD_ClrFrame
****************************************************************************//**
*
* Clears the frame buffer and initiates the common lines.
* In general case it is recommended to be called after \ref Cy_SegLCD_Init
*                                           and before \ref Cy_SegLCD_Enable.
*
* \param base    The base pointer to the LCD instance registers.
* \param commons The pointer to array of common lines.
*                The array size is specified by \ref cy_stc_seglcd_config_t.comNum.
*                Each common line value should be made using
*                \ref CY_SEGLCD_COMMON macro.
*
* \return \ref cy_en_seglcd_status_t.
*
* \funcusage
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_Config
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_Init
*
*******************************************************************************/
cy_en_seglcd_status_t Cy_SegLCD_ClrFrame(LCD_Type * base, uint32_t const * commons)
{
    uint32_t retVal = (uint32_t)CY_SEGLCD_BAD_PARAM;

    if (NULL != commons)
    {
        uint32_t i;

        InvClrData(base, false); /* Clear the entire frame buffer to all zeroes */

        retVal = (uint32_t)CY_SEGLCD_SUCCESS;

        /* Re-initialize the commons */
        for (i = 0UL; i < CY_SEGLCD_COM_NUM(base); i++)
        {
            retVal |= (uint32_t)Cy_SegLCD_WritePixel(base, commons[i], true);
        }
    }

    return((cy_en_seglcd_status_t)retVal);
}


/*******************************************************************************
* Function Name: Cy_SegLCD_InvFrame
****************************************************************************//**
*
* Inverts the frame buffer (all the connected pixel states are inverted).
*
* \param base    The base pointer to the LCD instance registers.
* \param commons The pointer to an array of common lines.
*                The array size is specified by \ref cy_stc_seglcd_config_t.comNum.
*                Each common line value should be made using
*                \ref CY_SEGLCD_COMMON macro.
*
* \return \ref cy_en_seglcd_status_t.
*
* \funcusage
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_InvFrame
*
*******************************************************************************/
cy_en_seglcd_status_t Cy_SegLCD_InvFrame(LCD_Type * base, uint32_t const * commons)
{
    uint32_t retVal = (uint32_t)CY_SEGLCD_BAD_PARAM;

    if (NULL != commons)
    {
        uint32_t i;

        InvClrData(base, true); /* Invert the entire frame buffer. */

        retVal = (uint32_t)CY_SEGLCD_SUCCESS;

        /* Re-initialize the common lines */
        for (i = 0UL; i < CY_SEGLCD_COM_NUM(base); i++)
        {
            uint32_t locCom = commons[i] & ~CY_SEGLCD_COM_Msk;
            uint32_t j = 0UL;

            /* Clear common lines data after frame buffer inverting */
            for (j = 0UL; j < CY_SEGLCD_COM_NUM(base); j++)
            {
                retVal |= (uint32_t)Cy_SegLCD_WritePixel(base, locCom | ((uint32_t)(j << CY_SEGLCD_COM_Pos)), false);
            }

            /* Set data for the common lines */
            retVal |= (uint32_t)Cy_SegLCD_WritePixel(base, commons[i], true);
        }
    }

    return((cy_en_seglcd_status_t)retVal);
}


/*******************************************************************************
* Function Name: Cy_SegLCD_WritePixel
****************************************************************************//**
*
*  Sets or clears a specified pixel.
*
* \param base The base pointer to the LCD instance registers.
* \param pixel The predefined packed number that points to the pixel location
*              in the frame buffer.
* \param value Specifies the pixel on/off state.
* \return \ref cy_en_seglcd_status_t.
*
* \funcusage
* \snippet seglcd/snippet/SegLCD_Snpt.h snippet_Cy_SegLCD_DefPixel
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_ActPixel
*
*******************************************************************************/
cy_en_seglcd_status_t Cy_SegLCD_WritePixel(LCD_Type * base, uint32_t pixel, bool value)
{
    cy_en_seglcd_status_t retVal = CY_SEGLCD_BAD_PIXEL;

    if (CY_SEGLCD_IS_PIX_VALID(pixel))
    {
        /* Extract the pixel location. */
        uint32_t loc_Pos = CY_SEGLCD_PIX_Pos(pixel);
        uint32_t loc_Msk = CY_SEGLCD_PIX_Msk(pixel);

        /* Write a new pixel value into the frame buffer. */
        CY_REG32_CLR_SET(*GetDataRegPtr(base, pixel), loc, value ? 1UL : 0UL);

        retVal = CY_SEGLCD_SUCCESS;
    }

    return(retVal);
}


/*******************************************************************************
* Function Name: Cy_SegLCD_ReadPixel
****************************************************************************//**
*
* Gets the state of a specified pixel.
*
* \param base The base pointer to the LCD instance registers.
* \param pixel The predefined packed number that points to the pixel location
*              in the frame buffer. Each pixel value should be made using
*              \ref CY_SEGLCD_PIXEL macro.
* \return Boolean pixel state.
*         If pixel value is invalid - the 'false' is returned.
*
* \funcusage
* \snippet seglcd/snippet/SegLCD_Snpt.h snippet_Cy_SegLCD_DefPixel
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_ActPixel
*
*******************************************************************************/
bool Cy_SegLCD_ReadPixel(LCD_Type * base, uint32_t pixel)
{
    bool retVal = false;

    if (CY_SEGLCD_IS_PIX_VALID(pixel))
    {
        /* Get the pixel value from the frame buffer */
        retVal = (0UL != (*GetDataRegPtr(base, pixel) & CY_SEGLCD_PIX_Msk(pixel)));
    }
    else
    {
        CY_ASSERT_L1(false);
    }

    return (retVal);
}


/*******************************************************************************
* Function Name: Cy_SegLCD_WriteChar
****************************************************************************//**
*
* Writes a specified character onto a specified display.
* Supports all display types except \ref CY_SEGLCD_BAR.
*
* \param base The base pointer to the LCD instance registers.
* \param character The code of the character to display.
*                  Should be within the font symbol codes range specified by
*           \ref cy_stc_seglcd_font_t.first and \ref cy_stc_seglcd_font_t.last
* \param position The position of the character/digit on display.
*                 Zero is the most left character/digit of the specified
*                 display \ref cy_stc_seglcd_disp_t.
* \param display The pointer to the display structure \ref cy_stc_seglcd_disp_t.
* \return \ref cy_en_seglcd_status_t.
*
* \funcusage
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_Char
*
*******************************************************************************/
cy_en_seglcd_status_t Cy_SegLCD_WriteChar(LCD_Type * base,
                                            char_t   character,
                                          uint32_t   position,
                        cy_stc_seglcd_disp_t const * display)
{
    uint32_t retVal = (uint32_t)CY_SEGLCD_BAD_PARAM;

    if (CY_SEGLCD_IS_SYMBOLIC(display, position)) /* If the display is symbolic/numeric */
    {
        uint32_t i;
        uint32_t locChar = (uint32_t)character;
        retVal = CY_SEGLCD_IS_BASIC(display->type) ? (uint32_t)CY_SEGLCD_SUCCESS : (uint32_t)CY_SEGLCD_CUSTOM;

        if ((character < display->font->first) || (character > display->font->last)) /* if out of the font range */
        {
            retVal |= (uint32_t)CY_SEGLCD_BAD_CHAR;
            locChar = (uint32_t)CY_SEGLCD_SPACE(display); /* The blank (space) character */
        }

        locChar = (uint32_t)(locChar - (uint32_t)display->font->first); /* Shift to the font char map starting index */

        for (i = 0UL; i < (uint32_t)display->type; i++)
        {
            uint32_t locPix = *(display->pixMap + (position * (uint32_t)display->type) + i); /* Current display pixel */
            uint32_t locIdx = _FLD2VAL(CY_SEGLCD_SYM_BYTE_IDX, i) + (locChar * CY_SYSLIB_DIV_ROUNDUP((uint32_t)display->type, CY_SEGLCD_OCTET)); /* current symbol byte index */
            bool     locVal = 0U != (display->font->fontMap[locIdx] & (uint8_t)(1U << _FLD2VAL(CY_SEGLCD_SYM_BIT_IDX, i))); /* current pixel value */

            retVal |= (uint32_t)Cy_SegLCD_WritePixel(base, locPix, display->invert != locVal);
        }
    }

    return((cy_en_seglcd_status_t)retVal);
}


/*******************************************************************************
* Function Name: Cy_SegLCD_WriteNumber
****************************************************************************//**
*
* Displays an integer value onto a specified display.
* Supports all display types except \ref CY_SEGLCD_BAR.
*
* \note The sign conversion, sign display, decimal points, and other special segments
*       outside the display symbols themselves should be handled on upper layer code.
*
* \param base The base pointer to the LCD instance registers.
* \param value The unsigned integer number to be displayed.
* \param position The position of the least significant digit of the number
*        as counted left to right starting at 0 - the first symbol on the left
*        of the specified display.
*        If the specified display contains fewer symbols than the number
*        requires to be displayed, the extra (more significant) digit(s) is(are) not
*        displayed and the \ref CY_SEGLCD_EXCEED value is returned.
* \param display The pointer to the display structure \ref cy_stc_seglcd_disp_t.
* \param zeroes:
*    - true - all the unused digits on the left of the displayed value are zeroes.
*    - false - all the above mentioned digits are blank.
* \param hex:
*    - true - the value is displayed in the hexadecimal format.
*    - false - the value is displayed in the decimal format.
* \return \ref cy_en_seglcd_status_t.
*
* \funcusage
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_DecNum
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_HexNum
*
*******************************************************************************/
cy_en_seglcd_status_t Cy_SegLCD_WriteNumber(LCD_Type * base,
                                            uint32_t   value,
                                            uint32_t   position,
                          cy_stc_seglcd_disp_t const * display,
                                                bool   zeroes,
                                                bool   hex)
{
    uint32_t retVal = (uint32_t)CY_SEGLCD_BAD_PARAM;

    if (CY_SEGLCD_IS_SYMBOLIC(display, position)) /* If the display is symbolic/numeric */
    {
        uint32_t locNum;
        uint32_t i = position + 1UL;
        uint32_t locDiv = (hex) ? 0x10UL : 10UL; /* The digit weight for hex/dec counting systems */
        retVal = (uint32_t)CY_SEGLCD_SUCCESS;

        do
        {
            i--;

            if ((0UL == value) && (i != position) && (!zeroes))
            {
                /* For 'not zeroes' mode each extra digit is cleared. */
                locNum = (uint32_t)CY_SEGLCD_NUM_BLANK;
            }
            else
            {
                /* Display the subsequent digit or '0' for 'zeroes' mode */
                locNum = value % locDiv;
            }

            /* Calculate the next digit value */
            value = value / locDiv;

            retVal |= (uint32_t)Cy_SegLCD_WriteChar(base, (display->font->ascii) ? NumToChar(locNum) : (char_t)locNum, i, display);
        }
        while (i != 0UL); /* While the current digit position is in the range of the display, keep processing the output */

        if (0UL != value)
        {
            retVal |= (uint32_t)CY_SEGLCD_EXCEED;
        }
    }

    return((cy_en_seglcd_status_t)retVal);
}


/*******************************************************************************
* Function Name: Cy_SegLCD_WriteString
****************************************************************************//**
*
* Writes a specified zero-terminated char string onto a specified display.
* Supports all display types except \ref CY_SEGLCD_BAR.
*
* \param base The base pointer to the LCD instance registers.
* \param string The pointer to the ASCII-coded null-terminated character string.
* \param position The position of the first string character at the display
*        as counted left to right starting at 0 - the first symbol on the left
*        of the specified display.
*        If the specified display contains fewer symbols than the string
*        requires to be displayed, the extra character(s) is(are) not displayed
*        and the \ref CY_SEGLCD_EXCEED value is returned.
* \param display The pointer to the display structure \ref cy_stc_seglcd_disp_t.
* \return \ref cy_en_seglcd_status_t.
*
* \funcusage
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_String
*
*******************************************************************************/
cy_en_seglcd_status_t Cy_SegLCD_WriteString(LCD_Type * base,
                                        char_t const * string,
                                            uint32_t   position,
                          cy_stc_seglcd_disp_t const * display)
{
    uint32_t retVal = (uint32_t)CY_SEGLCD_BAD_PARAM;

    if (CY_SEGLCD_IS_ASCII(display, position)) /* If the display is symbolic/numeric and the font is ASCII-coded */
    {
        uint32_t i;
        retVal = (uint32_t)CY_SEGLCD_SUCCESS;

        for (i = 0UL; (i + position) < display->symNum; i++)
        {
            retVal |= (uint32_t)Cy_SegLCD_WriteChar(base, ('\0' != string[i]) ? string[i] : CY_SEGLCD_SPACE(display), i + position, display);
        }

        if ('\0' != string[i])
        {
            retVal |= (uint32_t)CY_SEGLCD_EXCEED;
        }
    }

    return((cy_en_seglcd_status_t)retVal);
}


/*******************************************************************************
* Function Name: Cy_SegLCD_BarGraph
****************************************************************************//**
*
* Draws a bar onto a specified bar graph / dial display.
* Only the \ref CY_SEGLCD_BAR display type is supported.
*
* \param base The base pointer to the LCD instance registers.
* \param value The length of the bar in pixels.
* \param position The position of the first bar pixel as counted from the
*        beginning ('0' is the first pixel) of the specified display.
*        If the specified display contains fewer pixels than the bar
*        requires to be displayed, the extra pixel(s) is(are) not
*        displayed and the \ref CY_SEGLCD_EXCEED value is returned.
* \param display The pointer to the display structure \ref cy_stc_seglcd_disp_t.
* \return \ref cy_en_seglcd_status_t.
*
* \funcusage
* \snippet seglcd/snippet/SegLCD_Snpt.h snippet_Cy_SegLCD_BarLength
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_BarGraphDisplay
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_BarGraphValue
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_BarGraph
*
*******************************************************************************/
cy_en_seglcd_status_t Cy_SegLCD_BarGraph(LCD_Type * base,
                                         uint32_t   value,
                                         uint32_t   position,
                       cy_stc_seglcd_disp_t const * display)
{
    uint32_t retVal = (uint32_t)CY_SEGLCD_BAD_PARAM;

    if (CY_SEGLCD_IS_BARGRAPH(display, position)) /* If the display is bar graph / dial */
    {
        uint32_t i;
        retVal = (uint32_t)CY_SEGLCD_SUCCESS;

        for (i = position; i < display->symNum; i++)
        {
            retVal |= (uint32_t)Cy_SegLCD_WritePixel(base, *(display->pixMap + i), i < (position + value));
        }

        if (((uint32_t)CY_SEGLCD_BAD_PIXEL != retVal) && ((position + value) > display->symNum))
        {
            retVal |= (uint32_t)CY_SEGLCD_EXCEED;
        }
    }

    return((cy_en_seglcd_status_t)retVal);
}
CY_MISRA_BLOCK_END('MISRA C-2012 Rule 11.3');

#endif /* CY_IP_MXLCD */

/* [] END OF FILE */
