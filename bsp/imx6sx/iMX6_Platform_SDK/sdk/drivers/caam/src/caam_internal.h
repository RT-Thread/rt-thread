/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
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

#ifndef __CAAM_INTERNAL_H__
#define	__CAAM_INTERNAL_H__

/* 4kbyte pages */
#define SEC_MEM_PAGE0       CAAM_SEC_RAM_START_ADDR
#define SEC_MEM_PAGE1       (CAAM_SEC_RAM_START_ADDR + 0x1000)
#define SEC_MEM_PAGE2       (CAAM_SEC_RAM_START_ADDR + 0x2000)
#define SEC_MEM_PAGE3       (CAAM_SEC_RAM_START_ADDR + 0x3000)

/* Configuration and special key registers */
#define CAAM_MCFGR          CAAM_BASE_ADDR + 0x0004
#define CAAM_SCFGR          CAAM_BASE_ADDR + 0x000c
#define CAAM_JR0MIDR        CAAM_BASE_ADDR + 0x0010
#define CAAM_JR1MIDR        CAAM_BASE_ADDR + 0x0018
#define CAAM_DECORR         CAAM_BASE_ADDR + 0x009c
#define CAAM_DECO0MID       CAAM_BASE_ADDR + 0x00a0
#define CAAM_DAR            CAAM_BASE_ADDR + 0x0120
#define CAAM_DRR            CAAM_BASE_ADDR + 0x0124
#define CAAM_JDKEKR         CAAM_BASE_ADDR + 0x0400
#define CAAM_TDKEKR         CAAM_BASE_ADDR + 0x0420
#define CAAM_TDSKR          CAAM_BASE_ADDR + 0x0440
#define CAAM_SKNR           CAAM_BASE_ADDR + 0x04e0
#define CAAM_SMSTA          CAAM_BASE_ADDR + 0x0FB4
#define CAAM_STA            CAAM_BASE_ADDR + 0x0FD4
#define CAAM_SMPO_0         CAAM_BASE_ADDR + 0x1FBC

/* RNG registers */
#define CAAM_RTMCTL         CAAM_BASE_ADDR + 0x0600
#define CAAM_RTSDCTL        CAAM_BASE_ADDR + 0x0610
#define CAAM_RTFRQMIN       CAAM_BASE_ADDR + 0x0618
#define CAAM_RTFRQMAX       CAAM_BASE_ADDR + 0x061C
#define CAAM_RDSTA          CAAM_BASE_ADDR + 0x06C0

/* Job Ring 0 registers */
#define CAAM_IRBAR0         CAAM_BASE_ADDR + 0x1004
#define CAAM_IRSR0          CAAM_BASE_ADDR + 0x100c
#define CAAM_IRSAR0         CAAM_BASE_ADDR + 0x1014
#define CAAM_IRJAR0         CAAM_BASE_ADDR + 0x101c
#define CAAM_ORBAR0         CAAM_BASE_ADDR + 0x1024
#define CAAM_ORSR0          CAAM_BASE_ADDR + 0x102c
#define CAAM_ORJRR0         CAAM_BASE_ADDR + 0x1034
#define CAAM_ORSFR0         CAAM_BASE_ADDR + 0x103c
#define CAAM_JRSTAR0        CAAM_BASE_ADDR + 0x1044
#define CAAM_JRINTR0        CAAM_BASE_ADDR + 0x104c
#define CAAM_JRCFGR0_MS     CAAM_BASE_ADDR + 0x1050
#define CAAM_JRCFGR0_LS     CAAM_BASE_ADDR + 0x1054
#define CAAM_IRRIR0         CAAM_BASE_ADDR + 0x105c
#define CAAM_ORWIR0         CAAM_BASE_ADDR + 0x1064
#define CAAM_JRCR0          CAAM_BASE_ADDR + 0x106c
#define CAAM_SMCJR0         CAAM_BASE_ADDR + 0x10f4
#define CAAM_SMCSJR0        CAAM_BASE_ADDR + 0x10fc
#define CAAM_SMAPJR0(y)     (CAAM_BASE_ADDR + 0x1104 + y*16)
#define CAAM_SMAG2JR0(y)    (CAAM_BASE_ADDR + 0x1108 + y*16)
#define CAAM_SMAG1JR0(y)    (CAAM_BASE_ADDR + 0x110C + y*16)
#define CAAM_SMAPJR0_PRTN1  CAAM_BASE_ADDR + 0x1114
#define CAAM_SMAG2JR0_PRTN1 CAAM_BASE_ADDR + 0x1118
#define CAAM_SMAG1JR0_PRTN1 CAAM_BASE_ADDR + 0x111c
#define CAAM_SMPO           CAAM_BASE_ADDR + 0x1fbc

