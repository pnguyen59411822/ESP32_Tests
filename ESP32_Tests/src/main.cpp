/* ==================================================
** Document
**
** =============================================== */


/**
 * 
 * Author:  Nguyễn Đại Phúc
 * Date:    9/3/2023
 * 
 * 
 * Title:   Use Fuzzy Logic to evaluate how hot it is
 * 
 * 
 * Shape point
 * 
 *     b .------. c     |     b /\ c     |  b *-----* c
 *      /        \      |      /  \      |    |      \
 *     /          \     |     /    \     |    |       \
 *  a *------------* d  |  a *------* d  |  a *--------* d
 * 
 * 
 * Details:
 * 
 *  Source: http://3.bp.blogspot.com/-J6nZXMi7zgo/Ueh_F2qPV0I/AAAAAAAAA4M/P4ioqBgVqrY/s1600/Chart025.gif
 *  
 *  Input
 *    1) Temperature      Min - Max   |   a   :   b   :   c   :   d
 *       - Cold           0   - 20    |   0   :   0   :   15  :   20
 *       - cool           21  - 29    |   15  :   20  :   20  :   30
 *       - warm           30  - 38    |   20  :   30  :   30  :   39
 *       - hot            39  - 45    |   30  :   39  :   39  :   45
 *       - very hot       46  - 54    |   39  :   45  :   45  :   55
 *       - scorching      55  - 100   |   45  :   55  :   100 :   100
 * 
 *    2) Humidity         Min - Max   |   a   :   b   :   c   :   d
 *       - Very dry       0   - 20    |   0   :   0   :   0   :   20
 *       - Dry            20  - 40    |   0   :   20  :   20  :   40
 *       - Normal         40  - 60    |   20  :   40  :   40  :   60
 *       - Wet            50  - 70    |   40  :   60  :   60  :   80
 *       - Very wet       60  - 100   |   60  :   80  :   100 :   100
 * 
 * 
 *  Output
 *    1) Heat index       Min - Max   |   a   :   b   :   c   :   d
 *       - no heat        0   - 20    |   0   :   0   :   15  :   20
 *       - comfort        21  - 29    |   15  :   20  :   20  :   30
 *       - discomfort     30  - 38    |   20  :   30  :   30  :   39
 *       - caution        39  - 45    |   30  :   39  :   39  :   45
 *       - dangerous      46  - 54    |   39  :   45  :   45  :   55
 *       - hazardous      55  - 100   |   45  :   55  :   100 :   100
 * 
 * 
 * Rules:
 *  
 * -----------------|-----------|-----------|-----------|-----------|-----------|
 *                  | very dry  |    dry    |   normal  |    wet    |  very wet |
 *                  | 0% - 20%  | 20% - 40% | 40% - 60% | 60% - 80% | 80% - 100%|
 * -----------------|-----------|-----------|-----------|-----------|-----------|
 * cold:      0ºC   | no heat   | no heat   | no heat   | no heat   | no heat   |
 * -----------------|-----------|-----------|-----------|-----------|-----------|
 * cool:      20ºC  | comfort   | comfort   | comfort   | comfort   | comfort   |
 * -----------------|-----------|-----------|-----------|-----------|-----------|
 * warm:      30ºC  | discomfort| discomfort| discomfort| caution   | caution   |
 * -----------------|-----------|-----------|-----------|-----------|-----------|
 * hot:       39ºC  | caution   | caution   | dangerous | hazardous | hazardous |
 * -----------------|-----------|-----------|-----------|-----------|-----------|
 * very hot:  45ºC  | dangerous | hazardous | hazardous | hazardous | hazardous |
 * -----------------|-----------|-----------|-----------|-----------|-----------|
 * scorching: 55ºC  | hazardous | hazardous | hazardous | hazardous | hazardous |
 * -----------------|-----------|-----------|-----------|-----------|-----------|
 * 
*/


/* ==================================================
** Library
**
** =============================================== */


#include <Arduino.h>

#include "Fuzzy.h"

#include "log_service.h"
#include "DHT_service.h"


/* ==================================================
** Macro definition
**
** =============================================== */


#define INDEX_FUZZY_TEMP        1
#define INDEX_FUZZY_HUMI        2
#define INDEX_FUZZY_HEAT_INDEX  3


/* ==================================================
** Function declaration
**
** =============================================== */


FuzzyInput  crt_fuzzyTemp();
FuzzyInput  crt_fuzzyHumi();
FuzzyOutput crt_fuzzyHeatIndex();

