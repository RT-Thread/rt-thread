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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vpu_test.h"
#include "vpu/vpu_debug.h"
#include "vpu/vpu_lib.h"
#include "timer/epit.h"
#include "registers/regsepit.h"

bs_mem_t g_bs_memory;
int32_t g_current_active_instance = 0;
int32_t g_total_active_instance = 0;

static int32_t g_is_interlaced_MPEG4 = 0;
static int32_t g_is_frame_drop[MAX_NUM_INSTANCE];

/*This is to choose the display HDMI video mode*/
//#define HDMI_RESOLUTION_720P60
#define HDMI_RESOLUTION_1080P60

static int g_buf_switch_index[MAX_NUM_INSTANCE];

/*
 * Fill the bitstream to VPU ring buffer
 */
int32_t dec_fill_bsbuffer(DecHandle handle, struct codec_control *cmd,
                          uint32_t bs_va_startaddr, uint32_t bs_va_endaddr,
                          uint32_t bs_pa_startaddr, int32_t defaultsize)
{
    RetCode ret;
    PhysicalAddress pa_read_ptr, pa_write_ptr;
    uint32_t target_addr, space;
    int32_t size;
    int32_t nread, room;

    ret = VPU_DecGetBitstreamBuffer(handle, &pa_read_ptr, &pa_write_ptr, &space);
    if (ret != RETCODE_SUCCESS) {
        err_msg("VPU_DecGetBitstreamBuffer failed\n");
        return -1;
    }

    /* Decoder bitstream buffer is empty */
    if (space <= 0)
        return 0;

    if (defaultsize > 0) {
        if (space < defaultsize)
            return 0;

        size = defaultsize;
    } else {
        size = ((space >> 9) << 9);
    }

    if (size == 0)
        return 0;

    /* Fill the bitstream buffer */
    if (bs_va_endaddr == pa_write_ptr) {
        target_addr = bs_va_startaddr;
    } else {
        target_addr = pa_write_ptr;
    }

    if ((target_addr + size) > bs_va_endaddr) {
        room = bs_va_endaddr - target_addr;
        nread = vpu_stream_read(cmd, (void *)target_addr, room);
        if (nread <= 0) {
            /* EOF or error */
            if (nread < 0) {
                return -1;
            }

        }
    } else {
        nread = vpu_stream_read(cmd, (void *)target_addr, size);
        if (nread <= 0) {
            /* EOF or error */
            if (nread < 0) {
                return -1;
            }
        }
    }

    ret = VPU_DecUpdateBitstreamBuffer(handle, nread);
    if (ret != RETCODE_SUCCESS) {
        err_msg("VPU_DecUpdateBitstreamBuffer failed\n");
        return -1;
    }

    return nread;
}

int32_t decoder_start(struct decode * dec)
{
    DecHandle handle = dec->handle;
    int32_t rot_en = dec->codecctrl->rot_en, rot_stride, fwidth, fheight;
    int32_t rot_angle = dec->codecctrl->rot_angle;
    int32_t dering_en = dec->codecctrl->dering_en;
    int32_t mirror;
    int32_t tiled2LinearEnable = dec->tiled2LinearEnable;

    fwidth = ((dec->picwidth + 15) & ~15);
    fheight = ((dec->picheight + 15) & ~15);

    if (rot_en || dering_en || tiled2LinearEnable || (dec->codecctrl->format == STD_MJPG)) {
        /*
         * VPU is setting the rotation angle by counter-clockwise.
         * We convert it to clockwise 
         */
        if (rot_en) {
            if (rot_angle == 90 || rot_angle == 270)
                rot_angle = 360 - rot_angle;
        } else
            rot_angle = 0;
        VPU_DecGiveCommand(handle, SET_ROTATION_ANGLE, &rot_angle);

        mirror = dec->codecctrl->mirror;
        VPU_DecGiveCommand(handle, SET_MIRROR_DIRECTION, &mirror);

        if (rot_en || dering_en) {
            rot_stride = (rot_angle == 90 || rot_angle == 270) ? fheight : fwidth;
        } else
            rot_stride = fwidth;
        VPU_DecGiveCommand(handle, SET_ROTATOR_STRIDE, &rot_stride);
    }

    dec->handle->initDone = 1;

    /*Now we can start video decoding... */

    return 0;
}

void decoder_free_framebuffer(struct decode *dec)
{
    int32_t i, totalfb;

    totalfb = dec->regfbcount + dec->extrafb;

    for (i = 0; i < totalfb; i++) {
        framebuf_free(dec->pfbpool[i]);
    }

    if (dec->fb) {
        free(dec->fb);
        dec->fb = NULL;
    }
    if (dec->pfbpool) {
        free(dec->pfbpool);
        dec->pfbpool = NULL;
    }

    return;
}

