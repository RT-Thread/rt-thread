/**
 * @file hal_sec_hash.c
 * @brief
 *
 * Copyright 2019-2030 Bouffalolab team
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 */
#include "hal_sec_hash.h"
#include "bl808_sec_eng.h"

void SEC_SHA_IRQHandler(void);

static sec_hash_device_t sec_hashx_device[SEC_HASH_MAX_INDEX] = {
    0
};

static SEC_Eng_SHA256_Ctx shaCtx;

static SEC_Eng_SHA256_Ctx sha256Ctx;

/**
 * @brief
 *
 * @param dev
 * @param oflag
 * @return int
 */
int sec_hash_open(struct device *dev, uint16_t oflag)
{
    sec_hash_device_t *sec_hash_device = (sec_hash_device_t *)dev;
    int ret = 0;

    switch (sec_hash_device->type) {
        case SEC_HASH_SHA1:
            ret = -1;
            break;

        case SEC_HASH_SHA224:
            Sec_Eng_SHA256_Init(&shaCtx, SEC_ENG_SHA_ID0, SEC_ENG_SHA224, sec_hash_device->shaBuf, sec_hash_device->shaPadding);
            Sec_Eng_SHA_Start(SEC_ENG_SHA_ID0);
            break;

        case SEC_HASH_SHA256:
            Sec_Eng_SHA256_Init(&shaCtx, SEC_ENG_SHA_ID0, SEC_ENG_SHA256, sec_hash_device->shaBuf, sec_hash_device->shaPadding);
            Sec_Eng_SHA_Start(SEC_ENG_SHA_ID0);
            break;

        case SEC_HASH_SHA384:
        case SEC_HASH_SHA512:
            ret = -1;
            break;

        default:
            ret = -1;
            break;
    }

    return ret;
}
/**
 * @brief
 *
 * @param dev
 * @return int
 */
int sec_hash_close(struct device *dev)
{
    //sec_hash_device_t *sec_hash_device = (sec_hash_device_t *)dev;
    //memset(sec_hash_device, 0, sizeof(sec_hash_device_t)); //will cause crash
    return 0;
}
/**
 * @brief
 *
 * @param dev
 * @param cmd
 * @param args
 * @return int
 */
int sec_hash_control(struct device *dev, int cmd, void *args)
{
    return 0;
}

/**
 * @brief
 *
 * @param dev
 * @param pos
 * @param buffer
 * @param size
 * @return int
 */
int sec_hash_write(struct device *dev, uint32_t pos, const void *buffer, uint32_t size)
{
    sec_hash_device_t *sec_hash_device = (sec_hash_device_t *)dev;
    int ret = 0;

    switch (sec_hash_device->type) {
        case SEC_HASH_SHA1:
            ret = -1;
            break;

        case SEC_HASH_SHA224:
            Sec_Eng_SHA256_Update(&shaCtx, SEC_ENG_SHA_ID0, (uint8_t *)buffer, size);
            break;

        case SEC_HASH_SHA256:
            Sec_Eng_SHA256_Update(&shaCtx, SEC_ENG_SHA_ID0, (uint8_t *)buffer, size);
            break;

        case SEC_HASH_SHA384:
        case SEC_HASH_SHA512:
            ret = -1;
            break;

        default:
            ret = -1;
            break;
    }

    return ret;
}

/**
 * @brief
 *
 * @param dev
 * @param pos
 * @param buffer
 * @param size
 * @return int
 */
int sec_hash_read(struct device *dev, uint32_t pos, void *buffer, uint32_t size)
{
    sec_hash_device_t *sec_hash_device = (sec_hash_device_t *)dev;
    int ret = 0;

    switch (sec_hash_device->type) {
        case SEC_HASH_SHA1:
            ret = -1;
            break;

        case SEC_HASH_SHA224:
            Sec_Eng_SHA256_Finish(&shaCtx, SEC_ENG_SHA_ID0, (uint8_t *)buffer);
            ret = 28;
            break;

        case SEC_HASH_SHA256:
            Sec_Eng_SHA256_Finish(&shaCtx, SEC_ENG_SHA_ID0, (uint8_t *)buffer);
            ret = 32;
            break;

        case SEC_HASH_SHA384:
        case SEC_HASH_SHA512:
            ret = -1;
            break;

        default:
            ret = -1;
            break;
    }

    return ret;
}

/**
 * @brief
 *
 * @param handle
 * @param type
 * @return int
 */
