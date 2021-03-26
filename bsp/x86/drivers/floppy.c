/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 */
#include <rtthread.h>
#include <rthw.h>

#include <bsp.h>

typedef rt_uint8_t  u8;
typedef rt_uint16_t u16;
typedef rt_uint32_t u32;

typedef rt_int8_t  s8;
typedef rt_int16_t s16;
typedef rt_int32_t s32;

#define OUTB(v,p) outb(p,v)

#include "floppy.h"
#include "dma.h"

#define SECTOR_SIZE 512
#define panic(str,...) do { rt_kprintf("panic::" str,##__VA_ARGS__); while(1); } while(0)

#define _local_irq_save(level) level = rt_hw_interrupt_disable()
#define _local_irq_restore(level) rt_hw_interrupt_enable(level)

static u8 floppy_buffer[512];                       /* 软盘高速缓冲区地址指针 */

#define MAX_REPLIES 7
static u8 floppy_reply_buffer[MAX_REPLIES];         /* 软驱回应缓冲区 */
#define ST0 (floppy_reply_buffer[0])                /* 软驱回应0号字节 */
#define ST1 (floppy_reply_buffer[1])                /* 软驱回应1号字节 */
#define ST2 (floppy_reply_buffer[2])                /* 软驱回应2号字节 */
#define ST3 (floppy_reply_buffer[3])                /* 软驱回应3号字节 */


static char *floppy_inc_name;                       /* 软驱型号名 */
static char *floppy_type;
static u32  floppy_motor=0;                         /* 软驱马达状态字节 */
static u32  floppy_size =0;
/**********************功能函数***************************/
static void floppy_result(void);                    /* 获得软驱响应状态  */
static u32  floppy_sendbyte(u32);                   /* 向软驱控制寄存器发送一个控制字节  */
static u32  floppy_getbyte(void);                   /* 从软驱数据寄存器得到一个数据字节  */
static u32  floppy_get_info(void);                  /* 得到软驱信息  */
static void floppy_motorOn(void);                   /* 打开软驱马达  */
static void floppy_motorOff(void);                  /* 关闭软驱马达  */
static void floppy_setmode(void);                   /* 软驱模式设置  */
static void block_to_hts(u32, u32*, u32*, u32*);    /* 逻辑块转为磁盘头、磁道号和扇区号  */
static void floppy_setupDMA(void);                  /* 设置软驱DMA通道  */
static void floppy_read_cmd(u32 blk);               /* 从软盘上读取指定的逻辑块到缓冲区  */


void floppy_result(void)
{
    u8 stat, i,count;
    i=0;
    for(count=0; count<0xFF; count++)
    {
        stat = inb( FD_STATUS ) & (STATUS_READY|STATUS_DIR|STATUS_BUSY); //读取状态寄存器
        if (stat == STATUS_READY)
            return;
        if (stat == (STATUS_READY|STATUS_DIR|STATUS_BUSY))
        {
            if(i>7) break;
            floppy_reply_buffer[i++]=inb_p(FD_DATA);
        }
    }

    panic("Get floppy status times out !\n");
}

u32 floppy_sendbyte( u32 value )
{
    u8 stat, i;

    for ( i = 0; i < 128; i++ ) {
        stat = inb( FD_STATUS ) & (STATUS_READY|STATUS_DIR);    //读取状态寄存器
        if  ( stat  == STATUS_READY )
        {
            OUTB( value ,FD_DATA);                              //将参数写入数据寄存器
            return 1;
        }
        io_delay();                                             // 作一些延迟
    }
    return 0;
}


u32 floppy_getbyte(void)
{
    u8 stat, i;

    for ( i = 0; i < 128; i++ ) {
        stat = inb( FD_STATUS ) & (STATUS_READY|STATUS_DIR|STATUS_BUSY); //读取状态寄存器
        if (stat == STATUS_READY)
            return -1;
        if ( stat  == 0xD0 )
            return inb(FD_DATA);
        io_delay();
    }
    return 0;
}


u32 floppy_get_info(void)
{
    u32 i;
    u8 CmType, FdType;

    floppy_sendbyte(0x10);
    i = floppy_getbyte();

    switch (i)
    {
        case 0x80:   floppy_inc_name = "NEC765A controller"; break;
        case 0x90:   floppy_inc_name = "NEC765B controller"; break;
        default:     floppy_inc_name = "Enhanced controller"; break;
    }

    CmType = readcmos(0x10);        //read floppy type from cmos
    FdType   = (CmType>>4) & 0x07;

    if ( FdType == 0 )
        panic("Floppy driver not found!");

    switch( FdType )
    {
    case 0x02: // 1.2MB
        floppy_type = "1.2MB";
        floppy_size = 2458*512;
    break;

    case 0x04: // 1.44MB       标准软盘
        floppy_type = "1.44MB";
        floppy_size = 2880*512;
        break;

    case 0x05: // 2.88MB
        floppy_type = "2.88MB";
        floppy_size = 2*2880*512;
        break;
    }
    return 1;
}


void floppy_motorOn( void )
{
    u32 eflags;
    if (!floppy_motor)
    {
        _local_irq_save(eflags);
        OUTB(28,FD_DOR);
        floppy_motor = 1;
        _local_irq_restore(eflags);
    }
    return;
}


