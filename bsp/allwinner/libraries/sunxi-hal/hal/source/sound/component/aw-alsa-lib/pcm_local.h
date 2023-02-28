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
#ifndef __AW_ALSA_PCM_LOCAL_H
#define __AW_ALSA_PCM_LOCAL_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <assert.h>
#include <pthread.h>
#include <errno.h>
#include <limits.h>
#include <aw-alsa-lib/pcm.h>
#include <aw-alsa-lib/pcm_config.h>

#define ATTRIBUTE_UNUSED    __attribute__ ((__unused__))

#define SND_PCM_VERSION     "V1.7.3"

#define SND_PCM_RATE_FIX_PERIOD_SIZE

#if 0
#define REFINE_DEBUG
#endif

typedef enum _snd_set_mode {
    SND_CHANGE,
    SND_TRY,
    SND_TEST,
} snd_set_mode_t;

typedef struct _snd_pcm_rbptr {
    snd_pcm_t *master;
    volatile snd_pcm_uframes_t *ptr;
    //int fd;
    off_t offset;
    int link_dst_count;
    snd_pcm_t **link_dst;
    //void *private_data;
    //void (*changed)(snd_pcm_t *pcm, snd_pcm_t *src);
} snd_pcm_rbptr_t;

typedef struct {
    int (*close)(snd_pcm_t *pcm);
    //int (*nonblock)(snd_pcm_t *pcm, int nonblock);
    //int (*async)(snd_pcm_t *pcm, int sig, pid_t pid);
    //int (*info)(snd_pcm_t *pcm, snd_pcm_info_t *info);
    int (*hw_refine)(snd_pcm_t *pcm, snd_pcm_hw_params_t *params);
    int (*hw_params)(snd_pcm_t *pcm, snd_pcm_hw_params_t *params);
    int (*hw_free)(snd_pcm_t *pcm);
    int (*sw_params)(snd_pcm_t *pcm, snd_pcm_sw_params_t *params); /* always locked */
    int (*channel_info)(snd_pcm_t *pcm, snd_pcm_channel_info_t *info);
    void (*dump)(snd_pcm_t *pcm);
    int (*mmap)(snd_pcm_t *pcm);
    int (*munmap)(snd_pcm_t *pcm);
    snd_pcm_chmap_query_t **(*query_chmaps)(snd_pcm_t *pcm);
    snd_pcm_chmap_t *(*get_chmap)(snd_pcm_t *pcm);
    int (*set_chmap)(snd_pcm_t *pcm, const snd_pcm_chmap_t *map);
} snd_pcm_ops_t;

typedef struct {
    //int (*status)(snd_pcm_t *pcm, snd_pcm_status_t *status);
    int (*prepare)(snd_pcm_t *pcm);
    int (*reset)(snd_pcm_t *pcm);
    int (*start)(snd_pcm_t *pcm);
    int (*drop)(snd_pcm_t *pcm);
    int (*drain)(snd_pcm_t *pcm);
    int (*pause)(snd_pcm_t *pcm, int enable);
    snd_pcm_state_t (*state)(snd_pcm_t *pcm);
    int (*hwsync)(snd_pcm_t *pcm);
    int (*delay)(snd_pcm_t *pcm, snd_pcm_sframes_t *delayp);
    int (*resume)(snd_pcm_t *pcm);
    int (*link)(snd_pcm_t *pcm1, snd_pcm_t *pcm2);
    //int (*link_slaves)(snd_pcm_t *pcm, snd_pcm_t *master);
    int (*unlink)(snd_pcm_t *pcm);
    //snd_pcm_sframes_t (*rewindable)(snd_pcm_t *pcm);
    snd_pcm_sframes_t (*rewind)(snd_pcm_t *pcm, snd_pcm_uframes_t frames);
    //snd_pcm_sframes_t (*forwardable)(snd_pcm_t *pcm);
    //snd_pcm_sframes_t (*forward)(snd_pcm_t *pcm, snd_pcm_uframes_t frames);
    snd_pcm_sframes_t (*writei)(snd_pcm_t *pcm, const void *buffer, snd_pcm_uframes_t size);
    //snd_pcm_sframes_t (*writen)(snd_pcm_t *pcm, void **bufs, snd_pcm_uframes_t size);
    snd_pcm_sframes_t (*readi)(snd_pcm_t *pcm, void *buffer, snd_pcm_uframes_t size);
    //snd_pcm_sframes_t (*readn)(snd_pcm_t *pcm, void **bufs, snd_pcm_uframes_t size);
    snd_pcm_sframes_t (*avail_update)(snd_pcm_t *pcm);
    snd_pcm_sframes_t (*mmap_commit)(snd_pcm_t *pcm, snd_pcm_uframes_t offset, snd_pcm_uframes_t size);
    //int (*htimestamp)(snd_pcm_t *pcm, snd_pcm_uframes_t *avail, snd_htimestamp_t *tstamp);
    //int (*poll_descriptors_count)(snd_pcm_t *pcm);
    //int (*poll_descriptors)(snd_pcm_t *pcm, struct pollfd *pfds, unsigned int space);
    //int (*poll_revents)(snd_pcm_t *pcm, struct pollfd *pfds, unsigned int nfds, unsigned short *revents);
    int (*may_wait_for_avail_min)(snd_pcm_t *pcm, snd_pcm_uframes_t avail);
    int (*wait)(snd_pcm_t *pcm, int timeout);
    void (*cache_update)(snd_pcm_t *pcm, snd_pcm_uframes_t offset, snd_pcm_uframes_t size);
} snd_pcm_fast_ops_t;

