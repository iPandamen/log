
#ifndef __LOG_STD_H__
#define __LOG_STD_H__

#include "log_core.h"

struct default_log_obj_property {
  FILE* _fp;
  char* _file_name;
};

extern struct log_obj_operations default_log_obj_default_operations;
extern struct log_obj default_log_obj;

#define LOG_ERROR(tag, format, ...) \
  LOG(&default_log_obj, LOG_LEVEL_ERROR, tag, format, ##__VA_ARGS__)
#define LOG_WARNING(tag, format, ...) \
  LOG(&default_log_obj, LOG_LEVEL_WARNING, tag, format, ##__VA_ARGS__)
#define LOG_INFO(tag, format, ...) \
  LOG(&default_log_obj, LOG_LEVEL_INFO, tag, format, ##__VA_ARGS__)
#define LOG_DEBUG(tag, format, ...) \
  LOG(&default_log_obj, LOG_LEVEL_DEBUG, tag, format, ##__VA_ARGS__)
#define LOG_VERBOSE(tag, format, ...) \
  LOG(&default_log_obj, LOG_LEVEL_VERBOSE, tag, format, ##__VA_ARGS__)

#endif /* __LOG_STD_H__ */


