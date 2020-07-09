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
#ifndef NRF_CLI_H__
#define NRF_CLI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "sdk_common.h"
#include "nrf_cli_vt100.h"

/**
 * @defgroup nrf_cli Command Line Interface
 * @ingroup app_common
 *
 * @brief Module for unified command line handling.
 *
 * @{
 */

/**
 * @brief Alias to @ref nrf_cli. Must be created here to satisfy
 *        module declaration order dependencies.
 *        */
typedef struct nrf_cli nrf_cli_t;

/**
 * @brief CLI command descriptor.
 **/
typedef struct {
    const char * p_syntax;  //!< Command syntax strings.
    const char * p_help;    //!< Command help string.

    void (*handler)(nrf_cli_t const * p_cli, size_t argc, char **argv); //!< Command handler.
} nrf_cli_cmd_t;


/**
 * @brief Initializes CLI command descriptor (@ref nrf_cli_cmd_t).
 *
 * @param _syntax  Command syntax (for example: "history").
 * @param _help    Command help string (string used in built-in help command).
 * @param _handler Handler function.
 * */
#define NRF_CLI_CMD(_syntax, _help, _handler)    {    \
        .p_syntax = _syntax,                          \
        .p_help = _help,                              \
        .handler = _handler,                          \
}

/**
 * @brief Internal CLI state.
 * */
typedef enum {
    NRF_CLI_STATE_UNINITIALIZED,    //!< State uninitialized.
    NRF_CLI_STATE_INITIALIZED,      //!< State initialized.
    NRF_CLI_STATE_COLLECT,          //!< State collect.
    NRF_CLI_STATE_EXECUTE,          //!< State execute.
} nrf_cli_state_t;

/**
 * @brief Unified CLI transport interface.
 * */
typedef struct {
    /**
     * @brief Initializes CLI transport interface.
     *
     * @return Standard error code.
     * */
    ret_code_t (*init)(void);

    /**
     * @brief Uninitialize CLI transport interface.
     *
     * @return Standard error code.
     * */
    ret_code_t (*uninit)(void);

    /**
     * @brief Writes data to transport interface.
     *
     * @param p_data Source buffer.
     * @param length Source buffer length.
     * @param p_cnt  Number of bytes written (NULL might be passed).
     *
     * @return Standard error code.
     * */
    ret_code_t (*write)(const void * p_data, size_t length, size_t * p_cnt);

    /**
     * @brief Reads data from transport interface.
     *
     * @param p_data Destination buffer.
     * @param length Destination buffer length.
     * @param p_cnt  Number of bytes received (NULL might be passed).
     *
     * @return Standard error code.
     * */
    ret_code_t (*read)(void * p_data, size_t length, size_t * p_cnt);

} nrf_cli_transport_t;

/**
 * @brief CLI instance context.
 * */
typedef struct {
    nrf_cli_state_t       state;         //!< Internal module state.
    nrf_cli_cmd_t const * p_current_cmd; //!< Current executed command.

    vt100_ctx_t vt100_ctx;          //!< VT100 color and cursor position.

    bool   escape;                  //!< Escape sequence indicator.
    bool   arrow;                   //!< Arrow escape sequence indicator.
    size_t argc;                    //!< Number of arguments.
    char * argv[NRF_CLI_ARGC_MAX];  //!< Argument list.

    size_t cmd_buff_pos;                        //!< Command buffer position.
    char   cmd_buff[NRF_CLI_CMD_BUFF_SIZE];     //!< Command input buffer.

    char printf_buff[NRF_CLI_PRINTF_BUFF_SIZE]; //!< Printf buffer size.

#if NRF_CLI_HISTORY_COUNT != 0
    bool   cmd_history_mode;
    size_t cmd_history_pos;     //!< Command history position.
    size_t cmd_history_act;     //!< Command history last entry.
    char   cmd_history_buff[NRF_CLI_HISTORY_COUNT][NRF_CLI_CMD_BUFF_SIZE]; //!< Command history buffer.
#endif
} nrf_cli_ctx_t;

