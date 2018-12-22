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

/*
 * Copyright (c) 2006, Chips & Media.  All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sdk.h"
#include "vpu/vpu_util.h"
#include "vpu/vpu_io.h"
#include "vpu/vpu_debug.h"
#include "BitAsmTable_CODA_960.h"

////////////////////////////////////////////////////////////////////////////////
// DEFINITIONS
////////////////////////////////////////////////////////////////////////////////

#define MAX_VSIZE       8192
#define MAX_HSIZE       8192

enum {
    SAMPLE_420 = 0xA,
    SAMPLE_H422 = 0x9,
    SAMPLE_V422 = 0x6,
    SAMPLE_444 = 0x5,
    SAMPLE_400 = 0x1
};

/*
 * VPU binary file header format:
 * 12-byte: platform version, eg, MX27, MX37, and so on.
 * 4-byte:  element numbers, each element is 16bit(unsigned short)
 */
typedef struct {
    uint8_t platform[12];
    uint32_t size;
} headerInfo;

////////////////////////////////////////////////////////////////////////////////
// VARIABLES
////////////////////////////////////////////////////////////////////////////////

extern uint32_t *virt_paraBuf;
vpu_resource_t *g_vpu_hw_map;

////////////////////////////////////////////////////////////////////////////////
// CODE
////////////////////////////////////////////////////////////////////////////////

RetCode DownloadBitCodeTable(uint32_t * virtCodeBuf)
{
    int i, size;
    volatile uint32_t data;
    uint32_t *virt_codeBuf = NULL;

    if (virtCodeBuf == NULL || bit_code == NULL) {
        err_msg("Failed to allocate bit_code\n");
        return RETCODE_FAILURE;
    }

    virt_codeBuf = virtCodeBuf;
    size = sizeof(bit_code) / sizeof(bit_code[0]);
    /* Copy full Microcode to Code Buffer allocated on SDRAM */
    for (i = 0; i < size; i += 4) {
        data = (bit_code[i + 0] << 16) | bit_code[i + 1];
        ((unsigned int *)virt_codeBuf)[i / 2 + 1] = data;
        data = (bit_code[i + 2] << 16) | bit_code[i + 3];
        ((unsigned int *)virt_codeBuf)[i / 2] = data;
    }

    return RETCODE_SUCCESS;
}

/*
 * GetCodecInstance() obtains an instance.
 * It stores a pointer to the allocated instance in *ppInst
 * and returns RETCODE_SUCCESS on success.
 * Failure results in 0(null pointer) in *ppInst and RETCODE_FAILURE.
 */
RetCode GetCodecInstance(CodecInst ** ppInst)
{
    int i;
    CodecInst *pCodecInst;

    for (i = 0; i < MAX_NUM_INSTANCE; ++i) {
        pCodecInst = (CodecInst *) (&g_vpu_hw_map->codecInstPool[i]);
        if (!pCodecInst->inUse)
            break;
    }

    if (i == MAX_NUM_INSTANCE) {
        *ppInst = 0;
        return RETCODE_FAILURE;
    }

    i = pCodecInst->instIndex;
    memset(pCodecInst, 0, sizeof(CodecInst));
    pCodecInst->instIndex = i;
    pCodecInst->inUse = 1;
    *ppInst = pCodecInst;
    return RETCODE_SUCCESS;
}

RetCode CheckInstanceValidity(CodecInst * pci)
{
    CodecInst *pCodecInst;
    int i;

    for (i = 0; i < MAX_NUM_INSTANCE; ++i) {
        pCodecInst = (CodecInst *) (&g_vpu_hw_map->codecInstPool[i]);
        if (pCodecInst == pci)
            return RETCODE_SUCCESS;
    }
    return RETCODE_INVALID_HANDLE;
}

RetCode CheckEncInstanceValidity(EncHandle handle)
{
    CodecInst *pCodecInst;
    RetCode ret;

    pCodecInst = handle;
    ret = CheckInstanceValidity(pCodecInst);
    if (ret != RETCODE_SUCCESS) {
        return RETCODE_INVALID_HANDLE;
    }
    if (!pCodecInst->inUse) {
        return RETCODE_INVALID_HANDLE;
    }

    if (pCodecInst->codecMode != MP4_ENC &&
        pCodecInst->codecMode != AVC_ENC && pCodecInst->codecMode != MJPG_ENC)
        return RETCODE_INVALID_HANDLE;
    return RETCODE_SUCCESS;
}

