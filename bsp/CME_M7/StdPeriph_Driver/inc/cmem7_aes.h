/**
    *****************************************************************************
    * @file     cmem7_aes.h
    *
    * @brief    CMEM7 AES header file
    *
    *
    * @version  V1.0
    * @date     3. September 2013
    *
    * @note
    *
    *****************************************************************************
    * @attention
    *
    * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
    * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
    * TIME. AS A RESULT, CAPITAL-MICRO SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
    * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
    * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
    * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
    *
    * <h2><center>&copy; COPYRIGHT 2013 Capital-micro </center></h2>
    *****************************************************************************
    */

#ifndef __CMEM7_AES_H
#define __CMEM7_AES_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "cmem7.h"
#include "cmem7_conf.h"

/**
  * @brief  AES decryption
    * @param[in] src A pointer to data to be decrypted
    * @param[out] dst A user-allocated buffer to fetch decrypted data
  * @param[in] len Expected data size to be decrypted, which should
    *                        be multiply times of 16
    * @retval BOOL True if succeed, or flase
    */
BOOL AES_Decrypt(const void *src, void *dst, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif /* __CMEM7_AES_H */

