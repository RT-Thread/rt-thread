#ifndef __FW_HEADER_H__
#define __FW_HEADER_H__

#include "stdint.h"
#include "stdio.h"

struct __attribute__((packed, aligned(4))) spi_flash_cfg_t {
    uint8_t ioMode;               /*!< Serail flash interface mode,bit0-3:IF mode,bit4:unwrap */
    uint8_t cReadSupport;         /*!< Support continuous read mode,bit0:continuous read mode support,bit1:read mode cfg */
    uint8_t clkDelay;             /*!< SPI clock delay,bit0-3:delay,bit4-6:pad delay */
    uint8_t clkInvert;            /*!< SPI clock phase invert,bit0:clck invert,bit1:rx invert,bit2-4:pad delay,bit5-7:pad delay */
    uint8_t resetEnCmd;           /*!< Flash enable reset command */
    uint8_t resetCmd;             /*!< Flash reset command */
    uint8_t resetCreadCmd;        /*!< Flash reset continuous read command */
    uint8_t resetCreadCmdSize;    /*!< Flash reset continuous read command size */
    uint8_t jedecIdCmd;           /*!< JEDEC ID command */
    uint8_t jedecIdCmdDmyClk;     /*!< JEDEC ID command dummy clock */
    uint8_t enter32BitsAddrCmd;   /*!< Enter 32-bits addr command */
    uint8_t exit32BitsAddrCmd;    /*!< Exit 32-bits addr command */
    uint8_t sectorSize;           /*!< *1024bytes */
    uint8_t mid;                  /*!< Manufacturer ID */
    uint16_t pageSize;            /*!< Page size */
    uint8_t chipEraseCmd;         /*!< Chip erase cmd */
    uint8_t sectorEraseCmd;       /*!< Sector erase command */
    uint8_t blk32EraseCmd;        /*!< Block 32K erase command,some Micron not support */
    uint8_t blk64EraseCmd;        /*!< Block 64K erase command */
    uint8_t writeEnableCmd;       /*!< Need before every erase or program */
    uint8_t pageProgramCmd;       /*!< Page program cmd */
    uint8_t qpageProgramCmd;      /*!< QIO page program cmd */
    uint8_t qppAddrMode;          /*!< QIO page program address mode */
    uint8_t fastReadCmd;          /*!< Fast read command */
    uint8_t frDmyClk;             /*!< Fast read command dummy clock */
    uint8_t qpiFastReadCmd;       /*!< QPI fast read command */
    uint8_t qpiFrDmyClk;          /*!< QPI fast read command dummy clock */
    uint8_t fastReadDoCmd;        /*!< Fast read dual output command */
    uint8_t frDoDmyClk;           /*!< Fast read dual output command dummy clock */
    uint8_t fastReadDioCmd;       /*!< Fast read dual io comamnd */
    uint8_t frDioDmyClk;          /*!< Fast read dual io command dummy clock */
    uint8_t fastReadQoCmd;        /*!< Fast read quad output comamnd */
    uint8_t frQoDmyClk;           /*!< Fast read quad output comamnd dummy clock */
    uint8_t fastReadQioCmd;       /*!< Fast read quad io comamnd */
    uint8_t frQioDmyClk;          /*!< Fast read quad io comamnd dummy clock */
    uint8_t qpiFastReadQioCmd;    /*!< QPI fast read quad io comamnd */
    uint8_t qpiFrQioDmyClk;       /*!< QPI fast read QIO dummy clock */
    uint8_t qpiPageProgramCmd;    /*!< QPI program command */
    uint8_t writeVregEnableCmd;   /*!< Enable write reg */
    uint8_t wrEnableIndex;        /*!< Write enable register index */
    uint8_t qeIndex;              /*!< Quad mode enable register index */
    uint8_t busyIndex;            /*!< Busy status register index */
    uint8_t wrEnableBit;          /*!< Write enable bit pos */
    uint8_t qeBit;                /*!< Quad enable bit pos */
    uint8_t busyBit;              /*!< Busy status bit pos */
    uint8_t wrEnableWriteRegLen;  /*!< Register length of write enable */
    uint8_t wrEnableReadRegLen;   /*!< Register length of write enable status */
    uint8_t qeWriteRegLen;        /*!< Register length of contain quad enable */
    uint8_t qeReadRegLen;         /*!< Register length of contain quad enable status */
    uint8_t releasePowerDown;     /*!< Release power down command */
    uint8_t busyReadRegLen;       /*!< Register length of contain busy status */
    uint8_t readRegCmd[4];        /*!< Read register command buffer */
    uint8_t writeRegCmd[4];       /*!< Write register command buffer */
    uint8_t enterQpi;             /*!< Enter qpi command */
    uint8_t exitQpi;              /*!< Exit qpi command */
    uint8_t cReadMode;            /*!< Config data for continuous read mode */
    uint8_t cRExit;               /*!< Config data for exit continuous read mode */
    uint8_t burstWrapCmd;         /*!< Enable burst wrap command */
    uint8_t burstWrapCmdDmyClk;   /*!< Enable burst wrap command dummy clock */
    uint8_t burstWrapDataMode;    /*!< Data and address mode for this command */
    uint8_t burstWrapData;        /*!< Data to enable burst wrap */
    uint8_t deBurstWrapCmd;       /*!< Disable burst wrap command */
    uint8_t deBurstWrapCmdDmyClk; /*!< Disable burst wrap command dummy clock */
    uint8_t deBurstWrapDataMode;  /*!< Data and address mode for this command */
    uint8_t deBurstWrapData;      /*!< Data to disable burst wrap */
    uint16_t timeEsector;         /*!< 4K erase time */
    uint16_t timeE32k;            /*!< 32K erase time */
    uint16_t timeE64k;            /*!< 64K erase time */
    uint16_t timePagePgm;         /*!< Page program time */
    uint16_t timeCe;              /*!< Chip erase time in ms */
    uint8_t pdDelay;              /*!< Release power down command delay time for wake up */
    uint8_t qeData;               /*!< QE set data */
};

