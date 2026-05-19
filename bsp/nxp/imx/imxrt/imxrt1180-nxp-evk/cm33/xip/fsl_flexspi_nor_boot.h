/*
 * Copyright 2021-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __FLEXSPI_NOR_BOOT_H__
#define __FLEXSPI_NOR_BOOT_H__

#include "fsl_common.h"

/*************************************
 *  Container
 *************************************/
/* Container header */
#define CNT_TAG_HEADER 0x87
#define CNT_SIZE       (uint16_t)(sizeof(container))
#define CNT_VERSION    0x00
#define CNT_NUM_IMG    1
#define CNT_FUSE_VER   0
#define CNT_SW_VER     0
#define CNT_FLAGS      0x00000000 // Container not authenticated

#define IMG_FLAGS 0x00000213      // Non-encrypted, SHA512, CM33, Executable

#define SGNBK_TAG     0x90
#define SGNBK_SIZE    (uint16_t)(sizeof(sign_block))
#define SGNBK_VERSION 0x00

typedef struct __attribute__((packed)) _cnt_hdr_
{
    uint8_t version;
    uint16_t length;
    uint8_t tag;

    uint32_t flags;

    uint16_t sw_ver;
    uint8_t fuse_ver;
    uint8_t num_images;

    uint16_t sign_blk_offset;
    uint16_t reserved1;
} cnt_hdr;

typedef struct __attribute__((packed)) _img_entry_
{
    uint32_t offset;
    uint32_t size;
    uint32_t load_addr;
    uint32_t reserved1;
    uint32_t entry;
    uint32_t reserved2;
    uint32_t flags;
    uint32_t metadata;
    uint8_t hash[64];
    uint8_t iv[32];
} image_entry;

typedef struct __attribute__((packed)) _sign_block_
{
    uint8_t version;
    uint16_t length;
    uint8_t tag;

    uint16_t cert_offset;
    uint16_t srk_offset;
    uint16_t sign_offset;
    uint16_t blob_offset;
    uint32_t reserved1;
    uint8_t data[0];
} sign_block;

typedef struct __attribute__((packed)) _container_
{
    cnt_hdr hdr;
    image_entry array[CNT_NUM_IMG];
    sign_block sign_block;
} container;

/* Set resume entry */
#if defined(__MCUXPRESSO)
extern uint32_t app_image_offset[];
extern uint32_t _image_size[];
extern uint32_t _image_loadaddr[];
extern uint32_t ResetISR[];
#define IMAGE_OFFSET        ((uint32_t)app_image_offset)
#define IMAGE_SIZE          ((uint32_t)_image_size)
#define IMAGE_LOAD_ADDRESS  ((uint32_t)_image_loadaddr)
#define IMAGE_ENTRY_ADDRESS ((uint32_t)ResetISR)

#elif defined(__ICCARM__)
#pragma section = "RO"
extern uint32_t __CONTAINER_IMG_OFFSET[];
extern uint32_t __CONTAINER_IMG_LOAD_ADDR[];
extern uint32_t __CONTAINER_IMG_ENTRY_ADDR[];
#define IMAGE_OFFSET        ((uint32_t)__CONTAINER_IMG_OFFSET)
#define IMAGE_SIZE          ((uint32_t)__section_size("RO"))
#define IMAGE_LOAD_ADDRESS  ((uint32_t)__CONTAINER_IMG_LOAD_ADDR)
#define IMAGE_ENTRY_ADDRESS ((uint32_t)__CONTAINER_IMG_ENTRY_ADDR)

#elif defined(__CC_ARM) || defined(__ARMCC_VERSION)
extern uint32_t Image$$ER_m_container_image_offset$$ZI$$Base[];
extern uint32_t Image$$VECTOR_ROM$$Base[];
extern uint32_t Load$$LR$$LR_m_text$$Length[];
#define IMAGE_OFFSET        ((uint32_t)Image$$ER_m_container_image_offset$$ZI$$Base)
#define IMAGE_SIZE          ((uint32_t)Load$$LR$$LR_m_text$$Length)
#define IMAGE_LOAD_ADDRESS  ((uint32_t)Image$$VECTOR_ROM$$Base)
#define IMAGE_ENTRY_ADDRESS ((uint32_t)Image$$VECTOR_ROM$$Base)

#elif defined(__GNUC__)
extern uint32_t __CONTAINER_IMG_OFFSET[];
extern uint32_t __CONTAINER_IMG_SIZE[];
extern uint32_t __VECTOR_TABLE[];
#define IMAGE_OFFSET        ((uint32_t)__CONTAINER_IMG_OFFSET)
#define IMAGE_SIZE          ((uint32_t)__CONTAINER_IMG_SIZE)
#define IMAGE_LOAD_ADDRESS  ((uint32_t)__VECTOR_TABLE)
#define IMAGE_ENTRY_ADDRESS ((uint32_t)__VECTOR_TABLE)
#endif

#endif /* __FLEXSPI_NOR_BOOT_H__ */
