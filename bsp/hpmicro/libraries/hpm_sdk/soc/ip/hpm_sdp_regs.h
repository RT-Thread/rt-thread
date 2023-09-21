/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_SDP_H
#define HPM_SDP_H

typedef struct {
    __RW uint32_t SDPCR;                       /* 0x0: SDP control register */
    __RW uint32_t MODCTRL;                     /* 0x4: Mod control register. */
    __RW uint32_t PKTCNT;                      /* 0x8: packet counter registers. */
    __RW uint32_t STA;                         /* 0xC: Status Registers */
    __RW uint32_t KEYADDR;                     /* 0x10: Key Address */
    __RW uint32_t KEYDAT;                      /* 0x14: Key Data */
    __RW uint32_t CIPHIV[4];                   /* 0x18 - 0x24: Cipher Initializtion Vector 0 */
    __RW uint32_t HASWRD[8];                   /* 0x28 - 0x44: Hash Data Word 0 */
    __RW uint32_t CMDPTR;                      /* 0x48: Command Pointer */
    __RW uint32_t NPKTPTR;                     /* 0x4C: Next Packet Address Pointer */
    __RW uint32_t PKTCTL;                      /* 0x50: Packet Control Registers */
    __RW uint32_t PKTSRC;                      /* 0x54: Packet Memory Source Address */
    __RW uint32_t PKTDST;                      /* 0x58: Packet Memory Destination Address */
    __RW uint32_t PKTBUF;                      /* 0x5C: Packet buffer size. */
} SDP_Type;


/* Bitfield definition for register: SDPCR */
/*
 * SFTRST (RW)
 *
 * soft reset.
 * Write 1 then 0, to reset the SDP block.
 */
#define SDP_SDPCR_SFTRST_MASK (0x80000000UL)
#define SDP_SDPCR_SFTRST_SHIFT (31U)
#define SDP_SDPCR_SFTRST_SET(x) (((uint32_t)(x) << SDP_SDPCR_SFTRST_SHIFT) & SDP_SDPCR_SFTRST_MASK)
#define SDP_SDPCR_SFTRST_GET(x) (((uint32_t)(x) & SDP_SDPCR_SFTRST_MASK) >> SDP_SDPCR_SFTRST_SHIFT)

/*
 * CLKGAT (RW)
 *
 * Clock Gate for the SDP main logic.
 * Write to 1 will clock gate for most logic of the SDP block, dynamic power saving when not use SDP block.
 */
#define SDP_SDPCR_CLKGAT_MASK (0x40000000UL)
#define SDP_SDPCR_CLKGAT_SHIFT (30U)
#define SDP_SDPCR_CLKGAT_SET(x) (((uint32_t)(x) << SDP_SDPCR_CLKGAT_SHIFT) & SDP_SDPCR_CLKGAT_MASK)
#define SDP_SDPCR_CLKGAT_GET(x) (((uint32_t)(x) & SDP_SDPCR_CLKGAT_MASK) >> SDP_SDPCR_CLKGAT_SHIFT)

/*
 * CIPDIS (RO)
 *
 * Cipher Disable, read the info, whether the CIPHER features is besing disable in this chip or not.
 * 1, Cipher is disabled in this chip.
 * 0, Cipher is enabled in this chip.
 */
#define SDP_SDPCR_CIPDIS_MASK (0x20000000UL)
#define SDP_SDPCR_CIPDIS_SHIFT (29U)
#define SDP_SDPCR_CIPDIS_GET(x) (((uint32_t)(x) & SDP_SDPCR_CIPDIS_MASK) >> SDP_SDPCR_CIPDIS_SHIFT)

/*
 * HASDIS (RO)
 *
 * HASH Disable, read the info, whether the HASH features is besing disable in this chip or not.
 * 1, HASH is disabled in this chip.
 * 0, HASH is enabled in this chip.
 */
#define SDP_SDPCR_HASDIS_MASK (0x10000000UL)
#define SDP_SDPCR_HASDIS_SHIFT (28U)
#define SDP_SDPCR_HASDIS_GET(x) (((uint32_t)(x) & SDP_SDPCR_HASDIS_MASK) >> SDP_SDPCR_HASDIS_SHIFT)

/*
 * CIPHEN (RW)
 *
 * Cipher Enablement, controlled by SW.
 * 1, Cipher is Enabled.
 * 0, Cipher is Disabled.
 */
#define SDP_SDPCR_CIPHEN_MASK (0x800000UL)
#define SDP_SDPCR_CIPHEN_SHIFT (23U)
#define SDP_SDPCR_CIPHEN_SET(x) (((uint32_t)(x) << SDP_SDPCR_CIPHEN_SHIFT) & SDP_SDPCR_CIPHEN_MASK)
#define SDP_SDPCR_CIPHEN_GET(x) (((uint32_t)(x) & SDP_SDPCR_CIPHEN_MASK) >> SDP_SDPCR_CIPHEN_SHIFT)

/*
 * HASHEN (RW)
 *
 * HASH Enablement, controlled by SW.
 * 1, HASH is Enabled.
 * 0, HASH is Disabled.
 */
