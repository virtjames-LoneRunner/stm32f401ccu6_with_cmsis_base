#ifndef RCC_H
#define RCC_H

#include <stdint.h>
#include <stdbool.h>

#include "defines.h"
#include "stm32f401xc.h"

#define RCC_CFGR_PLLSRC_HSI_CLK 0x0
#define RCC_CFGR_PLLSRC_HSE_CLK 0x1

typedef enum {
  PWR_SCALE3_RES,
  PWR_SCALE3,
  PWR_SCALE2,
  PWR_SCALE1,
} voltage_scale_e;

typedef enum {
  RCC_HSE_CONFIG_3V3_84MHZ,
} pll_config_e;

typedef enum {
  RCC_HSI,
  RCC_HSE,
  RCC_PLL,
  // TODO: Add more sources as needed rcc_osc_on
  // especially if sound (I2S) processing is needed
} rcc_clock_src_e;

typedef struct
{	
  uint32_t pllm;
  uint32_t plln;
  uint32_t pllp;
  uint32_t pllq;
  uint32_t pllr;
  uint32_t pll_source;
  uint32_t hpre;  // HIGH SPEED AHB 84MHZ MAX
  uint32_t ppre1; // LOW SPEED 42MHZ MAX
  uint32_t ppre2; // HIGH SPEED 84MHZ MAX
  uint32_t voltage_scale;
  uint32_t flash_config;
  uint32_t ahb_frequency;
  uint32_t apb1_frequency;
  uint32_t apb2_frequency;
} rcc_clock_conf;

// Mask
typedef struct {
    uint32_t ahb1;
    uint32_t ahb2;
    uint32_t apb1;
    uint32_t apb2;
} periph_clk_config_t;

enum rcc_periph_clken {
	/* AHB1 peripherals*/
	RCC_GPIOA	= _REG_BIT(0x30, 0),
	RCC_GPIOB	= _REG_BIT(0x30, 1),
	RCC_GPIOC	= _REG_BIT(0x30, 2),
	RCC_GPIOD	= _REG_BIT(0x30, 3),
	RCC_GPIOE	= _REG_BIT(0x30, 4),
	RCC_GPIOF	= _REG_BIT(0x30, 5),
	RCC_GPIOG	= _REG_BIT(0x30, 6),
	RCC_GPIOH	= _REG_BIT(0x30, 7),
	RCC_GPIOI	= _REG_BIT(0x30, 8),
	RCC_GPIOJ	= _REG_BIT(0x30, 9),
	RCC_GPIOK	= _REG_BIT(0x30, 10),
	RCC_CRC		= _REG_BIT(0x30, 12),
	RCC_BKPSRAM	= _REG_BIT(0x30, 18),
	RCC_CCMDATARAM	= _REG_BIT(0x30, 20),
	RCC_DMA1	= _REG_BIT(0x30, 21),
	RCC_DMA2	= _REG_BIT(0x30, 22),
	RCC_DMA2D	= _REG_BIT(0x30, 23),
	RCC_ETHMAC	= _REG_BIT(0x30, 25),
	RCC_ETHMACTX	= _REG_BIT(0x30, 26),
	RCC_ETHMACRX	= _REG_BIT(0x30, 27),
	RCC_ETHMACPTP	= _REG_BIT(0x30, 28),
	RCC_OTGHS	= _REG_BIT(0x30, 29),
	RCC_OTGHSULPI	= _REG_BIT(0x30, 30),

	/* AHB2 peripherals */
	RCC_DCMI	= _REG_BIT(0x34, 0),
	RCC_CRYP	= _REG_BIT(0x34, 4),
	RCC_HASH	= _REG_BIT(0x34, 5),
	RCC_RNG		= _REG_BIT(0x34, 6),
	RCC_OTGFS	= _REG_BIT(0x34, 7),

	/* AHB3 peripherals */
	RCC_FSMC	= _REG_BIT(0x38, 0),
	RCC_FMC		= _REG_BIT(0x38, 0),
	RCC_QUADSPI	= _REG_BIT(0x38, 1),

