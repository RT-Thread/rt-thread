/**
  ******************************************************************************
  * @file    bl808_usb.h
  * @version V1.0
  * @date
  * @brief   This file is the standard driver header file
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
#ifndef __BL808_USB_H__
#define __BL808_USB_H__

#include "usb_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  USB
 *  @{
 */

/** @defgroup  USB_Public_Types
 *  @{
 */

/**
 *  @brief USB LPM response type definition
 */
typedef enum {
    USB_LPM_RESP_NYET = 0, /*!< response LPM with NYET */
    USB_LPM_RESP_ACK = 1,  /*!< response LPM with ACK */
} USB_LPM_RESP_Type;

/**
 *  @brief USB LPM configuration structure type definition
 */
typedef struct
{
    uint8_t lpmEn;          /*!< response LPM or not */
    USB_LPM_RESP_Type resp; /*!< response LPM with ACK or NAK */
    uint8_t minBesl;        /*!< BESL min value */
    uint8_t maxBesl;        /*!< BESL max value */
    uint8_t lpmWakeUpEn;    /*!< LPM wakeup enable */
} USB_LPM_Cfg_Type;

/**
 *  @brief USB global interrupt type definition
 */
typedef enum {
    USB_GLOBAL_INT_DEV = 0, /*!< USB device interrupt type */
    USB_GLOBAL_INT_OTG = 1, /*!< USB OTG interrupt type */
    USB_GLOBAL_INT_HC = 2,  /*!< USB host interrupt type */
} USB_GLOBAL_INT_Type;

/**
 *  @brief USB global interrupt type definition
 */
typedef enum {
    USB_DEVICE_SPEED_FULL_SPEED = 0, /*!< USB device interrupt type */
    USB_DEVICE_SPEED_HIGH_SPEED = 1, /*!< USB OTG interrupt type */
} USB_DEVICE_SPEED_Type;

/**
 *  @brief USB normal configuration structure type definition
 */
typedef struct
{
    uint8_t forceFullSpeed; /*!< force device to full speed */
    uint8_t chipEn;         /*!< chip enable */
    uint8_t swRst;          /*!< software reset */
    uint8_t remoteWakeupEn; /*!< remote wakeup capability enable */
    uint32_t rstTimeOut;    /*!< software reset timeout count */
} USB_NORMAL_Cfg_Type;

/**
 *  @brief USB FIFO empty type definition
 */
typedef enum {
    USB_FIFO_EMPTY_FIFO_0 = 8,  /*!< USB FIFO 0 empty type */
    USB_FIFO_EMPTY_FIFO_1 = 9,  /*!< USB FIFO 1 empty type */
    USB_FIFO_EMPTY_FIFO_2 = 10, /*!< USB FIFO 2 empty type */
    USB_FIFO_EMPTY_FIFO_3 = 11, /*!< USB FIFO 3 empty type */
} USB_FIFO_EMPTY_Type;

/**
 *  @brief USB endpoint ID type definition
 */
typedef enum {
    USB_Endpoint_0 = 0, /*!< USB endpoint ID 0 */
    USB_Endpoint_1 = 1, /*!< USB endpoint ID 1 */
    USB_Endpoint_2 = 2, /*!< USB endpoint ID 2 */
    USB_Endpoint_3 = 3, /*!< USB endpoint ID 3 */
    USB_Endpoint_4 = 4, /*!< USB endpoint ID 4 */
    USB_Endpoint_5 = 5, /*!< USB endpoint ID 5 */
    USB_Endpoint_6 = 6, /*!< USB endpoint ID 6 */
    USB_Endpoint_7 = 7, /*!< USB endpoint ID 7 */
    USB_Endpoint_8 = 8, /*!< USB endpoint ID 8 */
} USB_Endpoint_Type;

/**
 *  @brief USB FIFO ID type definition
 */
typedef enum {
    USB_FIFO_0 = 0, /*!< USB endpoint ID 0 */
    USB_FIFO_1 = 1, /*!< USB endpoint ID 1 */
    USB_FIFO_2 = 2, /*!< USB endpoint ID 2 */
    USB_FIFO_3 = 3, /*!< USB endpoint ID 3 */
} USB_FIFO_Type;

/**
 *  @brief USB FIFO direction type definition
 */
typedef enum {
    USB_FIFO_DIR_OUT = 0, /*!< USB FIFO direction out */
    USB_FIFO_DIR_IN = 1,  /*!< USB FIFO direction in */
    USB_FIFO_DIR_BID = 2, /*!< USB FIFO direction bidirectional */
} USB_FIFO_DIR_Type;

/**
 *  @brief USB FIFO block max size type definition
 */
typedef enum {
    USB_FIFO_BLOCK_MAX_SIZE_512 = 0,  /*!< USB FIFO block max packet size 512 */
    USB_FIFO_BLOCK_MAX_SIZE_1024 = 1, /*!< USB FIFO block max packet size 1024 */
} USB_FIFO_BLOCK_MAX_SIZE_Type;

/**
 *  @brief USB FIFO block count type definition
 */
