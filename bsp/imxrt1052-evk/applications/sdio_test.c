#include "rtthread.h"
#include <stdint.h>
#include "string.h"

#define __is_print(ch) ((unsigned int)((ch) - ' ') < 127u - ' ')
static void dump_hex(const rt_uint8_t *ptr, rt_size_t buflen)
{
    unsigned char *buf = (unsigned char*)ptr;
    int i, j;

    for (i=0; i<buflen; i+=16)
    {
        rt_kprintf("%08X: ", i);

        for (j=0; j<16; j++)
            if (i+j < buflen)
                rt_kprintf("%02X ", buf[i+j]);
            else
                rt_kprintf("   ");
        rt_kprintf(" ");

        for (j=0; j<16; j++)
            if (i+j < buflen)
                rt_kprintf("%c", __is_print(buf[i+j]) ? buf[i+j] : '.');
        rt_kprintf("\n");
    }
}


static void read_sd__(uint32_t addr, int length, int count)
{
    rt_device_t device = RT_NULL;
    rt_err_t result;
    struct rt_device_blk_geometry geometry;
    rt_uint8_t * read_buffer  = RT_NULL;

    device = rt_device_find("sd0");
    rt_device_init(device);
    rt_device_open(device,RT_DEVICE_FLAG_RDWR);

    rt_memset(&geometry, 0, sizeof(geometry));
    result = rt_device_control(device,
                               RT_DEVICE_CTRL_BLK_GETGEOME,
                               &geometry);                  
    rt_kprintf("device info:\r\n");
    rt_kprintf("sector  size : %d byte\r\n", geometry.bytes_per_sector);
    rt_kprintf("sector count : %d \r\n", geometry.sector_count);
    rt_kprintf("block   size : %d byte\r\n", geometry.block_size);
    
    rt_kprintf("\r\n");
    read_buffer = rt_malloc(geometry.bytes_per_sector*length);
    if( read_buffer == RT_NULL )
    {
        rt_kprintf("no memory for read_buffer!\r\n");
        goto __return;
    }
    
    memset(read_buffer,0x00,geometry.bytes_per_sector*length);
    // for(i = 0;i < count; i++)
    {
        result = rt_device_read(device,addr,read_buffer, length);
        
        dump_hex(read_buffer,geometry.bytes_per_sector * length);
        if(result != length)
        {
            rt_kprintf("read device :%s ", device->parent.name);
            rt_kprintf("the first sector failed.\r\n");
            goto __return;
        }
        rt_kprintf("\n");
    }
     
__return:
    if( read_buffer != RT_NULL )
    {
        rt_free(read_buffer);
    }  
}

static void write_sd__(uint32_t addr, int length, unsigned char data)
{
    int i;
    rt_device_t device = RT_NULL;
    rt_err_t result;
    struct rt_device_blk_geometry geometry;
    rt_uint8_t * write_buffer = RT_NULL;
    rt_uint8_t * data_point = RT_NULL;;
    
    device = rt_device_find("sd0");
    rt_device_init(device);
    rt_device_open(device,RT_DEVICE_FLAG_RDWR);

    rt_memset(&geometry, 0, sizeof(geometry));
    result = rt_device_control(device,
                               RT_DEVICE_CTRL_BLK_GETGEOME,
                               &geometry);                  
    rt_kprintf("device info:\r\n");
    rt_kprintf("sector  size : %d byte\r\n", geometry.bytes_per_sector);
    rt_kprintf("sector count : %d \r\n", geometry.sector_count);
    rt_kprintf("block   size : %d byte\r\n", geometry.block_size);
    rt_kprintf("\r\n");
    write_buffer = rt_malloc(geometry.bytes_per_sector);
    if( write_buffer == RT_NULL )
    {
        rt_kprintf("no memory for write_buffer!\r\n");
        goto __return;
    }
    data_point = write_buffer;
    
    for(i=data; i<geometry.bytes_per_sector; i++)
    {
        *data_point++ = (rt_uint8_t)i;
    }
    
    for(i = addr;i < (length + addr); i++)
    {
        rt_device_write(device, addr, write_buffer,1);
    }
    
__return:
    if( write_buffer != RT_NULL )
    {
        rt_free(write_buffer);
    }
}

int sdio_read(uint32_t addr, int length, int count)
{
    read_sd__(addr, length, count);
    
    return 0;
}

int sdio_write(uint32_t addr, int length, unsigned char data)
{
    write_sd__(addr, length, data);
    
    return 0;
}



#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT_ALIAS(sdio_read, sdior, sdio read test);
FINSH_FUNCTION_EXPORT_ALIAS(sdio_write, sdiow, sdio write test);
#endif