RetCode CheckDecInstanceValidity(DecHandle handle)
{
    CodecInst *pCodecInst;
    RetCode ret;

    pCodecInst = handle;
    ret = CheckInstanceValidity(pCodecInst);
    if (ret != RETCODE_SUCCESS) {
        return RETCODE_INVALID_HANDLE;
    }
    if (!pCodecInst->inUse) {
        return RETCODE_INVALID_HANDLE;
    }

    if (cpu_is_mx6()) {
        if (pCodecInst->codecMode != MP4_DEC &&
            pCodecInst->codecMode != AVC_DEC &&
            pCodecInst->codecMode != VC1_DEC &&
            pCodecInst->codecMode != MP2_DEC &&
            pCodecInst->codecMode != DV3_DEC &&
            pCodecInst->codecMode != AVS_DEC &&
            pCodecInst->codecMode != RV_DEC &&
            pCodecInst->codecMode != VPX_DEC && pCodecInst->codecMode != MJPG_DEC)
            return RETCODE_INVALID_PARAM;
    } else {
        if (pCodecInst->codecMode != MP4_DEC &&
            pCodecInst->codecMode != AVC_DEC &&
            pCodecInst->codecMode != VC1_DEC &&
            pCodecInst->codecMode != MP2_DEC &&
            pCodecInst->codecMode != DV3_DEC &&
            pCodecInst->codecMode != RV_DEC && pCodecInst->codecMode != MJPG_DEC)
            return RETCODE_INVALID_PARAM;
    }
    return RETCODE_SUCCESS;
}

void FreeCodecInstance(CodecInst * pCodecInst)
{
    pCodecInst->inUse = 0;
}

void BitIssueCommand(CodecInst * pCodecInst, int cmd)
{
    int instIdx = 0, cdcMode = 0, auxMode = 0;

    if (pCodecInst != NULL) {
        /* Save context related registers to vpu */
        vpu_reg_write(BIT_BIT_STREAM_PARAM, pCodecInst->ctxRegs[CTX_BIT_STREAM_PARAM]);
        vpu_reg_write(BIT_FRM_DIS_FLG, pCodecInst->ctxRegs[CTX_BIT_FRM_DIS_FLG]);
        vpu_reg_write(BIT_WR_PTR, pCodecInst->ctxRegs[CTX_BIT_WR_PTR]);
        vpu_reg_write(BIT_RD_PTR, pCodecInst->ctxRegs[CTX_BIT_RD_PTR]);
        vpu_reg_write(BIT_FRAME_MEM_CTRL, pCodecInst->ctxRegs[CTX_BIT_FRAME_MEM_CTRL]);
        vpu_reg_write(BIT_WORK_BUF_ADDR, pCodecInst->contextBufMem.phy_addr);
        instIdx = pCodecInst->instIndex;
        cdcMode = pCodecInst->codecMode;
        auxMode = pCodecInst->codecModeAux;
    }

    vpu_reg_write(BIT_BUSY_FLAG, 0x1);
    vpu_reg_write(BIT_RUN_INDEX, instIdx);
    vpu_reg_write(BIT_RUN_COD_STD, cdcMode);
    vpu_reg_write(BIT_RUN_AUX_STD, auxMode);
    vpu_reg_write(BIT_RUN_COMMAND, cmd);
}