typedef enum {
    USB_FIFO_BLOCK_CNT_SINGLE_BLOCK = 0,  /*!< USB FIFO single block */
    USB_FIFO_BLOCK_CNT_DOUBLE_BLOCKS = 1, /*!< USB FIFO double block */
    USB_FIFO_BLOCK_CNT_TRIPLE_BLOCKS = 2, /*!< USB FIFO triple block */
} USB_FIFO_BLOCK_CNT_Type;

/**
 *  @brief USB FIFO transfer type definition
 */
typedef enum {
    USB_FIFO_TRANSFER_RSV = 0,  /*!< USB FIFO transfer type is reserved */
    USB_FIFO_TRANSFER_ISO = 1,  /*!< USB FIFO transfer type is isochronous */
    USB_FIFO_TRANSFER_BULK = 2, /*!< USB FIFO transfer type is bulk */
    USB_FIFO_TRANSFER_INT = 3,  /*!< USB FIFO transfer type is interrupt */
} USB_FIFO_TRANSFER_Type;

/**
 *  @brief USB FIFO configuration structure type definition
 */
typedef struct
{
    uint8_t enable;                         /*!< FIFO enable or disable */
    USB_FIFO_DIR_Type dir;                  /*!< FIFO direction */
    USB_Endpoint_Type epID;                 /*!< Endpoint number of FIFO */
    USB_FIFO_BLOCK_MAX_SIZE_Type blockSize; /*!< FIFO block max size */
    USB_FIFO_BLOCK_CNT_Type blockType;      /*!< FIFO block type */
    USB_FIFO_TRANSFER_Type fifoType;        /*!< FIFO transfer type */
} USB_FIFO_Cfg_Type;

/**
 *  @brief USB DMA target FIFO type definition
 */
typedef enum {
    USB_DMA_TARGET_FIFO_CTRL = 0, /*!< USB DMA target FIFO is control FIFO */
    USB_DMA_TARGET_FIFO_0 = 1,    /*!< USB DMA target FIFO is FIFO 0 */
    USB_DMA_TARGET_FIFO_1 = 2,    /*!< USB DMA target FIFO is FIFO 1 */
    USB_DMA_TARGET_FIFO_2 = 3,    /*!< USB DMA target FIFO is FIFO 2 */
    USB_DMA_TARGET_FIFO_3 = 4,    /*!< USB DMA target FIFO is FIFO 3 */
} USB_DMA_TARGET_FIFO_Type;

/**
 *  @brief USB DMA transfer type definition
 */
typedef enum {
    USB_DMA_TRANS_DIR_FIFO_2_MEM = 0,  /*!< USB DMA transfer type is FIFO to memory */
    USB_DMA_TRANS_DIR_MEM_2_FIFO = 1,  /*!< USB DMA transfer type is memory to FIFO */
    USB_DMA_TRANS_DIR_FIFO_2_FIFO = 2, /*!< USB DMA transfer type is FIFO to FIFO */
} USB_DMA_TRANS_DIR_Type;

/**
 *  @brief USB DMA configuration structure type definition
 */
typedef struct
{
    USB_DMA_TRANS_DIR_Type dir; /*!< USB DMA transfer direction */
    uint32_t memAddr;           /*!< USB DMA target memory address */
    uint32_t length;            /*!< USB DMA transfer length */
} USB_DMA_Cfg_Type;

/**
 *  @brief USB Virtual DMA target FIFO type definition
 */
typedef enum {
    USB_VDMA_TARGET_FIFO_CTRL = 0, /*!< USB VDMA target FIFO is control FIFO */
    USB_VDMA_TARGET_FIFO_0 = 1,    /*!< USB VDMA target FIFO is FIFO 0 */
    USB_VDMA_TARGET_FIFO_1 = 2,    /*!< USB VDMA target FIFO is FIFO 1 */
    USB_VDMA_TARGET_FIFO_2 = 3,    /*!< USB VDMA target FIFO is FIFO 2 */
    USB_VDMA_TARGET_FIFO_3 = 4,    /*!< USB VDMA target FIFO is FIFO 3 */
} USB_VDMA_TARGET_FIFO_Type;

/**
 *  @brief USB Virtual DMA transfer type definition
 */
typedef enum {
    USB_VDMA_TRANS_DIR_FIFO_2_MEM = 0,  /*!< USB VDMA transfer type is FIFO to memory */
    USB_VDMA_TRANS_DIR_MEM_2_FIFO = 1,  /*!< USB VDMA transfer type is memory to FIFO */
    USB_VDMA_TRANS_DIR_FIFO_2_FIFO = 2, /*!< USB VDMA transfer type is FIFO to FIFO */
} USB_VDMA_TRANS_DIR_Type;

/**
 *  @brief USB Virtual DMA configuration structure type definition
 */
typedef struct
{
    USB_VDMA_TRANS_DIR_Type dir; /*!< USB VDMA transfer direction */
    uint32_t memAddr;            /*!< USB VDMA target memory address */
    uint32_t length;             /*!< USB VDMA transfer length */
} USB_VDMA_Cfg_Type;

/**
 *  @brief USB interrupt group type definition
 */
