/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
#ifndef NRF_CLI_VT100_H__
#define NRF_CLI_VT100_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#define VT100_ASCII_ESC 0x1b
#define VT100_ASCII_DEL 0x7F
#define VT100_ASCII_BSPACE 0x08

#define VT100_SETNL                                    \
    {                                                  \
        VT100_ASCII_ESC, '[', '2', '0', 'h'            \
    } /* Set new line mode */
#define VT100_SETAPPL                                  \
    {                                                  \
        VT100_ASCII_ESC, '[', '?', '1', 'h'            \
    } /* Set cursor key to application */
#define VT100_SETCOL                                   \
    {                                                  \
        VT100_ASCII_ESC, '[', '?', '3', 'h'            \
    } /* Set number of columns to 132 */
#define VT100_SETSMOOTH                                \
    {                                                  \
        VT100_ASCII_ESC, '[', '?', '4', 'h'            \
    } /* Set smooth scrolling */
#define VT100_SETREVSCRN                               \
    {                                                  \
        VT100_ASCII_ESC, '[', '?', '5', 'h'            \
    } /* Set reverse video on screen */
#define VT100_SETORGREL                                \
    {                                                  \
        VT100_ASCII_ESC, '[', '?', '6', 'h'            \
    } /* Set origin to relative */
#define VT100_SETWRAP                                  \
    {                                                  \
        VT100_ASCII_ESC, '[', '?', '7', 'h'            \
    } /* Set auto-wrap mode */
#define VT100_SETREP                                   \
    {                                                  \
        VT100_ASCII_ESC, '[', '?', '8', 'h'            \
    } /* Set auto-repeat mode */
#define VT100_SETINTER                                 \
    {                                                  \
        VT100_ASCII_ESC, '[', '?', '9', 'h'            \
    } /* Set interlacing mode */

#define VT100_SETLF                                    \
    {                                                  \
        VT100_ASCII_ESC, '[', '2', '0', 'l'            \
    } /* Set line feed mode */
#define VT100_SETCURSOR                                \
    {                                                  \
        VT100_ASCII_ESC, '[', '?', '1', 'l'            \
    } /* Set cursor key to cursor */
#define VT100_SETVT52                                  \
    {                                                  \
        VT100_ASCII_ESC, '[', '?', '2', 'l'            \
    } /* Set VT52 (versus ANSI) */
#define VT100_RESETCOL                                 \
    {                                                  \
        VT100_ASCII_ESC, '[', '?', '3', 'l'            \
    } /* Set number of columns to 80 */
#define VT100_SETJUMP                                  \
    {                                                  \
        VT100_ASCII_ESC, '[', '?', '4', 'l'            \
    } /* Set jump scrolling */
#define VT100_SETNORMSCRN                              \
    {                                                  \
        VT100_ASCII_ESC, '[', '?', '5', 'l'            \
    } /* Set normal video on screen */
#define VT100_SETORGABS                                \
    {                                                  \
        VT100_ASCII_ESC, '[', '?', '6', 'l'            \
    } /* Set origin to absolute */
#define VT100_RESETWRAP                                \
    {                                                  \
        VT100_ASCII_ESC, '[', '?', '7', 'l'            \
    } /* Reset auto-wrap mode */
#define VT100_RESETREP                                 \
    {                                                  \
        VT100_ASCII_ESC, '[', '?', '8', 'l'            \
    } /* Reset auto-repeat mode */
#define VT100_RESETINTER                               \
    {                                                  \
        VT100_ASCII_ESC, '[', '?', '9', 'l'            \
    } /* Reset interlacing mode */

#define VT100_ALTKEYPAD                                \
    {                                                  \
        VT100_ASCII_ESC, '='                           \
    } /* Set alternate keypad mode */
#define VT100_NUMKEYPAD                                \
    {                                                  \
        VT100_ASCII_ESC, '>'                           \
    } /* Set numeric keypad mode */

#define VT100_SETUKG0                                  \
    {                                                  \
        VT100_ASCII_ESC, '(', 'A'                      \
    } /* Set United Kingdom G0 character set */
#define VT100_SETUKG1                                  \
    {                                                  \
        VT100_ASCII_ESC, ')', 'A'                      \
    } /* Set United Kingdom G1 character set */
#define VT100_SETUSG0                                  \
    {                                                  \
        VT100_ASCII_ESC, '(', 'B'                      \
    } /* Set United States G0 character set */
