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
#ifndef __FSL_MMAU_INS_H__
#define __FSL_MMAU_INS_H__

/******************************************************************************
 * MMAU memory map                                                            *
 ******************************************************************************/
/* Registers decorated load/store addresses                                   */
#define MMAU__X0        0xF0004000l /* Accumulator register X0                */
#define MMAU__X1        0xF0004004l /* Accumulator register X1                */
#define MMAU__X2        0xF0004008l /* Accumulator register X2                */
#define MMAU__X3        0xF000400Cl /* Accumulator register X3                */
#define MMAU__A0        0xF0004010l /* Accumulator register A0                */
#define MMAU__A1        0xF0004014l /* Accumulator register A1                */
#define MMAU__A10       0xF0004010l /* Accumulator register pair A10          */
/* Unsigned integer instructions decorated load/store addresses               */
#define MMAU__REGRW      0xf0004000l /* Registers RW                          */
#define MMAU__UMUL       0xf0004020l /* A10=X2*X3                             */
#define MMAU__UMULD      0xf0004040l /* A10=X21*X3                            */
#define MMAU__UMULDA     0xf0004060l /* A10=A10*X3                            */
#define MMAU__UMAC       0xf00040A0l /* A10=X2*X3+A10                         */
#define MMAU__UMACD      0xf00040C0l /* A10=X21*X3+A10                        */
#define MMAU__UMACDA     0xf00040E0l /* A10=A10*X3+X21                        */
#define MMAU__UDIV       0xf0004120l /* X21/X3=A10                            */
#define MMAU__UDIVD      0xf0004140l /* A10=X2/X3                             */
#define MMAU__UDIVDA     0xf0004160l /* A10=X21/X3                            */
#define MMAU__UDIVDD     0xf0004180l /* A10=A10/X3                            */
#define MMAU__UDIVDDA    0xf00041A0l /* A10=A10/X32                           */
#define MMAU__USQR       0xf0004220l /* A10=SQR(X3)                           */
#define MMAU__USQRD      0xf0004240l /* A10=SQR(X32)                          */
#define MMAU__USQRDA     0xf0004260l /* A10=SQR(A10)                          */
/* Signed fractional instructions decorated load/store addresses              */
#define MMAU__QSQR       0xf00042A0l /* A10=SQR(X3)                           */
#define MMAU__QSQRD      0xf00042C0l /* A10=SQR(X32)                          */
#define MMAU__QSQRDA     0xf00042E0l /* A10=SQR(A10)                          */
#define MMAU__QDIV       0xf0004320l /* A10=X2/X3                             */
#define MMAU__QDIVD      0xf0004340l /* A10=X21/X3                            */
#define MMAU__QDIVDA     0xf0004360l /* A10=A10/X3                            */
#define MMAU__QMUL       0xf0004420l /* A10=X2*X3                             */
#define MMAU__QMULD      0xf0004440l /* A10=X21*X3                            */
#define MMAU__QMULDA     0xf0004460l /* A10=A10*X3                            */
#define MMAU__QMAC       0xf00044A0l /* A10=X2*X3+A10                         */
#define MMAU__QMACD      0xf00044C0l /* A10=X21*X3+A10                        */
#define MMAU__QMACDA     0xf00044E0l /* A10=A10*X3+X21                        */
/* Signed integer instructions decorated load/store addresses                 */
#define MMAU__SMUL       0xf0004620l /* A10=X2*X3                             */
#define MMAU__SMULD      0xf0004640l /* A10=X21*X3                            */
#define MMAU__SMULDA     0xf0004660l /* A10=A10*X3                            */
#define MMAU__SMAC       0xf00046A0l /* A10=X2*X3+A10                         */
#define MMAU__SMACD      0xf00046C0l /* A10=X21*X3+A10                        */
#define MMAU__SMACDA     0xf00046E0l /* A10=A10*X3+X21                        */
#define MMAU__SDIV       0xf0004720l /* A10=X2/X3                             */
#define MMAU__SDIVD      0xf0004740l /* A10=X21/X3                            */
#define MMAU__SDIVDA     0xf0004760l /* A10=A10/X3                            */
#define MMAU__SDIVDD     0xf0004780l /* A10=X10/X32                           */
#define MMAU__SDIVDDA    0xf00047A0l /* A10=A10/X32                           */
/* Auxiliary decorated load/store addresses                                   */
#define MMAU__SAT        0xf0004800l /* Saturation                            */

/******************************************************************************
* List of the fractional data types
*
*//*! @addtogroup basic_data_types Fractional Data Types
* @{
 ******************************************************************************/
typedef short int           frac16_t;   /*!< Q0.15  fractional                */
typedef long                frac24_t;   /*!< Q8.23  fractional                */
typedef long                frac32_t;   /*!< Q0.31  fractional                */
typedef long long           frac48_t;   /*!< Q16.47 fractional                */
typedef long long           frac64_t;   /*!< Q0.63  fractional                */
/*! @} End of basic_data_types                                                */

/******************************************************************************
 * MMAU instruction set.
 *
 *//*! @addtogroup mmau_instructions MMAU Mathematical Operations
 * @{
 ******************************************************************************/
/******************************************************************************
 * MMAU unsigned instruction set.
 *
 *//*! @addtogroup uint_instructions Unsigned Integer Operands
 * @{
 ******************************************************************************/
/***************************************************************************//*!
 * @brief   Loads A10 accumulator register of the MMAU by 64-bit unsigned value.
 * @details The @ref ulda_d function loads A10 accumulator register of the MMAU
 *          by 64-bit unsigned value.
 * @param   dval    @ref uint64_t unsigned value.
 ******************************************************************************/
static inline void MMAU_HAL_ulda_d (register uint64_t dval)
{
  *((uint64_t volatile *)(MMAU__REGRW|MMAU__A10))= dval;
}

/***************************************************************************//*!
 * @brief   Multiplies two 32-bit unsigned values returning a 64-bit unsigned
 *          product.
 * @details The @ref MMAU_HAL_d_umul_ll function multiplies two 32-bit unsigned values
 *          returning a 64-bit unsigned product.
 * @param   lval1   @ref uint32_t unsigned value.
 * @param   lval2   @ref uint32_t unsigned value.
 * @return  @ref uint64_t unsigned value.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline uint64_t MMAU_HAL_d_umul_ll (register uint32_t lval1, register uint32_t lval2)
{
  *((uint32_t volatile *)(MMAU__UMUL|MMAU__X2))= lval1;
  *((uint32_t volatile *)(MMAU__UMUL|MMAU__X3))= lval2;
  return *((uint64_t volatile *)(MMAU__UMUL| MMAU__A10));
}

/***************************************************************************//*!
 * @brief   Multiplies 64-bit unsigned value with 32-bit unsigned value returning
 *          a 64-bit unsigned product.
 * @details The @ref MMAU_HAL_d_umul_dl function multiplies 64-bit unsigned value with
 *          32-bit unsigned value returning a 64-bit unsigned product.
 * @param   dval    @ref uint64_t unsigned value.
 * @param   lval    @ref uint32_t unsigned value.
 * @return  @ref uint64_t unsigned value.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline uint64_t MMAU_HAL_d_umul_dl (register uint64_t dval, register uint32_t lval)
{
  *((uint64_t volatile *)(MMAU__UMULD|MMAU__X1))= dval;
  *((uint32_t volatile *)(MMAU__UMULD|MMAU__X3))= lval;
  return *((uint64_t volatile *)(MMAU__UMULD| MMAU__A10));
}

/***************************************************************************//*!
 * @brief   Saturating multiplies 64-bit unsigned value with 32-bit unsigned value
 *          returning saturated 64-bit unsigned product.
 * @details The @ref MMAU_HAL_d_umuls_dl function multiplies 64-bit unsigned value with
 *          32-bit unsigned value returning saturated 64-bit unsigned product.
 * @param   dval    @ref uint64_t unsigned value.
 * @param   lval    @ref uint32_t unsigned value.
 * @return  @ref uint64_t unsigned value.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation.
 ******************************************************************************/
static inline uint64_t MMAU_HAL_d_umuls_dl (register uint64_t dval, register uint32_t lval)
{
  *((uint64_t volatile *)(MMAU__UMULD|MMAU__X1|MMAU__SAT))= dval;
  *((uint32_t volatile *)(MMAU__UMULD|MMAU__X3|MMAU__SAT))= lval;
  return *((uint64_t volatile *)(MMAU__UMULD| MMAU__A10|MMAU__SAT));
}

/***************************************************************************//*!
 * @brief   Multiplies 32-bit unsigned value with 64-bit unsigned value stored in
 *          the A10 register of the MMAU returning a 64-bit unsigned product.
 * @details The @ref MMAU_HAL_d_umula_l function multiplies 32-bit unsigned value with
 *          64-bit unsigned value stored in the A10 register of the MMAU
 *          returning a 64-bit unsigned product.
 * @param   lval    @ref uint32_t unsigned value.
 * @return  @ref uint64_t unsigned value.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline uint64_t MMAU_HAL_d_umula_l (register uint32_t lval)
{
  *((uint32_t volatile *)(MMAU__UMULDA|MMAU__X3))=lval;
  return *((uint64_t volatile *)(MMAU__UMULDA| MMAU__A10));
}

/***************************************************************************//*!
 * @brief   Saturating multiply 32-bit unsigned value with 64-bit unsigned value
 *          stored in the A10 register of the MMAU returning saturated 64-bit unsigned
 *          product.
 * @details The @ref MMAU_HAL_d_umulas_l function multiplies 32-bit unsigned value with
 *          64-bit unsigned value stored in the A10 register of the MMAU
 *          returning saturated 64-bit unsigned product.
 * @param   lval    @ref uint32_t unsigned value.
 * @return  @ref uint64_t unsigned value.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation.
 ******************************************************************************/
