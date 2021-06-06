/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* File Name     : r_mmc_rspi.c
* Version       : 1.23C
* Device(s)     : RX Family
* Tool-Chain    : RX Standard Toolchain (V.1.2.1.0)
* H/W Platform  : -
* Description	: MMC driver SPI mode RSPI communication module
******************************************************************************/
/******************************************************************************
* History       : DD.MM.YYYY Version Description
*               : 22.08.2011 1.23B
*               : 27.12.2012 1.23C
******************************************************************************/
#include "r_mtl_com.h"			/* Renesas tool common definitions				*/
#include "r_mmc.h"				/* MMC driver common definitions				*/
#include "r_mmc_sub.h"			/* MMC driver sub module definitions			*/
#include "r_mmc_sfr.h"			/* MMC driver SFR definitions					*/
#include "r_mmc_io.h"			/* MMC driver I/O module definitions			*/
#include "r_mmc_rx_str.h"		/* MMC driver for RX family structure definitions	*/

#if defined(MMC_RSPI_USED)
/************************************************************************************************/
/*	Definitions																					*/
/************************************************************************************************/
#define MMC_FID							(8UL << 6 | 6UL)

#if defined(MMC_NOCHK_TIMEOUT)
#define MMC_RSPI_TX_TIMEOUT_CHK(wait , line)
#define MMC_RSPI_TRX_TIMEOUT_CHK(wait , line)
#define MMC_RSPI_TRX_DTC_TIMEOUT_CHK(wait , line)
#else	/* #if defined(MMC_NOCHK_TIMEOUT) */
#define MMC_RSPI_TX_TIMEOUT_CHK(wait , line)	do										\
{																						\
	wait--;																				\
	if (wait == 0) 								/* Transmission waiting time over	*/	\
	{																					\
		MMC_RSPI_TX_DI();						/* RSPI transmit disable			*/	\
		R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, line);										\
		return MMC_ERR_HARD;															\
	}																					\
	R_mtl_wait_lp(MMC_T_RSPI_WAIT);														\
}while(0)

#define MMC_RSPI_TRX_TIMEOUT_CHK(wait , line)	do										\
{																						\
	wait--;																				\
	if (wait == 0)								/* Transmission waiting time over	*/	\
	{																					\
		MMC_RSPI_TRX_DI();						/* RSPI transmit&receive disable	*/	\
		R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, line);										\
		return MMC_ERR_HARD;															\
	}																					\
	R_mtl_wait_lp(MMC_T_RSPI_WAIT);														\
}while(0)

#define MMC_RSPI_TRX_DTC_TIMEOUT_CHK(wait , line)	do									\
{																						\
	wait--;																				\
	if (wait == 0) 								/* Receive waiting time over		*/	\
	{																					\
		MMC_DTC_TRX_DI();																\
		MMC_DTC_DI();																	\
		MMC_RSPI_TRX_DI();						/* RSPI transmit&receive disable	*/	\
		R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, line);										\
		return MMC_ERR_HARD;															\
	}																					\
	R_mtl_wait_lp(MMC_T_RSPI_WAIT);														\
}while(0)
#endif	/* #if defined(MMC_NOCHK_TIMEOUT) */

#if defined(MMC_SYNC_ORERR)
#define MMC_RSPI_ORERR_CHK(line)	do													\
{																						\
	if (MMC_RSPI_ORER == MMC_TRUE) 				/* Overrun error ?					*/	\
	{																					\
		MMC_RSPI_ORER = MMC_FALSE; 				/* Overrun error flag clear			*/	\
		MMC_RSPI_SPDR;			 				/* recieve data	read				*/	\
		while(MMC_RSPI_ORER != MMC_FALSE);		/* wait Overrun error clear			*/	\
		MMC_RSPI_TRX_DI();						/* RSPI transmit&receive disable	*/	\
		R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, line);										\
		return MMC_ERR_HARD;															\
	}																					\
}while(0)
#else	/* #if defined(MMC_SYNC_ORERR) */
#define MMC_RSPI_ORERR_CHK(line)
#endif	/* #if defined(MMC_SYNC_ORERR) */

STATIC uint32_t R_mmc_Rspi_Tx_Exchg(uint8_t * pData, uint32_t Size);
STATIC void R_mmc_Rspi_Rx_Exchg(uint8_t * pData, uint32_t Data, uint32_t Size);

STATIC const uint8_t T_RspiSpb[5] = {2 , 7 , 15 , 1 , 2};

