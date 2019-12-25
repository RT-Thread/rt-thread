/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
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
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(NRF_CLI)
#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>
#include "nrf_cli.h"
#include "nrf_cli_vt100.h"
#include "app_error.h"
#include "nrf_assert.h"
#include "nrf_delay.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_atomic.h"

#if NRF_MODULE_ENABLED(NRF_CLI_WILDCARD)
#include "fnmatch.h"
#endif

#if NRF_MODULE_ENABLED(NRF_CLI_HISTORY)
    #if NRF_CLI_HISTORY_ELEMENT_SIZE * NRF_CLI_HISTORY_ELEMENT_COUNT == 0
        #error Not proper memory size allocated for NRF_CLI_HISTORY
    #endif
#endif

/* 2 == 1 char for cmd + 1 char for '\0' */
#if NRF_CLI_CMD_BUFF_SIZE < 2
    #error too small NRF_CLI_CMD_BUFF_SIZE
#endif

#if NRF_CLI_PRINTF_BUFF_SIZE < 1
    #error too small NRF_CLI_PRINTF_BUFF_SIZE
#endif

#define NRF_CLI_HELP_CLEAR              "Clear screen."
#define NRF_CLI_HELP_COLORS             "Toggle colored syntax."
#define NRF_CLI_HELP_COLORS_OFF         "Disable colored syntax."
#define NRF_CLI_HELP_COLORS_ON          "Enable colored syntax."
#define NRF_CLI_HELP_STATISTICS         "CLI statistics."
#define NRF_CLI_HELP_STATISTICS_SHOW    "Get CLI statistics for the Logger module."
#define NRF_CLI_HELP_STATISTICS_RESET   "Reset CLI statistics for the Logger module."
#define NRF_CLI_HELP_RESIZE             "Console gets terminal screen size or assumes 80 in case " \
                                        "the readout fails. It must be executed after each terminal " \
                                        "width change to ensure correct text display."
#define NRF_CLI_HELP_RESIZE_DEFAULT     "Assume 80 chars screen width and send this setting "     \
                                        "to the terminal."
#define NRF_CLI_HELP_HISTORY            "Command history."
#define NRF_CLI_HELP_ECHO               "Toggle CLI echo."
#define NRF_CLI_HELP_ECHO_ON            "Enable CLI echo."
#define NRF_CLI_HELP_ECHO_OFF           "Disable CLI echo. Arrows and buttons: Backspace, "       \
                                        "Delete, End, Home, Insert are not handled."
#define NRF_CLI_HELP_CLI                "Useful, not Unix-like CLI commands."

#define NRF_CLI_MSG_SPECIFY_SUBCOMMAND  "Please specify a subcommand."
#define NRF_CLI_MSG_UNKNOWN_PARAMETER   " unknown parameter: "
#define NRF_CLI_MSG_COMMAND_NOT_FOUND   ": command not found"
#define NRF_CLI_MSG_TAB_OVERFLOWED      "Tab function: commands counter overflowed."

/*lint -save -esym(526,cli_command*) -esym(526,cli_sorted_cmd_ptrs*)*/
NRF_SECTION_DEF(cli_command, nrf_cli_cmd_entry_t);
#define CLI_DATA_SECTION_ITEM_GET(i) NRF_SECTION_ITEM_GET(cli_command, nrf_cli_cmd_entry_t, (i))
#define CLI_DATA_SECTION_ITEM_COUNT  NRF_SECTION_ITEM_COUNT(cli_command, nrf_cli_cmd_entry_t)

NRF_SECTION_DEF(cli_sorted_cmd_ptrs, const char *);
/*lint -restore*/
#define CLI_SORTED_CMD_PTRS_ITEM_GET(i) NRF_SECTION_ITEM_GET(cli_sorted_cmd_ptrs, const char *, (i))
#define CLI_SORTED_CMD_PTRS_START_ADDR_GET NRF_SECTION_START_ADDR(cli_sorted_cmd_ptrs)

#if defined(NRF_CLI_LOG_BACKEND) && NRF_CLI_LOG_BACKEND
#include "nrf_log_str_formatter.h"
#include "nrf_log_internal.h"
#endif

#define NRF_CLI_INIT_OPTION_PRINTER                  (NULL)

#define NRF_CLI_MAX_TERMINAL_SIZE       (250u)
#define NRF_CLI_CURSOR_POSITION_BUFFER  (10u)   /* 10 == {esc, [, 2, 5, 0, ;, 2, 5, 0, '\0'} */
#define NRF_CLI_DEFAULT_TERMINAL_WIDTH  (80u)   /* Default PuTTY width. */
#define NRF_CLI_DEFAULT_TERMINAL_HEIGHT (24u)   /* Default PuTTY height. */
#define NRF_CLI_INITIAL_CURS_POS        (1u)    /* Initial cursor position is: (1, 1). */

#define NRF_CLI_CMD_ROOT_LVL            (0u)

/* Macro to send VT100 commands. */
#define NRF_CLI_VT100_CMD(_p_cli_, _cmd_)   {       \
    ASSERT(_p_cli_);                                \
    ASSERT(_p_cli_->p_fprintf_ctx);                 \
    static char const cmd[] = _cmd_;                \
    nrf_fprintf(_p_cli_->p_fprintf_ctx, "%s", cmd); \
}

#if NRF_MODULE_ENABLED(NRF_CLI_WILDCARD)
typedef enum
{
    WILDCARD_CMD_ADDED,
    WILDCARD_CMD_ADDED_MISSING_SPACE,
    WILDCARD_CMD_NO_MATCH_FOUND
} wildcard_cmd_status_t;
#endif


static bool cli_log_entry_process(nrf_cli_t const * p_cli, bool skip);
static void cli_execute(nrf_cli_t const * p_cli);


static inline void transport_buffer_flush(nrf_cli_t const * p_cli)
{
    nrf_fprintf_buffer_flush(p_cli->p_fprintf_ctx);
}

static inline void cli_flag_help_set(nrf_cli_t const * p_cli)
{
    p_cli->p_ctx->internal.flag.show_help = 1;
}
static inline void cli_flag_help_clear(nrf_cli_t const * p_cli)
{
    p_cli->p_ctx->internal.flag.show_help = 0;
}

#if NRF_MODULE_ENABLED(NRF_CLI_BUILD_IN_CMDS)
static inline void cli_flag_echo_set(nrf_cli_t const * p_cli)
{
    p_cli->p_ctx->internal.flag.echo = 1;
}

static inline void cli_flag_echo_clear(nrf_cli_t const * p_cli)
{
    p_cli->p_ctx->internal.flag.echo = 0;
}
#endif /* NRF_MODULE_ENABLED(NRF_CLI_BUILD_IN_CMDS) */

static inline bool cli_flag_echo_is_set(nrf_cli_t const * p_cli)
{
    return p_cli->p_ctx->internal.flag.echo == 1 ? true : false;
}

static inline bool cli_flag_processing_is_set(nrf_cli_t const * p_cli)
{
    return p_cli->p_ctx->internal.flag.processing == 1 ? true : false;
}

static inline uint8_t cli_flag_last_nl_get(nrf_cli_t const * p_cli)
{
    return p_cli->p_ctx->internal.flag.last_nl;
}

static inline void cli_flag_last_nl_set(nrf_cli_t const * p_cli, uint8_t val)
{
    p_cli->p_ctx->internal.flag.last_nl = val;
}

static inline void receive_state_change(nrf_cli_t const * p_cli, nrf_cli_receive_t state)
{
    p_cli->p_ctx->receive_state = state;
}

static inline size_t cli_strlen(char const * str)
{
    return str == NULL ? 0 : strlen(str);
}

static void cli_cmd_buffer_clear(nrf_cli_t const * p_cli)
{
    p_cli->p_ctx->cmd_buff[0] = '\0';  /* clear command buffer */
    p_cli->p_ctx->cmd_buff_pos = 0;
    p_cli->p_ctx->cmd_buff_len = 0;
}

/* Function returns true if cursor is at beginning of an empty line. */
static inline bool cursor_in_empty_line(nrf_cli_t const * p_cli)
{
    return ( (p_cli->p_ctx->cmd_buff_pos + cli_strlen(p_cli->p_name)) %
              p_cli->p_ctx->vt100_ctx.cons.terminal_wid == 0);
}

/* Function returns true if command length is equal to multiplicity of terminal width. */
static inline bool full_line_cmd(nrf_cli_t const * p_cli)
{
    return ((p_cli->p_ctx->cmd_buff_len + cli_strlen(p_cli->p_name)) %
            p_cli->p_ctx->vt100_ctx.cons.terminal_wid == 0);
}

#if NRF_MODULE_ENABLED(NRF_CLI_WILDCARD)
/* Function returns true if string contains wildcard character: '?' or '*'. */
static bool wildcard_character_exist(char * p_str)
{
    size_t str_len = cli_strlen(p_str);
    for (size_t i = 0; i < str_len; i++)
    {
        if ((p_str[i] == '?') || (p_str[i] == '*'))
        {
            return true;
        }
    }
    return false;
}
#endif

/* Function sends data stream to the CLI instance. Each time before the cli_write function is called,
 * it must be ensured that IO buffer of fprintf is flushed to avoid synchronization issues.
 * For that purpose, use function transport_buffer_flush(p_cli) */
static void cli_write(nrf_cli_t const * p_cli,
                      void const *      p_data,
                      size_t            length,
                      size_t *          p_cnt)
{
    ASSERT(p_cli && p_data);
    ASSERT(p_cli->p_iface->p_api);
    size_t offset = 0;
    size_t cnt;
    while (length)
    {
        ret_code_t ret = p_cli->p_iface->p_api->write(p_cli->p_iface,
                                                      &((uint8_t const *)p_data)[offset],
                                                      length,
                                                      &cnt);
        UNUSED_VARIABLE(ret);
        ASSERT(ret == NRF_SUCCESS);
        ASSERT(length >= cnt);
        offset += cnt;
        length -= cnt;
        if (cnt == 0 && (p_cli->p_ctx->state != NRF_CLI_STATE_PANIC_MODE_ACTIVE))
        {
#if NRF_MODULE_ENABLED(NRF_CLI_USES_TASK_MANAGER)
            (void)task_events_wait(NRF_CLI_TRANSPORT_TX_RDY_TASK_EVT);
#else
            while (p_cli->p_ctx->internal.flag.tx_rdy == 0)
            {
                ;
            }
            p_cli->p_ctx->internal.flag.tx_rdy = 0;
#endif
        }
    }

    if (p_cnt)
    {
        *p_cnt = cnt;
    }
}

/* Function sends 1 character to the CLI instance. */
static inline void cli_putc(nrf_cli_t const * p_cli, char ch)
{
    nrf_fprintf(p_cli->p_fprintf_ctx, "%c", ch);
}

/* Function reads data from the CLI instance. */
static void cli_read(nrf_cli_t const * p_cli,
                     void *            p_data,
                     size_t            length,
                     size_t *          p_cnt)
{
    ASSERT(p_cli && p_data);
    ASSERT(p_cli->p_iface);

    ret_code_t ret = p_cli->p_iface->p_api->read(p_cli->p_iface, p_data, length, p_cnt);
    UNUSED_VARIABLE(ret);
}

/* Function cmd_get shall be used to search commands. It moves the pointer pp_entry to command
 * of static command structure. If the command cannot be found, the function will set pp_entry to NULL.
 *   p_command   Pointer to command which will be processed (no matter the root command).
 *   lvl         Level of the requested command.
 *   idx         Index of the requested command.
 *   pp_entry    Pointer which points to subcommand[idx] after function execution.
 *   p_st_entry  Pointer to the structure where dynamic entry data can be stored.
 */
static void cmd_get(nrf_cli_cmd_entry_t const *     p_command,
                    size_t                          lvl,
                    size_t                          idx,
                    nrf_cli_static_entry_t const ** pp_entry,
                    nrf_cli_static_entry_t *        p_st_entry)
{
    ASSERT (pp_entry != NULL);
    ASSERT (p_st_entry != NULL);

    if (lvl == NRF_CLI_CMD_ROOT_LVL)
    {
        if (idx < CLI_DATA_SECTION_ITEM_COUNT)
        {
            nrf_cli_cmd_entry_t const * p_cmd = NULL;
            char const * * pp_sorted_cmds = (char const * *)CLI_SORTED_CMD_PTRS_START_ADDR_GET;
            for (size_t i = 0; i < CLI_DATA_SECTION_ITEM_COUNT; i++)
            {
                p_cmd = CLI_DATA_SECTION_ITEM_GET(i);
                if (!strcmp(pp_sorted_cmds[idx], p_cmd->u.p_static->p_syntax))
                {
                    *pp_entry = p_cmd->u.p_static;
                    return;
                }
            }
        }
        *pp_entry = NULL;
        return;
    }

    if (p_command == NULL)
    {
        *pp_entry = NULL;
        return;
    }

    if (p_command->is_dynamic)
    {
        p_command->u.p_dynamic_get(idx, p_st_entry);
        if (p_st_entry->p_syntax == NULL)
        {
            *pp_entry = NULL;
        }
        else
        {
            *pp_entry = p_st_entry;
        }
    }
    else
    {
        if (p_command->u.p_static[idx].p_syntax != NULL)
        {
            *pp_entry = &p_command->u.p_static[idx];
        }
        else
        {
            *pp_entry = NULL;
        }
    }
}

/* Function multiline_console_data_check checks the current cursor position (x, y) on terminal screen
 * based on: command length, console name length, and terminal width.
 * Example 1:
 * || - cursor
 *  ----------------------------
 * |console_name $: ||          |
 *  ----------------------------
 * => coordinates are:  cur_x = 17, cur_x_end = 17,
 *                      cur_y = 1,  cur_y_end = 1
 * Example 2:
 *  ----------------------------
 * |console_name $: test command|
 * |showing |e|xample           |
 *  ----------------------------
 * => coordinates are:  cur_x = 9, cur_x_end = 18 (cursor can be one column after 'e')
 * =>                   cur_y = 2, cur_y_end = 2
 * Example 3:
 *  ----------------------------
 * |console_name $: test command|
 * |showing e|x|ample with more |
 * |parameters                  |
 *  ----------------------------
 * => coordinates are:  cur_x = 10, cur_x_end = 11 (cursor can be one column after 's')
 * =>                   cur_y = 2, cur_y_end = 3
 */
static nrf_cli_multiline_cons_t const * multiline_console_data_check(nrf_cli_t const * p_cli)
{
    nrf_cli_ctx_t * p_ctx = p_cli->p_ctx;
    nrf_cli_multiline_cons_t * p_cons = &p_cli->p_ctx->vt100_ctx.cons;

    p_cons->name_len = cli_strlen(p_cli->p_name);

    /* Current cursor position in command.
     * +1 -> because home position is (1, 1) */
    p_cons->cur_x = (p_ctx->cmd_buff_pos + p_cons->name_len) % p_cons->terminal_wid + 1;
    p_cons->cur_y = (p_ctx->cmd_buff_pos + p_cons->name_len) / p_cons->terminal_wid + 1;

    /* Extreme position when cursor is at the end of command. */
    p_cons->cur_y_end = (p_ctx->cmd_buff_len + p_cons->name_len) / p_cons->terminal_wid + 1;
    p_cons->cur_x_end = (p_ctx->cmd_buff_len + p_cons->name_len) % p_cons->terminal_wid + 1;

    return p_cons;
}


#if NRF_MODULE_ENABLED(NRF_CLI_METAKEYS)
/* Calculates relative line number of given position in buffer */
static uint32_t cli_line_num_with_buffer_offset_get(nrf_cli_t const * p_cli,
                                                    nrf_cli_cmd_len_t buffer_pos)
{
    uint32_t name_len;
    nrf_cli_multiline_cons_t *p_cons = &p_cli->p_ctx->vt100_ctx.cons;

    name_len = cli_strlen(p_cli->p_name);

    return ((buffer_pos + name_len) / p_cons->terminal_wid);
}
#endif


