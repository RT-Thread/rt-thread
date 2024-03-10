/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _VPU_TEST_H_
#define _VPU_TEST_H_
#include <filesystem/fsapi.h>
#include "sdk.h"
#include "vpu/vpu_lib.h"
#include "vpu/vpu_io.h"
#include "vpu/vpu_util.h"
#include "ipu/ipu_common.h"
#include "vdoa/vdoa.h"
#include "usdhc/usdhc_ifc.h"
#include "registers/regsusdhc.h"

#define MAX_FIFO_SIZE 		32
#define NUM_FRAME_BUFS	64
#define FB_INDEX_MASK		(NUM_FRAME_BUFS - 1)

enum {
    ENDLESS_LOOP_PLAY,
    VIDEO_FILE_PLAY,
};

#define SD_PORT_INDEX	HW_USDHC3
#define SZ_4K			4 * 1024

#define STREAM_BUF_SIZE		0x200000
#define STREAM_FILL_SIZE	0x40000
#define STREAM_READ_SIZE	(512 * 8)
#define STREAM_END_SIZE		0
#define PS_SAVE_SIZE		0x080000
#define VP8_MB_SAVE_SIZE	0x080000
#define MPEG4_SCRATCH_SIZE	0x080000

#define ENCODER_OUTPUT_SIZE	0x2000000

#define STREAM_ENC_PIC_RESET 	1

#define PATH_V4L2	0
#define PATH_FILE	1
#define PATH_NET	2
#define PATH_IPU	3
#define PATH_MEM	4

/* Test operations */
#define ENCODE		1
#define DECODE		2
#define LOOPBACK	3

#define DEFAULT_PORT		5555
#define DEFAULT_PKT_SIZE	0x28000

#define SIZE_USER_BUF            0x1000
#define USER_DATA_INFO_OFFSET    8*17

#define VDOA_DIS            (0)
#define VDOA_EN             (1)

enum {
    MODE420 = 0,
    MODE422 = 1,
    MODE224 = 2,
    MODE444 = 3,
    MODE400 = 4
};

enum {
    VPLAY_FREE_RUN = 0,
    VPLAY_25FPS = 25,
    VPLAY_30FPS = 30,
};

struct frame_buf {
    int32_t addrY;
    int32_t addrCb;
    int32_t addrCr;
    int32_t strideY;
    int32_t strideC;
    int32_t mvColBuf;
    vpu_mem_desc desc;
};

struct v4l_buf {
    void *start;
    off_t offset;
    size_t length;
};

#define MAX_BUF_NUM	32
#define QUEUE_SIZE	(MAX_BUF_NUM + 1)
struct ipu_queue {
    int32_t list[MAX_BUF_NUM + 1];
    int32_t head;
    int32_t tail;
};

struct ipu_buf {
    int32_t ipu_paddr;
    void *ipu_vaddr;
    int32_t field;
};

struct capture_testbuffer {
    size_t offset;
    uint32_t length;
};

struct rot {
    int32_t rot_en;
    int32_t ipu_rot_en;
    int32_t rot_angle;
};

#define MAX_PATH	256
typedef struct codec_control {
    int32_t input;              /* Input file name */
    uint32_t input_mem_addr;    /*active only if the input is stored in memory */
    int32_t output;             /* Output file name */
    uint32_t output_mem_addr;
    int32_t src_scheme;
    int32_t dst_scheme;
    int32_t width;
    int32_t height;
    int32_t enc_width;
    int32_t enc_height;
    int32_t loff;
    int32_t toff;
    int32_t format;
    int32_t deblock_en;
    int32_t dering_en;
    int32_t rot_en;
    int32_t ipu_rot_en;
    int32_t rot_angle;
    int32_t mirror;
    int32_t chromaInterleave;
    int32_t bitrate;
    int32_t gop;
    int32_t save_enc_hdr;
    int32_t count;
    int32_t prescan;
    int32_t bs_mode;
    int32_t mp4_h264Class;
    int32_t fps;
    int32_t mapType;
    int32_t read_mode;
} codec_control_t;

typedef struct {
    const char *name;
     int32_t(*test) (void *arg);
} vpu_test_t;

struct decode {
    DecHandle handle;
    PhysicalAddress phy_bsbuf_addr;
    PhysicalAddress phy_ps_buf;
    PhysicalAddress phy_slice_buf;
    PhysicalAddress phy_vp8_mbparam_buf;
    int32_t phy_slicebuf_size;
    int32_t phy_vp8_mbparam_size;
    uint32_t virt_bsbuf_addr;
    int32_t picwidth;
    int32_t picheight;
    int32_t orig_picwidth;      //for vdoa usage
    int32_t orig_picheight;
    int32_t stride;
    int32_t mjpg_fmt;
    int32_t regfbcount;
    int32_t minfbcount;
    int32_t rot_buf_count;
    int32_t extrafb;
    FrameBuffer *fb;
    struct frame_buf **pfbpool;
    vpu_mem_desc *mvcol_memdesc;
    Rect picCropRect;
    int32_t reorderEnable;
    int32_t tiled2LinearEnable;
    int32_t totalFrameDecoded;
    DecReportInfo mbInfo;
    DecReportInfo mvInfo;
    DecReportInfo frameBufStat;
    DecReportInfo userData;

    struct codec_control *codecctrl;
};

