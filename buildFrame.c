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


void buildIFrame(void* data) {

   TaskDataFrame* IFdata = (TaskDataFrame*)data;

   char* lengthStr;
   char* checkStr;
	int i = 0;
   int x = 0;
   int length = 0;
   int check = 0;
   // Start
   *(IFdata->aTXBufferPtr) = 0x01;
   check = (char)check ^ (char)*(IFdata->aTXBufferPtr+i);
   // Length
   length = 6 + strlen((IFdata->textPtr));
   lengthStr = itoa(length,NULL,16);
   if(strlen(lengthStr) == 1) {
      for(i=1;i<4;i++){
			*(IFdata->aTXBufferPtr+i) = '0';
         check = (char)check ^ (char)*(IFdata->aTXBufferPtr+i);
         x = i+1;
      }
   } else if(strlen(lengthStr) == 2) {
      for(i=1;i<3;i++){
			*(IFdata->aTXBufferPtr+i) = '0';
         check = (char)check ^ (char)*(IFdata->aTXBufferPtr+i);
         x = i+1;
      }
   } else if(strlen(lengthStr) == 3) {
		i = 1;
		*(IFdata->aTXBufferPtr+i) = '0';
      check = (char)check ^ (char)*(IFdata->aTXBufferPtr+i);
      i++;
      x = i+1;
   }
   for(i=x;i<5;i++) {
      *(IFdata->aTXBufferPtr+i) = (char)lengthStr[i-x];
      check = (char)check ^ (char)*(IFdata->aTXBufferPtr+i);
   }

   // Text
   for(i = 5;i<strlen((IFdata->textPtr))+5;i++) {
   	*(IFdata->aTXBufferPtr+i) = (char)*(IFdata->textPtr+i-5);
      check = (char)check ^ (char)*(IFdata->aTXBufferPtr+i);
   }

   // Check
   checkStr = itoa(check,NULL,16);
   for(i = strlen((IFdata->textPtr))+5;i<strlen((IFdata->textPtr))+5+2;i++) {
      if(checkStr[i-strlen((IFdata->textPtr))+5] != NULL) {
	   	*(IFdata->aTXBufferPtr+i) = (char)checkStr[i - (strlen((IFdata->textPtr))+5)];
      } else {
      	*(IFdata->aTXBufferPtr+i) = '0';
      }
   }

   // End
   *(IFdata->aTXBufferPtr+i) = 0x0A;
}
