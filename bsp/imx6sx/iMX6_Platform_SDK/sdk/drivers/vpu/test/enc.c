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

#include <string.h>
#include <stdlib.h>
#include "vpu_test.h"
#include "vpu/vpu_debug.h"

static int32_t frameRateInfo = 0;

/*get the output of encoder to the destination*/
static int32_t enc_read_line_buffer(struct encode *enc, PhysicalAddress paBsBufAddr,
                                    int32_t bsBufsize)
{
    uint32_t vbuf;

    vbuf = enc->virt_bsbuf_addr + paBsBufAddr - enc->phy_bsbuf_addr;
    return vpu_stream_write(enc->codecctrl, (void *)vbuf, bsBufsize);
}

static int32_t
enc_readbs_ring_buffer(EncHandle handle, struct codec_control *cmd,
                       uint32_t bs_va_startaddr, uint32_t bs_va_endaddr, uint32_t bs_pa_startaddr,
                       int32_t defaultsize)
{
    RetCode ret;
    int32_t space = 0, room;
    PhysicalAddress pa_read_ptr, pa_write_ptr;
    uint32_t target_addr, size;

    ret = VPU_EncGetBitstreamBuffer(handle, &pa_read_ptr, &pa_write_ptr, &size);
    if (ret != RETCODE_SUCCESS) {
        err_msg("EncGetBitstreamBuffer failed\n");
        return -1;
    }

    /* No space in ring buffer */
    if (size <= 0)
        return 0;

    if (defaultsize > 0) {
        if (size < defaultsize)
            return 0;

        space = defaultsize;
    } else {
        space = size;
    }

    if (space > 0) {
        target_addr = bs_va_startaddr + (pa_read_ptr - bs_pa_startaddr);
        if ((target_addr + space) > bs_va_endaddr) {
            room = bs_va_endaddr - target_addr;
            vpu_stream_write(cmd, (void *)target_addr, room);
            vpu_stream_write(cmd, (void *)bs_va_startaddr, (space - room));
        } else {
            vpu_stream_write(cmd, (void *)target_addr, space);
        }

        ret = VPU_EncUpdateBitstreamBuffer(handle, space);
        if (ret != RETCODE_SUCCESS) {
            err_msg("EncUpdateBitstreamBuffer failed\n");
            return -1;
        }
    }

    return space;
}

static int32_t encoder_set_header(struct encode *enc)
{
    EncHeaderParam enchdr_param = { 0 };
    EncHandle handle = enc->handle;
    RetCode ret;

    /* Must put encode header before encoding */
    if (enc->codecctrl->format == STD_MPEG4) {
        enchdr_param.headerType = VOS_HEADER;
        VPU_EncGiveCommand(handle, ENC_PUT_MP4_HEADER, &enchdr_param);
        if (enc->ringBufferEnable == 0) {
            ret = enc_read_line_buffer(enc, enchdr_param.buf, enchdr_param.size);
            if (ret < 0)
                return -1;
        }

        enchdr_param.headerType = VIS_HEADER;
        VPU_EncGiveCommand(handle, ENC_PUT_MP4_HEADER, &enchdr_param);
        if (enc->ringBufferEnable == 0) {
            ret = enc_read_line_buffer(enc, enchdr_param.buf, enchdr_param.size);
            if (ret < 0)
                return -1;
        }

        enchdr_param.headerType = VOL_HEADER;
        VPU_EncGiveCommand(handle, ENC_PUT_MP4_HEADER, &enchdr_param);
        if (enc->ringBufferEnable == 0) {
            ret = enc_read_line_buffer(enc, enchdr_param.buf, enchdr_param.size);
            if (ret < 0)
                return -1;
        }
    } else if (enc->codecctrl->format == STD_AVC) {
        if (!enc->mvc_extension || !enc->mvc_paraset_refresh_en) {
            enchdr_param.headerType = SPS_RBSP;
            VPU_EncGiveCommand(handle, ENC_PUT_AVC_HEADER, &enchdr_param);
            if (enc->ringBufferEnable == 0) {
                ret = enc_read_line_buffer(enc, enchdr_param.buf, enchdr_param.size);
                if (ret < 0)
                    return -1;
            }
        }

        if (enc->mvc_extension) {
            enchdr_param.headerType = SPS_RBSP_MVC;
            VPU_EncGiveCommand(handle, ENC_PUT_AVC_HEADER, &enchdr_param);
            if (enc->ringBufferEnable == 0) {
                ret = enc_read_line_buffer(enc, enchdr_param.buf, enchdr_param.size);
                if (ret < 0)
                    return -1;
            }
        }

        enchdr_param.headerType = PPS_RBSP;
        VPU_EncGiveCommand(handle, ENC_PUT_AVC_HEADER, &enchdr_param);
        if (enc->ringBufferEnable == 0) {
            ret = enc_read_line_buffer(enc, enchdr_param.buf, enchdr_param.size);
            if (ret < 0)
                return -1;
        }

        if (enc->mvc_extension) {   /* MVC */
            enchdr_param.headerType = PPS_RBSP_MVC;
            VPU_EncGiveCommand(handle, ENC_PUT_AVC_HEADER, &enchdr_param);
            if (enc->ringBufferEnable == 0) {
                ret = enc_read_line_buffer(enc, enchdr_param.buf, enchdr_param.size);
                if (ret < 0)
                    return -1;
            }
        }
    }

    return 0;
}

