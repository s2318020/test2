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
* File Name	   : resetprg.c
* Device(s)    : RX631/N
* Description  : Defines post-reset routines that are used to configure the MCU prior to the main program starting. 
*                This is were the program counter starts on power-up or reset.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 26.10.2011 1.00     First Release
*         : 13.03.2012 1.10     Stack sizes are now defined in r_bsp_config.h. Because of this the #include for 
*                               stacksct.h was removed. Settings for SCKCR are now set in r_bsp_config.h and used here
*                               to setup clocks based on user settings.
*         : 16.07.2012 1.20     Added ability to enable FPU Exceptions based on the EXCEP_FPU_ISR_CALLBACK macro and 
*                               the ability to enable NMI interrupts based on the NMI_ISR_CALLBACK. Also added code
*                               to enable BCLK and SDCLK output based on settings in r_bsp_config.h.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Defines machine level functions used in this file */
#include    <machine.h>
/* Defines MCU configuration functions used in this file */
#include    <_h_c_lib.h>
/* Defines standard variable types used in this file */
#include    <stdbool.h>
#include    <stdint.h>

/* Define the target platform */
#include    "iodefine.h"
#include    "r_bsp_config.h"

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
/* Main program function delcaration */
void operating_frequency_set(void);

/***********************************************************************************************************************
* Function name: operating_frequency_set
* Description  : Configures the clock settings for each of the device clocks
* Arguments    : none
* Return value : none
***********************************************************************************************************************/
void operating_frequency_set(void)
{
    /* Used for constructing value to write to SCKCR register. */
    uint32_t temp_clock = 0;
    
    /* 
    Clock Description              Frequency
    ----------------------------------------
    Input Clock Frequency............  12 MHz
    PLL frequency (x16).............. 192 MHz
    Internal Clock Frequency.........  96 MHz    
    Peripheral Clock Frequency.......  48 MHz
    USB Clock Frequency..............  48 MHz
    External Bus Clock Frequency.....  24 MHz */

    volatile unsigned int i;

    /* Protect off. */
    SYSTEM.PRCR.WORD = 0xA50B;			
    
    /* Uncomment if not using sub-clock */
    //SYSTEM.SOSCCR.BYTE = 0x01;          /* stop sub-clock */
    SYSTEM.SOSCCR.BYTE = 0x00;			/* Enable sub-clock for RTC */

    /* Wait 131,072 cycles * 12 MHz = 10.9 ms */
    SYSTEM.MOSCWTCR.BYTE = 0x0D;		

    /* PLL wait is 4,194,304 cycles (default) * 192 MHz (12 MHz * 16) = 20.1 ms*/
    SYSTEM.PLLWTCR.BYTE = 0x0F;			

    /* Set PLL Input Divisor. */
    SYSTEM.PLLCR.BIT.PLIDIV = PLL_DIV >> 1;

    /* Set PLL Multiplier. */
    SYSTEM.PLLCR.BIT.STC = PLL_MUL - 1;

    /* EXTAL ON */
    SYSTEM.MOSCCR.BYTE = 0x00;			

    /* PLL ON */
    SYSTEM.PLLCR2.BYTE = 0x00;			

    for(i = 0;i< 0x168;i++)             
    {
        /* Wait over 12ms */
        nop() ;
    }

    /* Figure out setting for FCK bits. */
#if   FCK_DIV == 1
    /* Do nothing since FCK bits should be 0. */
#elif FCK_DIV == 2
    temp_clock |= 0x10000000;
#elif FCK_DIV == 4
    temp_clock |= 0x20000000;
#elif FCK_DIV == 8
    temp_clock |= 0x30000000;
#elif FCK_DIV == 16
    temp_clock |= 0x40000000;
#elif FCK_DIV == 32
    temp_clock |= 0x50000000;
#elif FCK_DIV == 64
    temp_clock |= 0x60000000;
#else
    #error "Error! Invalid setting for FCK_DIV in r_bsp_config.h"
#endif

    /* Figure out setting for ICK bits. */
#if   ICK_DIV == 1
    /* Do nothing since ICK bits should be 0. */
#elif ICK_DIV == 2
    temp_clock |= 0x01000000;
#elif ICK_DIV == 4
    temp_clock |= 0x02000000;
#elif ICK_DIV == 8
    temp_clock |= 0x03000000;
#elif ICK_DIV == 16
    temp_clock |= 0x04000000;
#elif ICK_DIV == 32
    temp_clock |= 0x05000000;
#elif ICK_DIV == 64
    temp_clock |= 0x06000000;
#else
    #error "Error! Invalid setting for ICK_DIV in r_bsp_config.h"
#endif

    /* Figure out setting for BCK bits. */
#if   BCK_DIV == 1
    /* Do nothing since BCK bits should be 0. */
#elif BCK_DIV == 2
    temp_clock |= 0x00010000;
#elif BCK_DIV == 4
    temp_clock |= 0x00020000;
#elif BCK_DIV == 8
    temp_clock |= 0x00030000;
#elif BCK_DIV == 16
    temp_clock |= 0x00040000;
#elif BCK_DIV == 32
    temp_clock |= 0x00050000;
#elif BCK_DIV == 64
    temp_clock |= 0x00060000;
#else
    #error "Error! Invalid setting for BCK_DIV in r_bsp_config.h"
#endif

    /* Configure PSTOP1 bit for BCLK output. */
#if BCLK_OUTPUT == 0    
    /* Set PSTOP1 bit */
    temp_clock |= 0x00800000;
#elif BCLK_OUTPUT == 1
    /* Clear PSTOP1 bit */
    temp_clock &= ~0x00800000;
#elif BCLK_OUTPUT == 2
    /* Clear PSTOP1 bit */
    temp_clock &= ~0x00800000;
    /* Set BCLK divider bit */
    SYSTEM.BCKCR.BIT.BCLKDIV = 1;
#else
    #error "Error! Invalid setting for BCLK_OUTPUT in r_bsp_config.h"
#endif

    /* Configure PSTOP0 bit for SDCLK output. */
#if SDCLK_OUTPUT == 0    
    /* Set PSTOP0 bit */
    temp_clock |= 0x00400000;
#elif SDCLK_OUTPUT == 1
    /* Clear PSTOP0 bit */
    temp_clock &= ~0x00400000;
#else
    #error "Error! Invalid setting for SDCLK_OUTPUT in r_bsp_config.h"
#endif

    /* Figure out setting for PCKA bits. */
#if   PCKA_DIV == 1
    /* Do nothing since PCKA bits should be 0. */
#elif PCKA_DIV == 2
    temp_clock |= 0x00001000;
#elif PCKA_DIV == 4
    temp_clock |= 0x00002000;
#elif PCKA_DIV == 8
    temp_clock |= 0x00003000;
#elif PCKA_DIV == 16
    temp_clock |= 0x00004000;
#elif PCKA_DIV == 32
    temp_clock |= 0x00005000;
#elif PCKA_DIV == 64
    temp_clock |= 0x00006000;
#else
    #error "Error! Invalid setting for PCKA_DIV in r_bsp_config.h"
#endif

    /* Figure out setting for PCKB bits. */
#if   PCKB_DIV == 1
    /* Do nothing since PCKB bits should be 0. */
#elif PCKB_DIV == 2
    temp_clock |= 0x00000100;
#elif PCKB_DIV == 4
    temp_clock |= 0x00000200;
#elif PCKB_DIV == 8
    temp_clock |= 0x00000300;
#elif PCKB_DIV == 16
    temp_clock |= 0x00000400;
#elif PCKB_DIV == 32
    temp_clock |= 0x00000500;
#elif PCKB_DIV == 64
    temp_clock |= 0x00000600;
#else
    #error "Error! Invalid setting for PCKB_DIV in r_bsp_config.h"
#endif

    /* Bottom byte of SCKCR register must be set to 0x11 */
    temp_clock |= 0x00000011;

    /* Set SCKCR register. */
    SYSTEM.SCKCR.LONG = temp_clock;
    
    /* Re-init temp_clock to use to set SCKCR2. */
    temp_clock = 0;

    /* Figure out setting for IEBCK bits. */
#if   IEBCK_DIV == 2
    temp_clock |= 0x00000001;
#elif IEBCK_DIV == 4
    temp_clock |= 0x00000002;
#elif IEBCK_DIV == 6
    temp_clock |= 0x0000000C;
#elif IEBCK_DIV == 8
    temp_clock |= 0x00000003;
#elif IEBCK_DIV == 16
    temp_clock |= 0x00000004;
#elif IEBCK_DIV == 32
    temp_clock |= 0x00000005;
#elif IEBCK_DIV == 64
    temp_clock |= 0x00000006;
#else
    #error "Error! Invalid setting for IEBCK_DIV in r_bsp_config.h"
#endif

    /* Figure out setting for UCK bits. */
#if   UCK_DIV == 3
    temp_clock |= 0x00000020;
#elif UCK_DIV == 4
    temp_clock |= 0x00000030;
#else
    #error "Error! Invalid setting for UCK_DIV in r_bsp_config.h"
#endif

    /* Set SCKCR2 register. */
    SYSTEM.SCKCR2.WORD = (uint16_t)temp_clock;

    /* Choose clock source. Default for r_bsp_config.h is PLL. */
    SYSTEM.SCKCR3.WORD = ((uint16_t)CLOCK_SOURCE) << 8;

    /* Protect on. */
    SYSTEM.PRCR.WORD = 0xA500;			
}

