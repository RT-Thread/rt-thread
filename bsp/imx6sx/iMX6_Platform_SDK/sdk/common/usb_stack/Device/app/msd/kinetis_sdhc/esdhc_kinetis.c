/**HEADER********************************************************************
*
* Copyright (c) 2009 Freescale Semiconductor;
* All Rights Reserved
*
***************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
**************************************************************************
*
* $FileName: esdhc.c$
* $Version : 3.7.5.1$
* $Date    : Mar-30-2011$
*
* Comments:
*
*   The file contains low level eSDHC driver functions.
*
*END************************************************************************/


#include <types.h>
#include "derivative.h" /* include peripheral declarations */
#include "esdhc_kinetis.h"

static const uint_32 ESDHC_COMMAND_XFERTYP[] =
{   /* CMD0 */
   SDHC_XFERTYP_CMDINX(ESDHC_CMD0) | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_NO),
   SDHC_XFERTYP_CMDINX(ESDHC_CMD1) | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_NO),
   SDHC_XFERTYP_CMDINX(ESDHC_CMD2) | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_136),
   SDHC_XFERTYP_CMDINX(ESDHC_CMD3) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
   SDHC_XFERTYP_CMDINX(ESDHC_CMD4) | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_NO),
   /* CMD5 */
   SDHC_XFERTYP_CMDINX(ESDHC_CMD5) | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
   SDHC_XFERTYP_CMDINX(ESDHC_CMD6) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
   SDHC_XFERTYP_CMDINX(ESDHC_CMD7) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48BUSY),
   SDHC_XFERTYP_CMDINX(ESDHC_CMD8) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
   SDHC_XFERTYP_CMDINX(ESDHC_CMD9) | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_136),
   /* CMD10 */
   SDHC_XFERTYP_CMDINX(ESDHC_CMD10) | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_136),
   SDHC_XFERTYP_CMDINX(ESDHC_CMD11) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
   SDHC_XFERTYP_CMDINX(ESDHC_CMD12) | SDHC_XFERTYP_CMDTYP(ESDHC_XFERTYP_CMDTYP_ABORT) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48BUSY),
   SDHC_XFERTYP_CMDINX(ESDHC_CMD13) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
   0,
   /* CMD15 */
   SDHC_XFERTYP_CMDINX(ESDHC_CMD15) | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_NO),
   SDHC_XFERTYP_CMDINX(ESDHC_CMD16) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
   SDHC_XFERTYP_CMDINX(ESDHC_CMD17) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
   SDHC_XFERTYP_CMDINX(ESDHC_CMD18) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
   0,
   /* CMD20 */
   SDHC_XFERTYP_CMDINX(ESDHC_CMD20) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
   0,
   SDHC_XFERTYP_CMDINX(ESDHC_ACMD22) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
   SDHC_XFERTYP_CMDINX(ESDHC_ACMD23) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
   SDHC_XFERTYP_CMDINX(ESDHC_CMD24) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
   /* CMD25 */
   SDHC_XFERTYP_CMDINX(ESDHC_CMD25) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
   SDHC_XFERTYP_CMDINX(ESDHC_CMD26) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
   SDHC_XFERTYP_CMDINX(ESDHC_CMD27) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
   SDHC_XFERTYP_CMDINX(ESDHC_CMD28) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48BUSY),
   SDHC_XFERTYP_CMDINX(ESDHC_CMD29) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48BUSY),
   /* CMD30 */
   SDHC_XFERTYP_CMDINX(ESDHC_CMD30) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
   0,
   SDHC_XFERTYP_CMDINX(ESDHC_CMD32) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
   SDHC_XFERTYP_CMDINX(ESDHC_CMD33) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
   SDHC_XFERTYP_CMDINX(ESDHC_CMD34) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
   /* CMD35 */
   SDHC_XFERTYP_CMDINX(ESDHC_CMD35) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
   SDHC_XFERTYP_CMDINX(ESDHC_CMD36) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
   SDHC_XFERTYP_CMDINX(ESDHC_CMD37) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
   SDHC_XFERTYP_CMDINX(ESDHC_CMD38) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48BUSY),
   SDHC_XFERTYP_CMDINX(ESDHC_CMD39) | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
   /* CMD40 */
   SDHC_XFERTYP_CMDINX(ESDHC_CMD40) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
   SDHC_XFERTYP_CMDINX(ESDHC_ACMD41) | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
   SDHC_XFERTYP_CMDINX(ESDHC_CMD42) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48BUSY),
   0,
   0,
   /* CMD45 */
   0,
   0,
   0,
   0,
   0,
   /* CMD50 */
   0,
   SDHC_XFERTYP_CMDINX(ESDHC_ACMD51) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
   SDHC_XFERTYP_CMDINX(ESDHC_CMD52) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
   SDHC_XFERTYP_CMDINX(ESDHC_CMD53) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
   0,
   /* CMD55 */
   SDHC_XFERTYP_CMDINX(ESDHC_CMD55) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
   SDHC_XFERTYP_CMDINX(ESDHC_CMD56) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48BUSY),
   0,
   0,
   0,
   /* CMD60 */
   SDHC_XFERTYP_CMDINX(ESDHC_CMD60) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48BUSY),
   SDHC_XFERTYP_CMDINX(ESDHC_CMD61) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48BUSY),
   0,
   0
};


