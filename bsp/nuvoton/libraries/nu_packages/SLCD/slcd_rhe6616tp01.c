/**************************************************************************//**
 * @file     LCDLIB.c
 * @version  V3.00
 * @brief    RHE6616TP01(8-COM, 40-SEG, 1/4 Bias) LCD library source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2019-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

#include <rtthread.h>
#include <rtdevice.h>

#include "drv_slcd.h"
#include "slcd_rhe6616tp01.h"

#define DBG_SECTION_NAME "slcd_demo"
#define DBG_LEVEL DBG_LOG
#include <rtdbg.h>

static rt_device_t g_psDev = RT_NULL;

/**************************************************************************//**
 *
 * Defines each text's segment (alphabet+numeric) in terms of COM and SEG numbers,
 * Using this way that text segment can be consisted of each bit in the
 * following bit pattern:
 * @illustration
 *              A
 *         -----------
 *         |\   |   /|
 *         F G  H  I B
 *         |  \ | /  |
 *         --J-- --K--
 *         |   /| \  |
 *         E  L M  N C
 *         | /  |   \|
 *         -----------
 *              D
 *
 *              0
 *         -----------
 *         |\   |   /|
 *        5| 6  7  8 |1
 *         |  \ | /  |
 *         --9-- -10--
 *         |   /| \  |
 *        4| 11 12 13|2
 *         | /  |   \|
 *         -----------
 *              3
 *
 *****************************************************************************/
static const char acMainDigitRawData[ZONE_MAIN_DIG_CNT][ZONE_MAIN_SEG_NUM][2] =
{
    {
        // digit 1, {com, seg}
        // A     // B     // C     // D
        {0,  1}, {0,  0}, {3,  0}, {3,  1},
        // E     // F     // G     // H
        {2,  3}, {0,  3}, {0,  2}, {1,  1},
        // I     // J     // K     // L
        {1,  0}, {1,  2}, {2,  0}, {3,  2},
        // M     // N
        {2,  2}, {2,  1},
    },
    {
        // digit 2, {com, seg}
        // A     // B     // C     // D
        {0, 18}, {0, 19}, {3, 19}, {3, 18},
        // E     // F     // G     // H
        {2, 16}, {0, 16}, {0, 17}, {1, 18},
        // I     // J     // K     // L
        {1, 19}, {1, 17}, {2, 19}, {3, 17},
        // M     // N
        {2, 17}, {2, 18},
    },
    {
        // digit 3, {com, seg}
        // A     // B     // C     // D
        {0, 22}, {0, 23}, {3, 23}, {3, 22},
        // E     // F     // G     // H
        {2, 20}, {0, 20}, {0, 21}, {1, 22},
        // I     // J     // K     // L
        {1, 23}, {1, 21}, {2, 23}, {3, 21},
        // M     // N
        {2, 21}, {2, 22},
    },
    {
        // digit 4, {com, seg}
        // A     // B     // C     // D
        {0, 26}, {0, 27}, {3, 27}, {3, 26},
        // E     // F     // G     // H
        {2, 24}, {0, 24}, {0, 25}, {1, 26},
        // I     // J     // K     // L
        {1, 27}, {1, 25}, {2, 27}, {3, 25},
        // M     // N
        {2, 25}, {2, 26},
    },
    {
        // digit 5, {com, seg}
        // A     // B     // C     // D
        {0, 30}, {0, 31}, {3, 31}, {3, 30},
        // E     // F     // G     // H
        {2, 28}, {0, 28}, {0, 29}, {1, 30},
        // I     // J     // K     // L
        {1, 31}, {1, 29}, {2, 31}, {3, 29},
        // M     // N
        {2, 29}, {2, 30},
    },
    {
        // digit 6, {com, seg}
        // A     // B     // C     // D
        {0, 34}, {0, 35}, {3, 35}, {3, 34},
        // E     // F     // G     // H
        {2, 32}, {0, 32}, {0, 33}, {1, 34},
        // I     // J     // K     // L
        {1, 35}, {1, 33}, {2, 35}, {3, 33},
        // M     // N
        {2, 33}, {2, 34},
    },
    {
        // digit 7, {com, seg}
        // A     // B     // C     // D
        {0, 38}, {0, 39}, {3, 39}, {3, 38},
        // E     // F     // G     // H
        {2, 36}, {0, 36}, {0, 37}, {1, 38},
        // I     // J     // K     // L
        {1, 39}, {1, 37}, {2, 39}, {3, 37},
        // M     // N
        {2, 37}, {2, 38},
    },
};


