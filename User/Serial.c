 #include <lpc23xx.h>
 #include "Serial.h"
 #include "Delay.h"
int length[4]={0,0,0,0};
char data[255];//={"","","",""};
//int length=0;
 static unsigned int tx_restart = 1;   /* NZ if TX restart is required */

#define TBUF_SIZE   256	     /*** Must be a power of 2 (2,4,8,16,32,64,128,256,512,...) ***/
#define RBUF_SIZE   256      /*** Must be a power of 2 (2,4,8,16,32,64,128,256,512,...) ***/

#if RBUF_SIZE < 2
#error RBUF_SIZE is too small.  It must be larger than 1.
#elif ((RBUF_SIZE & (RBUF_SIZE-1)) != 0)
#error RBUF_SIZE must be a power of 2.
#endif

 #if TBUF_SIZE < 2
#error TBUF_SIZE is too small.  It must be larger than 1.
#elif ((TBUF_SIZE & (TBUF_SIZE-1)) != 0)
#error TBUF_SIZE must be a power of 2.
#endif

struct buf_uart0 {
  unsigned int in;          /* Next In Index */
  unsigned int out;         /* Next Out Index */
  char buf [RBUF_SIZE];     /* Buffer */
};

struct buf_uart1 {
  unsigned int in;          /* Next In Index */
  unsigned int out;         /* Next Out Index */
  char buf [RBUF_SIZE];     /* Buffer */
};

struct buf_uart2 {
  unsigned int in;          /* Next In Index */
  unsigned int out;         /* Next Out Index */
  char buf [RBUF_SIZE];     /* Buffer */
};

struct buf_uart3 {
  unsigned int in;          /* Next In Index */
  unsigned int out;         /* Next Out Index */
  char buf [RBUF_SIZE];     /* Buffer */
};
/***************************UART0***************************************/
static struct buf_uart0 rbuf_uart0 = { 0, 0, };
#define SIO_RBUFLEN_UART0 ((unsigned short)(rbuf_uart0.in - rbuf_uart0.out))

static struct buf_uart0 tbuf_uart0 = { 0, 0, };
#define SIO_TBUFLEN_UART0 ((unsigned short)(tbuf_uart0.in - tbuf_uart0.out))

/***************************UART1***************************************/
static struct buf_uart1 rbuf_uart1 = { 0, 0, };
#define SIO_RBUFLEN_UART1 ((unsigned short)(rbuf_uart1.in - rbuf_uart1.out))

static struct buf_uart1 tbuf_uart1 = { 0, 0, };
#define SIO_TBUFLEN_UART1 ((unsigned short)(tbuf_uart1.in - tbuf_uart1.out))
/***************************UART2***************************************/
static struct buf_uart2 rbuf_uart2 = { 0, 0, };
#define SIO_RBUFLEN_UART2 ((unsigned short)(rbuf_uart2.in - rbuf_uart2.out))

static struct buf_uart2 tbuf_uart2 = { 0, 0, };
#define SIO_TBUFLEN_UART2 ((unsigned short)(tbuf_uart2.in - tbuf_uart2.out))
/***************************UART3***************************************/
static struct buf_uart3 rbuf_uart3 = { 0, 0, };
#define SIO_RBUFLEN_UART3 ((unsigned short)(rbuf_uart3.in - rbuf_uart3.out))

