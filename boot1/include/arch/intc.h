/*
**********************************************************************************************************************
*                                                    ePDK
*                                    the Easy Portable/Player Develop Kits
*                                              eBIOS Sub-System
*
*                                   (c) Copyright 2007-2009, Steven.ZGJ.China
*                                             All Rights Reserved
*
* Moudle  : ebios
* File    : intc.h
*
* By      : Jerry
* Version : v2.0
* Date    : 2009-9-11 14:40:43
**********************************************************************************************************************
*/
#ifndef _INTC_H_
#define _INTC_H_

/*
*********************************************************************************************************
*   Interrupt controller define
*********************************************************************************************************
*/
/* GIC registers */
#define GICD_CTLR			__REG(ARMA9_GIC_BASE + 0x0000)
#define GICD_TYPE			__REG(ARMA9_GIC_BASE + 0x0004)
#define GICD_IIDR			__REG(ARMA9_GIC_BASE + 0x0008)

#define GICD_IGROUPR		__REG(ARMA9_GIC_BASE + 0x0080)

#define GICD_ISENABLER(n)	__REG(ARMA9_GIC_BASE + 0x100 + 4 * (n))
#define GICD_ICENABLER(n)	__REG(ARMA9_GIC_BASE + 0x180 + 4 * (n))

#define GICD_ISPENDR(n)		__REG(ARMA9_GIC_BASE + 0x200 + 4 * (n))
#define GICD_ICPENDR(n)		__REG(ARMA9_GIC_BASE + 0x280 + 4 * (n))

#define GICD_ISACTIVER(n)	__REG(ARMA9_GIC_BASE + 0x300 + 4 * (n))
#define GICD_ICACTIVER(n)	__REG(ARMA9_GIC_BASE + 0x380 + 4 * (n))

#define GICD_SGI_PRIO(n)	__REG(ARMA9_GIC_BASE + 0x400 + 4 * (n))
#define GICD_PPI_PRIO(n)	__REG(ARMA9_GIC_BASE + 0x410 + 4 * (n))
#define GICD_SPI_PRIO(n)	__REG(ARMA9_GIC_BASE + 0x420 + 4 * (n))

#define GICD_SGI_ITARG(n)	__REG(ARMA9_GIC_BASE + 0x800 + 4 * (n))
#define GICD_PPI_ITARG(n)	__REG(ARMA9_GIC_BASE + 0x810 + 4 * (n))
#define GICD_SPI_ITARG(n)	__REG(ARMA9_GIC_BASE + 0x820 + 4 * (n))

#define GICD_ICFGR(n)		__REG(ARMA9_GIC_BASE + 0xc00 + 4 * (n))

#define GICD_SGIR			__REG(ARMA9_GIC_BASE + 0xf00)	// 0xf00

#define GICC_CTRL			__REG(ARMA9_CPUIF_BASE + 0x000)	// 0x8000
#define GICC_PMR			__REG(ARMA9_CPUIF_BASE + 0x004) // 0x8004
#define GICC_BPR			__REG(ARMA9_CPUIF_BASE + 0x008) // 0x8008
#define GICC_IAR			__REG(ARMA9_CPUIF_BASE + 0x00c) // 0x800c
#define GICC_EOIR			__REG(ARMA9_CPUIF_BASE + 0x010) // 0x8010
#define GICC_RPR			__REG(ARMA9_CPUIF_BASE + 0x014) // 0x8014
#define GICC_HPPIR			__REG(ARMA9_CPUIF_BASE + 0x018) // 0x8018
#define GICC_DIR			__REG(ARMA9_CPUIF_BASE + 0x1000)// 0x1000

#define GIC_SRC_SPI(n)		(n+32)

//#ifndef FPGA_PLATFORM	//chip irq mapping
#if 0

