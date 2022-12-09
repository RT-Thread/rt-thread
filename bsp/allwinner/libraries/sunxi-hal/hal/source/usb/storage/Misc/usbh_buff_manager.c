/*
********************************************************************************************************************
*                                              usb_host
*
*                              (c) Copyright 2007-2009, holi.China
*                                       All Rights Reserved
*
* File Name     : usbh_buff_manager.c
*
* Author        : javen
*
* Version       : 2.0
*
* Date          : 2009.08.19
*
* Description   : 启用缓存机制，用来提高USBH的读写速度.
*                 当fs_buffer < 32k的时候，这种机制才有效
*                 当fs_buffer >= 32k的时候，这种机制反而会影响速度
*                 当fs_buffer的地址是不连续的地址，必须用这种机制, 因为dma读写必须保证是连续的物理地址
*
* 注:  缓存管理的基础是device处于连接状态. 如果device被拔走了, 必须重新配置buff
*
* History       :
*     v1.0  holi  2008.11.22 - 读写速度快, 但是只支持单个lun
*     v2.0  javen 2009.08.19 - 支持多个lun 和 多种类型的设备, 但是读写速度不如以前
********************************************************************************************************************
*/
#include "usb_os_platform.h"
#include "usbh_buff_manager.h"
#include  "error.h"
#include  "usb_msc_i.h"

static usbh_buff_manager_t usbh_buff_manager;

typedef int(* buff_blk_func_t)(void *pBuffer, unsigned int blk, unsigned int n, void *hDev);


/* usbh_temp_buff的最大长度 */
static unsigned int usbh_temp_buff_max_len(void)
{
    return usbh_buff_manager.temp_buff_len;
}

/*
*********************************************************************
*                     set_usbh_temp_buff_default
*
* Description:
*     初始化一个usbh_temp_buff
* Arguments:
*
* Returns:
*
* note:
*
*
*********************************************************************
*/
static void set_usbh_temp_buff_default(usbh_temp_buff_t *temp_buff)
{
    unsigned int cpu_sr = 0;

    if (temp_buff == NULL)
    {
        //DMSG_PANIC("ERR: set_usbh_temp_buff_default: input error\n");
        //DMSG_PANIC("ERR: temp_buff = 0x%x\n", temp_buff);
        return ;
    }

    ENTER_CRITICAL(cpu_sr);
    temp_buff->dev_id        = 0xffffffff;
    temp_buff->start_lba     = 0;
    temp_buff->end_lba       = 0;
    temp_buff->sector_size   = 0;
    temp_buff->used_time     = 0;
    temp_buff->is_valid      = 0;
    temp_buff->is_busy       = 0;
    memset(temp_buff->buff, 0, temp_buff->buff_len);
    EXIT_CRITICAL(cpu_sr);
}

/* 设置目标buff为busy状态, 此时buff的状态不允许被修改。
 *
 * usbh_temp_buff在使用dma接收数据期间, 可能有blk_read或者blk_write
 * 请求试图去修改buff的属性, 如设置buff为无效。busy状态可以防止这样的
 * 事情发生
 */
static void set_usbh_temp_buff_busy(unsigned int buff_num)
{
    usbh_buff_manager_t *buff_mgr = &usbh_buff_manager;
    unsigned int cpu_sr = 0;
    //unsigned int i = 0;

    if (buff_num >= buff_mgr->temp_buff_nr)
    {
        //DMSG_PANIC("ERR: set_usbh_temp_buff_busy: input error\n");
        //DMSG_PANIC("ERR: buff_num = 0x%x\n", buff_num);
        return ;
    }

    //for (i = 0; i < buff_mgr->temp_buff_nr; i++)
    {
        //if (buff_mgr->buff_array[i].buff == temp_buff)
        {
            ENTER_CRITICAL(cpu_sr);
            buff_mgr->buff_array[buff_num].is_busy = 1;
            EXIT_CRITICAL(cpu_sr);
        }
    }
}

/* 设置目标buff为不busy状态, 此时buff的状态允许被修改。 */
static void set_usbh_temp_buff_free(unsigned int buff_num)
{
    usbh_buff_manager_t *buff_mgr = &usbh_buff_manager;
    unsigned int cpu_sr = 0;
    //unsigned int i = 0;

    if (buff_num >= buff_mgr->temp_buff_nr)
    {
        //DMSG_PANIC("ERR: set_usbh_temp_buff_free: input error\n");
        //DMSG_PANIC("ERR: buff_num = 0x%x\n", buff_num);
        return ;
    }

    //for (i = 0; i < buff_mgr->temp_buff_nr; i++)
    {
        //if (buff_mgr->buff_array[i].buff == temp_buff)
        {
            ENTER_CRITICAL(cpu_sr);
            buff_mgr->buff_array[buff_num].is_busy = 0;
            EXIT_CRITICAL(cpu_sr);
        }
    }
}

