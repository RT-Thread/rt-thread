 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     crc.c
 * @brief    CSI Source File for CRC Driver
 * @version  V1.0
 * @date     19. Feb 2020
 ******************************************************************************/
#include <drv/irq.h>
#include <stdio.h>
#include <string.h>
#include <drv/crc.h>
#include <drv/common.h>
#include    <assert.h>

/**
\brief CRC State
*/
typedef struct {
    uint32_t busy             : 1;        ///< busy flag
    uint32_t timeout          : 1;        ///< timeout state
    uint32_t error            : 1;        ///< error
} csi_crc_state_t;

/*----- CRC Control Codes: Mode -----*/
typedef enum {
    CRC_MODE_CRC8                   = 0,   ///< Mode CRC8
    CRC_MODE_CRC16,                        ///< Mode CRC16
    CRC_MODE_CRC32                         ///< Mode CRC32
} csi_crc_mode_t;


/*----- CRC Control Codes: Mode Parameters: Key length -----*/
typedef enum {
    CRC_STANDARD_ROHC         = 0,    ///< Standard CRC RHOC
    CRC_STANDARD_MAXIM,               ///< Standard CRC MAXIAM
    CRC_STANDARD_X25,                 ///< Standard CRC X25
    CRC_STANDARD_CCITT,               ///< Standard CRC CCITT
    CRC_STANDARD_CCITT_FALSE,         ///< Standard CRC CCITT-FALSE
    CRC_STANDARD_USB,                 ///< Standard CRC USB
    CRC_STANDARD_IBM,                 ///< Standard CRC IBM
    CRC_STANDARD_MODBUS,              ///< Standard CRC MODBUS
    CRC_STANDARD_ITU,                 ///< Standard CRC ITU
    CRC_STANDARD_PMEQ_2,              ///< Standard CRC PMEQ_2
    CRC_STANDARD_XMODEM,              ///< Standard CRC XMODEM
    CRC_STANDARD_DNP,                 ///< Standard CRC DNP
    CRC_STANDARD_NONE,                ///< Standard CRC NONE
    CRC_STANDARD_CRC8_31,
    CRC_STANDARD_CRC8_7,
} csi_crc_standard_t;

/**
\brief CRC config param
 */
typedef struct {
   csi_crc_mode_t       mode;
   csi_crc_standard_t   standard;
} csi_crc_config_t;

/**
\brief CRC ctrl block
 */
typedef struct {
    csi_dev_t           dev;
    csi_crc_config_t    config;
    csi_crc_state_t     state;
} csi_crc_t;

/**
  \brief       Initialize CRC Interface. 1. Initializes the resources needed for the CRC interface 2.registers event callback function
  \param[in]   crc  crc handle to operate.
  \param[in]   idx  device id
  \return      \ref csi_error_t
*/
csi_error_t csi_crc_init(csi_crc_t *crc, uint32_t idx)
{
    CSI_PARAM_CHK(crc, CSI_ERROR);
    ///< 获取中断号、基地址等相关信息
    target_get(DEV_WJ_CRC_TAG, idx, &crc->dev);

    return CSI_OK;
}

/**
  \brief       De-initialize CRC Interface. stops operation and releases the software resources used by the interface
  \param[in]   crc  crc handle to operate.
  \return      none
*/
void csi_crc_uninit(csi_crc_t *crc)
{

}
/**
  \brief       config crc mode.
  \param[in]   crc       crc handle to operate.
  \param[in]   config    \ref csi_crc_config_t
  \return      \ref csi_error_t
*/
csi_error_t csi_crc_config(csi_crc_t *crc, csi_crc_config_t *config)
{
    csi_error_t ret = CSI_OK;
    CSI_PARAM_CHK(crc, CSI_ERROR);

    crc->config = *config;

    switch (config->standard) {
        case CRC_STANDARD_MODBUS:
            ///< TODO：设置模式
            ///< TODO：设置极性
            ///< TODO：设置初始值

            break;

        case CRC_STANDARD_IBM:

            ///< TODO：设置模式
            ///< TODO：设置极性
            ///< TODO：设置初始值
            break;

        case CRC_STANDARD_MAXIM:
            ///< TODO：设置模式
            ///< TODO：设置极性
            ///< TODO：设置初始值
            break;

        case CRC_STANDARD_USB:
            ///< TODO：设置模式
            ///< TODO：设置极性
            ///< TODO：设置初始值
            break;

        case CRC_STANDARD_CCITT:
            ///< TODO：设置模式
            ///< TODO：设置极性
            ///< TODO：设置初始值
            break;

        case CRC_STANDARD_CCITT_FALSE:
            ret = CSI_ERROR;
            break;

        case CRC_STANDARD_X25:
            ///< TODO：设置模式
            ///< TODO：设置极性
            ///< TODO：设置初始值
            break;

        case CRC_STANDARD_CRC8_31:
            ///< TODO：设置模式
            ///< TODO：设置极性
            break;

        case CRC_STANDARD_CRC8_7:
            ///< TODO：设置模式
            ///< TODO：设置极性
            break;


        case CRC_STANDARD_XMODEM:
            ret = CSI_ERROR;
            break;


        case CRC_STANDARD_DNP:
            ret = CSI_ERROR;
            break;

        default:
            ret = CSI_ERROR;
    }

    return ret;

}

