

#include "x_log.h"

static int x_log_obj_op_init(log_obj_t *_log_obj) {
  if(_log_obj) {

    x_log_obj_property_t* _property = _log_obj->_property;
    if(_property) {
      if(_property->_file_name) {
        _property->_fp = fopen(_property->_file_name, "a+");
      }
    }
  }
  return 0;
}

static int x_log_obj_op_exit(log_obj_t* _log_obj) {

  if(_log_obj) {
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

static int x_log_obj_op_mutex_init(log_obj_t* _log_obj) {

  int rc = -1;
  if(_log_obj) {
    _log_obj->_mutex = malloc(sizeof(pthread_mutex_t));
    if(_log_obj->_mutex) {
      rc = pthread_mutex_init(_log_obj->_mutex, NULL);
    }
  }
  return rc;
}

static int x_log_obj_op_mutex_lock(log_obj_t* _log_obj) {
  int rc = -1;
  if(_log_obj) {
    rc = pthread_mutex_lock(_log_obj->_mutex);
  }
  return rc;
}

static int x_log_obj_op_mutex_unlock(log_obj_t* _log_obj) { 
  int rc = -1;
  if(_log_obj) {
    rc = pthread_mutex_unlock(_log_obj->_mutex);
  }
  return rc; 
}

static int x_log_obj_op_mutex_destroy(log_obj_t* _log_obj) {
  int rc = -1;
  if(_log_obj) {
    if(_log_obj->_mutex) {
      rc = pthread_mutex_destroy(_log_obj->_mutex);
      free(_log_obj->_mutex);
    }
  }
  return rc;
}

static int x_log_obj_op_printf(log_obj_t* _log_obj, char* _buf) {

  int ret = 0;
  if(_log_obj) {
    x_log_obj_property_t* _property = _log_obj->_property;
    if(_property) {
      if(_property->_fp) {
        ret = fprintf(_property->_fp, "%s", _buf);
      } else {
        ret = fprintf(stdout, "%s", _buf);
      }
    }
  }
  return ret;
};


static x_log_obj_property_t x_log_obj_default_property = {
  ._fp = NULL,
  ._file_name = NULL,
};

log_obj_operations_t x_log_obj_default_operations ={
  ._init = x_log_obj_op_init,
  ._exit = x_log_obj_op_exit,
  ._mutex_init = x_log_obj_op_mutex_init,
  ._mutex_lock = x_log_obj_op_mutex_lock,
  ._mutex_unlock = x_log_obj_op_mutex_unlock,
  ._mutex_destroy = x_log_obj_op_mutex_destroy,
  ._printf = x_log_obj_op_printf,

};

log_obj_t x_log_obj = {
  ._name = "x_log_obj",
  ._level = LOG_LEVEL_WARNING,
  ._property = &x_log_obj_default_property,
  ._op = &x_log_obj_default_operations,
  ._next = NULL,
};