typedef enum {
    USB_GRP_INT_G0 = 0, /*!< USB group 0 interrupt type */
    USB_GRP_INT_G1 = 1, /*!< USB group 1 interrupt type */
    USB_GRP_INT_G2 = 2, /*!< USB group 2 interrupt type */
    USB_GRP_INT_G3 = 3, /*!< USB group 3 interrupt type */
    USB_GRP_INT_G4 = 4, /*!< USB group 4 interrupt type */
} USB_GRP_INT_Type;

/**
 *  @brief USB interrupt group0 type definition
 */
typedef enum {
    USB_SUB_GRP0_INT_CX_SETUP = 0,        /*!< group0 endpoint 0 setup data received */
    USB_SUB_GRP0_INT_CX_IN = 1,           /*!< group0 endpoint 0 IN */
    USB_SUB_GRP0_INT_CX_OUT = 2,          /*!< group0 endpoint 0 OUT */
    USB_SUB_GRP0_INT_CX_COMFAIL = 3,      /*!< group0 endpoint 0 COMFAIL */
    USB_SUB_GRP0_INT_CX_COMABORT = 4,     /*!< group0 endpoint 0 COMABORT */
    USB_SUB_GRP1_INT_F0_OUT = 5,          /*!< group1 OUT interrupt of FIFO 0 */
    USB_SUB_GRP1_INT_F0_SPK = 6,          /*!< group1 short packet interrupt of FIFO 0 */
    USB_SUB_GRP1_INT_F1_OUT = 7,          /*!< group1 OUT interrupt of FIFO 1 */
    USB_SUB_GRP1_INT_F1_SPK = 8,          /*!< group1 short packet interrupt of FIFO 1 */
    USB_SUB_GRP1_INT_F2_OUT = 9,          /*!< group1 OUT interrupt of FIFO 2 */
    USB_SUB_GRP1_INT_F2_SPK = 10,         /*!< group1 short packet interrupt of FIFO 2 */
    USB_SUB_GRP1_INT_F3_OUT = 11,         /*!< group1 OUT interrupt of FIFO 3 */
    USB_SUB_GRP1_INT_F3_SPK = 12,         /*!< group1 short packet interrupt of FIFO 3 */
    USB_SUB_GRP1_INT_F0_IN = 13,          /*!< group1 IN interrupt of FIFO 0 */
    USB_SUB_GRP1_INT_F1_IN = 14,          /*!< group1 IN interrupt of FIFO 1 */
    USB_SUB_GRP1_INT_F2_IN = 15,          /*!< group1 IN interrupt of FIFO 2 */
    USB_SUB_GRP1_INT_F3_IN = 16,          /*!< group1 IN interrupt of FIFO 3 */
    USB_SUB_GRP2_INT_RESET = 17,          /*!< group2 USB reset interrupt */
    USB_SUB_GRP2_INT_SUSPEND = 18,        /*!< group2 suspend interrupt */
    USB_SUB_GRP2_INT_RESUME = 19,         /*!< group2 resume interrupt */
    USB_SUB_GRP2_INT_TX0BYTE = 20,        /*!< group2 transferred zero-length data packet interrupt */
    USB_SUB_GRP2_INT_RX0BYTE = 21,        /*!< group2 received zero-length data packet interrupt */
    USB_SUB_GRP2_INT_DMA_CMPLT = 22,      /*!< group2 DMA completion interrupt */
    USB_SUB_GRP2_INT_DMA_ERROR = 23,      /*!< group2 DMA error interrupt */
    USB_SUB_GRP2_INT_IDLE = 24,           /*!< group2 dev_idle interrupt */
    USB_SUB_GRP2_INT_WAKEUP_BY_VBUS = 25, /*!< group2 dev_wakeup_byVBUS interrupt */
    USB_SUB_GRP3_INT_VDMA_CMPLT_CXF = 26, /*!< group3 Virtual DMA completion interrupt for FIFO CXF */
    USB_SUB_GRP3_INT_VDMA_CMPLT_F0 = 27,  /*!< group3 Virtual DMA completion interrupt for FIFO 0 */
    USB_SUB_GRP3_INT_VDMA_CMPLT_F1 = 28,  /*!< group3 Virtual DMA completion interrupt for FIFO 1 */
    USB_SUB_GRP3_INT_VDMA_CMPLT_F2 = 29,  /*!< group3 Virtual DMA completion interrupt for FIFO 2 */
    USB_SUB_GRP3_INT_VDMA_CMPLT_F3 = 30,  /*!< group3 Virtual DMA completion interrupt for FIFO 3 */
    USB_SUB_GRP3_INT_VDMA_ERROR_CXF = 31, /*!< group3 Virtual DMA error interrupt for FIFO CXF */
    USB_SUB_GRP3_INT_VDMA_ERROR_F0 = 32,  /*!< group3 Virtual DMA error interrupt for FIFO 0 */
    USB_SUB_GRP3_INT_VDMA_ERROR_F1 = 33,  /*!< group3 Virtual DMA error interrupt for FIFO 1 */
    USB_SUB_GRP3_INT_VDMA_ERROR_F2 = 34,  /*!< group3 Virtual DMA error interrupt for FIFO 2 */
    USB_SUB_GRP3_INT_VDMA_ERROR_F3 = 35,  /*!< group3 Virtual DMA error interrupt for FIFO 3 */
    USB_SUB_GRP4_INT_L1 = 36,             /*!< group4 L1-state-change interrupt */
} USB_SUB_GRP_INT_Type;

