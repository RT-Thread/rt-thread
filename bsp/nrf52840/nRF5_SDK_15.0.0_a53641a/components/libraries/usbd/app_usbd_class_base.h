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

#ifndef APP_USBD_CLASS_BASE_H__
#define APP_USBD_CLASS_BASE_H__

#include <stdint.h>
#include <stddef.h>

#include "app_usbd_types.h"
#include "nrf_drv_usbd.h"
#include "nrf_assert.h"
#include "app_util.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup app_usbd_class_base USBD Class Base module
 * @ingroup app_usbd
 *
 * @brief @tagAPI52840 The base for any class instance is defined in this module.
 *
 * @details Any class instance must start from base class instance structure.
 * This makes them compatible with USBD library independently of the
 * implementation details.
 * @{
 */

/**
 * @brief Endpoint configuration
 */
typedef struct
{
    nrf_drv_usbd_ep_t address; //!< Endpoint address
} app_usbd_class_ep_conf_t;

/**
 * @brief Interface configuration
 */
typedef struct
{
    uint8_t number;    //!< Interface number
    uint8_t ep_cnt;    //!< Endpoint number
    uint8_t ep_offset; //!< Offset of the first endpoint
                       /**< Offset in bytes of the first endpoint.
                        *   The offset is calculated from the address of this interface structure
                        */
} app_usbd_class_iface_conf_t;

/**
 * @brief Instance variable data
 */
typedef struct
{
    app_usbd_class_inst_t const * p_next;       //!< Pointer to the next instance
    app_usbd_class_inst_t const * p_sof_next;   //!< Pointer to the next SOF event requiring instance
} app_usbd_class_data_t;

/**
 * @brief Class descriptor context
 */
typedef struct
{
    uint32_t   line;        //!< Number of line to resume writing descriptors from
    uint8_t    data_buffer; //!< Data from last call of feeder
} app_usbd_class_descriptor_ctx_t;

/**
 * @brief Class descriptor state
 */
typedef struct
{
    uint8_t  *                          p_buffer;     //!< Pointer to buffer
    uint32_t                            current_size; //!< Current size of descriptor
    uint32_t                            maximum_size; //!< Maximum size of descriptor
    app_usbd_class_descriptor_ctx_t *   p_context;    //!< Pointer to context
} app_usbd_class_descriptor_state_t;

/**
 * @brief   Class interface function set
 * */
typedef struct {
    /**
     * @brief Instance callback function
     *
     * The function used by every class instance.
     * @param[in,out] p_inst  Instance of the class
     * @param[in]     p_event Event to process
     *
     * @return Standard error code
     *
     * @note If given event is not supported by class, return @ref NRF_ERROR_NOT_SUPPORTED
     */
    ret_code_t (* event_handler)(app_usbd_class_inst_t const * const p_inst,
                                 app_usbd_complex_evt_t const * const p_event);

    /**
     * @brief Instance feed descriptors
     *
     * Feeds whole descriptor of the instance
     * @param[in]     p_ctx     Class descriptor context
     * @param[in,out] p_inst    Instance of the class
     * @param[out]    p_buff    Buffer for descriptor
     * @param[in]     max_size  Requested size of the descriptor
     *
     * @return True if not finished feeding the descriptor, false if done
     */
    bool (* feed_descriptors)(app_usbd_class_descriptor_ctx_t  * p_ctx,
                              app_usbd_class_inst_t const      * p_inst,
                              uint8_t                          * p_buff,
                              size_t                             max_size);


    /**
     * @brief Select interface
     *
     * Function called when class interface has to be selected.
     *
     * This function would be called for every interface when:
     * - SET_INTERFACE command is processed by the default handler
     * - SET_CONFIG(1) command is processed by the default handler
     *
     * @note Remember to disable all the endpoints that are not used
     *       in the selected configuration.
     * @note If this function pointer is NULL default procedure would
     *       just enable all the interface endpoints and selecting
     *       alternate configurations other than 0 would generate error.
     * @note Calling the function with alternate setting 0 has to always succeed.
     *
     * @param[in,out] p_inst    Instance of the class
     * @param[in]     iface_idx Index of the interface inside class structure
     * @param[in]     alternate Alternate setting that should be selected
     *
     * @return Function has to return @ref NRF_SUCCESS when it has successfully proceed
     *         interface selection.
     *         If it returns @ref NRF_ERROR_NOT_SUPPORTED, default function would be used
     *         to proceed the request - just like there would be NULL pointer in this field.
     *         Any other kind of error would make library to STALL the request.
     */
    ret_code_t (* iface_select)(app_usbd_class_inst_t const * const p_inst,
                                uint8_t iface_idx,
                                uint8_t alternate);

    /**
     * @brief Deselect interface
     *
     * Function called when the class interface has to be deselected.
     *
     * This function would be called for every interface when:
     * - Library start internal event is processed by the default handler
     * - RESET event is processed by the default handler
     * - SET_ADDRESS is processed by the default handler
     * - SET_CONFIG(0) is processed by the default handler
     *
     * @note Just after this function is called all the interface
     *       endpoints would be disabled.
     *       This function does not has to take care about it.
     * @note If this function pointer is NULL default procedure would
     *       just disable all the interface endpoints.
     *
     * @param[in,out] p_inst    Instance of the class
     * @param[in]     iface_idx Index of the interface inside class structure
     */
    void (* iface_deselect)(app_usbd_class_inst_t const * const p_inst, uint8_t iface_idx);

    /**
     * @brief Get current interface
     *
     * Function called when class interface has to return its alternate settings
     * in reaction on GET_INTERFACE command.
     * It should be defined in a pair with @ref app_usbd_class_methods_t::iface_select.
     *
     * @param[in]  p_inst     Instance of the class
     * @param[in]  iface_idx  Index of the interface inside class structure
     *
     * @return Current alternate setting of the selected interface.
     *
     * @note For the classes that support this function, when an interface that has not alternate
     *       configurations has been selected this function has to return 0 - default alternate setting.
     *
     * @note If this function pointer it NULL default procedure would return alternate interface
     *       value 0.
     */
    uint8_t (* iface_selection_get)(app_usbd_class_inst_t const * const p_inst, uint8_t iface_idx);

} app_usbd_class_methods_t;

/**
 * @brief The instance structure itself
 *
 * The structure of base class instance
 */
struct app_usbd_class_inst_s
{
    app_usbd_class_data_t          * p_data;          //!< Pointer to non-constant data
    app_usbd_class_methods_t const * p_class_methods; //!< Class interface methods
    struct
    {
        uint8_t cnt;      //!< Number of defined interfaces
        uint8_t config[]; //!< Interface configuration data followed by endpoint data
    } iface; //!< Interface structure
};


/**
 * @brief Get total number of interfaces
 *
 *
 */
static inline uint8_t app_usbd_class_iface_count_get(app_usbd_class_inst_t const * const p_inst)
{
    return p_inst->iface.cnt;
}

/**
 * @brief Interface accessing function
 *
 * Get interface pointer.
 * Interfaces creates continuous array in the memory so it is possible to get
 * interface with index 0 and the just iterate to the next one.
 *
 * @param p_inst    Pointer to the class instance
 * @param iface_idx Index of the instance to get.
 *                  This is not the interface identifier.
 *                  Technically it is the index of the interface in the class description array.
 * @return Pointer to the interface configuration parameters or NULL if given index is out of interface scope for given class.
 */
static inline app_usbd_class_iface_conf_t const * app_usbd_class_iface_get(
        app_usbd_class_inst_t const * const p_inst,
        uint8_t iface_idx)
{
    ASSERT(NULL != p_inst);
    if (iface_idx >= (app_usbd_class_iface_count_get(p_inst)))
    {
        return NULL;
    }

    app_usbd_class_iface_conf_t const * p_interface =
            (app_usbd_class_iface_conf_t const * )(p_inst->iface.config);
    return &(p_interface[iface_idx]);
}

/**
 * @brief Get interface number
 *
 * @param p_iface Pointer to interface structure
 *
 * @return Interface number from interface configuration structure
 */
static inline uint8_t app_usbd_class_iface_number_get(
        app_usbd_class_iface_conf_t const * const p_iface)
{
    return p_iface->number;
}

/**
 * @brief Get number of endpoints in interface
 *
 * @param p_iface Pointer to interface structure
 *
 * @return Number of endpoints used by given interface
 */
static inline uint8_t app_usbd_class_iface_ep_count_get(
        app_usbd_class_iface_conf_t const * const p_iface)
{
    return p_iface->ep_cnt;
}

/**
 * @brief Interface Endpoint accessing function
 *
 * @param p_iface Interface configuration pointer
 * @param ep_idx  Endpoint index
 *
 * @return Endpoint information structure pointer or NULL if given index is outside of endpoints for selected interface.
 *
 * @sa app_usbd_class_iface_get
 */
static inline app_usbd_class_ep_conf_t const * app_usbd_class_iface_ep_get(
        app_usbd_class_iface_conf_t const * const p_iface,
        uint8_t ep_idx)
{
    ASSERT(NULL != p_iface);
    if (ep_idx >= p_iface->ep_cnt)
    {
        return NULL;
    }

    app_usbd_class_ep_conf_t const * p_ep =
            (app_usbd_class_ep_conf_t const * )(((uint8_t const *)p_iface) + p_iface->ep_offset);
    return &(p_ep[ep_idx]);
}

/**
 * @brief Translate endpoint address to class index
 *
 * @param p_iface       Interface configuration pointer
 * @param ep_address    Endpoint address
 *
 * @return Endpoint index or number of endpoints if not found
 *
 */
static inline  uint8_t app_usbd_class_iface_ep_idx_get(
        app_usbd_class_iface_conf_t const * const p_iface,
        nrf_drv_usbd_ep_t ep_address)
{
    ASSERT(NULL != p_iface);
    app_usbd_class_ep_conf_t const * p_ep =
            (app_usbd_class_ep_conf_t const * )(((uint8_t const *)p_iface) + p_iface->ep_offset);

    uint8_t i;
    for (i = 0; i < p_iface->ep_cnt; ++i)
    {
        if (ep_address == p_ep[i].address)
        {
            break;
        }
    }

    return i;
}

/**
 * @brief Get the selected endpoint address
 *
 * @param p_ep Endpoint configuration structure
 *
 * @return Endpoint address
 */
static inline nrf_drv_usbd_ep_t app_usbd_class_ep_address_get(app_usbd_class_ep_conf_t const * p_ep)
{
    return (nrf_drv_usbd_ep_t)p_ep->address;
}

/**
 * @brief Get the pointer to the writable instance data
 *
 * @param p_inst Instance pointer
 * @return Pointer to writable instance data
 */
static inline app_usbd_class_data_t * app_usbd_class_data_access(
        app_usbd_class_inst_t const * const p_inst)
{
    return p_inst->p_data;
}

/**
 * @name Internal macros for argument mapping
 *
 * Functions to be used as a mapping macro for @ref MACRO_MAP, @ref MACRO_MAP_FOR or @ref MACRO_MAP_FOR_PARAM
 * @{
 */
    /**
     * @brief Count the number of endpoints in given configuration
     *
     * Config should be given as a interface configuration in a brackets:
     * @code
     * (interface_nr, ep1, ep2, ep3)
     * @endcode
     * Number of endpoints may vary from 0 to a few (technically up to 16, but it seems not to make sense to use more than 4).
     * Interface number is always present.
     *
     * @param iface_config Single interface configuration (in brackets)
     *
     * @return Number of endpoints in interface. This is computed value - can be used by compiler but not by preprocessor.
     */
    #define APP_USBD_CLASS_CONF_IFACE_EP_COUNT_(iface_config)   \
                        (NUM_VA_ARGS(BRACKET_EXTRACT(iface_config)) - 1)

    /**
     * @brief Adds the number of endpoints in given config to the current value
     *
     * This is basically @ref APP_USBD_CLASS_CONF_IFACE_EP_COUNT_ with plus sign added.
     *
     * @param iface_config See parameters documentation in @ref APP_USBD_CLASS_CONF_IFACE_EP_COUNT_
     *
     * @return Plus sign followed by number of endpoints in interface.
     *
     * @sa APP_USBD_CLASS_CONF_IFACE_EP_COUNT_
     */
    #define APP_USBD_CLASS_CONF_IFACE_EP_PLUS_COUNT_(iface_config)  \
                        + APP_USBD_CLASS_CONF_IFACE_EP_COUNT_(iface_config)

    /**
     * @brief Create variable for endpoint
     */

    /**
     * @brief Extract endpoints given interface configuration
     *
     * This macro gets single endpoint configuration and extracts all the endpoints.
     * It also adds comma on the end of extracted endpoints.
     * This way when this macro is called few times it generates nice list of all endpoints
     * that may be used to array initialization.
     *
     * @param iface_config Single interface configuration in brackets.
     *                     The format should be similar like described in @ref APP_USBD_CLASS_CONF_IFACE_EP_COUNT_.
     */
    #define APP_USBD_CLASS_IFACE_EP_EXTRACT_(iface_config)                  \
        CONCAT_2(APP_USBD_CLASS_IFACE_EP_EXTRACT_,                          \
                NUM_VA_ARGS_IS_MORE_THAN_1(BRACKET_EXTRACT(iface_config)))  \
                (BRACKET_EXTRACT(iface_config))

    /**
     * @brief Auxiliary macro for @ref APP_USBD_CLASS_IFACE_EP_EXTRACT_
     *
     * This macro is called when interface has no endpoints
     */
    #define APP_USBD_CLASS_IFACE_EP_EXTRACT_0(iface_nr)

    /**
     * @brief Auxiliary macro for @ref APP_USBD_CLASS_IFACE_EP_EXTRACT_
     *
     * This macro is called when interface has at least one endpoint
     */
    #define APP_USBD_CLASS_IFACE_EP_EXTRACT_1(...)              \
                APP_USBD_CLASS_IFACE_EP_EXTRACT_1_(__VA_ARGS__)

    #define APP_USBD_CLASS_IFACE_EP_EXTRACT_1_(iface_nr, ...)   \
                MACRO_MAP_REC(PARAM_CBRACE, __VA_ARGS__)

    /**
     * @brief Generate configuration for single interface
     *
     * This macro extract configuration for single interface.
     * The configuration is inside curly brackets and comma is added on the end.
     * This mean it can be directly used to init array of interface configurations.
     *
     * @param iface_config  Single interface configuration
     * @param N             Currently processed configuration
     * @param iface_configs All interfaces configuration in brackets
     */
    #define APP_USBD_CLASS_IFACE_CONFIG_EXTRACT_(iface_config, N, iface_configs)  \
        CONCAT_2(APP_USBD_CLASS_IFACE_CONFIG_EXTRACT_,                            \
                NUM_VA_ARGS_IS_MORE_THAN_1(BRACKET_EXTRACT(iface_config)))        \
                (N, iface_configs, BRACKET_EXTRACT(iface_config))

    #define APP_USBD_CLASS_IFACE_CONFIG_EXTRACT_x(iface_config, N, iface_configs) \
        [N] = !!!iface_config!!!
    /**
     * @brief Auxiliary macro for @ref APP_USBD_CLASS_IFACE_CONFIG_EXTRACT_
     *
     * This macro is called when interface has no endpoints
     */
    #define APP_USBD_CLASS_IFACE_CONFIG_EXTRACT_0(N, iface_configs, iface_nr)   \
        APP_USBD_CLASS_IFACE_CONFIG_EXTRACT_0_(N, iface_configs, iface_nr)
    #define APP_USBD_CLASS_IFACE_CONFIG_EXTRACT_0_(N, iface_configs, iface_nr)  \
        { .number = iface_nr, .ep_cnt = 0, .ep_offset = 0 },

    /**
     * @brief Auxiliary macro for @ref APP_USBD_CLASS_IFACE_CONFIG_EXTRACT_
     *
     * This macro is called when interface has at last one endpoint
     */
    #define APP_USBD_CLASS_IFACE_CONFIG_EXTRACT_1(N, iface_configs, ...)    \
        APP_USBD_CLASS_IFACE_CONFIG_EXTRACT_1_(N, iface_configs, __VA_ARGS__)
    #define APP_USBD_CLASS_IFACE_CONFIG_EXTRACT_1_(N, iface_configs, iface_nr, ...)     \
        { .number = iface_nr, .ep_cnt = NUM_VA_ARGS(__VA_ARGS__),                       \
          .ep_offset = APP_USBD_CLASS_CONF_TOTAL_EP_COUNT_N(N, iface_configs) *         \
                       sizeof(app_usbd_class_ep_conf_t)                                 \
                       + ((NUM_VA_ARGS(BRACKET_EXTRACT(iface_configs)) - N) *           \
                               sizeof(app_usbd_class_iface_conf_t))                     \
        },

/** @} */


/**
 * @name Macros that uses mapping macros internally
 *
 * Auxiliary macros that uses mapping macros to make some calculations or realize other functionality.
 * Mapped here for easier unit testing and to hide complex mapping functions calling.
 * @{
 */

/**
 * @brief Count total number of endpoints
 *
 * @param iface_configs List of interface configurations like explained
 *                      in documentation for @ref APP_USBD_CLASS_INSTANCE_TYPEDEF
 *
 * @return The equation to calculate the number of endpoints by compiler.
 */
#define APP_USBD_CLASS_CONF_TOTAL_EP_COUNT(iface_configs) \
    (0 MACRO_MAP(APP_USBD_CLASS_CONF_IFACE_EP_PLUS_COUNT_, BRACKET_EXTRACT(iface_configs)))

/**
 * @brief Count total number of endpoint up-to interface index
 *
 * The version of @ref APP_USBD_CLASS_CONF_TOTAL_EP_COUNT macro which takes the
 * number of interfaces to analyze.
 *
 * @param N             Number of interfaces to analyze
 * @param iface_configs List of interface configurations like explained
 *                      in documentation for @ref APP_USBD_CLASS_INSTANCE_TYPEDEF
 *
 * @return The equation to calculate the number of endpoints by compiler.
 */
#define APP_USBD_CLASS_CONF_TOTAL_EP_COUNT_N(N, iface_configs) \
    (0 MACRO_MAP_N(N, APP_USBD_CLASS_CONF_IFACE_EP_PLUS_COUNT_, BRACKET_EXTRACT(iface_configs)))

/**
 * @brief Extract configurations for interfaces
 *
 * This macro extracts the configurations for every interface.
 * Basically uses the @ref APP_USBD_CLASS_IFACE_CONFIG_EXTRACT_ macro on every
 * configuration found.
 *
 * This should generate interface configuration initialization data
 * in comma separated initializers in curly braces.
 *
 * @param iface_configs List of interface configurations like explained
 *                      in documentation for @ref APP_USBD_CLASS_INSTANCE_TYPEDEF
 *
 * @return Comma separated initialization data for all interfaces.
 */
/*lint -emacro( (40), APP_USBD_CLASS_IFACES_CONFIG_EXTRACT) */
#define APP_USBD_CLASS_IFACES_CONFIG_EXTRACT(iface_configs)     \
    MACRO_MAP_FOR_PARAM(iface_configs,                          \
                        APP_USBD_CLASS_IFACE_CONFIG_EXTRACT_,   \
                        BRACKET_EXTRACT(iface_configs))

/**
 * @brief Extract all endpoints
 *
 * Macro that extracts all endpoints from every interface
 *
 * @param iface_configs List of interface configurations like explained
 *                      in documentation for @ref APP_USBD_CLASS_INSTANCE_TYPEDEF
 *
 * @return Comma separated list of endpoints
 */
/*lint -emacro( (40), APP_USBD_CLASS_IFACES_EP_EXTRACT) */
#define APP_USBD_CLASS_IFACES_EP_EXTRACT(iface_configs) \
    MACRO_MAP(APP_USBD_CLASS_IFACE_EP_EXTRACT_, BRACKET_EXTRACT(iface_configs))


/** @} */


/**
 * @brief USBD instance of class mnemonic
 *
 * Macro that generates mnemonic for the name of the structure that describes instance for selected class.
 *
 * @param type_name The name of the instance without _t postfix
 *
 * @return The name with the right postfix to create the name for the type for the class.
 */
#define APP_USBD_CLASS_INSTANCE_TYPE(type_name) CONCAT_2(type_name, _t)

/**
 * @brief USBD data for instance class mnemonic
 *
 * The mnemonic of the variable type that holds writable part of the class instance.
 *
 * @param type_name The name of the instance without _t postfix
 *
 * @return The name with the right postfix to create the name for the data type for the class.
 */
#define APP_USBD_CLASS_DATA_TYPE(type_name) CONCAT_2(type_name, _data_t)

/**
 * @brief Declare class specific member of class instance
 *
 * @param type Type of the attached class configuration.
 *
 * @sa APP_USBD_CLASS_INSTANCE_TYPEDEF
 */
#define APP_USBD_CLASS_INSTANCE_SPECIFIC_DEC(type) type class_part;

/**
 * @brief Used if there is no class specific configuration
 *
 * This constant can be used if there is no specific configuration inside created instance
 *
 * @sa APP_USBD_CLASS_INSTANCE_TYPEDEF
 */
#define APP_USBD_CLASS_INSTANCE_SPECIFIC_DEC_NONE

/**
 * @brief Declare class specific member of class data
 *
 * @param type Type of the attached class data.
 *
 * @sa APP_USBD_CLASS_DATA_TYPEDEF
 */
#define APP_USBD_CLASS_DATA_SPECIFIC_DEC(type) APP_USBD_CLASS_INSTANCE_SPECIFIC_DEC(type)

/**
 * @brief Used if there is no class specific data
 *
 * This constant can be used if there is no specific writable data inside created instance
 *
 * @sa APP_USBD_CLASS_DATA_TYPEDEF
 */
#define APP_USBD_CLASS_DATA_SPECIFIC_DEC_NONE APP_USBD_CLASS_INSTANCE_SPECIFIC_DEC_NONE




/**
 * @brief Instance structure declaration
 *
 * The macro that declares a variable type that would be used to store given class instance.
 * Class instance stores all the data from @ref app_usbd_class_inst_t and overlaid data for specified class.
 *
 * The structure of interface configuration data:
 * @code
 * (
 *    (iface1_nr, (ep1, ep2, ep3)),
      (iface2_nr),
      (iface3_nr, (ep4))
 * )
 * @endcode
 *
 * @param type_name          The name of the instance without _t postfix.
 * @param interfaces_configs List of interface configurations like explained above.
 * @param class_config_dec   Result of the macro
 *                           @ref APP_USBD_CLASS_INSTANCE_SPECIFIC_DEC or
 *                           @ref APP_USBD_CLASS_INSTANCE_SPECIFIC_DEC_NONE
 *
 * @return The definition of the structure type that holds all the required data.
 *
 * @note It should not be used directly in the final application. See @ref APP_USBD_CLASS_DATA_TYPEDEF instead.
 *
 * @note APP_USBD_CLASS_DATA_TYPEDEF has to be called first for the compilation to success.
 *
 * @sa APP_USBD_CLASS_TYPEDEF
 */
#define APP_USBD_CLASS_INSTANCE_TYPEDEF(type_name, interfaces_configs, class_config_dec)     \
    typedef union CONCAT_2(type_name, _u)                                                    \
    {                                                                                        \
        app_usbd_class_inst_t base;                                                          \
        struct                                                                               \
        {                                                                                    \
            APP_USBD_CLASS_DATA_TYPE(type_name) * p_data;                                    \
            app_usbd_class_methods_t const * p_class_methods;                                \
            struct                                                                           \
            {                                                                                \
                uint8_t cnt;                                                                 \
                app_usbd_class_iface_conf_t                                                  \
                                config[NUM_VA_ARGS(BRACKET_EXTRACT(interfaces_configs))];    \
                app_usbd_class_ep_conf_t                                                     \
                                ep[APP_USBD_CLASS_CONF_TOTAL_EP_COUNT(interfaces_configs)];  \
            } iface;                                                                         \
            class_config_dec                                                                 \
        } specific;                                                                          \
    } APP_USBD_CLASS_INSTANCE_TYPE(type_name)

/**
 * @brief Same as @ref APP_USBD_CLASS_INSTANCE_TYPEDEF but for class with EP0 only.
 */
#define APP_USBD_CLASS_INSTANCE_NO_EP_TYPEDEF(type_name, interfaces_configs, class_config_dec)  \
    typedef union CONCAT_2(type_name, _u)                                                       \
    {                                                                                           \
        app_usbd_class_inst_t base;                                                             \
        struct                                                                                  \
        {                                                                                       \
            APP_USBD_CLASS_DATA_TYPE(type_name) * p_data;                                       \
            app_usbd_class_methods_t const * p_class_methods;                                   \
            struct                                                                              \
            {                                                                                   \
                uint8_t cnt;                                                                    \
                app_usbd_class_iface_conf_t                                                     \
                                config[NUM_VA_ARGS(BRACKET_EXTRACT(interfaces_configs))];       \
            } iface;                                                                            \
            class_config_dec                                                                    \
        } specific;                                                                             \
    } APP_USBD_CLASS_INSTANCE_TYPE(type_name)

/**
 * @brief Writable data structure declaration
 *
 * The macro that declares a variable type that would be used to store given class writable data.
 * Writable data contains base part of the type @ref app_usbd_class_data_t followed by
 * class specific data.
 *
 * @param type_name      The name of the type without _t postfix.
 * @param class_data_dec Result of the macro
 *                       @ref APP_USBD_CLASS_DATA_SPECIFIC_DEC or
 *                       @ref APP_USBD_CLASS_DATA_SPECIFIC_DEC_NONE
 *
 * @return The definition of the structure type that holds all the required writable data
 *
 * @note It should not be used directly in the final application. See @ref APP_USBD_CLASS_DATA_TYPEDEF instead.
 *
 * @sa APP_USBD_CLASS_TYPEDEF
 */
#define APP_USBD_CLASS_DATA_TYPEDEF(type_name, class_data_dec) \
    typedef struct                                             \
    {                                                          \
        app_usbd_class_data_t base;                            \
        class_data_dec                                         \
    }APP_USBD_CLASS_DATA_TYPE(type_name)


/**
 * @brief Declare all data types required by the class instance
 *
 * Macro that declares data type first and then instance type.
 *
 * @param type_name          The name of the type without _t postfix.
 * @param interface_configs  List of interface configurations like in @ref APP_USBD_CLASS_INSTANCE_TYPEDEF.
 * @param class_config_dec   Result of the macro
 *                           @ref APP_USBD_CLASS_INSTANCE_SPECIFIC_DEC or
 *                           @ref APP_USBD_CLASS_INSTANCE_SPECIFIC_DEC_NONE
 * @param class_data_dec     Result of the macro
 *                           @ref APP_USBD_CLASS_DATA_SPECIFIC_DEC or
 *                           @ref APP_USBD_CLASS_DATA_SPECIFIC_DEC_NONE
 *
 * @return Declaration of the data type for the instance and instance itself.
 *
 * @sa APP_USBD_CLASS_DATA_TYPEDEF
 * @sa APP_USBD_CLASS_INSTANCE_TYPEDEF
 */
#define APP_USBD_CLASS_TYPEDEF(type_name, interface_configs, class_config_dec, class_data_dec) \
    APP_USBD_CLASS_DATA_TYPEDEF(type_name, class_data_dec);                                    \
    APP_USBD_CLASS_INSTANCE_TYPEDEF(type_name, interface_configs, class_config_dec)

/**
 * @brief Same as @ref APP_USBD_CLASS_TYPEDEF but for class with EP0 only.
 */
#define APP_USBD_CLASS_NO_EP_TYPEDEF(type_name,                                                \
                                     interface_configs,                                        \
                                     class_config_dec,                                         \
                                     class_data_dec)                                           \
    APP_USBD_CLASS_DATA_TYPEDEF(type_name, class_data_dec);                                    \
    APP_USBD_CLASS_INSTANCE_NO_EP_TYPEDEF(type_name, interface_configs, class_config_dec)

