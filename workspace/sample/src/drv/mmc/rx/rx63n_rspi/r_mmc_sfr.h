/*""FILE COMMENT""*******************************************************************
* File Name		: r_mmc_sfr.h
* Version      	: 1.23C
* Device(s)    	: RX63N
* Tool-Chain 	: RX Standard Toolchain (V.1.2.1.0)
* H/W Platform 	: -
* Description	: MMC driver SFR RX63N-RSPI common definitions
*************************************************************************************
* History	: DD.MM.YYYY Version Description
*			: 27.12.2012 Ver1.23C
*""FILE COMMENT END""***************************************************************/
#ifndef __MMC_SFR_H__
#define __MMC_SFR_H__
#include "r_mmc_user_config.h"

/************************************************************************************************/
/*	Definitions																					*/
/************************************************************************************************/
/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
/*                              Do not change the following data.                               */
/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
#define _MMC_DRIVER_CPU_MODULE_NAME_	"RX63N_RSPI"

#define CAT_2(a,b) a##b
#define CAT(a,b) CAT_2(a,b)

#define RSPIn	CAT(RSPI, MMC_RSPI_CHANNEL)
#define _RSPIn	CAT(_RSPI, MMC_RSPI_CHANNEL)
#define MMC_RX	CAT(_RSPIn, CAT(_SPRI , MMC_RSPI_CHANNEL))
#define MMC_TX	CAT(_RSPIn, CAT(_SPTI , MMC_RSPI_CHANNEL))

#define	__IR_BYTE( x )		ICU.IR[ IR ## x ].BYTE
#define	 _IR_BYTE( x )		__IR_BYTE( x )
#define	__IPR_BYTE( x )		ICU.IPR[ IPR ## x ].BYTE
#define	 _IPR_BYTE( x )		__IPR_BYTE( x )
#define	__DTCE_BYTE( x )	ICU.DTCER[ DTCE ## x ].BYTE
#define	 _DTCE_BYTE( x )	__DTCE_BYTE( x )
#define	__PDR( x,y )		PORT ## x.PDR.BIT.B ## y
#define	 _PDR( x,y )		__PDR( x , y )
#define	__PIDR( x,y )		PORT ## x.PIDR.BIT.B ## y
#define	 _PIDR( x,y )		__PIDR( x , y )
#define	__PODR( x,y )		PORT ## x.PODR.BIT.B ## y
#define	 _PODR( x,y )		__PODR( x , y )
#define	__PMR( x,y )		PORT ## x.PMR.BIT.B ## y
#define	 _PMR( x,y )		__PMR( x , y )
#define	__DSCR( x,y )		PORT ## x.DSCR.BIT.B ## y
#define	 _DSCR( x,y )		__DSCR( x , y )
#define	__PFS( x,y )		MPC.P ## x ## y ## PFS.BYTE
#define	 _PFS( x,y )		__PFS( x , y )

/*----------------------------------------------------------------------------------------------*/
/*	 Define the control port.			 														*/
/*----------------------------------------------------------------------------------------------*/
#define MMC_PFSWE			MPC.PWPR.BIT.PFSWE
#define MMC_B0WI			MPC.PWPR.BIT.B0WI

#if (MMC_RSPI_CHANNEL == 0)

#if (MMC_RSPI_RXD_PIN == 'A')
#define MMC_DATAI_PORTNO	1		/* MMC DataIn Port No. */
#define MMC_DATAI_BITNO		7		/* MMC DataIn Bit No.  */
#define	MMC_PFS_DATAI_INIT	(uint8_t)0x0D
#elif (MMC_RSPI_RXD_PIN == 'B')
#define MMC_DATAI_PORTNO	A		/* MMC DataIn Port No. */
#define MMC_DATAI_BITNO		7		/* MMC DataIn Bit No.  */
#define	MMC_PFS_DATAI_INIT	(uint8_t)0x0D
#elif (MMC_RSPI_RXD_PIN == 'C')
#define MMC_DATAI_PORTNO	C		/* MMC DataIn Port No. */
#define MMC_DATAI_BITNO		7		/* MMC DataIn Bit No.  */
#define	MMC_PFS_DATAI_INIT	(uint8_t)0x0D
#endif	/* MMC_RSPI_RXD_PIN */

#if (MMC_RSPI_SCK_PIN == 'A')
#define MMC_CLK_PORTNO		A		/* MMC CLK Port No.  */
#define MMC_CLK_BITNO		5		/* MMC CLK Bit  No.  */
#define	MMC_PFS_CLK_INIT	(uint8_t)0x0D
#define	MMC_DSCR_CLK_SET	1
#elif (MMC_RSPI_SCK_PIN == 'B')
#define MMC_CLK_PORTNO		B		/* MMC CLK Port No.  */
#define MMC_CLK_BITNO		0		/* MMC CLK Bit  No.  */
#define	MMC_PFS_CLK_INIT	(uint8_t)0x0D
#define	MMC_DSCR_CLK_SET	1
#elif (MMC_RSPI_SCK_PIN == 'C')
#define MMC_CLK_PORTNO		C		/* MMC CLK Port No.  */
#define MMC_CLK_BITNO		5		/* MMC CLK Bit  No.  */
#define	MMC_PFS_CLK_INIT	(uint8_t)0x0D
#define	MMC_DSCR_CLK_SET	1
#endif	/* MMC_RSPI_SCK_PIN */

#if (MMC_RSPI_TXD_PIN == 'A')
#define MMC_DATAO_PORTNO	1		/* MMC DataOut Port No. */
#define MMC_DATAO_BITNO		6		/* MMC DataOut Bit No.  */
#define	MMC_PFS_DATAO_INIT	(uint8_t)0x0D
#define	MMC_DSCR_DATAO_SET	0
#elif (MMC_RSPI_TXD_PIN == 'B')
#define MMC_DATAO_PORTNO	A		/* MMC DataOut Port No. */
#define MMC_DATAO_BITNO		6		/* MMC DataOut Bit No.  */
#define	MMC_PFS_DATAO_INIT	(uint8_t)0x0D
#define	MMC_DSCR_DATAO_SET	1
#elif (MMC_RSPI_TXD_PIN == 'C')
#define MMC_DATAO_PORTNO	C		/* MMC DataOut Port No. */
#define MMC_DATAO_BITNO		6		/* MMC DataOut Bit No.  */
#define	MMC_PFS_DATAO_INIT	(uint8_t)0x0D
#define	MMC_DSCR_DATAO_SET	1
#endif	/* MMC_RSPI_TXD_PIN */


#elif (MMC_RSPI_CHANNEL == 1)

#if (MMC_RSPI_RXD_PIN == 'A')
#define MMC_DATAI_PORTNO	3		/* MMC DataIn Port No. */
#define MMC_DATAI_BITNO		0		/* MMC DataIn Bit No.  */
#define	MMC_PFS_DATAI_INIT	(uint8_t)0x0D
#elif (MMC_RSPI_RXD_PIN == 'B')
#define MMC_DATAI_PORTNO	E		/* MMC DataIn Port No. */
#define MMC_DATAI_BITNO		3		/* MMC DataIn Bit No.  */
#define	MMC_PFS_DATAI_INIT	(uint8_t)0x0D
#elif (MMC_RSPI_RXD_PIN == 'C')
#define MMC_DATAI_PORTNO	E		/* MMC DataIn Port No. */
#define MMC_DATAI_BITNO		7		/* MMC DataIn Bit No.  */
#define	MMC_PFS_DATAI_INIT	(uint8_t)0x0D
#endif	/* MMC_RSPI_RXD_PIN */

#if (MMC_RSPI_SCK_PIN == 'A')
#define MMC_CLK_PORTNO		2		/* MMC CLK Port No.  */
#define MMC_CLK_BITNO		7		/* MMC CLK Bit  No.  */
#define	MMC_PFS_CLK_INIT	(uint8_t)0x0D
#define	MMC_DSCR_CLK_SET	1
#elif (MMC_RSPI_SCK_PIN == 'B')
#define MMC_CLK_PORTNO		E		/* MMC CLK Port No.  */
#define MMC_CLK_BITNO		1		/* MMC CLK Bit  No.  */
#define	MMC_PFS_CLK_INIT	(uint8_t)0x0E
#define	MMC_DSCR_CLK_SET	1
#elif (MMC_RSPI_SCK_PIN == 'C')
#define MMC_CLK_PORTNO		E		/* MMC CLK Port No.  */
#define MMC_CLK_BITNO		5		/* MMC CLK Bit  No.  */
#define	MMC_PFS_CLK_INIT	(uint8_t)0x0D
#define	MMC_DSCR_CLK_SET	1
#endif	/* MMC_RSPI_SCK_PIN */

