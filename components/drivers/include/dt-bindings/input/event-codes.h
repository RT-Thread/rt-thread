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

#define EV_SYN                  0
#define EV_KEY                  1
#define EV_REL                  2
#define EV_ABS                  3
#define EV_MSC                  4
#define EV_SW                   5
#define EV_LED                  17
#define EV_SND                  18
#define EV_REP                  20
#define EV_FF                   21
#define EV_PWR                  22
#define EV_FF_STATUS            23
#define EV_MAX                  31
#define EV_CNT                  (EV_MAX + 1)

/*
 * Synchronization events.
 */

#define SYN_REPORT              0
#define SYN_CONFIG              1
#define SYN_MT_REPORT           2
#define SYN_DROPPED             3
#define SYN_MAX                 15
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
#define KEY_STOP                128 /* AC Stop */
#define KEY_MENU                139 /* Menu Key */
#define KEY_SETUP               141
#define KEY_SLEEP               142 /* System Sleep Key */
#define KEY_WAKEUP              143 /* System Wake Up Key */
#define KEY_COFFEE              152 /* Screen Saver Key */
#define KEY_BACK                158 /* Back Key */
#define KEY_FORWARD             159 /* Forward Key */
#define KEY_PLAYPAUSE           164
#define KEY_RECORD              167
#define KEY_REWIND              168
#define KEY_EXIT                174 /* AC Exit */
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
#define KEY_CANCEL              223 /* AC Cancel */
#define KEY_BRIGHTNESSDOWN      224 /* Brightness Down Key */
#define KEY_BRIGHTNESSUP        225 /* Brightneess Up Key */
#define KEY_MEDIA               226 /* Media toggle */
#define KEY_BLUETOOTH           237 /* Bluetooth Key */
#define KEY_WLAN                238 /* Wireless LAN Key */
#define KEY_UWB                 239 /* Ultra-Wideband Key */
#define KEY_SELECT              353
#define KEY_CLEAR               355
#define KEY_INFO                358 /* AL OEM Features/Tips/Tutorial */
#define KEY_PROGRAM             362 /* Media Select Program Guide */
#define KEY_CALENDAR            397
#define KEY_RED                 398
#define KEY_GREEN               399
#define KEY_YELLOW              400
#define KEY_BLUE                401
#define KEY_CHANNELUP           402 /* Channel Increment */
#define KEY_CHANNELDOWN         403 /* Channel Decrement */
#define KEY_RESTART             408 /* Restart Key */

#define BTN_MISC                256
#define BTN_0                   256
#define BTN_1                   257
#define BTN_2                   258
#define BTN_3                   259
#define BTN_4                   260
#define BTN_5                   261
#define BTN_6                   262
#define BTN_7                   263
#define BTN_8                   264
#define BTN_9                   265

#define BTN_MOUSE               272
#define BTN_LEFT                272
#define BTN_RIGHT               273
#define BTN_MIDDLE              274
#define BTN_SIDE                275
#define BTN_EXTRA               276
#define BTN_FORWARD             277
#define BTN_BACK                278
#define BTN_TASK                279

#define BTN_JOYSTICK            288
#define BTN_TRIGGER             288
#define BTN_THUMB               289
#define BTN_THUMB2              290
#define BTN_TOP                 291
#define BTN_TOP2                292
#define BTN_PINKIE              293
#define BTN_BASE                294
#define BTN_BASE2               295
#define BTN_BASE3               296
#define BTN_BASE4               297
#define BTN_BASE5               298
#define BTN_BASE6               299
#define BTN_DEAD                303

#define BTN_GAMEPAD             304
#define BTN_SOUTH               304
#define BTN_A                   BTN_SOUTH
#define BTN_EAST                305
#define BTN_B                   BTN_EAST
#define BTN_C                   306
#define BTN_NORTH               307
#define BTN_X                   BTN_NORTH
#define BTN_WEST                308
#define BTN_Y                   BTN_WEST
#define BTN_Z                   309
#define BTN_TL                  310
#define BTN_TR                  311
#define BTN_TL2                 312
#define BTN_TR2                 313
#define BTN_SELECT              314
#define BTN_START               315
#define BTN_MODE                316
#define BTN_THUMBL              317
#define BTN_THUMBR              318

