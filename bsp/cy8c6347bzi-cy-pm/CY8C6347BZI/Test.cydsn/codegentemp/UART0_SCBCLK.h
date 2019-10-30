/***************************************************************************//**
* \file     UART0_SCBCLK.h
* \version  1.0
*
* \brief
* Provides the source code to the API for the UART0_SCBCLK Component.
*
********************************************************************************
* \copyright
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_UART0_SCBCLK_NAME_UART0_SCBCLK_H)
#define CY_UART0_SCBCLK_NAME_UART0_SCBCLK_H

/* For _DIV_TYPE and _DIV_NUM #defines */
#include "cyfitter.h"

/* makes uint32_t defined */
#include <stdint.h>

#include "sysclk/cy_sysclk.h"

/***************************************
* Preprocessor Macros
***************************************/
/**
* \addtogroup group_macros
* @{
*/
/** The peripheral clock divider number */
#define UART0_SCBCLK_DIV_NUM ((uint32_t)UART0_SCBCLK__DIV_NUM)
/** The peripheral clock divider type */
#define UART0_SCBCLK_DIV_TYPE ((cy_en_divider_types_t)UART0_SCBCLK__DIV_TYPE)
/** @} group_macros */

/***************************************
* Function Prototypes
***************************************/

/**
* \addtogroup group_general
* @{
*/

/*******************************************************************************
* Function Name: UART0_SCBCLK_Enable
****************************************************************************//**
*
* Enables the programmable clock divider assigned to this Component.
*
* \param None
*
* \return None
*
*******************************************************************************/
__STATIC_INLINE void UART0_SCBCLK_Enable(void)
{
    (void)Cy_SysClk_PeriphEnableDivider(UART0_SCBCLK_DIV_TYPE, UART0_SCBCLK_DIV_NUM);
}

/*******************************************************************************
* Function Name: UART0_SCBCLK_Disable
****************************************************************************//**
*
* Disables the programmable clock divider assigned to this Component.
*
* \param None
*
* \return None
*
*******************************************************************************/
__STATIC_INLINE void UART0_SCBCLK_Disable(void)
{
    (void)Cy_SysClk_PeriphDisableDivider(UART0_SCBCLK_DIV_TYPE, UART0_SCBCLK_DIV_NUM);
}

/*******************************************************************************
* Function Name: UART0_SCBCLK_SetDivider
****************************************************************************//**
*
* Sets the value of a programmable clock divider assigned to this Component.
* This is only used for integer dividers. Use UART0_SCBCLK_SetFracDivider()
* for setting factional dividers.
*
* \param dividerValue
* The divider value. The source of the divider is peri_clk which is a divided
* version of hf_clk[0]. The divider value causes integer division of
* (divider value + 1), or division by 1 to 256 (8-bit divider) or
* 1 to 65536 (16-bit divider).
*
* \return None
*
*******************************************************************************/
__STATIC_INLINE void UART0_SCBCLK_SetDivider(uint32_t dividerValue)
{
    (void)Cy_SysClk_PeriphSetDivider(UART0_SCBCLK_DIV_TYPE, UART0_SCBCLK_DIV_NUM, dividerValue);
}

/*******************************************************************************
* Function Name: UART0_SCBCLK_GetDivider
****************************************************************************//**
*
* Returns the integer divider value for the programmable clock divider assigned
* to this Component. This is only used for integer dividers.
* Use UART0_SCBCLK_GetFracDivider() with a fractional divider.
*
* \param None
*
* \return
* The divider value. The source of the divider is peri_clk which is a divided
* version of hf_clk[0]. The integer division done is by (divider value + 1),
* or division by 1 to 256 (8-bit divider) or 1 to 65536 (16-bit divider).
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART0_SCBCLK_GetDivider(void)
{
    return Cy_SysClk_PeriphGetDivider(UART0_SCBCLK_DIV_TYPE, UART0_SCBCLK_DIV_NUM);
}

/*******************************************************************************
* Function Name: UART0_SCBCLK_SetFracDivider
****************************************************************************//**
*
* Sets the values of a programmable clock divider assigned to this Component.
* This is only used for fractional dividers. Use UART0_SCBCLK_SetDivider()
* for setting integer dividers.
*
* \param dividerIntValue
* The integer divider value. The source of the divider is peri_clk which is a
* divided version of hf_clk[0]. The divider value causes integer division of
* (divider value + 1), or division by 1 to 65536 (16-bit divider) or
* 1 to 16777216 (24-bit divider).
*
* \param dividerFracValue
* This is the fraction piece of the divider. The fractional divider can be
* 0 - 31; it divides the clock by 1/32 for each count. To divide the clock by
* 11/32nds, set this value to 11.
*
* \return None
*
*******************************************************************************/
__STATIC_INLINE void UART0_SCBCLK_SetFracDivider(uint32_t dividerIntValue, uint32_t dividerFracValue)
{
    (void)Cy_SysClk_PeriphSetFracDivider(UART0_SCBCLK_DIV_TYPE, UART0_SCBCLK_DIV_NUM, dividerIntValue, dividerFracValue);
}

/*******************************************************************************
* Function Name: UART0_SCBCLK_GetFracDivider
****************************************************************************//**
*
* Returns the divider values for the programmable clock divider assigned to this
* Component. This is only used for fractional dividers.
* Use UART0_SCBCLK_GetDivider() with an integer divider.
*
* \param *dividerIntValue
* pointer to return integer divider value
*
* \param *dividerFracValue
* pointer to return fractional divider value
*
* \return None. Loads pointed-to variables.
*
*******************************************************************************/
__STATIC_INLINE void UART0_SCBCLK_GetFracDivider(uint32_t *dividerIntValue, uint32_t *dividerFracValue)
{
    Cy_SysClk_PeriphGetFracDivider(UART0_SCBCLK_DIV_TYPE, UART0_SCBCLK_DIV_NUM, dividerIntValue, dividerFracValue);
}

/** @} general */

#endif /* CY_CLOCK_UART0_SCBCLK_H */

/* [] END OF FILE */
