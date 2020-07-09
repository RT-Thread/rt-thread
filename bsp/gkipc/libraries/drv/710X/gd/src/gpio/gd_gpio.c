/*
*******************************************************************************
**
** \file      gd_gpio.c
**
** \brief     GPIO driver (core functions).
**
**            Copyright:   2012 - 2013 (C) GoKe Microelectronics ShangHai Branch
**
** \attention THIS SAMPLE CODE IS PROVDMAD AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \version
**
*******************************************************************************
*/
#include <stdio.h>
#include <string.h>
#include "gtypes.h"

#include <gh_gpio.h>
#include <gh_debug_rct.h>

#include "gd_int.h"
#include "gd_gpio.h"

#define GD_GPIO_PIN_COUNT 64

/*
***********************************************************
** local structures
***********************************************************
*/
typedef struct
{
    U8             number;
    GBOOL          in_use;
    GD_GPIO_TYPE_E type;
    void         (*notifier)(void);
}GD_GPIO_HANDLE_S;

enum
{
    GD_GPIO_IRQ_ENABLE = 1,
    GD_GPIO_IRQ_CLEAR  = 0
};

/*
***********************************************************
** local variables
***********************************************************
*/
static GD_GPIO_HANDLE_S gd_gpio_handle_array[GD_GPIO_PIN_COUNT];
static GD_HANDLE        gd_gpio_int_handle = 0;
static GD_GPIO_XREF_S   gd_gpio_xref_table[GD_GPIO_PIN_COUNT];//max maped function for each pin
static U16              gd_Gpio_xref_table_count = 0;

/*
***********************************************************
** local functions
***********************************************************
*/
static GD_GPIO_HANDLE_S* gpioCheckHandle(GD_HANDLE handle);
#if 1
GISR1                    gpioIsr0();
static GD_INT_DATA_S*    gpioIrqHandler(void);
#endif
static void gpioIntSetting(U8 number,GD_GPIO_INT_TRIGGER_E type);

