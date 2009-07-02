#ifndef __DFS_CACHE_H__
#define __DFS_CACHE_H__

#include <rtthread.h>

#define IOMAN_STATUS_ATTR_VALIDDATA  0
#define IOMAN_STATUS_ATTR_USERBUFFER 1
#define IOMAN_STATUS_ATTR_WRITE      2

#define IOM_MODE_READONLY  1
#define IOM_MODE_READWRITE 2
#define IOM_MODE_EXP_REQ   4

#define DFS_SECTOR_SIZE     512

struct _IOManager
{
	rt_device_t device;
	rt_uint8_t  numbuf;
	
    rt_uint32_t sector[DFS_CACHE_MAX_NUM];
	rt_uint8_t  status[DFS_CACHE_MAX_NUM];
	rt_uint8_t  usage [DFS_CACHE_MAX_NUM];

    /* cache FIFO */
    rt_uint8_t  ring_fifo[DFS_CACHE_MAX_NUM];

    /* cache buffer */
    rt_uint8_t  cache[DFS_CACHE_MAX_NUM][DFS_SECTOR_SIZE];
};
typedef struct _IOManager IOManager;

rt_err_t ioman_init(IOManager* ioman);
rt_uint8_t* ioman_getSector(IOManager *ioman, rt_uint32_t address, rt_uint8_t mode);
rt_err_t ioman_releaseSector(IOManager *ioman, rt_uint8_t* buf);
rt_err_t ioman_flushRange(IOManager *ioman, rt_uint32_t address_low, rt_uint32_t address_high);

rt_err_t ioman_directSectorRead(IOManager *ioman, rt_uint32_t address, rt_uint8_t* buf, rt_uint32_t numsector);
rt_err_t ioman_directSectorWrite(IOManager *ioman, rt_uint32_t address, rt_uint8_t* buf, rt_uint32_t numsector);

#endif