/*
*********************************************************************
*                     set_usbh_temp_buff_valid
*
* Description:
*     如果成功的装载了device的数据, 就认为这个buffer是有效的
* Arguments:
*     buff         :  input.  待设置有效的buff
*     dev_id       :  input.  设备标识符
*     start_lba    :  input.  起始扇区
*     sector_size  :  input.  扇区大小
* Returns:
*
* note:
*
*
*********************************************************************
*/
static int set_usbh_temp_buff_valid(unsigned int buff_num, unsigned int dev_id, unsigned int start_lba, unsigned int sector_size)
{
    usbh_buff_manager_t *buff_mgr = &usbh_buff_manager;
    //unsigned int i = 0;
    unsigned int cpu_sr = 0;

    if (buff_num >= buff_mgr->temp_buff_nr || sector_size == 0)
    {
        //DMSG_PANIC("ERR: set_usbh_temp_buff_valid: input error\n");
        //DMSG_PANIC("ERR: buff_num = %d, sector_size = 0x%x\n", buff_num, sector_size);
        return -1;
    }

    //for (i = 0; i < buff_mgr->temp_buff_nr; i++)
    {
        //设置buff有效，并且保存它所记录的起始扇区
        //if (buff_mgr->buff_array[i].buff == buff)
        {
            ENTER_CRITICAL(cpu_sr);
            buff_mgr->buff_array[buff_num].dev_id        = dev_id;
            buff_mgr->buff_array[buff_num].sector_size   = sector_size;
            buff_mgr->buff_array[buff_num].start_lba     = start_lba;
            buff_mgr->buff_array[buff_num].end_lba       = start_lba + (buff_mgr->buff_array[buff_num].buff_len / sector_size) - 1;
            buff_mgr->buff_array[buff_num].used_time     = 1;  /* 第一次被fs使用 */
            buff_mgr->buff_array[buff_num].is_valid      = 1;
            EXIT_CRITICAL(cpu_sr);
            /*
                        //DMSG_TEMP_TEST("valid buffer is %d, start_lba = %d, end_lba = %d\n",
                                  i, start_lba, buff_mgr->buff_array[i].end_lba);
            */
            return 0;
        }
    }

    ////DMSG_PANIC("ERR: the buff is not belong to usbh temp buff manager\n");
    //return -1;
}

/*
***************************************************************************
*                     set_usbh_temp_buff_invalid
*
* Description:
*     设置dev的某一个buff无效。lba内容的落到buffer内,就认为次buffer无效
* Arguments:
*     dev_id  :  input.  用来确定设备的身份
*     lba     :  input.  用来查找buff
* Returns:
*     返回成功与失败
* note:
*
*
***************************************************************************
*/
static int set_usbh_temp_buff_invalid(unsigned int dev_id, unsigned int lba)
{
    usbh_buff_manager_t *buff_mgr = &usbh_buff_manager;
    unsigned int i = 0;

    for (i = 0; i < buff_mgr->temp_buff_nr; i++)
    {
        //设置dev的lba的buff无效
        if ((buff_mgr->buff_array[i].dev_id == dev_id)
            && (buff_mgr->buff_array[i].start_lba <= lba)
            && (lba <= buff_mgr->buff_array[i].end_lba))
        {
            set_usbh_temp_buff_default(&(buff_mgr->buff_array[i]));
        }
    }

    return 0;
}

/*
*********************************************************************
*                     set_usbh_temp_buff_invalid_by_dev
*
* Description:
*     设置和dev_id匹配的buff无效
* Arguments:
*     dev_id  :  input.  用来确定设备的身份
* Returns:
*     返回成功与失败
* note:
*
*
*********************************************************************
*/
int set_usbh_temp_buff_invalid_by_dev(unsigned int dev_id)
{
    usbh_buff_manager_t *buff_mgr = &usbh_buff_manager;
    unsigned int i = 0;

    for (i = 0; i < buff_mgr->temp_buff_nr; i++)
    {
        //与dev_id匹配的所有的buff都无效
        if (buff_mgr->buff_array[i].dev_id == dev_id)
        {
            set_usbh_temp_buff_default(&(buff_mgr->buff_array[i]));
        }
    }

    return 0;
}

/*
*********************************************************************
*                     set_usbh_temp_buff_invalid
*
* Description:
*     设置和dev_id匹配的buff无效
* Arguments:
*     dev_id  :  input.  用来确定设备的身份
* Returns:
*     返回成功与失败
* note:
*
*********************************************************************
*/
int set_all_usbh_temp_buff_invalid(void)
{
    usbh_buff_manager_t *buff_mgr = &usbh_buff_manager;
    unsigned int i = 0;

    for (i = 0; i < buff_mgr->temp_buff_nr; i++)
    {
        set_usbh_temp_buff_default(&(buff_mgr->buff_array[i]));
    }

    return 0;
}

