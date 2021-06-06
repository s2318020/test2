/*""FILE COMMENT""*******************************************************************
* File Name		: r_mtl_tim.h
* Version      	: 4.05R00B
* Device(s)    	: Renesas MCU
* Tool-Chain 	: -
* H/W Platform 	: -
* Description	: Common header file
*************************************************************************************
* History	: DD.MM.YYYY Version Description
*			: 28.01.2003 1.00R01 First Release
*			: 02.12.2003 2.00R01
*			: 03.03.2004 2.00R02
*			: 02.12.2004 3.00R01
*			: 20.06.2006 3.10R01
*			: 15.09.2006 4.00R01
*			: 19.01.2007 4.01R00
*			: 06.02.2007 4.02R00
*			: 31.10.2007 4.03R00
*			: 22.06.2010 4.05R00
* 			: 25.06.2010 4.05R00A
* 			: 02.03.2012 4.05R00B
*""FILE COMMENT END""***************************************************************/
#ifndef	__MTL_TIM_H__
#define	__MTL_TIM_H__
/*==============================================================================================*/

/*	Define the counter value for the timer.														*/
/*	Specify according to the user MCU, clock and wait requirements.								*/
/*																								*/

/*	Set the reference value to 10% more than the actual calculated value.						*/
/*==============================================================================================*/

/*==============================================================================================*/
#ifdef MTL_TIM_RX600__12_5MHz_noWait_Ix8
/*	Setting for 12.5MHz no wait Ix8 = 100MHz(Compile Option "-optimize=2 -size")*/
#define MTL_T_250NS								   5		/* loop Number of 250ns				*/	/** SET **/
#define MTL_T_500NS								  11		/* loop Number of 500ns				*/	/** SET **/
#define MTL_T_1US								  24		/* loop Number of   1us				*/	/** SET **/
#define MTL_T_2US								  49		/* loop Number of   2us				*/	/** SET **/
#define MTL_T_4US								  99		/* loop Number of   4us				*/	/** SET **/
#define MTL_T_5US								 124		/* loop Number of   5us				*/	/** SET **/
#define MTL_T_10US								 249		/* loop Number of  10us				*/	/** SET **/
#define MTL_T_20US								 499		/* loop Number of  20us				*/	/** SET **/
#define MTL_T_30US								 749		/* loop Number of  30us				*/	/** SET **/
#define MTL_T_50US								1249		/* loop Number of  50us				*/	/** SET **/
#define MTL_T_100US								2499		/* loop Number of 100us				*/	/** SET **/
#define MTL_T_200US								4999		/* loop Number of 200us				*/	/** SET **/
#define MTL_T_300US								7499		/* loop Number of 300us				*/	/** SET **/
#define MTL_T_400US							    9999		/* loop Number of 400us				*/	/** SET **/
#define MTL_T_1MS							   24999		/* loop Number of   1ms				*/	/** SET **/
#endif

#ifdef MTL_TIM_RX600__12_0MHz_noWait_Ix8
/*	Setting for 12.0MHz no wait Ix8 = 96MHz(Compile Option "-optimize=2 -size")*/
#define MTL_T_250NS								   5		/* loop Number of 250ns				*/	/** SET **/
#define MTL_T_500NS								  11		/* loop Number of 500ns				*/	/** SET **/
#define MTL_T_1US								  23		/* loop Number of   1us				*/	/** SET **/
#define MTL_T_2US								  47		/* loop Number of   2us				*/	/** SET **/
#define MTL_T_4US								  95		/* loop Number of   4us				*/	/** SET **/
#define MTL_T_5US								 119		/* loop Number of   5us				*/	/** SET **/
#define MTL_T_10US								 239		/* loop Number of  10us				*/	/** SET **/
#define MTL_T_20US								 479		/* loop Number of  20us				*/	/** SET **/
#define MTL_T_30US								 719		/* loop Number of  30us				*/	/** SET **/
#define MTL_T_50US								1199		/* loop Number of  50us				*/	/** SET **/
#define MTL_T_100US								2399		/* loop Number of 100us				*/	/** SET **/
#define MTL_T_200US								4799		/* loop Number of 200us				*/	/** SET **/
#define MTL_T_300US								7199		/* loop Number of 300us				*/	/** SET **/
#define MTL_T_400US							    9599		/* loop Number of 400us				*/	/** SET **/
#define MTL_T_1MS							   23999		/* loop Number of   1ms				*/	/** SET **/
#endif

