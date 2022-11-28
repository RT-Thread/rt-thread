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
#ifndef SUPPORT_ADB_FORWARD
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "pcm_local.h"
#include <aw-alsa-lib/pcm_plugin.h>
#include <aw-alsa-lib/pcm_config.h>
#include "pcm_plugin_generic.h"

int _snd_pcm_file_open(snd_pcm_t **pcmp, const snd_pcm_config_t *pcm_config,
        snd_pcm_stream_t stream, int mode)
{
    return -1;
}
#else
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "pcm_local.h"
#include <aw-alsa-lib/pcm_plugin.h>
#include <aw-alsa-lib/pcm_config.h>
#include "pcm_plugin_generic.h"
#include <aw_list.h>

#if 0
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#else
#include <lwip/sockets.h>
#endif
#include <strings.h>

#include <adb_forward.h>

enum {
    FILE_MODE_UNKNOWN = 0,
    FILE_MODE_FLASH,
    FILE_MODE_ADB,
    FILE_MODE_NETWORK,
};

#define DEFAULT_PLAYBACK_PORT   (12345)
#define DEFAULT_CAPTURE_PORT    (12346)

typedef enum _snd_pcm_file_format {
    SND_PCM_FILE_FORMAT_RAW,
    SND_PCM_FILE_FORMAT_WAV
} snd_pcm_file_format_t;

typedef struct {
    snd_pcm_generic_t gen;
    int format;
    snd_pcm_uframes_t appl_ptr;
    snd_pcm_uframes_t file_ptr_bytes;
    snd_pcm_uframes_t wbuf_size;
    size_t wbuf_size_bytes;
    size_t wbuf_used_bytes;
    char *wbuf;
    size_t rbuf_size_bytes;
    size_t rbuf_used_bytes;
    char *rbuf;
    snd_pcm_channel_area_t *wbuf_areas;
    size_t buffer_bytes;
    /*struct wav_fmt wav_header;*/
    size_t filelen;

    int port;
    char *server;

    int file_mode;
    int timestamp_debug;
    void *file_mode_private_data;
    uint64_t record_send_len;
} snd_pcm_file_t;


typedef struct file_adb {
    int port;
    snd_pcm_file_t *file;
} file_adb_t;

typedef struct file_socket {
    int sock;
    int state;
} file_socket_t;

__attribute__((weak)) uint64_t adb_get_record_recv_len(void)
{
    return 0;
}

#if 0
#include <sys/time.h>
static int file_mode_send(int sock, void *data, unsigned int len, snd_pcm_file_t *file)
{
    struct timeval start, end;
    int err;
    int debug = file->timestamp_debug;

#if 0
    if (debug)
        gettimeofday(&start, NULL);
    err = send(sock, data, len, 0);
    if (debug) {
        int ms1, ms2;
        gettimeofday(&end, NULL);
        ms1 = start.tv_sec * 1000 + start.tv_usec / 1000;
        ms2 = end.tv_sec * 1000 + end.tv_usec / 1000;
        awalsa_info("[%s]socket send %u bytes takes %ums\n",
            (file->file_mode == FILE_MODE_ADB) ? "adb" : "network",
            len, ms2 - ms1);
    }
#else
    /* TODO, avoid overrun loop, sleep to ensure server recv data */
    int ms1, ms2;
    gettimeofday(&start, NULL);
    adb_forward_send(a->port, data, len);
    file->record_send_len += err;
    gettimeofday(&end, NULL);
    ms1 = start.tv_sec * 1000 + start.tv_usec / 1000;
    ms2 = end.tv_sec * 1000 + end.tv_usec / 1000;
    if (debug) {
        awalsa_info("[%s]socket send %u bytes takes %ums\n",
            (file->file_mode == FILE_MODE_ADB) ? "adb" : "network",
            len, ms2 - ms1);
    }
    if (file->file_mode == FILE_MODE_ADB && ms2 - ms1 > 100) {
        /* in case, sleep and ensure server receive data */
        int sleep_wait_recv = ms2 - ms1;
        uint64_t recv_count;
        if (sleep_wait_recv < 1000)
            sleep_wait_recv = 1000;
        else
            sleep_wait_recv = 2000;
        awalsa_info("send spend %d ms, sleep %d ms to ensure server recv..\n",
                ms2 - ms1, sleep_wait_recv);
        awalsa_info("before sleep, record_send_len=%llu, record_recv_len=%llu\n",
            file->record_send_len, adb_get_record_recv_len());
        usleep(sleep_wait_recv*1000);
        recv_count = adb_get_record_recv_len();
        if (recv_count != 0 &&
            (file->record_send_len - recv_count > (uint64_t)(20*1024))) {
            awalsa_info("send len larger than recv %llu, sleep more\n",
                    file->record_send_len - recv_count);
            sleep(1);
        }
        awalsa_info("after sleep, record_send_len=%llu, record_recv_len=%llu\n",
            file->record_send_len, adb_get_record_recv_len());
    }
#endif

    return err;
}
#endif

