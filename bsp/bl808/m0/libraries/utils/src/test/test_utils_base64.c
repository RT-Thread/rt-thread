/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <FreeRTOS.h>
#ifdef CONFIG_CLI_CMD_ENABLE
#include <cli.h>
#endif
#include "utils_base64.h"
#include <utils_log.h>

#ifdef UTILS_BASE64_TEST

static void cmd_encode(char *buf, int len, int argc, char **argv)
{
    uint32_t input_len, output_len = 0;
    char *inbuf, *outbuf = NULL;

    if (argc != 3)
    {
        log_error("Usage:\r\n");
        log_error("encode_base64 0x420c0000 512\r\n");
        return;
    }

    inbuf = (char *)strtol(argv[1], NULL, 0);
    input_len = strtol(argv[2], NULL, 0);
    if (inbuf != NULL && input_len != 0)
    {
        output_len = 4 * ((input_len + 2) / 3);
        outbuf = calloc(1, output_len);

        if (outbuf)
        {
            if (SUCCESS_RETURN == utils_base64encode((uint8_t *)inbuf, input_len, output_len, (uint8_t *)outbuf, &output_len))
            {
                uint32_t i = 0;
                char *addr = outbuf;
                for (i = 0; i < output_len; i++)
                {
                #ifdef CONFIG_CLI_CMD_ENABLE
                    aos_cli_printf("%c", *(char *)addr);
                #endif
                    addr += 1;
                }
            }
            else
            {
                log_error("base64 encode error\r\n");
            }

            free(outbuf);
        }
        else
        {
            log_error("base64 encode mem not enough %d\r\n", output_len);
        }
    }
    else
    {
        log_error("base64 encode argc error\r\n");
    }

}

#ifdef CONFIG_CLI_CMD_ENABLE
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
        { "encode_base64", "base64 encode", cmd_encode},
};
#endif

int base64_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user) / sizeof(cmds_user[0]));
    return 0;
}
#endif