/*!
*******************************************************************************
**
** \brief Initialise the driver.
**
** This function initialises the GPIO driver. It disables all GPIO
** interrupts and registers the GPIO interrupt with the interrupt
** driver.
**
** If the driver is already initialised,
** #GD_ERR_ALREADY_INITIALIZED will be returned.
**
** \param pInitParams Pointer to an init structure GD_GPIO_INIT_PARAMS_S.
**
** \return
** - #GD_OK if successfull
** - #GD_ERR_ALREADY_INITIALIZED in case of error, already initialized
** - #GD_ERR_BAD_PARAMTER in case of error if the given parameter structure
**                        is invalid
**
** \sa GD_GPIO_Terminate()
**
*******************************************************************************
*/
GERR GD_GPIO_Init(GD_GPIO_INIT_PARAMS_S* pInitParams)
{
    U8 index;
#if 1
    GD_INT_OPEN_PARAMS_S irq;
#endif
    GD_HANDLE handle;

    if(gd_gpio_int_handle != 0)
    {
        return( GD_ERR_ALREADY_INITIALIZED );
    }

    if (( pInitParams == NULL )||( pInitParams->xrefTable == NULL )
            ||(pInitParams->xrefTableCount>(GD_GPIO_PIN_COUNT))) {
        return(GD_ERR_BAD_PARAMETER);
    }

    gd_Gpio_xref_table_count = pInitParams->xrefTableCount;
    // set default value, and copy the gpio table.
    for (index = 0; index < GD_GPIO_PIN_COUNT; index++) {
        if (index < gd_Gpio_xref_table_count) {
            gd_gpio_xref_table[index].pin  = pInitParams->xrefTable[index].pin;
            gd_gpio_xref_table[index].type = pInitParams->xrefTable[index].type;
            if (gd_gpio_xref_table[index].type != GD_GPIO_TYPE_UNDEFINED) {
                // open the default function mode of gpio.
                GD_GPIO_Open(gd_gpio_xref_table[index].pin,
                             gd_gpio_xref_table[index].type,
                             0,
                             &handle);
            }
        } else {
            gd_gpio_xref_table[index].pin  = 0xff;// index; ???
            gd_gpio_xref_table[index].type = GD_GPIO_TYPE_UNDEFINED;
        }
    }

    // clean all status of gpio handle.
    for (index = 0; index < GD_GPIO_PIN_COUNT; index++) {
        gd_gpio_handle_array[index].in_use   = GFALSE;
        gd_gpio_handle_array[index].number   = 0;
        gd_gpio_handle_array[index].type     = GD_GPIO_TYPE_UNDEFINED;
        gd_gpio_handle_array[index].notifier = NULL;
    }

    // register interrupt routine
#if 1
    irq.type            = GD_INT_GPIO0_IRQ;
    irq.active          = GD_INT_INVERT_IRQ;
    irq.sensitivity     = GD_INT_LEVEL_HIGH;
    irq.priority        = GD_INT_LOW_PRIORITY;
    irq.isrFct.lowPrio  = gpioIsr0;

    if(pInitParams->irqPriority == GD_INT_MID_PRIORITY)
    {
        irq.priority        = GD_INT_MID_PRIORITY;
        irq.isrFct.midPrio  = gpioIsr0;
    }
#endif

    // this is used for gpio enable
    GH_GPIO_set_INT_EN(1);

	/*FIXME(heyong):gk7101  phy type*/
	if(pInitParams->phyType == 0)//internal phy 
	{ 
		GH_GPIO_set_PER_SEL((U32)0x00000002);
	}
	else //external phy 
	{ 
		GH_GPIO_set_PER_SEL((U32)0x00000003); 
	}
    

    // very special internal setting, hard wire CTS to 1
    // this is required to start the uart later
#if 1
    //GH_GPIO_set_InConfig_SIGNAL(((GD_GPIO_TYPE_INPUT_UART0_CTS>>8) & 0xff)-1, 1);

    if(GD_INT_Open(&irq, &gd_gpio_int_handle) != GD_OK)
    {
        gd_gpio_int_handle = 0;
        return(GD_ERR_ALREADY_INITIALIZED);
    }
    GD_INT_SetHandler(irq.type, gpioIrqHandler);
    GD_INT_Enable(&gd_gpio_int_handle, GD_INT_ENABLED);
#endif
    return(GD_OK);
}

/*!
*******************************************************************************
**
** \brief  Exits the driver.
**
** This function terminates the GPIO driver. It closes all open
** GPIO lines and closes the GPIO interrupt handler with the
** interrupt driver.
**
** If the driver was not initialised, #GD_OK will be returned anyway.
**
** \return
** - #GD_OK if successfull
**
*******************************************************************************
*/
GERR GD_GPIO_Exit(void)
{
    U8 index;
    GD_HANDLE handle;

    if(gd_gpio_int_handle == 0)
    {
        return(GD_OK);
    }

    for(index=0; index < GD_GPIO_PIN_COUNT; index++)
    {
        handle = (GD_HANDLE)(&gd_gpio_handle_array[index]);
        GD_GPIO_Close(&handle);

        gd_gpio_handle_array[index].in_use      = GFALSE;
        gd_gpio_handle_array[index].notifier    = NULL;
    }
    GH_GPIO_set_INT_EN_int_en(GD_GPIO_IRQ_CLEAR);
    GD_INT_Enable(&gd_gpio_int_handle, GD_INT_DISABLED);
    GD_INT_Close(&gd_gpio_int_handle);

    gd_gpio_int_handle          = 0;
    gd_Gpio_xref_table_count    = 0;
    return(GD_OK);
}