const ESDHC_INIT_STRUCT _bsp_esdhc0_init = {
   0,                               /* ESDHC device number */
   4000000,                         /* ESDHC baudrate      */
#ifdef MCU_MK70F12
   120000000                        /* ESDHC clock source  */
#else
   96000000
#endif
};
extern const ESDHC_INFO_STRUCT_PTR   esdhc_info_ptr;
/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_esdhc_io_init
* Returned Value   : 0 or -1
* Comments         :
*    This function performs BSP-specific initialization related to ESDHC
*
*END*----------------------------------------------------------------------*/
static int_32 _bsp_esdhc_io_init
(
uint_8  dev_num,
uint_16 value
)
{
   SIM_MemMapPtr   sim  = SIM_BASE_PTR;
   PORT_MemMapPtr  pctl;

   switch (dev_num)
   {
   case 0:
      /* Configure GPIO for SDHC peripheral function */
      pctl = (PORT_MemMapPtr)PORTE_BASE_PTR;

      pctl->PCR[0] = value & (PORT_PCR_MUX(4) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_DSE_MASK);    /* ESDHC.D1  */
      pctl->PCR[1] = value & (PORT_PCR_MUX(4) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_DSE_MASK);    /* ESDHC.D0  */
      pctl->PCR[2] = value & (PORT_PCR_MUX(4) | PORT_PCR_DSE_MASK);                                          /* ESDHC.CLK */
      pctl->PCR[3] = value & (PORT_PCR_MUX(4) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_DSE_MASK);    /* ESDHC.CMD */
      pctl->PCR[4] = value & (PORT_PCR_MUX(4) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_DSE_MASK);    /* ESDHC.D3  */
      pctl->PCR[5] = value & (PORT_PCR_MUX(4) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_DSE_MASK);    /* ESDHC.D2  */

      /* Enable clock gate to SDHC module */
#ifdef MCU_MK70F12
      sim->SCGC3 |= SIM_SCGC3_ESDHC_MASK;
#else
      sim->SCGC3 |= SIM_SCGC3_SDHC_MASK;
#endif 
      break;

   default:
      /* Do nothing if bad dev_num was selected */
      return -1;
   }
   return 0;
}

/*FUNCTION****************************************************************
*
* Function Name    : _esdhc_set_baudrate
* Returned Value   : None
* Comments         :
*    Find and set closest divider values for given baudrate.
*
*END*********************************************************************/
static void _esdhc_set_baudrate
(
/* [IN/OUT] Module registry pointer */
SDHC_MemMapPtr esdhc_ptr,

/* [IN] Module input clock in Hz */
uint_32         clock,

/* [IN] Desired baudrate in Hz */
uint_32         baudrate
)
{
   uint_32 pres, div, min, minpres = 0x80, mindiv = 0x0F;
   int_32  val;

   /* Find closest setting */
   min = (uint_32)-1;
   for (pres = 2; pres <= 256; pres <<= 1)
   {
      for (div = 1; div <= 16; div++)
      {
         val = pres * div * baudrate - clock;
         if (val >= 0)
         {
            if (min > val)
            {
               min = val;
               minpres = pres;
               mindiv = div;
            }
         }
      }
   }

   /* Disable ESDHC clocks */
   esdhc_ptr->SYSCTL &= (~ SDHC_SYSCTL_SDCLKEN_MASK);

   /* Change dividers */
   div = esdhc_ptr->SYSCTL & (~ (SDHC_SYSCTL_DTOCV_MASK | SDHC_SYSCTL_SDCLKFS_MASK | SDHC_SYSCTL_DVS_MASK));
   esdhc_ptr->SYSCTL = div | (SDHC_SYSCTL_DTOCV(0x0E) | SDHC_SYSCTL_SDCLKFS(minpres >> 1) | SDHC_SYSCTL_DVS(mindiv - 1));

   /* Wait for stable clock */
   while (0 == (esdhc_ptr->PRSSTAT & SDHC_PRSSTAT_SDSTB_MASK))
   {
   };

   /* Enable ESDHC clocks */
   esdhc_ptr->SYSCTL |= SDHC_SYSCTL_SDCLKEN_MASK;
   esdhc_ptr->IRQSTAT |= SDHC_IRQSTAT_DTOE_MASK;
}

/*FUNCTION****************************************************************
*
* Function Name    : _esdhc_is_running
* Returned Value   : TRUE if running, FALSE otherwise
* Comments         :
*    Checks whether eSDHC module is currently in use.
*
*END*********************************************************************/
static boolean _esdhc_is_running
(
/* [IN] Module registry pointer */
SDHC_MemMapPtr esdhc_ptr
)
{
   return (0 != (esdhc_ptr->PRSSTAT & (SDHC_PRSSTAT_RTA_MASK | SDHC_PRSSTAT_WTA_MASK | SDHC_PRSSTAT_DLA_MASK | SDHC_PRSSTAT_CDIHB_MASK | SDHC_PRSSTAT_CIHB_MASK)));
}

/*FUNCTION****************************************************************
*
* Function Name    : _esdhc_status_wait
* Returned Value   : bits set for given mask
* Comments         :
*    Waits for ESDHC interrupt status register bits according to given mask.
*
*END*********************************************************************/
static uint_32 _esdhc_status_wait
(
/* [IN] Module registry pointer */
SDHC_MemMapPtr esdhc_ptr,

/* [IN] Mask of IRQSTAT bits to wait for */
uint_32         mask
)
{
   uint_32             result;
   do
   {
      result = esdhc_ptr->IRQSTAT & mask;
   }
   while (0 == result);
   return result;
}

