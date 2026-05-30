/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_exti.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#include "n32h76x_78x_exti.h"
#include "misc.h"

/**
*\*\name    EXTI_DeInit.
*\*\fun     Reset the EXTI registers.
*\*\param   Core_Type (The input parameters must be the following values):
*\*\          - CORE_M7
*\*\          - CORE_M4
*\*\return  none
**/
void EXTI_DeInit(void)
{
    EXTI->RT_CFG[0] = 0x00000000;
    EXTI->RT_CFG[1] = 0x00000000;
    EXTI->FT_CFG[0] = 0x00000000;
    EXTI->FT_CFG[1] = 0x00000000;
    EXTI->TSSEL     = 0x00000000;

    if(Get_CurrentCPU() != CM7_CPU)
    {
        EXTI->M4IMASK[0] = 0x00000000;
        EXTI->M4IMASK[1] = 0x00000000;

        EXTI->M7EMASK[0] = 0x00000000;
        EXTI->M7EMASK[1] = 0x00000000;

        EXTI->M4PEND[0]  = 0xFFFFFFFF;
        EXTI->M4PEND[1]  = 0x0000FFFF;

        EXTI->M4IMASK_DRC[0] = 0x00000000;
        EXTI->M4IMASK_DRC[1] = 0x00000000;

        EXTI->M4EMASK_DRC[0] = 0x00000000;
        EXTI->M4EMASK_DRC[1] = 0x00000000;
    }
    else
    {
        EXTI->M7IMASK[0] = 0x00000000;
        EXTI->M7IMASK[1] = 0x00000000;

        EXTI->M7EMASK[0] = 0x00000000;
        EXTI->M7EMASK[1] = 0x00000000;

        EXTI->M7PEND[0]  = 0xFFFFFFFF;
        EXTI->M7PEND[1]  = 0x0000FFFF;

        EXTI->M7IMASK_DRC[0] = 0x00000000;
        EXTI->M7IMASK_DRC[1] = 0x00000000;

        EXTI->M7EMASK_DRC[0] = 0x00000000;
        EXTI->M7EMASK_DRC[1] = 0x00000000;
    }
}

