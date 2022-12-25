#include "hal_sec_ecdsa.h"
#include "bl808_sec_eng.h"

#define ECP_SECP256R1_REG_TYPE           SEC_ENG_PKA_REG_SIZE_32
#define ECP_SECP256R1_N_REG_INDEX        0
#define ECP_SECP256R1_NPRIME_N_REG_INDEX 1
#define ECP_SECP256R1_INVR_N_REG_INDEX   2
#define ECP_SECP256R1_NPRIME_P_REG_INDEX 3
#define ECP_SECP256R1_INVR_P_REG_INDEX   4
#define ECP_SECP256R1_SIZE               32
/* Used in verify */
#define ECP_SECP256R1_S_REG_INDEX     5
#define ECP_SECP256R1_BAR_S_REG_INDEX 6
#define ECP_SECP256R1_HASH_REG_INDEX  6 //use ECP_SECP256R1_BAR_S_REG_INDEX since it's temp
#define ECP_SECP256R1_U1_REG_INDEX    7
#define ECP_SECP256R1_LT_REG_TYPE     SEC_ENG_PKA_REG_SIZE_64
#define ECP_SECP256R1_LT_REG_INDEX    7
#define ECP_SECP256R1_SLT_REG_TYPE    SEC_ENG_PKA_REG_SIZE_128
#define ECP_SECP256R1_SLT_REG_INDEX   3

//#define ECDSA_DBG                                   1
//#define ECDSA_DBG_DETAIL                            1

#define secp256r1
#define secp256k1
#define SEC_ECC_POINT_MUL_PARAM_CFG(G) sec_ecc_point_mul_cfg( \
    (uint32_t *)G##P,                                         \
    (uint32_t *)G##PrimeN_P,                                  \
    (uint32_t *)G##_1,                                        \
    (uint32_t *)G##_BAR2,                                     \
    (uint32_t *)G##_BAR3,                                     \
    (uint32_t *)G##_BAR4,                                     \
    (uint32_t *)G##_BAR8,                                     \
    (uint32_t *)G##_1P1,                                      \
    (uint32_t *)G##_1M1)

#define SEC_ECC_BASIC_PARAM_CFG(G) sec_ecc_basic_parameter_cfg( \
    (uint32_t *)G##N,                                           \
    (uint32_t *)G##PrimeN_N,                                    \
    (uint32_t *)G##InvR_N)

void bflb_platform_dump(uint8_t *data, uint32_t len);

#if (defined(ECDSA_DBG) || defined(ECDSA_DBG_DETAIL))
uint32_t pka_tmp[32] = { 0 };
#endif
/********************************************** secp256r1 *******************************************/
const uint8_t secp256r1P[32] ALIGN4 = {
    0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};
const uint8_t secp256r1B[32] ALIGN4 = {
    0x5a, 0xc6, 0x35, 0xd8, 0xaa, 0x3a, 0x93, 0xe7, 0xb3, 0xeb, 0xbd, 0x55, 0x76, 0x98, 0x86, 0xbc,
    0x65, 0x1d, 0x06, 0xb0, 0xcc, 0x53, 0xb0, 0xf6, 0x3b, 0xce, 0x3c, 0x3e, 0x27, 0xd2, 0x60, 0x4b
};
const uint8_t secp256r1Gx[32] ALIGN4 = {
    0x6b, 0x17, 0xd1, 0xf2, 0xe1, 0x2c, 0x42, 0x47, 0xf8, 0xbc, 0xe6, 0xe5, 0x63, 0xa4, 0x40, 0xf2,
    0x77, 0x03, 0x7d, 0x81, 0x2d, 0xeb, 0x33, 0xa0, 0xf4, 0xa1, 0x39, 0x45, 0xd8, 0x98, 0xc2, 0x96
};
const uint8_t secp256r1Gy[32] ALIGN4 = {
    0x4f, 0xe3, 0x42, 0xe2, 0xfe, 0x1a, 0x7f, 0x9b, 0x8e, 0xe7, 0xeb, 0x4a, 0x7c, 0x0f, 0x9e, 0x16,
    0x2b, 0xce, 0x33, 0x57, 0x6b, 0x31, 0x5e, 0xce, 0xcb, 0xb6, 0x40, 0x68, 0x37, 0xbf, 0x51, 0xf5
};
const uint8_t secp256r1N[32] ALIGN4 = {
    0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xbc, 0xe6, 0xfa, 0xad, 0xa7, 0x17, 0x9e, 0x84, 0xf3, 0xb9, 0xca, 0xc2, 0xfc, 0x63, 0x25, 0x51
};
const uint8_t secp256r1PrimeN_N[32] ALIGN4 = {
    0x60, 0xd0, 0x66, 0x33, 0xa9, 0xd6, 0x28, 0x1c, 0x50, 0xfe, 0x77, 0xec, 0xc5, 0x88, 0xc6, 0xf6,
    0x48, 0xc9, 0x44, 0x08, 0x7d, 0x74, 0xd2, 0xe4, 0xcc, 0xd1, 0xc8, 0xaa, 0xee, 0x00, 0xbc, 0x4f
};
const uint8_t secp256r1InvR_N[32] ALIGN4 = {
    0x60, 0xd0, 0x66, 0x33, 0x49, 0x05, 0xc1, 0xe9, 0x07, 0xf8, 0xb6, 0x04, 0x1e, 0x60, 0x77, 0x25,
    0xba, 0xde, 0xf3, 0xe2, 0x43, 0x56, 0x6f, 0xaf, 0xce, 0x1b, 0xc8, 0xf7, 0x9c, 0x19, 0x7c, 0x79
};
const uint8_t secp256r1PrimeN_P[32] ALIGN4 = {
    0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
};
const uint8_t secp256r1InvR_P[32] ALIGN4 = {
    0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xfd, 0x00, 0x00, 0x00, 0x02,
    0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00
};
const uint8_t secp256r1_1[32] ALIGN4 = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
};
const uint8_t secp256r1_BAR2[32] ALIGN4 = {
    0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02
};
const uint8_t secp256r1_BAR3[32] ALIGN4 = {
    0x00, 0x00, 0x00, 0x02, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xfd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03
};
const uint8_t secp256r1_BAR4[32] ALIGN4 = {
    0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04
};
const uint8_t secp256r1_BAR8[32] ALIGN4 = {
    0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08
};
const uint8_t secp256r1_1P1[32] ALIGN4 = {
    0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02
};
const uint8_t secp256r1_1M1[32] ALIGN4 = {
    0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const uint8_t secp256r1_Zerox[32] ALIGN4 = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const uint8_t secp256r1_Zeroy[32] ALIGN4 = {
    0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
};
const uint8_t secp256r1_Gx[32] ALIGN4 = {
    0x18, 0x90, 0x5f, 0x76, 0xa5, 0x37, 0x55, 0xc6, 0x79, 0xfb, 0x73, 0x2b, 0x77, 0x62, 0x25, 0x10,
    0x75, 0xba, 0x95, 0xfc, 0x5f, 0xed, 0xb6, 0x01, 0x79, 0xe7, 0x30, 0xd4, 0x18, 0xa9, 0x14, 0x3c
};
const uint8_t secp256r1_Gy[32] ALIGN4 = {
    0x85, 0x71, 0xff, 0x18, 0x25, 0x88, 0x5d, 0x85, 0xd2, 0xe8, 0x86, 0x88, 0xdd, 0x21, 0xf3, 0x25,
    0x8b, 0x4a, 0xb8, 0xe4, 0xba, 0x19, 0xe4, 0x5c, 0xdd, 0xf2, 0x53, 0x57, 0xce, 0x95, 0x56, 0x0a
};

/********************************************** secp256k1 *******************************************/
const uint8_t secp256k1P[32] ALIGN4 = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFC, 0x2F
};
const uint8_t secp256k1B[32] ALIGN4 = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07
};
const uint8_t secp256k1Gx[32] ALIGN4 = {
    0x79, 0xBE, 0x66, 0x7E, 0xF9, 0xDC, 0xBB, 0xAC, 0x55, 0xA0, 0x62, 0x95, 0xCE, 0x87, 0x0B, 0x07,
    0x02, 0x9B, 0xFC, 0xDB, 0x2D, 0xCE, 0x28, 0xD9, 0x59, 0xF2, 0x81, 0x5B, 0x16, 0xF8, 0x17, 0x98
};
const uint8_t secp256k1Gy[32] ALIGN4 = {
    0x4f, 0xe3, 0x42, 0xe2, 0xfe, 0x1a, 0x7f, 0x9b, 0x8e, 0xe7, 0xeb, 0x4a, 0x7c, 0x0f, 0x9e, 0x16,
    0x2b, 0xce, 0x33, 0x57, 0x6b, 0x31, 0x5e, 0xce, 0xcb, 0xb6, 0x40, 0x68, 0x37, 0xbf, 0x51, 0xf5
};
const uint8_t secp256k1N[32] ALIGN4 = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
    0xBA, 0xAE, 0xDC, 0xE6, 0xAF, 0x48, 0xA0, 0x3B, 0xBF, 0xD2, 0x5E, 0x8C, 0xD0, 0x36, 0x41, 0x41
};
const uint8_t secp256k1PrimeN_N[32] ALIGN4 = {
    0xd9, 0xe8, 0x89, 0xd, 0x64, 0x94, 0xef, 0x93, 0x89, 0x7f, 0x30, 0xc1, 0x27, 0xcf, 0xab, 0x5e,
    0x50, 0xa5, 0x1a, 0xc8, 0x34, 0xb9, 0xec, 0x24, 0x4b, 0xd, 0xff, 0x66, 0x55, 0x88, 0xb1, 0x3f
};
const uint8_t secp256k1InvR_N[32] ALIGN4 = {
    0xd9, 0xe8, 0x89, 0xd, 0x64, 0x94, 0xef, 0x93, 0x89, 0x7f, 0x30, 0xc1, 0x27, 0xcf, 0xab, 0x5d,
    0x3b, 0xbb, 0xd4, 0x56, 0x7f, 0xa5, 0xc, 0x3c, 0x80, 0xfd, 0x22, 0x93, 0x80, 0x97, 0xc0, 0x16
};
const uint8_t secp256k1PrimeN_P[32] ALIGN4 = {
    0xc9, 0xbd, 0x19, 0x5, 0x15, 0x53, 0x83, 0x99, 0x9c, 0x46, 0xc2, 0xc2, 0x95, 0xf2, 0xb7, 0x61,
    0xbc, 0xb2, 0x23, 0xfe, 0xdc, 0x24, 0xa0, 0x59, 0xd8, 0x38, 0x9, 0x1d, 0xd2, 0x25, 0x35, 0x31
};
const uint8_t secp256k1InvR_P[32] ALIGN4 = {
    0xc9, 0xbd, 0x19, 0x5, 0x15, 0x53, 0x83, 0x99, 0x9c, 0x46, 0xc2, 0xc2, 0x95, 0xf2, 0xb7, 0x61,
    0xbc, 0xb2, 0x23, 0xfe, 0xdc, 0x24, 0xa0, 0x59, 0xd8, 0x38, 0x9, 0x1d, 0x8, 0x68, 0x19, 0x2a
};
const uint8_t secp256k1_1[32] ALIGN4 = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
};
const uint8_t secp256k1_BAR2[32] ALIGN4 = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x07, 0xa2
};
const uint8_t secp256k1_BAR3[32] ALIGN4 = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x0b, 0x73
};
const uint8_t secp256k1_BAR4[32] ALIGN4 = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x0f, 0x44
};
const uint8_t secp256k1_BAR8[32] ALIGN4 = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x1e, 0x88
};
const uint8_t secp256k1_1P1[32] ALIGN4 = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x03, 0xd2
};
const uint8_t secp256k1_1M1[32] ALIGN4 = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x03, 0xd0
};
const uint8_t secp256k1_Zerox[32] ALIGN4 = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const uint8_t secp256k1_Zeroy[32] ALIGN4 = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x03, 0xd1
};
const uint8_t secp256k1_Gx[32] ALIGN4 = {
    0x99, 0x81, 0xe6, 0x43, 0xe9, 0x08, 0x9f, 0x48, 0x97, 0x9f, 0x48, 0xc0, 0x33, 0xfd, 0x12, 0x9c,
    0x23, 0x1e, 0x29, 0x53, 0x29, 0xbc, 0x66, 0xdb, 0xd7, 0x36, 0x2e, 0x5a, 0x48, 0x7e, 0x20, 0x97
};
const uint8_t secp256k1_Gy[32] ALIGN4 = {
    0xcf, 0x3f, 0x85, 0x1f, 0xd4, 0xa5, 0x82, 0xd6, 0x70, 0xb6, 0xb5, 0x9a, 0xac, 0x19, 0xc1, 0x36,
    0x8d, 0xfc, 0x5d, 0x5d, 0x1f, 0x1d, 0xc6, 0x4d, 0xb1, 0x5e, 0xa6, 0xd2, 0xd3, 0xdb, 0xab, 0xe2
};

