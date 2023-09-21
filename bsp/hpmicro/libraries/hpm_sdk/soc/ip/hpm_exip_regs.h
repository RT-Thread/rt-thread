/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_EXIP_H
#define HPM_EXIP_H

typedef struct {
    __R  uint8_t  RESERVED0[3072];             /* 0x0 - 0xBFF: Reserved */
    __RW uint32_t CFG;                         /* 0xC00: Configure Register */
    __R  uint32_t STA;                         /* 0xC04: Status Register */
    __R  uint8_t  RESERVED1[248];              /* 0xC08 - 0xCFF: Reserved */
    struct {
        __RW uint32_t KEY0;                    /* 0xD00: AES KEY */
        __RW uint32_t KEY1;                    /* 0xD04: AES KEY */
        __RW uint32_t KEY2;                    /* 0xD08: AES KEY */
        __RW uint32_t KEY3;                    /* 0xD0C: AES KEY */
        __RW uint32_t CTR0;                    /* 0xD10: AES Counter Word */
        __RW uint32_t CTR1;                    /* 0xD14: AES Counter Word */
        __RW uint32_t RGN_SA;                  /* 0xD18: AES Region Descriptor Word */
        __RW uint32_t RGN_EA;                  /* 0xD1C: AES Region Descriptor Word */
        __R  uint8_t  RESERVED0[32];           /* 0xD20 - 0xD3F: Reserved */
    } RGN[4];
} EXIP_Type;


/* Bitfield definition for register: CFG */
/*
 * EXIPE (RW)
 *
 * Block Enable, when set to "0", this block disabled, and all the data from QSPI will pass the the read mast directly; EXIP process data as the configuration in the CR regs.
 */
#define EXIP_CFG_EXIPE_MASK (0x80000000UL)
#define EXIP_CFG_EXIPE_SHIFT (31U)
#define EXIP_CFG_EXIPE_SET(x) (((uint32_t)(x) << EXIP_CFG_EXIPE_SHIFT) & EXIP_CFG_EXIPE_MASK)
#define EXIP_CFG_EXIPE_GET(x) (((uint32_t)(x) & EXIP_CFG_EXIPE_MASK) >> EXIP_CFG_EXIPE_SHIFT)

/*
 * KBS (RW)
 *
 * KeyBlob Initiate
 * "0", Key Blob was not initiated yet.
 * "1", Key Blob was properly initiated.
 */
#define EXIP_CFG_KBS_MASK (0x40000000UL)
#define EXIP_CFG_KBS_SHIFT (30U)
#define EXIP_CFG_KBS_SET(x) (((uint32_t)(x) << EXIP_CFG_KBS_SHIFT) & EXIP_CFG_KBS_MASK)
#define EXIP_CFG_KBS_GET(x) (((uint32_t)(x) & EXIP_CFG_KBS_MASK) >> EXIP_CFG_KBS_SHIFT)

/*
 * KBEN (RW)
 *
 * Key Block Processing Enable.
 * "0", key blob processing is enabled.
 * "1", Key blob processing is disabled.
 */
#define EXIP_CFG_KBEN_MASK (0x20U)
#define EXIP_CFG_KBEN_SHIFT (5U)
#define EXIP_CFG_KBEN_SET(x) (((uint32_t)(x) << EXIP_CFG_KBEN_SHIFT) & EXIP_CFG_KBEN_MASK)
#define EXIP_CFG_KBEN_GET(x) (((uint32_t)(x) & EXIP_CFG_KBEN_MASK) >> EXIP_CFG_KBEN_SHIFT)

/*
 * IE (RW)
 *
 * Interrupt Request Enable. This field determines if the setting of SR[KBERR] generates a system interrupt.
 * 0b - SR[KBERR] = 1 does not generate an interrupt request.
 * 1b - SR[KBERR] = 1 generates an interrupt request.
 */
#define EXIP_CFG_IE_MASK (0x1U)
#define EXIP_CFG_IE_SHIFT (0U)
#define EXIP_CFG_IE_SET(x) (((uint32_t)(x) << EXIP_CFG_IE_SHIFT) & EXIP_CFG_IE_MASK)
#define EXIP_CFG_IE_GET(x) (((uint32_t)(x) & EXIP_CFG_IE_MASK) >> EXIP_CFG_IE_SHIFT)

/* Bitfield definition for register: STA */
/*
 * KBC (RO)
 *
 * Key Blob Processing Done
 * "0", key blob was not enabled or processing not done yet.
 * "1", key blob processing was enabled and done.
 */
#define EXIP_STA_KBC_MASK (0x80000000UL)
#define EXIP_STA_KBC_SHIFT (31U)
#define EXIP_STA_KBC_GET(x) (((uint32_t)(x) & EXIP_STA_KBC_MASK) >> EXIP_STA_KBC_SHIFT)