/**
 * @brief Forward declaration of type defined by @ref APP_USBD_CLASS_TYPEDEF
 *
 * @param type_name          The name of the type without _t postfix.
 * */
#define APP_USBD_CLASS_FORWARD(type_name) union CONCAT_2(type_name, _u)

/**
 * @brief Generate the initialization data for
 *
 * Macro that generates the initialization data for instance.
 *
 * @param p_ram_data         Pointer to writable instance data structure
 * @param class_methods      Class methods
 * @param interfaces_configs Exactly the same interface config data that in @ref APP_USBD_CLASS_INSTANCE_TYPEDEF
 * @param class_config_part  Configuration part. The data should be inside brackets.
 *                           Any data here would be removed from brackets and then put as an initialization
 *                           data for class_part member of instance structure.
 *
 * @note It should not be used directly in the final application. See @ref APP_USBD_CLASS_INST_DEF instead.
 */
#define APP_USBD_CLASS_INSTANCE_INITVAL(p_ram_data,                                     \
                                        class_methods,                                  \
                                        interfaces_configs,                             \
                                        class_config_part)                              \
    {                                                                                   \
        .specific = {                                                                   \
            .p_data = p_ram_data,                                                       \
            .p_class_methods = class_methods,                                           \
            .iface = {                                                                  \
                .cnt    = NUM_VA_ARGS(BRACKET_EXTRACT(interfaces_configs)),             \
                .config = { APP_USBD_CLASS_IFACES_CONFIG_EXTRACT(interfaces_configs) }, \
                .ep     = { APP_USBD_CLASS_IFACES_EP_EXTRACT(interfaces_configs) }      \
            },                                                                          \
            BRACKET_EXTRACT(class_config_part)                                          \
        }                                                                               \
    }

