
/* this linker command file is to be included if user wants to use the DCSM feature on the device
 * DCSM  means Dual Zone Code Security Module.
 * This linker command file works as an addendum ot the already existing Flash/RAM linker command file
 * that the project has.
 * The sections in the *_ZoneSelectBlock.asm source file is linked as per the commands given in the file
 * NOTE - please note fill=0xFFFF, this helps if users include this file in the project by mistake and
 * doesn't provide the needed proper *_ZoneSelectBlock.asm sources .
 * Please refer to the Blinky DCSM example in the controlsuite examples for proper usage of this.
 *
 * Once users are confident that they want to program the passwords in OTP, the DSECT section type can be removed.
 *
*/

MEMORY
{
PAGE 0 :  /* Program Memory */

   /* Z1 OTP.  LinkPointers */
   DCSM_OTP_Z1_LINKPOINTER   : origin = 0x78000, length = 0x00000C
   /* Z1 OTP.  PSWDLOCK/RESERVED */
   DCSM_OTP_Z1_PSWDLOCK	    : origin = 0x78010, length = 0x000004
   /* Z1 OTP.  CRCLOCK/RESERVED */
   DCSM_OTP_Z1_CRCLOCK	    : origin = 0x78014, length = 0x000004
   /* Z1 OTP.  RESERVED/BOOTCTRL */
   DCSM_OTP_Z1_BOOTCTRL	    : origin = 0x7801C, length = 0x000004

   /* DCSM Z1 Zone Select Contents (!!Movable!!) */
   /* Z1 OTP.  Z1 password locations / Flash and RAM partitioning */
   DCSM_ZSEL_Z1_P0	        : origin = 0x78020, length = 0x000010

   /* Z2 OTP.  LinkPointers */
   DCSM_OTP_Z2_LINKPOINTER	: origin = 0x78200, length = 0x00000C
   /* Z2 OTP.  GPREG1/GPREG2 */
   DCSM_OTP_Z2_GPREG	        : origin = 0x7820C, length = 0x000004
   /* Z2 OTP.  PSWDLOCK/RESERVED */
   DCSM_OTP_Z2_PSWDLOCK	    : origin = 0x78210, length = 0x000004
   /* Z2 OTP.  CRCLOCK/RESERVED */
   DCSM_OTP_Z2_CRCLOCK	    : origin = 0x78214, length = 0x000004
   /* Z2 OTP.  GPREG3/BOOTCTRL */
   DCSM_OTP_Z2_BOOTCTRL	    : origin = 0x7821C, length = 0x000004

   /* DCSM Z1 Zone Select Contents (!!Movable!!) */
   /* Z2 OTP.  Z2 password locations / Flash and RAM partitioning  */
   DCSM_ZSEL_Z2_P0	        : origin = 0x78220, length = 0x000010

}

SECTIONS
{
   dcsm_otp_z1_linkpointer 	: > DCSM_OTP_Z1_LINKPOINTER		PAGE = 0, type = DSECT
   dcsm_otp_z1_pswdlock		: > DCSM_OTP_Z1_PSWDLOCK		PAGE = 0, type = DSECT
   dcsm_otp_z1_crclock		: > DCSM_OTP_Z1_CRCLOCK			PAGE = 0, type = DSECT
   dcsm_otp_z1_bootctrl		: > DCSM_OTP_Z1_BOOTCTRL		PAGE = 0, type = DSECT
   dcsm_zsel_z1				: > DCSM_ZSEL_Z1_P0				PAGE = 0, type = DSECT

   dcsm_otp_z2_linkpointer	: > DCSM_OTP_Z2_LINKPOINTER		PAGE = 0, type = DSECT
   dcsm_otp_z2_pswdlock		: > DCSM_OTP_Z2_PSWDLOCK		PAGE = 0, type = DSECT
   dcsm_otp_z2_crclock		: > DCSM_OTP_Z2_CRCLOCK			PAGE = 0, type = DSECT
   dcsm_otp_z2_bootctrl		: > DCSM_OTP_Z2_BOOTCTRL		PAGE = 0, type = DSECT
   dcsm_zsel_z2				: > DCSM_ZSEL_Z2_P0				PAGE = 0, type = DSECT
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
