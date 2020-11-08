/**************************************************************************//**
 * @file     nu_dac.h
 * @version V1.00
 * @brief    M480 series DAC driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#ifndef __NU_DAC_H__
#define __NU_DAC_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup DAC_Driver DAC Driver
  @{
*/


/** @addtogroup DAC_EXPORTED_CONSTANTS DAC Exported Constants
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/*  DAC_CTL Constant Definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define DAC_CTL_LALIGN_RIGHT_ALIGN   (0UL<<DAC_CTL_LALIGN_Pos)   /*!< Right alignment. \hideinitializer */
#define DAC_CTL_LALIGN_LEFT_ALIGN    (1UL<<DAC_CTL_LALIGN_Pos)   /*!< Left alignment \hideinitializer */

#define DAC_WRITE_DAT_TRIGGER      (0UL)    /*!< Write DAC_DAT trigger \hideinitializer */
#define DAC_SOFTWARE_TRIGGER       (0UL|DAC_CTL_TRGEN_Msk)    /*!< Software trigger \hideinitializer */
#define DAC_LOW_LEVEL_TRIGGER      ((0UL<<DAC_CTL_ETRGSEL_Pos)|(1UL<<DAC_CTL_TRGSEL_Pos)|DAC_CTL_TRGEN_Msk)   /*!< STDAC pin low level trigger \hideinitializer */
#define DAC_HIGH_LEVEL_TRIGGER     ((1UL<<DAC_CTL_ETRGSEL_Pos)|(1UL<<DAC_CTL_TRGSEL_Pos)|DAC_CTL_TRGEN_Msk)   /*!< STDAC pin high level trigger \hideinitializer */
#define DAC_FALLING_EDGE_TRIGGER   ((2UL<<DAC_CTL_ETRGSEL_Pos)|(1UL<<DAC_CTL_TRGSEL_Pos)|DAC_CTL_TRGEN_Msk)   /*!< STDAC pin falling edge trigger \hideinitializer */
#define DAC_RISING_EDGE_TRIGGER    ((3UL<<DAC_CTL_ETRGSEL_Pos)|(1UL<<DAC_CTL_TRGSEL_Pos)|DAC_CTL_TRGEN_Msk)   /*!< STDAC pin rising edge trigger \hideinitializer */
#define DAC_TIMER0_TRIGGER         ((2UL<<DAC_CTL_TRGSEL_Pos)|DAC_CTL_TRGEN_Msk)   /*!< Timer 0 trigger \hideinitializer */
#define DAC_TIMER1_TRIGGER         ((3UL<<DAC_CTL_TRGSEL_Pos)|DAC_CTL_TRGEN_Msk)   /*!< Timer 1 trigger \hideinitializer */
#define DAC_TIMER2_TRIGGER         ((4UL<<DAC_CTL_TRGSEL_Pos)|DAC_CTL_TRGEN_Msk)   /*!< Timer 2 trigger \hideinitializer */
#define DAC_TIMER3_TRIGGER         ((5UL<<DAC_CTL_TRGSEL_Pos)|DAC_CTL_TRGEN_Msk)   /*!< Timer 3 trigger \hideinitializer */
#define DAC_EPWM0_TRIGGER          ((6UL<<DAC_CTL_TRGSEL_Pos)|DAC_CTL_TRGEN_Msk)   /*!< EPWM0 trigger \hideinitializer */
#define DAC_EPWM1_TRIGGER          ((7UL<<DAC_CTL_TRGSEL_Pos)|DAC_CTL_TRGEN_Msk)   /*!< EPWM1 trigger \hideinitializer */

#define DAC_TRIGGER_MODE_DISABLE   (0UL<<DAC_CTL_TRGEN_Pos)   /*!< Trigger mode disable \hideinitializer */
#define DAC_TRIGGER_MODE_ENABLE    (1UL<<DAC_CTL_TRGEN_Pos)   /*!< Trigger mode enable \hideinitializer */


/*@}*/ /* end of group DAC_EXPORTED_CONSTANTS */


/** @addtogroup DAC_EXPORTED_FUNCTIONS DAC Exported Functions
  @{
*/

