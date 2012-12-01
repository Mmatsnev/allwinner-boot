/*
**********************************************************************************************************************
*											        eGon
*						           the Embedded GO-ON Bootloader System
*									       eGON arm boot sub-system
*
*						  Copyright(C), 2006-2010, SoftWinners Microelectronic Co., Ltd.
*                                           All Rights Reserved
*
* File    : arm_swi
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
#include "include.h"

extern void jump_to( __u32 addr );
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
void eGon2_jump_to(__u32 addr)
{
    eGon2_printf("eGon2_jump_to\n");
	axp_set_next_poweron_status(0x0e);
	eGon2_timer_exit();			//关闭timer
    eGon2_key_exit();           //关闭按键
    eGon2_twi_exit();           //关闭TWI设备
    eGon2_block_device_exit(); //关闭用到的存储设备
    close_sys_int( );      // close system interrupt
	eGon2_Int_Exit( );     // 关闭所有中断
	disable_icache();      // 关闭icache
	mmu_disable();		   // 关闭mmu
    flush_dcache();		   // 关闭dcache
    disable_dcache();
    jump_to( addr );

    return;
}
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
void eGon2_jump_to_android_linux(__s32 zero, __s32 mod_id, __u32 paddr, __u32 kernal_addr)
{
    __u32 kernal_addr_base;
    
    void (*kernel_entry)(int zero, int arch, uint params);
	
	eGon2_printf("jump %x %x %x %x\n", zero, mod_id, paddr, kernal_addr);
	axp_set_next_poweron_status(0x0e);
	eGon2_timer_exit();			//关闭timer
    eGon2_key_exit();           //关闭按键
    eGon2_twi_exit();           //关闭TWI设备
    eGon2_printf("nand before %x %x %x %x\n", zero, mod_id, paddr, kernal_addr);
    eGon2_block_device_exit(); //关闭用到的存储设备
    eGon2_printf("nand after %x %x %x %x\n", zero, mod_id, paddr, kernal_addr);
    eGon2_printf("%s %d %x\n", __FILE__, __LINE__, kernal_addr);
    close_sys_int( );      // close system interrupt
    eGon2_printf("%s %d %x\n", __FILE__, __LINE__, kernal_addr);
	eGon2_Int_Exit( );     // 关闭所有中断
	eGon2_printf("%s %d %x\n", __FILE__, __LINE__, kernal_addr);
	disable_icache();      // 关闭icache
	eGon2_printf("%s %d %x\n", __FILE__, __LINE__, kernal_addr);
	mmu_disable();		   // 关闭mmu
	eGon2_printf("%s %d %x\n", __FILE__, __LINE__, kernal_addr);
    flush_dcache();		   // 关闭dcache
    eGon2_printf("%s %d %x\n", __FILE__, __LINE__, kernal_addr);
    disable_dcache();
    eGon2_printf("%s %d %x\n", __FILE__, __LINE__, kernal_addr);
	eGon2_printf("%s %d %x\n", __FILE__, __LINE__, kernal_addr_base);
	kernal_addr_base = 0x4a000000;
	kernel_entry = (void (*)(int, int, __u32))(kernal_addr_base);
	eGon2_printf("%s %d %x\n", __FILE__, __LINE__, kernal_addr);
	kernel_entry(zero, mod_id, paddr);

    return;
}
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
void eGon2_jump_Fel( void )
{
    eGon2_printf("eGon2_jump_Fel\n");
	axp_set_next_poweron_status(0);
	eGon2_timer_exit();			//关闭timer
    eGon2_key_exit();           //关闭按键
    eGon2_twi_exit();           //关闭TWI设备
	eGon2_block_device_exit(); //关闭用到的存储设备
	close_sys_int( );                   // close system interrupt
	set_vect_high_addr( );              // set interrupt vector low address
	eGon2_Int_Exit( );     // 关闭所有中断
	disable_icache();      // 关闭icache
	mmu_disable();		   // 关闭mmu
    flush_dcache();		   // 关闭dcache
    disable_dcache();
    {
    	__u32 timedly;

    	for(timedly = 0; timedly < 5000; timedly ++);
    }
	jump_to( FEL_BASE );

	return ;
}
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
void eGon2_simple_jump_Fel( void )
{
    eGon2_printf("eGon2_simple_jump_Fel\n");
	eGon2_timer_exit();	   //关闭timer
    eGon2_key_exit();      //关闭按键
    eGon2_twi_exit();      //关闭TWI设备
	close_sys_int( );      // close system interrupt
	set_vect_high_addr( ); // set interrupt vector low address
	eGon2_Int_Exit( );     // 关闭所有中断
	disable_icache();      // 关闭icache
	mmu_disable();		   // 关闭mmu
    flush_dcache();		   // 关闭dcache
    disable_dcache();
    {
    	__u32 timedly;

    	for(timedly = 0; timedly < 5000; timedly ++);
    }
	jump_to( FEL_BASE );

	return ;
}

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
void eGon2_power_off(void)
{
	axp_set_next_poweron_status(0);
	eGon2_block_device_exit();
	axp_set_hardware_poweroff_vol();
	axp_set_power_off();

	for(;;);
}
