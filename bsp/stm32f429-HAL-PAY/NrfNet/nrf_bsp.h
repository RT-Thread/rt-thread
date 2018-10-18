#ifndef __NRF_BSP_H__
#include <nrf_data.h>

#define NRF_STORE_FLAG		0x11223344
#define NRF_STORE_ADDRESS	(ADDR_FLASH_SECTOR_11)

u32 Get_RunTime(void);
void NRF_GetMacAddr(u8 *mac,const u8 addr,u32 pwd);
u32 Get_NetworkID(void);
u8 Get_Nid(const u8 val);
void NRF_CopyMac(u8 *dstMac,const u8 *srcMac);
u8 NRF_StoreParam(NODESTATUS *NodeStatus);
void NRF_ReadParam(NODESTATUS *NodeStatus);
void NRF_ClearStroreData(void);
#endif

