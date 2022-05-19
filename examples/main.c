#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "x_log.h"

#include "x_assert.h"


int main(int argc, char* argv[])
{
  printf("X_LOG_ENABLE: %d\n", X_LOG_ENABLE);
  X_LOG_REGISTER(&x_log_obj);
  X_LOG_START();

  printf("X_LOG_LEVEL: %d\n", X_LOG_LEVEL);
  printf("x_log_obj level: %d\n", x_log_get_level(&x_log_obj));

  // x_log_set_level(&x_log_obj, X_LOG_LEVEL_VERBOSE);
  // printf("x_log_obj level: %d\n", x_log_get_level(&x_log_obj));

  X_LOG_USER("EXAMPLE", "Hello world!");
  X_LOG_ERROR("EXAMPLE", "Hello world!");
  X_LOG_WARNING("EXAMPLE", "Hello world!");
  X_LOG_INFO("EXAMPLE", "Hello world!");
  X_LOG_TRACE("EXAMPLE", "Hello world!");
  X_LOG_VERBOSE("EXAMPLE", "Hello world!");
  X_LOG_VERBOSE(NULL, "Hello world!");

  // X_ASSERT_NULL(0);
  // X_ASSERT_MALLOC(0);
  //
  // uint64_t count = 0xFFFFFFFFFFFFF;
  // uint8_t a = 1, b = 1, c = 1;
  // printf("0, count: %ld s\n", count);
  // printf("0, a: %d, b: %d, c: %d\n", a, b, c);
  //
  // double _start = 0.0, _end = 0.0;
  // for(uint64_t i = 0; i < count; i++){
  //   if(a) {
  //     if(b) {
  //       if(c) {
  //       }
  //     }
  //   }
  // }
  // _end = (double)clock() / CLOCKS_PER_SEC;
  // printf("0, diff: %lf s\n", _end - _start);
  //
  // _start = (double)clock() / CLOCKS_PER_SEC;
  // for(uint64_t i = 0; i < count; i++){
  //   if(a && b && c) {
  //   }
  // }
  // _end = (double)clock() / CLOCKS_PER_SEC;
  // printf("1, diff: %lf s\n", _end - _start);
  //
  X_LOG_END();
  return 0;
}
