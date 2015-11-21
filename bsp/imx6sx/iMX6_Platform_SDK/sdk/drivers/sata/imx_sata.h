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
#ifndef _IMX_SATA_H_
#define _IMX_SATA_H_

#include "sdk.h"
#include "registers/regssata.h"

//////////////////////////////////////////////////////////////////////////////
// Definitions
//////////////////////////////////////////////////////////////////////////////

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef signed int s32;

#define SATA_FAT_BLOCK_SIZE           4096
#define SATA_HDD_SECTOR_SIZE          512

#define SATA_RECEIVED_FIS_BASE     SATA_PROTOCOL_BUFFER_BASE
#define SATA_RECEIVED_FIS_SIZE     sizeof(sata_rx_fis_t)    //256-byte

#define SATA_COMMAND_LIST_BASE     (SATA_RECEIVED_FIS_BASE+0x400)
#define SATA_COMMAND_HEADER_SIZE   sizeof(sata_command_header_t)
#define SATA_COMMAND_LIST_SIZE     (SATA_COMMAND_HEADER_SIZE*32)
#define SATA_COMMAND_TABLE_BASE    (SATA_COMMAND_LIST_BASE + SATA_COMMAND_LIST_SIZE)
#define SATA_COMMAND_TABLE_SIZE    (SATA_PROTOCOL_BUFFER_SIZE- SATA_RECEIVED_FIS_SIZE - SATA_COMMAND_LIST_SIZE)

#define SATA_MAX_TRANSFER_SECTOR_CNT    32
#define SATA_MAX_TRANSFER_DATA_SZ     (SATA_HDD_SECTOR_SIZE*SATA_MAX_TRANSFER_SECTOR_CNT)

#define MAX_TIMEOUT_COUNTER           0x1FFFF
#define PORT_N_INIT_TIMEOUT           500000    // 500ms
#define PORT_N_DET_TIEMOUT            1000  // 1ms

#define MOUNT_MODE                    1
#define UMOUNT_MODE                   0

#define SATA_PDMA_ENABLED             1

//! @brief SATA FIS Types Definitions
#define SATA_FIS_TYPE_RFIS_H2D             0x27 //Register FIS - Host to Device
#define SATA_FIS_TYPE_RFIS_D2H             0x34 //Register FIS - Device to Host
#define SATA_FIS_TYPE_DAFIS                0x39 //DMA Activate FIS - Device to Host
#define SATA_FIS_TYPE_DSFIS                0x41 //DMA Setup FIS - Bi-dir
#define SATA_FIS_TYPE_DFIS                 0x46 //Data FIS - Bi-dir
#define SATA_FIS_TYPE_BAFIS                0x58 //BIST Activate - Bi-dir
#define SATA_FIS_TYPE_PSFIS                0x5F //PIO Setup FIS - Device to Host
#define SATA_FIS_TYPE_SDBFIS               0xA1 //Set Device Bits FIS - Device to Host

//! @brief SATA OPERATION Direction
#define SATA_READ                          0x0
#define SATA_WRITE                         0x1

#define SATA_DISABLED                      0x0
#define SATA_ENABLED                       0x1

#define IOC                                0x1  //Interrupt On Complete

//! @brief TIMER1MS
//! @brief 1ms is AHB Frequency 133MHz/1000, the default value is 100000 for 100Mhz frequency
#define SATA_AHCI_HOST_TIMER1MS_MASK       133000

//! @brief Interrupt Status
#define SATA_AHCI_HOST_IS_PORT_N_INTR_ISSUED(n) (1<<n)

//! @brief OOBR
#define SATA_AHCI_HOST_OOBR_COMWAKE_MIN_VAL  (0x02<<24)
#define SATA_AHCI_HOST_OOBR_COMWAKE_MAX_VAL  (0x06<<16)
#define SATA_AHCI_HOST_OOBR_COMINIT_MIN_VAL  (0x0b<<8)
#define SATA_AHCI_HOST_OOBR_COMINIT_MAX_VAL  (0x14<<0)