void encoder_free_framebuffer(struct encode *enc)
{
    int32_t i;

    for (i = 0; i < enc->totalfb; i++) {
        framebuf_free(enc->pfbpool[i]);
    }

    free(enc->fb);
    free(enc->pfbpool);
}

int32_t encoder_allocate_framebuffer(struct encode *enc)
{
    EncHandle handle = enc->handle;
    int32_t i, enc_stride, src_stride, src_fbid;
    int32_t totalfb, minfbcount, srcfbcount, extrafbcount;
    RetCode ret;
    FrameBuffer *fb;
    PhysicalAddress subSampBaseA = 0, subSampBaseB = 0;
    struct frame_buf **pfbpool;
    EncExtBufInfo extbufinfo = { 0 };
    int32_t enc_fbwidth, enc_fbheight, src_fbwidth, src_fbheight;

    minfbcount = enc->minFrameBufferCount;
    srcfbcount = 1;

    enc_fbwidth = (enc->enc_picwidth + 15) & ~15;
    enc_fbheight = (enc->enc_picheight + 15) & ~15;
    src_fbwidth = (enc->src_picwidth + 15) & ~15;
    src_fbheight = (enc->src_picheight + 15) & ~15;

    if (cpu_is_mx6()) {
        if (enc->codecctrl->format == STD_AVC && enc->mvc_extension)    /* MVC */
            extrafbcount = 2 + 2;   /* Subsamp [2] + Subsamp MVC [2] */
        else if (enc->codecctrl->format == STD_MJPG)
            extrafbcount = 0;
        else
            extrafbcount = 2;   /* Subsamp buffer [2] */
    } else
        extrafbcount = 0;

    enc->totalfb = totalfb = minfbcount + extrafbcount + srcfbcount;

    /* last framebuffer is used as src frame in the test */
    enc->src_fbid = src_fbid = totalfb - 1;

    fb = enc->fb = calloc(totalfb, sizeof(FrameBuffer));
    if (fb == NULL) {
        err_msg("Failed to allocate enc->fb\n");
        return -1;
    }

    pfbpool = enc->pfbpool = calloc(totalfb, sizeof(struct frame_buf *));
    if (pfbpool == NULL) {
        err_msg("Failed to allocate enc->pfbpool\n");
        free(fb);
        return -1;
    }

    if (enc->codecctrl->mapType == LINEAR_FRAME_MAP) {
        /* All buffers are linear */
        for (i = 0; i < minfbcount + extrafbcount; i++) {
            pfbpool[i] = framebuf_alloc(enc->codecctrl->format, enc->mjpg_fmt,
                                        enc_fbwidth, enc_fbheight, 0);
            if (pfbpool[i] == NULL) {
                goto err1;
            }
        }
    } else {
        /* Encoded buffers are tiled */
        for (i = 0; i < minfbcount; i++) {
            pfbpool[i] = tiled_framebuf_alloc(enc->codecctrl->format, enc->mjpg_fmt,
                                              enc_fbwidth, enc_fbheight, 0,
                                              enc->codecctrl->mapType);
            if (pfbpool[i] == NULL)
                goto err1;
        }
        /* sub frames are linear */
        for (i = minfbcount; i < minfbcount + extrafbcount; i++) {
            pfbpool[i] = framebuf_alloc(enc->codecctrl->format, enc->mjpg_fmt,
                                        enc_fbwidth, enc_fbheight, 0);
            if (pfbpool[i] == NULL)
                goto err1;
        }
    }

    for (i = 0; i < minfbcount + extrafbcount; i++) {
        fb[i].myIndex = i;
        fb[i].bufY = pfbpool[i]->addrY;
        fb[i].bufCb = pfbpool[i]->addrCb;
        fb[i].bufCr = pfbpool[i]->addrCr;
        fb[i].strideY = pfbpool[i]->strideY;
        fb[i].strideC = pfbpool[i]->strideC;
    }

    if (cpu_is_mx6() && (enc->codecctrl->format != STD_MJPG)) {
        subSampBaseA = fb[minfbcount].bufY;
        subSampBaseB = fb[minfbcount + 1].bufY;
        if (enc->codecctrl->format == STD_AVC && enc->mvc_extension) {  /* MVC */
            extbufinfo.subSampBaseAMvc = fb[minfbcount + 2].bufY;
            extbufinfo.subSampBaseBMvc = fb[minfbcount + 3].bufY;
        }
    }

    /* Must be a multiple of 16 */
    if (enc->codecctrl->rot_angle == 90 || enc->codecctrl->rot_angle == 270)
        enc_stride = (enc->enc_picheight + 15) & ~15;
    else
        enc_stride = (enc->enc_picwidth + 15) & ~15;
    src_stride = (enc->src_picwidth + 15) & ~15;

    extbufinfo.scratchBuf = enc->scratchBuf;
    ret = VPU_EncRegisterFrameBuffer(handle, fb, minfbcount, enc_stride, src_stride,
                                     subSampBaseA, subSampBaseB, &extbufinfo);
    if (ret != RETCODE_SUCCESS) {
        err_msg("Register frame buffer failed\n");
        goto err1;
    }

    {
        /* Allocate a single frame buffer for source frame */
        pfbpool[src_fbid] = framebuf_alloc(enc->codecctrl->format, enc->mjpg_fmt,
                                           src_fbwidth, src_fbheight, 0);
        if (pfbpool[src_fbid] == NULL) {
            err_msg("failed to allocate single framebuf\n");
            goto err1;
        }

        fb[src_fbid].myIndex = enc->src_fbid;
        fb[src_fbid].bufY = pfbpool[src_fbid]->addrY;
        fb[src_fbid].bufCb = pfbpool[src_fbid]->addrCb;
        fb[src_fbid].bufCr = pfbpool[src_fbid]->addrCr;
        fb[src_fbid].strideY = pfbpool[src_fbid]->strideY;
        fb[src_fbid].strideC = pfbpool[src_fbid]->strideC;
    }

    return 0;

  err1:
    for (i = 0; i < totalfb; i++) {
        framebuf_free(pfbpool[i]);
    }

    free(fb);
    free(pfbpool);
    return -1;
}