struct encode {
    EncHandle handle;           /* Encoder handle */
    PhysicalAddress phy_bsbuf_addr; /* Physical bitstream buffer */
    uint32_t virt_bsbuf_addr;   /* Virtual bitstream buffer */
    int32_t enc_picwidth;       /* Encoded Picture width */
    int32_t enc_picheight;      /* Encoded Picture height */
    int32_t src_picwidth;       /* Source Picture width */
    int32_t src_picheight;      /* Source Picture height */
    int32_t totalfb;            /* Total number of framebuffers allocated */
    int32_t src_fbid;           /* Index of frame buffer that contains YUV image */
    FrameBuffer *fb;            /* frame buffer base given to encoder */
    struct frame_buf **pfbpool; /* allocated fb pointers are stored here */
    ExtBufCfg scratchBuf;
    int32_t mp4_dataPartitionEnable;
    int32_t ringBufferEnable;
    int32_t mjpg_fmt;
    int32_t mvc_paraset_refresh_en;
    int32_t mvc_extension;
    int32_t linear2TiledEnable;
    int32_t minFrameBufferCount;

    EncReportInfo mbInfo;
    EncReportInfo mvInfo;
    EncReportInfo sliceInfo;

    struct codec_control *codecctrl;    /* command line */
    uint8_t *huffTable;
    uint8_t *qMatTable;
};

typedef struct {
    struct frame_buf *frames[MAX_FIFO_SIZE];
    uint32_t id[MAX_FIFO_SIZE];
    int32_t wrptr;
    int32_t rdptr;
    int32_t size;
    int32_t full;
    uint32_t popCnt;
} vdec_frame_buffer_t;

typedef struct {
    uint32_t bs_start;
    uint32_t bs_offset;
    uint32_t bs_end;
} bs_mem_t;

typedef struct {
    uint32_t timer_start;
    uint32_t timer_elapsed_ms;
} vpu_frame_timer_t;

extern struct decode *g_dec_instance[];
extern struct encode *g_enc_instance[];
extern vdec_frame_buffer_t g_dec_fifo[];
extern uint32_t g_bs_buffer[];
extern int32_t g_current_active_instance;
extern int32_t g_total_active_instance;
extern vpu_resource_t *g_vpu_hw_map;
extern int32_t g_disp_clr_index[];
extern int32_t g_multi_instance;
extern bs_mem_t g_bs_memory;
extern uint32_t g_usdhc_instance;

void framebuf_init(void);
int32_t vpu_stream_read(struct codec_control *cmd, char *buf, int32_t n);
int32_t vpu_stream_write(struct codec_control *cmd, char *buf, int32_t n);
struct frame_buf *framebuf_alloc(int32_t stdMode, int32_t format, int32_t strideY, int32_t height,
                                 int32_t mvCol);
struct frame_buf *tiled_framebuf_alloc(int32_t stdMode, int32_t format, int32_t strideY,
                                       int32_t height, int32_t mvCol, int32_t mapType);
void framebuf_free(struct frame_buf *fb);
int32_t encoder_open(struct encode *enc);
void encoder_close(struct encode *enc);
int32_t encoder_configure(struct encode *enc);
int32_t encoder_allocate_framebuffer(struct encode *enc);
void encoder_free_framebuffer(struct encode *enc);

int32_t decoder_open(struct decode *dec);
void decoder_close(struct decode *dec);
int32_t decoder_parse(struct decode *dec);
int32_t decoder_allocate_framebuffer(struct decode *dec);
void decoder_free_framebuffer(struct decode *dec);
int32_t video_data_cmp(unsigned char *src, unsigned char *dst, int32_t size);
int32_t decoder_setup(void *arg);
int32_t encoder_setup(void *arg);
int32_t ipu_render_refresh(uint32_t ipu_index, uint32_t buffer);
void config_system_parameters(void);
void dec_fifo_init(vdec_frame_buffer_t * fifo, int32_t size);
int32_t dec_fifo_push(vdec_frame_buffer_t * fifo, struct frame_buf **frame, uint32_t id);
int32_t dec_fifo_pop(vdec_frame_buffer_t * fifo, struct frame_buf **frame, uint32_t * id);
int32_t dec_fifo_is_empty(vdec_frame_buffer_t * fifo);
int32_t dec_fifo_is_full(vdec_frame_buffer_t * fifo);
void decoder_frame_display(void);
int32_t decode_test(void *arg);
int32_t encode_test(void *arg);
int32_t dec_fill_bsbuffer(DecHandle handle, struct codec_control *cmd,
                          uint32_t bs_va_startaddr, uint32_t bs_va_endaddr,
                          uint32_t bs_pa_startaddr, int32_t defaultsize);
extern int32_t config_hdmi_si9022(int32_t ipu_index, int32_t ipu_di);
extern void hdmi_1080P60_video_output(int32_t ipu_index, int32_t ipu_di);
extern int32_t ips_hdmi_1080P60_stream(int32_t ipu_index);
extern void hdmi_720P60_video_output(int32_t ipu_index, int32_t ipu_di);
extern int32_t ips_hannstar_xga_yuv_stream(int32_t ipu_index);
extern void ipu_dma_update_buffer(uint32_t ipu_index, uint32_t channel, uint32_t buffer_index,
                                  uint32_t buffer_addr);
extern int32_t ipu_idmac_chan_cur_buff(uint32_t ipu_index, uint32_t channel);
extern void ipu_channel_buf_ready(int32_t ipu_index, int32_t channel, int32_t buf);

#endif