#define GIC_SRC_UART0		GIC_SRC_SPI(0)   // (32)
#define GIC_SRC_UART1		GIC_SRC_SPI(1)   // (33)
#define GIC_SRC_UART2       GIC_SRC_SPI(2)   // (34)
#define GIC_SRC_UART3       GIC_SRC_SPI(3)   // (35)
#define GIC_SRC_UART4       GIC_SRC_SPI(4)   // (36)
#define GIC_SRC_UART5       GIC_SRC_SPI(5)   // (37)
#define GIC_SRC_TWI0        GIC_SRC_SPI(6  ) // (38)
#define GIC_SRC_TWI1        GIC_SRC_SPI(7  ) // (39)
#define GIC_SRC_TWI2        GIC_SRC_SPI(8  ) // (40)
#define GIC_SRC_TWI3        GIC_SRC_SPI(9  ) // (41)
//#define GIC_SRC_STWI        GIC_SRC_SPI(10 ) // (42)

#define GIC_SRC_PAEINT      GIC_SRC_SPI(11 ) // (43)
#define GIC_SRC_SPDIF       GIC_SRC_SPI(12 ) // (44)
#define GIC_SRC_IIS0        GIC_SRC_SPI(13 ) // (45)
#define GIC_SRC_IIS1        GIC_SRC_SPI(14 ) // (46)
#define GIC_SRC_PBEINT      GIC_SRC_SPI(15 ) // (47)
#define GIC_SRC_PEEINT      GIC_SRC_SPI(16 ) // (48)
#define GIC_SRC_PGEINT      GIC_SRC_SPI(17 ) // (49)

#define GIC_SRC_TIMER0      GIC_SRC_SPI(18 ) // (50)
#define GIC_SRC_TIMER1      GIC_SRC_SPI(19 ) // (51)
#define GIC_SRC_TIMER2      GIC_SRC_SPI(20 ) // (52)
#define GIC_SRC_TIMER3      GIC_SRC_SPI(21 ) // (53)
#define GIC_SRC_TIMER4      GIC_SRC_SPI(22 ) // (54)
#define GIC_SRC_TIMER5      GIC_SRC_SPI(23 ) // (55)

#define GIC_SRC_WATCHDOG4   GIC_SRC_SPI(24 ) // (56)
#define GIC_SRC_WATCHDOG1   GIC_SRC_SPI(25 ) // (57)
#define GIC_SRC_WATCHDOG2   GIC_SRC_SPI(26 ) // (58)
#define GIC_SRC_WATCHDOG3   GIC_SRC_SPI(27 ) // (59)
#define GIC_SRC_TP          GIC_SRC_SPI(28 ) // (60)
#define GIC_SRC_CODEC       GIC_SRC_SPI(29 ) // (61)
#define GIC_SRC_LRADC       GIC_SRC_SPI(30 ) // (62)
#define GIC_SRC_MTCACC      GIC_SRC_SPI(31 ) // (63)
#define GIC_SRC_NMI         GIC_SRC_SPI(32 ) // (64)
#define GIC_SRC_RTIMER0     GIC_SRC_SPI(33 ) // (65)
#define GIC_SRC_RTIMER1     GIC_SRC_SPI(34 ) // (66)

#define GIC_SRC_RWATCHDOG   GIC_SRC_SPI(36 ) // (68)
#define GIC_SRC_RCIR        GIC_SRC_SPI(37 ) // (69)
#define GIC_SRC_RUART       GIC_SRC_SPI(38 ) // (70)
#define GIC_SRC_RP2WI       GIC_SRC_SPI(39 ) // (71)
#define GIC_SRC_RALARM0     GIC_SRC_SPI(40 ) // (72)
#define GIC_SRC_RALARM1     GIC_SRC_SPI(41 ) // (73)
//#define GIC_SRC_RPIO        GIC_SRC_SPI(42 ) // (74)
#define GIC_SRC_1WIRE       GIC_SRC_SPI(43 ) // (75)
#define GIC_SRC_TWI         GIC_SRC_SPI(44 ) // (76)
#define GIC_SRC_RPLEINT     GIC_SRC_SPI(45 ) // (77)
#define GIC_SRC_RPMEINT     GIC_SRC_SPI(46 ) // (78)

