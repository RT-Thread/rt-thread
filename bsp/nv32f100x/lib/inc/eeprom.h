#ifndef EEPROM_H_
#define EEPROM_H_

/******************************************************************************
* Includes
******************************************************************************/
#include "common.h"

#define EERPOM_SIZE	1024		// in bytes
#define EEPROM_START_ADR 0x00401000
#define EEPROM_ERR_SUCCESS 0x01
#define EEPROM_ADR_OverFlow 0x02
#define EEPROM_ERR_INVALID_PARAM 0x04
#define EEPROM_BLANK 0xffffffff
#define EEPROM_SECTOR_MASK 0x00401200
#define EEPROM_ARRAY_ADR_MASK 0x1ff


uint16_t Adress_Js(uint32_t adr);
uint16_t EEPROM_Erase(uint32_t adr);
uint32_t EEPROM_Read(uint32_t adr);
uint8_t EEPROM_ReadByte(uint32_t adr);


uint16_t EEPROM_Write(uint32_t adr, uint32_t Data);
uint16_t EEPROM_WriteByte(uint32_t adr, uint8_t Data);
uint16_t EERPOM_Writeup4byte(uint32_t adr, uint8_t *pData,uint32_t length);
#endif
