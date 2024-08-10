#ifndef __DEVICE_H
#define __DEVICE_h

typedef enum {
    LOGLEVEL_ONLY_CONSOLE   = 0b00000001,
    LOGLEVEL_ONLY_LOGD      = 0b00000010,
    LOGLEVEL_ONLY_LOGV      = 0b00000100,
    LOGLEVEL_ONLY_LOGI      = 0b00001000,
    LOGLEVEL_ONLY_LOGW      = 0b00010000,
    LOGLEVEL_ONLY_LOGE      = 0b00100000,
} E_LOGLEVEL;

int device_master_log(E_LOGLEVEL level, const char *format, ...);

#endif
