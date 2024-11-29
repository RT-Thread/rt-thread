/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __DT_BINDINGS_INPUT_EVENT_CODES_H__
#define __DT_BINDINGS_INPUT_EVENT_CODES_H__

/*
 * Event types
 */

#define EV_SYN                  0x00
#define EV_KEY                  0x01
#define EV_REL                  0x02
#define EV_ABS                  0x03
#define EV_MSC                  0x04
#define EV_SW                   0x05
#define EV_LED                  0x11
#define EV_SND                  0x12
#define EV_REP                  0x14
#define EV_FF                   0x15
#define EV_PWR                  0x16
#define EV_FF_STATUS            0x17
#define EV_MAX                  0x1f
#define EV_CNT                  (EV_MAX + 1)

/*
 * Synchronization events.
 */

#define SYN_REPORT              0
#define SYN_CONFIG              1
#define SYN_MT_REPORT           2
#define SYN_DROPPED             3
#define SYN_MAX                 0xf
#define SYN_CNT                 (SYN_MAX + 1)

/*
 * Keys and buttons
 */

#define KEY_RESERVED            0   /* Reserved, do not use */
#define KEY_ESC                 1   /* Escape Key */
#define KEY_1                   2   /* 1 Key */
#define KEY_2                   3   /* 2 Key */
#define KEY_3                   4   /* 3 Key */
#define KEY_4                   5   /* 4 Key */
#define KEY_5                   6   /* 5 Key */
#define KEY_6                   7   /* 6 Key */
#define KEY_7                   8   /* 7 Key */
#define KEY_8                   9   /* 8 Key */
#define KEY_9                   10  /* 9 Key */
#define KEY_0                   11  /* 0 Key */
#define KEY_MINUS               12  /* Minus Key */
#define KEY_EQUAL               13  /* Equal Key */
#define KEY_BACKSPACE           14  /* Backspace Key */
#define KEY_TAB                 15  /* Tab Key*/
#define KEY_Q                   16  /* Q Key */
#define KEY_W                   17  /* W Key */
#define KEY_E                   18  /* E Key */
#define KEY_R                   19  /* R Key */
#define KEY_T                   20  /* T Key */
#define KEY_Y                   21  /* Y Key */
#define KEY_U                   22  /* U Key */
#define KEY_I                   23  /* I Key */
#define KEY_O                   24  /* O Key */
#define KEY_P                   25  /* P Key */
#define KEY_LEFTBRACE           26  /* Left Brace Key */
#define KEY_RIGHTBRACE          27  /* Right Brace Key */
#define KEY_ENTER               28  /* Enter Key */
#define KEY_LEFTCTRL            29  /* Left Ctrl Key */
#define KEY_A                   30  /* A Key */
#define KEY_S                   31  /* S Key */
#define KEY_D                   32  /* D Key */
#define KEY_F                   33  /* F Key */
#define KEY_G                   34  /* G Key */
#define KEY_H                   35  /* H Key */
#define KEY_J                   36  /* J Key */
#define KEY_K                   37  /* K Key */
#define KEY_L                   38  /* L Key */
#define KEY_SEMICOLON           39  /* Semicolon Key */
#define KEY_APOSTROPHE          40  /* Apostrophe Key */
#define KEY_GRAVE               41  /* Grave (backtick) Key */
#define KEY_LEFTSHIFT           42  /* Left Shift Key */
#define KEY_BACKSLASH           43  /* Backslash Key */
#define KEY_Z                   44  /* Z Key */
#define KEY_X                   45  /* X Key */
#define KEY_C                   46  /* C Key */
#define KEY_V                   47  /* V Key */
#define KEY_B                   48  /* B Key */
#define KEY_N                   49  /* N Key */
#define KEY_M                   50  /* M Key */
#define KEY_COMMA               51  /* Comma Key */
#define KEY_DOT                 52  /* Dot Key */
#define KEY_SLASH               53  /* Slash Key */
#define KEY_RIGHTSHIFT          54  /* Right Shift Key */
#define KEY_KPASTERISK          55  /* Keypad Asterisk Key */
#define KEY_LEFTALT             56  /* Left Alt Key */
#define KEY_SPACE               57  /* Space Key */
#define KEY_CAPSLOCK            58  /* Caps Lock Key */
#define KEY_F1                  59  /* F1 Key */
#define KEY_F2                  60  /* F2 Key */
#define KEY_F3                  61  /* F3 Key */
#define KEY_F4                  62  /* F4 Key */
#define KEY_F5                  63  /* F5 Key */
#define KEY_F6                  64  /* F6 Key */
#define KEY_F7                  65  /* F7 Key */
#define KEY_F8                  66  /* F8 Key */
#define KEY_F9                  67  /* F9 Key */
#define KEY_F10                 68  /* F10 Key */
#define KEY_NUMLOCK             69  /* Num Lock Key */
#define KEY_SCROLLLOCK          70  /* Scroll Lock Key */
#define KEY_KP7                 71  /* Keypad 7 Key */
#define KEY_KP8                 72  /* Keypad 8 Key */
#define KEY_KP9                 73  /* Keypad 9 Key */
#define KEY_KPMINUS             74  /* Keypad Minus Key */
#define KEY_KP4                 75  /* Keypad 4 Key */
#define KEY_KP5                 76  /* Keypad 5 Key */
#define KEY_KP6                 77  /* Keypad 6 Key */
#define KEY_KPPLUS              78  /* Keypad Plus Key */
#define KEY_KP1                 79  /* Keypad 1 Key */
#define KEY_KP2                 80  /* Keypad 2 Key */
#define KEY_KP3                 81  /* Keypad 3 Key */
#define KEY_KP0                 82  /* Keypad 0 Key */
#define KEY_KPDOT               83  /* Keypad Dot Key */
#define KEY_F11                 87  /* F11 Key */
#define KEY_F12                 88  /* F12 Key */
#define KEY_KPENTER             96  /* Keypad Enter Key */
#define KEY_RIGHTCTRL           97  /* Right Ctrl Key */
#define KEY_KPSLASH             98  /* Keypad Slash Key */
#define KEY_SYSRQ               99  /* SysReq Key */
#define KEY_RIGHTALT            100 /* Right Alt Key */
#define KEY_HOME                102 /* Home Key */
#define KEY_UP                  103 /* Up Key */
#define KEY_PAGEUP              104 /* Page UpKey */
#define KEY_LEFT                105 /* Left Key */
#define KEY_RIGHT               106 /* Right Key */
#define KEY_END                 107 /* End Key */
#define KEY_DOWN                108 /* Down Key */
#define KEY_PAGEDOWN            109 /* Page Down Key */
#define KEY_INSERT              110 /* Insert Key */
#define KEY_DELETE              111 /* Delete Key */
#define KEY_MUTE                113 /* Mute Key */
#define KEY_VOLUMEDOWN          114 /* Volume Down Key */
#define KEY_VOLUMEUP            115 /* Volume Up Key */
#define KEY_POWER               116 /* Power Key */
#define KEY_KPEQUAL             117 /* Keypad Equal Key */
#define KEY_KPPLUSMINUS         118 /* Keypad Plus Key */
#define KEY_PAUSE               119 /* Pause Key */
#define KEY_SCALE               120 /* Scale Key */
#define KEY_KPCOMMA             121 /* Keypad Comma Key */
#define KEY_LEFTMETA            125 /* Left Meta Key */
#define KEY_RIGHTMETA           126 /* Right Meta Key */
#define KEY_COMPOSE             127 /* Compose Key */
#define KEY_MENU                139 /* Menu Key */
#define KEY_SLEEP               142 /* System Sleep Key */
#define KEY_WAKEUP              143 /* System Wake Up Key */
#define KEY_COFFEE              152 /* Screen Saver Key */
#define KEY_BACK                158 /* Back Key */
#define KEY_FORWARD             159 /* Forward Key */
#define KEY_F13                 183 /* F13 Key */
#define KEY_F14                 184 /* F14 Key */
#define KEY_F15                 185 /* F15 Key */
#define KEY_F16                 186 /* F16 Key */
#define KEY_F17                 187 /* F17 Key */
#define KEY_F18                 188 /* F18 Key */
#define KEY_F19                 189 /* F19 Key */
#define KEY_F20                 190 /* F20 Key */
#define KEY_F21                 191 /* F21 Key */
#define KEY_F22                 192 /* F22 Key */
#define KEY_F23                 193 /* F23 Key */
#define KEY_F24                 194 /* F24 Key */
#define KEY_PLAY                207 /* Play Key */
#define KEY_FASTFORWARD         208 /* Fast Forward Key */
#define KEY_PRINT               210 /* Print Key */
#define KEY_CONNECT             218 /* Connect Key */
#define KEY_BRIGHTNESSDOWN      224 /* Brightness Up Key */
#define KEY_BRIGHTNESSUP        225 /* Brightneess Down Key */
#define KEY_MEDIA               226 /* Media toggle */
#define KEY_BLUETOOTH           237 /* Bluetooth Key */
#define KEY_WLAN                238 /* Wireless LAN Key */
#define KEY_UWB                 239 /* Ultra-Wideband Key */
#define KEY_RESTART             408 /* Restart Key */

