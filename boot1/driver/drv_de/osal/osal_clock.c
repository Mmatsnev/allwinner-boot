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
#include "types.h"
#include "osal_de.h"

#if 1
__s32 OSAL_CCMU_SetSrcFreq(__u32 nSclkNo, __u32 nFreq)
{
    //__inf("OSAL_CCMU_SetSrcFreq,%d,%d\n", nSclkNo, nFreq);

    if(nSclkNo == SYS_CLK_PLL3)
    {
        sys_put_wvalue(0x01c20010,0x81000007 | ((nFreq/3000000)<<8));
    }
    else if(nSclkNo == SYS_CLK_PLL7)
    {
        sys_put_wvalue(0x01c20030,0x81000007 | ((nFreq/3000000)<<8));
    }
    else if(nSclkNo == SYS_CLK_PLL6)
    {
        __u32 N=0, K=2;
        __u32 value = 0;

        N = (nFreq + ((K * 24000000)/2)) / (K * 24000000);
        value = sys_get_wvalue(0x01c20028) & (~(0x1f<<8)) & (~(0x3<<4));
        sys_put_wvalue(0x01c20028,value | (1<<31) | (N<<8) | ((K-1)<<4));
    }
    return 0;
}


__u32 OSAL_CCMU_GetSrcFreq(__u32 nSclkNo)
{
    __u32 value = 0;

    //__inf("OSAL_CCMU_GetSrcFreq,%d\n",nSclkNo);

    if(nSclkNo == SYS_CLK_PLL3)
    {
        value = (sys_get_wvalue(0x01c20010) >> 8)&0x7f;
    }
    else if(nSclkNo == SYS_CLK_PLL7)
    {
        value = (sys_get_wvalue(0x01c20030) >> 8)&0x7f;
    }
    else if(nSclkNo == SYS_CLK_PLL6)
    {
        __u32 reg,N,K,P;

        reg = sys_get_wvalue(0x01c20028);
        N = ((reg >>8)&0x1f) + 1;
        K = ((reg>>4)&0x3) + 1;

        value = (24 * N * K)/2;
    }

    return value * 3000000;
}

__hdle OSAL_CCMU_OpenMclk(__s32 nMclkNo)
{
    return (__hdle)nMclkNo;
}

__s32  OSAL_CCMU_CloseMclk(__hdle hMclk)
{
    return 0;
}

