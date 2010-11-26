#include "uip_pbuf.h"
#include "rtdef.h"

typedef rt_uint32_t	mem_ptr_t;
#define LWIP_MEM_ALIGN(addr) ((void *)(((mem_ptr_t)(addr) + RT_ALIGN_SIZE - 1) & ~(mem_ptr_t)(RT_ALIGN_SIZE-1)))
#define LWIP_MEM_ALIGN_SIZE(size) (((size) + RT_ALIGN_SIZE - 1) & ~(RT_ALIGN_SIZE-1))
#define SIZEOF_STRUCT_PBUF        LWIP_MEM_ALIGN_SIZE(sizeof(struct pbuf))

u8_t
pbuf_free(struct pbuf *p)
{

  //struct pbuf *q;
  
  if (p == RT_NULL) return 0;
  rt_free(p);
  //rt_free(&p->len);
  
  return 1;
}

struct pbuf *
pbuf_alloc(pbuf_layer layer, u16_t length, pbuf_type type)
{
  struct pbuf *p;
  u16_t offset = 0;
  offset += 16;
  
    /* If pbuf is to be allocated in RAM, allocate memory for it. */
  p = (struct pbuf*)rt_malloc(LWIP_MEM_ALIGN_SIZE(SIZEOF_STRUCT_PBUF + offset) + LWIP_MEM_ALIGN_SIZE(length));
  if (p == RT_NULL)  return RT_NULL; 
    /* Set up internal structure of the pbuf. */
  p->payload = LWIP_MEM_ALIGN((void *)((u8_t *)p + SIZEOF_STRUCT_PBUF + offset));
  p->len = length;   
  return p;
}

u8_t
pbuf_header(struct pbuf *p, s16_t header_size_increment) //
{
 //extrat link header
    uint8_t *ptr;
    
    ptr = p->payload;
    ptr -= header_size_increment;
    p->payload = ptr;
    p->len += header_size_increment;
 
    return 0;
}