/******************************************************************************
**
** \file      gd_i2c_sw.c
**
** \brief     I2C driver.
**
**            (C) Goke Microelectronics China 2002 - 2007
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
**            This file implements the I2C API in software and replaces the
**            I2C hardware driver (\c gd_i2c.c). The driver uses a software
**            I2C protocol where the GPIO pins are accessed directly.
**
** \note      You can only use hardware or software I2C. The option is
**            toggeled via compiler switch \c "CFLAGS += -DGD_I2C_SOFTWARE".
**
** \version   \$Id: gd_i2c_sw.c,v 1.17 2010/07/21 13:14:00 benny Exp $
**
******************************************************************************/
/* to enable the software I2C (by using gpio read/write) instead of hardware */
/* I2C modify makfile via:                                                   */
/*       CFLAGS_USER += -DGD_I2C_SOFTWARE                                    */
/* and do not change the source code                                         */

/*---------------------------------------------------------------------------*/
/* include files                                                             */
/*---------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "gtypes.h"
#include "gd_int.h"
#include "gd_i2c.h"
#include "gd_gpio.h"
#include "gd_timer.h"

#ifdef GD_I2C_SOFTWARE /* do we use HW or SW I2C driver ?????? */
//#define GD_I2C_SW_DELAYS          1
/*---------------------------------------------------------------------------*/
/* local defines                                                             */
/*---------------------------------------------------------------------------*/
#define SI2C_BUS_FREE_TIME        0x080 // Bus free for 4,7  or 1,3 us

#ifdef GD_I2C_SW_DELAYS
#define SI2C_SDA_START_TIME       0x040 // hold time at start for 4,0 or 0,6
#define SI2C_SCL_START_TIME       0x040 // low time after start for 4,45 or 1,2
#define SI2C_SETUP_STOP_TIME      0x040 // low time after start for 4,0  or 0,6
#define SI2C_SETUP_DATA_TIME      0x003 // low time after start for 0,25 or 0,1
#define SI2C_HIGH_HOLD_TIME       0x040 // hold time at start for 4,0  or 0,6
#define SI2C_LOW_HOLD_TIME        0x070 // Bus free for 4,7  or 1,3
#else
#define SI2C_SDA_START_TIME       0x00 // hold time at start for 4,0 or 0,6
#define SI2C_SCL_START_TIME       0x00 // low time after start for 4,45 or 1,2
#define SI2C_SETUP_STOP_TIME      0x00 // low time after start for 4,0  or 0,6
#define SI2C_SETUP_DATA_TIME      0x00 // low time after start for 0,25 or 0,1
#define SI2C_HIGH_HOLD_TIME       0x00 // hold time at start for 4,0  or 0,6
#define SI2C_LOW_HOLD_TIME        0x00 // Bus free for 4,7  or 1,3
#endif

#define MAX_CHECK_WRA             0x40000
#define MAX_DATA_LENGTH           0xF000

#define I2C_SW_SDA_HIGH_HOLD_TIME 0x002 // low time after start for 4,0  or 0,6
#define I2C_SW_SDA_LOW_HOLD_TIME  0x003 // low time after start for 0,25 or 0,1
#define I2C_SW_SCL_HIGH_HOLD_TIME 0x050 // hold time at start for 4,0  or 0,6
#define I2C_SW_SCL_LOW_HOLD_TIME  0x001 // low time after start for 4,45 or 1,2

#define I2C_DATA_TYPE_OUTPUT_0  GD_GPIO_TYPE_OUTPUT_0
#define I2C_DATA_TYPE_OUTPUT_1  GD_GPIO_TYPE_OUTPUT_1
#define I2C_DATA_TYPE_INPUT     GD_GPIO_TYPE_INPUT_0
#define I2C_CLK_TYPE_OUTPUT_0   GD_GPIO_TYPE_OUTPUT_0
#define I2C_CLK_TYPE_OUTPUT_1   GD_GPIO_TYPE_OUTPUT_1
#define I2C_CLK_TYPE_INPUT      GD_GPIO_TYPE_INPUT_0

/*---------------------------------------------------------------------------*/
/* local data                                                                */
/*---------------------------------------------------------------------------*/
static U8        i2c_cvs_revision[] = "$Revision: 1.17 $";
static GBOOL     i2c_initialized    = GFALSE;
static GD_HANDLE i2c_sda_handle     = NULL;
static GD_HANDLE i2c_scl_handle     = NULL;
static S8        i2c_sda_pin        = -1;
static S8        i2c_scl_pin        = -1;
static S8        i2c_sda_pin2       = -1;
static S8        i2c_scl_pin2       = -1;


