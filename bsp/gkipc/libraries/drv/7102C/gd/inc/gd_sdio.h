#ifndef _GD_SDIO_H_
#define _GD_SDIO_H_

#include <gtypes.h>
#include <gmodids.h>

#define GD_SDIO0                0
#define GD_SDIO1                1


/*!
*******************************************************************************
**
** SDIO OPEN  parameter.
**
******************************************************************************/
typedef struct
{
    U32    isConnected;
    U32    sectorSize;
    U32    sectorCount;
    U32    mediaType;
    U32    manufacturerID;
    U32    applicationID;
    U32    productRevision;
    U32    serialNumber;
    U32    dataIoNumber;
    U8     productName[5];
}GD_SDIO_VolumeInfoT;


/*!
*************************************************************************
** \brief Version of the SDIO driver.
**
** This number consists of a \b major version number stored in bits
** 16 to 31 (upper word) and a \b minor version number stored in bits
** 0 to 15 (lower word).
** - The \b major number has to be increased when a parameter change
**   occurs for the existing driver's API after its first release.
** - The \b minor number has to be increased when functions are added to
**   the existing driver's API after its first release.
**
** \note This value has to be assigend to the \b version field of the
**       GAPI_SDIO_OpenParamsT structure.
**
*************************************************************************
*/

typedef enum {
    GAPI_SDIO_VERSION = (S32)0x00010000 //!< The current driver version
} GD_SDIO_VersionEnumT;


 typedef enum {
    GAPI_SDIO_TRANSFER_TYPE_NORMAL = 0,     //!< Normal transfer type for SD/SDHC/MMC cards (default)
    GAPI_SDIO_TRANSFER_TYPE_DIRECT,         //!< Direct transfer mode special for SDIO cards
    GAPI_SDIO_TRANSFER_TYPE_SECURE,         //!< Spezial secure transfer mode for SD-Cards
    GAPI_SDIO_TRANSFER_TYPE_WIFI
} GD_SDIO_TransferTypeEnumT;

typedef enum
{
    CARDTYPE_NONE = 0,
    CARDTYPE_MMC,
    CARDTYPE_SD10,
    CARDTYPE_SD11,
    CARDTYPE_SD20
}GD_SDIO_Card_Type;

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
typedef void (*GD_SDIO_NotifyFuncT)(U32 index, U32 comState, void* optArgPtr);

typedef void (*GD_SDIO_IRQFuncT)();
typedef void (*GD_SDIO_RESETFuncT)(U32 index);


/*!
*************************************************************************
** \brief Open parameters for the SDIO driver.
**
** This data structure covers all parameters which need to be specified
** when an instance of the driver is opened.
**
*************************************************************************
*/
typedef struct {
    /*!
       The version of the driver.
       \ref GAPI_SDIO_VersionEnumT "GAPI_SDIO_VERSION".
    */
    GD_SDIO_VersionEnumT version;
	GD_SDIO_TransferTypeEnumT type;
    /*!
    ** The handle specific notification function.
    */
    GD_SDIO_NotifyFuncT  notifyFunc;

	GD_SDIO_IRQFuncT	irqFunc;

	GD_SDIO_RESETFuncT resetFunc;
    /*!
    ** Optional data pointer for the notification function.
    */
    void*                notifyFuncOptPtr;
    /*!
       Flag to request DMA for read/write transfer operation.
    */
    U32       			isUseDmaWay;
} GD_SDIO_OpenParamsT;

/*cid info */
typedef struct
{
    U8    MID;        /*Manufacturer ID            width:8[127:120]*/
    U16   OID;        /*OEM/Application ID       width:16[119:104]*/
    U8    PNM[5];     /*Product name               width:40[103:64]*/
    U8    PRV;        /*Product revision            width:8[63:56]*/
    U32   PSN;        /*Product serial number    width:32[55:24]*/
    U16   MDT;        /*Manufacturing date        width:12[19:8]*/
}sdioCidInfo;

/*I just care about usefull info of CSD*/
typedef struct
{
    U8    csdStructure;        /*csd revision*/
    U32   classes;            /*Describes the card command classes  CCC*/
    U32   tranSpeed;           /*transfer speed*/
    U8    eraseBlkEn;          /*erase block enable*/
    U8    permWriteProtect;    /*write protect*/
    U8    tmpWriteProtect;     /*write protect*/
}sdiocsdInfo;