#define SDP_SDPCR_HASHEN_MASK (0x400000UL)
#define SDP_SDPCR_HASHEN_SHIFT (22U)
#define SDP_SDPCR_HASHEN_SET(x) (((uint32_t)(x) << SDP_SDPCR_HASHEN_SHIFT) & SDP_SDPCR_HASHEN_MASK)
#define SDP_SDPCR_HASHEN_GET(x) (((uint32_t)(x) & SDP_SDPCR_HASHEN_MASK) >> SDP_SDPCR_HASHEN_SHIFT)

/*
 * MCPEN (RW)
 *
 * Memory Copy Enablement, controlled by SW.
 * 1, Memory copy is Enabled.
 * 0, Memory copy is Disabled.
 */
#define SDP_SDPCR_MCPEN_MASK (0x200000UL)
#define SDP_SDPCR_MCPEN_SHIFT (21U)
#define SDP_SDPCR_MCPEN_SET(x) (((uint32_t)(x) << SDP_SDPCR_MCPEN_SHIFT) & SDP_SDPCR_MCPEN_MASK)
#define SDP_SDPCR_MCPEN_GET(x) (((uint32_t)(x) & SDP_SDPCR_MCPEN_MASK) >> SDP_SDPCR_MCPEN_SHIFT)

/*
 * CONFEN (RW)
 *
 * Constant Fill to memory, controlled by SW.
 * 1, Constant fill is Enabled.
 * 0, Constant fill is Disabled.
 */
#define SDP_SDPCR_CONFEN_MASK (0x100000UL)
#define SDP_SDPCR_CONFEN_SHIFT (20U)
#define SDP_SDPCR_CONFEN_SET(x) (((uint32_t)(x) << SDP_SDPCR_CONFEN_SHIFT) & SDP_SDPCR_CONFEN_MASK)
#define SDP_SDPCR_CONFEN_GET(x) (((uint32_t)(x) & SDP_SDPCR_CONFEN_MASK) >> SDP_SDPCR_CONFEN_SHIFT)

/*
 * DCRPDI (RW)
 *
 * Decryption Disable bit, Write to 1 to disable the decryption.
 */
#define SDP_SDPCR_DCRPDI_MASK (0x80000UL)
#define SDP_SDPCR_DCRPDI_SHIFT (19U)
#define SDP_SDPCR_DCRPDI_SET(x) (((uint32_t)(x) << SDP_SDPCR_DCRPDI_SHIFT) & SDP_SDPCR_DCRPDI_MASK)
#define SDP_SDPCR_DCRPDI_GET(x) (((uint32_t)(x) & SDP_SDPCR_DCRPDI_MASK) >> SDP_SDPCR_DCRPDI_SHIFT)

/*
 * TSTPKT0IRQ (RW)
 *
 * Test purpose for interrupt when Packet counter reachs "0", but CHAIN=1 in the current packet.
 */
#define SDP_SDPCR_TSTPKT0IRQ_MASK (0x20000UL)
#define SDP_SDPCR_TSTPKT0IRQ_SHIFT (17U)
#define SDP_SDPCR_TSTPKT0IRQ_SET(x) (((uint32_t)(x) << SDP_SDPCR_TSTPKT0IRQ_SHIFT) & SDP_SDPCR_TSTPKT0IRQ_MASK)
#define SDP_SDPCR_TSTPKT0IRQ_GET(x) (((uint32_t)(x) & SDP_SDPCR_TSTPKT0IRQ_MASK) >> SDP_SDPCR_TSTPKT0IRQ_SHIFT)

/*
 * RDSCEN (RW)
 *
 * when set to "1", the 1st data packet descriptor loacted in the register(CMDPTR, NPKTPTR, ...)
 * when set to "0", the 1st data packet descriptor loacted in the memeory(pointed by CMDPTR)
 */
#define SDP_SDPCR_RDSCEN_MASK (0x100U)
#define SDP_SDPCR_RDSCEN_SHIFT (8U)
#define SDP_SDPCR_RDSCEN_SET(x) (((uint32_t)(x) << SDP_SDPCR_RDSCEN_SHIFT) & SDP_SDPCR_RDSCEN_MASK)
#define SDP_SDPCR_RDSCEN_GET(x) (((uint32_t)(x) & SDP_SDPCR_RDSCEN_MASK) >> SDP_SDPCR_RDSCEN_SHIFT)

/*
 * INTEN (RW)
 *
 * Interrupt Enablement, controlled by SW.
 * 1, SDP interrupt is enabled.
 * 0, SDP interrupt is disabled.
 */
#define SDP_SDPCR_INTEN_MASK (0x1U)
#define SDP_SDPCR_INTEN_SHIFT (0U)
#define SDP_SDPCR_INTEN_SET(x) (((uint32_t)(x) << SDP_SDPCR_INTEN_SHIFT) & SDP_SDPCR_INTEN_MASK)
#define SDP_SDPCR_INTEN_GET(x) (((uint32_t)(x) & SDP_SDPCR_INTEN_MASK) >> SDP_SDPCR_INTEN_SHIFT)

/* Bitfield definition for register: MODCTRL */
/*
 * AESALG (RW)
 *
 * AES algorithem selection.
 * 0x0 = AES 128;
 * 0x1 = AES 256;
 * 0x8 = SM4；
 * Others, reserved.
 */
#define SDP_MODCTRL_AESALG_MASK (0xF0000000UL)
#define SDP_MODCTRL_AESALG_SHIFT (28U)
#define SDP_MODCTRL_AESALG_SET(x) (((uint32_t)(x) << SDP_MODCTRL_AESALG_SHIFT) & SDP_MODCTRL_AESALG_MASK)
#define SDP_MODCTRL_AESALG_GET(x) (((uint32_t)(x) & SDP_MODCTRL_AESALG_MASK) >> SDP_MODCTRL_AESALG_SHIFT)