struct _snd_pcm {
    char *name;
    snd_pcm_type_t type;
    snd_pcm_stream_t stream;
    int mode;
    void *private_data;

    int setup;
    int donot_close;    /* don't close this PCM */

    snd_pcm_access_t access;
    snd_pcm_format_t format;
    unsigned int channels;
    unsigned int rate;
    snd_pcm_uframes_t period_size;
    unsigned int period_time;
    unsigned int periods;
    snd_pcm_uframes_t avail_min;
    snd_pcm_uframes_t start_threshold;
    snd_pcm_uframes_t stop_threshold;
    snd_pcm_uframes_t silence_size;
    snd_pcm_uframes_t boundary;

    snd_pcm_uframes_t buffer_size;
    unsigned int buffer_time;
    unsigned int sample_bits;
    unsigned int frame_bits;

    snd_pcm_rbptr_t appl;
    snd_pcm_rbptr_t hw;

    unsigned int mmap_rw;   /* use always mmapped buffer */
    unsigned int mmap_shadow;   /* don't call actual mmap, use the mmaped buffer of the slave */
    snd_pcm_channel_info_t *mmap_channels;
    snd_pcm_channel_area_t *running_areas;
    snd_pcm_channel_area_t *stopped_areas;

    const snd_pcm_ops_t *ops;
    const snd_pcm_fast_ops_t *fast_ops;
    snd_pcm_t *op_arg;
    snd_pcm_t *fast_op_arg;

    pthread_mutex_t lock;
};

int snd_pcm_new(snd_pcm_t **pcmp, snd_pcm_type_t type, const char *name, snd_pcm_stream_t stream, int mode);
int snd_pcm_free(snd_pcm_t *pcm);

int snd_pcm_wait_nocheck(snd_pcm_t *pcm, int timeout);

void snd_pcm_areas_from_buf(snd_pcm_t *pcm, snd_pcm_channel_area_t *areas, void *buf);
void snd_pcm_areas_from_bufs(snd_pcm_t *pcm, snd_pcm_channel_area_t *areas, void **bufs);

int snd_pcm_mmap(snd_pcm_t *pcm);
int snd_pcm_munmap(snd_pcm_t *pcm);
void snd_pcm_set_hw_ptr(snd_pcm_t *pcm, volatile snd_pcm_uframes_t *hw_ptr, int fd, off_t offset);
void snd_pcm_set_appl_ptr(snd_pcm_t *pcm, volatile snd_pcm_uframes_t *appl_ptr, int fd, off_t offset);
void snd_pcm_link_hw_ptr(snd_pcm_t *pcm, snd_pcm_t *slave);
void snd_pcm_link_appl_ptr(snd_pcm_t *pcm, snd_pcm_t *slave);
void snd_pcm_unlink_hw_ptr(snd_pcm_t *pcm, snd_pcm_t *slave);
void snd_pcm_unlink_appl_ptr(snd_pcm_t *pcm, snd_pcm_t *slave);
void snd_pcm_mmap_appl_backward(snd_pcm_t *pcm, snd_pcm_uframes_t frames);
void snd_pcm_mmap_appl_forward(snd_pcm_t *pcm, snd_pcm_uframes_t frames);
void snd_pcm_mmap_hw_backward(snd_pcm_t *pcm, snd_pcm_uframes_t frames);
void snd_pcm_mmap_hw_forward(snd_pcm_t *pcm, snd_pcm_uframes_t frames);

