/* ==================================================
** Library
**
** =============================================== */


#include "log_service.h"


/* ==================================================
** Extern variable definition
**
** =============================================== */


bool flg_upd = false;



/* ==================================================
** Extern function definition
**
** =============================================== */


void Log_init()
{
    #ifdef LOG_PORT

    LOG_PORT.begin(115200);
    delay(2000);

    #endif
}


inline void Log_start_upd()
{
    flg_upd = true;
}


inline void Log_stop_upd()
{
    if(!flg_upd) {return;}

    flg_upd = false;
    LOG_PORT.printf("\n");
}