#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "../x_log.h"

int main(int argc, char* argv[])
{
  printf("LOG_ENABLE: %d\n", X_LOG_ENABLE);
  X_LOG_OBJ_REGISTER(&x_log_obj);
  X_LOG_START();

  X_LOG_ERROR("DEFAULT", "Hello world!");
  X_LOG_WARNING("DEFAULT", "Hello world!");
  X_LOG_INFO("DEFAULT", "Hello world!");
  X_LOG_DEBUG("DEFAULT", "Hello world!");
  X_LOG_VERBOSE("DEFAULT", "Hello world!");

  X_LOG_END();
  return 0;
}
