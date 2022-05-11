/**
 * \file
 *
 * \brief Component description for DIVAS
 *
 * Copyright (c) 2018 Microchip Technology Inc.
 *
 * \asf_license_start
 *
 * \page License
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the Licence at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * \asf_license_stop
 *
 */

#ifndef _SAMC21_DIVAS_COMPONENT_
#define _SAMC21_DIVAS_COMPONENT_

/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR DIVAS */
/* ========================================================================== */
/** \addtogroup SAMC21_DIVAS Divide and Square Root Accelerator */
/*@{*/

#define DIVAS_U2258
#define REV_DIVAS                   0x100

/* -------- DIVAS_CTRLA : (DIVAS Offset: 0x00) (R/W  8) Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  SIGNED:1;         /*!< bit:      0  Signed                             */
    uint8_t  DLZ:1;            /*!< bit:      1  Disable Leading Zero Optimization  */
    uint8_t  :6;               /*!< bit:  2.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} DIVAS_CTRLA_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DIVAS_CTRLA_OFFSET          0x00         /**< \brief (DIVAS_CTRLA offset) Control */
#define DIVAS_CTRLA_RESETVALUE      _U_(0x00)    /**< \brief (DIVAS_CTRLA reset_value) Control */

#define DIVAS_CTRLA_SIGNED_Pos      0            /**< \brief (DIVAS_CTRLA) Signed */
#define DIVAS_CTRLA_SIGNED          (_U_(0x1) << DIVAS_CTRLA_SIGNED_Pos)
#define DIVAS_CTRLA_DLZ_Pos         1            /**< \brief (DIVAS_CTRLA) Disable Leading Zero Optimization */
#define DIVAS_CTRLA_DLZ             (_U_(0x1) << DIVAS_CTRLA_DLZ_Pos)
#define DIVAS_CTRLA_MASK            _U_(0x03)    /**< \brief (DIVAS_CTRLA) MASK Register */

/* -------- DIVAS_STATUS : (DIVAS Offset: 0x04) (R/W  8) Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  BUSY:1;           /*!< bit:      0  DIVAS Accelerator Busy             */
    uint8_t  DBZ:1;            /*!< bit:      1  Writing a one to this bit clears DBZ to zero */
    uint8_t  :6;               /*!< bit:  2.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} DIVAS_STATUS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DIVAS_STATUS_OFFSET         0x04         /**< \brief (DIVAS_STATUS offset) Status */
#define DIVAS_STATUS_RESETVALUE     _U_(0x00)    /**< \brief (DIVAS_STATUS reset_value) Status */

#define DIVAS_STATUS_BUSY_Pos       0            /**< \brief (DIVAS_STATUS) DIVAS Accelerator Busy */
#define DIVAS_STATUS_BUSY           (_U_(0x1) << DIVAS_STATUS_BUSY_Pos)
#define DIVAS_STATUS_DBZ_Pos        1            /**< \brief (DIVAS_STATUS) Writing a one to this bit clears DBZ to zero */
#define DIVAS_STATUS_DBZ            (_U_(0x1) << DIVAS_STATUS_DBZ_Pos)
#define DIVAS_STATUS_MASK           _U_(0x03)    /**< \brief (DIVAS_STATUS) MASK Register */

/* -------- DIVAS_DIVIDEND : (DIVAS Offset: 0x08) (R/W 32) Dividend -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t DIVIDEND:32;      /*!< bit:  0..31  DIVIDEND                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} DIVAS_DIVIDEND_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DIVAS_DIVIDEND_OFFSET       0x08         /**< \brief (DIVAS_DIVIDEND offset) Dividend */
#define DIVAS_DIVIDEND_RESETVALUE   _U_(0x00000000) /**< \brief (DIVAS_DIVIDEND reset_value) Dividend */

#define DIVAS_DIVIDEND_DIVIDEND_Pos 0            /**< \brief (DIVAS_DIVIDEND) DIVIDEND */
#define DIVAS_DIVIDEND_DIVIDEND_Msk (_U_(0xFFFFFFFF) << DIVAS_DIVIDEND_DIVIDEND_Pos)
#define DIVAS_DIVIDEND_DIVIDEND(value) (DIVAS_DIVIDEND_DIVIDEND_Msk & ((value) << DIVAS_DIVIDEND_DIVIDEND_Pos))
#define DIVAS_DIVIDEND_MASK         _U_(0xFFFFFFFF) /**< \brief (DIVAS_DIVIDEND) MASK Register */

/* -------- DIVAS_DIVISOR : (DIVAS Offset: 0x0C) (R/W 32) Divisor -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t DIVISOR:32;       /*!< bit:  0..31  DIVISOR                            */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} DIVAS_DIVISOR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DIVAS_DIVISOR_OFFSET        0x0C         /**< \brief (DIVAS_DIVISOR offset) Divisor */
#define DIVAS_DIVISOR_RESETVALUE    _U_(0x00000000) /**< \brief (DIVAS_DIVISOR reset_value) Divisor */

