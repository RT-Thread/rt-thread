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
#ifndef __SOUND_CORE_H
#define __SOUND_CORE_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <hal_sem.h>
#include <hal_mutex.h>
#include <interrupt.h>
#include <hal_cache.h>
#include <sunxi_hal_common.h>
#include "aw_list.h"
#include "pcm_common.h"
#include "hal_atomic.h"
#include "hal_interrupt.h"
//#define SNDRV_DEBUG

#define SND_CORE_VERSION    "V1.4.0"

typedef unsigned int hal_irq_state_t;

#define hal_local_irq_enable()  hal_interrupt_enable()
#define hal_local_irq_disable() hal_interrupt_disable()
#define hal_local_irq_save(flags) \
    do { \
        flags = hal_interrupt_save(); \
    } while (0)
#define hal_local_irq_restore(flags) \
    do { \
        hal_interrupt_restore(flags); \
    } while (0)

typedef void* __iomem;
typedef __iomem dma_addr_t;

struct snd_dai;
struct snd_pcm_substream;
struct snd_pcm_hw_params;
struct snd_pcm_runtime;
struct snd_pcm;

typedef hal_mutex_t snd_mutex_t;
snd_mutex_t snd_mutex_init(void);
int snd_mutex_lock_timeout(snd_mutex_t mutex, long ms);
int snd_mutex_lock(snd_mutex_t mutex);
void snd_mutex_unlock(snd_mutex_t mutex);
void snd_mutex_destroy(snd_mutex_t mutex);

typedef struct {
    hal_sem_t sem;
    int waiting;
} *snd_schd_t;
snd_schd_t snd_schd_init(void);
int snd_schd_timeout(snd_schd_t schd, long ms);
void snd_schd_wakeup(snd_schd_t schd);
void snd_schd_destroy(snd_schd_t schd);

void snd_pcm_stream_lock_irq(struct snd_pcm_substream *substream);
void snd_pcm_stream_unlock_irq(struct snd_pcm_substream *substream);

hal_irq_state_t _snd_pcm_stream_lock_irqsave(struct snd_pcm_substream *substream);
void snd_pcm_stream_unlock_irqrestore(struct snd_pcm_substream *substream,
                    unsigned long flags);

#define snd_pcm_stream_lock_irqsave(substream, flags) \
    do { \
        flags = _snd_pcm_stream_lock_irqsave(substream); \
    } while (0)

#define snd_readb(reg)          (*(volatile uint8_t  *)(reg))
#define snd_readw(reg)          (*(volatile uint16_t *)(reg))
#define snd_readl(reg)          (*(volatile uint32_t *)(reg))
#define snd_writeb(value,reg)   (*(volatile uint8_t  *)(reg) = (value))
#define snd_writew(value,reg)   (*(volatile uint16_t *)(reg) = (value))
#define snd_writel(value,reg)   (*(volatile uint32_t *)(reg) = (value))

#define snd_malloc(size)    calloc(1, size)
#define snd_strdup(ptr)     strdup(ptr)
#define snd_free(ptr)       free((void *)ptr)


#define SNDRV_LOG_COLOR_NONE        "\e[0m"
#define SNDRV_LOG_COLOR_RED     "\e[31m"
#define SNDRV_LOG_COLOR_GREEN   "\e[32m"
#define SNDRV_LOG_COLOR_YELLOW      "\e[33m"
#define SNDRV_LOG_COLOR_BLUE        "\e[34m"

