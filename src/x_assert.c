#include "x_assert.h"

static x_log_obj_t *x_assert_log_obj = X_ASSERT_DEFAULT_LOG_OBJ;

void x_assert_set_log_obj(x_log_obj_t *_obj) 
{
  x_assert_log_obj = _obj;
}

x_log_obj_t *x_assert_get_log_obj(void) 
{
  return x_assert_log_obj;
}







