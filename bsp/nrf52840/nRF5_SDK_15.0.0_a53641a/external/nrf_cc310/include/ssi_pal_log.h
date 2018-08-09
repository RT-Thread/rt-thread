/**************************************************************************************
* Copyright (c) 2016-2017, ARM Limited or its affiliates. All rights reserved         *
*                                                                                     *
* This file and the related binary are licensed under the following license:          *
*                                                                                     *
* ARM Object Code and Header Files License, v1.0 Redistribution.                      *
*                                                                                     *
* Redistribution and use of object code, header files, and documentation, without     *
* modification, are permitted provided that the following conditions are met:         *
*                                                                                     *
* 1) Redistributions must reproduce the above copyright notice and the                *
*    following disclaimer in the documentation and/or other materials                 *
*    provided with the distribution.                                                  *
*                                                                                     *
* 2) Unless to the extent explicitly permitted by law, no reverse                     *
*    engineering, decompilation, or disassembly of is permitted.                      *
*                                                                                     *
* 3) Redistribution and use is permitted solely for the purpose of                    *
*    developing or executing applications that are targeted for use                   *
*    on an ARM-based product.                                                         *
*                                                                                     *
* DISCLAIMER. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND                  *
* CONTRIBUTORS "AS IS." ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT             *
* NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT,        *
* AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE          *
* COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   *
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED            *
* TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR              *
* PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF              *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING                *
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS                  *
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                        *
**************************************************************************************/


#ifndef _SSI_PAL_LOG_H_
#define _SSI_PAL_LOG_H_

#include "ssi_pal_types.h"


/*!
@file
@brief This file contains the PAL layer log definitions, by default the log is disabled.
@defgroup ssi_pal_log CryptoCell PAL logging APIs and definitions
@{
@ingroup ssi_pal

*/

/* PAL log levels (to be used in SASI_PAL_logLevel) */
/*! PAL log level - disabled. */
#define SASI_PAL_LOG_LEVEL_NULL      -1 /*!< \internal Disable logging */
/*! PAL log level - error. */
#define SASI_PAL_LOG_LEVEL_ERR       0
/*! PAL log level - warning. */
#define SASI_PAL_LOG_LEVEL_WARN      1
/*! PAL log level - info. */
#define SASI_PAL_LOG_LEVEL_INFO      2
/*! PAL log level - debug. */
#define SASI_PAL_LOG_LEVEL_DEBUG     3
/*! PAL log level - trace. */
#define SASI_PAL_LOG_LEVEL_TRACE     4
/*! PAL log level - data. */
#define SASI_PAL_LOG_LEVEL_DATA      5

#ifndef SASI_PAL_LOG_CUR_COMPONENT
/* Setting default component mask in case caller did not define */
/* (a mask that is always on for every log mask value but full masking) */
/*! Default log debugged component.*/
#define SASI_PAL_LOG_CUR_COMPONENT 0xFFFFFFFF
#endif
#ifndef SASI_PAL_LOG_CUR_COMPONENT_NAME
/*! Default log component name.*/
#define SASI_PAL_LOG_CUR_COMPONENT_NAME "Dx"
#endif

/* Select compile time log level (default if not explicitly specified by caller) */
#ifndef SASI_PAL_MAX_LOG_LEVEL /* Can be overriden by external definition of this constant */
#ifdef DEBUG
/*! Default debug log level (when debug is set to on).*/
#define SASI_PAL_MAX_LOG_LEVEL  SASI_PAL_LOG_LEVEL_ERR /*SASI_PAL_LOG_LEVEL_DEBUG*/
#else /* Disable logging */
/*! Default debug log level (when debug is set to off).*/
#define SASI_PAL_MAX_LOG_LEVEL SASI_PAL_LOG_LEVEL_NULL
#endif
#endif /*SASI_PAL_MAX_LOG_LEVEL*/
/*! Evaluate SASI_PAL_MAX_LOG_LEVEL in case provided by caller */
#define __SASI_PAL_LOG_LEVEL_EVAL(level) level
/*! Maximal log level defintion.*/
#define _SASI_PAL_MAX_LOG_LEVEL __SASI_PAL_LOG_LEVEL_EVAL(SASI_PAL_MAX_LOG_LEVEL)

#ifdef ARM_DSM //not support ARM DSM log feature
/*! Log init function. */
#define SaSi_PalLogInit() do {} while (0)
/*! Log set level function - sets the level of logging in case of debug. */
#define SaSi_PalLogLevelSet(setLevel) do {} while (0)
/*! Log set mask function - sets the component masking in case of debug. */
#define SaSi_PalLogMaskSet(setMask) do {} while (0)
/*! Log log funtion based on various platform */
#define SaSi_PalLogPlatsampan(level, msg)  do {} while (0)