RetCode CheckEncOpenParam(EncOpenParam * pop)
{
    int picWidth;
    int picHeight;

    if (pop == 0) {
        return RETCODE_INVALID_PARAM;
    }
    picWidth = pop->picWidth;
    picHeight = pop->picHeight;
    if (pop->bitstreamBuffer % 4) { /* not 4-bit aligned */
        return RETCODE_INVALID_PARAM;
    }
    if (pop->bitstreamBufferSize % 1024 ||
        pop->bitstreamBufferSize < 1024 || pop->bitstreamBufferSize > 16383 * 1024) {
        return RETCODE_INVALID_PARAM;
    }
    if (pop->bitstreamFormat != STD_MPEG4 &&
        pop->bitstreamFormat != STD_H263 &&
        pop->bitstreamFormat != STD_AVC && pop->bitstreamFormat != STD_MJPG) {
        return RETCODE_INVALID_PARAM;
    }
    if (pop->bitRate > 32767 || pop->bitRate < 0) {
        return RETCODE_INVALID_PARAM;
    }
    if (pop->bitRate != 0 && pop->initialDelay > 32767) {
        return RETCODE_INVALID_PARAM;
    }
    if (pop->bitRate != 0 && pop->initialDelay != 0 && pop->vbvBufferSize < 0) {
        return RETCODE_INVALID_PARAM;
    }
    if (pop->gopSize > 32767) {
        return RETCODE_INVALID_PARAM;
    }
    if (pop->slicemode.sliceMode != 0 && pop->slicemode.sliceMode != 1) {
        return RETCODE_INVALID_PARAM;
    }
    if (pop->slicemode.sliceMode == 1) {
        if (pop->slicemode.sliceSizeMode != 0 && pop->slicemode.sliceSizeMode != 1) {
            return RETCODE_INVALID_PARAM;
        }
        if (pop->slicemode.sliceSize == 0) {
            return RETCODE_INVALID_PARAM;
        }
    }

    if (pop->intraRefresh < 0 || pop->intraRefresh >= (picWidth * picHeight / 256)) {
        return RETCODE_INVALID_PARAM;
    }

    if (pop->bitstreamFormat == STD_MPEG4) {
        EncMp4Param *param = &pop->EncStdParam.mp4Param;
        if (param->mp4_dataPartitionEnable != 0 && param->mp4_dataPartitionEnable != 1) {
            return RETCODE_INVALID_PARAM;
        }
        if (param->mp4_dataPartitionEnable == 1) {
            if (param->mp4_reversibleVlcEnable != 0 && param->mp4_reversibleVlcEnable != 1) {
                return RETCODE_INVALID_PARAM;
            }
        }
        if (param->mp4_intraDcVlcThr < 0 || param->mp4_intraDcVlcThr > 7) {
            return RETCODE_INVALID_PARAM;
        }
    } else if (pop->bitstreamFormat == STD_H263) {
        EncH263Param *param = &pop->EncStdParam.h263Param;
        if (param->h263_annexJEnable != 0 && param->h263_annexJEnable != 1) {
            return RETCODE_INVALID_PARAM;
        }
        if (param->h263_annexKEnable != 0 && param->h263_annexKEnable != 1) {
            return RETCODE_INVALID_PARAM;
        }
        if (param->h263_annexTEnable != 0 && param->h263_annexTEnable != 1) {
            return RETCODE_INVALID_PARAM;
        }
        if (param->h263_annexJEnable == 0 &&
            param->h263_annexKEnable == 0 && param->h263_annexTEnable == 0) {
            if (!(picWidth == 128 && picHeight == 96) &&
                !(picWidth == 176 && picHeight == 144) &&
                !(picWidth == 352 && picHeight == 288) && !(picWidth == 704 && picHeight == 576)) {
                return RETCODE_INVALID_PARAM;
            }
        }
    } else if (pop->bitstreamFormat == STD_AVC) {
        EncAvcParam *param = &pop->EncStdParam.avcParam;
        if (param->avc_constrainedIntraPredFlag != 0 && param->avc_constrainedIntraPredFlag != 1) {
            return RETCODE_INVALID_PARAM;
        }
        if (param->avc_disableDeblk != 0 &&
            param->avc_disableDeblk != 1 && param->avc_disableDeblk != 2) {
            return RETCODE_INVALID_PARAM;
        }
        if (param->avc_deblkFilterOffsetAlpha < -6 || param->avc_deblkFilterOffsetAlpha > 6) {
            return RETCODE_INVALID_PARAM;
        }
        if (param->avc_deblkFilterOffsetBeta < -6 || param->avc_deblkFilterOffsetBeta > 6) {
            return RETCODE_INVALID_PARAM;
        }
        if (param->avc_chromaQpOffset < -12 || param->avc_chromaQpOffset > 12) {
            return RETCODE_INVALID_PARAM;
        }

        if (param->avc_frameCroppingFlag != 0 && param->avc_frameCroppingFlag != 1) {
            return RETCODE_INVALID_PARAM;
        }

        if (param->avc_frameCropLeft & 0x01 ||
            param->avc_frameCropRight & 0x01 ||
            param->avc_frameCropTop & 0x01 || param->avc_frameCropBottom & 0x01) {
            return RETCODE_INVALID_PARAM;
        }

        if (param->avc_audEnable != 0 && param->avc_audEnable != 1) {
            return RETCODE_INVALID_PARAM;
        }
        if (param->avc_fmoEnable != 0 && param->avc_fmoEnable != 1) {
            return RETCODE_INVALID_PARAM;
        }
        if (param->avc_fmoEnable == 1) {
            if (param->avc_fmoType != 0 && param->avc_fmoType != 1) {
                return RETCODE_INVALID_PARAM;
            }
            if (param->avc_fmoSliceNum < 2 || 8 < param->avc_fmoSliceNum) {
                return RETCODE_INVALID_PARAM;
            }
        }
    }

    if (picWidth < 32 || picHeight < 16) {
        return RETCODE_INVALID_PARAM;
    }

    return RETCODE_SUCCESS;
}

RetCode CheckEncParam(CodecInst * pCodecInst, EncParam * param)
{
    if (param == 0) {
        return RETCODE_INVALID_PARAM;
    }
    if (param->skipPicture != 0 && param->skipPicture != 1) {
        return RETCODE_INVALID_PARAM;
    }
    if (param->skipPicture == 0) {
        if (param->sourceFrame == 0) {
            return RETCODE_INVALID_FRAME_BUFFER;
        }
        if (param->forceIPicture != 0 && param->forceIPicture != 1) {
            return RETCODE_INVALID_PARAM;
        }
    }

    /* no rate control */
    if (pCodecInst->CodecInfo.encInfo.openParam.bitRate == 0) {
        if (pCodecInst->codecMode == MP4_ENC) {
            if (param->quantParam < 1 || param->quantParam > 31) {
                return RETCODE_INVALID_PARAM;
            }
        } else {                /* AVC_ENC */
            if (param->quantParam < 0 || param->quantParam > 51) {
                return RETCODE_INVALID_PARAM;
            }
        }
    }
    return RETCODE_SUCCESS;
}

