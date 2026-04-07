#ifndef YASTK_DEBUG_H
#define YASTK_DEBUG_H

#define YASTK_DEBUG 1

#ifdef NDEBUG
#undef YASTK_DEBUG
#define YASTK_DEBUG 0
#endif

#if YASTK_DEBUG == 1

#include <stdio.h>
#include <stdarg.h>

#define YASTK_DEBUG_PREFIX "[ YASTK DEBUG ]: "
#define YASTK_INFO_PREFIX  "[ YASTK INFO ]: "
#define YASTK_WARN_PREFIX  "[ YASTK WARN ]: "
#define YASTK_ERROR_PREFIX "[ YASTK ERROR ]: "

#define YASTK_LOG_DEBUG(formatted_string, ...) \
    printf("\e[0;36m" YASTK_DEBUG_PREFIX "\e[0m" formatted_string, ##__VA_ARGS__)

#define YASTK_LOG_INFO(formatted_string, ...) \
    printf("\e[0;32m" YASTK_INFO_PREFIX "\e[0m" formatted_string, ##__VA_ARGS__)

#define YASTK_LOG_WARN(formatted_string, ...) \
    printf("\e[0;33m" YASTK_WARN_PREFIX "\e[0m" formatted_string, ##__VA_ARGS__)

#define YASTK_LOG_ERROR(formatted_string, ...) \
    printf("\e[0;31m" YASTK_ERROR_PREFIX "\e[0m" formatted_string, ##__VA_ARGS__)

#define YASTK_LOG_FUNCTION_CALL(fn_name) \
    YASTK_LOG_DEBUG(fn_name " was called.\n")

#define YASTK_LOG_FUNCTION_BACK(fn_name) \
    YASTK_LOG_DEBUG("Back in " fn_name "\n")

#define YASTK_TYPE_CALL_ADDRESS 0
#define YASTK_TYPE_CALL_VALUE   1

#define YASTK_LOG_PARAMETER(ordinal_number, type_str, type_call, fmt, ...) \
    YASTK_LOG_DEBUG(ordinal_number " parameter (type: " type_str ") with %s " fmt, \
              (type_call == YASTK_TYPE_CALL_ADDRESS ? "address" : "value"), \
              ##__VA_ARGS__)

#define YASTK_LOG_RETURN(type_str, type_call, fmt, ...) \
    YASTK_LOG_DEBUG("Returning (type: " type_str ") %s " fmt, \
              (type_call == YASTK_TYPE_CALL_ADDRESS ? "address" : "value"), \
              ##__VA_ARGS__)

#define YASTK_TCA YASTK_TYPE_CALL_ADDRESS
#define YASTK_TCV YASTK_TYPE_CALL_VALUE

#else

/* No-op macros when YASTK_DEBUG is disabled */
#define YASTK_LOG_DEBUG(formatted_string, ...)
#define YASTK_LOG_INFO(formatted_string, ...)
#define YASTK_LOG_WARN(formatted_string, ...)
#define YASTK_LOG_ERROR(formatted_string, ...)
#define YASTK_LOG_FUNCTION_CALL(fn_name)
#define YASTK_LOG_FUNCTION_BACK(fn_name)
#define YASTK_LOG_PARAMETER(ordinal_number, type_str, type_call, fmt, ...)
#define YASTK_LOG_RETURN(type_str, type_call, fmt, ...)

#endif

#endif
