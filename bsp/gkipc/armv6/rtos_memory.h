/*!
*******************************************************************************
**
** \file        rtos_memory.h
**
** \version     1.0
**
** \date        March 20, 2003
**
** \author      Wolfgang Larisch
**
** \brief       A generic OS adaptation layer library
**
** This header file defines RTOS internal functions which are implemented
** either in the uC/OS or the Nucleus port (maybe others OSes will follow in
** the future).
**
** \attention   THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**              ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**              OMMISSIONS.
**
** (C) Copyright 2002 - 2007 by Goke Microelectronics China
**
*******************************************************************************
*/
#ifndef RTOS_MEMORY_H
#define RTOS_MEMORY_H
#include "gtypes.h"
#include "rtos_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
*******************************************************************************
**
** \brief Allocate a bunch of memory from the system heap
**
** This function allocates the given size of memory from the available
** OS controlled SDRAM heap space.
**
** \param  size   size of memory in bytes to allocate.
** \param  shared a boolean value which decides whether to allocate a
**                memory block as shared (GTRUE) or as private (GFALSE)
**                memory. Private memory can only be de-allocated by
**                the thread that has allocated the memory, shared
**                memory can be de-allocated by any thread.
**
** \return memory a pointer to the start address of the allocated memory
**                block, or \b NULL if the required size of memory was not
**                available.
**
** \sa     rtos_types
**
*******************************************************************************
*/
RTOS_Memory RTOS_SysMemoryAllocate( RTOS_Size size, RTOS_Flag shared );

/*!
*******************************************************************************
**
** \brief Release (de-allocate) a bunch of system heap memory
**
** This function de-allocates a previoulsy allocated bunch of memory.
**
** \param  memory a pointer to the start of the memory block  to release.
**
** \return status the result status, either \b RTOS_OK,
**                \b RTOS_MEMORY_FAILURE if the given memory pointer does not
**                point to dynamic allocated memory  or \b RTOS_THREAD_FAILURE
**                if the allocated memory space is owned by a different
**                thread.
**
** \sa     rtos_types
** \sa     rtos_status
**
*******************************************************************************
*/
RTOS_Status RTOS_SysMemoryRelease( RTOS_Memory memory );

/*
*******************************************************************************
**
** This function allocates the given size of memory from the available
** OS controlled user heap.
** For better performace, we control all the available OS handled RAM by
** segments of a min. size of RTOS_HeapMinAllocSize bytes.
**
*******************************************************************************
*/
RTOS_Memory RTOS_MemoryAllocate( RTOS_Size bytes, RTOS_Flag shared );

RTOS_Memory RTOS_Malloc( RTOS_Size bytes);

RTOS_Memory RTOS_Realloc( RTOS_Memory addr, RTOS_Size bytes );

/*
*******************************************************************************
**
** This function de-allocates a previoulsy allocated bunch of memory
** within the user heap.
**
*******************************************************************************
*/
RTOS_Status RTOS_MemoryRelease( RTOS_Memory memory );

/*
*******************************************************************************
**
** This function sets the given amount of bytes in the given source address
** the the specified byte value.
**
*******************************************************************************
*/
RTOS_Memory RTOS_MemorySet( RTOS_Memory mem, U8 value, RTOS_Size bytes );


#ifdef __cplusplus
}
#endif

/*
*******************************************************************************
**
** end
**
*******************************************************************************
*/
#endif /* RTOS_MEMORY_H */
