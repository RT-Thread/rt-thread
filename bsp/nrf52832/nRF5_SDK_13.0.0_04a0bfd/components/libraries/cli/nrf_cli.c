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
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(NRF_CLI)
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>

#include "nrf_cli.h"
#include "nrf_assert.h"

/**
 * @brief Maximum commands per line after tab key press.
 * */
#define NRF_CLI_TAB_CMD_PER_LINE (8)

static void cli_write(nrf_cli_t const * p_cli,
                      void const *      p_data,
                      size_t   length,
                      size_t * p_cnt)
{
    ASSERT(p_cli && p_data);
    ASSERT(p_cli->p_iface->write);
    ret_code_t ret = p_cli->p_iface->write(p_data, length, p_cnt);
    UNUSED_VARIABLE(ret);
}

static void cli_read(nrf_cli_t const * p_cli,
                     void *   p_data,
                     size_t   length,
                     size_t * p_cnt)
{
    ASSERT(p_cli && p_data);
    ASSERT(p_cli->p_iface->read);
    ret_code_t ret = p_cli->p_iface->read(p_data, length, p_cnt);
    UNUSED_VARIABLE(ret);
}

#if NRF_CLI_VT100_COLORS
static void vt100_color_set(nrf_cli_t const * p_cli, vt100_color_t color)
{
    const uint8_t cmd[] = VT100_COLOR(color);

    if (p_cli->p_ctx->vt100_ctx.col.col == color)
    {
        return;
    }

    p_cli->p_ctx->vt100_ctx.col.col = color;
    cli_write(p_cli, cmd, sizeof(cmd), NULL);
}

static void vt100_bgcolor_set(nrf_cli_t const * p_cli, vt100_color_t bgcolor)
{
    const uint8_t cmd[] = VT100_BGCOLOR(bgcolor);

    if (p_cli->p_ctx->vt100_ctx.col.bgcol == bgcolor)
    {
        return;
    }

    p_cli->p_ctx->vt100_ctx.col.bgcol = bgcolor;
    cli_write(p_cli, cmd, sizeof(cmd), NULL);
}

static void vt100_colors_store(nrf_cli_t const * p_cli,
                               vt100_colors_t * p_color)
{
    memcpy(p_color, &p_cli->p_ctx->vt100_ctx.col, sizeof(vt100_colors_t));
}

static void vt100_colors_restore(nrf_cli_t const * p_cli,
                                 vt100_colors_t const * p_color)
{
    vt100_color_set(p_cli, p_color->col);
    vt100_bgcolor_set(p_cli, p_color->bgcol);
}

static void vt100_screen_clear(nrf_cli_t const * p_cli)
{
    static const uint8_t cmd[] = VT100_CLEARSCREEN;
    cli_write(p_cli, cmd, sizeof(cmd), NULL);
}

static void vt100_cursor_set(nrf_cli_t const * p_cli, uint16_t x, uint16_t y)
{
    char cmd[24];
    sprintf(cmd, "%c[%d;%dH", VT100_ASCII_ESC, y + 1, x + 1);

    cli_write(p_cli, cmd, strlen(cmd), NULL);
}
#else
static void vt100_color_set(nrf_cli_t const * p_cli, vt100_color_t color) {}
static void vt100_bgcolor_set(nrf_cli_t const * p_cli, vt100_color_t bgcolor) {}
static void vt100_colors_store(nrf_cli_t const * p_cli,
                               vt100_colors_t * p_color) {}
static void vt100_colors_restore(nrf_cli_t const * p_cli,
                                 vt100_colors_t const * p_color) {}
static void vt100_screen_clear(nrf_cli_t const * p_cli) {}
static void vt100_cursor_set(nrf_cli_t const * p_cli, uint16_t x, uint16_t y) {}
#endif

static void cli_putc(nrf_cli_t const * p_cli, char ch)
{
    cli_write(p_cli, &ch, sizeof(ch), NULL);
}

ret_code_t nrf_cli_init(nrf_cli_t const * p_cli)
{
    ASSERT(p_cli);
    ASSERT(p_cli->p_ctx && p_cli->p_iface && p_cli->p_name && p_cli->p_cmd_set);

    ret_code_t ret = p_cli->p_iface->init();
    if (ret != NRF_SUCCESS)
    {
        return ret;
    }

    memset(p_cli->p_ctx, 0, sizeof(nrf_cli_ctx_t));
    p_cli->p_ctx->state = NRF_CLI_STATE_INITIALIZED;

    vt100_color_set(p_cli, NRF_CLI_NORMAL);
    vt100_bgcolor_set(p_cli, VT100_COLOR_BLACK);
    vt100_cursor_set(p_cli, 0, 0);
    vt100_screen_clear(p_cli);

    return NRF_SUCCESS;
}