/*
 * KBEN (RO)
 *
 * Key Blob Processing Enable
 * “0”, Key Blob processing is not enabled.
 * "1", Key Blob processing is enabled.
 */
#define EXIP_STA_KBEN_MASK (0x40000000UL)
#define EXIP_STA_KBEN_SHIFT (30U)
#define EXIP_STA_KBEN_GET(x) (((uint32_t)(x) & EXIP_STA_KBEN_MASK) >> EXIP_STA_KBEN_SHIFT)

/*
 * EXIPE (RO)
 *
 * Block Enable Mode.
 * "0", EXIP disabled and bypasses all the data by the QSPI
 * "1", EXIP is enabled, and processes data from the QSPI as the hw configuration bits.
 */
#define EXIP_STA_EXIPE_MASK (0x20000000UL)
#define EXIP_STA_EXIPE_SHIFT (29U)
#define EXIP_STA_EXIPE_GET(x) (((uint32_t)(x) & EXIP_STA_EXIPE_MASK) >> EXIP_STA_EXIPE_SHIFT)

/*
 * RGNE (RO)
 *
 * Context Integrity Error.
 * This field signals an integrity error was detected in a specific context during key blob processing as signaled by SR[KBERR] = 1. bit 19 corresponds to context 3, bit 18 to context 2, bit 17 to context 1, bit 16 to context 0.
 *  This field is cleared if SR[KBERR] was set in response to a write asserting CR[FERR]. It is also cleared when SR[KBERR] is cleared.
 * 0000b - No key blob integrity error was detected for context “n”.
 * 0001b - A key blob integrity error was detected in context “n”.
 */
#define EXIP_STA_RGNE_MASK (0xF0000UL)
#define EXIP_STA_RGNE_SHIFT (16U)
#define EXIP_STA_RGNE_GET(x) (((uint32_t)(x) & EXIP_STA_RGNE_MASK) >> EXIP_STA_RGNE_SHIFT)

/*
 * KBERR (RO)
 *
 * Key Blob Error
 * This field signals that one or more errors were detected during key blob processing. SR[ERCTX] provides
 * the details on which contexts detected errors. This indicator can also be set by writing CR[FERR] = 1 (for
 * testing purposes). If CR[IRQE] = 1, then the assertion of KBERR generates an interrupt request.
 * "0", No key blob error detected.
 * "1", One or more key blob errors has been detected
 */
#define EXIP_STA_KBERR_MASK (0x1U)
#define EXIP_STA_KBERR_SHIFT (0U)
#define EXIP_STA_KBERR_GET(x) (((uint32_t)(x) & EXIP_STA_KBERR_MASK) >> EXIP_STA_KBERR_SHIFT)

/* Bitfield definition for register of struct array RGN: KEY0 */
/*
 * KEY (RW)
 *
 * AES Key
 * The key is typically loaded as the corresponding key blob is unwrapped; alternatively, if enabled, it can be
 * written using the APB bus. The four consecutive little-endian memory-mapped registers
 * provide 128 bits of key storage.
 * Word0: KEY[31:0][A03, A02, A01, A00]
 * Word1: KEY[31:0][A07, A06, A05, A04]
 * Word2: KEY[31:0][A11, A10, A09, A08]
 * Word3: KEY[31:0][A15, A14, A13, A12]
 */
#define EXIP_RGN_KEY0_KEY_MASK (0xFFFFFFFFUL)
#define EXIP_RGN_KEY0_KEY_SHIFT (0U)
#define EXIP_RGN_KEY0_KEY_SET(x) (((uint32_t)(x) << EXIP_RGN_KEY0_KEY_SHIFT) & EXIP_RGN_KEY0_KEY_MASK)
#define EXIP_RGN_KEY0_KEY_GET(x) (((uint32_t)(x) & EXIP_RGN_KEY0_KEY_MASK) >> EXIP_RGN_KEY0_KEY_SHIFT)

/* Bitfield definition for register of struct array RGN: KEY1 */
/*
 * KEY (RW)
 *
 * AES Key
 * The key is typically loaded as the corresponding key blob is unwrapped; alternatively, if enabled, it can be
 * written using the APB bus. The four consecutive little-endian memory-mapped registers
 * provide 128 bits of key storage.
 * Word0: KEY[31:0][A03, A02, A01, A00]
 * Word1: KEY[31:0][A07, A06, A05, A04]
 * Word2: KEY[31:0][A11, A10, A09, A08]
 * Word3: KEY[31:0][A15, A14, A13, A12]
 */
