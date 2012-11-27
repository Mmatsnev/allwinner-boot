#include "iep_drc.h"
#include "iep_drc_ebios.h"
#include "iep_drc_tab.h"
#include "../../de/disp_clk.h"
//#include "../de/disp_lcd.h"

static __u32 g_drc_clk_status;

static __hdle h_drcahbclk0, h_drcdramclk0, h_drcmclk0, h_drcahbclk1, h_drcdramclk1, h_drcmclk1;
static __drc_t giep[2];	//DRC module parameters
static __drc_pwrsv_t gpwrsv[2];	//Power Saving algorithm parameters
static __u32 *pttab[2];   //POINTER of LGC tab
static __u32 printf_cnt=0; //for test
static __u32 g_iep_status[2] = {0,0};

//power save core 
#define SCENE_CHNG_THR   45	//
#define SCENE_CHANGE_DETECT_DISABLE 1	//enable detetion cause filcker in actual ic test 111230, so disable it.

#define CLK_ON 1
#define CLK_OFF 0
#define RST_INVAILD 0
#define RST_VAILD   1

//#define DRC_DEFAULT_ENABLE	//Enable drc default
//#define DRC_DEMO_HALF_SCREEN //when defined DRC_DEFAULT_ENABLE, run DRC in DEMO mode 		
#define PWRSAVE_PROC_THRES	85 //when BSP_disp_lcd_get_bright() exceed PWRSAVE_PROC_THRES, STOP PWRSAVE.

#define ____SEPARATOR_DRC_CLK____
__s32 drc_clk_init(__u32 sel)
{
	__u32 dram_pll;
	
	if(!sel)
	{
	    h_drcahbclk0 = OSAL_CCMU_OpenMclk(AHB_CLK_DRC0);
	    h_drcdramclk0 = OSAL_CCMU_OpenMclk(DRAM_CLK_DRC0);
	    h_drcmclk0 = OSAL_CCMU_OpenMclk(MOD_CLK_IEPDRC0);

		OSAL_CCMU_MclkReset(h_drcmclk0, RST_INVAILD);

		OSAL_CCMU_SetMclkSrc(h_drcmclk0, SYS_CLK_PLL6);

		dram_pll = OSAL_CCMU_GetSrcFreq(SYS_CLK_PLL6);
		if(dram_pll < 300000000)
		{
			OSAL_CCMU_SetMclkDiv(h_drcmclk0, 1);
		}
		else
		{
			OSAL_CCMU_SetMclkDiv(h_drcmclk0, 2);
		}
		
		OSAL_CCMU_MclkOnOff(h_drcahbclk0, CLK_ON);
		OSAL_CCMU_MclkOnOff(h_drcmclk0, CLK_ON);
		
		g_drc_clk_status  |= (CLK_DRC0_AHB_ON | CLK_DRC0_MOD_ON);
	}
	else
	{
		h_drcahbclk1 = OSAL_CCMU_OpenMclk(AHB_CLK_DRC1);
	    h_drcdramclk1 = OSAL_CCMU_OpenMclk(DRAM_CLK_DRC1);
	    h_drcmclk1 = OSAL_CCMU_OpenMclk(MOD_CLK_IEPDRC1);

		OSAL_CCMU_MclkReset(h_drcmclk1, RST_INVAILD);

		OSAL_CCMU_SetMclkSrc(h_drcmclk1, SYS_CLK_PLL6);
		
		dram_pll = OSAL_CCMU_GetSrcFreq(SYS_CLK_PLL6);
		if(dram_pll < 300000000)
		{
			OSAL_CCMU_SetMclkDiv(h_drcmclk1, 1);
		}
		else
		{
			OSAL_CCMU_SetMclkDiv(h_drcmclk1, 2);
		}
				
		OSAL_CCMU_MclkOnOff(h_drcahbclk1, CLK_ON);
		OSAL_CCMU_MclkOnOff(h_drcmclk1, CLK_ON);
		
		g_drc_clk_status  |= (CLK_DRC1_AHB_ON | CLK_DRC1_MOD_ON);
	}
	return DIS_SUCCESS;
}

