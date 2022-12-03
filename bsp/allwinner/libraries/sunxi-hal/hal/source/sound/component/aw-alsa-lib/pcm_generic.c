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

#include <stdlib.h>
#include <stdio.h>
#include "pcm_local.h"
#include "pcm_generic.h"

int snd_pcm_generic_close(snd_pcm_t *pcm)
{
    snd_pcm_generic_t *generic = pcm->private_data;
    int err = 0;
    awalsa_debug("\n");
    if (generic->close_slave)
        err = snd_pcm_close(generic->slave);
    free(generic);
    return err;
}

int snd_pcm_generic_hw_free(snd_pcm_t *pcm)
{
    snd_pcm_generic_t *generic = pcm->private_data;
    awalsa_debug("\n");
    return snd_pcm_hw_free(generic->slave);
}

int snd_pcm_generic_sw_params(snd_pcm_t *pcm, snd_pcm_sw_params_t *params)
{
    snd_pcm_generic_t *generic = pcm->private_data;
    awalsa_debug("\n");
    return snd_pcm_sw_params(generic->slave, params);
}

int snd_pcm_generic_hw_refine(snd_pcm_t *pcm, snd_pcm_hw_params_t *params)
{
    snd_pcm_generic_t *generic = pcm->private_data;
    awalsa_debug("\n");
    return snd_pcm_hw_refine(generic->slave, params);
}

int snd_pcm_generic_hw_params(snd_pcm_t *pcm, snd_pcm_hw_params_t *params)
{
    snd_pcm_generic_t *generic = pcm->private_data;
    awalsa_debug("\n");
    return _snd_pcm_hw_params_internal(generic->slave, params);
}

int snd_pcm_generic_prepare(snd_pcm_t *pcm)
{
    snd_pcm_generic_t *generic = pcm->private_data;
    awalsa_debug("\n");
    return snd_pcm_prepare(generic->slave);
}

int snd_pcm_generic_channel_info(snd_pcm_t *pcm, snd_pcm_channel_info_t *info)
{
    snd_pcm_generic_t *generic = pcm->private_data;
    awalsa_debug("\n");
    if (pcm->mmap_shadow) {
        /* No own buffer is required - the plugin won't change
         * the data on the buffer, or do safely on-the-place
         * conversion
         */
        return snd_pcm_channel_info(generic->slave, info);
    } else {
        /* Allocate own buffer */
        return snd_pcm_channel_info_shm(pcm, info, -1);
    }
}

int snd_pcm_generic_mmap(snd_pcm_t *pcm)
{
    awalsa_debug("\n");
    if (pcm->mmap_shadow) {
        /* Copy the slave mmapped buffer data */
        snd_pcm_generic_t *generic = pcm->private_data;
        pcm->mmap_channels = generic->slave->mmap_channels;
        pcm->running_areas = generic->slave->running_areas;
        pcm->stopped_areas = generic->slave->stopped_areas;
    }
    return 0;
}

int snd_pcm_generic_munmap(snd_pcm_t *pcm)
{
    awalsa_debug("\n");
    if (pcm->mmap_shadow) {
        /* Clean up */
        pcm->mmap_channels = NULL;
        pcm->running_areas = NULL;
        pcm->stopped_areas = NULL;
    }
    return 0;
}

snd_pcm_chmap_query_t **snd_pcm_generic_query_chmaps(snd_pcm_t *pcm)
{
    snd_pcm_generic_t *generic = pcm->private_data;
    awalsa_debug("\n");
    return snd_pcm_query_chmaps(generic->slave);
}

snd_pcm_chmap_t *snd_pcm_generic_get_chmap(snd_pcm_t *pcm)
{
    snd_pcm_generic_t *generic = pcm->private_data;
    awalsa_debug("\n");
    return snd_pcm_get_chmap(generic->slave);
}

