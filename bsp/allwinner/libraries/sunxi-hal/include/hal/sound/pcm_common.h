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
#ifndef __SOUND_PCM_COMMON_H
#define __SOUND_PCM_COMMON_H

#include <stdint.h>
#include <errno.h>

#ifndef EBADFD
#define EBADFD      77
#endif
#ifndef ESTRPIPE
#define ESTRPIPE    86
#endif

#ifndef LONG_MAX
#define LONG_MAX    ((long)(~0UL>>1))
#endif
#ifndef ULONG_MAX
#define ULONG_MAX   (~0UL)
#endif
#ifndef UINT_MAX
#define UINT_MAX    (~0U)
#endif

#define SND_PCM_APPEND  (1<<8)

typedef unsigned long snd_pcm_uframes_t;
typedef signed long snd_pcm_sframes_t;
typedef union snd_interval snd_interval_t;

#define SNDRV_PCM_INFO_MMAP     0x00000001  /* hardware supports mmap */
#define SNDRV_PCM_INFO_MMAP_VALID   0x00000002  /* period data are valid during transfer */
#define SNDRV_PCM_INFO_DOUBLE       0x00000004  /* Double buffering needed for PCM start/stop */
#define SNDRV_PCM_INFO_BATCH        0x00000010  /* double buffering */
#define SNDRV_PCM_INFO_INTERLEAVED  0x00000100  /* channels are interleaved */
#define SNDRV_PCM_INFO_NONINTERLEAVED   0x00000200  /* channels are not interleaved */
#define SNDRV_PCM_INFO_COMPLEX      0x00000400  /* complex frame organization (mmap only) */
#define SNDRV_PCM_INFO_BLOCK_TRANSFER   0x00010000  /* hardware transfer block of samples */
#define SNDRV_PCM_INFO_OVERRANGE    0x00020000  /* hardware supports ADC (capture) overrange detection */
#define SNDRV_PCM_INFO_RESUME       0x00040000  /* hardware supports stream resume after suspend */
#define SNDRV_PCM_INFO_PAUSE        0x00080000  /* pause ioctl is supported */
#define SNDRV_PCM_INFO_HALF_DUPLEX  0x00100000  /* only half duplex */
#define SNDRV_PCM_INFO_JOINT_DUPLEX 0x00200000  /* playback and capture stream are somewhat correlated */
#define SNDRV_PCM_INFO_SYNC_START   0x00400000  /* pcm support some kind of sync go */
#define SNDRV_PCM_INFO_NO_PERIOD_WAKEUP 0x00800000  /* period wakeup can be disabled */
#define SNDRV_PCM_INFO_HAS_WALL_CLOCK   0x01000000      /* (Deprecated)has audio wall clock for audio/system time sync */
#define SNDRV_PCM_INFO_HAS_LINK_ATIME              0x01000000  /* report hardware link audio time, reset on startup */
#define SNDRV_PCM_INFO_HAS_LINK_ABSOLUTE_ATIME     0x02000000  /* report absolute hardware link audio time, not reset on startup */
#define SNDRV_PCM_INFO_HAS_LINK_ESTIMATED_ATIME    0x04000000  /* report estimated link audio time */
#define SNDRV_PCM_INFO_HAS_LINK_SYNCHRONIZED_ATIME 0x08000000  /* report synchronized audio/system time */
#define SNDRV_PCM_INFO_DRAIN_TRIGGER    0x40000000      /* internal kernel flag - trigger in drain */
#define SNDRV_PCM_INFO_FIFO_IN_FRAMES   0x80000000  /* internal kernel flag - FIFO size is in frames */

/** PCM access type */
typedef enum _snd_pcm_access {
        /** mmap access with simple interleaved channels */
        SND_PCM_ACCESS_MMAP_INTERLEAVED = 0,
        /** mmap access with simple non interleaved channels */
        SND_PCM_ACCESS_MMAP_NONINTERLEAVED,
        /** mmap access with complex placement */
        SND_PCM_ACCESS_MMAP_COMPLEX,
        /** snd_pcm_readi/snd_pcm_writei access */
        SND_PCM_ACCESS_RW_INTERLEAVED,
        /** snd_pcm_readn/snd_pcm_writen access */
        SND_PCM_ACCESS_RW_NONINTERLEAVED,
        SND_PCM_ACCESS_LAST = SND_PCM_ACCESS_RW_NONINTERLEAVED
} snd_pcm_access_t;