static BL_Err_Type sec_ecc_basic_parameter_cfg(uint32_t *n, uint32_t *prime_n, uint32_t *invr_n)
{
    Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_N_REG_INDEX, (uint32_t *)n, ECP_SECP256R1_SIZE / 4, 0);
    Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_NPRIME_N_REG_INDEX, (uint32_t *)prime_n, ECP_SECP256R1_SIZE / 4, 0);
    Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_INVR_N_REG_INDEX, (uint32_t *)invr_n, ECP_SECP256R1_SIZE / 4, 0);
    return SUCCESS;
}
static BL_Err_Type sec_ecc_basic_parameter_init(uint8_t id)
{
    if (id >= ECP_TYPE_MAX) {
        return ERROR;
    }

    if (id == ECP_SECP256R1) {
        SEC_ECC_BASIC_PARAM_CFG(secp256r1);
    } else if (id == ECP_SECP256K1) {
        SEC_ECC_BASIC_PARAM_CFG(secp256k1);
    }

    return SUCCESS;
}

static BL_Err_Type sec_ecc_point_mul_cfg(uint32_t *p, uint32_t *primeN_p, uint32_t *ori_1, uint32_t *bar2,
                                         uint32_t *bar3, uint32_t *bar4, uint32_t *bar8, uint32_t *bar1p1, uint32_t *bar1m1)
{
    Sec_Eng_PKA_Write_Data(SEC_ENG_PKA_REG_SIZE_32, 0, (uint32_t *)p, ECP_SECP256R1_SIZE / 4, 0);
    Sec_Eng_PKA_Write_Data(SEC_ENG_PKA_REG_SIZE_32, 1, (uint32_t *)primeN_p, ECP_SECP256R1_SIZE / 4, 0);
    Sec_Eng_PKA_Write_Data(SEC_ENG_PKA_REG_SIZE_32, 8, (uint32_t *)ori_1, ECP_SECP256R1_SIZE / 4, 0);
    Sec_Eng_PKA_Write_Data(SEC_ENG_PKA_REG_SIZE_32, 9, (uint32_t *)bar2, ECP_SECP256R1_SIZE / 4, 0);
    Sec_Eng_PKA_Write_Data(SEC_ENG_PKA_REG_SIZE_32, 10, (uint32_t *)bar3, ECP_SECP256R1_SIZE / 4, 0);
    Sec_Eng_PKA_Write_Data(SEC_ENG_PKA_REG_SIZE_32, 11, (uint32_t *)bar4, ECP_SECP256R1_SIZE / 4, 0);
    Sec_Eng_PKA_Write_Data(SEC_ENG_PKA_REG_SIZE_32, 12, (uint32_t *)bar8, ECP_SECP256R1_SIZE / 4, 0);
    Sec_Eng_PKA_Write_Data(SEC_ENG_PKA_REG_SIZE_32, 19, (uint32_t *)bar1p1, ECP_SECP256R1_SIZE / 4, 0);
    Sec_Eng_PKA_Write_Data(SEC_ENG_PKA_REG_SIZE_32, 20, (uint32_t *)bar1m1, ECP_SECP256R1_SIZE / 4, 0);

    return SUCCESS;
}

static int sec_ecc_point_mul_init(uint8_t id)
{
    if (id >= ECP_TYPE_MAX) {
        return ERROR;
    }

    if (id == ECP_SECP256R1) {
        SEC_ECC_POINT_MUL_PARAM_CFG(secp256r1);
    } else if (id == ECP_SECP256K1) {
        SEC_ECC_POINT_MUL_PARAM_CFG(secp256k1);
    }

    return SUCCESS;
}

static void sec_ecdsa_point_add_inf_check(uint8_t *pka_p1_eq_inf, uint8_t *pka_p2_eq_inf)
{
    uint8_t res[4];

    /* index 2:BAR_Zero_x
     * index 3:BAR_Zero_y
     * index 4:BAR_Zero_z
     * index 5:BAR_G_x
     * index 6:BAR_G_y
     * index 7:BAR_G_z
     * index 8:1
     * index 9:2
     * index 10:3
     * index 11:4
     * index 12:8
     * index 19:1P1
     * index 20:1m1*/

    //cout = 1 if X1 = 0
    Sec_Eng_PKA_LCMP(res, 3, 2, 3, 8); //s0 < s1 => cout = 1
    //cout = 1 if Y1 < Bar_1p1
    Sec_Eng_PKA_LCMP(res + 1, 3, 3, 3, 19);
    //cout=1 if Y1 > Bar_1m1
    Sec_Eng_PKA_LCMP(res + 2, 3, 20, 3, 3);
    //cout =1 if Z1 = 0
    Sec_Eng_PKA_LCMP(res + 3, 3, 4, 3, 8);
    *pka_p1_eq_inf = res[0] & res[1] & res[2] & res[3];

    //cout = 1 if X2 = 0
    Sec_Eng_PKA_LCMP(res, 3, 5, 3, 8);
    // cout = 1 if Y2 < Bar_1p1
    Sec_Eng_PKA_LCMP(res + 1, 3, 6, 3, 19);
    //cout = 1 if Y2 > Bar_1m1
    Sec_Eng_PKA_LCMP(res + 2, 3, 20, 3, 6);
    //cout = 1 if Z2 = 0
    Sec_Eng_PKA_LCMP(res + 3, 3, 7, 3, 8);
    *pka_p2_eq_inf = res[0] & res[1] & res[2] & res[3];
}

static void sec_ecdsa_copy_x2_to_x1(uint8_t id)
{
    //X2->X1
    Sec_Eng_PKA_Move_Data(3, 2, 3, 5, 0);
    //Y2->Y1
    Sec_Eng_PKA_Move_Data(3, 3, 3, 6, 0);
    //Z2->Z1
    Sec_Eng_PKA_Move_Data(3, 4, 3, 7, 1); //Caution!!! wait movdat ready to execute next command
}

