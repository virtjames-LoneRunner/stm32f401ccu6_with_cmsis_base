#include <stdint.h>

extern uint32_t _sidata, _sdata, _edata, _sbss, _ebss, _estack;
extern void main(void);

// Reset Handler: The first code the CPU runs
void Reset_Handler(void) {
    // 1. Copy .data from FLASH to RAM
    uint32_t *pSrc = &_sidata;
    uint32_t *pDest = &_sdata;
    while (pDest < &_edata) {
        *pDest++ = *pSrc++;
    }

    // 2. Initialize .bss to zero
    pDest = &_sbss;
    while (pDest < &_ebss) {
        *pDest++ = 0;
    }

    // 3. Call SystemInit (usually provided by CMSIS)
    // SystemInit(); 

    // 4. Jump to main
    main();

    while (1); // Trap if main returns
}

// Minimal Vector Table
__attribute__((section(".isr_vector"), used))
uint32_t vector_table[] = {
    (uint32_t)&_estack,         // Top of Stack
    (uint32_t)Reset_Handler,    // Reset Handler
    0,                          // NMI Handler
    0,                          // HardFault Handler
    // ... Add more handlers as needed
};
