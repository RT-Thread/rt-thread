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
#ifndef __AW_ALSA_PCM_DIRECT_H
#define __AW_ALSA_PCM_DIRECT_H

#include <aw-alsa-lib/pcm.h>
#include <aw-alsa-lib/plugin/pcm_direct_config.h>
#include <semaphore.h>

#define DIRECT_IPC_SEMS     1
#define DIRECT_IPC_SEM_CLIENT   0

typedef void (mix_areas_t)(unsigned int size,
               volatile void *dst, void *src,
               volatile signed int *sum, size_t dst_step,
               size_t src_step, size_t sum_step);

typedef void (mix_areas_16_t)(unsigned int size,
                  volatile signed short *dst, signed short *src,
                  volatile signed int *sum, size_t dst_step,
                  size_t src_step, size_t sum_step);

typedef void (mix_areas_32_t)(unsigned int size,
                  volatile signed int *dst, signed int *src,
                  volatile signed int *sum, size_t dst_step,
                  size_t src_step, size_t sum_step);

typedef void (mix_areas_24_t)(unsigned int size,
                  volatile unsigned char *dst, unsigned char *src,
                  volatile signed int *sum, size_t dst_step,
                  size_t src_step, size_t sum_step);

typedef void (mix_areas_u8_t)(unsigned int size,
                  volatile unsigned char *dst, unsigned char *src,
                  volatile signed int *sum, size_t dst_step,
                  size_t src_step, size_t sum_step);

typedef struct snd_pcm_direct snd_pcm_direct_t;

/* shared among direct plugin clients - be careful to be 32/64bit compatible! */
typedef struct {
    unsigned int magic;         /* magic number */
    snd_pcm_type_t type;            /* PCM type (currently only hw) */
    struct {
        snd_pcm_format_t format;
        snd_interval_t rate;
        snd_interval_t period_size;
        snd_interval_t period_time;
        snd_interval_t periods;
        snd_interval_t buffer_size;
        snd_interval_t buffer_time;
    } hw;
    struct {
        /* copied to slave PCMs */
        snd_pcm_access_t access;
        snd_pcm_format_t format;
        unsigned int channels;
        unsigned int rate;
        unsigned int period_size;
        unsigned int period_time;
        unsigned int periods;

        unsigned int avail_min;
        unsigned int start_threshold;
        unsigned int stop_threshold;
        unsigned int silence_threshold;
        unsigned int silence_size;

        unsigned int recoveries;    /* no of executed recoveries on slave*/

        unsigned long long boundary;

        unsigned int info;
        unsigned int msbits;
        unsigned int rate_num;
        unsigned int rate_den;
        unsigned int hw_flags;
        unsigned int fifo_size;
        unsigned int buffer_size;
        unsigned int buffer_time;

        unsigned int sample_bits;
        unsigned int frame_bits;
    } s;
    union {
        struct {
            unsigned long long chn_mask;
        } dshare;
    } u;
} snd_pcm_direct_share_t;

struct snd_pcm_direct {
    snd_pcm_type_t type;
    key_t ipc_key;

    sem_t *semid;
    int poll_index;

    int locked[DIRECT_IPC_SEMS];
    snd_pcm_t *spcm;
    snd_pcm_direct_share_t *shmptr;
    snd_pcm_uframes_t appl_ptr;
    snd_pcm_uframes_t last_appl_ptr;
    snd_pcm_uframes_t hw_ptr;
    snd_pcm_uframes_t avail_max;
        snd_pcm_uframes_t slave_appl_ptr;
        snd_pcm_uframes_t slave_hw_ptr;
        snd_pcm_uframes_t slave_period_size;
        snd_pcm_uframes_t slave_buffer_size;
        snd_pcm_uframes_t slave_boundary;

    int (*sync_ptr)(snd_pcm_t *pcm);

    snd_pcm_state_t state;

    int interleaved;
    int slowptr;
    int max_periods;        /* max periods (-1 = fixed periods, 0 = max buffer size) */
    int var_periodsize;     /* allow variable period size if max_periods is != -1*/

    unsigned int channels;
    unsigned int *bindings;
    unsigned int recoveries;    /* mirror of executed recoveries on slave */

