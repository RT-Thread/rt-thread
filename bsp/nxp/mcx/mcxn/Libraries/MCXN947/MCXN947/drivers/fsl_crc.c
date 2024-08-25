/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_crc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.crc"
#endif

/*! @internal @brief Has data register with name CRC. */
#if defined(FSL_FEATURE_CRC_HAS_CRC_REG) && FSL_FEATURE_CRC_HAS_CRC_REG
#define DATA   CRC
#define DATALL CRCLL
#endif

#if defined(CRC_DRIVER_USE_CRC16_CCIT_FALSE_AS_DEFAULT) && CRC_DRIVER_USE_CRC16_CCIT_FALSE_AS_DEFAULT
/* @brief Default user configuration structure for CRC-16-CCITT */
#define CRC_DRIVER_DEFAULT_POLYNOMIAL 0x1021U
/*< CRC-16-CCIT polynomial x**16 + x**12 + x**5 + x**0 */
#define CRC_DRIVER_DEFAULT_SEED 0xFFFFU
/*< Default initial checksum */
#define CRC_DRIVER_DEFAULT_REFLECT_IN false
/*< Default is no transpose */
#define CRC_DRIVER_DEFAULT_REFLECT_OUT false
/*< Default is transpose bytes */
#define CRC_DRIVER_DEFAULT_COMPLEMENT_CHECKSUM false
/*< Default is without complement of CRC data register read data */
#define CRC_DRIVER_DEFAULT_CRC_BITS kCrcBits16
/*< Default is 16-bit CRC protocol */
#define CRC_DRIVER_DEFAULT_CRC_RESULT kCrcFinalChecksum
/*< Default is resutl type is final checksum */
#endif /* CRC_DRIVER_USE_CRC16_CCIT_FALSE_AS_DEFAULT */

#if defined(CRC_RSTS)
#define CRC_RESETS_ARRAY CRC_RSTS
#endif

/*! @brief CRC type of transpose of read write data */
typedef enum _crc_transpose_type
{
    kCrcTransposeNone         = 0U, /*! No transpose  */
    kCrcTransposeBits         = 1U, /*! Tranpose bits in bytes  */
    kCrcTransposeBitsAndBytes = 2U, /*! Transpose bytes and bits in bytes */
    kCrcTransposeBytes        = 3U, /*! Transpose bytes */
} crc_transpose_type_t;

/*!
 * @brief CRC module configuration.
 *
 * This structure holds the configuration for the CRC module.
 */
typedef struct _crc_module_config
{
    uint32_t polynomial;                 /*!< CRC Polynomial, MSBit first.@n
                                              Example polynomial: 0x1021 = 1_0000_0010_0001 = x^12+x^5+1 */
    uint32_t seed;                       /*!< Starting checksum value */
    crc_transpose_type_t readTranspose;  /*!< Type of transpose when reading CRC result. */
    crc_transpose_type_t writeTranspose; /*!< Type of transpose when writing CRC input data. */
    bool complementChecksum;             /*!< True if the result shall be complement of the actual checksum. */
    crc_bits_t crcBits;                  /*!< Selects 16- or 32- bit CRC protocol. */
} crc_module_config_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
#if defined(CRC_RESETS_ARRAY)
/*!
 * @brief Get instance number for CRC module.
 *
 * @param base CRC peripheral base address
 */
static uint32_t CRC_GetInstance(CRC_Type *base);
#endif
/*******************************************************************************
 * Variables
 ******************************************************************************/
#if defined(CRC_RESETS_ARRAY)
static CRC_Type *const s_crcBases[] = CRC_BASE_PTRS;

/* Reset array */
static const reset_ip_name_t s_crcResets[] = CRC_RESETS_ARRAY;
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
#if defined(CRC_RESETS_ARRAY)
static uint32_t CRC_GetInstance(CRC_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_crcBases); instance++)
    {
        if (s_crcBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_crcBases));

    return instance;
}
#endif

/*!
 * @brief Returns transpose type for CRC protocol reflect in parameter.
 *
 * This functions helps to set writeTranspose member of crc_config_t structure. Reflect in is CRC protocol parameter.
 *
 * @param enable True or false for the selected CRC protocol Reflect In (refin) parameter.
 */
static inline crc_transpose_type_t CRC_GetTransposeTypeFromReflectIn(bool enable)
{
    return ((enable) ? kCrcTransposeBitsAndBytes : kCrcTransposeBytes);
}

