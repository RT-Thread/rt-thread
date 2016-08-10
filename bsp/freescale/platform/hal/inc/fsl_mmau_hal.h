/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
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

#ifndef __FSL_MMAU_HAL_H__
#define __FSL_MMAU_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"
#include "fsl_mmau_ins.h"

/*!
 * @addtogroup mmau_hal MMAU Hardware Abstraction Layer
 * @{
 */
 
/*! @file*/

/******************************************************************************
 * Definitions
 *****************************************************************************/
/*! 
 * @addtogroup mmau_int_sources MMAU Interrupt Sources
 * @{
 */
#define INT_MMAU_QIE  (1U<<12)  /*!< Accumulation Overflow Interrupt Enable. */
#define INT_MMAU_VIE  (1U<<13)  /*!< Multiply or Divide Overflow Interrupt Enable. */
#define INT_MMAU_DZIE (1U<<14)  /*!< Divide by Zero Interrupt Enable. */
/*@}*/

/*! 
 * @addtogroup mmau_int_flags MMAU Interrupt Flags
 * @{
 */
#define INT_MMAU_QIF  (1U<<4)   /*!< Accumulation Overflow Interrupt Flag. */
#define INT_MMAU_VIF  (1U<<5)   /*!< Multiply or Divide Overflow Interrupt Flag. */
#define INT_MMAU_DZIF (1U<<6)   /*!< Divide by Zero Interrupt Flag. */
/*@}*/

/*! 
 * @addtogroup mmau_ins_result_flags MMAU Instruction Result Flags
 * @{
 */
#define INS_MMAU_Q    (1U<<0)   /*!< Accumulation Overflow. */
#define INS_MMAU_V    (1U<<1)   /*!< Multiply or Divide Overflow. */
#define INS_MMAU_DZ   (1U<<2)	  /*!< Divide by Zero. */
#define INS_MMAU_N    (1U<<3)   /*!< Signed calculation result is negative. */
/*@}*/

/*!
 * @brief MMAU status return codes.
 */
typedef enum _mmau_status
{
    kStatus_MMAU_Success         = 0U, /*!< Success. */
    kStatus_MMAU_InvalidArgument = 1U, /*!< Invalid argument existed. */
    kStatus_MMAU_Failed          = 2U  /*!< Execution failed. */
} mmau_status_t;   

   
/*!
 * @brief Defines the structure to configure the MMAU.
 * @internal gui name="MMAU configuration" id="MmauConfig"
 */
typedef struct MmauUserConfig
{
    uint32_t mmauIntReqMask;     /*!< Enable interrupt request sources: INT_MMAU_QIE|INT_MMAU_VIE|INT_MMAU_DZIE. @internal gui name="Interrupt request sources" id="IntRequestSrc" range="0..28672" */
    bool mmauDmaReq;             /*!< Enable (true) or disable (false) DMA request when MMAU is in IDLE (not busy) state. @internal gui name="DMA requests when MMAU is in IDLE state" id="DmaRequest" */
    bool mmauAccess;             /*!< MMAU registers can only be accessed in Supervisor Mode (true) or in both User Mode or Supervisor Mode (false). @internal gui name="MMAU registers can only be accessed in Supervisor Mode" id="RegisterAccess"*/
} mmau_user_config_t;

/*!
 * @brief Defines the structure to hold states of the MMAU registers.
 */
typedef struct MmauRegState
{ 
    uint32_t  x0;                 /*!< X0 Operand Register. */
    uint32_t  x1;                 /*!< X1 Operand Register. */
    uint32_t  x2;                 /*!< X2 Operand Register. */
    uint32_t  x3;                 /*!< X3 Operand Register. */
    uint32_t  a0;                 /*!< A0 Accumulator Register. */  
    uint32_t  a1;                 /*!< A1 Accumulator Register. */
    uint32_t  csr;                /*!< CSR Control/Status Register. */
} mmau_reg_state_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif
  
/*!
 * @brief Resets the control/status register into a reset state.
 *
 * This function resets the control/status register to a known state. This state is
 * defined in a Reference Manual, which is power on reset value. This function must
 * execute in a Supervisor Mode.
 *
 * @param base Peripheral MMAU base pointer.  
 */