static inline uint64_t MMAU_HAL_d_umulas_l (register uint32_t lval)
{
  *((uint32_t volatile *)(MMAU__UMULDA|MMAU__X3|MMAU__SAT))=lval;
  return *((uint64_t volatile *)(MMAU__UMULDA| MMAU__A10|MMAU__SAT));
}

/***************************************************************************//*!
 * @brief   Multiplies two 32-bit unsigned values and add product with value
 *          stored in the A10 register of the MMAU returning a 64-bit unsigned
 *          A10 register value.
 * @details The @ref MMAU_HAL_d_umac_ll function multiplies two 32-bit unsigned values
 *          and add product with value stored in the A10 register of the MMAU
 *          returning a 64-bit unsigned A10 register value.
 * @param   lval1   @ref uint32_t unsigned value.
 * @param   lval2   @ref uint32_t unsigned value.
 * @return  @ref uint64_t unsigned value.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline uint64_t MMAU_HAL_d_umac_ll (register uint32_t lval1, register uint32_t lval2)
{
  *((uint32_t volatile *)(MMAU__UMAC|MMAU__X2))= lval1;
  *((uint32_t volatile *)(MMAU__UMAC|MMAU__X3))= lval2;
  return *((uint64_t volatile *)(MMAU__UMAC| MMAU__A10));
}

/***************************************************************************//*!
 * @brief   Saturating multiply two 32-bit unsigned values and add product with
 *          value stored in the A10 register of the MMAU returning a 64-bit unsigned
 *          A10 register value.
 * @details The @ref MMAU_HAL_d_umacs_ll function multiplies two 32-bit unsigned values
 *          and add product with value stored in the A10 register of the MMAU
 *          returning saturated 64-bit unsigned A10 register value.
 * @param   lval1   @ref uint32_t unsigned value.
 * @param   lval2   @ref uint32_t unsigned value.
 * @return  @ref uint64_t unsigned value.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation.
 ******************************************************************************/
static inline uint64_t MMAU_HAL_d_umacs_ll (register uint32_t lval1, register uint32_t lval2)
{
  *((uint32_t volatile *)(MMAU__UMAC|MMAU__X2|MMAU__SAT))= lval1;
  *((uint32_t volatile *)(MMAU__UMAC|MMAU__X3|MMAU__SAT))= lval2;
  return *((uint64_t volatile *)(MMAU__UMAC| MMAU__A10|MMAU__SAT));
}

/***************************************************************************//*!
 * @brief   Multiplies 64-bit unsigned value with 32-bit unsigned value and add
 *          product with value stored in the A10 register of the MMAU
 *          returning a 64-bit unsigned A10 register value.
 * @details The @ref MMAU_HAL_d_umac_dl function multiplies 64-bit unsigned value with
 *          32-bit unsigned value and add product with value stored in the
 *          A10 register of the MMAU returning a 64-bit unsigned A10 register
 *          value.
 * @param   dval    @ref uint64_t unsigned value.
 * @param   lval    @ref uint32_t unsigned value.
 * @return  @ref uint64_t unsigned value.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline uint64_t MMAU_HAL_d_umac_dl (register uint64_t dval, register uint32_t lval)
{
  *((uint64_t volatile *)(MMAU__UMACD|MMAU__X1))= dval;
  *((uint32_t volatile *)(MMAU__UMACD|MMAU__X3))= lval;
  return *((uint64_t volatile *)(MMAU__UMACD| MMAU__A10));
}

/***************************************************************************//*!
 * @brief   Saturating multiply 64-bit unsigned value with 32-bit unsigned value
 *          and add product with value stored in the A10 register of the MMAU
 *          returning saturated 64-bit unsigned A10 register value.
 * @details The @ref MMAU_HAL_d_umacs_dl function multiplies 64-bit unsigned value with
 *          32-bit unsigned value and add product with value stored in the
 *          A10 register of the MMAU returning saturated 64-bit unsigned A10
 *          register value.
 * @param   dval    @ref uint64_t unsigned value.
 * @param   lval    @ref uint32_t unsigned value.
 * @return  @ref uint64_t unsigned value.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation.
 ******************************************************************************/
static inline uint64_t MMAU_HAL_d_umacs_dl (register uint64_t dval, register uint32_t lval)
{
  *((uint64_t volatile *)(MMAU__UMACD|MMAU__X1|MMAU__SAT))= dval;
  *((uint32_t volatile *)(MMAU__UMACD|MMAU__X3|MMAU__SAT))= lval;
  return *((uint64_t volatile *)(MMAU__UMACD| MMAU__A10|MMAU__SAT));
}

/***************************************************************************//*!
 * @brief   Multiplies 32-bit unsigned value by value stored in the A10 register
 *          of the MMAU and add product with 64-bit unsigned value returning
 *          a 64-bit unsigned A10 register value.
 * @details The @ref MMAU_HAL_d_umaca_dl function multiplies 32-bit unsigned value by
 *          value stored in the A10 register of the MMAU and add product with
 *          64-bit unsigned value returning a 64-bit unsigned A10 register
 *          value.
 * @param   dval    @ref uint64_t unsigned value.
 * @param   lval    @ref uint32_t unsigned value.
 * @return  @ref uint64_t unsigned value.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline uint64_t MMAU_HAL_d_umaca_dl (register uint64_t dval, register uint32_t lval)
{
  *((uint64_t volatile *)(MMAU__UMACDA|MMAU__X1))= dval;
  *((uint32_t volatile *)(MMAU__UMACDA|MMAU__X3))= lval;
  return *((uint64_t volatile *)(MMAU__UMACDA| MMAU__A10));
}

/***************************************************************************//*!
 * @brief   Saturating multiply 32-bit unsigned value by value stored in the A10
 *          register of the MMAU and add product with 64-bit unsigned value returning
 *          a saturated 64-bit unsigned A10 register value.
 * @details The @ref MMAU_HAL_d_umacas_dl function multiplies 32-bit unsigned value by
 *          value stored in the A10 register of the MMAU and add product with
 *          64-bit unsigned value returning saturated 64-bit unsigned A10
 *          register value.
 * @param   dval    @ref uint64_t unsigned value.
 * @param   lval    @ref uint32_t unsigned value.
 * @return  @ref uint64_t unsigned value.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation.
 ******************************************************************************/
static inline uint64_t MMAU_HAL_d_umacas_dl (register uint64_t dval, register uint32_t lval)
{
  *((uint64_t volatile *)(MMAU__UMACDA|MMAU__X1|MMAU__SAT))= dval;
  *((uint32_t volatile *)(MMAU__UMACDA|MMAU__X3|MMAU__SAT))= lval;
  return *((uint64_t volatile *)(MMAU__UMACDA| MMAU__A10|MMAU__SAT));
}

/***************************************************************************//*!
 * @brief   Divides two 32-bit unsigned values returning a 32-bit unsigned
 *          quotient.
 * @details The @ref MMAU_HAL_l_udiv_ll function divides two 32-bit unsigned values
 *          returning a 32-bit unsigned quotient.
 * @param   lnum    @ref uint32_t unsigned value.
 * @param   lden    @ref uint32_t unsigned value.
 * @return  @ref uint32_t unsigned value.
 * @note    Quotient is stored in A0 register of the MMAU for next computation.
 ******************************************************************************/
static inline uint32_t MMAU_HAL_l_udiv_ll (register uint32_t lnum, register uint32_t lden)
{
  *((uint32_t volatile *)(MMAU__UDIV|MMAU__X2))= lnum;
  *((uint32_t volatile *)(MMAU__UDIV|MMAU__X3))= lden;
  return *((uint32_t volatile *)(MMAU__UDIV|MMAU__A0));
}

/***************************************************************************//*!
 * @brief   Divides 64-bit unsigned value by 32-bit unsigned value returning a
 *          64-bit unsigned quotient.
 * @details The @ref MMAU_HAL_d_udiv_dl function divides 64-bit unsigned value by 32-bit
 *          unsigned value returning a 64-bit unsigned quotient.
 * @param   dnum    @ref uint64_t unsigned value.
 * @param   lden    @ref uint32_t unsigned value.
 * @return  @ref uint64_t unsigned value.
 * @note    Quotient is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline uint64_t MMAU_HAL_d_udiv_dl (register uint64_t dnum, register uint32_t lden)
{
  *((uint64_t volatile *)(MMAU__UDIVD|MMAU__X1))= dnum;
  *((uint32_t volatile *)(MMAU__UDIVD|MMAU__X3))= lden;
  return *((uint64_t volatile *)(MMAU__UDIVD| MMAU__A10));
}

/***************************************************************************//*!
 * @brief   Divides two 64-bit unsigned values returning a 64-bit unsigned
 *          quotient.
 * @details The @ref MMAU_HAL_d_udiv_dd function divides two 64-bit unsigned values
 *          returning a 64-bit unsigned quotient.
 * @param   dnum    @ref uint64_t unsigned value.
 * @param   dden    @ref uint64_t unsigned value.
 * @return  @ref uint64_t unsigned value.
 * @note    Quotient is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline uint64_t MMAU_HAL_d_udiv_dd (register uint64_t dnum, register uint64_t dden)
{
  *((uint64_t volatile *)(MMAU__UDIVDD|MMAU__X0))=dnum;
  *((uint64_t volatile *)(MMAU__UDIVDD|MMAU__X2))=dden;
  return *((uint64_t volatile *)(MMAU__UDIVDD| MMAU__A10));
}

/***************************************************************************//*!
 * @brief   Divides 32-bit unsigned value stored in the A10 register of the MMAU
 *          by 32-bit unsigned value returning a 64-bit unsigned quotient.
 * @details The @ref MMAU_HAL_d_udiva_l function divides 64-bit unsigned value stored in
 *          the A10 register of the MMAU by 32-bit unsigned value returning
 *          a 64-bit unsigned quotient.
 * @param   lden1   @ref uint32_t unsigned value.
 * @return  @ref uint64_t unsigned value.
 * @note    Quotient is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline uint64_t MMAU_HAL_d_udiva_l (register uint32_t lden1)
{
  *((uint32_t volatile *)(MMAU__UDIVDA|MMAU__X3))=lden1;
  return *((uint64_t volatile *)(MMAU__UDIVDA| MMAU__A10));
}

/***************************************************************************//*!
 * @brief   Divides 64-bit unsigned value stored in the A10 register of the MMAU
 *          by 64-bit unsigned value returning a 64-bit unsigned quotient.
 * @details The @ref MMAU_HAL_d_udiva_d function divides 64-bit unsigned value stored in
 *          the A10 register of the MMAU by 64-bit unsigned value returning
 *          a 64-bit unsigned quotient.
 * @param   dden1   @ref uint64_t unsigned value.
 * @return  @ref uint64_t unsigned value.
 * @note    Quotient is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline uint64_t MMAU_HAL_d_udiva_d (register uint64_t dden1)
{
  *((uint64_t volatile *)(MMAU__UDIVDDA|MMAU__X2))=dden1;
  return *((uint64_t volatile *)(MMAU__UDIVDDA| MMAU__A10));
}

/***************************************************************************//*!
 * @brief   Computes and returns a 32-bit unsigned square root of the 32-bit
 *          unsigned radicand.
 * @details The @ref MMAU_HAL_l_usqr_l function computes and returns a 32-bit unsigned
 *          square root of the 32-bit unsigned radicand.
 * @param   lrad    @ref uint32_t unsigned radicand.
 * @return  @ref uint32_t unsigned square root.
 * @note    Quotient is stored in A0 register of the MMAU for next computation.
 ******************************************************************************/
