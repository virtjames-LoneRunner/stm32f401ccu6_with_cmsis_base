#include "rcc.h"

#define _RCC_REG(i)		MMIO32(RCC_BASE + ((i) >> 5))
#define _RCC_BIT(i)		(1 << ((i) & 0x1f))

/* Set the default clock frequencies after reset. */
uint32_t rcc_ahb_frequency = 16000000;
uint32_t rcc_apb1_frequency = 16000000;
uint32_t rcc_apb2_frequency = 16000000;

const rcc_clock_conf rcc_hse_25mhz_3v3[] = {
	{ /* 84MHz */
    /* Using 25MHz external as HSE; no bypass */
		.pllm = 25,
		.plln = 336,
		.pllp = 4,
		.pllq = 7,
		.pllr = 0,
		.pll_source = RCC_CFGR_PLLSRC_HSE_CLK,
		.hpre = RCC_CFGR_HPRE_DIV1,
		.ppre1 = RCC_CFGR_PPRE1_DIV2,
		.ppre2 = RCC_CFGR_PPRE2_DIV1,
		.voltage_scale = PWR_SCALE2,
		.flash_config = FLASH_ACR_DCEN | FLASH_ACR_ICEN |
				FLASH_ACR_LATENCY_2WS | FLASH_ACR_PRFTEN,
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

  // turn on peripheral clock to APB1 PWR clock
  rcc_periph_clock_enable(RCC_PWR);
  // set VOS to ramp up the PWR voltage to accommodate the higher clock freq
  pwr_set_vos_scale(config->voltage_scale)  ;

  // PLL must be disabled before configuring it
  rcc_osc_off(RCC_PLL);
  // rcc_wait_osc_ready(RCC_PLL);
  // configure pll 
  rcc_configure_pll(config->pllm, config->plln, 
                    config->pllp, config->pllq, 
                    config->pll_source);

  // configure clock peripheral clock prescalers
  // TODO: Figure out R
  rcc_set_periph_prescalers(config->hpre, config->ppre1, config->ppre2);
  
  rcc_osc_on(RCC_PLL);
  rcc_wait_osc_ready(RCC_PLL);

  // Adaptive real-time memory accelerator (ART Accelerator from STMicroelectronics)
  // Each read memory operation provides 128 bits from either four 32 bits or eight 
  // 16-bits instructions. 
  // Prefetch is enabled by setting PRFTEN bit in FLASH_ACR
  // This is also enabled through flash_configure_opt

  // Instructions for increasing CPU frequency (from the reference manual).
  // 1. Program the new number of wait states to LATENCY bits in FLASH_ACR
  // 2. Check that new wait states is taken into account to access the flash memory
  //    by reading FLASH_ACR register
  // flash_set_wait_states(config->flash_config);  // removes configs for caches
  flash_configure_opt(config->flash_config);    // includes configs for caches
  // 3. Modify CPU clock source by writing SW bits in RCC_CFGR
  // 4. If needed, modify CPU clock prescaler HPRE bits in RCC_CFGR

  // NEED TO CONFIGURE PLL and PRESCALERS FIRST
  
  rcc_set_sysclk_src(RCC_CFGR_SW_PLL);
  rcc_wait_for_sysclk_status(RCC_PLL);

  // 5. Check that new CPU clock source and/or the new CPU clock prescaler value is/are 
  //    taken into account by reading SWS bits and HPRE bits in RCC_CFGR
  
	rcc_ahb_frequency  = config->ahb_frequency;
	rcc_apb1_frequency = config->apb1_frequency;
	rcc_apb2_frequency = config->apb2_frequency;
  
  // Disable unused HSI clock
	if (config->pll_source == RCC_CFGR_PLLSRC_HSE_CLK) {
		rcc_osc_off(RCC_HSI);
	}
}

// void rcc_configure_pll(const uint32_t m_div, const uint32_t n_mul, 
//                        const uint32_t p_div, const uint32_t q_div,
//                        const uint32_t pll_src) {
//   uint32_t reg32 = (RCC->PLLCFGR & ~(RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN | 
//                                      RCC_PLLCFGR_PLLP | RCC_PLLCFGR_PLLQ |
//                                      RCC_PLLCFGR_PLLSRC));
//   reg32 |= ((m_div << RCC_PLLCFGR_PLLM_Pos) | (n_mul << RCC_PLLCFGR_PLLN_Pos) | 
//             (p_div << RCC_PLLCFGR_PLLP_Pos) | (q_div << RCC_PLLCFGR_PLLQ_Pos) |
//             (pll_src << RCC_PLLCFGR_PLLSRC_Pos));
//   RCC->PLLCFGR  = reg32;
// }
void rcc_configure_pll(const uint32_t m, const uint32_t n, 
                       const uint32_t p, const uint32_t q,
                       const uint32_t pll_src) {
    
    // 1. Clear the register
    uint32_t reg32 = RCC->PLLCFGR & ~(RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN | 
                                      RCC_PLLCFGR_PLLP | RCC_PLLCFGR_PLLQ |
                                      RCC_PLLCFGR_PLLSRC);

    // 2. Convert raw 'P' (2, 4, 6, 8) to the 2-bit code (0, 1, 2, 3)
    // Formula: (P / 2) - 1. So 4 becomes (4/2)-1 = 1.
    uint32_t p_code = (p / 2) - 1;

    // 3. Apply shifts. 
    // NOTE: Check if pll_src is already shifted. If it is, don't shift it again.
    uint32_t src_val = pll_src;
    if (src_val > 1) { 
        // If src_val is something like 0x400000, it's already shifted.
        // We don't need to shift it again.
    } else {
        src_val = (src_val << RCC_PLLCFGR_PLLSRC_Pos);
    }

    reg32 |= (m << RCC_PLLCFGR_PLLM_Pos);
    reg32 |= (n << RCC_PLLCFGR_PLLN_Pos);
    reg32 |= (p_code << RCC_PLLCFGR_PLLP_Pos);
    reg32 |= (q << RCC_PLLCFGR_PLLQ_Pos);
    reg32 |= src_val;

    RCC->PLLCFGR = reg32;
}

void rcc_set_periph_prescalers(const uint32_t hpre, 
                               const uint32_t ppre1, const uint32_t ppre2) {
  uint32_t reg32 = (RCC->CFGR & ~(RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2));
  reg32 |= ((hpre << RCC_CFGR_HPRE_Pos) | 
            (ppre1 << RCC_CFGR_PPRE1_Pos) | (ppre2 << RCC_CFGR_PPRE2_Pos));
  RCC->CFGR = reg32;
}

void rcc_set_sysclk_source(uint32_t clk)
{
	uint32_t reg32 = RCC->CFGR & ~(RCC_CFGR_SW);
	RCC->CFGR = (reg32 | clk);
}

void rcc_wait_for_sysclk_status(const rcc_clock_src_e osc)
{
	switch (osc) {
	case RCC_PLL:
		while ((RCC->CFGR & RCC_CFGR_SW_Msk) != RCC_CFGR_SW_PLL);
		break;
	case RCC_HSE:
		while ((RCC->CFGR & RCC_CFGR_SWS_Msk) != RCC_CFGR_SWS_HSE);
		break;
	case RCC_HSI:
		while ((RCC->CFGR & RCC_CFGR_SWS_Msk) != RCC_CFGR_SWS_HSI);
		break;
	default:
		/* Shouldn't be reached. */
		break;
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
