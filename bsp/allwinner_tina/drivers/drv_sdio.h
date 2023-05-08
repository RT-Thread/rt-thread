/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-08     RT-Thread    the first version
 */
#ifndef __DRV_SDIO_H__
#define __DRV_SDIO_H__


#define MMC0_BASE_ADDR     0x01C0F000
#define MMC1_BASE_ADDR     0x01C10000

struct tina_mmc
{
    volatile rt_uint32_t gctl_reg;            /* (0x000) */
    volatile rt_uint32_t ckcr_reg;            /* (0x004) */
    volatile rt_uint32_t tmor_reg;            /* (0x008) */
    volatile rt_uint32_t bwdr_reg;            /* (0x00C) */
    volatile rt_uint32_t bksr_reg;            /* (0x010) */
    volatile rt_uint32_t bycr_reg;            /* (0x014) */
    volatile rt_uint32_t cmdr_reg;            /* (0x018) */
    volatile rt_uint32_t cagr_reg;            /* (0x01C) */
    volatile rt_uint32_t resp0_reg;           /* (0x020) */
    volatile rt_uint32_t resp1_reg;           /* (0x024) */
    volatile rt_uint32_t resp2_reg;           /* (0x028) */
    volatile rt_uint32_t resp3_reg;           /* (0x02C) */
    volatile rt_uint32_t imkr_reg;            /* (0x030) */
    volatile rt_uint32_t misr_reg;            /* (0x034) */
    volatile rt_uint32_t risr_reg;            /* (0x038) */
    volatile rt_uint32_t star_reg;            /* (0x03C) */
    volatile rt_uint32_t fwlr_reg;            /* (0x040) */
    volatile rt_uint32_t funs_reg;            /* (0x044) */
    volatile rt_uint32_t cbcr_reg;            /* (0x048) */
    volatile rt_uint32_t bbcr_reg;            /* (0x04C) */
    volatile rt_uint32_t dbgc_reg;            /* (0x050) */
    volatile rt_uint32_t reserved0;
    volatile rt_uint32_t a12a_reg;            /* (0x058) */
    volatile rt_uint32_t reserved1[7];
    volatile rt_uint32_t hwrst_reg;           /* (0x078) */
    volatile rt_uint32_t reserved2;
    volatile rt_uint32_t dmac_reg;            /* (0x080) */
    volatile rt_uint32_t dlba_reg;            /* (0x084) */
    volatile rt_uint32_t idst_reg;            /* (0x088) */
    volatile rt_uint32_t idie_reg;            /* (0x08C) */
    volatile rt_uint32_t chda_reg;            /* (0x090) */
    volatile rt_uint32_t cbda_reg;            /* (0x094) */
    volatile rt_uint32_t reserved3[26];
    volatile rt_uint32_t card_thldc_reg;      /* (0x100) */
    volatile rt_uint32_t reserved4[2];
    volatile rt_uint32_t emmc_dsbd_reg;       /* (0x10c) */
    volatile rt_uint32_t reserved5[12];
    volatile rt_uint32_t reserved6[48];
    volatile rt_uint32_t fifo_reg;            /* (0x200) */
};

typedef struct tina_mmc *tina_mmc_t;

#define MMC0    ((tina_mmc_t)MMC0_BASE_ADDR)
#define MMC1    ((tina_mmc_t)MMC1_BASE_ADDR)


#define BIT(x)              (1UL<<(x))
/* Struct for Intrrrupt Information */
#define SDXC_RespErr        BIT(1)  //0x2
#define SDXC_CmdDone        BIT(2)  //0x4
#define SDXC_DataOver       BIT(3)  //0x8
#define SDXC_TxDataReq      BIT(4)  //0x10
#define SDXC_RxDataReq      BIT(5)  //0x20
#define SDXC_RespCRCErr     BIT(6)  //0x40
#define SDXC_DataCRCErr     BIT(7)  //0x80
#define SDXC_RespTimeout    BIT(8)  //0x100
#define SDXC_ACKRcv         BIT(8)  //0x100
#define SDXC_DataTimeout    BIT(9)  //0x200
#define SDXC_BootStart      BIT(9)  //0x200
#define SDXC_DataStarve     BIT(10) //0x400
#define SDXC_VolChgDone     BIT(10) //0x400
#define SDXC_FIFORunErr     BIT(11) //0x800
#define SDXC_HardWLocked    BIT(12) //0x1000
#define SDXC_StartBitErr    BIT(13) //0x2000
#define SDXC_AutoCMDDone    BIT(14) //0x4000
#define SDXC_EndBitErr      BIT(15) //0x8000
#define SDXC_SDIOInt        BIT(16) //0x10000
#define SDXC_CardInsert     BIT(30) //0x40000000
#define SDXC_CardRemove     BIT(31) //0x80000000
#define SDXC_IntErrBit      (SDXC_RespErr | SDXC_RespCRCErr | SDXC_DataCRCErr \
                            | SDXC_RespTimeout | SDXC_DataTimeout | SDXC_FIFORunErr \
                            | SDXC_HardWLocked | SDXC_StartBitErr | SDXC_EndBitErr)  //0xbfc2

