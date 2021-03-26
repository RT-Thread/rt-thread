#ifndef __SWM320_FLASH_H__
#define __SWM320_FLASH_H__


void FLASH_Erase(uint32_t addr);
void FLASH_Write(uint32_t addr, uint32_t buff[], uint32_t count);

void Flash_Param_at_120MHz(void);



typedef void (*IAP_Cache_Reset_t)(void);
typedef void (*IAP_Flash_Param_t)(uint32_t cfg0, uint32_t cfg1);
typedef void (*IAP_Flash_Erase_t)(uint32_t sector);
typedef void (*IAP_Flash_Write_t)(uint32_t flash_addr, uint32_t ram_addr, uint32_t count);

extern IAP_Cache_Reset_t IAP_Cache_Reset;
extern IAP_Flash_Param_t IAP_Flash_Param;
extern IAP_Flash_Erase_t IAP_Flash_Erase;
extern IAP_Flash_Write_t IAP_Flash_Write;


#endif //__SWM320_FLASH_H__
