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
	}
	.bss : {
		*(.bss)
	}
}