/*!
*******************************************************************************
**
** \brief Opens a GPIO.
**
** This function opens a GPIO and configures it.
**
** \param  number      Number of the GPIO to open.
** \param  type        Operation type of the GPIO.
** \param  pIntConfig  Pointer to an interrupt configuration structure.
**                     You may pass a NULL pointer here to disable interrupt
**                     generation for the given GPIO.
** \param  pHandle     Pointer to a handle that shall be filled as return
**                     value.
**
** \return
** - #GD_OK if successfull
** - #GD_ERR_ALREADY_OPEN in case of error if the given GPIO is already in use
** - #GD_ERR_BAD_PARAMTER in case of error if either the given type is out of
**                        range or if the given interrupt mode is not supported
**
*******************************************************************************
*/
GERR GD_GPIO_Open(U8 number, GD_GPIO_TYPE_E type, GD_GPIO_INT_CONFIG_S* pIntConfig, GD_HANDLE* pHandle)
{
    GD_GPIO_HANDLE_S* ph;
    GERR gerr;
    U32 temp_value = 0;
    if(number >= GD_GPIO_PIN_COUNT)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    ph = &gd_gpio_handle_array[number];
    if(ph->in_use == GTRUE)
    {
        *pHandle = (GD_HANDLE)ph;
        return(GD_ERR_ALREADY_OPEN);
    }

    ph->number = number;
    ph->type   = type;

    ph->in_use = GTRUE;
    gerr = GD_GPIO_SetType((GD_HANDLE)ph, type);
    if(gerr != GD_OK)
    {
        ph->in_use = GFALSE;
        return gerr;
    }
    ph->in_use = GFALSE;

    if((GD_GPIO_GET_FUNC(type) == GD_GPIO_FUNC_IN) && (pIntConfig != NULL))
    {
        if(pIntConfig->enable == GFALSE)
        {
            if(number < 32)
            {
                temp_value = GH_GPIO_get_IE_LOW();
                temp_value = temp_value & (~(0x1 << number));
                GH_GPIO_set_IE_LOW(temp_value);
            }
            else
            {
                temp_value = GH_GPIO_get_IE_HIGH();
                temp_value = temp_value & (~(0x1 << (number - 32)));
                GH_GPIO_set_IE_HIGH(temp_value);
            }
            ph->notifier = NULL;
        }
        else
        {
            ph->notifier = pIntConfig->notifyFct;
            gpioIntSetting(number, pIntConfig->trigger);
            if(number < 32)
            {
                temp_value = GH_GPIO_get_IE_LOW();
                temp_value = temp_value | (0x1 << number);
                GH_GPIO_set_IE_LOW(temp_value);
            }
            else
            {
                temp_value = GH_GPIO_get_IE_HIGH();
                temp_value = temp_value | (0x1 << (number - 32));
                GH_GPIO_set_IE_HIGH(temp_value);
            }
        }

    }
    else
    {
        ph->notifier = NULL;
    }

    ph->in_use = GTRUE;

    *pHandle = (GD_HANDLE)ph;
    return(GD_OK);
}

/*!
*******************************************************************************
**
** \brief  Opens a GPIO in function mode.
**
** This function opens a GPIO in function mode.
**
** \param  type     GPIO function type of the GPIO to open.
** \param  pHandle  Pointer to a handle that shall be filled as return value.
**
** \return
** - #GD_OK if successfull
** - #GD_ERR_ALREADY_OPEN in case of error if the given GPIO is already in use
** - #GD_ERR_BAD_PARAMTER in case of error if either the given type is out of
**                        range or if the given interrupt mode is not supported
**
*******************************************************************************
*/
GERR GD_GPIO_OpenFunctionMode(GD_GPIO_TYPE_E type, GD_HANDLE* pHandle)
{
    U32 index;

    for(index=0; index < gd_Gpio_xref_table_count; index++)
    {
        if(gd_gpio_xref_table[index].type == type)
        {
            return(GD_GPIO_Open( gd_gpio_xref_table[index].pin, type, 0, pHandle));
        }
    }
    return(GD_ERR_BAD_PARAMETER);
}

