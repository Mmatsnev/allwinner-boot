/*
**********************************************************************************************************************
*											        eGon
*						           the Embedded GO-ON Bootloader System
*									       eGON arm boot sub-system
*
*						  Copyright(C), 2006-2010, SoftWinners Microelectronic Co., Ltd.
*                                           All Rights Reserved
*
* File    : nand_osal_boot0.c
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
#include "egon2.h"

void NAND_AHBEnable(void)
{
    *(volatile __u32 *)(CCMU_REGS_BASE + 0x60) |= 1 << 13;
}

void NAND_AHBDisable(void)
{
    *(volatile __u32 *)(CCMU_REGS_BASE + 0x60) &= ~(1 << 13);
}

void NAND_ClkRequest(void)
{
    return ;
}

void NAND_ClkRelease(void)
{
    return ;
}

void NAND_ClkEnable(void)
{
	*(volatile __u32 *)(CCMU_REGS_BASE + 0x80) |= 1U << 31;

    return ;
}

void NAND_ClkDisable(void)
{
	*(volatile __u32 *)(CCMU_REGS_BASE + 0x80) &= ~(1U << 31);

    return ;
}

void NAND_WaitDmaFinish(void)
{
	return ;
}
/*
**********************************************************************************************************************
*
*             NAND_GetCmuClk
*
*  Description:
*
*
*  Parameters:
*
*
*  Return value:
*
*
**********************************************************************************************************************
*/
__u32 NAND_GetCmuClk(void)
{
	__u32 reg_val;
	__u32 factor_n;
	__u32 factor_k;
	__u32 clock;

	reg_val  = *(volatile unsigned int *)(0x01c20000 + 0x28);
	factor_n = (reg_val >> 8) & 0x1f;
	factor_k = ((reg_val >> 4) & 0x3) + 1;

	clock = 24 * factor_n * factor_k/2;

	return clock;
}
/*
**********************************************************************************************************************
*
*             NAND_GetCmuClk
*
*  Description:
*
*
*  Parameters:
*
*
*  Return value:
*
*
**********************************************************************************************************************
*/
void NAND_SetClk(__u32 nand_max_clock)
{
	__u32 edo_clk, cmu_clk;
	__u32 cfg;
	__u32 nand_clk_divid_ratio;

	/*set nand clock*/
	//edo_clk = (nand_max_clock > 20)?(nand_max_clock-10):nand_max_clock;
	edo_clk = nand_max_clock * 2;

    cmu_clk = NAND_GetCmuClk( );
	nand_clk_divid_ratio = cmu_clk / edo_clk;
	if (cmu_clk % edo_clk)
			nand_clk_divid_ratio++;
	if (nand_clk_divid_ratio){
		if (nand_clk_divid_ratio > 16)
			nand_clk_divid_ratio = 15;
		else
			nand_clk_divid_ratio--;
	}
	/*set nand clock gate on*/
	cfg = *(volatile __u32 *)(CCMU_REGS_BASE + 0x80);

	/*gate on nand clock*/
	cfg |= (1U << 31);
	/*take cmu pll as nand src block*/
	cfg &= ~(0x3 << 24);
	cfg |=  (0x2 << 24);
	//set divn = 0
	cfg &= ~(0x03 << 12);

	/*set ratio*/
	cfg &= ~(0x0f << 0);
	cfg |= (nand_clk_divid_ratio & 0xf) << 0;

	*(volatile __u32 *)(CCMU_REGS_BASE + 0x80) = cfg;
}

__s32 NAND_GetClk(void)
{
	__u32 cmu_clk;
	__u32 cfg;
	__u32 nand_max_clock, nand_clk_divid_ratio;

	/*set nand clock*/
    cmu_clk = NAND_GetCmuClk( );

    /*set nand clock gate on*/
	cfg = *(volatile __u32 *)(CCMU_REGS_BASE + 0x80);
    nand_clk_divid_ratio = ((cfg)&0xf) +1;
    nand_max_clock = cmu_clk/(2*nand_clk_divid_ratio);

    return nand_max_clock;


}

/*
**********************************************************************************************************************
*
*             NAND_GetCmuClk
*
*  Description:
*
*
*  Parameters:
*
*
*  Return value:
*
*
**********************************************************************************************************************
*/
extern  __s32 boot_set_gpio(void  *user_gpio_list, __u32 group_count_max, __s32 set_gpio);

void NAND_PIORequest(void)
{
	boot_set_gpio((void *)BOOT_STORAGE_CODE1, 0, 1);
}
/*
**********************************************************************************************************************
*
*             NAND_ReleasePin
*
*  Description:
*
*
*  Parameters:
*
*
*  Return value:
*
*
**********************************************************************************************************************
*/
void NAND_PIORelease(void)
{
	return ;
}
void NAND_EnRbInt(void)
{
	return ;
}


void NAND_ClearRbInt(void)
{
	return ;
}

int NAND_WaitRbReady(void)
{
	return 0;
}

void NAND_RbInterrupt(void)
{
	return ;
}
/*
************************************************************************************************************
*
*                                             OSAL_malloc
*
*    �������ƣ�
*
*    �����б�
*
*    ����ֵ  ��
*
*    ˵��    �� ����һ����ٵ�malloc������Ŀ��ֻ���ṩ����һ��������������벻ͨ��
*               �����ṩ�κεĺ�������
*
************************************************************************************************************
*/
void* NAND_Malloc(unsigned int Size)
{
	return (void *)0x40000000;
}
/*
************************************************************************************************************
*
*                                             OSAL_free
*
*    �������ƣ�
*
*    �����б�
*
*    ����ֵ  ��
*
*    ˵��    �� ����һ����ٵ�free������Ŀ��ֻ���ṩ����һ��������������벻ͨ��
*               �����ṩ�κεĺ�������
*
************************************************************************************************************
*/
void NAND_Free(void *pAddr, unsigned int Size)
{
    return ;
}

void *NAND_IORemap(unsigned int base_addr, unsigned int size)
{
    return (void *)base_addr;
}
/*
**********************************************************************************************************************
*
*             OSAL_printf
*
*  Description:  �û����������趨�Ƿ���Ҫ��ӡ
*
*
*  Parameters:
*
*
*  Return value:
*
*
**********************************************************************************************************************
*/
__s32 NAND_Print(const char * str, ...)
{
	//UART_printf2(str);
    return 0;
}