__s32 drc_clk_exit(__u32 sel)
{
	if(!sel)
	{
		OSAL_CCMU_MclkReset(h_drcmclk0, RST_VAILD);

		if(g_drc_clk_status & CLK_DRC0_DRAM_ON)
		{
			OSAL_CCMU_MclkOnOff(h_drcdramclk0, CLK_OFF);
		}
		
		if(g_drc_clk_status & CLK_DRC0_MOD_ON)
		{
			OSAL_CCMU_MclkOnOff(h_drcmclk0, CLK_OFF);
		}
		
		if(g_drc_clk_status & CLK_DRC0_AHB_ON)
		{
			OSAL_CCMU_MclkOnOff(h_drcahbclk0, CLK_OFF);
		}

		OSAL_CCMU_CloseMclk(h_drcahbclk0);
	    OSAL_CCMU_CloseMclk(h_drcdramclk0);
	    OSAL_CCMU_CloseMclk(h_drcmclk0);					

		g_drc_clk_status &= (CLK_DRC0_AHB_OFF & CLK_DRC0_MOD_OFF & CLK_DRC0_DRAM_OFF);
	}
	else
	{
		OSAL_CCMU_MclkReset(h_drcmclk1, RST_VAILD);

		if(g_drc_clk_status & CLK_DRC1_DRAM_ON)
		{
			OSAL_CCMU_MclkOnOff(h_drcdramclk1, CLK_OFF);
		}
		
		if(g_drc_clk_status & CLK_DRC1_MOD_ON)
		{
			OSAL_CCMU_MclkOnOff(h_drcmclk1, CLK_OFF);
		}
		
		if(g_drc_clk_status & CLK_DRC1_AHB_ON)
		{
			OSAL_CCMU_MclkOnOff(h_drcahbclk1, CLK_OFF);
		}

		OSAL_CCMU_CloseMclk(h_drcahbclk1);
	    OSAL_CCMU_CloseMclk(h_drcdramclk1);
	    OSAL_CCMU_CloseMclk(h_drcmclk1);					

		g_drc_clk_status &= (CLK_DRC1_AHB_OFF & CLK_DRC1_MOD_OFF & CLK_DRC1_DRAM_OFF);
	}
    return DIS_SUCCESS;
}

__s32 drc_clk_open(__u32 sel)
{
	if(!sel)
	{
		OSAL_CCMU_MclkOnOff(h_drcdramclk0, CLK_ON);

		g_drc_clk_status |= (CLK_DRC0_DRAM_ON);
	}
	else
	{
		OSAL_CCMU_MclkOnOff(h_drcdramclk1, CLK_ON);

		g_drc_clk_status |= (CLK_DRC1_DRAM_ON);
	}
	return DIS_SUCCESS;
}

__s32 drc_clk_close(__u32 sel)
{
	if(!sel)
	{
		OSAL_CCMU_MclkOnOff(h_drcdramclk0, CLK_OFF);

		g_drc_clk_status &= (CLK_DRC0_DRAM_OFF);
	}
	else
	{
		OSAL_CCMU_MclkOnOff(h_drcdramclk1, CLK_OFF);

		g_drc_clk_status &= (CLK_DRC1_DRAM_OFF);
	}
	return DIS_SUCCESS;	
}

#define ____SEPARATOR_DRC_MAIN_TASK____

//en : 0-close when vbi
//en : 1- open when vbi
//en : 2-close immediately
__s32 drc_enable(__u32 sel, __u32 en)
{
	switch(en)
	{
		case 0:		
	
			if(g_iep_status[sel] & DRC_USED)
			{
				g_iep_status[sel] |= DRC_NEED_CLOSED;
			}
			else
			{
				DE_INF("[iep_drc.c]DRC hasn't opened yet !\n");
			}
			break;	
			
		case 1:	
			if(g_iep_status[sel] & DRC_REQUIRED)
			{
				//if((gdisp.screen[sel].output_type == DISP_OUTPUT_TYPE_LCD) && (gdisp.screen[sel].status & LCD_ON))
				//{
				if(!(g_iep_status[sel] & DRC_USED))
				{
					drc_init(sel);
					g_iep_status[sel] |= DRC_USED;
					DE_INF("[iep_drc.c]DRC open now!\n");
				}
				else
				{
					DE_INF("[iep_drc.c]DRC has already opened before !\n");
				}
				//}
				//else
				//{
				//	DE_INF("[iep_drc.c]Will OPEN DRC when output to LCD !\n");
				//}
			}
			else
			{
				DE_INF("[iep_drc.c]Run DISP_CMD_DRC_ON will open DRC !\n");
			}
			break;
	
		case 2:	
			if(g_iep_status[sel] & DRC_USED)
			{
				drc_close_proc(sel);
			}
			else
			{
				DE_INF("[iep_drc.c]DRC hasn't opened yet !\n");
			}
			break;

	}
	return DIS_SUCCESS;

}

