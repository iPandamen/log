
#include "x_log.h"

static int x_log_obj_op_init(x_log_obj_t *_log_obj) {
  if(_log_obj) {
#if LOG_MUTEX_ENABLE
    LOG_MUTEX_INIT(&_obj->_mutex);
#endif /* LOG_MUTEX_ENABLE */

    x_log_set_level(_log_obj, X_LOG_LEVEL);

    x_log_obj_property_t* _property = _log_obj->_property;
    if(_property) {
      if(_property->_file_name) {
        _property->_fp = fopen(_property->_file_name, "a+");
      }
      if(!_property->_fp) {
        _property->_fp = stdout;
      }
    }
  }
  return 0;
}

static int x_log_obj_op_exit(x_log_obj_t* _log_obj) {

  if(_log_obj) {

#if LOG_MUTEX_ENABLE
  LOG_MUTEX_DESTROY(&_obj->_mutex);
#endif /* LOG_MUTEX_ENABLE */

    x_log_obj_property_t* _property = _log_obj->_property;
    if(_property) {
      if(_property->_file_name) {
        if(_property->_fp) {
          if(_property->_fp != stdout) {
            fclose(_property->_fp);
          }
        }
      }
    }
  }
  return 0;
}

static int x_log_obj_op_mutex_lock(x_log_obj_t* _log_obj) {
  if(_log_obj) {
#if LOG_MUTEX_ENABLE
    LOG_MUTEX_LOCK(&_obj->_mutex);
#endif /* LOG_MUTEX_ENABLE */
  }
  return 0;
}

static int x_log_obj_op_mutex_unlock(x_log_obj_t* _log_obj) { 
  if(_log_obj) {
#if LOG_MUTEX_ENABLE
    LOG_MUTEX_UNLOCK(&_obj->_mutex);
#endif /* LOG_MUTEX_ENABLE */
  }
  return 0; 
}


static int x_log_obj_op_printf(x_log_obj_t* _log_obj, char* _buf) {

  int ret = 0;
  if(_log_obj) {
    x_log_obj_property_t* _property = _log_obj->_property;
    if(_property) {
      if(_property->_fp) {
        ret = fprintf(_property->_fp, "%s", _buf);
      }
    }
  }
  return ret;
};


static x_log_obj_property_t x_log_obj_default_property = {
  ._fp = NULL,
  ._file_name = X_LOG_DEFAULT_FILE_NAME,
};

x_log_obj_operations_t x_log_obj_default_operations ={
  ._init = x_log_obj_op_init,
  ._exit = x_log_obj_op_exit,
  ._mutex_lock = x_log_obj_op_mutex_lock,
  ._mutex_unlock = x_log_obj_op_mutex_unlock,
  ._printf = x_log_obj_op_printf,

};

x_log_obj_t x_log_obj = {
  ._name = "x_log_obj",
  ._property = &x_log_obj_default_property,
  ._op = &x_log_obj_default_operations,
  ._next = NULL,
};