/*
    SD CMD reg
REG[0-5] : Cmd ID
REG[6]   : Has response
REG[7]   : Long response
REG[8]   : Check response CRC
REG[9]   : Has data
REG[10]  : Write
REG[11]  : Steam mode
REG[12]  : Auto stop
REG[13]  : Wait previous over
REG[14]  : About cmd
REG[15]  : Send initialization
REG[21]  : Update clock
REG[31]  : Load cmd
*/
#define SDXC_RESPONSE_CMD        BIT(6)
#define SDXC_LONG_RESPONSE_CMD   BIT(7)
#define SDXC_CHECK_CRC_CMD       BIT(8)
#define SDXC_HAS_DATA_CMD        BIT(9)
#define SDXC_WRITE_CMD           BIT(10)
#define SDXC_STEAM_CMD           BIT(11)
#define SDXC_AUTO_STOP_CMD       BIT(12)
#define SDXC_WAIT_OVER_CMD       BIT(13)
#define SDXC_ABOUT_CMD           BIT(14)
#define SDXC_SEND_INIT_CMD       BIT(15)
#define SDXC_UPDATE_CLOCK_CMD    BIT(21)
#define SDXC_LOAD_CMD            BIT(31)

/*
    SD status reg
REG[0]   : FIFO_RX_LEVEL
REG[1]   : FIFO_TX_LEVEL
REG[2]   : FIFO_EMPTY
REG[3]   : FIFO_FULL
REG[4-7] : FSM_STA
REG[8]   : CARD_PRESENT
REG[9]   : CARD_BUSY
REG[10]  : FSM_BUSY
REG[11-16]: RESP_IDX
REG[17-21]: FIFO_LEVEL
REG[31]   : DMA_REQ
*/

#define SDXC_FIFO_RX_LEVEL    BIT(0)
#define SDXC_FIFO_TX_LEVEL    BIT(1)
#define SDXC_FIFO_EMPTY       BIT(2)
#define SDXC_FIFO_FULL        BIT(3)
#define SDXC_CARD_PRESENT     BIT(8)
#define SDXC_CARD_BUSY        BIT(9)
#define SDXC_FSM_BUSY         BIT(10)
#define SDXC_DMA_REQ          BIT(31)

struct mmc_des_v4p1
{
    rt_uint32_t                         : 1,
                    dic                 : 1, /* disable interrupt on completion                                    */
                    last_des            : 1, /* 1-this data buffer is the last buffer                              */
                    first_des           : 1, /* 1-data buffer is the first buffer,0-data buffer contained in the next descriptor is 1st buffer        */
                    des_chain           : 1, /* 1-the 2nd address in the descriptor is the next descriptor address */
                    end_of_ring         : 1, /* 1-last descriptor flag when using dual data buffer in descriptor   */
                                        : 24,
                    card_err_sum        : 1, /* transfer error flag                                                */
                    own                 : 1; /* des owner:1-idma owns it, 0-host owns it                           */

#define SDXC_DES_NUM_SHIFT 12  /* smhc2!! */
#define SDXC_DES_BUFFER_MAX_LEN (1 << SDXC_DES_NUM_SHIFT)
    rt_uint32_t data_buf1_sz  : 16,
                data_buf2_sz     : 16;
    rt_uint32_t buf_addr_ptr1;
    rt_uint32_t buf_addr_ptr2;
};

#endif