#if NRF_MODULE_ENABLED(NRF_CLI_METAKEYS)
/* Calculates column number of given position in buffer */
static uint32_t cli_col_num_with_buffer_offset_get(nrf_cli_t const * p_cli,
                                                   nrf_cli_cmd_len_t buffer_pos)
{
    uint32_t name_len;
    nrf_cli_multiline_cons_t *p_cons = &p_cli->p_ctx->vt100_ctx.cons;

    name_len = cli_strlen(p_cli->p_name);

    /* columns are counted from 1 */
    return (1 + ((buffer_pos + name_len) % p_cons->terminal_wid));
}
#endif


#if NRF_MODULE_ENABLED(NRF_CLI_METAKEYS)
/* For the given buffer, calculates row span between position2 and position1 */
static int32_t cli_row_span_with_buffer_offsets_get(nrf_cli_t const * p_cli,
                                                    nrf_cli_cmd_len_t offset1,
                                                    nrf_cli_cmd_len_t offset2)
{
    return cli_line_num_with_buffer_offset_get(p_cli, offset2)
            - cli_line_num_with_buffer_offset_get(p_cli, offset1);
}
#endif

#if NRF_MODULE_ENABLED(NRF_CLI_METAKEYS)
/* For the given buffer, calculates column span between position2 and position 1 */
static int32_t cli_column_span_with_buffer_offsets_get(nrf_cli_t const * p_cli,
                                                       nrf_cli_cmd_len_t offset1,
                                                       nrf_cli_cmd_len_t offset2)
{
    return cli_col_num_with_buffer_offset_get(p_cli, offset2)
            - cli_col_num_with_buffer_offset_get(p_cli, offset1);
}
#endif


/* Function sends VT100 command to clear the screen from cursor position to end of the screen. */
static inline void cli_clear_eos(nrf_cli_t const * p_cli)
{
    NRF_CLI_VT100_CMD(p_cli, NRF_CLI_VT100_CLEAREOS);
}

/* Function sends VT100 command to save cursor position. */
static inline void cli_cursor_save(nrf_cli_t const * p_cli)
{
    NRF_CLI_VT100_CMD(p_cli, NRF_CLI_VT100_SAVECURSOR);
}

/* Function sends VT100 command to restore saved cursor position. */
static inline void cli_cursor_restore(nrf_cli_t const * p_cli)
{
    NRF_CLI_VT100_CMD(p_cli, NRF_CLI_VT100_RESTORECURSOR);
}

/* Function forcing new line - cannot be replaced with function cursor_down_move. */
static inline void cursor_next_line_move(nrf_cli_t const * p_cli)
{
    nrf_fprintf(p_cli->p_fprintf_ctx, "\n");
}

/* Function moves cursor left by n positions. */
static inline void cursor_left_move(nrf_cli_t const * p_cli, nrf_cli_cmd_len_t n)
{
    if (n > 0)
    {
        nrf_fprintf(p_cli->p_fprintf_ctx, "\033[%dD", n);
    }
}

/* Function moves cursor right by n positions. */
static inline void cursor_right_move(nrf_cli_t const * p_cli, nrf_cli_cmd_len_t n)
{
    if (n > 0)
    {
        nrf_fprintf(p_cli->p_fprintf_ctx, "\033[%dC", n);
    }
}

#if NRF_MODULE_ENABLED(NRF_CLI_METAKEYS)
/* Moves cursor horizontally by a number. Positive is right */
static void cursor_horiz_move(nrf_cli_t const * p_cli, int32_t delta)
{
    if (delta > 0)
    {
        cursor_right_move(p_cli, delta);
    }
    else if (delta < 0)
    {
        cursor_left_move(p_cli, -delta);
    }
    else { }
}
#endif

/* Function moves cursor up by n positions. */
static inline void cursor_up_move(nrf_cli_t const * p_cli, nrf_cli_cmd_len_t n)
{
    if (n > 0)
    {
        nrf_fprintf(p_cli->p_fprintf_ctx, "\033[%dA", n);
    }
}

/* Function moves cursor down by n positions but it will bring no effect if cursor is in the last
 * line of terminal screen. In such case, the cursor_next_line_move function shall be invoked. */
static inline void cursor_down_move(nrf_cli_t const * p_cli, nrf_cli_cmd_len_t n)
{
    if (n > 0)
    {
         nrf_fprintf(p_cli->p_fprintf_ctx, "\033[%dB", n);
    }
}

#if NRF_MODULE_ENABLED(NRF_CLI_METAKEYS)
/* Moves cursor vertically by a number. Positive is down */
static void cursor_vert_move(nrf_cli_t const * p_cli, int32_t delta)
{
    if (delta > 0)
    {
        cursor_down_move(p_cli, delta);
    }
    else if (delta < 0)
    {
        cursor_up_move(p_cli, -delta);
    }
    else { }
}
#endif

/* Function increments cursor position (if possible) and moves cursor to new line if necessary. */
static void cursor_position_increment(nrf_cli_t const * p_cli)
{
    if (p_cli->p_ctx->cmd_buff_pos >= p_cli->p_ctx->cmd_buff_len)
    {
        return; /* incrementation not possible */
    }

    nrf_cli_multiline_cons_t const * p_cons = multiline_console_data_check(p_cli);
    nrf_cli_cmd_len_t cur_y = p_cons->cur_y;
    ++p_cli->p_ctx->cmd_buff_pos;
    p_cons = multiline_console_data_check(p_cli);

    if (cur_y == p_cons->cur_y)
    {
        cursor_right_move(p_cli, 1);
    }
    else
    {
        cursor_next_line_move(p_cli);
    }
}

/* Function will move cursor back to position == cmd_buff_pos. Example usage is when cursor needs
 * to be moved back after printing some text. This function cannot be used to move cursor to new
 * location by manual change of cmd_buff_pos.*/
static void cursor_position_synchronize(nrf_cli_t const * p_cli)
{
    nrf_cli_multiline_cons_t const * p_cons = multiline_console_data_check(p_cli);
    bool last_line = p_cons->cur_y == p_cons->cur_y_end ? true : false;

    /* In case cursor reaches the bottom line of a terminal, it will be moved to the next line. */
    if (cursor_in_empty_line(p_cli) || full_line_cmd(p_cli))
    {
        cursor_next_line_move(p_cli);
    }

    if (last_line)
    {
        cursor_left_move(p_cli, p_cons->cur_x_end - p_cons->cur_x);
    }
    else
    {
        cursor_up_move(p_cli, p_cons->cur_y_end - p_cons->cur_y);
        if (p_cons->cur_x > p_cons->cur_x_end)
        {
            cursor_right_move(p_cli, p_cons->cur_x - p_cons->cur_x_end);
        }
        else
        {
            cursor_left_move(p_cli, p_cons->cur_x_end - p_cons->cur_x);
        }
    }
}

#if NRF_MODULE_ENABLED(NRF_CLI_METAKEYS)
/**
 *  Removes the "word" to the left of the cursor:
 *  - if there are spaces at the cursor position, remove all spaces to the left
 *  - remove the non-spaces (word) until a space is found or a beginning of buffer
 */
static void cli_cmd_word_remove(nrf_cli_t const * p_cli)
{
    nrf_cli_cmd_len_t new_pos;
    nrf_cli_cmd_len_t chars_to_delete;
    int32_t row_span;
    int32_t col_span;

    /* Line must not be empty and cursor must not be at 0 to continue */
    if ((p_cli->p_ctx->cmd_buff_len == 0) || (p_cli->p_ctx->cmd_buff_pos == 0))
    {
        return;
    }

    /* start at the current position */
    new_pos = p_cli->p_ctx->cmd_buff_pos;
    chars_to_delete = 0;

    /* look back for all spaces then for non-spaces */
    while ((new_pos >= 1) && (p_cli->p_ctx->cmd_buff[new_pos - 1] == ' '))
    {
        ++chars_to_delete;
        --new_pos;
    }

    while ((new_pos >= 1) && (p_cli->p_ctx->cmd_buff[new_pos - 1] != ' '))
    {
        --new_pos;
        ++chars_to_delete;
    }

    /* calculate the new cursor */
    row_span = cli_row_span_with_buffer_offsets_get(p_cli, p_cli->p_ctx->cmd_buff_pos, new_pos);
    col_span = cli_column_span_with_buffer_offsets_get(p_cli, p_cli->p_ctx->cmd_buff_pos, new_pos);

    /* manage the buffer */
    memmove(&p_cli->p_ctx->cmd_buff[new_pos],
            &p_cli->p_ctx->cmd_buff[new_pos + chars_to_delete],
            p_cli->p_ctx->cmd_buff_len - chars_to_delete);
    p_cli->p_ctx->cmd_buff_len -= chars_to_delete;
    p_cli->p_ctx->cmd_buff_pos = new_pos;
    p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_len] = '\0';

    /* update display */
    cursor_horiz_move(p_cli, col_span);
    cursor_vert_move(p_cli, row_span);
    cli_cursor_save(p_cli);
    nrf_cli_fprintf(p_cli,
            NRF_CLI_NORMAL,
            "%s",
            &p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_pos]);
    cli_clear_eos(p_cli);
    cli_cursor_restore(p_cli);
}
#endif

#if NRF_MODULE_ENABLED(NRF_CLI_HISTORY) || NRF_MODULE_ENABLED(NRF_CLI_METAKEYS)
/* Function moves cursor to begin of command position, just after console name. */
static void cursor_home_position_move(nrf_cli_t const * p_cli)
{
    nrf_cli_multiline_cons_t const * p_cons = multiline_console_data_check(p_cli);

    if ((p_cons->cur_x == p_cons->name_len + NRF_CLI_INITIAL_CURS_POS) &&
        (p_cons->cur_y == NRF_CLI_INITIAL_CURS_POS))
    {
        return; /* nothing to handle because cursor is in start position */
    }

    if (p_cons->cur_y > NRF_CLI_INITIAL_CURS_POS)
    {
        cursor_up_move(p_cli, p_cons->cur_y - NRF_CLI_INITIAL_CURS_POS);
    }

    if (p_cons->cur_x > p_cons->name_len)
    {
        cursor_left_move(p_cli, p_cons->cur_x - NRF_CLI_INITIAL_CURS_POS - p_cons->name_len);
    }
    else
    {
        cursor_right_move(p_cli, p_cons->name_len + NRF_CLI_INITIAL_CURS_POS - p_cons->cur_x);
    }
    /* align data buffer pointer with cursor position */
    p_cli->p_ctx->cmd_buff_pos = 0;
}
#endif

/* Function moves cursor to end of command. */
static void cursor_end_position_move(nrf_cli_t const * p_cli)
{
    nrf_cli_multiline_cons_t const * p_cons = multiline_console_data_check(p_cli);

    if ((p_cons->cur_x == p_cons->cur_x_end) && (p_cons->cur_y == p_cons->cur_y_end))
    {
        return; /* nothing to handle because cursor is in end position */
    }

    if (p_cons->cur_y_end > p_cons->cur_y)
    {
        cursor_down_move(p_cli, p_cons->cur_y_end - p_cons->cur_y);
    }

    if (p_cons->cur_x > p_cons->cur_x_end)
    {
        cursor_left_move(p_cli, p_cons->cur_x - p_cons->cur_x_end);
    }
    else
    {
        cursor_right_move(p_cli, p_cons->cur_x_end - p_cons->cur_x);
    }
    /* align data buffer pointer with cursor position */
    p_cli->p_ctx->cmd_buff_pos = p_cli->p_ctx->cmd_buff_len;
}

#if NRF_MODULE_ENABLED(NRF_CLI_BUILD_IN_CMDS)
/* Function reads cursor position from terminal. */
static ret_code_t cursor_position_get(nrf_cli_t const * p_cli)
{
    size_t   cnt;
    uint16_t x = 0; /* horizontal position */
    uint16_t y = 0; /* vertical position */
    char     c = 0;

    nrf_cli_cmd_len_t buff_idx = 0;

    /* clear temp buffer */
    memset(p_cli->p_ctx->temp_buff, 0, sizeof(p_cli->p_ctx->temp_buff));

    /* escape code asking terminal about its size */
    static char const cmd_get_terminal_size[] = "\033[6n";

    nrf_fprintf(p_cli->p_fprintf_ctx, cmd_get_terminal_size);
    /* fprintf buffer needs to be flushed to start sending prepared escape code to the terminal */
    transport_buffer_flush(p_cli);

    /* timeout for terminal response = ~1s */
    for (uint16_t i = 0; i < 1000; i++)
    {
        do
        {
            cli_read(p_cli, &c, sizeof(c), &cnt);
            if (cnt == 0)
            {
                nrf_delay_us(999);
                continue;
            }
            if ((c != NRF_CLI_VT100_ASCII_ESC) &&
                (p_cli->p_ctx->temp_buff[0] != NRF_CLI_VT100_ASCII_ESC))
            {
                continue;
            }

            if (c == 'R') /* end of response from the terminal */
            {
                p_cli->p_ctx->temp_buff[buff_idx] = '\0';
                if (p_cli->p_ctx->temp_buff[1] != '[')
                {
                    p_cli->p_ctx->temp_buff[0] = 0;
                    return NRF_ERROR_INVALID_DATA;
                }
                buff_idx = 2;  /* index start position in the buffer where 'y' is stored */
                while (p_cli->p_ctx->temp_buff[buff_idx] != ';')
                {
                    y = y * 10 + (p_cli->p_ctx->temp_buff[buff_idx++] - '0');
                    if (buff_idx >= NRF_CLI_CMD_BUFF_SIZE)
                    {
                        return NRF_ERROR_DATA_SIZE;
                    }
                }
                if (++buff_idx >= NRF_CLI_CMD_BUFF_SIZE)
                {
                    return NRF_ERROR_DATA_SIZE;
                }
                while (p_cli->p_ctx->temp_buff[buff_idx] != '\0')
                {
                    x = x * 10 + (p_cli->p_ctx->temp_buff[buff_idx++] - '0');
                    if (buff_idx >= NRF_CLI_CMD_BUFF_SIZE)
                    {
                        return NRF_ERROR_DATA_SIZE;
                    }
                }
                /* horizontal cursor position */
                if (x > NRF_CLI_MAX_TERMINAL_SIZE)
                {
                    p_cli->p_ctx->vt100_ctx.cons.cur_x = NRF_CLI_MAX_TERMINAL_SIZE;
                }
                else
                {
                    p_cli->p_ctx->vt100_ctx.cons.cur_x = (nrf_cli_cmd_len_t)x;
                }
                /* vertical cursor position */
                if (y > NRF_CLI_MAX_TERMINAL_SIZE)
                {
                    p_cli->p_ctx->vt100_ctx.cons.cur_y = NRF_CLI_MAX_TERMINAL_SIZE;
                }
                else
                {
                    p_cli->p_ctx->vt100_ctx.cons.cur_y = (nrf_cli_cmd_len_t)y;
                }
                p_cli->p_ctx->temp_buff[0] = 0;
                return NRF_SUCCESS;
            }
            else
            {
                p_cli->p_ctx->temp_buff[buff_idx] = c;
            }

            if (++buff_idx > NRF_CLI_CURSOR_POSITION_BUFFER - 1)
            {
                p_cli->p_ctx->temp_buff[0] = 0;
                /* data_buf[NRF_CLI_CURSOR_POSITION_BUFFER - 1] is reserved for '\0' */
                return NRF_ERROR_NO_MEM;
            }

        } while (cnt > 0);
    }
    return NRF_ERROR_TIMEOUT;
}

/* Function gets terminal width and height. */
static ret_code_t terminal_size_get(nrf_cli_t const *   p_cli,
                                    nrf_cli_cmd_len_t * p_length,
                                    nrf_cli_cmd_len_t * p_height)
{
    ASSERT(p_length);
    ASSERT(p_height);

    uint16_t x;
    uint16_t y;

    if (cursor_position_get(p_cli) == NRF_SUCCESS)
    {
        x = p_cli->p_ctx->vt100_ctx.cons.cur_x;
        y = p_cli->p_ctx->vt100_ctx.cons.cur_y;
        /* assumption: terminal widht and height < 999 */
        cursor_right_move(p_cli, NRF_CLI_MAX_TERMINAL_SIZE); /* move to last column */
        cursor_down_move(p_cli,  NRF_CLI_MAX_TERMINAL_SIZE); /* move to last row */
    }
    else
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    if (cursor_position_get(p_cli) == NRF_SUCCESS)
    {
        *p_length = p_cli->p_ctx->vt100_ctx.cons.cur_x;
        *p_height = p_cli->p_ctx->vt100_ctx.cons.cur_y;
        cursor_left_move(p_cli, *p_length - x);
        cursor_up_move(p_cli, *p_height - y);

        return NRF_SUCCESS;
    }
    return NRF_ERROR_NOT_SUPPORTED;
}
#endif // NRF_MODULE_ENABLED(NRF_CLI_BUILD_IN_CMDS)

