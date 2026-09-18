#include <lpc21xx.h>
#include "header.h"
void lcd_data(unsigned char data)
{
unsigned int temp;
IOCLR1 = 0xFE << 16; 
temp = (data & 0xF0) << 16; 
IOSET1 = temp; 
IOSET1 = 1 << 17; 
IOCLR1 = 1 << 18; 
IOSET1 = 1 << 19; 
delay_ms(2); 
IOCLR1 = 1 << 19; 

IOCLR1 = 0xFE << 16;
IOSET1 = (data & 0x0F) << 20; 
IOSET1 = 1 << 17; 
IOCLR1 = 1 << 18; 
IOSET1 = 1 << 19; 
delay_ms(2);
IOCLR1 = 1 << 19; 
}
void lcd_cmd(unsigned int cmd)
{
unsigned int temp;
IOCLR1 = 0xFE << 16; 
temp = (cmd & 0xF0) << 16; 
IOSET1 = temp; 
IOCLR1 = 1 << 17;
IOCLR1 = 1 << 18; 
IOSET1 = 1 << 19; 
delay_ms(2);
IOCLR1 = 1 << 19; 

IOCLR1 = 0xFE << 16; 
IOSET1 = (cmd & 0x0F) << 20; 
IOCLR1 = 1 << 17; 
IOCLR1 = 1 << 18; 
IOSET1 = 1 << 19; 
delay_ms(2);
IOCLR1 = 1 << 19; 
}
void lcd_init()
{
 IODIR1 = 0xFE << 16; 
 IOCLR1 = 1 << 19; 
 lcd_cmd(0x02); 
 lcd_cmd(0x28); 
 lcd_cmd(0x0E); 
 lcd_cmd(0x01); 
}
void lcd_string(char *ptr)
{
while(*ptr != 0) 
{
lcd_data(*ptr); 
ptr++; 
}
}
void lcd_integer(int num)
{
int a[10], i = 0;
if(num == 0) 
{
lcd_data('0');
}
if(num < 0) 
{
num = -num;
lcd_data('-');
}
while(num > 0) 
{
a[i] = num % 10 + 48; 
num = num / 10; 
i++;
}
for(i = i-1; i >= 0; i--) 
{
lcd_data(a[i]);
}
}

void lcd_float(float f)
{
	int i;
	if(f==0)
	{
		lcd_data('0');
		return;
	}
	if(f<0)
	{
		lcd_data('-');
		f=-f;
	}
	i=(int)f;
	lcd_integer(i);
	lcd_data('-');
	f=(f-i)*100;
	lcd_integer(f);
}



	
