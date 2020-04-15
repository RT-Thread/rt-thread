//*****************************************************************************
//
//  am_hal_queue.c
//! @file
//!
//! @brief Functions for implementing a queue system.
//!
//! @addtogroup Miscellaneous2 Software Features (MISC)
//! @ingroup apollo2hal
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2017, Ambiq Micro
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision 1.2.11 of the AmbiqSuite Development Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "am_mcu_apollo.h"

//*****************************************************************************
//
//! @brief Initializes a queue.
//!
//! @param psQueue - Pointer to a queue structure.
//! @param pvData - Pointer to a memory location to be used for data storage.
//! @param ui32ItemSize - Number of bytes per item in the queue.
//! @param ui32ArraySize - Number of bytes in the data array.
//!
//! This function initializes the members of a queue structure and attaches it
//! to an array of memory that it can use for storage. This function should be
//! called before the queue is used.
//!
//! In this example, we are creating a queue that can hold 1024 32-bit
//! integers. The integers themselves will be stored in the array named
//! pui32WorkingSpace, while information about the queue itself will be stored
//! in sDataQueue.
//!
//! @note The caller should not modify any of the members of am_hal_queue_t
//! structures. The queue API will handle these members in a thread-safe way.
//!
//! @note The queue will remember what size data is in it. Other queue API
//! functions will perform transfers in units of "items" where one "item" is
//! the number of bytes you specify in the \e ui32ItemSize argument upon
//! initialization.
//!
//! Example usage:
//!
//! @code
//!
//! //
//! // Declare a queue structure and an array of bytes we can use to store
//! // data.
//! //
//! am_hal_queue_t sDataQueue;
//! uint32_t pui32WorkingSpace[1024];
//!
//! //
//! // Attach the queue structure to the working memory.
//! //
//! am_hal_queue_init(&sDataQueue, pui8WorkingSpace, sizeof(uint32_t)
//!                   sizeof(pui32WorkingSpace));
//!
//! @endcode
//!
//! The am_hal_queue_from_array macro is a convenient shorthand for this
//! operation. The code below does the same thing as the code above.
//!
//! @code
//!
//! //
//! // Declare a queue structure and an array of bytes we can use to store
//! // data.
//! //
//! am_hal_queue_t sDataQueue;
//! uint32_t pui32WorkingSpace[1024];
//!
//! //
//! // Attach the queue structure to the working memory.
//! //
//! am_hal_queue_from_array(&sDataQueue, pui8WorkingSpace);
//!
//! @endcode
//
//*****************************************************************************
void
am_hal_queue_init(am_hal_queue_t *psQueue, void *pvData, uint32_t ui32ItemSize,
                  uint32_t ui32ArraySize)
{
    psQueue->ui32WriteIndex = 0;
    psQueue->ui32ReadIndex = 0;
    psQueue->ui32Length = 0;
    psQueue->ui32Capacity = ui32ArraySize;
    psQueue->ui32ItemSize = ui32ItemSize;
    psQueue->pui8Data = (uint8_t *) pvData;
}

//*****************************************************************************
//
//! @brief Adds an item to the Queue
//!
//! @param psQueue - Pointer to a queue structure.
//! @param pvSource - Pointer to the data to be added.
//! @param ui32NumItems - Number of items to be added.
//!
//! This function will copy the data pointed to by pvSource into the queue. The
//! \e ui32NumItems term specifies the number of items to be copied from \e
//! pvSource. The size of an "item" depends on how the queue was initialized.
//! Please see am_hal_queue_init() for more information on this.
//!
//! @return true if the add operation was successful, or false if the queue
//! didn't have enough space.
//
//*****************************************************************************
bool
am_hal_queue_item_add(am_hal_queue_t *psQueue, const void *pvSource, uint32_t ui32NumItems)
{
    uint32_t i;
    uint8_t *pui8Source;
    uint32_t ui32Bytes = ui32NumItems * psQueue->ui32ItemSize;
    bool bSuccess = false;
    uint32_t ui32Primask;

    pui8Source = (uint8_t *) pvSource;

    ui32Primask = am_hal_interrupt_master_disable();

    //
    // Check to make sure that the buffer isn't already full
    //
    if ( am_hal_queue_space_left(psQueue) >= ui32Bytes )
    {
        //
        // Loop over the bytes in the source array.
        //
        for ( i = 0; i < ui32Bytes; i++ )
        {
            //
            // Write the value to the buffer.
            //
            psQueue->pui8Data[psQueue->ui32WriteIndex] = pui8Source[i];

            //
            // Advance the write index, making sure to wrap if necessary.
            //
            psQueue->ui32WriteIndex = ((psQueue->ui32WriteIndex + 1) %
                                        psQueue->ui32Capacity);
        }

        //
        // Update the length value appropriately.
        //
        psQueue->ui32Length += ui32Bytes;

        //
        // Report a success.
        //
        bSuccess = true;
    }
    else
    {
        //
        // The buffer can't fit the amount of data requested. Return a
        // failure.
        //
        bSuccess = false;
    }

    am_hal_interrupt_master_set(ui32Primask);

    return bSuccess;
}

//*****************************************************************************
//
//! @brief Removes an item from the Queue
//!
//! @param psQueue - Pointer to a queue structure.
//! @param pvDest - Pointer to the data to be added.
//! @param ui32NumItems - Number of items to be added.
//!
//! This function will copy the data from the queue into the memory pointed to
//! by pvDest. The \e ui32NumItems term specifies the number of items to be
//! copied from the queue. The size of an "item" depends on how the queue was
//! initialized.  Please see am_hal_queue_init() for more information on this.
//!
//! @return true if we were able to pull the requested number of items from the
//! queue, or false if the queue didn't have that many items to pull.
//
//*****************************************************************************
bool
am_hal_queue_item_get(am_hal_queue_t *psQueue, void *pvDest, uint32_t ui32NumItems)
{
    uint32_t i;
    uint8_t *pui8Dest;
    uint32_t ui32Bytes = ui32NumItems * psQueue->ui32ItemSize;
    bool bSuccess = false;
    uint32_t ui32Primask;

    pui8Dest = (uint8_t *) pvDest;

    ui32Primask = am_hal_interrupt_master_disable();

    //
    // Check to make sure that the buffer isn't empty
    //
    if ( am_hal_queue_data_left(psQueue) >= ui32Bytes )
    {
        //
        // Loop over the bytes in the destination array.
        //
        for ( i = 0; i < ui32Bytes; i++ )
        {
            //
            // Grab the next value from the buffer.
            //
            pui8Dest[i] = psQueue->pui8Data[psQueue->ui32ReadIndex];

            //
            // Advance the read index, wrapping if needed.
            //
            psQueue->ui32ReadIndex = ((psQueue->ui32ReadIndex + 1) %
                                       psQueue->ui32Capacity);
        }

        //
        // Adjust the length value to reflect the change.
        //
        psQueue->ui32Length -= ui32Bytes;

        //
        // Report a success.
        //
        bSuccess = true;
    }
    else
    {
        //
        // If the buffer didn't have enough data, just return false.
        //
        bSuccess = false;
    }

    am_hal_interrupt_master_set(ui32Primask);

    return bSuccess;
}

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