FuzzyRuleAntecedent crt_antecedent_cold();
FuzzyRuleAntecedent crt_antecedent_cool();
FuzzyRuleAntecedent crt_antecedent_warm_AndVeryDryToNormal();
FuzzyRuleAntecedent crt_antecedent_warm_AndWetToVeryWet();
FuzzyRuleAntecedent crt_antecedent_hot_AndVeryDryToDry();
FuzzyRuleAntecedent crt_antecedent_hot_AndNormal();
FuzzyRuleAntecedent crt_antecedent_hot_AndWetToVeryWet();
FuzzyRuleAntecedent crt_antecedent_veryHot_AndVeryDry();
FuzzyRuleAntecedent crt_antecedent_veryHot_AndDryToVeryWet();
FuzzyRuleAntecedent crt_antecedent_scorching();

FuzzyRuleConsequent crt_consequent_noHeat();
FuzzyRuleConsequent crt_consequent_comfort();
FuzzyRuleConsequent crt_consequent_discomfort();
FuzzyRuleConsequent crt_consequent_caution();
FuzzyRuleConsequent crt_consequent_dangerous();
FuzzyRuleConsequent crt_consequent_hazardous();

FuzzyRule crt_rule1(FuzzyRuleAntecedent  *antecedent, FuzzyRuleConsequent *consequent);
FuzzyRule crt_rule2(FuzzyRuleAntecedent  *antecedent, FuzzyRuleConsequent *consequent);
FuzzyRule crt_rule3(FuzzyRuleAntecedent  *antecedent, FuzzyRuleConsequent *consequent);
FuzzyRule crt_rule4(FuzzyRuleAntecedent  *antecedent, FuzzyRuleConsequent *consequent);
FuzzyRule crt_rule5(FuzzyRuleAntecedent  *antecedent, FuzzyRuleConsequent *consequent);
FuzzyRule crt_rule6(FuzzyRuleAntecedent  *antecedent, FuzzyRuleConsequent *consequent);
FuzzyRule crt_rule7(FuzzyRuleAntecedent  *antecedent, FuzzyRuleConsequent *consequent);
FuzzyRule crt_rule8(FuzzyRuleAntecedent  *antecedent, FuzzyRuleConsequent *consequent);
FuzzyRule crt_rule9(FuzzyRuleAntecedent  *antecedent, FuzzyRuleConsequent *consequent);
FuzzyRule crt_rule10(FuzzyRuleAntecedent *antecedent, FuzzyRuleConsequent *consequent);


/* ==================================================
** Global variables
**
** =============================================== */


Fuzzy fuzzy = Fuzzy();

// Temperature input
FuzzySet cold       = FuzzySet(0,   0,   15,  20);
FuzzySet cool       = FuzzySet(15,  20,  20,  30);
FuzzySet warm       = FuzzySet(20,  30,  30,  39);
FuzzySet hot        = FuzzySet(30,  39,  39,  45);
FuzzySet veryHot    = FuzzySet(39,  45,  45,  55);
FuzzySet scorching  = FuzzySet(45,  55,  100, 100);

// Humidity input
FuzzySet veryDry  = FuzzySet(0,   0,   0,   20);
FuzzySet dry      = FuzzySet(0,   20,  20,  40);
FuzzySet normal   = FuzzySet(20,  40,  40,  60);
FuzzySet wet      = FuzzySet(40,  60,  60,  80);
FuzzySet veryWet  = FuzzySet(60,  100, 100, 100);

// Heat index ouput
FuzzySet noHeat     = FuzzySet(0,   0,   15,  20);
FuzzySet comfort    = FuzzySet(15,  20,  20,  30);
FuzzySet discomfort = FuzzySet(20,  30,  30,  39);
FuzzySet caution    = FuzzySet(30,  39,  39,  45);
FuzzySet dangerous  = FuzzySet(39,  45,  45,  55);
FuzzySet hazardous  = FuzzySet(45,  55,  100, 100);


/* ==================================================
** Main
**
** =============================================== */


void setup() 
{
  Log_init();
  DHT_init();

  FuzzyInput  fuzzyTemp      = crt_fuzzyTemp();
  FuzzyInput  fuzzyHumi      = crt_fuzzyHumi();
  FuzzyOutput fuzzyHeatIndex = crt_fuzzyHeatIndex();

  fuzzy.addFuzzyInput (&fuzzyTemp);
  fuzzy.addFuzzyInput (&fuzzyHumi);
  fuzzy.addFuzzyOutput(&fuzzyHeatIndex);

}


void loop() 
{
  DHT_upd();
}


/* ==================================================
** Function definition
**
** =============================================== */


