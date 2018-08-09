/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
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

#define NRF_CLI_VT100_ASCII_ESC     (0x1b)
#define NRF_CLI_VT100_ASCII_DEL     (0x7F)
#define NRF_CLI_VT100_ASCII_BSPACE  (0x08)

#define NRF_CLI_VT100_SETNL                                             \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '2', '0', 'h', '\0'               \
    } /* Set new line mode */
#define NRF_CLI_VT100_SETAPPL                                           \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '?', '1', 'h', '\0'               \
    } /* Set cursor key to application */
#define NRF_CLI_VT100_SETCOL_132                                        \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '?', '3', 'h', '\0'               \
    } /* Set number of columns to 132 */
#define NRF_CLI_VT100_SETSMOOTH                                         \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '?', '4', 'h', '\0'               \
    } /* Set smooth scrolling */
#define NRF_CLI_VT100_SETREVSCRN                                        \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '?', '5', 'h', '\0'               \
    } /* Set reverse video on screen */
#define NRF_CLI_VT100_SETORGREL                                         \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '?', '6', 'h', '\0'               \
    } /* Set origin to relative */
#define NRF_CLI_VT100_SETWRAP_ON                                        \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '?', '7', 'h', '\0'               \
    } /* Set auto-wrap mode */
#define NRF_CLI_VT100_SETWRAP_OFF                                       \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '?', '7', 'l', '\0'               \
    } /* Set auto-wrap mode */

#define NRF_CLI_VT100_SETREP                                            \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '?', '8', 'h', '\0'               \
    } /* Set auto-repeat mode */
#define NRF_CLI_VT100_SETINTER                                          \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '?', '9', 'h', '\0'               \
    } /* Set interlacing mode */

#define NRF_CLI_VT100_SETLF                                             \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '2', '0', 'l', '\0'               \
    } /* Set line feed mode */
#define NRF_CLI_VT100_SETCURSOR                                         \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '?', '1', 'l', '\0'               \
    } /* Set cursor key to cursor */
#define NRF_CLI_VT100_SETVT52                                           \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '?', '2', 'l', '\0'               \
    } /* Set VT52 (versus ANSI) */
#define NRF_CLI_VT100_SETCOL_80                                         \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '?', '3', 'l', '\0'               \
    } /* Set number of columns to 80 */
#define NRF_CLI_VT100_SETJUMP                                           \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '?', '4', 'l', '\0'               \
    } /* Set jump scrolling */
#define NRF_CLI_VT100_SETNORMSCRN                                       \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '?', '5', 'l', '\0'               \
    } /* Set normal video on screen */
#define NRF_CLI_VT100_SETORGABS                                         \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '?', '6', 'l', '\0'               \
    } /* Set origin to absolute */
#define NRF_CLI_VT100_RESETWRAP                                         \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '?', '7', 'l', '\0'               \
    } /* Reset auto-wrap mode */
#define NRF_CLI_VT100_RESETREP                                          \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '?', '8', 'l', '\0'               \
    } /* Reset auto-repeat mode */
#define NRF_CLI_VT100_RESETINTER                                        \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '?', '9', 'l', '\0'               \
    } /* Reset interlacing mode */

#define NRF_CLI_VT100_ALTKEYPAD                                         \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '=', '\0'                              \
    } /* Set alternate keypad mode */
#define NRF_CLI_VT100_NUMKEYPAD                                         \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '>', '\0'                              \
    } /* Set numeric keypad mode */

#define NRF_CLI_VT100_SETUKG0                                           \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '(', 'A', '\0'                         \
    } /* Set United Kingdom G0 character set */
#define NRF_CLI_VT100_SETUKG1                                           \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, ')', 'A', '\0'                         \
    } /* Set United Kingdom G1 character set */
#define NRF_CLI_VT100_SETUSG0                                           \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '(', 'B', '\0'                         \
    } /* Set United States G0 character set */
#define NRF_CLI_VT100_SETUSG1                                           \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, ')', 'B', '\0'                         \
    } /* Set United States G1 character set */
#define NRF_CLI_VT100_SETSPECG0                                         \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '(', '0', '\0'                         \
    } /* Set G0 special chars. & line set */
#define NRF_CLI_VT100_SETSPECG1                                         \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, ')', '0', '\0'                         \
    } /* Set G1 special chars. & line set */
#define NRF_CLI_VT100_SETALTG0                                          \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '(', '1', '\0'                         \
    } /* Set G0 alternate character ROM */
#define NRF_CLI_VT100_SETALTG1                                          \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, ')', '1', '\0'                         \
    } /* Set G1 alternate character ROM */
#define NRF_CLI_VT100_SETALTSPECG0                                      \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '(', '2', '\0'                         \
    } /* Set G0 alt char ROM and spec. graphics */
