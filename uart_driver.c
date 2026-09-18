#include<lpc21xx.h>
#define THRE ((U0LSR>>5)&1)
void uart0_init(unsigned int boud)
{
	unsigned int pclk,result=0;
	if(VPBDIV==0x0)
		pclk=15000000;
	else if(VPBDIV==0x01)
		pclk=6000000;
	result=pclk|(16*boud);
	PINSEL0|=0x05;
	U0LCR=0x83;
	U0DLM=(result>>0)&0xff;
	U0LCR=0x03;
}
void uart0_tx(unsigned char data)
{
	U0THR=data;
	while(THRE==0);
}
#define ROR (U0LSR & 1)
unsigned char uart0_rx()
{
 while(ROR ==0);
	return U0RBR;
}
void uart0_tx_string(char *ptr)
{
	while(*ptr!=0)
	{
		uart0_tx(*ptr);
		ptr++;
	}
}


void uart0_integer(int num)
{
int a[10], i = 0;
if(num == 0) 
{
uart0_tx('0');
}
if(num < 0) 
{
num = -num;
uart0_tx('-');
}
while(num > 0) 
{
a[i] = num % 10 + 48; 
num = num / 10; 
i++;
}
for(i = i-1; i >= 0; i--) 
{
uart0_tx(a[i]);
}
}

void uart0_float(float f)
{
	int i;
	if(f==0)
	{
		uart0_tx('0');
		return;
	}
	if(f<0)
	{
		uart0_tx('-');
		f=-f;
	}
	i=(int)f;
	uart0_integer(i);
	uart0_tx('-');
	f=(f-i)*100;
	uart0_integer(f);
}