#if NRF_MODULE_ENABLED(NRF_CLI_VT100_COLORS)
static void vt100_color_set(nrf_cli_t const * p_cli, nrf_cli_vt100_color_t color)
{
    if (color != NRF_CLI_DEFAULT)
    {
        if (p_cli->p_ctx->vt100_ctx.col.col == color)
        {
            return;
        }

        uint8_t cmd[] = NRF_CLI_VT100_COLOR(color - 1);

        p_cli->p_ctx->vt100_ctx.col.col = color;
        nrf_fprintf(p_cli->p_fprintf_ctx, "%s", cmd);
    }
    else
    {
        static uint8_t const cmd[] = NRF_CLI_VT100_MODESOFF;

        p_cli->p_ctx->vt100_ctx.col.col = color;
        nrf_fprintf(p_cli->p_fprintf_ctx, "%s", cmd);
    }
}

static void vt100_bgcolor_set(nrf_cli_t const * p_cli, nrf_cli_vt100_color_t bgcolor)
{
    if (bgcolor != NRF_CLI_DEFAULT)
    {
        if (p_cli->p_ctx->vt100_ctx.col.bgcol == bgcolor)
        {
            return;
        }
         /* -1 because default value is first in enum */
        uint8_t cmd[] = NRF_CLI_VT100_BGCOLOR(bgcolor - 1);

        p_cli->p_ctx->vt100_ctx.col.bgcol = bgcolor;
        nrf_fprintf(p_cli->p_fprintf_ctx, "%s", cmd);
    }
}

static inline void vt100_colors_store(nrf_cli_t const *        p_cli,
                                      nrf_cli_vt100_colors_t * p_color)
{
    memcpy(p_color, &p_cli->p_ctx->vt100_ctx.col, sizeof(nrf_cli_vt100_colors_t));
}

static void vt100_colors_restore(nrf_cli_t const *              p_cli,
                                 nrf_cli_vt100_colors_t const * p_color)
{
    vt100_color_set(p_cli, p_color->col);
    vt100_bgcolor_set(p_cli, p_color->bgcol);
}
#endif // NRF_MODULE_ENABLED(NRF_CLI_VT100_COLORS)

static void left_arrow_handle(nrf_cli_t const * p_cli)
{
    nrf_cli_multiline_cons_t const * p_cons = multiline_console_data_check(p_cli);

    if ((p_cons->cur_x == p_cons->name_len + NRF_CLI_INITIAL_CURS_POS) &&
        (p_cons->cur_y == NRF_CLI_INITIAL_CURS_POS))
    {
        return; /* nothing to handle because cursor is in start position */
    }

    if (p_cons->cur_x == NRF_CLI_INITIAL_CURS_POS)
    {   /* go to previous line */
        cursor_up_move(p_cli, 1);
        cursor_right_move(p_cli, p_cons->terminal_wid);
        --p_cli->p_ctx->cmd_buff_pos;
    }
    else
    {
        cursor_left_move(p_cli, 1);
        --p_cli->p_ctx->cmd_buff_pos;
    }
}

static void right_arrow_handle(nrf_cli_t const * p_cli)
{
    nrf_cli_multiline_cons_t const * p_cons = multiline_console_data_check(p_cli);

    if ((p_cons->cur_x == p_cons->cur_x_end) &&
        (p_cons->cur_y == p_cons->cur_y_end))
    {
        return; /* nothing to handle because cursor is in start position */
    }

    if (p_cons->cur_x == p_cons->terminal_wid) /* go to next line */
    {
        cursor_down_move(p_cli, 1);
        cursor_left_move(p_cli, p_cons->terminal_wid);
        ++p_cli->p_ctx->cmd_buff_pos;
    }
    else
    {
        cursor_right_move(p_cli, 1);
        ++p_cli->p_ctx->cmd_buff_pos;
    }
}

static inline void  char_insert_echo_off(nrf_cli_t const * p_cli, char data)
{
    if (p_cli->p_ctx->cmd_buff_len >= (NRF_CLI_CMD_BUFF_SIZE - 1))
    {
        return;
    }

    p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_pos++] = data;
    p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_pos] = '\0';
    ++p_cli->p_ctx->cmd_buff_len;
}

static void char_insert(nrf_cli_t const * p_cli, char data)
{
    nrf_cli_cmd_len_t diff;
    bool ins_mode = (bool)p_cli->p_ctx->internal.flag.insert_mode;

    diff = p_cli->p_ctx->cmd_buff_len - p_cli->p_ctx->cmd_buff_pos;

    if (!ins_mode)
    {
        if (p_cli->p_ctx->cmd_buff_len >= (NRF_CLI_CMD_BUFF_SIZE - 1))
        {
            return;
        }
        if (diff > 0)
        {
            memmove(&p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_pos + 1],
                    &p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_pos],
                    diff);
        }
    }
    else
    {
        if ((p_cli->p_ctx->cmd_buff_len >= (NRF_CLI_CMD_BUFF_SIZE - 1)) &&
            (diff == 0))
        {
            /* If cmd buffer is full, it is possible to replace chars but adding new
               is not allowed. */
            return;
        }
    }

    p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_pos] = data;

    if (!ins_mode)
    {
        p_cli->p_ctx->cmd_buff[++p_cli->p_ctx->cmd_buff_len] = '\0';
    }

    if (diff > 0)
    {
        nrf_cli_multiline_cons_t const * p_cons = multiline_console_data_check(p_cli);
        bool last_line = p_cons->cur_y == p_cons->cur_y_end ? true : false;

        /* Below if-else statement is to minimize esc codes transmission. */
        if (last_line)
        {
            nrf_cli_fprintf(p_cli,
                            NRF_CLI_NORMAL,
                            "%s",
                            &p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_pos]);
            /* Move cursor one position left less in case of insert mode. */
            cursor_left_move(p_cli, diff - ins_mode);
        }
        else
        {
            /* Save the current cursor position in order to get back after fprintf function. */
            cli_cursor_save(p_cli);
            nrf_cli_fprintf(p_cli,
                            NRF_CLI_NORMAL,
                            "%s",
                            &p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_pos]);
            cli_cursor_restore(p_cli);
            /* Move cursor right by one position to edit the next character. */
            cursor_right_move(p_cli, 1);
        }
    }
    else
    {
        /* New char appended at the end of buffer. */
        if (ins_mode)
        {
            p_cli->p_ctx->cmd_buff[++p_cli->p_ctx->cmd_buff_len] = '\0';
        }
        cli_putc(p_cli, data);
    }

    /* Incrementation needs to be executed before invoking function: cursor_in_empty_line. */
    ++p_cli->p_ctx->cmd_buff_pos;

    /* Forcing terminal to switch to a new line if the command is too long. */
    if (cursor_in_empty_line(p_cli))
    {
        cursor_next_line_move(p_cli);
        return;
    }

    if (full_line_cmd(p_cli))
    {
        nrf_cli_multiline_cons_t const * p_cons = multiline_console_data_check(p_cli);

        /* The code below will force the terminal to scroll one line down when the currently entered command
         * reaches lower right corner of the terminal screen. */
        cursor_down_move(p_cli, p_cons->cur_y_end - p_cons->cur_y - 1);
        cursor_next_line_move(p_cli);
        cursor_up_move(p_cli, p_cons->cur_y_end - p_cons->cur_y);
        cursor_right_move(p_cli, p_cons->cur_x - 1);
        return;
    }
}

static void char_backspace(nrf_cli_t const * p_cli)
{
    nrf_cli_cmd_len_t diff;

    if ((p_cli->p_ctx->cmd_buff_len == 0) || (p_cli->p_ctx->cmd_buff_pos == 0))
    {
        return;
    }

    diff = p_cli->p_ctx->cmd_buff_len - p_cli->p_ctx->cmd_buff_pos;

    memmove(&p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_pos - 1],
            &p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_pos],
            diff + 1);

    --p_cli->p_ctx->cmd_buff_pos;
    --p_cli->p_ctx->cmd_buff_len;

    if (diff > 0)
    {
        cli_putc(p_cli, NRF_CLI_VT100_ASCII_BSPACE);

        nrf_cli_multiline_cons_t const * p_cons = multiline_console_data_check(p_cli);
        bool last_line = p_cons->cur_y == p_cons->cur_y_end ? true : false;

        if (last_line)
        {
            nrf_cli_fprintf(p_cli,
                            NRF_CLI_NORMAL,
                            "%s",
                            &p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_pos]);
            cli_clear_eos(p_cli);
            cursor_left_move(p_cli, diff);
        }
        else
        {
            /* If cursor is not in last cmd line, its position needs to be saved by
             * VT100 command. */
            cli_cursor_save(p_cli);
            cli_clear_eos(p_cli);
            nrf_cli_fprintf(p_cli,
                            NRF_CLI_NORMAL,
                            "%s",
                            &p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_pos]);
            cli_cursor_restore(p_cli);
        }
    }
    else
    {
        static char const cmd_bspace[] = {
            NRF_CLI_VT100_ASCII_BSPACE, ' ', NRF_CLI_VT100_ASCII_BSPACE, '\0'};
        nrf_fprintf(p_cli->p_fprintf_ctx, "%s", cmd_bspace);
    }
}

static void char_delete(nrf_cli_t const * p_cli)
{
    nrf_cli_cmd_len_t diff;

    diff = p_cli->p_ctx->cmd_buff_len - p_cli->p_ctx->cmd_buff_pos;

    if (diff == 0)
    {
        return;
    }

    memmove(&p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_pos],
            &p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_pos + 1],
            diff);

    --p_cli->p_ctx->cmd_buff_len;

    nrf_cli_multiline_cons_t const * p_cons = multiline_console_data_check(p_cli);
    bool last_line = p_cons->cur_y == p_cons->cur_y_end ? true : false;

    /* If last line of command is edited, there is no need for saving cursor position. */
    if (last_line)
    {
        nrf_cli_fprintf(p_cli,
                        NRF_CLI_NORMAL,
                        "%s",
                        &p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_pos]);
        NRF_CLI_VT100_CMD(p_cli, NRF_CLI_VT100_CLEAREOL);
        cursor_left_move(p_cli, --diff);
    }
    else
    {
        cli_cursor_save(p_cli);
        cli_clear_eos(p_cli);
        nrf_cli_fprintf(p_cli,
                        NRF_CLI_NORMAL,
                        "%s",
                        &p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_pos]);
        cli_cursor_restore(p_cli);
    }
}

static char make_argv(size_t * p_argc, char ** pp_argv, char * p_cmd, uint8_t max_argc)
{
    char c;
    char quote = 0;

    *p_argc = 0;
    do
    {
        c = *p_cmd;
        if (c == '\0')
        {
            break;
        }

        if (isspace((int)c))
        {
            *p_cmd++ = '\0';
            continue;
        }

        pp_argv[(*p_argc)++] = p_cmd;
        quote = 0;

        while (1)
        {
            c = *p_cmd;

            if (c == '\0')
            {
                break;
            }

            if (!quote)
            {
                switch (c)
                {
                    case '\\':
                        memmove(p_cmd, p_cmd + 1, cli_strlen(p_cmd));
                        p_cmd += 1;
                        continue;

                    case '\'':
                    case '\"':
                        memmove(p_cmd, p_cmd + 1, cli_strlen(p_cmd));
                        quote = c;
                        continue;
                    default:
                        break;
                }
            }

            if (quote == c)
            {
                memmove(p_cmd, p_cmd + 1, cli_strlen(p_cmd));
                quote = 0;
                continue;
            }

            if (quote && c == '\\')
            {
                char t = *(p_cmd + 1);

                if (t == quote)
                {
                    memmove(p_cmd, p_cmd + 1, cli_strlen(p_cmd));
                    p_cmd += 1;
                    continue;
                }

                if (t == '0')
                {
                    uint8_t i;
                    uint8_t v = 0;

                    for (i = 2; i < (2 + 3); i++)
                    {
                        t = *(p_cmd + i);

                        if (t >= '0' && t <= '7')
                        {
                            v = (v << 3) | (t - '0');
                        }
                        else
                        {
                            break;
                        }
                    }

                    if (i > 2)
                    {
                        memmove(p_cmd, p_cmd + (i - 1), cli_strlen(p_cmd) - (i - 2));
                        *p_cmd++ = v;
                        continue;
                    }
                }

                if (t == 'x')
                {
                    uint8_t i;
                    uint8_t v = 0;

                    for (i = 2; i < (2 + 2); i++)
                    {
                        t = *(p_cmd + i);

                        if (t >= '0' && t <= '9')
                        {
                            v = (v << 4) | (t - '0');
                        }
                        else if (t >= 'a' && t <= 'f')
                        {
                            v = (v << 4) | (t - 'a' + 10);
                        }
                        else if (t >= 'A' && t <= 'F')
                        {
                            v = (v << 4) | (t - 'A' + 10);
                        }
                        else
                        {
                            break;
                        }
                    }

                    if (i > 2)
                    {
                        memmove(p_cmd, p_cmd + (i - 1), cli_strlen(p_cmd) - (i - 2));
                        *p_cmd++ = v;
                        continue;
                    }
                }
            }
            if (!quote && isspace((int)c))
            {
                break;
            }

            p_cmd += 1;
        }
    } while (*p_argc < max_argc);

    ASSERT(*p_argc <= NRF_CLI_ARGC_MAX);
    pp_argv[*p_argc] = 0;

    return quote;
}

static void cli_state_set(nrf_cli_t const * p_cli, nrf_cli_state_t state)
{
    p_cli->p_ctx->state = state;

    if (state == NRF_CLI_STATE_ACTIVE)
    {
            cli_cmd_buffer_clear(p_cli);
            nrf_cli_fprintf(p_cli, NRF_CLI_INFO, "%s", p_cli->p_name);
    }
}

#if NRF_MODULE_ENABLED(NRF_CLI_HISTORY)
static inline void history_mode_exit(nrf_cli_t const * p_cli)
{
    p_cli->p_ctx->p_cmd_list_element = NULL;
}

