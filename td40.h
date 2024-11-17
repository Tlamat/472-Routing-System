//***************************************************************************
//                                TD40.H
//***************************************************************************
//
// Created:  September 9, 2000
// Modified: November 29, 2000
//           October 1, 2001 - added defines for registers (tcorn)
// Module:   TD40 Evaluation Board API
//
// Notes:
//
// The following header file defines the interface for using the TD40.LIB
// library for accessing the peripheral components (A/D converter, D/A converter,
// serial port, onboard timers, etc.) on the TD40 evaluation board.
//
//***************************************************************************

/*  Defines for register offsets  */
/* Processor Control Registers */
#define	rRELREG			0xFFFE		/* Peripheral Control Block Relocation */
#define	rRESCON			0xFFF6		/* Reset Configuration */
#define	rPRL				0xFFF4		/* Processor Release Level */
#define	rAUXCON			0xFFF2		/* Auxiliary Configuration */
#define	rSYSCON			0xFFF0		/* Sytem Configuration */
#define	rWDTCON			0xFFE6		/* Watchdog Timer Control */
#define	rEDRAM			0xFFE4		/* Enable RCU */
#define	rCDRAM			0xFFE2		/* Clock Prescaler */
#define	rMDRAM			0xFFE0		/* Memory Partition */

/* DMA Registers */
#define  rD1CON			0xFFDA		/* DMA 1 Control */
#define	rD1TC				0xFFD8		/* DMA 1 Transfer Count */
#define	rD1DSTH			0xFFD6		/* DMA 1 Destination Address High */
#define	rD1DSTL			0xFFD4		/* DMA 1 Destination Address Low */
#define	rD1SRCH			0xFFD2		/* DMA 1 Source Address High */
#define	rD1SRCL			0xFFD0		/* DMA 1 Source Address Low */
#define  rD0CON			0xFFCA		/* DMA 0 Control */
#define	rD0TC				0xFFC8		/* DMA 0 Transfer Count */
#define	rD0DSTH			0xFFC6		/* DMA 0 Destination Address High */
#define	rD0DSTL			0xFFC4		/* DMA 0 Destination Address Low */
#define	rD0SRCH			0xFFC2		/* DMA 0 Source Address High */
#define	rD0SRCL			0xFFC0		/* DMA 0 Source Address Low */

/* Chip-Select Registers */
#define	rMPCS				0xFFA8		/* PCS and MCS Auxiliary */
#define	rMMCS				0xFFA6		/* Midrange Memory Chip Select */
#define	rPACS				0xFFA4		/* Peripheral Chip Select */
#define	rLMCS				0xFFA2		/* Low Memory Chip Select */
#define	rUMCS				0xFFA0		/* Upper Memory Select */

/* Serial Port 1 Registers */
#define	rSP1BAUD			0xFF18		/* Serial Port 1 Baud Rate Divisor */
#define	rSP1RD			0xFF16		/* Serial Port 1 Receive Data */
#define	rSP1TD			0xFF14		/* Serial Port 1 Transmit */
#define	rSP1STS			0xFF12		/* Serial Port 1 Status */
#define	rSP1CT			0xFF10		/* Serial Port 1 Control */

/* Serial Port 0 Registers */
#define	rSP0BAUD			0xFF88		/* Serial Port 0 Baud Rate Divisor */
#define	rSP0STS			0xFF82		/* Serial Port 0 Status */
#define	rSP0CT			0xFF80		/* Serial Port 0 Control */

/* PIO Registers */
#define	rPDATA1			0xFF7A		/* PIO Data 1 */
#define	rPDIR1			0xFF78		/* PIO Direction 1 */
#define	rPIOMODE1		0xFF76		/* PIO Mode 1 */
#define	rPDATA0			0xFF74		/* PIO Data 0 */
#define	rPDIR0			0xFF72		/* PIO Direction 0 */
#define	rPIOMODE0		0xFF70		/* PIO Mode 0 */