typedef snd_pcm_sframes_t (*snd_pcm_xfer_areas_func_t)(snd_pcm_t *pcm,
                               const snd_pcm_channel_area_t *areas,
                               snd_pcm_uframes_t offset,
                               snd_pcm_uframes_t size);

snd_pcm_sframes_t snd_pcm_read_areas(snd_pcm_t *pcm, const snd_pcm_channel_area_t *areas,
                     snd_pcm_uframes_t offset, snd_pcm_uframes_t size,
                     snd_pcm_xfer_areas_func_t func);
snd_pcm_sframes_t snd_pcm_write_areas(snd_pcm_t *pcm, const snd_pcm_channel_area_t *areas,
                      snd_pcm_uframes_t offset, snd_pcm_uframes_t size,
                      snd_pcm_xfer_areas_func_t func);
static inline int snd_pcm_channel_info(snd_pcm_t *pcm, snd_pcm_channel_info_t *info)
{
    return pcm->ops->channel_info(pcm, info);
}
int snd_pcm_channel_info_shm(snd_pcm_t *pcm, snd_pcm_channel_info_t *info, int shmid);

/* return true if the PCM stream may wait to get avail_min space */
static inline int snd_pcm_may_wait_for_avail_min(snd_pcm_t *pcm, snd_pcm_uframes_t avail)
{
    if (avail >= pcm->avail_min)
        return 0;
    if (pcm->fast_ops->may_wait_for_avail_min)
        return pcm->fast_ops->may_wait_for_avail_min(pcm, avail);
    return 1;
}

static inline void snd_pcm_lock(snd_pcm_t *pcm)
{
    pthread_mutex_lock(&pcm->lock);
}

static inline void snd_pcm_unlock(snd_pcm_t *pcm)
{
    pthread_mutex_unlock(&pcm->lock);
}


/* locked versions */
int __snd_pcm_mmap_begin(snd_pcm_t *pcm, const snd_pcm_channel_area_t **areas,
             snd_pcm_uframes_t *offset, snd_pcm_uframes_t *frames);
snd_pcm_sframes_t __snd_pcm_mmap_commit(snd_pcm_t *pcm,
                    snd_pcm_uframes_t offset,
                    snd_pcm_uframes_t frames);
int __snd_pcm_wait_in_lock(snd_pcm_t *pcm, int timeout);

static inline snd_pcm_sframes_t __snd_pcm_avail_update(snd_pcm_t *pcm)
{
    return pcm->fast_ops->avail_update(pcm->fast_op_arg);
}

static inline int __snd_pcm_start(snd_pcm_t *pcm)
{
    return pcm->fast_ops->start(pcm->fast_op_arg);
}

static inline snd_pcm_state_t __snd_pcm_state(snd_pcm_t *pcm)
{
    return pcm->fast_ops->state(pcm->fast_op_arg);
}

static inline int __snd_pcm_hwsync(snd_pcm_t *pcm)
{
    return pcm->fast_ops->hwsync(pcm->fast_op_arg);
}

/* handle special error cases */
static inline int snd_pcm_check_error(snd_pcm_t *pcm, int err)
{
    if (err == -EINTR) {
        switch (__snd_pcm_state(pcm)) {
        case SND_PCM_STATE_XRUN:
            return -EPIPE;
        case SND_PCM_STATE_SUSPENDED:
            return -ESTRPIPE;
        case SND_PCM_STATE_DISCONNECTED:
            return -ENODEV;
        default:
            break;
        }
    }
    return err;
}