#define EXIP_RGN_KEY1_KEY_MASK (0xFFFFFFFFUL)
#define EXIP_RGN_KEY1_KEY_SHIFT (0U)
#define EXIP_RGN_KEY1_KEY_SET(x) (((uint32_t)(x) << EXIP_RGN_KEY1_KEY_SHIFT) & EXIP_RGN_KEY1_KEY_MASK)
#define EXIP_RGN_KEY1_KEY_GET(x) (((uint32_t)(x) & EXIP_RGN_KEY1_KEY_MASK) >> EXIP_RGN_KEY1_KEY_SHIFT)

/* Bitfield definition for register of struct array RGN: KEY2 */
/*
 * KEY (RW)
 *
 * AES Key
 * The key is typically loaded as the corresponding key blob is unwrapped; alternatively, if enabled, it can be
 * written using the APB bus. The four consecutive little-endian memory-mapped registers
 * provide 128 bits of key storage.
 * Word0: KEY[31:0][A03, A02, A01, A00]
 * Word1: KEY[31:0][A07, A06, A05, A04]
 * Word2: KEY[31:0][A11, A10, A09, A08]
 * Word3: KEY[31:0][A15, A14, A13, A12]
 */
#define EXIP_RGN_KEY2_KEY_MASK (0xFFFFFFFFUL)
#define EXIP_RGN_KEY2_KEY_SHIFT (0U)
#define EXIP_RGN_KEY2_KEY_SET(x) (((uint32_t)(x) << EXIP_RGN_KEY2_KEY_SHIFT) & EXIP_RGN_KEY2_KEY_MASK)
#define EXIP_RGN_KEY2_KEY_GET(x) (((uint32_t)(x) & EXIP_RGN_KEY2_KEY_MASK) >> EXIP_RGN_KEY2_KEY_SHIFT)

/* Bitfield definition for register of struct array RGN: KEY3 */
/*
 * KEY (RW)
 *
 * AES Key
 * The key is typically loaded as the corresponding key blob is unwrapped; alternatively, if enabled, it can be
 * written using the APB bus. The four consecutive little-endian memory-mapped registers
 * provide 128 bits of key storage.
 * Word0: KEY[31:0][A03, A02, A01, A00]
 * Word1: KEY[31:0][A07, A06, A05, A04]
 * Word2: KEY[31:0][A11, A10, A09, A08]
 * Word3: KEY[31:0][A15, A14, A13, A12]
 */
#define EXIP_RGN_KEY3_KEY_MASK (0xFFFFFFFFUL)
#define EXIP_RGN_KEY3_KEY_SHIFT (0U)
#define EXIP_RGN_KEY3_KEY_SET(x) (((uint32_t)(x) << EXIP_RGN_KEY3_KEY_SHIFT) & EXIP_RGN_KEY3_KEY_MASK)
#define EXIP_RGN_KEY3_KEY_GET(x) (((uint32_t)(x) & EXIP_RGN_KEY3_KEY_MASK) >> EXIP_RGN_KEY3_KEY_SHIFT)

/* Bitfield definition for register of struct array RGN: CTR0 */
/*
 * CTR (RW)
 *
 * AES Counter
 * The upper 64 bits of the counter are typically loaded as the corresponding key blob is unwrapped;
 * alternatively, if enabled, it can be written using the slave peripheral bus. The two consecutive memorymapped registers directly provide the upper 64 bits of counter storage.
 * Word0: CTR[31:0][C3, C2, C1, C0]
 * Word1: CTR[31:0][C7, C6, C5, C4]
 * The third 32-bit portion of the CTR is formed by exclusive-or’ing the upper 64 bits of the counter as two
 * 32-bit values, while the least-significant portion of the counter is the 32-bit 0-modulo-16 byte system
 * address of the external flash memory.
 * CTR[C0...C15] = {CTR[C0...C7], CTR[C0...C3] ^ CTR[C4...C7], systemAddress[31–4], 0h}
 */
#define EXIP_RGN_CTR0_CTR_MASK (0xFFFFFFFFUL)
#define EXIP_RGN_CTR0_CTR_SHIFT (0U)
#define EXIP_RGN_CTR0_CTR_SET(x) (((uint32_t)(x) << EXIP_RGN_CTR0_CTR_SHIFT) & EXIP_RGN_CTR0_CTR_MASK)
#define EXIP_RGN_CTR0_CTR_GET(x) (((uint32_t)(x) & EXIP_RGN_CTR0_CTR_MASK) >> EXIP_RGN_CTR0_CTR_SHIFT)