/*@} end of group USB_Public_Types */

/** @defgroup  USB_Public_Constants
 *  @{
 */

/** @defgroup  USB_LPM_RESP_TYPE
 *  @{
 */
#define IS_USB_LPM_RESP_TYPE(type) (((type) == USB_LPM_RESP_NYET) || \
                                    ((type) == USB_LPM_RESP_ACK))

/** @defgroup  USB_GLOBAL_INT_TYPE
 *  @{
 */
#define IS_USB_GLOBAL_INT_TYPE(type) (((type) == USB_GLOBAL_INT_DEV) || \
                                      ((type) == USB_GLOBAL_INT_OTG) || \
                                      ((type) == USB_GLOBAL_INT_HC))

/** @defgroup  USB_DEVICE_SPEED_TYPE
 *  @{
 */
#define IS_USB_DEVICE_SPEED_TYPE(type) (((type) == USB_DEVICE_SPEED_FULL_SPEED) || \
                                        ((type) == USB_DEVICE_SPEED_HIGH_SPEED))

/** @defgroup  USB_FIFO_EMPTY_TYPE
 *  @{
 */
#define IS_USB_FIFO_EMPTY_TYPE(type) (((type) == USB_FIFO_EMPTY_FIFO_0) || \
                                      ((type) == USB_FIFO_EMPTY_FIFO_1) || \
                                      ((type) == USB_FIFO_EMPTY_FIFO_2) || \
                                      ((type) == USB_FIFO_EMPTY_FIFO_3))

/** @defgroup  USB_ENDPOINT_TYPE
 *  @{
 */
#define IS_USB_ENDPOINT_TYPE(type) (((type) == USB_Endpoint_1) || \
                                    ((type) == USB_Endpoint_2) || \
                                    ((type) == USB_Endpoint_3) || \
                                    ((type) == USB_Endpoint_4) || \
                                    ((type) == USB_Endpoint_5) || \
                                    ((type) == USB_Endpoint_6) || \
                                    ((type) == USB_Endpoint_7) || \
                                    ((type) == USB_Endpoint_8))

/** @defgroup  USB_FIFO_TYPE
 *  @{
 */
#define IS_USB_FIFO_TYPE(type) (((type) == USB_FIFO_0) || \
                                ((type) == USB_FIFO_1) || \
                                ((type) == USB_FIFO_2) || \
                                ((type) == USB_FIFO_3))

/** @defgroup  USB_FIFO_DIR_TYPE
 *  @{
 */
#define IS_USB_FIFO_DIR_TYPE(type) (((type) == USB_FIFO_DIR_OUT) || \
                                    ((type) == USB_FIFO_DIR_IN) ||  \
                                    ((type) == USB_FIFO_DIR_BID))

/** @defgroup  USB_FIFO_BLOCK_MAX_SIZE_TYPE
 *  @{
 */
#define IS_USB_FIFO_BLOCK_MAX_SIZE_TYPE(type) (((type) == USB_FIFO_BLOCK_MAX_SIZE_512) || \
                                               ((type) == USB_FIFO_BLOCK_MAX_SIZE_1024))

/** @defgroup  USB_FIFO_BLOCK_CNT_TYPE
 *  @{
 */
#define IS_USB_FIFO_BLOCK_CNT_TYPE(type) (((type) == USB_FIFO_BLOCK_CNT_SINGLE_BLOCK) ||  \
                                          ((type) == USB_FIFO_BLOCK_CNT_DOUBLE_BLOCKS) || \
                                          ((type) == USB_FIFO_BLOCK_CNT_TRIPLE_BLOCKS))

/** @defgroup  USB_FIFO_TRANSFER_TYPE
 *  @{
 */
#define IS_USB_FIFO_TRANSFER_TYPE(type) (((type) == USB_FIFO_TRANSFER_RSV) ||  \
                                         ((type) == USB_FIFO_TRANSFER_ISO) ||  \
                                         ((type) == USB_FIFO_TRANSFER_BULK) || \
                                         ((type) == USB_FIFO_TRANSFER_INT))

/** @defgroup  USB_DMA_TARGET_FIFO_TYPE
 *  @{
 */
#define IS_USB_DMA_TARGET_FIFO_TYPE(type) (((type) == USB_DMA_TARGET_FIFO_0) || \
                                           ((type) == USB_DMA_TARGET_FIFO_1) || \
                                           ((type) == USB_DMA_TARGET_FIFO_2) || \
                                           ((type) == USB_DMA_TARGET_FIFO_3) || \
                                           ((type) == USB_DMA_TARGET_FIFO_CTRL))

/** @defgroup  USB_DMA_TRANS_DIR_TYPE
 *  @{
 */
#define IS_USB_DMA_TRANS_DIR_TYPE(type) (((type) == USB_DMA_TRANS_DIR_FIFO_2_MEM) || \
                                         ((type) == USB_DMA_TRANS_DIR_MEM_2_FIFO) || \
                                         ((type) == USB_DMA_TRANS_DIR_FIFO_2_FIFO))

/** @defgroup  USB_VDMA_TARGET_FIFO_TYPE
 *  @{
 */
