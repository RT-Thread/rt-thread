/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USB_HID_H
#define USB_HID_H

/* Subclass codes (HID 4.2) */
#define HID_SUBCLASS_NONE   0 /* No subclass */
#define HID_SUBCLASS_BOOTIF 1 /* Boot Interface Subclass */

/* HID Protocol Codes (HID 4.3) */
#define HID_PROTOCOL_NONE     0x00
#define HID_PROTOCOL_BOOT     0x00
#define HID_PROTOCOL_KEYBOARD 0x01
#define HID_PROTOCOL_REPORT   0x01
#define HID_PROTOCOL_MOUSE    0x02

/* HID Class Descriptor Types (HID 7.1) */
#define HID_DESCRIPTOR_TYPE_HID          0x21
#define HID_DESCRIPTOR_TYPE_HID_REPORT   0x22
#define HID_DESCRIPTOR_TYPE_HID_PHYSICAL 0x23

/* HID Class Specific Requests (HID 7.2) */
#define HID_REQUEST_GET_REPORT   0x01
#define HID_REQUEST_GET_IDLE     0x02
#define HID_REQUEST_GET_PROTOCOL 0x03
#define HID_REQUEST_SET_REPORT   0x09
#define HID_REQUEST_SET_IDLE     0x0A
#define HID_REQUEST_SET_PROTOCOL 0x0B

/* Report Type (MS byte of wValue for GET_REPORT) (HID 7.2.1) */
#define HID_REPORT_INPUT   0x01
#define HID_REPORT_OUTPUT  0x02
#define HID_REPORT_FEATURE 0x03

/* HID Descriptor ***********************************************************/

#define HID_COUNTRY_NONE        0x00 /* Not Supported */
#define HID_COUNTRY_ARABIC      0x01 /* Arabic */
#define HID_COUNTRY_BELGIAN     0x02 /* Belgian */
#define HID_COUNTRY_CANADA      0x03 /* Canadian-Bilingual */
#define HID_COUNTRY_CANADRFR    0x04 /* Canadian-French */
#define HID_COUNTRY_CZECH       0x05 /* Czech Republic */
#define HID_COUNTRY_DANISH      0x06 /* Danish */
#define HID_COUNTRY_FINNISH     0x07 /* Finnish */
#define HID_COUNTRY_FRENCH      0x08 /* French */
#define HID_COUNTRY_GERMAN      0x09 /* German */
#define HID_COUNTRY_GREEK       0x10 /* Greek */
#define HID_COUNTRY_HEBREW      0x11 /* Hebrew */
#define HID_COUNTRY_HUNGARY     0x12 /* Hungary */
#define HID_COUNTRY_ISO         0x13 /* International (ISO) */
#define HID_COUNTRY_ITALIAN     0x14 /* Italian */
#define HID_COUNTRY_JAPAN       0x15 /* Japan (Katakana) */
#define HID_COUNTRY_KOREAN      0x16 /* Korean  */
#define HID_COUNTRY_LATINAM     0x17 /* Latin American */
#define HID_COUNTRY_DUTCH       0x18 /* Netherlands/Dutch */
#define HID_COUNTRY_NORWEGIAN   0x19 /* Norwegian */
#define HID_COUNTRY_PERSIAN     0x20 /* Persian (Farsi) */
#define HID_COUNTRY_POLAND      0x21 /* Poland */
#define HID_COUNTRY_PORTUGUESE  0x22 /* Portuguese */
#define HID_COUNTRY_RUSSIA      0x23 /* Russia */
#define HID_COUNTRY_SLOVAKIA    0x24 /* Slovakia */
#define HID_COUNTRY_SPANISH     0x25 /* Spanish */
#define HID_COUNTRY_SWEDISH     0x26 /* Swedish */
#define HID_COUNTRY_SWISSFR     0x27 /* Swiss/French */
#define HID_COUNTRY_SWISSGR     0x28 /* Swiss/German */
#define HID_COUNTRY_SWITZERLAND 0x29 /* Switzerland */
#define HID_COUNTRY_TAIWAN      0x30 /* Taiwan */
#define HID_COUNTRY_TURKISHQ    0x31 /* Turkish-Q */
#define HID_COUNTRY_UK          0x32 /* UK */
#define HID_COUNTRY_US          0x33 /* US */
#define HID_COUNTRY_YUGOSLAVIA  0x34 /* Yugoslavia */
#define HID_COUNTRY_TURKISHF    0x35 /* Turkish-F */

/* HID report items */
#define HID_REPORT_ITEM_SIZE_MASK   0x03
#define HID_REPORT_ITEM_SIZE_0      0x00 /* No data follows */
#define HID_REPORT_ITEM_SIZE_1      0x01 /* 1 byte of data follows */
#define HID_REPORT_ITEM_SIZE_2      0x02 /* 2 bytes of data follow */
#define HID_REPORT_ITEM_SIZE_4      0x03 /* 4 bytes of data follow */
#define HID_REPORT_ITEM_TYPE_MASK   0x0c
#define HID_REPORT_ITEM_TYPE_MAIN   0x00
#define HID_REPORT_ITEM_TYPE_GLOBAL 0x04
#define HID_REPORT_ITEM_TYPE_LOCAL  0x08
#define HID_REPORT_ITEM_TAG_MASK    0xf0

/* Main Items (HID 6.2.2.4) */
#define HID_MAIN_ITEM_CONSTANT      (1 << 0) /* Constant(1) vs Data(0) */
#define HID_MAIN_ITEM_VARIABLE      (1 << 1) /* Variable(1) vs Array(0) */
#define HID_MAIN_ITEM_RELATIVE      (1 << 2) /* Relative(1) vs Absolute(0) */
#define HID_MAIN_ITEM_WRAP          (1 << 3) /* Wrap(1) vs No Wrap(0) */
#define HID_MAIN_ITEM_NONLINEAR     (1 << 4) /* Non Linear(1) vs Linear(0) */
#define HID_MAIN_ITEM_NOPREFERRED   (1 << 5) /* No Preferred (1) vs Preferred State(0) */
#define HID_MAIN_ITEM_NULLSTATE     (1 << 6) /* Null state(1) vs No Null position(0) */
#define HID_MAIN_ITEM_VOLATILE      (1 << 7) /* Volatile(1) vs Non volatile(0) */
#define HID_MAIN_ITEM_BUFFEREDBYTES (1 << 8) /* Buffered Bytes(1) vs Bit Field(0) */