#define GIC_SRC_SPINLOCK    GIC_SRC_SPI(48 ) // (80)
#define GIC_SRC_MBOX        GIC_SRC_SPI(49 ) // (81)
#define GIC_SRC_DMA         GIC_SRC_SPI(50 ) // (82)
#define GIC_SRC_HSTMR0      GIC_SRC_SPI(51 ) // (83)
#define GIC_SRC_HSTMR1      GIC_SRC_SPI(52 ) // (84)
#define GIC_SRC_HSTMR2      GIC_SRC_SPI(53 ) // (85)
#define GIC_SRC_HSTMR3      GIC_SRC_SPI(54 ) // (86)

#define GIC_SRC_TZASC       GIC_SRC_SPI(56 ) // (88)

#define GIC_SRC_VE          GIC_SRC_SPI(58 ) // (90)
#define GIC_SRC_DIGMIC      GIC_SRC_SPI(59 ) // (91)
#define GIC_SRC_MMC0        GIC_SRC_SPI(60 ) // (92)
#define GIC_SRC_MMC1        GIC_SRC_SPI(61 ) // (93)
#define GIC_SRC_MMC2        GIC_SRC_SPI(62 ) // (94)
#define GIC_SRC_MMC3        GIC_SRC_SPI(63 ) // (95)

#define GIC_SRC_SPI0        GIC_SRC_SPI(65 ) // (97 )
#define GIC_SRC_SPI1        GIC_SRC_SPI(66 ) // (98 )
#define GIC_SRC_SPI2        GIC_SRC_SPI(67 ) // (99 )
#define GIC_SRC_SPI3        GIC_SRC_SPI(68 ) // (100)
#define GIC_SRC_NAND1       GIC_SRC_SPI(69 ) // (101)
#define GIC_SRC_NAND0       GIC_SRC_SPI(70 ) // (102)
#define GIC_SRC_USBOTG      GIC_SRC_SPI(71 ) // (103)
#define GIC_SRC_USBEHCI0    GIC_SRC_SPI(72 ) // (104)
#define GIC_SRC_USBOHCI0    GIC_SRC_SPI(73 ) // (105)
#define GIC_SRC_USBEHCI1    GIC_SRC_SPI(74 ) // (106)
#define GIC_SRC_USBOHCI1    GIC_SRC_SPI(75 ) // (107)
//#define GIC_SRC_USBEHCI2    GIC_SRC_SPI(76 ) // (108)
#define GIC_SRC_USBOHCI2    GIC_SRC_SPI(77 ) // (109)

#define GIC_SRC_SS          GIC_SRC_SPI(80 ) // (112)
#define GIC_SRC_TS          GIC_SRC_SPI(81 ) // (113)
#define GIC_SRC_GMAC        GIC_SRC_SPI(82 ) // (114)

#define GIC_SRC_CSI0        GIC_SRC_SPI(84 ) // (116)
#define GIC_SRC_CSI1        GIC_SRC_SPI(85 ) // (117)
#define GIC_SRC_LCD0        GIC_SRC_SPI(86 ) // (118)
#define GIC_SRC_LCD1        GIC_SRC_SPI(87 ) // (119)
#define GIC_SRC_HDMI        GIC_SRC_SPI(88 ) // (120)
#define GIC_SRC_MIPIDSI     GIC_SRC_SPI(89 ) // (121)
#define GIC_SRC_MIPICSI     GIC_SRC_SPI(90 ) // (122)
#define GIC_SRC_DRC01       GIC_SRC_SPI(91 ) // (123)
#define GIC_SRC_DEU01       GIC_SRC_SPI(92 ) // (124)
#define GIC_SRC_DEFE0       GIC_SRC_SPI(93 ) // (125)
#define GIC_SRC_DEFE1       GIC_SRC_SPI(94 ) // (126)
#define GIC_SRC_DEBE0       GIC_SRC_SPI(95 ) // (127)
#define GIC_SRC_DEBE1       GIC_SRC_SPI(96 ) // (128)
#define GIC_SRC_GPU         GIC_SRC_SPI(97 ) // (129)