#if defined(MMC_DTC_USED)
#pragma section DTCTBL
#ifndef MMC_DTC_RAM
uint32_t 				gDtcVctTbl[256];
MMC_DTCALLOC_FULL_t 	gDtcAlloc[2];
#endif
#pragma section
#else	/* #if defined(MMC_DTC_USED) */
#endif	/* #if defined(MMC_DTC_USED) */

/******************************************************************************
* Declaration  : void R_mmc_Init_Sfr(void)
* Function Name: R_mmc_Init_Sfr
* Description  : Initialize SFR to use.
* Argument     : None
* Return Value : None
******************************************************************************/
void R_mmc_Init_Sfr(void)
{
	MMC_RSPI_DI();										/* RSPI disable setting							*/
}

/******************************************************************************
* Declaration  : void R_mmc_Sync_Enable(uint8_t flag, uint16_t bitrate)
* Function Name: R_mmc_Sync_Enable
* Description  : Enable SIO Module (option) and Set boudrate.
* Argument     : uint8_t  flag : 0=bitrate set ,1=SIO enable + bitrate set
*              : uint16_t bitrate : bitrate
* Return Value : None
******************************************************************************/
void R_mmc_Sync_Enable(uint8_t flag, uint16_t bitrate)
{
	if (flag != 0)
	{
		MMC_RSPI_EI(bitrate);							/* RSPI enable setting							*/
	}
	else
	{
		MMC_RSPI_BRR_SET(bitrate);						/* RSPI bitrate setting							*/
	}
}

/******************************************************************************
* Declaration  : void R_mmc_Sync_Disable(void)
* Function Name: R_mmc_Sync_Disable
* Description  : Disable SIO Module.
* Argument     : None
* Return Value : None
******************************************************************************/
void R_mmc_Sync_Disable(void)
{
	MMC_RSPI_DI();
}

/******************************************************************************
* Declaration  : int16_t R_mmc_Sync_MultTx(natural_uint_t TxCnt, uint8_t *pData)
* Function Name: R_mmc_Sync_MultTx
* Description  : Transmit the data for the designated number of bytes consecutively.
* Argument     : natural_uint_t	TxCnt	; Number of send bytes
*              : uint8_t 	*pData	; Send data buffer pointer
* Return Value : MMC_OK				; Success
*              : MMC_ERR_HARD		; Hardware Error
******************************************************************************/
int16_t R_mmc_Sync_MultTx(natural_uint_t TxCnt, uint8_t *pData)
{
#if !defined(MMC_NOCHK_TIMEOUT)
	natural_uint_t		TxWait = MMC_RSPI_TX_WAIT;				/* Transmission waiting counter					*/
#endif	/* #if !defined(MMC_NOCHK_TIMEOUT) */
	uint32_t			TxData;
	uint32_t 			tran_size;

	MMC_RSPI_TX_EI();											/* RSPI transmission enable	(RSPIn.SPCR.BYTE=0xE9)					*/

	do
	{
		tran_size = ((TxCnt >= MMC_RSPI_TRAN_SIZE) ? MMC_RSPI_TRAN_SIZE : TxCnt);

		TxData = R_mmc_Rspi_Tx_Exchg(pData, tran_size);
		pData += tran_size;
		/* Transmission preparation completion check */
		while (MMC_TXNEXT_CHECK())  							/* Loop for transmission empty	(ICU.IRn.IR Interrupt Status Flag)				*/
		{
			MMC_RSPI_TX_TIMEOUT_CHK(TxWait , __LINE__);
		}
		/* Transmission data -> Transmission buffer register */
		MMC_TXNEXT_CLR();										/* Transmission empty flag clear				*/
		MMC_RSPI_DATASIZE_SET(T_RspiSpb[tran_size]);                            //(RSPIn.SPCMDn.SPB[3:0] 設定	)
		MMC_RSPI_SPDR = TxData;									/* Transmission data setting	(RSPIn.SPDR	)				*/
		TxCnt -= tran_size;
	}
	while (TxCnt != 0);

	/* Transmission preparation completion check */
	while (MMC_TXNEXT_CHECK())  								/* Loop for transmission completion	(ICU.IRn.IR Interrupt Status Flag)			*/
	{
		MMC_RSPI_TX_TIMEOUT_CHK(TxWait , __LINE__);
	}

	/* Final data transmission completion check */
	while (MMC_RSPI_TXEND != MMC_FALSE)  						/* Loop for transmission completion	(RSPIn.SPSR.BIT.IDLNF ;RSPI transfer state)			*/
	{
		MMC_RSPI_TX_TIMEOUT_CHK(TxWait , __LINE__);
	}
	/* Clear IR bit of IR register */
	MMC_RSPI_TX_DI();											/* RSPI transmit disable (RSPIn.SPCR.BYTE=0x09)						*/

	return MMC_OK;
}