/* Timer Registers */
#define	rT2CON			0xFF66		/* Timer 2 Mode and Control */
#define	rT2CMPA			0xFF62		/* Timer 2 Maxcount Compare A */
#define	rT2CNT			0xFF60		/* Timer 2 Count */
#define	rT1CON			0xFF5E		/* Timer 1 Mode and Control */
#define	rT1CMPB			0xFF5C		/* Timer 1 Maxcount Compare B */
#define	rT1CMPA			0xFF5A		/* Timer 1 Maxcount Compare A */
#define	rT1CNT			0xFF58		/* Timer 1 Count */
#define	rT0CON			0xFF56		/* Timer 0 Mode and Control */
#define	rT0CMPB			0xFF54		/* Timer 0 Maxcount Compare B */
#define	rT0CMPA			0xFF52		/* Timer 0 Maxcount Compare A */
#define	rT0CNT			0xFF50		/* Timer 0 Count */

/* Interrupt Registers */
#define	rSP0CON			0xFF44		/* Serial Port 0 Interrupt Control */
#define	rSPICON			0xFF42		/* Serial Port Interrupt Control */
#define	rINT4				0xFF40		/* INT4 Control */
#define	rINT3				0xFF3E		/* INT3 Control */
#define	rINT2				0xFF3C		/* INT2 Control */
#define	rINT1				0xFF3A		/* INT1 Control */
#define	rINT0				0xFF38		/* INT0 Control */
#define	rDMA1CON			0xFF36		/* DMA 1 Interrupt Control */
#define	rDMA0CON			0xFF34		/* DMA 0 Interrupt Control */
#define	rTCUCON			0xFF32		/* Timer Interrupt Control */
#define	rT2INTCON		0xFF3A		/* Tiemr 2 Interrupt Control */
#define	rT1INTCON		0xFF38		/* Tiemr 1 Interrupt Control */
#define	rT0INTCON		0xFF32		/* Timer 0 Interrupt Control */
#define	rINTSTS			0xFF30		/* Interrupt Status */
#define	rREQST			0xFF2E		/* Interrupt Request */
#define	rINSERV			0xFF2C		/* In-Service */
#define	rPRIMSK			0xFF2A		/* Priority Mask */
#define	rIMASK			0xFF28		/* Interrupt Mask */
#define	rPOLLST			0xFF26		/* Poll Status */
#define	rPOLL				0xFF24		/* Poll */
#define	rEOI				0xFF22		/* End-of-Interrupt */
#define	rINTVEC			0xFF20		/* Interrupt Vector */

/* I/O port defines */
#define	TTL_DATA_OUT		0x101	/* TTL data lines */
#define TTL_CSR			0x103	/* TTL line control */

/*  Data structure for Serial operation */

typedef struct  {
	unsigned char ready;          /* TRUE when ready */
	unsigned char baud;
	unsigned int mode;
	unsigned char iflag;     /* interrupt status     */
	unsigned char* in_buf;        /* Input buffer */
	unsigned int in_tail;        /* Input buffer TAIL ptr */
	unsigned int in_head;        /* Input buffer HEAD ptr */
	unsigned int in_size;        /* Input buffer size */
	unsigned int in_crcnt;       /* Input <CR> count */
	unsigned char in_mt;          /* Input buffer FLAG */
	unsigned char in_full;        /* input buffer full */
	unsigned char* out_buf;       /* Output buffer */
	unsigned int out_tail;       /* Output buffer TAIL ptr */
	unsigned int out_head;       /* Output buffer HEAD ptr */
	unsigned int out_size;       /* Output buffer size */
	unsigned char out_full;       /* Output buffer FLAG */
	unsigned char out_mt;         /* Output buffer MT */
	unsigned char tmso;	// transmit macro service operation
	unsigned char rts;
	unsigned char dtr;
	unsigned char en485;
	unsigned char err;
	unsigned char node;
	unsigned char cr; /* scc CR register    */
	unsigned char slave;
	unsigned int in_segm;       /* input buffer segment */
	unsigned int in_offs;       /* input buffer offset */
	unsigned int out_segm;       /* output buffer segment */
	unsigned int out_offs;       /* output buffer offset */
	unsigned char byte_delay;	/* V25 macro service byte delay */
} COM;


