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
#ifndef  __OSAL_DE_H__
#define  __OSAL_DE_H__

#include "egon2.h"

#ifdef __FPGA_DEBUG__
#define AW_IRQ_DEFE0        59
#define AW_IRQ_LCD0         57
#define AW_IRQ_MIPIDSI      35
#define INTC_IRQNO_LCDC1    100
#define INTC_IRQNO_SCALER1  100
#else
#define AW_IRQ_DEFE0        125
#define AW_IRQ_LCD0         118
#define AW_IRQ_MIPIDSI      121
#define INTC_IRQNO_LCDC1    119
#define INTC_IRQNO_SCALER1  126
#endif


/* define system clock id       */
typedef enum __AW_CCU_CLK_ID
{
    AW_SYS_CLK_NONE=0,  /* invalid clock id                     */

    /* OSC */
    AW_SYS_CLK_LOSC,    /* "sys_losc"   ,LOSC, 32768 hz clock   */
    AW_SYS_CLK_HOSC,    /* "sys_hosc"   ,HOSC, 24Mhz clock      */

    /* PLL */
    AW_SYS_CLK_PLL1,    /* "sys_pll1"   ,PLL1 clock             */
    AW_SYS_CLK_PLL2,    /* "sys_pll2"   ,PLL2 clock             */
    AW_SYS_CLK_PLL3,    /* "sys_pll3"   ,PLL3 clock             */
    AW_SYS_CLK_PLL4,    /* "sys_pll4"   ,PLL4 clock             */
    AW_SYS_CLK_PLL5,    /* "sys_pll5"   ,PLL5 clock             */
    AW_SYS_CLK_PLL6,    /* "sys_pll6"   ,PLL6 clock,            */
    AW_SYS_CLK_PLL7,    /* "sys_pll7"   ,PLL7 clock             */
    AW_SYS_CLK_PLL8,    /* "sys_pll8"   ,PLL8 clock             */
    AW_SYS_CLK_PLL9,    /* "sys_pll9"   ,PLL9 clock             */
    AW_SYS_CLK_PLL10,   /* "sys_pll10"  ,PLL10 clock            */

    /* related PLL */
    AW_SYS_CLK_PLL2X8,  /* "sys_pll2X8"   ,PLL2 8X clock        */
    AW_SYS_CLK_PLL3X2,  /* "sys_pll3X2"   ,PLL3 X2 clock        */
    AW_SYS_CLK_PLL6x2,  /* "sys_pll6X2"   ,PLL6 X2 clock        */
    AW_SYS_CLK_PLL7X2,  /* "sys_pll7X2"   ,PLL7 X2 clock        */
    AW_SYS_CLK_MIPIPLL, /* "sys_mipi_pll" ,MIPI PLL clock       */

    /* CPU & BUS */
    AW_SYS_CLK_AC327,   /* "sys_ac327"  ,CPU clock              */
    AW_SYS_CLK_AR100,   /* "sys_ar100"  ,CPU clock              */
    AW_SYS_CLK_AXI,     /* "sys_axi"    ,AXI clock              */
    AW_SYS_CLK_AHB0,    /* "sys_ahb0"   ,AHB0 clock             */
    AW_SYS_CLK_AHB1,    /* "sys_ahb1"   ,AHB1 clock             */
    AW_SYS_CLK_APB0,    /* "sys_apb0"   ,APB0 clock             */
    AW_SYS_CLK_APB1,    /* "sys_apb1"   ,APB1 clock             */
    AW_SYS_CLK_APB2,    /* "sys_apb2"   ,APB2 clock             */

    AW_CCU_CLK_NULL,    /* null module clock id                 */

    /* module clock */
    AW_MOD_CLK_NAND0,       /* "mod_nand0"                      */
    AW_MOD_CLK_NAND1,       /* "mod_nand1"                      */
    AW_MOD_CLK_SDC0,        /* "mod_sdc0"                       */
    AW_MOD_CLK_SDC1,        /* "mod_sdc1"                       */
    AW_MOD_CLK_SDC2,        /* "mod_sdc2"                       */
    AW_MOD_CLK_SDC3,        /* "mod_sdc3"                       */
    AW_MOD_CLK_TS,          /* "mod_ts"                         */
    AW_MOD_CLK_SS,          /* "mod_ss"                         */
    AW_MOD_CLK_SPI0,        /* "mod_spi0"                       */
    AW_MOD_CLK_SPI1,        /* "mod_spi1"                       */
    AW_MOD_CLK_SPI2,        /* "mod_spi2"                       */
    AW_MOD_CLK_SPI3,        /* "mod_spi3"                       */
    AW_MOD_CLK_I2S0,        /* "mod_i2s0"                       */
    AW_MOD_CLK_I2S1,        /* "mod_i2s1"                       */
    AW_MOD_CLK_SPDIF,       /* "mod_spdif"                      */
    AW_MOD_CLK_USBPHY0,     /* "mod_usbphy0"                    */
    AW_MOD_CLK_USBPHY1,     /* "mod_usbphy1"                    */
    AW_MOD_CLK_USBPHY2,     /* "mod_usbphy2"                    */
    AW_MOD_CLK_USBEHCI0,    /* "mod_usbehci0"                   */
    AW_MOD_CLK_USBEHCI1,    /* "mod_usbehci1"                   */
    AW_MOD_CLK_USBOHCI0,    /* "mod_usbohci0"                   */
    AW_MOD_CLK_USBOHCI1,    /* "mod_usbohci1"                   */
    AW_MOD_CLK_USBOHCI2,    /* "mod_usbohci2"                   */
    AW_MOD_CLK_USBOTG,      /* "mod_usbotg"                     */
    AW_MOD_CLK_MDFS,        /* "mod_mdfs"                       */
    AW_MOD_CLK_DEBE0,       /* "mod_debe0"                      */
    AW_MOD_CLK_DEBE1,       /* "mod_debe1"                      */
    AW_MOD_CLK_DEFE0,       /* "mod_defe0"                      */
    AW_MOD_CLK_DEFE1,       /* "mod_defe1"                      */
    AW_MOD_CLK_DEMIX,       /* "mod_demp"                       */
    AW_MOD_CLK_LCD0CH0,     /* "mod_lcd0ch0"                    */
    AW_MOD_CLK_LCD0CH1,     /* "mod_lcd0ch1"                    */
    AW_MOD_CLK_LCD1CH0,     /* "mod_lcd1ch0"                    */
    AW_MOD_CLK_LCD1CH1,     /* "mod_lcd1ch1"                    */
    AW_MOD_CLK_CSI0S,       /* "mod_csi0s"                      */
    AW_MOD_CLK_CSI0M,       /* "mod_csi0m"                      */
    AW_MOD_CLK_CSI1S,       /* "mod_csi1s"                      */
    AW_MOD_CLK_CSI1M,       /* "mod_csi1m"                      */
    AW_MOD_CLK_VE,          /* "mod_ve"                         */
    AW_MOD_CLK_ADDA,        /* "mod_adda"                       */
    AW_MOD_CLK_AVS,         /* "mod_avs"                        */
    AW_MOD_CLK_HDMI,        /* "mod_hdmi"                       */
    AW_MOD_CLK_PS,          /* "mod_ps"                         */
    AW_MOD_CLK_MTCACC,      /* "mod_mtcacc"                     */
    AW_MOD_CLK_MBUS0,       /* "mod_mbus0"                      */
    AW_MOD_CLK_MBUS1,       /* "mod_mbus1"                      */
    AW_MOD_CLK_DRAM,        /* "mod_dram"                       */
    AW_MOD_CLK_MIPIDSIS,    /* "mod_mipidsis"                   */
    AW_MOD_CLK_MIPIDSIP,    /* "mod_mipidsip"                   */
    AW_MOD_CLK_MIPICSIS,    /* "mod_mipicsis"                   */
    AW_MOD_CLK_MIPICSIP,    /* "mod_mipicsip"                   */
    AW_MOD_CLK_IEPDRC0,     /* "mod_iepdrc0"                    */
    AW_MOD_CLK_IEPDRC1,     /* "mod_iepdrc1"                    */
    AW_MOD_CLK_IEPDEU0,     /* "mod_iepdeu0"                    */
    AW_MOD_CLK_IEPDEU1,     /* "mod_iepdeu1"                    */
    AW_MOD_CLK_GPUCORE,     /* "mod_gpucore"                    */
    AW_MOD_CLK_GPUMEM,      /* "mod_gpumem"                     */
    AW_MOD_CLK_GPUHYD,      /* "mod_gpuhyd"                     */
    AW_MOD_CLK_TWI0,        /* "mod_twi0"                       */
    AW_MOD_CLK_TWI1,        /* "mod_twi1"                       */
    AW_MOD_CLK_TWI2,        /* "mod_twi2"                       */
    AW_MOD_CLK_TWI3,        /* "mod_twi3"                       */
    AW_MOD_CLK_UART0,       /* "mod_uart0"                      */
    AW_MOD_CLK_UART1,       /* "mod_uart1"                      */
    AW_MOD_CLK_UART2,       /* "mod_uart2"                      */
    AW_MOD_CLK_UART3,       /* "mod_uart3"                      */
    AW_MOD_CLK_UART4,       /* "mod_uart4"                      */
    AW_MOD_CLK_UART5,       /* "mod_uart5"                      */
    AW_MOD_CLK_GMAC,        /* "mod_gmac"                       */
    AW_MOD_CLK_DMA,         /* "mod_dma"                        */
    AW_MOD_CLK_HSTMR,       /* "mod_hstmr"                      */
    AW_MOD_CLK_MSGBOX,      /* "mod_msgbox"                     */
    AW_MOD_CLK_SPINLOCK,    /* "mod_spinlock"                   */
    AW_MOD_CLK_LVDS,        /* "mod_lvds"                       */
    AW_MOD_CLK_SMPTWD,      /* "smp_twd"                        */

    /* axi module gating */
    AW_AXI_CLK_DRAM,        /* "axi_dram"                       */

    /* ahb module gating */
    AW_AHB_CLK_MIPICSI,     /* "ahb_mipicsi"                    */
    AW_AHB_CLK_MIPIDSI,     /* "ahb_mipidsi"                    */
    AW_AHB_CLK_SS,          /* "ahb_ss"                         */
    AW_AHB_CLK_DMA,         /* "ahb_dma"                        */
    AW_AHB_CLK_SDMMC0,      /* "ahb_sdmmc0"                     */
    AW_AHB_CLK_SDMMC1,      /* "ahb_sdmmc1"                     */
    AW_AHB_CLK_SDMMC2,      /* "ahb_sdmmc2"                     */
    AW_AHB_CLK_SDMMC3,      /* "ahb_sdmmc3"                     */
    AW_AHB_CLK_NAND1,       /* "ahb_nand1"                      */
    AW_AHB_CLK_NAND0,       /* "ahb_nand0"                      */
    AW_AHB_CLK_SDRAM,       /* "ahb_sdram"                      */
    AW_AHB_CLK_GMAC,        /* "ahb_gmac"                       */
    AW_AHB_CLK_TS,          /* "ahb_ts"                         */
    AW_AHB_CLK_HSTMR,       /* "ahb_hstmr"                      */
    AW_AHB_CLK_SPI0,        /* "ahb_spi0"                       */
    AW_AHB_CLK_SPI1,        /* "ahb_spi1"                       */
    AW_AHB_CLK_SPI2,        /* "ahb_spi2"                       */
    AW_AHB_CLK_SPI3,        /* "ahb_spi3"                       */
    AW_AHB_CLK_OTG,         /* "ahb_otg"                        */
    AW_AHB_CLK_EHCI0,       /* "ahb_ehci0"                      */
    AW_AHB_CLK_EHCI1,       /* "ahb_ehci1"                      */
    AW_AHB_CLK_OHCI0,       /* "ahb_ohci0"                      */
    AW_AHB_CLK_OHCI1,       /* "ahb_ohci1"                      */
    AW_AHB_CLK_OHCI2,       /* "ahb_ohci2"                      */
    AW_AHB_CLK_VE,          /* "ahb_ve"                         */
    AW_AHB_CLK_LCD0,        /* "ahb_lcd0"                       */
    AW_AHB_CLK_LCD1,        /* "ahb_lcd1"                       */
    AW_AHB_CLK_CSI0,        /* "ahb_csi0"                       */
    AW_AHB_CLK_CSI1,        /* "ahb_csi1"                       */
    AW_AHB_CLK_HDMID,       /* "ahb_hdmid"                      */
    AW_AHB_CLK_DEBE0,       /* "ahb_debe0"                      */
    AW_AHB_CLK_DEBE1,       /* "ahb_debe1"                      */
    AW_AHB_CLK_DEFE0,       /* "ahb_defe0"                      */
    AW_AHB_CLK_DEFE1,       /* "ahb_defe1"                      */
    AW_AHB_CLK_MP,          /* "ahb_mp"                         */
    AW_AHB_CLK_GPU,         /* "ahb_gpu"                        */
    AW_AHB_CLK_MSGBOX,      /* "ahb_msgbox"                     */
    AW_AHB_CLK_SPINLOCK,    /* "ahb_spinlock"                   */
    AW_AHB_CLK_DEU0,        /* "ahb_deu0"                       */
    AW_AHB_CLK_DEU1,        /* "ahb_deu1"                       */
    AW_AHB_CLK_DRC0,        /* "ahb_drc0"                       */
    AW_AHB_CLK_DRC1,        /* "ahb_drc1"                       */
    AW_AHB_CLK_MTCACC,      /* "ahb_mtcacc"                     */

    /* apb module gating */
    AW_APB_CLK_ADDA,        /* "apb_adda"                       */
    AW_APB_CLK_SPDIF,       /* "apb_spdif"                      */
    AW_APB_CLK_PIO,         /* "apb_pio"                        */
    AW_APB_CLK_I2S0,        /* "apb_i2s0"                       */
    AW_APB_CLK_I2S1,        /* "apb_i2s1"                       */
    AW_APB_CLK_TWI0,        /* "apb_twi0"                       */
    AW_APB_CLK_TWI1,        /* "apb_twi1"                       */
    AW_APB_CLK_TWI2,        /* "apb_twi2"                       */
    AW_APB_CLK_TWI3,        /* "apb_twi3"                       */
    AW_APB_CLK_UART0,       /* "apb_uart0"                      */
    AW_APB_CLK_UART1,       /* "apb_uart1"                      */
    AW_APB_CLK_UART2,       /* "apb_uart2"                      */
    AW_APB_CLK_UART3,       /* "apb_uart3"                      */
    AW_APB_CLK_UART4,       /* "apb_uart4"                      */
    AW_APB_CLK_UART5,       /* "apb_uart5"                      */

    /* dram module gating */
    AW_DRAM_CLK_VE,         /* "dram_ve"                        */
    AW_DRAM_CLK_CSI0,       /* "dram_csi0"                      */
    AW_DRAM_CLK_CSI1,       /* "dram_csi1"                      */
    AW_DRAM_CLK_TS,         /* "dram_ts"                        */
    AW_DRAM_CLK_DRC0,       /* "dram_drc0"                      */
    AW_DRAM_CLK_DRC1,       /* "dram_drc1"                      */
    AW_DRAM_CLK_DEU0,       /* "dram_deu0"                      */
    AW_DRAM_CLK_DEU1,       /* "dram_deu1"                      */
    AW_DRAM_CLK_DEFE0,      /* "dram_defe0"                     */
    AW_DRAM_CLK_DEFE1,      /* "dram_defe1"                     */
    AW_DRAM_CLK_DEBE0,      /* "dram_debe0"                     */
    AW_DRAM_CLK_DEBE1,      /* "dram_debe1"                     */
    AW_DRAM_CLK_MP,         /* "dram_mp"                        */

    AW_CCU_CLK_CNT          /* invalid id, for calc count       */

} __aw_ccu_clk_id_e;



