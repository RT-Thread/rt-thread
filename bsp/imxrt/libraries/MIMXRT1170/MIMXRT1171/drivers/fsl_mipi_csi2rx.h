/*
 * Copyright 2017, 2019-2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_MIPI_CSI2RX_H_
#define FSL_MIPI_CSI2RX_H_

#include "fsl_common.h"

/*!
 * @addtogroup csi2rx
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief CSI2RX driver version. */
#define FSL_CSI2RX_DRIVER_VERSION (MAKE_VERSION(2, 0, 4))
/*! @} */

#if (defined(FSL_FEATURE_CSI2RX_HAS_NO_REG_PREFIX) && FSL_FEATURE_CSI2RX_HAS_NO_REG_PREFIX)

#define CSI2RX_REG_CFG_NUM_LANES(base)             (base)->CFG_NUM_LANES
#define CSI2RX_REG_CFG_DISABLE_DATA_LANES(base)    (base)->CFG_DISABLE_DATA_LANES
#define CSI2RX_REG_BIT_ERR(base)                   (base)->BIT_ERR
#define CSI2RX_REG_IRQ_STATUS(base)                (base)->IRQ_STATUS
#define CSI2RX_REG_IRQ_MASK(base)                  (base)->IRQ_MASK
#define CSI2RX_REG_ULPS_STATUS(base)               (base)->ULPS_STATUS
#define CSI2RX_REG_PPI_ERRSOT_HS(base)             (base)->PPI_ERRSOT_HS
#define CSI2RX_REG_PPI_ERRSOTSYNC_HS(base)         (base)->PPI_ERRSOTSYNC_HS
#define CSI2RX_REG_PPI_ERRESC(base)                (base)->PPI_ERRESC
#define CSI2RX_REG_PPI_ERRSYNCESC(base)            (base)->PPI_ERRSYNCESC
#define CSI2RX_REG_PPI_ERRCONTROL(base)            (base)->PPI_ERRCONTROL
#define CSI2RX_REG_CFG_DISABLE_PAYLOAD_0(base)     (base)->CFG_DISABLE_PAYLOAD_0
#define CSI2RX_REG_CFG_DISABLE_PAYLOAD_1(base)     (base)->CFG_DISABLE_PAYLOAD_1
#define CSI2RX_REG_CFG_IGNORE_VC(base)             (base)->CFG_IGNORE_VC
#define CSI2RX_REG_CFG_VID_VC(base)                (base)->CFG_VID_VC
#define CSI2RX_REG_CFG_VID_P_FIFO_SEND_LEVEL(base) (base)->CFG_VID_P_FIFO_SEND_LEVEL
#define CSI2RX_REG_CFG_VID_VSYNC(base)             (base)->CFG_VID_VSYNC
#define CSI2RX_REG_CFG_VID_HSYNC_FP(base)          (base)->CFG_VID_HSYNC_FP
#define CSI2RX_REG_CFG_VID_HSYNC(base)             (base)->CFG_VID_HSYNC
#define CSI2RX_REG_CFG_VID_HSYNC_BP(base)          (base)->CFG_VID_HSYNC_BP

#else

