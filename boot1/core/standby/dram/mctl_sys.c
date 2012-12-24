//*****************************************************************************
//	Allwinner Technology, All Right Reserved. 2006-2010 Copyright (c)
//
//	File: 				mctl_sys.c
//
//	Description:  This file implements basic functions for AW1633 DRAM controller
//
//	History:
//              2012/02/06      Berg Xing       0.10    Initial version
//              2012/02/24      Berg Xing       0.20    Support 2 channel
//              2012/02/27      Berg Xing       0.30    modify mode register access
//				2012/03/01		Berg Xing       0.40    add LPDDR2
//				2012/03/10		Berg Xing       0.50    add mctl_dll_init() function
//				2012/04/26		Berg Xing       0.60    add deep sleep
//				2012/06/19		Berg Xing       0.70    add 2T mode
//				2012/11/07		CPL				0.80	FPGA version based on berg's code
//				2012/11/14		CPL				0.90	add SID and regulate the parameters order
//				2012/11/21		CPL				0.91	modify parameters error
//				2012/11/25		CPL				0.92	modify for IC test
//				2012/11/27		CPL				0.93	add master configuration
//				2012/11/28		CPL				0.94	modify for boot and burn interface compatible
//				2012/11/29		CPL				0.95	modify lock parameters configuration
//				2012/12/3		CPL				0.96	add dll&pll delay and simple test
//				2012/12/6		CPL				0.97	add write odt enable function
//				2012/12/8		CPL				0.98	add read odt enable & adjust dll phase
//				2012/12/10		CPL				0.99	extend DLL & PLL delay
//				2012/12/22		CPL				0.991	disable master access when enter standby and enable when exit standby
//*****************************************************************************
#include "mctl_reg.h"
#include "mctl_hal.h"

void mctl_self_refresh_entry(unsigned int ch_index)
{
	unsigned int reg_val;
	unsigned int ch_id;
	
	//Disable the DRAM master access
	mctl_write_w(SDR_COM_MAER, 0);

	if(ch_index == 1)
		ch_id = 0x1000;
	else
		ch_id = 0x0;
	//set SLEEP command
	reg_val = 0x3;
	mctl_write_w(ch_id + SDR_SCTL, reg_val);

	//check whether in Low Power State
	while(  (mctl_read_w(ch_id + SDR_SSTAT)&0x7) != 0x5 ) {};

	//put PAD into power down state
	reg_val = mctl_read_w(ch_id + SDR_ACIOCR);
	reg_val |= (0x1<<3)|(0x1<<8)|(0x3<<18);
	mctl_write_w(ch_id + SDR_ACIOCR, reg_val);

	reg_val = mctl_read_w(ch_id + SDR_DXCCR);
	reg_val |= (0x1<<2)|(0x1<<3);
	mctl_write_w(ch_id + SDR_DXCCR, reg_val);

	reg_val = mctl_read_w(ch_id + SDR_DSGCR);
	reg_val &= ~(0x1<<28);
	mctl_write_w(ch_id + SDR_DSGCR, reg_val);
}

void mctl_self_refresh_exit(unsigned int ch_index)
{
	unsigned int reg_val;
	unsigned int ch_id;

	if(ch_index == 1)
		ch_id = 0x1000;
	else
		ch_id = 0x0;

	reg_val = mctl_read_w(ch_id + SDR_DSGCR);
	reg_val |= (0x1<<28);
	mctl_write_w(ch_id + SDR_DSGCR, reg_val);

	reg_val = mctl_read_w(ch_id + SDR_DXCCR);
	reg_val &= ~((0x1<<2)|(0x1<<3));
	mctl_write_w(ch_id + SDR_DXCCR, reg_val);

	//put PAD into power down state
	reg_val = mctl_read_w(ch_id + SDR_ACIOCR);
	reg_val &= ~((0x1<<3)|(0x1<<8)|(0x3<<18));
	mctl_write_w(ch_id + SDR_ACIOCR, reg_val);

	//set WAKEUP command
	reg_val = 0x4;
	mctl_write_w(ch_id + SDR_SCTL, reg_val);

	//check whether in Low Power State
	while(  (mctl_read_w(ch_id + SDR_SSTAT)&0x7) != 0x3 ) {};
	
	//Disable the DRAM master access
	mctl_write_w(SDR_COM_MAER, 0xFFFFFFFF);
}

void mctl_deep_sleep_entry(void)
{
	unsigned int reg_val;

	//put external DRAM into sleep state
	mctl_self_refresh_entry(0);
	//if(MCTL_CHANNEL_NUM == 2)
	if(mctl_read_w(SDR_COM_CR) & (0x1<<19))
	{
		mctl_self_refresh_entry(1);
	}

	//hold PAD
	reg_val = mctl_read_w(R_VDD_SYS_PWROFF_GATE);
	reg_val |= (0x1<<1);
	//if(MCTL_CHANNEL_NUM == 2)
	if(mctl_read_w(SDR_COM_CR) & (0x1<<19))
		reg_val |=0x3;
	mctl_write_w(R_VDD_SYS_PWROFF_GATE, reg_val);

  	//put DRAMC AHB register circuit on reset state
  	reg_val = mctl_read_w(CCM_AHB1_RST_REG0);
  	reg_val &= ~(0x1<<14);
  	mctl_write_w(CCM_AHB1_RST_REG0, reg_val);

  	//put DRAMC other circuit on reset state
  	reg_val = mctl_read_w(CCM_DRAMCLK_CFG_CTRL);
  	reg_val &= ~(0x1U<<31);
  	mctl_write_w(CCM_DRAMCLK_CFG_CTRL, reg_val);

  	//gate off DRAMC AHB clk
  	reg_val = mctl_read_w(CCM_AHB1_GATE0_CTRL);
  	reg_val &=~(0x1<<14);
  	mctl_write_w(CCM_AHB1_GATE0_CTRL, reg_val);

  	//gate off DRAMC MDFS clk
  	reg_val = mctl_read_w(CCM_MDFS_CLK_CTRL);
  	reg_val &=~(0x1U<<31);
  	mctl_write_w(CCM_MDFS_CLK_CTRL, reg_val);

  	//DRAMC PLL off
  	reg_val = mctl_read_w(CCM_PLL5_DDR_CTRL);
  	reg_val &=~(0x1U<<31);
  	mctl_write_w(CCM_PLL5_DDR_CTRL, reg_val);
  	
  	reg_val = mctl_read_w(CCM_PLL5_DDR_CTRL);
  	reg_val |= 0x1<<20;
  	mctl_write_w(CCM_PLL5_DDR_CTRL, reg_val);
}

void mctl_deep_sleep_exit(__dram_para_t *para)
{
	init_DRAM(1, para);
}