    union {
        struct {
            int shmid_sum;          /* IPC global sum ring buffer memory identification */
            int *shm_sum_id;        /* IPC global sum ring buffer memory identification */
            signed int *sum_buffer;     /* shared sum buffer */
            mix_areas_16_t *mix_areas_16;
            mix_areas_32_t *mix_areas_32;
            mix_areas_24_t *mix_areas_24;
            mix_areas_u8_t *mix_areas_u8;
            mix_areas_16_t *remix_areas_16;
            mix_areas_32_t *remix_areas_32;
            mix_areas_24_t *remix_areas_24;
            mix_areas_u8_t *remix_areas_u8;
        } dmix;
        struct {
        } dsnoop;
        struct {
            unsigned long long chn_mask;
        } dshare;
    } u;
};

struct slave_params {
    snd_pcm_format_t format;
        int rate;
        int channels;
        int period_time;
        int buffer_time;
        snd_pcm_sframes_t period_size;
        snd_pcm_sframes_t buffer_size;
        unsigned int periods;
};

static inline int snd_pcm_direct_semaphore_down(snd_pcm_direct_t *dmix, int sem_num)
{
    int ret;

    ret = sem_wait(dmix->semid);
    if (ret != 0) {
        awalsa_err("sem_wait failed, ret=%d\n", ret);
        return -1;
    }
    dmix->locked[sem_num]++;

    return ret;
}

static inline int snd_pcm_direct_semaphore_up(snd_pcm_direct_t *dmix, int sem_num)
{
    int ret;

    ret = sem_post(dmix->semid);
    if (ret != 0) {
        awalsa_err("sem_post failed, ret=%d\n", ret);
        return -1;
    }

    dmix->locked[sem_num]--;

    return ret;
}


int snd_pcm_slave_conf_hw_params(const snd_pcm_direct_slave_config_t *conf, struct slave_params *params);

int snd_pcm_direct_semaphore_shm_create_or_connect(snd_pcm_direct_t *dmix);
int snd_pcm_direct_semaphore_shm_discard(snd_pcm_direct_t *dmix);

int snd_pcm_direct_initialize_slave(snd_pcm_direct_t *dmix, snd_pcm_t *spcm, struct slave_params *params);
int snd_pcm_direct_initialize_secondary_slave(snd_pcm_direct_t *dmix,
                        snd_pcm_t *spcm,
                        struct slave_params *params);

int snd_pcm_direct_last_pcm(snd_pcm_direct_t *dmix);

int snd_pcm_direct_check_interleave(snd_pcm_direct_t *dmix, snd_pcm_t *pcm);

int snd_pcm_direct_hw_refine(snd_pcm_t *pcm, snd_pcm_hw_params_t *params);
int snd_pcm_direct_hw_params(snd_pcm_t *pcm, snd_pcm_hw_params_t * params);
int snd_pcm_direct_hw_free(snd_pcm_t *pcm);
int snd_pcm_direct_sw_params(snd_pcm_t *pcm, snd_pcm_sw_params_t * params);
int snd_pcm_direct_channel_info(snd_pcm_t *pcm, snd_pcm_channel_info_t * info);
int snd_pcm_direct_mmap(snd_pcm_t *pcm);
int snd_pcm_direct_munmap(snd_pcm_t *pcm);
int snd_pcm_direct_prepare(snd_pcm_t *pcm);

int snd_pcm_direct_slave_recover(snd_pcm_direct_t *direct);
int snd_pcm_direct_client_chk_xrun(snd_pcm_direct_t *direct, snd_pcm_t *pcm);
int snd_pcm_direct_wait(snd_pcm_t *pcm, int timeout);

/*TODO*/
int snd_pcm_hw_wait_with_index(snd_pcm_t *hw_pcm, int index, int timeout);
int snd_pcm_hw_poll_index_init(snd_pcm_t *hw_pcm);
int snd_pcm_hw_poll_index_release(snd_pcm_t *hw_pcm, int index);

int snd_pcm_direct_initialize_poll_index(snd_pcm_direct_t *dmix);
int snd_pcm_direct_destroy_poll_index(snd_pcm_direct_t *dmix);

int snd_pcm_direct_last_pcm_drop(snd_pcm_direct_t *dmix);
#endif /* __AW_ALSA_PCM_DIRECT_H */
