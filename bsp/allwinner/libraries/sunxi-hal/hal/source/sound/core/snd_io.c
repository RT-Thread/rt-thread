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
#include <sound/snd_core.h>

 /*#define SND_IO_DEBUG */
#ifdef SND_IO_DEBUG
#define snd_io_debug        printf
#else
#define snd_io_debug(fmt, args...)
#endif

unsigned int snd_codec_read(struct snd_codec *codec, unsigned int reg)
{
    unsigned int val = 0;
//        uint32_t __cpsr;
        /*__cpsr = hal_spin_lock_irqsave();*/

    if (codec->read)
        val = codec->read(codec, reg);
    else
        val = snd_readl(codec->codec_base_addr + reg);

        /*hal_spin_unlock_irqrestore(__cpsr);*/
    snd_io_debug("reg=0x%x, val:0x%x\n", reg, val);

    return val;
}

int snd_codec_write(struct snd_codec *codec, unsigned int reg, unsigned int val)
{
    int ret = 0;
//        uint32_t __cpsr;
        /*__cpsr = hal_spin_lock_irqsave();*/

    if (codec->write)
        ret = codec->write(codec, reg, val);
    else
        ret = snd_writel(val, codec->codec_base_addr + reg);

        /*hal_spin_unlock_irqrestore(__cpsr);*/
    snd_io_debug("reg=0x%x, val=0x%x\n", reg, val);

    return ret;
}

int snd_codec_update_bits(struct snd_codec *codec, unsigned int reg,
                unsigned int mask, unsigned int value)
{
    int ret = 0;
    unsigned int old, new;
    bool change;
//        uint32_t __cpsr;
        /*__cpsr = hal_spin_lock_irqsave();*/

    if (codec->read)
        old = codec->read(codec, reg);
    else
        old = snd_readl(codec->codec_base_addr + reg);
    snd_io_debug("old: 0X%x\n", old);
    new = (old & ~mask) | (value & mask);
    snd_io_debug("new: 0X%x\n", new);
    change = old != new;
    if (change) {
        if (codec->write)
            ret = codec->write(codec, reg, new);
        else
            ret = snd_writel(new, codec->codec_base_addr + reg);
    }

        /*hal_spin_unlock_irqrestore(__cpsr);*/
    snd_io_debug("reg=0x%x, mask=0x%x, val=0x%x, change=%u\n", reg, mask, value, change);

    return ret;
}

unsigned int snd_platform_read(struct snd_platform *platform, unsigned int reg)
{
    unsigned int val = 0;
//        uint32_t __cpsr;
        /*__cpsr = hal_spin_lock_irqsave();*/

    val = snd_readl(platform->mem_base + reg);

        /*hal_spin_unlock_irqrestore(__cpsr);*/
    snd_io_debug("reg=0x%x, val=0x%x\n", reg, val);

    return val;
}

int snd_platform_write(struct snd_platform *platform, unsigned int reg, unsigned int val)
{
    int ret = 0;
//        uint32_t __cpsr;
        /*__cpsr = hal_spin_lock_irqsave();*/

    ret = snd_writel(val, platform->mem_base + reg);

        /*hal_spin_unlock_irqrestore(__cpsr);*/
    snd_io_debug("reg=0x%x, val=0x%x\n", reg, val);

    return ret;
}

int snd_platform_update_bits(struct snd_platform *platform, unsigned int reg,
                unsigned int mask, unsigned int value)
{
    int ret = 0;
    unsigned int old, new;
    bool change;
//        uint32_t __cpsr;
        /*__cpsr = hal_spin_lock_irqsave();*/

    old = snd_readl(platform->mem_base + reg);
    snd_io_debug("old: 0X%x\n", old);
    new = (old & ~mask) | (value & mask);
    snd_io_debug("new: 0X%x\n", new);
    change = old != new;
    if (change)
        ret = snd_writel(new, platform->mem_base + reg);

        /*hal_spin_unlock_irqrestore(__cpsr);*/
    snd_io_debug("reg=0x%x, mask=0x%x, val=0x%x, change=%u\n", reg, mask, value, change);

    return ret;
}
