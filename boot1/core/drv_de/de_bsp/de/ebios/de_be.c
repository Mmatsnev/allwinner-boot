#include "de_be.h"
#include "de_fe.h"

__u32 image_reg_base[2] = {0,0};//DISE_REGS_BASE;

__u32  csc_tab[192] = 
{
    //Y/G   Y/G      Y/G      Y/G      U/R      U/R     U/R        U/R     V/B      V/B       V/B       V/B
    //bt601
	0x04a8,0x1e70,0x1cbf,0x0878,0x04a8,0x0000,0x0662,0x3211,0x04a8,0x0812,0x0000,0x2eb1,//yuv2rgb	//worked 12-02-09
    0x0400,0x0000,0x0000,0x0000,0x0000,0x0400,0x0000,0x0000,0x0000,0x0000,0x0400,0x0000,//yuv2yuv
    0x0400,0x0000,0x0000,0x0000,0x0000,0x0400,0x0000,0x0000,0x0000,0x0000,0x0400,0x0000,//rgb2rgb
    0x0204,0x0107,0x0064,0x0100,0x1ed6,0x1f68,0x01c1,0x0800,0x1e87,0x01c1,0x1fb7,0x0800,//rgb2yuv

    //bt709
    0x04a7,0x1f25,0x1ddd,0x04cf,0x04a7,0x0000,0x072c,0x307d,0x04a7,0x0875,0x0000,0x2dea,//yuv2rgb
    0x0400,0x0000,0x0000,0x0000,0x0000,0x0400,0x0000,0x0000,0x0000,0x0000,0x0400,0x0000,//yuv2yuv
    0x0400,0x0000,0x0000,0x0000,0x0000,0x0400,0x0000,0x0000,0x0000,0x0000,0x0400,0x0000,//rgb2rgb
    0x0274,0x00bb,0x003f,0x0100,0x1ea5,0x1f98,0x01c1,0x0800,0x1e67,0x01c1,0x1fd7,0x0800,//rgb2yuv

    //DISP_YCC
    0x0400,0x1e9e,0x1d24,0x087b,0x0400,0x0000,0x059b,0x34c8,0x0400,0x0715,0x0000,0x31d4,//yuv2rgb
    0x0400,0x0000,0x0000,0x0000,0x0000,0x0400,0x0000,0x0000,0x0000,0x0000,0x0400,0x0000,//yuv2yuv
    0x0400,0x0000,0x0000,0x0000,0x0000,0x0400,0x0000,0x0000,0x0000,0x0000,0x0400,0x0000,//rgb2rgb
    0x0258,0x0132,0x0075,0x0000,0x1eac,0x1f53,0x0200,0x0800,0x1e53,0x0200,0x1fac,0x0800,//rgb2yuv

    //xvYCC
    0x04a7,0x1f25,0x1ddd,0x04cf,0x04a7,0x0000,0x072c,0x307d,0x04a7,0x0875,0x0000,0x2dea,//yuv2rgb
    0x0400,0x0000,0x0000,0x0000,0x0000,0x0400,0x0000,0x0000,0x0000,0x0000,0x0400,0x0000,//yuv2yuv
    0x0400,0x0000,0x0000,0x0000,0x0000,0x0400,0x0000,0x0000,0x0000,0x0000,0x0400,0x0000,//rgb2rgb
    0x0274,0x00bb,0x003f,0x0100,0x1ea5,0x1f98,0x01c1,0x0800,0x1e67,0x01c1,0x1fd7,0x0800 //rgb2yuv
};

