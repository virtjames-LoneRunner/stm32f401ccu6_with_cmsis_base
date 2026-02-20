#include <stdint.h>
#include "interrupt_stm32.h"

extern uint32_t _sidata, _sdata, _edata, _sbss, _ebss, _estack;
extern void main(void);

typedef void(*const irq_handler)(void);

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
irq_handler vector_table[] = {
    (irq_handler)&_estack,         // Top of Stack
    (irq_handler)Reset_Handler,
    (irq_handler)NMI_Handler,
    (irq_handler)HardFault_Handler,
    (irq_handler)MemManage_Handler,
    (irq_handler)BusFault_Handler,
    (irq_handler)UsageFault_Handler,
    0,
    0,
    0,
    0,
    (irq_handler)SVCall_Handler,
    (irq_handler)DebugMonitor_Handler,
    0,
    (irq_handler)PendSV_Handler,
    (irq_handler)SysTick_Handler,

    /* Peripheral Interrupts start at IRQn 0 */
    (irq_handler)WWDG_Handler,
    (irq_handler)EXTI16_PVD_Handler,
    (irq_handler)EXTI21_TAMP_STAMP_Handler,
    (irq_handler)EXTI22_RTC_WKUP_Handler,
    (irq_handler)FLASH_Handler,
    (irq_handler)RCC_Handler,
    (irq_handler)EXTI0_Handler,
    (irq_handler)EXTI1_Handler,
    (irq_handler)EXTI2_Handler,
    (irq_handler)EXTI3_Handler,
    (irq_handler)EXTI4_Handler,
    (irq_handler)DMA1_Stream0_Handler,
    (irq_handler)DMA1_Stream1_Handler,
    (irq_handler)DMA1_Stream2_Handler,
    (irq_handler)DMA1_Stream3_Handler,
    (irq_handler)DMA1_Stream4_Handler,
    (irq_handler)DMA1_Stream5_Handler,
    (irq_handler)DMA1_Stream6_Handler,
    (irq_handler)ADC_Handler,
    (irq_handler)EXTI9_5_Handler,
    (irq_handler)TIM1_BRK_TIM9_Handler,
    (irq_handler)TIM1_UP_TIM10_Handler,
    (irq_handler)TIM1_TRG_COM_TIM11_Handler,
    (irq_handler)TIM1_CC_Handler,
    (irq_handler)TIM2_Handler,
    (irq_handler)TIM3_Handler,
    (irq_handler)TIM4_Handler,
    (irq_handler)I2C1_EV_Handler,
    (irq_handler)I2C1_ER_Handler,
    (irq_handler)I2C2_EV_Handler,
    (irq_handler)I2C2_ER_Handler,
    (irq_handler)SPI1_Handler,
    (irq_handler)SPI2_Handler,
    (irq_handler)USART1_Handler,
    (irq_handler)USART2_Handler,
    (irq_handler)EXTI15_10_Handler,
    (irq_handler)EXTI17_RTC_Alarm_Handler,
    (irq_handler)EXTI18_OTG_FS_WKUP_Handler,
    (irq_handler)DMA1_Stream7_Handler,
    (irq_handler)SDIO_Handler,
    (irq_handler)TIM5_Handler,
    (irq_handler)SPI3_Handler,
    (irq_handler)DMA2_Stream0_Handler,
    (irq_handler)DMA2_Stream1_Handler,
    (irq_handler)DMA2_Stream2_Handler,
    (irq_handler)DMA2_Stream3_Handler,
    (irq_handler)DMA2_Stream4_Handler,
    (irq_handler)OTG_FS_Handler,
    (irq_handler)DMA2_Stream5_Handler,
    (irq_handler)DMA2_Stream6_Handler,
    (irq_handler)DMA2_Stream7_Handler,
    (irq_handler)USART6_Handler,
    (irq_handler)I2C3_EV_Handler,
    (irq_handler)I2C3_ER_Handler,
    (irq_handler)FPU_Handler,
    (irq_handler)SPI4_Handler,
};