/**************************************************************************//**
 *
 * Defines each text's segment (numeric) in terms of COM and BIT numbers,
 * Using this way that text segment can be consisted of each bit in the
 * following bit pattern:
 * @illustration
 *
 *         ---A---
 *         |     |
 *         F     B
 *         |     |
 *         ---G---
 *         |     |
 *         E     C
 *         |     |
 *         ---D---
 *
 *         ---0---
 *         |     |
 *         5     1
 *         |     |
 *         ---6---
 *         |     |
 *         4     2
 *         |     |
 *         ---3---
 *
 *****************************************************************************/
static const char acPPMDigitRawData[ZONE_PPM_DIG_CNT][ZONE_PPM_SEG_NUM][2] =
{
    {
        // digit 1, {com, seg}
        // A     // B     // C     // D
        {4, 16}, {5, 17}, {7, 17}, {7, 16},
        // E     // F     // G
        {6, 16}, {5, 16}, {6, 17},
    },
    {
        // digit 2, {com, seg}
        // A     // B     // C     // D
        {4, 18}, {5, 19}, {7, 19}, {7, 18},
        // E     // F     // G
        {6, 18}, {5, 18}, {6, 19},
    },
    {
        // digit 3, {com, seg}
        // A     // B     // C     // D
        {4, 20}, {5, 21}, {7, 21}, {7, 20},
        // E     // F     // G
        {6, 20}, {5, 20}, {6, 21},
    },
};

static const char acTEMPDigitRawData[ZONE_TEMP_DIG_CNT][ZONE_TEMP_SEG_NUM][2] =
{
    {
        // digit 1, {com, seg}
        // A     // B     // C     // D
        {4, 22}, {5, 23}, {7, 23}, {7, 22},
        // E     // F     // G
        {6, 22}, {5, 22}, {6, 23},
    },
    {
        // digit 2, {com, seg}
        // A     // B     // C     // D
        {4, 24}, {5, 25}, {7, 25}, {7, 24},
        // E     // F     // G
        {6, 24}, {5, 24}, {6, 25},
    },
    {
        // digit 3, {com, seg}
        // A     // B     // C     // D
        {4, 26}, {5, 27}, {7, 27}, {7, 26},
        // E     // F     // G
        {6, 26}, {5, 26}, {6, 27},
    },
};

static const char acVERDigitRawData[ZONE_VER_DIG_CNT][ZONE_VER_SEG_NUM][2] =
{
    {
        // digit 1, {com, seg}
        // A     // B     // C     // D
        {4, 28}, {5, 29}, {7, 29}, {7, 28},
        // E     // F     // G
        {6, 28}, {5, 28}, {6, 29},
    },
    {
        // digit 2, {com, seg}
        // A     // B     // C     // D
        {4, 30}, {5, 31}, {7, 31}, {7, 30},
        // E     // F     // G
        {6, 30}, {5, 30}, {6, 31},
    },
    {
        // digit 3, {com, seg}
        // A     // B     // C     // D
        {4, 32}, {5, 33}, {7, 33}, {7, 32},
        // E     // F     // G
        {6, 32}, {5, 32}, {6, 33},
    },
    {
        // digit 4, {com, seg}
        // A     // B     // C     // D
        {4, 34}, {5, 35}, {7, 35}, {7, 34},
        // E     // F     // G
        {6, 34}, {5, 34}, {6, 35},
    },
    {
        // digit 5, {com, seg}
        // A     // B     // C     // D
        {4, 36}, {5, 37}, {7, 37}, {7, 36},
        // E     // F     // G
        {6, 36}, {5, 36}, {6, 37},
    },
    {
        // digit 6, {com, seg}
        // A     // B     // C     // D
        {4, 38}, {5, 39}, {7, 39}, {7, 38},
        // E     // F     // G
        {6, 38}, {5, 38}, {6, 39},
    },
};

