#include "init.test.h"
#include "exti.h"
#include "io.h"
#include "stm32f401xc.h"

volatile static bool enableLED = false;

void EXTI0_IRQHandler(void) {
  enableLED = true;
  exti_clear_pending(EXTI_0);
}

void delay(volatile uint32_t count) {
    while(count--) {
        __NOP();
    }
}

void init_mcu(void) {
  // rcc_hsi_clock_setup();
  rcc_clock_pll_setup(RCC_HSE_CONFIG_3V3_84MHZ);
  static periph_clk_config_t periph_config = {
    .ahb1 = (RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_DMA2EN),
    .ahb2 = 0x0,
    .apb1 = 0x0,
    .apb2 = RCC_APB2ENR_SYSCFGEN, // enable SYSCFGEN
  };
  rcc_enable_peripherals(&periph_config);

  static io_pin_config_t pin_config = {
    .mode   = IO_MODE_OUTPUT,
    .otype  = IO_OTYPE_PP,
    .pupd   = IO_PUPD_NO,
    .speed  = IO_SPEED_LOW,
    .altf   = IO_AF0,
  };

  static io_pin_config_t inpin_config = {
    .mode   = IO_MODE_INPUT,
    .otype  = IO_OTYPE_PP,
    .pupd   = IO_PUPD_DOWN,
    .speed  = IO_SPEED_LOW,
    .altf   = IO_AF0,
  };

  io_configure_pin(GPIOC, IO13, &pin_config);
  io_configure_pin(GPIOA, IO0, &inpin_config);

  io_set_out(GPIOC, IO13, IO_OUT_LOW);

  exti_configure(EXTI_0, EXTI_SOURCE_PORTA, EXTI_TRIG_RISING);
  exti_set_interrupt_mask(EXTI_0, EXTI_STATE_ENABLED);
  // NVIC_SetPriority(EXTI0_IRQn, 2); // Set priority (0 is highest)
  NVIC_EnableIRQ(EXTI0_IRQn);
}

void init_test(uint32_t *srcAddr, uint32_t *dstAddr, uint16_t length) {
  init_mcu();

  while(1) {
    if (enableLED) {
      io_set_out((GPIO_TypeDef *)GPIOC_BASE, IO13, IO_OUT_HIGH);
      delay(10000000);
      io_set_out((GPIO_TypeDef *)GPIOC_BASE, IO13, IO_OUT_LOW);
      enableLED = false;
    }
  }
}