static struct buf_uart3 tbuf_uart3 = { 0, 0, };
#define SIO_TBUFLEN_UART3 ((unsigned short)(tbuf_uart3.in - tbuf_uart3.out))

 void IRQ_UART0 (void) __irq {
  volatile char dummy;
  volatile char IIR;
  struct buf_uart0 *p;
  while (((IIR = U0IIR) & 0x01) == 0) {
     switch (IIR & 0x0E) {
       case 0x06: 
         dummy = U0LSR;  
         break;

       case 0x04: 
       case 0x0C: 
         p = &rbuf_uart0;

         if (((p->in - p->out) & ~(RBUF_SIZE-1)) == 0) {
           p->buf [p->in & (RBUF_SIZE-1)] = U0RBR;
           p->in++;
         }
         break;

       case 0x02: 
	    
         p = &tbuf_uart0;

         if (p->in != p->out) {
           U0THR = p->buf [p->out & (TBUF_SIZE-1)];
           p->out++;
           tx_restart = 0;
         }
         else {
           tx_restart = 1;
		   
         }
         break;

       case 0x00: 
	  
         dummy = U1MSR; 
         break;

       default:
         break;
     }
  }		
 
  VICVectAddr = 0; 
}
void IRQ_UART1 (void) __irq {
  volatile char dummy;
  volatile char IIR;
  struct buf_uart1 *p;
  while (((IIR = U1IIR) & 0x01) == 0) {
     switch (IIR & 0x0E) {
       case 0x06: 
         dummy = U1LSR;  
         break;

       case 0x04: 
       case 0x0C: 
         p = &rbuf_uart1;

         if (((p->in - p->out) & ~(RBUF_SIZE-1)) == 0) {
           p->buf [p->in & (RBUF_SIZE-1)] = U1RBR;
           p->in++;
         }
         break;
       case 0x02: 
         p = &tbuf_uart1;
         if (p->in != p->out) {
           U1THR = p->buf [p->out & (TBUF_SIZE-1)];
           p->out++;
           tx_restart = 0;
         }
         else {
           tx_restart = 1;
		   
         }
         break;

       case 0x00: 
	  
         dummy = U1MSR; 
         break;

       default:
         break;
     }
  }		
 
  VICVectAddr = 0; 
}
void IRQ_UART2 (void) __irq {
  volatile char dummy;
  volatile char IIR;
  struct buf_uart2 *p;
  while (((IIR = U2IIR) & 0x01) == 0) {
     switch (IIR & 0x0E) {
       case 0x06: 
         dummy = U2LSR;  
         break;

       case 0x04: 
       case 0x0C: 
         p = &rbuf_uart2;

         if (((p->in - p->out) & ~(RBUF_SIZE-1)) == 0) {
           p->buf [p->in & (RBUF_SIZE-1)] = U2RBR;
           p->in++;
         }
         break;
       case 0x02: 
         p = &tbuf_uart2;
         if (p->in != p->out) {
           U2THR = p->buf [p->out & (TBUF_SIZE-1)];
           p->out++;
           tx_restart = 0;
         }
         else {
           tx_restart = 1;
		   
         }
         break;

       case 0x00: 
	  
         dummy = U1MSR; 
         break;

       default:
         break;
     }
  }		
 
  VICVectAddr = 0; 
}
void IRQ_UART3 (void) __irq {
  volatile char dummy;
  volatile char IIR;
  struct buf_uart3 *p;
  while (((IIR = U3IIR) & 0x01) == 0) {
     switch (IIR & 0x0E) {
       case 0x06: 
         dummy = U3LSR;  
         break;

       case 0x04: 
       case 0x0C: 
         p = &rbuf_uart3;

         if (((p->in - p->out) & ~(RBUF_SIZE-1)) == 0) {
           p->buf [p->in & (RBUF_SIZE-1)] = U3RBR;
           p->in++;
         }
         break;
       case 0x02: 
         p = &tbuf_uart3;
         if (p->in != p->out) {
           U3THR = p->buf [p->out & (TBUF_SIZE-1)];
           p->out++;
           tx_restart = 0;
         }
         else {
           tx_restart = 1;
		   
         }
         break;

       case 0x00: 
	  
         dummy = U1MSR; 
         break;

       default:
         break;
     }
  }		
 
  VICVectAddr = 0; 
}
 void InitSerial (int Port)  {
 switch(Port){               
 	case 0: 
    	PINSEL0 |= 0x00000050;               	/* Enable TxD0 and RxD0              */
  		U0FDR    = 0;                          	/* Fractional divider not used       */
  		U0LCR    = 0x83;                       	/* 8 bits, no Parity, 1 Stop bit     */
  		U0DLL    = 78;                         	/* 9600 Baud Rate @ 12.0 MHZ PCLK    */
  		U0DLM    = 0;                          	/* High divisor latch = 0            */
  		U0LCR    = 0x03;                       	/* DLAB = 0                          */
		U0IER = 0;               

	  	VICVectAddr6 = (unsigned long)IRQ_UART0;
	  	VICVectCntl6 = 15;       
	  	VICIntEnable = 1 <<6;
	  	U0IER = 3;
 	 break;
	 case 1: 
    	PINSEL0 |= 0x40000000;               	/* Enable TxD1                p0.15--p0.16       */	 
    	PINSEL1 |= 0x00000001;               	/* Enable RxD1                       */
  		U1FDR    = 0;                          	/* Fractional divider not used       */
  		U1LCR    = 0x83;                       	/* 8 bits, no Parity, 1 Stop bit     */
  		U1DLL    = 78;                         	/* 9600 Baud Rate @ 12.0 MHZ PCLK    */
  		U1DLM    = 0;                          	/* High divisor latch = 0            */
  		U1LCR    = 0x03;                       	/* DLAB = 0                          */
		U1IER = 0;               

	  	VICVectAddr7 = (unsigned long)IRQ_UART1;
	  	VICVectCntl7 = 15;       
	  	VICIntEnable = 1 <<7;
	  	U1IER = 3;       
 	 break;
	 case 2: 
    	PINSEL4 |= 0x000A0000;
  		U2FDR    = 0;                          	/* Fractional divider not used       */
  		U2LCR    = 0x83;                       	/* 8 bits, no Parity, 1 Stop bit     */
  		U2DLL    = 78;                         	/* 19200 Baud Rate @ 12.0 MHZ PCLK    */
  		U2DLM    = 0;                          	/* High divisor latch = 0            */
  		U2LCR    = 0x03;                       	/* DLAB = 0                          */
		U2IER = 0;
		VICVectAddr28 = (unsigned long)IRQ_UART2;
	  	VICVectCntl28 = 15;       
	  	VICIntEnable = 1 <<28;
	  	U2IER = 3;
 	 break;
	 case 3: 
    	PINSEL1 |= 0x003C0000;                                    /* Enable TxD3  rxd=p0.26   txd=p0.25*/
  		U3FDR    = 0;                          	/* Fractional divider not used       */
  		U3LCR    = 0x83;                       	/* 8 bits, no Parity, 1 Stop bit     */
  		U3DLL    = 78;                         	/* 9600 Baud Rate @ 12.0 MHZ PCLK    */
  		U3DLM    = 0;                          	/* High divisor latch = 0            */
  		U3LCR    = 0x03;                       	/* DLAB = 0                          */
		U3IER = 0;
		VICVectAddr29 = (unsigned long)IRQ_UART3;
	  	VICVectCntl29 = 15;       
	  	VICIntEnable = 1 <<29;
	  	U3IER = 3;
 	 break;
  }
}
void sendchar (int ch,int Port)  {                
  switch(Port){
  	case 0:
  		while (!(U0LSR & 0x20));
  		U0THR = ch;
	break;
	case 1:
  		while (!(U1LSR & 0x20));
  		U1THR = ch;
	break;
	case 2:
  		while (!(U2LSR & 0x20));
  		U2THR = ch;
	break;
	case 3:
  		while (!(U3LSR & 0x20));
  		U3THR = ch;
	break;
  }
}
void SerialPrint(int Port,char *Text){
		int i=0;
	   for(i=0;Text[i]!='\0';i++)
	  		sendchar (Text[i],Port);
	  
}
 int GetChar_uart0(void){
	struct buf_uart0 *p = &rbuf_uart0;
	if (SIO_RBUFLEN_UART0 == 0)
	    return (-1);
	return (p->buf [(p->out++) & (RBUF_SIZE - 1)]);
}
 int GetChar_uart1(void){
	struct buf_uart1 *p = &rbuf_uart1;
	if (SIO_RBUFLEN_UART1 == 0)
	    return (-1);
	return (p->buf [(p->out++) & (RBUF_SIZE - 1)]);
}
int GetChar_uart2(void){
	struct buf_uart2 *p = &rbuf_uart2;
	if (SIO_RBUFLEN_UART2 == 0)
	    return (-1);
	return (p->buf [(p->out++) & (RBUF_SIZE - 1)]);
}
int GetChar_uart3(void){
	struct buf_uart3 *p = &rbuf_uart3;
	if (SIO_RBUFLEN_UART3 == 0)
	    return (-1);
	return (p->buf [(p->out++) & (RBUF_SIZE - 1)]);
}
char *GetString(int Port){
	int f=0;
	int d=0;
	int end=1;
	
	 for( f=0;f<256;f++)
	 	data[f]='\0';
		length[Port]=0;
	while(end){
			switch(Port){
				case 0:
					d= GetChar_uart0();
					if(d!=-1){
					data[length[Port]]=d;
					length[Port]++;
					}
					else{
						end=0;
					}
				break;		
				case 1:
					d= GetChar_uart1();
					if(d!=-1){
					data[length[Port]]=d;
					length[Port]++;
					}
					else{
						end=0;
					}
				break;
				case 2:
					d= GetChar_uart2();
					if(d!=-1){
					data[length[Port]]=d;
					length[Port]++;
					}
					else{
						end=0;
					}
				break;
				case 3:
					d= GetChar_uart3();
					if(d!=-1){
					data[length[Port]]=d;
					length[Port]++;
					}
					else{
						end=0;
						
					}
				break;
			}
			
		}
		return data;	
}
int	GetStringLength(int Port){
  return length[Port];	
}
