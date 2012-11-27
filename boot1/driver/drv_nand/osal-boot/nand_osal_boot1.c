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

__hdle   nand_gpio_hd = 0;

__s32 NAND_CleanFlushDCacheRegion(__u32 buff_addr, __u32 len)
{
	wlibc_CleanFlushDCacheRegion((void *)buff_addr, len);

	return 0;
}

__u32 NAND_DMASingleMap(__u32 rw, __u32 buff_addr, __u32 len)
{
	return buff_addr;
}

__u32 NAND_DMASingleUnmap(__u32 rw, __u32 buff_addr, __u32 len)
{
	return buff_addr;
}


int NAND_WaitDmaFinish(void)
{
    return 0;
}

__u32 _Getpll6Clk(void)
{
	return 600;
}

int NAND_ClkRequest(__u32 nand_Index)
{
    __u32 edo_clk, pll6_clk;
	__u32 cfg;
	__u32 nand_clk_divid_ratio;
	__u32 nand_clock;
	
	nand_clock = 10;
	
	if(nand_Index == 0)
	{
		/*set nand clock*/
		//edo_clk = (nand_max_clock > 20)?(nand_max_clock-10):nand_max_clock;
		edo_clk = nand_clock * 2;
	
	    pll6_clk = _Getpll6Clk();
		nand_clk_divid_ratio = pll6_clk / edo_clk;
		if (pll6_clk % edo_clk)
				nand_clk_divid_ratio++;
		if (nand_clk_divid_ratio){
			if (nand_clk_divid_ratio > 16)
				nand_clk_divid_ratio = 15;
			else
				nand_clk_divid_ratio--;
		}
		/*set nand clock gate on*/
		cfg = *(volatile __u32 *)(0x01c20000 + 0x80);
	
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
	
		*(volatile __u32 *)(0x01c20000 + 0x80) = cfg;
		
		//open ahb
		cfg = *(volatile __u32 *)(0x01c20000 + 0x60);
		cfg |= (0x1<<13);
		*(volatile __u32 *)(0x01c20000 + 0x60) = cfg;
		
		//open reset
		cfg = *(volatile __u32 *)(0x01c20000 + 0x2c0);
		cfg |= (0x1<<13);
		*(volatile __u32 *)(0x01c20000 + 0x2c0) = cfg;
		
	}
	else
	{
		/*set nand clock*/
		//edo_clk = (nand_max_clock > 20)?(nand_max_clock-10):nand_max_clock;
		edo_clk = nand_clock * 2;
	
	    pll6_clk = _Getpll6Clk();
		nand_clk_divid_ratio = pll6_clk / edo_clk;
		if (pll6_clk % edo_clk)
				nand_clk_divid_ratio++;
		if (nand_clk_divid_ratio){
			if (nand_clk_divid_ratio > 16)
				nand_clk_divid_ratio = 15;
			else
				nand_clk_divid_ratio--;
		}
		/*set nand clock gate on*/
		cfg = *(volatile __u32 *)(0x01c20000 + 0x84);
	
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
	
		*(volatile __u32 *)(0x01c20000 + 0x84) = cfg;
		
		//open ahb
		cfg = *(volatile __u32 *)(0x01c20000 + 0x60);
		cfg |= (0x1<<12);
		*(volatile __u32 *)(0x01c20000 + 0x60) = cfg;
		
		//open reset
		cfg = *(volatile __u32 *)(0x01c20000 + 0x2c0);
		cfg |= (0x1<<12);
		*(volatile __u32 *)(0x01c20000 + 0x2c0) = cfg;
	}		
	

	return 0;
}