#define VT100_SETUSG1                                  \
    {                                                  \
        VT100_ASCII_ESC, ')', 'B'                      \
    } /* Set United States G1 character set */
#define VT100_SETSPECG0                                \
    {                                                  \
        VT100_ASCII_ESC, '(', '0'                      \
    } /* Set G0 special chars. & line set */
#define VT100_SETSPECG1                                \
    {                                                  \
        VT100_ASCII_ESC, ')', '0'                      \
    } /* Set G1 special chars. & line set */
#define VT100_SETALTG0                                 \
    {                                                  \
        VT100_ASCII_ESC, '(', '1'                      \
    } /* Set G0 alternate character ROM */
#define VT100_SETALTG1                                 \
    {                                                  \
        VT100_ASCII_ESC, ')', '1'                      \
    } /* Set G1 alternate character ROM */
#define VT100_SETALTSPECG0                             \
    {                                                  \
        VT100_ASCII_ESC, '(', '2'                      \
    } /* Set G0 alt char ROM and spec. graphics */
#define VT100_SETALTSPECG1                             \
    {                                                  \
        VT100_ASCII_ESC, ')', '2'                      \
    } /* Set G1 alt char ROM and spec. graphics */

#define VT100_SETSS2                                   \
    {                                                  \
        VT100_ASCII_ESC, 'N'                           \
    } /* Set single shift 2 */
#define VT100_SETSS3                                   \
    {                                                  \
        VT100_ASCII_ESC, 'O'                           \
    } /* Set single shift 3 */

#define VT100_MODESOFF                                 \
    {                                                  \
        VT100_ASCII_ESC, '[', 'm'                      \
    } /* Turn off character attributes */
#define VT100_MODESOFF_                                \
    {                                                  \
        VT100_ASCII_ESC, '[', '0', 'm'                 \
    } /* Turn off character attributes */
#define VT100_BOLD                                     \
    {                                                  \
        VT100_ASCII_ESC, '[', '1', 'm'                 \
    } /* Turn bold mode on */
#define VT100_LOWINT                                   \
    {                                                  \
        VT100_ASCII_ESC, '[', '2', 'm'                 \
    } /* Turn low intensity mode on */
#define VT100_UNDERLINE                                \
    {                                                  \
        VT100_ASCII_ESC, '[', '4', 'm'                 \
    } /* Turn underline mode on */
#define VT100_BLINK                                    \
    {                                                  \
        VT100_ASCII_ESC, '[', '5', 'm'                 \
    } /* Turn blinking mode on */
#define VT100_REVERSE                                  \
    {                                                  \
        VT100_ASCII_ESC, '[', '7', 'm'                 \
    } /* Turn reverse video on */
#define VT100_INVISIBLE                                \
    {                                                  \
        VT100_ASCII_ESC, '[', '8', 'm'                 \
    } /* Turn invisible text mode on */

#define VT100_SETWIN(t, b)                             \
    {                                                  \
        VT100_ASCII_ESC, '[', (t), ';', (b), 'r'       \
    } /* Set top and bottom line#s of a window */

#define VT100_CURSORUP(n)                              \
    {                                                  \
        VT100_ASCII_ESC, '[', (n), 'A'                 \
    } /* Move cursor up n lines */
#define VT100_CURSORDN(n)                              \
    {                                                  \
        VT100_ASCII_ESC, '[', (n), 'B'                 \
    } /* Move cursor down n lines */
#define VT100_CURSORRT(n)                              \
    {                                                  \
        VT100_ASCII_ESC, '[', (n), 'C'                 \
    } /* Move cursor right n lines */
#define VT100_CURSORLF(n)                              \
    {                                                  \
        VT100_ASCII_ESC, '[', (n), 'D'                 \
    } /* Move cursor left n lines */
#define VT100_CURSORHOME                               \
    {                                                  \
        VT100_ASCII_ESC, '[', 'H'                      \
    } /* Move cursor to upper left corner */
#define VT100_CURSORHOME_                              \
    {                                                  \
        VT100_ASCII_ESC, '[', ';', 'H'                 \
    } /* Move cursor to upper left corner */
#define VT100_CURSORPOS(v, h)                          \
    {                                                  \
        VT100_ASCII_ESC, '[', (v), ';', (h), 'H'       \
    } /* Move cursor to screen location v,h */

