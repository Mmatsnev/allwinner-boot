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


static  __u32  pll1_value = 0;
static  __u32  pll2_value = 0;
static  __u32  pll3_value = 0;
static  __u32  pll4_value = 0;
static  __u32  pll5_value = 0;
static  __u32  pll6_value = 0;
static  __u32  pll7_value = 0;
static  __u32  pll8_value = 0;
static  __u32  pll9_value = 0;
static  __u32  pll10_value = 0;

__s32 standby_clock_store(void)
{
	pll1_value  = CCMU_REG_PLL1_CTRL;
	pll2_value  = CCMU_REG_PLL2_CTRL;
	pll3_value  = CCMU_REG_PLL3_CTRL;
	pll4_value  = CCMU_REG_PLL4_CTRL;
	pll5_value  = CCMU_REG_PLL5_CTRL;
	pll6_value  = CCMU_REG_PLL6_CTRL;
	pll7_value  = CCMU_REG_PLL7_CTRL;
	pll8_value  = CCMU_REG_PLL8_CTRL;
	pll9_value  = CCMU_REG_PLL9_CTRL;
	pll10_value = CCMU_REG_PLL10_CTRL;

	return 0;
}


__s32 standby_clock_restore(void)
{
	CCMU_REG_PLL1_CTRL  = pll1_value;
	CCMU_REG_PLL2_CTRL  = pll2_value;
	CCMU_REG_PLL3_CTRL  = pll3_value;
	CCMU_REG_PLL4_CTRL  = pll4_value;
	CCMU_REG_PLL5_CTRL  = pll5_value;
	CCMU_REG_PLL6_CTRL  = pll6_value;
	CCMU_REG_PLL7_CTRL  = pll7_value;
	CCMU_REG_PLL8_CTRL  = pll8_value;
	CCMU_REG_PLL9_CTRL  = pll9_value;
	CCMU_REG_PLL10_CTRL = pll10_value;

	return 0;
}

__s32 standby_clock_to_source(int clock_source)
{
	__u32 reg_val;

	reg_val = CCMU_REG_AXI_MOD;
	reg_val &= ~(0x03 << 16);
	if(clock_source == 32000)
	{
		;
	}
	else if(clock_source == 24000000)
	{
		reg_val |= 1 << 16;
	}
	else
	{
		reg_val |= 2 << 16;
	}
	CCMU_REG_AXI_MOD = reg_val;

	return 0;
}

void standby_clock_plldisable(void)
{
	CCMU_REG_PLL1_CTRL &= ~(1U << 31);
	CCMU_REG_PLL2_CTRL &= ~(1U << 31);
	CCMU_REG_PLL3_CTRL &= ~(1U << 31);
	CCMU_REG_PLL4_CTRL &= ~(1U << 31);
	CCMU_REG_PLL5_CTRL &= ~(1U << 31);
	CCMU_REG_PLL6_CTRL &= ~(1U << 31);
	CCMU_REG_PLL7_CTRL &= ~(1U << 31);
	CCMU_REG_PLL8_CTRL &= ~(1U << 31);
	CCMU_REG_PLL9_CTRL &= ~(1U << 31);
	CCMU_REG_PLL10_CTRL &= ~(1U << 31);
}

void standby_clock_divsetto0(void)
{
	return ;
}

void standby_clock_divsetback(void)
{
	return ;
}

void standby_clock_drampll_ouput(int op)
{
//	__u32 reg_val;
//
//	reg_val = CCMU_REG_PLL5_CTRL;
//	if(op)
//	{
//		reg_val |= 1 << 29;
//	}
//	else
//	{
//		reg_val &= ~(1 << 29);
//	}
//	CCMU_REG_PLL5_CTRL = reg_val;
//
//	return;
}

/*
*********************************************************************************************************
*                           standby_tmr_enable_watchdog
*
*Description: enable watch-dog.
*
*Arguments  : none.
*
*Return     : none;
*
*Notes      :
*
*********************************************************************************************************
*/
#define  TMR_WATCHDOG_MODE   (*(volatile unsigned int *)(0x1c20C00 + 0x94))

void standby_tmr_enable_watchdog(void)
{
    /* set watch-dog reset, timeout is 2 seconds */
    TMR_WATCHDOG_MODE = (2<<3) | (1<<1);
    /* enable watch-dog */
    TMR_WATCHDOG_MODE |= (1<<0);
}


/*
*********************************************************************************************************
*                           standby_tmr_disable_watchdog
*
*Description: disable watch-dog.
*
*Arguments  : none.
*
*Return     : none;
*
*Notes      :
*
*********************************************************************************************************
*/
void standby_tmr_disable_watchdog(void)
{
    /* disable watch-dog reset */
    TMR_WATCHDOG_MODE &= ~(1<<1);
    /* disable watch-dog */
    TMR_WATCHDOG_MODE &= ~(1<<0);
}

void standby_clock_apb1_to_source(int clock)
{
//	__u32 reg_val;
//
//	reg_val = CCMU_REG_APB1;
//	reg_val &= ~(0x03 << 24);
//	if(clock == 32000)
//	{
//		reg_val |= (2 << 24);
//	}
//	CCMU_REG_APB1 = reg_val;
}


void standby_clock_24m_op(int op)
{
//	__u32 reg_val1, reg_val2;
//
//	if(!op)
//	{
//		reg_val1 = CCMU_REG_OSC24M;
//		reg_val1 &= ~1;
//		CCMU_REG_OSC24M = reg_val1;
//
//		reg_val2 = CCMU_REG_OSC24M;
//		reg_val2 &= ~(0xffU << 24);
//		reg_val2 |=  (0xA7U << 24);
//		reg_val2 &= ~(0x01 << 16);
//		CCMU_REG_OSC24M = reg_val2;
//
//		reg_val1 = CCMU_REG_PLL5_CTRL;
//		reg_val1 &= ~(1 << 7);
//		CCMU_REG_PLL5_CTRL = reg_val1;
//
//		reg_val2 &= ~(0xffU << 24);
//		CCMU_REG_OSC24M = reg_val2;
//	}
//	else
//	{
//		int i;
//
//		reg_val1 = CCMU_REG_OSC24M;
//		reg_val1 &= ~(0xffU << 24);
//		reg_val1 |=  (0xA7U << 24);
//		reg_val1 |=  (0x01 << 16);
//		CCMU_REG_OSC24M = reg_val1;
//
//		reg_val2 = CCMU_REG_PLL5_CTRL;
//		reg_val2 |= 1 << 7;
//		CCMU_REG_PLL5_CTRL = reg_val2;
//
//		reg_val1 &= ~(0xffU << 24);
//		CCMU_REG_OSC24M = reg_val1;
//
//		for(i=0;i<100;i++);
//
//		reg_val1 = CCMU_REG_OSC24M;
//		reg_val1 |= 1;
//		CCMU_REG_OSC24M = reg_val1;
//		for(i=0;i<100;i++);
//	}

	return;
}