#if (MMC_RSPI_TXD_PIN == 'A')
#define MMC_DATAO_PORTNO	2		/* MMC DataOut Port No. */
#define MMC_DATAO_BITNO		6		/* MMC DataOut Bit No.  */
#define	MMC_PFS_DATAO_INIT	(uint8_t)0x0D
#define	MMC_DSCR_DATAO_SET	0
#elif (MMC_RSPI_TXD_PIN == 'B')
#define MMC_DATAO_PORTNO	E		/* MMC DataOut Port No. */
#define MMC_DATAO_BITNO		2		/* MMC DataOut Bit No.  */
#define	MMC_PFS_DATAO_INIT	(uint8_t)0x0E
#define	MMC_DSCR_DATAO_SET	1
#elif (MMC_RSPI_TXD_PIN == 'C')
#define MMC_DATAO_PORTNO	E		/* MMC DataOut Port No. */
#define MMC_DATAO_BITNO		6		/* MMC DataOut Bit No.  */
#define	MMC_PFS_DATAO_INIT	(uint8_t)0x0D
#define	MMC_DSCR_DATAO_SET	1
#endif	/* MMC_RSPI_TXD_PIN */

#elif (MMC_RSPI_CHANNEL == 2)

#define MMC_DATAI_PORTNO	D		/* MMC DataIn Port No. */
#define MMC_DATAI_BITNO		2		/* MMC DataIn Bit No.  */
#define	MMC_PFS_DATAI_INIT	(uint8_t)0x0D
#define MMC_CLK_PORTNO		D		/* MMC CLK Port No.  */
#define MMC_CLK_BITNO		3		/* MMC CLK Bit  No.  */
#define	MMC_PFS_CLK_INIT	(uint8_t)0x0D
#define	MMC_DSCR_CLK_SET	1
#define MMC_DATAO_PORTNO	D		/* MMC DataOut Port No. */
#define MMC_DATAO_BITNO		1		/* MMC DataOut Bit No.  */
#define	MMC_PFS_DATAO_INIT	(uint8_t)0x0D
#define	MMC_DSCR_CLK_SET	1


#endif	/* MMC_RSPI_CHANNEL */

#define MMC_PDR_DATAI		 _PDR( MMC_DATAI_PORTNO , MMC_DATAI_BITNO )		/* MMC DataIn							*/
#define MMC_PIDR_DATAI		_PIDR( MMC_DATAI_PORTNO , MMC_DATAI_BITNO )		/* MMC DataIn							*/
#define MMC_PMR_DATAI		 _PMR( MMC_DATAI_PORTNO , MMC_DATAI_BITNO )		/* MMC DataIn							*/
#define MMC_PFS_DATAI		 _PFS( MMC_DATAI_PORTNO , MMC_DATAI_BITNO )		/* MMC DataIn							*/
#define MMC_PDR_CLK			 _PDR( MMC_CLK_PORTNO , MMC_CLK_BITNO )			/* MMC CLK								*/
#define MMC_PODR_CLK		_PODR( MMC_CLK_PORTNO , MMC_CLK_BITNO )			/* MMC CLK								*/
#define MMC_PMR_CLK			 _PMR( MMC_CLK_PORTNO , MMC_CLK_BITNO )			/* MMC CLK								*/
#define MMC_DSCR_CLK		_DSCR( MMC_CLK_PORTNO , MMC_CLK_BITNO )			/* MMC CLK								*/
#define MMC_PFS_CLK			 _PFS( MMC_CLK_PORTNO , MMC_CLK_BITNO )			/* MMC CLK								*/
#define MMC_PDR_DATAO		 _PDR( MMC_DATAO_PORTNO , MMC_DATAO_BITNO )		/* MMC DataOut							*/
#define MMC_PODR_DATAO		_PODR( MMC_DATAO_PORTNO , MMC_DATAO_BITNO )		/* MMC DataOut							*/
#define MMC_PMR_DATAO		 _PMR( MMC_DATAO_PORTNO , MMC_DATAO_BITNO )		/* MMC DataOut							*/
#define MMC_DSCR_DATAO		_DSCR( MMC_DATAO_PORTNO , MMC_DATAO_BITNO )		/* MMC DataOut							*/
#define MMC_PFS_DATAO		 _PFS( MMC_DATAO_PORTNO , MMC_DATAO_BITNO )		/* MMC DataOut							*/

#define MMC_PDR_CS0			 _PDR(MMC_CS0_PORTNO , MMC_CS0_BITNO )			/* MMC CS0		(Negative-true logic)	*/
#define MMC_PODR_CS0		_PODR(MMC_CS0_PORTNO , MMC_CS0_BITNO )			/* MMC CS0		(Negative-true logic)	*/
#define MMC_PMR_CS0			 _PMR(MMC_CS0_PORTNO , MMC_CS0_BITNO )			/* MMC CS0		(Negative-true logic)	*/
#define MMC_PDR_DETECT0		 _PDR(MMC_DETECT0_PORTNO , MMC_DETECT0_BITNO )	/* MMC DETECT0	(Negative-true logic)	*/
#define MMC_PIDR_DETECT0	_PIDR(MMC_DETECT0_PORTNO , MMC_DETECT0_BITNO )	/* MMC DETECT0	(Negative-true logic)	*/
#define MMC_PMR_DETECT0		 _PMR(MMC_DETECT0_PORTNO , MMC_DETECT0_BITNO )	/* MMC DETECT0	(Negative-true logic)	*/

#if (MMC_SLOT_NUM > 1)
#define MMC_PDR_CS1			 _PDR(MMC_CS1_PORTNO , MMC_CS1_BITNO )			/* MMC CS1		(Negative-true logic)	*/
#define MMC_PODR_CS1		_PODR(MMC_CS1_PORTNO , MMC_CS1_BITNO )			/* MMC CS1		(Negative-true logic)	*/
#define MMC_PMR_CS1			 _PMR(MMC_CS1_PORTNO , MMC_CS1_BITNO )			/* MMC CS1		(Negative-true logic)	*/
#define MMC_PDR_DETECT1		 _PDR(MMC_DETECT1_PORTNO , MMC_DETECT1_BITNO )	/* MMC DETECT1	(Negative-true logic)	*/
#define MMC_PIDR_DETECT1	_PIDR(MMC_DETECT1_PORTNO , MMC_DETECT1_BITNO )	/* MMC DETECT1	(Negative-true logic)	*/
#define MMC_PMR_DETECT1		 _PMR(MMC_DETECT1_PORTNO , MMC_DETECT1_BITNO )	/* MMC DETECT1	(Negative-true logic)	*/
#endif	/* #if (MMC_SLOT_NUM > 1) */


/*----------- Definitions of resource used -----------*/
#undef	MMC_CRC_HARD
#undef	MMC_CRC_SOFT
#undef	MMC_CRC_MSBF
#undef	MMC_CRC_LSBF
#undef	MMC_DTC_USED

#define MMC_RSPI_USED										/* RSPI used							*/
#define MMC_RSPI_TRAN_SIZE	4								/* RSPI transmit size 					*/
#define MMC_SYNC_MSBF										/* RSPI MSB first						*/

#ifdef MMC_OPTION_1
#define MMC_CRC_SOFT										/* Encode by soft CRC (ROM table used)	*/
#endif	/* #ifdef MMC_OPTION_1 */

#ifdef MMC_OPTION_2
#define MMC_CRC_HARD										/* Encode by hard CRC					*/
#define MMC_CRC_MSBF										/* CRC MSB first						*/
#endif	/* #ifdef MMC_OPTION_2 */

