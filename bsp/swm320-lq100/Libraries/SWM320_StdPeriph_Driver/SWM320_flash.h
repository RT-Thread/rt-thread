#ifndef __SWM320_FLASH_H__
#define __SWM320_FLASH_H__


void FLASH_Erase(uint32_t addr);
void FLASH_Write(uint32_t addr, uint32_t buff[], uint32_t size);


#endif //__SWM320_FLASH_H__
