/* libc stubs for qemu-virt64-riscv — override toolchain libc with non-vector implementations */

#include <rtthread.h>

void *memcpy(void *dest, const void *src, size_t n)
{
    const char *s = (const char *)src;
    char *d = (char *)dest;
    size_t i;
    for (i = 0; i < n; i++)
        d[i] = s[i];
    return dest;
}

void *memset(void *s, int c, size_t n)
{
    char *p = (char *)s;
    size_t i;
    for (i = 0; i < n; i++)
        p[i] = (char)c;
    return s;
}

int memcmp(const void *s1, const void *s2, size_t n)
{
    const unsigned char *a = (const unsigned char *)s1;
    const unsigned char *b = (const unsigned char *)s2;
    size_t i;
    for (i = 0; i < n; i++)
        if (a[i] != b[i])
            return (int)a[i] - (int)b[i];
    return 0;
}