#define VT100_HVHOME                                   \
    {                                                  \
        VT100_ASCII_ESC, '[', 'f'                      \
    } /* Move cursor to upper left corner */
#define VT100_HVHOME_                                  \
    {                                                  \
        VT100_ASCII_ESC, '[', ';', 'f'                 \
    } /* Move cursor to upper left corner */
#define VT100_HVPOS(v, h)                              \
    {                                                  \
        VT100_ASCII_ESC, '[', (v), ';', (h), 'f'       \
    } /* Move cursor to screen location v,h */
#define VT100_INDEX                                    \
    {                                                  \
        VT100_ASCII_ESC, 'D'                           \
    } /* Move/scroll window up one line */
#define VT100_REVINDEX                                 \
    {                                                  \
        VT100_ASCII_ESC, 'M'                           \
    } /* Move/scroll window down one line */
#define VT100_NEXTLINE                                 \
    {                                                  \
        VT100_ASCII_ESC, 'E'                           \
    } /* Move to next line */
#define VT100_SAVECURSOR                               \
    {                                                  \
        VT100_ASCII_ESC, '7'                           \
    } /* Save cursor position and attributes */
#define VT100_RESTORECURSOR                            \
    {                                                  \
        VT100_ASCII_ESC, '8'                           \
    } /* Restore cursor position and attribute */

#define VT100_TABSET                                   \
    {                                                  \
        VT100_ASCII_ESC, 'H'                           \
    } /* Set a tab at the current column */
#define VT100_TABCLR                                   \
    {                                                  \
        VT100_ASCII_ESC, '[', 'g'                      \
    } /* Clear a tab at the current column */
#define VT100_TABCLR_                                  \
    {                                                  \
        VT100_ASCII_ESC, '[', '0', 'g'                 \
    } /* Clear a tab at the current column */
#define VT100_TABCLRALL                                \
    {                                                  \
        VT100_ASCII_ESC, '[', '3', 'g'                 \
    } /* Clear all tabs */

#define VT100_DHTOP                                    \
    {                                                  \
        VT100_ASCII_ESC, '#', '3'                      \
    } /* Double-height letters, top half */
#define VT100_DHBOT                                    \
    {                                                  \
        VT100_ASCII_ESC, '#', '4'                      \
    } /* Double-height letters, bottom hal */
#define VT100_SWSH                                     \
    {                                                  \
        VT100_ASCII_ESC, '#', '5'                      \
    } /* Single width, single height letters */
#define VT100_DWSH                                     \
    {                                                  \
        VT100_ASCII_ESC, '#', '6'                      \
    } /* Double width, single height letters */

#define VT100_CLEAREOL                                 \
    {                                                  \
        VT100_ASCII_ESC, '[', 'K'                      \
    } /* Clear line from cursor right */
#define VT100_CLEAREOL_                                \
    {                                                  \
        VT100_ASCII_ESC, '[', '0', 'K'                 \
    } /* Clear line from cursor right */
#define VT100_CLEARBOL                                 \
    {                                                  \
        VT100_ASCII_ESC, '[', '1', 'K'                 \
    } /* Clear line from cursor left */
#define VT100_CLEARLINE                                \
    {                                                  \
        VT100_ASCII_ESC, '[', '2', 'K'                 \
    } /* Clear entire line */

#define VT100_CLEAREOS                                 \
    {                                                  \
        VT100_ASCII_ESC, '[', 'J'                      \
    } /* Clear screen from cursor down */
#define VT100_CLEAREOS_                                \
    {                                                  \
        VT100_ASCII_ESC, '[', '0', 'J'                 \
    } /* Clear screen from cursor down */
#define VT100_CLEARBOS                                 \
    {                                                  \
        VT100_ASCII_ESC, '[', '1', 'J'                 \
    } /* Clear screen from cursor up */
#define VT100_CLEARSCREEN                              \
    {                                                  \
        VT100_ASCII_ESC, '[', '2', 'J'                 \
    } /* Clear entire screen */

#define VT100_DEVSTAT                                  \
    {                                                  \
        VT100_ASCII_ESC, '5', 'n'                      \
    } /* Device status report */
#define VT100_TERMOK                                   \
    {                                                  \
        VT100_ASCII_ESC, '0', 'n'                      \
    } /* Response: terminal is OK */
