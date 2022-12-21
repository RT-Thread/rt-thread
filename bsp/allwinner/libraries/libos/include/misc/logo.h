/*
 * =====================================================================================
 *
 *       Filename:  logo.h
 *
 *    Description:  For show bootup stage logo.
 *
 *        Version:  2.0
 *         Create:  2017-11-03 11:35:27
 *       Revision:  none
 *       Compiler:  gcc version 6.3.0 (crosstool-NG crosstool-ng-1.23.0)
 *
 *         Author:  caozilong@allwinnertech.com
 *   Organization:  BU1-PSW
 *  Last Modified:  2017-11-03 11:38:15
 *
 * =====================================================================================
 */

#ifndef LOGO_H
#define LOGO_H

/* ----------------------------------------------------------------------------*/
/** @brief  release_logo_buf <release bootlogo buffer, execute in shell.> */
/* ----------------------------------------------------------------------------*/
void release_logo_buf(void);

/* ----------------------------------------------------------------------------*/
/** @brief  show_logo <trigger show RGB logo> */
/* ----------------------------------------------------------------------------*/
void show_logo(void);

/* ----------------------------------------------------------------------------*/
/** @brief  close_logo <close logo display > */
/* ----------------------------------------------------------------------------*/
void close_logo(void);

/* ----------------------------------------------------------------------------*/
/** @brief  show_cvbs <trigger show cvbs input > */
/* ----------------------------------------------------------------------------*/
void show_cvbs(void);

#endif  /*LOGO_H*/
