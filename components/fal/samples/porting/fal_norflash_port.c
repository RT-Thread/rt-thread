#include <fal.h>
#include "fal_def.h"

#define FLASH_SECTOR_SIZE      ( 4 * 1024 )
#define FLASH_START_ADDR       0U
#define FLASH_END_ADDR         0x01000000U  // 16*1024*1024

#define FLASH_PROGRAM_MIN_SIZE 256  // 256 bytes
//每次对falsh写入时 底层可以写入的最大字节数为 FLASH_PAGE_SIZE
#define FLASH_PAGE_SIZE        FLASH_PROGRAM_MIN_SIZE  // 256 bytes

/**
 * @brief 需要实现以下函数
 */
extern int norflash_init( void );
extern void norflash_read( uint8_t* pbuf, uint32_t addr, uint16_t datalen );
extern void norflash_write_page( uint8_t* pbuf, uint32_t addr, uint16_t datalen );
extern void norflash_erase_sector( uint32_t saddr );

static int init( void );
static int read( long offset, uint8_t* buf, size_t size );
static int write( long offset, const uint8_t* buf, size_t size );
static int erase( long offset, size_t size );

#define FAL_ALIGN_UP( size, align ) \
    ( ( ( size ) + ( align ) - 1 ) - ( ( ( size ) + ( align ) - 1 ) % ( align ) ) )
#define FAL_ALIGN_DOWN( size, align ) ( ( ( size ) / ( align ) ) * ( align ) )

static int32_t get_sector( uint32_t address )
{
    uint32_t sector = 0;
    if ( address < FLASH_END_ADDR && address >= FLASH_START_ADDR ) {
        address -= FLASH_START_ADDR;
        sector = address / FLASH_SECTOR_SIZE;
        return sector;
    }
    return -1;
}

static int init( void )
{
    norflash_init();
    return 0;
}


static int read( long offset, uint8_t* buf, size_t size )
{
    norflash_read( buf, offset + FLASH_START_ADDR, size );
    return size;
}

static uint32_t judge_whether_erase( uint8_t* sector_buf, uint16_t len )
{
    uint8_t* p = sector_buf;
    for ( size_t i = 0; i < len; i++ ) {
        if ( p[ i ] != 0xFF ) {
            return 1;
        }
    }
    return 0;
}
/**
 * @brief
 *
 * @param offset 绝对地址
 * @param buf 读出来的扇区数据缓存
 * @param size 从扇区开始要写的长度 小于扇区大小
 * @return int
 */
