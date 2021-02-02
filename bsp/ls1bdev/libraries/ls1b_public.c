/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-06     勤为本       first version
 * 2021-02-02     michael5hzg@gmail.com       adapt to ls1b
 */

// 一些常用的、共用的接口

/*
 * 将指定寄存器的指定位置1
 * @reg 寄存器地址
 * @bit 需要置1的那一bit
 */
void reg_set_one_bit(volatile unsigned int *reg, unsigned int bit)
{
    unsigned int temp, mask;

    mask = 1 << bit;
    temp = *reg;
    temp |= mask;
    *reg = temp;

    return ;
}


/*
 * 将指定寄存器的指定位清零
 * @reg 寄存器地址
 * @bit 需要清零的那一bit
 */
void reg_clr_one_bit(volatile unsigned int *reg, unsigned int bit)
{
    unsigned int temp, mask;

    mask = 1 << bit;
    temp = *reg;
    temp &= ~mask;
    *reg = temp;

    return ;
}



/*
 * 获取指定寄存器的指定位的值
 * @reg 寄存器地址
 * @bit 需要读取值的那一bit
 * @ret 指定位的值
 */
unsigned int reg_get_bit(volatile unsigned int *reg, unsigned int bit)
{
    unsigned int temp;

    temp = *reg;
    temp = (temp >> bit) & 1;

    return temp;
}


/*
 * 向寄存器中写入8bit(一个字节)数据
 * @data 待写入的数据
 * @addr 寄存器地址
 */
void reg_write_8(unsigned char data, volatile unsigned char *addr)
{
    *addr = data;
}


/*
 * 从寄存器读出8bit(一个字节)数据
 * @addr 寄存器地址
 * @ret 读出的数据
 */
unsigned char reg_read_8(volatile unsigned char *addr)
{
    return (*addr);
}


/*
 * 向寄存器中写一个32bit的数据
 * @data 待写入的数据
 * @addr 寄存器地址
 */
void reg_write_32(unsigned int data, volatile unsigned int *addr)
{
    *addr = data;
}


/*
 * 从寄存器读出一个32bit数据
 * @addr 寄存器地址
 * @ret 读出的数据
 */
unsigned int reg_read_32(volatile unsigned int *addr)
{
    return (*addr);
}



/**
 * ffs - find first bit set
 * @x: the word to search
 *
 * This is defined the same way as
 * the libc and compiler builtin ffs routines, therefore
 * differs in spirit from the above ffz (man ffs).
 */
int ls1b_ffs(int x)
{
	int r = 1;

	if (!x)
		return 0;
	if (!(x & 0xffff)) {
		x >>= 16;
		r += 16;
	}
	if (!(x & 0xff)) {
		x >>= 8;
		r += 8;
	}
	if (!(x & 0xf)) {
		x >>= 4;
		r += 4;
	}
	if (!(x & 3)) {
		x >>= 2;
		r += 2;
	}
	if (!(x & 1)) {
		x >>= 1;
		r += 1;
	}
	return r;
}


/*
 * fls - find last (most-significant) bit set
 * @x: the word to search
 *
 * This is defined the same way as ffs.
 * Note fls(0) = 0, fls(1) = 1, fls(0x80000000) = 32.
 */
int ls1b_fls(int x)
{
    int r = 32;

    if (!x)
        return 0;
    if (!(x & 0xffff0000u))
    {
        x <<= 16;
        r -= 16;
    }
    if (!(x & 0xff000000u))
    {
        x <<= 8;
        r -= 8;
    }
    if (!(x & 0xf0000000u))
    {
        x <<= 4;
        r -= 4;
    }
    if (!(x & 0xc0000000u))
    {
        x <<= 2;
        r -= 2;
    }
    if (!(x & 0x80000000u))
    {
        x <<= 1;
        r -= 1;
    }

    return r;
}