__s32 drc_init(__u32 sel)
{
	//DRC clk
	drc_clk_open(sel);
	
	//DRC module 		
	DRC_EBIOS_Set_Mode(sel, 2);		
	DRC_EBIOS_Set_Display_Size(sel, giep[sel].scn_width, giep[sel].scn_height);	
	DRC_EBIOS_Drc_Set_Spa_Coeff(sel, spatial_coeff);
	DRC_EBIOS_Drc_Set_Int_Coeff(sel, intensity_coeff);
	DRC_EBIOS_Drc_Adjust_Enable(sel, 0);	//default: no adjust 
	DRC_EBIOS_Drc_Set_Lgc_Autoload_Disable(sel, 0); //default: autoload enable
	DRC_EBIOS_Lh_Set_Mode(sel, 0);	//default: histogram normal mode
	DRC_EBIOS_Lh_Set_Thres(sel, hist_thres_pwrsv);
	
	memset(gpwrsv[sel].min_adj_index_hist, 255, sizeof(__u8)*IEP_LH_PWRSV_NUM);

	giep[sel].drc_win_en = 1;
/*	giep[sel].drc_win.x = 0;
	giep[sel].drc_win.y = 0;		
	giep[sel].drc_win.width = scn_width;		
	giep[sel].drc_win.height = scn_height;*/ //will clear when drc enable actually, but apps dont know when, so delete it.		
	giep[sel].waitframe = 1;	//set 1 to make sure first frame wont get a random lgc table
	giep[sel].runframe = 0;
		
	return DIS_SUCCESS;

}

#define ____SEPARATOR_IEP_DRC_CORE____

