/***************************************************************************//**
* \file cy_crypto_core_hw_v1.c
* \version 2.70
*
* \brief
*  This file provides the source code for the HAL API for the
*  in the Crypto driver.
*
********************************************************************************
* \copyright
* Copyright (c) (2020-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include "cy_device.h"

#if defined(CY_IP_MXCRYPTO)

#include "cy_crypto_core_hw_v1.h"

#if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)

#if defined(__cplusplus)
extern "C" {
#endif

#include "cy_syslib.h"

/*******************************************************************************
* Function Name: Cy_Crypto_SetReg1Instr
****************************************************************************//**
*
* Writes one 32-Bit data word into Crypto FIFO.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param data0
* The address of data to be placed into Crypto FIFO
* on the address CRYPTO_REGFILE_R0.
*
*******************************************************************************/
void Cy_Crypto_SetReg1Instr(CRYPTO_Type *base, uint32_t data0)
{
    /* Check whether FIFO has enough space for 1 instruction */
    while(Cy_Crypto_Core_GetFIFOUsed(base) >= (CY_CRYPTO_INSTR_FIFODEPTH - 1u))
    {
    }

    REG_CRYPTO_INSTR_FF_WR(base) = (uint32_t)(((uint32_t)CY_CRYPTO_V1_SET_REG1_OPC << CY_CRYPTO_OPCODE_POS) |
                                   (uint32_t)CY_CRYPTO_REGFILE_R0);

    REG_CRYPTO_INSTR_FF_WR(base) = data0;
}

/*******************************************************************************
* Function Name: Cy_Crypto_SetReg2Instr
****************************************************************************//**
*
* Writes two 32-Bit data words into Crypto FIFO.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param data0
* The address of data to be placed into Crypto FIFO
* on the address CRYPTO_REGFILE_R0.
*
* \param data1
* The address of data to be placed into Crypto FIFO
* on the address CRYPTO_REGFILE_R1.
*
*******************************************************************************/
void Cy_Crypto_SetReg2Instr(CRYPTO_Type *base, uint32_t data0, uint32_t data1)
{
    /* Check whether FIFO has enough space for 2 instructions */
    while(Cy_Crypto_Core_GetFIFOUsed(base) >= (CY_CRYPTO_INSTR_FIFODEPTH - 2u))
    {
    }

    REG_CRYPTO_INSTR_FF_WR(base) = (uint32_t)(((uint32_t)CY_CRYPTO_V1_SET_REG2_OPC << CY_CRYPTO_OPCODE_POS) |
                                   ((uint32_t)CY_CRYPTO_REGFILE_R1 << CY_CRYPTO_RSRC4_SHIFT) |
                                   (uint32_t)CY_CRYPTO_REGFILE_R0);

    REG_CRYPTO_INSTR_FF_WR(base) = data0;
    REG_CRYPTO_INSTR_FF_WR(base) = data1;
}

/*******************************************************************************
* Function Name: Cy_Crypto_SetReg3Instr
****************************************************************************//**
*
* Writes three 32-Bit data words into Crypto FIFO.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param data0
* The address of data to be placed into Crypto FIFO
* on the address CRYPTO_REGFILE_R0.
*
* \param data1
* The address of data to be placed into Crypto FIFO
* on the address CRYPTO_REGFILE_R1.
*
* \param data2
* The address of data to be be placed into Crypto FIFO
* on the address CRYPTO_REGFILE_R2.
*
*******************************************************************************/
void Cy_Crypto_SetReg3Instr(CRYPTO_Type *base, uint32_t data0, uint32_t data1, uint32_t data2)
{
    /* Check whether FIFO has enough space for 3 instructions */
    while(Cy_Crypto_Core_GetFIFOUsed(base) >= (CY_CRYPTO_INSTR_FIFODEPTH - 3u))
    {
    }

    REG_CRYPTO_INSTR_FF_WR(base) = (uint32_t)( ((uint32_t)CY_CRYPTO_V1_SET_REG3_OPC << CY_CRYPTO_OPCODE_POS) |
                                   ((uint32_t)CY_CRYPTO_REGFILE_R2 << CY_CRYPTO_RSRC8_SHIFT) |
                                   ((uint32_t)CY_CRYPTO_REGFILE_R1 << CY_CRYPTO_RSRC4_SHIFT) |
                                   (uint32_t)CY_CRYPTO_REGFILE_R0 );

    REG_CRYPTO_INSTR_FF_WR(base) = data0;
    REG_CRYPTO_INSTR_FF_WR(base) = data1;
    REG_CRYPTO_INSTR_FF_WR(base) = data2;
}

