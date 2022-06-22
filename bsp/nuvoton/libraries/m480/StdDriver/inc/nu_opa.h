/**************************************************************************//**
 * @file     nu_opa.h
 * @version  V3.00
 * @brief    M480 series OPA driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_OPA_H__
#define __NU_OPA_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup OPA_Driver OPA Driver
  @{
*/

/** @addtogroup OPA_EXPORTED_CONSTANTS OPA Exported Constants
  @{
*/
#define OPA_CALIBRATION_CLK_1K                        (0UL)                     /*!< OPA calibration clock select 1 KHz  \hideinitializer */
#define OPA_CALIBRATION_RV_1_2_AVDD                   (0UL)                     /*!< OPA calibration reference voltage select 1/2 AVDD  \hideinitializer */
#define OPA_CALIBRATION_RV_H_L_VCM                    (1UL)                     /*!< OPA calibration reference voltage select from high vcm to low vcm \hideinitializer */

/*@}*/ /* end of group OPA_EXPORTED_CONSTANTS */

/** @addtogroup OPA_EXPORTED_FUNCTIONS OPA Exported Functions
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/* Define OPA functions prototype                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
__STATIC_INLINE int32_t OPA_Calibration(OPA_T *opa, uint32_t u32OpaNum, uint32_t u32ClockSel, uint32_t u32LevelSel);

/**
  * @brief This macro is used to power on the OPA circuit
  * @param[in] opa The pointer of the specified OPA module
  * @param[in] u32OpaNum The OPA number. 0 for OPA0; 1 for OPA1; 2 for OPA2.
  * @return None
  * @details This macro will set OPx_EN (x=0, 1) bit of OPACR register to power on the OPA circuit.
  * @note Remember to enable HIRC clock while power on the OPA circuit.
  * \hideinitializer
  */
#define OPA_POWER_ON(opa, u32OpaNum) ((opa)->CTL |= (1UL<<(OPA_CTL_OPEN0_Pos+(u32OpaNum))))

/**
  * @brief This macro is used to power down the OPA circuit
  * @param[in] opa The pointer of the specified OPA module
  * @param[in] u32OpaNum The OPA number. 0 for OPA0; 1 for OPA1; 2 for OPA2.
  * @return None
  * @details This macro will clear OPx_EN (x=0, 1) bit of OPACR register to power down the OPA circuit.
  * \hideinitializer
  */
#define OPA_POWER_DOWN(opa, u32OpaNum) ((opa)->CTL &= ~(1UL<<(OPA_CTL_OPEN0_Pos+(u32OpaNum))))

/**
  * @brief This macro is used to enable the OPA Schmitt trigger buffer
  * @param[in] opa The pointer of the specified OPA module
  * @param[in] u32OpaNum The OPA number. 0 for OPA0; 1 for OPA1; 2 for OPA2.
  * @return None
  * @details This macro will set OPSCHx_EN (x=0, 1) bit of OPACR register to enable the OPA Schmitt trigger buffer.
  * \hideinitializer
  */
#define OPA_ENABLE_SCH_TRIGGER(opa, u32OpaNum) ((opa)->CTL |= (1UL<<(OPA_CTL_OPDOEN0_Pos+(u32OpaNum))))

/**
  * @brief This macro is used to disable the OPA Schmitt trigger buffer
  * @param[in] opa The pointer of the specified OPA module
  * @param[in] u32OpaNum The OPA number. 0 for OPA0; 1 for OPA1; 2 for OPA2.
  * @return None
  * @details This macro will clear OPSCHx_EN (x=0, 1) bit of OPACR register to disable the OPA Schmitt trigger buffer.
  * \hideinitializer
  */
#define OPA_DISABLE_SCH_TRIGGER(opa, u32OpaNum) ((opa)->CTL &= ~(1UL<<(OPA_CTL_OPDOEN0_Pos+(u32OpaNum))))

/**
  * @brief This macro is used to enable OPA Schmitt trigger digital output interrupt
  * @param[in] opa The pointer of the specified OPA module
  * @param[in] u32OpaNum The OPA number. 0 for OPA0; 1 for OPA1; 2 for OPA2.
  * @return None
  * @details This macro will set OPDIEx (x=0, 1) bit of OPACR register to enable the OPA Schmitt trigger digital output interrupt.
  * \hideinitializer
  */
#define OPA_ENABLE_INT(opa, u32OpaNum) ((opa)->CTL |= (1UL<<(OPA_CTL_OPDOIEN0_Pos+(u32OpaNum))))

/**
  * @brief This macro is used to disable OPA Schmitt trigger digital output interrupt
  * @param[in] opa The pointer of the specified OPA module
  * @param[in] u32OpaNum The OPA number. 0 for OPA0; 1 for OPA1; 2 for OPA2.
  * @return None
  * @details This macro will clear OPDIEx (x=0, 1) bit of OPACR register to disable the OPA Schmitt trigger digital output interrupt.
  * \hideinitializer
  */
