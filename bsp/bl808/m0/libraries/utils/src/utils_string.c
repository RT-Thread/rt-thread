/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <utils_string.h>

static int params_filter(char** params,uint32_t *r)
{	
	char *p ;
	uint32_t result=0;
	uint8_t base=0;
	
	p = *params;
	
    if((*p == '0') && ((*(p+1) == 'x') || (*(p+1) == 'X')) ){
		p = p + 2;
		base = 16;
		
	}else{
		base = 10;
	}
	
	while(*p){
		result *= base;
	    if(*p >= '0' && *p<='9')
			result += *p-'0';
		else if(base==10)
			return -1;
			
		if(base==16){
			if(*p >= 'a' && *p<='f')
				result += *p-'a' + 10;
			else if(*p >= 'A' && *p<='F')
				result += *p-'A' + 10;
		
		}
		p++;
	}
		
	*r = result;
	return 0;
	
}


void get_bytearray_from_string(char** params, uint8_t *result,int array_size)
{
    
    int i = 0;
    char rand[3];

    for(i=0; i < array_size; i++){
        strncpy(rand, (const char*)*params, 2);
        rand[2]='\0';
        result[i] = strtol(rand, NULL, 16);
        *params = *params + 2;
    }
}

void get_uint8_from_string(char** params, uint8_t *result)
{
	uint32_t p = 0;
	int state=0;
	
	state = params_filter(params,&p);
	if(!state){
		*result = p & 0xff;
	}else
		*result = 0;
}

void get_uint16_from_string(char** params, uint16_t *result)
{
	uint32_t p = 0;
	int state=0;
	
	state = params_filter(params,&p);
	if(!state){
		*result = p & 0xffff;
	}else
		*result = 0;
}

void get_uint32_from_string(char** params, uint32_t *result)
{
    uint32_t p = 0;
	int state=0;
	
	state = params_filter(params,&p);
	if(!state){
		*result = p;
	}else
		*result = 0;
}

void utils_parse_number(const char *str, char sep, uint8_t *buf, int buflen, int base)
{
  int i;
  for (i = 0; i < buflen; i++) {
    buf[i] = (uint8_t)strtol(str, NULL, base);
    str = strchr(str, sep);
    if (str == NULL || *str == '\0') {
      break;
    }
    str++;
  }
}

void utils_parse_number_adv(const char *str, char sep, uint8_t *buf, int buflen, int base, int *count)
{
  int i;

  for (i = 0; i < buflen; i++) {
    buf[i] = (uint8_t)strtol(str, NULL, base);
    str = strchr(str, sep);
    if (str == NULL || *str == '\0') {
      break;
    }
    str++;
  }
  *count = (i + 1);
}


unsigned long long convert_arrayToU64(uint8_t* inputArray)
{
    unsigned long long result = 0;
    for(uint8_t i = 0; i < 8; i++)
    {
        result <<= 8;
        result |= (unsigned long long)inputArray[7-i];
    }

    return result;
}

void convert_u64ToArray(unsigned long long inputU64, uint8_t result[8])
{
    for(int i = 0; i < 8; i++)
    {
        result[i] = inputU64>>(i*8);
    }
}

void utils_memcpy8(void *dst, void *src, size_t len)
{
    uint8_t *d = (uint8_t *)dst;
    uint8_t *s = (uint8_t *)src;

    while (len--) {
        *d++ = *s++;
    }
}

void utils_memcpy16(void *dst, void *src, size_t len)
{
    uint16_t *d = (uint16_t *)dst;
    uint16_t *s = (uint16_t *)src;

    len >>= 1;//convert to half words

    while (len--) {
        *d++ = *s++;
    }
}

void utils_memcpy32(void *dst, void *src, size_t len)
{
    uint32_t *d = (uint32_t *)dst;
    uint32_t *s = (uint32_t *)src;

    len >>= 2;//convert to words

    while (len--) {
        *d++ = *s++;
    }
}

void utils_memcpy64(void *dst, void *src, size_t len)
{
    uint64_t *d = (uint64_t *)dst;
    uint64_t *s = (uint64_t *)src;

    len >>= 3;//convert to two words

    while (len--) {
        *d++ = *s++;
    }
}

