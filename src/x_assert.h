#ifndef __X_ASSERT_H_
#define __X_ASSERT_H_


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdio.h>
#include <stdbool.h>

#include "x_log.h"

extern void x_assert_set_log_obj(x_log_obj_t *_obj);
extern x_log_obj_t *x_assert_get_log_obj(void);

#define X_ASSERT_NULL_ENABLE 1

#define X_ASSERT_DEFAULT_LOG_OBJ &x_log_obj

#define X_ASSERT_HANDLE do {} while(0);

#define X_ASSERT(expression, msg)                                                                              \
  do {                                                                                                               \
    if(!(expression)) {                                                                                              \
      X_LOG(x_assert_get_log_obj(), X_LOG_LEVEL_ERROR, "Assert", "Assert at expression: %s (%s)", #expression, msg);                            \
      X_ASSERT_HANDLE \
    }                                                                                                              \
  } while(0)

#if X_ASSERT_NULL_ENABLE
#define X_ASSERT_NULL(pointer) X_ASSERT(pointer, "pointer is nullptr")
#else
#define X_ASSERT_NULL(pointer)
#endif /* X_ASSERT_ENABLE */

#if X_ASSERT_NULL_ENABLE
#define X_ASSERT_MALLOC(pointer) X_ASSERT(pointer != NULL, "malloc failed");
#else
#define X_ASSERT_MALLOC(pointer)
#endif /* X_ASSERT_ENABLE */

#ifdef __cplusplus
}
#endif /* -__cplusplus */

#endif /* __X_ASSERT_H_ */

