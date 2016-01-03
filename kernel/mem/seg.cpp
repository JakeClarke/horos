
#define PRIVILAGE_LEVEL_KERN 0
#define PRIVILAGE_LEVEL_USER 3

#define SIG_SELECT_DESC_TYPE_GDT 0
#define SIG_SELECT_DESC_TYPE_LDT 1


#define SIG_DESC_TYPE_ACCESSED 1
#define SIG_DESC_TYPE_DATA_RO 0
#define SIG_DESC_TYPE_DATA_RW 2
#define SIG_DESC_TYPE_CODE_XO 8
#define SIG_DESC_TYPE_CODE_XR 10

#define KERNEL_CODE_START (0x00100000)
#define KERNEL_DATA_START (0x00100000)
#define KERNEL_STACK_START (0x00100000)



extern "C" {

	struct SegSelectDesc {
		unsigned char priv : 2;
		unsigned char type : 1; // 0 if GDT, 1 for LDT
		unsigned short offset : 13; // offset in selector tbl.
	};


	struct SegSelect {
		struct SegSelectDesc code, data, stack, extra, fs, gs;
	};

	struct SegDesc {
		short limitLow;
		short baseLow;

		unsigned char baseMid; // bits 23 : 15 for the base address
		unsigned char type : 4;
		unsigned char sysSeg : 1; // AKA s type in intel manual
		unsigned char priv : 2;
		unsigned char present : 1; // is present in physical memory
		unsigned char limitHigh : 5;
		unsigned char ign:1; // meaningless
		unsigned char D_B : 1;
		unsigned char limitGranularity : 1; // if clear limit range 1b - 1MiB 1b increments, if set limit is 1KiB to 4GiB in 4KiB increments
		unsigned char baseHigh;
	};


}

#define LIMIT_MASK 0xfff

namespace {
		SegDesc encodeSegDesc(unsigned int base, unsigned int limit, short type, short priv) {
		return {
			limit & 0xffff,
			base & 0xffff,

			(base >> 16), // base mid
			type & 0xf, // type
			1, // sysseg
			priv, // prival
			1, // present
			(limit >> 16), // limit high
			0, // ignore
			1, // D_B
			1, // we are only going to deal with 4k
			(base >> 16) & 0xff
		};
	}

	extern "C" {
		void selectSeg(SegSelect seg);
		void setGDT(SegDesc *, unsigned int);
		void reloadSeg();
	}
}

#define GDT_ENTRY_KERNEL_CODE (1)
#define GDT_ENTRY_KERNEL_DATA (2)
#define GDT_ENTRY_USER_CODE (3)
#define GDT_ENTRY_USER_DATA (4)


SegDesc gdt[5];


#define MEM_START 0x0
#define MEM_END 0xFFFFFFFF

extern "C" void gdtInit() {

	gdt[GDT_ENTRY_KERNEL_CODE] = encodeSegDesc(MEM_START, MEM_END, SIG_DESC_TYPE_CODE_XR, PRIVILAGE_LEVEL_KERN);
	gdt[GDT_ENTRY_KERNEL_DATA] = encodeSegDesc(MEM_START, MEM_END, SIG_DESC_TYPE_DATA_RW, PRIVILAGE_LEVEL_KERN);
	gdt[GDT_ENTRY_USER_CODE] = encodeSegDesc(MEM_START, MEM_END, SIG_DESC_TYPE_CODE_XR, PRIVILAGE_LEVEL_USER);
	gdt[GDT_ENTRY_USER_DATA] = encodeSegDesc(MEM_START, MEM_END, SIG_DESC_TYPE_DATA_RW, PRIVILAGE_LEVEL_USER);
	//gdt[GDT_ENTRY_KERNEL_CODE] = encodeSegDesc(KERNEL_CODE_START, 1, SIG_DESC_TYPE_CODE_XR, PRIVILAGE_LEVEL_KERN);
	//gdt[GDT_ENTRY_KERNEL_DATA] = encodeSegDesc(KERNEL_DATA_START, 2, SIG_DESC_TYPE_DATA_RW, PRIVILAGE_LEVEL_KERN);


	setGDT(&gdt[0], sizeof(gdt));
	reloadSeg();

	//SegSelect kernDesc  = {
	//	{PRIVILAGE_LEVEL_KERN, SIG_SELECT_DESC_TYPE_GDT, GDT_ENTRY_KERNEL_CODE},
	//	{PRIVILAGE_LEVEL_KERN, SIG_SELECT_DESC_TYPE_GDT, GDT_ENTRY_KERNEL_DATA}
	//};

	//selectSeg(kernDesc);
	
}