/*FUNCTION****************************************************************
*
* Function Name    : _esdhc_init
* Returned Value   : error code
* Comments         :
*    ESDHC registers initialization and card detection.
*
*END*********************************************************************/
static int_32 _esdhc_init
(
/* [IN/OUT] Module registry pointer */
SDHC_MemMapPtr        esdhc_ptr,

/* [IN/OUT] Device runtime information */
ESDHC_INFO_STRUCT_PTR  esdhc_info_ptr,

/* [IN] Device initialization data */
ESDHC_INIT_STRUCT_CPTR esdhc_init_ptr
)
{
   esdhc_info_ptr->CARD = ESDHC_CARD_NONE;

   /* De-init GPIO - to prevent unwanted clocks on bus */
   if (_bsp_esdhc_io_init (esdhc_init_ptr->CHANNEL, 0) == -1)
   {
      return IO_ERROR_DEVICE_INVALID;
   }

   /* Reset ESDHC */
   esdhc_ptr->SYSCTL = SDHC_SYSCTL_RSTA_MASK | SDHC_SYSCTL_SDCLKFS(0x80);
   while (esdhc_ptr->SYSCTL & SDHC_SYSCTL_RSTA_MASK)
   { };

   /* Initial values */
   esdhc_ptr->VENDOR = 0;
   esdhc_ptr->BLKATTR = SDHC_BLKATTR_BLKCNT(1) | SDHC_BLKATTR_BLKSIZE(512);
   esdhc_ptr->PROCTL = SDHC_PROCTL_EMODE(ESDHC_PROCTL_EMODE_INVARIANT) | SDHC_PROCTL_D3CD_MASK;
   esdhc_ptr->WML = SDHC_WML_RDWML(1) | SDHC_WML_WRWML(1);

   /* Set the ESDHC initial baud rate divider and start */
   _esdhc_set_baudrate (esdhc_ptr, esdhc_init_ptr->CLOCK_SPEED, 4000000);

   /* Poll inhibit bits */
   while (esdhc_ptr->PRSSTAT & (SDHC_PRSSTAT_CIHB_MASK | SDHC_PRSSTAT_CDIHB_MASK))
   { };

   /* Init GPIO again */
   if (_bsp_esdhc_io_init (esdhc_init_ptr->CHANNEL, 0xFFFF) == -1)
   {
      return IO_ERROR_DEVICE_INVALID;
   }

   /* Enable requests */
   esdhc_ptr->IRQSTAT = 0xFFFF;
   esdhc_ptr->IRQSTATEN = SDHC_IRQSTATEN_DEBESEN_MASK | SDHC_IRQSTATEN_DCESEN_MASK | SDHC_IRQSTATEN_DTOESEN_MASK
   | SDHC_IRQSTATEN_CIESEN_MASK | SDHC_IRQSTATEN_CEBESEN_MASK | SDHC_IRQSTATEN_CCESEN_MASK | SDHC_IRQSTATEN_CTOESEN_MASK
   | SDHC_IRQSTATEN_BRRSEN_MASK | SDHC_IRQSTATEN_BWRSEN_MASK | SDHC_IRQSTATEN_CRMSEN_MASK
   | SDHC_IRQSTATEN_TCSEN_MASK | SDHC_IRQSTATEN_CCSEN_MASK;

   /* 80 initial clocks */
   esdhc_ptr->SYSCTL |= SDHC_SYSCTL_INITA_MASK;
   while (esdhc_ptr->SYSCTL & SDHC_SYSCTL_INITA_MASK)
   { };

   /* Check card */
   if (esdhc_ptr->PRSSTAT & SDHC_PRSSTAT_CINS_MASK)
   {
      esdhc_info_ptr->CARD = ESDHC_CARD_UNKNOWN;
   }
   esdhc_ptr->IRQSTAT |= SDHC_IRQSTAT_CRM_MASK;

   return ESDHC_OK;
}

