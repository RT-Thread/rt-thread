/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-02 18:32:54
 * @LastEditTime: 2021-05-24 14:33:45
 * @Description:  Description of file
 *
 * @Modify History:
 * * * Ver   Who        Date         Changes
 * * ----- ------     --------    --------------------------------------
 */

#ifndef QSPI_HW_H
#define QSPI_HW_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ft_qspi.h"
#include "ft_types.h"

/* register definition */
#define FT_REG_QSPI_CAP_OFFSET (0x00)       /* Flash capacity setting register */
#define FT_REG_QSPI_RD_CFG_OFFSET (0x04)    /* Address access reads configuration registers */
#define FT_REG_QSPI_WR_CFG_OFFSET (0x08)    /* Write buffer flush register */
#define FT_REG_QSPI_FLUSH_OFFSET (0x0C)     /* Write buffer flush register */
#define FT_REG_QSPI_CMD_PORT_OFFSET (0x10)  /* Command port register */
#define FT_REG_QSPI_ADDR_PORT_OFFSET (0x14) /* Address port register */
#define FT_REG_QSPI_HD_PORT_OFFSET (0x18)   /* Upper bit port register */
#define FT_REG_QSPI_LD_PORT_OFFSET (0x1C)   /* low bit port register */
#define FT_REG_QSPI_FUN_SET_OFFSET (0x20)   /* CS setting register  */
#define FT_REG_QSPI_WIP_RD_OFFSET (0x24)    /* WIP reads the Settings register */
#define FT_REG_QSPI_WP_OFFSET (0x28)        /* WP register */
#define FT_REG_QSPI_MODE_OFFSET (0x2C)      /* Mode setting register */

/*QSPI_CAP*/
#define FT_REG_QSPI_CAP_FLASH_NUM(data) ((data) << 3) /* Flash number */
#define FT_REG_QSPI_CAP_FLASH_CAP(data) ((data) << 0) /*  The flash capacity */

/* RD_CFG */
#define FT_RD_CFG_CMD(data) ((data) << 24)       /* Read Command */
#define FT_RD_CFG_THROUGH(data) ((data) << 23)   /*  The programming flag in the status register */
#define FT_RD_CFG_TRANSFER(data) ((data) << 20)  /*  */
#define FT_RD_CFG_ADDR_SEL(data) ((data) << 19)  /*  */
#define FT_RD_CFG_LATENCY(data) ((data) << 18)   /*  */
#define FT_RD_CFG_MODE_BYTE(data) ((data) << 17) /*  */
#define FT_RD_CFG_CMD_SIGN(data) ((data) << 9)   /*  */
#define FT_RD_CFG_DUMMY(data) ((data) << 4)      /*  */
#define FT_RD_CFG_D_BUFFER(data) ((data) << 3)   /*  */
#define FT_RD_CFG_SCK_SEL(data) ((data) << 0)    /*  */

/*QSPI_WR_CFG*/
#define FT_WR_CFG_CMD(data) ((data) << 24)
#define FT_WR_CFG_WAIT(data) ((data) << 9)
#define FT_WR_CFG_THROUGH(data) ((data) << 8)
#define FT_WR_CFG_TRANSFER(data) ((data) << 5)
#define FT_WR_CFG_ADDRSEL(data) ((data) << 4)
#define FT_WR_CFG_MODE(data) ((data) << 3)
#define FT_WR_CFG_SCK_SEL(data) ((data) << 0)

/*QSPI_CMD_PORT*/
#define FT_CMD_PORT_CMD(data) ((data) << 24)
#define FT_CMD_PORT_WAIT(data) ((data) << 22)
#define FT_CMD_PORT_THROUGH(data) ((data) << 21)
#define FT_CMD_PORT_CS(data) ((data) << 19)
#define FT_CMD_PORT_TRANSFER(data) ((data) << 16)
#define FT_CMD_PORT_ADDR(data) ((data) << 15)
#define FT_CMD_PORT_LATENCY(data) ((data) << 14)
#define FT_CMD_PORT_DATA_TRANS(data) ((data) << 13)
#define FT_CMD_PORT_ADDR_SEL(data) ((data) << 12)
#define FT_CMD_PORT_DUMMY(data) ((data) << 7)
#define FT_CMD_PORT_P_BUFFER(data) ((data) << 6)
#define FT_CMD_PORT_RW_NUM(data) ((data) << 3)
#define FT_CMD_PORT_CLK_SEL(data) ((data) << 0)

/*QSPI_FUN_SET*/
#define FT_FUN_SET_CS_HOLD(data) ((data) << 24)
#define FT_FUN_SET_CS_SETUP(data) ((data) << 16)
#define FT_FUN_SET_CS_DELAY(data) ((data) << 0)

