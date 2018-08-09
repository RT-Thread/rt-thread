/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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

#ifndef NRF_SECTION_ITER_H__
#define NRF_SECTION_ITER_H__

#include <stddef.h>
#include "nrf_section.h"
#include "nrf_assert.h"
#include "app_util.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @defgroup nrf_section_iter Section variables iterator
 * @ingroup app_common
 * @{
 */

/**@brief Single section description structure. */
typedef struct
{
    void * p_start;     //!< Pointer to the start of section.
    void * p_end;       //!< Pointer to the end of section.
} nrf_section_t;


/**@brief Set of the sections description structure. */
typedef struct
{
#if defined(__GNUC__)
    nrf_section_t           section;    //!< Description of the set of sections.
                                        /**<
                                         * In case of GCC all sections in the set are sorted and
                                         * placed in contiguous area, because they are treated as
                                         * one section.
                                         */
#else
    nrf_section_t const   * p_first;    //!< Pointer to the first section in the set.
    nrf_section_t const   * p_last;     //!< Pointer to the last section in the set.
#endif
    size_t                  item_size;  //!< Size of the single item in the section.
} nrf_section_set_t;


/**@brief Section iterator structure. */
typedef struct
{
    nrf_section_set_t const * p_set;        //!< Pointer to the appropriate section set.
#if !defined(__GNUC__)
    nrf_section_t const     * p_section;    //!< Pointer to the selected section.
                                            /**<
                                             * In case of GCC all sections in the set are sorted and
                                             * placed in contiguous area, because they are treated
                                             * as one section.
                                             */
#endif
    void                    * p_item;       //!< Pointer to the selected item in the section.
} nrf_section_iter_t;


/**@brief Create a set of sections.
 *
 * @note  This macro reserves memory for the given set of sections.
 *
 * @details  A set of sections, is an ordered collections of sections.
 *
 * @param[in]   _name   Name of the set.
 * @param[in]   _type   Type of the elements stored in the sections.
 * @param[in]   _count  Number of the sections in the set. This parameter is ignored in case of GCC.
 * @hideinitializer
 */
#if defined(__GNUC__)

#define NRF_SECTION_SET_DEF(_name, _type, _count)                                                   \
                                                                                                    \
    NRF_SECTION_DEF(_name, _type);                                                                  \
    static nrf_section_set_t const _name =                                                          \
    {                                                                                               \
        .section =                                                                                  \
        {                                                                                           \
            .p_start = NRF_SECTION_START_ADDR(_name),                                               \
            .p_end   = NRF_SECTION_END_ADDR(_name),                                                 \
        },                                                                                          \
        .item_size  = sizeof(_type),                                                                \
    }

#else

#define NRF_SECTION_SET_DEF(_name, _type, _count)                                                   \
/*lint -save -emacro(14, MACRO_REPEAT_FOR*)  */                                                     \
MACRO_REPEAT_FOR(_count, NRF_SECTION_DEF_, _name, _type)                                            \
static nrf_section_t const CONCAT_2(_name, _array)[] =                                              \
{                                                                                                   \
    MACRO_REPEAT_FOR(_count, NRF_SECTION_SET_DEF_, _name)                                           \
};                                                                                                  \
/*lint -restore */                                                                                  \
static nrf_section_set_t const _name =                                                              \
{                                                                                                   \
    .p_first   = CONCAT_2(_name, _array),                                                           \
    .p_last    = CONCAT_2(_name, _array) + ARRAY_SIZE(CONCAT_2(_name, _array)),                     \
    .item_size = sizeof(_type),                                                                     \
}

#ifndef DOXYGEN
#define NRF_SECTION_DEF_(_priority, _name, _type)                                                   \
NRF_SECTION_DEF(CONCAT_2(_name, _priority), _type);

#define NRF_SECTION_SET_DEF_(_priority, _name)                                                      \
{                                                                                                   \
    .p_start = NRF_SECTION_START_ADDR(CONCAT_2(_name, _priority)),                                  \
    .p_end   = NRF_SECTION_END_ADDR(CONCAT_2(_name, _priority)),                                    \
},
#endif // DOXYGEN
#endif // __GNUC__


/**@brief   Macro to declare a variable and register it in the section set.
 *
 * @note    The order of the section in the set is based on the priority. The order with which
 *          variables are placed in a section is dependant on the order with which the linker
 *          encouters the variables during linking.
 *
 * @param[in]   _name       Name of the section set.
 * @param[in]   _priority   Priority of the desired section.
 * @param[in]   _var        The variable to register in the given section.
 * @hideinitializer
 */
#define NRF_SECTION_SET_ITEM_REGISTER(_name, _priority, _var)                                       \
    NRF_SECTION_ITEM_REGISTER(CONCAT_2(_name, _priority), _var)


/**@brief Function for initializing the section set iterator.
 *
 * @param[in]   p_iter  Pointer to the iterator.
 * @param[in]   p_set   Pointer to the sections set.
 */
void nrf_section_iter_init(nrf_section_iter_t * p_iter, nrf_section_set_t const * p_set);


/**@brief Function for incrementing iterator.
 *
 * @param[in]   p_iter   Pointer to the iterator.
 */
void nrf_section_iter_next(nrf_section_iter_t * p_iter);


/**@brief Function for getting the element pointed to by the iterator.
 *
 * @param[in]   p_iter  Pointer to the iterator.
 *
 * @retval  Pointer to the element or NULL if iterator points end of the set.
 */
static inline void * nrf_section_iter_get(nrf_section_iter_t const * p_iter)
{
    ASSERT(p_iter);
    return p_iter->p_item;
}

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NRF_SECTION_ITER_H__