static void sec_ecdsa_point_add(uint8_t id)
{
    /* index 2:BAR_Zero_x
     * index 3:BAR_Zero_y
     * index 4:BAR_Zero_z
     * index 5:BAR_G_x
     * index 6:BAR_G_y
     * index 7:BAR_G_z
     * index 8:1
     * index 9:2
     * index 10:3
     * index 11:4
     * index 12:8
     * index 19:1P1
     * index 20:1m1*/

    //U1 = Y2*Z1
    //PKA_MMUL(0,3,13,3, 6,3, 4,3,0);//d_reg_type,d_reg_idx,s0_reg_type,s0_reg_idx,s1_reg_type,s1_reg_idx,s2_reg_type,s2_reg_idx
    Sec_Eng_PKA_MMUL(3, 13, 3, 6, 3, 4, 3, 0, 0);

    //U2 = Y1*Z2
    //PKA_MMUL(0,3,14,3, 3,3, 7,3,0);
    Sec_Eng_PKA_MMUL(3, 14, 3, 3, 3, 7, 3, 0, 0);

    //V1 = X2*Z1
    //PKA_MMUL(0,3,15,3, 5,3, 4,3,0);
    Sec_Eng_PKA_MMUL(3, 15, 3, 5, 3, 4, 3, 0, 0);

    //V2 = X1*Z2
    //PKA_MMUL(0,3,16,3, 2,3, 7,3,0);
    Sec_Eng_PKA_MMUL(3, 16, 3, 2, 3, 7, 3, 0, 0);

    //U = U1-U2
    //PKA_MSUB(0,3,13,3,13,3,14,3,0);
    Sec_Eng_PKA_MSUB(3, 13, 3, 13, 3, 14, 3, 0, 0);

    //V = V1-V2
    //PKA_MSUB(0,3,15,3,15,3,16,3,0);
    Sec_Eng_PKA_MSUB(3, 15, 3, 15, 3, 16, 3, 0, 0);

    //W = Z1*Z2
    //PKA_MMUL(0,3, 2,3, 4,3, 7,3,0);
    Sec_Eng_PKA_MMUL(3, 2, 3, 4, 3, 7, 3, 0, 0);

    //V^2
    //PKA_MMUL(0,3, 3,3,15,3,15,3,0);
    Sec_Eng_PKA_MMUL(3, 3, 3, 15, 3, 15, 3, 0, 0);

    //V^3
    //PKA_MMUL(0,3, 4,3, 3,3,15,3,0);
    Sec_Eng_PKA_MMUL(3, 4, 3, 3, 3, 15, 3, 0, 0);

    //U^2
    //PKA_MMUL(0,3,17,3,13,3,13,3,0);
    Sec_Eng_PKA_MMUL(3, 17, 3, 13, 3, 13, 3, 0, 0);

    //U^2*W
    //PKA_MMUL(0,3,17,3,17,3, 2,3,0);
    Sec_Eng_PKA_MMUL(3, 17, 3, 17, 3, 2, 3, 0, 0);

    //U^2*W-V^3
    //PKA_MSUB(0,3,17,3,17,3, 4,3,0);
    Sec_Eng_PKA_MSUB(3, 17, 3, 17, 3, 4, 3, 0, 0);

    //2*V^2
    //PKA_MMUL(0,3,18,3, 9,3, 3,3,0);
    Sec_Eng_PKA_MMUL(3, 18, 3, 9, 3, 3, 3, 0, 0);

    //2*V^2*V2
    //PKA_MMUL(0,3,18,3,18,3,16,3,0);
    Sec_Eng_PKA_MMUL(3, 18, 3, 18, 3, 16, 3, 0, 0);

    //A = U^2*W-V^3-2*V^2*V2
    //PKA_MSUB(0,3,18,3,17,3,18,3,0);
    Sec_Eng_PKA_MSUB(3, 18, 3, 17, 3, 18, 3, 0, 0);

    //V^2*V2
    //PKA_MMUL(0,3, 3,3, 3,3,16,3,0);
    Sec_Eng_PKA_MMUL(3, 3, 3, 3, 3, 16, 3, 0, 0);

    //V^3*U2
    //PKA_MMUL(0,3,14,3, 4,3,14,3,0);
    Sec_Eng_PKA_MMUL(3, 14, 3, 4, 3, 14, 3, 0, 0);

    //Z3 = V^3*W
    //PKA_MMUL(0,3, 4,3, 4,3, 2,3,0);
    Sec_Eng_PKA_MMUL(3, 4, 3, 4, 3, 2, 3, 0, 0);

    //X3 = V*A
    //PKA_MMUL(0,3, 2,3,15,3,18,3,0);
    Sec_Eng_PKA_MMUL(3, 2, 3, 15, 3, 18, 3, 0, 0);

    //V^2*V2-A
    //PKA_MSUB(0,3, 3,3, 3,3,18,3,0);
    Sec_Eng_PKA_MSUB(3, 3, 3, 3, 3, 18, 3, 0, 0);

    //U*(V^2*V2-A)
    //PKA_MMUL(0,3, 3,3,13,3, 3,3,0);
    Sec_Eng_PKA_MMUL(3, 3, 3, 13, 3, 3, 3, 0, 0);

    //Y3 = U*(V^2*V2-A)-V^3*U2
    //PKA_MSUB(1,3, 3,3, 3,3,14,3,0);
    Sec_Eng_PKA_MSUB(3, 3, 3, 3, 3, 14, 3, 0, 1);
}
/**
 * @brief calculate secp256r1's W
 *
 * @note index 13:W = 3X^2-3Z^2
 */
static void sec_ecdsa_cal_secp256r1_w(void)
{
    //X1^2
    //PKA_MMUL(0,3,13,3, 5,3, 5,3,0);//d_reg_type,d_reg_idx,s0_reg_type,s0_reg_idx,s1_reg_type,s1_reg_idx,s2_reg_type,s2_reg_idx
    Sec_Eng_PKA_MMUL(3, 13, 3, 5, 3, 5, 3, 0, 0);

    //Z1^2
    //PKA_MMUL(0,3,14,3, 7,3, 7,3,0);
    Sec_Eng_PKA_MMUL(3, 14, 3, 7, 3, 7, 3, 0, 0);

    //X1^2-Z1^2
    //PKA_MSUB(0,3,13,3,13,3,14,3,0);
    Sec_Eng_PKA_MSUB(3, 13, 3, 13, 3, 14, 3, 0, 0);

    //W = 3*(X1^2-Z1^2)
    //PKA_MMUL(0,3,13,3,10,3,13,3,0);
    Sec_Eng_PKA_MMUL(3, 13, 3, 10, 3, 13, 3, 0, 0);
}

/**
 * @brief calculate secp256k1's W
 *
 * @note index 13:W = 3X^2
 */
static void sec_ecdsa_cal_secp256k1_w(void)
{
    //X1^2
    Sec_Eng_PKA_MMUL(3, 13, 3, 5, 3, 5, 3, 0, 0);

    //W = 3* (X1^2)
    Sec_Eng_PKA_MMUL(3, 13, 3, 10, 3, 13, 3, 0, 0);
}

static BL_Err_Type sec_ecdsa_point_double(sec_ecp_type id)
{
    /* index 2:BAR_Zero_x
     * index 3:BAR_Zero_y
     * index 4:BAR_Zero_z
     * index 5:BAR_G_x
     * index 6:BAR_G_y
     * index 7:BAR_G_z
     * index 8:1
     * index 9:2
     * index 10:3
     * index 11:4
     * index 12:8
     * index 19:1P1
     * index 20:1m1*/

    if (id >= ECP_TYPE_MAX) {
        return ERROR;
    }

    if (id == ECP_SECP256R1) {
        sec_ecdsa_cal_secp256r1_w();
    } else if (id == ECP_SECP256K1) {
        sec_ecdsa_cal_secp256k1_w();
    }

    //S = Y1*Z1
    //PKA_MMUL(0,3,14,3, 6,3, 7,3,0);
    Sec_Eng_PKA_MMUL(3, 14, 3, 6, 3, 7, 3, 0, 0);

    //X1*Y1
    //PKA_MMUL(0,3,15,3, 5,3, 6,3,0);
    Sec_Eng_PKA_MMUL(3, 15, 3, 5, 3, 6, 3, 0, 0);

    //W^2
    //PKA_MMUL(0,3, 7,3,13,3,13,3,0);
    Sec_Eng_PKA_MMUL(3, 7, 3, 13, 3, 13, 3, 0, 0);

    //B = X1*Y1*S
    //PKA_MMUL(0,3,15,3,15,3,14,3,0);
    Sec_Eng_PKA_MMUL(3, 15, 3, 15, 3, 14, 3, 0, 0);

    //8*B
    //PKA_MMUL(0,3, 5,3,12,3,15,3,0);
    Sec_Eng_PKA_MMUL(3, 5, 3, 12, 3, 15, 3, 0, 0);

    //H = W^2-8*B
    //PKA_MSUB(0,3, 7,3, 7,3, 5,3,0);
    Sec_Eng_PKA_MSUB(3, 7, 3, 7, 3, 5, 3, 0, 0);

    //2*H
    //PKA_MMUL(0,3, 5,3, 9,3, 7,3,0);
    Sec_Eng_PKA_MMUL(3, 5, 3, 9, 3, 7, 3, 0, 0);

    //X2 = 2*H*S
    //PKA_MMUL(0,3, 5,3, 5,3,14,3,0);
    Sec_Eng_PKA_MMUL(3, 5, 3, 5, 3, 14, 3, 0, 0);

    //4*B
    //PKA_MMUL(0,3,15,3,11,3,15,3,0);
    Sec_Eng_PKA_MMUL(3, 15, 3, 11, 3, 15, 3, 0, 0);

    //S^2
    //PKA_MMUL(0,3,16,3,14,3,14,3,0);
    Sec_Eng_PKA_MMUL(3, 16, 3, 14, 3, 14, 3, 0, 0);

    //4*B-H
    //PKA_MSUB(0,3,15,3,15,3, 7,3,0);
    Sec_Eng_PKA_MSUB(3, 15, 3, 15, 3, 7, 3, 0, 0);

    //Y1^2
    //PKA_MMUL(0,3, 6,3, 6,3, 6,3,0);
    Sec_Eng_PKA_MMUL(3, 6, 3, 6, 3, 6, 3, 0, 0);

    //W*(4*B-H)
    //PKA_MMUL(0,3,15,3,15,3,13,3,0);
    Sec_Eng_PKA_MMUL(3, 15, 3, 15, 3, 13, 3, 0, 0);

    //8*Y1^2
    //PKA_MMUL(0,3, 6,3,12,3, 6,3,0);
    Sec_Eng_PKA_MMUL(3, 6, 3, 12, 3, 6, 3, 0, 0);

    //8*Y1^2*S^2
    //PKA_MMUL(0,3, 6,3, 6,3,16,3,0);
    Sec_Eng_PKA_MMUL(3, 6, 3, 6, 3, 16, 3, 0, 0);

    //Y2 = W*(4*B-H)-8*Y1^2*S^2
    //PKA_MSUB(0,3, 6,3,15,3, 6,3,0);
    Sec_Eng_PKA_MSUB(3, 6, 3, 15, 3, 6, 3, 0, 0);

    //S^3
    //PKA_MMUL(0,3, 7,3,14,3,16,3,0);
    Sec_Eng_PKA_MMUL(3, 7, 3, 14, 3, 16, 3, 0, 0);

    //Z2 = 8*S^3
    //PKA_MMUL(1,3, 7,3,12,3, 7,3,0);
    Sec_Eng_PKA_MMUL(3, 7, 3, 12, 3, 7, 3, 0, 1);

    return SUCCESS;
}
#ifdef ECDSA_DBG_DETAIL
static void sec_ecdsa_dump_temp_result()
{
    Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, 2, (uint32_t *)pka_tmp, ECP_SECP256R1_SIZE / 4);
    MSG("2=\r\n");
    bflb_platform_dump(pka_tmp, ECP_SECP256R1_SIZE);
    Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, 3, (uint32_t *)pka_tmp, ECP_SECP256R1_SIZE / 4);
    MSG("3=\r\n");
    bflb_platform_dump(pka_tmp, ECP_SECP256R1_SIZE);
    Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, 4, (uint32_t *)pka_tmp, ECP_SECP256R1_SIZE / 4);
    MSG("4=\r\n");
    bflb_platform_dump(pka_tmp, ECP_SECP256R1_SIZE);

    Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, 5, (uint32_t *)pka_tmp, ECP_SECP256R1_SIZE / 4);
    MSG("5=\r\n");
    bflb_platform_dump(pka_tmp, ECP_SECP256R1_SIZE);
    Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, 6, (uint32_t *)pka_tmp, ECP_SECP256R1_SIZE / 4);
    MSG("6=\r\n");
    bflb_platform_dump(pka_tmp, ECP_SECP256R1_SIZE);
    Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, 7, (uint32_t *)pka_tmp, ECP_SECP256R1_SIZE / 4);
    MSG("7=\r\n");
    bflb_platform_dump(pka_tmp, ECP_SECP256R1_SIZE);
}
#endif
static int sec_ecdsa_verify_point_mul(uint8_t id, const uint32_t *m)
{
    uint32_t i, j, k;
    uint32_t tmp;
    uint32_t isOne = 0;
    uint8_t *p = (uint8_t *)m;
    uint8_t pka_p1_eq_inf, pka_p2_eq_inf;

    /* Remove zeros bytes*/
    k = 0;

    while (p[k] == 0 && k < 31) {
        k++;
    }

    i = 31;

    for (; i >= k; i--) {
        tmp = p[i];
        j = 0;

        for (j = 0; j < 8; j++) {
            isOne = tmp & (1 << j);

            if (isOne) {
                sec_ecdsa_point_add_inf_check(&pka_p1_eq_inf, &pka_p2_eq_inf);

                if (pka_p1_eq_inf == 1 && pka_p2_eq_inf == 0) {
                    //sum = X2
                    sec_ecdsa_copy_x2_to_x1(id);
#ifdef ECDSA_DBG_DETAIL
                    MSG("sum = X2\r\n");
                    sec_ecdsa_dump_temp_result();
#endif
                } else if (pka_p1_eq_inf == 0 && pka_p2_eq_inf == 1) {
                    //sum = X1
                    //MSG("sum = X1\r\n");
                } else if (pka_p1_eq_inf == 0 && pka_p2_eq_inf == 0) {
                    //sum = X1 + X2
                    sec_ecdsa_point_add(id);
#ifdef ECDSA_DBG_DETAIL
                    MSG("sum = X1+X2\r\n");
                    sec_ecdsa_dump_temp_result();
#endif
                } else {
                    //MSG("Error! infinite point + infinite point\r\n");
                    return -1;
                }
            }

            sec_ecdsa_point_double(id);
#ifdef ECDSA_DBG_DETAIL
            sec_ecdsa_dump_temp_result();
#endif
        }

        if (i == 0) {
            break;
        }
    }

    return 0;
}

