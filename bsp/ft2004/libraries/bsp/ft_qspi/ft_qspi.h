/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-05 21:31:10
 * @LastEditTime: 2021-04-05 21:31:10
 * @Description:  Description of file
 * @Modify History:
 * * * Ver   Who        Date         Changes
 * * ----- ------     --------    --------------------------------------
 * *   v1.0  hh       2021-04-05     init
 */

#ifndef FT_QSPI_H
#define FT_QSPI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ft_types.h"
#include "ft_error_code.h"

#define FQSPI_SUCCESS FST_SUCCESS                                                      /* SUCCESS */
#define FQSPI_FAILURE FT_MAKE_ERRCODE(errQspi, errBspGeneral, FST_FAILURE)             /* Normal */
#define FQSPI_TIMEOUT FT_MAKE_ERRCODE(errQspi, errBspGeneral, FST_TIMEOUT)             /* Timeout */
#define FQSPI_EILSEQ FT_MAKE_ERRCODE(errQspi, errBspGeneral, FST_EILSEQ)               /* Illegal byte sequence. */
#define FQSPI_INVALID_PARAM FT_MAKE_ERRCODE(errQspi, errBspGeneral, FST_INVALID_PARAM) /* Invalid param. */

/* qspi bsp command instruction operation  */
#define FQSPI_CMD_NEED_ADDR_MASK 0x1U
#define FQSPI_CMD_NEED_DUMMY_MASK 0x2U
#define FQSPI_CMD_NEED_GET_MASK 0x4U
#define FQSPI_CMD_NEED_SET_MASK 0x08U
#define FQSPI_CMD_ADDRESS_3BYTE_MASK 0x10U
#define FQSPI_CMD_ADDRESS_4BYTE_MASK 0x20U

/* qspi cmd of transfer operation */
#define FQSPI_DATA_NEED_DUMMY_MASK 0x1U
#define FQSPI_DATA_ADDRESS_3BYTE_MASK 0x2U
#define FQSPI_DATA_ADDRESS_4BYTE_MASK 0x4U