/******************************************************************************
* Declaration  : int16_t R_mmc_Sync_Rx(natural_uint_t RxCnt, uint8_t *pData)
* Function Name: R_mmc_Sync_Rx
* Description  : Receive the data for the designated number of bytes.
* Argument     : natural_uint_t	RxCnt	; Number of recieve bytes
*              : uint8_t 	*pData	; Recieve data buffer pointer
* Return Value : MMC_OK				; Success
*              : MMC_ERR_HARD		; Hardware Error
******************************************************************************/
int16_t R_mmc_Sync_Rx(natural_uint_t RxCnt, uint8_t *pData)
{
#if !defined(MMC_NOCHK_TIMEOUT)
	natural_uint_t		RxWait = MMC_RSPI_RX_WAIT;				/* Receive waiting counter						*/
#endif	/* #if !defined(MMC_NOCHK_TIMEOUT) */
	MMC_EXCHG_LONG		RxData;
	uint8_t 			tran_size;
	uint8_t 			recv_size;

	MMC_RSPI_TRX_EI();											/* RSPI transmit&receive enable					*/

	if (RxCnt > 0)
	{
		/* Transmission preparation completion check */
		while (MMC_TXNEXT_CHECK()) 								/* Loop for transmission empty					*/
		{
			MMC_RSPI_TRX_TIMEOUT_CHK(RxWait , __LINE__);
		}
		MMC_TXNEXT_CLR();
		tran_size = ((RxCnt >= MMC_RSPI_TRAN_SIZE) ? MMC_RSPI_TRAN_SIZE : RxCnt);
		recv_size = tran_size;
		MMC_RSPI_DATASIZE_SET(T_RspiSpb[tran_size]);
		MMC_RSPI_SPDR  = RSPI_DUMMY_DATA;
		RxCnt -= tran_size;

		while (RxCnt != 0)
		{
			tran_size = ((RxCnt >= MMC_RSPI_TRAN_SIZE) ? MMC_RSPI_TRAN_SIZE : RxCnt);

			/* Receive completion check */
			while (MMC_RXNEXT_CHECK())  						/* Loop for transmission empty					*/
			{
				MMC_RSPI_ORERR_CHK(__LINE__);
				MMC_RSPI_TRX_TIMEOUT_CHK(RxWait , __LINE__);
			}
			/* Receive data -> Receive data buffer */
			MMC_RXNEXT_CLR();									/* Receive completion flag clear				*/
			RxData.ul = MMC_RSPI_SPDR;							/* Receive data taking							*/

			while (MMC_TXNEXT_CHECK())  						/* Loop for transmission empty					*/
			{
				MMC_RSPI_TRX_TIMEOUT_CHK(RxWait , __LINE__);
			}
			/* Receive dummy data -> Transmission buffer register */
			MMC_TXNEXT_CLR();
			MMC_RSPI_DATASIZE_SET(T_RspiSpb[tran_size]);
			MMC_RSPI_SPDR  = RSPI_DUMMY_DATA;
			R_mmc_Rspi_Rx_Exchg(pData, RxData.ul, recv_size);
			pData += recv_size;
			recv_size = tran_size;
			RxCnt -= tran_size;
		}

		while (MMC_RXNEXT_CHECK())  							/* Loop for transmission empty					*/
		{
			MMC_RSPI_ORERR_CHK(__LINE__);
			MMC_RSPI_TRX_TIMEOUT_CHK(RxWait , __LINE__);
		}
		/* Receive data -> Receive data buffer */
		MMC_RXNEXT_CLR();										/* Receive completion flag clear				*/
		RxData.ul = MMC_RSPI_SPDR;								/* Receive data taking							*/
		R_mmc_Rspi_Rx_Exchg(pData, RxData.ul, recv_size);

		/* Final data transmission completion check */
		while (MMC_RSPI_TXEND != MMC_FALSE)  					/* Loop for transmission completion				*/
		{
			MMC_RSPI_TX_TIMEOUT_CHK(RxWait , __LINE__);
		}
	}

	/* Clear IR bit of IR register */
	MMC_RSPI_TRX_DI();								/* RSPI transmit&receive disable				*/

	return MMC_OK;
}