/** PCM sample format */
typedef enum _snd_pcm_format {
        /** Unknown */
        SND_PCM_FORMAT_UNKNOWN = -1,
        /** Signed 8 bit */
        SND_PCM_FORMAT_S8 = 0,
        /** Unsigned 8 bit */
        SND_PCM_FORMAT_U8,
        /** Signed 16 bit Little Endian */
        SND_PCM_FORMAT_S16_LE,
        /** Signed 16 bit Big Endian */
        SND_PCM_FORMAT_S16_BE,
        /** Unsigned 16 bit Little Endian */
        SND_PCM_FORMAT_U16_LE,
        /** Unsigned 16 bit Big Endian */
        SND_PCM_FORMAT_U16_BE,
        /** Signed 24 bit Little Endian using low three bytes in 32-bit word */
        SND_PCM_FORMAT_S24_LE,
        /** Signed 24 bit Big Endian using low three bytes in 32-bit word */
        SND_PCM_FORMAT_S24_BE,
        /** Unsigned 24 bit Little Endian using low three bytes in 32-bit word */
        SND_PCM_FORMAT_U24_LE,
        /** Unsigned 24 bit Big Endian using low three bytes in 32-bit word */
        SND_PCM_FORMAT_U24_BE,
        /** Signed 32 bit Little Endian */
        SND_PCM_FORMAT_S32_LE,
        /** Signed 32 bit Big Endian */
        SND_PCM_FORMAT_S32_BE,
        /** Unsigned 32 bit Little Endian */
        SND_PCM_FORMAT_U32_LE,
        /** Unsigned 32 bit Big Endian */
        SND_PCM_FORMAT_U32_BE,

    /* only support little endian */
    /** Signed 16 bit CPU endian */
        SND_PCM_FORMAT_S16 = SND_PCM_FORMAT_S16_LE,
        /** Unsigned 16 bit CPU endian */
        SND_PCM_FORMAT_U16 = SND_PCM_FORMAT_U16_LE,
        /** Signed 24 bit CPU endian */
        SND_PCM_FORMAT_S24 = SND_PCM_FORMAT_S24_LE,
        /** Unsigned 24 bit CPU endian */
        SND_PCM_FORMAT_U24 = SND_PCM_FORMAT_U24_LE,
        /** Signed 32 bit CPU endian */
        SND_PCM_FORMAT_S32 = SND_PCM_FORMAT_S32_LE,
        /** Unsigned 32 bit CPU endian */
        SND_PCM_FORMAT_U32 = SND_PCM_FORMAT_U32_LE,

    SND_PCM_FORMAT_LAST = SND_PCM_FORMAT_U32_BE,
} snd_pcm_format_t;

/** PCM state */
typedef enum _ksnd_pcm_state {
        /** Open */
        SNDRV_PCM_STATE_OPEN = 0,
        /** Setup installed */
        SNDRV_PCM_STATE_SETUP,
        /** Ready to start */
        SNDRV_PCM_STATE_PREPARED,
        /** Running */
        SNDRV_PCM_STATE_RUNNING,
        /** Stopped: underrun (playback) or overrun (capture) detected */
        SNDRV_PCM_STATE_XRUN,
        /** Draining: running (playback) or stopped (capture) */
        SNDRV_PCM_STATE_DRAINING,
        /** Paused */
        SNDRV_PCM_STATE_PAUSED,
        /** Hardware is suspended */
        SNDRV_PCM_STATE_SUSPENDED,
        /** Hardware is disconnected */
        SNDRV_PCM_STATE_DISCONNECTED,
        SNDRV_PCM_STATE_LAST = SNDRV_PCM_STATE_DISCONNECTED
} ksnd_pcm_state_t;


