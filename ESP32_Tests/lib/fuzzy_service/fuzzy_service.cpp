
#include <Arduino.h>
#include <Fuzzy.h>


/* ==================================================
** Macro
**
** =============================================== */


#define INDEX_FUZZY_INPUT1 1
#define INDEX_FUZZY_INPUT2 2
#define INDEX_FUZZY_OUTPUT 1


/* ==================================================
** Function declaration
**
** =============================================== */


void init_fuzzySets_input1();
void init_fuzzySets_input2();
void init_fuzzySets_output();
void init_antecedents();
void init_consequents();
void init_rules();
void init_fuzzy();


/* ==================================================
** Constant
**
** =============================================== */


const float membershipFunctions_input1[] = {18, 21, 24, 26, 29, 32, 35, 38, 41, 43, 45};
const float membershipFunctions_input2[] = {-10, 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110};
const float membershipFunctions_output[] = {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 49, 50, 51, 56, 57, 58, 62, 65, 66, 69, 74, 75, 77, 84, 85, 95, 96, 107, 119, 131};

const float consequents_value[] = {
        18, 18, 18, 19, 20, 21, 21, 21, 22, 22,  22,
        21, 21, 22, 23, 23, 24, 24, 25, 25, 26,  26, 
        23, 24, 25, 25, 26, 27, 27, 29, 29, 31,  33, 
        25, 26, 27, 28, 29, 31, 32, 34, 36, 39,  42, 
        28, 29, 30, 32, 34, 35, 38, 41, 45, 50,  56, 
        30, 32, 34, 35, 38, 42, 45, 51, 58, 66,  74, 
        33, 35, 37, 40, 43, 49, 56, 62, 69, 77,  85, 
        35, 38, 41, 45, 50, 57, 65, 74, 84, 95,  107, 
        37, 41, 44, 51, 58, 66, 75, 85, 96, 107, 119};

const int num_fuzzySets_input1 = sizeof(membershipFunctions_input1) / sizeof(membershipFunctions_input1[0])-2;
const int num_fuzzySets_input2 = sizeof(membershipFunctions_input2) / sizeof(membershipFunctions_input2[0])-2;
const int num_fuzzySets_output = sizeof(membershipFunctions_output) / sizeof(membershipFunctions_output[0])-2;
const int num_rules = sizeof(consequents_value) / sizeof(consequents_value[0]);


/* ==================================================
** Variable
**
** =============================================== */


Fuzzy fuzzy;

FuzzySet fuzzySets_input1[num_fuzzySets_input1];
FuzzySet fuzzySets_input2[num_fuzzySets_input2];
FuzzySet fuzzySets_output[num_fuzzySets_output];

FuzzyInput  fuzzyInput1 = FuzzyInput(INDEX_FUZZY_INPUT1);
FuzzyInput  fuzzyInput2 = FuzzyInput(INDEX_FUZZY_INPUT2);
FuzzyOutput fuzzyOutput = FuzzyOutput(INDEX_FUZZY_OUTPUT);

FuzzyRuleAntecedent antecedents[num_rules];
FuzzyRuleConsequent consequents[num_rules];
FuzzyRule           rules      [num_rules];


/* ==================================================
** Main
**
** =============================================== */


void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.print(F("\n\n"));

  randomSeed(analogRead(0));

  init_fuzzySets_input1();
  init_fuzzySets_input2();
  init_fuzzySets_output();
  init_antecedents();
  init_consequents();
  init_rules();
  init_fuzzy();
}


void loop()
{
float input1 = random(membershipFunctions_input1[1], membershipFunctions_input1[num_fuzzySets_input1]);
float input2 = random(membershipFunctions_input2[1], membershipFunctions_input2[num_fuzzySets_input2]);

fuzzy.setInput(INDEX_FUZZY_INPUT1, input1);
fuzzy.setInput(INDEX_FUZZY_INPUT2, input2);

fuzzy.fuzzify();

float output = fuzzy.defuzzify(INDEX_FUZZY_OUTPUT);
Serial.printf("Input1: %.2f | Input 2: %.2f | Ouput: %.2f\n", input1, input2, output);

delay(2000);
}


/* ==================================================
** Function definition
**
** =============================================== */


void init_fuzzySets_input1()
{
  for(int i=0; i<num_fuzzySets_input1; ++i)
  {
    float a = membershipFunctions_input1[i];
    float b = membershipFunctions_input1[i+1];
    float c = membershipFunctions_input1[i+1];
    float d = membershipFunctions_input1[i+2];

    fuzzySets_input1[i] = FuzzySet(a, b, c, d);
    fuzzyInput1.addFuzzySet(&fuzzySets_input1[i]);
  }
}


void init_fuzzySets_input2()
{
  for(int i=0; i<num_fuzzySets_input2; ++i)
  {
    float a = membershipFunctions_input2[i];
    float b = membershipFunctions_input2[i+1];
    float c = membershipFunctions_input2[i+1];
    float d = membershipFunctions_input2[i+2];

    fuzzySets_input2[i] = FuzzySet(a, b, c, d);
    fuzzyInput2.addFuzzySet(&fuzzySets_input2[i]);
  }
}


void init_fuzzySets_output()
{
  for(int i=0; i<num_fuzzySets_output; ++i)
  {
    float a = membershipFunctions_output[i];
    float b = membershipFunctions_output[i+1];
    float c = membershipFunctions_output[i+1];
    float d = membershipFunctions_output[i+2];

    fuzzySets_output[i] = FuzzySet(a, b, c, d);
    fuzzyOutput.addFuzzySet(&fuzzySets_output[i]);
  }
}


void init_antecedents()
{
  for(int i=0; i<num_fuzzySets_input1; ++i){
    for(int j=0; j<num_fuzzySets_input2; ++j)
    {
      antecedents[i*num_fuzzySets_input2+j].joinWithAND(&fuzzySets_input1[i], &fuzzySets_input2[j]);
    }
  }
}


void init_consequents()
{
  for(int i=0; i<num_rules; ++i)
  {
    for(int j=0; j<num_fuzzySets_output; ++j)
    {
      if(consequents_value[i] == membershipFunctions_output[j+1]){
        consequents[i].addOutput(&fuzzySets_output[j]);
        break;
      }
    }
  }
}


void init_rules()
{
  for(int i=0; i<num_rules; ++i){
    rules[i] = FuzzyRule(i+1, &antecedents[i], &consequents[i]);
  }
}


void init_fuzzy()
{
  fuzzy.addFuzzyInput  (&fuzzyInput1);
  fuzzy.addFuzzyInput  (&fuzzyInput2);
  fuzzy.addFuzzyOutput (&fuzzyOutput);

  for(int i=0; i<num_rules; ++i){
    fuzzy.addFuzzyRule(&rules[i]);
  }
}