__s32 OSAL_CCMU_SetMclkSrc(__hdle hMclk, __u32 nSclkNo)
{
    __u32 clk_src = 0;
    __u32 value = 0;

    //__inf("OSAL_CCMU_SetMclkSrc,%d,%d\n", hMclk, nSclkNo);

    if(hMclk == MOD_CLK_LCD0CH0 || hMclk == MOD_CLK_LCD1CH0)
    {
        if(nSclkNo == SYS_CLK_PLL3)
        {
            clk_src = 0;
        }
        else if(nSclkNo == SYS_CLK_PLL7)
        {
            clk_src = 1;
        }
        else if(nSclkNo == SYS_CLK_PLL3X2)
        {
            clk_src = 2;
        }
        else if(nSclkNo == SYS_CLK_PLL7X2)
        {
            clk_src = 3;
        }else if(nSclkNo == SYS_CLK_MIPIPLL)
        {
            clk_src = 4;
        }
    }
    else if(hMclk == MOD_CLK_LCD0CH1 || hMclk == MOD_CLK_LCD0CH1 || hMclk ==  MOD_CLK_HDMI 
        || hMclk == MOD_CLK_MIPIDSIP || hMclk == MOD_CLK_MIPIDSIS)
    {
        if(nSclkNo == SYS_CLK_PLL3)
        {
            clk_src = 0;
        }
        else if(nSclkNo == SYS_CLK_PLL7)
        {
            clk_src = 1;
        }
        else if(nSclkNo == SYS_CLK_PLL3X2)
        {
            clk_src = 2;
        }
        else if(nSclkNo == SYS_CLK_PLL7X2)
        {
            clk_src = 3;
        }
    }
    else if(hMclk == MOD_CLK_DEBE0 || hMclk == MOD_CLK_DEBE1 || hMclk == MOD_CLK_DEFE0 
        || hMclk == MOD_CLK_DEFE1 || hMclk == MOD_CLK_IEPDEU0 || hMclk ==  MOD_CLK_IEPDEU1 
        || hMclk == MOD_CLK_IEPDRC0 || hMclk == MOD_CLK_IEPDRC1 )
    {
        if(nSclkNo == SYS_CLK_PLL3)
        {
            clk_src = 0;
        }
        else if(nSclkNo == SYS_CLK_PLL7)
        {
            clk_src = 1;
        }
        else if(nSclkNo == SYS_CLK_PLL6x2)
        {
            clk_src = 2;
        }
        else if(nSclkNo == SYS_CLK_PLL8)
        {
            clk_src = 3;
        }
        else if(nSclkNo == SYS_CLK_PLL9)
        {
            clk_src = 4;
        }
        else if(nSclkNo == SYS_CLK_PLL10)
        {
            clk_src = 5;
        }
    }


    if(hMclk == MOD_CLK_LCD0CH0)
    {
        value = sys_get_wvalue(0x01c20118) & (~(0x7<<24));
        sys_put_wvalue(0x01c20118, value | (clk_src<<24));
    }
    else if(hMclk == MOD_CLK_LCD1CH0)
    {
        value = sys_get_wvalue(0x01c2011c) & (~(0x7<<24));
        sys_put_wvalue(0x01c2011c, value | (clk_src<<24));
    }
    else if(hMclk == MOD_CLK_LCD0CH1)
    {
        value = sys_get_wvalue(0x01c2012c) & (~(0x3<<24));
        sys_put_wvalue(0x01c2012c, value | (clk_src<<24));
    }
    else if(hMclk == MOD_CLK_LCD1CH1)
    {
        value = sys_get_wvalue(0x01c20130) & (~(0x3<<24));
        sys_put_wvalue(0x01c20130, value | (clk_src<<24));
    }
    else if(hMclk == MOD_CLK_HDMI)
    {
        value = sys_get_wvalue(0x01c20150) & (~(0x3<<24));
        sys_put_wvalue(0x01c20150, value | (clk_src<<24));
    }
    else if(hMclk == MOD_CLK_DEBE0)
    {
        value = sys_get_wvalue(0x01c20104) & (~(0x7<<24));
        sys_put_wvalue(0x01c20104, value | (clk_src<<24));
    }
    else if(hMclk == MOD_CLK_DEBE1)
    {
        value = sys_get_wvalue(0x01c20108) & (~(0x7<<24));
        sys_put_wvalue(0x01c20108, value | (clk_src<<24));
    }
    else if(hMclk == MOD_CLK_DEFE0)
    {
        value = sys_get_wvalue(0x01c2010c) & (~(0x7<<24));
        sys_put_wvalue(0x01c2010c, value | (clk_src<<24));
    }
    else if(hMclk == MOD_CLK_DEFE1)
    {
        value = sys_get_wvalue(0x01c20110) & (~(0x7<<24));
        sys_put_wvalue(0x01c20110, value | (clk_src<<24));
    }
    else if(hMclk == MOD_CLK_MIPIDSIS)
    {
        value = sys_get_wvalue(0x01c20168) & (~(0x3<<24));
        sys_put_wvalue(0x01c20168, value | (clk_src<<24));
    }
    else if(hMclk == MOD_CLK_MIPIDSIP)
    {
        value = sys_get_wvalue(0x01c20168) & (~(0x3<<8));
        sys_put_wvalue(0x01c20168, value | (clk_src<<8));
    }
    else if(hMclk == MOD_CLK_IEPDRC0)
    {
        value = sys_get_wvalue(0x01c20180) & (~(0x7<<24));
        sys_put_wvalue(0x01c20180, value | (clk_src<<24));
    }
    else if(hMclk == MOD_CLK_IEPDRC0)
    {
        value = sys_get_wvalue(0x01c20184) & (~(0x7<<24));
        sys_put_wvalue(0x01c20184, value | (clk_src<<24));
    }
    else if(hMclk == MOD_CLK_IEPDEU0)
    {
        value = sys_get_wvalue(0x01c20188) & (~(0x7<<24));
        sys_put_wvalue(0x01c20188, value | (clk_src<<24));
    }
    else if(hMclk == MOD_CLK_IEPDEU1)
    {
        value = sys_get_wvalue(0x01c2018c) & (~(0x7<<24));
        sys_put_wvalue(0x01c2018c, value | (clk_src<<24));
    }
    return 0;
}