void EncodeHeader(EncHandle handle, EncHeaderParam * encHeaderParam)
{
    CodecInst *pCodecInst;
    EncInfo *pEncInfo;
    PhysicalAddress rdPtr;
    PhysicalAddress wrPtr;
    int data = 0, frameCroppingFlag = 0;

    pCodecInst = handle;
    pEncInfo = &pCodecInst->CodecInfo.encInfo;

    if (cpu_is_mx6() && (pEncInfo->ringBufferEnable == 0)) {
        vpu_reg_write(CMD_ENC_HEADER_BB_START, pEncInfo->streamBufStartAddr);
        vpu_reg_write(CMD_ENC_HEADER_BB_SIZE, pEncInfo->streamBufSize / 1024);
    } else if (!cpu_is_mx6() && (pEncInfo->dynamicAllocEnable == 1)) {
        vpu_reg_write(CMD_ENC_HEADER_BB_START, encHeaderParam->buf);
        vpu_reg_write(CMD_ENC_HEADER_BB_SIZE, encHeaderParam->size);
    }

    if (cpu_is_mx6() && (encHeaderParam->headerType == 0) &&
        (pEncInfo->openParam.bitstreamFormat == STD_AVC)) {
        EncOpenParam *encOP;
        uint32_t CropV, CropH;

        encOP = &(pEncInfo->openParam);
        if (encOP->EncStdParam.avcParam.avc_frameCroppingFlag == 1) {
            frameCroppingFlag = 1;
            CropH = encOP->EncStdParam.avcParam.avc_frameCropLeft << 16;
            CropH |= encOP->EncStdParam.avcParam.avc_frameCropRight;
            CropV = encOP->EncStdParam.avcParam.avc_frameCropTop << 16;
            CropV |= encOP->EncStdParam.avcParam.avc_frameCropBottom;
            vpu_reg_write(CMD_ENC_HEADER_FRAME_CROP_H, CropH);
            vpu_reg_write(CMD_ENC_HEADER_FRAME_CROP_V, CropV);
        }
    }

    if (cpu_is_mx6()) {
        vpu_reg_write(CMD_ENC_HEADER_CODE, encHeaderParam->headerType | frameCroppingFlag << 2);
    } else {
        if (encHeaderParam->headerType == VOS_HEADER || encHeaderParam->headerType == SPS_RBSP) {
            data = (((encHeaderParam->userProfileLevelIndication & 0xFF) << 8) |
                    ((encHeaderParam->userProfileLevelEnable & 0x01) << 4) |
                    (encHeaderParam->headerType & 0x0F));
            vpu_reg_write(CMD_ENC_HEADER_CODE, data);
        } else {
            vpu_reg_write(CMD_ENC_HEADER_CODE, encHeaderParam->headerType); /* 0: SPS, 1: PPS */
        }
    }

    BitIssueCommand(pCodecInst, ENCODE_HEADER);
    while (vpu_reg_read(BIT_BUSY_FLAG)) ;

    if ((cpu_is_mx6() && (pEncInfo->ringBufferEnable == 0)) ||
        (!cpu_is_mx6() && (pEncInfo->dynamicAllocEnable == 1))) {
        rdPtr = vpu_reg_read(CMD_ENC_HEADER_BB_START);
        wrPtr = vpu_reg_read(BIT_WR_PTR);
        pCodecInst->ctxRegs[CTX_BIT_WR_PTR] = wrPtr;
    } else {
        rdPtr = vpu_reg_read(BIT_RD_PTR);
        wrPtr = vpu_reg_read(BIT_WR_PTR);
        pCodecInst->ctxRegs[CTX_BIT_WR_PTR] = wrPtr;
    }

    encHeaderParam->buf = rdPtr;
    encHeaderParam->size = wrPtr - rdPtr;
}

RetCode CheckDecOpenParam(DecOpenParam * pop)
{
    if (pop == 0) {
        return RETCODE_INVALID_PARAM;
    }
    if (pop->bitstreamBuffer % 4) { /* not 4-bit aligned */
        return RETCODE_INVALID_PARAM;
    }

    if (cpu_is_mx6() & (pop->bitstreamFormat == STD_MJPG)) {
        if (!pop->jpgLineBufferMode) {
            if (pop->bitstreamBufferSize % 1024 || pop->bitstreamBufferSize < 1024)
                return RETCODE_INVALID_PARAM;
        }
    } else if (pop->bitstreamBufferSize % 1024 ||
               pop->bitstreamBufferSize < 1024 || pop->bitstreamBufferSize > 16383 * 1024) {
        return RETCODE_INVALID_PARAM;
    }

    /* Workaround for STD_H263 support: Force to convert STD_H263
       to STD_MPEG4 since VPU treats all H263 as MPEG4 in decoder */
    if (pop->bitstreamFormat == STD_H263)
        pop->bitstreamFormat = STD_MPEG4;

    if (cpu_is_mx6()) {
        if (pop->bitstreamFormat != STD_MPEG4 &&
            pop->bitstreamFormat != STD_AVC &&
            pop->bitstreamFormat != STD_VC1 &&
            pop->bitstreamFormat != STD_MPEG2 &&
            pop->bitstreamFormat != STD_DIV3 &&
            pop->bitstreamFormat != STD_RV &&
            pop->bitstreamFormat != STD_AVS &&
            pop->bitstreamFormat != STD_VP8 && pop->bitstreamFormat != STD_MJPG)
            return RETCODE_INVALID_PARAM;
    } else {
        if (pop->bitstreamFormat != STD_MPEG4 &&
            pop->bitstreamFormat != STD_AVC &&
            pop->bitstreamFormat != STD_VC1 &&
            pop->bitstreamFormat != STD_MPEG2 &&
            pop->bitstreamFormat != STD_DIV3 &&
            pop->bitstreamFormat != STD_RV && pop->bitstreamFormat != STD_MJPG)
            return RETCODE_INVALID_PARAM;
    }

    if (pop->mp4DeblkEnable == 1 && !(pop->bitstreamFormat ==
                                      STD_MPEG4
                                      || pop->bitstreamFormat ==
                                      STD_MPEG2 || pop->bitstreamFormat == STD_DIV3)) {
        return RETCODE_INVALID_PARAM;
    }
    return RETCODE_SUCCESS;
}

