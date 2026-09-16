#include "kernel/apic.h"
#include "kernel/msr.h"
#include "kernel/cpuid.h"
#include "kernel/paging.h"
#include "kernel/io.h"
#include <stdint.h>
#include <stdbool.h>
#include "lib/string.h"
#include "kernel/kernel.h"

uintptr_t basepage_apic_phys;
volatile uint32_t* lapic;

void remap_oldpic(uint8_t master_ofs, uint8_t slave_ofs) {
    // Master = IRQ0 - IRQ7
    // Slave = IRQ8 - IRQ15

    outb(MasterPIC_code, 0x11);
    outb(SlavePIC_code, 0x11);

    outb(MasterPIC_data, master_ofs);
    outb(SlavePIC_data, slave_ofs);

    outb(MasterPIC_data, 4); // dizer para o master que o slave está ligado ao irq2 no master
    outb(SlavePIC_data, 2);

    outb(MasterPIC_data, 1); // 8080 -> 8086
    outb(SlavePIC_data, 1);

    outb(MasterPIC_data, 0); // desmascarar
    outb(SlavePIC_data, 0);
}

void disable_oldpic() {
    // thanks 8259 PIC
    // but you need to rest
    outb(MasterPIC_data, 0xFF);
    outb(SlavePIC_data, 0xFF);
    // now, use APIC
}

bool has_apic() {
    struct cpuid_result a = cpuid(1, 0);
    return a.edx & CPUID_EDX_APIC;
}
void set_apic() {
    if (!has_apic()) return;
    uintptr_t apicbasemsr = rdmsr(IA32_APIC_BASE_MSR) | IA32_APIC_BASE_MSR_ENABLE;
    wrmsr(IA32_APIC_BASE_MSR, apicbasemsr);

    basepage_apic_phys = apicbasemsr >> 12;
    lapic = phys_to_virt(basepage_apic_phys, 1); // Local APIC mapped :D

}

void set_pit_freq(uint32_t freq) {
    uint16_t div = initialpic_freq / freq;
    outb(0x43, 0b00110111); // set command (channel 0, square wave)
    outb(0x40, div & 0xFF); // low
    outb(0x40, div >> 8); // high
}