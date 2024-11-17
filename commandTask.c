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

#define ON						0x11
#define TASK1_PRIORITY		11
#define STACK_SIZE			1024

void far interrupt jamAq_ISR(void);
void far interrupt IncreaseConv_ISR(void);
void far interrupt DecreaseConv_ISR(void);
void buildIFrame(void*);
void far ReaderTask(void*);

extern commandCount;
extern UWORD Task1_Stk[STACK_SIZE];
extern TaskDataRead ReaderTaskData;
extern serInBufPtr;
extern serOutBufPtr;

void far CommandTask(void* data) {
	while(1) {
		TaskDataCommand* ComdData = (TaskDataCommand*)data;
      commandCount++;
      if((ComdData->CommandBufferPtr)[0] != NULL) {
	      if(*(ComdData->CommandBufferPtr) == 'I') {
				// Initialize System
      	   *(ComdData->initialPtr) = TRUE;
            s1_init(baud, *(ComdData->serInBufPtr), BUFFSIZE, *(ComdData->serOutBuf), BUFFSIZE, *(ComdData->cPtr));
	      } else if(*(ComdData->CommandBufferPtr) == 'S') {
   	   	// Enable data Interrupts
      	   int4_init(1,jamAq_ISR);
         	int3_init(1,IncreaseConv_ISR);
			   int1_init(1,DecreaseConv_ISR);
            OSTaskCreate(ReaderTask, (void*)&*(ComdData->ReaderTaskDataPtr),(void*)&(ComdData->task1Stk)[STACK_SIZE-1],TASK1_PRIORITY);
			} else if(*(ComdData->CommandBufferPtr) == 'P') {
      		// Terminate tasks
         	// disable measurement/data interrupts
	         int4_init(0,jamAq_ISR);
   	      int3_init(0,IncreaseConv_ISR);
			   int1_init(0,DecreaseConv_ISR);
            OSTaskDel(TASK1_PRIORITY);
	      } else if(*(ComdData->CommandBufferPtr) == 'D') {
				// enable/disable data logging
				if(!*(ComdData->dataLoggingPtr)) {
		      	*(ComdData->dataLoggingPtr) = TRUE;
   	      } else if(*(ComdData->dataLoggingPtr)) {
      	   	*(ComdData->dataLoggingPtr) = FALSE;
	         }
            outport(0x205,1);
   	   } else if(*(ComdData->CommandBufferPtr) == 'M') {
      	   // Request Item Information
      		*(ComdData->mCommandPtr) = TRUE;
            *(ComdData->transmitPtr) = TRUE;
	      } else if(*(ComdData->CommandBufferPtr) == 'A') {
   	   	// Request status, warning, alarm info display
      	   *(ComdData->aCommandPtr) = TRUE;
            *(ComdData->transmitPtr) = TRUE;
	      }
      }
      (ComdData->CommandBufferPtr)[0] = NULL;
   	OSTimeDly(5);
   }
}