FuzzyInput  crt_fuzzyTemp()
{
  FuzzyInput fuzzyInput = FuzzyInput(INDEX_FUZZY_TEMP);

  fuzzyInput.addFuzzySet(&cold);
  fuzzyInput.addFuzzySet(&cool);
  fuzzyInput.addFuzzySet(&warm);
  fuzzyInput.addFuzzySet(&hot);
  fuzzyInput.addFuzzySet(&veryHot);
  fuzzyInput.addFuzzySet(&scorching);

  return fuzzyInput;
}


FuzzyInput  crt_fuzzyHumi()
{
  FuzzyInput fuzzyInput = FuzzyInput(INDEX_FUZZY_HUMI);

  fuzzyInput.addFuzzySet(&veryDry);
  fuzzyInput.addFuzzySet(&dry);
  fuzzyInput.addFuzzySet(&normal);
  fuzzyInput.addFuzzySet(&wet);
  fuzzyInput.addFuzzySet(&veryWet);

  return fuzzyInput;
}


FuzzyOutput crt_fuzzyHeatIndex()
{
  FuzzyOutput fuzzyOutput = FuzzyOutput(INDEX_FUZZY_HEAT_INDEX);

  fuzzyOutput.addFuzzySet(&noHeat);
  fuzzyOutput.addFuzzySet(&comfort);
  fuzzyOutput.addFuzzySet(&discomfort);
  fuzzyOutput.addFuzzySet(&caution);
  fuzzyOutput.addFuzzySet(&dangerous);
  fuzzyOutput.addFuzzySet(&hazardous);

  return fuzzyOutput;
}


FuzzyRuleAntecedent crt_antecedent_cold()
{
  FuzzyRuleAntecedent antecedent = FuzzyRuleAntecedent();

  antecedent.joinSingle(&cold);

  return antecedent;
}


FuzzyRuleAntecedent crt_antecedent_cool()
{
  FuzzyRuleAntecedent antecedent = FuzzyRuleAntecedent();

  antecedent.joinSingle(&cool);

  return antecedent;
}


FuzzyRuleAntecedent crt_antecedent_warm_AndVeryDryToNormal()
{
  FuzzyRuleAntecedent antecedent      = FuzzyRuleAntecedent();
  FuzzyRuleAntecedent veryDryToDry    = FuzzyRuleAntecedent();
  FuzzyRuleAntecedent veryDryToNormal = FuzzyRuleAntecedent();

  veryDryToDry.joinWithOR    (&veryDry,      &dry);
  veryDryToNormal.joinWithOR (&veryDryToDry, &normal);
  antecedent.joinWithAND     (&warm, &veryDryToNormal);

  return antecedent;
}


FuzzyRuleAntecedent crt_antecedent_warm_AndWetToVeryWet()
{
  FuzzyRuleAntecedent antecedent   = FuzzyRuleAntecedent();
  FuzzyRuleAntecedent wetToVeryWet = FuzzyRuleAntecedent();

  wetToVeryWet.joinWithOR (&wet,  &veryWet);
  antecedent.joinWithAND  (&warm, &wetToVeryWet);

  return antecedent;
}


FuzzyRuleAntecedent crt_antecedent_hot_AndVeryDryToDry()
{
  FuzzyRuleAntecedent antecedent   = FuzzyRuleAntecedent();
  FuzzyRuleAntecedent veryDryToDry = FuzzyRuleAntecedent();

  veryDryToDry.joinWithOR (&veryDry,  &dry);
  antecedent.joinWithAND  (&hot, &veryDryToDry);

  return antecedent;
}


FuzzyRuleAntecedent crt_antecedent_hot_AndNormal()
{
  FuzzyRuleAntecedent antecedent = FuzzyRuleAntecedent();
  antecedent.joinWithAND (&hot, &normal);

  return antecedent;
}


FuzzyRuleAntecedent crt_antecedent_hot_AndWetToVeryWet()
{
  FuzzyRuleAntecedent antecedent   = FuzzyRuleAntecedent();
  FuzzyRuleAntecedent wetToVeryWet = FuzzyRuleAntecedent();

  wetToVeryWet.joinWithOR (&wet,  &veryWet);
  antecedent.joinWithAND (&hot, &wetToVeryWet);

  return antecedent;
}


FuzzyRuleAntecedent crt_antecedent_veryHot_AndVeryDry()
{
  FuzzyRuleAntecedent antecedent = FuzzyRuleAntecedent();
  antecedent.joinWithAND (&veryHot, &veryDry);

  return antecedent;
}