/*---------------------------------------------------------------------------*/
/* local functions                                                           */
/*---------------------------------------------------------------------------*/
GERR I2C_SW_writeSDA(U16 waitTime, U8 data);
GERR I2C_SW_writeSDAnoCheck(U16 waitTime, U8 data);
GERR I2C_SW_writeSCL(U16 waitTime, U8 data);
void I2C_SW_readSCL(U8 *pScl);
void I2C_SW_readSDA(U8 *pSda);
void I2C_SW_gpioIicStart();
GERR I2C_SW_gpioIicReStart();
GERR I2C_SW_gpioIicStop();

GERR I2C_SW_gpioIicRdAck();
GERR I2C_SW_gpioIicWrAck();
GERR I2C_SW_gpioIicWrNoAck();
GERR I2C_SW_gpioIicWrByte(U8 Data);
GERR I2C_SW_gpioIicRdByte(U8 *pData);


/*!
*******************************************************************************
**
** \brief  Cancel the write/read process of I2C bus.
**
** \sa      GD_I2C_Read() <br>
**          GD_I2C_Write()
**
******************************************************************************/
void GD_I2C_CancelProcess(GD_HANDLE *handleP)
{
    GERR gerr;
    int i;

    if (i2c_initialized == GFALSE)
        return; // GD_ERR_NOT_INITIALIZED;

    GD_GPIO_Close(&i2c_sda_handle);
    GD_GPIO_Close(&i2c_scl_handle);
    gerr = GD_GPIO_Open(i2c_sda_pin, I2C_DATA_TYPE_OUTPUT_1, NULL, &i2c_sda_handle);
    gerr = GD_GPIO_Open(i2c_scl_pin, I2C_CLK_TYPE_OUTPUT_1, NULL, &i2c_scl_handle);
    GD_GPIO_Write(i2c_sda_handle, 1);            // set SDA to high
    GD_GPIO_Write(i2c_scl_handle, 1);            // set SCL to high

    for (i = 0;i < SI2C_BUS_FREE_TIME;i++); // delay loop
}


/*!
*******************************************************************************
**
** \brief  Closes an I2C channel.
**
** \param  handleP Pointer to handle which can be used to control the hardware.
**
** \return Possible return codes:
**         - \c #GD_OK
**         - \c #GD_ERR_NOT_INITIALIZED
**
** \sa     GD_I2C_Open()
**
******************************************************************************/
GERR GD_I2C_Close(GD_HANDLE *handleP)
{
    if (i2c_initialized == GFALSE)
        return GD_ERR_NOT_INITIALIZED;
    if(i2c_sda_handle)
    {
        GD_GPIO_Close(&i2c_sda_handle);        // set SDA to high
        i2c_sda_handle = NULL;
    }
    if(i2c_scl_handle)
    {
        GD_GPIO_Close(&i2c_scl_handle);        // set SDA to high
        i2c_scl_handle = NULL;
    }

    *handleP = NULL;
    return GD_OK;
}


/*!
*******************************************************************************
**
** \brief  Get the current driver version.
**
** \return Pointer to the version string.
**
******************************************************************************/
U8 *GD_I2C_GetRevisionString(void)
{
    return(i2c_cvs_revision);
}


/*!
*******************************************************************************
**
** \brief  Initializes the driver.
**
**         This function initializes the driver. It is called only once
**         during boot time. It sets the ISR and the dedicated GPIO pins
**         for SDA and SCL.
**
**         The GPIO pins must be i2c_initialized in this function for each channel.
**         With the open function you are able to select different channels
**         driving multiple devices on each channel using different slave
**         adresses.
**
**         Currently the driver supports only one channel.
**
** \note   If you are using the software I2C driver (\c gd_i2c_sw.c) you have
**         to assign GPIO pins for SDA and SCL of the dedicated channel.
**         If you are using the hardware driver (\c gd_i2c.c) the GPIO pins
**         are autmatically assigned (only SmartMPEG and SmartMPEG-E).
**
** \note   SmartMPEG-L has no hardware I2C and therefore can not not use the
**         driver (\c gd_i2c.c).
**
** \param  paramsP  Pointer to init parameter structure.
**
** \return Possible return codes:
**         - \c #GD_OK
**         - \c #GD_ERR_ALREADY_INITIALIZED
**         - \c #GD_ERR_I2C_INT_ERR
**         - \c #GD_ERR_BAD_PARAMETER
**
** \sa     GD_I2C_Open()
** \sa     \c GD_I2C_INIT_PARAMS_S
**
******************************************************************************/
GERR GD_I2C_Init(GD_I2C_INIT_PARAMS_S* paramsP)
{
    GERR gerr;

    if( i2c_initialized == GTRUE )
        return  GD_ERR_ALREADY_INITIALIZED;

    i2c_sda_pin  = paramsP->gpioSdaPinCh1;
    i2c_scl_pin  = paramsP->gpioSclPinCh1;
    i2c_sda_pin2 = paramsP->gpioSdaPinCh2;
    i2c_scl_pin2 = paramsP->gpioSclPinCh2;

    i2c_initialized = GTRUE;

    if ((paramsP->mode != GD_I2C_AUTO_MASTER_MODE)&&
        (paramsP->mode != GD_I2C_GENERIC_MASTER_MODE))
        return GD_ERR_BAD_PARAMETER;

    return GD_OK;
}

