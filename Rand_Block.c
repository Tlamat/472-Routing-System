//----------------------------------------------------------------------------
// AUTHOR:    Jered Aasheim
// CREATED:   September 8, 2000
// MODIFIED:  July 16, 2008 - Display section removed
// PROJECT:   EE 471 Lab #2
// MODULE:    Random integer generator
//
// Abstract:  This module accepts a high and low int and returns a random
//	      integer between the given values.
//----------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include "boolean.h"
#include "td40.h"
#include "TCB_Data_Structs.h"

int seed = 1;

int randomInteger(int low, int high)
{
	double randNum = 0.0;
 	int multiplier = 2743;
	int addOn = 5923;
	double max = INT_MAX + 1.0;

	if (low > high)
		return randomInteger(high, low);
	else {
   	seed = seed*multiplier + addOn;
   	randNum = seed;

		if (randNum < 0)
			randNum = randNum + max;
      randNum = randNum/max;
      return ((int)((high-low+1)*randNum))+low;
   }
}