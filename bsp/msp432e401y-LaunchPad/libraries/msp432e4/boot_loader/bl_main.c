//*****************************************************************************
//
// bl_main.c - The file holds the main control loop of the boot loader.
//
// Copyright (c) 2006-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "bl_config.h"
#include "ti/devices/msp432e4/inc/msp.h"
#include "ti/devices/msp432e4/boot_loader/bl_commands.h"
#include "ti/devices/msp432e4/boot_loader/bl_decrypt.h"
#include "ti/devices/msp432e4/boot_loader/bl_flash.h"
#include "ti/devices/msp432e4/boot_loader/bl_hooks.h"
#include "ti/devices/msp432e4/boot_loader/bl_i2c.h"
#include "ti/devices/msp432e4/boot_loader/bl_packet.h"
#include "ti/devices/msp432e4/boot_loader/bl_ssi.h"
#include "ti/devices/msp432e4/boot_loader/bl_uart.h"
#ifdef CHECK_CRC
#include "ti/devices/msp432e4/boot_loader/bl_crc32.h"
#endif

//*****************************************************************************
//
// Make sure that the application start address falls on a flash page boundary
//
//*****************************************************************************
#if (APP_START_ADDRESS & (FLASH_PAGE_SIZE - 1))
#error ERROR: APP_START_ADDRESS must be a multiple of FLASH_PAGE_SIZE bytes!
#endif

//*****************************************************************************
//
// Make sure that the flash reserved space is a multiple of flash pages.
//
//*****************************************************************************
#if (FLASH_RSVD_SPACE & (FLASH_PAGE_SIZE - 1))
#error ERROR: FLASH_RSVD_SPACE must be a multiple of FLASH_PAGE_SIZE bytes!
#endif

//*****************************************************************************
//
//! \addtogroup bl_main_api
//! @{
//
//*****************************************************************************
#if defined(I2C_ENABLE_UPDATE) || defined(SSI_ENABLE_UPDATE) || \
    defined(UART_ENABLE_UPDATE) || defined(DOXYGEN)

//*****************************************************************************
//
// A prototype for the function (in the startup code) for calling the
// application.
//
//*****************************************************************************
extern void CallApplication(uint32_t ui32Base);

//*****************************************************************************
//
// A prototype for the function (in the startup code) for a predictable length
// delay.
//
//*****************************************************************************
extern void Delay(uint32_t ui32Count);

//*****************************************************************************
//
// Holds the current status of the last command that was issued to the boot
// loader.
//
//*****************************************************************************
uint8_t g_ui8Status;

//*****************************************************************************
//
// This holds the current remaining size in bytes to be downloaded.
//
//*****************************************************************************
uint32_t g_ui32TransferSize;

//*****************************************************************************
//
// This holds the total size of the firmware image being downloaded (if the
// protocol in use provides this).
//
//*****************************************************************************
#if (defined BL_PROGRESS_FN_HOOK) || (defined CHECK_CRC)
uint32_t g_ui32ImageSize;
#endif

//*****************************************************************************
//
// This holds the current address that is being written to during a download
// command.
//
//*****************************************************************************
uint32_t g_ui32TransferAddress;
#ifdef CHECK_CRC
uint32_t g_ui32ImageAddress;
#endif

//*****************************************************************************
//
// This is the data buffer used during transfers to the boot loader.
//
//*****************************************************************************
uint32_t g_pui32DataBuffer[BUFFER_SIZE];

//*****************************************************************************
//
// This is an specially aligned buffer pointer to g_pui32DataBuffer to make
// copying to the buffer simpler.  It must be offset to end on an address that
// ends with 3.
//
//*****************************************************************************
uint8_t *g_pui8DataBuffer;

