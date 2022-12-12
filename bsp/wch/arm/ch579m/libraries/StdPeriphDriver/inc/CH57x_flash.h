


#ifndef __CH57x_FLASH_H__
#define __CH57x_FLASH_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "CH579SFR.h"
#include "core_cm0.h"

#define ROM_UUID_ADDR        0x40608         // chip UID address ( ID-48bit + CKS-16bit )
#define ROM_MAC_ADDR         0x40608         // NET MAC address 48bit

// 获取唯一ID
void GetUniqueID(PUINT8 buf);                                           /* 获取芯片唯一ID，小端模式，6B-ID， 2B-CKS */

// 获取网络MAC
void GetMACAddress(PUINT8 buf);                                         /* 获取网络MAC，小端模式，6B-MAC */


UINT8 FlashBlockErase(UINT32 addr);
UINT8 FlashWriteDW(UINT32 addr, UINT32 dat);
UINT8 FlashWriteBuf(UINT32 addr, PUINT32 pdat, UINT16 len);



#ifdef __cplusplus
}
#endif

#endif  // __CH57x_FLASH_H__