/*FUNCTION****************************************************************
*
* Function Name    : _esdhc_send_command
* Returned Value   : 0 on success, 1 on error, -1 on timeout
* Comments         :
*    One ESDHC command transaction.
*
*END*********************************************************************/
static int_32 _esdhc_send_command
(
/* [IN/OUT] Module registry pointer */
SDHC_MemMapPtr          esdhc_ptr,

/* [IN/OUT] Command specification */
ESDHC_COMMAND_STRUCT_PTR command
)
{
   uint_32                      xfertyp;
   
   /* Check command */
   xfertyp = ESDHC_COMMAND_XFERTYP[command->COMMAND & 0x3F];
   if ((0 == xfertyp) && (0 != command->COMMAND))
   {
      return 1;
   }

   /* Card removal check preparation */
   esdhc_ptr->IRQSTAT |= SDHC_IRQSTAT_CRM_MASK;

   /* Wait for cmd line idle */
   while (esdhc_ptr->PRSSTAT & SDHC_PRSSTAT_CIHB_MASK)
   { };

   /* Setup command */
   esdhc_ptr->CMDARG = command->ARGUMENT;
   xfertyp &= (~ SDHC_XFERTYP_CMDTYP_MASK);
   xfertyp |= SDHC_XFERTYP_CMDTYP(command->TYPE);
   if (ESDHC_TYPE_RESUME == command->TYPE)
   {
      xfertyp |= SDHC_XFERTYP_DPSEL_MASK;
   }
   if (ESDHC_TYPE_SWITCH_BUSY == command->TYPE)
   {
      if ((xfertyp & SDHC_XFERTYP_RSPTYP_MASK) == SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48))
      {
         xfertyp &= (~ SDHC_XFERTYP_RSPTYP_MASK);
         xfertyp |= SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48BUSY);
      }
      else
      {
         xfertyp &= (~ SDHC_XFERTYP_RSPTYP_MASK);
         xfertyp |= SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48);
      }
   }
   esdhc_ptr->BLKATTR &= (~ SDHC_BLKATTR_BLKCNT_MASK);
   if (0 != command->BLOCKS)
   {
      if ((xfertyp & SDHC_XFERTYP_RSPTYP_MASK) != SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48BUSY))
      {
         xfertyp |= SDHC_XFERTYP_DPSEL_MASK;
      }
      if (command->READ)
      {
         xfertyp |= SDHC_XFERTYP_DTDSEL_MASK;
      }
      if (command->BLOCKS > 1)
      {
         xfertyp |= SDHC_XFERTYP_MSBSEL_MASK;
      }
      if ((uint_32)-1 != command->BLOCKS)
      {
         esdhc_ptr->BLKATTR |= SDHC_BLKATTR_BLKCNT(command->BLOCKS);
         xfertyp |= SDHC_XFERTYP_BCEN_MASK;
      }
   }

   /* Issue command */
   esdhc_ptr->DSADDR = 0;
   esdhc_ptr->XFERTYP = xfertyp;

   /* Wait for response */
   if (_esdhc_status_wait (esdhc_ptr, SDHC_IRQSTAT_CIE_MASK | SDHC_IRQSTAT_CEBE_MASK | SDHC_IRQSTAT_CCE_MASK | SDHC_IRQSTAT_CC_MASK) != SDHC_IRQSTAT_CC_MASK)
   {
      esdhc_ptr->IRQSTAT |= SDHC_IRQSTAT_CTOE_MASK | SDHC_IRQSTAT_CIE_MASK | SDHC_IRQSTAT_CEBE_MASK | SDHC_IRQSTAT_CCE_MASK | SDHC_IRQSTAT_CC_MASK;
      return 1;
   }

   /* Check card removal */
   if (esdhc_ptr->IRQSTAT & SDHC_IRQSTAT_CRM_MASK)
   {
      esdhc_ptr->IRQSTAT |= SDHC_IRQSTAT_CTOE_MASK | SDHC_IRQSTAT_CC_MASK;
      return 1;
   }

   /* Get response, if available */
   if (esdhc_ptr->IRQSTAT & SDHC_IRQSTAT_CTOE_MASK)
   {
      esdhc_ptr->IRQSTAT |= SDHC_IRQSTAT_CTOE_MASK | SDHC_IRQSTAT_CC_MASK;
      return -1;
   }
   if ((xfertyp & SDHC_XFERTYP_RSPTYP_MASK) != SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_NO))
   {
      command->RESPONSE[0] = esdhc_ptr->CMDRSP[0];
      if ((xfertyp & SDHC_XFERTYP_RSPTYP_MASK) == SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_136))
      {
         command->RESPONSE[1] = esdhc_ptr->CMDRSP[1];
         command->RESPONSE[2] = esdhc_ptr->CMDRSP[2];
         command->RESPONSE[3] = esdhc_ptr->CMDRSP[3];
      }
   }
   esdhc_ptr->IRQSTAT |= SDHC_IRQSTAT_CC_MASK;

   return 0;
}

/*FUNCTION****************************************************************
*
* Function Name    : _esdhc_ioctl
* Returned Value   : error code
* Comments         :
*    This function performs miscellaneous services for the ESDHC I/O device.
*
*END*********************************************************************/