#define HID_MAIN_ITEM_SIZE(pfx)           ((pfx)&HID_REPORT_ITEM_SIZE_MASK)
#define HID_MAIN_ITEM_INPUT_PREFIX        0x80
#define HID_MAIN_ITEM_INPUT_CONSTANT      HID_MAIN_ITEM_CONSTANT
#define HID_MAIN_ITEM_INPUT_VARIABLE      HID_MAIN_ITEM_VARIABLE
#define HID_MAIN_ITEM_INPUT_RELATIVE      HID_MAIN_ITEM_RELATIVE
#define HID_MAIN_ITEM_INPUT_WRAP          HID_MAIN_ITEM_WRAP
#define HID_MAIN_ITEM_INPUT_NONLINEAR     HID_MAIN_ITEM_NONLINEAR
#define HID_MAIN_ITEM_INPUT_NOPREFERRED   HID_MAIN_ITEM_NOPREFERRED
#define HID_MAIN_ITEM_INPUT_NULLSTATE     HID_MAIN_ITEM_NULLSTATE
#define HID_MAIN_ITEM_INPUT_BUFFEREDBYTES HID_MAIN_ITEM_BUFFEREDBYTES

#define HID_MAIN_ITEM_OUTPUT_PREFIX        0x90
#define HID_MAIN_ITEM_OUTPUT_CONSTANT      HID_MAIN_ITEM_CONSTANT
#define HID_MAIN_ITEM_OUTPUT_VARIABLE      HID_MAIN_ITEM_VARIABLE
#define HID_MAIN_ITEM_OUTPUT_RELATIVE      HID_MAIN_ITEM_RELATIVE
#define HID_MAIN_ITEM_OUTPUT_WRAP          HID_MAIN_ITEM_WRAP
#define HID_MAIN_ITEM_OUTPUT_NONLINEAR     HID_MAIN_ITEM_NONLINEAR
#define HID_MAIN_ITEM_OUTPUT_NOPREFERRED   HID_MAIN_ITEM_NOPREFERRED
#define HID_MAIN_ITEM_OUTPUT_NULLSTATE     HID_MAIN_ITEM_NULLSTATE
#define HID_MAIN_ITEM_OUTPUT_VOLATILE      HID_MAIN_ITEM_VOLATILE
#define HID_MAIN_ITEM_OUTPUT_BUFFEREDBYTES HID_MAIN_ITEM_BUFFEREDBYTES

#define HID_MAIN_ITEM_FEATURE_PREFIX        0xb0
#define HID_MAIN_ITEM_FEATURE_CONSTANT      HID_MAIN_ITEM_CONSTANT
#define HID_MAIN_ITEM_FEATURE_VARIABLE      HID_MAIN_ITEM_VARIABLE
#define HID_MAIN_ITEM_FEATURE_RELATIVE      HID_MAIN_ITEM_RELATIVE
#define HID_MAIN_ITEM_FEATURE_WRAP          HID_MAIN_ITEM_WRAP
#define HID_MAIN_ITEM_FEATURE_NONLINEAR     HID_MAIN_ITEM_NONLINEAR
#define HID_MAIN_ITEM_FEATURE_NOPREFERRED   HID_MAIN_ITEM_NOPREFERRED
#define HID_MAIN_ITEM_FEATURE_NULLSTATE     HID_MAIN_ITEM_NULLSTATE
#define HID_MAIN_ITEM_FEATURE_VOLATILE      HID_MAIN_ITEM_VOLATILE
#define HID_MAIN_ITEM_FEATURE_BUFFEREDBYTES HID_MAIN_ITEM_BUFFEREDBYTES

#define HID_MAIN_ITEM_COLLECTION_PREFIX    0xa0
#define HID_MAIN_ITEM_COLLECTION_PHYSICAL  0x00 /* Physical (group of axes) */
#define HID_MAIN_ITEM_COLLECTION_APPL      0x01 /* Application (mouse, keyboard) */
#define HID_MAIN_ITEM_COLLECTION_LOGICAL   0x02 /* Logical (interrelated data) */
#define HID_MAIN_ITEM_COLLECTION_REPORT    0x03 /* Report */
#define HID_MAIN_ITEM_COLLECTION_ARRAY     0x04 /* Named Array */
#define HID_MAIN_ITEM_COLLECTION_SWITCH    0x05 /* Usage Switch */
#define HID_MAIN_ITEM_COLLECTION_MODIFIER  0x06 /* Usage Modifier */
#define HID_MAIN_ITEM_ENDCOLLECTION_PREFIX 0xc0

/* Global Items (HID 6.2.2.7) */
#define HID_GLOBAL_ITEM_SIZE(pfx)          ((pfx)&HID_REPORT_ITEM_SIZE_MASK)
#define HID_GLOBAL_ITEM_USAGEPAGE_PREFIX   0x04 /* Usage Page */
#define HID_GLOBAL_ITEM_LOGICALMIN_PREFIX  0x14 /* Logical Minimum */
#define HID_GLOBAL_ITEM_LOGICALMAX_PREFIX  0x24 /* Logical Maximum */
#define HID_GLOBAL_ITEM_PHYSICALMIN_PREFIX 0x34 /* Physical Minimum */
#define HID_GLOBAL_ITEM_PHYSMICALAX_PREFIX 0x44 /* Physical Maximum */
#define HID_GLOBAL_ITEM_UNITEXP_PREFIX     0x54 /* Unit Exponent */
#define HID_GLOBAL_ITEM_UNIT_PREFIX        0x64 /* Unit */
#define HID_GLOBAL_ITEM_REPORTSIZE_PREFIX  0x74 /* Report Size */
#define HID_GLOBAL_ITEM_REPORTID_PREFIX    0x84 /* Report ID */
#define HID_GLOBAL_ITEM_REPORTCOUNT_PREFIX 0x94 /* Report Count */
#define HID_GLOBAL_ITEM_PUSH_PREFIX        0xa4 /* Push */
#define HID_GLOBAL_ITEM_POP_PREFIX         0xb4 /* Pop */