ret_code_t nrf_cli_uninit(nrf_cli_t const * p_cli)
{
    ASSERT(p_cli);
    ASSERT(p_cli->p_ctx && p_cli->p_iface && p_cli->p_name && p_cli->p_cmd_set);

    ret_code_t ret = p_cli->p_iface->uninit();
    if (ret != NRF_SUCCESS)
    {
        return ret;
    }

    memset(p_cli->p_ctx, 0, sizeof(nrf_cli_ctx_t));
    p_cli->p_ctx->state = NRF_CLI_STATE_UNINITIALIZED;

    return NRF_SUCCESS;
}

static void cli_state_change(nrf_cli_t const * p_cli, nrf_cli_state_t state)
{
    p_cli->p_ctx->state = state;
    switch (p_cli->p_ctx->state)
    {
        case NRF_CLI_STATE_COLLECT:
            p_cli->p_ctx->cmd_buff_pos = 0;
            nrf_cli_fprintf(p_cli, NRF_CLI_INFO, "%s", p_cli->p_name);
            break;
        default:
            break;
    }
}

ret_code_t nrf_cli_start(nrf_cli_t const * p_cli)
{
    if (p_cli->p_ctx->state != NRF_CLI_STATE_INITIALIZED)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    cli_state_change(p_cli, NRF_CLI_STATE_COLLECT);
    return NRF_SUCCESS;
}

ret_code_t nrf_cli_stop(nrf_cli_t const * p_cli)
{
    if (p_cli->p_ctx->state == NRF_CLI_STATE_INITIALIZED ||
        p_cli->p_ctx->state == NRF_CLI_STATE_UNINITIALIZED)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    cli_state_change(p_cli, NRF_CLI_STATE_INITIALIZED);
    return NRF_SUCCESS;
}

static void cli_handle_tab(nrf_cli_t const * p_cli)
{
    size_t i;

    if (p_cli->p_ctx->cmd_buff_pos == 0)
    {
        /*Show all commands*/
        for (i = 0; i < p_cli->cmd_count; i++)
        {
            if ((i % NRF_CLI_TAB_CMD_PER_LINE) == 0)
            {
                nrf_cli_fprintf(p_cli, NRF_CLI_WARNING, "\r\n");
            }

            nrf_cli_fprintf(p_cli, NRF_CLI_WARNING, "  %s",
                            p_cli->p_cmd_set[i].p_syntax);
        }

        nrf_cli_fprintf(p_cli, NRF_CLI_INFO, "\r\n%s", p_cli->p_name);
        return;
    }

    size_t match_cnt = 0;
    size_t last_match = 0;

    for (i = 0; i < p_cli->cmd_count; i++)
    {
        if (strncmp(p_cli->p_cmd_set[i].p_syntax,
                    p_cli->p_ctx->cmd_buff,
                    p_cli->p_ctx->cmd_buff_pos) != 0)
        {
            continue;
        }

        match_cnt++;
        last_match = i;
    }

    if (match_cnt == 0)
    {
        return;
    }

    if (match_cnt == 1)
    {
        size_t pos = p_cli->p_ctx->cmd_buff_pos;

        strcpy(p_cli->p_ctx->cmd_buff + p_cli->p_ctx->cmd_buff_pos,
               p_cli->p_cmd_set[last_match].p_syntax + pos);

        p_cli->p_ctx->cmd_buff_pos =
                strlen(p_cli->p_cmd_set[last_match].p_syntax);

        p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_pos] = ' ';
        ++p_cli->p_ctx->cmd_buff_pos;
        p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_pos] = '\0';

        nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "%s",
                        p_cli->p_ctx->cmd_buff + pos);
        return;
    }

    uint32_t k = 0;
    for (i = 0; i < p_cli->cmd_count; i++)
    {
        if (strncmp(p_cli->p_cmd_set[i].p_syntax,
                    p_cli->p_ctx->cmd_buff,
                    p_cli->p_ctx->cmd_buff_pos))
        {
            continue;
        }

        if ((k % NRF_CLI_TAB_CMD_PER_LINE) == 0)
        {
            nrf_cli_fprintf(p_cli, NRF_CLI_WARNING, "\r\n");
        }

        nrf_cli_fprintf(p_cli, NRF_CLI_WARNING, "  %s",
                        p_cli->p_cmd_set[i].p_syntax);
        k++;
    }

    nrf_cli_fprintf(p_cli, NRF_CLI_INFO, "\r\n%s", p_cli->p_name);
    p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_pos] = '\0';
    nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "%s", p_cli->p_ctx->cmd_buff);

    return;
}

