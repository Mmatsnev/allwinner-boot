//----------------------------------------------------------------------------------------------------------//
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//    I MMMMMMMMMMI                                                                                         //
//      I FF      BBI                                                                                       //
//      I FF      I EE  FFMMFFI MMMMLL  I MMMMMMEE          EEMMBBLLBBFF    FFMMMMBBI   I MMBBBBMMMMI       //
//      I FF        EEI   I BBBBI   I     I     LLFF      EELL  I BBFF    FFFF    I BBI   I BBI   I EE      //
//      I FF        EEI   I FF          I BBMMMMMMFF      FF      I FF  I EE        I LL  I FF      EEI     //
//      I FF      I EE    I FF          EEI     I FF      FF      I FF  I EE        I LL  I FF      EEI     //
//      I FF      FFI     I FF          EEI     BBFF      FFI     EEFF    FFI       FFI   I FF      EEI     //
//    I MMMMMMMMMMFF    BBMMMMMMMMFF    LLMMMMMMFFMMFF    I BBMMMMFFFF    I BBMMMMMMLL  I MMMMFF  BBMMBBI   //
//                                                                I FF                                      //
//                                                                FFLL                                      //
//                                                          BBMMMMEE                                        //
//                                                                                                          //
//                                                                                                          //
//----------------------------------------------------------------------------------------------------------//
//                                                                                                          //
//                                              Dragon System                                               //
//                                                                                                          //
//                               (c) Copyright 2006-2007, Scottyu China                                     //
//                                                                                                          //
//                                           All Rights Reserved                                            //
//                                                                                                          //
// File    : ImgDecode.cpp                                                                                  //
// By      : scottyu                                                                                        //
// Version : V1.00                                                                                          //
// Time    : 2008-11-03 9:57:52                                                                             //
//                                                                                                          //
//----------------------------------------------------------------------------------------------------------//
//                                                                                                          //
// HISTORY                                                                                                  //
//                                                                                                          //
// 1 2008-11-03 9:57:55                                                                                     //
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//----------------------------------------------------------------------------------------------------------//

#include  "../card_sprite_i.h"

#include "imgdecode.h"
#include "imagefile_new.h"

#define HEAD_ID				0		//ͷ���ܽӿ�����
#define TABLE_ID			1		//�����ܽӿ�����
#define DATA_ID				2		//���ݼ��ܽӿ�����
#define IF_CNT				3		//���ܽӿڸ���	����ֻ��ͷ���ܣ������ܣ����ݼ���3��
#define	MAX_KEY_SIZE 		32		//���볤��

#pragma pack(push, 1)
typedef struct tag_IMAGE_HANDLE
{

//	HANDLE  fp;			//

	ImageHead_t  ImageHead;		//imgͷ��Ϣ

	ImageItem_t *ItemTable;		//item��Ϣ��

//	RC_ENDECODE_IF_t rc_if_decode[IF_CNT];//���ܽӿ�

//	BOOL			bWithEncpy; // �Ƿ����
}IMAGE_HANDLE;

#define INVALID_INDEX		0xFFFFFFFF


typedef struct tag_ITEM_HANDLE{
	uint	index;					//��ItemTable�е�����
	uint    reserved[3];
//	long long pos;
}ITEM_HANDLE;

#define ITEM_PHOENIX_TOOLS 	  "PXTOOLS "