/*
 * AESMOD (RW)
 *
 * AES mode selection.
 * 0x0 = ECB;
 * 0x1 = CBC;
 * Others, reserved.
 */
#define SDP_MODCTRL_AESMOD_MASK (0xF000000UL)
#define SDP_MODCTRL_AESMOD_SHIFT (24U)
#define SDP_MODCTRL_AESMOD_SET(x) (((uint32_t)(x) << SDP_MODCTRL_AESMOD_SHIFT) & SDP_MODCTRL_AESMOD_MASK)
#define SDP_MODCTRL_AESMOD_GET(x) (((uint32_t)(x) & SDP_MODCTRL_AESMOD_MASK) >> SDP_MODCTRL_AESMOD_SHIFT)

/*
 * AESKS (RW)
 *
 * AES Key Selection.
 * These regisgers are being used to select the AES key that stored in the 16x128 key ram of the SDP, or select the key from the OTP. Detail as following:
 * 0x00: key from the 16x128, this is the key read address, valid for AES128; AES256 will use 128 bit from this address and 128 bit key from next address as 256 bit AES key.
 * 0x01: key from the 16x128, this is the key read address, valid for AES128, not valid for AES286.
 * ....
 * 0x0E: key from the 16x128, this is the key read address, valid for AES128; AES256 will use 128 from this add and 128 from next add for the AES key.
 * 0x0F: key from the 16x128, this is the key read address, valid for AES128, not valid for AES286.
 * 0x20: kman_sk0[127:0] from the key manager for AES128; AES256 will use kman_sk0[255:0] as AES key.
 * 0x21: kman_sk0[255:128] from the key manager for AES128; not valid for AES256.
 * 0x22: kman_sk1[127:0] from the key manager for AES128; AES256 will use kman_sk1[255:0] as AES key.
 * 0x23: kman_sk1[255:128] from the key manager for AES128; not valid for AES256.
 * 0x24: kman_sk2[127:0] from the key manager for AES128; AES256 will use kman_sk2[255:0] as AES key.
 * 0x25: kman_sk2[255:128] from the key manager for AES128; not valid for AES256.
 * 0x26: kman_sk3[127:0] from the key manager for AES128; AES256 will use kman_sk3[255:0] as AES key.
 * 0x27: kman_sk3[255:128] from the key manager for AES128; not valid for AES256.
 * 0x30: exip0_key[127:0] from OTP for AES128; AES256 will use exip0_key[255:0] as AES key.
 * 0x31: exip0_key[255:128] from OTP for AES128; not valid for AES256.
 * 0x32: exip1_key[127:0] from OTP for AES128; AES256 will use exip1_key[255:0] as AES key.
 * 0x33: exip1_key[255:128] from OTP for AES128; not valid for AES256.
 * Other values, reserved.
 */
#define SDP_MODCTRL_AESKS_MASK (0xFC0000UL)
#define SDP_MODCTRL_AESKS_SHIFT (18U)
#define SDP_MODCTRL_AESKS_SET(x) (((uint32_t)(x) << SDP_MODCTRL_AESKS_SHIFT) & SDP_MODCTRL_AESKS_MASK)
#define SDP_MODCTRL_AESKS_GET(x) (((uint32_t)(x) & SDP_MODCTRL_AESKS_MASK) >> SDP_MODCTRL_AESKS_SHIFT)

/*
 * AESDIR (RW)
 *
 * AES direction
 * 1x1, AES Decryption
 * 1x0, AES Encryption.
 */
#define SDP_MODCTRL_AESDIR_MASK (0x10000UL)
#define SDP_MODCTRL_AESDIR_SHIFT (16U)
#define SDP_MODCTRL_AESDIR_SET(x) (((uint32_t)(x) << SDP_MODCTRL_AESDIR_SHIFT) & SDP_MODCTRL_AESDIR_MASK)
#define SDP_MODCTRL_AESDIR_GET(x) (((uint32_t)(x) & SDP_MODCTRL_AESDIR_MASK) >> SDP_MODCTRL_AESDIR_SHIFT)

/*
 * HASALG (RW)
 *
 * HASH Algorithem selection.
 * 0x0 SHA1 —
 * 0x1 CRC32 —
 * 0x2 SHA256 —
 */
#define SDP_MODCTRL_HASALG_MASK (0xF000U)
#define SDP_MODCTRL_HASALG_SHIFT (12U)
#define SDP_MODCTRL_HASALG_SET(x) (((uint32_t)(x) << SDP_MODCTRL_HASALG_SHIFT) & SDP_MODCTRL_HASALG_MASK)
#define SDP_MODCTRL_HASALG_GET(x) (((uint32_t)(x) & SDP_MODCTRL_HASALG_MASK) >> SDP_MODCTRL_HASALG_SHIFT)

/*
 * CRCEN (RW)
 *
 * CRC enable.
 * 1x1, CRC is enabled.
 * 1x0, CRC is disabled.
 */