#ifdef MTL_TIM_RX200__50_0MHz_noWait
/*	Setting for 50.0MHz no wait (Compile Option "-optimize=2 -size")*/
#define MTL_T_250NS								   2		/* loop Number of 250ns				*/	/** SET **/
#define MTL_T_500NS								   5		/* loop Number of 500ns				*/	/** SET **/
#define MTL_T_1US								  11		/* loop Number of   1us				*/	/** SET **/
#define MTL_T_2US								  24		/* loop Number of   2us				*/	/** SET **/
#define MTL_T_4US								  49		/* loop Number of   4us				*/	/** SET **/
#define MTL_T_5US								  61		/* loop Number of   5us				*/	/** SET **/
#define MTL_T_10US								 124		/* loop Number of  10us				*/	/** SET **/
#define MTL_T_20US								 249		/* loop Number of  20us				*/	/** SET **/
#define MTL_T_30US								 374		/* loop Number of  30us				*/	/** SET **/
#define MTL_T_50US								 624		/* loop Number of  50us				*/	/** SET **/
#define MTL_T_100US								1249		/* loop Number of 100us				*/	/** SET **/
#define MTL_T_200US								2499		/* loop Number of 200us				*/	/** SET **/
#define MTL_T_300US								3749		/* loop Number of 300us				*/	/** SET **/
#define MTL_T_400US							    4999		/* loop Number of 400us				*/	/** SET **/
#define MTL_T_1MS							   12499		/* loop Number of   1ms				*/	/** SET **/
#endif

#ifdef MTL_TIM_RL78__32MHz_noWait
/*	Setting for 32.0MHz no wait */
#define MTL_T_1US								   3		/* loop Number of   1us				*/	/** SET **/
#define MTL_T_2US								   8		/* loop Number of   2us				*/	/** SET **/
#define MTL_T_4US								  17		/* loop Number of   4us				*/	/** SET **/
#define MTL_T_5US								  21		/* loop Number of   5us				*/	/** SET **/
#define MTL_T_10US								  44 		/* loop Number of  10us				*/	/** SET **/
#define MTL_T_20US								  90		/* loop Number of  20us				*/	/** SET **/
#define MTL_T_30US								 136		/* loop Number of  30us				*/	/** SET **/
#define MTL_T_50US								 227		/* loop Number of  50us				*/	/** SET **/
#define MTL_T_100US								 456 		/* loop Number of 100us				*/	/** SET **/
#define MTL_T_200US								 913		/* loop Number of 200us				*/	/** SET **/
#define MTL_T_300US								1370 		/* loop Number of 300us				*/	/** SET **/
#define MTL_T_400US							    1827 		/* loop Number of 400us				*/	/** SET **/
#define MTL_T_1MS							 	4572 		/* loop Number of   1ms				*/	/** SET **/
#endif

#ifdef MTL_TIM_RL78__24MHz_noWait
/*	Setting for 24.0MHz no wait */
#define MTL_T_1US								   2		/* loop Number of   1us				*/	/** SET **/
#define MTL_T_2US								   5		/* loop Number of   2us				*/	/** SET **/
#define MTL_T_4US								  12		/* loop Number of   4us				*/	/** SET **/
#define MTL_T_5US								  16		/* loop Number of   5us				*/	/** SET **/
#define MTL_T_10US								  33 		/* loop Number of  10us				*/	/** SET **/
#define MTL_T_20US								  67		/* loop Number of  20us				*/	/** SET **/
#define MTL_T_30US								 101		/* loop Number of  30us				*/	/** SET **/
#define MTL_T_50US								 170		/* loop Number of  50us				*/	/** SET **/
#define MTL_T_100US								 341 		/* loop Number of 100us				*/	/** SET **/
#define MTL_T_200US								 684		/* loop Number of 200us				*/	/** SET **/
#define MTL_T_300US								1027 		/* loop Number of 300us				*/	/** SET **/
#define MTL_T_400US							    1370 		/* loop Number of 400us				*/	/** SET **/
#define MTL_T_1MS							   	3428 		/* loop Number of   1ms				*/	/** SET **/
#endif

#ifdef MTL_TIM_RL78__20MHz_noWait
/*	Setting for 20.0MHz no wait */
#define MTL_T_1US								   1		/* loop Number of   1us				*/	/** SET **/
#define MTL_T_2US								   4		/* loop Number of   2us				*/	/** SET **/
#define MTL_T_4US								  10		/* loop Number of   4us				*/	/** SET **/
#define MTL_T_5US								  13		/* loop Number of   5us				*/	/** SET **/
#define MTL_T_10US								  27		/* loop Number of  10us				*/	/** SET **/
#define MTL_T_20US								  56		/* loop Number of  20us				*/	/** SET **/
#define MTL_T_30US								  84		/* loop Number of  30us				*/	/** SET **/
#define MTL_T_50US								 141		/* loop Number of  50us				*/	/** SET **/
#define MTL_T_100US								 284		/* loop Number of 100us				*/	/** SET **/
#define MTL_T_200US								 570		/* loop Number of 200us				*/	/** SET **/
#define MTL_T_300US								 856		/* loop Number of 300us				*/	/** SET **/
#define MTL_T_400US							    1141		/* loop Number of 400us				*/	/** SET **/
#define MTL_T_1MS							   	2856		/* loop Number of   1ms				*/	/** SET **/
#endif

/*==============================================================================================*/
#ifdef MTL_TIM_McuType__Clock_Settings
/*	Setting for xxxxxx																			*/
#endif

/*==============================================================================================*/
#endif	/* #ifndef	__MTL_TIM_H__ */

