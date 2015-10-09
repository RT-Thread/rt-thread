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

#if !defined(__FSL_MMDVSQ_HAL_H__)
#define __FSL_MMDVSQ_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_MMDVSQ_COUNT

/*! @addtogroup mmdvsq_hal*/
/*! @{*/

/*! @file fsl_mmdvsq_hal.h */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief MMDVSQ execution status */
typedef enum _mmdvsq_execution_status
{
    kMmdvsqIdleSquareRoot       = 0x01, /* MMDVSQ is idle, last calculation was a square root */
    kMmdvsqIdleDivide           = 0x02, /* MMDVSQ is idle, last calculation was a divide */
    kMmdvsqBusySquareRoot       = 0x05, /* MMDVSQ is busy processing a square root calculation */
    kMmdvsqBusyDivide           = 0x06  /* MMDVSQ is busy processing a divide calculation */
} mmdvsq_execution_status_t;

/*! @brief MMDVSQ divide operation select */
typedef enum _mmdvsq_divide_opertion_select
{
    kMmdvsqSignedDivideGetQuotient,        	/*Select signed divide operation, return the quotient */
    kMmdvsqUnsignedDivideGetQuotient,   	/* Select unsigned divide operation, return the quotient */
    kMmdvsqSignedDivideGetRemainder,     	/* Select signed divide operation, return the remainder */
    kMmdvsqUnsignedDivideGetRemainder	    /* Select unsigned divide operation, return the remainder */
} mmdvsq_divide_operation_select_t;

/*! @brief MMDVSQ divide fast start select */
typedef enum _mmdvsq_divide_fast_start_select
{
    kMmdvsqDivideFastStart,     /* Divide operation is initiated by a write to the DSOR register */
    kMmdvsqDivideNormalStart	/* Divide operation is initiated by a write to CSR[SRT] = 1, normal start instead fast start*/
} mmdvsq_divide_fast_start_select_t;

/*! @brief MMDVSQ divide by zero setting*/
typedef enum _mmdvsq_divide_by_zero_select
{
    kMmdvsqDivideByZeroDis,    /* disable divide by zero detect */
    kMmdvsqDivideByZeroEn      /* enable divide by zero detect */
} mmdvsq_divide_by_zero_select_t;

/*! @brief MMDVSQ divide by zero status*/
typedef enum _mmdvsq_divide_by_zero_status
{
    kMmdvsqNonZeroDivisor,      /*Divisor is not zero*/
    kMmdvsqZeroDivisor          /*Divisor is zero */
} mmdvsq_divide_by_zero_status_t;

/*! @brief MMDVSQ unsigned or signed divide calculation select */
typedef enum _mmdvsq_unsigned_divide_select
{
    kMmdvsqSignedDivide,		/*Select signed divide operation*/
    kMmdvsqUnsignedDivide       	/* Select unsigned divide operation */
} mmdvsq_unsined_divide_select_t;


/*! @brief MMDVSQ remainder or quotient result select */
typedef enum _mmdvsq_remainder_calculation_select{
    kMmdvsqDivideReturnQuotient,    /*Return quotient in RES register*/
    kMmdvsqDivideReturnRemainder	/* Return remainder in RES register */
} mmdvsq_remainder_calculation_select_t;

/*! @brief MCG mode transition API error code definitions */
typedef enum _mmdvsq_error_code_t{
    /* MMDVSQ error codes */
    kMmdvsqErrNotReady          = 0x01,   /* - MMDVSQ is busy */
    kMmdvsqErrDivideTimeOut     = 0x02,   /* - MMDVSQ is busy in divide operation  */
    kMmdvsqErrSqrtTimeOut       = 0x03,   /* - MMDVSQ is busy in square root operation */
    kMmdvsqErrDivideByZero      = 0x04    /* - MMDVSQ is in divide operation, and the divisor is zer0 */    
} mmdvsq_error_code_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*! @name MMDVSQ operations access API*/
/*@{*/