/**
 * @brief Same as @ref APP_USBD_CLASS_INSTANCE_INITVAL but for class with EP0 only.
 */
#define APP_USBD_CLASS_INSTANCE_NO_EP_INITVAL(p_ram_data,                               \
                                              class_methods,                            \
                                              interfaces_configs,                       \
                                              class_config_part)                        \
    {                                                                                   \
        .specific = {                                                                   \
            .p_data = p_ram_data,                                                       \
            .p_class_methods = class_methods,                                           \
            .iface = {                                                                  \
                .cnt    = NUM_VA_ARGS(BRACKET_EXTRACT(interfaces_configs)),             \
                .config = { APP_USBD_CLASS_IFACES_CONFIG_EXTRACT(interfaces_configs) }  \
            },                                                                          \
            BRACKET_EXTRACT(class_config_part)                                          \
        }                                                                               \
    }

/**
 * @brief Define the base class instance
 *
 * Macro that defines whole instance variable and fill it with initialization data.
 *
 * The tricky part is @c class_config_part.
 * The configuration data here has to be placed inside brackets.
 * Then any type of values can be used depending on the type used in @ref APP_USBD_CLASS_TYPEDEF.
 * If instance does not has any specyfic data, use just empty bracket here.
 * @code
 * APP_USBD_CLASS_TYPEDEF(
 *      some_base_class,
 *      CLASS_BASE_CONFIGURATION,
 *      APP_USBD_CLASS_INSTANCE_SPECIFIC_DEC_NONE,
 *      APP_USBD_CLASS_DATA_SPECIFIC_DEC_NONE
 * );
 * APP_USBD_CLASS_INST_DEF(
 *     some_base_class_inst,
 *     some_base_class,
 *     base_class_event_handler,
 *     CLASS_BASE_CONFIGURATION,
 *     () // Empty configuration
 * );
 * @endcode
 *
 * If the type of instance configuration is simple type, just provide initialization value:
 * @code
 * APP_USBD_CLASS_TYPEDEF(
 *      some_base_class,
 *      CLASS_BASE_CONFIGURATION,
 *      APP_USBD_CLASS_INSTANCE_SPECIFIC_DEC_NONE,
 *      APP_USBD_CLASS_DATA_SPECIFIC_DEC(uint8_t)
 * );
 * APP_USBD_CLASS_INST_DEF(
 *     some_base_class_inst,
 *     some_base_class,
 *     base_class_event_handler,
 *     CLASS_BASE_CONFIGURATION,
 *     (12) // Example values
 * );
 * @endcode
 *
 * If the type of instance configuration is structure, provide initialization value for the whole structure:
 * @code
 * typedef structure
 * {
 *     uint32_t p1;
 *     uint8_t p2;
 * }my_config_t;
 *
 * APP_USBD_CLASS_TYPEDEF(
 *      some_base_class,
 *      CLASS_BASE_CONFIGURATION,
 *      APP_USBD_CLASS_INSTANCE_SPECIFIC_DEC_NONE,
 *      APP_USBD_CLASS_DATA_SPECIFIC_DEC(my_config_t)
 * );
 * APP_USBD_CLASS_INST_DEF(
 *     some_base_class_inst,
 *     some_base_class,
 *     base_class_event_handler,
 *     CLASS_BASE_CONFIGURATION,
 *     ({12, 3}) // Example values
 * );
 * @endcode
 *
 * @param instance_name The name of created instance variable.
 *                      It would be constant variable and its type would be app_usbd_class_inst_t.
 * @param type_name     The name of the variable type. It has to be the same type that was passed to
 *                      @ref APP_USBD_CLASS_TYPEDEF
 * @param class_methods Class unified interface.
 * @param interfaces_configs The same configuration data that the one passed to @ref APP_USBD_CLASS_TYPEDEF
 * @param class_config_part  Configuration data to the type that was declared by class_data_dec when calling
 *                           @ref APP_USBD_CLASS_TYPEDEF.
 *                           Configuration data has to be provided in brackets.
 *                           It would be extracted from brackets and placed in initialization part of configuration structure.
 *                           See detailed description of this macro for more informations.
 */
