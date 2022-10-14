

#include "x_log.h"

x_log_obj_t *x_log_obj_new(void) {
  
  return NULL;
}

void x_log_obj_del(x_log_obj_t *_obj){

}

int x_log_obj_init(x_log_obj_t* _obj) {
  if (_obj) {
    if (_obj->_path) {
      _obj->_fp = fopen(_obj->_path, "a+");
    } else {
      _obj->_fp = stdout;
    }
  }
  return 0;
}

int x_log_obj_reset(x_log_obj_t* _obj) {
  x_log_obj_exit(_obj);
  x_log_obj_init(_obj);
}

int x_log_obj_exit(x_log_obj_t* _obj) {
  if (_obj) {
    if (_obj->_fp != stdout) {
      fclose(_obj->_fp);
    }
    _obj->_fp = -1;
  }
  return 0;
}

int x_log_obj_printf(x_log_obj_t* _obj, const char* _str) {
  if (_obj) {
    if (_obj->_fp != -1) {
      fprintf(_obj->_fp, _str);
    }
  }
  return 0;
}

int x_log_obj_set_path(x_log_obj_t* _obj, const char* _path) {
  if (_obj) {
    _obj->_path = _path;
  }
  return 0;
}

const char* x_log_obj_get_path(x_log_obj_t* _obj) {
  const char* _path = NULL;
  if (_obj) {
    _path = _obj->_path;
  }
  return _path;
}

log_obj_operations_t x_log_obj_operations = {
  ._init = x_log_obj_init,
  ._exit = x_log_obj_exit,
  ._reset = x_log_obj_reset,
  ._printf = x_log_obj_printf,
};