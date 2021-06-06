/*""FILE COMMENT""*******************************************************************
* File Name		: r_testmain.h
* Version      	: 1.01
* Device(s)    	: Renesas MCU
* Tool-Chain 	: -
* H/W Platform 	: -
* Description	: MMC driver sample program header file.
*************************************************************************************
* History	: DD.MM.YYYY Version Description
* 			: 15.06.2010 1.00	 First Release
* 			: 02.03.2012 1.01
*""FILE COMMENT END""***************************************************************/
#ifndef __TESTMAIN_H__
#define __TESTMAIN_H__

/******************************************************************************
Macro definitions
******************************************************************************/
#define MMC_INS_CHAT			20						/* counter value of chattering detection		*/
#define MMC_TEST_BLKNO			2						/* number of blocks for test					*/


#if 1
/* Use a standard library. */
#include <string.h>
#define MEMCMP(S1, S2, N)					memcmp((const void *)(S1), (const void *)(S2), (size_t)(N))
#define MEMMOVE(S1, S2, N)					memmove((S1), (S2), (N))
#define MEMCPY(S1, S2, N)					memcpy((S1), (S2), (N))
#define MEMSET(S, C, N)						memset((S), (C), (N))
#define STRCAT(S1, S2)						strcat((S1), (S2))
#define STRCMP(S1, S2)						strcmp((S1), (S2))
#define STRCPY(S1, S2)						strcpy((S1), (S2))
#define STRLEN(S)							strlen((S))
#else
/* Use processing of r_mtl_mem.c ,r_mtl_str.c. */
#define MEMCMP(S1, S2, N)					R_mtl_memcmp((S1), (S2), (N))
#define MEMMOVE(S1, S2, N)					R_mtl_memmove((S1), (S2), (N))
#define MEMCPY(S1, S2, N)					R_mtl_memcpy((S1), (S2), (N))
#define MEMSET(S, C, N)						R_mtl_memset((S), (C), (N))
#define STRCAT(S1, S2)						R_mtl_strcat((S1), (S2))
#define STRCMP(S1, S2)						R_mtl_strcmp((S1), (S2))
#define STRCPY(S1, S2)						R_mtl_strcpy((S1), (S2))
#define STRLEN(S)							R_mtl_strlen((S))
#endif

#endif	/* __TESTMAIN_H__ */