GERR GD_I2C_Exit( void )
{
    if( i2c_initialized == 0 )
        return( GD_ERR_NOT_INITIALIZED );

    i2c_sda_pin        = -1;
    i2c_scl_pin        = -1;
    i2c_sda_pin2       = -1;
    i2c_scl_pin2       = -1;
    i2c_initialized = GFALSE;

    return( GD_OK );
}


/*!
*******************************************************************************
**
** \brief  Opens an I2C channel.
**
**         Here we set the datarate of the selected channel.
**         Currently only one channel is supported.
**
** \param  parameterP Pointer to the structure containing the settings for a
**                    specific I2C request.
** \param  handleP    Pointer to handle which can be used to control the hardware.
**
** \return Possible return codes:
**         - \c #GD_OK
**
** \sa     GD_I2C_Close()
**
******************************************************************************/
GERR GD_I2C_Open(GD_I2C_OPEN_PARAMS_S *parameterP, GD_HANDLE *handleP)
{
    int i;
    GERR gerr;
    if (i2c_initialized == GFALSE)
        return GD_ERR_NOT_INITIALIZED;
    if((parameterP == NULL) || (parameterP->speed == 0))
    {
        return GD_ERR_BAD_PARAMETER;
    }

    *handleP = parameterP->speed;

    /* Reset the SCL & SDA pin of I2C */
    switch(parameterP->channel)
    {
    case GD_I2C_CHANNEL_ONE:
        if((i2c_sda_pin == -1) || (i2c_scl_pin == -1))
        {
            return GD_ERR_BAD_PARAMETER;
        }
        gerr = GD_GPIO_Open(i2c_sda_pin, I2C_DATA_TYPE_OUTPUT_1, NULL, &i2c_sda_handle);
        if (gerr != GD_OK)
            return GD_ERR_I2C_INT_ERR;

        gerr = GD_GPIO_Open(i2c_scl_pin, I2C_CLK_TYPE_OUTPUT_1, NULL, &i2c_scl_handle);
        if (gerr != GD_OK)
            return GD_ERR_I2C_INT_ERR;
        break;
    case GD_I2C_CHANNEL_TWO:
        if((i2c_sda_pin2 == -1) || (i2c_scl_pin2 == -1))
        {
            return GD_ERR_BAD_PARAMETER;
        }
        gerr = GD_GPIO_Open(i2c_sda_pin2, I2C_DATA_TYPE_OUTPUT_1, NULL, &i2c_sda_handle);
        if (gerr != GD_OK)
            return GD_ERR_I2C_INT_ERR;

        gerr = GD_GPIO_Open(i2c_scl_pin2, I2C_CLK_TYPE_OUTPUT_1, NULL, &i2c_scl_handle);
        if (gerr != GD_OK)
            return GD_ERR_I2C_INT_ERR;
        break;
    }

    GD_GPIO_Write(i2c_sda_handle, 1);        // set SDA to high
    GD_GPIO_Write(i2c_scl_handle, 1);        // set SCL to high

    for (i = 0;i < SI2C_BUS_FREE_TIME;i++); // delay loop
    return GD_OK;
}