/*
*********************************************************************
*                     select_invalid_usbh_temp_buff
*
* Description:
*     选择一个没有用的buff，用来转载device的数据
* Arguments:
*
* Returns:
*
* note:
*   挑选的策略为:
*       1、buff处于busy状态, 不选
*       2、挑选invalid buff
*       3、挑选valid buff里面被fs使用次数最少的一个buff
*       4、所有的buff的bit次数一样, 就按顺序挑选一个非busy的buff
*       5、以上条件都不满足, 挑选失败, 返回NULL
*
*
*********************************************************************
*/
static void *select_invalid_usbh_temp_buff(unsigned int *buff_num)
{
    usbh_buff_manager_t *buff_mgr = &usbh_buff_manager;
    void *temp_buff = NULL;
    unsigned int min_used = 0xffffffff;       //最小的使用次数
    //unsigned int buff_num = 0;               //被选中的buff的号
    unsigned int i = 0;

    if (buff_num == NULL)
    {
        return NULL;
    }

    //--<1>--挑选invalid的buffer
    for (i = 0; i < buff_mgr->temp_buff_nr; i++)
    {
        //--<1-1>--设备处于busy状态, 就去挑选下一个
        if (buff_mgr->buff_array[i].is_busy)
        {
            continue;
        }

        //--<1-2>--挑选invalid的buffer
        if (buff_mgr->buff_array[i].is_valid == 0)
        {
            temp_buff = buff_mgr->buff_array[i].buff;
            *buff_num  = i;
            set_usbh_temp_buff_default(&(buff_mgr->buff_array[*buff_num]));
            return temp_buff;
        }

        //--<1-3>--buffer都有效，就去挑选被fs使用次数最少的一个buff
        if (min_used > buff_mgr->buff_array[i].used_time)
        {
            min_used  = buff_mgr->buff_array[i].used_time;
            *buff_num  = i;
            temp_buff = buff_mgr->buff_array[i].buff;
        }

        //--<1-4>--在每次挑选的过程中, used_time除2
        //如果在下一次挑选之前, 又被fs使用, 这样它又慢慢生长了； 否则，会慢慢老去
        buff_mgr->buff_array[i].used_time = buff_mgr->buff_array[i].used_time >> 1;
    }

    //--<2>--挑选被fs使用次数最少的buffer
    if (min_used != 0xffffffff)
    {
        set_usbh_temp_buff_default(&(buff_mgr->buff_array[*buff_num]));
        return temp_buff;
    }

    //--<3>--没有找到理想的buffer就按顺序挑选一个不常用的,
    for (i = 0; i < buff_mgr->temp_buff_nr; i++)
    {
        if (buff_mgr->buff_array[i].is_busy == 0)
        {
            temp_buff = buff_mgr->buff_array[i].buff;
            *buff_num  = i;
            set_usbh_temp_buff_default(&(buff_mgr->buff_array[*buff_num]));
            return temp_buff;
        }
    }

    //--<4>--所有的buff都处于busy状态, 就无buff可用了
    temp_buff = NULL;
    return temp_buff;
}

/* 选择最优的buffer, 返回最优的buffer号 */
static int select_best_buffer(unsigned int dev_id, unsigned int lba, unsigned int size, unsigned int *nr)
{
    usbh_buff_manager_t *buff_mgr = &usbh_buff_manager;
    unsigned int max_len = 0;  /* 命中buffer里存放的最大数据长度 */
    unsigned int i = 0;

    for (i = 0; i < buff_mgr->temp_buff_nr; i++)
    {
        if ((dev_id == buff_mgr->buff_array[i].dev_id) && buff_mgr->buff_array[i].is_valid)
        {
            /* 落到了buffer内 */
            if (buff_mgr->buff_array[i].start_lba <= lba && buff_mgr->buff_array[i].end_lba >= lba)
            {
                if (max_len <= (buff_mgr->buff_array[i].end_lba - lba + 1))
                {
                    max_len = (buff_mgr->buff_array[i].end_lba - lba + 1);
                    *nr = i;
                }

                if (max_len >= size)
                {
                    break;
                }
            }
        }
    }

    if (i >= buff_mgr->temp_buff_nr && max_len == 0)
    {
        ////DMSG_PANIC("find best buffer find\n");
        *nr = 0xff;
        return -1;
    }

    return 0;
}

/*
******************************************************************************
*                     read_usbh_temp_buff
*
* Description:
*     如果成功的装载了device的数据, 就认为这个buffer是有效的
*
* Arguments:
*     dev_id  :  input.  用来查找指定设备的buff
*     lba     :  input.  本次读写的起始扇区
*     size    :  input.  本次读写的扇区个数
*     buff    :  output. 转载本次读的数据
*
* Returns:
*     is_copy = 1: 返回从buffer中读取的数据
*     is_copy = 0: 返回从buffer中最大效数据长度
*
* note:
*                     start     lba                 lba+size           end
*     usbh_temp_buff: |---------|----------------------|----------------|
*                               |----valid_sector------|
*                               |-------------left_sector---------------|
*
******************************************************************************
*/
static int read_usbh_temp_buff(unsigned int dev_id, unsigned int lba, unsigned int size, void *buff, unsigned int is_copy)
{
    usbh_buff_manager_t *buff_mgr = &usbh_buff_manager;
    unsigned int buff_start        = 0;  /* 数据在buff的起始地址       */
    unsigned int valid_sector      = 0;  /* buffer里的效数据长度       */
    unsigned int max_valid_sector  = 0;  /* buffer里的最大效数据长度   */
    unsigned int buff_len          = 0;  /* 本次读写数据的长度         */
    unsigned int buff_no           = 0;
#define min( x, y )          ( (x) < (y) ? (x) : (y) )

    if (buff == NULL)
    {
        //DMSG_PANIC("ERR: read_usbh_temp_buff: input error\n");
        return 0;
    }

    if (select_best_buffer(dev_id, lba, size, &buff_no) == 0)
    {
        max_valid_sector = buff_mgr->buff_array[buff_no].end_lba - lba + 1;

        if (is_copy)
        {
            buff_start  = (lba - buff_mgr->buff_array[buff_no].start_lba) * (buff_mgr->buff_array[buff_no].sector_size);
            valid_sector = min(size, max_valid_sector);
            buff_len    = valid_sector * (buff_mgr->buff_array[buff_no].sector_size);

            if (buff_mgr->buff_array[buff_no].buff == NULL)
            {
                //DMSG_PANIC("ERR: usbh temp buff had free, can not used\n");
                return -1;
            }

            //DMSG_TEMP_TEST("special buffer is %d, start_lba = %d, end_lba = %d\n",
                           //buff_no,
                           //buff_mgr->buff_array[buff_no].start_lba,
                           //buff_mgr->buff_array[buff_no].end_lba);
            buff_mgr->buff_array[buff_no].used_time++;
            memcpy(buff, (void *)((unsigned char *)(buff_mgr->buff_array[buff_no].buff) + buff_start), buff_len);
            return valid_sector;
        }
    }

    return max_valid_sector;
}

