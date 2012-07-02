#include <rtthread.h>
#include <rtdevice.h>
#include <string.h>

void rt_ringbuffer_init(struct rt_ringbuffer* rb, rt_uint8_t *pool, rt_uint16_t size)
{
	RT_ASSERT(rb != RT_NULL);

	/* initialize read and write index */
	rb->read_index = rb->write_index = 0;

	/* set buffer pool and size */
	rb->buffer_ptr = pool;
	rb->buffer_size = RT_ALIGN_DOWN(size, RT_ALIGN_SIZE);
}

rt_size_t rt_ringbuffer_put(struct rt_ringbuffer* rb, const rt_uint8_t *ptr, rt_uint16_t length)
{
	rt_uint16_t size;
	rt_uint16_t mask;

	RT_ASSERT(rb != RT_NULL);

	mask = rb->buffer_size - 1;
	/* whether has enough space */
	size = rb->buffer_size - ((rb->write_index - rb->read_index) & mask);

	/* no space */
	if (size == 0) return 0;
	/* drop some data */
	if (size < length) length = size;

	if (rb->read_index > rb->write_index)
	{
		/* read_index - write_index = empty space */
		memcpy(&rb->buffer_ptr[rb->write_index], ptr, length);
		rb->write_index += length;
	}
	else
	{
		if (rb->buffer_size - rb->write_index >= length)
		{
			/* there is enough space after write_index */
			memcpy(&rb->buffer_ptr[rb->write_index], ptr, length);
			rb->write_index = (rb->write_index + length) & mask;
		}
		else
		{
			memcpy(&rb->buffer_ptr[rb->write_index], ptr,
					rb->buffer_size - rb->write_index);
			memcpy(&rb->buffer_ptr[0], &ptr[rb->buffer_size - rb->write_index],
					length - (rb->buffer_size - rb->write_index));
			rb->write_index = length - (rb->buffer_size - rb->write_index);
		}
	}

	return length;
}

/**
 * put a character into ring buffer
 */
rt_size_t rt_ringbuffer_putchar(struct rt_ringbuffer* rb, const rt_uint8_t ch)
{
	rt_uint16_t next;
	rt_uint16_t mask;

	RT_ASSERT(rb != RT_NULL);
	/* whether has enough space */
	mask = rb->buffer_size - 1;
	next = (rb->write_index + 1) & mask;

	if (next == rb->read_index) return 0;

	/* put character */
	rb->buffer_ptr[rb->write_index] = ch;
	rb->write_index = next;

	return 1;
}

/**
 *  get data from ring buffer
 */
rt_size_t rt_ringbuffer_get(struct rt_ringbuffer* rb, rt_uint8_t *ptr, rt_uint16_t length)
{
	rt_size_t size;
	rt_uint16_t mask;

	RT_ASSERT(rb != RT_NULL);
	/* whether has enough data  */
	mask = rb->buffer_size - 1;
	size = (rb->write_index - rb->read_index) & mask;

	/* no data */
	if (size == 0) return 0;
	/* less data */
	if (size < length) length = size;

	if (rb->read_index > rb->write_index)
	{
		if (rb->buffer_size - rb->read_index >= length)
		{
			/* copy directly */
			memcpy(ptr, &rb->buffer_ptr[rb->read_index], length);
			rb->read_index = (rb->read_index + length) & mask;
		}
		else
		{
			/* copy first and second */
			memcpy(ptr, &rb->buffer_ptr[rb->read_index],
				   rb->buffer_size - rb->read_index);
			memcpy(&ptr[rb->buffer_size - rb->read_index], &rb->buffer_ptr[0],
				   length - rb->buffer_size + rb->read_index);
			rb->read_index = length - rb->buffer_size + rb->read_index;
		}
	}
	else
	{
		memcpy(ptr, &rb->buffer_ptr[rb->read_index], length);
		rb->read_index += length;
	}

	return length;
}

rt_size_t rt_ringbuffer_getchar(struct rt_ringbuffer* rb, rt_uint8_t *ch)
{
	rt_uint16_t next;
	rt_uint16_t mask;

	RT_ASSERT(rb != RT_NULL);
	
	/* ringbuffer is empty */
	if (rb->read_index == rb->write_index) return 0;

	/* whether has data */
	mask = rb->buffer_size - 1;
	next = (rb->read_index + 1) & mask;

	/* put character */
	*ch = rb->buffer_ptr[rb->read_index];
	rb->read_index = next;

	return 1;
}

/**
 * get available data size
 */
rt_size_t rt_ringbuffer_available_size(struct rt_ringbuffer* rb)
{
	rt_size_t size;
	rt_uint16_t mask;

	RT_ASSERT(rb != RT_NULL);

	mask = rb->buffer_size - 1;
	size = (rb->write_index - rb->read_index) & mask;

	/* return the available size */
	return size;
}

/**
 * get empty space size
 */
rt_size_t rt_ringbuffer_emptry_size(struct rt_ringbuffer* rb)
{
	RT_ASSERT(rb != RT_NULL);

	return rb->buffer_size - rt_ringbuffer_available_size(rb);
}