/*
*********************************************************************************************************
*                                           PWRSAVE_CORE
*
* Description : PoWeRSAVE alg core
*
* Arguments   : sel		<screen index>        
*		        
* Returns         :     0
*
*Note	       :    power save mode alg.  Dynamic adjust backlight and lgc gain through screen content and user backlight setting
*                               Add SCENE CHANGE DETECT.
*			  Add HANG-UP DETECT: When use PWRSAVE_CORE in LOW referential backlight condiction, backlight will flicker. So STOP use PWRSAVE_CORE.
*
*Date	:       11/12/21
**********************************************************************************************************/
static __inline __s32 PWRSAVE_CORE(__u32 sel)
{
	__u32 i;
	__u32 hist_region_num = 8;
	__u32 histcnt[IEP_LH_INTERVAL_NUM];
	__u32 hist[IEP_LH_INTERVAL_NUM], p95;
	__u32 size=0;
	__u32 min_adj_index;
	__u32 lgcaddr;
	__u32 drc_filter_total=0, drc_filter_tmp=0;

	if(BSP_disp_lcd_get_bright(sel) < PWRSAVE_PROC_THRES)
	{
		memset(gpwrsv[sel].min_adj_index_hist, 255, sizeof(__u8)*IEP_LH_PWRSV_NUM);
		lgcaddr = (__u32)pttab[sel] + ((128-1)<<9);
		lgcaddr = (__u32)OSAL_VAtoPA((void*)lgcaddr);
		DRC_EBIOS_Drc_Set_Lgc_Addr(sel, lgcaddr);	//set "gain=1" tab to lgc

        BSP_disp_lcd_set_bright_dimming(sel, 256);
		BSP_disp_lcd_set_bright(sel, BSP_disp_lcd_get_bright(sel),1);	
			
	}
	else
	{
		p95=0;
		
		hist_region_num = (hist_region_num>8)? 8 : IEP_LH_INTERVAL_NUM;
		
		//read histogram result
		DRC_EBIOS_Lh_Get_Cnt_Rec(sel, histcnt);

		for(i=0; i<IEP_LH_INTERVAL_NUM; i++)
		{
			size += histcnt[i];
		}
		size = (size==0) ? 1 : size;
		
		//calculate some var
		hist[0] = (histcnt[0]*100)/size;
		for (i = 1; i < hist_region_num; i++)
		{
			hist[i] = (histcnt[i]*100)/size + hist[i-1];
		}

		for (i = 0; i< hist_region_num; i++)
		{
			if (hist[i] >= 95)
			{
				p95 = hist_thres_pwrsv[i];
				break;
			}
		}

		if(i == hist_region_num)//sometime, hist[hist_region_num - 1] may less than 95 due to integer calc
		{
			p95 = hist_thres_pwrsv[7];
		}

		min_adj_index = p95;
		
		//__inf("min_adj_index: %d\n", min_adj_index);
		
#if SCENE_CHANGE_DETECT_DISABLE
		for(i = 0; i <IEP_LH_PWRSV_NUM - 1; i++)
		{
			gpwrsv[sel].min_adj_index_hist[i] = gpwrsv[sel].min_adj_index_hist[i+1];
		}
		gpwrsv[sel].min_adj_index_hist[IEP_LH_PWRSV_NUM-1] = min_adj_index;
		
		for (i = 0; i <IEP_LH_PWRSV_NUM; i++)
		{
			drc_filter_total += drc_filter[i];
			drc_filter_tmp += drc_filter[i]*gpwrsv[sel].min_adj_index_hist[i];
		}
		min_adj_index = drc_filter_tmp/drc_filter_total;
#else
		//ADD frame average alg
		//SCENE CHANGE DETECT
		if (abs((__s32)min_adj_index - gpwrsv[sel].min_adj_index_hist[IEP_LH_PWRSV_NUM - 1]) > SCENE_CHNG_THR)
		{
			memset(gpwrsv[sel].min_adj_index_hist, min_adj_index, sizeof(__u8)*IEP_LH_PWRSV_NUM);
		}
		else
		{
			//store new gain index, shift history data
			for(i = 0; i <IEP_LH_PWRSV_NUM - 1; i++)
			{
				gpwrsv[sel].min_adj_index_hist[i] = gpwrsv[sel].min_adj_index_hist[i+1];
			}
			gpwrsv[sel].min_adj_index_hist[IEP_LH_PWRSV_NUM-1] = min_adj_index;
			
			for (i = 0; i <IEP_LH_PWRSV_NUM; i++)
			{
				drc_filter_total += drc_filter[i];
				drc_filter_tmp += drc_filter[i]*gpwrsv[sel].min_adj_index_hist[i];
			}
			min_adj_index = drc_filter_tmp/drc_filter_total;
		}

#endif

		min_adj_index = (min_adj_index >= 255)?255:((min_adj_index<hist_thres_pwrsv[0])?hist_thres_pwrsv[0]:min_adj_index);

        BSP_disp_lcd_set_bright_dimming(sel, min_adj_index+1);
		BSP_disp_lcd_set_bright(sel, BSP_disp_lcd_get_bright(sel), 1);

		//lgcaddr = (__u32)pwrsv_lgc_tab[min_adj_index-128];
		lgcaddr = (__u32)pttab[sel] + ((min_adj_index - 128)<<9);

		if(printf_cnt == 120)
		{
			__inf("save backlight power: %d percent\n", (256 - (__u32)min_adj_index)*100 / 256);
			printf_cnt = 0;
		}
		else
		{
			printf_cnt++;
		}
		
		//virtual to physcal addr
		lgcaddr = (__u32)OSAL_VAtoPA((void*)lgcaddr);
		
		DRC_EBIOS_Drc_Set_Lgc_Addr(sel, lgcaddr);
	}

	return 0;
}