#define APP_USBD_CLASS_INST_DEF(instance_name,                                  \
                                type_name,                                      \
                                class_methods,                                  \
                                interfaces_configs,                             \
                                class_config_part)                              \
    static APP_USBD_CLASS_DATA_TYPE(type_name) CONCAT_2(instance_name, _data);  \
    static const APP_USBD_CLASS_INSTANCE_TYPE(type_name) instance_name =        \
        APP_USBD_CLASS_INSTANCE_INITVAL(                                        \
            &CONCAT_2(instance_name, _data),                                    \
            class_methods,                                                      \
            interfaces_configs,                                                 \
            class_config_part)


/**
 * @brief Define the base class instance in global scope
 *
 * This is the same macro like @ref APP_USBD_CLASS_INST_DEF but it creates the instance
 * without static keyword.
 *
 * @param instance_name      See documentation for @ref APP_USBD_CLASS_INST_DEF
 * @param type_name          See documentation for @ref APP_USBD_CLASS_INST_DEF
 * @param class_methods      See documentation for @ref APP_USBD_CLASS_INST_DEF
 * @param interfaces_configs See documentation for @ref APP_USBD_CLASS_INST_DEF
 * @param class_config_part  See documentation for @ref APP_USBD_CLASS_INST_DEF
 */
