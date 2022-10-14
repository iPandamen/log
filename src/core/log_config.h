
#ifndef __LOG_CONFIG_H__
#define __LOG_CONFIG_H__

#ifndef LOG_ENABLE_MUTEX
#define LOG_ENABLE_MUTEX 1
#endif /* LOG_ENABLE_MUTEX */


#if LOG_ENABLE_MUTEX

#include <pthread.h>

#define log_obj_mutex_init(mutex, attr)   pthread_mutex_init(mutex, attr)
#define log_obj_mutex_destroy(mutex)      pthread_mutex_destroy(mutex)
#define log_obj_mutex_lock(mutex)         pthread_mutex_lock(mutex)
#define log_obj_mutex_unlock(mutex)       pthread_mutex_unlock(mutex)

typedef pthread_mutex_t log_obj_mutex_t;

#else 

#define log_obj_mutex_init(mutex, attr) )
#define log_obj_mutex_destroy(mutex)    
#define log_obj_mutex_lock(mutex)       
#define log_obj_mutex_unlock(mutex)  

#endif /* LOG_ENABLE_MUTEX */


#endif /* __LOG_CONFIG_H__ */