static inline uint32_t MMAU_HAL_l_usqr_l (register uint32_t lrad)
{
  *((uint32_t volatile *)(MMAU__USQR|MMAU__X3))=lrad;
  return *((uint32_t volatile *)(MMAU__USQR|MMAU__A0));
}

/***************************************************************************//*!
 * @brief   Computes and returns a 32-bit unsigned square root of the 64-bit
 *          unsigned radicand.
 * @details The @ref MMAU_HAL_l_usqr_d function computes and returns a 32-bit unsigned
 *          square root of the 64-bit unsigned radicand.
 * @param   drad    @ref uint64_t unsigned radicand.
 * @return  @ref uint32_t unsigned square root.
 * @note    Quotient is stored in A0 register of the MMAU for next computation.
 ******************************************************************************/
static inline uint32_t MMAU_HAL_l_usqr_d (register uint64_t drad)
{
  *((uint64_t volatile *)(MMAU__USQRD|MMAU__X2))=drad;
  return *((uint32_t volatile *)(MMAU__USQRD|MMAU__A0));
}

/***************************************************************************//*!
 * @brief   Computes and returns a 16-bit unsigned square root of the 32-bit
 *          unsigned radicand.
 * @details The @ref MMAU_HAL_s_usqr_l function computes and returns a 16-bit unsigned
 *          square root of the 32-bit unsigned radicand.
 * @param   lrad    @ref uint32 unsigned radicand.
 * @return  @ref uint16 unsigned square root.
 * @note    Square root is stored in A0 register of the MMAU for next
 *          computation.
 ******************************************************************************/
static inline uint16_t MMAU_HAL_s_usqr_l (register uint32_t lrad)
{
  *((uint32_t volatile *)(MMAU__USQR|MMAU__X3))= lrad;
  return *((uint16_t volatile *)(MMAU__USQR|MMAU__A0));
}

/***************************************************************************//*!
 * @brief   Computes and returns a 32-bit unsigned square root of the radicand
 *          stored in the A10 register of the MMAU.
 * @details The @ref MMAU_HAL_l_usqra function computes and returns a 32-bit unsigned
 *          square root of the radicand stored in the A10 register of the MMAU.
 * @return  @ref uint32_t unsigned square root.
 * @note    Quotient is stored in A0 register of the MMAU for next computation.
 ******************************************************************************/
static inline uint32_t MMAU_HAL_l_usqra (void)
{
  return *((uint32_t volatile *)(MMAU__USQRDA|MMAU__A0));
}
/*@}*/

/******************************************************************************
 * MMAU instruction set.
 *
 *//*! @addtogroup int_instructions Signed Integer Operands
 * @{
 ******************************************************************************/
/***************************************************************************//*!
 * @brief   Loads A10 accumulator register of the MMAU by 64-bit integer value.
 * @details The @ref MMAU_HAL_slda_d function loads A10 accumulator register of the MMAU
 *          by 64-bit integer value.
 * @param   dval    @ref int64_t integer value.
 ******************************************************************************/
static inline void MMAU_HAL_slda_d (register int64_t dval)
{
  *((int64_t volatile *)(MMAU__REGRW|MMAU__A10))= dval;
}

/***************************************************************************//*!
 * @brief   Multiplies two 32-bit integer values returning a 64-bit integer
 *          product.
 * @details The @ref MMAU_HAL_d_smul_ll function multiplies two 32-bit integer values
 *          returning a 64-bit integer product.
 * @param   lval1   @ref int32_t integer value.
 * @param   lval2   @ref int32_t integer value.
 * @return  @ref int64_t integer value.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline int64_t MMAU_HAL_d_smul_ll (register int32_t lval1, register int32_t lval2)
{
  *((int32_t volatile *)(MMAU__SMUL|MMAU__X2))= lval1;
  *((int32_t volatile *)(MMAU__SMUL|MMAU__X3))= lval2;
  return *((int64_t volatile *)(MMAU__SMUL| MMAU__A10));
}

/***************************************************************************//*!
 * @brief   Multiplies 64-bit integer value with 32-bit integer value returning a
 *          64-bit integer product.
 * @details The @ref MMAU_HAL_d_smul_dl function multiplies 64-bit integer value with
 *          32-bit integer value returning a 64-bit integer product.
 * @param   dval    @ref int64_t integer value.
 * @param   lval    @ref int32_t integer value.
 * @return  @ref int64_t integer value.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline int64_t MMAU_HAL_d_smul_dl (register int64_t dval, register int32_t lval)
{
  *((int64_t volatile *)(MMAU__SMULD|MMAU__X1))= dval;
  *((int32_t volatile *)(MMAU__SMULD|MMAU__X3))= lval;
  return *((int64_t volatile *)(MMAU__SMULD| MMAU__A10));
}

/***************************************************************************//*!
 * @brief   Saturating multiply 64-bit integer value with 32-bit integer value
 *          returning saturated 64-bit integer product.
 * @details The @ref MMAU_HAL_d_smuls_dl function multiplies 64-bit integer value with
 *          32-bit integer value returning saturated 64-bit integer product.
 * @param   dval    @ref int64_t integer value.
 * @param   lval    @ref int32_t integer value.
 * @return  @ref int64_t integer value.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation.
 ******************************************************************************/
static inline int64_t MMAU_HAL_d_smuls_dl (register int64_t dval, register int32_t lval)
{
  *((int64_t volatile *)(MMAU__SMULD|MMAU__X1|MMAU__SAT))= dval;
  *((int32_t volatile *)(MMAU__SMULD|MMAU__X3|MMAU__SAT))= lval;
  return *((int64_t volatile *)(MMAU__SMULD|MMAU__A10|MMAU__SAT));
}

/***************************************************************************//*!
 * @brief   Multiplies 32-bit integer value with 64-bit integer value stored in
 *          the A10 register of the MMAU returning a 64-bit integer product.
 * @details The @ref MMAU_HAL_d_smula_l function multiplies 32-bit integer value with
 *          64-bit integer value stored in the A10 register of the MMAU
 *          returning a 64-bit integer product.
 * @param   lval    @ref int32_t integer value.
 * @return  @ref int64_t integer value.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline int64_t MMAU_HAL_d_smula_l (register int32_t lval)
{
  *((int32_t volatile *)(MMAU__SMULDA|MMAU__X3))=lval;
  return *((int64_t volatile *)(MMAU__SMULDA| MMAU__A10));
}

/***************************************************************************//*!
 * @brief   Saturating multiply 32-bit integer value with 64-bit integer value
 *          stored in the A10 register of the MMAU returning saturated 64-bit integer
 *          product.
 * @details The @ref MMAU_HAL_d_smulas_l function multiplies 32-bit integer value with
 *          64-bit integer value stored in the A10 register of the MMAU
 *          returning saturated 64-bit integer product.
 * @param   lval    @ref int32_t integer value.
 * @return  @ref int64_t integer value.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation.
 ******************************************************************************/
static inline int64_t MMAU_HAL_d_smulas_l (register int32_t lval)
{
  *((int32_t volatile *)(MMAU__SMULDA|MMAU__X3|MMAU__SAT))=lval;
  return *((int64_t volatile *)(MMAU__SMULDA| MMAU__A10|MMAU__SAT));
}