/* Local Items (HID 6.2.2.8) */
#define HID_LOCAL_ITEM_SIZE(pfx)            ((pfx)&HID_REPORT_ITEM_SIZE_MASK)
#define HID_LOCAL_ITEM_USAGE_PREFIX         0x08 /* Usage */
#define HID_LOCAL_ITEM_USAGEMIN_PREFIX      0x18 /* Usage Minimum */
#define HID_LOCAL_ITEM_USAGEMAX_PREFIX      0x28 /* Usage Maximum */
#define HID_LOCAL_ITEM_DESIGNATORIDX_PREFIX 0x38 /* Designator Index  */
#define HID_LOCAL_ITEM_DESIGNATORMIN_PREFIX 0x48 /* Designator Minimum */
#define HID_LOCAL_ITEM_DESIGNATORMAX_PREFIX 0x58 /* Designator Maximum */
#define HID_LOCAL_ITEM_STRINGIDX_PREFIX     0x78 /* String Index */
#define HID_LOCAL_ITEM_STRINGMIN_PREFIX     0x88 /* String Minimum */
#define HID_LOCAL_ITEM_STRINGMAX_PREFIX     0x98 /* xx */
#define HID_LOCAL_ITEM_DELIMITER_PREFIX     0xa8 /* Delimiter */

/* Modifier Keys (HID 8.3) */
#define HID_MODIFER_LCTRL  (1 << 0) /* Left Ctrl */
#define HID_MODIFER_LSHIFT (1 << 1) /* Left Shift */
#define HID_MODIFER_LALT   (1 << 2) /* Left Alt */
#define HID_MODIFER_LGUI   (1 << 3) /* Left GUI */
#define HID_MODIFER_RCTRL  (1 << 4) /* Right Ctrl */
#define HID_MODIFER_RSHIFT (1 << 5) /* Right Shift */
#define HID_MODIFER_RALT   (1 << 6) /* Right Alt */
#define HID_MODIFER_RGUI   (1 << 7) /* Right GUI */

/* Keyboard output report (1 byte) (HID B.1) */
#define HID_KBD_OUTPUT_REPORT_NUMLOCK    (1 << 0)
#define HID_KBD_OUTPUT_REPORT_CAPSLOCK   (1 << 1)
#define HID_KBD_OUTPUT_REPORT_SCROLLLOCK (1 << 2)
#define HID_KBD_OUTPUT_REPORT_COMPOSE    (1 << 3)
#define HID_KBD_OUTPUT_REPORT_KANA       (1 << 4)

/* Mouse input report (HID B.2) */
#define HID_MOUSE_INPUT_REPORT_BUTTON1     (1 << 0)
#define HID_MOUSE_INPUT_REPORT_BUTTON2     (1 << 1)
#define HID_MOUSE_INPUT_REPORT_BUTTON3     (1 << 2)
#define HID_MOUSE_INPUT_REPORT_BUTTON_MASK (7)

#define HID_MOUSE_INPUT_BUTTON_LEFT        (1 << 0)
#define HID_MOUSE_INPUT_BUTTON_RIGHT       (1 << 1)
#define HID_MOUSE_INPUT_BUTTON_MIDDLE      (1 << 2)
#define HID_MOUSE_INPUT_BUTTON_BACKWARD    (1 << 3)
#define HID_MOUSE_INPUT_BUTTON_FORWARD     (1 << 4)

/* Joystick input report (4 bytes) (HID D.1) */
#define HID_JS_INPUT_REPORT_HATSWITCH_SHIFT (0)
#define HID_JS_INPUT_REPORT_HATSWITCH_MASK  (15 << HID_JSIN_HATSWITCH_SHIFT)
#define HID_JS_INPUT_REPORT_BUTTON1         (1 << 4)
#define HID_JS_INPUT_REPORT_BUTTON2         (1 << 5)
#define HID_JS_INPUT_REPORT_BUTTON3         (1 << 6)
#define HID_JS_INPUT_REPORT_BUTTON4         (1 << 7)

/* Usage pages (HuT 3) */
#define HID_USAGE_PAGE_UNDEFINED       0x00 /* Undefined */
#define HID_USAGE_PAGE_GENERIC_DCTRL   0x01 /* Generic Desktop Controls */
#define HID_USAGE_PAGE_SIMCTRL         0x02 /* Simulation Controls */
#define HID_USAGE_PAGE_VRCTRL          0x03 /* VR Controls */
#define HID_USAGE_PAGE_SPORTCTRL       0x04 /* Sport Controls */
#define HID_USAGE_PAGE_GAMECTRL        0x05 /* Game Controls */
#define HID_USAGE_PAGE_GENERIC_DEVCTRL 0x06 /* Generic Device Controls */
#define HID_USAGE_PAGE_KBD             0x07 /* Keyboard/Keypad */
#define HID_USAGE_PAGE_LEDS            0x08 /* LEDs */
#define HID_USAGE_PAGE_BUTTON          0x09 /* Button */
#define HID_USAGE_PAGE_ORDINAL         0x0a /* Ordinal */
#define HID_USAGE_PAGE_TELEPHONY       0x0b /* Telephony */
#define HID_USAGE_PAGE_CONSUMER        0x0c /* Consumer */
#define HID_USAGE_PAGE_DIGITIZER       0x0d /* Digitizer */
                                            /* 0x0e Reserved */
