/*
 * Copyright 2019-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_GT911_H_
#define _FSL_GT911_H_

#include "fsl_common.h"

/*
 * Change Log:
 *
 * 1.0.3:
 *   - Fixed MISRA 2012 issues.
 *
 * 1.0.2:
 *   - Fixed the issue that INT pin is output low when using kGT911_I2cAddrAny.
 *
 * 1.0.1:
 *   - Update GT911_GetMultiTouch and GT911_GetSingleTouch to return
 *     kStatus_TOUCHPANEL_NotTouched when no touch happens.
 *
 * 1.0.0:
 *   - Initial version.
 */

/*!
 * @addtogroup gt911
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief GT911 maximum number of simultaneously detected touches. */
#define GT911_MAX_TOUCHES (10U)

/*! @brief Error code definition. */
enum _touch_status
{
    kStatus_TOUCHPANEL_NotTouched = MAKE_STATUS(kStatusGroup_TOUCH_PANEL, 0) /*!< No touch happen. */
};

/*! @brief Touch point definition. */
typedef struct
{
    bool valid;      /*!< Whether the touch point coordinate value is valid. */
    uint8_t touchID; /*!< Id of the touch point. This numeric value stays constant between down and up event. */
    uint16_t x;      /*!< X coordinate of the touch point */
    uint16_t y;      /*!< Y coordinate of the touch point */
} touch_point_t;

/*! @brief gt911 I2C address mode.*/
typedef enum _gt911_i2c_addr_mode
{
    kGT911_I2cAddrMode0, /*!< 7-bit address 0x5D, or 8-bit 0xBA/0xBB */
    kGT911_I2cAddrMode1, /*!< 7-bit address 0x14, or 8-bit 0x28/0x29 */
    kGT911_I2cAddrAny,   /*!< Use 0x5D or 0x14, driver selects the right one to use,
                              this is used for the case that MCU could not pull
                              the INT pin level.
                              */
} gt911_i2c_addr_mode_t;

/*! @brief gt911 interrupt pin mode.*/
typedef enum _gt911_int_pin_mode
{
    kGT911_IntPinPullDown, /*!< Interrupt pin output pull down. */
    kGT911_IntPinPullUp,   /*!< Interrupt pin output pull up. */
    kGT911_IntPinInput,    /*!< Interrupt pin set to input mode. */
} gt911_int_pin_mode_t;

/*! @brief gt911 interrupt trigger mode.*/
typedef enum _gt911_int_trig_mode
{
    kGT911_IntRisingEdge,  /*!< Rising edge. */
    kGT911_IntFallingEdge, /*!< Falling edge. */
    kGT911_IntLowLevel,    /*!< Low level. */
    kGT911_IntHighLevel,   /*!< High edge. */
} gt911_int_trig_mode_t;

typedef status_t (*gt911_i2c_send_func_t)(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
typedef status_t (*gt911_i2c_receive_func_t)(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);
typedef void (*gt911_int_pin_func_t)(gt911_int_pin_mode_t mode);
typedef void (*gt911_reset_pin_func_t)(bool pullUp);

/*! @brief gt911 configure structure.*/
typedef struct _gt911_point_reg
{
    uint8_t id;       /*!< Track ID. */
    uint8_t lowX;     /*!< Low byte of x coordinate. */
    uint8_t highX;    /*!< High byte of x coordinate. */
    uint8_t lowY;     /*!< Low byte of y coordinate. */
    uint8_t highY;    /*!< High byte of x coordinate. */
    uint8_t lowSize;  /*!< Low byte of point size. */
    uint8_t highSize; /*!< High byte of point size. */
    uint8_t reserved; /*!< Reserved. */
} gt911_point_reg_t;

/*! @brief gt911 configure structure.*/
typedef struct _gt911_config
{
    gt911_i2c_send_func_t I2C_SendFunc;        /*!< Function to send I2C data. */
    gt911_i2c_receive_func_t I2C_ReceiveFunc;  /*!< Function to receive I2C data. */
    void (*timeDelayMsFunc)(uint32_t delayMs); /*!< Function to delay some MS. */
    gt911_int_pin_func_t intPinFunc;           /*!< Function to set interrupt pin to different mode. */
    gt911_reset_pin_func_t pullResetPinFunc;   /*!< Function to pull reset pin high or low. */
    uint8_t touchPointNum;                     /*!< How many touch points to enable. */
    gt911_i2c_addr_mode_t i2cAddrMode;         /*!< I2C address mode. */
    gt911_int_trig_mode_t intTrigMode;         /*!< Interrupt trigger mode. */
} gt911_config_t;

/*! @brief gt911 driver structure.*/
typedef struct _gt911_handle
{
    gt911_i2c_send_func_t I2C_SendFunc;            /*!< Function to send I2C data. */
    gt911_i2c_receive_func_t I2C_ReceiveFunc;      /*!< Function to receive I2C data. */
    void (*timeDelayMsFunc)(uint32_t delayMs);     /*!< Function to delay some MS. */
    gt911_reset_pin_func_t pullResetPinFunc;       /*!< Function to pull reset pin high or low. */
    gt911_point_reg_t pointReg[GT911_MAX_TOUCHES]; /*!< Buffer to receive touch point raw data. */
    uint8_t touchPointNum;                         /*!< How many touch points to enable. */
    uint8_t i2cAddr;                               /*!< I2C address. */
    uint16_t resolutionX;                          /*!< Resolution. */
    uint16_t resolutionY;                          /*!< Resolution. */
} gt911_handle_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initialize the driver.
 *
 * @param[in] handle Pointer to the GT911 driver.
 * @param[in] config Pointer to the configuration.
 * @return Returns @ref kStatus_Success if succeeded, otherwise return error code.
 */
status_t GT911_Init(gt911_handle_t *handle, const gt911_config_t *config);

/*!
 * @brief De-initialize the driver.
 *
 * @param[in] handle Pointer to the GT911 driver.
 * @return Returns @ref kStatus_Success if succeeded, otherwise return error code.
 */
status_t GT911_Deinit(gt911_handle_t *handle);

/*!
 * @brief Get single touch point coordinate.
 *
 * @param[in] handle Pointer to the GT911 driver.
 * @param[out] touch_x X coordinate of the touch point.
 * @param[out] touch_y Y coordinate of the touch point.
 * @return Returns @ref kStatus_Success if succeeded, otherwise return error code.
 */
status_t GT911_GetSingleTouch(gt911_handle_t *handle, int *touch_x, int *touch_y);

/*!
 * @brief Get multiple touch points coordinate.
 *
 * When calling this function, parameter @ref touch_count means the array size
 * of @p touch_array. After the function returns, the @p touch_count means how
 * many valid touch points there are in the @p touch_array.
 *
 * @param[in] handle Pointer to the GT911 driver.
 * @param[in, out] touch_count The touch point number.
 * @param[out] touch_array Array of touch points coordinate.
 * @return Returns @ref kStatus_Success if succeeded, otherwise return error code.
 */
status_t GT911_GetMultiTouch(gt911_handle_t *handle, uint8_t *touch_count, touch_point_t touch_array[]);

/*!
 * @brief Get touch IC resolution.
 *
 * Note the touch resolution might be different with display resolution.
 *
 * @param handle Pointer to the driver.
 * @param touch_x X resolution.
 * @param touch_y Y resolution.
 * @return Returns @ref kStatus_Success if succeeded, otherwise return error code.
 */
status_t GT911_GetResolution(gt911_handle_t *handle, int *resolutionX, int *resolutionY);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_GT911_H_ */