#define VT100_TERMNOK                                  \
    {                                                  \
        VT100_ASCII_ESC, '3', 'n'                      \
    } /* Response: terminal is not OK */

#define VT100_GETCURSOR                                \
    {                                                  \
        VT100_ASCII_ESC, '[', '6', 'n'                 \
    } /* Get cursor position */
#define VT100_CURSORPOSAT                              \
    {                                                  \
        VT100_ASCII_ESC, (v), ';', (h), 'R'            \
    } /* Response: cursor is at v,h */

#define VT100_IDENT                                    \
    {                                                  \
        VT100_ASCII_ESC, '[', 'c'                      \
    } /* Identify what terminal type */
#define VT100_IDENT_                                   \
    {                                                  \
        VT100_ASCII_ESC, '[', '0', 'c'                 \
    } /* Identify what terminal type */
#define VT100_GETTYPE                                       \
    {                                                       \
        VT100_ASCII_ESC, '[', '?', '1', ';', (n), '0', 'c'  \
    } /* Response: terminal type code n */

#define VT100_RESET                                         \
    {                                                       \
        VT100_ASCII_ESC, 'c'                                \
    } /*  Reset terminal to initial state */

#define VT100_ALIGN                                         \
    {                                                       \
        VT100_ASCII_ESC, '#', '8'                           \
    } /* Screen alignment display */
#define VT100_TESTPU                                        \
    {                                                       \
        VT100_ASCII_ESC, '[', '2', ';', '1', 'y'            \
    } /* Confidence power up test */
#define VT100_TESTLB                                        \
    {                                                       \
        VT100_ASCII_ESC, '[', '2', ';', '2', 'y'            \
    } /* Confidence loopback test */
#define VT100_TESTPUREP                                     \
    {                                                       \
        VT100_ASCII_ESC, '[', '2', ';', '9', 'y'            \
    } /* Repeat power up test */
#define VT100_TESTLBREP                                     \
    {                                                       \
        VT100_ASCII_ESC, '[', '2', ';', '1', '0', 'y'       \
    } /* Repeat loopback test */

#define VT100_LEDSOFF                                       \
    {                                                       \
        VT100_ASCII_ESC, '[', '0', 'q'                      \
    } /* Turn off all four leds */
#define VT100_LED1                                          \
    {                                                       \
        VT100_ASCII_ESC, '[', '1', 'q'                      \
    } /* Turn on LED #1 */
#define VT100_LED2                                          \
    {                                                       \
        VT100_ASCII_ESC, '[', '2', 'q'                      \
    } /* Turn on LED #2 */
#define VT100_LED3                                          \
    {                                                       \
        VT100_ASCII_ESC, '[', '3', 'q'                      \
    } /* Turn on LED #3 */
#define VT100_LED4                                          \
    {                                                       \
        VT100_ASCII_ESC, '[', '4', 'q'                      \
    } /* Turn on LED #4 */

/* Function Keys */

#define VT100_PF1                                           \
    {                                                       \
        VT100_ASCII_ESC, 'O', 'P'                           \
    }
#define VT100_PF2                                           \
    {                                                       \
        VT100_ASCII_ESC, 'O', 'Q'                           \
    }
#define VT100_PF3                                           \
    {                                                       \
        VT100_ASCII_ESC, 'O', 'R'                           \
    }
#define VT100_PF4                                           \
    {                                                       \
        VT100_ASCII_ESC, 'O', 'S'                           \
    }

/* Arrow keys */

#define VT100_UP_RESET                 \
    {                                  \
        VT100_ASCII_ESC, 'A'           \
    }
#define VT100_UP_SET                   \
    {                                  \
        VT100_ASCII_ESC, 'O', 'A'      \
    }
#define VT100_DOWN_RESET               \
    {                                  \
        VT100_ASCII_ESC, 'B'           \
    }
#define VT100_DOWN_SET                 \
    {                                  \
        VT100_ASCII_ESC, 'O', 'B'      \
    }
#define VT100_RIGHT_RESET              \
    {                                  \
        VT100_ASCII_ESC, 'C'           \
    }
#define VT100_RIGHT_SET                \
    {                                  \
        VT100_ASCII_ESC, 'O', 'C'      \
    }
#define VT100_LEFT_RESET               \
    {                                  \
        VT100_ASCII_ESC, 'D'           \
    }