static int32_t encoder_start(struct encode *enc)
{
    EncHandle handle = enc->handle;
    EncParam enc_param = { 0 };
    EncOutputInfo outinfo = { 0 };
    int32_t ret = 0;
    int32_t src_fbid = enc->src_fbid, img_size, frame_id = 0;
    struct frame_buf **pfbpool = enc->pfbpool;
    struct frame_buf *pfb;
    uint32_t yuv_addr;
    PhysicalAddress phy_bsbuf_start = enc->phy_bsbuf_addr;
    uint32_t virt_bsbuf_start = enc->virt_bsbuf_addr;
    uint32_t virt_bsbuf_end = virt_bsbuf_start + STREAM_BUF_SIZE;
    int32_t encode_end = 0;
    char frame_index_str[8];
    char *backwards = "\b\b\b\b\b\b\b\b";

    /*put encode header */
    ret = encoder_set_header(enc);
    if (ret) {
        err_msg("Encode fill headers failed\n");
        return -1;
    }

    enc_param.sourceFrame = &enc->fb[src_fbid];
    enc_param.quantParam = 23;
    enc_param.forceIPicture = 0;
    enc_param.skipPicture = 0;
    enc_param.enableAutoSkip = 1;

    enc_param.encLeftOffset = 0;
    enc_param.encTopOffset = 0;

    if ((enc_param.encLeftOffset + enc->enc_picwidth) > enc->src_picwidth) {
        err_msg("Configure is failure for width and left offset\n");
        return -1;
    }
    if ((enc_param.encTopOffset + enc->enc_picheight) > enc->src_picheight) {
        err_msg("Configure is failure for height and top offset\n");
        return -1;
    }

    img_size = enc->src_picwidth * enc->src_picheight * 3 / 2;

    _raw_puts("Frame encoding         ");
    /* The main encoding loop */
    while (1) {
        pfb = pfbpool[src_fbid];
        yuv_addr = pfb->addrY;
        ret = vpu_stream_read(enc->codecctrl, (char *)yuv_addr, img_size);
        //wait untill the SD read finished
        card_wait_xfer_done(SD_PORT_INDEX);

        if (ret <= 0)

            break;

        ret = VPU_EncStartOneFrame(handle, &enc_param);
        if (ret != RETCODE_SUCCESS) {
            err_msg("VPU_EncStartOneFrame failed Err code:%d\n", ret);
            goto err2;
        }

        while (VPU_IsBusy()) {
            hal_delay_us(1000);
            if (enc->ringBufferEnable == 1) {
                ret = enc_readbs_ring_buffer(handle, enc->codecctrl,
                                             virt_bsbuf_start, virt_bsbuf_end,
                                             phy_bsbuf_start, STREAM_READ_SIZE);
                if (ret < 0) {
                    goto err2;
                } else if (ret == 0) {
                    encode_end = 1;
                }
            }
        }

        ret = VPU_EncGetOutputInfo(handle, &outinfo);
        if (ret != RETCODE_SUCCESS) {
            err_msg("VPU_EncGetOutputInfo failed Err code: %d\n", ret);
            goto err2;
        }

        if (outinfo.skipEncoded)
            printf("Skip encoding one Frame!\n");

        if (enc->ringBufferEnable == 0) {
            ret = enc_read_line_buffer(enc, outinfo.bitstreamBuffer, outinfo.bitstreamSize);
            if (ret < 0) {
                err_msg("writing bitstream buffer failed\n");
                goto err2;
            }
        } else
            enc_readbs_ring_buffer(handle, enc->codecctrl, virt_bsbuf_start,
                                   virt_bsbuf_end, phy_bsbuf_start, 0);

        frame_id++;
        sprintf(frame_index_str, "%8d", frame_id);
        _raw_puts(backwards);
        _raw_puts(frame_index_str);
        if (encode_end == 1) {
            break;
        }
    }

    printf("\nTotal encoded %d frames\n", frame_id);

  err2:
    /* For automation of test case */
    if (ret > 0)
        ret = 0;

    return ret;
}