#define HID_USAGE_PAGE_PIDPAGE 0x0f         /* PID Page  Physical Interface Device */
#define HID_USAGE_PAGE_UNICODE 0x10         /* Unicode */
                                            /* 0x11-13 Reserved */
#define HID_USAGE_PAGE_ALPHA_DISPLAY 0x14   /* Alphanumeric Display */
                                            /* 0x15-3f Reserved */
#define HID_USAGE_PAGE_MEDICAL 0x40         /* Medical Instruments */
                                            /* 0x41-7f Reserved */
                                            /* 0x80-83 Monitor Devices */
                                            /* 0x84-87 Power Devices */
                                            /* 0x88-8b Reserved */
#define HID_USAGE_PAGE_BARCODE_SCANNER 0x8c /* Bar Code Scanner page */
#define HID_USAGE_PAGE_SCALE           0x8d /* Scale page */
#define HID_USAGE_PAGE_MSR             0x8e /* Magnetic Stripe Reading (MSR) Devices */
#define HID_USAGE_PAGE_POS             0x8f /* Point of Sale devices */
#define HID_USAGE_PAGE_CAMERA_CTRL     0x90 /* Camera Control Page */

/* Generic Desktop Page Usage IDs (HuT 4) */
#define HID_DESKTOP_USAGE_UNDEFINED 0x00        /* Undefined */
#define HID_DESKTOP_USAGE_POINTER   0x01        /* Pointer */
#define HID_DESKTOP_USAGE_MOUSE     0x02        /* Mouse */
                                           /* 0x03 Reserved */
#define HID_DESKTOP_USAGE_JOYSTICK  0x04        /* Joystick */
#define HID_DESKTOP_USAGE_GAMEPAD   0x05        /* Game Pad */
#define HID_DESKTOP_USAGE_KEYBOARD  0x06        /* Keyboard */
#define HID_DESKTOP_USAGE_KEYPAD    0x07        /* Keypad */
#define HID_DESKTOP_USAGE_MULTIAXIS 0x08        /* Multi-axis Controller */
#define HID_DESKTOP_USAGE_TABLET    0x09        /* Tablet PC System Controls */
                                           /* 0x0a-2f Reserved */
#define HID_DESKTOP_USAGE_X         0x30        /* X */
#define HID_DESKTOP_USAGE_Y         0x31        /* Y */
#define HID_DESKTOP_USAGE_Z         0x32        /* Z */
#define HID_DESKTOP_USAGE_RX        0x33        /* Rx */
#define HID_DESKTOP_USAGE_RY        0x34        /* Ry */
#define HID_DESKTOP_USAGE_RZ        0x35        /* Rz */
#define HID_DESKTOP_USAGE_SLIDER    0x36        /* Slider */
#define HID_DESKTOP_USAGE_DIAL      0x37        /* Dial */
#define HID_DESKTOP_USAGE_WHEEL     0x38        /* Wheel */
#define HID_DESKTOP_USAGE_HATSWITCH 0x39        /* Hat switch */
#define HID_DESKTOP_USAGE_COUNTED   0x3a        /* Counted Buffer */
#define HID_DESKTOP_USAGE_BYTECOUNT 0x3b        /* Byte Count */
#define HID_DESKTOP_USAGE_MOTION    0x3c        /* Motion Wakeup */
#define HID_DESKTOP_USAGE_START     0x3d        /* Start */
#define HID_DESKTOP_USAGE_SELECT    0x3e        /* Select */
                                           /* 0x3f Reserved */
#define HID_DESKTOP_USAGE_VX         0x40       /* Vx */
#define HID_DESKTOP_USAGE_VY         0x41       /* Vy */
#define HID_DESKTOP_USAGE_VZ         0x42       /* Vz */
#define HID_DESKTOP_USAGE_VBRX       0x43       /* Vbrx */
#define HID_DESKTOP_USAGE_VBRY       0x44       /* Vbry */
#define HID_DESKTOP_USAGE_VBRZ       0x45       /* Vbrz */
#define HID_DESKTOP_USAGE_VNO        0x46       /* Vno */
#define HID_DESKTOP_USAGE_FEATURE    0x47       /* Feature Notification */
#define HID_DESKTOP_USAGE_RESOLUTION 0x48       /* Resolution Multiplier */
                                           /* 0x49-7f Reserved */
#define HID_DESKTOP_USAGE_CONTROL      0x80     /* System Control */
#define HID_DESKTOP_USAGE_POWERDOWN    0x81     /* System Power Down */
#define HID_DESKTOP_USAGE_SLEEP        0x82     /* System Sleep */
#define HID_DESKTOP_USAGE_WAKEUP       0x83     /* System Wake Up */
#define HID_DESKTOP_USAGE_CONTEXT_MENU 0x84     /* System Context Menu */
#define HID_DESKTOP_USAGE_MAIN_MENU    0x85     /* System Main Menu */
#define HID_DESKTOP_USAGE_APP_MENU     0x86     /* System App Menu */
#define HID_DESKTOP_USAGE_MENU_HELP    0x87     /* System Menu Help */
#define HID_DESKTOP_USAGE_MENU_EXIT    0x88     /* System Menu Exit */
#define HID_DESKTOP_USAGE_MENU_SELECT  0x89     /* System Menu Select */
#define HID_DESKTOP_USAGE_MENU_RIGHT   0x8a     /* System Menu Right */
#define HID_DESKTOP_USAGE_MENU_LEFT    0x8b     /* System Menu Left */
#define HID_DESKTOP_USAGE_MENU_UP      0x8c     /* System Menu Up */
#define HID_DESKTOP_USAGE_MENU_DOWN    0x8d     /* System Menu Down */
#define HID_DESKTOP_USAGE_COLD_RESTART 0x8e     /* System Cold Restart */
#define HID_DESKTOP_USAGE_WARM_RESTART 0x8f     /* System Warm Restart */
#define HID_DESKTOP_USAGE_DPAD_UP      0x90     /* D-pad Up */
#define HID_DESKTOP_USAGE_DPAD_DOWN    0x91     /* D-pad Down */
#define HID_DESKTOP_USAGE_DPAD_RIGHT   0x92     /* D-pad Right */
#define HID_DESKTOP_USAGE_DPAD_LEFT    0x93     /* D-pad Left */
                                           /* 0x94-9f Reserved */