__s32 OSAL_CCMU_GetMclkSrc(__hdle hMclk)
{
    return 0;
}

__s32 OSAL_CCMU_SetMclkDiv(__hdle hMclk, __s32 nDiv)
{
    __u32 value = 0;

    //__inf("OSAL_CCMU_SetMclkDiv,%d,%d\n", hMclk, nDiv);

    if(hMclk == MOD_CLK_LCD0CH1)
    {
        value = sys_get_wvalue(0x01c2012c) & (~(0xf<<0));
        sys_put_wvalue(0x01c2012c, value | ((nDiv-1)<<0));
    }
    else if(hMclk == MOD_CLK_LCD1CH1)
    {
        value = sys_get_wvalue(0x01c20130) & (~(0xf<<0));
        sys_put_wvalue(0x01c20130, value | ((nDiv-1)<<0));
    }
    else if(hMclk == MOD_CLK_HDMI)
    {
        value = sys_get_wvalue(0x01c20150) & (~(0xf<<0));
        sys_put_wvalue(0x01c20150, value | ((nDiv-1)<<0));
    }
    else if(hMclk == MOD_CLK_DEBE0)
    {
        value = sys_get_wvalue(0x01c20104) & (~(0xf<<0));
        sys_put_wvalue(0x01c20104, value | ((nDiv-1)<<0));
    }
    else if(hMclk == MOD_CLK_DEBE1)
    {
        value = sys_get_wvalue(0x01c20108) & (~(0xf<<0));
        sys_put_wvalue(0x01c20108, value | ((nDiv-1)<<0));
    }
    else if(hMclk == MOD_CLK_DEFE0)
    {
        value = sys_get_wvalue(0x01c2010c) & (~(0xf<<0));
        sys_put_wvalue(0x01c2010c, value | ((nDiv-1)<<0));
    }
    else if(hMclk == MOD_CLK_DEFE1)
    {
        value = sys_get_wvalue(0x01c20110) & (~(0xf<<0));
        sys_put_wvalue(0x01c20110, value | ((nDiv-1)<<0));
    }
    else if(hMclk == MOD_CLK_MIPIDSIS)
    {
        value = sys_get_wvalue(0x01c20168) & (~(0xf<<16));
        sys_put_wvalue(0x01c20168, value | ((nDiv-1)<<16));
    }
    else if(hMclk == MOD_CLK_MIPIDSIP)
    {
        value = sys_get_wvalue(0x01c20168) & (~(0xf<<0));
        sys_put_wvalue(0x01c20168, value | ((nDiv-1)<<0));
    }
    else if(hMclk == MOD_CLK_IEPDRC0)
    {
        value = sys_get_wvalue(0x01c20180) & (~(0xf<<0));
        sys_put_wvalue(0x01c20180, value | ((nDiv-1)<<0));
    }
    else if(hMclk == MOD_CLK_IEPDRC1)
    {
        value = sys_get_wvalue(0x01c20184) & (~(0xf<<0));
        sys_put_wvalue(0x01c20184, value | ((nDiv-1)<<0));
    }
    else if(hMclk == MOD_CLK_IEPDEU0)
    {
        value = sys_get_wvalue(0x01c20188) & (~(0xf<<0));
        sys_put_wvalue(0x01c20188, value | ((nDiv-1)<<0));
    }
    else if(hMclk == MOD_CLK_IEPDEU1)
    {
        value = sys_get_wvalue(0x01c2018c) & (~(0xf<<0));
        sys_put_wvalue(0x01c2018c, value | ((nDiv-1)<<0));
    }
    
    return 0;
}

__u32 OSAL_CCMU_GetMclkDiv(__hdle hMclk)
{
    return 0;
}