int32_t encoder_configure(struct encode * enc)
{
    EncHandle handle = enc->handle;
    EncInitialInfo initinfo = { 0 };
    RetCode ret;
    MirrorDirection mirror;

    if (enc->codecctrl->rot_en) {
        VPU_EncGiveCommand(handle, ENABLE_ROTATION, 0);
        VPU_EncGiveCommand(handle, ENABLE_MIRRORING, 0);
        VPU_EncGiveCommand(handle, SET_ROTATION_ANGLE, &enc->codecctrl->rot_angle);
        mirror = enc->codecctrl->mirror;
        VPU_EncGiveCommand(handle, SET_MIRROR_DIRECTION, &mirror);
    }

    ret = VPU_EncGetInitialInfo(handle, &initinfo);
    if (ret != RETCODE_SUCCESS) {
        err_msg("Encoder GetInitialInfo failed\n");
        return -1;
    }

    enc->minFrameBufferCount = initinfo.minFrameBufferCount;

    enc->mbInfo.enable = 0;
    enc->mvInfo.enable = 0;
    enc->sliceInfo.enable = 0;

    return 0;
}

void encoder_close(struct encode *enc)
{
    EncOutputInfo outinfo = { 0 };
    RetCode ret;

    ret = VPU_EncClose(enc->handle);
    if (ret == RETCODE_FRAME_NOT_COMPLETE) {
        VPU_EncGetOutputInfo(enc->handle, &outinfo);
        VPU_EncClose(enc->handle);
    }
}

