//----------------------------------------------------------------------------
// AUTHORS:   Eric Lund and Jean Tenca
// CREATED:   July 16, 2008
// MODIFIED:  July 16, 2008
// PROJECT:   EE 471 Lab #2
// MODULE:    Directions block
//
// Abstract:  
//
//
//----------------------------------------------------------------------------

#include "boolean.h"
#include "ucos.h"
#include "td40.h"
#include "TCB_Data_Structs.h"
#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <string.h>

#define ON		0
#define OFF		1

extern fwdCount;
extern rightCount;
extern leftCount;

void far LeftTask(void* data)
{
   while(1) {

		TaskDataDir* LeftTaskPtr = (TaskDataDir*)data;  // Get the data for forward
    	if(*(LeftTaskPtr->systemReadyPtr)){
	         if(*(LeftTaskPtr->itemPresentPtr) == FALSE) {
				  	if(*(LeftTaskPtr->DirectionPtr)){             //If the package is moving fwd

					*(LeftTaskPtr->itemPresentPtr) = TRUE;	  // Item is present
					outportb(0x0200,ON);							  // Turn on Green LED
   		   	*(LeftTaskPtr->systemReadyPtr) = FALSE;
  				}
  	   	}
      }
      OSTimeDly(5);
   }
//	return;
}

void far FwdTask(void* data)
{
   while(1) {

		TaskDataDir* FwdTaskPtr = (TaskDataDir*)data;  // Get the data for forward
    	if(*(FwdTaskPtr->systemReadyPtr)){
	         if(*(FwdTaskPtr->itemPresentPtr) == FALSE) {
				  	if(*(FwdTaskPtr->DirectionPtr)) {             //If the package is moving fwd

						*(FwdTaskPtr->itemPresentPtr) = TRUE;	  // Item is present
						outportb(0x0201,ON);							  // Turn on Yellow LED
	   	      	*(FwdTaskPtr->systemReadyPtr) = FALSE;
//                  int6_init(1,Interval_ISR);
					}
  	   	  	}
      	}
      OSTimeDly(5);
   }
//	return;
}

void far RightTask(void* data)
{
	while(1) {

		TaskDataDir* RightTaskPtr = (TaskDataDir*)data;  // Get the data for Right
    	if(*(RightTaskPtr->systemReadyPtr)){
    	   if(*(RightTaskPtr->itemPresentPtr) == FALSE) {
				  	if(*(RightTaskPtr->DirectionPtr)){             //If the package is moving right

						*(RightTaskPtr->itemPresentPtr) = TRUE;	  // Item is present
						outportb(0x0202,ON);							  // Turn on Red LED
	   	      	*(RightTaskPtr->systemReadyPtr) = FALSE;
			  	}
  	     	}
      }
      OSTimeDly(5);
   }
//	return;
}
