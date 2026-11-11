/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#ifndef __HW_CRYPTO_ROCKCHIP_V2_H__
#define __HW_CRYPTO_ROCKCHIP_V2_H__

#include <rtthread.h>
#include <hwcrypto.h>
#include <hw_bignum.h>

#include <drivers/misc.h>

#define _SBF(s, v)                      ((v) << (s))

#define CRYPTO_WRITE_MASK_SHIFT         (16)
#define CRYPTO_WRITE_MASK_ALL           ((0xffffu << CRYPTO_WRITE_MASK_SHIFT))

#define CRYPTO_CLK_CTL                  0x0000
#define CRYPTO_AUTO_CLKGATE_EN          RT_BIT(0)

#define CRYPTO_RST_CTL                  0x0004
#define CRYPTO_SW_PKA_RESET             RT_BIT(2)
#define CRYPTO_SW_RNG_RESET             RT_BIT(1)
#define CRYPTO_SW_CC_RESET              RT_BIT(0)

#define CRYPTO_DMA_INT_EN               0x0008
#define CRYPTO_ZERO_ERR_INT_EN          RT_BIT(6)
#define CRYPTO_LIST_ERR_INT_EN          RT_BIT(5)
#define CRYPTO_SRC_ERR_INT_EN           RT_BIT(4)
#define CRYPTO_DST_ERR_INT_EN           RT_BIT(3)
#define CRYPTO_SRC_ITEM_INT_EN          RT_BIT(2)
#define CRYPTO_DST_ITEM_DONE_INT_EN     RT_BIT(1)
#define CRYPTO_LIST_DONE_INT_EN         RT_BIT(0)

#define CRYPTO_DMA_INT_ST               0x000C
#define CRYPTO_LOCKSTEP_INT_ST          RT_BIT(7)
#define CRYPTO_ZERO_LEN_INT_ST          RT_BIT(6)
#define CRYPTO_LIST_ERR_INT_ST          RT_BIT(5)
#define CRYPTO_SRC_ERR_INT_ST           RT_BIT(4)
#define CRYPTO_DST_ERR_INT_ST           RT_BIT(3)
#define CRYPTO_SRC_ITEM_DONE_INT_ST     RT_BIT(2)
#define CRYPTO_DST_ITEM_DONE_INT_ST     RT_BIT(1)
#define CRYPTO_LIST_DONE_INT_ST         RT_BIT(0)

#define CRYPTO_DMA_CTL                  0x0010
#define CRYPTO_DMA_RESTART              RT_BIT(1)
#define CRYPTO_DMA_START                RT_BIT(0)

#define CRYPTO_DMA_LLI_ADDR             0x0014

#define CRYPTO_FIFO_CTL                 0x0040
#define CRYPTO_DOUT_BYTESWAP            RT_BIT(1)
#define CRYPTO_DOIN_BYTESWAP            RT_BIT(0)

#define CRYPTO_BC_CTL                   0x0044
#define CRYPTO_BC_AES                   _SBF(8, 0x00)
#define CRYPTO_BC_SM4                   _SBF(8, 0x01)
#define CRYPTO_BC_DES                   _SBF(8, 0x02)
#define CRYPTO_BC_TDES                  _SBF(8, 0x03)
#define CRYPTO_BC_ECB                   _SBF(4, 0x00)
#define CRYPTO_BC_CBC                   _SBF(4, 0x01)
#define CRYPTO_BC_CTS                   _SBF(4, 0x02)
#define CRYPTO_BC_CTR                   _SBF(4, 0x03)
#define CRYPTO_BC_CFB                   _SBF(4, 0x04)
#define CRYPTO_BC_OFB                   _SBF(4, 0x05)
#define CRYPTO_BC_XTS                   _SBF(4, 0x06)
#define CRYPTO_BC_CCM                   _SBF(4, 0x07)
#define CRYPTO_BC_GCM                   _SBF(4, 0x08)
#define CRYPTO_BC_128_bit_key           _SBF(2, 0x00)
#define CRYPTO_BC_192_bit_key           _SBF(2, 0x01)
#define CRYPTO_BC_256_bit_key           _SBF(2, 0x02)
#define CRYPTO_BC_DECRYPT               RT_BIT(1)
#define CRYPTO_BC_ENABLE                RT_BIT(0)