#define KEY_MAX                 0x2ff
#define KEY_CNT                 (KEY_MAX + 1)

/*
 * Relative axes
 */

#define REL_X                   0x00
#define REL_Y                   0x01
#define REL_Z                   0x02
#define REL_RX                  0x03
#define REL_RY                  0x04
#define REL_RZ                  0x05
#define REL_HWHEEL              0x06
#define REL_DIAL                0x07
#define REL_WHEEL               0x08
#define REL_MISC                0x09
#define REL_RESERVED            0x0a
#define REL_WHEEL_HI_RES        0x0b
#define REL_HWHEEL_HI_RES       0x0c
#define REL_MAX                 0x0f
#define REL_CNT                 (REL_MAX + 1)

/*
 * Absolute axes
 */

#define ABS_X                   0x00
#define ABS_Y                   0x01
#define ABS_Z                   0x02
#define ABS_RX                  0x03
#define ABS_RY                  0x04
#define ABS_RZ                  0x05
#define ABS_THROTTLE            0x06
#define ABS_RUDDER              0x07
#define ABS_WHEEL               0x08
#define ABS_GAS                 0x09
#define ABS_BRAKE               0x0a
#define ABS_HAT0X               0x10
#define ABS_HAT0Y               0x11
#define ABS_HAT1X               0x12
#define ABS_HAT1Y               0x13
#define ABS_HAT2X               0x14
#define ABS_HAT2Y               0x15
#define ABS_HAT3X               0x16
#define ABS_HAT3Y               0x17
#define ABS_PRESSURE            0x18
#define ABS_DISTANCE            0x19
#define ABS_TILT_X              0x1a
#define ABS_TILT_Y              0x1b
#define ABS_TOOL_WIDTH          0x1c

