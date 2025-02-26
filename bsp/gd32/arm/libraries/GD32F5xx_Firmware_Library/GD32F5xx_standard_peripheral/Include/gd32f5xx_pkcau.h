/*!
    \file    gd32f5xx_pkcau.h
    \brief   definitions for the PKCAU

    \version 2024-07-31, V1.1.0, firmware for GD32F5xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#ifndef GD32F5XX_PKCAU_H
#define GD32F5XX_PKCAU_H

#include "gd32f5xx.h"

/* PKCAU definitions */
#define PKCAU                             PKCAU_BASE                    /*!< PKCAU base address */

/* registers definitions */
#define PKCAU_CTL                         REG32(PKCAU + 0x00000000U)    /*!< PKCAU control register */
#define PKCAU_STAT                        REG32(PKCAU + 0x00000004U)    /*!< PKCAU status register */
#define PKCAU_STATC                       REG32(PKCAU + 0x00000008U)    /*!< PKCAU status clear register */

/* bits definitions */
/* PKCAU_CTL */
#define PKCAU_CTL_PKCAUEN                 BIT(0)                        /*!< PKCAU peripheral enable */
#define PKCAU_CTL_START                   BIT(1)                        /*!< start operation */
#define PKCAU_CTL_MODESEL                 BITS(8,13)                    /*!< operation mode selection */
#define PKCAU_CTL_ENDIE                   BIT(17)                       /*!< end of operation interrupt enable */
#define PKCAU_CTL_RAMERRIE                BIT(19)                       /*!< RAM error interrupt enable */
#define PKCAU_CTL_ADDRERRIE               BIT(20)                       /*!< address error interrupt enable */

/* PKCAU_STAT */
#define PKCAU_STAT_BUSY                   BIT(16)                       /*!< busy flag */
#define PKCAU_STAT_ENDF                   BIT(17)                       /*!< end of PKCAU operation */
#define PKCAU_STAT_RAMERR                 BIT(19)                       /*!< PKCAU RAM error */
#define PKCAU_STAT_ADDRERR                BIT(20)                       /*!< address error */

/* PKCAU_STATC */
#define PKCAU_STATC_ENDFC                 BIT(17)                       /*!< end of PKCAU operation flag clear */
#define PKCAU_STATC_RAMERRC               BIT(19)                       /*!< PKCAU RAM error flag clear */
#define PKCAU_STATC_ADDRERRC              BIT(20)                       /*!< address error flag clear */

/* constants definitions */
/* montgomery parameter structure */
typedef struct{
    const uint8_t* modulus_n;                                           /*!< modulus value n */
    uint32_t modulus_n_len;                                             /*!< modulus length in byte */
}pkcau_mont_parameter_struct;

/* modular addition, modular subtraction, montgomery multiplication, modular inversion, modular reduction parameter structure */
typedef struct{
    const uint8_t* oprd_a;                                              /*!< operand A */
    uint32_t oprd_a_len;                                                /*!< operand A length in byte */
    const uint8_t* oprd_b;                                              /*!< operand B */
    uint32_t oprd_b_len;                                                /*!< operand b length in byte */
    const uint8_t* modulus_n;                                           /*!< modulus value n */
    uint32_t modulus_n_len;                                             /*!< modulus length in byte */
}pkcau_mod_parameter_struct;

/* modular exponentiation parameter structure */
typedef struct{
    const uint8_t* oprd_a;                                              /*!< operand A */
    uint32_t oprd_a_len;                                                /*!< operand A length in byte */
    const uint8_t* exp_e;                                               /*!< exponent e */
    uint32_t e_len;                                                     /*!< exponent length in byte */
    const uint8_t* modulus_n;                                           /*!< modulus n */
    uint32_t modulus_n_len;                                             /*!< modulus length in byte */
    uint8_t* mont_para;                                                 /*!< montgomery parameter R2 mod n */
    uint32_t mont_para_len;                                             /*!< montgomery parameter length in byte */
}pkcau_mod_exp_parameter_struct;

/* arithmetic addition, arithmetic subtraction, arithmetic multiplication and arithmetic comparison parameter structure */
typedef struct{
    const uint8_t* oprd_a;                                              /*!< operand A */
    uint32_t oprd_a_len;                                                /*!< length of operand in byte */
    const uint8_t* oprd_b;                                              /*!< operand B */
    uint32_t oprd_b_len;                                                /*!< length of operand in byte */
}pkcau_arithmetic_parameter_struct;

