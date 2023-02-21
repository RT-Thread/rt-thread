/**************************************************************************//**
 * @file     nu_bmc.h
 * @version  V1.00
 * @brief    M460 series BMC driver header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_BMC_H__
#define __NU_BMC_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup BMC_Driver BMC Driver
  @{
*/

/** @addtogroup BMC_EXPORTED_CONSTANTS BMC Exported Constants
  @{
*/
#define BMC_BITWIDTH_1               (0UL)                      /*!< The bit time period of logic 0 is same as logic 1 \hideinitializer */
#define BMC_BITWIDTH_15              (BMC_CTL_BWADJ_Msk)        /*!< The bit time period of logic 0 is 1.5 times logic 1 \hideinitializer */

#define BMC_PREAMBLE_64              (0UL)                      /*!< BMC preamble is 64 bits \hideinitializer */
#define BMC_PREAMBLE_32              (BMC_CTL_PREAM32_Msk)      /*!< BMC preamble is 32 bits \hideinitializer */

#define BMC_DUM_LVL_LOW              (0UL)                      /*!< BMC dummy level is low \hideinitializer */
#define BMC_DUM_LVL_HIGH             (BMC_CTL_DUMLVL_Msk)       /*!< BMC dummy level is high \hideinitializer */

#define BMC_GROUP_0                  (0UL)                      /*!< BMC group 0 mask \hideinitializer */
#define BMC_GROUP_1                  (4UL)                      /*!< BMC group 1 mask \hideinitializer */
#define BMC_GROUP_2                  (8UL)                      /*!< BMC group 2 mask \hideinitializer */
#define BMC_GROUP_3                  (12UL)                     /*!< BMC group 3 mask \hideinitializer */
#define BMC_GROUP_4                  (16UL)                     /*!< BMC group 4 mask \hideinitializer */
#define BMC_GROUP_5                  (20UL)                     /*!< BMC group 5 mask \hideinitializer */
#define BMC_GROUP_6                  (24UL)                     /*!< BMC group 6 mask \hideinitializer */
#define BMC_GROUP_7                  (28UL)                     /*!< BMC group 7 mask \hideinitializer */

#define BMC_CHANNEL_NUM              (32UL)                     /*!< BMC total channel number \hideinitializer */

#define BMC_FTXD_INT_MASK            (0x1UL)                    /*!< Frame transmit done interrupt mask \hideinitializer */
#define BMC_TXUND_INT_MASK           (0x2UL)                    /*!< Transmit data under run interrupt mask \hideinitializer */

#define BMC_G0TXUND_MASK             (0x01UL)                   /*!< BMC group 0 transmit data under run mask \hideinitializer */
#define BMC_G1TXUND_MASK             (0x02UL)                   /*!< BMC group 1 transmit data under run mask \hideinitializer */
#define BMC_G2TXUND_MASK             (0x04UL)                   /*!< BMC group 2 transmit data under run mask \hideinitializer */
#define BMC_G3TXUND_MASK             (0x08UL)                   /*!< BMC group 3 transmit data under run mask \hideinitializer */
#define BMC_G4TXUND_MASK             (0x10UL)                   /*!< BMC group 4 transmit data under run mask \hideinitializer */
#define BMC_G5TXUND_MASK             (0x20UL)                   /*!< BMC group 5 transmit data under run mask \hideinitializer */
#define BMC_G6TXUND_MASK             (0x40UL)                   /*!< BMC group 6 transmit data under run mask \hideinitializer */
#define BMC_G7TXUND_MASK             (0x80UL)                   /*!< BMC group 7 transmit data under run mask \hideinitializer */


/*@}*/ /* end of group BMC_EXPORTED_CONSTANTS */


/** @addtogroup BMC_EXPORTED_FUNCTIONS BMC Exported Functions
  @{
*/

/**
  * @brief      Enable BMC controller
  * @return     None
  * @details    This macro is used to enable Biphase Mask Coding function.
  * \hideinitializer
  */
#define BMC_ENABLE()    (BMC->CTL |= BMC_CTL_BMCEN_Msk)

/**
  * @brief      Disable BMC controller
  * @return     None
  * @details    This macro is used to disable Biphase Mask Coding function.
  * \hideinitializer
  */
#define BMC_DISABLE()    (BMC->CTL &= ~BMC_CTL_BMCEN_Msk)

/**
  * @brief      Set the bit width adjustment
  * @param[in]  u32BitAdj BMC bit time period adjustment selection, valid values are:
  *                       - \ref BMC_BITWIDTH_1
  *                       - \ref BMC_BITWIDTH_15
  * @return     None
  * @details    This macro is used to set bit width adjustment.
  * \hideinitializer
  */
#define BMC_BITWIDTH_ADJUST(u32BitAdj)    (BMC->CTL = (BMC->CTL & ~BMC_CTL_BWADJ_Msk) | (u32BitAdj))

