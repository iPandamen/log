
#ifndef __X_LOG_CONFIG_H__
#define __X_LOG_CONFIG_H__

#ifndef  X_LOG_ENABLE
#define X_LOG_ENABLE 1
#endif /* X_LOG_ENABLE */


#ifndef X_LOG_DEFAULT_FILE_NAME
#define X_LOG_DEFAULT_FILE_NAME NULL
#endif /* X_LOG_DEFAULT_FILE_NAME */

#ifndef X_LOG_LEVEL
#warning "The X_LOG_LEVEL define is not defined, it will be set as default value X_LOG_LEVEL_WARNING"
#define X_LOG_LEVEL X_LOG_LEVEL_WARNING
#endif /* X_LOG_LEVEL */


#ifndef X_LOG_MUTEX_ENABLE
#define X_LOG_MUTEX_ENABLE 0
#endif /*  X_LOG_MUTEX_ENABLE */

#if X_LOG_MUTEX_ENABLE

#include <pthread.h>

#  define X_LOG_MUTEX_TYPE pthread_mutex_t
#  define X_LOG_MUTEX_INIT(mutex) pthread_mutex_init(mutex, NULL);
#  define X_LOG_MUTEX_DESTROY(mutex) pthread_mutex_destroy(mutex);
#  define X_LOG_MUTEX_LOCK(mutex) pthread_mutex_lock(mutex);
#  define X_LOG_MUTEX_TRYLOCK(mutex) pthread_mutex_trylock(mutex);
#  define X_LOG_MUTEX_UNLOCK(mutex) pthread_mutex_unlock(mutex);

#endif

#endif /* __X_LOG_CONFIG_H__ /




