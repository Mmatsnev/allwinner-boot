#ifndef   MCTL_PAR_H
#define   MCTL_PAR_H

#include "include.h"

//this type just for dram driver
typedef unsigned int        uint32;

/* PRCM registers define */
#define R_PRCM_BASE			(0x01f01400)
#define R_CPUS_CLK_CFG_REG		(R_PRCM_BASE + 0x00)
#define R_APB0_CLK_DIV_REG		(R_PRCM_BASE + 0x0c)
#define R_CPU0_CLK_EN_REG		(R_PRCM_BASE + 0x10)
#define R_CPU1_CLK_EN_REG		(R_PRCM_BASE + 0x14)
#define R_CPU2_CLK_EN_REG		(R_PRCM_BASE + 0x18)
#define R_CPU3_CLK_EN_REG		(R_PRCM_BASE + 0x1C)
#define R_APB0_CLK_GATE_REG		(R_PRCM_BASE + 0x28)
#define R_PLL_CTRL0_REG			(R_PRCM_BASE + 0x40)
#define R_PLL_CTRL1_REG			(R_PRCM_BASE + 0x44)
#define R_1WIRE_CLK_CTRL_REG		(R_PRCM_BASE + 0x50)
#define R_CIR_CLK_CTRL_REG		(R_PRCM_BASE + 0x54)
#define R_APB0_MOD_RST_REG		(R_PRCM_BASE + 0xb0)
#define R_CLK_OUTD_REG			(R_PRCM_BASE + 0xf0)
#define R_CPU_POWOFF_REG		(R_PRCM_BASE + 0x100)

#define R_VDD_SYS_PWROFF_GATE		(R_PRCM_BASE + 0x110)
#define R_GPU_PWROFF_GATE		(R_PRCM_BASE + 0x118)
#define R_VDD_SYS_PWR_RESET		(R_PRCM_BASE + 0x120)
#define R_CPU1_PWR_CLAMP		(R_PRCM_BASE + 0x144)
#define R_CPU2_PWR_CLAMP		(R_PRCM_BASE + 0x148)
#define R_CPU3_PWR_CLAMP		(R_PRCM_BASE + 0x14C)

#define R_RAM_CFG_REG			(R_PRCM_BASE + 0x180)
#define R_RAM_TEST_REG			(R_PRCM_BASE + 0x190)


//ccmu register list
#define CCM_BASE			(0x01c20000)
#define CCM_PLL1_CPUX_CTRL  		(CCM_BASE+0x000)
#define CCM_PLL2_AUDIO_CTRL 		(CCM_BASE+0x008)
#define CCM_PLL3_VIDEO_CTRL    		(CCM_BASE+0x010)
#define CCM_PLL4_VE_CTRL     		(CCM_BASE+0x018)
#define CCM_PLL5_DDR_CTRL  		(CCM_BASE+0x020)
#define CCM_PLL6_MOD_CTRL  		(CCM_BASE+0x028)
#define CCM_PLL7_VIDEO1_CTRL		(CCM_BASE+0x030)
#define CCM_PLL8_GPU_CTRL  		(CCM_BASE+0x038)
#define CCM_MIPI_PLL_CTRL		(CCM_BASE+0x040)

#define CCM_CPU_L2_AXI_CTRL		(CCM_BASE+0x050)
#define CCM_AHB1_APB1_CTRL		(CCM_BASE+0x054)
#define CCM_APB2_CLK_CTRL		(CCM_BASE+0x058)
#define CCM_AXI_GATE_CTRL		(CCM_BASE+0x05c)
#define CCM_AHB1_GATE0_CTRL		(CCM_BASE+0x060)
#define CCM_AHB1_GATE1_CTRL		(CCM_BASE+0x064)
#define CCM_APB1_GATE0_CTRL		(CCM_BASE+0x068)
#define CCM_APB2_GATE0_CTRL		(CCM_BASE+0x06C)

#define CCM_NAND0_SCLK_CTRL		(CCM_BASE+0x080)
#define CCM_NAND1_SCLK_CTRL		(CCM_BASE+0x084)

