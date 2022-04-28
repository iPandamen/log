
#include "log_default.h"

static int default_log_obj_op_init(log_obj_t *_obj) {
  if(_obj) {
#if LOG_MUTEX_ENABLE
    LOG_MUTEX_INIT(&_obj->_mutex);
#endif /* LOG_MUTEX_ENABLE */

    default_log_obj_property_t* _property = _obj->_property;
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

static int default_log_obj_op_exit(log_obj_t* _obj) {

  if(_obj) {

#if LOG_MUTEX_ENABLE
  LOG_MUTEX_DESTROY(&_obj->_mutex);
#endif /* LOG_MUTEX_ENABLE */

    default_log_obj_property_t* _property = _obj->_property;
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

static int default_log_obj_op_mutex_lock(log_obj_t* _obj) {
  if(_obj) {
#if LOG_MUTEX_ENABLE
    LOG_MUTEX_LOCK(&_obj->_mutex);
#endif /* LOG_MUTEX_ENABLE */
  }
  return 0;
}

static int default_log_obj_op_mutex_unlock(log_obj_t* _obj) { 
  if(_obj) {
#if LOG_MUTEX_ENABLE
    LOG_MUTEX_UNLOCK(&_obj->_mutex);
#endif /* LOG_MUTEX_ENABLE */
  }
  return 0; 
}


static int default_log_obj_op_printf(log_obj_t* _obj, char* _buf) {

  int ret = 0;
  if(_obj) {
    default_log_obj_property_t* _property = _obj->_property;
    if(_property) {
      if(_property->_fp) {
        ret = fprintf(_property->_fp, "%s", _buf);
      }
    }
  }
  return ret;
};


static default_log_obj_property_t default_log_obj_default_property = {
  ._fp = NULL,
  ._file_name = DEFAULT_LOG_FILE_NAME,
};

log_obj_operations_t default_log_obj_default_operations ={
  ._init = default_log_obj_op_init,
  ._exit = default_log_obj_op_exit,
  ._mutex_lock = default_log_obj_op_mutex_lock,
  ._mutex_unlock = default_log_obj_op_mutex_unlock,
  ._printf = default_log_obj_op_printf,

};

log_obj_t default_log_obj = {
  ._name = "defaultandard log obj",
  ._property = &default_log_obj_default_property,
  ._op = &default_log_obj_default_operations,
  ._next = NULL,
};