typedef int snd_pcm_hw_param_t;
#define SND_PCM_HW_PARAM_ACCESS     0
#define SND_PCM_HW_PARAM_FORMAT     1
#define SND_PCM_HW_PARAM_FIRST_MASK SND_PCM_HW_PARAM_ACCESS
#define SND_PCM_HW_PARAM_LAST_MASK  SND_PCM_HW_PARAM_FORMAT
#define SND_PCM_HW_PARAM_SAMPLE_BITS    2
#define SND_PCM_HW_PARAM_FRAME_BITS 3
#define SND_PCM_HW_PARAM_CHANNELS   4
#define SND_PCM_HW_PARAM_RATE       5
#define SND_PCM_HW_PARAM_PERIOD_TIME    6
#define SND_PCM_HW_PARAM_PERIOD_SIZE    7
#define SND_PCM_HW_PARAM_PERIOD_BYTES   8
#define SND_PCM_HW_PARAM_PERIODS    9
#define SND_PCM_HW_PARAM_BUFFER_TIME    10
#define SND_PCM_HW_PARAM_BUFFER_SIZE    11
#define SND_PCM_HW_PARAM_BUFFER_BYTES   12
#define SND_PCM_HW_PARAM_FIRST_RANGE SND_PCM_HW_PARAM_SAMPLE_BITS
#define SND_PCM_HW_PARAM_LAST_RANGE SND_PCM_HW_PARAM_BUFFER_BYTES
#define SND_PCM_HW_PARAM_FIRST_INTERVAL SND_PCM_HW_PARAM_ACCESS
#define SND_PCM_HW_PARAM_LAST_INTERVAL SND_PCM_HW_PARAM_BUFFER_BYTES

static inline int hw_is_mask(int var)
{
    return var >= SND_PCM_HW_PARAM_FIRST_MASK &&
        var <= SND_PCM_HW_PARAM_LAST_MASK;
}

static inline int hw_is_range(int var)
{
    return var >= SND_PCM_HW_PARAM_FIRST_RANGE &&
        var <= SND_PCM_HW_PARAM_LAST_RANGE;
}

union snd_interval {
    struct {
        uint32_t min;
        uint32_t max;
        int openmin;    /* whether the interval is left-open */
        int openmax;    /* whether the interval is right-open */
        int integer;    /* whether the value is integer or not */
        int empty;
    } range;
    uint32_t mask;
};

typedef struct snd_pcm_hw_params {
    union snd_interval intervals[SND_PCM_HW_PARAM_LAST_INTERVAL -
                SND_PCM_HW_PARAM_FIRST_INTERVAL + 1];
    unsigned int can_paused;

    uint32_t rmask;     /* W: requested masks */
    uint32_t cmask;     /* R: changed masks */
} snd_pcm_hw_params_t;

typedef struct snd_pcm_sw_params {
    snd_pcm_uframes_t avail_min;            /* min avail frames for wakeup */
    snd_pcm_uframes_t start_threshold;      /* min hw_avail frames for automatic start */
    snd_pcm_uframes_t stop_threshold;       /* min avail frames for automatic stop */
    snd_pcm_uframes_t silence_size;         /* silence block size */
    snd_pcm_uframes_t boundary;             /* pointers wrap point */
} snd_pcm_sw_params_t;


typedef long ksnd_pcm_sframes_t;
typedef unsigned long ksnd_pcm_uframes_t;

struct snd_pcm_mmap_status {
    ksnd_pcm_state_t state;
    ksnd_pcm_uframes_t hw_ptr;
};

struct snd_pcm_mmap_control {
    ksnd_pcm_uframes_t appl_ptr;
    ksnd_pcm_uframes_t avail_min;
};

#define SNDRV_PCM_SYNC_PTR_HWSYNC       (1<<0)  /* execute hwsync */
#define SNDRV_PCM_SYNC_PTR_APPL         (1<<1)  /* get appl_ptr from driver (r/w op) */
#define SNDRV_PCM_SYNC_PTR_AVAIL_MIN    (1<<2)  /* get avail_min from driver */

typedef struct _snd_pcm_channel_info {
    unsigned int channel;
    void *addr;         /* base address of channel samples */
    unsigned int first;     /* offset to first sample in bits */
    unsigned int step;      /* samples distance in bits */
    enum { SND_PCM_AREA_MMAP, SND_PCM_AREA_LOCAL } type;
} snd_pcm_channel_info_t;


static inline unsigned int div32(unsigned int a, unsigned int b,
                 unsigned int *r)
{
    if (b == 0) {
        *r = 0;
        return UINT_MAX;
    }
    *r = a % b;
    return a / b;
}