static int write_sector( long offset, const uint8_t* buf, size_t size )
{
    uint32_t addr      = FLASH_START_ADDR + offset;
    uint32_t addr_up   = FAL_ALIGN_UP( addr, FLASH_PAGE_SIZE );
    uint32_t addr_down = FAL_ALIGN_DOWN( addr, FLASH_PAGE_SIZE );

    uint32_t addr_end      = addr + size;
    uint32_t addr_end_up   = FAL_ALIGN_UP( addr_end, FLASH_PAGE_SIZE );
    uint32_t addr_end_down = FAL_ALIGN_DOWN( addr_end, FLASH_PAGE_SIZE );

    uint32_t cur_addr      = addr_down;
    uint32_t max_write_len = 0;
    uint32_t write_len     = 0;
    while ( cur_addr < addr_end_up ) {
        if ( cur_addr < addr ) {
            max_write_len = ( addr_up - addr );
            write_len     = size >= max_write_len ? max_write_len : size;
            norflash_write_page( buf, addr, write_len );
            buf += write_len;
        }
        else if ( cur_addr == addr_end_down ) {
            max_write_len = FLASH_PAGE_SIZE;
            write_len     = addr_end - cur_addr;
            write_len     = write_len >= max_write_len ? max_write_len : write_len;
            norflash_write_page( buf, cur_addr, write_len );
        }
        else {
            norflash_write_page( buf, cur_addr, FLASH_PAGE_SIZE );
            buf += FLASH_PAGE_SIZE;
        }

        cur_addr += FLASH_PAGE_SIZE;
    }
    return size;
}
static int write( long offset, const uint8_t* buf, size_t size )
{
    uint32_t addr      = FLASH_START_ADDR + offset;
    uint32_t addr_up   = FAL_ALIGN_UP( addr, FLASH_SECTOR_SIZE );
    uint32_t addr_down = FAL_ALIGN_DOWN( addr, FLASH_SECTOR_SIZE );

    uint32_t addr_end      = addr + size;
    uint32_t addr_end_up   = FAL_ALIGN_UP( addr_end, FLASH_SECTOR_SIZE );
    uint32_t addr_end_down = FAL_ALIGN_DOWN( addr_end, FLASH_SECTOR_SIZE );
    uint32_t cur_addr      = addr_down;

    uint32_t max_write_len = 0;
    uint32_t write_len     = 0;

    if ( addr_end_up > FLASH_END_ADDR || ( int )addr_end_down < FLASH_START_ADDR ) return -1;
    //如果不使用内存分配可以定义一个static FLASH_SECTOR_SIZE 长度的buf
    uint8_t* read_sector_buf = FAL_MALLOC( FLASH_SECTOR_SIZE );
    if ( read_sector_buf == RT_NULL ) {
        return -2;
    }
    while ( cur_addr < addr_end_up ) {
        // 首次扇区写
        if ( cur_addr < addr ) {
            read( cur_addr - FLASH_START_ADDR, read_sector_buf, FLASH_SECTOR_SIZE );
            max_write_len = ( addr_up - addr );
            write_len     = size >= max_write_len ? max_write_len : size;
            if ( judge_whether_erase( read_sector_buf + addr - cur_addr, write_len ) ){
                norflash_erase_sector( get_sector( cur_addr ) );
                FAL_MEMCPY( read_sector_buf + ( addr - cur_addr ), buf, write_len );
                write_sector( cur_addr, read_sector_buf, FLASH_SECTOR_SIZE );
            }
            else {
                write_sector( addr, buf, write_len );
            }
            buf += write_len;
        }
        //最后一次扇区写
        else if ( cur_addr == addr_end_down ) {
            read( cur_addr - FLASH_START_ADDR, read_sector_buf, FLASH_SECTOR_SIZE );
            max_write_len = FLASH_SECTOR_SIZE;
            write_len     = addr_end - cur_addr;
            write_len     = write_len >= max_write_len ? max_write_len : write_len;
            if ( judge_whether_erase( read_sector_buf,  write_len ) ) {
                FAL_MEMCPY( read_sector_buf, buf, write_len );
                norflash_erase_sector( get_sector( cur_addr ) );
                write_sector( cur_addr, read_sector_buf, FLASH_SECTOR_SIZE );
            }
            else {
                write_sector( cur_addr, buf, write_len );
            }
        }
        //中间扇区写 直接擦除
        else {
            norflash_erase_sector( get_sector( cur_addr ) );
            write_sector( cur_addr, buf, FLASH_SECTOR_SIZE );
            buf += FLASH_SECTOR_SIZE;
        }
        cur_addr += FLASH_SECTOR_SIZE;
    }
    FAL_FREE( read_sector_buf );
    return size;
}

static int erase( long offset, size_t size )
{
    int32_t  cur_erase_sector;
    uint32_t addr      = FLASH_START_ADDR + offset;
    uint32_t addr_down = FAL_ALIGN_DOWN( addr, FLASH_SECTOR_SIZE );

    uint32_t addr_end    = addr + size;
    uint32_t addr_end_up = FAL_ALIGN_UP( addr_end, FLASH_SECTOR_SIZE );
    uint32_t cur_addr    = addr_down;

    while ( cur_addr < addr_end_up ) {
        cur_erase_sector = get_sector( cur_addr );
        if ( cur_erase_sector == -1 ) {
            return cur_addr - addr;
        }
        norflash_erase_sector( cur_erase_sector );
        cur_addr += FLASH_SECTOR_SIZE;
    }
    return size;
}
const struct fal_flash_dev norflash0 = {
    .name       = "norflash0",
    .addr       = FLASH_START_ADDR,
    .len        = FLASH_END_ADDR - FLASH_START_ADDR,
    .blk_size   = FLASH_SECTOR_SIZE,
    .ops        = { init, read, write, erase },
    .write_gran = 1,
};