	/* APB1 peripherals*/
	RCC_TIM2	= _REG_BIT(0x40, 0),
	RCC_TIM3	= _REG_BIT(0x40, 1),
	RCC_TIM4	= _REG_BIT(0x40, 2),
	RCC_TIM5	= _REG_BIT(0x40, 3),
	RCC_TIM6	= _REG_BIT(0x40, 4),
	RCC_TIM7	= _REG_BIT(0x40, 5),
	RCC_TIM12	= _REG_BIT(0x40, 6),
	RCC_TIM13	= _REG_BIT(0x40, 7),
	RCC_TIM14	= _REG_BIT(0x40, 8),
	RCC_WWDG	= _REG_BIT(0x40, 11),
	RCC_SPI2	= _REG_BIT(0x40, 14),
	RCC_SPI3	= _REG_BIT(0x40, 15),
	RCC_USART2	= _REG_BIT(0x40, 17),
	RCC_USART3	= _REG_BIT(0x40, 18),
	RCC_UART4	= _REG_BIT(0x40, 19),
	RCC_UART5	= _REG_BIT(0x40, 20),
	RCC_I2C1	= _REG_BIT(0x40, 21),
	RCC_I2C2	= _REG_BIT(0x40, 22),
	RCC_I2C3	= _REG_BIT(0x40, 23),
	RCC_CAN1	= _REG_BIT(0x40, 25),
	RCC_CAN2	= _REG_BIT(0x40, 26),
	RCC_PWR		= _REG_BIT(0x40, 28),
	RCC_DAC		= _REG_BIT(0x40, 29),
	RCC_UART7	= _REG_BIT(0x40, 30),/* F2xx, F3xx */
	RCC_UART8	= _REG_BIT(0x40, 31),/* F2xx, F3xx */

	/* APB2 peripherals */
	RCC_TIM1	= _REG_BIT(0x44, 0),
	RCC_TIM8	= _REG_BIT(0x44, 1),
	RCC_USART1	= _REG_BIT(0x44, 4),
	RCC_USART6	= _REG_BIT(0x44, 5),
	RCC_ADC1	= _REG_BIT(0x44, 8),
	RCC_ADC2	= _REG_BIT(0x44, 9),
	RCC_ADC3	= _REG_BIT(0x44, 10),
	RCC_SDIO	= _REG_BIT(0x44, 11),
	RCC_SPI1	= _REG_BIT(0x44, 12),
	RCC_SPI4	= _REG_BIT(0x44, 13),/* F2xx, F3xx */
	RCC_SYSCFG	= _REG_BIT(0x44, 14),
	RCC_TIM9	= _REG_BIT(0x44, 16),
	RCC_TIM10	= _REG_BIT(0x44, 17),
	RCC_TIM11	= _REG_BIT(0x44, 18),
	RCC_SPI5	= _REG_BIT(0x44, 20),/* F2xx, F3xx */
	RCC_SPI6	= _REG_BIT(0x44, 21),/* F2xx, F3xx */
	RCC_SAI1EN	= _REG_BIT(0x44, 22),/* F42x, F43x */
	RCC_LTDC	= _REG_BIT(0x44, 26),/* F42x, F43x */
	RCC_DSI		= _REG_BIT(0x44, 27),/* F4x9, F4x9 */


	/* BDCR */
	RCC_RTC		= _REG_BIT(0x70, 15),

	/* AHB1 peripherals*/
	SCC_GPIOA	= _REG_BIT(0x50, 0),
	SCC_GPIOB	= _REG_BIT(0x50, 1),
	SCC_GPIOC	= _REG_BIT(0x50, 2),
	SCC_GPIOD	= _REG_BIT(0x50, 3),
	SCC_GPIOE	= _REG_BIT(0x50, 4),
	SCC_GPIOF	= _REG_BIT(0x50, 5),
	SCC_GPIOG	= _REG_BIT(0x50, 6),
	SCC_GPIOH	= _REG_BIT(0x50, 7),
	SCC_GPIOI	= _REG_BIT(0x50, 8),
	SCC_GPIOJ	= _REG_BIT(0x50, 9),
	SCC_GPIOK	= _REG_BIT(0x50, 10),
	SCC_CRC		= _REG_BIT(0x50, 12),
	SCC_FLTIF	= _REG_BIT(0x50, 15),
	SCC_SRAM1	= _REG_BIT(0x50, 16),
	SCC_SRAM2	= _REG_BIT(0x50, 17),
	SCC_BKPSRAM	= _REG_BIT(0x50, 18),
	SCC_SRAM3	= _REG_BIT(0x50, 19),/* F2xx, F3xx */
	SCC_DMA1	= _REG_BIT(0x50, 21),
	SCC_DMA2	= _REG_BIT(0x50, 22),
	SCC_DMA2D	= _REG_BIT(0x50, 23), /* F4x9 */
	SCC_ETHMAC	= _REG_BIT(0x50, 25),
	SCC_ETHMACTX	= _REG_BIT(0x50, 26),
	SCC_ETHMACRX	= _REG_BIT(0x50, 27),
	SCC_ETHMACPTP	= _REG_BIT(0x50, 28),
	SCC_OTGHS	= _REG_BIT(0x50, 29),
	SCC_OTGHSULPI	= _REG_BIT(0x50, 30),