__s32 OSAL_CCMU_MclkOnOff(__hdle hMclk, __s32 bOnOff)
{
    __u32 value = 0;

    //__inf("OSAL_CCMU_MclkOnOff,%d,%d\n", hMclk, bOnOff);

    if(hMclk == MOD_CLK_LCD0CH0)
    {
        value = sys_get_wvalue(0x01c20118) & (~(0x1<<31));
        sys_put_wvalue(0x01c20118, value | (bOnOff<<31));
    }
    else if(hMclk == MOD_CLK_LCD1CH0)
    {
        value = sys_get_wvalue(0x01c2011c) & (~(0x1<<31));
        sys_put_wvalue(0x01c2011c, value | (bOnOff<<31));
    }
    else if(hMclk == MOD_CLK_LCD0CH1)
    {
        value = sys_get_wvalue(0x01c2012c) & (~(0x1<<31));
        sys_put_wvalue(0x01c2012c, value | (bOnOff<<31));
    }
    else if(hMclk == MOD_CLK_LCD1CH1)
    {
        value = sys_get_wvalue(0x01c20130) & (~(0x1<<31));
        sys_put_wvalue(0x01c20130, value | (bOnOff<<31));
    }
    else if(hMclk == MOD_CLK_HDMI)
    {
        value = sys_get_wvalue(0x01c20150) & (~(0x1<<31));
        sys_put_wvalue(0x01c20150, value | (bOnOff<<31));
    }
    else if(hMclk == MOD_CLK_DEBE0)
    {
        value = sys_get_wvalue(0x01c20104) & (~(0x1<<31));
        sys_put_wvalue(0x01c20104, value | (bOnOff<<31));
    }
    else if(hMclk == MOD_CLK_DEBE1)
    {
        value = sys_get_wvalue(0x01c20108) & (~(0x1<<31));
        sys_put_wvalue(0x01c20108, value | (bOnOff<<31));
    }
    else if(hMclk == MOD_CLK_DEFE0)
    {
        value = sys_get_wvalue(0x01c2010c) & (~(0x1<<31));
        sys_put_wvalue(0x01c2010c, value | (bOnOff<<31));
    }
    else if(hMclk == MOD_CLK_DEFE1)
    {
        value = sys_get_wvalue(0x01c20110) & (~(0x1<<31));
        sys_put_wvalue(0x01c20110, value | (bOnOff<<31));
    }
    else if(hMclk == MOD_CLK_MIPIDSIS)
    {
        value = sys_get_wvalue(0x01c20168) & (~(0x1<<31));
        sys_put_wvalue(0x01c20168, value | (bOnOff<<31));
    }
    else if(hMclk == MOD_CLK_MIPIDSIP)
    {
        value = sys_get_wvalue(0x01c20168) & (~(0x1<<15));
        sys_put_wvalue(0x01c20168, value | (bOnOff<<15));
    }
    else if(hMclk == MOD_CLK_IEPDRC0)
    {
        value = sys_get_wvalue(0x01c20180) & (~(0x1<<31));
        sys_put_wvalue(0x01c20180, value | (bOnOff<<31));
    }
    else if(hMclk == MOD_CLK_IEPDRC1)
    {
        value = sys_get_wvalue(0x01c20184) & (~(0x1<<31));
        sys_put_wvalue(0x01c20184, value | (bOnOff<<31));
    }
    else if(hMclk == MOD_CLK_IEPDEU0)
    {
        value = sys_get_wvalue(0x01c20188) & (~(0x1<<31));
        sys_put_wvalue(0x01c20188, value | (bOnOff<<31));
    }
    else if(hMclk == MOD_CLK_IEPDEU1)
    {
        value = sys_get_wvalue(0x01c2018c) & (~(0x1<<31));
        sys_put_wvalue(0x01c2018c, value | (bOnOff<<31));
    }
    else if(hMclk == DRAM_CLK_DEBE0)
    {
        value = sys_get_wvalue(0x01c20100) & (~(0x1<<26));
        sys_put_wvalue(0x01c20100, value | (bOnOff<<26));
    }
    else if(hMclk == DRAM_CLK_DEBE1)
    {
        value = sys_get_wvalue(0x01c20100) & (~(0x1<<27));
        sys_put_wvalue(0x01c20100, value | (bOnOff<<27));
    }
    else if(hMclk == DRAM_CLK_DEFE0)
    {
        value = sys_get_wvalue(0x01c20100) & (~(0x1<<24));
        sys_put_wvalue(0x01c20100, value | (bOnOff<<24));
    }
    else if(hMclk == DRAM_CLK_DEFE1)
    {
        value = sys_get_wvalue(0x01c20100) & (~(0x1<<25));
        sys_put_wvalue(0x01c20100, value | (bOnOff<<25));
    }
    else if(hMclk == DRAM_CLK_DEU0)
    {
        value = sys_get_wvalue(0x01c20100) & (~(0x1<<18));
        sys_put_wvalue(0x01c20100, value | (bOnOff<<18));
    }
    else if(hMclk == DRAM_CLK_DEU1)
    {
        value = sys_get_wvalue(0x01c20100) & (~(0x1<<19));
        sys_put_wvalue(0x01c20100, value | (bOnOff<<19));
    }
    else if(hMclk == DRAM_CLK_DRC0)
    {
        value = sys_get_wvalue(0x01c20100) & (~(0x1<<16));
        sys_put_wvalue(0x01c20100, value | (bOnOff<<16));
    }
    else if(hMclk == DRAM_CLK_DRC1)
    {
        value = sys_get_wvalue(0x01c20100) & (~(0x1<<17));
        sys_put_wvalue(0x01c20100, value | (bOnOff<<17));
    }
    else if(hMclk == AHB_CLK_DEFE0)
    {
        value = sys_get_wvalue(0x01c20064) & (~(0x1<<14));
        sys_put_wvalue(0x01c20064, value | (bOnOff<<14));
    }
    else if(hMclk == AHB_CLK_DEFE1)
    {
        value = sys_get_wvalue(0x01c20064) & (~(0x1<<15));
        sys_put_wvalue(0x01c20064, value | (bOnOff<<15));
    }
    else if(hMclk == AHB_CLK_DEBE0)
    {
        value = sys_get_wvalue(0x01c20064) & (~(0x1<<12));
        sys_put_wvalue(0x01c20064, value | (bOnOff<<12));
    }
    else if(hMclk == AHB_CLK_DEBE1)
    {
        value = sys_get_wvalue(0x01c20064) & (~(0x1<<13));
        sys_put_wvalue(0x01c20064, value | (bOnOff<<13));
    }
    else if(hMclk == AHB_CLK_HDMI)
    {
        value = sys_get_wvalue(0x01c20064) & (~(0x1<<11));
        sys_put_wvalue(0x01c20064, value | (bOnOff<<11));
    }
    else if(hMclk == AHB_CLK_LCD0)
    {
        value = sys_get_wvalue(0x01c20064) & (~(0x1<<4));
        sys_put_wvalue(0x01c20064, value | (bOnOff<<4));
    }
    else if(hMclk == AHB_CLK_LCD1)
    {
        value = sys_get_wvalue(0x01c20064) & (~(0x1<<5));
        sys_put_wvalue(0x01c20064, value | (bOnOff<<5));
    }
    else if(hMclk == AHB_CLK_DRC0)
    {
        value = sys_get_wvalue(0x01c20064) & (~(0x1<<25));
        sys_put_wvalue(0x01c20064, value | (bOnOff<<25));
    }
    else if(hMclk == AHB_CLK_DRC1)
    {
        value = sys_get_wvalue(0x01c20064) & (~(0x1<<26));
        sys_put_wvalue(0x01c20064, value | (bOnOff<<26));
    }
    else if(hMclk == AHB_CLK_DEU0)
    {
        value = sys_get_wvalue(0x01c20064) & (~(0x1<<23));
        sys_put_wvalue(0x01c20064, value | (bOnOff<<23));
    }
    else if(hMclk == AHB_CLK_DEU1)
    {
        value = sys_get_wvalue(0x01c20064) & (~(0x1<<24));
        sys_put_wvalue(0x01c20064, value | (bOnOff<<24));
    }
    
    return 0;
}

