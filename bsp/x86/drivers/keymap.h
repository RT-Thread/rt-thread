/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 */

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                              keymap.h
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/********************************************************************/
/*    "scan code" <--> "key" map.                                     */
/*    It should be and can only be included by keyboard.c!          */
/********************************************************************/

#ifndef _TINIX_KEYMAP_H_
#define _TINIX_KEYMAP_H_


/* Keymap for US MF-2 keyboard. */

rt_uint32_t keymap[NR_SCAN_CODES * MAP_COLS] = {

/* scan-code            !Shift      Shift       E0 XX       */
/* ==================================================================== */
/* 0x00 - none      */  0,      0,      0,
/* 0x01 - ESC       */  ESC,        ESC,        0,
/* 0x02 - '1'       */  '1',        '!',        0,
/* 0x03 - '2'       */  '2',        '@',        0,
/* 0x04 - '3'       */  '3',        '#',        0,
/* 0x05 - '4'       */  '4',        '$',        0,
/* 0x06 - '5'       */  '5',        '%',        0,
/* 0x07 - '6'       */  '6',        '^',        0,
/* 0x08 - '7'       */  '7',        '&',        0,
/* 0x09 - '8'       */  '8',        '*',        0,
/* 0x0A - '9'       */  '9',        '(',        0,
/* 0x0B - '0'       */  '0',        ')',        0,
/* 0x0C - '-'       */  '-',        '_',        0,
/* 0x0D - '='       */  '=',        '+',        0,
/* 0x0E - BS        */  BACKSPACE,  BACKSPACE,  0,
/* 0x0F - TAB       */  TAB,        TAB,        0,
/* 0x10 - 'q'       */  'q',        'Q',        0,
/* 0x11 - 'w'       */  'w',        'W',        0,
/* 0x12 - 'e'       */  'e',        'E',        0,
/* 0x13 - 'r'       */  'r',        'R',        0,
/* 0x14 - 't'       */  't',        'T',        0,
/* 0x15 - 'y'       */  'y',        'Y',        0,
/* 0x16 - 'u'       */  'u',        'U',        0,
/* 0x17 - 'i'       */  'i',        'I',        0,
/* 0x18 - 'o'       */  'o',        'O',        0,
/* 0x19 - 'p'       */  'p',        'P',        0,
/* 0x1A - '['       */  '[',        '{',        0,
/* 0x1B - ']'       */  ']',        '}',        0,
/* 0x1C - CR/LF     */  ENTER,      ENTER,      PAD_ENTER,
/* 0x1D - l. Ctrl   */  CTRL_L,     CTRL_L,     CTRL_R,
/* 0x1E - 'a'       */  'a',        'A',        0,
/* 0x1F - 's'       */  's',        'S',        0,
/* 0x20 - 'd'       */  'd',        'D',        0,
/* 0x21 - 'f'       */  'f',        'F',        0,
/* 0x22 - 'g'       */  'g',        'G',        0,
/* 0x23 - 'h'       */  'h',        'H',        0,
/* 0x24 - 'j'       */  'j',        'J',        0,
/* 0x25 - 'k'       */  'k',        'K',        0,
/* 0x26 - 'l'       */  'l',        'L',        0,
/* 0x27 - ';'       */  ';',        ':',        0,
/* 0x28 - '\''      */  '\'',       '"',        0,
/* 0x29 - '`'       */  '`',        '~',        0,
/* 0x2A - l. SHIFT  */  SHIFT_L,    SHIFT_L,    0,
/* 0x2B - '\'       */  '\\',       '|',        0,
/* 0x2C - 'z'       */  'z',        'Z',        0,
/* 0x2D - 'x'       */  'x',        'X',        0,
/* 0x2E - 'c'       */  'c',        'C',        0,
/* 0x2F - 'v'       */  'v',        'V',        0,
/* 0x30 - 'b'       */  'b',        'B',        0,
/* 0x31 - 'n'       */  'n',        'N',        0,
/* 0x32 - 'm'       */  'm',        'M',        0,
/* 0x33 - ','       */  ',',        '<',        0,
/* 0x34 - '.'       */  '.',        '>',        0,
/* 0x35 - '/'       */  '/',        '?',        PAD_SLASH,
/* 0x36 - r. SHIFT  */  SHIFT_R,    SHIFT_R,    0,
/* 0x37 - '*'       */  '*',        '*',        0,
/* 0x38 - ALT       */  ALT_L,      ALT_L,      ALT_R,
/* 0x39 - ' '       */  ' ',        ' ',        0,
/* 0x3A - CapsLock  */  CAPS_LOCK,  CAPS_LOCK,  0,
/* 0x3B - F1        */  F1,     F1,     0,
/* 0x3C - F2        */  F2,     F2,     0,
/* 0x3D - F3        */  F3,     F3,     0,
/* 0x3E - F4        */  F4,     F4,     0,
/* 0x3F - F5        */  F5,     F5,     0,
/* 0x40 - F6        */  F6,     F6,     0,
/* 0x41 - F7        */  F7,     F7,     0,
/* 0x42 - F8        */  F8,     F8,     0,
/* 0x43 - F9        */  F9,     F9,     0,
/* 0x44 - F10       */  F10,        F10,        0,
/* 0x45 - NumLock   */  NUM_LOCK,   NUM_LOCK,   0,
/* 0x46 - ScrLock   */  SCROLL_LOCK,    SCROLL_LOCK,    0,
/* 0x47 - Home      */  PAD_HOME,   '7',        HOME,
/* 0x48 - CurUp     */  PAD_UP,     '8',        UP,
/* 0x49 - PgUp      */  PAD_PAGEUP, '9',        PAGEUP,
/* 0x4A - '-'       */  PAD_MINUS,  '-',        0,
/* 0x4B - Left      */  PAD_LEFT,   '4',        LEFT,
/* 0x4C - MID       */  PAD_MID,    '5',        0,
/* 0x4D - Right     */  PAD_RIGHT,  '6',        RIGHT,
/* 0x4E - '+'       */  PAD_PLUS,   '+',        0,
/* 0x4F - End       */  PAD_END,    '1',        END,
/* 0x50 - Down      */  PAD_DOWN,   '2',        DOWN,
/* 0x51 - PgDown    */  PAD_PAGEDOWN,   '3',        PAGEDOWN,
/* 0x52 - Insert    */  PAD_INS,    '0',        INSERT,
/* 0x53 - Delete    */  PAD_DOT,    '.',        DELETE,
/* 0x54 - Enter     */  0,      0,      0,
/* 0x55 - ???       */  0,      0,      0,
/* 0x56 - ???       */  0,      0,      0,
/* 0x57 - F11       */  F11,        F11,        0,
/* 0x58 - F12       */  F12,        F12,        0,
/* 0x59 - ???       */  0,      0,      0,
/* 0x5A - ???       */  0,      0,      0,
/* 0x5B - ???       */  0,      0,      GUI_L,
/* 0x5C - ???       */  0,      0,      GUI_R,
/* 0x5D - ???       */  0,      0,      APPS,
/* 0x5E - ???       */  0,      0,      0,
/* 0x5F - ???       */  0,      0,      0,
/* 0x60 - ???       */  0,      0,      0,
/* 0x61 - ???       */  0,      0,      0,
/* 0x62 - ???       */  0,      0,      0,
/* 0x63 - ???       */  0,      0,      0,
/* 0x64 - ???       */  0,      0,      0,
/* 0x65 - ???       */  0,      0,      0,
/* 0x66 - ???       */  0,      0,      0,
/* 0x67 - ???       */  0,      0,      0,
/* 0x68 - ???       */  0,      0,      0,
/* 0x69 - ???       */  0,      0,      0,
/* 0x6A - ???       */  0,      0,      0,
/* 0x6B - ???       */  0,      0,      0,
/* 0x6C - ???       */  0,      0,      0,
/* 0x6D - ???       */  0,      0,      0,
/* 0x6E - ???       */  0,      0,      0,
/* 0x6F - ???       */  0,      0,      0,
/* 0x70 - ???       */  0,      0,      0,
/* 0x71 - ???       */  0,      0,      0,
/* 0x72 - ???       */  0,      0,      0,
/* 0x73 - ???       */  0,      0,      0,
/* 0x74 - ???       */  0,      0,      0,
/* 0x75 - ???       */  0,      0,      0,
/* 0x76 - ???       */  0,      0,      0,
/* 0x77 - ???       */  0,      0,      0,
/* 0x78 - ???       */  0,      0,      0,
/* 0x78 - ???       */  0,      0,      0,
/* 0x7A - ???       */  0,      0,      0,
/* 0x7B - ???       */  0,      0,      0,
/* 0x7C - ???       */  0,      0,      0,
/* 0x7D - ???       */  0,      0,      0,
/* 0x7E - ???       */  0,      0,      0,
/* 0x7F - ???       */  0,      0,      0
};

