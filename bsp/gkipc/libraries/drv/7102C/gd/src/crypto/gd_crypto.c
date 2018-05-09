/*!
*****************************************************************************
** \file        gd_lib/GK7101/src/crypto/crypto.c
**
** \version     $Id$
**
** \brief
**
** \attention   THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**              ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**              OMMISSIONS
**
** (C) Copyright 2012-2013 by GOKE MICROELECTRONICS CO.,LTD
**
*****************************************************************************
*/
#include <stdio.h>
#include <string.h>

#include "gtypes.h"
#include "gh_crypto.h"
#include "gd_int.h"
#include "gd_timer.h"
#include "gd_crypto.h"


//*****************************************************************************
//*****************************************************************************
//** Local Defines
//*****************************************************************************
//*****************************************************************************
#define ENCRPT  0
#define DECRPT  1

//*****************************************************************************
//*****************************************************************************
//** Local structures
//*****************************************************************************
//*****************************************************************************
typedef struct
{
    GD_CRYPTO_MODE_E    mode;
    GBOOL               useint;
    GD_HANDLE           inthandle;
    void                (*notifyFct)();
}GD_CRYPTO_DeviceT;



//*****************************************************************************
//*****************************************************************************
//** Global Data
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** Local Data
//*****************************************************************************
//*****************************************************************************
static GD_CRYPTO_DeviceT    desdevice;
static GD_CRYPTO_DeviceT    aesdevice;
static GD_HANDLE            deshandle = 0;
static GD_HANDLE            aeshandle = 0;
static volatile GBOOL       des_done __attribute__ ((section(".nocache_buffer")));
static volatile GBOOL       aes_done __attribute__ ((section(".nocache_buffer")));


//*****************************************************************************
//*****************************************************************************
//** Local Functions Declaration
//*****************************************************************************
//*****************************************************************************
static GISR2 gd_aes_crypt_isr(void);
static GISR2 gd_des_crypt_isr(void);
static GERR gd_crypto_ProcessData(GD_HANDLE handle, U32 type, GD_CRYPTO_DATA_T* data_in, GD_CRYPTO_DATA_T* data_out);


