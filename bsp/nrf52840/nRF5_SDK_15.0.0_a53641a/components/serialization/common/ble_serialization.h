/**
 * Copyright (c) 2013 - 2018, Nordic Semiconductor ASA
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
#ifndef BLE_SERIALIZATION_H__
#define BLE_SERIALIZATION_H__

#include "nordic_common.h"
#include "nrf_error.h"
#include <stdint.h>
#include <stddef.h>
#include "cond_field_serialization.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Types of serialization packets. */
typedef enum
{
    SER_PKT_TYPE_CMD = 0,     /**< Command packet type. */
    SER_PKT_TYPE_RESP,        /**< Command Response packet type. */
    SER_PKT_TYPE_EVT,         /**< Event packet type. */
    SER_PKT_TYPE_DTM_CMD,     /**< DTM Command packet type. */
    SER_PKT_TYPE_DTM_RESP,    /**< DTM Response packet type. */
    SER_PKT_TYPE_RESET_CMD,   /**< System Reset Command packet type. */
#if defined(ANT_STACK_SUPPORT_REQD)
    SER_PKT_TYPE_ANT_CMD,     /**< ANT Command packet type. */
    SER_PKT_TYPE_ANT_RESP,    /**< ANT Response packet type. */
    SER_PKT_TYPE_ANT_EVT,     /**< ANT Event packet type. */
#endif
    SER_PKT_TYPE_MAX          /**< Upper bound. */
} ser_pkt_type_t;

#define  LOW16(a) ((uint16_t)((a & 0x0000FFFF) >> 0))
#define HIGH16(a) ((uint16_t)((a & 0xFFFF0000) >> 16))

//lint -esym(516,__INTADDR__) Symbol '__INTADDR__()' has arg. type conflict
//lint -esym(628,__INTADDR__) no argument information provided for function '__INTADDR__()'

/** Size in bytes of the Error Code field in a Command Response packet. */
#define SER_ERR_CODE_SIZE              4
/** Size in bytes of the Packet Type field (@ref ser_pkt_type_t). */
#define SER_PKT_TYPE_SIZE              1
/** Size in bytes of the Operation Code field. */
#define SER_OP_CODE_SIZE               1

/** Position of the Packet Type field in a serialized packet buffer. */
#define SER_PKT_TYPE_POS               0
/** Position of the Operation Code field in a serialized packet buffer. */
#define SER_PKT_OP_CODE_POS            (SER_PKT_TYPE_SIZE)
/** Position of the Data in a serialized packet buffer. */
#define SER_PKT_DATA_POS               (SER_PKT_TYPE_SIZE + SER_OP_CODE_SIZE)

/** Position of the Operation Code field in a command buffer. */
#define SER_CMD_OP_CODE_POS            0
/** Position of the Data in a command buffer.*/
#define SER_CMD_DATA_POS               (SER_OP_CODE_SIZE)
/** Size of the Command header. */
#define SER_CMD_HEADER_SIZE            (SER_OP_CODE_SIZE)
/** Size of the Command Response header. */
#define SER_CMD_RSP_HEADER_SIZE        (SER_OP_CODE_SIZE + SER_ERR_CODE_SIZE)
/** Position of the Command Response code. */
#define SER_CMD_RSP_STATUS_CODE_POS    (SER_OP_CODE_SIZE)

/** Size of event ID field. */
#define SER_EVT_ID_SIZE                2
/** Position of event ID field. */
#define SER_EVT_ID_POS                 0
/** Size of event header. */
#define SER_EVT_HEADER_SIZE            (SER_EVT_ID_SIZE)
/** Size of event connection handler. */
#define SER_EVT_CONN_HANDLE_SIZE       2

#if defined(ANT_STACK_SUPPORT_REQD)
/** Size of event ID field. */
#define SER_ANT_EVT_ID_SIZE            2
/** Position of event ID field. */
#define SER_ANT_EVT_ID_POS             0
/** Size of event header. */
#define SER_ANT_EVT_HEADER_SIZE        (SER_ANT_EVT_ID_SIZE)
#endif

/** Position of the Op Code in the DTM command buffer.*/
#define SER_DTM_CMD_OP_CODE_POS        0
/** Position of the data in the DTM command buffer.*/
#define SER_DTM_CMD_DATA_POS           1

/** Position of the Op Code in the DTM command response buffer.*/
#define SER_DTM_RESP_OP_CODE_POS       1
/** Position of the status field in the DTM command response buffer.*/
#define SER_DTM_RESP_STATUS_POS        2

/** Value to indicate that an optional field is encoded in the serialized packet, e.g. white list.*/
#define SER_FIELD_PRESENT              0x01
/** Value to indicate that an optional field is not encoded in the serialized packet. */
#define SER_FIELD_NOT_PRESENT          0x00


/** Enable SER_ASSERT<*> asserts */
#define SER_ASSERTS_ENABLED 1

/** Returns with error code if expr is not true. It is used for checking error which should be
 * checked even when SER_ASSERTS_ENABLED is not set. */
#define SER_ERROR_CHECK(expr, error_code) do { if (!(expr)) return (error_code); } while (0)


#ifdef SER_ASSERTS_ENABLED
/** Returns with error code if expr is not true. */
#define SER_ASSERT(expr, error_code) SER_ERROR_CHECK(expr, error_code)
/** Returns if expression is not true. */
#define SER_ASSERT_VOID_RETURN(expr) do { if (!(expr)) return; } while (0)
/** Returns with  \ref NRF_ERROR_INVALID_LENGTH if len is not less or equal to maxlen. */
#define SER_ASSERT_LENGTH_LEQ(len, maxlen) \
    SER_ASSERT((len) <= (maxlen), NRF_ERROR_INVALID_LENGTH)
/** Returns with  \ref NRF_ERROR_INVALID_LENGTH if actual_len is not equal to expected_len. */
#define SER_ASSERT_LENGTH_EQ(actual_len, expected_len) \
    SER_ASSERT((actual_len) == (expected_len), NRF_ERROR_INVALID_LENGTH)
