#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define LOG_ENABLE 1

#include "../log.h"

int main(int argc, char* argv[])
{

  LOG_REGISTER(&x_log_obj, LOG_LEVEL_VERBOSE);
  LOG_START();

  printf("X_LOG_LEVEL: %d\n",log_get_level(&x_log_obj));
  X_LOG_INFO("Version", "V%d.%d.%d", log_version_major(), log_version_minor(), log_version_patch());


  X_LOG_USER("EXAMPLE", "Hello world!");
  X_LOG_ERROR("EXAMPLE", "Hello world!");
  X_LOG_WARNING("EXAMPLE", "Hello world!");
  X_LOG_INFO("EXAMPLE", "Hello world!");
  X_LOG_TRACE("EXAMPLE", "Hello world!");
  X_LOG_VERBOSE("EXAMPLE", "Hello world!");
  X_LOG_VERBOSE(NULL, "Hello world!");

  LOG_END();
  return 0;
}
