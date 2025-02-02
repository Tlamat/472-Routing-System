#include <string.h>
#include <dos.h>
#include <stdlib.h>
#include <math.h>
#include "boolean.h"
#include "ucos.h"
#include "td40.h"
#include "TCB_Data_Structs.h"

#define t2count		5
#define PwdPeriod		200
#define ON				0
#define OFF				1			


extern int delayTime;
//extern int intervalTimer;
extern newBool itemPresent;
extern int PwdTimer;

void interrupt far Timer2_ISR(void)
{
	// delayTime global counter, 0-5 seconds
	// t2count is the time timer 2 runs for
	delayTime = delayTime + t2count;
	PwdTimer = PwdTimer + t2count;
//   intervalTimer = intervalTimer + t2count;

	if(0 == delayTime%5000 && itemPresent == FALSE) {
		delayTime = 0;
	}
  	// Issue EOI
   outport(0xFF22, 0x8000);
}