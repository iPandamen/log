#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "../log_default.h"

int main(int argc, char* argv[])
{
  LOG_OBJ_REGISTER(&default_log_obj);
  LOG_START();

  LOG_ERROR("DEFAULT", "Hello worlld");

  LOG_END();
  return 0;
}