int32_t decoder_allocate_framebuffer(struct decode * dec)
{
    DecBufInfo bufinfo;
    int32_t i, regfbcount = dec->regfbcount, totalfb;
    int32_t dst_scheme = dec->codecctrl->dst_scheme, rot_en = dec->codecctrl->rot_en;
    int32_t deblock_en = dec->codecctrl->deblock_en;
    int32_t dering_en = dec->codecctrl->dering_en;
    int32_t tiled2LinearEnable = dec->tiled2LinearEnable;
    RetCode ret;
    DecHandle handle = dec->handle;
    FrameBuffer *fb;
    struct frame_buf **pfbpool;
    int32_t stride;

    if (rot_en || dering_en || tiled2LinearEnable) {
        /*
         * At least 1 extra fb for rotation(or dering) is needed, two extrafb
         * are allocated for rotation 
         */
        dec->rot_buf_count = (dec->codecctrl->dst_scheme == PATH_IPU) ? 2 : 1;
        dec->extrafb += dec->rot_buf_count;
    }

    if (deblock_en) {
        dec->extrafb++;
    }

    totalfb = regfbcount + dec->extrafb;

    fb = dec->fb = calloc(totalfb, sizeof(FrameBuffer));
    if (fb == NULL) {
        err_msg("Failed to allocate fb\n");
        return -1;
    }

    pfbpool = dec->pfbpool = calloc(totalfb, sizeof(struct frame_buf *));
    if (pfbpool == NULL) {
        err_msg("Failed to allocate pfbpool\n");
        free(dec->fb);
        dec->fb = NULL;
        return -1;
    }

    if ((dst_scheme != PATH_IPU) || ((dst_scheme == PATH_IPU) && deblock_en)) {
        if (dec->codecctrl->mapType == LINEAR_FRAME_MAP) {
            /* All buffers are linear */
            for (i = 0; i < totalfb; i++) {
                /*Note by Ray: set the strideline and height to max, to support direct rendering one any display panel */
                pfbpool[i] = framebuf_alloc(dec->codecctrl->format, dec->mjpg_fmt,
                                            FRAME_MAX_WIDTH, FRAME_MAX_HEIGHT, 1);
                if (pfbpool[i] == NULL)
                    goto err;
            }
        } else {
            /* decoded buffers are tiled */
            for (i = 0; i < regfbcount; i++) {
                pfbpool[i] = tiled_framebuf_alloc(dec->codecctrl->format, dec->mjpg_fmt,
                                                  dec->stride, dec->picheight, 1,
                                                  dec->codecctrl->mapType);
                if (pfbpool[i] == NULL)
                    goto err;
            }

            for (i = regfbcount; i < totalfb; i++) {
                /* if tiled2LinearEnable == 1, post processing buffer is linear,
                 * otherwise, the buffer is tiled */
                if (dec->tiled2LinearEnable)
                    pfbpool[i] = framebuf_alloc(dec->codecctrl->format, dec->mjpg_fmt,
                                                dec->stride, dec->picheight, 1);
                else
                    pfbpool[i] = tiled_framebuf_alloc(dec->codecctrl->format, dec->mjpg_fmt,
                                                      dec->stride, dec->picheight, 1,
                                                      dec->codecctrl->mapType);
                if (pfbpool[i] == NULL)
                    goto err;
            }
        }

        for (i = 0; i < totalfb; i++) {
            fb[i].myIndex = i;
            fb[i].bufY = pfbpool[i]->addrY;
            fb[i].bufCb = pfbpool[i]->addrCb;
            fb[i].bufCr = pfbpool[i]->addrCr;
            fb[i].bufMvCol = pfbpool[i]->mvColBuf;
        }

        /*initialize the decoder fifo */
        dec_fifo_init(&g_dec_fifo[dec->handle->instIndex], totalfb);
    }

    stride = ((dec->stride + 15) & ~15);
    if (dec->codecctrl->format == STD_AVC) {
        bufinfo.avcSliceBufInfo.bufferBase = dec->phy_slice_buf;
        bufinfo.avcSliceBufInfo.bufferSize = dec->phy_slicebuf_size;
    } else if (dec->codecctrl->format == STD_VP8) {
        bufinfo.vp8MbDataBufInfo.bufferBase = dec->phy_vp8_mbparam_buf;
        bufinfo.vp8MbDataBufInfo.bufferSize = dec->phy_vp8_mbparam_size;
    }

    /* User needs to fill max suported macro block value of frame as following */
    bufinfo.maxDecFrmInfo.maxMbX = dec->stride / 16;
    bufinfo.maxDecFrmInfo.maxMbY = dec->picheight / 16;
    bufinfo.maxDecFrmInfo.maxMbNum = dec->stride * dec->picheight / 256;

    ret = VPU_DecRegisterFrameBuffer(handle, fb, dec->regfbcount, stride, &bufinfo);
    if (ret != RETCODE_SUCCESS) {
        err_msg("Register frame buffer failed, ret=%d\n", ret);
        goto err;
    }

    return 0;

  err:
    if (dst_scheme != PATH_IPU) {
        for (i = 0; i < totalfb; i++) {
            framebuf_free(pfbpool[i]);
        }
    }

    free(dec->fb);
    free(dec->pfbpool);
    dec->fb = NULL;
    dec->pfbpool = NULL;
    return -1;
}

