/*
+------------------------------------------------------------------------------
| Project   : Device Filesystem
+------------------------------------------------------------------------------
| Copyright 2004 - 2009  www.rt-thread.org
| All rights reserved.
|------------------------------------------------------------------------------
| File      : dfs_cache.c, the LUT disk cache implementation
|------------------------------------------------------------------------------
| Chang Logs:
| Date           Author       Notes
| 2009-04-26     bernard      The first version.
+------------------------------------------------------------------------------
*/
#include "dfs_cache.h"

#define ioman_isReqRo(mode)  ((mode)&(IOM_MODE_READONLY))
#define ioman_isReqRw(mode)  ((mode)&(IOM_MODE_READWRITE))
#define ioman_isReqExp(mode) ((mode)&(IOM_MODE_EXP_REQ))

rt_err_t ioman_init(IOManager* ioman)
{
    register rt_uint32_t index;
    RT_ASSERT(ioman != RT_NULL);

	ioman->numbuf = DFS_CACHE_MAX_NUM;
	
	rt_memset(ioman->sector, 0,sizeof(ioman->sector));
	rt_memset(ioman->status, 0,sizeof(ioman->status));
	rt_memset(ioman->usage, 0, sizeof(ioman->usage));
	rt_memset(ioman->ring_fifo, 0, sizeof(ioman->ring_fifo));
	rt_memset(ioman->cache, 0, sizeof(ioman->cache));
	
    /* init fifo */
    for (index = 0; index < ioman->numbuf; index ++)
    {
    	ioman->ring_fifo[index] = ioman->numbuf - index - 1;
    }

    return RT_EOK;
}

/*
 * get the last fifo item and put it to the top of fifo ring
 */
static rt_uint8_t ioman_ring_fifo_swap(IOManager *ioman)
{
    rt_uint8_t bp;
    rt_uint32_t index;

    bp = ioman->ring_fifo[ioman->numbuf - 1];
    for (index = ioman->numbuf - 1; index > 0; index --)
    {
        ioman->ring_fifo[index] = ioman->ring_fifo[index - 1];
    }

    ioman->ring_fifo[0] = bp;

    return bp;
}

/*
 * get the index of bp in fifo ring and then put it to the top of
 * fifo ring
 */
static void ioman_ring_fifo_relocate(IOManager *ioman, rt_uint32_t bp)
{
    rt_uint32_t bp_index = 0;
    register rt_uint32_t index;

    /* find bp in fifo ring */
    for (index = 0; index < ioman->numbuf; index ++)
    {
        if (ioman->ring_fifo[index] == bp)
        {
            bp_index = index;
            break;
        }
    }

    /* not found bp in fifo ring */
    if (index == ioman->numbuf) return;

    /* move the bp to the top of fifo ring */
    for (index = bp_index; index > 0; index --)
    {
        ioman->ring_fifo[index] = ioman->ring_fifo[index - 1];
    }
    ioman->ring_fifo[0] = bp;
}

/*
 * get last bp in fifo ring
 */
rt_inline rt_uint8_t ioman_ring_fifo_last(IOManager *ioman)
{
    RT_ASSERT(ioman != RT_NULL);
    return ioman->ring_fifo[ioman->numbuf - 1];
}

static rt_err_t ioman_readSector(IOManager *ioman, rt_uint32_t address, rt_uint8_t* buf)
{
    rt_err_t result;

    RT_ASSERT(buf != RT_NULL);

    result = rt_device_read(ioman->device, address * DFS_SECTOR_SIZE, buf, DFS_SECTOR_SIZE);
    if (result == DFS_SECTOR_SIZE) return RT_EOK;

	return -RT_ERROR;
}

static rt_err_t ioman_writeSector(IOManager *ioman, rt_uint32_t address, rt_uint8_t* buf)
{
    rt_err_t result;

    RT_ASSERT(buf != RT_NULL);

    result = rt_device_write(ioman->device, address * DFS_SECTOR_SIZE, buf, DFS_SECTOR_SIZE);
    if (result == DFS_SECTOR_SIZE) return RT_EOK;

	return -RT_ERROR;
}

static rt_int32_t ioman_findSectorInCache(IOManager *ioman, rt_uint32_t address)
{
	rt_uint32_t c;

	for(c=0;c<ioman->numbuf;c++)
	{
		if((ioman->status[c] & (1 << IOMAN_STATUS_ATTR_VALIDDATA)) &&
            ioman->sector[c] == address)
            return (c);
	}

	return -RT_ERROR;
}

