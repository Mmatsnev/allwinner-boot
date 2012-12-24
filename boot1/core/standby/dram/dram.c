/*
*********************************************************************************************************
*                                                AR100 SYSTEM
*                                     AR100 Software System Develop Kits
*                                              	 dram module
*
*                                    (c) Copyright 2012-2016, Sunny China
*                                             All Rights Reserved
*
* File    : dram.c
* By      : Sunny
* Version : v1.0
* Date    : 2012-5-22
* Descript: dram driver.
* Update  : date                auther      ver     notes
*           2012-5-22 18:24:02	Sunny       1.0     Create this file.
*********************************************************************************************************
*/

#include "dram_i.h"

int dram_power_save_process(void)
{
	mctl_deep_sleep_entry();

	return 0;
}

int dram_power_up_process(void)
{
	__dram_para_t  *dram_parameters = (__dram_para_t *)BOOT_STANDBY_DRAM_PARA_ADDR;

	mctl_deep_sleep_exit(dram_parameters);

	return 0;
}

int dram_enter_self_refresh(void)
{
	mctl_self_refresh_entry(0);
	if(mctl_read_w(SDR_COM_CR) & (0x1<<19))
	{
		mctl_self_refresh_entry(1);
	}

	return 0;
}

int dram_exit_self_refresh(void)
{
	mctl_self_refresh_exit(0);
	if(mctl_read_w(SDR_COM_CR) & (0x1<<19))
	{
		mctl_self_refresh_exit(1);
	}

	return 0;
}