#define CRYPTO_HASH_CTL                 0x0048
#define CRYPTO_SHA1                     _SBF(4, 0x00)
#define CRYPTO_MD5                      _SBF(4, 0x01)
#define CRYPTO_SHA256                   _SBF(4, 0x02)
#define CRYPTO_SHA224                   _SBF(4, 0x03)
#define CRYPTO_SM3                      _SBF(4, 0x06)
#define CRYPTO_SHA512                   _SBF(4, 0x08)
#define CRYPTO_SHA384                   _SBF(4, 0x09)
#define CRYPTO_HMAC_ENABLE              RT_BIT(3)
#define CRYPTO_HW_PAD_ENABLE            RT_BIT(2)
#define CRYPTO_HASH_ENABLE              RT_BIT(0)

#define CRYPTO_CH0_IV_0                 0x0100
#define CRYPTO_CH0_KEY_0                0x0180
#define CRYPTO_CH0_IV_LEN_0             0x0300

#define CRYPTO_CH0_PC_LEN_0             0x0280
#define CRYPTO_CH0_PC_LEN_1             0x0284
#define CRYPTO_CH0_AAD_LEN_0            0x02c0
#define CRYPTO_CH0_AAD_LEN_1            0x02c4

#define CRYPTO_CH0_TAG_0                0x0320
#define CRYPTO_CH0_TAG_1                0x0324
#define CRYPTO_CH0_TAG_2                0x0328
#define CRYPTO_CH0_TAG_3                0x032c

#define CRYPTO_HASH_DOUT_0              0x03a0

#define CRYPTO_TAG_VALID                0x03e0
#define CRYPTO_CH0_TAG_VALID            RT_BIT(0)

#define CRYPTO_HASH_VALID               0x03e4
#define CRYPTO_HASH_IS_VALID            RT_BIT(0)

#define LLI_DMA_CTRL_LAST               RT_BIT(0)
#define LLI_DMA_CTRL_PAUSE              RT_BIT(1)
#define LLI_DMA_CTRL_LIST_DONE          RT_BIT(8)
#define LLI_DMA_CTRL_DST_DONE           RT_BIT(9)
#define LLI_DMA_CTRL_SRC_DONE           RT_BIT(10)

#define LLI_USER_CIPHER_START           RT_BIT(0)
#define LLI_USER_STRING_START           RT_BIT(1)
#define LLI_USER_STRING_LAST            RT_BIT(2)
#define LLI_USER_STRING_AAD             RT_BIT(3)

#define CRYPTO_PKA_BASE_OFFSET          0x0480

#define CRYPTO_RAM_CTL                  (0x0480 - CRYPTO_PKA_BASE_OFFSET)
#define CRYPTO_RAM_CTL_SEL_MASK         _SBF(16, 3)
#define CRYPTO_RAM_CTL_CPU              _SBF(0, 0)
#define CRYPTO_RAM_CTL_PKA              _SBF(0, 1)
#define CRYPTO_RAM_CTL_ECC              _SBF(0, 2)

#define CRYPTO_RAM_ST                   (0x0484 - CRYPTO_PKA_BASE_OFFSET)
#define CRYPTO_CLK_RAM_RDY              RT_BIT(0)

#define CRYPTO_OPCODE                   (0x0880 - CRYPTO_PKA_BASE_OFFSET)
#define CRYPTO_OPCODE_TAG_SHIFT         0
#define CRYPTO_OPCODE_R_SHIFT           6
#define CRYPTO_OPCODE_R_DIS_SHIFT       11
#define CRYPTO_OPCODE_B_SHIFT           12
#define CRYPTO_OPCODE_B_IMMED_SHIFT     17
#define CRYPTO_OPCODE_A_SHIFT           18
#define CRYPTO_OPCODE_A_IMMED_SHIFT     23
#define CRYPTO_OPCODE_LEN_SHIFT         24
#define CRYPTO_OPCODE_CODE_SHIFT        27
#define CRYPTO_MEMORY_MAP0              (0x0800 - CRYPTO_PKA_BASE_OFFSET)
#define CRYPTO_MAP_REG_NUM              32
#define CRYPTO_LEN_REG_NUM              8
#define CRYPTO_N_NP_T0_T1_ADDR          (0x0884 - CRYPTO_PKA_BASE_OFFSET)
#define CRYPTO_N_VIRTUAL_ADDR_SHIFT     0
#define CRYPTO_NP_VIRTUAL_ADDR_SHIFT    5
#define CRYPTO_T0_VIRTUAL_ADDR_SHIFT    10
#define CRYPTO_T1_VIRTUAL_ADDR_SHIFT    15

