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
    .flash_cfg.cfg.mid = 0x00,                  /*!< Manufacturer ID */
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
    .flash_cfg.cfg.cReadMode = 0x20,            /*!< Config data for continuous read mode */
    .flash_cfg.cfg.cRExit = 0xf0,               /*!< Config data for exit continuous read mode */
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
    .clk_cfg.cfg.xtal_type = 0x07, /*!<  0:None,1:24M,2:32M,3:38.4M,4:40M,5:26M,6:RC32M  */
    .clk_cfg.cfg.mcu_clk = 0x04,   /*!< mcu_clk 0:RC32M,1:Xtal,2:cpupll 400M,3:wifipll 192M,4:wifipll 320M */
    .clk_cfg.cfg.mcu_clk_div = 0x00,
    .clk_cfg.cfg.mcu_bclk_div = 0x00,

    .clk_cfg.cfg.mcu_pbclk_div = 0x03,
    .clk_cfg.cfg.lp_div = 0x01,
    .clk_cfg.cfg.dsp_clk = 0x03, /* 0:RC32M,1:Xtal,2:wifipll 240M,3:wifipll 320M,4:cpupll 400M */
    .clk_cfg.cfg.dsp_clk_div = 0x00,

    .clk_cfg.cfg.dsp_bclk_div = 0x01,
    .clk_cfg.cfg.dsp_pbclk = 0x02, /* 0:RC32M,1:Xtal,2:wifipll 160M,3:cpupll 160M,4:wifipll 240M */
    .clk_cfg.cfg.dsp_pbclk_div = 0x00,
    .clk_cfg.cfg.emi_clk = 0x02, /*!<  0:mcu pbclk,1:cpupll 200M,2:wifipll 320M,3:cpupll 400M */

    .clk_cfg.cfg.emi_clk_div = 0x01,
    .clk_cfg.cfg.flash_clk_type = 0x01, /*!< 0:wifipll 120M,1:xtal,2:cpupll 100M,3:wifipll 80M,4:bclk,5:wifipll 96M */
    .clk_cfg.cfg.flash_clk_div = 0x00,
    .clk_cfg.cfg.wifipll_pu = 0x01,

    .clk_cfg.cfg.aupll_pu = 0x01,
    .clk_cfg.cfg.cpupll_pu = 0x01,
    .clk_cfg.cfg.mipipll_pu = 0x01,
    .clk_cfg.cfg.uhspll_pu = 0x01,

    .clk_cfg.crc32 = 0xdeadbeef,

    /* basic cfg */
    .basic_cfg.sign_type = 0x0,          /* [1: 0]   for sign */
    .basic_cfg.encrypt_type = 0x0,       /* [3: 2]   for encrypt */
    .basic_cfg.key_sel = 0x0,            /* [5: 4]   key slot */
    .basic_cfg.xts_mode = 0x0,           /* [6]      for xts mode */
    .basic_cfg.aes_region_lock = 0x0,    /* [7]      rsvd */
    .basic_cfg.no_segment = 0x1,         /* [8]      no segment info */
    .basic_cfg.rsvd_0 = 0x0,             /* [9]      boot2 enable(rsvd_0) */
    .basic_cfg.rsvd_1 = 0x0,             /* [10]     boot2 rollback(rsvd_1) */
    .basic_cfg.cpu_master_id = 0x0,      /* [14: 11] master id */
    .basic_cfg.notload_in_bootrom = 0x0, /* [15]     notload in bootrom */
    .basic_cfg.crc_ignore = 0x1,         /* [16]     ignore crc */
    .basic_cfg.hash_ignore = 0x1,        /* [17]     hash ignore */
    .basic_cfg.power_on_mm = 0x1,        /* [18]     power on mm */
    .basic_cfg.em_sel = 0x1,             /* [21: 19] em_sel */
    .basic_cfg.cmds_en = 0x1,            /* [22]     command spliter enable */
#if 0
# 0 : cmds bypass wrap commands to macro, original mode;
# 1 : cmds handle wrap commands, original mode;
# 2 : cmds bypass wrap commands to macro, cmds force wrap16 * 4 splitted into two wrap8 * 4;
# 3 : cmds handle wrap commands, cmds force wrap16 * 4 splitted into two wrap8 * 4
#endif
    .basic_cfg.cmds_wrap_mode = 0x1, /* [24: 23] cmds wrap mode */
