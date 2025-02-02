#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <string.h>
#include "boolean.h"
#include "td40.h"
#include "TCB_Data_Structs.h"

#define BUFFSIZE		2000		

extern char line[50];
extern newBool jamRight;
extern newBool jamLeft;
extern newBool jamFwd;

void interrupt far jamAq_ISR()
{
//   int s0 = pio_rd(29);
//   int s1 = pio_rd(9);

	int s = pio_rd(0);
	s = s & 0x3;

   if(s == 3) {
    	sprintf(line,"Right");
		jamRight = TRUE;
	} else if(s == 1) {
    	sprintf(line,"Left");
      jamLeft = TRUE;
	} else if(s == 2) {
    	sprintf(line,"Forward");
      jamFwd = TRUE;
	} else {
		sprintf(line,"False Alarm");
	}
   // EOI
   outport(0xFF22,0x8000);
}