#ifdef MMC_OPTION_3
#define MMC_CRC_SOFT										/* Encode by soft CRC (ROM table used)	*/
#define MMC_DTC_USED										/* DTC Used (Read Only) 				*/
#endif	/* #ifdef MMC_OPTION_3 */

#ifdef MMC_OPTION_4
#define MMC_CRC_HARD										/* Encode by hard CRC					*/
#define MMC_CRC_MSBF										/* CRC MSB first						*/
#define MMC_DTC_USED										/* DTC Used (Read Only) 				*/
#endif	/* #ifdef MMC_OPTION_4 */


/*----------------- PRCR definitions -----------------*/
#define MMC_PRCR			SYSTEM.PRCR.WORD
#define MMC_PRCR_W_EI		(uint16_t)0xA502
#define MMC_PRCR_W_DI		(uint16_t)0xA500

#define MMC_PRCR_EI() do{ 			\
	MMC_PRCR = MMC_PRCR_W_EI;		\
}while(0)

#define MMC_PRCR_DI() do{ 			\
	MMC_PRCR = MMC_PRCR_W_DI;		\
}while(0)

/*----------------- RSPI definitions -----------------*/
#define MMC_MSTP_RSPI			_MSTP(_RSPIn)				/* RSPI Module stop register					*/
#define MMC_RSPI_SPCR			RSPIn.SPCR.BYTE				/* RSPI control register						*/
#define MMC_RSPI_SSLP			RSPIn.SSLP.BYTE				/* RSPI slave select polarity register			*/
#define MMC_RSPI_SPPCR			RSPIn.SPPCR.BYTE			/* RSPI pin control register					*/
#define MMC_RSPI_SPSR			RSPIn.SPSR.BYTE				/* RSPI status register							*/
#define MMC_RSPI_SPDR			RSPIn.SPDR.LONG					/* RSPI data register							*/
#define MMC_RSPI_SPSCR			RSPIn.SPSCR.BYTE			/* RSPI sequence control register				*/
#define MMC_RSPI_SPSSR			RSPIn.SPSSR.BYTE			/* RSPI sequence status register				*/
#define MMC_RSPI_SPBR			RSPIn.SPBR.BYTE				/* RSPI bit rate register						*/
#define MMC_RSPI_SPDCR			RSPIn.SPDCR.BYTE			/* RSPI data control register					*/
#define MMC_RSPI_SPCKD			RSPIn.SPCKD.BYTE			/* RSPI clock delayl register					*/
#define MMC_RSPI_SSLND			RSPIn.SSLND.BYTE			/* RSPI slave select negation delay register	*/
#define MMC_RSPI_SPND			RSPIn.SPND.BYTE				/* RSPI next access delay register				*/
#define MMC_RSPI_SPCR2			RSPIn.SPCR2.BYTE			/* RSPI control register 2						*/
#define MMC_RSPI_SPCMD0			RSPIn.SPCMD0.WORD			/* RSPI command register 0						*/

#define MMC_RSPI_ORER			RSPIn.SPSR.BIT.OVRF			/* RSPI overrun error flag						*/
#define MMC_RSPI_PER			RSPIn.SPSR.BIT.PERF			/* RSPI Parity error flag						*/
#define MMC_RSPI_MODF			RSPIn.SPSR.BIT.MODF			/* RSPI Mode Fault error flag					*/
#define MMC_RSPI_SPB			RSPIn.SPCMD0.BIT.SPB		/* RSPI data length setting						*/
#define MMC_RSPI_TXEND			RSPIn.SPSR.BIT.IDLNF		/* RSPI idle flag								*/
#define MMC_RSPI_TXNEXT			_IR_BYTE(MMC_TX)			/* RSPI Transmit data empty						*/
#define MMC_RSPI_RXNEXT			_IR_BYTE(MMC_RX)			/* RSPI Receive data full						*/
#define MMC_VECT_TXNEXT			_VECT(MMC_TX)				/* RSPI Transmit data empty vector number		*/
#define MMC_VECT_RXNEXT			_VECT(MMC_RX)				/* RSPI Receive data full vector number			*/
#define MMC_RSPI_TXNEXT_ISEL	_DTCE_BYTE(MMC_TX)			/* RSPI Transmit data empty interrupt select	*/
#define MMC_RSPI_RXNEXT_ISEL	_DTCE_BYTE(MMC_RX)			/* RSPI Receive data full interrupt select		*/
#define MMC_RSPI_TXNEXT_IER		_IEN(MMC_TX)				/* RSPI Transmit data interrupt enable flag		*/
#define MMC_RSPI_RXNEXT_IER		_IEN(MMC_RX)				/* RSPI Receive data full interrupt enable flag	*/
#define MMC_RSPI_IPR			_IPR_BYTE(MMC_TX)			/* RSPI Transmit&Receive interrupt priority		*/


/* RSPI setting */
#define MMC_SPCR_INIT			(uint8_t)0x09
/*	00001001B	*/	/* SPCR RSPI unused setting							*/
/*	|||||||+---------- Mode select			: clock synchronous			*/
/*	||||||+----------- Communication select	: Initial setting			*/
/*	|||||+------------ Mode Fault Error		: Disable					*/
/*	||||+------------- Master Slave select	: Master					*/
/*	|||+-------------- Error interrupt		: Disable					*/
/*	||+--------------- Transmit interrupt	: Disable					*/
/*	|+---------------- RSPI function enable	: Disable					*/
/*	+----------------- Receive interrupt	: Disable					*/

#define MMC_SPPCR_INIT			(uint8_t)0x30
/*	00110000B	*/	/* SPPCR Pin control setting						*/
/*	|||||||+---------- Loopback				: Clock synchronous			*/
/*	||||||+----------- Loopback2			: Only transmit operation	*/
/*	|||||+------------ Output pin mode		: Disable					*/
/*	||||+------------- Reserved											*/
/*	|||+-------------- MOSI idle fixed value: Equals 1					*/
/*	||+--------------- MOSI output value	: Value set in the MOIFV bit*/
/*	++---------------- Reserved											*/

#define MMC_SPSCR_INIT			(uint8_t)0x00
/*	00000000B	*/	/* SPSCR RSPI Sequence control setting				*/
/*	|||||+++---------- Sequence length		: Clock synchronous			*/
/*	+++++------------- Loopback2			: Only transmit operation	*/

#define MMC_SPDCR_INIT			(uint8_t)0x20//(uint8_t)0x24
/*	00100000B	*/	/* SPDCR RSPI Data control setting					*/
/*	||||||++---------- Number of frames		: 1							*/
/*	||||++------------ SSL pin				: Not applicable			*/
/*	|||+-------------- Read data			: From receive buffer		*/
/*	||+--------------- Data access size		: Long word					*/
/*	++---------------- Reserved											*/


#define MMC_SPCMD0_INIT			(uint16_t)0x0203
/*	0000001000000011B  SPCMD0 Command register setting					*/
/*	|||||||||||||||+-- Variation on odd edge. Sampling on even edge		*/
/*	||||||||||||||+--- RSPCK=1 when idle								*/
/*	||||||||||||++---- Bit rate division	: base bit rate				*/
/*	|||||||||+++------ SSL signal Assertion : Not applicable			*/
/*	||||||||+--------- SSL signal level		: Not applicable			*/
/*	||||++++---------- RSPI data length		: 32bit						*/
/*	|||+-------------- MSB First										*/
/*	||+--------------- Next access delay 	: Initial setting			*/
/*	|+---------------- Negation 	delay 	: Initial setting			*/
/*	+----------------- RSPCK delay		 	: Initial setting			*/

#define MMC_SPCR2_INIT			(uint8_t)0x00
/*	00000000B	*/	/* SPCR2 RSPI control setting						*/
/*	|||||||+---------- Parity Enable		: Disable					*/
/*	||||||+----------- Parity mode			: Not applicable			*/
/*	|||||+------------ Idle interrupt		: Disable					*/
/*	||||+------------- Parity self testing	: Disable					*/
/*	++++-------------- Reserved											*/