static inline snd_pcm_uframes_t snd_pcm_mmap_playback_avail(snd_pcm_t *pcm)
{
    snd_pcm_sframes_t avail;
    avail = *pcm->hw.ptr + pcm->buffer_size - *pcm->appl.ptr;
    if (avail < 0)
        avail += pcm->boundary;
    else if ((snd_pcm_uframes_t) avail >= pcm->boundary)
        avail -= pcm->boundary;
    return avail;
}

static inline snd_pcm_uframes_t snd_pcm_mmap_capture_avail(snd_pcm_t *pcm)
{
    snd_pcm_sframes_t avail;
    avail = *pcm->hw.ptr - *pcm->appl.ptr;
    if (avail < 0)
        avail += pcm->boundary;
    return avail;
}

static inline snd_pcm_uframes_t snd_pcm_mmap_avail(snd_pcm_t *pcm)
{
    if (pcm->stream == SND_PCM_STREAM_PLAYBACK)
        return snd_pcm_mmap_playback_avail(pcm);
    else
        return snd_pcm_mmap_capture_avail(pcm);
}

static inline snd_pcm_sframes_t snd_pcm_mmap_playback_hw_avail(snd_pcm_t *pcm)
{
    return pcm->buffer_size - snd_pcm_mmap_playback_avail(pcm);
}

static inline snd_pcm_sframes_t snd_pcm_mmap_capture_hw_avail(snd_pcm_t *pcm)
{
    return pcm->buffer_size - snd_pcm_mmap_capture_avail(pcm);
}

static inline const snd_pcm_channel_area_t *snd_pcm_mmap_areas(snd_pcm_t *pcm)
{
    if (pcm->stopped_areas && __snd_pcm_state(pcm) != SND_PCM_STATE_RUNNING)
        return pcm->stopped_areas;
    return pcm->running_areas;
}

static inline snd_pcm_uframes_t snd_pcm_mmap_offset(snd_pcm_t *pcm)
{
    assert(pcm);
    return *pcm->appl.ptr % pcm->buffer_size;
}

static inline snd_pcm_uframes_t snd_pcm_mmap_hw_offset(snd_pcm_t *pcm)
{
    assert(pcm);
    return *pcm->hw.ptr % pcm->buffer_size;
}

static inline void *snd_pcm_channel_area_addr(const snd_pcm_channel_area_t *area, snd_pcm_uframes_t offset)
{
    unsigned int bitofs = area->first + area->step * offset;
    assert(bitofs % 8 == 0);
    return (char *) area->addr + bitofs / 8;
}

static inline unsigned int snd_pcm_channel_area_step(const snd_pcm_channel_area_t *area)
{
    assert(area->step % 8 == 0);
    return area->step / 8;
}

static inline snd_pcm_sframes_t _snd_pcm_writei(snd_pcm_t *pcm, const void *buffer, snd_pcm_uframes_t size)
{
    /* lock handled in the callback */
    return pcm->fast_ops->writei(pcm->fast_op_arg, buffer, size);
}

static inline snd_pcm_sframes_t _snd_pcm_readi(snd_pcm_t *pcm, void *buffer, snd_pcm_uframes_t size)
{
    /* lock handled in the callback */
    return pcm->fast_ops->readi(pcm->fast_op_arg, buffer, size);
}



static inline int muldiv(int a, int b, int c, int *r)
{
    int64_t n = (int64_t)a * b;
    int64_t v = n / c;
    if (v > INT_MAX) {
        *r = 0;
        return INT_MAX;
    }
    if (v < INT_MIN) {
        *r = 0;
        return INT_MIN;
    }
    *r = n % c;
    return v;
}

static inline int muldiv_down(int a, int b, int c)
{
    int64_t v = (int64_t)a * b / c;
    if (v > INT_MAX) {
        return INT_MAX;
    }
    if (v < INT_MIN) {
        return INT_MIN;
    }
    return v;
}

static inline int muldiv_near(int a, int b, int c)
{
    int r;
    int n = muldiv(a, b, c, &r);
    if (r >= (c + 1) / 2)
        n++;
    return n;
}

