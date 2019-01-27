/* ------------------------------------------
 * Copyright (c) 2016, Synopsys, Inc. All rights reserved.

 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:

 * 1) Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.

 * 2) Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.

 * 3) Neither the name of the Synopsys, Inc., nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.

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
 *
 * \version 2016.05
 * \date 2014-12-25
 * \author Wayne Ren(Wei.Ren@synopsys.com)
--------------------------------------------- */

/**
 * \file
 * \ingroup	EMBARC_ERROR
 * \brief	header file to define common definitions error management
 */

/**
 * \addtogroup	EMBARC_ERROR
 * @{
 */

#ifndef _EMBARC_ERROR_H_
#define _EMBARC_ERROR_H_

#include <stdint.h>
#include "inc/arc/arc_builtin.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * \name	Main Error Code Definitions
 * @{
 */
#define E_OK		(0)		/*!< ok */
#define E_SYS		(-5)		/*!< system error */
#define E_NOSPT		(-9)		/*!< unsupported features */
#define E_RSFN		(-10)		/*!< reserved function code */
#define E_RSATR		(-11)		/*!< reserved attribute */
#define E_PAR		(-17)		/*!< parameter error */
#define E_ID		(-18)		/*!< invalid ID number */
#define E_CTX		(-25)		/*!< context error */
#define E_MACV		(-26)		/*!< memory access violation */
#define E_OACV		(-27)		/*!< object access violation */
#define E_ILUSE		(-28)		/*!< illegal service call use */
#define E_NOMEM		(-33)		/*!< insufficient memory */
#define E_NOID		(-34)		/*!< no ID number available */
#define E_NORES		(-35)		/*!< no resource available */
#define E_OBJ		(-41)		/*!< object state error */
#define E_NOEXS		(-42)		/*!< non-existent object */
#define E_QOVR		(-43)		/*!< queue overflow */
#define E_RLWAI		(-49)		/*!< forced release from waiting */
#define E_TMOUT		(-50)		/*!< polling failure or timeout */
#define E_DLT		(-51)		/*!< waiting object deleted */
#define E_CLS		(-52)		/*!< waiting object state changed */
#define E_WBLK		(-57)		/*!< non-blocking accepted */
#define E_BOVR		(-58)		/*!< buffer overflow */
#define E_OPNED		(-6)		/*!< device is opened */
#define E_CLSED		(-7)		/*!< device is closed */
/** @} end of name */

/**
 * \name	Generate And Decompose Error Code
 * @{
 */
#ifndef ERCD
/** generate error code using main error code and sub error code */
#define ERCD(mercd, sercd) \
		((uint32_t)((((uint32_t) sercd) << 8) | (((uint32_t) mercd) & 0xffU)))
#endif /* ERCD */

#ifndef MERCD
#ifdef INT8_MAX
/** get main error code from error code */
#define MERCD(ercd)		((uint32_t)((int8_t)(ercd)))
#else /* INT8_MAX */
/** get main error code from error code */
#define MERCD(ercd)		((uint32_t)(((uint32_t) ercd) | ~0xffU))
#endif /* INT8_MAX */
#endif /* MERCD */

#ifndef SERCD
/** get sub error code from error code */
#define SERCD(ercd)		((uint32_t)((ercd) >> 8))
#endif /* SERCD */
/** @} end of name */

/**
 * \name	Check Error
 * @{
 */
/**
 * \brief   check an expression to see if it is right, and when error
 * 	set the ercd, and goto exit_label
 * \param   EXPR	the expression that need to be checked (==0 failed)
 * \param   ERCD	MUST pass a variable to here to get the error code
 * \param   ERROR_CODE error code that pass to ERCD
 * \param   EXIT_LABEL a label to go when error happens
 */
#define CHECK_EXP(EXPR, ERCD, ERROR_CODE, EXIT_LABEL) 	{	\
		if (_arc_rarely(!(EXPR))) { 			\
			ERCD = (ERROR_CODE);			\
			goto EXIT_LABEL;			\
		}						\
	}
/**
 * \brief   check an expression to see if it is right, and when error
 * 			directly goto exit_label
 * \param   EXPR       the expression that need to be checked (==0 failed)
 * \param   EXIT_LABEL a label to go when error happens
 * \retval
 */
#define CHECK_EXP_NOERCD(EXPR, EXIT_LABEL) {			\
		if (_arc_rarely(!(EXPR))) { 			\
			goto EXIT_LABEL;			\
		}						\
	}
/** check cnt bytes align, 1 for aligned, 0 for not-aligned */
#define CHECK_ALIGN_BYTES(pointer, cnt)		((((uint32_t)(pointer)) & (cnt-1)) == 0)
/** check 2 bytes align, 1 for aligned, 0 for not-aligned */
#define CHECK_ALIGN_2BYTES(pointer)		((((uint32_t)(pointer)) & 0x1) == 0)
/** check 4 bytes align, 1 for aligned, 0 for not-aligned */
#define CHECK_ALIGN_4BYTES(pointer)		((((uint32_t)(pointer)) & 0x3) == 0)
/** check 8 bytes align, 1 for aligned, 0 for not-aligned */
#define CHECK_ALIGN_8BYTES(pointer)		((((uint32_t)(pointer)) & 0x7) == 0)
/** @} end of name */

#ifdef __cplusplus
}
#endif

#endif /* _EMBARC_ERROR_H_ */
/** @} end of group EMBARC_ERROR */