/*
******************************************************************************
*                     write_usbh_temp_buff
*
* Description:
*     数据在写入device之前, 更新usbh_temp_buff, 以便下次直接读取
* Arguments:
*     dev_id  :  input.  用来查找指定设备的buff
*     lba     :  input.  本次读写的起始扇区
*     size    :  input.  本次读写的扇区个数
*     buff    :  input.  转载本次写的数据
*
* Returns:
*     返回写成功的buff地址
* note:
*
*
******************************************************************************
*/
static void *write_usbh_temp_buff(unsigned int dev_id, unsigned int lba, unsigned int size, const void *buff)
{
    usbh_buff_manager_t *buff_mgr = &usbh_buff_manager;
    unsigned int buff_start  = 0;  /* 数据在buff的起始地址 */
    unsigned int buff_len    = 0;  /* 本次读写数据的长度 */
    unsigned int i           = 0;

    if (buff == NULL)
    {
        //DMSG_PANIC("ERR: write_usbh_temp_buff: input error\n");
        return NULL;
    }

    //--<1>--在现有的buff里面去寻找合适的buff
    for (i = 0; i < buff_mgr->temp_buff_nr; i++)
    {
        //dev_id匹配, 并且这个buff有效, 就去确认本次读写的lba是否完整的落在buff内
        if ((dev_id == buff_mgr->buff_array[i].dev_id) && buff_mgr->buff_array[i].is_valid)
        {
            //要读的lba落在buff内, 并且size没有超出buff的范围, 就可以直接更新了
            if ((buff_mgr->buff_array[i].start_lba <= (lba + size))
                && ((lba + size) < buff_mgr->buff_array[i].end_lba)
                && (buff_mgr->buff_array[i].start_lba <= lba)
                && (lba < buff_mgr->buff_array[i].end_lba))
            {
                buff_start = (lba - buff_mgr->buff_array[i].start_lba) * (buff_mgr->buff_array[i].sector_size);
                buff_len   = size * (buff_mgr->buff_array[i].sector_size);

                if (buff_mgr->buff_array[i].buff == NULL)
                {
                    //DMSG_PANIC("ERR: usbh temp buff had free, can not used\n");
                    return NULL;
                }

                buff_mgr->buff_array[i].used_time++;
                memcpy((void *)((unsigned char *)(buff_mgr->buff_array[i].buff) + buff_start), buff, buff_len);
                //这里返回blk的偏移地址
                //return buff_mgr->buff_array[i].buff;
                return (void *)((unsigned char *)(buff_mgr->buff_array[i].buff) + buff_start);
            }
        }
    }

    return NULL;
}