/*!
*******************************************************************************
**
** \brief  Read data from an I2C channel.
**
**         This function reads data from an I2C channel.
**         Two mode are support:
**         - Direct receive of \c rdDataLen bytes (set \c wrDataLen = 0).
**         - First transmit (\c wrDataLen +1) bytes, then restart and
**           receive \c rdDataLen bytes.
**
** \param  handleP     Pointer to handle which can be used to control the hardware.
** \param  msSlaveAddr Slave address of external I2C device.
** \param  writeDataP  Pointer to data to be transmitted to I2C device.
** \param  wrDataLen   Length of transmit data.
** \param  readDataP   Pointer to data to be received from I2C device.
** \param  rdDataLen   Length of receive data.
**
** \return Possible return codes:
**         - \c #GD_OK
**         - \c #GD_ERR_BAD_PARAMETER
**         - \c #GD_ERR_I2C_BUSY
**         - \c #GD_ERR_TIMEOUT
**
** \sa      GD_I2C_Open() <br>
**          GD_I2C_CancelProcess() <br>
**          GD_I2C_Write()
**
******************************************************************************/
GERR GD_I2C_Read(GD_HANDLE *handleP, U8 msSlaveAddr, U8* writeDataP,
                            U32 wrDataLen, U8* readDataP, U32 rdDataLen)
{
    GERR gerr;
    int  ix;
    U8   Data;

    if (i2c_initialized == GFALSE)
        return GD_ERR_NOT_INITIALIZED;

    gerr = 0;
    if (wrDataLen)
    {
        I2C_SW_gpioIicStart();
        gerr = I2C_SW_gpioIicWrByte(msSlaveAddr);
        if (gerr != GD_OK)
        {
          I2C_SW_gpioIicRdAck();          // generate one more clock and quit
          I2C_SW_gpioIicStop();           // send IIC Stop condition
          return(gerr);
        }
        gerr = I2C_SW_gpioIicRdAck();     // test acknowledge
        if (gerr != GD_OK)
        {
          I2C_SW_gpioIicStop();           // send IIC Stop condition
          return(gerr);
        }
        for (ix = 0; ix < wrDataLen; ix++)
        {
            Data  = *writeDataP ++;             // get TX-Data
            gerr = I2C_SW_gpioIicWrByte(Data);
            if (gerr != GD_OK)
            {
              I2C_SW_gpioIicRdAck();          // generate one more clock and quit
              I2C_SW_gpioIicStop();           // send IIC Stop condition
              return(gerr);
            }
            gerr = I2C_SW_gpioIicRdAck();      // test acknowledge
            if (gerr != GD_OK)
            {
              I2C_SW_gpioIicStop();           // send IIC Stop condition
              return(gerr);
            }
        }
        gerr = I2C_SW_gpioIicReStart();        // make "Repeated"-Start
        if (gerr != GD_OK)
        {
          I2C_SW_gpioIicStop();           // send IIC Stop condition
          return(gerr);
        }
    }
    //--- direct read ----
    else
    {
        I2C_SW_gpioIicStart();
    }
    gerr = I2C_SW_gpioIicWrByte(msSlaveAddr|0x0001);
    if (gerr != GD_OK)
    {
      I2C_SW_gpioIicRdAck();          // generate one more clock and quit
      I2C_SW_gpioIicStop();           // send IIC Stop condition
      return(gerr);
    }
    gerr = I2C_SW_gpioIicRdAck();     // test acknowledge
    if (gerr != GD_OK)
    {
      I2C_SW_gpioIicStop();           // send IIC Stop condition
      return(gerr);
    }

    while ((rdDataLen--)&&(!gerr))
    {
        gerr = I2C_SW_gpioIicRdByte(readDataP);// read Data
        if (gerr != GD_OK)
        {
            I2C_SW_gpioIicWrNoAck();            // Send NoAcknowledge
            I2C_SW_gpioIicStop();               // send IIC Stop condition
            return(gerr);
        }
        readDataP++;                            // next data
        if (rdDataLen)
            gerr = I2C_SW_gpioIicWrAck();       // Send Acknowledge
        else
            gerr = I2C_SW_gpioIicWrNoAck();     // Send NoAcknowledge
        if (gerr != GD_OK)
        {
            I2C_SW_gpioIicStop();               // send IIC Stop condition
            return(gerr);
        }
    }
    gerr = I2C_SW_gpioIicStop();                       // send IIC Stop condition
    return gerr;
}


/*!
*******************************************************************************
**
** \brief  This function resets SCL/SDA line.
**
******************************************************************************/
void GD_I2C_Reset(GD_HANDLE *handleP)
{
    GERR gerr;
    int i;

    if (i2c_initialized == GFALSE)
        return; // GD_ERR_NOT_INITIALIZED;

    GD_GPIO_Close(&i2c_sda_handle);
    GD_GPIO_Close(&i2c_scl_handle);

    gerr = GD_GPIO_Open(i2c_sda_pin, I2C_DATA_TYPE_OUTPUT_1, NULL, &i2c_sda_handle);
    gerr = GD_GPIO_Open(i2c_scl_pin, I2C_CLK_TYPE_OUTPUT_1, NULL, &i2c_scl_handle);

    GD_GPIO_Write(i2c_sda_handle, 1);            // set SDA to high
    GD_GPIO_Write(i2c_scl_handle, 1);            // set SCL to high

    for (i = 0;i<SI2C_BUS_FREE_TIME;i++);   // delay loop
}