#define APP_USBD_CLASS_INST_GLOBAL_DEF(instance_name,                           \
                                       type_name,                               \
                                       class_methods,                           \
                                       interfaces_configs,                      \
                                       class_config_part)                       \
    static APP_USBD_CLASS_DATA_TYPE(type_name) CONCAT_2(instance_name, _data);  \
    const APP_USBD_CLASS_INSTANCE_TYPE(type_name) instance_name =               \
        APP_USBD_CLASS_INSTANCE_INITVAL(                                        \
            &CONCAT_2(instance_name, _data),                                    \
            class_methods,                                                      \
            interfaces_configs,                                                 \
            class_config_part)

/**
 * @brief Same as @ref APP_USBD_CLASS_INST_GLOBAL_DEF but for class with EP0 only.
 */
#define APP_USBD_CLASS_INST_NO_EP_GLOBAL_DEF(instance_name,                     \
                                             type_name,                         \
                                             class_methods,                     \
                                             interfaces_configs,                \
                                             class_config_part)                 \
    static APP_USBD_CLASS_DATA_TYPE(type_name) CONCAT_2(instance_name, _data);  \
    const APP_USBD_CLASS_INSTANCE_TYPE(type_name) instance_name =               \
        APP_USBD_CLASS_INSTANCE_NO_EP_INITVAL(                                  \
            &CONCAT_2(instance_name, _data),                                    \
            class_methods,                                                      \
            interfaces_configs,                                                 \
            class_config_part)
