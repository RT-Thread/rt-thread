/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
/** @file sdk_alloca.h
 *
 * @brief Defines alloca() function.
 *
 * @details This file defines alloca() function. This can be done directly or by including system
 * header files. Not all platforms support alloca(). In this case no error will be shown, but
 * SDK_ALLOCA_DEFINED will be set to 0.
 */

#ifndef SDK_ALLOCA_H__
#define SDK_ALLOCA_H__


#if defined(__SDK_DOXYGEN__)
    /** @brief Set to one it alloca() function is available on this platform and it is correctly defined
     *  by this header file.
     */
    #define SDK_ALLOCA_DEFINED 1
#elif defined(__GNUC__)
    #if defined(__SES_ARM)
        // SES does not have definition of alloca(), but it have working GCC's __builtin_alloca().
        #if !defined(alloca)
            #define alloca(size) __builtin_alloca((size))
        #endif
    #else
        // alloca() can be defined in <malloc.h> on some platforms, but if not then try standard <alloca.h> header file.
        #include <malloc.h>
        #if !defined(alloca)
            #include <alloca.h>
        #endif
    #endif
    #define SDK_ALLOCA_DEFINED 1
#elif defined(__IAR_SYSTEMS_ICC__)
    // IAR does not support alloca() function.
    #define SDK_ALLOCA_DEFINED 0
#else
    // All other supported compilers have alloca() definition in <alloca.h> header file.
    #include <alloca.h>
    #define SDK_ALLOCA_DEFINED 1
#endif


/*lint -"d__builtin_alloca=(void*)" */


#endif // NRF_ALLOCA_H__
