/*
*******************************************************************************
**
** \file      gd_int.c
**
** \brief     INT driver (core functions).
**
**            Copyright:   2012 - 2013 (C) GoKe Microelectronics ShangHai Branch
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \version
**
*******************************************************************************
*/
#include <stdio.h>
#include <string.h>

#include <gtypes.h>
#include "gh_vic.h"
#include "gd_int.h"
#include "gd_int_priv.h"


GD_ARM_INTR_IsrFuncT ARM_INTR_IsrFunctionTable[GD_VIC_INSTANCES * GD_INT_VEC_OFFSET] __attribute__ ((section(".nocache_buffer"))) = {NULL};
GD_ARM_INTR_IsrFuncT ARM_INTR_BsrFunctionTable[GD_VIC_INSTANCES * GD_INT_VEC_OFFSET] __attribute__ ((section(".nocache_buffer"))) = {NULL};
GBOOL               IrqsInUse[GD_VIC_INSTANCES * GD_INT_VEC_OFFSET] __attribute__ ((section(".nocache_buffer"))) = {0};

/*!
********************************************************************************
**
** \brief Initialize the INT driver
**
** This function initializes the interrupt driver, it sets all required
** interrupt registers to default value. In addition it sets the hook
** functions for the first three interrupts (reset, memerr, insterr) given
** in the parameter structure.
**
** \param  initParams  A pointer to the #GD_INT_INIT_PARAMS_S structure to get
**                     initializataion for the first three interrupt
**                     vectors from
**
** \return
** - #GD_ERR_ALREADY_INITIALIZED if the INT driver is already initialized
** - #GD_OK if successfull
**
********************************************************************************
*/
GERR GD_INT_Init(GD_INT_INIT_PARAMS_S *initParams)
{
    U32 i,j;
    GD_INT_DisableAllInterrupts();

    /* Set VIC sense and event type for each entry
     * note: we initialize udc vbus irq type here */
    GH_VIC_set_Sense(0, 0x00000000);
    GH_VIC_set_BothEdge(0, 0x00000000);
    GH_VIC_set_Event(0, 0x00000000);
#if (GD_VIC_INSTANCES >= 2)
    GH_VIC_set_Sense(1, 0x00000000);
    GH_VIC_set_BothEdge(1, 0x00000000);
    GH_VIC_set_Event(1, 0x00000000);
#endif

    /* Disable all IRQ */
    GH_VIC_set_Select(0, 0x00000000);
    GH_VIC_set_Enable(0, 0x00000000);
    GH_VIC_set_EnClr(0, 0xffffffff);
    GH_VIC_set_EdgeClr(0, 0xffffffff);
#if (GD_VIC_INSTANCES >= 2)
    GH_VIC_set_Select(1, 0x00000000);
    GH_VIC_set_Enable(1, 0x00000000);
    GH_VIC_set_EnClr(1, 0xffffffff);
    GH_VIC_set_EdgeClr(1, 0xffffffff);
#endif

    for(i = 0; i < GD_VIC_INSTANCES; i++)
    {
        for(j = 0; j < GD_INT_VEC_OFFSET; j++)
        {
            ARM_INTR_IsrFunctionTable[i * GD_INT_VEC_OFFSET + j] = NULL;
            ARM_INTR_BsrFunctionTable[i * GD_INT_VEC_OFFSET + j] = NULL;
        }
    }
    //GD_INT_EnableAllInterrupts();
    return( GD_OK );
}


/**
 * Configure an IRQ vector on the VIC.
 */