#define NRF_CLI_VT100_SETALTSPECG1                                      \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, ')', '2', '\0'                         \
    } /* Set G1 alt char ROM and spec. graphics */

#define NRF_CLI_VT100_SETSS2                                            \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'N', '\0'                              \
    } /* Set single shift 2 */
#define NRF_CLI_VT100_SETSS3                                            \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'O', '\0'                              \
    } /* Set single shift 3 */

#define NRF_CLI_VT100_MODESOFF                                          \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', 'm', '\0'                         \
    } /* Turn off character attributes */
#define NRF_CLI_VT100_MODESOFF_                                         \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '0', 'm', '\0'                    \
    } /* Turn off character attributes */
#define NRF_CLI_VT100_BOLD                                              \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '1', 'm', '\0'                    \
    } /* Turn bold mode on */
#define NRF_CLI_VT100_LOWINT                                            \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '2', 'm', '\0'                    \
    } /* Turn low intensity mode on */
#define NRF_CLI_VT100_UNDERLINE                                         \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '4', 'm', '\0'                    \
    } /* Turn underline mode on */
#define NRF_CLI_VT100_BLINK                                             \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '5', 'm', '\0'                    \
    } /* Turn blinking mode on */
#define NRF_CLI_VT100_REVERSE                                           \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '7', 'm', '\0'                    \
    } /* Turn reverse video on */
#define NRF_CLI_VT100_INVISIBLE                                         \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '8', 'm', '\0'                    \
    } /* Turn invisible text mode on */

#define NRF_CLI_VT100_SETWIN(t, b)                                      \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', (t), ';', (b), 'r', '\0'          \
    } /* Set top and bottom line#s of a window */

#define NRF_CLI_VT100_CURSORUP(n)                                       \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', (n), 'A', '\0'                    \
    } /* Move cursor up n lines */
#define NRF_CLI_VT100_CURSORDN(n)                                       \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', (n), 'B', '\0'                    \
    } /* Move cursor down n lines */
#define NRF_CLI_VT100_CURSORRT(n)                                       \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', (n), 'C', '\0'                    \
    } /* Move cursor right n lines */
#define NRF_CLI_VT100_CURSORLF(n)                                       \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', (n), 'D', '\0'                    \
    } /* Move cursor left n lines */
#define NRF_CLI_VT100_CURSORHOME                                        \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', 'H', '\0'                         \
    } /* Move cursor to upper left corner */
#define NRF_CLI_VT100_CURSORHOME_                                       \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', ';', 'H', '\0'                    \
    } /* Move cursor to upper left corner */
#define NRF_CLI_VT100_CURSORPOS(v, h)                                   \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', (v), ';', (h), 'H', '\0'          \
    } /* Move cursor to screen location v,h */

#define NRF_CLI_VT100_HVHOME                                            \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', 'f', '\0'                         \
    } /* Move cursor to upper left corner */
#define NRF_CLI_VT100_HVHOME_                                           \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', ';', 'f', '\0'                    \
    } /* Move cursor to upper left corner */
#define NRF_CLI_VT100_HVPOS(v, h)                                       \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', (v), ';', (h), 'f', '\0'          \
    } /* Move cursor to screen location v,h */
#define NRF_CLI_VT100_INDEX                                             \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'D', '\0'                              \
    } /* Move/scroll window up one line */
#define NRF_CLI_VT100_REVINDEX                                          \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'M', '\0'                              \
    } /* Move/scroll window down one line */
#define NRF_CLI_VT100_NEXTLINE                                          \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'E', '\0'                              \
    } /* Move to next line */
#define NRF_CLI_VT100_SAVECURSOR                                        \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '7', '\0'                              \
    } /* Save cursor position and attributes */
#define NRF_CLI_VT100_RESTORECURSOR                                     \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '8', '\0'                              \
    } /* Restore cursor position and attribute */

#define NRF_CLI_VT100_TABSET                                            \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'H', '\0'                              \
    } /* Set a tab at the current column */
#define NRF_CLI_VT100_TABCLR                                            \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', 'g', '\0'                         \
    } /* Clear a tab at the current column */
#define NRF_CLI_VT100_TABCLR_                                           \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '0', 'g', '\0'                    \
    } /* Clear a tab at the current column */
#define NRF_CLI_VT100_TABCLRALL                                         \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '3', 'g', '\0'                    \
    } /* Clear all tabs */

#define NRF_CLI_VT100_DHTOP                                             \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '#', '3', '\0'                         \
    } /* Double-height letters, top half */
#define NRF_CLI_VT100_DHBOT                                             \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '#', '4', '\0'                         \
    } /* Double-height letters, bottom hal */