#if NRF_CLI_HISTORY_COUNT != 0
static size_t cli_history_increment_mod(size_t act)
{
    if (act < (NRF_CLI_HISTORY_COUNT - 1))
    {
        return act + 1;
    }

    return 0;
}

static size_t cli_history_decrement_mod(size_t act)
{
    if (act > 0)
    {
        return act - 1;
    }

    return NRF_CLI_HISTORY_COUNT - 1;
}


static void cli_history_handle(nrf_cli_t const * p_cli, bool up)
{
    size_t len;
    size_t act = p_cli->p_ctx->cmd_history_act;
    if (!up)
    {
        if (act == p_cli->p_ctx->cmd_history_pos)
        {
            return;
        }

        act = cli_history_increment_mod(act);
        if (act == p_cli->p_ctx->cmd_history_pos &&
            p_cli->p_ctx->cmd_history_mode)
        {
            size_t clear_size = strlen(p_cli->p_ctx->cmd_buff);
            memset(p_cli->p_ctx->cmd_buff, ' ', clear_size);
            p_cli->p_ctx->cmd_buff[clear_size] = '\0';
            nrf_cli_fprintf(p_cli, NRF_CLI_INFO, "\r%s%s\r",
                            p_cli->p_name,
                            p_cli->p_ctx->cmd_buff);

            p_cli->p_ctx->cmd_history_mode = false;
            p_cli->p_ctx->cmd_history_act = act;
            cli_state_change(p_cli, NRF_CLI_STATE_COLLECT);
            return;
        }
    }
    else
    {
        if (act == p_cli->p_ctx->cmd_history_pos &&
            p_cli->p_ctx->cmd_history_mode)
        {
            return;
        }
        act = cli_history_decrement_mod(act);
    }

    p_cli->p_ctx->cmd_history_mode = true;
    len = strlen(p_cli->p_ctx->cmd_history_buff[act]);
    if (!len)
    {
        return;
    }

    size_t clear_size = strlen(p_cli->p_ctx->cmd_buff);
    if (clear_size > len)
    {
        nrf_cli_fprintf(p_cli, NRF_CLI_INFO, "\r%s", p_cli->p_name);
        memset(p_cli->p_ctx->cmd_buff, ' ', clear_size);
        p_cli->p_ctx->cmd_buff[clear_size] = '\0';
        nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "%s", p_cli->p_ctx->cmd_buff);
    }

    p_cli->p_ctx->cmd_history_act = act;
    p_cli->p_ctx->cmd_buff_pos = len;

    strcpy(p_cli->p_ctx->cmd_buff, p_cli->p_ctx->cmd_history_buff[act]);
    nrf_cli_fprintf(p_cli, NRF_CLI_INFO, "\r%s", p_cli->p_name);
    nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "%s", p_cli->p_ctx->cmd_buff);
}
#else
static void cli_history_handle(nrf_cli_t const * p_cli, bool up)
{
}
#endif