static void snd_pcm_file_write_bytes(snd_pcm_t *pcm, size_t bytes)
{
    snd_pcm_file_t *file = pcm->private_data;
    assert(bytes <= file->wbuf_used_bytes);
#if 0
    if (file->format == SND_PCM_FILE_FORMAT_WAV &&
        !file->wav_header.fmt) {
        if (write_wav_header(pcm) < 0)
            return;
    }
#endif
    awalsa_debug("\n");
    while (bytes > 0) {
        snd_pcm_sframes_t err = -1;
        size_t n = bytes;
        size_t cont = file->wbuf_size_bytes - file->file_ptr_bytes;
        if (n > cont)
            n = cont;
        awalsa_debug("file mode=%d\n", file->file_mode);
        if (file->file_mode == FILE_MODE_ADB) {
            file_adb_t *a = (file_adb_t *)file->file_mode_private_data;
            if (!a)
                goto ignore_adb_state;
            /*printf("[%s] line:%d adb forward send %u bytes\n", __func__, __LINE__, n);    */
            adb_forward_send(a->port, file->wbuf + file->file_ptr_bytes, n);
        } else if (file->file_mode == FILE_MODE_NETWORK) {

        }
    ignore_adb_state:
        err = n;
        bytes -= err;
        file->wbuf_used_bytes -= err;
        file->file_ptr_bytes += err;
        if (file->file_ptr_bytes == file->wbuf_size_bytes)
            file->file_ptr_bytes = 0;
        file->filelen += err;
        if ((snd_pcm_uframes_t)err != n)
            break;
    }
}

static void snd_pcm_file_add_frames(snd_pcm_t *pcm,
                    const snd_pcm_channel_area_t *areas,
                    snd_pcm_uframes_t offset,
                    snd_pcm_uframes_t frames)
{
    snd_pcm_file_t *file = pcm->private_data;
    while (frames > 0) {
        snd_pcm_uframes_t n = frames;
        snd_pcm_uframes_t cont = file->wbuf_size - file->appl_ptr;
        snd_pcm_uframes_t avail = file->wbuf_size - snd_pcm_bytes_to_frames(pcm, file->wbuf_used_bytes);
        if (n > cont)
            n = cont;
        if (n > avail)
            n = avail;
        snd_pcm_areas_copy(file->wbuf_areas, file->appl_ptr,
                   areas, offset,
                   pcm->channels, n, pcm->format);
        frames -= n;
        offset += n;
        file->appl_ptr += n;
        if (file->appl_ptr == file->wbuf_size)
            file->appl_ptr = 0;
        file->wbuf_used_bytes += snd_pcm_frames_to_bytes(pcm, n);
        if (file->wbuf_used_bytes > file->buffer_bytes)
            snd_pcm_file_write_bytes(pcm, file->wbuf_used_bytes - file->buffer_bytes);
        assert(file->wbuf_used_bytes < file->wbuf_size_bytes);
    }
}

