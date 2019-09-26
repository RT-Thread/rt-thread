#ifndef __LINUX_ZLIB_H__
#define __LINUX_ZLIB_H__

#include <cyg/compress/zlib.h>

#define zlib_deflateInit(x,y) deflateInit(x,y)
#define zlib_deflate(x,y) deflate(x,y)
#define zlib_deflateEnd(x) deflateEnd(x)
#define zlib_inflateInit(x) inflateInit(x)
#define zlib_inflateInit2(x,y) inflateInit2(x,y)
#define zlib_inflate(x,y) inflate(x,y)
#define zlib_inflateEnd(x) inflateEnd(x)


#endif /* __LINUX_ZLIB_H__ */