/***************************************************************************//*!
 * @brief   Multiplies two 32-bit integer values and adds product with value stored
 *          in the A10 register of the MMAU returning a 64-bit integer
 *          A10 register value.
 * @details The @ref MMAU_HAL_d_smac_ll function multiplies two 32-bit integer values and
 *          add product with value stored in the A10 register of the MMAU
 *          returning a 64-bit integer A10 register value.
 * @param   lval1   @ref int32_t integer value.
 * @param   lval2   @ref int32_t integer value.
 * @return  @ref int64_t integer value.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline int64_t MMAU_HAL_d_smac_ll (register int32_t lval1, register int32_t lval2)
{
  *((int32_t volatile *)(MMAU__SMAC|MMAU__X2))= lval1;
  *((int32_t volatile *)(MMAU__SMAC|MMAU__X3))= lval2;
  return *((int64_t volatile *)(MMAU__SMAC| MMAU__A10));
}

/***************************************************************************//*!
 * @brief   Saturating multiply two 32-bit integer values and add product with
 *          value stored in the A10 register of the MMAU returning a 64-bit integer
 *          A10 register value.
 * @details The @ref MMAU_HAL_d_smacs_ll function multiplies two 32-bit integer values
 *          and add product with value stored in the A10 register of the MMAU
 *          returning saturated 64-bit integer A10 register value.
 * @param   lval1   @ref int32_t integer value.
 * @param   lval2   @ref int32_t integer value.
 * @return  @ref int64_t integer value.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation.
 ******************************************************************************/
static inline int64_t MMAU_HAL_d_smacs_ll (register int32_t lval1, register int32_t lval2)
{
  *((int32_t volatile *)(MMAU__SMAC|MMAU__X2|MMAU__SAT))= lval1;
  *((int32_t volatile *)(MMAU__SMAC|MMAU__X3|MMAU__SAT))= lval2;
  return *((int64_t volatile *)(MMAU__SMAC| MMAU__A10|MMAU__SAT));
}

/***************************************************************************//*!
 * @brief   Multiplies 64-bit integer value with 32-bit integer value and adds
 *          product with value stored in the A10 register of the MMAU
 *          returning a 64-bit integer A10 register value.
 * @details The @ref MMAU_HAL_d_smac_dl function multiplies 64-bit integer value with
 *          32-bit integer value and add product with value stored in the
 *          A10 register of the MMAU returning a 64-bit integer A10 register
 *          value.
 * @param   dval    @ref int64_t integer value.
 * @param   lval    @ref int32_t integer value.
 * @return  @ref int64_t integer value.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline int64_t MMAU_HAL_d_smac_dl (register int64_t dval, register int32_t lval)
{
  *((int64_t volatile *)(MMAU__SMACD|MMAU__X1))= dval;
  *((int32_t volatile *)(MMAU__SMACD|MMAU__X3))= lval;
  return *((int64_t volatile *)(MMAU__SMACD| MMAU__A10));
}

/***************************************************************************//*!
 * @brief   Saturating multiply 64-bit integer value with 32-bit integer value
 *          and add product with value stored in the A10 register of the MMAU
 *          returning saturated 64-bit integer A10 register value.
 * @details The @ref MMAU_HAL_d_smacs_dl function multiplies 64-bit integer value with
 *          32-bit integer value and add product with value stored in the
 *          A10 register of the MMAU returning saturated 64-bit integer A10
 *          register value.
 * @param   dval    @ref int64_t integer value.
 * @param   lval    @ref int32_t integer value.
 * @return  @ref int64_t integer value.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation. If saturation occurs, the instruction sets the
 *          accumulation overflow (Q) and multiply or divide overflow (V) flags
 *          to 1 in the CSR. Otherwise, it clears the Q and V flags.
 ******************************************************************************/
static inline int64_t MMAU_HAL_d_smacs_dl (register int64_t dval, register int32_t lval)
{
  *((int64_t volatile *)(MMAU__SMACD|MMAU__X1|MMAU__SAT))= dval;
  *((int32_t volatile *)(MMAU__SMACD|MMAU__X3|MMAU__SAT))= lval;
  return *((int64_t volatile *)(MMAU__SMACD| MMAU__A10|MMAU__SAT));
}

/***************************************************************************//*!
 * @brief   Multiplies 32-bit integer value by value stored in the A10 register of
 *          the MMAU and adds product with 64-bit integer value returning
 *          a 64-bit integer A10 register value.
 * @details The @ref MMAU_HAL_d_smaca_dl function multiplies 32-bit integer value by
 *          value stored in the A10 register of the MMAU and add product with
 *          64-bit integer value returning a 64-bit integer A10 register value.
 * @param   dval    @ref int64_t integer value.
 * @param   lval    @ref int32_t integer value.
 * @return  @ref int64_t integer value.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline int64_t MMAU_HAL_d_smaca_dl (register int64_t dval, register int32_t lval)
{
  *((int64_t volatile *)(MMAU__SMACDA|MMAU__X1))= dval;
  *((int32_t volatile *)(MMAU__SMACDA|MMAU__X3))= lval;
  return *((int64_t volatile *)(MMAU__SMACDA| MMAU__A10));
}

/***************************************************************************//*!
 * @brief   Saturating multiply 32-bit integer value by value stored in the A10
 *          register of the MMAU and add product with 64-bit integer value returning
 *          a saturated 64-bit integer A10 register value.
 * @details The @ref MMAU_HAL_d_smacas_dl function multiplies 32-bit integer value by
 *          value stored in the A10 register of the MMAU and add product with
 *          64-bit integer value returning saturated 64-bit integer A10 register
 *          value.
 * @param   dval    @ref int64_t integer value.
 * @param   lval    @ref int32_t integer value.
 * @return  @ref int64_t integer value.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation. If saturation occurs, the instruction sets the
 *          accumulation overflow (Q) and multiply or divide overflow (V) flags
 *          to 1 in the CSR. Otherwise, it clears the Q and V flags.
 ******************************************************************************/
static inline int64_t MMAU_HAL_d_smacas_dl (register int64_t dval, register int32_t lval)
{
  *((int64_t volatile *)(MMAU__SMACDA|MMAU__X1|MMAU__SAT))= dval;
  *((int32_t volatile *)(MMAU__SMACDA|MMAU__X3|MMAU__SAT))= lval;
  return *((int64_t volatile *)(MMAU__SMACDA| MMAU__A10|MMAU__SAT));
}

/***************************************************************************//*!
 * @brief   Divides two 32-bit integer values returning a 32-bit integer
 *          quotient.
 * @details The @ref MMAU_HAL_l_sdiv_ll function divides two 32-bit integer values
 *          returning a 32-bit integer quotient.
 * @param   lnum    @ref int32_t integer value.
 * @param   lden    @ref int32_t integer value.
 * @return  @ref int32_t integer value.
 * @note    Quotient is stored in A0 register of the MMAU for next computation.
 ******************************************************************************/
static inline int32_t MMAU_HAL_l_sdiv_ll (register int32_t lnum, register int32_t lden)
{
  *((int32_t volatile *)(MMAU__SDIV|MMAU__X2))= lnum;
  *((int32_t volatile *)(MMAU__SDIV|MMAU__X3))= lden;
  return *((int32_t volatile *)(MMAU__SDIV|MMAU__A0));
}

/***************************************************************************//*!
 * @brief   Divides two 32-bit integer values returning a 32-bit integer
 *          quotient.
 * @details The @ref MMAU_HAL_l_sdivs_ll function divides two 32-bit integer values
 *          returning a 32-bit integer quotient.
 * @param   lnum    @ref int32_t integer value.
 * @param   lden    @ref int32_t integer value.
 * @return  @ref int32_t integer value.
 * @note    Saturated quotient is  stored in A0 register of the MMAU for
 *          next computation.
 ******************************************************************************/
static inline int32_t MMAU_HAL_l_sdivs_ll (register int32_t lnum, register int32_t lden)
{
  *((int32_t volatile *)(MMAU__SDIV|MMAU__X2|MMAU__SAT))= lnum;
  *((int32_t volatile *)(MMAU__SDIV|MMAU__X3|MMAU__SAT))= lden;
  return *((int32_t volatile *)(MMAU__SDIV|MMAU__A0|MMAU__SAT));
}

/***************************************************************************//*!
 * @brief   Divides 64-bit integer value by 32-bit integer value returning a
 *          64-bit integer quotient.
 * @details The @ref MMAU_HAL_d_sdiv_dl function divides 64-bit integer value by 32-bit
 *          integer value returning a 64-bit integer quotient.
 * @param   dnum    @ref int64_t integer value.
 * @param   lden    @ref int32_t integer value.
 * @return  @ref int64_t integer value.
 * @note    Quotient is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline int64_t MMAU_HAL_d_sdiv_dl (register int64_t dnum, register int32_t lden)
{
  *((int64_t volatile *)(MMAU__SDIVD|MMAU__X1))= dnum;
  *((int32_t volatile *)(MMAU__SDIVD|MMAU__X3))= lden;
  return *((int64_t volatile *)(MMAU__SDIVD| MMAU__A10));
}

/***************************************************************************//*!
 * @brief   Divides 64-bit integer value by 32-bit integer value returning a
 *          64-bit integer quotient.
 * @details The @ref MMAU_HAL_d_sdivs_dl function divides 64-bit integer value by 32-bit
 *          integer value returning a 64-bit integer quotient.
 * @param   dnum    @ref int64_t integer value.
 * @param   lden    @ref int32_t integer value.
 * @return  @ref int64_t integer value.
 * @note    Saturated quotient is  stored in A10 register of the MMAU for
 *          next computation. 
 ******************************************************************************/
static inline int64_t MMAU_HAL_d_sdivs_dl (register int64_t dnum, register int32_t lden)
{
  *((int64_t volatile *)(MMAU__SDIVD|MMAU__X1|MMAU__SAT))= dnum;
  *((int32_t volatile *)(MMAU__SDIVD|MMAU__X3|MMAU__SAT))= lden;
  return *((int64_t volatile *)(MMAU__SDIVD| MMAU__A10|MMAU__SAT));
}

