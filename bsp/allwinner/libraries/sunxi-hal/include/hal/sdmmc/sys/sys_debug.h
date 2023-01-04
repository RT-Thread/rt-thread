/*
 * Copyright (C) 2017 ALLWINNERTECH TECHNOLOGY CO., LTD. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the
 *       distribution.
 *    3. Neither the name of ALLWINNERTECH TECHNOLOGY CO., LTD. nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
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
 */

#ifndef __R_DEBUG_H__
#define __R_DEBUG_H__

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define R_DEBUG_ON


/*
 * @brief Debug level
 */
#define DBG_LEVEL_MASK (0x0F)


#define R_LEVEL_EMERG 0

#define R_LEVEL_ALERT 1

#define R_LEVEL_CRIT 2

#define R_LEVEL_ERROR 3

#define R_LEVEL_WARNING 4

#define R_LEVEL_NOTICE 5

#define R_LEVEL_INFO 6

#define R_LEVEL_DEBUG 7

#define R_LEVEL_ALL 0x0F


/*
 * No expanded condition
 */
#define NOEXPAND 1


/*
 * module ON/OFF
 */
#define DBG_ON (1 << 4)

#define DBG_OFF (0)


/*
 * Always show message
 */
#define MOD_DBG_ALW_ON (DBG_ON | R_LEVEL_ALL)


/************************************************************
 * R_DEBUG INTERFACE
 ************************************************************/
#ifdef R_DEBUG_ON

#define R_DEBUG_PRINT(msg, arg...) printf(msg, ##arg)

#define R_DEBUG_ABORT() \
    do { \
        printf("system aborted!"); \
        sys_abort(); \
    } while (0)


/*
 * @brief   The realization of showing debug messages.
 * @param   module: Contained a module On/Off and a module debug level.
 * @param   dlevel: Debug message showed level for seal like MDEBUG.
 * @param   expand: Expanded condition if level param and module ON/OFF are not
 *                  enough for developer.
 * @param   msg: The debug message.
 * @param   arg: Arguement shown in debug message which like printf arguement.
 * @retval  None
 */
