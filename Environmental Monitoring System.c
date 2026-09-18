#include <LPC21xx.H>
#include"header.h"
#include <stdio.h>

#define WATER  ((IOPIN0>>14)&1)
#define Green  1<<17
#define Red  1<<18

int main(){

unsigned int a_value=0,a_value1,soil,ldr;
float vout=0,temp=0;
char a[20];

lcd_init();
uart_init(9600);
adc_init();

	while(1){
	lcd_cmd(0x80);
			uart_str("\r\n--:Tempurature:--");
			lcd_str("Temp: ");

			//============ TEMP ==========
	 		a_value=adc_read(1);
		 	vout=(a_value*3.3)/1023;
	 		temp=(vout-0.5)/0.01;
				
			lcd_cmd(0x80);
			lcd_str("Temp:");
	 	  lcd_float(temp);
					 
			//=========== SOIL ===========
		 	a_value1=adc_read(0); 
		 	soil=(a_value1/1023.0)*100;
			//============ LDR ===========
			ldr=adc_read(3);

			//============================
		 	sprintf(a,"\r\nTemperature:%.2f\r\nSoil Moisture:%d",temp,soil);
	 		uart_str(a);

				if(ldr>=600){
					sprintf(a,"\r\nLight level:Dark");
					uart_str(a);
				}
				else if(ldr>=200&&ldr<=600){
					sprintf(a,"\r\nClimate:Normal");
					uart_str(a);
				}
				else{
					sprintf(a,"\r\nClimate:Sunny");
					uart_str(a);
				}

			//==========Water sensor==================
			lcd_cmd(0xc0);
			lcd_str("Status:");
			 if(WATER==0){
					sprintf(a,"\r\nWater Sensor:NOT DETECTED\r\nSYSTEM Status:SAFE\r\nLED Status:GREEN\r\n"); 
					uart_str(a);
					lcd_str("SAFE");
					IOSET0=Red;
					IOCLR0=Green;

				}
			else{
					sprintf(a,"\r\nWater Sensor:DETECTED \r\nSYSTEM Status:ALERT \r\nLED Status:RED\r\n");  
					uart_str(a);
					lcd_str("ALERT");
					IOSET0=Green;
					IOCLR0=Red;
				}
			delay_ms(2000);		
	}
}