/***********************************************************************
* COM1 Serial Port initializer...
*
* void s1_init( unsigned char b,
*  	unsigned char* ibuf,int isiz, unsigned char* obuf,int osiz, COM *c)
*
* INPUT:
* unsigned char b = Baud rate based on 40 Mhz Clk
* 	baud - baud rate expressed in number 1 to 13
*       baud = 1,               110 baud
*       baud = 2,               150 baud
*       baud = 3,               300 baud
*       baud = 4,               600 baud
*       baud = 5,               1200 baud
*       baud = 6,               2400 baud
*       baud = 7,               4800 baud
*       baud = 8,               9600 baud
*       baud = 9,               19,200 baud (default)
*       baud = 10,              38,400 baud
*		  baud = 11,              57,600 baud
*       baud = 12,              115,200 baud
*       baud = 13,              250,000 baud
*       baud = 14,              500,000 baud
*       baud = 15,              1,250,000 baud
*
*               ibuf    - Pointer to input buffer
*               isize   - Size of input data buffer
*               obuf    - Pointer to output buffer
*               osize   - Size of output data buffer
*               COM structure, defined in ae.h
*
******************************************************/
void s1_init(unsigned char b, unsigned char*ibuf,int isiz,unsigned char* obuf,int osiz,COM *c);

/*****************************************************
;  int putser1(unsigned char outch, COM *c )
;  where: outch   - Character to be output
;			 COM *c, communication structure
;	Return 1, if character is taken into the output buffer
;	Return 0, if not ready, Nothing happen
;	Character will be sent to serial output with interrupt isr
;	(CTS & DTR not checked)
;*****************************************************/
int putser1( unsigned char outch, COM *c);

/*****************************************************
*  putsers1( unsigned char *str, COM *c )
*     Output a string to the serial port
*
*    where:	str - Output string
*				c	- Serial data structure
****************************************************/
int putsers1(char *str, COM *c);

void s1_send_e(void);
void s1_rec_e(void);

/************************************************************
// Function:  char s1_cts(void);
//
//	Return J2 pin 22 current states of P18.
//	NOTE: P18 is input only, may be read by software.
//						return 0, if CTS low
//						return 1, if CTS high
************************************************************/
unsigned char s1_cts(void);

/*************************************************
//		Function:  void s1_rts(char onoff)
//		RTS=J2 pin 31=P19 low, if onoff=0
//		RTS=J2 pin 31=P19 high, if onoff=1
**************************************************/
void s1_rts( char b );

/*******************************************************
;  char getser1(COM *c)     - Get a character from the input buffer
;
;       Return the last one character from s1_in_buf, c->in_tail++
; NOTE: Assumes SERHIT() has been run before,
;		assure that there is a character present
;*****************************************************/
unsigned char getser1( COM *c );

/***********************************************************************
;  getsers1( COM *c, int len, unsigned char* str)
*                        Read string from serial port
*	while( i<len ){
*	while( !serhit1(c) );
*		ch = 0x7f & getser1(c);
*		switch( ch ) {
*		case 0x0d:      str[i++] = '\0';
*				return( i );
*		default:        str[i++] = ch;
*				break; }		}
*	str[i] = '\0';
*	return( len );
*************************************************************************/
int getsers1( COM *c,int len,char *str );

/***********************************************************************
*  SER_CLOSE(COM *c)    - Close down serial port
*   Hardware shut down and interrupt disabled
***********************************************************************/
void s1_close(COM *c);

/*******************************************************
;  int SERHIT(COM *c)   - Return 1 or 0
;       return 1, if anything is in buffer
;			return 0, if not
;******************************************************/
unsigned char serhit1( COM *c );

/******************************************************
;  void CLEAN_SER_SCC( COM *c )        - Flush input buffer
;*******************************************/
void clean_ser1( COM *c );

/****************************************************
//	Function:  unsigned char s1_status(void);
// Return SP1STS
****************************************************/
unsigned int s1_status(void);

void interrupt far s1_isr(void);
void interrupt far dma1_isr(void);



typedef struct{
	unsigned char sec1;
	unsigned char sec10;
	unsigned char min1;
	unsigned char min10;
	unsigned char hour1;
	unsigned char hour10;
	unsigned char day1;
	unsigned char day10;
	unsigned char mon1;
	unsigned char mon10;
	unsigned char year1;
	unsigned char year10;
	unsigned char wk;
} TIM;

void ae_init(void);
void ae_reset(void);
void led(int i);      //P12 used for led
void delay_ms(int m);
void delay0(unsigned int t);
void	HLPRsetvect(
				unsigned int	wVec,		/* Interrupt vector number */
				void	far		*ih		/* Interrupt handler to install */
			);