#define SDP_MODCTRL_CRCEN_MASK (0x800U)
#define SDP_MODCTRL_CRCEN_SHIFT (11U)
#define SDP_MODCTRL_CRCEN_SET(x) (((uint32_t)(x) << SDP_MODCTRL_CRCEN_SHIFT) & SDP_MODCTRL_CRCEN_MASK)
#define SDP_MODCTRL_CRCEN_GET(x) (((uint32_t)(x) & SDP_MODCTRL_CRCEN_MASK) >> SDP_MODCTRL_CRCEN_SHIFT)

/*
 * HASCHK (RW)
 *
 * HASH Check Enable Bit.
 * 1x1, HASH check need, hash result will compare with the HASHRSLT 0-7 registers;
 * 1x0, HASH check is not enabled, HASHRSLT0-7 store the HASH result.
 * For SHA1, will use HASHRSLT0-3 words, and HASH 256 will use HASH0-7 words.
 */
#define SDP_MODCTRL_HASCHK_MASK (0x400U)
#define SDP_MODCTRL_HASCHK_SHIFT (10U)
#define SDP_MODCTRL_HASCHK_SET(x) (((uint32_t)(x) << SDP_MODCTRL_HASCHK_SHIFT) & SDP_MODCTRL_HASCHK_MASK)
#define SDP_MODCTRL_HASCHK_GET(x) (((uint32_t)(x) & SDP_MODCTRL_HASCHK_MASK) >> SDP_MODCTRL_HASCHK_SHIFT)

/*
 * HASOUT (RW)
 *
 * When hashing is enabled, this bit controls the input or output data of the AES engine is hashed.
 * 0 INPUT HASH
 * 1 OUTPUT HASH
 */
#define SDP_MODCTRL_HASOUT_MASK (0x200U)
#define SDP_MODCTRL_HASOUT_SHIFT (9U)
#define SDP_MODCTRL_HASOUT_SET(x) (((uint32_t)(x) << SDP_MODCTRL_HASOUT_SHIFT) & SDP_MODCTRL_HASOUT_MASK)
#define SDP_MODCTRL_HASOUT_GET(x) (((uint32_t)(x) & SDP_MODCTRL_HASOUT_MASK) >> SDP_MODCTRL_HASOUT_SHIFT)

/*
 * DINSWP (RW)
 *
 * Decide whether the SDP byteswaps the input data (big-endian data);
 * When all bits are set, the data is assumed to be in the big-endian format
 */
#define SDP_MODCTRL_DINSWP_MASK (0x30U)
#define SDP_MODCTRL_DINSWP_SHIFT (4U)
#define SDP_MODCTRL_DINSWP_SET(x) (((uint32_t)(x) << SDP_MODCTRL_DINSWP_SHIFT) & SDP_MODCTRL_DINSWP_MASK)
#define SDP_MODCTRL_DINSWP_GET(x) (((uint32_t)(x) & SDP_MODCTRL_DINSWP_MASK) >> SDP_MODCTRL_DINSWP_SHIFT)

/*
 * DOUTSWP (RW)
 *
 * Decide whether the SDP byteswaps the output data (big-endian data); When all bits are set, the data is assumed to be in the big-endian format
 */
#define SDP_MODCTRL_DOUTSWP_MASK (0xCU)
#define SDP_MODCTRL_DOUTSWP_SHIFT (2U)
#define SDP_MODCTRL_DOUTSWP_SET(x) (((uint32_t)(x) << SDP_MODCTRL_DOUTSWP_SHIFT) & SDP_MODCTRL_DOUTSWP_MASK)
#define SDP_MODCTRL_DOUTSWP_GET(x) (((uint32_t)(x) & SDP_MODCTRL_DOUTSWP_MASK) >> SDP_MODCTRL_DOUTSWP_SHIFT)

/*
 * KEYSWP (RW)
 *
 * Decide whether the SDP byteswaps the Key (big-endian data).
 * When all bits are set, the data is assumed to be in the big-endian format
 */
#define SDP_MODCTRL_KEYSWP_MASK (0x3U)
#define SDP_MODCTRL_KEYSWP_SHIFT (0U)
#define SDP_MODCTRL_KEYSWP_SET(x) (((uint32_t)(x) << SDP_MODCTRL_KEYSWP_SHIFT) & SDP_MODCTRL_KEYSWP_MASK)
#define SDP_MODCTRL_KEYSWP_GET(x) (((uint32_t)(x) & SDP_MODCTRL_KEYSWP_MASK) >> SDP_MODCTRL_KEYSWP_SHIFT)

/* Bitfield definition for register: PKTCNT */
/*
 * CNTVAL (RO)
 *
 * This read-only field shows the current (instantaneous) value of the packet counter
 */
#define SDP_PKTCNT_CNTVAL_MASK (0xFF0000UL)
#define SDP_PKTCNT_CNTVAL_SHIFT (16U)
#define SDP_PKTCNT_CNTVAL_GET(x) (((uint32_t)(x) & SDP_PKTCNT_CNTVAL_MASK) >> SDP_PKTCNT_CNTVAL_SHIFT)

/*
 * CNTINCR (RW)
 *
 * The value written to this field is added to the spacket count.
 */
#define SDP_PKTCNT_CNTINCR_MASK (0xFFU)
#define SDP_PKTCNT_CNTINCR_SHIFT (0U)
#define SDP_PKTCNT_CNTINCR_SET(x) (((uint32_t)(x) << SDP_PKTCNT_CNTINCR_SHIFT) & SDP_PKTCNT_CNTINCR_MASK)
#define SDP_PKTCNT_CNTINCR_GET(x) (((uint32_t)(x) & SDP_PKTCNT_CNTINCR_MASK) >> SDP_PKTCNT_CNTINCR_SHIFT)