#define CRYPTO_PKA_STATUS               (0x0888 - CRYPTO_PKA_BASE_OFFSET)
#define CRYPTO_PKA_PIPE_IS_RDY          RT_BIT(0)
#define CRYPTO_PKA_BUSY                 RT_BIT(1)
#define CRYPTO_PKA_ALU_OUT_ZERO         RT_BIT(2)
#define CRYPTO_PKA_ALU_MODOVRFLW        RT_BIT(3)
#define CRYPTO_PKA_DIV_BY_ZERO          RT_BIT(4)
#define CRYPTO_PKA_ALU_CARRY            RT_BIT(5)
#define CRYPTO_PKA_ALU_SIGN_OUT         RT_BIT(6)
#define CRYPTO_PKA_MODINV_OF_ZERO       RT_BIT(7)
#define CRYPTO_PKA_CPU_BUSY             RT_BIT(8)
#define CRYPTO_PKA_OPCODE_STATUS_SHIFT  9
#define CRYPTO_PKA_OPCODE_STATUS_MASK   0x00003e00
#define CRYPTO_PKA_TAG_STATUS_SHIFT     14
#define CRYPTO_PKA_TAG_STATUS_MASK      0x0003c000

#define CRYPTO_PKA_SW_RESET             (0x088C - CRYPTO_PKA_BASE_OFFSET)
#define CRYPTO_PKA_L0                   (0x0890 - CRYPTO_PKA_BASE_OFFSET)
#define CRYPTO_PKA_PIPE_RDY             (0x08B0 - CRYPTO_PKA_BASE_OFFSET)
#define CRYPTO_PKA_DONE                 (0x08B4 - CRYPTO_PKA_BASE_OFFSET)
#define CRYPTO_SRAM_BASE                (0x1000 - CRYPTO_PKA_BASE_OFFSET)
#define CRYPTO_SRAM_SIZE                0x1000

#ifndef RK_ECC_BASE_OFFSET
#define RK_ECC_BASE_OFFSET              CRYPTO_PKA_BASE_OFFSET
#endif

struct rt_clk_array;
struct rt_reset_control;

struct rockchip_crypto
{
    struct rt_hwcrypto_device parent;
    struct rt_mutex mutex;
    rt_uint8_t *regs;
    struct rt_clk_array *clk_arr;
    struct rt_reset_control *rstc;
};

enum rk_bignum_endian
{
    RK_BG_BIG_ENDIAN,
    RK_BG_LITTILE_ENDIAN
};

struct rk_bignum
{
    rt_uint32_t n_words;
    rt_uint32_t *data;
};

struct rk_ecp_point
{
    struct rk_bignum *x;
    struct rk_bignum *y;
};

struct rk_bignum *rk_bn_alloc(rt_uint32_t max_size);
void rk_bn_free(struct rk_bignum *bn);
rt_err_t rk_bn_set_data(struct rk_bignum *bn, const rt_uint8_t *data,
        rt_uint32_t size, enum rk_bignum_endian endian);
rt_err_t rk_bn_get_data(const struct rk_bignum *bn, rt_uint8_t *data,
        rt_uint32_t size, enum rk_bignum_endian endian);
rt_uint32_t rk_bn_get_size(const struct rk_bignum *bn);
int rk_bn_highest_bit(const struct rk_bignum *bn);

struct rk_ecp_point *rk_ecc_alloc_point_zero(rt_uint32_t max_size);
struct rk_ecp_point *rk_ecc_alloc_point(const rt_uint8_t *x, rt_uint32_t x_len,
        const rt_uint8_t *y, rt_uint32_t y_len,
        enum rk_bignum_endian endian, rt_uint32_t max_size);
void rk_ecc_free_point(struct rk_ecp_point *point);
rt_bool_t rk_ecp_point_is_zero(struct rk_ecp_point *point);

#ifdef RT_HWCRYPTO_USING_BIGNUM
const struct hwcrypto_bignum_ops *rk_crypto_bignum_ops_get(void);
void rk_crypto_pka_init(struct rockchip_crypto *rc);
void rk_crypto_ecc_init(struct rockchip_crypto *rc);
#else
rt_inline const struct hwcrypto_bignum_ops *rk_crypto_bignum_ops_get(void)
{
    return RT_NULL;
}