/*
********************************************************************************************************
*                     usbh_msc_special_read
*
* Description:
*     通过usbh_temp_buff管理来读取设备的数据, 如果usbh_temp_buff里面有
* 想要的数据，就从usbh_temp_buff里读。否则直接向device读取数据。
*
* Arguments:
*     pBuffer           :  output. 接收本次读的数据
*     blk               :  input.  本次读写的起始扇区
*     n                 :  input.  本次读写的扇区个数
*     hDev              :  input.  设备句柄
*     dev_id            :  input.  设备号
*     blk_read_entry    :  input.  块设备读函数的入口, 如sd_read.
*
* Returns:
*     返回读成功的blk数
* note:
*
*  usbh_temp_buff读的策略是:
*
*      1、user buffer size小于usb temp buffer size
*      (1)、查询单个temp buffer里有多少有效数据, 查询有效数据最大的哪个buffer
*      (2)、如果满足user buffer的要求, 就返回。
*      (3)、如果不能够满足，就开启另外一个usb temp buffer
*           从device取数据，把有效数据copy到user buffer中。
*
*      2、user buffer size大于等于usb temp buffer size
*      (1)、从usb temp buffer里取有效数据
*      (2)、如果剩余数据大于等于usb temp buffer size，就直接用user buffer从设备取数据
*      (3)、如果剩余数据小于usb temp buffer size，就开启另外一个usb temp buffer
*           从device取数据，把有效数据copy到user buffer中。
*
********************************************************************************************************
*/
#if 1
int usbh_msc_special_read(void *pBuffer,
                          unsigned int blk,
                          unsigned int n,
                          void *hDev,
                          unsigned int dev_id,
                          unsigned int secter_size,
                          void *blk_read_entry)
{
    unsigned char *Buffer_temp   = (unsigned char *)pBuffer;
    unsigned int temp_sector_1 = 0;            //本次所要读写的数据长度
    unsigned int total_len     = 0;            //本次所要读写的数据长度
    unsigned int left_sector   = 0;            /* 剩余扇区个数  */
    //  unsigned int sector_nr     = 0;            //本次成功读取的扇区个数
    void *usbh_temp_buff = NULL;        //usbh_temp_buff
    usbh_buff_manager_t *buff_mgr = &usbh_buff_manager;
    buff_blk_func_t buff_blk_read;

    //--<1>--check input
    if (pBuffer == NULL || n == 0 || hDev == NULL || blk_read_entry == NULL)
    {
        //DMSG_PANIC("ERR : usbh_msc_special_read: input is error\n");
        //DMSG_PANIC("ERR : usbh_msc_special_read: pBuffer = 0x%x, n = %d, hDev = 0x%x,blk_read  = 0x%x\n",
        //           pBuffer, n, hDev, blk_read_entry);
        return 0;
    }

    //DMSG_TEMP_TEST("read: --<1-0>--, Buffer_temp_s = %x, Buffer_temp_e = %x\n",
    //               Buffer_temp, (Buffer_temp + n * secter_size));
    buff_blk_read  = (buff_blk_func_t)blk_read_entry;
    total_len = (n * secter_size);

    if (total_len < usbh_temp_buff_max_len())
    {
        unsigned int buff_num = 0;
        //(1)、查询单个temp buffer里有多少有效数据, 查询有效数据最大的哪个buffer
        temp_sector_1 = read_usbh_temp_buff(dev_id, blk, n, pBuffer, 0);
        //DMSG_TEMP_TEST("read: --<1-1>--, secter_size = %d, blk = %d, n = %d, temp_sector_1 = %d\n",
         //              secter_size, blk, n, temp_sector_1);

        //(2)、如果满足user buffer的要求, 就返回。
        if (temp_sector_1 >= n)
        {
            ////DMSG_TEMP_TEST("read: --<1-2>--, secter_size = %d, blk = %d, n = %d, temp_sector_1 = %d\n",
            //               secter_size, blk, n, temp_sector_1);
            return read_usbh_temp_buff(dev_id, blk, n, pBuffer, 1);
        }

        /*
        (3)、如果不能够满足，就开启另外一个usb temp buffer
             从device取数据，把有效数据copy到user buffer中。
        */
        //--<3-1>--挑选一个无用的buff, 去device里取数据
        usbh_temp_buff = select_invalid_usbh_temp_buff(&buff_num);

        if (usbh_temp_buff == NULL)
        {
            //DMSG_PANIC("ERR: select_invalid_usbh_temp_buff failed\n");
            //既然不能再使用usbh_temp_buff了, 就直接读吧
            return buff_blk_read(pBuffer, blk, n, hDev);
        }

        //--<3-2>--从设备读数据
        set_usbh_temp_buff_busy(buff_num);
        temp_sector_1 = buff_blk_read(usbh_temp_buff, blk, buff_mgr->temp_buff_len / secter_size, hDev);
        set_usbh_temp_buff_free(buff_num);

        if (temp_sector_1 != (buff_mgr->temp_buff_len / secter_size))
        {
            //DMSG_PANIC("ERR: usbh_msc_special_read: buff_blk_read failed\n");
            return 0;
        }

        //--<3-3>--设置这个buff有效
        set_usbh_temp_buff_valid(buff_num, dev_id, blk, secter_size);
        //--<3-4>--把从设备读数据, 传递给fs
        memcpy(pBuffer, usbh_temp_buff, total_len);
        //DMSG_TEMP_TEST("memcpy1: pBuffer = %x,pBuffer_s = %x, pBuffer_e = %x\n",
                       //(unsigned int)pBuffer, Buffer_temp, Buffer_temp + total_len);
        //DMSG_TEMP_TEST("read: --<1-3>--, secter_size = %d, blk = %d, n = %d, total_len = %d\n",
                       //secter_size, blk, n, total_len);
        return n;
    }
    else
    {
        unsigned int buff_num = 0;
        //(1)、从usb temp buffer里取有效数据
        temp_sector_1 = read_usbh_temp_buff(dev_id, blk, n, pBuffer, 1);
        //DMSG_TEMP_TEST("read: --<2-1>--, secter_size = %d, blk = %d, n = %d, temp_sector_1 = %d\n",
                       //secter_size, blk, n, temp_sector_1);

        if (((n - temp_sector_1) * secter_size) >= usbh_temp_buff_max_len())
        {
            //(2)、如果剩余数据大于等于usb temp buffer size，就直接用user buffer从设备取数据
            left_sector = buff_blk_read(Buffer_temp + (temp_sector_1 * secter_size),
                                        (blk + temp_sector_1),
                                        (n - temp_sector_1),
                                        hDev);
            //DMSG_TEMP_TEST("read: --<2-2>--, secter_size = %d, blk = %d, n = %d, left_sector = %d\n",
                           //secter_size, blk, n, left_sector);
            //DMSG_TEMP_TEST("memcpy4: pBuffer_s = %x, pBuffer_e = %x\n",
                           //Buffer_temp + (temp_sector_1 * secter_size),
                           //Buffer_temp + (temp_sector_1 * secter_size) + ((n - temp_sector_1) * secter_size));

            if (left_sector)
            {
                return (left_sector + temp_sector_1);
            }
            else
            {
                return 0;  /* read faild */
            }
        }
        else
        {
            /* (3)、如果剩余数据小于usb temp buffer size，就开启另外一个usb temp buffer
                    从device取数据，把有效数据copy到user buffer中。 */
            //--<3-1>--挑选一个无用的buff, 去device里取数据
            usbh_temp_buff = select_invalid_usbh_temp_buff(&buff_num);

            if (usbh_temp_buff == NULL)
            {
                //DMSG_PANIC("ERR: select_invalid_usbh_temp_buff failed\n");
                //既然不能再使用usbh_temp_buff了, 就直接读吧
                return buff_blk_read(pBuffer, blk, n, hDev);
            }

            //--<3-2>--从设备读数据
            set_usbh_temp_buff_busy(buff_num);
            left_sector = buff_blk_read(usbh_temp_buff, (blk + temp_sector_1), buff_mgr->temp_buff_len / secter_size, hDev);
            set_usbh_temp_buff_free(buff_num);

            if (left_sector != (buff_mgr->temp_buff_len / secter_size))
            {
                //DMSG_PANIC("ERR: usbh_msc_special_read: buff_blk_read failed\n");
                return 0;
            }

            //--<3-3>--设置这个buff有效
            set_usbh_temp_buff_valid(buff_num, dev_id, (blk + temp_sector_1), secter_size);
            //--<3-4>--把从设备读数据, 传递给fs
            memcpy(Buffer_temp + (temp_sector_1 * secter_size),
                          usbh_temp_buff,
                         ((n - temp_sector_1) * secter_size));
            //DMSG_TEMP_TEST("memcpy2: pBuffer_s = %x, pBuffer_e = %x\n",
                          // Buffer_temp + (temp_sector_1 * secter_size),
                          // Buffer_temp + (temp_sector_1 * secter_size) + ((n - temp_sector_1) * secter_size));
            //DMSG_TEMP_TEST("read: --<2-3>--, secter_size = %d, blk = %d, n = %d, left_sector = %d\n",
                         //  secter_size, blk, n, (n - temp_sector_1));
            return n;
        }
    }
}
#else
/*
********************************************************************************************************
*                     usbh_msc_special_read
*
* Description:
*     通过usbh_temp_buff管理来读取设备的数据, 如果usbh_temp_buff里面有
* 想要的数据，就从usbh_temp_buff里读。否则直接向device读取数据。
*
* Arguments:
*     pBuffer           :  output. 接收本次读的数据
*     blk               :  input.  本次读写的起始扇区
*     n                 :  input.  本次读写的扇区个数
*     hDev              :  input.  设备句柄
*     dev_id            :  input.  设备号
*     blk_read_entry    :  input.  块设备读函数的入口, 如sd_read.
*
* Returns:
*     返回读成功的blk数
* note:
*
*  usbh_temp_buff读的策略是:
*
********************************************************************************************************
*/
int usbh_msc_special_read(void *pBuffer,
                          unsigned int blk,
                          unsigned int n,
                          void *hDev,
                          unsigned int dev_id,
                          unsigned int secter_size,
                          void *blk_read_entry)
{
    unsigned char *Buffer_temp = (unsigned char *)pBuffer;
    unsigned int this_len = 0;   //本次所要读写的数据长度
    unsigned int sector_nr = 0;  //本次成功读取的扇区个数
    void *usbh_temp_buff = NULL;   //usbh_temp_buff
    usbh_buff_manager_t *buff_mgr = &usbh_buff_manager;
    buff_blk_func_t buff_blk_read;

    //--<1>--check input
    if (pBuffer == NULL || n == 0 || hDev == NULL || blk_read_entry == NULL)
    {
        //DMSG_PANIC("ERR : usbh_msc_special_read: input is error\n");
        //DMSG_PANIC("ERR : usbh_msc_special_read: pBuffer = 0x%x, n = %d, hDev = 0x%x,blk_read  = 0x%x\n",
                   pBuffer, n, hDev, blk_read_entry);
        return 0;
    }

    //--<2>--满足如下之一, 就使用usbh_temp_buff
    /* 1、没有超出了usbh_temp_buff的最大范围
     * 2、pBuffer地址物理不连续
     * 3、地址不对其
     */
    sector_nr = n;
    this_len = n * secter_size;
    buff_blk_read  = (buff_blk_func_t)blk_read_entry;

    if (this_len <= usbh_temp_buff_max_len())
    {
        int ret = 0;
        //--<3-1>--尝试到usbh_temp_buff里读, 读成功就直接闪人
        /*
                if(read_usbh_temp_buff(dev_id, blk, n, pBuffer) == 0){
                    return sector_nr;
                }
        */
        sector_nr = read_usbh_temp_buff(dev_id, blk, n, pBuffer, 0);

        if (sector_nr)
        {
            /* 如果现有的buffer里面有一半以上的数据可用, 就先从buffer里取数据, 再向设备去剩余数据 */
            if (sector_nr /*> (n/2)*/)
            {
                sector_nr = read_usbh_temp_buff(dev_id, blk, n, pBuffer, 1);

                if (sector_nr < n)
                {
                    sector_nr += buff_blk_read(Buffer_temp + (sector_nr * secter_size),
                                               (blk + sector_nr),
                                               (n - sector_nr),
                                               hDev);
                }

                return sector_nr;
            }
        }

        //--<3-2>--挑选一个无用的buff, 去device里取数据
        usbh_temp_buff = select_invalid_usbh_temp_buff();

        if (usbh_temp_buff == NULL)
        {
            //DMSG_PANIC("ERR: select_invalid_usbh_temp_buff failed\n");
            //既然不能再使用usbh_temp_buff了, 就直接读吧
            return buff_blk_read(pBuffer, blk, n, hDev);
        }

        //--<3-3>--从设备读数据
        set_usbh_temp_buff_busy(usbh_temp_buff);
        ret = buff_blk_read(usbh_temp_buff, blk, buff_mgr->temp_buff_len / secter_size, hDev);
        set_usbh_temp_buff_free(usbh_temp_buff);

        if (ret != (buff_mgr->temp_buff_len / secter_size))
        {
            //DMSG_PANIC("ERR: usbh_msc_special_read: buff_blk_read failed\n");
            return 0;
        }

        //--<3-2-4>--设置这个buff有效
        set_usbh_temp_buff_valid(usbh_temp_buff, dev_id, blk, secter_size);
        //--<3-4>--把从设备读数据, 传递给fs
        memcpy(pBuffer, usbh_temp_buff, this_len);
        return n;
    }
    else
    {
        /*
         *******************************************************************
         * 大于32k读的时候, 不用usbh_temp_buff也就不用更新usbh_temp_buff了
         * usbh_temp_buff的内容依旧和device是同步的
         *******************************************************************
         */
        sector_nr = read_usbh_temp_buff(dev_id, blk, n, pBuffer, 1);

        if (sector_nr)
        {
            if (sector_nr < n)
            {
                sector_nr += buff_blk_read(Buffer_temp + (sector_nr * secter_size),
                                           (blk + sector_nr),
                                           (n - sector_nr),
                                           hDev);
            }
        }
        else
        {
            sector_nr = buff_blk_read(pBuffer, blk, n, hDev);
        }

        return sector_nr;
    }
}
#endif

