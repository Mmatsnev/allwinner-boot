/*
 * (C) Copyright 2012
 *     wangflord@allwinnerstech.com
 *
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program;
 *
 */
#include "include.h"
#include "axp221.h"

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
//int axp221_read_int_enable_status(__u8 *buffer)
//{
//	int   i;
//	__u8  int_reg = BOOT_POWER22_INTEN1;
//
//	for(i=0;i<3;i++)
//	{
//		if(axp_i2c_read(AXP22_ADDR, int_reg, buffer + i))
//	    {
//	        return -1;
//	    }
//	    int_reg ++;
//	}
//
//	return 0;
//}
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
//__s32 axp221_write_int_enable_status(__u8 *buffer)
//{
//	int   i;
//	__u8  int_reg = BOOT_POWER22_INTEN1;
//
//	for(i=0;i<3;i++)
//	{
//		if(axp_i2c_write(AXP22_ADDR, int_reg, buffer + i))
//	    {
//	        return -1;
//	    }
//	    int_reg ++;
//	}
//
//	return 0;
//}
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
__s32 standby_axp_int_query(__u8 *int_status)
{
	int   i, delay;
	__u8  int_reg = BOOT_POWER22_INTSTS1;

	for(i=0;i<3;i++)
	{
		for(delay = 0; delay <= 4000; delay++);
		if(standby_axp_i2c_read(AXP22_ADDR, int_reg, int_status + i))
	    {
	        return -1;
	    }
	    for(delay = 0; delay <= 4000; delay++);
	    if(standby_axp_i2c_write(AXP22_ADDR, int_reg, int_status[i]))
	    {
	        return -1;
	    }
	    int_reg ++;
	}

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
int standby_axp_probe_dcin_exist(void)
{
	u8 reg_value;

	if(standby_axp_i2c_read(AXP22_ADDR, BOOT_POWER22_STATUS, &reg_value))
    {
        return -1;
    }

    return (reg_value & 0x50);
}

