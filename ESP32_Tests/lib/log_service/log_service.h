#ifndef log_service_h
#define log_service_h


/* ==================================================
** Macro
**
** =============================================== */


#define LOG_ENABLE

#ifdef  LOG_ENABLE
#define LOG_PORT    Serial
#endif


/* ==================================================
** Library
**
** =============================================== */


#ifdef LOG_PORT
#include "HardwareSerial.h"
#endif


/* ==================================================
** Extern function declaration
**
** =============================================== */


void Log_init();

inline void Log_start_upd();
inline void Log_stop_upd();


/* ==================================================
** Macro function definition
**
** =============================================== */


#ifdef LOG_PORT

    #define LOG_I(fmt, ...) \
        do \
        { \
            Log_stop_upd(); \
            LOG_PORT.printf("I (%.3Lf) " fmt "\n", \
                            (long double)millis()/1000, ##__VA_ARGS__); \
        } while(0)


    #define LOG_E(fmt, ...) \
        do \
        { \
            Log_stop_upd(); \
            LOG_PORT.printf("E (%.3Lf) " fmt "\n", \
                            (long double)millis()/1000, ##__VA_ARGS__); \
        } while(0)


    #define LOG_U(fmt, ...) \
        do \
        { \
            Log_start_upd(); \
            LOG_PORT.printf("U (%.3Lf) " fmt "\n", \
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
    #define LOG_U(...)      do { (void)0; } while (0)
    #define LOG_PRINTF(...) do { (void)0; } while (0)

#endif

#endif