#define JRCFG_LS_IMSK       0x00000001      /* Interrupt Mask */
#define JR_MID              2               /* Matches ROM configuration */
#define KS_G1               (1 << JR_MID)   /* CAAM only */
#define PERM                0x0000B008      /* Clear on release,
                                             * lock SMAP
                                             * lock SMAG
                                             * group 1 Blob
                                             */    

#define CMD_PAGE_ALLOC      0x1
#define CMD_PAGE_DEALLOC    0x2
#define CMD_PART_DEALLOC    0x3
#define CMD_INQUIRY         0x5
#define PAGE(x)             (x << 16)
#define PARTITION(x)        (x << 8)

#define SMCSJR_AERR         (3 << 12)
#define SMCSJR_CERR         (3 << 14)
#define CMD_COMPLETE        (3 << 14)

#define SMCSJR_PO           (3 << 6)
#define PAGE_AVAILABLE      0
#define PAGE_OWNED          (3 << 6)

#define PARTITION_OWNER(x)  (0x3 << (x*2))

#define CAAM_BUSY_MASK      0x00000001      /* BUSY from status reg */
#define CAAM_IDLE_MASK      0x00000002      /* IDLE from status reg */

#define JOB_RING_ENTRIES    1
#define JOB_RING_STS        (0xF << 28)

/** OSC_DIV in RNG trim fuses */
#define RNG_TRIM_OSC_DIV    0
/** ENT_DLY multiplier in RNG trim fuses */
#define RNG_TRIM_ENT_DLY    200*4

#define RTMCTL_PGM  (1 << 16)
#define RTMCTL_ERR  (1 << 12)
#define RDSTA_IF0   1
#define RDSTA_SKVN  (1 << 30)

typedef enum {
    PAGE_0,
    PAGE_1,
    PAGE_2,
    PAGE_3,
} page_num_e;

typedef enum {
    PARTITION_0,
    PARTITION_1,
    PARTITION_2,
    PARTITION_3,
    PARTITION_4,
    PARTITION_5,
    PARTITION_6,
    PARTITION_7,
} partition_num_e;

/*****************************************
 *----- Blob decapsulate descriptor -----*
 *****************************************/
/* 1. Header
 *
 *  1011 0000 1000 0000 0000 0000 0000 1001
 *  |||| |                             ||||
 *  ++++-+-- Header                    ++++-- 9 words in descriptor
 */  
#define DECAP_BLOB_DESC1 0xB0800009

/* 2. Load command KEY 2 immediate
 *  
 *  0001 0100 1100 0000 0000 1100 0000 1000
 *  |||| |||  |||| |||| |||| |||| |||| ||||
 *  |||| |||  |||| |||| |||| |||| ++++-++++-- Length 
 *  |||| |||  |||| |||| ++++-++++-- Offset
 *  |||| |||  |+++-++++-- DST (Destination Register) Key2
 *  |||| |||  +-- IMM (Immediate flag)
 *  |||| |++-- class 2
 *  ++++-+-- Load command
 */
#define DECAP_BLOB_DESC2 0x14C00C08

/* 3. 8 bytes for load command above - aad data
 *
 *  0000 0000 0001 0000 0101 0101 0110 0110
 *  |||| |||| |||| |||| |||| |||| |||| ||||
 *  |||| |||| |||| |||| |||| |||| ++++-++++-- CCM Mode 
 *  |||| |||| |||| |||| ++++-++++-- AES
 *  |||| |||| ++++-++++-- Length
 *  ++++-++++-- Flag
 */
#define DECAP_BLOB_DESC3 0x00105566
#define DECAP_BLOB_DESC4 0x00000000

/* 5. SEQ In Ptr
 *  
 *  1111 0000 0000 0000 0000 0000 0100 0000
 *  |||| |              |||| |||| |||| ||||
 *  |||| |              ++++-++++-++++-++++-- Length in bytes (64) 
 *  ++++-+-- Seq In Ptr
 */
#define DECAP_BLOB_DESC5 0xF0000040