void NAND_ClkRelease(__u32 nand_Index)
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
int NAND_SetClk(__u32 nand_Index, __u32 nand_clock)
{
	__u32 edo_clk, pll6_clk;
	__u32 cfg;
	__u32 nand_clk_divid_ratio;
	
	if(nand_Index == 0)
	{
		/*set nand clock*/
		//edo_clk = (nand_max_clock > 20)?(nand_max_clock-10):nand_max_clock;
		edo_clk = nand_clock * 2;
	
	    pll6_clk = _Getpll6Clk();
		nand_clk_divid_ratio = pll6_clk / edo_clk;
		if (pll6_clk % edo_clk)
				nand_clk_divid_ratio++;
		if (nand_clk_divid_ratio){
			if (nand_clk_divid_ratio > 16)
				nand_clk_divid_ratio = 15;
			else
				nand_clk_divid_ratio--;
		}
		/*set nand clock gate on*/
		cfg = *(volatile __u32 *)(0x01c20000 + 0x80);
	
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
	
		*(volatile __u32 *)(0x01c20000 + 0x80) = cfg;
		
	}
	else
	{
		/*set nand clock*/
		//edo_clk = (nand_max_clock > 20)?(nand_max_clock-10):nand_max_clock;
		edo_clk = nand_clock * 2;
	
	    pll6_clk = _Getpll6Clk();
		nand_clk_divid_ratio = pll6_clk / edo_clk;
		if (pll6_clk % edo_clk)
				nand_clk_divid_ratio++;
		if (nand_clk_divid_ratio){
			if (nand_clk_divid_ratio > 16)
				nand_clk_divid_ratio = 15;
			else
				nand_clk_divid_ratio--;
		}
		/*set nand clock gate on*/
		cfg = *(volatile __u32 *)(0x01c20000 + 0x84);
	
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
	
		*(volatile __u32 *)(0x01c20000 + 0x84) = cfg;
		
	}		
	

	return 0;
}

int NAND_GetClk(__u32 nand_Index)
{
	__u32 pll6_clk;
	__u32 cfg;
	__u32 nand_max_clock, nand_clk_divid_ratio;
	
	if(nand_Index == 0)
	{
		/*set nand clock*/
	    pll6_clk = _Getpll6Clk();
	
	    /*set nand clock gate on*/
		cfg = *(volatile __u32 *)(0x01c20000 + 0x80);
	    nand_clk_divid_ratio = ((cfg)&0xf) +1;
	    nand_max_clock = pll6_clk/(2*nand_clk_divid_ratio);
	
	}
	else
	{
		/*set nand clock*/
	    pll6_clk = _Getpll6Clk();
	
	    /*set nand clock gate on*/
		cfg = *(volatile __u32 *)(0x01c20000 + 0x84);
	    nand_clk_divid_ratio = ((cfg)&0xf) +1;
	    nand_max_clock = pll6_clk/(2*nand_clk_divid_ratio);
		
	}		
	
	return nand_max_clock;
}

void NAND_PIORequest(__u32 nand_index)
{
	if(nand_index == 0)
	{
		*(volatile __u32 *)(0x01c20800 + 0x48) = 0x22222222;
		*(volatile __u32 *)(0x01c20800 + 0x4c) = 0x22222222;
		*(volatile __u32 *)(0x01c20800 + 0x50) = 0x22222222;
		*(volatile __u32 *)(0x01c20800 + 0x54) = 0x7222;  
	}
	else if(nand_index == 1)
	{
		*(volatile __u32 *)(0x01c20800 + 0xfc) = 0x22222222;
		*(volatile __u32 *)(0x01c20800 + 0x100) &= (~0xf);
		*(volatile __u32 *)(0x01c20800 + 0x100) |= (0x2);
		*(volatile __u32 *)(0x01c20800 + 0x108) &= (~0xf<<20);
		*(volatile __u32 *)(0x01c20800 + 0x108) |= (0x2<<20);   
	}
	else
	{
		
	}		
			
	

}

void NAND_PIORelease(__u32 nand_Index)
{
	return;
}	

void NAND_Memset(void* pAddr, unsigned char value, unsigned int len)
{
    memset(pAddr, value, len);   
}

void NAND_Memcpy(void* pAddr_dst, void* pAddr_src, unsigned int len)
{
    memcpy(pAddr_dst, pAddr_src, len);    
}

void * NAND_Malloc(unsigned int Size)
{
	return wBoot_malloc(Size);
}

void NAND_Free(void *pAddr, unsigned int Size)
{
	wBoot_free(pAddr);
}

void  OSAL_IrqUnLock(__u32  p)
{
    ;
}
void  OSAL_IrqLock  (__u32 *p)
{
    ;
}

int NAND_WaitRbReady(void)
{
    return 0;
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
*  Description:  用户可以自行设定是否需要打印
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
int NAND_Print(const char * str, ...)
{
    wlibc_uprintf(str);

    return 0;
}

__u32 NAND_VA_TO_PA(__u32 buff_addr)
{
    return buff_addr;
}

__u32 NAND_GetIOBaseAddrCH0(void)
{
	return 0x01c03000;
}
	
__u32 NAND_GetIOBaseAddrCH1(void)
{
	return 0x01c05000;
}