/*cal d*G if pkX(pky)==NULL
 * cal d(bG) if pkX(pky)!=NULL */
static int32_t sec_ecdh_get_scalar_point(uint8_t id, const uint32_t *pkX, const uint32_t *pkY, const uint32_t *private_key, const uint32_t *pRx, const uint32_t *pRy)
{
#ifdef ECDSA_DBG
    uint32_t pk_z[8];
#endif

    if (id >= ECP_TYPE_MAX) {
        return ERROR;
    }

    /* Pointer check */
    if (private_key == NULL) {
        return -1;
    }

    Sec_Eng_PKA_Reset();
    Sec_Eng_PKA_BigEndian_Enable();

    sec_ecc_basic_parameter_init(id);

    //Clear D[7]
    //PKA_CREG(1,4, 7,0);
    Sec_Eng_PKA_CREG(ECP_SECP256R1_LT_REG_TYPE, 7, ECP_SECP256R1_SIZE / 4, 1);

    sec_ecc_point_mul_init(id);

    if (id == ECP_SECP256R1) {
        //X1
        //PKA_CTREG(3, 2,8,bar_Zero_x);
        Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 2, (uint32_t *)secp256r1_Zerox, ECP_SECP256R1_SIZE / 4, 0);
        //Y1
        //PKA_CTREG(3, 3,8,bar_Zero_y);
        Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 3, (uint32_t *)secp256r1_Zeroy, ECP_SECP256R1_SIZE / 4, 0);
    } else if (id == ECP_SECP256K1) {
        //X1
        Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 2, (uint32_t *)secp256k1_Zerox, ECP_SECP256R1_SIZE / 4, 0);
        //Y1
        Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 3, (uint32_t *)secp256k1_Zeroy, ECP_SECP256R1_SIZE / 4, 0);
    }
    //Z1
    //PKA_CTREG(3, 4,8,bar_Zero_z);
    //PKA_MOVDAT(1,3, 4,3, 2);
    Sec_Eng_PKA_Move_Data(3, 4, 3, 2, 1);

    if (pkX == NULL) {
        if (id == ECP_SECP256R1) {
            //X2
            //PKA_CTREG(3, 5,8,bar_G_x);
            Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 5, (uint32_t *)secp256r1_Gx, ECP_SECP256R1_SIZE / 4, 0);
            //Y2
            //PKA_CTREG(3, 6,8,bar_G_y);
            Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 6, (uint32_t *)secp256r1_Gy, ECP_SECP256R1_SIZE / 4, 0);
        } else if (id == ECP_SECP256K1) {
            //X2
            Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 5, (uint32_t *)secp256k1_Gx, ECP_SECP256R1_SIZE / 4, 0);
            //Y2
            Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 6, (uint32_t *)secp256k1_Gy, ECP_SECP256R1_SIZE / 4, 0);
        }
    } else {
        /* chaneg peer's public key to mont domain*/
        //PUB_x
        //PKA_CTREG(3, 5,8,PUB_x);
        Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 5, (uint32_t *)pkX, ECP_SECP256R1_SIZE / 4, 0);
        //bar_pub_x
        //PKA_GF2MONT(3, 5,3, 5);
        /* Change s to Mont domain,remember to clear temp register and index 0 is P256*/
        /* Clear register for ECP_SECP256R1_LT_REG_INDEX*/
        Sec_Eng_PKA_CREG(ECP_SECP256R1_REG_TYPE, 2 * ECP_SECP256R1_LT_REG_INDEX - 1, ECP_SECP256R1_SIZE / 4, 1);
        Sec_Eng_PKA_CREG(ECP_SECP256R1_REG_TYPE, 2 * ECP_SECP256R1_LT_REG_INDEX, ECP_SECP256R1_SIZE / 4, 1);
        Sec_Eng_PKA_GF2Mont(ECP_SECP256R1_REG_TYPE, 5, ECP_SECP256R1_REG_TYPE, 5, 256,
                            ECP_SECP256R1_LT_REG_TYPE, ECP_SECP256R1_LT_REG_INDEX, ECP_SECP256R1_REG_TYPE, 0);
#ifdef ECDSA_DBG
        Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, 5, (uint32_t *)pka_tmp, ECP_SECP256R1_SIZE / 4);
        MSG("PK.x in Mont:\r\n");
        bflb_platform_dump(pka_tmp, ECP_SECP256R1_SIZE);
#endif

        //PUB_y
        //PKA_CTREG(3, 6,8,PUB_y);
        Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 6, (uint32_t *)pkY, ECP_SECP256R1_SIZE / 4, 0);
        //bar_pub_y
        //PKA_GF2MONT(3, 6,3, 6);
        Sec_Eng_PKA_CREG(ECP_SECP256R1_REG_TYPE, 2 * ECP_SECP256R1_LT_REG_INDEX - 1, ECP_SECP256R1_SIZE / 4, 1);
        Sec_Eng_PKA_CREG(ECP_SECP256R1_REG_TYPE, 2 * ECP_SECP256R1_LT_REG_INDEX, ECP_SECP256R1_SIZE / 4, 1);
        Sec_Eng_PKA_GF2Mont(ECP_SECP256R1_REG_TYPE, 6, ECP_SECP256R1_REG_TYPE, 6, 256,
                            ECP_SECP256R1_LT_REG_TYPE, ECP_SECP256R1_LT_REG_INDEX, ECP_SECP256R1_REG_TYPE, 0);
#ifdef ECDSA_DBG
        Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, 6, (uint32_t *)pka_tmp, ECP_SECP256R1_SIZE / 4);
        MSG("PK.y in Mont:\r\n");
        bflb_platform_dump(pka_tmp, ECP_SECP256R1_SIZE);
#endif
    }

    //Z2
    //PKA_CTREG(3, 7,8,bar_G_z);
    //PKA_MOVDAT(1,3, 7,3, 3);
    Sec_Eng_PKA_Move_Data(3, 7, 3, 3, 1);
    /* Clear temp register since it's used in point-mul*/
    Sec_Eng_PKA_CREG(ECP_SECP256R1_LT_REG_TYPE, 7, ECP_SECP256R1_SIZE / 4, 1);

    sec_ecdsa_verify_point_mul(id, private_key);
    //get bar_u1_x
    Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, 2, (uint32_t *)pRx, ECP_SECP256R1_SIZE / 4);
