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
 *       - Very dry       0   - 20    |   0   :   0   :   20  :   20
 *       - Dry            20  - 40    |   20  :   40  :   40  :   50
 *       - Normal         40  - 60    |   40  :   50  :   50  :   60
 *       - Wet            50  - 70    |   50  :   60  :   60  :   70
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
** Main
**
** =============================================== */


void setup() 
{
  Log_init();
  DHT_init();
}


void loop() 
{
  DHT_upd();
}