#define _R_DEBUG(module, dlevel, expand, msg, arg...)   \
        do { \
            if ( \
                ((module) & DBG_ON) && \
                (((module) & DBG_LEVEL_MASK) >= dlevel) && \
                (expand)) { \
                R_DEBUG_PRINT(msg, ##arg); \
            } \
        } while(0)

/*
 * @brief   The realization of showing debug messages and it can't be turn off by
 *          module ON/OFF.
 * @param   module: Contained a module On/Off and a module debug level.
 * @param   dlevel: Debug message showed level for seal.
 * @param   expand: Expanded condition if level param is not enough for developer.
 * @param   msg: The debug message.
 * @param   arg: Arguement shown in debug message which like printf arguement.
 * @retval  None
 */
#define _R_INFO(module, dlevel, expand, msg, arg...)    \
        do { \
            if ( \
                (((int16_t)(module) & DBG_LEVEL_MASK) >= dlevel) && \
                (expand)) { \
                R_DEBUG_PRINT(msg, ##arg); \
            } \
        } while(0)

/*
 * @brief   The realization of assert debug messages shown the assert position,
 *          for example: "[Assert] At module_debug.h line 112 fun _MASSERT: **"
 * @param   module: Contained a module On/Off and a module debug level.
 * @param   dlevel: Debug message showed level for seal.
 * @param   msg: The debug message.
 * @param   arg: Arguement shown in debug message which like printf arguement.
 * @retval  None
 */
#define _R_ASSERT(assert, module, dlevel, msg, arg...)  \
        _R_DEBUG(module, dlevel, !(assert), \
                "[Assert] At %s line %d fun %s: " msg, \
                __FILE__, __LINE__, __func__, ##arg)

/*
 * @brief   The realization of assert debug messages shown the assert position,
 *          and abort. for example: "[Assert] At module_debug.h line 112 fun
 *          _MASSERT: ***"
 * @param   module: Contained a module On/Off and a module debug level.
 * @param   dlevel: Debug message showed level for seal.
 * @param   msg: The debug message.
 * @param   arg: Arguement shown in debug message which like printf arguement.
 * @retval  None
 */
#define _R_ASSERT_ABORT(assert, module, dlevel, msg, arg...)    \
        do { \
            if ((((int16_t)(module) & DBG_LEVEL_MASK) >= dlevel) && !(assert)) { \
                R_DEBUG_PRINT("[Assert] At %s line %d fun %s: " msg, \
                             __FILE__, __LINE__, __func__, ##arg); \
                R_DEBUG_ABORT(); \
            } \
        } while(0)


/*
 * @brief   A level debug message
 * @param   module: Contained a module On/Off and a module debug level.
 * @param   expand: Expanded condition if level param and module ON/OFF are not
 *                  enough for developer.
 * @param   msg: The debug message.
 * @param   arg: Arguement shown in debug message which like printf arguement.
 * @retval  None
 */
#define R_ERROR(module, expand, msg, arg...) \
        _R_DEBUG(module, R_LEVEL_ERROR, expand, msg, ##arg)

#define R_ALERT(module, expand, msg, arg...) \
        _R_DEBUG(module, R_LEVEL_ALERT, expand, msg, ##arg)

#define R_CRIT(module, expand, msg, arg...) \
        _R_DEBUG(module, R_LEVEL_CRIT, expand, msg, ##arg)

#define R_EMERG(module, expand, msg, arg...) \
        _R_DEBUG(module, R_LEVEL_EMERG, R_xpand, msg, ##arg)

#define R_WARN(module, expand, msg, arg...) \
        _R_DEBUG(module, R_LEVEL_WARNING, expand, msg, ##arg)

#define R_NOTICE(module, expand, msg, arg...) \
        _R_DEBUG(module, R_LEVEL_NOTICE, expand, msg, ##arg)

#define R_INFO(module, expand, msg, arg...) \
        _R_DEBUG(module, R_LEVEL_INFO, expand, msg, ##arg)

#define R_DEBUG(module, expand, msg, arg...) \
        _R_DEBUG(module, R_LEVEL_DEBUG, expand, msg, ##arg)


/*
 * @brief   Assert a full debug message with position(file, line, etc.) without level.
 *          for example: "[Assert] At module_debug.h line 112 fun _MASSERT: ***"
 * @param   assert: Debug condition
 * @param   module: Contained a module On/Off at least.
 * @param   msg: The debug message.
 * @param   arg: Arguement shown in debug message which like printf arguement.
 * @retval  None
 */
#define R_ASSERT(assert, module, msg, arg...) \
        _R_ASSERT(assert, module, R_LEVEL_ALL, msg, ##arg)

#define R_ASSERT_ABORT(assert, module, msg, arg...) \
        _R_ASSERT_ABORT(assert, module, R_LEVEL_ALL, msg, ##arg)

/*
 * @brief   Assert a full debug message with position(file, line, etc.) and
 *          error number without level. for example:
 *          "[Assert] At module_debug.h line 112 fun _MASSERT: condition p != NULL is fault. errno is 115."
 * @param   condition: It will assert a message if condition is fault.
 * @retval  Nuon
 */
#ifndef assert
#define assert(condition) R_ASSERT(condition, MOD_DBG_ALW_ON, "condition %s is fault. errno is %d.\n", #condition, r_thread_errno)
#endif

/*
// THIS REALIZATION DO NOT SEAL
#define R_ASSERT(assert, module, msg, arg...) \
        _R_ASSERT(assert, module, R_LEVEL_ALL, "[%s]" msg, #module, ##arg)

#define R_ASSERT_ABORT(assert, module, msg, arg...) \
        _R_ASSERT_ABORT(assert, module, R_LEVEL_ALL, "[%s]" msg, #module, ##arg)
*/


/*
 * @brief   notify the function entry and exit/return in the debug level
 * @param   module: Contained a module On/Off at least.
 * @param   mname: module name in string
 * @param   ret: return value
 * @retval  None
 */
#define R_ENTRY(module, mname) \
        R_DEBUG(module, NOEXPAND, mname "entry %s().\n", __func__)

#define R_RET(module, mname, ret) \
        R_DEBUG(module, NOEXPAND, mname "exit %s() with return %d.\n", __func__, ret)

#define R_RET_NOVAL(module, mname) \
        R_DEBUG(module, NOEXPAND, mname "exit %s().\n", __func__)


#else /* MDEBUG_ON */

#define R_DEBUG_PRINT(msg, arg...)

#define R_DEBUG_ABORT()


#define _R_DEBUG(module, dlevel, expand, msg, arg...)

#define _R_INFO(module, dlevel, expand, msg, arg...)

#define _R_ASSERT(assert, module, dlevel, msg, arg...)

#define _R_ASSERT_ABORT(assert, module, dlevel, msg, arg...)


#define R_ERROR(module, expand, msg, arg...)

#define R_ALERT(module, expand, msg, arg...)

#define R_CRIT(module, expand, msg, arg...)

#define R_EMERG(module, expand, msg, arg...)

#define R_WARN(module, expand, msg, arg...)

#define R_NOTICE(module, expand, msg, arg...)

#define R_INFO(module, expand, msg, arg...)

#define R_DEBUG(module, expand, msg, arg...)


#define R_ASSERT(assert, module, msg, arg...)

#define R_ASSERT_ABORT(assert, module, msg, arg...)

#ifndef assert
#define assert(condition)
#endif


#define R_ENTRY(module, mname)

#define R_RET(module, mname, ret)

#define R_RET_NOVAL(module, mname)

#endif /* R_DEBUG_ON */

#define ROM_DUMP_MASK   (1 << 0)
#define ROM_DBG_MASK    (1 << 1)
#define ROM_INF_MASK    (1 << 2)
#define ROM_WRN_MASK    (1 << 3)
#define ROM_ERR_MASK    (1 << 4)
#define ROM_ANY_MASK    (1 << 5)
#define ROM_ABORT_MASK  (1 << 6)
#define ROM_TOTAL_MASKS (ROM_DUMP_MASK | ROM_DBG_MASK | ROM_INF_MASK | \
                         ROM_WRN_MASK | ROM_ERR_MASK | ROM_ANY_MASK | \
                         ROM_ABORT_MASK)

enum {
    DUMP_PREFIX_NONE,
    DUMP_PREFIX_ADDRESS,
    DUMP_PREFIX_OFFSET
};

extern int hex_to_bin(char ch);

extern int hex2bin(unsigned char *dst, const char *src, size_t count);

extern void hex_dump_to_buffer(const void *buf, size_t len, int rowsize,
                               int groupsize, char *linebuf, size_t linebuflen,
                               bool ascii);

extern void hex_dump_to_buffer(const void *buf, size_t len, int rowsize,
                               int groupsize, char *linebuf, size_t linebuflen,
                               bool ascii);

extern void print_hex_dump(const char *prefix_str, int prefix_type,
                           int rowsize, int groupsize,
                           const void *buf, size_t len, bool ascii);


extern void print_hex_dump_words(const void *addr, unsigned int len);

/*
//$ Example of r_debug from mqtt $

#define MQTT_MODULE (DBG_ON | R_LEVEL_DEBUG)

#ifdef MOTT_ASSERT_ON
#define MQTT_ASSERT(assert, msg, arg...) R_ALERT(MOD_DBG_ALW_ON, (assert), "[MQTT assert] "msg, ##arg)
#else
#define MQTT_ASSERT(assert, msg, arg...)
#endif

#ifdef MQTT_DBG_ON

#define MQTT_INFO(msg, arg...) R_INFO(MQTT_MODULE, NOEXPAND, "[MQTT info] " msg, ##arg)

#define MQTT_WARN(msg, arg...) R_WARN(MQTT_MODULE, NOEXPAND, "[MQTT warning] " msg, ##arg)

#define MQTT_DEBUG(msg, arg...) R_DEBUG(MQTT_MODULE, NOEXPAND, "[MQTT debug] " msg, ##arg)



#define MQTT_ENTRY() R_ENTRY(MQTT_MODULE, "[MQTT entry] ")

#define MQTT_EXIT(ret) R_RET(MQTT_MODULE, "[MQTT return] ", ret)

#else

#define MQTT_INFO(msg, arg...)

#define MQTT_WARN(msg, arg...)

#define MQTT_DEBUG(msg, arg...)


#define MQTT_ENTRY()

#define MQTT_EXIT(ret)

#endif

*/

extern void print_hex_dump_bytes(const void *addr, unsigned int len);
extern void print_hex_dump_words(const void *addr, unsigned int len);

#endif /* __R_DEBUG_H__ */