/* CRT parameter structure */
typedef struct{
    const uint8_t* oprd_a;                                              /*!< operand A */
    uint32_t oprd_a_len;                                                /*!< length of operand in byte */
    uint8_t* oprd_dp;                                                   /*!< operand dp */
    uint32_t oprd_dp_len;                                               /*!< length of operand dp in byte */
    uint8_t* oprd_dq;                                                   /*!< operand dq */
    uint32_t oprd_dq_len;                                               /*!< length of operand dq in byte */
    uint8_t* oprd_qinv;                                                 /*!< operand qinv */
    uint32_t oprd_qinv_len;                                             /*!< length of operand qinv in byte */
    uint8_t* oprd_p;                                                    /*!< prime operand p */
    uint32_t oprd_p_len;                                                /*!< length of operand p in byte */
    uint8_t* oprd_q;                                                    /*!< prime operand q */
    uint32_t oprd_q_len;                                                /*!< length of operand q in byte */
}pkcau_crt_parameter_struct;

/* ECC curve parameter structure */
typedef struct{
    uint8_t* modulus_p;                                                 /*!< curve modulus p */
    uint32_t modulus_p_len;                                             /*!< curve modulus p length in byte */
    uint8_t* coff_a;                                                    /*!< curve coefficient a */
    uint32_t coff_a_len;                                                /*!< curve coefficient a length in byte */
    uint8_t* coff_b;                                                    /*!< curve coefficient b */
    uint32_t coff_b_len;                                                /*!< curve coefficient b length in byte */
    uint8_t* base_point_x;                                              /*!< curve base point coordinate x */
    uint32_t base_point_x_len;                                          /*!< curve base point coordinate x length in byte */
    uint8_t* base_point_y;                                              /*!< curve base point coordinate y */
    uint32_t base_point_y_len;                                          /*!< curve base point coordinate y length in byte */
    uint8_t* order_n;                                                   /*!< curve prime order n */
    uint32_t order_n_len;                                               /*!< curve prime order n length in byte */
    uint32_t a_sign;                                                    /*!< curve coefficient a sign */

    const uint8_t* multi_k;                                             /*!< scalar multiplier k */
    uint32_t multi_k_len;                                               /*!< scalar multiplier k length in byte */

    const uint8_t* integer_k;                                           /*!< integer k */
    uint32_t integer_k_len;                                             /*!< integer k length in byte */
    const uint8_t* private_key_d;                                       /*!< private key d */
    uint32_t private_key_d_len;                                         /*!< private key d length in byte */
    uint8_t* mont_para;                                                 /*!< montgomery parameter R2 mod n */
    uint32_t mont_para_len;                                             /*!< montgomery parameter R2 mod n length in byte */
}pkcau_ec_group_parameter_struct;

/* point structure */
typedef struct{
    const uint8_t* point_x;                                             /*!< point coordinate x */
    uint32_t point_x_len;                                               /*!< point coordinate x length in byte > */
    const uint8_t* point_y;                                             /*!< point coordinate y */
    uint32_t point_y_len;                                               /*!< point coordinate y length in byte > */
}pkcau_point_parameter_struct;

/* signature structure */
typedef struct{
    const uint8_t* sign_r;                                              /*!< signature part r */
    uint32_t sign_r_len;                                                /*!< signature part r lnegth in byte */
    const uint8_t* sign_s;                                              /*!< signature part s */
    uint32_t sign_s_len;                                                /*!< signature part s lnegth in byte */
}pkcau_signature_parameter_struct;

/* hash structure */
typedef struct {
    const uint8_t *hash_z;                                              /*!< hash value z */
    uint32_t hash_z_len;                                                /*!< hash value z length in byte */
}pkcau_hash_parameter_struct;


/* ecdsa signature, ecc scalar multiplication output structure */
typedef struct{
    uint32_t sign_extra;                                                /*!< flag of extended ECDSA sign (extra outputs) */
    uint8_t* sign_r;                                                    /*!< pointer to signature part r */
    uint8_t* sign_s;                                                    /*!< pointer to signature part s */
    uint8_t* point_x;                                                   /*!< pointer to point kP coordinate x */
    uint8_t* point_y;                                                   /*!< pointer to point kP coordinate y */
}pkcau_ecc_out_struct;