/*!
*******************************************************************************
**
** \brief  Write data to I2C channel.
**
**         This function writes data to an I2C channel.
**         Transmit (\c dataLen + 1) bytes.
**
** \param  handleP     Pointer to handle which can be used to control the hardware.
** \param  msSlaveAddr Slave address of external I2C device.
** \param  dataP       Pointer to data to be transmitted to I2C device
**                     including subaddress if needed.
** \param  dataLen     Length of transmit data.
**
** \return Possible return codes:
**         - \c #GD_OK
**         - \c #GD_ERR_BAD_PARAMETER
**         - \c #GD_ERR_I2C_BUSY
**         - \c #GD_ERR_TIMEOUT
**
** \sa      GD_I2C_Open() <br>
**          GD_I2C_CancelProcess() <br>
**          GD_I2C_Read()
**
******************************************************************************/
GERR GD_I2C_Write(GD_HANDLE *handleP,U8 msSlaveAddr,U8* writeDataP,U32 dataLen)
{
    GERR gerr;
    int ix, nTotData;

    if (i2c_initialized == GFALSE)
        return GD_ERR_NOT_INITIALIZED;
    if (((dataLen + 1) > MAX_DATA_LENGTH)||(writeDataP == NULL)||(dataLen == 0))
        return GD_ERR_BAD_PARAMETER;

    nTotData = (dataLen);
    if (nTotData >= MAX_DATA_LENGTH)
        return GD_ERR_BAD_PARAMETER;
    gerr = 0;

    I2C_SW_gpioIicStart();
    gerr = I2C_SW_gpioIicWrByte(msSlaveAddr);
    if (gerr != GD_OK)
    {
      I2C_SW_gpioIicRdAck();          // generate one more clock and quit
      I2C_SW_gpioIicStop();           // send IIC Stop condition
      return(gerr);
    }
    gerr = I2C_SW_gpioIicRdAck();          // test acknowledge
    if (gerr != GD_OK)
    {
      I2C_SW_gpioIicStop();           // send IIC Stop condition
      return(gerr);
    }

    for (ix = 0; ix < nTotData; ix++)
    {
        gerr = I2C_SW_gpioIicWrByte((writeDataP[ix]));
        if (gerr != GD_OK)
        {
          I2C_SW_gpioIicRdAck();          // generate one more clock and quit
          I2C_SW_gpioIicStop();           // send IIC Stop condition
          return(gerr);
        }
        gerr = I2C_SW_gpioIicRdAck();      // test acknowledge
        if (gerr != GD_OK)
        {
          I2C_SW_gpioIicStop();           // send IIC Stop condition
          return(gerr);
        }
    }
    gerr = I2C_SW_gpioIicStop();
    return gerr;
}
GERR GD_I2C_SetOperationMode(GD_I2C_CHANNEL_E channel,GD_I2C_OPEN_MODE_E operationMode)
{
    return GD_OK;
}
GERR GD_I2C_SetProtocol(GD_HANDLE *handleP,GD_I2C_PROTOCOL_E protocol)
{
    return GD_OK;
}
GERR GD_I2C_SetMode(GD_HANDLE *handleP,GD_I2C_MODE_E Mode)
{
    return GD_OK;
}


/*---------------------------------------------------------------------------*/
/*  Read acknowledge condition at IIC-Bus                                    */
/*---------------------------------------------------------------------------*/
GERR I2C_SW_gpioIicRdAck()
{
    U8 SDA_LEVEL;
    GERR gerr;

    gerr = I2C_SW_writeSDAnoCheck(SI2C_HIGH_HOLD_TIME,   1);      // set SDA to high
    if (gerr != GD_OK)
        return(gerr);
    gerr = I2C_SW_writeSCL(1,   1);                 // set SCL to high
    if (gerr != GD_OK)
        return(gerr);
    /* read SDA level */
    I2C_SW_readSDA(&SDA_LEVEL);
    I2C_SW_writeSCL(SI2C_LOW_HOLD_TIME,  0);        // set SCL to low
    if (SDA_LEVEL)
        return GD_ERR_I2C_SL_NACK;                  // check SDA level
    return GD_OK;
}