#else
#if _SASI_PAL_MAX_LOG_LEVEL > SASI_PAL_LOG_LEVEL_NULL
/*! Log init function. */
void SaSi_PalLogInit(void);
/*! Log set level function - sets the level of logging in case of debug. */
void SaSi_PalLogLevelSet(int setLevel);
/*! Log set mask function - sets the component masking in case of debug. */
void SaSi_PalLogMaskSet(uint32_t setMask);
/*! Log log funtion based on various platform */
void SaSi_PalLogPlat(uint32_t level, const char *msg);

/*! Global variable for log level */
extern int SaSi_PAL_logLevel;
/*! Global variable for log mask */
extern uint32_t SaSi_PAL_logMask;
#else /* No log */
/*! Log init function. */
#define SaSi_PalLogInit() do {} while (0)
/*! Log set level function - sets the level of logging in case of debug. */
#define SaSi_PalLogLevelSet(setLevel) do {} while (0)
/*! Log set mask function - sets the component masking in case of debug. */
#define SaSi_PalLogMaskSet(setMask) do {} while (0)
/*! Log log funtion based on various platform */
#define SaSi_PalLogPlat(level, msg)  do {} while (0)

#endif
#endif

/*! Filter logging based on logMask and dispatch to platform specific logging mechanism */
#define _SASI_PAL_LOG(level, msg)  \
    if (SaSi_PAL_logMask & SASI_PAL_LOG_CUR_COMPONENT) \
        SaSi_PalLogPlat(SASI_PAL_LOG_LEVEL_ ## level, msg )

#if (_SASI_PAL_MAX_LOG_LEVEL >= SASI_PAL_LOG_LEVEL_ERR)

/*! Log messages according to log level.*/
#define SASI_PAL_LOG_ERR(msg) \
    _SASI_PAL_LOG(ERR, msg)
#else
/*! Log messages according to log level.*/
#define SASI_PAL_LOG_ERR( ... ) do {} while (0)
#endif

#if (_SASI_PAL_MAX_LOG_LEVEL >= SASI_PAL_LOG_LEVEL_WARN)
/*! Log messages according to log level.*/
#define SASI_PAL_LOG_WARN(msg) \
    if (SaSi_PAL_logLevel >= SASI_PAL_LOG_LEVEL_WARN) \
        _SASI_PAL_LOG(WARN, msg)
#else
/*! Log messages according to log level.*/
#define SASI_PAL_LOG_WARN( ... ) do {} while (0)
#endif

#if (_SASI_PAL_MAX_LOG_LEVEL >= SASI_PAL_LOG_LEVEL_INFO)
/*! Log messages according to log level.*/
#define SASI_PAL_LOG_INFO(msg) \
    if (SaSi_PAL_logLevel >= SASI_PAL_LOG_LEVEL_INFO) \
        _SASI_PAL_LOG(INFO, msg)
#else
/*! Log messages according to log level.*/
#define SASI_PAL_LOG_INFO( ... ) do {} while (0)
#endif

#if (_SASI_PAL_MAX_LOG_LEVEL >= SASI_PAL_LOG_LEVEL_DEBUG)
/*! Log messages according to log level.*/
#define SASI_PAL_LOG_DEBUG(msg) \
    if (SaSi_PAL_logLevel >= SASI_PAL_LOG_LEVEL_DEBUG) \
        _SASI_PAL_LOG(DEBUG, msg)

/*! Log message buffer.*/
#define SASI_PAL_LOG_DUMP_BUF(msg, buf, size)       \
    do {                        \
    int i;                      \
    uint8_t *pData = (uint8_t*)buf;         \
                            \
    PRINTF("%s (%d):\n", msg, size);        \
    for (i = 0; i < size; i++) {            \
        PRINTF("0x%02X ", pData[i]);        \
        if ((i & 0xF) == 0xF) {         \
            PRINTF("\n");           \
        }                   \
    }                       \
    PRINTF("\n");                   \
    } while (0)
#else
/*! Log debug messages.*/
#define SASI_PAL_LOG_DEBUG( ... ) do {} while (0)
/*! Log debug buffer.*/
#define SASI_PAL_LOG_DUMP_BUF(msg, buf, size)   do {} while (0)
#endif

#if (_SASI_PAL_MAX_LOG_LEVEL >= SASI_PAL_LOG_LEVEL_TRACE)
/*! Log debug trace.*/
#define SASI_PAL_LOG_TRACE(msg) \
    if (SaSi_PAL_logLevel >= SASI_PAL_LOG_LEVEL_TRACE) \
        _SASI_PAL_LOG(TRACE, format, msg)
#else
/*! Log debug trace.*/
#define SASI_PAL_LOG_TRACE(...) do {} while (0)
#endif

#if (_SASI_PAL_MAX_LOG_LEVEL >= SASI_PAL_LOG_LEVEL_TRACE)
/*! Log debug data.*/
#define SASI_PAL_LOG_DATA(msg) \
    if (SaSi_PAL_logLevel >= SASI_PAL_LOG_LEVEL_TRACE) \
        _SASI_PAL_LOG(DATA, format, msg)
#else
/*! Log debug data.*/
#define SASI_PAL_LOG_DATA( ...) do {} while (0)
#endif
/**
@}
 */
#endif /*_SSI_PAL_LOG_H_*/