static void vic_set_type(GD_INT_OPEN_PARAMS_S *openParams)
{
    U32 mask = 0x0;
    U32 bit = 0x0;
    U8 vic = (U8)(openParams->type / GD_INT_VEC_OFFSET);
    U32 select = 0x0, sense = 0x0, bothedges = 0x0, event = 0x0;
    mask = ~(0x1 << (openParams->type % GD_INT_VEC_OFFSET));
    bit = (0x1 << (openParams->type % GD_INT_VEC_OFFSET));

    /* Line directly connected to VIC */
    select    = GH_VIC_get_Select(vic);
    sense     = GH_VIC_get_Sense(vic);
    bothedges = GH_VIC_get_BothEdge(vic);
    event     = GH_VIC_get_Event(vic);

    switch (openParams->sensitivity)
    {
    case GD_INT_RISING_EDGE:
        sense &= mask;      // edge triggered
        bothedges &= mask;  // single edge
        event |= bit;       // rising edge triggered
        break;
    case GD_INT_FALLING_EDGE:
        sense &= mask;      // edge triggered
        bothedges &= mask;  // single edge
        event &= mask;      // falling edge triggered
        break;
    case GD_INT_BOTH_EDGES:
        sense &= mask;      // edge triggered
        bothedges |= bit;   // both edges
        event &= mask;      // no effect
        break;
    case GD_INT_LEVEL_LOW:
        sense |= bit;       // level sensitive
        bothedges &= mask;  // no effect, single edge
        event &= mask;      // Low-level
        break;
    case GD_INT_LEVEL_HIGH:
        sense |= bit;       // level sensitive
        bothedges &= mask;  // no effect, single edge
        event |= bit;       // High-level
        break;
    }
    if(openParams->priority == GD_INT_LOW_PRIORITY)
    {
        select |= bit;      // FIQ
    }
    else
    {
        select &= mask;     // IRQ
    }
    // openParams->active // no used

    GH_VIC_set_Select(vic, select);
    GH_VIC_set_Sense(vic, sense);
    GH_VIC_set_BothEdge(vic, bothedges);
    GH_VIC_set_Event(vic, event);
}
/*!
********************************************************************************
**
** \brief Opens the INT driver
**
** This function opens a new instance of the interrupt driver
**
** \param  openParams a structure containing all parameters required to open
**                    a new instance of the INT driver
** \param  handle     a pointer to the GD_HANDLE variable where to store the
**                    result
**
** \return
** - #GD_ERR_BAD_PARAMETER in case of error one/more parameters are invalid
** - #GD_ERR_ALREADY_OPEN if the driver is already open
** - #GD_OK if successfull
**
********************************************************************************
*/
GERR GD_INT_Open(GD_INT_OPEN_PARAMS_S *openParams, GD_HANDLE *handle)
{
    *handle = 0;
    if(openParams->type > GD_INT_LAST_IRQ)
        return( GD_ERR_BAD_PARAMETER );
    /* check if IRQ already occupied if not add it to list of used IRQs */
    if(IrqsInUse[openParams->type] == GTRUE)
        return(GD_ERR_ALREADY_OPEN);
    IrqsInUse[openParams->type] = GTRUE;

    /* set value for IRQ_sens register */
    vic_set_type(openParams);

    GD_INT_SetVector(openParams->type, (void (*)())openParams->isrFct.lowPrio);

    /* return handle for requested IRQ vector */
    *handle = openParams->type;
    return( GD_OK );
}

/*!
********************************************************************************
**
** \brief Close the INT driver
**
** This function closes a previously opened INT driver instance.
**
** \param  handleP a pointer to the IDE handle to close
**
********************************************************************************
*/
void GD_INT_Close(GD_HANDLE *handleP)
{
    if(*handleP > GD_INT_LAST_IRQ)
        return;

    /* disable interupt in IRQ_mask register */
    if(IrqsInUse[*handleP] == GTRUE)
    {
        GD_INT_Enable(handleP, 0);
        //GH_GPREGS_set_ARMIRQEnable(IrqMaskRegister);
    }
    IrqsInUse[*handleP] = GFALSE;

    /* overwrite ISR in interrupt base vector table with jump to _exit_halt */
    /* (default defined in startup file). */
    GD_INT_SetVector(*handleP, _exit_halt);
    GD_INT_SetHandler(*handleP, NULL);
    *handleP = 0;
}

