/*
 * File      : kbddef.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-16     Bernard      first version
 */
#ifndef __KBD_DEF_H__
#define __KBD_DEF_H__

/* The keyboard key have been cleverly chosen to map to ASCII */
typedef enum
{
    RTGUIK_UNKNOWN      = 0,
    RTGUIK_FIRST        = 0,
    RTGUIK_BACKSPACE    = 8,
    RTGUIK_TAB          = 9,
    RTGUIK_CLEAR        = 12,
    RTGUIK_RETURN       = 13,
    RTGUIK_PAUSE        = 19,
    RTGUIK_ESCAPE       = 27,
    RTGUIK_SPACE        = 32,
    RTGUIK_EXCLAIM      = 33,
    RTGUIK_QUOTEDBL     = 34,
    RTGUIK_HASH         = 35,
    RTGUIK_DOLLAR       = 36,
    RTGUIK_AMPERSAND    = 38,
    RTGUIK_QUOTE        = 39,
    RTGUIK_LEFTPAREN    = 40,
    RTGUIK_RIGHTPAREN   = 41,
    RTGUIK_ASTERISK     = 42,
    RTGUIK_PLUS         = 43,
    RTGUIK_COMMA        = 44,
    RTGUIK_MINUS        = 45,
    RTGUIK_PERIOD       = 46,
    RTGUIK_SLASH        = 47,
    RTGUIK_0            = 48,
    RTGUIK_1            = 49,
    RTGUIK_2            = 50,
    RTGUIK_3            = 51,
    RTGUIK_4            = 52,
    RTGUIK_5            = 53,
    RTGUIK_6            = 54,
    RTGUIK_7            = 55,
    RTGUIK_8            = 56,
    RTGUIK_9            = 57,
    RTGUIK_COLON        = 58,
    RTGUIK_SEMICOLON    = 59,
    RTGUIK_LESS         = 60,
    RTGUIK_EQUALS       = 61,
    RTGUIK_GREATER      = 62,
    RTGUIK_QUESTION     = 63,
    RTGUIK_AT           = 64,

    /*
       Skip uppercase letters
     */
    RTGUIK_LEFTBRACKET  = 91,
    RTGUIK_BACKSLASH    = 92,
    RTGUIK_RIGHTBRACKET = 93,
    RTGUIK_CARET        = 94,
    RTGUIK_UNDERSCORE   = 95,
    RTGUIK_BACKQUOTE    = 96,
    RTGUIK_a            = 97,
    RTGUIK_b            = 98,
    RTGUIK_c            = 99,
    RTGUIK_d            = 100,
    RTGUIK_e            = 101,
    RTGUIK_f            = 102,
    RTGUIK_g            = 103,
    RTGUIK_h            = 104,
    RTGUIK_i            = 105,
    RTGUIK_j            = 106,
    RTGUIK_k            = 107,
    RTGUIK_l            = 108,
    RTGUIK_m            = 109,
    RTGUIK_n            = 110,
    RTGUIK_o            = 111,
    RTGUIK_p            = 112,
    RTGUIK_q            = 113,
    RTGUIK_r            = 114,
    RTGUIK_s            = 115,
    RTGUIK_t            = 116,
    RTGUIK_u            = 117,
    RTGUIK_v            = 118,
    RTGUIK_w            = 119,
    RTGUIK_x            = 120,
    RTGUIK_y            = 121,
    RTGUIK_z            = 122,
    RTGUIK_DELETE       = 127,

    /* International keyboard */
    RTGUIK_WORLD_0      = 160,      /* 0xA0 */
    RTGUIK_WORLD_1      = 161,
    RTGUIK_WORLD_2      = 162,
    RTGUIK_WORLD_3      = 163,
    RTGUIK_WORLD_4      = 164,
    RTGUIK_WORLD_5      = 165,
    RTGUIK_WORLD_6      = 166,
    RTGUIK_WORLD_7      = 167,
    RTGUIK_WORLD_8      = 168,
    RTGUIK_WORLD_9      = 169,
    RTGUIK_WORLD_10     = 170,
    RTGUIK_WORLD_11     = 171,
    RTGUIK_WORLD_12     = 172,
    RTGUIK_WORLD_13     = 173,
    RTGUIK_WORLD_14     = 174,
    RTGUIK_WORLD_15     = 175,
    RTGUIK_WORLD_16     = 176,
    RTGUIK_WORLD_17     = 177,
    RTGUIK_WORLD_18     = 178,
    RTGUIK_WORLD_19     = 179,
    RTGUIK_WORLD_20     = 180,
    RTGUIK_WORLD_21     = 181,
    RTGUIK_WORLD_22     = 182,
    RTGUIK_WORLD_23     = 183,
    RTGUIK_WORLD_24     = 184,
    RTGUIK_WORLD_25     = 185,
    RTGUIK_WORLD_26     = 186,
    RTGUIK_WORLD_27     = 187,
    RTGUIK_WORLD_28     = 188,
    RTGUIK_WORLD_29     = 189,
    RTGUIK_WORLD_30     = 190,
    RTGUIK_WORLD_31     = 191,
    RTGUIK_WORLD_32     = 192,
    RTGUIK_WORLD_33     = 193,
    RTGUIK_WORLD_34     = 194,
    RTGUIK_WORLD_35     = 195,
    RTGUIK_WORLD_36     = 196,
    RTGUIK_WORLD_37     = 197,
    RTGUIK_WORLD_38     = 198,
    RTGUIK_WORLD_39     = 199,
    RTGUIK_WORLD_40     = 200,
    RTGUIK_WORLD_41     = 201,
    RTGUIK_WORLD_42     = 202,
    RTGUIK_WORLD_43     = 203,
    RTGUIK_WORLD_44     = 204,
    RTGUIK_WORLD_45     = 205,
    RTGUIK_WORLD_46     = 206,
    RTGUIK_WORLD_47     = 207,
    RTGUIK_WORLD_48     = 208,
    RTGUIK_WORLD_49     = 209,
    RTGUIK_WORLD_50     = 210,
    RTGUIK_WORLD_51     = 211,
    RTGUIK_WORLD_52     = 212,
    RTGUIK_WORLD_53     = 213,
    RTGUIK_WORLD_54     = 214,
    RTGUIK_WORLD_55     = 215,
    RTGUIK_WORLD_56     = 216,
    RTGUIK_WORLD_57     = 217,
    RTGUIK_WORLD_58     = 218,
    RTGUIK_WORLD_59     = 219,
    RTGUIK_WORLD_60     = 220,
    RTGUIK_WORLD_61     = 221,
    RTGUIK_WORLD_62     = 222,
    RTGUIK_WORLD_63     = 223,
    RTGUIK_WORLD_64     = 224,
    RTGUIK_WORLD_65     = 225,
    RTGUIK_WORLD_66     = 226,
    RTGUIK_WORLD_67     = 227,
    RTGUIK_WORLD_68     = 228,
    RTGUIK_WORLD_69     = 229,
    RTGUIK_WORLD_70     = 230,
    RTGUIK_WORLD_71     = 231,
    RTGUIK_WORLD_72     = 232,
    RTGUIK_WORLD_73     = 233,
    RTGUIK_WORLD_74     = 234,
    RTGUIK_WORLD_75     = 235,
    RTGUIK_WORLD_76     = 236,
    RTGUIK_WORLD_77     = 237,
    RTGUIK_WORLD_78     = 238,
    RTGUIK_WORLD_79     = 239,
    RTGUIK_WORLD_80     = 240,
    RTGUIK_WORLD_81     = 241,
    RTGUIK_WORLD_82     = 242,
    RTGUIK_WORLD_83     = 243,
    RTGUIK_WORLD_84     = 244,
    RTGUIK_WORLD_85     = 245,
    RTGUIK_WORLD_86     = 246,
    RTGUIK_WORLD_87     = 247,
    RTGUIK_WORLD_88     = 248,
    RTGUIK_WORLD_89     = 249,
    RTGUIK_WORLD_90     = 250,
    RTGUIK_WORLD_91     = 251,
    RTGUIK_WORLD_92     = 252,
    RTGUIK_WORLD_93     = 253,
    RTGUIK_WORLD_94     = 254,
    RTGUIK_WORLD_95     = 255,      /* 0xFF */

    /* Numeric keypad */
    RTGUIK_KP0          = 256,
    RTGUIK_KP1          = 257,
    RTGUIK_KP2          = 258,
    RTGUIK_KP3          = 259,
    RTGUIK_KP4          = 260,
    RTGUIK_KP5          = 261,
    RTGUIK_KP6          = 262,
    RTGUIK_KP7          = 263,
    RTGUIK_KP8          = 264,
    RTGUIK_KP9          = 265,
    RTGUIK_KP_PERIOD    = 266,
    RTGUIK_KP_DIVIDE    = 267,
    RTGUIK_KP_MULTIPLY  = 268,
    RTGUIK_KP_MINUS     = 269,
    RTGUIK_KP_PLUS      = 270,
    RTGUIK_KP_ENTER     = 271,
    RTGUIK_KP_EQUALS    = 272,

    /* Arrows + Home/End pad */
    RTGUIK_UP           = 273,
    RTGUIK_DOWN         = 274,
    RTGUIK_RIGHT        = 275,
    RTGUIK_LEFT         = 276,
    RTGUIK_INSERT       = 277,
    RTGUIK_HOME         = 278,
    RTGUIK_END          = 279,
    RTGUIK_PAGEUP       = 280,
    RTGUIK_PAGEDOWN     = 281,

    /* Function keys */
    RTGUIK_F1           = 282,
    RTGUIK_F2           = 283,
    RTGUIK_F3           = 284,
    RTGUIK_F4           = 285,
    RTGUIK_F5           = 286,
    RTGUIK_F6           = 287,
    RTGUIK_F7           = 288,
    RTGUIK_F8           = 289,
    RTGUIK_F9           = 290,
    RTGUIK_F10          = 291,
    RTGUIK_F11          = 292,
    RTGUIK_F12          = 293,
    RTGUIK_F13          = 294,
    RTGUIK_F14          = 295,
    RTGUIK_F15          = 296,

    /* Key state modifier keys */
    RTGUIK_NUMLOCK      = 300,
    RTGUIK_CAPSLOCK     = 301,
    RTGUIK_SCROLLOCK    = 302,
    RTGUIK_RSHIFT       = 303,
    RTGUIK_LSHIFT       = 304,
    RTGUIK_RCTRL        = 305,
    RTGUIK_LCTRL        = 306,
    RTGUIK_RALT         = 307,
    RTGUIK_LALT         = 308,
    RTGUIK_RMETA        = 309,
    RTGUIK_LMETA        = 310,
    RTGUIK_LSUPER       = 311,      /* Left "Windows" key */
    RTGUIK_RSUPER       = 312,      /* Right "Windows" key */
    RTGUIK_MODE         = 313,      /* "Alt Gr" key */
    RTGUIK_COMPOSE      = 314,      /* Multi-key compose key */

    /* Miscellaneous function keys */
    RTGUIK_HELP         = 315,
    RTGUIK_PRINT        = 316,
    RTGUIK_SYSREQ       = 317,
    RTGUIK_BREAK        = 318,
    RTGUIK_MENU         = 319,
    RTGUIK_POWER        = 320,      /* Power key */

    RTGUIK_LAST
} RTGUI_KBD_KEY;

/* Enumeration of valid key mods (possibly OR'd together) */
typedef enum
{
    RTGUI_KMOD_NONE     = 0x0000,
    RTGUI_KMOD_LSHIFT   = 0x0001,
    RTGUI_KMOD_RSHIFT   = 0x0002,
    RTGUI_KMOD_LCTRL    = 0x0040,
    RTGUI_KMOD_RCTRL    = 0x0080,
    RTGUI_KMOD_LALT     = 0x0100,
    RTGUI_KMOD_RALT     = 0x0200,
    RTGUI_KMOD_LMETA    = 0x0400,
    RTGUI_KMOD_RMETA    = 0x0800,
    RTGUI_KMOD_NUM      = 0x1000,
    RTGUI_KMOD_CAPS     = 0x2000,
    RTGUI_KMOD_MODE     = 0x4000,
    RTGUI_KMOD_RESERVED = 0x8000
} RTGUI_KBD_MOD;

typedef enum
{
    RTGUI_KEYDOWN,          /* Keys pressed */
    RTGUI_KEYUP,            /* Keys released */
} RTGUI_KBD_TYPE;

#endif
