#include <string.h>

__attribute__((used))
wchar_t *wcscat(wchar_t *str_dst, const wchar_t *str_src)
{
    wchar_t *dst_iter = str_dst;
    int i = 0;

    while (*dst_iter != 0)
        ++dst_iter;

    while (str_src[i] != 0)
    {
        dst_iter[i] = str_src[i];
        ++i;
    }

	dst_iter[i] = 0;

	return str_dst;
}

__attribute__((used))
int wcscmp(const wchar_t *string1, const wchar_t *string2)
{
    int i = 0;
    register wchar_t c1, c2;

    while (1)
    {
        c1 = string1[i];
        c2 = string2[i];

        if (c1 < c2)
        {
			return -1;
		}
		else if (c1 > c2)
        {
			return 1;
		}

        if ((c1 == 0) || (c2 == 0))
            break;

        ++i;
	}

	return 0;
}

__attribute__((used))
int wcsncmp(const wchar_t *string1, const wchar_t *string2, int count)
{
    int i = 0;

    while (i < count)
    {
		if (string1[i] < string2[i])
        {
			return -1;
		}
		else if (string1[i] > string2[i])
        {
			return 1;
		}

        if ((string1[i] == 0) || (string2[i] == 0))
            break;
        ++i;
	}

	return 0;
}

__attribute__((used))
wchar_t *wcscpy(wchar_t *str_dst, const wchar_t *str_src)
{
    int i = 0;

    while (str_src[i] != 0)
    {
        str_dst[i] = str_src[i];
        ++i;
    }

	str_dst[i] = 0;

	return str_dst;
}

__attribute__((used))
wchar_t *wcsncpy(wchar_t *str_dst, const wchar_t *str_src, int count)
{
    int i = 0;

    while ((str_src[i] != 0) && (i < count))
    {
        str_dst[i] = str_src[i];
        ++i;
    }

	str_dst[i] = 0;

	return str_dst;
}

__attribute__((used))
int wcslen(const wchar_t *str)
{
    int i = 0;

    while (str[i] != 0)
        ++i;

	return i;
}

__attribute__((used))
wchar_t *wcsupr(wchar_t *str)
{
    wchar_t *str_iter = str;

    while (*str_iter != 0)
    {
        if ((*str_iter >= (wchar_t)'a') && (*str_iter <= (wchar_t)'z'))
            *str_iter -= 0x0020;
        ++str_iter;
    }

    return str;
}

__attribute__((used))
wchar_t *wcslwr(wchar_t *str)
{
    wchar_t *str_iter = str;

    while (*str_iter != 0)
    {
        if ((*str_iter <= (wchar_t)'Z') && (*str_iter >= (wchar_t)'A'))
            *str_iter += 0x0020;
        ++str_iter;
    }

    return str;
}