static void history_handle(nrf_cli_t const * p_cli, bool up)
{
    nrf_cli_memobj_header_t header = {
        .p_prev = NULL,
        .p_next = NULL,
        .cmd_len = 0
    };
    nrf_cli_cmd_len_t current_cmd_len;
    bool skip = false;

    if (!up) /* button down */
    {
        if (p_cli->p_ctx->p_cmd_list_element == NULL)
        {
            return;
        }
        cursor_home_position_move(p_cli);

        nrf_memobj_read(p_cli->p_ctx->p_cmd_list_element,
                        &header,
                        NRF_CLI_HISTORY_HEADER_SIZE,
                        0);

        p_cli->p_ctx->p_cmd_list_element = header.p_next;
        current_cmd_len = p_cli->p_ctx->cmd_buff_len;

        if (p_cli->p_ctx->p_cmd_list_element == NULL)
        {
            if (cli_strlen(p_cli->p_ctx->temp_buff) > 0)
            {
                strcpy(p_cli->p_ctx->cmd_buff, p_cli->p_ctx->temp_buff);
            }
            else
            {
                p_cli->p_ctx->cmd_buff[0] = '\0';
            }
            header.cmd_len = cli_strlen(p_cli->p_ctx->cmd_buff);
            skip = true;
        }
    }
    else /* button up */
    {
        if ((p_cli->p_ctx->p_cmd_list_element == p_cli->p_ctx->p_cmd_list_tail) ||
            (p_cli->p_ctx->p_cmd_list_head == NULL))
        {
            /* Nothing to display. */
            return;
        }
        cursor_home_position_move(p_cli);

        if (p_cli->p_ctx->p_cmd_list_element == NULL)
        {
            current_cmd_len = cli_strlen(p_cli->p_ctx->cmd_buff);

            p_cli->p_ctx->p_cmd_list_element = p_cli->p_ctx->p_cmd_list_head;
            /* Save the currently entered and not executed command. */
            if (current_cmd_len > 0)
            {
                strcpy(p_cli->p_ctx->temp_buff, p_cli->p_ctx->cmd_buff);
            }
            else
            {
                p_cli->p_ctx->temp_buff[0] = '\0';
            }
        }
        else
        {
            nrf_memobj_read(p_cli->p_ctx->p_cmd_list_element,
                            &header,
                            NRF_CLI_HISTORY_HEADER_SIZE,
                            0);
            current_cmd_len = header.cmd_len;
            p_cli->p_ctx->p_cmd_list_element = header.p_prev;
        }
    }
    if (!skip)
    {
        nrf_memobj_read(p_cli->p_ctx->p_cmd_list_element,
                        &header,
                        NRF_CLI_HISTORY_HEADER_SIZE,
                        0);

        nrf_memobj_read(p_cli->p_ctx->p_cmd_list_element,
                        p_cli->p_ctx->cmd_buff,
                        header.cmd_len + 1, /* +1 for '\0' */
                        NRF_CLI_HISTORY_HEADER_SIZE);
    }

    p_cli->p_ctx->cmd_buff_pos = header.cmd_len;
    p_cli->p_ctx->cmd_buff_len = header.cmd_len;

    if (current_cmd_len > header.cmd_len)
    {
        cli_clear_eos(p_cli);
    }

    nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "%s", p_cli->p_ctx->cmd_buff);
    if (cursor_in_empty_line(p_cli) || full_line_cmd(p_cli))
    {
        cursor_next_line_move(p_cli);
    }
}

static void history_list_element_add(nrf_cli_t const * p_cli, nrf_memobj_t * p_memobj)
{
    ASSERT(p_memobj != NULL);

    nrf_cli_memobj_header_t header;

    if (p_cli->p_ctx->p_cmd_list_head == NULL)
    {
        p_cli->p_ctx->p_cmd_list_head = p_memobj;
        p_cli->p_ctx->p_cmd_list_tail = p_memobj;
        header.p_prev = NULL;
        header.p_next = NULL;
        header.cmd_len = p_cli->p_ctx->cmd_buff_len;
    }
    else
    {
        nrf_memobj_read(p_cli->p_ctx->p_cmd_list_head,
                        &header,
                        NRF_CLI_HISTORY_HEADER_SIZE,
                        0);

        header.p_next = p_memobj;

        nrf_memobj_write(p_cli->p_ctx->p_cmd_list_head,
                         &header,
                         NRF_CLI_HISTORY_HEADER_SIZE,
                         0);

        header.p_next = NULL;
        header.p_prev = p_cli->p_ctx->p_cmd_list_head;
        header.cmd_len = p_cli->p_ctx->cmd_buff_len;

        p_cli->p_ctx->p_cmd_list_head = p_memobj;
    }

    nrf_memobj_write(p_memobj,
                     &header,
                     NRF_CLI_HISTORY_HEADER_SIZE,
                     0);

    nrf_memobj_write(p_memobj,
                     p_cli->p_ctx->cmd_buff,
                     p_cli->p_ctx->cmd_buff_len + 1, /* +1 for '\0' */
                     NRF_CLI_HISTORY_HEADER_SIZE);
}

static void history_list_element_oldest_remove(nrf_cli_t const * p_cli)
{
    if (p_cli->p_ctx->p_cmd_list_tail == NULL)
    {
        return; // nothing to do
    }

    nrf_cli_memobj_header_t header;
    nrf_memobj_t * p_memobj = p_cli->p_ctx->p_cmd_list_tail;

    nrf_memobj_read(p_memobj,
                    &header,
                    NRF_CLI_HISTORY_HEADER_SIZE,
                    0);

    p_cli->p_ctx->p_cmd_list_tail = header.p_next;
    memset(&header, 0, sizeof(nrf_cli_memobj_header_t));
    nrf_memobj_write(p_memobj, &header, NRF_CLI_HISTORY_HEADER_SIZE, 0);
    nrf_memobj_free(p_memobj);

    /* Checking if memory objects list is empty. */
    if (p_cli->p_ctx->p_cmd_list_tail == NULL)
    {
        p_cli->p_ctx->p_cmd_list_head = NULL;
        return;
    }

    nrf_memobj_read(p_cli->p_ctx->p_cmd_list_tail,
                    &header,
                    NRF_CLI_HISTORY_HEADER_SIZE,
                    0);

    header.p_prev = NULL;
    nrf_memobj_write(p_cli->p_ctx->p_cmd_list_tail, &header, NRF_CLI_HISTORY_HEADER_SIZE, 0);
}

static void history_list_free_memory(nrf_cli_t const * p_cli)
{
    while (p_cli->p_ctx->p_cmd_list_tail != NULL)
    {
        history_list_element_oldest_remove(p_cli);
    }
}

static void history_save(nrf_cli_t const * p_cli)
{
    nrf_cli_cmd_len_t cmd_new_len = cli_strlen(p_cli->p_ctx->cmd_buff);

    history_mode_exit(p_cli);

    if (cmd_new_len == 0)
    {
        return;
    }

    /* Checking if newly entered command is not duplicated with previous one. */
    if (p_cli->p_ctx->p_cmd_list_head != NULL)
    {
        nrf_cli_memobj_header_t header;

        nrf_memobj_read(p_cli->p_ctx->p_cmd_list_head,
                        &header,
                        NRF_CLI_HISTORY_HEADER_SIZE,
                        0);
        if (cmd_new_len == header.cmd_len)
        {
            nrf_memobj_read(p_cli->p_ctx->p_cmd_list_head,
                            p_cli->p_ctx->temp_buff,
                            header.cmd_len + 1, /* +1 for '\0' */
                            NRF_CLI_HISTORY_HEADER_SIZE);

            if (strcmp(p_cli->p_ctx->cmd_buff, p_cli->p_ctx->temp_buff) == 0)
            {
                /* Duplicated command, nothing to save. */
                p_cli->p_ctx->temp_buff[0] = '\0';
                return;
            }
            p_cli->p_ctx->temp_buff[0] = '\0';
        }
    }

    for (size_t idx = 0; idx < NRF_CLI_HISTORY_ELEMENT_COUNT; idx++)
    {
        nrf_memobj_t * p_memobj;

        p_memobj = nrf_memobj_alloc(p_cli->p_cmd_hist_mempool,
                                    ((size_t)NRF_CLI_HISTORY_HEADER_SIZE + cmd_new_len + 1));
        if (p_memobj != NULL)
        {
            history_list_element_add(p_cli, p_memobj);
            return;
        }
        else
        {
            history_list_element_oldest_remove(p_cli);
        }
    }
    return;
}
#endif // NRF_MODULE_ENABLED(NRF_CLI_HISTORY)

/* Function checks how many identical characters have two strings starting from the first character. */
static nrf_cli_cmd_len_t str_similarity_check(char const * str_a, char const * str_b)
{
    nrf_cli_cmd_len_t cnt = 0;

    while (str_a[cnt] != '\0')
    {
        if (str_a[cnt] != str_b[cnt])
        {
            return cnt;
        }

        if (++cnt == 0)
        {
            return --cnt; /* too long strings */
        }
    }
    return cnt;
}

static void completion_insert(nrf_cli_t const * p_cli,
                              char const *      p_compl,
                              nrf_cli_cmd_len_t compl_len)
{
    ASSERT (p_compl);

    nrf_cli_cmd_len_t diff = p_cli->p_ctx->cmd_buff_len - p_cli->p_ctx->cmd_buff_pos;

    if ((p_cli->p_ctx->cmd_buff_len + compl_len > NRF_CLI_CMD_BUFF_SIZE - 1) ||
        (compl_len == 0))
    {
        return;
    }

    /* Make space for completion. */
    memmove(&p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_pos + compl_len],
            &p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_pos],
            diff + 1); /* + 1 for '\0' */

    /* Insert completion. */
    memmove(&p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_pos],
            p_compl,
            compl_len);

    p_cli->p_ctx->cmd_buff_len = cli_strlen(p_cli->p_ctx->cmd_buff);
    nrf_cli_fprintf(p_cli,
                    NRF_CLI_NORMAL,
                    "%s",
                    &p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_pos]);
    p_cli->p_ctx->cmd_buff_pos += compl_len;

    if (cursor_in_empty_line(p_cli) || full_line_cmd(p_cli))
    {
        cursor_next_line_move(p_cli);
    }

    if (diff > 0)
    {
        cursor_position_synchronize(p_cli);
    }
}

static void option_print(nrf_cli_t const * p_cli,
                         char const *      p_option,
                         nrf_cli_cmd_len_t longest_option)
{
    static char const * tab = "  ";

    /* Function initialization has been requested. */
    if (p_option == NULL)
    {
        p_cli->p_ctx->vt100_ctx.printed_cmd = 0;
        return;
    }
    longest_option += cli_strlen(tab);

    nrf_cli_cmd_len_t columns =
        (p_cli->p_ctx->vt100_ctx.cons.terminal_wid - cli_strlen(tab)) / longest_option;
    nrf_cli_cmd_len_t diff = longest_option - cli_strlen(p_option);

    if (p_cli->p_ctx->vt100_ctx.printed_cmd++ % columns == 0)
    {
        nrf_cli_fprintf(p_cli, NRF_CLI_OPTION, "\n%s%s", tab, p_option);
    }
    else
    {
        nrf_cli_fprintf(p_cli, NRF_CLI_OPTION, "%s", p_option);
    }
    cursor_right_move(p_cli, diff);
}

static inline bool is_completion_candidate(const char *candidate,
                                           const char *str,
                                           size_t len)
{
	return (strncmp(candidate, str, len) == 0) ? true : false;
}

static void cli_tab_handle(nrf_cli_t const * p_cli)
{
    size_t cmd_idx;
    size_t cmd_last = 0;
    size_t cmd_first = 0;
    size_t cmd_cnt = 0;

    size_t argc;
    char * argv[NRF_CLI_ARGC_MAX + 1]; /* +1 reserved for NULL in function make_argv */

    nrf_cli_cmd_len_t cmd_lvl = NRF_CLI_CMD_ROOT_LVL;
    nrf_cli_cmd_len_t cmd_longest = 0; /* longest matching command */

    /* Calculating the longest possible completion length. -1 for '\0'. */
    nrf_cli_cmd_len_t compl_len = (NRF_CLI_CMD_BUFF_SIZE - 1) - p_cli->p_ctx->cmd_buff_len;

    if (compl_len == 0)
    {
        return;
    }

    /* Copy command from its beginning to cursor position. */
    memcpy(p_cli->p_ctx->temp_buff,
           p_cli->p_ctx->cmd_buff,
           p_cli->p_ctx->cmd_buff_pos);

    p_cli->p_ctx->temp_buff[p_cli->p_ctx->cmd_buff_pos] = '\0';

    /* Check if the current cursor position points to the 'space' character. */
    bool space = isspace((int)p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_pos - 1]);

#if NRF_MODULE_ENABLED(NRF_CLI_HISTORY)
    /* If the Tab key is pressed, "history mode" must be terminated because tab and history handlers
       are sharing the same array: temp_buff. */
    history_mode_exit(p_cli);
#endif

    /* Create argument list. */
    (void)make_argv(&argc,
                    &argv[0],
                    p_cli->p_ctx->temp_buff,
                    NRF_CLI_ARGC_MAX);

    nrf_cli_cmd_len_t arg_len = cli_strlen(argv[cmd_lvl]);

    /* Variable 'static_entry' is needed to handle dynamic commands. */
    nrf_cli_static_entry_t static_entry;

    nrf_cli_cmd_entry_t const * p_cmd = NULL;
    nrf_cli_static_entry_t const * p_st_cmd = NULL;
    nrf_cli_static_entry_t const * p_st_cmd_last = NULL;

    do
    {
        if ((argc == 0) ||
            (cmd_lvl >= argc - 1 + space))
        {
            if (space)
            {
                arg_len = 0;
            }
            else
            {
                arg_len = cli_strlen(argv[cmd_lvl]);
            }

            cmd_idx = 0;

            while (1)
            {
                cmd_get(p_cmd, cmd_lvl, cmd_idx++, &p_st_cmd, &static_entry);

                if (p_st_cmd == NULL)
                {
                    /* No more commands available. */
                    break;
                }

                if (!is_completion_candidate(argv[cmd_lvl],
                                             p_st_cmd->p_syntax,
                                             arg_len))
                {
                    continue;
                }

                cmd_cnt++;

                if (p_st_cmd_last == NULL)
                {
                    cmd_first = cmd_idx - 1;
                    cmd_longest = cli_strlen(p_st_cmd->p_syntax);
                    if (compl_len > (cmd_longest - arg_len))
                    {
                        compl_len = cmd_longest - arg_len;
                    }
                }
                else
                {
                    nrf_cli_cmd_len_t len = cli_strlen(p_st_cmd->p_syntax);
                    if (len > cmd_longest)
                    {
                        cmd_longest = len;
                    }

                    if (compl_len > 0)  /* Checking if partial completion is possible */
                    {
                        nrf_cli_static_entry_t last_entry;
                        cmd_get(p_cmd, cmd_lvl, cmd_last, &p_st_cmd_last, &last_entry);

                        len = str_similarity_check(p_st_cmd->p_syntax + arg_len,
                                                   p_st_cmd_last->p_syntax + arg_len);
                        if (compl_len > len)
                        {
                            /* Determining the longest possible completion. */
                            compl_len = len;
                        }
                    }
                }
                cmd_last = cmd_idx - 1;
                p_st_cmd_last = p_st_cmd;

                if (cmd_idx == 0) /* Too many possibilities */
                {
                    nrf_cli_warn(p_cli, NRF_CLI_MSG_TAB_OVERFLOWED);
                    break;
                }
            }
        }
        else
        {
            cmd_idx = 0;

            while (1)
            {
                cmd_get(p_cmd, cmd_lvl, cmd_idx++, &p_st_cmd, &static_entry);

                if (cmd_idx == 0)
                {
                    /* No match found and commands counter overflowed. */
                    nrf_cli_warn(p_cli, NRF_CLI_MSG_TAB_OVERFLOWED);
                    return;
                }

                if (p_st_cmd == NULL) /* No more commands available */
                {
                    return;
                }

#if NRF_MODULE_ENABLED(NRF_CLI_WILDCARD)
                /* Ignore wildcard character arguments if they are "standalone". Example:
                    1. log enable info b*<tab>  -> "b*"  is treated as a command so no match found
                    2. log enable info b* <tab> -> "b* " is ignored, <tab> will prompt all available
                                                   commands. */
                if (wildcard_character_exist(argv[cmd_lvl]))
                {
                    break;
                }
#endif
                /* Fuction "strcmp" is used because an exact match is required. */
                if (strcmp(argv[cmd_lvl], p_st_cmd->p_syntax) == 0)
                {
                    p_cmd = p_st_cmd->p_subcmd;
                    break;
                }
            }
        }

        if ((p_cmd == NULL) || (p_st_cmd == NULL))
        {
            break;
        }

    } while (++cmd_lvl < argc + space);

    if (cmd_cnt == 0)
    {
        /* No match found. */
        return;
    }

    if (cmd_cnt == 1) /* only one match found */
    {
        if (p_cmd->is_dynamic)
        {
            /* In case of dynamic entry, function cmd_get shall be called again for matching
             * command index (cmd_last). It is because static_entry is most likely appended by
             * not valid data.
             */
            cmd_get(p_cmd, cmd_lvl, cmd_last, &p_st_cmd_last, &static_entry);
        }
        if (cli_strlen(p_st_cmd_last->p_syntax) != arg_len) /* no exact match found */
        {
            completion_insert(p_cli, p_st_cmd_last->p_syntax + arg_len, compl_len);
        }

        /* Next character in the buffer is not 'space'. */
        if (!isspace((int)p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_pos]))
        {
            if (p_cli->p_ctx->internal.flag.insert_mode)
            {
                p_cli->p_ctx->internal.flag.insert_mode = 0;
                char_insert(p_cli, ' ');
                p_cli->p_ctx->internal.flag.insert_mode = 1;
            }
            else
            {
                char_insert(p_cli, ' ');
            }
        }
        else
        {
            /*  case:
                | | -> cursor
                cons_name $: valid_cmd valid_sub_cmd| |argument  <tab>
             */
            cursor_position_increment(p_cli);
            /* result:
               cons_name $: valid_cmd valid_sub_cmd |a|rgument
             */
        }
        return;
    }

    /* Printing all matching commands (options). */
    option_print(p_cli, NRF_CLI_INIT_OPTION_PRINTER, cmd_longest);
    cmd_idx = cmd_first;
    while (cmd_cnt)
    {
        cmd_get(p_cmd, cmd_lvl, cmd_idx++, &p_st_cmd, &static_entry);
        if (!is_completion_candidate(argv[cmd_lvl],
                                     p_st_cmd->p_syntax,
                                     arg_len))
        {
            continue;
        }
        cmd_cnt--;
        option_print(p_cli, p_st_cmd->p_syntax, cmd_longest);
    }

    nrf_cli_fprintf(p_cli, NRF_CLI_INFO, "\n%s", p_cli->p_name);
    nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "%s", p_cli->p_ctx->cmd_buff);

    cursor_position_synchronize(p_cli);
    completion_insert(p_cli, p_st_cmd_last->p_syntax + arg_len, compl_len);
}