#define CSI2RX_REG_CFG_NUM_LANES(base)             (base)->CSI2RX_CFG_NUM_LANES
#define CSI2RX_REG_CFG_DISABLE_DATA_LANES(base)    (base)->CSI2RX_CFG_DISABLE_DATA_LANES
#define CSI2RX_REG_BIT_ERR(base)                   (base)->CSI2RX_BIT_ERR
#define CSI2RX_REG_IRQ_STATUS(base)                (base)->CSI2RX_IRQ_STATUS
#define CSI2RX_REG_IRQ_MASK(base)                  (base)->CSI2RX_IRQ_MASK
#define CSI2RX_REG_ULPS_STATUS(base)               (base)->CSI2RX_ULPS_STATUS
#define CSI2RX_REG_PPI_ERRSOT_HS(base)             (base)->CSI2RX_PPI_ERRSOT_HS
#define CSI2RX_REG_PPI_ERRSOTSYNC_HS(base)         (base)->CSI2RX_PPI_ERRSOTSYNC_HS
#define CSI2RX_REG_PPI_ERRESC(base)                (base)->CSI2RX_PPI_ERRESC
#define CSI2RX_REG_PPI_ERRSYNCESC(base)            (base)->CSI2RX_PPI_ERRSYNCESC
#define CSI2RX_REG_PPI_ERRCONTROL(base)            (base)->CSI2RX_PPI_ERRCONTROL
#define CSI2RX_REG_CFG_DISABLE_PAYLOAD_0(base)     (base)->CSI2RX_CFG_DISABLE_PAYLOAD_0
#define CSI2RX_REG_CFG_DISABLE_PAYLOAD_1(base)     (base)->CSI2RX_CFG_DISABLE_PAYLOAD_1
#define CSI2RX_REG_CFG_IGNORE_VC(base)             (base)->CSI2RX_CFG_IGNORE_VC
#define CSI2RX_REG_CFG_VID_VC(base)                (base)->CSI2RX_CFG_VID_VC
#define CSI2RX_REG_CFG_VID_P_FIFO_SEND_LEVEL(base) (base)->CSI2RX_CFG_VID_P_FIFO_SEND_LEVEL
#define CSI2RX_REG_CFG_VID_VSYNC(base)             (base)->CSI2RX_CFG_VID_VSYNC
#define CSI2RX_REG_CFG_VID_HSYNC_FP(base)          (base)->CSI2RX_CFG_VID_HSYNC_FP
#define CSI2RX_REG_CFG_VID_HSYNC(base)             (base)->CSI2RX_CFG_VID_HSYNC
#define CSI2RX_REG_CFG_VID_HSYNC_BP(base)          (base)->CSI2RX_CFG_VID_HSYNC_BP

#endif

#ifndef MIPI_CSI2RX_CSI2RX_CFG_NUM_LANES_csi2rx_cfg_num_lanes_MASK
#define MIPI_CSI2RX_CSI2RX_CFG_NUM_LANES_csi2rx_cfg_num_lanes_MASK MIPI_CSI2RX_CFG_NUM_LANES_CFG_NUM_LANES_MASK
#endif

#ifndef MIPI_CSI2RX_CSI2RX_IRQ_MASK_csi2rx_irq_mask_MASK
#define MIPI_CSI2RX_CSI2RX_IRQ_MASK_csi2rx_irq_mask_MASK MIPI_CSI2RX_IRQ_MASK_IRQ_MASK_MASK
#endif

/*! @brief CSI2RX data lanes.  */
enum _csi2rx_data_lane
{
    kCSI2RX_DataLane0 = (1U << 0U), /*!< Data lane 0. */
    kCSI2RX_DataLane1 = (1U << 1U), /*!< Data lane 1. */
    kCSI2RX_DataLane2 = (1U << 2U), /*!< Data lane 2. */
    kCSI2RX_DataLane3 = (1U << 3U)  /*!< Data lane 3. */
};