/*!
*******************************************************************************
**
** \brief Closes a GPIO.
**
** This function closes a GPIO and disables the related interrupt.
** It shall also be used to close the special SDRAM od TSD GPIO lines.
**
** \param pHandle Pointer to a handle of a GPIO that shall be closed. The
**                handle will be set to #NULL.
**
** \return
** - #GD_OK if successfull
** - #GD_ERR_INVALID_HANDLE in case of error if the given handle is invalid
**
*******************************************************************************
*/
GERR GD_GPIO_Close(GD_HANDLE* pHandle)
{
    GD_GPIO_HANDLE_S* ph;
    U32 temp_value = 0;
    if(pHandle == NULL)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    ph = gpioCheckHandle(*pHandle);
    if(ph && (ph->in_use == GTRUE))
    {

        if(ph->number < 32)
        {
            temp_value = GH_GPIO_get_IE_LOW();
            temp_value = temp_value & (~(0x1 << ph->number));
            GH_GPIO_set_IE_LOW(temp_value);
        }
        else
        {
            temp_value = GH_GPIO_get_IE_HIGH();
            temp_value = temp_value & (~(0x1 << (ph->number - 32)));
            GH_GPIO_set_IE_HIGH(temp_value);
        }
        ph->in_use      = GFALSE;
        ph->notifier    = NULL;
        *pHandle        = 0;
    }
    return(GD_OK);
}

/*!
*******************************************************************************
**
** \brief Closes a GPIO with type.
**
** This function closes a GPIO and disables the related interrupt.
** It shall also be used to close the special SDRAM od TSD GPIO lines.
**
** \param type Pointer to the type of a GPIO that shall be closed.
**
** \return
** - #GD_OK if successfull
** - #GD_ERR_INVALID_HANDLE in case of error if the given handle is invalid
**
*******************************************************************************
*/
GERR GD_GPIO_CloseWithType(U32 type)
{
    GD_GPIO_HANDLE_S* ph = NULL;
    U16 index;
    U32 number;

    for(index=0; index < gd_Gpio_xref_table_count; index++)
    {
        if(gd_gpio_xref_table[index].type == type)
        {
            number          = gd_gpio_xref_table[index].pin;
            ph              = &gd_gpio_handle_array[number];
            ph->in_use      = GFALSE;
            ph->notifier    = NULL;
            return(GD_OK);
        }
    }
    return(GD_ERR_BAD_PARAMETER);
}
/*!
*******************************************************************************
**
** \brief Changes the type of a GPIO.
**
** This function changes the type of an open GPIO. Note that it can
** not be used for GPIO lines operating in function mode.
**
** \param  handle Handle of the GPIO to change.
** \param  type   New type to configure.
**
** \return
** - #GD_OK if successfull
** - #GD_ERR_INVALID_HANDLE in case of error if the given handle is invalid
** - #GD_ERR_BAD_PARAMETER in case of error if the given type is out of range
**
*******************************************************************************
*/
GERR GD_GPIO_SetType(GD_HANDLE handle, GD_GPIO_TYPE_E type)
{
    GD_GPIO_HANDLE_S* ph;

    ph = gpioCheckHandle(handle);
    if(!ph || (ph->in_use != GTRUE))
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    switch(GD_GPIO_GET_FUNC(type))
    {
    case GD_GPIO_FUNC_OUT:     // out
        GH_GPIO_set_OUTPUT_CFG_out_sel(ph->number, GD_GPIO_GET_OUT_SEL(type));
        GH_GPIO_set_OUTPUT_CFG_oen_sel(ph->number, GD_GPIO_GET_OEN_SEL(type));
        break;
    case GD_GPIO_FUNC_IN:     // in
        if(GD_GPIO_GET_IN_SEL(type) >= 2)
        {
            GH_GPIO_set_OUTPUT_CFG_out_sel(ph->number, GD_GPIO_GET_OUT_SEL(type));
            GH_GPIO_set_OUTPUT_CFG_oen_sel(ph->number, GD_GPIO_GET_OEN_SEL(type));
            GH_GPIO_set_INPUT_CFG_in_sel(GD_GPIO_GET_IN_SEL(type) - 2, ph->number);
        }
        else
        {
            GH_GPIO_set_OUTPUT_CFG_out_sel(ph->number, GD_GPIO_GET_OUT_SEL(type));
            GH_GPIO_set_OUTPUT_CFG_oen_sel(ph->number, GD_GPIO_GET_OEN_SEL(type));
            //GH_GPIO_set_INPUT_CFG_in_sel(GD_GPIO_GET_IN_SEL(type) - 2, ph->number);
        }
        break;
    case GD_GPIO_FUNC_INOUT:     // in+out
        // don't change, otherwise if out_sel at first might output a 0, then change to 1
        GH_GPIO_set_INPUT_CFG_in_sel(GD_GPIO_GET_IN_SEL(type) - 2, ph->number);
        GH_GPIO_set_OUTPUT_CFG_oen_sel(ph->number, GD_GPIO_GET_OEN_SEL(type));
        GH_GPIO_set_OUTPUT_CFG_out_sel(ph->number, GD_GPIO_GET_OUT_SEL(type));
        break;
    default:
        return(GD_ERR_BAD_PARAMETER);
    }
    if(GD_GPIO_GET_OEN_INVERT(type))
    {
        GH_GPIO_set_OUTPUT_CFG_oen_invert(ph->number, GD_GPIO_GET_OEN_INVERT(type));
    }
    GH_GPIO_set_OUTPUT_CFG_out_invert(ph->number, GD_GPIO_GET_OUT_INVERT(type));
    // Pull up/down & 2mA......
    if(GD_GPIO_GET_IOCTRL(type))
    {
        switch(ph->number%4)
        {
        case 0:
            GH_PLL_set_IOCTRL_GPIO_io0(ph->number/4, GD_GPIO_GET_IOCTRL(type));
            break;
        case 1:
            GH_PLL_set_IOCTRL_GPIO_io1(ph->number/4, GD_GPIO_GET_IOCTRL(type));
            break;
        case 2:
            GH_PLL_set_IOCTRL_GPIO_io2(ph->number/4, GD_GPIO_GET_IOCTRL(type));
            break;
        case 3:
            GH_PLL_set_IOCTRL_GPIO_io3(ph->number/4, GD_GPIO_GET_IOCTRL(type));
            break;
        }
    }

    ph->type = type; // add by francis
    return(GD_OK);
}