#define FQSPI_FLASH_CMD_WRR 0x01        /* Write status register */
#define FQSPI_FLASH_CMD_PP 0x02         /* Page program */
#define FQSPI_FLASH_CMD_READ 0x03       /* Normal read data bytes */
#define FQSPI_FLASH_CMD_WRDI 0x04       /* Write disable */
#define FQSPI_FLASH_CMD_RDSR1 0x05      /* Read status register */
#define FQSPI_FLASH_CMD_WREN 0x06       /* Write enable */
#define FQSPI_FLASH_CMD_RDSR2 0x07      /* Read status register */
#define FQSPI_FLASH_CMD_FAST_READ 0x0B  /* Fast read data bytes */
#define FQSPI_FLASH_CMD_4FAST_READ 0x0C /* Fast read data bytes */
#define FQSPI_FLASH_CMD_4PP 0x12        /* Page program */
#define FQSPI_FLASH_CMD_4READ 0x13      /* Normal read data bytes */
#define FQSPI_FLASH_CMD_P4E 0x20        /* Erase 4kb sector */
#define FQSPI_FLASH_CMD_4P4E 0x21       /* Erase 4kb sector */
#define FQSPI_FLASH_CMD_QPP 0x32        /* Quad Page program */
#define FQSPI_FLASH_CMD_4QPP 0x34       /* Quad Page program */
#define FQSPI_FLASH_CMD_RDCR 0x35       /* Read config register */
#define FQSPI_FLASH_CMD_BE 0x60         /* Bulk erase */
#define FQSPI_FLASH_CMD_RDAR 0x65       /* Read Any Register  */
#define FQSPI_FLASH_CMD_QOR 0x6B        /* Quad read data bytes */
#define FQSPI_FLASH_CMD_4QOR 0x6C       /* Quad read data bytes */
#define FQSPI_FLASH_CMD_WRAR 0x71       /* Write Any Register  */
#define FQSPI_FLASH_CMD_RDID 0x9F       /* Read JEDEC ID */
#define FQSPI_FLASH_CMD_4BAM 0xB7       /* Enter 4 Bytes Mode */
#define FQSPI_FLASH_CMD_4BE 0xC7        /* Bulk erase */
#define FQSPI_FLASH_CMD_SE 0xD8         /* Sector erase */
#define FQSPI_FLASH_CMD_4SE 0xDC        /* Sector erase */
#define FQSPI_FLASH_CMD_4BEX 0xE9       /* Exit 4 Bytes Mode */
#define FQSPI_FLASH_CMD_QIOR 0xEB       /* Quad read data bytes */
#define FQSPI_FLASH_CMD_4QIOR 0xEC      /* Quad read data bytes */
#define FQSPI_FLASH_DISCOVERABLE_PARAMETER 0x5a
#define FQSPI_CMD_ENABLE_RESET 0x66
#define FQSPI_CMD_RESET 0x99

    struct FQSpi_DataPack
    {
        u32 flags;      /* Follow qspi cmd of transfer operation */
        u32 cmd;        /* Command instruction */
        u32 addr;       /* Flash address */
        u32 dummyCycle; /* dummy Cycle */
        const u8 *txBuf;
        u8 *rxBuf;  /* Need send or read buffer */
        u32 length; /*  Buffer length */
    };

    struct FQSpi_CmdPack
    {
        u32 flags;      /* Follow qspi bsp command instruction operation */
        u32 cmd;        /* Command instruction */
        u32 addr;       /* Command address */
        u32 dummyCycle; /* dummy Cycle */
        const u8 *txBuf;
        u8 *rxBuf;  /* Need send or read buffer */
        u32 length; /*  Buffer length */
    };

    typedef struct
    {
        u32 instanceId;        /* Id of device */
        uintptr_t baseAddress; /* Base address of qspi */
        u32 transMode;         /* Transfer mode */
        u32 capacity;          /* Flash capacity */
        u32 addrMode;          /**/
        u32 clkDiv;
        u32 qspiDevNum; /*Qspi device number */
        u32 channel;    /* Cs number */
        u32 bitWidth;   /* Transfer unit width */
    } FQSpi_Config_t;

    typedef struct
    {
        FQSpi_Config_t config;
        u32 isReady; /**< Device is initialized and ready */

    } FQSpi_t;

    /**
     * @name: FQSpi_LookupConfig
     * @msg:  FQSpi_LookupConfig returns a reference FQSpi_Config_t structure based on the
     *          unique device id.
     * @in param {u32} instanceId : unique device
     * @return {FQSpi_Config_t} FQSpi_Config_t is a reference to a config record in the configuration
     *        table (in qspi_g.c) corresponding to <i>instanceId</i>, or NULL if no match is found.
     */
    FQSpi_Config_t *FQSpi_LookupConfig(u32 instanceId);

    /**
     * @name: FQSpi_CfgInitialize
     * @msg:  This function intializes the configuration for the qspi instance
     * @in param {FQSpi_t *} pQspi:  A pointer to the qspi instance
     * @in param {FQSpi_Config_t *} pConfig:  A pointer to the qspi instance config record
     * @return {ft_error_t}
     */
    ft_error_t FQSpi_CfgInitialize(FQSpi_t *pQspi, FQSpi_Config_t *pConfig);

    /**
     * @name: FQSpi_CmdOperation
     * @msg:  This function send command instruction  by the struct FQSpi_CmdPack
     * @in param {FQSpi_t *} pQspi: A pointer to the qspi instance
     * @in param {struct FQSpi_CmdPack *} pCmdPack:  Need to send command instruction package
     * @return {ft_error_t}
     */
    ft_error_t FQSpi_CmdOperation(FQSpi_t *pQspi, struct FQSpi_CmdPack *pCmdPack);

    /**
     * @name: FQSpi_Read
     * @msg:  This function reads flash data from a specific address by {struct FQSpi_DataPack}
     * @in param {FQSpi_t *} pQspi: A pointer to the qspi instance
     * @in param {struct FQSpi_DataPack *} pDataPack: Need to read data package
     * @return {ft_error_t}
     */
    ft_error_t FQSpi_Read(FQSpi_t *pQspi, struct FQSpi_DataPack *pDataPack);

    /**
     * @name: FQSpi_Write
     * @msg:  This function writes data  from a specific address by {struct FQSpi_DataPack}
     * @in param {FQSpi_t *} pQspi:  A pointer to the qspi instance
     * @in param {struct FQSpi_DataPack *} pDataPack: Need to read data package
     * @return {ft_error_t}
     */
    ft_error_t FQSpi_Write(FQSpi_t *pQspi, struct FQSpi_DataPack *pDataPack);

    /**
     * @name: FQSpi_FlashRegSet
     * @msg:  This function sends command instruction with specific parameters
     * @in param {FQSpi_t *} pQspi:  A pointer to the qspi instance
     * @in param {FT_IN u8} cmd:   Command instruction
     * @in param {FT_IN u8 *} writebuf: Data that needs to be sent through command instruction registers
     * @in param {u32} length: Data length
     * @return {ft_error_t}
     */
    ft_error_t FQSpi_FlashRegSet(FQSpi_t *pQspi,
                                 FT_IN u8 cmd,
                                 FT_IN u8 *writebuf,
                                 u32 length);

#ifdef __cplusplus
}
#endif

#endif
