/******************************************************************************

* DISCLAIMER

* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized.

* This software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.

* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY,
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
* PARTICULAR PURPOSE AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY
* DISCLAIMED.

* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES
* FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS
* AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

* Renesas reserves the right, without notice, to make changes to this
* software and to discontinue the availability of this software.
* By using this software, you agree to the additional terms and
* conditions found by accessing the following link:
* http://www.renesas.com/disclaimer
******************************************************************************/

/* 	Copyright (C) 2010(2012) Renesas Electronics Corporation All rights reserved.  */

/*""FILE COMMENT""*******************************************************************
* File Name		: r_testmain.c
* Version      	: 1.01
* Device(s)    	: Renesas MCU
* Tool-Chain 	: -
* H/W Platform 	: -
* Description	: MMC driver sample program
*************************************************************************************
* History	: DD.MM.YYYY Version Description
* 			: 15.06.2010 1.00	 First Release
* 			: 03.02.2012 1.01
*""FILE COMMENT END""***************************************************************/
#if defined(__K0R__)
#pragma sfr
#pragma NOP
#endif
#include "r_stdint.h"
#include <string.h>
#include <stdlib.h>
#include "r_mtl_com.h"
#include "r_mmc.h"
#include "r_testmain.h"
#include "r_board.h"


/************************************************************************************************/
/*	Definitions																					*/
/************************************************************************************************/



/************************************************************************************************/
/*	Unions																						*/
/************************************************************************************************/


/************************************************************************************************/
/*	Structs																						*/
/************************************************************************************************/


/************************************************************************************************/
/*	Globals																						*/
/************************************************************************************************/
uint8_t 				gSendBuf[MMC_BLK_SIZE * MMC_TEST_BLKNO];
uint8_t 				gRecvBuf[MMC_BLK_SIZE * MMC_TEST_BLKNO];

uint8_t					gSlotNo = MMC_SLOT0;			/* Slot number									*/
uint32_t				gBlkNo[MMC_SLOT_NUM];			/* Block number									*/
MMC_INFO				gMmcInfo[MMC_SLOT_NUM];			/* MMC information								*/
uint32_t				gBtmBlkNo[MMC_SLOT_NUM];		/* Last block number							*/

uint16_t				gDetChatCnt[MMC_SLOT_NUM];		/* Counter of chattering detection				*/
uint16_t				gDetSts_Old[MMC_SLOT_NUM];		/* Previous status of detection					*/

uint32_t				gRnd_cnt;

/************************************************************************************************/
/*	Macros																						*/
/************************************************************************************************/


/************************************************************************************************/
/*	Prototypes																					*/
/************************************************************************************************/
static void 	R_sample_program_mmc_driver(void);
static void 	R_init_card_detect_chat(void);
static int16_t 	R_card_insertion_chk(uint8_t slotno);
static void 	R_wdata_set(uint32_t block_num, uint16_t block_cnt, uint8_t *pData);
static void 	R_error(uint32_t errflg , int16_t errid);


/*----------------------------------------------------------------------------------------------*/
/******************************************************************************
* Declaration  : void main(void)
* Description  : read and write to last 10 blocks
* Argument     : None
* Return Value : None
******************************************************************************/
void main(void)
{
	/* MMC driver_sample program					*/
	R_sample_program_mmc_driver();
}

/******************************************************************************
* Declaration  : void R_sample_program_mmc_driver(void)
* Description  : read and write to last 10 blocks
* Argument     : None
* Return Value : None
******************************************************************************/
static void R_sample_program_mmc_driver(void)
{
	uint16_t			byte_cnt;
	int16_t				ret_value;
	int8_t				led_brinkcnt;

	gRnd_cnt = 0;
	led_brinkcnt = 0;

	/* Initialize MMC driver.	*/
	R_mmc_Init_Driver();

	/* Initialize card detect chattering.	*/
	R_init_card_detect_chat();

	/* Check the MMC insertion. */
	do
	{
		R_mtl_wait_lp(MTL_T_1MS);
		gRnd_cnt++;
		if (++led_brinkcnt >= 0)
		{
			LED0_ON();
		}
		else
		{
			LED0_OFF();
		}
        
		ret_value = R_card_insertion_chk(gSlotNo);
		if (ret_value < MMC_OK)
		{
			R_error(1, ret_value);
		}
	}
	while (ret_value != MMC_TRUE);

	//LED0_ON();

	ret_value = R_mmc_Init_Slot(gSlotNo);
	if (ret_value < MMC_OK)
	{
		R_error(2, ret_value);
	}

	/* Get MMC information */
	ret_value = R_mmc_Get_MmcInfo(gSlotNo, &gMmcInfo[gSlotNo]);
	if (ret_value < MMC_OK)
	{
		R_error(3, ret_value);
	}

	gBtmBlkNo[gSlotNo] = gMmcInfo[gSlotNo].MaxBlkNum;

	gBlkNo[gSlotNo] = gBtmBlkNo[gSlotNo] - MMC_TEST_BLKNO;

	/* Set Write data . */
	R_wdata_set(gBlkNo[gSlotNo], MMC_TEST_BLKNO, gSendBuf);   //512x2

	/* Write data. */
	ret_value = R_mmc_Write_Data(gSlotNo, gBlkNo[gSlotNo], MMC_TEST_BLKNO, gSendBuf, MMC_MODE_NORMAL);
	if (ret_value < MMC_OK)
	{
		R_error(4, ret_value);
	}

	/* Read data. */
	ret_value = R_mmc_Read_Data(gSlotNo, gBlkNo[gSlotNo], MMC_TEST_BLKNO, gRecvBuf, MMC_MODE_NORMAL);
	if (ret_value < MMC_OK)
	{
		R_error(5, ret_value);
	}

	/* Compare data. */
	byte_cnt = MMC_TEST_BLKNO * MMC_BLK_SIZE;
	if (MEMCMP(gSendBuf, gRecvBuf, byte_cnt) != 0)
	{
		R_error(6, ret_value);
	}

	LED1_ON();

	/* Check the MMC removal. */
	do
	{
		R_mtl_wait_lp(MTL_T_1MS);
		if (++led_brinkcnt >= 0)
		{
			LED0_OFF();
		}
		else
		{
			LED0_ON();
		}

		ret_value = R_card_insertion_chk(gSlotNo);
		if (ret_value < MMC_OK)
		{
			R_error(7, ret_value);
		}
	}
	while (ret_value != MMC_FALSE);

	LED0_OFF();

	ret_value = R_mmc_Detach(gSlotNo);
	if (ret_value < MMC_OK)
	{
		R_error(8, ret_value);
	}

	/* Success */
	LED2_ON();
	while (1);
}