/*I just case ablot usefull info of SCR*/
typedef struct
{
    U32    scrStructure;        // SCR Register Structure Version
    U32    sdSpec;              // Describes the Physical Layer Specification Version supported by the card.
    U32    stateaftererase;     // Defines the data status after erase, whether it is 0 or 1.
    U32    sdSecurity;          // Describes the Security Specification Version supported by the card.
    U32    sdBusWith;           // Describes all the DAT bus widths that are supported by this card.
}sdioScrInfo;

/*Card capacity classification*/
typedef enum 
{
    CARDCAPACITY_SDSC = 0,
    CARDCAPACITY_SDHC_OR_SDXC
}GD_SDIO_Card_Capacity;

typedef struct
{
    U32    index;                /*index of handle array*/
    U32    ocr;                  /*card volage info*/
    U32    csd[4];               /*csd info (invert)*/
    U32    read_bl_len;
    U32    write_bl_len;
    U64    capacity_user;
    U32    sectorcount;
    U32    inhighspeed;
    U32    maxTransferBlk;
    U32    eraseGrpSize;
    sdioScrInfo    scr;
    sdiocsdInfo    csdInfo;
    U32    tran_speed;              /*max transfer speed*/
    U32    rca;                     /*card address*/
    U32    cid[4];                  /*card  cid info*/
    GD_SDIO_Card_Type    type;      /*card type*/
    GD_SDIO_Card_Capacity capacity; /*card capacity*/
    U32    highCapacity;            /*is high capacity*/
    sdioCidInfo    cidInfo;
}sdioBlockT;

/* SDIO specific handle */
typedef struct
 {
     U32                   inUse;        /* specifies if handle is in use */
     U32                   index;        /*index of handle array*/
     GD_SDIO_OpenParamsT openParams;   /* open params of the handle */
     sdioBlockT            devicePtr;    /* pointer to hardware device */
 } sdioHandleT;

typedef struct
{
    U32    IRQStatus;  /*!< content of IRQ status register.*/
}SDIO_DATA_S;

#define    GD_SDIO_ERR_BASE    (GD_SDIO_MODULE_ID<<16)
//#define    SDIO_INT_MODE
enum
{
    GD_ERR_SDIO_CARD_INIT_FAILED = GD_SDIO_ERR_BASE,
    GD_ERR_SDIO_INT_ERR,
    GD_ERR_SDIO_NO_CARD,
    GD_ERR_SDIO_CARD_BUSY,
    GD_ERR_SDIO_READ_FAILED,
    GD_ERR_SDIO_WRITE_FAILED,
    GD_ERR_SDIO_ERASE_FAILED,
    GD_ERR_SDIO_CMD_NO_SUPPORTED,
    GD_ERR_SDIO_SET_BLOCK_SIZE,
    GD_ERR_SDIO_CMD_FAILED,
    GD_ERR_SDIO_CARD_LOCKED
};



/*!
*******************************************************************************
**
** SDIO API functions.
**
******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

GERR GD_SDIO_Init(GD_SDIO_OpenParamsT* openParamsP, U32 index);
GERR GD_SDIO_Exit(sdioHandleT *sdiohandle, U32 index);
GERR GD_SDIO_Rsponse(void);
GERR GD_SDIO_Open(GD_SDIO_OpenParamsT *openParamsP,sdioHandleT *pHandle, U32 index);
GERR GD_SDIO_Close(sdioHandleT *sdiohandle, U32 index);
GERR GD_SDIO_ReadSector(sdioHandleT * sdiohandle, U32 startblk, void* buffer, U32 blkcount);
GERR GD_SDIO_WriteSector(sdioHandleT * sdiohandle, U32 startblk, void* buffer, U32 blkcount);
GERR GD_SDIO_EraseSector(sdioHandleT * sdiohandle, U32 start, U32 blkcnt);
GERR GD_SDIO_GetCardInfo(sdioHandleT * sdiohandle, GD_SDIO_VolumeInfoT *info,U32 index);


#ifdef __cplusplus
}
#endif

#endif