int32_t encoder_open(struct encode *enc)
{
    EncHandle handle = { 0 };
    EncOpenParam encop = { 0 };
    RetCode ret;

    /* Fill up parameters for encoding */
    encop.bitstreamBuffer = enc->phy_bsbuf_addr;
    encop.bitstreamBufferSize = STREAM_BUF_SIZE;
    encop.bitstreamFormat = enc->codecctrl->format;
    encop.mapType = enc->codecctrl->mapType;
    encop.linear2TiledEnable = enc->linear2TiledEnable;

    /* width and height in command line means source image size */
    if (enc->codecctrl->width && enc->codecctrl->height) {
        enc->src_picwidth = enc->codecctrl->width;
        enc->src_picheight = enc->codecctrl->height;
    }

    /* enc_width and enc_height in command line means encoder output size */
    if (enc->codecctrl->enc_width && enc->codecctrl->enc_height) {
        enc->enc_picwidth = enc->codecctrl->enc_width;
        enc->enc_picheight = enc->codecctrl->enc_height;
    } else {
        enc->enc_picwidth = enc->src_picwidth;
        enc->enc_picheight = enc->src_picheight;
    }

    /* If rotation angle is 90 or 270, pic width and height are swapped */
    if (enc->codecctrl->rot_angle == 90 || enc->codecctrl->rot_angle == 270) {
        encop.picWidth = enc->enc_picheight;
        encop.picHeight = enc->enc_picwidth;
    } else {
        encop.picWidth = enc->enc_picwidth;
        encop.picHeight = enc->enc_picheight;
    }

    /*Note: Frame rate cannot be less than 15fps per H.263 spec */
    encop.frameRateInfo = frameRateInfo = 30;
    encop.bitRate = enc->codecctrl->bitrate;
    encop.gopSize = enc->codecctrl->gop;
    encop.slicemode.sliceMode = 0;  /* 0: 1 slice per picture; 1: Multiple slices per picture */
    encop.slicemode.sliceSizeMode = 0;  /* 0: silceSize defined by bits; 1: sliceSize defined by MB number */
    encop.slicemode.sliceSize = 4000;   /* Size of a slice in bits or MB numbers */

    encop.initialDelay = 0;
    encop.vbvBufferSize = 0;    /* 0 = ignore 8 */
    encop.intraRefresh = 0;
    encop.sliceReport = 0;
    encop.mbReport = 0;
    encop.mbQpReport = 0;
    encop.rcIntraQp = -1;
    encop.userQpMax = 0;
    encop.userQpMin = 0;
    encop.userQpMinEnable = 0;
    encop.userQpMaxEnable = 0;

    encop.IntraCostWeight = 0;
    encop.MEUseZeroPmv = 0;
    /* (3: 16x16, 2:32x16, 1:64x32, 0:128x64, H.263(Short Header : always 3) */
    encop.MESearchRange = 3;

    encop.userGamma = (uint32_t) (0.75 * 32768);    /*  (0*32768 <= gamma <= 1*32768) */
    encop.RcIntervalMode = 1;   /* 0:normal, 1:frame_level, 2:slice_level, 3: user defined Mb_level */
    encop.MbInterval = 0;
    encop.avcIntra16x16OnlyModeEnable = 0;

    encop.ringBufferEnable = enc->ringBufferEnable = 0;
    encop.dynamicAllocEnable = 0;
    encop.chromaInterleave = enc->codecctrl->chromaInterleave;

    if (enc->codecctrl->format == STD_MPEG4) {
        encop.EncStdParam.mp4Param.mp4_dataPartitionEnable = 0;
        enc->mp4_dataPartitionEnable = encop.EncStdParam.mp4Param.mp4_dataPartitionEnable;
        encop.EncStdParam.mp4Param.mp4_reversibleVlcEnable = 0;
        encop.EncStdParam.mp4Param.mp4_intraDcVlcThr = 0;
        encop.EncStdParam.mp4Param.mp4_hecEnable = 0;
        encop.EncStdParam.mp4Param.mp4_verid = 2;
    } else if (enc->codecctrl->format == STD_H263) {
        encop.EncStdParam.h263Param.h263_annexIEnable = 0;
        encop.EncStdParam.h263Param.h263_annexJEnable = 1;
        encop.EncStdParam.h263Param.h263_annexKEnable = 0;
        encop.EncStdParam.h263Param.h263_annexTEnable = 0;
    } else if (enc->codecctrl->format == STD_AVC) {
        encop.EncStdParam.avcParam.avc_constrainedIntraPredFlag = 0;
        encop.EncStdParam.avcParam.avc_disableDeblk = 1;
        encop.EncStdParam.avcParam.avc_deblkFilterOffsetAlpha = 6;
        encop.EncStdParam.avcParam.avc_deblkFilterOffsetBeta = 0;
        encop.EncStdParam.avcParam.avc_chromaQpOffset = 10;
        encop.EncStdParam.avcParam.avc_audEnable = 0;
        if (cpu_is_mx6()) {
            encop.EncStdParam.avcParam.interview_en = 0;
            encop.EncStdParam.avcParam.paraset_refresh_en = enc->mvc_paraset_refresh_en = 0;
            encop.EncStdParam.avcParam.prefix_nal_en = 0;
            encop.EncStdParam.avcParam.mvc_extension = enc->codecctrl->mp4_h264Class;
            enc->mvc_extension = enc->codecctrl->mp4_h264Class;
            encop.EncStdParam.avcParam.avc_frameCroppingFlag = 0;
            encop.EncStdParam.avcParam.avc_frameCropLeft = 0;
            encop.EncStdParam.avcParam.avc_frameCropRight = 0;
            encop.EncStdParam.avcParam.avc_frameCropTop = 0;
            encop.EncStdParam.avcParam.avc_frameCropBottom = 0;
            if (enc->codecctrl->rot_angle != 90 &&
                enc->codecctrl->rot_angle != 270 && enc->enc_picheight == 1080) {
                /*
                 * In case of AVC encoder, when we want to use
                 * unaligned display width frameCroppingFlag
                 * parameters should be adjusted to displayable
                 * rectangle
                 */
                encop.EncStdParam.avcParam.avc_frameCroppingFlag = 1;
                encop.EncStdParam.avcParam.avc_frameCropBottom = 8;
            }

        } else {
            encop.EncStdParam.avcParam.avc_fmoEnable = 0;
            encop.EncStdParam.avcParam.avc_fmoType = 0;
            encop.EncStdParam.avcParam.avc_fmoSliceNum = 1;
            encop.EncStdParam.avcParam.avc_fmoSliceSaveBufSize = 32;    /* FMO_SLICE_SAVE_BUF_SIZE */
        }
    }

    ret = VPU_EncOpen(&handle, &encop);
    if (ret != RETCODE_SUCCESS) {
        err_msg("Encoder open failed %d\n", ret);
        return -1;
    }

    enc->handle = handle;
    return 0;
}