__u32  image_enhance_tab[256] = 
{
	//bt601(CONSTANT and COEFFICIENT in 12bit fraction)
	0x0000041D,0x00000810,0x00000191,0x00010000,0xFFFFFDA2,0xFFFFFB58,0x00000706,0x00080000,
	0x00000706,0xFFFFFA1D,0xFFFFFEDD,0x00080000,0x00000000,0x00000000,0x00000000,0x00001000,
	0x000012A0,0x00000000,0x00001989,0xFFF21168,0x000012A0,0xFFFFF9BE,0xFFFFF2FE,0x000877CF,
	0x000012A0,0x0000204A,0x00000000,0xFFEEB127,0x00000000,0x00000000,0x00000000,0x00001000,
	//bt709(CONSTANT and COEFFICIENT in 12bit fraction)
	0x000002EE,0x000009D3,0x000000FE,0x00010000,0xfffffe62,0xfffffA98,0x00000706,0x00080000,
	0x00000706,0xfffff99E,0xffffff5C,0x00080000,0x00000000,0x00000000,0x00000000,0x00001000,
	0x000012A0,0x00000000,0x00001CB0,0xFFF07DF4,0x000012A0,0xfffffC98,0xfffff775,0x0004CFDF,
	0x000012A0,0x000021D7,0x00000000,0xFFEDEA7F,0x00000000,0x00000000,0x00000000,0x00001000,
	//YCC(CONSTANT and COEFFICIENT in 12bit fraction)
	0x000004C8,0x00000963,0x000001D5,0x00000000,0xFFFFFD4D,0xFFFFFAB3,0x00000800,0x00080000,
	0x00000800,0xFFFFF94F,0xFFFFFEB2,0x00080000,0x00000000,0x00000000,0x00000000,0x00001000,
	0x00001000,0x00000000,0x0000166F,0xFFF4C84B,0x00001000,0xFFFFFA78,0xFFFFF491,0x00087B16,
	0x00001000,0x00001C56,0x00000000,0xFFF1D4FE,0x00000000,0x00000000,0x00000000,0x00001000,
	//Dedicated CSC for DRC(CONSTANT and COEFFICIENT in 12bit fraction)
	0x0000030A,0x00000A66,0x0000028F,0x00000000,0xFFFFFE31,0xFFFFF9CF,0x00000800,0x00080000,
	0x00000800,0xFFFFF995,0xFFFFFE6B,0x00080000,0x00000000,0x00000000,0x00000000,0x00001000,
	0x00001000,0x00000000,0x000019EC,0xFFF30A3D,0x00001000,0xFFFFF962,0xFFFFF86D,0x000718BC,
	0x00001000,0x00001AE1,0x00000000,0xFFF28F5C,0x00000000,0x00000000,0x00000000,0x00001000,
    //sin table
    0xffffffbd,0xffffffbf,0xffffffc1,0xffffffc2,0xffffffc4,0xffffffc6,0xffffffc8,0xffffffca,
    0xffffffcc,0xffffffce,0xffffffd1,0xffffffd3,0xffffffd5,0xffffffd7,0xffffffd9,0xffffffdb,
    0xffffffdd,0xffffffdf,0xffffffe2,0xffffffe4,0xffffffe6,0xffffffe8,0xffffffea,0xffffffec,
    0xffffffef,0xfffffff1,0xfffffff3,0xfffffff5,0xfffffff8,0xfffffffa,0xfffffffc,0xfffffffe,
    0x00000000,0x00000002,0x00000004,0x00000006,0x00000008,0x0000000b,0x0000000d,0x0000000f,
    0x00000011,0x00000014,0x00000016,0x00000018,0x0000001a,0x0000001c,0x0000001e,0x00000021,
    0x00000023,0x00000025,0x00000027,0x00000029,0x0000002b,0x0000002d,0x0000002f,0x00000032,
    0x00000034,0x00000036,0x00000038,0x0000003a,0x0000003c,0x0000003e,0x0000003f,0x00000041,
    //cos table
    0x0000006c,0x0000006d,0x0000006e,0x0000006f,0x00000071,0x00000072,0x00000073,0x00000074,
    0x00000074,0x00000075,0x00000076,0x00000077,0x00000078,0x00000079,0x00000079,0x0000007a,
    0x0000007b,0x0000007b,0x0000007c,0x0000007c,0x0000007d,0x0000007d,0x0000007e,0x0000007e,
    0x0000007e,0x0000007f,0x0000007f,0x0000007f,0x0000007f,0x0000007f,0x0000007f,0x0000007f,
    0x00000080,0x0000007f,0x0000007f,0x0000007f,0x0000007f,0x0000007f,0x0000007f,0x0000007f,
    0x0000007e,0x0000007e,0x0000007e,0x0000007d,0x0000007d,0x0000007c,0x0000007c,0x0000007b,
    0x0000007b,0x0000007a,0x00000079,0x00000079,0x00000078,0x00000077,0x00000076,0x00000075,
    0x00000074,0x00000074,0x00000073,0x00000072,0x00000071,0x0000006f,0x0000006e,0x0000006d
};


__s32 DE_Set_Reg_Base(__u32 sel, __u32 address)
{
	image_reg_base[sel] = address;
	// memset((void*)(image0_reg_base+0x800), 0,0x1000-0x800); 
	    	
	return 0;
}

__u32 DE_Get_Reg_Base(__u32 sel)
{

   return image_reg_base[sel];

}

__u32 DE_BE_Reg_Init(__u32 sel)
{
	memset((void*)(image_reg_base[sel]+0x800), 0,0x1000-0x800); 

	return 0;
}

__s32 DE_BE_Set_SystemPalette(__u32 sel, __u32 * pbuffer, __u32 offset,__u32 size)
{
	__u32 *pdest_end;
    __u32 *psrc_cur;
    __u32 *pdest_cur;

    if(size > DE_BE_PALETTE_TABLE_SIZE)
    {
        size = DE_BE_PALETTE_TABLE_SIZE;
    }
    
	psrc_cur = pbuffer;
	pdest_cur = (__u32*)(DE_Get_Reg_Base(sel)+DE_BE_PALETTE_TABLE_ADDR_OFF  + offset);
	pdest_end = pdest_cur + (size>>2);

    while(pdest_cur < pdest_end)
    {
    	*(volatile __u32 *)pdest_cur++ = *psrc_cur++;
    }
    
   return 0;
}

