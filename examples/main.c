#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "../x_log.h"

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

  X_LOG_END();
  return 0;
}