int sec_hash_init(sec_hash_handle_t *handle, uint8_t type)
{
    int ret = 0;

    switch (type) {
        case SEC_HASH_SHA1:
            ret = -1;
            break;

        case SEC_HASH_SHA224:
            handle->type = type;
            Sec_Eng_SHA256_Init(&sha256Ctx, SEC_ENG_SHA_ID0, SEC_ENG_SHA224, handle->shaBuf, handle->shaPadding);
            Sec_Eng_SHA_Start(SEC_ENG_SHA_ID0);
            break;

        case SEC_HASH_SHA256:
            handle->type = type;
            Sec_Eng_SHA256_Init(&sha256Ctx, SEC_ENG_SHA_ID0, SEC_ENG_SHA256, handle->shaBuf, handle->shaPadding);
            Sec_Eng_SHA_Start(SEC_ENG_SHA_ID0);
            break;

        case SEC_HASH_SHA384:
        case SEC_HASH_SHA512:
            ret = -1;
            break;

        default:
            ret = -1;
            break;
    }

    return ret;
}
/**
 * @brief
 *
 * @param handle
 * @return int
 */
int sec_hash_deinit(sec_hash_handle_t *handle)
{
    memset(handle->shaBuf, 0, sizeof(handle->shaBuf));
    memset(handle->shaPadding, 0, sizeof(handle->shaPadding));

    return 0;
}

/**
 * @brief
 *
 * @param handle
 * @param buffer
 * @param size
 * @return int
 */
int sec_hash_update(sec_hash_handle_t *handle, const void *buffer, uint32_t size)
{
    int ret = 0;

    switch (handle->type) {
        case SEC_HASH_SHA1:
            ret = -1;
            break;

        case SEC_HASH_SHA224:
            Sec_Eng_SHA256_Update(&sha256Ctx, SEC_ENG_SHA_ID0, (uint8_t *)buffer, size);
            break;

        case SEC_HASH_SHA256:
            Sec_Eng_SHA256_Update(&sha256Ctx, SEC_ENG_SHA_ID0, (uint8_t *)buffer, size);
            break;

        case SEC_HASH_SHA384:
        case SEC_HASH_SHA512:
            ret = -1;
            break;

        default:
            ret = -1;
            break;
    }

    return ret;
}

/**
 * @brief
 *
 * @param handle
 * @param buffer
 * @return int
 */
int sec_hash_finish(sec_hash_handle_t *handle, void *buffer)
{
    int ret = 0;

    switch (handle->type) {
        case SEC_HASH_SHA1:
            ret = -1;
            break;

        case SEC_HASH_SHA224:
            Sec_Eng_SHA256_Finish(&sha256Ctx, SEC_ENG_SHA_ID0, (uint8_t *)buffer);
            ret = 28;
            break;

        case SEC_HASH_SHA256:
            Sec_Eng_SHA256_Finish(&sha256Ctx, SEC_ENG_SHA_ID0, (uint8_t *)buffer);
            ret = 32;
            break;

        case SEC_HASH_SHA384:
        case SEC_HASH_SHA512:
            ret = -1;
            break;

        default:
            ret = -1;
            break;
    }

    return ret;
}

/**
 * @brief
 *
 * @param index
 * @param type
 * @param name
 * @param flag
 * @return int
 */
static int sec_hash_sha_register(enum sec_hash_index_type index, enum sec_hash_type type, const char *name)
{
    struct device *dev;

    if (SEC_HASH_MAX_INDEX == 0) {
        return -DEVICE_EINVAL;
    }

    dev = &(sec_hashx_device[index].parent);
    sec_hashx_device[index].type = type;

    dev->open = sec_hash_open;
    dev->close = sec_hash_close;
    dev->control = sec_hash_control;
    dev->write = sec_hash_write;
    dev->read = sec_hash_read;

    dev->type = DEVICE_CLASS_SEC_HASH;
    dev->handle = NULL;

    return device_register(dev, name);
}

/**
 * @brief
 *
 * @param index
 * @param name
 * @param flag
 * @return int
 */
int sec_hash_sha256_register(enum sec_hash_index_type index, const char *name)
{
    return sec_hash_sha_register(index, SEC_HASH_SHA256, name);
}

/**
 * @brief
 *
 * @param index
 * @param name
 * @param flag
 * @return int
 */
int sec_hash_sha224_register(enum sec_hash_index_type index, const char *name)
{
    return sec_hash_sha_register(index, SEC_HASH_SHA224, name);
}

/**
 * @brief
 *
 * @param handle
 */
void sec_hash_isr(void)
{
}

/**
 * @brief
 *
 */
void SEC_SHA_IRQ(void)
{
    sec_hash_isr();
}