int DecBitstreamBufEmpty(DecHandle handle)
{
    CodecInst *pCodecInst;
    PhysicalAddress rdPtr;
    PhysicalAddress wrPtr;
    int instIndex;

    pCodecInst = handle;

    instIndex = vpu_reg_read(BIT_RUN_INDEX);

    rdPtr = (pCodecInst->instIndex == instIndex) ?
        vpu_reg_read(BIT_RD_PTR) : pCodecInst->ctxRegs[CTX_BIT_RD_PTR];
    wrPtr = (pCodecInst->instIndex == instIndex) ?
        vpu_reg_read(BIT_WR_PTR) : pCodecInst->ctxRegs[CTX_BIT_WR_PTR];

    return rdPtr == wrPtr;
}

RetCode CopyBufferData(uint8_t * dst, uint8_t * src, int size)
{
    uint32_t temp;

    if (!dst || !src || !size)
        return RETCODE_FAILURE;

    int i;
    for (i = 0; i < size / 8; i++) {
        /* swab odd and even words and swab32 */
        temp = *((uint32_t *) src + i * 2 + 1);
        *((uint32_t *) dst + i * 2) = swab32(temp);
        temp = *((uint32_t *) src + i * 2);
        *((uint32_t *) dst + i * 2 + 1) = swab32(temp);
    }
    return RETCODE_SUCCESS;
}

void GetParaSet(EncHandle handle, int paraSetType, EncParamSet * para)
{
    CodecInst *pCodecInst;
    EncInfo *pEncInfo;
    int frameCroppingFlag = 0;

    pCodecInst = handle;
    pEncInfo = &pCodecInst->CodecInfo.encInfo;

    if (cpu_is_mx6() && (paraSetType == 0) && (pEncInfo->openParam.bitstreamFormat == STD_AVC)) {
        EncOpenParam *encOP;
        uint32_t CropV, CropH;

        encOP = &(pEncInfo->openParam);
        if (encOP->EncStdParam.avcParam.avc_frameCroppingFlag == 1) {
            frameCroppingFlag = 1;
            CropH = encOP->EncStdParam.avcParam.avc_frameCropLeft << 16;
            CropH |= encOP->EncStdParam.avcParam.avc_frameCropRight;
            CropV = encOP->EncStdParam.avcParam.avc_frameCropTop << 16;
            CropV |= encOP->EncStdParam.avcParam.avc_frameCropBottom;
            vpu_reg_write(CMD_ENC_HEADER_FRAME_CROP_H, CropH);
            vpu_reg_write(CMD_ENC_HEADER_FRAME_CROP_V, CropV);
        }
    }

    /* SPS: 0, PPS: 1, VOS: 1, VO: 2, VOL: 0 */
    vpu_reg_write(CMD_ENC_PARA_SET_TYPE, paraSetType | (frameCroppingFlag << 2));
    BitIssueCommand(pCodecInst, ENC_PARA_SET);
    while (vpu_reg_read(BIT_BUSY_FLAG)) ;

    para->paraSet = virt_paraBuf;
    para->size = vpu_reg_read(RET_ENC_PARA_SET_SIZE);

}

void SetParaSet(DecHandle handle, int paraSetType, DecParamSet * para)
{
    CodecInst *pCodecInst;
    int i;
    uint32_t *src;
    int byteSize;

    pCodecInst = handle;

    src = para->paraSet;
    byteSize = para->size / 4;

    for (i = 0; i < byteSize; i += 1) {
        virt_paraBuf[i] = *src++;
    }

    vpu_reg_write(CMD_DEC_PARA_SET_TYPE, paraSetType);
    vpu_reg_write(CMD_DEC_PARA_SET_SIZE, para->size);

    BitIssueCommand(pCodecInst, DEC_PARA_SET);
    while (vpu_reg_read(BIT_BUSY_FLAG)) ;

}

