#ifndef __AXP_HEAD__
#define __AXP_HEAD__
#include "p2wi.h"

#define   BOOT_POWER22_OUTPUT_CTL2     	   			(0x12)
#define   BOOT_POWER22_OUTPUT_DLDO3_VO					(0x17)
#define   BOOT_POWER22_OUTPUT_DLDO3_SW					(0x12)
#define   BOOT_POWER22_OUTPUT_ELDO3_VO				(0x1B)

int axp221_set_dc1sw(int on_off);
int axp221_set_dldo3(int on_off);

#endif