#if 0
# 0 : SF_CTRL_WRAP_LEN_8, 1 : SF_CTRL_WRAP_LEN_16, 2 : SF_CTRL_WRAP_LEN_32,
# 3 : SF_CTRL_WRAP_LEN_64, 9 : SF_CTRL_WRAP_LEN_4096
#endif
    .basic_cfg.cmds_wrap_len = 0x9,  /* [28: 25] cmds wrap len */
    .basic_cfg.icache_invalid = 0x1, /* [29] icache invalid */
    .basic_cfg.dcache_invalid = 0x1, /* [30] dcache invalid */
    .basic_cfg.rsvd_3 = 0x0,         /* [31] rsvd_3 */

#ifdef BFLB_BOOT2
    .basic_cfg.group_image_offset = 0x00002000, /* flash controller offset */
#else
    .basic_cfg.group_image_offset = 0x00001000, /* flash controller offset */
#endif
    .basic_cfg.aes_region_len = 0x00000000,     /* aes region length */

    .basic_cfg.img_len_cnt = 0x00010000, /* image length or segment count */
    .basic_cfg.hash = { 0xdeadbeef },    /* hash of the image */

    /* cpu cfg */
    .cpu_cfg[0].config_enable = 0x01, /* coinfig this cpu */
    .cpu_cfg[0].halt_cpu = 0x0,       /* halt this cpu */
    .cpu_cfg[0].cache_enable = 0x0,   /* cache setting :only for BL Cache */
    .cpu_cfg[0].cache_wa = 0x0,       /* cache setting :only for BL Cache*/
    .cpu_cfg[0].cache_wb = 0x0,       /* cache setting :only for BL Cache*/
    .cpu_cfg[0].cache_wt = 0x0,       /* cache setting :only for BL Cache*/
    .cpu_cfg[0].cache_way_dis = 0x0,  /* cache setting :only for BL Cache*/
    .cpu_cfg[0].rsvd = 0x0,

    .cpu_cfg[0].cache_range_h = 0x00000000,
    .cpu_cfg[0].cache_range_l = 0x00000000,
    /* image_address_offset */
    .cpu_cfg[0].image_address_offset = 0x0,
    .cpu_cfg[0].rsvd0 = 0x58000000,   /* rsvd0 */
    .cpu_cfg[0].msp_val = 0x00000000, /* msp value */

    /* cpu cfg */
    .cpu_cfg[1].config_enable = 0x0, /* coinfig this cpu */
    .cpu_cfg[1].halt_cpu = 0x0,      /* halt this cpu */
    .cpu_cfg[1].cache_enable = 0x0,  /* cache setting :only for BL Cache */
    .cpu_cfg[1].cache_wa = 0x0,      /* cache setting :only for BL Cache*/
    .cpu_cfg[1].cache_wb = 0x0,      /* cache setting :only for BL Cache*/
    .cpu_cfg[1].cache_wt = 0x0,      /* cache setting :only for BL Cache*/
    .cpu_cfg[1].cache_way_dis = 0x0, /* cache setting :only for BL Cache*/
    .cpu_cfg[1].rsvd = 0x0,

    .cpu_cfg[1].cache_range_h = 0x00000000,
    .cpu_cfg[1].cache_range_l = 0x00000000,
    /* image_address_offset */
    .cpu_cfg[1].image_address_offset = 0x0,
    .cpu_cfg[1].rsvd0 = 0x58000000,   /* rsvd0 */
    .cpu_cfg[1].msp_val = 0x00000000, /* msp value */

    /* address of partition table 0 */ /* 4 */
    .boot2_pt_table_0_rsvd = 0x00000000,
    /* address of partition table 1 */ /* 4 */
    .boot2_pt_table_1_rsvd = 0x00000000,

    /* address of flashcfg table list */ /* 4 */
    .flash_cfg_table_addr = 0x00000000,
    /* flashcfg table list len */ /* 4 */
    .flash_cfg_table_len = 0x00000000,

    .rsvd1[0] = 0x20000320,
    .rsvd1[1] = 0x00000000,
    .rsvd1[2] = 0x2000F038,
    .rsvd1[3] = 0x18000000,

    .crc32 = 0xdeadbeef /* 4 */
};
