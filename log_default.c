
#include "log_default.h"

static int default_log_obj_op_init(struct log_obj *_obj) {
  if(_obj) {
#if LOG_MUTEX_ENABLE
    LOG_MUTEX_INIT(&_obj->_mutex);
#endif /* LOG_MUTEX_ENABLE */

    struct default_log_obj_property* _property = _obj->_property;
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

static int default_log_obj_op_exit(struct log_obj* _obj) {

  if(_obj) {

#if LOG_MUTEX_ENABLE
  LOG_MUTEX_DESTROY(&_obj->_mutex);
#endif /* LOG_MUTEX_ENABLE */

    struct default_log_obj_property* _property = _obj->_property;
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

static int default_log_obj_op_mutex_lock(struct log_obj* _obj) {
  if(_obj) {
#if LOG_MUTEX_ENABLE
    LOG_MUTEX_LOCK(&_obj->_mutex);
#endif /* LOG_MUTEX_ENABLE */
  }
  return 0;
}

static int default_log_obj_op_mutex_unlock(struct log_obj* _obj) { 
  if(_obj) {
#if LOG_MUTEX_ENABLE
    LOG_MUTEX_UNLOCK(&_obj->_mutex);
#endif /* LOG_MUTEX_ENABLE */
  }
  return 0; 
}


static int default_log_obj_op_printf(struct log_obj* _obj, char* _buf) {

  int ret = 0;
  if(_obj) {
    struct default_log_obj_property* _property = _obj->_property;
    if(_property) {
      if(_property->_fp) {
        ret = fprintf(_property->_fp, "%s", _buf);
      }
    }
  }
  return ret;
};


static struct default_log_obj_property default_log_obj_default_property = {
  ._fp = NULL,
  ._file_name = DEFAULT_LOG_FILE_NAME,
};

struct log_obj_operations default_log_obj_default_operations ={
  ._init = default_log_obj_op_init,
  ._exit = default_log_obj_op_exit,
  ._mutex_lock = default_log_obj_op_mutex_lock,
  ._mutex_unlock = default_log_obj_op_mutex_unlock,
  ._printf = default_log_obj_op_printf,

};

struct log_obj default_log_obj = {
  ._name = "defaultandard log obj",
  ._property = &default_log_obj_default_property,
  ._op = &default_log_obj_default_operations,
  ._next = NULL,
};

