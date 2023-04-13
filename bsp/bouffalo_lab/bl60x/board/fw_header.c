#include "fw_header.h"

__attribute__((section(".fw_header"))) struct bootheader_t fw_header = {
    .magiccode = 0x504e4642,
    .rivison = 0x00000001,
    /*flash config */
    .flash_cfg.magiccode = 0x47464346,
    .flash_cfg.cfg.ioMode = 0x11,               /*!< Serail flash interface mode,bit0-3:IF mode,bit4:unwrap */
    .flash_cfg.cfg.cReadSupport = 0x00,         /*!< Support continuous read mode,bit0:continuous read mode support,bit1:read mode cfg */
    .flash_cfg.cfg.clkDelay = 0x01,             /*!< SPI clock delay,bit0-3:delay,bit4-6:pad delay */
    .flash_cfg.cfg.clkInvert = 0x01,            /*!< SPI clock phase invert,bit0:clck invert,bit1:rx invert,bit2-4:pad delay,bit5-7:pad delay */
    .flash_cfg.cfg.resetEnCmd = 0x66,           /*!< Flash enable reset command */
    .flash_cfg.cfg.resetCmd = 0x99,             /*!< Flash reset command */
    .flash_cfg.cfg.resetCreadCmd = 0xff,        /*!< Flash reset continuous read command */
    .flash_cfg.cfg.resetCreadCmdSize = 0x03,    /*!< Flash reset continuous read command size */
    .flash_cfg.cfg.jedecIdCmd = 0x9f,           /*!< JEDEC ID command */
    .flash_cfg.cfg.jedecIdCmdDmyClk = 0x00,     /*!< JEDEC ID command dummy clock */
    .flash_cfg.cfg.enter32BitsAddrCmd = 0xb7,   /*!< Enter 32-bits addr command */
    .flash_cfg.cfg.exit32BitsAddrCmd = 0xe9,    /*!< Exit 32-bits addr command */
    .flash_cfg.cfg.sectorSize = 0x04,           /*!< *1024bytes */
    .flash_cfg.cfg.mid = 0xff,                  /*!< Manufacturer ID */
    .flash_cfg.cfg.pageSize = 0x100,            /*!< Page size */
    .flash_cfg.cfg.chipEraseCmd = 0xc7,         /*!< Chip erase cmd */
    .flash_cfg.cfg.sectorEraseCmd = 0x20,       /*!< Sector erase command */
    .flash_cfg.cfg.blk32EraseCmd = 0x52,        /*!< Block 32K erase command,some Micron not support */
    .flash_cfg.cfg.blk64EraseCmd = 0xd8,        /*!< Block 64K erase command */
    .flash_cfg.cfg.writeEnableCmd = 0x06,       /*!< Need before every erase or program */
    .flash_cfg.cfg.pageProgramCmd = 0x02,       /*!< Page program cmd */
    .flash_cfg.cfg.qpageProgramCmd = 0x32,      /*!< QIO page program cmd */
    .flash_cfg.cfg.qppAddrMode = 0x00,          /*!< QIO page program address mode */
    .flash_cfg.cfg.fastReadCmd = 0x0b,          /*!< Fast read command */
    .flash_cfg.cfg.frDmyClk = 0x01,             /*!< Fast read command dummy clock */
    .flash_cfg.cfg.qpiFastReadCmd = 0x0b,       /*!< QPI fast read command */
    .flash_cfg.cfg.qpiFrDmyClk = 0x01,          /*!< QPI fast read command dummy clock */
    .flash_cfg.cfg.fastReadDoCmd = 0x3b,        /*!< Fast read dual output command */
    .flash_cfg.cfg.frDoDmyClk = 0x01,           /*!< Fast read dual output command dummy clock */
    .flash_cfg.cfg.fastReadDioCmd = 0xbb,       /*!< Fast read dual io comamnd */
    .flash_cfg.cfg.frDioDmyClk = 0x00,          /*!< Fast read dual io command dummy clock */
    .flash_cfg.cfg.fastReadQoCmd = 0x6b,        /*!< Fast read quad output comamnd */
    .flash_cfg.cfg.frQoDmyClk = 0x01,           /*!< Fast read quad output comamnd dummy clock */
    .flash_cfg.cfg.fastReadQioCmd = 0xeb,       /*!< Fast read quad io comamnd */
    .flash_cfg.cfg.frQioDmyClk = 0x02,          /*!< Fast read quad io comamnd dummy clock */
    .flash_cfg.cfg.qpiFastReadQioCmd = 0xeb,    /*!< QPI fast read quad io comamnd */
    .flash_cfg.cfg.qpiFrQioDmyClk = 0x02,       /*!< QPI fast read QIO dummy clock */
    .flash_cfg.cfg.qpiPageProgramCmd = 0x02,    /*!< QPI program command */
    .flash_cfg.cfg.writeVregEnableCmd = 0x50,   /*!< Enable write reg */
    .flash_cfg.cfg.wrEnableIndex = 0x00,        /*!< Write enable register index */
    .flash_cfg.cfg.qeIndex = 0x01,              /*!< Quad mode enable register index */
    .flash_cfg.cfg.busyIndex = 0x00,            /*!< Busy status register index */
    .flash_cfg.cfg.wrEnableBit = 0x01,          /*!< Write enable bit pos */
    .flash_cfg.cfg.qeBit = 0x01,                /*!< Quad enable bit pos */
    .flash_cfg.cfg.busyBit = 0x00,              /*!< Busy status bit pos */
    .flash_cfg.cfg.wrEnableWriteRegLen = 0x02,  /*!< Register length of write enable */
    .flash_cfg.cfg.wrEnableReadRegLen = 0x01,   /*!< Register length of write enable status */
    .flash_cfg.cfg.qeWriteRegLen = 0x02,        /*!< Register length of contain quad enable */
    .flash_cfg.cfg.qeReadRegLen = 0x01,         /*!< Register length of contain quad enable status */
    .flash_cfg.cfg.releasePowerDown = 0xab,     /*!< Release power down command */
    .flash_cfg.cfg.busyReadRegLen = 0x01,       /*!< Register length of contain busy status */
    .flash_cfg.cfg.readRegCmd[0] = 0x05,        /*!< Read register command buffer */
    .flash_cfg.cfg.readRegCmd[1] = 0x35,        /*!< Read register command buffer */
    .flash_cfg.cfg.readRegCmd[2] = 0x00,        /*!< Read register command buffer */
    .flash_cfg.cfg.readRegCmd[3] = 0x00,        /*!< Read register command buffer */
    .flash_cfg.cfg.writeRegCmd[0] = 0x01,       /*!< Write register command buffer */
    .flash_cfg.cfg.writeRegCmd[1] = 0x01,       /*!< Write register command buffer */
    .flash_cfg.cfg.writeRegCmd[2] = 0x00,       /*!< Write register command buffer */
    .flash_cfg.cfg.writeRegCmd[3] = 0x00,       /*!< Write register command buffer */
    .flash_cfg.cfg.enterQpi = 0x38,             /*!< Enter qpi command */
    .flash_cfg.cfg.exitQpi = 0xff,              /*!< Exit qpi command */
    .flash_cfg.cfg.cReadMode = 0xa0,            /*!< Config data for continuous read mode */
    .flash_cfg.cfg.cRExit = 0xff,               /*!< Config data for exit continuous read mode */
    .flash_cfg.cfg.burstWrapCmd = 0x77,         /*!< Enable burst wrap command */
    .flash_cfg.cfg.burstWrapCmdDmyClk = 0x03,   /*!< Enable burst wrap command dummy clock */
    .flash_cfg.cfg.burstWrapDataMode = 0x02,    /*!< Data and address mode for this command */
    .flash_cfg.cfg.burstWrapData = 0x40,        /*!< Data to enable burst wrap */
    .flash_cfg.cfg.deBurstWrapCmd = 0x77,       /*!< Disable burst wrap command */
    .flash_cfg.cfg.deBurstWrapCmdDmyClk = 0x03, /*!< Disable burst wrap command dummy clock */
    .flash_cfg.cfg.deBurstWrapDataMode = 0x02,  /*!< Data and address mode for this command */
    .flash_cfg.cfg.deBurstWrapData = 0xf0,      /*!< Data to disable burst wrap */
    .flash_cfg.cfg.timeEsector = 300,           /*!< 4K erase time */
    .flash_cfg.cfg.timeE32k = 1200,             /*!< 32K erase time */
    .flash_cfg.cfg.timeE64k = 1200,             /*!< 64K erase time */
    .flash_cfg.cfg.timePagePgm = 50,            /*!< Page program time */
    .flash_cfg.cfg.timeCe = 30000,              /*!< Chip erase time in ms */
    .flash_cfg.cfg.pdDelay = 20,                /*!< Release power down command delay time for wake up */
    .flash_cfg.cfg.qeData = 0,                  /*!< QE set data */
    .flash_cfg.crc32 = 0xdeadbeef,
    /* clock cfg */
    .clk_cfg.magiccode = 0x47464350,
    .clk_cfg.cfg.xtal_type = 0x04, /*!<  0:None,1:24M,2:32M,3:38.4M,4:40M,5:26M,6:RC32M  */
    .clk_cfg.cfg.pll_clk = 0x04,   /*!< mcu_clk 0:RC32M,1:XTAL,2:PLL 48M,3:PLL 120M,4:PLL 160M,5:PLL 192M */
    .clk_cfg.cfg.hclk_div = 0x00,
    .clk_cfg.cfg.bclk_div = 0x01,
    .clk_cfg.cfg.flash_clk_type = 0x03, /*!< 0:120M,1:XCLK(RC32M or XTAL),2:48M,3:80M,4:BCLK,5:96M */
    .clk_cfg.cfg.flash_clk_div = 0x01,
    .clk_cfg.crc32 = 0xdeadbeef,

    /* boot cfg */
    .boot_cfg.bval.sign = 0x0,               /* [1: 0]      for sign*/
    .boot_cfg.bval.encrypt_type = 0x0,       /* [3: 2]      for encrypt */
    .boot_cfg.bval.key_sel = 0x0,            /* [5: 4]      for key sel in boot interface*/
    .boot_cfg.bval.rsvd6_7 = 0x0,            /* [7: 6]      for encrypt*/
    .boot_cfg.bval.no_segment = 0x1,         /* [8]         no segment info */
    .boot_cfg.bval.cache_select = 0x1,       /* [9]         for cache */
    .boot_cfg.bval.notload_in_bootrom = 0x0, /* [10]        not load this img in bootrom */
    .boot_cfg.bval.aes_region_lock = 0x0,    /* [11]        aes region lock */
    .boot_cfg.bval.cache_way_disable = 0x3,  /* [15: 12]    cache way disable info*/
    .boot_cfg.bval.crc_ignore = 0x1,         /* [16]        ignore crc */
    .boot_cfg.bval.hash_ignore = 0x1,        /* [17]        hash crc */
    .boot_cfg.bval.halt_ap = 0x0,            /* [18]        halt ap */
    .boot_cfg.bval.rsvd19_31 = 0x0,          /* [31:19]     rsvd */

    .img_segment_info.img_len = 0x00010000, /* image length or segment count */
    .rsvd0 = 0x00000000,
#ifdef BFLB_BOOT2
    .img_start.flashoffset = 0x00002000, /* flash controller offset */
#else
    .img_start.flashoffset = 0x00001000, /* flash controller offset */
#endif
    .hash = { 0xdeadbeef },              /* hash of the image */

    .crc32 = 0xdeadbeef /* 4 */
};
