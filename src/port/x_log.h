
#ifndef __X_LOG_H__
#define __X_LOG_H__

#include <pthread.h>

#include "../core/log_core.h"

#include "x_log_conf_internal.h"

typedef struct __x_log_obj_property {
  FILE* _fp;
  char* _file_name;
}x_log_obj_property_t;

extern log_obj_operations_t x_log_obj_default_operations;
extern log_obj_t x_log_obj;

#define X_LOG_USER(tag, format, ...) \
  LOG(&x_log_obj, LOG_LEVEL_USER, tag, format, ##__VA_ARGS__)
#define X_LOG_ERROR(tag, format, ...) \
  LOG(&x_log_obj, LOG_LEVEL_ERROR, tag, format, ##__VA_ARGS__)
#define X_LOG_WARNING(tag, format, ...) \
  LOG(&x_log_obj, LOG_LEVEL_WARNING, tag, format, ##__VA_ARGS__)
#define X_LOG_INFO(tag, format, ...) \
  LOG(&x_log_obj, LOG_LEVEL_INFO, tag, format, ##__VA_ARGS__)
#define X_LOG_TRACE(tag, format, ...) \
  LOG(&x_log_obj, LOG_LEVEL_TRACE, tag, format, ##__VA_ARGS__)
#define X_LOG_VERBOSE(tag, format, ...) \
  LOG(&x_log_obj, LOG_LEVEL_VERBOSE, tag, format, ##__VA_ARGS__)

#endif /* __X_LOG_STD_H__ */