/**
 * @brief CLI instance internals.
 *
 * @ref nrf_cli_t
 * */
struct nrf_cli {
    const char * p_name;    //!< Terminal name.

    nrf_cli_transport_t const * p_iface;    //!< Transport interface.
    nrf_cli_cmd_t const *       p_cmd_set;   //!< Command set array.
    size_t  cmd_count;        //!< Command set array size.
    nrf_cli_ctx_t * p_ctx;    //!< Internal context.
};


/**
 * @brief Macro for defining command line interface instance.
 *
 * @param name              Instance name.
 * @param cli_prefix        CLI prefix string.
 * @param transport_iface   Transport interface.
 * @param cmd_set_tab       Command set array.
 * */
#define NRF_CLI_DEF(name, cli_prefix, transport_iface, cmd_set_tab)     \
        static nrf_cli_ctx_t CONCAT_2(name, _ctx);                      \
        static const nrf_cli_t name = {                                 \
            .p_name = cli_prefix,                                       \
            .p_iface = &transport_iface,                                \
            .p_cmd_set = cmd_set_tab,                                   \
            .cmd_count = ARRAY_SIZE(cmd_set_tab),                       \
            .p_ctx = &CONCAT_2(name, _ctx),                             \
        }

/**
 * @brief Initializes a transport layer and internal CLI state.
 *
 * @param p_cli CLI instance.
 *
 * @return Standard error code.
 * */
ret_code_t nrf_cli_init(nrf_cli_t const * p_cli);

/**
 * @brief Uninitializes a transport layer and internal CLI state.
 *
 * @param p_cli CLI instance.
 *
 * @return Standard error code.
 * */
ret_code_t nrf_cli_uninit(nrf_cli_t const * p_cli);

/**
 * @brief Start CLI processing.
 *
 * @param p_cli CLI instance.
 *
 * @return Standard error code.
 * */
ret_code_t nrf_cli_start(nrf_cli_t const * p_cli);

/**
 * @brief Stop CLI processing.
 *
 * @param p_cli CLI instance.
 *
 * @return Standard error code.
 * */
ret_code_t nrf_cli_stop(nrf_cli_t const * p_cli);

#define NRF_CLI_NORMAL   VT100_COLOR_WHITE  /**< Normal color printf.  */
#define NRF_CLI_INFO     VT100_COLOR_GREEN  /**< Info color printf.    */
#define NRF_CLI_WARNING  VT100_COLOR_YELLOW /**< Warning color printf. */
#define NRF_CLI_ERROR    VT100_COLOR_RED    /**< Error color printf.   */

/**
 * @brief Printf like function, which send formated data stream to CLI.
 *
 * @param p_cli CLI instance.
 * @param color Printf color.
 * @param p_fmt Format string.
 * @param ...   List of parameters to print.
 * */
void nrf_cli_fprintf(nrf_cli_t const * p_cli,
                     vt100_color_t color,
                     const char * p_fmt,
                     ...);

/**
 * @brief Process function, which should be executed when data is ready
 *        in transport interface.
 *
 * @param p_cli CLI instance.
 * */
void nrf_cli_process(nrf_cli_t const * p_cli);

/**
 * @brief Option argument type.
 * */
typedef enum {
    NRF_CLI_GETOPT_TYPE_NO_ARG,     /**< No argument required.*/
    NRF_CLI_GETOPT_TYPE_REQUIRED,   /**< Argument required.*/
    NRF_CLI_GETOPT_TYPE_OPTIONAL,   /**< Argument optional.*/
} nrf_cli_getopt_type_t;


/**
 * @brief Option descriptor.
 * */
typedef struct {
    const char * p_optname;         //!< Option long name.
    const char   optname_short;     //!< Option short name.
    nrf_cli_getopt_type_t type;     //!< Option type.
    const char * p_optname_help;    //!< Option help string.
} nrf_cli_getopt_option_t;


/**
 * @brief Option structure initializer @ref nrf_cli_getopt_option_t.
 *
 * @param _optname    Option name long.
 * @param _shortname  Option name short.
 * @param _type       Option type @ref nrf_cli_getopt_type_t.
 * @param _help       Option help string.
 * */
