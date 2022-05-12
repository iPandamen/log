#ifndef __X_LOG_TYPE_H__
#define __X_LOG_TYPE_H__

#include "x_log_config.h"

struct __x_log_obj_operations;
struct __x_log_obj;

typedef enum {
 X_LOG_LEVEL_NONE = 0,
 X_LOG_LEVEL_USER,
 X_LOG_LEVEL_ERROR,
 X_LOG_LEVEL_WARNING,
 X_LOG_LEVEL_INFO,
 X_LOG_LEVEL_TRACE,
 X_LOG_LEVEL_VERBOSE,
 X_LOG_LEVEL_NUM
}x_log_level_t;

typedef struct __x_log_obj_operations {
  int (*_init)(struct __x_log_obj *_obj);
  int (*_exit)(struct __x_log_obj *_obj);

  int (*_mutex_lock)(struct __x_log_obj* _obj);
  int (*_mutex_unlock)(struct __x_log_obj *_obj);
  int (*_printf)(struct __x_log_obj* _obj, char *str);
}x_log_obj_operations_t;

typedef struct __x_log_obj {
  const char *_name;
  x_log_level_t _level;

  void *_property;

#if X_LOG_MUTEX_ENABLE
  X_LOG_MUTEX_TYPE _mutex;
#endif /* X_LOG_MUTEX_ENABLE */

  struct __x_log_obj_operations *_op;
  struct __x_log_obj *_next;
}x_log_obj_t;


typedef struct __x_log{
  int _num;
  x_log_obj_t *_head;
}x_log_t;


#endif /* __X_LOG_TYPE_H__ */

