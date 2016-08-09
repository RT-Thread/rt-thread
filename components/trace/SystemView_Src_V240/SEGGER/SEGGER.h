/*********************************************************************
*               SEGGER MICROCONTROLLER GmbH & Co. KG                 *
*       Solutions for real time microcontroller applications         *
**********************************************************************
*                                                                    *
*       (c) 2015 - 2016  SEGGER Microcontroller GmbH & Co. KG        *
*                                                                    *
*       www.segger.com     Support: support@segger.com               *
*                                                                    *
**********************************************************************
*                                                                    *
*       SEGGER SystemView * Real-time application analysis           *
*                                                                    *
**********************************************************************
*                                                                    *
* All rights reserved.                                               *
*                                                                    *
* * This software may in its unmodified form be freely redistributed *
*   in source form.                                                  *
* * The source code may be modified, provided the source code        *
*   retains the above copyright notice, this list of conditions and  *
*   the following disclaimer.                                        *
* * Modified versions of this software in source or linkable form    *
*   may not be distributed without prior consent of SEGGER.          *
*                                                                    *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS "AS IS" AND     *
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,  *
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A        *
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL               *
* SEGGER Microcontroller BE LIABLE FOR ANY DIRECT, INDIRECT,         *
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES           *
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS    *
* OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS            *
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,       *
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING          *
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS *
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.       *
*                                                                    *
**********************************************************************
*                                                                    *
*       SystemView version: V2.40                                    *
*                                                                    *
**********************************************************************
----------------------------------------------------------------------
File    : SEGGER.h
Purpose : Global types etc & general purpose utility functions
---------------------------END-OF-HEADER------------------------------
*/

#ifndef SEGGER_H            // Guard against multiple inclusion
#define SEGGER_H

#include "Global.h"         // Type definitions: U8, U16, U32, I8, I16, I32

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*********************************************************************
*
*       Keywords/specifiers
*
**********************************************************************
*/

#ifndef INLINE
  #ifdef _WIN32
    //
    // Microsoft VC6 and newer.
    // Force inlining without cost checking.
    //
    #define INLINE  __forceinline
  #else
    #if (defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__) || defined(__RX) || defined(__ICCRX__))
      //
      // Other known compilers.
      //
      #define INLINE  inline
    #else
      //
      // Unknown compilers.
      //
      #define INLINE
    #endif
  #endif
#endif

/*********************************************************************
*
*       Function-like macros
*
**********************************************************************
*/

#define SEGGER_COUNTOF(a)          (sizeof((a))/sizeof((a)[0]))
#define SEGGER_MIN(a,b)            (((a) < (b)) ? (a) : (b))
#define SEGGER_MAX(a,b)            (((a) > (b)) ? (a) : (b))

/*********************************************************************
*
*       Types
*
**********************************************************************
*/

typedef struct {
  char *pBuffer;
  int   BufferSize;
  int   Cnt;
} SEGGER_BUFFER_DESC;

typedef struct {
  int  CacheLineSize;                                // 0: No Cache. Most Systems such as ARM9 use a 32 bytes cache line size.
  void (*pfDMB)       (void);                        // Optional DMB function for Data Memory Barrier to make sure all memory operations are completed.
  void (*pfClean)     (void *p, unsigned NumBytes);  // Optional clean function for cached memory.
  void (*pfInvalidate)(void *p, unsigned NumBytes);  // Optional invalidate function for cached memory.
} SEGGER_CACHE_CONFIG;

/*********************************************************************
*
*       Utility functions
*
**********************************************************************
*/

void SEGGER_ARM_memcpy   (void *pDest, const void *pSrc, int NumBytes);
void SEGGER_memcpy       (void *pDest, const void *pSrc, int NumBytes);
void SEGGER_memxor       (void *pDest, const void *pSrc, unsigned NumBytes);
void SEGGER_StoreChar    (SEGGER_BUFFER_DESC *p, char c);
void SEGGER_PrintUnsigned(SEGGER_BUFFER_DESC *pBufferDesc, U32 v, unsigned Base, int NumDigits);
void SEGGER_PrintInt     (SEGGER_BUFFER_DESC *pBufferDesc, I32 v, unsigned Base, unsigned NumDigits);
int  SEGGER_snprintf     (char *pBuffer, int BufferSize, const char *sFormat, ...);


#if defined(__cplusplus)
}                /* Make sure we have C-declarations in C++ programs */
#endif

#endif                      // Avoid multiple inclusion

/*************************** End of file ****************************/
