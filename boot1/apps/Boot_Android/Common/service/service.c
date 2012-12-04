/*
**********************************************************************************************************************
*											        eGon
*						           the Embedded GO-ON Bootloader System
*									       eGON arm boot sub-system
*
*						  Copyright(C), 2006-2010, SoftWinners Microelectronic Co., Ltd.
*                                           All Rights Reserved
*
* File    :
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
#include "types.h"

int usbvol_limit = 0;
int usbcur_limit = 0;
int usbpc_cur = 0, usbpc_vol = 4400;
int usbdc_cur = 0, usbdc_vol = 4400;

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
int power_set_limit(void)
{
	return (usbvol_limit && usbcur_limit);
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
int power_set_init(void)
{
	wBoot_script_parser_fetch("pmu_para", "pmu_usbvol_limit", &usbvol_limit, 1);
	wBoot_script_parser_fetch("pmu_para", "pmu_usbcur_limit", &usbcur_limit, 1);
	wBoot_script_parser_fetch("pmu_para", "pmu_usbvol", &usbdc_vol, 1);
	wBoot_script_parser_fetch("pmu_para", "pmu_usbcur", &usbdc_cur, 1);
	wBoot_script_parser_fetch("pmu_para", "pmu_usbvol_pc", &usbpc_vol, 1);
	wBoot_script_parser_fetch("pmu_para", "pmu_usbcur_pc", &usbpc_cur, 1);
	__inf("pmu_usbvol_limit = %d, pmu_usbcur_limit = %d\n", usbvol_limit, usbcur_limit);
	__inf("usbdc_vol = %d, usbdc_cur = %d\n", usbdc_vol, usbdc_cur);
	__inf("usbpc_vol = %d, usbpc_cur = %d\n", usbpc_vol, usbpc_cur);

	return 0;
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
void power_set_usbpc(void)
{
	__inf("set pc\n");
	if(usbvol_limit)
	{
		wBoot_power_vol_limit(usbpc_vol);
	}
	if(usbcur_limit)
	{
		wBoot_power_cur_limit(usbpc_cur);
	}
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
void power_set_usbdc(void)
{
	__inf("set pc\n");
	if(usbvol_limit)
	{
		wBoot_power_vol_limit(usbdc_vol);
	}
	if(usbcur_limit)
	{
		wBoot_power_cur_limit(usbdc_cur);
	}
}