#define IS_USB_VDMA_TARGET_FIFO_TYPE(type) (((type) == USB_VDMA_TARGET_FIFO_0) || \
                                            ((type) == USB_VDMA_TARGET_FIFO_1) || \
                                            ((type) == USB_VDMA_TARGET_FIFO_2) || \
                                            ((type) == USB_VDMA_TARGET_FIFO_3) || \
                                            ((type) == USB_VDMA_TARGET_FIFO_CTRL))

/** @defgroup  USB_VDMA_TRANS_DIR_TYPE
 *  @{
 */
#define IS_USB_VDMA_TRANS_DIR_TYPE(type) (((type) == USB_VDMA_TRANS_DIR_FIFO_2_MEM) || \
                                          ((type) == USB_VDMA_TRANS_DIR_MEM_2_FIFO) || \
                                          ((type) == USB_VDMA_TRANS_DIR_FIFO_2_FIFO))

/** @defgroup  USB_GRP_INT_TYPE
 *  @{
 */
#define IS_USB_GRP_INT_TYPE(type) (((type) == USB_GRP_INT_G0) || \
                                   ((type) == USB_GRP_INT_G1) || \
                                   ((type) == USB_GRP_INT_G2) || \
                                   ((type) == USB_GRP_INT_G3) || \
                                   ((type) == USB_GRP_INT_G4))

/** @defgroup  USB_SUB_GRP_INT_TYPE
 *  @{
 */
#define IS_USB_SUB_GRP_INT_TYPE(type) (((type) == USB_SUB_GRP0_INT_CX_SETUP) ||       \
                                       ((type) == USB_SUB_GRP0_INT_CX_IN) ||          \
                                       ((type) == USB_SUB_GRP0_INT_CX_OUT) ||         \
                                       ((type) == USB_SUB_GRP0_INT_CX_COMFAIL) ||     \
                                       ((type) == USB_SUB_GRP0_INT_CX_COMABORT) ||    \
                                       ((type) == USB_SUB_GRP1_INT_F0_OUT) ||         \
                                       ((type) == USB_SUB_GRP1_INT_F0_SPK) ||         \
                                       ((type) == USB_SUB_GRP1_INT_F1_OUT) ||         \
                                       ((type) == USB_SUB_GRP1_INT_F1_SPK) ||         \
                                       ((type) == USB_SUB_GRP1_INT_F2_OUT) ||         \
                                       ((type) == USB_SUB_GRP1_INT_F2_SPK) ||         \
                                       ((type) == USB_SUB_GRP1_INT_F3_OUT) ||         \
                                       ((type) == USB_SUB_GRP1_INT_F3_SPK) ||         \
                                       ((type) == USB_SUB_GRP1_INT_F0_IN) ||          \
                                       ((type) == USB_SUB_GRP1_INT_F1_IN) ||          \
                                       ((type) == USB_SUB_GRP1_INT_F2_IN) ||          \
                                       ((type) == USB_SUB_GRP1_INT_F3_IN) ||          \
                                       ((type) == USB_SUB_GRP2_INT_RESET) ||          \
                                       ((type) == USB_SUB_GRP2_INT_SUSPEND) ||        \
                                       ((type) == USB_SUB_GRP2_INT_RESUME) ||         \
                                       ((type) == USB_SUB_GRP2_INT_TX0BYTE) ||        \
                                       ((type) == USB_SUB_GRP2_INT_RX0BYTE) ||        \
                                       ((type) == USB_SUB_GRP2_INT_DMA_CMPLT) ||      \
                                       ((type) == USB_SUB_GRP2_INT_DMA_ERROR) ||      \
                                       ((type) == USB_SUB_GRP2_INT_IDLE) ||           \
                                       ((type) == USB_SUB_GRP2_INT_WAKEUP_BY_VBUS) || \
                                       ((type) == USB_SUB_GRP3_INT_VDMA_CMPLT_CXF) || \
                                       ((type) == USB_SUB_GRP3_INT_VDMA_CMPLT_F0) ||  \
                                       ((type) == USB_SUB_GRP3_INT_VDMA_CMPLT_F1) ||  \
                                       ((type) == USB_SUB_GRP3_INT_VDMA_CMPLT_F2) ||  \
                                       ((type) == USB_SUB_GRP3_INT_VDMA_CMPLT_F3) ||  \
                                       ((type) == USB_SUB_GRP3_INT_VDMA_ERROR_CXF) || \
                                       ((type) == USB_SUB_GRP3_INT_VDMA_ERROR_F0) ||  \
                                       ((type) == USB_SUB_GRP3_INT_VDMA_ERROR_F1) ||  \
                                       ((type) == USB_SUB_GRP3_INT_VDMA_ERROR_F2) ||  \
                                       ((type) == USB_SUB_GRP3_INT_VDMA_ERROR_F3) ||  \
                                       ((type) == USB_SUB_GRP4_INT_L1))

/*@} end of group USB_Public_Constants */

/** @defgroup  USB_Public_Macros
 *  @{
 */