static const char acTimeDigitRawData[ZONE_TIME_DIG_CNT][ZONE_TIME_SEG_NUM][2] =
{
    {
        // digit 1, {com, seg}
        // A     // B     // C     // D
        {7,  2}, {6,  3}, {4,  3}, {4,  2},
        // E     // F     // G
        {5,  2}, {6,  2}, {5, 3},
    },
    {
        // digit 2, {com, seg}
        // A     // B     // C     // D
        {7,  4}, {6,  5}, {4,  5}, {4,  4},
        // E     // F     // G
        {5,  4}, {6,  4}, {5, 5},
    },
    {
        // digit 3, {com, seg}
        // A     // B     // C     // D
        {7,  6}, {6,  7}, {4,  7}, {4,  6},
        // E     // F     // G
        {5,  6}, {6,  6}, {5, 7},
    },
    {
        // digit 4, {com, seg}
        // A     // B     // C     // D
        {7,  8}, {6,  9}, {4,  9}, {4,  8},
        // E     // F     // G
        {5,  8}, {6,  8}, {5, 9},
    },
};

static const char acNuMicroDigitRawData[ZONE_NUMICRO_DIG_CNT][ZONE_NUMICRO_SEG_NUM][2] =
{
    {
        // digit 1, {com, seg}
        // A     // B     // C     // D
        {3,  4}, {2,  5}, {0,  5}, {0,  4},
        // E     // F     // G
        {1,  4}, {2,  4}, {1,  5},
    },
    {
        // digit 2, {com, seg}
        // A     // B     // C     // D
        {3,  6}, {2,  7}, {0,  7}, {0,  6},
        // E     // F     // G
        {1,  6}, {2,  6}, {1,  7},
    },
    {
        // digit 3, {com, seg}
        // A     // B     // C     // D
        {3,  8}, {2,  9}, {0,  9}, {0,  8},
        // E     // F     // G
        {1,  8}, {2,  8}, {1,  9},
    },
};

/**************************************************************************//**
 *
 * Defines segments for the alphabet - ASCII table 0x20 to 0x7A
 * Bit pattern below defined for alphabet (text segments)
 *
 *****************************************************************************/
static const uint16_t auMainDigitMap[] =
{
    0x0000, /* space */
    0x1100, /* ! */
    0x0280, /* " */
    0x0000, /* # */
    0x0000, /* $ */
    0x0000, /* % */
    0x0000, /* & */
    0x0000, /* ? */
    0x0039, /* ( */
    0x000f, /* ) */
    0x3fc0, /* * */
    0x1540, /* + */
    0x0000, /* , */
    0x0440, /* - */
    0x8000, /* . */
    0x2200, /* / */

    0x003F, /* 0 */
    0x0006, /* 1 */
    0x061B, /* 2 */
    0x060F, /* 3 */
    0x0626, /* 4 */
    0x062D, /* 5 */
    0x063D, /* 6 */
    0x0007, /* 7 */
    0x063F, /* 8 */
    0x062F, /* 9 */

    0x0000, /* : */
    0x0000, /* ; */
    0x2100, /* < */
    0x0000, /* = */
    0x0840, /* > */
    0x1403, /* ? */
    0x3FFF, /* @ */

    0x0637, /* A */
    0x2339, /* B */
    0x0039, /* C */
    0x2139, /* D */
    0x0639, /* E */
    0x0631, /* F */
    0x043D, /* G */
    0x0636, /* H */
    0x1080, /* I */
    0x000E, /* J */
    0x2330, /* K */
    0x0038, /* L */
    0x0176, /* M */
    0x2076, /* N */
    0x003F, /* O */
    0x0633, /* P */
    0x203F, /* Q */
    0x2331, /* R */
    0x062D, /* S */
    0x1081, /* T */
    0x003E, /* U */
    0x0930, /* V */
    0x2836, /* W */
    0x2940, /* X */
    0x1140, /* Y */
    0x0909, /* Z */

    0x0039, /* [ */
    0x0900, /* backslash */
    0x000F, /* ] */
    0x2800, /* ^ */
    0x0008, /* _ */
    0x0040, /* ` */

    0x1218, /* a */
    0x063C, /* b */
    0x0618, /* c */
    0x061E, /* d */
    0x0A18, /* e */
    0x0231, /* f */
    0x048F, /* g */
    0x1230, /* h */
    0x1000, /* i */
    0x000E, /* j */
    0x2330, /* k */
    0x0038, /* l */
    0x1614, /* m */
    0x1404, /* n */
    0x061C, /* o */
    0x0331, /* p */
    0x0447, /* q */
    0x1400, /* r */
    0x2408, /* s */
    0x0238, /* t */
    0x1018, /* u */
    0x0810, /* v */
    0x2814, /* w */
    0x2940, /* x */
    0x0446, /* y */
    0x0A08, /* z */

    0x0000,
};