/*!
 * @brief Returns transpose type for CRC protocol reflect out parameter.
 *
 * This functions helps to set readTranspose member of crc_config_t structure. Reflect out is CRC protocol parameter.
 *
 * @param enable True or false for the selected CRC protocol Reflect Out (refout) parameter.
 */
static inline crc_transpose_type_t CRC_GetTransposeTypeFromReflectOut(bool enable)
{
    return ((enable) ? kCrcTransposeBitsAndBytes : kCrcTransposeNone);
}

/*!
 * @brief Starts checksum computation.
 *
 * Configures the CRC module for the specified CRC protocol. @n
 * Starts the checksum computation by writing the seed value
 *
 * @param base CRC peripheral address.
 * @param config Pointer to protocol configuration structure.
 */
static void CRC_ConfigureAndStart(CRC_Type *base, const crc_module_config_t *config)
{
    uint32_t crcControl;

    /* pre-compute value for CRC control registger based on user configuraton without WAS field */
    crcControl = 0U | CRC_CTRL_TOT(config->writeTranspose) | CRC_CTRL_TOTR(config->readTranspose) |
                 CRC_CTRL_FXOR(config->complementChecksum) | CRC_CTRL_TCRC(config->crcBits);

    /* make sure the control register is clear - WAS is deasserted, and protocol is set */
    base->CTRL = crcControl;

    /* write polynomial register */
    base->GPOLY = config->polynomial;

    /* write pre-computed control register value along with WAS to start checksum computation */
    base->CTRL = crcControl | CRC_CTRL_WAS(true);

    /* write seed (initial checksum) */
    base->DATA = config->seed;

    /* deassert WAS by writing pre-computed CRC control register value */
    base->CTRL = crcControl;
}

/*!
 * @brief Starts final checksum computation.
 *
 * Configures the CRC module for the specified CRC protocol. @n
 * Starts final checksum computation by writing the seed value.
 * @note CRC_Get16bitResult() or CRC_Get32bitResult() return final checksum
 *       (output reflection and xor functions are applied).
 *
 * @param base CRC peripheral address.
 * @param protocolConfig Pointer to protocol configuration structure.
 */
static void CRC_SetProtocolConfig(CRC_Type *base, const crc_config_t *protocolConfig)
{
    crc_module_config_t moduleConfig;
    /* convert protocol to CRC peripheral module configuration, prepare for final checksum */
    moduleConfig.polynomial         = protocolConfig->polynomial;
    moduleConfig.seed               = protocolConfig->seed;
    moduleConfig.readTranspose      = CRC_GetTransposeTypeFromReflectOut(protocolConfig->reflectOut);
    moduleConfig.writeTranspose     = CRC_GetTransposeTypeFromReflectIn(protocolConfig->reflectIn);
    moduleConfig.complementChecksum = protocolConfig->complementChecksum;
    moduleConfig.crcBits            = protocolConfig->crcBits;

    CRC_ConfigureAndStart(base, &moduleConfig);
}

/*!
 * @brief Starts intermediate checksum computation.
 *
 * Configures the CRC module for the specified CRC protocol. @n
 * Starts intermediate checksum computation by writing the seed value.
 * @note CRC_Get16bitResult() or CRC_Get32bitResult() return intermediate checksum (raw data register value).
 *
 * @param base CRC peripheral address.
 * @param protocolConfig Pointer to protocol configuration structure.
 */
static void CRC_SetRawProtocolConfig(CRC_Type *base, const crc_config_t *protocolConfig)
{
    crc_module_config_t moduleConfig;
    /* convert protocol to CRC peripheral module configuration, prepare for intermediate checksum */
    moduleConfig.polynomial = protocolConfig->polynomial;
    moduleConfig.seed       = protocolConfig->seed;
    moduleConfig.readTranspose =
        kCrcTransposeNone; /* intermediate checksum does no transpose of data register read value */
    moduleConfig.writeTranspose     = CRC_GetTransposeTypeFromReflectIn(protocolConfig->reflectIn);
    moduleConfig.complementChecksum = false; /* intermediate checksum does no xor of data register read value */
    moduleConfig.crcBits            = protocolConfig->crcBits;

    CRC_ConfigureAndStart(base, &moduleConfig);
}

/*!
 * brief Enables and configures the CRC peripheral module.
 *
 * This function enables the clock gate in the SIM module for the CRC peripheral.
 * It also configures the CRC module and starts a checksum computation by writing the seed.
 *
 * param base CRC peripheral address.
 * param config CRC module configuration structure.
 */