#define USB_SUB_GRP0_INT_OFS              (0)
#define USB_SUB_GRP1_INT_OFS              (32)
#define USB_SUB_GRP2_INT_OFS              (64)
#define USB_SUB_GRP3_INT_OFS              (96)
#define USB_SUB_GRP4_INT_OFS              (128)
#define USB_SOF_TIMER_MASK_AFTER_RESET_HS (0x44C)
#define USB_SOF_TIMER_MASK_AFTER_RESET_FS (0x2710)

#define USB_INT_CX_SETUP       (1ULL << USB_SUB_GRP0_INT_CX_SETUP)
#define USB_INT_CX_IN          (1ULL << USB_SUB_GRP0_INT_CX_IN)
#define USB_INT_CX_OUT         (1ULL << USB_SUB_GRP0_INT_CX_OUT)
#define USB_INT_CX_COMFAIL     (1ULL << USB_SUB_GRP0_INT_CX_COMFAIL)
#define USB_INT_CX_COMABORT    (1ULL << USB_SUB_GRP0_INT_CX_COMABORT)
#define USB_INT_F0_OUT         (1ULL << USB_SUB_GRP1_INT_F0_OUT)
#define USB_INT_F0_SPK         (1ULL << USB_SUB_GRP1_INT_F0_SPK)
#define USB_INT_F1_OUT         (1ULL << USB_SUB_GRP1_INT_F1_OUT)
#define USB_INT_F1_SPK         (1ULL << USB_SUB_GRP1_INT_F1_SPK)
#define USB_INT_F2_OUT         (1ULL << USB_SUB_GRP1_INT_F2_OUT)
#define USB_INT_F2_SPK         (1ULL << USB_SUB_GRP1_INT_F2_SPK)
#define USB_INT_F3_OUT         (1ULL << USB_SUB_GRP1_INT_F3_OUT)
#define USB_INT_F3_SPK         (1ULL << USB_SUB_GRP1_INT_F3_SPK)
#define USB_INT_F0_IN          (1ULL << USB_SUB_GRP1_INT_F0_IN)
#define USB_INT_F1_IN          (1ULL << USB_SUB_GRP1_INT_F1_IN)
#define USB_INT_F2_IN          (1ULL << USB_SUB_GRP1_INT_F2_IN)
#define USB_INT_F3_IN          (1ULL << USB_SUB_GRP1_INT_F3_IN)
#define USB_INT_RESET          (1ULL << USB_SUB_GRP2_INT_RESET)
#define USB_INT_SUSPEND        (1ULL << USB_SUB_GRP2_INT_SUSPEND)
#define USB_INT_RESUME         (1ULL << USB_SUB_GRP2_INT_RESUME)
#define USB_INT_TX0BYTE        (1ULL << USB_SUB_GRP2_INT_TX0BYTE)
#define USB_INT_RX0BYTE        (1ULL << USB_SUB_GRP2_INT_RX0BYTE)
#define USB_INT_DMA_CMPLT      (1ULL << USB_SUB_GRP2_INT_DMA_CMPLT)
#define USB_INT_DMA_ERROR      (1ULL << USB_SUB_GRP2_INT_DMA_ERROR)
#define USB_INT_IDLE           (1ULL << USB_SUB_GRP2_INT_IDLE)
#define USB_INT_WAKEUP_BY_VBUS (1ULL << USB_SUB_GRP2_INT_WAKEUP_BY_VBUS)
#define USB_INT_VDMA_CMPLT_CXF (1ULL << USB_SUB_GRP3_INT_VDMA_CMPLT_CXF)
#define USB_INT_VDMA_CMPLT_F0  (1ULL << USB_SUB_GRP3_INT_VDMA_CMPLT_F0)
#define USB_INT_VDMA_CMPLT_F1  (1ULL << USB_SUB_GRP3_INT_VDMA_CMPLT_F1)
#define USB_INT_VDMA_CMPLT_F2  (1ULL << USB_SUB_GRP3_INT_VDMA_CMPLT_F2)
#define USB_INT_VDMA_CMPLT_F3  (1ULL << USB_SUB_GRP3_INT_VDMA_CMPLT_F3)
#define USB_INT_VDMA_ERROR_CXF (1ULL << USB_SUB_GRP3_INT_VDMA_ERROR_CXF)
#define USB_INT_VDMA_ERROR_F0  (1ULL << USB_SUB_GRP3_INT_VDMA_ERROR_F0)
#define USB_INT_VDMA_ERROR_F1  (1ULL << USB_SUB_GRP3_INT_VDMA_ERROR_F1)
#define USB_INT_VDMA_ERROR_F2  (1ULL << USB_SUB_GRP3_INT_VDMA_ERROR_F2)
#define USB_INT_VDMA_ERROR_F3  (1ULL << USB_SUB_GRP3_INT_VDMA_ERROR_F3)
#define USB_INT_L1             (1ULL << USB_SUB_GRP4_INT_L1)