#define SATA_AHCI_PORT_N_INTR_ENANBLE_MASK (BM_SATA_P0IE_TFEE \
                                           |BM_SATA_P0IE_HBFE \
                                           |BM_SATA_P0IE_HBDE \
                                           |BM_SATA_P0IE_IFE \
                                           |BM_SATA_P0IE_INFE \
                                           |BM_SATA_P0IE_DHRE \
                                           |BM_SATA_P0IE_PSE \
                                           |BM_SATA_P0IE_DSE \
                                           |BM_SATA_P0IE_SDBE \
                                           |BM_SATA_P0IE_UFE \
                                           |BM_SATA_P0IE_PCE \
                                           |BM_SATA_P0IE_OFE);

//! @brief PxDMACR Macros
#define DMACR_AHB_BURST_SIZE_1_DWORD       0x1
#define DMACR_AHB_BURST_SIZE_2_DWORDS      0x2
#define DMACR_AHB_BURST_SIZE_4_DWORDS      0x3
#define DMACR_AHB_BURST_SIZE_8_DWORDS      0x4
#define DMACR_AHB_BURST_SIZE_16_DWORDS     0x5
#define DMACR_AHB_BURST_SIZE_32_DWORDS     0x6
#define DMACR_AHB_BURST_SIZE_64_DWORDS     0x7
#define DMACR_AHB_BURST_SIZE_128_DWORDS    0x8
#define DMACR_AHB_BURST_SIZE_256_DWORDS    0x0  //0x9~0xF
#define DMACR_TRANSAC_SIZE_1_DWORD         0x0
#define DMACR_TRANSAC_SIZE_2_DWORDS        0x1
#define DMACR_TRANSAC_SIZE_4_DWORDS        0x2
#define DMACR_TRANSAC_SIZE_8_DWORDS        0x3
#define DMACR_TRANSAC_SIZE_16_DWORDS       0x4
#define DMACR_TRANSAC_SIZE_32_DWORDS       0x5
#define DMACR_TRANSAC_SIZE_64_DWORDS       0x6
#define DMACR_TRANSAC_SIZE_128_DWORDS      0x7
#define DMACR_TRANSAC_SIZE_256_DWORDS      0x8
#define DMACR_TRANSAC_SIZE_512_DWORDS      0x9
#define DMACR_TRANSAC_SIZE_1K_DWORDS       0xA

//! @brief PxSSTS Macros
#define  SSTS_DET_NO_DEVICE_NO_PHY         0x0  //No device detected and PHY communication not established
#define  SSTS_DET_DEV_DET_NO_PHY           0x1  //Device detected but PHY is not establish
#define  SSTS_DET_DEV_DET_PHY_RDY          0x3  //Device detected and PHY is establed
#define  SSTS_DET_PHY_OFFLINE              0x4  //Phy is in offline mode or in a BIST loopback mode

#define  SSTS_SPD_NO_DEVICE                0x0  //No device detected and PHY communication not established
#define  SSTS_SPD_GEN1_1_5G                0x1  //Generation 1 communication rate negociated
#define  SSTS_SPD_GEN2_3_0G                0x2  //Generation 2 communication rate negociated

#define  SSTS_IPM_NO_DEVICE                0x0  //No device detected and PHY communication not established
#define  SSTS_IPM_ACTIVE                   0x1  //interface in active state
#define  SSTS_IPM_PARTIAL                  0x2  //interface in Partial power management state
#define  SSTS_IPM_SLUMBER                  0x6  //interface in Slumber power management state

//! @brief PxSCTL Macros
#define  SCTL_DET_COMM_INIT                (0x1<<0) //Perform interface communication initialization sequence
#define  SCTL_DET_PHY_OFFLINE              (0x4<<0) //Disable the SATA interface and put PHY in offline mode

#define  SCTL_SPD_GEN1_NEGOCIATE           (0x1<<4) //Gen1 speed negociation
#define  SCTL_SPD_GEN2_NEGOCIATE           (0x2<<4) //Gen2 speed negociation