/**
*\*\name    EXTI_InitPeripheral.
*\*\fun     Initializes the EXTI according to EXTI_InitStruct.
*\*\param   EXTI_InitStruct(The input parameters must be the following values) :
*\*\param   EXTI_Line
*\*\            - EXTI_LINE0
*\*\            - EXTI_LINE1
*\*\            - EXTI_LINE2
*\*\            - EXTI_LINE3
*\*\            - EXTI_LINE4
*\*\            - EXTI_LINE5
*\*\            - EXTI_LINE6
*\*\            - EXTI_LINE7
*\*\            - EXTI_LINE8
*\*\            - EXTI_LINE9
*\*\            - EXTI_LINE10
*\*\            - EXTI_LINE11
*\*\            - EXTI_LINE12
*\*\            - EXTI_LINE13
*\*\            - EXTI_LINE14
*\*\            - EXTI_LINE15
*\*\            - EXTI_LINE16
*\*\            - EXTI_LINE17
*\*\            - EXTI_LINE18
*\*\            - EXTI_LINE19
*\*\            - EXTI_LINE20
*\*\            - EXTI_LINE21
*\*\            - EXTI_LINE22
*\*\            - EXTI_LINE23
*\*\            - EXTI_LINE24
*\*\            - EXTI_LINE25
*\*\            - EXTI_LINE49
*\*\            - EXTI_LINE51
*\*\            - EXTI_LINE52
*\*\            - EXTI_LINE54
*\*\            - EXTI_LINE55
*\*\            - EXTI_LINE56
*\*\            - EXTI_LINE62
*\*\            - EXTI_LINE63
*\*\            - EXTI_LINE64
*\*\            - EXTI_LINE65
*\*\            - EXTI_LINE66
*\*\            - EXTI_LINE67
*\*\            - EXTI_LINE68
*\*\            - EXTI_LINE69
*\*\            - EXTI_LINE70
*\*\            - EXTI_LINE71
*\*\            - EXTI_LINE72
*\*\            - EXTI_LINE73
*\*\            - EXTI_LINE74
*\*\            - EXTI_LINE75
*\*\            - EXTI_LINE76
*\*\            - EXTI_LINE77
*\*\            - EXTI_LINE78
*\*\            - EXTI_LINE79
*\*\            - EXTI_LINE80
*\*\            - EXTI_LINE81
*\*\            - EXTI_LINE82
*\*\            - EXTI_LINE83
*\*\            - EXTI_LINE84
*\*\            - EXTI_LINE85
*\*\            - EXTI_LINE86
*\*\            - EXTI_LINE87
*\*\            - EXTI_LINE88
*\*\            - EXTI_LINE89
*\*\          - EXTI_Mode
*\*\            - EXTI_Mode_Interrupt
*\*\            - EXTI_Mode_Event
*\*\          - EXTI_Trigger
*\*\            - EXTI_Trigger_Falling
*\*\            - EXTI_Trigger_Rising
*\*\            - EXTI_Trigger_Rising_Falling
*\*\          - EXTI_LineCmd:
*\*\            - ENABLE
*\*\            - DISABLE
*\*\return  none
**/
void EXTI_InitPeripheral(EXTI_InitType* EXTI_InitStruct)
{
    uint32_t tmpregister;
    uint32_t temp;
    uint32_t exti_index;
    uint32_t cpu_offset = 0;
    uint8_t  temp_index;

    if(Get_CurrentCPU() != CM7_CPU)
    {
        cpu_offset = 0x20;
    }

    if(EXTI_InitStruct->EXTI_Line >= 100)
    {
        cpu_offset += 0xC0;
        EXTI_InitStruct->EXTI_Line -= 100;
    }

    temp_index = EXTI_InitStruct->EXTI_Line / 32;
    exti_index = (uint32_t)0x00000001 << (EXTI_InitStruct->EXTI_Line % 32);

    tmpregister = (uint32_t)EXTI_BASE + (uint32_t)EXTI_InitStruct->EXTI_Mode + cpu_offset + 4 * temp_index;

    if (EXTI_InitStruct->EXTI_LineCmd != DISABLE)
    {
        /* Clear EXTI line interrupt/event configuration */
        *(__IO uint32_t*)tmpregister &= ~exti_index;

        if(EXTI_InitStruct->EXTI_Mode == EXTI_Mode_Interrupt)
        {
            temp = tmpregister + 0x40;
        }
        else
        {
            temp = tmpregister - 0x40;
        }

        /* Clear EXTI line interrupt/event configuration */
        *(__IO uint32_t*)temp &= ~exti_index;

        if(cpu_offset < 0xC0)
        {
            /* Select the trigger for the selected external interrupts */
            if (EXTI_InitStruct->EXTI_Trigger == EXTI_Trigger_Rising_Falling)
            {
                /* Rising Falling edge */
                EXTI->RT_CFG[temp_index] |= exti_index;
                EXTI->FT_CFG[temp_index] |= exti_index;
            }
            else
            {
                /* Clear Rising Falling edge configuration */
                EXTI->RT_CFG[temp_index] &= ~exti_index;
                EXTI->FT_CFG[temp_index] &= ~exti_index;

                temp = (uint32_t)EXTI_BASE + (uint32_t)EXTI_InitStruct->EXTI_Trigger + 4 * temp_index;

                /* Clear EXTI line event/interrupt configuration */
                *(__IO uint32_t*)temp |= exti_index;
            }
        }

        /* Enable EXTI line event configuration */
        *(__IO uint32_t*)tmpregister |= exti_index;
    }
    else
    {
        /* Disable the selected external lines */
        *(__IO uint32_t*)tmpregister &= ~(exti_index);
    }

}