#define USB_SUB_GROUP_0_CX_SETUP_BIT_MUSK       (0x00000001)
#define USB_SUB_GROUP_0_CX_IN_BIT_MUSK          (0x00000002)
#define USB_SUB_GROUP_0_CX_OUT_BIT_MUSK         (0x00000004)
#define USB_SUB_GROUP_0_CX_COMFAIL_BIT_MUSK     (0x00000010)
#define USB_SUB_GROUP_0_CX_COMABORT_BIT_MUSK    (0x00000020)
#define USB_SUB_GROUP_1_F0_OUT_BIT_MUSK         (0x00000001)
#define USB_SUB_GROUP_1_F0_SPK_BIT_MUSK         (0x00000002)
#define USB_SUB_GROUP_1_F1_OUT_BIT_MUSK         (0x00000004)
#define USB_SUB_GROUP_1_F1_SPK_BIT_MUSK         (0x00000008)
#define USB_SUB_GROUP_1_F2_OUT_BIT_MUSK         (0x00000010)
#define USB_SUB_GROUP_1_F2_SPK_BIT_MUSK         (0x00000020)
#define USB_SUB_GROUP_1_F3_OUT_BIT_MUSK         (0x00000040)
#define USB_SUB_GROUP_1_F3_SPK_BIT_MUSK         (0x00000080)
#define USB_SUB_GROUP_1_F0_IN_BIT_MUSK          (0x00010000)
#define USB_SUB_GROUP_1_F1_IN_BIT_MUSK          (0x00020000)
#define USB_SUB_GROUP_1_F2_IN_BIT_MUSK          (0x00040000)
#define USB_SUB_GROUP_1_F3_IN_BIT_MUSK          (0x00080000)
#define USB_SUB_GROUP_2_RESET_BIT_MUSK          (0x00000001)
#define USB_SUB_GROUP_2_SUSPEND_BIT_MUSK        (0x00000002)
#define USB_SUB_GROUP_2_RESUME_BIT_MUSK         (0x00000004)
#define USB_SUB_GROUP_2_TX0BYTE_BIT_MUSK        (0x00000020)
#define USB_SUB_GROUP_2_RX0BYTE_BIT_MUSK        (0x00000040)
#define USB_SUB_GROUP_2_CMPLT_BIT_MUSK          (0x00000080)
#define USB_SUB_GROUP_2_ERROR_BIT_MUSK          (0x00000100)
#define USB_SUB_GROUP_2_IDLE_BIT_MUSK           (0x00000200)
#define USB_SUB_GROUP_2_WAKEUP_BY_VBUS_BIT_MUSK (0x00000400)
#define USB_SUB_GROUP_3_VDMA_CMPLT_CXF_BIT_MUSK (0x00000001)
#define USB_SUB_GROUP_3_VDMA_CMPLT_F0_BIT_MUSK  (0x00000002)
#define USB_SUB_GROUP_3_VDMA_CMPLT_F1_BIT_MUSK  (0x00000004)
#define USB_SUB_GROUP_3_VDMA_CMPLT_F2_BIT_MUSK  (0x00000008)
#define USB_SUB_GROUP_3_VDMA_CMPLT_F3_BIT_MUSK  (0x00000010)
#define USB_SUB_GROUP_3_VDMA_ERROR_CXF_BIT_MUSK (0x00010000)
#define USB_SUB_GROUP_3_VDMA_ERROR_F0_BIT_MUSK  (0x00020000)
#define USB_SUB_GROUP_3_VDMA_ERROR_F1_BIT_MUSK  (0x00040000)
#define USB_SUB_GROUP_3_VDMA_ERROR_F2_BIT_MUSK  (0x00080000)
#define USB_SUB_GROUP_3_VDMA_ERROR_F3_BIT_MUSK  (0x00100000)
#define USB_SUB_GROUP_4_L1_BIT_MUSK             (0x00000001)

/*@} end of group USB_Public_Macros */

/** @defgroup  USB_Public_Functions
 *  @{
 */

/**
 *  @brief USB Functions
 */