/*
****************************************************************************
*                     usbh_msc_special_write
*
* Description:
*     通过usbh_temp_buff管理来读取设备的数据, 如果usbh_temp_buff里面有
* 想要的数据，就从usbh_temp_buff里读。否则直接向device读取数据。
*
* Arguments:
*     pBuffer           :  input.  要写入device的数据
*     blk               :  input.  本次读写的起始扇区
*     n                 :  input.  本次读写的扇区个数
*     hDev              :  input.  设备句柄
*     dev_id            :  input.  设备号
*     blk_write_entry   :  input.  块设备读函数的入口, 如sd_write.
*
* Returns:
*     返回读成功的blk数
* note:
*  满足如下之一, 就使用usbh_temp_buff
*      1、没有超出了usbh_temp_buff的最大范围
*      2、pBuffer地址物理不连续
*      3、地址不对其
*
*  usbh_temp_buff写的策略是:
*      1、data_len < 32k, pBuffer地址物理不连续, 地址不对其
*         (1)、尝试更新usbh_temp_buff成功, 就去写device
*         (2)、尝试更新usbh_temp_buff失败, 就把相关的usbh_temp_buff无效掉
*         (3)、掉选一个无效的buff，用来传输数据。(因为pbuffer可能是物理不连续的)
*
*      2、data_len >= 32k, pBuffer地址物理连续, 地址对其
*         (1)、把相关的usbh_temp_buff无效掉
*         (2)、掉选一个无效的buff, 更新。
*         (3)、设置这个buff有效

*
****************************************************************************
*/
int usbh_msc_special_write(void *pBuffer,
                           unsigned int blk,
                           unsigned int n,
                           void *hDev,
                           unsigned int dev_id,
                           unsigned int secter_size,
                           void *blk_write_entry)
{
    unsigned int this_len = 0;     //本次所要读写的数据长度
    void *usbh_temp_buff = NULL;   //usbh_temp_buff
    buff_blk_func_t buff_blk_write;

    //--<1>--check input
    if (pBuffer == NULL || n == 0 || hDev == NULL || blk_write_entry == NULL)
    {
        //DMSG_PANIC("ERR : usbh_msc_special_read: input is error\n");
        //DMSG_PANIC("ERR : usbh_msc_special_read: pBuffer = 0x%x, n = %d, hDev = 0x%x,blk_read  = 0x%x\n",
        //           pBuffer, n, hDev, blk_write_entry);
        return 0;
    }

    //--<3>--满足如下之一, 就使用usbh_temp_buff
    /* 1、没有超出了usbh_temp_buff的最大范围
     * 2、pBuffer地址物理不连续
     * 3、地址不对齐
     */
    this_len = n * secter_size;
    buff_blk_write = (buff_blk_func_t)blk_write_entry;

    if (this_len < usbh_temp_buff_max_len())
    {
        unsigned int buff_num = 0;
        //--<3-1-1>--尝试更新usbh_temp_buff, 返回的usbh_temp_buff可能并不是buff的起始地址
        usbh_temp_buff = write_usbh_temp_buff(dev_id, blk, n, pBuffer);

        if (usbh_temp_buff != NULL)
        {
            //更新成功, 就直接开始写了
            return buff_blk_write(usbh_temp_buff, blk, n, hDev);
        }

        //更新失败, 就设置这个buff无效
        //有些buff存放了部分内容,这里必须把这部分内容无效掉
        set_usbh_temp_buff_invalid(dev_id, blk);
        //--<3-1-2>--挑选一个无用的buff, 这个buff仅仅是为了传数据
        usbh_temp_buff = select_invalid_usbh_temp_buff(&buff_num);

        if (usbh_temp_buff == NULL)
        {
            //DMSG_PANIC("ERR: select_invalid_usbh_temp_buff failed\n");
            //既然不能再使用usbh_temp_buff了, 就直接写把
            return buff_blk_write(pBuffer, blk, n, hDev);
        }

        memcpy(usbh_temp_buff, pBuffer, this_len);
        /*
         **********************************************************
         * 这里因为this_len不满32k,所以不能设置usbh_temp_buff有效
         **********************************************************
         */
        //--<3-1-3>--用usbh_temp_buff来进行写
        return buff_blk_write(usbh_temp_buff, blk, n, hDev);
    }
    else
    {
        //数据大于32k, 就设置与dev_id匹配的buffer无效
        set_usbh_temp_buff_invalid_by_dev(dev_id);
        return buff_blk_write(pBuffer, blk, n, hDev);
    }
}

