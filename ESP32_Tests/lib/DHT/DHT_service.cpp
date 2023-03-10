/* ==================================================
** Libraries
**
** =============================================== */


#include "DHT_service.h"
#include "DHT_const.h"

#include "log_service.h"


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
** Extern variables
**
** =============================================== */


//


/* ==================================================
** Global variables
**
** =============================================== */


DHT dht(DHT_PIN, DHT_TYPE);

// Huminity
float huminity;
// Temperature C
float tempC;
// Temperature F
float tempF;
// Heat index C
float hiC;
// Heat index F
float hiF;

uint32_t intv_wait_upd;


/* ==================================================
** Global function declaration
**
** =============================================== */


//


/* ==================================================
** Global function definition
**
** =============================================== */


//


/* ==================================================
** Extern function definition
**
** =============================================== */


void DHT_init()
{
    dht.begin();
}


void DHT_upd()
{
    if(millis() - intv_wait_upd < TIME_WAIT_UPD) {return;}

    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float f = dht.readTemperature(true);

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t) || isnan(f))
    {
        LOG_E("[DHT] Failed to read from DHT sensor!");
        return;
    }

    huminity    = h;
    tempC       = t;
    tempF       = f;
    hiC         = dht.computeHeatIndex(t, h, false);
    hiF         = dht.computeHeatIndex(t, h);

    LOG_I("[DHT][UPD] Humidity: %.2f% | Temperature: %.2f°C  %.2f°F | Head index: %.2f°C  %.2f°F\n", h, t, f, hiC, hiF);
}


float DHT_get_tempC()
{
    return tempC;
}


float DHT_get_humi()
{
    return huminity;
}