#define HID_DESKTOP_USAGE_DOCK            0xa0  /* System Dock */
#define HID_DESKTOP_USAGE_UNDOCK          0xa1  /* System Undock */
#define HID_DESKTOP_USAGE_SETUP           0xa2  /* System Setup */
#define HID_DESKTOP_USAGE_BREAK           0xa3  /* System Break */
#define HID_DESKTOP_USAGE_DEBUG_BREAK     0xa4  /* System Debugger Break */
#define HID_DESKTOP_USAGE_APP_BREAK       0xa5  /* Application Break */
#define HID_DESKTOP_USAGE_APP_DEBUG_BREAK 0xa6  /* Application Debugger Break */
#define HID_DESKTOP_USAGE_MUTE            0xa7  /* System Speaker Mute */
#define HID_DESKTOP_USAGE_HIBERNATE       0xa8  /* System Hibernate */
                                           /* 0xa9-af Reserved */
#define HID_DESKTOP_USAGE_DISPLAY_INVERT   0xb0 /* System Display Invert */
#define HID_DESKTOP_USAGE_DISPALY_INTERNAL 0xb1 /* System Display Internal */
#define HID_DESKTOP_USAGE_DISPLAY_EXTERNAL 0xb2 /* System Display External */
#define HID_DESKTOP_USAGE_DISPLAY_BOTH     0xb3 /* System Display Both */
#define HID_DESKTOP_USAGE_DISPLAY_DUAL     0xb4 /* System Display Dual */
#define HID_DESKTOP_USAGE_DISPLAY_TOGGLE   0xb5 /* System Display Toggle Int/Ext */
#define HID_DESKTOP_USAGE_DISPLAY_SWAP     0xb6 /* System Display Swap */
#define HID_DESKTOP_USAGE_                 0xb7 /* System Display LCD Autoscale */
                                           /* 0xb8-ffff Reserved */