/**
  \brief       accumulate crc. Computes the 32-bit CRC of 32-bit data buffer using combination of the previous CRC value and the new one.
  \param[in]   crc     crc handle to operate.
  \param[in]   data    Pointer to the input data
  \param[in]   size    intput data size.
  \return      \ref calculate value
*/
uint32_t csi_crc_accumulate(csi_crc_t *crc, const void *data, uint32_t size)
{
    uint32_t ret = 0U;
    CSI_PARAM_CHK(crc, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);

    if (size <= 0U) {
        ret = 0U;
    } else {

        crc->state.busy = 1U;

        /* put the data int the register */
        uint32_t cur;
        uint8_t *p = (uint8_t *)data;

        for (cur = 0U; cur < (size - 3U); cur += 4U, p += 4U) {
             ///< TODO：设置待计算crc 数据： (uint32_t)(p[0]) | ((uint32_t)(p[1]) << 8U) | ((uint32_t)(p[2]) << 16U) | ((uint32_t)(p[3]) << 24U)
        }

        uint32_t data1 = 0U;
        uint8_t i;

        if (cur < size) {
            for (i = 0U; i < (size - cur); i++) {
                data1 |= ((uint32_t)(p[i]) << (i * 8U));
            }
            ///< TODO：设置待计算crc 数据 ： data1
        }

        crc->state.busy = 0U;
        ///< TODO：获取计算结果到ret
    }

    return ret;

}

/**
  \brief       calculate crc. Computes the 32-bit CRC of 32-bit data buffer independently of the previous CRC value.
  \param[in]   crc     crc handle to operate.
  \param[in]   data    Pointer to the input data
  \param[in]   size    intput data size.
  \return      \ref calculate value
*/
uint32_t csi_crc_calculate(csi_crc_t *crc, const void *data, uint32_t size)
{
    uint32_t ret = 0U;

    CSI_PARAM_CHK(crc, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);

    if (size <= 0U) {
        ret = 0U;
    } else {

        crc->state.busy = 1U;
        /* put the data int the register */
        uint32_t cur;
        uint8_t *p = (uint8_t *)data;

        for (cur = 0U; cur < (size - 3U); cur += 4U, p += 4U) {
        ///< TODO：设置待计算crc 数据： (uint32_t)(p[0]) | ((uint32_t)(p[1]) << 8U) | ((uint32_t)(p[2]) << 16U) | ((uint32_t)(p[3]) << 24U)
        }

        uint32_t data1 = 0U;
        uint8_t i;

        if (cur < size) {
            for (i = 0U; i < (size - cur); i++) {
                data1 |= ((uint32_t)(p[i]) << (i * 8U));
            }

            ///< TODO：设置待计算crc 数据 ： data1
        }

        crc->state.busy = 0U;

        ///< TODO：获取计算结果到ret
    }

    return ret;
}

/**
  \brief       Get CRC state.
  \param[in]   crc  crc handle to operate.
  \return      CRC state \ref  csi_crc_state_t
*/
csi_crc_state_t csi_crc_get_state(csi_crc_t *crc)
{

    return  crc->state;
}

/**
 * \brief Compute the CRC-7 checksum of a buffer.
 *
 * See JESD84-A441.  Used by the MMC protocol.  Uses 0x09 as the
 * polynomial with no reflection.  The CRC is left
 * justified, so bit 7 of the result is bit 6 of the CRC.
 * init = 0; poly = 0x09 refin = 0 refout = 0 xorout = 0
 * \param[in] crc      crc init value or crc immediate result
 * \param[in] data     data buf to be calculate
 * \param[in] size     data size
 *
 * \return    The computed CRC7 value
 */