/* Functions returns true if new line character shall be processed */
static bool process_nl(nrf_cli_t const * p_cli, uint8_t data)
{
    if ((data != '\r') && (data != '\n'))
    {
        cli_flag_last_nl_set(p_cli, 0);
        return false;
    }

    if ((cli_flag_last_nl_get(p_cli) == 0) ||
        (data == cli_flag_last_nl_get(p_cli)))
    {
        cli_flag_last_nl_set(p_cli, data);
        return true;
    }

    return false;
}

#define NRF_CLI_ASCII_MAX_CHAR (127u)
static inline ret_code_t ascii_filter(char const data)
{
    return (uint8_t)data > NRF_CLI_ASCII_MAX_CHAR ? NRF_ERROR_INVALID_DATA : NRF_SUCCESS;
}

static void cli_state_collect(nrf_cli_t const * p_cli)
{
    size_t count = 0;
    char data;

    while (1)
    {
        cli_read(p_cli, &data, sizeof(data), &count);
        if (count == 0)
        {
            return;
        }

        if (ascii_filter(data) != NRF_SUCCESS)
        {
            continue;
        }

#if NRF_MODULE_ENABLED(NRF_PWR_MGMT)
        nrf_pwr_mgmt_feed();
#endif

        switch (p_cli->p_ctx->receive_state)
        {
            case NRF_CLI_RECEIVE_DEFAULT:
                if (process_nl(p_cli, data))
                {
                    if (p_cli->p_ctx->cmd_buff_len == 0)
                    {
                        history_mode_exit(p_cli);
                        cursor_next_line_move(p_cli);
                    }
                    else
                    {
                        /* Command execution */
                        cli_execute(p_cli);
                    }

                    cli_state_set(p_cli, NRF_CLI_STATE_ACTIVE);
                    return;
                }
                switch (data)
                {
                    case NRF_CLI_VT100_ASCII_ESC:       /* ESCAPE */
                        receive_state_change(p_cli, NRF_CLI_RECEIVE_ESC);
                        break;
                    case '\0':
                        break;
#if NRF_MODULE_ENABLED(NRF_CLI_METAKEYS)
                    case NRF_CLI_VT100_ASCII_CTRL_A:    /* CTRL + A */
                        cursor_home_position_move(p_cli);
                        break;
                    case NRF_CLI_VT100_ASCII_CTRL_C:    /* CTRL + C */
                        cursor_end_position_move(p_cli);
                        if (!cursor_in_empty_line(p_cli))
                        {
                            cursor_next_line_move(p_cli);
                        }
                        cli_state_set(p_cli, NRF_CLI_STATE_ACTIVE);
                        break;
                    case NRF_CLI_VT100_ASCII_CTRL_E:    /* CTRL + E */
                        cursor_end_position_move(p_cli);
                        break;
                    case NRF_CLI_VT100_ASCII_CTRL_L:    /* CTRL + L */
                        NRF_CLI_VT100_CMD(p_cli, NRF_CLI_VT100_CURSORHOME);
                        NRF_CLI_VT100_CMD(p_cli, NRF_CLI_VT100_CLEARSCREEN);
                        nrf_cli_fprintf(p_cli, NRF_CLI_INFO, "%s", p_cli->p_name);
                        if (cli_flag_echo_is_set(p_cli))
                        {
                            nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "%s", p_cli->p_ctx->cmd_buff);
                            cursor_position_synchronize(p_cli);
                        }
                        break;
                    case NRF_CLI_VT100_ASCII_CTRL_U:    /* CTRL + U */
                        cursor_home_position_move(p_cli);
                        cli_cmd_buffer_clear(p_cli);
                        cli_clear_eos(p_cli);
                        break;
                    case NRF_CLI_VT100_ASCII_CTRL_W:    /* CTRL + W */
                        cli_cmd_word_remove(p_cli);
                        break;
#endif
                    case '\t':                          /* TAB */
                        if (cli_flag_echo_is_set(p_cli))
                        {
                            cli_tab_handle(p_cli);
                        }
                        break;
                    case NRF_CLI_VT100_ASCII_BSPACE:    /* BACKSPACE */
                        if (cli_flag_echo_is_set(p_cli))
                        {
                            char_backspace(p_cli);
                        }
                        break;
                    case NRF_CLI_VT100_ASCII_DEL:       /* DELETE */
                        if (cli_flag_echo_is_set(p_cli))
                        {
                            char_delete(p_cli);
                        }
                        break;
                    default:
                        if (isprint((int)data))
                        {
                            if (cli_flag_echo_is_set(p_cli))
                            {
                                char_insert(p_cli, data);
                            }
                            else
                            {
                                char_insert_echo_off(p_cli, data);
                            }
                        }
                        break;
                }
                break;
            case NRF_CLI_RECEIVE_ESC:
                if (data == '[')
                {
                    receive_state_change(p_cli, NRF_CLI_RECEIVE_ESC_SEQ);
                }
                else
                {
                    receive_state_change(p_cli, NRF_CLI_RECEIVE_DEFAULT);
                }
                break;
            case NRF_CLI_RECEIVE_ESC_SEQ:
                receive_state_change(p_cli, NRF_CLI_RECEIVE_DEFAULT);

                if (!cli_flag_echo_is_set(p_cli))
                {
                    return;
                }

                switch (data)
                {
#if NRF_MODULE_ENABLED(NRF_CLI_HISTORY)
                    case 'A': /* UP arrow */
                        history_handle(p_cli, true);
                        break;
                    case 'B': /* DOWN arrow */
                        history_handle(p_cli, false);
                        break;
#endif
                    case 'C': /* RIGHT arrow */
                        right_arrow_handle(p_cli);
                        break;
                    case 'D': /* LEFT arrow */
                        left_arrow_handle(p_cli);
                        break;
                    case '4': /* END Button in ESC[n~ mode */
                        receive_state_change(p_cli, NRF_CLI_RECEIVE_TILDE_EXP);
                        /* fall through */
                    case 'F': /* END Button in VT100 mode */
                        cursor_end_position_move(p_cli);
                        break;
                    case '1': /* HOME Button in ESC[n~ mode */
                        receive_state_change(p_cli, NRF_CLI_RECEIVE_TILDE_EXP);
                        /* fall through */
                    case 'H': /* HOME Button in VT100 mode */
                        cursor_home_position_move(p_cli);
                        break;
                    case '2': /* INSERT Button in ESC[n~ mode */
                        receive_state_change(p_cli, NRF_CLI_RECEIVE_TILDE_EXP);
                        /* fall through */
                    case 'L': /* INSERT Button in VT100 mode */
                        p_cli->p_ctx->internal.flag.insert_mode ^= 1;
                        break;
                    case '3':/* DELETE Button in ESC[n~ mode */
                        receive_state_change(p_cli, NRF_CLI_RECEIVE_TILDE_EXP);
                        if (cli_flag_echo_is_set(p_cli))
                        {
                            char_delete(p_cli);
                        }
                        break;
                    default:
                        break;
                }
                break;
            case NRF_CLI_RECEIVE_TILDE_EXP:
                receive_state_change(p_cli, NRF_CLI_RECEIVE_DEFAULT);
                break;
            default:
                receive_state_change(p_cli, NRF_CLI_RECEIVE_DEFAULT);
                break;
        }
    }
}

/* Function remove white chars from beginning and end of command buffer. */
static void cmd_trim(nrf_cli_t const * p_cli)
{
    nrf_cli_cmd_len_t i = 0;

    if (p_cli->p_ctx->cmd_buff[0] == '\0') /* no command in the buffer */
    {
        return;
    }

    /* Counting white characters starting from beginning of the command. */
    while (isspace((int)p_cli->p_ctx->cmd_buff[i++]))
    {
        if (i == 0)
        {
            p_cli->p_ctx->cmd_buff[0] = '\0';
            return;
        }
    }

    /* Removing counted white characters. */
    if (--i > 0)
    {
        memmove(p_cli->p_ctx->cmd_buff,
                p_cli->p_ctx->cmd_buff + i,
                (p_cli->p_ctx->cmd_buff_len + 1) - i); /* +1 for '\0' */
        p_cli->p_ctx->cmd_buff_len = p_cli->p_ctx->cmd_buff_len - i;
        p_cli->p_ctx->cmd_buff_pos = p_cli->p_ctx->cmd_buff_len;
    }

    /* Counting white characters starting from end of command. */
    char * p_end = &p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_len - 1];
    i = 0;
    while (isspace((int)*p_end))
    {
        ++i;
        --p_end;
    }

    /* Removing counted white characters. */
    if (p_end != &p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_len - 1])
    {
        p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_len - i] = '\0';
        p_cli->p_ctx->cmd_buff_len = p_cli->p_ctx->cmd_buff_len - i;
        p_cli->p_ctx->cmd_buff_pos = p_cli->p_ctx->cmd_buff_len;
    }
}

#if NRF_MODULE_ENABLED(NRF_CLI_WILDCARD)
static void spaces_trim(char * p_char)
{
    nrf_cli_cmd_len_t shift = 0;
    nrf_cli_cmd_len_t len = cli_strlen(p_char);

    if (p_char == NULL)
    {
        return;
    }

    for (nrf_cli_cmd_len_t i = 0; i < len - 1; i++)
    {
        if (isspace((int)p_char[i]))
        {
            for (nrf_cli_cmd_len_t j = i + 1; j < len; j++)
            {
                if (isspace((int)p_char[j]))
                {
                    shift++;
                    continue;
                }
                if (shift > 0)
                {
                    memmove(&p_char[i + 1], &p_char[j], len - shift + 1); // +1 for EOS
                    len -= shift;
                    shift = 0;
                }
                break;
            }
        }
    }
}

/* Adds new command and one space just before pattern */
static bool command_to_tmp_buffer_add(nrf_cli_t const * p_cli,
                                      char const *      p_new_cmd,
                                      char const *      p_pattern)
{
    nrf_cli_cmd_len_t cmd_len = cli_strlen(p_new_cmd);
    nrf_cli_cmd_len_t shift;
    char *            p_cmd_source_addr;

    /* +1 for space */
    if (((size_t)p_cli->p_ctx->cmd_tmp_buff_len + cmd_len + 1) > NRF_CLI_CMD_BUFF_SIZE)
    {
        nrf_cli_warn(p_cli,
                     "Command buffer is too short to expand all commands matching "
                     "wildcard pattern");
        return false;
    }

    p_cmd_source_addr = strstr(p_cli->p_ctx->temp_buff, p_pattern);

    if (p_cmd_source_addr == NULL)
    {
        return false;
    }

    shift = cli_strlen(p_cmd_source_addr);

    /* make place for new command:      + 1 for space                 + 1 for EOS */
    memmove(p_cmd_source_addr + cmd_len + 1, p_cmd_source_addr, shift + 1);
    memcpy(p_cmd_source_addr, p_new_cmd, cmd_len);
    p_cmd_source_addr[cmd_len] = ' ';

    p_cli->p_ctx->cmd_tmp_buff_len += cmd_len + 1; // + 1 for space

    return true;
}

/* removes pattern and following space */
static void pattern_from_tmp_buffer_remove(nrf_cli_t const * p_cli,
                                           char const *      p_pattern)
{
    size_t shift;
    char * p_pattern_addr = strstr(p_cli->p_ctx->temp_buff, p_pattern);

    nrf_cli_cmd_len_t pattern_len = cli_strlen(p_pattern);

    if (p_pattern_addr == NULL)
    {
        return;
    }

    if (p_pattern_addr > p_cli->p_ctx->temp_buff)
    {
        if (*(p_pattern_addr - 1) == ' ')
        {
            pattern_len++;      /* space needs to be removed as well */
            p_pattern_addr--;   /* set pointer to space */
        }
    }

    shift = cli_strlen(p_pattern_addr) - pattern_len + 1; /* +1 for EOS */
    p_cli->p_ctx->cmd_tmp_buff_len -= pattern_len;

    memmove(p_pattern_addr, p_pattern_addr + pattern_len, shift);
}

/**
 * @internal @brief Function for searching and adding commands matching to wildcard pattern.
 *
 * This function is internal to nrf_cli module and shall be not called directly.
 *
 * @param[in/out] p_cli         Pointer to the CLI instance.
 * @param[in]     p_cmd         Pointer to command which will be processed
 * @param[in]     cmd_lvl       Command level in the command tree.
 * @param[in]     p_pattern     Pointer to wildcard pattern.
 * @param[out]    p_counter     Number of found and added commands.
 *
 * @retval WILDCARD_CMD_ADDED                   All matching commands added to the buffer.
 * @retval WILDCARD_CMD_ADDED_MISSING_SPACE     Not all matching commands added because
 *                                              NRF_CLI_CMD_BUFF_SIZE is too small.
 * @retval WILDCARD_CMD_NO_MATCH_FOUND          No matching command found.
 */
static wildcard_cmd_status_t commands_expand(nrf_cli_t const *           p_cli,
                                             nrf_cli_cmd_entry_t const * p_cmd,
                                             size_t                      cmd_lvl,
                                             char *                      p_pattern,
                                             size_t *                    p_counter)
{
    size_t cmd_idx = 0;
    size_t counter = 0;
    bool   success = false;

    nrf_cli_static_entry_t         static_entry;
    nrf_cli_static_entry_t const * p_static_entry = NULL;
    wildcard_cmd_status_t          ret_val = WILDCARD_CMD_NO_MATCH_FOUND;

    do
    {
        cmd_get(p_cmd,
                cmd_lvl,
                cmd_idx++,
                &p_static_entry,
                &static_entry);

        if (p_static_entry == NULL)
        {
            break;
        }

        if (0 == fnmatch(p_pattern, p_static_entry->p_syntax, 0))
        {
            success = command_to_tmp_buffer_add(p_cli,
                                                p_static_entry->p_syntax,
                                                p_pattern);
            if (!success)
            {
                break;
            }
            counter++;
        }

    } while(cmd_idx != 0);

    if (counter > 0)
    {
        *p_counter = counter;
        pattern_from_tmp_buffer_remove(p_cli, p_pattern);

        if (success)
        {
            ret_val = WILDCARD_CMD_ADDED;
        }
        else
        {
            ret_val = WILDCARD_CMD_ADDED_MISSING_SPACE;
        }
    }

    return ret_val;
}
#endif // NRF_MODULE_ENABLED(NRF_CLI_WILDCARD)

/* Function is analyzing the command buffer to find matching commands. Next, it invokes the  last recognized
 * command which has a handler and passes the rest of command buffer as arguments. */
