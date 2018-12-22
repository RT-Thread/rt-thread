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

/*!
 * @file vpu_util.h
 *
 * @brief VPU utilities. All functions and definitions here are for use of VPU library.
 *
 * @ingroup diag_vpu
 */

#ifndef _VPU_UTIL_H_
#define _VPU_UTIL_H_

#include <sys/types.h>

#include "vpu_reg.h"
#include "vpu_lib.h"
#include "vpu_io.h"
#include "vpu_gdi.h"

//! @addtogroup diag_vpu
//! @{

//////////////////////////////////////////////////////////////////////////////
// DEFINITIONS
//////////////////////////////////////////////////////////////////////////////

#define MAX_FW_BINARY_LEN		200 * 1024
typedef enum {
    INT_BIT_PIC_RUN = 3,
    INT_BIT_BIT_BUF_EMPTY = 14,
    INT_BIT_BIT_BUF_FULL = 15
} InterruptBit;

#if defined(CHIP_MX6DQ) || defined(CHIP_MX6SDL)
#define BIT_WORK_SIZE			(128*1024)
#else
#define BIT_WORK_SIZE			(128*1024)
#endif
#define SIZE_CONTEXT_BUF		BIT_WORK_SIZE

#define SIZE_PIC_PARA_BASE_BUF          0x100
#define SIZE_MV_DATA                    0x20000
#define SIZE_MB_DATA                    0x4000
#define SIZE_FRAME_BUF_STAT             0x100
#define SIZE_SLICE_INFO                 0x4000
#define USER_DATA_INFO_OFFSET           8*17
#define JPU_GBU_SIZE			512

#define ADDR_PIC_PARA_BASE_OFFSET       0
#define ADDR_MV_BASE_OFFSET             ADDR_PIC_PARA_BASE_OFFSET + SIZE_PIC_PARA_BASE_BUF
#define ADDR_MB_BASE_OFFSET             ADDR_MV_BASE_OFFSET + SIZE_MV_DATA
#define ADDR_FRAME_BUF_STAT_BASE_OFFSET ADDR_MB_BASE_OFFSET + SIZE_MB_DATA
#define ADDR_SLICE_BASE_OFFSET          ADDR_MB_BASE_OFFSET + SIZE_MB_DATA
#define ENC_ADDR_END_OF_RPT_BUF         ADDR_FRAME_BUF_STAT_BASE_OFFSET + SIZE_SLICE_INFO
#define DEC_ADDR_END_OF_RPT_BUF         ADDR_FRAME_BUF_STAT_BASE_OFFSET + SIZE_FRAME_BUF_STAT

#define DC_TABLE_INDEX0		    0
#define AC_TABLE_INDEX0		    1
#define DC_TABLE_INDEX1		    2
#define AC_TABLE_INDEX1		    3
#define Q_COMPONENT0		    0
#define Q_COMPONENT1		    0x40
#define Q_COMPONENT2		    0x80
#define HUFF_VAL_SIZE		    162

#define VPU_SW_RESET_BPU_CORE   0x008
#define VPU_SW_RESET_BPU_BUS    0x010
#define VPU_SW_RESET_VCE_CORE   0x020
#define VPU_SW_RESET_VCE_BUS    0x040
#define VPU_SW_RESET_GDI_CORE   0x080
#define VPU_SW_RESET_GDI_BUS    0x100

