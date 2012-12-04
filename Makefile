all:
	make -f make_nand  -C boot1/core
	make -f make_sdmmc -C boot1/core

	make -C boot1/apps/Boot_Android
	make -C boot1/apps/Card_Android
	make -C boot1/driver/drv_de