static void cli_execute(nrf_cli_t const * p_cli)
{
    char quote;
    size_t argc;
    char * argv[NRF_CLI_ARGC_MAX + 1]; /* +1 reserved for NULL added by function make_argv */

    size_t cmd_idx;             /* currently analyzed command in cmd_level */
    size_t cmd_lvl = NRF_CLI_CMD_ROOT_LVL; /* currently analyzed command level */
    size_t cmd_handler_lvl = 0; /* last command level for which a handler has been found */

    nrf_cli_cmd_entry_t const * p_cmd = NULL;

    cmd_trim(p_cli);

#if NRF_MODULE_ENABLED(NRF_CLI_HISTORY)
    history_save(p_cli);
#endif

#if NRF_MODULE_ENABLED(NRF_CLI_WILDCARD)
/* Wildcard can be correctly handled under following conditions:
     - wildcard command does not have a handler
     - wildcard command is on the deepest commands level
     - other commands on the same level as wildcard command shall also not have a handler

   Algorithm:
   1. Command buffer is copied to Temp buffer.
   2. Algorithm goes through Command buffer to find handlers and subcommands.
   3. If algorithm will find a wildcard character it switches to Temp buffer.
   4. In the Temp buffer command with found wildcard character is changed into matching command(s).
   5. Algorithm switch back to Command buffer and analyzes next command.
   6. When all arguments are analyzed from Command buffer, Temp buffer is copied to Command buffer.
   7. Last found handler is executed with all arguments in the Command buffer.
*/
    size_t commands_expanded = 0;

    memset(p_cli->p_ctx->temp_buff, 0, sizeof(p_cli->p_ctx->temp_buff));
    memcpy(p_cli->p_ctx->temp_buff,
           p_cli->p_ctx->cmd_buff,
           p_cli->p_ctx->cmd_buff_len);

    /* Function spaces_trim must be used instead of make_argv. At this point it is important to keep
       temp_buff as a one string. It will allow to find wildcard commands easly with strstr
       function. */
    spaces_trim(p_cli->p_ctx->temp_buff);
    p_cli->p_ctx->cmd_tmp_buff_len = cli_strlen(p_cli->p_ctx->temp_buff) + 1;  // +1 for EOS
#endif

    cursor_end_position_move(p_cli);
    if (!cursor_in_empty_line(p_cli))
    {
        cursor_next_line_move(p_cli);
    }

    /* create argument list */
    quote = make_argv(&argc,
                      &argv[0],
                      p_cli->p_ctx->cmd_buff,
                      NRF_CLI_ARGC_MAX);

    if (!argc)
    {
        cursor_next_line_move(p_cli);
        return;
    }

    if (quote != 0)
    {
        nrf_cli_error(p_cli, "not terminated: %c", quote);
        return;
    }

    /*  Searching for a matching root command. */
    for (cmd_idx = 0; cmd_idx <= CLI_DATA_SECTION_ITEM_COUNT; ++cmd_idx)
    {
        if (cmd_idx >= CLI_DATA_SECTION_ITEM_COUNT)
        {
            nrf_cli_error(p_cli, "%s%s", argv[0], NRF_CLI_MSG_COMMAND_NOT_FOUND);
            return;
        }

        p_cmd = CLI_DATA_SECTION_ITEM_GET(cmd_idx);
        if (strcmp(argv[cmd_lvl], p_cmd->u.p_static->p_syntax) != 0)
        {
            continue;
        }
        break;
    }

    /* Root command shall be always static. */
    ASSERT(p_cmd->is_dynamic == false);

    /* Memory reserved for dynamic commands. */
    nrf_cli_static_entry_t static_entry;
    nrf_cli_static_entry_t const * p_static_entry = NULL;

    memset(&p_cli->p_ctx->active_cmd, 0, sizeof(p_cli->p_ctx->active_cmd));
    if (p_cmd->u.p_static->handler != NULL)
    {
        p_cli->p_ctx->active_cmd = *p_cmd->u.p_static;
    }

    p_cmd = p_cmd->u.p_static->p_subcmd;
    cmd_lvl++;
    cmd_idx = 0;

    while (1)
    {
        if (cmd_lvl >= argc)
        {
            break;
        }

        if (!strcmp(argv[cmd_lvl], "-h") || !strcmp(argv[cmd_lvl], "--help"))
        {
            /* Command called with help option so it makes no sense to search deeper commands. */
            cli_flag_help_set(p_cli);
            break;
        }

#if NRF_MODULE_ENABLED(NRF_CLI_WILDCARD)
        /* Wildcard character is found */
        if (wildcard_character_exist(argv[cmd_lvl]))
        {
            size_t counter = 0;
            wildcard_cmd_status_t status;

            /* Function will search commands tree for commands matching wildcard pattern stored in
               argv[cmd_lvl]. If match is found wildcard pattern will be replaced by matching
               commands in temp_buffer. If there is no space to add all matching commands function
               will add as many as possible. Next it will continue to search for next wildcard
               pattern and it will try to add matching commands. */
            status = commands_expand(p_cli, p_cmd, cmd_lvl, argv[cmd_lvl], &counter);
            if (WILDCARD_CMD_NO_MATCH_FOUND == status)
            {
                break;
            }
            commands_expanded += counter;
            cmd_lvl++;
            continue;
        }
#endif

        cmd_get(p_cmd,
                cmd_lvl,
                cmd_idx++,
                &p_static_entry,
                &static_entry);

        if ((cmd_idx == 0) || (p_static_entry == NULL))
        {
            break;
        }

        if (strcmp(argv[cmd_lvl], p_static_entry->p_syntax) == 0)
        {
            /* checking if command has a handler */
            if (p_static_entry->handler != NULL)
            {
#if NRF_MODULE_ENABLED(NRF_CLI_WILDCARD)
                if (commands_expanded > 0)
                {
                    cursor_end_position_move(p_cli);
                    if (!cursor_in_empty_line(p_cli))
                    {
                        cursor_next_line_move(p_cli);
                    }
                    /* An error occured, fnmatch argument cannot be followed by argument
                    * with a handler to avoid multiple function calls. */
                    nrf_cli_error(p_cli, "Error: requested multiple function executions");
                    cli_flag_help_clear(p_cli);
                    return;
                }
#endif
                /* Storing p_st_cmd->handler is not feasible for dynamic commands. Data will be
                 * invalid with the next loop iteration. */
                cmd_handler_lvl = cmd_lvl;
                p_cli->p_ctx->active_cmd = *p_static_entry;
            }

            cmd_lvl++;
            cmd_idx = 0;
            p_cmd = p_static_entry->p_subcmd;
        }
    }
#if NRF_MODULE_ENABLED(NRF_CLI_WILDCARD)
    if (commands_expanded > 0)
    {
        /* Copy temp_buff to cmd_buff */
        memcpy(p_cli->p_ctx->cmd_buff,
               p_cli->p_ctx->temp_buff,
               p_cli->p_ctx->cmd_tmp_buff_len);
        p_cli->p_ctx->cmd_buff_len = p_cli->p_ctx->cmd_tmp_buff_len;

        /* calling make_arg function again because cmd_buffer has additional commads */
        (void)make_argv(&argc,
                        &argv[0],
                        p_cli->p_ctx->cmd_buff,
                        NRF_CLI_ARGC_MAX);
    }
 #endif

    if (p_cli->p_ctx->active_cmd.handler != NULL)
    {
        p_cli->p_ctx->active_cmd.handler(p_cli,
                                         argc - cmd_handler_lvl,
                                         &argv[cmd_handler_lvl]);
    }
    else
    {
        nrf_cli_error(p_cli, NRF_CLI_MSG_SPECIFY_SUBCOMMAND);
    }
    cli_flag_help_clear(p_cli);
}

/* Function required by qsort. */
static int string_cmp(void const * pp_a, void const * pp_b)
{
    ASSERT(pp_a);
    ASSERT(pp_b);

    char const ** pp_str_a = (char const **)pp_a;
    char const ** pp_str_b = (char const **)pp_b;

    return strcmp(*pp_str_a, *pp_str_b);
}

static void cli_transport_evt_handler(nrf_cli_transport_evt_t evt_type, void * p_context)
{
    nrf_cli_t * p_cli = (nrf_cli_t *)p_context;
    ASSERT(p_cli);
#if NRF_MODULE_ENABLED(NRF_CLI_USES_TASK_MANAGER)
    task_events_set(p_cli->p_ctx->task_id, evt_type == NRF_CLI_TRANSPORT_EVT_RX_RDY ?
            NRF_CLI_TRANSPORT_RX_RDY_TASK_EVT : NRF_CLI_TRANSPORT_TX_RDY_TASK_EVT);
#else

    if (evt_type == NRF_CLI_TRANSPORT_EVT_RX_RDY)
    {

    }
    else
    {
        /* wr done evt */
        p_cli->p_ctx->internal.flag.tx_rdy = 1;
    }
#endif
}

static ret_code_t nrf_cli_instance_init(nrf_cli_t const * p_cli,
                                        void const *      p_config,
                                        bool              use_colors)
{
    ASSERT(p_cli);
    ASSERT(p_cli->p_ctx && p_cli->p_iface && p_cli->p_name);

#if defined(NRF_CLI_LOG_BACKEND) && NRF_CLI_LOG_BACKEND
    ((nrf_cli_log_backend_t *)p_cli->p_log_backend->p_ctx)->p_cli = p_cli;
#endif
    ret_code_t ret = p_cli->p_iface->p_api->init(p_cli->p_iface,
                                                 p_config,
                                                 cli_transport_evt_handler,
                                                 (void *)p_cli);
    if (ret != NRF_SUCCESS)
    {
        return ret;
    }

#if NRF_MODULE_ENABLED(NRF_CLI_HISTORY)
    ASSERT(p_cli->p_cmd_hist_mempool);
    ret = nrf_memobj_pool_init(p_cli->p_cmd_hist_mempool);
    if (ret != NRF_SUCCESS)
    {
        return ret;
    }
    p_cli->p_ctx->p_cmd_list_head = NULL;
    p_cli->p_ctx->p_cmd_list_tail = NULL;
#endif

    memset(p_cli->p_ctx, 0, sizeof(nrf_cli_ctx_t));
    p_cli->p_ctx->internal.flag.tx_rdy = 1;

#if NRF_MODULE_ENABLED(NRF_CLI_VT100_COLORS)
    p_cli->p_ctx->internal.flag.use_colors = use_colors;
#endif
    p_cli->p_ctx->internal.flag.echo = NRF_CLI_ECHO_STATUS;
    p_cli->p_ctx->state = NRF_CLI_STATE_INITIALIZED;
    p_cli->p_ctx->vt100_ctx.cons.terminal_wid = NRF_CLI_DEFAULT_TERMINAL_WIDTH;
    p_cli->p_ctx->vt100_ctx.cons.terminal_hei = NRF_CLI_DEFAULT_TERMINAL_HEIGHT;

    const char * * pp_sorted_cmds = (const char * *)CLI_SORTED_CMD_PTRS_START_ADDR_GET;
    for (size_t i = 0; i < CLI_DATA_SECTION_ITEM_COUNT; i++)
    {
        const nrf_cli_cmd_entry_t * cmd;
        cmd = CLI_DATA_SECTION_ITEM_GET(i);

        /* NULL syntax commands not allowed. */
        ASSERT(cmd);
        ASSERT(cmd->u.p_static->p_syntax);

        pp_sorted_cmds[i] = cmd->u.p_static->p_syntax;
    }

    if (CLI_DATA_SECTION_ITEM_COUNT > 0)
    {
        qsort(pp_sorted_cmds,
              CLI_DATA_SECTION_ITEM_COUNT,
              sizeof (char *),
              string_cmp);
    }

    return NRF_SUCCESS;
}

#if NRF_MODULE_ENABLED(NRF_CLI_USES_TASK_MANAGER)
static ret_code_t nrf_cli_instance_uninit(nrf_cli_t const * p_cli);
void console_task(void * p_context)
{
    nrf_cli_t * p_cli = (nrf_cli_t *)p_context;

    ret_code_t ret = nrf_cli_start(p_cli);
    APP_ERROR_CHECK(ret);

    while (1)
    {
        uint32_t evts = task_events_wait(NRF_CLI_TASK_EVTS);

        if (evts & NRF_CLI_KILL_TASK_EVT)
        {
            (void)nrf_cli_instance_uninit(p_cli);
            task_exit();
        }
        else
        {
            nrf_cli_process(p_cli);
        }
    }
}
#endif

ret_code_t nrf_cli_init(nrf_cli_t const *  p_cli,
                        void const *       p_config,
                        bool               use_colors,
                        bool               log_backend,
                        nrf_log_severity_t init_lvl)
{
    ASSERT(p_cli);

    ret_code_t err_code = nrf_cli_instance_init(p_cli, p_config, use_colors);

#if NRF_CLI_LOG_BACKEND && NRF_MODULE_ENABLED(NRF_LOG)
    if ((err_code == NRF_SUCCESS) && log_backend && NRF_CLI_LOG_BACKEND)
    {
        int32_t id = nrf_log_backend_add(p_cli->p_log_backend, init_lvl);
        if (id < 0)
        {
            return NRF_ERROR_NO_MEM;
        }

        nrf_log_backend_enable(p_cli->p_log_backend);
    }
#endif
    return err_code;
}

ret_code_t nrf_cli_task_create(nrf_cli_t const * p_cli)
{
#if NRF_MODULE_ENABLED(NRF_CLI_USES_TASK_MANAGER)
    p_cli->p_ctx->task_id = task_create(console_task, p_cli->p_name,(void *)p_cli);
    if (p_cli->p_ctx->task_id == TASK_ID_INVALID)
    {
        return NRF_ERROR_NO_MEM;
    }
    else
    {
        return NRF_SUCCESS;
    }
#else
    return NRF_ERROR_NOT_SUPPORTED;
#endif
}

static ret_code_t nrf_cli_instance_uninit(nrf_cli_t const * p_cli)
{
    ASSERT(p_cli);
    ASSERT(p_cli->p_ctx && p_cli->p_iface && p_cli->p_name);

    if (cli_flag_processing_is_set(p_cli))
    {
        return NRF_ERROR_BUSY;
    }

#if NRF_CLI_LOG_BACKEND && NRF_MODULE_ENABLED(NRF_LOG)
    if (p_cli->p_log_backend != NULL)
    {
        nrf_log_backend_disable(p_cli->p_log_backend);
        nrf_log_backend_remove(p_cli->p_log_backend);
    }
#endif

    ret_code_t ret = p_cli->p_iface->p_api->uninit(p_cli->p_iface);
    if (ret != NRF_SUCCESS)
    {
        return ret;
    }

#if NRF_MODULE_ENABLED(NRF_CLI_HISTORY)
    history_list_free_memory(p_cli);
#endif

    memset(p_cli->p_ctx, 0, sizeof(nrf_cli_ctx_t));
    p_cli->p_ctx->state = NRF_CLI_STATE_UNINITIALIZED;

    return NRF_SUCCESS;
}

ret_code_t nrf_cli_uninit(nrf_cli_t const * p_cli)
{
#if NRF_MODULE_ENABLED(NRF_CLI_USES_TASK_MANAGER)
    if (cli_flag_processing_is_set(p_cli))
    {
        return NRF_ERROR_BUSY;
    }
    task_events_set(p_cli->p_ctx->task_id, NRF_CLI_KILL_TASK_EVT);
    return NRF_SUCCESS;
#else
    return nrf_cli_instance_uninit(p_cli);
#endif
}

