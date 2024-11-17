//----------------------------------------------------------------------------
// AUTHORS:   Eric Lund and Jean Tenca
// CREATED:   July 16, 2008
// MODIFIED:  July 16, 2008
// PROJECT:   EE 471 Lab #2
// MODULE:    Routing Task
//
// Abstract:  This module checks for any errors such as jams or a bad id tag.
//	      If there are no errors, the id tag, direction, and time to
//	      destination are displayed. Once done, the module clears the TERN
//	      board and resets the variables for the next loop.
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

#define TASK7_PRIORITY     18
#define STACK_SIZE			1024

// Prototypes
int randomInteger(int low, int high);
void jamWarning(void* data);
void idWarning(void* data);
void sizeWarning(void* data);
//void far SerialTask(void* data);
void far ParseTask(void* data);


void far RoutingTask(void* data){

   char ID [9];
//   char dirStr[40];
//   char idStr[40];
//   char sizeStr[40];
//   char jamStr[40];

   while(1) {

		TaskDataRout* RoutData = (TaskDataRout*)data;	// Get data for Routing
      OSSchedLock();
 		routCount++;
		if(!*(RoutData->inUsePtr)) {

   		// If item is present
			if(*(RoutData->itemPresentPtr)) {
				// Set and Get Variables
				int size = *(RoutData->itemSizePtr);
            int i = 0;

//            char* IDtemp = NULL;

				int itemDirection = NULL;
				int time = randomInteger(1,15);

				*(RoutData->displayTimePtr) = time * 1000;
	    		*(RoutData->inUsePtr) = TRUE;


	         // Set ID
				for(i = 0; i < 9; i++) {
           		ID[i] = *(RoutData->itemIDPtr+i);
	         }

   	      if(*(RoutData->LeftPtr)) {
					itemDirection = 0;
               *(RoutData->itemDirectionPtr) = 'L';
               *(RoutData->itemDirectionPtr+1) = 'F';
				} else if(*(RoutData->FwdPtr)) {
					itemDirection = 1;
               *(RoutData->itemDirectionPtr) = 'F';
               *(RoutData->itemDirectionPtr+1) = 'W';
				} else if(*(RoutData->RightPtr)) {
					itemDirection = 2;
               *(RoutData->itemDirectionPtr) = 'R';
               *(RoutData->itemDirectionPtr+1) = 'T';
      	   }

	      	// Indicates there is an error with the item size
				if(size < 0) {

					*(RoutData->sizeErrorPtr) = 1;
               if(*(RoutData->dataLogPtr)) {
						*(RoutData->transmitPtr) = TRUE;
   		         *(RoutData->aCommandPtr) = TRUE;
               }
               (RoutData->frameTextPtr) = "size";
					// Tell Scheduler to put serial communication in queue
					OSTaskCreate(ParseTask, (void*)&*(RoutData->ParseTaskDataPtr), (void*)&(RoutData->Task7StkPtr)[STACK_SIZE-1], TASK7_PRIORITY);

	            // Reset Variables
					*(RoutData->displayTimePtr) = 0;
					*(RoutData->inUsePtr) = FALSE;
         	   *(RoutData->aCommandPtr) = TRUE;
					// Call warning function
					sizeWarning(RoutData->SizeDataPtr);

					// Indicates there is an error with the ID
				} else if('-' == ID[0]) {
					// Send Data to Serial Communications
					// ID
	//				IDtemp = ID;
					*(RoutData->linePtr) = randomInteger(0,10) + 'a';
					for(i = 1;i<4;i++) {
						*(RoutData->linePtr + i) = randomInteger(0,9) + '0';
					}
					*(RoutData->linePtr+5) = '\0';

					*(RoutData->idErrorPtr) = 1;
               if(*(RoutData->dataLogPtr)) {
						*(RoutData->transmitPtr) = TRUE;
   		         *(RoutData->aCommandPtr) = TRUE;
               }
					// Tell Scheduler to put parse and serial communication in queue

//					OSTaskCreate(ParseTask, (void*)&*(RoutData->ParseTaskDataPtr), (void*)&(RoutData->Task7StkPtr)[STACK_SIZE-1], TASK7_PRIORITY);


					// Reset Variables
					*(RoutData->displayTimePtr) = 0;
					*(RoutData->inUsePtr) = FALSE;
            	*(RoutData->aCommandPtr) = TRUE;
					// Call warning function
					idWarning(RoutData->IdDataPtr);

					// Indicates there is a jam
				} else if(*(RoutData->jamPresentPtr)) {

					if(*(RoutData->dataLogPtr)) {
						*(RoutData->transmitPtr) = TRUE;
   		         *(RoutData->aCommandPtr) = TRUE;
               }

					// Tell Scheduler to put Parse in queue
					OSTaskCreate(ParseTask, (void*)&*(RoutData->ParseTaskDataPtr), (void*)&(RoutData->Task7StkPtr)[STACK_SIZE-1], TASK7_PRIORITY);

					// Reset Direction and display time
					*(RoutData->displayTimePtr) = 0;
					*(RoutData->inUsePtr) = FALSE;
	            *(RoutData->aCommandPtr) = TRUE;

					jamWarning(RoutData->JamDataPtr);

					// Prints ID, Direction, and Time to the screen
				} else {
					// Print to LCD
					lcd_movecursor(0x80);
					lcd_fillrow(1, ' ');
					lcd_movecursor(0xc0);
					lcd_fillrow(1, ' ');
            	lcd_movecursor(0x80);

	            lcd_putstr(ID);
					lcd_put(' ');
					lcd_putstr(itoa(itemDirection,NULL,10));
					lcd_put(' ');
			  		lcd_putstr(itoa(time,NULL,10));

               if(*(RoutData->dataLogPtr)) {
						*(RoutData->transmitPtr) = TRUE;
   		         *(RoutData->mCommandPtr) = TRUE;
               }
					OSTaskCreate(ParseTask, (void*)&*(RoutData->ParseTaskDataPtr), (void*)&(RoutData->Task7StkPtr)[STACK_SIZE-1], TASK7_PRIORITY);

				}
			}
      }
		if(*(RoutData->jamPresentPtr) > 0) {
			jamWarning(RoutData->JamDataPtr);
		}
		if(*(RoutData->idStatePtr) > 0) {
  			idWarning(RoutData->IdDataPtr);
		}
		if(*(RoutData->sizeStatePtr) > 0) {
  			sizeWarning(RoutData->SizeDataPtr);
		}

		if ((*(RoutData->displayTimePtr) <= *(RoutData->delayTimePtr)) && *(RoutData->itemPresentPtr)) {
			// Reset the system for next package
	   	// Reset Global Variables
			*RoutData->itemPresentPtr = FALSE;
			*RoutData->inUsePtr = FALSE;
		    // Reset the screen
			lcd_movecursor(0x80);
			lcd_fillrow(1, ' ');
			lcd_movecursor(0x80);
			// Reset LEDs
			outportb(0x0200,1);
			outportb(0x0201,1);
			outportb(0x0202,1);
		} 
      OSSchedUnlock();
      OSTimeDly(5);
   }
//	return;
}