static inline uint64_t div_u64_rem(uint64_t dividend, uint32_t divisor, uint32_t *remainder)
{
    *remainder = dividend % divisor;
    return dividend / divisor;
}

static inline unsigned int div_down(unsigned int a, unsigned int b)
{
    if (b == 0)
        return UINT_MAX;
    return a / b;
}

static inline unsigned int div_up(unsigned int a, unsigned int b)
{
    unsigned int r;
    unsigned int q;
    if (b == 0)
        return UINT_MAX;
    q = div32(a, b, &r);
    if (r)
        ++q;
    return q;
}

static inline unsigned int mul(unsigned int a, unsigned int b)
{
    if (a == 0)
        return 0;
    if (div_down(UINT_MAX, a) < b)
        return UINT_MAX;
    return a * b;
}

static inline unsigned int add(unsigned int a, unsigned int b)
{
    if (a >= UINT_MAX - b)
        return UINT_MAX;
    return a + b;
}

static inline unsigned int sub(unsigned int a, unsigned int b)
{
    if (a > b)
        return a - b;
    return 0;
}

static inline unsigned int muldiv32(unsigned int a, unsigned int b,
                    unsigned int c, unsigned int *r)
{
    uint64_t n = (uint64_t)a * (uint64_t)b;
    uint32_t rem;
    if (c == 0) {
        *r = 0;
        return UINT_MAX;
    }
    n = div_u64_rem(n, c, &rem);
    if (n >= UINT_MAX) {
        *r = 0;
        return UINT_MAX;
    }
    *r = rem;
    return n;
}

static inline int __pcm_ffs(uint32_t value)
{
    uint32_t offset;

    for (offset = 0; offset < sizeof(value)*8; offset++) {
        if (value & (1<<offset))
            return offset;
    }
    return -1;
}

static inline int __ffs(uint32_t value)
{
    uint32_t offset;

    for (offset = 0; offset < sizeof(value)*8; offset++) {
        if (value & (1<<offset))
            return offset;
    }
    return -1;
}

static inline int __fls(uint32_t value)
{
    uint32_t offset;

    for (offset = sizeof(value)*8; offset > 0; offset--) {
        if (value & (1<<(offset - 1)))
            return offset;
    }
    return -1;
}

static inline snd_pcm_access_t params_access(const struct snd_pcm_hw_params *p)
{
    const union snd_interval *interval = NULL;
    interval = &p->intervals[SND_PCM_HW_PARAM_ACCESS -
                SND_PCM_HW_PARAM_FIRST_INTERVAL];

    if (interval->mask != 0)
        return (snd_pcm_access_t)__ffs(interval->mask);
    return (snd_pcm_access_t)-1;
}

static inline snd_pcm_format_t params_format(const struct snd_pcm_hw_params *p)
{
    const union snd_interval *interval = NULL;
    interval = &p->intervals[SND_PCM_HW_PARAM_FORMAT -
                SND_PCM_HW_PARAM_FIRST_INTERVAL];

    if (interval->mask != 0)
        return (snd_pcm_format_t)__ffs(interval->mask);
    return SND_PCM_FORMAT_UNKNOWN;
}

static inline snd_interval_t *hw_param_interval(struct snd_pcm_hw_params *params,
                        snd_pcm_hw_param_t var)
{
    return &params->intervals[var];
}

static inline const union snd_interval *hw_param_interval_c(const struct snd_pcm_hw_params *params,
                            int var)
{
    return &params->intervals[var - SND_PCM_HW_PARAM_FIRST_INTERVAL];
}

static inline unsigned int params_channels(const struct snd_pcm_hw_params *p)
{
    return hw_param_interval_c(p, SND_PCM_HW_PARAM_CHANNELS)->range.min;
}

static inline unsigned int params_rate(const struct snd_pcm_hw_params *p)
{
    return hw_param_interval_c(p, SND_PCM_HW_PARAM_RATE)->range.min;
}

static inline unsigned int params_period_size(const struct snd_pcm_hw_params *p)
{
    return hw_param_interval_c(p, SND_PCM_HW_PARAM_PERIOD_SIZE)->range.min;
}