/*!
 * @brief perform the current MMDVSQ  unsigned divide operation and get remainder 
 *
 * This function performs the MMDVSQ unsigned divide operation and get remainder. 
 * It is in block mode. For non-block mode, other HAL routines can be used.    
 *
 * @param	base	Base address for current MMDVSQ instance.    
 * @param	dividend   -Dividend value 
 * @param	divisor    -Divisor value 
 *  
 * @return  Unsigned divide calculation result in the MMDVSQ_RES register.
 */
uint32_t MMDVSQ_HAL_DivUR(MMDVSQ_Type * base, uint32_t dividend, uint32_t divisor);

/*!
 * @brief perform the current MMDVSQ unsigned divide operation and get quotient 
 *
 * This function performs the MMDVSQ unsigned divide operation and get quotient. 
 * It is in block mode. For non-block mode, other HAL routines can be used.
 *
 * @param	base	Base address for current MMDVSQ instance.    
 * @param	dividend   -Dividend value 
 * @param	divisor    -Divisor value 
 *  
 * @return  Unsigned divide calculation result in the MMDVSQ_RES register.
 */
uint32_t MMDVSQ_HAL_DivUQ(MMDVSQ_Type * base, uint32_t dividend, uint32_t divisor);


/*!
 * @brief perform the current MMDVSQ signed divide operation and get remainder 
 *
 * This function performs the MMDVSQ signed divide operation and get remainder. 
 * It is in block mode. For non-block mode, other HAL routines can be used. 
 *
 * @param	base	Base address for current MMDVSQ instance.    
 * @param	dividend   -Dividend value 
 * @param	divisor    -Divisor value 
 *  
 * @return  Signed divide calculation result in the MMDVSQ_RES register.
 */
uint32_t MMDVSQ_HAL_DivSR(MMDVSQ_Type * base, uint32_t dividend, uint32_t divisor);

/*!
 * @brief perform the current MMDVSQ signed divide operation and get quotient 
 *
 * This function performs the MMDVSQ signed divide operation and get quotient.
 * It is in block mode. For non-block mode, other HAL routines can be used. 
 *
 * @param	base	Base address for current MMDVSQ instance.    
 * @param	dividend   -Dividend value 
 * @param	divisor    -Divisor value 
 *  
 * @return  Signed divide calculation result in the MMDVSQ_RES register.
 */
uint32_t MMDVSQ_HAL_DivSQ(MMDVSQ_Type * base, uint32_t dividend, uint32_t divisor);

/*!
 * @brief set the current MMDVSQ square root operation
 *
 * This function performs the MMDVSQ square root operation and return the sqrt result of given radicantvalue
 * It is in block mode. For non-block mode, other HAL routines can be used.
 *
 * @param	base	Base address for current MMDVSQ instance.
 * @param	radicand   	- Radicand value 
 *  
 * @return  Square root calculation result in the MMDVSQ_RES register.
 */
uint16_t MMDVSQ_HAL_Sqrt(MMDVSQ_Type * base, uint32_t radicand);

/*@}*/

/*! @name MMDVSQ control register access API*/
/*@{*/

/*!
 * @brief Get the current MMDVSQ execution status
 *
 * This function checks the current MMDVSQ execution status
 *
 * @param	base	Base address for current MMDVSQ instance.
 *
 * @return	Current MMDVSQ execution status
 */
static inline mmdvsq_execution_status_t MMDVSQ_HAL_GetExecutionStatus(MMDVSQ_Type * base)
{
   return (mmdvsq_execution_status_t)(MMDVSQ_RD_CSR(base)>>MMDVSQ_CSR_SQRT_SHIFT);
}

/*!
 * @brief Get the current MMDVSQ BUSY status
 *
 * This function checks the current MMDVSQ BUSY status
 *
 * @param	base	Base address for current MMDVSQ instance.
 *
 * @return	MMDVSQ is busy or idle
 */