/*---------------------------------------------------------------------------*/
/*  Read one Byte from IIC-Bus                                               */
/*---------------------------------------------------------------------------*/
GERR I2C_SW_gpioIicRdByte(U8 *pReadData)
{

    U16   Mask;
    U8    Data;                                       // read data
    U8    SDA_LEVEL;
    GERR  gerr;

    Data = 0;
    Mask = 0x0080;
    while (Mask)
    {
        gerr = I2C_SW_writeSCL(SI2C_HIGH_HOLD_TIME,   1);  // set SCL to high
        if (gerr != GD_OK)
            return (gerr);
        I2C_SW_readSDA(&SDA_LEVEL);
        if (SDA_LEVEL) Data |= Mask;                // read SDA level
        I2C_SW_writeSCL(SI2C_LOW_HOLD_TIME,  0);    // set SCL to low
        Mask >>= 1;                                 // shift mask one bit right
    }
    *pReadData = Data;
    return GD_OK;
}

/*---------------------------------------------------------------------------*/
/*  Send ReStart condition to IIC-Bus                                        */
/*---------------------------------------------------------------------------*/
GERR I2C_SW_gpioIicReStart()
{
    GERR gerr;
    gerr = I2C_SW_writeSDA(SI2C_SDA_START_TIME,   1);      // set SDA to High
    if (gerr != GD_OK)
        return (gerr);
    gerr = I2C_SW_writeSCL(SI2C_SCL_START_TIME,   1);      // set SCL to High
    if (gerr != GD_OK)
        return (gerr);
    I2C_SW_writeSDA(SI2C_SDA_START_TIME,   0);      // set SDA to low
    I2C_SW_writeSCL(SI2C_SCL_START_TIME,   0);      // set SCL to low
    return (GD_OK);
}

/*---------------------------------------------------------------------------*/
/*  Send Start condition to IIC-Bus                                          */
/*---------------------------------------------------------------------------*/
void I2C_SW_gpioIicStart()
{
    I2C_SW_writeSDA(SI2C_SDA_START_TIME,  0);       // set SDA to low
    I2C_SW_writeSCL(SI2C_SCL_START_TIME,  0);       // set SCL to low
}

/*---------------------------------------------------------------------------*/
/*  Send Stop condition to IIC-Bus                                           */
/*---------------------------------------------------------------------------*/
GERR I2C_SW_gpioIicStop()
{
    U16 i;
    GERR gerr;

    I2C_SW_writeSDA(1,   0);                            // set SDA to low
    gerr = I2C_SW_writeSCL(SI2C_SETUP_STOP_TIME,   1);  // set SCL to high
    if (gerr != GD_OK)
        return (gerr);
    gerr = I2C_SW_writeSDA(SI2C_SETUP_STOP_TIME,   1);         // set SDA to high
    for (i = 0;i < SI2C_BUS_FREE_TIME;i++); // delay loop
    return (gerr);
}

/*---------------------------------------------------------------------------*/
/*  Write acknowledge condition at IIC-Bus                                   */
/*---------------------------------------------------------------------------*/
GERR I2C_SW_gpioIicWrAck()
{
    GERR  gerr;

    I2C_SW_writeSDA(SI2C_LOW_HOLD_TIME,   0);       // set SDA to low
    /* generate clock pulse */
    gerr = I2C_SW_writeSCL(1,   1);                 // set SCL to high
    if (gerr != GD_OK)
        return (gerr);
    I2C_SW_writeSCL(SI2C_LOW_HOLD_TIME,  0);        // set SCL to low

    gerr = I2C_SW_writeSDA(SI2C_HIGH_HOLD_TIME,   1);      // set SDA to high
    return (gerr);
}

/*---------------------------------------------------------------------------*/
/*  Write one Byte to IIC-Bus                                                */
/*---------------------------------------------------------------------------*/
GERR I2C_SW_gpioIicWrByte(U8 Data)
{
    U16  Mask;
    #ifdef GD_I2C_SW_DELAYS
    int  i;
    #endif
    GERR gerr;

    Mask = 0x0080;
    #ifdef GD_I2C_SW_DELAYS
    for (i = 0; i < SI2C_HIGH_HOLD_TIME; i++);          // delay loop
    #endif
    while (Mask)
    {
        if (Data & Mask)
        {
            gerr = I2C_SW_writeSDA(I2C_SW_SDA_HIGH_HOLD_TIME,1); // set SDA to high
            if (gerr != GD_OK)
                return (gerr);
        }
        else
            I2C_SW_writeSDA(I2C_SW_SDA_LOW_HOLD_TIME, 0); // set SDA to low
        gerr = I2C_SW_writeSCL(I2C_SW_SCL_HIGH_HOLD_TIME, 1);  // set SCL to high
        if (gerr != GD_OK)
            return (gerr);
        I2C_SW_writeSCL(I2C_SW_SCL_LOW_HOLD_TIME,  0);  // set SCL to low
        Mask >>= 1;                                     // shift mask one bit right
    }
    return GD_OK;
}