/*******************************************************************************
* Function Name: Cy_Crypto_SetReg4Instr
****************************************************************************//**
*
* Writes four 32-Bit data words into Crypto FIFO.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param data0
* The address of data to be placed into Crypto FIFO
* on the address CRYPTO_REGFILE_R0.
*
* \param data1
* The address of data to be placed into Crypto FIFO
* on the address CRYPTO_REGFILE_R1.
*
* \param data2
* The address of data to be placed into Crypto FIFO
* on the address CRYPTO_REGFILE_R2.
*
* \param data3
* The address of data to be placed into Crypto FIFO
* on the address CRYPTO_REGFILE_R3.
*
*******************************************************************************/
void Cy_Crypto_SetReg4Instr(CRYPTO_Type *base, uint32_t data0, uint32_t data1, uint32_t data2, uint32_t data3)
{
    /* Check whether FIFO has enough space for 4 instructions */
    while(Cy_Crypto_Core_GetFIFOUsed(base) >= (CY_CRYPTO_INSTR_FIFODEPTH - 4u))
    {
    }

    REG_CRYPTO_INSTR_FF_WR(base) = (uint32_t)(((uint32_t)CY_CRYPTO_V1_SET_REG4_OPC << CY_CRYPTO_OPCODE_POS) |
                                   ((uint32_t)CY_CRYPTO_REGFILE_R3 << CY_CRYPTO_RSRC12_SHIFT) |
                                   ((uint32_t)CY_CRYPTO_REGFILE_R2 << CY_CRYPTO_RSRC8_SHIFT) |
                                   ((uint32_t)CY_CRYPTO_REGFILE_R1 << CY_CRYPTO_RSRC4_SHIFT) |
                                   (uint32_t)CY_CRYPTO_REGFILE_R0);

    REG_CRYPTO_INSTR_FF_WR(base) = data0;
    REG_CRYPTO_INSTR_FF_WR(base) = data1;
    REG_CRYPTO_INSTR_FF_WR(base) = data2;
    REG_CRYPTO_INSTR_FF_WR(base) = data3;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Run0ParamInstr
*****************************************************************************//**
*
* Run the Crypto instruction without parameters.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param instr
* The Opcode of the called instruction.
*
*******************************************************************************/
void Cy_Crypto_Run0ParamInstr(CRYPTO_Type *base, uint8_t instr)
{
    /* Check whether FIFO has enough space for 1 instruction */
    while(Cy_Crypto_Core_GetFIFOUsed(base) >= CY_CRYPTO_INSTR_FIFODEPTH)
    {
    }

    REG_CRYPTO_INSTR_FF_WR(base) = (uint32_t)((uint32_t)instr << CY_CRYPTO_OPCODE_POS);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Run1ParamInstr
*****************************************************************************//**
*
* Run the Crypto instruction with one parameter.
* The parameter must be placed into register 0
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param instr
* The Opcode of the called instruction.
*
* \param rdst0Shift
* The shift for the instruction operand.
*
*******************************************************************************/
void Cy_Crypto_Run1ParamInstr(CRYPTO_Type *base, uint8_t instr, uint32_t rdst0Shift)
{
    /* Check whether FIFO has enough space for 1 instruction */
    while(Cy_Crypto_Core_GetFIFOUsed(base) >= CY_CRYPTO_INSTR_FIFODEPTH)
    {
    }

    REG_CRYPTO_INSTR_FF_WR(base) = (uint32_t)(((uint32_t)instr << CY_CRYPTO_OPCODE_POS) |
                                   ((uint32_t)CY_CRYPTO_REGFILE_R0 << rdst0Shift));
}

/*******************************************************************************
* Function Name: Cy_Crypto_Run2ParamInstr
*****************************************************************************//**
*
* Run the Crypto instruction with two parameters.
* The zero parameter must be placed into register 0,
* the first parameter must be placed into register 1.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param instr
* The Opcode of the called instruction.
*
* \param rdst0Shift
* The shift for the zero instruction operand.
*
* \param rdst1Shift
* The shift for the second instruction operand.
*
*******************************************************************************/
void Cy_Crypto_Run2ParamInstr(CRYPTO_Type *base,
                           uint8_t instr,
                           uint32_t rdst0Shift,
                           uint32_t rdst1Shift)
{
    /* Check whether FIFO has enough space for 1 instruction */
    while(Cy_Crypto_Core_GetFIFOUsed(base) >= CY_CRYPTO_INSTR_FIFODEPTH)
    {
    }

    REG_CRYPTO_INSTR_FF_WR(base) = (uint32_t)(((uint32_t)instr << CY_CRYPTO_OPCODE_POS) |
                                   ((uint32_t)CY_CRYPTO_REGFILE_R1 << rdst1Shift) |
                                   ((uint32_t)CY_CRYPTO_REGFILE_R0 << rdst0Shift));
}

/*******************************************************************************
* Function Name: Cy_Crypto_Run3ParamInstr
*****************************************************************************//**
*
* Run the Crypto instruction with three parameters.
* The zero parameter must be placed into register 0,
* the first parameter must be placed into register 1,
* the second parameter must be placed into register 2.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param instr
* The Opcode of the called instruction.
*
* \param rdst0Shift
* The shift for the zero instruction operand.
*
* \param rdst1Shift
* The shift for the second instruction operand.
*
** \param rdst2Shift
* The shift for the second instruction operand.
*
*******************************************************************************/
void Cy_Crypto_Run3ParamInstr(CRYPTO_Type *base,
                           uint8_t instr,
                           uint8_t rdst0Shift,
                           uint8_t rdst1Shift,
                           uint8_t rdst2Shift)
{
    /* Check whether FIFO has enough space for 1 instruction */
    while(Cy_Crypto_Core_GetFIFOUsed(base) >= CY_CRYPTO_INSTR_FIFODEPTH)
    {
    }

    REG_CRYPTO_INSTR_FF_WR(base) = (uint32_t)(((uint32_t)instr << CY_CRYPTO_OPCODE_POS) |
                                   ((uint32_t)CY_CRYPTO_REGFILE_R2 << rdst2Shift) |
                                   ((uint32_t)CY_CRYPTO_REGFILE_R1 << rdst1Shift) |
                                   ((uint32_t)CY_CRYPTO_REGFILE_R0 << rdst0Shift));
}

/*******************************************************************************
* Function Name: Cy_Crypto_Run4ParamInstr
*****************************************************************************//**
*
* Run the Crypto instruction with four parameters.
* The zero parameter must be placed into register 0,
* the first parameter must be placed into register 1,
* the second parameter must be placed into register 2,
* the third parameter must be placed into register 3.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param instr
* The Opcode of the called instruction.
*
* \param rdst0Shift
* The shift for the zero instruction operand.
*
* \param rdst1Shift
* The shift for the first instruction operand.
*
* \param rdst2Shift
* The shift for the second instruction operand.
*
* \param rdst3Shift
* The shift for the third instruction operand.
*
*******************************************************************************/
void Cy_Crypto_Run4ParamInstr(CRYPTO_Type *base,
                           uint8_t instr,
                           uint32_t rdst0Shift,
                           uint32_t rdst1Shift,
                           uint32_t rdst2Shift,
                           uint32_t rdst3Shift)
{
    /* Check whether FIFO has enough space for 1 instruction */
    while(Cy_Crypto_Core_GetFIFOUsed(base) >= CY_CRYPTO_INSTR_FIFODEPTH)
    {
    }

    REG_CRYPTO_INSTR_FF_WR(base) = (uint32_t)(((uint32_t)instr << CY_CRYPTO_OPCODE_POS) |
                                   ((uint32_t)CY_CRYPTO_REGFILE_R3 << rdst3Shift) |
                                   ((uint32_t)CY_CRYPTO_REGFILE_R2 << rdst2Shift) |
                                   ((uint32_t)CY_CRYPTO_REGFILE_R1 << rdst1Shift) |
                                   ((uint32_t)CY_CRYPTO_REGFILE_R0 << rdst0Shift));
}

#if defined(__cplusplus)
}
#endif

#endif /* defined(CY_CRYPTO_CFG_HW_V1_ENABLE) */

#endif /* defined(CY_IP_MXCRYPTO) */


/* [] END OF FILE */
