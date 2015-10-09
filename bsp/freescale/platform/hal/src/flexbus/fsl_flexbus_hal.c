/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "fsl_flexbus_hal.h"
#if FSL_FEATURE_SOC_FB_COUNT

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXBUS_HAL_Init
 * Description   : This function initializes the module to default state.
 *
 *END**************************************************************************/
void FLEXBUS_HAL_Init(FB_Type* base)
{
    int chip = 0;
    uint32_t reg_value = 0x0;

    for (chip = 0; chip < FB_CSAR_COUNT; chip++)
    {
        /* Reset CSMR register, all chips not valid (disabled).*/
        FB_WR_CSMR(base, chip, 0x0U);
        /* Set default base addr */
        FB_BWR_CSAR_BA(base, chip, 0x0000U);
        /* Reset FB_CSCRx register */
        FB_WR_CSCR(base, chip, 0x00U);
    }

    /* Set FB_CSPMCR register*/
    /* FlexBus signal group 1 multiplex control.*/
    reg_value |= kFlexbusMultiplexGroup1_FB_ALE << FB_CSPMCR_GROUP1_SHIFT;
    /* FlexBus signal group 2 multiplex control.*/
    reg_value |= kFlexbusMultiplexGroup2_FB_CS4 << FB_CSPMCR_GROUP2_SHIFT;
    /* FlexBus signal group 3 multiplex control.*/
    reg_value |= kFlexbusMultiplexGroup3_FB_CS5 << FB_CSPMCR_GROUP3_SHIFT;
    /* FlexBus signal group 4 multiplex control.*/
    reg_value |= kFlexbusMultiplexGroup4_FB_TBST << FB_CSPMCR_GROUP4_SHIFT;
    /* FlexBus signal group 5 multiplex control.*/
    reg_value |= kFlexbusMultiplexGroup5_FB_TA << FB_CSPMCR_GROUP5_SHIFT;
    /* Write to CSPMCR register.*/
    FB_WR_CSPMCR(base, reg_value);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXBUS_HAL_Configure
 * Description   : This function configures the module to a known state.
 *
 *END**************************************************************************/
void FLEXBUS_HAL_Configure(FB_Type* base, const flexbus_user_config_t* userConfigPtr)
{
    uint8_t chip = userConfigPtr->chip;
    uint32_t reg_value = 0x0;

    assert(chip < FB_CSAR_COUNT);
    assert(userConfigPtr->waitStates <= 0x3F);

    /* Base address.*/
    reg_value |= userConfigPtr->baseAddress;
    /* Write to CSAR register.*/
    FB_WR_CSAR(base, chip, reg_value);

    /* Chip-select validation.*/
    reg_value = 0x1 << FB_CSMR_V_SHIFT;
    /* Write protect.*/
    reg_value |= (uint32_t)(userConfigPtr->writeProtect ? 0x1 : 0x0 ) << FB_CSMR_WP_SHIFT;
    /* Base address mask.*/
    reg_value |= userConfigPtr->baseAddressMask << FB_CSMR_BAM_SHIFT;
    /* Write to CSMR register.*/
    FB_WR_CSMR(base, chip, reg_value);

    /* Burst write.*/
    reg_value = (uint32_t)(userConfigPtr->burstWrite ? 0x1 : 0x0) << FB_CSCR_BSTW_SHIFT;
    /* Burst read.*/
    reg_value |= (uint32_t)(userConfigPtr->burstRead ? 0x1 : 0x0) << FB_CSCR_BSTR_SHIFT;
    /* Byte-enable mode.*/
    reg_value |= (uint32_t)(userConfigPtr->byteEnableMode ? 0x1 : 0x0) << FB_CSCR_BEM_SHIFT;
    /* Port size.*/
    reg_value |= (uint32_t)userConfigPtr->portSize << FB_CSCR_PS_SHIFT;
    /* The internal transfer acknowledge for accesses.*/
    reg_value |= (uint32_t)(userConfigPtr->autoAcknowledge ? 0x1 : 0x0) << FB_CSCR_AA_SHIFT;
    /* Byte-Lane shift.*/
    reg_value |= (uint32_t)userConfigPtr->byteLaneShift << FB_CSCR_BLS_SHIFT;
    /* The number of wait states.*/
    reg_value |= (uint32_t)userConfigPtr->waitStates << FB_CSCR_WS_SHIFT;
    /* Write address hold or deselect.*/
    reg_value |= (uint32_t)userConfigPtr->writeAddressHold << FB_CSCR_WRAH_SHIFT;
    /* Read address hold or deselect.*/
    reg_value |= (uint32_t)userConfigPtr->readAddressHold << FB_CSCR_RDAH_SHIFT;
    /* Address setup.*/
    reg_value |= (uint32_t)userConfigPtr->addressSetup << FB_CSCR_ASET_SHIFT;
    /* Extended transfer start/extended address latch.*/
    reg_value |= (uint32_t)(userConfigPtr->extendTransferAddress ? 0x1 : 0x0) << FB_CSCR_EXTS_SHIFT;
    /* Secondary wait state.*/
    reg_value |= (uint32_t)(userConfigPtr->secondaryWaitStates ? 0x1 : 0x0) << FB_CSCR_SWSEN_SHIFT;
    /* Write to CSCR register.*/
    FB_WR_CSCR(base, chip, reg_value);

    /* FlexBus signal group 1 multiplex control.*/
    reg_value = (uint32_t)userConfigPtr->group1MultiplexControl << FB_CSPMCR_GROUP1_SHIFT;
    /* FlexBus signal group 2 multiplex control.*/
    reg_value |= (uint32_t)userConfigPtr->group2MultiplexControl << FB_CSPMCR_GROUP2_SHIFT;
    /* FlexBus signal group 3 multiplex control.*/
    reg_value |= (uint32_t)userConfigPtr->group3MultiplexControl << FB_CSPMCR_GROUP3_SHIFT;
    /* FlexBus signal group 4 multiplex control.*/
    reg_value |= (uint32_t)userConfigPtr->group4MultiplexControl << FB_CSPMCR_GROUP4_SHIFT;
    /* FlexBus signal group 5 multiplex control.*/
    reg_value |= (uint32_t)userConfigPtr->group5MultiplexControl << FB_CSPMCR_GROUP5_SHIFT;
    /* Write to CSPMCR register.*/
    FB_WR_CSPMCR(base, reg_value);
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/