#if defined(CHIP_MX53)
enum {
    AVC_DEC = 0,
    VC1_DEC = 1,
    MP2_DEC = 2,
    MP4_DEC = 3,
    DV3_DEC = 3,
    RV_DEC = 4,
    MJPG_DEC = 5,
    AVC_ENC = 8,
    MP4_ENC = 11,
    MJPG_ENC = 13,
    /* dummy */
    AVS_DEC = 0x81,
    VPX_DEC = 0x82
};
#elif defined(CHIP_MX6DQ) || defined(CHIP_MX6SDL)
enum {
    AVC_DEC = 0,
    VC1_DEC = 1,
    MP2_DEC = 2,
    MP4_DEC = 3,
    DV3_DEC = 3,
    RV_DEC = 4,
    AVS_DEC = 5,
    MJPG_DEC = 6,
    VPX_DEC = 7,
    AVC_ENC = 8,
    MP4_ENC = 11,
    MJPG_ENC = 13
};
#else
enum {
    MP4_DEC = 0,
    MP4_ENC = 1,
    AVC_DEC = 2,
    AVC_ENC = 3,
    VC1_DEC = 4,
    MP2_DEC = 5,
    DV3_DEC = 6,
    /* dummy */
    RV_DEC = 0x81,
    MJPG_DEC = 0x82,
    MJPG_ENC = 0x83
};
#endif

enum {
    MP4_AUX_MPEG4 = 0,
    MP4_AUX_DIVX3 = 1
};

enum {
    VPX_AUX_THO = 0,
    VPX_AUX_VP6 = 1,
    VPX_AUX_VP8 = 2
};

enum {
    AVC_AUX_AVC = 0,
    AVC_AUX_MVC = 1
};

enum {
    SEQ_INIT = 1,
    SEQ_END = 2,
    PIC_RUN = 3,
    SET_FRAME_BUF = 4,
    ENCODE_HEADER = 5,
    ENC_PARA_SET = 6,
    DEC_PARA_SET = 7,
    DEC_BUF_FLUSH = 8,
    RC_CHANGE_PARAMETER = 9,
    VPU_WAKE = 11,
    FIRMWARE_GET = 0xf
};

enum {
    API_MUTEX = 0,
    REG_MUTEX = 1
};

enum {
    CTX_BIT_STREAM_PARAM = 0,
    CTX_BIT_FRM_DIS_FLG,
    CTX_BIT_WR_PTR,
    CTX_BIT_RD_PTR,
    CTX_BIT_FRAME_MEM_CTRL,
    CTX_MAX_REGS
};

enum {
    Marker = 0xFF,
    FF_Marker = 0x00,
    SOI_Marker = 0xFFD8,        // Start of image
    EOI_Marker = 0xFFD9,        // End of image
    JFIF_CODE = 0xFFE0,         // Application
    EXIF_CODE = 0xFFE1,
    DRI_Marker = 0xFFDD,        // Define restart interval
    RST_Marker = 0xD,           // 0xD0 ~0xD7
    DQT_Marker = 0xFFDB,        // Define quantization table(s)
    DHT_Marker = 0xFFC4,        // Define Huffman table(s)
    SOF_Marker = 0xFFC0,        // Start of frame : Baseline DCT
    SOS_Marker = 0xFFDA,        // Start of scan
};

typedef struct {
    int useBitEnable;
    int useIpEnable;
    int useDbkEnable;
    int useOvlEnable;
    int useBtpEnable;
    int useMeEnable;

    int useHostBitEnable;
    int useHostIpEnable;
    int useHostDbkEnable;
    int useHostBtpEnable;
    int useHostOvlEnable;
    int useHostMeEnable;

    PhysicalAddress bufBitUse;
    PhysicalAddress bufIpAcDcUse;
    PhysicalAddress bufDbkYUse;
    PhysicalAddress bufDbkCUse;
    PhysicalAddress bufOvlUse;
    PhysicalAddress bufBtpUse;

    PhysicalAddress searchRamAddr;
    int searchRamSize;

} SecAxiUse;

typedef struct CacheSizeCfg {
    unsigned PageSizeX:4;
    unsigned PageSizeY:4;
    unsigned CacheSizeX:4;
    unsigned CacheSizeY:4;
    unsigned Reserved:16;
} CacheSizeCfg;

typedef struct {
    union {
        uint32_t word;
        CacheSizeCfg cfg;
    } luma;
    union {
        uint32_t word;
        CacheSizeCfg cfg;
    } chroma;
    unsigned Bypass:1;
    unsigned DualConf:1;
    unsigned PageMerge:2;
    unsigned LumaBufferSize:8;
    unsigned CbBufferSize:8;
    unsigned CrBufferSize:8;
} MaverickCacheConfig;

