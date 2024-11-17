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

extern ParseBufferRX[150];
extern int Seq_Num;

void CFrame(newBool ack) {
	int CFrame[5];
   int i = 0;

   CFrame[0] = 0x01;

   if(ack) {
   	CFrame[1] = 0x06;
   } else {
   	CFrame[1] = 0x15;
   }

   Seq_Num = (Seq_Num + 0x01)%8;
   CFrame[2] = Seq_Num;

	CFrame[3] = 0x0A;

   for(i=0;i<4;i++) {
   	ParseBufferRX[i] = CFrame[i];
   }
}