//*****************************************************************************
//
// Converts a word from big endian to little endian.  This macro uses compiler-
// specific constructs to perform an inline insertion of the "rev" instruction,
// which performs the byte swap directly.
//
//*****************************************************************************
#if defined(__ICCARM__)
#include <intrinsics.h>
#define SwapWord(x)             __REV(x)
#endif
#if defined(__CCARM__) || defined(__GNUC__)
#define SwapWord(x) __extension__                                             \
        ({                                                                    \
             register uint32_t __ret, __inp = x;                              \
             __asm__("rev %0, %1" : "=r" (__ret) : "r" (__inp));              \
             __ret;                                                           \
        })
#endif
#if defined(rvmdk) || defined(__ARMCC_VERSION)
#define SwapWord(x)             __rev(x)
#endif
#if defined(__TI_ARM__)
uint32_t
SwapWord(uint32_t x)
{
    __asm("    rev     r0, r0\n"
          "    bx      lr\n"); // need this to make sure r0 is returned
    return(x + 1); // return makes compiler happy - ignored
}
#endif

//*****************************************************************************
//
//! Configures the microcontroller.
//!
//! This function configures the peripherals and GPIOs of the microcontroller,
//! preparing it for use by the boot loader.  The interface that has been
//! selected as the update port will be configured, and auto-baud will be
//! performed if required.
//!
//! \return None.
//
//*****************************************************************************
void
ConfigureDevice(void)
{
#ifdef UART_ENABLE_UPDATE
    uint32_t ui32ProcRatio;
#endif

#ifdef CRYSTAL_FREQ
    //
    // Since the crystal frequency was specified, enable the main oscillator
    // and clock the processor from it.
    //
    //
    // Since the crystal frequency was specified, enable the main oscillator
    // and clock the processor from it. Check for whether the Oscillator range
    // has to be set and wait states need to be updated
    //
    if(CRYSTAL_FREQ >= 10000000)
    {
        SYSCTL->MOSCCTL |= (SYSCTL_MOSCCTL_OSCRNG);
        SYSCTL->MOSCCTL &= ~(SYSCTL_MOSCCTL_PWRDN |
                             SYSCTL_MOSCCTL_NOXTAL);
    }
    else
    {
        SYSCTL->MOSCCTL &= ~(SYSCTL_MOSCCTL_PWRDN |
                             SYSCTL_MOSCCTL_NOXTAL);
    }

    //
    // Wait for the Oscillator to Stabilize
    //
    Delay(524288);

    if(CRYSTAL_FREQ > 16000000)
    {
        SYSCTL->MEMTIM0  = (SYSCTL_MEMTIM0_FBCHT_1_5 |
                            (1 << SYSCTL_MEMTIM0_FWS_S) |
                             SYSCTL_MEMTIM0_EBCHT_1_5 |
                            (1 << SYSCTL_MEMTIM0_EWS_S) |
                             SYSCTL_MEMTIM0_MB1);
        SYSCTL->RSCLKCFG = (SYSCTL_RSCLKCFG_MEMTIMU |
                            SYSCTL_RSCLKCFG_OSCSRC_MOSC);
    }
    else
    {
        SYSCTL->RSCLKCFG = (SYSCTL_RSCLKCFG_OSCSRC_MOSC);
    }
#endif

#ifdef I2C_ENABLE_UPDATE
    //
    // Enable the clocks to the I2C and GPIO modules.
    //
    SYSCTL->RCGCGPIO |= (I2C_SCLPIN_CLOCK_ENABLE |
                               I2C_SDAPIN_CLOCK_ENABLE);
    SYSCTL->RCGCI2C |= I2C_CLOCK_ENABLE;

    //
    // Configure the GPIO pins for hardware control, open drain with pull-up,
    // and enable them.
    //
    I2C_SCLPIN_BASE->AFSEL |= I2C_CLK;
    I2C_SCLPIN_BASE->PCTL |= I2C_CLK_PCTL;
    I2C_SCLPIN_BASE->DEN |= I2C_CLK;
    I2C_SCLPIN_BASE->ODR &= ~(I2C_CLK);
    I2C_SCLPIN_BASE->PUR |= I2C_CLK;

    I2C_SDAPIN_BASE->AFSEL |= I2C_DATA;
    I2C_SDAPIN_BASE->PCTL |= I2C_DATA_PCTL;
    I2C_SDAPIN_BASE->DEN |= I2C_DATA;
    I2C_SDAPIN_BASE->ODR |= I2C_DATA;
    I2C_SDAPIN_BASE->PUR |= I2C_DATA;

    //
    // Enable the I2C Slave Mode.
    //
    I2Cx->MCR = I2C_MCR_MFE | I2C_MCR_SFE;

    //
    // Setup the I2C Slave Address.
    //
    I2Cx->SOAR = I2C_SLAVE_ADDR;

    //
    // Enable the I2C Slave Device on the I2C bus.
    //
    I2Cx->SCSR = I2C_SCSR_DA;
#endif

#ifdef SSI_ENABLE_UPDATE
    //
    // Enable the clocks to the SSI and GPIO modules.
    //
    SYSCTL->RCGCGPIO |= (SSI_CLKPIN_CLOCK_ENABLE |
                         SSI_FSSPIN_CLOCK_ENABLE |
                         SSI_MISOPIN_CLOCK_ENABLE |
                         SSI_MOSIPIN_CLOCK_ENABLE);
    SYSCTL->RCGCSSI |= SSI_CLOCK_ENABLE;

    //
    // Make the pin be peripheral controlled.
    //
    SSI_CLKPIN_BASE->AFSEL |= SSI_CLK;
    SSI_CLKPIN_BASE->PCTL |= SSI_CLK_PCTL;
    SSI_CLKPIN_BASE->DEN |= SSI_CLK;
    SSI_CLKPIN_BASE->ODR &= ~(SSI_CLK);

    SSI_FSSPIN_BASE->AFSEL |= SSI_CS;
    SSI_FSSPIN_BASE->PCTL |= SSI_CS_PCTL;
    SSI_FSSPIN_BASE->DEN |= SSI_CS;
    SSI_FSSPIN_BASE->ODR &= ~(SSI_CS);

    SSI_MISOPIN_BASE->AFSEL |= SSI_TX;
    SSI_MISOPIN_BASE->PCTL |= SSI_TX_PCTL;
    SSI_MISOPIN_BASE->DEN |= SSI_TX;
    SSI_MISOPIN_BASE->ODR &= ~(SSI_TX);

    SSI_MOSIPIN_BASE->AFSEL |= SSI_RX;
    SSI_MOSIPIN_BASE->PCTL |= SSI_RX_PCTL;
    SSI_MOSIPIN_BASE->DEN |= SSI_RX;
    SSI_MOSIPIN_BASE->ODR &= ~(SSI_RX);

    //
    // Set the SSI protocol to Motorola with default clock high and data
    // valid on the rising edge.
    //
    SSIx->CR0 = (SSI_CR0_SPH | SSI_CR0_SPO | (DATA_BITS_SSI - 1));

    //
    // Enable the SSI interface in slave mode.
    //
    SSIx->CR1 = SSI_CR1_MS | SSI_CR1_SSE;
#endif

#ifdef UART_ENABLE_UPDATE
    //
    // Enable the the clocks to the UART and GPIO modules.
    //
    SYSCTL->RCGCGPIO |= (UART_RXPIN_CLOCK_ENABLE |
                          UART_TXPIN_CLOCK_ENABLE);
    SYSCTL->RCGCUART |= UART_CLOCK_ENABLE;

    //
    // Keep attempting to sync until we are successful.
    //
#ifdef UART_AUTOBAUD
    while(UARTAutoBaud(&ui32ProcRatio) < 0)
    {
    }
#else
    ui32ProcRatio = UART_BAUD_RATIO(UART_FIXED_BAUDRATE);
#endif

    //
    // Make the pin be peripheral controlled.
    //
    UART_RXPIN_BASE->AFSEL |= UART_RX;
    UART_RXPIN_BASE->PCTL |= UART_RX_PCTL;
    UART_RXPIN_BASE->ODR &= ~(UART_RX);
    UART_RXPIN_BASE->DEN |= UART_RX;

    UART_TXPIN_BASE->AFSEL |= UART_TX;
    UART_TXPIN_BASE->PCTL |= UART_TX_PCTL;
    UART_TXPIN_BASE->ODR &= ~(UART_TX);
    UART_TXPIN_BASE->DEN |= UART_TX;

    //
    // Set the baud rate.
    //
    UARTx->IBRD = ui32ProcRatio >> 6;
    UARTx->FBRD = ui32ProcRatio & UART_FBRD_DIVFRAC_M;

    //
    // Set data length, parity, and number of stop bits to 8-N-1.
    //
    UARTx->LCRH = UART_LCRH_WLEN_8 | UART_LCRH_FEN;

    //
    // Enable RX, TX, and the UART.
    //
    UARTx->CTL = (UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE);

#ifdef UART_AUTOBAUD
    //
    // Need to ack in the UART case to hold it up while we get things set up.
    //
    AckPacket();
#endif
#endif
}