extern const ESDHC_INIT_STRUCT _bsp_esdhc0_init;
int_32 _esdhc_ioctl
(
/* [IN] The command to perform */
uint_32             cmd,

/* [IN/OUT] Parameters for the command */
pointer             param_ptr
)
{
   ESDHC_INIT_STRUCT_CPTR  esdhc_init_ptr;
   SDHC_MemMapPtr          esdhc_ptr;
   ESDHC_COMMAND_STRUCT    command;
   boolean                 mem, io, mmc, ceata, mp, hc;
   int_32                  val;
   uint_32                 result = ESDHC_OK;
   uint_32_ptr             param32_ptr = param_ptr;



   /* Get register base */
   esdhc_ptr = (pointer)SDHC_BASE_PTR;
   esdhc_init_ptr = &_bsp_esdhc0_init;
   if (NULL == esdhc_ptr)
   {
      return IO_ERROR_DEVICE_INVALID;
   }

   switch (cmd)
   {
   case IO_IOCTL_ESDHC_INIT:

      result = _esdhc_init (esdhc_ptr, esdhc_info_ptr, esdhc_init_ptr);
      if (ESDHC_OK != result)
      {
         break;
      }

      mem = FALSE;
      io = FALSE;
      mmc = FALSE;
      ceata = FALSE;
      hc = FALSE;
      mp = FALSE;

      /* CMD0 - Go to idle - reset card */
      command.COMMAND = ESDHC_CMD0;
      command.TYPE = ESDHC_TYPE_NORMAL;
      command.ARGUMENT = 0;
      command.READ = FALSE;
      command.BLOCKS = 0;
      if (_esdhc_send_command (esdhc_ptr, &command))
      {
         result = ESDHC_ERROR_INIT_FAILED;
         break;
      }

      /* CMD8 - Send interface condition - check HC support */
      command.COMMAND = ESDHC_CMD8;
      command.TYPE = ESDHC_TYPE_NORMAL;
      command.ARGUMENT = 0x000001AA;
      command.READ = FALSE;
      command.BLOCKS = 0;
      val = _esdhc_send_command (esdhc_ptr, &command);
      if (val > 0)
      {
         result = ESDHC_ERROR_INIT_FAILED;
         break;
      }
      if (val == 0)
      {
         if (command.RESPONSE[0] != command.ARGUMENT)
         {
            result = ESDHC_ERROR_INIT_FAILED;
            break;
         }
         hc = TRUE;
      }

      /* CMD5 - Send operating conditions - test IO */
      command.COMMAND = ESDHC_CMD5;
      command.TYPE = ESDHC_TYPE_NORMAL;
      command.ARGUMENT = 0;
      command.READ = FALSE;
      command.BLOCKS = 0;
      val = _esdhc_send_command (esdhc_ptr, &command);
      if (val > 0)
      {
         result = ESDHC_ERROR_INIT_FAILED;
         break;
      }
      if (val == 0)
      {
         if (((command.RESPONSE[0] >> 28) & 0x07) && (command.RESPONSE[0] & 0x300000))
         {
            /* CMD5 - Send operating conditions - init IO */
            command.COMMAND = ESDHC_CMD5;
            command.TYPE = ESDHC_TYPE_NORMAL;
            command.ARGUMENT = 0x300000;
            command.READ = FALSE;
            command.BLOCKS = 0;
            val = 0;
            do
            {
               val++;
               if (_esdhc_send_command (esdhc_ptr, &command))
               {
                  result = ESDHC_ERROR_INIT_FAILED;
                  break;
               }
            } while ((0 == (command.RESPONSE[0] & 0x80000000)) && (val < BSP_ALARM_FREQUENCY));
            if (ESDHC_OK != result)
            {
               break;
            }
            if (command.RESPONSE[0] & 0x80000000)
            {
               io = TRUE;
            }
            if (command.RESPONSE[0] & 0x08000000)
            {
               mp = TRUE;
            }
         }
      }
      else
      {
         mp = TRUE;
      }

      if (mp)
      {
         /* CMD55 - Application specific command - check MMC */
         command.COMMAND = ESDHC_CMD55;
         command.TYPE = ESDHC_TYPE_NORMAL;
         command.ARGUMENT = 0;
         command.READ = FALSE;
         command.BLOCKS = 0;
         val = _esdhc_send_command (esdhc_ptr, &command);
         if (val > 0)
         {
            result = ESDHC_ERROR_INIT_FAILED;
            break;
         }
         if (val < 0)
         {
            /* MMC or CE-ATA */
            io = FALSE;
            mem = FALSE;
            hc = FALSE;

            /* CMD1 - Send operating conditions - check HC */
            command.COMMAND = ESDHC_CMD1;
            command.TYPE = ESDHC_TYPE_NORMAL;
            command.ARGUMENT = 0x40300000;
            command.READ = FALSE;
            command.BLOCKS = 0;
            if (_esdhc_send_command (esdhc_ptr, &command))
            {
               result = ESDHC_ERROR_INIT_FAILED;
               break;
            }
            if (0x20000000 == (command.RESPONSE[0] & 0x60000000))
            {
               hc = TRUE;
            }
            mmc = TRUE;

            /* CMD39 - Fast IO - check CE-ATA signature CE */
            command.COMMAND = ESDHC_CMD39;
            command.TYPE = ESDHC_TYPE_NORMAL;
            command.ARGUMENT = 0x0C00;
            command.READ = FALSE;
            command.BLOCKS = 0;
            if (_esdhc_send_command (esdhc_ptr, &command))
            {
               result = ESDHC_ERROR_INIT_FAILED;
               break;
            }
            if (0xCE == (command.RESPONSE[0] >> 8) & 0xFF)
            {
               /* CMD39 - Fast IO - check CE-ATA signature AA */
               command.COMMAND = ESDHC_CMD39;
               command.TYPE = ESDHC_TYPE_NORMAL;
               command.ARGUMENT = 0x0D00;
               command.READ = FALSE;
               command.BLOCKS = 0;
               if (_esdhc_send_command (esdhc_ptr, &command))
               {
                  result = ESDHC_ERROR_INIT_FAILED;
                  break;
               }
               if (0xAA == (command.RESPONSE[0] >> 8) & 0xFF)
               {
                  mmc = FALSE;
                  ceata = TRUE;
               }
            }
         }
         else
         {
            /* SD */
            /* ACMD41 - Send Operating Conditions */
            command.COMMAND = ESDHC_ACMD41;
            command.TYPE = ESDHC_TYPE_NORMAL;
            command.ARGUMENT = 0;
            command.READ = FALSE;
            command.BLOCKS = 0;
            if (_esdhc_send_command (esdhc_ptr, &command))
            {
               result = ESDHC_ERROR_INIT_FAILED;
               break;
            }
            if (command.RESPONSE[0] & 0x300000)
            {
               val = 0;
               do
               {
                  val++;

                  /* CMD55 + ACMD41 - Send OCR */
                  command.COMMAND = ESDHC_CMD55;
                  command.TYPE = ESDHC_TYPE_NORMAL;
                  command.ARGUMENT = 0;
                  command.READ = FALSE;
                  command.BLOCKS = 0;
                  if (_esdhc_send_command (esdhc_ptr, &command))
                  {
                     result = ESDHC_ERROR_INIT_FAILED;
                     break;
                  }

                  command.COMMAND = ESDHC_ACMD41;
                  command.TYPE = ESDHC_TYPE_NORMAL;
                  if (hc)
                  {
                     command.ARGUMENT = 0x40300000;
                  }
                  else
                  {
                     command.ARGUMENT = 0x00300000;
                  }
                  command.READ = FALSE;
                  command.BLOCKS = 0;
                  if (_esdhc_send_command (esdhc_ptr, &command))
                  {
                     result = ESDHC_ERROR_INIT_FAILED;
                     break;
                  }
               } while ((0 == (command.RESPONSE[0] & 0x80000000)) && (val < BSP_ALARM_FREQUENCY));
               if (ESDHC_OK != result)
               {
                  break;
               }
               if (val >= BSP_ALARM_FREQUENCY)
               {
                  hc = FALSE;
               }
               else
               {
                  mem = TRUE;
                  if (hc)
                  {
                     hc = FALSE;
                     if (command.RESPONSE[0] & 0x40000000)
                     {
                        hc = TRUE;
                     }
                  }
               }
            }
         }
      }
      if (mmc)
      {
         esdhc_info_ptr->CARD = ESDHC_CARD_MMC;
      }
      if (ceata)
      {
         esdhc_info_ptr->CARD = ESDHC_CARD_CEATA;
      }
      if (io)
      {
         esdhc_info_ptr->CARD = ESDHC_CARD_SDIO;
      }
      if (mem)
      {
         esdhc_info_ptr->CARD =  ESDHC_CARD_SD;
         if (hc)
         {
            esdhc_info_ptr->CARD = ESDHC_CARD_SDHC;
         }
      }
      if (io && mem)
      {
         esdhc_info_ptr->CARD = ESDHC_CARD_SDCOMBO;
         if (hc)
         {
            esdhc_info_ptr->CARD = ESDHC_CARD_SDHCCOMBO;
         }
      }

      /* De-Init GPIO */
      if (_bsp_esdhc_io_init (esdhc_init_ptr->CHANNEL, 0) == -1)
      {
         return IO_ERROR_DEVICE_INVALID;
      }

      /* Set the ESDHC default baud rate */
      _esdhc_set_baudrate (esdhc_ptr, esdhc_init_ptr->CLOCK_SPEED, esdhc_init_ptr->BAUD_RATE);

      /* Init GPIO */
      if (_bsp_esdhc_io_init (esdhc_init_ptr->CHANNEL, 0xFFFF) == -1)
      {
         return IO_ERROR_DEVICE_INVALID;
      }
      break;
   case IO_IOCTL_ESDHC_SEND_COMMAND:
      val = _esdhc_send_command (esdhc_ptr, (ESDHC_COMMAND_STRUCT_PTR)param32_ptr);
      if (val > 0)
      {
         result = ESDHC_ERROR_COMMAND_FAILED;
      }
      if (val < 0)
      {
         result = ESDHC_ERROR_COMMAND_TIMEOUT            ;
      }
      break;
   case IO_IOCTL_ESDHC_GET_BAUDRATE:
      if (NULL == param32_ptr)
      {
         result = SD_INVALID_PARAMETER;
      }
      else
      {
         /* Get actual baudrate */
         val = ((esdhc_ptr->SYSCTL & SDHC_SYSCTL_SDCLKFS_MASK) >> SDHC_SYSCTL_SDCLKFS_SHIFT) << 1;
         val *= ((esdhc_ptr->SYSCTL & SDHC_SYSCTL_DVS_MASK) >> SDHC_SYSCTL_DVS_SHIFT) + 1;
         *param32_ptr = (uint_32)((esdhc_init_ptr->CLOCK_SPEED) / val);
      }
      break;
   case IO_IOCTL_ESDHC_SET_BAUDRATE:
      if (NULL == param32_ptr)
      {
         result = SD_INVALID_PARAMETER;
      }
      else if (0 == (*param32_ptr))
      {
         result = SD_INVALID_PARAMETER;
      }
      else
      {
         if (! _esdhc_is_running (esdhc_ptr))
         {
            /* De-Init GPIO */
            if (_bsp_esdhc_io_init (esdhc_init_ptr->CHANNEL, 0) == -1)
            {
               result = IO_ERROR_DEVICE_INVALID;
               break;
            }

            /* Set closest baudrate */
            _esdhc_set_baudrate (esdhc_ptr, esdhc_init_ptr->CLOCK_SPEED, *param32_ptr);

            /* Init GPIO */
            if (_bsp_esdhc_io_init (esdhc_init_ptr->CHANNEL, 0xFFFF) == -1)
            {
               result = IO_ERROR_DEVICE_INVALID;
               break;
            }
         }
         else
         {
            result = IO_ERROR_DEVICE_BUSY;
         }
      }
      break;
   case IO_IOCTL_ESDHC_GET_BLOCK_SIZE:
      if (NULL == param32_ptr)
      {
         result = SD_INVALID_PARAMETER;
      }
      else
      {
         /* Get actual ESDHC block size */
         *param32_ptr = (esdhc_ptr->BLKATTR & SDHC_BLKATTR_BLKSIZE_MASK) >> SDHC_BLKATTR_BLKSIZE_SHIFT;
      }
      break;
   case IO_IOCTL_ESDHC_SET_BLOCK_SIZE:
      if (NULL == param32_ptr)
      {
         result = SD_INVALID_PARAMETER;
      }
      else
      {
         /* Set actual ESDHC block size */
         if (! _esdhc_is_running (esdhc_ptr))
         {
            if (*param32_ptr > 0x0FFF)
            {
               result = SD_INVALID_PARAMETER;
            }
            else
            {
               esdhc_ptr->BLKATTR &= (~ SDHC_BLKATTR_BLKSIZE_MASK);
               esdhc_ptr->BLKATTR |= SDHC_BLKATTR_BLKSIZE(*param32_ptr);
            }
         }
         else
         {
            result = IO_ERROR_DEVICE_BUSY;
         }
      }
      break;
   case IO_IOCTL_ESDHC_GET_BUS_WIDTH:
      if (NULL == param32_ptr)
      {
         result = SD_INVALID_PARAMETER;
      }
      else
      {
         /* Get actual ESDHC bus width */
         val = (esdhc_ptr->PROCTL & SDHC_PROCTL_DTW_MASK) >> SDHC_PROCTL_DTW_SHIFT;
         if (ESDHC_PROCTL_DTW_1BIT == val)
         {
            *param32_ptr = ESDHC_BUS_WIDTH_1BIT;
         }
         else if (ESDHC_PROCTL_DTW_4BIT == val)
         {
            *param32_ptr = ESDHC_BUS_WIDTH_4BIT;
         }
         else if (ESDHC_PROCTL_DTW_8BIT == val)
         {
            *param32_ptr = ESDHC_BUS_WIDTH_8BIT;
         }
         else
         {
            result = ESDHC_ERROR_INVALID_BUS_WIDTH;
         }
      }
      break;
   case IO_IOCTL_ESDHC_SET_BUS_WIDTH:
      if (NULL == param32_ptr)
      {
         result = SD_INVALID_PARAMETER;
      }
      else
      {
         /* Set actual ESDHC bus width */
         if (! _esdhc_is_running (esdhc_ptr))
         {
            if (ESDHC_BUS_WIDTH_1BIT == *param32_ptr)
            {
               esdhc_ptr->PROCTL &= (~ SDHC_PROCTL_DTW_MASK);
               esdhc_ptr->PROCTL |= SDHC_PROCTL_DTW(ESDHC_PROCTL_DTW_1BIT);
            }
            else if (ESDHC_BUS_WIDTH_4BIT == *param32_ptr)
            {
               esdhc_ptr->PROCTL &= (~ SDHC_PROCTL_DTW_MASK);
               esdhc_ptr->PROCTL |= SDHC_PROCTL_DTW(ESDHC_PROCTL_DTW_4BIT);
            }
            else if (ESDHC_BUS_WIDTH_8BIT == *param32_ptr)
            {
               esdhc_ptr->PROCTL &= (~ SDHC_PROCTL_DTW_MASK);
               esdhc_ptr->PROCTL |= SDHC_PROCTL_DTW(ESDHC_PROCTL_DTW_8BIT);
            }
            else
            {
               result = ESDHC_ERROR_INVALID_BUS_WIDTH;
            }
         }
         else
         {
            result = IO_ERROR_DEVICE_BUSY;
         }
      }
      break;
   case IO_IOCTL_ESDHC_GET_CARD:
      if (NULL == param32_ptr)
      {
         result = SD_INVALID_PARAMETER;
      }
      else
      {
         /* 80 clocks to update levels */
         esdhc_ptr->SYSCTL |= SDHC_SYSCTL_INITA_MASK;
         while (esdhc_ptr->SYSCTL & SDHC_SYSCTL_INITA_MASK)
         { };

         /* Update and return actual card status */
         if (esdhc_ptr->IRQSTAT & SDHC_IRQSTAT_CRM_MASK)
         {
            esdhc_ptr->IRQSTAT |= SDHC_IRQSTAT_CRM_MASK;
            esdhc_info_ptr->CARD = ESDHC_CARD_NONE;
         }
         if (esdhc_ptr->PRSSTAT & SDHC_PRSSTAT_CINS_MASK)
         {
            if (ESDHC_CARD_NONE == esdhc_info_ptr->CARD)
            {
               esdhc_info_ptr->CARD = ESDHC_CARD_UNKNOWN;
            }
         }
         else
         {
            esdhc_info_ptr->CARD = ESDHC_CARD_NONE;
         }
         *param32_ptr = esdhc_info_ptr->CARD;
      }
      break;

   case IO_IOCTL_FLUSH_OUTPUT:
      /* Wait for transfer complete */
      _esdhc_status_wait (esdhc_ptr, SDHC_IRQSTAT_TC_MASK);
      if (esdhc_ptr->IRQSTAT & (SDHC_IRQSTAT_DEBE_MASK | SDHC_IRQSTAT_DCE_MASK | SDHC_IRQSTAT_DTOE_MASK))
      {
         esdhc_ptr->IRQSTAT |= SDHC_IRQSTAT_DEBE_MASK | SDHC_IRQSTAT_DCE_MASK | SDHC_IRQSTAT_DTOE_MASK;
         result = ESDHC_ERROR_DATA_TRANSFER;
      }
      esdhc_ptr->IRQSTAT |= SDHC_IRQSTAT_TC_MASK | SDHC_IRQSTAT_BRR_MASK | SDHC_IRQSTAT_BWR_MASK;
      break;

   default:
      result = IO_ERROR_INVALID_IOCTL_CMD;
      break;
   }
   return result;
}