/* Bitfield definition for register: STA */
/*
 * TAG (RO)
 *
 * packet tag.
 */
#define SDP_STA_TAG_MASK (0xFF000000UL)
#define SDP_STA_TAG_SHIFT (24U)
#define SDP_STA_TAG_GET(x) (((uint32_t)(x) & SDP_STA_TAG_MASK) >> SDP_STA_TAG_SHIFT)

/*
 * IRQ (W1C)
 *
 * interrupt Request, requested when error happen, or when packet processing done, packet counter reach to zero.
 */
#define SDP_STA_IRQ_MASK (0x800000UL)
#define SDP_STA_IRQ_SHIFT (23U)
#define SDP_STA_IRQ_SET(x) (((uint32_t)(x) << SDP_STA_IRQ_SHIFT) & SDP_STA_IRQ_MASK)
#define SDP_STA_IRQ_GET(x) (((uint32_t)(x) & SDP_STA_IRQ_MASK) >> SDP_STA_IRQ_SHIFT)

/*
 * CHN1PKT0 (W1C)
 *
 * the chain buffer "chain" bit is "1", while packet counter is "0", now, waiting for new buffer data.
 */
#define SDP_STA_CHN1PKT0_MASK (0x100000UL)
#define SDP_STA_CHN1PKT0_SHIFT (20U)
#define SDP_STA_CHN1PKT0_SET(x) (((uint32_t)(x) << SDP_STA_CHN1PKT0_SHIFT) & SDP_STA_CHN1PKT0_MASK)
#define SDP_STA_CHN1PKT0_GET(x) (((uint32_t)(x) & SDP_STA_CHN1PKT0_MASK) >> SDP_STA_CHN1PKT0_SHIFT)

/*
 * AESBSY (RO)
 *
 * AES Busy
 */
#define SDP_STA_AESBSY_MASK (0x80000UL)
#define SDP_STA_AESBSY_SHIFT (19U)
#define SDP_STA_AESBSY_GET(x) (((uint32_t)(x) & SDP_STA_AESBSY_MASK) >> SDP_STA_AESBSY_SHIFT)

/*
 * HASBSY (RO)
 *
 * Hashing Busy
 */
#define SDP_STA_HASBSY_MASK (0x40000UL)
#define SDP_STA_HASBSY_SHIFT (18U)
#define SDP_STA_HASBSY_GET(x) (((uint32_t)(x) & SDP_STA_HASBSY_MASK) >> SDP_STA_HASBSY_SHIFT)

/*
 * PKTCNT0 (W1C)
 *
 * Packet Counter registers reachs to ZERO now.
 */
#define SDP_STA_PKTCNT0_MASK (0x20000UL)
#define SDP_STA_PKTCNT0_SHIFT (17U)
#define SDP_STA_PKTCNT0_SET(x) (((uint32_t)(x) << SDP_STA_PKTCNT0_SHIFT) & SDP_STA_PKTCNT0_MASK)
#define SDP_STA_PKTCNT0_GET(x) (((uint32_t)(x) & SDP_STA_PKTCNT0_MASK) >> SDP_STA_PKTCNT0_SHIFT)

/*
 * PKTDON (W1C)
 *
 * Packet processing done, will trigger this itnerrrupt when the "PKTINT" bit set in the packet control word.
 */
#define SDP_STA_PKTDON_MASK (0x10000UL)
#define SDP_STA_PKTDON_SHIFT (16U)
#define SDP_STA_PKTDON_SET(x) (((uint32_t)(x) << SDP_STA_PKTDON_SHIFT) & SDP_STA_PKTDON_MASK)
#define SDP_STA_PKTDON_GET(x) (((uint32_t)(x) & SDP_STA_PKTDON_MASK) >> SDP_STA_PKTDON_SHIFT)

/*
 * ERRSET (W1C)
 *
 * Working mode setup error.
 */
#define SDP_STA_ERRSET_MASK (0x20U)
#define SDP_STA_ERRSET_SHIFT (5U)
#define SDP_STA_ERRSET_SET(x) (((uint32_t)(x) << SDP_STA_ERRSET_SHIFT) & SDP_STA_ERRSET_MASK)
#define SDP_STA_ERRSET_GET(x) (((uint32_t)(x) & SDP_STA_ERRSET_MASK) >> SDP_STA_ERRSET_SHIFT)

/*
 * ERRPKT (W1C)
 *
 * Packet head access error, or status update error.
 */
#define SDP_STA_ERRPKT_MASK (0x10U)
#define SDP_STA_ERRPKT_SHIFT (4U)
#define SDP_STA_ERRPKT_SET(x) (((uint32_t)(x) << SDP_STA_ERRPKT_SHIFT) & SDP_STA_ERRPKT_MASK)
#define SDP_STA_ERRPKT_GET(x) (((uint32_t)(x) & SDP_STA_ERRPKT_MASK) >> SDP_STA_ERRPKT_SHIFT)

/*
 * ERRSRC (W1C)
 *
 * Source Buffer Access Error
 */
