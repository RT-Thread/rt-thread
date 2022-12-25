/**
  ******************************************************************************
  * @file    ring_buffer.h
  * @version V1.0
  * @date
  * @brief   This file is the common component header file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__

#include "bflb_bsp_driver_glue.h"

/** @addtogroup  BL_Common_Component
 *  @{
 */

/** @addtogroup  RING_BUFFER
 *  @{
 */

/** @defgroup  RING_BUFFER_Public_Types
 *  @{
 */

/**
 *  @brief Ring buffer status type definition
 */
typedef enum {
    RING_BUFFER_EMPTY,                       /*!< Ring buffer is empty */
    RING_BUFFER_PARTIAL,                     /*!< Ring buffer has partial data */
    RING_BUFFER_FULL,                        /*!< Ring buffer is full */
}Ring_Buffer_Status_Type;

/**
 *  @brief Ring buffer structure definition
 */
typedef struct {
    uint8_t* pointer;                        /*!< Pointer of ring buffer */
    uint8_t readMirror;                      /*!< Read mirror,used to judge empty or full */
    uint32_t readIndex;                      /*!< Index of read address */
    uint8_t writeMirror;                     /*!< Write mirror,used to judge empty or full */
    uint32_t writeIndex;                     /*!< Index of write address */
    uint32_t size;                           /*!< Size of ring buffer */
    void (*lock)(void);                      /*!< Lock ring buffer */
    void (*unlock)(void);                    /*!< Unlock ring buffer */
}Ring_Buffer_Type;

/*@} end of group RING_BUFFER_Public_Types */

/** @defgroup  RING_BUFFER_Public_Constants
 *  @{
 */

/** @defgroup  RING_BUFFER_STATUS_TYPE
 *  @{
 */
#define IS_RING_BUFFER_STATUS_TYPE(type)                 (((type) == RING_BUFFER_EMPTY) || \
                                                          ((type) == RING_BUFFER_PARTIAL) || \
                                                          ((type) == RING_BUFFER_FULL))

/*@} end of group RING_BUFFER_Public_Constants */

/** @defgroup  RING_BUFFER_Public_Macros
 *  @{
 */
typedef void (ringBuffer_Lock_Callback)(void);
typedef void (ringBuffer_Read_Callback)(void*,uint8_t*,uint32_t);
typedef void (ringBuffer_Write_Callback)(void*,uint8_t*,uint32_t);

/*@} end of group RING_BUFFER_Public_Macros */

/** @defgroup  RING_BUFFER_Public_Functions
 *  @{
 */
BL_Err_Type Ring_Buffer_Init(Ring_Buffer_Type* rbType,uint8_t* buffer,uint32_t size,ringBuffer_Lock_Callback* lockCb,
                             ringBuffer_Lock_Callback* unlockCb);
BL_Err_Type Ring_Buffer_Reset(Ring_Buffer_Type* rbType);
uint32_t Ring_Buffer_Write_Callback(Ring_Buffer_Type* rbType,uint32_t length,ringBuffer_Write_Callback* writeCb,
                                    void* parameter);
uint32_t Ring_Buffer_Write(Ring_Buffer_Type* rbType,const uint8_t* data,uint32_t length);
uint32_t Ring_Buffer_Write_Byte(Ring_Buffer_Type* rbType,const uint8_t data);
uint32_t Ring_Buffer_Write_Force(Ring_Buffer_Type* rbType,const uint8_t* data,uint32_t length);
uint32_t Ring_Buffer_Write_Byte_Force(Ring_Buffer_Type* rbType,const uint8_t data);
uint32_t Ring_Buffer_Read_Callback(Ring_Buffer_Type* rbType,uint32_t length,ringBuffer_Read_Callback* readCb,
                                   void* parameter);
uint32_t Ring_Buffer_Read(Ring_Buffer_Type* rbType,uint8_t* data,uint32_t length);
uint32_t Ring_Buffer_Read_Byte(Ring_Buffer_Type* rbType,uint8_t* data);
uint32_t Ring_Buffer_Peek(Ring_Buffer_Type* rbType,uint8_t* data,uint32_t length);
uint32_t Ring_Buffer_Peek_Byte(Ring_Buffer_Type* rbType,uint8_t* data);
uint32_t Ring_Buffer_Get_Length(Ring_Buffer_Type* rbType);
uint32_t Ring_Buffer_Get_Empty_Length(Ring_Buffer_Type* rbType);
Ring_Buffer_Status_Type Ring_Buffer_Get_Status(Ring_Buffer_Type* rbType);

/*@} end of group RING_BUFFER_Public_Functions */

/*@} end of group RING_BUFFER */

/*@} end of group BL_Common_Component */

#endif /* __RING_BUFFER_H__ */
