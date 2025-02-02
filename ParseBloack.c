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

int randomInteger(int,int);
void buildIFrame(void*);


void far ParseTask(void* data) {

	while(1) {

		TaskDataParse* ParseData = (TaskDataParse*)data;
		int i = 0;
		newBool badID = FALSE;

		// recieving
		if(*(ParseData->recievedMsgPtr)) {
			// verifty command
			if(*(ParseData->commandPtr) == 'I' ||
         									    'S' ||
								                'P' ||
                        					 'D' ||
 								                'M' ||
                        					 'A') {
				// pass to command task
				*(ParseData->commandBufferPtr) = (ParseData->commandPtr)[0];
			} else {
				(ParseData->commandBufferPtr)[0] = '\0';
				*(ParseData->frameTextPtr) = 'E';
      	   buildIFrame(ParseData->frameDataPtr);
   	      *(ParseData->transmitParsedPtr) = TRUE;
			}
      	*(ParseData->recievedMsgPtr) = FALSE;
		}

	   // transmitting
   	if(*(ParseData->transmitPtr)) {
	      // Build M Response
    		if(*(ParseData->mCommandPtr)) {
				// M
	         *(ParseData->frameTextPtr) = 'M';
         	// SP
      	 	*(ParseData->frameTextPtr+1) = 0x20;
   	      // Field 0 - Temperature Data
	         for(i = 2; i<6;i++) {
         	 	*(ParseData->frameTextPtr+i) = (randomInteger(0,9) + '0');
      	   }
				// Field 1 - Identification
	         for(i = 6;i<14;i++) {
         	  	*(ParseData->frameTextPtr+i) = *(ParseData->itemIdentificationPtr+i-6);
      	   }
				// Field 2 - Size
	         if(*(ParseData->itemSizePtr) > 9) {
					// 10s digit
	      	  	*(ParseData->frameTextPtr+14) = (*(ParseData->itemSizePtr)>>1) + '0';
      	      // 1s digit
   		      *(ParseData->frameTextPtr+15) = (*(ParseData->itemSizePtr) - 10) + '0';
				} else if(*(ParseData->itemSizePtr) <= 9) {
            	// 10s digit
					*(ParseData->frameTextPtr+14) = '0';
      	      // 1s digit
   		      *(ParseData->frameTextPtr+15) = *(ParseData->itemSizePtr) + '0';
				}
         	// Field 3 - Direction
      	   for(i = 16;i<18;i++) {
   	        	*(ParseData->frameTextPtr+i) = *(ParseData->itemDirectionPtr+i-16);
	         }
         	*(ParseData->mCommandPtr) = FALSE;
      	}

   	   // Build A response
	      if(*(ParseData->aCommandPtr)) {
				// SP
	   	  	*(ParseData->frameTextPtr+1) = 0x20;
				// Field 0 - Jam Status
	   		/*for(i=2;i<4;i++) {
					*(ParseData->frameTextPtr+i) = *(ParseData->jamStatusPtr+i-2);
	   	   } */
   		   if(*(ParseData->jamPresentPtr)) {
	      	 	*(ParseData->frameTextPtr+2) = 'J';
					*(ParseData->frameTextPtr+3) = 'P';
		   	} else {
					*(ParseData->frameTextPtr+2) = 'N';
   			   *(ParseData->frameTextPtr+3) = 'O';
		      }

   		   // Field 1 - Jam Line Info
   	  		for(i=4;i<7;i++) {
		      	if(*(ParseData->jamPresentPtr)) {
		     			*(ParseData->frameTextPtr+i) = *(ParseData->linePtr+i-4);
   	   	 	} else {
	  					*(ParseData->frameTextPtr+i) = NULL;
   	      	}
			   }
   	 		// Field 2 - Jam Line Direction
   			for(i=7;i<9;i++) {
			     	if(*(ParseData->jamPresentPtr)) {
	   	   		*(ParseData->frameTextPtr+i) = *(ParseData->itemDirectionPtr+i-7);
	   			} else {
	      		  	*(ParseData->frameTextPtr+i) = NULL;
	   	    	}
   		  	}
		  	   // Field 3 - Bad Identification
				/*for(i=9;i<11;i++) {
     			 	*(ParseData->aResponsePtr+i) = *(ParseData->badIdStatus+i-9);
		  	   }*/
				if(*(ParseData->idErrorPtr)) {
   				*(ParseData->frameTextPtr+9) = 'B';
   		   	*(ParseData->frameTextPtr+10) = 'I';
		  	      badID = TRUE;
	   	   } else {
					*(ParseData->frameTextPtr+9) = 'N';
     		   	*(ParseData->frameTextPtr+10) = 'O';
		  	      badID = FALSE;
	   	   }
     			// Field 4 - Bad ID Value
	  		   for(i = 11;i < 19; i++) {
   		      if(badID) {
	      			*(ParseData->frameTextPtr+i) = *(ParseData->itemIdentificationPtr+i-11);
        			} else {
	     		      *(ParseData->frameTextPtr+i) = NULL;
  			      }
  		   	}
				//for(i = 0;i<19;i++) {
	      	 //  *(ParseData->ParseBufferTXPtr+i) = *(ParseData->frameTextPtr+i);
      	   //}
   	      *(ParseData->aCommandPtr) = FALSE;
	      }
      	// Build Control Frame
   	   buildIFrame(ParseData->frameDataPtr);
	      *(ParseData->transmitParsedPtr) = TRUE;
      	*(ParseData->transmitPtr) = FALSE;
		}
	   OSTimeDly(5);
   }
//   return;
}