/**
*\*\name    EXTI_InitStruct.
*\*\fun     Fills each EXTI_InitStruct member with its default value.
*\*\param   InitStruct :
*\*\            - - Pointer to the EXTI_InitType structure which will be initialized.
*\*\return  none
**/
void EXTI_InitStruct(EXTI_InitType* EXTI_InitStruct )
{
    EXTI_InitStruct->EXTI_Line      = EXTI_LINE0;
    EXTI_InitStruct->EXTI_Mode      = EXTI_Mode_Interrupt;
    EXTI_InitStruct->EXTI_Trigger   = EXTI_Trigger_Falling;
    EXTI_InitStruct->EXTI_LineCmd   = DISABLE;
}

/**
*\*\name    EXTI_TriggerSWInt.
*\*\fun     Generates a Software interrupt.
*\*\param   EXTI_Line
*\*\            - EXTI_LINE0
*\*\            - EXTI_LINE1
*\*\            - EXTI_LINE2
*\*\            - EXTI_LINE3
*\*\            - EXTI_LINE4
*\*\            - EXTI_LINE5
*\*\            - EXTI_LINE6
*\*\            - EXTI_LINE7
*\*\            - EXTI_LINE8
*\*\            - EXTI_LINE9
*\*\            - EXTI_LINE10
*\*\            - EXTI_LINE11
*\*\            - EXTI_LINE12
*\*\            - EXTI_LINE13
*\*\            - EXTI_LINE14
*\*\            - EXTI_LINE15
*\*\            - EXTI_LINE16
*\*\            - EXTI_LINE17
*\*\            - EXTI_LINE18
*\*\            - EXTI_LINE19
*\*\            - EXTI_LINE20
*\*\            - EXTI_LINE21
*\*\            - EXTI_LINE22
*\*\            - EXTI_LINE23
*\*\            - EXTI_LINE49
*\*\            - EXTI_LINE52
*\*\            - EXTI_LINE62
*\*\            - EXTI_LINE63
*\*\            - EXTI_LINE64
*\*\            - EXTI_LINE65
*\*\            - EXTI_LINE66
*\*\            - EXTI_LINE67
*\*\            - EXTI_LINE68
*\*\            - EXTI_LINE69
*\*\            - EXTI_LINE70
*\*\            - EXTI_LINE71
*\*\            - EXTI_LINE72
*\*\            - EXTI_LINE73
*\*\            - EXTI_LINE74
*\*\            - EXTI_LINE75
*\*\            - EXTI_LINE81
*\*\            - EXTI_LINE82
*\*\            - EXTI_LINE86
*\*\            - EXTI_LINE87
*\*\            - EXTI_LINE88
*\*\            - EXTI_LINE89
*\*\return  none
**/
void EXTI_TriggerSWInt(uint32_t EXTI_Line)
{
    if(EXTI_Line < 100)
    {
        EXTI->SWIE[EXTI_Line / 32] |= (uint32_t)0x00000001 << (EXTI_Line % 32);
    }
}