/* Following are not for MX27 TO1 */
RetCode SetGopNumber(EncHandle handle, uint32_t * pGopNumber)
{
    CodecInst *pCodecInst;
    int data = 0;
    uint32_t gopNumber = *pGopNumber;

    pCodecInst = handle;
    data = 1;
    vpu_reg_write(CMD_ENC_SEQ_PARA_CHANGE_ENABLE, data);
    vpu_reg_write(CMD_ENC_SEQ_PARA_RC_GOP, gopNumber);
    BitIssueCommand(pCodecInst, RC_CHANGE_PARAMETER);
    while (vpu_reg_read(BIT_BUSY_FLAG)) ;

    return RETCODE_SUCCESS;
}

RetCode SetIntraQp(EncHandle handle, uint32_t * pIntraQp)
{
    CodecInst *pCodecInst;
    int data = 0;
    uint32_t intraQp = *pIntraQp;

    pCodecInst = handle;
    data = 1 << 1;
    vpu_reg_write(CMD_ENC_SEQ_PARA_CHANGE_ENABLE, data);
    vpu_reg_write(CMD_ENC_SEQ_PARA_RC_INTRA_QP, intraQp);
    BitIssueCommand(pCodecInst, RC_CHANGE_PARAMETER);
    while (vpu_reg_read(BIT_BUSY_FLAG)) ;

    return RETCODE_SUCCESS;
}

RetCode SetBitrate(EncHandle handle, uint32_t * pBitrate)
{
    CodecInst *pCodecInst;
    int data = 0;
    uint32_t bitrate = *pBitrate;

    pCodecInst = handle;
    data = 1 << 2;
    vpu_reg_write(CMD_ENC_SEQ_PARA_CHANGE_ENABLE, data);
    vpu_reg_write(CMD_ENC_SEQ_PARA_RC_BITRATE, bitrate);
    BitIssueCommand(pCodecInst, RC_CHANGE_PARAMETER);
    while (vpu_reg_read(BIT_BUSY_FLAG)) ;

    return RETCODE_SUCCESS;
}

RetCode SetFramerate(EncHandle handle, uint32_t * pFramerate)
{
    CodecInst *pCodecInst;
    int data = 0;
    uint32_t framerate = *pFramerate;

    pCodecInst = handle;
    data = 1 << 3;
    vpu_reg_write(CMD_ENC_SEQ_PARA_CHANGE_ENABLE, data);
    vpu_reg_write(CMD_ENC_SEQ_PARA_RC_FRAME_RATE, framerate);
    BitIssueCommand(pCodecInst, RC_CHANGE_PARAMETER);
    while (vpu_reg_read(BIT_BUSY_FLAG)) ;

    return RETCODE_SUCCESS;
}

RetCode SetIntraRefreshNum(EncHandle handle, uint32_t * pIntraRefreshNum)
{
    CodecInst *pCodecInst;
    uint32_t intraRefreshNum = *pIntraRefreshNum;
    int data = 0;

    pCodecInst = handle;
    data = 1 << 4;
    vpu_reg_write(CMD_ENC_SEQ_PARA_CHANGE_ENABLE, data);
    vpu_reg_write(CMD_ENC_SEQ_PARA_INTRA_MB_NUM, intraRefreshNum);
    BitIssueCommand(pCodecInst, RC_CHANGE_PARAMETER);
    while (vpu_reg_read(BIT_BUSY_FLAG)) ;

    return RETCODE_SUCCESS;
}

RetCode SetSliceMode(EncHandle handle, EncSliceMode * pSliceMode)
{
    CodecInst *pCodecInst;
    uint32_t data = 0;
    int data2 = 0;

    data = pSliceMode->sliceSize << 2 | pSliceMode->sliceSizeMode << 1 | pSliceMode->sliceMode;
    pCodecInst = handle;

    data2 = 1 << 5;
    vpu_reg_write(CMD_ENC_SEQ_PARA_CHANGE_ENABLE, data2);
    vpu_reg_write(CMD_ENC_SEQ_PARA_SLICE_MODE, data);
    BitIssueCommand(pCodecInst, RC_CHANGE_PARAMETER);
    while (vpu_reg_read(BIT_BUSY_FLAG)) ;

    return RETCODE_SUCCESS;
}

RetCode SetHecMode(EncHandle handle, int mode)
{
    CodecInst *pCodecInst;
    uint32_t HecMode = mode;
    int data = 0;
    pCodecInst = handle;

    data = 1 << 6;
    vpu_reg_write(CMD_ENC_SEQ_PARA_CHANGE_ENABLE, data);
    vpu_reg_write(CMD_ENC_SEQ_PARA_HEC_MODE, HecMode);
    BitIssueCommand(pCodecInst, RC_CHANGE_PARAMETER);
    while (vpu_reg_read(BIT_BUSY_FLAG)) ;

    return RETCODE_SUCCESS;
}