static int snd_pcm_file_close(snd_pcm_t *pcm)
{
    snd_pcm_file_t *file = pcm->private_data;

    awalsa_debug("\n");
    if (file->file_mode_private_data != NULL) {
        switch (file->file_mode) {
        case FILE_MODE_ADB: {
            file_adb_t *a = file->file_mode_private_data;
            adb_forward_end(a->port);
            free(a);
            }
            break;
        case FILE_MODE_NETWORK: {
            file_socket_t *s = file->file_mode_private_data;
            if (s->sock)
                close(s->sock);
            free(s);
            }
            break;
        }
    }
    if (file->server)
        free(file->server);
    return snd_pcm_generic_close(pcm);
}

static int snd_pcm_file_reset(snd_pcm_t *pcm)
{
    snd_pcm_file_t *file = pcm->private_data;
    awalsa_debug("\n");
    int err = snd_pcm_reset(file->gen.slave);
    if (err >= 0) {
        /* FIXME: Questionable here */
        snd_pcm_file_write_bytes(pcm, file->wbuf_used_bytes);
        assert(file->wbuf_used_bytes == 0);
    }
    return err;
}

static int snd_pcm_file_drop(snd_pcm_t *pcm)
{
    snd_pcm_file_t *file = pcm->private_data;
    int err = snd_pcm_drop(file->gen.slave);
    awalsa_debug("\n");
    if (err >= 0) {
        /* FIXME: Questionable here */
        snd_pcm_file_write_bytes(pcm, file->wbuf_used_bytes);
        assert(file->wbuf_used_bytes == 0);
    }
    return err;
}

/* locking */
static int snd_pcm_file_drain(snd_pcm_t *pcm)
{
    snd_pcm_file_t *file = pcm->private_data;
    int err = snd_pcm_drain(file->gen.slave);
    awalsa_debug("\n");
    if (err >= 0) {
        snd_pcm_lock(pcm);
        snd_pcm_file_write_bytes(pcm, file->wbuf_used_bytes);
        assert(file->wbuf_used_bytes == 0);
        snd_pcm_unlock(pcm);
    }
    return err;
}

/* locking */
static snd_pcm_sframes_t snd_pcm_file_writei(snd_pcm_t *pcm, const void *buffer, snd_pcm_uframes_t size)
{
    snd_pcm_file_t *file = pcm->private_data;
    snd_pcm_channel_area_t areas[pcm->channels];
    /*awalsa_debug("\n");*/
    snd_pcm_sframes_t n = _snd_pcm_writei(file->gen.slave, buffer, size);
    if (n > 0) {
        snd_pcm_areas_from_buf(pcm, areas, (void*) buffer);
        snd_pcm_lock(pcm);
        /*TODO*/
        snd_pcm_file_add_frames(pcm, areas, 0, n);
        snd_pcm_unlock(pcm);
    }
    return n;
}

/* locking */
static snd_pcm_sframes_t snd_pcm_file_readi(snd_pcm_t *pcm, void *buffer, snd_pcm_uframes_t size)
{
    snd_pcm_file_t *file = pcm->private_data;
    snd_pcm_channel_area_t areas[pcm->channels];
    snd_pcm_sframes_t n;

    awalsa_debug("\n");
    n = _snd_pcm_readi(file->gen.slave, buffer, size);
    if (n <= 0)
        return n;

    snd_pcm_areas_from_buf(pcm, areas, buffer);
    snd_pcm_file_add_frames(pcm, areas, 0, n);
    return n;
}

static snd_pcm_sframes_t snd_pcm_file_mmap_commit(snd_pcm_t *pcm,
                              snd_pcm_uframes_t offset,
                          snd_pcm_uframes_t size)
{
    snd_pcm_file_t *file = pcm->private_data;
    snd_pcm_uframes_t ofs;
    snd_pcm_uframes_t siz = size;
    const snd_pcm_channel_area_t *areas;
    snd_pcm_sframes_t result;

    result = snd_pcm_mmap_begin(file->gen.slave, &areas, &ofs, &siz);
    if (result >= 0) {
        assert(ofs == offset && siz == size);
        result = snd_pcm_mmap_commit(file->gen.slave, ofs, siz);
        if (result > 0)
            snd_pcm_file_add_frames(pcm, areas, ofs, result);
    }
    return result;
}

