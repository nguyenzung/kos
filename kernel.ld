ENTRY(start)

SECTIONS
{
	. = 1M;
	.text ALIGN(0x1000) :
	{
		start_text = .;
		KEEP(*(.multiboot))
		*(.text) 
	}

	.rodata ALIGN(0x1000) :
    {
        *(.rodata*)
    }

	.data ALIGN(0x1000) :
	{	
		start_data = .;
		*(.data)
	}

	.bss : {
		*(.bss)
	}
}