#define VT100_LEFT_SET                 \
    {                                  \
        VT100_ASCII_ESC, 'O', 'D'      \
    }

/* Numeric Keypad Keys */

#define VT100_NUMERIC_0                \
    {                                  \
        '0'                            \
    }
#define VT100_ALT_0                    \
    {                                  \
        VT100_ASCII_ESC, 'O', 'p'      \
    }
#define VT100_NUMERIC_1                \
    {                                  \
        '1'                            \
    }
#define VT100_ALT_1                    \
    {                                  \
        VT100_ASCII_ESC, 'O', 'q'      \
    }
#define VT100_NUMERIC_2                \
    {                                  \
        '2'                            \
    }
#define VT100_ALT_2                    \
    {                                  \
        VT100_ASCII_ESC, 'O', 'r'      \
    }
#define VT100_NUMERIC_3                \
    {                                  \
        '3'                            \
    }
#define VT100_ALT_3                    \
    {                                  \
        VT100_ASCII_ESC, 'O', 's'      \
    }
#define VT100_NUMERIC_4                \
    {                                  \
        '4'                            \
    }
#define VT100_ALT_4                    \
    {                                  \
        VT100_ASCII_ESC, 'O', 't'      \
    }
#define VT100_NUMERIC_5                \
    {                                  \
        '5'                            \
    }
#define VT100_ALT_5                    \
    {                                  \
        VT100_ASCII_ESC, 'O', 'u'      \
    }
#define VT100_NUMERIC_6                \
    {                                  \
        '6'                            \
    }
#define VT100_ALT_6                    \
    {                                  \
        VT100_ASCII_ESC, 'O', 'v'      \
    }
#define VT100_NUMERIC_7                \
    {                                  \
        '7'                            \
    }
#define VT100_ALT_7                    \
    {                                  \
        VT100_ASCII_ESC, 'O', 'w'      \
    }
#define VT100_NUMERIC_8                \
    {                                  \
        '8'                            \
    }
#define VT100_ALT_8                    \
    {                                  \
        VT100_ASCII_ESC, 'O', 'x'      \
    }
#define VT100_NUMERIC_9                \
    {                                  \
        '9',
#define VT100_ALT_9                    \
    {                                  \
        VT100_ASCII_ESC, 'O', 'y'      \
    }
#define VT100_NUMERIC_MINUS            \
    {                                  \
        '-'                            \
    }
#define VT100_ALT_MINUS                \
    {                                  \
        VT100_ASCII_ESC, 'O', 'm'      \
    }
#define VT100_NUMERIC_COMMA            \
    {                                  \
        ','                            \
    }
#define VT100_ALT_COMMA                \
    {                                  \
        VT100_ASCII_ESC, 'O', 'l'      \
    }
#define VT100_NUMERIC_PERIOD           \
    {                                  \
        '.'                            \
    }
#define VT100_ALT_PERIOD               \
    {                                  \
        VT100_ASCII_ESC, 'O', 'n'      \
    }
#define VT100_NUMERIC_ENTER            \
    {                                  \
        ASCII_CR                       \
    }
#define VT100_ALT_ENTER                \
    {                                  \
        VT100_ASCII_ESC, 'O', 'M'      \
    }


typedef enum {
    VT100_COLOR_BLACK = 0,
    VT100_COLOR_RED,
    VT100_COLOR_GREEN,
    VT100_COLOR_YELLOW,
    VT100_COLOR_BLUE,
    VT100_COLOR_MAGENTA,
    VT100_COLOR_CYAN,
    VT100_COLOR_WHITE,

    VT100_COLOR_END
} vt100_color_t;

#define VT100_COLOR(__col)                           \
    {                                                \
        VT100_ASCII_ESC, '[', '3', '0' + __col, 'm'  \
    }
#define VT100_BGCOLOR(__col)                         \
    {                                                \
        VT100_ASCII_ESC, '[', '4', '0' + __col, 'm'  \
    }

typedef struct {
    uint16_t x;
    uint16_t y;
} vt100_cursor_t;

typedef struct {
    vt100_color_t col;
    vt100_color_t bgcol;
} vt100_colors_t;

typedef struct {
    vt100_cursor_t cur;
    vt100_colors_t col;
} vt100_ctx_t;



#ifdef __cplusplus
}
#endif

#endif /* NRF_CLI_VT100_H__ */