/*! @brief CSI2RX payload type.  */
enum _csi2rx_payload
{
    kCSI2RX_PayloadGroup0Null         = (1U << 0U),  /*!< NULL. */
    kCSI2RX_PayloadGroup0Blank        = (1U << 1U),  /*!< Blank. */
    kCSI2RX_PayloadGroup0Embedded     = (1U << 2U),  /*!< Embedded. */
    kCSI2RX_PayloadGroup0YUV420_8Bit  = (1U << 10U), /*!< Legacy YUV420 8 bit. */
    kCSI2RX_PayloadGroup0YUV422_8Bit  = (1U << 14U), /*!< YUV422 8 bit. */
    kCSI2RX_PayloadGroup0YUV422_10Bit = (1U << 15U), /*!< YUV422 10 bit. */
    kCSI2RX_PayloadGroup0RGB444       = (1U << 16U), /*!< RGB444. */
    kCSI2RX_PayloadGroup0RGB555       = (1U << 17U), /*!< RGB555. */
    kCSI2RX_PayloadGroup0RGB565       = (1U << 18U), /*!< RGB565. */
    kCSI2RX_PayloadGroup0RGB666       = (1U << 19U), /*!< RGB666. */
    kCSI2RX_PayloadGroup0RGB888       = (1U << 20U), /*!< RGB888. */
    kCSI2RX_PayloadGroup0Raw6         = (1U << 24U), /*!< Raw 6. */
    kCSI2RX_PayloadGroup0Raw7         = (1U << 25U), /*!< Raw 7. */
    kCSI2RX_PayloadGroup0Raw8         = (1U << 26U), /*!< Raw 8. */
    kCSI2RX_PayloadGroup0Raw10        = (1U << 27U), /*!< Raw 10. */
    kCSI2RX_PayloadGroup0Raw12        = (1U << 28U), /*!< Raw 12. */
    kCSI2RX_PayloadGroup0Raw14        = (1U << 29U), /*!< Raw 14. */
    kCSI2RX_PayloadGroup1UserDefined1 = (1U << 0U),  /*!< User defined 8-bit data type 1, 0x30. */
    kCSI2RX_PayloadGroup1UserDefined2 = (1U << 1U),  /*!< User defined 8-bit data type 2, 0x31. */
    kCSI2RX_PayloadGroup1UserDefined3 = (1U << 2U),  /*!< User defined 8-bit data type 3, 0x32. */
    kCSI2RX_PayloadGroup1UserDefined4 = (1U << 3U),  /*!< User defined 8-bit data type 4, 0x33. */
    kCSI2RX_PayloadGroup1UserDefined5 = (1U << 4U),  /*!< User defined 8-bit data type 5, 0x34. */
    kCSI2RX_PayloadGroup1UserDefined6 = (1U << 5U),  /*!< User defined 8-bit data type 6, 0x35. */
    kCSI2RX_PayloadGroup1UserDefined7 = (1U << 6U),  /*!< User defined 8-bit data type 7, 0x36. */
    kCSI2RX_PayloadGroup1UserDefined8 = (1U << 7U)   /*!< User defined 8-bit data type 8, 0x37. */
};

/*! @brief CSI2RX configuration.  */
typedef struct _csi2rx_config
{
    uint8_t laneNum;          /*!< Number of active lanes used for receiving data. */
    uint8_t tHsSettle_EscClk; /*!< Number of rx_clk_esc clock periods for T_HS_SETTLE.
                                   The T_HS_SETTLE should be in the range of
                                   85ns + 6UI to 145ns + 10UI. */
} csi2rx_config_t;

/*! @brief MIPI CSI2RX bit errors. */
enum _csi2rx_bit_error
{
    kCSI2RX_BitErrorEccTwoBit = (1U << 0U), /*!< ECC two bit error has occurred. */
    kCSI2RX_BitErrorEccOneBit = (1U << 1U)  /*!< ECC one bit error has occurred. */
};

/*! @brief MIPI CSI2RX PPI error types. */
typedef enum _csi2rx_ppi_error
{
    kCSI2RX_PpiErrorSotHs,     /*!< CSI2RX DPHY PPI error ErrSotHS. */
    kCSI2RX_PpiErrorSotSyncHs, /*!< CSI2RX DPHY PPI error ErrSotSync_HS. */
    kCSI2RX_PpiErrorEsc,       /*!< CSI2RX DPHY PPI error ErrEsc. */
    kCSI2RX_PpiErrorSyncEsc,   /*!< CSI2RX DPHY PPI error ErrSyncEsc. */
    kCSI2RX_PpiErrorControl,   /*!< CSI2RX DPHY PPI error ErrControl. */
} csi2rx_ppi_error_t;

/*! @brief MIPI CSI2RX interrupt. */
enum _csi2rx_interrupt
{
    kCSI2RX_InterruptCrcError         = (1U << 0U), /* CRC error. */
    kCSI2RX_InterruptEccOneBitError   = (1U << 1U), /* One bit ECC error. */
    kCSI2RX_InterruptEccTwoBitError   = (1U << 2U), /* One bit ECC error. */
    kCSI2RX_InterruptUlpsStatusChange = (1U << 3U), /* ULPS status changed. */
    kCSI2RX_InterruptErrorSotHs       = (1U << 4U), /* D-PHY ErrSotHS occurred. */
    kCSI2RX_InterruptErrorSotSyncHs   = (1U << 5U), /* D-PHY ErrSotSync_HS occurred. */
    kCSI2RX_InterruptErrorEsc         = (1U << 6U), /* D-PHY ErrEsc occurred. */
    kCSI2RX_InterruptErrorSyncEsc     = (1U << 7U), /* D-PHY ErrSyncEsc occurred. */
    kCSI2RX_InterruptErrorControl     = (1U << 8U), /* D-PHY ErrControl occurred. */
};