/**
 * @brief Access class specific configuration
 *
 * Macro that returns class specific configuration.
 *
 * @param[in] p_inst Instance pointer
 *
 * @return A pointer for class specific part of the instance
 *
 * @note If macro is used on the instance that has no class specific configuration
 *       an error would be generated during compilation.
 */
#define APP_USBD_CLASS_GET_SPECIFIC_CONFIG(p_inst) (&((p_inst)->specific.class_part))

/**
 * @brief Access class specific data
 *
 * @param[in] p_inst Instance pointer
 *
 * @return A pointer for class specific part of writable data
 *
 * @note If macro is used on the instance that has no class specific data
 *       an error would be generated during compilation.
 */
#define APP_USBD_CLASS_GET_SPECIFIC_DATA(p_inst) (&(((p_inst)->specific.p_data)->class_part))

/**
 * @brief Macro to get base instance from class specific instance
 *
 * This macro may be used on class specific instance to get base instance that
 * can be processed by base instance access functions.
 * Class specific instance can be just casted to class base instance,
 * but then we would totally lost type safety.
 *
 * A little more safe is to use pointer to base member of class instance.
 * This would generate an error when used on any variable that has no base member
 * and would generate also error if this base member is wrong type.
 */
#define APP_USBD_CLASS_BASE_INSTANCE(p_inst) (&((p_inst)->base))