typedef struct {
    uint32_t *paraSet;
    int size;
} DecParamSet;

typedef struct {
    int enable;
    int is_secondary;
    PhysicalAddress start_address;
    PhysicalAddress end_address;
} WriteMemProtectRegion;

typedef struct {
    WriteMemProtectRegion region[6];
} WriteMemProtectCfg;

typedef struct {
    int width;
    int height;
    int codecMode;
    int profile;
} SetIramParam;

typedef struct {
    unsigned subFrameSyncOn:1;
    unsigned sourceBufNumber:7;
    unsigned sourceBufIndexBase:8;
} EncSubFrameSyncConfig;

typedef struct {
    int picWidth;
    int picHeight;
    int alignedWidth;
    int alignedHeight;
    int seqInited;
    int frameIdx;
    int format;

    int rstIntval;
    int busReqNum;
    int mcuBlockNum;
    int compNum;
    int compInfo[3];

    uint32_t huffCode[4][256];
    uint32_t huffSize[4][256];
    uint8_t *pHuffVal[4];
    uint8_t *pHuffBits[4];
    uint8_t *pCInfoTab[5];
    uint8_t *pQMatTab[4];

} JpgEncInfo;

typedef struct {
    EncOpenParam openParam;
    EncInitialInfo initialInfo;

    PhysicalAddress streamRdPtr;
    PhysicalAddress streamBufStartAddr;
    PhysicalAddress streamBufEndAddr;
    int streamBufSize;

    FrameBuffer *frameBufPool;
    int numFrameBuffers;
    int stride;
    int srcFrameWidth;
    int srcFrameHeight;

    int rotationEnable;
    int mirrorEnable;
    MirrorDirection mirrorDirection;
    int rotationAngle;

    int initialInfoObtained;
    int dynamicAllocEnable;
    int ringBufferEnable;
    int mp4_dataPartitionEnable;
    int linear2TiledEnable;
    int mapType;

    SecAxiUse secAxiUse;
    MaverickCacheConfig cacheConfig;
    EncSubFrameSyncConfig subFrameSyncConfig;
    GdiTiledMap sTiledInfo;

    EncReportInfo encReportMBInfo;
    EncReportInfo encReportMVInfo;
    EncReportInfo encReportSliceInfo;

    vpu_mem_desc picParaBaseMem;
    vpu_mem_desc searchRamMem;  /* Used if IRAM is disabled */

} EncInfo;

/* bit input */
/* buffer, buffer_end and size_in_bits must be present and used by every reader */
typedef struct {
    const uint8_t *buffer, *buffer_end;
    int index;
    int size_in_bits;
} GetBitContext;

typedef struct {
    DecOpenParam openParam;
    DecInitialInfo initialInfo;

    PhysicalAddress streamWrPtr;
    PhysicalAddress streamBufStartAddr;
    PhysicalAddress streamBufEndAddr;
    int streamEndflag;
    int streamBufSize;

    FrameBuffer *frameBufPool;
    int numFrameBuffers;
    FrameBuffer *recFrame;
    int stride;

    int rotationEnable;
    int deringEnable;
    int mirrorEnable;
    MirrorDirection mirrorDirection;
    int rotationAngle;
    FrameBuffer rotatorOutput;
    int rotatorStride;
    int rotatorOutputValid;
    int initialInfoObtained;

    FrameBuffer deBlockingFilterOutput;
    int deBlockingFilterOutputValid;

    int filePlayEnable;
    int picSrcSize;
    int dynamicAllocEnable;
    int vc1BframeDisplayValid;
    int mapType;
    int tiledLinearEnable;

    DbkOffset dbkOffset;

    SecAxiUse secAxiUse;
    MaverickCacheConfig cacheConfig;

    vpu_mem_desc picParaBaseMem;
    vpu_mem_desc userDataBufMem;
    WriteMemProtectCfg writeMemProtectCfg;
    GdiTiledMap sTiledInfo;

    DecReportInfo decReportFrameBufStat;    /* Frame Buffer Status */
    DecReportInfo decReportMBInfo;  /* Mb Param for Error Concealment */
    DecReportInfo decReportMVInfo;  /* Motion vector */
    DecReportInfo decReportUserData;
} DecInfo;