static inline bool MMDVSQ_HAL_GetBusyStatus(MMDVSQ_Type * base)
{
   return MMDVSQ_BRD_CSR_BUSY(base);   
}

/*!
 * @brief set the current MMDVSQ divide fast start
 *
 * This function sets the MMDVSQ divide fast start. 
 *
 * @param	base	Base address for current MMDVSQ instance.
 * @param 	enable 		Enable or disable divide fast start mode.
 *        				- true:  ensable divide fast start.
 *        				- false: disable divide fast start, use normal start.
 *  
 */
static inline void MMDVSQ_HAL_SetDivideFastStart(MMDVSQ_Type * base, bool enable)
{
    MMDVSQ_BWR_CSR_DFS(base, enable ? 0 : 1);
}

/*!
 * @brief get the current MMDVSQ divide fast start setting 
 *
 * This function gets the MMDVSQ divide fast start setting
 *
 * @param	base	Base address for current MMDVSQ instance.
 *
 * @return	MMDVSQ divide start is fast start or normal start
 *          -true  : enable fast start mode.
 *        	-false : disable fast start, divide works normal start mode.
 */
static inline bool MMDVSQ_HAL_GetDivideFastStart(MMDVSQ_Type * base)
{
    return (!MMDVSQ_BRD_CSR_DFS(base));
}

/*!
 * @brief set the current MMDVSQ divide by zero detection
 *
 * This function sets the MMDVSQ divide by zero detection
 *
 * @param	base	Base address for current MMDVSQ instance.
 
 * @param 	enable 		Enable or disable divide by zero detect.
 *        				- true:  Enable divide by zero detect.
 *        				- false: Disable divide by zero detect.
 *  
 */
static inline void MMDVSQ_HAL_SetDivdeByZero(MMDVSQ_Type * base, bool enable )
{
    MMDVSQ_BWR_CSR_DZE(base, enable ? 1 : 0);
}

/*!
 * @brief get the current MMDVSQ divide by zero setting 
 *
 * This function gets the MMDVSQ divide by zero setting 
 *
 * @param	base	Base address for current MMDVSQ instance.
 *
 * @return	MMDVSQ divide is non-zero divisor or zero divisor
 *        	- true:  Enable divide by zero detect.
 *          - false: Disable divide by zero detect.
 */
static inline bool MMDVSQ_HAL_GetDivdeByZeroSetting(MMDVSQ_Type * base)
{

    return MMDVSQ_BRD_CSR_DZE(base);
}

/*!
 * @brief get the current MMDVSQ divide by zero status 
 *
 * This function gets the MMDVSQ divide by zero status
 *
 * @param	base	Base address for current MMDVSQ instance.
 *
 * @return	MMDVSQ divide is non-zero divisor or zero divisor
 *        	- true:  zero divisor.
 *          - false: non-zero divisor.
 */
static inline bool MMDVSQ_HAL_GetDivdeByZeroStatus(MMDVSQ_Type * base)
{

    return MMDVSQ_BRD_CSR_DZ(base);
}

/*!
 * @brief set the current MMDVSQ divide remainder calculation
 *
 * This function sets the MMDVSQ divide remainder calculation
 *
 * @param	base	Base address for current MMDVSQ instance.
 * @param 	enable 		Return quotient or remainder in the MMDVSQ_RES register.
 *        				- true:  Return remainder in MMQVSQ_RES.
 *        				- false: Return quotient  in MMQVSQ_RES.
 *  
 */
static inline void MMDVSQ_HAL_SetRemainderCalculation(MMDVSQ_Type * base, bool enable)
{
    MMDVSQ_BWR_CSR_REM(base, enable ? 1 : 0);
}

/*!
 * @brief get the current MMDVSQ divide remainder calculation
 *
 * This function gets the MMDVSQ divide remainder calculation
 *
 * @param	base	Base address for current MMDVSQ instance.
 *  
 * @return	MMDVSQ divide remainder calculation is quotient or remainder
 *        	       	    - true:  return remainder in RES register.
 *        		        - false: return quotient in RES register.
 */
