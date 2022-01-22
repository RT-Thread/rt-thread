/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-01-01     aozima       the first version.
 * 2012-02-11     aozima       add multiple sector speed test.
 * 2012-05-27     aozima       use rt_deice API.
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
        result = rt_device_open(device,RT_DEVICE_FLAG_RDWR);
        if( result != RT_EOK )
        {
            return result;
        }

        // step 2: get device info
        rt_memset(&geometry, 0, sizeof(geometry));
        result = rt_device_control(device,
                                   RT_DEVICE_CTRL_BLK_GETGEOME,
                                   &geometry);
        if( result != RT_EOK )
        {
            rt_kprintf("device : %s cmd RT_DEVICE_CTRL_BLK_GETGEOME failed.\r\n");
            return result;
        }
        rt_kprintf("device info:\r\n");
        rt_kprintf("sector  size : %d byte\r\n", geometry.bytes_per_sector);
        rt_kprintf("sector count : %d \r\n", geometry.sector_count);
        rt_kprintf("block   size : %d byte\r\n", geometry.block_size);

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

        /* step 3:  R/W test */
        {
            rt_uint32_t i, err_count, sector_no;
            rt_uint8_t * data_point;

            i = rt_device_read(device, 0, read_buffer, 1);
            if(i != 1)
            {
                rt_kprintf("read device :%s ", device->parent.name);
                rt_kprintf("the first sector failed.\r\n");
                goto __return;
            }

            data_point = write_buffer;
            for(i=0; i<geometry.bytes_per_sector; i++)
            {
                *data_point++ = (rt_uint8_t)i;
            }

            /* write first sector */
            sector_no = 0;
            data_point = write_buffer;
            *data_point++ = (rt_uint8_t)sector_no;
            i = rt_device_write(device, sector_no, write_buffer,1);
            if( i != 1 )
            {
                rt_kprintf("read the first sector success!\r\n");
                rt_kprintf("but write device :%s ", device->parent.name);
                rt_kprintf("the first sector failed.\r\n");
                rt_kprintf("maybe readonly!\r\n");
                goto __return;
            }

            /* write the second sector */
            sector_no = 1;
            data_point = write_buffer;
            *data_point++ = (rt_uint8_t)sector_no;
            i = rt_device_write(device,sector_no,write_buffer,1);
            if( i != 1 )
            {
                rt_kprintf("write device :%s ",device->parent.name);
                rt_kprintf("the second sector failed.\r\n");
                goto __return;
            }

            /* write the end sector */
            sector_no = geometry.sector_count-1;
            data_point = write_buffer;
            *data_point++ = (rt_uint8_t)sector_no;
            i = rt_device_write(device,sector_no,write_buffer,1);
            if( i != 1 )
            {
                rt_kprintf("write device :%s ",device->parent.name);
                rt_kprintf("the end sector failed.\r\n");
                goto __return;
            }

            /* verify first sector */
            sector_no = 0;
            i = rt_device_read(device,sector_no,read_buffer,1);
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

            /* verify sector sector */
            sector_no = 1;
            i = rt_device_read(device,sector_no,read_buffer,1);
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

            /* verify the end sector */
            sector_no = geometry.sector_count-1;
            i = rt_device_read(device,sector_no,read_buffer,1);
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
            rt_kprintf("device R/W test pass!\r\n");

        } /* step 3: I/O R/W test */

        rt_kprintf("\r\nRT_TICK_PER_SECOND:%d\r\n", RT_TICK_PER_SECOND);

        // step 4: continuous single sector speed test
        {
            rt_uint32_t tick_start,tick_end;
            rt_uint32_t i;

            rt_kprintf("\r\ncontinuous single sector speed test:\r\n");

            if( geometry.sector_count < 10 )
            {
                rt_kprintf("device sector_count < 10, speed test abort!\r\n");
            }
            else
            {
                unsigned int sector;

                // sign sector write
                rt_kprintf("write: ");
                sector = 0;
                tick_start = rt_tick_get();
                for(i=0; i<200; i++)
                {
                    sector += rt_device_write(device, i, read_buffer, 1);
                    if((i != 0) && ((i%4) == 0) )
                    {
                        if(sector < 4)
                        {
                            rt_kprintf("#");
                        }
                        else
                        {
                            rt_kprintf("<");
                        }
                        sector = 0;
                    }
                }
                tick_end = rt_tick_get();
                rt_kprintf("\r\nwrite 200 sector from %d to %d, ",tick_start,tick_end);
                calculate_speed_print( (geometry.bytes_per_sector*200UL*RT_TICK_PER_SECOND)/(tick_end-tick_start) );
                rt_kprintf("\r\n");

                // sign sector read
                rt_kprintf("read : ");
                sector = 0;
                tick_start = rt_tick_get();
                for(i=0; i<200; i++)
                {
                    sector += rt_device_read(device, i, read_buffer, 1);
                    if((i != 0) && ((i%4) == 0) )
                    {
                        if(sector < 4)
                        {
                            rt_kprintf("#");
                        }
                        else
                        {
                            rt_kprintf(">");
                        }
                        sector = 0;
                    }
                }
                tick_end = rt_tick_get();
                rt_kprintf("\r\nread 200 sector from %d to %d, ",tick_start,tick_end);
                calculate_speed_print( (geometry.bytes_per_sector*200UL*RT_TICK_PER_SECOND)/(tick_end-tick_start) );
                rt_kprintf("\r\n");
            }
        }// step 4: speed test

        // step 5: random single sector speed test
        {
            rt_uint32_t tick_start,tick_end;
            rt_uint32_t i;

            rt_kprintf("\r\nrandom single sector speed test:\r\n");

            if( geometry.sector_count < 10 )
            {
                rt_kprintf("device sector_count < 10, speed test abort!\r\n");
            }
            else
            {
                unsigned int sector;

                // sign sector write
                rt_kprintf("write: ");
                sector = 0;
                tick_start = rt_tick_get();
                for(i=0; i<200; i++)
                {
                    sector += rt_device_write(device, (geometry.sector_count / 10) * (i%10) + (i%10), read_buffer, 1);
                    if((i != 0) && ((i%4) == 0) )
                    {
                        if(sector < 4)
                        {
                            rt_kprintf("#");
                        }
                        else
                        {
                            rt_kprintf("<");
                        }
                        sector = 0;
                    }
                }
                tick_end = rt_tick_get();
                rt_kprintf("\r\nwrite 200 sector from %d to %d, ",tick_start,tick_end);
                calculate_speed_print( (geometry.bytes_per_sector*200UL*RT_TICK_PER_SECOND)/(tick_end-tick_start) );
                rt_kprintf("\r\n");

                // sign sector read
                rt_kprintf("read : ");
                sector = 0;
                tick_start = rt_tick_get();
                for(i=0; i<200; i++)
                {
                    sector += rt_device_read(device, (geometry.sector_count / 10) * (i%10) + (i%10), read_buffer, 1);
                    if((i != 0) && ((i%4) == 0) )
                    {
                        if(sector < 4)
                        {
                            rt_kprintf("#");
                        }
                        else
                        {
                            rt_kprintf(">");
                        }
                        sector = 0;
                    }
                }
                tick_end = rt_tick_get();
                rt_kprintf("\r\nread 200 sector from %d to %d, ",tick_start,tick_end);
                calculate_speed_print( (geometry.bytes_per_sector*200UL*RT_TICK_PER_SECOND)/(tick_end-tick_start) );
                rt_kprintf("\r\n");
            }
        }// step 4: speed test

        /* step 6: multiple sector speed test */
        {
            rt_uint8_t * multiple_buffer;
            rt_uint8_t * ptr;
            rt_uint32_t tick_start,tick_end;
            rt_uint32_t sector,i;

            rt_kprintf("\r\nmultiple sector speed test\r\n");

            for(sector=2; sector<256; sector=sector*2)
            {
                multiple_buffer = rt_malloc(geometry.bytes_per_sector * sector);

                if(multiple_buffer == RT_NULL)
                {
                    rt_kprintf("no memory for %d sector! multiple sector speed test abort!\r\n", sector);
                    break;
                }

                rt_memset(multiple_buffer, sector, geometry.bytes_per_sector * sector);
                rt_kprintf("write: ");
                tick_start = rt_tick_get();
                for(i=0; i<10; i++)
                {
                    rt_size_t n;
                    n = rt_device_write(device, 50, multiple_buffer, sector);
                    if(n == sector)
                    {
                        rt_kprintf("<");
                    }
                    else
                    {
                        rt_kprintf("#");
                    }
                }
                tick_end = rt_tick_get();
                rt_kprintf("\r\n");
                rt_kprintf("multiple write %d sector speed : ", sector);
                calculate_speed_print( (geometry.bytes_per_sector * sector * 10 * RT_TICK_PER_SECOND)/(tick_end-tick_start) );
                rt_kprintf("\r\n");

                rt_memset(multiple_buffer, ~sector, geometry.bytes_per_sector * sector);
                rt_kprintf("read : ");
                tick_start = rt_tick_get();
                for(i=0; i<10; i++)
                {
                    rt_size_t n;
                    n = rt_device_read(device, 50, multiple_buffer, sector);
                    if(n == sector)
                    {
                        rt_kprintf(">");
                    }
                    else
                    {
                        rt_kprintf("#");
                    }
                }
                tick_end = rt_tick_get();
                rt_kprintf("\r\n");
                rt_kprintf("multiple read %d sector speed : ", sector);
                calculate_speed_print( (geometry.bytes_per_sector * sector * 10 * RT_TICK_PER_SECOND)/(tick_end-tick_start) );

                ptr = multiple_buffer;
                for(i=0; i<geometry.bytes_per_sector * sector; i++)
                {
                    if(*ptr != sector)
                    {
                        rt_kprintf(" but data verify fail!");
                        break;
                    }
                    ptr++;
                }
                rt_kprintf("\r\n\r\n");

                rt_free(multiple_buffer);
            }
        } /* step 5: multiple sector speed test */

        rt_device_close(device);
        return RT_EOK;
    }// device can read and write.
    else
    {
        // device read only
        rt_device_close(device);
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
    rt_device_close(device);
    return RT_ERROR;
}

int device_test(const char * device_name)
{
    rt_device_t device = RT_NULL;

    // step 1:find device
    device = rt_device_find(device_name);
    if( device == RT_NULL)
    {
        rt_kprintf("device %s: not found!\r\n", device_name);
        return RT_ERROR;
    }

    // step 2:init device
    if (!(device->flag & RT_DEVICE_FLAG_ACTIVATED))
    {
        rt_err_t result;
        result = rt_device_init(device);
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
FINSH_FUNCTION_EXPORT(device_test, e.g: device_test("sd0"));
#endif