/* Keyboard usage IDs (HuT 10) */
#define HID_KBD_USAGE_NONE            0x00 /* Reserved (no event indicated) */
#define HID_KBD_USAGE_ERRORROLLOVER   0x01 /* Keyboard ErrorRollOver */
#define HID_KBD_USAGE_POSTFAIL        0x02 /* Keyboard POSTFail */
#define HID_KBD_USAGE_ERRUNDEF        0x03 /* Keyboard ErrorUndefined */
#define HID_KBD_USAGE_A               0x04 /* Keyboard a or A (B-Z follow) */
#define HID_KBD_USAGE_1               0x1e /* Keyboard 1 (2-9 follow) */
#define HID_KBD_USAGE_EXCLAM          0x1e /* Keyboard 1 and ! */
#define HID_KBD_USAGE_AT              0x1f /* Keyboard 2 and @ */
#define HID_KBD_USAGE_POUND           0x20 /* Keyboard 3 and # */
#define HID_KBD_USAGE_DOLLAR          0x21 /* Keyboard 4 and $ */
#define HID_KBD_USAGE_PERCENT         0x22 /* Keyboard 5 and % */
#define HID_KBD_USAGE_CARAT           0x23 /* Keyboard 6 and ^ */
#define HID_KBD_USAGE_AMPERSAND       0x24 /* Keyboard 7 and & */
#define HID_KBD_USAGE_ASTERISK        0x25 /* Keyboard 8 and * */
#define HID_KBD_USAGE_LPAREN          0x26 /* Keyboard 9 and ( */
#define HID_KBD_USAGE_0               0x27 /* Keyboard 0 and ) */
#define HID_KBD_USAGE_RPAREN          0x27 /* Keyboard 0 and ) */
#define HID_KBD_USAGE_ENTER           0x28 /* Keyboard Return (ENTER) */
#define HID_KBD_USAGE_ESCAPE          0x29 /* Keyboard ESCAPE */
#define HID_KBD_USAGE_DELETE          0x2a /* Keyboard DELETE (Backspace) */
#define HID_KBD_USAGE_TAB             0x2b /* Keyboard Tab */
#define HID_KBD_USAGE_SPACE           0x2c /* Keyboard Spacebar */
#define HID_KBD_USAGE_HYPHEN          0x2d /* Keyboard - and (underscore) */
#define HID_KBD_USAGE_UNDERSCORE      0x2d /* Keyboard - and (underscore) */
#define HID_KBD_USAGE_EQUAL           0x2e /* Keyboard = and + */
#define HID_KBD_USAGE_PLUS            0x2e /* Keyboard = and + */
#define HID_KBD_USAGE_LBRACKET        0x2f /* Keyboard [ and { */
#define HID_KBD_USAGE_LBRACE          0x2f /* Keyboard [ and { */
#define HID_KBD_USAGE_RBRACKET        0x30 /* Keyboard ] and } */
#define HID_KBD_USAGE_RBRACE          0x30 /* Keyboard ] and } */
#define HID_KBD_USAGE_BSLASH          0x31 /* Keyboard \ and | */
#define HID_KBD_USAGE_VERTBAR         0x31 /* Keyboard \ and | */
#define HID_KBD_USAGE_NONUSPOUND      0x32 /* Keyboard Non-US # and ~ */
#define HID_KBD_USAGE_TILDE           0x32 /* Keyboard Non-US # and ~ */
#define HID_KBD_USAGE_SEMICOLON       0x33 /* Keyboard ; and : */
#define HID_KBD_USAGE_COLON           0x33 /* Keyboard ; and : */
#define HID_KBD_USAGE_SQUOTE          0x34 /* Keyboard ' and " */
#define HID_KBD_USAGE_DQUOUTE         0x34 /* Keyboard ' and " */
#define HID_KBD_USAGE_GACCENT         0x35 /* Keyboard Grave Accent and Tilde */
#define HID_KBD_USAGE_GTILDE          0x35 /* Keyboard Grave Accent and Tilde */
#define HID_KBD_USAGE_COMMON          0x36 /* Keyboard , and < */
#define HID_KBD_USAGE_LT              0x36 /* Keyboard , and < */
#define HID_KBD_USAGE_PERIOD          0x37 /* Keyboard . and > */
#define HID_KBD_USAGE_GT              0x37 /* Keyboard . and > */
#define HID_KBD_USAGE_DIV             0x38 /* Keyboard / and ? */
#define HID_KBD_USAGE_QUESTION        0x38 /* Keyboard / and ? */
#define HID_KBD_USAGE_CAPSLOCK        0x39 /* Keyboard Caps Lock */
#define HID_KBD_USAGE_F1              0x3a /* Keyboard F1 */
#define HID_KBD_USAGE_F2              0x3b /* Keyboard F2 */
#define HID_KBD_USAGE_F3              0x3c /* Keyboard F3 */
#define HID_KBD_USAGE_F4              0x3d /* Keyboard F4 */
#define HID_KBD_USAGE_F5              0x3e /* Keyboard F5 */
#define HID_KBD_USAGE_F6              0x3f /* Keyboard F6 */
#define HID_KBD_USAGE_F7              0x40 /* Keyboard F7 */
#define HID_KBD_USAGE_F8              0x41 /* Keyboard F8 */
#define HID_KBD_USAGE_F9              0x42 /* Keyboard F9 */
#define HID_KBD_USAGE_F10             0x43 /* Keyboard F10 */
#define HID_KBD_USAGE_F11             0x44 /* Keyboard F11 */
#define HID_KBD_USAGE_F12             0x45 /* Keyboard F12 */
#define HID_KBD_USAGE_PRINTSCN        0x46 /* Keyboard PrintScreen */
#define HID_KBD_USAGE_SCROLLLOCK      0x47 /* Keyboard Scroll Lock */
#define HID_KBD_USAGE_PAUSE           0x48 /* Keyboard Pause */
#define HID_KBD_USAGE_INSERT          0x49 /* Keyboard Insert */
#define HID_KBD_USAGE_HOME            0x4a /* Keyboard Home */
#define HID_KBD_USAGE_PAGEUP          0x4b /* Keyboard PageUp */
#define HID_KBD_USAGE_DELFWD          0x4c /* Keyboard Delete Forward */
#define HID_KBD_USAGE_END             0x4d /* Keyboard End */
#define HID_KBD_USAGE_PAGEDOWN        0x4e /* Keyboard PageDown */
#define HID_KBD_USAGE_RIGHT           0x4f /* eyboard RightArrow */
#define HID_KBD_USAGE_LEFT            0x50 /* Keyboard LeftArrow */
#define HID_KBD_USAGE_DOWN            0x51 /* Keyboard DownArrow */
#define HID_KBD_USAGE_UP              0x52 /* Keyboard UpArrow */
#define HID_KBD_USAGE_KPDNUMLOCK      0x53 /* Keypad Num Lock and Clear */
#define HID_KBD_USAGE_KPDNUMLOCKCLEAR 0x53 /* Keypad Num Lock and Clear */
#define HID_KBD_USAGE_KPDDIV          0x54 /* Keypad / */
#define HID_KBD_USAGE_KPDMUL          0x55 /* Keypad * */
#define HID_KBD_USAGE_KPDHMINUS       0x56 /* Keypad - */
#define HID_KBD_USAGE_KPDPLUS         0x57 /* Keypad + */
#define HID_KBD_USAGE_KPDEMTER        0x58 /* Keypad ENTER */
#define HID_KBD_USAGE_KPD1            0x59 /* Keypad 1 (2-9 follow) */
#define HID_KBD_USAGE_KPDEND          0x59 /* Keypad 1 and End */
#define HID_KBD_USAGE_KPDDOWN         0x5a /* Keypad 2 and Down Arrow */
#define HID_KBD_USAGE_KPDPAGEDN       0x5b /* Keypad 3 and PageDn */
#define HID_KBD_USAGE_KPDLEFT         0x5c /* Keypad 4 and Left Arrow */
#define HID_KBD_USAGE_KPDRIGHT        0x5e /* Keypad 6 and Right Arrow */
#define HID_KBD_USAGE_KPDHOME         0x5f /* Keypad 7 and Home */
#define HID_KBD_USAGE_KPDUP           0x60 /* Keypad 8 and Up Arrow */
#define HID_KBD_USAGE_KPDPAGEUP       0x61 /* Keypad 9 and PageUp */
#define HID_KBD_USAGE_KPD0            0x62 /* Keypad 0 and Insert */
#define HID_KBD_USAGE_KPDINSERT       0x62 /* Keypad 0 and Insert */
#define HID_KBD_USAGE_KPDDECIMALPT    0x63 /* Keypad . and Delete */
#define HID_KBD_USAGE_KPDDELETE       0x63 /* Keypad . and Delete */
#define HID_KBD_USAGE_NONSLASH        0x64 /* Keyboard Non-US \ and | */
#define HID_KBD_USAGE_NONUSVERT       0x64 /* Keyboard Non-US \ and | */
#define HID_KBD_USAGE_APPLICATION     0x65 /* Keyboard Application */
#define HID_KBD_USAGE_POWER           0x66 /* Keyboard Power */
#define HID_KBD_USAGE_KPDEQUAL        0x67 /* Keypad = */
#define HID_KBD_USAGE_F13             0x68 /* Keyboard F13 */
#define HID_KBD_USAGE_F14             0x69 /* Keyboard F14 */
#define HID_KBD_USAGE_F15             0x6a /* Keyboard F15 */
#define HID_KBD_USAGE_F16             0x6b /* Keyboard F16 */
#define HID_KBD_USAGE_F17             0x6c /* Keyboard F17 */
#define HID_KBD_USAGE_F18             0x6d /* Keyboard F18 */
#define HID_KBD_USAGE_F19             0x6e /* Keyboard F19 */
#define HID_KBD_USAGE_F20             0x6f /* Keyboard F20 */
#define HID_KBD_USAGE_F21             0x70 /* Keyboard F21 */
#define HID_KBD_USAGE_F22             0x71 /* Keyboard F22 */
#define HID_KBD_USAGE_F23             0x72 /* Keyboard F23 */
#define HID_KBD_USAGE_F24             0x73 /* Keyboard F24 */
#define HID_KBD_USAGE_EXECUTE         0x74 /* Keyboard Execute */
#define HID_KBD_USAGE_HELP            0x75 /* Keyboard Help */
#define HID_KBD_USAGE_MENU            0x76 /* Keyboard Menu */
#define HID_KBD_USAGE_SELECT          0x77 /* Keyboard Select */
#define HID_KBD_USAGE_STOP            0x78 /* Keyboard Stop */
#define HID_KBD_USAGE_AGAIN           0x79 /* Keyboard Again */
#define HID_KBD_USAGE_UNDO            0x7a /* Keyboard Undo */
#define HID_KBD_USAGE_CUT             0x7b /* Keyboard Cut */
#define HID_KBD_USAGE_COPY            0x7c /* Keyboard Copy */
#define HID_KBD_USAGE_PASTE           0x7d /* Keyboard Paste */
#define HID_KBD_USAGE_FIND            0x7e /* Keyboard Find */
#define HID_KBD_USAGE_MUTE            0x7f /* Keyboard Mute */
#define HID_KBD_USAGE_VOLUP           0x80 /* Keyboard Volume Up */
#define HID_KBD_USAGE_VOLDOWN         0x81 /* Keyboard Volume Down */
#define HID_KBD_USAGE_LCAPSLOCK       0x82 /* Keyboard Locking Caps Lock */
#define HID_KBD_USAGE_LNUMLOCK        0x83 /* Keyboard Locking Num Lock */
#define HID_KBD_USAGE_LSCROLLLOCK     0x84 /* Keyboard Locking Scroll Lock */
#define HID_KBD_USAGE_KPDCOMMA        0x85 /* Keypad Comma */
#define HID_KBD_USAGE_KPDEQUALSIGN    0x86 /* Keypad Equal Sign */
#define HID_KBD_USAGE_INTERNATIONAL1  0x87 /* Keyboard International 1 */
#define HID_KBD_USAGE_INTERNATIONAL2  0x88 /* Keyboard International 2 */
#define HID_KBD_USAGE_INTERNATIONAL3  0x89 /* Keyboard International 3 */
#define HID_KBD_USAGE_INTERNATIONAL4  0x8a /* Keyboard International 4 */
#define HID_KBD_USAGE_INTERNATIONAL5  0x8b /* Keyboard International 5 */
#define HID_KBD_USAGE_INTERNATIONAL6  0x8c /* Keyboard International 6 */
#define HID_KBD_USAGE_INTERNATIONAL7  0x8d /* Keyboard International 7 */
#define HID_KBD_USAGE_INTERNATIONAL8  0x8e /* Keyboard International 8 */
#define HID_KBD_USAGE_INTERNATIONAL9  0x8f /* Keyboard International 9 */
#define HID_KBD_USAGE_LANG1           0x90 /* Keyboard LANG1 */
#define HID_KBD_USAGE_LANG2           0x91 /* Keyboard LANG2 */
#define HID_KBD_USAGE_LANG3           0x92 /* Keyboard LANG3 */
#define HID_KBD_USAGE_LANG4           0x93 /* Keyboard LANG4 */
#define HID_KBD_USAGE_LANG5           0x94 /* Keyboard LANG5 */
#define HID_KBD_USAGE_LANG6           0x95 /* Keyboard LANG6 */
#define HID_KBD_USAGE_LANG7           0x96 /* Keyboard LANG7 */
#define HID_KBD_USAGE_LANG8           0x97 /* Keyboard LANG8 */
#define HID_KBD_USAGE_LANG9           0x98 /* Keyboard LANG9 */
#define HID_KBD_USAGE_ALTERASE        0x99 /* Keyboard Alternate Erase */
#define HID_KBD_USAGE_SYSREQ          0x9a /* Keyboard SysReq/Attention */
#define HID_KBD_USAGE_CANCEL          0x9b /* Keyboard Cancel */
#define HID_KBD_USAGE_CLEAR           0x9c /* Keyboard Clear */
#define HID_KBD_USAGE_PRIOR           0x9d /* Keyboard Prior */
#define HID_KBD_USAGE_RETURN          0x9e /* Keyboard Return */
#define HID_KBD_USAGE_SEPARATOR       0x9f /* Keyboard Separator */
#define HID_KBD_USAGE_OUT             0xa0 /* Keyboard Out */
#define HID_KBD_USAGE_OPER            0xa1 /* Keyboard Oper */
#define HID_KBD_USAGE_CLEARAGAIN      0xa2 /* Keyboard Clear/Again */
#define HID_KBD_USAGE_CLRSEL          0xa3 /* Keyboard CrSel/Props */
#define HID_KBD_USAGE_EXSEL           0xa4 /* Keyboard ExSel */
#define HID_KBD_USAGE_KPD00           0xb0 /* Keypad 00 */
#define HID_KBD_USAGE_KPD000          0xb1 /* Keypad 000 */
#define HID_KBD_USAGE_THOUSEPARATOR   0xb2 /* Thousands Separator */
#define HID_KBD_USAGE_DECSEPARATOR    0xb3 /* Decimal Separator */
#define HID_KBD_USAGE_CURRUNIT        0xb4 /* Currency Unit */
#define HID_KBD_USAGE_CURRSUBUNIT     0xb5 /* Currency Sub-unit */
#define HID_KBD_USAGE_KPDLPAREN       0xb6 /* Keypad ( */
#define HID_KBD_USAGE_KPDRPAREN       0xb7 /* Keypad ) */
#define HID_KBD_USAGE_KPDLBRACE       0xb8 /* Keypad { */
#define HID_KBD_USAGE_KPDRBRACE       0xb9 /* Keypad } */
#define HID_KBD_USAGE_KPDTAB          0xba /* Keypad Tab */
#define HID_KBD_USAGE_KPDBACKSPACE    0xbb /* Keypad Backspace */
#define HID_KBD_USAGE_KPDA            0xbc /* Keypad A (B-F follow) */
#define HID_KBD_USAGE_KPDXOR          0xc2 /* Keypad XOR */
#define HID_KBD_USAGE_KPDEXP          0xc3 /* Keypad ^ */
#define HID_KBD_USAGE_KPDPERCENT      0xc4 /* Keypad % */
#define HID_KBD_USAGE_KPDLT           0xc5 /* Keypad < */
#define HID_KBD_USAGE_KPDGT           0xc6 /* Keypad > */
#define HID_KBD_USAGE_KPDAMPERSAND    0xc7 /* Keypad & */
#define HID_KBD_USAGE_KPDAND          0xc8 /* Keypad && */
#define HID_KBD_USAGE_KPDVERT         0xc9 /* Keypad | */
#define HID_KBD_USAGE_KPDOR           0xca /* Keypad || */
#define HID_KBD_USAGE_KPDCOLON        0xcb /* Keypad : */
#define HID_KBD_USAGE_KPDPOUND        0xcc /* Keypad # */
#define HID_KBD_USAGE_KPDSPACE        0xcd /* Keypad Space */
#define HID_KBD_USAGE_KPDAT           0xce /* Keypad @ */
#define HID_KBD_USAGE_KPDEXCLAM       0xcf /* Keypad ! */
#define HID_KBD_USAGE_KPDMEMSTORE     0xd0 /* Keypad Memory Store */
#define HID_KBD_USAGE_KPDMEMRECALL    0xd1 /* Keypad Memory Recall */
#define HID_KBD_USAGE_KPDMEMCLEAR     0xd2 /* Keypad Memory Clear */
#define HID_KBD_USAGE_KPDMEMADD       0xd3 /* Keypad Memory Add */
#define HID_KBD_USAGE_KPDMEMSUB       0xd4 /* Keypad Memory Subtract */
#define HID_KBD_USAGE_KPDMEMMULT      0xd5 /* Keypad Memory Multiply */
#define HID_KBD_USAGE_KPDMEMDIV       0xd6 /* Keypad Memory Divide */
#define HID_KBD_USAGE_KPDPLUSMINUS    0xd7 /* Keypad +/- */
#define HID_KBD_USAGE_KPDCLEAR        0xd8 /* Keypad Clear */
#define HID_KBD_USAGE_KPDCLEARENTRY   0xd9 /* Keypad Clear Entry */
#define HID_KBD_USAGE_KPDBINARY       0xda /* Keypad Binary */
#define HID_KBD_USAGE_KPDOCTAL        0xdb /* Keypad Octal */
#define HID_KBD_USAGE_KPDDECIMAL      0xdc /* Keypad Decimal */
#define HID_KBD_USAGE_KPDHEXADECIMAL  0xdd /* Keypad Hexadecimal */
#define HID_KBD_USAGE_LCTRL           0xe0 /* Keyboard LeftControl */
#define HID_KBD_USAGE_LSHIFT          0xe1 /* Keyboard LeftShift */
#define HID_KBD_USAGE_LALT            0xe2 /* Keyboard LeftAlt */
#define HID_KBD_USAGE_LGUI            0xe3 /* Keyboard Left GUI */
#define HID_KBD_USAGE_RCTRL           0xe4 /* Keyboard RightControl */
#define HID_KBD_USAGE_RSHIFT          0xe5 /* Keyboard RightShift */
#define HID_KBD_USAGE_RALT            0xe6 /* Keyboard RightAlt */
#define HID_KBD_USAGE_RGUI            0xe7 /* Keyboard Right GUI */

