#ifndef __USB_OS_PLATFORM_H__
#define __USB_OS_PLATFORM_H__

#include <stdint.h>
#include <typedef.h>

#define dma_addr_t  unsigned long
#define gfp_t       uint32_t

uint16_t le16_to_cpu(uint16_t x);
uint32_t le32_to_cpu(uint32_t x);
uint32_t le32_to_cpup(const uint32_t *x);

#define cpu_to_le16(x) le16_to_cpu((x))
#define cpu_to_le32(x) le32_to_cpu(x)

static inline u16 get_be16(u8 *buf)
{
    return ((__u16) buf[0] << 8) | ((__u16) buf[1]);
}

static inline u32 get_be32(u8 *buf)
{
    return ((__u32) buf[0] << 24) | ((__u32) buf[1] << 16) |
           ((__u32) buf[2] << 8) | ((__u32) buf[3]);
}

static inline void put_be16(__u8 *buf, __u16 val)
{
    buf[0] = (__u8)(val >> 8);
    buf[1] = (__u8)val;
}

static inline void put_be32(__u8 *buf, __u32 val)
{
    buf[0] = (__u8)(val >> 24);
    buf[1] = (__u8)(val >> 16);
    buf[2] = (__u8)(val >> 8);
    buf[3] = (__u8)val;
}

/* 取绝对值 */
#undef  absolute
#define absolute(p)                     ((p) > 0 ? (p) : -(p))

//#define readb(addr)      (*((volatile unsigned char *)(long)(addr)))
//#define readw(addr)             (*((volatile unsigned short *)(long)(addr)))
// #define readl(addr)             (*((volatile unsigned int *)(long)(addr)))
//#define writeb(v, addr) (*((volatile unsigned char *)(long)(addr)) = (unsigned char)(v))
//#define writew(v, addr) (*((volatile unsigned short *)(long)(addr)) = (unsigned short)(v))
// #define writel(v, addr) (*((volatile unsigned int *)(long)(addr)) = (unsigned int)(v))

#if defined(CONFIG_ARCH_SUN8IW20) || defined(CONFIG_SOC_SUN20IW1)
#define readl(addr)             (*((volatile unsigned int *)(long)(addr)))
#define writel(v, addr) (*((volatile unsigned int *)(long)(addr)) = (unsigned int)(v))
#endif

void *usb_dma_malloc(uint32_t size, dma_addr_t *p_addr);
void usb_dma_free(void *v_addr, dma_addr_t p_addr);
void usb_set_bit(int bit_nr, volatile uint32_t *addr);
void usb_clear_bit(int bit_nr, volatile uint32_t *addr);
uint32_t usb_test_bit(int bit_nr, volatile uint32_t *addr);
uint32_t usb_test_and_clear_bit(int bit_nr, volatile uint32_t *addr);
void usb_clear_bit32(int bit_nr, volatile uint32_t *addr);
void usb_dec32(uint32_t *addr);
void usb_inc32(uint32_t *addr);
void Usb_uint2str_dec(unsigned int input, char *str);
#endif
