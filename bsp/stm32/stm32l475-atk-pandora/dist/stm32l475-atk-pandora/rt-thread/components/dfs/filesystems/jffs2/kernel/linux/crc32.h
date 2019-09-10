#ifndef CRC32_H
#define CRC32_H

#include <cyg/crc/crc.h>

#define crc32(val, s, len) cyg_crc32_accumulate(val, (unsigned char *)s, len)

#endif