__s32 DE_BE_Get_SystemPalette(__u32 sel, __u32 *pbuffer, __u32 offset,__u32 size)
{
	__u32 *pdest_end;
    __u32 *psrc_cur;
    __u32 *pdest_cur;

    if(size > DE_BE_PALETTE_TABLE_SIZE)
    {
        size = DE_BE_PALETTE_TABLE_SIZE;
    }
	
	psrc_cur = (__u32*)(DE_Get_Reg_Base(sel)+DE_BE_PALETTE_TABLE_ADDR_OFF + offset);
	pdest_cur = pbuffer;
	pdest_end = pdest_cur + (size>>2);
	
    while(pdest_cur < pdest_end)
    {
    	*(volatile __u32 *)pdest_cur++ = *psrc_cur++;
    }

    return 0;	
}

__s32 DE_BE_Enable(__u32 sel)
{
    DE_BE_WUINT32(sel,DE_BE_MODE_CTL_OFF,DE_BE_RUINT32(sel, DE_BE_MODE_CTL_OFF) | (0x01<<1));//start
    DE_BE_WUINT32(sel,DE_BE_MODE_CTL_OFF,DE_BE_RUINT32(sel, DE_BE_MODE_CTL_OFF) | 0x01);//enable  
    
    return 0;
}   

__s32 DE_BE_Disable(__u32 sel)
{
    DE_BE_WUINT32(sel,DE_BE_MODE_CTL_OFF,DE_BE_RUINT32(sel, DE_BE_MODE_CTL_OFF) & 0xfffffffd);//reset
    DE_BE_WUINT32(sel,DE_BE_MODE_CTL_OFF,DE_BE_RUINT32(sel, DE_BE_MODE_CTL_OFF) & 0xfffffffe);//disable

    return 0;
} 

// 0:lcd0 only; 1:lcd1 only
// 2:lcd0+fe0; 3:lcd1+fe0
// 4:lcd0+fe1; 5:lcd1+fe1
// 6:fe0 only;  7:fe1 only
__s32 DE_BE_Output_Select(__u32 sel, __u32 out_sel)
{
    DE_BE_WUINT32(sel,DE_BE_MODE_CTL_OFF,(DE_BE_RUINT32(sel, DE_BE_MODE_CTL_OFF) & 0xff8fffff) | (out_sel << 20));//start

    if((out_sel == 6) || (out_sel == 7))
    {
        DE_BE_WUINT32(sel, DE_BE_ERROR_CORRECTION, 0xffffffff);
    }
    else
    {
        DE_BE_WUINT32(sel, DE_BE_ERROR_CORRECTION, 0);
    }

    return 0;
}   

__s32 DE_BE_Set_BkColor(__u32 sel, __disp_color_t bkcolor)
{
    DE_BE_WUINT32(sel,DE_BE_COLOR_CTL_OFF, (bkcolor.alpha<<24) | (bkcolor.red<<16) | (bkcolor.green<<8) | bkcolor.blue);

    return 0;
}

__s32 DE_BE_Set_ColorKey(__u32 sel, __disp_color_t ck_max,__disp_color_t  ck_min,__u32 ck_red_match, __u32 ck_green_match, __u32 ck_blue_match)
{
    DE_BE_WUINT32(sel,DE_BE_CLRKEY_MAX_OFF,(ck_max.alpha<<24) | (ck_max.red<<16) | (ck_max.green<<8) | ck_max.blue);
    DE_BE_WUINT32(sel,DE_BE_CLRKEY_MIN_OFF,(ck_min.alpha<<24) | (ck_min.red<<16) | (ck_min.green<<8) | ck_min.blue);
    DE_BE_WUINT32(sel,DE_BE_CLRKEY_CFG_OFF,(ck_red_match<<4) | (ck_green_match<<2) | ck_blue_match);
    
    return 0;
}

__s32 DE_BE_reg_auto_load_en(__u32 sel, __u32 en)
{
    __u32 tmp;
    
    tmp = DE_BE_RUINT32(sel, DE_BE_FRMBUF_CTL_OFF);
    DE_BE_WUINT32(sel, DE_BE_FRMBUF_CTL_OFF, tmp | ((1-en)<<1));//bit1:enable, bit0:ready
    
    return 0;
}

__s32 DE_BE_Cfg_Ready(__u32 sel)
{
    __u32 tmp;
    
    tmp = DE_BE_RUINT32(sel, DE_BE_FRMBUF_CTL_OFF);
    DE_BE_WUINT32(sel, DE_BE_FRMBUF_CTL_OFF, tmp | 0x1);//bit1:enable, bit0:ready
    
    return 0;
}


