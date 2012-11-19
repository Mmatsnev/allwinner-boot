OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
SECTIONS
{
	. = 0x42400000;
	.boot_head ALIGN(4):
	{
		parameters/Boot1_head.o(.rodata)
	}

	.text ALIGN(4):
	{
		start/asm_start.o (.text)
		*(EXCLUDE_FILE(arm_board/arm_start.o).text)
	}

	.arm_start ALIGN(4):
	{
		_arm_start = .;
		arm_board/arm_start.o (.text)
		_arm_end = .;
	}

	.data ALIGN(4):
	{
		*(.data)
	}
	.rodata ALIGN(4):
	{
		*(.rodata)
	}

	.bss ALIGN(4):
	{
		_bss_start = .;
		*(.bss)
		_bss_end = .;
	}

	.notes ALIGN(4):
	{
		*(.note.*)
	}
}