/***************************************************************************//*!
 * @brief   Divides two 64-bit integer values returning a 64-bit integer
 *          quotient.
 * @details The @ref MMAU_HAL_d_sdiv_dd function divides two 64-bit integer values
 *          returning a 64-bit integer quotient.
 * @param   dnum    @ref int64_t integer value.
 * @param   dden    @ref int64_t integer value.
 * @return  @ref int64_t integer value.
 * @note    Quotient is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline int64_t MMAU_HAL_d_sdiv_dd (register int64_t dnum, register int64_t dden)
{
  *((int64_t volatile *)(MMAU__SDIVDD|MMAU__X0))=dnum;
  *((int64_t volatile *)(MMAU__SDIVDD|MMAU__X2))=dden;
  return *((int64_t volatile *)(MMAU__SDIVDD| MMAU__A10));
}

/***************************************************************************//*!
 * @brief   Divides two 64-bit integer values returning a 64-bit integer
 *          quotient.
 * @details The @ref MMAU_HAL_d_sdivs_dd function divides two 64-bit integer values
 *          returning a 64-bit integer quotient.
 * @param   dnum    @ref int64_t integer value.
 * @param   dden    @ref int64_t integer value.
 * @return  @ref int64_t integer value.
 * @note    Saturated quotient is  stored in A10 register of the MMAU for
 *          next computation. 
 ******************************************************************************/
static inline int64_t MMAU_HAL_d_sdivs_dd (register int64_t dnum, register int64_t dden)
{
  *((int64_t volatile *)(MMAU__SDIVDD|MMAU__X0|MMAU__SAT))=dnum;
  *((int64_t volatile *)(MMAU__SDIVDD|MMAU__X2|MMAU__SAT))=dden;
  return *((int64_t volatile *)(MMAU__SDIVDD| MMAU__A10|MMAU__SAT));
}

/***************************************************************************//*!
 * @brief   Divides 32-bit integer value stored in the A10 register of the MMAU
 *          by 32-bit integer value returning a 64-bit integer quotient.
 * @details The @ref MMAU_HAL_d_sdiva_l function divides 32-bit integer value stored in
 *          the A10 register of the MMAU by 32-bit integer value returning
 *          a 64-bit integer quotient.
 * @param   lden1   @ref int32_t integer value.
 * @return  @ref int64_t integer value.
 * @note    Quotient is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline int64_t MMAU_HAL_d_sdiva_l (register int32_t lden1)
{
  *((int32_t volatile *)(MMAU__SDIVDA|MMAU__X3))=lden1;
  return *((int64_t volatile *)(MMAU__SDIVDA| MMAU__A10));
}

/***************************************************************************//*!
 * @brief   Divides 32-bit integer value stored in the A10 register of the MMAU
 *          by 32-bit integer value returning saturated 64-bit integer quotient.
 * @details The @ref MMAU_HAL_d_sdivas_l function divides 32-bit integer value stored in
 *          the A10 register of the MMAU by 32-bit integer value returning
 *          a saturated 64-bit integer quotient.
 * @param   lden1   @ref int32_t integer value.
 * @return  @ref int64_t integer value.
 * @note    Saturated quotient is  stored in A10 register of the MMAU for
 *          next computation. 
 ******************************************************************************/
static inline int64_t MMAU_HAL_d_sdivas_l (register int32_t lden1)
{
  *((int32_t volatile *)(MMAU__SDIVDA|MMAU__X3|MMAU__SAT))=lden1;
  return *((int64_t volatile *)(MMAU__SDIVDA| MMAU__A10|MMAU__SAT));
}

/***************************************************************************//*!
 * @brief   Divides 64-bit integer value stored in the A10 register of the MMAU
 *          by 64-bit integer value returning a 64-bit integer quotient.
 * @details The @ref MMAU_HAL_d_sdiva_d function divides 64-bit integer value stored in
 *          the A10 register of the MMAU by 64-bit integer value returning
 *          a 64-bit integer quotient.
 * @param   dden1   @ref int64_t integer value.
 * @return  @ref int64_t integer value.
 * @note    Quotient is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline int64_t MMAU_HAL_d_sdiva_d (register int64_t dden1)
{
  *((int64_t volatile *)(MMAU__SDIVDDA|MMAU__X2))=dden1;
  return *((int64_t volatile *)(MMAU__SDIVDDA| MMAU__A10));
}

/***************************************************************************//*!
 * @brief   Divides 64-bit integer value stored in the A10 register of the MMAU
 *          by 64-bit integer value returning saturated 64-bit integer quotient.
 * @details The @ref MMAU_HAL_d_sdivas_d function divides 64-bit integer value stored in
 *          the A10 register of the MMAU by 64-bit integer value returning
 *          a saturated 64-bit integer quotient.
 * @param   dden1   @ref int64_t integer value.
 * @return  @ref int64_t integer value.
 * @note    Saturated quotient is  stored in A10 register of the MMAU for
 *          next computation. 
 ******************************************************************************/
static inline int64_t MMAU_HAL_d_sdivas_d (register int64_t dden1)
{
  *((int64_t volatile *)(MMAU__SDIVDDA|MMAU__X2|MMAU__SAT))=dden1;
  return *((int64_t volatile *)(MMAU__SDIVDDA| MMAU__A10|MMAU__SAT));
}
/*@}*/

/******************************************************************************
 * MMAU instruction set.
 *
 *//*! @addtogroup frac_instructions Fractional Operands
 * @{
 ******************************************************************************/
/***************************************************************************//*!
 * @brief   Loads A10 accumulator register of the MMAU by 64-bit fractional
 *          value.
 * @details The @ref MMAU_HAL_lda_d function loads A10 accumulator register of the MMAU
 *          by 64-bit fractional value.
 * @param   dval    @ref frac64_t fractional value.
 ******************************************************************************/
static inline void MMAU_HAL_lda_d (register frac64_t dval)
{
  *((frac64_t volatile *)(MMAU__REGRW|MMAU__A10))= dval;
}

/***************************************************************************//*!
 * @brief   Multiplies two 32-bit fractional values returning a 32-bit fractional
 *          product.
 * @details The @ref MMAU_HAL_l_mul_ll function multiplies two 32-bit fractional values
 *          returning a 32-bit fractional product.
 * @param   lval1   @ref frac32_t fractional value.
 * @param   lval2   @ref frac32_t fractional value.
 * @return  @ref frac32_t fractional value.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline frac32_t MMAU_HAL_l_mul_ll (register frac32_t lval1, register frac32_t lval2)
{
  *((frac32_t volatile *)(MMAU__QMUL|MMAU__X2))= lval1;
  *((frac32_t volatile *)(MMAU__QMUL|MMAU__X3))= lval2;
  return *((frac32_t volatile *)(MMAU__QMUL|MMAU__A1));
}

/***************************************************************************//*!
 * @brief   Saturating multiply two 32-bit fractional values returning saturated
 *          32-bit fractional product.
 * @details The @ref MMAU_HAL_l_muls_ll function multiplies two 32-bit fractional values
 *          returning saturated 32-bit fractional product.
 * @param   lval1   @ref frac32_t fractional value.
 * @param   lval2   @ref frac32_t fractional value.
 * @return  @ref frac32_t fractional value.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation.
 ******************************************************************************/
static inline frac32_t MMAU_HAL_l_muls_ll (register frac32_t lval1, register frac32_t lval2)
{
  *((frac32_t volatile *)(MMAU__QMUL|MMAU__X2|MMAU__SAT))= lval1;
  *((frac32_t volatile *)(MMAU__QMUL|MMAU__X3|MMAU__SAT))= lval2;
  return *((frac32_t volatile *)(MMAU__QMUL|MMAU__A1|MMAU__SAT));
}

/***************************************************************************//*!
 * @brief   Multiplies two 32-bit fractional values returning a 64-bit fractional
 *          product.
 * @details The @ref MMAU_HAL_d_mul_ll function multiplies two 32-bit fractional values
 *          returning a 64-bit fractional product.
 * @param   lval1   @ref frac32_t fractional value.
 * @param   lval2   @ref frac32_t fractional value.
 * @return  @ref frac64_t fractional value.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline frac64_t MMAU_HAL_d_mul_ll (register frac32_t lval1, register frac32_t lval2)
{
  *((frac32_t volatile *)(MMAU__QMUL|MMAU__X2))= lval1;
  *((frac32_t volatile *)(MMAU__QMUL|MMAU__X3))= lval2;
  return *((frac64_t volatile *)(MMAU__QMUL| MMAU__A10));
}

/***************************************************************************//*!
 * @brief   Saturating multiply two 32-bit fractional values returning saturated
 *          64-bit fractional product.
 * @details The @ref MMAU_HAL_d_muls_ll function multiplies two 32-bit fractional values
 *          returning saturated 64-bit fractional product.
 * @param   lval1   @ref frac32_t fractional value.
 * @param   lval2   @ref frac32_t fractional value.
 * @return  @ref frac64_t fractional value.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation. If saturation occurs, the instruction sets the
 *          accumulation overflow (Q) and multiply or divide overflow (V) flags
 *          to 1 in the CSR. Otherwise, it clears the Q and V flags.
 ******************************************************************************/
static inline frac64_t MMAU_HAL_d_muls_ll (register frac32_t lval1, register frac32_t lval2)
{
  *((frac32_t volatile *)(MMAU__QMUL|MMAU__X2|MMAU__SAT))= lval1;
  *((frac32_t volatile *)(MMAU__QMUL|MMAU__X3|MMAU__SAT))= lval2;
  return *((frac64_t volatile *)(MMAU__QMUL| MMAU__A10|MMAU__SAT));
}