/* PKCAU operation code */
#define CTL_MODE(regval)                  (BITS(8,13) & ((uint32_t)(regval) << 8))
#define PKCAU_MODE_MOD_EXP                CTL_MODE(0)                   /*!< montgomery parameter computation then modular exponentiation */
#define PKCAU_MODE_MONT_PARAM             CTL_MODE(1)                   /*!< montgomery parameter computation only */
#define PKCAU_MODE_MOD_EXP_FAST           CTL_MODE(2)                   /*!< modular exponentiation only */
#define PKCAU_MODE_CRT_EXP                CTL_MODE(7)                   /*!< RSA CRT exponentiation */
#define PKCAU_MODE_MOD_INVERSION          CTL_MODE(8)                   /*!< modular inversion */
#define PKCAU_MODE_ARITHMETIC_ADD         CTL_MODE(9)                   /*!< arithmetic addition */
#define PKCAU_MODE_ARITHMETIC_SUB         CTL_MODE(10)                  /*!< arithmetic subtraction */
#define PKCAU_MODE_ARITHMETIC_MUL         CTL_MODE(11)                  /*!< arithmetic multiplication */
#define PKCAU_MODE_ARITHMETIC_COMP        CTL_MODE(12)                  /*!< arithmetic comparison */
#define PKCAU_MODE_MOD_REDUCTION          CTL_MODE(13)                  /*!< modular reduction */
#define PKCAU_MODE_MOD_ADD                CTL_MODE(14)                  /*!< modular addition */
#define PKCAU_MODE_MOD_SUB                CTL_MODE(15)                  /*!< modular subtraction */
#define PKCAU_MODE_MONT_MUL               CTL_MODE(16)                  /*!< montgomery multiplication */
#define PKCAU_MODE_ECC_SCALAR_MUL         CTL_MODE(32)                  /*!< montgomery parameter computation then ECC scalar multiplication */
#define PKCAU_MODE_ECC_SCALAR_MUL_FAST    CTL_MODE(34)                  /*!< ECC scalar multiplication only */
#define PKCAU_MODE_ECDSA_SIGN             CTL_MODE(36)                  /*!< ECDSA sign */
#define PKCAU_MODE_ECDSA_VERIFICATION     CTL_MODE(38)                  /*!< ECDSA verification */
#define PKCAU_MODE_POINT_CHECK            CTL_MODE(40)                  /*!< point on elliptic curve Fp check */

/* PKCAU interrupt */
#define PKCAU_INT_ADDRERR                 PKCAU_CTL_ADDRERRIE           /*!< address error interrupt enable */
#define PKCAU_INT_RAMERR                  PKCAU_CTL_RAMERRIE            /*!< RAM error interrupt enable */
#define PKCAU_INT_END                     PKCAU_CTL_ENDIE               /*!< end of operation interrupt enable */

/* PKCAU flag definitions */
#define PKCAU_FLAG_ADDRERR                PKCAU_STAT_ADDRERR            /*!< address error flag */
#define PKCAU_FLAG_RAMERR                 PKCAU_STAT_RAMERR             /*!< PKCAU RAM error flag */
#define PKCAU_FLAG_END                    PKCAU_STAT_ENDF               /*!< end of PKCAU operation flag */
#define PKCAU_FLAG_BUSY                   PKCAU_STAT_BUSY               /*!< busy flag */

/* PKCAU interrupt flag definitions */
#define PKCAU_INT_FLAG_ADDRERR            PKCAU_STAT_ADDRERR            /*!< address error flag */
#define PKCAU_INT_FLAG_RAMERR             PKCAU_STAT_RAMERR             /*!< PKCAU RAM error flag */
#define PKCAU_INT_FLAG_ENDF               PKCAU_STAT_ENDF               /*!< end of PKCAU operation flag */

