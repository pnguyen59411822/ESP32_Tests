/* ==================================================
** Library
**
** =============================================== */


#include "log_service.h"


/* ==================================================
** Macro
**
** =============================================== */


#ifndef MONITOR_SPEED
#define MONITOR_SPEED			115200
#endif


/* ==================================================
** Extern variables
**
** =============================================== */


bool flg_upd = false;



/* ==================================================
** Extern function definition
**
** =============================================== */


void Log_init()
{
    #ifdef LOG_ENABLE
    #ifdef LOG_PORT
    LOG_PORT.begin(MONITOR_SPEED);
    LOG_PRINTF("\n\n\r");
    delay(500);
    #endif
    #endif
}