#define NRF_CLI_VT100_SWSH                                              \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '#', '5', '\0'                         \
    } /* Single width, single height letters */
#define NRF_CLI_VT100_DWSH                                              \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '#', '6', '\0'                         \
    } /* Double width, single height letters */

#define NRF_CLI_VT100_CLEAREOL                                          \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', 'K', '\0'                         \
    } /* Clear line from cursor right */
#define NRF_CLI_VT100_CLEAREOL_                                         \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '0', 'K', '\0'                    \
    } /* Clear line from cursor right */
#define NRF_CLI_VT100_CLEARBOL                                          \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '1', 'K', '\0'                    \
    } /* Clear line from cursor left */
#define NRF_CLI_VT100_CLEARLINE                                         \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '2', 'K', '\0'                    \
    } /* Clear entire line */

#define NRF_CLI_VT100_CLEAREOS                                          \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', 'J', '\0'                         \
    } /* Clear screen from cursor down */
#define NRF_CLI_VT100_CLEAREOS_                                         \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '0', 'J', '\0'                    \
    } /* Clear screen from cursor down */
#define NRF_CLI_VT100_CLEARBOS                                          \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '1', 'J', '\0'                    \
    } /* Clear screen from cursor up */
#define NRF_CLI_VT100_CLEARSCREEN                                       \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '2', 'J', '\0'                    \
    } /* Clear entire screen */

#define NRF_CLI_VT100_DEVSTAT                                           \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '5', 'n', '\0'                         \
    } /* Device status report */
#define NRF_CLI_VT100_TERMOK                                            \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '0', 'n', '\0'                         \
    } /* Response: terminal is OK */
#define NRF_CLI_VT100_TERMNOK                                           \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '3', 'n', '\0'                         \
    } /* Response: terminal is not OK */

#define NRF_CLI_VT100_GETCURSOR                                         \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '6', 'n', '\0'                    \
    } /* Get cursor position */
#define NRF_CLI_VT100_CURSORPOSAT                                       \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, (v), ';', (h), 'R', '\0'               \
    } /* Response: cursor is at v,h */

#define NRF_CLI_VT100_IDENT                                             \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', 'c', '\0'                         \
    } /* Identify what terminal type */
#define NRF_CLI_VT100_IDENT_                                            \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '0', 'c', '\0'                    \
    } /* Identify what terminal type */
#define NRF_CLI_VT100_GETTYPE                                           \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '?', '1', ';', (n), '0', 'c', '\0'\
    } /* Response: terminal type code n */

#define NRF_CLI_VT100_RESET                                             \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'c', '\0'                              \
    } /*  Reset terminal to initial state */

#define NRF_CLI_VT100_ALIGN                                             \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '#', '8', '\0'                         \
    } /* Screen alignment display */
#define NRF_CLI_VT100_TESTPU                                            \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '2', ';', '1', 'y', '\0'          \
    } /* Confidence power up test */
#define NRF_CLI_VT100_TESTLB                                            \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '2', ';', '2', 'y', '\0'          \
    } /* Confidence loopback test */
#define NRF_CLI_VT100_TESTPUREP                                         \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '2', ';', '9', 'y', '\0'          \
    } /* Repeat power up test */
#define NRF_CLI_VT100_TESTLBREP                                         \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '2', ';', '1', '0', 'y', '\0'     \
    } /* Repeat loopback test */

#define NRF_CLI_VT100_LEDSOFF                                           \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '0', 'q', '\0'                    \
    } /* Turn off all four leds */
#define NRF_CLI_VT100_LED1                                              \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '1', 'q', '\0'                    \
    } /* Turn on LED #1 */
#define NRF_CLI_VT100_LED2                                              \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '2', 'q', '\0'                    \
    } /* Turn on LED #2 */
#define NRF_CLI_VT100_LED3                                              \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '3', 'q', '\0'                    \
    } /* Turn on LED #3 */
#define NRF_CLI_VT100_LED4                                              \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, '[', '4', 'q', '\0'                    \
    } /* Turn on LED #4 */

/* Function Keys */

#define NRF_CLI_VT100_PF1                                               \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'O', 'P', '\0'                         \
    }
#define NRF_CLI_VT100_PF2                                               \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'O', 'Q', '\0'                         \
    }
#define NRF_CLI_VT100_PF3                                               \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'O', 'R', '\0'                         \
    }
#define NRF_CLI_VT100_PF4                                               \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'O', 'S', '\0'                         \
    }

/* Arrow keys */

#define NRF_CLI_VT100_UP_RESET                                          \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'A', '\0'                              \
    }
#define NRF_CLI_VT100_UP_SET                                            \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'O', 'A', '\0'                         \
    }
