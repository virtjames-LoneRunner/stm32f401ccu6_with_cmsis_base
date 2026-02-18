#include "test/init.test.h"
// #include "test/blink.test.h"

#define TEST_SIZE 4000U
// Use 'uint32_t' to test 32-bit (Word) transfers, which are fastest
volatile uint32_t src_buffer[TEST_SIZE];
volatile uint32_t dst_buffer[TEST_SIZE];

int main(void) {
  for (int i = 0; i < TEST_SIZE; i++) {
      src_buffer[i] = 0xDEAD0000 | i;      // src_buffer will be [0, 1, 2, 3...]
      dst_buffer[i] = 0;      // dst_buffer is wiped clean
  }
  init_test((uint32_t *)&src_buffer, (uint32_t *)&dst_buffer, TEST_SIZE);

  // blink_test();

  while(1) {
    __NOP();
  }
}