typedef __s32 (*ISRCallback)( void *pArg);
/* 刷新标记位 */
#define  CACHE_FLUSH_I_CACHE_REGION				0  /* 清除I-cache中代表主存中一块区域的cache行 			*/
#define  CACHE_FLUSH_D_CACHE_REGION				1  /* 清除D-cache中代表主存中一块区域的cache行 			*/
#define  CACHE_FLUSH_CACHE_REGION				2  /* 清除D-cache和I-cache中代表主存中一块区域的cache行 */
#define  CACHE_CLEAN_D_CACHE_REGION				3  /* 清理D-cache中代表主存中一块区域的cache行 			*/
#define  CACHE_CLEAN_FLUSH_D_CACHE_REGION	 	4  /* 清理并清除D-cache中代表主存中一块区域的cache行 	*/
#define  CACHE_CLEAN_FLUSH_CACHE_REGION			5  /* 清理并清除D-cache，接下来解除I-cache 				*/

__hdle OSAL_GPIO_Request(user_gpio_set_t *gpio_list, __u32 group_count_max);
__hdle OSAL_GPIO_Request_Ex(char *main_name, const char *sub_name);
__s32 OSAL_GPIO_Release(__hdle p_handler, __s32 if_release_to_default_status);
__s32 OSAL_GPIO_DevGetAllPins_Status(unsigned p_handler, user_gpio_set_t *gpio_status, unsigned gpio_count_max, unsigned if_get_from_hardware);
__s32 OSAL_GPIO_DevGetONEPins_Status(unsigned p_handler, user_gpio_set_t *gpio_status,const char *gpio_name,unsigned if_get_from_hardware);
__s32 OSAL_GPIO_DevSetONEPin_Status(u32 p_handler, user_gpio_set_t *gpio_status, const char *gpio_name, __u32 if_set_to_current_input_status);
__s32 OSAL_GPIO_DevSetONEPIN_IO_STATUS(u32 p_handler, __u32 if_set_to_output_status, const char *gpio_name);
__s32 OSAL_GPIO_DevSetONEPIN_PULL_STATUS(u32 p_handler, __u32 set_pull_status, const char *gpio_name);
__s32 OSAL_GPIO_DevREAD_ONEPIN_DATA(u32 p_handler, const char *gpio_name);
__s32 OSAL_GPIO_DevWRITE_ONEPIN_DATA(u32 p_handler, __u32 value_to_gpio, const char *gpio_name);

