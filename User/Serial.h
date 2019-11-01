#ifndef _SERIAL_H
#define	_SERIAL_H
extern  void InitSerial (int Port);
extern void sendchar (int ch,int Port);
extern void SerialPrint(int Port,char *Text);
#endif
