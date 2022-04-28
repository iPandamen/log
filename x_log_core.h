
#ifndef __X_LOG_H__
#define __X_LOG_H__

#define _GNU_SOURCE

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "x_log_types.h"

extern int x_log_obj_init(x_log_obj_t *_log_obj);
extern int x_log_obj_exit(x_log_obj_t *_log_obj);
extern int x_log_obj_mutex_lock(x_log_obj_t *_log_obj);
extern int x_log_obj_mutex_unlock(x_log_obj_t *_log_obj);
extern int x_log_obj_printf(x_log_obj_t *_log_obj, char *_str);


extern void x_log_obj_register(x_log_obj_t*_log_obj);
extern void x_log_start(void);
extern void x_log_end(void);

extern int x_log_add(x_log_obj_t *_log_obj, int _level, const char* const _tag,
                     const char* _file, const char* _func, int _line,
                     const char* const format, ...) __attribute__((format(printf, 7, 8)));

#define THIS_FILE (strrchr(__FILE__, '/') + 1)

#if X_LOG_ENABLE

#define X_LOG_OBJ_REGISTER(log_obj) \
  do {                 \
    x_log_obj_register(log_obj);   \
  } while (0)

#define X_LOG_START() \
  do {              \
    x_log_start();   \
  } while (0)

#define X_LOG_END() \
  do {              \
    x_log_end();     \
  } while (0)

#define X_LOG(log_obj, level, tag, format, ...)                                 \
  do {                                                                    \
    if (level <= X_LOG_LEVEL) {                                             \
      x_log_add(log_obj, level, tag, __FILE__, __FUNCTION__, __LINE__, format, \
               ##__VA_ARGS__);                                            \
    }                                                                     \
  } while (0)

#else

#define X_LOG_OBJ_REGISTER(log_obj)
#define X_LOG_START()
#define X_LOG_END()
#define X_LOG(log_obj, level, tag, format, ...)

#endif

#endif /* __X_LOG_H__ */