/*---------------------------------------------------------------------------*/
/*  Write no acknowledge condition at IIC-Bus                                */
/*---------------------------------------------------------------------------*/
GERR I2C_SW_gpioIicWrNoAck()
{
    U8   SDA_LEVEL;
    GERR gerr;

    gerr = I2C_SW_writeSDAnoCheck(SI2C_HIGH_HOLD_TIME,   1);        // set SDA to high
    if (gerr != GD_OK)
        return (gerr);
    I2C_SW_readSDA(&SDA_LEVEL);
    if (!(SDA_LEVEL))
        return GD_ERR_I2C_BUSY;                       // check SDA level
    gerr = I2C_SW_writeSCL(SI2C_HIGH_HOLD_TIME,   1); // set SCL to high
    if (gerr != GD_OK)
        return (gerr);
    I2C_SW_writeSCL(I2C_SW_SCL_LOW_HOLD_TIME,  0);    // set SCL to low
    return GD_OK;
}

void I2C_SW_readSCL(U8 *pScl)
{
    GD_GPIO_SetType(i2c_scl_handle, I2C_CLK_TYPE_INPUT);
    GD_GPIO_Read(i2c_scl_handle, pScl);
}

void I2C_SW_readSDA(U8 *pSda)
{
    #ifdef GD_I2C_SW_DELAYS
    U16 i;
    #endif
    GD_GPIO_SetType(i2c_sda_handle, I2C_DATA_TYPE_INPUT);
    #ifdef GD_I2C_SW_DELAYS
    for (i = 0; i < 10; i++);             // delay loop
    #endif
    GD_GPIO_Read(i2c_sda_handle, pSda);
}

GERR I2C_SW_writeSCL(U16 waitTime, U8 data)
{
    U32 i;
    U8  SCL_LEVEL;

    if (data > 0)
    {
      GD_GPIO_SetType(i2c_scl_handle, I2C_CLK_TYPE_OUTPUT_1);
      GD_GPIO_Write(i2c_scl_handle, 1);      // set SCL to high
      i = MAX_CHECK_WRA;
      /*I2C_SW_readSCL(&SCL_LEVEL);
      while ((SCL_LEVEL != 1) && (i > 0))
      {
          //GD_GPIO_SetType(i2c_scl_handle, I2C_GPIO_TYPE_OUTPUT_1);
          //GD_GPIO_Write(i2c_scl_handle, 1);      // set SCL to high
          I2C_SW_readSCL(&SCL_LEVEL);
          i--;                                  // wait high level at SCL
      }*/
      if (!i)
          return GD_ERR_TIMEOUT;
    }
    else
    {
      GD_GPIO_SetType(i2c_scl_handle, I2C_CLK_TYPE_OUTPUT_0);
      GD_GPIO_Write(i2c_scl_handle, 0);         // set SCL to low
      i = MAX_CHECK_WRA;
      /*I2C_SW_readSCL(&SCL_LEVEL);
      while ((SCL_LEVEL != 0) && (i > 0))
      {
          GD_GPIO_SetType(i2c_scl_handle, I2C_GPIO_TYPE_OUTPUT_0);
          GD_GPIO_Write(i2c_scl_handle, 0);      // set SCL to high
          I2C_SW_readSCL(&SCL_LEVEL);
          i--;                                  // wait high level at SCL
      }*/
      if (!i)
          return GD_ERR_TIMEOUT;
    }
    #ifdef GD_I2C_SW_DELAYS
    for (i = 0; i < waitTime; i++);             // delay loop
    #endif
    return (GD_OK);
}