int32_t decoder_parse(struct decode * dec)
{
    DecInitialInfo initinfo = { 0 };
    DecHandle handle = dec->handle;
    int32_t align, profile, level, extended_fbcount;
    RetCode ret;

    /* Parse bitstream and get width/height/framerate etc */
    VPU_DecSetEscSeqInit(handle, 1);
    ret = VPU_DecGetInitialInfo(handle, &initinfo);
    VPU_DecSetEscSeqInit(handle, 0);
    if (ret != RETCODE_SUCCESS) {
        err_msg("VPU_DecGetInitialInfo failed, ret:%d, errorcode:%d\n", ret, initinfo.errorcode);
        return -1;
    }

    if (initinfo.streamInfoObtained) {
        switch (dec->codecctrl->format) {
        case STD_AVC:
            info_msg("H.264 Profile: %d Level: %d Interlace: %d\n",
                     initinfo.profile, initinfo.level, initinfo.interlace);

            if (initinfo.aspectRateInfo) {
                int32_t aspect_ratio_idc;
                int32_t sar_width, sar_height;

                if ((initinfo.aspectRateInfo >> 16) == 0) {
                    aspect_ratio_idc = (initinfo.aspectRateInfo & 0xFF);
                    info_msg("aspect_ratio_idc: %d\n", aspect_ratio_idc);
                } else {
                    sar_width = (initinfo.aspectRateInfo >> 16) & 0xFFFF;
                    sar_height = (initinfo.aspectRateInfo & 0xFFFF);
                    info_msg("sar_width: %d, sar_height: %d\n", sar_width, sar_height);
                }
            } else {
                info_msg("Aspect Ratio is not present.\n");
            }

            break;
        case STD_VC1:
            if (initinfo.profile == 0)
                info_msg("VC1 Profile: Simple\n");
            else if (initinfo.profile == 1)
                info_msg("VC1 Profile: Main\n");
            else if (initinfo.profile == 2)
                info_msg("VC1 Profile: Advanced\n");

            info_msg("Level: %d Interlace: %d Progressive Segmented Frame: %d\n",
                     initinfo.level, initinfo.interlace, initinfo.vc1_psf);

            if (initinfo.aspectRateInfo)
                info_msg("Aspect Ratio [X, Y]:[%3d, %3d]\n",
                         (initinfo.aspectRateInfo >> 8) & 0xff, (initinfo.aspectRateInfo) & 0xff);
            else
                info_msg("Aspect Ratio is not present.\n");

            break;
        case STD_MPEG2:
            info_msg("Mpeg2 Profile: %d Level: %d Progressive Sequence Flag: %d\n",
                     initinfo.profile, initinfo.level, initinfo.interlace);
            /*
             * Profile: 3'b101: Simple, 3'b100: Main, 3'b011: SNR Scalable,
             * 3'b10: Spatially Scalable, 3'b001: High
             * Level: 4'b1010: Low, 4'b1000: Main, 4'b0110: High 1440, 4'b0100: High
             */
            if (initinfo.aspectRateInfo)
                info_msg("Aspect Ratio Table index: %d\n", initinfo.aspectRateInfo);
            else
                info_msg("Aspect Ratio is not present.\n");
            break;

        case STD_MPEG4:
            if (initinfo.level & 0x80) {    /* VOS Header */
                initinfo.level &= 0x7F;
                if (initinfo.level == 8 && initinfo.profile == 0) {
                    level = 0;
                    profile = 0;    /* Simple, Level_L0 */
                } else {
                    switch (initinfo.profile) {
                    case 0xB:
                        profile = 1;    /* advanced coding efficiency object */
                        break;
                    case 0xF:
                        if ((initinfo.level & 8) == 0)
                            profile = 2;    /* advanced simple object */
                        else
                            profile = 5;    /* reserved */
                        break;
                    case 0x0:
                        profile = 0;
                        break;  /* Simple Profile */
                    default:
                        profile = 5;
                        break;
                    }
                    level = initinfo.level;
                }
            } else {            /* VOL Header only */
                level = 7;      /* reserved */
                switch (initinfo.profile) {
                case 0x1:
                    profile = 0;    /* simple object */
                    break;
                case 0xC:
                    profile = 1;    /* advanced coding efficiency object */
                    break;
                case 0x11:
                    profile = 2;    /* advanced simple object */
                    break;
                default:
                    profile = 5;    /* reserved */
                    break;
                }
            }
            g_is_interlaced_MPEG4 = initinfo.interlace;

            info_msg("Mpeg4 Profile: %d Level: %d Interlaced: %d\n",
                     profile, level, initinfo.interlace);
            /*
             * Profile: 8'b00000000: SP, 8'b00010001: ASP
             * Level: 4'b0000: L0, 4'b0001: L1, 4'b0010: L2, 4'b0011: L3, ...
             * SP: 1/2/3/4a/5/6, ASP: 0/1/2/3/4/5
             */
            if (initinfo.aspectRateInfo)
                info_msg("Aspect Ratio Table index: %d\n", initinfo.aspectRateInfo);
            else
                info_msg("Aspect Ratio is not present.\n");

            break;

        case STD_RV:
            info_msg("RV Profile: %d Level: %d\n", initinfo.profile, initinfo.level);
            break;

        case STD_H263:
            info_msg("H263 Profile: %d Level: %d\n", initinfo.profile, initinfo.level);
            break;

        case STD_DIV3:
            info_msg("DIV3 Profile: %d Level: %d\n", initinfo.profile, initinfo.level);
            break;

        case STD_MJPG:
            dec->mjpg_fmt = initinfo.mjpg_sourceFormat;
            info_msg("MJPG SourceFormat: %d\n", initinfo.mjpg_sourceFormat);
            break;

        case STD_AVS:
            info_msg("AVS Profile: %d Level: %d\n", initinfo.profile, initinfo.level);
            break;

        case STD_VP8:
            info_msg("VP8 Profile: %d Level: %d\n", initinfo.profile, initinfo.level);
            info_msg("hScaleFactor: %d vScaleFactor:%d\n",
                     initinfo.vp8ScaleInfo.hScaleFactor, initinfo.vp8ScaleInfo.vScaleFactor);
            break;
        default:
            break;
        }
    }

    info_msg("Decoder: width = %d, height = %d, frameRateRes = %d, frameRateDiv = %d, count = %u\n",
             initinfo.picWidth, initinfo.picHeight,
             initinfo.frameRateRes, initinfo.frameRateDiv, initinfo.minFrameBufferCount);

    /*
     * We suggest to add two more buffers than minFrameBufferCount:
     *
     * VPU_DecClrDispFlag is used to control framebuffer whether can be
     * used for decoder again. One framebuffer dequeue from IPU is delayed
     * for performance improvement and one framebuffer is delayed for
     * display flag clear.
     *
     * Performance is better when more buffers are used if IPU performance
     * is bottleneck.
     *
     * Two more buffers may be needed for interlace stream from IPU DVI view
     */
    dec->minfbcount = initinfo.minFrameBufferCount;
    extended_fbcount = 2;

    if (initinfo.interlace)
        dec->regfbcount = dec->minfbcount + extended_fbcount + 2;
    else
        dec->regfbcount = dec->minfbcount + extended_fbcount;

    /*the original picwidth and picheight is for vdoa usage */
    dec->orig_picwidth = initinfo.picWidth;
    dec->orig_picheight = initinfo.picHeight;
    dec->picwidth = ((initinfo.picWidth + 15) & ~15);

    align = 16;

    if ((dec->codecctrl->format == STD_MPEG2 ||
         dec->codecctrl->format == STD_VC1 ||
         dec->codecctrl->format == STD_AVC || dec->codecctrl->format == STD_VP8)
        && initinfo.interlace == 1)
        align = 32;

    dec->picheight = ((initinfo.picHeight + align - 1) & ~(align - 1));

    if ((dec->picwidth == 0) || (dec->picheight == 0))
        return -1;

    /*
     * Information about H.264 decoder picture cropping rectangle which
     * presents the offset of top-left point and bottom-right point from
     * the origin of frame buffer.
     *
     * By using these four offset values, host application can easily
     * detect the position of target output window. When display cropping
     * is off, the cropping window size will be 0.
     *
     * This structure for cropping rectangles is only valid for H.264
     * decoder case.
     */

    /* Add non-h264 crop support, assume left=top=0 */
    if ((dec->picwidth > initinfo.picWidth ||
         dec->picheight > initinfo.picHeight) &&
        (!initinfo.picCropRect.left &&
         !initinfo.picCropRect.top &&
         !initinfo.picCropRect.right && !initinfo.picCropRect.bottom)) {
        initinfo.picCropRect.left = 0;
        initinfo.picCropRect.top = 0;
        initinfo.picCropRect.right = initinfo.picWidth;
        initinfo.picCropRect.bottom = initinfo.picHeight;
    }

    info_msg("CROP left/top/right/bottom %d %d %d %d\n",
             initinfo.picCropRect.left,
             initinfo.picCropRect.top, initinfo.picCropRect.right, initinfo.picCropRect.bottom);

    memcpy(&(dec->picCropRect), &(initinfo.picCropRect), sizeof(initinfo.picCropRect));

    /* worstSliceSize is in kilo-byte unit */
    dec->phy_slicebuf_size = initinfo.worstSliceSize * 1024;
    /*Note by Ray: to support direct rendering */
    if (dec->codecctrl->mapType != LINEAR_FRAME_MAP)
        dec->stride = dec->picwidth;
    else
        dec->stride = FRAME_MAX_WIDTH;

    info_msg("Display fps will be %d\n", dec->codecctrl->fps);

    return 0;
}