/**************************************************************************//**
 * Defines segments for the numeric display
 *****************************************************************************/
static const uint16_t auPPMDigitMap[] =
{
    0x3F, /* 0 */
    0x06, /* 1 */
    0x5B, /* 2 */
    0x4F, /* 3 */
    0x66, /* 4 */
    0x6D, /* 5 */
    0x7D, /* 6 */
    0x07, /* 7 */
    0x7F, /* 8 */
    0x6F, /* 9 */
};

static const uint16_t auTEMPDigitMap[] =
{
    0x3F, /* 0 */
    0x06, /* 1 */
    0x5B, /* 2 */
    0x4F, /* 3 */
    0x66, /* 4 */
    0x6D, /* 5 */
    0x7D, /* 6 */
    0x07, /* 7 */
    0x7F, /* 8 */
    0x6F, /* 9 */
};

static const uint16_t auVERDigitMap[] =
{
    0x3F, /* 0 */
    0x06, /* 1 */
    0x5B, /* 2 */
    0x4F, /* 3 */
    0x66, /* 4 */
    0x6D, /* 5 */
    0x7D, /* 6 */
    0x07, /* 7 */
    0x7F, /* 8 */
    0x6F, /* 9 */
};

static const uint16_t auTimeDigitMap[] =
{
    0x3F, /* 0 */
    0x06, /* 1 */
    0x5B, /* 2 */
    0x4F, /* 3 */
    0x66, /* 4 */
    0x6D, /* 5 */
    0x7D, /* 6 */
    0x07, /* 7 */
    0x7F, /* 8 */
    0x6F, /* 9 */
};

static const uint16_t auNuMicroDigitMap[] =
{
    0x3F, /* 0 */
    0x06, /* 1 */
    0x5B, /* 2 */
    0x4F, /* 3 */
    0x66, /* 4 */
    0x6D, /* 5 */
    0x7D, /* 6 */
    0x07, /* 7 */
    0x7F, /* 8 */
    0x6F, /* 9 */
};

/* Zone information */
static const LCD_ZONE_INFO_T g_LCDZoneInfo[] =
{
    {ZONE_MAIN_DIG_CNT,     ZONE_MAIN_SEG_NUM},
    {ZONE_PPM_DIG_CNT,      ZONE_PPM_SEG_NUM},
    {ZONE_TEMP_DIG_CNT,     ZONE_TEMP_SEG_NUM},
    {ZONE_VER_DIG_CNT,      ZONE_VER_SEG_NUM},
    {ZONE_TIME_DIG_CNT,     ZONE_TIME_SEG_NUM},
    {ZONE_NUMICRO_DIG_CNT,  ZONE_NUMICRO_SEG_NUM},
};

/* Raw data table for each zone */
static const char *g_GetLCDComSeg[] =
{
    (const char *)(acMainDigitRawData),
    (const char *)(acPPMDigitRawData),
    (const char *)(acTEMPDigitRawData),
    (const char *)(acVERDigitRawData),
    (const char *)(acTimeDigitRawData),
    (const char *)(acNuMicroDigitRawData),
};

/* Display mapping table for each zone */
static const uint16_t *g_LCDDispTable[] =
{
    (const uint16_t *)(auMainDigitMap),
    (const uint16_t *)(auPPMDigitMap),
    (const uint16_t *)(auTEMPDigitMap),
    (const uint16_t *)(auVERDigitMap),
    (const uint16_t *)(auTimeDigitMap),
    (const uint16_t *)(auNuMicroDigitMap),
};


void SLCD_SetPixel(uint32_t u32Com, uint32_t u32Seg, uint32_t u32OnFlag)
{
    if (g_psDev)
    {
        struct nu_slcd_pixel sNuSLCDPxl;

        sNuSLCDPxl.m_u32Com = u32Com;
        sNuSLCDPxl.m_u32Seg = u32Seg;
        sNuSLCDPxl.m_u32OnFlag = u32OnFlag;
        rt_device_write(g_psDev, 0, (void *)&sNuSLCDPxl, sizeof(struct nu_slcd_pixel));
    }
}

/**
 *  @brief Display text on LCD
 *
 *  @param[in]  u32Zone     the assigned number of display area
 *  @param[in]  InputStr    Text string to show on display
 *
 *  @return None
 */
