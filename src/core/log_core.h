
#ifndef __LOG_CORE_H__
#define __LOG_CORE_H__

#define _GNU_SOURCE

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "log_types.h"

extern int log_obj_init(log_obj_t *_log_obj);
extern int log_obj_exit(log_obj_t *_log_obj);

extern int log_obj_mutex_init(log_obj_t *_log_obj);
extern int log_obj_mutex_lock(log_obj_t *_log_obj);
extern int log_obj_mutex_unlock(log_obj_t *_log_obj);
extern int log_obj_mutex_destroy(log_obj_t *_log_obj);

extern int log_obj_printf(log_obj_t *_log_obj, char *_str);


extern void log_register(log_obj_t*_log_obj);
extern void log_start(void);
extern void log_end(void);

extern int log_set_level(log_obj_t *_log_obj, log_level_t _level);
extern int log_get_level(log_obj_t *_log_obj);

extern int log_add(log_obj_t *_log_obj, int _level, const char* const _tag,
                     const char* _file, const char* _func, int _line,
                     const char* const format, ...) __attribute__((format(printf, 7, 8)));

#define THIS_FILE (strrchr(__FILE__, '/') + 1)

#if LOG_ENABLE

#define LOG_REGISTER(log_obj) \
  do {                 \
    log_register(log_obj);   \
  } while (0)

#define LOG_START() \
  do {              \
    log_start();   \
  } while (0)

#define LOG_END() \
  do {              \
    log_end();     \
  } while (0)

#define LOG(log_obj, level, tag, format, ...)                                 \
  do {                                                                    \
    log_add(log_obj, level, tag, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);                                            \
  } while (0)

#else

#define LOG_REGISTER(log_obj)
#define LOG_START()
#define LOG_END()
#define LOG(log_obj, level, tag, format, ...)

#endif

#endif /* __LOG_CORE_H__ */
