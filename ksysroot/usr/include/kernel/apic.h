#ifndef APIC_H
#define APIC_H
#include <stdint.h>
#include <stdbool.h>

#define MasterPIC_code 0x20
#define SlavePIC_code 0xA0
#define MasterPIC_data 0x21
#define SlavePIC_data 0xA1

#define initialpic_freq 1193182

#define osfreq 250
#define tickinms (1000 / osfreq)

void remap_oldpic(uint8_t master_ofs, uint8_t slave_ofs);
void disable_oldpic();
void set_pit_freq(uint32_t freq);
bool has_apic();
void set_apic();
#endif