/* all about esmt factory */

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <hal_timer.h>

#include "inter.h"

static struct nor_info idt_esmt[] =
{
    {
        .model = "en25qh128",
        .id = {0x1c, 0x70, 0x18},
        .total_size = SZ_16M,
        .flag = SUPPORT_GENERAL,
    },
};

static struct nor_factory nor_esmt = {
    .factory = FACTORY_ESMT,
    .idt = idt_esmt,
    .idt_cnt = sizeof(idt_esmt),

    .init = NULL,
    .deinit = NULL,
    .init_lock = NULL,
    .deinit_lock = NULL,
    .lock = NULL,
    .unlock = NULL,
    .islock = NULL,
    .set_quad_mode = NULL,
    .set_4bytes_addr = NULL,
};

int nor_register_factory_esmt(void)
{
    return nor_register_factory(&nor_esmt);
}
