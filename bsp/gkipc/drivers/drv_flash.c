#include <stdio.h>
#include <rtdevice.h>

#include "gtypes.h"
#include "gd_sflash.h"

/*---------------------------------------------------------------------------*/
/* local defines                                                             */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* local data types                                                          */
/*---------------------------------------------------------------------------*/

struct gk_flash
{

    struct rt_device device;
    struct rt_mutex lock;
    struct rt_device_blk_geometry flashinfo;

    GD_HANDLE    handle;

};

static struct gk_flash flashdev;

/*---------------------------------------------------------------------------*/
/* local data                                                                */
/*---------------------------------------------------------------------------*/


static rt_uint32_t auctempArr[512] = {0};

/*---------------------------------------------------------------------------*/
/* local  functions                                                          */
/*---------------------------------------------------------------------------*/
static rt_err_t  gk_flash_init  (rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t  gk_flash_open  (rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t  gk_flash_close (rt_device_t dev)
{
    return RT_EOK;
}

static rt_size_t gk_flash_read  (rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(buffer != RT_NULL);
    RT_ASSERT(size > 0);
    RT_ASSERT(dev->user_data != NULL);

    int  ret     = 0;
    rt_uint32_t temp        = 0;
    rt_uint32_t readSize    = 0;
    char *ptr            = NULL;
    U8  readLastBuffer[4] = {0};
    rt_uint32_t numReadSize        = 0;
    rt_uint32_t offsetAddr         = 0;

    struct gk_flash *flashdevPtr = (struct gk_flash *)dev->user_data;

    rt_mutex_take(&flashdevPtr->lock, RT_WAITING_FOREVER);

    rt_memset(auctempArr, 0, 512);

    if(pos%4 != 0)
    {
        temp = pos%4;
        if((size+8) > 512)
        {
            ret |= GD_SFLASH_Read(flashdevPtr->handle, pos-temp, auctempArr, 4);
            readSize = 4-temp;
            ptr = (char*)auctempArr;
            rt_memcpy(buffer,ptr+temp,readSize);
            ret |= GD_SFLASH_Read(flashdevPtr->handle, pos+readSize, (rt_uint32_t *)buffer+readSize, (size-readSize)/4);
        }
        else
        {
            readSize = ((size+8)/4);
            ret |= GD_SFLASH_Read(flashdevPtr->handle, pos-temp, auctempArr, readSize);
            ptr = (char *)auctempArr;
            rt_memcpy(buffer, ptr+temp, size);
        }
    }
    else
    {
        if (size % 4)
        {
            if (size/4 != 0)
            {
                ret |= GD_SFLASH_Read(flashdevPtr->handle, pos, (rt_uint32_t*)buffer, size/4);
                if ( ret != GD_OK )
                {
                   rt_kprintf( "\n[%d][gk_flash_read] GD_SFLASH_Read_Byte err!!\n",__LINE__);
                }
            }

            numReadSize = size % 4;
            offsetAddr  = size - numReadSize;
            ret |= GD_SFLASH_Read(flashdevPtr->handle, pos+offsetAddr, (rt_uint32_t *)readLastBuffer, 1); // read 4 bytes
            if ( ret != GD_OK )
            {
               rt_kprintf( "\n[%d][gk_flash_read] GD_SFLASH_Read_Byte err!!\n",__LINE__);
            }

            rt_memcpy((U8 *)buffer+offsetAddr, readLastBuffer, numReadSize);

        }
        else
        {
            ret |= GD_SFLASH_Read(flashdevPtr->handle, pos, (rt_uint32_t *)buffer, size/4);
            if ( ret != GD_OK )
            {
               rt_kprintf( "\n[%d][gk_flash_read] GD_SFLASH_Read_Byte err!!\n",__LINE__);
            }
        }

    }

    rt_mutex_release(&flashdevPtr->lock);

    return (ret == GD_OK)?RT_EOK:RT_ERROR;

}

static rt_size_t gk_flash_write (rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(buffer != RT_NULL);
    RT_ASSERT(size > 0);
    RT_ASSERT(dev->user_data != NULL);

    int ret             = GD_OK;
    U8  writeLastBuffer[4] = {0};
    rt_uint32_t numWriteSize       = 0;
    rt_uint32_t offsetAddr         = 0;

    struct gk_flash *flashdevPtr = (struct gk_flash *)dev->user_data;

    if(pos %4 != 0)
    {
        rt_kprintf("\n[gk_flash_write] the write flash address isn't assigned in 4 bytes.\n");
        return RT_ERROR;
    }

    rt_mutex_take(&flashdevPtr->lock, RT_WAITING_FOREVER);

    if(size%4)
    {
        if (size/4 != 0)
        {
            ret = GD_SFLASH_Write(flashdevPtr->handle, pos, (rt_uint32_t*)buffer, size/4);
            if ( ret != GD_OK )
            {
               rt_kprintf("\n[gk_flash_write:%d] GD_SFLASH_Write_Byte err!!,ret = %ld\n",__LINE__,ret);
            }
        }
        numWriteSize = size%4;
        offsetAddr   = size - numWriteSize;

        rt_memcpy(writeLastBuffer, (U8 *)buffer+offsetAddr, numWriteSize);

        ret |= GD_SFLASH_Program(flashdevPtr->handle, (pos + offsetAddr), (rt_uint32_t*)writeLastBuffer, 1);// write 4 bytes
        if ( ret != GD_OK )
        {
           rt_kprintf("\n[gk_flash_write:%d] GD_SFLASH_Write_Byte err!!,ret = %ld\n",__LINE__,ret);
        }
    }
    else
    {
        ret = GD_SFLASH_Write(flashdevPtr->handle, pos, (rt_uint32_t*)buffer, size/4);
        if ( ret != GD_OK )
        {
           rt_kprintf("\n[gk_flash_write:%d] GD_SFLASH_Write_Byte err!!,ret = %ld\n",__LINE__,ret);
        }
    }

    rt_mutex_release(&flashdevPtr->lock);

    return (ret == GD_OK)?RT_EOK:RT_ERROR;

}

static rt_err_t  gk_flash_control(rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(dev->user_data != NULL);
    RT_ASSERT(args != RT_NULL);
    rt_uint32_t i = 0,ret;

    struct gk_flash *flashdevPtr = (struct gk_flash *)dev->user_data;

    rt_mutex_take(&flashdevPtr->lock, RT_WAITING_FOREVER);

    switch(cmd)
    {
        case RT_DEVICE_CTRL_BLK_GETGEOME:
        {
            struct rt_device_blk_geometry *geometry;

            geometry = (struct rt_device_blk_geometry *)args;
            if (geometry == RT_NULL)
            {
                rt_mutex_release(&flashdevPtr->lock);
                return -RT_ERROR;
            }
            geometry->bytes_per_sector = flashdevPtr->flashinfo.bytes_per_sector;
            geometry->sector_count = flashdevPtr->flashinfo.sector_count;
            geometry->block_size = flashdevPtr->flashinfo.bytes_per_sector;//64k

            break;
        }
        case RT_DEVICE_CTRL_BLK_ERASE: //params are sector index to erase start and end.
        {
            rt_uint32_t *addrs = (rt_uint32_t *) args, start_sector = addrs[0], end_sector = addrs[1];

            rt_size_t phy_size;

            if (addrs == RT_NULL || start_sector > end_sector || start_sector > flashdevPtr->flashinfo.sector_count)
            {
                rt_mutex_release(&flashdevPtr->lock);
                return -RT_ERROR;
            }

            for(i = start_sector; i <= end_sector; i++)
            {
                ret = GD_SFLASH_EraseSector(flashdevPtr->handle, (rt_uint16_t)i);
                if ( ret != GD_OK )
                {
                    rt_kprintf("\n[gk_flash_control] GD_SFLASH_EraseSector err!!\n");
                }

                rt_kprintf("\n[gk_flash_control] erase sector number = %ld\n", i);
            }

            break;
        }
        default:
            break;
    }

    rt_mutex_release(&flashdevPtr->lock);

    return RT_EOK;
}


void rt_flash_init(void)
{

    GD_SFLASH_CHANNEL_E channel = GD_SFLASH_CHANNEL_0;
    rt_uint32_t deviceBytes = 0;
    rt_uint16_t sectorCount = 0;
    rt_uint32_t sectorSize = 0;
    rt_uint16_t tmp_sectorIndex = 16;
    rt_int32_t ret;

    GD_SFLASH_Init();

    rt_memset((void *)&flashdev,0,sizeof(struct gk_flash));

    for(;channel<GD_SFLASH_SPI_CHANNEL_0_0; channel++)
    {
      ret = GD_SFLASH_Open((GD_HANDLE *)&flashdev.handle, GD_SFLASH_FREQ_DIV4, channel);
      if(ret == GD_OK)
          break;
    }

    if ( channel == GD_SFLASH_SPI_CHANNEL_0_0 )
    {
      rt_kprintf("\nrt_flash_init failed!!\n");
      return;
    }


    ret = GD_SFLASH_GetSize(flashdev.handle, &deviceBytes);

    deviceBytes *= sizeof(rt_uint32_t);

    if (ret != GD_OK)
    {
        rt_kprintf("\n[rt_flash_init] GD_SFLASH_GetSize err!!\n");
    }
    else
    {
        //rt_kprintf("\n[rt_flash_init] deviceBytes = 0x%lx\n", deviceBytes);
    }


    ret = GD_SFLASH_GetNumberOfSectors(flashdev.handle, &sectorCount);
    if (ret != GD_OK)
    {
        rt_kprintf("\n[rt_flash_init] GD_SFLASH_GetNumberOfSectors err!!\n");
    }
    else
    {
        //rt_kprintf("\n[rt_flash_init] sectorCount = %ld\n", sectorCount);
    }


    ret = GD_SFLASH_GetSectorSize(flashdev.handle, tmp_sectorIndex, &sectorSize);
    sectorSize *= sizeof(rt_uint32_t);
    if (ret != GD_OK)
    {
        rt_kprintf("\n[gk_flash_control] GD_SFLASH_GetSectorSize err!!\n");
    }
    else
    {
        //rt_kprintf("\n[gk_flash_control] sectorBytes = 0x%lx\n", sectorSize);
    }

    flashdev.flashinfo.bytes_per_sector = sectorSize;
    flashdev.flashinfo.sector_count = sectorCount;
    flashdev.flashinfo.block_size = sectorSize;//64k

    flashdev.device.type            = RT_Device_Class_Block;
    flashdev.device.rx_indicate     = RT_NULL;
    flashdev.device.tx_complete     = RT_NULL;

    flashdev.device.init            = gk_flash_init;
    flashdev.device.open            = gk_flash_open;
    flashdev.device.close           = gk_flash_close;
    flashdev.device.read            = gk_flash_read;
    flashdev.device.write           = gk_flash_write;
    flashdev.device.control         = gk_flash_control;
    flashdev.device.user_data       = (void *)&flashdev;


    ret = rt_mutex_init(&flashdev.lock,"sflash", RT_IPC_FLAG_FIFO);
    if (ret != RT_EOK)
    {
        rt_kprintf("\nrt_flash_init creat mutex failed!!\n");
        return;
    }

    rt_device_register(&flashdev.device, "sflash",
                               RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE);

}