#define ____SEPARATOR_DRC_PROC____
__s32 drc_proc(__u32 sel)
{
	__u32 top, bot, left, right;
	__u32 lgcaddr;
	__u32 csc_mode, drc_mode;

	csc_mode = (giep[sel].video_mode_en)?3:1;
	drc_mode = (giep[sel].video_mode_en==1)?0:1;
	DRC_EBIOS_Drc_Set_Mode(sel, drc_mode);
	
	if(giep[sel].runframe < giep[sel].waitframe)
	{
		//first  frame, wont get the valid histogram, so open a "zero" window
		top = 0;
		bot = 0;
		left = 0;
		right = 0;
		
		DRC_EBIOS_Set_Win_Para(sel, top, bot, left, right);
		DRC_EBIOS_Win_Enable(sel, 1);		//enable here
		DRC_EBIOS_Set_Csc_Coeff(sel, csc_mode);		//12-04-01 debug flicker in LCD opening
		//BSP_disp_set_output_csc(sel, gdisp.screen[sel].output_type, 1);	//TBD
		
		lgcaddr = (__u32)pttab[sel] + ((128-1)<<9);
		lgcaddr = (__u32)OSAL_VAtoPA((void*)lgcaddr);
		DRC_EBIOS_Drc_Set_Lgc_Addr(sel, lgcaddr);	//set "gain=1" tab to lgc
		DRC_EBIOS_Enable(sel);  //enable here		
		//DE_INF("waitting for runframe %d up to%d!\n", giep.runframe, giep.waitframe);
		giep[sel].runframe++;
	}
	else
	{
		DRC_EBIOS_Set_Csc_Coeff(sel, csc_mode);	//flicker when mode change??
		if(giep[sel].drc_win_en)
		{
			//convert rectangle to register
			top = giep[sel].drc_win.y;
			bot = giep[sel].drc_win.y + giep[sel].drc_win.height - 1;
			left = giep[sel].drc_win.x;
			right = giep[sel].drc_win.x + giep[sel].drc_win.width - 1;

			DRC_EBIOS_Set_Win_Para(sel, top, bot, left, right);
		}
		//BACKLIGHT Control ALG
		PWRSAVE_CORE(sel);
	}

	return DIS_SUCCESS;

}

__s32 drc_close_proc(__u32 sel)
{	

	//DRC module
	DRC_EBIOS_Disable(sel);
	
	//another module
    //BSP_disp_set_output_csc(sel, gdisp.screen[sel].output_type, 0);	//TBD

	//DRC clk
	drc_clk_close(sel);
	
	g_iep_status[sel] &= DRC_USED_MASK;
	g_iep_status[sel] &= DRC_NEED_CLOSED_MASK;

	 BSP_disp_lcd_set_bright_dimming(sel, 256);
	BSP_disp_lcd_set_bright(sel, BSP_disp_lcd_get_bright(sel), 1);
	return DIS_SUCCESS;

}

#define ____SEPARATOR_DRC_BSP____
__s32 IEP_Drc_Init(__u32 sel)
{
#ifdef DRC_DEFAULT_ENABLE
	__disp_rect_t regn;
#endif
	__u32 lcdgamma;
	int  value = 1;
	char primary_key[20];
	int  ret;

	memset(&giep[sel], 0, sizeof(__drc_t));
	memset(&gpwrsv[sel], 0, sizeof(__drc_pwrsv_t));

	drc_clk_init(sel);
	pttab[sel] = OSAL_PhyAlloc(IEP_LGC_TAB_SIZE);//OSAL_PhyAlloc(IEP_LGC_TAB_SIZE);

	sprintf(primary_key, "lcd%d_para", sel);

	ret = OSAL_Script_FetchParser_Data(primary_key, "lcdgamma4iep", &value, 1);
	if(ret < 0)
	{
		DE_WRN("lcdgamma4iep for lcd%d not exist.\n", sel);
		lcdgamma = 6; //default gamma = 2.2;
	}
	else
	{
		DE_INF("lcdgamma4iep for lcd%d = %d.\n", sel, value);
		if(value > 30 || value < 10)
		{
			DE_WRN("lcdgamma4iep for lcd%d too small or too large. default value 22 will be set. please set it between 10 and 30 to make it valid.\n",sel);
			lcdgamma = 6;//default gamma = 2.2;
		}
		else
		{
			lcdgamma = (value - 10)/2;
		}
	}
#if defined(__LINUX_OSAL__)
	memcpy(pttab[sel], pwrsv_lgc_tab[128*lcdgamma], IEP_LGC_TAB_SIZE);
#endif
	
#ifdef DRC_DEFAULT_ENABLE
#ifdef DRC_DEMO_HALF_SCREEN
	regn.x = BSP_disp_get_screen_width(sel)/2;	//TBD
	regn.y = 0;
	regn.width = BSP_disp_get_screen_width(sel)/2;
	regn.height = BSP_disp_get_screen_height(sel);
#else 
	regn.x = 0;
	regn.y = 0;
	regn.width = BSP_disp_get_screen_width(sel);
	regn.height = BSP_disp_get_screen_height(sel);
#endif
	IEP_Drc_Set_Mode(sel, 0);	//default running HSV mode when default open when DRC_DEFAULT_ENABLE==1
	IEP_Drc_Enable(sel, 1);
	IEP_Drc_Set_Winodw(sel, regn);
#endif

	return DIS_SUCCESS;

}
	