/*lint -emacro(142 438 616 646, APP_USBD_CLASS_DESCRIPTOR_INIT, APP_USBD_CLASS_DESCRIPTOR_BEGIN, APP_USBD_CLASS_DESCRIPTOR_YIELD, APP_USBD_CLASS_DESCRIPTOR_END, APP_USBD_CLASS_DESCRIPTOR_WRITE)*/

/**
 * @brief Initialize class descriptor
 *
 * @param[in] p_ctx Class descriptor context
 */

#define APP_USBD_CLASS_DESCRIPTOR_INIT(p_ctx)       \
    (p_ctx)->line = 0;

/**
 * @brief Begin class descriptor
 *
 * @param[in] p_ctx    Class descriptor context
 * @param[in] p_buff   Buffer to write into
 * @param[in] max_size Size of the buffer
 */

#define APP_USBD_CLASS_DESCRIPTOR_BEGIN(p_ctx, p_buff, max_size)            \
    ASSERT((p_ctx) != NULL);                                                \
    app_usbd_class_descriptor_state_t this_descriptor_feed;                 \
    this_descriptor_feed.p_buffer     = (p_buff);                           \
    this_descriptor_feed.current_size = 0;                                  \
    this_descriptor_feed.maximum_size = (max_size);                         \
    this_descriptor_feed.p_context    = (p_ctx);                            \
    switch ((this_descriptor_feed.p_context)->line)                         \
    {                                                                       \
        case 0:                                                             \
            ;

/**
 * @brief Yield class descriptor
 *
 */

#define APP_USBD_CLASS_DESCRIPTOR_YIELD()                   \
do                                                          \
{                                                           \
        (this_descriptor_feed.p_context)->line = __LINE__;  \
        return true;                                        \
        case __LINE__:                                      \
            ;                                               \
} while (0)

/*lint -emacro(438 527, APP_USBD_CLASS_DESCRIPTOR_END)*/

/**
 * @brief End class descriptor
 *
 * This function has to be called at the end of class descriptor feeder function.
 * No other operations in feeder function can be done after calling it.
 */

#define APP_USBD_CLASS_DESCRIPTOR_END()             \
        APP_USBD_CLASS_DESCRIPTOR_YIELD();          \
    }                                               \
    (this_descriptor_feed.p_context)->line = 0;     \
    return false;


