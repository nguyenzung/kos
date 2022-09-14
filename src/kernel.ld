ENTRY(start)

SECTIONS
{
	. = 50000;

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
