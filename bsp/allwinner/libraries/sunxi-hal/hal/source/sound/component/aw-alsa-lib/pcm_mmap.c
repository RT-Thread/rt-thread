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
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "pcm_local.h"

void snd_pcm_mmap_appl_backward(snd_pcm_t *pcm, snd_pcm_uframes_t frames)
{
    snd_pcm_sframes_t appl_ptr = *pcm->appl.ptr;
    appl_ptr -= frames;
    if (appl_ptr < 0)
        appl_ptr += pcm->boundary;
    *pcm->appl.ptr = appl_ptr;
}

void snd_pcm_mmap_appl_forward(snd_pcm_t *pcm, snd_pcm_uframes_t frames)
{
    snd_pcm_uframes_t appl_ptr = *pcm->appl.ptr;
    appl_ptr += frames;
    if (appl_ptr >= pcm->boundary)
        appl_ptr -= pcm->boundary;
    *pcm->appl.ptr = appl_ptr;
}

void snd_pcm_mmap_hw_backward(snd_pcm_t *pcm, snd_pcm_uframes_t frames)
{
    snd_pcm_sframes_t hw_ptr = *pcm->hw.ptr;
    hw_ptr -= frames;
    if (hw_ptr < 0)
        hw_ptr += pcm->boundary;
    *pcm->hw.ptr = hw_ptr;
}

void snd_pcm_mmap_hw_forward(snd_pcm_t *pcm, snd_pcm_uframes_t frames)
{
    snd_pcm_uframes_t hw_ptr = *pcm->hw.ptr;
    hw_ptr += frames;
    if (hw_ptr >= pcm->boundary)
        hw_ptr -= pcm->boundary;
    *pcm->hw.ptr = hw_ptr;
}

static snd_pcm_sframes_t snd_pcm_mmap_write_areas(snd_pcm_t *pcm,
                          const snd_pcm_channel_area_t *areas,
                          snd_pcm_uframes_t offset,
                          snd_pcm_uframes_t size)
{
    snd_pcm_uframes_t xfer = 0;

    if (snd_pcm_mmap_playback_avail(pcm) < size) {
        awalsa_err("too short avail %ld to size %ld\n", snd_pcm_mmap_playback_avail(pcm), size);
        return -EPIPE;
    }
    awalsa_debug("size: %lu\n", size);
    while (size > 0) {
        const snd_pcm_channel_area_t *pcm_areas;
        snd_pcm_uframes_t pcm_offset;
        snd_pcm_uframes_t frames = size;
        snd_pcm_sframes_t result;

        __snd_pcm_mmap_begin(pcm, &pcm_areas, &pcm_offset, &frames);
        snd_pcm_areas_copy(pcm_areas, pcm_offset,
                   areas, offset,
                   pcm->channels,
                   frames, pcm->format);
        result = __snd_pcm_mmap_commit(pcm, pcm_offset, frames);
        if (result < 0)
            return xfer > 0 ? (snd_pcm_sframes_t)xfer : result;
        offset += result;
        xfer += result;
        size -= result;
    }
    return (snd_pcm_sframes_t)xfer;
}

snd_pcm_sframes_t snd_pcm_mmap_writei(snd_pcm_t *pcm, const void *buffer, snd_pcm_uframes_t size)
{
    snd_pcm_channel_area_t areas[pcm->channels];
    snd_pcm_areas_from_buf(pcm, areas, (void*)buffer);
    return snd_pcm_write_areas(pcm, areas, 0, size,
                   snd_pcm_mmap_write_areas);
}

static snd_pcm_sframes_t snd_pcm_mmap_read_areas(snd_pcm_t *pcm,
                         const snd_pcm_channel_area_t *areas,
                         snd_pcm_uframes_t offset,
                         snd_pcm_uframes_t size)
{
    snd_pcm_uframes_t xfer = 0;

    if (snd_pcm_mmap_capture_avail(pcm) < size) {
        awalsa_err("too short avail %ld to size %ld\n", snd_pcm_mmap_capture_avail(pcm), size);
        return -EPIPE;
    }
    while (size > 0) {
        const snd_pcm_channel_area_t *pcm_areas;
        snd_pcm_uframes_t pcm_offset;
        snd_pcm_uframes_t frames = size;
        snd_pcm_sframes_t result;

        __snd_pcm_mmap_begin(pcm, &pcm_areas, &pcm_offset, &frames);
        snd_pcm_areas_copy(areas, offset,
                   pcm_areas, pcm_offset,
                   pcm->channels,
                   frames, pcm->format);
        result = __snd_pcm_mmap_commit(pcm, pcm_offset, frames);
        if (result < 0)
            return xfer > 0 ? (snd_pcm_sframes_t)xfer : result;
        offset += result;
        xfer += result;
        size -= result;
    }
    return (snd_pcm_sframes_t)xfer;
}

snd_pcm_sframes_t snd_pcm_mmap_readi(snd_pcm_t *pcm, void *buffer, snd_pcm_uframes_t size)
{
    snd_pcm_channel_area_t areas[pcm->channels];
    snd_pcm_areas_from_buf(pcm, areas, buffer);
    return snd_pcm_read_areas(pcm, areas, 0, size,
                  snd_pcm_mmap_read_areas);
}

