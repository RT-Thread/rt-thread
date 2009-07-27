#include <rtthread.h>

#include "dac.h"

short dac_buffer[MAX_BUFFERS][DAC_BUFFER_MAX_SIZE];
int dac_buffer_size[MAX_BUFFERS];
int stopped;
unsigned long current_srate;
unsigned int underruns;

void dac_reset()
{
	stopped = 1;
	underruns = 0;
	dac_set_srate(44100);
}

// return the index of the next writeable buffer or -1 on failure
int dac_get_writeable_buffer()
{
	return 0;
}

// returns -1 if there is no free DMA buffer
int dac_fill_dma()
{
	return 0;
}

int dac_set_srate(unsigned long srate)
{
	if (current_srate == srate)
		return 0;
		
	rt_kprintf("setting rate %lu\n", srate);
	switch(srate) {
	case 8000:	
	case 8021:	
	case 32000:	
	case 44100:	
	case 48000:	
	case 88200:	
	case 96000:	
		break;
	default:
		return -1;
	}

	current_srate = srate;
	return 0;
}

void dac_init(void)
{
	dac_reset();
}