int32_t encoder_setup(void *arg)
{
    struct codec_control *codecctrl = NULL;
    vpu_mem_desc mem_desc = { 0 };
    vpu_mem_desc scratch_mem_desc = { 0 };
    struct encode *enc;
    int32_t ret = 0;

    /*set the parameters of encoder input here!! */
    codecctrl = (struct codec_control *)arg;

    /* allocate memory for must remember stuff */
    enc = (struct encode *)calloc(1, sizeof(struct encode));
    if (enc == NULL) {
        err_msg("Failed to allocate encode structure\n");
        return -1;
    }

    /* get the contigous bit stream buffer */
    mem_desc.size = STREAM_BUF_SIZE;
    ret = vpu_malloc(&mem_desc);
    if (ret) {
        err_msg("Unable to obtain physical memory\n");
        free(enc);
        return -1;
    }

    /* mmap that physical buffer, in OS the virt and phy addr could be different */
    enc->virt_bsbuf_addr = mem_desc.virt_addr;
    enc->phy_bsbuf_addr = mem_desc.phy_addr;
    enc->codecctrl = codecctrl;

    /* get the contigous bit stream buffer */
    mem_desc.size = ENCODER_OUTPUT_SIZE;
    ret = vpu_malloc(&mem_desc);
    if (ret) {
        err_msg("Unable to obtain physical memory\n");
        free(enc);
        return -1;
    }
    enc->codecctrl->output_mem_addr = mem_desc.phy_addr;
    g_bs_memory.bs_start = enc->codecctrl->output_mem_addr;
    g_bs_memory.bs_end = enc->codecctrl->output_mem_addr;

    if (enc->codecctrl->mapType) {
        enc->linear2TiledEnable = 1;
        enc->codecctrl->chromaInterleave = 1;   /* Must be CbCrInterleave for tiled */
    } else
        enc->linear2TiledEnable = 0;

    /* open the encoder */
    ret = encoder_open(enc);
    if (ret)
        goto err;

    /* configure the encoder */
    ret = encoder_configure(enc);
    if (ret)
        goto err1;

    if ((codecctrl->format == STD_MPEG4) && enc->mp4_dataPartitionEnable) {
        scratch_mem_desc.size = MPEG4_SCRATCH_SIZE;
        ret = vpu_malloc(&scratch_mem_desc);
        if (ret) {
            err_msg("Unable to obtain physical slice save mem\n");
            goto err1;
        }
        enc->scratchBuf.bufferBase = scratch_mem_desc.phy_addr;
        enc->scratchBuf.bufferSize = scratch_mem_desc.size;
    }
    /* allocate memory for the frame buffers */
    ret = encoder_allocate_framebuffer(enc);
    if (ret)
        goto err1;

    /* start encoding */
    ret = encoder_start(enc);

    if (enc->codecctrl->dst_scheme == PATH_MEM)
        printf("Encoded output is stored from 0x%08x to 0x%08x\n", g_bs_memory.bs_start,
               g_bs_memory.bs_end);

    /* free the allocated framebuffers */
    encoder_free_framebuffer(enc);
  err1:
    /* close the encoder */
    encoder_close(enc);
  err:
    free(enc);
    return ret;
}