/**
  * @brief Start the D/A conversion.
  * @param[in] dac Base address of DAC module.
  * @return None
  * @details User writes SWTRG bit (DAC_SWTRG[0]) to generate one shot pulse and it is cleared to 0 by hardware automatically.
  * \hideinitializer
  */
#define DAC_START_CONV(dac) ((dac)->SWTRG = DAC_SWTRG_SWTRG_Msk)

/**
  * @brief Enable DAC data left-aligned.
  * @param[in] dac Base address of DAC module.
  * @return None
  * @details User has to load data into DAC_DAT[15:4] bits. DAC_DAT[31:16] and DAC_DAT[3:0] are ignored in DAC conversion.
  * \hideinitializer
  */
#define DAC_ENABLE_LEFT_ALIGN(dac) ((dac)->CTL |= DAC_CTL_LALIGN_Msk)

/**
  * @brief Enable DAC data right-aligned.
  * @param[in] dac Base address of DAC module.
  * @return None
  * @details User has to load data into DAC_DAT[11:0] bits, DAC_DAT[31:12] are ignored in DAC conversion.
  * \hideinitializer
  */
#define DAC_ENABLE_RIGHT_ALIGN(dac) ((dac)->CTL &= ~DAC_CTL_LALIGN_Msk)

/**
  * @brief Enable output voltage buffer.
  * @param[in] dac Base address of DAC module.
  * @return None
  * @details The DAC integrates a voltage output buffer that can be used to reduce output impedance and
  *         drive external loads directly without having to add an external operational amplifier.
  * \hideinitializer
  */
#define DAC_ENABLE_BYPASS_BUFFER(dac) ((dac)->CTL |= DAC_CTL_BYPASS_Msk)

/**
  * @brief Disable output voltage buffer.
  * @param[in] dac Base address of DAC module.
  * @return None
  * @details This macro is used to disable output voltage buffer.
  * \hideinitializer
  */
#define DAC_DISABLE_BYPASS_BUFFER(dac) ((dac)->CTL &= ~DAC_CTL_BYPASS_Msk)

/**
  * @brief Enable the interrupt.
  * @param[in] dac Base address of DAC module.
  * @param[in] u32Ch Not used in M480 DAC.
  * @return None
  * @details This macro is used to enable DAC interrupt.
  * \hideinitializer
  */
#define DAC_ENABLE_INT(dac, u32Ch) ((dac)->CTL |= DAC_CTL_DACIEN_Msk)

/**
  * @brief Disable the interrupt.
  * @param[in] dac Base address of DAC module.
  * @param[in] u32Ch Not used in M480 DAC.
  * @return None
  * @details This macro is used to disable DAC interrupt.
  * \hideinitializer
  */
#define DAC_DISABLE_INT(dac, u32Ch) ((dac)->CTL &= ~DAC_CTL_DACIEN_Msk)

/**
  * @brief Enable DMA under-run interrupt.
  * @param[in] dac Base address of DAC module.
  * @return None
  * @details This macro is used to enable DMA under-run interrupt.
  * \hideinitializer
  */
#define DAC_ENABLE_DMAUDR_INT(dac) ((dac)->CTL |= DAC_CTL_DMAURIEN_Msk)

/**
  * @brief Disable DMA under-run interrupt.
  * @param[in] dac Base address of DAC module.
  * @return None
  * @details This macro is used to disable DMA under-run interrupt.
  * \hideinitializer
  */
#define DAC_DISABLE_DMAUDR_INT(dac) ((dac)->CTL &= ~DAC_CTL_DMAURIEN_Msk)

/**
  * @brief Enable PDMA mode.
  * @param[in] dac Base address of DAC module.
  * @return None
  * @details DAC DMA request is generated when a hardware trigger event occurs while DMAEN (DAC_CTL[2]) is set.
  * \hideinitializer
  */
#define DAC_ENABLE_PDMA(dac) ((dac)->CTL |= DAC_CTL_DMAEN_Msk)

/**
  * @brief Disable PDMA mode.
  * @param[in] dac Base address of DAC module.
  * @return None
  * @details This macro is used to disable DMA mode.
  * \hideinitializer
  */
#define DAC_DISABLE_PDMA(dac) ((dac)->CTL &= ~DAC_CTL_DMAEN_Msk)