//*****************************************************************************
//*****************************************************************************
//** API Functions
//*****************************************************************************
//*****************************************************************************
GERR GD_CRYPTO_Open(GD_CRYPTO_OpenParamsT* pOpenParams, GD_HANDLE* pHandle)
{
    U32 i,nkey;
    GD_INT_OPEN_PARAMS_S OpenParams;
    GD_CRYPTO_DeviceT* device;
    if(pHandle == NULL)
    {
        return GD_ERR_NOT_INITIALIZED;
    }
    if((pOpenParams == NULL) || (pOpenParams->pkey == NULL))
    {
        return GD_ERR_BAD_PARAMETER;
    }
    if (pOpenParams->mode >= GD_CRYPTO_MODE_MAX)
    {
        return GD_ERR_BAD_PARAMETER;
    }
    nkey = 2;
    switch(pOpenParams->mode)
    {
    case GD_CRYPTO_DES:
        if(deshandle)
        {
            return GD_ERR_ALREADY_OPEN;
        }
        nkey = 2;
        for(i=0;i<nkey;i++)
        {
            GH_CRYPTO_set_DES_Key(i,(*pOpenParams->pkey).key[i]);
        }
        desdevice.mode      = pOpenParams->mode;
        desdevice.useint    = pOpenParams->useint;
        desdevice.notifyFct = pOpenParams->notifyFct;

        *pHandle  = (GD_HANDLE)&desdevice;
        deshandle = (GD_HANDLE)&aesdevice;
        break;
    case GD_CRYPTO_AES_128:
        if(aeshandle)
        {
            return GD_ERR_ALREADY_OPEN;
        }
        nkey = 4;
        for(i=0;i<nkey;i++)
        {
            GH_CRYPTO_set_AES_128_Key(i,(*pOpenParams->pkey).key[i]);
        }
        aesdevice.mode      = pOpenParams->mode;
        aesdevice.useint    = pOpenParams->useint;
        aesdevice.notifyFct = pOpenParams->notifyFct;

        *pHandle  = (GD_HANDLE)&aesdevice;
        aeshandle = (GD_HANDLE)&aesdevice;
        break;
    case GD_CRYPTO_AES_192:
        if(aeshandle)
        {
            return GD_ERR_ALREADY_OPEN;
        }
        nkey = 6;
        for(i=0;i<nkey;i++)
        {
            GH_CRYPTO_set_AES_192_Key(i,(*pOpenParams->pkey).key[i]);
        }
        aesdevice.mode      = pOpenParams->mode;
        aesdevice.useint    = pOpenParams->useint;
        aesdevice.notifyFct = pOpenParams->notifyFct;

        *pHandle  = (GD_HANDLE)&aesdevice;
        aeshandle = (GD_HANDLE)&aesdevice;
        break;
    case GD_CRYPTO_AES_256:
        if(aeshandle)
        {
            return GD_ERR_ALREADY_OPEN;
        }
        nkey = 8;
        for(i=0;i<nkey;i++)
        {
            GH_CRYPTO_set_AES_256_Key(i,(*pOpenParams->pkey).key[i]);
        }
        aesdevice.mode      = pOpenParams->mode;
        aesdevice.useint    = pOpenParams->useint;
        aesdevice.notifyFct = pOpenParams->notifyFct;

        *pHandle  = (GD_HANDLE)&aesdevice;
        aeshandle = (GD_HANDLE)&aesdevice;
        break;
    }

    device = (GD_CRYPTO_DeviceT*)(*pHandle);
    if(device->useint)
    {
        OpenParams.sensitivity  = GD_INT_RISING_EDGE;
        OpenParams.priority     = GD_INT_MID_PRIORITY;
        if(pOpenParams->mode == GD_CRYPTO_DES)
        {
            GH_CRYPTO_set_DES_Interrupt_En(1);
#if defined(GK710X)            
            OpenParams.type     = GD_INT_DES_OUTPUT_READY_IRQ;
#else
            OpenParams.type     = GD_INT_CRYPTO_OUTPUT_READY_IRQ;
#endif            
            OpenParams.isrFct.midPrio = gd_des_crypt_isr;
        }
        else
        {
            GH_CRYPTO_set_AES_Interrupt_En(1);
#if defined(GK710X)            
            OpenParams.type     = GD_INT_AES_OUTPUT_READY_IRQ;
#else
            OpenParams.type     = GD_INT_CRYPTO_OUTPUT_READY_IRQ;
#endif               
            OpenParams.isrFct.midPrio = gd_aes_crypt_isr;
        }
        GD_INT_Open(&OpenParams, &device->inthandle);
        GD_INT_Enable(&device->inthandle, 1);
    }
    return GD_OK;
}