/******************************************************************************
* Declaration  : int16_t R_card_insertion_chk(gSlotNo)
* Function Name: R_card_insertion_chk
* Description  : Check whether a card is inserted.
               : After insertion confirmation, sample program initialize it for MMC
* Argument     : uint8_t gSlotNo: Slot No.
* Return Value : Library return value
******************************************************************************/
static int16_t R_card_insertion_chk(uint8_t slot_num)
{
	uint8_t				DetSts;							/* Detection status								*/
	int16_t				api_ret;

	/* Check MMC insertion. */
	api_ret = R_mmc_Chk_Detect(slot_num, &DetSts);	/* Get status of MMC insertion.					*/
	if (api_ret < MMC_OK)
	{
		return api_ret;
	}
	if (DetSts != gDetSts_Old[slot_num])			/* Status Changed!								*/
	{
		if (DetSts == MMC_TRUE)						/* Removal -> Insertion							*/
		{
			gDetChatCnt[slot_num]--;				/* Chattering counter decrement					*/
			if (gDetChatCnt[slot_num] == 0)			/* counter =0 									*/
			{
				gDetChatCnt[slot_num] = MMC_INS_CHAT;
				gDetSts_Old[slot_num] = DetSts;
				/* Initialize MMC slot. */
			}
		}
		else
		{
			/* Insertion -> Removal							*/
			/* Do not care chattering. */
			gDetChatCnt[slot_num] = MMC_INS_CHAT;
			gDetSts_Old[slot_num] = DetSts;
		}
	}
	else
	{
		/* No change									*/
		gDetChatCnt[slot_num] = MMC_INS_CHAT;
	}
	return gDetSts_Old[slot_num];
}


/******************************************************************************
* Declaration  : void R_init_card_detect_chat(void)
* Function Name: R_init_card_detect_chat
* Description  : clear of the chattering counter
* Argument     : None
* Return Value : None
******************************************************************************/
static void R_init_card_detect_chat(void)	/* Initial process																	*/
{
	uint8_t				slot_num;							/* Slot number									*/

	for (slot_num = MMC_SLOT0; slot_num < MMC_SLOT_NUM; slot_num++)
	{
		gDetChatCnt[slot_num] = MMC_INS_CHAT;			/* Reset the counter of chattering detection.	*/
		gDetSts_Old[slot_num] = MMC_FALSE;				/* Set the previous status of detection	to "removal".	*/
	}
}


/*----------------------------------------------------------------------------------------------*/
/******************************************************************************
* Declaration  : void R_wdata_set(uint32_t block_num, uint16_t block_cnt, uint8_t *pData)
* Function Name: R_wdata_set
* Description  : stores a random letter in a buffer
* Argument     : uint32_t block_num  :  Block No
*              : uint16_t block_cnt  :  Block Length
*              : uint8_t *pData 	 :  The buffer pointer that a random data is stored
* Return Value : None
******************************************************************************/
static void R_wdata_set(uint32_t block_num, uint16_t block_cnt, uint8_t *pData)	/* Edit data for writing.				*/
{
	uint32_t				i;
	uint32_t				byte_cnt;

	byte_cnt = block_cnt * MMC_BLK_SIZE;
	srand((unsigned int)gRnd_cnt);
	for (i = 0; i < byte_cnt; i++)
	{
		*(pData + i) = (uint8_t)rand();
	}
}

/******************************************************************************
* Declaration  : void R_error(uint32_t errflg)
* Function Name: R_error
* Description  : When Sample program detected an error, This function are called
* Argument     : Error code
* Return Value : None
******************************************************************************/
static void R_error(uint32_t errflg , int16_t errid)
{
	LED3_ON();
	switch (errflg)
	{
		case 1:
			/* R_card_insertion_chk (attach) Error */
			while (1);
			break;
		case 2:
			/*  R_mmc_Init_Slot func error. */
			while (1);
			break;
		case 3:
			/*  R_mmc_Get_MmcInfo func error. */
			while (1);
			break;
		case 4:
			/*  R_mmc_Write_Data func error. */
			while (1);
			break;
		case 5:
			/*  R_mmc_Read_Data func error. */
			while (1);
			break;
		case 6:
			/*  Data Compare error. */
			while (1);
			break;
		case 7:
			/*  R_mmc_Chk_Detect (Detach) Error */
			while (1);
			break;
		case 8:
			/* Detach Func Error */
			while (1);
			break;
		default:
			while (1);
			break;
	}
}