int32_t encode_test(void *arg)
{
    struct codec_control *codecctrl;
    int32_t file_in, file_out;

    uint8_t in_enc_file[] = "raw_yv12.yuv";
    uint8_t out_enc_file[] = "out.264";

    codecctrl = (struct codec_control *)calloc(1, sizeof(struct codec_control));
    if (codecctrl == NULL) {
        err_msg("Failed to allocate command structure\n");
        return -1;
    }

    if ((file_in = Fopen(in_enc_file, (uint8_t *) "r")) < 0) {
        printf("Can't open the file: %s !\n", in_enc_file);
        goto err2;
    }

    if ((file_out = Fopen(out_enc_file, (uint8_t *) "w")) < 0) {
        printf("Can't open the file: %s !\n", out_enc_file);
        goto err1;
    }

    /*now enable the INTERRUPT mode of usdhc */
    set_card_access_mode(1, 0);
    
    memset((void *)&g_bs_memory, 0, sizeof(bs_mem_t));
    codecctrl->input = file_in; /* Input file name */
    codecctrl->output = file_out;   /* Output file name */
    codecctrl->format = STD_AVC;
    codecctrl->src_scheme = PATH_FILE;
    codecctrl->dst_scheme = PATH_FILE;
    codecctrl->dering_en = 0;
    codecctrl->deblock_en = 0;
    codecctrl->chromaInterleave = 0;    //partial interleaved mode
    codecctrl->mapType = LINEAR_FRAME_MAP;
    codecctrl->bs_mode = 0;     /*disable pre-scan */
    codecctrl->fps = 24;
    codecctrl->enc_width = 320;
    codecctrl->enc_height = 240;
    codecctrl->width = 320;
    codecctrl->height = 240;
    codecctrl->gop = 0;
    codecctrl->read_mode = 0;
    encoder_setup(codecctrl);

  err1:
    Fclose(file_out);

  err2:
    Fclose(file_in);

    return 0;
}
