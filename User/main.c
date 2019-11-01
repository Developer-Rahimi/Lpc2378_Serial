#include <lpc23xx.h>
  #include "Serial.h"
 #define CCLK 12000000
#define PCLK (CCLK/4)
void delay_s (unsigned int x)
{
x=x*CCLK;
while(x--);
}

void delay_ms(unsigned int x)
{
  x=x*(CCLK/1000);
  while(x--);
}

void delay_us(unsigned int x)
{
x=x*(CCLK/1000000);
while(x--);
}
 int main(void){
   InitSerial(0);
   InitSerial(1);
   InitSerial(2);

 while(1){
  	  SerialPrint(0,"Hello World!\r\n");
	  SerialPrint(1,"Hello World!\r\n");
	  SerialPrint(2,"Hello World!\r\n");
	  delay_ms(1000);
 }
 }