__s32 OSAL_CCMU_MclkReset(__hdle hMclk, __s32 bReset)
{
    __u32 value = 0;

    //__inf("OSAL_CCMU_MclkReset,%d,%d\n", hMclk, bReset);

    bReset = 1-bReset;

    if(hMclk == MOD_CLK_DEFE0)
    {
        value = sys_get_wvalue(0x01c202c4) & (~(0x1<<14));
        sys_put_wvalue(0x01c202c4, value | (bReset<<14));
    }
    else if(hMclk == MOD_CLK_DEFE1)
    {
        value = sys_get_wvalue(0x01c202c4) & (~(0x1<<15));
        sys_put_wvalue(0x01c202c4, value | (bReset<<15));
    }
    else if(hMclk == MOD_CLK_DEBE0)
    {
        value = sys_get_wvalue(0x01c202c4) & (~(0x1<<12));
        sys_put_wvalue(0x01c202c4, value | (bReset<<12));
    }
    else if(hMclk == MOD_CLK_DEBE1)
    {
        value = sys_get_wvalue(0x01c202c4) & (~(0x1<<13));
        sys_put_wvalue(0x01c202c4, value | (bReset<<13));
    }
    else if(hMclk == MOD_CLK_HDMI)
    {
        value = sys_get_wvalue(0x01c202c4) & (~(0x1<<11));
        sys_put_wvalue(0x01c202c4, value | (bReset<<11));
    }
    else if(hMclk == MOD_CLK_LCD0CH0)
    {
        value = sys_get_wvalue(0x01c202c4) & (~(0x1<<4));
        sys_put_wvalue(0x01c202c4, value | (bReset<<4));
    }
    else if(hMclk == MOD_CLK_LCD1CH0)
    {
        value = sys_get_wvalue(0x01c202c4) & (~(0x1<<5));
        sys_put_wvalue(0x01c202c4, value | (bReset<<5));
    }
    else if(hMclk == MOD_CLK_LVDS)
    {
        value = sys_get_wvalue(0x01c202c8) & (~(0x1<<0));
        sys_put_wvalue(0x01c202c8, value | (bReset<<0));
    }
    else if(hMclk == MOD_CLK_IEPDRC0)
    {
        value = sys_get_wvalue(0x01c202c4) & (~(0x1<<25));
        sys_put_wvalue(0x01c202c4, value | (bReset<<25));
    }
    else if(hMclk == MOD_CLK_IEPDRC1)
    {
        value = sys_get_wvalue(0x01c202c4) & (~(0x1<<26));
        sys_put_wvalue(0x01c202c4, value | (bReset<<26));
    }
    else if(hMclk == MOD_CLK_IEPDEU0)
    {
        value = sys_get_wvalue(0x01c202c4) & (~(0x1<<23));
        sys_put_wvalue(0x01c202c4, value | (bReset<<23));
    }
    else if(hMclk == MOD_CLK_IEPDEU1)
    {
        value = sys_get_wvalue(0x01c202c4) & (~(0x1<<24));
        sys_put_wvalue(0x01c202c4, value | (bReset<<24));
    }
    else if(hMclk == MOD_CLK_MIPIDSIS)
    {
        value = sys_get_wvalue(0x01c202c0) & (~(0x1<<1));
        sys_put_wvalue(0x01c202c0, value | (bReset<<1));
    }
    return 0;
}