void SetDecSecondAXIIRAM(SecAxiUse * psecAxiIramInfo, SetIramParam * parm)
{
    iram_t iram;
    iram.start = VPU_SEC_AXI_START;
    iram.end = VPU_SEC_AXI_END;
    int size, dbk_size, bitram_size, ipacdc_size, ovl_size, btp_size;
    int mbNumX, mbNumY;

    if (!parm->width) {
        err_msg("Width is zero when calling SetDecSecondAXIIRAM function\n");
        return;
    }

    memset(psecAxiIramInfo, 0, sizeof(SecAxiUse));

    size = iram.end - iram.start + 1;

    mbNumX = (parm->width + 15) / 16;
    mbNumY = (parm->height + 15) / 16;

    /* Setting internal iram usage per priority when iram isn't enough */
    if ((parm->codecMode == VC1_DEC) && (parm->profile == 2))
        dbk_size = (512 * mbNumX + 1023) & ~1023;
    else
        dbk_size = (256 * mbNumX + 1023) & ~1023;

    if (size >= dbk_size) {
        psecAxiIramInfo->useHostDbkEnable = 1;
        psecAxiIramInfo->bufDbkYUse = iram.start;
        psecAxiIramInfo->bufDbkCUse = iram.start + dbk_size / 2;
        size -= dbk_size;
    } else
        goto out;

    bitram_size = (128 * mbNumX + 1023) & ~1023;
    if (size >= bitram_size) {
        psecAxiIramInfo->useHostBitEnable = 1;
        psecAxiIramInfo->bufBitUse = psecAxiIramInfo->bufDbkCUse + dbk_size / 2;
        size -= bitram_size;
    } else
        goto out;

    ipacdc_size = (128 * mbNumX + 1023) & ~1023;
    if (size >= ipacdc_size) {
        psecAxiIramInfo->useHostIpEnable = 1;
        psecAxiIramInfo->bufIpAcDcUse = psecAxiIramInfo->bufBitUse + bitram_size;
        size -= ipacdc_size;
    } else
        goto out;

    ovl_size = (80 * mbNumX + 1023) & ~1023;
    if (parm->codecMode == VC1_DEC) {
        if (size >= ovl_size) {
            psecAxiIramInfo->useHostOvlEnable = 1;
            psecAxiIramInfo->bufOvlUse = psecAxiIramInfo->bufIpAcDcUse + ipacdc_size;
            size -= ovl_size;
        }
        if (cpu_is_mx6()) {
            btp_size = ((((mbNumX + 15) / 16) * mbNumY + 1) * 6 + 255) & ~255;
            if (size >= btp_size) {
                psecAxiIramInfo->useHostBtpEnable = 1;
                psecAxiIramInfo->bufBtpUse = psecAxiIramInfo->bufOvlUse + ovl_size;
                size -= btp_size;
            }
        }
    }
  out:
    /* i.MX53/i.MX6Q uses secondary AXI for IRAM access */
    psecAxiIramInfo->useBitEnable = psecAxiIramInfo->useHostBitEnable;
    psecAxiIramInfo->useIpEnable = psecAxiIramInfo->useHostIpEnable;
    psecAxiIramInfo->useDbkEnable = psecAxiIramInfo->useHostDbkEnable;
    psecAxiIramInfo->useOvlEnable = psecAxiIramInfo->useHostOvlEnable;
    psecAxiIramInfo->useBtpEnable = psecAxiIramInfo->useHostBtpEnable = 0;

    if (((parm->codecMode == VC1_DEC) && !psecAxiIramInfo->useHostOvlEnable) ||
        !psecAxiIramInfo->useHostIpEnable)
        warn_msg("VPU iram is less than needed, some parts don't use iram\n");
}

