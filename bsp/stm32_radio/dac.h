#ifndef _DAC_H_
#define _DAC_H_

#define MAX_BUFFERS 1
#define DAC_BUFFER_MAX_SIZE 2400
extern short dac_buffer[MAX_BUFFERS][DAC_BUFFER_MAX_SIZE];
extern int dac_buffer_size[MAX_BUFFERS];
extern unsigned long current_srate;
extern unsigned int underruns;

void dac_reset(void);
int dac_get_writeable_buffer(void);
int dac_get_readable_buffer(void);
int dac_readable_buffers(void);
int dac_writeable_buffers(void);
int dac_busy_buffers(void);
int adc_busy_buffers(void);
int dac_fill_dma(void);

void dac_enable_dma(void);
void dac_disable_dma(void);
int dac_next_dma_empty(void);
int dac_first_dma_empty(void);
int adc_next_dma_empty(void);
int adc_first_dma_empty(void);
void dac_set_first_dma(short *buffer, int n);
void dac_set_next_dma(short *buffer, int n);
int dma_endtx(void);
void dac_write_reg(unsigned char reg, unsigned short value);
int dac_set_srate(unsigned long srate);
void dac_init(void);

#endif /* _DAC_H_ */