/**
*\*\name    EXTI_Flag_Status_Get.
*\*\fun     Get EXTI line flag status.
*\*\param   EXTI_Line
*\*\            - EXTI_LINE0
*\*\            - EXTI_LINE1
*\*\            - EXTI_LINE2
*\*\            - EXTI_LINE3
*\*\            - EXTI_LINE4
*\*\            - EXTI_LINE5
*\*\            - EXTI_LINE6
*\*\            - EXTI_LINE7
*\*\            - EXTI_LINE8
*\*\            - EXTI_LINE9
*\*\            - EXTI_LINE10
*\*\            - EXTI_LINE11
*\*\            - EXTI_LINE12
*\*\            - EXTI_LINE13
*\*\            - EXTI_LINE14
*\*\            - EXTI_LINE15
*\*\            - EXTI_LINE16
*\*\            - EXTI_LINE17
*\*\            - EXTI_LINE18
*\*\            - EXTI_LINE19
*\*\            - EXTI_LINE20
*\*\            - EXTI_LINE21
*\*\            - EXTI_LINE22
*\*\            - EXTI_LINE23
*\*\            - EXTI_LINE49
*\*\            - EXTI_LINE52
*\*\            - EXTI_LINE62
*\*\            - EXTI_LINE63
*\*\            - EXTI_LINE64
*\*\            - EXTI_LINE65
*\*\            - EXTI_LINE66
*\*\            - EXTI_LINE67
*\*\            - EXTI_LINE68
*\*\            - EXTI_LINE69
*\*\            - EXTI_LINE70
*\*\            - EXTI_LINE71
*\*\            - EXTI_LINE72
*\*\            - EXTI_LINE73
*\*\            - EXTI_LINE74
*\*\            - EXTI_LINE75
*\*\            - EXTI_LINE81
*\*\            - EXTI_LINE82
*\*\            - EXTI_LINE86
*\*\            - EXTI_LINE87
*\*\            - EXTI_LINE88
*\*\            - EXTI_LINE89
*\*\return  SET or RESET
**/
FlagStatus EXTI_GetStatusFlag(uint32_t EXTI_Line)
{
    FlagStatus bitstatus = RESET;
    uint32_t line_index;

    if(EXTI_Line < 100)
    {
        line_index = (uint32_t)0x00000001 << (EXTI_Line % 32);

        if (Get_CurrentCPU() != CM7_CPU)
        {
            if (( EXTI->M4PEND[EXTI_Line / 32] & line_index ) != ( uint32_t )RESET )
            {
                bitstatus = SET;
            }
            else
            {
                bitstatus = RESET;
            }

            return bitstatus;
        }
        else
        {
            if (( EXTI->M7PEND[EXTI_Line / 32] & line_index ) != ( uint32_t )RESET )
            {
                bitstatus = SET;
            }
            else
            {
                bitstatus = RESET;
            }

            return bitstatus;
        }
    }

    return bitstatus;
}

/**
*\*\name    EXTI_ClrStatusFlag.
*\*\fun     Clear EXTI line flag status.
*\*\param   EXTI_Line:
*\*\            - EXTI_LINE0
*\*\            - EXTI_LINE1
*\*\            - EXTI_LINE2
*\*\            - EXTI_LINE3
*\*\            - EXTI_LINE4
*\*\            - EXTI_LINE5
*\*\            - EXTI_LINE6
*\*\            - EXTI_LINE7
*\*\            - EXTI_LINE8
*\*\            - EXTI_LINE9
*\*\            - EXTI_LINE10
*\*\            - EXTI_LINE11
*\*\            - EXTI_LINE12
*\*\            - EXTI_LINE13
*\*\            - EXTI_LINE14
*\*\            - EXTI_LINE15
*\*\            - EXTI_LINE16
*\*\            - EXTI_LINE17
*\*\            - EXTI_LINE18
*\*\            - EXTI_LINE19
*\*\            - EXTI_LINE20
*\*\            - EXTI_LINE21
*\*\            - EXTI_LINE22
*\*\            - EXTI_LINE23
*\*\            - EXTI_LINE49
*\*\            - EXTI_LINE52
*\*\            - EXTI_LINE62
*\*\            - EXTI_LINE63
*\*\            - EXTI_LINE64
*\*\            - EXTI_LINE65
*\*\            - EXTI_LINE66
*\*\            - EXTI_LINE67
*\*\            - EXTI_LINE68
*\*\            - EXTI_LINE69
*\*\            - EXTI_LINE70
*\*\            - EXTI_LINE71
*\*\            - EXTI_LINE72
*\*\            - EXTI_LINE73
*\*\            - EXTI_LINE74
*\*\            - EXTI_LINE75
*\*\            - EXTI_LINE81
*\*\            - EXTI_LINE82
*\*\            - EXTI_LINE86
*\*\            - EXTI_LINE87
*\*\            - EXTI_LINE88
*\*\            - EXTI_LINE89
*\*\return  none
**/
void EXTI_ClrStatusFlag(uint32_t EXTI_Line)
{
    uint32_t line_index;

    if(EXTI_Line < 100)
    {
        line_index = (uint32_t)0x00000001 << (EXTI_Line % 32);

        if (Get_CurrentCPU() != CM7_CPU)
        {
            EXTI->M4PEND[EXTI_Line / 32] = line_index;
        }
        else
        {
            EXTI->M7PEND[EXTI_Line / 32] = line_index;
        }
    }
}

