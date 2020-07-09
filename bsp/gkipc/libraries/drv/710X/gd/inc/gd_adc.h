/*!
*******************************************************************************
**
** \file      gd_adc.h
**
** \brief     ADC.
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
#ifndef _GD_ADC_H_
#define _GD_ADC_H_

#include "gmodids.h"



//*****************************************************************************
//*****************************************************************************
//** Defines and Macros
//*****************************************************************************
//*****************************************************************************
#define GD_ADC_ERR_BASE             (GD_ADC_MODULE_ID << 16)
#define GD_ADC_AUX_ATOP_INITIALIZE  0x025A
#define GD_ADC_CONTROL_INITIALIZE   0x000A




//*****************************************************************************
//*****************************************************************************
//** Enumerated types
//*****************************************************************************
//*****************************************************************************

/*!
*******************************************************************************
**
** \brief ADC driver error codes.
**
*******************************************************************************
*/
enum
{
    GD_ERR_ADC_TYPE_NOT_SUPPORTED = GD_ADC_ERR_BASE, //!< Device not supported.
};

/*---------------------------------------------------------------------------*/
/* types, enums and structures                                               */
/*---------------------------------------------------------------------------*/
/*!
*******************************************************************************
**
** \brief ADC channel number.
**
** \sa    GD_ADC_OPEN_PARAMS_S
**
******************************************************************************/
typedef enum
{
    GD_ADC_ENABLE_DISABLE = 0,
    GD_ADC_ENABLE_ENABLE,
    GD_ADC_ENABLE_COUNT,
}GD_ADC_ENABLE_E;

typedef enum
{
    GD_ADC_CONTROL_CHANNEL_ONE = 0x5, //!< ADC pad_sar_key1.
    GD_ADC_CONTROL_CHANNEL_TWO = 0x6, //!< ADC pad_sar_key2.
    GD_ADC_CONTROL_CHANNEL_COUNT,
}GD_ADC_CONTROL_CHANNEL_E;

typedef enum
{
    GD_ADC_CHANNEL_ONE = 0, //!< ADC channel 1.
    GD_ADC_CHANNEL_TWO,     //!< ADC channel 2.
    GD_ADC_CHANNEL_COUNT,
}GD_ADC_CHANNEL_E;

enum
{
    GD_ADC_REQ_CHANNEL_ONE = 1, //!< ADC req channel 1.
    GD_ADC_REQ_CHANNEL_TWO,     //!< ADC req channel 2.
};
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
** \sa    GD_ADC_Open() <BR>
**
******************************************************************************/
typedef struct
{
    U32     val_lo : 10;
    U32            :  5;
    U32     val_hi : 10;
    U32            :  5;
    U32     en_lo  :  1;
    U32     en_hi  :  1;
} GD_ADC_CONTROL_S;
typedef union
{
    U32                     data;
    GD_ADC_CONTROL_S        control;
}GD_ADC_CRYPTO_DATA_T;

typedef struct
{
    GD_ADC_CHANNEL_E channel;
    GD_ADC_CRYPTO_DATA_T control;
} GD_ADC_OPEN_PARAMS_S;


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

GERR GD_ADC_Init(void);
GERR GD_ADC_Exit(void);
GERR GD_ADC_Open(GD_ADC_OPEN_PARAMS_S * openParamsP, GD_HANDLE* pHandle );
GERR GD_ADC_Close(GD_HANDLE * pHandle);
GERR GD_ADC_Read(GD_HANDLE *pHandle, U32* data);

#ifdef __cplusplus
}
#endif



#endif /* _GD_ADC_H_ */


/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

