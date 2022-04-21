
#ifndef __LOG_CONFIG_H__
#define __LOG_CONFIG_H__

#define LOG_ENABLE 1
#define LOG_MUTEX_ENABLE 1

#define DEFAULT_LOG_FILE_NAME NULL

#define LOG_LEVEL LOG_LEVEL_VERBOSE

#if LOG_MUTEX_ENABLE

#include <pthread.h>

#  define LOG_MUTEX_TYPE pthread_mutex_t
#  define LOG_MUTEX_INIT(mutex) pthread_mutex_init(mutex, NULL);
#  define LOG_MUTEX_DESTROY(mutex) pthread_mutex_destroy(mutex);
#  define LOG_MUTEX_LOCK(mutex) pthread_mutex_lock(mutex);
#  define LOG_MUTEX_TRYLOCK(mutex) pthread_mutex_trylock(mutex);
#  define LOG_MUTEX_UNLOCK(mutex) pthread_mutex_unlock(mutex);

#endif

#endif /* __LOG_CONFIG_H__ */




