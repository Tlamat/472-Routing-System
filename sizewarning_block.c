//----------------------------------------------------------------------------
// AUTHORS:   Eric Lund and Jean Tenca
// CREATED:   July 28, 2008
// MODIFIED:  July 28, 2008
// PROJECT:   EE 471 Lab #2
// MODULE:    Size warning block
//
// Abstract:  This block handles the case of an Size warning. It
//				  flashes the yellow LED and waits for the user to press a key on
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

void sizeWarning(void* data) {
	TaskDataWarn* sizeData = (TaskDataWarn*)data;
   *(sizeData->keypadInputPtr) = lcd_read();
   if(0 == *(sizeData->errorStatePtr)) {
//    	*(sizeData->warnTimePtr) = 0;
	   *(sizeData->errorStatePtr) = 1;
      *(sizeData->errorPtr) = TRUE;
   	// Prints Error Message to screen
      lcd_movecursor(0x80);
		lcd_fillrow(1, ' ');
      lcd_movecursor(0x80);
		lcd_putstr("Incorrect Item Size");
      lcd_movecursor(0xc0);
		lcd_putstr("Press key to continue");
      *(sizeData->keypadInputPtr) = -1;
      // Turns off LEDs
      outportb(0x0200,OFF);
      outportb(0x0201,OFF);
      outportb(0x0202,OFF);
      *(sizeData->inUsePtr) = FALSE;
      *(sizeData->itemPresentPtr) = FALSE;
      //int6_init(0,Interval_ISR);
   }

   // Run program until the user presses a key
	if(-1 != *(sizeData->keypadInputPtr)) {
		// Resets Globals
		*(sizeData->errorStatePtr) = 0;
		// Clears Screen
    	lcd_movecursor(0xc0);
  		lcd_fillrow(2, ' ');
		lcd_movecursor(0x80);
		// Turns off LED
		outportb(0x0201,1);
	} else {
		// Toggle Yellow LED on 2 sec, off 1 sec, on 2 sec, off 1 sec
		if(1 == *(sizeData->errorStatePtr)) {
			outportb(0x0201,ON);
			*(sizeData->errorStatePtr) = 2;
		}
      if(2 == *(sizeData->errorStatePtr) &&
      	(*(sizeData->warnTimePtr) >= 2000)){
			outportb(0x0201,OFF);
     		*(sizeData->errorStatePtr) = 3;
		} else if(3 == *(sizeData->errorStatePtr) &&
				 (*(sizeData->warnTimePtr) >= 3000)) {
			outportb(0x0201,ON);
     		*(sizeData->errorStatePtr) = 4;
     	} else if(4 == *(sizeData->errorStatePtr) &&
				 (*(sizeData->warnTimePtr) >= 5000)) {
			outportb(0x0201,OFF);
			*(sizeData->errorStatePtr) = 5;
		} else if(5 == *(sizeData->errorStatePtr) &&
				 (*(sizeData->warnTimePtr) >= 6000)) {
			*(sizeData->errorStatePtr) = 1;
//			*(sizeData->warnTimePtr) = 0;
		}
	}
}