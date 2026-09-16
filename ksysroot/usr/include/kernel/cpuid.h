#ifndef CPUID_H
#define CPUID_H
#include <stdint.h>
#include <stdbool.h>
// edx
#define CPUID_EDX_MSR (1 << 5)
#define CPUID_EDX_SYSENTER (1 << 11)
#define CPUID_EDX_APIC (1 << 9)
struct cpuid_result {
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
};
static inline struct cpuid_result cpuid(uint32_t leaf, uint32_t subleaf)
{
    struct cpuid_result r;

    asm volatile (
        "cpuid"
        : "=a"(r.eax), "=b"(r.ebx), "=c"(r.ecx), "=d"(r.edx)
        : "a"(leaf), "c"(subleaf)
    );

    return r;
}
#endif