GERR GD_CRYPTO_Close(GD_HANDLE* pHandle)
{
    GD_CRYPTO_DeviceT* device = (GD_CRYPTO_DeviceT*)(*pHandle);
    if(device == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    switch(device->mode)
    {
    case GD_CRYPTO_DES:
        deshandle = 0;
        break;
    case GD_CRYPTO_AES_128:
        aeshandle = 0;
        break;
    case GD_CRYPTO_AES_192:
        aeshandle = 0;
        break;
    case GD_CRYPTO_AES_256:
        aeshandle = 0;
        break;
    }
    if(device->mode == GD_CRYPTO_DES)
    {
        GH_CRYPTO_set_DES_Interrupt_En(0);
    }
    else
    {
        GH_CRYPTO_set_AES_Interrupt_En(0);
    }
    if(device->useint && device->inthandle)
    {
        GD_INT_Enable(&device->inthandle, 0);
        GD_INT_Close(&device->inthandle);
    }
    *pHandle = 0;
    return GD_OK;
}

GERR GD_CRYPTO_EncrptData(GD_HANDLE handle, GD_CRYPTO_DATA_T* data_in, GD_CRYPTO_DATA_T* data_out)
{
    return gd_crypto_ProcessData(handle, ENCRPT, data_in, data_out);
}

GERR GD_CRYPTO_DecrptData(GD_HANDLE handle, GD_CRYPTO_DATA_T* data_in, GD_CRYPTO_DATA_T* data_out)
{
    return gd_crypto_ProcessData(handle, DECRPT, data_in, data_out);
}


//*****************************************************************************
//*****************************************************************************
//** Local Functions
//*****************************************************************************
//*****************************************************************************
static GISR2 gd_des_crypt_isr(void)
{
    des_done = GTRUE;
}

static GISR2 gd_aes_crypt_isr(void)
{
    aes_done = GTRUE;
}

static GERR gd_crypto_ProcessData(GD_HANDLE handle, U32 type, GD_CRYPTO_DATA_T* data_in, GD_CRYPTO_DATA_T* data_out)
{
    GD_CRYPTO_DeviceT* device = (GD_CRYPTO_DeviceT*)handle;
    if(device == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    if((data_in == NULL) || (data_out == NULL))
    {
        return GD_ERR_BAD_PARAMETER;
    }
    switch(device->mode)
    {
    case GD_CRYPTO_DES:
        des_done = GFALSE;
        GH_CRYPTO_set_DES_Opcode(type);
        GH_CRYPTO_set_DES_Input(0, data_in->des_data.data_hi);
        GH_CRYPTO_set_DES_Input(1, data_in->des_data.data_lo);
        if(device->useint)
        {
            do
            {
                GD_TIMER_Delay(2);
            }while(!des_done);
            data_out->des_data.data_hi = GH_CRYPTO_get_DES_Output(0);
            data_out->des_data.data_lo = GH_CRYPTO_get_DES_Output(1);
        }
        else
        {
            while(!GH_CRYPTO_get_DES_Output_Rdy())
            {
                ;
            }
            data_out->des_data.data_hi = GH_CRYPTO_get_DES_Output(0);
            data_out->des_data.data_lo = GH_CRYPTO_get_DES_Output(1);
        }
        break;
    case GD_CRYPTO_AES_128:
    case GD_CRYPTO_AES_192:
    case GD_CRYPTO_AES_256:
        aes_done = GFALSE;
        GH_CRYPTO_set_AES_Opcode(type);
        GH_CRYPTO_set_AES_Input(0, data_in->aes_data.data_127_96);
        GH_CRYPTO_set_AES_Input(1, data_in->aes_data.data_95_64);
        GH_CRYPTO_set_AES_Input(2, data_in->aes_data.data_63_32);
        GH_CRYPTO_set_AES_Input(3, data_in->aes_data.data_31_0);
        if(device->useint)
        {
            do
            {
                GD_TIMER_Delay(2);
            }while(!aes_done);
            data_out->aes_data.data_127_96 = GH_CRYPTO_get_AES_Output(0);
            data_out->aes_data.data_95_64  = GH_CRYPTO_get_AES_Output(1);
            data_out->aes_data.data_63_32  = GH_CRYPTO_get_AES_Output(2);
            data_out->aes_data.data_31_0   = GH_CRYPTO_get_AES_Output(3);
        }
        else
        {
            while(!GH_CRYPTO_get_AES_Output_Rdy())
            {
                ;
            }
            data_out->aes_data.data_127_96 = GH_CRYPTO_get_AES_Output(0);
            data_out->aes_data.data_95_64  = GH_CRYPTO_get_AES_Output(1);
            data_out->aes_data.data_63_32  = GH_CRYPTO_get_AES_Output(2);
            data_out->aes_data.data_31_0   = GH_CRYPTO_get_AES_Output(3);
        }
        break;
    }
    return GD_OK;
}