static inline unsigned int params_period_time(const struct snd_pcm_hw_params *p)
{
    return hw_param_interval_c(p, SND_PCM_HW_PARAM_PERIOD_TIME)->range.min;
}

static inline unsigned int params_periods(const struct snd_pcm_hw_params *p)
{
    return hw_param_interval_c(p, SND_PCM_HW_PARAM_PERIODS)->range.min;
}

static inline unsigned int params_buffer_size(const struct snd_pcm_hw_params *p)
{
    return hw_param_interval_c(p, SND_PCM_HW_PARAM_BUFFER_SIZE)->range.min;
}

static inline unsigned int params_buffer_time(const struct snd_pcm_hw_params *p)
{
    return hw_param_interval_c(p, SND_PCM_HW_PARAM_BUFFER_TIME)->range.min;
}


int snd_pcm_format_physical_width(snd_pcm_format_t format);


#define SND_MASK_BITS 32

static inline void snd_mask_none(snd_interval_t *interval)
{
    interval->mask = 0U;
}

static inline void snd_mask_any(snd_interval_t *interval)
{
    interval->mask = ~0U;
}

static inline int snd_mask_empty(const snd_interval_t *interval)
{
    return !interval->mask;
}

static inline int snd_mask_full(const snd_interval_t *interval)
{
    return interval->mask == 0xffffffff;
}

static inline unsigned int snd_mask_min(const snd_interval_t *interval)
{
    unsigned int i;
    for (i = 0; i < sizeof(interval->mask) * 8; i++) {
        if (interval->mask & (1 << i))
            return i;
    }
    return 0;
}

static inline unsigned int snd_mask_max(const snd_interval_t *interval)
{
    unsigned int i;
    for (i = sizeof(interval->mask) * 8; i > 0; i--) {
        if (interval->mask & (1 << (i - 1)))
            return i - 1;
    }
    return 0;
}

static inline void snd_mask_set(snd_interval_t *interval, unsigned int val)
{
    interval->mask |= (1 << val);
}

static inline void snd_mask_reset(snd_interval_t *interval, unsigned int val)
{
    interval->mask &= ~(1 << val);
}

static inline void snd_mask_set_range(snd_interval_t *interval,
        unsigned int from, unsigned int to)
{
    unsigned int i;
    for (i = from; i <= to; i++)
        interval->mask |= (1 << i);
}

static inline void snd_mask_reset_range(snd_interval_t *interval,
        unsigned int from, unsigned int to)
{
    unsigned int i;
    for (i = from; i <= to; i++)
        interval->mask &= ~(1 << i);
}

static inline void snd_mask_leave(snd_interval_t *interval, unsigned int val)
{
    snd_mask_none(interval);
    interval->mask |= (1 << val);
}

static inline void snd_mask_intersect(snd_interval_t *interval, const snd_interval_t *v)
{
    interval->mask &= v->mask;
}

static inline int snd_mask_eq(snd_interval_t *interval, const snd_interval_t *v)
{
    return interval->mask == v->mask;
}

static inline void snd_mask_copy(snd_interval_t *interval, const snd_interval_t *v)
{
    interval->mask = v->mask;
}

static inline int snd_mask_test(const snd_interval_t *interval, unsigned int val)
{
    return interval->mask & (1 << val);
}

static inline int snd_mask_single(const snd_interval_t *interval)
{
    unsigned int bits = sizeof(interval->mask) * 8;
    unsigned int i;
    int c = 0;
    for (i = 0; i < bits; ++i) {
        if (!(interval->mask & (1 << i)))
            continue;
        if (c)
            return 0;
        c++;
    }
    return 1;
}

static inline int snd_mask_refine(snd_interval_t *interval, const snd_interval_t *v)
{
    snd_interval_t old;
    snd_mask_copy(&old, interval);
    snd_mask_intersect(interval, v);
    if (snd_mask_empty(interval))
        return -EINVAL;
    return !snd_mask_eq(interval, &old);
}

static inline int snd_mask_refine_first(snd_interval_t *interval)
{
    if (snd_mask_single(interval))
        return 0;
    snd_mask_leave(interval, snd_mask_min(interval));
    return 1;
}