/** Returns with  \ref NRF_ERROR_NULL if pointer is null. */
#define SER_ASSERT_NOT_NULL(ptr) SER_ASSERT((ptr) != NULL, NRF_ERROR_NULL)
#else
#define SER_ASSERT(expr, error_code)
#define SER_ASSERT_VOID_RETURN(expr)
#define SER_ASSERT_LENGTH_LEQ(len, maxlen) UNUSED_VARIABLE(maxlen)
#define SER_ASSERT_LENGTH_EQ(actual_len, expected_len)
#define SER_ASSERT_NOT_NULL(ptr)
#endif

#if  defined(BLE_GATT_MTU_SIZE_DEFAULT) && !defined(GATT_MTU_SIZE_DEFAULT)
#define GATT_MTU_SIZE_DEFAULT BLE_GATT_MTU_SIZE_DEFAULT
#endif

/** See Bluetooth 4.0 spec: 3.4.4.7. */
#define BLE_GATTC_HANDLE_COUNT_LEN_MAX     ((GATT_MTU_SIZE_DEFAULT - 1) / 2)

/** Subtract 1 from X if X is greater than 0. */
#define SUB1(X) (((X)>0) ? ((X)-1) : (X))

static inline void static_force_impl_castable_p_void(void const * const p) {}
/** Force the argument to be a double pointer. */
#define STATIC_FORCE_PP(PP) static_force_impl_castable_p_void(*(PP))

/** Field decoder for special structures containing variable length data. */
typedef uint32_t (*field_ext_decoder_handler_t)(uint8_t const * const p_buf,
                                                uint32_t              buf_len,
                                                uint32_t * const      p_index,
                                                uint32_t * const      p_ext_length,
                                                void *                p_field);


/** Push uint8_t field into the output packet. */
#define SER_PUSH_uint8(P_VAR) do { \
                err_code = uint8_t_enc((P_VAR), p_buf, buf_len, p_index); \
                SER_ASSERT(err_code == NRF_SUCCESS, err_code);            \
            } while (0)

/** Push uint16_t field into the output packet. */
#define SER_PUSH_uint16(P_VAR) do { \
                err_code = uint16_t_enc((P_VAR), p_buf, buf_len, p_index); \
                SER_ASSERT(err_code == NRF_SUCCESS, err_code);             \
            } while (0)

/** Push uint32_t field into the output packet. */
#define SER_PUSH_uint32(P_VAR) do { \
                err_code = uint32_t_enc((P_VAR), p_buf, buf_len, p_index); \
                SER_ASSERT(err_code == NRF_SUCCESS, err_code);             \
            } while (0)

/** Push int8_t field into the output packet. */
#define SER_PUSH_int8(P_VAR)  SER_PUSH_uint8(P_VAR)

/** Push uint16_t field into the output packet. */
#define SER_PUSH_int16(P_VAR) SER_PUSH_uint16(P_VAR)

/** Push uint32_t field into the output packet. */
#define SER_PUSH_int32(P_VAR) SER_PUSH_uint32(P_VAR)

/** Push a constant length array of bytes into the output packet. */
#define SER_PUSH_uint8array(P_DATA, LEN) do { \
                err_code = uint8_vector_enc((P_DATA), (LEN), p_buf, buf_len, p_index); \
                SER_ASSERT(err_code == NRF_SUCCESS, err_code);                         \
            } while (0)

/** Push a variable length (8-bit) array of bytes into the output packet. */
#define SER_PUSH_len8data(P_DATA, LEN) do { \
                err_code = len8data_enc((P_DATA), (LEN), p_buf, buf_len, p_index); \
                SER_ASSERT(err_code == NRF_SUCCESS, err_code);                     \
            } while (0)

/** Push a variable length (16-bit) array of bytes into the output packet. */
#define SER_PUSH_len16data(P_DATA, LEN) do { \
                err_code = len16data_enc((P_DATA), (LEN), p_buf, buf_len, p_index); \
                SER_ASSERT(err_code == NRF_SUCCESS, err_code);                      \
            } while (0)

/** Push a variable length (16-bit) array of 16-bit words into the output packet. */
#define SER_PUSH_len16data16(P_DATA, LEN) do { \
                err_code = count16_cond_data16_enc((P_DATA), (LEN), p_buf, buf_len, p_index); \
                SER_ASSERT(err_code == NRF_SUCCESS, err_code);                                \
            } while (0)

/** Push a buffer into the output packet. */
#define SER_PUSH_buf(P_DATA, LEN) do { \
                err_code = buf_enc((P_DATA), (LEN), p_buf, buf_len, p_index); \
                SER_ASSERT(err_code == NRF_SUCCESS, err_code);                \
            } while (0)

/** Push a structure into the output packet. */
#define SER_PUSH_FIELD(P_VAR, P_ENCODER) do { \
                err_code = field_enc((P_VAR), p_buf, buf_len, p_index, (P_ENCODER)); \
                SER_ASSERT(err_code == NRF_SUCCESS, err_code);                       \
            } while (0)

/** Push an array of structures into the output packet. */
#define SER_PUSH_FIELD_ARRAY(P_ARRAY, P_ENCODER, COUNT) do { \
                for (uint32_t _idx = 0; _idx < (COUNT); ++_idx)  \
                {                                                \
                    SER_PUSH_FIELD(&((P_ARRAY)[_idx]),P_ENCODER);\
                }                                                \
            } while (0)

/** Conditionally push a field if the specified pointer is not null. */
#define SER_PUSH_COND(P_VAR, P_ENCODER) do { \
                err_code = cond_field_enc((P_VAR), p_buf, buf_len, p_index, (P_ENCODER)); \
                SER_ASSERT(err_code == NRF_SUCCESS, err_code);                            \
            } while (0)


/** Pull a uint8_t field from the input packet. */
#define SER_PULL_uint8(P_VAR) do { \
                err_code = uint8_t_dec(p_buf, packet_len, p_index, (P_VAR)); \
                SER_ASSERT(err_code == NRF_SUCCESS, err_code);               \
            } while (0)

/** Pull a uint16_t field from the input packet. */
#define SER_PULL_uint16(P_VAR) do { \
                err_code = uint16_t_dec(p_buf, packet_len, p_index, (P_VAR)); \
                SER_ASSERT(err_code == NRF_SUCCESS, err_code);                \
            } while (0)

/** Pull a uint32_t field from the input packet. */
#define SER_PULL_uint32(P_VAR) do { \
                err_code = uint32_t_dec(p_buf, packet_len, p_index, (P_VAR)); \
                SER_ASSERT(err_code == NRF_SUCCESS, err_code);                \
            } while (0)

