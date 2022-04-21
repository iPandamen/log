
#ifndef __LOG_H__
#define __LOG_H__

#define _GNU_SOURCE

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "log_types.h"

extern int log_obj_init(struct log_obj *_obj);
extern int log_obj_exit(struct log_obj *_obj);
extern int log_obj_mutex_lock(struct log_obj *_obj);
extern int log_obj_mutex_unlock(struct log_obj *_obj);
extern int log_obj_printf(struct log_obj *_obj, char *_str);


extern void log_obj_register(struct log_obj* _obj);
extern void log_start(void);
extern void log_end(void);

extern int log_add(struct log_obj* _log, int _level, const char* const _tag,
                     const char* _file, const char* _func, int _line,
                     const char* const format, ...) __attribute__((format(printf, 7, 8)));

#define THIS_FILE (strrchr(__FILE__, '/') + 1)

#if LOG_ENABLE

#define LOG_OBJ_REGISTER(_obj) \
  do {                 \
    log_obj_register(_obj);   \
  } while (0)

#define LOG_START() \
  do {              \
    log_start();   \
  } while (0)

#define LOG_END() \
  do {              \
    log_end();     \
  } while (0)

#define LOG(log, level, tag, format, ...)                                 \
  do {                                                                    \
    if (level <= LOG_LEVEL) {                                             \
      log_add(log, level, tag, __FILE__, __FUNCTION__, __LINE__, format, \
               ##__VA_ARGS__);                                            \
    }                                                                     \
  } while (0)

#else

#define LOG_OBJ_REGISTER(_obj)
#define LOG_START()
#define LOG_END()
#define LOG(log, level, tag, format, ...)

#endif

#endif /* __LOG_H__ */