void utils_memset8(void *src, uint8_t n, size_t len)
{
    uint8_t *s = (uint8_t *)src;

    while (len--) {
        *s++ = n;
    }
}

void utils_memset16(void *src, uint16_t n, size_t len)
{
    uint16_t *s = (uint16_t *)src;

    len >>= 1;//convert to half words

    while (len--) {
        *s++ = n;
    }
}

void utils_memset32(void *src, uint32_t n, size_t len)
{
    uint32_t *s = (uint32_t *)src;

    len >>= 2;//convert to words

    while (len--) {
        *s++ = n;
    }
}

void utils_memset64(void *src, uint64_t n, size_t len)
{
    uint64_t *s = (uint64_t *)src;

    len >>= 3;//convert to two words

    while (len--) {
        *s++ = n;
    }
}

void utils_memset8_with_seq(void *src, uint8_t seq, size_t len)
{
    uint8_t *s = (uint8_t *)src;

    while (len--) {
        *s++ = (seq++);
    }
}

void utils_memset16_with_seq(void *src, uint16_t seq, size_t len)
{
    uint16_t *s = (uint16_t *)src;

    len >>= 1;//convert to half words

    while (len--) {
        *s++ = (seq++);
    }
}

void utils_memset32_with_seq(void *src, uint32_t seq, size_t len)
{
    uint32_t *s = (uint32_t *)src;

    len >>= 2;//convert to words

    while (len--) {
        *s++ = (seq++);
    }
}

void utils_memset64_with_seq(void *src, uint64_t seq, size_t len)
{
    uint64_t *s = (uint64_t *)src;

    len >>= 3;//convert to two words

    while (len--) {
        *s++ = (seq++);
    }
}

void utils_memdrain8(void *src, size_t len)
{
    volatile uint8_t *s = (uint8_t *)src;
    uint8_t tmp;

    while (len--) {
        tmp = *s++;
    }

    (void)tmp;
}

void utils_memdrain16(void *src, size_t len)
{
    volatile uint16_t *s = (uint16_t *)src;
    uint16_t tmp;

    len >>= 1;//convert to half words

    while (len--) {
        tmp = *s++;
    }
    
    (void)tmp;
}

void utils_memdrain32(void *src, size_t len)
{
    volatile uint32_t *s = (uint32_t *)src;
    uint32_t tmp;

    len >>= 2;//convert to words

    while (len--) {
        tmp = *s++;
    }
    
    (void)tmp;
}

void utils_memdrain64(void *src, size_t len)
{
    volatile uint64_t *s = (uint64_t *)src;
    uint64_t tmp;

    len >>= 3;//convert to two words

    while (len--) {
        tmp = *s++;
    }
    
    (void)tmp;
}

void * utils_memdrain8_with_check(void *src, size_t len, uint8_t seq)
{
    volatile uint8_t *s = (uint8_t *)src;
    uint8_t tmp;

    (void)tmp;

    while (len--) {
        tmp = *s++;
        if((seq++) != tmp){
            return (uint8_t *)s-1;
        }
    }

    return NULL; 
}

void * utils_memdrain16_with_check(void *src, size_t len, uint16_t seq)
{
    volatile uint16_t *s = (uint16_t *)src;
    uint16_t tmp;
    (void)tmp;

    len >>= 1;//convert to half words

    while (len--) {
        tmp = *s++;
        if((seq++) != tmp){
            return (uint16_t *)s-1;
        }
    }
    
    return NULL; 
}

void * utils_memdrain32_with_check(void *src, size_t len, uint32_t seq)
{
    volatile uint32_t *s = (uint32_t *)src;
    uint32_t tmp;
    (void)tmp;

    len >>= 2;//convert to words

    while (len--) {
        tmp = *s++;
        if((seq++) != tmp){
            return (uint32_t *)s-1;
        }
    }
    
    return NULL; 
}

void * utils_memdrain64_with_check(void *src, size_t len, uint64_t seq)
{
    volatile uint64_t *s = (uint64_t *)src;
    uint64_t tmp;
    (void)tmp;

    len >>= 3;//convert to two words

    while (len--) {
        tmp = *s++;
        if((seq++) != tmp){
            return (uint64_t *)s-1;
        }
    }
    
    return NULL; 
}