int snd_pcm_generic_set_chmap(snd_pcm_t *pcm, const snd_pcm_chmap_t *map)
{
    snd_pcm_generic_t *generic = pcm->private_data;
    awalsa_debug("\n");
    return snd_pcm_set_chmap(generic->slave, map);
}

snd_pcm_state_t snd_pcm_generic_state(snd_pcm_t *pcm)
{
    snd_pcm_generic_t *generic = pcm->private_data;
    awalsa_debug("\n");
    return snd_pcm_state(generic->slave);
}

int snd_pcm_generic_hwsync(snd_pcm_t *pcm)
{
    snd_pcm_generic_t *generic = pcm->private_data;
    awalsa_debug("\n");
    return snd_pcm_hwsync(generic->slave);
}

int snd_pcm_generic_reset(snd_pcm_t *pcm)
{
    snd_pcm_generic_t *generic = pcm->private_data;
    awalsa_debug("\n");
    return snd_pcm_reset(generic->slave);
}

int snd_pcm_generic_start(snd_pcm_t *pcm)
{
    snd_pcm_generic_t *generic = pcm->private_data;
    awalsa_debug("\n");
    return snd_pcm_start(generic->slave);
}

int snd_pcm_generic_drop(snd_pcm_t *pcm)
{
    snd_pcm_generic_t *generic = pcm->private_data;
    awalsa_debug("\n");
    return snd_pcm_drop(generic->slave);
}

int snd_pcm_generic_drain(snd_pcm_t *pcm)
{
    snd_pcm_generic_t *generic = pcm->private_data;
    awalsa_debug("\n");
    return snd_pcm_drain(generic->slave);
}

int snd_pcm_generic_pause(snd_pcm_t *pcm, int enable)
{
    snd_pcm_generic_t *generic = pcm->private_data;
    awalsa_debug("\n");
    return snd_pcm_pause(generic->slave, enable);
}

int snd_pcm_generic_resume(snd_pcm_t *pcm)
{
    snd_pcm_generic_t *generic = pcm->private_data;
    awalsa_debug("\n");
    return snd_pcm_resume(generic->slave);
}

int snd_pcm_generic_delay(snd_pcm_t *pcm, snd_pcm_sframes_t *delayp)
{
    snd_pcm_generic_t *generic = pcm->private_data;
    awalsa_debug("\n");
    return snd_pcm_delay(generic->slave, delayp);
}

snd_pcm_sframes_t snd_pcm_generic_writei(snd_pcm_t *pcm, const void *buffer, snd_pcm_uframes_t size)
{
    snd_pcm_generic_t *generic = pcm->private_data;
    awalsa_debug("\n");
    return _snd_pcm_writei(generic->slave, buffer, size);
}

snd_pcm_sframes_t snd_pcm_generic_readi(snd_pcm_t *pcm, void *buffer, snd_pcm_uframes_t size)
{
    snd_pcm_generic_t *generic = pcm->private_data;
    awalsa_debug("\n");
    return _snd_pcm_readi(generic->slave, buffer, size);
}

snd_pcm_sframes_t snd_pcm_generic_avail_update(snd_pcm_t *pcm)
{
    snd_pcm_generic_t *generic = pcm->private_data;
    awalsa_debug("\n");
    return snd_pcm_avail_update(generic->slave);
}

snd_pcm_sframes_t snd_pcm_generic_mmap_commit(snd_pcm_t *pcm,
                          snd_pcm_uframes_t offset,
                          snd_pcm_uframes_t size)
{
    snd_pcm_generic_t *generic = pcm->private_data;
    awalsa_debug("\n");
    return snd_pcm_mmap_commit(generic->slave, offset, size);
}

int snd_pcm_generic_may_wait_for_avail_min(snd_pcm_t *pcm, snd_pcm_uframes_t avail)
{
    snd_pcm_generic_t *generic = pcm->private_data;
    awalsa_debug("\n");
    return snd_pcm_may_wait_for_avail_min(generic->slave,
            snd_pcm_mmap_avail(generic->slave));
}
