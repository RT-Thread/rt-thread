/*
 * The Clear BSD License
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 * that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
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

#include "imxrt1052_spiflash_config.h"

#define XIP_BOOT_HEADER_ENABLE  1
/*******************************************************************************
 * Code
 ******************************************************************************/
#if defined(XIP_BOOT_HEADER_ENABLE) && (XIP_BOOT_HEADER_ENABLE == 1)
#if defined(__CC_ARM) || defined(__GNUC__)
__attribute__((section(".boot_hdr.conf")))
#elif defined(__ICCARM__)
#pragma location = ".boot_hdr.conf"
#endif

const flexspi_nor_config_t spiflash_config = {
    .memConfig =
        {
            .tag = FLEXSPI_CFG_BLK_TAG,/*标志：FCFB*/
            .version = FLEXSPI_CFG_BLK_VERSION,/*版本：V1.4.0*/
            .readSampleClkSrc = kFlexSPIReadSampleClk_LoopbackInternally,/*内部环回*/
            .csHoldTime = 3u, /*保持时间*/
            .csSetupTime = 3u,/*建立时间*/
            .columnAddressWidth = 0u,/*列地址宽度*/
            .deviceModeCfgEnable = 1u,/*设备模式配置使能*/
            .deviceModeType = 1u,/*Quad 使能命令*/
            .deviceModeSeq.seqNum = 1u,/*LUT序列号*/
            .deviceModeSeq.seqId = 4u, /*LUT序列索引*/    
            .deviceModeArg = 0x000200,/*设置 QE=1（S9）*/
            .deviceType = kFlexSpiDeviceType_SerialNOR,/*设备类型为nor flash*/
            .sflashPadType = kSerialFlash_4Pads,/*设备数据总线为4*/
            .serialClkFreq = kFlexSpiSerialClk_133MHz,/*flash 时钟*/
            .sflashA1Size = 32u * 1024u * 1024u,      /*flash 大小32MBytes*/
            //.dataValidTime = {16u, 16u},
            .lookupTable =
                {
                    /*快速读命令（四线）*/
                    [0]     = FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0xEB, RADDR_SDR, FLEXSPI_4PAD, 0x18),
                    [1]     = FLEXSPI_LUT_SEQ(DUMMY_SDR, FLEXSPI_4PAD, 0x06, READ_SDR, FLEXSPI_4PAD, 0x04),
                    

                    /*读状态命令*/
                    [1*4]   = FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0x05, READ_SDR, FLEXSPI_1PAD, 0x04),
                    /*写使能命令*/
                    [3*4]   = FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0x06, STOP, FLEXSPI_1PAD, 0),      
                    /*擦除扇区命令*/
                    [5*4]   = FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0x20, RADDR_SDR, FLEXSPI_1PAD, 0x04),
                    /*页编程命令（四线）*/
                    [9*4]   = FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0x32, RADDR_SDR, FLEXSPI_1PAD, 0x18),  
                    [9*4+1] = FLEXSPI_LUT_SEQ(WRITE_SDR,FLEXSPI_4PAD , 0x04, STOP, FLEXSPI_1PAD, 0),                  
                    /*整片擦除*/
                    [11*4]  = FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0xc7, STOP, FLEXSPI_1PAD, 0),                  
                },
        },
    .pageSize = 256u,/*页大小为256字节*/
    .sectorSize = 4u * 1024u,/*扇区大小为4k字节*/
};
#endif /* XIP_BOOT_HEADER_ENABLE */