/**
  * @brief      Set the bit number of preamble
  * @param[in]  u32PreamBit BMC preamble bit number selection, valid values are:
  *                         - \ref BMC_PREAMBLE_64
  *                         - \ref BMC_PREAMBLE_32
  * @return     None
  * @details    This macro is used to set the bit number of preamble.
  * \hideinitializer
  */
#define BMC_PREAMBLE_BIT(u32PreamBit)    (BMC->CTL = (BMC->CTL & ~BMC_CTL_PREAM32_Msk) | (u32PreamBit))

/**
  * @brief      Set the dummy bit level
  * @param[in]  u32DumLvl BMC dummy bit level selection, valid values are:
  *                       - \ref BMC_DUM_LVL_LOW
  *                       - \ref BMC_DUM_LVL_HIGH
  * @return     None
  * @details    This macro is used to set dummy bit level.
  * \hideinitializer
  */
#define BMC_DUMMY_LEVEL(u32DumLvl)    (BMC->CTL = (BMC->CTL & ~BMC_CTL_DUMLVL_Msk) | (u32DumLvl))

/**
  * @brief      Enable PDMA function
  * @return     None
  * @details    This macro is used to enable PDMA function.
  * \hideinitializer
  */
#define BMC_ENABLE_DMA()    (BMC->CTL |= BMC_CTL_DMAEN_Msk)

/**
  * @brief      Disable PDMA function
  * @return     None
  * @details    This macro is used to disable PDMA function.
  * \hideinitializer
  */
#define BMC_DISABLE_DMA()    (BMC->CTL &= ~BMC_CTL_DMAEN_Msk)

/**
  * @brief      Enable BMC group 0 channels
  * @return     None
  * @details    This macro is used to enable BMC channel 0~3.
  * \hideinitializer
  */
#define BMC_ENABLE_GROUP0()    (BMC->CTL |= BMC_CTL_G0CHEN_Msk)

/**
  * @brief      Enable BMC group 1 channels
  * @return     None
  * @details    This macro is used to enable BMC channel 4~7.
  * \hideinitializer
  */
#define BMC_ENABLE_GROUP1()    (BMC->CTL |= BMC_CTL_G1CHEN_Msk)

/**
  * @brief      Enable BMC group 2 channels
  * @return     None
  * @details    This macro is used to enable BMC channel 8~11.
  * \hideinitializer
  */
#define BMC_ENABLE_GROUP2()    (BMC->CTL |= BMC_CTL_G2CHEN_Msk)

/**
  * @brief      Enable BMC group 3 channels
  * @return     None
  * @details    This macro is used to enable BMC channel 12~15.
  * \hideinitializer
  */
#define BMC_ENABLE_GROUP3()    (BMC->CTL |= BMC_CTL_G3CHEN_Msk)

/**
  * @brief      Enable BMC group 4 channels
  * @return     None
  * @details    This macro is used to enable BMC channel 16~19.
  * \hideinitializer
  */
#define BMC_ENABLE_GROUP4()    (BMC->CTL |= BMC_CTL_G4CHEN_Msk)

/**
  * @brief      Enable BMC group 5 channels
  * @return     None
  * @details    This macro is used to enable BMC channel 20~23.
  * \hideinitializer
  */
#define BMC_ENABLE_GROUP5()    (BMC->CTL |= BMC_CTL_G5CHEN_Msk)

/**
  * @brief      Enable BMC group 6 channels
  * @return     None
  * @details    This macro is used to enable BMC channel 24~27.
  * \hideinitializer
  */
#define BMC_ENABLE_GROUP6()    (BMC->CTL |= BMC_CTL_G6CHEN_Msk)

/**
  * @brief      Enable BMC group 7 channels
  * @return     None
  * @details    This macro is used to enable BMC channel 28~31.
  * \hideinitializer
  */
#define BMC_ENABLE_GROUP7()    (BMC->CTL |= BMC_CTL_G7CHEN_Msk)

/**
  * @brief      Get channel's FIFO empty flag
  * @return     Which channel's FIFO is empty
  * @details    This macro will return which channel's FIFO is empty.
  * \hideinitializer
  */
#define BMC_GET_CH_EMPTY_FLAG()    (BMC->CHEMPTY)


uint32_t BMC_SetBitClock(uint32_t u32BitClock);
uint32_t BMC_GetBitClock(void);
uint32_t BMC_SetDummyDelayPeriod(uint32_t u32ChGroup, uint32_t u32DumDelay);
void BMC_EnableInt(uint32_t u32Mask);
void BMC_DisableInt(uint32_t u32Mask);
uint32_t BMC_GetIntFlag(uint32_t u32Mask);
void BMC_ClearIntFlag(uint32_t u32Mask);
uint32_t BMC_GetStatus(uint32_t u32Mask);
void BMC_ClearStatus(uint32_t u32Mask);


/*@}*/ /* end of group BMC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group BMC_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __NU_BMC_H__ */