static int snd_pcm_file_hw_free(snd_pcm_t *pcm)
{
    snd_pcm_file_t *file = pcm->private_data;
    free(file->wbuf);
    free(file->wbuf_areas);
    /*free(file->final_fname);*/
    file->wbuf = NULL;
    file->wbuf_areas = NULL;
    /*file->final_fname = NULL;*/
    return snd_pcm_hw_free(file->gen.slave);
}

static int snd_pcm_file_hw_params(snd_pcm_t *pcm, snd_pcm_hw_params_t * params)
{
    snd_pcm_file_t *file = pcm->private_data;
    unsigned int channel;
    snd_pcm_t *slave = file->gen.slave;
    awalsa_debug("\n");
    int err = _snd_pcm_hw_params_internal(slave, params);
    if (err < 0)
        return err;
    file->buffer_bytes = snd_pcm_frames_to_bytes(slave, slave->buffer_size);
    file->wbuf_size = slave->buffer_size * 2;
    file->wbuf_size_bytes = snd_pcm_frames_to_bytes(slave, file->wbuf_size);
    file->wbuf_used_bytes = 0;
    assert(!file->wbuf);
    awalsa_debug("buffer bytes=%d, wbuf_size_bytes=%d\n",
        file->buffer_bytes, file->wbuf_size_bytes);
    file->wbuf = malloc(file->wbuf_size_bytes);
    if (file->wbuf == NULL) {
        snd_pcm_file_hw_free(pcm);
        return -ENOMEM;
    }
    file->wbuf_areas = malloc(sizeof(*file->wbuf_areas) * slave->channels);
    if (file->wbuf_areas == NULL) {
        snd_pcm_file_hw_free(pcm);
        return -ENOMEM;
    }
    file->appl_ptr = file->file_ptr_bytes = 0;
    for (channel = 0; channel < slave->channels; ++channel) {
        snd_pcm_channel_area_t *a = &file->wbuf_areas[channel];
        a->addr = file->wbuf;
        a->first = slave->sample_bits * channel;
        a->step = slave->frame_bits;
    }

    /* pointer may have changed - e.g if plug is used. */
    snd_pcm_unlink_hw_ptr(pcm, file->gen.slave);
    snd_pcm_unlink_appl_ptr(pcm, file->gen.slave);

    snd_pcm_link_hw_ptr(pcm, file->gen.slave);
    snd_pcm_link_appl_ptr(pcm, file->gen.slave);

    return 0;
}

static int snd_pcm_file_wait(snd_pcm_t *pcm, int timeout)
{
    snd_pcm_file_t *file = pcm->private_data;
    snd_pcm_t *spcm = file->gen.slave;

    return snd_pcm_wait_nocheck(spcm, timeout);
}

static void snd_pcm_file_dump(snd_pcm_t *pcm)
{
    snd_pcm_file_t *file = pcm->private_data;

    switch (file->file_mode) {
    case FILE_MODE_ADB:
        printf("File PCM (ADB port:%d)\n", file->port);
        break;
    case FILE_MODE_NETWORK:
        printf("File PCM (NETOWRK server:%s, port:%d)\n",
            file->server ? file->server : "unknown", file->port);
        break;
    default:
        printf("File PCM (Unknown file mode:%d)\n", file->file_mode);
        break;;
    }
    if (pcm->setup) {
        printf("Its setup is:\n");
        snd_pcm_dump_setup(pcm);
    }
    printf("Slave: ");
    snd_pcm_dump(file->gen.slave);
}