#define GIC_SRC_CTI0        GIC_SRC_SPI(108) // (140)
#define GIC_SRC_CTI1        GIC_SRC_SPI(109) // (141)
#define GIC_SRC_CTI2        GIC_SRC_SPI(110) // (142)
#define GIC_SRC_CTI3        GIC_SRC_SPI(111) // (143)
#define GIC_SRC_COMMTX0     GIC_SRC_SPI(112) // (144)
#define GIC_SRC_COMMTX1     GIC_SRC_SPI(113) // (145)
#define GIC_SRC_COMMTX2     GIC_SRC_SPI(114) // (146)
#define GIC_SRC_COMMTX3     GIC_SRC_SPI(115) // (147)
#define GIC_SRC_COMMRX0     GIC_SRC_SPI(116) // (148)
#define GIC_SRC_COMMRX1     GIC_SRC_SPI(117) // (149)
#define GIC_SRC_COMMRX2     GIC_SRC_SPI(118) // (150)
#define GIC_SRC_COMMRX3     GIC_SRC_SPI(119) // (151)
#define GIC_SRC_PMU0        GIC_SRC_SPI(120) // (152)
#define GIC_SRC_PMU1        GIC_SRC_SPI(121) // (153)
#define GIC_SRC_PMU2        GIC_SRC_SPI(122) // (154)
#define GIC_SRC_PMU3        GIC_SRC_SPI(123) // (155)
#define GIC_SRC_AXIE        GIC_SRC_SPI(124) // (156)

#define GIC_IRQ_NUM			(GIC_SRC_GPU + 1)

