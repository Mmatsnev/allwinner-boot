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
#include "axp.h"
#include "axp221.h"

int power_step_level = 1;
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
int axp_probe(void)
{
	u8    pmu_type;

	if(axp_i2c_read(AXP20_ADDR, BOOT_POWER20_VERSION, &pmu_type))
	{
		eGon2_printf("axp read error\n");

		return -1;
	}
	pmu_type &= 0x0f;
	if(pmu_type & 0x06)
	{
		/* pmu type AXP221 */
		eGon2_printf("PMU: AXP221\n");

		return 0;
	}

	eGon2_printf("PMU: NULL\n");

	return -1;
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
int power_init(int set_vol)
{
	int ret = -1;

	//set_vol = uboot_spare_head.boot_data.run_core_vol;
	//set_clock = uboot_spare_head.boot_data.run_clock;
	if(!set_vol)
	{
		set_vol = 1400;
	}
	if(!axp_probe())
	{
		if(!axp_probe_power_supply_condition())
		{
			if(!axp_set_dcdc2(set_vol))
			{
				eGon2_printf("axp_set_dcdc2 ok\n");
				ret = 0;
			}
			else
			{
				eGon2_printf("axp_set_dcdc2 fail\n");
			}
		}
		else
		{
			eGon2_printf("axp_probe_power_supply_condition error\n");
		}
	}
	else
	{
		eGon2_printf("axp_probe error\n");
	}

	return ret;
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
int axp_probe_power_supply_condition(void)
{
	int   dcin_exist, bat_vol;
	//int   buffer_value;
	//char  bat_value, bat_cou;
	int   ratio;

	//检测电压，决定是否开机
    dcin_exist = axp221_probe_dcin_exist();
    eGon2_printf("dcin_exist = %d\n", dcin_exist);
    //先判断条件，如果上次关机记录的电量百分比<=5%,同时库仑计值小于5mAh，则关机，否则继续判断
    bat_vol = axp221_probe_battery_vol();
	eGon2_printf("bat vol = %d\n", bat_vol);
	if((bat_vol < 3400) && (!dcin_exist))
	{
	    axp_set_hardware_poweroff_vol();
		axp221_set_power_off();
		for(;;);
	}
	//读之前的记录百分比
	//buffer_value = axp221_probe_buttery_resistance_record();
	//if(buffer_value < 0)
	//{
	//	eGon2_printf("axp read error\n");
	//	return -1;
	//}
	ratio = axp221_probe_battery_ratio();
	if(ratio < 0)
	{
		return -1;
	}
	else if(ratio <= 1)
	{
		power_step_level = 2;
	}
	else
	{
		power_step_level = 3;
	}
#if 0
	if(buffer_value & 0x80)
	{
		bat_value = buffer_value & 0x7f;
		bat_cou = axp221_probe_bat_coulomb_count();
		if((bat_value <= 0) && (bat_cou < 30))
		{
			eGon2_printf("bat_cou=%x\n", bat_cou);
		}
		if(dcin_exist)
		{
			if(bat_vol > (3600 + 100))
			{
				axp221_clear_data_buffer();
				power_step_level = 2;
			}
			else
			{
				power_step_level = 3;
			}
		}
		else
		{
			if(bat_vol > 3600)
			{
				axp221_clear_data_buffer();
				power_step_level = 3;
			}
			else
			{
				power_step_level = 1;
			}
		}
	}
	else
	{
		if(dcin_exist)
		{
			power_step_level = 2;
		}
		else
		{
			if(bat_vol >= 3600)
			{
				power_step_level = 3;
			}
			else
			{
				power_step_level = 1;
			}
		}
	}
#endif
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
int axp_get_power_vol_level(void)
{
	return power_step_level;
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
int axp_probe_startup_cause(void)
{
	int buffer_value;
	int poweron_reason, next_action;
	int ret;

	buffer_value = axp221_probe_last_poweron_status();
	if(buffer_value < 0)
	{
		return -1;
	}
    if(buffer_value == 0x0e)		//表示前一次是在系统状态，下一次应该也进入系统
    {
    	eGon2_printf("pre sys mode\n");
    	return -1;
    }
    else if(buffer_value == 0x0f)      //表示前一次是在boot standby状态，下一次也应该进入boot standby
	{
		eGon2_printf("pre boot mode\n");
		return 0;
	}
	//获取 开机原因，是按键触发，或者插入电压触发
	poweron_reason = axp221_probe_poweron_cause();
	next_action = 0x0e;
	ret         = 1;
	if(poweron_reason == AXP_POWER_ON_BY_POWER_KEY)
	{
		next_action = 0x0e;
		ret = 1;
	}
	else if(poweron_reason == AXP_POWER_ON_BY_POWER_TRIGGER)
	{
		eGon2_printf("power trigger\n");
		next_action = 0x0f;
    	ret = 0;
	}
	//把开机原因写入寄存器
	axp221_set_next_poweron_status(next_action);

    return ret;
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
int axp_set_hardware_poweron_vol(void) //设置开机之后，PMU硬件关机电压为2.9V
{
	int vol_value;

	if(eGon2_script_parser_fetch("pmu_para", "pmu_pwron_vol", &vol_value, 1))
	{
		eGon2_printf("boot power:unable to find power off vol set\n");
		vol_value = 2900;
	}
	return axp221_set_poweroff_vol(vol_value);
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
int axp_set_hardware_poweroff_vol(void) //设置关机之后，PMU硬件下次开机电压为3.3V
{
	int vol_value;

	if(eGon2_script_parser_fetch("pmu_para", "pmu_pwroff_vol", &vol_value, 1))
	{
		eGon2_printf("boot power:unable to find power off vol set\n");
		vol_value = 3300;
	}
	return axp221_set_poweroff_vol(vol_value);
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
int  axp_set_power_off(void)
{
	return axp221_set_power_off();
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
int axp_set_next_poweron_status(int value)
{
	return axp221_set_next_poweron_status(value);
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
int  axp_power_get_dcin_battery_exist(__u32 *dcin_exist, __u32 *battery_exist)
{
	*dcin_exist = axp221_probe_dcin_exist();
	*battery_exist = axp221_probe_battery_exist();

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
int  axp_probe_battery_vol(void)
{
	return axp221_probe_battery_vol();
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
int  axp_probe_rest_battery_capacity(void)
{
	return axp221_probe_battery_ratio();
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
int  axp_probe_key(void)
{
	return axp221_probe_key();
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
int axp_set_power_supply_output(void)
{
	int vol_value;

	//set dcdc3
	if(!eGon2_script_parser_fetch("target", "dcdc3_vol", &vol_value, 1))
	{
		axp_set_dcdc3(vol_value);
	}
	else
	{
		eGon2_printf("boot power:unable to find dcdc3 set\n");
	}
	//set dcdc4
	if(!eGon2_script_parser_fetch("target", "dcdc4_vol", &vol_value, 1))
	{
		axp_set_dcdc4(vol_value);
	}
	else
	{
		eGon2_printf("boot power:unable to find dcdc4 set\n");
	}
    //set dcdc5
	if(!eGon2_script_parser_fetch("target", "dcdc5_vol", &vol_value, 1))
	{
		axp221_set_dcdc5(vol_value);
	}
	else
	{
		eGon2_printf("boot power:unable to find dcdc5 set\n");
	}
	//set ldo2
	if(!eGon2_script_parser_fetch("target", "ldo2_vol", &vol_value, 1))
	{
		axp_set_ldo2(vol_value);
	}
	else
	{
		eGon2_printf("boot power:unable to find ldo2 set\n");
	}
	//set ldo3
	if(!eGon2_script_parser_fetch("target", "ldo3_vol", &vol_value, 1))
	{
		axp_set_ldo3(vol_value);
	}
	else
	{
		eGon2_printf("boot power:unable to find ldo3 set\n");
	}
	//set ldo4
//	if(!eGon2_script_parser_fetch("target", "ldo4_vol", &vol_value, 1))
//	{
//		axp_set_ldo4(vol_value);
//	}
//	else
//	{
//		eGon2_printf("boot power:unable to find ldo4 set\n");
//	}
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
int  axp_set_dcdc2(int set_vol)
{
	return axp221_set_dcdc2(set_vol);
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
int  axp_set_dcdc3(int set_vol)
{
	return axp221_set_dcdc3(set_vol);
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
int  axp_set_dcdc4(int set_vol)
{
	return axp221_set_dcdc4(set_vol);
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

int  axp_set_ldo2(int set_vol)
{
	return axp221_set_ldo2(set_vol);
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
int  axp_set_ldo3(int set_vol)
{
	return axp221_set_ldo3(set_vol);
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
int  axp_set_ldo4(int set_vol)
{
	return axp221_set_ldo4(set_vol);
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
int  axp_probe_charge_current(void)
{
	return axp221_probe_charge_current();
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
int  axp_set_charge_current(int current)
{
	return axp221_set_charge_current(current);
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
int  axp_set_charge_control(void)
{
	return axp221_set_charge_control();
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
int  axp_set_vbus_cur_limit(int current)
{
	return axp221_set_vbus_cur_limit(current);
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
int  axp_set_vbus_vol_limit(int vol)
{
	return axp221_set_vbus_vol_limit(vol);
}

