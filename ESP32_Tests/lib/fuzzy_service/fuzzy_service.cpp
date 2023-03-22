
#include "fuzzy_service.h"
#include "fuzzy_service_const.h"

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


// 


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


void Fuzzy_init()
{
  randomSeed(analogRead(0));

  init_fuzzySets_input1();
  init_fuzzySets_input2();
  init_fuzzySets_output();
  init_antecedents();
  init_consequents();
  init_rules();
  init_fuzzy();
}


float Fuzzy_get_ouput(float input1, float input2)
{
    fuzzy.setInput(INDEX_FUZZY_INPUT1, input1);
    fuzzy.setInput(INDEX_FUZZY_INPUT2, input2);

    fuzzy.fuzzify();
    return fuzzy.defuzzify(INDEX_FUZZY_OUTPUT);
}


float Fuzzy_random_input1()
{
    return random(input1_min, input1_max);
}


float Fuzzy_random_input2()
{
    return random(input2_min, input2_max);
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