/*! @brief MIPI CSI2RX D-PHY ULPS state. */
enum _csi2rx_ulps_status
{
    kCSI2RX_ClockLaneUlps = (1U << 0U), /*!< Clock lane is in ULPS state. */
    kCSI2RX_DataLane0Ulps = (1U << 1U), /*!< Data lane 0 is in ULPS state. */
    kCSI2RX_DataLane1Ulps = (1U << 2U), /*!< Data lane 1 is in ULPS state. */
    kCSI2RX_DataLane2Ulps = (1U << 3U), /*!< Data lane 2 is in ULPS state. */
    kCSI2RX_DataLane3Ulps = (1U << 4U), /*!< Data lane 3 is in ULPS state. */
    kCSI2RX_ClockLaneMark = (1U << 5U), /*!< Clock lane is in mark state. */
    kCSI2RX_DataLane0Mark = (1U << 6U), /*!< Data lane 0 is in mark state. */
    kCSI2RX_DataLane1Mark = (1U << 7U), /*!< Data lane 1 is in mark state. */
    kCSI2RX_DataLane2Mark = (1U << 8U), /*!< Data lane 2 is in mark state. */
    kCSI2RX_DataLane3Mark = (1U << 9U), /*!< Data lane 3 is in mark state. */
};

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Enables and configures the CSI2RX peripheral module.
 *
 * @param base CSI2RX peripheral address.
 * @param config CSI2RX module configuration structure.
 */
void CSI2RX_Init(MIPI_CSI2RX_Type *base, const csi2rx_config_t *config);

/*!
 * @brief Disables the CSI2RX peripheral module.
 *
 * @param base CSI2RX peripheral address.
 */
void CSI2RX_Deinit(MIPI_CSI2RX_Type *base);

/*!
 * @brief Gets the MIPI CSI2RX bit error status.
 *
 * This function gets the RX bit error status, the return value could be compared
 * with @ref _csi2rx_bit_error. If one bit ECC error detected, the return value
 * could be passed to the function @ref CSI2RX_GetEccBitErrorPosition to get the
 * position of the ECC error bit.
 *
 * Example:
 * @code
    uint32_t bitError;
    uint32_t bitErrorPosition;

    bitError = CSI2RX_GetBitError(MIPI_CSI2RX);

    if (kCSI2RX_BitErrorEccTwoBit & bitError)
    {
        Two bits error;
    }
    else if (kCSI2RX_BitErrorEccOneBit & bitError)
    {
        One bits error;
        bitErrorPosition = CSI2RX_GetEccBitErrorPosition(bitError);
    }
   @endcode
 *
 * @param base CSI2RX peripheral address.
 * @return The RX bit error status.
 */
static inline uint32_t CSI2RX_GetBitError(MIPI_CSI2RX_Type *base)
{
    return CSI2RX_REG_BIT_ERR(base);
}

/*!
 * @brief Get ECC one bit error bit position.
 *
 * If @ref CSI2RX_GetBitError detects ECC one bit error, this function could
 * extract the error bit position from the return value of @ref CSI2RX_GetBitError.
 *
 * @param bitError The bit error returned by @ref CSI2RX_GetBitError.
 * @return The position of error bit.
 */
static inline uint32_t CSI2RX_GetEccBitErrorPosition(uint32_t bitError)
{
    return (bitError >> 2U) & 0x1FU;
}

/*!
 * @brief Gets the MIPI CSI2RX D-PHY ULPS status.
 *
 * Example to check whether data lane 0 is in ULPS status.
 * @code
   uint32_t status = CSI2RX_GetUlpsStatus(MIPI_CSI2RX);

   if (kCSI2RX_DataLane0Ulps & status)
   {
       Data lane 0 is in ULPS status.
   }
   @endcode
 *
 * @param base CSI2RX peripheral address.
 * @return The MIPI CSI2RX D-PHY ULPS status, it is OR'ed value or @ref _csi2rx_ulps_status.
 */
static inline uint32_t CSI2RX_GetUlpsStatus(MIPI_CSI2RX_Type *base)
{
    return CSI2RX_REG_ULPS_STATUS(base);
}