#else	//fpga irq mapping
#define GIC_SRC_NMI         GIC_SRC_SPI(0) 	// (32)
#define GIC_SRC_UART0		GIC_SRC_SPI(1)	// (33)
#define GIC_SRC_TWI0        GIC_SRC_SPI(2)	// (34)
#define GIC_SRC_TWI1        GIC_SRC_SPI(2)	// (34)	not exist in fpga, just for compiling
#define GIC_SRC_TWI2        GIC_SRC_SPI(2)	// (34)	not exist in fpga, just for compiling
#define GIC_SRC_TWI3        GIC_SRC_SPI(2)	// (34)	not exist in fpga, just for compiling
#define GIC_SRC_PAEINT      GIC_SRC_SPI(2)	// (34)
#define GIC_SRC_PBEINT      GIC_SRC_SPI(2)	// (34) not exist in fpga, just for compiling
#define GIC_SRC_PEEINT      GIC_SRC_SPI(2)	// (34) not exist in fpga, just for compiling
#define GIC_SRC_PGEINT      GIC_SRC_SPI(2)	// (34) not exist in fpga, just for compiling
#define GIC_SRC_SPDIF       GIC_SRC_SPI(3)  // (35)
#define GIC_SRC_IIS0        GIC_SRC_SPI(3)  // (35)
#define GIC_SRC_CSI0        GIC_SRC_SPI(3)  // (35)
#define GIC_SRC_MIPIDSI     GIC_SRC_SPI(3)  // (35)
#define GIC_SRC_MIPICSI     GIC_SRC_SPI(3)  // (35)
#define GIC_SRC_TIMER0      GIC_SRC_SPI(4)  // (36)
#define GIC_SRC_TIMER1      GIC_SRC_SPI(5)  // (37)
#define GIC_SRC_TIMER2      GIC_SRC_SPI(5)  // (37)
#define GIC_SRC_TIMER3      GIC_SRC_SPI(5)  // (37)
#define GIC_SRC_TIMER4      GIC_SRC_SPI(5)  // (37)
#define GIC_SRC_TIMER5      GIC_SRC_SPI(5)  // (37)
#define GIC_SRC_DMA         GIC_SRC_SPI(6)  // (38)
#define GIC_SRC_WATCHDOG1   GIC_SRC_SPI(7)  // (39)
#define GIC_SRC_WATCHDOG2   GIC_SRC_SPI(8)  // (40)
#define GIC_SRC_RTIMER0     GIC_SRC_SPI(9)  // (41)
#define GIC_SRC_RTIMER1     GIC_SRC_SPI(9)  // (41)
#define GIC_SRC_RWATCHDOG   GIC_SRC_SPI(9)  // (41)
#define GIC_SRC_SPINLOCK    GIC_SRC_SPI(10) // (42)
#define GIC_SRC_MBOX        GIC_SRC_SPI(11) // (43)
#define GIC_SRC_HSTMR0      GIC_SRC_SPI(12) // (44)
#define GIC_SRC_HSTMR1      GIC_SRC_SPI(12) // (44)	not exist in fpga, just for compiling
#define GIC_SRC_HSTMR2      GIC_SRC_SPI(12) // (44)	not exist in fpga, just for compiling
#define GIC_SRC_HSTMR3      GIC_SRC_SPI(12) // (44)	not exist in fpga, just for compiling
#define GIC_SRC_MMC0        GIC_SRC_SPI(13) // (45)
#define GIC_SRC_MMC1        GIC_SRC_SPI(13) // (45) not exist in fpga, just for compiling
#define GIC_SRC_MMC2        GIC_SRC_SPI(13) // (45)
#define GIC_SRC_MMC3        GIC_SRC_SPI(13) // (45) not exist in fpga, just for compiling
#define GIC_SRC_SPI0        GIC_SRC_SPI(13) // (45)
#define GIC_SRC_NAND0       GIC_SRC_SPI(14) // (46)
#define GIC_SRC_NAND1       GIC_SRC_SPI(15) // (47)
#define GIC_SRC_GPU         GIC_SRC_SPI(15) // (47)
#define GIC_SRC_RCIR    	GIC_SRC_SPI(16) // (48)
#define GIC_SRC_RUART    	GIC_SRC_SPI(16) // (48)
#define GIC_SRC_RPLEINT     GIC_SRC_SPI(17) // (49)
#define GIC_SRC_RPMEINT     GIC_SRC_SPI(17) // (49)
#define GIC_SRC_RALARM0     GIC_SRC_SPI(18) // (50)
#define GIC_SRC_RALARM1     GIC_SRC_SPI(18) // (50)
#define GIC_SRC_RP2WI       GIC_SRC_SPI(19) // (51)
#define GIC_SRC_TWI         GIC_SRC_SPI(19) // (51)
#define GIC_SRC_VE          GIC_SRC_SPI(20) // (52)
#define GIC_SRC_USBOTG      GIC_SRC_SPI(21) // (53)
#define GIC_SRC_USBEHCI0    GIC_SRC_SPI(22) // (54)
#define GIC_SRC_USBOHCI0    GIC_SRC_SPI(23) // (55)
#define GIC_SRC_SS          GIC_SRC_SPI(24) // (56)
#define GIC_SRC_TS          GIC_SRC_SPI(24) // (56)
#define GIC_SRC_GMAC        GIC_SRC_SPI(24) // (56)
#define GIC_SRC_CODEC       GIC_SRC_SPI(24) // (56)
#define GIC_SRC_TP          GIC_SRC_SPI(24) // (56)
#define GIC_SRC_LCD0        GIC_SRC_SPI(25) // (57)
#define GIC_SRC_TZASC       GIC_SRC_SPI(26) // (58)
#define GIC_SRC_DEFE0       GIC_SRC_SPI(27) // (59)
#define GIC_SRC_DEBE0       GIC_SRC_SPI(28) // (60)
#define GIC_SRC_DRC01       GIC_SRC_SPI(29) // (61)
#define GIC_SRC_DEU01       GIC_SRC_SPI(30) // (62)
#define GIC_SRC_1WIRE       GIC_SRC_SPI(31) // (63)
#define GIC_IRQ_NUM			(GIC_SRC_1WIRE + 1)

#endif

#endif  /* _INTC_H_ */

