/*
 * File      : drv_mmc.h
 * This file is part of gkipc BSP for RT-Thread distribution.
 *
 * Copyright (c) 2017 chengdu goke Microelectronics Co., Ltd.
 * All rights reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *  Visit http://www.goke.com to get contact with goke.
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef MMC_H_
#define MMC_H_

#include "rtdevice.h"

#define MMC_FEQ_MIN 100000
#define MMC_FEQ_MAX 50000000
#define MMC_DMA_DESC_BUFF_SIZE (0x1f00)
#define MMC_HANDLE_COUNT 2


#define CARD_UNPLUGED 1
#define CARD_PLUGED 0

typedef enum {
    RT_GAPI_SDIO_VERSION = (rt_int32_t)0x00010000 //!< The current driver version
} RT_SDIO_VersionEnumT;


 typedef enum {
    RT_GAPI_SDIO_TRANSFER_TYPE_NORMAL = 0,     //!< Normal transfer type for SD/SDHC/MMC cards (default)
    RT_GAPI_SDIO_TRANSFER_TYPE_DIRECT,         //!< Direct transfer mode special for SDIO cards
    RT_GAPI_SDIO_TRANSFER_TYPE_SECURE,         //!< Spezial secure transfer mode for SD-Cards
    RT_GAPI_SDIO_TRANSFER_TYPE_WIFI
} RT_SDIO_TransferTypeEnumT;

 typedef enum rt_card_type
 {
     RT_CARDTYPE_NONE = 0,
     RT_CARDTYPE_MMC,
     RT_CARDTYPE_SD10,
     RT_CARDTYPE_SD20,
     RT_CARDTYPE_SDHC
 }RT_SDIO_Card_Type;

 /*!
****************************************************************************
**
** \brief SDIO callback function signature
**
** This is the callback function signature required by the SDIO driver
** for internally notification functions.
**
** \param comState  Comunication status.
** \param optArgPtr Optional arg pointer.
**
****************************************************************************
*/
typedef void (*RT_SDIO_NotifyFuncT)(rt_uint32_t index, rt_uint32_t comState, void* optArgPtr);

typedef void (*RT_SDIO_IRQFuncT)();
typedef void (*RT_SDIO_RESETFuncT)(rt_uint32_t index);




typedef struct {
    /*!
       The version of the driver.
       \ref GAPI_SDIO_VersionEnumT "GAPI_SDIO_VERSION".
    */
    RT_SDIO_VersionEnumT      version;
	RT_SDIO_TransferTypeEnumT type;
    /*!
    ** The handle specific notification function.
    */
    RT_SDIO_NotifyFuncT  notifyFunc;

	RT_SDIO_IRQFuncT	 irqFunc;

	RT_SDIO_RESETFuncT   resetFunc;
    /*!
    ** Optional data pointer for the notification function.
    */
    void*                notifyFuncOptPtr;
    /*!
       Flag to request DMA for read/write transfer operation.
    */
    rt_uint32_t          isUseDmaWay;
}RT_SDIO_OpenParamsT;


/*cid info */
typedef struct
{
    rt_uint8_t    MID;        /*Manufacturer ID            width:8[127:120]*/
    rt_uint16_t   OID;        /*OEM/Application ID       width:16[119:104]*/
    rt_uint8_t    PNM[5];     /*Product name               width:40[103:64]*/
    rt_uint8_t    PRV;        /*Product revision            width:8[63:56]*/
    rt_uint32_t   PSN;        /*Product serial number    width:32[55:24]*/
    rt_uint16_t   MDT;        /*Manufacturing date        width:12[19:8]*/
}rtSdioCidInfo;

/*I just care about usefull info of CSD*/
typedef struct
{
    rt_uint8_t    csdStructure;        /*csd revision*/
    rt_uint32_t   classes;            /*Describes the card command classes  CCC*/
    rt_uint32_t   tranSpeed;           /*transfer speed*/
    rt_uint8_t    eraseBlkEn;          /*erase block enable*/
    rt_uint8_t    permWriteProtect;    /*write protect*/
    rt_uint8_t    tmpWriteProtect;     /*write protect*/
}rtSdiocsdInfo;

/*I just case ablot usefull info of SCR*/
typedef struct
{
    rt_uint32_t    scrStructure;        // SCR Register Structure Version
    rt_uint32_t    sdSpec;              // Describes the Physical Layer Specification Version supported by the card.
    rt_uint32_t    stateaftererase;     // Defines the data status after erase, whether it is 0 or 1.
    rt_uint32_t    sdSecurity;          // Describes the Security Specification Version supported by the card.
    rt_uint32_t    sdBusWith;           // Describes all the DAT bus widths that are supported by this card.
}rtSdioScrInfo;

typedef struct
{
    rt_uint32_t    index;                /*index of handle array*/
    rt_uint32_t    ocr;                  /*card volage info*/
    rt_uint32_t    csd[4];               /*csd info (invert)*/
    rt_uint32_t    read_bl_len;
    rt_uint32_t    write_bl_len;
    unsigned long long    capacity_user;
    rt_uint32_t    sectorcount;
    rt_uint32_t    inhighspeed;
    rt_uint32_t    maxTransferBlk;
    rt_uint32_t    eraseGrpSize;
    rtSdioScrInfo  scr;
    rtSdiocsdInfo  csdInfo;
    rt_uint32_t    tran_speed;            /*max transfer speed*/
    rt_uint32_t    rca;                   /*card address*/
    rt_uint32_t    cid[4];                /*card  cid info*/
    enum rt_card_type    type;       /*card type*/
    rt_uint32_t      highCapacity;          /*is high capacity*/
    rtSdioCidInfo    cidInfo;
}rtSdioBlockT;

/* SDIO specific handle */
typedef struct
 {
     rt_uint32_t           inUse;        /* specifies if handle is in use */
     rt_uint32_t           index;        /*index of handle array*/
     RT_SDIO_OpenParamsT   openParams;   /* open params of the handle */
     rtSdioBlockT          devicePtr;    /* pointer to hardware device */
 } rtSdioHandleT;

typedef struct gk_mmc_driver
{
    rtSdioHandleT        handle;
    RT_SDIO_OpenParamsT  openParams;
    struct rt_device     *deviceP[MMC_HANDLE_COUNT];
    struct dfs_partition *partP[MMC_HANDLE_COUNT];
}gk_mmc_driver_s;


typedef void (*fs_sdio_notify_func_t)(rt_uint32_t index, rt_uint32_t comState, void* optArgPtr);

int rt_hw_mmc_init(gk_mmc_driver_s *pMmcParams);

#endif /* MMC_H_ */
