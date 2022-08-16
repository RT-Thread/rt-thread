#ifndef __SWM341_FLASH_H__
#define __SWM341_FLASH_H__


uint32_t FLASH_Erase(uint32_t addr);
uint32_t FLASH_Write(uint32_t addr, uint32_t buff[], uint32_t count);

void Flash_Param_at_xMHz(uint32_t x);

#define FLASH_RES_OK    0
#define FLASH_RES_TO    1   //Timeout
#define FLASH_RES_ERR   2



typedef void (*IAP_Cache_Reset_t)(uint32_t cfg, uint32_t flag);
typedef int  (*IAP_Flash_Param_t)(uint32_t cfg0, uint32_t cfg1, uint32_t flag);
typedef int  (*IAP_Flash_Erase_t)(uint32_t sector, uint32_t flag);
typedef int  (*IAP_Flash_Write_t)(uint32_t flash_addr, uint32_t ram_addr, uint32_t count, uint32_t flag);

extern const IAP_Cache_Reset_t IAP_Cache_Reset;
extern const IAP_Flash_Param_t IAP_Flash_Param;
extern const IAP_Flash_Erase_t IAP_Flash_Erase;
extern const IAP_Flash_Write_t IAP_Flash_Write;


#endif //__SWM341_FLASH_H__
