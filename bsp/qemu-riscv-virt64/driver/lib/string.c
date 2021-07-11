#include <rthw.h>
#include "../../rtconfig.h"

#ifdef USING_RV64_LINUX_GNU_TOOLCHAIN

size_t strlen(const char *s) {
  return rt_strlen(s);
}

char *strcpy(char* dst, const char* src) {
  char *p1 = dst;
  const char *p2 = src;
  for( ; *p2 != 0; p1++, p2++) *p1 = *p2;
  *p1 = 0;
  return dst;
}

char* strncpy(char* dst, const char* src, size_t n) {
  return rt_strncpy(dst, src, n);
}

char* strcat(char* dst, const char* src) {
  size_t len = rt_strlen(dst);
  strcpy(dst + len, src);
  return dst;
}

int strcmp(const char* s1, const char* s2) {
  return rt_strcmp(s1, s2);
}

int strncmp(const char* s1, const char* s2, size_t n) {
  return rt_strncmp(s1, s2, n);
}

void* memset(void* v,int c,size_t n) {
  return rt_memset(v, c, n);
}

void* memmove(void* dst, const void* src,size_t n) {
  return rt_memmove(dst, src, n);
}

void* memcpy(void* out, const void* in, size_t n) {
  rt_memcpy(out, in, n);
}

int memcmp(const void* s1, const void* s2, size_t n) {
  return rt_memcmp(s1, s2, n);
}

const char* strstr(const char* s1, const char* s2){
    return rt_strstr(s1, s2);
}

char *strrchr(const char *s, int c)
{
    if(s == RT_NULL) return RT_NULL;
    char *p_char = RT_NULL;
    while(*s != '\0')
    {
        if(*s == (char)c) p_char = (char *)s;
        s++;
    }
    return p_char;
}


#endif
