/**************************************************************************/
/* FILE NAME: INTCISRVECTOR.c               COPYRIGHT (c) Freescale 2012  */
/*                                                All Rights Reserved     */
/* DESCRIPTION:                                                           */
/* This file contains a table of ISRs for INTC in software (SW) vector    */
/* mode. The table contains addresses for 1024 ISR vectors.               */
/* Table address stards at base of section ".isrvectbl"                   */
/* This file is an example Interrupt Service Routine call file with       */
/* ISR's be replaced by the user application code as needed.              */
/*                                                                        */
/*========================================================================*/
/* REV      AUTHOR        DATE        DESCRIPTION OF CHANGE               */
/* ---   -----------    ----------    ---------------------               */
/* 0.1   S. Mihalik      07/Jun/04    Initial version                     */
/* 0.2	  R. Moran       23/Feb/07    Modified for specific test ISRs	  */
/* 0.21	  I. Harris      11/Jan/10    Modified for specific test ISRs	  */
/* 0.23   I.Harris       01/Feb/11    Modified for GTM FPGA               */
/* 0.23   I.Harris       01/Feb/12    Modified for MPC5764M               */
/**************************************************************************/
#include "typedefs.h"
/*========================================================================*/
/*		PROTOTYPES						  */
/*========================================================================*/
void dummy 						  (void);

/*========================================================================*/
/*	GLOBAL VARIABLES						  */
/*========================================================================*/


extern void pit0_interrupt(void);
extern void pit1_interrupt(void);
extern void pit2_interrupt(void);
extern void pit3_interrupt(void);
extern void pit4_interrupt(void);
extern void pit5_interrupt(void);
extern void pit6_interrupt(void);
extern void pit7_interrupt(void);

const uint32_t __attribute__ ((section (".intc_vector_table"))) IntcIsrVectorTable[] = {

(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 00 - 04 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 05 - 09 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 10 - 14 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 15 - 19 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 20 - 24 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 25 - 29 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 30 - 34 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 35 - 39 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 40 - 44 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 45 - 49 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 50 - 54 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&pit0_interrupt, /* ISRs 55 - 59 */
(unsigned int)&pit1_interrupt, (unsigned int)&pit2_interrupt, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 60 - 64 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 65 - 69 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 70 - 74 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 75 - 79 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 80 - 84 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 85 - 89 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 90 - 94 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 95 - 99 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 100 - 104 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 105 - 109 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 110 - 114 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 115 - 119 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 120 - 124 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&pit3_interrupt, (unsigned int)&pit4_interrupt, (unsigned int)&pit5_interrupt, /* ISRs 125 - 129 */
(unsigned int)&pit6_interrupt, (unsigned int)&pit7_interrupt, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 130 - 134 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 135 - 139 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 140 - 144 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 145 - 149 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 150 - 154 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 155 - 159 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 160 - 164 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 165 - 169 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 170 - 174 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 175 - 179 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 180 - 184 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 185 - 189 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 190 - 194 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 195 - 199 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 200 - 204 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 205 - 209 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 210 - 214 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 215 - 219 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 220 - 224 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 225 - 229 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 230 - 234 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 235 - 239 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 240 - 244 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 245 - 249 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 250 - 254 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 255 - 259 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 260 - 264 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 265 - 269 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 270 - 274 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 275 - 279 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 280 - 284 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 285 - 289 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 290 - 294 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 295 - 299 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 300 - 304 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 305 - 309 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 310 - 314 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 315 - 319 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 320 - 324 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 325 - 329 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 330 - 334 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 335 - 339 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 340 - 344 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 345 - 349 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 350 - 354 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 355 - 359 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 360 - 364 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 365 - 369 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 370 - 374 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 375 - 379 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 380 - 384 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 385 - 389 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 390 - 394 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 395 - 399 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 400 - 404 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 405 - 409 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 410 - 414 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 415 - 419 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 420 - 424 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 425 - 429 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 430 - 434 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 435 - 439 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 440 - 444 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 445 - 449 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 450 - 454 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 455 - 459 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 460 - 464 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 465 - 469 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 470 - 474 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 475 - 479 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 480 - 484 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 485 - 489 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 490 - 494 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 495 - 499 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 500 - 504 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 505 - 509 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 510 - 514 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 515 - 519 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 520 - 524 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 525 - 529 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 530 - 534 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 535 - 539 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 540 - 544 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 545 - 549 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 550 - 554 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 555 - 559 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 560 - 564 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 565 - 569 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 570 - 574 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 575 - 579 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 580 - 584 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 585 - 589 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 590 - 594 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 595 - 599 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 600 - 604 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 605 - 609 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 610 - 614 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 615 - 619 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 620 - 624 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 625 - 629 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 630 - 634 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 635 - 639 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 640 - 644 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 645 - 649 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 650 - 654 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 655 - 659 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 660 - 664 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 665 - 669 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 670 - 674 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 675 - 679 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 680 - 684 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 685 - 689 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 690 - 694 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 695 - 699 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 700 - 704 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 705 - 709 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 710 - 714 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 715 - 719 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 720 - 724 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 725 - 729 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 730 - 734 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 735 - 739 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 740 - 744 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 745 - 749 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 750 - 754 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy,  /* ISRs 755 - 759 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 760 - 764 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 765 - 769 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 770 - 774 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 775 - 779 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 780 - 784 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 785 - 789 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 790 - 794 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 795 - 799 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 800 - 804 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 805 - 809 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 810 - 814 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 815 - 819 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 820 - 824 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 825 - 829 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 830 - 834 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 835 - 839 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 845 - 849 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 850 - 854 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 855 - 859 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 860 - 864 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 865 - 869 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 870 - 874 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 875 - 879 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 880 - 884 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 885 - 889 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 890 - 894 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 895 - 899 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 900 - 904 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 905 - 909 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 910 - 914 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 915 - 919 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 920 - 924 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 925 - 929 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 930 - 934 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 935 - 939 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 940 - 944 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 945 - 949 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 950 - 954 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 955 - 959 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 960 - 964 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 965 - 969 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 970 - 974 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 975 - 979 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 980 - 984 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 985 - 989 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 990 - 994 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 995 - 999 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 1000 - 1004 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 1005 - 1009 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 1010 - 1014 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 1015 - 1019 */
(unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, (unsigned int)&dummy, /* ISRs 1020 - 1024 */
};      

#ifdef __GNUC__
__attribute__ ((section(".text")))
#endif

/*========================================================================*/
/*			FUNCTIONS													  */
/*========================================================================*/
  
/**************************************************************************/
/* FUNCTION     : dummy													  */
/* PURPSE      : Dummy function which is entered if any non-used vector   */
/*							is called.									  */
/**************************************************************************/
void dummy (void) {
     
    while (1){};                 
	    
}  