BL_Err_Type USB_Set_Normal_Config(USB_NORMAL_Cfg_Type *cfg);
BL_Err_Type USB_SOF_Mask_Time_HighSpeed(void);
BL_Err_Type USB_SOF_Mask_Time_FullSpeed(void);
BL_Err_Type USB_SoftDetach_Enable(void);
BL_Err_Type USB_SoftDetach_Disable(void);
USB_DEVICE_SPEED_Type USB_Get_Device_Speed_Status(void);
BL_Err_Type USB_Go_Suspend(uint8_t enable);
BL_Err_Type USB_Set_Device_Address(uint8_t addr);
uint8_t USB_Get_Device_Address(void);
BL_Err_Type USB_Non_Ctrl_Transfer_Enable(void);
BL_Err_Type USB_Non_Ctrl_Transfer_Disable(void);
BL_Err_Type USB_Clear_CTRL_FIFO(void);
BL_Sts_Type USB_Is_CTRL_FIFO_Empty(void);
BL_Sts_Type USB_Is_CTRL_FIFO_Full(void);
BL_Err_Type USB_Clear_FIFO(void);
BL_Err_Type USB_Reset_FIFO(USB_FIFO_Type fifoID);
BL_Sts_Type USB_Is_FIFO_Empty(USB_FIFO_EMPTY_Type fifoNum);
BL_Err_Type USB_Set_FIFO_Of_Endpoint_IN(USB_Endpoint_Type epID, USB_FIFO_Type fifoID);
BL_Err_Type USB_Set_FIFO_Of_Endpoint_OUT(USB_Endpoint_Type epID, USB_FIFO_Type fifoID);
BL_Err_Type USB_Set_FIFO_Config(USB_FIFO_Type fifoID, USB_FIFO_Cfg_Type *cfg);
uint16_t USB_Get_OUT_FIFO_Count(USB_FIFO_Type fifoID);
BL_Err_Type USB_Set_Endpoint_IN_MaxPacketSize(USB_Endpoint_Type epID, uint16_t max);
BL_Err_Type USB_Set_Endpoint_OUT_MaxPacketSize(USB_Endpoint_Type epID, uint16_t max);
BL_Err_Type USB_Set_CTRL_Endpoint_Stall_Once(void);
BL_Err_Type USB_Set_Endpoint_IN_Stall(USB_Endpoint_Type epID, uint8_t enable);
BL_Err_Type USB_Set_Endpoint_OUT_Stall(USB_Endpoint_Type epID, uint8_t enable);
BL_Err_Type USB_CTRL_Endpoint_Data_Transfer_Done(void);
BL_Sts_Type USB_Is_Endpoint_Receive_Zero_Length_Packet(USB_Endpoint_Type epID);
BL_Err_Type USB_Clear_Endpoint_Receive_Zero_Length_Packet_Status(USB_Endpoint_Type epID);
BL_Err_Type USB_Reset_Endpoint_IN_Data_Toggle_Sequence(USB_Endpoint_Type epID);
BL_Err_Type USB_Reset_Endpoint_OUT_Data_Toggle_Sequence(USB_Endpoint_Type epID);
BL_Err_Type USB_Endpoint_Transmit_Zero_Length_Packet(USB_Endpoint_Type epID);
BL_Sts_Type USB_Is_Endpoint_Transfer_Zero_Length_Packet(USB_Endpoint_Type epID);
BL_Err_Type USB_Clear_Endpoint_Transfer_Zero_Length_Packet_Status(USB_Endpoint_Type epID);
BL_Err_Type USB_Get_Setup_Command(uint32_t setup[2]);
void USB_Reset_DMA_Accessing_Fifo(void);
BL_Err_Type USB_Update_DMA_Trans(uint32_t memAddr, uint32_t length);
BL_Err_Type USB_Set_DMA_Config(USB_DMA_TARGET_FIFO_Type fifoN, USB_DMA_Cfg_Type *cfg);
BL_Err_Type USB_Set_DMA_Start(void);
BL_Err_Type USB_Set_VDMA_Config(USB_VDMA_TARGET_FIFO_Type fifoN, USB_VDMA_Cfg_Type *cfg);
BL_Err_Type USB_Set_VDMA_Start(USB_VDMA_TARGET_FIFO_Type fifoN);
BL_Sts_Type USB_Get_VDMA_Start(USB_VDMA_TARGET_FIFO_Type fifoN);
BL_Err_Type USB_Set_VDMA_Enable(void);
BL_Err_Type USB_Set_LPM_Config(USB_LPM_Cfg_Type *cfg);
uint8_t USB_Get_LPM_BESL(void);
/*----------*/
BL_Err_Type USB_Set_Suspend_Delay(uint8_t ms);
/*----------*/
BL_Err_Type USB_Global_IntEnable(uint8_t enable);
BL_Err_Type USB_Global_IntMask(USB_GLOBAL_INT_Type intType, BL_Mask_Type intMask);
BL_Sts_Type USB_Global_IntStatus(USB_GLOBAL_INT_Type intType);
/*----------*/
BL_Err_Type USB_Group_IntMask(USB_GRP_INT_Type intType, BL_Mask_Type intMask);
BL_Sts_Type USB_Group_IntStatus(USB_GRP_INT_Type intType);
/*----------*/
BL_Err_Type USB_Sub_Group_IntMask(uint64_t intType);
BL_Err_Type USB_Sub_Group_IntUnmask(uint64_t intType);
/*----------*/
uint32_t USB_Get_Sub_Group_0_IntStatus(void);
uint32_t USB_Get_Sub_Group_1_IntStatus(void);
uint32_t USB_Get_Sub_Group_2_IntStatus(void);
uint32_t USB_Get_Sub_Group_3_IntStatus(void);
uint32_t USB_Get_Sub_Group_4_IntStatus(void);
uint32_t USB_Get_Sub_Group_0_IntMask(void);
uint32_t USB_Get_Sub_Group_1_IntMask(void);
uint32_t USB_Get_Sub_Group_2_IntMask(void);
uint32_t USB_Get_Sub_Group_3_IntMask(void);
uint32_t USB_Get_Sub_Group_4_IntMask(void);
BL_Err_Type USB_Get_Sub_Group_0_IntClear(uint32_t clrVal);
BL_Err_Type USB_Get_Sub_Group_1_IntClear(uint32_t clrVal);
BL_Err_Type USB_Get_Sub_Group_2_IntClear(uint32_t clrVal);
BL_Err_Type USB_Get_Sub_Group_3_IntClear(uint32_t clrVal);
BL_Err_Type USB_Get_Sub_Group_4_IntClear(uint32_t clrVal);
/*----------*/;

/*@} end of group USB_Public_Functions */

/*@} end of group USB */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_USB_H__ */
