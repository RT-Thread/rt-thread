/*!
*******************************************************************************
**
** \file      gd_i2s.h
**
** \brief     I2S.
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
#ifndef _GD_I2S_H_
#define _GD_I2S_H_

#include <gtypes.h>
#include "gmodids.h"
#include "gd_int.h"
#include "gd_uart.h"


typedef     GD_INT_DATA_S* (*GD_I2S_ISR_T)(U8 channelIndex);

/*!
*******************************************************************************
**
** \brief I2S driver error codes.
**
*******************************************************************************
*/
enum
{
    GD_ERR_I2S_TYPE_NOT_SUPPORTED = 0, //!< Device not supported.
    GD_ERR_I2S_INT_ERR,
    GD_ERR_I2S_NOT_OPEN,
    GD_ERR_I2S_BUSY,
	GD_ERR_I2S_WAIT,    
};

/*!
*******************************************************************************
**
** \brief i2s channel.
**
*******************************************************************************
*/

typedef enum
{
    GD_I2S_CHANNEL_2 = 0,     //!< I2S  2 channel.
    GD_I2S_CHANNEL_4 = 1,     //!< I2S  4 channel.
    GD_I2S_CHANNEL_6 = 2,     //!< I2S  6 channel.
}GD_I2S_CHANNEL_E;

/*!
*******************************************************************************
**
** \brief I2S operition modes.
**
** \sa    GD_I2S_MODE_S
**
******************************************************************************/
typedef enum
{
    GD_I2S_LEFT_MODE  = 0,   //!< Left justify mode.
    GD_I2S_RIGHT_MODE = 1,  //!< Right justify  mode.
    GD_I2S_MSB_MODE   = 2,    //!< MSB extend mode.
    GD_I2S_I2S_MODE   = 4,    //!< I2S mode.
    GD_I2S_DSP_MODE   = 6,    //!< DSP mode.
}GD_I2S_MODE_E;

/*!
*******************************************************************************
**
** \brief I2S datarate speed modes.
**
** \sa    GD_I2S_SPEED_E
**
******************************************************************************/
typedef enum
{
	GD_I2S_24000BPS = 24000,
    GD_I2S_32000BPS = 32000,     //!< 32kHz datarate.
    GD_I2S_44100BPS = 44100,
    GD_I2S_48000BPS = 48000,       //!< 48kHz datarate.
    GD_I2S_96000BPS = 96000,
}GD_I2S_SPEED_E;

/*!
*******************************************************************************
**
** \brief I2S datarate wlen modes.
**
** \sa    GD_I2S_WLEN_E
**
******************************************************************************/
typedef enum
{
    GD_I2S_16BIT = 16,     //!< 32kHz datarate.
    GD_I2S_24BIT = 24,        //!< 48kHz datarate.
}GD_I2S_WLEN_E;



/*!
*******************************************************************************
**
** \brief I2S operition modes.
**
** \sa    GD_I2S_OPEN_MODE_E
**
******************************************************************************/
typedef enum
{
    GD_I2S_GENERIC_MASTER_MODE, //!< Generic master mode.
    GD_I2S_GENERIC_SLAVER_MODE, //!< Generic slave mode.
    GD_I2S_AUTO_MASTER_MODE,    //!< Auto master mode.
    GD_I2S_AUTO_SLAVER_MODE,    //!< Auto slave mode.
    GD_I2S_DMA_MASTER_MODE,     //!< DMA master mode.
    GD_I2S_DMA_SLAVER_MODE,     //!< DMA slave mode.
}GD_I2S_OPEN_MODE_E;


enum
{
	I2S_EVENT_FRAME          = 1, /* received one audio frame or send finished one audio frame */
    I2S_EVENT_WILL_OVERFLOW  = 2,
	I2S_EVENT_WILL_UNDERFLOW = 3,	
    I2S_EVENT_ALREADY_OVERFLOW  = 4,
	I2S_EVENT_ALREADY_UNDERFLOW = 5,	
	I2S_EVENT_UNDEFINED         = 6,
};

typedef void (*GD_I2S_Notifier)(U32 event);


/*!
*******************************************************************************
**
** I2S INIT  parameter.
**
******************************************************************************/
typedef struct
{
   GBOOL               master;   
   GD_I2S_CHANNEL_E    channel;
   GD_I2S_MODE_E       mode;
   GD_I2S_SPEED_E      speed;
   GD_I2S_WLEN_E       wlen; 
} GD_I2S_INIT_PARAM_S;


typedef struct
{
   U32      		   frameSize;
   GD_I2S_Notifier     notifier; 
} GD_I2S_OPEN_PARAM_S;


#ifdef __cplusplus
extern "C" {
#endif

GERR GD_I2S_RX_Open(GD_I2S_OPEN_PARAM_S *openParams);
GERR GD_I2S_RX_Enable(void);
GERR GD_I2S_RX_Disable(void);
GERR GD_I2S_RX_Read_Frame(U8 *data, U32 *length);
GERR GD_I2S_RX_Close(void);
GERR GD_I2S_TX_Open(GD_I2S_OPEN_PARAM_S *openParams);
GERR GD_I2S_TX_Enable(void);
GERR GD_I2S_TX_Disable(void);
GERR GD_I2S_TX_Mute(void);
GERR GD_I2S_TX_Unmute(void);
GERR GD_I2S_TX_Write_Frame(U8 *data, U32 length);
GERR GD_I2S_TX_Close(void);
GERR GD_I2S_SetClock(GD_I2S_SPEED_E speed);
GERR GD_I2S_SetWlen(GD_I2S_WLEN_E wlen);
GERR GD_I2S_SetMode(GD_I2S_MODE_E mode);
GERR GD_I2S_SetChannel(GD_I2S_CHANNEL_E channel);
GERR GD_I2S_Init(GD_I2S_INIT_PARAM_S *initParams);
GERR GD_I2S_Bind_Rx2Tx(void);
GERR GD_I2S_Unbind_Rx2Tx(void);
GERR GD_I2S_Exit(void);



#ifdef __cplusplus
}
#endif



#endif /* _GD_I2C_H_ */


/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

