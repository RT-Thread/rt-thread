/*
 * Copyright (c) 2010-2012, Freescale Semiconductor, Inc.
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
#ifndef _ATAPI_H_
#define _ATAPI_H_

//! @addtogroup diag_sata
//! @{

//////////////////////////////////////////////////////////////////////////////
// Definitions
//////////////////////////////////////////////////////////////////////////////

//! @brief Enumeration of ATAPI COMMAND
typedef enum ATAPI_COMMAND {
    ATAPI_COMMAND_IDENTIFY_DEVICE = 0xEC,
    ATAPI_COMMAND_READ_DMA = 0xC8,
    ATAPI_COMMAND_READ_SECTOR = 0x20,
    ATAPI_COMMAND_READ_DMA_QUEUED = 0xC7,
    ATAPI_COMMAND_WRITE_DMA = 0xCA,
    ATAPI_COMMAND_WRITE_SECTOR = 0x30,
    ATAPI_COMMAND_WRITE_DMA_QUEUED = 0xCC,
    ATAPI_COMMAND_DIAGNOSIS = 0x90,
    ATAPI_COMMAND_PACKET = 0xA0,
    ATAPI_COMMAND_READ_BUFFER = 0xE4,
    ATAPI_COMMAND_WRITE_BUFFER = 0xE8,
    ATAPI_COMMAND_SET_FEATURES = 0xEF,
    ATAPI_COMMAND_SEC_ERS_PREP = 0xF3,
    ATAPI_COMMAND_FORMAT = 0xF7,
    ATAPI_COMMAND_SLEEP = 0xE6,
    ATAPI_COMMAND_CHK_PWR_MODE = 0xE5,
    ATAPI_COMMAND_IDLE_IMMEDIATE = 0xE1,
    ATAPI_COMMAND_STBY_IMMEDIATE = 0xE0,
    ATAPI_COMMAND_DEVICE_RESET = 0x08,
    ATAPI_COMMAND_CFA_WRITE_MULTI_W_OUT_ERASE = 0xCD,
    ATAPI_COMMAND_CFA_WRITE_SECTOR_W_OUT_ERASE = 0xCD,
} atapi_cmd_t;

//! @brief Data structure defined based on ATAPI7 specification(T13/1532D)
//! ide_disk.h has another similar defintions
typedef struct sata_identify_data_t_ {
    u16 general_conf;           // 00    : general configuration
    u16 num_cylinders;          // 01    : number of cylinders (default CHS trans)
    u16 specific_conf;          // 02    : specific configuration
    u16 num_heads;              // 03    : number of heads (default CHS trans)
    u16 num_ub_per_track;       // 04    : number of unformatted bytes per track
    u16 num_ub_per_sector;      // 05    : number of unformatted bytes per sector
    u16 num_sectors;            // 06    : number of sectors per track (default CHS trans)
    u16 rsv5[2];                // 07-08 : number of sectors per card
    u16 rsv6;                   // 09    : reserved
    u16 serial[10];             // 10-19 : serial number (string)
    u16 rsv7;                   // 20    : buffer type (dual ported)
    u16 rsv8;                   // 21    : buffer size in 512 increments
    u16 rsv9;                   // 22    : number of ECC bytes passed on R/W Long cmds
    u16 fw_rev[4];              // 23-26 : firmware revision (string)
    u16 model_num[20];          // 27-46 : model number (string)
    u16 rw_mult_support;        // 47    : max number of sectors on R/W multiple cmds
    u16 rsv10;                  // 48    : reserved
    u16 capabilities[2];        // 49-50 : LBA, DMA, IORDY support indicator
    u16 rsv11;                  // 51    : PIO data transfer cycle timing mode
    u16 rsv12;                  // 52    : single word DMA data transfer cycle timing mode
    u16 cur_field_validity;     // 53    : words 54-58 validity (0 == not valid)
    u16 rsv13;                  // 54    : number of current cylinders
    u16 rsv14;                  // 55    : number of current heads
    u16 rsv15;                  // 56    : number of current sectors per track
    u16 rsv16[2];               // 57-58 : current capacity in sectors
    u16 mult_sectors;           // 59    : multiple sector setting
    u16 lba_total_sectors[2];   // 60-61 : total sectors in LBA mode
    u16 rsv17;                  // 62    : single word DMA support
    u16 mw_dma;                 // 63    : multi word DMA support
    u16 apio_modes;             // 64    : advanced PIO transfer mode supported
    u16 min_dma_timing;         // 65    : minimum multiword DMA transfer cycle
    u16 rec_dma_timing;         // 66    : recommended multiword DMA cycle
    u16 min_pio_timing;         // 67    : min PIO transfer time without flow control
    u16 min_pio_iordy_timing;   // 68    : min PIO transfer time with IORDY flow control
    u16 rsv18[6];               // 69-74 : reserved
    u16 queue_depth;            // 75    : queue depth
    u16 rsv19[4];               // 76-79 : reserved for SATA
    u16 major_ver;              // 80    : major version number
    u16 minor_ver;              // 81    : minor version number
    u16 cmd_set_supp[3];        // 82-84 : command set supported
    u16 cmd_set_enabled[3];     // 85-87 : command set/feature enabled
    u16 ultra_dma_mode;         // 88    : ultra dma modes
    u16 sec_ers_unit_time;      // 89    : time required for security erase unit completion
    u16 enhance_sec_ers_time;   // 90    : time required for enhanced security erase completion
    u16 current_pm_val;         // 91    : current advanced power management value
    u16 master_pwd_rev;         // 92    : master password revision code
    u16 hw_conf_tst_result;     // 93    : hardware configuration test result
    u16 acoustic_mng_val;       // 94    : automatic acoustic management value
    u16 stream_min_req_sz;      // 95    : stream minimum request size
    u16 stream_trans_time_dma;  // 96    : streaming transfer time - dma
    u16 stream_access_latency;  // 97    : streaming access latency - dma and pio
    u16 stream_perf_gran[2];    // 98-99 : streaming performance granularity
    u16 max_48b_lba_addr[4];    // 100-103:maximum user lba for 48b address feature set
    u16 stream_trans_time_pio;  // 104   : streaming transfer time - pio
    u16 rsv20;                  // 105   : reserved
    u16 sector_size;            // 106   : physical sector size/logical sector size
    u16 inter_seek_delay_us;    // 107   : inter-seek delay for ISO-7799 acoustic testing in ms
    u16 world_wide_name[4];     // 108-111:world wide name
    u16 rsv21[4];               // 112-115:reserved for world wide name extension to 128bits
    u16 rsv22;                  // 116   : reserved for technical report
    u16 sector_sz_in_word[2];   // 117-118:words per logical sector
    u16 rsv23[8];               // 119-126:reserved
    u16 rem_stat_notify_supp;   // 127   : removable mdedia status notification feature set support
    u16 security_status;        // 128   : security status
    u16 vendor_specific[31];    // 129-159:vendor specific
    u16 cfa_pwr_mode_1;         // 160   : CFA power mode 1
    u16 rsv24[15];              // 161-175:reserved for assignment by the CF association
    u16 sn[30];                 // 176-205:current media serial number
    u16 rsv25[49];              // 206-254: reserved
    u16 integrity;              // 255   : 15-8 -> checksum; 7-0 -> signature;
} sata_identify_data_t;

//! @}

#endif

//////////////////////////////////////////////////////////////////////////////
// EOF
//////////////////////////////////////////////////////////////////////////////