struct __attribute__((packed, aligned(4))) boot_flash_cfg_t {
    uint32_t magiccode;
    struct spi_flash_cfg_t cfg;
    uint32_t crc32;
};

struct __attribute__((packed, aligned(4))) sys_clk_cfg_t {
    uint8_t xtal_type;
    uint8_t mcu_clk;
    uint8_t mcu_clk_div;
    uint8_t mcu_bclk_div;

    uint8_t mcu_pbclk_div;
    uint8_t emi_clk;
    uint8_t emi_clk_div;
    uint8_t flash_clk_type;

    uint8_t flash_clk_div;
    uint8_t wifipll_pu;
    uint8_t aupll_pu;
    uint8_t rsvd0;
};

struct __attribute__((packed, aligned(4))) boot_clk_cfg_t {
    uint32_t magiccode;
    struct sys_clk_cfg_t cfg;
    uint32_t crc32;
};

struct __attribute__((packed, aligned(4))) boot_basic_cfg_t {
    uint32_t sign_type          : 2; /* [1: 0]   for sign */
    uint32_t encrypt_type       : 2; /* [3: 2]   for encrypt */
    uint32_t key_sel            : 2; /* [5: 4]   key slot */
    uint32_t xts_mode           : 1; /* [6]      for xts mode */
    uint32_t aes_region_lock    : 1; /* [7]      rsvd */
    uint32_t no_segment         : 1; /* [8]      no segment info */
    uint32_t rsvd_0             : 1; /* [9]      boot2 enable(rsvd_0) */
    uint32_t rsvd_1             : 1; /* [10]     boot2 rollback(rsvd_1) */
    uint32_t cpu_master_id      : 4; /* [14: 11] master id */
    uint32_t notload_in_bootrom : 1; /* [15]     notload in bootrom */
    uint32_t crc_ignore         : 1; /* [16]     ignore crc */
    uint32_t hash_ignore        : 1; /* [17]     hash ignore */
    uint32_t power_on_mm        : 1; /* [18]     power on mm */
    uint32_t em_sel             : 3; /* [21: 19] em_sel */
    uint32_t cmds_en            : 1; /* [22]     command spliter enable */
    uint32_t cmds_wrap_mode     : 2; /* [24: 23] cmds wrap mode */
    uint32_t cmds_wrap_len      : 4; /* [28: 25] cmds wrap len */
    uint32_t icache_invalid     : 1; /* [29] icache invalid */
    uint32_t dcache_invalid     : 1; /* [30] dcache invalid */
    uint32_t rsvd_3             : 1; /* [31] rsvd_3 */

    uint32_t group_image_offset; /* flash controller offset */
    uint32_t aes_region_len;     /* aes region length */

    uint32_t img_len_cnt;  /* image length or segment count */
    uint32_t hash[32 / 4]; /* hash of the image */
};

struct __attribute__((packed, aligned(4))) boot_cpu_cfg_t {
    uint8_t config_enable;     /* coinfig this cpu */
    uint8_t halt_cpu;          /* halt this cpu */
    uint8_t cache_enable  : 1; /* cache setting */
    uint8_t cache_wa      : 1; /* cache setting */
    uint8_t cache_wb      : 1; /* cache setting */
    uint8_t cache_wt      : 1; /* cache setting */
    uint8_t cache_way_dis : 4; /* cache setting */
    uint8_t rsvd;

    uint32_t image_address_offset; /* image_address_offset */
    uint32_t rsvd1;                /* rsvd */
    uint32_t msp_val;              /* msp value */
};

struct __attribute__((packed, aligned(4))) aesiv_cfg_t {
    uint8_t aesiv[16];
    uint32_t crc32;
};

struct __attribute__((packed, aligned(4))) pkey_cfg_t {
    uint8_t eckeyx[32]; /* ec key in boot header */
    uint8_t eckeyy[32]; /* ec key in boot header */
    uint32_t crc32;
};

struct __attribute__((packed, aligned(4))) sign_cfg_t {
    uint32_t sig_len;
    uint8_t signature[32];
    uint32_t crc32;
};

struct __attribute__((packed, aligned(4))) bootheader_t {
    uint32_t magiccode; /* 4 */
    uint32_t rivison;   /* 4 */

    struct boot_flash_cfg_t flash_cfg; /* 4 + 84 + 4 */
    struct boot_clk_cfg_t clk_cfg;     /* 4 + 12 + 4 */

    struct boot_basic_cfg_t basic_cfg; /* 4 + 4 + 4 + 4 + 4*8 */

    struct boot_cpu_cfg_t cpu_cfg; /* 16 */

    uint32_t boot2_pt_table_0_rsvd; /* address of partition table 0 */ /* 4 */
    uint32_t boot2_pt_table_1_rsvd; /* address of partition table 1 */ /* 4 */

    uint32_t flash_cfg_table_addr; /* address of flashcfg table list */ /* 4 */
    uint32_t flash_cfg_table_len; /* flashcfg table list len */         /* 4 */

    uint32_t rsvd0[6]; /* rsvd */
    uint32_t rsvd1[6]; /* rsvd */

    uint32_t rsvd; /* 4 */

    uint32_t crc32; /* 4 */
};

#endif