__s32 DE_BE_Sprite_Enable(__u32 sel, __bool enable)
{
	DE_BE_WUINT32(sel, DE_BE_SPRITE_EN_OFF,(DE_BE_RUINT32(sel, DE_BE_SPRITE_EN_OFF)&0xfffffffe) | enable);
	return 0;
}

__s32 DE_BE_Sprite_Disable(__u32 sel)
{
	DE_BE_WUINT32(sel, DE_BE_SPRITE_EN_OFF,DE_BE_RUINT32(sel, DE_BE_SPRITE_EN_OFF)&0xfffffffe);
	return 0;
}

__s32 DE_BE_Sprite_Set_Format(__u32 sel, __u8 pixel_seq,__u8 format)
{
	DE_BE_WUINT32(sel, DE_BE_SPRITE_FORMAT_CTRL_OFF,(pixel_seq<<12)|(format<<8));
	return 0;
}

__s32 DE_BE_Sprite_Global_Alpha_Enable(__u32 sel, __bool enable)
{
	DE_BE_WUINT32(sel, DE_BE_SPRITE_ALPHA_CTRL_OFF,enable);
	return 0;
}

__s32 DE_BE_Sprite_Set_Global_Alpha(__u32 sel, __u8 alpha_val)
{
    __u32 tmp;

    tmp = DE_BE_RUINT32(sel, DE_BE_SPRITE_ALPHA_CTRL_OFF);
    tmp = (tmp & 0x00ffffff) | (alpha_val << 24);
    
	DE_BE_WUINT32(sel, DE_BE_SPRITE_ALPHA_CTRL_OFF,tmp);
	return 0;
}      

__s32 DE_BE_Sprite_Block_Set_Pos(__u32 sel, __u8 blk_idx,__s16 x,__s16 y)
{	
  	DE_BE_WUINT32IDX(sel, DE_BE_SPRITE_POS_CTRL_OFF,blk_idx,((y&0xffff)<<16) | (x&0xffff));
   	return 0;
}

__s32 DE_BE_Sprite_Block_Set_Size(__u32 sel, __u8 blk_idx,__u32 xsize,__u32 ysize)//todo
{
	__u32 tmp = 0;

	tmp = DE_BE_RUINT32IDX(sel, DE_BE_SPRITE_ATTR_CTRL_OFF,blk_idx) & 0x0000003f;
	
	DE_BE_WUINT32IDX(sel, DE_BE_SPRITE_ATTR_CTRL_OFF,blk_idx,tmp | ((ysize-1)<<20) | ((xsize-1)<<8));
	return 0;
}

__s32 DE_BE_Sprite_Block_Set_fb(__u32 sel, __u8 blk_idx,__u32 addr, __u32 line_width)
{
	DE_BE_WUINT32IDX(sel, DE_BE_SPRITE_ADDR_OFF,blk_idx,addr);
	DE_BE_WUINT32IDX(sel, DE_BE_SPRITE_LINE_WIDTH_OFF,blk_idx, line_width<<3);
	return 0;
}

__s32 DE_BE_Sprite_Block_Set_Next_Id(__u32 sel, __u8 blk_idx,__u8 next_blk_id)
{
    __u32 tmp = 0;

    tmp = DE_BE_RUINT32IDX(sel, DE_BE_SPRITE_ATTR_CTRL_OFF,blk_idx) & 0xffffffc0;
	DE_BE_WUINT32IDX(sel, DE_BE_SPRITE_ATTR_CTRL_OFF,blk_idx,tmp | next_blk_id);
	return 0;
}

__s32 DE_BE_Sprite_Set_Palette_Table(__u32 sel, __u32 address, __u32 offset, __u32 size)
{
	__u32 *pdest_end;
    __u32 *psrc_cur;
    __u32 *pdest_cur;

    if(size > DE_BE_SPRITE_PALETTE_TABLE_SIZE)
    {
        size = DE_BE_SPRITE_PALETTE_TABLE_SIZE;
    }

	psrc_cur = (__u32*)address;
	pdest_cur = (__u32*)(DE_Get_Reg_Base(sel) + DE_BE_SPRITE_PALETTE_TABLE_ADDR_OFF + offset);
	pdest_end = pdest_cur + (size>>2);

    while(pdest_cur < pdest_end)
    {
    	*(volatile __u32 *)pdest_cur++ = *psrc_cur++;
    }
    
    return 0;	
}