/**
*\*\name    EXTI_GetITStatus.
*\*\fun     GET EXTI line interrupt status.
*\*\param   EXTI_Line
*\*\            - EXTI_LINE0
*\*\            - EXTI_LINE1
*\*\            - EXTI_LINE2
*\*\            - EXTI_LINE3
*\*\            - EXTI_LINE4
*\*\            - EXTI_LINE5
*\*\            - EXTI_LINE6
*\*\            - EXTI_LINE7
*\*\            - EXTI_LINE8
*\*\            - EXTI_LINE9
*\*\            - EXTI_LINE10
*\*\            - EXTI_LINE11
*\*\            - EXTI_LINE12
*\*\            - EXTI_LINE13
*\*\            - EXTI_LINE14
*\*\            - EXTI_LINE15
*\*\            - EXTI_LINE16
*\*\            - EXTI_LINE17
*\*\            - EXTI_LINE18
*\*\            - EXTI_LINE19
*\*\            - EXTI_LINE20
*\*\            - EXTI_LINE21
*\*\            - EXTI_LINE22
*\*\            - EXTI_LINE23
*\*\            - EXTI_LINE49
*\*\            - EXTI_LINE52
*\*\            - EXTI_LINE62
*\*\            - EXTI_LINE63
*\*\            - EXTI_LINE64
*\*\            - EXTI_LINE65
*\*\            - EXTI_LINE66
*\*\            - EXTI_LINE67
*\*\            - EXTI_LINE68
*\*\            - EXTI_LINE69
*\*\            - EXTI_LINE70
*\*\            - EXTI_LINE71
*\*\            - EXTI_LINE72
*\*\            - EXTI_LINE73
*\*\            - EXTI_LINE74
*\*\            - EXTI_LINE75
*\*\            - EXTI_LINE81
*\*\            - EXTI_LINE82
*\*\            - EXTI_LINE86
*\*\            - EXTI_LINE87
*\*\            - EXTI_LINE88
*\*\            - EXTI_LINE89
*\*\return  SET or RESET
**/
ITStatus EXTI_GetITStatus( uint32_t EXTI_Line)
{
    ITStatus bitstatus = RESET;
    uint32_t enablestatus = 0;
    uint32_t line_index;
    uint8_t temp_index;

    if(EXTI_Line < 100)
    {
        temp_index = EXTI_Line / 32;
        line_index = (uint32_t)0x00000001 << (EXTI_Line % 32);

        if (Get_CurrentCPU() != CM7_CPU)
        {
            enablestatus =  EXTI->M4IMASK[temp_index] & line_index;

            if ((( EXTI->M4PEND[temp_index] & line_index ) != ( uint32_t )RESET) && ( enablestatus != ( uint32_t )RESET ))
            {
                bitstatus = SET;
            }
            else
            {
                bitstatus = RESET;
            }

            return bitstatus;
        }
        else
        {
            enablestatus =  EXTI->M7IMASK[temp_index] & line_index;

            if ((( EXTI->M7PEND[temp_index] & line_index ) != ( uint32_t )RESET) && ( enablestatus != ( uint32_t )RESET ))
            {
                bitstatus = SET;
            }
            else
            {
                bitstatus = RESET;
            }

            return bitstatus;
        }
    }

    return bitstatus;
}