#define HID_KBD_USAGE_MAX 0xe7

/* HID Report Definitions */
struct usb_hid_class_subdescriptor {
    uint8_t bDescriptorType;/* Class descriptor type (See 7.1) */
    uint16_t wDescriptorLength;/* Size of the report descriptor */
} __PACKED;

struct usb_hid_descriptor {
    uint8_t bLength; /* Size of the HID descriptor */
    uint8_t bDescriptorType;/* HID descriptor type */
    uint16_t bcdHID;/* HID class specification release */
    uint8_t bCountryCode;/* Country code */
    uint8_t bNumDescriptors;/* Number of descriptors (>=1) */

    /*
     * Specification says at least one Class Descriptor needs to
     * be present (Report Descriptor).
     */
    struct usb_hid_class_subdescriptor subdesc[1];
} __PACKED;

/* Standard Reports *********************************************************/

/* Keyboard input report (8 bytes) (HID B.1) */
struct usb_hid_kbd_report
{
  uint8_t modifier;  /* Modifier keys. See HID_MODIFER_* definitions */
  uint8_t reserved;
  uint8_t key[6];    /* Keycode 1-6 */
};

/* Keyboard output report (1 byte) (HID B.1),
 * see USBHID_KBDOUT_* definitions
 */

/* Mouse input report (HID B.2) */
struct usb_hid_mouse_report
{
  uint8_t buttons;   /* See HID_MOUSE_INPUT_BUTTON_* definitions */
  uint8_t xdisp;     /* X displacement */
  uint8_t ydisp;     /* y displacement */
                     /* Device specific additional bytes may follow */
#ifdef CONFIG_INPUT_MOUSE_WHEEL
  uint8_t wdisp;     /* Wheel displacement */
#endif
};

/* Joystick input report (1 bytes) (HID D.1) */
struct usb_hid_js_report
{
  uint8_t xpos;      /* X position */
  uint8_t ypos;      /* X position */
  uint8_t buttons;   /* See USBHID_JSIN_* definitions */
  uint8_t throttle;  /* Throttle */
};

#endif /* USB_HID_H */