//*****************************************************************************
//
//! This function performs the update on the selected port.
//!
//! This function is called directly by the boot loader or it is called as a
//! result of an update request from the application.
//!
//! \return Never returns.
//
//*****************************************************************************
void
Updater(void)
{
    uint32_t ui32Size, ui32Temp, ui32FlashSize;
#ifdef CHECK_CRC
    uint32_t ui32Retcode;
#endif

    //
    // This ensures proper alignment of the global buffer so that the one byte
    // size parameter used by the packetized format is easily skipped for data
    // transfers.
    //
    g_pui8DataBuffer = ((uint8_t *)g_pui32DataBuffer) + 3;

    //
    // Insure that the COMMAND_SEND_DATA cannot be sent to erase the boot
    // loader before the application is erased.
    //
    g_ui32TransferAddress = 0xffffffff;

    //
    // Read any data from the serial port in use.
    //
    while(1)
    {
        //
        // Receive a packet from the port in use.
        //
        ui32Size = sizeof(g_pui32DataBuffer) - 3;
        if(ReceivePacket(g_pui8DataBuffer, &ui32Size) != 0)
        {
            continue;
        }

        //
        // The first byte of the data buffer has the command and determines
        // the format of the rest of the bytes.
        //
        switch(g_pui8DataBuffer[0])
        {
            //
            // This was a simple ping command.
            //
            case COMMAND_PING:
            {
                //
                // This command always sets the status to COMMAND_RET_SUCCESS.
                //
                g_ui8Status = COMMAND_RET_SUCCESS;

                //
                // Just acknowledge that the command was received.
                //
                AckPacket();

                //
                // Go back and wait for a new command.
                //
                break;
            }

            //
            // This command indicates the start of a download sequence.
            //
            case COMMAND_DOWNLOAD:
            {
                //
                // Until determined otherwise, the command status is success.
                //
                g_ui8Status = COMMAND_RET_SUCCESS;

                //
                // A simple do/while(0) control loop to make error exits
                // easier.
                //
                do
                {
                    //
                    // See if a full packet was received.
                    //
                    if(ui32Size != 9)
                    {
                        //
                        // Indicate that an invalid command was received.
                        //
                        g_ui8Status = COMMAND_RET_INVALID_CMD;

                        //
                        // This packet has been handled.
                        //
                        break;
                    }

                    //
                    // Get the address and size from the command.
                    //
                    g_ui32TransferAddress = SwapWord(g_pui32DataBuffer[1]);
                    g_ui32TransferSize = SwapWord(g_pui32DataBuffer[2]);

                    //
                    // Depending upon the build options set, keep a copy of
                    // the original size and start address because we will need
                    // these later.
                    //
#if (defined BL_PROGRESS_FN_HOOK) || (defined CHECK_CRC)
                    g_ui32ImageSize = g_ui32TransferSize;
#endif
#ifdef CHECK_CRC
                    g_ui32ImageAddress = g_ui32TransferAddress;
#endif

                    //
                    // Check for a valid starting address and image size.
                    //
                    if(!BL_FLASH_AD_CHECK_FN_HOOK(g_ui32TransferAddress,
                                                  g_ui32TransferSize))
                    {
                        //
                        // Set the code to an error to indicate that the last
                        // command failed.  This informs the updater program
                        // that the download command failed.
                        //
                        g_ui8Status = COMMAND_RET_INVALID_ADR;

                        //
                        // This packet has been handled.
                        //
                        break;
                    }


                    //
                    // Only erase the space that we need if we are not
                    // protecting the code, otherwise erase the entire flash.
                    //
#ifdef FLASH_CODE_PROTECTION
                    ui32FlashSize = BL_FLASH_SIZE_FN_HOOK();
#ifdef FLASH_RSVD_SPACE
                    if((ui32FlashSize - FLASH_RSVD_SPACE) !=
                       g_ui32TransferAddress)
                    {
                        ui32FlashSize -= FLASH_RSVD_SPACE;
                    }
#endif
#else
                    ui32FlashSize = g_ui32TransferAddress + g_ui32TransferSize;
#endif

                    //
                    // Clear the flash access interrupt.
                    //
                    BL_FLASH_CL_ERR_FN_HOOK();

                    //
                    // Leave the boot loader present until we start getting an
                    // image.
                    //
                    for(ui32Temp = g_ui32TransferAddress;
                        ui32Temp < ui32FlashSize; ui32Temp += FLASH_PAGE_SIZE)
                    {
                        //
                        // Erase this block.
                        //
                        BL_FLASH_ERASE_FN_HOOK(ui32Temp);
                    }

                    //
                    // Return an error if an access violation occurred.
                    //
                    if(BL_FLASH_ERROR_FN_HOOK())
                    {
                        g_ui8Status = COMMAND_RET_FLASH_FAIL;
                    }
                }
                while(0);

                //
                // See if the command was successful.
                //
                if(g_ui8Status != COMMAND_RET_SUCCESS)
                {
                    //
                    // Setting g_ui32TransferSize to zero makes
                    // COMMAND_SEND_DATA fail to accept any data.
                    //
                    g_ui32TransferSize = 0;
                }

                //
                // Acknowledge that this command was received correctly.  This
                // does not indicate success, just that the command was
                // received.
                //
                AckPacket();

                //
                // If we have a start notification hook function, call it
                // now if everything is OK.
                //
#ifdef BL_START_FN_HOOK
                if(g_ui32TransferSize)
                {
                    BL_START_FN_HOOK();
                }
#endif

                //
                // Go back and wait for a new command.
                //
                break;
            }

            //
            // This command indicates that control should be transferred to
            // the specified address.
            //
            case COMMAND_RUN:
            {
                //
                // Acknowledge that this command was received correctly.  This
                // does not indicate success, just that the command was
                // received.
                //
                AckPacket();

                //
                // See if a full packet was received.
                //
                if(ui32Size != 5)
                {
                    //
                    // Indicate that an invalid command was received.
                    //
                    g_ui8Status = COMMAND_RET_INVALID_CMD;

                    //
                    // This packet has been handled.
                    //
                    break;
                }

                //
                // Get the address to which control should be transferred.
                //
                g_ui32TransferAddress = SwapWord(g_pui32DataBuffer[1]);

                //
                // This determines the size of the flash available on the
                // device in use.
                //
                ui32FlashSize = BL_FLASH_SIZE_FN_HOOK();

                //
                // Test if the transfer address is valid for this device.
                //
                if(g_ui32TransferAddress >= ui32FlashSize)
                {
                    //
                    // Indicate that an invalid address was specified.
                    //
                    g_ui8Status = COMMAND_RET_INVALID_ADR;

                    //
                    // This packet has been handled.
                    //
                    break;
                }

                //
                // Make sure that the ACK packet has been sent.
                //
                FlushData();

                //
                // Reset and disable the peripherals used by the boot loader.
                //
#ifdef I2C_ENABLE_UPDATE
                SYSCTL->RCGCI2C &= ~I2C_CLOCK_ENABLE;
                SYSCTL->SRI2C = I2C_CLOCK_ENABLE;
                SYSCTL->SRI2C = 0;
#endif
#ifdef UART_ENABLE_UPDATE
                SYSCTL->RCGCUART &= ~UART_CLOCK_ENABLE;
                SYSCTL->SRUART = UART_CLOCK_ENABLE;
                SYSCTL->SRUART = 0;
#endif
#ifdef SSI_ENABLE_UPDATE
                SYSCTL->RCGCSSI &= ~SSI_CLOCK_ENABLE;
                SYSCTL->SRSSI = SSI_CLOCK_ENABLE;
                SYSCTL->SRSSI = 0;
#endif

                //
                // Branch to the specified address.  This should never return.
                // If it does, very bad things will likely happen since it is
                // likely that the copy of the boot loader in SRAM will have
                // been overwritten.
                //
                ((void (*)(void))g_ui32TransferAddress)();

                //
                // In case this ever does return and the boot loader is still
                // intact, simply reset the device.
                //
                SCB->AIRCR = NVIC_APINT_VECTKEY | NVIC_APINT_SYSRESETREQ;

                //
                // The microcontroller should have reset, so this should
                // never be reached.  Just in case, loop forever.
                //
                while(1)
                {
                }
            }

            //
            // This command just returns the status of the last command that
            // was sent.
            //
            case COMMAND_GET_STATUS:
            {
                //
                // Acknowledge that this command was received correctly.  This
                // does not indicate success, just that the command was
                // received.
                //
                AckPacket();

                //
                // Return the status to the updater.
                //
                SendPacket(&g_ui8Status, 1);

                //
                // Go back and wait for a new command.
                //
                break;
            }

            //
            // This command is sent to transfer data to the device following
            // a download command.
            //
            case COMMAND_SEND_DATA:
            {
                //
                // Until determined otherwise, the command status is success.
                //
                g_ui8Status = COMMAND_RET_SUCCESS;

                //
                // If this is overwriting the boot loader then the application
                // has already been erased so now erase the boot loader.
                //
                if(g_ui32TransferAddress == 0)
                {
                    //
                    // Clear the flash access interrupt.
                    //
                    BL_FLASH_CL_ERR_FN_HOOK();

                    //
                    // Erase the boot loader.
                    //
                    for(ui32Temp = 0; ui32Temp < APP_START_ADDRESS;
                        ui32Temp += FLASH_PAGE_SIZE)
                    {
                        //
                        // Erase this block.
                        //
                        BL_FLASH_ERASE_FN_HOOK(ui32Temp);
                    }

                    //
                    // Return an error if an access violation occurred.
                    //
                    if(BL_FLASH_ERROR_FN_HOOK())
                    {
                        //
                        // Setting g_ui32TransferSize to zero makes
                        // COMMAND_SEND_DATA fail to accept any more data.
                        //
                        g_ui32TransferSize = 0;

                        //
                        // Indicate that the flash erase failed.
                        //
                        g_ui8Status = COMMAND_RET_FLASH_FAIL;
                    }
                }

                //
                // Take one byte off for the command.
                //
                ui32Size = ui32Size - 1;

                //
                // Check if there are any more bytes to receive.
                //
                if(g_ui32TransferSize >= ui32Size)
                {
                    //
                    // If we have been provided with a decryption hook function
                    // call it here.
                    //
#ifdef BL_DECRYPT_FN_HOOK
                    BL_DECRYPT_FN_HOOK(g_pui8DataBuffer + 1, ui32Size);
#endif

                    //
                    // Write this block of data to the flash
                    //
                    BL_FLASH_PROGRAM_FN_HOOK(g_ui32TransferAddress,
                                             (uint8_t *) &g_pui32DataBuffer[1],
                                             ((ui32Size + 3) & ~3));

                    //
                    // Return an error if an access violation occurred.
                    //
                    if(BL_FLASH_ERROR_FN_HOOK())
                    {
                        //
                        // Indicate that the flash programming failed.
                        //
                        g_ui8Status = COMMAND_RET_FLASH_FAIL;
                    }
                    else
                    {
                        //
                        // Now update the address to program.
                        //
                        g_ui32TransferSize -= ui32Size;
                        g_ui32TransferAddress += ui32Size;

                        //
                        // If a progress hook function has been provided, call
                        // it here.
                        //
#ifdef BL_PROGRESS_FN_HOOK
                        BL_PROGRESS_FN_HOOK(g_ui32ImageSize -
                                            g_ui32TransferSize,
                                            g_ui32ImageSize);
#endif

#ifdef CHECK_CRC
                        //
                        // If we've reached the end, check the CRC in the
                        // image to determine whether or not we report an error
                        // back to the host.
                        //
                        if(g_ui32TransferSize == 0)
                        {
                            InitCRC32Table();
                            ui32Retcode = CheckImageCRC32(
                                    (uint32_t *)g_ui32ImageAddress);

                            //
                            // Was the CRC good?  We consider the CRC good if
                            // the header is found and the embedded CRC matches
                            // the calculated value or, if ENFORCE_CRC is not
                            // defined, if the header exists but is unpopulated.
                            //
#ifdef ENFORCE_CRC
                            if(ui32Retcode == CHECK_CRC_OK)
#else
                            if((ui32Retcode == CHECK_CRC_OK) ||
                               (ui32Retcode == CHECK_CRC_NO_LENGTH))
#endif
                            {
                                //
                                // The calculated CRC agreed with the embedded
                                // value.
                                //
                                g_ui8Status = COMMAND_RET_SUCCESS;
                            }
                            else
                            {
                                //
                                // The calculated CRC didn't match the expected
                                // value or the image didn't contain an embedded
                                // CRC.
                                //
                                g_ui8Status = COMMAND_RET_CRC_FAIL;
                            }
                        }
#endif
                    }
                }
                else
                {
                    //
                    // This indicates that too much data is being sent to the
                    // device.
                    //
                    g_ui8Status = COMMAND_RET_INVALID_ADR;
                }

                //
                // Acknowledge that this command was received correctly.  This
                // does not indicate success, just that the command was
                // received.
                //
                AckPacket();

                //
                // If we have an end notification hook function, and we've
                // reached the end, call it now.
                //
#ifdef BL_END_FN_HOOK
                if(g_ui32TransferSize == 0)
                {
                    BL_END_FN_HOOK();
                }
#endif

                //
                // Go back and wait for a new command.
                //
                break;
            }

            //
            // This command is used to reset the device.
            //
            case COMMAND_RESET:
            {
                //
                // Send out a one-byte ACK to ensure the byte goes back to the
                // host before we reset everything.
                //
                AckPacket();

                //
                // Make sure that the ACK packet has been sent.
                //
                FlushData();

                //
                // Perform a software reset request.  This will cause the
                // microcontroller to reset; no further code will be executed.
                //
                SCB->AIRCR = NVIC_APINT_VECTKEY | NVIC_APINT_SYSRESETREQ;

                //
                // The microcontroller should have reset, so this should never
                // be reached.  Just in case, loop forever.
                //
                while(1)
                {
                }
            }

            //
            // Just acknowledge the command and set the error to indicate that
            // a bad command was sent.
            //
            default:
            {
                //
                // Acknowledge that this command was received correctly.  This
                // does not indicate success, just that the command was
                // received.
                //
                AckPacket();

                //
                // Indicate that a bad comand was sent.
                //
                g_ui8Status = COMMAND_RET_UNKNOWN_CMD;

                //
                // Go back and wait for a new command.
                //
                break;
            }
        }
    }
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
#endif
