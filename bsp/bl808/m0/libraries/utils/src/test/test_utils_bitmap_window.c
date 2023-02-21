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
#include <utils_bitmap_window.h>

#ifdef CONFIG_CLI_CMD_ENABLE
#include <cli.h>
#endif
#include <stdio.h>

static void cmd_bitmap_window_test(char *buf, int len, int argc, char **argv)
{
    int ret;
    struct utils_bitmap_ctx ctx;

    utils_bitmap_window_init(&ctx, 0, 4095);

    printf("Set Seq 1 2 3 4 5 6 7...\r\n");
    utils_bitmap_window_bit_set(&ctx, 1);
    utils_bitmap_window_bit_set(&ctx, 2);
    utils_bitmap_window_bit_set(&ctx, 3);
    utils_bitmap_window_bit_set(&ctx, 4);
    utils_bitmap_window_bit_set(&ctx, 5);
    utils_bitmap_window_bit_set(&ctx, 6);
    ret = utils_bitmap_window_bit_set(&ctx, 7);
    printf("  Got ssn %d(0) Bitmap %llx(0), ret %x\r\n",
        utils_bitmap_window_ssn_get(&ctx),
        utils_bitmap_window_map_get(&ctx),
        ret
    );

    printf("Set Seq 0 ...\r\n");
    ret = utils_bitmap_window_bit_set(&ctx, 0);
    printf("  Got ssn %d(8) Bitmap %llx(0), ret %x\r\n",
        utils_bitmap_window_ssn_get(&ctx),
        utils_bitmap_window_map_get(&ctx),
        ret
    );

    printf("Set Seq 0 ...\r\n");
    ret = utils_bitmap_window_bit_set(&ctx, 0);
    printf("  Got ssn %d(8) Bitmap %llx(0), ret %x\r\n",
        utils_bitmap_window_ssn_get(&ctx),
        utils_bitmap_window_map_get(&ctx),
        ret
    );

    printf("Set Seq 9 ...\r\n");
    ret = utils_bitmap_window_bit_set(&ctx, 9);
    printf("  Got ssn %d(8) Bitmap %llx(2), ret %x\r\n",
        utils_bitmap_window_ssn_get(&ctx),
        utils_bitmap_window_map_get(&ctx),
        ret
    );

    printf("Set Seq 9 ...\r\n");
    ret = utils_bitmap_window_bit_set(&ctx, 9);
    printf("  Got ssn %d(8) Bitmap %llx(2), ret %d\r\n",
        utils_bitmap_window_ssn_get(&ctx),
        utils_bitmap_window_map_get(&ctx),
        ret
    );

}

#ifdef CONFIG_CLI_CMD_ENABLE
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
  {"utils_bitmap_widow_test", "bitmap window test", cmd_bitmap_window_test},
};
#endif

int utils_bitmap_window_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user) / sizeof(cmds_user[0]));
    return 0;
}