/*!
*******************************************************************************
**
** \brief Read a GPIO bit.
**
** This function reads the GPIO data bit given by the number element inside
** the given handl.
**
** \param  handle Handle of the GPIO to read.
** \param  pBit   Pointer to a data field which shall be filled.
**
** \return
** - #GD_OK if successfull
** - #GD_ERR_INVALID_HANDLE in case of error if the given handle is invalid
** - #GD_ERR_BAD_PARAMTER in case of error if the given type is not an input
**
*******************************************************************************
*/
GERR GD_GPIO_Read(GD_HANDLE handle, U8 *pBit)
{
    GD_GPIO_HANDLE_S* ph = gpioCheckHandle(handle);
    U32 shift;
    U32 bits;

    if(!ph || (ph->in_use != GTRUE))
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(GD_GPIO_GET_FUNC(ph->type) == GD_GPIO_FUNC_IN)
    {
        if(ph->number <= 31)
        {
            shift = ph->number;
            bits  = GH_GPIO_get_DIN_LOW();
        }
        else
        {
            shift = ph->number - 32;
            bits  = GH_GPIO_get_DIN_HIGH();
        }
        *pBit = (U8)((bits >> shift) & 1);
        return(GD_OK);
    }
    return(GD_ERR_BAD_PARAMETER);
}

/*!
*******************************************************************************
**
** \brief Write a GPIO bit.
**
** This function writes the GPIO data bit given by the number element inside
** the given handl.
**
** \param  handle   Handle of the GPIO to write.
** \param  bit      Data bit to write.
**
** \return
** - #GD_OK if successfull
** - #GD_ERR_INVALID_HANDLE in case of error if the given handle is invalid
** - #GD_ERR_BAD_PARAMTER in case of error if the given type is not an output
**
*******************************************************************************
*/
GERR GD_GPIO_Write(GD_HANDLE handle, U8 bit)
{
    GD_GPIO_HANDLE_S* ph = gpioCheckHandle(handle);

    if(!ph || (ph->in_use != GTRUE))
    {
        return( GD_ERR_INVALID_HANDLE );
    }

    if(GD_GPIO_GET_FUNC(ph->type) == GD_GPIO_FUNC_OUT)
    {
        GH_GPIO_set_OUTPUT_CFG_out_sel(ph->number, bit&0x1);
        return(GD_OK);
    }
    return(GD_ERR_BAD_PARAMETER);
}

