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
#include <hal_cmd.h>
#include <sound/snd_core.h>
#include "sunxi-codec.h"


/*#define TEST_MODE*/

#ifndef u32
#define u32 unsigned int
#endif

#define ADDR_WIDTH  0x3f

u32 read_prcm_wvalue(u32 addr, void *ADDA_PR_CFG_REG);
void write_prcm_wvalue(u32 addr, u32 val, void *ADDA_PR_CFG_REG);

unsigned int sunxi_codec_read(struct snd_codec *codec, unsigned int reg)
{
    /* struct sunxi_codec_info *sunxi_codec = codec->private_data; */
    unsigned int reg_val;

    if (reg >= SUNXI_PR_CFG) {
        reg = reg - SUNXI_PR_CFG;
        return read_prcm_wvalue(reg, codec->codec_base_addr + SUNXI_PR_CFG);
    } else {
#ifdef TEST_MODE
        reg_val = 0x1;
#else
        reg_val = snd_readl(codec->codec_base_addr + reg);
#endif
    }
    return reg_val;
}

unsigned int sunxi_codec_write(struct snd_codec *codec, unsigned int reg, unsigned int val)
{
    /* struct sunxi_codec_info *sunxi_codec = codec->private_data; */

    if (reg >= SUNXI_PR_CFG) {
        reg = reg - SUNXI_PR_CFG;
        write_prcm_wvalue(reg, val, codec->codec_base_addr + SUNXI_PR_CFG);
    } else {
#ifndef TEST_MODE
        snd_writel(val, codec->codec_base_addr + reg);
#endif
    }
    return 0;
}

u32 read_prcm_wvalue(u32 addr, void *ADDA_PR_CFG_REG)
{
        u32 reg = 0;

#ifndef TEST_MODE
        reg = snd_readl(ADDA_PR_CFG_REG);
        reg |= (0x1 << 28);
        snd_writel(reg, ADDA_PR_CFG_REG);

        reg = snd_readl(ADDA_PR_CFG_REG);
        reg &= ~(0x1 << 24);
        snd_writel(reg, ADDA_PR_CFG_REG);

        reg = snd_readl(ADDA_PR_CFG_REG);
        reg &= ~(ADDR_WIDTH << 16);
        reg |= (addr << 16);
        snd_writel(reg, ADDA_PR_CFG_REG);

        reg = snd_readl(ADDA_PR_CFG_REG);
        reg &= (0xff << 0);
#endif

        return reg;
}

void write_prcm_wvalue(u32 addr, u32 val, void *ADDA_PR_CFG_REG)
{
        u32 reg;

#ifndef TEST_MODE
        reg = snd_readl(ADDA_PR_CFG_REG);
        reg |= (0x1 << 28);
        snd_writel(reg, ADDA_PR_CFG_REG);

        reg = snd_readl(ADDA_PR_CFG_REG);
        reg &= ~(ADDR_WIDTH << 16);
        reg |= (addr << 16);
        snd_writel(reg, ADDA_PR_CFG_REG);

        reg = snd_readl(ADDA_PR_CFG_REG);
        reg &= ~(0xff << 8);
        reg |= (val << 8);
        snd_writel(reg, ADDA_PR_CFG_REG);

        reg = snd_readl(ADDA_PR_CFG_REG);
        reg |= (0x1 << 24);
        snd_writel(reg, ADDA_PR_CFG_REG);

        reg = snd_readl(ADDA_PR_CFG_REG);
        reg &= ~(0x1 << 24);
        snd_writel(reg, ADDA_PR_CFG_REG);
#endif
}

#include <console.h>
__attribute__((weak)) void sunxi_audiocodec_reg_dump(void)
{

}

int cmd_audiocodec_dump(int argc, char *argv[])
{
    /*TODO, add read,write function */
    sunxi_audiocodec_reg_dump();
}
FINSH_FUNCTION_EXPORT_CMD(cmd_audiocodec_dump, audiocodec, audiocodec dump reg);