#ifdef ECDSA_DBG
    MSG("bar_u1_x\r\n");
    bflb_platform_dump(pRx, ECP_SECP256R1_SIZE);
#endif
    Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, 3, (uint32_t *)pRy, ECP_SECP256R1_SIZE / 4);
#ifdef ECDSA_DBG
    MSG("bar_u1_y\r\n");
    bflb_platform_dump(pRy, ECP_SECP256R1_SIZE);
#endif
#ifdef ECDSA_DBG
    Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, 4, (uint32_t *)pk_z, ECP_SECP256R1_SIZE / 4);
    MSG("bar_u1_z\r\n");
    bflb_platform_dump(pk_z, ECP_SECP256R1_SIZE);
#endif

    //get R.x
    //R.z ^ -1
    Sec_Eng_PKA_MINV(ECP_SECP256R1_REG_TYPE, 5, ECP_SECP256R1_REG_TYPE, 4, ECP_SECP256R1_REG_TYPE, 0, 1);
    if (id == ECP_SECP256R1) {
        //inv_r
        //PKA_CTREG(3, 6,8,inv_r);
        Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 6, (uint32_t *)secp256r1InvR_P, ECP_SECP256R1_SIZE / 4, 0);
    } else if (id == ECP_SECP256K1) {
        Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 6, (uint32_t *)secp256k1InvR_P, ECP_SECP256R1_SIZE / 4, 0);
    }
    //R.z ^ -1
    Sec_Eng_PKA_CREG(ECP_SECP256R1_REG_TYPE, 2 * ECP_SECP256R1_LT_REG_INDEX - 1, ECP_SECP256R1_SIZE / 4, 1);
    Sec_Eng_PKA_CREG(ECP_SECP256R1_REG_TYPE, 2 * ECP_SECP256R1_LT_REG_INDEX, ECP_SECP256R1_SIZE / 4, 1);
    //PKA_MONT2GF(3, 5,3, 5,3, 6);
    Sec_Eng_PKA_Mont2GF(ECP_SECP256R1_REG_TYPE, 5, ECP_SECP256R1_REG_TYPE, 5, ECP_SECP256R1_REG_TYPE, 6,
                        ECP_SECP256R1_LT_REG_TYPE, ECP_SECP256R1_LT_REG_INDEX, ECP_SECP256R1_REG_TYPE, 0);

    //R.x (Montgomery to GF)
    //PKA_MONT2GF(3, 6,3, 2,3, 6);
    Sec_Eng_PKA_Mont2GF(ECP_SECP256R1_REG_TYPE, 6, ECP_SECP256R1_REG_TYPE, 2, ECP_SECP256R1_REG_TYPE, 6,
                        ECP_SECP256R1_LT_REG_TYPE, ECP_SECP256R1_LT_REG_INDEX, ECP_SECP256R1_REG_TYPE, 0);

    //R.x (GF to Affine domain)
    //PKA_MONT2GF(3, 2,3, 5,3, 6);
    Sec_Eng_PKA_Mont2GF(ECP_SECP256R1_REG_TYPE, 2, ECP_SECP256R1_REG_TYPE, 5, ECP_SECP256R1_REG_TYPE, 6,
                        ECP_SECP256R1_LT_REG_TYPE, ECP_SECP256R1_LT_REG_INDEX, ECP_SECP256R1_REG_TYPE, 0);
    Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, 2, (uint32_t *)pRx, ECP_SECP256R1_SIZE / 4);
#ifdef ECDSA_DBG
    MSG("R.x=\r\n");
    bflb_platform_dump(pRx, ECP_SECP256R1_SIZE);
#endif
    if (id == ECP_SECP256R1) {
        Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_N_REG_INDEX, (uint32_t *)secp256r1N, ECP_SECP256R1_SIZE / 4, 0);
    } else if (id == ECP_SECP256K1) {
        Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_N_REG_INDEX, (uint32_t *)secp256k1N, ECP_SECP256R1_SIZE / 4, 0);
    }

    Sec_Eng_PKA_MREM(ECP_SECP256R1_REG_TYPE, 2, ECP_SECP256R1_REG_TYPE, 2,
                     ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_N_REG_INDEX, 1);
    Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, 2, (uint32_t *)pRx, ECP_SECP256R1_SIZE / 4);
#ifdef ECDSA_DBG
    MSG("R.x%n=\r\n");
    bflb_platform_dump(pRx, ECP_SECP256R1_SIZE);
#endif
    if (id == ECP_SECP256R1) {
        /*after %n,re write p*/
        Sec_Eng_PKA_Write_Data(SEC_ENG_PKA_REG_SIZE_32, 0, (uint32_t *)secp256r1P, ECP_SECP256R1_SIZE / 4, 0);
    } else if (id == ECP_SECP256K1) {
        Sec_Eng_PKA_Write_Data(SEC_ENG_PKA_REG_SIZE_32, 0, (uint32_t *)secp256k1P, ECP_SECP256R1_SIZE / 4, 0);
    }

    //get R.y
    //R.z ^ -1
    Sec_Eng_PKA_MINV(ECP_SECP256R1_REG_TYPE, 5, ECP_SECP256R1_REG_TYPE, 4, ECP_SECP256R1_REG_TYPE, 0, 1);
    //inv_r
    //PKA_CTREG(3, 6,8,inv_r);
    if (id == ECP_SECP256R1) {
        Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 6, (uint32_t *)secp256r1InvR_P, ECP_SECP256R1_SIZE / 4, 0);
    } else if (id == ECP_SECP256K1) {
        Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 6, (uint32_t *)secp256k1InvR_P, ECP_SECP256R1_SIZE / 4, 0);
    }
    //R.z ^ -1
    Sec_Eng_PKA_CREG(ECP_SECP256R1_REG_TYPE, 2 * ECP_SECP256R1_LT_REG_INDEX - 1, ECP_SECP256R1_SIZE / 4, 1);
    Sec_Eng_PKA_CREG(ECP_SECP256R1_REG_TYPE, 2 * ECP_SECP256R1_LT_REG_INDEX, ECP_SECP256R1_SIZE / 4, 1);
    //PKA_MONT2GF(3, 5,3, 5,3, 6);
    Sec_Eng_PKA_Mont2GF(ECP_SECP256R1_REG_TYPE, 5, ECP_SECP256R1_REG_TYPE, 5, ECP_SECP256R1_REG_TYPE, 6,
                        ECP_SECP256R1_LT_REG_TYPE, ECP_SECP256R1_LT_REG_INDEX, ECP_SECP256R1_REG_TYPE, 0);
    //R.x (Montgomery to GF)
    //PKA_MONT2GF(3, 6,3, 2,3, 6);
    Sec_Eng_PKA_Mont2GF(ECP_SECP256R1_REG_TYPE, 6, ECP_SECP256R1_REG_TYPE, 3, ECP_SECP256R1_REG_TYPE, 6,
                        ECP_SECP256R1_LT_REG_TYPE, ECP_SECP256R1_LT_REG_INDEX, ECP_SECP256R1_REG_TYPE, 0);

    //R.x (GF to Affine domain)
    //PKA_MONT2GF(3, 2,3, 5,3, 6);
    Sec_Eng_PKA_Mont2GF(ECP_SECP256R1_REG_TYPE, 3, ECP_SECP256R1_REG_TYPE, 5, ECP_SECP256R1_REG_TYPE, 6,
                        ECP_SECP256R1_LT_REG_TYPE, ECP_SECP256R1_LT_REG_INDEX, ECP_SECP256R1_REG_TYPE, 0);
    Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, 3, (uint32_t *)pRy, ECP_SECP256R1_SIZE / 4);
#ifdef ECDSA_DBG
    MSG("R.y=\r\n");
    bflb_platform_dump(pRy, ECP_SECP256R1_SIZE);
#endif
    if (id == ECP_SECP256R1) {
        Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_N_REG_INDEX, (uint32_t *)secp256r1N, ECP_SECP256R1_SIZE / 4, 0);
    } else if (id == ECP_SECP256K1) {
        Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_N_REG_INDEX, (uint32_t *)secp256k1N, ECP_SECP256R1_SIZE / 4, 0);
    }
    Sec_Eng_PKA_MREM(ECP_SECP256R1_REG_TYPE, 3, ECP_SECP256R1_REG_TYPE, 3,
                     ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_N_REG_INDEX, 1);
    Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, 3, (uint32_t *)pRy, ECP_SECP256R1_SIZE / 4);
#ifdef ECDSA_DBG
    MSG("R.y%n=\r\n");
    bflb_platform_dump(pRy, ECP_SECP256R1_SIZE);
#endif
    return 0;
}

static int32_t sec_ecc_is_zero(uint8_t *a, uint32_t len)
{
    uint32_t i = 0;

    for (i = 0; i < len; i++) {
        if (a[i] != 0) {
            return 0;
        }
    }

    return 1;
}

static int32_t sec_ecc_cmp(uint8_t *a, uint8_t *b, uint32_t len)
{
    uint32_t i = 0, j = 0;

    for (i = 0; i < len; i++) {
        if (a[i] != 0) {
            break;
        }
    }

    for (j = 0; j < len; j++) {
        if (b[j] != 0) {
            break;
        }
    }

    if (i == len && j == len) {
        return (0);
    }

    if (i > j) {
        return (-1);
    }

    if (j > i) {
        return (1);
    }

    for (; i < len; i++) {
        if (a[i] > b[i]) {
            return (1);
        }

        if (a[i] < b[i]) {
            return (-1);
        }
    }

    return 0;
}

int sec_ecdsa_init(sec_ecdsa_handle_t *handle, sec_ecp_type id)
{
    Sec_Eng_PKA_Reset();
    Sec_Eng_PKA_BigEndian_Enable();
    Sec_Eng_Trng_Enable();

    handle->ecpId = id;

    return 0;
}

int sec_ecdsa_deinit(sec_ecdsa_handle_t *handle)
{
    Sec_Eng_PKA_Reset();

    return 0;
}

