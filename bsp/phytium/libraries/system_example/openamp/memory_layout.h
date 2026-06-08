#ifndef MEMORY_LAYOUT_H
#define MEMORY_LAYOUT_H

#if defined __cplusplus
extern "C" {
#endif

/*slave core0*/
/* 与linux共享的内存 */
#define SLAVE00_SOURCE_TABLE_ADDR        0xc0000000 /*与linux协商好的地址*/
#define SLAVE00_KICK_IO_ADDR             0xc0224000

/* MEM = |tx vring|rx vring|share buffer| */
#define SLAVE00_SHARE_MEM_ADDR           0xffffffff /*全F表示等待linux分配*/
#define SLAVE00_SHARE_MEM_SIZE           0x100000 /*共享内存大小*/
#define SLAVE00_VRING_SIZE               0x8000UL
#define SLAVE00_VRING_NUM                0x100
#define SLAVE00_TX_VRING_ADDR            0xffffffff /*全F表示等待linux分配*/
#define SLAVE00_RX_VRING_ADDR            0xffffffff /*全F表示等待linux分配*/

#define SLAVE00_SOURCE_TABLE_ATTRIBUTE   (MT_NORMAL|MT_P_RW_U_NA)
#define SLAVE00_SHARE_BUFFER_ATTRIBUTE   (MT_NORMAL|MT_P_RW_U_NA)

#if defined __cplusplus
}
#endif

#endif /* MEMORY_LAYOUT_H */