#define DIVAS_DIVISOR_DIVISOR_Pos   0            /**< \brief (DIVAS_DIVISOR) DIVISOR */
#define DIVAS_DIVISOR_DIVISOR_Msk   (_U_(0xFFFFFFFF) << DIVAS_DIVISOR_DIVISOR_Pos)
#define DIVAS_DIVISOR_DIVISOR(value) (DIVAS_DIVISOR_DIVISOR_Msk & ((value) << DIVAS_DIVISOR_DIVISOR_Pos))
#define DIVAS_DIVISOR_MASK          _U_(0xFFFFFFFF) /**< \brief (DIVAS_DIVISOR) MASK Register */

/* -------- DIVAS_RESULT : (DIVAS Offset: 0x10) (R/  32) Result -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t RESULT:32;        /*!< bit:  0..31  RESULT                             */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} DIVAS_RESULT_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DIVAS_RESULT_OFFSET         0x10         /**< \brief (DIVAS_RESULT offset) Result */
#define DIVAS_RESULT_RESETVALUE     _U_(0x00000000) /**< \brief (DIVAS_RESULT reset_value) Result */

#define DIVAS_RESULT_RESULT_Pos     0            /**< \brief (DIVAS_RESULT) RESULT */
#define DIVAS_RESULT_RESULT_Msk     (_U_(0xFFFFFFFF) << DIVAS_RESULT_RESULT_Pos)
#define DIVAS_RESULT_RESULT(value)  (DIVAS_RESULT_RESULT_Msk & ((value) << DIVAS_RESULT_RESULT_Pos))
#define DIVAS_RESULT_MASK           _U_(0xFFFFFFFF) /**< \brief (DIVAS_RESULT) MASK Register */

/* -------- DIVAS_REM : (DIVAS Offset: 0x14) (R/  32) Remainder -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t REM:32;           /*!< bit:  0..31  REM                                */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} DIVAS_REM_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DIVAS_REM_OFFSET            0x14         /**< \brief (DIVAS_REM offset) Remainder */
#define DIVAS_REM_RESETVALUE        _U_(0x00000000) /**< \brief (DIVAS_REM reset_value) Remainder */

#define DIVAS_REM_REM_Pos           0            /**< \brief (DIVAS_REM) REM */
#define DIVAS_REM_REM_Msk           (_U_(0xFFFFFFFF) << DIVAS_REM_REM_Pos)
#define DIVAS_REM_REM(value)        (DIVAS_REM_REM_Msk & ((value) << DIVAS_REM_REM_Pos))
#define DIVAS_REM_MASK              _U_(0xFFFFFFFF) /**< \brief (DIVAS_REM) MASK Register */

/* -------- DIVAS_SQRNUM : (DIVAS Offset: 0x18) (R/W 32) Square Root Input -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t SQRNUM:32;        /*!< bit:  0..31  Square Root Input                  */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} DIVAS_SQRNUM_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DIVAS_SQRNUM_OFFSET         0x18         /**< \brief (DIVAS_SQRNUM offset) Square Root Input */
#define DIVAS_SQRNUM_RESETVALUE     _U_(0x00000000) /**< \brief (DIVAS_SQRNUM reset_value) Square Root Input */

#define DIVAS_SQRNUM_SQRNUM_Pos     0            /**< \brief (DIVAS_SQRNUM) Square Root Input */
#define DIVAS_SQRNUM_SQRNUM_Msk     (_U_(0xFFFFFFFF) << DIVAS_SQRNUM_SQRNUM_Pos)
#define DIVAS_SQRNUM_SQRNUM(value)  (DIVAS_SQRNUM_SQRNUM_Msk & ((value) << DIVAS_SQRNUM_SQRNUM_Pos))
#define DIVAS_SQRNUM_MASK           _U_(0xFFFFFFFF) /**< \brief (DIVAS_SQRNUM) MASK Register */

/** \brief DIVAS hardware registers */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef struct {
  __IO DIVAS_CTRLA_Type          CTRLA;       /**< \brief Offset: 0x00 (R/W  8) Control */
       RoReg8                    Reserved1[0x3];
  __IO DIVAS_STATUS_Type         STATUS;      /**< \brief Offset: 0x04 (R/W  8) Status */
       RoReg8                    Reserved2[0x3];
  __IO DIVAS_DIVIDEND_Type       DIVIDEND;    /**< \brief Offset: 0x08 (R/W 32) Dividend */
  __IO DIVAS_DIVISOR_Type        DIVISOR;     /**< \brief Offset: 0x0C (R/W 32) Divisor */
  __I  DIVAS_RESULT_Type         RESULT;      /**< \brief Offset: 0x10 (R/  32) Result */
  __I  DIVAS_REM_Type            REM;         /**< \brief Offset: 0x14 (R/  32) Remainder */
  __IO DIVAS_SQRNUM_Type         SQRNUM;      /**< \brief Offset: 0x18 (R/W 32) Square Root Input */
} Divas;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/*@}*/

#endif /* _SAMC21_DIVAS_COMPONENT_ */