uint img_file_start;			//�̼�����ʼλ��
//------------------------------------------------------------------------------------------------------------
//image��������Ľӿ�
//------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------
//
// ����˵��
//
//
// ����˵��
//
//
// ����ֵ
//
//
// ����
//    ��
//
//------------------------------------------------------------------------------------------------------------
HIMAGE 	Img_Open	(__u32 start)
{
	IMAGE_HANDLE * pImage = NULL;
	uint ItemTableSize;					//�̼��������Ĵ�С

//	if(strcmp((const char *)ImageFile, "c:/imgfile"))
//	{
//		__inf("sunxi sprite error: unable to get firmware full path\n");
//
//		return NULL;
//	}

//	img_file_start = sprite_card_firmware_start();
//	if(!img_file_start)
//	{
//		__inf("sunxi sprite error: unable to get firmware start position\n");
//
//		return NULL;
//	}

	img_file_start = start;

	__inf("img start = %x\n", img_file_start);
	pImage = (IMAGE_HANDLE *)wBoot_malloc(sizeof(IMAGE_HANDLE));
	if (NULL == pImage)
	{
		__inf("sunxi sprite error: fail to wBoot_malloc memory for img head\n");

		return NULL;
	}
	memset(pImage, 0, sizeof(IMAGE_HANDLE));
	//------------------------------------------------
	//��imgͷ
	//------------------------------------------------
	//__inf("try to read mmc start %d\n", img_file_start);
	if(wBoot_block_read(img_file_start, IMAGE_HEAD_SIZE/512, &pImage->ImageHead))
	{
		__inf("sunxi sprite error: read image head fail\n");

		goto _img_open_fail_;
	}
	__inf("read mmc ok\n");
	//------------------------------------------------
	//�Ƚ�magic
	//------------------------------------------------
	if (memcmp(pImage->ImageHead.magic, IMAGE_MAGIC, 8) != 0)
	{
		__inf("sunxi sprite error: image magic is bad\n");

		goto _img_open_fail_;
	}
	//------------------------------------------------
	//Ϊ���������ٿռ�
	//------------------------------------------------
	ItemTableSize = pImage->ImageHead.itemcount * sizeof(ImageItem_t);
	pImage->ItemTable = (ImageItem_t*)wBoot_malloc(ItemTableSize);
	if (NULL == pImage->ItemTable)
	{
		__inf("sunxi sprite error: fail to wBoot_malloc memory for item table\n");

		goto _img_open_fail_;
	}
	//------------------------------------------------
	//����������
	//------------------------------------------------
	if(wBoot_block_read(img_file_start + (IMAGE_HEAD_SIZE/512), ItemTableSize/512, pImage->ItemTable))
	{
		__inf("sunxi sprite error: read iamge item table fail\n");

		goto _img_open_fail_;
	}

	return pImage;

_img_open_fail_:
	if(pImage->ItemTable)
	{
		wBoot_free(pImage->ItemTable);
	}
	if(pImage)
	{
		wBoot_free(pImage);
	}

	return NULL;
}



//------------------------------------------------------------------------------------------------------------
//
// ����˵��
//
//
// ����˵��
//
//
// ����ֵ
//
//
// ����
//    ��
//
//------------------------------------------------------------------------------------------------------------
HIMAGEITEM 	Img_OpenItem	(HIMAGE hImage, char * MainType, char * subType)
{
	IMAGE_HANDLE* pImage = (IMAGE_HANDLE *)hImage;
	ITEM_HANDLE * pItem  = NULL;
	uint          i;

	if (NULL == pImage || NULL == MainType || NULL == subType)
	{
		return NULL;
	}

	pItem = (ITEM_HANDLE *) wBoot_malloc(sizeof(ITEM_HANDLE));
	if (NULL == pItem)
	{
		__inf("sunxi sprite error : cannot wBoot_malloc memory for item\n");

		return NULL;
	}
	pItem->index = INVALID_INDEX;

	for (i = 0; i < pImage->ImageHead.itemcount ; i++)
	{
//		int nCmp = memcmp(ITEM_PHOENIX_TOOLS, MainType, MAINTYPE_LEN);
//
//		if (nCmp == 0)//
//		{
//			if (memcmp(MainType, pImage->ItemTable[i].mainType, MAINTYPE_LEN) == 0 )
//			{
//				pItem->index = i;
//
//				return pItem;
//			}
//		}
//		else
//		{
//			nCmp = memcmp(MainType, pImage->ItemTable[i].mainType, MAINTYPE_LEN);
//			if(nCmp == 0)
//			{
//				nCmp = memcmp(subType,  pImage->ItemTable[i].subType,  SUBTYPE_LEN);
//				if( nCmp == 0)
//				{
//					pItem->index = i;
//
//					return pItem;
//				}
//			}
//		}
		if(!memcmp(subType,  pImage->ItemTable[i].subType,  SUBTYPE_LEN))
		{
			pItem->index = i;
			//__inf("try to wBoot_malloc %x\n", (uint)pItem);

			return pItem;
		}
	}

	__inf("sunxi sprite error : cannot find item %s %s\n", MainType, subType);

	wBoot_free(pItem);
	pItem = NULL;

	return NULL;
}