/* function declarations */
/* initialization functions */
/* reset pkcau */
void pkcau_deinit(void);
/* initialize montgomery parameter structure with a default value */
void pkcau_mont_struct_para_init(pkcau_mont_parameter_struct* init_para);
/* initialize modular parameter structure with a default value */
void pkcau_mod_struct_para_init(pkcau_mod_parameter_struct* init_para);
/* initialize modular exponentiation parameter structure with a default value */
void pkcau_mod_exp_struct_para_init(pkcau_mod_exp_parameter_struct* init_para);
/* initialize arithmetic parameter structure with a default value */
void pkcau_arithmetic_struct_para_init(pkcau_arithmetic_parameter_struct* init_para);
/* initialize CRT parameter structure with a default value */
void pkcau_crt_struct_para_init(pkcau_crt_parameter_struct* init_para);
/* initialize ECC curve parameter structure with a default value */
void pkcau_ec_group_struct_para_init(pkcau_ec_group_parameter_struct* init_para);
/* initialize point parameter structure with a default value */
void pkcau_point_struct_para_init(pkcau_point_parameter_struct* init_para);
/* initialize signature parameter structure with a default value */
void pkcau_signature_struct_para_init(pkcau_signature_parameter_struct* init_para);
/* initialize hash parameter structure with a default value */
void pkcau_hash_struct_para_init(pkcau_hash_parameter_struct* init_para);
/* initialize ecc output parameter structure with a default value */
void pkcau_ecc_out_struct_para_init(pkcau_ecc_out_struct* init_para);

/* application function declarations */
/* enable PKCAU */
void pkcau_enable(void);
/* disable PKCAU */
void pkcau_disable(void);
/* start operation */
void pkcau_start(void);
/* configure the PKCAU operation mode */
void pkcau_mode_set(uint32_t mode);
/* execute montgomery parameter operation */
void pkcau_mont_param_operation(pkcau_mont_parameter_struct* mont_para, uint8_t* results);
/* execute modular operation, include modular addition, modular subtraction and montgomery multiplication */
void pkcau_mod_operation(pkcau_mod_parameter_struct* mod_para, uint32_t mode, uint8_t* results);
/* execute modular exponentiation operation */
void pkcau_mod_exp_operation(pkcau_mod_exp_parameter_struct* mod_exp_para, uint32_t mode, uint8_t* results);
/* execute modular inversion operation */
void pkcau_mod_inver_operation(pkcau_mod_parameter_struct* mod_inver_para, uint8_t* results);
/* execute modular reduction operation */
void pkcau_mod_reduc_operation(pkcau_mod_parameter_struct* mod_reduc_para, uint8_t* results);
/* execute arithmetic addition operation */
void pkcau_arithmetic_operation(pkcau_arithmetic_parameter_struct* arithmetic_para, uint32_t mode, uint8_t* results);
/* execute RSA CRT exponentiation operation */
void pkcau_crt_exp_operation(pkcau_crt_parameter_struct* crt_para, uint8_t* results);
/* execute point check operation */
uint8_t pkcau_point_check_operation(pkcau_point_parameter_struct* point_para, const pkcau_ec_group_parameter_struct* curve_group_para);
/* execute point multiplication operation */
void pkcau_point_mul_operation(pkcau_point_parameter_struct* point_para, const pkcau_ec_group_parameter_struct* curve_group_para, uint32_t mode, pkcau_ecc_out_struct* result);
/* execute ECDSA sign operation */
uint8_t pkcau_ecdsa_sign_operation(pkcau_hash_parameter_struct* hash_para, const pkcau_ec_group_parameter_struct* curve_group_para, pkcau_ecc_out_struct* result);
/* execute ECDSA verify operation */
uint8_t pkcau_ecdsa_verification_operation(pkcau_point_parameter_struct* point_para, pkcau_hash_parameter_struct* hash_para, pkcau_signature_parameter_struct* signature_para, const pkcau_ec_group_parameter_struct* curve_group_para);

/* interrupt & flag functions */
/* get PKCAU flag status */
FlagStatus pkcau_flag_get(uint32_t flag);
/* clear PKCAU flag status */
void pkcau_flag_clear(uint32_t flag);
/* enable PKCAU interrupt */
void pkcau_interrupt_enable(uint32_t interrupt);
/* disable PKCAU interrupt */
void pkcau_interrupt_disable(uint32_t interrupt);
/* get PKCAU interrupt flag status */
FlagStatus pkcau_interrupt_flag_get(uint32_t int_flag);
/* clear PKCAU interrupt flag status */
void pkcau_interrupt_flag_clear(uint32_t int_flag);

#endif /* GD32F5XX_PKCAU_H */

