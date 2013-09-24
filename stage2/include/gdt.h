#ifndef GDT_H_
#define GDT_H_

const u8_t GDT_ACCESS_PRESENT = (1<<7);
const u8_t GDT_ACCESS_EX      = (1<<3);
const u8_t GDT_ACCESS_DC      = (1<<2);
const u8_t GDT_ACCESS_RW      = (1<<1);

const u8_t GDT_FLAG_GR        = (1<<7);
const u8_t GDT_FLAG_SZ        = (1<<6);

#include "tehboot.h"
#include "tbtype.h"

struct GDT_ENTRY_REAL {
	u16_t limit_low;
	u16_t base_low;
	u8_t  base_mid;
	u8_t  access_byte;
	u8_t  flags;
	u8_t  base_high;
} __attribute__((packed));

typedef struct GDT_ENTRY_REAL gdt_entry_t;

#define load_gdt( gdt ) \
	__asm__("lgdt (%[ptr])" : [ptr] "=r" ( (gdt) ) );

#define gdt_entry_set_limit( entry, limit ) \
	(entry)->limit_low = limit & 0x0000FFFF; \
	(entry)->flags    |= (limit>>16) & 0x0F

#define gdt_entry_set_base( entry, base ) \
	(entry)->base_low  = (base     & 0xFFFF); \
	(entry)->base_mid  = (base>>16) & 0xFF; \
	(entry)->base_high = (base>>24) & 0xFF

#define gdt_entry_enable_access( flag ) \
	(entry)->access_byte |= (flag)

#define gdt_entry_disable_access( flag ) \
	(entry)->access_byte &= ~(flag)

#define gdt_entry_enable_flag( flag ) \
	(entry)->flags |= flag

#define gdt_entry_disable_flag( flag ) \
	(entry)->flags &= ~(flag)

#endif
