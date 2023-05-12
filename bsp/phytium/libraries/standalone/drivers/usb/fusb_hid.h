/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fusb_hid.h
 * Date: 2022-02-11 13:33:09
 * LastEditTime: 2022-02-17 17:49:20
 * Description:  This files is for definition of USB hub device function
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/9/28   init commit
 */

#ifndef  FUSB_HID_H
#define  FUSB_HID_H

/***************************** Include Files *********************************/

#include "fusb.h"

#ifdef __cplusplus
extern "C"
{
#endif

/************************** Constant Definitions *****************************/
/*----------------------------------------------------------------------
 *
 *  Function and Keypad Key Definitions.
 *  Many are just for compatibility.
 *
 */

#define KEY_CODE_YES  0x100  /* If get_wch() gives a key code */

#define KEY_BREAK     0x101  /* Not on PC KBD */
#define KEY_DOWN      0x102  /* Down arrow key */
#define KEY_UP        0x103  /* Up arrow key */
#define KEY_LEFT      0x104  /* Left arrow key */
#define KEY_RIGHT     0x105  /* Right arrow key */
#define KEY_HOME      0x106  /* home key */
#define KEY_BACKSPACE 0x107  /* not on pc */
#define KEY_F0        0x108  /* function keys; 64 reserved */

#define KEY_DL        0x148  /* delete line */
#define KEY_IL        0x149  /* insert line */
#define KEY_DC        0x14a  /* delete character */
#define KEY_IC        0x14b  /* insert char or enter ins mode */
#define KEY_EIC       0x14c  /* exit insert char mode */
#define KEY_CLEAR     0x14d  /* clear screen */
#define KEY_EOS       0x14e  /* clear to end of screen */
#define KEY_EOL       0x14f  /* clear to end of line */
#define KEY_SF        0x150  /* scroll 1 line forward */
#define KEY_SR        0x151  /* scroll 1 line back (reverse) */
#define KEY_NPAGE     0x152  /* next page */
#define KEY_PPAGE     0x153  /* previous page */
#define KEY_STAB      0x154  /* set tab */
#define KEY_CTAB      0x155  /* clear tab */
#define KEY_CATAB     0x156  /* clear all tabs */
#define KEY_ENTER     0x157  /* enter or send (unreliable) */
#define KEY_SRESET    0x158  /* soft/reset (partial/unreliable) */
#define KEY_RESET     0x159  /* reset/hard reset (unreliable) */
#define KEY_PRINT     0x15a  /* print/copy */
#define KEY_LL        0x15b  /* home down/bottom (lower left) */
#define KEY_ABORT     0x15c  /* abort/terminate key (any) */
#define KEY_SHELP     0x15d  /* short help */
#define KEY_LHELP     0x15e  /* long help */
#define KEY_BTAB      0x15f  /* Back tab key */
#define KEY_BEG       0x160  /* beg(inning) key */
#define KEY_CANCEL    0x161  /* cancel key */
#define KEY_CLOSE     0x162  /* close key */
#define KEY_COMMAND   0x163  /* cmd (command) key */
#define KEY_COPY      0x164  /* copy key */
#define KEY_CREATE    0x165  /* create key */
#define KEY_END       0x166  /* end key */
#define KEY_EXIT      0x167  /* exit key */
#define KEY_FIND      0x168  /* find key */
#define KEY_HELP      0x169  /* help key */
#define KEY_MARK      0x16a  /* mark key */
#define KEY_MESSAGE   0x16b  /* message key */
#define KEY_MOVE      0x16c  /* move key */
#define KEY_NEXT      0x16d  /* next object key */
#define KEY_OPEN      0x16e  /* open key */
#define KEY_OPTIONS   0x16f  /* options key */
#define KEY_PREVIOUS  0x170  /* previous object key */
#define KEY_REDO      0x171  /* redo key */
#define KEY_REFERENCE 0x172  /* ref(erence) key */
#define KEY_REFRESH   0x173  /* refresh key */
#define KEY_REPLACE   0x174  /* replace key */
#define KEY_RESTART   0x175  /* restart key */
#define KEY_RESUME    0x176  /* resume key */
#define KEY_SAVE      0x177  /* save key */
#define KEY_SBEG      0x178  /* shifted beginning key */
#define KEY_SCANCEL   0x179  /* shifted cancel key */
#define KEY_SCOMMAND  0x17a  /* shifted command key */
#define KEY_SCOPY     0x17b  /* shifted copy key */
#define KEY_SCREATE   0x17c  /* shifted create key */
#define KEY_SDC       0x17d  /* shifted delete char key */
#define KEY_SDL       0x17e  /* shifted delete line key */
#define KEY_SELECT    0x17f  /* select key */
#define KEY_SEND      0x180  /* shifted end key */
#define KEY_SEOL      0x181  /* shifted clear line key */
#define KEY_SEXIT     0x182  /* shifted exit key */
#define KEY_SFIND     0x183  /* shifted find key */
#define KEY_SHOME     0x184  /* shifted home key */
#define KEY_SIC       0x185  /* shifted input key */

#define KEY_SLEFT     0x187  /* shifted left arrow key */
#define KEY_SMESSAGE  0x188  /* shifted message key */
#define KEY_SMOVE     0x189  /* shifted move key */
#define KEY_SNEXT     0x18a  /* shifted next key */
#define KEY_SOPTIONS  0x18b  /* shifted options key */
#define KEY_SPREVIOUS 0x18c  /* shifted prev key */
#define KEY_SPRINT    0x18d  /* shifted print key */
#define KEY_SREDO     0x18e  /* shifted redo key */
#define KEY_SREPLACE  0x18f  /* shifted replace key */
#define KEY_SRIGHT    0x190  /* shifted right arrow */
#define KEY_SRSUME    0x191  /* shifted resume key */
#define KEY_SSAVE     0x192  /* shifted save key */
#define KEY_SSUSPEND  0x193  /* shifted suspend key */
#define KEY_SUNDO     0x194  /* shifted undo key */
#define KEY_SUSPEND   0x195  /* suspend key */
#define KEY_UNDO      0x196  /* undo key */

/* PDCurses-specific key definitions -- PC only */

#define ALT_0         0x197
#define ALT_1         0x198
#define ALT_2         0x199
#define ALT_3         0x19a
#define ALT_4         0x19b
#define ALT_5         0x19c
#define ALT_6         0x19d
#define ALT_7         0x19e
#define ALT_8         0x19f
#define ALT_9         0x1a0
#define ALT_A         0x1a1
#define ALT_B         0x1a2
#define ALT_C         0x1a3
#define ALT_D         0x1a4
#define ALT_E         0x1a5
#define ALT_F         0x1a6
#define ALT_G         0x1a7
#define ALT_H         0x1a8
#define ALT_I         0x1a9
#define ALT_J         0x1aa
#define ALT_K         0x1ab
#define ALT_L         0x1ac
#define ALT_M         0x1ad
#define ALT_N         0x1ae
#define ALT_O         0x1af
#define ALT_P         0x1b0
#define ALT_Q         0x1b1
#define ALT_R         0x1b2
#define ALT_S         0x1b3
#define ALT_T         0x1b4
#define ALT_U         0x1b5
#define ALT_V         0x1b6
#define ALT_W         0x1b7
#define ALT_X         0x1b8
#define ALT_Y         0x1b9
#define ALT_Z         0x1ba

#define CTL_LEFT      0x1bb  /* Control-Left-Arrow */
#define CTL_RIGHT     0x1bc
#define CTL_PGUP      0x1bd
#define CTL_PGDN      0x1be
#define CTL_HOME      0x1bf
#define CTL_END       0x1c0

#define KEY_A1        0x1c1  /* upper left on Virtual keypad */
#define KEY_A2        0x1c2  /* upper middle on Virt. keypad */
#define KEY_A3        0x1c3  /* upper right on Vir. keypad */
#define KEY_B1        0x1c4  /* middle left on Virt. keypad */
#define KEY_B2        0x1c5  /* center on Virt. keypad */
#define KEY_B3        0x1c6  /* middle right on Vir. keypad */
#define KEY_C1        0x1c7  /* lower left on Virt. keypad */
#define KEY_C2        0x1c8  /* lower middle on Virt. keypad */
#define KEY_C3        0x1c9  /* lower right on Vir. keypad */

#define PADSLASH      0x1ca  /* slash on keypad */
#define PADENTER      0x1cb  /* enter on keypad */
#define CTL_PADENTER  0x1cc  /* ctl-enter on keypad */
#define ALT_PADENTER  0x1cd  /* alt-enter on keypad */
#define PADSTOP       0x1ce  /* stop on keypad */
#define PADSTAR       0x1cf  /* star on keypad */
#define PADMINUS      0x1d0  /* minus on keypad */
#define PADPLUS       0x1d1  /* plus on keypad */
#define CTL_PADSTOP   0x1d2  /* ctl-stop on keypad */
#define CTL_PADCENTER 0x1d3  /* ctl-enter on keypad */
#define CTL_PADPLUS   0x1d4  /* ctl-plus on keypad */
#define CTL_PADMINUS  0x1d5  /* ctl-minus on keypad */
#define CTL_PADSLASH  0x1d6  /* ctl-slash on keypad */
#define CTL_PADSTAR   0x1d7  /* ctl-star on keypad */
#define ALT_PADPLUS   0x1d8  /* alt-plus on keypad */
#define ALT_PADMINUS  0x1d9  /* alt-minus on keypad */
#define ALT_PADSLASH  0x1da  /* alt-slash on keypad */
#define ALT_PADSTAR   0x1db  /* alt-star on keypad */
#define ALT_PADSTOP   0x1dc  /* alt-stop on keypad */
#define CTL_INS       0x1dd  /* ctl-insert */
#define ALT_DEL       0x1de  /* alt-delete */
#define ALT_INS       0x1df  /* alt-insert */
#define CTL_UP        0x1e0  /* ctl-up arrow */
#define CTL_DOWN      0x1e1  /* ctl-down arrow */
#define CTL_TAB       0x1e2  /* ctl-tab */
#define ALT_TAB       0x1e3
#define ALT_MINUS     0x1e4
#define ALT_EQUAL     0x1e5
#define ALT_HOME      0x1e6
#define ALT_PGUP      0x1e7
#define ALT_PGDN      0x1e8
#define ALT_END       0x1e9
#define ALT_UP        0x1ea  /* alt-up arrow */
#define ALT_DOWN      0x1eb  /* alt-down arrow */
#define ALT_RIGHT     0x1ec  /* alt-right arrow */
#define ALT_LEFT      0x1ed  /* alt-left arrow */
#define ALT_ENTER     0x1ee  /* alt-enter */
#define ALT_ESC       0x1ef  /* alt-escape */
#define ALT_BQUOTE    0x1f0  /* alt-back quote */
#define ALT_LBRACKET  0x1f1  /* alt-left bracket */
#define ALT_RBRACKET  0x1f2  /* alt-right bracket */
#define ALT_SEMICOLON 0x1f3  /* alt-semi-colon */
#define ALT_FQUOTE    0x1f4  /* alt-forward quote */
#define ALT_COMMA     0x1f5  /* alt-comma */
#define ALT_STOP      0x1f6  /* alt-stop */
#define ALT_FSLASH    0x1f7  /* alt-forward slash */
#define ALT_BKSP      0x1f8  /* alt-backspace */
#define CTL_BKSP      0x1f9  /* ctl-backspace */
#define PAD0          0x1fa  /* keypad 0 */

#define CTL_PAD0      0x1fb  /* ctl-keypad 0 */
#define CTL_PAD1      0x1fc
#define CTL_PAD2      0x1fd
#define CTL_PAD3      0x1fe
#define CTL_PAD4      0x1ff
#define CTL_PAD5      0x200
#define CTL_PAD6      0x201
#define CTL_PAD7      0x202
#define CTL_PAD8      0x203
#define CTL_PAD9      0x204

#define ALT_PAD0      0x205  /* alt-keypad 0 */
#define ALT_PAD1      0x206
#define ALT_PAD2      0x207
#define ALT_PAD3      0x208
#define ALT_PAD4      0x209
#define ALT_PAD5      0x20a
#define ALT_PAD6      0x20b
#define ALT_PAD7      0x20c
#define ALT_PAD8      0x20d
#define ALT_PAD9      0x20e

#define CTL_DEL       0x20f  /* clt-delete */
#define ALT_BSLASH    0x210  /* alt-back slash */
#define CTL_ENTER     0x211  /* ctl-enter */

#define SHF_PADENTER  0x212  /* shift-enter on keypad */
#define SHF_PADSLASH  0x213  /* shift-slash on keypad */
#define SHF_PADSTAR   0x214  /* shift-star  on keypad */
#define SHF_PADPLUS   0x215  /* shift-plus  on keypad */
#define SHF_PADMINUS  0x216  /* shift-minus on keypad */
#define SHF_UP        0x217  /* shift-up on keypad */
#define SHF_DOWN      0x218  /* shift-down on keypad */
#define SHF_IC        0x219  /* shift-insert on keypad */
#define SHF_DC        0x21a  /* shift-delete on keypad */

#define KEY_MOUSE     0x21b  /* "mouse" key */
#define KEY_SHIFT_L   0x21c  /* Left-shift */
#define KEY_SHIFT_R   0x21d  /* Right-shift */
#define KEY_CONTROL_L 0x21e  /* Left-control */
#define KEY_CONTROL_R 0x21f  /* Right-control */
#define KEY_ALT_L     0x220  /* Left-alt */
#define KEY_ALT_R     0x221  /* Right-alt */
#define KEY_RESIZE    0x222  /* Window resize */
#define KEY_SUP       0x223  /* Shifted up arrow */
#define KEY_SDOWN     0x224  /* Shifted down arrow */

#define KEY_MIN       KEY_BREAK      /* Minimum curses key value */
#define KEY_MAX       KEY_SDOWN      /* Maximum curses key */

#define KEY_F(n)      (KEY_F0 + (n))

/**************************** Type Definitions *******************************/
enum
{
    FUSB_HID_SUBCLASS_NONE = 0,
    FUSB_HID_SUBCLASS_BOOT = 1
};

typedef enum
{
    FUSB_HID_PROTOCOL_BOOT = 0,
    FUSB_HID_PROTOCOL_REPORT = 1
} FUsbHidProtocol;

enum
{
    FUSB_HID_BOOT_PROTOCOL_NONE = 0,
    FUSB_HID_BOOT_PROTOCOL_KEYBOARD = 1,
    FUSB_HID_BOOT_PROTOCOL_MOUSE = 2
};

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/
/* USB HID的初始化函数，由应用程序注册到FUSB框架中 */
void FUsbHidInit(FUsbDev *dev);
int FUsbHidCheckInput(FUsbDev *dev, int times);

#ifdef __cplusplus
}
#endif


#endif
