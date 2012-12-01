#ifndef   _MCTL_HAL_H   
#define   _MCTL_HAL_H


//#define LINUX_CONFIG
//#define FPGA_PLATFORM

//#define LPDDR2_FPGA_S2C_2CS_2CH
#define DDR3_32B
#define TEST_MEM 0x40000000


typedef struct __DRAM_PARA
{
	//normal configuration
	unsigned int        dram_clk;		
	unsigned int        dram_type;		//dram_type			DDR2: 2				DDR3: 3				LPDDR2: 6
    unsigned int        dram_zq;
    unsigned int		dram_odt_en;
    	
	//control configuration
	unsigned int		dram_para1;
    unsigned int		dram_para2;

	//timing configuration
	unsigned int		dram_mr0;
    unsigned int		dram_mr1;
    unsigned int		dram_mr2;
    unsigned int		dram_mr3;
    unsigned int		dram_tpr0;	
    unsigned int		dram_tpr1;	
    unsigned int		dram_tpr2;	
    unsigned int		dram_tpr3;			
    unsigned int		dram_tpr4;					
    unsigned int		dram_tpr5;					
   	unsigned int		dram_tpr6;	

    //reserved for future use
    unsigned int		dram_tpr7;
    unsigned int		dram_tpr8;
    unsigned int		dram_tpr9;
    unsigned int		dram_tpr10;
    unsigned int		dram_tpr11;
    unsigned int		dram_tpr12;
    unsigned int		dram_tpr13;
    	
}__dram_para_t;

extern __dram_para_t *dram_para;

static unsigned int DRAMC_init(__dram_para_t *para);
static unsigned int DRAMC_init_auto(__dram_para_t *para);
static unsigned int mctl_sys_init(void);
static unsigned int mctl_reset_release(void);
static unsigned int mctl_dll_init(unsigned int ch_index, __dram_para_t *para);
static unsigned int mctl_channel_init(unsigned int ch_index, __dram_para_t *para);
static unsigned int mctl_com_init(__dram_para_t *para);
static unsigned int mctl_port_cfg(void);
extern signed int init_DRAM(int type, void *para);
static unsigned int ss_bonding_id(void);
static void paraconfig(unsigned int *para, unsigned int mask, unsigned int value);

#endif  //_MCTL_HAL_H