	/* AHB2 peripherals */
	SCC_DCMI	= _REG_BIT(0x54, 0),
	SCC_CRYP	= _REG_BIT(0x54, 4),
	SCC_HASH	= _REG_BIT(0x54, 5),
	SCC_RNG		= _REG_BIT(0x54, 6),
	SCC_OTGFS	= _REG_BIT(0x54, 7),

	/* AHB3 peripherals */
	SCC_QSPIC	= _REG_BIT(0x58, 1),
	SCC_FMC		= _REG_BIT(0x58, 0),
	SCC_FSMC	= _REG_BIT(0x58, 0),

	/* APB1 peripherals*/
	SCC_TIM2	= _REG_BIT(0x60, 0),
	SCC_TIM3	= _REG_BIT(0x60, 1),
	SCC_TIM4	= _REG_BIT(0x60, 2),
	SCC_TIM5	= _REG_BIT(0x60, 3),
	SCC_TIM6	= _REG_BIT(0x60, 4),
	SCC_TIM7	= _REG_BIT(0x60, 5),
	SCC_TIM12	= _REG_BIT(0x60, 6),
	SCC_TIM13	= _REG_BIT(0x60, 7),
	SCC_TIM14	= _REG_BIT(0x60, 8),
	SCC_WWDG	= _REG_BIT(0x60, 11),
	SCC_SPI2	= _REG_BIT(0x60, 14),
	SCC_SPI3	= _REG_BIT(0x60, 15),
	SCC_USART2	= _REG_BIT(0x60, 17),
	SCC_USART3	= _REG_BIT(0x60, 18),
	SCC_UART4	= _REG_BIT(0x60, 19),
	SCC_UART5	= _REG_BIT(0x60, 20),
	SCC_I2C1	= _REG_BIT(0x60, 21),
	SCC_I2C2	= _REG_BIT(0x60, 22),
	SCC_I2C3	= _REG_BIT(0x60, 23),
	SCC_CAN1	= _REG_BIT(0x60, 25),
	SCC_CAN2	= _REG_BIT(0x60, 26),
	SCC_PWR		= _REG_BIT(0x60, 28),
	SCC_DAC		= _REG_BIT(0x60, 29),
	SCC_UART7	= _REG_BIT(0x60, 30),/* F2xx, F3xx */
	SCC_UART8	= _REG_BIT(0x60, 31),/* F2xx, F3xx */

	/* APB2 peripherals */
	SCC_TIM1	= _REG_BIT(0x64, 0),
	SCC_TIM8	= _REG_BIT(0x64, 1),
	SCC_USART1	= _REG_BIT(0x64, 4),
	SCC_USART6	= _REG_BIT(0x64, 5),
	SCC_ADC1	= _REG_BIT(0x64, 8),
	SCC_ADC2	= _REG_BIT(0x64, 9),
	SCC_ADC3	= _REG_BIT(0x64, 10),
	SCC_SDIO	= _REG_BIT(0x64, 11),
	SCC_SPI1	= _REG_BIT(0x64, 12),
	SCC_SPI4	= _REG_BIT(0x64, 13),/* F2xx, F3xx */
	SCC_SYSCFG	= _REG_BIT(0x64, 14),
	SCC_TIM9	= _REG_BIT(0x64, 16),
	SCC_TIM10	= _REG_BIT(0x64, 17),
	SCC_TIM11	= _REG_BIT(0x64, 18),
	SCC_SPI5	= _REG_BIT(0x64, 20),/* F2xx, F3xx */
	SCC_SPI6	= _REG_BIT(0x64, 21),/* F2xx, F3xx */
	SCC_SAI1	= _REG_BIT(0x64, 22),/* F4x9 */
	SCC_LTDC	= _REG_BIT(0x64, 26),/* F4x9 */
	SCC_DSI		= _REG_BIT(0x64, 27),/* F4x9 */
};

extern const rcc_clock_conf rcc_hse_25mhz_3v3[1];

void rcc_hsi_clock_setup();
void rcc_clock_pll_setup(const pll_config_e config_select);
void rcc_enable_peripherals(const periph_clk_config_t *config);
void rcc_set_sysclk_src(const uint32_t clk);
void rcc_periph_clock_enable(enum rcc_periph_clken clken);
void rcc_periph_clock_disable(enum rcc_periph_clken clken);

static void rcc_osc_on(const rcc_clock_src_e osc_src);
static void rcc_osc_off(const rcc_clock_src_e osc_src);
static void rcc_wait_osc_ready(const rcc_clock_src_e osc_src);
static bool rcc_is_osc_ready(const rcc_clock_src_e osc_src);

#endif
