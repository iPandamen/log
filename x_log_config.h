
#ifndef __LOG_CONFIG_H__
#define __LOG_CONFIG_H__

#define X_LOG_ENABLE 1
#define XLOG_MUTEX_ENABLE 1

#define X_LOG_DEFAULT_FILE_NAME NULL

#define X_LOG_LEVEL X_LOG_LEVEL_VERBOSE

#if LOG_MUTEX_ENABLE

#include <pthread.h>

#  define X_LOG_MUTEX_TYPE pthread_mutex_t
#  define X_LOG_MUTEX_INIT(mutex) pthread_mutex_init(mutex, NULL);
#  define X_LOG_MUTEX_DESTROY(mutex) pthread_mutex_destroy(mutex);
#  define X_LOG_MUTEX_LOCK(mutex) pthread_mutex_lock(mutex);
#  define X_LOG_MUTEX_TRYLOCK(mutex) pthread_mutex_trylock(mutex);
#  define X_LOG_MUTEX_UNLOCK(mutex) pthread_mutex_unlock(mutex);

#endif

#endif /* __LOG_CONFIG_H__ */




