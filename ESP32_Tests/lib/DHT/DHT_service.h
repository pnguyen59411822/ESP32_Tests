#ifndef DHT_service_h
#define DHT_service_h


/* ==================================================
** Libraries
**
** =============================================== */


#include <Arduino.h>


/* ==================================================
** Macro definition
**
** =============================================== */


//


/* ==================================================
** Type definition
**
** =============================================== */


//


/* ==================================================
** Extern function declaration
**
** =============================================== */


void DHT_init();
void DHT_upd();

float DHT_get_tempC();
float DHT_get_humi();


/* ==================================================
** Extern variables
**
** =============================================== */


//


#endif