static inline int snd_mask_refine_last(snd_interval_t *interval)
{
    if (snd_mask_single(interval))
        return 0;
    snd_mask_leave(interval, snd_mask_max(interval));
    return 1;
}

static inline int snd_mask_refine_min(snd_interval_t *interval, unsigned int val)
{
    if (snd_mask_min(interval) >= val)
        return 0;
    snd_mask_reset_range(interval, 0, val - 1);
    if (snd_mask_empty(interval))
        return -EINVAL;
    return 1;
}

static inline int snd_mask_refine_max(snd_interval_t *interval, unsigned int val)
{
    if (snd_mask_max(interval) <= val)
        return 0;
    snd_mask_reset_range(interval, val + 1, SND_MASK_BITS);
    if (snd_mask_empty(interval))
        return -EINVAL;
    return 1;
}

static inline int snd_mask_refine_set(snd_interval_t *interval, unsigned int val)
{
    int changed;
    changed = !snd_mask_single(interval);
    snd_mask_leave(interval, val);
    if (snd_mask_empty(interval))
        return -EINVAL;
    return changed;
}

static inline int snd_mask_value(const snd_interval_t *interval)
{
    return snd_mask_min(interval);
}

static inline int snd_mask_always_eq(const snd_interval_t *m1, const snd_interval_t *m2)
{
    return snd_mask_single(m1) && snd_mask_single(m2) &&
        snd_mask_value(m1) == snd_mask_value(m2);
}

static inline int snd_mask_never_eq(const snd_interval_t *m1, const snd_interval_t *m2)
{
    if (m1->mask & m2->mask)
        return 0;
    return 1;
}

static inline void snd_range_any(snd_interval_t *i)
{
    i->range.min = 0;
    i->range.openmin = 0;
    i->range.max = UINT_MAX;
    i->range.openmax= 0;
    i->range.integer = 0;
    i->range.empty = 0;
}

static inline void snd_range_none(snd_interval_t *i)
{
    i->range.empty = 1;
}

static inline int snd_range_checkempty(snd_interval_t *i)
{
    return (i->range.min > i->range.max ||
        (i->range.min == i->range.max && (i->range.openmin || i->range.openmax)));
}

static inline int snd_range_empty(const snd_interval_t *i)
{
    return i->range.empty;
}

static inline int snd_range_single(const snd_interval_t *i)
{
    return (i->range.min == i->range.max ||
        (i->range.min + 1 == i->range.max && i->range.openmax));
}

static inline int snd_range_value(const snd_interval_t *i)
{
    return i->range.min;
}

static inline void snd_range_set_value(snd_interval_t *i, unsigned int val)
{
    i->range.openmax = i->range.openmin = 0;
    i->range.min = i->range.max = val;
    i->range.integer = 0;
    i->range.empty = 0;
}

static inline int snd_range_min(const snd_interval_t *i)
{
    return i->range.min;
}

static inline int snd_range_max(const snd_interval_t *i)
{
    unsigned int v;
    v = i->range.max;
    if (i->range.openmax)
        v--;
    return v;
}

static inline void snd_range_set_minmax(snd_interval_t *i, unsigned int min, unsigned int max)
{
    i->range.openmax = i->range.openmin = 0;
    i->range.min = min;
    i->range.max = max;
    i->range.integer = 0;
    i->range.empty = 0;
}

static inline int snd_range_test(const snd_interval_t *i, unsigned int val)
{
    return !((i->range.min > val || (i->range.min == val && i->range.openmin) ||
        i->range.max < val || (i->range.max == val && i->range.openmax)));
}

static inline void snd_range_copy(snd_interval_t *d, const snd_interval_t *s)
{
    d->range = s->range;
}

static inline int snd_range_setinteger(snd_interval_t *i)
{
    if (i->range.integer)
        return 0;
    if (i->range.openmin && i->range.openmax && i->range.min == i->range.max)
        return -EINVAL;
    i->range.integer = 1;
    return 1;
}

static inline void snd_range_floor(snd_interval_t *i)
{
    if (i->range.integer || snd_range_empty(i))
        return;
    i->range.openmin = 0;
    if (i->range.openmax) {
        i->range.max--;
        i->range.openmax = 0;
    }
    i->range.integer = 1;
}