__WEAK void sec_ecdsa_verify_suss_callback(uint32_t    state, uint8_t is_en)
{
    
}

int sec_ecdsa_verify(sec_ecdsa_handle_t *handle, const uint32_t *hash, uint32_t hashLenInWord, const uint32_t *r, const uint32_t *s)
{
    uint32_t bar_u1_x[8];
    uint32_t bar_u1_y[8];
    uint32_t bar_u1_z[8];
    uint32_t bar_u2_x[8];
    uint32_t bar_u2_y[8];
    uint32_t bar_u2_z[8];
    uint32_t pka_u1[8] = { 0 };
    uint32_t pka_u2[8] = { 0 };
    uint32_t i = 0;

    /* Pointer check */
    if (hash == NULL || handle->publicKeyx == NULL || handle->publicKeyy == NULL || r == NULL || s == NULL) {
        return -1;
    }

    Sec_Eng_PKA_Reset();
    Sec_Eng_PKA_BigEndian_Enable();

    /*Step 0: make sure r and s are in range 1..n-1*/

    /* r and s should not be 0*/
    Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_S_REG_INDEX, (uint32_t *)r, ECP_SECP256R1_SIZE / 4, 0);
    Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 8, (uint32_t *)secp256r1_1, ECP_SECP256R1_SIZE / 4, 0);
    //cout = 1 if r = 0
    Sec_Eng_PKA_LCMP((uint8_t *)&i, ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_S_REG_INDEX, ECP_SECP256R1_REG_TYPE, 8); //s0 < s1 => cout = 1

    if (i == 1) {
        return -1;
    }

    Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_S_REG_INDEX, (uint32_t *)s, ECP_SECP256R1_SIZE / 4, 0);
    //cout = 1 if r = 0
    Sec_Eng_PKA_LCMP((uint8_t *)&i, ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_S_REG_INDEX, ECP_SECP256R1_REG_TYPE, 8); //s0 < s1 => cout = 1

    if (i == 1) {
        return -1;
    }

    sec_ecc_basic_parameter_init(handle->ecpId);

    /* r and s should not be 0*/
    Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_S_REG_INDEX, (uint32_t *)r, ECP_SECP256R1_SIZE / 4, 0);
    //cout = 1 if r < N
    Sec_Eng_PKA_LCMP((uint8_t *)&i, ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_S_REG_INDEX, ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_N_REG_INDEX);

    if (i != 1) {
        return -1;
    }

    Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_S_REG_INDEX, (uint32_t *)s, ECP_SECP256R1_SIZE / 4, 0);
    //cout = 1 if r < N
    Sec_Eng_PKA_LCMP((uint8_t *)&i, ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_S_REG_INDEX, ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_N_REG_INDEX);

    if (i != 1) {
        return -1;
    }

    /* u1 = e / s mod n, u2 = r / s mod n
     * R = u1 G + u2 Q*/

    /* Step1: Get S^-1*/
    Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_S_REG_INDEX, (uint32_t *)s, ECP_SECP256R1_SIZE / 4, 0);
    /* Change s to Mont domain */
    /* Clear register for ECP_SECP256R1_LT_REG_INDEX*/
    Sec_Eng_PKA_CREG(ECP_SECP256R1_REG_TYPE, 2 * ECP_SECP256R1_LT_REG_INDEX - 1, ECP_SECP256R1_SIZE / 4, 1);
    Sec_Eng_PKA_CREG(ECP_SECP256R1_REG_TYPE, 2 * ECP_SECP256R1_LT_REG_INDEX, ECP_SECP256R1_SIZE / 4, 1);
    Sec_Eng_PKA_GF2Mont(ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_S_REG_INDEX, ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_S_REG_INDEX, 256,
                        ECP_SECP256R1_LT_REG_TYPE, ECP_SECP256R1_LT_REG_INDEX, ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_N_REG_INDEX);
#ifdef ECDSA_DBG
    Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_S_REG_INDEX, (uint32_t *)pka_tmp, ECP_SECP256R1_SIZE / 4);
    MSG("GF2Mont Result of s:\r\n");
    bflb_platform_dump(pka_tmp, ECP_SECP256R1_SIZE);
#endif

    /* Get S^-1 in Mont domain */
    Sec_Eng_PKA_MINV(ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_BAR_S_REG_INDEX, ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_S_REG_INDEX,
                     ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_N_REG_INDEX, 1);
#ifdef ECDSA_DBG
    Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_BAR_S_REG_INDEX, (uint32_t *)pka_tmp, ECP_SECP256R1_SIZE / 4);
    MSG("s^-1 in Mont:\r\n");
    bflb_platform_dump(pka_tmp, ECP_SECP256R1_SIZE);
#endif

    /* Change S^-1 into GF domain,now  ECP_SECP256R1_S_REG_INDEX store s^-1*/
    /* Clear register for ECP_SECP256R1_LT_REG_INDEX*/
    Sec_Eng_PKA_Mont2GF(ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_S_REG_INDEX, ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_BAR_S_REG_INDEX, ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_INVR_N_REG_INDEX,
                        ECP_SECP256R1_LT_REG_TYPE, ECP_SECP256R1_LT_REG_INDEX, ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_N_REG_INDEX);
#ifdef ECDSA_DBG
    Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_S_REG_INDEX, (uint32_t *)pka_tmp, ECP_SECP256R1_SIZE / 4);
    MSG("S^-1:\r\n");
    bflb_platform_dump(pka_tmp, ECP_SECP256R1_SIZE);
#endif

    /* Step2: Get u1*/
    //u1=hash(e)*s^-1;
    Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_HASH_REG_INDEX, (uint32_t *)hash, ECP_SECP256R1_SIZE / 4, 0);
    Sec_Eng_PKA_LMUL(ECP_SECP256R1_LT_REG_TYPE, ECP_SECP256R1_LT_REG_INDEX, ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_HASH_REG_INDEX,
                     ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_S_REG_INDEX, 0);
    Sec_Eng_PKA_MREM(ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_U1_REG_INDEX, ECP_SECP256R1_LT_REG_TYPE, ECP_SECP256R1_LT_REG_INDEX,
                     ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_N_REG_INDEX, 1);
    Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_U1_REG_INDEX, (uint32_t *)pka_u1, ECP_SECP256R1_SIZE / 4);
#ifdef ECDSA_DBG
    MSG("u1:\r\n");
    bflb_platform_dump(pka_u1, ECP_SECP256R1_SIZE);
#endif

    /* Step3: Get u2*/
    //u2=r*s^-1;
    // use hash and u1 temp register
    Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_HASH_REG_INDEX, (uint32_t *)r, ECP_SECP256R1_SIZE / 4, 0);
    Sec_Eng_PKA_LMUL(ECP_SECP256R1_LT_REG_TYPE, ECP_SECP256R1_LT_REG_INDEX, ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_HASH_REG_INDEX,
                     ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_S_REG_INDEX, 0);
    Sec_Eng_PKA_MREM(ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_U1_REG_INDEX, ECP_SECP256R1_LT_REG_TYPE, ECP_SECP256R1_LT_REG_INDEX,
                     ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_N_REG_INDEX, 1);
    Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_U1_REG_INDEX, (uint32_t *)pka_u2, ECP_SECP256R1_SIZE / 4);
#ifdef ECDSA_DBG
    MSG("u2:\r\n");
    bflb_platform_dump(pka_u2, ECP_SECP256R1_SIZE);
#endif

    /* Step4: Get u1*G*/

    //Clear D[7]
    //PKA_CREG(1,4, 7,0);
    Sec_Eng_PKA_CREG(ECP_SECP256R1_LT_REG_TYPE, 7, ECP_SECP256R1_SIZE / 4, 1);

    sec_ecc_point_mul_init(handle->ecpId);

    //X1
    //PKA_CTREG(3, 2,8,bar_Zero_x);
    Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 2, (uint32_t *)secp256r1_Zerox, ECP_SECP256R1_SIZE / 4, 0);
    //Y1
    //PKA_CTREG(3, 3,8,bar_Zero_y);
    Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 3, (uint32_t *)secp256r1_Zeroy, ECP_SECP256R1_SIZE / 4, 0);
    //Z1
    //PKA_CTREG(3, 4,8,bar_Zero_z);
    //PKA_MOVDAT(1,3, 4,3, 2);
    Sec_Eng_PKA_Move_Data(3, 4, 3, 2, 1);

    //X2
    //PKA_CTREG(3, 5,8,bar_G_x);
    Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 5, (uint32_t *)secp256r1_Gx, ECP_SECP256R1_SIZE / 4, 0);
    //Y2
    //PKA_CTREG(3, 6,8,bar_G_y);
    Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 6, (uint32_t *)secp256r1_Gy, ECP_SECP256R1_SIZE / 4, 0);
    //Z2
    //PKA_CTREG(3, 7,8,bar_G_z);
    //PKA_MOVDAT(1,3, 7,3, 3);
    Sec_Eng_PKA_Move_Data(3, 7, 3, 3, 1);

    sec_ecdsa_verify_point_mul(handle->ecpId, pka_u1);
    //get bar_u1_x
    Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, 2, (uint32_t *)bar_u1_x, ECP_SECP256R1_SIZE / 4);
#ifdef ECDSA_DBG
    MSG("bar_u1_x\r\n");
    bflb_platform_dump(bar_u1_x, ECP_SECP256R1_SIZE);
#endif
    Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, 3, (uint32_t *)bar_u1_y, ECP_SECP256R1_SIZE / 4);
#ifdef ECDSA_DBG
    MSG("bar_u1_y\r\n");
    bflb_platform_dump(bar_u1_y, ECP_SECP256R1_SIZE);
#endif
    Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, 4, (uint32_t *)bar_u1_z, ECP_SECP256R1_SIZE / 4);
#ifdef ECDSA_DBG
    MSG("bar_u1_z\r\n");
    bflb_platform_dump(bar_u1_z, ECP_SECP256R1_SIZE);