/*!
 * @brief Gets the MIPI CSI2RX D-PHY PPI error lanes.
 *
 * This function checks the PPI error occurred on which data lanes, the returned
 * value is OR'ed value of @ref csi2rx_ppi_error_t. For example, if the ErrSotHS
 * is detected, to check the ErrSotHS occurred on which data lanes, use like this:
 *
 * @code
   uint32_t errorDataLanes = CSI2RX_GetPpiErrorDataLanes(MIPI_CSI2RX, kCSI2RX_PpiErrorSotHs);

   if (kCSI2RX_DataLane0 & errorDataLanes)
   {
       ErrSotHS occurred on data lane 0.
   }

   if (kCSI2RX_DataLane1 & errorDataLanes)
   {
       ErrSotHS occurred on data lane 1.
   }
   @endcode
 *
 * @param base CSI2RX peripheral address.
 * @param errorType What kind of error to check.
 * @return The data lane mask that error @p errorType occurred.
 */
static inline uint32_t CSI2RX_GetPpiErrorDataLanes(MIPI_CSI2RX_Type *base, csi2rx_ppi_error_t errorType)
{
    uint32_t errorLanes;

    if (kCSI2RX_PpiErrorSotHs == errorType)
    {
        errorLanes = CSI2RX_REG_PPI_ERRSOT_HS(base);
    }
    else if (kCSI2RX_PpiErrorSotSyncHs == errorType)
    {
        errorLanes = CSI2RX_REG_PPI_ERRSOTSYNC_HS(base);
    }
    else if (kCSI2RX_PpiErrorEsc == errorType)
    {
        errorLanes = CSI2RX_REG_PPI_ERRESC(base);
    }
    else if (kCSI2RX_PpiErrorSyncEsc == errorType)
    {
        errorLanes = CSI2RX_REG_PPI_ERRSYNCESC(base);
    }
    else
    {
        errorLanes = CSI2RX_REG_PPI_ERRCONTROL(base);
    }

    return errorLanes;
}

/*!
 * @brief Enable the MIPI CSI2RX interrupts.
 *
 * This function enables the MIPI CSI2RX interrupts. The interrupts to enable
 * are passed in as an OR'ed value of @ref _csi2rx_interrupt. For example, to enable
 * one bit and two bit ECC error interrupts, use like this:
 *
 * @code
   CSI2RX_EnableInterrupts(MIPI_CSI2RX, kCSI2RX_InterruptEccOneBitError | kCSI2RX_InterruptEccTwoBitError);
   @endcode
 *
 * @param base CSI2RX peripheral address.
 * @param mask OR'ed value of @ref _csi2rx_interrupt.
 */
static inline void CSI2RX_EnableInterrupts(MIPI_CSI2RX_Type *base, uint32_t mask)
{
    CSI2RX_REG_IRQ_MASK(base) &= ~mask;
}

/*!
 * @brief Disable the MIPI CSI2RX interrupts.
 *
 * This function disables the MIPI CSI2RX interrupts. The interrupts to disable
 * are passed in as an OR'ed value of @ref _csi2rx_interrupt. For example, to disable
 * one bit and two bit ECC error interrupts, use like this:
 *
 * @code
   CSI2RX_DisableInterrupts(MIPI_CSI2RX, kCSI2RX_InterruptEccOneBitError | kCSI2RX_InterruptEccTwoBitError);
   @endcode
 *
 * @param base CSI2RX peripheral address.
 * @param mask OR'ed value of @ref _csi2rx_interrupt.
 */
static inline void CSI2RX_DisableInterrupts(MIPI_CSI2RX_Type *base, uint32_t mask)
{
    CSI2RX_REG_IRQ_MASK(base) |= mask;
}

/*!
 * @brief Get the MIPI CSI2RX interrupt status.
 *
 * This function returns the MIPI CSI2RX interrupts status as an OR'ed value
 * of @ref _csi2rx_interrupt.
 *
 * @param base CSI2RX peripheral address.
 * @return OR'ed value of @ref _csi2rx_interrupt.
 */
static inline uint32_t CSI2RX_GetInterruptStatus(MIPI_CSI2RX_Type *base)
{
    return CSI2RX_REG_IRQ_STATUS(base);
}

#if defined(__cplusplus)
}
#endif

/*!
 *@}
 */

#endif /* FSL_MIPI_CSI2RX_H_ */
