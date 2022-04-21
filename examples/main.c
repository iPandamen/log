#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "../log_default.h"

int main(int argc, char* argv[])
{
  printf("LOG_ENABLE: %d\n", LOG_ENABLE);
  LOG_OBJ_REGISTER(&default_log_obj);
  LOG_START();

  LOG_ERROR("DEFAULT", "Hello world!");
  LOG_WARNING("DEFAULT", "Hello world!");
  LOG_INFO("DEFAULT", "Hello world!");
  LOG_DEBUG("DEFAULT", "Hello world!");
  LOG_VERBOSE("DEFAULT", "Hello world!");

  LOG_END();
  return 0;
}
