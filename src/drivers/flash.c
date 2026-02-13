#include "flash.h"

void flash_configure_opt(const uint32_t config) {
  uint32_t flash_config = (FLASH->ACR & ~(FLASH_ACR_DCEN | 
                                          FLASH_ACR_ICEN | 
                                          FLASH_ACR_PRFTEN |
                                          FLASH_ACR_LATENCY));

  if (config & (FLASH_ACR_ICEN | FLASH_ACR_DCEN)) {
    FLASH->ACR = flash_config | FLASH_ACR_ICRST | FLASH_ACR_DCRST;
    FLASH->ACR = flash_config;
  }

  FLASH->ACR = flash_config | (config & (FLASH_ACR_PRFTEN | 
                                         FLASH_ACR_DCEN | 
                                         FLASH_ACR_ICEN |
                                         FLASH_ACR_LATENCY));

  // Wait
  while((FLASH->ACR & FLASH_ACR_LATENCY) != (config & FLASH_ACR_LATENCY));
};

void flash_set_wait_states(const uint32_t wait_states) {
  uint32_t reg32;
  uint32_t ws = (wait_states & FLASH_ACR_LATENCY);
  reg32 = FLASH->ACR;
  reg32 &= ~(FLASH_ACR_LATENCY);
  reg32 |= (ws << FLASH_ACR_LATENCY_Pos);
  FLASH->ACR = reg32;

  // Wait
  while((FLASH->ACR & FLASH_ACR_LATENCY) != ws);
};

void flash_wait(void) {
  while((FLASH->SR & FLASH_SR_BSY) == FLASH_SR_BSY);
}