/*FUNCTION****************************************************************
*
* Function Name    : _esdhc_read
* Returned Value   : Returns the number of bytes received or IO_ERROR
* Comments         :
*   Reads the data into provided array.
*
*END*********************************************************************/
int_32 _esdhc_read
(
/* [OUT] Where the characters are to be stored */
uint_8_ptr               data_ptr,

/* [IN] The number of bytes to read */
int_32               n
)
{
   ESDHC_INIT_STRUCT_CPTR  esdhc_init_ptr;
   SDHC_MemMapPtr          esdhc_ptr;
   uint_32                 bytes, i, j;
   uint_32_ptr             ptr;


   /* Get register base */
   esdhc_ptr = (pointer)SDHC_BASE_PTR;

   /* Workaround for random bit polling failures - not suitable for IO cards */
   if ((esdhc_info_ptr->CARD == ESDHC_CARD_SD) || (esdhc_info_ptr->CARD == ESDHC_CARD_SDHC) || (esdhc_info_ptr->CARD == ESDHC_CARD_MMC) || (esdhc_info_ptr->CARD == ESDHC_CARD_CEATA))
   {
      while (esdhc_ptr->PRSSTAT & SDHC_PRSSTAT_DLA_MASK)
      { };
   }

   /* Read data in 4 byte counts */
   bytes = n;
   while (bytes)
   {
      i = bytes > 512 ? 512 : bytes;
      ptr = esdhc_info_ptr->BUFFER;
      for (j = (i + 3) >> 2; j != 0; j--)
      {
         if (esdhc_ptr->IRQSTAT & (SDHC_IRQSTAT_DEBE_MASK | SDHC_IRQSTAT_DCE_MASK | SDHC_IRQSTAT_DTOE_MASK))
         {
            esdhc_ptr->IRQSTAT |= SDHC_IRQSTAT_DEBE_MASK | SDHC_IRQSTAT_DCE_MASK | SDHC_IRQSTAT_DTOE_MASK | SDHC_IRQSTAT_BRR_MASK;
            return IO_ERROR;
         }

         while (0 == (esdhc_ptr->PRSSTAT & SDHC_PRSSTAT_BREN_MASK))
         { };

#ifdef LITTLE_ENDIAN
         *ptr++ = esdhc_ptr->DATPORT;
#else
         *ptr++ = _psp_swap4byte (esdhc_ptr->DATPORT);
#endif
      }
      memcpy (data_ptr, esdhc_info_ptr->BUFFER, i);
      data_ptr += i;
      bytes -= i;
   }

   return n;
}