static void cli_state_collect(nrf_cli_t const * p_cli)
{
    size_t count = 0;
    char data = '\0';

    while (1)
    {
        cli_read(p_cli, &data, sizeof(data), &count);
        if (count == 0)
        {
            return;
        }

        if (p_cli->p_ctx->escape)
        {
            p_cli->p_ctx->escape = false;
            if (data == '[')
            {
                p_cli->p_ctx->arrow = true;
                return;
            }
        }

        if (p_cli->p_ctx->arrow)
        {
            p_cli->p_ctx->arrow = false;
            switch (data)
            {
                case 'A': /*UP arrow*/
                    cli_history_handle(p_cli, true);
                    break;
                case 'B': /*DOWN arrow*/
                    cli_history_handle(p_cli, false);
                    break;
                default:
                    break;
            }
            return;
        }

        switch (data)
        {
            case VT100_ASCII_ESC:
                p_cli->p_ctx->escape = true;
                break;
            case '\0':
                break;
            case '\t':
                cli_handle_tab(p_cli);
                break;
            case '\n':
                break;
            case '\r':
                if (p_cli->p_ctx->cmd_buff_pos == 0)
                {
                    nrf_cli_fprintf(p_cli, NRF_CLI_INFO, "\r\n", p_cli->p_name);
                    cli_state_change(p_cli, NRF_CLI_STATE_COLLECT);
                    break;
                }

                p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_pos] = '\0';
                ++p_cli->p_ctx->cmd_buff_pos;
                cli_state_change(p_cli, NRF_CLI_STATE_EXECUTE);
                break;
            case VT100_ASCII_BSPACE: //ASCII backspace
            case VT100_ASCII_DEL:    //ASCII delete

                if (p_cli->p_ctx->cmd_buff_pos == 0)
                {
                    break;
                }

                cli_putc(p_cli, VT100_ASCII_BSPACE);
                cli_putc(p_cli, ' ');
                cli_putc(p_cli, VT100_ASCII_BSPACE);
                --p_cli->p_ctx->cmd_buff_pos;

                break;
            default:

                if (!isprint((int)data))
                {
                    break;
                }

                p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_pos] = data;
                ++p_cli->p_ctx->cmd_buff_pos;

                if (p_cli->p_ctx->cmd_buff_pos == NRF_CLI_CMD_BUFF_SIZE)
                {
                    p_cli->p_ctx->cmd_buff_pos = 0;
                    nrf_cli_fprintf(p_cli, NRF_CLI_ERROR,
                            "\r\n input buffer overflow NRF_CLI_CMD_BUFF_SIZE");
                    cli_state_change(p_cli, NRF_CLI_STATE_COLLECT);
                    return;
                }

                cli_putc(p_cli, data);
                break;
        }
    }
}

#if NRF_CLI_HISTORY_COUNT != 0
static void cli_history_save(nrf_cli_t const * p_cli)
{
    p_cli->p_ctx->cmd_history_mode = false;
    (void)strncpy(p_cli->p_ctx->cmd_history_buff[p_cli->p_ctx->cmd_history_pos],
                  p_cli->p_ctx->cmd_buff,
                  p_cli->p_ctx->cmd_buff_pos);

    size_t pos = p_cli->p_ctx->cmd_buff_pos;
    p_cli->p_ctx->cmd_history_buff[p_cli->p_ctx->cmd_history_pos][pos] = '\0';

    p_cli->p_ctx->cmd_history_pos =
            cli_history_increment_mod(p_cli->p_ctx->cmd_history_pos);
    p_cli->p_ctx->cmd_history_act = p_cli->p_ctx->cmd_history_pos;
}
#else
static void cli_history_save(nrf_cli_t const * p_cli) {}
#endif

static void cli_state_execute(nrf_cli_t const * p_cli)
{
    /*Create argument list.*/
    char * p_start = p_cli->p_ctx->cmd_buff;
    const char * p_end = &p_cli->p_ctx->cmd_buff[p_cli->p_ctx->cmd_buff_pos];

    cli_history_save(p_cli);

    memset(p_cli->p_ctx->argv, 0, sizeof(p_cli->p_ctx->argv));

    p_cli->p_ctx->argc = 1;
    p_cli->p_ctx->argv[0] = p_start;


    bool was_blank = false;
    while (p_start < p_end)
    {
        if (*p_start == ' ' || *p_start == '\t')
        {
            *p_start = '\0';
            was_blank = true;
            ++p_start;
            continue;
        }

        if (was_blank && *p_start != '\0')
        {
            if (p_cli->p_ctx->argc >= NRF_CLI_ARGC_MAX)
            {
                nrf_cli_fprintf(p_cli, NRF_CLI_ERROR,
                        "\r\n too many parameters >= NRF_CLI_ARGC_MAX\r\n");
                cli_state_change(p_cli, NRF_CLI_STATE_COLLECT);
                return;
            }

            was_blank = false;
            p_cli->p_ctx->argv[p_cli->p_ctx->argc] = p_start;
            ++p_cli->p_ctx->argc;
        }

        ++p_start;
    }

    /*Try match command syntax.*/
    for (size_t i = 0; i < p_cli->cmd_count; ++i) {

        if (strcmp(p_cli->p_ctx->argv[0], p_cli->p_cmd_set[i].p_syntax) != 0)
        {
            continue;
        }

        ASSERT(p_cli->p_cmd_set[i].handler);
        p_cli->p_ctx->p_current_cmd = &p_cli->p_cmd_set[i];

        nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "\r\n");
        p_cli->p_ctx->p_current_cmd->handler(p_cli,
                                              p_cli->p_ctx->argc,
                                              p_cli->p_ctx->argv);
        cli_state_change(p_cli, NRF_CLI_STATE_COLLECT);
        return;

    }

    nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "%s", "\r\ncommand not found\r\n");
    cli_state_change(p_cli, NRF_CLI_STATE_COLLECT);
}