#define CCM_SDC0_SCLK_CTRL		(CCM_BASE+0x088)
#define CCM_SDC1_SCLK_CTRL		(CCM_BASE+0x08c)
#define CCM_SDC2_SCLK_CTRL		(CCM_BASE+0x090)
#define CCM_SDC3_SCLK_CTRL		(CCM_BASE+0x094)
#define CCM_TS_SCLK_CTRL		(CCM_BASE+0x098)
#define CCM_SS_SCLK_CTRL		(CCM_BASE+0x09c)
#define CCM_SPI0_SCLK_CTRL		(CCM_BASE+0x0a0)
#define CCM_SPI1_SCLK_CTRL		(CCM_BASE+0x0a4)
#define CCM_SPI2_SCLK_CTRL		(CCM_BASE+0x0a8)
#define CCM_SPI3_SCLK_CTRL		(CCM_BASE+0x0ac)
#define CCM_I2S0_SCLK_CTRL		(CCM_BASE+0x0b0)
#define CCM_I2S1_SCLK_CTRL		(CCM_BASE+0x0b4)

#define CCM_SPDIF_SCLK_CTRL		(CCM_BASE+0x0c0)

#define CCM_USBPHY_SCLK_CTRL		(CCM_BASE+0x0cc)

#define CCM_MDFS_CLK_CTRL		(CCM_BASE+0x0f0)
#define CCM_DRAMCLK_CFG_CTRL		(CCM_BASE+0x0f4)
#define CCM_DRAMCLK_GATE_CTRL		(CCM_BASE+0x0100)
#define CCM_BE0_SCLK_CTRL		(CCM_BASE+0x0104)
#define CCM_BE1_SCLK_CTRL		(CCM_BASE+0x0108)
#define CCM_FE0_SCLK_CTRL		(CCM_BASE+0x010c)
#define CCM_FE1_SCLK_CTRL		(CCM_BASE+0x0110)
#define CCM_MP_SCLK_CTRL		(CCM_BASE+0x0114)
#define CCM_LCD0C0_SCLK_CTRL		(CCM_BASE+0x0118)
#define CCM_LCD1C0_SCLK_CTRL		(CCM_BASE+0x011c)

#define CCM_LCD0C1_SCLK_CTRL		(CCM_BASE+0x012c)
#define CCM_LCD1C1_SCLK_CTRL		(CCM_BASE+0x0130)
#define CCM_CSI0_SCLK_CTRL		(CCM_BASE+0x0134)
#define CCM_CSI1_SCLK_CTRL		(CCM_BASE+0x0138)
#define CCM_VE_SCLK_CTRL		(CCM_BASE+0x013c)
#define CCM_CODEC_SCLK_CTRL		(CCM_BASE+0x0140)
#define CCM_AVS_SCLK_CTRL		(CCM_BASE+0x0144)

#define CCM_HDMI_SCLK_CTRL		(CCM_BASE+0x0150)

#define CCM_MBUS_SCLK_CTRL0		(CCM_BASE+0x015c)
#define CCM_MBUS_SCLK_CTRL1		(CCM_BASE+0x0160)

#define CCM_MIPIDSI_SCLK_CTRL		(CCM_BASE+0x0168)
#define CCM_MIPICSI0_SCLK_CTRL		(CCM_BASE+0x016c)

#define CCM_DRC0_SCLK_CTRL		(CCM_BASE+0x0180)
#define CCM_DRC1_SCLK_CTRL		(CCM_BASE+0x0184)
#define CCM_DEU0_SCLK_CTRL		(CCM_BASE+0x0188)
#define CCM_DEU1_SCLK_CTRL		(CCM_BASE+0x018c)

#define CCM_GPU_CORECLK_CTRL		(CCM_BASE+0x01A0)
#define CCM_GPU_MEMCLK_CTRL		(CCM_BASE+0x01A4)
#define CCM_GPU_HYDCLK_CTRL		(CCM_BASE+0x01A8)

