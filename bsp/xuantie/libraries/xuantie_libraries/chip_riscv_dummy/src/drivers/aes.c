/*
 *  Copyright (C) 2017-2024 Alibaba Group Holding Limited
 */

/*******************************************************
 * @file    wj_aes.c
 * @brief   source file for aes csi driver
 * @version V1.0
 * @date    2. July 2020
 * ******************************************************/

#include <drv/aes.h>
#include <drv/irq.h>

#define AES_READ_CACHE_LITTLE(_addr_)   \
    (((uint32_t) * (_addr_ + 0U) << 0)  | ((uint32_t) * (_addr_ + 1U) << 8) | \
     ((uint32_t) * (_addr_ + 2U) << 16) | ((uint32_t) * (_addr_ + 3U) << 24))

#define AES_WRITE_CACHE_LITTLE(_addr_, _data_) \
    do {  \
        *(_addr_+0U) = (uint8_t)*(_data_+0U);  \
        *(_addr_+1U) = (uint8_t)*(_data_+1U);  \
        *(_addr_+2U) = (uint8_t)*(_data_+2U);  \
        *(_addr_+3U) = (uint8_t)*(_data_+3U);  \
    } while(0)

#define AES_IS_16BYTES_ALIGNMENT(_size_)     ((_size_ % 16U) ? -1 : 0)