#define SDP_STA_ERRSRC_MASK (0x8U)
#define SDP_STA_ERRSRC_SHIFT (3U)
#define SDP_STA_ERRSRC_SET(x) (((uint32_t)(x) << SDP_STA_ERRSRC_SHIFT) & SDP_STA_ERRSRC_MASK)
#define SDP_STA_ERRSRC_GET(x) (((uint32_t)(x) & SDP_STA_ERRSRC_MASK) >> SDP_STA_ERRSRC_SHIFT)

/*
 * ERRDST (W1C)
 *
 * Destination Buffer Error
 */
#define SDP_STA_ERRDST_MASK (0x4U)
#define SDP_STA_ERRDST_SHIFT (2U)
#define SDP_STA_ERRDST_SET(x) (((uint32_t)(x) << SDP_STA_ERRDST_SHIFT) & SDP_STA_ERRDST_MASK)
#define SDP_STA_ERRDST_GET(x) (((uint32_t)(x) & SDP_STA_ERRDST_MASK) >> SDP_STA_ERRDST_SHIFT)

/*
 * ERRHAS (W1C)
 *
 * Hashing Check Error
 */
#define SDP_STA_ERRHAS_MASK (0x2U)
#define SDP_STA_ERRHAS_SHIFT (1U)
#define SDP_STA_ERRHAS_SET(x) (((uint32_t)(x) << SDP_STA_ERRHAS_SHIFT) & SDP_STA_ERRHAS_MASK)
#define SDP_STA_ERRHAS_GET(x) (((uint32_t)(x) & SDP_STA_ERRHAS_MASK) >> SDP_STA_ERRHAS_SHIFT)

/*
 * ERRCHAIN (W1C)
 *
 * buffer chain error happen when packet's CHAIN bit=0, but the Packet counter is still not zero.
 */
#define SDP_STA_ERRCHAIN_MASK (0x1U)
#define SDP_STA_ERRCHAIN_SHIFT (0U)
#define SDP_STA_ERRCHAIN_SET(x) (((uint32_t)(x) << SDP_STA_ERRCHAIN_SHIFT) & SDP_STA_ERRCHAIN_MASK)
#define SDP_STA_ERRCHAIN_GET(x) (((uint32_t)(x) & SDP_STA_ERRCHAIN_MASK) >> SDP_STA_ERRCHAIN_SHIFT)

/* Bitfield definition for register: KEYADDR */
/*
 * INDEX (RW)
 *
 * To write a key to the SDP KEY RAM, the software must first write the desired key index/subword to this register.
 * Key index pointer. The valid indices are 0-[number_keys].
 * In the SDP, there is a 16x128 key ram can store 16 AES128 keys or 8 AES 256 Keys; this index is for addressing the 16 128-bit key addresses.
 */
#define SDP_KEYADDR_INDEX_MASK (0xFF0000UL)
#define SDP_KEYADDR_INDEX_SHIFT (16U)
#define SDP_KEYADDR_INDEX_SET(x) (((uint32_t)(x) << SDP_KEYADDR_INDEX_SHIFT) & SDP_KEYADDR_INDEX_MASK)
#define SDP_KEYADDR_INDEX_GET(x) (((uint32_t)(x) & SDP_KEYADDR_INDEX_MASK) >> SDP_KEYADDR_INDEX_SHIFT)

/*
 * SUBWRD (RW)
 *
 * Key subword pointer. The valid indices are 0-3. After each write to the key data register, this field
 * increments; To write a key, the software must first write the desired key index/subword to this register.
 */
#define SDP_KEYADDR_SUBWRD_MASK (0x3U)
#define SDP_KEYADDR_SUBWRD_SHIFT (0U)
#define SDP_KEYADDR_SUBWRD_SET(x) (((uint32_t)(x) << SDP_KEYADDR_SUBWRD_SHIFT) & SDP_KEYADDR_SUBWRD_MASK)
#define SDP_KEYADDR_SUBWRD_GET(x) (((uint32_t)(x) & SDP_KEYADDR_SUBWRD_MASK) >> SDP_KEYADDR_SUBWRD_SHIFT)

/* Bitfield definition for register: KEYDAT */
/*
 * KEYDAT (RW)
 *
 * This register provides the write access to the key/key subword specified by the key index register.
 * Writing this location updates the selected subword for the key located at the index
 * specified by the key index register. The write also triggers the SUBWORD field of the
 * KEY register to increment to the next higher word in the key
 */
#define SDP_KEYDAT_KEYDAT_MASK (0xFFFFFFFFUL)
#define SDP_KEYDAT_KEYDAT_SHIFT (0U)
#define SDP_KEYDAT_KEYDAT_SET(x) (((uint32_t)(x) << SDP_KEYDAT_KEYDAT_SHIFT) & SDP_KEYDAT_KEYDAT_MASK)
#define SDP_KEYDAT_KEYDAT_GET(x) (((uint32_t)(x) & SDP_KEYDAT_KEYDAT_MASK) >> SDP_KEYDAT_KEYDAT_SHIFT)

/* Bitfield definition for register array: CIPHIV */
/*
 * CIPHIV (RW)
 *
 * cipher initialization vector.
 */
