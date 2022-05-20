
#include "log_core.h"

static log_t _log; 

__thread struct timeval last_log_time;

int log_obj_init(log_obj_t *_log_obj) {
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

int log_obj_exit(log_obj_t *_log_obj) {
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

int log_obj_mutex_init(log_obj_t *_log_obj) {
  int rc = -1;
  if(_log_obj && _log_obj->_op && _log_obj->_op->_mutex_init) {
    rc =_log_obj->_op->_mutex_init(_log_obj);
  }
  return rc;
}

int log_obj_mutex_lock(log_obj_t *_log_obj) {
  int  rc = -1;
  if(_log_obj && _log_obj->_op && _log_obj->_op->_mutex_lock) {
    rc =_log_obj->_op->_mutex_lock(_log_obj);
  }
  return rc;
}

int log_obj_mutex_unlock(log_obj_t *_log_obj) {
  int  rc = -1;
  if(_log_obj && _log_obj->_op && _log_obj->_op->_mutex_unlock) {
    rc =_log_obj->_op->_mutex_unlock(_log_obj);
  }
  return rc;
}

int log_obj_mutex_destroy(log_obj_t *_log_obj) {
  int  rc = -1;
  if(_log_obj && _log_obj->_op && _log_obj->_op->_mutex_destroy) {
    rc =_log_obj->_op->_mutex_destroy(_log_obj);
  }
  return rc;
}

int log_obj_printf(log_obj_t *_log_obj, char *_str) {
  int  rc = -1;
  if(_log_obj && _log_obj->_op && _log_obj->_op->_printf) {
    rc = _log_obj->_op->_printf(_log_obj, _str);
  }
  return rc;
}

void log_register(log_obj_t*_log_obj) {
  log_obj_t *_temp_obj = _log._head;
  if(_temp_obj) {
    while(_temp_obj->_next) {
      _temp_obj = _temp_obj->_next;
    }
    _temp_obj->_next =_log_obj;
  } else {
    _log._head =_log_obj;
  }
}

void log_start(void) {
  log_obj_t *_obj = _log._head;
  while(_obj) {
    log_obj_init(_obj);
    log_obj_mutex_init(_obj);
    _obj = _obj->_next;
  }
}

void log_end(void) {
  log_obj_t *_obj = _log._head;
  while(_obj) {
    log_obj_exit(_obj);
    log_obj_mutex_destroy(_obj);
    _obj = _obj->_next;
  }
}

int log_set_level(log_obj_t *_log_obj, log_level_t _level) {
  int ret = -1;
  if(_log_obj) {
    _log_obj->_level = _level;
    ret = 0;
  }
  return ret;
}

int log_get_level(log_obj_t *_log_obj) {
  int _level = -1;
  if(_log_obj) {
    _level = _log_obj->_level;
  }
  return _level;
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
    "NONE", "USER", "ERROR", "WARNING", "INFO", "TRACE", "VERBOSE", NULL};
  
  if(_level < LOG_LEVEL_NUM) {
    char _timestamp[32] = {0};
    log_timestamp(_timestamp, sizeof(_timestamp));

    char* _t_buf = NULL;

    if(_tag) {
      ret = asprintf(&_t_buf, "[ %s ][ %s ][ %s ] (%s, in %s line #%d):\r\n%s\r\n",
                     _timestamp, _log_level_str[_level], _tag, _func, _file, _line,
                     _format);
    } else {
      ret = asprintf(&_t_buf, "[ %s ][ %s ](%s, in %s line #%d):\r\n%s\r\n",
                     _timestamp, _log_level_str[_level], _func, _file, _line,
                     _format);
    }

    if(ret < 0) {
    } else {
      if (_t_buf) {
        ret = vasprintf(buf, _t_buf, va_l);
        free(_t_buf);
      }
    }
  }
  return ret;
}

int log_add(log_obj_t*_log_obj, int _level, const char* const _tag,
              const char* _file, const char* _func, int _line,
              const char* const _format, ...) {
  int ret = -1;
  if (_log_obj) {
    if(_level <= _log_obj->_level) {
      char* _buf = NULL;
      va_list va_l;
      va_start(va_l, _format);
      log_string(&_buf, _level, _tag, _file, _func, _line, _format, va_l);

      if (_buf) {

        log_obj_mutex_lock(_log_obj);
        ret = log_obj_printf(_log_obj, _buf);
        log_obj_mutex_unlock(_log_obj);
        free(_buf);
      }
      va_end(va_l);
    }
  }
  return ret;
}