//------------------------------------------------------------------------------------------------------------
//
// ����˵��
//
//
// ����˵��
//
//
// ����ֵ
//
//
// ����
//    ��
//
//------------------------------------------------------------------------------------------------------------
long long Img_GetItemSize	(HIMAGE hImage, HIMAGEITEM hItem)
{
	IMAGE_HANDLE* pImage = (IMAGE_HANDLE *)hImage;
	ITEM_HANDLE * pItem  = (ITEM_HANDLE  *)hItem;
	long long       size;

	if (NULL == pItem)
	{
		__inf("sunxi sprite error : item is NULL\n");

		return 0;
	}

	size = pImage->ItemTable[pItem->index].filelenHi;
	size <<= 32;
	size |= pImage->ItemTable[pItem->index].filelenLo;

	return size;
}

//------------------------------------------------------------------------------------------------------------
//
// ����˵��
//
//
// ����˵��
//
//
// ����ֵ
//
//
// ����
//    ��
//
//------------------------------------------------------------------------------------------------------------
uint Img_GetItemStart	(HIMAGE hImage, HIMAGEITEM hItem)
{
	IMAGE_HANDLE* pImage = (IMAGE_HANDLE *)hImage;
	ITEM_HANDLE * pItem  = (ITEM_HANDLE  *)hItem;
	long long       start;
	long long		offset;

	if (NULL == pItem)
	{
		__inf("sunxi sprite error : item is NULL\n");

		return 0;
	}
	offset = pImage->ItemTable[pItem->index].offsetHi;
	offset <<= 32;
	offset |= pImage->ItemTable[pItem->index].offsetLo;
	start = offset/512;

	return ((uint)start + img_file_start);
}
//------------------------------------------------------------------------------------------------------------
//
// ����˵��
//
//
// ����˵��
//
//
// ����ֵ
//     ����ʵ�ʶ�ȡ���ݵĳ���
//
// ����
//    ��
//
//------------------------------------------------------------------------------------------------------------
#if 0
uint Img_ReadItem(HIMAGE hImage, HIMAGEITEM hItem, void *buffer, uint buffer_size)
{
	IMAGE_HANDLE* pImage = (IMAGE_HANDLE *)hImage;
	ITEM_HANDLE * pItem  = (ITEM_HANDLE  *)hItem;
	long long     start;
	long long	  offset;
	uint	      file_size;
	void          *tmp;

	if (NULL == pItem)
	{
		__inf("sunxi sprite error : item is NULL\n");

		return 0;
	}
	if(pImage->ItemTable[pItem->index].filelenHi)
	{
		__inf("sunxi sprite error : the item too big\n");

		return 0;
	}
	file_size = pImage->ItemTable[pItem->index].filelenLo;
	__inf("file size=%d, buffer size=%d\n", file_size, buffer_size);
	if(file_size > buffer_size)
	{
		__inf("sunxi sprite error : buffer is smaller than data size\n");

		return 0;
	}
	if(file_size > 2 * 1024 * 1024)
	{
		__inf("sunxi sprite error : this function cant be used to read data over 2M bytes\n");

		return 0;
	}
	file_size = (file_size + 1023) & (~(1024 - 1));
	offset = pImage->ItemTable[pItem->index].offsetHi;
	offset <<= 32;
	offset |= pImage->ItemTable[pItem->index].offsetLo;
	start = offset/512;

	__inf("wBoot_malloc size = %d\n", file_size);
	tmp = wBoot_malloc(file_size);
	if(!tmp)
	{
		__inf("sunxi sprite error : fail to get memory for temp data\n");

		return 0;
	}
	if(!wBoot_block_read((uint)start + img_file_start, file_size/512, tmp))
	{
		__inf("sunxi sprite error : read item data failed\n");
		wBoot_free(tmp);

		return 0;
	}
	memcpy(buffer, tmp, buffer_size);
	wBoot_free(tmp);

	return buffer_size;
}
#else
uint Img_ReadItem(HIMAGE hImage, HIMAGEITEM hItem, void *buffer, uint buffer_size)
{
	IMAGE_HANDLE* pImage = (IMAGE_HANDLE *)hImage;
	ITEM_HANDLE * pItem  = (ITEM_HANDLE  *)hItem;
	long long     start;
	long long	  offset;
	uint	      file_size;

	if (NULL == pItem)
	{
		__inf("sunxi sprite error : item is NULL\n");

		return 0;
	}
	if(pImage->ItemTable[pItem->index].filelenHi)
	{
		__inf("sunxi sprite error : the item too big\n");

		return 0;
	}

	file_size = pImage->ItemTable[pItem->index].filelenLo;
	file_size = (file_size + 1023) & (~(1024 - 1));
	if(file_size > buffer_size)
	{
		__inf("sunxi sprite error : buffer is smaller than data size\n");

		return 0;
	}

	offset = pImage->ItemTable[pItem->index].offsetHi;
	offset <<= 32;
	offset |= pImage->ItemTable[pItem->index].offsetLo;
	start = offset/512;

	if(wBoot_block_read((uint)start + img_file_start, file_size/512, buffer))
	{
		__inf("sunxi sprite error : read item data failed\n");

		return 0;
	}

	return file_size;
}
#endif
//------------------------------------------------------------------------------------------------------------
//
// ����˵��
//
//
// ����˵��
//
//
// ����ֵ
//     ����ʵ�ʶ�ȡ���ݵĳ���
//
// ����
//    ��
//
//------------------------------------------------------------------------------------------------------------

