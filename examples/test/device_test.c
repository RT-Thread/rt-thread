/*
 * File      : device_test.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-01-01     aozima       the first version
 */

#include <rtthread.h>

/* calculate speed */
static void calculate_speed_print(rt_uint32_t speed)
{
    rt_uint32_t k,m;

    k = speed/1024UL;
    if( k )
    {
        m = k/1024UL;
        if( m )
        {
            rt_kprintf("%d.%dMbyte/s",m,k%1024UL*100/1024UL);
        }
        else
        {
            rt_kprintf("%d.%dKbyte/s",k,speed%1024UL*100/1024UL);
        }
    }
    else
    {
        rt_kprintf("%dbyte/s",speed);
    }
}

static rt_err_t _block_device_test(rt_device_t device)
{
    rt_err_t result;
    struct rt_device_blk_geometry geometry;
    rt_uint8_t * read_buffer  = RT_NULL;
    rt_uint8_t * write_buffer = RT_NULL;

    rt_kprintf("\r\n");

    if( (device->flag & RT_DEVICE_FLAG_RDWR) == RT_DEVICE_FLAG_RDWR )
    {
        // device can read and write.
        // step 1: open device
        result = device->open(device,RT_DEVICE_FLAG_RDWR);
        if( result == RT_EOK )
        {
            device->open_flag |= RT_DEVICE_OFLAG_RDWR | RT_DEVICE_OFLAG_OPEN;
        }
        else
        {
            return result;
        }

        // step 2: get device info
        rt_memset(&geometry, 0, sizeof(geometry));
        result = rt_device_control(device, RT_DEVICE_CTRL_BLK_GETGEOME, &geometry);
        if( result != RT_EOK )
        {
            rt_kprintf("device : %s cmd RT_DEVICE_CTRL_BLK_GETGEOME failed.\r\n");
            return result;
        }
        rt_kprintf("device info:\r\n");
        rt_kprintf("sector  size : %d byte\r\n",geometry.bytes_per_sector);
        rt_kprintf("sector count : %d \r\n",geometry.sector_count);
        rt_kprintf("block   size : %d byte\r\n",geometry.block_size);

        rt_kprintf("\r\n");
        read_buffer = rt_malloc(geometry.bytes_per_sector);
        if( read_buffer == RT_NULL )
        {
            rt_kprintf("no memory for read_buffer!\r\n");
            goto __return;
        }
        write_buffer = rt_malloc(geometry.bytes_per_sector);
        if( write_buffer == RT_NULL )
        {
            rt_kprintf("no memory for write_buffer!\r\n");
            goto __return;
        }

        //step 3: I/O R/W test
        {
            rt_uint32_t i,err_count,sector_no;
            rt_uint8_t * data_point;

            // the first sector
            sector_no = 0;
            data_point = write_buffer;
            *data_point++ = (rt_uint8_t)sector_no;
            for(i=1; i<geometry.bytes_per_sector; i++)
            {
                *data_point++ = (rt_uint8_t)i;
            }
            i = device->write(device,sector_no,write_buffer,1);
            if( i != 1 )
            {
                rt_kprintf("write device :%s ",device->parent.name);
                rt_kprintf("the first sector failed.\r\n");
                goto __return;
            }
            i = device->read(device,sector_no,read_buffer,1);
            if( i != 1 )
            {
                rt_kprintf("read device :%s ",device->parent.name);
                rt_kprintf("the first sector failed.\r\n");
                goto __return;
            }
            err_count = 0;
            data_point = read_buffer;
            if( (*data_point++) != (rt_uint8_t)sector_no)
            {
                err_count++;
            }
            for(i=1; i<geometry.bytes_per_sector; i++)
            {
                if( (*data_point++) != (rt_uint8_t)i )
                {
                    err_count++;
                }
            }
            if( err_count > 0 )
            {
                rt_kprintf("verify device :%s ",device->parent.name);
                rt_kprintf("the first sector failed.\r\n");
                goto __return;
            }
            // the second sector
            sector_no = 1;
            data_point = write_buffer;
            *data_point++ = (rt_uint8_t)sector_no;
            for(i=1; i<geometry.bytes_per_sector; i++)
            {
                *data_point++ = (rt_uint8_t)i;
            }
            i = device->write(device,sector_no,write_buffer,1);
            if( i != 1 )
            {
                rt_kprintf("write device :%s ",device->parent.name);
                rt_kprintf("the second sector failed.\r\n");
                goto __return;
            }
            i = device->read(device,sector_no,read_buffer,1);
            if( i != 1 )
            {
                rt_kprintf("read device :%s ",device->parent.name);
                rt_kprintf("the second sector failed.\r\n");
                goto __return;
            }
            err_count = 0;
            data_point = read_buffer;
            if( (*data_point++) != (rt_uint8_t)sector_no)
            {
                err_count++;
            }
            for(i=1; i<geometry.bytes_per_sector; i++)
            {
                if( (*data_point++) != (rt_uint8_t)i )
                {
                    err_count++;
                }
            }
            if( err_count > 0 )
            {
                rt_kprintf("verify device :%s ",device->parent.name);
                rt_kprintf("the second sector failed.\r\n");
                goto __return;
            }
            // the end sector
            sector_no = geometry.sector_count-1;
            data_point = write_buffer;
            *data_point++ = (rt_uint8_t)sector_no;
            for(i=1; i<geometry.bytes_per_sector; i++)
            {
                *data_point++ = (rt_uint8_t)i;
            }
            i = device->write(device,sector_no,write_buffer,1);
            if( i != 1 )
            {
                rt_kprintf("write device :%s ",device->parent.name);
                rt_kprintf("the end sector failed.\r\n");
                goto __return;
            }
            i = device->read(device,sector_no,read_buffer,1);
            if( i != 1 )
            {
                rt_kprintf("read device :%s ",device->parent.name);
                rt_kprintf("the end sector failed.\r\n");
                goto __return;
            }
            err_count = 0;
            data_point = read_buffer;
            if( (*data_point++) != (rt_uint8_t)sector_no)
            {
                err_count++;
            }
            for(i=1; i<geometry.bytes_per_sector; i++)
            {
                if( (*data_point++) != (rt_uint8_t)i )
                {
                    err_count++;
                }
            }
            if( err_count > 0 )
            {
                rt_kprintf("verify device :%s ",device->parent.name);
                rt_kprintf("the end sector failed.\r\n");
                goto __return;
            }
            rt_kprintf("device I/O R/W test pass!\r\n");

        }//step 3: I/O R/W test

        // step 4: speed test
        {
            rt_uint32_t tick_start,tick_end;
            rt_uint32_t i;

            rt_kprintf("\r\n");
            rt_kprintf("device I/O speed test.\r\n");
            rt_kprintf("RT_TICK_PER_SECOND:%d\r\n",RT_TICK_PER_SECOND);

            if( geometry.sector_count < 10 )
            {
                rt_kprintf("device sector_count < 10,speed test abort!\r\n");
            }
            else
            {
                // sign sector read
                tick_start = rt_tick_get();
                for(i=0; i<200; i++)
                {
                    device->read(device,i%10,read_buffer,1);
                }
                tick_end = rt_tick_get();
                rt_kprintf("read 200 sector from %d to %d, ",tick_start,tick_end);
                calculate_speed_print( (geometry.bytes_per_sector*200UL*RT_TICK_PER_SECOND)/(tick_end-tick_start) );
                rt_kprintf("\r\n");

                // sign sector write
                tick_start = rt_tick_get();
                for(i=0; i<200; i++)
                {
                    device->write(device,i%10,read_buffer,1);
                }
                tick_end = rt_tick_get();
                rt_kprintf("write 200 sector from %d to %d, ",tick_start,tick_end);
                calculate_speed_print( (geometry.bytes_per_sector*200UL*RT_TICK_PER_SECOND)/(tick_end-tick_start) );
                rt_kprintf("\r\n");
            }
        }// step 4: speed test

        return RT_EOK;
    }// device can read and write.
    else
    {
        // device read only
        return RT_EOK;
    }// device read only

__return:
    if( read_buffer != RT_NULL )
    {
        rt_free(read_buffer);
    }
    if( write_buffer != RT_NULL )
    {
        rt_free(write_buffer);
    }
    return RT_ERROR;
}

int device_test(const char * device_name)
{
    rt_device_t device = RT_NULL;

    // step 1:find device
    device = rt_device_find(device_name);
    if( device == RT_NULL)
    {
        rt_kprintf("device %s: not found!\r\n");
        return RT_ERROR;
    }

    // step 2:init device
    if (!(device->flag & RT_DEVICE_FLAG_ACTIVATED))
    {
        rt_err_t result;
        result = device->init(device);
        if (result != RT_EOK)
        {
            rt_kprintf("To initialize device:%s failed. The error code is %d\r\n",
                       device->parent.name, result);
            return result;
        }
        else
        {
            device->flag |= RT_DEVICE_FLAG_ACTIVATED;
        }
    }

    // step 3: device test
    switch( device->type )
    {
    case RT_Device_Class_Block :
        rt_kprintf("block device!\r\n");
        return _block_device_test(device);
    default:
        rt_kprintf("unkown device type : %02X",device->type);
        return RT_ERROR;
    }
}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(device_test, e.g:device_test("sd0"));
#endif

