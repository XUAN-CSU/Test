#ifndef COMM_TYPE_H
#define COMM_TYPE_H

#include "device.h"

#define WLC_LOGI(...) device_master_log(LOGLEVEL_ONLY_CONSOLE | LOGLEVEL_ONLY_LOGI, ##__VA_ARGS__);
#define WLC_LOGW(...) device_master_log(LOGLEVEL_ONLY_CONSOLE | LOGLEVEL_ONLY_LOGW, ##__VA_ARGS__);
#define WLC_LOGE(...) device_master_log(LOGLEVEL_ONLY_CONSOLE | LOGLEVEL_ONLY_LOGE, ##__VA_ARGS__);

#endif
