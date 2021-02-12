/* *************************************************
 *
 * This module contains the function `__low_level_init', a function
 * that is called before the `main' function of the program.  Normally
 * low-level initializations - such as setting the prefered interrupt
 * level or setting the watchdog - can be performed here.
 *
 * Note that this function is called before the data segments are
 * initialized, this means that this function cannot rely on the
 * values of global or static variables.
 *
 * When this function returns zero, the startup code will inhibit the
 * initialization of the data segments. The result is faster startup,
 * the drawback is that neither global nor static data will be
 * initialized.
 *
 * Copyright 1999-2004 IAR Systems. All rights reserved.
 *
 * $Revision: 36818 $
 *
 ************************************************* */

#ifdef __cplusplus
extern "C" {
#endif

extern int PreInit(void);

#pragma language=extended

__interwork int __low_level_init(void);

__interwork int __low_level_init(void)
{
    /*====================================*/
    /*  Initialize hardware.              */
    /*  AND                               */
    /* Choose if segment initialization   */
    /* should be done or not.             */
    /* Return: 0 to omit seg_init         */
    /*         1 to run seg_init          */
    /*====================================*/
    return !PreInit(); // See system_max32660.c
}

#pragma language=default

#ifdef __cplusplus
}
#endif