static rt_err_t ioman_flushSector(IOManager *ioman, rt_uint32_t bp)
{
    rt_err_t result;

    RT_ASSERT(ioman != RT_NULL);

    result = ioman_writeSector(ioman, ioman->sector[bp], &ioman->cache[bp][0]);
    if (result == RT_EOK)
    {
        /* set status */
        ioman->status[bp] &= ~(1 << IOMAN_STATUS_ATTR_WRITE);
    }

    return result;
}

rt_uint8_t* ioman_getSector(IOManager *ioman, rt_uint32_t address, rt_uint8_t mode)
{
    rt_int32_t bp;

    RT_ASSERT(ioman != RT_NULL);

    bp = ioman_findSectorInCache(ioman, address);
    if (bp != -RT_ERROR)
    {
        /* incress cache usage */
        ioman->usage[bp] ++;

        /* relocate bp in fifo ring */
        ioman_ring_fifo_relocate(ioman, bp);

        if (ioman_isReqRw(mode))
            ioman->status[bp] |= (1 << IOMAN_STATUS_ATTR_WRITE);

        return &(ioman->cache[bp][0]);
    }

    /* not find in cache, get the last bp in fifo ring */
    bp = ioman_ring_fifo_last(ioman);
    if ((ioman->status[bp] & (1 << IOMAN_STATUS_ATTR_WRITE)) &&
		ioman->usage[bp] == 0)
    {
        /* it's a writable buffer, flush it */
        ioman_flushSector(ioman, bp);
    }

    /* strip last bp in fifo ring */
    bp = ioman_ring_fifo_swap(ioman);

    /* read sector */
    ioman_readSector(ioman, address, &ioman->cache[bp][0]);
    ioman->sector[bp] = address;
    ioman->usage [bp] = 1;
    ioman->status[bp] = (1 << IOMAN_STATUS_ATTR_VALIDDATA);
    if (ioman_isReqRw(mode))
		ioman->status[bp] |= (1 << IOMAN_STATUS_ATTR_WRITE);

	return &ioman->cache[bp][0];
}

rt_err_t ioman_releaseSector(IOManager *ioman, rt_uint8_t* buf)
{
	rt_uint32_t bp;

    /* get buffer place */
    bp = ((rt_uint32_t)buf - (rt_uint32_t)&ioman->cache[0]) / DFS_SECTOR_SIZE;

    /* decrease usage */
    if (ioman->usage[bp] >  0) ioman->usage[bp] --;
	if (ioman->usage[bp] == 0)
	{
		if(ioman->status[bp] & (1 << IOMAN_STATUS_ATTR_WRITE))
		{
			ioman_flushSector(ioman,bp);
		}
	}

	return RT_EOK;
}

rt_err_t ioman_flushRange(IOManager *ioman, rt_uint32_t address_low, rt_uint32_t address_high)
{
	rt_uint32_t c;

	if(address_low > address_high)
	{
		c = address_low; address_low = address_high; address_high = c;
	}

	for(c = 0; c < ioman->numbuf; c++)
	{
		if((ioman->sector[c]>=address_low)
            && (ioman->sector[c]<=address_high)
            && (ioman->status[c] & (1 << IOMAN_STATUS_ATTR_WRITE)))
		{
			if(ioman_flushSector(ioman,c) != RT_EOK)
				return -RT_ERROR;

            /* remove writable status */
			if(ioman->usage[c]==0) ioman->status[c] &= ~IOMAN_STATUS_ATTR_WRITE;
		}
	}

	return RT_EOK;
}

/*
 * read multi-sectors directly (none-cachable)
 */
rt_err_t ioman_directSectorRead(IOManager *ioman, rt_uint32_t address, rt_uint8_t* buf, rt_uint32_t numsector)
{
    rt_err_t result;

    RT_ASSERT(buf != RT_NULL);

    result = rt_device_read(ioman->device, address * DFS_SECTOR_SIZE, buf, DFS_SECTOR_SIZE * numsector);
    if (result == DFS_SECTOR_SIZE * numsector) return RT_EOK;

	return -RT_ERROR;
}

/*
 * write multi-sectors directly (none-cachable)
 */
rt_err_t ioman_directSectorWrite(IOManager *ioman, rt_uint32_t address, rt_uint8_t* buf, rt_uint32_t numsector)
{
    rt_err_t result;

    RT_ASSERT(buf != RT_NULL);

    result = rt_device_write(ioman->device, address * DFS_SECTOR_SIZE, buf, DFS_SECTOR_SIZE * numsector);
    if (result == DFS_SECTOR_SIZE * numsector) return RT_EOK;

	return -RT_ERROR;
}