void floppy_motorOff( void )
{
    u32 eflags;
    if (floppy_motor)
    {
        _local_irq_save(eflags);
        OUTB(12,FD_DOR);
        floppy_motor = 0;
        _local_irq_restore(eflags);

    }
    return;
}


void floppy_setmode(void)
{
    floppy_sendbyte (FD_SPECIFY);
    floppy_sendbyte (0xcf);
    floppy_sendbyte (0x06);
    OUTB (0,FD_DCR);
}


void block_to_hts(u32 block, u32 *head, u32 *track, u32 *sector )
{
    *head = ( block % ( 18 * 2 ) ) /18;
    *track =  block / ( 18 * 2 );
    *sector = block % 18 + 1;
}


void floppy_setupDMA(void)
{
    u32 eflags;
    _local_irq_save(eflags);
    DisableDma(2);
    ClearDmaFF(2);
    SetDmaMode(2,DMA_MODE_READ);
    SetDmaAddr(2,(unsigned long)floppy_buffer);
    SetDmaCount(2,512);
    EnableDma(2);
    _local_irq_restore(eflags);
}


void floppy_read_cmd(u32 blk)
{
    u32 head;
    u32 track;
    u32 sector;

    block_to_hts(blk,&head,&track,&sector);

    floppy_motorOn();
    io_delay();

    floppy_setupDMA();
    io_delay();

    floppy_setmode();
    io_delay();
    floppy_sendbyte (FD_READ);                  //send read command
    floppy_sendbyte (head*4 + 0);
    floppy_sendbyte (track);                    /*  Cylinder  */
    floppy_sendbyte (head);                     /*  Head  */
    floppy_sendbyte (sector);                   /*  Sector  */
    floppy_sendbyte (2);                        /*  0=128, 1=256, 2=512, 3=1024, ...  */
    floppy_sendbyte (18);
    //floppy_sendbyte (sector+secs-1);          /*  Last sector in track:here are  sectors count */
    floppy_sendbyte (0x1B);
    floppy_sendbyte (0xff);
    return;
}

static struct rt_device devF;
static struct rt_mutex lock;
static struct rt_semaphore sem;

/* RT-Thread device interface */

static rt_err_t rt_floppy_init_internal(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t rt_floppy_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_floppy_close(rt_device_t dev)
{
    return RT_EOK;
}

/* position: block page address, not bytes address
 * buffer:
 * size  : how many blocks
 */
static rt_size_t rt_floppy_read(rt_device_t device, rt_off_t position, void *buffer, rt_size_t size)
{
    rt_size_t doSize = size;

    rt_mutex_take(&lock, RT_WAITING_FOREVER);
    while(size>0)
    {
        floppy_read_cmd(position);

        rt_sem_take(&sem, RT_WAITING_FOREVER); /* waiting isr sem forever */

        floppy_result();
        io_delay();

        if(ST1 != 0 || ST2 != 0)
        {
            panic("ST0 %d ST1 %d ST2 %d\n",ST0,ST1,ST2);
        }

        rt_memcpy(buffer, floppy_buffer, 512);

        floppy_motorOff();
        io_delay();

        position += 1;
        size     -= 1;
    }
    rt_mutex_release(&lock);

    return doSize;
}

/* position: block page address, not bytes address
 * buffer:
 * size  : how many blocks
 */
static rt_size_t rt_floppy_write(rt_device_t device, rt_off_t position, const void *buffer, rt_size_t size)
{
    rt_mutex_take(&lock, RT_WAITING_FOREVER);
    panic("FIXME:I don't know how!\n");
    rt_mutex_release(&lock);
    return size;
}

static rt_err_t rt_floppy_control(rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev != RT_NULL);

    if (cmd == RT_DEVICE_CTRL_BLK_GETGEOME)
    {
        struct rt_device_blk_geometry *geometry;

        geometry = (struct rt_device_blk_geometry *)args;
        if (geometry == RT_NULL) return -RT_ERROR;

        geometry->bytes_per_sector = SECTOR_SIZE;
        geometry->block_size = SECTOR_SIZE;

        geometry->sector_count = floppy_size / SECTOR_SIZE;
    }

    return RT_EOK;
}

static void rt_floppy_isr(int vector, void* param)
{
    (void)vector;
    (void)param;
    rt_sem_release(&sem);
}

void rt_floppy_init(void)
{
    struct rt_device *device;

    rt_mutex_init(&lock,"fdlock", RT_IPC_FLAG_FIFO);
    rt_sem_init(&sem, "fdsem", 0, RT_IPC_FLAG_FIFO);

    rt_hw_interrupt_install(FLOPPY_IRQ, rt_floppy_isr, RT_NULL, "floppy");
    rt_hw_interrupt_umask(FLOPPY_IRQ);

    floppy_get_info();
    rt_kprintf("Floppy Inc : %s  Floppy Type : %s\n",floppy_inc_name,floppy_type);

    device = &(devF);

    device->type  = RT_Device_Class_Block;
    device->init = rt_floppy_init_internal;
    device->open = rt_floppy_open;
    device->close = rt_floppy_close;
    device->read = rt_floppy_read;
    device->write = rt_floppy_write;
    device->control = rt_floppy_control;
    device->user_data = NULL;

    rt_device_register(device, "floppy",
                       RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE | RT_DEVICE_FLAG_STANDALONE);

}
