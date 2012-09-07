/*
**********************************************************************************************************************
*											        eGon
*						                     the Embedded System
*									       script parser sub-system
*
*						  Copyright(C), 2006-2010, SoftWinners Microelectronic Co., Ltd.
*                                           All Rights Reserved
*
* File    : standby.c
*
* By      : Jerry
*
* Version : V2.00
*
* Date	  :
*
* Descript:
**********************************************************************************************************************
*/
#include "include.h"
#include "standby.h"
#include "dram_i.h"

/*
************************************************************************************************************
*
*                                             function
*
*    函数名称：
*
*    参数列表：
*
*    返回值  ：
*
*    说明    ：
*
*
************************************************************************************************************
*/
void mctl_self_refresh_entry(__u32 channel_num)
{
	__u32 reg_val;
	__u32 ch_id;

	if(channel_num == 1)
		ch_id = 0x1000;
	else
		ch_id = 0x0;
	//set SLEEP command
	reg_val = 0x3;
	mctl_write_w(ch_id + SDR_SCTL, reg_val);

	//check whether in Low Power State
	while(  (mctl_read_w(ch_id + SDR_SSTAT)&0x7) != 0x5 ) {};
}
/*
************************************************************************************************************
*
*                                             function
*
*    函数名称：
*
*    参数列表：
*
*    返回值  ：
*
*    说明    ：
*
*
************************************************************************************************************
*/
void mctl_self_refresh_exit(__u32 channel_num)
{
	__u32 reg_val;
	__u32 ch_id;

	if(channel_num == 1)
		ch_id = 0x1000;
	else
		ch_id = 0x0;
	//set SLEEP command
	reg_val = 0x4;
	mctl_write_w(ch_id + SDR_SCTL, reg_val);

	//check whether in Low Power State
	while(  (mctl_read_w(ch_id + SDR_SSTAT)&0x7) != 0x3 ) {};
}
