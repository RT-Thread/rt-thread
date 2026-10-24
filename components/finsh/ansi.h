/**
 * @file ansi.h
 * @brief VT100/xterm ANSI escape macros for serial terminal (e.g. Xshell).
 *
 * Usage:
 *   uart_puts(ANSI_CLR_LINE);
 *   uart_puts("log: ");
 *   uart_puts(msg);
 *   uart_puts(ANSI_CRLF);
 *   redraw_prompt();
 *
 * Compile-time: uart_puts(ANSI_CLR_LINE);
 * Runtime:     rt_kprintf(ANSI_FMT_CUB, n);
 */

#ifndef ANSI_H
#define ANSI_H

/* -------------------------------------------------------------------------- */
/* Core                                                                       */
/* -------------------------------------------------------------------------- */

#define ANSI_ESC "\x1b"
#define ANSI_CSI "\x1b["

#define ANSI_CRLF "\r\n"
#define ANSI_CR   "\r"
#define ANSI_LF   "\n"

/* -------------------------------------------------------------------------- */
/* Erase                                                                      */
/* -------------------------------------------------------------------------- */

/** Clear from cursor to end of line */
#define ANSI_EL ANSI_CSI "0K"
/** Clear from line start to cursor */
#define ANSI_EL_START ANSI_CSI "1K"
/** Clear entire current line */
#define ANSI_EL_LINE ANSI_CSI "2K"

/** Clear screen, cursor home (1,1) */
#define ANSI_CLS ANSI_CSI "2J"
/** Clear screen + scrollback (xterm) */
#define ANSI_CLS_ALL ANSI_CSI "3J"

/** Carriage return + erase whole line (most used) */
#define ANSI_CLR_LINE "\r" ANSI_EL_LINE

/* -------------------------------------------------------------------------- */
/* Cursor move — parameterized (n must be decimal literal or macro)          */
/* -------------------------------------------------------------------------- */

#define ANSI_CUU(n)        ANSI_CSI #n "A" /* cursor up */
#define ANSI_CUD(n)        ANSI_CSI #n "B" /* cursor down */
#define ANSI_CUF(n)        ANSI_CSI #n "C" /* cursor forward (right) */
#define ANSI_CUB(n)        ANSI_CSI #n "D" /* cursor back (left) */
#define ANSI_CHA(n)        ANSI_CSI #n "G" /* cursor column, 1-based */
#define ANSI_CUP(row, col) ANSI_CSI #row ";" #col "H"

#define ANSI_CUU1 ANSI_CSI "1A"
#define ANSI_CUD1 ANSI_CSI "1B"
#define ANSI_CUF1 ANSI_CSI "1C"
#define ANSI_CUB1 ANSI_CSI "1D"

/* -------------------------------------------------------------------------- */
/* Cursor move — runtime (rt_kprintf / printf / snprintf, n >= 1)            */
/* -------------------------------------------------------------------------- */

#define ANSI_FMT_CUU ANSI_ESC "[%dA"
#define ANSI_FMT_CUD ANSI_ESC "[%dB"
#define ANSI_FMT_CUF ANSI_ESC "[%dC"
#define ANSI_FMT_CUB ANSI_ESC "[%dD"
#define ANSI_FMT_CHA ANSI_ESC "[%dG"    /* column 1-based */
#define ANSI_FMT_CUP ANSI_ESC "[%d;%dH" /* row, col; both 1-based */

/** Move to column n (1 = first column) — compile-time literal only */
#define ANSI_COL(n) ANSI_CHA(n)

/**
 * Jump to end of current line without tracking column count.
 * Terminals clamp column to line width (works on Xshell VT100/xterm).
 */
#define ANSI_EOL   ANSI_CSI "999C"
#define ANSI_EOL_G ANSI_CSI "999G"

/* Save / restore cursor (optional; not all terminals support) */
#define ANSI_SAVE_CURSOR    ANSI_CSI "s"
#define ANSI_RESTORE_CURSOR ANSI_CSI "u"

/* -------------------------------------------------------------------------- */
/* SGR — text attributes                                                      */
/* -------------------------------------------------------------------------- */

#define ANSI_RESET     ANSI_CSI "0m"
#define ANSI_BOLD      ANSI_CSI "1m"
#define ANSI_DIM       ANSI_CSI "2m"
#define ANSI_UNDERLINE ANSI_CSI "4m"
#define ANSI_REVERSE   ANSI_CSI "7m"

#define ANSI_FG_BLACK   ANSI_CSI "30m"
#define ANSI_FG_RED     ANSI_CSI "31m"
#define ANSI_FG_GREEN   ANSI_CSI "32m"
#define ANSI_FG_YELLOW  ANSI_CSI "33m"
#define ANSI_FG_BLUE    ANSI_CSI "34m"
#define ANSI_FG_MAGENTA ANSI_CSI "35m"
#define ANSI_FG_CYAN    ANSI_CSI "36m"
#define ANSI_FG_WHITE   ANSI_CSI "37m"

#define ANSI_BG_BLACK   ANSI_CSI "40m"
#define ANSI_BG_RED     ANSI_CSI "41m"
#define ANSI_BG_GREEN   ANSI_CSI "42m"
#define ANSI_BG_YELLOW  ANSI_CSI "43m"
#define ANSI_BG_BLUE    ANSI_CSI "44m"
#define ANSI_BG_MAGENTA ANSI_CSI "45m"
#define ANSI_BG_CYAN    ANSI_CSI "46m"
#define ANSI_BG_WHITE   ANSI_CSI "47m"

/* -------------------------------------------------------------------------- */
/* Shell UI helpers (two-line layout: log above, prompt below)               */
/* -------------------------------------------------------------------------- */

/** Erase bottom interactive line (prompt + input); input kept in RAM. */
#define ANSI_PROMPT_CLEAR ANSI_CLR_LINE

/**
 * After a log line exists above: go up one line and move to its end.
 * Then uart_puts() incremental log bytes, then ANSI_UI_NEWLINE + redraw prompt.
 */
#define ANSI_LOG_APPEND_POS ANSI_CUU1 ANSI_EOL

/** Separate log row from prompt row (structural newline, not log content). */
#define ANSI_UI_NEWLINE ANSI_CRLF

/**
 * Overwrite current line in place (progress / status on one line).
 * uart_puts(ANSI_LINE_OVERWRITE); uart_puts("progress 50%");
 */
#define ANSI_LINE_OVERWRITE ANSI_CLR_LINE

#endif /* ANSI_H */