/** Pull an int8_t field from the input packet. */
#define SER_PULL_int8(P_VAR)  SER_PULL_uint8(P_VAR)

/** Pull an int16_t field from the input packet. */
#define SER_PULL_int16(P_VAR) SER_PULL_uint16(P_VAR)

/** Pull an int32_t field from the input packet. */
#define SER_PULL_int32(P_VAR) SER_PULL_uint32(P_VAR)

/** Pull a constant length byte array from the input packet. */
#define SER_PULL_uint8array(P_DATA, LEN) do { \
                err_code = uint8_vector_dec(p_buf, packet_len, p_index, (P_DATA), (LEN)); \
                SER_ASSERT(err_code == NRF_SUCCESS, err_code);                            \
            } while (0)

/** Pull a variable length (8-bit) byte array from the input packet. */
#define SER_PULL_len8data(PP_DATA, LEN) do { \
                STATIC_FORCE_PP(PP_DATA);                                              \
                err_code = len8data_dec(p_buf, packet_len, p_index, (PP_DATA), (LEN)); \
                SER_ASSERT(err_code == NRF_SUCCESS, err_code);                         \
            } while (0)

/** Pull a variable length (16-bit) byte array from the input packet. */
#define SER_PULL_len16data(PP_DATA, P_LEN) do { \
                STATIC_FORCE_PP(PP_DATA);                                                 \
                err_code = len16data_dec(p_buf, packet_len, p_index, (PP_DATA), (P_LEN)); \
                SER_ASSERT(err_code == NRF_SUCCESS, err_code);                            \
            } while (0)

/** Pull a variable length (16-bit) word (16-bit) array from the input packet. */
#define SER_PULL_len16data16(PP_DATA, P_LEN) do { \
                STATIC_FORCE_PP(PP_DATA);                                                           \
                err_code = count16_cond_data16_dec(p_buf, packet_len, p_index, (PP_DATA), (P_LEN)); \
                SER_ASSERT(err_code == NRF_SUCCESS, err_code);                                      \
            } while (0)

/** Pull a buffer from the input packet. */
#define SER_PULL_buf(PP_DATA, OUT_BUF_LEN, LEN) do { \
                STATIC_FORCE_PP(PP_DATA);                                                        \
                err_code = buf_dec(p_buf, packet_len, p_index, (PP_DATA), (OUT_BUF_LEN), (LEN)); \
                SER_ASSERT(err_code == NRF_SUCCESS, err_code);                                   \
            } while (0)

/** Pull a structure from the input packet. */
#define SER_PULL_FIELD(P_VAR, P_DECODER) do { \
                err_code = field_dec(p_buf, packet_len, p_index, (P_VAR), (P_DECODER)); \
                SER_ASSERT(err_code == NRF_SUCCESS, err_code);                          \
            } while (0)

/** Pull an array of structures from the input packet. */
#define SER_PULL_FIELD_ARRAY(P_ARRAY, P_DECODER, COUNT) do { \
                for (uint32_t _idx = 0; _idx < (COUNT); ++_idx)    \
                {                                                  \
                    SER_PULL_FIELD(&((P_ARRAY)[_idx]),P_DECODER);  \
                }                                                  \
            } while (0)

/** Conditionally pull a structure from the input packet. */
#define SER_PULL_COND(PP_VAR, P_DECODER) do { \
                STATIC_FORCE_PP(PP_VAR);                                                                \
                err_code = cond_field_dec(p_buf, packet_len, p_index, (void * *)(PP_VAR), (P_DECODER)); \
                SER_ASSERT(err_code == NRF_SUCCESS, err_code);                                          \
            } while (0)


/** Start the encoding of a structure and prepare local variables for the usage of SER_PUSH_ macros. */
#define SER_STRUCT_ENC_BEGIN(STRUCT_TYPE)                           \
            SER_ASSERT_NOT_NULL(p_buf);                             \
            SER_ASSERT_NOT_NULL(p_index);                           \
            SER_ASSERT_NOT_NULL(p_void_struct);                     \
            STRUCT_TYPE * p_struct = (STRUCT_TYPE *) p_void_struct; \
            uint32_t err_code = NRF_SUCCESS

/** End the encoding of a structure. */
#define SER_STRUCT_ENC_END return err_code

/** Start the decoding of a structure and prepare local variables for the usage of SER_PULL_ macros. */
#define SER_STRUCT_DEC_BEGIN(STRUCT_TYPE)                           \
            SER_ASSERT_NOT_NULL(p_buf);                             \
            SER_ASSERT_NOT_NULL(p_index);                           \
            SER_ASSERT_NOT_NULL(p_void_struct);                     \
            STRUCT_TYPE * p_struct = (STRUCT_TYPE *) p_void_struct; \
            uint32_t err_code = NRF_SUCCESS;                        \
            uint32_t packet_len = buf_len

/** End the encoding of a structure. */
#define SER_STRUCT_DEC_END return err_code


/** Start the encoding of command request and prepare local variables for the usage of SER_PUSH_ macros. */
#define SER_REQ_ENC_BEGIN(OPCODE)              \
            SER_ASSERT_NOT_NULL(p_buf);        \
            SER_ASSERT_NOT_NULL(p_buf_len);    \
                                               \
            uint32_t index    = 0;             \
            uint32_t * const p_index = &index; \
            uint32_t err_code = NRF_SUCCESS;   \
            uint32_t buf_len  = *p_buf_len;    \
                                               \
            uint8_t  opcode   = (OPCODE);      \
            SER_PUSH_uint8(&opcode)

/** End the encoding of command request. */
#define SER_REQ_ENC_END    \
            *p_buf_len = index; \
            return NRF_SUCCESS  \

/** Start the decoding of command response that does not contain any data except the result code. */
#define SER_RSP_DEC_RESULT_ONLY(OPCODE) \
            return ser_ble_cmd_rsp_dec(p_buf, packet_len, (OPCODE), p_result_code)