#define BTN_DIGI                320
#define BTN_TOOL_PEN            320
#define BTN_TOOL_RUBBER         321
#define BTN_TOOL_BRUSH          322
#define BTN_TOOL_PENCIL         323
#define BTN_TOOL_AIRBRUSH       324
#define BTN_TOOL_FINGER         325
#define BTN_TOOL_MOUSE          326
#define BTN_TOOL_LENS           327
#define BTN_TOOL_QUINTTAP       328 /* Five fingers on trackpad */
#define BTN_STYLUS3             329
#define BTN_TOUCH               330
#define BTN_STYLUS              331
#define BTN_STYLUS2             332
#define BTN_TOOL_DOUBLETAP      333
#define BTN_TOOL_TRIPLETAP      334
#define BTN_TOOL_QUADTAP        335 /* Four fingers on trackpad */

#define KEY_MAX                 767
#define KEY_CNT                 (KEY_MAX + 1)

#define BTN_TOUCH               330

/*
 * Relative axes
 */

#define REL_X                   0
#define REL_Y                   1
#define REL_Z                   2
#define REL_RX                  3
#define REL_RY                  4
#define REL_RZ                  5
#define REL_HWHEEL              6
#define REL_DIAL                7
#define REL_WHEEL               8
#define REL_MISC                9
#define REL_RESERVED            10
#define REL_WHEEL_HI_RES        11
#define REL_HWHEEL_HI_RES       12
#define REL_MAX                 15
#define REL_CNT                 (REL_MAX + 1)

/*
 * Absolute axes
 */

#define ABS_X                   0
#define ABS_Y                   1
#define ABS_Z                   2
#define ABS_RX                  3
#define ABS_RY                  4
#define ABS_RZ                  5
#define ABS_THROTTLE            6
#define ABS_RUDDER              7
#define ABS_WHEEL               8
#define ABS_GAS                 9
#define ABS_BRAKE               10
#define ABS_HAT0X               16
#define ABS_HAT0Y               17
#define ABS_HAT1X               18
#define ABS_HAT1Y               19
#define ABS_HAT2X               20
#define ABS_HAT2Y               21
#define ABS_HAT3X               22
#define ABS_HAT3Y               23
#define ABS_PRESSURE            24
#define ABS_DISTANCE            25
#define ABS_TILT_X              26
#define ABS_TILT_Y              27
#define ABS_TOOL_WIDTH          28

#define ABS_VOLUME              32
#define ABS_PROFILE             33

#define ABS_MISC                40
#define ABS_RESERVED            46

#define ABS_MT_SLOT             47      /* MT slot being modified */
#define ABS_MT_TOUCH_MAJOR      48      /* Major axis of touching ellipse */
#define ABS_MT_TOUCH_MINOR      49      /* Minor axis (omit if circular) */
#define ABS_MT_WIDTH_MAJOR      50      /* Major axis of approaching ellipse */
#define ABS_MT_WIDTH_MINOR      51      /* Minor axis (omit if circular) */
#define ABS_MT_ORIENTATION      52      /* Ellipse orientation */
#define ABS_MT_POSITION_X       53      /* Center X touch position */
#define ABS_MT_POSITION_Y       54      /* Center Y touch position */
#define ABS_MT_TOOL_TYPE        55      /* Type of touching device */
#define ABS_MT_BLOB_ID          56      /* Group a set of packets as a blob */
#define ABS_MT_TRACKING_ID      57      /* Unique ID of initiated contact */
#define ABS_MT_PRESSURE         58      /* Pressure on contact area */
#define ABS_MT_DISTANCE         59      /* Contact hover distance */
#define ABS_MT_TOOL_X           60      /* Center X tool position */
#define ABS_MT_TOOL_Y           61      /* Center Y tool position */

#define ABS_MAX                 63
#define ABS_CNT                 (ABS_MAX + 1)

#endif /* __DT_BINDINGS_INPUT_EVENT_CODES_H__ */