static inline bool MMDVSQ_HAL_GetRemainderCalculation(MMDVSQ_Type * base)
{
    return MMDVSQ_BRD_CSR_REM(base);
}

/*!
 * @brief set the current MMDVSQ unsigned divide calculation
 *
 * This function sets the MMDVSQ unsigned divide calculation
 *
 * @param	base	Base address for current MMDVSQ instance.
 *
 * @param 	enable 		Enable or disable unsigned divide calculation.
 *        				- true:  Enable unsigned divide calculation.
 *        				- false: Disable unsigned divide calculation.

 *  
 */
static inline void MMDVSQ_HAL_SetUnsignedCalculation(MMDVSQ_Type * base, bool enable)
{
    MMDVSQ_BWR_CSR_USGN(base, enable ? 1 : 0);
}

/*!
 * @brief get the current MMDVSQ unsigned divide calculation
 *
 * This function gets the MMDVSQ unsigned divide calculation
 *
 * @param	base	Base address for current MMDVSQ instance.
 *  
 * @return	MMDVSQ divide is unsigned divide operation
 *          - true:  perform an unsigned divide.
 *        	- false: perform a signed divide
 */
static inline bool MMDVSQ_HAL_GetUnsignedCalculation(MMDVSQ_Type * base)
{
    return MMDVSQ_BRD_CSR_USGN(base);
}

/*!
 * @brief get the current MMDVSQ operation result
 *
 * This function gets the MMDVSQ operation result
 *
 * @param	base	Base address for current MMDVSQ instance.
 *  
 * @return	MMDVSQ operation result
 */
static inline uint32_t MMDVSQ_HAL_GetResult(MMDVSQ_Type * base)
{
    return MMDVSQ_RD_RES(base); 
}

/*!
 * @brief set the current MMDVSQ dividend value
 *
 * This function sets the MMDVSQ dividend value
 *
 * @param	base	Base address for current MMDVSQ instance.
 * 
* @param	dividend	Dividend value for divide calculations. 
 */
static inline void MMDVSQ_HAL_SetDividend(MMDVSQ_Type * base, uint32_t dividend)
{
    MMDVSQ_WR_DEND( base, dividend);
}

/*!
 * @brief get the current MMDVSQ dividend value
 *
 * This function gets the MMDVSQ dividend value
 *
 * @param	base	Base address for current MMDVSQ instance.
 *
 * @return	MMDVSQ dividend value 
 */
static inline uint32_t MMDVSQ_HAL_GetDividend(MMDVSQ_Type * base)
{
    return MMDVSQ_RD_DEND(base);
}

/*!
 * @brief set the current MMDVSQ divisor value
 *
 * This function sets the MMDVSQ divisor value
 *
 * @param	base	Base address for current MMDVSQ instance.
 *  
* @param	divisor	Divisor value for divide calculations..
 */
static inline void MMDVSQ_HAL_SetDivisor(MMDVSQ_Type * base, uint32_t divisor)
{
    MMDVSQ_WR_DSOR(base, divisor);
}

/*!
 * @brief get the current MMDVSQ divisor value 
 *
 * This function gets the MMDVSQ divisor value
 *
 * @param	base	Base address for current MMDVSQ instance.
 *  
 * @return	MMDVSQ divisor value
 */
static inline uint32_t MMDVSQ_HAL_GetDivisor(MMDVSQ_Type * base)
{
    return MMDVSQ_RD_DSOR(base); 
}

/*!
 * @brief set the current MMDVSQ radicand value
 *
 * This function sets the MMDVSQ radicand value
*
 * @param	base	Base address for current MMDVSQ instance.
 *
 * @param	radicand	Radicand value of Sqrt.
 *  
 */
static inline void MMDVSQ_HAL_SetRadicand(MMDVSQ_Type * base, uint32_t radicand)
{
    MMDVSQ_WR_RCND(base, radicand);
}

/*@}*/

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif
#endif /* __FSL_MMDVSQ_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