#define MMC_SPCR_TX				(uint8_t)0x6B
/*	01101011B	*/	/* SPCR RSPI unused setting							*/
/*	|||||||+---------- Mode select			: Clock synchronous			*/
/*	||||||+----------- Communication select	: Only transmit operation	*/
/*	|||||+------------ Mode Fault Error		: Disable					*/
/*	||||+------------- Master Slave select	: Master					*/
/*	|||+-------------- Error interrupt		: Disable					*/
/*	||+--------------- Transmit interrupt	: Enable					*/
/*	|+---------------- RSPI function enable	: Enable					*/
/*	+----------------- Receive interrupt	: Disable					*/

#define MMC_SPCR_TRX			(uint8_t)0xE9
/*	11101001B	*/	/* SPCR RSPI unused setting							*/
/*	|||||||+---------- Mode select			: Clock synchronous			*/
/*	||||||+----------- Communication select	: Full-duplex operation		*/
/*	|||||+------------ Mode Fault Error		: Disable					*/
/*	||||+------------- Master Slave select	: Master					*/
/*	|||+-------------- Error interrupt		: Disable					*/
/*	||+--------------- Transmit interrupt	: Enable					*/
/*	|+---------------- RSPI function enable	: Enable					*/
/*	+----------------- Receive interrupt	: Enable					*/

#define MMC_RSPI_TXNEXT_MASK	(uint8_t)0x01
/*	00000001B	*/	/* Interrupt Request Flag Check						*/
/*	|||||||+---------- Interrupt Status Flag : Check					*/
/*	+++++++----------- Reserved				 : No Check.				*/

#define MMC_RSPI_TXNEXT_OFF		(uint8_t)0x00
/*	00000000B	*/	/* Interrupt Request Flag Check						*/
/*	|||||||+---------- Interrupt Status Flag : Clear					*/
/*	+++++++----------- Reserved				 : Writes 0.				*/

#define MMC_RSPI_RXNEXT_MASK	(uint8_t)0x01
/*	00000001B	*/	/* Interrupt Request Flag Check						*/
/*	|||||||+---------- Interrupt Status Flag : Check					*/
/*	+++++++----------- Reserved				 : No Check.				*/

#define MMC_RSPI_RXNEXT_OFF		(uint8_t)0x00
/*	00000000B	*/	/* Interrupt Request Flag Check						*/
/*	|||||||+---------- Interrupt Status Flag : Clear					*/
/*	+++++++----------- Reserved				 : Writes 0.				*/

#define MMC_RSPI_INT_PRIORITY	(uint8_t)0x00
/*	00000000B	*/	/* Interrupt Request Flag Check						*/
/*	|||||+++---------- Interrupt priority	 : 0 (Disable)				*/
/*	+++++------------- Reserved				 : Writes 0.				*/


#define MMC_DUMMY_DATA			(uint8_t)0xFF		/* MMC dummy data for some command	*/
#define RSPI_DUMMY_DATA			(uint32_t)0xFFFFFFFF	/* SPI dummy data for receiving data	*/

/*----------------- CRC definitions ------------------*/
#ifdef MMC_CRC_HARD
#define MMC_CRCC				CRC.CRCCR.BYTE				/* CRC control register					*/
#define MMC_CRCIN				CRC.CRCDIR					/* CRC input register					*/
#define MMC_CRCD				CRC.CRCDOR					/* CRC data register					*/
#define MMC_MSTPCR_CRC			SYSTEM.MSTPCRB.BIT.MSTPB23	/* CRC Module stop setting 				*/

#endif	/* #ifdef MMC_CRC_HARD */

#ifdef MMC_DTC_USED
#define	MMC_DTCCR				DTC.DTCCR.BYTE
#define	MMC_DTCVBR				DTC.DTCVBR
#define	MMC_DTCADMOD			DTC.DTCADMOD.BYTE
#define	MMC_DTCST				DTC.DTCST.BYTE
#define MMC_MSTPCR_DTC			SYSTEM.MSTPCRA.BIT.MSTPA28	/* DTC Module stop setting 				*/

#define MMC_DTCCR_INIT1			(uint8_t)0x08
/*	00001000B	*/	/* DTCCR initial setting						*/
/*	|||||||+---------- Transfer Stop Flag	: Read only 			*/
/*	|||||++----------- Reserved				: Writes 0.				*/
/*	||||+------------- Reserved				: Writes 1.				*/
/*	|||+-------------- Read Skip			: Disable				*/
/*	+++--------------- Reserved				: Writes 0.				*/

#define MMC_DTCCR_INIT2			(uint8_t)0x18
/*	00011000B	*/	/* DTCCR initial setting (Set after DTC table.)	*/
/*	|||||||+---------- Transfer Stop Flag	: Read only 			*/
/*	|||||++----------- Reserved				: Writes 0.				*/
/*	||||+------------- Reserved				: Writes 1.				*/
/*	|||+-------------- Read skip			: Enable				*/
/*	+++--------------- Reserved				: Writes 0.				*/

#define MMC_DTCADOMOD_INIT		(uint8_t)0x00
/*	00000000B	*/	/* DTCADOMOD initial setting					*/
/*	|||||||+---------- Short-Address Mode 	: Full-address mode		*/
/*	+++++++----------- Reserved				: Writes 0.				*/

#define MMC_DTCST_INIT1			(uint8_t)0x00
/*	00000000B	*/	/* DTCST initial setting (Set after DTC table.) */
/*	|||||||+---------- DTC Module Start 	: DTC module stop		*/
/*	+++++++----------- Reserved				: Writes 0.				*/

#define MMC_DTCST_INIT2			(uint8_t)0x01
/*	00000001B	*/	/* DTCST initial setting						*/
/*	|||||||+---------- DTC Module Start 	: DTC module start		*/
/*	+++++++----------- Reserved				: Writes 0.				*/

#define	MMC_MRA_TX_TX_EI_LIT1	(uint8_t)0x88
/*	10001000B	*/	/* DTC Mode Register A for TX						*/
/*	||||||++---------- Reserved 				: Writes 0.				*/
/*	||||++------------ Source Addressing Mode	: Increment				*/
/*	||++-------------- Data Transfer Size		: Byte transfer			*/
/*	++---------------- DTC Mode					: Block transfer mode	*/

#define	MMC_MRB_TX_TX_EI_LIT1	(uint8_t)0x8C
/*	10001100B	*/	/* DTC Mode Register B for TX						*/
/*	||||||++---------- Reserved 			: Writes 0.					*/
/*	||||++------------ Destination Addressing Mode	: Decrement			*/
/*	|||+-------------- Transfer Mode Select	: Destination side			*/
/*	||+--------------- Interrupt Select		: When specified data transfer is completed	*/
/*	|+---------------- Chain Transfer Select: Continuously				*/
/*	+----------------- Chain Transfer Enable: Enable					*/

#define	MMC_MRA_TX_TX_EI_LIT2	(uint8_t)0x20
/*	00100000B	*/	/* DTC Mode Register A for TX						*/
/*	||||||++---------- Reserved 				: Writes 0.				*/
/*	||||++------------ Source Addressing Mode	: Fixed.				*/
/*	||++-------------- Data Transfer Size		: Long word transfer	*/
/*	++---------------- DTC Mode					: Normal transfer mode	*/

#define	MMC_MRB_TX_TX_EI_LIT2	(uint8_t)0x00
/*	00000000B	*/	/* DTC Mode Register B for TX						*/
/*	||||||++---------- Reserved 			: Writes 0.					*/
/*	||||++------------ Destination Addressing Mode	: Fixed				*/
/*	|||+-------------- Transfer Mode Select	: Don't Care (Normal mode)	*/
/*	||+--------------- Interrupt Select		: When specified data transfer is completed	*/
/*	|+---------------- Chain Transfer Select: Don't Care (Chain disable)*/
/*	+----------------- Chain Transfer Enable: Disable					*/

#define	MMC_MRA_TX_TX_EI_BIG1	(uint8_t)0x28
/*	00101000B	*/	/* DTC Mode Register A for TX						*/
/*	||||||++---------- Reserved 				: Writes 0.				*/
/*	||||++------------ Source Addressing Mode	: Increment				*/
/*	||++-------------- Data Transfer Size		: Long word transfer	*/
/*	++---------------- DTC Mode					: Normal transfer mode	*/