/*QSPI_WIP_RD*/
#define FT_WIP_RD_CMD(data) ((data) << 24)
#define FT_WIP_RD_TRANSFER(data) ((data) << 3)
#define FT_WIP_RD_SCK_SEL(data) ((data) << 0)

/*QSPI_WP*/
#define FT_WP_EN(data) ((data) << 17)
#define FT_WP_WP(data) ((data) << 16)
#define FT_WP_HOLD(data) ((data) << 8)
#define FT_WP_SETUP(data) ((data) << 0)

/*QSPI_MODE*/
#define FT_MODE_VALID(data) ((data) << 8)
#define FT_MODE_MODE(data) ((data) << 0)

#define FT_QSPI_FLASH_CAP_4MB 0
#define FT_QSPI_FLASH_CAP_8MB 1
#define FT_QSPI_FLASH_CAP_16MB 2
#define FT_QSPI_FLASH_CAP_32MB 3
#define FT_QSPI_FLASH_CAP_64MB 4
#define FT_QSPI_FLASH_CAP_128MB 5
#define FT_QSPI_FLASH_CAP_256MB 6

#define FT_QSPI_ADDR_SEL_3 0
#define FT_QSPI_ADDR_SEL_4 1

#define FT_QSPI_SCK_DIV_128 0
#define FT_QSPI_SCK_DIV_2 1
#define FT_QSPI_SCK_DIV_4 2
#define FT_QSPI_SCK_DIV_8 3
#define FT_QSPI_SCK_DIV_16 4
#define FT_QSPI_SCK_DIV_32 5
#define FT_QSPI_SCK_DIV_64 6

#define FT_QSPI_TRANSFER_1_1_1 0
#define FT_QSPI_TRANSFER_1_1_2 1
#define FT_QSPI_TRANSFER_1_1_4 2
#define FT_QSPI_TRANSFER_1_2_2 3
#define FT_QSPI_TRANSFER_1_4_4 4
#define FT_QSPI_TRANSFER_2_2_2 5
#define FT_QSPI_TRANSFER_4_4_4 6

    /* typedefs */
    /*QSPI_RD_CFG*/
    typedef union
    {
        u32 data;
        struct
        {
            u32 rdSckSel : 3;   /* 2:0   */
            u32 dBuffer : 1;    /* 3     */
            u32 dummy : 5;      /* 8:4   */
            u32 cmdSign : 8;    /* 16:9  */
            u32 modeByte : 1;   /* 17    */
            u32 rdLatency : 1;  /* 18    */
            u32 rdAddrSel : 1;  /* 19    */
            u32 rdTransfer : 3; /* 22:20 */
            u32 rdThrough : 1;  /* 23    */
            u32 rdCmd : 8;      /* 31:24 */
        } val;
    } FQSpi_RdCfgReg_t;

    /*QSPI_WR_CFG*/
    typedef union
    {
        u32 data;
        struct
        {
            u32 wrSckSel : 3;   /* 2:0   */
            u32 wrMode : 1;     /* 3     */
            u32 wrAddrsel : 1;  /* 4     */
            u32 wrTransfer : 3; /* 7:5   */
            u32 wrThrough : 1;  /* 8     */
            u32 wrWait : 1;     /* 9     */
            u32 wrRes : 14;     /* 23:10 */
            u32 wrCmd : 8;      /* 31:24 */
        } val;
    } FQSpi_WrCfgReg_t;

    /*QSPI_CMD_PORT*/
    typedef union
    {
        u32 data;
        struct
        {
            u32 sckSel : 3;       /* 2:0   */
            u32 rwMum : 3;        /* 5:3   */
            u32 pBuffer : 1;      /* 6     */
            u32 dummy : 5;        /* 11:7  */
            u32 addrSel : 1;      /* 12    */
            u32 dataTransfer : 1; /* 13    */
            u32 latency : 1;      /* 14    */
            u32 cmdAddr : 1;      /* 15    */
            u32 transfer : 3;     /* 18:16 */
            u32 cs : 2;           /* 20:19 */
            u32 through : 1;      /* 21    */
            u32 wait : 1;         /* 22    */
            u32 res : 1;          /* 23    */
            u32 cmd : 8;          /* 31:24 */
        } val;
    } FQSpi_CmdPortReg_t;

    /**
 * @name: FQSpi_Reset
 * @msg:  This routine performs the QSPI controller initialization.
 * @in param: pQspi
 * @return {*}
 */
    void FQSpi_Reset(FQSpi_t *pQspi);

#ifdef __cplusplus
}
#endif

#endif // !
