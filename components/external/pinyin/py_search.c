#include "py_search.h"
#ifdef PY_LIST_1
#include "py_mb_list_1.h"
#include "py_num_list_1.h"
#endif
#ifdef PY_LIST_2
#include "py_mb_list_2.h"
#include "py_num_list_2.h"
#endif
 
#define msg_list_item(first_msg, offset, index) (*(const char *const *)((const char *)(first_msg) + (offset) * (index)))

static int8_t _strcmp(const char *str1, const char *str2)
{
    while (*str1 == *str2)
    {
        if (!*str1) return 0;
        str1++;
        str2++;
    }

    return (*str1 - *str2);
}

static uint8_t _match(const char *str1, const char *str2)
{
    uint8_t n = 0;

    while (*str1 == *str2)
    {
        if (!*str1) return 0xFF;
        str1++;
        str2++;
        n++;
    }

    return n;
}

static void best_search(const char *msg, const char *const *first_msg, uint16_t offset, uint16_t count, uint16_t *plow, uint16_t *phigh)
{
    uint16_t low = 0, high = count - 1;
    uint16_t test;

    // binary search
    test = (low + high) >> 1;
    while (low < test)
    {
        if (_strcmp(msg_list_item(first_msg, offset, test), msg) >= 0) high = test;
        else low = test;
        test = (low + high) >> 1;
    }
    if ((low == 0) && _strcmp(msg_list_item(first_msg, offset, 0), msg) >= 0)
    {
        test = 0;
    }
    else
    {
        test = high;

        // find the best match
        if (_strcmp(msg_list_item(first_msg, offset, test), msg))
        {
            uint8_t m = _match(msg_list_item(first_msg, offset, low), msg);
            if (_match(msg_list_item(first_msg, offset, high), msg) <= m)
            {
                if (m > 0)
                {
                    uint16_t n = 1;

                    // 2^n search down
                    while (low > 0)
                    {
                        high = low;
                        low = (low > n) ? (low - n) : 0;
                        if (_match(msg_list_item(first_msg, offset, low), msg) < m) break;
                        n <<= 1;
                    }
                    if ((low == 0) && (_match(msg_list_item(first_msg, offset, 0), msg) >= m))
                    {
                        test = 0;
                    }
                    else
                    {
                        // binary search
                        test = (low + high) >> 1;
                        while (low < test)
                        {
                            if (_match(msg_list_item(first_msg, offset, test), msg) >= m) high = test;
                            else low = test;
                            test = (low + high) >> 1;
                        }
                        test = high;
                    }
                }
                else
                {
                    test = 0;
                }
            }
            else
            {
                test = high;
            }
        }
    }

    // find all item
    low = high = test;
    if (high < count - 1)
    {
        uint16_t m = low, n = 1;

        // 2^n search up
        while (high < count - 1)
        {
            low = high;
            high = (high + n < (count - 1)) ? (high + n) : (count - 1);
            if (_strcmp(msg_list_item(first_msg, offset, high), msg_list_item(first_msg, offset, m))) break;
            n <<= 1;
        }

        // binary search
        test = (low + high) >> 1;
        while (low < test)
        {
            if (_strcmp(msg_list_item(first_msg, offset, test), msg_list_item(first_msg, offset, m))) high = test;
            else low = test;
            test = (low + high) >> 1;
        }
        if ((high != (count - 1)) || _strcmp(msg_list_item(first_msg, offset, count - 1), msg_list_item(first_msg, offset, m)))
        {
            high = low;
        }

        low = m;
    }

    *plow = low;
    *phigh = high;
}

uint8_t py_mb_search(const char *msg, const py_mb_t **list, uint8_t size)
{
    uint16_t low, high;
    uint8_t count = 0;

    best_search(msg, &py_mb_list[0].msg, sizeof(py_mb_list[0]), sizeof(py_mb_list) / sizeof(py_mb_list[0]), &low, &high);

    while (low <= high)
    {
        if (count >= size) break;
        list[count++] = &py_mb_list[low++];
    }

    return count;
}

uint8_t py_num_search(const char *msg, const py_mb_t **list, uint8_t size)
{
    uint16_t low, high;
    uint8_t count = 0;

    best_search(msg, &py_num_list[0].msg, sizeof(py_num_list[0]), sizeof(py_num_list) / sizeof(py_num_list[0]), &low, &high);

    while (low <= high)
    {
        if (count >= size) break;
        list[count++] = &py_mb_list[py_num_list[low++].index];
    }

    return count;
}