#define CCM_PLL_STABLE_REG		(CCM_BASE+0x0200)
#define CCM_MCLK_STABLE_REG		(CCM_BASE+0x0204)

#define CCM_PPL1_BIAS_REG		(CCM_BASE+0x0220)
#define CCM_PPL2_BIAS_REG		(CCM_BASE+0x0224)
#define CCM_PPL3_BIAS_REG		(CCM_BASE+0x0228)
#define CCM_PPL4_BIAS_REG		(CCM_BASE+0x022C)
#define CCM_PPL5_BIAS_REG		(CCM_BASE+0x0230)
#define CCM_PPL6_BIAS_REG		(CCM_BASE+0x0234)
#define CCM_PPL7_BIAS_REG		(CCM_BASE+0x0238)
#define CCM_PPL8_BIAS_REG		(CCM_BASE+0x023C)
#define CCM_MIPIPLL_BIAS_REG		(CCM_BASE+0x0240)

#define CCM_PPL1_TUNE_REG		(CCM_BASE+0x0250)

#define CCM_PPL5_TUNE_REG		(CCM_BASE+0x0260)

#define CCM_MIPIPLL_TUNE_REG		(CCM_BASE+0x0270)

#define CCM_PPL1_PAT_REG		(CCM_BASE+0x0280)
#define CCM_PPL2_PAT_REG		(CCM_BASE+0x0284)
#define CCM_PPL3_PAT_REG		(CCM_BASE+0x0288)
#define CCM_PPL4_PAT_REG		(CCM_BASE+0x028C)
#define CCM_PPL5_PAT_REG		(CCM_BASE+0x0290)

#define CCM_PPL7_PAT_REG		(CCM_BASE+0x0298)
#define CCM_PPL8_PAT_REG		(CCM_BASE+0x029C)

#define CCM_MIPIPLL_PAT_REG		(CCM_BASE+0x02A0)

#define CCM_AHB1_RST_REG0		(CCM_BASE+0x02C0)
#define CCM_AHB1_RST_REG1		(CCM_BASE+0x02C4)
#define CCM_AHB1_RST_REG2		(CCM_BASE+0x02C8)

#define CCM_APB1_RST_REG		(CCM_BASE+0x02D0)
#define CCM_APB2_RST_REG		(CCM_BASE+0x02D8)

#define CCM_CLK_OUTA_REG		(CCM_BASE+0x0300)
#define CCM_CLK_OUTB_REG		(CCM_BASE+0x0304)
#define CCM_CLK_OUTC_REG		(CCM_BASE+0x0308)


/* ------------------ DRAM Configuration ------------------ */
#define DRAM_MEM_BASE		(0x40000000)
#define HEAP_MEM_START		(0x48000000)	//heap start offset: 128MB
#define HEAP_MEM_SIZE		(0x18000000)	//384MB
#define DRAM_FREE_MEM_BASE	(0x40100000)	//free memory for test, size 7M

#define PLL5_DDR_CLK		(360000000)

#ifdef FPGA_PLATFORM
	//#define DDR2_32B
	//#define DDR3_32B
	//#define DDR2_FPGA_BJ530 //DDR2_32B 
	#define DDR2_FPGA_S2C
	//#define LPDDR2_FPGA_S2C_2CS_2CH
	#define MCTL_CLK			PLL5_DDR_CLK
	#define MCTL_ACCESS_MODE		1		//0: sequence mode, 1: interleave mode
	#define MCTL_CHANNEL_NUM		1
	#ifdef DDR2_FPGA_S2C
		#define MCTL_CS_NUM		2
	#else
		#define MCTL_CS_NUM		2
	#endif
#else
//#define DDR2_32B
#define DDR3_32B
//#define LPDDR2_32B
#define MCTL_CLK			PLL5_DDR_CLK
#define MCTL_ACCESS_MODE		1				//0: sequence mode, 1: interleave mode
#define MCTL_CHANNEL_NUM		2
#define MCTL_CS_NUM			1
#endif

