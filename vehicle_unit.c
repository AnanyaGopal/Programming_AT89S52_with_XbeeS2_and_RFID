#include<reg51.h>
#include<string.h>

// Defining specific pins of the ports
sbit ledred = P2^0;
sbit ledwhite = P2^1;
//sbit zig_veh_rx = P3^0;

// Delay function
void delay(int time){           //When time = 1, delay = 5m
	int i,j;
	for(i=0;i<time;i++)
	for(j=0;j<1275;j++);
}

//Serial communication
void serial_setup()	   {
 IE= 0x90;			   //EnableInterrupt bit=1, EnableSerialIntBit=1//10010000
 SCON = 0x50;		  //SM1=1,REN=1//01010000
 TMOD = 0x20;	      //Timer1 mode1 for serial communication
 TH1 = -3;			  //baud rate=9600
 TR1=1;				   //Start Timer 1
}

/* Serial Interrupt service routine 
 * The other zigbee will either send a 1 or a zero
 * Receive data completely at SBUF
 */	   

void rx_isr() interrupt 4{	   //Serial Interrupt service routine  
	while(RI==0); 
		if(RI==1){
			P2 = SBUF;
		//	if(SBUF == 9){
		//			ledwhite = 1;
		//			ledred   = 0;
		//		}
		//	if(SBUF == 1){
		//		   ledred     = 1;
		//		   ledwhite   = 0;
		//	} else {
		//		  ledred     = 1;
		//		  ledwhite   = 1;
		//	}
	}
	RI=0;
}
void main(){
	ledred     = 0;
}