#define	MMC_MRB_TX_TX_EI_BIG1	(uint8_t)0x00
/*	00000000B	*/	/* DTC Mode Register B for TX						*/
/*	||||||++---------- Reserved 			: Writes 0.					*/
/*	||||++------------ Destination Addressing Mode	: Fixed				*/
/*	|||+-------------- Transfer Mode Select	: Don't Care (Normal mode)	*/
/*	||+--------------- Interrupt Select		: When specified data transfer is completed	*/
/*	|+---------------- Chain Transfer Select: Don't Care (Chain disable)*/
/*	+----------------- Chain Transfer Enable: Disable					*/


#define	MMC_MRA_TRX_TX_EI		(uint8_t)0x20
/*	00100000B	*/	/* DTC Mode Register A for TX						*/
/*	||||||++---------- Reserved 				: Writes 0.				*/
/*	||||++------------ Source Addressing Mode	: Fixed					*/
/*	||++-------------- Data Transfer Size		: Long word transfer	*/
/*	++---------------- DTC Mode					: Normal transfer mode	*/

#define	MMC_MRB_TRX_TX_EI 		(uint8_t)0x00
/*	00000000B	*/	/* DTC Mode Register B for TX						*/
/*	||||||++---------- Reserved 			: Writes 0.					*/
/*	||||++------------ Destination Addressing Mode	: Fixed				*/
/*	|||+-------------- Transfer Mode Select	: Don't Care (Normal mode)	*/
/*	||+--------------- Interrupt Select		: When specified data transfer is completed	*/
/*	|+---------------- Chain Transfer Select: Don't Care (Chain disable)*/
/*	+----------------- Chain Transfer Enable: Disable					*/

#define	MMC_MRA_TRX_RX_EI		(uint8_t)0x20
/*	00100000B	*/	/* DTC Mode Register A for RX						*/
/*	||||||++---------- Reserved 				: Writes 0.				*/
/*	||||++------------ Source Addressing Mode	: Fixed					*/
/*	||++-------------- Data Transfer Size		: Long word transfer	*/
/*	++---------------- DTC Mode					: Normal transfer mode	*/

#define	MMC_MRB_TRX_RX_EI 		(uint8_t)0x08
/*	00001000B	*/	/* DTC Mode Register B for RX						*/
/*	||||||++---------- Reserved 			: Writes 0.					*/
/*	||||++------------ Destination Addressing Mode	: Increment			*/
/*	|||+-------------- Transfer Mode Select	: Don't Care (Normal mode)	*/
/*	||+--------------- Interrupt Select		: When specified data transfer is completed	*/
/*	|+---------------- Chain Transfer Select: Don't Care (Chain disable)*/
/*	+----------------- Chain Transfer Enable: Disable					*/

#define	MMC_ISEL_DTC  (uint8_t)0x01
/*	00000001B	*/	/* DTC Activation Setting							*/
/*	|||||||+---------- DTC Activation Enable : Enable					*/
/*	+++++++----------- Reserved				 : Writes 0.				*/


#endif	/* #ifdef MMC_DTC_USED */

/************************************************************************************************/
/*	Unions																						*/
/************************************************************************************************/

/************************************************************************************************/
/*	Structs																						*/
/************************************************************************************************/

/************************************************************************************************/
/*	Externs																						*/
/************************************************************************************************/

/************************************************************************************************/
/*	Macros																						*/
/************************************************************************************************/
/*------------- output port drive control --------------*/
#define MMC_DSCR_HIGH_DRIVE								/* High-drive output						*/

#if ((MMC_DSCR_DATAO_SET == 1) && defined(MMC_DSCR_HIGH_DRIVE))
#define MMC_DSCR_DATAO_INIT() do {						/* Driver use terminal initial setting	*/	\
	MMC_DSCR_DATAO = MMC_HI;							/* DataOut High-drive output			*/	\
} while (0)
#else	/* #if ((MMC_DSCR_DATAO_SET == 1) && defined(MMC_DSCR_HIGH_DRIVE)) */
#define MMC_DSCR_DATAO_INIT()							/* DataOut default-drive output			*/
#endif	/* #if ((MMC_DSCR_DATAO_SET == 1) && defined(MMC_DSCR_HIGH_DRIVE)) */

#if ((MMC_DSCR_CLK_SET == 1) && defined(MMC_DSCR_HIGH_DRIVE))
#define MMC_DSCR_CLK_INIT() do {						/* Driver use terminal initial setting	*/	\
	MMC_DSCR_CLK = MMC_HI;								/* CLK High-drive output				*/	\
} while (0)
#else	/* #if ((MMC_DSCR_CLK_SET == 1) && defined(MMC_DSCR_HIGH_DRIVE)) */
#define MMC_DSCR_CLK_INIT()								/* CLK default-drive output				*/
#endif	/* #if ((MMC_DSCR_CLK_SET == 1) && defined(MMC_DSCR_HIGH_DRIVE)) */

/*------------- Driver use port control --------------*/
#if (MMC_SLOT_NUM == 1)
/* !!!! The other Ports are set to input mode. !!!! */
#define MMC_IO_INIT() do {								/* Driver use terminal initial setting	*/	\
	MMC_PMR_DATAI   = MMC_FALSE;						/* DataIn			Peripheral disable	*/	\
	MMC_PMR_DATAO   = MMC_FALSE;						/* DataOut			Peripheral disable	*/	\
	MMC_PMR_CLK	    = MMC_FALSE;						/* CLK				Peripheral disable	*/	\
	MMC_PMR_CS0	    = MMC_FALSE;						/* CS0				Peripheral disable	*/	\
	MMC_PMR_DETECT0 = MMC_FALSE;						/* DETECT0			Peripheral disable	*/	\
	MMC_PODR_CS0    = MMC_HI;							/* CS0				"H"					*/	\
	MMC_PDR_CS0     = MMC_OUT;							/* CS0				Output				*/	\
	MMC_PODR_CS0    = MMC_HI;							/* CS0				"H"					*/	\
	MMC_B0WI 		= MMC_FALSE;						/* PFSWE bit write enable				*/	\
	MMC_PFSWE 		= MMC_TRUE;							/* PmnPFS Register write enable			*/	\
	MMC_PDR_DATAI   = MMC_IN;							/* DataIn			Input				*/	\
	MMC_PFS_DATAI	= MMC_PFS_DATAI_INIT;				/* DataIn 			Pin Function Select	*/	\
	MMC_PODR_DATAO  = MMC_HI;							/* DataOut			"H"					*/	\
	MMC_PDR_DATAO   = MMC_OUT;							/* DataOut			Output				*/	\
	MMC_PODR_DATAO  = MMC_HI;							/* DataOut			"H"					*/	\
	MMC_PFS_DATAO	= MMC_PFS_DATAO_INIT;				/* DataOut 			Pin Function Select	*/	\
	MMC_DSCR_DATAO_INIT();								/* DataOut			High-drive output	*/	\
	MMC_PODR_CLK   	= MMC_HI;							/* CLK				"H"					*/	\
	MMC_PDR_CLK   	= MMC_OUT;							/* CLK				Output				*/	\
	MMC_PODR_CLK   	= MMC_HI;							/* CLK				"H"					*/	\
	MMC_PFS_CLK		= MMC_PFS_CLK_INIT;					/* CLK 				Pin Function Select	*/	\
	MMC_DSCR_CLK_INIT();								/* CLK				High-drive output	*/	\
	MMC_PFSWE 		= MMC_FALSE;						/* PmnPFS Register write disable		*/	\
	MMC_B0WI 		= MMC_TRUE;							/* PFSWE bit write disable				*/	\
	MMC_PDR_DETECT0 = MMC_IN;							/* DETECT0			Input				*/	\
} while (0)
#endif	/* #if (MMC_SLOT_NUM == 1) */

