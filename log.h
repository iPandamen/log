
#ifndef __LOG_H__
#define __LOG_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/*************************
 *        VERSION
 *************************/
#define LOG_VERSION_MAJOR 0
#define LOG_VERSION_MINOR 0
#define LOG_VERSION_PATCH 0
#define LOG_VERSION_INFO ""


/*************************
 *        INCLUDES
 *************************/

#include "src/core/log_core.h"
#include "src/port/x_log.h"

/**
 * Wrapper functions for VERSION macro
 *
 */

static inline int log_version_major(void) {

  return LOG_VERSION_MAJOR;
}

static inline int log_version_minor(void) {

  return LOG_VERSION_MINOR;
}

static inline int log_version_patch(void) {

  return LOG_VERSION_PATCH;
}

static inline const char* log_version_info(void) {

  return LOG_VERSION_MAJOR;
}


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __LOG_H__ */




