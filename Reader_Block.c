//----------------------------------------------------------------------------
// AUTHORS:   Eric Lund and Jean Tenca
// CREATED:   July 16, 2008
// MODIFIED:  July 16, 2008
// PROJECT:   EE 471 Lab #2
// MODULE:    Reader Task
//
// Abstract:  This module generates the item size, identification tag, and a
//	      	  direction.
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

#define sizeFail 1
#define idFail 1

// Prototype
int randomInteger(int low, int high);
extern itemPresent;
extern readCount;

void far ReaderTask(void* data)
{
	int itemSize,temp,i,itemDirection;

	while(1)
	{
		TaskDataRead* ReadData = (TaskDataRead*)data; // Get data for Reading
//      OSSchedLock();
		readCount++;
		if(0 == (*(ReadData->delayTimePtr)%5000) && 0 == *(ReadData->jamStatePtr) && !itemPresent) {

		   // Set and Get local variables
	  		itemSize = randomInteger(sizeFail,15);
  			temp = 0;
			i = 0;

			// Set direction from randomly generated number
			// 0 = Left, 1 = Forward, 2 = Right
			itemDirection = randomInteger(0,2);

			if (0 == itemDirection) {
				*(ReadData->LeftPtr) = TRUE;
            *(ReadData->RightPtr) = FALSE;
            *(ReadData->FwdPtr) = FALSE;
			} else if (1 == itemDirection) {
				*(ReadData->FwdPtr) = TRUE;
            *(ReadData->LeftPtr) = FALSE;
            *(ReadData->RightPtr) = FALSE;
			} else if (2 == itemDirection) {
				*(ReadData->RightPtr) = TRUE;
            *(ReadData->LeftPtr) = FALSE;
            *(ReadData->FwdPtr) = FALSE;
			}

			// Get item size from randomly generated number
			while (0 == itemSize) {
				itemSize = randomInteger(sizeFail,15);
			}

			*(ReadData->itemSizePtr) = itemSize;

			for(i = 0; i < 8 ; i++){

				if (0 == i) {
					temp = randomInteger(idFail, 15);
				} else {
					temp = randomInteger(0, 15);
				}

				if (temp < 0) {
					*(ReadData->itemIDPtr+i) = '-';
				} else if (temp > -1 && temp < 10) {
					*(ReadData->itemIDPtr+i) = temp + '0';
				} else if (temp > 9) {
					*(ReadData->itemIDPtr+i) = 'a' + temp - 10;
				}
			}

			*(ReadData->itemIDPtr+8) = '\0'; 					// Prints ID as a string
			// Sets ID to Global Variable
			//*(ReadData->itemIDPtr) = identificationChar;
			*(ReadData->systemReadyPtr) = TRUE;
		}
//      OSSchedUnlock();
		OSTimeDly(5);
	}
	//return;
}