void MMAU_HAL_Init(MMAU_Type* base);

/*!
 * @brief Configures the MMAU.
 *
 * This function configures the MMAU.
 * 
 * @param base Peripheral MMAU base pointer.
 * @param configStructPtr MMAU configuration structure.
 */
void MMAU_HAL_Config(MMAU_Type* base, const mmau_user_config_t * configStructPtr);

/*!
 * @brief Sets the interrupt request sources.
 * 
 * This function sets the interrupt request sources.
 * 
 * @param base Peripheral MMAU base pointer.
 * @param mask Mask of the MMAU interrupts to be enabled (INT_MMAU_QIE|INT_MMAU_VIE|INT_MMAU_DZIE).
 */
static inline void MMAU_HAL_SetIntCmd(MMAU_Type* base, uint32_t mask)
{
    register uint32_t tmp;
 
    tmp = MMAU_RD_CSR(base)&~(INT_MMAU_QIE|INT_MMAU_VIE|INT_MMAU_DZIE);
  
    MMAU_WR_CSR(base, tmp|mask);
}

/*!
 * @brief Gets the instruction result flags.
 * 
 * This function gets the instruction result flags. Instruction result flags are updated by the MMAU after the computation of each instruction. 
 * 
 * @param base Peripheral MMAU base pointer.
 * @return Mask of the instruction result flags (INS_MMAU_Q|INS_MMAU_V|INS_MMAU_DZ|INS_MMAU_N).
 */
static inline uint32_t MMAU_HAL_GetInstrFlagsCmd(MMAU_Type* base)
{
    return MMAU_RD_CSR(base)&(INS_MMAU_Q|INS_MMAU_V|INS_MMAU_DZ|INS_MMAU_N);
}

/*!
 * @brief Writes the instruction result flags.
 * 
 * This function writes the instruction result flags.
 * 
 * @param base Peripheral MMAU base pointer.
 * @param mask Mask of the instruction result flags to be written (INS_MMAU_Q|INS_MMAU_V|INS_MMAU_DZ|INS_MMAU_N).
 */
static inline void MMAU_HAL_WriteInstrFlagsCmd(MMAU_Type* base, uint32_t mask)
{
    MMAU_WR_CSR_IF_CLR (base, mask);
}

/*!
 * @brief Gets MMAU state.
 * 
 *  This function gets the state of the MMAU. It returns control/status register value.
 * 
 * @param base Peripheral MMAU base pointer.
 * @return Control/status register value.
 */
static inline uint32_t MMAU_HAL_GetStateCmd(MMAU_Type* base)
{
  return MMAU_RD_CSR(base);
}

/*!
 * @brief Gets interrupt flags.
 *
 * This function gets the interrupt flags.
 *
 * @param base Peripheral MMAU base pointer.
 * @return Mask of the asserted interrupt flags (INT_MMAU_QIF|INT_MMAU_VIF|INT_MMAU_DZIF).
 */
static inline uint32_t MMAU_HAL_GetIntStatusFlagsCmd(MMAU_Type* base)
{
    return MMAU_RD_CSR(base)&(INT_MMAU_QIF|INT_MMAU_VIF|INT_MMAU_DZIF);
}

/*!
 * @brief Configures MMAU state.
 * 
 * This function configures MMAU state. It writes state into the control interrupt flag clear register.
 * 
 * @param state Value of a state of the MMAU.
 * @param base Peripheral MMAU base pointer.
 */
static inline void MMAU_HAL_ConfigStateCmd(MMAU_Type* base, uint32_t state)
{
    MMAU_WR_CSR_IF_CLR(base, state);
}

/*!
 * @brief Clears the interrupt flags.
 * 
 * This function clears the interrupt flags.
 * 
 * @param base Peripheral MMAU base pointer.
 * @param mask Mask of the MMAU interrupts to be cleared (INT_MMAU_QIF|INT_MMAU_VIF|INT_MMAU_DZIF).
 * @note This function preserves instruction result flags.
 */
