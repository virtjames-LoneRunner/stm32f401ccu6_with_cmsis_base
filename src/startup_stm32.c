#include <stdint.h>
#include "interrupt_stm32.h"

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

__attribute__((section(".isr_vector"), used))
uint32_t vector_table[] = {
    (uint32_t)&_estack,         // Top of Stack
    (uint32_t)Reset_Handler,
    (uint32_t)NMI_Handler,
    (uint32_t)HardFault_Handler,
    (uint32_t)MemManage_Handler,
    (uint32_t)BusFault_Handler,
    (uint32_t)UsageFault_Handler,
    0,
    (uint32_t)SVCall_Handler,
    (uint32_t)DebugMonitor_Handler,
    0,
    (uint32_t)PendSV_Handler,
    (uint32_t)SysTick_Handler,
    (uint32_t)WWDG_Handler,
    (uint32_t)EXTI16_PVD_Handler,
    (uint32_t)EXTI21_TAMP_STAMP_Handler,
    (uint32_t)EXTI22_RTC_WKUP_Handler,
    (uint32_t)FLASH_Handler,
    (uint32_t)RCC_Handler,
    (uint32_t)EXTI0_Handler,
    (uint32_t)EXTI1_Handler,
    (uint32_t)EXTI2_Handler,
    (uint32_t)EXTI3_Handler,
    (uint32_t)EXTI4_Handler,
    (uint32_t)DMA1_Stream0_Handler,
    (uint32_t)DMA1_Stream1_Handler,
    (uint32_t)DMA1_Stream2_Handler,
    (uint32_t)DMA1_Stream3_Handler,
    (uint32_t)DMA1_Stream4_Handler,
    (uint32_t)DMA1_Stream5_Handler,
    (uint32_t)DMA1_Stream6_Handler,
    (uint32_t)ADC_Handler,
    (uint32_t)EXTI9_5_Handler,
    (uint32_t)TIM1_BRK_TIM9_Handler,
    (uint32_t)TIM1_UP_TIM10_Handler,
    (uint32_t)TIM1_TRG_COM_TIM11_Handler,
    (uint32_t)TIM1_CC_Handler,
    (uint32_t)TIM2_Handler,
    (uint32_t)TIM3_Handler,
    (uint32_t)TIM4_Handler,
    (uint32_t)I2C1_EV_Handler,
    (uint32_t)I2C1_ER_Handler,
    (uint32_t)I2C2_EV_Handler,
    (uint32_t)I2C2_ER_Handler,
    (uint32_t)SPI1_Handler,
    (uint32_t)SPI2_Handler,
    (uint32_t)USART1_Handler,
    (uint32_t)USART2_Handler,
    (uint32_t)EXTI15_10_Handler,
    (uint32_t)EXTI17_RTC_Alarm_Handler,
    (uint32_t)EXTI18_OTG_FS_WKUP_Handler,
    (uint32_t)DMA1_Stream7_Handler,
    (uint32_t)SDIO_Handler,
    (uint32_t)TIM5_Handler,
    (uint32_t)SPI3_Handler,
    (uint32_t)DMA2_Stream0_Handler,
    (uint32_t)DMA2_Stream1_Handler,
    (uint32_t)DMA2_Stream2_Handler,
    (uint32_t)DMA2_Stream3_Handler,
    (uint32_t)DMA2_Stream4_Handler,
    (uint32_t)OTG_FS_Handler,
    (uint32_t)DMA2_Stream5_Handler,
    (uint32_t)DMA2_Stream6_Handler,
    (uint32_t)DMA2_Stream7_Handler,
    (uint32_t)USART6_Handler,
    (uint32_t)I2C3_EV_Handler,
    (uint32_t)I2C3_ER_Handler,
    (uint32_t)FPU_Handler,
    (uint32_t)SPI4_Handler,
};