#define SND_PCM_HW_PARBIT_ACCESS    (1U << SND_PCM_HW_PARAM_ACCESS)
#define SND_PCM_HW_PARBIT_FORMAT    (1U << SND_PCM_HW_PARAM_FORMAT)
#define SND_PCM_HW_PARBIT_CHANNELS  (1U << SND_PCM_HW_PARAM_CHANNELS)
#define SND_PCM_HW_PARBIT_RATE      (1U << SND_PCM_HW_PARAM_RATE)
#define SND_PCM_HW_PARBIT_PERIOD_TIME   (1U << SND_PCM_HW_PARAM_PERIOD_TIME)
#define SND_PCM_HW_PARBIT_PERIOD_SIZE   (1U << SND_PCM_HW_PARAM_PERIOD_SIZE)
#define SND_PCM_HW_PARBIT_PERIODS   (1U << SND_PCM_HW_PARAM_PERIODS)
#define SND_PCM_HW_PARBIT_BUFFER_TIME   (1U << SND_PCM_HW_PARAM_BUFFER_TIME)
#define SND_PCM_HW_PARBIT_BUFFER_SIZE   (1U << SND_PCM_HW_PARAM_BUFFER_SIZE)
#define SND_PCM_HW_PARBIT_SAMPLE_BITS   (1U << SND_PCM_HW_PARAM_SAMPLE_BITS)
#define SND_PCM_HW_PARBIT_FRAME_BITS    (1U << SND_PCM_HW_PARAM_FRAME_BITS)
#define SND_PCM_HW_PARBIT_PERIOD_BYTES  (1U << SND_PCM_HW_PARAM_PERIOD_BYTES)
#define SND_PCM_HW_PARBIT_BUFFER_BYTES  (1U << SND_PCM_HW_PARAM_BUFFER_BYTES)

#define SND_PCM_ACCBIT_MMAP  ((1U << SND_PCM_ACCESS_MMAP_INTERLEAVED) | \
                  (1U << SND_PCM_ACCESS_MMAP_NONINTERLEAVED) | \
                  (1U << SND_PCM_ACCESS_MMAP_COMPLEX))
#define SND_PCM_ACCBIT_MMAPI (1U << SND_PCM_ACCESS_MMAP_INTERLEAVED)
#define SND_PCM_ACCBIT_MMAPN (1U << SND_PCM_ACCESS_MMAP_NONINTERLEAVED)
#define SND_PCM_ACCBIT_MMAPC (1U << SND_PCM_ACCESS_MMAP_COMPLEX)

#define SND_PCM_ACCBIT_SHM ((1U << SND_PCM_ACCESS_MMAP_INTERLEAVED) | \
                (1U << SND_PCM_ACCESS_RW_INTERLEAVED) | \
                (1U << SND_PCM_ACCESS_MMAP_NONINTERLEAVED) | \
                (1U << SND_PCM_ACCESS_RW_NONINTERLEAVED))
#define SND_PCM_ACCBIT_SHMI ((1U << SND_PCM_ACCESS_MMAP_INTERLEAVED) | \
                 (1U << SND_PCM_ACCESS_RW_INTERLEAVED))
#define SND_PCM_ACCBIT_SHMN ((1U << SND_PCM_ACCESS_MMAP_NONINTERLEAVED) | \
                 (1U << SND_PCM_ACCESS_RW_NONINTERLEAVED))

#define SND_PCM_FMTBIT_LINEAR \
    ((1U << SND_PCM_FORMAT_S8) | \
     (1U << SND_PCM_FORMAT_U8) | \
     (1U << SND_PCM_FORMAT_S16_LE) | \
     (1U << SND_PCM_FORMAT_S16_BE) | \
     (1U << SND_PCM_FORMAT_U16_LE) | \
     (1U << SND_PCM_FORMAT_U16_BE) | \
     (1U << SND_PCM_FORMAT_S24_LE) | \
     (1U << SND_PCM_FORMAT_S24_BE) | \
     (1U << SND_PCM_FORMAT_U24_LE) | \
     (1U << SND_PCM_FORMAT_U24_BE) | \
     (1U << SND_PCM_FORMAT_S32_LE) | \
     (1U << SND_PCM_FORMAT_S32_BE) | \
     (1U << SND_PCM_FORMAT_U32_LE) | \
     (1U << SND_PCM_FORMAT_U32_BE))

