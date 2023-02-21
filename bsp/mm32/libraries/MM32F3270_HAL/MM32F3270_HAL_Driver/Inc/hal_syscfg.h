/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef __HAL_SYSCFG_H__
#define __HAL_SYSCFG_H__

#include "hal_common.h"

/*!
 * @addtogroup SYSCFG
 * @{
 */

/*!
 * @brief Boot memory mapping mode.
 */
typedef enum
{
    SYSCFG_BootMemMode_Flash = 0u, /*!< SYSCFG Boot Memory Flash mode. */
    SYSCFG_BootMemMode_ROM   = 1u, /*!< SYSCFG Boot Memory ROM mode. */
    SYSCFG_BootMemMode_SRAM  = 3u, /*!< SYSCFG Boot Memory SRAM mode. */
} SYSCFG_BootMemMode_Type;

/*!
 * @brief Set FSMC compatible mode.
 */
typedef enum
{
    SYSCFG_FSMCMode_NorFlash = 0u, /*!< SYSCFG FSMC compatible with Nor Flash. */
    SYSCFG_FSMCMode_8080 = 1u, /*!< SYSCFG FSMC compatible with 8080 protocal. */
} SYSCFG_FSMCMode_Type;

/*!
 * @brief FSMC pin usage.
 * FSMC pins can be used as data use only or mixed as data use and address use.
 */
typedef enum
{
    SYSCFG_FSMCPinUseMode_DataAndAddrMixed = 0u, /*!< FSMC pins can be used mixedly. */
    SYSCFG_FSMCPinUseMode_DataOnly = 1u, /*!< FSMC pins can be used for data only. */
} SYSCFG_FSMCPinUseMode_Type;

/*!
 * @brief External interrupt port.
 */
typedef enum
{
    SYSCFG_EXTIPort_GPIOA = (0x00U), /*!< SYSCFG External Interrupt GPIOA. */
    SYSCFG_EXTIPort_GPIOB = (0x01U), /*!< SYSCFG External Interrupt GPIOB. */
    SYSCFG_EXTIPort_GPIOC = (0x02U), /*!< SYSCFG External Interrupt GPIOC. */
    SYSCFG_EXTIPort_GPIOD = (0x03U), /*!< SYSCFG External Interrupt GPIOD. */
    SYSCFG_EXTIPort_GPIOE = (0x04U), /*!< SYSCFG External Interrupt GPIOE. */
    SYSCFG_EXTIPort_GPIOF = (0x05U), /*!< SYSCFG External Interrupt GPIOF. */
} SYSCFG_EXTIPort_Type;

/*!
 * @brief External interrupt line.
 */
typedef enum
{
    SYSCFG_EXTILine_0  =  (0x00U),  /*!< Pin 0 selected.    */
    SYSCFG_EXTILine_1  =  (0x01U),  /*!< Pin 1 selected.    */
    SYSCFG_EXTILine_2  =  (0x02U),  /*!< Pin 2 selected.    */
    SYSCFG_EXTILine_3  =  (0x03U),  /*!< Pin 3 selected.    */
    SYSCFG_EXTILine_4  =  (0x04U),  /*!< Pin 4 selected.    */
    SYSCFG_EXTILine_5  =  (0x05U),  /*!< Pin 5 selected.    */
    SYSCFG_EXTILine_6  =  (0x06U),  /*!< Pin 6 selected.    */
    SYSCFG_EXTILine_7  =  (0x07U),  /*!< Pin 7 selected.    */
    SYSCFG_EXTILine_8  =  (0x08U),  /*!< Pin 8 selected.    */
    SYSCFG_EXTILine_9  =  (0x09U),  /*!< Pin 9 selected.    */
    SYSCFG_EXTILine_10 =  (0x0AU),  /*!< Pin 10 selected.   */
    SYSCFG_EXTILine_11 =  (0x0BU),  /*!< Pin 11 selected.   */
    SYSCFG_EXTILine_12 =  (0x0CU),  /*!< Pin 12 selected.   */
    SYSCFG_EXTILine_13 =  (0x0DU),  /*!< Pin 13 selected.   */
    SYSCFG_EXTILine_14 =  (0x0EU),  /*!< Pin 14 selected.   */
    SYSCFG_EXTILine_15 =  (0x0FU),  /*!< Pin 15 selected.   */
} SYSCFG_EXTILine_Type;