void clka_en(int i);
void clkb_en(int i);
void pwr_save_en(int i);
void hitwd(void);

//
//	reset ee to remain enabled for reads
//	where s = segment register value pointing to ee starting addr.
//		for example = 0x8000
//
void amd_ee_read_reset(unsigned int s);

//
//	sec=0x00-0x07 for AM29F010, 16K/sector
//		sec=0	0x00000-0x03fff
//		sec=1	0x04000-0x07fff
//		sec=2	0x08000-0x0bfff
//		sec=3	0x0c000-0x0ffff
//		sec=4	0x10000-0x13fff
//		sec=5	0x14000-0x17fff
//		sec=6	0x18000-0x1bfff
//		sec=7	0x1c000-0x1ffff
//
//	sec=0x10-0x17 for AM29F040
//		sec=10	0x00000-0x0ffff
//		sec=11	0x10000-0x1ffff
//		sec=12	0x20000-0x2ffff
//		sec=13	0x30000-0x3ffff
//		sec=14	0x40000-0x4ffff
//		sec=15	0x50000-0x5ffff
//		sec=16	0x60000-0x6ffff
//		sec=17	0x70000-0x7ffff
//	segm=segment register value pointing to ee address 0
// returns:		if pass, return(0);
// 				if fail, return(1);
//
int amd_ee_sec_erase(unsigned int segm, unsigned char sec );

//
//	write one byte dat to AM29F040, at address of s:o
//	Approximately 70 us for 0 wait, 80us for 1 wait.
//		where s=segment register, it is fixed to 0x8000
//				o=offset register
// returns:		if pass, return(0);
// 				if fail, return(1);
//
// Be aware of that a data bit "0" can not be programmed back to a "1" !!!
// Attempting to do so will hang up the system !!!
// you can program the "1"s to "0"s.
// Only erase operation can convert "0"s to "1"s
//
//

int amd_ee_byte_pro_512(unsigned int s, unsigned int o, unsigned char dat);

//
//	write one byte dat to AM29F010, at address of s:o, 80us per byte approx.
//		where s=segment register, you may use s=0x8000-0xe000
//				o=offset register
// returns:		if pass, return(0);
// 				if fail, return(1);
//
// Be aware of that a data bit "0" can not be programmed back to a "1" !!!
// Attempting to do so will hang up the system !!!
// you can program the "1"s to "0"s.
// Only erase operation can convert "0"s to "1"s
//

int amd_ee_byte_pro_128(unsigned int s, unsigned int o, unsigned char dat);

//
// unsigned char rtc_rds(char* time_string);
// put a time string into time_string, based on the reading of RTC.
//	At least 15 bytes of buffer must be available for the time_string
//	returns 0, if RTC OK, or returns 1, if problem
//
unsigned char rtc_rds(char* time_string);
int rtc_rd(TIM *r);
void rtc_init(unsigned char*);


void t2_init(unsigned int tm,unsigned int ta,void interrupt far(*t2_isr)());
void t1_init(unsigned int tm,unsigned int ta,unsigned int tb,void interrupt far(*t1_isr)());
void t0_init(unsigned int tm,unsigned int ta,unsigned int tb,void interrupt far(*t0_isr)());
unsigned int t2_rd(void);
unsigned int t1_rd(void);
unsigned int t0_rd(void);

//	Analog to Digital conversion using TLC2543 on the A-Engine-88/86
//	Input:
//		unsigned char c = input channel
//		c = 0,	input ch = AD0
//		c = 1,	input ch = AD1
//		c = 2,	input ch = AD2
//		c = 3,	input ch = AD3
//		c = 4,	input ch = AD4
//		c = 5,	input ch = AD5
//		c = 6,	input ch = AD6
//		c = 7,	input ch = AD7
//		c = 8,	input ch = AD8
//		c = 9,	input ch = AD9
//		c = a,	input ch = AD10
//	In order to operate ADC, P11 must be input.
//	P11 is shared by RTC, EE. It must be high while power on/reset
//	For AE88, using PPI for ADC, I20,I21,I22 must be output
//	For AE86, using PAL for ADC, T0=CLK, T1=DIN, T2=ADCS
//		Enter the ae_ad12(unsigned char c);  EE is stopped first.
//		Enter the ae86_ad12(unsigned char c);  EE is stopped first.
//
//	Output: 12 bit AD data of the previous channel !
//		Unipolar:
//		(Vref+ - Vref-)=0x7ff
//		Vref- = 0x000
//		Vref+ = 0xfff
//
//
int ae_ad12(unsigned char c);

