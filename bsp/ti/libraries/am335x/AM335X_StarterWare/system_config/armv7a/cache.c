/**
 *  \file   cache.c
 *
 *  \brief  APIs for configuring Cache
 *
 *  This file contains the APIs for configuring ARMv7a Cache
*/

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/
#include "cache.h"
#include "cp15.h"

/*****************************************************************************
**                      INTERNAL MACRO DEFINITIONS
******************************************************************************/
#define CORTEX_A8_L2EN                   (0x02)
#define PRIMARY_PART_CORTEX_A8           (0xC08) 

/*****************************************************************************
**                         FUNCTION DEFINITIONS
******************************************************************************/
/**
 * \brief   Disables Cache. The levels/type of Cache to be disabled
 *          is passed as parameter.
 *
 * \param   disFlag   Caches to be disabled.
 *            'disFlag' can take one of the below values. \n
 *                CACHE_ICACHE - To disable Instruction Cache \n
 *                CACHE_DCACHE - To disable Data/Unified Cache \n
 *                CACHE_ALL - To disable all levels of Cache
 *
 * \return  None.
 *
 * \Note    Disabling Data Cache disables Unified cache also, if present.
 **/
void CacheDisable(unsigned int disFlag)
{
    if(disFlag & CACHE_ICACHE)
    {
        /*
        **  Disable I-Cache. The I-Cache invalidation is also done inside
        **  CP15ICacheDisable().
        */
        CP15ICacheDisable();
    }

    /* Here D Cache Disabling disables Unified cache also */
    if(disFlag & CACHE_DCACHE)
    {
        /*
        **  Disable D-Cache. The D-Cache Clean and Invalidation is also done
        **  inside CP15DCacheDisable().
        */
        CP15DCacheDisable();

        /* For Cortex A8, L2EN has to be disabled for L2 Cache */
        if(PRIMARY_PART_CORTEX_A8 == CP15MainIdPrimPartNumGet())
        {
            CP15AuxControlFeatureDisable(CORTEX_A8_L2EN);
        }
    }
}

/**
 * \brief   Enables Cache. The levels/type of Cache to be enabled
 *          is passed as parameter.
 *
 * \param   enFlag   Caches to be enabled.
 *            'enFlag' can take one of the below values. \n
 *                CACHE_ICACHE - To enable Instruction Cache \n
 *                CACHE_DCACHE - To enable Data/Unified Cache \n
 *                CACHE_ALL - To enable all levels of Cache
 *
 * \return  None.
 *
 * \Note    Enabling Data Cache enables Unified cache also, if present.
 **/
void CacheEnable(unsigned int enFlag)
{
    if(enFlag & CACHE_ICACHE)
    { 
        CP15ICacheFlush();
        CP15ICacheEnable();
    }

    if(enFlag & CACHE_DCACHE)
    {   
        /* For Cortex A8, L2EN has to be enabled for L2 Cache */
        if(PRIMARY_PART_CORTEX_A8 == CP15MainIdPrimPartNumGet())
        {
            CP15AuxControlFeatureEnable(CORTEX_A8_L2EN);
        }

        CP15DCacheFlush();
        CP15DCacheEnable();
    }
}

/**
 * \brief   This API invalidates the entire I-Cache
 *
 * \param   None
 *
 * \return  None.
 *
 **/
void CacheInstInvalidateAll(void)
{
    CP15ICacheFlush();
}

/**
 * \brief   This API invalidates a section of I-Cache. 
 *
 * \param   startAddr    Starting address to be invalidated
 * \param   numBytes     The number of bytes to be invalidated
 *
 * \return  None.
 *
 **/
void CacheInstInvalidateBuff(unsigned int startAddr, unsigned int numBytes)
{
    CP15ICacheFlushBuff(startAddr, numBytes);
}

/**
 * \brief   This API Cleans and Invalidates the entire Data Cache.
 *
 * \param   None
 *
 * \return  None.
 *
 **/
void CacheDataCleanInvalidateAll(void)
{
    CP15DCacheCleanFlush();
}

/**
 * \brief   This API Cleans the entire Data Cache.
 *
 * \param   None
 *
 * \return  None.
 *
 **/
void CacheDataCleanAll(void)
{
    CP15DCacheClean();
}

/**
 * \brief   This API Invalidates the entire Data Cache.
 *
 * \param   None
 *
 * \return  None.
 *
 **/
void CacheDataInvalidateAll(void)
{
    CP15DCacheFlush();
}

/**
 * \brief   This API clean a section of D-Cache, upto PoC. This API
 *          can be used to make a buffer in D-Cache to be coherent
 *          with the memory. For example, If DMA engine has to access
 *          a memory area for transmitting, to make sure that the 
 *          D-Cache values for the corresponding buffer is written to 
 *          memory, this API can be used.
 *
 * \param   startAddr    Starting address of the buffer to be cleaned
 * \param   numBytes     The number of bytes to be cleaned.
 *
 * \return  None.
 *
 **/
void CacheDataCleanBuff(unsigned int startAddr, unsigned int numBytes)
{
    CP15DCacheCleanBuff(startAddr, numBytes);
}

/**
 * \brief   This API invalidates a section of D-Cache till PoC. With this
 *          API, we can make sure that the next read of the buffer happens
 *          from memory. This is required if any DMA engine has updated
 *          the memory area with any data, other than from the D-Cache.
 *
 * \param   startAddr    Starting address of the buffer to be invalidated
 * \param   numBytes     The number of bytes to be invalidated
 *
 * \return  None.
 *
 **/
void CacheDataInvalidateBuff(unsigned int startAddr, unsigned int numBytes)
{
    CP15DCacheFlushBuff(startAddr, numBytes);
}

/**
 * \brief   This API cleans and invalidates a section of D-Cache to PoC.
 *
 * \param   startAddr    Starting address of the buffer to be cleaned 
 *                       and invalidated
 * \param   numBytes     The number of bytes to be cleaned and invalidated
 *
 * \return  None.
 *
 **/
void CacheDataCleanInvalidateBuff(unsigned int startAddr, unsigned int numBytes)
{
    CP15DCacheCleanFlushBuff(startAddr, numBytes);
}

/***************************** End Of File ***********************************/

