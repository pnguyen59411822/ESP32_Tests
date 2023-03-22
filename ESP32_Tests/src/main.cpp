#include <Arduino.h>
#include "fuzzy_service.h"


void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.print(F("\n\n"));

  randomSeed(analogRead(0));
  
  Fuzzy_init();
}

void loop()
{
  // get random entrances
  float input1 = Fuzzy_random_input1();
  float input2 = Fuzzy_random_input2();
  float output = Fuzzy_get_ouput(input1, input2);

  Serial.printf("Input 1: %.2f | Input 2: %.2f | Output: %.2f", input1, input2, output);

  // wait 12 seconds
  delay(8000);
}