//	outportb(0x120,1);  // T0=0, CLK
//	outportb(0x128,1);  // T1=0, DIN
//	outportb(0x130,1);  // T2=0, ADCS
int ae86_ad12(unsigned char c);

void nmi_init(void interrupt far (* nmi_isr)());
void int0_init(unsigned char i, void interrupt far (*int0_isr)());
void int1_init(unsigned char i, void interrupt far (*int1_isr)());
void int2_init(unsigned char i, void interrupt far (*int2_isr)());
void int3_init(unsigned char i, void interrupt far (*int3_isr)());
void int4_init(unsigned char i, void interrupt far (*int4_isr)());
void int5_init(unsigned char i, void interrupt far (*int5_isr)());
void int6_init(unsigned char i, void interrupt far (*int6_isr)());


//
// void pio_init(char bit, char mode)
//	where bit=0-31
//			mode=0, Normal operation
//			mode=1, Input with pullup/down
//			mode=2, Output
//			mode=3, input without pull
//
void pio_init(char bit, char mode);


//
//	void pio_wr(char bit, char dat)
//	where bit=0-31
//		dat=0/1
//
void pio_wr(char bit, char dat);

//
// unsigned int pio_rd(char port)
//	return P15-P0, if port=0
//	return P16-P31, if port=1
//
unsigned int pio_rd(char port);

// setup I/O wait states for I/O instructions
//	where wait = 0-7
//	wait=0,			wait states = 0, I/O enable for 100 ns
//	wait=1,			wait states = 1, I/O enable for 100+25 ns
//	wait=2,			wait states = 2, I/O enable for 100+50 ns
//	wait=3,			wait states = 3, I/O enable for 100+75 ns
//	wait=4,			wait states = 5, I/O enable for 100+125 ns
//	wait=5,			wait states = 7, I/O enable for 100+175 ns
//	wait=6,			wait states = 9, I/O enable for 100+225 ns
//	wait=7,			wait states = 15, I/O enable for 100+375 ns
void io_wait(char wait);

unsigned int crc16(unsigned char *wptr, unsigned int count);

/******************************************************
	void ae_da(int dat1, int dat2)
	output dat to U11 DAC of AE88
	Requires P12=CLK, P26=DI, P29=LD/CS as output pins !
	where dat1 for channel A, dat2 for channel B;	dat1/2 = 0-4095
*******************************************************/
void ae_da(int dat1, int dat2);

/******************************************************
	void ae86_da(int dat1, int dat2)
	output dat to U15 DAC of AE86
	Requires T0=CLK=0x120, T1=DI=0x128, T3=LD/CS=0x138
	where dat1 for channel A, dat2 for channel B;	dat1/2 = 0-4095
	Output 0-2.5V at VA=J4.16, VB=J4.18
*******************************************************/
void ae86_da(int dat1, int dat2);




//*****************************************************************************
//                                 LCD/KEYPAD API
//*****************************************************************************
//
// The following API offers a variety of functions for interfacing with the
// LCD/keypad on the TD40 evaluation board.  The dimensions of the LCD screen
// are 16 columns by 2 rows and each position is memory mapped as follows:
//
//              COL1 COL2 COL3 COL4 COL5 COL6 COL7 COL8 ...  COL16
//             ---------------------------------------------------
//       ROW 1 |0x80|0x81|0x82|0x83|0x84|0x85|0x86|0x87|... |0x8f|
//       ROW 2 |0xc0|0xc1|0xc2|0xc3|0xc4|0xc5|0xc6|0xc7|... |0xcf|
//             ---------------------------------------------------
//
// To help make programming the LCD screen easier, a set of useful I/O routines
// are offered:
//
//   * lcd_put(char)            - outputs a character to current cursor position
//   * lcd_putstr(char*)        - outputs a C string to current cursor position
//   * lcd_movecursor(char)     - moves cursor to specified address
//   * lcd_fillrow(int, char)   - fills a specified row with the specified character
//   * lcd_read()               - synchronously reads from the keypad
//   * lcd_init()               - initializes LCD/Keypad
//
// Note that each time the lcd_put() or lcd_putstr() function is called, the
// cursor is moved to the next appropriate position on the LCD screen.
//
// Additionally, the subroutine named lcd_init()only needs to be called once at
// the beginning of the program.
//
//----------------------------------------------------------------------------

