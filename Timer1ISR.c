#include <string.h>
#include <dos.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <string.h>
#include "boolean.h"
#include "ucos.h"
#include "td40.h"
#include "TCB_Data_Structs.h"

#define ON				0
#define OFF				1

extern int PwdPeriod;
extern int PwdTimer;
extern int PwdOffTime;
void interrupt far Timer1_ISR(void);

// Reaches this interrupt when Timer1 hits its high count
void interrupt far Timer1_ISR(void)
{
   if(PwdTimer >= 200) {
   	PwdTimer = 0;
      t1_init(0xE003,PwdOffTime * 10000,(PwdPeriod * 10000) - (PwdOffTime * 10000),Timer1_ISR);
   }

   if(PwdTimer >= PwdOffTime) {
	 	// Send Off to the Motor
   	outportb(0x0206,OFF);
   } else if(PwdTimer < PwdOffTime){
   	outportb(0x0206,ON);
   }
   // EOI
   outport(0xFF22,0x8000);
}