#define ABS_VOLUME              0x20
#define ABS_PROFILE             0x21

#define ABS_MISC                0x28
#define ABS_RESERVED            0x2e

#define ABS_MT_SLOT             0x2f    /* MT slot being modified */
#define ABS_MT_TOUCH_MAJOR      0x30    /* Major axis of touching ellipse */
#define ABS_MT_TOUCH_MINOR      0x31    /* Minor axis (omit if circular) */
#define ABS_MT_WIDTH_MAJOR      0x32    /* Major axis of approaching ellipse */
#define ABS_MT_WIDTH_MINOR      0x33    /* Minor axis (omit if circular) */
#define ABS_MT_ORIENTATION      0x34    /* Ellipse orientation */
#define ABS_MT_POSITION_X       0x35    /* Center X touch position */
#define ABS_MT_POSITION_Y       0x36    /* Center Y touch position */
#define ABS_MT_TOOL_TYPE        0x37    /* Type of touching device */
#define ABS_MT_BLOB_ID          0x38    /* Group a set of packets as a blob */
#define ABS_MT_TRACKING_ID      0x39    /* Unique ID of initiated contact */
#define ABS_MT_PRESSURE         0x3a    /* Pressure on contact area */
#define ABS_MT_DISTANCE         0x3b    /* Contact hover distance */
#define ABS_MT_TOOL_X           0x3c    /* Center X tool position */
#define ABS_MT_TOOL_Y           0x3d    /* Center Y tool position */

#define ABS_MAX                 0x3f
#define ABS_CNT                 (ABS_MAX + 1)

#endif /* __DT_BINDINGS_INPUT_EVENT_CODES_H__ */
