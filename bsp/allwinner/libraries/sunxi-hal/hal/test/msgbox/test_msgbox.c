/*
 * Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
 *
 * Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
 * the the people's Republic of China and other countries.
 * All Allwinner Technology Co.,Ltd. trademarks are used with permission.
 *
 * DISCLAIMER
 * THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
 * IF YOU NEED TO INTEGRATE THIRD PARTY'S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR
 * MPEGLA, ETC.) IN ALLWINNERS'SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE
 * TO OBTAIN ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES. ALLWINNER SHALL
 * HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
 * COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
 * YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY'S TECHNOLOGY.
 *
 *
 * THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
 * PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
 * THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
 * OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include <hal_log.h>
#include <hal_cmd.h>
#include <sunxi_hal_pwm.h>
#include <hal_msgbox.h>
#include "../drivers/hal/source/msgbox/platform-msgbox.h"

struct msg_endpoint sedp;

void msgbox_rec(uint32_t d, void *data)
{
    printfFromISR("rec:%d\n", d);
    hal_msgbox_channel_send(&sedp, (void *)&d, sizeof(d));
}

static inline int calculte_n(int local, int remote)
{
    if (remote < local)
        return remote;
    else
        return remote - 1;
}

u32 msgbox_test(void)
{
    struct msg_endpoint *medp = &sedp;
    u32 data = 0;

    medp->rec = msgbox_rec;
    hal_msgbox_alloc_channel(medp, 0, 1, 1);
    hal_msgbox_channel_send(medp, (u8 *)&data, 4);

    while (1) {
        void *msg_sts, *msg_reg, *msg_irq_s;

        msg_sts = (void *)MSGBOX_MSG_STA_REG(
            medp->local_amp,
            calculte_n(medp->local_amp, medp->remote_amp),
            medp->read_ch);
        msg_reg = (void *)MSGBOX_MSG_REG(medp->local_amp,
                         calculte_n(medp->local_amp,
                                medp->remote_amp),
                         medp->read_ch);
        msg_irq_s = (void *)MSGBOX_RD_IRQ_STA_REG(
            medp->local_amp,
            calculte_n(medp->local_amp, medp->remote_amp));

        printf("send data %d\n", data);
        hal_msgbox_channel_send(medp, (void *)&data, sizeof(data));
        break;
    }

        /* writel(1 << (medp->read_ch * 2), msg_irq_s); */

    return 0;
}

static int cmd_test_msgbox(int argc, char **argv)
{
    msgbox_test();
    return 0;
}

FINSH_FUNCTION_EXPORT_CMD(cmd_test_msgbox, hal_msgbox, test msgbox)
