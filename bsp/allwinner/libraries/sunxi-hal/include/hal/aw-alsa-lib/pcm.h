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
#ifndef __AW_ALSA_PCM_H
#define __AW_ALSA_PCM_H
#ifdef __cplusplus
extern "C" {
#endif

#include <sound/ksound.h>
#include <sound/card.h>
#include <sound/pcm_common.h>
#include <alloca.h>
#include <string.h>
#include <sys/types.h>
#include <hal_mutex.h>

#ifndef snd_malloc
#define snd_malloc(size)    calloc(size, 1)
#endif

#ifndef snd_free
#define snd_free(ptr)       free(ptr)
#endif


/* debug option */
#define AW_ALSA_LOG_COLOR_NONE      "\e[0m"
#define AW_ALSA_LOG_COLOR_RED       "\e[31m"
#define AW_ALSA_LOG_COLOR_GREEN     "\e[32m"
#define AW_ALSA_LOG_COLOR_YELLOW    "\e[33m"
#define AW_ALSA_LOG_COLOR_BLUE      "\e[34m"

//#define AW_ALSA_DEBUG
#ifdef AW_ALSA_DEBUG
#define awalsa_debug(fmt, args...) \
    printf(AW_ALSA_LOG_COLOR_GREEN "[AWALSA_DEBUG][%s:%u]" fmt \
        AW_ALSA_LOG_COLOR_NONE, __FUNCTION__, __LINE__, ##args)
#else
#define awalsa_debug(fmt, args...)
#endif

//#define AW_ALSA_PRINT
#ifdef AW_ALSA_PRINT
#define awalsa_print(fmt, args...) \
    printf("[AWALSA_PRINT][%s:%u]" fmt, \
        __FUNCTION__, __LINE__, ##args)
#else
#define awalsa_print(fmt, args...)
#endif

#define awalsa_info(fmt, args...) \
    printf(AW_ALSA_LOG_COLOR_BLUE "[AWALSA_INFO][%s:%u]" fmt \
        AW_ALSA_LOG_COLOR_NONE, __FUNCTION__, __LINE__, ##args)

#define awalsa_err(fmt, args...) \
    printf(AW_ALSA_LOG_COLOR_RED "[AWALSA_ERR][%s:%u]" fmt \
        AW_ALSA_LOG_COLOR_NONE, __FUNCTION__, __LINE__, ##args)
/* end debug option */

/** Non blocking mode (flag for open mode) \hideinitializer */
//#define SND_PCM_NONBLOCK      0x00000001
/** Async notification (flag for open mode) \hideinitializer */
//#define SND_PCM_ASYNC         0x00000002
/** In an abort state (internal, not allowed for open) */
//#define SND_PCM_ABORT         0x00008000
/** Disable automatic (but not forced!) rate resamplinig */
#define SND_PCM_NO_AUTO_RESAMPLE    0x00010000
/** Disable automatic (but not forced!) channel conversion */
#define SND_PCM_NO_AUTO_CHANNELS    0x00020000
/** Disable automatic (but not forced!) format conversion */
#define SND_PCM_NO_AUTO_FORMAT      0x00040000
/** Disable soft volume control */
//#define SND_PCM_NO_SOFTVOL        0x00080000

typedef struct _snd_pcm snd_pcm_t;

enum _snd_pcm_type {
    /** Kernel level PCM */
    SND_PCM_TYPE_HW = 0,
    /** One or more linked PCM with exclusive access to selected
        channels */
    SND_PCM_TYPE_MULTI,
    /** File writing plugin */
    SND_PCM_TYPE_FILE,
    /** Linear format conversion PCM */
    SND_PCM_TYPE_LINEAR,
    /** Rate conversion PCM */
    SND_PCM_TYPE_RATE,
    /** Attenuated static route PCM */
    SND_PCM_TYPE_ROUTE,
    /** Format adjusted PCM */
    SND_PCM_TYPE_PLUG,
    /** Direct Mixing plugin */
    SND_PCM_TYPE_DMIX,
    /** Direct Snooping plugin */
    SND_PCM_TYPE_DSNOOP,
    /** Soft volume plugin */
    SND_PCM_TYPE_SOFTVOL,
    /** External filter plugin */
    SND_PCM_TYPE_EXTPLUG,
    SND_PCM_TYPE_LAST = SND_PCM_TYPE_EXTPLUG
};

/** PCM type */
typedef enum _snd_pcm_type snd_pcm_type_t;

/** PCM state */
typedef enum _snd_pcm_state {
        /** Open */
        SND_PCM_STATE_OPEN = 0,
        /** Setup installed */
        SND_PCM_STATE_SETUP,
        /** Ready to start */
        SND_PCM_STATE_PREPARED,
        /** Running */
        SND_PCM_STATE_RUNNING,
        /** Stopped: underrun (playback) or overrun (capture) detected */
        SND_PCM_STATE_XRUN,
        /** Draining: running (playback) or stopped (capture) */
        SND_PCM_STATE_DRAINING,
        /** Paused */
        SND_PCM_STATE_PAUSED,
        /** Hardware is suspended */
        SND_PCM_STATE_SUSPENDED,
        /** Hardware is disconnected */
        SND_PCM_STATE_DISCONNECTED,
        SND_PCM_STATE_LAST = 1024,
} snd_pcm_state_t;

/** PCM stream (direction) */
typedef enum _snd_pcm_stream {
        /** Playback stream */
        SND_PCM_STREAM_PLAYBACK = 0,
        /** Capture stream */
        SND_PCM_STREAM_CAPTURE,
        SND_PCM_STREAM_LAST = SND_PCM_STREAM_CAPTURE
} snd_pcm_stream_t;


/** PCM area specification */
typedef struct _snd_pcm_channel_area {
    /** base address of channel samples */
    void *addr;
    /** offset to first sample in bits */
    unsigned int first;
    /** samples distance in bits */
    unsigned int step;
} snd_pcm_channel_area_t;


int snd_pcm_open(snd_pcm_t **pcm, const char *name,
        snd_pcm_stream_t stream, int mode);
int snd_pcm_close(snd_pcm_t *pcm);

int snd_pcm_hw_params_malloc(snd_pcm_hw_params_t **ptr);
void snd_pcm_hw_params_free(snd_pcm_hw_params_t *obj);
int snd_pcm_hw_refine(snd_pcm_t *pcm, snd_pcm_hw_params_t *params);
int snd_pcm_hw_params(snd_pcm_t *pcm, snd_pcm_hw_params_t *params);
int snd_pcm_hw_free(snd_pcm_t *pcm);
int snd_pcm_reset(snd_pcm_t *pcm);
int snd_pcm_start(snd_pcm_t *pcm);
int snd_pcm_prepare(snd_pcm_t *pcm);
int snd_pcm_drop(snd_pcm_t *pcm);
int snd_pcm_drain(snd_pcm_t *pcm);
int snd_pcm_pause(snd_pcm_t *pcm, int enable);
int snd_pcm_recover(snd_pcm_t *pcm, int err, int silent);
int snd_pcm_resume(snd_pcm_t *pcm);
snd_pcm_state_t snd_pcm_state(snd_pcm_t *pcm);
snd_pcm_stream_t snd_pcm_stream(snd_pcm_t *pcm);
int snd_pcm_hwsync(snd_pcm_t *pcm);
int snd_pcm_delay(snd_pcm_t *pcm, snd_pcm_sframes_t *delayp);
snd_pcm_sframes_t snd_pcm_avail_update(snd_pcm_t *pcm);
int snd_pcm_hw_params_can_pause(const snd_pcm_hw_params_t *params);
snd_pcm_sframes_t snd_pcm_rewind(snd_pcm_t *pcm, snd_pcm_uframes_t frames);
int snd_pcm_link(snd_pcm_t *pcm1, snd_pcm_t *pcm2);
int snd_pcm_unlink(snd_pcm_t *pcm);

snd_pcm_sframes_t snd_pcm_writei(snd_pcm_t *pcm, const void *buffer, snd_pcm_uframes_t size);
snd_pcm_sframes_t snd_pcm_readi(snd_pcm_t *pcm, void *buffer, snd_pcm_uframes_t size);

int snd_pcm_wait(snd_pcm_t *pcm, int timeout);

int snd_pcm_dump(snd_pcm_t *pcm);
int snd_pcm_dump_setup(snd_pcm_t *pcm);
int snd_pcm_dump_hw_setup(snd_pcm_t *pcm);
int snd_pcm_dump_sw_setup(snd_pcm_t *pcm);
int snd_pcm_hw_params_dump(snd_pcm_hw_params_t *params);

/** channel positions */
enum snd_pcm_chmap_position {
    SND_CHMAP_UNKNOWN = 0,  /**< unspecified */
    SND_CHMAP_NA,       /**< N/A, silent */
    SND_CHMAP_MONO,     /**< mono stream */
    SND_CHMAP_FL,       /**< front left */
    SND_CHMAP_FR,       /**< front right */
    SND_CHMAP_RL,       /**< rear left */
    SND_CHMAP_RR,       /**< rear right */
    SND_CHMAP_FC,       /**< front center */
    SND_CHMAP_LFE,      /**< LFE */
    SND_CHMAP_SL,       /**< side left */
    SND_CHMAP_SR,       /**< side right */
    SND_CHMAP_RC,       /**< rear center */
    SND_CHMAP_FLC,      /**< front left center */
    SND_CHMAP_FRC,      /**< front right center */
    SND_CHMAP_RLC,      /**< rear left center */
    SND_CHMAP_RRC,      /**< rear right center */
    SND_CHMAP_FLW,      /**< front left wide */
    SND_CHMAP_FRW,      /**< front right wide */
    SND_CHMAP_FLH,      /**< front left high */
    SND_CHMAP_FCH,      /**< front center high */
    SND_CHMAP_FRH,      /**< front right high */
    SND_CHMAP_TC,       /**< top center */
    SND_CHMAP_TFL,      /**< top front left */
    SND_CHMAP_TFR,      /**< top front right */
    SND_CHMAP_TFC,      /**< top front center */
    SND_CHMAP_TRL,      /**< top rear left */
    SND_CHMAP_TRR,      /**< top rear right */
    SND_CHMAP_TRC,      /**< top rear center */
    SND_CHMAP_TFLC,     /**< top front left center */
    SND_CHMAP_TFRC,     /**< top front right center */
    SND_CHMAP_TSL,      /**< top side left */
    SND_CHMAP_TSR,      /**< top side right */
    SND_CHMAP_LLFE,     /**< left LFE */
    SND_CHMAP_RLFE,     /**< right LFE */
    SND_CHMAP_BC,       /**< bottom center */
    SND_CHMAP_BLC,      /**< bottom left center */
    SND_CHMAP_BRC,      /**< bottom right center */
    SND_CHMAP_LAST = SND_CHMAP_BRC,
};

/** channel map list type */
enum snd_pcm_chmap_type {
    SND_CHMAP_TYPE_NONE = 0,/**< unspecified channel position */
    SND_CHMAP_TYPE_FIXED,   /**< fixed channel position */
    SND_CHMAP_TYPE_VAR, /**< freely swappable channel position */
    SND_CHMAP_TYPE_PAIRED,  /**< pair-wise swappable channel position */
    SND_CHMAP_TYPE_LAST = SND_CHMAP_TYPE_PAIRED, /**< last entry */
};

/** the channel map header */
typedef struct snd_pcm_chmap {
    unsigned int channels;  /**< number of channels */
    unsigned int pos[0];    /**< channel position array */
} snd_pcm_chmap_t;

/** the header of array items returned from snd_pcm_query_chmaps() */
typedef struct snd_pcm_chmap_query {
    enum snd_pcm_chmap_type type;   /**< channel map type */
    snd_pcm_chmap_t map;        /**< available channel map */
} snd_pcm_chmap_query_t;

snd_pcm_chmap_query_t **snd_pcm_query_chmaps(snd_pcm_t *pcm);
void snd_pcm_free_chmaps(snd_pcm_chmap_query_t **maps);
snd_pcm_chmap_t *snd_pcm_get_chmap(snd_pcm_t *pcm);
int snd_pcm_set_chmap(snd_pcm_t *pcm, const snd_pcm_chmap_t *map);

/* for pthread mutex lock */
typedef hal_mutex_t snd_pcm_mutex_t;
snd_pcm_mutex_t snd_thread_mutex_init(void);
int snd_thread_mutex_lock_timeout(snd_pcm_mutex_t mutex, long ms);
int snd_thread_mutex_lock(snd_pcm_mutex_t mutex);
int snd_thread_mutex_unlock(snd_pcm_mutex_t mutex);
void snd_thread_mutex_destroy(snd_pcm_mutex_t mutex);

size_t snd_pcm_hw_params_sizeof(void);
size_t snd_pcm_sw_params_sizeof(void);

#define __snd_alloca(ptr,type) do { *ptr = (type##_t *) alloca(type##_sizeof()); memset(*ptr, 0, type##_sizeof()); } while (0)
#define snd_pcm_hw_params_alloca(ptr) __snd_alloca(ptr, snd_pcm_hw_params)

int snd_pcm_hw_params_any(snd_pcm_t *pcm, snd_pcm_hw_params_t *params);

int snd_pcm_hw_params_set_format(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, snd_pcm_format_t val);
int snd_pcm_hw_params_get_format(const snd_pcm_hw_params_t *params, snd_pcm_format_t *format);

int snd_pcm_hw_params_set_channels(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, unsigned int val);
int snd_pcm_hw_params_get_channels(const snd_pcm_hw_params_t *params, unsigned int *val);

int snd_pcm_hw_params_set_rate(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, unsigned int val, int dir);
int snd_pcm_hw_params_get_rate(const snd_pcm_hw_params_t *params, unsigned int *val, int *dir);

int snd_pcm_hw_params_set_period_time(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, unsigned int us, int dir);
int snd_pcm_hw_params_set_period_time_near(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, unsigned int *val, int *dir);
int snd_pcm_hw_params_get_period_time(const snd_pcm_hw_params_t *params, unsigned int *val, int *dir);

int snd_pcm_hw_params_set_period_size(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, snd_pcm_uframes_t val, int dir);
int snd_pcm_hw_params_set_period_size_near(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, snd_pcm_uframes_t *val, int *dir);
int snd_pcm_hw_params_get_period_size(const snd_pcm_hw_params_t *params, snd_pcm_uframes_t *val, int *dir);

int snd_pcm_hw_params_set_periods(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, unsigned int val, int dir);
int snd_pcm_hw_params_set_periods_near(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, unsigned int *val, int *dir);
int snd_pcm_hw_params_get_periods(const snd_pcm_hw_params_t *params, unsigned int *val, int *dir);

int snd_pcm_hw_params_set_buffer_size(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, snd_pcm_uframes_t val);
int snd_pcm_hw_params_set_buffer_size_near(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, snd_pcm_uframes_t *val);
int snd_pcm_hw_params_get_buffer_size(const snd_pcm_hw_params_t *params, snd_pcm_uframes_t *val);

int snd_pcm_hw_params_set_buffer_time(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, unsigned int us);
int snd_pcm_hw_params_set_buffer_time_near(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, unsigned int *val, int *dir);

int snd_pcm_hw_params_set_access(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, snd_pcm_access_t access);
int snd_pcm_hw_params_get_access(const snd_pcm_hw_params_t *params, snd_pcm_access_t *access);

#define snd_pcm_sw_params_alloca(ptr) __snd_alloca(ptr, snd_pcm_sw_params)

int snd_pcm_sw_params_current(snd_pcm_t *pcm, snd_pcm_sw_params_t *params);
int snd_pcm_sw_params_set_start_threshold(snd_pcm_t *pcm, snd_pcm_sw_params_t *params, snd_pcm_uframes_t val);
int snd_pcm_sw_params_get_start_threshold(snd_pcm_sw_params_t *params, snd_pcm_uframes_t *val);
int snd_pcm_sw_params_set_stop_threshold(snd_pcm_t *pcm, snd_pcm_sw_params_t *params, snd_pcm_uframes_t val);
int snd_pcm_sw_params_get_stop_threshold(snd_pcm_sw_params_t *params, snd_pcm_uframes_t *val);
int snd_pcm_sw_params_set_silence_size(snd_pcm_t *pcm, snd_pcm_sw_params_t *params, snd_pcm_uframes_t val);
int snd_pcm_sw_params_get_silence_size(snd_pcm_sw_params_t *params, snd_pcm_uframes_t *val);
int snd_pcm_sw_params_set_avail_min(snd_pcm_t *pcm, snd_pcm_sw_params_t *params, snd_pcm_uframes_t val);
int snd_pcm_sw_params_get_avail_min(const snd_pcm_sw_params_t *params, snd_pcm_uframes_t *val);
int snd_pcm_sw_params_get_boundary(const snd_pcm_sw_params_t *params, snd_pcm_uframes_t *val);
int snd_pcm_sw_params(snd_pcm_t *pcm, snd_pcm_sw_params_t *params);


ssize_t snd_pcm_format_size(snd_pcm_format_t format, size_t samples);
snd_pcm_sframes_t snd_pcm_bytes_to_frames(snd_pcm_t *pcm, ssize_t bytes);
ssize_t snd_pcm_frames_to_bytes(snd_pcm_t *pcm, snd_pcm_sframes_t frames);

snd_pcm_type_t snd_pcm_type(snd_pcm_t *pcm);

const char *snd_pcm_type_name(snd_pcm_type_t type);
const char *snd_pcm_stream_name(snd_pcm_stream_t stream);
const char *snd_pcm_access_name(const snd_pcm_access_t _access);
const char *snd_pcm_format_name(const snd_pcm_format_t format);
const char *snd_pcm_state_name(const snd_pcm_state_t state);

/* Direct Access (MMAP) functions */
int snd_pcm_mmap_begin(snd_pcm_t *pcm,
               const snd_pcm_channel_area_t **areas,
               snd_pcm_uframes_t *offset,
               snd_pcm_uframes_t *frames);
snd_pcm_sframes_t snd_pcm_mmap_commit(snd_pcm_t *pcm,
                      snd_pcm_uframes_t offset,
                      snd_pcm_uframes_t frames);
snd_pcm_sframes_t snd_pcm_mmap_writei(snd_pcm_t *pcm, const void *buffer, snd_pcm_uframes_t size);
snd_pcm_sframes_t snd_pcm_mmap_readi(snd_pcm_t *pcm, void *buffer, snd_pcm_uframes_t size);

int snd_pcm_area_silence(const snd_pcm_channel_area_t *dst_channel, snd_pcm_uframes_t dst_offset,
             unsigned int samples, snd_pcm_format_t format);
int snd_pcm_areas_silence(const snd_pcm_channel_area_t *dst_channels, snd_pcm_uframes_t dst_offset,
              unsigned int channels, snd_pcm_uframes_t frames, snd_pcm_format_t format);
int snd_pcm_area_copy(const snd_pcm_channel_area_t *dst_channel, snd_pcm_uframes_t dst_offset,
              const snd_pcm_channel_area_t *src_channel, snd_pcm_uframes_t src_offset,
              unsigned int samples, snd_pcm_format_t format);
int snd_pcm_areas_copy(const snd_pcm_channel_area_t *dst_channels, snd_pcm_uframes_t dst_offset,
               const snd_pcm_channel_area_t *src_channels, snd_pcm_uframes_t src_offset,
               unsigned int channels, snd_pcm_uframes_t frames, snd_pcm_format_t format);

#ifdef __cplusplus
}
#endif

#endif /* __AW_ALSA_PCM_H */