#if (MMC_SLOT_NUM > 1)
/* !!!! The other Ports are set to input mode. !!!! */
#define MMC_IO_INIT() do {								/* Driver use terminal initial setting	*/	\
	MMC_PMR_DATAI   = MMC_FALSE;						/* DataIn			Peripheral disable	*/	\
	MMC_PMR_DATAO   = MMC_FALSE;						/* DataOut			Peripheral disable	*/	\
	MMC_PMR_CLK	    = MMC_FALSE;						/* CLK				Peripheral disable	*/	\
	MMC_PMR_CS0	    = MMC_FALSE;						/* CS0				Peripheral disable	*/	\
	MMC_PMR_CS1	    = MMC_FALSE;						/* CS0				Peripheral disable	*/	\
	MMC_PMR_DETECT0 = MMC_FALSE;						/* DETECT0			Peripheral disable	*/	\
	MMC_PMR_DETECT1 = MMC_FALSE;						/* DETECT1			Peripheral disable	*/	\
	MMC_PODR_CS0    = MMC_HI;							/* CS0				"H"					*/	\
	MMC_PDR_CS0     = MMC_OUT;							/* CS0				Output				*/	\
	MMC_PODR_CS0    = MMC_HI;							/* CS0				"H"					*/	\
	MMC_PODR_CS1    = MMC_HI;							/* CS1				"H"					*/	\
	MMC_PDR_CS1     = MMC_OUT;							/* CS1				Output				*/	\
	MMC_PODR_CS1    = MMC_HI;							/* CS1				"H"					*/	\
	MMC_B0WI 		= MMC_FALSE;						/* PFSWE bit write enable				*/	\
	MMC_PFSWE 		= MMC_TRUE;							/* PmnPFS Register write enable			*/	\
	MMC_PDR_DATAI   = MMC_IN;							/* DataIn			Input				*/	\
	MMC_PFS_DATAI	= MMC_PFS_DATAI_INIT;				/* DataIn 			Pin Function Select	*/	\
	MMC_PODR_DATAO  = MMC_HI;							/* DataOut			"H"					*/	\
	MMC_PDR_DATAO   = MMC_OUT;							/* DataOut			Output				*/	\
	MMC_PODR_DATAO  = MMC_HI;							/* DataOut			"H"					*/	\
	MMC_PFS_DATAO	= MMC_PFS_DATAO_INIT;				/* DataOut 			Pin Function Select	*/	\
	MMC_DSCR_DATAO_INIT();								/* DataOut			High-drive output	*/	\
	MMC_PODR_CLK   	= MMC_HI;							/* CLK				"H"					*/	\
	MMC_PDR_CLK   	= MMC_OUT;							/* CLK				Output				*/	\
	MMC_PODR_CLK   	= MMC_HI;							/* CLK				"H"					*/	\
	MMC_PFS_CLK		= MMC_PFS_CLK_INIT;					/* CLK 				Pin Function Select	*/	\
	MMC_DSCR_CLK_INIT();								/* CLK				High-drive output	*/	\
	MMC_PFSWE 		= MMC_FALSE;						/* PmnPFS Register write disable		*/	\
	MMC_B0WI 		= MMC_TRUE;							/* PFSWE bit write disable				*/	\
	MMC_PDR_DETECT0 = MMC_IN;							/* DETECT0			Input				*/	\
	MMC_PDR_DETECT1 = MMC_IN;							/* DETECT1			Input				*/	\
} while (0)
#endif	/* #if (MMC_SLOT_NUM > 1) */

/*------------------ DataIn control ------------------*/
#define MMC_DATAI_INIT() do {							/* DataIn initial setting				*/	\
} while (0)

/*----------------- DataOut control ------------------*/
#define MMC_DATAO_INIT() do {							/* DataOut initial setting				*/	\
} while (0)

#define MMC_DATAO_OPEN() do {							/* DataOut open setting					*/	\
} while (0)

/*------------------- CLK control --------------------*/
#define MMC_CLK_INIT() do {								/* CLK initial setting					*/	\
} while (0)

#define MMC_CLK_OPEN() do {								/* CLK open setting						*/	\
} while (0)

/*------------------ DETECT control ------------------*/
#if (MMC_SLOT_NUM == 1)
#define MMC_DETECT_INIT(SlotNo) do {					/* DETECT initial setting				*/	\
	MMC_PDR_DETECT0     = MMC_IN;						/* DETECT			Input				*/	\
} while (0)

#define MMC_GET_DETECT(SlotNo, Lv) do {					/* DETECT input control					*/	\
	Lv = MMC_PIDR_DETECT0;																			\
} while (0)
#endif	/* #if (MMC_SLOT_NUM == 1) */

#if (MMC_SLOT_NUM > 1)
#define MMC_DETECT_INIT(SlotNo) do {					/* DETECT initial setting				*/	\
	switch (SlotNo) {																				\
	case MMC_SLOT0:		MMC_PDR_DETECT0 = MMC_IN;	break;											\
	case MMC_SLOT1:		MMC_PDR_DETECT1 = MMC_IN;	break;											\
	default:										break;											\
	}																								\
} while (0)

#define MMC_GET_DETECT(SlotNo, Lv) do {					/* DETECT input control					*/	\
	Lv = MMC_HI;										/* Initialize by non-detection			*/	\
	switch (SlotNo) {																				\
	case MMC_SLOT0:		Lv = MMC_PIDR_DETECT0;		break;											\
	case MMC_SLOT1:		Lv = MMC_PIDR_DETECT1;		break;											\
	default:										break;											\
	}																								\
} while (0)
#endif	/* #if (MMC_SLOT_NUM > 1) */

/*-------------------- CS control --------------------*/
#if (MMC_SLOT_NUM == 1)
#define MMC_CS_INIT(SlotNo) do {						/* CS initial setting					*/	\
	MMC_PODR_CS0     = MMC_HI;							/* CS0				"H"					*/	\
	MMC_PDR_CS0		 = MMC_OUT;							/* CS0				Output				*/	\
	MMC_PODR_CS0     = MMC_HI;							/* CS0				"H"					*/	\
} while (0)

#define MMC_CS_OPEN(SlotNo) do {						/* CS open setting						*/	\
	MMC_PDR_CS0     = MMC_IN;							/* CS0				Input				*/	\
} while (0)

#define MMC_SET_CS(SlotNo, Lv) do {						/* CS output control					*/	\
	MMC_PODR_CS0       = Lv;																		\
} while (0)
#endif	/* #if (MMC_SLOT_NUM == 1) */

#if (MMC_SLOT_NUM > 1)
#define MMC_CS_INIT(SlotNo) do {						/* CS initial setting					*/	\
	switch (SlotNo) {																				\
	case MMC_SLOT0:																					\
		MMC_PODR_CS0   = MMC_HI;						/* CS0				"H"					*/	\
		MMC_PDR_CS0  = MMC_OUT;							/* CS0				Output				*/	\
		MMC_PODR_CS0   = MMC_HI;						/* CS0				"H"					*/	\
		break;																						\
	case MMC_SLOT1:																					\
		MMC_PODR_CS1   = MMC_HI;						/* CS1				"H"					*/	\
		MMC_PDR_CS1  = MMC_OUT;							/* CS1				Output				*/	\
		MMC_PODR_CS1   = MMC_HI;						/* CS1				"H"					*/	\
		break;																						\
	default:		break;																			\
	}																								\
} while (0)

#define MMC_CS_OPEN(SlotNo) do {						/* CS open setting						*/	\
	switch (SlotNo) {																				\
	case MMC_SLOT0:		MMC_PDR_CS0 = MMC_IN;	break;	/* CS0			Input					*/	\
	case MMC_SLOT1:		MMC_PDR_CS1 = MMC_IN;	break;	/* CS1			Input					*/	\
	default:									break;												\
	}																								\
} while (0)

#define MMC_SET_CS(SlotNo, Lv) do {						/* CS output control					*/	\
	switch (SlotNo) {																				\
	case MMC_SLOT0:		MMC_PODR_CS0 = Lv;		break;												\
	case MMC_SLOT1:		MMC_PODR_CS1 = Lv;		break;												\
	default:									break;												\
	}																								\
} while (0)

#endif	/* #if (MMC_SLOT_NUM > 1) */

/*------------------- RSPI control -------------------*/