#define NRF_CLI_OPT(_optname, _shortname, _type, _help)    {    \
        .p_optname = _optname,                                  \
        .optname_short = _shortname,                            \
        .type = _type,                                          \
        .p_optname_help = _help,                                \
}

/**
 * @brief Getopt parser context.
 * */
typedef struct {
    size_t argc;            //!< Number of arguments.
    char ** pp_argv;        //!< Argument list.
    size_t arg_idx;         //!< Current argument index.
    const char * p_optarg;  //!< Current option argument.

    nrf_cli_getopt_option_t const * p_opt;  //!< Option list.
    size_t opt_count;                       //!< Option list size.
} nrf_cli_getopt_ctx_t;


/**
 * @brief Initializes getopt parser context.
 *
 * @param argc      Number of arguments.
 * @param pp_argv   Argument list.
 * @param opt_count Number of options.
 * @param p_opt     Option array.
 * @param p_optctx  Option parser context.
 * */
void nrf_cli_getopt_ctx_init(size_t argc,
                             char ** pp_argv,
                             size_t opt_count,
                             nrf_cli_getopt_option_t const * p_opt,
                             nrf_cli_getopt_ctx_t * p_optctx);

/**
 * @brief Standard library getopt/getopt_long method replacement.
 *
 * @param p_optctx  Option parser context.
 *
 * @return Parsed option (one letter options are supported by this parser).
 * @retval '?' unknown option / no required argument.
 * @retval -1 if all options have been processed.
 * @retval other if option was successfully parsed.
 * */
int32_t nrf_cli_getopt(nrf_cli_getopt_ctx_t * p_optctx);

/**
 * @brief Returns handle to current parsed argument
 *        (optarg variable replacement).
 *
 * @warning This call is only valid while @ref nrf_cli_getopt
 *          is returning >= 0.
 * @param p_optctx  Option parser context.
 *
 * @return Handle to option argument.
 *  */
__STATIC_INLINE const char * nrf_cli_optarg_get(nrf_cli_getopt_ctx_t * p_optctx)
{
    return p_optctx->p_optarg;
}

/**
 * @brief Shows command help and options. May be used as default '-h' option
 *        handler. It will print actual command help and option description:
 *
 * Example output:
 * @code
   nrf_cli:~$ list -h
   list - list all commands
   Options:
     -h, --help    show command help
     -v, --verbose show all command help strings
 * @endcode
 *
 * @param p_cli     CLI instance.
 * @param p_opt     Option array.
 * @param opt_len   Option array size.
 * */
void nrf_cli_opt_help_show(nrf_cli_t const * p_cli,
                           nrf_cli_getopt_option_t const * p_opt,
                           size_t opt_len);

/**
 * @brief List command handler.
 *
 * @param p_cli CLI instance.
 * @param argc  Number of argv parameters.
 * @param argv  Parameter list.
 * */
void nrf_cli_cmd_list(nrf_cli_t const * p_cli, size_t argc, char **argv);

/**
 * @brief Clear screen command handler.
 *
 * @param p_cli CLI instance.
 * @param argc  Number of argv parameters.
 * @param argv  Parameter list.
 **/
void nrf_cli_cmd_clear(nrf_cli_t const * p_cli, size_t argc, char **argv);

/**
 * @brief Show history command handler.
 *
 * @param p_cli CLI instance.
 * @param argc  Number of argv parameters.
 * @param argv  Parameter list.
 **/
void nrf_cli_cmd_history(nrf_cli_t const * p_cli, size_t argc, char **argv);
/**
 * @brief Built-in command set.
 * */
#define NRF_CLI_BUILTIN_CMD_SET                                         \
        NRF_CLI_CMD("list", "list all commands", nrf_cli_cmd_list),     \
        NRF_CLI_CMD("clear", "clear screen", nrf_cli_cmd_clear),        \
        NRF_CLI_CMD("history", "command history", nrf_cli_cmd_history)  \

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* NRF_CLI_H__ */