/* 6. Pointer for above SEQ In ptr command */
/* Address is provided during run time */
#define DECAP_BLOB_DESC6 0x00000000 

/* 7. SEQ Out Ptr
 *  
 *  1111 1000 0000 0000 0000 0000 0001 0000
 *  |||| |              |||| |||| |||| ||||
 *  |||| |              ++++-++++-++++-++++-- Length in bytes (16) 
 *  ++++-+-- Seq In Ptr
 */
#define DECAP_BLOB_DESC7 0xF8000010

/* 8. Pointer for above SEQ Out ptr command */
/* Address could be changed during run time */
#define DECAP_BLOB_DESC8 SEC_MEM_PAGE1

/* 9. Protocol 
 *  
 *  1000 0110 0000 1101 0000 0000 0000 1000
 *  |||| |||| |||| |||| |||| |||| |||| ||||
 *  |||| |||| |||| |||| ++++-++++-++++-++++-- Proto Info = sec mem blob
 *  |||| |||| ++++-++++-- Protocol ID = Blob
 *  |||| |+++-- Optype - decapsulation protocol
 *  ++++-+-- Seq In Ptr
 */
#define DECAP_BLOB_DESC9 0x860D0008

/*****************************************
 *----- Blob encapsulate descriptor -----*
 *****************************************/
/* Blob Header
 *
 *  1011 0000 1000 0000 0000 0000 0000 1001
 *  |||| |                             |
 *  ++++-+-- Header                    +-- 9 words in descriptor
 */  
#define ENCAP_BLOB_DESC1  0xB0800009

/* 2. Load command KEY 2 immediate
 *  
 *  0001 0100 1100 0000 0000 1100 0000 1000
 *  |||| |||  |||| |||| |||| |||| |||| ||||
 *  |||| |||  |||| |||| |||| |||| ++++-++++-- Length 
 *  |||| |||  |||| |||| ++++-++++-- Offset
 *  |||| |||  |+++-++++-- DST (Destination Register) Key2
 *  |||| |||  +-- IMM (Immediate flag)
 *  |||| |++-- class 2
 *  ++++-+-- Load command
 */
#define ENCAP_BLOB_DESC2 0x14C00C08

/* 3. 8 bytes for load command above - aad data
 *
 *  0000 0000 0001 0000 0101 0101 0110 0110
 *  |||| |||| |||| |||| |||| |||| |||| ||||
 *  |||| |||| |||| |||| |||| |||| ++++-++++-- CCM Mode 
 *  |||| |||| |||| |||| ++++-++++-- AES
 *  |||| |||| ++++-++++-- Length
 *  ++++-++++-- Flag
 */
#define ENCAP_BLOB_DESC3 0x00105566
#define ENCAP_BLOB_DESC4 0x00000000

/* 5. SEQ In Ptr
 *  
 *  1111 0000 0000 0000 0000 0000 0001 0000
 *  |||| |              |||| |||| |||| ||||
 *  |||| |              ++++-++++-++++-++++-- Length in bytes (16) 
 *  ++++-+-- Seq In Ptr
 */
#define ENCAP_BLOB_DESC5 0xF0000010

/* 6. Pointer for above SEQ In ptr command */
/* Address could be changed during run time */
#define ENCAP_BLOB_DESC6 SEC_MEM_PAGE1

/* 7. SEQ Out Ptr
 *  
 *  1111 1000 0000 0000 0000 0000 0100 0000
 *  |||| |              |||| |||| |||| ||||
 *  |||| |              ++++-++++-++++-++++-- Length in bytes (64) 
 *  ++++-+-- Seq Out Ptr
 */
#define ENCAP_BLOB_DESC7  0xF8000040

/* 8. Pointer for above SEQ Out ptr command */
/* Address is provided during run time */
#define ENCAP_BLOB_DESC8  0x00000000

/* 9. Protocol 
 *  
 *  1000 0111 0000 1101 0000 0000 0000 1000
 *  |||| |||| |||| |||| |||| |||| |||| ||||
 *  |||| |||| |||| |||| ++++-++++-++++-++++-- Proto Info = sec mem blob
 *  |||| |||| ++++-++++-- Protocol ID = Blob
 *  |||| |+++-- Optype - encapsulation protocol
 *  ++++-+-- Seq In Ptr
 */
#define ENCAP_BLOB_DESC9  0x870D0008