#define MMC_RSPI_DI() do {								/* RSPI disable setting					*/	\
	MMC_RSPI_SPCR	= MMC_SPCR_INIT;					/* Transmit&receive disable				*/	\
	MMC_RSPI_SPCR;										/* SPCR register read					*/	\
	MMC_RSPI_SPSR_CLEAR();								/* OER/MODF/PER clear					*/	\
	MMC_PRCR_EI();																					\
	MMC_MSTP_RSPI = 1;									/* RSPI0 Module stop enable setting		*/	\
	MMC_PRCR_DI();																					\
} while (0)

#define MMC_RSPI_EI(BR_DATA) do {						/* RSPI enable setting					*/	\
	MMC_PRCR_EI();																					\
	MMC_MSTP_RSPI = 0;									/* RSPI0 Module stop disable setting  == MSTP_RSPI1	(SYSTEM.MSTPCRB.BIT.MSTPB16)	*/	\
	MMC_PRCR_DI();																					\
	MMC_RSPI_SPCR   = MMC_SPCR_INIT;					/* RSPI enable							*/	\
	MMC_RSPI_SPCR;										/* SPCR register read					*/	\
	MMC_RSPI_SPPCR  = MMC_SPPCR_INIT;																\
	MMC_RSPI_SPBR   = BR_DATA;							/* Bit rate setting						*/	\
	MMC_RSPI_SPDCR  = MMC_SPDCR_INIT;					/* RSPI use frame count set				*/	\
	MMC_RSPI_SPCR2  = MMC_SPCR2_INIT;					/* RSPI parity and interrupt mask setting*/	\
	MMC_RSPI_SPCMD0 = MMC_SPCMD0_INIT;					/**** RSPI communication format setting	****/	\
	MMC_RSPI_SPSCR  = MMC_SPSCR_INIT;					/*0→0→*/                                    \
	MMC_RSPI_SPSR_CLEAR();								/* OER/MODF/PER clear					*/	\
	MMC_RSPI_IPR	= MMC_RSPI_INT_PRIORITY;			/* RSPI interrupt priority setting		*/	\
} while (0)

#define MMC_RSPI_BRR_SET(BR_DATA) do {					/* RSPI bit rate setting				*/	\
	MMC_RSPI_SPBR  = BR_DATA;																		\
} while (0)

#define MMC_RSPI_DATASIZE_SET(SIZE) do {				/* RSPI transmit enable setting			*/	\
	MMC_RSPI_SPB = SIZE;																			\
} while (0)

#define MMC_RSPI_SPSR_CLEAR() do {						/* RSPI status register clear			*/	\
	if(MMC_RSPI_ORER != MMC_FALSE)																	\
	{																								\
		do																							\
		{																							\
			MMC_RSPI_ORER = MMC_FALSE;																\
		}while(MMC_RSPI_ORER != MMC_FALSE);															\
	}																								\
	if(MMC_RSPI_PER != MMC_FALSE)																	\
	{																								\
		do																							\
		{																							\
			MMC_RSPI_PER = MMC_FALSE;																\
		}while(MMC_RSPI_PER != MMC_FALSE);															\
	}																								\
	if(MMC_RSPI_MODF != MMC_FALSE)																	\
	{																								\
		do																							\
		{																							\
			MMC_RSPI_MODF = MMC_FALSE;																\
		}while(MMC_RSPI_MODF != MMC_FALSE);															\
	}																								\
} while (0)

#define MMC_RSPI_TX_EI() do {							/* RSPI transmit enable setting	 		*/	\
	MMC_PMR_DATAI	= MMC_TRUE;							/* DataIn			Peripheral enable	*/	\
	MMC_PMR_DATAO	= MMC_TRUE;							/* DataOut			Peripheral enable	*/	\
	MMC_PMR_CLK 	= MMC_TRUE;							/* CLK				Peripheral enable	*/	\
	MMC_RSPI_SPSR_CLEAR();								/* Error flag clear						*/	\
	MMC_TXNEXT_CLR();									/* Transmission empty flag clear	ICU.IRn.IR=0	*/	\
	MMC_RSPI_SPCR   = MMC_SPCR_TX;						/* Transmit enable						*/	\
	MMC_RSPI_SPCR;										/* SPCR register read					*/	\
} while (0)

#define MMC_RSPI_TRX_EI() do {							/* RSPI transmit&receive enable setting	*/	\
	MMC_PMR_DATAI	= MMC_TRUE;							/* DataIn			Peripheral enable	*/	\
	MMC_PMR_DATAO	= MMC_TRUE;							/* DataOut			Peripheral enable	*/	\
	MMC_PMR_CLK 	= MMC_TRUE;							/* CLK				Peripheral enable	*/	\
	MMC_RSPI_SPSR_CLEAR();								/* Error flag clear						*/	\
	MMC_TXNEXT_CLR();									/* Transmission empty flag clear		*/	\
	MMC_RXNEXT_CLR();									/* Receive completion flag clear		*/	\
	MMC_RSPI_SPCR   = MMC_SPCR_TRX;						/* Transmit&receive enable				*/	\
	MMC_RSPI_SPCR;										/* SPCR register read					*/	\
} while (0)

#define  MMC_RSPI_TX_DI() do {							/* RSPI transmit disable setting		*/	\
	MMC_RSPI_SPCR   = MMC_SPCR_INIT;					/* Transmit disable						*/	\
	MMC_RSPI_SPCR;										/* SPCR register read					*/	\
	MMC_PMR_DATAI 	= MMC_FALSE;						/* DataIn			Peripheral disable	*/	\
	MMC_PMR_DATAO	= MMC_FALSE;						/* DataOut			Peripheral disable	*/	\
	MMC_PMR_CLK 	= MMC_FALSE;						/* CLK				Peripheral disable	*/	\
	MMC_RSPI_SPSR_CLEAR();								/* Error flag clear						*/	\
	MMC_TXNEXT_CLR();									/* Transmission empty flag clear ICU.IRn.IR=0		*/	\
} while (0)

#define MMC_RSPI_TRX_DI() do {						/* RSPI transmit&receive disable setting	*/	\
	MMC_RSPI_SPCR  = MMC_SPCR_INIT;					/* Transmit&receive disable					*/	\
	MMC_RSPI_SPCR;									/* SPCR register read						*/	\
	MMC_PMR_DATAI 	= MMC_FALSE;						/* DataIn			Peripheral disable	*/	\
	MMC_PMR_DATAO	= MMC_FALSE;						/* DataOut			Peripheral disable	*/	\
	MMC_PMR_CLK 	= MMC_FALSE;						/* CLK				Peripheral disable	*/	\
	MMC_RSPI_SPSR_CLEAR();								/* Error flag clear						*/	\
	MMC_TXNEXT_CLR();								/* Transmission empty flag clear			*/	\
	MMC_RXNEXT_CLR();								/* Receive completion flag clear			*/	\
} while (0)

#define MMC_TXNEXT_CHECK()	((MMC_RSPI_TXNEXT & MMC_RSPI_TXNEXT_MASK) == 0x00)
#define MMC_TXNEXT_CLR()	(MMC_RSPI_TXNEXT = MMC_RSPI_TXNEXT_OFF)
#define MMC_RXNEXT_CHECK()	((MMC_RSPI_RXNEXT & MMC_RSPI_RXNEXT_MASK) == 0x00)
#define MMC_RXNEXT_CLR()	(MMC_RSPI_RXNEXT = MMC_RSPI_RXNEXT_OFF)

/*----------------- CRC calculation ------------------*/
#ifdef MMC_CRC_HARD
#define MMC_CRC_CLR()		MMC_PRCR_EI();	MMC_MSTPCR_CRC = 0;	MMC_PRCR_DI();	MMC_CRCC  = 0x87
#define MMC_CRC_SET(Data)	MMC_CRCIN = Data
#define MMC_CRC_GET(Data)	Data = MMC_CRCD
#else	/* #ifdef MMC_CRC_HARD */
#define MMC_CRC_CLR()			gMmc_CrcData.us = 0x0000
#ifdef MTL_MCU_LITTLE
#define MMC_CRC_SET(Data) do {																		\
	uint8_t	ucTmp;																					\
	ucTmp              = gMmc_CrcData.uc[0];														\
	gMmc_CrcData.us    = T_Crc_Ccitt[gMmc_CrcData.uc[1] ^ Data];									\
	gMmc_CrcData.uc[1] = gMmc_CrcData.uc[1] ^ ucTmp;												\
} while (0)
#else	/* #ifdef MTL_MCU_LITTLE */
#define MMC_CRC_SET(Data) do {																		\
	uint8_t	ucTmp;																					\
	ucTmp              = gMmc_CrcData.uc[1];														\
	gMmc_CrcData.us    = T_Crc_Ccitt[gMmc_CrcData.uc[0] ^ Data];									\
	gMmc_CrcData.uc[0] = gMmc_CrcData.uc[0] ^ ucTmp;												\
} while (0)
#endif	/* #ifdef MTL_MCU_LITTLE */
#define MMC_CRC_GET(Data)		Data = gMmc_CrcData.us
#endif	/* #ifdef MMC_CRC_HARD */

