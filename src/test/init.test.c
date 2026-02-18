#include "init.test.h"
#include "dma.h"

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
    .apb2 = 0x0,
  };
  rcc_enable_peripherals(&periph_config);

  static io_pin_config_t pin_config = {
    .mode   = IO_MODE_OUTPUT,
    .otype  = IO_OTYPE_PP,
    .pupd   = IO_PUPD_NO,
    .speed  = IO_SPEED_LOW,
    .altf   = IO_AF0,
  };

  // GPIOC->MODER &= ~(3U << (13 * 2)); // Clear bits 26, 27
  // GPIOC->MODER |=  (1U << (13 * 2)); // Set bit 26 (Output mode)
  io_configure_pin((GPIO_TypeDef *)GPIOC_BASE, IO13, &pin_config);
  // io_configure_pin((GPIO_TypeDef *)GPIOB_BASE, IO10, &pin_config);
  io_configure_pin((GPIO_TypeDef *)GPIOA_BASE, IO11, &pin_config);
}

void init_test(uint32_t *srcAddr, uint32_t *dstAddr, uint16_t length) {
  init_mcu();

  const dma_stream_config_t dma_conf[] = {
    {
      .dmaIndex = DMA_2,
      .dmaStream = DMA_STREAM0,

      .channel = DMA_CH0,
      .mBurst = DMA_BURST_SINGLE,
      .pBurst = DMA_BURST_SINGLE,
      .enDBM = DMA_DBM_DISABLED,
      .dir = DMA_DIR_MEM_TO_MEM, // <--- ENSURE THIS IS SET
      .mInc = DMA_INC_MODE_INCR,
      .pInc = DMA_INC_MODE_INCR,
      .mSize = DMA_SIZE_WORD,
      .pSize = DMA_SIZE_WORD,
      // .pl = ,
      // .pIncos = ,
      // .mSize = ,
      // .pSize = ,
      // .mIncMode = ,
      // .pIncMode = ,
      // .circ = ,
      // .dir = ,
      // .pFCtrl = ,
      // .enTCIE = ,
      // .enHTIE = ,
      // .enTEIE = ,
      // .enDMEIE = ,
      .enStream = DMA_STREAM_ENABLE,
      // .m0Addr = ,
      // .m1Addr = ,
      // .pAddr = ,
      // .numDataTransfer = ,
    }
  };
  dma_configure_stream(&dma_conf[0]);
  for (int i = 0; i < 10; i++) {
    io_toggle_pin((GPIO_TypeDef *)GPIOC_BASE, IO13);
    delay(1000000); 
  }
  dma_start(dma_conf[0].dmaIndex, dma_conf[0].dmaStream, srcAddr, dstAddr, length);
  for (int i = 0; i < 3; i++) {
    io_toggle_pin((GPIO_TypeDef *)GPIOC_BASE, IO13);
    delay(5000000); 
  }

  while(1) {
      /* 3. Toggle PC13 */
      /* ODR = Output Data Register */
      // GPIOC->ODR ^= (1U << 13);
      // io_toggle_pin((GPIO_TypeDef *)GPIOC_BASE, IO13);
      // io_toggle_pin((GPIO_TypeDef *)GPIOB_BASE, IO10);
      // io_toggle_pin((GPIO_TypeDef *)GPIOA_BASE, IO11);
      // io_set_out((GPIO_TypeDef *)GPIOA_BASE, IO_MASK_11, IO_OUT_LOW);
      // delay(1); 
      //
      // io_set_out((GPIO_TypeDef *)GPIOA_BASE, IO_MASK_11, IO_OUT_HIGH);
      // delay(1); 

      /* On many Black Pill boards, the LED is 'active low' */
      /* (Pin LOW = LED ON, Pin HIGH = LED OFF) */
      
      // delay(900000000); 

      // io_set_out((GPIO_TypeDef *)GPIOA_BASE, IO_MASK_11, IO_OUT_HIGH);
      // delay(900000000); 

    // GPIOA->BSRR = (IO_MASK_11 << 16); 
    // GPIOA->BSRR = (IO_MASK_11); 
  }
}
