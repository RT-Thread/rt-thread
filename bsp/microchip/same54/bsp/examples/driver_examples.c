/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

static uint8_t aes_plain_text[16]
    = {0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a};
static uint8_t aes_key[16]
    = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
static uint8_t aes_cipher_text[16]
    = {0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60, 0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97};
uint8_t aes_output[16] = {0x00};
/**
 * Example of using CRYPTOGRAPHY_0 to Encrypt/Decrypt datas.
 */
void CRYPTOGRAPHY_0_example(void)
{
	int32_t i;
	aes_sync_enable(&CRYPTOGRAPHY_0);
	aes_sync_set_encrypt_key(&CRYPTOGRAPHY_0, aes_key, AES_KEY_128);
	aes_sync_ecb_crypt(&CRYPTOGRAPHY_0, AES_ENCRYPT, aes_plain_text, aes_output);
	for (i = 0; i < 16; i++) {
		while (aes_output[i] != aes_cipher_text[i])
			;
	}
}

/**
 * Example of using TARGET_IO to write "Hello World" using the IO abstraction.
 */
void TARGET_IO_example(void)
{
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&TARGET_IO, &io);
	usart_sync_enable(&TARGET_IO);

	io_write(io, (uint8_t *)"Hello World!", 12);
}