//DDR2_32B				DDR2_32B_128Mx8x4
//DDR3_32B				DDR3_32B_256Mx8x4

#define MCTL_2T_MOD

//*****************************************************************************
//DDR2 SDRAM(x32)
//*****************************************************************************
#ifdef DDR2_FPGA_S2C
//DDR2 128Mx8 (128M Byte), total 1GB
#define MCTL_DDR_TYPE			2				//1: DDR, 2: DDR2, 3: DDR3
#define MCTL_BANK_SIZE			8
#define MCTL_ROW_WIDTH			14
#define MCTL_BUS_WIDTH			32
#define MCTL_PAGE_SIZE			4				//unit in KByte for one rank
#endif

#ifdef DDR2_FPGA_S2C_2C
//DDR2 128Mx8 (128M Byte), total 512MB
#define MCTL_DDR_TYPE			2				//1: DDR, 2: DDR2, 3: DDR3
#define MCTL_BANK_SIZE			8
#define MCTL_ROW_WIDTH			14
#define MCTL_BUS_WIDTH			16
#define MCTL_PAGE_SIZE			2				//unit in KByte for one rank
#endif

#ifdef DDR2_32B
//DDR2 128Mx8 (128M Byte)
#define MCTL_DDR_TYPE			2				//1: DDR, 2: DDR2, 3: DDR3
#define MCTL_BANK_SIZE			8
#define MCTL_ROW_WIDTH			14
#define MCTL_BUS_WIDTH			32
#define MCTL_PAGE_SIZE			4				//unit in KByte for one rank
#endif

//*****************************************************************************
//DDR3 SDRAM(x32)
//*****************************************************************************
#ifdef DDR3_32B
//DDR3 256Mx8 (256M Byte)
#define MCTL_DDR_TYPE			3				//1: DDR, 2: DDR2, 3: DDR3
#define MCTL_BANK_SIZE			8
#define MCTL_ROW_WIDTH			15
#define MCTL_BUS_WIDTH			32
#define MCTL_PAGE_SIZE			4				//unit in KByte for one rank
#endif

#ifdef DDR3_32B_128M8
//DDR3 128Mx8 (128M Byte)
#define MCTL_DDR_TYPE			3				//1: DDR, 2: DDR2, 3: DDR3
#define MCTL_BANK_SIZE			8
#define MCTL_ROW_WIDTH			14
#define MCTL_BUS_WIDTH			32
#define MCTL_PAGE_SIZE			4				//unit in KByte for one rank
#endif


#ifdef DDR3_32B_512M8
//DDR3 128Mx8 (128M Byte)
#define MCTL_DDR_TYPE			3				//1: DDR, 2: DDR2, 3: DDR3
#define MCTL_BANK_SIZE			8
#define MCTL_ROW_WIDTH			16
#define MCTL_BUS_WIDTH			32
#define MCTL_PAGE_SIZE			2				//unit in KByte for one rank (for debug)
#endif

//*****************************************************************************
//LPDDR2 SDRAM(x32)
//*****************************************************************************
#ifdef LPDDR2_FPGA_S2C_2CS_2CH
//LPDDR2 128Mx32 (512M Byte), total 2GB
#define MCTL_DDR_TYPE			6				//1: DDR, 2: DDR2, 3: DDR3
#define MCTL_BANK_SIZE			8
#define MCTL_ROW_WIDTH			14
#define MCTL_BUS_WIDTH			32
#define MCTL_PAGE_SIZE			4				//unit in KByte for one rank
#endif

#ifdef LPDDR2_32B
//LPDDR2 128Mx32 (512MB)
#define MCTL_DDR_TYPE			6				//1: DDR, 2: DDR2, 3: DDR3
#define MCTL_BANK_SIZE			8
#define MCTL_ROW_WIDTH			14
#define MCTL_BUS_WIDTH			32
#define MCTL_PAGE_SIZE			4				//unit in KByte for one rank
#endif




#if (MCTL_DDR_TYPE==2)		//DDR2-800

