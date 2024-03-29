#ifndef __LOG_TYPES_H__
#define __LOG_TYPES_H__

#include "log_config.h"

struct __log_obj_operations;
struct __log_obj;

typedef enum {
  LOG_LEVEL_NONE = 0,
  LOG_LEVEL_USER,
  LOG_LEVEL_ERROR,
  LOG_LEVEL_WARNING,
  LOG_LEVEL_INFO,
  LOG_LEVEL_TRACE,
  LOG_LEVEL_VERBOSE,
  LOG_LEVEL_NUM
} log_level_t;

typedef struct __log_obj_operations {
  int (*_init)(struct __log_obj *_obj);
  int (*_exit)(struct __log_obj *_obj);

  int (*_reset)(struct __log_obj *_obj);

  int (*_printf)(struct __log_obj *_obj, const char *_str);
} log_obj_operations_t;

typedef struct __log_obj {
  const char *_name;
  log_level_t _level;
  log_obj_mutex_t _mutex;

  struct __log_obj_operations *_op;
  struct __log_obj *_next;
} log_obj_t;

typedef struct __log {
  int _num;
  log_obj_t *_head;
} log_t;

#endif /* __LOG_TYPES_H__ */