int32_t decoder_open(struct decode * dec)
{
    RetCode ret;
    DecHandle handle = { 0 };
    DecOpenParam oparam = { 0 };
    if (dec->codecctrl->mapType == LINEAR_FRAME_MAP)
        dec->tiled2LinearEnable = 0;
    else
        /* CbCr interleave must be enabled for tiled map */
        dec->codecctrl->chromaInterleave = 1;

    oparam.bitstreamFormat = dec->codecctrl->format;
    oparam.bitstreamBuffer = dec->phy_bsbuf_addr;
    oparam.bitstreamBufferSize = STREAM_BUF_SIZE;
    oparam.pBitStream = (uint8_t *) dec->virt_bsbuf_addr;
    oparam.reorderEnable = dec->reorderEnable;
    oparam.mp4DeblkEnable = dec->codecctrl->deblock_en;
    oparam.chromaInterleave = dec->codecctrl->chromaInterleave;
    oparam.mp4Class = dec->codecctrl->mp4_h264Class;
    oparam.avcExtension = dec->codecctrl->mp4_h264Class;
    oparam.mjpg_thumbNailDecEnable = 0;
    oparam.mapType = dec->codecctrl->mapType;
    oparam.tiled2LinearEnable = dec->tiled2LinearEnable;
    oparam.bitstreamMode = dec->codecctrl->bs_mode;

    if (oparam.mp4DeblkEnable == 1) {
        dec->codecctrl->deblock_en = 0;
    }

    oparam.psSaveBuffer = dec->phy_ps_buf;
    oparam.psSaveBufferSize = PS_SAVE_SIZE;

    ret = VPU_DecOpen(&handle, &oparam);
    if (ret != RETCODE_SUCCESS) {
        err_msg("VPU_DecOpen failed %d\n", ret);
        return -1;
    }

    dec->handle = handle;
    return 0;
}