rt_inline void rk_crypto_pka_init(struct rockchip_crypto *rc)
{
    RT_UNUSED(rc);
}

rt_inline void rk_crypto_ecc_init(struct rockchip_crypto *rc)
{
    RT_UNUSED(rc);
}
#endif /* RT_HWCRYPTO_USING_BIGNUM */

#define RK_ECP_MAX_BITS                 256
#define RK_ECP_MAX_BYTES                (RK_ECP_MAX_BITS / 8)
#define RK_ECP_MAX_WORDS                (RK_ECP_MAX_BITS / 32)
#define RK_ECP_MAX_WORDS_ALL            (512 / 32)

#define RK_ECC_CTL                      0x03F0
#define RK_ECC_CTL_FUNC_SM2_CURVER      _SBF(8, 0x0)
#define RK_ECC_CTL_FUNC_ECC_CURVER      _SBF(8, 0x1)
#define RK_ECC_CTL_FUNC_SEL_VERIFY      _SBF(4, 0x3)
#define RK_ECC_CTL_REQ_ECC              _SBF(0, 1)

#define RK_ECC_INT_EN                   0x03F4
#define RK_ECC_INT_ST                   0x03F8
#define RK_ECC_ABN_ST                   0x03FC
#define RK_ECC_CURVE_WIDE               0x0400
#define RK_ECC_CURVE_WIDE_192           192
#define RK_ECC_CURVE_WIDE_224           224
#define RK_ECC_CURVE_WIDE_256           256
#define RK_ECC_DATA_ENDIAN              0x0408
#define RK_ECC_DATA_ENDIAN_LITTLE       0x0

#define RK_ECC_RAM_CTL                  0x0480
#define RK_ECC_RAM_CTL_SEL_MASK         _SBF(16, 3)
#define RK_ECC_RAM_CTL_CPU              _SBF(0, 0)
#define RK_ECC_RAM_CTL_ECC              _SBF(0, 2)

#define SM2_RAM_BASE_OFFSET             0x1000

enum rk_ecp_group_id
{
    RK_ECP_DP_NONE = 0,
    RK_ECP_DP_SECP192R1,
    RK_ECP_DP_SECP224R1,
    RK_ECP_DP_SECP256R1,
    RK_ECP_DP_SM2P256V1,
};

struct rk_ecp_group
{
    enum rk_ecp_group_id id;
    const char *curve_name;
    rt_uint32_t wide;
    const rt_uint8_t *p;
    const rt_uint8_t *a;
    const rt_uint8_t *n;
    const rt_uint8_t *gx;
    const rt_uint8_t *gy;
    rt_size_t p_len;
    rt_size_t a_len;
    rt_size_t n_len;
    rt_size_t gx_len;
    rt_size_t gy_len;
    enum rk_bignum_endian endian;
};

struct rk_ecc_verify
{
    rt_uint32_t e[RK_ECP_MAX_WORDS_ALL];
    rt_uint32_t r_[RK_ECP_MAX_WORDS_ALL];
    rt_uint32_t s_[RK_ECP_MAX_WORDS_ALL];
    rt_uint32_t p_x[RK_ECP_MAX_WORDS_ALL];
    rt_uint32_t p_y[RK_ECP_MAX_WORDS_ALL];
    rt_uint32_t A[RK_ECP_MAX_WORDS_ALL];
    rt_uint32_t P[RK_ECP_MAX_WORDS_ALL];
    rt_uint32_t N[RK_ECP_MAX_WORDS_ALL];
    rt_uint32_t G_x[RK_ECP_MAX_WORDS_ALL];
    rt_uint32_t G_y[RK_ECP_MAX_WORDS_ALL];
    rt_uint32_t r[RK_ECP_MAX_WORDS_ALL];
    rt_uint32_t v[RK_ECP_MAX_WORDS_ALL];
};

rt_err_t rk_crypto_ecc_verify(int group_id, rt_uint8_t *hash, rt_uint32_t hash_len,
        struct rk_ecp_point *point_p, struct rk_ecp_point *point_sign);
rt_uint32_t rk_crypto_ecc_get_max_size(void);
rt_uint32_t rk_crypto_ecc_get_curve_nbits(rt_uint32_t group_id);

#endif /* __HW_CRYPTO_ROCKCHIP_V2_H__ */
