/*
* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
*
* Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
* the the people's Republic of China and other countries.
* All Allwinner Technology Co.,Ltd. trademarks are used with permission.
*
* DISCLAIMER
* THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
* IF YOU NEED TO INTEGRATE THIRD PARTY’S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
* IN ALLWINNERS’SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
* ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
* ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
* COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
* YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY’S TECHNOLOGY.
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
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <hal_cmd.h>
#include <aw-alsa-lib/control.h>
#include <aw-alsa-lib/pcm.h>
#include <aw-alsa-lib/common.h>

static void card_list(void)
{
    int num, i;
    num = snd_card_num();
    if (num < 0) {
        printf("no registered card...\n");
        return;
    }
    printf("Sound Card list:\n");
    printf("%8s%20s\n", "card_num", "card_name");
    for (i = 0; i < num; i++) {
        if (i != snd_card_index(snd_card_name(i))) {
            printf("card_num%d not equal index convert"
                "from name:%s\n", i, snd_card_name(i));
            return;
        }
        printf("%8d%20s\n", i, snd_card_name(i));
    }
}


static void usage(void)
{
    printf("Usage: soundcard [option]\n");
    printf("-c,          sound card number\n");
    printf("-l,          sound card list\n");
    printf("-i,          sound card info\n");
    printf("-s,          sound card pcm stream info, 0-playback; 1-capture\n");
    printf("\n");
}

int cmd_soundcard(int argc, char *argv[])
{
    int c;
    int card_num = -1;
    int stream = -1;

    while ((c = getopt(argc, argv, "c:lis:h")) != -1) {
        switch (c) {
        case 'c':
            card_num = atoi(optarg);
            break;
        case 'l':
            card_list();
            return 0;
        case 'i':
            return snd_card_info(card_num);
        case 's':
            stream = atoi(optarg);
            if (stream != 0 && stream != 1) {
                printf("unknown stream:%d\n", stream);
            }
            return snd_card_pcm_info(card_num, 0, stream);
        default:
            usage();
            return 0;
        }
    }

    return 0;
}

FINSH_FUNCTION_EXPORT_CMD(cmd_soundcard, soundcard, soundcard info);
