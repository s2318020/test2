/*""FILE COMMENT""*******************************************************************
* File Name		: r_mmc_rx.h
* Version      	: 1.23C
* Device(s)    	: RX Family
* Tool-Chain 	: -
* H/W Platform 	: -
* Description	: MMC driver for RX family common definitions
*************************************************************************************
* History	: DD.MM.YYYY Version Description
*			: 06.12.2012 Ver1.23C
*""FILE COMMENT END""***************************************************************/
#ifndef	_R_MMC_RX_STR_H_
#define	_R_MMC_RX_STR_H_

/******************************************************************************
Typedef definitions
******************************************************************************/
/* DTC Allocation of transfer data in full-address mode */
typedef	struct	MMC_DTCALLOC_FULL_tag
{
#if defined(MTL_MCU_LITTLE)
	uint16_t	reserved;
	uint8_t		MRB;
	uint8_t		MRA;
	volatile uint32_t	SAR;
	volatile uint32_t	DAR;
	volatile uint16_t	CRB;
	volatile uint16_t	CRA;
#else
	uint8_t		MRA;
	uint8_t		MRB;
	uint16_t	reserved;
	volatile uint32_t	SAR;
	volatile uint32_t	DAR;
	volatile uint16_t	CRA;
	volatile uint16_t	CRB;
#endif
}MMC_DTCALLOC_FULL_t;

#endif