//static __int64 __Img_ReadItemData(HIMAGE hImage, HIMAGEITEM hItem, void * buffer, __int64 Length);
//
//// ���ݷ�����м��ٴ����İ汾 scott 2009-06-22 10:37:17
////////////////////////////////////////////////////////////////////////////
////ÿ�ζ�ȡ�Ĵ�С��չ��10M
//
//__int64 Img_ReadItemData(HIMAGE hImage, HIMAGEITEM hItem, void * buffer, __int64 Length)
//{
//	__int64 readlen = 0;
//	__int64 nRet = 0;
//	IMAGE_HANDLE* pImage = (IMAGE_HANDLE *)hImage;
//	ITEM_HANDLE * pItem  = (ITEM_HANDLE  *)hItem;
//	DWORD dwLen;
//	//u8 buffer_encode[SIZE_32K];
//	u8* buffer_encode = (u8*)wBoot_malloc(SIZE_10M);
//	__int64 this_read;
//	__int64 pos = 0;
//	pEnDecode pfDecode = pImage->rc_if_decode[DATA_ID].EnDecode;
//
//	//Ϊ���ٶȲ����в����ļ�⹤�� scott 2009-06-22
//	//Msg("Img_ReadItemData:Length=%x datalen=%x pos=%x",
//	//	Length, pImage->ItemTable[pItem->index].datalen, pItem->pos); //__inf
//
//	__int64 nLenTmp = Get64bitLen(pImage->ItemTable[pItem->index].filelenLo, pImage->ItemTable[pItem->index].filelenHi);
//	__int64 nFileLen = nLenTmp;
//	if (pItem->pos >= nLenTmp) //filelen <= datalen
//	{
//		Err("Img_ReadItemData", __FILE__, __LINE__,
//			"pos(%x) >= pItem->filelen(%x)",nLenTmp);
//		goto readEnd;
//	}
//	//------------------------------------------------
//	//Լ�����ݲ��ᳬ���������ݵķ�Χ
//	//------------------------------------------------
//	nLenTmp = Get64bitLen(pImage->ItemTable[pItem->index].datalenLo, pImage->ItemTable[pItem->index].datalenHi);
//	Length = min(Length, nLenTmp - pItem->pos);
//	//Msg("Length_min=%x", Length);
//	//------------------------------------------------
//	//���ܺ��������16byte���з��飬��Ҫ������߽�����
//	//------------------------------------------------
//	if ((pItem->pos % ENCODE_LEN) == 0)	//pos�����Ƿ���ı߽�����
//	{
//		nLenTmp = Get64bitLen(pImage->ItemTable[pItem->index].offsetLo , pImage->ItemTable[pItem->index].offsetHi);
//		pos = nLenTmp + pItem->pos;
//		//fseek(pImage->fp, pos, SEEK_SET);
//		FsSeek(pImage->fp, pos, SEEK_SET);
//		readlen = 0;
//		while(readlen < Length)
//		{
//			//------------------------------------------------
//			//ÿ�ζ�ȡn������
//			//------------------------------------------------
//			this_read = min(SIZE_10M, (Length - readlen));
//			u32 n = (this_read + ENCODE_LEN - 1) / ENCODE_LEN;	//
//			memset(buffer_encode, 0, n * ENCODE_LEN);
//			//fread(buffer_encode, this_read, 1, pImage->fp);		//һ�ζ�n������,�ٶȸ��� note has bug
//			//fread(buffer_encode, n * ENCODE_LEN, 1, pImage->fp);	//OK ����ͨ���������ȡ�����ķ���
//			u32 nReadAlian =  n * ENCODE_LEN;
//			if(pImage->bWithEncpy == FALSE)
//			{
//				ReadFile(pImage->fp, buffer, nReadAlian/*n * ENCODE_LEN*/, &dwLen, NULL);
//			}
////			else
////			{
////				ReadFile(pImage->fp, buffer_encode, nReadAlian/*n * ENCODE_LEN*/, &dwLen, NULL);	//OK ����ͨ���������ȡ�����ķ���
////
////				//fseek(pImage->fp, 0, SEEK_CUR);
////				//Msg("this_read=%x", this_read);
////				//------------------------------------------------
////				//�������ݽ���
////				//------------------------------------------------
////				u8 * pin = buffer_encode;
////				u8 * pout= (u8 *)buffer;
////				pout     = pout + readlen;	//ʵ��������ݵ�ƫ����
////
////				for (u32 i = 0; i < n; i++)	//���������н���
////				{
////					//------------------------------------------------
////					//ÿ�ν���һ������
////					//------------------------------------------------
////					if (OK !=  pfDecode(pImage->rc_if_decode[DATA_ID].handle, pin , pout))
////						return 0;
////					/*
////					//__inf start
////					if (i == (n-1))
////					{
////						Msg("last:%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x ",
////						pout[0], pout[1], pout[2],  pout[3],  pout[4],  pout[5],  pout[6], pout[7],
////						pout[8], pout[9], pout[10], pout[11], pout[12], pout[13], pout[14],pout[15]);
////					}
////					//__inf end
////					*/
////					pin += ENCODE_LEN;
////					pout+= ENCODE_LEN;
////				}
////
////			}
//			//------------------------------------------------
//			//����ʵ����Ч���ݳ���
//			//------------------------------------------------
//			readlen += this_read;
//		}
//		if((pItem->pos + readlen) >= nFileLen )
//		{
//			readlen = nFileLen - pItem->pos;
//		}
//
//		pItem->pos += readlen;
//		//Msg("Img_ReadItemData: pos_new =%x", pItem->pos);
//	//	Msg("Read %d\ nFileLen = %x\n", readlen, nFileLen);
//		nRet = readlen;
//		goto readEnd;
//
//	}
//	else
//	{
//		//------------------------------------------------
//		//����ǿ��ֻ�����������������������ǰ��һЩ�̼������ܻ����𲻼��ݵ����⣬
//		//���������ֻ������ԭʼ�汾��������
//		//------------------------------------------------
//
//		//MessageBox(NULL, "�밴�ն��������������", "����", MB_OK);
//		//return 0;
//
//		Msg("�밴�ն��������������");
//		nRet =   __Img_ReadItemData(hImage, hItem,  buffer, Length);
//	}
//
//
//
//readEnd:
//	wBoot_free(buffer_encode);
//	return nRet;
//}
//
//
////ԭʼ�İ汾���������У�����ÿ�ζ�img�ļ���16byte���ٶȲ��ߣ���Ҫ��������
//__int64 __Img_ReadItemData(HIMAGE hImage, HIMAGEITEM hItem, void * buffer, __int64 Length)
//{
//	__int64 readlen = 0;
//	IMAGE_HANDLE* pImage = (IMAGE_HANDLE *)hImage;
//	ITEM_HANDLE * pItem  = (ITEM_HANDLE  *)hItem;
//	u8 buffer_encode[ENCODE_LEN];
//	__int64 pos = 0;
//	DWORD dwLen;
//	pEnDecode pfDecode = pImage->rc_if_decode[DATA_ID].EnDecode;
//	if (NULL == pImage || NULL == pItem || NULL == buffer || 0 == Length)
//	{
//		return 0;
//	}
//
//
//	if (pItem->pos >= pImage->ItemTable[pItem->index].filelenLo) //filelen <= datalen
//	{
//		Err("Img_ReadItemData", __FILE__, __LINE__, "pos >= pItem->filelen");
//		return 0;
//	}
//	//------------------------------------------------
//	//Լ�����ݲ��ᳬ���������ݵķ�Χ
//	//------------------------------------------------
//	__int64 nTmp = Get64bitLen(pImage->ItemTable[pItem->index].datalenLo, pImage->ItemTable[pItem->index].datalenHi);
//	Length = min(Length, nTmp - pItem->pos);
//
//	if(pImage->bWithEncpy == FALSE)
//	{
//		nTmp = Get64bitLen(pImage->ItemTable[pItem->index].offsetLo, pImage->ItemTable[pItem->index].offsetHi);
//		pos = nTmp + pItem->pos;
//		//fseek(pImage->fp, pos, SEEK_SET);
//		FsSeek(pImage->fp, pos, SEEK_SET);
//		ReadFile(pImage->fp, buffer, Length, &dwLen, NULL);
//		pItem->pos += Length;
//		return Length;
//	}
//
//	//------------------------------------------------
//	//���ܺ��������16byte���з��飬��Ҫ������߽�����
//	//------------------------------------------------
//	if ((pItem->pos % ENCODE_LEN) == 0)	//pos�����Ƿ���ı߽�����
//	{
//		nTmp = Get64bitLen(pImage->ItemTable[pItem->index].offsetLo, pImage->ItemTable[pItem->index].offsetHi);
//		pos = nTmp + pItem->pos;
//		//fseek(pImage->fp, pos, SEEK_SET);
//		FsSeek(pImage->fp, pos, SEEK_SET);
//
//		while(readlen < Length)
//		{
//			//ÿ�ζ�ȡһ������
//			memset(buffer_encode, 0, ENCODE_LEN);
//		//	fread(buffer_encode, ENCODE_LEN, 1, pImage->fp);
//		//	fseek(pImage->fp, 0, SEEK_CUR);
//			ReadFile(pImage->fp, buffer_encode, ENCODE_LEN, &dwLen, NULL);
//			//�������ݽ���
//			u8 * pin = buffer_encode;
//			u8 * pout= (u8 *)buffer;
//			pout     = pout + readlen;
//			if (OK != pfDecode(pImage->rc_if_decode[DATA_ID].handle, pin , pout))
//				return 0;
//			//����ʵ����Ч���ݳ���
//			readlen += min(Length- readlen, ENCODE_LEN);
//		}
//		pItem->pos += readlen;
//		return readlen;
//	}
//	else //pos���ڱ߽�
//	{
//		//pos���ڱ߽磬��ͷ����seek
//		pos = pImage->ItemTable[pItem->index].offsetLo +
//				  pItem->pos - (pItem->pos % ENCODE_LEN);
//		//fseek(pImage->fp, pos, SEEK_SET);
//		FsSeek(pImage->fp, pos, SEEK_SET);
//
//		//-----------------------------------
//		//**********************OOOOOOOOOOOOO     *��ʾ�Ѿ���ȡ������ O��ʾδ��ȡ������
//		//-----------------------------------
//		if ((0 < Length) && (Length < ENCODE_LEN)) //��ȡ�����ݲ���һ�����鳤��
//		{
//			u32 read = ENCODE_LEN - (pItem->pos % ENCODE_LEN); //������δ��ȡ�����ݳ���
//			if (Length <= read)	//��Ҫ��ȡ������С�ڵ��ڷ�����δ��ȡ�����ݳ��� ֻ�ö�һ�����鼴��
//			{
//				//-----------------------------------
//				//**********************OOOOOOOOOOOOO     *��ʾ�Ѿ���ȡ������ O��ʾδ��ȡ������
//				//-----------------------------------
//				u32 read = ENCODE_LEN - pItem->pos % ENCODE_LEN;
//				memset(buffer_encode, 0, ENCODE_LEN);
//				//fread(buffer_encode, ENCODE_LEN, 1, pImage->fp);
//				ReadFile(pImage->fp, buffer_encode, ENCODE_LEN, &dwLen, NULL);
//
//				//�������ݽ���
//				u8 * pin = buffer_encode;
//				u8 * pout= (u8 *)buffer;
//				pout     = pout + readlen;
//				if (OK != pfDecode(pImage->rc_if_decode[DATA_ID].handle, pin , pout))
//					return 0;
//
//				readlen = Length;
//				pItem->pos += readlen;
//				return readlen;
//			}
//			else //��Ҫ���������������
//			{
//				//----------------------------------- //-----------------------------------
//				//**********************OOOOOOOOOOOOO //OOOOOOOOOO
//				//----------------------------------- //-----------------------------------
//				//��һ������
//				u32 read = ENCODE_LEN - pItem->pos % ENCODE_LEN;
//				memset(buffer_encode, 0, ENCODE_LEN);
//				//fread(buffer_encode, ENCODE_LEN, 1, pImage->fp);
//				ReadFile(pImage->fp, buffer_encode, ENCODE_LEN, &dwLen, NULL);
//				//�������ݽ���
//				u8 * pin = buffer_encode;
//				u8 * pout= (u8 *)buffer;
//				pout     = pout + readlen;
//				if (OK != pfDecode(pImage->rc_if_decode[DATA_ID].handle, pin , pout))
//					return 0;
//
//				readlen += read;
//
//				//�ڶ�������
//				__int64 Left_Length = Length - read;			//ʣ�������
//				memset(buffer_encode, 0, ENCODE_LEN);
//				//fread(buffer_encode, ENCODE_LEN, 1, pImage->fp);
//				//fseek(pImage->fp, 0, SEEK_CUR);
//				ReadFile(pImage->fp, buffer_encode, ENCODE_LEN, &dwLen, NULL);
//				//�������ݽ���
//				pin = buffer_encode;
//				pout= (u8 *)buffer;
//				pout     = pout + readlen;
//				if (OK != pfDecode(pImage->rc_if_decode[DATA_ID].handle, pin , pout))
//					return 0;
//				readlen += Left_Length;
//
//				pItem->pos += readlen;
//				return readlen;
//			}
//		}
//		else if (Length >= ENCODE_LEN) //��ȡ�����ݲ�����һ�����鳤��
//		{
//			//-----------------------------------
//			//**********************OOOOOOOOOOOOO     *��ʾ�Ѿ���ȡ������ O��ʾδ��ȡ������
//			//-----------------------------------
//			u32 read = ENCODE_LEN - pItem->pos % ENCODE_LEN;
//			memset(buffer_encode, 0, ENCODE_LEN);
//			//fread(buffer_encode, ENCODE_LEN, 1, pImage->fp);
//		//	fread(pImage->fp, buffer_encode, ENCODE_LEN, &dwLen,NULL);
//			ReadFile(pImage->fp, buffer_encode, ENCODE_LEN, &dwLen,NULL);
//
//			//�������ݽ���
//			u8 * pin = buffer_encode;
//			u8 * pout= (u8 *)buffer;
//			pout     = pout + readlen;
//			if (OK != pfDecode(pImage->rc_if_decode[DATA_ID].handle, pin , pout))
//				return 0;
//
//			readlen += read;
//
//			//------------------------------------------------
//			//ʣ������ݰ��շ�����д���
//			//------------------------------------------------
//			u32 Left_Length = Length - read;
//			u32 Left_readlen= 0;
//			while(Left_readlen < Left_Length)
//			{
//				//ÿ�ζ�ȡһ������
//				memset(buffer_encode, 0, ENCODE_LEN);
//			//	fread(buffer_encode, ENCODE_LEN, 1, pImage->fp);
//			//	fseek(pImage->fp, 0, SEEK_CUR);
//				ReadFile(pImage->fp, buffer_encode, ENCODE_LEN, &dwLen, NULL);
//				//�������ݽ���
//				u8 * pin = buffer_encode;
//				u8 * pout= (u8 *)buffer;
//				pout     = pout + readlen;
//				if (OK != pfDecode(pImage->rc_if_decode[DATA_ID].handle, pin , pout))
//					return 0;
//				//����ʵ����Ч���ݳ���
//				Left_readlen += min(Left_Length - Left_readlen, ENCODE_LEN);
//			}
//
//			readlen += Left_readlen;
//		}
//
//		pItem->pos += readlen;
//		return readlen;
//	}
//
//	return 0;
//}