//out_csc: 0:rgb, 1:yuv for tv, 2:yuv for hdmi, 3: yuv for drc
//out_color_range:  0:16~255, 1:0~255, 2:16~235
__s32 DE_BE_Set_Enhance_ex(__u8 sel, __u32 out_csc, __u32 out_color_range, __u32 enhance_en, __u32 brightness, __u32 contrast, __u32 saturaion, __u32 hue)
{
#if 0
	__s32 i_bright;
	__s32 i_contrast;
	__s32 i_saturaion;
	__s32 i_hue;	//fix
	__scal_matrix4x4 matrixEn;
	__scal_matrix4x4 matrixconv, *ptmatrix;
	__scal_matrix4x4 matrixresult;
	__s64 *pt;
	__s32 sinv, cosv;	//sin_tab: 7 bit fractional
	__s32 i;
	__scal_matrix4x4 tmpcoeff;
    
	brightness = brightness>100?100:(brightness<0?0:brightness);
	contrast = contrast>100?100:(contrast<0?0:contrast);
	saturaion = saturaion>100?100:(saturaion<0?0:saturaion);

	i_bright = (__s32)(brightness*64/100);
	i_saturaion = (__s32)(saturaion*64/100);
	i_contrast = (__s32)(contrast*64/100);
	i_hue = (__s32)(hue*64/100);

	sinv = image_enhance_tab[8*16 + (i_hue&0x3f)];
	cosv = image_enhance_tab[8*16 + 8*8 + (i_hue&0x3f)];

	//calculate enhance matrix
	matrixEn.x00 = i_contrast << 5;
	matrixEn.x01 = 0;
	matrixEn.x02 = 0;
	matrixEn.x03 = (((i_bright - 32) + 16) <<10) - ( i_contrast << 9);
	matrixEn.x10 = 0;
	matrixEn.x11 = (i_contrast * i_saturaion * cosv) >> 7;
	matrixEn.x12 = (i_contrast * i_saturaion * sinv) >> 7;
	matrixEn.x13 = (1<<17) - ((matrixEn.x11 + matrixEn.x12)<<7);
	matrixEn.x20 = 0;
	matrixEn.x21 = (-i_contrast * i_saturaion * sinv)>>7;
	matrixEn.x22 = (i_contrast * i_saturaion * cosv) >> 7;
	matrixEn.x23 = (1<<17) - ((matrixEn.x22 + matrixEn.x21)<<7);
	matrixEn.x30 = 0;
	matrixEn.x31 = 0;
	matrixEn.x32 = 0;
	matrixEn.x33 = 1024;

	if(out_csc == 0)	//RGB output
	{
		if(enhance_en == 1)
		{
			for(i=0; i<16; i++)
			{	
				*((__s64 *)(&tmpcoeff.x00) + i) = ((__s64)*(image_enhance_tab + 0x20 + i) <<32 ) >>32;	//bt709 rgb2yuv coeff
				// *((__s64 *)(&tmpcoeff.x00) + i) = ((__s64)*(image_enhance_tab + i) <<32 ) >>32;	//bt601 rgb2yuv coeff
				// *((__s64 *)(&tmpcoeff.x00) + i) = ((__s64)*(image_enhance_tab + 0x40 + i) <<32 ) >>32;	//YCC rgb2yuv coeff
			}
		
			ptmatrix = &tmpcoeff;
			
			//convolution of enhance matrix and rgb2yuv matrix
			iDE_SCAL_Matrix_Mul(matrixEn, *ptmatrix, &matrixconv);
		
			for(i=0; i<16; i++)
			{	
				*((__s64 *)(&tmpcoeff.x00) + i) = ((__s64)*(image_enhance_tab + 0x30 + i) <<32)>>32;	//bt709 yuv2rgb coeff
				// *((__s64 *)(&tmpcoeff.x00) + i) = ((__s64)*(image_enhance_tab + 0x10 + i) <<32)>>32;	//bt601 yuv2rgb coeff
				// *((__s64 *)(&tmpcoeff.x00) + i) = ((__s64)*(image_enhance_tab + 0x50 + i) <<32)>>32;	//YCC yuv2rgb coeff
			}
						
			ptmatrix = &tmpcoeff;
			
			//convert to RGB
			iDE_SCAL_Matrix_Mul(*ptmatrix, matrixconv, &matrixconv);
	
			//rearrange CSC coeff
			matrixresult.x00 = (matrixconv.x00+8)/16;	matrixresult.x01 = (matrixconv.x01+8)/16;
			matrixresult.x02 = (matrixconv.x02+8)/16;	matrixresult.x03 = (matrixconv.x03+512)/1024;
			matrixresult.x10 = (matrixconv.x10+8)/16;	matrixresult.x11 = (matrixconv.x11+8)/16;
			matrixresult.x12 = (matrixconv.x12+8)/16;	matrixresult.x13 = (matrixconv.x13+512)/1024;
			matrixresult.x20 = (matrixconv.x20+8)/16;	matrixresult.x21 = (matrixconv.x21+8)/16;
			matrixresult.x22 = (matrixconv.x22+8)/16;	matrixresult.x23 = (matrixconv.x23+512)/1024;
			matrixresult.x30 = (matrixconv.x30+8)/16;	matrixresult.x31 = (matrixconv.x31+8)/16;
			matrixresult.x32 = (matrixconv.x32+8)/16;	matrixresult.x33 = (matrixconv.x33+512)/1024;
		}
		else
		{
			matrixresult.x00 = 0x400;	matrixresult.x01 = 0;
			matrixresult.x02 = 0;		matrixresult.x03 = 0;
			matrixresult.x10 = 0;		matrixresult.x11 = 0x400;
			matrixresult.x12 = 0;		matrixresult.x13 = 0;
			matrixresult.x20 = 0;		matrixresult.x21 = 0;
			matrixresult.x22 = 0x400;	matrixresult.x23 = 0;
			matrixresult.x30 = 0;		matrixresult.x31 = 0;
			matrixresult.x32 = 0;		matrixresult.x33 = 0x400;
		}
		
		//OUTPUT RANGE MODIFY
		ptmatrix = &matrixresult;
		
		if(out_color_range == DISP_COLOR_RANGE_16_255)
        {
        	matrixconv.x00 = 0x03c4;				matrixconv.x01 = 0x0000;
			matrixconv.x02 = 0x0000;				matrixconv.x03 = 0x0100;
			matrixconv.x10 = 0x0000;				matrixconv.x11 = 0x03c4;
			matrixconv.x12 = 0x0000;				matrixconv.x13 = 0x0100;
			matrixconv.x20 = 0x0000;				matrixconv.x21 = 0x0000;
			matrixconv.x22 = 0x03c4;				matrixconv.x23 = 0x0100;
			matrixconv.x30 = 0x0000;				matrixconv.x31 = 0x0000;
			matrixconv.x32 = 0x0000;				matrixconv.x33 = 0x0100;
	    }
	    else if(out_color_range == DISP_COLOR_RANGE_16_235)
	    {
        	matrixconv.x00 = 0x0370;				matrixconv.x01 = 0x0000;
			matrixconv.x02 = 0x0000;				matrixconv.x03 = 0x0100;
			matrixconv.x10 = 0x0000;				matrixconv.x11 = 0x0370;
			matrixconv.x12 = 0x0000;				matrixconv.x13 = 0x0100;
			matrixconv.x20 = 0x0000;				matrixconv.x21 = 0x0000;
			matrixconv.x22 = 0x0370;				matrixconv.x23 = 0x0100;
		}
		else	//DISP_COLOR_RANGE_0_255
		{
			matrixconv.x00 = 0x0400;				matrixconv.x01 = 0x0000;
			matrixconv.x02 = 0x0000;				matrixconv.x03 = 0x0000;
			matrixconv.x10 = 0x0000;				matrixconv.x11 = 0x0400;
			matrixconv.x12 = 0x0000;				matrixconv.x13 = 0x0000;
			matrixconv.x20 = 0x0000;				matrixconv.x21 = 0x0000;
			matrixconv.x22 = 0x0400;				matrixconv.x23 = 0x0000;
		}

		iDE_SCAL_Matrix_Mul(matrixconv, *ptmatrix, &matrixresult);

		matrixresult.x00 = matrixresult.x00;	matrixresult.x01 = matrixresult.x01;
		matrixresult.x02 = matrixresult.x02;	matrixresult.x03 = matrixresult.x03 + 8;
		matrixresult.x10 = matrixresult.x10;	matrixresult.x11 = matrixresult.x11;
		matrixresult.x12 = matrixresult.x12;	matrixresult.x13 = matrixresult.x13 + 8;
		matrixresult.x20 = matrixresult.x20;	matrixresult.x21 = matrixresult.x21;
		matrixresult.x22 = matrixresult.x22;	matrixresult.x23 = matrixresult.x23 + 8;
	}
			
	else if(out_csc == 1)	//YUV for tv(range 16-235)
	{
        for(i=0; i<16; i++)
        {   
            *((__s64 *)(&tmpcoeff.x00) + i)  = ((__s64)*(image_enhance_tab + i) <<32)>>32;  //bt601 rgb2yuv coeff
        }
    
        if(enhance_en == 1)
        {
            //convolution of enhance matrix and rgb2yuv matrix

            ptmatrix = &tmpcoeff;
        
            iDE_SCAL_Matrix_Mul(matrixEn, *ptmatrix, &matrixconv);
            
            matrixresult.x00 = matrixconv.x00/4;    matrixresult.x01 = matrixconv.x01/4;
            matrixresult.x02 = matrixconv.x02/4;    matrixresult.x03 = matrixconv.x03/256 + 8;
            matrixresult.x10 = matrixconv.x10/4;    matrixresult.x11 = matrixconv.x11/4;
            matrixresult.x12 = matrixconv.x12/4;    matrixresult.x13 = matrixconv.x13/256 + 8;
            matrixresult.x20 = matrixconv.x20/4;    matrixresult.x21 = matrixconv.x21/4;
            matrixresult.x22 = matrixconv.x22/4;    matrixresult.x23 = matrixconv.x23/256 + 8;
        }
        else
        {
            matrixresult.x00 = tmpcoeff.x00/4;  matrixresult.x01 = tmpcoeff.x01/4;
            matrixresult.x02 = tmpcoeff.x02/4;  matrixresult.x03 = tmpcoeff.x03/256 + 8;
            matrixresult.x10 = tmpcoeff.x10/4;  matrixresult.x11 = tmpcoeff.x11/4;
            matrixresult.x12 = tmpcoeff.x12/4;  matrixresult.x13 = tmpcoeff.x13/256 + 8;
            matrixresult.x20 = tmpcoeff.x20/4;  matrixresult.x21 = tmpcoeff.x21/4;
            matrixresult.x22 = tmpcoeff.x22/4;  matrixresult.x23 = tmpcoeff.x23/256 + 8;
        }
    }
	else if(out_csc == 2)//YUV for HDMI(range 16-235)
	{
		for(i=0; i<16; i++)
		{	
			*((__s64 *)(&tmpcoeff.x00) + i)  = ((__s64)*(image_enhance_tab + i) <<32)>>32;	//bt601 rgb2yuv coeff
		}
			
		if(enhance_en == 1)
		{
			//convolution of enhance matrix and rgb2yuv matrix

			ptmatrix = &tmpcoeff;
		
			iDE_SCAL_Matrix_Mul(matrixEn, *ptmatrix, &matrixconv);
			
			matrixresult.x00 = matrixconv.x20/4;	matrixresult.x01 = matrixconv.x21/4;
			matrixresult.x02 = matrixconv.x22/4;	matrixresult.x03 = matrixconv.x23/256 + 8;
			matrixresult.x10 = matrixconv.x00/4;	matrixresult.x11 = matrixconv.x01/4;
			matrixresult.x12 = matrixconv.x02/4;	matrixresult.x13 = matrixconv.x03/256 + 8;
			matrixresult.x20 = matrixconv.x10/4;	matrixresult.x21 = matrixconv.x11/4;
			matrixresult.x22 = matrixconv.x12/4;	matrixresult.x23 = matrixconv.x13/256 + 8;
		}
		else
		{
			matrixresult.x00 = tmpcoeff.x20/4;	matrixresult.x01 = tmpcoeff.x21/4;
			matrixresult.x02 = tmpcoeff.x22/4;	matrixresult.x03 = tmpcoeff.x23/256 + 8;
			matrixresult.x10 = tmpcoeff.x00/4;	matrixresult.x11 = tmpcoeff.x01/4;
			matrixresult.x12 = tmpcoeff.x02/4;	matrixresult.x13 = tmpcoeff.x03/256 + 8;
			matrixresult.x20 = tmpcoeff.x10/4;	matrixresult.x21 = tmpcoeff.x11/4;
			matrixresult.x22 = tmpcoeff.x12/4;	matrixresult.x23 = tmpcoeff.x13/256 + 8;
		}
	}
	else //if(out_csc == 3)//YUV for DRC
	{
		for(i=0; i<16; i++)
		{	
			*((__s64 *)(&tmpcoeff.x00) + i)  = ((__s64)*(image_enhance_tab + 0x60 + i) <<32)>>32;	//dedicated rgb2yuv coeff
		}
			
		if(enhance_en == 1)
		{
			//convolution of enhance matrix and rgb2yuv matrix

			ptmatrix = &tmpcoeff;
		
			iDE_SCAL_Matrix_Mul(matrixEn, *ptmatrix, &matrixconv);
			
			matrixresult.x00 = matrixconv.x00/4;	matrixresult.x01 = matrixconv.x01/4;
			matrixresult.x02 = matrixconv.x02/4;	matrixresult.x03 = matrixconv.x03/256 + 8;
			matrixresult.x10 = matrixconv.x10/4;	matrixresult.x11 = matrixconv.x11/4;
			matrixresult.x12 = matrixconv.x12/4;	matrixresult.x13 = matrixconv.x13/256 + 8;
			matrixresult.x20 = matrixconv.x20/4;	matrixresult.x21 = matrixconv.x21/4;
			matrixresult.x22 = matrixconv.x22/4;	matrixresult.x23 = matrixconv.x23/256 + 8;
		}
		else
		{
			matrixresult.x00 = tmpcoeff.x00/4;	matrixresult.x01 = tmpcoeff.x01/4;
			matrixresult.x02 = tmpcoeff.x02/4;	matrixresult.x03 = tmpcoeff.x03/256 + 8;
			matrixresult.x10 = tmpcoeff.x10/4;	matrixresult.x11 = tmpcoeff.x11/4;
			matrixresult.x12 = tmpcoeff.x12/4;	matrixresult.x13 = tmpcoeff.x13/256 + 8;
			matrixresult.x20 = tmpcoeff.x20/4;	matrixresult.x21 = tmpcoeff.x21/4;
			matrixresult.x22 = tmpcoeff.x22/4;	matrixresult.x23 = tmpcoeff.x23/256 + 8;
		}
	}

	//range limited
	iDE_SCAL_Csc_Lmt(&matrixresult.x00, -8191, 8191, 0, 16383);
	iDE_SCAL_Csc_Lmt(&matrixresult.x01, -8191, 8191, 0, 16383);
	iDE_SCAL_Csc_Lmt(&matrixresult.x02, -8191, 8191, 0, 16383);
	iDE_SCAL_Csc_Lmt(&matrixresult.x03, -16383, 16383, 0, 32767);
	iDE_SCAL_Csc_Lmt(&matrixresult.x10, -8191, 8191, 0, 16383);
	iDE_SCAL_Csc_Lmt(&matrixresult.x11, -8191, 8191, 0, 16383);
	iDE_SCAL_Csc_Lmt(&matrixresult.x12, -8191, 8191, 0, 16383);
	iDE_SCAL_Csc_Lmt(&matrixresult.x13, -16383, 16383, 0, 32767);
	iDE_SCAL_Csc_Lmt(&matrixresult.x20, -8191, 8191, 0, 16383);
	iDE_SCAL_Csc_Lmt(&matrixresult.x21, -8191, 8191, 0, 16383);
	iDE_SCAL_Csc_Lmt(&matrixresult.x22, -8191, 8191, 0, 16383);
	iDE_SCAL_Csc_Lmt(&matrixresult.x23, -16383, 16383, 0, 32767);

	pt = (__s64*)&(matrixresult.x00);	
	
	for(i=0;i<4;i++)	
	{		
		DE_BE_WUINT32(sel, DE_BE_OUT_COLOR_R_COEFF_OFF+ 4*i, (__u32 )(*(pt + i)));		
	    DE_BE_WUINT32(sel, DE_BE_OUT_COLOR_G_COEFF_OFF+ 4*i, (__u32 )(*(pt + 4 + i)));		
	    DE_BE_WUINT32(sel, DE_BE_OUT_COLOR_B_COEFF_OFF+ 4*i, (__u32 )(*(pt + 8 + i)));	
	}	

	DE_BE_enhance_enable(sel, 1);
#endif
	return 0;
}

