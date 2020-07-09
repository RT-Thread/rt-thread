/*!
*******************************************************************************
**
** \file      gd_spi.h
**
** \brief     Serail Peripheral Interface driver.
**
**            (C) Goke Microelectronics China 2007 - 2010
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. HUNAN GOFORTUNE SEMICONDUCTOR
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \version   \$Id: gd_spi.h,v 1.1 2013/11/21 01:27:52
**
*******************************************************************************
*/
#ifndef GD_SPI_H
#define GD_SPI_H

#include <gtypes.h>
#include <gmodids.h>


/*!
*******************************************************************************
**
** \anchor gd_spi_error_base
** \brief The base error code for the serial peripheral interface driver.
**
*******************************************************************************
*/
/*@{*/
#define  GD_SPI_ERR_BASE  ( GD_SPI_MODULE_ID << 16)
/*@}*/

typedef enum
{
    GD_SPI_CHANNEL_0 = 0,
    GD_SPI_CHANNEL_1,
    GD_SPI_CHANNEL_NUM
}GD_SPI_CHANNEL_E;

typedef enum
{
    GD_SPI_SLAVE0 = 0,
    GD_SPI_SLAVE1,
    GD_SPI_SLAVE2,
    GD_SPI_SLAVE3,
    GD_SPI_SLAVE4,
    GD_SPI_SLAVE5,
    GD_SPI_SLAVE_NUM
}GD_SPI_SLAVE_E;

// TODO: to be confirmed for each clock value
typedef enum
{
   GD_SPI_FREQ_81M = 81000000,
   GD_SPI_FREQ_40M = 40000000,
   GD_SPI_FREQ_30M = 30000000,
   GD_SPI_FREQ_27M = 27000000,
   GD_SPI_FREQ_20M = 20000000,
   GD_SPI_FREQ_16M = 16000000,
   GD_SPI_FREQ_13M = 13500000,
   GD_SPI_FREQ_10M = 10000000,
   GD_SPI_FREQ_9M  =  9000000,
   GD_SPI_FREQ_6M  =  6000000,
   GD_SPI_FREQ_3M  =  3000000,
   GD_SPI_FREQ_1M  =  1000000,
}GD_SPI_SPEED_MODE;

typedef enum
{
    SPI_POLARITY_MODE0 = 0,//!< Sclk low level,fisrt edge get data.
    SPI_POLARITY_MODE1,//!< Sclk low level,second edge get data.
    SPI_POLARITY_MODE2,//!< Sclk high level,first edge get data. 
    SPI_POLARITY_MODE3,//!< Sclk high level,second edge get data.
}GD_SPI_POLARITY_MODE;
/*!
*******************************************************************************
**
** \brief SPI driver error codes.
**
*******************************************************************************
*/
enum
{
    GD_ERR_SPI_TYPE_NOT_SUPPORTED = GD_SPI_ERR_BASE, //!< Device not supported.
    GD_ERR_SPI_IN_USE,                                  //!< Read error.
    GD_ERR_SPI_NOT_OPEN,
    GD_ERR_SPI_READ,                                    //!< Read error.
    GD_ERR_SPI_WRITE,                                   //!< Write error.
    GD_ERR_SPI_ERASE,
    GD_ERR_SPI_UNLOCK_FAIL,
    GD_ERR_SPI_INI_ERR,
    GD_ERR_SPI_BUSY,
};

/*!
*******************************************************************************
**
** \brief SPI open parameter.
**
******************************************************************************/
typedef enum
{
    GD_SPI_UNUSED,
    GD_SPI_WRITE_ONLY,
    GD_SPI_READ_ONLY,
    GD_SPI_WRITE_READ,
}GD_SPI_RW;

typedef struct
{
    /*! The connection parameters to be applied when open an instance of the
        driver.
     */
    U8              spi;
    U8              slave;
    U8              csgpio;
    U8              polarity;    //!< send and recive data mode
    U32             baudrate;
    GBOOL           used_irq;
} GD_SPI_OPEN_PARAMS_S;