void LCDLIB_Printf(uint32_t u32Zone, char *InputStr)
{
    uint32_t    i, index, ch, len;
    uint16_t    DispData;
    uint32_t    com, seg;

    len = rt_strlen(InputStr);

    /* Fill out all characters on display */
    for (index = 0; index < g_LCDZoneInfo[u32Zone].u32DigitCnt; index++)
    {
        if (index < len)
        {
            ch = *InputStr;
        }
        else
        {
            /* Padding with SPACE */
            ch = 0x20;
        }

        /* For Main Zone */
        if (u32Zone == ZONE_MAIN_DIGIT)
        {
            /* The Main Digit Table is an ASCII table beginning with "SPACE" (hex is 0x20) */
            ch = ch - 0x20;
            DispData = *(g_LCDDispTable[u32Zone] + ch);
        }
        /* For Other Zones (Support '0' ~ '9' only) */
        else if ((ch >= '0') && (ch <= '9'))
        {
            ch = ch - '0';
            DispData = *(g_LCDDispTable[u32Zone] + ch);
        }
        /* Out of definition. Will show "SPACE" */
        else
        {
            DispData = 0;
        }

        for (i = 0; i < g_LCDZoneInfo[u32Zone].u32MaxSegNum; i++)
        {
            com = *(g_GetLCDComSeg[u32Zone]
                    + (index * g_LCDZoneInfo[u32Zone].u32MaxSegNum * 2)
                    + (i * 2) + 0);
            seg = *(g_GetLCDComSeg[u32Zone]
                    + (index * g_LCDZoneInfo[u32Zone].u32MaxSegNum * 2)
                    + (i * 2) + 1);

            /* Turn off display */
            SLCD_SetPixel(com, seg, 0);

            if (DispData & (1 << i))
            {
                /* Turn on display */
                SLCD_SetPixel(com, seg, 1);
            }
        }

        InputStr++;
    }
}

/**
 *  @brief Display number on LCD
 *
 *  @param[in]  u32Zone     the assigned number of display area
 *  @param[in]  InputNum    number to show on display
 *
 *  @return None
 */
void LCDLIB_PrintNumber(uint32_t u32Zone, uint32_t InputNum)
{
    uint32_t    i, index, val, div;
    uint16_t    DispData;
    uint32_t    com, seg;

    /* Extract useful digits */
    div = 1;

    /* Fill out all characters on display */
    index = g_LCDZoneInfo[u32Zone].u32DigitCnt;
    while (index != 0)
    {
        index--;

        val = (InputNum / div) % 10;
        if (u32Zone == ZONE_MAIN_DIGIT)
            val += 16; /* The Main Digit Table is an ASCII table beginning with "SPACE" */

        DispData = *(g_LCDDispTable[u32Zone] + val);

        for (i = 0; i < g_LCDZoneInfo[u32Zone].u32MaxSegNum; i++)
        {
            com = *(g_GetLCDComSeg[u32Zone]
                    + (index * g_LCDZoneInfo[u32Zone].u32MaxSegNum * 2)
                    + (i * 2) + 0);
            seg = *(g_GetLCDComSeg[u32Zone]
                    + (index * g_LCDZoneInfo[u32Zone].u32MaxSegNum * 2)
                    + (i * 2) + 1);

            /* Turn off display */
            SLCD_SetPixel(com, seg, 0);

            if (DispData & (1 << i))
            {
                /* Turn on display */
                SLCD_SetPixel(com, seg, 1);
            }
        }

        div = div * 10;
    }
}

/**
 *  @brief Display character on LCD
 *
 *  @param[in]  u32Zone     the assigned number of display area
 *  @param[in]  u32Index    the requested display position in zone
 *  @param[in]  u8Ch        Character to show on display
 *
 *  @return None
 */