#ifdef SNDRV_DEBUG
#define snd_print(fmt, args...) \
    printf(SNDRV_LOG_COLOR_GREEN "[SND_DEBUG][%s:%d]" fmt \
        SNDRV_LOG_COLOR_NONE, __FUNCTION__, __LINE__, ##args)
#else
#define snd_print(fmt, args...)
#endif

#if 0
#define snd_info(fmt, args...) \
    printf(SNDRV_LOG_COLOR_BLUE "[SND_INFO][%s:%d]" fmt \
        SNDRV_LOG_COLOR_NONE, __FUNCTION__, __LINE__, ##args)
#else
#define snd_info(fmt, args...)
#endif

#define snd_err(fmt, args...) \
    printf(SNDRV_LOG_COLOR_RED "[SND_ERR][%s:%d]" fmt \
        SNDRV_LOG_COLOR_NONE, __FUNCTION__, __LINE__, ##args)
#if 0
#define snd_lock_debug(fmt, args...) \
    printf(SNDRV_LOG_COLOR_RED "[SND_LOCK_DEBUG][%s:%u]" fmt \
        SNDRV_LOG_COLOR_NONE, __FUNCTION__, __LINE__, ##args)
#else
#define snd_lock_debug(fmt, args...)
#endif

typedef int snd_ctl_elem_type_t;
#define SND_CTL_ELEM_TYPE_INTEGER ((snd_ctl_elem_type_t)0)
#define SND_CTL_ELEM_TYPE_ENUMERATED ((snd_ctl_elem_type_t)1)
#define SND_CTL_ELEM_TYPE_LAST SND_CTL_ELEM_TYPE_ENUMERATE

#define SND_CTL_ENUM_AUTO_MASK (0)

#define SND_CTL_KCONTROL(xname, xreg, xshift, xmax) \
{ \
    .type = SND_CTL_ELEM_TYPE_INTEGER, \
    .name   = xname, \
    .reg    = xreg, \
    .shift  = xshift, \
    .max    = xmax, \
    .min    = 0, \
    .get    = NULL, \
    .set    = NULL, \
    .count  = 1, \
}

#define SND_CTL_KCONTROL_EXT(xname, xmax, xmin, xget, xset) \
{ \
    .type = SND_CTL_ELEM_TYPE_INTEGER, \
    .name   = xname, \
    .reg    = 0, \
    .shift  = 0, \
    .max    = xmax, \
    .min    = xmin, \
    .get    = xget, \
    .set    = xset, \
    .count  = 1, \
}

#define SND_CTL_KCONTROL_EXT_REG(xname, xreg, xshift, xmax, xget, xset) \
{ \
    .type = SND_CTL_ELEM_TYPE_INTEGER, \
    .name   = xname, \
    .reg    = xreg, \
    .shift  = xshift, \
    .max    = xmax, \
    .min    = 0, \
    .get    = xget, \
    .set    = xset, \
    .count  = 1, \
}

#define SND_CTL_KCONTROL_VALUE_EXT(xname, xreg, xshift, xmax, xmin, xget, xset) \
{ \
    .type = SND_CTL_ELEM_TYPE_INTEGER, \
    .name   = xname, \
    .reg    = xreg, \
    .shift  = xshift, \
    .max    = xmax, \
    .min    = xmin, \
    .get    = xget, \
    .set    = xset, \
    .count  = 1, \
}

#define SND_CTL_KCONTROL_USER(xname, xmax, xmin, xcur) \
{ \
    .type = SND_CTL_ELEM_TYPE_INTEGER, \
    .name   = xname, \
    .max    = xmax, \
    .min    = xmin, \
    .reg    = xcur, \
    .get    = NULL, \
    .set    = NULL, \
    .count  = 1, \
    .private_data_type = SND_MODULE_USER, \
}

#define SND_CTL_ENUM(xname, xitems, xtexts, xreg, xshift) \
{ \
    .type = SND_CTL_ELEM_TYPE_ENUMERATED, \
    .name = xname,\
    .items = xitems, \
    .texts = xtexts, \
    .reg    = xreg, \
    .shift  = xshift, \
    .mask   = SND_CTL_ENUM_AUTO_MASK, \
    .get = NULL, \
    .set = NULL, \
    .count  = 1, \
}

#define SND_CTL_ENUM_EXT(xname, xitems, xtexts, xmask, xget, xset) \
{ \
    .type = SND_CTL_ELEM_TYPE_ENUMERATED, \
    .name = xname,\
    .items = xitems, \
    .texts = xtexts, \
    .mask   = xmask, \
    .get = xget, \
    .set = xset, \
    .count  = 1, \
}

#define SND_CTL_ENUM_VALUE_EXT(xname, xitems, xtexts, xreg, xshift, xmask, xget, xset) \
{ \
    .type = SND_CTL_ELEM_TYPE_ENUMERATED, \
    .name = xname,\
    .items = xitems, \
    .texts = xtexts, \
    .reg    = xreg, \
    .shift  = xshift, \
    .mask   = xmask, \
    .get = xget, \
    .set = xset, \
    .count  = 1, \
}

enum snd_platform_type {
    SND_PLATFORM_TYPE_CPUDAI = 0,
    SND_PLATFORM_TYPE_INTERNAL_I2S,
    SND_PLATFORM_TYPE_DAUDIO0 = 5,
    SND_PLATFORM_TYPE_DAUDIO1,
    SND_PLATFORM_TYPE_DAUDIO2,
    SND_PLATFORM_TYPE_DAUDIO3,
    SND_PLATFORM_TYPE_DAUDIO_MAX,
    SND_PLATFORM_TYPE_DMIC = 10,
    SND_PLATFORM_TYPE_SPDIF = 12,
    SND_PLATFORM_TYPE_MAX,
};

enum snd_module_type {
    SND_MODULE_UNKNOWN = 0,
    SND_MODULE_CODEC,
    SND_MODULE_PLATFORM,
    SND_MODULE_USER,
};

enum {
    SNDRV_PCM_STREAM_PLAYBACK = 0,
    SNDRV_PCM_STREAM_CAPTURE,
    SNDRV_PCM_STREAM_LAST = SNDRV_PCM_STREAM_CAPTURE,
};

enum snd_device_type {
    SNDRV_DEV_CONTROL,
    SNDRV_DEV_PCM,
    SNDRV_DEV_TIMER,
};

struct sunxi_dma_params {
    char *name;
    dma_addr_t dma_addr;
    uint32_t src_maxburst;
    uint32_t dst_maxburst;
    uint8_t dma_drq_type_num;
};

struct snd_dma_buffer {
    dma_addr_t addr;
    size_t bytes;
};

struct snd_pcm_ops {
    int (*open)(struct snd_pcm_substream *substream);
    int (*close)(struct snd_pcm_substream *substream);
    int (*ioctl)(struct snd_pcm_substream * substream,
             unsigned int cmd, void *arg);
    int (*hw_params)(struct snd_pcm_substream *substream,
            struct snd_pcm_hw_params *params);
    int (*hw_free)(struct snd_pcm_substream *substream);
    int (*prepare)(struct snd_pcm_substream *substream);
    int (*trigger)(struct snd_pcm_substream *substream, int cmd);
    snd_pcm_uframes_t (*pointer)(struct snd_pcm_substream *substream);
    int (*copy)(struct snd_pcm_substream *substream, int channel,
            snd_pcm_uframes_t pos,
            void *buf, snd_pcm_uframes_t count);
};

struct snd_dai_ops {
    int (*set_sysclk)(struct snd_dai *dai,
            int clk_id, unsigned int freq, int dir);
    int (*set_clkdiv)(struct snd_dai *dai, int div_id, int div);
    int (*set_pll)(struct snd_dai *dai, int pll_id, int source,
            unsigned int freq_in, unsigned int freq_out);
    int (*set_fmt)(struct snd_dai *dai, unsigned int fmt);
    int (*startup)(struct snd_pcm_substream *,
            struct snd_dai *);
    void (*shutdown)(struct snd_pcm_substream *,
            struct snd_dai *);
    int (*hw_params)(struct snd_pcm_substream *,
            struct snd_pcm_hw_params *, struct snd_dai *);
    int (*hw_free)(struct snd_pcm_substream *,
            struct snd_dai *);
    int (*prepare)(struct snd_pcm_substream *,
            struct snd_dai *);
    int (*trigger)(struct snd_pcm_substream *, int,
            struct snd_dai *);
    int (*dapm_control)(struct snd_pcm_substream *,
            struct snd_dai *, int onoff);
};

struct snd_pcm_hardware {
    uint32_t info;
    uint32_t formats;
    uint32_t rates;
    uint32_t rate_min;
    uint32_t rate_max;
    uint32_t channels_min;
    uint32_t channels_max;
    uint32_t buffer_bytes_max;
    uint32_t period_bytes_min;
    uint32_t period_bytes_max;
    uint32_t periods_min;
    uint32_t periods_max;
};

struct snd_pcm_hw_constrains {
    union snd_interval intervals[SND_PCM_HW_PARAM_LAST_INTERVAL - SND_PCM_HW_PARAM_FIRST_INTERVAL + 1];
    unsigned int rules_num;
    unsigned int rules_all;
    struct snd_pcm_hw_rule *rules;
};

static inline snd_interval_t *constrs_interval(struct snd_pcm_hw_constrains *constrs,
        snd_pcm_hw_param_t var)
{
    return &constrs->intervals[var - SND_PCM_HW_PARAM_FIRST_INTERVAL];
}

struct snd_pcm_stream {
    const char *stream_name;
    uint64_t formats;
    uint32_t rates;
    uint32_t rate_min;
    uint32_t rate_max;
    uint32_t channels_min;
    uint32_t channels_max;
};

struct snd_dai {
    const char *name;
    uint32_t id;
    struct snd_pcm_stream playback;
    struct snd_pcm_stream capture;
    const struct snd_dai_ops *ops;
    void *playback_dma_data;
    void *capture_dma_data;
    int (*probe)(struct snd_dai *dai);
    int (*remove)(struct snd_dai *dai);
    void *component;
};

typedef struct snd_codec {
    const char *name;
    struct snd_dai *codec_dai;
    uint32_t codec_dai_num;
    int (*probe)(struct snd_codec *);
    int (*remove)(struct snd_codec *);
    void *private_data;
    void *codec_base_addr;
    bool playback_only;
    bool capture_only;
    struct snd_pcm_hardware *hw;
    unsigned int (*read)(struct snd_codec *, unsigned int);
    unsigned int (*write)(struct snd_codec *, unsigned int, unsigned int);
    struct snd_kcontrol *controls;
    unsigned int num_controls;
} snd_codec_t;

struct snd_platform {
    char *name;
    int type;
    int (*probe)(struct snd_platform *);
    int (*remove)(struct snd_platform *);
    int (*pcm_new)(struct snd_pcm *);
    void (*pcm_free)(struct snd_pcm *);
    const struct snd_pcm_ops *ops;
    struct snd_dai *cpu_dai;
    void *private_data;
    void *mem_base;
    struct snd_kcontrol *controls;
    unsigned int num_controls;
    struct snd_pcm_hardware *pcm_hw;
};


struct snd_pcm_runtime {
    snd_pcm_uframes_t hw_ptr_base;
    snd_pcm_access_t access;
    snd_pcm_format_t format;
    unsigned int rate;
    unsigned int channels;
    unsigned int can_paused;
    snd_pcm_uframes_t period_size;
    unsigned int periods;
    snd_pcm_uframes_t buffer_size;
    snd_pcm_uframes_t min_align;        /* Min alignment for the format, frame align */
    unsigned int frame_bits;
    unsigned int sample_bits;
    unsigned int no_period_wakeup: 1;

    dma_addr_t dma_addr;
    size_t dma_bytes;

    struct snd_dma_buffer *dma_buffer_p;

    /* private section */
    void *private_data;

    struct snd_pcm_mmap_status *status;
    struct snd_pcm_mmap_control *control;

    /* HW constrains */
    struct snd_pcm_hardware hw;
    struct snd_pcm_hw_constrains hw_constrains;

    /* Other params */
    snd_pcm_uframes_t start_threshold;
    snd_pcm_uframes_t stop_threshold;
    snd_pcm_uframes_t silence_size;

    snd_pcm_uframes_t silence_start;
    snd_pcm_uframes_t silence_filled;

    snd_pcm_uframes_t boundary;

    /* locking / scheduling */
    snd_pcm_uframes_t twake;
    snd_schd_t tsleep;   /* transfer sleep */
    snd_schd_t sleep;    /* poll sleep (drain...) */
    snd_schd_t dsleep;  /* direct access sleep */

    snd_schd_t dsleep_list[32];

    unsigned int xrun_cnt;

    snd_mutex_t pcm_mutex;
};

struct snd_ctl_info {
    unsigned int id;
    snd_ctl_elem_type_t type;
    const unsigned char *name;
    unsigned long value;
    int min,max;
    int count;
    /* for enum */
    unsigned int items;
    const char * const *texts;

    unsigned long *private_data;
};

typedef int (snd_kcontrol_get_t) (struct snd_kcontrol *, struct snd_ctl_info *);
typedef int (snd_kcontrol_set_t) (struct snd_kcontrol *, unsigned long);

struct snd_kcontrol {
    unsigned int id;
    snd_ctl_elem_type_t type;
    const unsigned char *name;
    int reg;
    unsigned int shift;
    int min,max;
    int mask;
    int count;
    /* for enum */
    unsigned int items;
    const char * const *texts;
    unsigned long value;

    snd_kcontrol_get_t *get;
    snd_kcontrol_set_t *set;
    struct list_head list;
    int dynamic;
    void *private_data;
    int private_data_type;
};

struct snd_ctl {
    struct snd_card *card;
    char id[64];
    struct list_head controls;
    int controls_num;
    snd_mutex_t ctl_mutex;
};

typedef struct snd_pcm_substream {
    struct snd_pcm *pcm;
    char name[48];
    int stream;
    struct snd_pcm_runtime *runtime;
    struct snd_pcm_ops *ops;
    struct snd_dma_buffer dma_buffer;
    hal_spinlock_t lock;
    int ref_count;
    int dapm_state;
    int hw_opened;
} snd_pcm_substream_t;

struct snd_pcm {
    struct snd_card *card;
    char name[48];
    char id[32];
    int num;
    struct snd_pcm_substream *streams[2];
    struct list_head list;
    enum snd_device_type type;
    void (*private_free) (struct snd_pcm *pcm);
    snd_mutex_t open_mutex;
};

struct snd_card {
    char *name;
    int num;
    struct snd_codec *codec;
    struct snd_platform *platform;
    struct list_head devices;
    struct list_head list;
    struct snd_ctl *ctl;
};

void snd_core_version(void);
int snd_card_register(const char *name,
        struct snd_codec *codec,
        int platform_type);
int snd_card_unregister_all(void);

static inline void *snd_soc_dai_get_component(struct snd_dai *dai)
{
    return dai->component;
}

static inline struct snd_dai *snd_soc_get_codec_dai(struct snd_pcm_substream *substream)
{
    struct snd_codec *codec;
    if (!substream || !substream->pcm || !substream->pcm->card)
        return NULL;
    codec = substream->pcm->card->codec;
    if (!codec)
        return NULL;
    return codec->codec_dai;
}

static inline struct snd_dai *snd_soc_get_cpu_dai(struct snd_pcm_substream *substream)
{
    struct snd_platform *platform;
    if (!substream || !substream->pcm || !substream->pcm->card)
        return NULL;
    platform = substream->pcm->card->platform;
    if (!platform)
        return NULL;
    return platform->cpu_dai;
}

static inline void snd_pcm_set_runtime_buffer(struct snd_pcm_substream *substream,
                        struct snd_dma_buffer *bufp)
{
    struct snd_pcm_runtime *runtime = substream->runtime;

    if (bufp) {
        runtime->dma_buffer_p = bufp;
        runtime->dma_addr = bufp->addr;
        runtime->dma_bytes = bufp->bytes;
    } else {
        runtime->dma_buffer_p = NULL;
        runtime->dma_addr = 0;
        runtime->dma_bytes = 0;
    }
}

int snd_ctl_add_elem(struct snd_ctl *ctl, struct snd_ctl_info *info);
int snd_ctl_remove_elem(struct snd_ctl *ctl, struct snd_kcontrol *control);
struct snd_card *snd_card_find_by_name(const char *name);
struct snd_card *snd_card_find_by_num(int num);
int snd_card_get_number(void);
struct snd_pcm *snd_card_find_pcm(struct snd_card *card, int device_num);
void snd_set_runtime_hwparams(struct snd_pcm_substream *substream,
            const struct snd_pcm_hardware *hw);
void snd_kcontrol_to_snd_ctl_info(struct snd_kcontrol *kcontrol,
            struct snd_ctl_info *info, unsigned long value);
int snd_soc_dai_set_fmt(struct snd_dai *dai, unsigned int fmt);
/* card list */
void snd_card_list(void);
int sunxi_soundcard_init(void);

#endif /* __SOUND_CORE_H */