/*!
*******************************************************************************
**
** \brief Invert the GPIO output data.
**
** This function invert the GPIO data bit given by the number element inside
** the given handl.
**
** \param  handle   Handle of the GPIO to invert.
** \param  modeValue      Normal mode or invert mode.
**
** \return
** - #GD_OK if successfull
** - #GD_ERR_INVALID_HANDLE in case of error if the given handle is invalid
** - #GD_ERR_BAD_PARAMTER in case of error if the given type is not an output
**
*******************************************************************************
*/
GERR GD_GPIO_ControlInvertData(GD_HANDLE handle, U8 modeValue)
{
    GD_GPIO_HANDLE_S* ph = gpioCheckHandle(handle);

    if(!ph || (ph->in_use != GTRUE ))
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(GD_GPIO_GET_FUNC(ph->type) == GD_GPIO_FUNC_OUT)
    {
        GH_GPIO_set_OUTPUT_CFG_out_invert(ph->number, modeValue);
        return(GD_OK);
    }
    return(GD_ERR_BAD_PARAMETER);
}

/*!
*******************************************************************************
**
** \brief Invert the GPIO enable mode.
**
** This function invert the GPIO enable mode given by the number element inside
** the given handl.
**
** \param  handle   Handle of the GPIO to invert.
** \param  modeValue      Normal mode or invert mode.
**
** \return
** - #GD_OK if successfull
** - #GD_ERR_INVALID_HANDLE in case of error if the given handle is invalid
** - #GD_ERR_BAD_PARAMTER in case of error if the given type is not an output
**
*******************************************************************************
*/
GERR GD_GPIO_ControlInvertEnable(GD_HANDLE handle, U8 modeValue)
{
    GD_GPIO_HANDLE_S* ph = gpioCheckHandle(handle);

    if(!ph || (ph->in_use != GTRUE))
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(GD_GPIO_GET_FUNC(ph->type) == GD_GPIO_FUNC_OUT)
    {
        GH_GPIO_set_OUTPUT_CFG_oen_invert(ph->number, modeValue);
        return(GD_OK);
    }
    return(GD_ERR_BAD_PARAMETER);
}

/*!
*******************************************************************************
**
** \brief Enables an interrupt.
**
** This function enables a GPIO interrupt.
**
** \return
** - #GD_OK if successfull
** - #GD_ERR_BAD_PARAMETER in case of error, gpio not initialize
**
*******************************************************************************
*/
GERR GD_GPIO_EnableInterrupt(void)
{
    if(gd_gpio_int_handle == 0)
    {
        return(GD_ERR_BAD_PARAMETER);
    }
    GH_GPIO_set_INT_EN_int_en(GD_GPIO_IRQ_ENABLE);
    return(GD_OK );
}

/*!
*******************************************************************************
**
** \brief Disables an interrupt.
**
** This function disables a GPIO interrupt.
**
** \param handle Handle of the GPIO to disable its interrupt.
**
** \return
** - #GD_OK if successfull
** - #GD_ERR_BAD_PARAMETER in case of error, gpio not initialize
**
*******************************************************************************
*/
GERR GD_GPIO_DisableInterrupt(void)
{
    if(gd_gpio_int_handle == 0)
    {
        return(GD_ERR_BAD_PARAMETER);
    }
    GH_GPIO_set_INT_EN_int_en(GD_GPIO_IRQ_CLEAR);
    return(GD_OK);
}

/*
*******************************************************************************
**
** \brief Check a given GPIO handle
**
** This function checks whether a given handle is valid.
**
** \param handle The GPIO handle to be checked
**
** \return
** - non-NULL if the given handle is ok
** - NULL in case of error if the given handle is invalid
**
*******************************************************************************
*/
static GD_GPIO_HANDLE_S* gpioCheckHandle(GD_HANDLE handle)
{
    GD_GPIO_HANDLE_S* check = (GD_GPIO_HANDLE_S*)handle;

    if(check && ( check == &gd_gpio_handle_array[check->number]))
    {
        return(check);
    }
    return(0);
}