/****************************************
 *----- Data encryption descriptor -----*
 ****************************************/
/* 1. Header
 *
 * 1011 0000 1000 0000 0000 0000 0000 1000
 * |||| | | ||||
 * ++++-+-- Header +-++++-- 8 words in descriptor
 */
#define ENCRYPT_DESC1 0xB0800008

/* 2. Load AES-128 key from secure memory
 *
 * 0010 0010 0000 0000 0000 0000 0001 0000
 * |||| | | |||| |||| |||| ||||
 * |||| | | ++++-++++-++++-++++-- 16 bytes
 * |||| | +-- Load FIFO with data for Class 1 CHA
 * ++++-+-- FIFO Load
 */
#define ENCRYPT_DESC2 0x02200010

/* 3. Pointer to key data in secure memory */
/* Address is provided during run time */
#define ENCRYPT_DESC3 0x00000000

/* 4. Algorith Operation - Decrypt with ECB mode
 *
 * 1000 0010 0001 0000 0000 0010 0000 1101
 * |||| |||| |||| |||| |||| |||| |||| ||||
 * |||| |||| |||| |||| |||| |||| |||| |||+-- Encrypt
 * |||| |||| |||| |||| |||| |||| |||| ++-- Initialize/Finalize
 * |||| |||| |||| |||| ---+-++++-++++-- ECB mode
 * |||| |||| ++++-++++-- AES
 * |||| |+++-- Optype: Class 1 algorithm
 * ++++-+-- ALGORITHM OP.
 */
#define ENCRYPT_DESC4 0x8210020D

/* 5. Load 16 bytes of message data
 *
 * 0010 0010 0001 0010 0000 0000 0001 0000
 * |||| |||| |||| |||| |||| |||| |||| ||||
 * |||| |||| |||| |||| |||| |||| |||| ||||
 * |||| |||| |||| |||| |||| |||| |||| ||||
 * |||| |||| |||| |||| ++++-++++-++++-++++-- Msg Length = 16Bytes
 * |||| |||| ||++-++++-- Input data type: Msg data LC1=1
 * |||| |||| |+-- EXT: No extended length
 * |||| |||| +-- IMM: data begins at the location pointed to by the next word
 * |||| |||++-SGT/VLF: FIFO Load-Pointer points to actual data
 * |||| |++-- Load FIFO with data for Class 1 CHA
 * ++++-+-- FIFO Load
 */
#define ENCRYPT_DESC5 0x22120010

/* 6. Pointer to plain text test vector message */
/* Address is provided during run time */
#define ENCRYPT_DESC6 0x00000000

/* 7. FIFO STORE - encrypted result.
 * 0110 0000 0011 0000 0000 0000 0001 0000
 * |||| |||| |||| |||| |||| |||| |||| ||||
 * |||| |||| |||| |||| ++++-++++-++++-++++-- Length = 16Bytes
 * |||| |||| ||++-++++-- Output data type: Msg Data
 * |||| |||| |+-- EXT: No extended length
 * |||| |||| +-- CONT: No continue
 * |||| |||+-- SGT/VLF: Pointer points to actual data
 * |||| |++-- AUX: None
 * ++++-+-- FIFO Store
 */
#define ENCRYPT_DESC7 0x60300010

/* 8. Pointer to ciphered text buffer */
/* Address is provided during run time */
#define ENCRYPT_DESC8 0x00000000

/*********************************************************************
 *----- Descriptor to instantiate RNG in non-deterministic mode -----*
 *********************************************************************/
// Header
#define RNG_INST_DESC1 0xB0800009
// Class 1 context load for personalization string, 8bytes
#define RNG_INST_DESC2 0x12A00008
// 8 bytes of personalization string (8-byte UID + zeros)
#define RNG_INST_DESC3 0x01020304
#define RNG_INST_DESC4 0x05060708
// Instantiate State Handle 0 using entropy from TRNG
// without prediction resistance
#define RNG_INST_DESC5 0x82500404
// Wait for Class 1 done
#define RNG_INST_DESC6 0xA2000001
// Immediate 4 byte load to clear written register
#define RNG_INST_DESC7 0x10880004
// Clear primary mode bit
#define RNG_INST_DESC8 0x00000001
// Generate secure keys without prediction resistance
#define RNG_INST_DESC9 0x82501000

#endif /* __CAAM_INTERNAL_H__ */