/*FUNCTION****************************************************************
*
* Function Name    : _esdhc_write
* Returned Value   : return number of byte transmitted or IO_ERROR
* Comments         :
*   Writes the provided data buffer to the device.
*
*END*********************************************************************/
int_32 _esdhc_write
(
/* [OUT] Where the characters are to be taken from */
uint_8_ptr               data_ptr,

/* [IN] The number of bytes to read */
int_32               n
)
{
   ESDHC_INIT_STRUCT_CPTR  esdhc_init_ptr;
   SDHC_MemMapPtr          esdhc_ptr;
   uint_32                 bytes, i;
   uint_32_ptr             ptr;

   /* Get register base */
   esdhc_ptr = (pointer)SDHC_BASE_PTR;

   /* Write data in 4 byte counts */
   bytes = n;
   while (bytes)
   {
      i = bytes > 512 ? 512 : bytes;
      ptr = esdhc_info_ptr->BUFFER;
      memcpy (ptr, data_ptr, i);
      data_ptr += i;
      bytes -= i;
      for (i = (i + 3) >> 2; i != 0; i--)
      {
         if (esdhc_ptr->IRQSTAT & (SDHC_IRQSTAT_DEBE_MASK | SDHC_IRQSTAT_DCE_MASK | SDHC_IRQSTAT_DTOE_MASK))
         {
            esdhc_ptr->IRQSTAT |= SDHC_IRQSTAT_DEBE_MASK | SDHC_IRQSTAT_DCE_MASK | SDHC_IRQSTAT_DTOE_MASK | SDHC_IRQSTAT_BWR_MASK;
            return IO_ERROR;
         }
         while (0 == (esdhc_ptr->PRSSTAT & SDHC_PRSSTAT_BWEN_MASK))
         { };

#ifdef LITTLE_ENDIAN
         esdhc_ptr->DATPORT = *ptr++;
#else
         esdhc_ptr->DATPORT = _psp_swap4byte (*ptr++);
#endif

      }
   }

   return n;
}



/* EOF */