/**
*\*\name    EXTI_ClrITPendBit.
*\*\fun     Clear EXTI line interrupt pend bit.
*\*\param   EXTI_Line
*\*\            - EXTI_LINE0
*\*\            - EXTI_LINE1
*\*\            - EXTI_LINE2
*\*\            - EXTI_LINE3
*\*\            - EXTI_LINE4
*\*\            - EXTI_LINE5
*\*\            - EXTI_LINE6
*\*\            - EXTI_LINE7
*\*\            - EXTI_LINE8
*\*\            - EXTI_LINE9
*\*\            - EXTI_LINE10
*\*\            - EXTI_LINE11
*\*\            - EXTI_LINE12
*\*\            - EXTI_LINE13
*\*\            - EXTI_LINE14
*\*\            - EXTI_LINE15
*\*\            - EXTI_LINE16
*\*\            - EXTI_LINE17
*\*\            - EXTI_LINE18
*\*\            - EXTI_LINE19
*\*\            - EXTI_LINE20
*\*\            - EXTI_LINE21
*\*\            - EXTI_LINE22
*\*\            - EXTI_LINE23
*\*\            - EXTI_LINE49
*\*\            - EXTI_LINE52
*\*\            - EXTI_LINE62
*\*\            - EXTI_LINE63
*\*\            - EXTI_LINE64
*\*\            - EXTI_LINE65
*\*\            - EXTI_LINE66
*\*\            - EXTI_LINE67
*\*\            - EXTI_LINE68
*\*\            - EXTI_LINE69
*\*\            - EXTI_LINE70
*\*\            - EXTI_LINE71
*\*\            - EXTI_LINE72
*\*\            - EXTI_LINE73
*\*\            - EXTI_LINE74
*\*\            - EXTI_LINE75
*\*\            - EXTI_LINE81
*\*\            - EXTI_LINE82
*\*\            - EXTI_LINE86
*\*\            - EXTI_LINE87
*\*\            - EXTI_LINE88
*\*\            - EXTI_LINE89
*\*\return  none
**/
void EXTI_ClrITPendBit( uint32_t EXTI_Line)
{
    uint32_t line_index;

    if(EXTI_Line < 100)
    {
        line_index = (uint32_t)0x00000001 << EXTI_Line % 32;

        if (Get_CurrentCPU() != CM7_CPU)
        {
            EXTI->M4PEND[EXTI_Line / 32] = line_index;
        }
        else
        {
            EXTI->M7PEND[EXTI_Line / 32] = line_index;
        }
    }
}

/**
*\*\name    EXTI_RTCTimeStampSel.
*\*\fun     Select the input of TimeStamp event.
*\*\param   EXTI_TSSEL_Line :
*\*\            - EXTI_TSSEL_LINE0
*\*\            - EXTI_TSSEL_LINE1
*\*\            - EXTI_TSSEL_LINE2
*\*\            - EXTI_TSSEL_LINE3
*\*\            - EXTI_TSSEL_LINE4
*\*\            - EXTI_TSSEL_LINE5
*\*\            - EXTI_TSSEL_LINE6
*\*\            - EXTI_TSSEL_LINE7
*\*\            - EXTI_TSSEL_LINE8
*\*\            - EXTI_TSSEL_LINE9
*\*\            - EXTI_TSSEL_LINE10
*\*\            - EXTI_TSSEL_LINE11
*\*\            - EXTI_TSSEL_LINE12
*\*\            - EXTI_TSSEL_LINE13
*\*\            - EXTI_TSSEL_LINE14
*\*\            - EXTI_TSSEL_LINE15
*\*\return  none
**/
void EXTI_RTCTimeStampSel(uint32_t EXTI_TSSEL_Line)
{
    uint32_t tempReg;

    tempReg = EXTI->TSSEL;

    tempReg &= ~EXTI_TSSEL_LINE_MASK;
    tempReg |= EXTI_TSSEL_Line;

    EXTI->TSSEL = tempReg;
}