#define  SCTL_IPM_TRANS_TO_PARTIAL_DIS     (0x1<<8) //Transition to Partial state disabled
#define  SCTL_IPM_TRANS_TO_SLUMBER_DIS     (0x2<<8) //Transition to Slumber state disabled
#define  SCTL_IPM_TRANS_TO_BOTH_PM_DIS     (0x3<<8) //Transition to Both PM state disabled

//! @brief PxTFD Macros
#define SATA_AHCI_PORT_N_TFD_BSY           (0x1<<7)
#define SATA_AHCI_PORT_N_TFD_DRQ           (0x1<<3)
#define SATA_AHCI_PORT_N_TFD_ERR           (0x1<<0)
#define SATA_AHCI_PORT_N_TFD_MASK          (SATA_AHCI_PORT_N_TFD_BSY|SATA_AHCI_PORT_N_TFD_DRQ|SATA_AHCI_PORT_N_TFD_ERR)

//! @brief SATA PHY Control Registers
//! @brief Reset Register
#define SATA_PHY_CR_RESET                  0x7F3F
//! @brief Creg Compare Upper Limit Register
#define SATA_PHY_CR_CLOCK_CRCMP_LT_LIMIT   0x0001
//! @brief Creg Compare Lower Lim:it Register
#define SATA_PHY_CR_CLOCK_CRCMP_GT_LIMIT   0x0002
//! @brief Creg Compare Mask Register
#define SATA_PHY_CR_CLOCK_CRCMP_MASK       0x0003
//! @brief Creg Compare Control Register
#define SATA_PHY_CR_CLOCK_CRCMP_CTL        0x0004
//! @brief Creg Compare Status Register
#define SATA_PHY_CR_CLOCK_CRCMP_STAT       0x0005
//! @brief Scope Sample Count Register
#define SATA_PHY_CR_CLOCK_SCOPE_SAMPLES    0x0006
//! @brief Scope Count Result Register
#define SATA_PHY_CR_CLOCK_SCOPE_COUNT      0x0007
//! @brief DAC Control Register
#define SATA_PHY_CR_CLOCK_DAC_CTL          0x0008
//! @brief Resistor Tuning Control Register
#define SATA_PHY_CR_CLOCK_RTUNE_CTL        0x0009
//! @brief ADC Output Register
#define SATA_PHY_CR_CLOCK_ADC_OUT          0x000A
//! @brief Spread Spectrum Phase Register
#define SATA_PHY_CR_CLOCK_SS_PHASE         0x000B
//! @brief JTAG Chip ID (High Bits) Register
#define SATA_PHY_CR_CLOCK_CHIP_ID_HI       0x000C
//! @brief JTAG Chip ID (Low Bits) Register
#define SATA_PHY_CR_CLOCK_CHIP_ID_LO       0x000D
//! @brief Frequency Status Register
#define SATA_PHY_CR_CLOCK_FREQ_STAT        0x000E
//! @brief Control Status Register
#define SATA_PHY_CR_CLOCK_CTL_STAT         0x000F
//! @brief Level Status Register
#define SATA_PHY_CR_CLOCK_LVL_STAT         0x0010
//! @brief Creg Status Register
#define SATA_PHY_CR_CLOCK_CREG_STAT        0x0011
//! @brief Frequency Override Register
#define SATA_PHY_CR_CLOCK_FREQ_OVRD        0x0012
//! @brief Control Override Register
#define SATA_PHY_CR_CLOCK_CTL_OVRD         0x0013
//! @brief Level Override Register
#define SATA_PHY_CR_CLOCK_LVL_OVRD         0x0014
//! @brief Creg Override Register
#define SATA_PHY_CR_CLOCK_CREG_OVRD        0x0015
//! @brief MPLL Control Register
#define SATA_PHY_CR_CLOCK_MPLL_CTL         0x0016
//! @brief MPLL Test Register
#define SATA_PHY_CR_CLOCK_MPLL_TST         0x0017
//! @brief Clock Select Override Register
#define SATA_PHY_CR_CLOCK_SEL_OVRD         0x001A

