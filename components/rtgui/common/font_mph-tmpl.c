/* adapted from utils/perfect_hash/example1-C/states-tmpl.c */

#include <rtthread.h>
#include <string.h>

static const rt_uint32_t T1[] = { $S1 };
static const rt_uint32_t T2[] = { $S2 };
static const rt_uint16_t G[] = { $G };

static rt_uint32_t hash_g(const rt_uint16_t key, const rt_uint32_t *T)
{
    rt_uint32_t sum = (T[0] * (key & 0xFF) + T[1] * (key >> 8)) % $NG;
    return G[sum % $NG];
}

static rt_uint32_t perfect_hash(const rt_uint16_t key)
{
    return (hash_g(key, T1) + hash_g(key, T2)) % $NG;
}

rt_uint32_t rtgui_font_mph${height}(const rt_uint16_t key)
{
    rt_uint32_t hash_value = perfect_hash(key);

    /*rt_kprintf("hash 0x7684 is %d", perfect_hash(0x7684));*/
    /*RT_ASSERT(K[hash_value] == key);*/
    /* NOTE: we trust you will not feed invalid data into me. So there is no
     * more sanity check which will consume more flash and memory. */
    if (hash_value < $NK)
        return hash_value;
    return -1;
}

const unsigned char hz${height}_font[] = { $font_data };

