/*
 * circle.ld
 */

SECTIONS
{
	. = 0x0;
	
	.text : {
		*(.text*)
	}

	_etext = .;

	.rodata : {
		*(.rodata*)
	}

	__init_start = .;

	.init_array : {
		*(.init_array*)
	}

	__init_end = .;

	.data : {
		*(.data*)
	}

	__bss_start = .;

	.bss : {
		*(.bss*)
	}

	_end = .;
}
