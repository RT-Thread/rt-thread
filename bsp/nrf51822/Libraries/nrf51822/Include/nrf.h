/*

Copyright (c) 2010 - 2021, Nordic Semiconductor ASA All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. Neither the name of Nordic Semiconductor ASA nor the names of its
   contributors may be used to endorse or promote products derived from this
   software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef NRF_H
#define NRF_H

/* MDK version */
#define MDK_MAJOR_VERSION   8 
#define MDK_MINOR_VERSION   38 
#define MDK_MICRO_VERSION   0 

   
/* Define coprocessor domains */
#if defined (NRF5340_XXAA_APPLICATION) || defined (NRF5340_XXAA_NETWORK)
    #ifndef NRF5340_XXAA
        #define NRF5340_XXAA
    #endif
#endif
#if defined (NRF5340_XXAA_APPLICATION)
    #ifndef NRF_APPLICATION
        #define NRF_APPLICATION
    #endif
#endif
#if defined (NRF5340_XXAA_NETWORK)
    #ifndef NRF_NETWORK
        #define NRF_NETWORK
    #endif
#endif

/* Apply compatibility macros for old nRF5340 macros */
#if defined(NRF5340_XXAA)
    #if defined (NRF_APPLICATION)
        #ifndef NRF5340_XXAA_APPLICATION
            #define NRF5340_XXAA_APPLICATION
        #endif
    #endif
    #if defined (NRF_NETWORK)
        #ifndef NRF5340_XXAA_NETWORK
            #define NRF5340_XXAA_NETWORK
        #endif
    #endif
#endif

/* Define NRF51_SERIES for common use in nRF51 series devices. Only if not previously defined. */
#if defined (NRF51) ||\
    defined (NRF51422_XXAA) ||\
    defined (NRF51422_XXAB) ||\
    defined (NRF51422_XXAC) ||\
    defined (NRF51801_XXAB) ||\
    defined (NRF51802_XXAA) ||\
    defined (NRF51822_XXAA) ||\
    defined (NRF51822_XXAB) ||\
    defined (NRF51822_XXAC) ||\
    defined (NRF51824_XXAA)
    #ifndef NRF51_SERIES
        #define NRF51_SERIES
    #endif
    #ifndef NRF51
        #define NRF51
    #endif
#endif

/* Redefine "old" too-generic name NRF52 to NRF52832_XXAA to keep backwards compatibility. */
#if defined (NRF52)
    #ifndef NRF52832_XXAA
        #define NRF52832_XXAA
    #endif
#endif

/* Define NRF52_SERIES for common use in nRF52 series devices. Only if not previously defined. */
#if defined (NRF52805_XXAA) || defined (NRF52810_XXAA) || defined (NRF52811_XXAA) || defined (NRF52820_XXAA) || defined (NRF52832_XXAA) || defined (NRF52832_XXAB) || defined (NRF52833_XXAA) || defined (NRF52840_XXAA)
    #ifndef NRF52_SERIES
        #define NRF52_SERIES
    #endif
#endif

/* Define NRF53_SERIES for common use in nRF53 series devices. */
#if defined (NRF5340_XXAA)
    #ifndef NRF53_SERIES
        #define NRF53_SERIES
    #endif
#endif

/* Define NRF91_SERIES for common use in nRF91 series devices. */
#if defined (NRF9160_XXAA)
    #ifndef NRF91_SERIES    
        #define NRF91_SERIES
    #endif
#endif

/* Device selection for device includes. */
#if defined (NRF51)
    #include "nrf51.h"
    #include "nrf51_bitfields.h"
    #include "nrf51_deprecated.h"

#elif defined (NRF52805_XXAA)
    #include "nrf52805.h"
    #include "nrf52805_bitfields.h"
    #include "nrf51_to_nrf52810.h"
    #include "nrf52_to_nrf52810.h"
    #include "nrf52810_to_nrf52811.h"
#elif defined (NRF52810_XXAA)
    #include "nrf52810.h"
    #include "nrf52810_bitfields.h"
    #include "nrf51_to_nrf52810.h"
    #include "nrf52_to_nrf52810.h"
    #include "nrf52810_name_change.h"
#elif defined (NRF52811_XXAA)
    #include "nrf52811.h"
    #include "nrf52811_bitfields.h"
    #include "nrf51_to_nrf52810.h"
    #include "nrf52_to_nrf52810.h"
    #include "nrf52810_to_nrf52811.h"
#elif defined (NRF52820_XXAA)
    #include "nrf52820.h"
    #include "nrf52820_bitfields.h"
    #include "nrf51_to_nrf52.h"
    #include "nrf52_to_nrf52833.h"
    #include "nrf52833_to_nrf52820.h"
#elif defined (NRF52832_XXAA) || defined (NRF52832_XXAB)
    #include "nrf52.h"
    #include "nrf52_bitfields.h"
    #include "nrf51_to_nrf52.h"
    #include "nrf52_name_change.h"
#elif defined (NRF52833_XXAA)
    #include "nrf52833.h"
    #include "nrf52833_bitfields.h"
    #include "nrf52_to_nrf52833.h"
    #include "nrf51_to_nrf52.h"
#elif defined (NRF52840_XXAA)
    #include "nrf52840.h"
    #include "nrf52840_bitfields.h"
    #include "nrf51_to_nrf52840.h"
    #include "nrf52_to_nrf52840.h"

#elif defined (NRF5340_XXAA)
    #if defined(NRF_APPLICATION)
        #include "nrf5340_application.h"
        #include "nrf5340_application_bitfields.h"
        #include "nrf5340_application_name_change.h"
    #elif defined (NRF_NETWORK)
        #include "nrf5340_network.h"
        #include "nrf5340_network_bitfields.h"
        #include "nrf5340_network_name_change.h"
    #endif

#elif defined (NRF9160_XXAA)
    #include "nrf9160.h"
    #include "nrf9160_bitfields.h"
    #include "nrf9160_name_change.h"

#else
    #error "Device must be defined. See nrf.h."
#endif /* NRF51, NRF52805_XXAA, NRF52810_XXAA, NRF52811_XXAA, NRF52820_XXAA, NRF52832_XXAA, NRF52832_XXAB, NRF52833_XXAA, NRF52840_XXAA, NRF5340_XXAA_APPLICATION, NRF5340_XXAA_NETWORK, NRF9160_XXAA */

#include "compiler_abstraction.h"

#endif /* NRF_H */