__s32 DE_BE_enhance_enable(__u32 sel, __bool enable)
{
    DE_BE_WUINT32(sel, DE_BE_OUT_COLOR_CTRL_OFF, enable);

    return 0;
}

__s32 DE_BE_deflicker_enable(__u32 sel, __bool enable)
{
	DE_BE_WUINT32(sel, DE_BE_MODE_CTL_OFF,(DE_BE_RUINT32(sel, DE_BE_MODE_CTL_OFF)&(~(1<<4))) | (enable<<4));
	
    return 0;
}

__s32 DE_BE_Set_Outitl_enable(__u32 sel, __bool enable)
{
	DE_BE_WUINT32(sel, DE_BE_MODE_CTL_OFF,(DE_BE_RUINT32(sel, DE_BE_MODE_CTL_OFF)&(~(1<<28))) | (enable<<28));
	
    return 0;
}

__s32 DE_BE_set_display_size(__u32 sel, __u32 width, __u32 height)
{
    DE_BE_WUINT32(sel, DE_BE_DISP_SIZE_OFF, ((height-1)<<16) | (width-1));
    return 0;
}

__s32 DE_BE_get_display_width(__u32 sel)
{
    __u32 tmp;
    
    tmp = DE_BE_RUINT32(sel, DE_BE_DISP_SIZE_OFF) & 0x0000ffff;

    return tmp + 1;
}

