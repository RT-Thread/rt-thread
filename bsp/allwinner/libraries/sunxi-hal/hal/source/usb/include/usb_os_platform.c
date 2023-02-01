#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <hal_osal.h>

#include "usb_os_platform.h"
#include "sunxi_hal_common.h"

hal_spinlock_t lock;


void *usb_dma_malloc(uint32_t size, dma_addr_t *p_addr)
{
    void *v_addr = NULL;

    /* should be 32 byte-align for QH and QTD */
    v_addr = dma_alloc_coherent(size);
    if (v_addr) {
        *p_addr = __va_to_pa((unsigned long)v_addr);
        memset(v_addr, 0, size);
        return v_addr;
    }

    hal_log_err("hal_malloc failed\n");
    return NULL;
}

void usb_dma_free(void *v_addr, dma_addr_t p_addr)
{
    if (v_addr)
        dma_free_coherent(v_addr);
}

void usb_set_bit(int bit_nr, volatile uint32_t *addr)
{
    int32_t mask;
    uint32_t cpu_sr;
    volatile uint32_t *p = addr;
    p += ((bit_nr & 0xffffffe0) >> 5);
    mask = 1 << (bit_nr & 0x1f);
    cpu_sr = hal_spin_lock_irqsave(&lock);
    (*p) |= mask;
    hal_spin_unlock_irqrestore(&lock, cpu_sr);
}
void usb_clear_bit(int bit_nr, volatile uint32_t *addr)
{
    int32_t mask;
    uint32_t cpu_sr;
    volatile uint32_t *p = addr;
    p += ((bit_nr & 0xffffffe0) >> 5);
    mask = 1 << (bit_nr & 0x1f);
    cpu_sr = hal_spin_lock_irqsave(&lock);
    (*p) &= (~mask);
    hal_spin_unlock_irqrestore(&lock, cpu_sr);
}
uint32_t usb_test_bit(int bit_nr, volatile uint32_t *addr)
{
    uint32_t ret;
    uint32_t cpu_sr;
    volatile uint32_t *p = addr;
    p += ((bit_nr & 0xffffffe0) >> 5);
    cpu_sr = hal_spin_lock_irqsave(&lock);
    ret = ((*p) >> (bit_nr & 31)) & 1;
    hal_spin_unlock_irqrestore(&lock, cpu_sr);
    return ret;
}
uint32_t usb_test_and_clear_bit(int bit_nr, volatile uint32_t *addr)
{
    uint32_t ret, mask;
    uint32_t cpu_sr;
    mask = 1 << (bit_nr & 0x1f);
    cpu_sr = hal_spin_lock_irqsave(&lock);
    ret = ((mask & *addr) != 0);
    *addr &= ~mask;
    hal_spin_unlock_irqrestore(&lock, cpu_sr);
    return ret;
}
void usb_clear_bit32(int bit_nr, volatile uint32_t *addr)
{
    uint32_t cpu_sr;
    int32_t mask;
    mask = 1 << (bit_nr & 0x1f);
    cpu_sr = hal_spin_lock_irqsave(&lock);
    *addr &= ~mask;
    hal_spin_unlock_irqrestore(&lock, cpu_sr);
}
void usb_dec32(uint32_t *addr)
{
    uint32_t cpu_sr;
    cpu_sr = hal_spin_lock_irqsave(&lock);
    *addr = *addr - 1;
    hal_spin_unlock_irqrestore(&lock, cpu_sr);
}
void usb_inc32(uint32_t *addr)
{
    uint32_t cpu_sr;
    cpu_sr = hal_spin_lock_irqsave(&lock);
    *addr = *addr + 1;
    hal_spin_unlock_irqrestore(&lock, cpu_sr);
}
uint16_t le16_to_cpu(uint16_t x)
{
    return x;
}
uint32_t le32_to_cpu(uint32_t x)
{
    return x;
}
uint32_t le32_to_cpup(const uint32_t *x)
{
    return *x;
}
void Usb_uint2str_dec(unsigned int input, char *str)
{
    char stack[11] = {0};
    int i ;
    int j ;

    if (input == 0)
    {
        str[0] = '0';
        str[1] = '\0';                   // 'str' must end with '\0'
        return ;
    }

    for (i = 0; input > 0; ++i)
    {
        stack[i] = input % 10 + '0';     // characters in reverse order are put in 'stack' .
        input /= 10;
    }                                    // at the end of 'for' loop, 'i' is the number of characters.

    for (--i, j = 0; i >= 0; --i, ++j)
    {
        str[j] = stack[i];
    }

    str[j] = '\0';                       // 'str' must end with '\0'
}

