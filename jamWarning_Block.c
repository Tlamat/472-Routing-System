//----------------------------------------------------------------------------
// AUTHORS:   Eric Lund and Jean Tenca
// CREATED:   July 16, 2008
// MODIFIED:  July 16, 2008
// PROJECT:   EE 471 Lab #2
// MODULE:    Jam warning block
//
// Abstract:  This module handles the situation where a jam has occured. It
//	      displays a written error message on the LED screen as well as 
//	      giving an aural warning via the Tern boards speaker.
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

#define OFF		1
#define ON		0

void jamWarning(void* data) {
	TaskDataJam* JamData = (TaskDataJam*)data;
   *(JamData->keypadInputPtr) = lcd_read();
   if(0 == *(JamData->errorStatePtr)) {
   	*(JamData->errorStatePtr) = 1;
  	   // Prints Error message to screen
      lcd_movecursor(0x80);
		lcd_fillrow(1, ' ');
      lcd_movecursor(0x80);
		lcd_putstr("Item Jam");
	   lcd_movecursor(0xc0);
  		lcd_putstr("Fire Missiles");
      // Sets Globals
      *(JamData->errorPtr) = TRUE;
      *(JamData->keypadInputPtr) = -1;
//      *(JamData->warnTimePtr) = 0;
      // Turns off LEDs
      outportb(0x0200,OFF);
      outportb(0x0201,OFF);
      outportb(0x0202,OFF);
		*(JamData->itemPresentPtr) = FALSE;
      *(JamData->inUsePtr) = FALSE;
   }

   // Run program until the user presses a key
	if(*(JamData->missilesFiredPtr)) {
      *(JamData->jamLeftPtr) = FALSE;
      *(JamData->jamRightPtr) = FALSE;
      *(JamData->jamFwdPtr) = FALSE;
      *(JamData->missilesPtr) = FALSE;
   	// Resets Globals
      *(JamData->errorStatePtr) = 0;
      *(JamData->errorPtr) = FALSE;
      // Clears Screen
      lcd_movecursor(0x80);
		lcd_fillrow(1, ' ');
    	lcd_movecursor(0xc0);
  		lcd_fillrow(2, ' ');
		lcd_movecursor(0x80);
      // Turns off alarm
      outportb(0x0203, OFF);
   } else {
   	if(1 == *(JamData->errorStatePtr)) {

			*(JamData->errorStatePtr) = 2;

     	}
      if(2 == *(JamData->errorStatePtr) &&
					((*(JamData->warnTimePtr)%1000) == 0)) {

			*(JamData->errorStatePtr) = 3;

     	} else if(3 == *(JamData->errorStatePtr) &&
      			((*(JamData->warnTimePtr)%2000) == 0)) {

			*(JamData->errorStatePtr) = 1;
//      	*(JamData->warnTimePtr) = 0;
      }
      // Moved to timer interrupt
      if (1 == *(JamData->errorStatePtr) || 2 == *(JamData->errorStatePtr)) {
      	if (0 == *(JamData->buzzerStatePtr)) {
        		outportb(0x0203,0);
        		*(JamData->buzzerStatePtr) = 1;
        	} else {
        		outportb(0x0203,1);
        		*(JamData->buzzerStatePtr) = 0;
      	}
		}
	}
}