static const snd_pcm_ops_t snd_pcm_file_ops = {
    .close = snd_pcm_file_close,
    /*.info = snd_pcm_generic_info,*/
    .hw_refine = snd_pcm_generic_hw_refine,
    .hw_params = snd_pcm_file_hw_params,
    .hw_free = snd_pcm_file_hw_free,
    .sw_params = snd_pcm_generic_sw_params,
    .channel_info = snd_pcm_generic_channel_info,
    .dump = snd_pcm_file_dump,
    /*.nonblock = snd_pcm_generic_nonblock,*/
    /*.async = snd_pcm_generic_async,*/
    .mmap = snd_pcm_generic_mmap,
    .munmap = snd_pcm_generic_munmap,
    .query_chmaps = snd_pcm_generic_query_chmaps,
    .get_chmap = snd_pcm_generic_get_chmap,
    .set_chmap = snd_pcm_generic_set_chmap,
};

static const snd_pcm_fast_ops_t snd_pcm_file_fast_ops = {
    /*.status = snd_pcm_generic_status,*/
    .state = snd_pcm_generic_state,
    .hwsync = snd_pcm_generic_hwsync,
    .delay = snd_pcm_generic_delay,
    .prepare = snd_pcm_generic_prepare,
    .reset = snd_pcm_file_reset,
    .start = snd_pcm_generic_start,
    .drop = snd_pcm_file_drop,
    .drain = snd_pcm_file_drain,
    .pause = snd_pcm_generic_pause,
    /*.rewindable = snd_pcm_file_rewindable,*/
    /*.rewind = snd_pcm_file_rewind,*/
    /*.forwardable = snd_pcm_file_forwardable,*/
    /*.forward = snd_pcm_file_forward,*/
    .resume = snd_pcm_generic_resume,
    /*.link = snd_pcm_generic_link,*/
    /*.link_slaves = snd_pcm_generic_link_slaves,*/
    /*.unlink = snd_pcm_generic_unlink,*/
    .writei = snd_pcm_file_writei,
    /*.writen = snd_pcm_file_writen,*/
    .readi = snd_pcm_file_readi,
    /*.readn = snd_pcm_file_readn,*/
    .avail_update = snd_pcm_generic_avail_update,
    .mmap_commit = snd_pcm_file_mmap_commit,
    /*.htimestamp = snd_pcm_generic_htimestamp,*/
    .wait = snd_pcm_file_wait,
};

static file_adb_t *file_adb_thread_init(int port)
{
    file_adb_t *a = NULL;

    a = calloc(1, sizeof(file_adb_t));
    if (!a) {
        awalsa_err("no memory\n");
        return NULL;
    }
    a->port = port;

    return a;
}

static int file_mode_adb_init(snd_pcm_file_t *file, int port)
{
    file_adb_t *a;

    a = file_adb_thread_init(port);
    if (!a)
        return -1;
    a->file = file;
    file->file_mode_private_data = (void *)a;
    adb_forward_create_with_rawdata(port);
    return 0;
}

static int file_mode_network_init(snd_pcm_file_t *file)
{
    int ret,s;
    struct sockaddr_in addr;
    file_socket_t *sock;

    if (!file->port || !file->server)
        return -1;

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(file->server);
    addr.sin_port = htons(file->port);

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        awalsa_err("create socket failed\n");
        return -1;
    }
    awalsa_debug("server:%s, port:%d\n", file->server, file->port);
    ret = connect(s, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) {
        awalsa_err("connect failed\n");
        goto err;
    }
    sock = calloc(1, sizeof(file_socket_t));
    if (!sock) {
        awalsa_err("no memory\n");
        ret = -1;
        goto err;
    }
    sock->sock = s;
    /*sock->state = FILE_SOCKET_FLAG_INIT;*/
    file->file_mode_private_data = (void *)sock;

    return 0;
err:
    if (s > 0)
        close(s);
    if (sock)
        free(sock);
    return ret;
}

static int snd_pcm_file_mode_init(snd_pcm_file_t *file)
{

    switch (file->file_mode) {
    case FILE_MODE_ADB:
        return file_mode_adb_init(file, file->port);
    case FILE_MODE_NETWORK:
        return file_mode_network_init(file);
    default:
        awalsa_err("unknown file mode:%d\n", file->file_mode);
        return -1;
    }

    return 0;
}