/*!
 * @brief I2C port mode.
 */
typedef enum
{
    SYSCFG_I2CPortMode_OpenDrain = 0u, /*!< I2C output open-drain mode. */
    SYSCFG_I2CPortMode_PushPull = 1u, /*!< I2C output push-pull mode. */
} SYSCFG_I2CPortMode_Type;

/*!
 * @brief Ethernet port mode.
 */
typedef enum
{
    SYSCFG_ENETPortMode_MII  = 0u, /*!< Ethernet connect on MMI port. */
    SYSCFG_ENETPortMode_RMII = 1u, /*!< Ethernet connect on RMMI port. */
} SYSCFG_ENETPortMode_Type;

/*!
 * @brief Ethernet speed mode.
 */
typedef enum
{
    SYSCFG_ENETSpeedMode_10Mb  = 0u, /*!< Ethernet speed mode of 10 Mbps. */
    SYSCFG_ENETSpeedMode_100Mb = 1u, /*!< Ethernet speed mode of 100 Mbps. */
} SYSCFG_ENETSpeedMode_Type;

/*!
 * @brief PVD threshold.
 */
typedef enum
{
    SYSCFG_PVDThold_1v8 = 0u, /*!< PVD threshold of 1.8 v.*/
    SYSCFG_PVDThold_2v1 = 1u, /*!< PVD threshold of 2.1 v.*/
    SYSCFG_PVDThold_2v4 = 2u, /*!< PVD threshold of 2.4 v.*/
    SYSCFG_PVDThold_2v7 = 3u, /*!< PVD threshold of 2.7 v.*/
    SYSCFG_PVDThold_3v0 = 4u, /*!< PVD threshold of 3.0 v.*/
    SYSCFG_PVDThold_3v3 = 5u, /*!< PVD threshold of 3.3 v.*/
    SYSCFG_PVDThold_3v6 = 6u, /*!< PVD threshold of 3.6 v.*/
    SYSCFG_PVDThold_3v9 = 7u, /*!< PVD threshold of 3.9 v.*/
    SYSCFG_PVDThold_4v2 = 8u, /*!< PVD threshold of 4.2 v.*/
    SYSCFG_PVDThold_4v5 = 9u, /*!< PVD threshold of 4.5 v.*/
    SYSCFG_PVDThold_4v8 = 10u, /*!< PVD threshold of 4.8 v.*/
} SYSCFG_PVDThold_Type;

/*!
 * @brief PVD output state.
 */
typedef enum
{
    SYSCFG_PVDOut_Low  = 0u, /*!< PVD output low.*/
    SYSCFG_PVDOut_High = 1u, /*!< PVD output high.*/
} SYSCFG_PVDOut_Type;

/*!
 * @brief VDT threshold alt.
 */
typedef enum
{
    SYSCFG_VDTThold_1v2 = 0u, /*!< VDT threshold of 1.2 v.*/
    SYSCFG_VDTThold_1v1 = 1u, /*!< VDT threshold of 1.1 v.*/
    SYSCFG_VDTThold_1v0 = 2u, /*!< VDT threshold of 1.0 v.*/
    SYSCFG_VDTThold_0v9 = 3u, /*!< VDT threshold of 0.9 v.*/
} SYSCFG_VDTThold_Type;

/*!
 * @brief VDT output state.
 */
typedef enum
{
    SYSCFG_VDTOut_Low  = 0u, /*!< VDT output low.*/
    SYSCFG_VDTOut_High = 1u, /*!< VDT output high.*/
} SYSCFG_VDTOut_Type;

/*!
 * @brief This type of structure instance is used to keep the settings when calling the @ref SYSCFG_EnablePVD().
 */