#define NRF_CLI_VT100_DOWN_RESET                                        \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'B', '\0'                              \
    }
#define NRF_CLI_VT100_DOWN_SET                                          \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'O', 'B', '\0'                         \
    }
#define NRF_CLI_VT100_RIGHT_RESET                                       \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'C', '\0'                              \
    }
#define NRF_CLI_VT100_RIGHT_SET                                         \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'O', 'C', '\0'                         \
    }
#define NRF_CLI_VT100_LEFT_RESET                                        \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'D', '\0'                              \
    }
#define NRF_CLI_VT100_LEFT_SET                                          \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'O', 'D', '\0'                         \
    }

/* Numeric Keypad Keys */

#define NRF_CLI_VT100_NUMERIC_0                                         \
    {                                                                   \
        '0', '\0'                                                       \
    }
#define NRF_CLI_VT100_ALT_0                                             \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'O', 'p', '\0'                         \
    }
#define NRF_CLI_VT100_NUMERIC_1                                         \
    {                                                                   \
        '1', '\0'                                                       \
    }
#define NRF_CLI_VT100_ALT_1                                             \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'O', 'q', '\0'                         \
    }
#define NRF_CLI_VT100_NUMERIC_2                                         \
    {                                                                   \
        '2', '\0'                                                       \
    }
#define NRF_CLI_VT100_ALT_2                                             \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'O', 'r', '\0'                         \
    }
#define NRF_CLI_VT100_NUMERIC_3                                         \
    {                                                                   \
        '3', '\0'                                                       \
    }
#define NRF_CLI_VT100_ALT_3                                             \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'O', 's', '\0'                         \
    }
#define NRF_CLI_VT100_NUMERIC_4                                         \
    {                                                                   \
        '4', '\0'                                                       \
    }
#define NRF_CLI_VT100_ALT_4                                             \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'O', 't', '\0'                         \
    }
#define NRF_CLI_VT100_NUMERIC_5                                         \
    {                                                                   \
        '5', '\0'                                                       \
    }
#define NRF_CLI_VT100_ALT_5                                             \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'O', 'u', '\0'                         \
    }
#define NRF_CLI_VT100_NUMERIC_6                                         \
    {                                                                   \
        '6', '\0'                                                       \
    }
#define NRF_CLI_VT100_ALT_6                                             \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'O', 'v', '\0'                         \
    }
#define NRF_CLI_VT100_NUMERIC_7                                         \
    {                                                                   \
        '7', '\0'                                                       \
    }
#define NRF_CLI_VT100_ALT_7                                             \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'O', 'w', '\0'                         \
    }
#define NRF_CLI_VT100_NUMERIC_8                                         \
    {                                                                   \
        '8', '\0'                                                       \
    }
#define NRF_CLI_VT100_ALT_8                                             \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'O', 'x', '\0'                         \
    }
#define NRF_CLI_VT100_NUMERIC_9                                         \
    {                                                                   \
        '9', '\0'
#define NRF_CLI_VT100_ALT_9                                             \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'O', 'y'                               \
    }
#define NRF_CLI_VT100_NUMERIC_MINUS                                     \
    {                                                                   \
        '-', '\0'                                                       \
    }
#define NRF_CLI_VT100_ALT_MINUS                                         \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'O', 'm', '\0'                         \
    }
#define NRF_CLI_VT100_NUMERIC_COMMA                                     \
    {                                                                   \
        ',', '\0'                                                       \
    }
#define NRF_CLI_VT100_ALT_COMMA                                         \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'O', 'l', '\0'                         \
    }
#define NRF_CLI_VT100_NUMERIC_PERIOD                                    \
    {                                                                   \
        '.', '\0'                                                       \
    }
#define NRF_CLI_VT100_ALT_PERIOD                                        \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'O', 'n', '\0'                         \
    }
#define NRF_CLI_VT100_NUMERIC_ENTER                                     \
    {                                                                   \
        ASCII_CR                                                        \
    }
#define NRF_CLI_VT100_ALT_ENTER                                         \
    {                                                                   \
        NRF_CLI_VT100_ASCII_ESC, 'O', 'M', '\0'                         \
    }

#define NRF_CLI_VT100_COLOR(__col)                                            \
    {                                                                         \
        NRF_CLI_VT100_ASCII_ESC, '[', '1', ';', '3', '0' + (__col), 'm', '\0' \
    }
#define NRF_CLI_VT100_BGCOLOR(__col)                                          \
    {                                                                         \
        NRF_CLI_VT100_ASCII_ESC, '[', '4', '0' + (__col), 'm', '\0'           \
    }

#ifdef __cplusplus
}
#endif

#endif /* NRF_CLI_VT100_H__ */