void nrf_cli_process(nrf_cli_t const * p_cli)
{
    ASSERT(p_cli);

    switch (p_cli->p_ctx->state)
    {
        case NRF_CLI_STATE_UNINITIALIZED:
        case NRF_CLI_STATE_INITIALIZED:
            break;
        case NRF_CLI_STATE_COLLECT:
            cli_state_collect(p_cli);
            break;
        case NRF_CLI_STATE_EXECUTE:
            cli_state_execute(p_cli);
            break;
        default:
            break;
    }

}


void nrf_cli_fprintf(nrf_cli_t const * p_cli,
                     vt100_color_t color,
                     const char * p_fmt,
                     ...)
{
    vt100_colors_t col;
    vt100_colors_store(p_cli, &col);

    va_list args = {0};
    va_start(args, p_fmt);

    int32_t ret = vsnprintf(p_cli->p_ctx->printf_buff,
                            NRF_CLI_PRINTF_BUFF_SIZE,
                            p_fmt,
                            args);
    va_end(args);
    UNUSED_VARIABLE(ret);
    vt100_color_set(p_cli, color);
    cli_write(p_cli,
              p_cli->p_ctx->printf_buff,
              strlen(p_cli->p_ctx->printf_buff),
              NULL);
    vt100_colors_restore(p_cli, &col);
}

void nrf_cli_getopt_ctx_init(size_t argc,
                             char ** pp_argv,
                             size_t opt_count,
                             nrf_cli_getopt_option_t const * p_opt,
                             nrf_cli_getopt_ctx_t * p_optctx)
{
    ASSERT(p_optctx);
    ASSERT(p_opt);

    p_optctx->argc = argc;
    p_optctx->pp_argv = pp_argv;
    p_optctx->opt_count = opt_count;
    p_optctx->p_opt = p_opt;
    p_optctx->arg_idx = 0;
    p_optctx->p_optarg = NULL;
}

int32_t nrf_cli_getopt(nrf_cli_getopt_ctx_t * p_optctx)
{
    ASSERT(p_optctx);

    if (p_optctx->arg_idx == p_optctx->argc)
    {
        /*No more arguments to parse.*/
        return -1;
    }

    /*Reset option argument*/
    p_optctx->p_optarg = NULL;

    /*Set current token.*/
    const char * p_current = p_optctx->pp_argv[p_optctx->arg_idx];
    ++p_optctx->arg_idx;

    ASSERT(p_current);

    /*Current if argument is an option. It must start with -. */
    if (p_current[0] != '-')
    {
        /* Argument is not an option. Set optarg and return '?' as a no option
         * indicator. */
        p_optctx->p_optarg = p_current;
        return '?';
    }

    nrf_cli_getopt_option_t const * p_found_opt = NULL;

    /*Short option option syntax*/
    if ((p_current[1]) != '\0' && (p_current[2] == '\0'))
    {

        for (size_t i = 0; i < p_optctx->opt_count; i++)
        {
            if (p_current[1] != p_optctx->p_opt[i].optname_short)
            {
                continue;
            }

            p_found_opt = &p_optctx->p_opt[i];
            break;
        }
    }
    else if (p_current[1] == '-' && p_current[2] != '\0')
    {
        /*Long option option syntax*/
        const char * p_syntax_start = &p_current[2];

        for (size_t i = 0; i < p_optctx->opt_count; i++)
        {
            if (strcmp(p_syntax_start, p_optctx->p_opt[i].p_optname) != 0)
            {
                continue;
            }

            p_found_opt = &p_optctx->p_opt[i];
            break;
        }
    }
    else
    {
        /*Option syntax error.*/
        p_optctx->p_optarg = p_current;
        return '?';
    }

    if (p_found_opt == NULL)
    {
        p_optctx->p_optarg = p_current;
        return '?';
    }

    if (p_found_opt->type == NRF_CLI_GETOPT_TYPE_NO_ARG)
    {
        return p_found_opt->optname_short;
    }

    char const * p_arg = p_optctx->pp_argv[p_optctx->arg_idx];
    if (p_optctx->arg_idx == p_optctx->argc || p_arg[0] == '-')
    {
        if (p_found_opt->type == NRF_CLI_GETOPT_TYPE_REQUIRED)
        {
            /*Argument is required but it seems that it is an option.*/
            p_optctx->p_optarg = p_current;
            return '?';
        }
    }

    ++p_optctx->arg_idx;

    p_optctx->p_optarg = p_arg;
    return p_found_opt->optname_short;
}