static inline void snd_range_unfloor(snd_interval_t *i)
{
    if (snd_range_empty(i))
        return;
    if (i->range.max == UINT_MAX)
        return;
    if (i->range.openmax)
        return;
    i->range.max++;
    i->range.openmax = 1;
    i->range.integer = 0;
}

static inline int snd_range_eq(const snd_interval_t *i1, const snd_interval_t *i2)
{
    if (i1->range.empty)
        return i2->range.empty;
    if (i2->range.empty)
        return i1->range.empty;
    return i1->range.min == i2->range.min &&
        i1->range.openmin == i2->range.openmin &&
        i1->range.max == i2->range.max &&
        i1->range.openmax == i2->range.openmax;
}

static inline int snd_range_always_eq(const snd_interval_t *i1, const snd_interval_t *i2)
{
    return snd_range_single(i1) && snd_range_single(i2) &&
        snd_range_value(i1) == snd_range_value(i2);
}

static inline int snd_range_never_eq(const snd_interval_t *i1, const snd_interval_t *i2)
{

    return (i1->range.max < i2->range.min ||
        (i1->range.max == i2->range.min &&
         (i1->range.openmax || i1->range.openmin)) ||
        i1->range.min > i2->range.max ||
        (i1->range.min == i2->range.max &&
         (i1->range.openmin || i2->range.openmax)));
}

int snd_range_refine(snd_interval_t *i, const snd_interval_t *v);
int snd_range_refine_first(snd_interval_t *i);
int snd_range_refine_last(snd_interval_t *i);
int snd_range_refine_min(snd_interval_t *i, unsigned int min, int openmin);
int snd_range_refine_max(snd_interval_t *i, unsigned int max, int openmax);
int snd_range_refine_set(snd_interval_t *i, unsigned int val);
void snd_range_add(const snd_interval_t *a, const snd_interval_t *b, snd_interval_t *c);
void snd_range_sub(const snd_interval_t *a, const snd_interval_t *b, snd_interval_t *c);
void snd_range_mul(const snd_interval_t *a, const snd_interval_t *b, snd_interval_t *c);
void snd_range_div(const snd_interval_t *a, const snd_interval_t *b, snd_interval_t *c);
void snd_range_muldiv(const snd_interval_t *a, const snd_interval_t *b,
        const snd_interval_t *c, snd_interval_t *d);
void snd_range_muldivk(const snd_interval_t *a, const snd_interval_t *b,
        unsigned int k, snd_interval_t *c);
void snd_range_mulkdiv(const snd_interval_t *a, unsigned int k,
        const snd_interval_t *b, snd_interval_t *c);
int snd_range_list(snd_interval_t *i, unsigned int count,
        const unsigned int *list, unsigned int mask);

const char *snd_pcm_hw_param_name(snd_pcm_hw_param_t param);

struct snd_pcm_hw_rule;
typedef int (*snd_pcm_hw_rule_func_t)(struct snd_pcm_hw_params *params,
                      struct snd_pcm_hw_rule *rule);

struct snd_pcm_hw_rule {
    unsigned int cond;
    int var;
    int deps[4];
    snd_pcm_hw_rule_func_t func;
    void *private_data;
};

int snd_pcm_hw_rule_mul(struct snd_pcm_hw_params *params, struct snd_pcm_hw_rule *rule);
int snd_pcm_hw_rule_div(struct snd_pcm_hw_params *params, struct snd_pcm_hw_rule *rule);
int snd_pcm_hw_rule_muldivk(struct snd_pcm_hw_params *params, struct snd_pcm_hw_rule *rule);
int snd_pcm_hw_rule_mulkdiv(struct snd_pcm_hw_params *params, struct snd_pcm_hw_rule *rule);
int snd_pcm_hw_rule_format(struct snd_pcm_hw_params *params, struct snd_pcm_hw_rule *rule);
int snd_pcm_hw_rule_sample_bits(struct snd_pcm_hw_params *params, struct snd_pcm_hw_rule *rule);
int snd_pcm_hw_rule_rate(struct snd_pcm_hw_params *params, struct snd_pcm_hw_rule *rule);
int snd_pcm_hw_rule_buffer_bytes_max(struct snd_pcm_hw_params *params, struct snd_pcm_hw_rule *rule);

#endif /* __SOUND_PCM_COMMON_H */
