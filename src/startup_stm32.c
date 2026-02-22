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
irq_handler vector_table[] = {
    (irq_handler)&_estack,         // Top of Stack
    (irq_handler)Reset_Handler,
    (irq_handler)NMI_IRQHandler,
    (irq_handler)HardFault_IRQHandler,
    (irq_handler)MemManage_IRQHandler,
    (irq_handler)BusFault_IRQHandler,
    (irq_handler)UsageFault_IRQHandler,
    0,
    0,
    0,
    0,
    (irq_handler)SVCall_IRQHandler,
    (irq_handler)DebugMonitor_IRQHandler,
    0,
    (irq_handler)PendSV_IRQHandler,
    (irq_handler)SysTick_IRQHandler,

    /* Peripheral Interrupts start at IRQn 0 */
    (irq_handler)WWDG_IRQHandler,
    (irq_handler)EXTI16_PVD_IRQHandler,
    (irq_handler)EXTI21_TAMP_STAMP_IRQHandler,
    (irq_handler)EXTI22_RTC_WKUP_IRQHandler,
    (irq_handler)FLASH_IRQHandler,
    (irq_handler)RCC_IRQHandler,
    (irq_handler)EXTI0_IRQHandler,
    (irq_handler)EXTI1_IRQHandler,
    (irq_handler)EXTI2_IRQHandler,
    (irq_handler)EXTI3_IRQHandler,
    (irq_handler)EXTI4_IRQHandler,
    (irq_handler)DMA1_Stream0_IRQHandler,
    (irq_handler)DMA1_Stream1_IRQHandler,
    (irq_handler)DMA1_Stream2_IRQHandler,
    (irq_handler)DMA1_Stream3_IRQHandler,
    (irq_handler)DMA1_Stream4_IRQHandler,
    (irq_handler)DMA1_Stream5_IRQHandler,
    (irq_handler)DMA1_Stream6_IRQHandler,
    (irq_handler)ADC_IRQHandler,
    (irq_handler)EXTI9_5_IRQHandler,
    (irq_handler)TIM1_BRK_TIM9_IRQHandler,
    (irq_handler)TIM1_UP_TIM10_IRQHandler,
    (irq_handler)TIM1_TRG_COM_TIM11_IRQHandler,
    (irq_handler)TIM1_CC_IRQHandler,
    (irq_handler)TIM2_IRQHandler,
    (irq_handler)TIM3_IRQHandler,
    (irq_handler)TIM4_IRQHandler,
    (irq_handler)I2C1_EV_IRQHandler,
    (irq_handler)I2C1_ER_IRQHandler,
    (irq_handler)I2C2_EV_IRQHandler,
    (irq_handler)I2C2_ER_IRQHandler,
    (irq_handler)SPI1_IRQHandler,
    (irq_handler)SPI2_IRQHandler,
    (irq_handler)USART1_IRQHandler,
    (irq_handler)USART2_IRQHandler,
    (irq_handler)EXTI15_10_IRQHandler,
    (irq_handler)EXTI17_RTC_Alarm_IRQHandler,
    (irq_handler)EXTI18_OTG_FS_WKUP_IRQHandler,
    (irq_handler)DMA1_Stream7_IRQHandler,
    (irq_handler)SDIO_IRQHandler,
    (irq_handler)TIM5_IRQHandler,
    (irq_handler)SPI3_IRQHandler,
    (irq_handler)DMA2_Stream0_IRQHandler,
    (irq_handler)DMA2_Stream1_IRQHandler,
    (irq_handler)DMA2_Stream2_IRQHandler,
    (irq_handler)DMA2_Stream3_IRQHandler,
    (irq_handler)DMA2_Stream4_IRQHandler,
    (irq_handler)OTG_FS_IRQHandler,
    (irq_handler)DMA2_Stream5_IRQHandler,
    (irq_handler)DMA2_Stream6_IRQHandler,
    (irq_handler)DMA2_Stream7_IRQHandler,
    (irq_handler)USART6_IRQHandler,
    (irq_handler)I2C3_EV_IRQHandler,
    (irq_handler)I2C3_ER_IRQHandler,
    (irq_handler)FPU_IRQHandler,
    (irq_handler)SPI4_IRQHandler,
};