/*!
*******************************************************************************
**
** \brief SPI ISR parameter.
**
******************************************************************************/
typedef struct
{
    /*! The connection parameters to be applied when used irq mode for the
        driver.
     */
    U8              spi;
    U32              write_len;
    U32              read_len;
    U32              all_len;
    U32              wf_len;
    U32              rf_len;
    U32              w_xfer;
    U32              r_xfer;
    U8              bitpw;
    U8              finished;
    GD_SPI_RW       rwmode;
    void*           wbuf;
    void*           rbuf;
    GD_HANDLE       spihandle;
    GD_HANDLE       spiIrqHandle;
} GD_SPI_ISR_PARAMS_S;


/*!
*******************************************************************************
**
** \brief SPI global parameter.
**
******************************************************************************/
typedef struct
{
    U8          spi;
    U8          slave;
    U8          using;
    U8          polarity;      //!< send and recive data mode
    U32         baudrate;
    GD_HANDLE   cs;
    U8          datwidth;
    GBOOL       used_irq;
} GD_SPI_STATUS_PARAMS_S;


/*!
*******************************************************************************
**
** \brief SPI write parameter.
**
******************************************************************************/
typedef struct
{
    U32         wBitSet;
    U32         sBitSet;
    U32         eBitSet;
    U32         wipMask;
    U32         address;
} GD_SPI_WR_PARAMS_S;


typedef struct
{
    U8  readID;        // command to read the chip identification
    U8  writeEnable;   // command to enable a write/erase sequence
    U8  writeDisable;  // command to disable a write/erase sequence
    U8  readStatus;    // command to read from status register
    U8  writeStatus;   // command to write to status register
    U8  readData;      // command to read data
    U8  readDataFast;  // command to read data in fast mode
    U8  eraseSector;   // command to erase a single sector
    U8  eraseChip;     // command to erase the entire chip
    U8  programPage;   // command to program a sector page
    U32 statusMaskWIP; // status register mask for bit write-in-progress
    U32 statusMaskWEL; // status register mask for bit write-enable-latch
    U8  readIO2;       // command to read data by IO2
    U8  readIO4;       // command to read data by IO4
    U8  programPage2;  // command to program a sector page by IO2
    U8  programPage4;  // command to program a sector page by IO4
}
GD_SPI_CMD_S;



/*
*******************************************************************
*   sflash cmd attribute
*   sflash cmd register bit definition
*   bit 31    30    29    28    27    26    25    24    23    22    21         20        19           18    17
        | rsrd    | hold time | transfer data bytes       |data cycle|adr and dummy cycle | cmd cycle |
                      00-100ns   11111 -- 4 bytes                                                           00 -x1
                      01-3us      other(e.g.,n) -- n bytes   0-3 cycle        0-3 cycle              01 -x2
                      10-100us                                                                                      10 -x4

    bit       16           15          14        13        12        11     10     9            8                      [7: 0]
        |         RWN            |  dummy cycle number   |  adr byte num    |                        |      cmd to DF                 |
          00 - rd data for SF     0 - 7 bytes cycle            0-7 bytes          1 - send cmd
          01 - wr data to SF                                                                0 - no send cmd        see specific flash cmd
          11 - nothing to do

********************************************************************
*/
/* send cmd or not [8]*/
#define SPI_SEND_CMD                    0x00000100
#define SPI_NO_SEND_CMD                 0x00000000

/* byte number of address to send [11:9]*/
#define SPI_SEND_ADDR_BYTE_NUM_0        0x00000000
#define SPI_SEND_ADDR_BYTE_NUM_1        0x00000200
#define SPI_SEND_ADDR_BYTE_NUM_2        0x00000400
#define SPI_SEND_ADDR_BYTE_NUM_3        0x00000600
#define SPI_SEND_ADDR_BYTE_NUM_4        0x00000800
#define SPI_SEND_ADDR_BYTE_NUM_5        0x00000a00
#define SPI_SEND_ADDR_BYTE_NUM_6        0x00000c00
#define SPI_SEND_ADDR_BYTE_NUM_7        0x00000e00