typedef struct
{
    SYSCFG_PVDThold_Type Thold; /* Set the threshold of the PVD. */
    SYSCFG_PVDOut_Type Output; /* Set the output of the PVD. */
} SYSCFG_PVDConf_Type;

/*!
 * @brief This type of structure instance is used to keep the settings when calling the @ref SYSCFG_EnableVDT().
 */
typedef struct
{
    SYSCFG_VDTThold_Type Thold;  /* Set the threshold of the VDT. */
    SYSCFG_VDTOut_Type Output; /* Set the output of the VDT. */
} SYSCFG_VDTConf_Type;

/*!
 * @brief Set boot memory mode.
 *
 * @param mode The memory mode. See to @ref SYSCFG_BootMemMode_Type.
 * @return None.
 */
void SYSCFG_SetBootMemMode(SYSCFG_BootMemMode_Type mode);

/*!
 * @brief Set FSMC pin usage mode.
 *
 * @param mode FMSC pin use mode to be set. See to @ref SYSCFG_FSMCPinUseMode_Type.
 * @return None.
 */
void SYSCFG_SetFSMCPinUseMode(SYSCFG_FSMCPinUseMode_Type mode);

/*!
 * @brief Set the FMSC compatible mode.
 *
 * @param mode The compatible mode to be set for FMSC. See to @ref SYSCFG_FSMCMode_Type.
 * @return None.
 */
void SYSCFG_SetFSMCMode(SYSCFG_FSMCMode_Type mode);

/*!
 * @brief Set the external interrupt mux.
 *
 * @param port external interrupt port. See to @ref SYSCFG_EXTIPort_Type.
 * @param line external interrupt line. See to @ref SYSCFG_EXTILine_Type.
 * @return None.
 */
void SYSCFG_SetExtIntMux(SYSCFG_EXTIPort_Type port, SYSCFG_EXTILine_Type line);

/*!
 * @brief Set the I2C port 0 mode.
 *
 * @param mode The I2C output state to be set. See to @ref SYSCFG_I2CPortMode_Type.
 * @return None.
 */
void SYSCFG_SetI2C0PortMode(SYSCFG_I2CPortMode_Type mode);

/*!
 * @brief Set the I2C port 1 mode.
 *
 * @param mode The I2C output state to be set. See to @ref SYSCFG_I2CPortMode_Type.
 * @return None.
 */
void SYSCFG_SetI2C1PortMode(SYSCFG_I2CPortMode_Type mode);

/*!
 * @brief Set the Ethernet port mode.
 *
 * @param mode The Ethernet port mode. See to @ref SYSCFG_ENETPortMode_Type.
 * @return None.
 */
void SYSCFG_SetENETPortMode(SYSCFG_ENETPortMode_Type mode);

/*!
 * @brief Set the Ethernet speed mode.
 *
 * @param mode The Ethernet speed mode. See to @ref SYSCFG_ENETSpeedMode_Type.
 * @return None.
 */
void SYSCFG_SetENETSpeedMode(SYSCFG_ENETSpeedMode_Type mode);

/*!
 * @brief Enable the PVD.
 *
 * @param conf Pointer to the PDV configuration structure. See to @ref SYSCFG_PVDConf_Type.
 * @return None.
 */
void SYSCFG_EnablePVD(SYSCFG_PVDConf_Type * conf);

/*!
 * @brief Enable the VDT.
 *
 * @param conf Pointer to the VDT configuration structure. See to @ref SYSCFG_VDTConf_Type.
 * @return None.
 */
void SYSCFG_EnableVDT(SYSCFG_VDTConf_Type * conf);

/*!
 * @brief Enable ADC checking VBat_Div3.
 *
 * @param enable 'true' to enable ADC checking, 'false' to disable ADC checking.
 * @return None.
 */
void SYSCFG_EnableADCCheckVBatDiv3(bool enable);

/*!
 * @brief Set the VOS delay time.
 *
 * @param time VOS delay time.
 * @return None.
 */
void SYSCFG_SetVOSDelayValue(uint32_t val);

/*!
 * @}
 */

#endif /* __HAL_SYSCFG_H__ */