#endif

    /* Step4: Get u2*Q*/
    //X1
    //PKA_CTREG(3, 2,8,bar_Zero_x);
    Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 2, (uint32_t *)secp256r1_Zerox, ECP_SECP256R1_SIZE / 4, 0);
    //Y1
    //PKA_CTREG(3, 3,8,bar_Zero_y);
    Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 3, (uint32_t *)secp256r1_Zeroy, ECP_SECP256R1_SIZE / 4, 0);
    //Z1
    //PKA_CTREG(3, 4,8,bar_Zero_z);
    //PKA_MOVDAT(1,3, 4,3, 2);
    Sec_Eng_PKA_Move_Data(3, 4, 3, 2, 1);

    //PUB_x
    //PKA_CTREG(3, 5,8,PUB_x);
    Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 5, (uint32_t *)handle->publicKeyx, ECP_SECP256R1_SIZE / 4, 0);
    //bar_pub_x
    //PKA_GF2MONT(3, 5,3, 5);
    /* Change s to Mont domain,remember to clear temp register and index 0 is P256*/
    /* Clear register for ECP_SECP256R1_LT_REG_INDEX*/
    Sec_Eng_PKA_CREG(ECP_SECP256R1_REG_TYPE, 2 * ECP_SECP256R1_LT_REG_INDEX - 1, ECP_SECP256R1_SIZE / 4, 1);
    Sec_Eng_PKA_CREG(ECP_SECP256R1_REG_TYPE, 2 * ECP_SECP256R1_LT_REG_INDEX, ECP_SECP256R1_SIZE / 4, 1);
    Sec_Eng_PKA_GF2Mont(ECP_SECP256R1_REG_TYPE, 5, ECP_SECP256R1_REG_TYPE, 5, 256,
                        ECP_SECP256R1_LT_REG_TYPE, ECP_SECP256R1_LT_REG_INDEX, ECP_SECP256R1_REG_TYPE, 0);
#ifdef ECDSA_DBG
    Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, 5, (uint32_t *)pka_tmp, ECP_SECP256R1_SIZE / 4);
    MSG("PK.x in Mont:\r\n");
    bflb_platform_dump(pka_tmp, ECP_SECP256R1_SIZE);
#endif

    //PUB_y
    //PKA_CTREG(3, 6,8,PUB_y);
    Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 6, (uint32_t *)handle->publicKeyy, ECP_SECP256R1_SIZE / 4, 0);
    //bar_pub_y
    //PKA_GF2MONT(3, 6,3, 6);
    Sec_Eng_PKA_CREG(ECP_SECP256R1_REG_TYPE, 2 * ECP_SECP256R1_LT_REG_INDEX - 1, ECP_SECP256R1_SIZE / 4, 1);
    Sec_Eng_PKA_CREG(ECP_SECP256R1_REG_TYPE, 2 * ECP_SECP256R1_LT_REG_INDEX, ECP_SECP256R1_SIZE / 4, 1);
    Sec_Eng_PKA_GF2Mont(ECP_SECP256R1_REG_TYPE, 6, ECP_SECP256R1_REG_TYPE, 6, 256,
                        ECP_SECP256R1_LT_REG_TYPE, ECP_SECP256R1_LT_REG_INDEX, ECP_SECP256R1_REG_TYPE, 0);
#ifdef ECDSA_DBG
    Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, 6, (uint32_t *)pka_tmp, ECP_SECP256R1_SIZE / 4);
    MSG("PK.y in Mont:\r\n");
    bflb_platform_dump(pka_tmp, ECP_SECP256R1_SIZE);
#endif

    //bar_pub_z
    //PKA_CTREG(3, 7,8,PUB_z);
    //PKA_MOVDAT(1,3, 7,3, 3);
    Sec_Eng_PKA_Move_Data(3, 7, 3, 3, 1);

    /* Clear temp register since it's used in point-mul*/
    Sec_Eng_PKA_CREG(ECP_SECP256R1_LT_REG_TYPE, 7, ECP_SECP256R1_SIZE / 4, 1);

    sec_ecdsa_verify_point_mul(handle->ecpId, pka_u2);
    //get bar_u1_x
    Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, 2, (uint32_t *)bar_u2_x, ECP_SECP256R1_SIZE / 4);
#ifdef ECDSA_DBG
    MSG("bar_u2_x\r\n");
    bflb_platform_dump(bar_u2_x, ECP_SECP256R1_SIZE);
#endif
    Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, 3, (uint32_t *)bar_u2_y, ECP_SECP256R1_SIZE / 4);
#ifdef ECDSA_DBG
    MSG("bar_u2_y\r\n");
    bflb_platform_dump(bar_u2_y, ECP_SECP256R1_SIZE);
#endif
    Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, 4, (uint32_t *)bar_u2_z, ECP_SECP256R1_SIZE / 4);
#ifdef ECDSA_DBG
    MSG("bar_u2_z\r\n");
    bflb_platform_dump(bar_u2_z, ECP_SECP256R1_SIZE);
#endif

    /* Step5: Get u1*G+u2*Q*/
    //move bar_u2_x
    //PKA_MOVDAT(0,3, 5,3, 2);
    Sec_Eng_PKA_Move_Data(3, 5, 3, 2, 0);
    //move bar_u2_y
    //PKA_MOVDAT(0,3, 6,3, 3);
    Sec_Eng_PKA_Move_Data(3, 6, 3, 3, 0);
    //move bar_u2_z
    //PKA_MOVDAT(1,3, 7,3, 4);
    Sec_Eng_PKA_Move_Data(3, 7, 3, 4, 1);

    //bar_u1_x
    //PKA_CTREG(3, 2,8,bar_u1_x);
    Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 2, (uint32_t *)bar_u1_x, ECP_SECP256R1_SIZE / 4, 0);
    //bar_u1_y
    //PKA_CTREG(3, 3,8,bar_u1_y);
    Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 3, (uint32_t *)bar_u1_y, ECP_SECP256R1_SIZE / 4, 0);
    //bar_u1_z
    //PKA_CTREG(3, 4,8,bar_u1_z);
    Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 4, (uint32_t *)bar_u1_z, ECP_SECP256R1_SIZE / 4, 0);

    //R = u1 * G + u2 * PUB
    //PKA_POINT_ADDITION();
    sec_ecdsa_point_add(handle->ecpId);

    /* Step6 Get R.x(R=u1G+u2P)*/
    //R.z ^ -1
    //PKA_MINV(0,3, 5,3, 4,3, 0);
    Sec_Eng_PKA_MINV(ECP_SECP256R1_REG_TYPE, 5, ECP_SECP256R1_REG_TYPE, 4, ECP_SECP256R1_REG_TYPE, 0, 1);
    //inv_r
    //PKA_CTREG(3, 6,8,inv_r);
    Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 6, (uint32_t *)secp256r1InvR_P, ECP_SECP256R1_SIZE / 4, 0);
    //R.z ^ -1
    Sec_Eng_PKA_CREG(ECP_SECP256R1_REG_TYPE, 2 * ECP_SECP256R1_LT_REG_INDEX - 1, ECP_SECP256R1_SIZE / 4, 1);
    Sec_Eng_PKA_CREG(ECP_SECP256R1_REG_TYPE, 2 * ECP_SECP256R1_LT_REG_INDEX, ECP_SECP256R1_SIZE / 4, 1);
    //PKA_MONT2GF(3, 5,3, 5,3, 6);
    Sec_Eng_PKA_Mont2GF(ECP_SECP256R1_REG_TYPE, 5, ECP_SECP256R1_REG_TYPE, 5, ECP_SECP256R1_REG_TYPE, 6,
                        ECP_SECP256R1_LT_REG_TYPE, ECP_SECP256R1_LT_REG_INDEX, ECP_SECP256R1_REG_TYPE, 0);

    //R.x (Montgomery to GF)
    //PKA_MONT2GF(3, 6,3, 2,3, 6);
    Sec_Eng_PKA_Mont2GF(ECP_SECP256R1_REG_TYPE, 6, ECP_SECP256R1_REG_TYPE, 2, ECP_SECP256R1_REG_TYPE, 6,
                        ECP_SECP256R1_LT_REG_TYPE, ECP_SECP256R1_LT_REG_INDEX, ECP_SECP256R1_REG_TYPE, 0);

    //R.x (GF to Affine domain)
    //PKA_MONT2GF(3, 2,3, 5,3, 6);
    Sec_Eng_PKA_Mont2GF(ECP_SECP256R1_REG_TYPE, 2, ECP_SECP256R1_REG_TYPE, 5, ECP_SECP256R1_REG_TYPE, 6,
                        ECP_SECP256R1_LT_REG_TYPE, ECP_SECP256R1_LT_REG_INDEX, ECP_SECP256R1_REG_TYPE, 0);
    Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, 2, (uint32_t *)bar_u2_x, ECP_SECP256R1_SIZE / 4);
#ifdef ECDSA_DBG
    MSG("R.x=\r\n");
    bflb_platform_dump(bar_u2_x, ECP_SECP256R1_SIZE);
#endif

    /* Step7 check R.x=r*/
    /* Check Result */
    for (i = 0; i < 8; i++) {
        if (bar_u2_x[i] != r[i]) {
            return -1;
        }
    }

#ifdef ECDSA_DBG
    MSG("Verify success\r\n");
#endif

    sec_ecdsa_verify_suss_callback(SEC_CODEPATH_STATE_SIGN, 1);
    
    return 0;
}

