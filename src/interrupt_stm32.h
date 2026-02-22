#ifndef INTERRUPT_STM32_H
#define INTERRUPT_STM32_H

typedef void(*const irq_handler)(void);

void Default_IRQHandler(void) {
  while(1);
}

void __attribute__((weak, alias("Default_IRQHandler"))) NMI_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) HardFault_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) MemManage_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) BusFault_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) UsageFault_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) SVCall_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) DebugMonitor_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) PendSV_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) SysTick_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) WWDG_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) EXTI16_PVD_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) EXTI21_TAMP_STAMP_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) EXTI22_RTC_WKUP_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) FLASH_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) RCC_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) EXTI0_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) EXTI1_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) EXTI2_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) EXTI3_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) EXTI4_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) DMA1_Stream0_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) DMA1_Stream1_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) DMA1_Stream2_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) DMA1_Stream3_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) DMA1_Stream4_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) DMA1_Stream5_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) DMA1_Stream6_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) ADC_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) EXTI9_5_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) TIM1_BRK_TIM9_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) TIM1_UP_TIM10_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) TIM1_TRG_COM_TIM11_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) TIM1_CC_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) TIM2_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) TIM3_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) TIM4_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) I2C1_EV_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) I2C1_ER_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) I2C2_EV_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) I2C2_ER_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) SPI1_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) SPI2_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) USART1_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) USART2_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) EXTI15_10_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) EXTI17_RTC_Alarm_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) EXTI18_OTG_FS_WKUP_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) DMA1_Stream7_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) SDIO_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) TIM5_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) SPI3_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) DMA2_Stream0_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) DMA2_Stream1_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) DMA2_Stream2_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) DMA2_Stream3_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) DMA2_Stream4_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) OTG_FS_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) DMA2_Stream5_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) DMA2_Stream6_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) DMA2_Stream7_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) USART6_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) I2C3_EV_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) I2C3_ER_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) FPU_IRQHandler(void);
void __attribute__((weak, alias("Default_IRQHandler"))) SPI4_IRQHandler(void);

#endif
