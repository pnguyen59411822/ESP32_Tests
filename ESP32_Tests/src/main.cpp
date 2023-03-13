#include <Arduino.h>
#include <Fuzzy.h>

// For scope, instantiate all objects you will need to access in loop()
// It may be just one Fuzzy, but for demonstration, this sample will print
// all FuzzySet pertinence

// Fuzzy
Fuzzy fuzzy = Fuzzy();

FuzzyInput  distance = FuzzyInput(1);
FuzzyOutput risk     = FuzzyOutput(1);

// FuzzyInput
FuzzySet near = FuzzySet(0, 20, 20, 40);
FuzzySet safe = FuzzySet(30, 50, 50, 70);
FuzzySet distant = FuzzySet(60, 80, 100, 100);

// FuzzyOutput
FuzzySet minimum = FuzzySet(0, 20, 20, 40);
FuzzySet average = FuzzySet(30, 50, 50, 70);
FuzzySet maximum = FuzzySet(60, 80, 80, 100);

FuzzyRuleAntecedent distanceNear = FuzzyRuleAntecedent();                     
FuzzyRuleConsequent riskMinimum  = FuzzyRuleConsequent();                     
FuzzyRule           fuzzyRule1   = FuzzyRule(1, &distanceNear, &riskMinimum); 

FuzzyRuleAntecedent distanceSafe = FuzzyRuleAntecedent();                     
FuzzyRuleConsequent riskAverage  = FuzzyRuleConsequent();                     
FuzzyRule           fuzzyRule2   = FuzzyRule(2, &distanceSafe, &riskAverage); 

FuzzyRuleAntecedent distanceDistant = FuzzyRuleAntecedent();                         
FuzzyRuleConsequent riskMaximum     = FuzzyRuleConsequent();                         
FuzzyRule           fuzzyRule3      = FuzzyRule(3, &distanceDistant, &riskMaximum);  

void setup()
{
  // Set the Serial output  
  Serial.begin(115200);
  // Set a random seed
  randomSeed(analogRead(0));

  // Every setup must occur in the function setup()

  // FuzzyInput

  if(!distance.addFuzzySet(&near))     {Serial.printf("FuzzyInput distance add FuzzySet near failed\n");}
  if(!distance.addFuzzySet(&safe))     {Serial.printf("FuzzyInput distance add FuzzySet safe failed\n");}
  if(!distance.addFuzzySet(&distant))  {Serial.printf("FuzzyInput distance add FuzzySet distant failed\n");}
  fuzzy.addFuzzyInput(&distance);
  

  // FuzzyOutput

  risk.addFuzzySet(&minimum);
  risk.addFuzzySet(&average);
  risk.addFuzzySet(&maximum);
  fuzzy.addFuzzyOutput(&risk);
  
  // Building FuzzyRule
  distanceNear.joinSingle(&near);
  riskMinimum.addOutput(&minimum);
  fuzzy.addFuzzyRule(&fuzzyRule1);

  // Building FuzzyRule
  distanceNear.joinSingle(&safe);
  riskMinimum.addOutput(&average);
  fuzzy.addFuzzyRule(&fuzzyRule2);

  // Building FuzzyRule
  distanceNear.joinSingle(&distant);
  riskMinimum.addOutput(&maximum);
  fuzzy.addFuzzyRule(&fuzzyRule3);
  
}

void loop()
{
  // get random entrances
  int input1 = random(0, 100);

  Serial.println("\n\n\nEntrance: ");
  Serial.print("\t\t\tDistance: ");
  Serial.print(input1);
  Serial.println("");

  fuzzy.setInput(1, input1);

  fuzzy.fuzzify();

  Serial.println("Input: ");
  Serial.print("\tDistance: Near-> ");
  Serial.print(near.getPertinence());
  Serial.print(", Safe-> ");
  Serial.print(safe.getPertinence());
  Serial.print(", Distant-> ");
  Serial.println(distant.getPertinence());

  float output1 = fuzzy.defuzzify(1);

  Serial.println("Output: ");
  Serial.print("\tRisk: Minimum-> ");
  Serial.print(minimum.getPertinence());
  Serial.print(", Average-> ");
  Serial.print(average.getPertinence());
  Serial.print(", Maximum-> ");
  Serial.println(maximum.getPertinence());

  Serial.println("Result: ");
  Serial.print("\t\t\tRisk: ");
  Serial.print(output1);

  // wait 12 seconds
  delay(8000);
}