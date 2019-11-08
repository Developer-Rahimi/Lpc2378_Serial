#ifndef _DELAY_H
#define	_DELAY_H
 #define CCLK 12000000
#define PCLK (CCLK/4)
extern  void delay_s (unsigned int x);

extern	void delay_ms(unsigned int x);

extern	void delay_us(unsigned int x);
#endif