static inline void MMAU_HAL_ClearIntStatusFlagsCmd(MMAU_Type* base, uint32_t mask)
{
    register uint32_t tmp;
 
    tmp = MMAU_RD_CSR(base)&(INS_MMAU_Q|INS_MMAU_V|INS_MMAU_DZ|INS_MMAU_N);
  
    MMAU_WR_CSR_IF_CLR(base, tmp|mask);
}
  
/*!
 * @brief Asserts the DMA request when in IDLE (not busy) state.
 * 
 * This function asserts the DMA request when in IDLE (not busy) state. After it is enabled, the DMA request is asserted 
 * when the BUSY flag is cleared.
 * 
 * @param base Peripheral MMAU base pointer.
 * @param enable Bool value for enabling (true) or disabling (false) DMA function.
 */
static inline void MMAU_HAL_SetDmaCmd(MMAU_Type* base, bool enable)
{
    MMAU_WR_CSR_DRE (base, enable);
}

/*!
 * @brief Sets access mode to the MMAU operand accumulator and control/status registers.
 * 
 * This function sets access mode to the MMAU operand, control, and status registers.
 * 
 * @param base Peripheral MMAU base pointer.
 * @param enable MMAU registers can only be accessed in Supervisor Mode (true) or 
 * in both User Mode or Supervisor Mode (false).
 */
static inline void MMAU_HAL_SetSupervisorOnlyCmd(MMAU_Type* base, bool enable)
{
    MMAU_WR_CSR_SO (base, enable);
}

/*!
 * @brief Gets the hardware revision level.
 * 
 * This function gets the hardware revision level of the MMAU. It returns HDR field of the control/status register.
 * 
 * @param base Peripheral MMAU base pointer.
 * @return uint32_t hardware revision level.
 */
static inline uint32_t MMAU_HAL_GetHwRevCmd(MMAU_Type* base)
{
    return MMAU_RD_CSR_HDR(base);
}

/*!
 * @brief Stores the MMAU operand and the control registers.
 *
 * This function stores MMAU operand and the control registers to the parameter p.
 *
 * @param base Peripheral MMAU base pointer.
 * @param p Pointer to the structure to store the MMAU registers.
 * @note This is an internal used function, it is recommend to use the function
 * MMAU_HAL_StoreRegStateCmd() instead.
 */
static inline void _store_mmau_state (MMAU_Type* base, volatile mmau_reg_state_t* p)
{
    p->x0 = base->X0;
    p->x1 = base->X1;
    p->x2 = base->X2;
    p->x3 = base->X3;
    p->a0 = base->A0;
    p->a1 = base->A1;
    p->csr = base->CSR;
}
/*!
 * @brief Stores the MMAU operand and control registers to the software stack.
 * 
 * This function stores the MMAU operand and control registers to the software stack. 
 * Call this function at the interrupt service routine entry.
 * 
 * @param base Peripheral MMAU base pointer.
 */
#define MMAU_HAL_StoreRegStateCmd(base)                                       \
                  volatile mmau_reg_state_t tmp; _store_mmau_state(base, &tmp)

/*!
 * @brief Restores the MMAU operand and control registers.
 *
 * This function restores the MMAU operand and control registers from the parameter p.
 *
 * @param base Peripheral MMAU base pointer.
 * @param p Pointer to the structure to restore the MMAU registers.
 * @note This is an internal used function, it is recommend to use the function
 * MMAU_HAL_RestoreRegStateCmd() instead.
 */
static inline void _restore_mmau_reg_state(MMAU_Type* base, volatile mmau_reg_state_t* p)
{
    base->X0 = p->x0;
    base->X1 = p->x1;
    base->X2 = p->x2;
    base->X3 = p->x3;
    base->A0 = p->a0;
    base->A1 = p->a1;
    base->CSR = p->csr;
}
/*!
 * @brief Restores the MMAU operand and control registers from the software stack.
 * 
 * This function restores the MMAU operand and control registers from the software stack. 
 * Call this function at exit the interrupt service routine.
 * 
 * @param base Peripheral MMAU base pointer.
 */
#define MMAU_HAL_RestoreRegStateCmd(base)                                     \
                  _restore_mmau_reg_state(base, &tmp)
  
/*@}*/

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */

#endif /* __FSL_MMAU_HAL_H__ */
/******************************************************************************
 * EOF
 *****************************************************************************/

