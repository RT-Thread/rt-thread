#include <stdint.h>            // standard integer definition
#include <string.h>            // string manipulation
#include "Eif_flash.h"         // flash definition
#include "interface.h"
//#include "flash_app_interface.h"

/// Flash environment structure
struct flash_env_tag1
{
    /// base address
    uint32_t    base_addr;
    /// length
    uint32_t    length;
};
//static struct flash_env_tag1 flash_env;



void eif_flash_init(void)
{
//    flash_env.base_addr = FLASH_BASE_ADDR;
//    flash_env.length    = FLASH_BASE_ADDR + FLASH_BLE_SIZE;

}


uint8_t eif_flash_erase(uint32_t offset, uint32_t size)
{
//    flash_erase(flash_env.base_addr, 1);
    return 0;
}


uint8_t eif_flash_write( uint32_t offset, uint32_t length, uint8_t *buffer)
{
//    uint8_t current_page_data[FLASH_BLE_SIZE];
//    flash_read(flash_env.base_addr, current_page_data, FLASH_BLE_SIZE);
//    flash_erase(flash_env.base_addr, 1);
//    memcpy(current_page_data + offset, buffer, length);
//    flash_write(flash_env.base_addr, current_page_data, FLASH_BLE_SIZE);

    return 0;
}


uint8_t eif_flash_read(uint32_t offset, uint32_t length, uint8_t *buffer)
{
//    uint32_t start_Ptr  = (flash_env.base_addr + offset);
//    flash_read(start_Ptr, buffer, length);
    return 0;
}
/// @} FLASH