int snd_pcm_file_open(snd_pcm_t **pcmp, const char *name, int port,
            const char *server, int file_mode, const char *fmt,
            int debug, snd_pcm_t *slave, int close_slave,
            snd_pcm_stream_t stream)
{
    snd_pcm_t *pcm;
    snd_pcm_file_t *file;
    snd_pcm_file_format_t format;
    int err;

    awalsa_debug("\n");
    assert(pcmp);
    if (!strcmp(fmt, "raw"))
        format = SND_PCM_FILE_FORMAT_RAW;
    else if (!strcmp(fmt, "wav"))
        format = SND_PCM_FILE_FORMAT_WAV;
    file = calloc(1, sizeof(snd_pcm_file_t));
    if (!file) {
        return -ENOMEM;
    }
    awalsa_debug("\n");

    file->port = port;
    if (server)
        file->server = strdup(server);
    file->file_mode = file_mode;
    snd_pcm_file_mode_init(file);

    file->record_send_len = 0;
    file->timestamp_debug = debug;
    file->format = format;
    file->gen.slave = slave;
    file->gen.close_slave = close_slave;

    err = snd_pcm_new(&pcm, SND_PCM_TYPE_FILE, name, slave->stream, slave->mode);
    if (err < 0)
        goto err;
    awalsa_debug("\n");
    pcm->ops = &snd_pcm_file_ops;
    pcm->fast_ops = &snd_pcm_file_fast_ops;
    pcm->private_data = file;
    pcm->mmap_shadow = 1;
    pcm->stream = stream;
    snd_pcm_link_hw_ptr(pcm, slave);
    snd_pcm_link_appl_ptr(pcm, slave);
    *pcmp = pcm;
    return 0;
err:
    if (file->server)
        free(file->server);
    free(file);
    return -1;
}

int _snd_pcm_file_open(snd_pcm_t **pcmp, const snd_pcm_config_t *pcm_config,
        snd_pcm_stream_t stream, int mode)
{
    int ret;
    const snd_pcm_file_config_t *file_config = (const snd_pcm_file_config_t *)(pcm_config->config);
    const snd_pcm_config_t *sconf = NULL;
    snd_pcm_t *spcm = NULL;
    const char *format = "raw";
    int file_mode = FILE_MODE_UNKNOWN;
    int port = DEFAULT_PLAYBACK_PORT;
    const char *server = NULL;

    awalsa_debug("\n");
    if (file_config->format)
        format = file_config->format;
    if (file_config->mode) {
        if (!strcmp(file_config->mode, "file"))
            file_mode = FILE_MODE_FLASH;
        else if (!strcmp(file_config->mode, "adb"))
            file_mode = FILE_MODE_ADB;
        else if (!strcmp(file_config->mode, "network"))
            file_mode = FILE_MODE_NETWORK;
    }

    if (file_config->port)
        port = file_config->port;
    if (file_config->server)
        server = file_config->server;

    if (!file_config->slave.pcm) {
        awalsa_err("slave is not defiled\n");
        return -EINVAL;
    }
    awalsa_debug("\n");
    sconf = snd_pcm_config_get_config(file_config->slave.pcm);
    if (!sconf) {
        awalsa_err("can't find asym pcm\n");
        return -EINVAL;
    }

    ret = snd_pcm_open_config(&spcm, sconf, stream, mode);
    if (ret < 0) {
        awalsa_err("unable to open slave\n");
        return ret;
    }

    awalsa_debug("\n");
    ret = snd_pcm_file_open(pcmp, pcm_config->name, port, server,
            file_mode, format, file_config->debug,
            spcm, 1, stream);
    if (ret < 0)
        snd_pcm_close(spcm);
    awalsa_debug("\n");

    return ret;
}
#endif /* SUPPORT_ADB_FORWARD */
