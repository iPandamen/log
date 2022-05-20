
#ifndef __X_LOG_CONFIG_H__
#define __X_LOG_CONFIG_H__

#ifndef X_LOG_DEFAULT_FILE_NAME
#warning "X_LOG_DEFAULT_FILE_NAME is not defined, the log will be ouput to stdout"
#define X_LOG_DEFAULT_FILE_NAME NULL
#endif /* X_LOG_DEFAULT_FILE_NAME */

#ifndef X_LOG_LEVEL
#warning "X_LOG_LEVEL is not defined, it will be set to the default value X_LOG_LEVEL_WARNING"
#define X_LOG_LEVEL LOG_LEVEL_WARNING
#endif /* X_LOG_LEVEL */

#endif /* __X_LOG_CONFIG_H__ */