/******************************************************************************
* Declaration  : int16_t R_mmc_Sync_DataOut(uint8_t *pData)
* Function Name: R_mmc_Sync_DataOut
* Description  : Transmit data and CRC-CCITT for 1 block.
* Argument     : uint8_t *pData		; Send data buffer pointer
* Return Value : MMC_OK				; Success
*              : MMC_ERR_HARD		; Hardware Error
******************************************************************************/
int16_t R_mmc_Sync_DataOut(uint8_t *pData)
{
#if !defined(MMC_NOCHK_TIMEOUT)
	natural_uint_t			TxWait = MMC_RSPI_TX_WAIT;	/* Transmission waiting counter					*/
#endif	/* #if !defined(MMC_NOCHK_TIMEOUT) */
	uint8_t					*pCrcBuf;					/* Transmission CRC data buffer pointer			*/
	uint16_t				CrcBuf;						/* Transmission CRC data buffer					*/
	int16_t					Ret;
	uint8_t					work[4];					/* Transmission CRC data buffer					*/
#if defined(MMC_DTC_USED)
	uint8_t					*pDataEnd = pData + MMC_BLK_SIZE;
#else
	natural_uint_t			TxCnt;						/* Transmission byte counter					*/
	uint32_t				TxData;
#endif

	MMC_CRC_CLR();

#if defined(MMC_DTC_USED)
	MMC_DTC_EI();
	MMC_DTC_TX_EI(pData, MMC_BLK_SIZE, work);

	MMC_RSPI_DATASIZE_SET(T_RspiSpb[MMC_RSPI_TRAN_SIZE]);
	MMC_RSPI_TX_EI();											/* RSPI transmission enable						*/

	while (gDtcAlloc[MMC_DTC_ALLOC_CHK_IDX].CRA != 0) 						/* Loop for receive completion					*/
	{
		if (pData < pDataEnd)
		{
			MMC_CRC_SET(*pData++);							/* CRC-CCITT calculation						*/
		}
		MMC_RSPI_TRX_DTC_TIMEOUT_CHK(RxWait , __LINE__);
	}
	while (pData < pDataEnd)
	{
		MMC_CRC_SET(*pData++);							/* CRC-CCITT calculation						*/
	}

	/* Final data transmission completion check */
	while (MMC_RSPI_TXEND != MMC_FALSE)  					/* Loop for transmission completion				*/
	{
		MMC_RSPI_TX_TIMEOUT_CHK(TxWait , __LINE__);
	}

	MMC_RSPI_TX_DI();								/* RSPI transmit disable						*/
	MMC_DTC_TX_DI();
	MMC_DTC_DI();


#else	/* #if defined(MMC_DTC_USED) */
	TxCnt = MMC_BLK_SIZE;

	MMC_RSPI_TX_EI();											/* RSPI transmission enable						*/
	MMC_RSPI_DATASIZE_SET(T_RspiSpb[MMC_RSPI_TRAN_SIZE]);

	do
	{
		TxData = R_mmc_Rspi_Tx_Exchg(pData, MMC_RSPI_TRAN_SIZE);
		MMC_CRC_SET(*pData++);							/* CRC-CCITT calculation						*/
		MMC_CRC_SET(*pData++);							/* CRC-CCITT calculation						*/
		MMC_CRC_SET(*pData++);							/* CRC-CCITT calculation						*/
		MMC_CRC_SET(*pData++);							/* CRC-CCITT calculation						*/
		/* Transmission preparation completion check */
		while (MMC_TXNEXT_CHECK())  				/* Loop for transmission empty					*/
		{
			MMC_RSPI_TX_TIMEOUT_CHK(TxWait , __LINE__);
		}
		/* Transmission data -> Transmission buffer register */
		MMC_TXNEXT_CLR();						/* Transmission empty flag clear				*/
		MMC_RSPI_SPDR = TxData;						/* Transmission data setting					*/
		TxCnt -= MMC_RSPI_TRAN_SIZE;
	}
	while (TxCnt != 0);

	/* Transmission preparation completion check */
	while (MMC_TXNEXT_CHECK())  					/* Loop for transmission completion				*/
	{
		MMC_RSPI_TX_TIMEOUT_CHK(TxWait , __LINE__);
	}

	/* Final data transmission completion check */
	while (MMC_RSPI_TXEND != MMC_FALSE)  					/* Loop for transmission completion				*/
	{
		MMC_RSPI_TX_TIMEOUT_CHK(TxWait , __LINE__);
	}

	/* Clear IR bit of IR register */
	MMC_RSPI_TX_DI();											/* RSPI transmit disable						*/

#endif	/* #if defined(MMC_DTC_USED) */

	/* Calculation CRC-CCITT data acquisition */
	CrcBuf = R_ExchgCrc();

	/* CRC-CCITT data transmission */
	pCrcBuf = (uint8_t*) & CrcBuf;

	work[0] = *(pCrcBuf + 1);
	work[1] = *(pCrcBuf + 0);
	Ret = R_mmc_Sync_MultTx(MMC_CRC_SIZE, work);
	if (Ret < MMC_OK)
	{
		R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
		return Ret;
	}

	return MMC_OK;
}
/******************************************************************************
* Declaration  : int16_t R_mmc_Sync_DataIn(uint8_t *pData)
* Function Name: R_mmc_Sync_DataIn
* Description  : Receive data for the specified byte and CRC-CCITT, and check CRC-CCITT.
* Argument     : uint8_t 		*pData			; Recieve data storage buffer pointer
* Return Value : MMC_OK							; Success
*              : MMC_ERR_HARD					; Hardware Error
*              : MMC_ERR_CRC					; CRC check error
******************************************************************************/
int16_t R_mmc_Sync_DataIn(uint8_t *pData)
{
	natural_uint_t 		RxCnt = MMC_BLK_SIZE;
#if !defined(MMC_NOCHK_TIMEOUT)
	natural_uint_t		RxWait = MMC_RSPI_RX_WAIT;		/* Receive waiting counter						*/
#endif	/* #if !defined(MMC_NOCHK_TIMEOUT) */
	MMC_EXCHG_SHORT		CrcBuf;							/* Receive CRC-CCITT data buffer				*/
	uint16_t			CrcData;						/* Calculation CRC-CCITT data storage buffer	*/
	int16_t				Ret;
#if !defined(MMC_DTC_USED)
	MMC_EXCHG_LONG		RxData;
#endif /* #if !defined(MMC_DTC_USED) */
	uint8_t				work[MMC_CRC_SIZE];

	MMC_CRC_CLR();

#if defined(MMC_DTC_USED)
	MMC_DTC_EI();
	MMC_DTC_TRX_EI(pData  , RxCnt / MMC_RSPI_TRAN_SIZE);
	MMC_RSPI_DATASIZE_SET(T_RspiSpb[MMC_RSPI_TRAN_SIZE]);
	MMC_RSPI_TRX_EI();									/* RSPI transmit&receive enable					*/

	while (gDtcAlloc[1].CRA != 0) 						/* Loop for receive completion					*/
	{
		if ((uint32_t)pData < gDtcAlloc[1].DAR)
		{
			R_mmc_Rspi_Rx_Exchg(pData, *(uint32_t *)pData, MMC_RSPI_TRAN_SIZE);
			MMC_CRC_SET(*pData++);							/* CRC-CCITT calculation						*/
			MMC_CRC_SET(*pData++);							/* CRC-CCITT calculation						*/
			MMC_CRC_SET(*pData++);							/* CRC-CCITT calculation						*/
			MMC_CRC_SET(*pData++);							/* CRC-CCITT calculation						*/
		}
		if (MMC_RSPI_ORER == MMC_TRUE) 					/* Overrun error ?					*/
		{
			MMC_DTC_TRX_DI();							/* DTC stop							*/
			MMC_DTC_DI();								/* DTC disable						*/
			MMC_RSPI_TRX_DI();							/* RSPI transmit&receive disable	*/
			R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
			return MMC_ERR_HARD;
		}
		MMC_RSPI_TRX_DTC_TIMEOUT_CHK(RxWait , __LINE__);
	}
	while ((uint32_t)pData < gDtcAlloc[1].DAR)
	{
		R_mmc_Rspi_Rx_Exchg(pData, *(uint32_t *)pData, MMC_RSPI_TRAN_SIZE);
		MMC_CRC_SET(*pData++);							/* CRC-CCITT calculation						*/
		MMC_CRC_SET(*pData++);							/* CRC-CCITT calculation						*/
		MMC_CRC_SET(*pData++);							/* CRC-CCITT calculation						*/
		MMC_CRC_SET(*pData++);							/* CRC-CCITT calculation						*/
	}

	/* Final data transmission completion check */
	while (MMC_RSPI_TXEND != MMC_FALSE)  			/* Loop for transmission completion				*/
	{
		MMC_RSPI_TX_TIMEOUT_CHK(RxWait , __LINE__);
	}

	MMC_RSPI_TRX_DI();									/* RSPI transmit&receive disable				*/
	MMC_DTC_TRX_DI();
	MMC_DTC_DI();

#else /* #if defined(MMC_DTC_USED) */

	MMC_RSPI_TRX_EI();											/* RSPI transmit&receive enable					*/

	while (MMC_TXNEXT_CHECK())
	{
		MMC_RSPI_TRX_TIMEOUT_CHK(RxWait , __LINE__);
	}
	/* Receive dummy data -> Transmission buffer register */
	MMC_TXNEXT_CLR();
	MMC_RSPI_DATASIZE_SET(T_RspiSpb[MMC_RSPI_TRAN_SIZE]);
	MMC_RSPI_SPDR  = RSPI_DUMMY_DATA;
	RxCnt -= MMC_RSPI_TRAN_SIZE;

	while (RxCnt != 0)
	{
		while (MMC_RXNEXT_CHECK())
		{
			MMC_RSPI_ORERR_CHK(__LINE__);
			MMC_RSPI_TRX_TIMEOUT_CHK(RxWait , __LINE__);
		}
		/* Receive data -> Receive data buffer */
		MMC_RXNEXT_CLR();
		RxData.ul = MMC_RSPI_SPDR;

		while (MMC_TXNEXT_CHECK())
		{
			MMC_RSPI_TRX_TIMEOUT_CHK(RxWait , __LINE__);
		}
		/* Receive dummy data -> Transmission buffer register */
		MMC_TXNEXT_CLR();
		MMC_RSPI_SPDR  = RSPI_DUMMY_DATA;

		R_mmc_Rspi_Rx_Exchg(pData, RxData.ul, MMC_RSPI_TRAN_SIZE);
		MMC_CRC_SET(*pData++);							/* CRC-CCITT calculation						*/
		MMC_CRC_SET(*pData++);							/* CRC-CCITT calculation						*/
		MMC_CRC_SET(*pData++);							/* CRC-CCITT calculation						*/
		MMC_CRC_SET(*pData++);							/* CRC-CCITT calculation						*/
		RxCnt -= MMC_RSPI_TRAN_SIZE;
	}

	while (MMC_RXNEXT_CHECK())
	{
		MMC_RSPI_ORERR_CHK(__LINE__);
		MMC_RSPI_TRX_TIMEOUT_CHK(RxWait , __LINE__);
	}
	/* Receive data -> Receive data buffer */
	MMC_RXNEXT_CLR();
	RxData.ul = MMC_RSPI_SPDR;
	R_mmc_Rspi_Rx_Exchg(pData, RxData.ul, MMC_RSPI_TRAN_SIZE);
	MMC_CRC_SET(*pData++);							/* CRC-CCITT calculation						*/
	MMC_CRC_SET(*pData++);							/* CRC-CCITT calculation						*/
	MMC_CRC_SET(*pData++);							/* CRC-CCITT calculation						*/
	MMC_CRC_SET(*pData);							/* CRC-CCITT calculation						*/

	/* Final data transmission completion check */
	while (MMC_RSPI_TXEND != MMC_FALSE)  			/* Loop for transmission completion				*/
	{
		MMC_RSPI_TX_TIMEOUT_CHK(RxWait , __LINE__);
	}
	/* Clear IR bit of IR register */
	MMC_RSPI_TRX_DI();									/* RSPI transmit&receive disable				*/

#endif /* #if defined(MMC_DTC_USED) */

	/* Calculation CRC-CCITT data acquisition */
	CrcData = R_ExchgCrc();

	Ret = R_mmc_Sync_Rx(MMC_CRC_SIZE, work);
	if (Ret < MMC_OK)
	{
		R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
		return Ret;
	}

	CrcBuf.uc[1] = work[0];
	CrcBuf.uc[0] = work[1];

	/* CRC check */
	if (CrcData != CrcBuf.us)
	{
		R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
		return MMC_ERR_CRC;
	}

	return MMC_OK;

}