/*
*********************************************************************
*                     init_usbh_buff_manager
*
* Description:
*     初始化 usbh 临时buffer，用来提高USBH的读写速度
* Arguments:
*
* Returns:
*
* note:
*
*
*********************************************************************
*/
int init_usbh_buff_manager(void)
{
    usbh_buff_manager_t *buff_mgr = &usbh_buff_manager;
    unsigned int i = 0;
    unsigned int page = 0;
    //--<1>--初始化usbh_buff_manager
    memset(buff_mgr, 0, sizeof(usbh_buff_manager_t));
    buff_mgr->temp_buff_nr  = USBH_TEMP_BUFFER_MAX_NUM;
    buff_mgr->temp_buff_len = USBH_TEMP_BUFFER_MAX_LEN;
    page = ((buff_mgr->temp_buff_len + 1023) >> 10) << 10;
    //DMSG_INFO("usb temp buffer size is %d\n", buff_mgr->temp_buff_len);

    //--<2>--构造并且初始化每一个temp_buff
    for (i = 0; i < buff_mgr->temp_buff_nr; i++)
    {
        buff_mgr->buff_array[i].buff = (void *)hal_malloc(page);

        if (buff_mgr->buff_array[i].buff == NULL)
        {
            //分配失败,就放弃使用缓冲机制
            //DMSG_PANIC("ERR: init_usbh_buff_manager: USB_OS_PAGE_MALLOC failed\n");
            goto failed;
        }

        memset((void *)buff_mgr->buff_array[i].buff, 0, buff_mgr->temp_buff_len);
        buff_mgr->buff_array[i].buff_len = buff_mgr->temp_buff_len;
        buff_mgr->buff_array[i].num = i;
        set_usbh_temp_buff_default(&(buff_mgr->buff_array[i]));
    }

    return 0;
failed:

    for (i = 0; i < buff_mgr->temp_buff_nr; i++)
    {
        if (buff_mgr->buff_array[i].buff)
        {
            hal_free(buff_mgr->buff_array[i].buff);
            buff_mgr->buff_array[i].buff = NULL;
        }
        else
        {
            //DMSG_PANIC("ERR: parameter is invalid, pfree failed\n");
        }
    }

    memset(buff_mgr, 0, sizeof(usbh_buff_manager_t));
    return -1;
}

/*
*********************************************************************
*                     exit_usbh_buff_manager
*
* Description:
*     sd信息设备，目前主要用于监测sd设备的读写情况
* Arguments:
*
* Returns:
*
* note:
*
*
*********************************************************************
*/
int exit_usbh_buff_manager(void)
{
    usbh_buff_manager_t *buff_mgr = &usbh_buff_manager;
    unsigned int i = 0;
    set_all_usbh_temp_buff_invalid();

    for (i = 0; i < buff_mgr->temp_buff_nr; i++)
    {
        if (buff_mgr->buff_array[i].buff)
        {
            hal_free(buff_mgr->buff_array[i].buff);
            buff_mgr->buff_array[i].buff = NULL;
        }
        else
        {
            //DMSG_PANIC("ERR: parameter is invalid, pfree failed\n");
        }
    }

    memset(buff_mgr, 0, sizeof(usbh_buff_manager_t));
    return 0;
}