void CRC_Init(CRC_Type *base, const crc_config_t *config)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* ungate clock */
    CLOCK_EnableClock(kCLOCK_Crc0);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if defined(CRC_RESETS_ARRAY)
    RESET_ReleasePeripheralReset(s_crcResets[CRC_GetInstance(base)]);
#endif

    /* configure CRC module and write the seed */
    if (config->crcResult == kCrcFinalChecksum)
    {
        CRC_SetProtocolConfig(base, config);
    }
    else
    {
        CRC_SetRawProtocolConfig(base, config);
    }
}

/*!
 * brief Loads default values to the CRC protocol configuration structure.
 *
 * Loads default values to the CRC protocol configuration structure. The default values are as follows.
 * code
 *   config->polynomial = 0x1021;
 *   config->seed = 0xFFFF;
 *   config->reflectIn = false;
 *   config->reflectOut = false;
 *   config->complementChecksum = false;
 *   config->crcBits = kCrcBits16;
 *   config->crcResult = kCrcFinalChecksum;
 * endcode
 *
 * param config CRC protocol configuration structure.
 */
void CRC_GetDefaultConfig(crc_config_t *config)
{
    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    static const crc_config_t crc16ccit = {
        CRC_DRIVER_DEFAULT_POLYNOMIAL,          CRC_DRIVER_DEFAULT_SEED,
        CRC_DRIVER_DEFAULT_REFLECT_IN,          CRC_DRIVER_DEFAULT_REFLECT_OUT,
        CRC_DRIVER_DEFAULT_COMPLEMENT_CHECKSUM, CRC_DRIVER_DEFAULT_CRC_BITS,
        CRC_DRIVER_DEFAULT_CRC_RESULT,
    };

    *config = crc16ccit;
}

/*!
 * brief Writes data to the CRC module.
 *
 * Writes input data buffer bytes to the CRC data register.
 * The configured type of transpose is applied.
 *
 * param base CRC peripheral address.
 * param data Input data stream, MSByte in data[0].
 * param dataSize Size in bytes of the input data buffer.
 */
void CRC_WriteData(CRC_Type *base, const uint8_t *data, size_t dataSize)
{
    const uint32_t *data32;

    /* 8-bit reads and writes till source address is aligned 4 bytes */
    while ((0U != dataSize) && (0U != ((uint32_t)data & 3U)))
    {
        base->ACCESS8BIT.DATALL = *data;
        data++;
        dataSize--;
    }

    /* use 32-bit reads and writes as long as possible */
    data32 = (const uint32_t *)(uint32_t)data;
    while (dataSize >= sizeof(uint32_t))
    {
        base->DATA = *data32;
        data32++;
        dataSize -= sizeof(uint32_t);
    }

    data = (const uint8_t *)data32;

    /* 8-bit reads and writes till end of data buffer */
    while (dataSize != 0U)
    {
        base->ACCESS8BIT.DATALL = *data;
        data++;
        dataSize--;
    }
}

/*!
 * brief Reads the 32-bit checksum from the CRC module.
 *
 * Reads the CRC data register (either an intermediate or the final checksum).
 * The configured type of transpose and complement is applied.
 *
 * param base CRC peripheral address.
 * return An intermediate or the final 32-bit checksum, after configured transpose and complement operations.
 */
uint32_t CRC_Get32bitResult(CRC_Type *base)
{
    return base->DATA;
}

/*!
 * brief Reads a 16-bit checksum from the CRC module.
 *
 * Reads the CRC data register (either an intermediate or the final checksum).
 * The configured type of transpose and complement is applied.
 *
 * param base CRC peripheral address.
 * return An intermediate or the final 16-bit checksum, after configured transpose and complement operations.
 */
uint16_t CRC_Get16bitResult(CRC_Type *base)
{
    uint32_t retval;
    uint32_t totr; /* type of transpose read bitfield */

    retval = base->DATA;
    totr   = (base->CTRL & CRC_CTRL_TOTR_MASK) >> CRC_CTRL_TOTR_SHIFT;

    /* check transpose type to get 16-bit out of 32-bit register */
    if (totr >= 2U)
    {
        /* transpose of bytes for read is set, the result CRC is in CRC_DATA[HU:HL] */
        retval &= 0xFFFF0000U;
        retval = retval >> 16U;
    }
    else
    {
        /* no transpose of bytes for read, the result CRC is in CRC_DATA[LU:LL] */
        retval &= 0x0000FFFFU;
    }
    return (uint16_t)retval;
}
