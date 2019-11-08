#include <lpc23xx.h>
#include "Serial.h"
#include "Delay.h"
char *Serial;

 int main(void){
	   InitSerial(0);
	   InitSerial(1);
	   InitSerial(2);
	   InitSerial(3);
	 while(1){
	  	  SerialPrint(0,"Hello World!\r\n");
		  SerialPrint(1,"Hello World!\r\n");
		  SerialPrint(2,"Hello World!\r\n");
		  SerialPrint(3,"Hello World!\r\n");
		  Serial=GetString(0);
		  if(GetStringLength(0)){
		  	 SerialPrint(0,Serial); 
		  }
		   Serial=GetString(1);
		  if(GetStringLength(1)){
		  	 SerialPrint(1,Serial); 
		  }	 
		  Serial=GetString(2);
		  if(GetStringLength(2)){
		  	 SerialPrint(2,Serial); 
		  }	 
		 	Serial=GetString(3);
		  if(GetStringLength(3)){
		  	 SerialPrint(3,Serial); 
		  }
		  delay_ms(2000);
	 }
 }