int OSAL_Script_FetchParser_Data(char *main_name, char *sub_name, int value[], int count);

__s32 OSAL_CCMU_SetSrcFreq(__u32 nSclkNo, __u32 nFreq);
__u32 OSAL_CCMU_GetSrcFreq(__u32 nSclkNo);
__hdle OSAL_CCMU_OpenMclk(__s32 nMclkNo);
__s32  OSAL_CCMU_CloseMclk(__hdle hMclk);
__s32 OSAL_CCMU_SetMclkSrc(__hdle hMclk, __u32 nSclkNo);
__s32 OSAL_CCMU_GetMclkSrc(__hdle hMclk);
__s32 OSAL_CCMU_SetMclkDiv(__hdle hMclk, __s32 nDiv);
__u32 OSAL_CCMU_GetMclkDiv(__hdle hMclk);
__s32 OSAL_CCMU_MclkOnOff(__hdle hMclk, __s32 bOnOff);
__s32 OSAL_CCMU_MclkReset(__hdle hMclk, __s32 bReset);

void OSAL_InterruptDisable(__u32 IrqNo);
void OSAL_InterruptEnable(__u32 IrqNo);
int OSAL_RegISR(__u32 IrqNo,
				__u32 Flags,
				ISRCallback Handler,
				void *pArg,
				__u32 DataSize,
				__u32 Prio);
void OSAL_UnRegISR(__u32 IrqNo, ISRCallback Handler, void *pArg);

void *OSAL_PAtoVA(void * pa);
void *OSAL_VAtoPA(void * pa);

void * OSAL_malloc(__u32 Size);
void OSAL_free(void * pAddr);

void OSAL_IrqLock(__u32 *cpu_sr);
void OSAL_IrqUnLock(__u32 cpu_sr);

void OSAL_CacheRangeFlush(void *Address, __u32 Length, __u32 Flags);

int OSAL_sw_get_ic_ver(void);

#define sys_get_wvalue(n)   (*((volatile __u32 *)(n)))          /* word input */
#define sys_put_wvalue(n,c) (*((volatile __u32 *)(n))  = (c))   /* word output */


#endif  //__OSAL_DE_H__