/*
********************************************************************************
**
** GPIO interrupt handler function
**
********************************************************************************
*/

GISR1 gpioIsr0(void)
{
    GD_INT_HANDLER_F Handler;
    GD_INT_DATA_S* intDataP;

    Handler = GD_INT_GetHandler(GD_INT_GPIO0_IRQ);
    intDataP = Handler();
    if(intDataP->processor)
    {
        intDataP->processor(intDataP->data);
    }
}

static GD_INT_DATA_S* gpioIrqHandler(void)
{
    static GD_INT_DATA_S intData;
    U8 index = 0;

    U32 gpioStatusHigh = 0;
    U32 gpioStatusLow = 0;

    intData.length      = 0;
    intData.data        = NULL;
    intData.processor   = NULL;


    GD_GPIO_DisableInterrupt();

    gpioStatusHigh = GH_GPIO_get_MIS_HIGH();
    gpioStatusLow = GH_GPIO_get_MIS_LOW();

    for(index=0; index < GD_GPIO_PIN_COUNT; index++)
    {
        if(index < 32)
        {
            if((gpioStatusLow & (0x1 << index)) != 0)
            {
                if(gd_gpio_handle_array[index].notifier)
                {
                    gd_gpio_handle_array[index].notifier();
                }
            }
        }
        else
        {
            if((gpioStatusHigh & (0x1 << (index - 32))) != 0)
            {
                if(gd_gpio_handle_array[index].notifier)
                {
                    gd_gpio_handle_array[index].notifier();
                }
            }
        }
    }
    GH_GPIO_set_IC_HIGH(0xFFFFFFFF);
    GH_GPIO_set_IC_LOW(0xFFFFFFFF);
    GD_GPIO_EnableInterrupt();

    return( &intData );
}

