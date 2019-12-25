/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
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
#ifndef APP_USBD_DUMMY_INTERNAL_H__
#define APP_USBD_DUMMY_INTERNAL_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup app_usbd_dummy_internals USB Dummy internals
 * @ingroup app_usbd_dummy
 *
 * @brief @tagAPI52840 Internals of the USB Dummy class.
 * @{
 */

/** @brief Forward declaration of Dummy Class type */
APP_USBD_CLASS_FORWARD(app_usbd_dummy);

/** @brief Dummy part of class instance data */
typedef struct {
    uint8_t none;
} app_usbd_dummy_inst_t;

/** @brief Dummy context */
typedef struct {
    uint8_t none;
} app_usbd_dummy_ctx_t;


/**
 * @brief Dummy configuration macro.
 *
 * Used by @ref APP_USBD_DUMMY_GLOBAL_DEF
 *
 * @param iface Interface number.
 * */
#define APP_USBD_DUMMY_CONFIG(iface) (iface)


/**
 * @brief Specific class constant data for Dummy.
 *
 * @ref app_usbd_dummy_inst_t
 */
#define APP_USBD_DUMMY_INSTANCE_SPECIFIC_DEC app_usbd_dummy_inst_t inst;

/**
 * @brief Specific class data for Dummy.
 *
 * @ref app_usbd_dummy_ctx_t
 * */
#define APP_USBD_DUMMY_DATA_SPECIFIC_DEC app_usbd_dummy_ctx_t ctx;


/** @brief Public Dummy class interface */
extern const app_usbd_class_methods_t app_usbd_dummy_class_methods;

/** @brief Global definition of Dummy instance */
#define APP_USBD_DUMMY_GLOBAL_DEF_INTERNAL(instance_name, interface_number)                        \
    APP_USBD_CLASS_INST_NO_EP_GLOBAL_DEF(                                                          \
        instance_name,                                                                             \
        app_usbd_dummy,                                                                            \
        &app_usbd_dummy_class_methods,                                                             \
        APP_USBD_DUMMY_CONFIG((interface_number)),                                                 \
        ()                                                                                         \
    )


/** @} */


#ifdef __cplusplus
}
#endif

#endif /* APP_USBD_DUMMY_INTERNAL_H__ */