/******************************************************************************
* Declaration       : STATIC uint32_t R_mmc_Rspi_Tx_Exchg(uint8_t * pData, uint32_t Size)
* Function Name     : R_mmc_Rspi_Tx_Exchg
* Description       : Exchange the Tx data in byte order.
* Argument          : uint8_t *pData 	: pointer of Tx data
* Return Value      : uint32_t 			: Exchange data
******************************************************************************/
STATIC uint32_t R_mmc_Rspi_Tx_Exchg(uint8_t * pData, uint32_t Size)
{
	MMC_EXCHG_LONG		Tmp;

	Tmp.ul = 0;

#ifdef MTL_MCU_LITTLE
	if (Size == 4)
	{
		Tmp.uc[3] = *pData++;
		Tmp.uc[2] = *pData++;
		Tmp.uc[1] = *pData++;
		Tmp.uc[0] = *pData;
	}
	else if (Size == 3)
	{
		Tmp.uc[2] = *pData++;
		Tmp.uc[1] = *pData++;
		Tmp.uc[0] = *pData;
	}
	else if (Size == 2)
	{
		Tmp.uc[1] = *pData++;
		Tmp.uc[0] = *pData;
	}
	else if (Size == 1)
	{
		Tmp.uc[0] = *pData;
	}
	else
	{
		/* nothing to do */
	}
#else	/* #ifndef MTL_MCU_LITTLE */
	if (Size == 4)
	{
		Tmp.uc[0] = *pData++;
		Tmp.uc[1] = *pData++;
		Tmp.uc[2] = *pData++;
		Tmp.uc[3] = *pData;
	}
	else if (Size == 3)
	{
		Tmp.uc[1] = *pData++;
		Tmp.uc[2] = *pData++;
		Tmp.uc[3] = *pData;
	}
	else if (Size == 2)
	{
		Tmp.uc[2] = *pData++;
		Tmp.uc[3] = *pData;
	}
	else if (Size == 1)
	{
		Tmp.uc[3] = *pData;
	}
	else
	{
		/* nothing to do */
	}
#endif	/* #ifdef MTL_MCU_LITTLE */
	return Tmp.ul;

}