void decoder_close(struct decode *dec)
{
    DecOutputInfo outinfo = { 0 };
    RetCode ret;

    ret = VPU_DecClose(dec->handle);
    if (ret == RETCODE_FRAME_NOT_COMPLETE) {
        VPU_DecGetOutputInfo(dec->handle, &outinfo);
        ret = VPU_DecClose(dec->handle);
        if (ret != RETCODE_SUCCESS)
            err_msg("VPU_DecClose failed\n");
    }
}

void decoder_frame_display(void)
{
    int32_t i = 0;
    struct frame_buf *display_buffer = NULL;
    uint32_t id;

    uint32_t proc_buffer, disp_buffer;

    for (i = 0; i < MAX_NUM_INSTANCE; i++) {
        if (g_vpu_hw_map->codecInstPool[i].inUse && g_vpu_hw_map->codecInstPool[i].initDone) {
            if (dec_fifo_pop(&g_dec_fifo[i], &display_buffer, &id) != -1) {
                g_buf_switch_index[i] = (g_buf_switch_index[i] + 1) % 2;
                VPU_DecClrDispFlag(g_dec_instance[i]->handle, g_disp_clr_index[i]);
                g_disp_clr_index[i] = id;

                if (g_dec_instance[i]->codecctrl->mapType != LINEAR_FRAME_MAP) {
                    if (i % 2 == 0) {
                        if (g_buf_switch_index[i] % 2) {
                            proc_buffer = IPU1_CH23_EBA0;
                            disp_buffer = IPU1_CH23_EBA0;
                        } else {
                            proc_buffer = IPU1_CH23_EBA1;
                            disp_buffer = IPU1_CH23_EBA1;
                        }
                    } else {
                        if (g_buf_switch_index[i] % 2) {
                            proc_buffer = IPU2_CH23_EBA0;
                            disp_buffer = IPU2_CH23_EBA0;
                        } else {
                            proc_buffer = IPU2_CH23_EBA1;
                            disp_buffer = IPU2_CH23_EBA1;
                        }
                    }
                    if (g_dec_instance[i]->codecctrl->mapType == TILED_FRAME_MB_RASTER_MAP) {
                        vdoa_clear_interrupt();
                        vdoa_setup(g_dec_instance[i]->picwidth, g_dec_instance[i]->picheight,
                                   g_dec_instance[i]->stride, FRAME_MAX_WIDTH, 0, 0, 16, 0);
                        vdoa_start(display_buffer->addrY & 0xFFFFF000,
                                   g_dec_instance[i]->picwidth * g_dec_instance[i]->picheight,
                                   proc_buffer, FRAME_MAX_WIDTH * FRAME_MAX_HEIGHT);
                        while (!vdoa_check_tx_eot()) ;
                        vdoa_clear_interrupt();
                    } else {    /*for tiled field mode */

                        int top_field = 0, bot_field = 0;

                        top_field = display_buffer->addrY & 0xFFFFF000;
                        bot_field = (display_buffer->addrCb & 0x00FFFFF0) << 8;
                        vdoa_setup(g_dec_instance[i]->orig_picwidth,
                                   g_dec_instance[i]->orig_picheight / 2, g_dec_instance[i]->stride,
                                   FRAME_MAX_WIDTH * 2, 1, 0, 8, 0);
                        vdoa_start(top_field & 0xFFFFF000,
                                   g_dec_instance[i]->picwidth * g_dec_instance[i]->picheight / 2,
                                   proc_buffer, FRAME_MAX_WIDTH * FRAME_MAX_HEIGHT);
                        while (!vdoa_check_tx_eot()) ;
                        vdoa_clear_interrupt();

                        vdoa_setup(g_dec_instance[i]->orig_picwidth,
                                   g_dec_instance[i]->orig_picheight / 2, g_dec_instance[i]->stride,
                                   FRAME_MAX_WIDTH * 2, 1, 0, 8, 0);
                        vdoa_start(bot_field & 0xFFFFF000,
                                   g_dec_instance[i]->picwidth * g_dec_instance[i]->picheight / 2,
                                   proc_buffer + g_dec_instance[i]->stride,
                                   FRAME_MAX_WIDTH * FRAME_MAX_HEIGHT);
                        while (!vdoa_check_tx_eot()) ;
                        vdoa_clear_interrupt();

                    }
                    ipu_render_refresh(i % 2 + 1, disp_buffer); // totally support two instance, inst0 on ipu1, inst2 on ipu2
                } else {
                    ipu_render_refresh(i % 2 + 1, display_buffer->addrY);   // totally support two instance, inst0 on ipu1, inst2 on ipu2
                }
            } else {
                g_is_frame_drop[i]++;   // time stamp reached but no frame available to display
            }
        }
    }
}