//! @brief sata port enumeration
enum {
    PORT0 = 0,
    PORT1,
    PORT2,
    PORT3,
    PORT4,
    PORT5,
    PORT6,
    PORT7,
    PORT8,
    PORT9,
    PORT10,
    PORT11,
    PORT12,
    PORT13,
    PORT14,
    PORT15,
    PORT16,
    PORT17,
    PORT18,
    PORT19,
    PORT20,
    PORT21,
    PORT22,
    PORT23,
    PORT24,
    PORT25,
    PORT26,
    PORT27,
    PORT28,
    PORT29,
    PORT30,
    PORT31,
};

//! @brief sata return code
typedef enum SATA_RETURN {
    SATA_PASS = 0,
    SATA_FAIL = 1,
} sata_return_t;

//! @brief Enumeration of sata phy reference clock 
typedef enum sata_phy_ref_clk {
    FREQ_100MHZ = 0,
    OSC_25MHZ,
    OSC_50MHZ,
    FUSE_USB_PHY_CLK,
    CCM_PLL_ENET,
    OSC_UNKNOWN = -1,
} sata_phy_ref_clk_t;

//! @brief HDD identify data structure
typedef struct hdd_identify_data {
    u16 general_conf;           // 00    : general configuration
    u16 num_cylinders;          // 01    : number of cylinders (default CHS trans)
    u16 reserved0;              // 02    : reserved
    u16 num_heads;              // 03    : number of heads (default CHS trans)
    u16 num_ub_per_track;       // 04    : number of unformatted bytes per track
    u16 num_ub_per_sector;      // 05    : number of unformatted bytes per sector
    u16 num_sectors;            // 06    : number of sectors per track (default CHS trans)
    u16 num_card_sectors[2];    // 07-08 : number of sectors per card
    u16 reserved1;              // 09    : reserved
    u16 serial[10];             // 10-19 : serial number (string)
    u16 buffer_type;            // 20    : buffer type (dual ported)
    u16 buffer_size;            // 21    : buffer size in 512 increments
    u16 num_ECC_bytes;          // 22    : number of ECC bytes passed on R/W Long cmds
    u16 firmware_rev[4];        // 23-26 : firmware revision (string)
    u16 model_num[20];          // 27-46 : model number (string)
    u16 rw_mult_support;        // 47    : max number of sectors on R/W multiple cmds
    u16 reserved2;              // 48    : reserved
    u16 capabilities;           // 49    : LBA, DMA, IORDY support indicator
    u16 reserved3;              // 50    : reserved
    u16 pio_xferc_timing;       // 51    : PIO data transfer cycle timing mode
    u16 dma_xferc_timing;       // 52    : single word DMA data transfer cycle timing mode
    u16 cur_field_validity;     // 53    : words 54-58 validity (0 == not valid)
    u16 cur_cylinders;          // 54    : number of current cylinders
    u16 cur_heads;              // 55    : number of current heads
    u16 cur_spt;                // 56    : number of current sectors per track
    u16 cur_capacity[2];        // 57-58 : current capacity in sectors
    u16 mult_sectors;           // 59    : multiple sector setting
    u16 lba_total_sectors[2];   // 60-61 : total sectors in LBA mode
    u16 sw_dma;                 // 62    : single word DMA support
    u16 mw_dma;                 // 63    : multi word DMA support
    u16 apio_modes;             // 64    : advanced PIO transfer mode supported
    u16 min_dma_timing;         // 65    : minimum multiword DMA transfer cycle
    u16 rec_dma_timing;         // 66    : recommended multiword DMA cycle
    u16 min_pio_timing;         // 67    : min PIO transfer time without flow control
    u16 min_pio_iordy_timing;   // 68    : min PIO transfer time with IORDY flow control
    u16 reserved4[187];         // 69-255: reserved
} hdd_identify_data_t;