void SetEncSecondAXIIRAM(SecAxiUse * psecAxiIramInfo, SetIramParam * parm)
{
    iram_t iram;
    iram.start = VPU_SEC_AXI_START;
    iram.end = VPU_SEC_AXI_END;
    int size, dbk_size, bitram_size, ipacdc_size, mbNumX;

    if (!parm->width) {
        err_msg("Width is zero when calling SetEncSecondAXIIRAM function\n");
        return;
    }

    memset(psecAxiIramInfo, 0, sizeof(SecAxiUse));

    size = iram.end - iram.start + 1;

    mbNumX = (parm->width + 15) / 16;

    if (cpu_is_mx6()) {
        psecAxiIramInfo->searchRamSize = 0;
        psecAxiIramInfo->searchRamAddr = 0;
        goto set_dbk;
    }

    /* Setting internal iram usage per priority when iram isn't enough */
    psecAxiIramInfo->searchRamSize = (parm->width * 36 + 2048 + 1023) & ~1023;
    if (size >= psecAxiIramInfo->searchRamSize) {
        psecAxiIramInfo->useHostMeEnable = 1;
        psecAxiIramInfo->searchRamAddr = iram.start;
        size -= psecAxiIramInfo->searchRamSize;
    } else {
        err_msg("VPU iram is less than search ram size\n");
        goto out;
    }

  set_dbk:
    /* Only H.264BP and H.263P3 are considered */
    dbk_size = (128 * mbNumX + 1023) & ~1023;
    if (size >= dbk_size) {
        psecAxiIramInfo->useHostDbkEnable = 1;
        psecAxiIramInfo->bufDbkYUse = iram.start + psecAxiIramInfo->searchRamSize;
        psecAxiIramInfo->bufDbkCUse = psecAxiIramInfo->bufDbkYUse + dbk_size / 2;
        size -= dbk_size;
    } else
        goto out;

    bitram_size = (128 * mbNumX + 1023) & ~1023;
    if (size >= bitram_size) {
        psecAxiIramInfo->useHostBitEnable = 1;
        psecAxiIramInfo->bufBitUse = psecAxiIramInfo->bufDbkCUse + dbk_size / 2;
        size -= bitram_size;
    } else
        goto out;

    ipacdc_size = (128 * mbNumX + 1023) & ~1023;
    if (size >= ipacdc_size) {
        psecAxiIramInfo->useHostIpEnable = 1;
        psecAxiIramInfo->bufIpAcDcUse = psecAxiIramInfo->bufBitUse + bitram_size;
        size -= ipacdc_size;
    }

    psecAxiIramInfo->useHostOvlEnable = 0;  /* no need to enable ovl in encoder */
    psecAxiIramInfo->useBtpEnable = 0;

  out:
    /* i.MX53 uses secondary AXI for IRAM access */
    psecAxiIramInfo->useBitEnable = psecAxiIramInfo->useHostBitEnable;
    psecAxiIramInfo->useIpEnable = psecAxiIramInfo->useHostIpEnable;
    psecAxiIramInfo->useDbkEnable = psecAxiIramInfo->useHostDbkEnable;
    psecAxiIramInfo->useMeEnable = psecAxiIramInfo->useHostMeEnable;

    if (!psecAxiIramInfo->useHostIpEnable)
        warn_msg("VPU iram is less than needed, some parts don't use iram\n");
}

void SetMaverickCache(MaverickCacheConfig * pCacheConf, int mapType, int chromInterleave)
{
    if (mapType == LINEAR_FRAME_MAP) {
        /* Set luma */
        pCacheConf->luma.cfg.PageSizeX = 2;
        pCacheConf->luma.cfg.PageSizeY = 0;
        pCacheConf->luma.cfg.CacheSizeX = 2;
        pCacheConf->luma.cfg.CacheSizeY = 6;
        /* Set chroma */
        pCacheConf->chroma.cfg.PageSizeX = 2;
        pCacheConf->chroma.cfg.PageSizeY = 0;
        pCacheConf->chroma.cfg.CacheSizeX = 2;
        pCacheConf->chroma.cfg.CacheSizeY = 4;
        pCacheConf->PageMerge = 2;
    } else {
        /* Set luma */
        pCacheConf->luma.cfg.PageSizeX = 0;
        pCacheConf->luma.cfg.PageSizeY = 2;
        pCacheConf->luma.cfg.CacheSizeX = 4;
        pCacheConf->luma.cfg.CacheSizeY = 4;
        /* Set chroma */
        pCacheConf->chroma.cfg.PageSizeX = 0;
        pCacheConf->chroma.cfg.PageSizeY = 2;
        pCacheConf->chroma.cfg.CacheSizeX = 4;
        pCacheConf->chroma.cfg.CacheSizeY = 3;
        pCacheConf->PageMerge = 1;
    }

    pCacheConf->Bypass = 0;     /* cache enable */
    pCacheConf->DualConf = 0;
    pCacheConf->LumaBufferSize = 32;
    if (chromInterleave) {
        pCacheConf->CbBufferSize = 0;
        pCacheConf->CrBufferSize = 0x10;
    } else {
        pCacheConf->CbBufferSize = 8;
        pCacheConf->CrBufferSize = 8;
    }
}

int vpu_sys_reset(int timeout)
{
    uint32_t val = 0;

    val = readl(SRC_BASE_ADDR + SRC_SCR_OFFSET);
    writel(val | (1 << 2), SRC_BASE_ADDR + SRC_SCR_OFFSET);

    /*wait for the bit self cleared */
    while (timeout-- > 0) {
        val = readl(SRC_BASE_ADDR + SRC_SCR_OFFSET) & (1 << 2);
        if (val == 0)
            return true;
    }
    return false;
}

vpu_resource_t *vpu_semaphore_open(void)
{
    int ret = 0;
    vpu_resource_t *semap;
    CodecInst *pCodecInst;
    int i;
    vpu_mem_desc share_mem;

    share_mem.size = sizeof(vpu_resource_t);
    ret = vpu_malloc(&share_mem);
    if (ret != 0) {
        err_msg("Unable to map physical of share memory\n");
        return NULL;
    }
    semap = (vpu_resource_t *) share_mem.phy_addr;

    memset(semap, 0, sizeof(vpu_resource_t));
    if (!semap->is_initialized) {
        for (i = 0; i < MAX_NUM_INSTANCE; ++i) {
            pCodecInst = (CodecInst *) (&semap->codecInstPool[i]);
            pCodecInst->instIndex = i;
            pCodecInst->inUse = 0;
        }
        semap->is_initialized = 1;
    }
    g_vpu_system_mem_size += share_mem.size;
    return semap;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
