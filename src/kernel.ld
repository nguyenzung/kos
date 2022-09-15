ENTRY(start)

SECTIONS
{
	. = 1M;
	.text :
	{
		KEEP(*(.multiboot))
		*(.text) 
	}

	.data :
	{	
		*(.rodata)
		*(.data)
		KEEP(*(.init_array))
	}
	.bss : {
		*(.bss)
	}
}
