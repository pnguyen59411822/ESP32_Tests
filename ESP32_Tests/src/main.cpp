#include <Arduino.h>

#include "log_service.h"
#include "DHT_service.h"

void setup() 
{
  Log_init();
  DHT_init();
}


void loop() 
{
  DHT_upd();
}