#else

typedef __u32 CSP_CCM_sysClkNo_t;


__s32 OSAL_CCMU_SetSrcFreq( CSP_CCM_sysClkNo_t nSclkNo, __u32 nFreq )
{
    return 0;
}

__u32 OSAL_CCMU_GetSrcFreq( CSP_CCM_sysClkNo_t nSclkNo )
{
    return 0;
}

__hdle OSAL_CCMU_OpenMclk( __s32 nMclkNo )
{
    return 0;
}

__s32 OSAL_CCMU_CloseMclk( __hdle hMclk )
{
    return 0;
}

__s32 OSAL_CCMU_SetMclkSrc( __hdle hMclk, CSP_CCM_sysClkNo_t nSclkNo )
{
    return 0;
}

__s32 OSAL_CCMU_GetMclkSrc( __hdle hMclk )
{
    return 0;
}

__s32 OSAL_CCMU_SetMclkDiv( __hdle hMclk, __s32 nDiv )
{
    return 0;
}

__u32 OSAL_CCMU_GetMclkDiv( __hdle hMclk )
{
    return 0;
}

__s32 OSAL_CCMU_MclkOnOff( __hdle hMclk, __s32 bOnOff )
{
    return 0;
}

__s32 OSAL_CCMU_MclkReset(__hdle hMclk, __s32 bReset)
{
    return 0;
}
#endif