#define MCTL_TREFI			78
#define MCTL_TMRD			2
#define MCTL_TRFC			52
#define MCTL_TRP			6
#define MCTL_TPREA			1
#define MCTL_TRTW			2
#define MCTL_TAL			0
#define MCTL_TCL			6
#define MCTL_TCWL			5
#define MCTL_TRAS			18
#define MCTL_TRC			24
#define MCTL_TRCD			6
#define MCTL_TRRD			4
#define MCTL_TRTP			3
#define MCTL_TWR			6
#define MCTL_TWTR			4
#define MCTL_TEXSR			200
#define MCTL_TXP			2
#define MCTL_TXPDLL			6
#define MCTL_TZQCS			0
#define MCTL_TZQCSI			0
#define MCTL_TDQS			1
#define MCTL_TCKSRE			0
#define MCTL_TCKSRX			0
#define MCTL_TCKE			3
#define MCTL_TMOD			0
#define MCTL_TRSTL			0
#define MCTL_TZQCL			0
#define MCTL_TMRR			2
#define MCTL_TCKESR			2
#define MCTL_TDPD			0

#define MCTL_MR0			0xa62
#define MCTL_MR1			0x0
#define MCTL_MR2			0x0
#define MCTL_MR3			0x0


#elif(MCTL_DDR_TYPE==3)		//DDR3-1333
#define MCTL_TREFI			78
#define MCTL_TMRD			4
#define MCTL_TRFC			107
#define MCTL_TRP			9
#define MCTL_TPREA			0
#define MCTL_TRTW			2
#define MCTL_TAL			0
#define MCTL_TCL			9
#define MCTL_TCWL			8
#define MCTL_TRAS			24
#define MCTL_TRC			33
#define MCTL_TRCD			9
#define MCTL_TRRD			4
#define MCTL_TRTP			5
#define MCTL_TWR			10
#define MCTL_TWTR			5
#define MCTL_TEXSR			512
#define MCTL_TXP			5
#define MCTL_TXPDLL			16
#define MCTL_TZQCS			64
#define MCTL_TZQCSI			0
#define MCTL_TDQS			1
#define MCTL_TCKSRE			7
#define MCTL_TCKSRX			7
#define MCTL_TCKE			4
#define MCTL_TMOD			12
#define MCTL_TRSTL			80
#define MCTL_TZQCL			512
#define MCTL_TMRR			2
#define MCTL_TCKESR			5
#define MCTL_TDPD			0

#define MCTL_MR0			0x1a50
#define MCTL_MR1			0x0
#define MCTL_MR2			0x18
#define MCTL_MR3			0x0

#elif(MCTL_DDR_TYPE==5)		//LPDDR
#else						//LPDDR2-800
#define MCTL_TREFI			78
#define MCTL_TMRD			2
#define MCTL_TRFC			52
#define MCTL_TRP			8
#define MCTL_TPREA			0
#define MCTL_TRTW			2
#define MCTL_TAL			0
#define MCTL_TCL			6
#define MCTL_TCWL			4
#define MCTL_TRAS			18
#define MCTL_TRC			27
#define MCTL_TRCD			8
#define MCTL_TRRD			4
#define MCTL_TRTP			3
#define MCTL_TWR			6
#define MCTL_TWTR			3
#define MCTL_TEXSR			200
#define MCTL_TXP			3
#define MCTL_TXPDLL			6
#define MCTL_TZQCS			0
#define MCTL_TZQCSI			0
#define MCTL_TDQS			1
#define MCTL_TCKSRE			5
#define MCTL_TCKSRX			5
#define MCTL_TCKE			3
#define MCTL_TMOD			0
#define MCTL_TRSTL			0
#define MCTL_TZQCL			0
#define MCTL_TMRR			2
#define MCTL_TCKESR			6
#define MCTL_TDPD			0

#define MCTL_MR0			0x0
#define MCTL_MR1			0x92
#define MCTL_MR2			0x4
#define MCTL_MR3			0x2


#endif


#endif  //MCTL_PAR_H
