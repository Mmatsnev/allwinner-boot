/*
**********************************************************************************************************************
*											        eGon
*						           the Embedded GO-ON Bootloader System
*									       eGON arm boot sub-system
*
*						  Copyright(C), 2006-2010, SoftWinners Microelectronic Co., Ltd.
*                                           All Rights Reserved
*
* File    : nand_boot0_write.c
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
#include "nand_flash.h"
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
__s32  Nand_Burn_Boot0(__u32 Boot0_buf, __u32 length )
{
    __u32 	            i;
	struct boot_flash_info info;
	__u32               pages_per_block;
	__u32               copies_per_block;
	__u8 				nand_version[4];
    __u8  				oob_buf[32];
    __s32				ret = -1;

	memset(oob_buf, 0xff, 32);
    NAND_VersionGet(nand_version);
    *(__s32 *)oob_buf = *(__s32 *)nand_version;

	if( NAND_Init( ) == FAIL )
		return -1;

	if( NAND_GetFlashInfo( &info ) == FAIL )
	{
		goto error;
	}
	/* 检查 page count */
	pages_per_block = info.blocksize / info.pagesize;
	if( pages_per_block%BOOT0_PAGE_ADVANCE != 0 )
	{
		goto error;
	}
	copies_per_block = pages_per_block / BOOT0_PAGE_ADVANCE;
    for( i = BOOT0_START_BLK_NUM;  i <= BOOT0_LAST_BLK_NUM;  i++ )
    {
		struct boot_physical_param  para;
		__u32  j;
		__u32  k;

		/* 擦除块 */
		para.chip  = 0;
		para.block = i;
		if( NAND_PhyErase( &para ) != SUCCESS )
		{
    		continue;
    	}

        /* 在块中烧写boot0备份 */
        for( j = 0;  j < copies_per_block;  j++ )
       	{

			for( k = 0;  k < BOOT0_PAGE_ADVANCE;  k++ )
			{
				para.chip  = 0;
				para.block = i;
				para.page = j * BOOT0_PAGE_ADVANCE + k;
				para.mainbuf = (void *) (Boot0_buf + k * SZ_1K);
				para.oobbuf = oob_buf;
				if( NAND_PhyWrite_1K( &para ) != SUCCESS )
				{
					__inf("NAND_PhyWrite_1K error\n");
				}
				if( NAND_PhyRead_1K( &para ) != SUCCESS )
				{
					__inf("NAND_PhyRead_1K error\n");
				}

       		}
		}
		__inf("burn block %d\n", i);
    }

	ret = 0;

error:
    NAND_PhyExit( );

    return ret;
}