/**
  * @brief Write data for conversion.
  * @param[in] dac Base address of DAC module.
  * @param[in] u32Ch Not used in M480 DAC.
  * @param[in] u32Data Decides the data for conversion, valid range are between 0~0xFFF.
  * @return None
  * @details 12 bit left alignment: user has to load data into DAC_DAT[15:4] bits.
  *         12 bit right alignment: user has to load data into DAC_DAT[11:0] bits.
  * \hideinitializer
  */
#define DAC_WRITE_DATA(dac, u32Ch, u32Data) ((dac)->DAT = (u32Data))

/**
  * @brief Read DAC 12-bit holding data.
  * @param[in] dac Base address of DAC module.
  * @param[in] u32Ch Not used in M480 DAC.
  * @return Return DAC 12-bit holding data.
  * @details This macro is used to read DAC_DAT register.
  * \hideinitializer
  */
#define DAC_READ_DATA(dac, u32Ch) ((dac)->DAT)

/**
  * @brief Get the busy state of DAC.
  * @param[in] dac Base address of DAC module.
  * @param[in] u32Ch Not used in M480 DAC.
  * @retval 0 Idle state.
  * @retval 1 Busy state.
  * @details This macro is used to read BUSY bit (DAC_STATUS[8]) to get busy state.
  * \hideinitializer
  */
#define DAC_IS_BUSY(dac, u32Ch) (((dac)->STATUS & DAC_STATUS_BUSY_Msk) >> DAC_STATUS_BUSY_Pos)

/**
  * @brief Get the interrupt flag.
  * @param[in] dac Base address of DAC module.
  * @param[in] u32Ch Not used in M480 DAC.
  * @retval 0 DAC is in conversion state.
  * @retval 1 DAC conversion finish.
  * @details This macro is used to read FINISH bit (DAC_STATUS[0]) to get DAC conversion complete finish flag.
  * \hideinitializer
  */
#define DAC_GET_INT_FLAG(dac, u32Ch) ((dac)->STATUS & DAC_STATUS_FINISH_Msk)

/**
  * @brief Get the DMA under-run flag.
  * @param[in] dac Base address of DAC module.
  * @retval 0 No DMA under-run error condition occurred.
  * @retval 1 DMA under-run error condition occurred.
  * @details This macro is used to read DMAUDR bit (DAC_STATUS[1]) to get DMA under-run state.
  * \hideinitializer
  */
#define DAC_GET_DMAUDR_FLAG(dac) (((dac)->STATUS & DAC_STATUS_DMAUDR_Msk) >> DAC_STATUS_DMAUDR_Pos)

/**
  * @brief This macro clear the interrupt status bit.
  * @param[in] dac Base address of DAC module.
  * @param[in] u32Ch Not used in M480 DAC.
  * @return None
  * @details User writes FINISH bit (DAC_STATUS[0]) to clear DAC conversion complete finish flag.
  * \hideinitializer
  */
#define DAC_CLR_INT_FLAG(dac, u32Ch) ((dac)->STATUS = DAC_STATUS_FINISH_Msk)

/**
  * @brief This macro clear the  DMA under-run flag.
  * @param[in] dac Base address of DAC module.
  * @return None
  * @details User writes DMAUDR bit (DAC_STATUS[1]) to clear DMA under-run flag.
  * \hideinitializer
  */
#define DAC_CLR_DMAUDR_FLAG(dac) ((dac)->STATUS = DAC_STATUS_DMAUDR_Msk)


/**
  * @brief Enable DAC group mode
  * @param[in] dac Base address of DAC module.
  * @return None
  * \hideinitializer
  */
#define DAC_ENABLE_GROUP_MODE(dac) (DAC0->CTL |= DAC_CTL_GRPEN_Msk)

/**
  * @brief Disable DAC group mode
  * @param[in] dac Base address of DAC module.
  * @return None
  * \hideinitializer
  */
#define DAC_DISABLE_GROUP_MODE(dac) (DAC0->CTL &= ~DAC_CTL_GRPEN_Msk)

void DAC_Open(DAC_T *dac, uint32_t u32Ch, uint32_t u32TrgSrc);
void DAC_Close(DAC_T *dac, uint32_t u32Ch);
uint32_t DAC_SetDelayTime(DAC_T *dac, uint32_t u32Delay);

/*@}*/ /* end of group DAC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group DAC_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __NU_DAC_H__ */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