/** Start the decoding of command response and prepare local variables for the usage of SER_PULL_ macros. */
#define SER_RSP_DEC_BEGIN(OPCODE)                           \
            SER_ASSERT_NOT_NULL(p_buf);                     \
            SER_ASSERT_NOT_NULL(p_result_code);             \
            uint32_t err_code = NRF_SUCCESS;                \
            uint32_t index    = 0;                          \
            uint32_t * const  p_index = &index;             \
            /* Decode the result code and exit if decoding has failed or \
               the decoded result is not NRF_SUCCESS. */        \
            err_code = ser_ble_cmd_rsp_result_code_dec(p_buf, &index, packet_len, (OPCODE), p_result_code); \
                                                            \
            SER_ASSERT(err_code == NRF_SUCCESS, err_code);  \
            if (*p_result_code != NRF_SUCCESS)              \
            {                                               \
                SER_ASSERT_LENGTH_EQ(index, packet_len);    \
                return NRF_SUCCESS;                         \
            }

/** End the decoding of command response. */
#define SER_RSP_DEC_END                                  \
                /* Require all data to be pulled. */     \
                SER_ASSERT_LENGTH_EQ(index, packet_len); \
                return err_code


/** Start the decoding of command request and prepare local variables for the usage of SER_PULL_ macros. */
#define SER_REQ_DEC_BEGIN(OPCODE)                                           \
            SER_ASSERT_NOT_NULL(p_buf);                                     \
            SER_ASSERT(packet_len>0, NRF_ERROR_INVALID_PARAM);              \
            uint32_t index = 0;                                             \
            uint32_t * const p_index = &index;                              \
            uint32_t err_code = NRF_SUCCESS;                                \
            SER_ASSERT(p_buf[index] == (OPCODE), NRF_ERROR_INVALID_PARAM);  \
            (void)err_code;                                                 \
            (void)p_index;                                                  \
            ++index

/** End the decoding of command request. */
#define SER_REQ_DEC_END                              \
            SER_ASSERT_LENGTH_EQ(index, packet_len); \
            return NRF_SUCCESS

/** Start the encoding of command response and prepare local variables for the usage of SER_PUSH_ macros. */
#define SER_RSP_ENC_BEGIN(OPCODE)                           \
            SER_ASSERT_NOT_NULL(p_buf);                     \
            SER_ASSERT_NOT_NULL(p_buf_len);                 \
            uint32_t index    = 0;                          \
            uint32_t * const p_index = &index;              \
            uint32_t err_code = NRF_SUCCESS;                \
            uint32_t buf_len  = *p_buf_len;                 \
            /* Push the opcode + result and exit if result  \
               is not NRF_SUCCESS. */                       \
            uint8_t  opcode   = (OPCODE);                   \
            SER_PUSH_uint8(&opcode);                        \
            SER_PUSH_uint32(&return_code);                  \
                                                            \
            SER_ASSERT(err_code == NRF_SUCCESS, err_code);  \
            if (return_code != NRF_SUCCESS)                 \
            {                                               \
                SER_RSP_ENC_END;                            \
            }

/** Start the encoding of command response that contains the result code only. */
#define SER_RSP_ENC_RESULT_ONLY(OPCODE) \
    return ser_ble_cmd_rsp_status_code_enc((OPCODE), return_code, p_buf, p_buf_len)

/** End the encoding of command response. */
#define SER_RSP_ENC_END         \
            *p_buf_len = index; \
            return NRF_SUCCESS


/** Start the encoding of an event and prepare local variables for the usage of SER_PUSH_ macros. */
#define SER_EVT_ENC_BEGIN(EVT_HEADER)           \
            SER_ASSERT_NOT_NULL(p_event);       \
            SER_ASSERT_NOT_NULL(p_buf);         \
            SER_ASSERT_NOT_NULL(p_buf_len);     \
            SER_ASSERT(p_event->header.evt_id == (EVT_HEADER), NRF_ERROR_INVALID_PARAM); \
            uint32_t index      = 0;            \
            uint32_t * p_index    = &index;     \
            uint32_t buf_len    = *p_buf_len;   \
            uint32_t err_code   = NRF_SUCCESS;  \
            uint16_t evt_header = (EVT_HEADER); \
            /* Push event header. */            \
            SER_PUSH_uint16(&evt_header)

/** End the encoding of an event. */
#define SER_EVT_ENC_END         \
            *p_buf_len = index; \
            return err_code


/** Start the decoding of an event that has an event-specific data structure
    and prepare local variables for the usage of SER_PULL_ macros. */