GERR I2C_SW_writeSDA(U16 waitTime, U8 data)
{
    U32 i;
    U8  SDA_LEVEL;

    if (data > 0)
    {
        GD_GPIO_SetType(i2c_sda_handle, I2C_DATA_TYPE_OUTPUT_1);
        GD_GPIO_Write(i2c_sda_handle, 1);        // set SDA to high
        i = MAX_CHECK_WRA;
        /*I2C_SW_readSDA(&SDA_LEVEL);
        while ((SDA_LEVEL != 1) && (i > 0))
        {
            GD_GPIO_SetType(i2c_sda_handle, I2C_GPIO_TYPE_OUTPUT_1);
            GD_GPIO_Write(i2c_sda_handle, 1);        // set SDA to high
            I2C_SW_readSDA(&SDA_LEVEL);
            i--;                                  // wait high level at SDA
        }*/
        if (!i)
            return GD_ERR_TIMEOUT;
    }
    else
    {
        GD_GPIO_SetType(i2c_sda_handle, I2C_DATA_TYPE_OUTPUT_0);
        GD_GPIO_Write(i2c_sda_handle, 0);        // set SDA to low
        i = MAX_CHECK_WRA;
        /*I2C_SW_readSDA(&SDA_LEVEL);
        while ((SDA_LEVEL != 0) && (i > 0))
        {
            GD_GPIO_SetType(i2c_sda_handle, I2C_GPIO_TYPE_OUTPUT_0);
            GD_GPIO_Write(i2c_sda_handle, 0);        // set SDA to high
            I2C_SW_readSDA(&SDA_LEVEL);
            i--;                                  // wait high level at SDA
        }*/
        if (!i)
            return GD_ERR_TIMEOUT;
    }
    #ifdef GD_I2C_SW_DELAYS
    for (i = 0; i < waitTime; i++);             // delay loop
    #endif
    return (GD_OK);
}

GERR I2C_SW_writeSDAnoCheck(U16 waitTime, U8 data)
{
    U32 i;
    U8  SDA_LEVEL;

    if (data > 0)
    {
        GD_GPIO_SetType(i2c_sda_handle, I2C_DATA_TYPE_OUTPUT_1);
        GD_GPIO_Write(i2c_sda_handle, 1);        // set SDA to high
    }
    else
    {
        GD_GPIO_SetType(i2c_sda_handle, I2C_DATA_TYPE_OUTPUT_0);
        GD_GPIO_Write(i2c_sda_handle, 0);        // set SDA to low
    }
    #ifdef GD_I2C_SW_DELAYS
    for (i = 0; i < waitTime; i++);             // delay loop
    #endif
    return (GD_OK);
}

#endif  /* GD_I2C_SOFTWARE  */


/* Version History */
/******************************************************************************

$Log: gd_i2c_sw.c,v $
Revision 1.18  2010/07/21 13:31:00  benny
[LEV 2] Porting H10,H20C,H20B,H01 together, use macro to control PCR sync and soft sync

Revision 1.17  2009/06/16 13:14:00  sgehre
[LEV 2] extended defines for SmartMPEG-C to also include SmartMPEG-M

Revision 1.16  2007/08/15 08:03:22  skau
I2C_SW_writeSDA caused problem while checking SDA
level at acknowledge. Extra function without check option added.

Revision 1.15  2007/07/04 14:06:54  mneuma
Check level in I2C_SW_writeSDA() was done on clk and not data line.

Revision 1.14  2007/01/31 06:43:26  shelle
Copyright updated

Revision 1.13  2006/10/06 10:58:52  skau
RN: input/output pin configuration order changed to overcome
SmartMPEG-L's limitation to push pull buffers. Handling of error feedback
from subroutines improved.

Revision 1.12  2006/08/01 12:45:14  jrende
RN: Corrected wrong clock and data pin settings.

Revision 1.11  2006/04/21 12:39:23  shelle
Version history corrected.

Revision 1.10  2006/03/08 13:13:12  wlaris
Adjusted for GNU compiler usage.

Revision 1.9  2005/12/28 14:32:17  mneuma
Doxygen updated.

Revision 1.8  2005/12/15 13:38:58  mneuma
RN: Init structure extended for I2C GPIO assignment.

Revision 1.6  2005/11/18 11:28:02  mneuma
GPIO handling for Smart-L added.

Revision 1.5  2004/03/30 16:33:22  shelle
BOOL, TRUE, FALSE replaced by GBOOL, GTRUE and GFALSE.

Revision 1.4  2004/03/22 15:25:51  mneuma
use GD_GPIO_TYPE_OUTPUT_OPEN_DRAIN instead
GD_GPIO_TYPE_OUTPUT_PUSH_PULL

Revision 1.3  2004/03/09 16:28:05  mneuma
clean-up

Revision 1.2  2004/03/08 16:06:10  mneuma
function calls reordered

Revision 1.1  2004/03/08 16:01:50  mneuma
initial version by Terence
******************************************************************************/