//! @brief sata disk identify structure
typedef struct _disk_identify_t {
    char serial[20 + 1];        // serial number
    char firmware_rev[8 + 1];   // firmware revision
    char model_num[40 + 1];     // model number
    u32 cylinders_num;          // number of cylinders         (CHS)
    u32 heads_num;              // number of heads             (CHS)
    u32 sectors_num;            // number of sectors per track (CHS)
    u32 lba_sectors_num;        // total number of sectors in LBA mode
    u32 phys_block_size;        // physical block size in sectors
    u32 max_transfer;           // Maximum transfer size in bytes
} disk_identify_t;

//! @brief sata disk information
typedef struct sata_disk_info {
    u8 port;
    u8 chan;
} sata_disk_info_t;

//! @brief sata device signature structure
typedef struct ata_dev_signature {
    u8 nsect;
    u8 lbal;
    u8 lbam;
    u8 lbah;
} ata_dev_sig_t __attribute__ ((aligned(4)));
/*
//! @brief sata AHCI registers
typedef struct sata_ahci_regs {
    //Generic Host Control 
    volatile u32 cap;           //0x00, HBA Capabilities Register
    volatile u32 ghc;           //0x04, Global HBA Control Register
    volatile u32 is;            //0x08, Interrupt Status Register
    volatile u32 pi;            //0x0c, Ports Implemented Register
    volatile u32 vs;            //0x10, AHCI Version Register
    volatile u32 ccc_ctl;       //0x14, Command Completion Coalescing Control
    volatile u32 ccc_ports;     //0x18, Command Completion Coalescing Ports
    volatile u32 rsv0[2];       //0x1c~0x23, reserved
    volatile u32 cap2;          //0x24, HBA Capabilities Extended Register
    volatile u32 rsv1[30];      //0x28~0x9f, reserved

    // Vendor Specific Registers 
    volatile u32 bistafis;      //0xa0, BIST Activate FIS Register
    volatile u32 bistctrl;      //0xa4, BIST Control Register
    volatile u32 bistfcnt;      //0xa8, BIST FIS Count Register
    volatile u32 biststs;       //0xac, BIST Status Register
    volatile u32 bistdec;       //0xb0, BIST DWORD Error Count Register
    volatile u32 rsv2[2];       //0xb4~0xbb, reserved
    volatile u32 oobr;          //0xbc, OOB Register
    volatile u32 rsv3[8];       //0xc0~0xdf, reserved
    volatile u32 timer1ms;      //0xe0, Timer 1-ms Register
    volatile u32 rsv4;          //0xe4~0xe7, reserved
    volatile u32 gparam1;       //0xe8, Global Parameter 1 Register
    volatile u32 gparam2;       //0xec, Global Parameter 2 Register
    volatile u32 pparam;        //0xf0, Port Parameter Register
    volatile u32 test;          //0xf4, Test Register
    volatile u32 version;       //0xf8, Version Register
    volatile u32 id;            //0xfc, ID Register
} sata_ahci_regs_t;

//! @brief Sata port registers
typedef struct sata_port_regs {
    volatile u32 clb;           //0x00, Command List Base Address Register
    volatile u32 clbu;          //0x04, Command List Base Address Upper 32-bit Register
    volatile u32 fb;            //0x08, FIS Base Address Register
    volatile u32 fbu;           //0x0c, FIS Base Address Upper 32-bit Register
    volatile u32 is;            //0x10, Interrupt Status Register
    volatile u32 ie;            //0x14, Interrupt Enable Register
    volatile u32 cmd;           //0x18, Command Register
    volatile u32 rsv0;          //0x1c, reserved
    volatile u32 tfd;           //0x20, Task File Data Register
    volatile u32 sig;           //0x24, Signature Register
    volatile u32 ssts;          //0x28, Serial ATA Status Register
    volatile u32 sctl;          //0x2c, Serial ATA Control Register
    volatile u32 serr;          //0x30, Serial ATA Error Register
    volatile u32 sact;          //0x34, Serial ATA Active Register
    volatile u32 ci;            //0x38, Command Issue Register
    volatile u32 sntf;          //0x3c, Serial ATA Notification Register
    volatile u32 rsv1[12];      //0x40, reserved
    volatile u32 dmacr;         //0x70, DMA Control Register
    volatile u32 rsv2;          //0x74, reserved
    volatile u32 phycr;         //0x78, PHY Control Register
    volatile u32 physr;         //0x7c, PHY Status Register
} sata_port_regs_t;
*/