int counter = 0;
static uint32_t epit_instance = HW_EPIT2;

void epit_isr_frame_control(void)
{
    epit_get_compare_event(epit_instance);

    decoder_frame_display();
}

int32_t decoder_setup(void *arg)
{
    struct codec_control *codecctrl;
    vpu_mem_desc mem_desc = { 0 };
    vpu_mem_desc ps_mem_desc = { 0 };
    vpu_mem_desc slice_mem_desc = { 0 };
    struct decode *dec;
    int32_t ret, fillsize = 0;

    codecctrl = (struct codec_control *)arg;

    dec = (struct decode *)calloc(1, sizeof(struct decode));
    if (dec == NULL) {
        err_msg("Failed to allocate decode structure\n");
        return -1;
    }

    /*get bitstream buffer for the video clip */
    mem_desc.size = STREAM_BUF_SIZE;
    ret = vpu_malloc(&mem_desc);
    if (ret) {
        err_msg("Unable to obtain physical mem\n");
        return -1;
    }

    /*in OS the phy and virt address could be different */
    dec->phy_bsbuf_addr = mem_desc.phy_addr;
    dec->virt_bsbuf_addr = mem_desc.virt_addr;
    dec->reorderEnable = 1;
    dec->tiled2LinearEnable = 0;
    dec->mbInfo.enable = 0;
    dec->mvInfo.enable = 0;
    dec->frameBufStat.enable = 0;
    dec->userData.enable = 0;
    dec->totalFrameDecoded = 0;
    dec->codecctrl = codecctrl;

    /*get PS save memory for AVC decoder */
    if (codecctrl->format == STD_AVC) {
        ps_mem_desc.size = PS_SAVE_SIZE;
        ret = vpu_malloc(&ps_mem_desc);
        if (ret) {
            err_msg("Unable to obtain physical ps save mem\n");
            goto err;
        }
        dec->phy_ps_buf = ps_mem_desc.phy_addr;
    }

    /* open decoder */
    ret = decoder_open(dec);
    if (ret)
        goto err;

    /*attach to the global decoder instance */
    g_dec_instance[dec->handle->instIndex] = dec;
    g_bs_buffer[dec->handle->instIndex] = dec->phy_bsbuf_addr;

    ret = dec_fill_bsbuffer(dec->handle, codecctrl,
                            dec->virt_bsbuf_addr,
                            (dec->virt_bsbuf_addr + STREAM_BUF_SIZE),
                            dec->phy_bsbuf_addr, fillsize);
    card_wait_xfer_done(SD_PORT_INDEX);

    if (ret < 0) {
        err_msg("dec_fill_bsbuffer failed\n");
        goto err1;
    }

    /* parse the bitstream */
    ret = decoder_parse(dec);
    if (ret) {
        err_msg("decoder parse failed\n");
        goto err1;
    }

    /* allocate slice buf */
    if (codecctrl->format == STD_AVC) {
        slice_mem_desc.size = dec->phy_slicebuf_size;
        ret = vpu_malloc(&slice_mem_desc);
        if (ret) {
            err_msg("Unable to obtain physical slice save mem\n");
            goto err1;
        }

        dec->phy_slice_buf = slice_mem_desc.phy_addr;
    }

    /* allocate frame buffers */
    ret = decoder_allocate_framebuffer(dec);
    if (ret)
        goto err1;

    /* start decoding */
    ret = decoder_start(dec);
    if (!ret)
        return ret;

  err1:
    decoder_close(dec);

    /* free the frame buffers */
    decoder_free_framebuffer(dec);
  err:
    free(dec);
    return ret;
}