void LCDLIB_PutChar(uint32_t u32Zone, uint32_t u32Index, uint8_t u8Ch)
{
    uint32_t    i;
    uint16_t    DispData;
    uint32_t    com, seg;

    if (u32Index <= g_LCDZoneInfo[u32Zone].u32DigitCnt)
    {
        /* For Main Zone */
        if (u32Zone == ZONE_MAIN_DIGIT)
        {
            /* The Main Digit Table is an ASCII table beginning with "SPACE" (hex is 0x20) */
            u8Ch = u8Ch - 0x20;
            DispData = *(g_LCDDispTable[u32Zone] + u8Ch);
        }
        /* For Other Zones (Support '0' ~ '9' only) */
        else if ((u8Ch >= '0') && (u8Ch <= '9'))
        {
            u8Ch = u8Ch - '0';
            DispData = *(g_LCDDispTable[u32Zone] + u8Ch);
        }
        /* Out of definition. Will show "SPACE" */
        else
        {
            DispData = 0;
        }

        for (i = 0; i < g_LCDZoneInfo[u32Zone].u32MaxSegNum; i++)
        {
            com = *(g_GetLCDComSeg[u32Zone]
                    + (u32Index * g_LCDZoneInfo[u32Zone].u32MaxSegNum * 2)
                    + (i * 2) + 0);

            seg = *(g_GetLCDComSeg[u32Zone]
                    + (u32Index * g_LCDZoneInfo[u32Zone].u32MaxSegNum * 2)
                    + (i * 2) + 1);

            /* Turn off display */
            SLCD_SetPixel(com, seg, 0);

            if (DispData & (1 << i))
            {
                /* Turn on display */
                SLCD_SetPixel(com, seg, 1);
            }
        }
    }
}

/**
 *  @brief Display symbol on LCD
 *
 *  @param[in]  u32Symbol   the combination of com, seg position
 *  @param[in]  u32OnOff    1: display symbol
 *                          0: not display symbol
 *
 *  @return     None
 */
void LCDLIB_SetSymbol(uint32_t u32Symbol, uint32_t u32OnOff)
{
    uint32_t com, seg;

    com = (u32Symbol & 0xF);
    seg = ((u32Symbol & 0xFF0) >> 4);

    if (u32OnOff)
        SLCD_SetPixel(com, seg, 1); /* Turn on display */
    else
        SLCD_SetPixel(com, seg, 0); /* Turn off display */

}

static S_LCD_CFG_T g_LCDCfg_RHE6616TP01 =
{
    __LXT,                      /*!< LCD clock source frequency */
    LCD_COM_DUTY_1_8,           /*!< COM duty */
    LCD_BIAS_LV_1_4,            /*!< Bias level */
    64,                         /*!< Operation frame rate */
    LCD_WAVEFORM_TYPE_A_NORMAL, /*!< Waveform type */
    LCD_DISABLE_ALL_INT,        /*!< Interrupt source */
    LCD_LOW_DRIVING_AND_BUF_ON, /*!< Driving mode */
    LCD_VOLTAGE_SOURCE_CP,      /*!< Voltage source */
};

static int nu_slcd_panel_init(void)
{
    uint32_t u32CPVol;
    rt_err_t ret = RT_EOK;

    g_psDev = rt_device_find("slcd");
    if (g_psDev == RT_NULL)
    {
        LOG_E("can't find slcd failed!\n");
        goto fail_nu_slcd_panel_init;
    }

    /* Give owned SLCD configuration before openning. */
    ret = rt_device_control(g_psDev, NU_SLCD_CMD_SET_LCD_CFG, (void *)&g_LCDCfg_RHE6616TP01);
    if (ret != RT_EOK)
    {
        LOG_E("configure SLCD failed!\n");
        goto fail_nu_slcd_panel_init;
    }

    /* Open SLCD. */
    ret = rt_device_open(g_psDev, RT_DEVICE_FLAG_WRONLY);
    if (ret != RT_EOK)
    {
        LOG_E("open dev failed!\n");
        goto fail_nu_slcd_panel_init;
    }

    /* Note: This panel need inject 4.8v, but m2354 charge pump max voltage is 3.6v. */
    u32CPVol = LCD_CP_VOLTAGE_LV_5;
    ret = rt_device_control(g_psDev, NU_SLCD_CMD_SET_CP_VOLTAGE, (void *)&u32CPVol);
    if (ret != RT_EOK)
    {
        LOG_E("faile to control cp voltage!\n");
        goto fail_nu_slcd_panel_init;
    }

    return (int)ret;

fail_nu_slcd_panel_init:

    if (g_psDev)
    {
        rt_device_close(g_psDev);
        g_psDev = RT_NULL;
    }
    return (int)ret;
}
INIT_COMPONENT_EXPORT(nu_slcd_panel_init);

/*** (C) COPYRIGHT 2019-2020 Nuvoton Technology Corp. ***/