typedef struct _hw_sata_port
{
    volatile hw_sata_p0clb_t CLB; //!< Port0 Command List Base Address Register
    volatile reg32_t _reserved7;
    volatile hw_sata_p0fb_t FB; //!< Port0 FIS Base Address Register
    volatile reg32_t _reserved8;
    volatile hw_sata_p0is_t IS; //!< Port0 Interrupt Status Register
    volatile hw_sata_p0ie_t IE; //!< Port0 Interrupt Enable Register
    volatile hw_sata_p0cmd_t CMD; //!< Port0 Command Register
    volatile reg32_t _reserved9;
    volatile hw_sata_p0tfd_t TFD; //!< Port0 Task File Data Register
    volatile hw_sata_p0sig_t SIG; //!< Port0 Signature Register
    volatile hw_sata_p0ssts_t SSTS; //!< Port0 Serial ATA Status Register
    volatile hw_sata_p0sctl_t SCTL; //!< Port0 Serial ATA Control {SControl} Register
    volatile hw_sata_p0serr_t SERR; //!< Port0 Serial ATA Error Register
    volatile hw_sata_p0sact_t SACT; //!< Port0 Serial ATA Active Register
    volatile hw_sata_p0ci_t CI; //!< Port0 Command Issue Register
    volatile hw_sata_p0sntf_t SNTF; //!< Port0 Serial ATA Notification Register
    volatile reg32_t _reserved10[12];
    volatile hw_sata_p0dmacr_t DMACR; //!< Port0 DMA Control Register
    volatile reg32_t _reserved11;
    volatile hw_sata_p0phycr_t PHYCR; //!< Port0 PHY Control Register
    volatile hw_sata_p0physr_t PHYSR; //!< Port0 PHY Status Register
} hw_sata_port_t;

#define HW_SATA_PORT(n) (*(hw_sata_port_t *)(HW_SATA_P0CLB_ADDR + n*0x80))

//! @brief SATA AHCI FIS Organization, 256 Bytes
typedef struct SATA_RX_FIS_STRUCT {
    u32 dsfis[7];               //@00h~1Bh, DMA Setup FIS
    u32 rsv0;                   //@1Ch~1Fh, Reserved
    u32 psfis[5];               //@20h~33h, PID Setup FIS
    u32 rsv1[2];                //@34h~3Fh, Reserved
    u32 rfis[5];                //@40h~53h, D2H Register FIS
    u32 rsv2;                   //@54h~57h, Reserved
    u32 sdbfis[2];              //@58h~5Fh, Set Device Bits FIS
    u32 ufis[16];               //@60h~9Fh, Unknown FIS
    u32 rsv3[25];               //@A0h~FFh, Reserved
} sata_rx_fis_t;

//! @brief SATA Command List Entry - Command Header, 32 Bytes
typedef struct SATA_COMMAND_HEADER_STRUCT {
    /*DW0 */
    union {
        u32 u;                  //Description Information
        struct {
            unsigned cfl:5;     //Bit4:0, Command FIS Length
            unsigned atapi:1;   //Bit5, ATAPI
            unsigned write:1;   //Bit6, Write - direction of operation
            unsigned prefetch:1;    //Bit7, Prefetchable
            unsigned reset:1;   //Bit8, Reset
            unsigned bist:1;    //Bit9, BIST
            unsigned clear:1;   //Bit10, Clear Busy upon R_OK
            unsigned rsv:1;     //Bit11, Reserved
            unsigned pmp:4;     //Bit15:12, Port Multiplier Port
            unsigned prdtl:16;  //Bit31:15, Physical Region Descriptor Table Length
        } field;
    } info;

    /*DW1 */
    u32 prdbc;                  //Physical Region Descriptor Byte Count

    /*DW2 */
    u32 ctba;                   //Command Table Descriptor Base Address, bit6~0 must be zero

    /*DW3 */
    u32 ctba_u;                 //Command Table Descriptor Base Address Upper 32bit

    /*DW4~DW7 */
    u32 rsv1[4];                //Reserved
} sata_command_header_t;