int snd_pcm_channel_info_shm(snd_pcm_t *pcm, snd_pcm_channel_info_t *info, int shmid)
{
    switch (pcm->access) {
    case SND_PCM_ACCESS_MMAP_INTERLEAVED:
    case SND_PCM_ACCESS_RW_INTERLEAVED:
        info->first = info->channel * pcm->sample_bits;
        info->step = pcm->frame_bits;
        break;
    case SND_PCM_ACCESS_MMAP_NONINTERLEAVED:
    case SND_PCM_ACCESS_RW_NONINTERLEAVED:
        info->first = 0;
        info->step = pcm->sample_bits;
        break;
    default:
        awalsa_err("invalid access type %d\n", pcm->access);
        return -EINVAL;
    }
    info->addr = 0;
    info->type = SND_PCM_AREA_LOCAL;
    return 0;
}

int snd_pcm_mmap(snd_pcm_t *pcm)
{
    int err;
    unsigned int c;
    assert(pcm);
    assert(pcm->ops->mmap);

    if (!pcm->setup) {
        awalsa_err("PCM not set up\n");
        return -EIO;
    }
    if (pcm->mmap_channels || pcm->running_areas) {
        awalsa_err("Already mmapped\n");
        return -EBUSY;
    }
    err = pcm->ops->mmap(pcm);
    if (err < 0)
        return err;
    if (pcm->mmap_shadow)
        return 0;
    pcm->mmap_channels = calloc(pcm->channels, sizeof(pcm->mmap_channels[0]));
    if (!pcm->mmap_channels)
        return -ENOMEM;
    pcm->running_areas = calloc(pcm->channels, sizeof(pcm->running_areas[0]));
    if (!pcm->running_areas) {
        free(pcm->mmap_channels);
        pcm->mmap_channels = NULL;
        return -ENOMEM;
    }
    for (c = 0; c < pcm->channels; ++c) {
        snd_pcm_channel_info_t *i = &pcm->mmap_channels[c];
        i->channel = c;
        err = snd_pcm_channel_info(pcm, i);
        if (err < 0) {
            free(pcm->mmap_channels);
            free(pcm->running_areas);
            pcm->mmap_channels = NULL;
            pcm->running_areas = NULL;
            return err;
        }
    }

    for (c = 0; c < pcm->channels; ++c) {
        snd_pcm_channel_info_t *i = &pcm->mmap_channels[c];
        snd_pcm_channel_area_t *a = &pcm->running_areas[c];
        char *ptr;
        size_t size;
        unsigned int c1;
        if (i->addr) {
            a->addr = i->addr;
            a->first = i->first;
            a->step = i->step;
            continue;
        }

        size = i->first + i->step * (pcm->buffer_size - 1) + pcm->sample_bits;
        for (c1 = c + 1; c1 < pcm->channels; ++c1) {
            snd_pcm_channel_info_t *i1 = &pcm->mmap_channels[c1];
            size_t s;
            if (i1->type != i->type)
                continue;
            switch (i1->type) {
            case SND_PCM_AREA_MMAP:
            case SND_PCM_AREA_LOCAL:
                break;
            default:
                assert(0);
            }
            s = i1->first + i1->step * (pcm->buffer_size - 1) + pcm->sample_bits;
            if (s > size)
                size = s;
        }
        size = (size + 7) / 8;
        switch (i->type) {
        case SND_PCM_AREA_MMAP:
            /* i->addr has got from snd_pcm_channel_info() */
            break;
        case SND_PCM_AREA_LOCAL:
            awalsa_debug("pcm_type:%s, size=%d, buffer_size=%d, period_size=%d\n",
                snd_pcm_type_name(snd_pcm_type(pcm)),
                size, pcm->buffer_size, pcm->period_size);
            ptr = malloc(size);
            if (ptr == NULL) {
                awalsa_err("malloc failed\n");
                return -ENOMEM;
            }
            i->addr = ptr;
            break;
        default:
            assert(0);
        }

        for (c1 = c + 1; c1 < pcm->channels; ++c1) {
            snd_pcm_channel_info_t *i1 = &pcm->mmap_channels[c1];
            if (i1->type != i->type)
                continue;
            switch (i1->type) {
            case SND_PCM_AREA_MMAP:
                break;
            case SND_PCM_AREA_LOCAL:
                if (pcm->access != SND_PCM_ACCESS_MMAP_INTERLEAVED &&
                        pcm->access != SND_PCM_ACCESS_RW_INTERLEAVED)
                    continue;
                break;
            default:
                assert(0);
            }
            i1->addr = i->addr;
        }

        a->addr = i->addr;
        a->first = i->first;
        a->step = i->step;
    }
    return 0;
}

int snd_pcm_munmap(snd_pcm_t *pcm)
{
    int err;
    unsigned int c;
    assert(pcm);
    assert(pcm->ops->mmap);

    if (!pcm->mmap_channels) {
        awalsa_err("Not mmapped\n");
        return -ENXIO;
    }
    if (pcm->mmap_shadow)
        return pcm->ops->munmap(pcm);

    for (c = 0; c < pcm->channels; ++c) {
        snd_pcm_channel_info_t *i = &pcm->mmap_channels[c];
        unsigned int c1;
        if (!i->addr)
            continue;
        for (c1 = c + 1; c1 < pcm->channels; ++c1) {
            snd_pcm_channel_info_t *i1 = &pcm->mmap_channels[c1];
            if (i1->addr != i->addr)
                continue;
            i1->addr = NULL;
        }
        switch (i->type) {
        case SND_PCM_AREA_MMAP:
            /* do nothing, the spaces are managed by driver */
            break;
        case SND_PCM_AREA_LOCAL:
            free(i->addr);
            break;
        default:
            assert(0);
        }
        i->addr = NULL;
    }

    err = pcm->ops->munmap(pcm);
    if (err < 0)
        return err;
    free(pcm->mmap_channels);
    free(pcm->running_areas);
    pcm->mmap_channels = NULL;
    pcm->running_areas = NULL;
    return 0;
}