/******************************************************************************
* Declaration       : STATIC void R_mmc_Rspi_Rx_Exchg(uint8_t * pData, uint32_t Data, uint32_t Size)
* Function Name     : R_mmc_Rspi_Rx_Exchg
* Description       : Exchange the Rx data in byte order.
* Argument          : uint8_t *pData	: distination data pointer
					: uint32_t Data		: Rx data
					: uint32_t Size		: data size per Byte
* Return Value      : None
******************************************************************************/
STATIC void R_mmc_Rspi_Rx_Exchg(uint8_t * pData, uint32_t Data, uint32_t Size)
{
	MMC_EXCHG_LONG		Tmp;

	Tmp.ul = Data;

#ifdef MTL_MCU_LITTLE
	if (Size == 4)
	{
		*pData++ = Tmp.uc[3];
		*pData++ = Tmp.uc[2];
		*pData++ = Tmp.uc[1];
		*pData   = Tmp.uc[0];
	}
	else if (Size == 3)
	{
		*pData++ = Tmp.uc[2];
		*pData++ = Tmp.uc[1];
		*pData   = Tmp.uc[0];
	}
	else if (Size == 2)
	{
		*pData++ = Tmp.uc[1];
		*pData   = Tmp.uc[0];
	}
	else if (Size == 1)
	{
		*pData = Tmp.uc[0];
	}
	else
	{
		/* nothing to do */
	}
#else	/* #ifdef MTL_MCU_LITTLE */
	if (Size == 4)
	{
		*pData++ = Tmp.uc[0];
		*pData++ = Tmp.uc[1];
		*pData++ = Tmp.uc[2];
		*pData   = Tmp.uc[3];
	}
	else if (Size == 3)
	{
		*pData++ = Tmp.uc[1];
		*pData++ = Tmp.uc[2];
		*pData   = Tmp.uc[3];
	}
	else if (Size == 2)
	{
		*pData++ = Tmp.uc[2];
		*pData   = Tmp.uc[3];
	}
	else if (Size == 1)
	{
		*pData = Tmp.uc[3];
	}
	else
	{
		/* nothing to do */
	}
#endif	/* #ifdef MTL_MCU_LITTLE */

}

#endif /* #if defined(MMC_RSPI_USED) */