/***************************************************************************//*!
 * @brief   Multiplies 64-bit fractional value with 32-bit fractional value
 *          returning a 64-bit fractional product.
 * @details The @ref MMAU_HAL_d_mul_dl function multiplies 64-bit fractional value with
 *          32-bit fractional value returning a 64-bit fractional product.
 * @param   dval    @ref frac64_t fractional value.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac64_t fractional value.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline frac64_t MMAU_HAL_d_mul_dl (register frac64_t dval, register frac32_t lval)
{
  *((frac64_t volatile *)(MMAU__QMULD|MMAU__X1))= dval;
  *((frac32_t volatile *)(MMAU__QMULD|MMAU__X3))= lval;
  return *((frac64_t volatile *)(MMAU__QMULD| MMAU__A10));
}

/***************************************************************************//*!
 * @brief   Saturating multiply 64-bit fractional value with 32-bit fractional
 *          value returning saturated 64-bit fractional product.
 * @details The @ref MMAU_HAL_d_muls_dl function multiplies 64-bit fractional value with
 *          32-bit fractional value returning saturated 64-bit fractional product.
 * @param   dval    @ref frac64_t fractional value.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac64_t fractional value.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation. If saturation occurs, the instruction sets the
 *          accumulation overflow (Q) and multiply or divide overflow (V) flags
 *          to 1 in the CSR. Otherwise, it clears the Q and V flags.
 ******************************************************************************/
static inline frac64_t MMAU_HAL_d_muls_dl (register frac64_t dval, register frac32_t lval)
{
  *((frac64_t volatile *)(MMAU__QMULD|MMAU__X1|MMAU__SAT))= dval;
  *((frac32_t volatile *)(MMAU__QMULD|MMAU__X3|MMAU__SAT))= lval;
  return *((frac64_t volatile *)(MMAU__QMULD| MMAU__A10|MMAU__SAT));
}

/***************************************************************************//*!
 * @brief   Multiplies 32-bit fractional value with 64-bit fractional value stored
 *          in the A10 register of the MMAU returning a 64-bit fractional product.
 * @details The @ref MMAU_HAL_d_mula_l function multiplies 32-bit fractional value with
 *          64-bit fractional value stored in the A10 register of the MMAU
 *          returning a 64-bit fractional product.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac64_t fractional value.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline frac64_t MMAU_HAL_d_mula_l (register frac32_t lval)
{
  *((frac32_t volatile *)(MMAU__QMULDA|MMAU__X3))=lval;
  return *((frac64_t volatile *)(MMAU__QMULDA| MMAU__A10));
}

/***************************************************************************//*!
 * @brief   Saturating multiply 32-bit fractional value with 64-bit fractional
 *          value stored in the A10 register of the MMAU returning saturated 64-bit
 *          fractional product.
 * @details The @ref MMAU_HAL_d_mulas_l function multiplies 32-bit fractional value with
 *          64-bit fractional value stored in the A10 register of the MMAU
 *          returning saturated 64-bit fractional product.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac64_t fractional value.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation. If saturation occurs, the instruction sets the
 *          accumulation overflow (Q) and multiply or divide overflow (V) flags
 *          to 1 in the CSR. Otherwise, it clears the Q and V flags.
 ******************************************************************************/
static inline frac64_t MMAU_HAL_d_mulas_l (register frac32_t lval)
{
  *((frac32_t volatile *)(MMAU__QMULDA|MMAU__X3|MMAU__SAT))=lval;
  return *((frac64_t volatile *)(MMAU__QMULDA| MMAU__A10|MMAU__SAT));
}

/***************************************************************************//*!
 * @brief   Multiplies 64-bit fractional value with 32-bit fractional value
 *          returning a 32-bit fractional product.
 * @details The @ref MMAU_HAL_l_mul_dl function multiplies 64-bit fractional value with
 *          32-bit fractional value returning a 32-bit fractional product.
 * @param   dval    @ref frac64_t fractional value.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac32_t fractional value.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline frac32_t MMAU_HAL_l_mul_dl (register frac64_t dval, register frac32_t lval)
{
  *((frac64_t volatile *)(MMAU__QMULD|MMAU__X1))= dval;
  *((frac32_t volatile *)(MMAU__QMULD|MMAU__X3))= lval;
  return *((frac32_t volatile *)(MMAU__QMULD|MMAU__A1));
}

/***************************************************************************//*!
 * @brief   Saturating multiply 64-bit fractional value with 32-bit fractional
 *          value returning saturated 32-bit fractional product.
 * @details The @ref MMAU_HAL_l_muls_dl function multiplies 64-bit fractional value with
 *          32-bit fractional value returning saturated 32-bit fractional
 *          product.
 * @param   dval    @ref frac64_t fractional value.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac32_t fractional value.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation.
 ******************************************************************************/
static inline frac32_t MMAU_HAL_l_muls_dl (register frac64_t dval, register frac32_t lval)
{
  *((frac64_t volatile *)(MMAU__QMULD|MMAU__X1|MMAU__SAT))= dval;
  *((frac32_t volatile *)(MMAU__QMULD|MMAU__X3|MMAU__SAT))= lval;
  return *((frac32_t volatile *)(MMAU__QMULD|MMAU__A1|MMAU__SAT));
}

/***************************************************************************//*!
 * @brief   Multiplies 32-bit fractional value with 64-bit fractional value stored
 *          in the A10 register of the MMAU returning a 32-bit fractional
 *          product.
 * @details The @ref MMAU_HAL_l_mula_l function multiplies 32-bit fractional value with
 *          64-bit fractional value stored in the A10 register of the MMAU
 *          returning a 32-bit fractional product.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac32_t fractional value.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline frac32_t MMAU_HAL_l_mula_l (register frac32_t lval)
{
  *((frac32_t volatile *)(MMAU__QMULDA|MMAU__X3))= lval;
  return *((frac32_t volatile *)(MMAU__QMULDA|MMAU__A1));
}

/***************************************************************************//*!
 * @brief   Saturating multiply 32-bit fractional value with 64-bit fractional
 *          value stored in the A10 register of the MMAU returning saturated
 *          32-bit fractional product.
 * @details The @ref MMAU_HAL_l_mulas_l function multiplies 32-bit fractional value with
 *          64-bit fractional value stored in the A10 register of the MMAU
 *          returning saturated 32-bit fractional product.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac32_t fractional value.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation.
 ******************************************************************************/
static inline frac32_t MMAU_HAL_l_mulas_l (register frac32_t lval)
{
  *((frac32_t volatile *)(MMAU__QMULDA|MMAU__X3|MMAU__SAT))= lval;
  return *((frac32_t volatile *)(MMAU__QMULDA|MMAU__A1|MMAU__SAT));
}

/***************************************************************************//*!
 * @brief   Multiplies two 32-bit fractional values and adds product with value
 *          stored in the A10 register of the MMAU returning a 64-bit fractional
 *          A10 register value.
 * @details The @ref MMAU_HAL_d_mac_ll function multiplies two 32-bit fractional values
 *          and add product with value stored in the A10 register of the MMAU
 *          returning a 64-bit fractional A10 register value.
 * @param   lval1   @ref frac32_t fractional value.
 * @param   lval2   @ref frac32_t fractional value.
 * @return  @ref frac64_t fractional value.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline frac64_t MMAU_HAL_d_mac_ll (register frac32_t lval1, register frac32_t lval2)
{
  *((frac32_t volatile *)(MMAU__QMAC|MMAU__X2))= lval1;
  *((frac32_t volatile *)(MMAU__QMAC|MMAU__X3))= lval2;
  return *((frac64_t volatile *)(MMAU__QMAC| MMAU__A10));
}

/***************************************************************************//*!
 * @brief   Saturating multiply two 32-bit fractional values and add product
 *          with value stored in the A10 register of the MMAU returning a 64-bit fractional
 *          A10 register value.
 * @details The @ref MMAU_HAL_d_macs_ll function multiplies two 32-bit fractional values
 *          and add product with value stored in the A10 register of the MMAU
 *          returning saturated 64-bit fractional A10 register value.
 * @param   lval1   @ref frac32_t fractional value.
 * @param   lval2   @ref frac32_t fractional value.
 * @return  @ref frac64_t fractional value.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation. If saturation occurs, the instruction sets the
 *          accumulation overflow (Q) and multiply or divide overflow (V) flags
 *          to 1 in the CSR. Otherwise, it clears the Q and V flags.
 ******************************************************************************/
static inline frac64_t MMAU_HAL_d_macs_ll (register frac32_t lval1, register frac32_t lval2)
{
  *((frac32_t volatile *)(MMAU__QMAC|MMAU__X2|MMAU__SAT))= lval1;
  *((frac32_t volatile *)(MMAU__QMAC|MMAU__X3|MMAU__SAT))= lval2;
  return *((frac64_t volatile *)(MMAU__QMAC| MMAU__A10|MMAU__SAT));
}

/***************************************************************************//*!
 * @brief   Multiplies 64-bit fractional value with 32-bit fractional value and
 *          adds product with value stored in the A10 register of the MMAU
 *          returning a 64-bit fractional A10 register value.
 * @details The @ref MMAU_HAL_d_mac_dl function multiplies 64-bit fractional value with
 *          32-bit fractional value and add product with value stored in the
 *          A10 register of the MMAU returning a 64-bit fractional A10 register
 *          value.
 * @param   dval    @ref frac64_t fractional value.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac64_t fractional value.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline frac64_t MMAU_HAL_d_mac_dl (register frac64_t dval, register frac32_t lval)
{
  *((frac64_t volatile *)(MMAU__QMACD|MMAU__X1))= dval;
  *((frac32_t volatile *)(MMAU__QMACD|MMAU__X3))= lval;
  return *((frac64_t volatile *)(MMAU__QMACD| MMAU__A10));
}

/***************************************************************************//*!
 * @brief   Saturating multiply 64-bit fractional value with 32-bit fractional
 *          value and add product with value stored in the A10 register of the MMAU
 *          returning saturated 64-bit fractional A10 register value.
 * @details The @ref MMAU_HAL_d_macs_dl function multiplies 64-bit fractional value with
 *          32-bit fractional value and add product with value stored in the
 *          A10 register of the MMAU returning saturated 64-bit fractional A10
 *          register value.
 * @param   dval    @ref frac64_t fractional value.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac64_t fractional value.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation. If saturation occurs, the instruction sets the
 *          accumulation overflow (Q) and multiply or divide overflow (V) flags
 *          to 1 in the CSR. Otherwise, it clears the Q and V flags.
 ******************************************************************************/