void snd_pcm_hw_param_dump(const snd_pcm_hw_params_t *params, snd_pcm_hw_param_t var);

int snd_pcm_hw_param_empty(const snd_pcm_hw_params_t *params,
               snd_pcm_hw_param_t var);
int snd_pcm_hw_param_always_eq(const snd_pcm_hw_params_t *params,
                   snd_pcm_hw_param_t var,
                   const snd_pcm_hw_params_t *params1);
int snd_pcm_hw_param_never_eq(const snd_pcm_hw_params_t *params,
                  snd_pcm_hw_param_t var,
                  const snd_pcm_hw_params_t *params1);
int snd_pcm_hw_param_get(const snd_pcm_hw_params_t *params, snd_pcm_hw_param_t var,
             unsigned int *val, int *dir);
int snd_pcm_hw_param_get_min(const snd_pcm_hw_params_t *params,
                 snd_pcm_hw_param_t var,
                 unsigned int *val, int *dir);
int snd_pcm_hw_param_get_max(const snd_pcm_hw_params_t *params,
                 snd_pcm_hw_param_t var,
                 unsigned int *val, int *dir);

void _snd_pcm_hw_param_any(snd_pcm_hw_params_t *params, snd_pcm_hw_param_t var);
void _snd_pcm_hw_params_any(snd_pcm_hw_params_t *params);

int _snd_pcm_hw_param_set_mask(snd_pcm_hw_params_t *params,
                   snd_pcm_hw_param_t var, const snd_interval_t *mask);
int _snd_pcm_hw_param_set_range(snd_pcm_hw_params_t *params,
                    snd_pcm_hw_param_t var, const snd_interval_t *val);

int _snd_pcm_hw_param_set(snd_pcm_hw_params_t *param,
              snd_pcm_hw_param_t var, unsigned int val, int dir);

int _snd_pcm_hw_param_set_min(snd_pcm_hw_params_t *params,
                  snd_pcm_hw_param_t var, unsigned int val, int dir);
int _snd_pcm_hw_param_set_max(snd_pcm_hw_params_t *params,
                  snd_pcm_hw_param_t var, unsigned int val, int dir);
int _snd_pcm_hw_param_set_minmax(snd_pcm_hw_params_t *params,
                 snd_pcm_hw_param_t var,
                 unsigned int min, int mindir,
                 unsigned int max, int maxdir);
int _snd_pcm_hw_param_refine(snd_pcm_hw_params_t *params,
                 snd_pcm_hw_param_t var,
                 const snd_pcm_hw_params_t *src);
int _snd_pcm_hw_params_refine(snd_pcm_hw_params_t *params,
                  unsigned int vars,
                  const snd_pcm_hw_params_t *src);

int snd_pcm_hw_param_refine_near(snd_pcm_t *pcm,
                 snd_pcm_hw_params_t *params,
                 snd_pcm_hw_param_t var,
                 const snd_pcm_hw_params_t *src);
int snd_pcm_hw_param_refine_multiple(snd_pcm_t *pcm,
                     snd_pcm_hw_params_t *params,
                     snd_pcm_hw_param_t var,
                     const snd_pcm_hw_params_t *src);

int snd_pcm_hw_refine(snd_pcm_t *pcm, snd_pcm_hw_params_t *params);
int snd_pcm_hw_refine_soft(snd_pcm_t *pcm, snd_pcm_hw_params_t *params);
int snd_pcm_hw_refine_slave(snd_pcm_t *pcm, snd_pcm_hw_params_t *params,
                int (*cprepare)(snd_pcm_t *pcm,
                        snd_pcm_hw_params_t *params),
                int (*cchange)(snd_pcm_t *pcm,
                       snd_pcm_hw_params_t *params,
                       snd_pcm_hw_params_t *sparams),
                int (*sprepare)(snd_pcm_t *pcm,
                        snd_pcm_hw_params_t *params),
                int (*schange)(snd_pcm_t *pcm,
                       snd_pcm_hw_params_t *params,
                       snd_pcm_hw_params_t *sparams),
                int (*srefine)(snd_pcm_t *pcm,
                       snd_pcm_hw_params_t *sparams));