uint8_t csi_crc7_be(uint8_t crc, uint8_t *data, uint32_t size)
{
    return 0;
}

/**
 * \brief Compute the CRC-8 checksum of a buffer.
 *  init = 0 or 0xff; poly = 0x07 refin = 0 refout = 0 xorout = 0
 * \param[in] crc      crc init value or crc immediate result
 * \param[in] data     data buf to be calculate
 * \param[in] size     data size
 * \return    The computed CRC8 value
 */
uint8_t csi_crc8(uint8_t crc, uint8_t *data, size_t size)
{
    csi_crc_state_t status;
    csi_crc_config_t config;
    static csi_crc_t crc1;
    uint8_t out;

    status.busy = 1U;

    csi_crc_init(&crc1, 0U);

    config.mode = CRC_MODE_CRC8;
    config.standard = CRC_STANDARD_CRC8_7;

    csi_crc_config(&crc1, &config);
    ///< TODO：设置初始值：crc
    out = (uint16_t)(csi_crc_calculate(&crc1, data, size));

    while (status.busy == 1U) {
        status = csi_crc_get_state(&crc1);
    }

    csi_crc_uninit(&crc1);
    return out;
}

/**
 * \brief Compute the CRC-8 checksum of a buffer.
 *  init = 0; poly = 0x31 refin = 1 refout = 1 xorout = 0
 * \param[in] crc      crc init value or crc immediate result
 * \param[in] data     data buf to be calculate
 * \param[in] size     data size
 * \return    The computed CRC8 value
 */
uint8_t csi_crc8_maxim(uint8_t crc, uint8_t *data, size_t size)
{
    csi_crc_state_t status;
    csi_crc_config_t config;
    static csi_crc_t crc1;
    uint8_t out;

    status.busy = 1U;

    csi_crc_init(&crc1, 0U);

    config.mode = CRC_MODE_CRC8;
    config.standard = CRC_STANDARD_CRC8_31;
    csi_crc_config(&crc1, &config);
    ///< TODO：设置初始值：crc
    out = (uint16_t)(csi_crc_calculate(&crc1, data, size));

    while (status.busy == 1U) {
        status = csi_crc_get_state(&crc1);
    }

    csi_crc_uninit(&crc1);
    return out;

}

/**
 * \brief Compute the CRC-16 checksum of a buffer.
 *   init = 0 or 0xffff; poly = 0x8005 refin = 1 refout = 1 xorout = 0
 * \param[in] crc      crc init value or crc immediate result
 * \param[in] data     data buf to be calculate
 * \param[in] size     data size
 * \return    The computed CRC16 without xorout
 */
uint16_t csi_crc16(uint16_t crc, uint8_t *data, uint32_t size)
{
    csi_crc_state_t status;
    csi_crc_t crc1;
    csi_crc_config_t config;
    uint16_t out;
    status.busy = 1U;

    if ((crc == 0U) || (crc == 0xffffU)) {

        csi_crc_init(&crc1, 0U);

        config.mode = CRC_MODE_CRC16;

        if (crc == 0xffffU) {
            config.standard = CRC_STANDARD_MODBUS;
        } else {
            config.standard = CRC_STANDARD_IBM;
        }

        csi_crc_config(&crc1, &config);
        out = (uint16_t)(csi_crc_calculate(&crc1, data, size));

        while (status.busy == 1U) {
            status = csi_crc_get_state(&crc1);
        }

        csi_crc_uninit(&crc1);
    } else {
        out = 0U; /* code */

    }

    return out;
}

/**
 * \brief Compute the CRC-16 checksum of a buffer.
 *  init = 0; poly = 0x1021 refin = 1 refout = 1 xorout = 0
 * \param[in] crc      crc init value or crc immediate result
 * \param[in] data     data buf to be calculate
 * \param[in] size     data size
 * \return    The computed CRC16 without xorout
 */
uint16_t csi_crc16_ccitt(uint16_t crc, uint8_t *data, uint32_t size)
{
    csi_crc_state_t status;
    csi_crc_config_t config;
    static csi_crc_t crc1;
    uint16_t out;

    status.busy = 1U;

    csi_crc_init(&crc1, 0U);
    config.mode = CRC_MODE_CRC16;
    config.standard = CRC_STANDARD_CCITT;
    csi_crc_config(&crc1, &config);
    out = (uint16_t)(csi_crc_calculate(&crc1, data, size));

    while (status.busy == 1U) {
        status = csi_crc_get_state(&crc1);
    }

    csi_crc_uninit(&crc1);

    return out;
}