void lcd_put(char);
void lcd_putstr(char*);
void lcd_movecursor(unsigned char);
void lcd_fillrow(int, char);
void lcd_cmd(unsigned char);
char lcd_read(void);
void lcd_init(void);


//-----------------------------------------------------------------------------
// Author:	Jered Aasheim
// Date:		November 29, 2000
//
// In order to use dynamic memory allocation on the TERN TD40 evaluation board,
// the heapsize needs to be defined (its default is zero).  Consequently, the
// necessary #define logic from HEAPSIZE.C (distributed by the TERN Corporation)
// has been included into this header file.
//
//-----------------------------------------------------------------------------

/*
//		HEAPSIZE.C - Paradigm C++ Heap Sizing Module
//
//		This module is included in a project to customize the size of the
//		application heaps.  Setting the macro HEAPSIZE to the desired size of the
//		default heap (in KB) is all this is required.
//
//		In compact, large, and huge memory models there is only a single heap
//		that is outside the default data segment and the size is selected by
//		the macro HEAPSIZE.
//
//		In small and medium memory models, you have the option of having two
//		heaps, the default heap which is part of DGROUP (and therefore is limited
//		to a maximum size of 64KB), and a far heap that can use the available RAM
//		in a system.  In this case HEAPSIZE selects the size of the default heap
//		and FHEAPSIZE selects the size of the far heap.
//
//		From the IDE, just add the define HEAPSIZE='###' to the HEAPSIZE.C node
//		to get the desired size.
*/

#if	!defined(HEAPSIZE)				/* HEAPSIZE sets the size of the default heap */
#define	HEAPSIZE			16				/* Create a default 16KB heap */
#endif

#if	!defined(FHEAPSIZE)				/* FHEAPSIZE sets the size of the far heap */
#define	FHEAPSIZE		0				/* Create a default 0KB far heap */
#endif

/*
//		Select the default heap and the far heap sizes
*/

#if	defined(__COMPACT__) || defined(__LARGE__) || defined(__HUGE__)
#define	NEARHEAP			0
#define	FARHEAP			HEAPSIZE
#else
#define	NEARHEAP			HEAPSIZE
#define	FARHEAP			FHEAPSIZE
#endif


/*
//		Do some error checking on the heap selections - no user customization
//		beyond this point unless you know what you are doing.
*/

#if	NEARHEAP > 0 && (defined(__COMPACT__) || defined(__LARGE__) || defined(__HUGE__))
#error Near heap not supported in far data memory models
#endif

#if NEARHEAP > 0
#if NEARHEAP >= 64
#error Near heap size must be less than 64KB
#else
#if defined(__FARBSS__) && (__FARBSS__ == 1)
#pragma option -zX_NHEAP -zYSTACK -zZDGROUP
#else
#pragma option -zE_NHEAP -zFSTACK -zHDGROUP
#endif
//static unsigned char __huge theNearHeap[NEARHEAP * 1024UL] ;
#if defined(__FARBSS__) && (__FARBSS__ == 1)
#pragma option -zX* -zY* -zZ*
#else
#pragma option -zE* -zF* -zH*
#endif
#endif
#endif

#if	FARHEAP > 0
#if	FARHEAP >= 1024 && !defined(__EXTADDR__)
#error	Far heap must be less than 1024KB
#else
#if defined(__FARBSS__) && (__FARBSS__ == 1)
#pragma option -zX* -zYFAR_HEAP -zZ*
#else
#pragma option -zE* -zFFAR_HEAP -zH*
#endif
static unsigned char __huge theFarHeap[FARHEAP * 1024UL] ;
#if defined(__FARBSS__) && (__FARBSS__ == 1)
#pragma option -zX* -zY* -zZ*
#else
#pragma option -zE* -zF* -zH*
#endif
#endif
#endif