int snd_pcm_hw_params_slave(snd_pcm_t *pcm, snd_pcm_hw_params_t *params,
                int (*cchange)(snd_pcm_t *pcm,
                       snd_pcm_hw_params_t *params,
                       snd_pcm_hw_params_t *sparams),
                int (*sprepare)(snd_pcm_t *pcm,
                        snd_pcm_hw_params_t *params),
                int (*schange)(snd_pcm_t *pcm,
                       snd_pcm_hw_params_t *params,
                       snd_pcm_hw_params_t *sparams),
                int (*sparams)(snd_pcm_t *pcm,
                       snd_pcm_hw_params_t *sparams));

int snd_pcm_hw_param_set(snd_pcm_t *pcm, snd_pcm_hw_params_t *params,
             snd_set_mode_t mode,
             snd_pcm_hw_param_t var, unsigned int val, int dir);
int snd_pcm_hw_param_set_first(snd_pcm_t *pcm, snd_pcm_hw_params_t *params,
                   snd_pcm_hw_param_t var, unsigned int *rval, int *dir);
int snd_pcm_hw_param_set_last(snd_pcm_t *pcm, snd_pcm_hw_params_t *params,
                  snd_pcm_hw_param_t var, unsigned int *rval, int *dir);
int snd_pcm_hw_param_set_min(snd_pcm_t *pcm, snd_pcm_hw_params_t *params,
                 snd_set_mode_t mode,
                 snd_pcm_hw_param_t var, unsigned int *val, int *dir);
int snd_pcm_hw_param_set_max(snd_pcm_t *pcm, snd_pcm_hw_params_t *params,
                 snd_set_mode_t mode,
                 snd_pcm_hw_param_t var, unsigned int *val, int *dir);
int snd_pcm_hw_param_set_minmax(snd_pcm_t *pcm, snd_pcm_hw_params_t *params,
                snd_set_mode_t mode,
                snd_pcm_hw_param_t var,
                unsigned int *min, int *mindir,
                unsigned int *max, int *maxdir);
int snd_pcm_hw_param_set_near(snd_pcm_t *pcm, snd_pcm_hw_params_t *params,
                  snd_pcm_hw_param_t var,
                  unsigned int *val, int *dir);
int snd_pcm_hw_param_set_mask(snd_pcm_t *pcm, snd_pcm_hw_params_t *params,
                  snd_set_mode_t mode,
                  snd_pcm_hw_param_t var, const snd_interval_t *val);

int _snd_pcm_hw_params_internal(snd_pcm_t *pcm, snd_pcm_hw_params_t *params);

static inline int snd_pcm_hw_param_can_changed(
        snd_pcm_hw_params_t *params, snd_pcm_hw_param_t var)
{
#if 0
    return params->cmask & (1 << var);
#endif
    return 1;
}

static inline int snd_pcm_hw_param_change(
        snd_pcm_hw_params_t *params, snd_pcm_hw_param_t var)
{
#if 0
    params->cmask |= (1 << var);
#endif
    return 0;
}


#define SND_PCM_APPEND  (1<<8)

int snd_pcm_open_config(snd_pcm_t **pcmp, const snd_pcm_config_t *pcm_config,
        snd_pcm_stream_t stream, int mode);


/* PCM Helper Functions */
int snd_pcm_format_signed(snd_pcm_format_t format);
int snd_pcm_format_unsigned(snd_pcm_format_t format);
int snd_pcm_format_linear(snd_pcm_format_t format);
int snd_pcm_format_little_endian(snd_pcm_format_t format);
int snd_pcm_format_big_endian(snd_pcm_format_t format);
int snd_pcm_format_width(snd_pcm_format_t format);
snd_pcm_format_t snd_pcm_build_linear_format(int width, int pwidth, int unsignd, int big_endian);

#if 0
static inline snd_interval_t *hw_param_interval(snd_pcm_hw_params_t *params,
                                                snd_pcm_hw_param_t var)
{
        return &params->intervals[var];
}

int snd_interval_refine(snd_interval_t *i, const snd_interval_t *v);
#endif
snd_pcm_chmap_query_t **_snd_pcm_make_single_query_chmaps(const snd_pcm_chmap_t *src);


#ifdef __cplusplus
}
#endif
#endif /* __AW_ALSA_PCM_LOCAL_H */