//! @brief SATA Physical Region Descriptor, 16 Bytes
typedef struct SATA_PHYSICAL_REGION_DESCRIPTOR {
    /*DW0 */
    u32 dba;                    //Data Base Address, bit0 must be zero
    /*DW1 */
    u32 dbau;                   //Data Base Address Upper 32-bits
    /*DW2 */
    u32 rsv;                    //Reserved
    /*DW3
       union
       {
       u32 u;               //Description Information
       struct
       {
       unsigned dbc :22;               //Data Byte Count, Bit 0 must be one
       unsigned rsv1: 9;               //Reserved bit
       unsigned ioc : 1;               //Interrupt On Complete
       } field;
       } info
     */
    u32 dbc_ioc;
} sata_prd_t;

//! @brief SATA Command FIS, this structure will cover all the FIS types
typedef struct SATA_COMMAND_FIS {
    u8 fisType;
    u8 pmPort_Cbit;
    u8 command;
    u8 features;
    u8 lbaLow;
    u8 lbaMid;
    u8 lbaHigh;
    u8 device;
    u8 lbaLowExp;
    u8 lbaMidExp;
    u8 lbaHighExp;
    u8 featuresExp;
    u8 sectorNum;
    u8 sectorNumExp;
    u8 rsv1;
    u8 control;
    u8 rsv2[48];
} sata_cfis_t;

//! @brief SATA Command Table
typedef struct SATA_COMMAND_TABLE {
    sata_cfis_t cfis;           //defintion of
    u32 acmd[4];                //ATAPI Command, up to 16 Bytes
    u32 rsv[12];                //64 byte reserved.
    sata_prd_t prdt;            //Base Address Physical Region Descriptor Table, max 65535 entries
    //there is only one prdt
} sata_command_table_t;

//////////////////////////////////////////////////////////////////////////////
// API
//////////////////////////////////////////////////////////////////////////////

/*!
 * @brief Initialize SATA Controller and also identify an attached hdd
 *
 * @return SATA_PASS or SATA_FAIL
 */
sata_return_t sata_init(void);

/*!
 * @brief Deinitialize SATA Controller and also identify an attached hdd
 *
 * @return SATA_PASS or SATA_FAIL
 */
sata_return_t sata_deinit(void);

/*!
 * @brief Detect the attached HDD and try to initialize it
 *
 * @param port        - SATA port
 * @return SATA_PASS or SATA_FAIL
 */
sata_return_t sata_identify(u32 port);


/*!
 * @brief Write some sectors to SATA disk with r/w thread
 *
 * @param start_block - Address of start sector
 * @param buf         - Pointer of destination buffer
 * @param len         - Length to read
 * @param port        - SATA port
 * @return SATA_PASS or SATA_FAIL
 */
sata_return_t sata_disk_write_sector(u32 start_block, u8 * buf, u32 len, u32 port);

/*!
 * @brief Read some sectors to SATA disk with r/w thread
 *
 * @param start_block    - Address of start sector
 * @param buf            - Pointer of destination buffer
 * @param len            - Length to read
 *  * @param port        - SATA port
 * @return SATA_PASS or SATA_FAIL
 */
sata_return_t sata_disk_read_sector(u32 start_block, u8 * buf, u32 len, u32 port);

/*!
 * @brief Print out buffer data
 *
 * @param buff Address of the buffer
 * @param size Buffer size
 * @param enable Print or not
 */
void printf_buffer(u32 buff, u32 size, u32 enable);

//! @}

#endif

//////////////////////////////////////////////////////////////////////////////
// EOF
//////////////////////////////////////////////////////////////////////////////