/*====================================================================================*
                Appendix: Scan code set 1
 *====================================================================================*

KEY MAKE    BREAK   -----   KEY MAKE    BREAK   -----   KEY MAKE    BREAK
--------------------------------------------------------------------------------------
A   1E  9E      9   0A  8A      [   1A  9A
B   30  B0      `   29  89      INSERT  E0,52   E0,D2
C   2E  AE      -   0C  8C      HOME    E0,47   E0,C7
D   20  A0      =   0D  8D      PG UP   E0,49   E0,C9
E   12  92      \   2B  AB      DELETE  E0,53   E0,D3
F   21  A1      BKSP    0E  8E      END E0,4F   E0,CF
G   22  A2      SPACE   39  B9      PG DN   E0,51   E0,D1
H   23  A3      TAB 0F  8F      U ARROW E0,48   E0,C8
I   17  97      CAPS    3A  BA      L ARROW E0,4B   E0,CB
J   24  A4      L SHFT  2A  AA      D ARROW E0,50   E0,D0
K   25  A5      L CTRL  1D  9D      R ARROW E0,4D   E0,CD
L   26  A6      L GUI   E0,5B   E0,DB       NUM 45  C5
M   32  B2      L ALT   38  B8      KP /    E0,35   E0,B5
N   31  B1      R SHFT  36  B6      KP *    37  B7
O   18  98      R CTRL  E0,1D   E0,9D       KP -    4A  CA
P   19  99      R GUI   E0,5C   E0,DC       KP +    4E  CE
Q   10  19      R ALT   E0,38   E0,B8       KP EN   E0,1C   E0,9C
R   13  93      APPS    E0,5D   E0,DD       KP .    53  D3
S   1F  9F      ENTER   1C  9C      KP 0    52  D2
T   14  94      ESC 01  81      KP 1    4F  CF
U   16  96      F1  3B  BB      KP 2    50  D0
V   2F  AF      F2  3C  BC      KP 3    51  D1
W   11  91      F3  3D  BD      KP 4    4B  CB
X   2D  AD      F4  3E  BE      KP 5    4C  CC
Y   15  95      F5  3F  BF      KP 6    4D  CD
Z   2C  AC      F6  40  C0      KP 7    47  C7
0   0B  8B      F7  41  C1      KP 8    48  C8
1   02  82      F8  42  C2      KP 9    49  C9
2   03  83      F9  43  C3      ]   1B  9B
3   04  84      F10 44  C4      ;   27  A7
4   05  85      F11 57  D7      '   28  A8
5   06  86      F12 58  D8      ,   33  B3

6   07  87      PRTSCRN E0,2A   E0,B7       .   34  B4
                    E0,37   E0,AA

7   08  88      SCROLL  46  C6      /   35  B5

8   09  89      PAUSE E1,1D,45  -NONE-
                      E1,9D,C5


-----------------
ACPI Scan Codes:
-------------------------------------------
Key     Make Code   Break Code
-------------------------------------------
Power       E0, 5E      E0, DE
Sleep       E0, 5F      E0, DF
Wake        E0, 63      E0, E3


-------------------------------
Windows Multimedia Scan Codes:
-------------------------------------------
Key     Make Code   Break Code
-------------------------------------------
Next Track  E0, 19      E0, 99
Previous Track  E0, 10      E0, 90
Stop        E0, 24      E0, A4
Play/Pause  E0, 22      E0, A2
Mute        E0, 20      E0, A0
Volume Up   E0, 30      E0, B0
Volume Down E0, 2E      E0, AE
Media Select    E0, 6D      E0, ED
E-Mail      E0, 6C      E0, EC
Calculator  E0, 21      E0, A1
My Computer E0, 6B      E0, EB
WWW Search  E0, 65      E0, E5
WWW Home    E0, 32      E0, B2
WWW Back    E0, 6A      E0, EA
WWW Forward E0, 69      E0, E9
WWW Stop    E0, 68      E0, E8
WWW Refresh E0, 67      E0, E7
WWW Favorites   E0, 66      E0, E6

*=====================================================================================*/



#endif /* _TINIX_KEYMAP_H_ */
