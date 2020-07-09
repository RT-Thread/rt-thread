/*!
*******************************************************************************
**
** \file      gd_i2c.h
**
** \brief     I2C.
**
**            Copyright:   2012 - 2013 (C) GoKe Microelectronics ShangHai Branch
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \note      Do not modify this file as it is generated automatically.
**
******************************************************************************/
#ifndef _GD_I2C_H_
#define _GD_I2C_H_

#include "gmodids.h"



//*****************************************************************************
//*****************************************************************************
//** Defines and Macros
//*****************************************************************************
//*****************************************************************************
#define GD_I2C_ERR_BASE   (GD_I2C_MODULE_ID << 16)





//*****************************************************************************
//*****************************************************************************
//** Enumerated types
//*****************************************************************************
//*****************************************************************************

/*!
*******************************************************************************
**
** \brief I2C driver error codes.
**
*******************************************************************************
*/
enum
{
    GD_ERR_I2C_TYPE_NOT_SUPPORTED = GD_I2C_ERR_BASE, //!< Device not supported.
    GD_ERR_I2C_INT_ERR,
    GD_ERR_I2C_NOT_OPEN,
    GD_ERR_I2C_NOACK,
    GD_ERR_I2C_START_NOACK,
    GD_ERR_I2C_RESTART_NOACK,
    GD_ERR_I2C_ADDR_NOACK,
    GD_ERR_I2C_DATA_NOACK,
    GD_ERR_I2C_READ_NOACK,
    GD_ERR_I2C_SL_NACK,
    GD_ERR_I2C_BUSY,
    GD_ERR_I2C_FIFO_OVERFLOW,
};

/*---------------------------------------------------------------------------*/
/* types, enums and structures                                               */
/*---------------------------------------------------------------------------*/
/*!
*******************************************************************************
**
** \brief I2C channel number.
**
** \sa    GD_I2C_OPEN_PARAMS_S
**
******************************************************************************/
typedef enum
{
    GD_I2C_CHANNEL_ONE = 0, //!< I2C channel 1.
    GD_I2C_CHANNEL_TWO,     //!< I2C channel 2.
}GD_I2C_CHANNEL_E;

/*!
*******************************************************************************
**
** \brief I2C operition modes.
**
** \sa    GD_I2C_INIT_PARAMS_S
**
******************************************************************************/
typedef enum
{
    GD_I2C_GENERIC_MASTER_MODE, //!< Generic master mode.
    GD_I2C_GENERIC_SLAVER_MODE, //!< Generic slave mode.
    GD_I2C_AUTO_MASTER_MODE,    //!< Auto master mode.
    GD_I2C_AUTO_SLAVER_MODE,    //!< Auto slave mode.
    GD_I2C_DMA_MASTER_MODE,     //!< DMA master mode.
    GD_I2C_DMA_SLAVER_MODE,     //!< DMA slave mode.
}GD_I2C_OPEN_MODE_E;

/*!
*******************************************************************************
**
** \brief Protocol modes.
**
** \sa    GD_I2C_SetProtocol()
**
******************************************************************************/
typedef enum
{
    GD_I2C_COMMON_PROTOCOL = 0,  //!< Common protocol.
    GD_I2C_RESTART_PROTOCOL,     //!< Protocol with restart.
} GD_I2C_PROTOCOL_E;

/*!
*******************************************************************************
**
** \brief I2C datarate speed modes.
**
** \sa    GD_I2C_OPEN_PARAMS_S
**
******************************************************************************/
typedef enum
{
    GD_I2C_100KBPS = 100000, //!< 100kHz datarate.
    GD_I2C_400KBPS = 400000,     //!< 400kHz datarate.
}GD_I2C_SPEED_E;


/*!
*******************************************************************************
**
** \brief I2C datarate speed modes.
**
** \sa    GD_I2C_OPEN_PARAMS_S
**
******************************************************************************/
typedef enum
{
    GD_I2C_NORMAL = 0,
    GD_I2C_TURBO_MODE,  // write operation only.
    GD_I2C_INTERRUPT,
}GD_I2C_MODE_E;


//*****************************************************************************
//*****************************************************************************
//** Data Structures
//*****************************************************************************
//*****************************************************************************
/*!
*******************************************************************************
**
** \brief Init parameters.
**
** \sa    GD_I2C_Init() <BR>
**        GD_I2C_OPEN_MODE_E
**
******************************************************************************/
typedef struct
{
    GD_I2C_OPEN_MODE_E  mode;     //!< Operation mode.
    S8                  priority; //!< IRQ priority e.g. \c #GD_INT_LOW_PRIORITY.
    S8                  gpioSdaPinCh1; //!< GPIO SDA pin assigmnet channel 1.
    S8                  gpioSclPinCh1; //!< GPIO SCL pin assigmnet channel 1.
    S8                  gpioSdaPinCh2; //!< For future use.
    S8                  gpioSclPinCh2; //!< For future use.
}GD_I2C_INIT_PARAMS_S;

typedef struct
{
    GD_I2C_CHANNEL_E        channel;
    GD_I2C_SPEED_E          speed;
    GD_I2C_MODE_E           mode;
} GD_I2C_OPEN_PARAMS_S;


//*****************************************************************************
//*****************************************************************************
//** Global Data
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** API Functions
//*****************************************************************************
//*****************************************************************************



#ifdef __cplusplus
extern "C" {
#endif

GERR GD_I2C_Init(GD_I2C_INIT_PARAMS_S* paramsP);
GERR GD_I2C_Exit(void);
GERR GD_I2C_Open(GD_I2C_OPEN_PARAMS_S * openParamsP, GD_HANDLE* pHandle );
GERR GD_I2C_Close(GD_HANDLE * pHandle);
GERR GD_I2C_Read(GD_HANDLE *pHandle,U8 address,U8* regbuffer,U32 regbytes,U8 * buffer,U32 bytes);
GERR GD_I2C_Write(GD_HANDLE *pHandle,U8 address,U8 * buffer,U32 bytes);
GERR GD_I2C_SetOperationMode(GD_I2C_CHANNEL_E channel,GD_I2C_OPEN_MODE_E operationMode);
GERR GD_I2C_SetProtocol(GD_HANDLE *handleP,GD_I2C_PROTOCOL_E protocol);
GERR GD_I2C_SetMode(GD_HANDLE *handleP,GD_I2C_MODE_E Mode);


#ifdef __cplusplus
}
#endif



#endif /* _GD_I2C_H_ */


/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

