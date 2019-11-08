#include "Delay.h"
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
