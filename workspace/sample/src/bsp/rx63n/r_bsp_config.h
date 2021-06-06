/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No 
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all 
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM 
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES 
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS 
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of 
* this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer 
*
* Copyright (C) 2012 Renesas Electronics Corporation. All rights reserved.    
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_bsp_config_reference.c
* Device(s)    : RX63x
* Description  : The file r_bsp_config.h is used to configure your BSP. r_bsp_config.h should be included
*                somewhere in your package so that the r_bsp code has access to it. This file (r_bsp_config_reference.h)
*                is just a reference file that the user can use to make their own r_bsp_config.h file.
************************************************************************************************************************
* History : DD.MM.YYYY Version Description           
*         : 13.03.2012 1.00    First Release         
*         : 26.06.2012 1.10    Added MCU product part number section. Added endian options for user app and user boot.
*                              Added OFS register macros. Added option for ROM Code Protect. Added callback function
*                              options for exception interrupts.
*         : 16.07.2012 1.20    Fixed bug with exception callback function names. Added BCLK_OUTPUT and SDCLK_OUTPUT 
*                              macro options.
***********************************************************************************************************************/
#ifndef R_BSP_CONFIG_REF_HEADER_FILE
#define R_BSP_CONFIG_REF_HEADER_FILE

/***********************************************************************************************************************
Configuration Options
***********************************************************************************************************************/

/* Clock source select (CKSEL).
   0 = Low Speed On-Chip Oscillator  (LOCO)
   1 = High Speed On-Chip Oscillator (HOCO)
   2 = Main Clock Oscillator  
   3 = Sub-Clock Oscillator
   4 = PLL Circuit
*/ 
#define CLOCK_SOURCE            (4)

/* Clock configuration options.
   The input clock frequency is specified and then the system clocks are set by specifying the multipliers used. The
   multiplier settings are used to set the clock registers in resetprg.c. If a 12MHz clock is used and the 
   ICLK is 96MHz, PCLKA is 48MHz, PCLKB is 48MHz, FCLK is 48MHz, USB Clock is 48MHz, and BCLK is 12MHz then the 
   settings would be:

   XTAL_HZ = 12000000
   PLL_DIV = 1  (no division)
   PLL_MUL = 16 (12MHz x 16 = 192MHz)
   ICK_DIV =  2      : System Clock (ICLK)        = (((XTAL_HZ/PLL_DIV) * PLL_MUL) / ICK_DIV)  = 96MHz
   PCKA_DIV = 4      : Peripheral Clock A (PCLKA) = (((XTAL_HZ/PLL_DIV) * PLL_MUL) / PCKA_DIV) = 48MHz
   PCKB_DIV = 4      : Peripheral Clock B (PCLKB) = (((XTAL_HZ/PLL_DIV) * PLL_MUL) / PCKB_DIV) = 48MHz
   FCK_DIV =  4      : Flash IF Clock (FCLK)      = (((XTAL_HZ/PLL_DIV) * PLL_MUL) / FCK_DIV)  = 48MHz
   BCK_DIV =  8      : External Bus Clock (BCK)   = (((XTAL_HZ/PLL_DIV) * PLL_MUL) / BCK_DIV)  = 24MHz
   UCK_DIV =  4      : USB Clock (UCLK)           = (((XTAL_HZ/PLL_DIV) * PLL_MUL) / UCK_DIV)  = 48MHz
*/
/* XTAL - Input clock frequency in Hz */
#define XTAL_HZ                 (12000000)
/* PLL Input Frequency Divider Select (PLIDIV). 
   Available divisors = /1 (no division), /2, /4
*/
#define PLL_DIV                 (1)
/* PLL Frequency Multiplication Factor Select (STC). 
   Available multipliers = x8, x10, x12, x16, x20, x24, x25, x50
*/
#define PLL_MUL                 (16)
/* System Clock Divider (ICK).
   Available divisors = /1 (no division), /2, /4, /8, /16, /32, /64
*/
#define ICK_DIV                 (2)
/* Peripheral Module Clock A Divider (PCKA). 
   Available divisors = /1 (no division), /2, /4, /8, /16, /32, /64
*/
#define PCKA_DIV                (4)
/* Peripheral Module Clock B Divider (PCKB). 
   Available divisors = /1 (no division), /2, /4, /8, /16, /32, /64
*/
#define PCKB_DIV                (4)
/* External Bus Clock Divider (BCK). 
   Available divisors = /1 (no division), /2, /4, /8, /16, /32, /64
*/
#define BCK_DIV                 (8)
/* Flash IF Clock Divider (FCK). 
   Available divisors = /1 (no division), /2, /4, /8, /16, /32, /64
*/
#define FCK_DIV                 (4)
/* IEBUS Clock Divider Select. 
   Available divisors = /1 (no division), /2, /4, /6, /8, /16, /32, /64
*/
#define IEBCK_DIV               (8)
/* USB Clock Divider Select. 
   Available divisors = /3, /4
*/
#define UCK_DIV                 (4)

/* Configure BCLK output pin (only effective when external bus enabled)
   Values 0=no output, 1 = BCK frequency, 2= BCK/2 frequency */
#define BCLK_OUTPUT             (0)
/* Configure SDCLK output pin (only effective when external bus enabled)
   Values 0=no output, 1 = BCK frequency */  
#define SDCLK_OUTPUT            (0)


#endif /* R_BSP_CONFIG_REF_HEADER_FILE */



