/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_RAND_RA6W1_H
#define BSP_RAND_RA6W1_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define PRNG_PAR_TYPE_32_BITS        (2U)
#define TRNG_DEF_SAMPLES_CNT         0X14
#define TRNG_REG_POLL_RETRY_LIMIT    10000
#define TRNG_RETRY_LIMIT 8

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/
bool     trng_init_regs(void);
bool     trng_is_valid(void);
uint32_t prng_rand(void);
uint32_t trng_rand(void);

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