int32_t decode_test(void *arg)
{
    int32_t err, i, temp = 0;
    int32_t primary_disp = 0;
    uint8_t revchar = (uint8_t) 0xFF;
    DecOutputInfo outinfo;
    DecParam decparam = { 0 };
    int32_t bs_read_mode = 0;
    int32_t active_inst_num = 0;
    int32_t map_type = LINEAR_FRAME_MAP;
    int32_t vplay_mode = VPLAY_30FPS;
    struct codec_control *codecctrl;
    int32_t file_in_1 = 0, file_in_2 = 0;
    uint8_t g_dec_file_1[] = "clip_1.264";
    uint8_t g_dec_file_2[] = "clip_2.264";
    int32_t epit_freq = 0;

    while (i < MAX_NUM_INSTANCE) {
        g_is_frame_drop[i] = 0; //initialize the frame drop flag
        g_buf_switch_index[i] = 0;  //initialize the buffer switch index
        i++;
    }

#if defined(CHIP_MX6DQ)
    printf("please select decoder instance:(1 or 2)\n");
    printf("\t1 - Single decoder with single display\n");
    printf
        ("\t2 - Dual decoder with display 1 on Hannstar LVDS panel, display 2 on HDMI Monotor/TV.\n");
    revchar = 0xFF;
    do {
        revchar = getchar();
    } while (revchar == (uint8_t) 0xFF);
#else
    revchar = '1';
#endif

    switch (revchar) {
    case '1':
        g_multi_instance = 0;
        if ((file_in_1 = Fopen(g_dec_file_1, (uint8_t *) "r")) < 0) {
            printf("Can't open the file: %s !\n", g_dec_file_1);
            err = 1;
        }
        printf("please choose the display device: (1 for Hannstar LVDS panel, or 2 for HDMI)\n");
        revchar = 0xFF;
        do {
            revchar = getchar();
        } while (revchar == (uint8_t) 0xFF);
        if (revchar == '1') {
            primary_disp = 1;
        } else {
            primary_disp = 2;
        }
        break;
    case '2':
        g_multi_instance = 1;
        if ((file_in_1 = Fopen(g_dec_file_1, (uint8_t *) "r")) < 0) {
            printf("Can't open the file: %s !\n", g_dec_file_1);
            err = 1;
        }
        if ((file_in_2 = Fopen(g_dec_file_2, (uint8_t *) "r")) < 0) {
            printf("Can't open the file: %s !\n", g_dec_file_2);
            err = 1;
        }
        primary_disp = 1;
        break;
    default:
        printf("Wrong Input! select 1 as default!\n");
        g_multi_instance = 0;
        if ((file_in_1 = Fopen(g_dec_file_1, (uint8_t *) "r")) < 0) {
            printf("Can't open the file: %s !\n", g_dec_file_1);
            err = 1;
        }
    }
    if (err == 1) {
        printf("Problem to open specified media files the fat32 system!!\n");
        return 0;
    }
    printf("please select decoder instance:(1 or 2)\n");
    printf("\t1 - endless decode test.\n");
    printf("\t2 - decode to the file end.\n");
    revchar = 0xFF;
    do {
        revchar = getchar();
    } while (revchar == (uint8_t) 0xFF);

    switch (revchar) {
    case '1':
        bs_read_mode = ENDLESS_LOOP_PLAY;
        break;
    case '2':
    default:
        bs_read_mode = VIDEO_FILE_PLAY;
        break;
    }
    printf("Enable VDOA?(y or n)\n");
    revchar = 0xFF;
    do {
        revchar = getchar();
    } while (revchar == (uint8_t) 0xFF);

    if ((revchar == 'Y') || (revchar == 'y')) {
        map_type = TILED_FRAME_MB_RASTER_MAP;
        //map_type = TILED_FIELD_MB_RASTER_MAP;
        memset((void *)IPU1_CH23_EBA0, 0x10, FRAME_MAX_WIDTH * FRAME_MAX_HEIGHT);
        memset((void *)IPU1_CH23_EBA0 + FRAME_MAX_WIDTH * FRAME_MAX_HEIGHT, 0x80,
               FRAME_MAX_WIDTH * FRAME_MAX_HEIGHT / 2);
        memset((void *)IPU1_CH23_EBA1, 0x10, FRAME_MAX_WIDTH * FRAME_MAX_HEIGHT);
        memset((void *)IPU1_CH23_EBA1 + FRAME_MAX_WIDTH * FRAME_MAX_HEIGHT, 0x80,
               FRAME_MAX_WIDTH * FRAME_MAX_HEIGHT / 2);
        memset((void *)IPU2_CH23_EBA0, 0x10, FRAME_MAX_WIDTH * FRAME_MAX_HEIGHT);
        memset((void *)IPU2_CH23_EBA0 + FRAME_MAX_WIDTH * FRAME_MAX_HEIGHT, 0x80,
               FRAME_MAX_WIDTH * FRAME_MAX_HEIGHT / 2);
        memset((void *)IPU2_CH23_EBA1, 0x10, FRAME_MAX_WIDTH * FRAME_MAX_HEIGHT);
        memset((void *)IPU2_CH23_EBA1 + FRAME_MAX_WIDTH * FRAME_MAX_HEIGHT, 0x80,
               FRAME_MAX_WIDTH * FRAME_MAX_HEIGHT / 2);
    } else {
        map_type = LINEAR_FRAME_MAP;
    }
    /*now enable the INTERRUPT mode of usdhc */
    set_card_access_mode(1, 1);

    /* initialize video streams and configure IPUs */
    if (primary_disp == 1)
        ips_hannstar_xga_yuv_stream(1);
    else {
#ifdef HDMI_RESOLUTION_1080P60
        hdmi_1080P60_video_output(1, 0);
#else
        hdmi_720P60_video_output(1, 0);
#endif
    }
    codecctrl = (struct codec_control *)calloc(1, sizeof(struct codec_control));
    if (codecctrl == NULL) {
        err_msg("Failed to allocate command structure\n");
        return -1;
    }
    /*set the decoder command args */
    codecctrl->input = file_in_1;   /* Input file name */
    codecctrl->format = STD_AVC;
    codecctrl->src_scheme = PATH_FILE;
    codecctrl->dst_scheme = PATH_MEM;
    codecctrl->dering_en = 0;
    codecctrl->deblock_en = 0;
    codecctrl->chromaInterleave = 1;    //partial interleaved mode
    codecctrl->mapType = map_type;
    codecctrl->bs_mode = 0;     /*disable pre-scan */
    codecctrl->read_mode = bs_read_mode;
    codecctrl->fps = 30;
    active_inst_num++;
    decoder_setup((void *)codecctrl);

    if (g_multi_instance) {
#ifdef HDMI_RESOLUTION_1080P60
        hdmi_1080P60_video_output(2, 0);
#else
        hdmi_720P60_video_output(2, 0);
#endif
        codecctrl = (struct codec_control *)calloc(1, sizeof(struct codec_control));
        if (codecctrl == NULL) {
            err_msg("Failed to allocate command structure\n");
            return -1;
        }
        /*set the decoder command args */
        codecctrl->input = file_in_2;   /* Input file name */
        codecctrl->format = STD_AVC;
        codecctrl->src_scheme = PATH_FILE;
        codecctrl->dst_scheme = PATH_MEM;
        codecctrl->dering_en = 0;
        codecctrl->deblock_en = 0;
        codecctrl->chromaInterleave = 1;    //partial interleaved mode
        codecctrl->mapType = map_type;
        codecctrl->bs_mode = 0; /*disable pre-scan */
        codecctrl->read_mode = bs_read_mode;
        codecctrl->fps = 30;
        active_inst_num++;
        decoder_setup((void *)codecctrl);

    }

    printf("Now start decoding test ... \n");

    if (vplay_mode != VPLAY_FREE_RUN) { /*Frame control used */
        epit_freq = get_main_clock(IPG_CLK);
        epit_init(epit_instance, CLKSRC_IPG_CLK, epit_freq / 1000000, SET_AND_FORGET, 0, 0);
        epit_setup_interrupt(epit_instance, epit_isr_frame_control, TRUE);
        epit_counter_enable(epit_instance, 1000000 / vplay_mode, IRQ_MODE);
    }

    while (1) {
        static int32_t inst = 0;
        if (active_inst_num == 0)
            break;
        /*get the next active instance */
        for (i = 1; i <= MAX_NUM_INSTANCE; i++) {
            temp = (inst + i) % MAX_NUM_INSTANCE;
            if (g_vpu_hw_map->codecInstPool[temp].inUse
                && g_vpu_hw_map->codecInstPool[temp].initDone) {
                inst = temp;
                break;
            }
        }
        decparam.dispReorderBuf = 0;

        decparam.prescanEnable = g_dec_instance[inst]->codecctrl->prescan;
        decparam.prescanMode = 0;

        decparam.skipframeMode = 0;
        decparam.skipframeNum = 0;
        decparam.iframeSearchEnable = 0;

        if (!VPU_IsBusy() && !dec_fifo_is_full(&g_dec_fifo[inst]) &&
            (VPU_DecBufferCheck(g_dec_instance[inst]->handle) == RETCODE_SUCCESS)) {
            VPU_DecStartOneFrame(g_dec_instance[inst]->handle, &decparam);
            while (VPU_IsBusy()) {
                /*If there is enough space, read the bitstream from the SD card to the bitstream buffer */
                err =
                    dec_fill_bsbuffer(g_dec_instance[inst]->handle, g_dec_instance[inst]->codecctrl,
                                      g_bs_buffer[inst], g_bs_buffer[inst] + STREAM_BUF_SIZE,
                                      g_bs_buffer[inst], STREAM_BUF_SIZE >> 2);
            };

            VPU_DecGetOutputInfo(g_dec_instance[inst]->handle, &outinfo);

            if (outinfo.indexFrameDisplay >= 0) {
                g_dec_instance[inst]->totalFrameDecoded++;

                /*push the decoded frame into fifo */
                dec_fifo_push(&g_dec_fifo[inst],
                              &(g_dec_instance[inst]->pfbpool[outinfo.indexFrameDisplay]),
                              outinfo.indexFrameDisplay);
            } else if (outinfo.indexFrameDisplay == -1) {
                g_vpu_hw_map->codecInstPool[inst].inUse = 0;
                info_msg("Decode instance %d finished!\n", inst);
                active_inst_num--;
            }
        }

        if (vplay_mode == VPLAY_FREE_RUN) {
            decoder_frame_display();
        } else if (g_is_frame_drop[inst]) {
            decoder_frame_display();
            g_is_frame_drop[inst]--;
        }
    }

    /*release all the buffers */
    for (i = 0; i < MAX_NUM_INSTANCE; i++) {
        if (g_vpu_hw_map->codecInstPool[i].initDone) {
            printf("Total frames decoded in instance %d is %d\n", i,
                   g_dec_instance[i]->totalFrameDecoded);
            decoder_close(g_dec_instance[i]);

            /* free the frame buffers */
            decoder_free_framebuffer(g_dec_instance[i]);

            free(g_dec_instance[i]->codecctrl);
            free(g_dec_instance[i]->fb);
            free(g_dec_instance[i]->pfbpool);
            g_dec_instance[i]->fb = NULL;
            g_dec_instance[i]->pfbpool = NULL;
            free(g_dec_instance[i]);

            g_disp_clr_index[i] = -1;
            g_vpu_hw_map->codecInstPool[i].initDone = 0;
        }
    }

    if (file_in_1 != 0)
        Fclose(file_in_1);
    if (file_in_2 != 0)
        Fclose(file_in_2);

    if (vplay_mode != VPLAY_FREE_RUN) { /*disable the timer for frame control */
        epit_counter_disable(epit_instance);
    }

    return 0;
}
