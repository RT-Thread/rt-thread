#include <rtthread.h>

#include <serial.h>

#define RT_CONSOLE_WIDTH		240
#define RT_CONSOLE_HEIGHT		320

#define RT_CONSOLE_FONT_WIDTH	8
#define RT_CONSOLE_FONT_HEIGHT	16

#define RT_CONSOLE_COL			(RT_CONSOLE_WIDTH/RT_CONSOLE_FONT_WIDTH)
#define RT_CONSOLE_ROW			(RT_CONSOLE_HEIGHT/RT_CONSOLE_FONT_HEIGHT)

#define RT_CONSOLE_TAB			4

#define RT_CONSOLE_FOREPIXEL	(0x001f)

extern struct serial_device uart0;

struct rt_console
{
	rt_uint8_t* video_ptr;
	rt_uint8_t* font_ptr;

	/* bpp and pixel of width */
	rt_uint8_t bpp;
	rt_uint32_t pitch;

	/* current cursor */
	rt_uint8_t current_col;
	rt_uint8_t current_row;
};
struct rt_console console;

void rt_hw_console_init(rt_uint8_t* video_ptr, rt_uint8_t* font_ptr, rt_uint8_t bpp);
void rt_hw_console_newline(void);
void rt_hw_console_putc(char c);
void rt_hw_console_clear(void);

void rt_hw_console_init(rt_uint8_t* video_ptr, rt_uint8_t* font_ptr, rt_uint8_t bpp)
{
	rt_memset(&console, 0, sizeof(struct rt_console));

	console.video_ptr = video_ptr;
	console.font_ptr = font_ptr;
	console.bpp = bpp;
	console.pitch = console.bpp * RT_CONSOLE_WIDTH;

	rt_hw_console_clear();
}

void rt_hw_console_putc(char c)
{
	switch (c)
	{
        case 10:
        case 11:
        case 12:
        case 13:
			/* to next line */
            rt_hw_console_newline();
            console.current_col = 0;
            break;

        case 9:
            console.current_col += RT_CONSOLE_TAB;
            break;

        default:
			{
				rt_uint8_t* font_ptr;
				register rt_uint32_t cursor;
				register rt_uint32_t i, j;

				if (console.current_col == RT_CONSOLE_COL)
				{
					rt_hw_console_newline();
					console.current_col = 0;

					rt_hw_console_putc(c);
					return;
				}

				font_ptr = console.font_ptr + c * RT_CONSOLE_FONT_HEIGHT;
				cursor = (console.current_row * RT_CONSOLE_FONT_HEIGHT) * console.pitch
					+ console.current_col * RT_CONSOLE_FONT_WIDTH * console.bpp;

				for (i = 0; i < RT_CONSOLE_FONT_HEIGHT; i ++ )
				{
					for (j = 0; j < RT_CONSOLE_FONT_WIDTH; j ++)
					{
						if ( ((font_ptr[i] >> (7-j)) & 0x01) != 0 )
						{
							/* draw a pixel */
							rt_uint8_t *ptr = &(console.video_ptr[cursor + i * console.pitch + j * console.bpp]);
							switch(console.bpp)
							{
							case 1:
								*ptr = RT_CONSOLE_FOREPIXEL;
								break;
							case 2:
								*(rt_uint16_t*)ptr = RT_CONSOLE_FOREPIXEL;
								break;
							case 3:
								ptr[0] = RT_CONSOLE_FOREPIXEL & 0xff;
								ptr[1] = (RT_CONSOLE_FOREPIXEL >> 8) & 0xff;
								ptr[2] = (RT_CONSOLE_FOREPIXEL >> 16) & 0xff;
								break;
							case 4:
								*(rt_uint32_t*)ptr = RT_CONSOLE_FOREPIXEL;
								break;
							}
						}
					}
				}

				console.current_col ++;
			}
			break;
	}
}

void rt_hw_console_newline()
{
	console.current_row ++;
	if (console.current_row >= RT_CONSOLE_ROW)
	{
		rt_uint32_t i;

		/* scroll to next line */
		for (i = 0; i < RT_CONSOLE_ROW - 1; i ++)
		{
			rt_memcpy(console.video_ptr + i * RT_CONSOLE_FONT_HEIGHT * console.pitch,
				console.video_ptr + (i + 1) * RT_CONSOLE_FONT_HEIGHT * console.pitch,
				RT_CONSOLE_FONT_HEIGHT * console.pitch);
		}

		/* clear last line */
		rt_memset(console.video_ptr + (RT_CONSOLE_ROW - 1) * RT_CONSOLE_FONT_HEIGHT * console.pitch,
			0,
			RT_CONSOLE_FONT_HEIGHT * console.pitch);

		console.current_row = RT_CONSOLE_ROW - 1;
	}
}

void rt_hw_console_clear()
{
	console.current_col = 0;
	console.current_row = 0;

	rt_memset(console.video_ptr, 0, RT_CONSOLE_HEIGHT * console.pitch);
}

/* write one character to serial, must not trigger interrupt */
void rt_hw_serial_putc(const char c)
{
	/*
		to be polite with serial console add a line feed
		to the carriage return character
	*/
	if (c=='\n')rt_hw_serial_putc('\r');

	while (!(uart0.uart_device->ustat & USTAT_TXB_EMPTY));
	uart0.uart_device->utxh = (c & 0x1FF);
}

/**
 * This function is used by rt_kprintf to display a string on console.
 *
 * @param str the displayed string
 */
void rt_hw_console_output(const char* str)
{
	while (*str)
	{
		rt_hw_serial_putc(*str++);
	}
}