static inline frac64_t MMAU_HAL_d_macs_dl (register frac64_t dval, register frac32_t lval)
{
  *((frac64_t volatile *)(MMAU__QMACD|MMAU__X1|MMAU__SAT))= dval;
  *((frac32_t volatile *)(MMAU__QMACD|MMAU__X3|MMAU__SAT))= lval;
  return *((frac64_t volatile *)(MMAU__QMACD| MMAU__A10|MMAU__SAT));
}

/***************************************************************************//*!
 * @brief   Multiplies 32-bit fractional value by value stored in the A10 register
 *          of the MMAU and adds product with 64-bit fractional value returning
 *          a 64-bit fractional A10 register value.
 * @details The @ref MMAU_HAL_d_maca_dl function multiplies 32-bit fractional value by
 *          value stored in the A10 register of the MMAU and add product with
 *          64-bit fractional value returning a 64-bit fractional A10 register
 *          value.
 * @param   dval    @ref frac64_t fractional value.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac64_t fractional value.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline frac64_t MMAU_HAL_d_maca_dl (register frac64_t dval, register frac32_t lval)
{
  *((frac64_t volatile *)(MMAU__QMACDA|MMAU__X1))= dval;
  *((frac32_t volatile *)(MMAU__QMACDA|MMAU__X3))= lval;
  return *((frac64_t volatile *)(MMAU__QMACDA| MMAU__A10));
}

/***************************************************************************//*!
 * @brief   Saturating multiply 32-bit fractional value by value stored in the
 *          A10 register of the MMAU and add product with 64-bit fractional value returning
 *          a saturated 64-bit fractional A10 register value.
 * @details The @ref MMAU_HAL_d_macas_dl function multiplies 32-bit fractional value by
 *          value stored in the A10 register of the MMAU and add product with
 *          64-bit fractional value returning saturated 64-bit fractional A10
 *          register value.
 * @param   dval    @ref frac64_t fractional value.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac64_t fractional value.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation. If saturation occurs, the instruction sets the
 *          accumulation overflow (Q) and multiply or divide overflow (V) flags
 *          to 1 in the CSR. Otherwise, it clears the Q and V flags.
 ******************************************************************************/
static inline frac64_t MMAU_HAL_d_macas_dl (register frac64_t dval, register frac32_t lval)
{
  *((frac64_t volatile *)(MMAU__QMACDA|MMAU__X1|MMAU__SAT))= dval;
  *((frac32_t volatile *)(MMAU__QMACDA|MMAU__X3|MMAU__SAT))= lval;
  return *((frac64_t volatile *)(MMAU__QMACDA| MMAU__A10|MMAU__SAT));
}

/***************************************************************************//*!
 * @brief   Multiplies two 32-bit fractional values and add product with value
 *          stored in the A10 register of the MMAU returning a 32-bit fractional
 *          A10 register value.
 * @details The @ref MMAU_HAL_l_mac_ll function multiplies two 32-bit fractional values
 *          and add product with value stored in the A10 register of the MMAU
 *          returning a 32-bit fractional A1 register value.
 * @param   lval1   @ref frac32_t fractional value.
 * @param   lval2   @ref frac32_t fractional value.
 * @return  @ref frac32_t fractional value.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline frac32_t MMAU_HAL_l_mac_ll (register frac32_t lval1, register frac32_t lval2)
{
  *((frac32_t volatile *)(MMAU__QMAC|MMAU__X2))= lval1;
  *((frac32_t volatile *)(MMAU__QMAC|MMAU__X3))= lval2;
  return *((frac32_t volatile *)(MMAU__QMAC|MMAU__A1));
}

/***************************************************************************//*!
 * @brief   Saturating multiply two 32-bit fractional values and add product
 *          with value stored in the A10 register of the MMAU returning a 32-bit
 *          fractional A10 register value.
 * @details The @ref MMAU_HAL_l_macs_ll function multiplies two 32-bit fractional values
 *          and add product with value stored in the A10 register of the MMAU
 *          returning saturated 32-bit fractional A1 register value.
 * @param   lval1   @ref frac32_t fractional value.
 * @param   lval2   @ref frac32_t fractional value.
 * @return  @ref frac32_t fractional value.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation.
 ******************************************************************************/
static inline frac32_t MMAU_HAL_l_macs_ll (register frac32_t lval1, register frac32_t lval2)
{
  *((frac32_t volatile *)(MMAU__QMAC|MMAU__X2|MMAU__SAT))= lval1;
  *((frac32_t volatile *)(MMAU__QMAC|MMAU__X3|MMAU__SAT))= lval2;
  return *((frac32_t volatile *)(MMAU__QMAC|MMAU__A1|MMAU__SAT));
}

/***************************************************************************//*!
 * @brief   Multiplies 64-bit fractional value with 32-bit fractional value and
 *          adds product with value stored in the A10 register of the MMAU
 *          returning a 32-bit fractional A10 register value.
 * @details The @ref MMAU_HAL_l_mac_dl function multiplies 64-bit fractional value with
 *          32-bit fractional value and add product with value stored in the A10
 *          register of the MMAU returning a 32-bit fractional A1 register
 *          value.
 * @param   dval    @ref frac64_t fractional value.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac32_t fractional value.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline frac32_t MMAU_HAL_l_mac_dl (register frac64_t dval, register frac32_t lval)
{
  *((frac64_t volatile *)(MMAU__QMACD|MMAU__X1))= dval;
  *((frac32_t volatile *)(MMAU__QMACD|MMAU__X3))= lval;
  return *((frac32_t volatile *)(MMAU__QMACD|MMAU__A1));
}

/***************************************************************************//*!
 * @brief   Saturating multiply 64-bit fractional value with 32-bit fractional
 *          value and add product with value stored in the A10 register of the
 *          MMAU returning saturated 32-bit fractional A10 register value.
 * @details The @ref MMAU_HAL_l_macs_dl function multiplies 64-bit fractional value with
 *          32-bit fractional value and add product with value stored in the A10
 *          register of the MMAU returning saturated 32-bit fractional A1
 *          register value.
 * @param   dval    @ref frac64_t fractional value.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac32_t fractional value.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation.
 ******************************************************************************/
static inline frac32_t MMAU_HAL_l_macs_dl (register frac64_t dval, register frac32_t lval)
{
  *((frac64_t volatile *)(MMAU__QMACD|MMAU__X1|MMAU__SAT))= dval;
  *((frac32_t volatile *)(MMAU__QMACD|MMAU__X3|MMAU__SAT))= lval;
  return *((frac32_t volatile *)(MMAU__QMACD|MMAU__A1|MMAU__SAT));
}

/***************************************************************************//*!
 * @brief   Multiplies 32-bit fractional value by value stored in the A10 register
 *          of the MMAU and adds product with 64-bit fractional value returning a
 *          32-bit fractional A10 register value.
 * @details The @ref MMAU_HAL_l_maca_dl function multiplies 32-bit fractional value by
 *          value stored in the A10 register of the MMAU and add product with
 *          64-bit fractional value returning a 32-bit fractional A1 register
 *          value.
 * @param   dval    @ref frac64_t fractional value.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac32_t fractional value.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline frac32_t MMAU_HAL_l_maca_dl (register frac64_t dval, register frac32_t lval)
{
  *((frac64_t volatile *)(MMAU__QMACDA|MMAU__X1))= dval;
  *((frac32_t volatile *)(MMAU__QMACDA|MMAU__X3))= lval;
  return *((frac32_t volatile *)(MMAU__QMACDA|MMAU__A1));
}

/***************************************************************************//*!
 * @brief   Saturating multiply 32-bit fractional value by value stored in the
 *          A10 register of the MMAU and add product with 64-bit fractional
 *          value returning a saturated 32-bit fractional A10 register value.
 * @details The @ref MMAU_HAL_l_macas_dl function multiplies 32-bit fractional value by
 *          value stored in the A10 register of the MMAU and add product with
 *          64-bit fractional value returning saturated 32-bit fractional A1
 *          register value.
 * @param   dval    @ref frac64_t fractional value.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac32_t fractional value.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation.
 ******************************************************************************/
static inline frac32_t MMAU_HAL_l_macas_dl (register frac64_t dval, register frac32_t lval)
{
  *((frac64_t volatile *)(MMAU__QMACDA|MMAU__X1|MMAU__SAT))= dval;
  *((frac32_t volatile *)(MMAU__QMACDA|MMAU__X3|MMAU__SAT))= lval;
  return *((frac32_t volatile *)(MMAU__QMACDA|MMAU__A1|MMAU__SAT));
}

/***************************************************************************//*!
 * @brief   Divides two 32-bit fractional values returning a 32-bit fractional
 *          quotient.
 * @details The @ref MMAU_HAL_l_div_ll function divides two 32-bit fractional values
 *          returning a 32-bit fractional quotient.
 * @param   lnum    @ref frac32_t fractional value.
 * @param   lden    @ref frac32_t fractional value.
 * @return  @ref frac32_t fractional value.
 * @note    Quotient is stored in A1 register of the MMAU for next computation.
 ******************************************************************************/
static inline frac32_t MMAU_HAL_l_div_ll (register frac32_t lnum, register frac32_t lden)
{
  *((frac32_t volatile *)(MMAU__QDIV|MMAU__X2))=lnum;
  *((frac32_t volatile *)(MMAU__QDIV|MMAU__X3))=lden;
  return *((frac32_t volatile *)(MMAU__QDIV|MMAU__A1));
}

