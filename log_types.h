#ifndef __LOG_TYPE_H__
#define __LOG_TYPE_H__

#include "log_config.h"

struct __log_obj_operations;
struct __log_obj;

typedef struct __log_obj_operations {
  int (*_init)(struct __log_obj *_obj);
  int (*_exit)(struct __log_obj *_obj);

  int (*_mutex_lock)(struct __log_obj* _obj);
  int (*_mutex_unlock)(struct __log_obj *_obj);
  int (*_printf)(struct __log_obj* _obj, char *str);
}log_obj_operations_t;

typedef struct __log_obj {
  const char *_name;
  void *_property;

#if LOG_MUTEX_ENABLE
  LOG_MUTEX_TYPE _mutex;
#endif /* LOG_MUTEX_ENABLE */

  struct __log_obj_operations *_op;
  struct __log_obj *_next;
}log_obj_t;


typedef struct __log_obj_list{
  int _num;
  log_obj_t *_head;
}log_obj_list_t;

typedef enum {
 LOG_LEVEL_NONE = 0,
 LOG_LEVEL_ERROR = 1,
 LOG_LEVEL_WARNING = 2,
 LOG_LEVEL_INFO = 3,
 LOG_LEVEL_DEBUG = 4,
 LOG_LEVEL_VERBOSE = 5,
 LOG_LEVEL_NUM
}log_level_t;


#endif /* __LOG_TYPE_H__ */

