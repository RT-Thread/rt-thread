#ifndef RINGBUFFER_H__
#ifndef RINGBUFFER_H__
#define RINGBUFFER_H__
#define RINGBUFFER_H__


#ifdef __cplusplus
#ifdef __cplusplus
extern "C" {
extern "C" {
#endif
#endif


#include <rtthread.h>
#include <rtthread.h>


/* ring buffer */
/* ring buffer */
struct rt_ringbuffer
struct rt_ringbuffer
{
{
    rt_uint8_t *buffer_ptr;
    rt_uint8_t *buffer_ptr;
    /* use the msb of the {read,write}_index as mirror bit. You can see this as
    /* use the msb of the {read,write}_index as mirror bit. You can see this as
     * if the buffer adds a virtual mirror and the pointers point either to the
     * if the buffer adds a virtual mirror and the pointers point either to the
     * normal or to the mirrored buffer. If the write_index has the same value
     * normal or to the mirrored buffer. If the write_index has the same value
     * with the read_index, but in a different mirror, the buffer is full.
     * with the read_index, but in a different mirror, the buffer is full.
     * While if the write_index and the read_index are the same and within the
     * While if the write_index and the read_index are the same and within the
     * same mirror, the buffer is empty. The ASCII art of the ringbuffer is:
     * same mirror, the buffer is empty. The ASCII art of the ringbuffer is:
     *
     *
     *          mirror = 0                    mirror = 1
     *          mirror = 0                    mirror = 1
     * +---+---+---+---+---+---+---+|+~~~+~~~+~~~+~~~+~~~+~~~+~~~+
     * +---+---+---+---+---+---+---+|+~~~+~~~+~~~+~~~+~~~+~~~+~~~+
     * | 0 | 1 | 2 | 3 | 4 | 5 | 6 ||| 0 | 1 | 2 | 3 | 4 | 5 | 6 | Full
     * | 0 | 1 | 2 | 3 | 4 | 5 | 6 ||| 0 | 1 | 2 | 3 | 4 | 5 | 6 | Full
     * +---+---+---+---+---+---+---+|+~~~+~~~+~~~+~~~+~~~+~~~+~~~+
     * +---+---+---+---+---+---+---+|+~~~+~~~+~~~+~~~+~~~+~~~+~~~+
     *  read_idx-^                   write_idx-^
     *  read_idx-^                   write_idx-^
     *
     *
     * +---+---+---+---+---+---+---+|+~~~+~~~+~~~+~~~+~~~+~~~+~~~+
     * +---+---+---+---+---+---+---+|+~~~+~~~+~~~+~~~+~~~+~~~+~~~+
     * | 0 | 1 | 2 | 3 | 4 | 5 | 6 ||| 0 | 1 | 2 | 3 | 4 | 5 | 6 | Empty
     * | 0 | 1 | 2 | 3 | 4 | 5 | 6 ||| 0 | 1 | 2 | 3 | 4 | 5 | 6 | Empty
     * +---+---+---+---+---+---+---+|+~~~+~~~+~~~+~~~+~~~+~~~+~~~+
     * +---+---+---+---+---+---+---+|+~~~+~~~+~~~+~~~+~~~+~~~+~~~+
     * read_idx-^ ^-write_idx
     * read_idx-^ ^-write_idx
     *
     *
     * The tradeoff is we could only use 32KiB of buffer for 16 bit of index.
     * The tradeoff is we could only use 32KiB of buffer for 16 bit of index.
     * But it should be enough for most of the cases.
     * But it should be enough for most of the cases.
     *
     *
     * Ref: http://en.wikipedia.org/wiki/Circular_buffer#Mirroring */
     * Ref: http://en.wikipedia.org/wiki/Circular_buffer#Mirroring */
    rt_uint16_t read_mirror : 1;
    rt_uint16_t read_mirror : 1;
    rt_uint16_t read_index : 15;
    rt_uint16_t read_index : 15;
    rt_uint16_t write_mirror : 1;
    rt_uint16_t write_mirror : 1;
    rt_uint16_t write_index : 15;
    rt_uint16_t write_index : 15;
    /* as we use msb of index as mirror bit, the size should be signed and
    /* as we use msb of index as mirror bit, the size should be signed and
     * could only be positive. */
     * could only be positive. */
    rt_int16_t buffer_size;
    rt_int16_t buffer_size;
};
};


enum rt_ringbuffer_state
enum rt_ringbuffer_state
{
{
    RT_RINGBUFFER_EMPTY,
    RT_RINGBUFFER_EMPTY,
    RT_RINGBUFFER_FULL,
    RT_RINGBUFFER_FULL,
    /* half full is neither full nor empty */
    /* half full is neither full nor empty */
    RT_RINGBUFFER_HALFFULL,
    RT_RINGBUFFER_HALFFULL,
};
};


/**
/**
 * RingBuffer for DeviceDriver
 * RingBuffer for DeviceDriver
 *
 *
 * Please note that the ring buffer implementation of RT-Thread
 * Please note that the ring buffer implementation of RT-Thread
 * has no thread wait or resume feature.
 * has no thread wait or resume feature.
 */
 */
void rt_ringbuffer_init(struct rt_ringbuffer *rb, rt_uint8_t *pool, rt_int16_t size);
void rt_ringbuffer_init(struct rt_ringbuffer *rb, rt_uint8_t *pool, rt_int16_t size);
void rt_ringbuffer_reset(struct rt_ringbuffer *rb);
void rt_ringbuffer_reset(struct rt_ringbuffer *rb);
rt_size_t rt_ringbuffer_put(struct rt_ringbuffer *rb, const rt_uint8_t *ptr, rt_uint16_t length);
rt_size_t rt_ringbuffer_put(struct rt_ringbuffer *rb, const rt_uint8_t *ptr, rt_uint16_t length);
rt_size_t rt_ringbuffer_put_force(struct rt_ringbuffer *rb, const rt_uint8_t *ptr, rt_uint16_t length);
rt_size_t rt_ringbuffer_put_force(struct rt_ringbuffer *rb, const rt_uint8_t *ptr, rt_uint16_t length);
rt_size_t rt_ringbuffer_putchar(struct rt_ringbuffer *rb, const rt_uint8_t ch);
rt_size_t rt_ringbuffer_putchar(struct rt_ringbuffer *rb, const rt_uint8_t ch);
rt_size_t rt_ringbuffer_putchar_force(struct rt_ringbuffer *rb, const rt_uint8_t ch);
rt_size_t rt_ringbuffer_putchar_force(struct rt_ringbuffer *rb, const rt_uint8_t ch);
rt_size_t rt_ringbuffer_get(struct rt_ringbuffer *rb, rt_uint8_t *ptr, rt_uint16_t length);
rt_size_t rt_ringbuffer_get(struct rt_ringbuffer *rb, rt_uint8_t *ptr, rt_uint16_t length);
rt_size_t rt_ringbuffer_getchar(struct rt_ringbuffer *rb, rt_uint8_t *ch);
rt_size_t rt_ringbuffer_getchar(struct rt_ringbuffer *rb, rt_uint8_t *ch);
rt_size_t rt_ringbuffer_data_len(struct rt_ringbuffer *rb);
rt_size_t rt_ringbuffer_data_len(struct rt_ringbuffer *rb);


#ifdef RT_USING_HEAP
#ifdef RT_USING_HEAP
struct rt_ringbuffer* rt_ringbuffer_create(rt_uint16_t length);
struct rt_ringbuffer* rt_ringbuffer_create(rt_uint16_t length);
void rt_ringbuffer_destroy(struct rt_ringbuffer *rb);
void rt_ringbuffer_destroy(struct rt_ringbuffer *rb);
#endif
#endif


rt_inline rt_uint16_t rt_ringbuffer_get_size(struct rt_ringbuffer *rb)
rt_inline rt_uint16_t rt_ringbuffer_get_size(struct rt_ringbuffer *rb)
{
{
    RT_ASSERT(rb != RT_NULL);
    RT_ASSERT(rb != RT_NULL);
    return rb->buffer_size;
    return rb->buffer_size;
}
}


/** return the size of empty space in rb */
#define rt_ringbuffer_space_len(rb) ((rb)->buffer_size - rt_ringbuffer_data_len(rb))


#ifdef __cplusplus
}
#endif

#endif