#define SER_EVT_DEC_BEGIN(EVT_CODE, EVT_GROUP, EVT_NAME)            \
            uint32_t err_code = NRF_SUCCESS;                        \
            uint32_t index = 0;                                     \
            uint32_t * p_index = &index;                            \
            SER_ASSERT_NOT_NULL(p_buf);                             \
            SER_ASSERT_NOT_NULL(p_event_len);                       \
            /* Calculate the base event structure length     */     \
            /* and make sure that there is enough free space */     \
            /* in the output buffer. */                             \
            uint32_t evt_struct_len =                               \
                    offsetof(ble_evt_t, evt.EVT_GROUP##_evt.params) \
                    - offsetof(ble_evt_t, evt)                      \
                    + sizeof(ble_##EVT_GROUP##_evt_##EVT_NAME##_t); \
            SER_ASSERT_LENGTH_LEQ(evt_struct_len, *p_event_len);    \
            *p_event_len -= evt_struct_len;                         \
            /* Some structures contains variable length arrays */   \
            /* and the overall size may be greater.            */   \
            uint32_t evt_extended_len = 0;                          \
            (void) evt_extended_len;                                \
            p_event->header.evt_id = EVT_CODE

/** Start the decoding of an event that has no event-specific data structure.
    and prepare local variables for the usage of SER_PULL_ macros. */
#define SER_EVT_DEC_BEGIN_NO_STRUCT(EVT_CODE, EVT_GROUP)            \
            uint32_t err_code = NRF_SUCCESS;                        \
            uint32_t index = 0;                                     \
            uint32_t * p_index = &index;                            \
            SER_ASSERT_NOT_NULL(p_buf);                             \
            SER_ASSERT_NOT_NULL(p_event_len);                       \
            /* Calculate the base event structure length     */     \
            /* and make sure that there is enough free space */     \
            /* in the output buffer. */                             \
            uint32_t evt_struct_len =                               \
                    offsetof(ble_evt_t, evt.EVT_GROUP##_evt.params) \
                    - offsetof(ble_evt_t, evt)          ;           \
            SER_ASSERT_LENGTH_LEQ(evt_struct_len, *p_event_len);    \
            *p_event_len -= evt_struct_len;                         \
            /* Some structures contain variable length arrays */   \
            /* and the overall size may be greater.            */   \
            uint32_t evt_extended_len = 0;                          \
            (void) evt_extended_len;                                \
            p_event->header.evt_id = EVT_CODE

/** End the decoding of an event. */
#define SER_EVT_DEC_END                                       \
            SER_ASSERT_LENGTH_EQ(index, packet_len);          \
            /*p_event_len = index;                */          \
            /*p_event->header.evt_len = index;     */         \
            *p_event_len = evt_struct_len + evt_extended_len; \
            return NRF_SUCCESS

/** Push an event-specific special field that contains variable length fields and get the extended data size. */
#define SER_PULL_FIELD_EXTENDED(P_VAR, P_DECODER)               \
            do                                                  \
            {                                                   \
                uint32_t field_ext_len = *p_event_len;          \
                err_code = field_ext_dec(p_buf, packet_len, p_index, &field_ext_len, (P_VAR), (P_DECODER)); \
                SER_ASSERT(err_code == NRF_SUCCESS, err_code);  \
                *p_event_len     -= field_ext_len;              \
                evt_extended_len += field_ext_len;              \
            } while (0)                                          \


/** Generic command response status code encoder. */
uint32_t ser_ble_cmd_rsp_status_code_enc(uint8_t          op_code,
                                         uint32_t         command_status,
                                         uint8_t * const  p_buf,
                                         uint32_t * const p_buf_len);

/** Generic command response result code decoder. */
uint32_t ser_ble_cmd_rsp_result_code_dec(uint8_t const * const p_buf,
                                         uint32_t * const      p_pos,
                                         uint32_t              packet_len,
                                         uint8_t               op_code,
                                         uint32_t * const      p_result_code);

/** Generic command response decoder. */
uint32_t ser_ble_cmd_rsp_dec(uint8_t const * const p_buf,
                             uint32_t              packet_len,
                             uint8_t               op_code,
                             uint32_t * const      p_result_code);



/**@brief Function for safe field encoding field.
 *
 * @param[in]      p_field          Pointer to the input struct. Must not be a null.
 * @param[in]      p_buf            Pointer to the beginning of the output buffer.
 * @param[in]      buf_len          Size of the buffer.
 * @param[in,out]  p_index          \c in: Index to start of uint8 value in buffer.
 *                                  \c out: Index in the buffer to the first byte after the encoded data.
 * @param[in]      fp_field_encoder Pointer to the function that implements fields encoding.
 *
 * @return NRF_SUCCESS              Field encoded successfully.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_NULL           p_field or fp_field_encoder is NULL.
 */
static inline uint32_t field_enc(void const * const      p_field,
                                 uint8_t * const         p_buf,
                                 uint32_t                buf_len,
                                 uint32_t * const        p_index,
                                 field_encoder_handler_t fp_field_encoder)
{
    SER_ASSERT_NOT_NULL(fp_field_encoder);
    SER_ASSERT_NOT_NULL(p_field);

    return fp_field_encoder(p_field, p_buf, buf_len, p_index);
}

/**@brief Function for safe field decoding.
 *
 * Function checks if conditional field is present in the input buffer and if it is set, it calls
 * the provided parser function that attempts to parse the buffer content to the known field.
 *
 * @param[in]      p_buf            Pointer to the beginning of the input buffer.
 * @param[in]      buf_len          Size of the buffer.
 * @param[in,out]  p_index          \c in: Index to the start of uint8 value in buffer.
 *                                  \c out: Index in the buffer to the first byte after the decoded data.
 * @param[in]      p_field          Pointer to the output location.
 * @param[in]      fp_field_decoder Pointer to the function that implements field decoding.
 *
 * @return NRF_SUCCESS              Field decoded successfully.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_NULL           p_field or fp_field_decoder is NULL.
 */
static inline uint32_t field_dec(uint8_t const * const   p_buf,
                                 uint32_t                buf_len,
                                 uint32_t * const        p_index,
                                 void * const            p_field,
                                 field_decoder_handler_t fp_field_decoder)
{
    SER_ASSERT_NOT_NULL(fp_field_decoder);
    SER_ASSERT_NOT_NULL(p_field);

    return fp_field_decoder(p_buf, buf_len, p_index, p_field);
}

/**@brief Function for safe decoding of an event-specific field that contains extended data.
 *
 * Some event structures contain a variable length array (extended data),
 * that may be written next to the event structure.
 *
 * @param[in]      p_buf            Pointer to the beginning of the input buffer.
 * @param[in]      buf_len          Size of the buffer.
 * @param[in,out]  p_index          \c in: Index to the start of uint8 value in the buffer.
 *                                  \c out: Index in the buffer to the first byte after the decoded data.
 * @param[in,out]  p_ext_length     \c in: Maximum size of extended data.
 *                                  \c out: Extended data length in bytes.
 * @param[in]      p_field          Pointer to output location.
 * @param[in]      fp_field_decoder Pointer to the function that implements field decoding.
 *
 * @return NRF_SUCCESS              Field decoded successfully.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_NULL           p_field or fp_field_decoder is NULL.
 */
static inline uint32_t field_ext_dec(uint8_t const * const        p_buf,
                                     uint32_t                     buf_len,
                                     uint32_t * const             p_index,
                                     uint32_t * const             p_ext_length,
                                     void * const                 p_field,
                                     field_ext_decoder_handler_t  fp_field_decoder)
{
    SER_ASSERT_NOT_NULL(fp_field_decoder);
    SER_ASSERT_NOT_NULL(p_field);

    return fp_field_decoder(p_buf, buf_len, p_index, p_ext_length, p_field);
}

/**@brief Function for safe encoding an uint16 value.
 *
 * Safe decoding of a uint16 value. Range checks will be done if @ref SER_ASSERTS_ENABLED is set.
 *
 * @param[in]      p_field          A uint16 value to be encoded.
 * @param[out]     p_buf            Buffer containing the value.
 * @param[in]      buf_len          Size of the buffer.
 * @param[in,out]  p_index          \c in: Index to the start of the uint16 value in the buffer.
 *                                  \c out: Index in the buffer to the first byte after the decoded value.
 *
 * @return NRF_SUCCESS              Fields decoded successfully.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t uint16_t_enc(const void * const p_field,
                      uint8_t * const    p_buf,
                      uint32_t           buf_len,
                      uint32_t * const   p_index);

/**@brief Function for safe decoding of a uint16 value.
 *
 * Safe decoding of a uint16 value. Range checks will be done if @ref SER_ASSERTS_ENABLED is set.
 *
 * @param[in]      p_buf            Buffer containing the value.
 * @param[in]      buf_len          Size of the buffer.
 * @param[in,out]  p_index          \c in: Index to the start of the uint16 value in the buffer.
 *                                  \c out: Index in the buffer to the first byte after the decoded value.
 * @param[out]     p_field          Pointer to the location where the uint16 value will be decoded.
 */
uint32_t uint16_t_dec(uint8_t const * const p_buf,
                      uint32_t              buf_len,
                      uint32_t * const      p_index,
                      void *                p_field);

/**@brief Function for safe decoding of a uint16 value.
 *
 * Safe decoding of a uint16 value. Range checks will be done if @ref SER_ASSERTS_ENABLED is set.
 *
 * @param[in]      p_buf            Buffer containing the value.
 * @param[in]      buf_len          Size of the buffer.
 * @param[in,out]  index            \c in: Index to the start of the uint16 value in buffer.
 *                                  \c out: Index in the buffer to the first byte after the decoded value.
 * @param[out]     value            Decoded uint16 value.
 */
void uint16_dec(uint8_t const * const p_buf,
                uint32_t              packet_len,
                uint32_t * const      index,
                uint16_t * const      value);

/**@brief Function for safe encoding of a uint18 value.
 *
 * Safe decoding of a uint8 value. Range checks will be done if @ref SER_ASSERTS_ENABLED is set.
 *
 * @param[in]      p_buf            Buffer containing the value.
 * @param[in]      buf_len          Size of the buffer.
 * @param[in,out]  p_index            \c in: Index to the start of the uint8 value in the buffer.
 *                                  \c out: Index in the buffer to the first byte after the decoded value.
 * @param[out]     p_field          Pointer to uint8 value to be encoded.
 *
 * @return NRF_SUCCESS              Fields decoded successfully.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t uint8_t_enc(const void * const p_field,
                     uint8_t * const    p_buf,
                     uint32_t           buf_len,
                     uint32_t * const   p_index);

/**@brief Function for safe decoding of a uint8 value.
 *
 * Safe decoding of a uint8 value. Range checks will be done if @ref SER_ASSERTS_ENABLED is set.
 *
 * @param[in]      p_buf            Buffer containing the value.
 * @param[in]      buf_len          Size of the buffer.
 * @param[in,out]  p_index          \c in: Index to the start of the uint8 value in buffer.
 *                                  \c out: Index in the buffer to the first byte after the decoded value.
 * @param[out]     p_field          Pointer to the location for decoded uint8 value.
 *
 * @return NRF_SUCCESS              Fields decoded successfully.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t uint8_t_dec(uint8_t const * const p_buf,
                     uint32_t              buf_len,
                     uint32_t * const      p_index,
                     void *                p_field);

/**@brief Function for safe decoding of a uint8 value.
 *
 * Safe decoding of a uint8 value. Range checks will be done if @ref SER_ASSERTS_ENABLED is set.
 *
 * @param[in]      p_buf            Buffer containing the value.
 * @param[in]      buf_len          Size of the buffer.
 * @param[in,out]  index            \c in: Index to the start of the uint8 value in the buffer.
 *                                  \c out: Index in the buffer to the first byte after the decoded value.
 * @param[out]     value            Decoded uint8 value.
 */
void uint8_dec(uint8_t const * const p_buf,
               uint32_t              packet_len,
               uint32_t * const      index,
               uint8_t * const       value);

/**@brief Function for safe decoding of a uint18 value.
 *
 * Safe decoding of a uint8 value. Range checks will be done if @ref SER_ASSERTS_ENABLED is set.
 *
 * @param[in]      p_buf            Buffer containing the value.
 * @param[in]      buf_len          Size of the buffer.
 * @param[in,out]  index            \c in: Index to the start of the uint8 value in the buffer.
 *                                  \c out: Index in the buffer to the first byte after the decoded value.
 * @param[out]     value            Decoded uint8 value.
 */
void int8_dec(uint8_t const * const p_buf,
              uint32_t              packet_len,
              uint32_t * const      index,
              int8_t * const        value);

/**@brief Function for safe encoding of a variable length field encoded as length(8bit) + data.
 *
 * Safe encoding of a variable length field. Range checks will be done if @ref SER_ASSERTS_ENABLED is set.
 *
 * @param[out]     p_data           Pointer to data to encode.
 * @param[in]      dlen             Length of data to encode (0-255).
 * @param[out]     p_buf            Buffer containing the value.
 * @param[in]      buf_len          Size of the buffer.
 * @param[in,out]  p_index          \c in: Index to the start of the uint8 value in the buffer.
 *                                  \c out: Index in the buffer to the first byte after the decoded value.
 *
 * @return NRF_SUCCESS              Fields decoded successfully.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t len8data_enc(uint8_t const * const p_data,
                      uint8_t const         dlen,
                      uint8_t * const       p_buf,
                      uint32_t              buf_len,
                      uint32_t * const      p_index);

/**@brief Function for safe decoding of a variable length field encoded as length(8bit) + data.
 *
 * Safe decoding of a variable length field. Range checks will be done if @ref SER_ASSERTS_ENABLED is set.
 *
 * @param[in]      p_buf            Buffer containing the value.
 * @param[in]      buf_len          Size of the buffer.
 * @param[in,out]  p_index          \c in: Index to the start of the uint8 value in the buffer.
 *                                  \c out: Index in the buffer to the first byte after the decoded value.
 * @param[out]     pp_data          Pointer to decoded data (p_data is set to NULL in
 *                                  case data is not present in the buffer).
 * @param[out]     p_len            Decoded length (0-255).
 *
 * @return NRF_SUCCESS              Fields decoded successfully.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t len8data_dec(uint8_t const * const p_buf,
                      uint32_t              buf_len,
                      uint32_t * const      p_index,
                      uint8_t * * const     pp_data,
                      uint8_t * const       p_len);

/**@brief Function for safe encoding of a variable length field encoded as length(16 bit) + data.
 *
 * Safe encoding of a variable length field. Range checks will be done if @ref SER_ASSERTS_ENABLED is set.
 * It is possible that provided p_data is NULL. In that case, length is encoded and it is followed by
 * SER_FIELD_NOT_PRESENT flag. Otherwise, the SER_FIELD_PRESENT flag precedes the data.
 *
 * @param[in]      p_data           Data to encode.
 * @param[in]      dlen             Input data length (16 bit).
 * @param[in]      p_buf            Pointer to the beginning of the output buffer.
 * @param[in]      buf_len          Size of the buffer.
 * @param[in,out]  p_index          \c in: Index to the start of the uint8 value in the buffer.
 *                                  \c out: Index in the buffer to the first byte after the encoded data.
 *
 * @return NRF_SUCCESS              Fields decoded successfully.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t len16data_enc(uint8_t const * const p_data,
                       uint16_t const        dlen,
                       uint8_t * const       p_buf,
                       uint32_t              buf_len,
                       uint32_t * const      p_index);

/**@brief Function for safe decoding of a variable length field encoded as length(16 bit) + data.
 *
 * Safe decoding of a variable length field. Range checks will be done if @ref SER_ASSERTS_ENABLED is set.
 * Encoded data consists of a length field, a presence flag, and conditional data (present only if the presence flag
 * is set). The p_data pointer cannot be NULL if the presence flag is set.
 *
 * @param[in]      p_buf            Pointer to the beginning of the input buffer.
 * @param[in]      buf_len          Size of the buffer.
 * @param[in,out]  p_index          \c in: Index to the start of the uint8 value in the buffer.
 *                                  \c out: Index in the buffer to the first byte after the decoded data.
 * @param[in]      pp_data          Pointer to decoded data.
 * @param[in]      p_dlen           Data length (16 bit).
 *
 * @return NRF_SUCCESS              Fields decoded successfully.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t len16data_dec(uint8_t const * const p_buf,
                       uint32_t              buf_len,
                       uint32_t * const      p_index,
                       uint8_t * * const     pp_data,
                       uint16_t * const      p_dlen);


/**@brief Function for safe encoding of a uint16 table with a given element count.
 *
 * Safe encoding of a variable length field. Range checks will be done if @ref SER_ASSERTS_ENABLED is set.
 * It is possible that the provided p_data is NULL. In that case, length is encoded and it is followed by a
 * SER_FIELD_NOT_PRESENT flag. Otherwise, the SER_FIELD_PRESENT flag precedes the data.
 *
 * @param[in]      p_data           Data table to encode.
 * @param[in]      count            Table element count.
 * @param[in]      p_buf            Pointer to the beginning of the output buffer.
 * @param[in]      buf_len          Size of the buffer.
 * @param[in,out]  p_index          \c in: Index to the start of the uint8 value in the buffer.
 *                                  \c out: Index in the buffer to the first byte after the encoded data.
 *
 * @return NRF_SUCCESS              Fields decoded successfully.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */

uint32_t count16_cond_data16_enc(uint16_t const * const p_data,
                                 uint16_t const         count,
                                 uint8_t * const        p_buf,
                                 uint32_t               buf_len,
                                 uint32_t * const       p_index);

/**@brief Function for safe decoding of a uint16 table with a given element count.
 *
 * Safe encoding of a variable length field. Range checks will be done if @ref SER_ASSERTS_ENABLED is set.
 * It is possible that the provided p_data is NULL. In that case, length is encoded and it is followed by a
 * SER_FIELD_NOT_PRESENT flag. Otherwise, the SER_FIELD_PRESENT flag precedes the data.
 *
 * @param[in]      p_buf            Pointer to the beginning of the output buffer.
 * @param[in]      buf_len          Size of the buffer.
 * @param[in,out]  p_index          \c in: Index to the start of the uint8 value in the buffer.
 *                                  \c out: Index in the buffer to the first byte after the encoded data.
 * @param[in]      pp_data          Pointer to the table to encode.
 * @param[in,out]  p_count          Pointer to table element count - initialised with max count.
 *
 * @return NRF_SUCCESS              Fields decoded successfully.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Initial count is smaller than actual.
 */

uint32_t count16_cond_data16_dec(uint8_t const * const p_buf,
                                 uint32_t              buf_len,
                                 uint32_t * const      p_index,
                                 uint16_t * * const    pp_data,
                                 uint16_t * const      p_count);


/**@brief Function for safe decoding of a variable length field encoded as length(16 bit) + data.
 *
 * Safe decoding of a variable length field. Range checks will be done if @ref SER_ASSERTS_ENABLED is set.
 * Encoded data consists of a presence flag, an optional length field, a second presence flag, and optional data.
 *
 *
 * @param[in]      p_buf            Pointer to the beginning of the input buffer.
 * @param[in]      buf_len          Size of the buffer.
 * @param[in,out]  p_index          \c in: Index to the start of the uint8 value in the buffer.
 *                                  \c out: Index in the buffer to the first byte after the decoded data.
 * @param[out]     pp_data          Pointer to decoded data.
 * @param[out]     pp_len           Data length (16 bit).
 *
 * @return NRF_SUCCESS              Fields decoded successfully.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */

uint32_t cond_len16_cond_data_dec(uint8_t const * const p_buf,
                                  uint32_t              buf_len,
                                  uint32_t * const      p_index,
                                  uint8_t * * const     pp_data,
                                  uint16_t * * const    pp_len);

/**@brief Command response encoder - replacement of ser_ble_cmd_rsp_status_code_enc
 * with layout aligned to the rest of encoder functions.
 *
 * @param[in]      op_code          Operation code - see BLE_GAP_SVCS.
 * @param[in]      return_code      nRF error code.
 * @param[in]      p_buff           Pointer to the start of pointer to decoded data.
 * @param[in,out]  p_buff_len       \c in: Size of the buffer.
 *                                  \c out: Used bytes in the buffer.
 * @param[in,out]  p_buff_len       \c in: Initial offset in the buffer.
 *                                  \c out: Final offset in the buffer.
 *
 * @return NRF_SUCCESS              Fields decoded successfully.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_NULL           Invalid pointer.
 */
uint32_t op_status_enc(uint8_t          op_code,
                       uint32_t         return_code,
                       uint8_t * const  p_buff,
                       uint32_t * const p_buff_len,
                       uint32_t * const p_index);

/**@brief Command response encoder with a conditional 16-bit field.
 *
 * @param[in]      op_code          Operation code - see BLE_GAP_SVCS.
 * @param[in]      return_code      nRF error code.
 * @param[in]      value            Optional 16-bit field encoded for return code == NRF_SUCCESS.
 * @param[in]      p_buff           Pointer to the start of pointer to decoded data.
 * @param[in,out]  p_buff_len       \c in: Size of the buffer.
 *                                  \c out: Used bytes in the buffer.
 * @param[in,out]  p_buff_len       \c in: Initial offset in the buffer.
 *                                  \c out: Final offset in the buffer.
 *
 * @return NRF_SUCCESS              Fields decoded successfully.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_NULL           Invalid pointer.
 */

uint32_t op_status_cond_uint16_enc(uint8_t          op_code,
                                   uint32_t         return_code,
                                   uint16_t         value,
                                   uint8_t * const  p_buff,
                                   uint32_t * const p_buff_len,
                                   uint32_t * const p_index);

/**@brief Function for safe encoding of a buffer of known size.
 *
 * Safe encoding of a buffer. Encoder assumes that the size is known to the decoder and it is not
 * encoded here. Range checks will be done if @ref SER_ASSERTS_ENABLED is set.
 *
 * @param[in]      p_data           Data to encode.
 * @param[in]      dlen             Input data length (16 bit).
 * @param[in]      p_buf            Pointer to the beginning of the output buffer.
 * @param[in]      buf_len          Size of the buffer.
 * @param[in,out]  p_index          \c in: Index to the start of the uint8 value in the buffer.
 *                                  \c out: Index in the buffer to the first byte after the encoded data.
 *
 * @return NRF_SUCCESS              Fields decoded successfully.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t buf_enc(uint8_t const * const p_data,
                 uint16_t const        dlen,
                 uint8_t * const       p_buf,
                 uint32_t              buf_len,
                 uint32_t * const      p_index);

/**@brief Function for safe decoding of a buffer of known size.
 *
 * Safe decoding of a buffer of known size. Range checks will be done if @ref SER_ASSERTS_ENABLED is set.
 * Encoded data consists of a presence flag and conditional data (present only if the presence flag
 * is set). The p_data pointer cannot be NULL only if the presence flag is set. Length is provided
 * as input to the function.
 *
 * @param[in]      p_buf            Pointer to the beginning of the input buffer.
 * @param[in]      buf_len          Size of the buffer.
 * @param[in,out]  p_index          \c in: Index to the start of the uint8 value in the buffer.
 *                                  \c out: Index in the buffer to the first byte after the decoded data.
 * @param[in]      pp_data          Pointer to decoded data.
 * @param[in]      data_len         Length of the buffer for decoded data (16 bit).
 * @param[in]      dlen             Length of the data to decode (16 bit).
 *
 * @return NRF_SUCCESS              Fields decoded successfully.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t buf_dec(uint8_t const * const p_buf,
                 uint32_t              buf_len,
                 uint32_t * const      p_index,
                 uint8_t * * const     pp_data,
                 uint16_t              data_len,
                 uint16_t              dlen);

/**@brief Function for safe encoding of a uint32 value.
 *
 * Safe decoding of a uint32 value. Range checks will be done if @ref SER_ASSERTS_ENABLED is set.
 *
 * @param[in]      p_field          A uint32 value to be encoded.
 * @param[out]     p_buf            Buffer containing the value.
 * @param[in]      buf_len          Size of the buffer.
 * @param[in,out]  p_index          \c in: Index to the start of the uint32 value in the buffer.
 *                                  \c out: Index in the buffer to the first byte after the decoded value.
 *
 * @return NRF_SUCCESS              Fields decoded successfully.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t uint32_t_enc(void const * const p_field,
                      uint8_t * const    p_buf,
                      uint32_t           buf_len,
                      uint32_t * const   p_index);

/**@brief Function for safe decoding of a uint32 value.
 *
 * Safe decoding of a uint32 value. Range checks will be done if @ref SER_ASSERTS_ENABLED is set.
 *
 * @param[in]      p_buf            Buffer containing the value.
 * @param[in]      buf_len          Size of the buffer.
 * @param[in,out]  p_index          \c in: Index to the start of the uint32 value in the buffer.
 *                                  \c out: Index in the buffer to the first byte after the decoded value.
 * @param[out]     value            Decoded uint32 value.
 */
uint32_t uint32_t_dec(uint8_t const * const p_buf,
                      uint32_t              buf_len,
                      uint32_t * const      p_index,
                      void *                p_field);

/**@brief Function for safe encoding of a uint8 vector.
 *
 * Range checks will be done if @ref SER_ASSERTS_ENABLED is set.
 * *
 * @param[in]      p_data           Data to encode.
 * @param[in]      dlen             Input data length (16 bit).
 * @param[in]      p_buf            Pointer to the beginning of the output buffer.
 * @param[in]      buf_len          Size of the buffer.
 * @param[in,out]  p_index          \c in: Index to the start of the uint8 value in the buffer.
 *                                  \c out: Index in the buffer to the first byte after the encoded data.
 *
 * @return NRF_SUCCESS              Fields decoded successfully.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t uint8_vector_enc(uint8_t const * const p_data,
                          uint16_t const        dlen,
                          uint8_t * const       p_buf,
                          uint32_t              buf_len,
                          uint32_t * const      p_index);

/**@brief Function for safe decoding a uint8 vector.
 *
 * Safe decoding of a buffer of known size. Range checks will be done if @ref SER_ASSERTS_ENABLED is set.
 * Vector length is provided as input to the function.
 *
 * @param[in]      p_buf            Pointer to the beginning of the input buffer.
 * @param[in]      buf_len          Size of the buffer.
 * @param[in,out]  p_index          \c in: Index to the start of the uint8 value in the buffer.
 *                                  \c out: Index in the buffer to the first byte after the decoded data.
 * @param[in]      p_data           Pointer to decoded data.
 * @param[in]      dlen             Length of data to decode (16 bit).
 *
 * @return NRF_SUCCESS              Fields decoded successfully.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t uint8_vector_dec(uint8_t const * const p_buf,
                 uint32_t              buf_len,
                 uint32_t * const      p_index,
                 uint8_t  * const      p_data,
                 uint16_t              dlen);


#ifdef __cplusplus
}
#endif

#endif


