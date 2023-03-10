#ifndef log_service_h
#define log_service_h


/* ==================================================
** Libraries
**
** =============================================== */


#include "HardwareSerial.h"


/* ==================================================
** Macro definition
**
** =============================================== */



#define LOG_ENABLE
#define LOG_PORT    Serial

#ifdef LOG_ENABLE

    #ifdef LOG_PORT

    extern bool flg_upd;
    
    #define LOG_I(fmt, ...) \
        do \
        { \
            if(flg_upd){ \
                flg_upd = false; \
                LOG_PORT.printf("\n"); \
            } \
            LOG_PORT.printf("I (%.3Lf) " fmt "\r\n", \
                            (long double)millis()/1000, ##__VA_ARGS__); \
        } while (0)

    #define LOG_E(fmt, ...) \
        do \
        { \
            if(flg_upd){ \
                flg_upd = false; \
                LOG_PORT.printf("\n"); \
            } \
            LOG_PORT.printf("E (%.3Lf) " fmt "\r\n", \
                            (long double)millis()/1000, ##__VA_ARGS__); \
        } while (0)

    #define LOG_U(fmt, ...) \
        do \
        { \
            flg_upd = true; \
            LOG_PORT.printf("U (%.3Lf) " fmt "\r", \
                            (long double)millis()/1000, ##__VA_ARGS__); \
        } while(0)

    #define LOG_PRINTF(fmt, ...) \
        do \
        { \
            LOG_PORT.printf(fmt , ##__VA_ARGS__); \
        } while (0)

    #else
        #define LOG_I(...)      do { (void)0; } while (0)
        #define LOG_E(...)      do { (void)0; } while (0)
        #define LOG_PRINTF(...) do { (void)0; } while (0)
    #endif

#else
    #define LOG_I(...)      do { (void)0; } while (0)
    #define LOG_E(...)      do { (void)0; } while (0)
    #define LOG_PRINTF(...) do { (void)0; } while (0)
#endif


/* ==================================================
** Type definition
**
** =============================================== */


//


/* ==================================================
** Extern function declaration
**
** =============================================== */


void Log_init();


#endif