/**
 * @brief Write descriptor using protothreads
 *
 * This function writes one byte to the buffer with offset. If buffer is full
 * it yields.
 *
 * It is used by the class descriptor feeders internally.
 *
 * @ref APP_USBD_CLASS_DESCRIPTOR_BEGIN has to be called before using this function.
 * @ref APP_USBD_CLASS_DESCRIPTOR_END has to be called after last use of this function.
 *
 * @param data Byte to be written to buffer
 */
#define APP_USBD_CLASS_DESCRIPTOR_WRITE(data)                                           \
do                                                                                      \
{                                                                                       \
    (this_descriptor_feed.p_context)->data_buffer = (data);                             \
    if (this_descriptor_feed.current_size >= this_descriptor_feed.maximum_size)         \
    {                                                                                   \
        APP_USBD_CLASS_DESCRIPTOR_YIELD();                                              \
    }                                                                                   \
    if(this_descriptor_feed.p_buffer != NULL)                                           \
    {                                                                                   \
        *(this_descriptor_feed.p_buffer + this_descriptor_feed.current_size) =          \
            (this_descriptor_feed.p_context)->data_buffer;                              \
    }                                                                                   \
    this_descriptor_feed.current_size++;                                                \
} while(0);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* APP_USBD_CLASS_BASE_H__ */