/***************************************************************************//*!
 * @brief   Divides two 32-bit fractional values returning a 32-bit fractional
 *          quotient.
 * @details The @ref MMAU_HAL_l_divs_ll function divides two 32-bit fractional values
 *          returning a 32-bit fractional quotient.
 * @param   lnum    @ref frac32_t fractional value.
 * @param   lden    @ref frac32_t fractional value.
 * @return  @ref frac32_t fractional value.
 * @note    Saturated quotient is  stored in A1 register of the MMAU for
 *          next computation. If saturation occurs, the instruction sets the
 *          accumulation overflow (Q) and multiply or divide overflow (V) flags
 *          to 1 in the CSR. Otherwise, it clears the Q and V flags.
 ******************************************************************************/
static inline frac32_t MMAU_HAL_l_divs_ll (register frac32_t lnum, register frac32_t lden)
{
  *((frac32_t volatile *)(MMAU__QDIV|MMAU__X2|MMAU__SAT))=lnum;
  *((frac32_t volatile *)(MMAU__QDIV|MMAU__X3|MMAU__SAT))=lden;
  return *((frac32_t volatile *)(MMAU__QDIV|MMAU__A1|MMAU__SAT));
}

/***************************************************************************//*!
 * @brief   Divides 64-bit fractional value stored in the A10 register of the
 *          MMAU by 32-bit fractional value returning saturated 32-bit
 *          fractional quotient.
 * @details The @ref MMAU_HAL_l_divas_l function divides 64-bit fractional value stored
 *          in the A10 register of the MMAU by 32-bit fractional value returning
 *          a saturated 32-bit fractional quotient.
 * @param   lden    @ref frac32_t fractional value.
 * @return  @ref frac32_t fractional value.
 * @note    Saturated quotient is stored in A1 register of the MMAU for next
 *          computation.
 ******************************************************************************/
static inline frac32_t MMAU_HAL_l_divas_l (register frac32_t lden)
{
  *((frac32_t volatile *)(MMAU__QDIVDA|MMAU__X3|MMAU__SAT))= lden;
  return *((frac32_t volatile *)(MMAU__QDIVDA|MMAU__A1|MMAU__SAT));
}

/***************************************************************************//*!
 * @brief   Divides 64-bit fractional value by 32-bit fractional value returning
 *          a 64-bit fractional quotient.
 * @details The @ref MMAU_HAL_d_div_dl function divides 64-bit fractional value by 32-bit
 *          fractional value returning a 64-bit fractional quotient.
 * @param   dnum    @ref frac64_t fractional value.
 * @param   lden    @ref frac32_t fractional value.
 * @return  @ref frac64_t fractional value.
 * @note    Quotient is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline frac64_t MMAU_HAL_d_div_dl (register frac64_t dnum, register frac32_t lden)
{
  *((frac64_t volatile *)(MMAU__QDIVD|MMAU__X1))= dnum;
  *((frac32_t volatile *)(MMAU__QDIVD|MMAU__X3))= lden;
  return *((frac64_t volatile *)(MMAU__QDIVD| MMAU__A10));
}

/***************************************************************************//*!
 * @brief   Divides 64-bit fractional value by 32-bit fractional value returning
 *          a 64-bit fractional quotient.
 * @details The @ref MMAU_HAL_d_divs_dl function divides 64-bit fractional value by
 *          32-bit fractional value returning a 64-bit fractional quotient.
 * @param   dnum    @ref frac64_t fractional value.
 * @param   lden    @ref frac32_t fractional value.
 * @return  @ref frac64_t fractional value.
 * @note    Saturated quotient is  stored in A10 register of the MMAU for
 *          next computation. If saturation occurs, the instruction sets the
 *          accumulation overflow (Q) and multiply or divide overflow (V) flags
 *          to 1 in the CSR. Otherwise, it clears the Q and V flags.
 ******************************************************************************/
static inline frac64_t MMAU_HAL_d_divs_dl (register frac64_t dnum, register frac32_t lden)
{
  *((frac64_t volatile *)(MMAU__QDIVD|MMAU__X1|MMAU__SAT))= dnum;
  *((frac32_t volatile *)(MMAU__QDIVD|MMAU__X3|MMAU__SAT))= lden;
  return *((frac64_t volatile *)(MMAU__QDIVD| MMAU__A10|MMAU__SAT));
}

/***************************************************************************//*!
 * @brief   Divides 32-bit fractional value stored in the A10 register of the
 *          MMAU by 32-bit fractional value returning a 64-bit fractional quotient.
 * @details The @ref MMAU_HAL_d_diva_l function divides 32-bit fractional value stored in
 *          the A10 register of the MMAU by 32-bit fractional value returning
 *          a 64-bit fractional quotient.
 * @param   lden1   @ref frac32_t fractional value.
 * @return  @ref frac64_t fractional value.
 * @note    Quotient is stored in A10 register of the MMAU for next computation.
 ******************************************************************************/
static inline frac64_t MMAU_HAL_d_diva_l (register frac32_t lden1)
{
  *((frac32_t volatile *)(MMAU__QDIVDA|MMAU__X3))=lden1;
  return *((frac64_t volatile *)(MMAU__QDIVDA| MMAU__A10));
}

/***************************************************************************//*!
 * @brief   Divides 32-bit fractional value stored in the A10 register of the
 *          MMAU by 32-bit fractional value returning saturated 64-bit fractional quotient.
 * @details The @ref MMAU_HAL_d_divas_l function divides 32-bit fractional value stored
 *          in the A10 register of the MMAU by 32-bit fractional value returning
 *          a saturated 64-bit fractional quotient.
 * @param   lden1   @ref frac32_t fractional value.
 * @return  @ref frac64_t fractional value.
 * @note    Saturated quotient is  stored in A10 register of the MMAU for
 *          next computation. If saturation occurs, the instruction sets the
 *          accumulation overflow (Q) and multiply or divide overflow (V) flags
 *          to 1 in the CSR. Otherwise, it clears the Q and V flags.
 ******************************************************************************/
static inline frac64_t MMAU_HAL_d_divas_l (register frac32_t lden1)
{
  *((frac32_t volatile *)(MMAU__QDIVDA|MMAU__X3|MMAU__SAT))=lden1;
  return *((frac64_t volatile *)(MMAU__QDIVDA| MMAU__A0|MMAU__SAT));
}

/***************************************************************************//*!
 * @brief   Divides 64-bit fractional value stored in the A10 register of the
 *          MMAU by 32-bit fractional value returning a 32-bit fractional
 *          quotient.
 * @details The @ref MMAU_HAL_l_diva_l function divides 64-bit fractional value stored in
 *          the A10 register of the MMAU by 32-bit fractional value returning a
 *          32-bit fractional quotient.
 * @param   lden    @ref frac32_t fractional value.
 * @return  @ref frac32_t fractional value.
 * @note    Quotient is stored in A1 register of the MMAU for next computation.
 ******************************************************************************/
static inline frac32_t MMAU_HAL_l_diva_l (register frac32_t lden)
{
  *((frac32_t volatile *)(MMAU__QDIVDA|MMAU__X3))= lden;
  return *((frac32_t volatile *)(MMAU__QDIVDA|MMAU__A1));
}
/***************************************************************************//*!
 * @brief   Computes and returns a 32-bit fractional square root of the 32-bit
 *          fractional radicand.
 * @details The @ref MMAU_HAL_l_sqr_l function computes and returns a 32-bit fractional
 *          square root of the 32-bit fractional radicand.
 * @param   lrad    @ref frac32_t fractional radicand.
 * @return  @ref frac32_t fractional square root.
 * @note    Square root is stored in A1 register of the MMAU for next
 *          computation.
 ******************************************************************************/
static inline frac32_t MMAU_HAL_l_sqr_l (register frac32_t lrad)
{
  *((frac32_t volatile *)(MMAU__QSQRD|MMAU__X2))= 0l;
  *((frac32_t volatile *)(MMAU__QSQRD|MMAU__X3))= lrad;
  return *((frac32_t volatile *)(MMAU__QSQRD|MMAU__A1));
}

/***************************************************************************//*!
 * @brief   Computes and returns a 32-bit fractional square root of the 64-bit
 *          fractional radicand.
 * @details The @ref MMAU_HAL_l_sqr_d function computes and returns a 32-bit fractional
 *          square root of the 64-bit fractional radicand.
 * @param   drad    @ref frac64_t fractional radicand.
 * @return  @ref frac32_t fractional square root.
 * @note    Quotient is stored in A1 register of the MMAU for next computation.
 ******************************************************************************/
static inline frac32_t MMAU_HAL_l_sqr_d (register frac64_t drad)
{
  *((frac64_t volatile *)(MMAU__QSQRD|MMAU__X2))=drad;
  return *((frac32_t volatile *)(MMAU__QSQRD|MMAU__A1));
}

/***************************************************************************//*!
 * @brief   Computes and returns a 32-bit fractional square root of the radicand
 *          stored in the A10 register of the MMAU.
 * @details The @ref MMAU_HAL_l_sqra function computes and returns a 32-bit fractional
 *          square root of the radicand stored in the A10 register of the MMAU.
 * @return  @ref frac32_t fractional square root.
 * @note    Quotient is stored in A1 register of the MMAU for next computation.
 ******************************************************************************/
static inline frac32_t MMAU_HAL_l_sqra (void)
{
  return *((frac32_t volatile *)(MMAU__QSQRDA|MMAU__A1));
}
/*@}*/
/*@}*/

#endif /* __FSL_MMAU_INS_H__ */
/******************************************************************************
 * EOF
 *****************************************************************************/

