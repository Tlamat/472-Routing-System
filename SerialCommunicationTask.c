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

#define OFF 	0x13
#define ON     0x11

#define TASK7_PRIORITY		18
#define STACK_SIZE			1024

void far ParseTask(void* data);

void far SerialTask(void* data)
{

   char RXBuffer[75];
	char TXBuffer[75];
	char lenStr[5];
   char ackBuffer[5];
   char checksumRX[2];
   newBool ack;
   newBool nak;
	int TXPos = 0;
	int RXPos = 0;
   int TXSend = 0;
   int length = 0;
   int ackTry;
   int i = 0;
   int z = 0;
   int wrEN  = 0;     // write enable
   int checksum = 0;
   newBool rxFull = FALSE;

   while(1) {
		// Get data for serial communications
		TaskDataSerCom* SerData = (TaskDataSerCom*)data;

		serCount++;
      wrEN = 0;
      length = 0;
      RXPos = 0;
      TXPos = 0;
      TXSend = 0;
      ackTry = 0;
      checksum = 0;
      ack = FALSE;
      nak = FALSE;

      // If we are Recieving
      if(serhit1(*(SerData->cPtr))) {
//			while(!ack && ackTry < 4) {
				while(serhit1(*(SerData->cPtr)) && RXPos < 75){
   		     	*(SerData->recievePtr) = TRUE;
					RXBuffer[RXPos] = getser1(*(SerData->cPtr));

	         	if(RXPos == 70) {
						// Send OFF to parse task
	   	        	*(SerData->frameTextPtr) = OFF;
					*(SerData->transmitPtr) = TRUE;
						rxFull = TRUE;
      	   	}

	         	if(RXPos <= 50 && rxFull) {
   	      		*(SerData->frameTextPtr) = ON;
				*(SerData->transmitPtr) = TRUE;
	   	         rxFull = FALSE;
   	   	   }                

	      		RXPos = RXPos + 1;

					// If you get a carriage return
      		   if(RXBuffer[RXPos-1] == '\n') {
	      		   // get length
            		sprintf(lenStr,"%c%c%c%c",RXBuffer[1], RXBuffer[2], RXBuffer[3], RXBuffer[4]);
	            	// length ATOI not working if Hex digit..works fine for Decimel
	   	         length = atoi(lenStr);
						// Extract Payload
      	   	   for(i = 0; i < length-6;i++) {
							// Put payload into a buffer
							*(SerData->aRXBufferPtr) = RXBuffer[i+5];
	//          	    	RXBuffer[i+5] = NULL;
   	            	*(SerData->aRXBposPtr) = *(SerData->aRXBposPtr) + 1;
	      			}
						RXPos = 0;
                  /*
      	      	// Handshake
         	      for(i=length-1;i<length+1;i++) {
	         	      checksumRX[i-(length-1)] = RXBuffer[i];
               	}
	               //checksumRX[2] = '\0';

		            for(i = 0;i<length-1;i++) {
   		         	checksum = (char)checksum ^ (char)RXBuffer[i];
      		      }

            	   ackBuffer[0] = 0x01;
               	ackBuffer[2] = 1;
	               ackBuffer[3] = 0x0A;
   	      	   if(atoi(itoa(checksum,NULL,16)) == atoi(checksumRX)) {
      	      		// send ack
         	         ackBuffer[1] = 0x06;
            	      ack = TRUE;
               	   nak = FALSE;
		            } else {
   		         	// send nak
      	            ackBuffer[1] = 0x15;
         	         nak = TRUE;
            	      ack = FALSE;
               	   ackTry++;
	         	   }
   	            wrEN = inport(0xFF12);        // "...get serial port status..."
      	         for(i = 0;i<4;i++) {
							if( (wrEN>>6) & 1) { 			// "if permission bit is 1..."
								outport(0xFF14, ackBuffer[i]);   //"write the next char..."
								ackBuffer[i] = NULL;
  							}
	               }*/
   				}
      	   }
      	//}
	   }

      if(*(SerData->recievePtr)) {
      	OSTaskCreate(ParseTask, (void*)&*(SerData->ParseTaskDataPtr), (void*)&(SerData->Task7StkPtr)[STACK_SIZE-1], TASK7_PRIORITY);
         clean_ser1(*(SerData->cPtr));
         ack = FALSE;
	      nak = FALSE;
   	   ackTry = 0;
         i = 0;
         while(RXBuffer[i] != NULL) {
         	RXBuffer[i] = NULL;
            i++;
         }
         i = 0;
      }


   	// Transmitting
      if(*(SerData->transmitParsedPtr) && *(SerData->initialPtr)) {
         ackTry = 0;
			// get chars from aTXbufferptr and put chars into transmit buffer
			while(*(SerData->aTXBufferPtr+TXPos) != NULL) {
				TXBuffer[TXPos] = *(SerData->aTXBufferPtr+TXPos);
				*(SerData->aTXBufferPtr+TXPos) = NULL;
				TXPos = TXPos + 1;
           	*(SerData->aTXBposPtr) = *(SerData->aTXBposPtr) - 1;
        	}

			// transmit to serial port
         if(75 == TXPos || *(SerData->aTXBposPtr) < 0) {
//				while(!ack && ackTry < 4) {
   	         nak = FALSE;
					TXSend = TXPos;
         	   TXPos = 0;
	        		while (TXSend > 0) {
						wrEN = inport(0xFF12);        // "...get serial port status..."
						if( (wrEN>>6) & 1) { 			// "if permission bit is 1..."
							outport(0xFF14, TXBuffer[TXPos]);   //"write the next char..."
//							TXBuffer[TXPos] = NULL;
            	      TXPos++;
  			  				TXSend = TXSend - 1;              //"increment to the next char"
	  					}
					}
      	     	// End Writing, Ack Check
/*         	   while(!ack && !nak) {
		      	   while(!serhit1(*(SerData->cPtr)));		// wait for response

	   	        	while(serhit1(*(SerData->cPtr))){
   	   		  		ackBuffer[z] = getser1(*(SerData->cPtr));
      	   	 		z++;
         	  		}
		      	   z = 0;
   		      	if(ackBuffer[1] == 0x06) {
	      		     	ack = TRUE;
   	      	   } else if(ackBuffer[1] == 0x15) {
      	      		nak = TRUE;
         	   	   ackTry = ackTry + 1;
	         	   }
//           		ackTry = ackTry + 1;
					 	if(ackTry > 3) {
   			        	// Transmit Error - Re-initialize
      			      lcd_movecursor(0x80);
//				  			lcd_fillrow(1, ' ');
//            	   	lcd_movecursor(0x80);
	            	  	lcd_putstr("Re-initialize Serial Port");
			         }
					}
				}  */
	  	   }

			if(*(SerData->transmitParsedPtr)) {
 				*(SerData->transmitParsedPtr) = FALSE;
	  	      *(SerData->aTXBposPtr) = 0;
            ackTry = 0;
            ack = FALSE;
		 	}

      	*(SerData->idErrorPtr) = FALSE;
	  	   *(SerData->sizeErrorPtr) = FALSE;
   	}
//      OSSchedUnlock();
		OSTimeDly(5);
	}
//   return;
}