/*!
********************************************************************************
**
** \brief Sets an interrupt vector
**
** This function sets the given interrupt vector ISR to jump to, the previous
** stored ISR is replaced by the given one. This function is for low and mid
** priority interrupts or functions. The caller may need to cast the function
** type.
**
** \param vector The interrupt vector to access, this is mainly the index of
**               the interrupt function table 'IntBaseFuncTable'.
** \param target The interrupt service routing to store for the given interrupt
**               vector.
**
********************************************************************************
*/
void GD_INT_SetVector( S8 vector, void (*target)() )
{
    ARM_INTR_IsrFunctionTable[vector] = (GD_ARM_INTR_IsrFuncT)target;
}

GD_ARM_INTR_IsrFuncT GD_INT_GetVector( S8 vector)
{
    return ARM_INTR_IsrFunctionTable[vector];
}

/*!
********************************************************************************
**
** \brief Invalidate the instruction cache
**
** Function invalids the content of the instruction cache.
** See 'GD_INT_InvalidateInstructionCache' for further information.
**
********************************************************************************
*/

void GD_INT_DisableAllInterrupts(void)
{
    unsigned long old;
    unsigned long tmp;

#if defined(_ARM_RVDS)

    __asm{mrs    old, cpsr       };
    __asm{orr    tmp, old, #0xc0 };
    __asm{msr    cpsr_c, tmp     };

#elif defined(_ARM_GNU)

    __asm__ __volatile__ (
        "mrs %0, cpsr\n"
        "orr %1, %0, #0xc0\n"
        "msr cpsr_c, %1"
        : "=r" (old), "=r" (tmp)
        :
        : "memory");

#endif
}

void GD_INT_EnableAllInterrupts(void)
{
    unsigned long tmp;

#if defined(_ARM_RVDS)

    __asm{mrs tmp, cpsr};
    __asm{bic tmp, tmp, #0xc0};
    __asm{msr cpsr_c, tmp};

#elif defined(_ARM_GNU)

    __asm__ __volatile__ (
        "mrs %0, cpsr\n"
        "bic %0, %0, #0xc0\n"
        "msr cpsr_c, %0"
        : "=r" (tmp)
        :
        : "memory");

#endif
}


/*!
********************************************************************************
**
** \brief enable a interrupt
**
** \param handleP The interrupt handle.
** \param enable 0 disable 1 enable.
**
********************************************************************************
*/
void GD_INT_Enable(GD_HANDLE *handleP, U8 enable)
{

    U32 r;
    U32 line = *handleP;
    if(enable)
    {
        r = GH_VIC_get_Enable(line / GD_INT_VEC_OFFSET);
        r |= (0x1 << (line % GD_INT_VEC_OFFSET));
        GH_VIC_set_Enable(line / GD_INT_VEC_OFFSET, r);
    }
    else
    {
        r = (0x1 << (line % GD_INT_VEC_OFFSET));
        GH_VIC_set_EnClr(line / GD_INT_VEC_OFFSET, r);
    }
}

void GD_IRQ_ISR(void)
{
    U32 irqStat,i,j;

    for(i = 0; i < GD_VIC_INSTANCES; i++)
    {
        irqStat = GH_VIC_get_IRQSts(i);
        //GH_VIC_set_EdgeClr(i, irqStat);
        for(j = 0; j < GD_INT_VEC_OFFSET; j++)
        {
            if((irqStat & (1 << j)) && (ARM_INTR_IsrFunctionTable[i * GD_INT_VEC_OFFSET + j] != NULL))
            {
                GH_VIC_set_EdgeClr(i, 1 << j);
                ARM_INTR_IsrFunctionTable[i * GD_INT_VEC_OFFSET + j]();
            }
        }
    }
}

void GD_FIQ_ISR(void)
{
    U32 irqStat,i,j;

    for(i = 0; i < GD_VIC_INSTANCES; i++)
    {
        irqStat = GH_VIC_get_FIQSts(i);
        //GH_VIC_set_EdgeClr(i, irqStat);
        for(j = 0; j < GD_INT_VEC_OFFSET; j++)
        {
            if((irqStat & (1 << j)) && (ARM_INTR_IsrFunctionTable[i * GD_INT_VEC_OFFSET + j] != NULL))
            {
                GH_VIC_set_EdgeClr(i, 1 << j);
                ARM_INTR_IsrFunctionTable[i * GD_INT_VEC_OFFSET + j]();
            }
        }
    }
}