ret_code_t nrf_cli_start(nrf_cli_t const * p_cli)
{
    ASSERT(p_cli);
    ASSERT(p_cli->p_ctx && p_cli->p_iface && p_cli->p_name);

    if (p_cli->p_ctx->state != NRF_CLI_STATE_INITIALIZED)
    {
        return NRF_ERROR_INVALID_STATE;
    }

#if NRF_MODULE_ENABLED(NRF_CLI_USES_TASK_MANAGER)
    void * p_context = (void *)((uint32_t)task_id_get());
    ((nrf_cli_log_backend_t *)p_cli->p_log_backend->p_ctx)->p_context = p_context;
#endif

    ret_code_t err_code = p_cli->p_iface->p_api->enable(p_cli->p_iface, false);

#if NRF_MODULE_ENABLED(NRF_CLI_USES_TASK_MANAGER)
    task_events_set(task_id_get(), NRF_CLI_TRANSPORT_RX_RDY_TASK_EVT);
#endif

    if (err_code == NRF_SUCCESS)
    {
#if NRF_CLI_VT100_COLORS_ENABLED
        vt100_color_set(p_cli, NRF_CLI_NORMAL);
        vt100_bgcolor_set(p_cli, NRF_CLI_VT100_COLOR_BLACK);
#endif
        nrf_fprintf(p_cli->p_fprintf_ctx, "\n\n");
        cli_state_set(p_cli, NRF_CLI_STATE_ACTIVE);
    }

    return err_code;
}

ret_code_t nrf_cli_stop(nrf_cli_t const * p_cli)
{
    ASSERT(p_cli);
    ASSERT(p_cli->p_ctx && p_cli->p_iface && p_cli->p_name);

    if (p_cli->p_ctx->state == NRF_CLI_STATE_INITIALIZED ||
        p_cli->p_ctx->state == NRF_CLI_STATE_UNINITIALIZED)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    cli_state_set(p_cli, NRF_CLI_STATE_INITIALIZED);
    return NRF_SUCCESS;
}

void nrf_cli_process(nrf_cli_t const * p_cli)
{
    ASSERT(p_cli);
    ASSERT(p_cli->p_ctx && p_cli->p_iface && p_cli->p_name);

    nrf_cli_internal_t internal;
    internal.value = 0;
    internal.flag.processing = 1;
    (void)nrf_atomic_u32_or((nrf_atomic_u32_t *)&p_cli->p_ctx->internal.value,
                            internal.value);

    switch (p_cli->p_ctx->state)
    {
        case NRF_CLI_STATE_UNINITIALIZED:
        case NRF_CLI_STATE_INITIALIZED:
            /* Console initialized but not started. */
            break;
        case NRF_CLI_STATE_ACTIVE:
        {
            cli_state_collect(p_cli);
            bool log_processed = cli_log_entry_process(p_cli, false);
            if (log_processed)
            {
                nrf_cli_fprintf(p_cli, NRF_CLI_INFO, "%s", p_cli->p_name);
                if (cli_flag_echo_is_set(p_cli))
                {
                    nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "%s", p_cli->p_ctx->cmd_buff);
                    cursor_position_synchronize(p_cli);
                }
            }
            break;
        }
        default:
            break;
    }
    transport_buffer_flush(p_cli);
    internal.value = (uint32_t)0xFFFFFFFF;
    internal.flag.processing = 0;
    (void)nrf_atomic_u32_and((nrf_atomic_u32_t *)&p_cli->p_ctx->internal.value,
                             internal.value);
}

/* Function shall be only used by the nrf_fprintf module. */
void nrf_cli_print_stream(void const * p_user_ctx, char const * p_data, size_t data_len)
{
    cli_write((nrf_cli_t const *)p_user_ctx,
              p_data,
              data_len,
              NULL);
}

void nrf_cli_fprintf(nrf_cli_t const *      p_cli,
                     nrf_cli_vt100_color_t  color,
                     char const *           p_fmt,
                                            ...)
{
    ASSERT(p_fmt);
    ASSERT(p_cli);
    ASSERT(p_cli->p_ctx && p_cli->p_iface && p_cli->p_name);

    va_list args = {0};
    va_start(args, p_fmt);

#if NRF_MODULE_ENABLED(NRF_CLI_VT100_COLORS)
    if ((p_cli->p_ctx->internal.flag.use_colors) &&
        (color != p_cli->p_ctx->vt100_ctx.col.col))
    {
        nrf_cli_vt100_colors_t col;

        vt100_colors_store(p_cli, &col);
        vt100_color_set(p_cli, color);

        nrf_fprintf_fmt(p_cli->p_fprintf_ctx, p_fmt, &args);

        vt100_colors_restore(p_cli, &col);
    }
    else
#endif // NRF_MODULE_ENABLED(NRF_CLI_VT100_COLORS)
    {
        nrf_fprintf_fmt(p_cli->p_fprintf_ctx, p_fmt, &args);
    }

    va_end(args);
}

/* Function prints a string on terminal screen with requested margin.
 * It takes care to not divide words.
 *   p_cli               Pointer to CLI instance.
 *   p_str               Pointer to string to be printed.
 *   terminal_offset     Requested left margin.
 *   offset_first_line   Add margin to the first printed line.
 */
static void format_offset_string_print(nrf_cli_t const * p_cli,
                                       char const *      p_str,
                                       size_t            terminal_offset,
                                       bool              offset_first_line)
{
    if (p_str == NULL)
    {
        return;
    }

    if (offset_first_line)
    {
        cursor_right_move(p_cli, terminal_offset);
    }

    size_t length;
    size_t offset = 0;

    /* Skipping whitespace. */
    while (isspace((int)*(p_str + offset)))
    {
       ++offset;
    }

    while (1)
    {
        size_t idx = 0;
        length = cli_strlen(p_str) - offset;

        if (length <= p_cli->p_ctx->vt100_ctx.cons.terminal_wid - terminal_offset)
        {
            for (idx = 0; idx < length; idx++)
            {
                if (*(p_str + offset + idx) == '\n')
                {
                    transport_buffer_flush(p_cli);
                    cli_write(p_cli, p_str + offset, idx, NULL);
                    offset += idx + 1;
                    cursor_next_line_move(p_cli);
                    cursor_right_move(p_cli, terminal_offset);
                    break;
                }
            }
            /* String will fit in one line. */
            nrf_fprintf(p_cli->p_fprintf_ctx, p_str + offset);
            break;
        }
        else
        {
            /* String is longer than terminal line so text needs to divide in the way
               to not divide words. */
            length = p_cli->p_ctx->vt100_ctx.cons.terminal_wid - terminal_offset;

            while (1)
            {
                /* Determining line break. */
                if (isspace((int)(*(p_str + offset + idx))))
                {
                    length = idx;
                    if (*(p_str + offset + idx) == '\n')
                    {
                        break;
                    }
                }
                if ((idx + terminal_offset) >= p_cli->p_ctx->vt100_ctx.cons.terminal_wid)
                {
                    /* End of line reached. */
                    break;
                }
                ++idx;
            }

            /* Writing one line, fprintf IO buffer must be flushed before calling cli_write. */
            transport_buffer_flush(p_cli);
            cli_write(p_cli, p_str + offset, length, NULL);
            offset += length;

            /* Calculating text offset to ensure that next line will not begin with a space. */
            while (isspace((int)(*(p_str + offset))))
            {
                ++offset;
            }
            cursor_next_line_move(p_cli);
            cursor_right_move(p_cli, terminal_offset);
        }
    }
    cursor_next_line_move(p_cli);
}

void nrf_cli_help_print(nrf_cli_t const *               p_cli,
                        nrf_cli_getopt_option_t const * p_opt,
                        size_t                          opt_len)
{
    ASSERT(p_cli);
    ASSERT(p_cli->p_ctx && p_cli->p_iface && p_cli->p_name);

    static uint8_t const tab_len = 2;
    static char const opt_sep[] =", "; /* options separator */
    static char const help[] = "-h, --help";
    static char const cmd_sep[] = " - "; /* command separator */
    uint16_t field_width = 0;
    uint16_t longest_string = cli_strlen(help) - cli_strlen(opt_sep);

    /* Printing help string for command. */
    nrf_cli_fprintf(p_cli,
                    NRF_CLI_NORMAL,
                    "%s%s",
                    p_cli->p_ctx->active_cmd.p_syntax,
                    cmd_sep);

    field_width = cli_strlen(p_cli->p_ctx->active_cmd.p_syntax) + cli_strlen(cmd_sep);
    format_offset_string_print(p_cli, p_cli->p_ctx->active_cmd.p_help, field_width, false);

    nrf_cli_print(p_cli, "Options:");

    /* Looking for the longest option string. */
    if ((opt_len > 0) && (p_opt != NULL))
    {
        for (size_t i = 0; i < opt_len; ++i)
        {
            if (cli_strlen(p_opt[i].p_optname_short) + cli_strlen(p_opt[i].p_optname)
                    > longest_string)
            {
                longest_string = cli_strlen(p_opt[i].p_optname_short)
                    + cli_strlen(p_opt[i].p_optname);
            }
        }
    }
    longest_string += cli_strlen(opt_sep) + tab_len;

    nrf_cli_fprintf(p_cli,
                    NRF_CLI_NORMAL,
                    "  %-*s:",
                    longest_string,
                    help);

    /* Print help string for options (only -h and --help). */
    field_width = longest_string + tab_len + 1; /* tab_len + 1 == "  " and ':' from: "  %-*s:" */
    format_offset_string_print(p_cli, "Show command help.", field_width, false);

    /* Formating and printing all available options (except -h, --help). */
    if (p_opt != NULL)
    {
        for (size_t i = 0; i < opt_len; ++i)
        {
            if ((p_opt[i].p_optname_short != NULL) && (p_opt[i].p_optname != NULL))
            {
                nrf_cli_fprintf(p_cli,
                                NRF_CLI_NORMAL,
                                "  %s%s%s",
                                p_opt[i].p_optname_short,
                                opt_sep,
                                p_opt[i].p_optname);
                field_width = longest_string + tab_len;
                cursor_right_move(p_cli,
                                  field_width - ( cli_strlen(p_opt[i].p_optname_short)
                                                + cli_strlen(p_opt[i].p_optname)
                                                + tab_len
                                                + cli_strlen(opt_sep)));
                cli_putc(p_cli, ':');
                ++field_width;  /* incrementing because char ':' was already printed above */
            }
            else if (p_opt[i].p_optname_short != NULL)
            {
                nrf_cli_fprintf(p_cli,
                                NRF_CLI_NORMAL,
                                "  %-*s:",
                                longest_string,
                                p_opt[i].p_optname_short);
                /* tab_len + 1 == "  " and ':' from: "  %-*s:" */
                field_width = longest_string + tab_len + 1;
            }
            else if (p_opt[i].p_optname != NULL)
            {
                nrf_cli_fprintf(p_cli,
                                NRF_CLI_NORMAL,
                                "  %-*s:",
                                longest_string,
                                p_opt[i].p_optname);
                /* tab_len + 1 == "  " and ':' from: "  %-*s:" */
                field_width = longest_string + tab_len + 1;
            }
            else
            {
                /* Do nothing. */
            }

            if (p_opt[i].p_optname_help != NULL)
            {
                format_offset_string_print(p_cli, p_opt[i].p_optname_help, field_width, false);
            }
            else
            {
                cursor_next_line_move(p_cli);
            }
        }
    }

    /* Checking if there are any subcommands avilable. */
    if (p_cli->p_ctx->active_cmd.p_subcmd == NULL)
    {
        return;
    }

    /* Printing formatted help of one level deeper subcommands. */
    nrf_cli_static_entry_t static_entry;
    nrf_cli_cmd_entry_t const * p_cmd = p_cli->p_ctx->active_cmd.p_subcmd;
    nrf_cli_static_entry_t const * p_st_cmd = NULL;

    field_width = 0;
    longest_string = 0;

    size_t cmd_idx = 0;

    /* Searching for the longest subcommand to print. */
    while (1)
    {
        cmd_get(p_cmd, !NRF_CLI_CMD_ROOT_LVL, cmd_idx++, &p_st_cmd, &static_entry);

        if (p_st_cmd == NULL)
        {
            break;
        }
        if (cli_strlen(p_st_cmd->p_syntax) > longest_string)
        {
            longest_string = cli_strlen(p_st_cmd->p_syntax);
        }
    }

    /* Checking if there are dynamic subcommands. */
    if (cmd_idx == 1)
    {
        /* No dynamic subcommands available. */
        return;
    }

    nrf_cli_print(p_cli, "Subcommands:");

    /* Printing subcommands and help string (if exists). */
    cmd_idx = 0;
    while (1)
    {
        cmd_get(p_cmd, !NRF_CLI_CMD_ROOT_LVL, cmd_idx++, &p_st_cmd, &static_entry);

        if (p_st_cmd == NULL)
        {
            break;
        }

        field_width = longest_string + tab_len;
        nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL,"  %-*s:", field_width, p_st_cmd->p_syntax);
        field_width += tab_len + 1; /* tab_len + 1 == "  " and ':' from: "  %-*s:" */

        if (p_st_cmd->p_help != NULL)
        {
            format_offset_string_print(p_cli, p_st_cmd->p_help, field_width, false);
        }
        else
        {
            cursor_next_line_move(p_cli);
        }
    }
}

#if NRF_CLI_LOG_BACKEND && NRF_MODULE_ENABLED(NRF_LOG)

#define NRF_CLI_LOG_MSG_OVERFLOW_MSK ((uint32_t)7)
static bool cli_log_entry_process(nrf_cli_t const * p_cli, bool skip)
{
    nrf_log_entry_t entry;

#if NRF_MODULE_ENABLED(NRF_CLI_STATISTICS)
    bool print_msg = false;
#endif

    if (nrf_queue_pop(((nrf_cli_log_backend_t *)p_cli->p_log_backend->p_ctx)->p_queue, &entry) !=
                                                                                      NRF_SUCCESS)
    {
        return false;
    }

    if (skip)
    {
        nrf_memobj_put(entry);
#if NRF_MODULE_ENABLED(NRF_CLI_STATISTICS)
        ++p_cli->p_ctx->statistics.log_lost_cnt;
        if ((p_cli->p_ctx->statistics.log_lost_cnt & NRF_CLI_LOG_MSG_OVERFLOW_MSK) == 1)
        {
            /* Set flag to print a message after clearing the currently entered command. */
            print_msg = true;
        }
        else
#endif
        {
            return true;
        }
    }
    {
        /* Erasing the currently displayed command and console name. */
        nrf_cli_multiline_cons_t const * p_cons = multiline_console_data_check(p_cli);

        if (p_cons->cur_y > NRF_CLI_INITIAL_CURS_POS)
        {
            cursor_up_move(p_cli, p_cons->cur_y - NRF_CLI_INITIAL_CURS_POS);
        }

        if (p_cons->cur_x > NRF_CLI_INITIAL_CURS_POS)
        {
            cursor_left_move(p_cli, p_cons->cur_x - NRF_CLI_INITIAL_CURS_POS);
        }
        cli_clear_eos(p_cli);
    }

#if NRF_MODULE_ENABLED(NRF_CLI_STATISTICS)
    if (print_msg)
    {
        /* Print the requested string and exit function. */
        nrf_cli_error(p_cli, "Lost logs - increase log backend queue size.");

        return true;
    }
#endif

    /* Printing logs from the queue. */
    do
    {
        nrf_log_header_t header;
        size_t           memobj_offset = 0;
        nrf_log_str_formatter_entry_params_t params;

        nrf_memobj_read(entry, &header, HEADER_SIZE*sizeof(uint32_t), memobj_offset);
        memobj_offset = HEADER_SIZE * sizeof(uint32_t);

        params.timestamp  = header.timestamp;
        params.module_id  = header.module_id;
        params.dropped    = header.dropped;
        params.use_colors = NRF_LOG_USES_COLORS; /* Color will be provided by the console application. */

        if (header.base.generic.type == HEADER_TYPE_STD)
        {
            char const * p_log_str = (char const *)((uint32_t)header.base.std.addr);
            params.severity  = (nrf_log_severity_t)header.base.std.severity;
            uint32_t nargs   = header.base.std.nargs;
            uint32_t args[6];

            nrf_memobj_read(entry, args, nargs*sizeof(uint32_t), memobj_offset);
            nrf_log_std_entry_process(p_log_str,
                                      args,
                                      nargs,
                                      &params,
                                      p_cli->p_fprintf_ctx);
        }
        else if (header.base.generic.type == HEADER_TYPE_HEXDUMP)
        {
            uint32_t data_len;
            uint8_t data_buf[8];
            uint32_t chunk_len;

            data_len        = header.base.hexdump.len;
            params.severity = (nrf_log_severity_t)header.base.hexdump.severity;

            do
            {
                chunk_len = sizeof(data_buf) > data_len ? data_len : sizeof(data_buf);
                nrf_memobj_read(entry, data_buf, chunk_len, memobj_offset);
                memobj_offset += chunk_len;
                data_len      -= chunk_len;
                nrf_log_hexdump_entry_process(data_buf, chunk_len, &params, p_cli->p_fprintf_ctx);
            } while (data_len > 0);
        }

        nrf_memobj_put(entry);
    } while (nrf_queue_pop(((nrf_cli_log_backend_t *)p_cli->p_log_backend->p_ctx)->p_queue, &entry)
                                                                                    == NRF_SUCCESS);
    return true;
}