__s32 DE_BE_get_display_height(__u32 sel)
{
    __u32 tmp;
    
    tmp = (DE_BE_RUINT32(sel, DE_BE_DISP_SIZE_OFF) & 0xffff0000)>>16;

    return tmp + 1;
}

__s32 DE_BE_EnableINT(__u8 sel,__u32 irqsrc)
{
    __u32 tmp;

    tmp = DE_BE_RUINT32(sel, DE_BE_INT_EN_OFF);
	DE_BE_WUINT32(sel, DE_BE_INT_EN_OFF, tmp | irqsrc);

	return 0;
}

__s32 DE_BE_DisableINT(__u8 sel, __u32 irqsrc)
{
    __u32 tmp;

    tmp = DE_BE_RUINT32(sel, DE_BE_INT_EN_OFF);
	DE_BE_WUINT32(sel, DE_BE_INT_EN_OFF, tmp & (~irqsrc));

	return 0;
}

__u32 DE_BE_QueryINT(__u8 sel)
{	
	__u32 ret = 0;

	ret = DE_BE_RUINT32(sel, DE_BE_INT_FLAG_OFF);
	
	return ret;
}

__u32 DE_BE_ClearINT(__u8 sel,__u32 irqsrc)
{
	DE_BE_WUINT32(sel, DE_BE_INT_FLAG_OFF,irqsrc);
	
	return 0;
}

