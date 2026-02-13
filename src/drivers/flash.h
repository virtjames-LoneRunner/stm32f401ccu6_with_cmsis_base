#ifndef FLASH_H
#define FLASH_H

#include <stdint.h>
#include <stdbool.h>
#include "defines.h"

// Only used for program and erase operations of flash
typedef struct {
  uint32_t key1;
  uint32_t key2;
} flash_unlock_keys_t;

// typedef struct {
//   bool prefetch;
//   bool instructionCache;
//   bool dataCache;
//   uint32_t latency;
// } flash_config_t;

void flash_wait(void);
void flash_configure_opt(const uint32_t config);
void flash_set_wait_states(const uint32_t wait_states);

#endif