/*Byte number of dummy cycle to send [14:12]*/
#define SPI_SEND_DUMMY_BYTE_NUM_0       0x00000000
#define SPI_SEND_DUMMY_BYTE_NUM_1       0x00001000
#define SPI_SEND_DUMMY_BYTE_NUM_2       0x00002000
#define SPI_SEND_DUMMY_BYTE_NUM_3       0x00003000
#define SPI_SEND_DUMMY_BYTE_NUM_4       0x00004000
#define SPI_SEND_DUMMY_BYTE_NUM_5       0x00005000
#define SPI_SEND_DUMMY_BYTE_NUM_6       0x00006000
#define SPI_SEND_DUMMY_BYTE_NUM_7       0x00007000

/* Command operation[16:15]: 00 for read data from SPI; 01 for write data to SPI; 11 for nothing to do */
#define SPI_RWN_READ                    0x00000000
#define SPI_RWN_WRITE                   0x00008000
#define SPI_RWN_NOTHING                 0x00018000

/*I/O mode of command cycle to SF[18:17]: 00 for x1; 01 for x2; 10 for x4*/
#define SPI_CMD_MODE_1X                 0x00000000
#define SPI_CMD_MODE_2X                 0x00020000
#define SPI_CMD_MODE_4X                 0x00040000

/* I/O mode of address and dummy cycle to SF[20:19]*/
#define SPI_ADDR_DUMMY_CYCLE_NUM_0      0x00000000
#define SPI_ADDR_DUMMY_CYCLE_NUM_1      0x00080000
#define SPI_ADDR_DUMMY_CYCLE_NUM_2      0x00100000
#define SPI_ADDR_DUMMY_CYCLE_NUM_3      0x00180000

/*I/O mode of data cycle to or from SF [22:21] */
#define SPI_DATA_CYCLE_NUM_0            0x00000000
#define SPI_DATA_CYCLE_NUM_1            0x00200000
#define SPI_DATA_CYCLE_NUM_2            0x00400000
#define SPI_DATA_CYCLE_NUM_3            0x00600000

/*Transfer data byte number to or from SF[27:23]. For 11111 case, transfer 4bytes per request. For other case, transfer number bytes.*/
#define SPI_TRANSFER_BYTE_NUM_4         0x0f800000
#define SPI_TRANSFER_BYTE_LOC           23

#define SPI_HOLD_TIME_100ns             0x00000000
#define SPI_HOLD_TIME_3us               0x10000000
#define SPI_HOLD_TIME_100us             0x20000000


/*
*******************************************************************************
*******************************************************************************
**
** Generic serial flash specific API functions
**
*******************************************************************************
*******************************************************************************
*/
#ifdef __cplusplus
extern "C" {
#endif

GERR GD_SPI_Init( void );
GERR GD_SPI_Exit( void );
GERR GD_SPI_Open( GD_SPI_OPEN_PARAMS_S *openParamsP, GD_HANDLE* pHandle );
GERR GD_SPI_Close( GD_HANDLE* pHandle );
GERR GD_SPI_WriteWords( GD_HANDLE handle, U16* wbuffer, U32 w_words );
GERR GD_SPI_WriteThenReadWords( GD_HANDLE handle, U16* wbuffer, U32 w_words, U16* rbuffer, U32 r_words );
GERR GD_SPI_WriteBytes( GD_HANDLE handle, U8* wbuffer, U32 w_size );
GERR GD_SPI_WriteThenReadBytes( GD_HANDLE handle, U8* wbuffer, U32 w_size, U8* rbuffer, U32 r_size );
GERR GD_SPI_GetDevice(GD_HANDLE handle);
GERR GD_SPI_ReleaseDevice(GD_HANDLE handle);
GERR GD_SPI_SetDatFormat(GD_HANDLE handle, U8 dat_width);

#ifdef __cplusplus
}
#endif

#endif
