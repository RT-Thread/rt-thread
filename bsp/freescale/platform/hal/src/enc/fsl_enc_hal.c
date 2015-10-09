/*******************************************************************************
*
* Copyright [2014-]2014 Freescale Semiconductor, Inc.

*
* This software is owned or controlled by Freescale Semiconductor.
* Use of this software is governed by the Freescale License
* distributed with this Material.
* See the LICENSE file distributed for more details.
* 
*
*******************************************************************************/

#include "fsl_enc_hal.h"
#if FSL_FEATURE_SOC_ENC_COUNT

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : ENC_HAL_Init
 * Description   : Resets all configurable registers to be in the reset state for ENC.
 * This function resets all configurable registers to be in the reset state for ENC.
 * It should be called before configuring the ENC module.
 *
 *END**************************************************************************/
void ENC_HAL_Init(ENC_Type* base)
{
    /* Reset counter registers, compare and modulus register */    
    ENC_WR_FILT(base, 0U);
    ENC_WR_WTR(base, 0U);
    ENC_WR_POSD(base, 0U);
    ENC_WR_REV(base, 0U);
    ENC_WR_UPOS(base, 0U);
    ENC_WR_LPOS(base, 0U);
    ENC_WR_UINIT(base, 0U);
    ENC_WR_LINIT(base, 0U);
    ENC_WR_UMOD(base, 0U);
    ENC_WR_LMOD(base, 0U);
    ENC_WR_UCOMP(base, 0xFFFFU);
    ENC_WR_LCOMP(base, 0xFFFFU);
    
    /* Reset control registers */
    ENC_WR_CTRL(base, 0U);
    ENC_WR_CTRL2(base, 0U);
    ENC_WR_TST(base, 0U);
}
   
/*FUNCTION**********************************************************************
 *
 * Function Name : ENC_HAL_SetInputFilterSamplePeriod
 * Description   : Set Input Filter Sample Period.
 * This function allows the user to set the input filter sample period. This value
 * represents the sampling period of the decoder input signals.
 * If value is 0x00 (default), then the input filter is bypassed.
 *
 *END**************************************************************************/
void ENC_HAL_SetInputFilterSamplePeriod(ENC_Type* base, uint8_t samplePeriod)
{
    /* Writing value of 0 first in order to clear the filter */
    ENC_BWR_FILT_FILT_PER(base, 0);
    
    /* Writing requesting value */
    ENC_BWR_FILT_FILT_PER(base, samplePeriod);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ENC_HAL_GetPosCounterRegister
 * Description   : Reads Position Counter Register.
 * This function allows the user to read the Position counter.
 *
 *END**************************************************************************/
uint32_t ENC_HAL_GetPosCounterReg(ENC_Type* base)
{
    uint32_t lowerPosCntReg = (uint32_t) ENC_RD_LPOS(base);
    uint32_t upperPosCntReg = (uint32_t) ENC_RD_UPOS(base);
    
    return (uint32_t) ((upperPosCntReg << 16) | lowerPosCntReg);
}
    
/*FUNCTION**********************************************************************
 *
 * Function Name : ENC_HAL_SetPosCounterRegister
 * Description   : Writes Position Counter Register.
 * This function allows the user to write the Position counter.
 *
 *END**************************************************************************/
void ENC_HAL_SetPosCounterReg(ENC_Type* base, uint32_t posVal)
{
    ENC_WR_LPOS(base, (uint16_t) posVal);
    ENC_WR_UPOS(base, (uint16_t) (posVal >> 16));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ENC_HAL_GetPosHoldReg
 * Description   : Reads Position Hold Register.
 * This function allows the user to read the Position hold register.
 *
 *END**************************************************************************/
uint32_t ENC_HAL_GetPosHoldReg(ENC_Type* base)
{
    uint32_t upperPosHoldReg = (uint32_t) ENC_RD_UPOSH(base);
    uint32_t lowerPosHoldReg = (uint32_t) ENC_RD_LPOSH(base);
    
    return (uint32_t) ((upperPosHoldReg << 16) | lowerPosHoldReg);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ENC_HAL_SetInitReg
 * Description   : Writes Initialization Registers.
 * This function allows the user to write initialization registers.
 *
 *END**************************************************************************/
void ENC_HAL_SetInitReg(ENC_Type* base, uint32_t initValue)
{
    ENC_WR_LINIT(base, (uint16_t) initValue);
    ENC_WR_UINIT(base, (uint16_t) (initValue >> 16));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ENC_HAL_GetInitReg
 * Description   : Reads Initialization Registers.
 * This function allows the user to read initialization registers.
 *
 *END**************************************************************************/
uint32_t ENC_HAL_GetInitReg(ENC_Type* base)
{
    uint32_t upperInitReg = (uint32_t) ENC_RD_UINIT(base);
    uint32_t lowerInitReg = (uint32_t) ENC_RD_LINIT(base);
    
    return (uint32_t) ((upperInitReg << 16) | lowerInitReg);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ENC_HAL_SetModulusReg
 * Description   : Writes Modulus Register.
 * This function allows the user to write the ENC modulo register. Modulus
 * acts as the upper bound during modulo counting and as the upper reload value
 * when rolling over from the lower bound.
 *
 *END**************************************************************************/
void ENC_HAL_SetModulusReg(ENC_Type* base, uint32_t modValue)
{
    ENC_WR_LMOD(base, (uint16_t) modValue);
    ENC_WR_UMOD(base, (uint16_t) (modValue >> 16));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ENC_HAL_GetModulusRegister
 * Description   : Reads Modulus Register.
 * This function allows the user to read the ENC modulo register. Modulus
 * acts as the upper bound during modulo counting and as the upper reload value
 * when rolling over from the lower bound.
 *
 *END**************************************************************************/
uint32_t ENC_HAL_GetModulusReg(ENC_Type* base)
{
    uint32_t upperModuloReg = (uint32_t) ENC_RD_UMOD(base);
    uint32_t lowerModuloReg = (uint32_t) ENC_RD_LMOD(base);
    
    return (uint32_t) ((upperModuloReg << 16) | lowerModuloReg);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ENC_HAL_SetCmpRegister
 * Description   : Writes Compare Register.
 * This function allows the user to write the ENC compare register. When the
 * value of Position counter matches the value of Compare register 
 * the CTRL[CMPIRQ] flag is set and the POSMATCH output is asserted.
 *
 *END**************************************************************************/
void ENC_HAL_SetCmpReg(ENC_Type* base, uint32_t cmpValue)
{
    ENC_WR_LCOMP(base, (uint16_t) cmpValue);
    ENC_WR_UCOMP(base, (uint16_t) (cmpValue >> 16));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ENC_HAL_GetCmpRegister
 * Description   : Reads Compare Register.
 * This function allows the user to write the ENC compare register. When the
 * value of Position counter matches the value of Compare register 
 * the CTRL[CMPIRQ] flag is set and the POSMATCH output is asserted.
 *
 *END**************************************************************************/
uint32_t ENC_HAL_GetCmpReg(ENC_Type* base)
{
    uint32_t upperCompareReg = (uint32_t) ENC_RD_UCOMP(base);
    uint32_t lowerCompareReg = (uint32_t) ENC_RD_LCOMP(base);
    
    return (uint32_t) ((upperCompareReg << 16) | lowerCompareReg);
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/