__s32 IEP_Drc_Exit(__u32 sel)
{
	drc_clk_exit(sel);
	OSAL_PhyFree(pttab[sel],IEP_LGC_TAB_SIZE);
	return DIS_SUCCESS;
}

/******************************************************************************/
/*************************IEP_Drc_Enable********************************/
/**����/�ر��Զ�������ƹ���**************************/
/*****************************************************************************/
//en : 0-close when vbi
//en : 1-open when vbi
//en : 2-close immediately, use when close screen
__s32 IEP_Drc_Enable(__u32 sel, __u32 en)
{
	if(en==1)
	{
		g_iep_status[sel] |= DRC_REQUIRED;
	}
	else
	{
		g_iep_status[sel] &= DRC_REQUIRED_MASK;
	}
	
	drc_enable(sel, en);
	
	return DIS_SUCCESS;
}

/******************************************************************************/
/**************************IEP_Drc_Set_Winodw*************************/
/**����DRCģʽ�Ĵ���******************************************/
/******************************************************************************/
__s32 IEP_Drc_Set_Winodw(__u32 sel, __disp_rect_t window)//full screen for default
{
/*
	__u32 scn_width, scn_height;
	
	scn_width = BSP_disp_get_screen_width(sel);	//TBD
    scn_height = BSP_disp_get_screen_height(sel);	//TBD

	if((window.x < 0) || ((window->x + window.width)>scn_width) ||
		(window.y < 0) || ((window->y + window.height)>scn_height))
	{
		DE_WRN("IEP_Drc_Set_Winodw for lcd%d: win_x: %d, win_y: %d, win_width: %d, win_height: %d.\n", sel, window.x, window.y, window.width, window.height);
		DE_WRN("DRC Windows Size Invaild!\n");	
		return DIS_PARA_FAILED;
	}//tbd
*/
	//drc
	memcpy(&giep[sel].drc_win, &window, sizeof(__disp_rect_t)); 
	DE_INF("IEP_Drc_Set_Winodw for lcd%d: drc window win_x: %d, win_y: %d, win_width: %d, win_height: %d.\n", sel, giep[sel].drc_win.x, giep[sel].drc_win.y, giep[sel].drc_win.width, giep[sel].drc_win.height);

	return DIS_SUCCESS;
}

__s32 IEP_Drc_Operation_In_Vblanking(__u32 sel)
{
	if(g_iep_status[sel] & DRC_NEED_CLOSED)
	{
		drc_close_proc(sel);
	}
	else if(g_iep_status[sel] & DRC_USED)
	{
		drc_proc(sel);
	}
	
	return DIS_SUCCESS;
}

__s32 IEP_Drc_Set_Reg_Base(__u32 sel, __u32 base)
{

	DRC_EBIOS_Set_Reg_Base(sel, base);
	return DIS_SUCCESS;
	
}

__s32 IEP_Drc_Set_Mode(__u32 sel, __iep_drc_mode_t mode)
{

	giep[sel].video_mode_en = mode;
    
	return DIS_SUCCESS;
	
}

__s32 IEP_Drc_Early_Suspend(__u32 sel)//close clk
{
	drc_clk_exit( sel);
	return DIS_SUCCESS;
}

__s32 IEP_Drc_suspend(__u32 sel)//save register
{
	return DIS_SUCCESS;
}

__s32 IEP_Drc_Resume (__u32 sel)//restore register
{
	return DIS_SUCCESS;
}

__s32 IEP_Drc_Late_Resume(__u32 sel)//open clk
{
	return DIS_SUCCESS;
}

__s32 IEP_Drc_Set_Imgsize(__u32 sel, __u32 width, __u32 height)
{
    giep[sel].scn_width = width;
    giep[sel].scn_height = height;

    DRC_EBIOS_Set_Display_Size(sel, giep[sel].scn_width, giep[sel].scn_height);

    return DIS_SUCCESS;
}
