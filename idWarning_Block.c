//----------------------------------------------------------------------------
// AUTHORS:   Eric Lund and Jean Tenca
// CREATED:   July 16, 2008
// MODIFIED:  July 16, 2008
// PROJECT:   EE 471 Lab #2
// MODULE:    ID warning block
//
// Abstract:  This block handles the case of an identification warning. It
//				  flashes the red LED and waits for the user to press a key on
//				  the touchpad.
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

#define ON		0
#define OFF		1

void interrupt far Interval_ISR(void);

void idWarning(void* data) {
	TaskDataWarn* idData = (TaskDataWarn*)data;
   *(idData->keypadInputPtr) = lcd_read();
   if(0 == *(idData->errorStatePtr)) {
//    	*(idData->warnTimePtr) = 0;
	   *(idData->errorStatePtr) = 1;
   	// Prints Error Message to screen
      lcd_movecursor(0x80);
		lcd_fillrow(1, ' ');
      lcd_movecursor(0x80);
		lcd_putstr("Incorrect Item ID");
	   lcd_movecursor(0xc0);
		lcd_putstr("Press key to continue");
      *(idData->keypadInputPtr) = -1;
      // Turns off LEDs
      outportb(0x0200,OFF);
      outportb(0x0201,OFF);
      outportb(0x0202,OFF);
      *(idData->inUsePtr) = FALSE;
      *(idData->itemPresentPtr) = FALSE;
      //int6_init(0,Interval_ISR);
   }

   // Run program until the user presses a key
	if(-1 != *(idData->keypadInputPtr)) {
   	// Resets Globals
   	*(idData->errorPtr) = FALSE;
      *(idData->itemPresentPtr) = FALSE;
      *(idData->errorStatePtr) = 0;
      // Clears Screen
    	lcd_movecursor(0xc0);
  		lcd_fillrow(2, ' ');
		lcd_movecursor(0x80);
      // Turns off LED
      outportb(0x0202,OFF);
	} else {
	   // Toggle Red LED on 1 sec, off 1 sec, on 1 sec, off 2 sec
		if(1 == *(idData->errorStatePtr)) {
			outportb(0x0202,ON);
   	   *(idData->errorStatePtr) = 2;
		}
      if(2 == *(idData->errorStatePtr) &&
      	(*(idData->warnTimePtr) >= 1000)){

			outportb(0x0202,OFF);
     		*(idData->errorStatePtr) = 3;

		} else if(3 == *(idData->errorStatePtr) &&
			(*(idData->warnTimePtr) >= 2000)) {

			outportb(0x0202,ON);
     		*(idData->errorStatePtr) = 4;

     	} else if(4 == *(idData->errorStatePtr) &&
      	(*(idData->warnTimePtr) >= 3000)) {

			outportb(0x0202,OFF);
         *(idData->errorStatePtr) = 5;

      } else if(5 == *(idData->errorStatePtr) &&
      	(*(idData->warnTimePtr) >= 5000)) {

			*(idData->errorStatePtr) = 1;
//         *(idData->warnTimePtr) = 0;
      }
	}
}