typedef struct CodecInst {
    int instIndex;
    int inUse;
    int initDone;
    int codecMode;
    int codecModeAux;
    vpu_mem_desc contextBufMem; /* For context buffer */
    unsigned long ctxRegs[CTX_MAX_REGS];
    union {
        EncInfo encInfo;
        DecInfo decInfo;
    } CodecInfo;
    union {
        EncParam encParam;
        DecParam decParam;
    } CodecParam;
} CodecInst;

typedef struct {
    int is_initialized;

    /* VPU data for sharing */
    CodecInst codecInstPool[MAX_NUM_INSTANCE];
    CodecInst *pendingInst;
} vpu_resource_t;

#define swab32(x) \
	((uint32_t)( \
		(((uint32_t)(x) & (uint32_t)0x000000ffUL) << 24) | \
		(((uint32_t)(x) & (uint32_t)0x0000ff00UL) <<  8) | \
		(((uint32_t)(x) & (uint32_t)0x00ff0000UL) >>  8) | \
		(((uint32_t)(x) & (uint32_t)0xff000000UL) >> 24) ))

extern int g_vpu_system_mem_size;

//////////////////////////////////////////////////////////////////////////////
// API
//////////////////////////////////////////////////////////////////////////////
void BitIssueCommand(CodecInst * pCodecInst, int cmd);
void BitIssueCommandEx(CodecInst * pCodecInst, int cmd);

RetCode LoadBitCodeTable(uint16_t * pBitCode, int *size);
RetCode DownloadBitCodeTable(uint32_t * virtCodeBuf);

RetCode GetCodecInstance(CodecInst ** ppInst);
void FreeCodecInstance(CodecInst * pCodecInst);

RetCode CheckInstanceValidity(CodecInst * pci);
RetCode CheckEncInstanceValidity(EncHandle handle);
RetCode CheckEncOpenParam(EncOpenParam * pop);
RetCode CheckEncParam(CodecInst * pCodecInst, EncParam * param);
void EncodeHeader(EncHandle handle, EncHeaderParam * encHeaderParam);
void GetParaSet(EncHandle handle, int paraSetType, EncParamSet * para);

RetCode CheckDecInstanceValidity(DecHandle handle);
RetCode CheckDecOpenParam(DecOpenParam * pop);
int DecBitstreamBufEmpty(DecHandle handle);
void SetParaSet(DecHandle handle, int paraSetType, DecParamSet * para);
RetCode CopyBufferData(uint8_t * dst, uint8_t * src, int size);

RetCode SetGopNumber(EncHandle handle, uint32_t * gopNumber);
RetCode SetIntraQp(EncHandle handle, uint32_t * intraQp);
RetCode SetBitrate(EncHandle handle, uint32_t * bitrate);
RetCode SetFramerate(EncHandle handle, uint32_t * framerate);
RetCode SetIntraRefreshNum(EncHandle handle, uint32_t * pIntraRefreshNum);
RetCode SetSliceMode(EncHandle handle, EncSliceMode * pSliceMode);
RetCode SetHecMode(EncHandle handle, int mode);

void SetDecSecondAXIIRAM(SecAxiUse * psecAxiIramInfo, SetIramParam * parm);
void SetEncSecondAXIIRAM(SecAxiUse * psecAxiIramInfo, SetIramParam * parm);
void SetMaverickCache(MaverickCacheConfig * pCacheConf, int mapType, int chromInterleave);

vpu_resource_t *vpu_semaphore_open(void);

//! @}

#endif

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