/**
  \brief       Initialize AES Interface. Initializes the resources needed for the AES interface
  \param[in]   aes    operate handle
  \param[in]   idx    device id
  \return      error code \ref csi_error_t
*/
csi_error_t csi_aes_init(csi_aes_t *aes, uint32_t idx)
{
    CSI_PARAM_CHK(aes, CSI_ERROR);

    csi_error_t ret = CSI_OK;

    ///< 获取中断号、基地址等相关信息
    if (0 == target_get(DEV_WJ_AES_TAG, idx, &aes->dev)) {

        ///< TODO：对AES的所有寄存器进行清零操作

    } else {
        ret = CSI_ERROR;
    }

    return ret;
}
/**
  \brief       De-initialize AES Interface. stops operation and releases the software resources used by the interface
  \param[in]   aes    aes handle to operate
  \return      None
*/
void csi_aes_uninit(csi_aes_t *aes)
{
    CSI_PARAM_CHK_NORETVAL(aes);

    ///< TODO：对AES的所有寄存器进行清零操作

}
/**
  \brief       Set encrypt key
  \param[in]   aes        aes handle to operate
  \param[in]   key        Pointer to the key buf
  \param[in]   key_len    Pointer to \ref csi_aes_key_bits_t
  \return      error code \ref csi_error_t
*/
csi_error_t csi_aes_set_encrypt_key(csi_aes_t *aes, void *key, csi_aes_key_bits_t key_len)
{
    CSI_PARAM_CHK(aes, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    switch (key_len) {
        case AES_KEY_LEN_BITS_128:
            ///< TODO：设置密钥长度为128 bits
            break;

        case AES_KEY_LEN_BITS_192:
            ///< TODO：设置密钥长度为128 bits
            break;

        case AES_KEY_LEN_BITS_256:
            ///< TODO：设置密钥长度为128 bits
            break;

        default:
            ret = CSI_ERROR;
            break;
    }

        ///< TODO：设置密钥
        ///< TODO：使能AES
        ///< TODO：停止AES

    return ret;
}
/**
  \brief       Set decrypt key
  \param[in]   aes        aes handle to operate
  \param[in]   key        Pointer to the key buf
  \param[in]   key_len    Pointer to \ref csi_aes_key_bits_t
  \return      error code \ref csi_error_t
*/
csi_error_t csi_aes_set_decrypt_key(csi_aes_t *aes, void *key, csi_aes_key_bits_t key_len)
{
    CSI_PARAM_CHK(aes, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    switch (key_len) {
        case AES_KEY_LEN_BITS_128:
            ///< TODO：设置密钥长度为128 bits
            break;

        case AES_KEY_LEN_BITS_192:
            ///< TODO：设置密钥长度为128 bits
            break;

        case AES_KEY_LEN_BITS_256:
            ///< TODO：设置密钥长度为128 bits
            break;

        default:
            ret = CSI_ERROR;
            break;
    }

       ///< TODO：设置密钥
       ///< TODO：使能AES
       ///< TODO：停止AES

    return ret;
}

/**
  \brief       Aes ecb encrypt or decrypt
  \param[in]   aes     aes handle to operate
  \param[in]   in      Pointer to the Source data
  \param[out]  out     Pointer to the Result data
  \param[in]   size    the Source data size
  \return      error code \ref csi_error_t
*/
csi_error_t csi_aes_ecb_encrypt(csi_aes_t *aes, void *in, void *out, uint32_t size)
{
    CSI_PARAM_CHK(aes, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    uint32_t i = 0U;
    uint32_t j = 0U;
    uint32_t n = 0U;
    uint32_t temp;
    ///< 加密数据长度判断
    if (0 == AES_IS_16BYTES_ALIGNMENT(size)) {

       ///< TODO：设置ECB模式
       ///< TODO：设置加密

        /* set the text before aes calculating */
        for (i = 0U; i < size; i = i + 16U) {
            for (j = 0U; j < 4U; j++) {
                n = (j << 2) + i;            ///< j:each time offset 4bytes, i:each time offset 16bytes
                temp = AES_READ_CACHE_LITTLE((uint8_t *)in + n);
                ///< TODO：写入待加密数据
            }

            ///< TODO：开始加密

            ///< TODO：等待加密完成

            for (j = 0U; j < 4U; j++) {
                n = (j << 2) + i;            ///< j:each time offset 4bytes, i:each time offset 16bytes
                ///< TODO：获取加密数据到 temp
                AES_WRITE_CACHE_LITTLE((uint8_t *)out + n, (uint8_t *)&temp);
            }
        }
    } else {
        ret = CSI_ERROR;
    }

    return ret;
}
/**
  \brief       Aes ecb decrypt
  \param[in]   aes     aes handle to operate
  \param[in]   in      Pointer to the Source data
  \param[out]  out     Pointer to the Result data
  \param[in]   size    the Source data size
  \return      error code \ref csi_error_t
*/
csi_error_t csi_aes_ecb_decrypt(csi_aes_t *aes, void *in, void *out, uint32_t size)
{
    CSI_PARAM_CHK(aes, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    uint32_t i = 0U;
    uint32_t j = 0U;
    uint32_t n = 0U;
    uint32_t temp;

    if (0 == AES_IS_16BYTES_ALIGNMENT(size)) {

       ///< TODO：设置ECB模式
       ///< TODO：设置解密


        /* set the text before aes calculating */
        for (i = 0U; i < size; i = i + 16U) {
            for (j = 0U; j < 4U; j++) {
                n = (j << 2) + i;            ///< j:each time offset 4bytes, i:each time offset 16bytes
                temp = AES_READ_CACHE_LITTLE((uint8_t *)in + n);
                 ///< TODO：写入待解密数据
            }

            ///< TODO：开始解密


            ///< TODO：等待加密完成

            for (j = 0U; j < 4U; j++) {
                n = (j << 2) + i;            ///< j:each time offset 4bytes, i:each time offset 16bytes
                ///< TODO：获取解密数据到 temp
                AES_WRITE_CACHE_LITTLE((uint8_t *)out + n, (uint8_t *)&temp);
            }
        }
    } else {
        ret = CSI_ERROR;
    }

    return ret;
}
/**
  \brief       Aes cbc encrypt or decrypt
  \param[in]   aes     aes handle to operate
  \param[in]   in      Pointer to the Source data
  \param[out]  out     Pointer to the Result data
  \param[in]   size    the Source data size
  \return      error code \ref csi_error_t
*/
csi_error_t csi_aes_cbc_encrypt(csi_aes_t *aes, void *in, void *out, uint32_t size, void *iv)
{
    CSI_PARAM_CHK(aes, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    uint32_t i = 0U;
    uint32_t j = 0U;
    uint32_t n = 0U;
    uint32_t temp;

    if (0 == AES_IS_16BYTES_ALIGNMENT(size)) {
        ///< TODO：清除IV 值

       ///< TODO：设置CBC模式
       ///< TODO：设置加密密

        /* set iv if the mode is CBC */
        for (i = 0U; i < 4U; i++) {
            temp = AES_READ_CACHE_LITTLE((uint8_t *)iv + (i << 2));
            ///< TODO：设置CBC值
        }

        /* set the text before aes calculating */
        for (i = 0U; i < size; i = i + 16U) {
            for (j = 0U; j < 4U; j++) {
                n = (j << 2) + i;            ///< j:each time offset 4bytes, i:each time offset 16bytes
                temp = AES_READ_CACHE_LITTLE((uint8_t *)in + n);
                ///< TODO：写入待加密数据
            }

            ///< TODO：开始加密

            ///< TODO：等待加密

            for (j = 0U; j < 4U; j++) {
                n = (j << 2) + i;            ///< j:each time offset 4bytes, i:each time offset 16bytes
                ///< TODO：获取加密数据到 temp
                AES_WRITE_CACHE_LITTLE((uint8_t *)out + n, (uint8_t *)&temp);
            }
        }

        for (i = 0U; i < 4U; i++) {
            ///< TODO：获取IV 数据到 temp
            AES_WRITE_CACHE_LITTLE((uint8_t *)iv + (i << 2), (uint8_t *)&temp);
        }
    } else {
        ret = CSI_ERROR;
    }

    return ret;
}
/**
  \brief       Aes cbc decrypt
  \param[in]   aes     aes handle to operate
  \param[in]   in      Pointer to the Source data
  \param[out]  out     Pointer to the Result data
  \param[in]   size    the Source data size
  \param[in]   iv      init vector
  \return      error code \ref csi_error_t
*/
csi_error_t csi_aes_cbc_decrypt(csi_aes_t *aes, void *in, void *out, uint32_t size, void *iv)
{
    CSI_PARAM_CHK(aes, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    uint32_t i = 0U;
    uint32_t j = 0U;
    uint32_t n = 0U;
    uint32_t temp = 0U;

    if (0 == AES_IS_16BYTES_ALIGNMENT(size)) {
        ///< TODO：清除IV 值


       ///< TODO：设置CBC模式
       ///< TODO：设置解密

        ///< TODO：设置IV 值

        /* set the text before aes calculating */
        for (i = 0U; i < size; i = i + 16U) {
            for (j = 0U; j < 4U; j++) {
                n = (j << 2) + i;            ///< j:each time offset 4bytes, i:each time offset 16bytes
                temp = AES_READ_CACHE_LITTLE((uint8_t *)in + n);
                ///< TODO：写入待解密数据
            }

            ///< TODO：开始解密

            ///< TODO：等待解密


            for (j = 0U; j < 4U; j++) {
                n = (j << 2) + i;            ///< j:each time offset 4bytes, i:each time offset 16bytes
                ///< TODO：获取解密数据到 temp
                AES_WRITE_CACHE_LITTLE((uint8_t *)out + n, (uint8_t *)&temp);
            }
        }

        for (i = 0U; i < 4U; i++) {
            ///< TODO：获取IV数据到 temp
            AES_WRITE_CACHE_LITTLE((uint8_t *)iv + (i << 2), (uint8_t *)&temp);
        }
    } else {
        ret = CSI_ERROR;
    }

    return ret;
}