static void nrf_log_backend_cli_put(nrf_log_backend_t const * p_backend, nrf_log_entry_t * p_msg)
{
    nrf_cli_log_backend_t * p_backend_cli = (nrf_cli_log_backend_t *)p_backend->p_ctx;
    nrf_cli_t const * p_cli = p_backend_cli->p_cli;

    //If panic mode cannot be handled, stop handling new requests.
    if (p_cli->p_ctx->state != NRF_CLI_STATE_PANIC_MODE_INACTIVE)
    {
        bool panic_mode = (p_cli->p_ctx->state == NRF_CLI_STATE_PANIC_MODE_ACTIVE);
        //If there is no place for a new log entry, remove the oldest one.
        ret_code_t err_code = nrf_queue_push(p_backend_cli->p_queue, &p_msg);
        while (err_code != NRF_SUCCESS)
        {
            (void)cli_log_entry_process(p_cli, panic_mode ? false : true);

            err_code = nrf_queue_push(p_backend_cli->p_queue, &p_msg);
        }
        nrf_memobj_get(p_msg);

        if (panic_mode)
        {
            (void)cli_log_entry_process(p_cli, false);
        }
#if NRF_MODULE_ENABLED(NRF_CLI_USES_TASK_MANAGER)
        else
        {
            task_events_set((task_id_t)((uint32_t)p_backend_cli->p_context & 0x000000FF),
                            NRF_CLI_LOG_PENDING_TASK_EVT);
        }
#endif
    }
}

static void nrf_log_backend_cli_flush(nrf_log_backend_t const * p_backend)
{
    nrf_cli_log_backend_t * p_backend_cli = (nrf_cli_log_backend_t *)p_backend->p_ctx;
    nrf_cli_t const *       p_cli = p_backend_cli->p_cli;
    nrf_log_entry_t *       p_msg;

    if (nrf_queue_pop(p_backend_cli->p_queue, &p_msg) == NRF_SUCCESS)
    {
        (void)cli_log_entry_process(p_cli, false);
    }
    UNUSED_PARAMETER(p_backend);
}

static void nrf_log_backend_cli_panic_set(nrf_log_backend_t const * p_backend)
{
    nrf_cli_log_backend_t * p_backend_cli = (nrf_cli_log_backend_t *)p_backend->p_ctx;
    nrf_cli_t const * p_cli = p_backend_cli->p_cli;

    if (p_cli->p_iface->p_api->enable(p_cli->p_iface, true) == NRF_SUCCESS)
    {
        p_cli->p_ctx->state = NRF_CLI_STATE_PANIC_MODE_ACTIVE;
    }
    else
    {
        p_cli->p_ctx->state = NRF_CLI_STATE_PANIC_MODE_INACTIVE;
    }
}

const nrf_log_backend_api_t nrf_log_backend_cli_api = {
        .put       = nrf_log_backend_cli_put,
        .flush     = nrf_log_backend_cli_flush,
        .panic_set = nrf_log_backend_cli_panic_set,
};
#else
static bool cli_log_entry_process(nrf_cli_t const * p_cli, bool skip)
{
    UNUSED_PARAMETER(p_cli);
    UNUSED_PARAMETER(skip);
    return false;
}
#endif // NRF_CLI_LOG_BACKEND

/* ============ built-in commands ============ */
#if NRF_MODULE_ENABLED(NRF_CLI_BUILD_IN_CMDS)

static bool nrf_cli_build_in_cmd_common_executed(nrf_cli_t const *               p_cli,
                                                 bool                            arg_cnt_nok,
                                                 nrf_cli_getopt_option_t const * p_opt,
                                                 size_t                          opt_len)
{
    if (nrf_cli_help_requested(p_cli))
    {
        nrf_cli_help_print(p_cli, p_opt, opt_len);
        return true;
    }

    if (arg_cnt_nok)
    {
         nrf_cli_error(p_cli, "%s: wrong parameter count", p_cli->p_ctx->active_cmd.p_syntax);
         return true;
    }

    return false;
}

static void nrf_cli_cmd_clear(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    ASSERT(p_cli);
    ASSERT(p_cli->p_ctx && p_cli->p_iface && p_cli->p_name);
    UNUSED_PARAMETER(argv);

    if ((argc == 2) && (nrf_cli_help_requested(p_cli)))
    {
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }
    NRF_CLI_VT100_CMD(p_cli, NRF_CLI_VT100_CURSORHOME);
    NRF_CLI_VT100_CMD(p_cli, NRF_CLI_VT100_CLEARSCREEN);
}

static void nrf_cli_cmd_cli(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    ASSERT(p_cli);
    ASSERT(p_cli->p_ctx && p_cli->p_iface && p_cli->p_name);
    UNUSED_PARAMETER(argv);

    if ((argc == 1) || ((argc == 2) && nrf_cli_help_requested(p_cli)) )
    {
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }
    nrf_cli_error(p_cli, NRF_CLI_MSG_SPECIFY_SUBCOMMAND);
}

#if NRF_MODULE_ENABLED(NRF_CLI_VT100_COLORS)
static void nrf_cli_cmd_colors_off(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    if (nrf_cli_build_in_cmd_common_executed(p_cli, (argc != 1), NULL, 0))
    {
        return;
    }
    p_cli->p_ctx->internal.flag.use_colors = 0;
}

static void nrf_cli_cmd_colors_on(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    if (nrf_cli_build_in_cmd_common_executed(p_cli, (argc != 1), NULL, 0))
    {
        return;
    }
    p_cli->p_ctx->internal.flag.use_colors = 1;
}

static void nrf_cli_cmd_colors(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    ASSERT(p_cli);
    ASSERT(p_cli->p_ctx && p_cli->p_iface && p_cli->p_name);

    if (argc == 1)
    {
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }

    if (nrf_cli_build_in_cmd_common_executed(p_cli, (argc != 2), NULL, 0))
    {
        return;
    }

    nrf_cli_error(p_cli, "%s:%s%s", argv[0], NRF_CLI_MSG_UNKNOWN_PARAMETER, argv[1]);
}
#endif // NRF_MODULE_ENABLED(NRF_CLI_VT100_COLORS)

static void nrf_cli_cmd_echo(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    if (nrf_cli_build_in_cmd_common_executed(p_cli, (argc > 2), NULL, 0))
    {
        return;
    }

    if (argc == 2)
    {
        nrf_cli_error(p_cli, "%s:%s%s", argv[0], NRF_CLI_MSG_UNKNOWN_PARAMETER, argv[1]);
        return;
    }
    nrf_cli_print(p_cli, "Echo status: %s", cli_flag_echo_is_set(p_cli) ? "on" : "off");
}

static void nrf_cli_cmd_echo_off(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    if (nrf_cli_build_in_cmd_common_executed(p_cli, (argc != 1), NULL, 0))
    {
        return;
    }

    cli_flag_echo_clear(p_cli);
}

static void nrf_cli_cmd_echo_on(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    if (nrf_cli_build_in_cmd_common_executed(p_cli, (argc != 1), NULL, 0))
    {
        return;
    }

    cli_flag_echo_set(p_cli);
}

#if NRF_MODULE_ENABLED(NRF_CLI_HISTORY)
static void nrf_cli_cmd_history(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    ASSERT(p_cli);
    ASSERT(p_cli->p_ctx && p_cli->p_iface && p_cli->p_name);

    if (nrf_cli_build_in_cmd_common_executed(p_cli, (argc != 1), NULL, 0))
    {
        return;
    }

    size_t i = 0;
    nrf_memobj_t const * p_cmd_list = p_cli->p_ctx->p_cmd_list_tail;
    nrf_cli_memobj_header_t header;

    while (1)
    {
        if ((p_cmd_list == NULL) || (i >= NRF_CLI_HISTORY_ELEMENT_COUNT))
        {
            break;
        }
        nrf_memobj_read((nrf_memobj_t * )p_cmd_list,
                        &header,
                        NRF_CLI_HISTORY_HEADER_SIZE,
                        0);
        nrf_memobj_read((nrf_memobj_t * )p_cmd_list,
                        p_cli->p_ctx->temp_buff,
                        header.cmd_len + 1,
                        NRF_CLI_HISTORY_HEADER_SIZE);
        p_cmd_list = header.p_next;
        nrf_cli_print(p_cli, "[%3d] %s", i++, p_cli->p_ctx->temp_buff);
    }
    p_cli->p_ctx->temp_buff[0] = '\0';
}
#endif // NRF_MODULE_ENABLED(NRF_CLI_HISTORY)

#if NRF_MODULE_ENABLED(NRF_CLI_STATISTICS)
void nrf_cli_cmd_cli_stats(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    if (argc == 1)
    {
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }

    if (argc == 2)
    {
        nrf_cli_error(p_cli, "%s:%s%s", argv[0], NRF_CLI_MSG_UNKNOWN_PARAMETER, argv[1]);
        return;
    }

    UNUSED_RETURN_VALUE(nrf_cli_build_in_cmd_common_executed(p_cli, (argc > 2), NULL, 0));
}

void nrf_cli_cmd_cli_stats_show(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    if (nrf_cli_build_in_cmd_common_executed(p_cli, (argc != 1), NULL, 0))
    {
        return;
    }

    nrf_queue_t const  * p_queue = ((nrf_cli_log_backend_t *)p_cli->p_log_backend->p_ctx)->p_queue;
    uint8_t max_util = nrf_queue_max_utilization_get(p_queue);
    uint8_t utilization = (uint8_t)(max_util * 100ul / p_queue->size);

    nrf_cli_print(p_cli,
                  "Lost logs: %u\nMax log queue utilization: %u%% [%u/%u]",
                  p_cli->p_ctx->statistics.log_lost_cnt,
                  utilization,
                  max_util,
                  p_queue->size);
}

void nrf_cli_cmd_cli_stats_reset(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    if (nrf_cli_build_in_cmd_common_executed(p_cli, (argc != 1), NULL, 0))
    {
        return;
    }

    p_cli->p_ctx->statistics.log_lost_cnt = 0;
    nrf_queue_max_utilization_reset(
                               ((nrf_cli_log_backend_t *)p_cli->p_log_backend->p_ctx)->p_queue);
}
#endif // NRF_MODULE_ENABLED(NRF_CLI_STATISTICS)

static void nrf_cli_cmd_resize_default(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    if (nrf_cli_build_in_cmd_common_executed(p_cli, (argc != 1), NULL, 0))
    {
        return;
    }

    NRF_CLI_VT100_CMD(p_cli, NRF_CLI_VT100_SETCOL_80);
    p_cli->p_ctx->vt100_ctx.cons.terminal_wid = NRF_CLI_DEFAULT_TERMINAL_WIDTH;
    p_cli->p_ctx->vt100_ctx.cons.terminal_hei = NRF_CLI_DEFAULT_TERMINAL_HEIGHT;
}

static void nrf_cli_cmd_resize(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    ASSERT(p_cli);
    ASSERT(p_cli->p_ctx && p_cli->p_iface && p_cli->p_name);

    if (argc == 1)
    {
        if (terminal_size_get(p_cli,
                              &p_cli->p_ctx->vt100_ctx.cons.terminal_wid,
                              &p_cli->p_ctx->vt100_ctx.cons.terminal_hei) != NRF_SUCCESS)
        {
            p_cli->p_ctx->vt100_ctx.cons.terminal_wid = NRF_CLI_DEFAULT_TERMINAL_WIDTH;
            p_cli->p_ctx->vt100_ctx.cons.terminal_hei = NRF_CLI_DEFAULT_TERMINAL_HEIGHT;
            nrf_cli_warn(p_cli, "No response from the terminal, assumed 80x24 screen size");
        }
        return;
    }

    if (nrf_cli_build_in_cmd_common_executed(p_cli, (argc > 2), NULL, 0))
    {
        return;
    }
    nrf_cli_error(p_cli, "%s:%s%s", argv[0], NRF_CLI_MSG_UNKNOWN_PARAMETER, argv[1]);
}

#if NRF_MODULE_ENABLED(NRF_CLI_VT100_COLORS)
NRF_CLI_CREATE_STATIC_SUBCMD_SET(m_sub_colors)
{
    NRF_CLI_CMD(off,    NULL,   NRF_CLI_HELP_COLORS_OFF,        nrf_cli_cmd_colors_off),
    NRF_CLI_CMD(on,     NULL,   NRF_CLI_HELP_COLORS_ON,         nrf_cli_cmd_colors_on),
    NRF_CLI_SUBCMD_SET_END
};
#endif

NRF_CLI_CREATE_STATIC_SUBCMD_SET(m_sub_echo)
{
    NRF_CLI_CMD(off,    NULL,   NRF_CLI_HELP_ECHO_OFF,          nrf_cli_cmd_echo_off),
    NRF_CLI_CMD(on,     NULL,   NRF_CLI_HELP_ECHO_ON,           nrf_cli_cmd_echo_on),
    NRF_CLI_SUBCMD_SET_END
};

#if NRF_MODULE_ENABLED(NRF_CLI_STATISTICS)
NRF_CLI_CREATE_STATIC_SUBCMD_SET(m_sub_cli_stats)
{
    NRF_CLI_CMD(reset,  NULL,   NRF_CLI_HELP_STATISTICS_RESET,  nrf_cli_cmd_cli_stats_reset),
    NRF_CLI_CMD(show,   NULL,   NRF_CLI_HELP_STATISTICS_SHOW,   nrf_cli_cmd_cli_stats_show),
    NRF_CLI_SUBCMD_SET_END
};
#endif // NRF_MODULE_ENABLED(NRF_CLI_STATISTICS)

NRF_CLI_CREATE_STATIC_SUBCMD_SET(m_sub_cli)
{
#if NRF_MODULE_ENABLED(NRF_CLI_VT100_COLORS)
    NRF_CLI_CMD(colors, &m_sub_colors,      NRF_CLI_HELP_COLORS,        nrf_cli_cmd_colors),
#endif
    NRF_CLI_CMD(echo,   &m_sub_echo,        NRF_CLI_HELP_ECHO,          nrf_cli_cmd_echo),
#if NRF_MODULE_ENABLED(NRF_CLI_STATISTICS)
    NRF_CLI_CMD(stats, &m_sub_cli_stats,    NRF_CLI_HELP_STATISTICS,    nrf_cli_cmd_cli_stats),
#endif
    NRF_CLI_SUBCMD_SET_END
};

NRF_CLI_CREATE_STATIC_SUBCMD_SET(m_sub_resize)
{
    NRF_CLI_CMD(default, NULL, NRF_CLI_HELP_RESIZE_DEFAULT, nrf_cli_cmd_resize_default),
    NRF_CLI_SUBCMD_SET_END
};

NRF_CLI_CMD_REGISTER(clear,     NULL,           NRF_CLI_HELP_CLEAR,     nrf_cli_cmd_clear);
NRF_CLI_CMD_REGISTER(cli,       &m_sub_cli,     NRF_CLI_HELP_CLI,       nrf_cli_cmd_cli);
#if NRF_MODULE_ENABLED(NRF_CLI_HISTORY)
NRF_CLI_CMD_REGISTER(history,   NULL,           NRF_CLI_HELP_HISTORY,   nrf_cli_cmd_history);
#endif
NRF_CLI_CMD_REGISTER(resize,    &m_sub_resize,  NRF_CLI_HELP_RESIZE,    nrf_cli_cmd_resize);

#endif // NRF_MODULE_ENABLED(NRF_CLI_BUILD_IN_CMDS)

#endif // NRF_MODULE_ENABLED(NRF_CLI)