#define SDP_CIPHIV_CIPHIV_MASK (0xFFFFFFFFUL)
#define SDP_CIPHIV_CIPHIV_SHIFT (0U)
#define SDP_CIPHIV_CIPHIV_SET(x) (((uint32_t)(x) << SDP_CIPHIV_CIPHIV_SHIFT) & SDP_CIPHIV_CIPHIV_MASK)
#define SDP_CIPHIV_CIPHIV_GET(x) (((uint32_t)(x) & SDP_CIPHIV_CIPHIV_MASK) >> SDP_CIPHIV_CIPHIV_SHIFT)

/* Bitfield definition for register array: HASWRD */
/*
 * HASWRD (RW)
 *
 * Hash Data Word x - HASH result bit; will store the expected hash result bit if hash check enabled; when hash check is not enabled,  the hash engine will store the final hash result[31:0] here.
 * If CRC mode enabled, this work store the CRC expected result if the check enabled, or store the final calcuated CRC result.
 */
#define SDP_HASWRD_HASWRD_MASK (0xFFFFFFFFUL)
#define SDP_HASWRD_HASWRD_SHIFT (0U)
#define SDP_HASWRD_HASWRD_SET(x) (((uint32_t)(x) << SDP_HASWRD_HASWRD_SHIFT) & SDP_HASWRD_HASWRD_MASK)
#define SDP_HASWRD_HASWRD_GET(x) (((uint32_t)(x) & SDP_HASWRD_HASWRD_MASK) >> SDP_HASWRD_HASWRD_SHIFT)

/* Bitfield definition for register: CMDPTR */
/*
 * CMDPTR (RW)
 *
 * current command addresses the register points to the multiword
 * descriptor that is to be executed (or is currently being executed)
 */
#define SDP_CMDPTR_CMDPTR_MASK (0xFFFFFFFFUL)
#define SDP_CMDPTR_CMDPTR_SHIFT (0U)
#define SDP_CMDPTR_CMDPTR_SET(x) (((uint32_t)(x) << SDP_CMDPTR_CMDPTR_SHIFT) & SDP_CMDPTR_CMDPTR_MASK)
#define SDP_CMDPTR_CMDPTR_GET(x) (((uint32_t)(x) & SDP_CMDPTR_CMDPTR_MASK) >> SDP_CMDPTR_CMDPTR_SHIFT)

/* Bitfield definition for register: NPKTPTR */
/*
 * NPKTPTR (RW)
 *
 * Next Packet Address Pointer
 */
#define SDP_NPKTPTR_NPKTPTR_MASK (0xFFFFFFFFUL)
#define SDP_NPKTPTR_NPKTPTR_SHIFT (0U)
#define SDP_NPKTPTR_NPKTPTR_SET(x) (((uint32_t)(x) << SDP_NPKTPTR_NPKTPTR_SHIFT) & SDP_NPKTPTR_NPKTPTR_MASK)
#define SDP_NPKTPTR_NPKTPTR_GET(x) (((uint32_t)(x) & SDP_NPKTPTR_NPKTPTR_MASK) >> SDP_NPKTPTR_NPKTPTR_SHIFT)

/* Bitfield definition for register: PKTCTL */
/*
 * PKTTAG (RW)
 *
 * packet tag
 */
#define SDP_PKTCTL_PKTTAG_MASK (0xFF000000UL)
#define SDP_PKTCTL_PKTTAG_SHIFT (24U)
#define SDP_PKTCTL_PKTTAG_SET(x) (((uint32_t)(x) << SDP_PKTCTL_PKTTAG_SHIFT) & SDP_PKTCTL_PKTTAG_MASK)
#define SDP_PKTCTL_PKTTAG_GET(x) (((uint32_t)(x) & SDP_PKTCTL_PKTTAG_MASK) >> SDP_PKTCTL_PKTTAG_SHIFT)

/*
 * CIPHIV (RW)
 *
 * Load Initial Vector for the AES in this packet.
 */
#define SDP_PKTCTL_CIPHIV_MASK (0x40U)
#define SDP_PKTCTL_CIPHIV_SHIFT (6U)
#define SDP_PKTCTL_CIPHIV_SET(x) (((uint32_t)(x) << SDP_PKTCTL_CIPHIV_SHIFT) & SDP_PKTCTL_CIPHIV_MASK)
#define SDP_PKTCTL_CIPHIV_GET(x) (((uint32_t)(x) & SDP_PKTCTL_CIPHIV_MASK) >> SDP_PKTCTL_CIPHIV_SHIFT)

/*
 * HASFNL (RW)
 *
 * Hash Termination packet
 */
#define SDP_PKTCTL_HASFNL_MASK (0x20U)
#define SDP_PKTCTL_HASFNL_SHIFT (5U)
#define SDP_PKTCTL_HASFNL_SET(x) (((uint32_t)(x) << SDP_PKTCTL_HASFNL_SHIFT) & SDP_PKTCTL_HASFNL_MASK)
#define SDP_PKTCTL_HASFNL_GET(x) (((uint32_t)(x) & SDP_PKTCTL_HASFNL_MASK) >> SDP_PKTCTL_HASFNL_SHIFT)

/*
 * HASINI (RW)
 *
 * Hash Initialization packat
 */
#define SDP_PKTCTL_HASINI_MASK (0x10U)
#define SDP_PKTCTL_HASINI_SHIFT (4U)
#define SDP_PKTCTL_HASINI_SET(x) (((uint32_t)(x) << SDP_PKTCTL_HASINI_SHIFT) & SDP_PKTCTL_HASINI_MASK)
#define SDP_PKTCTL_HASINI_GET(x) (((uint32_t)(x) & SDP_PKTCTL_HASINI_MASK) >> SDP_PKTCTL_HASINI_SHIFT)

