#pragma once

#include <string.h>
#include <stdbool.h>
#include "Type_Info.h"



// This code was copied from https://stackoverflow.com/questions/4014827/how-can-i-compare-strings-in-c-using-a-switch-statement
// This code was made by stackoverflow user Andrea Carron.
/** Begin a switch for the string x */
// "ss" stands for "Switch String".
#define switch_s(string) \
  do \
  { \
    String ss_Value__ = string; \
    bool ss_Found_Case__ = false; if (true) {

#define case_s(value) \
  } if (strcmp(ss_Value__, value) == false) { ss_Found_Case__ = true;

#define icase_s(value) \
  } if (strcasecmp(ss_Value__, value) == false) { ss_Found_Case__ = true;

#define defualt_s \
  } if (ss_Found_Case__ == false) { 

#define switch_end_s \
  } } while(0)

  