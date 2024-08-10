#include <stdio.h>              // fwrite fclose
#include <time.h>
#include <stdarg.h>				// using for the va relative
#include "device.h"
#include <string.h>

#define LOG_FILE_FLAG_MASTER 0
#define LOG_FILE_FLAG_USER 1

#define DEFAULT_APPHOME "/bin/"
#define DEFAULT_SRVHOME "/"
#define DEFAULT_FONTHOME "/usr/font/tm_font"

#define DEFAULT_BASEPATH "./data/"
#define DEFAULT_BASEPATH_APP "apps/"
#define DEFAULT_BASEPATH_MASTER "master/"

#define DEFAULT_CFGFILE "./.szconfig"
#define DEFAULT_MASTER_LOGNAME "master.log"


unsigned char g_base_path[512];
unsigned char g_master_logname[512];

static int log_writebuf(const char *filename, unsigned char *content, int buflen);
static unsigned char*  method_base_getbasedir();     /* quick get, ensure memory right, no need to free, but thread nnot safety */
static unsigned char* method_base_getmasterbasedir();
static int log_get_masterdir(char *o_logfilename, int filename_len);
static int log_getlogfilename(int flag, char *o_logfilename, int filename_len);
static int device_logs(int flag, int level, const char *loginfo, int log_length);

static int log_writebuf(const char *filename, unsigned char *content, int buflen)
{
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        perror("Error opening file writebuf");
        printf(" err filename %s\n", filename);
        return -1;
    }

    size_t w = fwrite(content, sizeof(char), buflen, file);
    fclose(file);
    return w == buflen ? 0 : -1;
}

static unsigned char*  method_base_getbasedir()     /* quick get, ensure memory right, no need to free, but thread nnot safety */
{
    strcpy(g_base_path, DEFAULT_BASEPATH);
    return g_base_path;
}

static unsigned char* method_base_getmasterbasedir()
{
    char *p = method_base_getbasedir();
    strcat(p, DEFAULT_BASEPATH_MASTER);
    return g_base_path;
}
static int log_get_masterdir(char *o_logfilename, int filename_len)
{
    if (!o_logfilename || filename_len <= 0)
        return -1;
    char *p = method_base_getmasterbasedir();
    strncpy(o_logfilename, p, filename_len);
    return 0;
}

static int log_getlogfilename(int flag, char *o_logfilename, int filename_len)
{
    // printf("============%s,%d=============\n", __FUNCTION__, __LINE__);
    int ret = -1;
    if (flag == 0) { // master
        if (strlen(g_master_logname) > 0) {
            strncpy(o_logfilename, g_master_logname, filename_len);
        } else {
            char path[128] = {};
            log_get_masterdir(path, sizeof(path));
            strcat(path, DEFAULT_MASTER_LOGNAME);
            strcpy(g_master_logname, path);
            strncpy(o_logfilename, path, filename_len);
        }

        ret = 0;
    } else if (flag == 1) {
        o_logfilename = "user/user.lgo";
        filename_len = sizeof(o_logfilename);
        ret = 0;
        //ret = log_get_curuserdir(o_logfilename, filename_len);
    }
    return ret;
}

// char g_logbuf[1024]
static int device_logs(int flag, int level, const char *loginfo, int log_length)
{
    if (!loginfo) {
        return -1;
    }
    int log_con = 0;
    int log_d = 0, log_v = 0, log_i = 0, log_w = 0, log_e = 0, log_f =0;
    int ret = 0;

    char filename[512] = {};
    ret = log_getlogfilename(flag, filename, sizeof(filename));

    if (ret) {
        printf("CANNOT FIND LOG FILE %s\n", filename);
        return -1;
    }

    if (level & LOGLEVEL_ONLY_CONSOLE) {
        log_con = 1;
        printf("%s\n", loginfo);
    }

    if (level & LOGLEVEL_ONLY_LOGD) {
        log_d = 1;
        log_writebuf(filename, loginfo, log_length);
    }

    if (level & LOGLEVEL_ONLY_LOGV) {
        log_v = 1;
        log_writebuf(filename, loginfo, log_length);
    }

    if (level & LOGLEVEL_ONLY_LOGI) {
        log_i = 1;
        log_writebuf(filename, loginfo, log_length);
    }

    if (level & LOGLEVEL_ONLY_LOGW) {
        log_i = 1;
        log_writebuf(filename, loginfo, log_length);
    }
       
    if (level & LOGLEVEL_ONLY_LOGE) {
        log_e = 1;
        log_writebuf(filename, loginfo, log_length);
    }
    return ret;
}   // end fo the device_logs(int flag, int level, const char *loginfo, int log_length)


int device_master_log(E_LOGLEVEL level, const char *format, ...)
{
    if (!format || strlen(format) < 0) {
        return -1;
    }

    char args_buff[4096] = {};

    time_t t = time(NULL);
    struct tm* now = localtime(&t);
    char time_buffer[80] ={};
    strftime(time_buffer, 80, "%Y%m%d %H%M%S", now);
    strcpy(args_buff, time_buffer);

    int t_len = strlen(time_buffer);

    int total_len = 0;

    va_list args;
    va_start(args, format);
    int length = vsnprintf(args_buff + t_len, sizeof(args_buff) - t_len, format, args);
    length += t_len;
    va_end(args);

    int ret = device_logs(LOG_FILE_FLAG_MASTER, level, args_buff, length);

    return ret;
}