void nrf_cli_opt_help_show(nrf_cli_t const * p_cli,
                           nrf_cli_getopt_option_t const * p_opt,
                           size_t opt_len)
{
    /*Show current command help string*/
    nrf_cli_fprintf(p_cli,
                    NRF_CLI_NORMAL,
                    "%s - %s\r\n",
                    p_cli->p_ctx->p_current_cmd->p_syntax,
                    p_cli->p_ctx->p_current_cmd->p_help);

    nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "Options:\r\n");

    for (size_t i = 0; i < opt_len; ++i)
    {

        nrf_cli_fprintf(p_cli,
                        NRF_CLI_NORMAL,
                        "  -%c, --%s\t%s\r\n",
                        p_opt[i].optname_short,
                        p_opt[i].p_optname,
                        p_opt[i].p_optname_help);
    }
}

void nrf_cli_cmd_list(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    /*Show help of command.*/
    bool verbose = false;

    static const nrf_cli_getopt_option_t opt[] = {

        NRF_CLI_OPT(
            "help",
            'h',
            NRF_CLI_GETOPT_TYPE_NO_ARG,
            "show command help"
        ),
        NRF_CLI_OPT(
            "verbose",
            'v',
            NRF_CLI_GETOPT_TYPE_NO_ARG,
            "show all command help strings"
        )
    };

    nrf_cli_getopt_ctx_t opt_ctx;
    nrf_cli_getopt_ctx_init(argc - 1, argv + 1, ARRAY_SIZE(opt), opt, &opt_ctx);

    do
    {
        int32_t c = nrf_cli_getopt(&opt_ctx);
        if (c < 0)
        {
            break;
        }

        switch (c)
        {
            case 'v':
                verbose = true;
                break;
            case 'h':
                nrf_cli_opt_help_show(p_cli, opt, ARRAY_SIZE(opt));
                return;
            case '?':
                nrf_cli_fprintf(p_cli, NRF_CLI_WARNING,
                                "list: unknown option: %s\r\n",
                                nrf_cli_optarg_get(&opt_ctx));
                break;
            default:
                break;
        }
    } while (1);


    /*Find command in command list*/
    for (size_t i = 0; i < p_cli->cmd_count; ++i)
    {
        if (verbose)
        {
            nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "  %s - %s\r\n",
                            p_cli->p_cmd_set[i].p_syntax,
                            p_cli->p_cmd_set[i].p_help);
        }
        else
        {
            nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "  %s\r\n",
                            p_cli->p_cmd_set[i].p_syntax);
        }
    }
}

void nrf_cli_cmd_clear(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    (void)argc;
    (void)argv;
    vt100_cursor_set(p_cli, 0, 0);
    vt100_screen_clear(p_cli);
}

void nrf_cli_cmd_history(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    (void)argc;
    (void)argv;
#if NRF_CLI_HISTORY_COUNT
    size_t pos = p_cli->p_ctx->cmd_history_pos;
    size_t i, j = 0;

    for (i = 0; i < NRF_CLI_HISTORY_COUNT; ++i)
    {
        const char * p_entry = p_cli->p_ctx->cmd_history_buff[pos];
        pos = cli_history_increment_mod(pos);
        size_t len = strlen(p_entry);
        if (!len)
        {
            continue;
        }

        nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "[%3d] %s\r\n", j++, p_entry);
    }
#else
    nrf_cli_fprintf(p_cli, NRF_CLI_WARNING, " history: not available\r\n");
#endif
}

#endif // NRF_MODULE_ENABLED(NRF_CLI)