#define OPA_DISABLE_INT(opa, u32OpaNum) ((opa)->CTL &= ~(1UL<<(OPA_CTL_OPDOIEN0_Pos+(u32OpaNum))))

/**
  * @brief This macro is used to get OPA digital output state
  * @param[in] opa The pointer of the specified OPA module
  * @param[in] u32OpaNum The OPA number. 0 for OPA0; 1 for OPA1; 2 for OPA2.
  * @return  OPA digital output state
  * @details This macro will return the OPA digital output value.
  * \hideinitializer
  */
#define OPA_GET_DIGITAL_OUTPUT(opa, u32OpaNum) (((opa)->STATUS & (OPA_STATUS_OPDO0_Msk<<(u32OpaNum)))?1UL:0UL)

/**
  * @brief This macro is used to get OPA interrupt flag
  * @param[in] opa The pointer of the specified OPA module
  * @param[in] u32OpaNum The OPA number. 0 for OPA0; 1 for OPA1; 2 for OPA2.
  * @retval     0 OPA interrupt does not occur.
  * @retval     1 OPA interrupt occurs.
  * @details This macro will return the ACMP interrupt flag.
  * \hideinitializer
  */
#define OPA_GET_INT_FLAG(opa, u32OpaNum) (((opa)->STATUS & (OPA_STATUS_OPDOIF0_Msk<<(u32OpaNum)))?1UL:0UL)

/**
  * @brief This macro is used to clear OPA interrupt flag
  * @param[in] opa The pointer of the specified OPA module
  * @param[in] u32OpaNum The OPA number. 0 for OPA0; 1 for OPA1; 2 for OPA2.
  * @return   None
  * @details This macro will write 1 to OPDFx (x=0,1) bit of OPASR register to clear interrupt flag.
  * \hideinitializer
  */
#define OPA_CLR_INT_FLAG(opa, u32OpaNum) ((opa)->STATUS = (OPA_STATUS_OPDOIF0_Msk<<(u32OpaNum)))


/**
  * @brief This function is used to configure and start OPA calibration
  * @param[in] opa The pointer of the specified OPA module
  * @param[in] u32OpaNum The OPA number. 0 for OPA0; 1 for OPA1; 2 for OPA2.
  * @param[in] u32ClockSel Select OPA calibration clock
  *                 - \ref OPA_CALIBRATION_CLK_1K
  * @param[in] u32RefVol Select OPA reference voltage
  *                 - \ref OPA_CALIBRATION_RV_1_2_AVDD
  *                 - \ref OPA_CALIBRATION_RV_H_L_VCM
  * @retval      0 PMOS and NMOS calibration successfully.
  * @retval     -1 only PMOS calibration failed.
  * @retval     -2 only NMOS calibration failed.
  * @retval     -3 PMOS and NMOS calibration failed.
  */
__STATIC_INLINE int32_t OPA_Calibration(OPA_T *opa,
                                        uint32_t u32OpaNum,
                                        uint32_t u32ClockSel,
                                        uint32_t u32RefVol)
{
    uint32_t u32CALResult;
    int32_t i32Ret = 0L;

    (opa)->CALCTL = (((opa)->CALCTL) & ~(OPA_CALCTL_CALCLK0_Msk << (u32OpaNum << 1)));
    (opa)->CALCTL = (((opa)->CALCTL) & ~(OPA_CALCTL_CALRVS0_Msk << (u32OpaNum))) | (((u32RefVol) << OPA_CALCTL_CALRVS0_Pos) << (u32OpaNum));
    (opa)->CALCTL |= (OPA_CALCTL_CALTRG0_Msk << (u32OpaNum));
    while((opa)->CALCTL & (OPA_CALCTL_CALTRG0_Msk << (u32OpaNum))) {}

    u32CALResult = ((opa)->CALST >> ((u32OpaNum)*4U)) & (OPA_CALST_CALNS0_Msk|OPA_CALST_CALPS0_Msk);
    if (u32CALResult == 0U)
    {
        i32Ret = 0L;
    }
    else if (u32CALResult == OPA_CALST_CALNS0_Msk)
    {
        i32Ret = -2L;
    }
    else if (u32CALResult == OPA_CALST_CALPS0_Msk)
    {
        i32Ret = -1L;
    }
    else if (u32CALResult == (OPA_CALST_CALNS0_Msk|OPA_CALST_CALPS0_Msk))
    {
        i32Ret = -3L;
    }

    return i32Ret;
}

/**
  * @brief This macro is used to generate asynchronous reset signals to OPA controller
  * @param    None
  * @return   None
  * \hideinitializer
  */
#define OPA_Reset() \
do { \
    SYS->IPRST2 |= SYS_IPRST2_OPARST_Msk; \
    SYS->IPRST2 &= ~SYS_IPRST2_OPARST_Msk; \
} while(0)

/*@}*/ /* end of group OPA_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group OPA_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __NU_OPA_H__ */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
