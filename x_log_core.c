
#include "x_log_core.h"

static x_log_t _log; 

int x_log_obj_init(x_log_obj_t *_log_obj) {
  int ret = -1;
  if(_log_obj) {
    if(_log_obj->_op) {
      if(_log_obj->_op->_init) {
        ret =_log_obj->_op->_init(_log_obj);
      }
    }
  }
  return ret;
}

int x_log_obj_exit(x_log_obj_t *_log_obj) {
  int ret = -1;
  if(_log_obj) {
    if(_log_obj->_op) {
      if(_log_obj->_op->_exit) {
        ret =_log_obj->_op->_exit(_log_obj);
      }
    }
  }
  return ret;
}

int x_log_obj_mutex_lock(x_log_obj_t *_log_obj) {
  int ret = -1;
  if(_log_obj) {
    if(_log_obj->_op) {
      if(_log_obj->_op->_mutex_lock) {
        ret =_log_obj->_op->_mutex_lock(_log_obj);
      }
    }
  }
  return ret;
}

int x_log_obj_mutex_unlock(x_log_obj_t *_log_obj) {
  int ret = -1;
  if(_log_obj) {
    if(_log_obj->_op) {
      if(_log_obj->_op->_mutex_unlock) {
        ret =_log_obj->_op->_mutex_unlock(_log_obj);
      }
    }
  }
  return ret;
}

int x_log_obj_printf(x_log_obj_t *_log_obj, char *_str) {
  int ret = -1;
  if(_log_obj) {
    if(_log_obj->_op) {
      if(_log_obj->_op->_printf) {
        ret =_log_obj->_op->_printf(_log_obj, _str);
      }
    }
  }
  return ret;
}

void x_log_register(x_log_obj_t*_log_obj) {
  x_log_obj_t *_temp_obj = _log._head;
  if(_temp_obj) {
    while(_temp_obj->_next) {
      _temp_obj = _temp_obj->_next;
    }
    _temp_obj->_next =_log_obj;
  } else {
    _log._head =_log_obj;
  }
}

void x_log_start(void) {
  x_log_obj_t *_temp_obj = _log._head;
  while(_temp_obj) {
    x_log_obj_init(_temp_obj);
    _temp_obj = _temp_obj->_next;
  }
}

void x_log_end(void) {
  x_log_obj_t *_temp_obj = _log._head;
  while(_temp_obj) {
    x_log_obj_exit(_temp_obj);
    _temp_obj = _temp_obj->_next;
  }
}


int x_log_set_level(x_log_obj_t *_log_obj, x_log_level_t _level) {
  int ret = -1;
  if(_log_obj) {
    _log_obj->_level = _level;
    ret = 0;
  }
  return ret;
}

int x_log_get_level(x_log_obj_t *_log_obj) {
  int _level = -1;
  if(_log_obj) {
    _level = _log_obj->_level;
  }
  return _level;
}


static int x_log_timestamp(char* _buf, int _b_len) {
  struct tm* _tm = NULL;
  time_t _t = 0;
  time(&_t);
  _tm = localtime(&_t);
  return strftime(_buf, _b_len, "%Y-%m-%d %H:%M:%S", _tm);
}

static int x_log_string(char** buf, int _level, const char* const _tag,
                      const char* _file, const char* _func, int _line,
                      const char* const _format, va_list va_l) {
  /*
   * @brief the prompt string of corresponding log level
   *
   */
  int ret = 0;
  static const char* const _x_log_level_str[] = {
    "NONE", "USER", "ERROR", "WARNING", "INFO", "TRACE", "VERBOSE", NULL};
  
  if(_level < X_LOG_LEVEL_NUM) {
    char _timestamp[32] = {0};
    x_log_timestamp(_timestamp, sizeof(_timestamp));

    char* _t_buf = NULL;
    if(asprintf(&_t_buf, "[ %s ][ %s ][ %s ] (%s, in %s line #%d):\r\n%s\r\n",
                _timestamp, _x_log_level_str[_level], _tag, _func, _file, _line,
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

int x_log_add(x_log_obj_t*_log_obj, int _level, const char* const _tag,
              const char* _file, const char* _func, int _line,
              const char* const _format, ...) {
  int ret = -1;
  if (_log_obj) {
    if(_level <= _log_obj->_level) {
      char* _buf = NULL;
      va_list va_l;
      va_start(va_l, _format);
      x_log_string(&_buf, _level, _tag, _file, _func, _line, _format, va_l);

      if (_buf) {

#if LOG_MUTEX_ENABLE
        x_log_obj_mutex_lock(_log_obj);
#endif /* LOG_MUTEX_ENABLE */

        ret = x_log_obj_printf(_log_obj, _buf);

#if LOG_MUTEX_ENABLE
        x_log_obj_mutex_unlock(_log_obj);
#endif /* LOG_MUTEX_ENABLE */
        free(_buf);
      }
      va_end(va_l);
    }
  }
  return ret;
}