int sec_ecdsa_sign(sec_ecdsa_handle_t *handle, const uint32_t *random_k, const uint32_t *hash, uint32_t hashLenInWord, uint32_t *r, uint32_t *s)
{
    uint32_t k[8];
    uint32_t Rx[8];
    uint32_t Ry[8];
    uint32_t KInvert[8];
    uint32_t maxTry1 = 100;

    /* Pointer check */
    if (handle->privateKey == NULL || hash == NULL || r == NULL || s == NULL) {
        return -1;
    }

    Sec_Eng_PKA_Reset();
    Sec_Eng_PKA_BigEndian_Enable();
    Sec_Eng_Trng_Enable();

    while (maxTry1--) {
        /* step 1 ,get random k*/
        if (random_k == NULL) {
            if (sec_ecc_get_random_value(k, (uint32_t *)secp256r1N, 32) < 0) {
                return -1;
            }
        } else {
            memcpy(k, random_k, 32);
        }

#ifdef ECDSA_DBG
        MSG("Random k:\r\n");
        bflb_platform_dump(k, ECP_SECP256R1_SIZE);
#endif

        /*step 2, calc R=kG*/
        if (sec_ecdsa_get_public_key(handle, k, Rx, Ry) < 0) {
            return -1;
        }

        if (sec_ecc_is_zero((uint8_t *)Rx, 32)) {
            continue;
        }

        memcpy(r, Rx, 32);
#ifdef ECDSA_DBG
        MSG("r:\r\n");
        bflb_platform_dump(r, ECP_SECP256R1_SIZE);
#endif
        sec_ecc_basic_parameter_init(handle->ecpId);
        /* step 3,get k^-1*/
        Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 5, (uint32_t *)k, ECP_SECP256R1_SIZE / 4, 0);
        Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_N_REG_INDEX, (uint32_t *)secp256r1N, ECP_SECP256R1_SIZE / 4, 0);
        /* Change k to Mont domain */
        /* Clear register for ECP_SECP256R1_LT_REG_INDEX*/
        Sec_Eng_PKA_CREG(ECP_SECP256R1_REG_TYPE, 2 * ECP_SECP256R1_LT_REG_INDEX - 1, ECP_SECP256R1_SIZE / 4, 1);
        Sec_Eng_PKA_CREG(ECP_SECP256R1_REG_TYPE, 2 * ECP_SECP256R1_LT_REG_INDEX, ECP_SECP256R1_SIZE / 4, 1);
        Sec_Eng_PKA_GF2Mont(ECP_SECP256R1_REG_TYPE, 5, ECP_SECP256R1_REG_TYPE, 5, 256,
                            ECP_SECP256R1_LT_REG_TYPE, ECP_SECP256R1_LT_REG_INDEX, ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_N_REG_INDEX);
#ifdef ECDSA_DBG
        Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, 5, (uint32_t *)pka_tmp, ECP_SECP256R1_SIZE / 4);
        MSG("GF2Mont Result of k:\r\n");
        bflb_platform_dump(pka_tmp, ECP_SECP256R1_SIZE);
#endif

        /* Get k^-1 in Mont domain */
        Sec_Eng_PKA_MINV(ECP_SECP256R1_REG_TYPE, 6, ECP_SECP256R1_REG_TYPE, 5,
                         ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_N_REG_INDEX, 1);
#ifdef ECDSA_DBG
        Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, 6, (uint32_t *)KInvert, ECP_SECP256R1_SIZE / 4);
        MSG("k^-1 in Mont:\r\n");
        bflb_platform_dump(KInvert, ECP_SECP256R1_SIZE);
#endif

        /* Change k^-1 into GF domain,now  ECP_SECP256R1_S_REG_INDEX store k^-1*/
        /* Clear register for ECP_SECP256R1_LT_REG_INDEX*/
        Sec_Eng_PKA_Mont2GF(ECP_SECP256R1_REG_TYPE, 5, ECP_SECP256R1_REG_TYPE, 6, ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_INVR_N_REG_INDEX,
                            ECP_SECP256R1_LT_REG_TYPE, ECP_SECP256R1_LT_REG_INDEX, ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_N_REG_INDEX);
        Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, 5, (uint32_t *)KInvert, ECP_SECP256R1_SIZE / 4);
#ifdef ECDSA_DBG
        MSG("k^-1:\r\n");
        bflb_platform_dump(KInvert, ECP_SECP256R1_SIZE);
#endif

        /* Step 4,r*d     ((e + r * d) / k) */
        Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 4, (uint32_t *)handle->privateKey, ECP_SECP256R1_SIZE / 4, 0);
        Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 5, (uint32_t *)r, ECP_SECP256R1_SIZE / 4, 0);
        Sec_Eng_PKA_LMUL(ECP_SECP256R1_SLT_REG_TYPE, ECP_SECP256R1_SLT_REG_INDEX, ECP_SECP256R1_REG_TYPE, 4,
                         ECP_SECP256R1_REG_TYPE, 5, 1);
#ifdef ECDSA_DBG
        Sec_Eng_PKA_Read_Data(ECP_SECP256R1_SLT_REG_TYPE, ECP_SECP256R1_SLT_REG_INDEX, (uint32_t *)pka_tmp, ECP_SECP256R1_SIZE / 2);
        MSG("r*d:\r\n");
        bflb_platform_dump(pka_tmp, ECP_SECP256R1_SIZE * 2);
#endif

        /* Step 5,e+r*d   ((e + r * d) / k) */
        Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 5, (uint32_t *)hash, ECP_SECP256R1_SIZE / 4, 0);
        Sec_Eng_PKA_LADD(ECP_SECP256R1_SLT_REG_TYPE, ECP_SECP256R1_SLT_REG_INDEX, ECP_SECP256R1_SLT_REG_TYPE, ECP_SECP256R1_SLT_REG_INDEX,
                         ECP_SECP256R1_REG_TYPE, 5, 1);
#ifdef ECDSA_DBG
        Sec_Eng_PKA_Read_Data(ECP_SECP256R1_SLT_REG_TYPE, ECP_SECP256R1_SLT_REG_INDEX, (uint32_t *)pka_tmp, ECP_SECP256R1_SIZE / 2);
        MSG("e+r*d:\r\n");
        bflb_platform_dump(pka_tmp, ECP_SECP256R1_SIZE * 2);
#endif

        /* Step 6,(e+r*d)*k^-1   ((e + r * d) / k) */
        Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, 5, (uint32_t *)KInvert, ECP_SECP256R1_SIZE / 4, 0);
        Sec_Eng_PKA_LMUL(ECP_SECP256R1_SLT_REG_TYPE, ECP_SECP256R1_SLT_REG_INDEX, ECP_SECP256R1_SLT_REG_TYPE, ECP_SECP256R1_SLT_REG_INDEX,
                         ECP_SECP256R1_REG_TYPE, 5, 1);
#ifdef ECDSA_DBG
        Sec_Eng_PKA_Read_Data(ECP_SECP256R1_SLT_REG_TYPE, ECP_SECP256R1_SLT_REG_INDEX, (uint32_t *)pka_tmp, ECP_SECP256R1_SIZE / 2);
        MSG("(e+r*d)*k^-1:\r\n");
        bflb_platform_dump(pka_tmp, ECP_SECP256R1_SIZE * 2);
#endif
        /*N write only this time,add following operation will not change this register*/
        Sec_Eng_PKA_Write_Data(ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_N_REG_INDEX, (uint32_t *)secp256r1N, ECP_SECP256R1_SIZE / 4, 0);
        Sec_Eng_PKA_MREM(ECP_SECP256R1_REG_TYPE, 4, ECP_SECP256R1_SLT_REG_TYPE, ECP_SECP256R1_SLT_REG_INDEX,
                         ECP_SECP256R1_REG_TYPE, ECP_SECP256R1_N_REG_INDEX, 1);
        Sec_Eng_PKA_Read_Data(ECP_SECP256R1_REG_TYPE, 4, (uint32_t *)s, ECP_SECP256R1_SIZE / 4);
#ifdef ECDSA_DBG
        MSG("s:\r\n");
        bflb_platform_dump(s, ECP_SECP256R1_SIZE);
#endif

        /* Check s zero*/
        if (sec_ecc_is_zero((uint8_t *)s, 32)) {
            continue;
        }

        return 0;
    }

    return -1;
}

int sec_ecdsa_get_private_key(sec_ecdsa_handle_t *handle, uint32_t *private_key)
{
    if (sec_ecc_get_random_value(private_key, (uint32_t *)secp256r1N, 32) < 0) {
        return -1;
    }

    return 0;
}

int sec_ecdsa_get_public_key(sec_ecdsa_handle_t *handle, const uint32_t *private_key, const uint32_t *pRx, const uint32_t *pRy)
{
    return sec_ecdh_get_scalar_point(handle->ecpId, NULL, NULL, private_key, pRx, pRy);
}

int sec_ecc_get_random_value(uint32_t *randomData, uint32_t *maxRef, uint32_t size)
{
    uint32_t maxTry = 100;
    int32_t ret = 0;

    while (maxTry--) {
        ret = Sec_Eng_Trng_Get_Random((uint8_t *)randomData, size);

        if (ret < 0) {
            return -1;
        }

        if (maxRef != NULL) {
            if (sec_ecc_cmp((uint8_t *)maxRef, (uint8_t *)randomData, size) > 0) {
                return 0;
            }
        } else {
            return 0;
        }
    }

    return -1;
}

int sec_eng_trng_enable(void)
{
    return Sec_Eng_Trng_Enable();
}

void sec_eng_trng_disable(void)
{
    Sec_Eng_Trng_Disable();
}

int sec_eng_trng_read(uint8_t data[32])
{
    return Sec_Eng_Trng_Read(data);
}

int sec_ecdh_init(sec_ecdh_handle_t *handle, sec_ecp_type id)
{
    Sec_Eng_PKA_Reset();
    Sec_Eng_PKA_BigEndian_Enable();
    Sec_Eng_Trng_Enable();

    handle->ecpId = id;

    return 0;
}

int sec_ecdh_deinit(sec_ecdh_handle_t *handle)
{
    Sec_Eng_PKA_Reset();

    return 0;
}

int sec_ecdh_get_encrypt_key(sec_ecdh_handle_t *handle, const uint32_t *pkX, const uint32_t *pkY, const uint32_t *private_key, const uint32_t *pRx, const uint32_t *pRy)
{
    return sec_ecdh_get_scalar_point(handle->ecpId, pkX, pkY, private_key, pRx, pRy);
}

int sec_ecdh_get_public_key(sec_ecdh_handle_t *handle, const uint32_t *private_key, const uint32_t *pRx, const uint32_t *pRy)
{
    return sec_ecdh_get_scalar_point(handle->ecpId, NULL, NULL, private_key, pRx, pRy);
}
