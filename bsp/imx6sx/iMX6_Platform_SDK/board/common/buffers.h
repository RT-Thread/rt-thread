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
/*!
 * @file buffers.h
 * @definitions for ALL buffer memory space regions used by sdk drivers
 */

#define IPU_DEFAULT_WORK_CLOCK 264000000
#define IPU_DMA_MEMORY_START	0x40000000
#define IPU_DMA_MEMORY_END		0x43FFFFFF

#define HDMI_AUDIO_BUF_START  0x4fff0000
#define HDMI_AUDIO_BUF_END    0x4fff4000

#define CH23_EBA0 	(IPU_DMA_MEMORY_START + 0x00000000)
#define CH23_EBA1 	(IPU_DMA_MEMORY_START + 0x00400000)
#define CH27_EBA0 	(IPU_DMA_MEMORY_START + 0x00800000)
#define CH27_EBA1 	(IPU_DMA_MEMORY_START + 0x00C00000)
#define CH28_EBA0 	(IPU_DMA_MEMORY_START + 0x01000000)
#define CH28_EBA1 	(IPU_DMA_MEMORY_START + 0x01400000)
#define CH0_EBA0 	(IPU_DMA_MEMORY_START + 0x01800000)
#define CH0_EBA1 	(IPU_DMA_MEMORY_START + 0x01C00000)

/*for dual video playback*/
#define IPU1_CH23_EBA0	CH23_EBA0
#define IPU1_CH23_EBA1	CH23_EBA1
#define IPU2_CH23_EBA0	CH27_EBA0
#define IPU2_CH23_EBA1	CH27_EBA1

// for video playback after resizing&rotation
#define CH22_EBA0 	(IPU_DMA_MEMORY_START + 0x01800000)
#define CH22_EBA1	(IPU_DMA_MEMORY_START + 0x01C00000)

#define CH21_EBA0 	(IPU_DMA_MEMORY_START + 0x02000000)
#define CH21_EBA1 	(IPU_DMA_MEMORY_START + 0x02400000)
#define CH20_EBA0 	(IPU_DMA_MEMORY_START + 0x02800000)
#define CH20_EBA1 	(IPU_DMA_MEMORY_START + 0x02C00000)

/* put the TWO video instance on different CS to
   improve the performance.
 */
#define VPU_WORK_BUFFERS        (0x44100000)
#define VIDEO_BUFFERS_START     (0x48000000)
#define VIDEO_BUFFERS_END       (0x4FFFFFFF)

/*OCRAM partition table*/
#define VPU_SEC_AXI_START	0x00910000
#define VPU_SEC_AXI_END		0x0091FFFF

/* OCRAM ADMA buffer */
#define USDHC_ADMA_BUFFER1 0x00907000
#define USDHC_ADMA_BUFFER2 0x00908000
#define USDHC_ADMA_BUFFER3 0x00909000
#define USDHC_ADMA_BUFFER4 0x0090A000

// USB buffers
#define QH_BUFFER               0x00908000  // internal RAM
#define TD_BUFFER               0x00908200  // internal RAM

#define SATA_PROTOCOL_BUFFER_BASE 0x0090a000
#define SATA_PROTOCOL_BUFFER_SIZE 0x1000
#define SATA_TRANSFER_BUFFER_BASE 0x0090c000