/*----------------- DTC control------------------*/
#ifdef MMC_DTC_USED

/* DTC module initialize */
#define MMC_DTC_EI() do{																			\
	MMC_PRCR_EI();																					\
	MMC_MSTPCR_DTC 	= 0;																			\
	MMC_PRCR_DI();																					\
	MMC_DTCCR 		= MMC_DTCCR_INIT1;																\
	MMC_DTCVBR 		= (uint32_t)&gDtcVctTbl;														\
	MMC_DTCADMOD	= MMC_DTCADOMOD_INIT;															\
	MMC_DTCST		= MMC_DTCST_INIT1;																\
}while(0)

/* DTC module stop */
#define MMC_DTC_DI() do{																			\
	MMC_DTCST		= MMC_DTCST_INIT1;																\
	MMC_DTCCR 		= MMC_DTCCR_INIT1;																\
	MMC_PRCR_EI();																					\
	MMC_MSTPCR_DTC 	= 1;																			\
	MMC_PRCR_DI();																					\
}while(0)

#if defined(MTL_MCU_LITTLE)
#define	MMC_DTC_ALLOC_CHK_IDX		1
#define MMC_DTC_TX_EI(pAdr,cnt,work) do{															\
	MMC_DTCCR					= MMC_DTCCR_INIT1;													\
	gDtcAlloc[0].reserved		= 0x0000;															\
	gDtcAlloc[0].MRA			= MMC_MRA_TX_TX_EI_LIT1;											\
	gDtcAlloc[0].MRB			= MMC_MRB_TX_TX_EI_LIT1;											\
	gDtcAlloc[0].SAR			= (uint32_t)pAdr;													\
	gDtcAlloc[0].DAR			= (uint32_t)((uint8_t *)&work)+3;									\
	gDtcAlloc[0].CRA			= (uint16_t)0x0404;													\
	gDtcAlloc[0].CRB			= (uint16_t)cnt/4;													\
	gDtcAlloc[1].reserved		= 0x0000;															\
	gDtcAlloc[1].MRA			= MMC_MRA_TX_TX_EI_LIT2;											\
	gDtcAlloc[1].MRB			= MMC_MRB_TX_TX_EI_LIT2;											\
	gDtcAlloc[1].SAR			= (uint32_t)&work;													\
	gDtcAlloc[1].DAR			= (uint32_t)&MMC_RSPI_SPDR;											\
	gDtcAlloc[1].CRA			= (uint16_t)cnt/4;													\
	gDtcAlloc[1].CRB			= (uint16_t)0xffff;													\
	gDtcVctTbl[MMC_VECT_TXNEXT]	= (uint32_t)&gDtcAlloc[0];											\
	MMC_DTCCR 					= MMC_DTCCR_INIT2;													\
	MMC_RSPI_TXNEXT_ISEL		= MMC_ISEL_DTC;														\
	MMC_RSPI_TXNEXT_IER			= MMC_TRUE;															\
	MMC_DTCST					= MMC_DTCST_INIT2;													\
}while(0)
#else	/* #if defined(MTL_MCU_LITTLE) */
#define	MMC_DTC_ALLOC_CHK_IDX		0
#define MMC_DTC_TX_EI(pAdr,cnt,work) do{															\
	MMC_DTCCR					= MMC_DTCCR_INIT1;													\
	gDtcAlloc[0].reserved		= 0x0000;															\
	gDtcAlloc[0].MRA			= MMC_MRA_TX_TX_EI_BIG1;											\
	gDtcAlloc[0].MRB			= MMC_MRB_TX_TX_EI_BIG1;											\
	gDtcAlloc[0].SAR			= (uint32_t)pAdr;													\
	gDtcAlloc[0].DAR			= (uint32_t)&MMC_RSPI_SPDR;											\
	gDtcAlloc[0].CRA			= (uint16_t)cnt/4;													\
	gDtcVctTbl[MMC_VECT_TXNEXT]	= (uint32_t)&gDtcAlloc[0];											\
	MMC_DTCCR 					= MMC_DTCCR_INIT2;													\
	MMC_RSPI_TXNEXT_ISEL		= MMC_ISEL_DTC;														\
	MMC_RSPI_TXNEXT_IER			= MMC_TRUE;															\
	MMC_DTCST					= MMC_DTCST_INIT2;													\
}while(0)
#endif

#define MMC_DTC_TX_DI() do{																			\
	MMC_RSPI_TXNEXT_IER			= MMC_FALSE;														\
}while(0)


#define MMC_DTC_TRX_EI(pAdr, cnt) do{																\
	MMC_DTCCR					= MMC_DTCCR_INIT1;													\
	gDtcAlloc[0].reserved		= 0x0000;															\
	gDtcAlloc[0].MRA			= MMC_MRA_TRX_TX_EI;												\
	gDtcAlloc[0].MRB			= MMC_MRB_TRX_TX_EI;												\
	gDtcAlloc[0].SAR			= (uint32_t)gMmcDummyData;											\
	gDtcAlloc[0].DAR			= (uint32_t)&MMC_RSPI_SPDR;											\
	gDtcAlloc[0].CRA			= (uint16_t)cnt;													\
	gDtcAlloc[1].reserved		= 0x0000;															\
	gDtcAlloc[1].MRA			= MMC_MRA_TRX_RX_EI;												\
	gDtcAlloc[1].MRB			= MMC_MRB_TRX_RX_EI;												\
	gDtcAlloc[1].SAR			= (uint32_t)&MMC_RSPI_SPDR;											\
	gDtcAlloc[1].DAR			= (uint32_t)pAdr;													\
	gDtcAlloc[1].CRA			= (uint16_t)cnt;													\
	gDtcVctTbl[MMC_VECT_TXNEXT]	= (uint32_t)&gDtcAlloc[0];											\
	gDtcVctTbl[MMC_VECT_RXNEXT]	= (uint32_t)&gDtcAlloc[1];											\
	MMC_DTCCR 					= MMC_DTCCR_INIT2;													\
	MMC_RSPI_TXNEXT_ISEL		= MMC_ISEL_DTC;														\
	MMC_RSPI_RXNEXT_ISEL		= MMC_ISEL_DTC;														\
	MMC_RSPI_TXNEXT_IER			= MMC_TRUE;															\
	MMC_RSPI_RXNEXT_IER			= MMC_TRUE;															\
	MMC_TXNEXT_CLR();																				\
	MMC_RXNEXT_CLR();																				\
	MMC_DTCST					= MMC_DTCST_INIT2;													\
}while(0)

#define MMC_DTC_TRX_DI() do{																		\
	MMC_RSPI_RXNEXT				= MMC_FALSE;														\
	MMC_RSPI_TXNEXT_IER			= MMC_FALSE;														\
	MMC_RSPI_RXNEXT_IER			= MMC_FALSE;														\
}while(0)
#else	/* #ifdef MMC_DTC_USED */
#define MMC_DTC_EI()
#define MMC_DTC_DI()
#define MMC_DTC_TX_EI(pAdr,cnt,work)
#define MMC_DTC_TX_DI()
#define MMC_DTC_TRX_EI(pAdr, cnt)
#define MMC_DTC_TRX_DI()
#endif	/* #ifdef MMC_DTC_USED */

/************************************************************************************************/
/*	Prototypes																					*/
/************************************************************************************************/

#endif /* __MMC_SFR_H__ */