/* Bitfield definition for register of struct array RGN: CTR1 */
/*
 * CTR (RW)
 *
 * AES Counter
 * The upper 64 bits of the counter are typically loaded as the corresponding key blob is unwrapped;
 * alternatively, if enabled, it can be written using the slave peripheral bus. The two consecutive memorymapped registers directly provide the upper 64 bits of counter storage.
 * Word0: CTR[31:0][C3, C2, C1, C0]
 * Word1: CTR[31:0][C7, C6, C5, C4]
 * The third 32-bit portion of the CTR is formed by exclusive-or’ing the upper 64 bits of the counter as two
 * 32-bit values, while the least-significant portion of the counter is the 32-bit 0-modulo-16 byte system
 * address of the external flash memory.
 * CTR[C0...C15] = {CTR[C0...C7], CTR[C0...C3] ^ CTR[C4...C7], systemAddress[31–4], 0h}
 */
#define EXIP_RGN_CTR1_CTR_MASK (0xFFFFFFFFUL)
#define EXIP_RGN_CTR1_CTR_SHIFT (0U)
#define EXIP_RGN_CTR1_CTR_SET(x) (((uint32_t)(x) << EXIP_RGN_CTR1_CTR_SHIFT) & EXIP_RGN_CTR1_CTR_MASK)
#define EXIP_RGN_CTR1_CTR_GET(x) (((uint32_t)(x) & EXIP_RGN_CTR1_CTR_MASK) >> EXIP_RGN_CTR1_CTR_SHIFT)

/* Bitfield definition for register of struct array RGN: RGN_SA */
/*
 * START (RW)
 *
 * Start Address
 * This field defines the most significant bits of the 0-modulo-1024 byte start address of the memory region
 * for context n.
 */
#define EXIP_RGN_RGN_SA_START_MASK (0xFFFFFC00UL)
#define EXIP_RGN_RGN_SA_START_SHIFT (10U)
#define EXIP_RGN_RGN_SA_START_SET(x) (((uint32_t)(x) << EXIP_RGN_RGN_SA_START_SHIFT) & EXIP_RGN_RGN_SA_START_MASK)
#define EXIP_RGN_RGN_SA_START_GET(x) (((uint32_t)(x) & EXIP_RGN_RGN_SA_START_MASK) >> EXIP_RGN_RGN_SA_START_SHIFT)

/* Bitfield definition for register of struct array RGN: RGN_EA */
/*
 * END (RW)
 *
 * End Address
 * This field defines the most significant bits of the 1023-modulo-1024 byte end address of the memory
 * region for context n.
 */
#define EXIP_RGN_RGN_EA_END_MASK (0xFFFFFC00UL)
#define EXIP_RGN_RGN_EA_END_SHIFT (10U)
#define EXIP_RGN_RGN_EA_END_SET(x) (((uint32_t)(x) << EXIP_RGN_RGN_EA_END_SHIFT) & EXIP_RGN_RGN_EA_END_MASK)
#define EXIP_RGN_RGN_EA_END_GET(x) (((uint32_t)(x) & EXIP_RGN_RGN_EA_END_MASK) >> EXIP_RGN_RGN_EA_END_SHIFT)

/*
 * DECEN (RW)
 *
 * AES Decryption Enable.
 * For accesses hitting in a valid context, this bit indicates if the fetched data is to be decrypted or simply
 * bypassed.
 * "0" - Bypass the fetched data.
 * "1" - Perform the CTR-AES128 mode decryption on the fetched data
 */
#define EXIP_RGN_RGN_EA_DECEN_MASK (0x2U)
#define EXIP_RGN_RGN_EA_DECEN_SHIFT (1U)
#define EXIP_RGN_RGN_EA_DECEN_SET(x) (((uint32_t)(x) << EXIP_RGN_RGN_EA_DECEN_SHIFT) & EXIP_RGN_RGN_EA_DECEN_MASK)
#define EXIP_RGN_RGN_EA_DECEN_GET(x) (((uint32_t)(x) & EXIP_RGN_RGN_EA_DECEN_MASK) >> EXIP_RGN_RGN_EA_DECEN_SHIFT)

/*
 * VALID (RW)
 *
 * Valid
 * This field signals if the context is valid or not.
 * "0" - Context is invalid.
 * "1" - Context is valid.
 */
#define EXIP_RGN_RGN_EA_VALID_MASK (0x1U)
#define EXIP_RGN_RGN_EA_VALID_SHIFT (0U)
#define EXIP_RGN_RGN_EA_VALID_SET(x) (((uint32_t)(x) << EXIP_RGN_RGN_EA_VALID_SHIFT) & EXIP_RGN_RGN_EA_VALID_MASK)
#define EXIP_RGN_RGN_EA_VALID_GET(x) (((uint32_t)(x) & EXIP_RGN_RGN_EA_VALID_MASK) >> EXIP_RGN_RGN_EA_VALID_SHIFT)



/* RGN register group index macro definition */
#define EXIP_RGN_0 (0UL)
#define EXIP_RGN_1 (1UL)
#define EXIP_RGN_2 (2UL)
#define EXIP_RGN_3 (3UL)


#endif /* HPM_EXIP_H */