static void gpioIntSetting(U8 number,GD_GPIO_INT_TRIGGER_E type)
{
    U32 temp_value = 0;

    switch(type)
    {
        case GD_GPIO_INT_TRIGGER_LOW_LEVEL:
            if(number < 32)
            {
                temp_value = GH_GPIO_get_IS_LOW();
                temp_value = temp_value | (0x1 << number);
                GH_GPIO_set_IS_LOW(temp_value);

                temp_value = GH_GPIO_get_IEV_LOW();
                temp_value = temp_value & (~(0x1 << number));
                GH_GPIO_set_IEV_LOW(temp_value);

                temp_value = GH_GPIO_get_IBE_LOW();
                temp_value = temp_value & (~(0x1 << number));
                GH_GPIO_set_IBE_LOW(temp_value);
            }
            else
            {
                temp_value = GH_GPIO_get_IS_HIGH();
                temp_value = temp_value | (0x1 << (number - 32));
                GH_GPIO_set_IS_HIGH(temp_value);

                temp_value = GH_GPIO_get_IEV_HIGH();
                temp_value = temp_value & (~(0x1 << (number - 32)));
                GH_GPIO_set_IEV_HIGH(temp_value);

                temp_value = GH_GPIO_get_IBE_HIGH();
                temp_value = temp_value & (~(0x1 << (number - 32)));
                GH_GPIO_set_IBE_HIGH(temp_value);

            }
            break;
        case GD_GPIO_INT_TRIGGER_HIGH_LEVEL:
            if(number < 32)
            {
                temp_value = GH_GPIO_get_IS_LOW();
                temp_value = temp_value | (0x1 << number);
                GH_GPIO_set_IS_LOW(temp_value);

                temp_value = GH_GPIO_get_IBE_HIGH();
                temp_value = temp_value & (~(0x1 << (number - 32)));
                GH_GPIO_set_IBE_LOW(temp_value);

                temp_value = GH_GPIO_get_IEV_LOW();
                temp_value = temp_value | (0x1 << number);
                GH_GPIO_set_IEV_LOW(temp_value);
            }
            else
            {
                temp_value = GH_GPIO_get_IS_HIGH();
                temp_value = temp_value | (0x1 << (number - 32));
                GH_GPIO_set_IS_HIGH(temp_value);

                temp_value = GH_GPIO_get_IBE_HIGH();
                temp_value = temp_value & (~(0x1 << (number - 32)));
                GH_GPIO_set_IBE_HIGH(temp_value);

                temp_value = GH_GPIO_get_IEV_HIGH();
                temp_value = temp_value | (0x1 << (number - 32));
                GH_GPIO_set_IEV_HIGH(temp_value);
            }
            break;
        case GD_GPIO_INT_TRIGGER_RISING_EDGE:
            if(number < 32)
            {
                temp_value = GH_GPIO_get_IS_LOW();
                temp_value = temp_value & (~(0x1 << number));
                GH_GPIO_set_IS_LOW(temp_value);

                temp_value = GH_GPIO_get_IBE_LOW();
                temp_value = temp_value & (~(0x1 << number));
                GH_GPIO_set_IBE_LOW(temp_value);

                temp_value = GH_GPIO_get_IEV_LOW();
                temp_value = temp_value | (0x1 << number);
                GH_GPIO_set_IEV_LOW(temp_value);
            }
            else
            {
                temp_value = GH_GPIO_get_IS_HIGH();
                temp_value = temp_value & (~(0x1 << (number - 32)));
                GH_GPIO_set_IS_HIGH(temp_value);

                temp_value = GH_GPIO_get_IBE_HIGH();
                temp_value = temp_value & (~(0x1 << (number - 32)));
                GH_GPIO_set_IBE_HIGH(temp_value);

                temp_value = GH_GPIO_get_IEV_HIGH();
                temp_value = temp_value | (0x1 << (number - 32));
                GH_GPIO_set_IEV_HIGH(temp_value);
            }
            break;
        case GD_GPIO_INT_TRIGGER_FALLING_EDGE:
            if(number < 32)
            {
                temp_value = GH_GPIO_get_IS_LOW();
                temp_value = temp_value & (~(0x1 << number));
                GH_GPIO_set_IS_LOW(temp_value);

                temp_value = GH_GPIO_get_IBE_LOW();
                temp_value = temp_value & (~(0x1 << number));
                GH_GPIO_set_IBE_LOW(temp_value);


                temp_value = GH_GPIO_get_IEV_LOW();
                temp_value = temp_value & (~(0x1 << number));
                GH_GPIO_set_IEV_LOW(temp_value);
            }
            else
            {
                temp_value = GH_GPIO_get_IS_HIGH();
                temp_value = temp_value & (~(0x1 << (number - 32)));
                GH_GPIO_set_IS_HIGH(temp_value);

                temp_value = GH_GPIO_get_IBE_HIGH();
                temp_value = temp_value & (~(0x1 << (number - 32)));
                GH_GPIO_set_IBE_HIGH(temp_value);

                temp_value = GH_GPIO_get_IEV_HIGH();
                temp_value = temp_value & (~(0x1 << (number - 32)));
                GH_GPIO_set_IEV_HIGH(temp_value);
            }
            break;
        case GD_GPIO_INT_TRIGGER_BOTH_EDGE:
            if(number < 32)
            {
                temp_value = GH_GPIO_get_IS_LOW();
                temp_value = temp_value & (~(0x1 << number));
                GH_GPIO_set_IS_LOW(temp_value);

                temp_value = GH_GPIO_get_IBE_LOW();
                temp_value = temp_value | (0x1 << number);
                GH_GPIO_set_IBE_LOW(temp_value);
            }
            else
            {
                temp_value = GH_GPIO_get_IS_HIGH();
                temp_value = temp_value & (~(0x1 << (number - 32)));
                GH_GPIO_set_IS_HIGH(temp_value);

                temp_value = GH_GPIO_get_IBE_HIGH();
                temp_value = temp_value | (0x1 << (number - 32));
                GH_GPIO_set_IBE_HIGH(temp_value);
            }
            break;
        default:
            break;
    }

    return;
}


