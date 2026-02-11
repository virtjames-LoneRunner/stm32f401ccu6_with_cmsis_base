#include "defines.h"
#include "stm32f401xc.h"
#include "rcc.h"

#define _RCC_REG(i)		MMIO32(RCC_BASE + ((i) >> 5))
#define _RCC_BIT(i)		(1 << ((i) & 0x1f))

const rcc_clock_conf rcc_hse_25mhz_3v3[] = {
	{ /* 84MHz */
		.pllm = 25,
		.plln = 336,
		.pllp = 4,
		.pllq = 7,
		.pllr = 0,
		.pll_source = RCC_CFGR_PLLSRC_HSE_CLK,
		.hpre = RCC_CFGR_HPRE_DIV1,
		.ppre1 = RCC_CFGR_PPRE1_DIV2,
		.ppre2 = RCC_CFGR_PPRE2_DIV1,
		.voltage_scale = PWR_SCALE1,
		.flash_config = FLASH_ACR_DCEN | FLASH_ACR_ICEN |
				FLASH_ACR_LATENCY_2WS,
		.ahb_frequency  = 84000000,
		.apb1_frequency = 42000000,
		.apb2_frequency = 84000000,
	},
};

// Copied from libopencm3.
void rcc_periph_clock_enable(enum rcc_periph_clken clken)
{
	_RCC_REG(clken) |= _RCC_BIT(clken);
}

void rcc_periph_clock_disable(enum rcc_periph_clken clken)
{
	_RCC_REG(clken) &= ~_RCC_BIT(clken);
}

void rcc_hsi_clock_setup() {
  /* Enable internal high-speed oscillator (HSI). */
  rcc_osc_on(RCC_HSI);
  rcc_wait_osc_ready(RCC_HSI);

  rcc_set_sysclk_src(RCC_CFGR_SW_HSI);
}

void rcc_clock_pll_setup(const pll_config_e config_select) {
  const rcc_clock_conf *config = &rcc_hse_25mhz_3v3[config_select];

  /* Enable internal high-speed oscillator (HSI). */
  rcc_osc_on(RCC_HSI);
  rcc_wait_osc_ready(RCC_HSI);

  rcc_set_sysclk_src(RCC_CFGR_SW_HSI);
  if (config->pll_source == RCC_CFGR_PLLSRC_HSE_CLK) {
    rcc_osc_on(RCC_HSE);
    rcc_wait_osc_ready(RCC_HSE);
  }
}


void rcc_enable_peripherals(const periph_clk_config_t *config) {
    if (config->ahb1) RCC->AHB1ENR |= config->ahb1;
    if (config->ahb2) RCC->AHB2ENR |= config->ahb2;
    if (config->apb1) RCC->APB1ENR |= config->apb1;
    if (config->apb2) RCC->APB2ENR |= config->apb2;
    // Dummy read
    (void)RCC->AHB1ENR;
}

static void rcc_osc_on(const rcc_clock_src_e osc_src) {
  switch (osc_src) {
    case RCC_HSI:
      RCC->CR |= RCC_CR_HSION;
      break;
    case RCC_HSE:
      RCC->CR |= RCC_CR_HSEON;
      break;
    case RCC_PLL:
      RCC->CR |= RCC_CR_PLLON;
      break;
  }
}

static void rcc_osc_off(const rcc_clock_src_e osc_src) {
  switch (osc_src) {
    case RCC_HSI:
      RCC->CR &= ~RCC_CR_HSION;
      break;
    case RCC_HSE:
      RCC->CR &= ~RCC_CR_HSEON;
      break;
    case RCC_PLL:
      RCC->CR &= ~RCC_CR_PLLON;
      break;
  }
}

static void rcc_wait_osc_ready(const rcc_clock_src_e osc_src) {
  while (!rcc_is_osc_ready(osc_src));
}

static bool rcc_is_osc_ready(const rcc_clock_src_e osc_src) {
  switch (osc_src) {
    case RCC_HSI:
      return RCC->CR & RCC_CR_HSIRDY;
    case RCC_HSE:
      return RCC->CR & RCC_CR_HSERDY;
    case RCC_PLL:
      return RCC->CR & RCC_CR_PLLRDY;
  }
  return false;
}

void rcc_set_sysclk_src(const uint32_t clk) {
  uint32_t reg32 = RCC->CFGR;

  // reset SW1:0
  reg32 &= ~((1 << 1) | (1 << 0));
  RCC->CFGR = (reg32 | clk);
}