//------------------------------------------------------------------------------------------------------------
//
// ����˵��
//
//
// ����˵��
//
//
// ����ֵ
//
//
// ����
//    ��
//
//------------------------------------------------------------------------------------------------------------
int Img_CloseItem	(HIMAGE hImage, HIMAGEITEM hItem)
{
	ITEM_HANDLE * pItem = (ITEM_HANDLE *)hItem;

	__inf("img close item %x\n", (__u32)hItem);
	if (NULL == pItem)
	{
		__inf("sunxi sprite error : item is null when close it\n");

		return -1;
	}
	//__inf("try to wBoot_free %x\n", (uint)pItem);
	wBoot_free(pItem);
	pItem = NULL;

	return 0;
}



//------------------------------------------------------------------------------------------------------------
//
// ����˵��
//
//
// ����˵��
//
//
// ����ֵ
//
//
// ����
//    ��
//
//------------------------------------------------------------------------------------------------------------
void  Img_Close	(HIMAGE hImage)
{
	IMAGE_HANDLE * pImage = (IMAGE_HANDLE *)hImage;

	if (NULL == pImage)
	{
		__inf("sunxi sprite error : imghead is null when close it\n");

		return ;
	}

	if (NULL != pImage->ItemTable)
	{
		wBoot_free(pImage->ItemTable);
		pImage->ItemTable = NULL;
	}

	memset(pImage, 0, sizeof(IMAGE_HANDLE));
	wBoot_free(pImage);
	pImage = NULL;

	return ;
}


