 #include <lpc23xx.h>
 #include "Serial.h"
 void InitSerial (int Port)  {
 switch(Port){               
 	case 0: 
    	PINSEL0 |= 0x00000050;               	/* Enable TxD0 and RxD0              */
  		U0FDR    = 0;                          	/* Fractional divider not used       */
  		U0LCR    = 0x83;                       	/* 8 bits, no Parity, 1 Stop bit     */
  		U0DLL    = 78;                         	/* 9600 Baud Rate @ 12.0 MHZ PCLK    */
  		U0DLM    = 0;                          	/* High divisor latch = 0            */
  		U0LCR    = 0x03;                       	/* DLAB = 0                          */
 	 break;
	 case 1: 
    	PINSEL0 |= 0x40000000;               	/* Enable TxD1                p0.15--p0.16       */	 
    	PINSEL1 |= 0x00000001;               	/* Enable RxD1                       */
  		U1FDR    = 0;                          	/* Fractional divider not used       */
  		U1LCR    = 0x83;                       	/* 8 bits, no Parity, 1 Stop bit     */
  		U1DLL    = 78;                         	/* 9600 Baud Rate @ 12.0 MHZ PCLK    */
  		U1DLM    = 0;                          	/* High divisor latch = 0            */
  		U1LCR    = 0x03;                       	/* DLAB = 0                          */
 	 break;
	 case 2: 
    	PINSEL0 |= 0x0500000;               	/* Enable TxD1 p0.10---p0.11         */
  		U2FDR    = 0;                          	/* Fractional divider not used       */
  		U2LCR    = 0x83;                       	/* 8 bits, no Parity, 1 Stop bit     */
  		U2DLL    = 78;                         	/* 9600 Baud Rate @ 12.0 MHZ PCLK    */
  		U2DLM    = 0;                          	/* High divisor latch = 0            */
  		U2LCR    = 0x03;                       	/* DLAB = 0                          */
 	 break;
	 case 3: 
    	PINSEL0 |= 0x000000A;               	/* p0.0-- p[0.1                      */
  		U3FDR    = 0;                          	/* Fractional divider not used       */
  		U3LCR    = 0x83;                       	/* 8 bits, no Parity, 1 Stop bit     */
  		U3DLL    = 78;                         	/* 9600 Baud Rate @ 12.0 MHZ PCLK    */
  		U3DLM    = 0;                          	/* High divisor latch = 0            */
  		U3LCR    = 0x03;                       	/* DLAB = 0                          */
 	 break;
  }
}
void sendchar (int ch,int Port)  {                 /* Write character to Serial Port    */
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
