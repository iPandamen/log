
#include "log_core.h"

static log_obj_list_t _log; 

int log_obj_init(log_obj_t *_obj) {
  int ret = -1;
  if(_obj) {
    if(_obj->_op) {
      if(_obj->_op->_init) {
        ret = _obj->_op->_init(_obj);
      }
    }
  }
  return ret;
}

int log_obj_exit(log_obj_t *_obj) {
  int ret = -1;
  if(_obj) {
    if(_obj->_op) {
      if(_obj->_op->_exit) {
        ret = _obj->_op->_exit(_obj);
      }
    }
  }
  return ret;
}

int log_obj_mutex_lock(log_obj_t *_obj) {
  int ret = -1;
  if(_obj) {
    if(_obj->_op) {
      if(_obj->_op->_mutex_lock) {
        ret = _obj->_op->_mutex_lock(_obj);
      }
    }
  }
  return ret;
}

int log_obj_mutex_unlock(log_obj_t *_obj) {
  int ret = -1;
  if(_obj) {
    if(_obj->_op) {
      if(_obj->_op->_mutex_unlock) {
        ret = _obj->_op->_mutex_unlock(_obj);
      }
    }
  }
  return ret;
}

int log_obj_printf(log_obj_t *_obj, char *_str) {
  int ret = -1;
  if(_obj) {
    if(_obj->_op) {
      if(_obj->_op->_printf) {
        ret = _obj->_op->_printf(_obj, _str);
      }
    }
  }
  return ret;
}

void log_obj_register(log_obj_t* _obj) {
  log_obj_t *_temp_obj = _log._head;
  if(_temp_obj) {
    while(_temp_obj->_next) {
      _temp_obj = _temp_obj->_next;
    }
    _temp_obj->_next = _obj;
  } else {
    _log._head = _obj;
  }
}

void log_start(void) {
  log_obj_t *_temp_obj = _log._head;
  while(_temp_obj) {
    log_obj_init(_temp_obj);
    _temp_obj = _temp_obj->_next;
  }
}

void log_end(void) {
  log_obj_t *_temp_obj = _log._head;
  while(_temp_obj) {
    log_obj_exit(_temp_obj);
    _temp_obj = _temp_obj->_next;
  }
}

static int log_timestamp(char* _buf, int _b_len) {
  struct tm* _tm = NULL;
  time_t _t = 0;
  time(&_t);
  _tm = localtime(&_t);
  return strftime(_buf, _b_len, "%Y-%m-%d %H:%M:%S", _tm);
}

static int log_string(char** buf, int _level, const char* const _tag,
                      const char* _file, const char* _func, int _line,
                      const char* const _format, va_list va_l) {
  /*
   * @brief the prompt string of corresponding log level
   *
   */
  int ret = 0;
  static const char* const _log_level_str[] = {
    "NONE", "ERROR", "WARNING", "INFO", "DEBUG", "VERBOSE", NULL};
  
  if(_level < LOG_LEVEL_NUM) {
    char _timestamp[32] = {0};
    log_timestamp(_timestamp, sizeof(_timestamp));

    char* _t_buf = NULL;
    if(asprintf(&_t_buf, "[ %s ][ %s ][ %s ] (%s, in %s line #%d):\r\n%s\r\n",
                _timestamp, _log_level_str[_level], _tag, _func, _file, _line,
                _format) < 0) {
      ret = -1;
    } else {
      if (_t_buf) {
        ret = vasprintf(buf, _t_buf, va_l);
        free(_t_buf);
      }
    }
  }
  return ret;
}

int log_add(log_obj_t* _obj, int _level, const char* const _tag,
              const char* _file, const char* _func, int _line,
              const char* const _format, ...) {
  int ret = -1;
  if (_obj) {
    char* _buf = NULL;
    va_list va_l;
    va_start(va_l, _format);
    log_string(&_buf, _level, _tag, _file, _func, _line, _format, va_l);

    if (_buf) {

#if LOG_MUTEX_ENABLE
      log_obj_mutex_lock(_obj);
#endif /* LOG_MUTEX_ENABLE */

      ret = log_obj_printf(_obj, _buf);

#if LOG_MUTEX_ENABLE
      log_obj_mutex_unlock(_obj);
#endif /* LOG_MUTEX_ENABLE */
      free(_buf);
    }
    va_end(va_l);
  }
  return ret;
}