FuzzyRuleAntecedent crt_antecedent_veryHot_AndDryToVeryWet()
{
  FuzzyRuleAntecedent antecedent   = FuzzyRuleAntecedent();
  FuzzyRuleAntecedent dryToNormal  = FuzzyRuleAntecedent();
  FuzzyRuleAntecedent dryToWet     = FuzzyRuleAntecedent();
  FuzzyRuleAntecedent dryToVeryWet = FuzzyRuleAntecedent();

  dryToNormal.joinWithOR  (&dry,         &normal );
  dryToWet.joinWithOR     (&dryToNormal, &wet    );
  dryToVeryWet.joinWithOR (&dryToWet,    &veryWet);
  antecedent.joinWithAND  (&veryHot,     &dryToVeryWet);

  return antecedent;
}


FuzzyRuleAntecedent crt_antecedent_scorching()
{
  FuzzyRuleAntecedent antecedent = FuzzyRuleAntecedent();
  antecedent.joinSingle(&scorching);

  return antecedent;
}


FuzzyRuleConsequent crt_consequent_noHeat()
{
  FuzzyRuleConsequent consequent = FuzzyRuleConsequent();
  consequent.addOutput(&noHeat);

  return consequent;
}


FuzzyRuleConsequent crt_consequent_comfort()
{
  FuzzyRuleConsequent consequent = FuzzyRuleConsequent();
  consequent.addOutput(&comfort);

  return consequent;
}


FuzzyRuleConsequent crt_consequent_discomfort()
{
  FuzzyRuleConsequent consequent = FuzzyRuleConsequent();
  consequent.addOutput(&discomfort);

  return consequent;
}


FuzzyRuleConsequent crt_consequent_caution()
{
  FuzzyRuleConsequent consequent = FuzzyRuleConsequent();
  consequent.addOutput(&caution);

  return consequent;
}


FuzzyRuleConsequent crt_consequent_dangerous()
{
  FuzzyRuleConsequent consequent = FuzzyRuleConsequent();
  consequent.addOutput(&dangerous);

  return consequent;
}


FuzzyRuleConsequent crt_consequent_hazardous()
{
  FuzzyRuleConsequent consequent = FuzzyRuleConsequent();
  consequent.addOutput(&hazardous);

  return consequent;
}


/**
 *  If
 *    - 
 *  Then
 *  
*/
FuzzyRule crt_rule1(FuzzyRuleAntecedent *antecedent, FuzzyRuleConsequent *consequent)
{
  FuzzyRule rule = FuzzyRule();


  return rule;
}


/**
 *  If
 *    - 
 *  Then
 *  
*/
FuzzyRule crt_rule2(FuzzyRuleAntecedent *antecedent, FuzzyRuleConsequent *consequent)
{
  FuzzyRule rule = FuzzyRule();


  return rule;
}


/**
 *  If
 *    - 
 *  Then
 *  
*/
FuzzyRule crt_rule3(FuzzyRuleAntecedent *antecedent, FuzzyRuleConsequent *consequent)
{
  FuzzyRule rule = FuzzyRule();


  return rule;
}


/**
 *  If
 *    - 
 *  Then
 *  
*/
FuzzyRule crt_rule4(FuzzyRuleAntecedent *antecedent, FuzzyRuleConsequent *consequent)
{
  FuzzyRule rule = FuzzyRule();


  return rule;
}


/**
 *  If
 *    - 
 *  Then
 *  
*/
FuzzyRule crt_rule5(FuzzyRuleAntecedent *antecedent, FuzzyRuleConsequent *consequent)
{
  FuzzyRule rule = FuzzyRule();


  return rule;
}


/**
 *  If
 *    - 
 *  Then
 *  
*/
FuzzyRule crt_rule6(FuzzyRuleAntecedent *antecedent, FuzzyRuleConsequent *consequent)
{
  FuzzyRule rule = FuzzyRule();


  return rule;
}


/**
 *  If
 *    - 
 *  Then
 *  
*/
FuzzyRule crt_rule7(FuzzyRuleAntecedent *antecedent, FuzzyRuleConsequent *consequent)
{
  FuzzyRule rule = FuzzyRule();


  return rule;
}


/**
 *  If
 *    - 
 *  Then
 *  
*/
FuzzyRule crt_rule8(FuzzyRuleAntecedent *antecedent, FuzzyRuleConsequent *consequent)
{
  FuzzyRule rule = FuzzyRule();


  return rule;
}


/**
 *  If
 *    - 
 *  Then
 *  
*/
FuzzyRule crt_rule9(FuzzyRuleAntecedent *antecedent, FuzzyRuleConsequent *consequent)
{
  FuzzyRule rule = FuzzyRule();


  return rule;
}


/**
 *  If
 *    - 
 *  Then
 *  
*/
FuzzyRule crt_rule10(FuzzyRuleAntecedent *antecedent, FuzzyRuleConsequent *consequent)
{
  FuzzyRule rule = FuzzyRule();


  return rule;
}