/*
 * CHAIN (RW)
 *
 * whether the next command pointer register must be loaded into the channel's current descriptor
 * pointer.
 */
#define SDP_PKTCTL_CHAIN_MASK (0x8U)
#define SDP_PKTCTL_CHAIN_SHIFT (3U)
#define SDP_PKTCTL_CHAIN_SET(x) (((uint32_t)(x) << SDP_PKTCTL_CHAIN_SHIFT) & SDP_PKTCTL_CHAIN_MASK)
#define SDP_PKTCTL_CHAIN_GET(x) (((uint32_t)(x) & SDP_PKTCTL_CHAIN_MASK) >> SDP_PKTCTL_CHAIN_SHIFT)

/*
 * DCRSEMA (RW)
 *
 * whether the channel's semaphore must be decremented at the end of the current operation.
 * When the semaphore reaches a value of zero, no more operations are issued from the channel.
 */
#define SDP_PKTCTL_DCRSEMA_MASK (0x4U)
#define SDP_PKTCTL_DCRSEMA_SHIFT (2U)
#define SDP_PKTCTL_DCRSEMA_SET(x) (((uint32_t)(x) << SDP_PKTCTL_DCRSEMA_SHIFT) & SDP_PKTCTL_DCRSEMA_MASK)
#define SDP_PKTCTL_DCRSEMA_GET(x) (((uint32_t)(x) & SDP_PKTCTL_DCRSEMA_MASK) >> SDP_PKTCTL_DCRSEMA_SHIFT)

/*
 * PKTINT (RW)
 *
 * Reflects whether the channel must issue an interrupt upon the completion of the packet
 */
#define SDP_PKTCTL_PKTINT_MASK (0x2U)
#define SDP_PKTCTL_PKTINT_SHIFT (1U)
#define SDP_PKTCTL_PKTINT_SET(x) (((uint32_t)(x) << SDP_PKTCTL_PKTINT_SHIFT) & SDP_PKTCTL_PKTINT_MASK)
#define SDP_PKTCTL_PKTINT_GET(x) (((uint32_t)(x) & SDP_PKTCTL_PKTINT_MASK) >> SDP_PKTCTL_PKTINT_SHIFT)

/* Bitfield definition for register: PKTSRC */
/*
 * PKTSRC (RW)
 *
 * Packet Memory Source Address
 */
#define SDP_PKTSRC_PKTSRC_MASK (0xFFFFFFFFUL)
#define SDP_PKTSRC_PKTSRC_SHIFT (0U)
#define SDP_PKTSRC_PKTSRC_SET(x) (((uint32_t)(x) << SDP_PKTSRC_PKTSRC_SHIFT) & SDP_PKTSRC_PKTSRC_MASK)
#define SDP_PKTSRC_PKTSRC_GET(x) (((uint32_t)(x) & SDP_PKTSRC_PKTSRC_MASK) >> SDP_PKTSRC_PKTSRC_SHIFT)

/* Bitfield definition for register: PKTDST */
/*
 * PKTDST (RW)
 *
 * Packet Memory Destination Address
 */
#define SDP_PKTDST_PKTDST_MASK (0xFFFFFFFFUL)
#define SDP_PKTDST_PKTDST_SHIFT (0U)
#define SDP_PKTDST_PKTDST_SET(x) (((uint32_t)(x) << SDP_PKTDST_PKTDST_SHIFT) & SDP_PKTDST_PKTDST_MASK)
#define SDP_PKTDST_PKTDST_GET(x) (((uint32_t)(x) & SDP_PKTDST_PKTDST_MASK) >> SDP_PKTDST_PKTDST_SHIFT)

/* Bitfield definition for register: PKTBUF */
/*
 * PKTBUF (RW)
 *
 */
#define SDP_PKTBUF_PKTBUF_MASK (0xFFFFFFFFUL)
#define SDP_PKTBUF_PKTBUF_SHIFT (0U)
#define SDP_PKTBUF_PKTBUF_SET(x) (((uint32_t)(x) << SDP_PKTBUF_PKTBUF_SHIFT) & SDP_PKTBUF_PKTBUF_MASK)
#define SDP_PKTBUF_PKTBUF_GET(x) (((uint32_t)(x) & SDP_PKTBUF_PKTBUF_MASK) >> SDP_PKTBUF_PKTBUF_SHIFT)



/* CIPHIV register group index macro definition */
#define SDP_CIPHIV_CIPHIV0 (0UL)
#define SDP_CIPHIV_CIPHIV1 (1UL)
#define SDP_CIPHIV_CIPHIV2 (2UL)
#define SDP_CIPHIV_CIPHIV3 (3UL)

/* HASWRD register group index macro definition */
#define SDP_HASWRD_HASWRD0 (0UL)
#define SDP_HASWRD_HASWRD1 (1UL)
#define SDP_HASWRD_HASWRD2 (2UL)
#define SDP_HASWRD_HASWRD3 (3UL)
#define SDP_HASWRD_HASWRD4 (4UL)
#define SDP_HASWRD_HASWRD5 (5UL)
#define SDP_HASWRD_HASWRD6 (6UL)
#define SDP_HASWRD_HASWRD7 (7UL)


#endif /* HPM_SDP_H */
