#ifndef fuzzy_service_const_h
#define fuzzy_service_const_h


/* ==================================================
** Libraries
**
** =============================================== */


//


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
const int num_rules            = sizeof(consequents_value) / sizeof(consequents_value[0]);

#endif